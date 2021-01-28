//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
#include <Menus.hpp>
#include <DBCtrls.hpp>
#include "dxfCheckBox.hpp"
#include "LMDCustomComponent.hpp"
#include "LMDStarter.hpp"
#include <CmAdmCtl.hpp>
#include <OleServer.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
    TComboBox *SerialSelectCB;
    TLabel *Label3;
    TRadioButton *LiveRB;
    TTimer *NewSerialTimer;
    TStaticText *StaticText6;
    TRichEdit *RichEdit1;
    TPopupMenu *PopupMenu1;
    TMenuItem *Clean1;
    TPanel *Panel2;
    TPanel *Panel1;
    TBitBtn *ConfigRequestBttn;
    TDBCheckBox *F2_SentCKB;
    TDBCheckBox *F2GotAnswerCKB;
    TComboBox *DeviceComboBox;
    TButton *CustomMsgBttn;
    TCheckBox *WriteLogPopMnu;
    TCheckBox *SendAnswerPopMnu;
    TSpeedButton *SpeedButton3;
    TEdit *Edit1;
    TStatusBar *StatusBar1;
    TdxfCheckBox *CB_Connect;
    TLabel *ConnectLabel;
    TPanel *Panel3;
    TLabel *Label1;
    TButton *Button2;
    TCheckBox *StatusCKB;
    TButton *ExitBttn;
    TButton *AlarmBttn;
    TLabel *Label2;
    TMenuItem *N1;
    TMenuItem *Frame09force1;
    TMenuItem *PrintRTF1;
    TBitBtn *BitBtn1;
    void __fastcall SWDateTimePicker1Change(TObject *Sender);
    void __fastcall SerialSelectCBChange(TObject *Sender);
    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
    void __fastcall NewSerialTimerTimer(TObject *Sender);
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall Clean1Click(TObject *Sender);
    void __fastcall ConfigRequestBttnClick(TObject *Sender);
    void __fastcall FormShow(TObject *Sender);
    void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
    void __fastcall DeviceComboBoxChange(TObject *Sender);
    void __fastcall CustomMsgBttnClick(TObject *Sender);
    void __fastcall FormConstrainedResize(TObject *Sender, int &MinWidth,
          int &MinHeight, int &MaxWidth, int &MaxHeight);
    void __fastcall FormResize(TObject *Sender);
    void __fastcall RichEdit1Change(TObject *Sender);
    void __fastcall CB_ConnectClick(TObject *Sender);
    void __fastcall StatusBar1DblClick(TObject *Sender);
    void __fastcall Button2Click(TObject *Sender);
    void __fastcall ExitBttnClick(TObject *Sender);
    void __fastcall SpeedButton3Click(TObject *Sender);
    void __fastcall AlarmBttnClick(TObject *Sender);
    void __fastcall Frame09force1Click(TObject *Sender);
    void __fastcall PrintRTF1Click(TObject *Sender);
    void __fastcall FormActivate(TObject *Sender);
    void __fastcall WriteLogPopMnuClick(TObject *Sender);
    void __fastcall BitBtn1Click(TObject *Sender);
private:	// User declarations
    int MemoSizeL;
    int MemoSizeH;
public:		// User declarations
    __fastcall TForm1(TComponent* Owner);

    void __fastcall AnalyzeRcv(void);
    void __fastcall MessageReceived(void);
    String __fastcall FormatSendString(unsigned char* buf, int len, bool space=true);
    void __fastcall SendCustomStr(int len);
    void __fastcall DeviceListInit();

    void __fastcall ThreadDone(TObject *Sender);

    bool F2Req;
    bool Cmd6Req;
    bool Cmd09Req;
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
