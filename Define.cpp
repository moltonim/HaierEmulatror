
#include <dateutils.hpp>
#include <string.h>
#include <stdio.h>

#include "AlarmPanel.h"
#include "Define.h"
#include "Unit1.h"

#include "DEF.h"


//////////////////////////////////////////////
ALARM_MESSAGE AlrmBuf;

//#define Answ_014D01_LEN     (42+1)
unsigned char Answ_014D01[100];

//#define Answ_62_LEN     (46+1)
unsigned char Answ_62[50];

//#define ANSW_70_LEN     (42+1)
unsigned char Answ_71_WC[50];
unsigned char Answ_71_WH[50];
unsigned char Answ_71_HVAC[50];
unsigned char Answ_71_HVAC2[50];
unsigned char Answ_71_WM[50];

unsigned char Answ_71_FR01[50];
unsigned char Answ_71_FRA3FE744[50];

unsigned char Answ_71_HO_ken1[50];
unsigned char Answ_71_HO_1[50];

unsigned char* answ71 = Answ_71_WC;     //default

//
String Answ71S = " {WC}";

//#define ANSW_73_LEN
unsigned char Answ_73[50];

//#define ANSW_F2_LEN
unsigned char Answ_F2[50];

//#define ANSW_FC_LEN
unsigned char Answ_FC[50];

int numOfAlarms[DEV_TYPE_LAST];

//Valutare se necessaria. Usare il num massimo di allarmi arrotondato al 32bit superiore
static int AlarmMsgByteDimension(DEV_TYPE val)
{
    switch (val)
    {
        case DEV_TYPE_WC:           return 8;      //WC
        case DEV_TYPE_WH:           return 2;      //WH  ??? 3??
        case DEV_TYPE_HVAC:         return 8;      //HVAC
        case DEV_TYPE_HVAC2:        return 10;     //HVAC type 2
        case DEV_TYPE_WM:           return 8;      //WM ???

        case DEV_TYPE_HO_Arcair:    // Hood Arcair
        case DEV_TYPE_HO_Haier:     // Hood Haier
                                    return 4;

        case DEV_TYPE_FR_RU60cm:
        case DEV_TYPE_FR_MultiD_HB20:
        case DEV_TYPE_FR_MultiD_A3FE744:
                                    return 8;      // FR FRA3FE744 & HB20 !

        default:                    break;
    }
    return 0;
}


static void VarsInit(void)
{
    int n;
    JSON_ALARM *ja;

    for (n = 0; n < DEV_TYPE_LAST; n++)
    {
        ja = JsonALRM[n].alrm;
        JsonALRM[n].dim = AlarmMsgByteDimension((DEV_TYPE)n);
        while (ja->pos != -1 )
        {
            numOfAlarms[n]++;       //to be removed!
            JsonALRM[n].totAlarm++;
            ja++;
        }
    }

    memset((char*)&AlrmBuf, 0, sizeof(AlrmBuf));
}


void StringInit(void)
{
    unsigned char *p;

    VarsInit();

    p = Answ_62;
    *p++ = 0xFF;
    *p++ = 0xFF;
    *p++ = 0x2C;    // FRAME LENGTH
    *p++ = 0;
    *p++ = 0;
    *p++ = 0;
    *p++ = 0;
    *p++ = 0;
    *p++ = 0;   //6th
    *p++ = 0x62;
    //memcpy((char*)&Answ_62[10],
    memcpy(p, DeviceProtocolVersion, 8);
    p += 8;
    memcpy(p, HW_SW_Version, 8);
    p += 8;
    //EncriptionSign
    *p++ = 0xF1;
    *p++ = 0;
    *p++ = 0;
    memcpy(p, HW_SW_Version, 8);
    p += 8;
    *p++ = 0;   //1 byte reserved
    memcpy(p, SoftApDeviceName_configMode_WC, 8);
    p += 8;
    *p++ = CalcCKS(Answ_62);

    ////////////////////////////////////////////////////

    p = Answ_71_WC;
    *p++ = 0xFF;
    *p++ = 0xFF;
    *p++ = 0x28;    // FRAME LENGTH
    *p++ = 0;
    *p++ = 0;
    *p++ = 0;
    *p++ = 0;
    *p++ = 0;
    *p++ = 0;   //6th
    *p++ = 0x71;
    memcpy(p, TYPEID_WC, 32);
    p += 32;
    *p++ = CalcCKS(Answ_71_WC);
    /////////
    p = Answ_71_WH;
    *p++ = 0xFF;
    *p++ = 0xFF;
    *p++ = 0x28;    // FRAME LENGTH
    *p++ = 0;
    *p++ = 0;
    *p++ = 0;
    *p++ = 0;
    *p++ = 0;
    *p++ = 0;   //6th
    *p++ = 0x71;
    memcpy(p, TYPEID_WH, 32);
    p += 32;
    *p++ = CalcCKS(Answ_71_WH);
    /////////
    p = Answ_71_FR01;
    *p++ = 0xFF;
    *p++ = 0xFF;
    *p++ = 0x28;    // FRAME LENGTH
    *p++ = 0;
    *p++ = 0;
    *p++ = 0;
    *p++ = 0;
    *p++ = 0;
    *p++ = 0;   //6th
    *p++ = 0x71;
    memcpy(p, TYPEID_FR01, 32);
    p += 32;
    *p++ = CalcCKS(Answ_71_FR01);
    /////////
    p = Answ_71_FRA3FE744;
    *p++ = 0xFF;
    *p++ = 0xFF;
    *p++ = 0x28;    // FRAME LENGTH
    *p++ = 0;
    *p++ = 0;
    *p++ = 0;
    *p++ = 0;
    *p++ = 0;
    *p++ = 0;   //6th
    *p++ = 0x71;
    memcpy(p, TYPEID_FRA3FE744, 32);
    p += 32;
    *p++ = CalcCKS(Answ_71_FRA3FE744);
    /////////

    p = Answ_71_WM;
    *p++ = 0xFF;
    *p++ = 0xFF;
    *p++ = 0x28;    // FRAME LENGTH
    *p++ = 0;
    *p++ = 0;
    *p++ = 0;
    *p++ = 0;
    *p++ = 0;
    *p++ = 0;   //6th
    *p++ = 0x71;
    memcpy(p, TYPEID_WM, 32);
    p += 32;
    *p++ = CalcCKS(Answ_71_WM);
    /////////
    p = Answ_71_HO_ken1;
    *p++ = 0xFF;
    *p++ = 0xFF;
    *p++ = 0x28;    // FRAME LENGTH
    *p++ = 0;
    *p++ = 0;
    *p++ = 0;
    *p++ = 0;
    *p++ = 0;
    *p++ = 0;   //6th
    *p++ = 0x71;
    memcpy(p, TYPEID_HO_ken1, 32);
    p += 32;
    *p++ = CalcCKS(Answ_71_HO_ken1);

    p = Answ_71_HO_1;
    *p++ = 0xFF;
    *p++ = 0xFF;
    *p++ = 0x28;    // FRAME LENGTH
    *p++ = 0;
    *p++ = 0;
    *p++ = 0;
    *p++ = 0;
    *p++ = 0;
    *p++ = 0;   //6th
    *p++ = 0x71;
    memcpy(p, TYPEID_HO_1, 32);
    p += 32;
    *p++ = CalcCKS(Answ_71_HO_1);

    /////////
    p = Answ_71_HVAC;
    *p++ = 0xFF;
    *p++ = 0xFF;
    *p++ = 0x28;    // FRAME LENGTH
    *p++ = 0;
    *p++ = 0;
    *p++ = 0;
    *p++ = 0;
    *p++ = 0;
    *p++ = 0;   //6th
    *p++ = 0x71;
    memcpy(p, TYPEID_HVAC, 32);
    p += 32;
    *p++ = CalcCKS(Answ_71_HVAC);

    /////////
    p = Answ_71_HVAC2;
    *p++ = 0xFF;
    *p++ = 0xFF;
    *p++ = 0x28;    // FRAME LENGTH
    *p++ = 0;
    *p++ = 0;
    *p++ = 0;
    *p++ = 0;
    *p++ = 0;
    *p++ = 0;   //6th
    *p++ = 0x71;
    memcpy(p, TYPEID_HVAC2, 32);
    p += 32;
    *p++ = CalcCKS(Answ_71_HVAC2);

    p = Answ_F2;
    *p++ = 0xFF;
    *p++ = 0xFF;
    *p++ = 0x0A;    // FRAME LENGTH
    *p++ = 0;
    *p++ = 0;
    *p++ = 0;
    *p++ = 0;
    *p++ = 0;
    *p++ = 0;   //6th
    *p++ = 0xF2;
    *p++ = 0;   //6th
    *p++ = 0;   //6th
    *p++ = CalcCKS(Answ_F2);

    p = Answ_73;
    *p++ = 0xFF;
    *p++ = 0xFF;
    *p++ = 12;    // FRAME LENGTH
    *p++ = 0;
    *p++ = 0;
    *p++ = 0;
    *p++ = 0;
    *p++ = 0;
    *p++ = 0;   //6th
    *p++ = 0x74;
    *p++ = 0x0F;
    *p++ = 0x5A;
    *p++ = 0;
    *p++ = 0;
    *p++ = CalcCKS(Answ_73);

    p = Answ_014D01;
    *p++ = 0xFF;
    *p++ = 0xFF;
    *p++ = 38;    // FRAME LENGTH
    *p++ = 0;
    *p++ = 0;
    *p++ = 0;
    *p++ = 0;
    *p++ = 0;
    *p++ = 0;   //6th
    *p++ = 0x02;
    *p++ = 0x6D;
    *p++ = 0x01;
    for(int n = 0; n < 28; n++)
        *p++ = n+1;
    *p++ = CalcCKS(Answ_014D01);


    p = Answ_FC;
    *p++ = 0xFF;
    *p++ = 0xFF;
    *p++ = 14;    // FRAME LENGTH
    *p++ = 0;
    *p++ = 0;
    *p++ = 0;
    *p++ = 0;
    *p++ = 0;
    *p++ = 0;   //6th
    *p++ = 0xFC;
    *p++ = 0;
    *p++ = 0;
    *p++ = 0;
    *p++ = 0;
    *p++ = 0;
    *p++ = 0;   //6th
    *p++ = CalcCKS(Answ_FC);
}


unsigned char CalcCKS(const unsigned char* buf)
{
    unsigned char val = 0;
    int n, len;
    unsigned char* p;

    p = (unsigned char*)buf;
    p += 2;
    len = *p;   //len include the ks

    for(n = 0; n < len; n++)
        val += *p++;

    return val;
}


unsigned char CalcCKS2(unsigned char* buf, int* newlen)
{
    unsigned char val = 0;
    int n, len;
    int delta;
    unsigned char c;
    unsigned char* p;

    p  = (unsigned char*)buf;
    p += 2;         //Jump the 0xFFFF header
    len  = *p;      //len include the cks
    
    for(n = 0; n < len; n++)
    {
        c = *p;
        val += c;
        if (c == 0xFF)
        {
            delta = len-n+1;
            memmove(p+1, p, delta);
            *(p+1) = 0x55;
            len++;
        }
        p++;
    }
    *newlen = len;
    return val;
}

//
bool CheckCKSrx(const unsigned char* buf)
{
    unsigned char val = 0;
    int n, len;
    bool b = false;
    unsigned char c;
    unsigned char* p;

    p  = (unsigned char*)buf;
    p += 2;         //Jump the 0xFFFF header
    len  = *p;      //len include the cks

    for(n = 0; n < len; n++)
    {
        c = *p;
        val += c;
        if (c == 0xFF)
        {
            len++;
        }
        p++;
    }
    b = (val == *p);

    return b;
}


//static int arcLen = 12;
static int StateMsgdim(DEV_TYPE val)
{
    switch (val)
    {
        case DEV_TYPE_WC:           return 28;      //WC
        case DEV_TYPE_WH:           return 50;      //WH
        case DEV_TYPE_HVAC:         return 32;      //HVAC
        case DEV_TYPE_HVAC2:        return 40;      //HVAC2
        case DEV_TYPE_WM:           return 23*2;    //WM ???
        case DEV_TYPE_FR_RU60cm:    return 28;      //FR01 RU 60cm ?
        case DEV_TYPE_HO_Arcair:    return 12;      // Hood Arcair
        case DEV_TYPE_HO_Haier:     return 15;      // Hood Haier

        case DEV_TYPE_FR_MultiD_HB20:
        case DEV_TYPE_FR_MultiD_A3FE744:
                                    return 28;      // FR FRA3FE744 & HB20 !

        default:                    break;
    }
    return 0;
}

int UpdateAlrmMsg(unsigned char frame)
{
    int device = Form1->DeviceComboBox->ItemIndex;
    int len = JsonALRM[device].dim;  //JsonALRM[device].totAlarm;
    unsigned char* p;

    p = Answ_73;
    *p++ = 0xFF;
    *p++ = 0xFF;
    *p++ = 8 + 2 + len;    // FRAME LENGTH
    *p++ = 0;
    *p++ = 0;
    *p++ = 0;
    *p++ = 0;
    *p++ = 0;
    *p++ = 0;   //6th
    *p++ = frame;
    *p++ = 0x0F;
    *p++ = 0x5A;
    for(int n = len-1; n >= 0; n--)
        *p++ = AlrmBuf.ErrBuff[n];
    len += 8;
    unsigned char c = CalcCKS2(Answ_73, &len);
    len += 2;     //add 0xFF, 0xFF as header
    p = Answ_73 + len;
    *p++ = c;
    len = p - Answ_73;
    return len;
}


char arcBuf[14] = {
    0,   //bit                  0
    1,   //windSpeed            1

    2,   //delaytime            2
    3,   //                     3

    4,  //machMode              4
    5,  //                      5

    6,  //rgbLightStatus        6
    7,  //rgbLightColor         7

    8,  //lastWorkTime          8
    9,  //lastWorkTime          9

    10, //lastWorkTime          10
    11, //lastWorkTime          11

    12, //                      12
    13, //                      13
    };
//
//  mode: se 0 = risposta al comando tipo 1, 9° carattere = 2
//           1 = invio spontaneo           , 9° carattere = 6
//
int UpdateStateMsg(int val, char mode)
{
    if (val < 0)
        return 0;

    static int st = 1;

    int n;
    unsigned char *p = Answ_014D01;
    static unsigned short Temperature[10];
    static unsigned char flagByte;
    static int oldval = -1;
    int len = StateMsgdim((DEV_TYPE)val);

    if (val != oldval)
    {
        memset((char*)&Temperature[0], 0, sizeof(Temperature));
        oldval = val;
    }

    p = Answ_014D01;
    *p++ = 0xFF;
    *p++ = 0xFF;
    *p++ = len+10;    // FRAME LENGTH
    *p++ = 0;
    *p++ = 0;
    *p++ = 0;
    *p++ = 0;
    *p++ = 0;
    *p++ = 0;   //6th
    *p++ = mode? 0x06:0x02;
    *p++ = 0x6D;
    *p++ = 0x01;
    for(int n = 0; n < len; n++)     //
        *p++ = 0;

    //*p++ = CalcCKS(Answ_014D01);

    len = p - Answ_014D01;     //debug purp also!
    Answ_014D01[2] = StateMsgdim((DEV_TYPE)val)+10;
    p = Answ_014D01;    //restart!!
    p += 12;            //Point to Byte index1

    switch (val)
    {
        case DEV_TYPE_WC:     // WC = Wine cooler, cantinetta
            //p += 12;    //Point to Byte index1: Upper temperature zone
            Temperature[0] %= 0xA0;
            *p = Temperature[0]++;
            p++;
            Temperature[1] %= 0xA0;
            *p = Temperature[1]++;
            p += 3;
            Temperature[2] %= 0xA0;
            *p = Temperature[2]++;
            p++;
            Temperature[3] %= 0x64;
            *p = Temperature[3]++;
            p++;
            Temperature[4] %= 0x1B;
            *p = Temperature[4]++;
            p++;
            Temperature[5] %= 0x1B;
            *p = Temperature[5]++;
            p = Answ_014D01 + 12+14;    //status byte
            flagByte ^= 0x60;
            *p = flagByte;              //toggle Power and light
            Answ_014D01[12+9] = 1;      //upperboxwinemode
            Answ_014D01[12+11] = 1;     //lowerboxwinemode

            //p = Answ_014D01 + len;
            //*p++ = CalcCKS(Answ_014D01);
            //len++;
        break;

        case DEV_TYPE_WH:     // WH = water heater, scaldabagno
            //p += 12;    //Point to Byte index1: Upper temperature zone
            Temperature[0] %= 0x6E;
            *p = Temperature[0]++;
            p++;
            Temperature[1] %= 0x37;
            *p = Temperature[1]++;
            p += 9;
            Temperature[2] %= 0xFE;
            *p = Temperature[2]++;
            p++;
            Temperature[3] %= 0x6E;
            *p = Temperature[3]++;
            p++;
            Temperature[4] %= 0x6E;
            *p = Temperature[4]++;
            p++;
            Temperature[5] %= 0x6E;
            *p = Temperature[5]++;
            p = Answ_014D01 + 12+36;   //status byte
            flagByte ^= 0x7F;
            *p = flagByte;             //toggle Power and light

            //p = Answ_014D01 + len;
            //*p++ = CalcCKS(Answ_014D01);
            //len++;
        break;

        case DEV_TYPE_HVAC:     // HVAC
            //p += 12;    //Point to Byte index1: Upper temperature zone
            p += st;
            p = Answ_014D01 + 12;           //restart!!
            Answ_014D01[14] = 1;    //windSpeed [4]
            Answ_014D01[26] = 1;    //errCode [38]
            Temperature[0] %= 0x0E;
            *p = Temperature[0]++;
            p += 4;
            Temperature[1] %= 0xFE;
            *p = Temperature[1]++;
            p++;
            flagByte ^= 0x3F;
            *p = flagByte;             //toggle Power and light
            p++;
            Temperature[2] ^= 0xFF;
            *p = Temperature[2];
            p++;    //p = 5!
            Temperature[3] %= 0x3C;
            *p = Temperature[3]++;

            //p = Answ_014D01 + len;
            //*p++ = CalcCKS(Answ_014D01);
            //len++;
        break;

        case DEV_TYPE_HVAC2:     // HVAC
            //p += 12;    //Point to Byte index1: Upper temperature zone
            p += st;
            p = Answ_014D01 + 12;           //restart!!
            Answ_014D01[14] = 1;    //windSpeed [4]
            Answ_014D01[26] = 1;    //errCode [38]
            Temperature[0] %= 0x0E;
            *p = Temperature[0]++;
            p += 4;
            Temperature[1] %= 0xFE;
            *p = Temperature[1]++;
            p++;
            flagByte ^= 0x3F;
            *p = flagByte;             //toggle Power and light
            p++;
            Temperature[2] ^= 0xFF;
            *p = Temperature[2];
            p++;    //p = 5!
            Temperature[3] %= 0x3C;
            *p = Temperature[3]++;
        break;

        case DEV_TYPE_WM:     // WM  lavatrice
            //p += 12;    //Point to Byte index1: Upper temperature zone
            Temperature[0] %= 13;
            *p = Temperature[0]++;
            p++;
            Temperature[1] %= 70;
            *p = Temperature[1]++;
            p++;
            flagByte ^= 0x3F;
            *p = flagByte;             //toggle Power and light
            p++;
            if (Temperature[2] == 0)
                Temperature[2]  = 1;
            Temperature[2] <<= 1;     //ci sono tutti!
            *p = (Temperature[2]>>8)&0xFF;
            p++;
            *p = Temperature[2]&0xFF;

            //p = Answ_014D01 + len;
            //*p++ = CalcCKS(Answ_014D01);
            //len++;
        break;

        case DEV_TYPE_FR_RU60cm:     // FR01: Fridge, RU60cm
            //p += 12;    //Point to Byte index1: Upper temperature zone
            Temperature[0] %= 85;       //0 means -38
            *p = Temperature[0]++;
            p++;
            Temperature[1] %= 85;       //0 means -38
            *p = Temperature[1]++;
            p += 3;
            *p = Temperature[2]++;      //0 means -38

            //p = Answ_014D01 + len;
            //*p++ = CalcCKS(Answ_014D01);
            //len++;
        break;

        case DEV_TYPE_HO_Arcair:     // Hood Arcair
            //p += 12;    //Point to Byte index1: OnOff Status etc.
            //p += 4;     //Point to Byte index1:
            for(n = 0; n < len; n++)
                *p++ = arcBuf[n];
            p = Answ_014D01 + 12 + 2;
            Temperature[0] %= 100;
            *p = Temperature[0]++;

            /*if (0)
            {
                p = Answ_014D01 + len;
                *p++ = CalcCKS(Answ_014D01);
            }
            else if (0)
            {
                c = CalcCKS2(Answ_014D01, &len);
                len += 2;     //add 0xFF, 0xFF as header
                p = Answ_014D01 + len;
                *p = c;
            }*/
            //len++;
        break;

        case DEV_TYPE_HO_Haier:     // Hood Haier
        default:
            len = -1;
        break;

        case DEV_TYPE_FR_MultiD_A3FE744:
        case DEV_TYPE_FR_MultiD_HB20:
            //p += 12;    //Point to Byte index1: OnOff Status etc.
            Temperature[0] %= 58;       //0 means -38
            *p = Temperature[0]++;
            
            //p = Answ_014D01 + len;
            //*p++ = CalcCKS(Answ_014D01);
            //len++;
        break;
    }
    unsigned char c = CalcCKS2(Answ_014D01, &len);
    len += 2;     //add 0xFF, 0xFF as header
    p = Answ_014D01 + len;
    *p = c;

    return ++len;
}


int FindCmdIdx(int val)
{
    int cmd = -1;
    int n = 0;
    while(serial_cmd[n].val)
    {
        if (serial_cmd[n].val == val)
        {
            cmd = n;
            break;
        }
        n++;
    }
    return cmd;
}


void UpdateLog(unsigned char *buf, int read, String note, int opt)
{
    if (!Form1->WriteLogPopMnu->Checked)
        return;

    String s = ExtractFilePath( Application->ExeName );
    String s2;
    int n, len;
    unsigned char* p = buf;

    unsigned short y, m, d, h, mm, ss, msec;
    DecodeDateTime(Now(), y, m, d, h, mm, ss, msec);

    s2.sprintf("%02d_%02d_%02d-%02d", y, m, d, h);
    s += s2+".log";

    int hh;
    if (!FileExists(s))
        hh = FileCreate(s);
    else
        hh = FileOpen(s, fmOpenWrite);
    
    FileSeek(hh, 0, 2);
    DecodeDateTime(Now(), y, m, d, h, mm, ss, msec);
    s2.sprintf("%02d:%02d:%02d.%03d ", h,mm,ss,msec );
    s = s2; //init here!

    if (note != "")
    {
        s += note + "\n";
        FileWrite(hh, s.c_str(), s.Length());
        if (buf == NULL)
        {
            FileClose(hh);
            return;
        }
    }

    if (read == 'r' || read == 'R')
    {
        s += "R";
    }
    else
    {
        s += "W";
    }
    s += " => ";
    len = opt;
    for (n = 0; n < len; n++)
        s += IntToHex((unsigned char)(*p++), 2) + " ";

    s += "\n";
    FileWrite(hh, s.c_str(), s.Length());
    FileClose(hh); 
}
