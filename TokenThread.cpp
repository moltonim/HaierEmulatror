//---------------------------------------------------------------------------

#include <vcl.h>
#include <dateutils.hpp>
#pragma hdrstop

#include "TokenThread.h"
#include "Unit1.h"
#include "SerialPort.h"
#include "SendCustomMsgForm.h"
#pragma package(smart_init)

#include "Define.h"

#define STATUS_TIMER_RELOAD_ms      6000

extern TSerialPort *Ser;
extern SERBUF_STRUCT comBuf;
extern unsigned long LenReaden;
extern bool DebugFlag;

int res;

//---------------------------------------------------------------------------

//   Important: Methods and properties of objects in VCL can only be
//   used in a method called using Synchronize, for example:
//
//      Synchronize(UpdateCaption);
//
//   where UpdateCaption could look like:
//
//      void __fastcall TockenThread::UpdateCaption()
//      {
//        Form1->Caption = "Updated in a thread";
//      }
//---------------------------------------------------------------------------

__fastcall TokenThread::TokenThread(bool CreateSuspended)
    : TThread(CreateSuspended)
{
    Priority = tpHigher;
    res = 0;
    StatusTimer = 0;
    Connected = false;
}
//---------------------------------------------------------------------------

void __fastcall TokenThread::Execute()
{
    //---- Place thread code here ----

    char* p;
    int ris;
    int n;

    while(!Terminated)
    {
        Synchronize(HeartBeat);             //gestione live led
        if (Form1->F2Req == true)
            Synchronize(SendRequestTest);   //Richiesta invio messaggio?

        Synchronize(SendAlarmFrame);

        Synchronize(SendStatus);
        
        Sleep(9);
        res = Ser->GetCharRXBuf();
        Synchronize(CommReceiving);
        if (res <= 0)
        {
            //Synchronize(CommReceiving);
            continue;
        }
        
        if (res > 100)
            res = 100;
        p = comBuf.buf;
        if (res+comBuf.rcv_pointer > sizeof(comBuf.buf))
            comBuf.rcv_pointer = 0;

        p += comBuf.rcv_pointer;
        LenReaden = 0;
        ris = -Ser->BIN_Read(p, res, LenReaden);

        if (ris == COMM_OK && LenReaden != 0)
        {
            comBuf.rcv_pointer += LenReaden;
            //if (comBuf.rcv_pointer > 700)     //debug purpose only!
                AnalizeRcv();
        }

        if (ris != COMM_OK)
            LenReaden++;

    }   //end while
    
}


void __fastcall TokenThread::HeartBeat(void)
{
    static unsigned int ms;
    unsigned int n = MilliSecondOfTheDay(Now());

    if ((n - ms) > 250)
    {
        ms = n;
        Form1->LiveRB->Checked = !Form1->LiveRB->Checked;
    }
}

//---------------------------------------------------------------------------

void __fastcall TokenThread::CommReceiving(void)
{
    String s;
    if (res )
    {
        s = "Receiving";
    //else    s = "Disconnect";
        if (comBuf.connect)
            Form1->StatusBar1->Panels->Items[0]->Text = s;
    }

}


void __fastcall TokenThread::AnalizeRcv(void)
{
    //Analyze recv buffer
    int n, t;
    if (comBuf.rcv_pointer <= 1)
        return;

    //Form1->ComReceiveTimer->Enabled = false;

    t++;

    for (n = 0; n < comBuf.rcv_pointer-1; n++)
    {
        if (comBuf.buf[n] == 0xFF && comBuf.buf[n+1] == 0xFF) //SOT found!
        {
            if (n == 0)
                continue;
            t = 0;
            memcpy(comBuf.msg, comBuf.buf, n);
            comBuf.rcv_size = n;
            memmove((char*)&comBuf.buf[0], (char*)&comBuf.buf[n], comBuf.rcv_pointer);
            comBuf.rcv_pointer -= n;
            t = sizeof(comBuf.buf)-comBuf.rcv_pointer;
                Synchronize(MessageReceived);
            n  = 0;
        }
    }
}


void __fastcall TokenThread::SendStatus(void)
{
    int n = MilliSecondOfTheWeek(Now()) - StatusTimer;

    if ( Connected == true &&
         ( (Form1->StatusCKB->Checked == true && n > STATUS_TIMER_RELOAD_ms) ||
         Form1->Cmd6Req == true )
       )
    {
        Form1->Cmd6Req = false;
        SendComAnsw(0x06);
        StatusTimer = MilliSecondOfTheWeek(Now());
    }

    if (Connected == true && Form1->Cmd09Req == true)
    {
        Form1->Cmd09Req = false;
        // forzare il comando 09!!!
        SendComAnsw(0x09);
        Form1->RichEdit1->SelAttributes->Color = clRed;
        Form1->RichEdit1->Lines->Add("Frame 09 'Module stop device alarm info' forced");
        Application->ProcessMessages();
    }

    if (Connected == true && Form1->Cmd7CReq == true)
    {
        Form1->Cmd7CReq = false;
        // forzare il comando 7C!!!
        SendComAnsw(0x7C);
        Form1->RichEdit1->SelAttributes->Color = clRed;
        Form1->RichEdit1->Lines->Add("Frame 7C 'Device active reporting interval' forced");
        Application->ProcessMessages();
    }

    if (!Connected &&
         (Form1->Cmd6Req == true || Form1->Cmd09Req == true)
        )
    {
        Form1->RichEdit1->SelAttributes->Color = clRed;
        Form1->RichEdit1->Lines->Add("Not connected!");
        Form1->Cmd6Req = false;
        Form1->Cmd09Req = false;
        Application->ProcessMessages();
    }

    String s;
    n %= 10000;
    n /=10;
    s.sprintf("%01d.%02d", n/100, (n%100));
    Form1->Label1->Caption = s;
}

/*
    Nota: cambia errore: trasmetto frame 04, poi:
    1.Need to reply within 50s;
    2.If the device does not receive the confirmation frame of 05, it will send 04 every 200ms;
    3.When the device receives 05, it will pause 5s and continue to send 04 at the frequency of 200ms;
    4.After receiving 09, the device will stop sending the current alarm;
    5.If the alarm status changes, the alarm will be resend;
    6.Status changes include the creation of new alarms or the disappearance of existing alarms;
    7.If all alarms disappear, send an alarm command with all zeros as per the rules until 09 is received;
    8.When an alarm is generated, query and shutdown commands can be supported.
    
*/
void __fastcall TokenThread::SendAlarmFrame(void)
{
    String s;
    int ris = 0;
    int n;
    __int64 t;

    if (AlrmBuf.err_present && AlrmBuf.ack_received  )
    {
        t = MilliSecondOfTheYear(Now());
        if (t > AlrmBuf.Delay5sec )
        {
            AlrmBuf.ack_received = 0;
            AlrmBuf.msg_toSend = 1;
            if (DebugFlag)
            {
                Form1->RichEdit1->SelAttributes->Color = clWhite;
                Form1->RichEdit1->Lines->Add(" debug: 5 sec alrm passed");
                Application->ProcessMessages();
            }
        }
    }
    if (AlrmBuf.err_present && AlrmBuf.msg_sent)
    {
        t = MilliSecondOfTheYear(Now());
        if (t > AlrmBuf.Delay200ms)
        {
            AlrmBuf.msg_toSend = 1;
            if (DebugFlag)
            {
                Form1->RichEdit1->SelAttributes->Color = clWhite;
                Form1->RichEdit1->Lines->Add(" debug: 200 ms alrm ack not recvd");
                Application->ProcessMessages();
                AlrmBuf.Delay200ms = MilliSecondOfTheYear(Now()) + 200;
            }
        }
    }
    if (AlrmBuf.err_present == 0 && AlrmBuf.err_zero )
    {
        AlrmBuf.err_zero = 0;
        AlrmBuf.msg_toSend = 1;
        AlrmBuf.ack_received = 0;
    }

    if (AlrmBuf.msg_toSend == 1)
    {
        AlrmBuf.msg_sent = 1;
        AlrmBuf.msg_toSend = 0;
        AlrmBuf.ack_received = 0;
        //Form1->RichEdit1->SelAttributes->Color = clFuchsia;
        n = UpdateAlrmMsg(0x04);
        s.sprintf("[04] Alarm sent: len = %d\n", n-3);
        if (Form1->SendAnswerPopMnu->Checked)
            ris = -Ser->BIN_Write(Answ_73, n, LenReaden);
        if (ris)
            ris++;
        AlrmBuf.Delay200ms = MilliSecondOfTheYear(Now()) + 210; //Add 10ms due to task tick
        s += Form1->FormatSendString(Answ_73, n);
        Form1->RichEdit1->SelAttributes->Color = clFuchsia;
        Form1->RichEdit1->Lines->Add(s);
        if (!Form2->Visible)
            Form1->RichEdit1->SetFocus();
        UpdateLog(NULL, 'w', "W => "+s, 0);
        }
}


void __fastcall TokenThread::SendRequestTest(void)
{
    String s;
    int ris = 0;
    if ( Form1->F2Req == true)
    {
        Form1->ConfigRequestBttn->Enabled = true;
        Form1->F2_SentCKB->Checked = true;
        Form1->F2Req = false;
        if (Form1->SendAnswerPopMnu->Checked)
            ris = -Ser->BIN_Write(Answ_F2, Answ_F2_LEN, LenReaden);
        if (ris)
            ris++;
        s = "Module enters configuration mode frame: ";
        s += Form1->FormatSendString(Answ_F2, Answ_F2_LEN);

        Form1->RichEdit1->SelAttributes->Color = clFuchsia;
        Form1->RichEdit1->Lines->Add(s);
        if (!Form2->Visible)
            Form1->RichEdit1->SetFocus();
        UpdateLog(NULL, 'r', "W => "+s, comBuf.rcv_size);
    }
}


void __fastcall TokenThread::MessageReceived(void)
{
    int n;
    String s, r;

    s.sprintf("%d", comBuf.rcv_pointer);
    Form1->Edit1->Text = s;

    if (comBuf.rcv_size <= 2)
        return;

    /*
    n = CalcCKS(comBuf.msg);
    if (n != comBuf.msg[comBuf.rcv_size-1])
        return;
    */
    if (!CheckCKSrx(comBuf.msg))
    {
        n++;
        return;
    }

    s = Form1->FormatSendString(comBuf.msg, comBuf.rcv_size);
    /*n = 43 - s.Length();
    if (n < 0)
        n = 0;
    while(n--)
        s += " ";*/
    s += "\nReceive: ";
    int v = comBuf.msg[9];
    int cmd = FindCmdIdx(v);

    if (cmd != -1)
    {
        Form1->RichEdit1->SelAttributes->Color = clLime;
        r.sprintf("len = %d cmd = 0x%02X", comBuf.msg[2], serial_cmd[cmd].val);
        s += r;
    }
    else
    {
        Form1->RichEdit1->SelAttributes->Color = clRed;
        s += "Unknow message";
        UpdateLog(NULL, 'r', "Unknow message: ", comBuf.rcv_size);
    }

    UpdateLog(NULL, 'r', "R => "+s, 0);
    Form1->RichEdit1->Lines->Add(s);
    SendComAnsw(serial_cmd[cmd].val);
}

void __fastcall TokenThread::SendComAnsw(int cmd)
{
    int n;
    String s = "";
    String r;
    int ris = 0;
    int fail = 0;

    switch (cmd)
    {
        case 0x61:
            Form1->RichEdit1->SelAttributes->Color = clAqua;
            //s = "[62] Device version response: ";
            s.sprintf("[62] Device version response; len = %d\n", Answ_62_LEN-3);
            if (Form1->SendAnswerPopMnu->Checked)
                ris = -Ser->BIN_Write(Answ_62, Answ_62_LEN, LenReaden);
            if (ris)
                ris++;
            s += Form1->FormatSendString(Answ_62, Answ_62_LEN);
        break;

        case 0x70:
            Form1->RichEdit1->SelAttributes->Color = clAqua;
            s.sprintf("[71] Device ID response %s; len = %d\:\n", Answ71S.c_str(), Answ_71_LEN-3);
            if (Form1->SendAnswerPopMnu->Checked)
                ris = -Ser->BIN_Write(answ71, Answ_71_LEN, LenReaden);
            if (ris)
                ris++;
            s += Form1->FormatSendString(answ71, Answ_71_LEN);
        break;

        case 0x01:      //Query attribute status
            //Form1->RichEdit1->SelAttributes->Color = clYellow;
            n = Form1->DeviceComboBox->ItemIndex;
            // Aggiungere qui il parser oppure il comando ricevuto etc!
            //aggiornare il colore (fuxia?) in caso di comando

            if (comBuf.msg[10] == 0x5D)
            {
                Form1->RichEdit1->SelAttributes->Color = clFuchsia;
                s.sprintf(">> Command: %02x, val = %02x %02x",
                    comBuf.msg[11], comBuf.msg[12], comBuf.msg[13]);
                Form1->RichEdit1->Lines->Add(s);

                Application->ProcessMessages();
                UpdateLog(NULL, 'w', "W => "+s, 0);
                Application->ProcessMessages();
            }

            Form1->RichEdit1->SelAttributes->Color = clYellow;
            n = UpdateStateMsg(n, 0);
            s.sprintf("[02] Answer Status; len = %d \n", n-3);
            if (Form1->SendAnswerPopMnu->Checked)
                ris = -Ser->BIN_Write(Answ_014D01, n, LenReaden);
            if (ris)
                ris++;
            s += Form1->FormatSendString(Answ_014D01, n);
        break;

        case 0x06:      //!SELF! attribute status (every 6 secs)
            //Form1->RichEdit1->SelAttributes->Color = DebugFlag? clYellow:clAqua;
            Form1->RichEdit1->SelAttributes->Color = clYellow;
            //^^ aggiustare qui: o yellow o aqua!    [done]
            n = Form1->DeviceComboBox->ItemIndex;
            n = UpdateStateMsg(n, 1);
            s.sprintf("[06] Send Status; len = %d \n", n-3);
            if (Form1->SendAnswerPopMnu->Checked)
                ris = -Ser->BIN_Write(Answ_014D01, n, LenReaden);
            if (ris)
                ris++;
            s += Form1->FormatSendString(Answ_014D01, n);
        break;

        case 0x05:
            Form1->RichEdit1->SelAttributes->Color = clYellow;
            s.sprintf("[05] Acknowledge received!");
            //s += Form1->FormatSendString(Answ_73, Answ_73_LEN);
            if (AlrmBuf.msg_sent == 1)
            {
                AlrmBuf.msg_sent = 0;
                //stop sendig frame 4 for 5 seconds!
                s += " [Error request]";
                AlrmBuf.ack_received = 1;
                AlrmBuf.Delay5sec = MilliSecondOfTheYear(Now()) + 5000;
            }
        break;

        case 0x09:      //Module stop device alarm info
            Form1->RichEdit1->SelAttributes->Color = clYellow;
            s.sprintf("[09] Stop send alarm info");
            //s += Form1->FormatSendString(Answ_73, Answ_73_LEN);
            if (Form1->SendAnswerPopMnu->Checked)
                ris = -Ser->BIN_Write(STOP_ALARM_9, STOP_ALARM_9_LEN, LenReaden);
            if (ris)
                ris++;

            s += "\n";
            s += Form1->FormatSendString(STOP_ALARM_9, STOP_ALARM_9_LEN);
            Form1->StatusBar1->Panels->Items[1]->Text = s;
            AlrmBuf.F09_received = 1;
            AlrmBuf.err_present = 0;
            if (AlrmBuf.msg_sent == 1)
            {
                //AlrmBuf.msg_sent = 0;
                /*
                //stop sendig frame 4 for 5 seconds!
                AlrmBuf.ack_received = 1;
                AlrmBuf.Delay5sec = MilliSecondOfTheYear(Now()) + 5000;
                */
            }
        break;

        case 0x73:
            Form1->RichEdit1->SelAttributes->Color = clAqua;
            n = UpdateAlrmMsg();
            s.sprintf("[74] Alarm status len = %d\n", n-3);
            if (Form1->SendAnswerPopMnu->Checked)
                ris = -Ser->BIN_Write(Answ_73, n, LenReaden);
            if (ris)
                ris++;
            s += Form1->FormatSendString(Answ_73, n);
        break;

        case 0x7C:
            Form1->RichEdit1->SelAttributes->Color = clAqua;
            s.sprintf("[7C]  = Set reporting interval\n");
            if (Form1->SendAnswerPopMnu->Checked)
                ris = -Ser->BIN_Write(STATUS_INTERVAL_7C, STATUS_INTERVAL_7C_LEN, LenReaden);
            if (ris)
                ris++;
            s += Form1->FormatSendString(STATUS_INTERVAL_7C, STATUS_INTERVAL_7C_LEN);
        break;

        //case 0x7D !!

        case 0xF7:      //ACKnowledge!
            Form1->RichEdit1->SelAttributes->Color = clYellow;
            s.sprintf("[F7] Actively report network status = ");
                //,/* ACK_5_LEN-3 */ );
            if (Form1->SendAnswerPopMnu->Checked)
                ris = -Ser->BIN_Write(ACK_5, ACK_5_LEN, LenReaden);
            if (ris)
                ris++;
            //Aggiunto qui lo stato!!!
            r = GetStatusStr(comBuf.msg);
            Form1->StatusBar1->Panels->Items[1]->Text = "Status: "+r;
            s += r+"\n";
            s += Form1->FormatSendString(ACK_5, ACK_5_LEN);

        break;

        case 0xF3:
            Form1->RichEdit1->SelAttributes->Color = clFuchsia;
            s = "[F3] Module configuration mode frame: OK";
            //s += Form1->FormatSendString(Answ_F2, Answ_F2_LEN);
            Form1->F2GotAnswerCKB->Checked = true;
            Form1->F2_SentCKB->Checked = false;
            UpdateLog(NULL, 'r', "==> "+s, 0);
            Form1->RichEdit1->Lines->Add(s);
            if (!Form2->Visible)
                Form1->RichEdit1->SetFocus();
        ///ATTENZIONE: RETURN!!
        return;

        case 0xFC:      
            Form1->RichEdit1->SelAttributes->Color = clAqua;
            s.sprintf("[FC] Query information: %d\n", Answ_FC_LEN-3);
            if (Form1->SendAnswerPopMnu->Checked)
                ris = -Ser->BIN_Write(Answ_FC, Answ_FC_LEN, LenReaden);
            if (ris)
                ris++;
            s += Form1->FormatSendString(Answ_FC, Answ_FC_LEN);
        break;

        default:
            Form1->RichEdit1->SelAttributes->Color = clRed;
            s = "Unhandle command :<";
            s += Form1->FormatSendString(comBuf.msg, comBuf.rcv_size);
            s += ">";
            fail = 1;
        break;
    }

    if (s == "")
        return;
    if (!Form1->SendAnswerPopMnu->Checked && !fail)
        s = "[Test]"+s;

    UpdateLog(NULL, 'r', "W => "+s, 0);
    if (Form1->RichEdit1->SelAttributes->Color == clBlack)
        Form1->RichEdit1->SelAttributes->Color  = clYellow;
    Form1->RichEdit1->Lines->Add(s);
}


/*

  When the network status is 0x00 01 AP unable to connect, the signal strength field
  indicates whether the module has been configured.
  0x00 00 module has never been configured;
  0x00 01 module has been configured

    From "U+ UART communication protocol for connected AC.docx" page 17

  When the network state is 0x00 09 low power consumption mode,
  the signal strength field is meaningless, and the default value is 0x00 00

  ??
  
*/
String __fastcall TokenThread::GetStatusStr(char* c)
{
    String r = "";
    unsigned char* p;
    int n1, n2;

    p = c + 10;
    n1  = *p++;
    n1 <<= 8;
    n1 |= *p++;

    n2 = *p++;
    n2 <<= 8;
    n2 |= *p;

    switch (n1)
    {
        case 0: r = "0: Communicat. normal";       break;
        case 1: r = "1: Unable to connect to ap."; break;
        case 2: r = "2: Can't connet to server";   break;
        case 3:
            switch (n2)
            {
                case 1: r = "3-1: Config softAP";    break;
                case 2: r = "3-2: Config Smartlink"; break;
                case 3: r = "3-3: Config WPS";       break;
                case 4: r = "3-4: Config BT";        break;
                default:
                    r = "Unknow config!";
                break;
            }
        break;
        default:
            r = "!Unknow network status!";
        break;

    }
    if (n1 == 0)
        Connected = true;
    else
        Connected = false;

    return r;
}
