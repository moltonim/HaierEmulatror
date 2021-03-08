#ifndef __DEFINE_H
#define __DEFINE_H

typedef struct _sercmd
{
    int val;
    char* cmd;
    } SERIAL_CMD;

typedef enum _devtype
{
    DEV_TYPE_WC,                 //0 wine cooler
    DEV_TYPE_WH,                 //1 water heater
    DEV_TYPE_HVAC,               //2 condizionatore
    DEV_TYPE_HVAC2,              // condiz 2
    DEV_TYPE_WM,                 //3 washing machine (dram?)
    DEV_TYPE_FR_RU60cm,          //4 Fridge russo 1
    DEV_TYPE_HO_Arcair,          //5 Hood Arcair (custom)
    DEV_TYPE_HO_Haier,           //6 Hood Haier
    DEV_TYPE_FR_MultiD_A3FE744,  //7 Fridge multidor 1
    DEV_TYPE_FR_MultiD_HB20,     //8 Fridge multidor 2
                                     
    DEV_TYPE_LAST

} DEV_TYPE;


typedef struct _alarm
{
    //int tag;
    char* name;
    int pos;
}   JSON_ALARM;


#define ERRBUFF_LEN     12

typedef struct _alarm_struct
{
    JSON_ALARM* alrm;
    int totAlarm;
    int dim;

    char name[30];
}   ALARM_ARRAY;


typedef struct _globalalrm_struct
{
    unsigned char ErrBuff[ERRBUFF_LEN];
    char err_present;
    char msg_sent;
    char msg_toSend;
    char ack_received;
    char F09_received;
    char err_zero;

    //MilliSecondOfTheYear
    __int64 Delay200ms;         //MilliSecondOfTheYear when starting
    __int64 Delay5sec;          //MilliSecondOfTheYear when starting
    // change?

}   ALARM_MESSAGE;


typedef struct _data_container
{
    DEV_TYPE type;				//incrementale! 0, 1, 2 etc. é un campo fisso! 
	unsigned char devName[50];
    //unsigned char status[];   Answ_014D01
    int status_len;     //StateMsgdim(x)
    int bigdata_len;
    char bigdata_present;
    char bigdata_answ;      //1 o 2? (inteso come risposta: 06 7D 01 oppure 06 7D 02
}   DEVICE_DATA;

//Functions
void StringInit(void);
void TypeID_init(DEV_TYPE dev);
unsigned char CalcCKS(const unsigned char* buf);
unsigned char CalcCKS2(unsigned char* buf, int* newlen);
//check chs in ricezione!
bool CheckCKSrx(const unsigned char* buf);
void UpdateLog(unsigned char *buf, int read, String note, int opt);
int UpdateAlrmMsg(unsigned char frame = 74);
int FindCmdIdx(int val);
int UpdateStateMsg(int val, char mode);

//variables...


//extern unsigned char ErrBuff[ERRBUFF_LEN];
extern ALARM_ARRAY   JsonALRM[];
extern ALARM_MESSAGE AlrmBuf;
extern unsigned char EncriptionSign[3];
//SoftAp Device name when in configuration mode
extern unsigned char TYPEID[];
extern unsigned char HW_SW_Version[];
extern unsigned char QueryAttrStatus[];
extern SERIAL_CMD    serial_cmd[];
extern DEVICE_DATA   Device[];

/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
// LEN = FF FF [2] len[1] {len-1}  CKS[1]
//                *-------------* = len!
// quindi lungh totale len (3° car) + 2xFF + 1CKS
// lunghezza totale: len + crc+ 2xFF = len+3!
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////


#define Answ_F2_LEN     (12+1)
extern unsigned char Answ_F2[];

#define Answ_62_LEN     (46+1)
extern unsigned char Answ_62[];

#define Answ_71_LEN     (42+1)
extern unsigned char Answ_71[];
extern String Answ71S;

/////////////////////////////////////////////
extern unsigned char ACK_5[];
extern unsigned char STOP_ALARM_9[];
extern unsigned char STATUS_INTERVAL_7C[];

#define Answ_73_LEN     (14+1)
extern unsigned char Answ_73[];

#define Answ_014D01_LEN     (40+1)
extern unsigned char Answ_014D01[];

extern unsigned char Answ_BigData[];

#define Answ_FC_LEN     (17+1)
extern unsigned char Answ_FC[];

#define ACK_5_LEN           (10+1)
#define STOP_ALARM_9_LEN    (10)
#define STATUS_INTERVAL_7C_LEN  (13)



#endif  //__DEFINE_H
