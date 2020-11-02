#include "crc16.h"

#pragma default_near_size 2

static void DoCRC(unsigned char bCh, unsigned short *pwCRC16)
{
	unsigned short wi;

    *pwCRC16 = bCh ^ (*pwCRC16);
    for (wi = 0; wi < 8; wi++)	{
        if (((*pwCRC16) & 1) == 1)	{
            *pwCRC16 >>= 1;
            *pwCRC16 = (*pwCRC16 ^ 0xA001);
        	}
        else *pwCRC16 >>= 1;
    	}
}

//---------------------------------------------------------------------------
unsigned short MakeCRC(unsigned char *bMemory, unsigned short len)
{
	unsigned long n;
	unsigned short wCRC = 0xFFFF; 
	
	for (n = 0; n < len; n++)
    	DoCRC( bMemory[n] , &wCRC) ;
    
    return wCRC>>8 | wCRC<<8;
}

#pragma default_near_size restore