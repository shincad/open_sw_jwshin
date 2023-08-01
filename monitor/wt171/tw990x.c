#include	"TopHeader.h"
#include "MTV230xfr.H"
#include	<stdio.h>
//#include <reg51.h>
#include "power.h"
#include "tw990x.h"
#include "extern.h"
#include "eepromadr.h"
#include "btc_osdmenu.h"
#include "tuner.h"

#if defined(TW9908)



#define TW990x_Addr		0x88

//****************************************************************//
//변수선언
//****************************************************************//
extern	BYTE	PowerOnsequence;
extern	xdata	BYTE	xEEPROMBuffer[MaxEepromBuffer];
extern	WORD	PowerOnTimer;
extern	bit		VideoActiveCompleted;
extern	BYTE	CurrentFunction;
extern	BYTE	OSDcharacters;
extern	BYTE	OSDWindows;
extern	BYTE	OSDstatus;
extern 	BYTE	PowerOnsequence;
//extern	BYTE	OSDcusorPosition;
extern	BYTE	SyncStableTimer;
extern	bit		PipOnOffFlag;
extern	bit		NoExistHfreq;
extern	bit		NoExistVfreq;


extern	bit	PipFastChange;

void AVDecoder_Init(void);
void SetAV_Brightness(void);
void SetAV_Contrast(void);
void SetAV_Saturation(void);
void SetAV_Tint(void);
void SetAV_Sharpness(void);
void AVDecoderSleep(void);
void AVDecoder_SelectInputPort();
void AVDecoder_ModeSetting(BYTE);
void CheckVideoSignal(void);
void CheckVideo(void);
void CheckTVSignal(unsigned char Count); 		//  1.27 cho
void CheckTVSignalChange();
void ArrangeFunctionTable(void);
void SetScalerPIPOutputCondition(BYTE Recdata);
void PipSubRegisterSet(void);
void ChangeToVideo50Hz60HzSystem();
BYTE EEPROM_Read(WORD address);
void EepromSetQue(WORD address, BYTE Recdata);
void SetScalerZoomFactor(BYTE Recdata);



extern	void PipHVPosition(void);
extern	void SetScalerOutputHVTotal(BYTE Recdata);
extern	void WordWriteScaler(BYTE address, WORD Recdata);//test
extern	void BitWriteScaler(BYTE address, BYTE BitArry, BYTE Recdata);

#ifdef USE_TTX
void SDA555xInit();
#endif

#ifdef	USE_4BitInterface								//4bit통신 함수선언
void	WriteReg4bit(BYTE address, BYTE Recdata);
#define	WriteScaler(val1,val2) WriteReg4bit(val1,val2)	
#else													//1bit통신 함수선언
void	WriteReg1bit(BYTE address, BYTE Recdata);
#define	WriteScaler(val0, val1) WriteReg1bit(val0, val1)
#endif


bit WriteI2C(BYTE sysaddr, BYTE subaddr, BYTE writedata);
WORD ReadI2C(BYTE SystemAdr, WORD address);

code BYTE TW990x_ResetTable[] =
{	      				//NTSC
		
//******************************************
//원래는 초기화 되야 하는데 간혹 안되서 강제로 초기화.

	0x04,				0x00,
	0x05,				0x00,
	0x06,				0x40,	
	0x07,				0x02,
	0x08,				0x15,
	0x09,				0xf0,
	0x0a,				0x80,
	0x0b,				0xd0,
	0x0c,				0x8c,
	0x0d,				0x00,
	0x0e,				0x11,
	0x0f,				0x00,
	0x10,				0x00,
	0x11,				0x60,
	0x12,				0x51,
	0x13,				0x7f,
	0x14,				0x5a,
	0x15,				0x00,
	//0x16,				0xc3,
	0x16,				0xc0,//2003-11-21
//	0x17,				0x80,
	0x18,				0x00,
	0x19,				0x58,
	0x1a,				0x80,
	0x1e,				0x00,
	0x1f,				0x00,
	//0x20,				0xa0,
	0x20,				0x57,	//2004-05-19	clamp 일정값이하에서는 특정패턴에서 규칙적가로줄무늬가 나타남.
	0x21,				0x22,
	0x22,				0xf0,
	0x23,				0xfe,
	//#ifdef WXGA_Panel
//	0x23,				0xa0,	//2003-11-18
	//#endif
	//0x24,				0x3c,
	//0x24,				0x33,	//2003-11-21
	//0x24,				0x47,	//2004-05-19
	#ifdef USE_NTSCtuner
	0x24,				0x45,	
	#else
	0x24,				0x4e,	//2004-07-01
	#endif
	0x25,				0x38,
	//0x25,				0x30,	//2003-11-05
	0x27,				0x20,
	//0x27,				0x08,	//2003-11-21
	0x28,				0x00,
	0x29,				0x15,
	0x2a,				0xa0,
	0x2b,				0x44,
	0x2c,				0x37,
	0x2d,				0x00,
	0x30,				0x00,
	0x31,				0x10,
	0x32,				0xa0,
	0x33,				0x22,
	0x34,				0x11,
	0x35,				0x35,
	0x36,				0x72,	
	0x39,				0x00,	
	//0x3B,				0x05,	//2003-09-02
	//0x3B,				0x14,	//2003-11-05
	//0x3B,				0x25,	//2003-11-05
	0x3B,				0x05,	//2004-05-19
	0x3C,				0xE3,	
	0x3D,				0x20,	
	0x3E,				0xAF,	
	0x3F,				0x00,	
	0x40,				0x00,	
	0x41,				0x40,	
	0x42,				0x40,	
	0x43,				0xC0,	
	0x44,				0x00,	
    	0x00	// 마지막을 나타내는 데이터임.
};

code BYTE TW990x_Table_Init[] =
{	      				//NTSC

//*********************************************
//실제 필요한 셋팅 

	TW99_ACNTL,		0x40,		//
	TW99_INFORM,		0x40,
//	TW99_OPFORM,		0x92,		//656 format
	TW99_OPFORM,		0x52,		//601 format
	TW99_CROP_HI,		0x13,
	TW99_VDELAY_LO,		0x02,		//youngdo 2003.5.19
//	TW99_VACTIVE_LO,	0x10,		//youngdo 2003.5.19ntsc
	TW99_VACTIVE_LO,	0x40,		//youngdo 2003.5.19  PAL
	TW99_HDELAY_LO,		0x3A,		//youngdo 2003.5.19 0x90,
	TW99_HACTIVE_LO,	0x28,
	TW99_SDT,			0x07,
	TW99_SDTR,			0x7f,
	TW99_CLMPG,			0x57,	//2004-05-19 //0x50,
	//#ifdef WXGA_Panel
	
	//#endif
	TW99_MISSCNT,		0x4c,		//remove vcr jitter
	TW99_VCNTL,		0x02,		//aflf on.
	TW99_MISC2,		0xa9,
	TW99_MISC3,		0xE2,	// no video blue 0xe6,	
//  RGB, FB  control	
	TW99_SBRIGHT,		0x20,
	TW99_SCONTRAST,		0x70,
	TW99_RGBCNTL,		0x01,	//RGB on,FB enable
	TW99_SCBGAIN,		0x40,	//sub is RGB,DAC enable
	#if defined	(SSWide_D01)
	TW99_PEAKWT,		0xe0,	//2003-11-18
	#elif defined	(SSWide_000)
	TW99_PEAKWT,		0xa0,	//2003-11-18
	#else	
	TW99_PEAKWT,		0xc0,	//2004-05-10	//LG W03 (유효값 0x9a~0xd0)
	#endif
//	TW99_VSHARP,		0x84,
	TW99_VSHARP,		0x80,		// smpark 20030730
	TW99_CNTRL1,		0x9c,		//

	TW99_ACNTL,		0xc0,	
    	0x00	// 마지막을 나타내는 데이터임.
};

void TW990xWrite(BYTE SubAddr,BYTE Data)
{
//   SendStart();
   WriteI2C(TW990x_Addr,SubAddr,Data);
 
   //SendStop();
}

BYTE TW990xRead(BYTE SubAddr)
{
   BYTE Data;
   Data= (BYTE)ReadI2C(TW990x_Addr,SubAddr);
   return Data;
}

// 값이 0이면 wirte종료된다.
void TW990x_RegInit(unsigned char *B_Addr_Table)
{

	while(*B_Addr_Table){
		TW990xWrite(*B_Addr_Table++,*B_Addr_Table++);
//		DelayNOP25();
//		DelayNOP25();
//		DelayNOP25();
//		DelayNOP25();
//		DelayNOP25();
//		DelayNOP25();
//		DelayNOP25();
	}
}

/*
void AVDecoderSleep(void)
{
	TW990xWrite(TW99_ACNTL,0x0f);
}


void AVDecoderWakeup(void)
{
	TW990xWrite(TW99_ACNTL,0xC0);
}
*/

void VideoDecoderInit(void)
{
	DBGputs("VideoDecoderInit");

	TW990x_RegInit(TW990x_ResetTable); //Parameters loading  
	TW990x_RegInit(TW990x_Table_Init); //Parameters loading  
	TW990x_RegInit(TW990x_Table_Init); //Parameters loading  
	TW990x_RegInit(TW990x_Table_Init); //Parameters loading  
	
	TW990xWrite(TW99_BRIGHT,0);
	TW990xWrite(TW99_CONTRAST,0x60);	
	
	TVColorSet();	
	
	SetBlueScrren(xEEPROMBuffer[BscrFlag_buf]);
	
	VideoInitUnit=0;
}

void AVDecoder_SelectInputPort()
{
	BYTE value;

	value = TW990xRead(TW99_INFORM)&0xc2;

	ArrangeFunctionTable();
	switch(CurrentFunction){
		case 3:                 // Svideo input ? 	
		case 6:			//PIP R+S
		case 9:			//PIP D+S
			value|=0x18;
			break;
		case	2:           // Composite input ?
		case 	5:		//PIP R+C
		case	8:		//PIP D+C
			value|=0x04;
//			value|=0x0D;			//scart test
			break;
		case	4:               	// TV input?
		case 	7:			//PIP R+T
		case	10:			//PIP D+T
			value|=0x00;
			SoundMuteTvTimer=0;
			TunerProcessing = 1;
			break;
#if defined(USE_SCART)			
		case	11:               	// SCART input?
		case 	12:			//PIP R+SCART
		case	13:			//PIP D+SCART
			value|=0x0D;
			break;	
#endif

		default:
			return;
	}
	
	 TW990xWrite(TW99_INFORM,value);

	VideoActiveCompleted = 1;
}



#ifdef	TestTunerSound
BYTE	testI2Cflag=1;	//testI2Cflag 1: 기존, 0: i2c 중단...
#endif
	
void VideoProcess(void)
{
	
	#ifdef CheckVideoStatus
	static BYTE idata VideoCheckTimer=0;
	static bit ReVideoDecoderSetting=0;
	static	BYTE idata NoVideoChattering=0;
	BYTE temp;
	static BYTE idata Video50HzTimer=0;
	static BYTE idata Video60HzTimer=0;
	#endif
	
	if(PowerOnsequence<PowerOnNormalStatus) return;
	if(xEEPROMBuffer[MainSubInputSource] < 0x08) return;//It's not video mode, return to main.


	
	//Video set후(video noraml display)에 No-Video Check(20ms 마다)
	#ifdef CheckVideoStatus
	//---------------------------------------------------------
	if(VideoActiveCompleted)
	{
		++VideoCheckTimer;
		if(VideoCheckTimer%4) return;

		#ifdef TestTunerSound//---------------------//2004-04-03
		{
			if(testI2Cflag)	temp = TW990xRead(0x01);	//Reading Decoder Status!! (0: NTSC, 1:PAL)
			else temp=0x01;
		}
		#else

		if(1)	temp = TW990xRead(0x01);	//Reading Decoder Status!! (0: NTSC, 1:PAL)
		//if(0)	temp = TW990xRead(0x01);	//Reading Decoder Status!! (0: NTSC, 1:PAL)
		else 
		{
			#if defined(USE_NTSCtuner)
			temp=0x00;
			#else 
			temp=0x01;
			#endif
		}
		#endif

		//if((!(temp&0x20))&&(PowerOnsequence>=MenuValueLoadandApply)&&CurrentFunction!=4&&CurrentFunction!=7&&CurrentFunction!=10)//50Hz검사, 파워시컨스가 이상되면
		//if((temp&0x01)&&(PowerOnsequence>=MenuValueLoadandApply)&&CurrentFunction!=4&&CurrentFunction!=7&&CurrentFunction!=10)//50Hz검사, 파워시컨스가 이상되면
		if((temp&0x01)&&(PowerOnsequence>=MenuValueLoadandApply))//50Hz검사, 파워시컨스가 이상되면
		{
			++Video50HzTimer;//60Hz->50Hz change!!
			if(Video50HzTimer==5)
			{
				//InvertOff;//
				Video60HzTimer=0;
				NowVideo50Hz=1;
				ChangeToVideo50Hz60HzSystem();
				SetScalerOutputHVTotal(xEEPROMBuffer[MainSubInputSource]);	//Output H,V Total//
				SetScalerZoomFactor(xEEPROMBuffer[MainSubInputSource]);	//☆☆☆
				SetScalerPIPOutputCondition(xEEPROMBuffer[MainSubInputSource]);	//2003-08-20
				//MUTEOFF;
				//AVDecoderWakeup();
				
				#ifdef USE_UART
				DBGputs("TO 50Hz");
				#endif
			}
			else
			{
				Video60HzTimer=0;
				if(Video50HzTimer==0xFE) Video50HzTimer=5;//One-Time!!
			}
		}

		//if((temp&0x20)&&(PowerOnsequence>=MenuValueLoadandApply)&&CurrentFunction!=4&&CurrentFunction!=7&&CurrentFunction!=10)//60Hz, 파워시컨스가 이상되면
		//if((!(temp&0x01))&&(PowerOnsequence>=MenuValueLoadandApply)&&CurrentFunction!=4&&CurrentFunction!=7&&CurrentFunction!=10)//60Hz, 파워시컨스가 이상되면
		if((!(temp&0x01))&&(PowerOnsequence>=MenuValueLoadandApply))//60Hz, 파워시컨스가 이상되면
		{
			++Video60HzTimer;//50Hz->60Hz change!!
			if(Video60HzTimer==5)
			{
				//InvertOff;//
				Video50HzTimer=0;
				NowVideo50Hz=0;
				ChangeToVideo50Hz60HzSystem();
				SetScalerOutputHVTotal(xEEPROMBuffer[MainSubInputSource]);	//Output H,V Total//
				SetScalerZoomFactor(xEEPROMBuffer[MainSubInputSource]);	//☆☆☆
				SetScalerPIPOutputCondition(xEEPROMBuffer[MainSubInputSource]);	//2003-08-20
				//MUTEOFF;
				//AVDecoderWakeup();
				
				#ifdef USE_UART
				DBGputs("TO 60Hz");
				#endif
			}
			else
			{
				Video50HzTimer=0;
				if(Video60HzTimer==0xFE) Video60HzTimer=5;//One-Time!!
			}
		}

		if( (temp&0x80)&&(CurrentFunction==PipRnC_mode||CurrentFunction==PipRnS_mode) )	{Mute_SoundOff;}//2004-06-29
		else if( !(temp&0x80)&&(!SoundMuteOnFlag)
						&&(PowerOnsequence>=GeneralStatus)
						&&(CurrentFunction==PipRnC_mode||CurrentFunction==PipRnS_mode) )		{Mute_SoundOn;SoundSetVolume();}
		
		if( !(temp&0x80)&&(PowerOnsequence>=GeneralStatus) &&!PipMuteTimer
					&&(CurrentFunction==PipRnC_mode||CurrentFunction==PipRnS_mode||CurrentFunction==PipRnT_mode) )	{	PIPMuteOff; }

				
		//------------------------------------------------------------------------------------------
		//Composite or S-video 50hz or 60Hz , No-signal Check
		//------------------------------------------------------------------------------------------
		if((temp&0x80)&&CurrentFunction!=7&&CurrentFunction!=10)	//TV PIP(NO-Video)인 경우 배제시킨다.
		{
			++NoVideoChattering;
			if(NoVideoChattering<10) return;
			NoVideoChattering=10;
			
			if(ReVideoDecoderSetting) return;//한번만 setting!!!하고 No-Video 채터링 일정시간동안 유지된후.
			
			//COMPOSITE/S-VIDEO no-video에 대한 
			if(xEEPROMBuffer[MainSubInputSource]<16)
			{
				MUTEON;
				PowerOnTimer = 0;
				PowerOnsequence = BeforeNoVideoScalerInit;
				//InvertOff;
				ReVideoDecoderSetting=1;
				return;
			}
			else if(CurrentFunction==4)//Full Television에 대해 싱크안정을 위해(방송미비할때 출력이 불안정하다.)
			{
				WriteScaler(0x2F,BIN_TO_BYTE(0,0,0,1,0,1,0,0));//FrameMode로 전환.
				//WriteScaler(0x2F,BIN_TO_BYTE(0,0,1,0,1,0,0,0));//FrameMode로 전환.
				ReVideoDecoderSetting=1;
				return;		
			}
			
			if(PowerOnsequence<GeneralStatus) return;//어느정도 scaler파워시컨스가 진행된후에 PIP video상태를 읽는다
	
		}
		//------------------------------------------------------------------------------------------
		
		NoVideoChattering = 0;	//Video가 다시 입력되면.
		if(ReVideoDecoderSetting)		//Video가 다시 입력되면.
		{
			if(xEEPROMBuffer[MainSubInputSource]==20||xEEPROMBuffer[MainSubInputSource]==22) //RGB+COMPOSITE(NO)->RGB+COMPOSITE
			{
				xEEPROMBuffer[MainSubInputSource]=20;
				CurrentFunction=PipRnC_mode;
			}
			else if(xEEPROMBuffer[MainSubInputSource]==28||xEEPROMBuffer[MainSubInputSource]==30) //RGB+SVIDEO(NO)->RGB+SVIDEO
			{
				xEEPROMBuffer[MainSubInputSource]=28;
				CurrentFunction=PipRnS_mode;
			}
			else if(xEEPROMBuffer[MainSubInputSource]==36||xEEPROMBuffer[MainSubInputSource]==38) //DVI+COMPOSITE(NO)->DVI+COMPOSITE
			{
				xEEPROMBuffer[MainSubInputSource]=36;
				CurrentFunction=PipDnC_mode;
			}
			else if(xEEPROMBuffer[MainSubInputSource]==44||xEEPROMBuffer[MainSubInputSource]==46) //DVI+SVIDEO(NO)->DVI+SVIDEO
			{
				xEEPROMBuffer[MainSubInputSource]=44;
				CurrentFunction=PipDnS_mode;
			}
			
			#if defined(USE_SCART)	
			else if(xEEPROMBuffer[MainSubInputSource]==72||xEEPROMBuffer[MainSubInputSource]==76) //RGB+SCART(NO)->RGB+SCART
			{
				xEEPROMBuffer[MainSubInputSource]=72;
				CurrentFunction=PipRnSC_mode;
			}
			else if(xEEPROMBuffer[MainSubInputSource]==80||xEEPROMBuffer[MainSubInputSource]==82) //DVI+SCART(NO)->DVI+SCART
			{
				xEEPROMBuffer[MainSubInputSource]=80;
				CurrentFunction=PipDnSC_mode;
			}
			#endif
			
			
			if( CurrentFunction==PipRnC_mode
				||CurrentFunction==PipRnS_mode
				||CurrentFunction==PipDnC_mode
				||CurrentFunction==PipDnS_mode)//PIP일경우.
			{
				ReVideoDecoderSetting = 0;
				PipSubRegisterSet();//PIP reg. set
//2003-10-15				SetScalerPIPOutputCondition(xEEPROMBuffer[MainSubInputSource]);
				
				#ifdef	PipDpmsON	//r+ c/sv/tv 경우
				if(~DpmsPipFlag)	MUTEOFF;
				#else
				MUTEOFF;
				#endif

			}
			else if(CurrentFunction==Tuner_mode) //Television
			{
				#if defined(EMH1A)
				WriteScaler(0x2F,BIN_TO_BYTE(0,0,0,1,1,1,0,0));
				#elif defined(EMH2)
				//WriteScaler(0x2F,BIN_TO_BYTE(0,0,1,1,0,1,0,0));	//2003-05-24
				WriteScaler(0x2F,BIN_TO_BYTE(0,0,0,1,0,1,0,0));//freerun mode
				#else
				WriteScaler(0x2F,BIN_TO_BYTE(0,0,0,1,1,1,0,0));
				#endif				
			}
			else//COMPOSITE or S-VIDEO
			{
				VideoActiveCompleted = 0;
				VideoInitUnit=0;
			}
		}
	}
	ReVideoDecoderSetting = 0;
	//---------------------------------------------------------
	#endif


	
	if(VideoActiveCompleted)
	{
		return;	//decoder initalize하였으면 건너뛴다.
	}

	if(!DecoderInit) 
	{ 		//전원 켜지고 한번만 한다.//그리고..dpms일때도 해야함.
		VideoDecoderInit();	
		DecoderInit=1;
	}	
	AVDecoder_SelectInputPort();	//각각 입력에 대한 채널설정값을 셋팅한다. 
	
	#ifdef USE_TTX
	TTXMode=0;			//TV mode 	
	#endif

	#ifdef	CheckVideoStatus//video status(50Hz, 60Hz) 재설정
		
		#if defined(USE_NTSCtuner)
		NowVideo50Hz=0;
		#elif defined(USE_PALSECAMtuner)
		NowVideo50Hz=1;
		#endif
		
		Video50HzTimer=0;
		Video60HzTimer=0;
		//ChangeToVideo50Hz60HzSystem();//초기진행시 디펄트옵션에 대해 50,60을 결정해놓고 나간다.
	#endif
	
	if(	xEEPROMBuffer[MainSubInputSource]==10||	//COMPOSITE
		xEEPROMBuffer[MainSubInputSource]==14||	//S-Video
		xEEPROMBuffer[MainSubInputSource]==68||	//SCART
		xEEPROMBuffer[MainSubInputSource]==18)	//Tuner
	{
		PowerOnsequence = ScalerstableWait;
		//youngdo		InvertOff;
		PowerOnTimer = 1;
	}
	else
	{
		if(!PipFastChange)
		{
			PowerOnsequence = PowerOnNormalStatus;	//강제로 모드트리거하고 파워시컨스를 전단계로 셋팅한다.
			ModeTrigger;
			//youngdo			InvertOff;
			SyncStableTimer=20;
			PowerOnTimer = 0;
		}
		else{
			PipFastChange = 0;
			//idelay5m(50);//2003-10-17
			SetScalerPIPOutputCondition(xEEPROMBuffer[MainSubInputSource]);//PIP on

			#ifdef	PipDpmsON	//r+ c/sv/tv 경우
			if(~DpmsPipFlag)	MUTEOFF;
			#else
			MUTEOFF;
			#endif

		}
	}
	VideoActiveCompleted = 1;							//set completed!!
}


void SetAV_Brightness(void)
{
	BYTE value;
	
	#ifdef WXGA_Panel
	value = (xEEPROMBuffer[COMPOSITEBRT_buf]*2-100);
	#else
	value = (xEEPROMBuffer[COMPOSITEBRT_buf]*2+28-128);
	#endif
	
	TW990xWrite(TW99_BRIGHT,value);

	#if 0	//-------------------------------------------
	if(xEEPROMBuffer[COMPOSITEBRT_buf]>=50)
		value=xEEPROMBuffer[COMPOSITEBRT_buf]-50;
	else 
		value=127+50-xEEPROMBuffer[COMPOSITEBRT_buf];
		WriteScaler(0x65,value);	//r
		WriteScaler(0x66,value);	//g
		WriteScaler(0x67,value);	//b
	#endif	//-------------------------------------------
}

void SetAV_Contrast(void)
{
	BYTE value;
	#ifdef WXGA_Panel
	//value = (xEEPROMBuffer[COMPOSITECONT]*2-20);	//2003-11-13
	value = (0x28+xEEPROMBuffer[COMPOSITECONT]);	//2004-05-08
	#else
	value = (xEEPROMBuffer[COMPOSITECONT]*2);
	#endif
	TW990xWrite(TW99_CONTRAST,value);	

	#if 0	//---------------
	if(xEEPROMBuffer[COMPOSITECONT]>=50)
		value=(xEEPROMBuffer[COMPOSITECONT]-50)*2.55;
	else 
		value=(100-xEEPROMBuffer[COMPOSITECONT])*2.55;
	WriteScaler(0x62,value);	//r
	WriteScaler(0x63,value);	//g
	WriteScaler(0x64,value);	//b			
	#endif	//---------------
}

void SetAV_Saturation(void)
{
	WORD xdata value;
	#ifdef WXGA_Panel
		//value=(xEEPROMBuffer[AVCOLOR]*2+28)*70;	
		//value/=127;
		value=(xEEPROMBuffer[AVCOLOR]);
	#else
		//value=(xEEPROMBuffer[AVCOLOR]*2+28)*0x7f;	
		value=(xEEPROMBuffer[AVCOLOR]+77);	
	#endif
	
	TW990xWrite(TW99_SAT_U,(BYTE)value);
	
	#ifdef WXGA_Panel
		//value=(xEEPROMBuffer[AVCOLOR]*2+28)*70;	
		//value/=127;
		value=(xEEPROMBuffer[AVCOLOR]);
	#else
		//value=(xEEPROMBuffer[AVCOLOR]*2+28)*0x5a;
		value=(xEEPROMBuffer[AVCOLOR]+40);
	#endif

	TW990xWrite(TW99_SAT_V,(BYTE)value);
	
	
}

void SetAV_Tint(void)
{
	BYTE value;
	value = 100-xEEPROMBuffer[AVTINT]*2;
	TW990xWrite(TW99_HUE,value);
}


void SetAV_Sharpness(void)
{
	xBYTE value;

	value=TW990xRead(TW99_SHARP)&0xf0;
	value+=xEEPROMBuffer[AVSharpness];
	TW990xWrite(TW99_SHARP,value);

}

//TV Auto Setup시에 사용하기 위한 함수이다.	//TV신호를 분석하여 보여줌.
void CheckTVSignal(BYTE Count)
{		xdata BYTE value;
		xdata BYTE i;


	//-----color체크및 신호처리.(Main이 되는 처리이다.)-------
	for (i=0;i<Count;i++)
	{
		value = TW990xRead(0x01);		
		if(value & 0x80 ) {	// no sync
			eTVSyncFlag=0;
		}
		else{	// Decoder h/v Locking.(video detected)
			eTVSyncFlag=1;
			return;
		}			
	}
}

void	SetBlueScrren(BYTE MenuVal)
{

	if(MenuVal) TW990xWrite(TW99_MISC3,0xE6);
	else TW990xWrite(TW99_MISC3,0xE2);



}

// 원래는 novatek칩에서 싱크를 읽어서 입력이 정상적인지를 확인 
//ed-tech에서는필요없�
/*
bit CheckTvSub(void){

		return 1;		
}
*/

			
void	TVColorLoad(void)
{

		switch(xEEPROMBuffer[SmartPicCtr_buf]) {
#ifdef WXGA_Panel
		case	SPCNormal:	//normal
			xEEPROMBuffer[COMPOSITECONT]= 	50;  	// 3.12fix(20)
			xEEPROMBuffer[COMPOSITEBRT_buf]=50;  	// 3.12fix(45)
			xEEPROMBuffer[AVCOLOR]=		50;  	// 3.12fix(50)
			xEEPROMBuffer[AVTINT]= 		50;	// 3.12fix(50)
			xEEPROMBuffer[AVSharpness]= 	3 ; // 3.12fix(04) // 4.7fix(02)
			break;
		case	SPCDynamic:	//Dynamic
			xEEPROMBuffer[COMPOSITECONT]= 	50;	//60%  	// 3.12fix(26)
			xEEPROMBuffer[COMPOSITEBRT_buf]=50;	//50%  	// 3.12fix(45)
			xEEPROMBuffer[AVCOLOR]= 	80;	//60%  	// 3.12fix(60)
			xEEPROMBuffer[AVTINT]= 		50;	//50  	// 3.12fix(50)
			xEEPROMBuffer[AVSharpness]= 	6;	//70%  	// 3.12fix(06)
			break;
		case	SPCCinema:	//Cinema
			xEEPROMBuffer[COMPOSITECONT]= 	50;	//55%  	// 3.12fix(24)
			xEEPROMBuffer[COMPOSITEBRT_buf]=50;	//40%  	// 3.12fix(36)
			xEEPROMBuffer[AVCOLOR]= 	75;	//50%  	// 3.12fix(50)
			xEEPROMBuffer[AVTINT]= 		50;	//50%  	// 3.12fix(50)
			xEEPROMBuffer[AVSharpness]= 	4;	//60%  	// 3.12fix(04)
			break;
		case	SPCUser:	//User	
			xEEPROMBuffer[COMPOSITECONT]= EEPROM_Read(COMPOSITECONT_adr);
			xEEPROMBuffer[COMPOSITEBRT_buf]= EEPROM_Read(COMPOSITEBRT_adr);
			xEEPROMBuffer[AVCOLOR]= EEPROM_Read(COMPOSITECOLOR_adr);
			xEEPROMBuffer[AVTINT]= EEPROM_Read(COMPOSITETINT_adr);	
			xEEPROMBuffer[AVSharpness]= EEPROM_Read(AVSharpness_adr);
			break;
#else
		case	SPCNormal:	//normal
			xEEPROMBuffer[COMPOSITECONT]= 	50;  	// 3.12fix(20)
			xEEPROMBuffer[COMPOSITEBRT_buf]=50;  	// 3.12fix(45)
			xEEPROMBuffer[AVCOLOR]=		50;  	// 3.12fix(50)
			xEEPROMBuffer[AVTINT]= 		50;	// 3.12fix(50)
			xEEPROMBuffer[AVSharpness]= 	3 ; // 3.12fix(04) // 4.7fix(02)
			break;
		case	SPCDynamic:	//Dynamic
			xEEPROMBuffer[COMPOSITECONT]= 	52;	//60%  	// 3.12fix(26)
			xEEPROMBuffer[COMPOSITEBRT_buf]=52;	//50%  	// 3.12fix(45)
			xEEPROMBuffer[AVCOLOR]= 	80;	//60%  	// 3.12fix(60)
			xEEPROMBuffer[AVTINT]= 		50;	//50  	// 3.12fix(50)
			xEEPROMBuffer[AVSharpness]= 	6;	//70%  	// 3.12fix(06)
			break;
		case	SPCCinema:	//Cinema
			xEEPROMBuffer[COMPOSITECONT]= 	52;	//55%  	// 3.12fix(24)
			xEEPROMBuffer[COMPOSITEBRT_buf]=52;	//40%  	// 3.12fix(36)
			xEEPROMBuffer[AVCOLOR]= 	75;	//50%  	// 3.12fix(50)
			xEEPROMBuffer[AVTINT]= 		50;	//50%  	// 3.12fix(50)
			xEEPROMBuffer[AVSharpness]= 	4;	//60%  	// 3.12fix(04)
			break;
		case	SPCUser:	//User	
			xEEPROMBuffer[COMPOSITECONT]= EEPROM_Read(COMPOSITECONT_adr);
			xEEPROMBuffer[COMPOSITEBRT_buf]= EEPROM_Read(COMPOSITEBRT_adr);
			xEEPROMBuffer[AVCOLOR]= EEPROM_Read(COMPOSITECOLOR_adr);
			xEEPROMBuffer[AVTINT]= EEPROM_Read(COMPOSITETINT_adr);	
			xEEPROMBuffer[AVSharpness]= EEPROM_Read(AVSharpness_adr);
			break;
#endif
	}
}


void TVColorSet(void)
{
	TVColorLoad();
	SetAV_Brightness();
	SetAV_Contrast();
	SetAV_Saturation();
	SetAV_Tint();
	SetAV_Sharpness();
}

void SaveCurrentColorToUser()
{
	xEEPROMBuffer[SmartPicCtr_buf]=SPCUser;
	EepromSetQue(COMPOSITECONT_adr,xEEPROMBuffer[COMPOSITECONT]);
	EepromSetQue(COMPOSITEBRT_adr,xEEPROMBuffer[COMPOSITEBRT_buf]);
	EepromSetQue(COMPOSITECOLOR_adr,xEEPROMBuffer[AVCOLOR]);
	EepromSetQue(COMPOSITETINT_adr,xEEPROMBuffer[AVTINT]);
	EepromSetQue(AVSharpness_adr,xEEPROMBuffer[AVSharpness]);	
	EepromSetQue(SmartPicCtr_adr,SPCUser);				
}


#endif
