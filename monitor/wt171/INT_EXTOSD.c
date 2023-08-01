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

//****************************************************************//
//화일참조
//****************************************************************//
#include	"TopHeader.h"

#if	defined(INT_EXTOSD)
#include	"MTV230xfr.h"

#include "ttx.h"
#include "extern.h"

//****************************************************************//
//함수선언
//****************************************************************//
#ifdef	USE_4BitInterface
void WriteOsdAdr4bit(BYTE address);
void WriteOsdDat4bit(BYTE Recdata);
#else
void WriteOsdAdr1bit(BYTE Recdata);
void WriteOsdDat1bit(BYTE Recdata);
#endif


//****************************************************************//
//변수선언
//****************************************************************//
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
	unsigned char Retdata;
	
	if(!Recdata) 			Retdata = 1;
	if(Recdata>0)			Retdata = 1;
	if(Recdata>=10)			Retdata = 2;
	if(Recdata>=100)		Retdata = 3;
	if(Recdata>=1000)		Retdata = 4;
	if(Recdata>=10000)		Retdata = 5;
	if(Recdata>=100000)		Retdata = 6;
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

void OSD230RowSend(BYTE Recdata)
{
	BYTE idata temp1=0;
	xOSDRA = Recdata&0x7F;
	#ifdef MicomXFRbackup
	temp1=&xOSDRA;
	xMicomBuffer[temp1]=Recdata&0x7F;
	#endif
}

void OSD230ColSend(BYTE Recdata)
{
	BYTE idata temp1=0;
	xOSDCA = Recdata&0x1F;
	#ifdef MicomXFRbackup
	temp1=&xOSDCA;
	xMicomBuffer[temp1]=Recdata&0x1F;
	#endif
}

void OSD230DataSend(BYTE Recdata)
{
	BYTE idata temp1=0;
		if(!HighOSDArea)
		{
			xOSDDT0 = Recdata;
			#ifdef MicomXFRbackup
			temp1=&xOSDDT0;
			xMicomBuffer[temp1]=Recdata;
			#endif
		}
		else
		{
			xOSDDT1 = Recdata;
			#ifdef MicomXFRbackup
			temp1=&xOSDDT1;
			xMicomBuffer[temp1]=Recdata;
			#endif
		}
//		HighOSDArea = 0;	//smpark 20030821
}


void OSDWINDOW(BYTE *Recdata, BYTE INTor230)
{
	#ifdef MicomXFRbackup
	BYTE Tttt;
	#endif
	
	BYTE  td_i=0,idx=0,seq_rc=2;
	BYTE  temp0=0,temp1=0;	

	if(!INTor230)			// 외부 OSD (INTor230==0)
	{        
		while(1)
		{
			temp1 = *(Recdata + temp0++);
			if(temp1 == F_STOP) break;
			xOSD_WIN_REG[temp0-1] = temp1;
			
			#ifdef MicomXFRbackup
			Tttt=&xOSD_WIN_REG[temp0-1];
			xMicomBuffer[Tttt]=temp1;
			#endif
		}
	}
	else				// 내부 OSD	(INTor230==1)
	{
		OSDstart;
	
		do
		{
			td_i=*(Recdata+idx++);
			if(seq_rc==2)
			{
				WriteOsdAdr1bit(td_i);
				if((td_i&0x80)==0)
				{
					if(td_i&0x40) 	seq_rc=0; 
					else 		seq_rc=1;
				}
				continue;
			}
			else if(seq_rc)
			{
				WriteOsdDat1bit(td_i);
				seq_rc=2;
				continue;
			}
			else
			{
				
				if(td_i==IN_F_START)
				{
					OSDstop;
					NOPx10;
					seq_rc=2;
					OSDstart;
					continue;
				}
				if(td_i==IN_F_STOP) break;
				WriteOsdDat1bit(td_i);
			}
		}while(1);
		
		OSDstop;
	}
}


void OSDWINDOW_OPTION(BYTE *Recdata)
{
	BYTE idata temp0=0;
	BYTE idata temp1=0;

	#ifdef MicomXFRbackup
	BYTE Tttt;
	#endif
	temp0 =temp1 =0;	

	while(1)
	{
		temp1 = *(Recdata + temp0++);
		if(temp1 == F_STOP) break;
		xOSDW_OPTION[temp0-1] = temp1;
		
		#ifdef MicomXFRbackup
		Tttt=&xOSDW_OPTION[temp0-1];
		xMicomBuffer[Tttt]=temp1;
		#endif
	}
}

//------------------------------------------IntOSD

void WriteOsdAdr1bit(BYTE Recdata);
void WriteOsdDat1bit(BYTE Recdata);
#define	OSDRowSend(val)		WriteOsdAdr1bit(val)
#define	OSDDataSend(val)	WriteOsdDat1bit(val)

void OSDSeqSend(BYTE Row,BYTE Col,BYTE Data,BYTE Count)
{
	OSDstart;
	OSDRowSend(Row);
	OSDRowSend(Col);
	while(Count--) OSDDataSend(Data);
	OSDstop;
}
/*
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

//---------------------------------------------------------------------

void OSD230DatPtrSend(BYTE *Recdata2,BYTE Recdata3)
{
	BYTE idata  temp0 = 0;
		while(Recdata3--)		
		{	
			OSD230DataSend(*(Recdata2+temp0));
			temp0++;
		}
}

void OSD230PtrSend(BYTE Recdata0,BYTE Recdata1,BYTE *Recdata2,BYTE Recdata3)//return -> Row,Col,Pointer(array),Pointer count)
{
	BYTE idata temp0 = 0;
		OSD230RowSend(Recdata0);
		OSD230ColSend(Recdata1);
		while(Recdata3--)		
		{	
			OSD230DataSend(*(Recdata2+temp0));
			temp0++;
		}
}

void OSD230SeqSend(BYTE Recdata0,BYTE Recdata1,BYTE Recdata2,BYTE Recdata3)
{
		OSD230RowSend(Recdata0);
		OSD230ColSend(Recdata1);
		while(Recdata3--) OSD230DataSend(Recdata2);
}


void OSD230SeqSend2(BYTE Recdata0,BYTE Recdata1,BYTE Recdata2,BYTE Recdata3)	//row,col,data,data//
{
	
	OSD230RowSend(Recdata0);
	OSD230ColSend(Recdata1);
	
	
	OSD230DataSend(Recdata2);
	OSD230DataSend(Recdata3);
}


void OSD230DataSendHigh(BYTE Recdata)
{
	BYTE temp1=0;

	xOSDDT1 = Recdata;
	
	#ifdef MicomXFRbackup
	temp1=&xOSDDT1;
	xMicomBuffer[temp1]=Recdata;
	#endif
}


void OSD230Data2SendHigh(BYTE Recdata0,BYTE Recdata1)
{
	OSD230DataSendHigh(Recdata0);
	OSD230DataSendHigh(Recdata1);
}
#endif
