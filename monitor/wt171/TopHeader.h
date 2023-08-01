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

   2003-01-10 2:39����  JDHAN           Modified for Monitor-TV
****************************************************************************/
#if !defined _NFREN_TOPHEADER_
#define _NFREN_TOPHEADER_

#include	<reg52.h>
#include	<intrins.h>
#include <stdio.h>			//smpark 
#include	"UTILmacro.h"
#include	"power.h"	//smpark
#include "sprocessor.h"

//-------------------------------------------------------------------------------------------------
// Board Option (select)
//-------------------------------------------------------------------------------------------------
#undef	EdtechTotalDemoBoard_Option//�̸���׸��߰�.
#undef	EdtechVpc3230DemoBoard_Option
#undef	EdtechEmotionBoard_Option
#undef	AtecBoard_Option
#define BtcBoard_Option
#undef	AtriumBoard_Option
#undef	CadinalBoard_Option
#undef	NewqSystemBoard_Option
//-------------------------------------------------------------------------------------------------

#ifdef	BtcBoard_Option		//**** Notice *****//
	//-------------------------------------------------------------------------------------------------
	#define	BTC_Version			0x18
	#undef	EMH1A
	#define	EMH2
	//----------------------------------------------------------------
	//#define	test_function	// function test �� debug option.
	#define	BURNING_TEST		// +jwshin 040813 Burning Test Mode Added...
	//----------------------------------------------------------------
	// first input signal select
	//-------------------------------------------------------------------------------------------------	
	#undef	Always_RGBFirst
	//*****************************
	#define	Always_FMRGBFirst	//***
	//*****************************
	#undef	Always_VIDEOFirst
	#undef	Always_FMVIDEOFirst
	#undef	Always_DVIFirst
	#undef	Always_FMDVIFirst
	#undef	Always_RGBCOMPOSITEPIP
	#undef	Always_TVFirst
	#undef	Always_FMTVFirst
	
	#ifdef 	Always_RGBFirst
	#define	RGB_LineSync
	#endif
	//-------------------------------------------------------------------------------------------------
	// MCU ����
	//-------------------------------------------------------------------------------------------------	
	#undef	MCU_MTV212
	#define	MCU_MTV230
	#undef	MCU_MTV412
	#undef	MCU_NT68F63//�߰�.
	//-------------------------------------------------------------------------------------------------
	// OSD ����	
	//-------------------------------------------------------------------------------------------------
	#undef	NoOsdMenu
	#undef	InternalOSD	// ����
	#define	INT_EXTOSD	// �ܺ� + ����
	
	#define	External_Debug
	#undef	HARDWAREI2C
	#undef	USE_4BitInterface
	
	//-------------------------------------------------------------------------------------------------
	// Key ����
	//-------------------------------------------------------------------------------------------------	
	#define	KEY_USE			//front-key���/������(���������θ������Ҷ�)
	#undef	MatrixLevel_KEY		//2line polling key ��Ʈ�������.
	#define	MTV230_ADC_KEY		//MTV230u-com ADCó���� ���� Ű ��Ʈ�������.
	#undef	MTV412_ADC_KEY		//MYV412u-com ADCó���� ���� Ű ��Ʈ�������.
	#undef	ADCKeyChange
	#undef	EdtechKeyHarness
	#define	ContinueToShortKeyDefine	//����Ű������ volumeŰ�߿��� ��Ű�� ����.
	#define	MenuKeyInitialize	//menu key�� 5���̻� ������ initialize�Ѵ�.

	//-------------------------------------------------------------------------------------------------
	// ADC Select
	//-------------------------------------------------------------------------------------------------
	#undef	AD9884
	#define	AD9883
	//-------------------------------------------------------------------------------------------------
	// Video Decoder select
	//-------------------------------------------------------------------------------------------------
	#undef	SAA7114
	#define	TW9908
	#undef	SAA7115
	#undef	VPX3226
	#undef	VPC323x			//3230�׸�.
	//-------------------------------------------------------------------------------------------------
	
	#define	CheckVideoStatus	//No-Video , 50Hz 60Hz�˻�
	#undef	FPSTATUS_ReadOK		//VPC3230 device����.
	
	//#define	Always_PowerOn		//system power(12V)�ΰ��Ǹ�.������ power-on/EEPROM ������ ���� �Ŀ� youngdo
	//-------------------------------------------------------------------------------------------------
//	#undef	DDC_ENABLE
	#define DDC_ENABLE
	
	//#define	MicomXFRbackup		//osdxfr, systemxfr backup for debug!!, enabl�ϰ� �Ǹ� xdata DWORD SumPhase[32] _at_	0x0A00;�� ���� warning�߻��Ѵ�.
	#undef	MicomXFRbackup		//osdxfr, systemxfr backup for debug!!, enabl�ϰ� �Ǹ� xdata DWORD SumPhase[32] _at_	0x0A00;�� ���� warning�߻��Ѵ�.
	
	#ifdef 	MicomXFRbackup	//
	#define	Mtv230OSDbackup	//
	#endif			//
	
	//#define Memory_1eaUse	//2004-02-09	//ram�� 1���� ���� ����.
	//#define	Ccd_Vchip	//2003-11-27	//CCD, V-chip �̿�� ����.
	//#define TempMemTest_pal	//2004-05-04
	//#define	Voluem_downCHINA		//2004-05-10	//�߱����� ������ �ٽ� �����.
	
	//-------------------------------------------------------------------------------------------------
	
	#define	StatusDisplay		//���ο�������Խ� ������ܿ� OSD!,recall.
	#undef	SXGA_60HzOver_NotSuuport//PC 1280x1024@75(135Mhz)
	
	#undef	PipDpmsON	//2003-10-21 pip�� dpms�϶� ��������..
	#undef	VideoDoubleOSD	//2003-10-24 	//video osd size -> double (?)
	#define OsdMenuFullBar	//2003-10-25	//osd menu bar range
	
	#define	OsdMenuType1		//2003-10-27	//Ư�� osd type ����//simple osd
	#define	PIPstyle2				//2004-05-25 	//�Ķ����� ���� �β���..
	#define	LoudBarType			//2004-05-28 	// Loud ǥ�� ����������...
	
	//#define	TempOsdMenu	//2003-10-29	//Osd������ ���� �ӽø޴�.
	//#define	ChannelDisplayDouble	//2003-11-17 //ä��ǥ�� ����/���� Ȯ��.
	#define	char_AVx		//2004-05-08 // Av1/2 or Composite/S-Video ǥ������ ����.

	#define	Wide4_3Aspect	// wide17"���� 4:3ȭ������� ǥ�� �����ϰ�.//2003-12-30
	
	//#define Mono_Sound	//test
//	#define	TestTunerSound	//test//msp i2c ���� �˻� �ߴ�
//	#define TestOsdAlwayOn	//2003-10-28	//osd test�� ����.
	#define	IntOsdBar		//2004-01-06 // ����OSD bar(����BackGround)
//	#define TestCH			//test
		//-------------------------------------------------------------------------------------------------
	#define	USE_TUNER
	//#define	USE_NTSCtuner
	#define	USE_PALSECAMtuner
	//---------------------------------------------------------------	
	#ifdef	USE_PALSECAMtuner
	#define	TunerRefDiv512
	#define OsdColor_Red	// �߱��� osdĮ��� ��������...//2004-01-02
	#define ChannelEdit_1	// channel edit �κ� simple�Ѱ�..//2004-05-06
	#define	PalCountry_ChinaOnly	//2004-05-10	//�߱� ���ļ��� ���...
	#define	FrequncyTableType			//2004-06-21
	#define	Country2TVtype	//2004-07-05 	//���ļ� ����ǥ�� ���ϰ�, pal�� ǥ��.
		//#ifdef Country2TVtype
		//#define	PAL_DK
		//#endif
	//#define	China_Freq
	//#define	Malaysia_Freq
	#define Russia_Freq
			
	#endif
	//---------------------------------------------------------------
	
	//Board Version.
	#if defined(USE_NTSCtuner)
	#define	MyboardID 0x44
	#elif defined(USE_PALSECAMtuner)
	#define	MyboardID 0x54
	#endif
	//-------------------------------------------------------------------------------------------------
	//#undef	FullScaleToVertical	// wide������ �����ϴ°� ����. ������ϸ� H�� ���ؼ��� ���̵�.
	//#define	FullScaleToVertical	//--> panel data.h�� ����!!!
	//-------------------------------------------------------------------------------------------------
	#define	InvertValueSlope	//invert pwm ���.
	#define	AdcGainSlope
	//#define	MultiLanguage
	//#undef  MultiLanguage
	#undef	DVI_USE				//DVI����� ����/�Ұ���.
	#undef	DVI_EDIDWrite		//DVI EDID writing(����ϱ� ���� �ϵ��������� �ʿ���)
	#undef	DviSyncCheck_IVIHID	//DVI �Է����ļ� �˻��� iv,ih,ide(�����Ϸ����)�� �˻�(��ȣ�����Ǵ�)
	#undef	DVIEDID_1st
	#undef	DVIEDID_2nd
	#undef	DrowCircle			//OHFACTOR,OVFACTOR��� ������ ����
	#define	ValuePercentChar_Blue
	#undef	Version_Display		//version�� �Ⱥ��δ�.
	#define	Board2nd
	#undef	PercentDigitArray
	#undef	USE_Coef			//coef ���ͻ��
	//-------------------------------------------------------------------------------------------------
	#define   USE_remocon
//	#undef   USE_remocon
//	#define VOLUME_PWM			// use PWM volume control


	
	#ifndef USE_remocon
	#define	USE_UART 
	#endif	
	#undef	Remocon_1st
	#undef	Remocon_2nd
	#undef	Remocon_3th
	#define  Remocon_BTC
	//#undef  Remocon_PNIX
	//-------------------------------------------------------------------------------------------------
	//#include	"PnlLM181E06.h"	//Panel parameters
	//#include	"PnlHT17E12.h"	//Panel parameters	//���� 17" e12
	//#include	"PnlLTM170EH.h"	//Panel parameters	//�Ｚ 17" eh/e4
	//#include	"PnlQD170EL07.h"//Panel parameters	//Quanta 17"/LG17"(L01)
	//#include	"PnlLM171W01.h"	//LG 17.1" WXGA	//5V
	#include	"PnlLM171W03.h"	//LG 17.1" WXGA	//12V
	//#include	"PnlLTM171W1.h"	//SS 17.1"(L01) WXGA
	//-------------------------------------------------------------------------------------------------
	#define SAMSUNG_TCPN9082DA27C		1	//SAMSUNG NTSC ����Ʃ��, PHILIPS ����Ʃ�ʵ� �̰����� �����Ѵ�.
	#define LGINOTEK_TAPC_H701F			2	// LG NTSC����Ʃ��
	#define SAMSUNG_TCPQ9091PD27D		3	// SamSung Pal-Multi ����Ʃ��
	#define SAMSUNG_TCPQ9091PD28L		4	// SamSung PAL ���� Ʃ��.
	
	#ifdef USE_NTSCtuner
	#define CURRENT_TUNNER		SAMSUNG_TCPN9082DA27C	//SAMSUNG NTSC ����Ʃ��
	//#define CURRENT_TUNNER		LGINOTEK_TAPC_H701F
	#else
	#define CURRENT_TUNNER		SAMSUNG_TCPQ9091PD27D
	#endif
	//-------------------------------------------------------------------------------------------------
	#define savememory
	#undef	USE_TTX
	#undef   USE_SCART
	#undef 	USE_TTXIIC
#endif



///////////////////////////////////////////////////
//	type define
///////////////////////////////////////////////////
typedef unsigned char  BYTE;        /* 0           to 255 */
typedef unsigned int   WORD;        /* 0           to 65535 */
typedef unsigned long  DWORD;       /* 0           to 4294967295 */
#define	Bool		bit
#define   xBYTE		xdata BYTE
#define	xUCHAR		xdata BYTE

#if	defined(MCU_MTV230)||defined(MCU_NT68F63)||defined(MCU_MTV412)
		#define	MaxBufferSize 	128
		#define	MaxEepromBuffer	64
#endif


/////////////////////////////////////////////////
//	Timer factor define
/////////////////////////////////////////////////
#define XTAL_FREQ		  		12000000L
#define TIMER0_INTERVAL1		1000							//1/uSEC unit
#define TIMER0_INTERVAL2		200							//1/uSEC unit
#define TIMER0_INTERVAL3		142							//1/uSEC unit
#define TIMER0_INTERVAL4		100							//1/uSEC unit

#define TIMER1_INTERVAL0		10000							//1/uSEC unit
#define	TIMER1_INTERVAL1		5000							//1/uSEC unit

#define TIMER_100us			(XTAL_FREQ/12/TIMER1_INTERVAL0)
#define TIMER_200us			(XTAL_FREQ/12/TIMER1_INTERVAL1)
#define TIMER_1ms			(XTAL_FREQ/12/TIMER0_INTERVAL1)
#define TIMER_5ms			(XTAL_FREQ/12/TIMER0_INTERVAL2)
#define TIMER_7ms			(XTAL_FREQ/12/TIMER0_INTERVAL3)
#define TIMER_10ms			(XTAL_FREQ/12/TIMER0_INTERVAL4)

#define	TIMER_50ms			10							//at TIMER_5ms
#define	TIMER_70ms			14							//at TIMER_5ms
#define	TIMER_100ms			20							//at TIMER_5ms
#define	Timer_300ms			60							//at TIMER_5ms
#define TIMER_500ms			100							//at TIMER_5ms
#define	TIMER_1000ms			200							//at TIMER_5ms
#define	TIMER_4000ms			800							//at TIMER_5ms
#define	TIMER_5000ms			1000							//at TIMER_5ms
#define	TIMER_6000ms			1200							//at TIMER_5ms


#define Timer0_1Cycle			(65535L-TIMER_5ms)					//16bit mode(65536L)
#define	Timer1_1Cycle			(255-TIMER_200us)

#define	step_1min			(60000/5);  //1�д���(6x10^4ms�� 5ms���� ����)//2003-07-31 by thkim
//#define	step_1min			(600/5);  //0.6s����//test


/////////////////////////////////////////////////
//	Timer0 SetValue define
//	
//	Setting Timer0 Interrupt Info.
//	GATE=0,C/TB=0,M1 M0 = 01(16Bit Cascade Timer)
//	all Timer 0,1
//	Timer 0 Enable
//	Timer 0 Start
/////////////////////////////////////////////////
#define	Timer0InterruptSet		{	\
		TL0	= Timer0_1Cycle;	\	
		TH0	= Timer0_1Cycle>>8;	\
		TMOD = 0x11;			\
		ET0	= 1;			\
		TR0	= 1;		}


/////////////////////////////////////////////////
//	External"0"
//	EX0 enable
//	TCON's IT0 high(falling edge)
//	Timer : 200us cycle
//	TIMER1 set!
/////////////////////////////////////////////////
#ifdef USE_remocon
#define	EXT0_Timer1InterruptSet	{		\
		EX0 = 1;			\
		IT0 = 1;			\
		TH1	= Timer1_1Cycle;	\	
		TMOD = 0x21;			\
		ET1	= 1;			\
		TR1	= 1;	}
#endif				

/////////////////////////////////////////////////
//	IPS & Debug ProgramSet define
// 	DDC ProgramSet define
//	slave A , B�߿��� B channel �����
//	slave A�� DDC�� �Ҵ��
//
//	�������� �����巹��(B) 0x54�� ��
//	�������� �����巹��(A) 0xA0�� ��
//	RCBBUF, SlaveAddr B match, Master IIC enabel
//	NovaTek�������� ��� EDID����Ÿ ������ �ʿ��ϹǷ� ���������Ͽ� �߰��Ұ�
/////////////////////////////////////////////////

//**EXT_I2C_Enable define�� ���� �ɼ�**
//DDC,ISP or Debug�� ���� �ɼ�.
//
//
#if 	defined(External_Debug)&&defined(DDC_ENABLE)
	#if	  defined(MCU_MTV230)
		#define	EXT_I2C_Enable				{\
			xSLVBADR	= 0x80|(0x54>>1);	\
			xSLVAADR	= 0x80|(0xA0>>1);	\
			xINTENI2C	= 0x80|0x40|0x1C|2;		\
			EX1	= 1;						}	
	#elif defined(MCU_MTV412)
		#define	EXT_I2C_Enable				{\
			ERROR,if use DDC, RAM problem	}	
	#elif defined(MCU_NT68F63)
		#define	EXT_I2C_Enable				{\
			xIIC0_ADDR = 0x54;				\
			xIIC0_CLK = 0x00;				\
			xINTIIC0_EN=	0x10|0x08|0x04|0x01;\
			xINTIIC0_FLG= 0x1F;				\
			EX1 = 1;						}	
	#endif
#elif	defined(External_Debug)
	#if	  defined(MCU_MTV230)||defined(MCU_MTV412)
		#define	EXT_I2C_Enable				{\
			xSLVBADR	= 0x80|(0x54>>1);	\
			xINTENI2C	= 0x80|0x40;		\
			EX1	= 1;						}
	#elif defined(MCU_NT68F63)
		#define	EXT_I2C_Enable				{\
			xIIC0_ADDR = 0x54;				\
			xIIC0_CLK = 0x00;				\
			xINTIIC0_EN=	0x10|0x08|0x04|0x01;\
			xINTIIC0_FLG= 0x1F;				\
			EX1 = 1;						}	
	#endif
#elif	defined(DDC_ENABLE)
	#if	  defined(MCU_MTV230)
		#define	EXT_I2C_Enable				{\
			xSLVAADR	= 0x80|(0xA0>>1);	\
			xINTENI2C	= 0x1C|2;			\
			EX1	= 1;						}		
	#elif defined(MCU_MTV412)
		#define	EXT_I2C_Enable				{}
		
	#elif defined(MCU_NT68F63)
		#define	EXT_I2C_Enable				{\
			xIIC0_ADDR = 0x54;				\
			xIIC0_CLK = 0x00;				\
			xINTIIC0_EN=	0x10|0x08|0x04|0x01;\
			xINTIIC0_FLG= 0x1F;				\
			EX1 = 1;						}		
	#endif
#else											//I2C��� �����ϸ� ~
		#define	EXT_I2C_Enable				{}
#endif


/////////////////////////////////////////////////
//	WatchDog & ADC Macro
//
/////////////////////////////////////////////////

#if	defined(MCU_MTV230)
#define	WDTClear		{xWDT = 0x00;}
#define	ADCdisable		{xADC = 0x00;}
#define	ADCenablePIN_0_1{xADC = 0x80|0x01|0x02;}

#elif	defined(MCU_MTV412)
#define	WDTClear		{xWDT = 0x00;}
#define	ADCdisable		{xADC = 0x00;}
#define	ADCenablePIN_0_1{xADC = 0x80|0x01|0x02;}
#define	ADCenablePIN_0_1_2{xADC = 0x80|0x01|0x02|0x04;}

#elif	defined(MCU_NT68F63)
#define	WDTClear		{xCLR_WDT=0x55;}
#define	ADCdisable		{xADC_CON = 0x00;}
#endif	


/////////////////////////////////////////////////
//	�������� �⺻��Ʈ ���� �� �߿� �������� ����
//	
//	�켱 �ؾ� ����
//	1.WatchDog ?
//	2.ADC ?
//	3.Important OptionRegister ?(@MTV device)
//		PWM Freq?
//		PWM Division?
//		CPU Clock?
//		IIC Config?
//	4.PortSet ?
//	5.Interrupt ?		(@NovaTek External)
//	5.H/V sync ?
//	6.IIC
//	7.FlashMemory ?		(@NovaTek)
//	8.USB ?				(@NovaTek)
/////////////////////////////////////////////////


#if	defined(MCU_MTV230)&&defined(BtcBoard_Option) 

#define	MTV230XfrSet		{\
			WDTClear;		\
			ADCenablePIN_0_1;	\
			xOPTION1 = 0x00;	\			
			xPADMOD1 = 0X81;	\
			xPADMOD2 = 0xA3;	\
			xPADMOD3 = 0xFC;	\
			xPADMOD4 = 0xE0;	\
			xP40 = 0;		\
			xP41 = 0;		\
			xP42 = 0;		\
			xP43 = 0;		\
			xP44 = 0;		\
			xP45 = 0;		\
			xP46 = 0;		\
			xP47 = 0;		\
			xP50 = 0;		\
			xP51 = 0;		\
			xP52 = 0;		\
			xP53 = 0;		\
			xP56 = 0;		\
			xP57 = 0;		\
			xHVSTUS = 0x80;		\
			xHCNTL = 0x00;		\
			xVCNTH = 0x00;		}		

#endif
	

/////////////////////////////////////////////////
//	ATEC MTV230 Initial & OSD utility
//	0xFCEh:CH
/////////////////////////////////////////////////
#if	defined(AtecBoard_Option)||defined(CadinalBoard_Option)||defined(AtriumBoard_Option)||defined(EdtechEmotionBoard_Option)\
	||defined(BtcBoard_Option)
#define MTV230OSDInit	{\
				xOSD_WIN_REG[0x0E]=0x01;\
				}
#else
#define MTV230OSDInit	{\
				NOP;\
				}
#endif

#if defined(InternalOSD)
#define	OSDOFF	{}
#else
#define	OSDOFF	{xOSDW_OPTION[1]=0x00|0x02;}
#endif


/////////////////////////////////////////////////
//	LED define
//
/////////////////////////////////////////////////



#if	defined(MCU_MTV230)&&defined(BtcBoard_Option) 
#define	ON	1
#define OFF	0
#define	LED_GRN(val)	{xP42 = val;}
#define	LED_OFF 	{LED_GRN(OFF);}
#define	LED_ON	LED_GRN(ON)	//test

#endif


/////////////////////////////////////////////////
//	KEY define & KEY chattering timing����.
//  
/////////////////////////////////////////////////
#if	defined(MCU_MTV230) && defined(MTV230_ADC_KEY)
#define	KEY_chatteringTime	TIMER_50ms
//#define	KEY_chatteringTime	TIMER_70ms
#define	Key_MenuSystemInit	TIMER_5000ms
//#define	Key_MenuSystemInit	TIMER_6000ms+TIMER_1000ms
#endif


/////////////////////////////////////////////////
//	SCALER Interface Pin define
//
/////////////////////////////////////////////////

#if	defined(MCU_MTV230)&&defined(BtcBoard_Option) 

	sbit	IOPD1=	P1^0;//Input
	sbit	IOPD0=	P1^1;//output
	sbit	SCLK=	P1^2;//Clock
	sbit	SCALER_CS= P1^3;//CS

	#define	_SCALER_CS_HIGH		{SCALER_CS = 1;}
	#define	_SCALER_CS_LOW		{SCALER_CS = 0;}
	#define	_SCALER_RST_LOW		{xP43 = 0;}
	#define	_SCALER_RST_HIGH	{xP43 = 1;}


#endif


/////////////////////////////////////////////////
//	System Pin define
//
//	1. systemp power 
//	-> pin39, DA4, DACtype
//
//	2. ADC enable, DA11, DACtype
//
/////////////////////////////////////////////////



#if	defined(MCU_MTV230)&&defined(BtcBoard_Option) 
	#define	_PowerON				{xP62 = 0;}
	#define	_PowerOFF			{xP62 = 1;}
	#define	PanelModulePowerOn		{xP44 = 0;}
	#define	PanelModulePowerOff		{xP44 = 1;}

	#define	TunerPowerOn		{xP47 = 0;}
	#define	TunerPowerOff		{xP47 = 1;}

//	sbit  AUDIOSEL0=P1^7;
//	sbit  AUDIOSEL1=P1^6;

	sbit  TTX_SCL=P1^7;
	sbit  TTX_SDA=P1^6;	
	#define AUDIOSEL0	xP60
	#define AUDIOSEL1	xP45
	
	#ifdef	Board2nd
	#ifdef	AtriumBoard_Option
//	#define	AsyncOn				{xP45 = 1;}
//	#define	AsyncOff			{xP45 = 0;}
	#else
//	#define	AsyncOn				{xP45 = 0;}// D-sub enable
	#define	AsyncOn			{}	//youngdo 2003.6.23
//	#define	AsyncOff			{xP45 = 1;}	//DVI enable
	#define	AsyncOff			{}	//youngdo 2003.6.23
	#endif
	#else
//	#define	AsyncOn				{xP45 = 1;}
//	#define	AsyncOff			{xP45 = 0;}
	#endif
	
#ifdef VOLUME_PWM
	#define	AudioSelection_TV		{AUDIOSEL1 = 1;AUDIOSEL0 = 0;SoundInputSelection(0);}
	#define	AudioSelection_AV		{AUDIOSEL1 = 1;AUDIOSEL0 = 1;SoundInputSelection(2);}
	#define	AudioSelection_PC		{AUDIOSEL1 = 0;AUDIOSEL0 = 1;SoundInputSelection(2);}
	#define	AudioSelection_SCART		{AUDIOSEL1 = 0;AUDIOSEL0 = 0;SoundInputSelection(2);}
#else
//		#if defined(Mono_Sound)
//	#define	AudioSelection_TV		{AUDIOSEL1 = 1;ScartSwitch(0x0100);SoundInputSelection(2);} //MONO
//		#else
	#define	AudioSelection_TV		{AUDIOSEL1 = 1;SoundInputSelection(0);}	//Tuner
//		#endif
	#define	AudioSelection_PC		{AUDIOSEL1 = 1;ScartSwitch(0x0000);SoundInputSelection(2);} // SCART1
	#define	AudioSelection_AV		{AUDIOSEL1 = 1;ScartSwitch(0x0200);SoundInputSelection(2);} // SCART2
#endif
	
	#define	InvertOn			{xP56 = 1;InvertSmartStart();}
	#define	InvertOff			{xP56 = 0;InvertPwmOFF;}
	#define	InvertPWM(val)			{xDAC[3]	=val; }
	#define	InvertPwmOFF			{xDAC[3]	=0x00;}

	
	
	#define	DVIEN_HIGH			{NOP;}
	#define	DVIEN_LOW			{NOP;}
	
	#define	LVDS_OFF			{NOP;}
	#define	LVDS_ON				{NOP;}
	
	#define	CLKINV_HIGH			{NOP;}
	#define	CLKINV_LOW			{NOP;}
	sbit	TW9908_RST	=	P3^5;
	#define	TW9908_RSTON		{TW9908_RST=0;}
	#define	TW9908_RSTOFF		{TW9908_RST=1;}	
	sbit	ST_DET	=	P3^4;
			
//		sbit	SCDT=	P1^7;//Input
		
//	#define	VIDEO_HIGH		{xP45 = 1;}
//	#define	VIDEO_LOW		{xP45 = 0;}


		sbit	SCL	=	P1^4;//Output
		sbit	SDA	=	P1^5;//In/Output		

	#define	MUTE_HIGH		{xP61 = 1;}
	#define	MUTE_LOW		{xP61 = 0;}	

	#define ADCEnable 				{\
	bit WriteI2C(BYTE sysaddr, BYTE subaddr, BYTE writedata);\
	WORD ReadI2C(BYTE SystemAdr, WORD address);\
	WriteI2C(ADC_sysaddress,0x0F,((BYTE)ReadI2C(ADC_sysaddress,0x0F)|0x02));}
	
	#define	ADCDisable				{\
	bit WriteI2C(BYTE sysaddr, BYTE subaddr, BYTE writedata);\
	WORD ReadI2C(BYTE SystemAdr, WORD address);\
	WriteI2C(ADC_sysaddress,0x0F,((BYTE)ReadI2C(ADC_sysaddress,0x0F)&0xFD));}
	
	#define	DVIEnable				DVIEN_HIGH
	#define	DVIDisable				DVIEN_LOW
	

	#ifdef VOLUME_PWM	////////////////////////////////////
		#define	VolumePWM(val)			{xDAC[1] = val;}
	
		//	#define	SOUNDSTBY_ON		{xP60 = 1;}
		//	#define	SOUNDSTBY_OFF		{xP60 = 0;}
			#define	SOUNDSTBY_ON		{}
			#define	SOUNDSTBY_OFF		{}   
	
/*		#define MuteOff_VolumeDown		{\
								MUTE_LOW;\
			 					VolumePWM(0);}//2003-10-06 4:52����
*/	
		
		#define	VIDEOenable				{\
										MUTE_LOW;\
										VolumePWM(0);}
	//							AVDecoderWakeup();}		
										
		#define	VIDEOdisable			{\
										MUTE_LOW;\
										VolumePWM(0);}
	//							AVDecoderSleep();}
		
		#define	Mute_SoundOff			{\
										MUTE_HIGH;\
										VolumePWM(0);}
										
		#define	Mute_SoundOn			MUTE_LOW;
	#else		///////////////////////////////////////////////
		#define	SOUNDSTBY_ON		{xDAC[1]=0;}
		#define	SOUNDSTBY_OFF		{xDAC[1]=0xff;}

/*		#define MuteOff_VolumeDown		{\
										MUTE_LOW;\
		 								SoundFastMute();}
*/		
		#define	VIDEOenable				{\
										MUTE_LOW;\
		 								SoundFastMute();}
										
		#define	VIDEOdisable			{\
										MUTE_LOW;\
		 								SoundFastMute();}

		#define	Mute_SoundOff			{\
										MUTE_LOW;\
		 								SoundFastMute();}
										
		#define	Mute_SoundOn			MUTE_HIGH;

	#endif	//////////////////////////////////////////////

	
#endif

/////////////////////////////////////////////////
//	Device Sys address define
//	Remocon custom code
//	TV fine tune value
/////////////////////////////////////////////////
#define	I2CErrorTry					5			//I2C fail�� ����� 5������ ��õ� �Ѵ�.
#define EEPROM_sysaddress			0xA0		//24LC16�� �ý��� ��巹���� 0xA0�̴�.
#define EEPROM_sysaddress_2402		0xA2		//24LC02�� �ý��� ��巹���� 0xA2�̴�.
#define	ModeEepromStartAddress		0x0
#define	TVchannelEepromStartAddress	0x200

#ifdef	AD9884
		#define	ADC_sysaddress		0x98	//AD9884�� �ý��� ��巹���� 0x98�̴�.
#elif	defined(AD9883)
		#define	ADC_sysaddress		0x98
#endif

#define	VPC323x_sysaddress			0x88		//VPC3230 decoder�� �ý��� ��巹���� 0x88�̴�.
#define	SAA7114_sysaddress			0x42		//SAA7114 decoder�� �ý��� ��巹���� 0x42�̴�.
#define	SAA7115_sysaddress			0x42		//SAA7115 decoder�� �ý��� ��巹���� SAA7114�� ����.
#define TW990x_SysAddr				0x88


/////////////////////////////////////////////////
//	Type structure!!
//
/////////////////////////////////////////////////
typedef struct
{
	BYTE Phase;
	WORD HF;
	WORD VF;
	WORD HTotal;
	WORD IHAS;
	WORD IVAS;
	WORD IHAW;
	WORD IVAW;
	BYTE IClkDly;
}	ModeTable;

typedef struct
{
	WORD PipHwidth;
	WORD PipVwidth;
} PipHVwidth;

typedef struct
{
	BYTE MinValue;
	BYTE MaxValue;
	BYTE EepromAdr;	
} valuestruct;

typedef struct
{
	BYTE	CHANNELNUM;
	WORD	TUNERPLL;
}	TunerTable;

/////////////////////////////////////////////////
//	OSD Define
/////////////////////////////////////////////////
#define	F_START			0x78
#define	F_STOP			0x79
	
#define	F_STOP			0x79
#define	IN_F_START		0x3E
#define	IN_F_STOP		0x3F


/////////////////////////////////////////////////
//	OSD Define
/////////////////////////////////////////////////

//==================================================================================================
#if defined(BtcBoard_Option)		//2003-04-14
//==================================================================================================
//OSDstatus, MENUstatus
#define	NotBUSY				0
#define	TopMenuWindow			1
#define SubMenuWindows			2
#define	VolumeDisplay			3
#define	Cursermove			4
#define	OSDCharArray			5
#define	OSDoff				6
#define	Mode_ResDisplay			7
#define	Nosignal_Display		8
#define	ColorTempWindow			9
#define FactoryRstOSD			10	//2003-04-30
/*
#define	RGB_Nosignalwindow	7
#define	DVI_Nosiganlwindow	8
#define	COMPOSITE_Nosignalwindow 9
#define	S_VIDEO_Nosignalwindow	10
*/
#define	Outofmode_Display		11
#define	OSDexpire_timer			12
#define	ValueDisplay			13
#define	TVchannelDisplay		14
#define	TVChannelNum			15
#define	OsdRamClear			16
#define	OSDwait				17
#define	AUTOTuneOSD			18
#define	NowStatusDisplay		19
#define	Subwindow			20
#define	AutoSearchChannelDisplay 	21
#define	SearchingDisplay		22
#define	MuteDisplay			23
#define	AddSelChannelDisplay 		24
#define	MinMaxValueNotApply		25
#define	CheckCableDisplay		26
#define	ReMuteDisplay			27
#define	ReVolumeDisplay			28

#define volume_mode			29	//2003-04-21
#define	OSDHotkeyMessageWindow		30
#define	PipWindows			31

#define SubMenuWindows2			32	//2003-05-27
#define CountryWindow			33
#define AutoChSetupWindow		34
#define	SscWindowDisplay		35
#define	SpcWindowDisplay		36
#define	MtsWindowDisplay		37
#define	SleepWindowDisplay		38	

#define RecallWindowDisplay		39
#define AddDelWindowDisplay		40
#define ChannelStatusDisplay		41


//OSDWindows
#define	AnalogSubwindow			1
#define	AnalogMainWindow		2
#define	AnalogPowerSaverWindow		3
#define	AnalogOutofFreqWindow		4
#define	AnalogSelfDigWindow		5
#define	DigitalSubWindow		6
#define	DigitalMainWindow		7
#define	DigitalPowerSaverWindow		8
#define	DigitalSelfDigWindow		9
#define	CompositeSubwindow		10
#define	CompositeNoVidSubwindow		11
#define	CompositeMainwindow		12
#define	S_videoSubwindow		13
#define	S_videoNoVidSubwindow		14
#define	S_videoMainWindow		15
#define	ChannelNumWindow		16
#define	TunerSubWindow			17
#define	TunerMainWindow			18
#define	PIPSubWindow			19
#define	PIPNoVideoWindow		20
#define	PIPMainWindow			21
#define	AutoTuneMainWindow		22
#define	VolumeWindow			23
#define	PipSelectionGuideWindow		24
#define	MuteWindow			25
#define	SscWindow			26
#define	SpcWindow			27
#define	MtsWindow			28
#define	SleepWindow			29

#define RecallWindow			30

//OSDcharacters
#define	AnalogMainChars			1	//br/con,color,position,setup,exit
#define	AnalogBrtChars			2	//brightness,contrast,exit
#define	AnalogColChars			3	//preset1,preset2,red,green,blue,exit
#define	AnalogPosChars			4	//horizontal,vertical,clock,phase,exit
#define	AnalogSetChars			5	//osd position,osd time,input source,exit
#define	VolumeChars			6	//volume
#define	TunerMainChars			7	//br/con,color,channel,setup,exit
#define	TunerBrtChars			8	//brightness,contrast,exit
#define	TunerColChars			9	//sharpness,color,tint,exit
#define	TunerChanChars			10	//air/catv,auto channel,manual channel,fine,exit
#define	TunerSetChars			11	//osd position,osd time,input source,exit
#define	DigitalMainChars		12	//br/con,color,positio,setup,exit
#define	DigitalBrtChars			13	//brightness,contrast,exit
#define	DigitalSetChars			14	//osd position,osd time,input source,exit
#define	CompositeMainChars		15	//br/con,color,position,setup,exit
#define	CompositeBrtChars		16	//brightness,contrast,exit
#define	CompositeColChars		17	//sharpness,color,tint,exit
#define	CompositeSetChars		18	//osd position,osd time,input source,exit
#define	S_videoMainChars		19	//br/con,color,position,setup,exit
#define	S_videoBrtChars			20	//brightness,contrast,exit
#define	S_videoColChars			21	//sharpness,color,tint,exit
#define	S_videoSetChars			22	//osd position,osd time,input source,exit
#define	PIPMainChars			23	//br/cont,color,pip,setup,exit
#define	PIPPipChars			24	//pip on/off, pip source, pip size, pip control, exit
#define	PIPControl			25	//pip swap, pip position, pip blend, exit
#define	PIPSetChars			26	//osd position,osd time,input source,pip source,exit
#define	AutoTuneChars			27
#define	AutoChannelChars		28	//processing auto...
#define	AutoSearchChannelChars		29	//
#define	AnalogSubChars			30	//analog
#define	DigitalSubChars			31	//digital
#define	TunerSubChars			32	//tuner
#define	CompositeSubChars		33	//composite
#define	S_videoSubChars			34	//S_video
#define	ChannelNumChars			35	//AIR:33
#define	CableChannelNumChars		36	//CATV:33
#define	ChannelOnlyNumber		37	//  33
#define	AnalogPowerSaverChars		38	//analog power saver mode
#define	DigitalPowerSaverChars		39	//digital power saver mode
#define	PipPowerSaverChars		40	//digital power saver mode
#define	OutOfFreqChars			41	//out of freqency
//#define	AnalogSelfDigChars		42	//analog diagnostic..
//#define	DigitalSelfDigChars		43	//digital diagnostic..
//#define	SelfRastCount			44	//20,19,,,
#define	CheckSignalCableChars		45
#define	PipSelectionGuideChars		46
#define	PipRgbCompositeChars		47
#define	PipRgbSvideoChars		48
#define	PipRgbTunerChars		49
#define	PipDviCompositeChars		50
#define	PipDviSvideoChars		51
#define	PipDviTunerChars		52
#define	MuteChars			53

#define	OSDHotkeyMsgChar		54

#define	PcChar				55
#define	TvChar				56
#define	Av1Char				57
#define	Av2Char				58
#if defined(USE_SCART)	
#define   ScartSubChars			59                       
#define	PipRgbScartChars		60                       
#define	PipDviScartChars		61                       
#endif                                                           
#define	SscChar				62		//03-08-06
#define	SpcChar				63                       
#define	MtsChar				64                       
#define	SleepChar			65                       
                                                                 
#define RecallChar			67

                                                                 
//smpark 20030810
#define DISPLAY_ADD_DEL   	0x01                                                              
#define DISPLAY_MTS			0x02                                                
                                                                 
//===============================================================
#else	//standard tv b/d                                        
//===============================================================
//(OSDstatus&MENUstatus)
#define	NotBUSY				0
#define	Totalwindow			1
#define	VolumeDisplay			2
#define	Cursermove			3
#define	OSDCharArray			4
#define	OSDoff				5
#define	Mode_ResDisplay			6
#define	Nosignal_Display		7
/*
#define	RGB_Nosignalwindow	7
#define	DVI_Nosiganlwindow	8
#define	COMPOSITE_Nosignalwindow 9
#define	S_VIDEO_Nosignalwindow	10
*/
#define	Totalwindow			1                        
#define	VolumeDisplay			2                        
#define	Cursermove			3                        
#define	OSDCharArray			4                        
#define	OSDoff				5                        
#define	Mode_ResDisplay			6                        
#define	Nosignal_Display		7                        
/*                                                               
#define	RGB_Nosignalwindow	7                                
#define	DVI_Nosiganlwindow	8                                
#define	COMPOSITE_Nosignalwindow 9                               
#define	S_VIDEO_Nosignalwindow	10                               
*/                                                               
#define	AddSelChannelDisplay 		24
#define	MinMaxValueNotApply		25
#define	CheckCableDisplay		26
#define	ReMuteDisplay			27
#define	ReVolumeDisplay			28

//OSDWindows
#define	AnalogSubwindow			1
#define	AnalogMainWindow		2
#define	AnalogPowerSaverWindow		3
#define	AnalogOutofFreqWindow		4
#define	AnalogSelfDigWindow		5
#define	DigitalSubWindow		6
#define	DigitalMainWindow		7
#define	DigitalPowerSaverWindow		8
#define	DigitalSelfDigWindow		9
#define	CompositeSubwindow		10
#define	CompositeNoVidSubwindow		11
#define	CompositeMainwindow		12
#define	S_videoSubwindow		13
#define	S_videoNoVidSubwindow		14
#define	S_videoMainWindow		15
#define	ChannelNumWindow		16
#define	TunerSubWindow			17
#define	TunerMainWindow			18
#define	PIPSubWindow			19
#define	PIPNoVideoWindow		20
#define	PIPMainWindow			21
#define	AutoTuneMainWindow		22
#define	VolumeWindow			23
#define	PipSelectionGuideWindow		24
#define	MuteWindow			25

//OSDcharacters
#define	AnalogMainChars			1	//br/con,color,position,setup,exit
#define	AnalogBrtChars			2	//brightness,contrast,exit
#define	AnalogColChars			3	//preset1,preset2,red,green,blue,exit
#define	AnalogPosChars			4	//horizontal,vertical,clock,phase,exit
#define	AnalogSetChars			5	//osd position,osd time,input source,exit
#define	VolumeChars			6	//volume
#define	TunerMainChars			7	//br/con,color,channel,setup,exit
#define	TunerBrtChars			8	//brightness,contrast,exit
#define	TunerColChars			9	//sharpness,color,tint,exit
#define	TunerChanChars			10	//air/catv,auto channel,manual channel,fine,exit
#define	TunerSetChars			11	//osd position,osd time,input source,exit
#define	DigitalMainChars		12	//br/con,color,positio,setup,exit
#define	DigitalBrtChars			13	//brightness,contrast,exit
#define	DigitalSetChars			14	//osd position,osd time,input source,exit
#define	CompositeMainChars		15	//br/con,color,position,setup,exit
#define	CompositeBrtChars		16	//brightness,contrast,exit
#define	CompositeColChars		17	//sharpness,color,tint,exit
#define	CompositeSetChars		18	//osd position,osd time,input source,exit
#define	S_videoMainChars		19	//br/con,color,position,setup,exit
#define	S_videoBrtChars			20	//brightness,contrast,exit
#define	S_videoColChars			21	//sharpness,color,tint,exit
#define	S_videoSetChars			22	//osd position,osd time,input source,exit
#define	PIPMainChars			23	//br/cont,color,pip,setup,exit
#define	PIPPipChars			24	//pip on/off, pip source, pip size, pip control, exit
#define	PIPControl			25	//pip swap, pip position, pip blend, exit
#define	PIPSetChars			26	//osd position,osd time,input source,pip source,exit
#define	AutoTuneChars			27
#define	AutoChannelChars		28	//processing auto...
#define	AutoSearchChannelChars		29	//
#define	AnalogSubChars			30	//analog
#define	DigitalSubChars			31	//digital
#define	TunerSubChars			32	//tuner
#define	CompositeSubChars		33	//composite
#define	S_videoSubChars			34	//S_video
#define	ChannelNumChars			35	//AIR:33
#define	CableChannelNumChars		36	//CATV:33
#define	ChannelOnlyNumber		37	//  33
#define	AnalogPowerSaverChars		38	//analog power saver mode
#define	DigitalPowerSaverChars		39	//digital power saver mode
#define	PipPowerSaverChars		40	//digital power saver mode
#define	OutOfFreqChars			41	//out of freqency
//#define	AnalogSelfDigChars		42	//analog diagnostic..
//#define	DigitalSelfDigChars		43	//digital diagnostic..
//#define	SelfRastCount			44	//20,19,,,
#define	CheckSignalCableChars		45
#define	PipSelectionGuideChars		46
#define	PipRgbCompositeChars		47
#define	PipRgbSvideoChars		48
#define	PipRgbTunerChars		49
#define	PipDviCompositeChars		50
#define	PipDviSvideoChars		51
#define	PipDviTunerChars		52
#define	MuteChars			53

//==================================================================================================
#endif
//==================================================================================================



#if	defined(USE_UART)
#define DBGprintf(_x_)		printf(_x_)
#define DBGputchar(_x_)		putchar(_x_)
#define DBGputs(_x_)		puts(_x_)
#define	DBGputss(_x_)		putss(_x_)
#else
#define DBGprintf(_x_)	
#define DBGputchar(_x_)		
#define DBGputs(_x_)
#define	DBGputss(_x_)
#endif

#ifdef USE_TTXIIC
#define BTC_START_I2C(_x_) 			TTX_START_I2C(_x_)
#define BTC_WriteData(_x_)			TTX_WriteData(_x_)
#define BTC_STOP_I2C(_x_)			TTX_STOP_I2C(_x_)
#define BTC_ReadDataNAK(_x_)		TTX_ReadDataNAK(_x_)
#define BTC_ReadDataACK(_x_)		TTX_ReadDataACK(_x_)
#else
#define BTC_START_I2C(_x_) 			START_I2C(_x_)
#define BTC_WriteData(_x_ )			WriteData(_x_)
#define BTC_STOP_I2C(_x_)			STOP_I2C(_x_)
#define BTC_ReadDataNAK(_x_)		ReadDataNAK(_x_)
#define BTC_ReadDataACK(_x_)		ReadDataACK(_x_)
#endif

/////////////////////////////////////////////////
//	KEY Define
/////////////////////////////////////////////////
#define	MenuKey		1
#define	SelKey		2
#define	DownKey		3
#define	UpKey		4
#define	LeftKey		5
#define	RightKey	6
#define	AutoKey		7
#define	PowerKey	8
#if defined (BtcBoard_Option)	
#define	TVpipKey	9
#define  OSD_ADD	10
#endif


#define	ChannelDown	DownKey
#define	ChannelUp	UpKey
#define	VolumeDown	LeftKey
#define	VolumeUp	RightKey

/////////////////////////////////////////////////
//	KEY ADC Value Define
/////////////////////////////////////////////////
#define	ADC0	10
#define	ADC1	20
#define	ADC2	30
#define	ADC3	40

// MTS OPTION smpark  20030818
#define MTS_NONE			0x00

#define MTS_STEREO_ON	0x01
#define MTS_STEREO_OFF	0x02

#define MTS_LANG_A		0x03
#define MTS_LANG_B		0x04
#define MTS_LANG_AB		0x05

#endif // _NFREN_TOPHEADER_