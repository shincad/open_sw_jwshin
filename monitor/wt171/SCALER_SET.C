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
#include	"EEPROMadr.h"
#include	"POWER.H"
#include	"TVMODE.h"
#include	"VideoParameter.h"
#include "extern.h"
#include "sprocessor.h"
#include	"btc_osdmenu.h"
#include "tuner.h"
#include "tools.h"

#if	defined(MCU_MTV230)
#include	"MTV230xfr.h"
#elif		defined(MCU_MTV412)
#include	"MTV412xfr.h"
#elif	defined(MCU_NT68F63)
#include	"NT68F63.h"
#endif

#if	defined(BtcBoard_Option) 
void 	 AVDecoderSleep(void);
#endif

//****************************************************************//
//함수선언
//****************************************************************//
void SetLinerate(BYTE Recdata);
BYTE EEPROM_Read(WORD address);
void EepromSetQue(WORD address, BYTE Recdata);
bit WriteI2C(BYTE sysaddr, BYTE subaddr, BYTE writedata);

//함수선언-프로그램순서
double ExtractCLK(BYTE Recdata);
void SetScalerInputOutputColorCondition(BYTE Recdata);
void SetScalerInputCondition(BYTE Recdata);
void SetScalerInputIBRQS(BYTE Recdata);
void SetScalerInputActive(BYTE Recdata);
void SetScalerInputHVLock(BYTE Recdata);
void SetScalerHPostion(BYTE Recdata);
void SetScalerVPostion(BYTE Recdata);
void SetScalerDclkPLL(double Clock);
void SetScalerMclkPLL(double Clock);
void SetScalerFMuse(BYTE Recdata);
void SetScalerFMothers(BYTE Recdata);
void SetScalerZoomFactor(BYTE Recdata);
void SetScalerOutputHVLockLoad(BYTE Recdata);
void SetScalerOutputHVTotal(BYTE Recdata);
void SetScalerOutputOREQSTART(BYTE Recdata);
void SetScalerPIPOutputCondition(BYTE Recdata);
void 	PutVolumePWM();
extern	void PipPositionService(void);
void		DelayNOP20();

//****************************************************************//
//변수선언
//****************************************************************//

#if defined(MCU_MTV230)||defined(MCU_NT68F63)
extern	xdata	BYTE	xRAM[MaxBufferSize][2];
extern	xdata	BYTE	xEEPROMBuffer[MaxEepromBuffer];
#elif defined(MCU_MTV412)
extern	xdata	BYTE	xRAM[MaxBufferSize][2];
extern	xdata	BYTE	xEEPROMBuffer[MaxEepromBuffer];
#endif

extern	WORD	PowerOnTimer;
extern	BYTE	PowerOnsequence;
extern	bit		VideoActiveCompleted;
extern	BYTE	CurrentFunction;
extern	BYTE	OSDstatus;
extern	BYTE	SyncStableTimer;
extern	bit	PipOnOffFlag;
extern	BYTE	AsicBufferQue;
extern	BYTE	AsicQuepointer;
extern code ModeTable ModeList[];
extern	BYTE	CurrentMode;
extern	WORD	NowHfreq;
extern	bit		YouHaveToInitTVchannel;

#if defined(INT_EXTOSD)		//2003-07-02 7:28오후
extern	WORD	idata NowVactive;
extern	WORD	idata NowHtotal;
#else 
extern	WORD	 NowVactive;
extern	WORD	 NowHtotal;
#endif

extern	DWORD idata NowVideoCLK;
extern	DWORD idata	NowAdcCLK;
extern	DWORD idata	NowScalerDCLK;
extern	DWORD idata	NowScalerMCLK;
extern	BYTE xdata SoundMuteTvTimer;

#ifdef	CheckVideoStatus
extern	bit		NowVideo50Hz;
#endif

extern	BYTE	TunerProcessing;
extern	bit	PipFastChange;
extern	BYTE	OSDWindows;
extern	BYTE	OSDcharacters;
extern	bit		SoundMuteOnFlag;
//extern	BYTE 	idata MenuNum;//test

BYTE TW990xRead(BYTE SubAddr);	//2003-08-19


BYTE	bdata	EMH1A_data;
sbit  EMH1ABIT7	=EMH1A_data^7;          
sbit  EMH1ABIT6 =EMH1A_data^6;          
sbit  EMH1ABIT5 =EMH1A_data^5;          
sbit  EMH1ABIT4 =EMH1A_data^4;          
sbit  EMH1ABIT3 =EMH1A_data^3;          
sbit  EMH1ABIT2 =EMH1A_data^2;          
sbit  EMH1ABIT1 =EMH1A_data^1;          
sbit  EMH1ABIT0 =EMH1A_data^0;      


/////////////////////////////////////////////////////////////////////
//	Backup register(마이컴에 백업시킨다.)
/////////////////////////////////////////////////////////////////////
void PutEMH2(BYTE address, BYTE Recdata)		
{
#if defined(MCU_MTV230)||defined(MCU_NT68F63)||defined(MCU_MTV412)
	if(address<0x80)	xRAM[address][0] = Recdata;
	else 			xRAM[address-0x80][1] = Recdata;
#endif	
}


/////////////////////////////////////////////////////////////////////
//	Load register data
/////////////////////////////////////////////////////////////////////
BYTE GetEMH1A(BYTE address)
{
	BYTE RetData=0;

#if defined(MCU_MTV230)||defined(MCU_NT68F63)||defined(MCU_MTV412)
	if(address<0x80)	RetData = xRAM[address][0];
	else 				RetData = xRAM[address-0x80][1];
	return(RetData);
#endif
}


/////////////////////////////////////////////////////////////////////
// 4bit? nibble통신
/////////////////////////////////////////////////////////////////////
#ifdef	USE_4BitInterface				

void WriteScalerNibble(BYTE Recdata)
{
	EMH1A_data = Recdata;
	
	IOPD3 = EMH1ABIT7;				//상위nibble
	IOPD2 = EMH1ABIT6;
	IOPD1 = EMH1ABIT5;
	IOPD0 = EMH1ABIT4;
	NOP;
	SCLK = 0;
	NOP;
	SCLK = 1;
	NOP;
	
	IOPD3 = EMH1ABIT3;				//하위nibble
	IOPD2 = EMH1ABIT2;
	IOPD1 = EMH1ABIT1;
	IOPD0 = EMH1ABIT0;	
	NOP;
	SCLK = 0;
	NOP;
	SCLK = 1;	
}

void WriteReg4bit(BYTE address, BYTE Recdata)
{
	_SCALER_CS_LOW;

	DelayNOP20();
	
	IOPD3 = 1;						//Write Adr Cmd
	IOPD2 = 1;
	IOPD1 = 0;
	IOPD0 = 0;
	
	NOP;
	SCLK = 0;
	NOP;
	SCLK = 1;
	NOP;
	
	WriteScalerNibble(address);		//Adr

	IOPD3 = 0;						//Write Dat Cmd
	IOPD2 = 0;
	IOPD1 = 0;
	IOPD0 = 0;
	
	NOP;
	SCLK = 0;
	NOP;
	SCLK = 1;
	NOP;

	WriteScalerNibble(Recdata);		//Dat
	DelayNOP20();
	_SCALER_CS_HIGH;

	PutEMH2(address,Recdata);			//Read/Write 가 안된다, backup받는다, 나중에 비트 혹은 특정데이타를 사용할때 읽어서 마스킹후 쓰기 위해
}

BYTE ReadScalerParallel(BYTE address)
{
	_SCALER_CS_LOW;
	DelayNOP20();
	
	IOPD3 = 1;						//Read Adr Cmd
	IOPD2 = 0;
	IOPD1 = 0;
	IOPD0 = 0;
	
	NOP;
	SCLK = 0;
	NOP;
	SCLK = 1;
	NOP;
	
	WriteScalerNibble(address);		//Adr

	SCLK = 0;						//Dummy Read
	NOP;
	EMH1ABIT7 = IOPD3;
	EMH1ABIT6 = IOPD2;
	EMH1ABIT5 = IOPD1;
	EMH1ABIT4 = IOPD0;
	NOP;
	SCLK = 1;
		
	SCLK = 0;						//high nibble
	NOP;
	EMH1ABIT7 = IOPD3;
	EMH1ABIT6 = IOPD2;
	EMH1ABIT5 = IOPD1;
	EMH1ABIT4 = IOPD0;
	NOP;
	SCLK = 1;

	SCLK = 0;						//low nibble
	NOP;
	EMH1ABIT3 = IOPD3;
	EMH1ABIT2 = IOPD2;
	EMH1ABIT1 = IOPD1;
	EMH1ABIT0 = IOPD0;
	NOP;
	SCLK = 1;
	
	
	DelayNOP20();
	
	_SCALER_CS_HIGH;
	return(EMH1A_data);
}
#define	WriteScaler(val1,val2) WriteReg4bit(val1,val2)
#define	ReadScaler	ReadScalerParallel


/////////////////////////////////////////////////////////////////////
//	//1bit serial통신
/////////////////////////////////////////////////////////////////////
#else	
void WriteScalerSerial(BYTE Recdata)
{
/*
값을 bdata EMH1A_data로 대입하고,
각각 비트를 포트에 대입한다.
*/

	EMH1A_data = Recdata;		//상위 nibble만 전송.

	IOPD0 = EMH1ABIT7;
	NOP;
	SCLK =0;
	NOP;
	SCLK =1;	

	IOPD0 = EMH1ABIT6;	
	NOP;
	SCLK =0;
	NOP;
	SCLK =1;	

	IOPD0 = EMH1ABIT5;
	NOP;
	SCLK =0;
	NOP;
	SCLK =1;	

	IOPD0 = EMH1ABIT4;
	NOP;
	SCLK =0;
	NOP;
	SCLK =1;	
}

void WriteReg1bit(BYTE address, BYTE Recdata)
{
	_SCALER_CS_LOW;
	DelayNOP20();
	WriteScalerSerial(0xC0);		//Adr Cmd
	WriteScalerSerial(address);		//Adr
	WriteScalerSerial(address<<4);		//Adr

	WriteScalerSerial(0x00);		//Dat Cmd 
	WriteScalerSerial(Recdata);		//Dat
	WriteScalerSerial(Recdata<<4);		//Dat
	DelayNOP20();
	_SCALER_CS_HIGH;
	SDA = 1;//2003-02-14 10:02오전, 강제로 High를 해둔다.왜녀면 I2C data라인과 공통라인이므로..
	PutEMH2(address,Recdata);			//Read/Write 가 안된다, backup받는다, 나중에 비트 혹은 특정데이타를 사용할때 읽어서 마스킹후 쓰기 위해
}										//1bit serial통신

BYTE ReadScalerSerial(BYTE address)
{
	_SCALER_CS_LOW;
	DelayNOP20();
	IOPD0 = 1;		//Cmd 0x8
	NOP;
	SCLK =0;
	NOP;
	SCLK =1;	

	IOPD0 = 0;	
	NOP;
	SCLK =0;
	NOP;
	SCLK =1;	

	IOPD0 = 0;
	NOP;
	SCLK =0;
	NOP;
	SCLK =1;	

	IOPD0 = 0;
	NOP;
	SCLK =0;
	NOP;
	SCLK =1;		
	
	WriteScalerSerial(address);
	WriteScalerSerial(address<<4);
	
	//NOPx6;
	
//////////////////////////////////////////////////////Dummy Read
	SCLK =0;
	NOP;
	EMH1ABIT7 = IOPD1;
	SCLK =1;		

	SCLK =0;
	NOP;
	EMH1ABIT6 = IOPD1;
	SCLK =1;		
	
	SCLK =0;
	NOP;
	EMH1ABIT5 = IOPD1;
	SCLK =1;
	
	SCLK =0;
	NOP;
	EMH1ABIT4 = IOPD1;
	SCLK =1;
//////////////////////////////////////////////////////
	
	SCLK =0;
	NOP;
	EMH1ABIT7 = IOPD1;
	SCLK =1;		

	SCLK =0;
	NOP;
	EMH1ABIT6 = IOPD1;
	SCLK =1;		
	
	SCLK =0;
	NOP;
	EMH1ABIT5 = IOPD1;
	SCLK =1;
	
	SCLK =0;
	NOP;
	EMH1ABIT4 = IOPD1;
	SCLK =1;
	
	SCLK =0;
	NOP;
	EMH1ABIT3 = IOPD1;
	SCLK =1;
	
	SCLK =0;
	NOP;
	EMH1ABIT2 = IOPD1;
	SCLK =1;
	
	SCLK =0;
	NOP;
	EMH1ABIT1 = IOPD1;
	SCLK =1;
	
	SCLK =0;
	NOP;
	EMH1ABIT0 = IOPD1;
	SCLK =1;
	
	DelayNOP20();
	_SCALER_CS_HIGH;
	return(EMH1A_data);
}

#define	WriteScaler(val0, val1) WriteReg1bit(val0, val1)
#define	ReadScaler	ReadScalerSerial
#endif


////////////////////////////////////////////////////////////////////////////
//
//	OSD comm
//	
////////////////////////////////////////////////////////////////////////////
#if defined	InternalOSD||defined(INT_EXTOSD)
#ifdef	USE_4BitInterface	//--------------------------------//nibble
void WriteScalerNibble(BYTE Recdata);	//4비트 통신 함수선언

void WriteOsdAdr4bit(BYTE address)	//address
{
	IOPD3 = 0;						//Write Adr Cmd
	IOPD2 = 0;
	IOPD1 = 0;
	IOPD0 = 1;
	NOP;
	SCLK = 0;
	NOP;
	SCLK = 1;
	NOP;
	WriteScalerNibble(address);	
}
void WriteOsdDat4bit(BYTE Recdata)	//data
{
	IOPD3 = 0;						//Write Dat Cmd
	IOPD2 = 0;
	IOPD1 = 0;
	IOPD0 = 0;
	NOP;
	SCLK = 0;
	NOP;
	SCLK = 1;
	NOP;
	WriteScalerNibble(Recdata);
}

#else	//-----------------------------------------------------	//serial
void WriteScalerSerial(BYTE Recdata);	//1비트 통신 함수선언


void WriteOsdAdr1bit(BYTE Recdata)
{
	WriteScalerSerial(0x10);		//Adr Cmd
	WriteScalerSerial(Recdata);		//Adr
	WriteScalerSerial(Recdata<<4);		//Adr
}

void WriteOsdDat1bit(BYTE Recdata)
{
	WriteScalerSerial(0x00);		//Dat Cmd
	WriteScalerSerial(Recdata);		//Adr
	WriteScalerSerial(Recdata<<4);		//Adr
}

#endif
#endif	//-----------------------------------------------------

/*
BitArry형태
#define	Bit7th	0x80
#define	Bit6th	0x40
#define	Bit5th	0x20
#define	Bit4th	0x10
#define	Bit3rd	0x08
#define	Bit2nd	0x04
#define	Bit1st	0x02
#define	Bit0ze	0x01
ex)
Address 0x38register에 비트0,1,2각각 "1"로 셋팅하고자 한다면
BitWriteScalerParallel(0x38,Bit0ze|Bit1st|Bit2nd,1);

ex)
Address 0x38register에 비트0만 "0"으로 셋팅하고자 한다면
BitWriteScalerParallel(0x38,Bit0ze,0);
*/

void BitWriteScaler(BYTE address, BYTE BitArry, BYTE Recdata)
{
	BYTE temp = GetEMH1A(address);
	
	if(Recdata)
	{
		if(BitArry&Bit7th) temp = temp|Bit7th;
		if(BitArry&Bit6th) temp = temp|Bit6th;
		if(BitArry&Bit5th) temp = temp|Bit5th;
		if(BitArry&Bit4th) temp = temp|Bit4th;
		if(BitArry&Bit3rd) temp = temp|Bit3rd;
		if(BitArry&Bit2nd) temp = temp|Bit2nd;
		if(BitArry&Bit1st) temp = temp|Bit1st;
		if(BitArry&Bit0ze) temp = temp|Bit0ze;
	}
	else
	{
		if(BitArry&Bit7th) temp = temp&~Bit7th;
		if(BitArry&Bit6th) temp = temp&~Bit6th;
		if(BitArry&Bit5th) temp = temp&~Bit5th;
		if(BitArry&Bit4th) temp = temp&~Bit4th;
		if(BitArry&Bit3rd) temp = temp&~Bit3rd;
		if(BitArry&Bit2nd) temp = temp&~Bit2nd;
		if(BitArry&Bit1st) temp = temp&~Bit1st;
		if(BitArry&Bit0ze) temp = temp&~Bit0ze;
	}
	WriteScaler(address,temp);
}

/*
Word 데이타중에서	상위8비트는 어드레스
					하위8비트는 어드레스+1
*/
void WordWriteScaler(BYTE address, WORD Recdata)
{
	WriteScaler(address,	(BYTE)(Recdata>>8));
	WriteScaler(address+1,	(BYTE)(Recdata>>0));
}

#ifdef	USE_4BitInterface

void WriteDummy(BYTE Recdata){
	EMH1A_data = Recdata;		//상위 nibble만 전송.

	IOPD0 = EMH1ABIT7;
	NOP;
	SCLK =0;
	NOP;
	SCLK =1;	

	IOPD0 = EMH1ABIT6;	
	NOP;
	SCLK =0;
	NOP;
	SCLK =1;	

	IOPD0 = EMH1ABIT5;
	NOP;
	SCLK =0;
	NOP;
	SCLK =1;	

	IOPD0 = EMH1ABIT4;
	NOP;
	SCLK =0;
	NOP;
	SCLK =1;	
}
	
void ScalerParallelMode(void)
{
	_SCALER_CS_LOW;

	DelayNOP20();
	WriteDummy(0xC0);		//Adr Cmd
	WriteDummy(0xA9);		//Adr(0xA9 -> 0xA0|0x90 nibble로 분리..
	WriteDummy(0xA9<<4);	//Adr

	WriteDummy(0x00);		//Dat Cmd 
	WriteDummy(0x80);		//Dat (0x40 -> 0x40|0x00 nibble로 분리..
	WriteDummy(0x80<<4);	//Dat

	_SCALER_CS_HIGH;
}
#endif


//****************************************************************//
//PIP SUB regisiter setting!!
//****************************************************************//
void PipSubRegisterSet(void)
{
	//PIP setting!!
	ExtractCLK(xEEPROMBuffer[MainSubInputSource]);
	//SetScalerDclkPLL(xEEPROMBuffer[MainSubInputSource]);	//2004-07-06//Dclk PLL set!//PTK_031128_70Hz이상 화면 깨지는현상때문에 풀어놓음
	SetScalerInputIBRQS(xEEPROMBuffer[MainSubInputSource]);
	SetScalerInputCondition(xEEPROMBuffer[MainSubInputSource]);
	SetScalerHPostion(xEEPROMBuffer[MainSubInputSource]);
	SetScalerVPostion(xEEPROMBuffer[MainSubInputSource]);
	SetScalerInputActive(xEEPROMBuffer[MainSubInputSource]);
	SetScalerOutputHVTotal(xEEPROMBuffer[MainSubInputSource]);//
	SetScalerFMothers(xEEPROMBuffer[MainSubInputSource]);
	SetScalerOutputOREQSTART(xEEPROMBuffer[MainSubInputSource]);
	SetScalerFMuse(xEEPROMBuffer[MainSubInputSource]);//
//test2004-07-06	SetScalerPIPOutputCondition(xEEPROMBuffer[MainSubInputSource]);//PIP
	#ifdef	PipDpmsON	//r+ c/sv/tv 경우
	if(~DpmsPipFlag) 	MUTEOFF;//2003-10-21
	#else
	MUTEOFF;
	#endif
}




/*
50<->60Hz변경시 고려사항
1. Zoom Factor
2. B-input V-active size
3. B-channel V-Position
4. SAA7114 vertical window length
5. 50Hz SAA7114 setting value
*/

//****************************************************************//
//Change Video 50Hz<->60Hz
//****************************************************************//
#ifdef	CheckVideoStatus
void ChangeToVideo50Hz60HzSystem(void)
{
	if(NowVideo50Hz)//50Hz로...
	{
		//display still!!(화면불안정 방지)
		BitWriteScaler(0xAA,0x08,1);
		
		BitWriteScaler(0x25,0x20,1);
		//Zoom Factor
		switch(xEEPROMBuffer[MainSubInputSource])
		{
			case	10://composite framesync
			case	14://s-video framesync
			case	18://tuner framesync
				#ifndef USE_NTSCtuner	//pal
				if(DisplayAspectRatioNum&0x03==aspect4_3)
				{
					// 4:3 ----------------------------------------------------------------------------
					WriteScaler(0x3B, 0x0A); // Scale Mode 0x1a: -> Random, Zomm Down
					
					WriteScaler(0x35,  (DWORD) ((((DWORD)BIHAW)<<16) / (DWORD)PanelHerizontalsize)>>16);
					WordWriteScaler	(0x36,	((((DWORD)BIHAW)<<16) / (DWORD)PanelHerizontalsize));
					
					WriteScaler(0x38,  ((((DWORD)(280)*2)<<16) / (DWORD)PanelVerticalsize*(3/4))>>16);
					WordWriteScaler	(0x39, ((((DWORD)(280)*2)<<16) / (DWORD)PanelVerticalsize*(3/4)));
					//---------------------------------------------------------------------------------
				}
				else if(DisplayAspectRatioNum&0x03==aspect16_9)
				{
					// 16:9 ---------------------------------------------------------------------------
					WriteScaler(0x3B, 0x0A); // Scale Mode 0x1a: -> Random, Zomm Down
					
					WriteScaler(0x35,  (DWORD) ((((DWORD)BIHAW)<<16) / (DWORD)PanelHerizontalsize)>>16);
					WordWriteScaler	(0x36,	((((DWORD)BIHAW)<<16) / (DWORD)PanelHerizontalsize));
					
					WriteScaler(0x38,  ((((DWORD)(280)*2)<<16) / (DWORD)PanelVerticalsize*(9/16))>>16);
					WordWriteScaler	(0x39,	((((DWORD)(280)*2)<<16) / (DWORD)PanelVerticalsize*(9/16)));	
					//---------------------------------------------------------------------------------
				}
				else if(DisplayAspectRatioNum&0x03==aspect_full)
				{
					#if defined(FullScaleToVertical)	// 입력을 판넬에 꽉차게
					// normal ----------------------------------------------------------------------------
					WriteScaler(0x3B, 0x0A); // Scale Mode 0x1a: -> Random, Zomm Down
					
					WriteScaler(0x35,  (DWORD) ((((DWORD)BIHAW)<<16) / (DWORD)PanelHerizontalsize)>>16);	//OH_factor
					WordWriteScaler	(0x36,	((((DWORD)BIHAW)<<16) / (DWORD)PanelHerizontalsize));
					
					WriteScaler(0x38,  ((((DWORD)(280)*2)<<16) / (DWORD)PanelVerticalsize)>>16);		//OV_factor
					WordWriteScaler	(0x39,	((((DWORD)(280)*2)<<16) / (DWORD)PanelVerticalsize));	
					//---------------------------------------------------------------------------------
					#else	//2003-08-13,	판넬의 높이(V)에 맞추어 출력보정함.(4:3비율)
					// normal ----------------------------------------------------------------------------
					WriteScaler(0x3B, 0x0A); // Scale Mode 0x1a: -> Random, Zomm Down
					
					WriteScaler(0x35,  (DWORD) ((((DWORD)BIHAW)<<16) / (DWORD)PanelVerticalsize*(4/3))>>16);	//OH_factor
					WordWriteScaler	(0x36,	((((DWORD)BIHAW)<<16) / (DWORD)PanelVerticalsize*(4/3)));
					
					WriteScaler(0x38,  ((((DWORD)(280)*2)<<16) / (DWORD)PanelVerticalsize)>>16);		//OV_factor
					WordWriteScaler	(0x39,	((((DWORD)(280)*2)<<16) / (DWORD)PanelVerticalsize));	
					//---------------------------------------------------------------------------------
					#endif
				}
				/*
				WriteScaler(0x3B, 0x0A); // Scale Mode 0x1a: -> Random, Zomm Down
				WriteScaler		(0x35,  (DWORD) ((((DWORD)700)<<16) / PanelHerizontalsize)>>16);
//youngdo 2003.5.23				WordWriteScaler	(0x36,	(DWORD) ((((DWORD)700)<<16) / PanelHerizontalsize));
				WordWriteScaler	(0x36,	 0x80a0);
				WriteScaler		(0x38,  (DWORD)((((DWORD)250*2)<<16) / PanelVerticalsize)>>16);
//youngdo 2003.5.23					WordWriteScaler	(0x39,	(DWORD)((((DWORD)250*2)<<16) / PanelVerticalsize));	
				WordWriteScaler	(0x39,	0x8a50);	

				WriteScaler(0x3B, 0x0A); // Scale Mode 0x1a: -> Random, Zomm Down
				*/
				#else	//ntsc
				
				if(DisplayAspectRatioNum&0x03==aspect4_3)
				{
					// 4:3 ----------------------------------------------------------------------------
					WriteScaler(0x3B, 0x0A); // Scale Mode 0x1a: -> Random, Zomm Down
					
					WriteScaler(0x35,  (DWORD) ((((DWORD)BIHAW)<<16) / (DWORD)PanelHerizontalsize)>>16);
					WordWriteScaler	(0x36,	((((DWORD)BIHAW)<<16) / (DWORD)PanelHerizontalsize));
					
					WriteScaler(0x38,  ((((DWORD)(280)*2)<<16) / (DWORD)PanelVerticalsize*(3/4))>>16);
					WordWriteScaler	(0x39, ((((DWORD)(280)*2)<<16) / (DWORD)PanelVerticalsize*(3/4)));	
					//---------------------------------------------------------------------------------
				}
				else if(DisplayAspectRatioNum&0x03==aspect16_9)
				{
					// 16:9 ---------------------------------------------------------------------------
					WriteScaler(0x3B, 0x0A); // Scale Mode 0x1a: -> Random, Zomm Down
					
					WriteScaler(0x35,  (DWORD) ((((DWORD)BIHAW)<<16) / (DWORD)PanelHerizontalsize)>>16);
					WordWriteScaler	(0x36,	((((DWORD)BIHAW)<<16) / (DWORD)PanelHerizontalsize));
					
					WriteScaler(0x38,  ((((DWORD)(280)*2)<<16) / (DWORD)PanelVerticalsize*(9/16))>>16);
					WordWriteScaler	(0x39,	((((DWORD)(280)*2)<<16) / (DWORD)PanelVerticalsize*(9/16)));	
					//---------------------------------------------------------------------------------
				}
				else if(DisplayAspectRatioNum&0x03==aspect_full)
				{
					#if defined(FullScaleToVertical)	// 입력을 판넬에 꽉차게
					// normal ----------------------------------------------------------------------------
					WriteScaler(0x3B, 0x0A); // Scale Mode 0x1a: -> Random, Zomm Down
					
					WriteScaler(0x35,  (DWORD) ((((DWORD)BIHAW)<<16) / (DWORD)PanelHerizontalsize)>>16);	//OH_factor
					WordWriteScaler	(0x36,	((((DWORD)BIHAW)<<16) / (DWORD)PanelHerizontalsize));
					
					WriteScaler(0x38,  ((((DWORD)(280)*2)<<16) / (DWORD)PanelVerticalsize)>>16);		//OV_factor
					WordWriteScaler	(0x39,	((((DWORD)(280)*2)<<16) / (DWORD)PanelVerticalsize));	
					//---------------------------------------------------------------------------------
					#else	//2003-08-13,	판넬의 높이(V)에 맞추어 출력보정함.(4:3비율)
					// normal ----------------------------------------------------------------------------
					WriteScaler(0x3B, 0x0A); // Scale Mode 0x1a: -> Random, Zomm Down
					
					WriteScaler(0x35,  (DWORD) ((((DWORD)BIHAW)<<16) / (DWORD)PanelVerticalsize*(4/3))>>16);	//OH_factor
					WordWriteScaler	(0x36,	((((DWORD)BIHAW)<<16) / (DWORD)PanelVerticalsize*(4/3)));
					
					WriteScaler(0x38,  ((((DWORD)(280)*2)<<16) / (DWORD)PanelVerticalsize)>>16);		//OV_factor
					WordWriteScaler	(0x39,	((((DWORD)(280)*2)<<16) / (DWORD)PanelVerticalsize));	
					//---------------------------------------------------------------------------------
					#endif
				}
				#endif
				
				break;	
			default:
				break;
		}
		
		//B-Channel Input active 
		switch(xEEPROMBuffer[MainSubInputSource])
		{
			case	8://composite linesync
			case	10://composite framesync
			case	12://s-video linesync
			case	14://s-video framesync
			case	16://tuner linesync
			case	18://tuner framesync
				//#ifndef USE_NTSCtuner
				//WordWriteScaler(0xA0,BIHAW);
				//WordWriteScaler(0xA6,280);//**critical issue!!
				//#else
				
				if(DisplayAspectRatioNum&0x03==aspect4_3)	//모두같음
				{
					WordWriteScaler(0xA0,BIHAW);
					WordWriteScaler(0xA6,(280)*2);
				}
				else if(DisplayAspectRatioNum&0x03==aspect16_9)
				{
					WordWriteScaler(0xA0,BIHAW);
					WordWriteScaler(0xA6,(280)*2);
				}
				else if(DisplayAspectRatioNum&0x03==aspect_full)
				{
					#if defined(FullScaleToVertical)	// 입력을 판넬에 꽉차게
					WordWriteScaler(0xA0,BIHAW);
					#else					//2003-08-13,	판넬의 높이(V)에 맞추어 출력보정함.(4:3비율)				
					WordWriteScaler(0xA0,BIHAW);
					#endif
					
					WordWriteScaler(0xA6,(280)*2);
				}
				//#endif
				break;			
			case	20://RGB+COMPOSITE(PIP)
			case	28://RGB+S-VIDEO(PIP)
			case	52://RGB+TUNER(PIP)
			case	36://DVI+COMPOSITE
			case	44://DVI+SIVIDEO
			case	60://DVI+TUNER
				//PAL/SECAM에서는 PIP가 작거나,크거나 관계가 없다.
				//#ifndef USE_NTSCtuner
				//WordWriteScaler(0xA0,BIHAW);
				//WordWriteScaler(0xA6,280);
				//#else
				
				switch(xEEPROMBuffer[PIPSIZE_buf]&0x03)
				{
					case SizeLarge://Large PIP size
						WordWriteScaler(0xA0,BIHAW);	//H
						WordWriteScaler(0xA6,280+1);	//V
						break;
					
					case SizeMiddle://Middle PIP size
						WordWriteScaler(0xA0,BIHAW);	//H
						WordWriteScaler(0xA6,280+1);	//V
						break;
					
					case SizeSmall://small PIP size
						WordWriteScaler(0xA0,BIHAW);
						WordWriteScaler(0xA6,280+1);
						break;
				}
				break;
				//#endif
			default:
				break;
		}
		
		//B-Channel H-position
		switch(xEEPROMBuffer[MainSubInputSource])
		{
			case	8://composite linesync
			case	10://composite framesync
			case	12://s-video linesync
			case	14://s-video framesync
			case	16://tuner linesync
			case	18://tuner framesync
				//#ifndef USE_NTSCtuner
				//WordWriteScaler(0x9e,IBHAS_Main50Hz_value);	//Bchannel IHAS
				//#else
				
				#ifdef Memory_1eaUse
				WordWriteScaler(0x9e,IBHAS_Main50Hz_value+2);	//Bchannel IHAS	
										//ram1개일때 노이즈로 인해 넓이를 2~4정도 줄였기 때문에 그에 대한 보정.(확대위해)
				#else
				switch(xEEPROMBuffer[DisplayAspcet_buf])
				{			//모두 같음
					case aspect4_3:\
						WordWriteScaler(0x9e,IBHAS_Main50Hz_value);	//Bchannel IHAS
						break;		
					case aspect16_9:
						WordWriteScaler(0x9e,IBHAS_Main50Hz_value);	//Bchannel IHAS 
						break;		
					case aspect_full:
						#if defined(FullScaleToVertical)	// 입력을 판넬에 꽉차게
							WordWriteScaler(0x9e,IBHAS_Main50Hz_value);	//Bchannel IHAS 
						#else					//2003-08-13,	판넬의 높이(V)에 맞추어 출력보정함.(4:3비율)
							WordWriteScaler(0x9e,IBHAS_Main50Hz_value+22);	//Bchannel IHAS 
						#endif
						break;		
				}
				//#endif
				#endif
				break;

				
			case	20://RGB+COMPOSITE(PIP)
			case	28://RGB+S-VIDEO(PIP)
			case	52://RGB+TUNER(PIP)
			case	36://DVI+COMPOSITE
			case	44://DVI+SIVIDEO
			case	60://DVI+TUNER
				WordWriteScaler(0x9e,IBHAS_Main50Hz_value);	//Bchannel IHAS
				break;
		}
		
		//B-Channel V-position
		switch(xEEPROMBuffer[MainSubInputSource])
		{
			case	8://composite linesync
			case	10://composite framesync
			case	12://s-video linesync
			case	14://s-video framesync
			case	16://tuner linesync
			case	18://tuner framesync
				WordWriteScaler(0xa2,IBVAS_Main50Hz_value);
				WordWriteScaler(0xa4,IBVAS_Main50Hz_value);
				break;
			
			case	20://RGB+COMPOSITE(PIP)
			case	28://RGB+S-VIDEO(PIP)
			case	52://RGB+TUNER(PIP)
			case	36://DVI+COMPOSITE
			case	44://DVI+SIVIDEO
			case	60://DVI+TUNER
//				#ifndef USE_NTSCtuner		//pal
						WordWriteScaler(0xa2,IBVAS_Main50Hz_value);		//Odd!!,  //Bchannel IVAS
						WordWriteScaler(0xa4,IBVAS_Main50Hz_value);		//Even!!  //Bchannel IVAS
//				#else	//ntsc
//						WordWriteScaler(0xa2,IBVAS_Main60Hz_value);		//Odd!!,  //Bchannel IVAS
//						WordWriteScaler(0xa4,IBVAS_Main60Hz_value);		//Even!!  //Bchannel IVAS
				/*
				switch(xEEPROMBuffer[PIPSIZE_buf]&0x03)
				{
					case SizeLarge://Large PIP size
						WordWriteScaler(0xa2,IBVAS_Main60Hz_value);		//Odd!!,  //Bchannel IVAS
						WordWriteScaler(0xa4,IBVAS_Main60Hz_value);		//Even!!  //Bchannel IVAS
						break;
					
					case SizeMiddle://middle PIP size
						WordWriteScaler(0xa2,IBVAS_Main60Hz_value);		//Odd!!,  //Bchannel IVAS
						WordWriteScaler(0xa4,IBVAS_Main60Hz_value);		//Even!!  //Bchannel IVAS
						break;

					case SizeSmall://small PIP size
						WordWriteScaler(0xa2,IBVAS_Main60Hz_value);		//Odd!!,  //Bchannel IVAS
						WordWriteScaler(0xa4,IBVAS_Main60Hz_value);		//Even!!  //Bchannel IVAS
						break;

				}
				*/
//				#endif
				break;
		}
		
		//SAA7114 50Hz,60Hz default value
		switch(xEEPROMBuffer[TVMODE])
		{
			#if defined(USE_NTSCtuner)
			case NTSC_AIR://air
			case NTSC_CATV://catv
				#if defined(SAA7114)
				WriteI2C(SAA7114_sysaddress,0x0E,0x01);
				#elif defined(SAA7115)
				WriteI2C(SAA7115_sysaddress,0x0E,0x01);
				#elif defined(TW9908)
				
				#endif
				break;
		
			#elif defined(USE_PALSECAMtuner)
			case PAL_I:
			case PAL_BG:
			case PAL_DK:
				#if defined(SAA7114)
				WriteI2C(SAA7114_sysaddress,0x0E,0x01);
				#elif defined(SAA7115)
				WriteI2C(SAA7115_sysaddress,0x0E,0x01);
				#elif defined(TW9908)
				
				#endif
				break;

			case SEC_BG:
			case SEC_DK:
			case SEC_L:
				#if defined(SAA7114)
				WriteI2C(SAA7114_sysaddress,0x0E,0x51);
				#elif defined(SAA7115)
				WriteI2C(SAA7115_sysaddress,0x0E,0x51);
				#elif defined(TW9908)
				
				#endif
				break;
			#endif
		}
		
		#if defined(SAA7114)
		//SAA7114 50Hz system value
		//WriteI2C(SAA7114_sysaddress,0x08,0xA8);
		WriteI2C(SAA7114_sysaddress,0x08,0x38);//2002-12-30 2:06오후
		//SAA7114 50Hz Veritcal input size~		
		WriteI2C(SAA7114_sysaddress,0x9a,0x36);
		WriteI2C(SAA7114_sysaddress,0x9e,0x36);
		#elif defined(SAA7115)
		WriteI2C(SAA7115_sysaddress,0x08,0x38);//2002-12-30 2:06오후
		WriteI2C(SAA7115_sysaddress,0x9a,0x36);
		WriteI2C(SAA7115_sysaddress,0x9e,0x36);
		#elif defined(TW9908)
		
		#endif
		
		
		//display still!!(화면불안정 방지)
		BitWriteScaler(0xAA,0x08,0);
	}
	else//60Hz로..		//--------------------------------------------------------------------------------------
	{
		//display still!!(화면불안정 방지)
		//BitWriteScaler(0xAA,0x08,1);
		
		//Zoom Factor
		switch(xEEPROMBuffer[MainSubInputSource])
		{
			case	10://composite framesync
			case	14://s-video framesync
			case	18://tuner framesync
			#if defined(USE_NTSCtuner)
				if(DisplayAspectRatioNum&0x03==aspect4_3)
				{
					// 4:3 ----------------------------------------------------------------------------
					WriteScaler(0x3B, 0x0A); // Scale Mode 0x1a: -> Random, Zomm Down
					
					WriteScaler(0x35,  (DWORD) ((((DWORD)BIHAW)<<16) / (DWORD)PanelHerizontalsize)>>16);
					WordWriteScaler	(0x36,	((((DWORD)BIHAW)<<16) / (DWORD)PanelHerizontalsize));
					//WordWriteScaler	(0x36,	 0x83b8);//temp value
					
					WriteScaler(0x38,  ((((DWORD)(BIVAW)*2)<<16) / (DWORD)PanelVerticalsize*(3/4))>>16);
					WordWriteScaler	(0x39,	((((DWORD)(BIVAW)*2)<<16) / (DWORD)PanelVerticalsize*(3/4)));	
					//WordWriteScaler	(0x39,	0x7764);//temp value
					//---------------------------------------------------------------------------------
				}
				else if(DisplayAspectRatioNum&0x03==aspect16_9)
				{
					// 16:9 ---------------------------------------------------------------------------
					WriteScaler(0x3B, 0x0A); // Scale Mode 0x1a: -> Random, Zomm Down
					
					WriteScaler(0x35,  (DWORD) ((((DWORD)BIHAW)<<16) / (DWORD)PanelHerizontalsize)>>16);
					WordWriteScaler	(0x36,	((((DWORD)BIHAW)<<16) / (DWORD)PanelHerizontalsize));
					//WordWriteScaler	(0x36,	 0x83b8);//temp value
					
					WriteScaler(0x38,  ((((DWORD)(BIVAW)*2)<<16) / (DWORD)PanelVerticalsize*(9/16))>>16);
					WordWriteScaler	(0x39,	((((DWORD)(BIVAW)*2)<<16) / (DWORD)PanelVerticalsize*(9/16)));	
					//WordWriteScaler	(0x39,	0x7764);//temp value
					//---------------------------------------------------------------------------------
				}
				else if(DisplayAspectRatioNum&0x03==aspect_full)
				{
					#if defined(FullScaleToVertical)	// 입력을 판넬에 꽉차게
					// normal ----------------------------------------------------------------------------
					WriteScaler(0x3B, 0x0A); // Scale Mode 0x1a: -> Random, Zomm Down
					
					WriteScaler(0x35,  (DWORD) ((((DWORD)BIHAW)<<16) / (DWORD)PanelHerizontalsize)>>16);	//OH_factor
					WordWriteScaler	(0x36,	((((DWORD)BIHAW)<<16) / (DWORD)PanelHerizontalsize));
					
					WriteScaler(0x38,  ((((DWORD)(BIVAW)*2)<<16) / (DWORD)PanelVerticalsize)>>16);		//OV_factor
					WordWriteScaler	(0x39,	((((DWORD)(BIVAW)*2)<<16) / (DWORD)PanelVerticalsize));
					//---------------------------------------------------------------------------------
					#else	//2003-08-13,	판넬의 높이(V)에 맞추어 출력보정함.(4:3비율)
					// normal ----------------------------------------------------------------------------
					WriteScaler(0x3B, 0x0A); // Scale Mode 0x1a: -> Random, Zomm Down
					
					WriteScaler(0x35,  (DWORD) ((((DWORD)BIHAW)<<16) / (DWORD)PanelVerticalsize*(4/3))>>16);	//OH_factor
					WordWriteScaler	(0x36,	((((DWORD)BIHAW)<<16) / (DWORD)PanelVerticalsize*(4/3)));
					
					WriteScaler(0x38,  ((((DWORD)(BIVAW)*2)<<16) / (DWORD)PanelVerticalsize)>>16);		//OV_factor
					WordWriteScaler	(0x39,	((((DWORD)(BIVAW)*2)<<16) / (DWORD)PanelVerticalsize));	
					//---------------------------------------------------------------------------------
					#endif
				}				
			#else
							if(DisplayAspectRatioNum&0x03==aspect4_3)
				{
					// 4:3 ----------------------------------------------------------------------------
					WriteScaler(0x3B, 0x0A); // Scale Mode 0x1a: -> Random, Zomm Down
					
					WriteScaler(0x35,  (DWORD) ((((DWORD)BIHAW)<<16) / (DWORD)PanelHerizontalsize)>>16);
					WordWriteScaler	(0x36,	((((DWORD)BIHAW)<<16) / (DWORD)PanelHerizontalsize));
					//WordWriteScaler	(0x36,	 0x83b8);//temp value
					
					WriteScaler(0x38,  ((((DWORD)(BIVAW)*2)<<16) / (DWORD)PanelVerticalsize*(3/4))>>16);
					WordWriteScaler	(0x39,	((((DWORD)(BIVAW)*2)<<16) / (DWORD)PanelVerticalsize*(3/4)));	
					//WordWriteScaler	(0x39,	0x7764);//temp value
					//---------------------------------------------------------------------------------
				}
				else if(DisplayAspectRatioNum&0x03==aspect16_9)
				{
					// 16:9 ---------------------------------------------------------------------------
					WriteScaler(0x3B, 0x0A); // Scale Mode 0x1a: -> Random, Zomm Down
					
					WriteScaler(0x35,  (DWORD) ((((DWORD)BIHAW)<<16) / (DWORD)PanelHerizontalsize)>>16);
					WordWriteScaler	(0x36,	((((DWORD)BIHAW)<<16) / (DWORD)PanelHerizontalsize));
					//WordWriteScaler	(0x36,	 0x83b8);//temp value
					
					WriteScaler(0x38,  ((((DWORD)(BIVAW)*2)<<16) / (DWORD)PanelVerticalsize*(9/16))>>16);
					WordWriteScaler	(0x39,	((((DWORD)(BIVAW)*2)<<16) / (DWORD)PanelVerticalsize*(9/16)));	
					//WordWriteScaler	(0x39,	0x7764);//temp value
					//---------------------------------------------------------------------------------
				}
				else if(DisplayAspectRatioNum&0x03==aspect_full)
				{
					#if defined(FullScaleToVertical)	// 입력을 판넬에 꽉차게
					// normal ----------------------------------------------------------------------------
					WriteScaler(0x3B, 0x0A); // Scale Mode 0x1a: -> Random, Zomm Down
					
					WriteScaler(0x35,  (DWORD) ((((DWORD)BIHAW)<<16) / (DWORD)PanelHerizontalsize)>>16);	//OH_factor
					WordWriteScaler	(0x36,	((((DWORD)BIHAW)<<16) / (DWORD)PanelHerizontalsize));
					
					WriteScaler(0x38,  ((((DWORD)(BIVAW)*2)<<16) / (DWORD)PanelVerticalsize)>>16);		//OV_factor
					WordWriteScaler	(0x39,	((((DWORD)(BIVAW)*2)<<16) / (DWORD)PanelVerticalsize));
					//---------------------------------------------------------------------------------
					#else	//2003-08-13,	판넬의 높이(V)에 맞추어 출력보정함.(4:3비율)
					// normal ----------------------------------------------------------------------------
					WriteScaler(0x3B, 0x0A); // Scale Mode 0x1a: -> Random, Zomm Down
					
					WriteScaler(0x35,  (DWORD) ((((DWORD)BIHAW)<<16) / (DWORD)PanelVerticalsize*(4/3))>>16);	//OH_factor
					WordWriteScaler	(0x36,	((((DWORD)BIHAW)<<16) / (DWORD)PanelVerticalsize*(4/3)));
					
					WriteScaler(0x38,  ((((DWORD)(BIVAW)*2)<<16) / (DWORD)PanelVerticalsize)>>16);		//OV_factor
					WordWriteScaler	(0x39,	((((DWORD)(BIVAW)*2)<<16) / (DWORD)PanelVerticalsize));	
					//---------------------------------------------------------------------------------
					#endif
				}
			#endif
				break;	
			default:
				break;
		}

		//B-Channel Input active
		switch(xEEPROMBuffer[MainSubInputSource])
		{
			case	8://composite linesync
			case	10://composite framesync
			case	12://s-video linesync
			case	14://s-video framesync
			case	16://tuner linesync
			case	18://tuner framesync
				if(DisplayAspectRatioNum&0x03==aspect4_3)	//모두같음
				{
					WordWriteScaler(0xA0,BIHAW);
					WordWriteScaler(0xA6,BIVAW*2);
				}
				else if(DisplayAspectRatioNum&0x03==aspect16_9)
				{
					WordWriteScaler(0xA0,BIHAW);
					WordWriteScaler(0xA6,BIVAW*2);
				}
				else if(DisplayAspectRatioNum&0x03==aspect_full)
				{
				#if defined(FullScaleToVertical)	// 입력을 판넬에 꽉차게
					WordWriteScaler(0xA0,BIHAW);
				#else					//2003-08-13,	판넬의 높이(V)에 맞추어 출력보정함.(4:3비율)				
					//WordWriteScaler(0xA0,PanelVerticalsize*(4/3));
					WordWriteScaler(0xA0,BIHAW);
				#endif
					
					WordWriteScaler(0xA6,BIVAW*2);
				}
				break;			
			case	20://RGB+COMPOSITE(PIP)
			case	28://RGB+S-VIDEO(PIP)
			case	52://RGB+TUNER(PIP)
			case	36://DVI+COMPOSITE
			case	44://DVI+SIVIDEO
			case	60://DVI+TUNER
				switch(xEEPROMBuffer[PIPSIZE_buf]&0x03)
				{
					case SizeLarge://Large PIP size
						WordWriteScaler(0xA0,BIHAW);	//H
						WordWriteScaler(0xA6,BIVAW+1);	//V
						break;
					
					case SizeMiddle://Middle PIP size
						WordWriteScaler(0xA0,BIHAW);	//H
						WordWriteScaler(0xA6,BIVAW+1);	//V
						break;
					
					case SizeSmall://small PIP size
						WordWriteScaler(0xA0,BIHAW);
						WordWriteScaler(0xA6,BIVAW+1);
						break;
				}
				break;
				
			default:
				break;
		}
		//B-Channel H-position
		switch(xEEPROMBuffer[MainSubInputSource])
		{
			case	8://composite linesync
			case	10://composite framesync
			case	12://s-video linesync
			case	14://s-video framesync
			case	16://tuner linesync
			case	18://tuner framesync
				#ifdef Memory_1eaUse
				WordWriteScaler(0x9e,IBHAS_Main60Hz_value+2);	//Bchannel IHAS	
				#else
				switch(xEEPROMBuffer[DisplayAspcet_buf])
				{			//모두 같음
					case aspect4_3:
						WordWriteScaler(0x9e,IBHAS_Main60Hz_value);	//Bchannel IHAS
						break;		
					case aspect16_9:
						WordWriteScaler(0x9e,IBHAS_Main60Hz_value);	//Bchannel IHAS 
						break;		
					case aspect_full:
						#if defined(FullScaleToVertical)	// 입력을 판넬에 꽉차게
							WordWriteScaler(0x9e,IBHAS_Main60Hz_value);	//Bchannel IHAS 
						#else					//2003-08-13,	판넬의 높이(V)에 맞추어 출력보정함.(4:3비율)
							WordWriteScaler(0x9e,IBHAS_Main60Hz_value+28);	//Bchannel IHAS 
						#endif
						break;		
				}
				#endif
				break;
			case	20://RGB+COMPOSITE(PIP)
			case	28://RGB+S-VIDEO(PIP)
			case	52://RGB+TUNER(PIP)
			case	36://DVI+COMPOSITE
			case	44://DVI+SIVIDEO
			case	60://DVI+TUNER

				WordWriteScaler(0x9e,IBHAS_Main60Hz_value);	//Bchannel IHAS

				break;
		}
		
		//B-Channel V-position
		switch(xEEPROMBuffer[MainSubInputSource])
		{
			case	8://composite linesync
			case	10://composite framesync
			case	12://s-video linesync
			case	14://s-video framesync
			case	16://tuner linesync
			case	18://tuner framesync
				#if defined(WXGA_Panel)
					WordWriteScaler(0xa2,IBVAS_Main60Hz_value);	//odd
					WordWriteScaler(0xa4,IBVAS_Main60Hz_value);	//even	//2003-08-01 9:50오후 
				#else
				switch(xEEPROMBuffer[DisplayAspcet_buf])
				{
					case aspect4_3:
						WordWriteScaler(0xa2,IBVAS_Main60Hz_value-1);	//odd
						WordWriteScaler(0xa4,IBVAS_Main60Hz_value-1);	//even	//2003-08-01 9:50오후 
						break;		
					case aspect16_9:
					case aspect_full:					
						WordWriteScaler(0xa2,IBVAS_Main60Hz_value);	//odd
						WordWriteScaler(0xa4,IBVAS_Main60Hz_value);	//even	//2003-08-01 9:50오후 
						break;		
				}
				#endif
				break;
			
			case	20://RGB+COMPOSITE(PIP)
			case	28://RGB+S-VIDEO(PIP)
			case	52://RGB+TUNER(PIP)
			case	36://DVI+COMPOSITE
			case	44://DVI+SIVIDEO
			case	60://DVI+TUNER
			
				#if 1
					WordWriteScaler(0xa2,IBVAS_Main60Hz_value);		//Odd!!,  //Bchannel IVAS
					WordWriteScaler(0xa4,IBVAS_Main60Hz_value);		//Even!!  //Bchannel IVAS
				#else
				switch(xEEPROMBuffer[PIPSIZE_buf]&0x03)
				{
					case SizeLarge://Large PIP size
						WordWriteScaler(0xa2,IBVAS_Main60Hz_value);		//Odd!!,  //Bchannel IVAS
						WordWriteScaler(0xa4,IBVAS_Main60Hz_value);		//Even!!  //Bchannel IVAS
						break;
					
					case SizeMiddle://middle PIP size
						WordWriteScaler(0xa2,IBVAS_Main60Hz_value);		//Odd!!,  //Bchannel IVAS
						WordWriteScaler(0xa4,IBVAS_Main60Hz_value);		//Even!!  //Bchannel IVAS
						break;

					case SizeSmall://small PIP size
						WordWriteScaler(0xa2,IBVAS_Main60Hz_value);		//Odd!!,  //Bchannel IVAS
						WordWriteScaler(0xa4,IBVAS_Main60Hz_value);		//Even!!  //Bchannel IVAS
						break;

				}
				#endif
				break;
		}
				
		//SAA7114 50Hz,60Hz default value
		switch(xEEPROMBuffer[TVMODE])
		{
			#if defined(USE_NTSCtuner)
			case NTSC_AIR://air
			case NTSC_CATV://catv
				#if defined(SAA7114)
				WriteI2C(SAA7114_sysaddress,0x0E,0x01);
				#elif defined(SAA7115)
				WriteI2C(SAA7115_sysaddress,0x0E,0x01);
				#elif defined(TW9908)
				
				#endif
				break;
		
			#elif defined(USE_PALSECAMtuner)
			case PAL_I:
			case PAL_BG:
			case PAL_DK:
				#if defined(SAA7114)
				WriteI2C(SAA7114_sysaddress,0x0E,0x01);
				#elif defined(SAA7115)
				WriteI2C(SAA7115_sysaddress,0x0E,0x01);
				#elif defined(TW9908)
				
				#endif
				break;

			case SEC_BG:
			case SEC_DK:
			case SEC_L:
				#if defined(SAA7114)
				WriteI2C(SAA7114_sysaddress,0x0E,0x51);
				#elif defined(SAA7115)
				WriteI2C(SAA7115_sysaddress,0x0E,0x51);
				#elif defined(TW9908)
				
				#endif
				break;
			#endif
		}
		#if defined(SAA7114)		
		//SAA7114 60Hz system value
		//WriteI2C(SAA7114_sysaddress,0x08,0xe8);
		WriteI2C(SAA7114_sysaddress,0x08,0xe8);
		
		//SAA7114 50Hz Veritcal input size~		
		WriteI2C(SAA7114_sysaddress,0x9a,0x04);
		WriteI2C(SAA7114_sysaddress,0x9e,0x04);
		#elif defined(SAA7115)
		WriteI2C(SAA7115_sysaddress,0x08,0xF0);
		WriteI2C(SAA7115_sysaddress,0x9a,0x04);
		WriteI2C(SAA7115_sysaddress,0x9e,0x04);
		#elif defined(TW9908)
		
		#endif
		//display still!!(화면불안정 방지)
		BitWriteScaler(0xAA,0x08,0);
	}
}
 #endif

//****************************************************************//
//RGB only function change!!
//****************************************************************//
void ChangeToRgbOnly(void)
{
	//ADC,DVI를 모두 disable하면 스케일러 출력(클럭공급이 원활치못함)이 불규칙하게 되어 화면이 약깐 흐름
	//시각적으로 뮤트를 하기 위해 인버터까지 끈다.
	Mute_SoundOff;
	InvertOff;
	MUTEON;
	CurrentFunction=0;
	OSDstatus = OSDoff;
	ModeTrigger;
	AsyncOn;				//sync input(Fr D-SUB)
	ADCEnable;
	DVIDisable;
	//VIDEOdisable;
	
#if	defined(BtcBoard_Option) 
	AudioSelection_PC;
#endif

	SyncStableTimer=10;
	xEEPROMBuffer[MainSubInputSource] = 2;
	EepromSetQue(MainSubInputSource_adr,2);
}


//****************************************************************//
//COMPOSITE only function change!!
//****************************************************************//
void ChangeToCompositeOnly(void)
{
	//ADC,DVI를 모두 disable하면 스케일러 출력(클럭공급이 원활치못함)이 불규칙하게 되어 화면이 약깐 흐름
	//시각적으로 뮤트를 하기 위해 인버터까지 끈다.
	Mute_SoundOff;
	InvertOff;//화면불안정감춤.
	MUTEON;
	//VIDEOenable;
	CurrentFunction=2;
	//MenuNum=5;//test
	OSDstatus = OSDoff;
	xEEPROMBuffer[MainSubInputSource]=10;
	VideoActiveCompleted = 0;
	EepromSetQue(MainSubInputSource_adr,10);
	//VIDEOdisable;
	PowerOnsequence = DevicestableWait;//2002-12-30 12:58오후
	PowerOnTimer = 10;
#if	defined(BtcBoard_Option) 
	AudioSelection_AV;
#endif
}

#if defined(USE_SCART)	
//****************************************************************//
//SCART only function change!!
//****************************************************************//
void ChangeToScartOnly(void)
{

	//ADC,DVI를 모두 disable하면 스케일러 출력(클럭공급이 원활치못함)이 불규칙하게 되어 화면이 약깐 흐름
	//시각적으로 뮤트를 하기 위해 인버터까지 끈다.
	Mute_SoundOff;
	InvertOff;//화면불안정감춤.
	MUTEON;
	//VIDEOenable;
	CurrentFunction=11;
	OSDstatus = OSDoff;
	xEEPROMBuffer[MainSubInputSource]=68;
	VideoActiveCompleted = 0;
	EepromSetQue(MainSubInputSource_adr,68);
	//VIDEOdisable;
	PowerOnsequence = DevicestableWait;//2002-12-30 12:58오후
	PowerOnTimer = 10;
	AudioSelection_SCART;
}
#endif
//****************************************************************//
//S-VIDEO only function change!!
//****************************************************************//
void ChangeToSvideoOnly(void)
{
	//ADC,DVI를 모두 disable하면 스케일러 출력(클럭공급이 원활치못함)이 불규칙하게 되어 화면이 약깐 흐름
	//시각적으로 뮤트를 하기 위해 인버터까지 끈다.
	Mute_SoundOff;
	InvertOff;//화면불안정감춤.
	MUTEON;
	//VIDEOenable;
	CurrentFunction=3;
	OSDstatus = OSDoff;
	xEEPROMBuffer[MainSubInputSource]=14;
	VideoActiveCompleted = 0;
	EepromSetQue(MainSubInputSource_adr,14);
	//VIDEOdisable;
	PowerOnsequence = DevicestableWait;//2002-12-30 12:58오후
	PowerOnTimer = 10;
#if	defined(BtcBoard_Option) 
	AudioSelection_AV;
#endif	
}		


//****************************************************************//
//TUNER only function change!!
//****************************************************************//
void ChangeToTunerOnly(void)
{
	//ADC,DVI를 모두 disable하면 스케일러 출력(클럭공급이 원활치못함)이 불규칙하게 되어 화면이 약깐 흐름
	//시각적으로 뮤트를 하기 위해 인버터까지 끈다.
	Mute_SoundOff;
	InvertOff;
	MUTEON;
	//VIDEOenable;
	CurrentFunction=4;
	OSDstatus = OSDoff;
	ADCDisable;
	DVIDisable;
	xEEPROMBuffer[MainSubInputSource] = 18;
	VideoActiveCompleted = 0;//video decoder 재설정..
	#if defined(SAA7114)
	WriteI2C(SAA7114_sysaddress,0x02,0xc5);//Input change!
	#elif defined(SAA7115)
	WriteI2C(SAA7115_sysaddress,0x02,0xc5);//Input change!
	#elif defined(TW9908)
	
	#endif
#if	defined(BtcBoard_Option) 
	AudioSelection_TV;
#endif	
	EepromSetQue(MainSubInputSource_adr,18);
}



//****************************************************************//
//PIP(RGB+TUNER) function change!!
//****************************************************************//																
/*memory save 2003.8.11 youngdo
void ChangeToPipRgbTuner(void)
{
	//ADC,DVI를 모두 disable하면 스케일러 출력(클럭공급이 원활치못함)이 불규칙하게 되어 화면이 약깐 흐름
	//시각적으로 뮤트를 하기 위해 인버터까지 끈다.
	InvertOff;
	MUTEON;
	VIDEOenable;
	AsyncOn;//if DVI -> RGB
	ADCEnable;
	DVIDisable;
	CurrentFunction=7;
	OSDstatus = OSDoff;
	//power.c에서 걸리게 되므로 할필요가 없음. 하게 되면 2번 튜너를 동일채널셋팅하게 됨.
	//case	NormalDisplayPrepare:
	xEEPROMBuffer[MainSubInputSource] = 52;
	VideoActiveCompleted = 0;
	#if defined(SAA7114)
	WriteI2C(SAA7114_sysaddress,0x02,0xc5);//Input change!
	#elif defined(SAA7115)
	WriteI2C(SAA7115_sysaddress,0x02,0xc5);//Input change!
	#elif defined(TW9908)
	
	#endif
#if	defined(BtcBoard_Option) 
	AudioSelection_TV;
#endif	
	EepromSetQue(MainSubInputSource_adr,52);
}
*/
	
//****************************************************************//
//PIP(RGB+TUNER) function change!!(FAST!)
//****************************************************************//
void ChangeToPipRgbTunerFast(void)
{
	Mute_SoundOff;
	PIPMuteOn;PipMuteTimer=40;
//	MUTEON;
//	WriteScaler(0x8E,0x00);//PIP OFF //2003-08-01
	//VIDEOenable;
	CurrentFunction=PipRnT_mode;	//7;
	//xOSDW_OPTION[1]=0x00|0x02;//OSD OFF
	//OSDOFF;
	SoundMuteTvTimer=0;
	TunerProcessing=1;//튜너셋팅..
	xEEPROMBuffer[MainSubInputSource] = 52;
	VideoActiveCompleted = 0;
	#if defined(SAA7114)
	WriteI2C(SAA7114_sysaddress,0x02,0xc5);//Input change!
	#elif defined(SAA7115)
	WriteI2C(SAA7115_sysaddress,0x02,0xc5);//Input change!
	#elif defined(TW9908)
	
	#endif
	EepromSetQue(MainSubInputSource_adr,52);
	PipFastChange = 1;
	
	PipSubRegisterSet();
	
	//OSD status 
	//Volume Path
	OSDWindows = AnalogSubwindow;
	OSDstatus = NowStatusDisplay;
	
#if	defined(BtcBoard_Option) 		
	AudioSelection_TV;
#else			
	AudioSelection_HIGH;
#endif
	
	OSDWindows = PIPSubWindow;
	OSDcharacters = PipRgbTunerChars;
					
}

#if defined(USE_SCART)
//****************************************************************//
//PIP(RGB+SCRAT) function change!!(FAST!)
//****************************************************************//
void ChangeToPipRgbScartFast(void)
{
	Mute_SoundOff;
	PIPMuteOn;PipMuteTimer=40;
	//MUTEON;
	//VIDEOenable;
	CurrentFunction=12;
	//xOSDW_OPTION[1]=0x00|0x02;//OSD OFF
	//OSDOFF;
	xEEPROMBuffer[MainSubInputSource] = 72;
	VideoActiveCompleted = 0;
	EepromSetQue(MainSubInputSource_adr,72);	
	PipFastChange = 1;
	
	PipSubRegisterSet();
	
	//OSD status 
	//Volume Path
	OSDWindows = AnalogSubwindow;
	OSDstatus = NowStatusDisplay;

	AudioSelection_SCART;

	if(!SoundMuteOnFlag)//MUTE가 아닌경우.
	{
//test2004-07-06		Mute_SoundOn;	//Sound On~~
		PutVolumePWM();		
	}
	OSDWindows = PIPSubWindow;
	OSDcharacters = PipRgbScartChars;
	
}
#endif

//****************************************************************//
//PIP(RGB+COMPOSITE) function change!!
//****************************************************************//
/*  for memory save 2003.6.5
void ChangeToPipRgbComposite(void)
{
	//ADC,DVI를 모두 disable하면 스케일러 출력(클럭공급이 원활치못함)이 불규칙하게 되어 화면이 약깐 흐름
	//시각적으로 뮤트를 하기 위해 인버터까지 끈다.
	InvertOff;
	MUTEON;
	VIDEOenable;
	AsyncOn;//if DVI -> RGB
	ADCEnable;
	DVIDisable;
	CurrentFunction=5;
	OSDstatus = OSDoff;
	xEEPROMBuffer[MainSubInputSource] = 20;
	VideoActiveCompleted = 0;
	#if defined(SAA7114)
	WriteI2C(SAA7114_sysaddress,0x02,0xc4);//Input change!
	#elif defined(SAA7115)
	WriteI2C(SAA7115_sysaddress,0x02,0xc4);//Input change!
	#elif defined(TW9908)
	
	#endif
	EepromSetQue(MainSubInputSource_adr,20);	
}
*/


//****************************************************************//
//PIP(RGB+COMPOSITE) function change!!(FAST!)
//****************************************************************//
void ChangeToPipRgbCompositeFast(void)
{
	Mute_SoundOff;
	PIPMuteOn;PipMuteTimer=40;
	//MUTEON;
//	WriteScaler(0x8E,0x00);//PIP OFF //2003-08-01
	
	//VIDEOenable;
	CurrentFunction=PipRnC_mode;	//5;
	//xOSDW_OPTION[1]=0x00|0x02;//OSD OFF
	//OSDOFF;
	xEEPROMBuffer[MainSubInputSource] = 20;
	VideoActiveCompleted = 0;
	#if defined(SAA7114)
	WriteI2C(SAA7114_sysaddress,0x02,0xc4);//Input change!
	#elif defined(SAA7115)
	WriteI2C(SAA7115_sysaddress,0x02,0xc4);//Input change!
	#elif defined(TW9908)
	//
	#endif
	EepromSetQue(MainSubInputSource_adr,20);	
	PipFastChange = 1;
	
	PipSubRegisterSet();
	
	//OSD status 
	//Volume Path
	OSDWindows = AnalogSubwindow;
	OSDstatus = NowStatusDisplay;
#if	defined(BtcBoard_Option) 		
	AudioSelection_AV;
#else		
	AudioSelection_LOW;
#endif
	if(!SoundMuteOnFlag)//MUTE가 아닌경우.
	{
//test2004-07-06		Mute_SoundOn;	//Sound On~~
		PutVolumePWM();		
	}
	OSDWindows = PIPSubWindow;
	OSDcharacters = PipRgbCompositeChars;
	
}


//****************************************************************//
//PIP(RGB+S-VIDEO) function change!!
//****************************************************************//
/*  for memory save 2003.6.5
void ChangeToPipRgbSvideo(void)
{
	//ADC,DVI를 모두 disable하면 스케일러 출력(클럭공급이 원활치못함)이 불규칙하게 되어 화면이 약깐 흐름
	//시각적으로 뮤트를 하기 위해 인버터까지 끈다.
	InvertOff;
	MUTEON;
	VIDEOenable;
	AsyncOn;//if DVI -> RGB
	ADCEnable;
	DVIDisable;
	CurrentFunction=6;
	OSDstatus = OSDoff;
	xEEPROMBuffer[MainSubInputSource] = 28;
	VideoActiveCompleted = 0;
	#if defined(SAA7114)
	WriteI2C(SAA7114_sysaddress,0x02,0xc6);//Input change!
	#elif defined(SAA7115)
	WriteI2C(SAA7115_sysaddress,0x02,0xc6);//Input change!
	#elif defined(TW9908)
	
	#endif
#if	defined(BtcBoard_Option) 
	AudioSelection_AV;
#endif	
	EepromSetQue(MainSubInputSource_adr,28);
}
*/

//****************************************************************//
//PIP(RGB+S-VIDEO) function change!!(FAST!)
//****************************************************************//
void ChangeToPipRgbSvideoFast(void)
{
	Mute_SoundOff;
	PIPMuteOn;PipMuteTimer=40;
//	MUTEON;
//	WriteScaler(0x8E,0x00);//PIP OFF //2003-08-01
	//VIDEOenable;
	CurrentFunction=PipRnS_mode;	//6
	//xOSDW_OPTION[1]=0x00|0x02;//OSD OFF
	////OSDOFF;
	xEEPROMBuffer[MainSubInputSource] = 28;
	VideoActiveCompleted = 0;
	#if defined(SAA7114)
	WriteI2C(SAA7114_sysaddress,0x02,0xc6);//Input change!
	#elif defined(SAA7115)
	WriteI2C(SAA7115_sysaddress,0x02,0xc6);//Input change!
	#elif defined(TW9908)
	
	#endif
	EepromSetQue(MainSubInputSource_adr,28);
	PipFastChange = 1;
	
	PipSubRegisterSet();
	//OSD status 
	//Volume Path
	OSDWindows = AnalogSubwindow;
	OSDstatus = NowStatusDisplay;
	#if	defined(BtcBoard_Option) 		
	AudioSelection_AV;
	#else	
	AudioSelection_LOW;
	#endif
	if(!SoundMuteOnFlag)//MUTE가 아닌경우.
	{
//test2004-07-06		Mute_SoundOn;	//Sound On~~
		PutVolumePWM();
	}
	OSDWindows = PIPSubWindow;
	OSDcharacters = PipRgbSvideoChars;
	
}


#ifdef DVI_USE
//****************************************************************//
//DVI only function change!!
//****************************************************************//
void ChangeToDviOnly(void)
{
	//ADC,DVI를 모두 disable하면 스케일러 출력(클럭공급이 원활치못함)이 불규칙하게 되어 화면이 약깐 흐름
	//시각적으로 뮤트를 하기 위해 인버터까지 끈다.
	Mute_SoundOff;
	InvertOff;
	MUTEON;
	//VIDEOdisable;
	CurrentFunction=1;
	OSDstatus = OSDoff;
	DelayNOP10();
	ModeTrigger;
	
	//Critcal Issue!!
	//B-channel(TV)->DVI로 전환되는 경우 sync-processor의 적절한 동작을 하기 위해선
	//다음 3두가지 동작은 필히 할것
	#ifdef	EMH2
	BitWriteScaler(0xA9,0x20,1);	
	#endif

	BitWriteScaler(0x25,0x20,1);	
	BitWriteScaler(0x01,0x10,0);	//TV Disable

	AsyncOff;
	ADCDisable;
	DVIEnable;
	SyncStableTimer=20;
	xEEPROMBuffer[MainSubInputSource] = 6;//Frame DVI
	EepromSetQue(MainSubInputSource_adr,6);
}


//****************************************************************//
//PIP(DVI+TUNER) function change!!
//****************************************************************//
void ChangeToPipDviTuner(void)
{
	//ADC,DVI를 모두 disable하면 스케일러 출력(클럭공급이 원활치못함)이 불규칙하게 되어 화면이 약깐 흐름
	//시각적으로 뮤트를 하기 위해 인버터까지 끈다.
	Mute_SoundOff;
	InvertOff;
	MUTEON;
	//VIDEOenable;
	AsyncOff;
	ADCDisable;
	DVIEnable;
	CurrentFunction=10;
	OSDstatus = OSDoff;
	xEEPROMBuffer[MainSubInputSource] = 60;
	VideoActiveCompleted = 0;
	//power.c에서 걸리게 되므로 할필요가 없음. 하게 되면 2번 튜너를 동일채널셋팅하게 됨.
	//case	NormalDisplayPrepare:
	#if defined(SAA7114)
	WriteI2C(SAA7114_sysaddress,0x02,0xc5);//Input change!
	#elif defined(SAA7115)
	WriteI2C(SAA7115_sysaddress,0x02,0xc5);//Input change!
	#elif defined(TW9908)
	
	#endif
	
	//Critcal Issue!!
	//B-channel(TV)->DVI로 전환되는 경우 sync-processor의 적절한 동작을 하기 위해선
	//다음 3두가지 동작은 필히 할것
	BitWriteScaler(0x25,0x20,1);	
	BitWriteScaler(0x01,0x10,0);	//TV Disable
	#ifdef	EMH2
	BitWriteScaler(0xA9,0x20,1);	
	#endif
	
	EepromSetQue(MainSubInputSource_adr,60);
}	

//****************************************************************//
//PIP(DVI+TUNER) function change!!(FAST)
//****************************************************************//
void ChangeToPipDviTunerFast(void)
{
	Mute_SoundOff;
	PIPMuteOn;PipMuteTimer=40;
	//MUTEON;
	//VIDEOenable;
	CurrentFunction=10;
	//xOSDW_OPTION[1]=0x00|0x02;//OSD OFF
	//OSDOFF;
	xEEPROMBuffer[MainSubInputSource] = 60;
	VideoActiveCompleted = 0;
	SoundMuteTvTimer=0;
	TunerProcessing=1;//투너셋팅..
	#if defined(SAA7114)
	WriteI2C(SAA7114_sysaddress,0x02,0xc5);//Input change!
	#elif defined(SAA7115)
	WriteI2C(SAA7115_sysaddress,0x02,0xc5);//Input change!
	#elif defined(TW9908)
	
	#endif
	
	EepromSetQue(MainSubInputSource_adr,60);
	PipFastChange = 1;
	
	//OSD status 
	//Volume Path
	OSDWindows = AnalogSubwindow;
	OSDstatus = NowStatusDisplay;
#if	defined(BtcBoard_Option) 		
	AudioSelection_TV;
#else	
	AudioSelection_HIGH;
#endif
	OSDWindows = PIPSubWindow;
	OSDcharacters = PipDviTunerChars;
					
	PipSubRegisterSet();
}	

//****************************************************************//
//PIP(DVI+COMPOSITE) function change!!
//****************************************************************//
void ChangeToPipDviComposite(void)
{
	//ADC,DVI를 모두 disable하면 스케일러 출력(클럭공급이 원활치못함)이 불규칙하게 되어 화면이 약깐 흐름
	//시각적으로 뮤트를 하기 위해 인버터까지 끈다.
	Mute_SoundOff;
	InvertOff;
	MUTEON;
	//VIDEOenable;
	AsyncOff;
	ADCDisable;
	DVIEnable;
	CurrentFunction=8;
	OSDstatus = OSDoff;
	xEEPROMBuffer[MainSubInputSource] = 36;
	VideoActiveCompleted = 0;
	#if defined(SAA7114)
	WriteI2C(SAA7114_sysaddress,0x02,0xc4);//Input change!
	#elif defined(SAA7115)
	WriteI2C(SAA7115_sysaddress,0x02,0xc4);//Input change!
	#elif defined(TW9908)
	
	#endif
	
	//Critcal Issue!!
	//B-channel(TV)->DVI로 전환되는 경우 sync-processor의 적절한 동작을 하기 위해선
	//다음 3두가지 동작은 필히 할것
	#ifdef	EMH2
	BitWriteScaler(0xA9,0x20,1);	
	#endif
	BitWriteScaler(0x25,0x20,1);	
	BitWriteScaler(0x01,0x10,0);	//TV Disable
	EepromSetQue(MainSubInputSource_adr,36);
}	


//****************************************************************//
//PIP(DVI+COMPOSITE) function change!!(FAST!)
//****************************************************************//
void ChangeToPipDviCompositeFast(void)
{
	Mute_SoundOff;
	PIPMuteOn;PipMuteTimer=40;
	//MUTEON;
	//VIDEOenable;
	CurrentFunction=8;
	//xOSDW_OPTION[1]=0x00|0x02;//OSD OFF
	//OSDOFF;
	xEEPROMBuffer[MainSubInputSource] = 36;
	VideoActiveCompleted = 0;
	#if defined(SAA7114)
	WriteI2C(SAA7114_sysaddress,0x02,0xc4);//Input change!
	#elif defined(SAA7115)
	WriteI2C(SAA7115_sysaddress,0x02,0xc4);//Input change!
	#elif defined(TW9908)
	
	#endif
	EepromSetQue(MainSubInputSource_adr,36);
	PipFastChange = 1;
	
	PipSubRegisterSet();
	
	//OSD status 
	//Volume Path
	OSDWindows = AnalogSubwindow;
	OSDstatus = NowStatusDisplay;
#if	defined(BtcBoard_Option) 		
	AudioSelection_AV;
#else	
	AudioSelection_LOW;
#endif
	if(!SoundMuteOnFlag)//MUTE가 아닌경우.
	{
//test2004-07-06		Mute_SoundOn;	//Sound On~~
		PutVolumePWM();
	}
	OSDWindows = PIPSubWindow;
	OSDcharacters = PipDviCompositeChars;
	
}	

//****************************************************************//
//PIP(DVI+S-VIDEO) function change!!
//****************************************************************//
void ChangeToPipDviSvideo(void)
{
	//ADC,DVI를 모두 disable하면 스케일러 출력(클럭공급이 원활치못함)이 불규칙하게 되어 화면이 약깐 흐름
	//시각적으로 뮤트를 하기 위해 인버터까지 끈다.
	Mute_SoundOff;
	InvertOff;
	MUTEON;
	//VIDEOenable;
	AsyncOff;
	ADCDisable;
	DVIEnable;
	CurrentFunction=9;
	OSDstatus = OSDoff;
	xEEPROMBuffer[MainSubInputSource] = 44;
	VideoActiveCompleted = 0;
	#if defined(SAA7114)
	WriteI2C(SAA7114_sysaddress,0x02,0xc6);//Input change!
	#elif defined(SAA7115)
	WriteI2C(SAA7115_sysaddress,0x02,0xc6);//Input change!
	#elif defined(TW9908)
	
	#endif
	
	//Critcal Issue!!
	//B-channel(TV)->DVI로 전환되는 경우 sync-processor의 적절한 동작을 하기 위해선
	//다음 3두가지 동작은 필히 할것
	BitWriteScaler(0x25,0x20,1);	
	BitWriteScaler(0x01,0x10,0);	//TV Disable
	#ifdef	EMH2
	BitWriteScaler(0xA9,0x20,1);	
	#endif
	
	EepromSetQue(MainSubInputSource_adr,44);
}

//****************************************************************//
//PIP(DVI+S-VIDEO) function change!!(FAST!)
//****************************************************************//
void ChangeToPipDviSvideoFast(void)
{
	Mute_SoundOff;
	PIPMuteOn;PipMuteTimer=40;
	//MUTEON;
	//VIDEOenable;
	CurrentFunction=9;
	//xOSDW_OPTION[1]=0x00|0x02;//OSD OFF
	//OSDOFF;
	xEEPROMBuffer[MainSubInputSource] = 44;
	VideoActiveCompleted = 0;
	#if defined(SAA7114)
	WriteI2C(SAA7114_sysaddress,0x02,0xc6);//Input change!
	#elif defined(SAA7115)
	WriteI2C(SAA7115_sysaddress,0x02,0xc6);//Input change!
	#elif defined(TW9908)
	
	#endif
	EepromSetQue(MainSubInputSource_adr,44);
	PipFastChange = 1;
	
	
	PipSubRegisterSet();
	
	//OSD status 
	//Volume Path
	OSDWindows = AnalogSubwindow;
	OSDstatus = NowStatusDisplay;
#if	defined(BtcBoard_Option) 		
	AudioSelection_AV;
#else	
	AudioSelection_LOW;
#endif
	if(!SoundMuteOnFlag)//MUTE가 아닌경우.
	{
//test2004-07-06		Mute_SoundOn;	//Sound On~~
		PutVolumePWM();
	}
	OSDWindows = PIPSubWindow;
	OSDcharacters = PipDviSvideoChars;
	
}

#if	defined(USE_SCART)
//****************************************************************//
//PIP(DVI+SCART) function change!!
//****************************************************************//
void ChangeToPipDviScart(void)
{
	//ADC,DVI를 모두 disable하면 스케일러 출력(클럭공급이 원활치못함)이 불규칙하게 되어 화면이 약깐 흐름
	//시각적으로 뮤트를 하기 위해 인버터까지 끈다.
	Mute_SoundOff;
	InvertOff;
	MUTEON;
	//VIDEOenable;
	AsyncOff;
	ADCDisable;
	DVIEnable;
	CurrentFunction=13;
	OSDstatus = OSDoff;
	xEEPROMBuffer[MainSubInputSource] = 80;
	VideoActiveCompleted = 0;
	
	//Critcal Issue!!
	//B-channel(TV)->DVI로 전환되는 경우 sync-processor의 적절한 동작을 하기 위해선
	//다음 3두가지 동작은 필히 할것
	#ifdef	EMH2
	BitWriteScaler(0xA9,0x20,1);	
	#endif
	BitWriteScaler(0x25,0x20,1);	
	BitWriteScaler(0x01,0x10,0);	//TV Disable
	EepromSetQue(MainSubInputSource_adr,80);
	
}	


//****************************************************************//
//PIP(DVI+SCRAT) function change!!(FAST!)
//****************************************************************//
void ChangeToPipDviScartFast(void)
{
	Mute_SoundOff;
	PIPMuteOn;PipMuteTimer=40;
	//MUTEON;
	//VIDEOenable;
	CurrentFunction=13;
	//xOSDW_OPTION[1]=0x00|0x02;//OSD OFF
	//OSDOFF;
	xEEPROMBuffer[MainSubInputSource] = 80;
	VideoActiveCompleted = 0;

	EepromSetQue(MainSubInputSource_adr,80);
	PipFastChange = 1;
	
	PipSubRegisterSet();
	
	//OSD status 
	//Volume Path
	OSDWindows = AnalogSubwindow;
	OSDstatus = NowStatusDisplay;

	AudioSelection_SCART;

	if(!SoundMuteOnFlag)//MUTE가 아닌경우.
	{
//test2004-07-06		Mute_SoundOn;	//Sound On~~
		PutVolumePWM();
	}
	OSDWindows = PIPSubWindow;
	OSDcharacters = PipDviScartChars;

}

#endif

#endif

//****************************************************************//
//Display port data Msb Lsb swap
//****************************************************************//
void SetScalerInputOutputColorCondition(BYTE Recdata)
{
	if(	4 <=Recdata&&Recdata<=7 ||//DVI,DVI+PIP
		36<=Recdata&&Recdata<=51||
		60<=Recdata&&Recdata<=67)
	{
		WriteScaler(0x75,BIN_TO_BYTE(1,0,0,0,0,0,0,1));
	}
	else
	{
		WriteScaler(0x75,BIN_TO_BYTE(1,0,0,0,0,0,0,0));
	}
}

void SetScalerInputCondition(BYTE Recdata)
{
	switch(Recdata)
	{
		//RGB&DVI&RGB+VIDEO(PIP)
		case 0:
		case 2:
		case 20://RGB+COMPOSITE
		case 28://RGB+SVIDEO
		case 52://RGB +TUNER
			BitWriteScaler(0x00,0x01,1);	//2002-12-01 5:29오후, 0->1
			BitWriteScaler(0x01,0x10,0);	//TV Disable
			WriteScaler(0x25,0x38|ModeList[CurrentMode].IClkDly);
			break;
		
		#ifdef DVI_USE
		case 6:	//DVI	
		case 36://DVI+COMPOSITE
		case 44://DVI+SIVIDEO
		case 60://DVI+TUNER
		case 38://DVI+COMPOSITE((NO)
		case 46://DVI+SVIDEO(NO)
			BitWriteScaler(0x00,0x01,0);
			BitWriteScaler(0x01,0x10,0);	//TV Disable
			if(NowHactive>=1280) WriteScaler(0x25,0x28|0x05);//ICLKDLY!!
			else WriteScaler(0x25,0x38|0x00);
			break;
		#endif	
			
		case 8://composite linesync
		case 10://composite framesync
		case 12://s-video linesync
		case 14://s-video framesync
		case 16://tuner linesync
		case 18://tuner framesync
			BitWriteScaler(0x00,0x01,1);
			BitWriteScaler(0x01,0x10,1);	//TV Enable
			WriteScaler(0x25,BIN_TO_BYTE(0,0,0,1,1,1,0,0));
			break;
	}
}

void SetScalerInputIBRQS(BYTE Recdata)
{
	BYTE ibrqs;
	switch(Recdata)
	{
		case	2://FrameMode(RGB)
		case	6:
			ibrqs=(NowAdcCLK<<4)/(NowScalerMCLK>>1);
			ibrqs=64-ibrqs;
			if((ibrqs&3)==0) ibrqs++;//... 48,52,56,60 ... unstable,so avoid quadruple value	
			WriteScaler(0x2e,ibrqs);	//IBRQS!
			break;
		case	10://composite framesync
		case	14://s-video framesync
		case	18://tuner framesync
			ibrqs=(NowVideoCLK<<4)/(NowScalerMCLK>>1);
			ibrqs=64-ibrqs;
			if((ibrqs&3)==0) ibrqs++;//... 48,52,56,60 ... unstable,so avoid quadruple value	
			WriteScaler(0x2e,ibrqs);	//IBRQS!
			break;
		case	20://RGB+COMPOSITE(PIP)
		case	28://RGB+S-VIDEO(PIP)
		case	52://RGB+TUNER(PIP)
		case	36://DVI+COMPOSITE
		case	44://DVI+SIVIDEO
		case	60://DVI+TUNER
			ibrqs=(NowAdcCLK<<4)/(NowScalerMCLK>>1);
			ibrqs=64-ibrqs;
			if((ibrqs&3)==0) ibrqs++;//... 48,52,56,60 ... unstable,so avoid quadruple value	
			WriteScaler(0x2e,ibrqs);	//IBRQS!
			
			WriteScaler(0x94,62);	//PIP-IBRQS!//2003-03-26 3:44오후,PIP center에 있을때 구별지을것.
			break;
		default:
			break;	
	}
}


//OSFACTOR=(((PanelHerizontalsize+255)/256)*2)*((double)NowScalerMCLK/NowScalerDCLK)-1;
void SetScalerOutputOREQSTART(BYTE Recdata)
{
	switch(Recdata)
	{
		
		case	2://FrameMode
		case	6://DVI FrameMode
		case	10://composite framesync
		case	14://s-video framesync
		case	18://tuner framesync
			#ifdef Memory_1eaUse
				#if defined(SXGA_Panel)
					WriteScaler(0x5d,0x09);	//OREQSTART!
				#elif defined(WXGA_Panel)
					WriteScaler(0x5d,0x00);	//OREQSTART! ram1ea일때 우측화면1/3 출렁거림 제거..
				#elif defined(XGA_Panel)
					WriteScaler(0x5d,0x0);
				#elif defined(SVGA_Panel)
					WriteScaler(0x5d,0x0);
				#else
					WriteScaler(0x5d,0x0);
				#endif
			#else
				#if defined(SXGA_Panel)
				//WriteScaler(0x5d,(((PanelHerizontalsize+255)/256)*2)*((double)NowScalerMCLK/NowScalerDCLK)-1);	//OREQSTART!
				WriteScaler(0x5d,0x09);	//OREQSTART!
				#elif defined(WXGA_Panel)
				//WriteScaler(0x5d,(((PanelHerizontalsize+255)/256)*2)*((double)NowScalerMCLK/NowScalerDCLK)-1);	//OREQSTART!
				WriteScaler(0x5d,0x09);	//OREQSTART!
				#elif defined(XGA_Panel)
				WriteScaler(0x5d,0x0);
				#elif defined(SVGA_Panel)
				WriteScaler(0x5d,0x0);
				#else
				WriteScaler(0x5d,0x0);
				#endif
			#endif
			
			break;
		
		//case	20:
		default:
			WriteScaler(0x5d,0x00);
			break;	
	}	
}

void SetScalerFMothers(BYTE Recdata)
{
	switch(Recdata)
	{
		case	2:
		case	6://DVI FrameMode
			WriteScaler(0x30,0x00);	//FM CAS latency
 			
 			#if defined(EMH1A)	
 			WriteScaler(0x93,0xF0);				//main frame delay!
			#elif defined(EMH2)
 			WriteScaler(0x93,0xE0);				//main frame delay!
			#else
 			WriteScaler(0x93,0xF0);				//main frame delay!
			#endif	
 			
			WordWriteScaler(0x97,NowHactive*24/48);					//frame offset!
			WriteScaler(0x99,0x00);				//Deinterlace,,,,
			WriteScaler(0xaa,0x00);				//frame refresh!
			break;
		
		
		case 10://composite framesync
		case 14://s-video framesync
		case 18://tuner framesync
			WriteScaler(0x30,0x0c);	//FM CAS latency
		
			#if defined(EMH1A)	
 			WriteScaler(0x93,0xF0);				//main frame delay!
			#elif defined(EMH2)
 			WriteScaler(0x93,0xE0);				//main frame delay!
			#else
 			WriteScaler(0x93,0xF0);				//main frame delay!
			#endif	
			
			#if defined(Memory_1eaUse)
			WordWriteScaler(0x97,BIHAW*24L/16-4);	//frame offset!	//16bit bandwidth memory 
			WriteScaler(0x99,0x9b);				//Deinterlace, memsize 16bit
			#else
			WordWriteScaler(0x97,BIHAW*24L/48);	//frame offset!	//48bit bandwidth memory 
			WriteScaler(0x99,0x83);				//Deinterlace, memsize 48bit
			#endif
			
			
			WriteScaler(0xaa,0x00);				//frame refresh!
			break;	
		
		case 20://RGB+COMPOSTE(PIP)
		case 28://RGB+S-VIDEO(PIP)
		case 52://RGB+TUNER(PIP)
		case 36://DVI+COMPOSITE
		case 44://DVI+SIVIDEO
		case 60://DVI+TUNER
			WriteScaler(0x30,0x0c);	//FM CAS latency
			WordWriteScaler(0x97,NowHactive*24/48);					//frame offset!
			WordWriteScaler(0x91,(512*16)>>4);

			#if defined(EMH1A)	
 			WriteScaler(0x93,0xfd);				//main frame delay!
			#elif defined(EMH2)
 			WriteScaler(0x93,0xEd);				//main frame delay!
			#else
 			WriteScaler(0x93,0xfd);				//main frame delay!
			#endif	

			WriteScaler(0x99,0x20);	//PIP16bit , Deinterlaced
			break;
		
		default:
			break;
	}
}

void PipBlendFunc(void)
{
			switch(xEEPROMBuffer[PIPBLEND_buf])
			{
				case 3://25%
					WriteScaler(0x8E,0x34);
					break;
					
				case 2://50%
					WriteScaler(0x8E,0x24);
					break;
					
				case 1://75%
					WriteScaler(0x8E,0x14);
					break;
					
				case 0://100%
					WriteScaler(0x8E,0x04);
					break;
					
				default://100%
					WriteScaler(0x8E,0x04);
					break;
			}
}

void	PipEnableFunc(void)
{
			switch(xEEPROMBuffer[PIPSIZE_buf]&0x03)
			{
				case SizeLarge://Large PIP size(512x384)
					#ifdef PipDpmsON
					if(NoExistHfreq||NoExistVfreq)	WriteScaler(0x9a,0xf8);//PIP ON!!
					else	WriteScaler(0x9a,0xf8);//PIP ON!!, scale up
					#else
						WriteScaler(0x9a,0xf8);	//PIP ON!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
					#endif
					//BitWriteScaler(0x9a,0x02,0);//PIP Deinterlaced "Off"
					break;
				
				case SizeMiddle://middle PIP size(400x300)	//2003-05-20 added by thkim
					if(!PipAspectFlag)
					{	
						#ifdef PipDpmsON
						if(NoExistHfreq||NoExistVfreq)	WriteScaler(0x9a,0xf8);//PIP ON!!
						else	WriteScaler(0x9a,0xf8);//PIP ON!!, scale up
						#else
							WriteScaler(0x9a,0xf8);//PIP ON!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
						#endif
					}
					else
					{
						#ifdef PipDpmsON
						if(NoExistHfreq||NoExistVfreq) WriteScaler(0x9a,0xfc);	//PIP ON!!, scale down
						else	WriteScaler(0x9a,0xfc);	//PIP ON!!, scale down
						#else	
							WriteScaler(0x9a,0xfc);	//PIP ON!!!!!!!!!!!!!!!!!!, scale down
						#endif
					}
					//BitWriteScaler(0x9a,0x02,0);//PIP Deinterlaced "Off"
					break;	

				case SizeSmall://small PIP size(320x240)	//2003-07-29 size modified
					if(!PipAspectFlag)	//4:3
					{	
						#ifdef PipDpmsON
						if(NoExistHfreq||NoExistVfreq)
						{
							if(NowVideo50Hz==0)	WriteScaler(0x9a,0xf8);	//PIP ON!!	
							else if(NowVideo50Hz==1)WriteScaler(0x9a,0xfc);	//PIP ON!!, scale down
						}
						else
						{
							if(NowVideo50Hz==0)	WriteScaler(0x9a,0xf8);	//PIP ON!!	
							else if(NowVideo50Hz==1)WriteScaler(0x9a,0xfc);	//PIP ON!!, scale down
						}
						#else
							if(NowVideo50Hz==0)	WriteScaler(0x9a,0xf8);	//PIP ON!!!!!!!!!!!!!!!!!!!!!!!!!!!!	
							else if(NowVideo50Hz==1)WriteScaler(0x9a,0xf8);	//PIP ON!!, scale down
						#endif
					}
					else				//16:9
					{
						#ifdef PipDpmsON
						if(NoExistHfreq||NoExistVfreq) WriteScaler(0x9a,0xfc);	//PIP ON!!, scale down
						else WriteScaler(0x9a,0xfc);	//PIP ON!!, scale down
						#else 
							WriteScaler(0x9a,0xfc);	//PIP ON!!!!!!!!!!!!!!!!!!!!!!!!!!, scale down
						#endif
					}

					break;	
			}
}

void SetScalerPIPOutputCondition(BYTE Recdata)	// ☆☆ pip enable!!! ☆☆
{						// pip 백그라운드 크기, 크기/위치/ON, PIP Blend 셋팅
	xBYTE pipBWoffset;
	#ifdef PIPstyle2
		pipBWoffset=8;
	#else
		pipBWoffset=4;
	#endif
	
	switch(Recdata)
	{
		case	22://RGB+COMPOSITE(NO)
		case	30://RGB+SVIDEO(NO)
		case	38://DVI+COMPOSITE(NO)
		case	46://DVI+SVIDEO(NO)
			
			break;
				
		case 20://RGB+COMPOSITE(PIP)
		case 28://RGB+SVIDEO(PIP)
		case 52://RGB+TUNER(PIP)
		case 36://DVI+COMPOSITE
		case 44://DVI+SIVIDEO
		case 60://DVI+TUNER
			
//test2003-10-16			PipPositionService();

		
			//PIP Bkg width		//2003-08-20
			#ifdef PipDpmsON	//2003-10-21
				WordWriteScaler(0xba,2047);//main Hwidth!
				WordWriteScaler(0xbe,2047);//main Vwidth!		
				//BitWriteScaler(0x9a,0x80,1);//test
			#else
			switch(xEEPROMBuffer[PIPSIZE_buf]&0x03)
			{
				case SizeLarge://Large PIP size(512x460)
					WordWriteScaler(0xba,512+pipBWoffset);//main Hwidth!
					if(!PipAspectFlag) WordWriteScaler(0xbe,384+pipBWoffset);//main Vwidth!		
					else		   WordWriteScaler(0xbe,288+pipBWoffset);//main Vwidth!		
             		break;
				
				case SizeMiddle://middle PIP size(400x300)	//2003-05-20 added by thkim
					WordWriteScaler(0xba,400+pipBWoffset);//main Hwidth!
					if(!PipAspectFlag)	WordWriteScaler(0xbe,300+pipBWoffset);//main Vwidth!	
					else			WordWriteScaler(0xbe,225+pipBWoffset);//main Vwidth!	

					break;	
                        	
				case SizeSmall://small PIP size(320x240)
					WordWriteScaler(0xba,320+pipBWoffset);//main Hwidth!
					if(!PipAspectFlag)	WordWriteScaler(0xbe,240+pipBWoffset);//main Vwidth!	
					else			WordWriteScaler(0xbe,180+pipBWoffset);//main Vwidth!	
					break;								
			}
			#endif
			//PIP Main width
			switch(xEEPROMBuffer[PIPSIZE_buf]&0x03)
			{
				case SizeLarge://Large PIP size(512x384)
					WordWriteScaler(0x82,512);//main Hwidth!
					if(!PipAspectFlag) WordWriteScaler(0x86,384);//main Vwidth!		
					else		   WordWriteScaler(0x86,288);//main Vwidth!		
					
					//WriteScaler(0x9a,0xf8);//PIP ON!!
//					WriteScaler(0x9a,0x78);//PIP ON!!
					//BitWriteScaler(0x9a,0x02,0);//PIP Deinterlaced "Off"
					break;
				
				case SizeMiddle://middle PIP size(400x300)	//2003-05-20 added by thkim
					WordWriteScaler(0x82,400);//main Hwidth!
					if(!PipAspectFlag)
					{	
						WordWriteScaler(0x86,300);//main Vwidth!	
						//WriteScaler(0x9a,0xf8);//PIP ON!!
//						WriteScaler(0x9a,0x78);//PIP ON!!
					}
					else
					{
						WordWriteScaler(0x86,225);//main Vwidth!	
						//WriteScaler(0x9a,0xfc);	//PIP ON!!, scale down
//						WriteScaler(0x9a,0x7c);	//PIP ON!!, scale down
					}
					//BitWriteScaler(0x9a,0x02,0);//PIP Deinterlaced "Off"
					break;	

				case SizeSmall://small PIP size(320x240)	//2003-07-29 size modified
					WordWriteScaler(0x82,320);//main Hwidth!
					if(!PipAspectFlag)
					{	
						WordWriteScaler(0x86,240);//main Vwidth!	
						
						//if(NowVideo50Hz==0)	WriteScaler(0x9a,0xf8);	//PIP ON!!	
						//else if(NowVideo50Hz==1)WriteScaler(0x9a,0xfc);	//PIP ON!!, scale down
//						if(NowVideo50Hz==0)	WriteScaler(0x9a,0x78);	//PIP ON!!	
//						else if(NowVideo50Hz==1)WriteScaler(0x9a,0x7c);	//PIP ON!!, scale down

					}
					else
					{
						WordWriteScaler(0x86,180);//main Vwidth!	
						//WriteScaler(0x9a,0xfc);	//PIP ON!!, scale down
//						WriteScaler(0x9a,0x7c);	//PIP ON!!, scale down
					}
					//BitWriteScaler(0x9a,0x02,0);//PIP Deinterlaced "Off"
					break;	
			}
			
			PipPositionService();
			
			if(MenuNum==menu_pip_size||MenuNum==menu_pip_AspectRatio) idelay5m(70);//2003-10-16
			
			//PIP enable
			PipEnableFunc();

			//WriteScaler(0x8E,0x08);//PIP memomry sequence reset
			//WriteScaler(0x8E,0x00);//PIP memomry sequence reset
			
			//PIP background color
			#ifdef PIPstyle2
			WriteScaler(0xdc,0);	//R
			WriteScaler(0xdd,0);	//G
			WriteScaler(0xde,155);	//B
			#else
			WriteScaler(0xdc,100);	//R
			WriteScaler(0xdd,0);	//G
			WriteScaler(0xde,200);	//B
			#endif

			//PIP background on/off
			if(	xEEPROMBuffer[MainSubInputSource]==20||
				xEEPROMBuffer[MainSubInputSource]==28||
				xEEPROMBuffer[MainSubInputSource]==52
				)BitWriteScaler(0x9a,0x80,1);//PIP MUTE main display	// pip일 경우	pip bgd on
			else BitWriteScaler(0x9a,0x80,0); //pip 아닐 경우 pip bgd off

			//PIP Blend
			if(MenuNum==menu_pip_blend)	PipBlendFunc();
			
			switch(xEEPROMBuffer[PIPBLEND_buf])
			{
				case 3://25%
								BitWriteScaler(0x8E,0x20,1);
								BitWriteScaler(0x8E,0x10,1);
								break;
				
				case 2://50%
								BitWriteScaler(0x8E,0x20,1);
								BitWriteScaler(0x8E,0x10,0);
								break;
				
				case 1://75%
								BitWriteScaler(0x8E,0x20,0);
								BitWriteScaler(0x8E,0x10,1);
								break;
					
				case 0://100%
				default://100%
								BitWriteScaler(0x8E,0x20,0);
								BitWriteScaler(0x8E,0x10,0);
					break;
			}
			
			//2003-05-29 8:21오후PipOnOffFlag=0;//PIP관련 플레그 지워둔다.(메뉴상에서 ON, OFF를 참조하기 위해)
			break;
		
		default:
			//MUTEON;//2003-08-01 11:24오후
			break;
	}       
}           
            
WORD GetDVTotal(WORD ivt,WORD ivaw)
{           
	return ((DWORD)ivt*PanelVerticalsize+(ivaw>>1))/ivaw;
}           
            
void SetScalerOutputHVTotal(BYTE Recdata)
{           
	WORD IVT;   
	double ILOCK;
	WORD DVT		= 0;
	WORD imsi		= 0;
	        
	switch(Recdata)
	{       
		case	0://LineSync(No Frame)
			IVT		= (ReadScaler(0x6F)&0x07)<<8|ReadScaler(0x70);
			DVT		= GetDVTotal(IVT,NowVactive);
			ILOCK	= ((double)DVT*8/IVT-(DFLT_OVACTIVESTART-1))*PanelMinHTotal;
			imsi	= (DWORD)ILOCK/PanelMinHTotal;
			WordWriteScaler(0x3C,PanelMaxHTotal);	//H-total
			WordWriteScaler(0x45,DVT+imsi);			//V-total
			break;
		
		#if defined(EMH1A)
		case	2://Frame
		case	6://DVI FMmode
		case	10://composite framesync
		case	14://s-video framesync
		case	18://tuner framesync
		case	20://RGB+COMPOSITE(PIP)
		case	28://RGB+SVIDEO(PIP)
		case	52://RGB+TUNER(PIP)
		case	36://DVI+COMPOSITE
		case	44://DVI+SIVIDEO
		case	60://DVI+TUNER
			WordWriteScaler(0x3C,PanelMinHTotal);
			WordWriteScaler(0x45,PanelMinVTotal);
			break;

		#elif defined(EMH2)
		case	2://Frame
		case	6://DVI FMmode
		case	20://RGB+COMPOSITE(PIP)
		case	28://RGB+SVIDEO(PIP)
		case	52://RGB+TUNER(PIP)
		case	36://DVI+COMPOSITE
		case	44://DVI+SIVIDEO
		case	60://DVI+TUNER
			#if defined (WXGA_Panel)	//2004-01-20
				if(NowVideo50Hz) WordWriteScaler(0x3C,PanelMinHTotal+270);	// wide17", pal에서 동영상 부자연스러움(끊어짐) 때문.
				else	//WordWriteScaler(0x3C,PanelMinHTotal);	//아래부분(중복)으로
			#endif//#else
			WordWriteScaler(0x3C,PanelMinHTotal);
			//#endif
			//WordWriteScaler(0x45,PanelMinVTotal+84);	//pc에서 60hz로...(->1278)//2003-08-18
			WordWriteScaler(0x45,PanelMinVTotal);	//pc에서 60hz로...	//PanelMinVTotal 값은 변경하면 안됨.
			break;
			
		case	10://composite framesync
		case	14://s-video framesync
		case	18://tuner framesync
			//WordWriteScaler(0x3C,PanelMinHTotal);
			//WordWriteScaler(0x45,1050);
			#if defined (WXGA_Panel)	//2004-01-20	//pal에서 total이 모자라 화면움직임이 부자연스럽기 때문에
				if(NowVideo50Hz) WordWriteScaler(0x3C,PanelMinHTotal+300);	//1340->1640
				else	//WordWriteScaler(0x3C,PanelMinHTotal+30);	//1340->1347
			#endif//#else
			WordWriteScaler(0x3C,PanelMinHTotal+30);//1340->1370
			//#endif
			//WordWriteScaler(0x45,PanelMinVTotal+7);//1032->1050//2003-08-14 1194->1201
			WordWriteScaler(0x45,PanelMinVTotal);	//2004-01-12	//V-total은 바꿔주면 안됨.
			break;

		#else
		case	2://Frame
		case	6://DVI FMmode
		case	10://composite framesync
		case	14://s-video framesync
		case	18://tuner framesync
		case	20://RGB+COMPOSITE(PIP)
		case	28://RGB+SVIDEO(PIP)
		case	52://RGB+TUNER(PIP)
		case	36://DVI+COMPOSITE
		case	44://DVI+SIVIDEO
		case	60://DVI+TUNER
			WordWriteScaler(0x3C,PanelMinHTotal);
			WordWriteScaler(0x45,PanelMinVTotal);
			break;
		#endif
		
		case	8://composite linesync
		case	12://s-video linesync
		case	16://tuner linesync
			IVT		= 262;
			DVT		= GetDVTotal(262,BIVAW);
			ILOCK	= ((double)DVT*8/IVT-(DFLT_OVACTIVESTART-1))*PanelMinHTotal;

			WordWriteScaler(0x3C,PanelMaxHTotal);
			WordWriteScaler(0x45,DVT+(DWORD)ILOCK/PanelMinHTotal);
			break;
		
		default:
			break;
	}	
}

void SetScalerOutputHVLockLoad(BYTE Recdata)
{
WORD IVT = 0;
double ILOCK; 
WORD DVT = 0;
	
	switch(Recdata)
	{
		case	0://LineSync(No Frame)
		case	2://FrameMode
		case	6:
		case	20://RGB+COMPOSITE(PIP)
		case	28://RGB+S-VIDEO(PIP)
		case	52://RGB+TUNER(PIP)
		case	36://DVI+COMPOSITE
		case	44://DVI+SIVIDEO
		case	60://DVI+TUNER
			IVT = (ReadScaler(0x6F)&0x07)<<8|ReadScaler(0x70);
			DVT = GetDVTotal(IVT,NowVactive);	//Output VTotal
			ILOCK = ((double)DVT*8/IVT-(DFLT_OVACTIVESTART-1))*PanelMinHTotal;
			
			WordWriteScaler(0x43,2047-(DWORD)ILOCK%PanelMinHTotal);				//Output VLockLoad
			WordWriteScaler(0x4D,DVT);											//Output HLockLoad
			break;
		
		case	8://composite linesync
		case	10://composite framesync
		case	12://s-video linesync
		case	14://s-video framesync
		case	16://tuner linesync
		case	18://tuner framesync
			DVT = GetDVTotal(262,BIVAW);
			#if defined(SXGA_Panel)
			WordWriteScaler(0x43,1200);	//Output VLockLoad
			#elif defined(WXGA_Panel)||defined(XGA_Panel)||defined(SVGA_Panel)
			WordWriteScaler(0x43,920);	//Output VLockLoad
			//#elif defined(SVGA_Panel)
			//WordWriteScaler(0x43,920);			//Output VLockLoad
			#else
			WordWriteScaler(0x43,920);	//Output VLockLoad
			#endif
			WordWriteScaler(0x4D,DVT);				//Output HLockLoad
			break;
			
		default:
			break;
	}
}

void SetScalerInputHVLock(BYTE Recdata)
{
	WORD IVT;
	switch(Recdata)
	{
		case	0:
		case	1:
		case	2:
		case	3:
		case	6:
		case	20://RGB+COMPOSITE(PIP)
		case	28://RGB+S-VIDEO(PIP)
		case	52://RGB+TUNER(PIP)
		case	36://DVI+COMPOSITE
		case	44://DVI+SIVIDEO
		case	60://DVI+TUNER
			IVT = (ReadScaler(0x6F)&0x07)<<8|ReadScaler(0x70);
			WordWriteScaler(0x0E,1);		//InputHLock,Linesync에 동작....
			WordWriteScaler(0x10,IVT-1);	//InputVLock.
			break;
		
		case	8://composite linesync
		case	12://s-video linesync
		case	16://tuner linesync
			WordWriteScaler(0x0E,1);		//InputHLock
			WordWriteScaler(0x10,262-1);	//InputVLock
			break;
		case	10://composite framesync
		case	14://s-video framesync
		case	18://tuner framesync
			WordWriteScaler(0x0E,1);		//InputHLock
			WordWriteScaler(0x10,277-1);	//InputVLock
			break;
		
		default:
			break;
	}	
}

void SetScalerZoomFactor(BYTE Recdata)
{
	DWORD	hsfactor=0,vsfactor=0;

	switch(Recdata)
	{
		case	0://LineSyncMode
		case	1:		
		case	2://FrameMode
		case	6://DVI FrameMode
		case	20://RGB+COMPOSITE(PIP)
		case	28://RGB+S-VIDEO(PIP)
		case	52://RGB+TUNER(PIP)
		case	36://DVI+COMPOSITE
		case	44://DVI+SIVIDEO
		case	60://DVI+TUNER
			if(NowVactive <= PanelVerticalsize){
			// ========= Zoom UP
				hsfactor = (DWORD)((((DWORD)NowHactive)<<16) / PanelHerizontalsize);
				vsfactor = (DWORD)((((DWORD)NowVactive)<<16) / PanelVerticalsize);
				#if defined(WXGA_Panel)
					#ifdef Wide4_3Aspect
					(BYTE)AspectFlag=xEEPROMBuffer[Aspect_buf]&&0x01;
					if(AspectFlag) hsfactor = (DWORD)((((DWORD)NowHactive)<<16) / 1024);
					#endif
					WriteScaler(0x3B,0x0a);	//2003-10-09
				#else
					WriteScaler(0x3B,(NowVactive < PanelVerticalsize)?0x0a:0x00);
				#endif
			}
			else{
			// ========= Zoom Down.....
				hsfactor = (DWORD)((((DWORD)PanelHerizontalsize)<<16) / NowHactive);
				vsfactor = (DWORD)((((DWORD)PanelVerticalsize )<<16) / NowVactive);
				WriteScaler(0x3B, 0x1A); // Scale Mode 0x1a: -> Random, Zomm Down
			}
			WriteScaler	(0x35,  hsfactor>>16);
			WordWriteScaler	(0x36,	hsfactor);
			WriteScaler	(0x38,  vsfactor>>16);
			WordWriteScaler	(0x39,	vsfactor);	
			//------------------------------2003-10-10 , wide 4:3변경후 다시 되돌아 올때를 대비..			
			#ifdef Wide4_3Aspect	
			(BYTE)AspectFlag=xEEPROMBuffer[Aspect_buf]&&0x01;
		
			if(AspectFlag)	//4:3
			{
				WriteScaler(0x41, 0x04);	//OH_ActiveWidth	//value:1024 = 0x400
				WriteScaler(0x42, 0x00);
				WriteScaler(0x3f, (DFLT_OHACTIVESTART+128)>>8);
				WriteScaler(0x40, DFLT_OHACTIVESTART+128);
			}
			else
			#endif
			{
			WriteScaler(0x3f, DFLT_OHACTIVESTART>>8);
			WriteScaler(0x40, DFLT_OHACTIVESTART);
			WriteScaler(0x41, PanelHerizontalsize>>8);	//OH_ActiveWidth
			WriteScaler(0x42, PanelHerizontalsize);
			}
			//------------------------------2003-08-04 by thkim, video mode에서 변경을 할수있기 때문에..
			WriteScaler(0x49, DFLT_OVACTIVESTART>>8);
			WriteScaler(0x4a, DFLT_OVACTIVESTART);
			WriteScaler(0x4b,  PanelVerticalsize>>8);
			WriteScaler(0x4c,  PanelVerticalsize);
			//-------------------------------------------------------
			
			if(NowVideo50Hz==0)	// 60Hz
			{
					
				switch(xEEPROMBuffer[PIPSIZE_buf]&0x03)
				{
				case SizeLarge://Large PIP size
					hsfactor = (((DWORD)512)<<16)/(684L)+1;		//PIP Hfactor(512 size)
					if(!PipAspectFlag) vsfactor = (((DWORD)230)<<16)/(384L);	//PIP Vfactor(384 size)
					else		   vsfactor = (((DWORD)230)<<16)/(288L);	//PIP Vfactor(288 size)
					break;

				case SizeMiddle://middle PIP size
					hsfactor = (((DWORD)400)<<16)/684L+1;		//PIP Hfactor(400 size)
					if(!PipAspectFlag) vsfactor = (((DWORD)(230))<<16)/300;	//PIP Vfactor(230 size)
					else		   vsfactor = (((DWORD)(225))<<16)/230+1;	//PIP Vfactor(225 size)
					break;	

				case SizeSmall://small PIP size
					hsfactor = (((DWORD)320)<<16)/684L+1;		//PIP Hfactor(320 size)
					if(!PipAspectFlag) vsfactor = (((DWORD)(230))<<16)/240;	//PIP Vfactor(240 size)
					else		   vsfactor = (((DWORD)(180))<<16)/230+1;	//PIP Vfactor(180 size)
					break;	
				}
			}
			else if(NowVideo50Hz==1)	// 50Hz		//2003-08-20
			{
				switch(xEEPROMBuffer[PIPSIZE_buf]&0x03)
				{
					case SizeLarge://Large PIP size
						hsfactor = (((DWORD)512)<<16)/(684L)+1;		//PIP Hfactor(512 size)
						if(!PipAspectFlag) vsfactor = (((DWORD)280)<<16)/(384L);	//PIP Vfactor(384 size)
						else		   vsfactor = (((DWORD)280)<<16)/(288L);	//PIP Vfactor(288 size)
						break;
                                	
					case SizeMiddle://middle PIP size
						hsfactor = (((DWORD)400)<<16)/684L+1;		//PIP Hfactor(400 size)
						if(!PipAspectFlag) vsfactor = (((DWORD)(280))<<16)/300;	//PIP Vfactor(230 size)
						else		   vsfactor = (((DWORD)(225))<<16)/280+1;	//PIP Vfactor(225 size)
						break;	
                                	
					case SizeSmall://small PIP size
						hsfactor = (((DWORD)320)<<16)/684L+1;		//PIP Hfactor(320 size)
						if(!PipAspectFlag) vsfactor = (((DWORD)(240))<<16)/280;	//PIP Vfactor(240 size)
						else		   vsfactor = (((DWORD)(180))<<16)/280+1;	//PIP Vfactor(180 size)
						break;	
				}
			}
			//PIP H factor
			WriteScaler(0x88,hsfactor>>16);
			WordWriteScaler(0x89,hsfactor);
			
			//PIP V factor
			WriteScaler(0x8B,vsfactor>>16);
			WordWriteScaler(0x8C,vsfactor);
			break;
		
		case	8://composite linesync
		case	12://s-video linesync
		case	16://tuner linesync
			hsfactor = (DWORD) ((((DWORD)BIHAW)<<16) / PanelHerizontalsize);
			vsfactor = (DWORD) ((((DWORD)BIVAW)<<16) / PanelVerticalsize);
			WriteScaler(0x3B, 0x0A); // Scale Mode 0x1a: -> Random, Zomm Down

			WriteScaler		(0x35,  hsfactor>>16);
			WordWriteScaler	(0x36,	hsfactor);
			WriteScaler		(0x38,  vsfactor>>16);
			WordWriteScaler	(0x39,	vsfactor);	

			break;
		
		case	10://composite framesync
		case	14://s-video framesync
		case	18://tuner framesync
			#ifdef Memory_1eaUse
				hsfactor = (DWORD) ((((DWORD)BIHAW-6)<<16) / PanelHerizontalsize);
			#else
				hsfactor = (DWORD) ((((DWORD)BIHAW)<<16) / PanelHerizontalsize);
			#endif
			
				//vsfactor = (DWORD)((((DWORD)240*2)<<16) / PanelVerticalsize);//deinterlace ovs factor
				//vsfactor = (DWORD)((((DWORD)BIVAW*2)<<16) / PanelVerticalsize);//deinterlace ovs factor	//2003-08-02
				//2003-08-02 --------------------------------------------------------------------------------------------------
				DisplayAspectRatioNum=(xEEPROMBuffer[DisplayAspcet_buf]&0x03);
				
		//****************************************
		if(!NowVideo50Hz)	// 60Hz		//2003-08-19 
		//****************************************
			{
			#if defined(WXGA_Panel)
				if(DisplayAspectRatioNum==aspect4_3)
				{
					#ifdef Memory_1eaUse
					hsfactor = (DWORD) ((((DWORD)BIHAW-6)<<16) / (1024+20) );
					#else
					hsfactor = (DWORD) ((((DWORD)BIHAW)<<16) / (1024+20) );
					#endif
					vsfactor = ((((DWORD)(230)*2)<<16) / PanelVerticalsize);
					WriteScaler(0x3f, (WORD)(DFLT_OHACTIVESTART+((WORD)PanelHerizontalsize-1044)/2)>>8);
					WriteScaler(0x40, DFLT_OHACTIVESTART+((WORD)PanelHerizontalsize-1044)/2);
					WriteScaler(0x41, 1044>>8);	//OH_ActiveWidth
					WriteScaler(0x42, 1044);
					
					WriteScaler(0x49, DFLT_OVACTIVESTART>>8);
					WriteScaler(0x4a, DFLT_OVACTIVESTART);
					WriteScaler(0x4b,  PanelVerticalsize>>8);	//OV_Height
					WriteScaler(0x4c,  PanelVerticalsize);
				}
				else if(DisplayAspectRatioNum==aspect16_9)
				{
					vsfactor = ((((DWORD)(230)*2)<<16) / 720);
					WriteScaler(0x3f, DFLT_OHACTIVESTART>>8);
					WriteScaler(0x40, DFLT_OHACTIVESTART);
					WriteScaler(0x41, PanelHerizontalsize>>8);	//OH_ActiveWidth
					WriteScaler(0x42, PanelHerizontalsize);
					WriteScaler(0x49, (WORD)((DFLT_OVACTIVESTART+(WORD)PanelVerticalsize-720)/2)>>8);
					WriteScaler(0x4a, DFLT_OVACTIVESTART+(((WORD)PanelVerticalsize-720)/2));
					WriteScaler(0x4b,  0x02);	//OV_Height
					WriteScaler(0x4c,  0xd0);	//0x2d0 (720)
				}
				else if(DisplayAspectRatioNum==aspect_full)
				{
					#ifndef FullScaleToVertical	// 입력을 판넬에 꽉차게
					hsfactor = 0x7d90;//0x7fd0;//(DWORD) ((((DWORD)BIHAW)<<16) / (DWORD)PanelVerticalsize*(4/3));
					#endif
					
					vsfactor = ((((DWORD)(230)*2)<<16) / (DWORD)PanelVerticalsize);
					WriteScaler(0x3f, DFLT_OHACTIVESTART>>8);
					WriteScaler(0x40, DFLT_OHACTIVESTART);
					WriteScaler(0x41, PanelHerizontalsize>>8);	//OH_ActiveWidth
					WriteScaler(0x42, PanelHerizontalsize);
					WriteScaler(0x4b,  PanelVerticalsize>>8);	//OV_Height
					WriteScaler(0x4c,  PanelVerticalsize);
					WriteScaler(0x49, DFLT_OVACTIVESTART>>8);
					WriteScaler(0x4a, DFLT_OVACTIVESTART);

				}
			#else			
				if(DisplayAspectRatioNum==aspect4_3)
				{
					vsfactor = ((((DWORD)(BIVAW+3)*2)<<16) / 960);
					WriteScaler(0x4b,  0x03);	//OV_Height
					WriteScaler(0x4c,  0xc0);	//0x3c0 (960)
					WriteScaler(0x49, (WORD)((DFLT_OVACTIVESTART+(WORD)PanelVerticalsize-960)/2)>>8);
					WriteScaler(0x4a, DFLT_OVACTIVESTART+(WORD)(((WORD)PanelVerticalsize-960)/2));
				}
				else if(DisplayAspectRatioNum==aspect16_9)
				{
					vsfactor = ((((DWORD)(BIVAW)*2)<<16) / 720);
					WriteScaler(0x4b,  0x02);	//OV_Height
					WriteScaler(0x4c,  0xd0);	//0x2d0 (720)
					WriteScaler(0x49, (WORD)((DFLT_OVACTIVESTART+(WORD)PanelVerticalsize-720)/2)>>8);
					WriteScaler(0x4a, DFLT_OVACTIVESTART+(((WORD)PanelVerticalsize-720)/2));
				}
				else if(DisplayAspectRatioNum==aspect_full)
				{
					#ifndef FullScaleToVertical	// 입력을 판넬에 꽉차게
					hsfactor = 0x7d90;//0x7fd0;//(DWORD) ((((DWORD)BIHAW)<<16) / (DWORD)PanelVerticalsize*(4/3));
					#endif
					
					vsfactor = ((((DWORD)(BIVAW)*2)<<16) / (DWORD)PanelVerticalsize);
					WriteScaler(0x4b,  PanelVerticalsize>>8);	//OV_Height
					WriteScaler(0x4c,  PanelVerticalsize);
					WriteScaler(0x49, DFLT_OVACTIVESTART>>8);
					WriteScaler(0x4a, DFLT_OVACTIVESTART);

				}
			#endif
		
		}
                        //------------------------------------------------------------------------------------------------------------
		//****************************************
		else 	// 50hz			//2003-08-19
		//****************************************
		{
		#if defined(WXGA_Panel)
			if(DisplayAspectRatioNum==aspect4_3)
			{
				#ifdef Memory_1eaUse
				hsfactor = (DWORD) ((((DWORD)BIHAW-6)<<16) / (1024+20) );
				#else
				hsfactor = (DWORD) ((((DWORD)BIHAW)<<16) / (1024+20) );
				#endif

				#ifdef USE_NTSCtuner
				vsfactor = ((((DWORD)(280)*2)<<16) / PanelVerticalsize);	
				#else
				//vsfactor = ((((DWORD)(BIVAW)*2)<<16) / PanelVerticalsize);	
				vsfactor = ((((DWORD)(280)*2)<<16) / PanelVerticalsize);	
				#endif
				WriteScaler(0x3f, (WORD)(DFLT_OHACTIVESTART+((WORD)PanelHerizontalsize-1044)/2)>>8);
				WriteScaler(0x40, DFLT_OHACTIVESTART+((WORD)PanelHerizontalsize-1044)/2);
				WriteScaler(0x41, 1044>>8);	//OH_ActiveWidth
				WriteScaler(0x42, 1044);
				
				WriteScaler(0x49, DFLT_OVACTIVESTART>>8);
				WriteScaler(0x4a, DFLT_OVACTIVESTART);
				WriteScaler(0x4b,  PanelVerticalsize>>8);	//OV_Height
				WriteScaler(0x4c,  PanelVerticalsize);
			}
			else if(DisplayAspectRatioNum==aspect16_9)
			{
				#ifdef USE_NTSCtuner
				vsfactor = ((((DWORD)(280)*2)<<16) / 720);	
				#else
				//vsfactor = ((((DWORD)(BIVAW)*2)<<16) / 720);
				vsfactor = ((((DWORD)(280)*2)<<16) / 720);	
				#endif

				WriteScaler(0x3f, DFLT_OHACTIVESTART>>8);
				WriteScaler(0x40, DFLT_OHACTIVESTART);
				WriteScaler(0x41, PanelHerizontalsize>>8);	//OH_ActiveWidth
				WriteScaler(0x42, PanelHerizontalsize);

				WriteScaler(0x49, (WORD)((DFLT_OVACTIVESTART+(WORD)PanelVerticalsize-720)/2)>>8);
				WriteScaler(0x4a, DFLT_OVACTIVESTART+(((WORD)PanelVerticalsize-720)/2));
				WriteScaler(0x4b,  0x02);	//OV_Height
				WriteScaler(0x4c,  0xd0);	//0x2d0
			}
			else if(DisplayAspectRatioNum==aspect_full)
			{
				#ifndef FullScaleToVertical	// 입력을 판넬에 꽉차게
				hsfactor = 0x7fd0;//(DWORD) ((((DWORD)BIHAW)<<16) / (DWORD)PanelVerticalsize*(4/3));
				#endif
				
				#ifdef USE_NTSCtuner
				vsfactor = ((((DWORD)(280)*2)<<16) / (DWORD)PanelVerticalsize);
				#else
				//vsfactor = ((((DWORD)(BIVAW)*2)<<16) / (DWORD)PanelVerticalsize);
				vsfactor = ((((DWORD)(280)*2)<<16) / (DWORD)PanelVerticalsize);
				#endif

				WriteScaler(0x3f, DFLT_OHACTIVESTART>>8);
				WriteScaler(0x40, DFLT_OHACTIVESTART);
				WriteScaler(0x41, PanelHerizontalsize>>8);	//OH_ActiveWidth
				WriteScaler(0x42, PanelHerizontalsize);

				WriteScaler(0x49, DFLT_OVACTIVESTART>>8);
				WriteScaler(0x4a, DFLT_OVACTIVESTART);
				WriteScaler(0x4b,  PanelVerticalsize>>8);	//OV_Height
				WriteScaler(0x4c,  PanelVerticalsize);
			}
		#else
			if(DisplayAspectRatioNum==aspect4_3)
			{
				vsfactor = ((((DWORD)(280)*2)<<16) / 960);	
				WriteScaler(0x49, (WORD)((DFLT_OVACTIVESTART+(WORD)PanelVerticalsize-960)/2)>>8);
				WriteScaler(0x4a, DFLT_OVACTIVESTART+(WORD)(((WORD)PanelVerticalsize-960)/2));
				WriteScaler(0x4b,  0x03);	//OV_Height
				WriteScaler(0x4c,  0xc0);	//0x3c0
			}
			else if(DisplayAspectRatioNum==aspect16_9)
			{
				vsfactor = ((((DWORD)(280)*2)<<16) / 720);	
				WriteScaler(0x49, (WORD)((DFLT_OVACTIVESTART+(WORD)PanelVerticalsize-720)/2)>>8);
				WriteScaler(0x4a, DFLT_OVACTIVESTART+(((WORD)PanelVerticalsize-720)/2));
				WriteScaler(0x4b,  0x02);	//OV_Height
				WriteScaler(0x4c,  0xd0);	//0x2d0
			}
			else if(DisplayAspectRatioNum==aspect_full)
			{
				#ifndef FullScaleToVertical	// 입력을 판넬에 꽉차게
				hsfactor = 0x7fd0;//(DWORD) ((((DWORD)BIHAW)<<16) / (DWORD)PanelVerticalsize*(4/3));
				#endif
				
				vsfactor = ((((DWORD)(280)*2)<<16) / (DWORD)PanelVerticalsize);
				WriteScaler(0x4b,  PanelVerticalsize>>8);	//OV_Height
				WriteScaler(0x4c,  PanelVerticalsize);
				WriteScaler(0x49, DFLT_OVACTIVESTART>>8);
				WriteScaler(0x4a, DFLT_OVACTIVESTART);

			}
		#endif
		//****************************************
		}
		//****************************************
			
				WriteScaler(0x3B, 0x0A); // Scale Mode 0x1a: -> Random, Zomm Down
                        	
				WriteScaler	(0x35,  hsfactor>>16);	// H
				WordWriteScaler	(0x36,	hsfactor);
				WriteScaler	(0x38,  vsfactor>>16);	// V
				WordWriteScaler	(0x39,	vsfactor);	

			break;	
		default:
			break;
	}	
}

void SetScalerInputActive(BYTE Recdata)
{
	switch(Recdata)
	{
		case	0:			//LineSyncMode!
		case	2:			//FrameMode!
		case	6:			//DVI!
			WordWriteScaler(0x04,NowHactive);
			WordWriteScaler(0x0A,NowVactive);
			break;
		
		case	8://composite linesync
		case	10://composite framesync
		case	12://s-video linesync
		case	14://s-video framesync
		case	16://tuner linesync
		case	18://tuner framesync
			WordWriteScaler(0xA0,BIHAW);
			WordWriteScaler(0xA6,BIVAW*2);
			break;
		
		case	20://RGB+COMPOSITE(PIP)
		case	28://RGB+S-VIDEO(PIP)
		case	52://RGB+TUNER(PIP)
		case	36://DVI+COMPOSITE
		case	44://DVI+SIVIDEO
		case	60://DVI+TUNER
			WordWriteScaler(0x04,NowHactive);
			WordWriteScaler(0x0A,NowVactive);

			WordWriteScaler(0xA0,BIHAW);
			WordWriteScaler(0xA6,BIVAW*2);

			break;
		default:
			break;
	}
}

void SetScalerDclkPLL(double Clock)
{
#define PLLIVD_M	10
BYTE p_dclk,n_dclk;

	Clock=0;//dummy

	/////////////////////////////////////////////////////////////////////
	// DCLK PLL set!!
	/////////////////////////////////////////////////////////////////////
	if     (NowScalerDCLK > 66000000.0) p_dclk = 0;
	else if(NowScalerDCLK > 38000000.0) p_dclk = 1;
	else                       p_dclk = 2;

	NowScalerDCLK *= ( ((WORD)PLLIVD_M+2)<<p_dclk );
	n_dclk = (BYTE)(NowScalerDCLK / 14318181.8l - 8)+1;
	BitWriteScaler(0x28,0x01,0);
	WriteScaler(0x2C, PLLIVD_M|(p_dclk<<6));		// DCLK_PLL1VD[15:8]
	WriteScaler(0x2D, n_dclk);						// DCLK_PLL1VD[7:0]
	BitWriteScaler(0x28,0x01,1);	
}


void SetScalerMclkPLL(double Clock)
{
#define PLLIVD_M	10
BYTE p_mclk,n_mclk;

	Clock=0;//dummy

	/////////////////////////////////////////////////////////////////////
	// MCLK PLL set!!
	/////////////////////////////////////////////////////////////////////
	if     (NowScalerMCLK > 66000000.0) p_mclk = 0;
	else if(NowScalerMCLK > 38000000.0) p_mclk = 1;
	else                       p_mclk = 2;
	
	NowScalerMCLK *= ( ((WORD)PLLIVD_M+2)<<p_mclk );
	n_mclk = (BYTE)(NowScalerMCLK / 14318181.8l - 8);
	BitWriteScaler(0x27,0x01|0x02,0);
	WriteScaler(0x2a, PLLIVD_M|(p_mclk<<6));	// MCLK_PLL1VD[15:8]
	WriteScaler(0x2b, n_mclk);					// MCLK_PLL1VD[7:0]
	BitWriteScaler(0x27,0x01,1);		
}

void SetScalerHPostion(BYTE Recdata)
{
	switch(Recdata)
	{
		case	8://composite linesync
		case	10://composite framesync
		case	12://s-video linesync
		case	14://s-video framesync
		case	16://tuner linesync
		case	18://tuner framesync
			//기존 소스를 VideoParameter.h에서 상수값을 받게 한다.
			#ifdef Memory_1eaUse
				if(NowVideo50Hz)	WordWriteScaler(0x9e,IBHAS_Main50Hz_value+2);	//Bchannel IHAS	
				else				WordWriteScaler(0x9e,IBHAS_Main60Hz_value+2);	//Bchannel IHAS
			#else
				if(NowVideo50Hz)	WordWriteScaler(0x9e,IBHAS_Main50Hz_value);	//Bchannel IHAS	//2004-01-27
				else				WordWriteScaler(0x9e,IBHAS_Main60Hz_value);	//Bchannel IHAS
			#endif
			/*
			#ifdef USE_NTSCtuner
				WordWriteScaler(0x9e,IBHAS_Main60Hz_value);	//Bchannel IHAS
			#else
				WordWriteScaler(0x9e,IBHAS_Main50Hz_value);	//Bchannel IHAS
			#endif
			*/
			break;
			
		case	20://RGB+COMPOSITE(PIP)
		case	28://RGB+S-VIDEO(PIP)
		case	52://RGB+TUNER(PIP)
			//WordWriteScaler(0x02,(ModeList[CurrentMode].IHAS+(BYTE)EEPROM_Read(CurrentMode*4+0))-0x80);	//2003-07-15 removed
			WordWriteScaler( 0x02, ModeList[CurrentMode].IHAS+0x80-(BYTE)EEPROM_Read(CurrentMode*4+0) );	//2003-07-28

			
			#if defined(SAA7114)
			WordWriteScaler(0x9e,107);	//Bchannel IHAS
			#elif defined(SAA7115)
			WordWriteScaler(0x9e,107);	//Bchannel IHAS
			#elif defined(VPC323x)
			WordWriteScaler(0x9e,108);	//Bchannel IHAS
			#elif defined(TW9908)
				//WordWriteScaler(0x9e,108);	//Bchannel IHAS youngdo
				
				if(NowVideo50Hz)	WordWriteScaler(0x9e,IBHAS_Main50Hz_value);	//Bchannel IHAS	//2004-01-27
				else				WordWriteScaler(0x9e,IBHAS_Main60Hz_value);	//Bchannel IHAS
				/*
				#ifdef USE_NTSCtuner
				WordWriteScaler(0x9e,IBHAS_Main60Hz_value);	//Bchannel IHAS //2003-08-01 10:06오후
				#else
				WordWriteScaler(0x9e,IBHAS_Main50Hz_value);	//Bchannel IHAS
				#endif
				*/
			#endif
				
			break;
			
		#ifdef DVI_USE	
		case	36://DVI+COMPOSITE
		case	44://DVI+SIVIDEO
		case	60://DVI+TUNER

			
			#if defined(SAA7114)
			WordWriteScaler(0x9e,107);	//Bchannel IHAS
			#elif defined(SAA7115)
			WordWriteScaler(0x9e,107);	//Bchannel IHAS
			#elif defined(VPC323x)
			WordWriteScaler(0x9e,108);	//Bchannel IHAS
			#elif defined(TW9908)
				//WordWriteScaler(0x9e,108);	//Bchannel IHAS youngdo
				WordWriteScaler(0x9e,IBHAS_Main60Hz_value);	//Bchannel IHAS //2003-08-01 10:07오후
			#endif
				
			WordWriteScaler(0x02,0);//Have to odd for DVI(1280)
			
			break;
		
		case	4://DVI Not-Frame
		case	6://DVI Frame
			WordWriteScaler(0x02,0);//Have to odd for DVI(1280)
			break;
		#endif
		
			
		default://RGB
			//WordWriteScaler(0x02,(ModeList[CurrentMode].IHAS+(BYTE)EEPROM_Read(CurrentMode*4+0))-0x80);	
			WordWriteScaler(0x02, ModeList[CurrentMode].IHAS+0x80-(BYTE)EEPROM_Read(CurrentMode*4+0));	//2003-05-30
			break;
	}
}


void SetScalerVPostion(BYTE Recdata)
{
	BYTE temp;

	switch(Recdata)
	{
		case	8://composite linesync
		case	10://composite framesync
		case	12://s-video linesync
		case	14://s-video framesync
		case	16://tuner linesync
		case	18://tuner framesync
			//기존 소스를 VideoParameter.h에서 상수값을 받게 한다.
			#if 1
					WordWriteScaler(0xa2,IBVAS_Main60Hz_value);	//Odd!!,  //Bchannel IVAS
					WordWriteScaler(0xa4,IBVAS_Main60Hz_value);	//Even!!  //Bchannel IVAS
			#else
			switch(xEEPROMBuffer[DisplayAspcet_buf])
			{	//모두같음
				case aspect4_3:
					WordWriteScaler(0xa2,IBVAS_Main60Hz_value);	//Odd!!,  //Bchannel IVAS
					WordWriteScaler(0xa4,IBVAS_Main60Hz_value);	//Even!!  //Bchannel IVAS//2003-08-01 9:50오후
					break;		
				case aspect16_9:
					WordWriteScaler(0xa2,IBVAS_Main60Hz_value);	//Odd!!,  //Bchannel IVAS
					WordWriteScaler(0xa4,IBVAS_Main60Hz_value);	//Even!!  //Bchannel IVAS//2003-08-01 9:50오후
					break;		
				case aspect_full:
					WordWriteScaler(0xa2,IBVAS_Main60Hz_value);	//Odd!!,  //Bchannel IVAS
					WordWriteScaler(0xa4,IBVAS_Main60Hz_value);	//Even!!  //Bchannel IVAS//2003-08-01 9:50오후
					break;		
			}
			#endif
			break;
		
		case	20://RGB+COMPOSITE(PIP)
		case	28://RGB+S-VIDEO(PIP)
		case	52://RGB+TUNER(PIP)
			temp=(BYTE)EEPROM_Read(CurrentMode*4+1);
			WordWriteScaler(0x06,temp);
			WordWriteScaler(0x08,temp);
			
			if(NowVideo50Hz)
			{
				WordWriteScaler(0xa2,IBVAS_Main50Hz_value);		//Odd!!,  //Bchannel IVAS
				WordWriteScaler(0xa4,IBVAS_Main50Hz_value);		//Even!!  //Bchannel IVAS
			}
			else
			{
				WordWriteScaler(0xa2,IBVAS_Main60Hz_value);		//Odd!!,  //Bchannel IVAS
				WordWriteScaler(0xa4,IBVAS_Main60Hz_value);		//Even!!  //Bchannel IVAS
			}
			/*
			#if defined(USE_NTSCtuner)
				WordWriteScaler(0xa2,IBVAS_Main60Hz_value);		//Odd!!,  //Bchannel IVAS
				WordWriteScaler(0xa4,IBVAS_Main60Hz_value);		//Even!!  //Bchannel IVAS
			#elif defined(USE_PALSECAMtuner)
				WordWriteScaler(0xa2,IBVAS_Main50Hz_value);		//Odd!!,  //Bchannel IVAS
				WordWriteScaler(0xa4,IBVAS_Main50Hz_value);		//Even!!  //Bchannel IVAS
			#endif
			*/
			break;

		case	6:
		case	36://DVI+COMPOSITE
		case	38://DVI+COMPOSITE((NO)
		case	44://DVI+SIVIDEO
		case	46://DVI+SVIDEO(NO)
		case	60://DVI+TUNER
			WordWriteScaler(0x06,0);
			WordWriteScaler(0x08,0);
			
			#if defined(USE_NTSCtuner)

			WordWriteScaler(0xa2,19);				//Odd!!,  //Bchannel IVAS
			WordWriteScaler(0xa4,19);				//Even!!  //Bchannel IVAS
		
			#elif defined(USE_PALSECAMtuner)
				WordWriteScaler(0xa2,19);				//Odd!!,  //Bchannel IVAS
				WordWriteScaler(0xa4,19);				//Even!!  //Bchannel IVAS
			#endif
			
			break;

		default://RGB
			temp=(BYTE)EEPROM_Read(CurrentMode*4+1);
			WordWriteScaler(0x06,temp);
			WordWriteScaler(0x08,temp);
			break;
	}
}


void SetScalerFMuse(BYTE Recdata)
{
	switch(Recdata)
	{
		case	0://Linesync Mode
		case	8://composite linesync
		case	12://s-video linesync
		case	16://tuner linesync
			WriteScaler(0x2F,0x08);
			break;
		
		case	2://Frame Mode
		case	20://RGB+COMPOSITE(PIP)
		case	28://RGB+S-VIDEO(PIP)
		case	52://RGB+TUNER(PIP)
			#if defined(Memory_1eaUse)
			WriteScaler(0x2F,BIN_TO_BYTE(0,0,0,0,1,0,0,0));
			#else
			WriteScaler(0x2F,BIN_TO_BYTE(0,0,0,1,0,1,0,0));
			#endif
			BitWriteScaler(0xA9,0x20,0);//DEMODE disable!
			break;	

		#ifdef DVI_USE
		case	6://DVI FMMODE
		case	36://DVI+COMPOSITE
		case	44://DVI+SIVIDEO
		case	60://DVI+TUNER
		case	38://DVI+COMPOSITE((NO)
		case	46://DVI+SVIDEO(NO)
			if(Recdata==4)WriteScaler(0x2F,0x08);
			else WriteScaler(0x2F,0x14);
			BitWriteScaler(0xA9,0x20,1);//DEMODE!
			break;
		#endif
/*		
		case	7:			//FreeRun Mode
			WriteScaler(0x2F,0x00);
			break;
*/		
		case	10://composite framesync
		case	14://s-video framesync
		case	18://tuner framesync
			#if defined(EMH1A)
			WriteScaler(0x2F,BIN_TO_BYTE(0,0,0,1,1,1,0,0));
			#elif defined(EMH2)
//youngdo 2003.5.24			WriteScaler(0x2F,BIN_TO_BYTE(0,0,1,1,0,1,0,0));
			WriteScaler(0x2F,BIN_TO_BYTE(0,0,0,1,0,1,0,0));	//freerun mode
			#else
			WriteScaler(0x2F,BIN_TO_BYTE(0,0,0,1,1,1,0,0));
			#endif
			
			BitWriteScaler(0xA9,0x20,0);//DEMODE disable!
			break;

		default:
			break;
	}
}

/*
실제 VESA standard Mode의 클럭계산(ADC output clock)
1280x1024@60
DCLK = 108MHz

108.000MHz 	= Horizontal Total * Vertical Total * Vfreq
			= 1688 x 1066 x 60Hz
			= 107964480
			= 108MHz
			



판넬의 중간체인 스케일러 출력 클럭계산
DCLK = (PanelVerticalsize/IVAW)*Now_Hf*PanelMinHTotal

ex)XGA Panel!!

IVAW			: Vertical Display Width VGA(480),SVGA(600),XGA(768)
PanelVerticalsize		: 768
Now_Hf			: 485(real Freq 485x100)
PanelMinHTotal	: 1056
DCLK = 768/768*48500*1056 	= 51216000
							= 51.2MHz

PanelMinHTotal(1056) =

     __________________________________________
    |					       |	   |
    |<------      1024CLK	       ------->|<- 32CLK ->|
____|					       |___________|
	 
    <-------------------- 1056CLK ------------------>
*/

#define WCYCLE	4
#define RCYCLE	4
//#define MCLKDCLKRATIO	1.26//2003-03-05 12:26오후
#define MCLKDCLKRATIO	1.2
#define LMCLKDCLKRATIO	1.35
#define MAX_MCLOCK	134000000.0


double ExtractCLK(BYTE Recdata)
{
	WORD ivt;
	WORD vaw;
	WORD WClks;
	WORD RClks;
	double idata MclkLimit;
	double idata mclk;
	double idata dclk;
	
	switch(Recdata)
	{
		case	0://PC Non Frame Mode!
				ivt = (ReadScaler(0x6F)&0x07)<<8|ReadScaler(0x70);			//scaler의 측정된 input VTotal값.
				vaw = NowVactive;
				NowScalerDCLK=(double)PanelMinHTotal * GetDVTotal(ivt,vaw) * NowHfreq * 102 / ivt;	// 2% tolerance
				NowScalerMCLK = 0;
				return 0;
			break;

		case	2://PC Frame Mode!
		case	6://DVI FMMODE!
		case	20://RGB+COMPOSITE
		case	28://RGB+SVIDEO
		case	52://RGB +TUNER
		case	36://DVI+COMPOSITE
		case	44://DVI+SIVIDEO
		case	60://DVI+TUNER
				ivt = (ReadScaler(0x6F)&0x07)<<8|ReadScaler(0x70);			//scaler의 측정된 input VTotal값.
				vaw = NowVactive;
				NowAdcCLK =  (double)NowHtotal*NowHfreq*100;
				//MCLK를 산출하기 위한 1차 DCLK
			#if defined(WXGA_Panel)
				//dclk=(double)PanelMinHTotal * GetDVTotal(ivt,vaw) * NowHfreq * 100 / ivt;	// 2% tolerance	//2003-09-26
				//dclk=(double)PanelMinHTotal * GetDVTotal(ivt,vaw) * NowHfreq * 75 / ivt;	// 2% tolerance	//2003-09-26
				//dclk = 50.0*PanelMinHTotal*PanelMinVTotal; 
				dclk = 60.0*PanelMinHTotal*PanelMinVTotal; 
			#else
				//dclk=(double)PanelMinHTotal * GetDVTotal(ivt,vaw) * NowHfreq * 102 / ivt;	// 2% tolerance	//2003-09-26
				dclk=(double)PanelMinHTotal * GetDVTotal(ivt,vaw) * NowHfreq * 120 / ivt;	// 2% tolerance	//2003-09-26
			#endif
				//dclk = 65.0*PanelMinHTotal*PanelMinVTotal;
				//dclk = 64.0*PanelMinHTotal*PanelMinVTotal; // 2003-03-05 12:01오후		//2003-09-26 removed by thkim
				//1. MCLK Limit 산출
				//2. MCLK Limit값과 비교후 셋팅
				WClks=((NowHactive+255)/256)*WCYCLE;
				RClks=(DWORD)NowHactive*NowVactive/PanelVerticalsize;
				RClks+=((NowHtotal+0x80) - NowHactive)
				     -((double)(NowHtotal+0x80) - NowHactive)
				     *(NowHactive + PanelHerizontalsize)
				     /((NowHtotal+0x80) + PanelHerizontalsize + WClks);
    			
				WClks=WClks + NowHactive;
				RClks=RClks + ((RClks+255)/256)*RCYCLE*2;
				WClks=WClks+RClks;
				RClks=PanelMinHTotal-PanelHerizontalsize;
				WClks=(DWORD)WClks*(WClks+RClks/2)/(WClks+RClks);
				
				//mclk Limit
				//Critical Issue!!   (double) why???
				MclkLimit=(double)(NowHfreq*100)*WClks/2+1300000;
				//MclkLimit=(NowHfreq*100)*WClks/2+1300000;
				
				//mclk
				mclk = dclk*MCLKDCLKRATIO;
				
				//Limit보다 작으면.. Limit값으로..
				if(MclkLimit>mclk)
				
				{
					NowScalerMCLK = MclkLimit;
					NowScalerDCLK = NowScalerMCLK/LMCLKDCLKRATIO;
				}
				//Max보다 크면 Max값으로..
				else if(mclk>=MAX_MCLOCK)
				{
					NowScalerMCLK = MAX_MCLOCK;
					NowScalerDCLK = dclk;
				}
				//
				else
				{
					NowScalerMCLK = mclk;
					NowScalerDCLK = dclk;
				}
				return 0;
			break;
		
		case	8://Linesync composite
		case	12://Linesync s-video
		case	16://Linesync tuner
			ivt = 262;
			vaw = BIVAW;
			NowHfreq = 158;//15.7khz
			NowVideoCLK=(DWORD)858*30*525;
			NowScalerDCLK=(double)PanelMinHTotal * GetDVTotal(ivt,vaw) * NowHfreq * 102 / ivt;	// 2% tolerance
			NowScalerMCLK = 0;
			return 0;
			break;
		
		case	10://Framesync composite
		case	14://Framesync s-video
		case	18://Framesync tuner
/*			if(NowVideo50Hz)
			{
				ivt = 312;
				NowHfreq = 157;//15.6khz
				NowVideoCLK=(DWORD)864*30*625;
			}
			else
			{
				ivt = 262;
				NowHfreq = 158;//15.7khz
				NowVideoCLK=(DWORD)858*30*525;
			}
*/
			ivt = 262;
			NowHfreq = 158;//15.7khz
			NowVideoCLK=(DWORD)858*30*525;
			vaw = BIVAW;
			
			
			//NowScalerDCLK=(double)PanelMinHTotal * GetDVTotal(ivt,vaw) * NowHfreq * 102 / ivt;	// 2% tolerance
			//dclk = 65.0*PanelMinHTotal*PanelMinVTotal;
			//상단 클럭으로 셋팅시 화면깨짐, 즉 RGB dclk,mclk와 비디오은 다르게 클럭계산..
		#if defined(WXGA_Panel)
			#ifdef USE_NTSCtuner
			dclk=(double)PanelMinHTotal * GetDVTotal(ivt,vaw) * NowHfreq * 92 / ivt;	// 2% tolerance
			#else
			dclk=(double)PanelMinHTotal * GetDVTotal(ivt,vaw) * NowHfreq * 100 / ivt;	// 2% tolerance
			#endif
		#else
			dclk=(double)PanelMinHTotal * GetDVTotal(ivt,vaw) * NowHfreq * 102 / ivt;	// 2% tolerance
		#endif
			//dclk=(double)PanelMinHTotal * GetDVTotal(ivt,vaw) * NowHfreq * 92 / ivt;	// 2% tolerance	//2003-09-26
			//dclk=(double)PanelMinHTotal * GetDVTotal(ivt,vaw) * NowHfreq * 98 / ivt;	// 2% tolerance	//2003-09-26
			
			WClks=((BIHAW+255)/256)*WCYCLE;
				RClks=(DWORD)BIHAW*BIVAW/PanelVerticalsize;
				RClks+=(858 - BIHAW)
				     -((double)858-BIHAW)
				     *(BIHAW + PanelHerizontalsize)
				     /(858 + PanelHerizontalsize + WClks);
    			
				WClks=WClks + BIHAW;
				RClks=RClks + ((RClks+255)/256)*RCYCLE*2;
				WClks=WClks+RClks;
				RClks=PanelMinHTotal-PanelHerizontalsize;
				WClks=(DWORD)WClks*(WClks+RClks/2)/(WClks+RClks);
				MclkLimit=(double)NowHfreq*100*WClks/2+1300000;
				//mclk = NowScalerDCLK*MCLKDCLKRATIO;
				mclk = dclk*MCLKDCLKRATIO;
				
				if(MclkLimit>mclk)
				{
					NowScalerMCLK = MclkLimit;
					NowScalerDCLK = NowScalerMCLK/LMCLKDCLKRATIO;
				}
				else if(mclk>=MAX_MCLOCK)
				{
					NowScalerMCLK = MAX_MCLOCK;
					//NowScalerDCLK = NowScalerDCLK;
					NowScalerDCLK = dclk;
				}
				else
				{
					NowScalerMCLK = mclk;
					//NowScalerDCLK = NowScalerDCLK;
					NowScalerDCLK = dclk;
				}
				return 0;
			break;
		default:
			break;
	}
}

void ScalerSet(void)
{
	//Input 관련
	ExtractCLK(xEEPROMBuffer[MainSubInputSource]);					//VIDEO,ADC,FrameCLK extract!!
	SetScalerInputOutputColorCondition(xEEPROMBuffer[MainSubInputSource]);
	SetScalerInputCondition(xEEPROMBuffer[MainSubInputSource]);		//scaler의 입력조건을 ..
	SetScalerInputIBRQS(xEEPROMBuffer[MainSubInputSource]);			//IBRQS set!
	SetScalerInputActive(xEEPROMBuffer[MainSubInputSource]);		//Input size set!(A,B-Port Area set!)
	SetScalerInputHVLock(xEEPROMBuffer[MainSubInputSource]);		//Input Locking set!
	SetScalerHPostion(xEEPROMBuffer[MainSubInputSource]);			//Input H-start position,EEPROM에서 읽어 셋팅
	SetScalerVPostion(xEEPROMBuffer[MainSubInputSource]);			//Input V-start position,EEPROM에서 읽어 셋팅
			
	//Display, Memory clock,Linerate관련
	SetScalerDclkPLL(xEEPROMBuffer[MainSubInputSource]);	//Dclk PLL set!
	SetScalerMclkPLL(xEEPROMBuffer[MainSubInputSource]);	//Mclk PLL set!
	SetLinerate(xEEPROMBuffer[MainSubInputSource]);

	//Frame,Linesync,FreeRun,DVI MODE, DEMODE LOCK, DEMODE Sync Sel 선택관련
	SetScalerFMuse(xEEPROMBuffer[MainSubInputSource]);

	//Frame Offset,Delay,Deinterlace,...
	SetScalerFMothers(xEEPROMBuffer[MainSubInputSource]);

	//Zoom관련
	if(MenuNum==menu_pip_size||MenuNum==menu_pip_AspectRatio) WriteScaler(0x9a,0x00);//PIP OFF//2003-10-16
	SetScalerZoomFactor(xEEPROMBuffer[MainSubInputSource]);

	//Output관련
	SetScalerOutputHVLockLoad(xEEPROMBuffer[MainSubInputSource]);	//Output H,V LockLoad set!
	SetScalerOutputHVTotal(xEEPROMBuffer[MainSubInputSource]);	//Output H,V Total
	SetScalerOutputOREQSTART(xEEPROMBuffer[MainSubInputSource]);
	SetScalerPIPOutputCondition(xEEPROMBuffer[MainSubInputSource]);	//PIP
}
	
	
	