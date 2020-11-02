//algorithm.h
#ifndef __ALGORITHM_H
#define __ALGORITHM_H

typedef unsigned long ulong;

ulong  CRC32(const ulong *pmsg, ulong msg_size);
unsigned short CRC16(const unsigned char* puchMsg, unsigned short usDataLen);


#endif