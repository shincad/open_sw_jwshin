//**************************************************************************
//
//		ttx.h
//
//**************************************************************************
#if !defined _NFREN_TTX_FUNCTIONS_
#define _NFREN_TTX_FUNCTIONS_

#include "Topheader.h"
#include "extern.h"
#include <stdio.h>

#define SDA555x_Addr		0x22

void idelay5m(BYTE time);
void putss(BYTE);

void DelayNOP20(void);		// Lcall is 4byte 4cycle
void DelayNOP12(void);		// Lcall is 4byte 4cycle
void DelayNOP10(void);		// Lcall is 4byte 4cycle
void DelayNOP6(void);		// Lcall is 4byte 4cycle
//void DelayNOP25(void);		// 25uS

bit SDA555xWriteData(unsigned char temp);
bit SDA555xSTART_I2C(unsigned char sysaddr);
void SDA555xSTOP_I2C(void);
WORD SDA555xReadDataNAK(void);
bit SDA555XWrite(unsigned char subaddr, unsigned char writedata);
unsigned char SDA555XRead(unsigned char address);
void SDA555xInit(void);
void SDA555xModeChange(void);

#endif	//_NFREN_TTX_FUNCTIONS_

