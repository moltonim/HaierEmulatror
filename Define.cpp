
#include <dateutils.hpp>
#include <string.h>
#include <stdio.h>

#include "Define.h"
#include "Unit1.h"


SERIAL_CMD serial_cmd[] = {
	{ 0x01,	"01 Control or setting"									 },
	{ 0x02,	"02 Status return"                                          },
	{ 0x03,	"03 Invalid command"                                        },
	{ 0x04,	"04 Alarm status report"                                    },
	{ 0x05,	"05 ACK"                                                    },
	{ 0x06,	"06 Status report"                                          },
	{ 0x09,	"09 Stop fault alarm frame"                                 },
	{ 0x60,	"60 Group command"                                          },
	{ 0x61,	"61 Device version query"                                   },
	{ 0x62,	"62 Device version response"                                },
	{ 0x63,	"63 Get the key"                                            },
	{ 0x64,	"64 Set encryption parameters"                              },
	{ 0x70,	"70 Device ID query"                                        },
	{ 0x71,	"71 Device ID response"                                     },
	{ 0x73,	"73 Query alarm status"                                     },
	{ 0x74,	"74 Query alarm response"                                   },
	{ 0x7C,	"7C Device report config frame"                             },
	{ 0x7D,	"7D Device report config response frame"                    },
	{ 0xF2,	"F2 Module enters config mode"                              },
	{ 0xF3,	"F3 Module enters config mode response"                     },
	{ 0xF4,	"F4 Module enters working mode"                             },
	{ 0xF5,	"F5 Module enters working mode response"                    },
	{ 0xF7,	"F7 Actively report network status"                         },
	{ 0xF8,	"F8 Module clear configuration information command"         },
	{ 0xF9,	"F9 Module enters production test mode"                     },
	{ 0xFA,	"FA Device big data report config"                          },
	{ 0xFB,	"FB Device big data report config resp"                     },
    { 0xFC,	"FC Query management info"                                  },
    { 0xFD,	"FD Query management info response"                         },
    {    0, "" },
};

JSON_ALARM ALARM_WH[] = {
	{ "middleTempSensorErr", 		0 },
	{ "dryHeatingAlarm", 			1 },
	{ "leakageAlarm", 				2 },
	{ "upperTempSensorErr", 		3 },
	{ "lowerTempSensorErr", 		4 },
	{ "middleUpperTempSensorErr", 	5 },
	{ "communicationErr", 			6 },
	{ "relayErr", 					7 },
	{ "inWaterTempSensorErr", 		8 },
	{ "thermostaticValveColdWaterSensorErr", 	9 },
	{ "thermostaticValveHotWaterSensorErr", 	10 },
	{ "thermostaticValveCommunicationErr", 		11 },
	{ "stepMotorErr", 				12 },
	{ "filterErr", 					13 },
	{ "middleLowerTempSensorErr", 	14 },
	{ "fireWallTempSensorErr", 		15 },
    { "", -1}
};

JSON_ALARM ALARM_WC[] = {
	{ "upperBoxTempSensorErr", 	1  },
	{ "lowerBoxTempSensorErr", 	3  },
	{ "doorAlarm", 				30 },
	{ "doorErr", 				33 },
	{ "upperBoxLowTempAlarm", 	44 },
	{ "upperBoxHighTempAlarm", 	45 },
	{ "lowerBoxLowTempAlarm", 	48 },
	{ "lowerBoxHighTempAlarm", 	49 },
    { "", -1}
};

JSON_ALARM ALARM_WM[] = {
	{ "fanErr", 					2 },
	{ "waterHeatingErr", 			3 },
	{ "hallErr", 					4 },
	{ "rpmErr", 					5 },
	{ "voltageHighAlarm", 			6 },
	{ "voltageLowAlarm", 			7 },
	{ "dataBackup1", 				8 },	
	{ "ddMotorNTCErr", 				9 },
	{ "motorStatorHighTempProtection", 	10 },
	{ "currentSensingCircuitErr", 	11 },
	{ "overcurrentAlarm", 			12 },
	{ "ipmErr", 					13 },
	{ "phaseBreakProtection", 		14 },
	{ "launchFailed", 				15 },
	{ "noPowerOnSignal", 			16 },
	{ "heaterRelayErr", 			17 },
	{ "heaterErr", 					18 },
	{ "tempSensorErr", 				19 },
	{ "inAirSensorErr", 			20 },
	{ "condenserSensorErr", 		21 },
	{ "doorLockFail", 				22 },
	{ "doorUnlockFail", 			23 },
	{ "motorDriverCommErr", 		24 },
	{ "powerDriverCommErr", 		25 },
	{ "displayBoardCommErr", 		26 },
	{ "mainRelayAdhesion", 			27 },
	{ "waterLevelSensorErr", 		28 },
	{ "inWaterErr", 				29 },
	{ "drainErr", 					30 },
	{ "waterOverHighAlarm", 		31 },
	{ "dryWaterLevelAlarm", 		32 },
	{ "dryHeatingAlarm", 			33 },
	{ "waterOverLowAlarm", 			34 },
	{ "waterLevelAlarm", 			35 },
	{ "spinUnbalanceAlarm", 		36 },
	{ "weightErr", 					37 },
	{ "dryOverweightAlarm", 		38 },
	{ "mainEEPROMErr", 				39 },
	{ "tempOverHighAlarm", 			40 },
	{ "otherAlarm", 				41 },
	{ "washFinishAlarm", 			42 },
	{ "dryDriverCommErr",	 		43 },
	{ "waterLeakageAlarm", 			44 },
	{ "purificationReductionWarning", 	45 },
	{ "purificationReductionAlarm", 46 },
	{ "purificationDriverCommErr", 	47 },
	{ "muCommErr", 					48 },
	{ "busCommErr", 				49 },
	{ "wpCommErr", 					50 },
	{ "clutchMotorErr", 			51 },
	{ "swSelfTestErr", 				52 },
	{ "autoFlowmeterErr",	 		53 },
	{ "fanDriverCommErr", 			54 },
	{ "rfidCommErr",		 		55 },
	{ "proxSensorErr",	 			60 },
	{ "wifiCfgFailed", 				61 },
	{ "wallLimitSwitchAlarm", 		62 },
    { "", -1}
};

JSON_ALARM ALARM_HVAC[] = {
	{ "outdoorModuleErr", 			0 },
	{ "outdoorDeforstSensorErr", 	1 },
	{ "outdoorExhaustSensorErr", 	2 },
	{ "outdoorEEPROMErr", 			3 },
	{ "indoorCoilerSensorErr", 		4 },
	{ "indoorOutdoorCommErr",	 	5 },
	{ "powerProtection", 			6 },
	{ "panelCommErr", 				7 },
	{ "outdoorCompressorOverheatProtection", 	8 },
	{ "outdoorEnviSensorErr", 		9 },
	{ "fullWaterProtection", 		10 },
	{ "indoorEEPROMErr", 			11 },
	{ "outdoorReturnAirSensorErr", 	12 },
	{ "cbdCommErr", 				13 },
	{ "indoorFanErr", 				14 },
	{ "outdoorFanErr", 				15 },
	{ "doorErr", 					16 },
	{ "filterCleaningAlarm",	 	17 },
	{ "waterLackProtection", 		18 },
	{ "humiditySensorErr", 			19 },
	{ "indoorTempSensorErr", 		20 },
	{ "mechanicalArmLimitErr", 		21 },
	{ "indoorPM2p5SensorErr",	 	22 },
	{ "outdoorPM2p5SensorErr", 		23 },
	{ "indoorHeatingOverloadAlarm", 24 },
	{ "outdoorACProtection", 		25 },
	{ "outdoorCompressorRunningErr",26 },
	{ "outdoorDCProtection", 		27 },
	{ "outdoorUnloadedErr", 		28 },
	{ "ctCurrentErr", 				29 },
	{ "indoorFreezingProtection", 	30 },
	{ "pressureProtection", 		31 },
	{ "returnAirOverheatAlarm", 	32 },
	{ "outdoorEvaporationSensorErr",33 },
	{ "outdoorCoolingOverloadAlarm",34 },
	{ "waterPumpErr", 				35 },
	{ "threePhaseSupplyErr", 		36 },
	{ "fourWayValveErr", 			37 },
	{ "externalAlarmSwitchErr", 	38 },
	{ "tempCuttingOffProtection", 	39 },
	{ "differentModeRunningErr", 	40 },
	{ "expansionValveErr", 			41 },
	{ "twErr", 						42 },
	{ "wireCtrCommErr", 			43 },
	{ "indoorUnitIdConflictErr", 	44 },
	{ "zeroPassageErr", 			45 },
	{ "outdoorUnitErr", 			46 },
	{ "ch2oSensorErr",			 	47 },
	{ "vocSensorErr", 				48 },
	{ "co2SensorErr", 				49 },
	{ "firewallErr", 				50 },
    { "", -1}
};


JSON_ALARM ALARM_FR_RU60cm[] = {
	{ "envTempSensorErr", 			0 },
	{ "refrigeratorSensorErr", 		1 },
	{ "freezerSensorErr", 			3 },
	{ "freezerDefrostingSensorErr", 8 },
	{ "ctrBoardCommErr", 			10 },
	{ "freezerFanErr", 				12 },
	{ "freezerDefrostingErr", 		14 },
	{ "wifiCommunicationErr", 		51 },
    { "", -1}
};

JSON_ALARM ALARM_HO_Arcair[] = {
	{ "scDryHeatingAlarm", 			0 },
	{ "scTempSensorErr", 			1 },
	{ "scHeaterErr", 				2 },
	{ "scMotorLacunarityErr", 		3 },
	{ "scMotorOvervoltageErr", 		4 },
	{ "scMotorOvercurrentErr", 		5 },
	{ "scMotorOverheatErr", 		6 },
	{ "scMotorUndervoltageErr", 	7 },
	{ "communicationErr", 			8 },
	{ "linkageModuleErr", 			9 },
	{ "bluetoothModuleErr", 		10 },
	{ "voiceModuleErr", 			11 },
	{ "gestureModuleErr", 			12 },
	{ "windCurtainModuleErr", 		13 },
	{ "anionModuleErr", 			14 },
	{ "smartWindModuleErr", 		15 },
	{ "airCleaningModuleErr", 		16 },
	{ "humanSensingModuleErr", 		17 },
	{ "windPressureSensorErr", 		18 },
	{ "sceneLightErr", 				19 },
    { "", -1}
};

JSON_ALARM ALARM_HO_Haier[] = {
	{ "scDryHeatingAlarm", 			0 },
	{ "scTempSensorErr", 			1 },
	{ "scHeaterErr", 				2 },
	{ "scMotorLacunarityErr", 		3 },
	{ "scMotorOvervoltageErr", 		4 },
	{ "scMotorOvercurrentErr", 		5 },
	{ "scMotorOverheatErr", 		6 },
	{ "scMotorUndervoltageErr", 	7 },
	{ "communicationErr", 			8 },
	{ "linkageModuleErr", 			9 },
	{ "bluetoothModuleErr", 		10 },
	{ "voiceModuleErr", 			11 },
	{ "gestureModuleErr", 			12 },
	{ "windCurtainModuleErr", 		13 },
	{ "anionModuleErr", 			14 },
	{ "smartWindModuleErr", 		15 },
	{ "airCleaningModuleErr", 		16 },
	{ "humanSensingModuleErr", 		17 },
	{ "windPressureSensorErr", 		18 },
	{ "sceneLightErr", 				19 },
    { "", -1}
};

JSON_ALARM ALARM_HB20[] = {
	{ "envTempSensorErr", 			0 },
	{ "refrigeratorSensorErr", 		1 },
	{ "freezerSensorErr", 			3 },
	{ "vtRoomSensorErr", 			4 },
	{ "freezerDefrostingSensorErr", 8 },
	{ "ctrBoardCommErr", 			10 },
	{ "freezerFanErr", 				12 },
	{ "freezerDefrostingErr", 		14 },
	{ "humiditySensorErr", 			15 },
	{ "refrigeratorDoorAlarm", 		30 },
	{ "airDoor1Err", 				45 },
    { "", -1}
};

JSON_ALARM ALARM_FRA3FE744[] = {
	{ "envTempSensorErr", 			0 },
	{ "refrigeratorSensorErr", 		1 },
	{ "freezerSensorErr", 			3 },
	{ "vtRoomSensorErr", 			4 },
	{ "freezerDefrostingSensorErr", 8 },
	{ "ctrBoardCommErr", 			10 },
	{ "freezerFanErr", 				12 },
	{ "humiditySensorErr", 			15 },
	{ "refrigeratorDoorAlarm", 		30 },
	{ "airDoor1Err", 				45 },
    { "", -1}
};

//////////////////////////////////////////////

ALARM_ARRAY JsonALRM[] = {
    { ALARM_WC          , 0, 0, "Wine Cooler" },
    { ALARM_WH          , 0, 0, "Water Heater" },
    { ALARM_HVAC        , 0, 0, "Air conditioning HVAC" },
    { ALARM_WM			, 0, 0, "Drum washing machine" },
    { ALARM_FR_RU60cm	, 0, 0, "Fridge RU 60cm" },
    { ALARM_HO_Arcair   , 0, 0, "Hood Arcair" },
    { ALARM_HO_Haier    , 0, 0, "Hood Haier" },
    { ALARM_FRA3FE744   , 0, 0, "Multidoor 982k A3FE744" },
    { ALARM_HB20        , 0, 0, "Multidoor 982J HB20" },

	{NULL, 0, 0, ""}
};


//not used yet
static SERIAL_CMD Device_status[] = {
    {0x01, "SoftAP configuration mode"      },
    {0x02, "Smartlink configuration mode"   },
    {0x03, "WPS configuration mode"         },
    {0x04, "BT configuration mode"          },
    {   0, "" },
};


unsigned char DeviceProtocolVersion[8] = {
    0x45, 0x2B, 0x2B, 0x32, 0x2E, 0x31, 0x37, 0x00
    };

unsigned char EncriptionSign[3] = {
    0xF1, 0x00, 0x00
    };

//SoftAp Device name when in configuration mode
unsigned char SoftApDeviceName_configMode_WC[8] = {
    0x55, 0x2D, 0x43, 0x45, 0x4C, 0x4C, 0x00, 0x00
    };

unsigned char SoftApDeviceName_configMode_WH[8] = {
    0x55, 0x2D, 0x45, 0x57, 0x48, 0x00, 0x00, 0x00
    };

unsigned char SoftApDeviceName_configMode_HVAC[8] = {
    0x55, 0x2D, 0x41, 0x43, 0x00, 0x00, 0x00, 0x00
    };

static unsigned char TYPEID_WC[32] = {
    0x20, 0x08, 0x61, 0x05, 0x1c, 0x40, 0x85, 0x04,
    0x08, 0x12, 0x00, 0x71, 0x80, 0x01, 0x32, 0x42,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x71, 0x80,
    0x02, 0x23, 0xa0, 0x00, 0x00, 0x00, 0x00, 0x40,
    };

static unsigned char TYPEID_WH[32] = {
    0x20, 0x1c, 0x12, 0x00, 0x00, 0x11, 0x86, 0x74,
    0x06, 0x16, 0x00, 0x41, 0x80, 0x07, 0x23, 0x41,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40,
    };

static unsigned char TYPEID_HVAC[32] = {
    0x20, 0x08, 0x61, 0x08, 0x00, 0x82, 0x03, 0x24,
    0x02, 0x12, 0x00, 0x11, 0x80, 0x09, 0x09, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40,
    };

static unsigned char TYPEID_HO_ken1[32] = {
    0x20, 0x1c, 0x10, 0xc7, 0x14, 0x12, 0x02, 0x10,
    0x09, 0x01, 0x37, 0x7a, 0x39, 0x98, 0x79, 0x00,
    0x00, 0x00, 0x41, 0x72, 0x63, 0x61, 0x69, 0x72,
    0x48, 0x64, 0x04, 0x64, 0x45, 0x00, 0x00, 0x40,
    };

static unsigned char TYPEID_HO_1[32] = {
    0x20, 0x1c, 0x10, 0xc7, 0x14, 0x12, 0x02, 0x10,
    0x09, 0x01, 0x37, 0x7a, 0x39, 0x98, 0x79, 0x00,
    0x00, 0x00, 0xfb, 0x0f, 0x11, 0x4f, 0xd0, 0xf0,
    0xee, 0xc4, 0x1b, 0x63, 0x51, 0xc1, 0x63, 0x40,
    };

static unsigned char TYPEID_WM[32] = {
    0x20, 0x1c, 0x51, 0x89, 0x0c, 0x31, 0xc3, 0x08,
    0x05, 0x01, 0x00, 0x21, 0x80, 0x00, 0x67, 0x4b,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40,
    };

static unsigned char TYPEID_FR01[32] = {   //Fridge: RU 60cm
    0x20, 0x08, 0x61, 0x05, 0x1c, 0x40, 0x85, 0x04,
    0x01, 0x24, 0x00, 0x61, 0x80, 0x06, 0x98, 0x55,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x61, 0x80,
    0x03, 0x12, 0x55, 0x00, 0x00, 0x00, 0x00, 0x40,
    };

static unsigned char TYPEID_FRA3FE744[32] = {
    0x20, 0x08, 0x61, 0x05, 0x1c, 0x40, 0x85, 0x04, 
    0x01, 0x21, 0x00, 0x61, 0x80, 0x09, 0x82, 0x4b,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x61, 0x80,
    0x03, 0x51, 0x52, 0x00, 0x00, 0x00, 0x00, 0x40,
    };

static unsigned char TYPEID_HB20[32] = {
    0x20, 0x08, 0x61, 0x05, 0x1c, 0x40, 0x85, 0x04, 
    0x01, 0x21, 0x00, 0x61, 0x80, 0x09, 0x82, 0x4a,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x61, 0x80,
    0x03, 0x51, 0x51, 0x00, 0x00, 0x00, 0x00, 0x40,
    };

/*   //esempio risposta sniffata dalla WM
ff ff 28 00 00 00 00 00 00 71 20 1c 51 89 0c 31
c3 08 05 01 00 21 80 00 67 4b 00 00 00 00 00 00
00 00 00 00 00 00 00 00 00 40 50
*/


unsigned char HW_SW_Version[8] = {
    0x32, 0x30, 0x31, 0x38, 0x30, 0x39, 0x30, 0x35,
    };

unsigned char ACK_5[11] = {
    0xFF, 0xFF, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x0d
    };

//#define Answ_014D01_LEN     (42+1)
unsigned char Answ_014D01[100];

//#define Answ_62_LEN     (46+1)
unsigned char Answ_62[50];

//#define ANSW_70_LEN     (42+1)
unsigned char Answ_71_WC[50];
unsigned char Answ_71_WH[50];
unsigned char Answ_71_HVAC[50];
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
        case DEV_TYPE_WH:           return 4;      //WH  ??? 3??
        case DEV_TYPE_HVAC:         return 8;      //HVAC
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
