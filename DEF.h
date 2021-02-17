#ifndef __DEF_H_
#define __DEF_H_


unsigned char SoftApDeviceName_configMode_WC[8] = {
    0x55, 0x2D, 0x43, 0x45, 0x4C, 0x4C, 0x00, 0x00
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


JSON_ALARM ALARM_HVAC2[] = {
    { "outdoorModuleErr", 			0 },
	{ "outdoorDeforstSensorErr", 	1 },
	{ "outdoorExhaustSensorErr", 	2 },
	{ "outdoorEEPROMErr", 			3 },
	{ "indoorCoilerSensorErr", 		4 },
	{ "indoorOutdoorCommErr", 		5 },
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
	{ "filterCleaningAlarm", 		17 },
	{ "waterLackProtection", 		18 },
	{ "humiditySensorErr", 			19 },
	{ "indoorTempSensorErr", 		20 },
	{ "mechanicalArmLimitErr", 		21 },
	{ "indoorPM2p5SensorErr", 		22 },
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
	{ "ch2oSensorErr", 				47 },
	{ "vocSensorErr", 				48 },
	{ "co2SensorErr", 				49 },
	{ "firewallErr", 				50 },
	{ "tdOverHighAlarm", 			51 },
	{ "envTempOverHighAlarm", 		52 },
	{ "mcuReset", 					53 },
	{ "moduleCurrentDetectionCircuitErr", 	54 },
	{ "liqPipeATempSensorErr", 		55 },
	{ "liqPipeBTempSensorErr", 		56 },
	{ "liqPipeCTempSensorErr", 		57 },
	{ "liqPipeDTempSensorErr", 		58 },
	{ "liqPipeETempSensorErr", 		59 },
	{ "airPipeATempSensorErr", 		60 },
	{ "airPipeBTempSensorErr", 		61 },
	{ "airPipeCTempSensorErr", 		62 },
	{ "airPipeDTempSensorErr", 		63 },

	{ "airPipeETempSensorErr", 		64 },
	{ "moduleTempSensorErr", 		65 },
	{ "powerInstantDetectErr", 		66 },
	{ "voltageOverHighProtection", 	67 },
	{ "voltageOverLowProtection", 	68 },
	{ "tc2Err", 					69 },
	{ "tc3Err", 					70 },
	{ "humanSensingModuleErr", 		71 },
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


ALARM_ARRAY JsonALRM[] = {
    { ALARM_WC          , 0, 0, "Wine Cooler" },
    { ALARM_WH          , 0, 0, "Water Heater" },
    { ALARM_HVAC        , 0, 0, "Air conditioning HVAC" },
    { ALARM_HVAC2       , 0, 0, "Air conditioning HVAC II" },
    { ALARM_WM			, 0, 0, "Drum washing machine" },
    { ALARM_FR_RU60cm	, 0, 0, "Fridge RU 60cm" },
    { ALARM_HO_Arcair   , 0, 0, "Hood Arcair" },
    { ALARM_HO_Haier    , 0, 0, "Hood Haier" },
    { ALARM_FRA3FE744   , 0, 0, "Multidoor 982k A3FE744" },
    { ALARM_HB20        , 0, 0, "Multidoor 982J HB20" },

	{NULL, 0, 0, ""}
};


//not used yet
SERIAL_CMD Device_status[] = {
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
/*
unsigned char SoftApDeviceName_configMode_WC[8] = {
    0x55, 0x2D, 0x43, 0x45, 0x4C, 0x4C, 0x00, 0x00
    };
*/

unsigned char SoftApDeviceName_configMode_WH[8] = {
    0x55, 0x2D, 0x45, 0x57, 0x48, 0x00, 0x00, 0x00
    };

unsigned char SoftApDeviceName_configMode_HVAC[8] = {
    0x55, 0x2D, 0x41, 0x43, 0x00, 0x00, 0x00, 0x00
    };

 unsigned char TYPEID_WC[32] = {
    0x20, 0x08, 0x61, 0x05, 0x1c, 0x40, 0x85, 0x04,
    0x08, 0x12, 0x00, 0x71, 0x80, 0x01, 0x32, 0x42,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x71, 0x80,
    0x02, 0x23, 0xa0, 0x00, 0x00, 0x00, 0x00, 0x40,
    };

 unsigned char TYPEID_WH[32] = {
    0x20, 0x1c, 0x12, 0x00, 0x00, 0x11, 0x86, 0x74,
    0x06, 0x16, 0x00, 0x41, 0x80, 0x07, 0x23, 0x41,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40,
    };

 unsigned char TYPEID_HVAC[32] = {
    0x20, 0x08, 0x61, 0x08, 0x00, 0x82, 0x03, 0x24,
    0x02, 0x12, 0x00, 0x11, 0x80, 0x09, 0x09, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40,
    };

 unsigned char TYPEID_HVAC2[32] = {
    0x20, 0x1c, 0x10, 0xc7, 0x08, 0x80, 0x81, 0x00,
    0x0d, 0x12, 0x05, 0x46, 0x45, 0x44, 0x85, 0x00,
    0x00, 0x00, 0x9c, 0xd6, 0x8e, 0x69, 0x2c, 0x10,
    0x4e, 0x2a, 0x33, 0x3e, 0xab, 0x95, 0xd1, 0x40,
    };

 unsigned char TYPEID_HO_ken1[32] = {
    0x20, 0x1c, 0x10, 0xc7, 0x14, 0x12, 0x02, 0x10,
    0x09, 0x01, 0x37, 0x7a, 0x39, 0x98, 0x79, 0x00,
    0x00, 0x00, 0x41, 0x72, 0x63, 0x61, 0x69, 0x72,
    0x48, 0x64, 0x04, 0x64, 0x45, 0x00, 0x00, 0x40,
    };

 unsigned char TYPEID_HO_1[32] = {
    0x20, 0x1c, 0x10, 0xc7, 0x14, 0x12, 0x02, 0x10,
    0x09, 0x01, 0x37, 0x7a, 0x39, 0x98, 0x79, 0x00,
    0x00, 0x00, 0xfb, 0x0f, 0x11, 0x4f, 0xd0, 0xf0,
    0xee, 0xc4, 0x1b, 0x63, 0x51, 0xc1, 0x63, 0x40,
    };

 unsigned char TYPEID_WM[32] = {
    0x20, 0x1c, 0x51, 0x89, 0x0c, 0x31, 0xc3, 0x08,
    0x05, 0x01, 0x00, 0x21, 0x80, 0x00, 0x67, 0x4b,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40,
    };

 unsigned char TYPEID_FR01[32] = {   //Fridge: RU 60cm
    0x20, 0x08, 0x61, 0x05, 0x1c, 0x40, 0x85, 0x04,
    0x01, 0x24, 0x00, 0x61, 0x80, 0x06, 0x98, 0x55,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x61, 0x80,
    0x03, 0x12, 0x55, 0x00, 0x00, 0x00, 0x00, 0x40,
    };

 //20 1C 10 C7 14 12 02 10 09 01 37 7A 39 98 79 00 00 00 FB 0F 11 4F D0 F0 EE C4 1B 63 51 C1 63 40
 unsigned char TYPEID_FRA3FE744[32] = { //k
    0x20, 0x08, 0x61, 0x05, 0x1c, 0x40, 0x85, 0x04,
    0x01, 0x21, 0x00, 0x61, 0x80, 0x09, 0x82, 0x4b,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x61, 0x80,
    0x03, 0x51, 0x52, 0x00, 0x00, 0x00, 0x00, 0x40,
    };

 unsigned char TYPEID_HB20[32] = {      //j
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

unsigned char STOP_ALARM_9[10] = {
    0xFF, 0xFF, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0b
    };

unsigned char STATUS_INTERVAL_7C[13] = {
    0xFF, 0xFF, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7C, 0x00, 0x64, 0xEA    //>checksum!
    };

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


#endif 
