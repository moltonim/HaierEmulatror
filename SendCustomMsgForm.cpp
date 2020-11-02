//---------------------------------------------------------------------------

#include <vcl.h>
#include <inifiles.hpp>
#pragma hdrstop

#include "Unit1.h"
#include "Serialport.h"
#include "SendCustomMsgForm.h"


//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

TForm2 *Form2;

static String prevText;

//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm2::CancelBttnClick(TObject *Sender)
{
    Close();    
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Edit2DblClick(TObject *Sender)
{
    Edit2->Clear();    
}
//---------------------------------------------------------------------------

void __fastcall TForm2::HexRBClick(TObject *Sender)
{
    //void
    String SS = "";
    String RR = "";
    int i;
    
  for( i=0; i<Edit2->Lines->Count; i++)
    SS += Edit2->Lines->Strings[i];
  // Aggiorna ToWrite
  for ( i=1; i<=SS.Length(); i++)
     ToWrite[i-1]=(unsigned char)SS[i];
  LenToWrite = SS.Length();

  int numi;
  unsigned char numch;
  
  for ( i=0; i<LenToWrite; i++)
  {
     numch=ToWrite[i];
     numi= (int)numch;
     if (HexRB->Checked)
        SS = SS.IntToHex(numi,2);
     else
        SS = IntToStr(numi);
     if (i == 0)
        RR = SS;
     else
        RR = RR + " " + SS;
  }
  Edit2->Lines->Strings[0] = RR;
        
}
//---------------------------------------------------------------------------

bool ok;

void __fastcall TForm2::Edit2KeyPress(TObject *Sender, char &Key)
{

    ok = true;
}
//---------------------------------------------------------------------------


void __fastcall TForm2::Edit2Change(TObject *Sender)
{
    prevText = Edit2->Text;
    int len = prevText.Length();
    if (!len)
        return;
    unsigned char Key = prevText[len];

    if (!ok)
    {
        ok = true;
        return;
    }

    if (Key >= 'a' && Key <= 'f')
        Key = Key - ('a'-'A');

    if ( (Key >= '0' && Key <= '9') || (Key >= 'A' && Key <= 'F') || Key == ' ' )
    {
        ok = true;
        return;

    }
    prevText.SetLength(len-1);
    Edit2->Text = prevText;
    Edit2->SelStart = len-1;

    ok = false;

}
//---------------------------------------------------------------------------

void __fastcall TForm2::SendBttnClick(TObject *Sender)
{
    //1st, correct the string!  Already done!!
    int answ = Application->MessageBox("Ok to send?", "Custom message", MB_OKCANCEL);
    if (answ != IDOK)
        return;

    //send!
    Form1->SendCustomStr(LenToWrite);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Edit2Exit(TObject *Sender)
{

  
  AnsiString App, App2;
  unsigned char numch;
  char numsch;
  int start,stop,numi;
  String s, RR;


  LenToWrite = 0;
  start = stop = 1;

  //for(int i=0; i<Edit2->Lines->Count; i++) App += Edit2->Lines->Strings[i];

  App = Edit2->Text;    //?

  while (start<=App.Length())
  {
     {
        // Cerca pos di inizio HEX
        while (start<=App.Length() &&
               !(   (App[start]>='0' && App[start]<='9')
                 || (App[start]>='A' && App[start]<='F')
                 || (App[start]>='a' && App[start]<='f')))
           start++;
        if (start>App.Length()) break;
        stop = start+1;
        while (stop<=App.Length() &&
                  ( (App[stop]>='0' && App[stop]<='9')
                 || (App[stop]>='A' && App[stop]<='F')
                 || (App[stop]>='a' && App[stop]<='f')) )
        {
           stop++;
           if (stop-start >= 2)
              break;
        }
     }
     App2 = App.SubString(start,stop-start);
     App2 = App2.Trim();
     App2 = "0x" + App2;
     numi = App2.ToInt();
     numch = (unsigned char)numi;
     numsch = (char) numch;
     ToWrite[LenToWrite++]=numch;
     if (numsch==0) numsch = 0x20; // Spazio per rappresentazione
     App2 = Format("%s", OPENARRAY(TVarRec, (numsch)));
     RR = RR + App2;
     start = stop;
  }
  
  //Edit2->Lines->Strings[0] = RR;
  //reconvert!
  s = "";
  RR = "";
  for (int i=0; i<LenToWrite; i++)
  {
    numch=ToWrite[i];
    s = s.IntToHex((int)numch,2);
    RR += s + " ";
  }
  // MessageDialog
  Edit2->Text = RR;


}
//---------------------------------------------------------------------------

