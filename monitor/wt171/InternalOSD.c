/****************************************************************************
   +----------------------------------------------------------------------+
   | Copyright EDtech co.ltd 2002                                         |
   | EDtech co.ltd reserves the right to change products                  |
   | or specifications without notice.                                    |
   +----------------------------------------------------------------------+
   Project    : TFT LCD monitor & TV
   Version    : 
   File Name  : 
   Functions  : 
   Revision   :

   2003-01-10 2:39오후  JDHAN           Modified for Monitor-TV
****************************************************************************/

#include	"TopHeader.h"
#include "extern.h"


#if	defined(InternalOSD)

#if		defined(MCU_MTV212)
#include	"MTV212xfr.h"
#elif	defined(MCU_MTV230)
#include	"MTV230xfr.h"
#elif		defined(MCU_MTV412)
#include	"MTV412xfr.h"
#elif	defined(MCU_NT68F63)
#include	"NT68F63.h"
#endif

#include "ttx.h"


//****************************************************************//
//함수선언
//****************************************************************//
#ifdef	USE_4BitInterface
	void WriteOsdAdr4bit(BYTE address);
	void WriteOsdDat4bit(BYTE Recdata);
	#define	OSDRowSend(val)		WriteOsdAdr4bit(val)
	#define	OSDDataSend(val)	WriteOsdDat4bit(val)
#else
	void WriteOsdAdr1bit(BYTE Recdata);
	void WriteOsdDat1bit(BYTE Recdata);
	#define	OSDRowSend(val)		WriteOsdAdr1bit(val)
	#define	OSDDataSend(val)	WriteOsdDat1bit(val)
#endif


//****************************************************************//
//변수선언
//****************************************************************//



////
#define	IN_F_START			0x78
#define	IN_F_STOP			0x79
#define	OSDstart	{\
					_SCALER_CS_LOW;\
					DelayNOP20();\
					}

#define	OSDstop		{\
					DelayNOP20();\
					_SCALER_CS_HIGH;\
					}


BYTE calToChar(DWORD Recdata)
{
	idata	unsigned char Retdata;
	
	if(!Recdata) 				Retdata = 1;
	if(Recdata>0)				Retdata = 1;
	if(Recdata>=10)				Retdata = 2;
	if(Recdata>=100)			Retdata = 3;
	if(Recdata>=1000)			Retdata = 4;
	if(Recdata>=10000)			Retdata = 5;
	if(Recdata>=100000)			Retdata = 6;
	if(Recdata>=1000000)		Retdata = 7;
	if(Recdata>=10000000)		Retdata = 8;
	if(Recdata>=100000000)		Retdata = 9;
	
	switch(Retdata)
	{
		case	0:
			CalBuffer[1-1] = 0;
			break;
		case	1:
			CalBuffer[1-1] = Recdata;
			break;
		
		case	2:
			CalBuffer[2-2] = (Recdata/10);
			CalBuffer[2-1] = (Recdata%10);
			break;
		
		case	3:
			CalBuffer[3-3] = (Recdata/100);
			CalBuffer[3-2] = (Recdata%100)/10;
			CalBuffer[3-1] = (Recdata%10);
			break;

		case	4:
			CalBuffer[4-4] = (Recdata/1000);
			CalBuffer[4-3] = (Recdata%1000)/100;
			CalBuffer[4-2] = (Recdata%100)/10;
			CalBuffer[4-1] = (Recdata%10);
			break;		
			
		case	5:
			CalBuffer[5-5] = (Recdata/10000);
			CalBuffer[5-4] = (Recdata/10000)/1000;
			CalBuffer[5-3] = (Recdata%1000)/100;
			CalBuffer[5-2] = (Recdata%100)/10;
			CalBuffer[5-1] = (Recdata%10);
			break;					
		
		case	6:
			CalBuffer[6-6] = (Recdata/100000);
			CalBuffer[6-5] = (Recdata/100000)/10000;
			CalBuffer[6-4] = (Recdata%10000)/1000;
			CalBuffer[6-3] = (Recdata%1000)/100;
			CalBuffer[6-2] = (Recdata%100)/10;
			CalBuffer[6-1] = (Recdata%10);
			break;						
			
		case	7:
			CalBuffer[7-7] = (Recdata/1000000);
			CalBuffer[7-6] = (Recdata/1000000)/100000;
			CalBuffer[7-5] = (Recdata/100000)/10000;
			CalBuffer[7-4] = (Recdata%10000)/1000;
			CalBuffer[7-3] = (Recdata%1000)/100;
			CalBuffer[7-2] = (Recdata%100)/10;
			CalBuffer[7-1] = (Recdata%10);
			break;									

		case	8:
			CalBuffer[8-8] = (Recdata/10000000);
			CalBuffer[8-7] = (Recdata/10000000)/1000000;
			CalBuffer[8-6] = (Recdata/1000000)/100000;
			CalBuffer[8-5] = (Recdata/100000)/10000;
			CalBuffer[8-4] = (Recdata%10000)/1000;
			CalBuffer[8-3] = (Recdata%1000)/100;
			CalBuffer[8-2] = (Recdata%100)/10;
			CalBuffer[8-1] = (Recdata%10);
			break;												

		case	9:
			CalBuffer[9-9] = (Recdata/100000000);
			CalBuffer[9-8] = (Recdata/100000000)/10000000;
			CalBuffer[9-7] = (Recdata/10000000)/1000000;
			CalBuffer[9-6] = (Recdata/1000000)/100000;
			CalBuffer[9-5] = (Recdata/100000)/10000;
			CalBuffer[9-4] = (Recdata%10000)/1000;
			CalBuffer[9-3] = (Recdata%1000)/100;
			CalBuffer[9-2] = (Recdata%100)/10;
			CalBuffer[9-1] = (Recdata%10);
			break;															
	}
	return Retdata;
}

/*
void OSDSeqSend(BYTE Row,BYTE Col,BYTE Data,BYTE Count)
{
	OSDstart;
	OSDRowSend(Row);
	OSDRowSend(Col);
	while(Count--) OSDDataSend(Data);
	OSDstop;
}

void OSDDataPtrSend(BYTE *Recdata2,BYTE Recdata3)
{
	idata	BYTE temp0 = 0;
	while(Recdata3--)		
	{	
		OSDDataSend(*(Recdata2+temp0));
		temp0++;
	}
}

void OSDPtrSend(BYTE Recdata0,BYTE Recdata1,BYTE *Recdata2,BYTE Recdata3)//return -> Row,Col,Pointer(array),Pointer count)
{
	idata	BYTE temp0 = 0;
	OSDstart;
	OSDRowSend(Recdata0);
	OSDRowSend(Recdata1);
	while(Recdata3--)		
	{	
		OSDDataSend(*(Recdata2+temp0));
		temp0++;
	}
	OSDstop;
}

*/
void I_OSDWINDOW(BYTE *ta)
{
	idata	BYTE td_i=0,idx=0,seq_rc=2;

	OSDstart;

	do
	{
		td_i=*(ta+idx++);
		if(seq_rc==2)
		{
			OSDRowSend(td_i);
			if((td_i&0x80)==0)
			{
				if(td_i&0x40) seq_rc=0; else seq_rc=1;
			}
			continue;
		}
		else if(seq_rc)
		{
			OSDDataSend(td_i);
			seq_rc=2;
			continue;
		}
		else
		{
			if(td_i==F_START)
			{
				OSDstop;
				NOPx10;
				seq_rc=2;
				OSDstart;
				continue;
			}
			if(td_i==F_STOP) break;
			OSDDataSend(td_i);
		}
	}while(1);
	OSDstop;
}

#endif