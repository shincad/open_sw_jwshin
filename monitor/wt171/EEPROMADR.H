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
#if defined(BtcBoard_Option) 
#define	BaseEEPROM_adr		0x100			//value 저장 메모리 base
#else
#define	BaseEEPROM_adr		0x700			//value 저장 메모리 base
#endif

//*******************************************************************************
//xdata	BYTE	xEEPROMBuffer[MaxEepromBuffer]	_at_	0x09C0;//0x9c0~0x9ff, 64
//*******************************************************************************

//EEPROM address define 
#define	EEPROMVERSION_adr	BaseEEPROM_adr+(0x00)
#define	POWERID_adr			BaseEEPROM_adr+(0x01)
#define	POWERID_buf			0x01
#define	MainSubInputSource_adr	BaseEEPROM_adr+(0x02)	//FrameNotFrameOrDvi
#define	MainSubInputSource	0x02						//FrameNotFrameOrDvi
#define	OSDOFFTIME_adr		BaseEEPROM_adr+(0x03)
#define	OSDOFFTIME_buf		0x03
#define	LANGUAGE_adr		BaseEEPROM_adr+(0x04)	//Language
#define	LANGUAGE_buf		0x04					//Language
#define	ANALOGBRT_adr		BaseEEPROM_adr+(0x05)
#define	ANALOGBRT_buf		0x05
#define	COMPOSITEBRT_adr	BaseEEPROM_adr+(0x06)
#define	COMPOSITEBRT_buf	0x06
#define	ANALOGCONT_adr		BaseEEPROM_adr+(0x07)
#define	ANALOGCONT			0x07
#define	COMPOSITECONT_adr	BaseEEPROM_adr+(0x08)
#define	COMPOSITECONT		0x08
#define	ColorTemp_addr		BaseEEPROM_adr+(0x09)
#define	ColorTemp			0x09
#define	ADCREDGAIN_adr		BaseEEPROM_adr+(0x0a)
#define	ADCREDGAIN_buf		0x0a
#define	ADCGREENGAIN_adr	BaseEEPROM_adr+(0x0b)
#define	ADCGREENGAIN_buf	0x0b
#define	ADCBLUEGAIN_adr		BaseEEPROM_adr+(0x0c)
#define	ADCBLUEGAIN_buf		0x0c
#define	OSDHPOSITION_adr	BaseEEPROM_adr+(0x0d)
#define	OSDHPOSITION_buf	0x0d
#define	OSDVPOSITION_adr	BaseEEPROM_adr+(0x0e)
#define	OSDVPOSITION_buf	0x0e
#define	COMPOSITESHARP_adr	BaseEEPROM_adr+(0x0f)
#define	COMPOSITESHARP_buf	0x0f
#define	COMPOSITECOLOR_adr	BaseEEPROM_adr+(0x10)
#define	AVCOLOR				0x10
#define	COMPOSITETINT_adr	BaseEEPROM_adr+(0x11)
#define	AVTINT				0x11
#define	VOLUME_adr			BaseEEPROM_adr+(0x12)
#define	VOLUME_buf			0x12
//-------------------- pip ---------------------------------------------------------------------------------
#define	PIPPOSITION_adr		BaseEEPROM_adr+(0x13)	// 좌(00/01/02),중(10/11/12),우(20/21/22)
#define	PIPPOSITION			0x13					// [high:H,low:V], (0:top/R,1:mid/M,2:bot/L)
#define	PIPSIZE_adr			BaseEEPROM_adr+(0x14)	// 0x[PipAspect:PipSize]
#define	PIPSIZE_buf			0x14					// low-> (0:L, 1:M, 2:S), high:(0->4:3, 1->16:9)
#define	PIPBLEND_adr		BaseEEPROM_adr+(0x15)
#define	PIPBLEND_buf		0x15
#define	PIPEN_SOURCE_adr	BaseEEPROM_adr+(0x16)	// [PipOnOff:Source]
#define	PIPEN_SOURCE_buf	0x16					// high: pip on/off(1/0), low: source(0:av1,1:av2,2:tv)
//-----------------------------------------------------------------------------------------------------
#define	WideModeFlag_adr	BaseEEPROM_adr+(0x17)
#define	WideModeFlag_buf	0x17

#define	NTSC_AIRTVFine_adr	BaseEEPROM_adr+(0x18)
#define	NTSC_AIRTVFine_buf	0x18

#define SSC_adr				BaseEEPROM_adr+(0x19)		// smpark 20030715
#define SSC					0x19						// smpark 20030715
#define	MTS_adr				BaseEEPROM_adr+(0x1a)		// smpark 20030722
#define MTS					0x1a

//#define	TtxFlag_adr		BaseEEPROM_adr+(0x2E)
//#define	TtxFlag_buf		0x2E
#define	BASS_adr			BaseEEPROM_adr+(0x1b)
#define	BASS				0x1b
#define	TREBLE_adr			BaseEEPROM_adr+(0x1c)
#define	TREBLE				0x1c
#define	LOUDNESS_adr		BaseEEPROM_adr+(0x1d)
#define	LOUDNESS			0x1d


#define	TVMODE_adr			BaseEEPROM_adr+(0x1e)	//TV MODE(NTSC,PAL BG,PAL DK,SECAM BG, SECAM DK).
													//Bit7:Manual Channel's ADD or DEL, BIT6:Auto Channel's STOP or START
#define	TVMODE				0x1e

#define	Sharpness_adr 		BaseEEPROM_adr+(0x1f)
#define	Sharpness_buf 		0x1f
#define	WhiteBlc_adr	 	BaseEEPROM_adr+(0x20)
#define	WhiteBlc_buf	 	0x20
#define	AVSharpness_adr		BaseEEPROM_adr+(0x21)
#define	AVSharpness			0x21
#define	SmartPicCtr_adr	 	BaseEEPROM_adr+(0x22)
#define	SmartPicCtr_buf	 	0x22
#define	Sleep_adr			BaseEEPROM_adr+(0x23)
#define	Sleep_buf			0x23

#if defined(BtcBoard_Option) 
//BTC TV data ***********************************************
#define	CurrentChannel_adr	BaseEEPROM_adr+(0x24)	
#define	CurrentChannel		0x24
#define	Prechannel_adr		BaseEEPROM_adr+(0x25)
#define	PreChannel			0x25
#define	SystemCountry_adr	BaseEEPROM_adr+(0x26)
#define	SystemCountry		0x26
#define	Antena_adr			BaseEEPROM_adr+(0x27)
#define	Antena				0x27
#define	Version_adr			BaseEEPROM_adr+(0x28)
#define	Version				0x28
#define	BscrFlag_adr		BaseEEPROM_adr+(0x29)
#define	BscrFlag_buf		0x29
#define	DisplayAspcet_adr	BaseEEPROM_adr+(0x2a)
#define	DisplayAspcet_buf	0x2a

#define	Dosmode_adr			BaseEEPROM_adr+(0x2b)
#define	Dosmode_buf			0x2b
#define	FactoryReset_adr	BaseEEPROM_adr+(0x2c)
#define	FactoryReset_buf	0x2c

#define	BackupMainSubInputSource_adr	BaseEEPROM_adr+(0x2d)	//FrameNotFrameOrDvi
#define	BackupMainSubInputSource		0x2d			//FrameNotFrameOrDvi

#ifdef TempOsdMenu
#define	TempOsd_adr			BaseEEPROM_adr+(0x2e)	//임시 osd menu
#define	TempOsd_buf			0x2e
#define	TempOsdBlend_adr	BaseEEPROM_adr+(0x2f)	//임시 osd menu
#define	TempOsdBlend_buf	0x2f
#endif


#if defined (Ccd_Vchip)&&(TempOsdMenu)
#define Ccd_adr				BaseEEPROM_adr+(0x30)	//[4:0] [4:display/3:field/2:channel/1:mode/0:caption]
#define Ccd_buf				0x30
#define Vchip_adr			BaseEEPROM_adr+(0x31)	//[1:0] [1:Partental/0:MotionPiture]
#define Vchip_buf			0x31

#ifdef Wide4_3Aspect
#define	Aspect_buf			BaseEEPROM_adr+(0x32)	//[0: Aspect Ratio(PC main display)]
#define	Aspect_adr			0x32
#endif

#elif defined (Ccd_Vchip)&& !defined(TempOsdMenu)
#define Ccd_adr				BaseEEPROM_adr+(0x2e)	//[4:0] [4:display/3:field/2:channel/1:mode/0:caption]
#define Ccd_buf				0x2e
#define Vchip_adr			BaseEEPROM_adr+(0x2f)	//[1:0] [1:Partental/0:MotionPiture]
#define Vchip_buf			0x2f

#ifdef Wide4_3Aspect
#define	Aspect_buf			BaseEEPROM_adr+(0x30)	//[0: Aspect Ratio(PC main display)]
#define	Aspect_adr			0x30
#endif

#elif !defined (Ccd_Vchip)&& defined(TempOsdMenu)
#ifdef Wide4_3Aspect
#define	Aspect_buf			BaseEEPROM_adr+(0x30)	//[0: Aspect Ratio(PC main display)]
#define	Aspect_adr			0x30
#endif

#elif !defined(Ccd_Vchip)&& !defined(TempOsdMenu)
#ifdef Wide4_3Aspect
#define	Aspect_buf			BaseEEPROM_adr+(0x2e)	//[0: Aspect Ratio(PC main display)]
#define	Aspect_adr			0x2e
#endif

#endif


//#define	Dummy2_adr		BaseEEPROM_adr+(0x31)

	

#define	TenTimeCheck_adr		BaseEEPROM_adr+(0x40)
#define	TenTimeCheck1_adr		BaseEEPROM_adr+(0x41)
#define	TenTimeCheck2_adr		BaseEEPROM_adr+(0x42)
#define	TenTimeCheck3_adr		BaseEEPROM_adr+(0x43)
#define	TenTimeCheck4_adr		BaseEEPROM_adr+(0x44)
#define	TenTimeCheck5_adr		BaseEEPROM_adr+(0x45)


#ifndef FrequncyTableType	//+++++++++++++++++++++++
#if defined(USE_NTSCtuner)
#define ep_ChannelStart			0x400	//channel memory to 0x5FF
#define ep_ChannelStartAir		0x400	//channel memory to 0x5FF
#define ep_ChannelStartCatv		0x500	// 1.27

#else
	#ifdef TempMemTest_pal
	#else
#define ep_ProgStart			0x300	//2003.6.9 pal인 경우 프로그램 넘버를 저장하는 것.
//#define ep_ProgEnd				0x363	
#define ep_ProgMemStart			0x400	//channel memory to 0x5FF
	#endif
#endif
#else	//+++++++++++++++++++++++++++++++++++++++++++
#define ep_ChannelStart				0x400
#endif	//+++++++++++++++++++++++++++++++++++++++++





#define NoDefine			0x670	// <-- 추가되는 데이터는 이부분에서 부터 적용하세요.
//*****************************************************************
#endif

#if 0	//
#define	PIPH0POSITION_adr	BaseEEPROM_adr+(0x3D)
#define	PIPH1POSITION_adr	BaseEEPROM_adr+(0x3E)
#define	PIPV0POSITION_adr	BaseEEPROM_adr+(0x3F)
#define	PIPV1POSITION_adr	BaseEEPROM_adr+(0x3F)
#endif

//#define	PIPONOFF_addr		BaseEEPROM_adr+(0x35)

//#define	ColorTemp_addr		BaseEEPROM_adr+(0x35)

#define	ANALOGBRT_min		0x00
#define	ANALOGBRT_max		100	//

#define	ANALOGCONT_min		0x00
#define	ANALOGCONT_max		100	//

#define	ADCREDGAIN_min		0x00
#define	ADCREDGAIN_max		100//70//0x3f
#define ADCREDGAIN_offset	0////2

#define	ADCGREENGAIN_min	ADCREDGAIN_min
#define	ADCGREENGAIN_max	ADCREDGAIN_max

#define	ADCBLUEGAIN_min		ADCREDGAIN_min
#define	ADCBLUEGAIN_max		ADCREDGAIN_max

#define	SAA7114Sharp_min	0x00
#define	SAA7114Sharp_max	0x07  //2003.6.30 YOUNGDO

#define	SAA7114Color_min	0
#define	SAA7114Color_max	100

#define	SAA7114Hue_min		0x00
#define	SAA7114Hue_max		100	////100//30 //test

#define	ClockValue_min		0x00
#define	ClockValue_max		0xff

#define	HorizontalValue_min	0x00
#define	HorizontalValue_max	0xff

#define	VerticalValue_min	0x00
#define	VerticalValue_max	74

#define	PhaseValue_min		0x00
#define	PhaseValue_max		0x1f

#define	SharpValue_min		0x00
#define	SharpValue_max		0x1f

#define	WhiteBlcValue_min	0
#define	WhiteBlcValue_max	0x64//50//0xff//0x1f


#define	OSDPOSITION_min		0x00
#define	OSDPOSITION_max		0x04

#if defined(SXGA_Panel)	//------------------
#define	OSDHpos_min		0x00
#define	OSDHpos_max		0x97
#define	OSDVpos_min		1//0x00
	#ifdef OsdMenuType1
#define	OSDVpos_max		0xbf
	#else	
#define	OSDVpos_max		0xaf//be
	#endif
#elif defined(WXGA_Panel) //-----------------
#define	OSDHpos_min		0x00
//#define	OSDHpos_max		0x92
#define	OSDHpos_max		0x97
#define	OSDVpos_min		1//0x00
	#ifdef OsdMenuType1
#define	OSDVpos_max		0x7f
	#else
#define	OSDVpos_max		0x6f//be
	#endif
#endif	//-----------------------------------

#define	OSDLANGUAGE_min		0x00
#define	OSDLANGUAGE_max		0x04
				
#define	OSDOFFTIME_min		5	//0x03
#define	OSDOFFTIME_max		60	//0x3c

#define	CurrentFunction_min	0x00
#if defined(USE_SCART)
#define	CurrentFunction_max	13
#else
#define	CurrentFunction_max	10
#endif

#define  SOUND_TREBLE_min	0		// smpark 20030715
#define  SOUND_TREBLE_max	100		// smpark 20030715

#define  SOUND_BASS_min		0		// smpark 20030715
#define  SOUND_BASS_max 	100		// smpark 20030715

#define  SOUND_LOUDNESS_min		0		// smpark 20030719
#define  SOUND_LOUDNESS_max 	100		// smpark 20030719



#define	TUNERBRT_min		ANALOGBRT_min
#define	TUNERBRT_max		ANALOGBRT_max

#define	TUNERCONT_min		ANALOGCONT_min
#define	TUNERCONT_max		ANALOGCONT_max

#define	TUNERSHARP_min		SAA7114Sharp_min
#define	TUNERSHARP_max		SAA7114Sharp_max

#define	TUNERCOLOR_min		SAA7114Color_min
#define	TUNERCOLOR_max		SAA7114Color_max

#define	TUNERTINT_min		SAA7114Hue_min
#define	TUNERTINT_max		SAA7114Hue_max

#define	DIGITALBRT_min		ANALOGBRT_min
#define	DIGITALBRT_max		ANALOGBRT_max

#define	DIGITALCONT_min		ANALOGCONT_min
#define	DIGITALCONT_max		ANALOGCONT_max

#define	COMPOSITEBRT_min	ANALOGBRT_min
#define	COMPOSITEBRT_max	ANALOGBRT_max

#define	COMPOSITECONT_min	ANALOGCONT_min
#define	COMPOSITECONT_max	ANALOGCONT_max

#define	COMPOSITESHARP_min	SAA7114Sharp_min
#define	COMPOSITESHARP_max	SAA7114Sharp_max

#define	COMPOSITECOLOR_min	SAA7114Color_min
#define	COMPOSITECOLOR_max	SAA7114Color_max

#define	COMPOSITETINT_min	SAA7114Hue_min
#define	COMPOSITETINT_max	SAA7114Hue_max

#define	S_VIDEOBRT_min		ANALOGBRT_min
#define	S_VIDEOBRT_max		ANALOGBRT_max

#define	S_VIDEOCONT_min		ANALOGCONT_min
#define	S_VIDEOCONT_max		ANALOGCONT_max

#define	S_VIDEOSHARP_min	SAA7114Sharp_min
#define	S_VIDEOSHARP_max	SAA7114Sharp_max

#define	S_VIDEOCOLOR_min	SAA7114Color_min
#define	S_VIDEOCOLOR_max	SAA7114Color_max

#define	S_VIDEOTINT_min		SAA7114Hue_min
#define	S_VIDEOTINT_max		SAA7114Hue_max

#define	TvFineTuneValue_min	0
//#define	TvFineTuneValue_max	48			//꼭 짝수일것!!!

#if defined(USE_NTSCtuner)
#define	TvFineTuneValue_max	90			//꼭 짝수일것!!!
#else
#define	TvFineTuneValue_max	48			//꼭 짝수일것!!!
#endif


//2003.7.1 youngdo #define	TvFineTuneValue_min2	0
//2003.7.1 youngdo #define	TvFineTuneValue_max2	36

#define	TvFineTuneValue_min2	0
#define	TvFineTuneValue_max2	100


#define	TvFineCenter		(TvFineTuneValue_max/2)	

#define	VOLUME_min		0
#define	VOLUME_max		100
/*
VolumePWM(xEEPROMBuffer[VOLUME_buf]*2.22+33);
*/

 #ifndef BtcBoard_Option
//#define	PIPPOSITION_min		OSDPOSITION_min
//#define	PIPPOSITION_max		OSDPOSITION_max
 #endif


#define	PipHposition_min	0
#define	PipHposition_max	2	//812//(ModeList[CurrentMode].IHAW-512)
#define	PipVposition_min	0
#define	PipVposition_max	2	//570//(ModeList[CurrentMode].IVAW-460)



#define	PIPBLEND_min		0
#define	PIPBLEND_max		3

#define	Sleep_min		0
#define	Sleep_max		90


#define	LangBuf			xEEPROMBuffer[LANGUAGE_buf]
