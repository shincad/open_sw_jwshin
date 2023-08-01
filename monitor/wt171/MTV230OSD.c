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
//------------------------------------------------------------------------------------------------------------------

//#if	defined(MCU_MTV230) /*&& !defined(InternalOSD)*/ && !defined(NoOsdMenu)	

#if	defined(MCU_MTV230) && !defined(InternalOSD) && !defined(NoOsdMenu) && !defined(INT_EXTOSD)

#include	"TopHeader.h"
//------------------------------------------------------------------------------------------------------------------
#include	"MTV230xfr.h"

//****************************************************************//
//변수선언
//****************************************************************//
extern	bit	HighOSDArea;

#if defined (MicomXFRbackup) && defined(Mtv230OSDbackup)
extern xdata BYTE xMicomBuffer[57];
#elif defined(MicomXFRbackup)
extern xdata BYTE xMicomBuffer[256];
#endif

extern	xdata	BYTE	xEEPROMBuffer[MaxEepromBuffer];


#if !defined(InternalOSD)
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
#endif

void OSD230RowSend(BYTE Recdata)
{
	BYTE temp1=0;
	xOSDRA = Recdata&0x7F;
	
	#ifdef MicomXFRbackup
	temp1=&xOSDRA;				//(mtv230xfr.c => xdata	BYTE xOSDRA _at_ 0xFA0;)
	xMicomBuffer[temp1]=Recdata&0x7F;	//(generalram.c => xdata BYTE xMicomBuffer[256] _at_ 0x0A00;)
	#endif
}

void OSD230ColSend(BYTE Recdata)
{
	BYTE temp1=0;
	xOSDCA = Recdata&0x1F;
	
	#ifdef MicomXFRbackup
	temp1=&xOSDCA;				//(mtv230xfr.c => xdata	BYTE xOSDCA _at_ 0xFA1;)
	xMicomBuffer[temp1]=Recdata&0x1F;
	#endif
}

void OSD230DataSend(BYTE Recdata)
{
	BYTE temp1=0;
	
	if(!HighOSDArea)	//if, HighOSDArea =0
	{
		xOSDDT0 = Recdata;		//(mtv230xfr.c => xdata	BYTE xOSDDT0 _at_ 0xFA2;)
		
		#ifdef MicomXFRbackup
		temp1=&xOSDDT0;
		xMicomBuffer[temp1]=Recdata;
		#endif
	}
	else			//if, HighOSDArea =1
	{
		xOSDDT1 = Recdata;
		
		#ifdef MicomXFRbackup
		temp1=&xOSDDT1;
		xMicomBuffer[temp1]=Recdata;
		#endif
	}
//	HighOSDArea = 0;	smpark 20030821
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


void OSDWINDOW(BYTE *Recdata)
{
	#ifdef MicomXFRbackup
	BYTE Tttt;
	#endif

	BYTE temp0=0;
	BYTE temp1=0;	
	while(1)
	{
		temp1 = *(Recdata + temp0++);
		if(temp1 == F_STOP) break;
		
		xOSD_WIN_REG[temp0-1] = temp1;		//(mtv230xfr.c => xdata	BYTE xOSD_WIN_REG[15] _at_ 0x0FC0;)
		
		#ifdef MicomXFRbackup
		Tttt=&xOSD_WIN_REG[temp0-1];
		xMicomBuffer[Tttt]=temp1;
		#endif
	}
}


void OSDWINDOW_OPTION(BYTE *Recdata)
{
	BYTE temp0=0;
	BYTE temp1=0;

	#ifdef MicomXFRbackup
	BYTE Tttt;
	#endif
	temp0 =temp1 =0;	

	while(1)
	{
		temp1 = *(Recdata + temp0++);
		if(temp1 == F_STOP) break;
		
		xOSDW_OPTION[temp0-1] = temp1;		//(mtv230xfr.c => xdata	BYTE xOSDW_OPTION[10] _at_ 0x0FD0;)
		
		#ifdef MicomXFRbackup
		Tttt=&xOSDW_OPTION[temp0-1];
		xMicomBuffer[Tttt]=temp1;
		#endif
	}
}

/*  for memory save 2003.6.5
void OSDMENU_FONT(BYTE	idata *addr)		// 2003-04-30 by thkim, [new define F_START, F_END]
{				   		// Icon & on the menu character does displays
	BYTE idata s_data;
	BYTE idata index;
	BYTE idata active_flag;
	
	index = s_data = HighOSDArea = 0;
	active_flag = 1;

	while(active_flag)
	{
		s_data = *(addr + index++);  
		if(s_data == F_START)
		{
			s_data = *(addr + index);	// First  Address(ROW_address)
			if((s_data & 0x80)==0x80) HighOSDArea = 1; // upper Font Area(0x0100~0x01ff)
			else 			  HighOSDArea = 0; // lower Font Area(0x0000~0x00ff)
			xOSDRA = s_data;
			++index;
			
			s_data = *(addr + index);	//Second Address(COL_address)
			xOSDCA = s_data;
			++index;
			  
		}
		else if(s_data == F_STOP) active_flag = 0;	   	//OSD  End
		else
		{					//After Address(DATA_address)
			if(HighOSDArea) xOSDDT1 = s_data; //upper Font memory
			else	        xOSDDT0 = s_data; //lower Font memory
		}
	}
}
*/


void OSD230DatPtrSend(BYTE *Recdata2,BYTE Recdata3)
{
	while(Recdata3--)		
	{	
		OSD230DataSend(*(Recdata2++));
	}
}

void OSD230PtrSend(BYTE Recdata0,BYTE Recdata1,BYTE *Recdata2,BYTE Recdata3)//return -> Row,Col,Pointer(array),Pointer count)
{
	OSD230RowSend(Recdata0);
	OSD230ColSend(Recdata1);
	while(Recdata3--)		
	{	
		OSD230DataSend(*Recdata2++);	
	}
}



void OSD230SeqSend(BYTE Recdata0,BYTE Recdata1,BYTE Recdata2,BYTE Recdata3)	//R,C,D,D...(ROW,COL,DATA,CNT)
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

void OSD230Data2SendHigh(BYTE Recdata0,BYTE Recdata1)
{
	OSD230DataSendHigh(Recdata0);
	OSD230DataSendHigh(Recdata1);
}



#endif	//------------------------------------------------------------------------------------------------------------------
