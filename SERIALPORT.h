//---------------------------------------------------------------------------
#ifndef SerialPortH
#define SerialPortH
//---------------------------------------------------------------------------
#include <SysUtils.hpp>
#include <Controls.hpp>
#include <Classes.hpp>
#include <Forms.hpp>
#include <Winbase.h>

#define BUFSIZE             20000

// Costanti ritornate dai metodi della classe TSerialPort
#define COMM_OK                  0
#define COMM_ERROR              -1
#define COMM_ERROR_COMNOTOPEN   -2
#define COMM_ERROR_TIMEOUT      -3

//---------------------------------------------------------------------------
// BAUD RATE. Se si inserisce un vuovo valore, modificare anche il vettore
// costante BaudConvert
typedef enum {cb___110=0,
              cb___300,
              cb___600,
              cb__1200,
              cb__2400,
              cb__4800,
              cb__9600,
              cb_14400,
              cb_19200,
              cb_38400,
              cb_56000,
              cb_57600,
              cb115200,
              cb128000,
              cb256000} comm_baudtype;
/*
const unsigned long BaudConvert[15] = {CBR_110, CBR_300, CBR_600, CBR_1200,
     CBR_2400, CBR_4800, CBR_9600, CBR_14400, CBR_19200, CBR_38400, CBR_56000,
     CBR_57600, CBR_115200, CBR_128000, CBR_256000};  **/
// PARITY
typedef enum {cpNo=0,
              cpOdd,
              cpEven,
              cpMark,
              cpSpace} comm_paritytype;
// DATA BITS
typedef enum {cd5=0,
              cd6,
              cd7,
              cd8} comm_datatype;
// STOP BITS
typedef enum {cs1=0,
              cs15,
              cs2} comm_stoptype;

typedef struct tagSERIALPORTINFO
{
    int    nPortNumber;
    LPTSTR sPortName;
    LPTSTR sFriendlyName;
    //struct tagSERIALPORTINFO* next;
} SERIALPORTINFO, *PSERIALPORTINFO;

int GetPortList(TList *TL);
void FreeTList(TList *TL, bool all=false);
void CreateCommList(TList *TL, TStringList *strl);

// COMPONENT DEFINITION
class PACKAGE TSerialPort : public TComponent
{
private:
  // Dati membro associati a proprietà
  unsigned int FCOMPort;
  comm_baudtype FBaud;
  comm_paritytype FParity;
  comm_datatype FData;
  comm_stoptype FStop;
  unsigned int FTOutRead;
  unsigned int FTOutWrite;
  unsigned long FBufferRX;
  unsigned long FBufferTX;
  // Dati membro privati
  DCB comm_dcb;
  COMMTIMEOUTS comm_TOuts;
  HANDLE comm_handle;
  // Private function
  void ShowLastError();
  void OpenCOMPort();

protected:
  virtual __fastcall ~TSerialPort();   // Class destructor
  void __fastcall SetCOMPort(unsigned int ACOMPort);
  void __fastcall SetBaud(comm_baudtype ABaud);
  void __fastcall SetParity(comm_paritytype AParity);
  void __fastcall SetData(comm_datatype AData);
  void __fastcall SetStop(comm_stoptype AStop);
  void __fastcall SetTOutRead(unsigned int ATOutRead);
  void __fastcall SetTOutWrite(unsigned int ATOutWrite);
  void __fastcall SetBufferRX(unsigned long ABufferRX);
  void __fastcall SetBufferTX(unsigned long ABufferTX);
  //Obsolete
  HANDLE  __fastcall BeginEnumeratePorts(void);
  //Obsolete
  bool __fastcall EnumeratePortsNext(HANDLE DeviceInfoSet, LPTSTR lpBuffer, LPTSTR buf=NULL, int len=0);
  //Obsolete
  bool  __fastcall EndEnumeratePorts(HANDLE DeviceInfoSet);

public:
  __fastcall TSerialPort(TComponent* Owner);

__published:
  // Proprietà
  __property unsigned int COMPort= {read=FCOMPort, write=SetCOMPort, default=0};
  __property comm_baudtype Baud = {read=FBaud, write=SetBaud, default=cb__9600};
  __property comm_paritytype Parity = {read=FParity, write=SetParity, default=cpNo};
  __property comm_datatype Data = {read=FData, write=SetData, default=cd8};
  __property comm_stoptype Stop = {read=FStop, write=SetStop, default=cs1};
  __property unsigned int TOutRead = {read=FTOutRead, write=SetTOutRead, default=2000};
  __property unsigned int TOutWrite = {read=FTOutWrite, write=SetTOutWrite, default=2000};
  __property unsigned long BufferRX = {read=FBufferRX, write=SetBufferRX, default=0};
  __property unsigned long BufferTX = {read=FBufferTX, write=SetBufferTX, default=0};

  //Obsolete
  int __fastcall CommList(TStringList *strl);
  //Obsolete
  int __fastcall CommNumber(TStringList *strl, int n);
  //Obsolete
  int __fastcall CommName(TStringList *strl, String s);
  // Metodi
  virtual HANDLE __fastcall GetHandle();
  virtual int __fastcall FlushBuffer(int RXorTX =0); // 0=RX 1=TX 2=BOTH
  virtual int __fastcall Read(char* buffer, unsigned long NumBytestoRead, unsigned long &NumBytesRead);
  virtual int __fastcall Write(const char* buffer, unsigned long NumBytestoWrite, unsigned long &NumBytesWritten);
  virtual int __fastcall ReadChar(char &carattere);
  virtual int __fastcall WriteChar(char carattere);
  virtual int __fastcall BIN_Read(unsigned char* buffer, unsigned long NumBytestoRead, unsigned long &NumBytesRead);
  virtual int __fastcall BIN_Write(const unsigned char* buffer, unsigned long NumBytestoWrite, unsigned long &NumBytesWritten);
  virtual int __fastcall BIN_ReadChar(unsigned char &carattere);
  virtual int __fastcall BIN_WriteChar(unsigned char carattere);
  virtual int __fastcall GetCharRXBuf();
  virtual int __fastcall GetCharTXBuf();
  virtual int __fastcall TryOpenCOMPort(int val);
};

//---------------------------------------------------------------------------
#endif
