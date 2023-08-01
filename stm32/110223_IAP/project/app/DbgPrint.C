//---------------------------------------------
//
//		IQS I/O Board Firmware
//		FileName : DbgPrint.c
//		Version : 1.00
//
//		Date   : 2010.12.17
//		Author : Shin Jung Wook
//						 DNP System.	
//						 
//---------------------------------------------
#include "stm32f10x_type.h"
#include "DbgPrint.h"
#include "Serial.h"
#include "util.h"

u8 PrtBuf[100];

void PrtChar	(u8		in);
void PrtShort	(u16	in);
void PrtInt		(u32	in);
void PrtMsg		(u8	   *in);


void PrtSpace	(void)
{
	u8 tmp;
	tmp = 0x20;
	SendHost(1,&tmp);
}

void PrtLF	(void)
{
  	u8 tmp[2]={0x0d,0x0a};
	SendHost(2,&tmp[0]);
}

void PrtChar	(u8		in)
{
	u32ToHex(in);
	SendHost(2,&HexOut[6]);
}

void PrtShort	(u16	in)
{
	u32ToHex(in);
	SendHost(4,&HexOut[4]);
}

void PrtInt		(u32	in)
{
	u32ToHex(in);
	SendHost(8,&HexOut[0]);
}
void PrtMsg		(u8	   *in)
{
	u8	size = 0;
	int i;
	for(i=0;i<100;i++)
	{
		size++;
		if( *(in+i) == 0) break;
	}
	for(i=0;i<size;i++)
	{
	  PrtBuf[i] = in[i];
	}
	PrtBuf[i++] = 0x0d;
	PrtBuf[i++] = 0x0a;
	SendHost(size+2, &PrtBuf[0]);
}

