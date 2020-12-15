//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "AlarmPanel.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm3 *Form3;
//---------------------------------------------------------------------------
__fastcall TForm3::TForm3(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm3::FormCreate(TObject *Sender)
{
  int n;
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
  }

  n = Edit[7]->Width + Edit[7]->Left + Edit[0]->Left;
  Form3->ClientWidth = n;
  n = n/2 - Label1->Width/2;
  Label1->Left = n;
    
}
//---------------------------------------------------------------------------

void __fastcall TForm3::EditClick(TObject *Sender)
{
    int n = dynamic_cast<TEdit*>(Sender)->Tag;
    
}
