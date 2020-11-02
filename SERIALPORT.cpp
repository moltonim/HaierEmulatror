/*===========================================================================
Componente     : SerialPort                   Autore   : Masciocchi Dario
Classe         : TSerialPort
Ancestor       : TComponent                   Versione : 1.0
Package        : EldorAut                     Data     : 15 ott 1998
Comp. Palette  : Eldor Autom
Componenti utilizzati : ----

---- DESCRIZIONE ------------------------------------------------------------
  Componente non visuale per la gestione della comunicazione seriale.
  La modifica delle proprietà del componente si riflette automaticamente sulle
  impostazioni di comunicazione.
  L'assegnamento di un valore alla proprietà COMPort (unsigned int) causa
  l'apertura automatica della connessione.

---- PROPRIETA' -------------------------------------------------------------
   unsigned int    COMPort   def.=0         <0: No connession>
   comm_baudtype   Baud      def.=cb__9600  <Imp. dei default: 9600,n,8,1>
   comm_paritytype Parity    def.=cpNo
   comm_datatype   Data      def.=cd8
   comm_stoptype   Stop      def.=cs1
   unsigned int    TOutRead  def.=2000      <tempo in msec>
   unsigned int    TOutWrite def.=2000      <tempo in msec>
   unsigned long   BufferRX  def.=0         <0: mantiene l'impostazione di def.>
   unsigned long   BufferTX  def.=0         <0: mantiene l'impostazione di def.>

---- METODI -----------------------------------------------------------------

  HANDLE __fastcall GetHandle();
     Restituisce l'handle dell'oggetto COM per permettere la chiamata diretta
     delle API di comunicazione

  int FlushBuffer(int RXorTX =0);
     Rimuove il contenuto del buffer di ricezione (RXorTX=0), di quello di
     trasmissione (RXorTX=1) o di entrambi(RXorTX=2)

  int Read(char* buffer, unsigned long NumBytestoRead, unsigned long &NumBytesRead);
     Legge NumBytestoRead caratteri dal buffer di ricezione (o attende che
     arrivino per un tempo pari al timeout specificato) e li pone in buffer.
     Pone in NumBytesRead il numero di caratteri letti (serve se TIMEOUT)
     Codici di ritorno: COMM_OK, COMM_ERROR_COMNOTOPEN, COMM_ERROR_TIMEOUT, COM_ERROR

  int Write(const char* buffer, unsigned long NumBytestoWrite, unsigned long &NumBytesWritten);
     Scrive NumBytestoWrite caratteri nel buffer di trasmissione (o attende che
     ci sia spazio per un tempo pari al timeout specificato) leggendo da buffer.
     Pone in NumBytesWritten il numero di caratteri scritti (serve se TIMEOUT).
     Codici di ritorno: COMM_OK, COMM_ERROR_COMNOTOPEN, COMM_ERROR_TIMEOUT, COM_ERROR

  int ReadChar(char &carattere);
     Legge un carattere dal buffer di ricezione.
     Codici di ritorno: COMM_OK, COMM_ERROR_COMNOTOPEN, COMM_ERROR_TIMEOUT, COM_ERROR

  int WriteChar(char carattere);
     Scrive un carattere nel buffer di trasmissione.
     Codici di ritorno: COMM_OK, COMM_ERROR_COMNOTOPEN, COMM_ERROR_TIMEOUT, COM_ERROR

  int BIN_Read(unsigned char* buffer, unsigned long NumBytestoRead, unsigned long &NumBytesRead);
     Versione BINARIA del metodo Read: legge UNSIGNED CHAR anziché CHAR.
     Legge NumBytestoRead caratteri dal buffer di ricezione (o attende che
     arrivino per un tempo pari al timeout specificato) e li pone in buffer.
     Pone in NumBytesRead il numero di caratteri letti (serve se TIMEOUT)
     Codici di ritorno: COMM_OK, COMM_ERROR_COMNOTOPEN, COMM_ERROR_TIMEOUT, COM_ERROR

  int BIN_Write(const unsigned char* buffer, unsigned long NumBytestoWrite, unsigned long &NumBytesWritten);
     Versione BINARIA del metodo Write: scrive UNSIGNED CHAR anziché CHAR.
     Scrive NumBytestoWrite caratteri nel buffer di trasmissione (o attende che
     ci sia spazio per un tempo pari al timeout specificato) leggendo da buffer.
     Pone in NumBytesWritten il numero di caratteri scritti (serve se TIMEOUT).
     Codici di ritorno: COMM_OK, COMM_ERROR_COMNOTOPEN, COMM_ERROR_TIMEOUT, COM_ERROR

  int BIN_ReadChar(unsigned char &carattere);
     Versione BINARIA del metodo ReadChar: legge UNSIGNED CHAR anziché CHAR.
     Legge un carattere dal buffer di ricezione.
     Codici di ritorno: COMM_OK, COMM_ERROR_COMNOTOPEN, COMM_ERROR_TIMEOUT, COM_ERROR

  int BIN_WriteChar(unsigned char carattere);
     Versione BINARIA del metodo WriteChar: scrive UNSIGNED CHAR anziché CHAR.
     Scrive un carattere nel buffer di trasmissione.
     Codici di ritorno: COMM_OK, COMM_ERROR_COMNOTOPEN, COMM_ERROR_TIMEOUT, COM_ERROR

  int GetCharRXBuf();
     Restituisce il numero di caratteri presenti nel buffer di ricezione.
     In caso di errore, restituisce (numero negativo) il codice di errore
     che può essere: COMM_ERROR_COMNOTOPEN o COMM_ERROR.

  int GetCharTXBuf();
     Restituisce il numero di caratteri presenti nel buffer di trasmissione.
     In caso di errore, restituisce (numero negativo) il codice di errore
     che può essere: COMM_ERROR_COMNOTOPEN o COMM_ERROR.

---- TIPI DI DATO -----------------------------------------------------------
  comm_baudtype: enumerativo
     valori: cb___110, cb___300, cb___600, cb__1200, cb__2400,  cb__4800,
             cb__9600, cb_14400, cb_19200, cb_38400, cb_56000,  cb_57600,
             cb115200, cb128000, cb256000
     è possibile convertire questo tipo in un unsigned long tramite il vettore
     BaudConvert: ULONGVar = BaudConvert[comm_baudtypeVar]

  comm_paritytype: enumerativo
     valori: cpNo, cpOdd, cpEven, cpMark, cpSpace

  comm_datatype: enumerativo
     valori: cd5, cd6, cd7, cd8
     il numero di bit di dati si ottiene sommando 5 alla variabile di
     tipo comm_datatype

  comm_stoptype: enumerativo
     valori: cs1=0, cs15, cs2

---- COSTANTI ---------------------------------------------------------------
  Valori ritornati dai metodi di TSerialPort:
     COMM_OK                  0
     COMM_ERROR              -1
     COMM_ERROR_COMNOTOPEN   -2
     COMM_ERROR_TIMEOUT      -3

===========================================================================*/


//---------------------------------------------------------------------------
#include <vcl.h>
#include <stdio.h>
#include <setupapi.h>
#include <dbt.h>
#include <ComCtrls.hpp>
#pragma hdrstop

#include "SerialPort.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------
// ValidCtrCheck is used to assure that the components created do not have
// any pure virtual functions.
//

#define RegDisposition_OpenExisting (0x00000001)   // open key only if exists
#define CM_REGISTRY_HARDWARE        (0x00000000)
#define MAX_NAME_PORTS          7

const unsigned long BaudConvert[15] = {CBR_110, CBR_300, CBR_600, CBR_1200,
     CBR_2400, CBR_4800, CBR_9600, CBR_14400, CBR_19200, CBR_38400, CBR_56000,
     CBR_57600, CBR_115200, CBR_128000, CBR_256000};

typedef DWORD WINAPI  (* CM_Open_DevNode_Key)(DWORD, DWORD, DWORD, DWORD, ::PHKEY, DWORD);

////////////////////////////////////////////////////////////////////////////////

static HANDLE SetupEnumeratePorts()
{
    HDEVINFO hDevices = INVALID_HANDLE_VALUE;
    DWORD dwGuids = 0;
    BOOL br = SetupDiClassGuidsFromName("Ports", 0, 0, &dwGuids);
    if (dwGuids) {
        LPGUID pguids = (LPGUID)HeapAlloc(GetProcessHeap(), 0, sizeof(GUID) * dwGuids);
        if (pguids) {
            br = SetupDiClassGuidsFromName("Ports", pguids, dwGuids, &dwGuids);
            if (br) {
                hDevices = SetupDiGetClassDevs(pguids, NULL, NULL, DIGCF_PRESENT);
            }
            HeapFree(GetProcessHeap(), 0, pguids);
        }
    }
    return hDevices;
}

static BOOL EndEnumeratePorts(HANDLE hDevices)
{
    if (SetupDiDestroyDeviceInfoList(hDevices)) {
        return TRUE;
    }
    return FALSE;
}

int __fastcall CompareCOM_ItemsNum(void *Item1, void *Item2)
{
  if (((PSERIALPORTINFO)Item1)->nPortNumber > ((PSERIALPORTINFO)Item2)->nPortNumber)
    return 1;
  else if (((PSERIALPORTINFO)Item1)->nPortNumber == ((PSERIALPORTINFO)Item2)->nPortNumber)
    return 0;
  else return -1;
}


BOOL GetSerialPortInfo(TList *TL)
{
    HANDLE hDevices = SetupEnumeratePorts();
    BOOL br = TRUE;
    DWORD nDevice = 0;
    String s;

    for (nDevice = 0; br ; nDevice++)
    {
        DWORD cbData = 0;
        SP_DEVINFO_DATA deviceData;
        deviceData.cbSize = sizeof(SP_DEVINFO_DATA);
        br = SetupDiEnumDeviceInfo(hDevices, nDevice, &deviceData);
        if (br)
        {
            TCHAR sz[16] = {0};
            HKEY hkey = SetupDiOpenDevRegKey(hDevices, &deviceData, DICS_FLAG_GLOBAL, 0, DIREG_DEV, KEY_READ);
            if (hkey)
            {
                DWORD cbSize = 16 * sizeof(TCHAR);
                RegQueryValueEx(hkey, "PortName", NULL, NULL, (LPBYTE)sz, &cbSize);
                RegCloseKey(hkey);
            }
            CharUpper(sz);
            if (sz[0] == 'C' && sz[1] == 'O' && sz[2] == 'M')
            {
                PSERIALPORTINFO pInfo = new SERIALPORTINFO;
                // = (PSERIALPORTINFO)HeapAlloc(GetProcessHeap(), 0, sizeof(SERIALPORTINFO));
                //pInfo->next = 0;
                pInfo->sPortName = (LPTSTR)HeapAlloc(GetProcessHeap(), 0, (lstrlen(sz) + 1));
                strcpy(pInfo->sPortName, sz);

                s = String(sz);
                //pInfo->sPortName = s;
                pInfo->nPortNumber = atoi(&sz[3]);

                SetupDiGetDeviceRegistryProperty(hDevices, &deviceData, SPDRP_FRIENDLYNAME, NULL, NULL, 0, &cbData);
                if (cbData)
                {
                    //pInfo->pszFriendlyName = (LPTSTR)HeapAlloc(GetProcessHeap(), 0, cbData + sizeof(TCHAR));
                    pInfo->sFriendlyName = (LPTSTR)HeapAlloc(GetProcessHeap(), 0, cbData + sizeof(TCHAR));
                    br = SetupDiGetDeviceRegistryProperty(hDevices, &deviceData, SPDRP_FRIENDLYNAME,
                                                      NULL, (LPBYTE)pInfo->sFriendlyName, cbData, NULL);
                }
                TL->Add(pInfo);
            }
        }
    }
    EndEnumeratePorts(hDevices);
    TL->Sort(CompareCOM_ItemsNum);
    return br;
}

void FreeTList(TList *TL, bool all)
{
  for (int i = 0; i < TL->Count; i++)  {
    PSERIALPORTINFO C = (PSERIALPORTINFO) TL->Items[i];
    HeapFree(GetProcessHeap(), 0, C->sPortName);
    HeapFree(GetProcessHeap(), 0, C->sFriendlyName);
    delete C;
  }
  if (all)
     delete TL;
}


int GetPortList(TList *TL)
{
  int n;
  const char* s = "0 - None";

  PSERIALPORTINFO pInfo = new SERIALPORTINFO;
  pInfo->sPortName = (LPTSTR)HeapAlloc(GetProcessHeap(), 0, (strlen(s) + 1));
  pInfo->sFriendlyName = (LPTSTR)HeapAlloc(GetProcessHeap(), 0, (strlen(s) + 1));
  strcpy(pInfo->sPortName, s);
  strcpy(pInfo->sFriendlyName, s);
  pInfo->nPortNumber = 0;
  TL->Add(pInfo);

  GetSerialPortInfo(TL);

  n = TL->Count;

  return n;
}

void CreateCommList(TList *TL, TStringList *strl)
{
  String s;

  strl->Clear();
  for (int i = 0; i < TL->Count; i++) {
    PSERIALPORTINFO C = (PSERIALPORTINFO) TL->Items[i];
    s = C->sFriendlyName;
    strl->Add(s);
    }

}



////////////////////////////////////////////////////////////////////////////////
HANDLE  __fastcall TSerialPort::BeginEnumeratePorts(void)
{
    BOOL guidTest=FALSE;
    DWORD RequiredSize=0;
    int j;
    HDEVINFO DeviceInfoSet;
    char* buf;

    guidTest = SetupDiClassGuidsFromNameA("Ports",0,0,&RequiredSize);
    if(RequiredSize < 1)
        return HANDLE(-1);

    buf=(char *)malloc(RequiredSize*sizeof(GUID));

    guidTest=SetupDiClassGuidsFromNameA("Ports",(GUID *)buf,
        RequiredSize*sizeof(GUID), &RequiredSize);

    if(!guidTest)
        return HANDLE(-1);

    DeviceInfoSet=SetupDiGetClassDevs((GUID *)buf, NULL, NULL, DIGCF_PRESENT);
    if(DeviceInfoSet == INVALID_HANDLE_VALUE)
        return (HANDLE)-1;

    free(buf);
    return DeviceInfoSet;
}

bool __fastcall TSerialPort::EnumeratePortsNext(HANDLE DeviceInfoSet, LPTSTR lpBuffer, LPTSTR buf, int buflen)
{
    static CM_Open_DevNode_Key OpenDevNodeKey=NULL;
    static HINSTANCE CfgMan;
    static int numDev=0;
    DWORD cbData;

    if (!DeviceInfoSet) {
        OpenDevNodeKey = NULL;
        CfgMan = 0;
        numDev = 0;
        return false;
        }
    int res1;
    char DevName[MAX_NAME_PORTS] = {0};
    int numport;

    SP_DEVINFO_DATA DeviceInfoData={0};
    DeviceInfoData.cbSize=sizeof(SP_DEVINFO_DATA);


    if(!DeviceInfoSet || !lpBuffer)
        return -1;
    if(!OpenDevNodeKey) {
        CfgMan=LoadLibrary("cfgmgr32");
        if(!CfgMan)
            return FALSE;
        OpenDevNodeKey=(CM_Open_DevNode_Key)GetProcAddress(CfgMan,"CM_Open_DevNode_Key");
        if(!OpenDevNodeKey) {
            FreeLibrary(CfgMan);
            return FALSE;
            }
        }

    while(TRUE) {
        HKEY KeyDevice;
        DWORD len;
        res1=SetupDiEnumDeviceInfo(DeviceInfoSet, numDev, &DeviceInfoData);

        if(!res1)   {
          SetupDiDestroyDeviceInfoList(DeviceInfoSet);
          FreeLibrary(CfgMan);
          OpenDevNodeKey=NULL;
          return FALSE;
          }

        res1 = OpenDevNodeKey( DeviceInfoData.DevInst, KEY_QUERY_VALUE, 0,
            RegDisposition_OpenExisting, &KeyDevice, CM_REGISTRY_HARDWARE);
        if(res1 != ERROR_SUCCESS)
            return NULL;

        len = MAX_NAME_PORTS;

        res1=RegQueryValueExA(
                KeyDevice,	// handle of key to query
                "portname",	// address of name of value to query
                NULL,	// reserved
                NULL,	// address of buffer for value type
                (LPBYTE)DevName,	// address of data buffer
                &len 	// address of data buffer size
                );

        RegCloseKey(KeyDevice);
        if(res1 != ERROR_SUCCESS)
            return NULL;
        numDev++;
        if(memicmp(DevName, "com", 3))
            continue;
        numport=atoi(DevName+3);
        if(numport > 0) {
          strcpy(lpBuffer,DevName);
          SetupDiGetDeviceRegistryProperty(DeviceInfoSet, &DeviceInfoData, SPDRP_FRIENDLYNAME, NULL, NULL, 0, &cbData);
	        if (cbData) {
            buflen = ((int)cbData > buflen)? buflen:(int)cbData;
            SetupDiGetDeviceRegistryProperty(DeviceInfoSet, &DeviceInfoData, SPDRP_FRIENDLYNAME, NULL, (LPTSTR)buf, buflen, NULL);
            }
          FreeLibrary(CfgMan);
          return TRUE;
         }

	      FreeLibrary(CfgMan);
        OpenDevNodeKey=NULL;
        return FALSE;
   }
}

bool __fastcall TSerialPort::EndEnumeratePorts(HANDLE DeviceInfoSet)
{
    if(SetupDiDestroyDeviceInfoList(DeviceInfoSet))
        return TRUE;
    else return FALSE;
}

////////////////////////////////////////////////////////////////////////////////


static inline void ValidCtrCheck(TSerialPort *)
{
  new TSerialPort(NULL);
}
//--COSTRUTTORE--------------------------------------------------------------
__fastcall TSerialPort::TSerialPort(TComponent* Owner)
  : TComponent(Owner)
{
  FCOMPort = 0;
  FBaud = cb__9600;
  FParity = cpNo;
  FData = cd8;
  FStop = cs1;
  FTOutRead = 2000;
  FTOutWrite = 2000;
  FBufferTX = 0;
  FBufferRX = 0;

  comm_handle = NULL;
}

//--DISTRUTTORE--------------------------------------------------------------
__fastcall TSerialPort::~TSerialPort()
{
  // Close handle if opened
  if (comm_handle!=NULL)
     if (!CloseHandle(comm_handle))
        // Chiusura fallita
        MessageDlg("Impossibile chiudere \nil collegamento",
           mtWarning,TMsgDlgButtons() <<  mbOK,0);
}

//--PRIVATA: SHOWERROR-------------------------------------------------------
void TSerialPort::ShowLastError()
{
  LPVOID lpMsgBuf;

  FormatMessage(
     FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
     NULL,
     GetLastError(),
     MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
     (LPTSTR) &lpMsgBuf,
     0,
     NULL
  );
  char * dummyconv = (char*) lpMsgBuf;
  // Display the string.
  String msgErrore = Format("%s",OPENARRAY(TVarRec,(dummyconv)));
  MessageDlg(msgErrore,mtWarning,TMsgDlgButtons() << mbOK,0);

  // Free the buffer.

  LocalFree( lpMsgBuf );
}




//MLT: TryOpenCommPort: Privata
//MLT: DA RIVEDERE !!!
//int TSerialPort::TryOpenCOMPort(int val)
int __fastcall TSerialPort::TryOpenCOMPort(int val)
{
  HANDLE comm_handle;
  char ss[10];

  // OPEN
  sprintf(ss,"\\\\.\\com%d",val);
  //comm_handle=CreateFile(ss,GENERIC_READ|GENERIC_WRITE,0,NULL,OPEN_EXISTING, 0, NULL);
  comm_handle=CreateFile(ss,0,0,NULL,OPEN_EXISTING, FILE_FLAG_OVERLAPPED, NULL);
  if (comm_handle == INVALID_HANDLE_VALUE || comm_handle == 0)
    return 1;

  CloseHandle(comm_handle);
  return 0;
}


//--PRIVATA: OPENCOMPORT-----------------------------------------------------
void TSerialPort::OpenCOMPort()
{
  BOOL Failure;
  char ss[10];
  //DWORD val;

  memset(ss, 0, sizeof(ss));
  if (comm_handle!=NULL)
     // Close current
     if (!CloseHandle(comm_handle))
     {
        // Chiusura fallita
        MessageDlg("Impossibile chiudere il \nprecedente collegamento",
           mtWarning,TMsgDlgButtons() << mbOK,0);
        comm_handle = NULL;
     }
  // OPEN
  //sprintf(ss,"COM%d",FCOMPort);
  sprintf(ss,"\\\\.\\com%d",FCOMPort);
  comm_handle=CreateFile(ss,GENERIC_READ|GENERIC_WRITE,0,NULL,OPEN_EXISTING, 0, NULL);
  //comm_handle=CreateFileA("\\\\.\\com20",GENERIC_READ|GENERIC_WRITE,0,NULL,OPEN_EXISTING, 0, NULL);
  if (comm_handle == INVALID_HANDLE_VALUE)
  {
     MessageDlg("Impossibile aprire \nla porta COM selezionata",
           mtError, TMsgDlgButtons() << mbOK,0);
     comm_handle = NULL;
     return;
  }
  // ALL OK: leggo impostazioni attuali per creare il DCB
  Failure = !GetCommState(comm_handle,&comm_dcb);

  // Set comm properties
  // BUFFER
  COMMPROP comm_prop;
  Failure &= !GetCommProperties(comm_handle,&comm_prop);
  DWORD BRXtoSet = comm_prop.dwCurrentRxQueue;
  DWORD BTXtoSet = comm_prop.dwCurrentTxQueue;
  if (!FBufferRX) BRXtoSet=FBufferRX;
  if (!FBufferTX) BTXtoSet=FBufferTX;
  Failure &= !SetupComm(comm_handle, BRXtoSet, BTXtoSet);
  // TIMEOUT
  comm_TOuts.ReadIntervalTimeout=0;
  comm_TOuts.ReadTotalTimeoutMultiplier=0;
  comm_TOuts.ReadTotalTimeoutConstant=FTOutRead;
  comm_TOuts.WriteTotalTimeoutMultiplier=0;
  comm_TOuts.WriteTotalTimeoutConstant=FTOutWrite;
  Failure &= !SetCommTimeouts(comm_handle,&comm_TOuts);
  // BAUD,PARITY,DATA,STOP
  comm_dcb.BaudRate = BaudConvert[FBaud];
  if (FParity==cpNo) comm_dcb.fParity = 0;
  else comm_dcb.fParity = 1;
  comm_dcb.Parity = FParity;
  unsigned DataToSet = FData + 5;
  comm_dcb.ByteSize = (BYTE)DataToSet;
  comm_dcb.StopBits = FStop;
  Failure &= !SetCommState(comm_handle,&comm_dcb);
  // FLUSH BUFFERS
  Failure &= !PurgeComm(comm_handle,PURGE_TXCLEAR|PURGE_RXCLEAR);
  // MSG if KO
  if (Failure)
     MessageDlg("Setup della porta\nCOM fallito.",
        mtError, TMsgDlgButtons() << mbOK,0);
}

//Obsolete
int __fastcall TSerialPort::CommList(TStringList *strl)
{
    //strl->Clear();
    /*int n = 0;
    for (n = 0; n < max+1; n++)
        if (TryOpenCOMPort(n))
            strl->Add(IntToStr(n));
   */
    HANDLE res;
    char buf[20];
    char friendname[50];

    EnumeratePortsNext(0, NULL);  //Delete the old enumerate, if any
    res=BeginEnumeratePorts();
    strl->Clear();
    strl->Add("0 - None");
    while(1) {
        if( !EnumeratePortsNext(res, buf, friendname, sizeof(friendname)) )
            break;
        strl->Add(String(buf)+"  ["+String(friendname)+"]");
        }

    EndEnumeratePorts(res);
    return 0;
}

//Obsolete
int __fastcall TSerialPort::CommNumber(TStringList *strl, int n)
{
    int size = strl->Count;

    if (n > size-1)
        return -1;

    if (n == 0)
        return 0;
    String s = strl->Strings[n];

    s = s.UpperCase();
    int pos = s.Pos("COM");
    s = s.SubString(pos+3, 3);
    n = StrToIntDef(s,0);
    if (pos && (n>0 && n < 255) )    {
        return n;
        }
    return n;
}

//Obsolete
int __fastcall TSerialPort::CommName(TStringList *strl, String s)
{
    int size = strl->Count;
    int n;

    for (n = 0; n < size; n++)
        if (s == strl->Strings[n])
            break;
    if (n >= size)
        return 0;

    s = s.UpperCase();
    int pos = s.Pos("COM");
    s = s.SubString(pos+3, 3);
    s = s.Trim();
    n = StrToIntDef(s,0);
    if (pos && (n>0 && n < 255) )    {
        return n;
        }
    return 0;
}



//--PROPRIETA' COMPort-------------------------------------------------------
void __fastcall TSerialPort::SetCOMPort(unsigned int ACOMPort)
{
  FCOMPort = ACOMPort;
  if (ComponentState.Contains(csDesigning)) return;
  // Codice non eseguito in fase di progettazione
  if (FCOMPort)
    OpenCOMPort();
  else
  {
     if (comm_handle!=NULL)
        // Chiude comunicazione corrente
        if (!CloseHandle(comm_handle))
           // Chiusura fallita
           MessageDlg("Impossibile chiudere il \nprecedente collegamento",
              mtWarning,TMsgDlgButtons() << mbOK,0);
     comm_handle = NULL;
  }
}

//--PROPRIETA' Baud----------------------------------------------------------
void __fastcall TSerialPort::SetBaud(comm_baudtype ABaud)
{
  FBaud = ABaud;
  if (ComponentState.Contains(csDesigning) || (comm_handle==NULL)) return;
  // Codice non eseguito in fase di progettazione o se COM non inizial.
  comm_dcb.BaudRate = BaudConvert[FBaud];
  if (!SetCommState(comm_handle,&comm_dcb))
     MessageDlg("Setup del baud \nrate fallito.",
        mtWarning,TMsgDlgButtons() << mbOK,0);
}

//--PROPRIETA' Parity--------------------------------------------------------
void __fastcall TSerialPort::SetParity(comm_paritytype AParity)
{
  FParity = AParity;
  if (ComponentState.Contains(csDesigning) || (comm_handle==NULL)) return;
  // Codice non eseguito in fase di progettazione o se COM non inizial.
  if (FParity==cpNo) comm_dcb.fParity = 0;
  else comm_dcb.fParity = 1;
  comm_dcb.Parity = FParity;
  if (!SetCommState(comm_handle,&comm_dcb))
     MessageDlg("Setup della \nparità fallito.",
        mtWarning,TMsgDlgButtons() << mbOK,0);

}

//--PROPRIETA' Data----------------------------------------------------------
void __fastcall TSerialPort::SetData(comm_datatype AData)
{
  FData = AData;
  if (ComponentState.Contains(csDesigning) || (comm_handle==NULL)) return;
  // Codice non eseguito in fase di progettazione o se COM non inizial.
  unsigned DataToSet = FData + 5;
  comm_dcb.ByteSize = (BYTE)DataToSet;
  if (!SetCommState(comm_handle,&comm_dcb))
     MessageDlg("Setup dei bit di \ndato fallito.",
        mtWarning,TMsgDlgButtons() << mbOK,0);
}

//--PROPRIETA' Stop----------------------------------------------------------
void __fastcall TSerialPort::SetStop(comm_stoptype AStop)
{
  FStop = AStop;
  if (ComponentState.Contains(csDesigning) || (comm_handle==NULL)) return;
  // Codice non eseguito in fase di progettazione o se COM non inizial.
  comm_dcb.StopBits = FStop;
  if (!SetCommState(comm_handle,&comm_dcb))
     MessageDlg("Setup dei bit di \nstop fallito.",
        mtWarning,TMsgDlgButtons() << mbOK,0);
}

//--PROPRIETA' TOutRead------------------------------------------------------
void __fastcall TSerialPort::SetTOutRead(unsigned int ATOutRead)
{
  FTOutRead = ATOutRead;
  if (ComponentState.Contains(csDesigning) || (comm_handle==NULL)) return;
  // Codice non eseguito in fase di progettazione o se COM non inizial.
  comm_TOuts.ReadTotalTimeoutConstant=FTOutRead;
  if (!SetCommTimeouts(comm_handle,&comm_TOuts))
     MessageDlg("Setup del timeout \ndi lettura fallito.",
        mtWarning,TMsgDlgButtons() << mbOK,0);
}

//--PROPRIETA' TOutWrite-----------------------------------------------------
void __fastcall TSerialPort::SetTOutWrite(unsigned int ATOutWrite)
{
  FTOutWrite = ATOutWrite;
  if (ComponentState.Contains(csDesigning) || (comm_handle==NULL)) return;
  // Codice non eseguito in fase di progettazione o se COM non inizial.
  comm_TOuts.WriteTotalTimeoutConstant=FTOutWrite;
  if (!SetCommTimeouts(comm_handle,&comm_TOuts))
     MessageDlg("Setup del timeout \ndi scrittura fallito.",
        mtWarning,TMsgDlgButtons() << mbOK,0);
}

//--PROPRIETA' BufferRX------------------------------------------------------
void __fastcall TSerialPort::SetBufferRX(unsigned long ABufferRX)
{
  COMMPROP comm_prop;
  BOOL Failure;
  DWORD BRXtoSet, BTXtoSet;

  FBufferRX = ABufferRX;
  if (ComponentState.Contains(csDesigning) || (comm_handle==NULL)) return;
  // Codice non eseguito in fase di progettazione o se COM non inizial.
  Failure = !GetCommProperties(comm_handle,&comm_prop);
  BRXtoSet = comm_prop.dwCurrentRxQueue;
  BTXtoSet = comm_prop.dwCurrentTxQueue;
  if (!FBufferRX) BRXtoSet=FBufferRX;
  if (!FBufferTX) BTXtoSet=FBufferTX;
  Failure &= !SetupComm(comm_handle, BRXtoSet, BTXtoSet);
  if (Failure)
     MessageDlg("Setup del buffer \ndi lettura fallito.",
        mtWarning,TMsgDlgButtons() << mbOK,0);
}

//--PROPRIETA' BufferTX------------------------------------------------------
void __fastcall TSerialPort::SetBufferTX(unsigned long ABufferTX)
{
  COMMPROP comm_prop;
  BOOL Failure;
  DWORD BRXtoSet, BTXtoSet;

  FBufferTX = ABufferTX;
  if (ComponentState.Contains(csDesigning) || (comm_handle==NULL)) return;
  // Codice non eseguito in fase di progettazione o se COM non inizial.
  Failure = !GetCommProperties(comm_handle,&comm_prop);
  BRXtoSet = comm_prop.dwCurrentRxQueue;
  BTXtoSet = comm_prop.dwCurrentTxQueue;
  if (!FBufferRX) BRXtoSet=FBufferRX;
  if (!FBufferTX) BTXtoSet=FBufferTX;
  Failure &= !SetupComm(comm_handle, BRXtoSet, BTXtoSet);
  if (Failure)
     MessageDlg("Setup del buffer \ndi scrittura fallito.",
        mtWarning,TMsgDlgButtons() << mbOK,0);
}

//--METODO GetHandle---------------------------------------------------------
HANDLE __fastcall TSerialPort::GetHandle()
{
  return comm_handle;
}

//--METODO FlushBuffer-------------------------------------------------------
int __fastcall TSerialPort::FlushBuffer(int RXorTX /*=0*/)  // 0=RX 1=TX 2=BOTH
{
  DWORD Flags;
  if (comm_handle == NULL) return COMM_ERROR_COMNOTOPEN;
  switch (RXorTX)
  {
    case 1: Flags=PURGE_TXCLEAR;
    break;
    case 2: Flags=PURGE_TXCLEAR|PURGE_RXCLEAR;
    break;
    default: Flags=PURGE_RXCLEAR;
  }
  if(PurgeComm(comm_handle,Flags)) return COMM_OK;
  else return COMM_ERROR;
}

//--METODO Read--------------------------------------------------------------
int __fastcall TSerialPort::Read(char* buffer, unsigned long NumBytestoRead,
                                   unsigned long &NumBytesRead)
{
  if (comm_handle == NULL) return COMM_ERROR_COMNOTOPEN;
  int ris=ReadFile(comm_handle,(void*)buffer,NumBytestoRead,&NumBytesRead,NULL);
  if (!ris)
  {
     ShowLastError();
     return COMM_ERROR;
  }
  if (NumBytesRead==NumBytestoRead) return COMM_OK;
  else return COMM_ERROR_TIMEOUT;
}

//--METODO Write-------------------------------------------------------------
int __fastcall TSerialPort::Write(const char* buffer, unsigned long NumBytestoWrite,
                                   unsigned long &NumBytesWritten)
{
  if (comm_handle == NULL) return COMM_ERROR_COMNOTOPEN;
  int ris=WriteFile(comm_handle,(void*)buffer,NumBytestoWrite,&NumBytesWritten,NULL);
  if (!ris)
  {
     ShowLastError();
     return COMM_ERROR;
  }
  if (NumBytesWritten==NumBytestoWrite) return COMM_OK;
  else return COMM_ERROR_TIMEOUT;
}

//--METODO ReadChar----------------------------------------------------------
int __fastcall TSerialPort::ReadChar(char &carattere)
{
  unsigned long BytesRead;

  if (comm_handle == NULL) return COMM_ERROR_COMNOTOPEN;
  int ris=ReadFile(comm_handle,(void*)&carattere,1,&BytesRead,NULL);
  if (!ris)
  {
     ShowLastError();
     return COMM_ERROR;
  }
  if (BytesRead==1) return COMM_OK;
  else return COMM_ERROR_TIMEOUT;
}

//--METODO WriteChar---------------------------------------------------------
int __fastcall TSerialPort::WriteChar(char carattere)
{
  unsigned long BytesWritten;

  if (comm_handle == NULL) return COMM_ERROR_COMNOTOPEN;
  int ris=WriteFile(comm_handle,(void*)&carattere,1,&BytesWritten,NULL);
  if (!ris)
  {
     ShowLastError();
     return COMM_ERROR;
  }
  if (BytesWritten==1) return COMM_OK;
  else return COMM_ERROR_TIMEOUT;

}

//--METODO BIN_Read----------------------------------------------------------
int __fastcall TSerialPort::BIN_Read(unsigned char* buffer, unsigned long NumBytestoRead,
                                   unsigned long &NumBytesRead)
{
  if (comm_handle == NULL) return COMM_ERROR_COMNOTOPEN;
  int ris=ReadFile(comm_handle,(void*)buffer,NumBytestoRead,&NumBytesRead,NULL);
  if (!ris)
  {
     ShowLastError();
     return COMM_ERROR;
  }
  if (NumBytesRead==NumBytestoRead) return COMM_OK;
  else return COMM_ERROR_TIMEOUT;
}

//--METODO BIN_Write---------------------------------------------------------
int __fastcall TSerialPort::BIN_Write(const unsigned char* buffer, unsigned long NumBytestoWrite,
                                   unsigned long &NumBytesWritten)
{
  if (comm_handle == NULL) return COMM_ERROR_COMNOTOPEN;
  int ris=WriteFile(comm_handle,(void*)buffer,NumBytestoWrite,&NumBytesWritten,NULL);
  if (!ris)
  {
     ShowLastError();
     return COMM_ERROR;
  }
  if (NumBytesWritten==NumBytestoWrite) return COMM_OK;
  else return COMM_ERROR_TIMEOUT;
}

//--METODO BIN_ReadChar------------------------------------------------------
int __fastcall TSerialPort::BIN_ReadChar(unsigned char &carattere)
{
  unsigned long BytesRead;

  if (comm_handle == NULL) return COMM_ERROR_COMNOTOPEN;
  int ris=ReadFile(comm_handle,(void*)&carattere,1,&BytesRead,NULL);
  if (!ris)
  {
     ShowLastError();
     return COMM_ERROR;
  }
  if (BytesRead==1) return COMM_OK;
  else return COMM_ERROR_TIMEOUT;
}

//--METODO BIN_WriteChar-----------------------------------------------------
int __fastcall TSerialPort::BIN_WriteChar(unsigned char carattere)
{
  unsigned long BytesWritten;

  if (comm_handle == NULL) return COMM_ERROR_COMNOTOPEN;
  int ris=WriteFile(comm_handle,(void*)&carattere,1,&BytesWritten,NULL);
  if (!ris)
  {
     ShowLastError();
     return COMM_ERROR;
  }
  if (BytesWritten==1) return COMM_OK;
  else return COMM_ERROR_TIMEOUT;

}

//--METODO GetCharRXBuf------------------------------------------------------
int __fastcall TSerialPort::GetCharRXBuf()
{
  COMSTAT comm_status;
  unsigned long ErrorCode;

  if (comm_handle == NULL) return COMM_ERROR_COMNOTOPEN;
  if(ClearCommError(comm_handle,&ErrorCode,&comm_status))
     return comm_status.cbInQue;
  else return COMM_ERROR;
}

//--METODO GetCharTXBuf------------------------------------------------------
int __fastcall TSerialPort::GetCharTXBuf()
{
  COMSTAT comm_status;
  unsigned long ErrorCode;

  if (comm_handle == NULL) return COMM_ERROR_COMNOTOPEN;
  if(ClearCommError(comm_handle,&ErrorCode,&comm_status))
     return comm_status.cbOutQue;
  else return COMM_ERROR;
}


//--COMPONENT REGISTRATION---------------------------------------------------
namespace Serialport
{
  void __fastcall PACKAGE Register()
  {
     TComponentClass classes[1] = {__classid(TSerialPort)};
     RegisterComponents("Eldor Autom", classes, 0);
  }
}
//---------------------------------------------------------------------------
