//---------------------------------------------------------------------------

#ifndef SendCustomMsgFormH
#define SendCustomMsgFormH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TForm2 : public TForm
{
__published:	// IDE-managed Components
    TMemo *Edit2;
    TBitBtn *SendBttn;
    TBitBtn *CancelBttn;
    TRadioButton *HexRB;
    TLabel *Label1;
    TLabel *Label2;
    void __fastcall CancelBttnClick(TObject *Sender);
    void __fastcall Edit2DblClick(TObject *Sender);
    void __fastcall HexRBClick(TObject *Sender);
    void __fastcall Edit2KeyPress(TObject *Sender, char &Key);
    void __fastcall Edit2Change(TObject *Sender);
    void __fastcall SendBttnClick(TObject *Sender);
    void __fastcall Edit2Exit(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall TForm2(TComponent* Owner);

    unsigned char ToWrite[BUFSIZE];
    int LenToWrite;
};
//---------------------------------------------------------------------------
extern PACKAGE TForm2 *Form2;
//---------------------------------------------------------------------------
#endif
