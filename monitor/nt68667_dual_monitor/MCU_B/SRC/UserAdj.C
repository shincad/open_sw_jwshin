#include "NT686xx_MCU_REG.H"
#include "NT686xx_SC_REG.H"
#include "UserAdj.H"
#include "RAM.H"
#include "IIC.H"
#include "MyDef.H"
#include "Scaler.H"
#include "NVRAM.H"
#include "Rom_map.H"
#include "OSD.H"
#include "MCU.H"
#include "OSD_TAB.H"	// LANG_NUM
#include "sRGB.H"
#include "AutoAdj.H"
//#include "stdio.H"
#include "ModeHandle.H"
#include "Panel.H"
#include "board.H"
#include "SmartBright.H"
#include "BFControl.H"
#include "HDCP.H"
#include "MIs.H"


void BrightnessUp(void)
{
	CheckColorTemperature();
	if(++ucBrightness > 100)
		ucBrightness = 100;
	else{
		SetBrightness();
		ShowBrightness();
		ucSavePointer = svBRIGHTNESS;
		ucDynBKMode = OFF;
	}
}

void BrightnessDown(void)
{
	CheckColorTemperature();
	if(--ucBrightness == 0xff)
		ucBrightness = 0x00;
	else{
		SetBrightness();
		ShowBrightness();
		ucSavePointer = svBRIGHTNESS;
		ucDynBKMode = OFF;
	}
}


#if _SmartBright_ == ON
void SetBrightOffset(void)
{
	if(ucBrightness > ucSmartBrightValue)
//		if ( (ucBrightness - ucSmartBrightValue) < (usBrightOffset-100) )
			usBrightOffset = 100 + (ucBrightness - ucSmartBrightValue);
	else
//		if ( (ucSmartBrightValue-ucBrightness) > (100-usBrightOffset) )
			usBrightOffset = 100 - (ucSmartBrightValue - ucBrightness);
//	printf("usBrightOffset x= %d\r\n",(unsigned short)usBrightOffset);
}
#endif

void ContrastUp(void)
{
	if(++ucContrast > 100)
		ucContrast = 100;
	else{
		SetContrastRGB();
		ShowContrast();
		ucSavePointer = svCONTRAST;
	}
}

void ContrastDown(void)
{
	if(--ucContrast == 0xff)
		ucContrast = 0x00;
	else{
		SetContrastRGB();
		ShowContrast();
		ucSavePointer = svCONTRAST;
	}
}

void SaturationUp(void)
{
	if(++ucSaturation > 100)
		ucSaturation = 100;
	else{
		SetContrastRGB();
		ShowSaturation();
		ucSavePointer = svSATURATION;
	}
}

void SaturationDown(void)
{
	if(--ucSaturation == 0xff)
		ucSaturation = 0x00;
	else{
		SetContrastRGB();
		ShowSaturation();
		ucSavePointer = svSATURATION;
	}
}

void TintUp(void)
{
	if(++ucTint > 100)
		ucTint = 100;
	else{
		SetContrastRGB();
		ShowTint();
		ucSavePointer = svTINT;
	}
}

void TintDown(void)
{
	if(--ucTint == 0xff)
		ucTint = 0x00;
	else{
		SetContrastRGB();
		ShowTint();
		ucSavePointer = svTINT;
	}
}









void ClockUp(void)
{
	if(++usHTotal > usMaxClk)
		usHTotal = usMaxClk;
	else{
		SetADC_PLL();
		ShowClock();
		ucSavePointer = svCLOCK;

	}
}

void ClockDown(void)
{
	if(--usHTotal < usMinClk)
		usHTotal = usMinClk;
	else{
		SetADC_PLL();
		ShowClock();
		ucSavePointer = svCLOCK;
	}
}

void PhaseUp(void)
{
	if(++ucADCPhase > 0x3f)
		ucADCPhase = 0x3f;
	else{
		SetADC_Phase();
		ShowPhase();
		ucSavePointer = svPHASE;
	}
}

void PhaseDown(void)
{
	if(--ucADCPhase == 0xff)
		ucADCPhase = 0x00;
	else{
		SetADC_Phase();
		ShowPhase();
		ucSavePointer = svPHASE;
	}
}

void HP_Up(void)
{
	if(++usHPStart > usMaxHP){
		usHPStart = usMaxHP;
	}
	else{
		SetHP();
		ShowHP();
		ucSavePointer = svHPOS;
	}
}

void HP_Down(void)
{
	usHPStart--;
	if((usHPStart < ucMinHP) || (usHPStart == 0xffff) ) {
		usHPStart = ucMinHP;
	}
	else{
		SetHP();
		ShowHP();
		ucSavePointer = svHPOS;
	}
}

void VP_Up(void)
{
	if(++usVPStart > ucMaxVP)
		usVPStart = ucMaxVP;
	else{
		SetVP();
		ShowVP();
		ucSavePointer = svVPOS;
	}
}

void VP_Down(void)
{
	usVPStart--;
	if((usVPStart == 0xffff)||(usVPStart < ucMinVP))
		usVPStart = ucMinVP;
	else{
		SetVP();
		ShowVP();
		ucSavePointer = svVPOS;
	}
}

void ClearNewMode()
{
code unsigned char initTab[]={
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
};
unsigned char i;
	//WRITE NEW MODE
	for (i=0;i<0x80;i+=16)
	{
		WritePage24C16(NVRAM_SYNC(0)+i,0,initTab,16);
	}
}

void FactoryReset()
{
//	unsigned char i;
	
	//LED_GrnOff();
	//LED_RedOn();
	bIsBurnInEnabled = FALSE;
	Write24C16(EPADDR_BURNIN, bIsBurnInEnabled);	//0x14 = Burn-in mode			
//	Write24C16(EPADDR_FACTORY, 0 );
	
	RecallPOT();
	
	ucBrightness = MCU_DataMap[EPADDR_BRIGHT_FACTORY];	//0x08 = brightness
	ucSavePointer = svBRIGHTNESS_F;
	SaveData();	
	
//	ucContrast = MCU_DataMap[EPADDR_CONTRAST_FACTORY];		//0x09 = contrast
//	ucSavePointer = svCONTRAST_F;
//	SaveData();
	
	ucColorTemperature = COLOR_6500;
	Write24C16(EPADDR_COLOR_TEMP, ucColorTemperature);
	SetColorTemp(ucColorTemperature);
		
	//WRITE NEW MODE
	//for (i=0;i<0x80;i+=16)
	//{
	//	WritePage24C16(NVRAM_SYNC(0)+i,0,initTab,16);
	//}
	ClearNewMode();
	
	//write factory mode in user area
	//for(i=0; i<NUMBER_OF_USER_MODE; i++){
	//		InitModeData(i);
	//}
	InitModeData16();
	Write24C16(EPADDR_USERSTART, MCU_DataMap[EPADDR_USERSTART]);

#ifdef DEMO_HDCP_KEY
	InitHDCP_DemoKey();
#endif
//	LED_GrnOn();
//	LED_RedOff();
		
	if ( ucLanguage != MCU_DataMap[EPADDR_OSDLANG] )
	{
		ucLanguage = MCU_DataMap[EPADDR_OSDLANG];
		Write24C16(EPADDR_OSDLANG,ucLanguage);

	}
}

void Recall(void)
	{
#if _SmartBright_ == ON
	bSmartBrightEnable = OFF;
	Write24C16(EPADDR_SMARTBRIGHT,bSmartBrightEnable);//0x2d = SmartBright
	
	ucBrightValue = 0xff;
#endif

	ucLFMode=LF_MODE_OFF;	// FOR RESET BrightnessUser
	ucBrightness = Read24C16(EPADDR_BRIGHT_FACTORY);	//0x08 = brightness
	ucSavePointer = svBRIGHTNESS;
	SaveData();
	
	ucContrast = Read24C16(EPADDR_CONTRAST_FACTORY);		//0x09 = contrast
	ucSavePointer = svCONTRAST;
	SaveData();
	//Recall6500(1);
	ucColorTemperature = COLOR_6500;
	Write24C16(EPADDR_COLOR_TEMP, ucColorTemperature);
	//SetColorTemp(ucColorTemperature);
	

#ifdef BF_DYNAMIC_BACKLIGHT
	ucDynBKMode = MCU_DataMap[EPADDR_DYNAMIC_BKMODE];
	Write24C16(EPADDR_DYNAMIC_BKMODE,ucDynBKMode);
	ucSavePointer = svDYBK;
	SaveData();
#endif

	ucLFMode = MCU_DataMap[EPADDR_DVI_LF_MODE];
	Write24C16(EPADDR_DVI_LF_MODE, ucLFMode);
	ucLFMode = MCU_DataMap[EPADDR_DSUB_LF_MODE];
	Write24C16(EPADDR_DSUB_LF_MODE, ucLFMode);
	if (POWER_DIGITAL)
		ucLFMode = Read24C16(EPADDR_DVI_LF_MODE);
	else
		ucLFMode = Read24C16(EPADDR_DSUB_LF_MODE);
	
	LFEnableSettings();			

	SetOSDAtCenter();

	ucR_GainUser = MCU_DataMap[EPADDR_RGAIN_USER];
	ucG_GainUser = MCU_DataMap[EPADDR_GGAIN_USER];
	ucB_GainUser = MCU_DataMap[EPADDR_BGAIN_USER];
	Write24C16(EPADDR_RGAIN_USER, ucR_GainUser);
	Write24C16(EPADDR_GGAIN_USER, ucG_GainUser);
	Write24C16(EPADDR_BGAIN_USER, ucB_GainUser);
		
	bStandalone = MCU_DataMap[EPADDR_STANDALONE];
	Write24C16(EPADDR_STANDALONE, (unsigned char)bStandalone);
	
	bMute = MCU_DataMap[EPADDR_MUTE];
	Write24C16(EPADDR_MUTE, (unsigned char)bMute);
	
	ucVolume = MCU_DataMap[EPADDR_VOLUME];		//0x0c = volume
	Write24C16(EPADDR_VOLUME, ucVolume);	//0x0c = volume
	SetVolume();


	ucTransparency = MCU_DataMap[EPADDR_TRANSPARENCY];
	Write24C16(EPADDR_TRANSPARENCY,ucTransparency);
	ucOSDTimer = MCU_DataMap[EPADDR_OSDTIMER];
	Set_usOSDTimer_10ms((unsigned short)ucOSDTimer*100);
	Write24C16(EPADDR_OSDTIMER,ucOSDTimer);
	ucSource = MCU_DataMap[EPADDR_INPUT_SRC];
	Write24C16(EPADDR_INPUT_SRC,ucSource);
	bResolutionNot = MCU_DataMap[EPADDR_RSO_NOTF];
	Write24C16(EPADDR_RSO_NOTF,bResolutionNot);

	bIsBurnInEnabled = FALSE;
	Write24C16(EPADDR_BURNIN, bIsBurnInEnabled);	//0x14 = Burn-in mode	
#ifdef DEMO_HDCP_KEY
		InitHDCP_DemoKey();
#endif
	
//	ClearAutoAdjTag();
	
	//-------------- RGB Mode 인 경우, 자동설정까지 해줄 것~!
	if(ucSignalType != sigDVI){
		if((bFactoryMode == FALSE)&&(bIsBurnInEnabled == FALSE)){
			if(ucOSDType != FACTORY){
				ShowAutoAdj();
			}
			AutoTune();
		}
	}
	//---------------- 자동 설정 후, OSD 깨짐 증상을 방지하기 위해, OSD Off Function Call~!
	OSD_OFF();				// +jwshin 111213
	
	
}
void OSD_X_Up(void)
{
	if(++ucOSDXPos > 100)
		ucOSDXPos = 100;
	else{
		SetPosition(ucOSDXPos,ucOSDYPos);
		ShowOSD_X();
		ucSavePointer = svOSDX;
	}
}

void OSD_X_Down(void)
{
	if(--ucOSDXPos > 100)
		ucOSDXPos = 0;
	else{
		SetPosition(ucOSDXPos,ucOSDYPos);
		ShowOSD_X();
		ucSavePointer = svOSDX;
	}
}

void OSD_Y_Up(void)
{
	if(++ucOSDYPos > 100)
		ucOSDYPos = 100;
	else{
		SetPosition(ucOSDXPos,ucOSDYPos);
		ShowOSD_Y();
		ucSavePointer = svOSDY;
	}
}

void OSD_Y_Down(void)
{
	if(--ucOSDYPos > 100)
		ucOSDYPos = 0;
	else{
		SetPosition(ucOSDXPos,ucOSDYPos);
		ShowOSD_Y();
		ucSavePointer = svOSDY;
	}
}

void TransparencyUp()
{
	if(++ucTransparency > 4)
		ucTransparency = 4;
	else{
		SetTransparency();
		ShowTransparency();
		ucSavePointer = svTRANSPARENCY;
	}
}

void TransparencyDown()
{
	if(--ucTransparency > 4)
		ucTransparency = 0;
	else{
		SetTransparency();
		ShowTransparency();
		ucSavePointer = svTRANSPARENCY;
	}
}

void SetTransparency()
{
	if(ucTransparency > 0){
		WriteIIC560(OSD_TRANSLUCENT_CTL, ((ucTransparency-1)<<3)|( ucTransparency-1) );	//(ucTransparency-1)*2
		WriteIIC560(OSD_CODE_FC_CTL,0x30);
	}
	else
		WriteIIC560(OSD_CODE_FC_CTL,0x00);
}

void OSD_TimerUp(void)
{
	if(++ucOSDTimer > 60)
		ucOSDTimer = 60;
	else{
		ShowOSD_Timer();
		Set_usOSDTimer_10ms((unsigned short)ucOSDTimer*100);
		ucSavePointer = svOSDTIMEOUT;
	}	
}

void OSD_TimerDown(void)
{
	if(--ucOSDTimer < 5)
		ucOSDTimer = 5;
	else{
		ShowOSD_Timer();
		Set_usOSDTimer_10ms((unsigned short)ucOSDTimer*100);
		ucSavePointer = svOSDTIMEOUT;
	}
}


void LanguageUp(void)
{
	if(++ucLanguage > mCHINESE_S)
		ucLanguage = mENGLISH;
	SelectLanguage();
	ucSavePointer = svLANGUAGE;
}

void LanguageDown(void)
{
	if(--ucLanguage > mCHINESE_S)
		ucLanguage = mCHINESE_S;
	SelectLanguage();
	ucSavePointer = svLANGUAGE;
}

void InputSourceUp(void)
{
	if(++ucSource > mSource_VIDEO)
		ucSource = mSource_VGA;
	SelectInput();
	ucSavePointer = svSOURCE;
}

void InputSourceDown(void)
{
	if(--ucSource > mSource_VIDEO)
		ucSource = mSource_VIDEO;
	SelectInput();
	ucSavePointer = svSOURCE;
}

void DirectVolumeUp(void)
{
	if(++ucVolume > MAXVOLUME){
		ucVolume = MAXVOLUME;
	}
	else{
		if(bMute){
			bMute = FALSE;
			ucSavePointer = svMUTE;
			SaveData();
			WriteWordIIC560(OSD_FC_ATTR_LSB,DirectWarningColor);
			WriteXY_Line(11, 3, 8, 0x00);
		}
		SetVolume();
		ShowVolume();
		ucSavePointer = svVOLUME;
	}
}

void DirectVolumeDown(void)
{
	if(--ucVolume == 0xff){
		ucVolume = 0;
	}
	else{
		if(bMute){
			bMute = FALSE;
			ucSavePointer = svMUTE;
			SaveData();
			WriteWordIIC560(OSD_FC_ATTR_LSB,DirectWarningColor);
			WriteXY_Line(11, 3, 8, 0x00);
		}
		SetVolume();
		ShowVolume();
		ucSavePointer = svVOLUME;
	}
}


void DirectBrightnessUp(void)
{
	CheckColorTemperature();
	if(++ucBrightness > 100){
		ucBrightness = 100;
	}
	else{
		SetBrightness();
		ShowBrightness();
		ucSavePointer = svBRIGHTNESS;
		ucDynBKMode = OFF;
	}
}

void DirectBrightnessDown(void)
{
	CheckColorTemperature();
	if(--ucBrightness == 0xff){
		ucBrightness = 0;
	}
	else{
		SetBrightness();
		ShowBrightness();
		ucSavePointer = svBRIGHTNESS;
		ucDynBKMode = OFF;
	}
}

void LoadModeIndependentSettings(void)
{
	
		//---- +jwshin 120224   
		//---- CopyLED Status Check 및 Reverse Flag Check
		bCopy_Flag = Read24C16(EPADDR_COPY_FLAG);
		bB_Screen_ReverseFlag = Read24C16(EPADDR_B_SCREEN_REV);
		bRGB_SW_Flag = Read24C16(EPADDR_RGB_SW1);
	
		if((bB_Screen_ReverseFlag == 0) && (bCopy_Flag == 0) && (bRGB_SW_Flag == 0)) {
			printf("1\r\n");
			RGB_SW1_RGB2();
			COPYLED_GrnOff();
		}
		else if((bB_Screen_ReverseFlag == 0) && (bCopy_Flag == 1) && (bRGB_SW_Flag == 1)) {
			printf("4\r\n");
			RGB_SW1_RGB1();
			COPYLED_GrnOn();
		}
		else if((bB_Screen_ReverseFlag == 1) && (bCopy_Flag == 0) && (bRGB_SW_Flag == 1)) {
			printf("6\r\n");
			RGB_SW1_RGB1();
			COPYLED_GrnOff();
		}
		else if((bB_Screen_ReverseFlag == 1) && (bCopy_Flag == 1) && (bRGB_SW_Flag == 0)) {
			printf("7\r\n");
			RGB_SW1_RGB2();
			COPYLED_GrnOn();
		}
		else
		{
			printf("Exp\r\n");
			}
			
		//--------------------------------------------------		
		ucOSDXPos = Read24C16(EPADDR_OSDX);		//0x15 = OSD position x	// read at OsdInit()
		ucOSDYPos = Read24C16(EPADDR_OSDY);		//0x16 = OSD position y
		ucTransparency = Read24C16(EPADDR_TRANSPARENCY);
		ucOSDTimer = Read24C16(EPADDR_OSDTIMER);
		Set_usOSDTimer_10ms((unsigned short)ucOSDTimer*100);
		ucColorTemperature = Read24C16(EPADDR_COLOR_TEMP);
		if(!bFactoryMode && (ucColorTemperature ==   COLOR_ORIGIN)){
			ucColorTemperature = COLOR_6500;
			Write24C16(EPADDR_COLOR_TEMP, ucColorTemperature);
		}
		ucLanguage = Read24C16(EPADDR_OSDLANG);		//0x06 = OSD Language
		ucSource = Read24C16(EPADDR_INPUT_SRC);

		ucBrightnessUser = Read24C16(EPADDR_BRIGHT_USER);	//0x36 = brightness/Inverter user
		ucContrastUser = Read24C16(EPADDR_CONTRAST_USER);	//0x37 = contrast user
		ucBrightnesssRGB = Read24C16(EPADDR_BRIGHT_SRGB);	//0x3a = brightness/Inverter sRGB
		ucContrastsRGB = Read24C16(EPADDR_CONTRAST_SRGB);	//0x3b = contrast sRGB
		ucSaturation = Read24C16(EPADDR_SATURATION);
		ucTint = Read24C16(EPADDR_TINT);
	
		//LoadCurrentSettingByInput(0,1);
		ucR_Gain5000K = Read24C16(EPADDR_RGAIN_5000);
		ucG_Gain5000K = Read24C16(EPADDR_GGAIN_5000);
		ucB_Gain5000K = Read24C16(EPADDR_BGAIN_5000);
		ucR_Gain7500K = Read24C16(EPADDR_RGAIN_7500);
		ucG_Gain7500K = Read24C16(EPADDR_GGAIN_7500);
		ucB_Gain7500K = Read24C16(EPADDR_BGAIN_7500);
		ucR_Gain8200K = Read24C16(EPADDR_RGAIN_8200);
		ucG_Gain8200K = Read24C16(EPADDR_GGAIN_8200);
		ucB_Gain8200K = Read24C16(EPADDR_BGAIN_8200);
		ucR_Gain11500K = Read24C16(EPADDR_RGAIN_11500);
		ucG_Gain11500K = Read24C16(EPADDR_GGAIN_11500);
		ucB_Gain11500K = Read24C16(EPADDR_BGAIN_11500);
			
		ucR_Gain9300K = Read24C16(EPADDR_RGAIN_9300);	//0x47 = r gain 9300K
		ucG_Gain9300K = Read24C16(EPADDR_GGAIN_9300);	//0x48 = g gain 9300K
		ucB_Gain9300K = Read24C16(EPADDR_BGAIN_9300);	//0x49 = b gain 9300K
		ucR_Gain6500K = Read24C16(EPADDR_RGAIN_6500);	//0x41 = r gain 6500K
		ucG_Gain6500K = Read24C16(EPADDR_GGAIN_6500);	//0x42 = g gain 6500K
		ucB_Gain6500K = Read24C16(EPADDR_BGAIN_6500);	//0x43 = b gain 6500K
		ucR_GainsRGB = Read24C16(EPADDR_RGAIN_SRGB);	//0x44 = r gain sRGB
		ucG_GainsRGB = Read24C16(EPADDR_GGAIN_SRGB);	//0x45 = g gain sRGB
		ucB_GainsRGB = Read24C16(EPADDR_BGAIN_SRGB);	//0x46 = b gain sRGB
		ucR_GainUser = Read24C16(EPADDR_RGAIN_USER);	//0x3e = r gain user
		ucG_GainUser = Read24C16(EPADDR_GGAIN_USER);	//0x3f = g gain user
		ucB_GainUser = Read24C16(EPADDR_BGAIN_USER);	//0x40 = b gain user
		ucBkOffset[0] = Read24C16(EPADDR_RBKOFFSET);
		ucBkOffset[1] = Read24C16(EPADDR_GBKOFFSET);
		ucBkOffset[2] = Read24C16(EPADDR_BBKOFFSET);
		
		#if 0						// -jwshin 130307
		ucBlackLevel = Read24C16(EPADDR_SCALER_OFFSET); //0x17 = scaler offset	// jerry
		ucPanelIDX = Read24C16(EPADDR_IDX);
		#else
//		ucBlackLevel = DEF_BLACKLEVEL;	//20051020 Steward+		// the same from MCU_DataMap[]
		ucBlackLevel = 100;						// +jwshin 130307
		ucPanelIDX = DEF_PANELIDX;		//20051020 Steward+
		#endif
//		ucPanelID = Read24C16(EPADDR_PANELID);
		ucMaxBrightness = Read24C16(EPADDR_MAX_BRIGHT);
		ucMinBrightness = Read24C16(EPADDR_MIN_BRIGHT);
		ucMaxContrast = Read24C16(EPADDR_MAX_CONTRAST);
		ucMidContrast = Read24C16(EPADDR_MID_CONTRAST);
		ucMinContrast = Read24C16(EPADDR_MIN_CONTRAST);
		
		//bIsBurnInEnabled = Read24C16(EPADDR_BURNIN);
		bIsBurnInEnabled = 0;
		Write24C16(EPADDR_BURNIN, bIsBurnInEnabled);				
		bIsOSDLocked = Read24C16(EPADDR_OSDLOCK);
//		bIsSWLocked = Read24C16(EPADDR_SWLOCK);
		bResolutionNot = Read24C16(EPADDR_RSO_NOTF);
		
//#ifdef BF_DYNAMIC_BACKLIGHT
//		ucNewDynBk  = iCurDynBk = ucBrightnessUser;
//		ucDynBKMode = Read24C16(EPADDR_DYNAMIC_BKMODE);
//#endif
			
#if _SmartBright_ == ON
		bSmartBrightEnable = Read24C16(EPADDR_SMARTBRIGHT);//0x29 = SmartBright
//		usBrightOffset = Read24C16(EPADDR_BRIGHTOFFSET_HI);//0x2a = BrightOffset high
//		usBrightOffset <<= 8;
//		usBrightOffset += Read24C16(EPADDR_BRIGHTOFFSET_LO);//0x2b = BrightOffset low
		usBrightOffset = Read24C16(EPADDR_BRIGHTOFFSET_LO);//0x2b = BrightOffset low
#endif

		bStandalone = Read24C16(EPADDR_STANDALONE);
		bMute = Read24C16(EPADDR_MUTE);
		ucVolume = Read24C16(EPADDR_VOLUME);		//0x0c = volume

#ifdef MODE_OFFSET		
		bOffsetDown = Read24C16(EPADDR_OFFSETDOWN);
#endif
		ucRGB_OFFSET = Read24C16(EPADDR_RGB_OFFSET);

#if _SmartBright_ == ON
	
	ucSmartBrightStart = ucBrightness;
	ucSmartBrightEnd = ucBrightness;
//	temp = ucBrightness + 256;
//	ucBrightValue = temp - usBrightOffset;
//	ucSmartBrightValue = (unsigned char)((float)(ucMaxBrightness - ucMinBrightness) * (ucBrightValue - MinBrightValue) / (MaxBrightValue - MinBrightValue) + ucMinBrightness + 0.5);

	ucSmartBrightValue = ucBrightness + 100 - usBrightOffset;
	if( ucSmartBrightValue > ucMaxBrightness ){
		ucSmartBrightValue = ucMaxBrightness;
		usBrightOffset = 100 + (ucBrightness-ucSmartBrightValue);
	}
	else if(ucSmartBrightValue < ucMinBrightness ){
		ucSmartBrightValue = ucMinBrightness;
		usBrightOffset = 100 + (ucBrightness-ucSmartBrightValue);
	}

	ucBrightValue = (unsigned char)((float)(MaxBrightValue - MinBrightValue) * (ucSmartBrightValue-ucMinBrightness) / (ucMaxBrightness - ucMinBrightness) + MinBrightValue +0.5);

//printf("ucBrightValue=%d\r\n",(unsigned short)ucBrightValue);	
//printf("usBrightOffset=%d\r\n",(unsigned short)usBrightOffset);
//printf("Load:ucSmartBrightValue=%d\r\n",(unsigned short)ucSmartBrightValue);

#endif

	SetPanelIDX();
	//SetBrightness();

//	LoadCurrentSettingByInput(0,1);
//	LFLoadInitState();
	if (POWER_DIGITAL)
		ucLFMode = Read24C16(EPADDR_DVI_LF_MODE);
	else
		ucLFMode = Read24C16(EPADDR_DSUB_LF_MODE);
	//LFEnableSettings();
	LFResetData();

//	SetColorTemp(ucColorTemperature);
//printf("Load1=%d,%d,%02x\r\n",(unsigned short)ucBrightness,(unsigned short)ucContrast,(unsigned short)ucColorTemperature);	
//	SetScalerOffset();
	
}

void SetColorTemp(unsigned char color_temp)
{
unsigned char bktemp;
//printf("SetColorTemp=%x\r\n",(unsigned short)color_temp);

	switch(color_temp){
	case COLOR_ORIGIN:	//Panel Orignal Color
		ucR_Gain = 0xff;		//r Panel Orignal Color
		ucG_Gain = 0xff;		//g Panel Orignal Color
		ucB_Gain = 0xff;		//b Panel Orignal Color
		break;
	case COLOR_SRGB:	//sRGB
// Philips iLab 20060831: to make a comparison between original factory alignment and TrueColor alignment possible
// we simulate the original 6500K configuration in the sRGB mode, so by switching between the 6500K and the sRGB mode
// one can see in one monitor the difference between the two alignment methods.
		ucR_Gain = ucR_GainsRGB;	//0x44 = r gain sRGB
		ucG_Gain = ucG_GainsRGB;	//0x45 = g gain sRGB
		ucB_Gain = ucB_GainsRGB;	//0x46 = b gain sRGB
		break;
	case COLOR_USER:	//user
		ucR_Gain = ucR_GainUser;	//0x3e = r gain user
		ucG_Gain = ucG_GainUser;	//0x3f = g gain user
		ucB_Gain = ucB_GainUser;	//0x40 = b gain user
		break;
	case COLOR_6500:	//6500K
		ucR_Gain = ucR_Gain6500K;	//0x41 = r gain 6500K
		ucG_Gain = ucG_Gain6500K;	//0x42 = g gain 6500K
		ucB_Gain = ucB_Gain6500K;	//0x43 = b gain 6500K
		break;
	case COLOR_9300:	//9300K
		ucR_Gain = ucR_Gain9300K;	//0x41 = r gain 6500K
		ucG_Gain = ucG_Gain9300K;	//0x42 = g gain 6500K
		ucB_Gain = ucB_Gain9300K;	//0x43 = b gain 6500K
		break;
	case COLOR_5000:
		ucR_Gain = ucR_Gain5000K;	//0x41 = r gain 6500K
		ucG_Gain = ucG_Gain5000K;	//0x42 = g gain 6500K
		ucB_Gain = ucB_Gain5000K;	//0x43 = b gain 6500K
		break;
	case COLOR_7500:
		ucR_Gain = ucR_Gain7500K;	//0x41 = r gain 6500K
		ucG_Gain = ucG_Gain7500K;	//0x42 = g gain 6500K
		ucB_Gain = ucB_Gain7500K;	//0x43 = b gain 6500K
		break;
	case COLOR_8200:
		ucR_Gain = ucR_Gain8200K;	//0x41 = r gain 6500K
		ucG_Gain = ucG_Gain8200K;	//0x42 = g gain 6500K
		ucB_Gain = ucB_Gain8200K;	//0x43 = b gain 6500K
		break;
	case COLOR_11500:
		ucR_Gain = ucR_Gain11500K;	//0x41 = r gain 6500K
		ucG_Gain = ucG_Gain11500K;	//0x42 = g gain 6500K
		ucB_Gain = ucB_Gain11500K;	//0x43 = b gain 6500K
		break;
	}
//printf("SetFC=%d,%d,%d\r\n",(unsigned short)ucR_Gain,(unsigned short)ucG_Gain,(unsigned short)ucB_Gain);
	// 2006-12-05 +
	bktemp = ucBrightness;
	if(color_temp != COLOR_SRGB){
		ucBrightness = Read24C16(EPADDR_BRIGHT);
		ucContrast = Read24C16(EPADDR_CONTRAST);		//0x09 = contrast
	}
	else{
		ucBrightness = ucBrightnesssRGB;	//0x3a = brightness/Inverter sRGB
		ucContrast = ucContrastsRGB;		//0x3b = contrast sRGB        		
	}

//	printf("ucDynBKMode = %x\r\n",(unsigned short)ucDynBKMode);
	if((ucDynBKMode == OFF)||(bBGMode == TRUE))
		SetBrightness();	
	else
		ucBrightness = bktemp;

	SetContrastRGB();
}

void LoadModeDependentSettings(void)
{

unsigned short addr;

//printf("RAM OK\r\n");
	addr = NVRAM_HPSTART((unsigned short)ucModeNumber);
	usHPStart = Read24C16_Short(addr);
	addr = NVRAM_RESOLU((unsigned short)ucModeNumber);
	ucResolution = Read24C16(addr);
	addr = NVRAM_PHASE((unsigned short)ucModeNumber);
	ucADCPhase = Read24C16(addr);
	addr = NVRAM_HTOTAL((unsigned short)ucModeNumber);
	usHTotal = Read24C16_Short(addr);
	addr = NVRAM_VPSTART((unsigned short)ucModeNumber);
	usVPStart = Read24C16_Short(addr);
	addr = usHPStart + H_ActiveTab[ucResolution]; 
	if(usHTotal < addr)
		usHTotal = addr;
	ucVPOffset = 0;

}

void SaveModeDependentSettings(void)
{

unsigned short short_mode = (unsigned short)ucModeNumber;

	Write24C16_Short(NVRAM_HPSTART(short_mode), usHPStart);
	Write24C16(NVRAM_PHASE(short_mode), ucADCPhase);
	Write24C16_Short(NVRAM_HTOTAL(short_mode), usHTotal);
	Write24C16_Short(NVRAM_VPSTART(short_mode), usVPStart);

	Write24C16_Short(NVRAM_HTOTAL50(short_mode), usHTotal);
//	Write24C16_Short(NVRAM_HP50(short_mode), usHPStart);

//	Write24C16(NVRAM_TIMING_ALTER(ucModeNumber), 1);

}

void ColorTempUp(void)
{
	if(++ucColorTemperature > COLOR_USER){
		ucColorTemperature = COLOR_USER;
	}
	else{
		ucSavePointer = svCOLOR;
		SetColorTemp(ucColorTemperature);
		if(ucColorTemperature > 3){
			ShowColorMenu();
		}
		SelectColorTemp();
	}
}

void ColorTempDown(void)
{
	if(--ucColorTemperature > COLOR_USER){
		ucColorTemperature = COLOR_5000;
	}
	else{
		ucSavePointer = svCOLOR;
		SetColorTemp(ucColorTemperature);
		if(ucColorTemperature > 3){
			ShowColorMenu();
		}
		SelectColorTemp();
	}
}

unsigned char ScalingColorGain(unsigned char RGB_Gain)
{
	return((unsigned char)((float)(RGB_Gain - MinColorGain) * 100 / (MaxColorGain - MinColorGain) + 0.5));
}

unsigned char ColorGainReturnToNormal(unsigned char RGB_Percentage)
{
	return((unsigned char)((float)RGB_Percentage * (MaxColorGain - MinColorGain) / 100 + MinColorGain + 0.5));
}

void ColorRedUp(void)
{
unsigned char temp;
	temp = ScalingColorGain(ucR_GainUser);
	if(++temp > 100){
		temp = 100;
	}
	else{
		ucR_GainUser = ColorGainReturnToNormal(temp);	//((unsigned short)temp * 255 + 50) / 100;
		ucR_Gain = ucR_GainUser;
		SetContrastRGB();
		ucSavePointer = svRED;
		ShowRed();
	}
}

void ColorGreenUp(void)
{
unsigned char temp;
	temp = ScalingColorGain(ucG_GainUser);
	if(++temp > 100){
		temp = 100;
	}
	else{
		ucG_GainUser = ColorGainReturnToNormal(temp);	//((unsigned short)temp * 255 + 50) / 100;
		ucG_Gain = ucG_GainUser;
		SetContrastRGB();
		ucSavePointer = svGREEN;
		ShowGreen();
	}
}

void ColorBlueUp(void)
{
unsigned char temp;
	temp = ScalingColorGain(ucB_GainUser);
	if(++temp > 100){
		temp = 100;
	}
	else{
		ucB_GainUser = ColorGainReturnToNormal(temp);	//((unsigned short)temp * 255 + 50) / 100;
		ucB_Gain = ucB_GainUser;
		SetContrastRGB();
		ucSavePointer = svBLUE;
		ShowBlue();
	}
}

void ColorRedDown(void)
{
unsigned char temp;
	temp = ScalingColorGain(ucR_GainUser);
	if(--temp == 0xff){
		temp = 0;
	}
	else{
		ucR_GainUser = ColorGainReturnToNormal(temp);	//((unsigned short)temp * 255 + 50) / 100;
		ucR_Gain = ucR_GainUser;
		SetContrastRGB();
		ucSavePointer = svRED;
		ShowRed();
	}
}

void ColorGreenDown(void)
{
unsigned char temp;
	temp = ScalingColorGain(ucG_GainUser);
	if(--temp == 0xff){
		temp = 0;
	}
	else{
		ucG_GainUser = ColorGainReturnToNormal(temp);	//((unsigned short)temp * 255 + 50) / 100;
		ucG_Gain = ucG_GainUser;
		SetContrastRGB();
		ucSavePointer = svGREEN;
		SaveData();
		ShowGreen();
	}
}

void ColorBlueDown(void)
{
unsigned char temp;
	temp = ScalingColorGain(ucB_GainUser);
	if(--temp == 0xff)
		temp = 0;
	else{
		ucB_GainUser = ColorGainReturnToNormal(temp);	//((unsigned short)temp * 255 + 50) / 100;
		ucB_Gain = ucB_GainUser;
		SetContrastRGB();
		ucSavePointer = svBLUE;
		ShowBlue();
	}
}


void RecallsRGBOffset()
{
	ucBkOffset[0] = MCU_DataMap[EPADDR_RBKOFFSET];
	ucBkOffset[1] = MCU_DataMap[EPADDR_GBKOFFSET];
	ucBkOffset[2] = MCU_DataMap[EPADDR_BBKOFFSET];
	Write24C16(EPADDR_RBKOFFSET,ucBkOffset[0]);
	Write24C16(EPADDR_GBKOFFSET,ucBkOffset[1]);
	Write24C16(EPADDR_BBKOFFSET,ucBkOffset[2]);
	WriteIIC560(SRGB_CTRL, 0x21);
	WriteIIC560(SRGB_COEF_OFFSET, MCU_DataMap[EPADDR_RBKOFFSET]);
	WriteIIC560(SRGB_CTRL, 0x23);
	WriteIIC560(SRGB_COEF_OFFSET, MCU_DataMap[EPADDR_GBKOFFSET]);
	WriteIIC560(SRGB_CTRL, 0x25);
	WriteIIC560(SRGB_COEF_OFFSET, MCU_DataMap[EPADDR_BBKOFFSET]);
}


void RecallPOT()
{
	usPOTTimerS_900 = 0;
	usPOTTimerS_900 = 0;
	ucPOTTimerM_4 = 0;
	ulPOTTimerH = 0;
	ulPOTTimerH = 0;
	Write24C16(EPADDR_POT_BYTE0,0x00);//0x1a = POT byte 0
	Write24C16(EPADDR_POT_BYTE1,0x00);//0x1b = POT byte 1
	Write24C16(EPADDR_POT_15M,0x00);	//0x2d = POT_5M
	bPOTUpdate = FALSE;
}
