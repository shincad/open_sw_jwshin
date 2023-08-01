#include "RAM.H"
#include "board.H"
#include "OSD.H"
#include "Scaler.H"
#include "IIC.H"
#include "UserAdj.H"
#include "AutoAdj.H"
#include "PANEL.H"
#include "NT686xx_MCU_REG.H"
#include "MCU.H"
#include "OSD_TAB.H"
#include "ModeHandle.H"
#include "sRGB.H"
//#include "stdio.H"
#include "ctype.H"
#include "NT686xx_SC_REG.H"
#include "NVRAM.H"
#include "Mis.H"
#include "ROM_Map.H"
#include "Factory.H"
#include "BFControl.H"
#include "smartbright.H"


xdata enum OSDTYPE		ucOSDType;
xdata enum OSDLevel_1	ucOSDLvl1_Cursor;
xdata unsigned char	ucOSDLvl2_Cursor;
xdata unsigned char	ucOSDLvl3_Cursor;

xdata unsigned char glob_buff[20];

void LoadFont(void)
{
code unsigned char PaletteTab[]={
	(unsigned char)(60*2+3), (unsigned char)((60*2+3)>>8),0xd0,0x00,0x00,
//
	(unsigned char)BLACK,(unsigned char)(BLACK>>8),
	(unsigned char)GREEN,(unsigned char)(GREEN>>8),
	(unsigned char)RED,(unsigned char)(RED>>8),
	(unsigned char)BLUE,(unsigned char)(BLUE>>8),
	(unsigned char)CYAN,(unsigned char)(CYAN>>8),
	(unsigned char)MAGENTA,(unsigned char)(MAGENTA>>8),
	(unsigned char)YELLOW,(unsigned char)(YELLOW>>8),
	(unsigned char)WHITE,(unsigned char)(WHITE>>8),
	(unsigned char)TBLACK,(unsigned char)(TBLACK>>8),
	(unsigned char)TRED, (unsigned char)(TRED>>8),
	(unsigned char)TGREEN,(unsigned char)(TGREEN>>8),
	(unsigned char)TBLUE,(unsigned char)(TBLUE>>8),
	(unsigned char)TCYAN,(unsigned char)(TCYAN>>8),
	(unsigned char)LF_COLOR,(unsigned char)(LF_COLOR>>8),
	(unsigned char)TYELLOW,(unsigned char)(TYELLOW>>8),
	(unsigned char)GRAY,(unsigned char)(GRAY>>8),


////////////////////////////////////////////Four Bit Palette////////////////////////////////////////////
//[0]//0x10
(unsigned char)0x0410, (unsigned char)(0x0410>>8),
(unsigned char)0xFFFF, (unsigned char)(0xFFFF>>8),
(unsigned char)0x001F, (unsigned char)(0x001F>>8),
(unsigned char)0xFFE0, (unsigned char)(0xFFE0>>8),
(unsigned char)0x0000, (unsigned char)(0x0000>>8),
(unsigned char)0xC5F8, (unsigned char)(0xC5F8>>8),
(unsigned char)0x0010, (unsigned char)(0x0010>>8),
(unsigned char)0x07FF, (unsigned char)(0x07FF>>8),
(unsigned char)0x07E0, (unsigned char)(0x07E0>>8),
(unsigned char)0xF81F, (unsigned char)(0xF81F>>8),
(unsigned char)0xF800, (unsigned char)(0xF800>>8),
(unsigned char)0xFFF0, (unsigned char)(0xFFF0>>8),
(unsigned char)0xC618, (unsigned char)(0xC618>>8),
(unsigned char)0x8400, (unsigned char)(0x8400>>8),
(unsigned char)0x8410, (unsigned char)(0x8410>>8),
(unsigned char)0x8010, (unsigned char)(0x8010>>8),

//[0]//0x20
(unsigned char)0x0410, (unsigned char)(0x0410>>8),
(unsigned char)0xC618, (unsigned char)(0xC618>>8),
(unsigned char)0xdf1e, (unsigned char)(0xdf1e>>8),
(unsigned char)0xFFE0, (unsigned char)(0xFFE0>>8),
(unsigned char)0x0000, (unsigned char)(0x0000>>8),
(unsigned char)0xC5F8, (unsigned char)(0xC5F8>>8),
(unsigned char)0x0010, (unsigned char)(0x0010>>8),
(unsigned char)0x07FF, (unsigned char)(0x07FF>>8),
(unsigned char)0x07E0, (unsigned char)(0x07E0>>8),
(unsigned char)0xF81F, (unsigned char)(0xF81F>>8),
(unsigned char)0xF800, (unsigned char)(0xF800>>8),
(unsigned char)0xFFF0, (unsigned char)(0xFFF0>>8),
(unsigned char)0xC618, (unsigned char)(0xC618>>8),
(unsigned char)0x8400, (unsigned char)(0x8400>>8),
(unsigned char)0x8410, (unsigned char)(0x8410>>8),
(unsigned char)0x8010, (unsigned char)(0x8010>>8),

////////////////////////////////////////////Two Bit Palette////////////////////////////////////////////
//[0]//0x30
(unsigned char)0x0410, (unsigned char)(0x0410>>8),
(unsigned char)0xFFFF, (unsigned char)(0xFFFF>>8),
(unsigned char)0x001F, (unsigned char)(0x001F>>8),
(unsigned char)0xFFE0, (unsigned char)(0xFFE0>>8),

//[1]//0x34
(unsigned char)0x0410, (unsigned char)(0x0410>>8),
(unsigned char)0xFFFF, (unsigned char)(0xFFFF>>8),
(unsigned char)0x001F, (unsigned char)(0x001F>>8),
(unsigned char)0x0000, (unsigned char)(0x0000>>8),

//[1]//0x34
(unsigned char)0x0410, (unsigned char)(0x0410>>8),
(unsigned char)0xC618, (unsigned char)(0xC618>>8),
(unsigned char)0xdf1e, (unsigned char)(0xdf1e>>8),
(unsigned char)0x0000, (unsigned char)(0x0000>>8),

};
//frame size = 32x17 = 544
//one bit size = (188)x18/2 = 1692
//two bit size = 8*18 = 144
//four bit size= 22*18*2=792
	WriteWordIIC560(OSD_FONT1B_ADDR_LI,544);	//one bit start addr
	WriteWordIIC560(OSD_FONT2B_ADDR_LI,544+1264);		//two bit start addr
	WriteWordIIC560(OSD_FONT4B_ADDR_LI,544+1264+144);	//four bit start addr
	
	WriteSequenceScaler(0xe0,PaletteTab);
	WriteSequenceScaler(0xe0,oneBitFont);

	

	WriteSequenceScaler(0xe0,MainIconTowBitFont);
	WriteSequenceScaler(0xe0,MainIconFourBitFont);
}

void OsdInit(unsigned char w,unsigned char h)
{
unsigned char tempHP,tempVP;
	WriteIIC560(OSD_CTRL1,0x00);
	WriteIIC560(WIN_SEL,0x00);
	ucOSDWidth = w;
	ucOSDHeight = h;

	if(bFactoryMode && (ucOSDType == MAIN_MENU ||ucOSDType == FACTORY)){
		tempHP = 0;
		tempVP = 100;
	}
	else if(ucOSDType < DIRECT_MENU){
		tempHP = ucOSDXPos;
		tempVP = ucOSDYPos;
	}
	else if(ucOSDType == LF_MAIN_MENU){
		tempHP = 50;
		tempVP = 0;
	}
	else{
		tempHP = 50;
		tempVP = 50;
	}

	SetPosition(tempHP,tempVP);

	//2004-01-10 for power sequence
	if(bBGMode == FALSE)
		WaitSetup(4);
	else
		Sleep(40);

	if(ucOSDType == FACTORY){
		WriteWordIIC560(OSD_FC_ATTR_LSB, FactoryColorW);
	}
	else if(ucOSDType==MAIN_MENU){
		WriteWordIIC560(OSD_FC_ATTR_LSB,MainFrameColor);
	}
	else{
		WriteWordIIC560(OSD_FC_ATTR_LSB, LeftFrameColor);
	}
	
	ClearOSD();

	if(((ucOSDType >= LOCK_MSG) && (ucOSDType <= OUT_RANGE)) && (ucOSDType != AUTO_SIGNAL)){
		ShowTitleGradient();

		usFontIndex = 32;
		ucStrAlignment = 2;
		ucStrWidth = ucOSDWidth;
		//---------------- +jwshin 120224
		if(ucOSDType == POWER_ON_LOGO)
		{
			WriteArialFont(MonSel_MainTab[0]);
		}
		//-----------------------------------------
		else
		{	
			WriteArialFont(AttentionStrTab[ucLanguage]);
		}
		WriteXY_String(0,0,1);
	}
}

void ShowTitleGradient(void)
{
unsigned char i;
	for(i=0; i<3; i++){
		FillLineAttr(0,i,ucOSDWidth, TitleTextColor);
	}
	WriteIIC560(WIN_SEL,0x07);
	WriteIIC560(WIN_HS,0);
	WriteIIC560(WIN_HE,ucOSDWidth-1);
	WriteIIC560(WIN_VS,0);
	WriteIIC560(WIN_VE,2);
	WriteIIC560(WIN_SDCL,iTGREEN);
	WriteIIC560(OSD_WIN_GRADIENT_CTRL1,0x0e);
	WriteIIC560(OSD_WIN_GRADIENT_CTRL2,0x11);
	WriteIIC560(WIN_SEL,0x80);
}

void SourceMenu(void)
{
	ucOSDType = DIRECT_MENU;
	ucOSDLvl1_Cursor = mDirect_Source;
	
	OsdInit(OSD_SRC_W,OSD_SRC_H);

	ShowTitleGradient();
	usFontIndex = 32;
	ucStrAlignment = 2;
	ucStrWidth = ucOSDWidth;

	WriteArialFont(InputStrTab[ucLanguage]);
	WriteXY_String(0,0,1);
	
	WriteArialFont(VGA_StrTab[ucLanguage]);
	WriteXY_String(1,0,4);
	
	WriteArialFont(DVI_StrTab[ucLanguage]);
	WriteXY_String(1,0,6);

	WriteArialFont(HDMI_StrTab[ucLanguage]);
	WriteXY_String(1,0,8);

	WriteArialFont(VIDEO_StrTab[ucLanguage]);
	WriteXY_String(1,0,10);

	ucOSDLvl2_Cursor = ucPowerStatus & ~SoftPowerOnFlag;
	SelectLFMITM();

	OSD_ON();
}

void ShowDirectVolumeMenu(void)
{
	ucOSDType = DIRECT_MENU;
	ucOSDLvl1_Cursor = mDirect_Volume;

	OsdInit(OSD2_WIDTH,OSD2_HIGHT);
	
	ShowTitleGradient();
	usFontIndex = 32;
	ucStrWidth = ucOSDWidth;
	ucStrAlignment = 2;
	WriteArialFont(VolumeStrTab[ucLanguage]);
	WriteXY_String(0,0,1);
	
	if(bMute){
		ucStrAlignment = 0;
		ucStrWidth = 4;
		WriteWordIIC560(OSD_FC_ATTR_LSB,DirectWarningColor);
		WriteArialFont(MuteTab[ucLanguage]);
		WriteXY_String(1,11,3);
	}
	
	ShowVolume();
	OSD_ON();
}

void ShowVolume(void)
{
	WriteWordIIC560(OSD_FC_ATTR_LSB,SliderColor);
	ShowSliderBar(5,5, ucVolume);
	ShowNum(0,11,6, ucVolume);
}

void ShowDirectBrightnessMenu(void)
{
	ucOSDType = DIRECT_MENU;
	ucOSDLvl1_Cursor = mDirect_Brightness;

	OsdInit(OSD2_WIDTH,OSD2_HIGHT);

	ShowTitleGradient();

	usFontIndex = 32;
	ucStrWidth = ucOSDWidth;
	ucStrAlignment = 2;
	WriteArialFont(BrightnessStrTab[ucLanguage]);
	WriteXY_String(0,0,1);
	
	ShowBrightness();
	if(ucColorTemperature == COLOR_SRGB){
		ucStrAlignment = 0;
		ucStrWidth = 1;
		WriteWordIIC560(OSD_FC_ATTR_LSB,DirectWarningColor);
		WriteArialFont(sRGBWarningStrTab[ucLanguage]);
		WriteXY_String(1,5,6);
		WriteArialFont(sRGBWarningStrTab[LANG_NUM+ucLanguage]);
		WriteXY_String(1,5,7);
	}
	
	OSD_ON();
}

void MainOSD(void)
{
code unsigned char MainIcon[10][12]={
	11,1,1,
	0x00,(unsigned char)MainIcon4Color1,(unsigned char)(MainIcon4Color1>>8),
	0x01,(unsigned char)MainIcon4Color1,(unsigned char)(MainIcon4Color1>>8),
	0x02,(unsigned char)MainIcon4Color1,(unsigned char)(MainIcon4Color1>>8),
	11,1,2,
	0x03,(unsigned char)MainIcon4Color1,(unsigned char)(MainIcon4Color1>>8),
	0x00,(unsigned char)MainIcon16Color1,(unsigned char)(MainIcon16Color1>>8),
	0x04,(unsigned char)MainIcon4Color1,(unsigned char)(MainIcon4Color1>>8),
	11,1,4,
	0x05,(unsigned char)MainIcon4Color2,(unsigned char)(MainIcon4Color2>>8),
	0x01,(unsigned char)MainIcon16Color1,(unsigned char)(MainIcon16Color1>>8),
	0x06,(unsigned char)MainIcon4Color2,(unsigned char)(MainIcon4Color2>>8),
	11,1,5,
	0x02,(unsigned char)MainIcon16Color1,(unsigned char)(MainIcon16Color1>>8),
	0x03,(unsigned char)MainIcon16Color1,(unsigned char)(MainIcon16Color1>>8),
	0x04,(unsigned char)MainIcon16Color1,(unsigned char)(MainIcon16Color1>>8),
	11,1,7,
	0x05,(unsigned char)MainIcon16Color1,(unsigned char)(MainIcon16Color1>>8),
	0x06,(unsigned char)MainIcon16Color1,(unsigned char)(MainIcon16Color1>>8),
	0x07,(unsigned char)MainIcon16Color1,(unsigned char)(MainIcon16Color1>>8),
	11,1,8,
	0x08,(unsigned char)MainIcon16Color1,(unsigned char)(MainIcon16Color1>>8),
	0x09,(unsigned char)MainIcon16Color1,(unsigned char)(MainIcon16Color1>>8),
	0x0A,(unsigned char)MainIcon16Color1,(unsigned char)(MainIcon16Color1>>8),
	11,1,10,
	0x07,(unsigned char)MainIcon4Color2,(unsigned char)(MainIcon4Color2>>8),
	0x0B,(unsigned char)MainIcon16Color1,(unsigned char)(MainIcon16Color1>>8),
	0x0C,(unsigned char)MainIcon16Color1,(unsigned char)(MainIcon16Color1>>8),
	11,1,11,
	0x0D,(unsigned char)MainIcon16Color1,(unsigned char)(MainIcon16Color1>>8),
	0x0E,(unsigned char)MainIcon16Color1,(unsigned char)(MainIcon16Color1>>8),
	0x0F,(unsigned char)MainIcon16Color1,(unsigned char)(MainIcon16Color1>>8),
	11,1,13,
	0x10,(unsigned char)MainIcon16Color1,(unsigned char)(MainIcon16Color1>>8),
	0x11,(unsigned char)MainIcon16Color1,(unsigned char)(MainIcon16Color1>>8),
	0x12,(unsigned char)MainIcon16Color1,(unsigned char)(MainIcon16Color1>>8),
	11,1,14,
	0x13,(unsigned char)MainIcon16Color1,(unsigned char)(MainIcon16Color1>>8),
	0x14,(unsigned char)MainIcon16Color1,(unsigned char)(MainIcon16Color1>>8),
	0x15,(unsigned char)MainIcon16Color1,(unsigned char)(MainIcon16Color1>>8),
};
code unsigned char MainIconDisable[2][12]={
	11,1,4,
	0x05,(unsigned char)MainIcon4Color3,(unsigned char)(MainIcon4Color3>>8),
	0x01,(unsigned char)MainIcon16Color2,(unsigned char)(MainIcon16Color2>>8),
	0x06,(unsigned char)MainIcon4Color3,(unsigned char)(MainIcon4Color3>>8),
	11,1,5,
	0x02,(unsigned char)MainIcon16Color2,(unsigned char)(MainIcon16Color2>>8),
	0x03,(unsigned char)MainIcon16Color2,(unsigned char)(MainIcon16Color2>>8),
	0x04,(unsigned char)MainIcon16Color2,(unsigned char)(MainIcon16Color2>>8),
};
unsigned char i;
	ucOSDLvl1_Cursor = 0;
	ucOSDLvl2_Cursor = 0;

	OsdInit(OSD_MAIN_WIDTH,OSD_MAIN_HEIGHT);

	for(i=0; i<3; i++){
		FillLineAttr(5,2+i,25, TitleTextColor);
	}
	for(i=0; i<8; i++){
		FillLineAttr(5,5+i,25, SubFrameColor);
	}

	WriteIIC560(WIN_SEL,0x07);
	WriteIIC560(WIN_HS,0);
	WriteIIC560(WIN_HE,31);
	WriteIIC560(WIN_VS,0);
	WriteIIC560(WIN_VE,16);
	WriteIIC560(WIN_SDCL,iTCYAN);
	WriteIIC560(OSD_WIN_GRADIENT_CTRL1,0x1e);
	WriteIIC560(OSD_WIN_GRADIENT_CTRL2,0x11);

	WriteIIC560(WIN_SEL,0x06);
	WriteIIC560(WIN_HS,5);
	WriteIIC560(WIN_HE,29);
	WriteIIC560(WIN_VS,2);
	WriteIIC560(WIN_VE,4);
	WriteIIC560(WIN_SDCL,iTGREEN);
	WriteIIC560(OSD_WIN_GRADIENT_CTRL1,0x0e);
	WriteIIC560(OSD_WIN_GRADIENT_CTRL2,0x11);

	WriteIIC560(WIN_SEL,0x05);
	WriteIIC560(WIN_HS,5);
	WriteIIC560(WIN_HE,29);
	WriteIIC560(WIN_VS,5);
	WriteIIC560(WIN_VE,12);
	WriteIIC560(WIN_SDCL,iWHITE);
	WriteIIC560(OSD_WIN_GRADIENT_CTRL1,0xee);
	WriteIIC560(OSD_WIN_GRADIENT_CTRL2,0x22);
	WriteIIC560(WIN_SEL,0xe0);

	for(i=0; i<10; i++){
		if(((i == 2)||(i == 3))&&((ucSource == mSource_DVI)||(ucSource == mSource_HDMI)))
			WriteColorIcon(MainIconDisable[i-2]);
		else
			WriteColorIcon(MainIcon[i]);
	}

	SelectMainIcon();
	usFontIndex = 100;
	ShowResolution(15,14);
	ShowSerialNo(15,15);					// +jwshin 111208		
	SetTransparency();

}

void WriteColorIcon(unsigned char *p)
{
#if NT68665
unsigned char ch,i,l;
unsigned short m;
	CheckRegPage(0x0e0);
/* start bit */
	IIC_Start();
/* transmit data */
	WriteByte(SCALER_I2C_ADDR);
	WriteByte(0xe0);
	WriteByte(0x80);
	m = p[2] * ucOSDWidth + p[1];
	ch = (unsigned char)m;
	WriteByte(ch);
	ch = (unsigned char)(m >> 8);
	WriteByte(ch);
	l = p[0] + 1;
	for(i=3; i<l; i++){
		ch = p[i];
		WriteByte(ch);
	}
/* stop bit */
	IIC_Stop();
#else
unsigned char volatile *pBus;
unsigned char i,l;
unsigned short m;
	SC_RegPage = 0x00;
	pBus = &SC_INDEX_CTRL;
	*pBus = 0x80;
	pBus++;
	m = p[2] * ucOSDWidth + p[1];
	*pBus = (unsigned char)m;
	pBus++;
	*pBus = (unsigned char)(m >> 8);
	pBus++;
	l = p[0] + 1;
	for(i=3; i<l; i++){
		*pBus = p[i];
	}

#endif
}

void MainIconWinOff(void)
{
	unsigned char WinControl;
	WinControl = ReadIIC560(OSD_CTRL1) & ~MainIconWinCtrl;
	WriteIIC560(OSD_CTRL1,WinControl);
}

void SelectMainIconWin(void)
{
	unsigned char WinSelect;
	WinSelect = ReadIIC560(WIN_SEL) & 0xf8;
	WriteIIC560(WIN_SEL,WinSelect | MainIconWinSel);	//windows 8 control
}

void MainIconWinOn(void)
{
	unsigned char WinControl;
	WinControl = ReadIIC560(OSD_CTRL1) | MainIconWinCtrl;
	WriteIIC560(OSD_CTRL1,WinControl);
}

void SubIconWinOff(void)
{
	unsigned char WinControl;
	WinControl = ReadIIC560(OSD_CTRL1) & ~SubIconWinCtrl;
	WriteIIC560(OSD_CTRL1,WinControl);
}

void SelectSubIconWin(void)
{
	unsigned char WinSelect;
	WinSelect = ReadIIC560(WIN_SEL) & 0xf8;
	WriteIIC560(WIN_SEL,WinSelect | SubIconWinSel);	//windows 8 control
}

void SubIconWinOn(void)
{
	unsigned char WinControl;
	WinControl = ReadIIC560(OSD_CTRL1) | SubIconWinCtrl;
	WriteIIC560(OSD_CTRL1,WinControl);
}

void OSD_ON(void)
{
	unsigned char WinControl;
	WinControl = ReadIIC560(OSD_CTRL1) | BIT_0;
	WriteIIC560(OSD_CTRL1,WinControl);
}

void SelectMainIcon(void)
{
	MainIconWinOff();
	SelectMainIconWin();
	WriteIIC560(WIN_HS,1);
	WriteIIC560(WIN_HE,3);
	WriteIIC560(WIN_VS,ucOSDLvl1_Cursor*3+0x01);
	WriteIIC560(WIN_VE,ucOSDLvl1_Cursor*3+0x02);
	WriteIIC560(WIN_CL,iTCYAN);
	WriteIIC560(OSD_WIN_ATTR,0x80);
	WriteIIC560(WIN_BL_HWID,0x01);
	WriteIIC560(WIN_BL_RCL,iRED);
	WriteIIC560(WIN_BL_LCL,iRED);
	MainIconWinOn();


	usFontIndex = 32;
	ucStrAlignment = 2;
	ucStrWidth = ucOSDWidth - 7;
	WriteWordIIC560(OSD_FC_ATTR_LSB,TitleTextColor);
	WriteXY_Line(5, 3, ucStrWidth, 0x00);
	WriteArialFont(MainMenuStrTab[ucOSDLvl1_Cursor*LANG_NUM+ucLanguage]);
	WriteXY_String(0, 5, 3);

	ShowSubMenu();
}

void ShowSubMenu(void)
{
code unsigned char FactoryStr[]={7,"Factory"};
unsigned char i;
	usFontIndex = 48;
	ucStrAlignment = 2;
	ucStrWidth = ucOSDWidth - 7;
	WriteWordIIC560(OSD_FC_ATTR_LSB,SubFrameColor);
	for(i=5; i<13; i++)
		WriteXY_Line(5, i, ucStrWidth, 0x00);
	WriteWordIIC560(OSD_FC_ATTR_LSB,MainFrameColor);
	WriteXY_Line(5, 13, ucStrWidth, 0x00);
	switch(ucOSDLvl1_Cursor){
	case mLUMINANCE:
		WriteArialFont(BrightnessStrTab[ucLanguage]);
		WriteXY_String(0, 5, 6);
		WriteArialFont(ContrastStrTab[ucLanguage]);
		WriteXY_String(0, 5, 8);
		if(ucSource > mSource_HDMI){
			WriteArialFont(SaturationStrTab[ucLanguage]);
			WriteXY_String(0, 5, 10);
			WriteArialFont(TintStrTab[ucLanguage]);
			WriteXY_String(0, 5, 12);
		}
		if(bFactoryMode == TRUE){
			WriteArialFont(FactoryStr);
			WriteXY_String(0,5,13);
		}
		break;
	case mPICTURE:
		WriteArialFont(PhaseStrTab[ucLanguage]);
		WriteXY_String(0, 5, 6);
		WriteArialFont(ClockStrTab[ucLanguage]);
		WriteXY_String(0, 5, 8);
		WriteArialFont(HPosStrTab[ucLanguage]);
		WriteXY_String(0, 5, 10);
		WriteArialFont(VPosStrTab[ucLanguage]);
		WriteXY_String(0, 5, 12);
		break;
	case mCOLOR:
		WriteArialFont(ColorTempStrTab[ucLanguage]);
		WriteXY_String(0, 5, 6);
		if(ucColorTemperature == COLOR_USER){
			WriteWordIIC560(OSD_FC_ATTR_LSB,SubFrameColor);
		}
		else{
			WriteWordIIC560(OSD_FC_ATTR_LSB,DisableColor);
		}
		WriteArialFont(RedStrTab[ucLanguage]);
		WriteXY_String(1, 5, 8);
		WriteArialFont(GreenStrTab[ucLanguage]);
		WriteXY_String(1, 5, 10);
		WriteArialFont(BlueStrTab[ucLanguage]);
		WriteXY_String(1, 5, 12);
		break;
	case mOSDSETTING:
		WriteArialFont(HorizontalStrTab[ucLanguage]);
		WriteXY_String(0, 5, 6);
		WriteArialFont(VerticalStrTab[ucLanguage]);
		WriteXY_String(0, 5, 8);
		WriteArialFont(TransparencyStrTab[ucLanguage]);
		WriteXY_String(0, 5, 10);
		WriteArialFont(OSDTimeStrTab[ucLanguage]);
		WriteXY_String(0, 5, 12);
		break;
	case mSETUP:
		WriteArialFont(LanguageStrTab[ucLanguage]);
		WriteXY_String(0, 5, 6);
		WriteArialFont(MuteTab[ucLanguage]);
		WriteXY_String(0, 5, 7);
		WriteArialFont(InputStrTab[ucLanguage]);
		WriteXY_String(0, 5,8);
		WriteArialFont(DCR_StrTab[ucLanguage]);
		WriteXY_String(0, 5,9);
		i = 10;
#if _Enable_OD_ == ON
		WriteArialFont(OverDriverTab[ucLanguage]);
		WriteXY_String(0, 5, i);
		i++;
#endif
		WriteArialFont(ResetStrTab[ucLanguage]);
		WriteXY_String(0, 5, i);
		break;
	}
}

void SelectSubItem(void)
{
	SubIconWinOff();
	SelectSubIconWin();
	WriteIIC560(WIN_HS,5);
	WriteIIC560(WIN_HE,29);
	if((ucOSDLvl2_Cursor == mFactory)&&(ucOSDLvl1_Cursor == mLUMINANCE)){
		WriteIIC560(WIN_VS,13);
		WriteIIC560(WIN_VE,13);
		WriteIIC560(WIN_CL,iTCYAN);
	}
	else{
		if(ucOSDLvl1_Cursor == mSETUP){
			WriteIIC560(WIN_VS,ucOSDLvl2_Cursor+0x06);
			WriteIIC560(WIN_VE,ucOSDLvl2_Cursor+0x06);
		}
		else{
			WriteIIC560(WIN_VS,ucOSDLvl2_Cursor*2+0x06);
			WriteIIC560(WIN_VE,ucOSDLvl2_Cursor*2+0x06);
		}
		WriteIIC560(WIN_CL,iWHITE);
	}
	WriteIIC560(OSD_WIN_ATTR,0x80);
	WriteIIC560(WIN_BL_HWID,0x01);
	WriteIIC560(WIN_BL_RCL,iMAGENTA);
	WriteIIC560(WIN_BL_LCL,iMAGENTA);
	SubIconWinOn();
}

void ShowAdjustMenu(void)
{
unsigned char i;
	usFontIndex = 48;
	ucStrAlignment = 0;
	ucStrWidth = ucOSDWidth - 7;
	WriteWordIIC560(OSD_FC_ATTR_LSB,SubFrameColor);
	for(i=5; i<13; i++)
		WriteXY_Line(5, i, ucStrWidth, 0x00);
	SubIconWinOff();
	switch(ucOSDLvl1_Cursor){
	case mLUMINANCE:
		switch(ucOSDLvl2_Cursor){
		case mLuminance_Brightness:
			WriteArialFont(BrightnessStrTab[ucLanguage]);
			WriteXY_String(0, 5, 6);
			ShowBrightness();
			if(ucColorTemperature == COLOR_SRGB){
				ucStrAlignment = 0;
				ucStrWidth = 1;
				WriteWordIIC560(OSD_FC_ATTR_LSB,WarningColor);
				WriteArialFont(sRGBWarningStrTab[ucLanguage]);
				WriteXY_String(1,5,11);
				WriteArialFont(sRGBWarningStrTab[LANG_NUM+ucLanguage]);
				WriteXY_String(1,5,12);
			}
			break;
		case mLuminance_Contrast:
			WriteArialFont(ContrastStrTab[ucLanguage]);
			WriteXY_String(0, 5, 6);
			ShowContrast();
			break;
		case mLuminance_Saturation:
			WriteArialFont(SaturationStrTab[ucLanguage]);
			WriteXY_String(0, 5, 6);
			ShowSaturation();
			break;
		case mLuminance_Tint:
			WriteArialFont(TintStrTab[ucLanguage]);
			WriteXY_String(0, 5, 6);
			ShowTint();
			break;
		}
		break;
	case mPICTURE:
		switch(ucOSDLvl2_Cursor){
		case mPicture_Phase:
			WriteArialFont(PhaseStrTab[ucLanguage]);
			WriteXY_String(0, 5, 6);
			ShowPhase();
			break;
		case mPicture_Clock:
			WriteArialFont(ClockStrTab[ucLanguage]);
			WriteXY_String(0, 5, 6);
			ShowClock();
			break;
		case mPicture_HPos:
			WriteArialFont(HPosStrTab[ucLanguage]);
			WriteXY_String(0, 5, 6);
			ShowHP();
			break;
		case mPicture_VPos:
			WriteArialFont(VPosStrTab[ucLanguage]);
			WriteXY_String(0, 5, 6);
			ShowVP();
			break;
		}
		break;
	case mCOLOR:
		switch(ucOSDLvl2_Cursor){
		case mColor_Tempk:
			WriteArialFont(ColorTempStrTab[ucLanguage]);
			WriteXY_String(0, 5, 6);
			ShowColorMenu();
			break;
		case mColor_User_R:
			WriteArialFont(RedStrTab[ucLanguage]);
			WriteXY_String(0, 5, 6);
			ShowRed();
			break;
		case mColor_User_G:
			WriteArialFont(GreenStrTab[ucLanguage]);
			WriteXY_String(0, 5, 6);
			ShowGreen();
			break;
		case mColor_User_B:
			WriteArialFont(BlueStrTab[ucLanguage]);
			WriteXY_String(0, 5, 6);
			ShowBlue();
			break;
		}
		break;
	case mOSDSETTING:
		switch(ucOSDLvl2_Cursor){
		case mOSDSetting_Horizontal:
			WriteArialFont(HorizontalStrTab[ucLanguage]);
			WriteXY_String(0, 5, 6);
			ShowOSD_X();
			break;
		case mOSDSetting_Vertical:
			WriteArialFont(VerticalStrTab[ucLanguage]);
			WriteXY_String(0, 5, 6);
			ShowOSD_Y();
			break;
		case mOSDSetting_Transparency:
			WriteArialFont(TransparencyStrTab[ucLanguage]);
			WriteXY_String(0, 5, 6);
			ShowTransparency();
			break;
		case mOSDSetting_OSDTimeout:
			WriteArialFont(OSDTimeStrTab[ucLanguage]);
			WriteXY_String(0, 5, 6);
			ShowOSD_Timer();
			break;
		}
		break;
	case mSETUP:
		switch(ucOSDLvl2_Cursor){
		case mSetup_Language:
			WriteArialFont(LanguageStrTab[ucLanguage]);
			WriteXY_String(0, 5, 6);
			ShowLanguageMenu();
			break;
		case mSetup_AudioMute:
			WriteArialFont(MuteTab[ucLanguage]);
			WriteXY_String(0, 5, 6);
			ShowOnOffMenu();
			break;
		case mSetup_Input:
			WriteArialFont(InputStrTab[ucLanguage]);
			WriteXY_String(0, 5, 6);
			ShowInputMenu();
			break;
		case mSetup_DCR:
			WriteArialFont(DCR_StrTab[ucLanguage]);
			WriteXY_String(0, 5, 6);
			ucOSDLvl3_Cursor = ucDynBKMode;
			ShowOnOffMenu();
			break;
#if _Enable_OD_ == ON
		case mSetup_OD:
			WriteArialFont(OverDriverTab[ucLanguage]);
			WriteXY_String(0, 5, 6);
			ucOSDLvl3_Cursor = Read24C16(EPADDR_OD_ONOFF);
			ShowOnOffMenu();
			break;
#endif
		case mSetup_Reset:
			WriteArialFont(ResetStrTab[ucLanguage]);
			WriteXY_String(0, 5, 6);
			ShowYesNoMenu();
			break;
		}
		break;
	}
}

void ShowColorMenu(void)
{
unsigned char i,k;
	usFontIndex = 64;
	ucStrAlignment = 2;
	if(ucColorTemperature > 4){
		k = ucColorTemperature - 4;
	}
	else{
		k = 0;
	}
	for(i=0; i<5; i++){
		WriteArialFont(ColorTemp_StrTab[(i+k) * LANG_NUM + ucLanguage]);
		WriteXY_String(0, 5, i+8);
	}
/*
	WriteArialFont(StrTab6500K);
	WriteXY_String(0, 5, 8);
	WriteArialFont(StrTab7500K);
	WriteXY_String(0, 5, 9);
	WriteArialFont(StrTab9300K);
	WriteXY_String(0, 5, 10);
	WriteArialFont(sRGB_StrTab[ucLanguage]);
	WriteXY_String(0, 5, 11);
	WriteArialFont(UserDefineStrTab[ucLanguage]);
	WriteXY_String(0, 5, 12);*/
	SelectColorTemp();
}

void SelectColorTemp(void)
{
unsigned char k;
	if(ucColorTemperature > 4){
		k = 4;
	}
	else{
		k = ucColorTemperature;
	}
	SubIconWinOff();
	SelectSubIconWin();
	WriteIIC560(WIN_HS,5);
	WriteIIC560(WIN_HE,29);
	WriteIIC560(WIN_VS,k+0x08);
	WriteIIC560(WIN_VE,k+0x08);
	WriteIIC560(WIN_CL,iWHITE);
	WriteIIC560(OSD_WIN_ATTR,0x80);
	WriteIIC560(WIN_BL_HWID,0x01);
	WriteIIC560(WIN_BL_RCL,iMAGENTA);
	WriteIIC560(WIN_BL_LCL,iMAGENTA);
	SubIconWinOn();
}

void ShowLanguageMenu(void)
{
/*	
unsigned char i;
	ucStrAlignment = 2;
	ucStrWidth = (ucOSDWidth - 7) / 2;
	for(i=0; i<4; i++){
		WriteArialFont(CountryStrTab[i*2]);
		WriteXY_String(0, 5, i+8);
		WriteArialFont(CountryStrTab[i*2+1]);
		WriteXY_String(0, 17, i+8);
	}

	SelectLanguage();
	*/				// -jwshin 111214
	//--------------- Language 부분은 사용하지 않기 때문에.. Remark..
}

void SelectLanguage(void)
{
unsigned char i;
	i = ucLanguage >> 1;
	SubIconWinOff();
	SelectSubIconWin();
	if((ucLanguage & BIT_0) == 0){
		WriteIIC560(WIN_HS,5);
		WriteIIC560(WIN_HE,16);
	}
	else{
		WriteIIC560(WIN_HS,17);
		WriteIIC560(WIN_HE,29);
	}
	WriteIIC560(WIN_VS,i+0x08);
	WriteIIC560(WIN_VE,i+0x08);
	WriteIIC560(WIN_CL,iWHITE);
	WriteIIC560(OSD_WIN_ATTR,0x80);
	WriteIIC560(WIN_BL_HWID,0x01);
	WriteIIC560(WIN_BL_RCL,iMAGENTA);
	WriteIIC560(WIN_BL_LCL,iMAGENTA);
	SubIconWinOn();
}

void ShowInputMenu(void)
{
	ucStrAlignment = 2;
	WriteArialFont(VGA_StrTab[ucLanguage]);
	WriteXY_String(0, 5, 8);
	WriteArialFont(DVI_StrTab[ucLanguage]);
	WriteXY_String(0, 5, 9);
	WriteArialFont(HDMI_StrTab[ucLanguage]);
	WriteXY_String(0, 5, 10);
	WriteArialFont(VIDEO_StrTab[ucLanguage]);
	WriteXY_String(0, 5, 11);
	ucSource = ucPowerStatus & ~SoftPowerOnFlag;
	SelectInput();
}

void SelectInput(void)
{
	SubIconWinOff();
	SelectSubIconWin();
	WriteIIC560(WIN_HS,5);
	WriteIIC560(WIN_HE,29);
	WriteIIC560(WIN_VS,ucSource+0x08);
	WriteIIC560(WIN_VE,ucSource+0x08);
	WriteIIC560(WIN_CL,iWHITE);
	WriteIIC560(OSD_WIN_ATTR,0x80);
	WriteIIC560(WIN_BL_HWID,0x01);
	WriteIIC560(WIN_BL_RCL,iMAGENTA);
	WriteIIC560(WIN_BL_LCL,iMAGENTA);
	SubIconWinOn();
}

void ShowYesNoMenu(void)
{
	ucStrAlignment = 2;
	WriteArialFont(NoStrTab[ucLanguage]);
	WriteXY_String(0, 5, 8);
	WriteArialFont(YesStrTab[ucLanguage]);
	WriteXY_String(0, 5,10);
	ucOSDLvl3_Cursor = 0;
	SelectYesNo();
}

void SelectYesNo(void)
{
	SubIconWinOff();
	SelectSubIconWin();
	WriteIIC560(WIN_HS,5);
	WriteIIC560(WIN_HE,29);
	WriteIIC560(WIN_VS,ucOSDLvl3_Cursor*2+0x08);
	WriteIIC560(WIN_VE,ucOSDLvl3_Cursor*2+0x08);
	WriteIIC560(WIN_CL,iWHITE);
	WriteIIC560(OSD_WIN_ATTR,0x80);
	WriteIIC560(WIN_BL_HWID,0x01);
	WriteIIC560(WIN_BL_RCL,iMAGENTA);
	WriteIIC560(WIN_BL_LCL,iMAGENTA);
	SubIconWinOn();
}

void ShowOnOffMenu(void)
{
	ucStrAlignment = 2;
	WriteArialFont(OffTab[ucLanguage]);
	WriteXY_String(0, 5, 8);
	WriteArialFont(OnTab[ucLanguage]);
	WriteXY_String(0, 5,10);
	SelectYesNo();
}


void SetOSDAtCenter()
{
//	ucOSDXPos = MCU_DataMap[EPADDR_OSDX];
//	ucOSDYPos = MCU_DataMap[EPADDR_OSDY];
	ucOSDXPos = 50;
	ucOSDYPos = 50;
	SetPosition(ucOSDXPos,ucOSDYPos);
	Write24C16(EPADDR_OSDX, ucOSDXPos);//0x15 = OSD position x
	Write24C16(EPADDR_OSDY, ucOSDYPos);//0x15 = OSD position x
}

void SetPosition(unsigned char x, unsigned char y)
{
#define OSDxy_RBx(w1)	(PanelWidth - (CHAR_Width * (w1)))
#define OSDxy_RBy(h1)	(PanelHeight - (CHAR_Height * (h1))-6)
unsigned short xy;
	xy = (unsigned long)OSDxy_RBx(ucOSDWidth) * x / 100;	//xy = (unsigned long)OSDxy_RBx * ucOSDXPos / 100;
	WriteWordIIC560(OSD_HS_LI,xy);
	WriteIIC560(OSD_HW,ucOSDWidth-1);
	xy = (unsigned long)OSDxy_RBy(ucOSDHeight) * (100 - y) / 100;	//xy = (unsigned long)OSDxy_RBy * (100 - ucOSDYPos) / 100;
	WriteWordIIC560(OSD_VS_LI,xy);
	WriteIIC560(OSD_VH,ucOSDHeight-1);
	WaitSetup(4);
}

void ClearOSD(void)
{
//	bOSDReady = FALSE;
	

	//WriteIIC560(OSD_TRANSLUCENT_CTL,0x1b);
// Clear osd ram
	WriteIIC560(OSD_CODE_FC,0x00);
	WriteIIC560(OSD_CODE_FC_CTL,0x01 );
	//WriteIIC560(OSD_CODE_FC_CTL,0x01 | BIT4 | BIT5);
// Wait for Clear Ready....
	while((ReadIIC560(OSD_CODE_FC_CTL) & BIT_0) != 0){
		CheckModeChange();
	}
	WriteXY_Char(1,0,0,0x00);
}



void OSD_OFF(void)
{
	if(ucSavePointer != svNONE)
		SaveData();		
	if(ucOSDType != OSDOFF){
		SubIconWinOff();
		MainIconWinOff();
		WriteIIC560(OSD_CTRL1,0x00);
		if(ucOSDType == FACTORY){
			LoadFont();
		}
		ucOSDType = OSDOFF;
	}
}



void ShowBrightness()
{
	if(ucOSDType == DIRECT_MENU){
		WriteWordIIC560(OSD_FC_ATTR_LSB,SliderColor);
		ShowSliderBar(5,5, ucBrightness);
		ShowNum(0,11,6, ucBrightness);
	}
	else{
		WriteWordIIC560(OSD_FC_ATTR_LSB,SliderColor);
		ShowNum(0,25,6, ucBrightness);
		ShowSliderBar(10,8, ucBrightness);
	}
}

void ShowContrast()
{	
	WriteWordIIC560(OSD_FC_ATTR_LSB,SliderColor);
	ShowNum(0,25,6, ucContrast);
	ShowSliderBar(10,8, ucContrast);	
}

void ShowSaturation()
{	
	WriteWordIIC560(OSD_FC_ATTR_LSB,SliderColor);
	ShowNum(0,25,6, ucSaturation);
	ShowSliderBar(10,8, ucSaturation);	
}

void ShowTint()
{	
	WriteWordIIC560(OSD_FC_ATTR_LSB,SliderColor);
	ShowNum(0,25,6, ucTint);
	ShowSliderBar(10,8, ucTint);	
}

void ShowPhase()
{
	WriteWordIIC560(OSD_FC_ATTR_LSB,SliderColor);
	ShowNum(0,25,6, ucADCCPhase100Pa);
	ShowSliderBar(10,8, ucADCCPhase100Pa);

}

void ShowClock()
{
unsigned char value;
	value = (usHTotal-usMinClk) * 100 / (usMaxClk-usMinClk);
	WriteWordIIC560(OSD_FC_ATTR_LSB,SliderColor);
	ShowNum(0,25,6, value);
	ShowSliderBar(10,8, value);	
}

void ShowHP()
{
unsigned char value;
	value = (usHPStart-ucMinHP) * 100 / (usMaxHP-ucMinHP);
	WriteWordIIC560(OSD_FC_ATTR_LSB,SliderColor);
	ShowNum(0,25,6, value);
	ShowSliderBar(10,8, value);	
}

void ShowVP()
{
unsigned char value;
	value = (usVPStart-ucMinVP) * 100 / (ucMaxVP-ucMinVP);
	WriteWordIIC560(OSD_FC_ATTR_LSB,SliderColor);
	ShowNum(0,25,6, value);
	ShowSliderBar(10,8, value);	
}

void ShowRed()
{
unsigned char value;
	value = ScalingColorGain(ucR_GainUser);
	WriteWordIIC560(OSD_FC_ATTR_LSB,SliderColor);
	ShowNum(0,25,6, value);
	ShowSliderBar(10,8, value);	
}

void ShowGreen()
{
unsigned char value;
	value = ScalingColorGain(ucG_GainUser);
	WriteWordIIC560(OSD_FC_ATTR_LSB,SliderColor);
	ShowNum(0,25,6, value);
	ShowSliderBar(10,8, value);	
}

void ShowBlue()
{
unsigned char value;
	value = ScalingColorGain(ucB_GainUser);
	WriteWordIIC560(OSD_FC_ATTR_LSB,SliderColor);
	ShowNum(0,25,6, value);
	ShowSliderBar(10,8, value);	
}

void ShowOSD_X()
{
	WriteWordIIC560(OSD_FC_ATTR_LSB,SliderColor);
	ShowNum(0,25,6, ucOSDXPos);
	ShowSliderBar(10,8, ucOSDXPos);

}
void ShowOSD_Y()
{
	WriteWordIIC560(OSD_FC_ATTR_LSB,SliderColor);
	ShowNum(0,25,6, ucOSDYPos);
	ShowSliderBar(10,8, ucOSDYPos);

}
void ShowTransparency()
{
unsigned char value;
	value = ((unsigned short)ucTransparency * 100 + 2) / 4;
	WriteWordIIC560(OSD_FC_ATTR_LSB,SliderColor);
	ShowNum(0,25,6, value);
	ShowSliderBar(10,8, value);
}

void ShowOSD_Timer()
{
unsigned char value;
	value = ((unsigned short)ucOSDTimer * 100 + 30) / 60;
	WriteWordIIC560(OSD_FC_ATTR_LSB,SliderColor);
	ShowNum(0,25,6, ucOSDTimer);
	ShowSliderBar(10,8, value);
}

//---------------- +jwshin 110418

void ShowOSD_Debug(unsigned char Val)
{
	WriteWordIIC560(OSD_FC_ATTR_LSB,SliderColor);
	ShowNum(0,25,6, Val);
	ShowSliderBar(10,8, Val);
}

//---------------------------------------------------



void WriteSequenceScaler(unsigned char addr,unsigned char *p)
{
#if NT68665
unsigned short i,l;
	CheckRegPage(0x0e0);
/* start bit */
	IIC_Start();
/* transmit data */
	WriteByte(SCALER_I2C_ADDR);
	WriteByte(addr);
	l = p[1] * 256;
	l = l + p[0] + 2;
	for(i=2; i<l; i++){
		WriteByte(p[i]);
	}
/* stop bit */
	IIC_Stop();
#else
unsigned short i,l;
unsigned char volatile *pBus;
	SC_RegPage = (unsigned char)(addr>>8);
	pBus = &SC_StarAddress;
	pBus += (unsigned char)addr;
	l = p[1] * 256;
	l = l + p[0] + 2;
	*pBus = p[2];
	pBus++;
	*pBus = p[3];
	pBus++;
	*pBus = p[4];
	pBus++;
	for(i=5; i<l; i++){
		*pBus = p[i];
	}
#endif
}
/*
void WriteStringScaler(unsigned char Attr,unsigned char *p)
{
#if NT68665
unsigned char i,l,ch;
unsigned short m;
	CheckRegPage(0x0e0);

	IIC_Start();

	WriteByte(SCALER_I2C_ADDR);
	WriteByte(0xe0);
	if(Attr == 0)
		WriteByte(0x40);
	else
		WriteByte(0x90);
	m = p[2] * ucOSDWidth + p[1];
	ch = (unsigned char)m;
	WriteByte(ch);
	ch = (unsigned char)(m >> 8);
	WriteByte(ch);
	l = p[0] + 1;
	for(i=3; i<l; i++){
		ch = p[i];
		WriteByte(ch);
	}

	IIC_Stop();
#else
unsigned char i,l;
unsigned char volatile *pBus;
unsigned short m;
	SC_RegPage = 0x00;
	pBus = &SC_INDEX_CTRL;
	if(Attr == 0)
		*pBus = 0x40;
	else
		*pBus = 0x90;
	pBus++;
	m = p[2] * ucOSDWidth + p[1];
	*pBus = (unsigned char)m;
	pBus++;
	*pBus = (unsigned char)(m >> 8);
	pBus++;
	l = p[0] + 1;
	for(i=3; i<l; i++){
		*pBus = p[i];
	}
#endif
}
*/


void WriteXY_Line(unsigned char x,unsigned char y,unsigned char l,unsigned char k)
{
#if NT68665
unsigned char i,ch;
unsigned short m;
	CheckRegPage(0x0e0);
/* start bit */
	IIC_Start();
/* transmit data */
	WriteByte(SCALER_I2C_ADDR);
	WriteByte(0xe0);
	WriteByte(0x90);
	m = y * ucOSDWidth + x;
	ch = (unsigned char)m;
	WriteByte(ch);
	ch = (unsigned char)(m >> 8);
	WriteByte(ch);
	for(i=0; i<l; i++){
		WriteByte(k);
	}
/* stop bit */
	IIC_Stop();
#else
unsigned char i;
unsigned char volatile *pBus;
unsigned short m;
	SC_RegPage = 0x00;
	pBus = &SC_INDEX_CTRL;
	*pBus = 0x90;
	pBus++;
	m = y * ucOSDWidth + x;
	*pBus = (unsigned char)m;
	pBus++;
	*pBus = (unsigned char)(m >> 8);
	pBus++;
	for(i=0; i<l; i++){
		*pBus = k;
	}
#endif
}

void WriteXY_Char(unsigned char Attr,unsigned char x,unsigned char y,unsigned char letter)
{
#if NT68665
unsigned char ch;
unsigned short m;
/* start bit */
	IIC_Start();
/* transmit data */
	WriteByte(SCALER_I2C_ADDR);
	WriteByte(0xe0);
	if(Attr == 0)
		WriteByte(0x40);
	else
		WriteByte(0x90);
	m = y * ucOSDWidth + x;
	ch = (unsigned char)m;
	WriteByte(ch);
	ch = (unsigned char)(m >> 8);
	WriteByte(ch);

	WriteByte(letter);

/* stop bit */
	IIC_Stop();
#else
unsigned char volatile *pBus;
unsigned short m;
	SC_RegPage = 0x00;
	pBus = &SC_INDEX_CTRL;
	if(Attr == 0)
		*pBus = 0x40;
	else
		*pBus = 0x90;
	pBus++;
	m = y * ucOSDWidth + x;
	*pBus = (unsigned char)m;
	pBus++;
	*pBus = (unsigned char)(m >> 8);
	pBus++;
	*pBus = letter;
#endif
}

#if 0
void WriteXY_StrScaler(unsigned char Attr,unsigned char x,unsigned char y,unsigned char *p)
{
#if NT68665
unsigned char i,l,ch;
unsigned short m;
	CheckRegPage(0x0e0);
/* start bit */
	IIC_Start();
/* transmit data */
	WriteByte(SCALER_I2C_ADDR);
	WriteByte(0xe0);
	if(Attr == 0)
		WriteByte(0x40);
	else
		WriteByte(0x90);
	m = (unsigned short)y * ucOSDWidth + x;
	ch = (unsigned char)m;
	WriteByte(ch);
	ch = (unsigned char)(m >> 8);
	WriteByte(ch);
	l = p[0] + 1;
	for(i=1; i<l; i++){
		ch = p[i];
		WriteByte(ch);
	}
/* stop bit */
	IIC_Stop();
#else
unsigned char i,l;
unsigned char volatile *pBus;
unsigned short m;
	SC_RegPage = 0x00;
	pBus = &SC_INDEX_CTRL;
	if(Attr == 0)
		*pBus = 0x40;
	else
		*pBus = 0x90;
	pBus++;
	m = (unsigned short)y * ucOSDWidth + x;
	*pBus = (unsigned char)m;
	pBus++;
	*pBus = (unsigned char)(m >> 8);
	pBus++;
	l = p[0] + 1;
	for(i=1; i<l; i++){
		*pBus = p[i];
	}
#endif
}
#endif

void FillLineAttr(unsigned char x,unsigned char y,unsigned char l,unsigned short Attr)
{
#if NT68665
unsigned char i,ch;
unsigned short m;
	CheckRegPage(0x0e0);
/* start bit */
	IIC_Start();
/* transmit data */
	WriteByte(SCALER_I2C_ADDR);
	WriteByte(0xe0);
	WriteByte(0x70);
	m = y * ucOSDWidth + x;
	ch = (unsigned char)m;
	WriteByte(ch);
	ch = (unsigned char)(m >> 8);
	WriteByte(ch);
	ch = (unsigned char)(Attr>>8);
	for(i=0; i<l; i++){
		//WriteByte((unsigned char) (Attr|0x02));
		WriteByte((unsigned char)Attr);
		WriteByte(ch);
	}
/* stop bit */
	IIC_Stop();
#else
unsigned char i;
unsigned short m;
unsigned char volatile *pBus;
	SC_RegPage = 0x00;
	pBus = &SC_INDEX_CTRL;
	*pBus = 0x70;
	pBus++;
	m = y * ucOSDWidth + x;
	*pBus = (unsigned char)m;
	pBus++;
	*pBus = (unsigned char)(m >> 8);
	pBus++;
	for(i=0; i<l; i++){
		*pBus = (unsigned char)Attr;
		*pBus = (unsigned char)(Attr>>8);
	}
#endif
}

void ShowNum(unsigned char Attr,unsigned char xx,unsigned char yy,unsigned char value)
{
unsigned char i,ch;
unsigned short m;
unsigned char buff[4];
#if !NT68665
unsigned char volatile *pBus;
#endif
//show value
#ifdef NO_PRINT_LIB
	UShortToStr((unsigned short)value, buff, 3);
#else
	sprintf(buff,"%3d",(unsigned short)value);
#endif
#if NT68665
	CheckRegPage(0x0e0);

	IIC_Start();

	WriteByte(SCALER_I2C_ADDR);
	WriteByte(0xe0);
	if(Attr == 0)
		WriteByte(0x40);
	else
		WriteByte(0x90);
	m = yy * ucOSDWidth + xx;
	ch = (unsigned char)m;
	WriteByte(ch);
	ch = (unsigned char)(m >> 8);
	WriteByte(ch);
		
	for(i=0; i<3; i++){
		if ( (ch=buff[i]) == 0x20 )
			WriteByte(0);
		else
			WriteByte(ch-0x28);
	}

	IIC_Stop();
#else
	SC_RegPage = 0x00;
	pBus = &SC_INDEX_CTRL;
	if(Attr == 0)
		*pBus = 0x40;
	else
		*pBus = 0x90;
	pBus++;
	m = yy * ucOSDWidth + xx;
	*pBus = (unsigned char)m;
	pBus++;
	*pBus = (unsigned char)(m >> 8);
	pBus++;
	for(i=0; i<3; i++){
		ch = buff[i];
		if(ch == 0x20)
			*pBus = 0;
		else
			*pBus = ch - 0x28;
	}

#endif
}

void ShowSliderBar(unsigned char xx,unsigned char yy,unsigned char value)
{
#define BarWidth 15
#if NT68665
unsigned char i,k,ch;
unsigned short m;
	CheckRegPage(0x0e0);

	IIC_Start();
	WriteByte(SCALER_I2C_ADDR);
	WriteByte(0xe0);
	WriteByte(0x90);
	m = yy * ucOSDWidth + xx;
	ch = (unsigned char)m;
	WriteByte(ch);
	ch = (unsigned char)(m >> 8);
	WriteByte(ch);
	m = value * BarWidth;
	k = m / 100;
	WriteByte(0x01);
	for(i=0; i<k; i++){
		WriteByte(0x06);
	}
	if(i < BarWidth){
		k = (m % 100) / 20;
		switch(k){
		case 0:
			WriteByte(0x02);
			break;
		case 1:
			WriteByte(0x03);
			break;
		case 2:
			WriteByte(0x04);
			break;
		case 3:
			WriteByte(0x05);
			break;
		case 4:
			WriteByte(0x06);
			break;	
		}
		i++;
		for(i; i<BarWidth; i++){
			WriteByte(0x02);
		}
	}
	WriteByte(0x07);
	IIC_Stop();
#else
unsigned char i,k;
unsigned char volatile *pBus;
unsigned short m;
	SC_RegPage = 0x00;
	pBus = &SC_INDEX_CTRL;
	*pBus = 0x90;
	pBus++;
	m = (unsigned short)yy * ucOSDWidth + xx;
	*pBus = (unsigned char)m;
	pBus++;
	*pBus = (unsigned char)(m >> 8);
	pBus++;

	m = value * BarWidth;
	k = m / 100;
	*pBus = 0x01;
	for(i=0; i<k; i++){
		*pBus = 0x06;
	}
	if(i < BarWidth){
		k = (m % 100) / 20;
		switch(k){
		case 0:
			*pBus = 0x02;
			break;
		case 1:
			*pBus = 0x03;
			break;
		case 2:
			*pBus = 0x04;
			break;
		case 3:
			*pBus = 0x05;
			break;
		case 4:
			*pBus = 0x06;
			break;	
		}
		i++;
		for(i; i<BarWidth; i++){
			*pBus = 0x02;
		}
	}
	*pBus = 0x07;
#endif
}


void ShowResolution(unsigned char x,unsigned char y)
{
unsigned char i;

	sprintf(glob_buff,"n%dx%d@%d.%dHz",GetHActive(ucResolution),GetVActive(ucResolution), (unsigned short)usVSync / 10, (unsigned short)usVSync % 10);
	for(i=0; i<32; i++){
		if(glob_buff[i] == 0)
			break;
	}
	glob_buff[0] = i - 1;
	ucStrAlignment = 1;
	ucStrWidth = 15;
//	WriteWordIIC560(OSD_FC_ATTR_LSB,ColorAttr);
	WriteArialFont(glob_buff);
	WriteXY_String(0,x,y);
}

void ShowSerialNo(unsigned char x, unsigned char y)
{
unsigned char i;
	ucStrAlignment = 0;
	ucStrWidth = 2;
	if(ucOSDType == MAIN_MENU){
//		WriteArialFont(SerialNoStrTab);				//-jwshin 111208
//		WriteXY_String(0,x-3,y);
	}

	ucStrAlignment = 1;
	ucStrWidth = 15;
	glob_buff[1] =' ';				// Space 처리... +jwshin 111208
	glob_buff[2] =' ';
	glob_buff[3] =' ';
	for(i=4; i<SN_LEN+4; i++){
		glob_buff[i] = ucSerialNum[i-4];
		if(glob_buff[i]==0x00 || glob_buff[i]==0x0A) break;
		//printf("%d=%02x\r\n", (unsigned short)i,(unsigned short)glob_buff[i]);
	}
	glob_buff[0] = i-1;
	WriteArialFont(glob_buff);
	WriteXY_String(0,x,y);

}

void WriteXY_String(unsigned char Attr,unsigned char x,unsigned char y)
{
#if NT68665
unsigned char i,l,ch;
unsigned short m,IndexTemp;
	IndexTemp = usFontIndex - ucFontLen;
	CheckRegPage(0x0e0);
/* start bit */
	IIC_Start();
/* transmit data */
	WriteByte(SCALER_I2C_ADDR);
	WriteByte(0xe0);
	if(Attr == 0)
		WriteByte(0x40);
	else
		WriteByte(0x90);
	m = y * ucOSDWidth + x;
	ch = (unsigned char)m;
	WriteByte(ch);
	ch = (unsigned char)(m >> 8);
	WriteByte(ch);

//ucStrAlignment
	if(ucStrAlignment == 0){		//Left
		l = 0;
	}
	else if(ucStrAlignment == 1){		//Right
		l = ucStrWidth - ucFontLen;
	}
	else if(ucStrAlignment == 2){		//Center
		l = (ucStrWidth - ucFontLen) >> 1;
	}
//write front space
	for(i=0; i<l; i++){
		WriteByte(0x00);
	}
//write font index
	for(i=0; i<ucFontLen; i++){
		ch = (unsigned char)(IndexTemp + i);
		WriteByte(ch);
	}
//write back space
	i = l + ucFontLen;
	for(i; i<ucStrWidth; i++){
		WriteByte(0x00);
	}
/* stop bit */
	IIC_Stop();
#else
unsigned char i,l,ch;
unsigned char volatile *pBus;
unsigned short m,IndexTemp;
	IndexTemp = usFontIndex - ucFontLen;
	SC_RegPage = 0x00;
	pBus = &SC_INDEX_CTRL;
	if(Attr == 0)
		*pBus = 0x40;
	else
		*pBus = 0x90;
	pBus++;
	m = y * ucOSDWidth + x;
	*pBus = (unsigned char)m;
	pBus++;
	*pBus = (unsigned char)(m >> 8);
	pBus++;

//ucStrAlignment
	if(ucStrAlignment == 0){		//Left
		l = 0;
	}
	else if(ucStrAlignment == 1){		//Right
		l = ucStrWidth - ucFontLen;
	}
	else if(ucStrAlignment == 2){		//Center
		l = (ucStrWidth - ucFontLen) >> 1;
	}
//write front space
	for(i=0; i<l; i++){
		*pBus = 0x00;
	}
//write font index
	for(i=0; i<ucFontLen; i++){
		ch = (unsigned char)(IndexTemp + i);
		*pBus = ch;
	}
//write back space
	i = l + ucFontLen;
	for(i; i<ucStrWidth; i++){
		*pBus = 0x00;
	}
#endif
}

void WriteArialFont(unsigned char *p)
{
unsigned char i,l,WD_Point,k,Row,width;
unsigned short m;
	ucFontLen = 0;
//string width
	m = 0;
	l = p[0] + 1;
	for(i=1; i<l; i++){
		k = p[i];// - 0x20; offset
		m += Arial_Width[k];
	}
//ucStrAlignment
	if(ucStrAlignment == 0){		//Left
		WD_Point = 0;
	}
	else if(ucStrAlignment == 1){		//Right
		m = (unsigned short)ucStrWidth * 12 - m;
		WD_Point = m % 12;
	}
	else if(ucStrAlignment == 2){		//Center
		m = (unsigned short)ucStrWidth * 12 - m;
		k = m / 12;
		WD_Point = m % 12;
		if((k & BIT_0) != 0){
			WD_Point += 12;
		}
		WD_Point >>= 1;
	}

	for(Row=0; Row<CHAR_Height; Row++){
		usFontBuffer[Row] = 0;
	}
//write font
	for(i=1; i<l; i++){
		k = p[i];// - 0x20;		//get font and font width
		width = Arial_Width[k]; //get font font width
		
		m = k * CHAR_Height;

		if(WD_Point == 0){
			for(Row=0; Row<CHAR_Height; Row++){
				usFontBuffer[Row] = Arial_Font[m+Row];
			}
		}
		else{
			for(Row=0; Row<CHAR_Height; Row++){	
				usFontBuffer[Row] |= (Arial_Font[m+Row] >> WD_Point);
			}
		}
		WD_Point += width;
		do{
			
			if(WD_Point == 12){		//buffer full?
				WriteCharFont();
				WD_Point = 0;
			}
			else if(WD_Point > 12){
				WriteCharFont();
				WD_Point -= 12;
				for(Row=0; Row<CHAR_Height; Row++){
					usFontBuffer[Row] = (Arial_Font[m+Row] << (width - WD_Point));
				}
			}
		}while(WD_Point>11);
	}
//write back space
	if(WD_Point != 0){
		WriteCharFont();
		WD_Point = 0;
	}
	
	if(bBGMode == FALSE)	//2007-02-16
		CheckModeChange();
}

void WriteCharFont(void)
{
#if NT68665
unsigned char i,ch;
	CheckRegPage(0x0e0);
/* start bit */
	IIC_Start();
/* transmit data */
	WriteByte(SCALER_I2C_ADDR);
	WriteByte(0xe0);
	WriteByte(0xa0);	//0xa0
	WriteByte((unsigned char)usFontIndex);	//Index low
	WriteByte((unsigned char)(usFontIndex>>8));	//Index high
	for(i=0; i<CHAR_Height; i++){
		usFontBuffer[i] >>= 4;
		WriteByte((unsigned char)usFontBuffer[i]);	//1'st byte
		ch = (unsigned char)(usFontBuffer[i]>>8) & 0x0f;
		i++;
		ch |= ((unsigned char)usFontBuffer[i] & 0xf0);
		WriteByte(ch);	//2'nd byte
		ch = (unsigned char)((usFontBuffer[i]>>8) & 0x00ff);
		WriteByte(ch);	//3'th byte
	}
	usFontIndex++;
	ucFontLen++;
/* stop bit */
	IIC_Stop();
#else
unsigned char i,ch;
unsigned char volatile *pBus;
	SC_RegPage = 0x00;
	pBus = &SC_INDEX_CTRL;
	*pBus = 0xa0;
	pBus++;
	*pBus = (unsigned char)usFontIndex;	//Index low
	pBus++;
	*pBus = (unsigned char)(usFontIndex>>8);	//Index high
	pBus++;
	for(i=0; i<CHAR_Height; i++){
		usFontBuffer[i] >>= 4;
		*pBus = (unsigned char)usFontBuffer[i];	//1'st byte
		ch = (unsigned char)(usFontBuffer[i]>>8) & 0x0f;
		i++;
		ch |= ((unsigned char)usFontBuffer[i] & 0xf0);
		*pBus = ch;	//2'nd byte
		ch = (unsigned char)((usFontBuffer[i]>>8) & 0x00ff);
		*pBus = ch;	//3'th byte
	}
	usFontIndex++;
	ucFontLen++;
#endif
}

void ShowAutoAdj(void)
{
	ucOSDType = AUTO_SIGNAL;
	
	OsdInit(OSD2_WIDTH,OSD2_HIGHT);

	ShowTitleGradient();
	ucStrAlignment = 2;
	ucStrWidth = ucOSDWidth;
	usFontIndex = 48;
	

	WriteArialFont(AutoStrTab[ucLanguage]);
	WriteXY_String(0,0,1);

	WriteArialFont(WaitStrTab[ucLanguage]);
	WriteXY_String(0,0,5);
	
	
	
	OSD_ON();
	
}


//----------------+jwshin 120224
void ShowMonSelMsg(unsigned char Val)
{
	ucOSDType = POWER_ON_LOGO;
	
	OsdInit(OSD2_WIDTH,OSD2_HIGHT);
	
	ucStrAlignment = 2;
	ucStrWidth = ucOSDWidth;
	usFontIndex = 48;
	
	WriteArialFont(MonSel1_Tab[Val]);
	WriteXY_String(0,0,4);
	
	if(Val==0) {				// +jwshin 120224 Button A가 Select 되어 있을 경우에만, RGB SW 상태를 Display 한다..
		if(Read24C16(EPADDR_RGB_SW1)==0) {
			WriteArialFont(RGBSel_Tab[1]);
		}
		else {
			WriteArialFont(RGBSel_Tab[0]);
		}
		WriteXY_String(0,0,5);
	}
	
	WriteArialFont(DomainDisplay_Tab[0]);
	WriteXY_String(0,0,6);

	OSD_ON();
	if(bInSync == FALSE) {
		Set_usOSD2Timer_10ms((unsigned short)ucOSDTimer*100);				// +jwshin 120302
	}
	else {
		Set_usOSD2Timer_10ms(300);				// +jwshin 120302
	}
}
//----------------------------------	
	
	
//----------------- +jwshin 120224
void ShowRGBStatus(void)
{
	ucOSDType = POWER_ON_LOGO;
	OsdInit(OSD2_WIDTH,OSD2_HIGHT);
	
	ucStrAlignment = 2;
	ucStrWidth = ucOSDWidth;
	usFontIndex = 48;
	
	if(Read24C16(EPADDR_RGB_SW1)==0) {
		WriteArialFont(RGBSel_Tab[1]);
	}
	else {
		WriteArialFont(RGBSel_Tab[0]);
	}
	WriteXY_String(0,0,4);
	OSD_ON();
	if(bInSync == FALSE) {
		Set_usOSD2Timer_10ms((unsigned short)ucOSDTimer*100);				// +jwshin 120302
	}
	else {
		Set_usOSD2Timer_10ms(300);				// +jwshin 120302
	}
}

void ShowSourceMsg(void)
{
//printf("ShowSourceMsg\r\n");
	ucOSDType = SOURCE_MSG;
	
	OsdInit(OSD2_WIDTH,OSD2_HIGHT);
	
	ucStrAlignment = 2;
	ucStrWidth = ucOSDWidth;
	usFontIndex = 48;
	
	//---------------- +jwshin 120302
	if(bInSync == TRUE) {
		if(ucPowerStatus == (SoftPowerOnFlag|mSource_VGA))
			WriteArialFont(SrcAnalogStrTab[ucLanguage]);
		else if(ucPowerStatus == (SoftPowerOnFlag|mSource_DVI))
			WriteArialFont(SrcDigitalStrTab[ucLanguage]);
		else  if(ucPowerStatus == (SoftPowerOnFlag|mSource_HDMI))
			WriteArialFont(HDMI_StrTab[ucLanguage]);
	 	else
			WriteArialFont(VIDEO_StrTab[ucLanguage]);
	}
	else {
		WriteArialFont(NoVideoStrTab[ucLanguage]);	
	}

	WriteXY_String(0,0,4);
	
	if(Read24C16(EPADDR_RGB_SW1) == 0)
	{
		WriteArialFont(RGBSel_Tab[1]);
	}
	else
	{
		WriteArialFont(RGBSel_Tab[0]);
	}
	WriteXY_String(0,0,6);
	//--------------------------------------
	OSD_ON();
	Set_usOSDTimer_10ms(300);
}

void ShowOutOfRangeOver(void)
{
//unsigned char i;
	if(bShowOutRange == FALSE){
//printf("ShowOutOfRangeOver0\r\n");
		ucOSDType = OUT_RANGE;

		OsdInit(OSD2_WIDTH,OSD2_HIGHT);

		ucStrAlignment = 2;
		ucStrWidth = ucOSDWidth;
		usFontIndex = 48;
		WriteArialFont(OutOfRangeOverStrTab[ucLanguage]);
		WriteXY_String(0,0,4);
		WriteArialFont(OutOfRangeOverStrTab[LANG_NUM+ucLanguage]);
		WriteXY_String(0,0,5);
		WriteArialFont(OutOfRangeOverStrTab[LANG_NUM*2+ucLanguage]);
		WriteXY_String(0,0,6);
		WriteArialFont(OutOfRangeOverStrTab[LANG_NUM*3+ucLanguage]);
		WriteXY_String(0,0,7);
		OSD_ON();
		usOSDMovingX = MaxMoveX/2;
		usOSDMovingY = MaxMoveY/2;
		Set_usWarningMsgTimer_1s(1800);
		bShowOutRange = TRUE;
	}
	else{
		SetMovePosition();
	}
	Set_usPoSvTimer(530);	//480+50	OUTRRANGETimer = 500;
}

void ShowOutOfRange85Hz(void)
{
//unsigned char i;
	bShowOutRange85 = TRUE;
	ucOSDType = OUT_RANGE2;
//printf("ShowOutOfRange85Hz\r\n");
	OsdInit(OSD2_WIDTH,OSD2_HIGHT);
	
	ucStrAlignment = 2;
	usFontIndex = 48;
	ucStrWidth = ucOSDWidth;
	WriteArialFont(OutOfRange85HzStrTab[ucLanguage]);
	WriteXY_String(0,0,4);
	WriteArialFont(OutOfRange85HzStrTab[LANG_NUM+ucLanguage]);
	WriteXY_String(0,0,5);
	WriteArialFont(OutOfRange85HzStrTab[LANG_NUM*2+ucLanguage]);
	WriteXY_String(0,0,6);
	WriteArialFont(OutOfRange85HzStrTab[LANG_NUM*3+ucLanguage]);
	WriteXY_String(0,0,7);

	OSD_ON();
	Set_usOSDTimer_10ms(500);
}

void ShowOSD_Lock(void)
{
	SubIconWinOff();
	MainIconWinOff();
	ucOSDType = LOCK_MSG;
	OsdInit(OSD2_WIDTH,OSD2_HIGHT);
	
	ucStrAlignment = 2;
	ucStrWidth = ucOSDWidth;
	usFontIndex = 48;

	if(bIsOSDLocked == FALSE){
		WriteArialFont(OSD_LockStrTab[ucLanguage]);
		WriteXY_String(0,0,4);
		WriteArialFont(OSD_LockStrTab[LANG_NUM+ucLanguage]);
		WriteXY_String(0,0,5);
	}
	else{
		WriteArialFont(OSD_LockStrTab[LANG_NUM*2+ucLanguage]);
		WriteXY_String(0,0,4);
		WriteArialFont(OSD_LockStrTab[LANG_NUM*3+ucLanguage]);
		WriteXY_String(0,0,5);
	}
	OSD_ON();
	Set_usOSDTimer_10ms(300);

}

void ShowDDCCiOnOff(void)
{
	ucOSDType = DDCCI_MSG;
	OsdInit(OSD2_WIDTH,OSD2_HIGHT);
	
	ucStrAlignment = 2;
	usFontIndex = 48;
	ucStrWidth = ucOSDWidth;
	if(bIsDDCCiSupported){
		WriteArialFont(DDCCiOnTab1[ucLanguage]);
		WriteXY_String(0,0,4);
	}
	else{
		WriteArialFont(DDCCiOffTab1[ucLanguage]);
		WriteXY_String(0,0,4);
	}
	OSD_ON();
	Set_usOSDTimer_10ms(300);
}

void ShowNoSync(void)
{

//	bIsFRCMode = 0;
	SetFreeRun();
	bBGMode = FALSE;		//NSTL "OSD flashes" 2006-01-11
	ForceToBackground(0);	//
	
	ucOSDType = NOSIGNAL;//ucOSDType = AUTO_SIGNAL;
	OsdInit(OSD2_WIDTH,OSD2_HIGHT);
	
	
	ucStrAlignment = 2;
	ucStrWidth = ucOSDWidth;
	usFontIndex = 48;
	WriteArialFont(NoSyncStrTab[ucLanguage]);
	WriteXY_String(0,0,5);
	OSD_ON();
}

void ShowNoVideo(void)
{

	if(bShowNoInput == FALSE){
//		bIsFRCMode = 0;
		SetFreeRun();
		
		ucOSDType = OUT_RANGE;
		OsdInit(OSD2_WIDTH,OSD2_HIGHT);
		usFontIndex = 48;
		ucStrAlignment = 2;
		ucStrWidth = ucOSDWidth;
		WriteArialFont(NoVideoStrTab[ucLanguage]);			
		WriteXY_String(0,0,4);
		//----------------- +jwshin 120224 RGB Display...
		if(Read24C16(EPADDR_RGB_SW1) == 0)
		{
			WriteArialFont(RGBSel_Tab[1]);
		}
		else
		{
			WriteArialFont(RGBSel_Tab[0]);
		}
		WriteXY_String(0,0,6);
		//---------------------------------------
		OSD_ON();
		usOSDMovingX = MaxMoveX/2;
		usOSDMovingY = MaxMoveY/2;
		Set_usWarningMsgTimer_1s(20);				// +jwshin 111209    Timer~!
		Set_usPoSvTimer(350);	//300+100
		bShowNoInput = TRUE;
	}
	else{
		Set_usPoSvTimer(350);
		SetMovePosition();
	}
}

void ShowDisconnected(void)
{
//printf("ShowDisconnected\r\n");
	if(bShowDiscon == FALSE){
		bIsFRCMode = 0;		//
		SetFreeRun();
		
		ucOSDType = OUT_RANGE;
		OsdInit(OSD2_WIDTH,OSD2_HIGHT);

		usFontIndex = 48;
		ucStrAlignment = 2;
		ucStrWidth = ucOSDWidth;
		WriteArialFont(DisconnectedStrTab[ucLanguage]);
		WriteXY_String(0,0,4);
		WriteArialFont(DisconnectedStrTab[LANG_NUM+ucLanguage]);
		WriteXY_String(0,0,5);
		OSD_ON();
		usOSDMovingX = MaxMoveX/2;
		usOSDMovingY = MaxMoveY/2;
		Set_usWarningMsgTimer_1s(1800);
		bShowDiscon = TRUE;
	}
	else{
		SetMovePosition();
	}
}

#ifdef ENABLE_TD_	//	THEFT DETERRENCE
void ShowTheftOSD(void)
{
code unsigned char TheftModeStr4[]={18, "Theft Mode Enabled"};
	if(bShowTheftOSD == FALSE){
		
		ucOSDType = THEFT_OSD;
		OsdInit(OSD2_WIDTH,OSD2_HIGHT);
		usFontIndex = 32;
		ucStrAlignment = 2;
		ucStrWidth = ucOSDWidth;
		WriteArialFont(TheftModeStr4);
		WriteXY_String(0,0,5);
		OSD_ON();
		usOSDMovingX = MaxMoveX/2;
		usOSDMovingY = MaxMoveY/2;
		Set_usPoSvTimer(350);	//300+100
		bShowTheftOSD = TRUE;
	}
	else{
		Set_usPoSvTimer(350);
		SetMovePosition();
	}
}
#endif

void SetMovePosition(void)
{
unsigned short xy;
	if(usOSDMovingX < 0x8000){
		usOSDMovingX += 6;
		if(usOSDMovingX >= MaxMoveX){
			usOSDMovingX = 0x8000+MaxMoveX;
		}
	}
	else{
		usOSDMovingX -= 6;
		if(usOSDMovingX < 0x8000){
			usOSDMovingX = 1;
		}
	}
	if(usOSDMovingY < 0x8000){
		usOSDMovingY += 6;
		if(usOSDMovingY >= MaxMoveY){
			usOSDMovingY = 0x8000+MaxMoveY;
		}
	}
	else{
		usOSDMovingY -= 6;
		if(usOSDMovingY <0x8000){
			usOSDMovingY = 1;
		}
	}
//	printf("\r\n");
//	printf("MaxMoveX=%d\r\n",MaxMoveX);
//	printf("MaxMoveY=%d\r\n",MaxMoveY);
	//xy = (usOSDMovingX & 0x7fff) * 6;
	xy = (usOSDMovingX & 0x7fff);
	//printf("usOSDMovingX=%d %d\r\n",usOSDMovingX,xy);
	WriteWordIIC560(OSD_HS_LI,xy);
	//xy = (usOSDMovingY & 0x7fff) * 6;
	xy = (usOSDMovingY & 0x7fff);
	//printf("usOSDMovingY=%d %d\r\n",usOSDMovingY,xy);
	WriteWordIIC560(OSD_VS_LI,xy);
	WriteIIC560(OSD_HW,OSD2_WIDTH-1);
	WriteIIC560(OSD_VH,OSD2_HIGHT-1);
}

#if 1
void ShowAging(unsigned char i)
{
#define OSD3_WIDTH	30
#define OSD3_HIGHT	1
#define OSD3_CCx (PanelWidth - (CHAR_Width * OSD_ZoomX * OSD3_WIDTH)) / 2
#define OSD3_CCy (PanelHeight - (CHAR_Height * OSD_ZoomY * OSD3_HIGHT)) / 2
#define OSD3_RRx (PanelWidth - (CHAR_Width * OSD_ZoomX * OSD3_WIDTH))
#define OSD3_BBy (PanelHeight - (CHAR_Height * OSD_ZoomY * OSD3_HIGHT))



code unsigned char Str[]={	32,"Auto + Menu : Quit burn in mode."};
	WriteIIC560(OSD_CTRL1,0x00);
	WriteIIC560(WIN_SEL,0x00);
	bShowAging = TRUE;
	ucOSDType = AUTO_SIGNAL;
	ucStrWidth = OSD3_WIDTH;
	switch(i){
	case 0://black
		ucStrAlignment = 2;
		WriteWordIIC560(OSD_HS_LI,OSD3_CCx);
		WriteWordIIC560(OSD_VS_LI,OSD3_CCy);
		break;
	case 4://Red
		ucStrAlignment = 2;
		WriteWordIIC560(OSD_HS_LI,OSD3_CCx);
		WriteWordIIC560(OSD_VS_LI,0);
		break;
	case 2://Green
		ucStrAlignment = 1;
		WriteWordIIC560(OSD_HS_LI,OSD3_RRx);
		WriteWordIIC560(OSD_VS_LI,OSD3_CCy);
		break;
	case 1://Blue
		ucStrAlignment = 2;
		WriteWordIIC560(OSD_HS_LI,OSD3_CCx);
		WriteWordIIC560(OSD_VS_LI,OSD3_BBy);
		break;
	case 7://White
		ucStrAlignment = 0;
		WriteWordIIC560(OSD_HS_LI,0);
		WriteWordIIC560(OSD_VS_LI,OSD3_CCy);
		break;
	default:
		ucStrAlignment = 2;
		WriteWordIIC560(OSD_HS_LI,OSD3_CCx);
		WriteWordIIC560(OSD_VS_LI,OSD3_CCy);
		break;
	}
	WriteIIC560(OSD_HW,OSD3_WIDTH-1);
	WriteIIC560(OSD_VH,OSD3_HIGHT-1);
	Sleep(40);
	ClearOSD();
	usFontIndex = 32;
	if(i == 7){
		WriteWordIIC560(OSD_FC_ATTR_LSB,AgingColor2);
	}
	else{
		WriteWordIIC560(OSD_FC_ATTR_LSB,AgingColor1);
	}
	WriteArialFont(Str);
	WriteXY_String(1,0,0);
	OSD_ON();
}
#endif

void SaveData(void)
{
	switch(ucSavePointer){
	case svBRIGHTNESS:
		Write24C16(EPADDR_BRIGHT,ucBrightness);//0x08 = brightness
		if ( ucLFMode==LF_MODE_OFF)
		{
			ucBrightnessUser = ucBrightness;
			Write24C16(EPADDR_BRIGHT_USER,ucBrightnessUser);//0x36 = brightness user
		}
#if _SmartBright_ == ON
		if((ucColorTemperature != COLOR_SRGB)&&(bSmartBrightEnable == ON)){
			//Write24C16(EPADDR_BRIGHTOFFSET_HI,(unsigned char)(usBrightOffset>>8));//0x2e = BrightOffset high
			Write24C16(EPADDR_BRIGHTOFFSET_LO,(unsigned char)usBrightOffset);//0x2f = BrightOffset low
		}
#endif		
		break;
//	case svPANELIDX:
//		Write24C16(EPADDR_IDX, ucPanelIDX);
//		break;
	case svCONTRAST:
		Write24C16(EPADDR_CONTRAST,ucContrast);//0x09 = contrast
		if ( ucLFMode==LF_MODE_OFF)
		{
			ucContrastUser = ucContrast;
			Write24C16(EPADDR_CONTRAST_USER,ucContrastUser);
		}
		break;
	case svCLOCK:
		Write24C16_Short(NVRAM_HTOTAL(ucModeNumber), usHTotal);
		break;
	case svPHASE:
		Write24C16(NVRAM_PHASE(ucModeNumber), ucADCPhase);
		break;
	case svHPOS:
		Write24C16_Short(NVRAM_HPSTART(ucModeNumber), usHPStart);
//		Write24C16(NVRAM_TIMING_ALTER(ucModeNumber), 1);
		break;
	case svVPOS:
		Write24C16_Short(NVRAM_VPSTART(ucModeNumber), usVPStart);		
//		Write24C16(NVRAM_TIMING_ALTER(ucModeNumber), 1);
		break;
	case svRED:
		if ( ucLFMode==LF_MODE_OFF)
		{
			Write24C16(EPADDR_RGAIN_USER,ucR_Gain);//0x3e = r gain user
		}
		break;
	case svGREEN:
		if ( ucLFMode==LF_MODE_OFF)
		{
			Write24C16(EPADDR_GGAIN_USER,ucG_Gain);//0x3f = g gain user
		}
		break;
	case svBLUE:
		if ( ucLFMode==LF_MODE_OFF)
		{
			Write24C16(EPADDR_BGAIN_USER,ucB_Gain);//0x40 = b gain user
		}
		break;
	case svOSDX:
		Write24C16(EPADDR_OSDX,ucOSDXPos);//0x15 = OSD position x
		break;
	case svOSDY:
		Write24C16(EPADDR_OSDY,ucOSDYPos);//0x16 = OSD position y
		break;
	case svBRIGHTNESS_F:
		Write24C16(EPADDR_BRIGHT_FACTORY,ucBrightness);
		Write24C16(EPADDR_BRIGHT,ucBrightness);//0x08 = brightness
		if ( ucLFMode==LF_MODE_OFF)
		{
			ucBrightnessUser = ucBrightness;
			Write24C16(EPADDR_BRIGHT_USER,ucBrightnessUser);//0x36 = brightness user
		}
#if _SmartBright_ == ON		
		if((ucColorTemperature != COLOR_SRGB)&&(bSmartBrightEnable == ON)){
			//Write24C16(EPADDR_BRIGHTOFFSET_HI,(unsigned char)(usBrightOffset>>8));//0x2e = BrightOffset high
			Write24C16(EPADDR_BRIGHTOFFSET_LO,(unsigned char)usBrightOffset);//0x2f = BrightOffset low
		}
#endif
		break;
	case svCONTRAST_F:
/*
		Write24C16(EPADDR_CONTRAST_FACTORY,ucContrast);
		Write24C16(EPADDR_CONTRAST,ucContrast);//0x09 = contrast
		if(ucLFMode==LF_MODE_OFF){
			ucContrastUser = ucContrast;
			Write24C16(EPADDR_CONTRAST_USER,ucContrastUser);
		}
*/
		Write24C16(EPADDR_RGB_OFFSET,ucRGB_OFFSET);
		break;
	case svLANGUAGE:
		Write24C16(EPADDR_OSDLANG,ucLanguage);//0x06 = OSD Language
		break;
	case svVOLUME:
		Write24C16(EPADDR_VOLUME, ucVolume);//0x0c = volume
		break;
	case svSTANDALONE:
		Write24C16(EPADDR_STANDALONE, (unsigned char)bStandalone);	// 0x27
		break;
	case svMUTE:
		Write24C16(EPADDR_MUTE, (unsigned char)bMute);
		break;
	case svCOLOR:
		Write24C16(EPADDR_COLOR_TEMP,ucColorTemperature);//0x19 = color temperature select
		break;
#if _SmartBright_ == ON
	case svSMARTBRIGHT:
		Write24C16(EPADDR_SMARTBRIGHT,(unsigned char)bSmartBrightEnable);
		if(bSmartBrightEnable == ON){
			usBrightOffset = DefaultBrightOffset;
			//ucADCCounter = 0;
			//ucBrightADC1 = 0;
			//Write24C16(EPADDR_BRIGHTOFFSET_HI,(unsigned char)(usBrightOffset>>8));//0x2e = BrightOffset high
			Write24C16(EPADDR_BRIGHTOFFSET_LO,(unsigned char)usBrightOffset);//0x2f = BrightOffset low
		}
		break;
#endif
	case svTRANSPARENCY:
		Write24C16(EPADDR_TRANSPARENCY, ucTransparency);
		break;
	case svOSDTIMEOUT:
		Write24C16(EPADDR_OSDTIMER, ucOSDTimer);
		break;
	case svSOURCE:
		Write24C16(EPADDR_INPUT_SRC, ucSource);
		ucPowerStatus = (ucSource | SoftPowerOnFlag);
		Write24C16(EPADDR_POWER, ucPowerStatus);
		break;
	case svSATURATION:
		Write24C16(EPADDR_SATURATION, ucSaturation);
		break;
	case svTINT:
		Write24C16(EPADDR_TINT, ucTint);
		break;
	case svDYBK:
		if(ucDynBKMode == 0){
			SetBrightness();
			iCurDynBk = ucBrightness;
		}
		ucNewDynBk = ucBrightness;
		if(ucLFMode==LF_MODE_OFF){
			Write24C16(EPADDR_DYNAMIC_BKMODE,ucDynBKMode);
		}
		break;
	}
	ucSavePointer = svNONE;
	ucNewControlValue = 2;
}

void SelectLFMITM(void)
{
unsigned char i;

	if(ucOSDType == LF_MAIN_MENU){
		i = ucOSDLvl1_Cursor * 2 + 4;
	}
	else{
		i = ucOSDLvl2_Cursor * 2  + 4;
		ucSource = ucOSDLvl2_Cursor;
	}

	MainIconWinOff();
	SelectMainIconWin();
	WriteIIC560(WIN_HS,0);
	WriteIIC560(WIN_HE,17);
	WriteIIC560(WIN_VS,i);
	WriteIIC560(WIN_VE,i);
	WriteIIC560(WIN_CL,iWHITE);
	WriteIIC560(OSD_WIN_ATTR,0x80);
	WriteIIC560(WIN_BL_HWID,0x01);
	WriteIIC560(WIN_BL_RCL,iMAGENTA);
	WriteIIC560(WIN_BL_LCL,iMAGENTA);
	MainIconWinOn();
}




#include "HDCP.H"
void HDCPPowerDet()
{
#if _ENABLE_HDCP_
	WriteIIC560(DVI_CTRL15, 0xb3);
	ucHDCPFlag=0;
	CheckHDCP();
	if(ucHDCPFlag) Sleep(1000);
	else WriteIIC560(DVI_CTRL15, 0xf3);
#endif
}

/*
void SourceToAuto()
{
//	ucSource = mSource_Auto;
	ucSavePointer = svSOURCE;
	OSD_OFF();
	BackLightOff();
	ucModeNumber=0xff;
	ucPowerStatus &= ~InputSourceDVI;
	InputSourceSelect();
	bSwitchSource = TRUE;
	HDCPPowerDet();
}
*/
void ChangeInputSource()
{
	ucSource = ucOSDLvl2_Cursor;
	ucSavePointer = svSOURCE;	//2007-03-06
	OSD_OFF();
	BackLightOff();
	ucModeNumber=0xff;
//	ucPowerStatus ^= InputSourceDVI;
	ucPowerStatus = SoftPowerOnFlag | ucSource;
	InputSourceSelect();
//	bShowNotAvailable = TRUE;
	bSwitchSource = TRUE;
	if((ucSource == mSource_DVI)||(ucSource == mSource_HDMI)){
		HDCPPowerDet();
	}
}

void CheckColorTemperature(void)
{
	if(ucColorTemperature == COLOR_SRGB){	//sRGB
		ucColorTemperature = COLOR_6500;
		Write24C16(EPADDR_COLOR_TEMP, ucColorTemperature);//0x19 = color temperature select
		SetColorTemp(ucColorTemperature);
	}
}


