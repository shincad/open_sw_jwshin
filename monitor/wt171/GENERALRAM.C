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
#include "eepromadr.h"

#if	defined(AtecBoard_Option)||defined(CadinalBoard_Option)||defined(AtriumBoard_Option)||defined(EdtechEmotionBoard_Option)\
	||defined(EdtechTotalDemoBoard_Option)||defined(EdtechVpc3230DemoBoard_Option)||defined(BtcBoard_Option)
#include	"autotunevalue.h"
#include	"btc_osdmenu.h"

bit	TimerBit=0;				//Timer Loop flag
bit 	LoopEnd =1;
bit	RepeatCodeWait=0;	//2003-08-09 5:06오후

//Keychattering 관련
idata WORD	KeyTimeBuffer0 =0;			//KEY chattering 2byte data
idata WORD	KeyTimeBuffer1 =0;			//KEY chattering 2byte data
idata BYTE	KEY_valueDetect0 =0;			//Temperary key value
idata BYTE	KEY_valueDetect1 =0;			//Temperary key value
BYTE	KEY_value =0;				//The last key value

//idata BYTE	OldKeyValue1 =0;			//Temperary key value
//idata BYTE	KeyChatterinfCNT1=0;	//KEY chattering count


//Power 관련
WORD	PowerOnTimer=0;				//power on하면서 필요한 타이머값을 갖는 ram
BYTE	PowerOffTimer=0;			//power off하면서 필요한 타이머값을 갖는 ram
BYTE	PowerOnsequence =4;			//power on sequence ram, default 4
BYTE	PowerOffsequence =4;			//power off sequence ram,default 4
#if	defined(USE_UART)
xBYTE	oldPowerOnsequence =4;
xBYTE	oldPowerOffsequence =4;	
#endif

bit		YouGoingInitialize=0;
bit		PowerONF = 0;			// Power on/off Flag	//2003-04-17
DWORD	SleepTimer=0;				//2003-07-31// sleep기능을 위한 타이머값을 갖는 램.

//Register 관련
BYTE	EepromBufferQue = 0;			//EEPROM
BYTE	EepromQuepointer = 0;



#if	defined(MCU_MTV230)
xdata	BYTE	xRAM[MaxBufferSize][2]		_at_	0x0800;//0x800~0x8ff, MaxBufferSize=128*[2] ->256
//xdata	WORD	xEEPROM_addr[MaxEepromBuffer]	_at_	0x0900;//0x900~0x97f, 128
//xdata	BYTE	xEEPROM_data[MaxEepromBuffer]	_at_	0x0980;//0x980~0x9bf, 64
xdata	WORD	xEEPROM_addr[MaxEepromBuffer-20]	_at_	0x0900;//0x900~0x97f, 128
xdata	BYTE	xEEPROM_data[MaxEepromBuffer-20]	_at_	0x0980;//0x980~0x9bf, 64
xdata	BYTE	xEEPROMBuffer[MaxEepromBuffer]	_at_	0x09C0;//0x9c0~0x9ff, 64
 
	#if defined (MicomXFRbackup) && defined(Mtv230OSDbackup)
xdata	BYTE	xMicomBuffer[57]		_at_	0x0A00;//0xa00~0xaff
	#elif defined(MicomXFRbackup)
xdata	BYTE	xMicomBuffer[256]		_at_	0x0A00;//0xa00~0xa39
	#endif


#elif	defined(MCU_MTV412)
xdata	BYTE	xRAM[MaxBufferSize][2]		_at_	0x0800;
xdata	WORD	xEEPROM_addr[MaxEepromBuffer]	_at_	0x0900;
xdata	BYTE	xEEPROM_data[MaxEepromBuffer]	_at_	0x0980;
xdata	BYTE	xEEPROMBuffer[MaxEepromBuffer]	_at_	0x09C0;

#ifdef MicomXFRbackup
xdata	BYTE	xMicomBuffer[256]		_at_	0x0E00;//0xa00~0xaff
#endif

#elif	defined(MCU_NT68F63)
xdata	BYTE	xRAM[MaxBufferSize][2]		_at_	0xF480;//MaxBufferSize=128
xdata	WORD	xEEPROM_adr[MaxEepromBuffer]	_at_	??;
xdata	BYTE	xEEPROM_adr[MaxEepromBuffer]	_at_	??;
xdata	BYTE	xEEPROMBuffer[MaxEepromBuffer]	_at_	??;
#endif

BYTE	idata BUFFER[4] = {0,};			//Debug용 버퍼.
BYTE	idata BUFFER_count=0;				//Debug용 쓰기 카운터
//BYTE	idata ReadCount = 0;				//Debug용 읽기 카운터
BYTE	ReadAdr = 0;				//Debug용 읽기 어드레스
//BYTE	xPORTram = 0;				//xPORT5 보완용

//Frequency 관련
WORD	NowHfreq =0;
WORD	NowVfreq =0;
WORD	BeforeHfreq =0;
WORD	BeforeVfreq =0;
bit		NoExistHfreq =0;
bit		NoExistVfreq =0;
WORD idata	NoHSYNC_chattering =0;
WORD idata 	NoVSYNC_chattering =0;
WORD	SYNC_chattering =0;
bit		SCDT_LOWBackup=0;
bit		SCDT_HIGHBackup=0;

//Mode 관련
bit		YouHaveToInitMode;
BYTE	CurrentMode =0;
bit	DosmodeFlag=1;	//2003-08-26	// (0:640*400, 1:720*400)
bit	BurningFlag=0;	//2003-09-01
#ifdef Wide4_3Aspect
bit		AspectFlag=0;	//2003-12-30 (0: wide,	1: 4:3)
#endif

#if defined(INT_EXTOSD)		//2003-07-02 7:28오후
WORD	idata NowHactive = 0;
WORD	idata NowVactive = 0;
WORD	idata NowHtotal;
#else
WORD	NowHactive = 0;
WORD	NowVactive = 0;
WORD	NowHtotal;
#endif


xBYTE	HorizontalValue;
xBYTE	VerticalValue;
BYTE	idata	ClockValue;
BYTE	idata	PhaseValue;
//BYTE	idata	SharpValue;//2003-04-28
//BYTE	idata	WhiteBlcValue;//2003-04-28
DWORD idata NowVideoCLK;
DWORD idata	NowAdcCLK;
DWORD idata	NowScalerDCLK;
DWORD idata	NowScalerMCLK;
BYTE	SyncStableTimer=0;

//Eeprom 관련
//BYTE	EepromAdr =0;		//2003-06-28 removed for memory save
//bit		I2cReadError=0;	//2003-06-28 removed for memory save
BYTE	idata	BackupInputStatus=2;	//2003-08-26

//OSD 관련
BYTE	OSDstatus = 0;		//OSD flow
//BYTE 	PreOSDstatus=0;	// smpark 20030818 : 이전 상태의 OSDstatus 저장 
BYTE	MENUstatus = 0;		//Menu flow
//BYTE	OSDcusorPosition;
BYTE	OsdMode;			//2003-04-21
bit		NowTopOsdOn = 0;
//bit		NowVolumOsdOn =0;
WORD	OSDofftimer = 0;
//BYTE	GetValue;	//2003-06-28 removed for memory save
//BYTE	OSDValue;	//2003-06-28 removed for memory save
BYTE	xdata CalBuffer[10] =0;
BYTE	OSDWindows;
BYTE	OSDcharacters;
//bit		OSDSelKeyin;
bit	HighOSDArea=0;	// smpark 20030821 //vlauue init.(=0)
//bit	OsdMenuOnFlag=0;	//2003-10-01 //osd menu가 계속 on되는지 위해

idata	BYTE	MenuMinVal;
idata	BYTE	MenuMaxVal;
idata	BYTE	MenuVal;
idata	BYTE	SubMenuVal;	//2003-11-28
bit		TransparencyOnfFlag=0;

bit		BarFlag = 0;
bit		SubWindowMsgFlag=0;

idata	unsigned int PageNum=0;
idata	BYTE	ChEdit_CursorNum=0;
idata	BYTE	ChEdit_CharNum=0;

#ifdef TempOsdMenu
idata	BYTE	TempOsdNum=0;		//2003-10-29	//임시 osd 메뉴 선택를 위해.
#endif

//CCD 관련	//2003-11-27
idata	bit CcdCaptionFlag=0;
idata	bit CcdModeFlag=0;
idata	bit CcdChannelFlag=0;
idata	bit CcdFieldFlag=0;
idata	bit CcdDisplayFlag=0;


//AutoTune 관련
WORD	idata RedL_Edge = 0;//RGB Legt_Edge
WORD	idata GrnL_Edge = 0;
WORD	idata BluL_Edge = 0;
WORD	idata RedR_Edge = 0;//RGB Right_Edge
WORD	idata GrnR_Edge = 0;
WORD	idata BluR_Edge = 0;
WORD	idata RedT_Edge = 0;//RGB Top_Edge
WORD	idata GrnT_Edge = 0;
WORD	idata BluT_Edge = 0;
WORD	xdata RedB_Edge = 0;//RGB Bottom_Edge
WORD	xdata GrnB_Edge = 0;
WORD	xdata BluB_Edge = 0;
xBYTE	AutoColorSet = 0;
bit		AutoFlag = 0;

#if defined(INT_EXTOSD)		//2003-07-02 7:37오후
WORD	idata ADCPLL=0;
#else
WORD	ADCPLL=0;
#endif

xBYTE	ADCPHASE=0;
//BYTE	AutoTimer;	//2003-06-28 removed for memory save
bit		AutoFirst = 0;
xBYTE	AutoProcess = 0;
bit	PhaseStableSet=0;
bit	ClockCompleted=0;
bit	PhaseCompleted=0;
bit	AutoToggle=0;

bit	SkipFlag=0;
bit	EditWindowFlag=0;

/*
#ifdef	OldPhaseSearch
WORD	xdata SumPhase[32]={0,};
#else
DWORD	xdata SumPhase[32]={0,};
//WORD	xdata SumPhase[32]={0,};
#endif
*/
//Video 관련
bit  VideoInitUnit = 0;
bit	VideoActiveCompleted = 0;
bit	PipFastChange = 0;
BYTE xdata SoundMuteTvTimer;

#ifdef	CheckVideoStatus
	bit		NowVideo50Hz=0;
#endif

//TV 관련
bit		YouHaveToInitTVchannel=0;
bit		AutoChannelTune;
bit		ChannelAdd_Del;
BYTE	TunerProcessing=0;
BYTE	xdata Backchannel=0;
BYTE	xdata Frontchannel=0;
BYTE	ChannelScanPointer=0;
WORD	idata RecmoconTVchannel;	
bit		UpDownChannel=0;
bit		UpDownChannel2=0;
bit		AddDelFlag=0;
bit		NowAutoChannelSearching=0;
bit		AntenaFlag=0;		// [0:cable, 1:air]
bit 		AFTenable=1;
bit	NotSearchCHflag=0;	//0:search, 1:not search
xBYTE	SearchCNT=0;

BYTE	idata	DisplayAspectRatioNum =0x02;	//2003-08-02 // [high:pip, low:tv] (0->4:3, 1->16:9, 2->normal)

//System관련
BYTE	CurrentFunction=0;
//PIP 관련
bit		PipOnOffFlag=0;
bit		PipAspectFlag=0;	//2003-07-31//(0->4:3,1->16:9)
xBYTE		PipBlendNum=0;		//2003-08-19 (0:off)
bit		PipHposUpdownFlag=1;	//2003-08-29 (1: up, 0:down)
bit		PipVposUpdownFlag=1;	//2003-08-29 (1: up, 0:down)
bit		PipZoomUpdownFlag=1;	//2003-08-29 (1: up, 0:down)
//#ifndef BtcBoard_Option
//0:large, 1:small
bit		PipSmallLargeFlag=0;
bit		DpmsPipFlag=0;	//2003-10-21
bit		DpmsFlag=0;	//2004-05-29
//#endif
BYTE	idata	PipInputSource=0;       
BYTE	xdata	PipSizeNum=0;
#if 1
BYTE	idata	PipHPositionNum=1;
BYTE	idata	PipVPositionNum=1;
#else	//TEEST
WORD	idata	PipHPositionNum=0;
WORD	idata	PipVPositionNum=0;
#endif
bit		FactoryDftFlag = 0;

xBYTE	PipMuteTimer=0;

bit		KeyContinueFlag=0;

//remocon관련
#ifdef USE_remocon
BYTE	xdata RepeatCodeCount;
BYTE	RemoteLongTimer;
BYTE	RemoteShortTimer;
DWORD	xdata	RemoteValue;
BYTE	RemoteQue;
bit		RepeatCodeBit;
WORD 	RemoconTenKeyTimer; 
BYTE	idata ReceiveRemoconCount;
//WORD 	SaveRemCode;		// smpark 20030806
bit		ThreeDigit=0;			// smpark 20030807
bit 		RemAddBtn=0;
BYTE	xdata SingleCH=0;		// smpark  20030818
bit SingleCHflag=0;
bit	RecallFlag=0;		//2003-10-06
#endif

bit 	Remote1keyFlag=0;

// Smart Sound Control
xBYTE	SoundMode;			// smpark 20030811
//xBYTE	SoundModeCnt;		// smpark 20030811
xBYTE PreSoundMode;	// smpark 20030811

//xdata WORD OldDetectSound=0;

// MTS	
BYTE  MTS_Stereo;			// smpark 20030818
BYTE  MTS_Bilingual; 			// smpark 20030818
// mode change

// language 설정
//BYTE xdata LangSelect=0;		// 기본 설정 : 영어


WORD xdata	SoundTimer=0;	// smpark 20030806
//WORD xdata	RemBufferCol;		// smpark 20030806
bit 		SoundMuteOnFlag;
bit 	RemoconDigit=0;	//smpark 20030827


#ifdef	DVI_EDIDWrite
bit	YouHaveToInitDviEDID=0;
BYTE idata MemoryCount=0;
#endif


//BTC   TV 관련 
bit ATFEnable;
bit IRMuteFlag;
bit eTVSyncFlag;
bit NoTunerFlag;
#ifdef USE_TTX
BYTE xdata TTXMode;
bit TTXInit=0;
#endif
bit DecoderInit=0;

BYTE xdata CHANNEL_LIMIT;
BYTE xdata CHANNEL_MAX;
BYTE xdata CHANNEL_MIN;
BYTE xdata IRDigitValue;
BYTE xdata TunerProcessTimer;
//BYTE xdata OSDStringBuff[24];
//BYTE xdata ColorSystem;
WORD xdata OLDDivider;
BYTE DelayTimer;
//BYTE xdata DelayTimerX;
BYTE xdata SearchChannel_Total;
BYTE xdata SearchChannel_Count;
BYTE xdata ProgNo=0;
BYTE xdata AutoFinePointer;

BYTE 	idata MenuNum=0;
BYTE	idata TvMenuNum=0;
BYTE	idata OsdGrade=0;
BYTE 	xdata SProcessor =0;
BYTE 	xdata SoundProcessTimer=0;
BYTE 	xdata SoundProcessStatus=0;
BYTE	xdata KEY_valueBackup0=0;
BYTE	xdata KEY_valueBackup1=0;
BYTE 	xdata FineTuneValue_max=TvFineTuneValue_max;//youngdo 2003.8.25

xBYTE	KeyStepTimer=0;
xBYTE	KeyActionTimer=20;
bit		ChdotDisplayFlag=0;

unsigned int  	TenMin=0;			//youngdo 2003.8.16
bit 			SetMin=0;			//youngdo 2003.8.16

void RamClear(void)
{
	NowHfreq =0;
	NowVfreq =0;
	BeforeHfreq =0;
	BeforeVfreq =0;
	NoExistHfreq =0;
	NoExistVfreq =0;
	NoHSYNC_chattering =0;
	NoVSYNC_chattering =0;
	SYNC_chattering =0;	
	CurrentMode =0;	
	VideoInitUnit=0;
	VideoActiveCompleted = 0;			//set completed!!
	NowAutoChannelSearching=0;
	AutoFlag=0;
	AutoColorSet = 0;
	AutoFlag = 0;
	ADCPHASE=0;
	AutoFirst = 0;
	AutoChannelTune=0;
	SoundMuteOnFlag =0;
#ifdef USE_TTX
	TTXMode=0;
	TTXInit=0;
#endif
	DecoderInit=0;
	AFTenable=1;
	SProcessor =0;	
	UpDownChannel=0;	
	SoundProcessTimer=0;	
	SoundProcessStatus=0;
	KEY_valueBackup0=0;
	KEY_valueBackup1=0;	

}

void ArrangeFunctionTable(void)
{
	if	(0<=xEEPROMBuffer[MainSubInputSource]&&xEEPROMBuffer[MainSubInputSource]<=3) 	  	CurrentFunction=Rgb_mode;		//0;//RGB
	else if	(4<=xEEPROMBuffer[MainSubInputSource]&&xEEPROMBuffer[MainSubInputSource]<=7)  CurrentFunction=Dvi_mode;		//1;//DVI
	else if	(8<=xEEPROMBuffer[MainSubInputSource]&&xEEPROMBuffer[MainSubInputSource]<=11) CurrentFunction=Composite_mode;	//2;//COMPOSITE
	else if	(12<=xEEPROMBuffer[MainSubInputSource]&&xEEPROMBuffer[MainSubInputSource]<=15)CurrentFunction=Svideo_mode;	//3;//S-VIDEO
	else if	(16<=xEEPROMBuffer[MainSubInputSource]&&xEEPROMBuffer[MainSubInputSource]<=19)CurrentFunction=Tuner_mode;	//4;//TUNER
	else if	(20<=xEEPROMBuffer[MainSubInputSource]&&xEEPROMBuffer[MainSubInputSource]<=27)CurrentFunction=PipRnC_mode;	//5;//PIP R+C
	else if	(28<=xEEPROMBuffer[MainSubInputSource]&&xEEPROMBuffer[MainSubInputSource]<=35)CurrentFunction=PipRnS_mode;	//6;//PIP R+S
	else if	(52<=xEEPROMBuffer[MainSubInputSource]&&xEEPROMBuffer[MainSubInputSource]<=59)CurrentFunction=PipRnT_mode;	//7;//PIP R+T
	else if	(36<=xEEPROMBuffer[MainSubInputSource]&&xEEPROMBuffer[MainSubInputSource]<=43)CurrentFunction=PipDnC_mode;	//8;//PIP D+C
	else if	(44<=xEEPROMBuffer[MainSubInputSource]&&xEEPROMBuffer[MainSubInputSource]<=51)CurrentFunction=PipDnS_mode;	//9;//PIP D+S
	else if	(60<=xEEPROMBuffer[MainSubInputSource]&&xEEPROMBuffer[MainSubInputSource]<=67)CurrentFunction=PipDnT_mode;	//10;//PIP D+T
	#if defined(USE_SCART)	                                                                              
	else if	(68<=xEEPROMBuffer[MainSubInputSource]&&xEEPROMBuffer[MainSubInputSource]<=71)CurrentFunction=Scart_mode;	//11;//SCART
	else if	(72<=xEEPROMBuffer[MainSubInputSource]&&xEEPROMBuffer[MainSubInputSource]<=79)CurrentFunction=PipRnSC_mode;	//12;//PIP R+SC
	else if	(80<=xEEPROMBuffer[MainSubInputSource]&&xEEPROMBuffer[MainSubInputSource]<=87)CurrentFunction=PipDnSC_mode;	//13;//PIP D+SC
	#endif
}
#endif
