#include "RAM.H"

idata unsigned short usTimer1_1ms;
idata unsigned char	ucTimer10ms;
idata unsigned short usPoSvTimer;
idata unsigned char ucLoopTimer_10ms;
idata unsigned char ucSyncStableTimer_10ms;
idata unsigned short usWarningMsgTimer_1s;
idata unsigned short usOSDTimer_10ms;
idata unsigned short usOSD2Timer_10ms;			// +jwshin 120302
idata unsigned char	ucSyncSourceTimer;
idata unsigned char	ucTimer1000ms;
idata unsigned short	usPOTTimerS_900;
idata unsigned char	ucPOTTimerM_4;
idata unsigned long ulPOTTimerH;
idata unsigned char ucTime2Backlight;
idata unsigned char ucOutOfRangeTimer;
idata unsigned char ucLEDTimer_10ms;
idata unsigned char ucBestMesgTimer;
bit bWillShowBestMesg;
bit bSetGreenPower;
idata unsigned char ucPurelyBlackCounter;

idata unsigned char ucNoSigTimer;							// +jwshin 111213

idata unsigned short usHSync;
idata unsigned short usVSync;
idata unsigned short usTmpHSync;
idata unsigned short usTmpVSync;
idata unsigned char ucHVPolarity;	
idata unsigned char ucTmpHVPol;

idata unsigned short usVTotal;
idata unsigned short usActiveH;


//idata unsigned char	ucPowerStatus_old;
idata unsigned char	ucPowerStatus;
idata unsigned char 	ucModeNumber;
idata unsigned char	ucSignalType;
idata unsigned char 	ucSource;

idata unsigned char ucCurrentDVIClk;
idata unsigned long ulDispHfreq;
idata unsigned long ulDotClk;
idata unsigned long ulHfreqCounter;
idata unsigned char ucResolution;


idata unsigned char	ucCurKey;
idata unsigned char	ucPrevKey;
idata unsigned char	ucTime2RepeatKey;
xdata unsigned char RepeatCounter;
xdata unsigned char KeyTemp1,KeyTemp2;


idata bit NoSigTogg;						// +jwshin 111213

idata bit bPowerSaveFlag;				// +jwshin 120228

idata bit bInSync;
idata bit bBGMode;
idata bit bKeyChanged;
idata bit bVideoMuted;
idata bit bModeChanged;
idata bit bForceToSleep;
idata bit bExitSysLoop;
            
idata bit bOptAbort;
idata bit bOutOfLimit;
idata bit bShowNoSync;
idata bit bShowDiscon;
idata bit bShowOutRange;
idata bit bShowOutRange85;
idata bit bShowNoInput;
idata bit bShowAging;
idata bit bSwitchSource;
idata bit bDDCUpdate;

//idata bit bIsNewMode; 		
idata bit bIsLEDFlashing;	
idata bit bGLEDState;
//idata bit bLFLEDState;
//idata bit bIsLFLEDFlashing;

idata bit bFactoryMode;
idata bit bOutOfRange;
idata bit bStatusReport;
idata bit bPOTUpdate;   
idata bit bPowerKeyFlag;
idata bit bIsInterlaced;
idata bit bDDCCmdUpdate;

idata bit bSyncFlag;      	
idata bit bIsFRCMode;     	
idata bit bIsNonFullScreen; 
idata bit bIsBurnInEnabled; 
idata bit bIsSyncConfirmed; 
idata bit bIsDDCCiSupported;



idata bit bFactoryModeType;
idata bit bDDC_Ci_Channel;

//idata bit bOSDReady;
//idata bit bOSDInfoChange;		// write Resolution info. when modechange
idata bit bDCReset;
idata bit bAC1stOn;
#ifdef MODE_OFFSET
idata bit bOffsetDown;
#endif
#if PanelID == CMO_M190E5_L0E  //neo 060811
idata bit bScalerOutput;
#endif

xdata unsigned char	ucLanguage;

#if 0
xdata unsigned char ucSharpness;
xdata unsigned char ucSaturation;
xdata unsigned char ucTint;
#endif

xdata unsigned char ucBrightness;
xdata unsigned char ucContrast;
xdata unsigned char	ucMaxBrightness;
xdata unsigned char	ucMinBrightness;
xdata unsigned char	ucMaxContrast;
xdata unsigned char	ucMidContrast;
xdata unsigned char	ucMinContrast;


xdata unsigned char ucPanelIDX;	// jerry

#if 0
xdata unsigned char ucBrightness9300K;
xdata unsigned char ucContrast9300K;
xdata unsigned char ucBrightness6500K;
xdata unsigned char ucContrast6500K;
#endif
xdata unsigned char ucBrightnessUser;
xdata unsigned char ucContrastUser;
xdata unsigned char ucBrightnesssRGB;
xdata unsigned char ucContrastsRGB;

xdata unsigned char ucR_Gain;
xdata unsigned char ucG_Gain;
xdata unsigned char ucB_Gain;
xdata unsigned char ucR_Gain9300K;
xdata unsigned char ucG_Gain9300K;
xdata unsigned char ucB_Gain9300K;
xdata unsigned char ucR_Gain6500K;
xdata unsigned char ucG_Gain6500K;
xdata unsigned char ucB_Gain6500K;
xdata unsigned char ucR_GainsRGB;
xdata unsigned char ucG_GainsRGB;
xdata unsigned char ucB_GainsRGB;
xdata unsigned char ucR_GainUser;
xdata unsigned char ucG_GainUser;
xdata unsigned char ucB_GainUser;
xdata unsigned char ucR_Gain5000K;
xdata unsigned char ucG_Gain5000K;
xdata unsigned char ucB_Gain5000K;
xdata unsigned char ucR_Gain7500K;
xdata unsigned char ucG_Gain7500K;
xdata unsigned char ucB_Gain7500K;
xdata unsigned char ucR_Gain8200K;
xdata unsigned char ucG_Gain8200K;
xdata unsigned char ucB_Gain8200K;
xdata unsigned char ucR_Gain11500K;
xdata unsigned char ucG_Gain11500K;
xdata unsigned char ucB_Gain11500K;

xdata unsigned char ucR_ADC_Gain;
xdata unsigned char ucG_ADC_Gain;
xdata unsigned char ucB_ADC_Gain;
xdata unsigned char ucR_ADC_Offset;
xdata unsigned char ucG_ADC_Offset;
xdata unsigned char ucB_ADC_Offset;
xdata unsigned char ucBlackLevel;
xdata unsigned char ucBkOffset[3];



xdata enum _SaveItem_	ucSavePointer;


xdata unsigned char ucOSDXPos;
xdata unsigned char ucOSDYPos;
xdata unsigned char ucTransparency;
idata unsigned char ucOSDTimer;
idata bit bIsOSDLocked; 	
//idata bit bIsSWLocked;
idata bit bResolutionNot;
idata bit bSmartResponse;
idata bit bSmartContrast;
idata bit PixelOrbit;
xdata unsigned char ucSizeType;

xdata unsigned char ucADCPhase;
xdata unsigned char ucADCCPhase100Pa;
xdata unsigned short usHTotal;
xdata unsigned short usMinClk;
xdata unsigned short usMaxClk;
xdata unsigned short usHPStart;
xdata unsigned short usMaxHP;
xdata unsigned char ucMinHP;
//xdata unsigned short usReferenceHP; // For 50% Phase // Jude 03/15/2005
xdata unsigned short usVPStart;
xdata unsigned char ucMaxVP;
xdata unsigned char ucMinVP;
xdata unsigned char ucVPOffset;
xdata unsigned short usPanelVBackPorch;


idata unsigned char	ucDDCCiTxChecksum;
idata unsigned char	ucDDCCiRxChecksum;

idata unsigned char ucDDCCiTxOut;
idata unsigned char ucDDCCiTxIn;
idata unsigned char ucDDCCiRxIn;
idata unsigned char ucDDCCiRxOut;
xdata unsigned char	ucDDCCiTxBuffer[DDCCi_BUFFER_SIZE];
xdata unsigned char	ucDDCCiRxBuffer[DDCCi_BUFFER_SIZE];

//
xdata unsigned char TempData;
xdata unsigned char TempValue;


xdata unsigned char ucBGColor;
xdata unsigned short usOSDMovingX;
xdata unsigned short usOSDMovingY;
idata unsigned char ucStrAlignment;
idata unsigned char ucStrWidth;
idata unsigned char ucFontLen;
idata unsigned short usFontIndex;
idata unsigned short usFontBuffer[FONT_BUFFER_SIZE];
xdata unsigned char ucOSDWidth;
xdata unsigned char ucOSDHeight;



xdata unsigned char ucColorTemperature;

idata unsigned char ucUARTTxIn;
idata unsigned char ucUARTTxOut;
idata unsigned char ucUARTRxOut;
idata unsigned char ucUARTRxIn;
xdata unsigned char ucUARTTxBuffer[UART_TX_BUFFER_SIZE];
xdata unsigned char ucUARTRxBuffer[UART_RX_BUFFER_SIZE];
xdata unsigned char ucIsTransDisabled;
xdata unsigned char ucNewControlValue;


idata unsigned char ucRegPage;



xdata unsigned char ucSerialNum[SN_TOTAL_LEN];



xdata unsigned char ucVolume;
idata bit bStandalone;
idata bit bMute;



// LF


xdata unsigned long  ulCurHisgrmTotal;
xdata unsigned long  ulCurHisgrm[ACE_PARTITIONS];

xdata unsigned char ucLFMode;
xdata unsigned char ucPrevLFMode;
xdata unsigned char ucIsLFDemoMode;
xdata unsigned char ucLFLuminance;
xdata unsigned char ucLFContrast;
xdata unsigned char ucLFColor;
xdata unsigned char ucLFHue;
xdata unsigned char ucLFSharpness;
xdata unsigned char ucLFCusACCMode;
xdata unsigned char ucLFYPeakEN;
xdata unsigned char *pLFCurAdj;
xdata unsigned char ucLFMaxAdj;
xdata unsigned char ucLFMinAdj;

xdata unsigned char ucBFColorMode;
xdata unsigned char ucBFFTMore;
xdata unsigned char ucBFGreenMore;
xdata unsigned char ucBFBlueMore;

// BF
xdata unsigned char ucBFMode;
//xdata unsigned char ucIsBF;
idata unsigned short usBFTimer_10ms;
idata unsigned short usBF_HIS_Timer1_10ms;
idata unsigned short usBF_HIS_Timer2_10ms;
idata unsigned short usBF_DYMBK_Timer_10ms;

xdata unsigned char ucBFWSize;
#ifndef BF_MOVING_WINDOW
idata unsigned char ucLFDemoTimer;
#endif
xdata unsigned char ucDynBKMode;
xdata int iCurDynBk;
xdata unsigned char ucNewDynBk;

#ifdef BF_MOVING_WINDOW
xdata unsigned short usBFMovingWidth;
idata bit bBFMovingDir;
xdata unsigned char ucBFMovingTimer;
#endif



#ifdef ANTI_ESD
idata unsigned char ucESDSaveD1;
idata unsigned char ucESDSaveD2;
idata unsigned char ucESDSaveD3;
idata unsigned char ucESDSaveD4;

idata unsigned char ucESDSaveF1;
#endif



//xdata unsigned char wflag;

idata bit bAutoClockResult;
xdata unsigned char mode_k;
xdata float maxPhase,temp_phase;
idata unsigned char ucBF_Status;



//	THEFT DETERRENCE
xdata unsigned char ucTD_ACMode;
xdata unsigned char ucTD_Timeout;
xdata unsigned short usTD_PinCodeL;
xdata unsigned short usTD_PinCodeH;
xdata unsigned char ucTD_State;
xdata unsigned char ucTD_TimeoutS;
idata bit bShowTheftOSD;
xdata unsigned char ucTD_PinFailedCount;
xdata unsigned char ucTD_PinFailedTimer;



xdata unsigned char ucRGB_OFFSET;
xdata unsigned char ucBrightnessLevel;
xdata unsigned char ucSaturation;
xdata unsigned char ucTint;
#if FE2P_LIB==ON
//Fe2p 2006/10/31 Alvin
idata bit feSave;
xdata unsigned char feValid_Block;
xdata unsigned short feSave_Timer;
xdata unsigned char Fe2pBuf[2048] _at_ Fe2pBufAddr;
#endif

