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
    ErrVal = 0;
}
//---------------------------------------------------------------------------
void __fastcall TForm3::FormCreate(TObject *Sender)
{
    int n;
    String s;
    for (n = 0; n<8; n++)
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
    }

    n = Edit[7]->Width + Edit[7]->Left + Edit[0]->Left;
    Form3->ClientWidth = n;
    n = n/2 - Label1->Width/2;
    Label1->Left = n;

    Label3->Visible = DebugFlag;

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
	for(n = 0; n < 8; n++)
	{
		Edit[n]->Enabled = true;
		if (!( (8-n) <= numbyte) )
        {
			Edit[n]->Text = "--";
            Edit[n]->Enabled = false;
        }

	}

    n = Form3->ClientWidth;
    n = n/2 - AlrmComboBox->Width/2;
    AlrmComboBox->Left = n;

    n = Form3->ClientWidth;
    n = n/2 - EnterBitBttn->Width/2;
    EnterBitBttn->Left = n;

	AlrmComboBox->Items->Clear();
    AlrmComboBox->Items->Add("Erase");
	JSON_ALARM *ja = JsonALRM[device].alrm;
    //JSON_ALARM *ja = ALARM_WC;
	for (n = 0; n < JsonALRM[device].totAlarm; n++)
	{
        s.sprintf("%s, %d", ja->name, ja->pos);
		AlrmComboBox->Items->Add(/*ja->name*/s);
		ja++;
	}
    AlrmComboBox->ItemIndex = 0;


}
//---------------------------------------------------------------------------

void __fastcall TForm3::NextBitBttnClick(TObject *Sender)
{
    int n = AlrmComboBox->ItemIndex +1;
    n %= JsonALRM[device].totAlarm;
    AlrmComboBox->ItemIndex = n;
    AlrmComboBoxChange(NULL);
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
    unsigned __int64 n;
    unsigned int t;
    unsigned __int64 val;
    unsigned __int64 i;
    String s;

    for (n = 0; n < 8; n++)
    {
        t = 7-n;
        i = 0xFF;
        i <<= n*(__int64)8;
        val = (ErrVal&i) >> (n*(__int64)8);
        s.sprintf("%02X", val);
        Edit[t]->Text = s;
    }
}

void __fastcall TForm3::SpeedButton1Click(TObject *Sender)
{
    static int b = 0;
    if (!b)
    {
        ErrVal = 1;
        b = 1;
    }
    else ErrVal <<= (__int64)1;
    String s;
    //s.sprintf("0x%X", ErrVal);
    s = "0x" + IntToHex((int)(ErrVal>>32), 8) + "." + IntToHex((int)(ErrVal&0xFFFFFFFF), 8);
    //if (bit > 32) s = s+".00000000";
    Label3->Caption = s;
    FillEdits();


}
//---------------------------------------------------------------------------

void __fastcall TForm3::AlrmComboBoxChange(TObject *Sender)
{
    int v = AlrmComboBox->ItemIndex;
    JSON_ALARM *ja = JsonALRM[device].alrm;

    unsigned long long    bit;
    if (v == 0)
    {
        ErrVal = 0;
    }
    else
    {
        ja += v-1;
        bit = ja->pos;
        ErrVal = 1;
        ErrVal <<= (bit);

    }
    String s;
    //s.sprintf("0x%X", ErrVal);
    s = "0x" + IntToHex((int)(ErrVal>>32), 8) + "." + IntToHex((int)(ErrVal&0xFFFFFFFF), 8);
    //if (bit > 32) s = s+".00000000";
    Label3->Caption = s;
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
    AlrmComboBox->ItemIndex = 0;
    AlrmComboBoxChange(NULL);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::EnterBitBttnClick(TObject *Sender)
{
    unsigned __int64 val;
    unsigned __int64 n;
    unsigned __int64 i;
    //int i;
    String s;
    val = 0;

    for(n = 0; n < 8; n++)
    {
        s = "0x" + Edit[7-(int)n]->Text;
        i = StrToIntDef(s, 0);
        //if (i == 0)
            Edit[7-(int)n]->Text = IntToHex((int)i, 2);
        i <<= (8*n);
        val += (unsigned __int64)i;
    }
    s = "0x" + IntToHex((int)(val>>32), 8) + "." + IntToHex((int)(val&0xFFFFFFFF), 8);
    //if (bit > 32) s = s+".00000000";
    Label3->Caption = s;
    ErrVal = val;

}
//---------------------------------------------------------------------------

