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
    TBitBtn *BitBtn1;
    TLabel *Label3;
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall FormShow(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall TForm3(TComponent* Owner);
    
    void __fastcall EditClick(TObject *Sender);

    TEdit* Edit[8*2];

};
//---------------------------------------------------------------------------
extern PACKAGE TForm3 *Form3;
//---------------------------------------------------------------------------
#endif
