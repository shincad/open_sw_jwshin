#ifndef	_RAM_H_
#define _RAM_H_

#include "mydef.h"
#include "panel.H"

extern idata unsigned short	usTimer1_1ms;
extern idata unsigned char	ucTimer10ms;
extern idata unsigned short	usPoSvTimer;
extern idata unsigned char	ucLoopTimer_10ms;
extern idata unsigned char	ucSyncStableTimer_10ms;
extern idata unsigned short	usWarningMsgTimer_1s;
extern idata unsigned short	usOSDTimer_10ms;
//------------ +jwshin 120302
extern idata unsigned short usOSD2Timer_10ms;
//-------------------------------------
extern idata unsigned char ucSyncSourceTimer;
extern idata unsigned char	ucTimer1000ms;
extern idata unsigned short	usPOTTimerS_900;
extern idata unsigned char	ucPOTTimerM_4;
extern idata unsigned long	ulPOTTimerH;
extern idata unsigned char ucTime2Backlight;
extern idata unsigned char ucOutOfRangeTimer;
extern idata unsigned char ucLEDTimer_10ms;
extern idata unsigned char ucBestMesgTimer;
extern bit bWillShowBestMesg;
extern bit bSetGreenPower;
extern idata unsigned char ucPurelyBlackCounter;

extern idata unsigned char ucNoSigTimer;							// +jwshin 111213

extern bit bB_Screen_ReverseFlag;											// +jwshin 120224
extern bit bCopy_Flag;																// +jwshin 120224
extern bit bRGB_SW_Flag;															// +jwshin 120224

//#define OUTRRANGETimer usPoSvTimer


extern idata unsigned short	usHSync;
extern idata unsigned short	usVSync;
extern idata unsigned short	usTmpHSync;
extern idata unsigned short	usTmpVSync;
extern idata unsigned char	ucHVPolarity;
extern idata unsigned char	ucTmpHVPol;

extern idata unsigned short usVTotal;
extern idata unsigned short usActiveH;

//extern idata unsigned char	ucPowerStatus_old;
extern idata unsigned char	ucPowerStatus;
	#define DSUB_Input	0x80
	#define DVI_Input	0x81
	#define HDMI_Input	0x82
	#define Video_Input 0x83

	#define SoftPowerOnFlag		 	BIT_7
 	#define InputSourceDVI		 	BIT_0
 	#define InputSourceHDMI		 	BIT_1
#define POWER_DIGITAL	((ucPowerStatus & BIT_0) != 0 )

extern idata unsigned char 	ucSource;
extern idata unsigned char	ucModeNumber;
extern idata unsigned char	ucSignalType;
	#define sigSEP 	0
	#define sigCOMP	1
	#define sigSOG	2
	#define sigDVI	3

extern idata unsigned char ucCurrentDVIClk;
extern idata unsigned long ulDispHfreq;
extern idata unsigned long ulDotClk;
extern idata unsigned long ulHfreqCounter;
extern idata unsigned char ucResolution;

extern idata unsigned char	ucCurKey;
extern idata unsigned char	ucPrevKey;
extern idata unsigned char	ucTime2RepeatKey;
extern xdata unsigned char RepeatCounter;
extern xdata unsigned char KeyTemp1,KeyTemp2;

extern idata bit NoSigTogg;						// +jwshin 111213

extern idata bit bPowerSaveFlag;			// +jwshin 120228

extern idata bit bInSync;
extern idata bit bBGMode;
extern idata bit bKeyChanged;
extern idata bit bVideoMuted;
extern idata bit bModeChanged;
extern idata bit bForceToSleep;
extern idata bit bExitSysLoop;
            
extern idata bit bOptAbort;
extern idata bit bOutOfLimit;
extern idata bit bShowNoSync;
extern idata bit bShowDiscon;
extern idata bit bShowOutRange;
extern idata bit bShowOutRange85;
extern idata bit bShowNoInput;
extern idata bit bShowAging;
extern idata bit bSwitchSource;
extern idata bit bDDCUpdate;

//extern idata bit bIsNewMode; 		
extern idata bit bIsLEDFlashing;
extern idata bit bGLEDState;
//extern idata bit bLFLEDState;
//extern idata bit bIsLFLEDFlashing;

extern idata bit bFactoryMode;
extern idata bit bOutOfRange;
extern idata bit bStatusReport;
extern idata bit bPOTUpdate;   
extern idata bit bPowerKeyFlag;
extern idata bit bIsInterlaced;
extern idata bit bDDCCmdUpdate;

extern idata bit bSyncFlag;      	
extern idata bit bIsFRCMode;     	
extern idata bit bIsNonFullScreen;
extern idata bit bIsBurnInEnabled; 
extern idata bit bIsSyncConfirmed;
extern idata bit bIsDDCCiSupported;



extern idata bit bFactoryModeType;
	#define FACTORY_DDCCI	0
  	#define FACTORY_4BYTE	1

extern idata bit bDDC_Ci_Channel;
//extern idata bit bOSDReady;
//extern idata bit bOSDInfoChange;		// write Resolution info. when modechange
extern idata bit bDCReset;			// when NoSync and DC Reset => NoVideo
extern idata bit bAC1stOn;
#ifdef MODE_OFFSET
extern idata bit bOffsetDown;
#endif

#if PanelID == CMO_M190E5_L0E  //neo 060811
extern idata bit bScalerOutput;
#endif


extern xdata unsigned char	ucLanguage;



extern xdata unsigned char	ucBrightness;
extern xdata unsigned char	ucContrast;
extern xdata unsigned char	ucMaxBrightness;
extern xdata unsigned char	ucMinBrightness;
extern xdata unsigned char	ucMaxContrast;
extern xdata unsigned char	ucMidContrast;
extern xdata unsigned char	ucMinContrast;
	#define MAX_BRIGHTNESS	100 //255
	#define MIN_BRIGHTNESS	0	//75
	#define MAX_CONTRAST 	100	//150
	#define MID_CONTRAST 	50	//128
	#define MIN_CONTRAST 	0	//78

extern xdata unsigned char   ucPanelIDX;

extern xdata unsigned char ucBrightnessUser;
extern xdata unsigned char ucContrastUser;
extern xdata unsigned char ucBrightnesssRGB;
extern xdata unsigned char ucContrastsRGB;

extern xdata unsigned char	ucR_Gain;
extern xdata unsigned char	ucG_Gain;
extern xdata unsigned char	ucB_Gain;
extern xdata unsigned char ucR_Gain9300K;
extern xdata unsigned char ucG_Gain9300K;
extern xdata unsigned char ucB_Gain9300K;
extern xdata unsigned char ucR_Gain6500K;
extern xdata unsigned char ucG_Gain6500K;
extern xdata unsigned char ucB_Gain6500K;
extern xdata unsigned char ucR_GainsRGB;
extern xdata unsigned char ucG_GainsRGB;
extern xdata unsigned char ucB_GainsRGB;
extern xdata unsigned char ucR_GainUser;
extern xdata unsigned char ucG_GainUser;
extern xdata unsigned char ucB_GainUser;
extern xdata unsigned char ucR_Gain5000K;
extern xdata unsigned char ucG_Gain5000K;
extern xdata unsigned char ucB_Gain5000K;
extern xdata unsigned char ucR_Gain7500K;
extern xdata unsigned char ucG_Gain7500K;
extern xdata unsigned char ucB_Gain7500K;
extern xdata unsigned char ucR_Gain8200K;
extern xdata unsigned char ucG_Gain8200K;
extern xdata unsigned char ucB_Gain8200K;
extern xdata unsigned char ucR_Gain11500K;
extern xdata unsigned char ucG_Gain11500K;
extern xdata unsigned char ucB_Gain11500K;
#define MinColorGain	0
#define MaxColorGain	255

#define USERGAIN_R100	(((unsigned short)ucR_GainUser * 100  + 128) / 255)
#define USERGAIN_G100	(((unsigned short)ucG_GainUser * 100  + 128) / 255)
#define USERGAIN_B100	(((unsigned short)ucB_GainUser * 100  + 128) / 255)

extern xdata unsigned char	ucR_ADC_Gain;
extern xdata unsigned char	ucG_ADC_Gain;
extern xdata unsigned char	ucB_ADC_Gain;
extern xdata unsigned char ucR_ADC_Offset;
extern xdata unsigned char ucG_ADC_Offset;
extern xdata unsigned char ucB_ADC_Offset;
extern xdata unsigned char ucBlackLevel;
	#define MAX_BLACKLEVEL	255
	#define MIN_BLACKLEVEL	0
extern xdata unsigned char ucBkOffset[3];
	#define RGB_OFFSET_MIN   92
	#define RGB_OFFSET_MAX  164
	#define RGB_OFFSET_SCOPE 72  //(RGB_OFFSET_MAX-RGB_OFFSET_MIN)
	
enum _SaveItem_ {
			svNONE,
			svBRIGHTNESS,
			svPANELIDX,		// jerry
			svCONTRAST,
			svCLOCK,
			svPHASE,
			svHPOS,
			svVPOS,	
			svRED,
			svGREEN,
			svBLUE,
			svVOLUME,
			svOSDX,
			svOSDY,
			svBRIGHTNESS_F,
			svCONTRAST_F,
			svLANGUAGE,
			svMUTE,
			svSTANDALONE, 
			svCOLOR,
			svSMARTBRIGHT,
			svTRANSPARENCY,
			svOSDLOCK,
			svOSDTIMEOUT,
			svSOURCE,
			svSATURATION,
			svTINT,
			svDYBK
		};
extern xdata enum _SaveItem_	ucSavePointer;
	

extern xdata unsigned char	ucOSDXPos;
extern xdata unsigned char	ucOSDYPos;
extern xdata unsigned char ucTransparency;
extern idata unsigned char ucOSDTimer;
extern idata bit bIsOSDLocked;
//extern idata bit bIsSWLocked;
extern idata bit bResolutionNot;
extern idata bit bSmartResponse;
extern idata bit bSmartContrast;
extern idata bit PixelOrbit;
extern xdata unsigned char ucSizeType;

extern xdata unsigned char	ucADCPhase;
extern xdata unsigned char ucADCCPhase100Pa;
extern xdata unsigned short usHTotal;
extern xdata unsigned short usMinClk;
extern xdata unsigned short usMaxClk;
extern xdata unsigned short	usHPStart;
extern xdata unsigned short usMaxHP;
extern xdata unsigned char	ucMinHP;
//extern xdata unsigned short usReferenceHP; // For 50% HP // Jude 03/15/2005
extern xdata unsigned short	usVPStart;
extern xdata unsigned char	ucMinVP;
extern xdata unsigned char	ucMaxVP;
extern xdata unsigned char ucVPOffset;
extern xdata unsigned short usPanelVBackPorch;

#define TRANSPARENCY100 ((unsigned short)ucTransparency*100/4)
//#define OSDTIMEOUT100	((unsigned short)((ucOSDTimer>>3)&0x07)*100/3)	//ucOSDTimer=5,10,20,60 ->0,1,2,3,
#define ADC_PHASE100		(((unsigned short)ucADCPhase * 100 + 32) / 63)
#define ADC_CLOCK100		((unsigned short)(usHTotal - usMinClk) * 100 / (usMaxClk - usMinClk))
#define ADC_HP100		((unsigned short)(usMaxHP-usHPStart) * 100 / (usMaxHP - ucMinHP))	
#define ADC_VP100		((unsigned short)(usVPStart-ucMinVP) * 100 / (ucMaxVP-ucMinVP))



extern idata unsigned char	ucDDCCiTxChecksum;
extern idata unsigned char	ucDDCCiRxChecksum;

extern idata unsigned char	ucDDCCiTxOut;
extern idata unsigned char	ucDDCCiTxIn;
extern idata unsigned char	ucDDCCiRxIn;
extern idata unsigned char	ucDDCCiRxOut;
extern xdata unsigned char	ucDDCCiTxBuffer[];
extern xdata unsigned char	ucDDCCiRxBuffer[];


extern xdata unsigned char TempValue;
extern xdata unsigned char TempData;


extern xdata unsigned char ucBGColor;
extern xdata unsigned short usOSDMovingX;
extern xdata unsigned short usOSDMovingY;
extern idata unsigned char ucStrAlignment;
extern idata unsigned char ucStrWidth;
extern idata unsigned char ucFontLen;
extern idata unsigned short usFontIndex;
extern idata unsigned short usFontBuffer[];
extern xdata unsigned char ucOSDWidth;
extern xdata unsigned char ucOSDHeight;


extern xdata unsigned char ucColorTemperature;
	#define COLOR_5000		0
	#define COLOR_6500		1
	#define COLOR_7500		2
	#define COLOR_8200		3
	#define COLOR_9300		4
	#define COLOR_11500		5
	#define COLOR_SRGB		6
	#define COLOR_USER		7

	#define COLOR_ORIGIN	8


extern idata unsigned char ucUARTTxIn;
extern idata unsigned char ucUARTTxOut;
extern idata unsigned char ucUARTRxOut;
extern idata unsigned char ucUARTRxIn;
extern xdata unsigned char ucUARTTxBuffer[UART_TX_BUFFER_SIZE];
extern xdata unsigned char ucUARTRxBuffer[UART_RX_BUFFER_SIZE];
extern xdata unsigned char ucIsTransDisabled;
extern xdata unsigned char ucNewControlValue;


extern idata unsigned char ucRegPage;




#define SN_TOTAL_LEN	15
#define SN_LEN	13
extern xdata unsigned char ucSerialNum[SN_TOTAL_LEN];// It MUST be used with idata , NOT xdata type




extern xdata unsigned char	ucVolume;
#define MAXVOLUME	100
extern idata bit bStandalone;
extern idata bit bMute;





#define ACE_PARTITIONS 16 // 4,8,16

#define BFDYNBK_TYPE_0 0
#define BFDYNBK_TYPE_1 1
#define BFDYNBK_TYPE_2 2
#define BFDYNBK_TYPE_3 3
#define BFDYNBK_TYPE_4 4
#define BFDYNBK_TYPE_5 5

#define BF_DYNAMIC_BACKLIGHT
#define BFDYNBK_TYPE BFDYNBK_TYPE_3



// LF variables
extern xdata unsigned long  ulCurHisgrmTotal;
extern xdata unsigned long  ulCurHisgrm[ACE_PARTITIONS];

extern xdata unsigned char ucLFMode;
extern xdata unsigned char ucPrevLFMode;
extern xdata unsigned char ucIsLFDemoMode;
extern xdata unsigned char ucLFLuminance;
extern xdata unsigned char ucLFContrast;
extern xdata unsigned char ucLFColor;
extern xdata unsigned char ucLFHue;
extern xdata unsigned char ucLFSharpness;
extern xdata unsigned char ucLFCusACCMode;
extern xdata unsigned char ucLFYPeakEN;
extern xdata unsigned char *pLFCurAdj;
extern xdata unsigned char ucLFMaxAdj;
extern xdata unsigned char ucLFMinAdj;

extern xdata unsigned char ucBFColorMode;
extern xdata unsigned char ucBFFTMore;
extern xdata unsigned char ucBFGreenMore;
extern xdata unsigned char ucBFBlueMore;

// BF
extern xdata unsigned char ucBFMode;
//extern xdata unsigned char ucIsBF;
extern idata unsigned short usBFTimer_10ms;
extern idata unsigned short usBF_HIS_Timer1_10ms;
extern idata unsigned short usBF_HIS_Timer2_10ms;
extern idata unsigned short usBF_DYMBK_Timer_10ms;

extern xdata unsigned char ucBFWSize;
#ifndef BF_MOVING_WINDOW
extern idata unsigned char ucLFDemoTimer;
#endif
extern xdata unsigned char ucDynBKMode;
extern xdata int iCurDynBk;
extern xdata unsigned char ucNewDynBk;

#ifdef BF_MOVING_WINDOW
extern xdata unsigned short usBFMovingWidth;
extern idata bit bBFMovingDir;
extern xdata unsigned char ucBFMovingTimer;
#endif



#ifdef ANTI_ESD
extern idata unsigned char ucESDSaveD1;
extern idata unsigned char ucESDSaveD2;
extern idata unsigned char ucESDSaveD3;
extern idata unsigned char ucESDSaveD4;
extern idata unsigned char ucESDSaveF1;

#endif






//extern xdata unsigned char wflag;

extern idata bit bAutoClockResult;
extern xdata unsigned char mode_k;
extern xdata float maxPhase,temp_phase;
extern idata unsigned char ucBF_Status;



//	THEFT DETERRENCE
extern xdata unsigned char ucTD_ACMode;
extern xdata unsigned char ucTD_Timeout;
extern xdata unsigned short usTD_PinCodeL;
extern xdata unsigned short usTD_PinCodeH;
extern xdata unsigned char ucTD_State;
#define TD_NORMAL 0
#define TD_POSSIBLE_THEFT 1
#define TD_THEFT 2
#define TD_LOG_TIMEOUT 4
extern xdata unsigned char ucTD_TimeoutS;
extern idata bit bShowTheftOSD;
extern xdata unsigned char ucTD_PinFailedCount;
extern xdata unsigned char ucTD_PinFailedTimer;


extern xdata unsigned char ucRGB_OFFSET;
extern xdata unsigned char ucBrightnessLevel;
extern xdata unsigned char ucSaturation;
extern xdata unsigned char ucTint;
#if FE2P_LIB==ON
//Fe2p 2006/10/31 Alvin
extern idata bit feSave;
extern xdata unsigned char feValid_Block;
extern xdata unsigned short feSave_Timer;
extern xdata unsigned char Fe2pBuf[2048];
#define Fe2pBufAddr 0x9000
#endif

#endif
