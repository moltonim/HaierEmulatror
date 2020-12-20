//---------------------------------------------------------------------------

#ifndef AlarmPanelH
#define AlarmPanelH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TForm3 : public TForm
{
__published:	// IDE-managed Components
    TEdit *Edit1;
    TLabel *Label1;
    TLabel *Label2;
    TButton *ClearBttn;
    TBitBtn *NextBitBttn;
    TComboBox *AlrmComboBox;
    TLabel *Label3;
    TSpeedButton *SpeedButton1;
    TBitBtn *EnterBitBttn;
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall FormShow(TObject *Sender);
    void __fastcall NextBitBttnClick(TObject *Sender);
    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
    void __fastcall SpeedButton1Click(TObject *Sender);
    void __fastcall AlrmComboBoxChange(TObject *Sender);
    void __fastcall Edit1Change(TObject *Sender);
    void __fastcall Edit1Enter(TObject *Sender);
    void __fastcall ClearBttnClick(TObject *Sender);
    void __fastcall EnterBitBttnClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall TForm3(TComponent* Owner);
    
    void __fastcall EditClick(TObject *Sender);
    void __fastcall FillEdits();

    TEdit* Edit[8*2];
    int device;
    unsigned long long ErrVal;

};
//---------------------------------------------------------------------------
extern PACKAGE TForm3 *Form3;
//---------------------------------------------------------------------------
#endif
