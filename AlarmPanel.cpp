//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "AlarmPanel.h"
#include "Unit1.h"
#include "Define.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm3 *Form3;

extern bool DebugFlag;

//---------------------------------------------------------------------------
__fastcall TForm3::TForm3(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm3::FormCreate(TObject *Sender)
{
    int n;
    String s;
    for (n = 0; n < ERRBUFF_LEN; n++)
    {
        Edit[n] = new TEdit(this);
        Edit[n]->Tag = n;
        Edit[n]->Parent = Edit1->Parent;
        Edit[n]->Text = "00";
        Edit[n]->Top = Edit1->Top;  // + 30*n +3;
        Edit[n]->Left = Edit1->Left +n*Edit1->Width + 15*n;
        Edit[n]->Width = Edit1->Width;
        Edit[n]->Height = Edit1->Height;
        Edit[n]->ReadOnly = false;
        Edit[n]->OnClick = EditClick;
        Edit[n]->OnEnter = Edit1Enter;
        Edit[n]->Visible = false;

        NumByteLabel[n] = new TStaticText(this);
        NumByteLabel[n]->Tag = n;
        NumByteLabel[n]->Parent = StaticText1->Parent;
        NumByteLabel[n]->Caption = IntToStr(n+1);
        NumByteLabel[n]->Top = StaticText1->Top;
        NumByteLabel[n]->Left = StaticText1->Left + n*Edit1->Width + 15*n;
        NumByteLabel[n]->Width = StaticText1->Width;
        NumByteLabel[n]->Visible = false;
    }

    n = Edit[ERRBUFF_LEN-1]->Width + Edit[ERRBUFF_LEN-1]->Left + Edit[0]->Left;
    Form3->ClientWidth = n;
    n = n/2 - Label1->Width/2;
    Label1->Left = n;
    //Label3->Visible = DebugFlag;

    n = Form3->ClientWidth;
    n -= NextBitBttn->Width;
    n -= ClearBttn->Left;
    NextBitBttn->Left = n;

    n = Form3->ClientWidth;
    n -= Form3->EnterBitBttn->Width;
    EnterBitBttn->Left = n;
    SpeedButton1->Visible = DebugFlag;

}
//---------------------------------------------------------------------------

void __fastcall TForm3::EditClick(TObject *Sender)
{
	//int n = dynamic_cast<TEdit*>(Sender)->Tag;

}

extern JSON_ALARM ALARM_WC[];
void __fastcall TForm3::FormShow(TObject *Sender)
{   
	device = Form1->DeviceComboBox->ItemIndex;
	String s;

    Form1->DeviceComboBox->Enabled = false;

	s.sprintf("Device = <%s> tot alarm = %d",
		JsonALRM[device].name, JsonALRM[device].totAlarm);
	Label2->Caption = s;
	int n = Form3->ClientWidth;
	n = n/2 - Label2->Width/2;
	Label2->Left = n;

	int numbyte = JsonALRM[device].dim;     //numero di byte
	for(n = 0; n < ERRBUFF_LEN; n++)
	{
		if (n < numbyte)
        {
            Edit[n]->Text = "00";
            Edit[n]->Visible = true;
            NumByteLabel[n]->Visible = true;
        }
        else
        {
            Edit[n]->Text = "--";
            Edit[n]->Visible = false;
            NumByteLabel[n]->Visible = false;
        }
	}

    n = Form3->ClientWidth;
    n = n/2 - AlrmComboBox->Width/2;
    //AlrmComboBox->Left = n;

    n = Form3->ClientWidth;
    n = n/2 - EnterBitBttn->Width/2;
    EnterBitBttn->Left = n;

	AlrmComboBox->Items->Clear();
    //AlrmComboBox->Items->Add("Erase");
	JSON_ALARM *ja = JsonALRM[device].alrm;
    //JSON_ALARM *ja = ALARM_WC;
	for (n = 0; n < JsonALRM[device].totAlarm; n++)
	{
        s.sprintf("%s, %d", ja->name, ja->pos);
		AlrmComboBox->Items->Add(/*ja->name*/s);
		ja++;
	}
    AlrmComboBox->ItemIndex = 0;

    //if (bit > 32) s = s+".00000000";
    //Label3->Caption = s;

}
//---------------------------------------------------------------------------

void __fastcall TForm3::NextBitBttnClick(TObject *Sender)
{
    int n = AlrmComboBox->ItemIndex;
    n %= JsonALRM[device].totAlarm;

    Sender = dynamic_cast<TSpeedButton*>(SpeedButton3);     // -
    SpeedButton2Click(Sender);

    if (++n >= AlrmComboBox->Items->Count)
        n = 0;

    AlrmComboBox->ItemIndex = n;
    AlrmComboBoxChange(NULL);
    Sender = dynamic_cast<TSpeedButton*>(SpeedButton2);     // +
    SpeedButton2Click(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::FormClose(TObject *Sender, TCloseAction &Action)
{
    if (Form1->CB_Connect->Checked == false)
        Form1->DeviceComboBox->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TForm3::FillEdits()
{
    unsigned int n;
    String s;

    for (n = 0; n < ERRBUFF_LEN; n++)
    {
        s.sprintf("%02X", AlrmBuf.ErrBuff[n]);
        Edit[n]->Text = s;
    }
}

void __fastcall TForm3::SpeedButton1Click(TObject *Sender)
{
    int n;
    String s;

    int max = JsonALRM[device].dim;
    for(n = 0; n < max; n++)
    {
        s.sprintf("%02X", AlrmBuf.ErrBuff[n]);
        Edit[n]->Text = s;
    }

}
//---------------------------------------------------------------------------

void __fastcall TForm3::AlrmComboBoxChange(TObject *Sender)
{
    //int v = AlrmComboBox->ItemIndex;

    /*
    memset(AlrmBuf.ErrBuff, 0, ERRBUFF_LEN);
    if (v == 0)
    {
        FillEdits();
        return;
    }

    JSON_ALARM *ja = JsonALRM[device].alrm;
    ja += v;
    unsigned int    bit = ja->pos;
    int byte = bit/8;
    int pos = bit%8;
    int val = 1<<pos;
    AlrmBuf.ErrBuff[byte] = (unsigned char)val;
    */

    FillEdits();
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Edit1Change(TObject *Sender)
{
    static int n;

    n++;
}
//---------------------------------------------------------------------------


void __fastcall TForm3::Edit1Enter(TObject *Sender)
{
    static int n;

    n++;
}
//---------------------------------------------------------------------------

void __fastcall TForm3::ClearBttnClick(TObject *Sender)
{
    //AlrmComboBox->ItemIndex = 0;
    //AlrmComboBoxChange(NULL);
    memset(AlrmBuf.ErrBuff, 0, ERRBUFF_LEN);
    //if (v == 0)
    {
        FillEdits();
        return;
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm3::EnterBitBttnClick(TObject *Sender)
{
    int n;
    unsigned int i;
    String s;
    unsigned char ErrBuffCpy[ERRBUFF_LEN];

    memcpy(ErrBuffCpy, AlrmBuf.ErrBuff, ERRBUFF_LEN);


    for(n = 0; n < ERRBUFF_LEN; n++)
    {
        s = "0x" + Edit[n]->Text;
        i = StrToIntDef(s, 0);
        Edit[n]->Text = IntToHex((int)i, 2);
        AlrmBuf.ErrBuff[n] = (unsigned char)i;
    }

    int max = JsonALRM[device].dim;
    char previous_err = AlrmBuf.err_present;
    s = "ALARM: 0x";
    AlrmBuf.err_present = 0;
    for(n = max-1; n >= 0; n--)
    {
        s.cat_sprintf("%02X", AlrmBuf.ErrBuff[n]);
        if (AlrmBuf.ErrBuff[n])
            AlrmBuf.err_present = 1;
    }
    Form1->StatusBar1->Panels->Items[3]->Text = s;

    if ( AlrmBuf.msg_toSend == 0 && AlrmBuf.err_present)
    {
        n = memcmp(ErrBuffCpy, AlrmBuf.ErrBuff, ERRBUFF_LEN);
        if (n != 0)     //qualcosa è cambiato
        {
            AlrmBuf.msg_toSend = 1;
            AlrmBuf.F09_received = 0;
        }
    }

    if (previous_err != 0 && AlrmBuf.err_present == 0)
    {
        AlrmBuf.err_zero = 1;
        AlrmBuf.msg_toSend = 1;
        AlrmBuf.F09_received = 0;
    }
}
//---------------------------------------------------------------------------


void __fastcall TForm3::SpeedButton2Click(TObject *Sender)
{
    int tag = dynamic_cast<TSpeedButton*>(Sender)->Tag;

    JSON_ALARM *ja = JsonALRM[device].alrm;
    int v = AlrmComboBox->ItemIndex;

    ja += v;
    unsigned int    bit = ja->pos;
    int byte = bit/8;
    int pos = bit%8;
    unsigned char val = 1<<pos;
    if (tag == 0)   //Ho scelto '+'
    {
        AlrmBuf.ErrBuff[byte] |= val;
    }
    else
    {
        AlrmBuf.ErrBuff[byte] &= val^0xFF;
    }
    FillEdits();
}
//---------------------------------------------------------------------------

