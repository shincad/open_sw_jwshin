/****************************************************************
Filename  	: Extern .h

Function	: YOUNG DO 2003.5.13

*****************************************************************/
#ifndef _EXTERNN_H
#define _EXTERNN_H


extern bit	TimerBit;				//Timer Loop flag
extern bit 	LoopEnd ;

extern BYTE mPtrDDC2;				// DDC Counter 2004/06/01 +jwshin
//Keychattering 관련
extern idata WORD	KeyTimeBuffer0;			//KEY chattering 2byte data
extern idata WORD	KeyTimeBuffer1 ;			//KEY chattering 2byte data
extern idata BYTE	KEY_valueDetect0 ;			//Temperary key value
extern idata BYTE	KEY_valueDetect1 ;			//Temperary key value
extern BYTE	KEY_value ;				//The last key value

extern	bit	RepeatCodeWait;
//extern idata BYTE	OldKeyValue1;			//Temperary key value
//extern idata BYTE	KeyChatterinfCNT1;	//KEY chattering count


//Power 관련
extern WORD	PowerOnTimer;				//power on하면서 필요한 타이머값을 갖는 ram
extern BYTE	PowerOffTimer;				//power off하면서 필요한 타이머값을 갖는 ram
extern BYTE	PowerOnsequence ;			//power on sequence ram, default 4
extern BYTE	PowerOffsequence ;			//power off sequence ram,default 4
#if	defined(USE_UART)
extern	xBYTE	oldPowerOnsequence;
extern  xBYTE	oldPowerOffsequence;	
#endif


extern bit		YouGoingInitialize;
extern bit		PowerONF ;			// Power on/off Flag	//2003-04-17
extern DWORD	SleepTimer;				//2003-07-31// sleep기능을 위한 타이머값을 갖는 램.

//Register 관련
extern BYTE	EepromBufferQue ;			//EEPROM
extern BYTE	EepromQuepointer ;

#if	defined(MCU_MTV230)
extern 	BYTE xdata	xRAM[MaxBufferSize][2]		;//0x800~0x8ff, MaxBufferSize=128
extern 	WORD xdata	xEEPROM_addr[]	;//0x900~0x97f, 128
extern 	BYTE xdata	xEEPROM_data[]	;//0x980~0x9bf, 64
extern 	BYTE xdata	xEEPROMBuffer[]	;//0x9c0~0x9ff, 64

	#if defined (MicomXFRbackup) && defined(Mtv230OSDbackup)
extern xdata BYTE xMicomBuffer[57];
	#elif defined(MicomXFRbackup)
extern xdata BYTE xMicomBuffer[256];
#endif

#endif   

extern idata BYTE	BUFFER[4];			//Debug용 버퍼.
extern idata BYTE	BUFFER_count;				//Debug용 쓰기 카운터


extern BYTE	ReadAdr ;				//Debug용 읽기 어드레스

//Frequency 관련
extern WORD	NowHfreq ;
extern WORD	NowVfreq ;
extern WORD	BeforeHfreq ;
extern WORD	BeforeVfreq ;
extern bit		NoExistHfreq ;
extern bit		NoExistVfreq ;
extern WORD idata	NoHSYNC_chattering ;
extern WORD idata 	NoVSYNC_chattering ;
extern WORD	SYNC_chattering ;
extern bit		SCDT_LOWBackup;
extern bit		SCDT_HIGHBackup;

//Mode 관련
extern bit		YouHaveToInitMode;
extern BYTE	CurrentMode ;
extern	bit	DosmodeFlag;	//2003-08-26	// (0:640*400, 1:720*400)
extern	bit	BurningFlag;
#ifdef Wide4_3Aspect
extern	bit AspectFlag;
#endif

#if defined(INT_EXTOSD)		//2003-07-02 7:28오후
extern 	WORD	idata NowHactive ;
extern	WORD	idata NowVactive;
extern	WORD	idata NowHtotal;
#else
extern 	WORD	NowHactive ;
extern	WORD	NowVactive;
extern	WORD	NowHtotal;
#endif

extern xBYTE	HorizontalValue;
extern xBYTE	VerticalValue;
extern BYTE	idata	ClockValue;
extern BYTE	idata	PhaseValue;
//BYTE	idata	SharpValue;//2003-04-28
//BYTE	idata	WhiteBlcValue;//2003-04-28
extern DWORD idata NowVideoCLK;
extern DWORD idata	NowAdcCLK;
extern DWORD idata	NowScalerDCLK;
extern DWORD idata	NowScalerMCLK;
extern BYTE	SyncStableTimer;

//Eeprom 관련
//extern BYTE	EepromAdr ;
//extern bit		I2cReadError;
extern	BYTE	idata	BackupInputStatus;	//2003-08-26

//OSD 관련
extern BYTE	OSDstatus ;		//OSD flow
extern BYTE	MENUstatus ;		//Menu flow
//extern BYTE	OSDcusorPosition;
extern BYTE  	OsdMode;			//2003-04-21
extern bit		NowTopOsdOn ;
//extern bit		NowVolumOsdOn ;
extern WORD	OSDofftimer ;
//extern BYTE	GetValue;
//extern BYTE	OSDValue;
extern BYTE	xdata CalBuffer[10];
extern BYTE	OSDWindows;
extern BYTE	OSDcharacters;
//extern bit		OSDSelKeyin;
extern bit	HighOSDArea;
//extern bit	OsdMenuOnFlag;
extern idata	BYTE	MenuMinVal;
extern idata	BYTE	MenuMaxVal;
extern idata	BYTE	MenuVal;
extern idata	BYTE	SubMenuVal;
extern bit	TransparencyOnfFlag;

extern bit	BarFlag;

//AutoTune 관련
extern WORD	idata RedL_Edge ;//RGB Legt_Edge
extern WORD	idata GrnL_Edge ;
extern WORD	idata BluL_Edge ;
extern WORD	idata RedR_Edge ;//RGB Right_Edge
extern WORD	idata GrnR_Edge ;
extern WORD	idata BluR_Edge ;
extern WORD	idata RedT_Edge ;//RGB Top_Edge
extern WORD	idata GrnT_Edge ;
extern WORD	idata BluT_Edge ;
extern WORD	xdata RedB_Edge ;//RGB Bottom_Edge
extern WORD	xdata GrnB_Edge ;
extern WORD	xdata BluB_Edge ;
extern xBYTE	AutoColorSet ;
extern bit		AutoFlag ;


#if defined(INT_EXTOSD)		//2003-07-02 7:37오후
extern WORD	idata	ADCPLL;
#else
extern WORD	ADCPLL;
#endif




extern xBYTE	ADCPHASE;

extern bit		AutoFirst ;
extern xBYTE	AutoProcess ;
extern bit	PhaseStableSet;
extern bit	ClockCompleted;
extern bit	PhaseCompleted;



//Video 관련
extern bit VideoInitUnit ;
extern bit	VideoActiveCompleted ;
extern bit	PipFastChange ;
extern BYTE xdata SoundMuteTvTimer;

#ifdef	CheckVideoStatus
extern 	bit		NowVideo50Hz;
#endif

//TV 관련
extern bit		YouHaveToInitTVchannel;
extern bit		AutoChannelTune;
extern bit		ChannelAdd_Del;
extern BYTE	TunerProcessing;
extern BYTE	xdata Backchannel;
extern BYTE	xdata Frontchannel;
extern BYTE	ChannelScanPointer;
extern WORD	idata RecmoconTVchannel;	
extern bit		UpDownChannel;
extern bit		UpDownChannel2;
extern bit		AddDelFlag;
extern bit		NowAutoChannelSearching;
extern bit		TtxFlag;
extern bit		BscrFlag;
extern bit		WideModeFlag;
extern bit		AntenaFlag;
extern xdata BYTE	TotalEeprom;

//System관련
extern BYTE	CurrentFunction;
//PIP 관련(0:on상태혹은가능, 1:off)
extern bit		PipOnOffFlag;
extern bit		PipAspectFlag;
extern BYTE	idata	DisplayAspectRatioNum;
extern xBYTE	PipBlendNum;
extern bit		PipHposUpdownFlag;
extern bit		PipVposUpdownFlag;
extern bit		PipZoomUpdownFlag;
//0:large, 1:small
extern bit		PipSmallLargeFlag;
extern bit		DpmsPipFlag;
extern bit		DpmsFlag;
extern BYTE	idata	PipInputSource;       
extern BYTE	xdata	PipSizeNum;
extern bit		FactoryDftFlag ;

extern	xBYTE	PipMuteTimer;

extern	bit		KeyContinueFlag;
//remocon관련
#ifdef USE_remocon
extern BYTE	xdata RepeatCodeCount;
extern BYTE	RemoteLongTimer;
extern BYTE	RemoteShortTimer;
extern DWORD xdata RemoteValue;
extern BYTE	RemoteQue;
extern bit		RepeatCodeBit;
extern WORD 	RemoconTenKeyTimer; 
extern BYTE	idata ReceiveRemoconCount;
#endif
extern bit	Remote1keyFlag;

extern bit 		SoundMuteOnFlag;

#ifdef	DVI_EDIDWrite
extern bit	YouHaveToInitDviEDID;
extern BYTE idata MemoryCount;
#endif

//BTC   TV 관련 
extern bit ATFEnable;
extern bit IRMuteFlag;
extern bit eTVSyncFlag;
extern bit NoTunerFlag;

#ifdef USE_TTX
extern BYTE xdata TTXMode;
extern bit TTXInit;
#endif

extern bit DecoderInit;

extern BYTE xdata CHANNEL_LIMIT;
extern BYTE xdata CHANNEL_MAX;
extern BYTE xdata CHANNEL_MIN;
extern BYTE xdata IRDigitValue;
extern BYTE xdata TunerProcessTimer;
//extern BYTE xdata ColorSystem;
extern WORD xdata OLDDivider;
extern BYTE DelayTimer;
//extern BYTE xdata DelayTimerX;
extern BYTE xdata SearchChannel_Total;
extern BYTE xdata SearchChannel_Count;
extern BYTE xdata ProgNo;

extern BYTE 	idata MenuNum;
extern BYTE	idata TvMenuNum;
extern BYTE	idata OsdGrade;
extern BYTE	idata PipHPositionNum;

extern idata	unsigned int PageNum;
extern idata	BYTE	ChEdit_CursorNum;
extern idata	BYTE	ChEdit_CharNum;

#ifdef TempOsdMenu
extern idata	BYTE	TempOsdNum;
#endif

//CCD관련
extern	idata	bit CcdCaptionFlag;
extern idata	bit CcdModeFlag;
extern idata	bit CcdChannelFlag;
extern idata	bit CcdFieldFlag;
extern idata	bit CcdDisplayFlag;

extern bit		SkipFlag;
extern bit		AutoToggle;
extern bit		SubWindowMsgFlag;
extern BYTE	idata	PipVPositionNum;
extern bit 	AFTenable;
extern	bit	NotSearchCHflag;
extern	xBYTE	SearchCNT;
extern BYTE xdata AutoFinePointer;
extern BYTE 	xdata SProcessor ;
extern BYTE 	xdata SoundProcessTimer;
extern BYTE 	xdata SoundProcessStatus;

extern xBYTE	KeyStepTimer;
extern	xBYTE	KeyActionTimer;
extern	bit ChdotDisplayFlag;

// BTC Remocon 관련
extern unsigned char RemDataTemp;	// smpark 20030805
extern bit bRemStart;					// smpark 20030805
extern unsigned char RemVolume;					// smpark 20030805

extern BYTE	xdata KEY_valueBackup0;
extern BYTE	xdata KEY_valueBackup1;
extern	xBYTE	SoundMode;			// smpark 20030811
//extern	xBYTE	SoundModeCnt;		// smpark 20030811
extern	xBYTE PreSoundMode;	// smpark 20030811

//extern 	xdata WORD OldDetectSound;

extern WORD xdata	SoundTimer;	// smpark 20030806
extern BYTE	xdata SingleCH;		// smpark  20030818
extern	bit SingleCHflag;
extern	bit	RecallFlag;

extern unsigned int  	TenMin;		//youngdo 2003.8.16
extern bit 			SetMin;		//youngdo 2003.8.16

extern BYTE  MTS_Stereo;			// smpark 20030818
extern BYTE  MTS_Bilingual; 		// smpark 20030818

//extern BYTE 	PreOSDstatus;		// smpark 20030818

extern BYTE OutputMode;			//smpark 20030820
//extern BYTE xdata LangSelect;			//smpark 20030821
extern bit RemoconDigit;			//smpark 20030827
extern BYTE xdata FineTuneValue_max;	//youngdo 2003.8.25

//*****************************************
//  code data
//******************************************
extern	code 	ModeTable	ModeList[];
extern	code BYTE	EEPROM_DftVal[];
extern	code PipHVwidth	PipHVawList[];	//2003-07-18

#endif

