//---------------------------------------------------------------------------

#include <vcl.h>
#include <inifiles.hpp>
#include <stdio.h>
#include <dateutils.hpp>
#pragma hdrstop

#include "Unit1.h"
#include "Define.h"
#include "algorithm.h"
#include "SerialPort.h"
#include "TokenThread.h"
#include "SendCustomMsgForm.h"
#include "SureConnectionThread.h"
#include "AlarmPanel.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "LMDBaseEdit"
#pragma link "LMDCustomBevelPanel"
#pragma link "LMDCustomControl"
#pragma link "LMDCustomMemo"
#pragma link "LMDCustomPanel"
#pragma link "LMDMemo"
#pragma link "dxfCheckBox"
#pragma link "dxfCheckBox"
#pragma link "LMDCustomComponent"
#pragma link "LMDStarter"
#pragma resource "*.dfm"
TForm1 *Form1;

TSerialPort *Ser;
TList *TL;
TStringList *CommList;
SureConnectThread *Task;
TokenThread *TaskToken;

int ThreadHandle = 0;

#define WINDOW_LARGE        675
#define WINDOW_TALL         560

//////////////////
#define ARCAIR_ONLY_


/*
typedef struct _serform
{
    unsigned char   buf[1000];
    unsigned char   msg[100];
    int    rcv_pointer;
    int    rcv_size;
    bool   connect;
}   SERBUF_STRUCT;
*/

SERBUF_STRUCT comBuf;
unsigned long LenReaden;
bool DebugFlag = false;

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
    : TForm(Owner)
{
    CommList = new TStringList;

    Ser = new TSerialPort(this);
    Ser->BufferRX = BUFSIZE;
    Ser->BufferTX = BUFSIZE;
    memset((char*)&comBuf, 0, sizeof(SERBUF_STRUCT));
    memset(AlrmBuf.ErrBuff, 0, ERRBUFF_LEN);

    StringInit();
    F2Req = false;
    Cmd6Req = false;
    Cmd09Req = false;
    Cmd7CReq = false;
    BidataReq = false;
}
//---------------------------------------------------------------------------


void __fastcall TForm1::AnalyzeRcv(void)
{
    //Analyze recv buffer
    int n;
    if (comBuf.rcv_pointer <= 1)
        return;

    for (n = 0; n < comBuf.rcv_pointer-2; n++)
    {
        if (comBuf.buf[n] == 0xFF && comBuf.buf[n+1] == 0xFF) //SOT found!
        {
            if (n == 0)
                continue;
            memcpy(comBuf.msg, comBuf.buf, n);
            comBuf.rcv_size = n;
            memmove((char*)&comBuf.buf[0], (char*)&comBuf.buf[n], comBuf.rcv_pointer);
            comBuf.rcv_pointer -= n;

            MessageReceived();
            //break;
            n  = 0;
        } 
    }
}

void __fastcall TForm1::MessageReceived(void)
{
    int n;
    String s, r;

    for (n = 0; n < comBuf.rcv_size; n++)
    {
        r = r.IntToHex(comBuf.msg[n], 2);
        s += r + " ";
    }
    r.sprintf("\t size %d[%d]", comBuf.rcv_size, comBuf.rcv_pointer);
    s += r;
    RichEdit1->Lines->Add(s);
}


void __fastcall TForm1::SWDateTimePicker1Change(TObject *Sender)
{
    //value
    /*
    TDate SW_Date = SWDateTimePicker1->Date;

    unsigned short y, m, d;
    SW_Date.DecodeDate(&y, &m, &d);

    String s;
    s.sprintf("%04d%02d%02d", y, m, d);
    unsigned char buf[10];
    //for(int n = 0; n < 8; n++)        buf[n] = s[n+1];
    sprintf(buf,"%04d%02d%02d", y, m, d);

    d++;
    */
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SerialSelectCBChange(TObject *Sender)
{

    int n = SerialSelectCB->ItemIndex;
    /*
    PSERIALPORTINFO Com = (PSERIALPORTINFO) TL->Items[n];
    n = Com->nPortNumber;
    Ser->COMPort = n;
    Ser->Baud = cb__9600;   //default value
    */

    CB_Connect->Visible     = (n == 0)? false:true;
    ConnectLabel->Enabled   = (n == 0)? false:true;

    //ConnectBttnClick(NULL);
    Ser->COMPort = 0;
    comBuf.connect = 0;
    CB_Connect->Checked = false;
        //ComReceiveTimer->Enabled = false;
    if (TaskToken)
        TaskToken->Suspend();
    Sleep(50);


    memset((char*)&comBuf, 0, sizeof(SERBUF_STRUCT));
    StatusBar1->Panels->Items[1]->Text = "Status: ";
    //ComReceiveTimer->Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormClose(TObject *Sender, TCloseAction &Action)
{
    delete CommList;

    Ser->COMPort = 0;
    FreeTList(TL, true);

    TIniFile *ini;
    ini = new TIniFile(ChangeFileExt( Application->ExeName, ".ini"));

    ini->WriteInteger("Position", "X", Form1->Left);
    ini->WriteInteger("Position", "Y", Form1->Top);
    ini->WriteInteger("Setting", "COMM", SerialSelectCB->ItemIndex);
    ini->WriteInteger("Setting", "Type", DeviceComboBox->ItemIndex);
    ini->WriteBool("Setting", "Write2Comm", SendAnswerPopMnu->Checked);
    ini->WriteBool("Setting", "Write LogFile", WriteLogPopMnu->Checked);
    ini->WriteBool("Setting", "Debug", DebugFlag);

    delete ini;

}
//---------------------------------------------------------------------------

void __fastcall TForm1::NewSerialTimerTimer(TObject *Sender)
{
    TList* T2 = new TList;
    GetPortList(T2);
    if (T2->Count != TL->Count) {
      //aggiunta/tolta qualche COMM: valutare i casi!
      FreeTList(TL,  false);
      TL->Clear();
      GetPortList(TL);
      //CommList->Clear();
      CreateCommList(TL, CommList);
      SerialSelectCB->Items = CommList;
      //Label2->Caption = "Num of COM port: "+IntToStr(CommList->Count-1);
    }
    FreeTList(T2, true);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormCreate(TObject *Sender)
{
    int n;
    TL = new TList;
    GetPortList(TL);
    CreateCommList(TL, CommList);
    SerialSelectCB->Items = CommList;

    Ser->COMPort = 0;
    //ComReceiveTimer->Enabled = false;
    comBuf.connect = 0;

    RichEdit1->DefAttributes->Color = clGreen;

    //TaskToken = new TokenThread(0);

    MemoSizeL = Form1->Width - Form1->RichEdit1->Width;
    MemoSizeH = Form1->Height -  Form1->RichEdit1->Height;

    TIniFile *ini;
    ini = new TIniFile(ChangeFileExt( Application->ExeName, ".ini" ) );

    Form1->Left = ini->ReadInteger("Position", "X", 10);
    Form1->Top  = ini->ReadInteger("Position", "Y", 10);

    SerialSelectCB->ItemIndex = ini->ReadInteger("Setting", "COMM", 0);
    SendAnswerPopMnu->Checked = ini->ReadBool("Setting", "Write2Comm", true);
    SerialSelectCBChange(NULL);
    WriteLogPopMnu->Checked = ini->ReadBool("Setting", "Write LogFile", false);
    DeviceComboBox->ItemIndex = ini->ReadInteger("Setting", "Type", 0);
    DebugFlag = ini->ReadBool("Setting", "Debug", false);

    //if (DebugFlag)
    {
        //
        SpeedButton3->Visible = DebugFlag;
        Edit1->Visible        = DebugFlag;
        //AlarmBttn->Enabled    = DebugFlag;
        //Frame09force1->Enabled= DebugFlag;
    }

    #ifdef ARCAIR_ONLY
    DeviceComboBox->ItemIndex = 5;
    #endif
    DeviceComboBoxChange(NULL);

    #ifdef ARCAIR_ONLY
    DeviceComboBox->Enabled = false;
    #endif

    delete ini;
}
//---------------------------------------------------------------------------



void __fastcall TForm1::Clean1Click(TObject *Sender)
{
    RichEdit1->Clear();
    StatusBar1->Panels->Items[1]->Text = "Status: ";    
}
//---------------------------------------------------------------------------


String __fastcall TForm1::FormatSendString(unsigned char* buf, int len, bool space)
{
    String s = "";
    String r;

    for (int n = 0; n < len; n++)
    {
        r = r.IntToHex(buf[n], 2);
        s += r;
        if (space)
            s += " ";
    }
    if (space)
        s.SetLength(s.Length()-1);  //remove last space added in the for loop
    return s;
}


void __fastcall TForm1::ConfigRequestBttnClick(TObject *Sender)
{
    F2Req = true;
    ConfigRequestBttn->Enabled = false;
    Form1->F2GotAnswerCKB->Checked = false;
}
//---------------------------------------------------------------------------


void __fastcall TForm1::FormShow(TObject *Sender)
{
    TaskToken = new TokenThread(1);
    if (TaskToken)
        ThreadHandle = TaskToken->Handle;
    else
        ThreadHandle = 0;
    Form1->StatusBar1->Panels->Items[3]->Text = "ALARM: none";
}
//---------------------------------------------------------------------------


void __fastcall TForm1::FormCloseQuery(TObject *Sender, bool &CanClose)
{
    TaskToken->Terminate();
}
//---------------------------------------------------------------------------


void __fastcall TForm1::DeviceComboBoxChange(TObject *Sender)
{
    int n = DeviceComboBox->ItemIndex;
    if (n <0 )
    {
        ;//Handle errors!
        return;
    }

    TypeID_init((DEV_TYPE)n);
    switch (n)
    {
        default:
        case DEV_TYPE_WC:
            Answ71S = " -WC-";
            Form1->StatusBar1->Panels->Items[2]->Text = "Wine Cooler";
        break;

        case DEV_TYPE_WH:
            Answ71S = " -WH-";
            Form1->StatusBar1->Panels->Items[2]->Text = "Water Heater";
        break;

        case DEV_TYPE_HVAC:
            Answ71S = " -HVAC-";
            Form1->StatusBar1->Panels->Items[2]->Text = "Air Conditioning HVAC";
        break;

        case DEV_TYPE_HVAC2:
            Answ71S = " -HVAC 2-";
            Form1->StatusBar1->Panels->Items[2]->Text = "Air Conditioning HVAC II";
        break;

        case DEV_TYPE_WM:
            Answ71S = " -WM-";
            Form1->StatusBar1->Panels->Items[2]->Text = "SDrum Washing Machine";
        break;

        case DEV_TYPE_FR_RU60cm:
            Answ71S = " -FR01-";
            Form1->StatusBar1->Panels->Items[2]->Text = "Fridge RU 60cm";
        break;

        case DEV_TYPE_HO_Arcair:
            Answ71S = " -HO-Ark-";
            #ifdef ARCAIR_ONLY
                Form1->StatusBar1->Panels->Items[2]->Text = ">> ARCAIR ONLY!";
            #else
                Form1->StatusBar1->Panels->Items[2]->Text = "Hood Arcair";
            #endif
        break;

        case DEV_TYPE_HO_Haier:
            Answ71S = " -HO-01-";
            Form1->StatusBar1->Panels->Items[2]->Text = "Hood Haier";
        break;

        case DEV_TYPE_FR_MultiD_A3FE744:
            Answ71S = " FR MD 982K A3FE";
            Form1->StatusBar1->Panels->Items[2]->Text = "Multidoor 982k A3FE744";
        break;

        case DEV_TYPE_FR_MultiD_HB20:
            Answ71S = " FR MD 982J HB20";
            Form1->StatusBar1->Panels->Items[2]->Text = "Multidoor 982J HB20";
        break;

    }
    // Write something?
    memset(AlrmBuf.ErrBuff, 0, ERRBUFF_LEN);
    Form1->StatusBar1->Panels->Items[3]->Text = "ALARM: none";

    if (DebugFlag && n <=1 )    //<= for test
    {
        BigDataBttn->Enabled = Device[n].bigdata_present;
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::CustomMsgBttnClick(TObject *Sender)
{
    Form2->Show();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SendCustomStr(int len)
{                                                         
    unsigned char cks;
    unsigned char buf[200];

    memcpy(buf, Form2->ToWrite, len);
    cks = CalcCKS2(buf, &len);
    len += 2;   //add header FF FF  
    buf[len++] = cks;

    unsigned long LenReaden;
    int ris = -Ser->BIN_Write(buf, len, LenReaden);
    //Write something on LOG & panel

    String s;
    if (ris == 0)
    {
        Form1->RichEdit1->SelAttributes->Color = clYellow;
        s.sprintf("Custom message sent [%d]: ", len);
        s += Form1->FormatSendString(buf, len);
    }
    else
    {
        Form1->RichEdit1->SelAttributes->Color = clRed;
        s.sprintf("Error %d on transmit!", -ris);
    }

    Form1->RichEdit1->Lines->Add(s);
    Form1->RichEdit1->SetFocus();
    UpdateLog(NULL, 'r', "W => "+s, len);
}

void __fastcall TForm1::FormConstrainedResize(TObject *Sender,
      int &MinWidth, int &MinHeight, int &MaxWidth, int &MaxHeight)
{
    MinWidth  = WINDOW_LARGE;
    MinHeight = WINDOW_TALL;
}
//---------------------------------------------------------------------------


void __fastcall TForm1::FormResize(TObject *Sender)
{
    //
    Form1->RichEdit1->Width = Form1->Width - MemoSizeL;
    Form1->Panel2->Left = Form1->RichEdit1->Width + 5;

    //from form1->OnCreate:
    // MemoSizeH = Form1->Height -  Form1->RichEdit1->Height;

    Form1->RichEdit1->Height = Form1->Height - MemoSizeH;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::RichEdit1Change(TObject *Sender)
{
    if (!Form2->Visible)        Form1->RichEdit1->SetFocus();    
}
//---------------------------------------------------------------------------



void __fastcall TForm1::CB_ConnectClick(TObject *Sender)
{
    Application->ProcessMessages();

    if (comBuf.connect == 0)
    {
        memset((char*)&comBuf, 0, sizeof(SERBUF_STRUCT));

        int n = SerialSelectCB->ItemIndex;
        if (n >= TL->Count || n<1)
        {
            MessageDlg("COMM probems\nCheck connections", mtConfirmation, TMsgDlgButtons() << mbOK , 0);
            return;
        }
        PSERIALPORTINFO Com = (PSERIALPORTINFO) TL->Items[n];
        n = Com->nPortNumber;

        Ser->COMPort = n;
        Ser->Baud = cb__9600;   //default value
        //ComReceiveTimer->Enabled = true;
        Ser->FlushBuffer(2);
        comBuf.connect = 1;
        DeviceComboBox->Enabled = false;
        //if (!DebugFlag)            AlarmBttn->Enabled = false;
        Panel1->Enabled = true;
        Sleep(50);
        TaskToken->Resume();

        Task = new SureConnectThread();
        Task->OnTerminate = ThreadDone;
    }
    else
    {
        Ser->COMPort = 0;
        TaskToken->Suspend();
        comBuf.connect = 0;
        LiveRB->Checked = false;
        DeviceComboBox->Enabled = true;
        AlarmBttn->Enabled = true;
        //StringInit();
        Panel1->Enabled = false;
        StatusBar1->Panels->Items[1]->Text = "Status: ";
        StatusBar1->Panels->Items[0]->Text = "";
    }    
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ThreadDone(TObject *Sender)
{
    //
}
void __fastcall TForm1::StatusBar1DblClick(TObject *Sender)
{
    Form1->StatusBar1->Panels->Items[1]->Text = "";
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ForceStatusBttnClick(TObject *Sender)
{
    Cmd6Req = true;    
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ExitBttnClick(TObject *Sender)
{
    Close();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::DeviceListInit()
{
    
}
void __fastcall TForm1::SpeedButton3Click(TObject *Sender)
{
    static int n;
    int newlen;
    /*
    char buf[20] = {0xFF, 0xFF, 0x0D, 0x01, 0x02, 0x03, 0x04, 0x05,
                    0x06, 0x02, 0x6D, 0x01, 0x05, 0xFF, 0xFF, 0x95,
                    0x10, 0x20, 0x30, 0x40};
    */
    //case receiving...
    char buf[20] = {0xFF, 0xFF, 0x0D, 0x01, 0x02, 0x03, 0x04, 0x05,
                    0x06, 0x02, 0x6D, 0x01, 0x05, 0xFF, 0x55, 0xFF,
                    0x55, 0x3F, 0x10, 0x20, };

    //unsigned char c = CalcCKS2(buf, &newlen);

    unsigned __int64 v = 1;
    v <<= (unsigned __int64)40;
    v++;

    bool b = CheckCKSrx(buf);
    char* p = buf;
    p += newlen;
    *p = 0x12;
    n++;
    b = b;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::AlarmBttnClick(TObject *Sender)
{
    Form3->Show();
    Form3->BringToFront();
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Frame09force1Click(TObject *Sender)
{
    // forzo lo stato 09
    if (!DebugFlag)
        return;
    Cmd09Req = true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::PrintRTF1Click(TObject *Sender)
{
    //Save to file "Log_*.rtf
    String s = ExtractFilePath( Application->ExeName );
    String s2;
    //int n, len;

    unsigned short y, m, d, h, mm, ss, msec;
    DecodeDateTime(Now(), y, m, d, h, mm, ss, msec);

    s2.sprintf("EmulatorWindow_%02d_%02d_%02d-%02d", y, m, d, h);
    s += s2+".rtf";
    RichEdit1->Lines->SaveToFile(s);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormActivate(TObject *Sender)
{
    if (Form3->Visible)
        Form3->BringToFront();
}
//---------------------------------------------------------------------------
//int answ = MessageDlg("Do you really want to ERASE flash?", mtConfirmation, TMsgDlgButtons() << mbOK << mbCancel/* <<mbIgnore*/, 0);
void __fastcall TForm1::WriteLogPopMnuClick(TObject *Sender)
{
    static bool b = false;

    if (!b)
    {
        b = true;
        MessageDlg("You can also print in RTF format by\nright click on black message box", mtConfirmation,
            TMsgDlgButtons() << mbOK , 0);
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::TypeIDreadBttnClick(TObject *Sender)
{
    //Scrivo il device ID selezionato sullo schermo.
    unsigned char* p = Answ_71;
    p += 10;
    String s = "Type ID selected:";
    RichEdit1->SelAttributes->Color = clLime;
    RichEdit1->Lines->Add(s);
    s = FormatSendString(p, 32);
    RichEdit1->SelAttributes->Color = clLime;
    RichEdit1->Lines->Add(s);
    RichEdit1->SelAttributes->Color = clWhite;
    s = FormatSendString(p, 32, false);
    RichEdit1->Lines->Add(s.LowerCase());
    RichEdit1->SelAttributes->Color = clLime;   //?    
//    RichEdit1->SetFocus();
    //RichEdit1->Lines->Add();
    //Lo copio nella clipboard ?    
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N7CSetreportinterval1Click(TObject *Sender)
{
    //frame 7C:   Device active reporting interval

    //if (!DebugFlag)         return;
    Cmd7CReq = true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Predictive1Click(TObject *Sender)
{
    //???
    Predictive1->Checked = !Predictive1->Checked; 
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BigDataBttnClick(TObject *Sender)
{
    BidataReq = true;    
}
//---------------------------------------------------------------------------

