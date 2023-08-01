#include "OSD_Tab.H"
#include "osd.H"
#include "OSD_LF.H"
#include "ram.H"
#include "NT686xx_MCU_REG.H"
#include "NT686xx_SC_REG.H"
#include "scaler.H"
#include "modeHandle.H"
#include <stdio.H>
#include <string.H>
#include "BFControl.H"
#include "MIS.H"


/*****************************************************************************
                                Light Frame OSD
 *****************************************************************************/

void ShowLFMainMenu(void)
{
unsigned char i;
	ucOSDType = LF_MAIN_MENU;
	
	OsdInit(LF_OSD_WIDTH,LF_OSD_HIGHT);
	
	ShowTitleGradient();
	usFontIndex = 32;
	ucStrAlignment = 2;
	ucStrWidth = ucOSDWidth;
	WriteArialFont(BrightModeStrTab);
	WriteXY_String(0,0,1);

	ucStrAlignment = 0;
	for(i=0; i<NUM_LF_MODE; i++){
		WriteArialFont(LTMItemStrTab[ucLanguage * NUM_LF_MODE + i]);
		WriteXY_String(0, 3, i*2+4);
	}
	
	SelectLFMITM();

	OSD_ON();
	
}


#ifndef BF_MOVING_WINDOW
static idata unsigned char ucLFDemoDir;
static idata unsigned char ucLFDemoPos;
static idata unsigned char ucTimer2ShowBKStatus;
#endif
void ShowLFDemoOSD(void)
{
	unsigned short OSD_RBx,OSD_RBy;
	OSD_RBx = 0x58;
	OSD_RBy = (PanelHeight - (LF_CHAR_Height * 3 * 2));
	ucOSDType = LFDEMO;
#if PanelWidth==1680
	ucOSDWidth = 43;
#else
	ucOSDWidth = 35;
#endif
	ucStrAlignment = 0;
	//usFontIndex = 1;
	usFontIndex = 0x90;
	
	WriteIIC560(OSD_CTRL1,0x00);
	WriteIIC560(WIN_SEL,0x00);
	Sleep(20);
	WriteIIC560(VHGLOB_ZMRNG,0xAA);
	WriteIIC560(OSD_ZOOM_CTL,0x03);

	WriteWordIIC560(OSD_HS_LI,OSD_RBx);
	WriteIIC560(OSD_HW,ucOSDWidth-1);

	WriteWordIIC560(OSD_VS_LI,OSD_RBy);
	WriteIIC560(OSD_VH,1);
	
	WriteWordIIC560(OSD_FC_ATTR_LSB,LFDemoStrColor);
	WaitSetup(4);
	ClearOSD();
	
	if(ucLFMode == LF_MODE_OFF){
		WriteArialFont(LF_DEMO_StrTab[0]);
		WriteXY_String(1,0,1);
	}
	else{
		WriteArialFont(LF_DEMO_StrTab[2]);
		WriteXY_String(1,0,1);
	}

	WriteArialFont(LF_DEMO_StrTab[3]);
#if PanelWidth==1680
	WriteXY_String(1,33,1);
#else
	WriteXY_String(1,21,1);
#endif
	
	OSD_ON();

	//
#ifndef BF_MOVING_WINDOW
	ucLFDemoDir = 0;
	ucLFDemoPos = 0x58;
	ucLFDemoTimer = 100;
	ucTimer2ShowBKStatus = 20;
#endif
}

#ifdef BF_MOVING_WINDOW
/*
void ShowBKStatus(void)
{
	if (ucLFDemoTimer != 0) return;
	ucLFDemoTimer = 10;
	if (ucTimer2ShowBKStatus == 0)
	{
		ucTimer2ShowBKStatus = 20;
		ShowNum(0,15,1, ((float)(iCurDynBk - ucMinBrightness) * 100 / (ucMaxBrightness - ucMinBrightness) + 0.5));
	}
	else
		ucTimer2ShowBKStatus--;
}
*/
#else
void MoveLFDemoOSD(void)
{
	if (ucLFDemoTimer != 0) return;
	ucLFDemoTimer = 10;
	if (ucTimer2ShowBKStatus == 0)
	{
		ucTimer2ShowBKStatus = 20;
		ShowNum(0,15,1, ((float)(iCurDynBk - ucMinBrightness) * 100 / (ucMaxBrightness - ucMinBrightness) + 0.5));
	}
	else
		ucTimer2ShowBKStatus--;
	if (ucLFDemoDir == 0)
	{
		ucLFDemoPos++;
		if (ucLFDemoPos > 0xb0) 
		{
			ucLFDemoPos = 0xb0;
			ucLFDemoDir = 1;
		}
	}
	else
	{
		ucLFDemoPos--;
		if (ucLFDemoPos > 0xb0) 
		{
			ucLFDemoPos = 0x00;
			ucLFDemoDir = 0;
		}
	}

	WriteWordIIC560(OSD_HS_LI, (unsigned short)ucLFDemoPos);
}
#endif
