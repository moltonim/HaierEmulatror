#ifndef __DEFINE_H
#define __DEFINE_H

typedef struct _sercmd
{
    int val;
    char* cmd;
    } SERIAL_CMD;


//Functions
void StringInit(void);
unsigned char CalcCKS(const unsigned char* buf);
void UpdateLog(unsigned char *buf, int read, String note, int opt);
int FindCmdIdx(int val);
int UpdateStateMsg(int val, char mode);
//int StateMsgdim(int val);

//variables...
extern unsigned char DeviceProtocolVersion[8];

extern unsigned char EncriptionSign[3];

//SoftAp Device name when in configuration mode
extern unsigned char SoftApDeviceName_configMode[8];

extern unsigned char TYPEID[32];

extern unsigned char HW_SW_Version[8];

extern unsigned char QueryAttrStatus[50];



extern SERIAL_CMD serial_cmd[];
extern SERIAL_CMD Device_status[];

/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
// LEN = FF FF [2] len[1] {len-1}  CKS[1]
//                *-------------* = len!
// quindi lungh totale len (3° car) + 2xFF + 1CKS
// lunghezza totale: len + crc+ 2xFF = len+3!
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////


#define Answ_F2_LEN     (12+1)
extern unsigned char Answ_F2[50];



#define Answ_62_LEN     (46+1)
extern unsigned char Answ_62[50];

#define Answ_71_LEN     (42+1)
extern unsigned char* answ71;
extern String Answ71S;
extern unsigned char Answ_71_WC[50];
extern unsigned char Answ_71_WH[50];
extern unsigned char Answ_71_WM[50];
extern unsigned char Answ_71_HVAC[50];
extern unsigned char Answ_71_FR01[50];
extern unsigned char ACK_5[11];

#define Answ_73_LEN     (14+1)
extern unsigned char Answ_73[50];

#define Answ_014D01_LEN     (40+1)
extern unsigned char Answ_014D01[100];

#define Answ_FC_LEN     (17+1)
extern unsigned char Answ_FC[50];

#define ACK_5_LEN       (10+1)


#endif  //__DEFINE_H
