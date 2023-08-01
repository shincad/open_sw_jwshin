#include "stdio.h"
#include "math.h"
#include "8051.h"
#include "NT686xx_MCU_REG.h"
#include "NT686xx_SC_REG.H"

#include "PANEL.H"

#include "MyDef.H"
#include "IIC.H"
#include "OD.h"

#include "BFControl.h"

//
#include "Ram.h"
#include "Board.h"
#include "Scaler.h"
#include "SRGB.h"
#include "NVRAM.h"
#include "ROM_MAP.H"

#include "Mis.h"

#include "UserAdj.h"
#include "OSD.h"
#include "OSD_LF.H"
//

// BrightFrame function
static idata unsigned char ucCurBFW;


void LFEnableSettings(void)
{
	unsigned char tmpBr;


	if((ucLFMode != LF_MODE_OFF||ucDynBKMode)){
		printf("LFEnableSettings\r\n");
		BF_DisableWindow(BF_WINDOW_2);
		BF_EnableWindow(BF_WINDOW_1);
		BF_SetActiveWindow(BF_WINDOW_1);
	}
	else{
		BF_DisableWindow(BF_WINDOW_1);
	}

	//if (ucPrevLFMode == ucLFMode) return;
	ucPrevLFMode = ucLFMode;

#if _Enable_OD_ == ON
	ucCurODMode = LF_OD_MODE_OFF;
	LFSetODMode();
#endif

//	if ((ucIsBF == FALSE) || (ucOSDType != LF_MAIN_MENU))
//	{

		if ( POWER_DIGITAL )
			Write24C16(EPADDR_DVI_LF_MODE, ucLFMode);
		else
			Write24C16(EPADDR_DSUB_LF_MODE, ucLFMode);
			
/*
		if (ucLFMode == LF_MODE_Economic)
		{
//			WriteIIC560(DISPLAY_CTRL,ucDisplayControl & ~BIT_3); 
			WriteIIC560(GAMMA_CTRL,0x00);	//gamma off, 10bit
		}
		else
		{
//			WriteIIC560(DISPLAY_CTRL,ucDisplayControl); 
			if (Read24C16(EPADDR_GAMMA_ONOFF) != 0x00)
				WriteIIC560(GAMMA_CTRL,0x80);	//gamma on, 10bit
		}
*/

		tmpBr = ucBrightness;
		LFResetData();
		//LFSetColorTemp();
		//SetBrightness();	
		//SetContrastRGB();
		
		LFSetSaturation();
		LFSetHue();
		LFSetSharpness(); 
		LFSetYPeak();
		BFEnhanceColor();
//	}

	LFSetACEMode();

#ifdef BF_DYNAMIC_BACKLIGHT
	if (ucDynBKMode == 0)
	{
#endif
/*	SetBrightness();
	if (tmpBr > ucBrightness)
	{
		while(tmpBr!=ucBrightness)
		{
			tmpBr--;
			tmpBrBK = ucBrightness;
			ucBrightness = tmpBr;
			SetBrightness();
			ucBrightness = tmpBrBK;
		}
	}
	else
	{
		while(tmpBr!=ucBrightness)
		{
			tmpBr++;
			tmpBrBK = ucBrightness;
			ucBrightness = tmpBr;
			SetBrightness();
			ucBrightness = tmpBrBK;
		}
	}*/
#ifdef BF_DYNAMIC_BACKLIGHT
	}
#endif

#if _Enable_OD_ == ON
	LFSetODMode();
#endif
}

void LFMenuControl(enum LFAction act)
{
	switch(act){
	case LFConfirm : 
		OSD_OFF();
#ifdef DCR_BY_PATTERN
		bBrightnessManual = 0;
		Set_usBFTimer_10ms(300);
#endif
		ucCurKey = 0xff;
		break;
	case LFOpen  : 
		OSD_OFF();
		ucOSDLvl1_Cursor = ucLFMode;
		ShowLFMainMenu();
		ucCurKey = 0xff;
		break;
	case LFDown  : 
		if(ucOSDType == LF_MAIN_MENU){
			ucLFMode = (ucLFMode + 1)%NUM_LF_MODE; // The number of LF modes is 6
			ucOSDLvl1_Cursor = ucLFMode;
			SelectLFMITM();
			LFEnableSettings();
			if(ucLFCusACCMode == LF_ACC_AUTO) Set_usBFTimer_10ms(300);
		}
		ucCurKey = 0xff;
		break;
	case LFUp : 
		if(ucOSDType == LF_MAIN_MENU){
			ucLFMode = (ucLFMode + NUM_LF_MODE-1)%NUM_LF_MODE; // The number of LF modes is 6
			ucOSDLvl1_Cursor = ucLFMode;
			SelectLFMITM();
			LFEnableSettings();
			if(ucLFCusACCMode == LF_ACC_AUTO) Set_usBFTimer_10ms(300);
		}
		ucCurKey = 0xff;
		break;
	default:
		break;
	}	
	ucCurKey = 0xff;

	if (ucOSDType != OSDOFF) Set_usOSDTimer_10ms(500);
}


enum LF_DEFAULT_TABLE
{ 
	LF_DEFAULT_COLORTEMP = 0,
	LF_DEFAULT_LUMINANCE,
	LF_DEFAULT_CONTRAST,
	LF_DEFAULT_COLOR,
	LF_DEFAULT_HUE,
	LF_DEFAULT_SHARPNESS,
	LF_DEFAULT_YPEAK,
	LF_DEFAULT_ACE,
	LF_DEFAULT_FT,
	LF_DEFAULT_OD,
	LF_DEFAULT_DBC
};
code unsigned char LFSettingTable[LF_MODE_NUMBER][11] =
{
	{	// OFFICE
		LF_DEFAULT_COLORTEMP_OFFICE_WORK,   
		LF_DEFAULT_LUMINANCE_OFFICE_WORK, 
		LF_DEFAULT_CONTRAST_OFFICE_WORK, 
		LF_DEFAULT_COLOR_OFFICE_WORK, 
		LF_DEFAULT_HUE_OFFICE_WORK, 		
		LF_DEFAULT_SHARPNESS_OFFICE_WORK, 
		LF_DEFAULT_YPEAK_OFFICE_WORK, 
		LF_DEFAULT_ACE_OFFICE_WORK, 
		LF_DEFAULT_FT_OFFICE_WORK,
		LF_DEFAULT_OD_OFFICE_WORK,
		LF_DEFAULT_DBC_OFFICE_WORK
	},{	// IMAGE VIEWING
		LF_DEFAULT_COLORTEMP_IMAGE_VIEWING, 
		LF_DEFAULT_LUMINANCE_IMAGE_VIEWING, 
		LF_DEFAULT_CONTRAST_IMAGE_VIEWING, 
		LF_DEFAULT_COLOR_IMAGE_VIEWING, 
		LF_DEFAULT_HUE_IMAGE_VIEWING, 
		LF_DEFAULT_SHARPNESS_IMAGE_VIEWING, 
		LF_DEFAULT_YPEAK_IMAGE_VIEWING, 
		LF_DEFAULT_ACE_IMAGE_VIEWING, 
		LF_DEFAULT_FT_IMAGE_VIEWING,
		LF_DEFAULT_OD_IMAGE_VIEWING,
		LF_DEFAULT_DBC_IMAGE_VIEWING
		
	},{	// ENTERTAINMENT
		LF_DEFAULT_COLORTEMP_ENTERTAINMENT,
		LF_DEFAULT_LUMINANCE_ENTERTAINMENT, 
		LF_DEFAULT_CONTRAST_ENTERTAINMENT, 
		LF_DEFAULT_COLOR_ENTERTAINMENT, 
		LF_DEFAULT_HUE_ENTERTAINMENT, 
		LF_DEFAULT_SHARPNESS_ENTERTAINMENT, 
		LF_DEFAULT_YPEAK_ENTERTAINMENT, 
		LF_DEFAULT_ACE_ENTERTAINMENT, 
		LF_DEFAULT_FT_ENTERTAINMENT,
		LF_DEFAULT_OD_ENTERTAINMENT,
		LF_DEFAULT_DBC_ENTERTAINMENT
	},
	{	// CUSTOM
#ifdef __LF_CUSTOM_MODE__
		LF_DEFAULT_COLORTEMP_CUSTOM,
		LF_DEFAULT_LUMINANCE_CUSTOM, 
		LF_DEFAULT_CONTRAST_CUSTOM, 
		LF_DEFAULT_COLOR_CUSTOM, 
		LF_DEFAULT_HUE_CUSTOM, 
		LF_DEFAULT_SHARPNESS_CUSTOM, 
		LF_DEFAULT_YPEAK_CUSTOM, 
		LF_DEFAULT_ACE_CUSTOM, 
		LF_DEFAULT_FT_CUSTOM,
		LF_DEFAULT_OD_CUSTOM,
		LF_DEFAULT_DBC_CUSTOM
#else	// ECONOMIC
		LF_DEFAULT_COLORTEMP_ECONOMIC,
		LF_DEFAULT_LUMINANCE_ECONOMIC, 
		LF_DEFAULT_CONTRAST_ECONOMIC, 
		LF_DEFAULT_COLOR_ECONOMIC, 
		LF_DEFAULT_HUE_ECONOMIC, 
		LF_DEFAULT_SHARPNESS_ECONOMIC, 
		LF_DEFAULT_YPEAK_ECONOMIC, 
		LF_DEFAULT_ACE_ECONOMIC, 
		LF_DEFAULT_FT_ECONOMIC,
		LF_DEFAULT_OD_ECONOMIC,
		LF_DEFAULT_DBC_ECONOMIC
#endif
	},{	// OFF
		LF_DEFAULT_COLORTEMP_OFF,
		LF_DEFAULT_LUMINANCE_OFF, 
		LF_DEFAULT_CONTRAST_OFF, 
		LF_DEFAULT_COLOR_OFF, 
		LF_DEFAULT_HUE_OFF, 
		LF_DEFAULT_SHARPNESS_OFF, 
		LF_DEFAULT_YPEAK_OFF, 
		LF_DEFAULT_ACE_OFF, 
		LF_DEFAULT_FT_OFF,
		LF_DEFAULT_OD_OFF,
		LF_DEFAULT_DBC_OFF
	}
};

void LFResetData(void)
{

		if (ucLFMode == LF_MODE_OFF)
		{
			ucColorTemperature = Read24C16(EPADDR_COLOR_TEMP);

			LFLoadInitState();
			
			ucDynBKMode        = Read24C16(EPADDR_DYNAMIC_BKMODE);
#if _Enable_OD_ == ON	
			ucCurODMode        = Read24C16(EPADDR_OD_MODE);
#endif

			
			ucR_GainUser = Read24C16(EPADDR_RGAIN_USER);	//0x3e = r gain user
			ucG_GainUser = Read24C16(EPADDR_GGAIN_USER);	//0x3f = g gain user
			ucB_GainUser = Read24C16(EPADDR_BGAIN_USER);	//0x40 = b gain user
		}
		else
		{
			ucColorTemperature = LFSettingTable[ucLFMode][LF_DEFAULT_COLORTEMP];
			ucLFLuminance      = LFSettingTable[ucLFMode][LF_DEFAULT_LUMINANCE];
			ucLFContrast       = LFSettingTable[ucLFMode][LF_DEFAULT_CONTRAST];
			Write24C16(EPADDR_LF_LUM, ucLFLuminance);
			Write24C16(EPADDR_LF_CON, ucLFContrast);    
			Write24C16(EPADDR_LF_CLRTEMP, ucColorTemperature);;
			ucDynBKMode        = LFSettingTable[ucLFMode][LF_DEFAULT_DBC];
#if _Enable_OD_ == ON	
			ucCurODMode        = LFSettingTable[ucLFMode][LF_DEFAULT_OD];
#endif

			ucR_GainUser = MCU_DataMap[EPADDR_RGAIN_USER-EPADDR_EMPTY0];	//0x3e = r gain user
			ucG_GainUser = MCU_DataMap[EPADDR_GGAIN_USER-EPADDR_EMPTY0];	//0x3f = g gain user
			ucB_GainUser = MCU_DataMap[EPADDR_BGAIN_USER-EPADDR_EMPTY0];	//0x40 = b gain user
			
		}
		ucBF_Status = 0;
		if(ucDynBKMode == OFF)
			ucBrightness = ucLFLuminance;
		ucContrast = ucLFContrast;
		ucSavePointer = svBRIGHTNESS;
		SaveData();
		ucSavePointer = svCONTRAST;
		SaveData();

		ucLFColor          = LFSettingTable[ucLFMode][LF_DEFAULT_COLOR];
		ucLFHue            = LFSettingTable[ucLFMode][LF_DEFAULT_HUE];
		ucLFSharpness      = LFSettingTable[ucLFMode][LF_DEFAULT_SHARPNESS];
		ucLFYPeakEN        = LFSettingTable[ucLFMode][LF_DEFAULT_YPEAK];
		ucLFCusACCMode     = LFSettingTable[ucLFMode][LF_DEFAULT_ACE];
		ucBFColorMode      = LFSettingTable[ucLFMode][LF_DEFAULT_FT];
		
#ifdef BF_DYNAMIC_BACKLIGHT
		ucNewDynBk  = iCurDynBk = ucBrightness;
#endif

#ifdef __LF_CUSTOM_MODE__
	}
#endif	
	//printf("LF Mode: %d\n\r", (unsigned short)ucLFMode);
	//printf("\tTemperature : %d\n\r", (unsigned short)ucColorTemperature);
	//printf("\tLuminance   : %d\n\r", (unsigned short)ucLFLuminance     );
	//printf("\tContrast Gap: %d\n\r", (unsigned short)ucLFContrast      );
	//printf("\tColor Sat.  : %d\n\r", (unsigned short)ucLFColor         );
	//printf("\tSharpness   : %d\n\r", (unsigned short)ucLFSharpness     );
	//printf("\tYPEAK Enhance: %d\n\r", (unsigned short)ucLFYPeakEN        );
	//printf("\tACE Mode    : %d\n\r", (unsigned short)ucBFMode          );
	//printf("\tFT Mode     : %d\n\r", (unsigned short)ucBFColorMode     );
	
	SetColorTemp(ucColorTemperature);
	
	
	LFSetMinMax(0);
	LFSetMinMax(1);
	LFSetMinMax(2);
	LFSetMinMax(3);
}

void LFLoadInitState(void)
{
		if(POWER_DIGITAL)
			ucLFMode = Read24C16(EPADDR_DVI_LF_MODE);
		else
			ucLFMode = Read24C16(EPADDR_DSUB_LF_MODE);

		ucLFLuminance = ucBrightnessUser;	//Read24C16(EPADDR_LF_CUS_LUM);
		ucLFContrast  = ucContrastUser;	//Read24C16(EPADDR_LF_CUS_CON);
		ucLFColor     = Read24C16(EPADDR_LF_CUS_CLR);
		ucLFSharpness = Read24C16(EPADDR_LF_CUS_SHP);
		ucLFCusACCMode = Read24C16(EPADDR_LF_CUS_ACC);
		ucLFYPeakEN    = Read24C16(EPADDR_LF_CUS_YP);
		
		ucBFMode      = Read24C16(EPADDR_BF_MODE);

		ucBFColorMode = Read24C16(EPADDR_BF_FT_MODE);
		ucBFFTMore    = Read24C16(EPADDR_BF_FT_FT);
		ucBFGreenMore = Read24C16(EPADDR_BF_FT_GREEN);
		ucBFBlueMore  = Read24C16(EPADDR_BF_FT_BLUE);

		ucBrightness = ucLFLuminance;
		ucContrast = ucLFContrast;
}

void LFSetMinMax(unsigned char index)
{
	code unsigned char LFMinMaxTable[][LF_MODE_NUMBER*2] =
	{
		{   // LUMINANCE
			LF_MIN_LUMINANCE_OFFICE_WORK   ,LF_MAX_LUMINANCE_OFFICE_WORK   ,
			LF_MIN_LUMINANCE_IMAGE_VIEWING ,LF_MAX_LUMINANCE_IMAGE_VIEWING ,
//			LF_MIN_LUMINANCE_VIDEO_PLAYBACK,LF_MAX_LUMINANCE_VIDEO_PLAYBACK,	
			LF_MIN_LUMINANCE_ENTERTAINMENT ,LF_MAX_LUMINANCE_ENTERTAINMENT        ,
			LF_MIN_LUMINANCE_ECONOMIC      ,LF_MAX_LUMINANCE_ECONOMIC      ,
			LF_MIN_LUMINANCE_OFF           ,LF_MAX_LUMINANCE_OFF
		},{ // CONTRAST
			LF_MIN_CONTRAST_OFFICE_WORK    ,LF_MAX_CONTRAST_OFFICE_WORK   ,
			LF_MIN_CONTRAST_IMAGE_VIEWING  ,LF_MAX_CONTRAST_IMAGE_VIEWING ,
//			LF_MIN_CONTRAST_VIDEO_PLAYBACK ,LF_MAX_CONTRAST_VIDEO_PLAYBACK,	
			LF_MIN_CONTRAST_ENTERTAINMENT         ,LF_MAX_CONTRAST_ENTERTAINMENT        ,
			LF_MIN_CONTRAST_ECONOMIC       ,LF_MAX_CONTRAST_ECONOMIC      ,
			LF_MIN_CONTRAST_OFF            ,LF_MAX_CONTRAST_OFF
		},{ // Color Sat.
			LF_MIN_COLORSAT_OFFICE_WORK    ,LF_MAX_COLORSAT_OFFICE_WORK   ,
			LF_MIN_COLORSAT_IMAGE_VIEWING  ,LF_MAX_COLORSAT_IMAGE_VIEWING ,
//			LF_MIN_COLORSAT_VIDEO_PLAYBACK ,LF_MAX_COLORSAT_VIDEO_PLAYBACK,	
			LF_MIN_COLORSAT_ENTERTAINMENT         ,LF_MAX_COLORSAT_ENTERTAINMENT        ,
			LF_MIN_COLORSAT_ECONOMIC       ,LF_MAX_COLORSAT_ECONOMIC      ,
			LF_MIN_COLORSAT_OFF            ,LF_MAX_COLORSAT_OFF
		},{ // SHARP
			LF_MIN_SHARP_OFFICE_WORK       ,LF_MAX_SHARP_OFFICE_WORK      ,
			LF_MIN_SHARP_IMAGE_VIEWING     ,LF_MAX_SHARP_IMAGE_VIEWING    ,
//			LF_MIN_SHARP_VIDEO_PLAYBACK    ,LF_MAX_SHARP_VIDEO_PLAYBACK   ,	
			LF_MIN_SHARP_ENTERTAINMENT            ,LF_MAX_SHARP_ENTERTAINMENT           ,
			LF_MIN_SHARP_ECONOMIC          ,LF_MAX_SHARP_ECONOMIC         ,
			LF_MIN_SHARP_OFF               ,LF_MAX_SHARP_OFF
		}
	};
	
	ucLFMaxAdj = LFMinMaxTable[index][2*ucLFMode+1];
	ucLFMinAdj = LFMinMaxTable[index][2*ucLFMode];
	
	if (index == 0)
	{
		if (ucLFMode == LF_MODE_OFF)
		{
			ucMinBrightness = Read24C16(EPADDR_MIN_BRIGHT);//0x24 = MinBrightness
			ucMaxBrightness = Read24C16(EPADDR_MAX_BRIGHT);//0x25 = MaxBrightness
		}
		else
		{
			ucMinBrightness = ucLFMinAdj;
			ucMaxBrightness = ucLFMaxAdj;
		}
	}
	else if (index == 1)
	{
		if (ucLFMode == LF_MODE_OFF)
		{
			ucMinContrast = Read24C16(EPADDR_MIN_CONTRAST);//0x26 = MinContrast
			ucMaxContrast = Read24C16(EPADDR_MAX_CONTRAST);//0x28 = MaxContrast
		}
		else
		{
			ucMinContrast = ucLFMinAdj;
			ucMaxContrast = ucLFMaxAdj; 
		}
	}
}




void LFSetSaturation(void)
{
	BF_SetSaturation(ucLFColor);
}

void LFSetHue(void)
{
	BF_SetHue(ucLFHue);
}

void LFSetSharpness(void)
{
	BF_SetSharpness(ucLFSharpness);	
}

void LFSetACEMode(void)
{

		ucBFMode = ucLFCusACCMode;
		if 	(ucLFCusACCMode > LF_ACC_MODE_2) ucBFMode -= BF_ACC_MODE_3;
		
		if (ucLFCusACCMode == LF_ACC_OFF)
		{
			BF_DisableACEMode();
		}
		else if (ucLFCusACCMode == LF_ACC_AUTO)
		{
			BF_SetDymACEMode(1);
			Set_usBFTimer_10ms(BF_DYNAMIC_ACC_TIME);
		}
		else
			BF_SetPreACEMode(ucLFCusACCMode);
}

void LFSetYPeak(void)
{
	BF_SetYPeaking(ucLFYPeakEN);
}



#if _Enable_OD_ == ON

#ifdef SMART_ACCELERATOR_OSD
void LFEnableOD(void)
{
	if (ucLFMode == LF_MODE_OFF)
		ucCurODMode = LF_OD_MODE_HIGH;
	else
		ucCurODMode = LFSettingTable[ucLFMode][LF_DEFAULT_OD];	
	LFSetODMode();
}

void LFDisableOD(void)
{
	ucCurODMode = LF_OD_MODE_OFF;
	LFSetODMode();
}
#endif


void LFSetODMode(void)
{

	if(ucSignalType != sigDVI)
	{
		unsigned char i = ReadIIC560(POWER_CTRL2);
		if (ucModeNumber < 9)
		{
			DisableOD();
			WriteIIC560(POWER_CTRL2,(i | BIT_0));
			return;
		}
		else
			WriteIIC560(POWER_CTRL2,i&0xFE);
	}

	if (ucPrevODMode == ucCurODMode) return;
	ucPrevODMode = ucCurODMode;


}
#endif

void LFLeaveDemoMode(unsigned char k)
{

	unsigned char tmpReg;

	if (ucOSDType == LFDEMO)
	{
		OSD_OFF();
		Sleep(20);
	}
	tmpReg = ReadIIC560(0x390);
	WriteIIC560(0x390, tmpReg&(~0xC0));
	WriteIIC560(0x394, 0x00); // Disable Border Type
	ucIsLFDemoMode = FALSE;
	BF_SetWindowSize(BF_WINDOW_FULLSCREEN);
#if 0
	bIsLFLEDFlashing = FALSE;
	LED_LF_Off();
#endif	
	WriteIIC560(VHGLOB_ZMRNG,0x00);
	WriteIIC560(OSD_ZOOM_CTL,0x00);
	

	if (k) 
	{
		if ( POWER_DIGITAL )
			ucLFMode = Read24C16(EPADDR_DVI_LF_MODE);
		else
			ucLFMode = Read24C16(EPADDR_DSUB_LF_MODE);
		LFEnableSettings();
		Write24C16(EPADDR_LFDEMO_ONOFF, ucIsLFDemoMode);
	}
}

void LFEnterDemoMode(unsigned char k)
{

	unsigned char tmpReg;

	OSD_OFF();

	WriteIIC560(0x391, 0xFF); // Border Color R
	WriteIIC560(0x392, 0xFF); // Border Color G
	WriteIIC560(0x393, 0xFF); // Border Color B
	WriteIIC560(0x394, 0x02); // Enable Border Type
	tmpReg = ReadIIC560(0x390);
	WriteIIC560(0x390, tmpReg|0x40);

	tmpReg = ucLFMode;
	ucLFMode = LF_MODE_Entertainment;
	LFEnableSettings();
#if _Enable_OD_ == ON
	ucCurODMode = LF_OD_MODE_HIGH;
	LFSetODMode();
#endif

	if ( POWER_DIGITAL )
		Write24C16(EPADDR_DVI_LF_MODE, tmpReg);
	else
		Write24C16(EPADDR_DSUB_LF_MODE, tmpReg);

#ifdef BF_MOVING_WINDOW
	#if defined(BF_RF_DISPLAY)
	usBFMovingWidth = PanelWidth>>1;
	#else
		usBFMovingWidth = H_ActiveTab[ucResolution]>>1;
	#endif

	bBFMovingDir = 0;
#endif
	ShowLFDemoOSD();
	ucIsLFDemoMode = TRUE;
	BF_SetWindowSize(BF_WINDOW_LEFTSIZE);

	ucLFMode = tmpReg;
	if (k) Write24C16(EPADDR_LFDEMO_ONOFF, ucIsLFDemoMode);
	
	
}


void BF_Init(void)
{

	unsigned char tmpReg;
	
	ucPrevLFMode = 0xff;
	ucIsLFDemoMode = FALSE;
	ucCurBFW = BF_WINDOW_1;
	ucBFWSize = 0xff;
	BF_SetWindowSize(BF_WINDOW_FULLSCREEN);

	tmpReg = ReadIIC560(0x390);
	WriteIIC560(0x390, tmpReg&(~0xC0));
	WriteIIC560(0x394, 0x00); // Disable Border Type

	BF_SetPreACEMode(BF_ACC_LINEAR);
#if 0
	ucPrevODMode = LF_OD_MODE_LOW;
	SetODTable(LF_OD_MODE_LOW);
#endif
}

void BF_EnableWindow(enum BF_WINDOW bfw)
{
	unsigned char tmpReg1, tmpReg2;

	tmpReg1 = ReadIIC560(BRIGHT_FRM_CTRL);

#if defined(BF_RF_DISPLAY)
	tmpReg1 |= 0x10; // Reference to display
#else
	tmpReg1 &= 0xEF; // Reference to capture
#endif
	tmpReg2 = ReadIIC560(0x390);

	switch(bfw)
	{
		case BF_WINDOW_1: 
			WriteIIC560(BRIGHT_FRM_CTRL, tmpReg1 | BRIGHT_FRM1_EN);
			WriteIIC560(0x390, tmpReg2 | 0x03);
			break;
		case BF_WINDOW_2: 
			WriteIIC560(BRIGHT_FRM_CTRL, tmpReg1 | BRIGHT_FRM2_EN);
			WriteIIC560(0x390, tmpReg2 | 0x0C);
			break;
	}
}

void BF_DisableWindow(enum BF_WINDOW bfw)
{
	unsigned char tmpReg1;

	tmpReg1 = ReadIIC560(BRIGHT_FRM_CTRL);

	if (bfw == BF_WINDOW_1)
		WriteIIC560(BRIGHT_FRM_CTRL, tmpReg1 & (~BRIGHT_FRM1_EN));
	else
		WriteIIC560(BRIGHT_FRM_CTRL, tmpReg1 & (~BRIGHT_FRM2_EN));

}
 	
void BF_SetActiveWindow(enum BF_WINDOW bfw)
{
	unsigned char tmpReg1;

	ucCurBFW = bfw;
	
	tmpReg1 = ReadIIC560(BRIGHT_FRM_SEL);
	if (bfw == BF_WINDOW_1)
		WriteIIC560(BRIGHT_FRM_SEL, tmpReg1&0xfe);
	else
		WriteIIC560(BRIGHT_FRM_SEL, tmpReg1|0x01);

		BF_SetWindowSize(ucBFWSize);

	WriteIIC560(0x3C0, 0x7C);
}

void BF_SetWindowSize(unsigned char type)
{

#ifndef BF_MOVING_WINDOW
	if (ucBFWSize == type) return;
#endif

	ucBFWSize = type;
	if (type == BF_WINDOW_FULLSCREEN)
	{
#if defined(BF_RF_DISPLAY)
		WriteIIC560(BRIGHT_FRM_HS_LI, 0x00);
		WriteIIC560(BRIGHT_FRM_HS_HI, 0x00);
		WriteIIC560(BRIGHT_FRM_HW_LI, PanelWidth&0xff);
		WriteIIC560(BRIGHT_FRM_HW_HI, PanelWidth>>8);
		WriteIIC560(BRIGHT_FRM_VS_LI, 0x00);
		WriteIIC560(BRIGHT_FRM_VS_HI, 0x00);
		WriteIIC560(BRIGHT_FRM_VH_LI, PanelHeight&0xff);
		WriteIIC560(BRIGHT_FRM_VH_HI, PanelHeight>>8);
#else
		WriteIIC560(BRIGHT_FRM_HS_LI, 0x00);
		WriteIIC560(BRIGHT_FRM_HS_HI, 0x00);
		WriteIIC560(BRIGHT_FRM_HW_LI, H_ActiveTab[ucResolution]&0xff);
		WriteIIC560(BRIGHT_FRM_HW_HI, H_ActiveTab[ucResolution]>>8);
		WriteIIC560(BRIGHT_FRM_VS_LI, 0x00);
		WriteIIC560(BRIGHT_FRM_VS_HI, 0x00);
		WriteIIC560(BRIGHT_FRM_VH_LI, V_ActiveTab[ucResolution]&0xff);
		WriteIIC560(BRIGHT_FRM_VH_HI, V_ActiveTab[ucResolution]>>8);
#endif
	}
	else if (type == BF_WINDOW_LEFTSIZE)
	{
#if defined(BF_RF_DISPLAY)
		WriteIIC560(BRIGHT_FRM_HS_LI, 0x00);
		WriteIIC560(BRIGHT_FRM_HS_HI, 0x00);
#ifdef BF_MOVING_WINDOW
		WriteIIC560(BRIGHT_FRM_HW_LI, (usBFMovingWidth)&0xFF);
		WriteIIC560(BRIGHT_FRM_HW_HI, (usBFMovingWidth)>>8);		
#else
		WriteIIC560(BRIGHT_FRM_HW_LI, (PanelWidth/2)&0xFF);
		WriteIIC560(BRIGHT_FRM_HW_HI, (PanelWidth/2)>>8);
#endif
		WriteIIC560(BRIGHT_FRM_VS_LI, 0x00);
		WriteIIC560(BRIGHT_FRM_VS_HI, 0x00);		
		WriteIIC560(BRIGHT_FRM_VH_LI, PanelHeight&0xff);
		WriteIIC560(BRIGHT_FRM_VH_HI, PanelHeight>>8);
#else
		WriteIIC560(BRIGHT_FRM_HS_LI, 0x00);
		WriteIIC560(BRIGHT_FRM_HS_HI, 0x00);
	#ifdef BF_MOVING_WINDOW
		WriteIIC560(BRIGHT_FRM_HW_LI, (usBFMovingWidth)&0xFF);
		WriteIIC560(BRIGHT_FRM_HW_HI, (usBFMovingWidth)>>8);		
	#else
		WriteIIC560(BRIGHT_FRM_HW_LI, (H_ActiveTab[ucResolution]/2)&0xFF);
		WriteIIC560(BRIGHT_FRM_HW_HI, (H_ActiveTab[ucResolution]/2)>>8);
	#endif
		WriteIIC560(BRIGHT_FRM_VS_LI, 0x00);
		WriteIIC560(BRIGHT_FRM_VS_HI, 0x00);		
		WriteIIC560(BRIGHT_FRM_VH_LI, V_ActiveTab[ucResolution]&0xFF);
		WriteIIC560(BRIGHT_FRM_VH_HI, V_ActiveTab[ucResolution]>>8);
#endif
	}
	else if (type == BF_WINDOW_RIGHTSIZE)
	{
#if defined(BF_RF_DISPLAY)
		WriteIIC560(BRIGHT_FRM_HS_LI, (PanelWidth/2)&0xFF);
		WriteIIC560(BRIGHT_FRM_HS_HI, (PanelWidth/2)>>8);
		WriteIIC560(BRIGHT_FRM_HW_LI, (PanelWidth/2)&0xFF);
		WriteIIC560(BRIGHT_FRM_HW_HI, (PanelWidth/2)>>8);
		WriteIIC560(BRIGHT_FRM_VS_LI, 0x00);
		WriteIIC560(BRIGHT_FRM_VS_HI, 0x00);		
		WriteIIC560(BRIGHT_FRM_VH_LI, PanelHeight&0xff);
		WriteIIC560(BRIGHT_FRM_VH_HI, PanelHeight>>8);
#else
		WriteIIC560(BRIGHT_FRM_HS_LI, (H_ActiveTab[ucResolution]/2)&0xFF);
		WriteIIC560(BRIGHT_FRM_HS_HI, (H_ActiveTab[ucResolution]/2)>>8);
		WriteIIC560(BRIGHT_FRM_HW_LI, (H_ActiveTab[ucResolution]/2)&0xFF);
		WriteIIC560(BRIGHT_FRM_HW_HI, (H_ActiveTab[ucResolution]/2)>>8);
		WriteIIC560(BRIGHT_FRM_VS_LI, 0x00);
		WriteIIC560(BRIGHT_FRM_VS_HI, 0x00);		
		WriteIIC560(BRIGHT_FRM_VH_LI, V_ActiveTab[ucResolution]&0xFF);
		WriteIIC560(BRIGHT_FRM_VH_HI, V_ActiveTab[ucResolution]>>8);
#endif
	}
	
}

void BF_MovingWindow()
{
	if ( ucBFMovingTimer )
	{
		ucBFMovingTimer = 0;
		BF_SetWindowSize(BF_WINDOW_LEFTSIZE);
		if ( bBFMovingDir==0 && (++usBFMovingWidth > (H_ActiveTab[ucResolution]*7/10)) )
			bBFMovingDir = 1;
		else if ( bBFMovingDir==1 && (--usBFMovingWidth < (H_ActiveTab[ucResolution]*3/10)) )
			bBFMovingDir = 0;
	}
}

 	
void BF_SetSaturation(unsigned char sat)
{
	WriteIIC560(0x3C8, sat);	
}
void BF_SetHue(unsigned char hue)
{
	WriteIIC560(0x3C7, hue);
}

void BF_SetSharpness(unsigned char shp)
{
	if ( shp <1 || shp > 31 )	return;
	if ( shp > 16 )
		WriteIIC560(BK_H_SHAP_CTRL, BK_H_ASRP|(shp-16));
	else
		WriteIIC560(BK_H_SHAP_CTRL, BK_H_ASRP|(32-shp));
}

void BF_SetYPeaking(unsigned char yp)
{
	if (yp == 0)
	{
		WriteIIC560(0x3A0, 0x00);
	}
	else
	{
		WriteIIC560(0x3A0, 0x01);	
		yp = (yp << 2) & 0x0C;
		WriteIIC560(0x3A1, yp);	
	}
}

void BF_SetPreACEMode(unsigned char mode)
{
	static code unsigned char PresetACCMode[][17] =
	{
		{  3, 21, 38, 56, 74, 91,109,126,145,162,180,198,215,233,251,255},	// Mode 1 // Std 1
		{  3,  7, 27, 47, 67, 87,107,127,147,167,187,207,227,247,251,255},	// Mode 2 // Std 2
		{ 15, 28, 41, 56, 71, 88,106,125,145,164,182,199,214,229,242,255},	// Mode 3 // S
		{ 15, 31, 52, 71, 88,103,117,130,141,153,167,182,199,218,239,255},	// Mode 4 // -S
		{ 11, 24, 37, 50, 64, 79, 94,109,125,142,159,177,195,215,240,255},	// Mode 5 // Sunshine Mode
		{ 20, 40, 59, 77, 95,112,129,145,161,176,190,204,218,231,243,255},	// Mode 6 // Night Mode
		{ 15, 31, 47, 63, 79, 95,111,127,143,159,175,191,207,223,239,255},	// Default Mode : 1:1 Linear
	};  
	unsigned char i, tmpReg;
#if !NT68665
	unsigned char volatile *pBus;
#endif	    
	tmpReg = ReadIIC560(0x3B1) & 0x0E;
	if (ucCurBFW == BF_WINDOW_2) tmpReg |= 0x20; 
	    
	tmpReg |= 0x50;  // Write Gamma
	WriteIIC560(0x3B1,tmpReg);
#if NT68665
	WriteIIC560(0x3B2,0x00);
	WriteIIC560(0x3B2,0x00);
	for(i = 0; i < ACE_PARTITIONS; i++){
		WriteIIC560(0x3B2,(((unsigned short)PresetACCMode[mode][i]+1)<<2)&0xFF);
		WriteIIC560(0x3B2,(((unsigned short)PresetACCMode[mode][i]+1)<<2)>>8);
	}
#else
	SC_RegPage = 0x03;
	pBus = &SC_ACE_DATA_PORT;
	*pBus = 0x00;
	*pBus = 0x00;
	for(i = 0; i < ACE_PARTITIONS; i++){
		*pBus = (((unsigned short)PresetACCMode[mode][i]+1) <<2 ) & 0xFF;
		*pBus = (((unsigned short)PresetACCMode[mode][i]+1) << 2) >> 8;
	}
	
#endif
	// Update I-Gamma
	WriteIIC560(0x3B1,tmpReg | 0x90);

	Sleep(100);
	BF_EnableACEMode();
}

void BF_UpdateHistogram(void)
{
    unsigned char tmpReg = 0;
    
//	BF_EnableACEMode();
	if((ReadIIC560(0x3B1) & 0x01) != 0) return;
	if(ucCurBFW == BF_WINDOW_2) tmpReg |= 0x20; 
//    WriteIIC560(0x3B0,0x08);
    WriteIIC560(0x3B1,tmpReg|0x01);
}


void BF_GetHistogram(void)
{
	unsigned char i, tmpHis1, tmpHis2, tmpHis3;
#if !NT68665
	unsigned char volatile *pBus;
#endif
    while ((ReadIIC560(0x3B1) & 0x01) != 0){
		if ((IsBackLightOn() == FALSE) || (bVideoMuted == TRUE)) return;
    }

	// Read Histograms //
	ulCurHisgrmTotal = 0;
#if NT68665
 	WriteIIC560(0x3B2,0x00);
	WriteIIC560(0x3B2,0x00);
   for(i = 0; i < ACE_PARTITIONS; i++){
    	tmpHis1 = ReadIIC560(0x3B2);
    	tmpHis2 = ReadIIC560(0x3B2);
    	tmpHis3 = ReadIIC560(0x3B2);
    	ulCurHisgrm[i]  = ((unsigned long)tmpHis3 << 16);
    	ulCurHisgrm[i] += ((unsigned long)tmpHis2 <<  8);
    	ulCurHisgrm[i] += (unsigned long)tmpHis1;
    	ulCurHisgrmTotal += ulCurHisgrm[i];
//    	printf("%d %ld\n\r",(unsigned short)i, ulCurHisgrm[i]);
	}
#else
	SC_RegPage = 0x03;
	pBus = &SC_ACE_DATA_PORT;
	*pBus = 0x00;
	*pBus = 0x00;
    for(i = 0; i < ACE_PARTITIONS; i++){
    	tmpHis1 = *pBus;
    	tmpHis2 = *pBus;
    	tmpHis3 = *pBus;
    	ulCurHisgrm[i]  = ((unsigned long)tmpHis3 << 16);
    	ulCurHisgrm[i] += ((unsigned long)tmpHis2 <<  8);
    	ulCurHisgrm[i] += (unsigned long)tmpHis1;
    	ulCurHisgrmTotal += ulCurHisgrm[i];
//    	printf("%d %ld\n\r",(unsigned short)i, ulCurHisgrm[i]);
	}
#endif
//	printf("%ld\n\r", ulCurHisgrmTotal);
}

code unsigned char YinYoutTab[][16] =
{	//0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15
	{ 4, 4, 6, 6, 8, 8,10,10,10,10, 8, 8, 6, 6, 4, 4,}, //0,  // 0 
	{ 4, 4, 6, 6, 8, 8,10,10,10,10, 8, 8, 6, 6, 4, 4,}, //1,  // 1*5120
	{ 4, 4, 6, 6, 8, 8,10,10,10,10, 8, 8, 6, 6, 4, 4,}, //2,  // 2*5120
	{ 4, 4, 6, 6, 8, 8,10,10,10,10, 8, 8, 6, 6, 4, 4,}, //3,  // 3*5120
	{ 4, 4, 6, 6, 8, 8,10,10,10,10, 8, 8, 6, 6, 4, 4,}, //4,  // 4*5120
	{ 4, 4, 8, 8, 8, 8,10,10,10,10, 8, 8, 8, 8, 4, 4,}, //5,  // 5*5120
	{ 4, 4, 8, 8, 8, 8,10,10,10,10, 8, 8, 8, 8, 4, 4,}, //6,  // 6*5120
	{ 4, 4, 8, 8, 8, 8,10,10,10,10, 8, 8, 8, 8, 4, 4,}, //7,  // 7*5120
	{ 6, 6, 8, 8, 8, 8,10,10,10,10, 8, 8, 8, 8, 6, 6,}, //8,  // 8*5120
	{ 8, 8, 8, 8, 8, 8,10,10,10,10, 8, 8, 8, 8, 8, 8,}, //9,  // 9*5120
	{10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,}, //10, //10*5120
	{11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,}, //11, //11*5120
	{12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,}, //12, //12*5120
	{13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,}, //13, //13*5120
	{14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,}, //14, //14*5120
	{15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,}, //15, //15*5120
	{16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16}, //16, // 1*81920
	{16,16,17,17,17,17,17,17,17,17,17,17,17,17,16,16}, //17, // 1*81920+ 2*5120
	{16,16,18,18,18,18,18,18,18,18,18,18,18,18,16,16}, //18, // 1*81920+ 4*5120
	{16,16,19,19,19,19,19,19,19,19,19,19,19,19,16,16}, //19, // 1*81920+ 6*5120
	{16,16,20,20,20,20,20,20,20,20,20,20,20,20,16,16}, //20, // 1*81920+ 8*5120
	{16,16,21,21,21,21,21,21,21,21,21,21,21,21,16,16}, //21, // 1*81920+10*5120
	{16,16,22,22,22,22,22,22,22,22,22,22,22,22,16,16}, //22, // 1*81920+12*5120
	{16,16,23,23,23,23,23,23,23,23,23,23,23,23,16,16}, //23, // 1*81920+14*5120
	{16,16,24,24,24,24,24,24,24,24,24,24,24,24,16,16}, //24, // 2*81920
	{16,16,25,25,25,25,25,25,25,25,25,25,25,25,16,16}, //25, // 2*81920+4*5120
	{16,16,26,26,26,26,26,26,26,26,26,26,26,26,16,16}, //26, // 2*81920+8*5120
	{16,16,27,27,27,27,27,27,27,27,27,27,27,27,16,16}, //27, // 2*81920+12*5120
	{16,16,28,28,28,28,28,28,28,28,28,28,28,28,16,16}, //28, // 2*81920+16*5120
	{16,16,29,29,29,29,29,29,29,29,29,29,29,29,16,16}, //29, // 2*81920+20*5120
	{16,16,30,30,30,30,30,30,30,30,30,30,30,30,16,16}, //30, // 2*81920+24*5120
	{16,16,31,31,31,31,31,31,31,31,31,31,31,31,16,16}, //31, // 2*81920+28*5120
	{16,16,32,32,32,32,32,32,32,32,32,32,32,32,16,16}, //32, // 2*81920+32*5120
};


void BF_SetDymACEMode(unsigned char reset)
{
#define OVERALL    1024

#define LOWERBOUND_0 58
#define LOWERBOUND_1 58
#define LOWERBOUND_2 58
#define LOWERBOUND_3 58
#define LOWERBOUND_4 58
#define LOWERBOUND_5 58
#define LOWERBOUND_6 58
#define LOWERBOUND_7 58
#define LOWERBOUND_8 58
#define LOWERBOUND_9 58
#define LOWERBOUND_A 58
#define LOWERBOUND_B 58
#define LOWERBOUND_C 58
#define LOWERBOUND_D 58
#define LOWERBOUND_E 58
#define LOWERBOUND_F 58
#define LOWERBOUND   (LOWERBOUND_0 + LOWERBOUND_1 + LOWERBOUND_2 + LOWERBOUND_3 + \
                      LOWERBOUND_4 + LOWERBOUND_5 + LOWERBOUND_6 + LOWERBOUND_7 + \
                      LOWERBOUND_8 + LOWERBOUND_9 + LOWERBOUND_A + LOWERBOUND_B + \
                      LOWERBOUND_C + LOWERBOUND_D + LOWERBOUND_E + LOWERBOUND_F)

#define UPPERBOUND_0 72
#define UPPERBOUND_1 72
#define UPPERBOUND_2 80
#define UPPERBOUND_3 80
#define UPPERBOUND_4 80
#define UPPERBOUND_5 80
#define UPPERBOUND_6 80
#define UPPERBOUND_7 80
#define UPPERBOUND_8 80
#define UPPERBOUND_9 80
#define UPPERBOUND_A 80
#define UPPERBOUND_B 80
#define UPPERBOUND_C 80
#define UPPERBOUND_D 80
#define UPPERBOUND_E 72
#define UPPERBOUND_F 72
#define UPPERBOUND   (UPPERBOUND_0 + UPPERBOUND_1 + UPPERBOUND_2 + UPPERBOUND_3 + \
                      UPPERBOUND_4 + UPPERBOUND_5 + UPPERBOUND_6 + UPPERBOUND_7 + \
                      UPPERBOUND_8 + UPPERBOUND_9 + UPPERBOUND_A + UPPERBOUND_B + \
                      UPPERBOUND_C + UPPERBOUND_D + UPPERBOUND_E + UPPERBOUND_F)

	float fICurv[ACE_PARTITIONS];
	float fICurvTotal;
	unsigned short usTmp, usVarSum;
	unsigned char i, tmpReg;
#if !NT68665
	unsigned char volatile *pBus;
#endif	    

	static xdata unsigned short usPrvHisgrm[ACE_PARTITIONS] = {0};
	static xdata unsigned char  ucIsHisgrmDiff = FALSE;

#ifdef BF_SMOOTH_AUTOACE
#if ACE_PARTITIONS == 16
	static unsigned short usCurICurv[ACE_PARTITIONS] = {0x0040, 0x0040, 0x0040, 0x0040, 
	                                                    0x0040, 0x0040, 0x0040, 0x0040, 
	                                                    0x0040, 0x0040, 0x0040, 0x0040, 
	                                                    0x0040, 0x0040, 0x0040, 0x0040};
#elif ACE_PARTITIONS == 8
	static unsigned short usCurICurv[ACE_PARTITIONS] = {0x0080, 0x0080, 0x0080, 0x0080, 
	                                                    0x0080, 0x0080, 0x0080, 0x0080};
#else
	static unsigned short usCurICurv[ACE_PARTITIONS] = {0x0100, 0x0100, 0x0100, 0x0100};
#endif
#endif

//#ifndef BF_SMOOTH_AUTOACE
//	BF_UpdateHistogram();
//#endif

	if (reset)
	{
		tmpReg = 0;
		if (ucCurBFW == BF_WINDOW_2) tmpReg |= 0x20; 
    	WriteIIC560(0x3B1,tmpReg|0x01);
	    for(i = 0; i < ACE_PARTITIONS; i++)
	    {
	    	usPrvHisgrm[i] = 0;
#ifdef BF_SMOOTH_AUTOACE
	    	usCurICurv[i] = 0x0040;
#endif
		}
	}

    while ((ReadIIC560(0x3B1) & 0x01) != 0)
    {
		if ((IsBackLightOn() == FALSE) || (bVideoMuted == TRUE)) return;
    }

	if (ulCurHisgrmTotal == 0) return;

    for(i = 0; i < ACE_PARTITIONS; i++)
    {
//#ifdef BF_SMOOTH_AUTOACE
		usVarSum = (unsigned short)(ulCurHisgrm[i]>>8);
		if (abs(usPrvHisgrm[i]-usVarSum) > 64)
		{
			usPrvHisgrm[i] = usVarSum;
			ucIsHisgrmDiff = TRUE;
		}
//#endif		
    	//printf("%ld",ulCurHisgrm[i]);
    	//printf("\n\r");
	}
	
//#ifdef BF_SMOOTH_AUTOACE	
	if (ucIsHisgrmDiff == FALSE) return;
//#endif

#ifdef BF_DYNAMIC_ARRAY
	fICurvTotal = 0;
	for(i = 0; i < ACE_PARTITIONS; i++)
	{
		unsigned short m;
		m = ulCurHisgrm[i]/5120;
		if (m > 64)
			m = 32;
		else if (m > 32)
			m = 24 + (m-32)/4;
		else if (m > 16)
			m = 16 + (m-16)/2;
		//printf("i:%d H:%ld m:%d y:%d\n\r",(unsigned short)i,ulCurHisgrm[i],m,(unsigned short)YinYoutTab[m][i]);
		fICurv[i] = YinYoutTab[m][i]+16;
		fICurvTotal += fICurv[i];
		//printf("CAL(%d): %d\n\r", (unsigned short)i, (unsigned short)fICurv[i]);
	}
#else	
	// Calculate new weighting by histogram.
	for(i = 0; i < ACE_PARTITIONS; i++)
	{
		fICurv[i] = ((float)OVERALL - LOWERBOUND)*ulCurHisgrm[i]/ulCurHisgrmTotal + LOWERBOUND_0 + 0.5;
		//printf("CAL(%d): %d\n\r", (unsigned short)i, (unsigned short)fICurv[i]);
	}	

#if ACE_PARTITIONS == 16
	usVarSum = 0;
	for(i = 6; i < 10; i++)
		usVarSum = usVarSum + fICurv[i];
	usVarSum = (usVarSum+2) / 4;        
	for(i = 6; i < 10; i++)
		fICurv[i] = usVarSum;
#elif ACE_PARTITIONS == 8
	usVarSum = 0;
	for(i = 3; i < 5; i++)
		usVarSum = usVarSum + fICurv[i];
	usVarSum = (usVarSum+1) / 2;
	for(i = 3; i < 5; i++)
		fICurv[i] = usVarSum;
#endif
#endif

#ifdef BF_SMOOTH_AUTOACE

#ifdef BF_DYNAMIC_ARRAY
	fICurvTotal = 1024/fICurvTotal;
	for(i = 1; i < ACE_PARTITIONS; i++)
		fICurv[i] = fICurv[i]*fICurvTotal;
#endif

	usVarSum = 0;
	for (i = 0; i < ACE_PARTITIONS; i++)
	{
		usTmp = (unsigned short)fICurv[i];
		if (usCurICurv[i] > usTmp)
		{
			usVarSum = usCurICurv[i] - usTmp + usVarSum;
			if ((usCurICurv[i] - usTmp) > 3)
				fICurv[i] = usCurICurv[i] - 3;
			else
				fICurv[i] = usTmp;
		}
		else
		{
			usVarSum = usTmp - usCurICurv[i] + usVarSum;
			if ((usTmp - usCurICurv[i]) > 3)
				fICurv[i] = usCurICurv[i] + 3;
			else
				fICurv[i] = usTmp;
		}
		//printf("NEW(%d): %d\n\r", (unsigned short)i, (unsigned short)usCurICurv[i]);		
	}

	usVarSum = usVarSum / ACE_PARTITIONS;
	if (usVarSum == 0) 
	{
		ucIsHisgrmDiff = FALSE;
		return;
	}

	usCurICurv[0] = fICurv[0];
	for(i = 1; i < ACE_PARTITIONS; i++)
	{
		usCurICurv[i] = fICurv[i];
		fICurv[i] = fICurv[i] + fICurv[i-1];
		//printf("IG(%d): %d\n\r", (unsigned short)i, (unsigned short)usCurICurv[i]);
	}
#else
	for(i = 1; i < ACE_PARTITIONS; i++)
	{
		fICurv[i] = fICurv[i] + fICurv[i-1];
		//printf("IG(%d): %d\n\r", (unsigned short)i, (unsigned short)usCurICurv[i]);
	}
#ifdef BF_DYNAMIC_ARRAY
	fICurvTotal = 1024/fICurvTotal;
	for(i = 1; i < ACE_PARTITIONS; i++){
		fICurv[i] = fICurv[i]*fICurvTotal;
		//printf("IG(%d): %d\n\r", (unsigned short)i, (unsigned short)fICurv[i]);
	}
#endif
	ucIsHisgrmDiff = FALSE;
#endif

	// Write I-Gamma //
	tmpReg = ReadIIC560(0x3B1) & 0x0E;
	if (ucCurBFW == BF_WINDOW_2) tmpReg |= 0x20; 
	tmpReg |= 0x50;
	WriteIIC560(0x3B1,tmpReg);
#if NT68665
	WriteIIC560(0x3B2,0x00);
	WriteIIC560(0x3B2,0x00);
	for(i = 0; i<ACE_PARTITIONS; i++){
		usTmp = (unsigned short)fICurv[i];
		WriteIIC560(0x3B2,usTmp&0xFF);
		WriteIIC560(0x3B2,usTmp>>8);
	}
#else
	SC_RegPage = 0x03;
	pBus = &SC_ACE_DATA_PORT;
	*pBus = 0x00;
	*pBus = 0x00;
	for(i = 0; i<ACE_PARTITIONS; i++){
		usTmp = (unsigned short)fICurv[i];
		*pBus = (unsigned char)(usTmp & 0xFF);
		*pBus = (unsigned char)(usTmp >> 8);
	}
#endif
	// Update I-Gamma
	WriteIIC560(0x3B1,tmpReg | 0x90);
    
	BF_EnableACEMode();
}

#ifdef BF_DYNAMIC_BACKLIGHT
void BF_SetDymBacklight(void)
{
	unsigned char i;
	unsigned char ucTmpDynBk;
	float    fCurBK;
#if BFDYNBK_TYPE == BFDYNBK_TYPE_4
	unsigned long  ulHisTotal;
#endif
	static unsigned char ucUpdateBK = FALSE;

    //if ((ReadIIC560(0x3B1) & 0x01) != 0) return;
	if (ulCurHisgrmTotal == 0) return;

#if BFDYNBK_TYPE == BFDYNBK_TYPE_1
	for(i = ACE_PARTITIONS-1; i > 0; i--)
		if (ulCurHisgrm[i] != 0) break;
	if (i < 2)
		ucTmpDynBk = ucMinBrightness;
	else
		ucTmpDynBk = ucBrightness;
#elif BFDYNBK_TYPE == BFDYNBK_TYPE_2
	for(i = ACE_PARTITIONS-1; i > 0; i--)
		if (ulCurHisgrm[i] != 0) break;
	if (i > 13) i = 15; // This is for 16 ACE area
	ucTmpDynBk = ((float)ucBrightness*i/(ACE_PARTITIONS-1) + 0.5);
#elif BFDYNBK_TYPE == BFDYNBK_TYPE_3
//	printf("BFDYNBK_TYPE_3=%ld,%ld\r\n",(unsigned long)ulCurHisgrmTotal,(unsigned long)ulCurHisgrm[0]);
	i = 0; // Dummy for removing waring
#if	ACE_PARTITIONS == 16
	fCurBK = (float)(ulCurHisgrmTotal - ulCurHisgrm[0] - ulCurHisgrm[1])/ulCurHisgrmTotal;
	//
//	printf("fCurBK=%f\r\n",fCurBK);
	
//	if(fCurBK > 0.45){
//		fCurBK = 1;
//	}
	if(fCurBK > 0.48){//0.48
		fCurBK = 1;
//		LED_GrnOn();
	}
	else if(fCurBK > 0.35){//0.35
		return;
	}
	else{
//		LED_GrnOn();
	}

#else
	fCurBK = (float)(ulCurHisgrmTotal - ulCurHisgrm[0])/ulCurHisgrmTotal;
#endif
	ucTmpDynBk = fCurBK*(ucMaxBrightness-ucMinBrightness)+ ucMinBrightness;
#elif BFDYNBK_TYPE == BFDYNBK_TYPE_4
	i = 0; // Dummy for removing waring
#if	ACE_PARTITIONS == 16
	fCurBK = (float)(ulCurHisgrmTotal - ulCurHisgrm[0] - ulCurHisgrm[1])/ulCurHisgrmTotal;
#else
	fCurBK = (float)(ulCurHisgrmTotal - ulCurHisgrm[0])/ulCurHisgrmTotal;
#endif
	ucTmpDynBk = fCurBK*(ucMaxBrightness-ucMinBrightness)+ ucMinBrightness;
#endif
	
	if(ucTmpDynBk != ucNewDynBk){
		ucNewDynBk = ucTmpDynBk;
		if(ucNewDynBk < ucMinBrightness ) ucNewDynBk = ucMinBrightness;
		else if(ucNewDynBk > ucMaxBrightness) ucNewDynBk = ucMaxBrightness;
#if BFDYNBK_TYPE == BFDYNBK_TYPE_1
		usBF_DYMBK_Timer_10ms = 250;
#endif
	}
	
	//printf("i:%d NewBK:%d\n\r", (unsigned short)i, (unsigned short)ucNewDynBk);
	
#if BFDYNBK_TYPE == BFDYNBK_TYPE_1
	if ((i > 1) || ((i < 2) && (usBF_DYMBK_Timer_10ms == 0)))
	{
#endif

	if ((abs(iCurDynBk-ucNewDynBk) < 10) && (ucUpdateBK == FALSE))return;

#if BFDYNBK_TYPE == BFDYNBK_TYPE_4
	fCurBK = fCurBK*100;
	if (fCurBK > 80)
	{
		if (iCurDynBk == ucBrightness) return;
		SetBrightness();
		ucUpdateBK = FALSE;
		//printf("1: SetBrightness: %d\n\r", (unsigned short)ucBrightness);
		return;
	}
	
	ulHisTotal = ulCurHisgrmTotal;
	for(i = ACE_PARTITIONS-1; i > ((ACE_PARTITIONS-1)/2); i--)
		ulHisTotal = ulHisTotal - ulCurHisgrm[i];
	fCurBK = (float)ulHisTotal/ulCurHisgrmTotal;
	fCurBK = fCurBK*100;
	if (fCurBK < 70)
	{
		if (iCurDynBk == ucBrightness) return;
		SetBrightness();
		ucUpdateBK = FALSE;
		//printf("2: SetBrightness: %d\n\r", (unsigned short)ucBrightness);
		return;
	}
#endif

	ucUpdateBK = TRUE;
	if (iCurDynBk != ucNewDynBk)
	{
//#ifdef BF_SMOOTH_AUTOACE
		if (abs(iCurDynBk-ucNewDynBk) < ((ucMaxBrightness-ucMinBrightness)>>2) )	//100
		{
			if (iCurDynBk < ucNewDynBk)
			{
				iCurDynBk++;
				if (iCurDynBk > ucNewDynBk) iCurDynBk = ucNewDynBk;
			}
			else
			{
				iCurDynBk--;
				if (iCurDynBk < ucNewDynBk) iCurDynBk = ucNewDynBk;
			}
		}
		else
		{
			if (iCurDynBk < ucNewDynBk)
			{
				iCurDynBk = ucNewDynBk;
				ucUpdateBK = FALSE;
			}
			else
			{
				//iCurDynBk = (iCurDynBk + ucNewDynBk)/2;
				iCurDynBk -= ((ucMaxBrightness-ucMinBrightness)>>2);	//50
			}
		}
//#else
//		iCurDynBk = ucNewDynBk;
//		ucUpdateBK = FALSE;
//#endif
	
		ucTmpDynBk = ucBrightness;
		ucBrightness = iCurDynBk;
		SetBrightness();
		ucBrightness = ucTmpDynBk;
		//printf("DynBK:%d BR:%d\n\r", iCurDynBk, (unsigned short)ucBrightness);
	}
	else
		ucUpdateBK = FALSE;

#if BFDYNBK_TYPE == BFDYNBK_TYPE_1
	}
#endif
}
#endif

void BF_EnableACEMode(void)
{
	unsigned char tmpReg;

	tmpReg = ReadIIC560(0x3B0);
	// Enable I-Gamma
#if (NT68670 || NT68670B || NT68167 || NT68667)
	if (ucCurBFW == BF_WINDOW_2) 
#else
	if (ucCurBFW == BF_WINDOW_1) 
#endif	
		tmpReg |= 0x01; 
	else
		tmpReg |= 0x02; 

#if    ACE_PARTITIONS == 16
		tmpReg |= 0x08; 
#elif  ACE_PARTITIONS == 8
		tmpReg |= 0x04; 
#endif

#if (NT68670 || NT68670B || NT68167 || NT68667)	// seperate for 665 is too slow at 070713
	WriteIIC560(0x3B0,tmpReg);
#else
	WriteIIC_WaitV(SCALER_I2C_ADDR, 0x3B0, tmpReg);
#endif	
}

void BF_DisableACEMode(void)
{
	unsigned char tmpReg;

	tmpReg = ReadIIC560(0x3B0);
	// Disable I-Gamma
#if (NT68670 || NT68670B || NT68167 || NT68667)
	if (ucCurBFW == BF_WINDOW_2) 
#else
	if (ucCurBFW == BF_WINDOW_1) 
#endif	
		tmpReg &= ~BIT_0; 
	else
		tmpReg &= ~BIT_1; 

	WriteIIC560(0x3B0,tmpReg);
}

// Color Related
void BFEnhanceColor(void) 
{
	switch(ucBFColorMode) {
	case BF_FTMODE_1:
    	ucBFFTMore = 0x4C;
		ucBFGreenMore = 0x8F;
		ucBFBlueMore = 0x87;
		WriteIIC560(0x3CC,0xE1);  //enable HH,HS
		break;
	case BF_FTMODE_2:
		ucBFFTMore = 0x00;  //0x80
		ucBFGreenMore = 0xA6;
		ucBFBlueMore = 0x80;
		WriteIIC560(0x3CC,0xE1);  //enable HH,HS
		break;
	case BF_FTMODE_3:
		ucBFFTMore = 0x00;  //0x80
		ucBFGreenMore = 0x80;
		ucBFBlueMore = 0xA6;
		WriteIIC560(0x3CC,0xE1);  //enable HH,HS
		break;
	case BF_FTMODE_USR:
		ucBFFTMore    = Read24C16(EPADDR_BF_FT_FT);
		ucBFGreenMore = Read24C16(EPADDR_BF_FT_GREEN);
		ucBFBlueMore  = Read24C16(EPADDR_BF_FT_BLUE);
		WriteIIC560(0x3CC,0xE1);  //enable HH,HS	
		break;
	case BF_FTMODE_OFF: //normal
		ucBFFTMore = 0x00;	//0x80
		ucBFGreenMore = 0x80;
		ucBFBlueMore = 0x80;
		WriteIIC560(0x3CC,0xE0);  //disable HH,HS
		break;
	}

	BFCorrectFleshTone();
	BFEnhanceGreen();
	BFEnhanceBlue();
	
//	if (  ucBFColorMode==BF_FTMODE_2)
//	{
//		BFEnhanceMag();	
//		SetContrastRGB();
//	}
}


void BFCorrectFleshTone(void) 
{
	unsigned char Temp;
	xdata unsigned short i;
	
	//Temp = ReadIIC560(0x3CC) & 0xFD;
    //WriteIIC560(0x3CC,Temp);
	////flesh tone
    //i = ucBFFTMore;
	//i = 0x80 + (i/12);
    //WriteIIC560(0x3CD,0x01);
	//WriteIIC560(0x3CE,0x00);
	//WriteIIC560(0x3CF,i);
 	//WriteIIC560(0x3CC,Temp | 0x02);
    //i = ucBFFTMore;
	//i = (i* 5)/12;
    //WriteIIC560(0x3CC,Temp);
	//WriteIIC560(0x3CD,0x01);
	//WriteIIC560(0x3CE,0x02);
	//WriteIIC560(0x3CF,i);
 	//WriteIIC560(0x3CC,Temp | 0x02);

	i = (unsigned short)ucBFFTMore*48/255;
	Temp = ReadIIC560(0x3CC) & 0xFD;
    WriteIIC560(0x3CC,Temp);
    WriteIIC560(0x3CD,0x01);
	WriteIIC560(0x3CE,0x00);
	WriteIIC560(0x3CF,i/2);
	WriteIIC560(0x3CE,0x01);
	WriteIIC560(0x3CF,i*3/4);
	WriteIIC560(0x3CE,0x02);
	WriteIIC560(0x3CF,i);
	WriteIIC560(0x3CE,0x03);
	WriteIIC560(0x3CF,i*3/4);
 	WriteIIC560(0x3CC,Temp | 0x02);
}

/*
void BFEnhanceMag(void) 
{
	unsigned char Temp;

	Temp = ReadIIC560(0x3CC) & 0xFD;

    WriteIIC560(0x3CC,Temp); 
	WriteIIC560(0x3CD,0x02);
	WriteIIC560(0x3CE,0x00);

	WriteIIC560(0x3CF,0x7a);
	WriteIIC560(0x3CF,0x88);
    WriteIIC560(0x3CC,Temp | 0x02);

}
*/
void BFEnhanceGreen(void) 
{
	unsigned char Temp;
	xdata unsigned short i;

	Temp = ReadIIC560(0x3CC) & 0xFD;
	//green/blue enhance
    WriteIIC560(0x3CC,Temp); 
	WriteIIC560(0x3CD,0x02);
	WriteIIC560(0x3CE,0x07);
	i = ucBFGreenMore;
	i = (i>>1)+0x40;
    WriteIIC560(0x3CF,i);
    WriteIIC560(0x3CF,ucBFGreenMore);
	WriteIIC560(0x3CF,i);
    WriteIIC560(0x3CC,Temp | 0x02);
}

void BFEnhanceBlue(void) 
{
	unsigned char Temp;
	xdata unsigned short i;
	
	Temp = ReadIIC560(0x3CC) & 0xFD;
	//green/blue enhance
    WriteIIC560(0x3CC,Temp); 
	WriteIIC560(0x3CD,0x02);
	WriteIIC560(0x3CE,0x0F);
	i = ucBFBlueMore;
	i = (i>>1)+0x40;
	WriteIIC560(0x3CF,i);
    WriteIIC560(0x3CF,ucBFBlueMore);
	WriteIIC560(0x3CF,i);
	WriteIIC560(0x3CC,Temp | 0x02);
}


