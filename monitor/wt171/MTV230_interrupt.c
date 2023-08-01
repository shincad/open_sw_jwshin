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
#include "extern.h"

#ifdef	MCU_MTV230
#include	"MTV230xfr.h"



//****************************************************************//
//함수선언
//****************************************************************//
BYTE GetEMH1A(BYTE address);
BYTE AD9884_Read(BYTE address);
bit WriteI2C(BYTE sysaddr, BYTE subaddr, BYTE writedata);
BYTE EEPROM_Read(WORD address);
WORD ReadI2C(BYTE SystemAdr, WORD address);
#ifdef	DVI_EDIDWrite
BYTE EEPROM_Read_02(WORD address);
#endif

#ifdef	USE_4BitInterface								//4bit통신 함수선언
void	WriteReg4bit(BYTE address, BYTE Recdata);
#define	WriteScaler(val1,val2) WriteReg4bit(val1,val2)	
BYTE	ReadScalerParallel(BYTE address);
#define	ReadScaler	ReadScalerParallel

#else													//1bit통신 함수선언
void	WriteReg1bit(BYTE address, BYTE Recdata);
#define	WriteScaler(val0, val1) WriteReg1bit(val0, val1)
BYTE	ReadScalerSerial(BYTE address);
#define	ReadScaler	ReadScalerSerial
#endif

void OSDSeqSend(BYTE Row,BYTE Col,BYTE Data,BYTE Count);
code BYTE EDID_Data[128]=
{	
/* 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x41, 0x34, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00,		// Modified Data
 0x14, 0x0e, 0x01, 0x01, 0x08, 0x25, 0x17, 0x78, 0x08, 0xfb, 0x89, 0xa1, 0x55, 0x4b, 0x97, 0x24,
 0x11, 0x48, 0x4f, 0xbf, 0xee, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x54, 0x19, 0x00, 0x40, 0x51, 0x00, 0x26, 0x30, 0x18, 0x88,
 0x36, 0x00, 0x60, 0x08, 0x11, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0xfc, 0x00, 0x57,
 0x54, 0x2d, 0x31, 0x37, 0x31, 0x50, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x00, 0x00, 0x00, 0xfd,
 0x00, 0x32, 0x50, 0x1e, 0x41, 0x08, 0x00, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x00, 0xf7,  */

/* 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x41, 0x34, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00,		// 150PV DDC Data
 0x26, 0x0a, 0x01, 0x01, 0x08, 0x1e, 0x17, 0x64, 0xe8, 0xfb, 0x89, 0xa1, 0x55, 0x4b, 0x97, 0x24,
 0x11, 0x48, 0x4f, 0xbf, 0xee, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x54, 0x19, 0x00, 0x40, 0x41, 0x00, 0x26, 0x30, 0x18, 0x88,
 0x36, 0x00, 0x60, 0x08, 0x11, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0xfc, 0x00, 0x57,
 0x54, 0x2d, 0x31, 0x37, 0x31, 0x50, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x00, 0x00, 0x00, 0xfd,
 0x00, 0x32, 0x50, 0x1e, 0x41, 0x08, 0x00, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x00, 0x1f, */

/*  0x20,0x24,0x4d,0x04,0x97,0x0f,0xd1,0x07,0x49,0x42,0x4d,0x09,0x54,0x46,0x54,0x2d,						// VESA Sheet Sample Data
 0x4c,0x43,0x44,0x20,0x4d,0x4f,0x42,0x49,0x54,0x4f,0x52,0x0a,0x20,0x20,0x20,0x20,
 0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x35,0x32,0x30,0x30,0x30,0x30,0x30,0x31,
 0x0a,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,
 0x50,0x30,0xd0,0x41,0x70,0x24,0x00,0x00,0x00,0x00,0x10,0x66,0x60,0x00,0x00,0x13,
 0x89,0xe0,0x58,0x00,0x3a,0x24,0x8c,0xff,0xff,0xff,0xdc,0x05,0xc0,0x00,0x32,0xec,
 0x9f,0x58,0x48,0x9d,0x23,0x17,0x4a,0x52,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
 0x00,0x00,0x3f,0x01,0xff,0x00,0x00,0x05,0x00,0x04,0x19,0x19,0x00,0x00,0x25,0x08,
 0x0f,0x03,0x03,0x06,0x0a,0x10,0x19,0x24,0x32,0x42,0x55,0x6a,0x82,0x9d,0xbb,0xdc,
 0x0f,0x0f,0x0f,0x10,0x0c,0x6c,0x72,0x00,0x30,0x2a,0xde,0x20,0x10,0x1a,0x18,0x33,
 0x00,0x88,0x2c,0xde,0x20,0x10,0x33,0x3f,0xff,0x10,0x00,0x00,0x54,0x00,0x00,0x06,
 0x40,0x1e,0x85,0x3c,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x51, */

/* 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x12, 0x6d, 0x00, 0x10, 0x01, 0x01, 0x01, 0x01,			//2004.06.03 +Shin
 0x16, 0x0d, 0x01, 0x01, 0x08, 0x25, 0x16, 0x78, 0xe8, 0xfb, 0x89, 0x9f, 0x55, 0x46, 0x98, 0x24,
 0x10, 0x48, 0x4c, 0xff, 0xee, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x54, 0x19, 0x00, 0x40, 0x41, 0x00, 0x26, 0x30, 0x18, 0x88,
 0x36, 0x00, 0x60, 0x08, 0x11, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0xfc, 0x00, 0x57,
 0x54, 0x2d, 0x31, 0x37, 0x31, 0x50, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x00, 0x00, 0x00, 0xfd,
 0x00, 0x32, 0x50, 0x1e, 0x41, 0x08, 0x00, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x00, 0xce,  */


 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x41, 0x34, 0x00, 0x10, 0x01, 0x01, 0x01, 0x01,			
 0x16, 0x0e, 0x01, 0x01, 0x08, 0x25, 0x16, 0x78, 0xe8, 0xfb, 0x89, 0x9f, 0x55, 0x46, 0x98, 0x24,
 0x10, 0x48, 0x4c, 0x25, 0x49, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0xe4, 0x25, 0x00, 0x40, 0x51, 0x00, 0x26, 0x30, 0x18, 0x88,
 0x36, 0x00, 0x72, 0xdc, 0x11, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0xfc, 0x00, 0x57,
 0x54, 0x2d, 0x31, 0x37, 0x31, 0x50, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x00, 0x00, 0x00, 0xfd,
 0x00, 0x3c, 0x3c, 0x3c, 0x3c, 0x09, 0x00, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x00, 0xb4, 


 

};

//****************************************************************//
//변수선언
//****************************************************************//
extern	bit	TimerBit;
extern	bit LoopEnd;
extern	bit	RepeatCodeWait;//2003-08-09 4:44오후



extern	BYTE	ReadAdr;
extern	WORD	PowerOnTimer;
extern	BYTE	PowerOffTimer;
extern	WORD	OSDofftimer;

#ifdef USE_remocon
extern	bit SCDT_LOWBackup;	
extern	bit SCDT_HIGHBackup;	
extern	bit		RepeatCodeBit;
extern	BYTE	RemoteShortTimer;
extern	BYTE	RemoteQue;
extern	BYTE	RemoteLongTimer;

extern bit ThreeDigit;				// smpark 20030806

//extern	BYTE	idata RepeatCodeCount;
extern	WORD 	RemoconTenKeyTimer;
#endif

#if defined (MicomXFRbackup) && defined(Mtv230OSDbackup)
extern xdata BYTE xMicomBuffer[57];
BYTE xdata *xdataptr;
#elif defined(MicomXFRbackup)
extern xdata BYTE xMicomBuffer[256];
BYTE xdata *xdataptr;
#endif

extern	BYTE	SyncStableTimer;


#define	Timer1Set	NOP;//Timer1 set!

/*
Interrupt#		Interrupt Desc		Interrupt Adr
0				External Int0		0x0003h
1				Timer/Counter0		0x000Bh
2				External Int1		0x0013h
3				Timer/Count1		0x001Bh
4				SerialPort			0x0023h
*/


/*

*16Bit Mode
<<0x54	0x00	0x02	0x11	0x23>>	
	0x54	:Not Bufferring(because, ID)
	0x00	:EMH1A Dev addr			//0z
	0x02	:EMH1A Sub addr(MSB)	//1st
	0x11	:16bit data's MSB		//2nd		
	0x23	:16bit data's LSB		//3rd
	
*8Bit Mode
<<0x54	0x01	0x06	0x11>>
	0x54	:Not Bufferring(because, ID)
	0x00	:EMH1A Dev addr			//0z
	0x02	:EMH1A Sub addr			//1st
	0x11	:8bit data				//2nd		

	
*/


/////////////////////////////////////////////////////////////////////
//	External interrupt routine
/////////////////////////////////////////////////////////////////////
#ifdef USE_remocon
void EX0_INT() interrupt 0
{
	if	(64<=RemoteShortTimer&&RemoteShortTimer<=68)		//Leader code	(13.5ms)
	{
		RemoteValue=0xffffffff;
		RemoteQue=0;
		RemoteLongTimer=0;
		RepeatCodeWait=0;
	}
	else if	(10<=RemoteShortTimer&&RemoteShortTimer<=12)	//High,shift(left) (2.25ms)
	{
		RemoteValue<<=1;
		RemoteValue|=1;
		++RemoteQue;
	}
	else if (5<=RemoteShortTimer&&RemoteShortTimer<=7)		//Low,shift(left)	(1.125ms)
	{
		RemoteValue<<=1;
		RemoteValue|=0;
		++RemoteQue;
	}
	//else if ((55<=RemoteShortTimer&&RemoteShortTimer<=59)||RepeatCodeBit||RemoteQue==32) {//REM
	else if ((55<=RemoteShortTimer&&RemoteShortTimer<=59)&& RepeatCodeWait) //2003-08-09 3:45오후
	{
		if(21<=RemoteLongTimer&&RemoteLongTimer<=23)	//Repeat code!!(108ms)
		{
			RemoteLongTimer=0;
			RepeatCodeCount++;

			if(RepeatCodeCount >5){		//kskim rmc 2003-08-09 5:18오후
				RepeatCodeBit=1;
				KeyContinueFlag=1;
				RepeatCodeCount=5;
			}
			else	KeyContinueFlag=0;
		}
		else{
			RemoteValue=0xffffffff;
			RemoteQue=0;
			RemoteLongTimer=0;
			RepeatCodeBit=0;
			RepeatCodeCount=0;
		}
	}
	RemoteShortTimer=0;
	Timer1Set;//Timer1 set!
	//RemBufferClrTimer=50; // 0.5sec	// smpark 20030806
}
#endif


/////////////////////////////////////////////////////////////////////
//	Timer "0" interrupt routine
/////////////////////////////////////////////////////////////////////
void timer0() interrupt 1
{
	TimerBit=1;
	TL0	= Timer0_1Cycle;
	TH0	= Timer0_1Cycle>>8;
	
	#ifdef USE_remocon
	++RemoteLongTimer;
	++RemoconTenKeyTimer;
	if(RemoteLongTimer > 26) //122) 
	{
		RemoteValue=0xffffffff;
		RemoteQue=0;
		RemoteLongTimer=0;
		RepeatCodeWait=0;
		RepeatCodeCount=0;
		KeyContinueFlag=0;
		//DataCode =0;
	}
	#endif

	if((xP54&0x01)==0) { 			// Burning Mode Exit +jwshin 040813
		BurningFlag=0;
	}

	if(PowerOnsequence==GeneralStatus)
	{
		if(TenMin>12000-1){ 	// by ohpal 1.2 
			TenMin=0;
 			SetMin=1;
	  	 }
   		else TenMin++;		// by ohpal 1.2 End 
	}	
	if(!LoopEnd)
	{
		if(PowerOnTimer) PowerOnTimer--;
		if(PowerOffTimer) PowerOffTimer--;
		if(OSDofftimer) OSDofftimer--;
		if(SyncStableTimer) SyncStableTimer--;
		if(SleepTimer) SleepTimer--;
	}
	if(DelayTimer)	DelayTimer--;
	
	#ifdef USE_remocon
	if(RemoconTenKeyTimer>=601)
	{
		ThreeDigit=0;
		if(ReceiveRemoconCount==1)
		{								//smpark 20030806
			ReceiveRemoconCount=0;
			//if(SingleCH)	TunerProcessing =30;
			//else if(SingleCH==0)TunerProcessing =30;

			//if(SingleCHflag)	TunerProcessing =30;
			//else if(SingleCHflag==0)TunerProcessing =30;
			
			TunerProcessing =30;
		}
		else if(ReceiveRemoconCount==0 && SingleCH==0 && SingleCHflag==1) TunerProcessing =30;		//2004-07-20
		//else if(ReceiveRemoconCount==0 && SingleCH==0) TunerProcessing =30;		//2004-07-20
		
	}
	#endif

	if(SoundTimer) SoundTimer--;
}

/////////////////////////////////////////////////////////////////////
//	External "1" interrupt routine
/////////////////////////////////////////////////////////////////////
void EX1_INT (void)	interrupt 2
{
//*********************************** DDC Process 2004/06/01 +jwshin *************//
#ifdef	DDC_ENABLE

	if((xINTFLGI2C&0x04)!=0)                               // Dbufl, ==1 if buffer is empty
	{
		xINTFLGI2C&=0x21; 
		if((xIICSTUS1st & 0x20) != 0) {
			xRXABUF=EDID_Data[mPtrDDC2++];
		}
	} 

	if((xINTFLGI2C&0x08)!=0)                            // Slave A matched
	{
		mPtrDDC2=xRXABUF;
		xRXABUF=EDID_Data[mPtrDDC2++];
	}

	if((xINTFLGI2C&0x10)!=0)                            // DDC2, TXABUF need a new byte
	{
		xRXABUF=EDID_Data[mPtrDDC2++];
		mPtrDDC2 &= 0x7F;								//만약 DDC Data가 128Byte 인 경우 mPtrDDC2 &= 0x7F;	
	}

#endif

#ifdef	External_Debug
	
	if((xINTFLGI2C&0x20)){		//slaveB address match interrupt flag check!(어드레스매칭이면, 데이타프레임의 처음, 이때 BUFFER_count를 처리)
		BUFFER_count = 0;	//어드레스가 매칭이 되면 버퍼갯수변수를 클리어 한다.왜, 시작이므로.
	}

	if((xINTFLGI2C&0x40))		//Receive interrupt flag check!(데이타를 받는다) : xINTFLGI2C(r)
	{ 
		BUFFER[BUFFER_count] = xRXBBUF;
		
		switch(BUFFER[0])
		{
			case 0x77:				//ISP ?
				EA	= 0;
				WDTClear;
				xISPSLV	= 0x7c;
				xISPEN	= 0x93;
				PCON	= 1;
				break;
/*			case 0x00:			//EMH2A write&read
				switch(BUFFER_count){
					case 0x01:
						ReadAdr = BUFFER[1];
						xRXBBUF = GetEMH1A(ReadAdr);
						break;
					case 0x02:
						WriteScaler(BUFFER[1],BUFFER[2]);
						break;
					case 0x03:
						WriteScaler(BUFFER[1]+0x01,BUFFER[3]);
						break;
					default:break;
				}
				break;
			case 0x01:			//EMH2A read Register read
				if(BUFFER_count==1)
				{
					ReadAdr = BUFFER[1];
					xRXBBUF = ReadScaler(ReadAdr);
				}
				break;
			
			case 0x02:			//AD9884 device Read
				if(BUFFER_count==1)
				{
					ReadAdr = BUFFER[1];
					xRXBBUF = AD9884_Read(ReadAdr);//
				}
				else if(BUFFER_count>1)
				{
					WriteI2C(ADC_sysaddress,ReadAdr,BUFFER[BUFFER_count]);
					ReadAdr++;
				}
				break;
			case 0x03://EEPROM Bank "0"
				if(BUFFER_count==1)
				{
					ReadAdr = BUFFER[1];
					#ifndef	DVI_EDIDWrite
					xRXBBUF = EEPROM_Read(0x00FF&ReadAdr);//
					#else
					xRXBBUF = EEPROM_Read_02(0x00FF&ReadAdr);//
					#endif
				}
				else if(BUFFER_count>1)
				{
					#ifndef	DVI_EDIDWrite
					WriteI2C(EEPROM_sysaddress,ReadAdr,BUFFER[BUFFER_count]);
					#else
					WriteI2C(EEPROM_sysaddress_2402,ReadAdr,BUFFER[BUFFER_count]);
					#endif
					ReadAdr++;
				}
				break;
			
			case 0x04://EEPROM Bank "1"
				if(BUFFER_count==1)
				{
					ReadAdr = BUFFER[1];
					xRXBBUF = EEPROM_Read(0x0100|ReadAdr);//
				}
				else if(BUFFER_count>1)
				{
					WriteI2C(EEPROM_sysaddress|2,ReadAdr,BUFFER[BUFFER_count]);
					ReadAdr++;
				}
				break;
			
			case 0x05://EEPROM Bank "2"
				if(BUFFER_count==1)
				{
					ReadAdr = BUFFER[1];
					xRXBBUF = EEPROM_Read(0x0200|ReadAdr);//
				}
				else if(BUFFER_count>1)
				{
					WriteI2C(EEPROM_sysaddress|4,ReadAdr,BUFFER[BUFFER_count]);
					ReadAdr++;
				}
				break;
			
			case 0x06://EEPROM Bank "3"
				if(BUFFER_count==1)
				{
					ReadAdr = BUFFER[1];
					xRXBBUF = EEPROM_Read(0x0300|ReadAdr);//
				}
				else if(BUFFER_count>1)
				{
					WriteI2C(EEPROM_sysaddress|6,ReadAdr,BUFFER[BUFFER_count]);
					ReadAdr++;
				}
				break;
			
			case 0x07://EEPROM Bank "4"
				if(BUFFER_count==1)
				{
					ReadAdr = BUFFER[1];
					xRXBBUF = EEPROM_Read(0x0400|ReadAdr);//
				}
				else if(BUFFER_count>1)
				{
					WriteI2C(EEPROM_sysaddress|8,ReadAdr,BUFFER[BUFFER_count]);
					ReadAdr++;
				}
				break;
			
			case 0x08://EEPROM Bank "5"
				if(BUFFER_count==1)
				{
					ReadAdr = BUFFER[1];
					xRXBBUF = EEPROM_Read(0x0500|ReadAdr);//
				}
				else if(BUFFER_count>1)
				{
					WriteI2C(EEPROM_sysaddress|0x0A,ReadAdr,BUFFER[BUFFER_count]);
					ReadAdr++;
				}
				break;
			
			case 0x09://EEPROM Bank "6"
				if(BUFFER_count==1)
				{
					ReadAdr = BUFFER[1];
					xRXBBUF = EEPROM_Read(0x0600|ReadAdr);//
				}
				else if(BUFFER_count>1)
				{
					WriteI2C(EEPROM_sysaddress|0x0C,ReadAdr,BUFFER[BUFFER_count]);
					ReadAdr++;
				}
				break;
			
			case 0x0A://EEPROM Bank "7"
				if(BUFFER_count==1)
				{
					ReadAdr = BUFFER[1];
					xRXBBUF = EEPROM_Read(0x0700|ReadAdr);//
				}
				else if(BUFFER_count>1)
				{
					WriteI2C(EEPROM_sysaddress|0x0E,ReadAdr,BUFFER[BUFFER_count]);
					ReadAdr++;
				}
				break; 
			
			#ifdef MicomXFRbackup
			case	0x0B://MicomXFR, write only!
				if(BUFFER_count==1)
				{
					ReadAdr = BUFFER[1];
					xRXBBUF = xMicomBuffer[ReadAdr];
				}
				else if(BUFFER_count>1)
				{
					xdataptr=0xF00|ReadAdr;//point로...
					*xdataptr=BUFFER[BUFFER_count];
					ReadAdr++;
				}
				break;
				
			case	0x0C://MicomXFR, read/write
				if(BUFFER_count==1)
				{
					ReadAdr = BUFFER[1];
					xdataptr=0xF00|ReadAdr;
					xRXBBUF = *xdataptr;
				}
				else if(BUFFER_count>1)
				{
					xdataptr=0xF00|ReadAdr;
					*xdataptr=BUFFER[BUFFER_count];
					ReadAdr++;
				}
				break;	
			#endif
			
			case	0x0D://SAA7114 device Read
				if(BUFFER_count==1)
				{
					ReadAdr = BUFFER[1];
					#if defined(SAA7114)
					xRXBBUF = ReadI2C(SAA7114_sysaddress,ReadAdr);//
					#elif defined(SAA7115)
					xRXBBUF = ReadI2C(SAA7115_sysaddress,ReadAdr);//
					#elif defined(TW9908)
					xRXBBUF = ReadI2C(TW990x_SysAddr,ReadAdr);//
					#endif
				}
				else if(BUFFER_count>1)
				{
					#if defined(SAA7114)
					WriteI2C(SAA7114_sysaddress,ReadAdr,BUFFER[BUFFER_count]);
					#elif defined(SAA7115)
					WriteI2C(SAA7115_sysaddress,ReadAdr,BUFFER[BUFFER_count]);
					#elif defined(TW9908)
					WriteI2C(TW990x_SysAddr,ReadAdr,BUFFER[BUFFER_count]);
					#endif
					ReadAdr++;
				}
				break;
								
			case	0x0E:	//IntOSD reg. write  Row addr. 0x0f

				if(BUFFER_count==2)
				{
					{	
						#define	IN_ATTR_ROW0	0xA0
						#define	IN_CII_COL0	0x40

						void OSDSeqSend(BYTE Row,BYTE Col,BYTE Data,BYTE Count);
					
						OSDSeqSend(IN_ATTR_ROW0+15,IN_CII_COL0+BUFFER[1],BUFFER[2],1);
					}
				}
				break; */


			
		}
		BUFFER_count++;
		if(BUFFER_count > 4) BUFFER_count = 0;
	}

/*	if((xINTFLGI2C&0x80))		//Transmit interrupt flag check!(데이타 읽기 모드를 받으면 읽기(read)로 셋팅됨)
	{
		ReadAdr++;
		switch(BUFFER[0])
		{
			case 0x00:				//EMH2A read동작(단 백업 ram에서 읽어 보낸다.) 
				xRXBBUF = GetEMH1A(ReadAdr);
				break;
			
			case 0x01:				//EMH2A read register read동작
				xRXBBUF = ReadScaler(ReadAdr);
				break;
			
			case 0x02:				//AD9884 or 3 read동작
				xRXBBUF = AD9884_Read(ReadAdr);
				break;
				
			case 0x03://EEPROM Bank "0"
				#ifndef	DVI_EDIDWrite
				xRXBBUF = EEPROM_Read(ReadAdr);
				#else
				xRXBBUF=EEPROM_Read_02(ReadAdr);
				#endif
				break;
			
			case 0x04://EEPROM Bank "1"
				xRXBBUF = EEPROM_Read(0x0100|ReadAdr);//
				break;
			
			case 0x05://EEPROM Bank "2"
				xRXBBUF = EEPROM_Read(0x0200|ReadAdr);//
				break;
			
			case 0x06://EEPROM Bank "3"
				xRXBBUF = EEPROM_Read(0x0300|ReadAdr);//
				break;
			
			case 0x07://EEPROM Bank "4"
				xRXBBUF = EEPROM_Read(0x0400|ReadAdr);//
				break;
				
			case 0x08://EEPROM Bank "5"
				xRXBBUF = EEPROM_Read(0x0500|ReadAdr);//
				break;
			
			case 0x09://EEPROM Bank "6"
				xRXBBUF = EEPROM_Read(0x0600|ReadAdr);//
				break;
			
			case 0x0a://EEPROM Bank "7"
				xRXBBUF = EEPROM_Read(0x0600|ReadAdr);//
				break;	
			
			#ifdef MicomXFRbackup
			case 0x0b://Micom XFR write only!
				xRXBBUF = xMicomBuffer[ReadAdr];
				break;
			
			case 0x0c://Micom XFR read/write
				xdataptr=0xF00|ReadAdr;
				xRXBBUF = *xdataptr;
				break;
			#endif
			
			case 0x0D:				//SAA7114 read
				#if defined(SAA7114)
				xRXBBUF = ReadI2C(SAA7114_sysaddress,ReadAdr);
				#elif defined(SAA7115)
				xRXBBUF = ReadI2C(SAA7115_sysaddress,ReadAdr);
				#elif defined(TW9908)
				xRXBBUF = ReadI2C(TW990x_SysAddr,ReadAdr);
				#endif
				break;
			
			default:
				break;
		}
		
	} */
	xINTFLGI2C = 0x00;		//인터럽트루틴안에 오면 0x03레지스터 비트를 지워라,Datasheet참조도 할것.
	xINTFLG	= 0x00;			//레지스터를 클리어 하고 빠진다. 싱크관련 인터럽트이므로 retfi하면 곧바로 들어오는걸 방지
#endif
}

/////////////////////////////////////////////////////////////////////
//	Timer "1" interrupt routine
/////////////////////////////////////////////////////////////////////
#ifdef USE_remocon
void timer1() interrupt 3
{
	++RemoteShortTimer;
	if(RemoteShortTimer>=0xFF) RemoteShortTimer=0xFF;//overflow prevent!
	Timer1Set;//Timer1 set!
	
	#ifndef BtcBoard_Option	
	if(!SCDT) SCDT_LOWBackup=1;//if(SCDT_LOWBackup&&SCDT)--->rising
	else SCDT_HIGHBackup=1;//if(SCDT_HIGHBackup&&!SCDT)--->falling
	#endif
}
#endif

#endif
