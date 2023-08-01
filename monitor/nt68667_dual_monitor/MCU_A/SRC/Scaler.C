#include "Scaler.H"
#include "MCU.H"
#include "UserAdj.H"
#include "DDC_Ci.H"
#include "NT686xx_MCU_REG.H"
#include "IIC.H"
#include "stdio.h"
#include "PANEL.H"
#include "RAM.H"
#include "sRGB.H"
#include "OSD.H"
#include "ModeHandle.H"
#include "ROM_MAP.H"
#include "8051.H"
#include <math.h>
#include "NT686xx_SC_REG.H"
#include "NVRAM.H"
#include "Board.H"
#include "Mis.H"
#include "AutoAdj.H"
#include "BFControl.H"
#include "HDCP.H"
#ifdef USE_GAMMA
#include "gamma.h"
#endif
#if _Enable_OD_ == ON
#include "OD.H"
#endif
#include "DebugModeEn.H"

//#define ScalerDebug

#ifdef ScalerDebug
	#define NVTprint(s) printf(s)
	#define NVTprint1(s, a1) printf(s, a1)
#else
	#define NVTprint(s)
	#define NVTprint1(s, a1)
#endif

#if PanelDepth == 6
	#define DisplayColorDepth 0xff
	//#define DT158 0x23
//	#define DT158 0x77
#else
	#define DisplayColorDepth 0x00
//	#define DT158 0x33
#endif

#if PanelTwoPixelPerClk == 1
	#define DisplayBusWidth 0x00
#else
	#define DisplayBusWidth 0xff
#endif

#if PanelSync_DE == 1
	#define DisplaySyncMode 0xff
#else
	#define DisplaySyncMode 0x00
#endif
#define DisplayControl (0x61 | (DisplayColorDepth & BIT_3) | (DisplayBusWidth & BIT_2) | (DisplaySyncMode & BIT_1))

#define DT155 (unsigned char)PanelPadDrive
#define DT156 (unsigned char)(PanelPadDrive >> 8)|((~Panel_Invert_DVS & BIT_4) | (~Panel_Invert_DHS & BIT_5) | (~Panel_Invert_DCLK& BIT_6) | (~Panel_Invert_DEN & BIT_7))
#define DT61 ((Panel_Invert_DVS & BIT_0) | (Panel_Invert_DHS & BIT_1) | (Panel_Invert_ulDotClk & BIT_2) | (Panel_Invert_DEN & BIT_3))

code unsigned short H_ActiveTab[TOTAL_RESOLUTION]={
//	 0	 1	 2	 3	 4	  5	   6    7	 8	  9	  10  11   12   13   14  15  16   17   18  19   20
	640,720,640,800,832,1024,1152,1152,1152,1280,1280,688,1280,1600,1280,848,720,1088,1280,640,1360,
//	 21   22   23   24   25   26   27   28   29   30  31   32  
	1400,1440,1680,1792,1856,1920,1920,1920,1280,960,1600,720,
};
code unsigned short V_ActiveTab[TOTAL_RESOLUTION]={
//	 0	 1	 2	 3	 4	 5	 6	 7	 8	  9	  10  11  12  13  14  15  16  17  18   19  20
	350,400,480,600,624,768,864,870,900,960,1024,556,720,1200,768,480,576,612,800,400,768,
//	 21   22  23   24   25   26   27   28   29   30  31   32  
	1050,900,1050,1344,1392,1080,1200,1440,1026,720,1000,350,
};

unsigned short GetHActive(unsigned char ucRes)	//SAVE "CODE MEMORY SPACE"
{
unsigned short tmp;
tmp=H_ActiveTab[ucRes];
	return tmp;
}

unsigned short GetVActive(unsigned char ucRes)
{
unsigned short tmp;
tmp=V_ActiveTab[ucRes];
	return tmp;
}

void UpdatePresetData(void)
{
//sync process and display
code unsigned short ScalerInitAddrTab[]={
	DV_TOTAL_LI,DV_TOTAL_HI, // Display Vtotal
	DV_VS_WID,		 // Display V Pulse Width
	DV_BG_BEG_LI,DV_BG_BEG_HI, // Display Background Window VBegin
	DV_BG_LEN_LI,DV_BG_LEN_HI, // Display Background Window VLength
	GDV_ACT_BEG_LI,GDV_ACT_BEG_HI, // Display Active VBegin
	GDV_ACT_LEN_LI,GDV_ACT_LEN_HI, // Display VActive

	DH_HTOTAL_LI,DH_HTOTAL_HI, // Display Htotal
	DH_HS_WID,		 // Display H Pulse Width
	DH_BG_BEG_LI,DH_BG_BEG_HI, // Display Background Window HBegin
	DH_BG_WID_LI,DH_BG_WID_HI, // Display  Backgroun Window HWidth
	GDH_ACT_BEG_LI,GDH_ACT_BEG_HI, // Display Active HBegin
	GDH_ACT_WID_LI,GDH_ACT_WID_HI, // Display HActive

	GI_SYNC_CTRL, // Sync Processor Ctrl: Select Raw_hs
	GI_SYNC_CTRL2, // Sync Processor Ctrl2: H/V output
	SOG_SLICER_CTRL, // SOG Slicer Ctrl
	FIFO_FLAG, // Clear FIFO interrupt 
	FIFO_FLAG_EN, // Disable FIFO interrupt
	GI_SYNC_CTRL3, // Sync out
	HPRE_THR_LO, // Hsync not present 
	HPRE_THR_HI, // Hsync present
	VPRE_THR_LO, // Vsync not present
	VPRE_THR_HI, // Vsync present
	HCNT_THR, //0x08// Hcounter change threshold
	V_CHANG_CTRL, //0x24// Vcounter change threshold
	SYNC_INT_EN1, // 0x3c H/V interrupt enable1
	SYNC_INT_EN2, // H/V interrupt enable2
	SYNC_INT_FLAG1, // H/V interrupt clear1
	SYNC_INT_FLAG2, // H/V interrupt clear2
	0xfff,	//end
};
code unsigned char ScalerInitDataTab[]={
	(unsigned char)PanelTypVTotal,(unsigned char)(PanelTypVTotal>>8), // Display Vtotal
	(unsigned char)PanelMinVSyncWidth, // Display V Pulse Width
	(unsigned char)PanelVActiveStart,(unsigned char)(PanelVActiveStart>>8), // Display Background Window VBegin
	(unsigned char)PanelHeight,(unsigned char)(PanelHeight>>8), // Display Background Window VLength
	(unsigned char)PanelVActiveStart,(unsigned char)(PanelVActiveStart>>8), // Display Active VBegin
	(unsigned char)PanelHeight,(unsigned char)(PanelHeight>>8), // Display VActive

	(unsigned char)PanelTypHTotal,(unsigned char)(PanelTypHTotal>>8), // Display Htotal
	(unsigned char)PanelMinHSyncWidth, // Display H Pulse Width
	(unsigned char)PanelHActiveStart,(unsigned char)(PanelHActiveStart>>8), // Display Background Window HBegin
	(unsigned char)PanelWidth,(unsigned char)(PanelWidth>>8), // Display  Backgroun Window HWidth
	(unsigned char)PanelHActiveStart,(unsigned char)(PanelHActiveStart>>8), // Display Active HBegin
	(unsigned char)PanelWidth,(unsigned char)(PanelWidth>>8), // Display HActive

	0x24, // Sync Processor Ctrl: Select Raw_hs
#if NT68167
	0xc3, // Sync Processor Ctrl2: H/V output
#else
	0xc0, // Sync Processor Ctrl2: H/V output
#endif
	0x00, // SOG Slicer Ctrl
	0x03, // Clear FIFO interrupt 
	0x00, // Disable FIFO interrupt
	0x43,	//0x40, // Sync out	//2007-05-08	1080i
	0x2d, // Hsync not present 
	0x2d, // Hsync present
	0x2d, // Vsync not present
	0x2d, // Vsync present
	0x04, //0x08// Hcounter change threshold
	0x24, // Vcounter change threshold	//2007-03-16 0x22->0x24 SOME MODES WILL MODE CHANGE LOOPLY (VG-828, GF-6900 1440x900)
#if PBusProtocol
	0x80,
#else
	0x00, // 0x3c H/V interrupt enable1
#endif
	0x00, // H/V interrupt enable2
	0x2f, // H/V interrupt clear1
	0x1f, // H/V interrupt clear2
};

code unsigned short UpdateSquenceAddrTable[]={
	ADC_TEST1,ADC_TEST2,ADC_MID_CH_SEL,0x00C,DVI_CTRL1,DVI_CTRL2,DVI_CTRL3,DVI_CTRL4,DVI_CTRL5,DVI_CTRL6,DVI_CTRL7,
	GPORT_CTRL,CLAMP_BEGIN,CLAMP_WIDTH,DIGITAL_CTRL,0x024,ADC_CK_CTRL,CAP_SWAP,GI_V_DE_DLY,0x028,0x029,
	GI_CAP_VBEGO_LI,GI_CAP_VBEGO_HI,GI_CAP_VBEGE_LI,GI_CAP_VBEGE_HI,GI_CAP_VLEN_LI,GI_CAP_VLEN_HI,GI_CAP_HBEG_LI,GI_CAP_HBEG_HI,GI_CAP_HWID_LI,GI_CAP_HWID_HI,GI_ALT_CTRL,
	BK_H_SHAP_CTRL,INTE_CTRL,GAMMA_CTRL,BK_V_SHAP_CTRL,DVI_CTRL15,DVI_CTRL16,
	DISPLAY_MUTE_CTRL,0x155,DISPLAY_POL_CTRL,DISPLAY_CLK_CTRL,DITH_CTRL,DITPLAY_CHANNEL,DISP_SWAP,GD_WIN_CTRL,INSIDE_CTRL1,0x18D,LVDS_MISC_CTRL1,
	LVDS_CTRL,ADC_OP_CURRENT,LVDS_MISC_CTRL3,
//	LVDS_CTRL,LVDS_MISC_CTRL3,
	0xfff,	//end
};

code unsigned char UpdateSquenceDataTable[]={

//  0x002,0x005,0x008,0x00c,0x018,0x019,0x01a,0x01b,0x01c,0x01d,0x01e
#if (NT68670B || NT68667)
	0x01, 0x08, 0x04, 0x55, 0x02, 0x03, 0x00, 0x00, 0x00, 0x02, 0xb8,
#elif NT68167
	(0x06|0xe0), 0x08, 0x00, 0x55, 0x02, 0x03, 0x00, 0x00, 0x00, 0x02, 0xb8,
#else
	0x03, 0x03, 0x04, 0x55, 0x02, 0x03, 0x00, 0x00, 0x00, 0x02, 0xb8,
#endif
//  0x020,0x021,0x022,0x023,0x024,0x025,0x026,0x027,0x028,0x029
	0xe1, 0x0c, 0x81, 0x00, 0x00, 0x00, 0x00, 0x11, 0x00, 0x00,
//	0x02e,0x02f,0x030,0x031,0x032,0x033,0x034,0x035,0x036,0x037,0x038
	0x20, 0x00, 0x00, 0x00, 0xe0, 0x01, 0x88, 0x00, 0x80, 0x02, 0x00,
//	0x060,0x064,0x065,0x066,0x146,0x147,
//	0x00, 0x00, 0x00, 0x00, 0xf3, 0x00,	//HDCP issue 2007-03-14
	0x00, 0x00, 0x00, 0x00, 0xb3, 0x00,
//	0x154,0x155,0x156,0x157,0x158,0x159,0x16a,0x16e,0x186,0x18d,0x1f5
	0x00, DT155,DT156,0x40,	DT158,0x00,	DT16A,0x07, 0x00, 0x00, 0x35,
//	0x1B8,0x1F1,0x1F7
#if NT68167
	0x10,
#else
	0x15,
#endif
#if PANEL_SIZE < 20
	0x2a, 0x00
#else
	0x15, 0x00
#endif
};

unsigned char i;
	i = 0;
	do{
		WriteIIC560(ScalerInitAddrTab[i],ScalerInitDataTab[i]);
		i++;
	}while(ScalerInitAddrTab[i] != 0xfff);
	i = 0;
	do{
		WriteIIC560(UpdateSquenceAddrTable[i],UpdateSquenceDataTable[i]);
		i++;
	}while(UpdateSquenceAddrTable[i] != 0xfff);

	
#if NT68167
	#if _167_VERSION_C
		WriteIIC560(0x00d, 0xC0);
		WriteIIC560(0x1F7, 0xE5);
	#endif
#endif

#if SCALAR_BOARD==PCBA_Q50x50
	WriteIIC560(ADC_MID_CH_SEL, 0x00);
#endif
	
//	CheckHDCP();
	if(!bAC1stOn){
		WriteIIC560(DVI_CTRL15, 0xf3);	// IT IS NECESSARY
	}	
#if NT68167
	WriteIIC560(ADC_VREF_TEST, 0x83);
	WriteIIC560(0x37A, ReadIIC560(0x37A)|0x01);
#endif
}

void InitScaler(void)
{
unsigned char i;

	//NVTprint("Init NT68560\n");
	 printf("Init Scaler\r\n");				// +jwshin 111212

	
#if (!PBusProtocol)
	ucRegPage = 0;
	WriteIIC(SCALER_I2C_ADDR,0xff,ucRegPage);
#endif
	WriteIIC560(POWER_CTRL1,0x20);	//	Warm reset
	WriteIIC560(POWER_CTRL1,0x00);	//	output port power down
	Sleep(10);
	TCONInit();
#ifdef DEMO_HDCP_KEY
	InitHDCP_DemoKey();
#endif

#if _ENABLE_HDCP_
	InitHDCP();
#endif

	UpdatePresetData();

#if (NT68670B || NT68667)
		WriteIIC560(LVDS_MISC_CTRL3,0x22);
		WriteIIC560(LVDS_MISC_CTRL1,0x40);
		WriteIIC560(LVDS_MISC_CTRL2,0x38);
		WriteIIC560(LVDS_MISC_CTRL3,0x00);
#endif

#if NT68167
	WriteIIC560(POWER_CTRL2,0x6b);	//all power on
#else
	WriteIIC560(POWER_CTRL2,0x2a);	//all power on
#endif
	WriteIIC560(DVI_CTRL12,0x20);	//all power on
//	WriteIIC560(0x101,0x00);	//	output port power down
	bIsFRCMode = FALSE;
	SetFreeRun();

//	ucSignalType = sigSEP;
	SetInterface();
#if NT68167
	WriteIIC560(ADC_POWER_UP,0x3f);
#else
	WriteIIC560(ADC_POWER_UP,0xff);
#endif
	WriteIIC560(DISPLAY_CTRL,DisplayControl);		//fifo auto lock, auto usHTotal 
	WriteIIC560(DISPLAY_MUTE_CTRL,0x02);
//Noise reduction
	// GetMode setting again
	//WriteIIC560(NR_CTRL,0x7a);			// Origional is 0x3a // Jude 03/25/2005
	//WriteIIC560(NR_THR_CTRL1,0x4E);	// 0X43  // Origional is 0x22 // Jude 03/25/2005	
	//WriteIIC560(NR_THR_CTRL2,0x33);
//PWM0
//	WriteIIC560(GPIO_CTRL,0x3c);	// PWM0,VSO HSOoutput	bit-2 for PWM with VSync
//	WriteIIC560(0x072,0x09);	// Sync Processor Ctrl: Bypass Sync Control
	WriteIIC560(0x073,0x01);
//	WriteIIC560(PWM0_HCNT,0xff);		// jerry
//	WriteIIC560(PWM1_LCNT,0x00);
//	WriteIIC560(PWM_CTRL1,0x05);		
//OSD
	WriteIIC560(OSD_BLINK_CTL,0x09);
//	WriteIIC560(SPACE_CTL,0x80);	//12x16
//ADC bandwidth	4: 300MHz 6: 500MHz
#ifndef MODE_BANDWIDTH
	WriteIIC560(ADC_BW_CTRL,0x06);
#endif

	WriteIIC560(HPLL_CTRL3,0x40);	//ADC clock duty

// For ADC R/G/B phase delay jacky 20040629
	WriteIIC560(HPLL_PHASE_CTRL1,0x00);
	WriteIIC560(HPLL_PHASE_CTRL2,0x00);//00
	WriteIIC560(HPLL_PHASE_CTRL1,0x40);
	WriteIIC560(HPLL_PHASE_CTRL2,0x01);//02
	WriteIIC560(HPLL_PHASE_CTRL1,0x80);
	WriteIIC560(HPLL_PHASE_CTRL2,0x00);//00

	WriteIIC560(GI_PHS_MASK,0x00);  // Phase mask
// 2005-05-26 mingyu: Trigger level
	WriteIIC560(HS_TRIG_LEVEL,0x37);	//0x77	0x33 //0x07
	//WriteIIC560(HS_TRIG_LEVEL,0x31);	// Solve the gitter issue for Dell PC (Jack's PC at BenQ)  // Jude 2007/05/16
	
	WriteIIC560(0x1AF, 0x4A);			// 2006-01-11 FAST MUTE
#if NT68167
	WriteIIC560(0x1FA,0x40);
	WriteIIC560(0x1ED,ReadIIC560(0x1ED)|BIT_5);
	WriteIIC560(ADC_BW_CTRL,0x06);
	WriteIIC560(0x011,0x58);
#else
	WriteIIC560(0x1FA,0x02);
	WriteIIC560(ADC_BW_CTRL,0x06);
#endif
//TMDS
	WriteIIC560(DVI_CTRL1,0x02);	//2005-01-06 DVI dot flash
	WriteIIC560(DVI_CTRL2,0x03);
	
//	WriteIIC560(LVDS_MISC_CTRL4,0x02);  //mark 041223 for LVDS(PLL) range fine tune	//NT68663 TO NT68665

	BF_Init();
#ifdef USE_GAMMA
	LoadGamma();
#endif


//NT68663 TO NT68665
	WriteIIC560(0x1EF,0x04);		//LVDS POWER UP
//	WriteIIC560(0x1FA,0x02);
#if NT68665
//	if(SCALER_VER==NT68665_VER_GJ)	//SUGGESTED BY MIDAS'S APP.NOTE.
//		WriteIIC560(0x1F6,0x04);
//	else
		WriteIIC560(0x1F6,0x00);
#endif
#if NT68670B||NT68667
	WriteIIC560(0x1F5,0x47);
	WriteIIC560(0x1F6,0x28);
#endif
	if((ucPowerStatus & SoftPowerOnFlag)!= 0){
		ScalerON();
#if PanelID == CMO_M190E5_L0E  //neo 060811
		bScalerOutput = 1;
#endif
	}

	//NEW DITHERING MODE TO REDUCE LOW GRAY LEVEL NOISE.
	WriteIIC560(0x370,0x00);//0xf0
	WriteIIC560(0x371,0x00);//0x02
//	WriteIIC560(0x390,0x10);	//IT AFFECT THE COLOR TEMP.
//	WriteIIC560(0x371,0x72);

	WriteIIC560(0x1cc,0x07);

#if Panel_Spread_Spect_En == 0xff
	i = (PanelSpreadSpectrumCtrl << 1) | BIT_0;
	WriteIIC560(SSC_CTRL,i);
#endif

#if _SmartBright_ == ON
	LightSensorOn();		// 2005-09-13 jerry
#endif
	WriteIIC560(0x1ed,0x08);//0x48
#if _Enable_OD_ == ON
	bSmartResponse = Read24C16(EPADDR_OD_ONOFF);
	SetODTable(3);
#endif
}

void TCONInit(void)
{
#if Use_TCON != 0
unsigned char i;
	WriteIIC560(0x0FF,0x02); // page2 enable

	NVTprint("TCON Init\n");

	for(i=0; i<0x70; i=i+16)
		WritePage560(i,i,TCON_Tab);
	for(i=0x70; i<0x7b; i++)
		WriteIIC(SCALER_I2C_ADDR,i,TCON_Tab[i]);
	for(i=0x80; i<0xa0; i=i+16)
		WritePage560(i,i,TCON_Tab);
	WriteIIC560(0x0FF,0x00); // page1 disable
#endif
}
#if Use_TCON != 0
void WritePage560(unsigned char target,unsigned char offset,unsigned char *value)
{
unsigned char i,ch;
/* start bit */
	IIC_Start();
/* transmit data */
	WriteByte(SCALER_I2C_ADDR);
	WriteByte(target);
	for(i=0; i<16; i++){
		ch = value[offset + i];
		WriteByte(ch);
	}
/* stop bit */
	IIC_Stop();
}
#endif

void SetADC_Phase(void)
{
	//WriteIIC560(0x0d9,ucADCPhase);
	WriteIIC560(0x0d9,ucADCPhase | BIT_6);	// Jude 03/25/2005
	
	ucADCCPhase100Pa = (((unsigned short)ucADCPhase * 100) + 32) / 63;
}

void SetADC_PLL(void)
{
#if PanelXga == 1
	#define	MIN_H_FREQ 298	//28	//KHz
	#define	MIN_V_FREQ 555	//49//Hz
	#define	MAX_H_FREQ 640 //85	//KHz
	#define	MAX_V_FREQ 860		 //Hz
	#define MAX_PIXEL_RATE 145	//90//MHz
#endif
#if PanelSxga == 1
	#define	MIN_H_FREQ 298	//28	//KHz
	//--- +jwshin 120525 Thin Client를 위해(1280x1024 50Hz)   
	#define	MIN_V_FREQ 455	//54	//49	//Hz		//2007-03-02	49 is TPV Request //2007-04-11	55 is Philips Request
//	#define	MIN_V_FREQ 555	//54	//49	//Hz		//2007-03-02	49 is TPV Request //2007-04-11	55 is Philips Request
	#define	MAX_H_FREQ 835	// 93	//KHz //93 FOR 1280X1024/85
	#define	MAX_V_FREQ 860		 //Hz
	#define MAX_PIXEL_RATE 166	//155 //MHz	//2007-03-02	TPV Request 1920x1200
#endif
#if PanelWsxga == 1
	#define	MIN_H_FREQ 298	//28	//KHz
	#define	MIN_V_FREQ 555	//54	//49	//Hz		//2007-03-02	49 is TPV Request //2007-04-11	55 is Philips Request
	#define	MAX_H_FREQ 835	// 93	//KHz //93 FOR 1280X1024/85
	#define	MAX_V_FREQ 860		 //Hz
	#define MAX_PIXEL_RATE 205	//155 //MHz	//2007-03-02	TPV Request 1920x1200
#endif

xdata unsigned long PixelRate;
unsigned char ch;
#if (!NT68167)
	unsigned char k;
#endif
xdata float temp;
	PixelRate = ((unsigned long)usHTotal * usHSync)/10000;
#ifdef R640_TUNE
	if(H_ActiveTab[ucResolution] == 640) PixelRate <<= 1;
#endif
	ch = (unsigned char)PixelRate;
#if NT68167
	
	// PLL configure sequence by APN v1.1 2008/2/14
	WriteIIC560(0xB04, ReadIIC560(0xB04)|BIT_0);
	WriteIIC560(0xB04, ReadIIC560(0xB04)&~BIT_0);


	WriteIIC560(HPLL_CTRL1, 0x21);
	if(ucSignalType == sigSOG){	// Clamping Width for SOG
		WriteIIC560(CLAMP_WIDTH, 0x80 | ((unsigned char)((float)ch*0.2)-1));
	}
	else
		WriteIIC560(CLAMP_WIDTH, 0x81);
#else
	WriteIIC560(HPLL_CTRL1, 0x53);
#endif
	//out of range
	bOutOfRange = FALSE;
	bOutOfLimit = FALSE;
	bShowOutRange = FALSE;
	bShowOutRange85 = FALSE;

//#if PanelXga == 1
//	if((ch > MAX_PIXEL_RATE)||(H_ActiveTab[ucResolution] > 1024))
//#else
//	if((ch > MAX_PIXEL_RATE)||(H_ActiveTab[ucResolution] > 1280))
//#endif
	if(ch > MAX_PIXEL_RATE)
		bOutOfLimit = TRUE;

	if((usHSync > MAX_H_FREQ)||(usHSync < MIN_H_FREQ)){
#if 0
//		if(ucResolution != R1280x1024 ) //1280x1024-85
		if(!((ucResolution != R1280x1024 )||(ucResolution != R1600x1200 ))) //1280x1024-85
			bOutOfLimit = TRUE;
		else{
			if(usHSync > 950)
				bOutOfLimit = TRUE;
		}
#else
		bOutOfLimit = TRUE;
#endif
	}
	if((usVSync > MAX_V_FREQ)||(usVSync < MIN_V_FREQ)){
		if(!(((ucResolution == R720x576)||(ucResolution == R1280x720)||(ucResolution == R1920x1080)) && (abs(usVSync - 500) < 11)))
			bOutOfLimit = TRUE;
	}
	
	if((ucResolution==R1920x1200) && (usVTotal>1240)&&(PanelID != SAM_LTM_240CT03))
		bOutOfLimit = TRUE;

	if(bOutOfLimit == TRUE){
		return;
	}

#if NT68167
	WriteIIC560(HPLL_FREQ_CTRL,0x00);
#else	
	if(bBGMode == FALSE){
		k = ReadIIC560(HPLL_FREQ_CTRL) & 0x03;
	}
	else{
		if(ch > 100){
			WriteIIC560(HPLL_FREQ_CTRL,0x10);
			k = 0;
		}
		else if (ch > 48){
			WriteIIC560(HPLL_FREQ_CTRL,0x11);
			k = 1;
		}
		else if(ch > 20){
			WriteIIC560(HPLL_FREQ_CTRL,0x12);
			k = 2;
		}
		else{
			WriteIIC560(HPLL_FREQ_CTRL,0x13);
			k = 3;
		}
	}
#endif

#if NT68167
	WriteIIC560(HPLL_CTRL2,0xc0);

	if( usHSync < 250 )
		WriteIIC560(HPLL_LINE_CNT,0x0A);
	else if( usHSync < 500 )
		WriteIIC560(HPLL_LINE_CNT,0x0B);
	else
		WriteIIC560(HPLL_LINE_CNT,0x0C);

    //Samuel-2008-05-19
    //Solve glitch pulse issue in Chroma 22293
/*
    {
        unsigned char i, HPLL_Line_Count;
        unsigned long HPLL_Count, HS_CNT_RESULT;
        HPLL_Line_Count = ReadIIC560(HPLL_LINE_CNT);
        HPLL_Count = (unsigned long) (pow(2, HPLL_Line_Count) / usHSync * 1920000);
        printf("HPLL_Count = %08LX\r\n", HPLL_Count);
        for( i=0; i<=2; i++) {
            Sleep(100);
            HS_CNT_RESULT = ReadWordIIC560(HS_CNT_RESULT_MI);
            HS_CNT_RESULT <<= 8;
            HS_CNT_RESULT += ReadIIC560(HS_CNT_RESULT_LI);
            if( abs(HPLL_Count - HS_CNT_RESULT) < 256 ) {
                break;
            }
            printf("HS_CNT_RESULT = %08LX\r\n", HS_CNT_RESULT);
        }
        //Disable HPLL Auto Load
        WriteIIC560(HPLL_FREQ_CTRL, 0x40);
    }
*/    
#else
	if((ucSignalType == sigSEP)||(ucSignalType == sigDVI))
		WriteIIC560(HPLL_CTRL2,0xBF);
	else
		WriteIIC560(HPLL_CTRL2,0xA0);

	WriteIIC560(HPLL_LINE_CNT,0x0C);
#endif
	
#if DUAL_MODE
	/*	2005-09-20
	When the system on DVI input,
	the HPLL will be power down.
	So, the firmware need to power up the HPLL to initialize the hardware.*/
      if(ucSignalType == sigDVI ){
      		ch = ReadIIC560(POWER_CTRL2);
      		WriteIIC560(POWER_CTRL2, ch | BIT_5);
      		Sleep(5);
      		WriteIIC560(POWER_CTRL2, ch );

//      		if((ReadIIC560(DVI_STATUS)&BIT_0) != 0)
//   			WriteIIC560(POWER_CTRL2, ch | BIT_5);
      	}
#endif

	if ( bBGMode == FALSE ) {
//

#if NT68167
		if(ucSignalType != sigSEP){ // SOG
			WriteIIC560(HPLL_PHASE_CTRL,0x08);		//0x0d
		}
		else{
			if((ucHVPolarity & BIT_1) == 0){
				WriteIIC560(HPLL_PHASE_CTRL,0x00);		//0x05
			}
			else{
				WriteIIC560(HPLL_PHASE_CTRL,0x08);		//0x0d
			}
		}
		PixelRate = ReadWordIIC560(HS_CNT_RESULT_MI) & 0xffff;
#else
		if(ucSignalType != sigSEP){ // SOG
			WriteIIC560(HPLL_PHASE_CTRL,0x09);		//0x0d
		}
		else{
			if((ucHVPolarity & BIT_1) == 0){
				WriteIIC560(HPLL_PHASE_CTRL,0x01);		//0x05
			}
			else{
				WriteIIC560(HPLL_PHASE_CTRL,0x09);		//0x0d
			}
		}
		PixelRate = ReadWordIIC560(HS_CNT_RESULT_MI) & 0x3fff;
#endif
		PixelRate <<= 8;
		ch = ReadIIC560(HS_CNT_RESULT_LI);
		PixelRate += ch;
	}
	else{
		WriteIIC560(HPLL_PHASE_CTRL,0x01);

ulHfreqCounter = 0;

if( ucSignalType != sigDVI || H_ActiveTab[ucResolution] > 1280 )	//1920x1200 HAS FIFO OVERFLOW
{
			ulHfreqCounter = 0;
			ucLoopTimer_10ms = 30;
			while(ucLoopTimer_10ms != 0){
#if NT68167
				PixelRate = ReadWordIIC560(HS_CNT_RESULT_MI) & 0xffff;
#else
				PixelRate = ReadWordIIC560(HS_CNT_RESULT_MI) & 0x3fff;
#endif
				PixelRate <<= 8;
				ch = ReadIIC560(HS_CNT_RESULT_LI);
				PixelRate += ch;

				if(PixelRate > ulHfreqCounter){
					if((PixelRate - ulHfreqCounter ) >  2){
						ulHfreqCounter = PixelRate;
						ucLoopTimer_10ms = 30;
					}
				}
				else{
					if((ulHfreqCounter - PixelRate ) >  2){
						ulHfreqCounter = PixelRate;
						ucLoopTimer_10ms = 30;
					}
				}
/*
				if(abs(PixelRate - ulHfreqCounter ) >  2){
						ulHfreqCounter = PixelRate;
						ucLoopTimer_10ms = 30;
				}
*/					
				CheckModeChange();
				if(usTmpHSync == 0xffff){
					break;
				}
			}
			ulHfreqCounter = PixelRate;

}

#if DUAL_MODE
		if(ucSignalType == sigDVI){      //neo 060620 suggest by jerry
			PixelRate = ReadWordIIC560(GI_HCNT_LI) & 0x1fff;
			if((PixelRate == 0x1fff)||(PixelRate == 0)){
				usTmpHSync = 0xffff;
			}
			else{
				    PixelRate = PixelRate * 512;
			}

			//printf("Hcounter(From Register) = %ld\r\n",PixelRate);		//IF DIFFERENCE IS LARGER, THEN USE ROUGHLY READ FROM REGISTER
			//if(abs(PixelRate - ulHfreqCounter ) > 512)
			//		ulHfreqCounter = PixelRate;		    
			if( (PixelRate > ulHfreqCounter && PixelRate - ulHfreqCounter  > 512) ||
				(ulHfreqCounter > PixelRate && ulHfreqCounter - PixelRate  > 512) )
			{
					ulHfreqCounter = PixelRate;		
			}
		}
#endif
		
#if NT68167
			if ( usHSync<250 )
				WriteIIC560(HPLL_FREQ_CTRL,0x40);
#endif
		
	}

#if NT68167
	if ( usHSync<250 )
		ulHfreqCounter = ulHfreqCounter>>2;
	else if ( usHSync<500 )
		ulHfreqCounter = ulHfreqCounter>>3;
	else
		ulHfreqCounter = ulHfreqCounter>>4;
#endif
	
	temp = ((float)usHTotal * 536870912) / ulHfreqCounter;
	PixelRate = (unsigned long)(temp + 0.5);
#ifdef R640_TUNE
	if(H_ActiveTab[ucResolution] == 640) PixelRate <<= 1;
#endif
//printf("DSS = %ld\r\n",PixelRate);

	if(usTmpHSync != 0xffff){

#if (!PBusProtocol)
		for(k; k>0; k--){
			PixelRate <<= 1;
		}
		WriteIIC560(HSDDS_RATIO_LI,(unsigned char)PixelRate);
		WriteIIC560(HSDDS_RATIO_MI,(unsigned char)(PixelRate>>8));
//		WriteIIC560(0x0D4,(unsigned char)(PixelRate>>16));
		WriteIIC_WaitV(SCALER_I2C_ADDR,0x0D4,(unsigned char)(PixelRate>>16));
#endif
#ifdef R640_TUNE
		if(H_ActiveTab[ucResolution] == 640)
			WriteWordIIC560(HSDDS_DIVIDER_LI,usHTotal<<1);
		else
#endif
		WriteWordIIC560(HSDDS_DIVIDER_LI,usHTotal);
	}

#if NT68167
	if(ucSignalType != sigSEP){ //SOG
		WriteIIC560(HPLL_PHASE_CTRL,0x00);	//0x0d
	}
	else{
		if((ucHVPolarity & BIT_1) == 0){

			WriteIIC560(HPLL_PHASE_CTRL,0x00);	//0x07
		}
		else{
			WriteIIC560(HPLL_PHASE_CTRL,0x08);	//0x0f
		}
	}
#else
	if(ucSignalType != sigSEP){ //SOG
		WriteIIC560(HPLL_PHASE_CTRL,0x09);	//0x0d
	}
	else{
		if((ucHVPolarity & BIT_1) == 0){

			WriteIIC560(HPLL_PHASE_CTRL,0x03);	//0x07
		}
		else{
			WriteIIC560(HPLL_PHASE_CTRL,0x0b);	//0x0f
		}
	}
#endif

#if (!PBusProtocol)
	if(ucResolution > 1){ 	//<==NSTL "Win98 logo shakes"
		ch = ReadIIC560(HPLL_PHASE_CTRL) | BIT_2;	//switch to manual lock
		Sleep(5);									//mingyu20041223
		WriteIIC560(HPLL_PHASE_CTRL,ch);
	}
#endif	

#ifdef ANTI_ESD
	// ESD ISSUE, AVOID HPLL REGISTER COULD BE RESET, jerry
	//ucESDSaveD0 = ReadIIC560(HPLL_CTRL1);
	ucESDSaveD1 = ReadIIC560(HPLL_FREQ_CTRL);
	ucESDSaveD2 = ReadIIC560(HSDDS_RATIO_LI);
	ucESDSaveD3 = ReadIIC560(HSDDS_RATIO_MI);
	ucESDSaveD4 = ReadIIC560(HSDDS_RATIO_HI);
	ucESDSaveF1 = ReadIIC560(DPLL_FREQ_CTRL);
#endif
	DebugModeEn();
}

void SetScaler(void)
{
xdata unsigned short i,InputActiveHeight,DispActiveHeight,dstVtotal,dstHtotal,V_Act;
#if PanelID == CPT_CLAA170EA07P
xdata unsigned short Hr2;//,Hr,Ht,Hr_diff1,Hr_diff2,dstVLockPos,dstHLockPos;
unsigned char Reg0x154;
#endif
unsigned char ch;
xdata float temp;

	bIsFRCMode = FALSE;
#if Panel_Spread_Spect_En == 0xff
	WriteIIC560(SSC_CTRL,0);
#endif
	WriteIIC560(DISPLAY_CTRL,DisplayControl);		//fifo auto lock, auto usHTotal 

	if(ucSignalType == sigDVI){
		usActiveH = ReadWordIIC560(DVI_CAP_HWID_LI);
		V_Act = ReadWordIIC560(DVI_CAP_VLEN_LI);

		if ( bIsInterlaced == TRUE )
			V_Act <<= 1;

		for(ch=0; ch<TOTAL_RESOLUTION; ch++){
			if((abs(H_ActiveTab[ch] - usActiveH) < 2) && (abs(V_ActiveTab[ch] - V_Act) < 2)){
				ucResolution = ch;
				break;
			}		
		}
		
	}
	else
	{	
		usActiveH = H_ActiveTab[ucResolution];
#ifdef R640_TUNE
		if(H_ActiveTab[ucResolution] == 640) usActiveH <<= 1;
#endif
		V_Act = V_ActiveTab[ucResolution];
	}
	



	if(usActiveH > PanelWidth)
		WriteIIC560(INSIDE_CTRL2,0x44);	//down scalling
	else
		WriteIIC560(INSIDE_CTRL2,0x04);	//up scalling

	WriteWordIIC560(GI_CAP_VLEN_LI,V_Act);		// Capture V_Active
	WriteWordIIC560(GI_CAP_HWID_LI,usActiveH);		// Capture H_Active
	InputActiveHeight = V_Act;

//	printf("ucResolution = %d x %d\r\n",H_ActiveTab[ucResolution],V_ActiveTab[ucResolution]);


// ulDotClk
	ulDotClk = ((unsigned long)PanelHeight * usVTotal / V_ActiveTab[ucResolution]) * usVSync * PanelMinHTotal / 10000;	//kHz	
	
	if(bIsInterlaced == TRUE){
		ulDotClk <<= 1;
	}
	DispActiveHeight = PanelHeight;				// set the vertical active height to the Panel Height
/*
#if (PanelID ==LPL_LM150X08_TL03 || PanelID ==LPL_LM170E01_TLBB || PanelID == LPL_LM170E01_TLBD || \ 
	PanelID ==LPL_LM190E03_TLB5 || PanelID ==LPL_LM190E03_TLB7	)
*/
#if 0
	if( H_ActiveTab[ucResolution] == PanelWidth && abs(usVSync-600)<12 )
	{
		printf("FINE TUNE FOR NATIVE MODE@60HZ IN LPL PANEL\r\n");
		dstHtotal = PanelTypHTotal;
	}
	else
		dstHtotal = PanelMinHTotal;
#else
		dstHtotal = PanelMinHTotal;
#endif

// calculate dst vtotal
	dstVtotal = ((((unsigned long)usVTotal * DispActiveHeight) << 4) / V_ActiveTab[ucResolution] + 8) >> 4;	//add .5 for rounding, make even

//printf("Step 1.\r\n");
//printf("dstHtotal=%d, dstVtotal=%d, InputActiveHeight =%d\r\nDispActiveHeight=%d\r\n", 
//	(unsigned short)dstHtotal,(unsigned short)dstVtotal, InputActiveHeight, (unsigned short)DispActiveHeight);
//printf("ulDotClk=%ld\r\n",ulDotClk);

	if(ulDotClk < PanelMinPClk){                            
		dstHtotal = PanelTypHTotal;
	}
	else if(ulDotClk > PanelMaxPClk){

		dstHtotal = PanelLowHTotal;
			
		if(ucSignalType == sigDVI){	//DVI
#if 1			
			DispActiveHeight = (unsigned short)(((float)PanelMaxPClk / dstHtotal * 10) * V_ActiveTab[ucResolution] / usHSync + 0.5);
			dstVtotal = ((((unsigned long)usVTotal * DispActiveHeight) << 4) / V_ActiveTab[ucResolution] + 8) >> 4;	//add .5 for rounding, make even
			if(dstVtotal < PanelMinVTotal){
				DispActiveHeight = (unsigned long)PanelMinVTotal * V_ActiveTab[ucResolution] / usVTotal;
			}
			if(DispActiveHeight > PanelHeight)
				DispActiveHeight = PanelHeight;
#endif
/*
//			DispActiveHeight = (unsigned short)(((float)PanelMaxPClk / dstHtotal * 10) * V_ActiveTab[Resolution] / usHSync + 0.5);
			DispActiveHeight = (unsigned long)PanelMaxHFreq * V_ActiveTab[ucResolution] / usHSync / 100;
			dstVtotal = ((((unsigned long)usVTotal * DispActiveHeight) << 4) / V_ActiveTab[ucResolution] + 8) >> 4;	//add .5 for rounding, make even
			if(dstVtotal < PanelMinVTotal){
				DispActiveHeight = (unsigned long)PanelMinVTotal * V_ActiveTab[ucResolution] / usVTotal;
			}
			if(DispActiveHeight > PanelHeight)
				DispActiveHeight = PanelHeight;
*/				
		}
		else{	//analog
			
			temp = (float)PanelMaxPClk / 12000;
#if 1			
			InputActiveHeight = (unsigned short)((float)dstHtotal * PanelHeight  * 4096 / ulHfreqCounter / temp);
			if(InputActiveHeight < V_ActiveTab[ucResolution])
				InputActiveHeight = V_ActiveTab[ucResolution];
			else if (InputActiveHeight < V_ActiveTab[ucResolution]+4)
				InputActiveHeight = V_ActiveTab[ucResolution]+4;
			if(InputActiveHeight > usVTotal)
				InputActiveHeight = usVTotal - 16;
			WriteWordIIC560(GI_CAP_VLEN_LI,InputActiveHeight);		// Capture V_Active
			ucVPOffset = (InputActiveHeight - V_ActiveTab[ucResolution]) / 2;
			ucMinVP += ucVPOffset;
			SetVP();
#endif
/*
			InputActiveHeight = (unsigned short)((float)dstHtotal * PanelHeight  * 4096 / ulHfreqCounter / temp);
			if(InputActiveHeight < V_ActiveTab[ucResolution])
				InputActiveHeight = V_ActiveTab[ucResolution];
			if((InputActiveHeight < PanelHeight + 8)&&(InputActiveHeight > PanelHeight))
				InputActiveHeight = InputActiveHeight + 8;
			if(InputActiveHeight > usVTotal)
			InputActiveHeight = usVTotal - 16;
			ulDispHfreq = (unsigned long)PanelHeight * usHSync * 100 / InputActiveHeight;
			if(ulDispHfreq > PanelMaxHFreq){
				InputActiveHeight = (unsigned long)PanelHeight * usHSync * 100 / PanelMaxHFreq;
				dstVtotal = ((((unsigned long)usVTotal * PanelHeight) << 4) / InputActiveHeight + 8) >> 4;	//add .5 for rounding, make even
				if(dstVtotal < PanelMinVTotal){
					InputActiveHeight = (unsigned long)PanelHeight * usVTotal / PanelMinVTotal;
				}
			}
			WriteWordIIC560(GI_CAP_VLEN_LI,InputActiveHeight);		// Capture V_Active
			ucVPOffset = (InputActiveHeight - V_ActiveTab[ucResolution]) / 2;
			ucMinVP += ucVPOffset;
			SetVP();
*/			
		}
	}
//	temp = (float)dstHtotal * PanelHeight * 4096 / ulHfreqCounter / V_ActiveTab[ucResolution];
//	ulDotClk = (unsigned long)(temp * 12000000) - 1000;

#if bDisplaySize != ActDisplay1680x1050
	if(ucResolution == R1280x1024)
		DispActiveHeight = 1024;
#endif

	WriteWordIIC560(DV_BG_LEN_LI,DispActiveHeight);		// Display VActive
	WriteWordIIC560(GDV_ACT_LEN_LI,DispActiveHeight);		// Display VActive

/*
	if ( ucSignalType != sigDVI && ucResolution==3 && usVSync > 740 )
	temp = ((float)dstHtotal+30) * DispActiveHeight * 4096 / ulHfreqCounter / InputActiveHeight;
	else
*/
#if PanelID == CPT_CLAA170EA07P
	temp = ((float)dstHtotal-0.2) * DispActiveHeight * 4096 / ulHfreqCounter / InputActiveHeight;
#else
	temp = ((float)dstHtotal-0.1) * DispActiveHeight * 4096 / ulHfreqCounter / InputActiveHeight;
#endif
	ulDotClk = (unsigned long)(temp * 12000000);

	if(bIsInterlaced == TRUE){
		ulDotClk <<= 1;
	}

	SetDPLL();

// Htotal
	WaitSetup(8);

	if(usTmpHSync != 0xffff){

		i = ReadWordIIC560(DSP_HTOTAL_R) & 0x0fff;
		if(abs(i - dstHtotal) < 5)		dstHtotal = i;

		dstVtotal = (ulDotClk * 10 / dstHtotal + (usVSync >> 1)) / usVSync;	
		if((dstVtotal-PanelHeight) > 256){
			usPanelVBackPorch = PanelMinVSyncBackPorch + 80;
		}
		else{
			usPanelVBackPorch = PanelMinVSyncBackPorch;
		}
		ulDispHfreq = ulDotClk / dstHtotal;		// burst mode
//printf("Step 2.\r\n");
//printf("dstHtotal=%d, dstVtotal=%d, InputActiveHeight =%d\r\nDispActiveHeight=%d\r\n", 
//	(unsigned short)dstHtotal,(unsigned short)dstVtotal, InputActiveHeight, (unsigned short)DispActiveHeight);
//printf("ulDotClk=%ld\r\n",ulDotClk);

		NVTprint1("ulDotClk = %ld\r\n",ulDotClk);
		NVTprint1("DispActiveHeight = %d\r\n",DispActiveHeight);
		NVTprint1("InputActiveHeight = %d\r\n",InputActiveHeight);
		NVTprint1("dstVtotal = %d\r\n",dstVtotal);
		NVTprint1("dstHtotal = %d\r\n",dstHtotal);
				
		WriteWordIIC560(DV_TOTAL_LI,dstVtotal);		// Display Vtotal
		i = usPanelVBackPorch + PanelMinVSyncWidth;
		WriteWordIIC560(DV_BG_BEG_LI,i);		// Display PanelVActiveStart
		i = i + (PanelHeight - DispActiveHeight) / 2;
		WriteWordIIC560(GDV_ACT_BEG_LI,i);		// Display PanelVActiveStart
		WriteWordIIC560(DH_HTOTAL_LI,dstHtotal);		// Display Htotal

		i = (dstHtotal - PanelWidth) / 3;
		WriteIIC560(DH_HS_WID,i);		 // Display H Pulse Width
		i <<= 1;
		WriteWordIIC560(DH_BG_BEG_LI,i);	//PanelHActiveStart
		WriteWordIIC560(GDH_ACT_BEG_LI,i);	//PanelHActiveStart


		SetBrightness();


		//i = ReadIIC560(SRGB_CTRL);
		//WriteIIC560(SRGB_CTRL, i | 0x10 );

#ifdef MODE_BANDWIDTH
#if PanelSxga == 1
		if ( H_ActiveTab[ucResolution] <= 640 ||  (H_ActiveTab[ucResolution]==1024 && usVSync<612) ) // ripple + by 2006/04/10
#else
		if ( H_ActiveTab[ucResolution] <= 640 )
#endif
			WriteIIC560(ADC_BW_CTRL,0x00);
		else if ( H_ActiveTab[ucResolution] <=800 )
			WriteIIC560(ADC_BW_CTRL,0x02);
		else
			WriteIIC560(ADC_BW_CTRL,0x06);
#endif

		
#ifdef MODE_OFFSET
#if PanelSxga == 1
		if ( H_ActiveTab[ucResolution] < 1280 && bOffsetDown==FALSE )
#else
		if ( H_ActiveTab[ucResolution] < 1024 && bOffsetDown==FALSE )
#endif
		{
			ucR_ADC_Offset-=3;
			ucG_ADC_Offset-=3;
			ucB_ADC_Offset-=3;
			bOffsetDown = TRUE;
			Write24C16(EPADDR_OFFSETDOWN, bOffsetDown);
//printf("Offset-8\r\n");			
			UpdateADCOffset();
		}
#if PanelSxga == 1
		else if ( H_ActiveTab[ucResolution] == 1280 && bOffsetDown==TRUE )
#else
		else if ( H_ActiveTab[ucResolution] == 1024 && bOffsetDown==TRUE )
#endif
		{
			ucR_ADC_Offset+=3;
			ucG_ADC_Offset+=3;
			ucB_ADC_Offset+=3;
			bOffsetDown = FALSE;
			Write24C16(EPADDR_OFFSETDOWN, bOffsetDown);
//printf("Offset+8\r\n");
			UpdateADCOffset();
		}
#endif

	}
	else{
		SetFreeRun();
//		goto ERROR1;
#if Panel_Spread_Spect_En == 0xff
		i = (PanelSpreadSpectrumCtrl << 1) | BIT_0;
		WriteIIC560(SSC_CTRL,i);
#endif

		return;
	}


	i = ReadIIC560(DISPLAY_CTRL);
	
	if (bIsInterlaced){
		if(//(ucResolution == R720x480) ||
		    //(ucResolution == R720x576) ||
		    (ucResolution == R1920x1080))
		{
			WriteIIC560(DISPLAY_CTRL,(i & ~BIT_6));		//manual HTotal
			WriteIIC560(DSP_VLOCK_POS_W, 0x01);
			WriteWordIIC560(DSP_HLOCK_POS_W, 0x200);
		}
		else
			WriteIIC560(DISPLAY_CTRL,i);		//fifo auto lock, auto HTotal 
	}
	else
		WriteIIC560(DISPLAY_CTRL,i);		//fifo auto lock, auto HTotal 

#if PanelID == CPT_CLAA170EA07P
//		printf("DCLK x = %ld\r\n",ulDotClk);
		Reg0x154 = ReadIIC560(0x154);
		if(Reg0x154 != 0){
//			WriteIIC560(INSIDE_CTRL3,0x01);		//set display normal
			WriteIIC560(DISPLAY_MUTE_CTRL,0x00);		//set display normal
		}
		WriteIIC560(INSIDE_CTRL1,0x12);	//read Hr2
		WriteIIC560(DISPLAY_CTRL,(DisplayControl & ~BIT_5));		//manual HTotal 

		WaitSetup(8);
		if(usTmpHSync == 0xffff){
			WriteIIC560(DISPLAY_CTRL,DisplayControl);		//fifo auto lock, auto HTotal 
			Reg0x154 = 0x02;		//restore display control
		}
		else{
			Hr2 = ReadWordIIC560(HR_VALUE);
//			printf("Hr2 = %x\r\n",Hr2);
			i = ReadWordIIC560(MISC_O_RD_LI) & 0x0fff;
			dstVtotal = i + PanelHeight;
			WriteWordIIC560(DV_TOTAL_LI,dstVtotal);		// Display Vtotal
//			printf("dstVtotal 1 = %d\r\n",dstVtotal);
//			if((Hr2 > 0x480) && (Hr2 < 0x5f0)){
			if(Hr2 > 0x480){
				temp = (float)ulDotClk * (Hr2 - 0x480);
				temp = temp / ((unsigned long)dstVtotal*dstHtotal);
				ulDotClk -= temp;
				SetDPLL();
			}
/*			if(abs(Hr2 - 640) < 128){
				temp = (float)ulDotClk * (Hr2 - 512);
				temp = temp / ((unsigned long)dstVtotal*dstHtotal);
				ulDotClk -= temp;
				SetDPLL();
			}*/
		}
//		printf("DCLK y = %ld\r\n",ulDotClk);
		WriteIIC560(DISPLAY_CTRL,DisplayControl);		//fifo auto lock, auto HTotal 
		WriteIIC560(0x154,Reg0x154);		//restore display control
		WriteIIC560(INSIDE_CTRL1,0x00);
#endif



	if(DispActiveHeight != PanelHeight){
		i = ReadIIC560(DISPLAY_CTRL);
		WriteIIC560(DISPLAY_CTRL,(i & ~BIT_5));		//manual HTotal
		WriteWordIIC560(DV_BG_LEN_LI,PanelHeight);		// Display VActive
	}

//ERROR1:

#if Panel_Spread_Spect_En == 0xff
	i = (PanelSpreadSpectrumCtrl << 1) | BIT_0;
	WriteIIC560(SSC_CTRL,i);
#endif
}

void SetDPLL(void)
{
unsigned long temp;
	WriteIIC560(DPLL_CTRL1,0x00);
#if NT68167
	WriteIIC560(DPLL_FREQ_CTRL,0x00);
	temp = ((float)ulDotClk * 16384) / 1500000;
#else

#if PanelXga == 0
	WriteIIC560(DPLL_FREQ_CTRL,0x10);
	temp = ((float)ulDotClk * 16384) / 1500000;
#else
	if(ulDotClk > 90000000){
		WriteIIC560(DPLL_FREQ_CTRL,0x10);
		temp = ((float)ulDotClk * 16384) / 1500000;
	}
	else if(ulDotClk > 40000000){
		WriteIIC560(DPLL_FREQ_CTRL,0x11);
		temp = ((float)ulDotClk * 32768) / 1500000;
	}
	else if(ulDotClk > 25000000){
		WriteIIC560(DPLL_FREQ_CTRL,0x12);
		temp = ((float)ulDotClk * 65536) / 1500000;
	}
	else{
		WriteIIC560(DPLL_FREQ_CTRL,0x13);
		temp = ((float)ulDotClk * 131072) / 1500000;
	}
#endif
#endif
	WriteIIC560(DDDS_RATIO_LI,(unsigned char)temp);
	WriteIIC560(DDDS_RATIO_MI,(unsigned char)(temp >> 8));
	WriteIIC560(DDDS_RATIO_HI,(unsigned char)(temp >> 16));
	WriteIIC560(DPLL_CTRL1,0x01);

#if NT68167
	#if _167_VERSION_B	
		WriteIIC560(DPLL_CTRL1,0x09);	
		WriteIIC560(DPLL_CTRL1,0x01);
	
		DebugModeEn();
	#endif
#endif

}

void SetHP(void)
{
// Horizontal Start
#ifdef R640_TUNE
	if(H_ActiveTab[ucResolution] == 640)
		WriteWordIIC560(GI_CAP_HBEG_LI,usHPStart<<1);
	else
#endif
	WriteWordIIC560(GI_CAP_HBEG_LI,usHPStart);

	NVTprint1("usHPStart = %d\r\n",usHPStart);

}

void SetVP(void)
{
// Vertical Start
	if ( bIsInterlaced == TRUE ) {
		WriteWordIIC560(GI_CAP_VBEGE_LI,(usVPStart-ucVPOffset+1));
		WriteWordIIC560(GI_CAP_VBEGO_LI,(usVPStart-ucVPOffset));
	}
	else{
		WriteWordIIC560(GI_CAP_VBEGO_LI,(usVPStart-ucVPOffset));
	}

	NVTprint1("usVPStart = %d\r\n",usVPStart);

}


void SetBrightness(void)
{
#ifndef BURST_BKL


	#define MaxBrightness 255
	#define MinBrightness 0
	#define MergeOffsetLevel 5

unsigned char value,tempbrightness;
#ifdef GREEN_POWER
		if(bVideoMuted == TRUE)
			tempbrightness = GREEN_POWER_BRIGHTNESS;
		else
			tempbrightness = ucBrightness;
#else
		tempbrightness = ucBrightness;
#endif
	
//	value = ((unsigned short)ucBrightness * 160) / 100+95;
	value = ((unsigned short)ucBrightness * 255 + 50) / 100;
//	value = ((unsigned short)tempbrightness * (MaxBrightness-MinBrightness) + 50) / 100 + MinBrightness;

/*
#ifdef _USE_PWM_B_
	WriteIIC560(PWM_CTRL1,0x00);	
#else
	WriteIIC560(PWM_CTRL0,0x00);	
#endif
*/
//------------ +jwshin 111214
WriteIIC560(PWM_CTRL1,0x00);
//-----------------------

#define INV_INVERTOR	123				// +jwshin 120223
#ifdef INV_INVERTOR
	#ifdef _USE_PWM_B_
	
		//----------------------- 사용 루틴...						PWM1이 PWMA 임.~!!!!
		WriteIIC560(PWM1_LCNT,value);	//low		//PWMB
		WriteIIC560(PWM1_HCNT,255-value);	//high


	#else
		WriteIIC560(PWM0_LCNT,value);	//low		//PWMB
		WriteIIC560(PWM0_HCNT,255-value);	//high
	#endif
#else
	#ifdef _USE_PWM_B_
		WriteIIC560(PWM1_LCNT,255-value);	//low		//PWMB
		WriteIIC560(PWM1_HCNT,value);	//high
	#else
		WriteIIC560(PWM0_LCNT,255-value);	//low		//PWMB
		WriteIIC560(PWM0_HCNT,value);	//high
	#endif
#endif
//	printf("ucBrightness = %d\r\n",(unsigned short)ucBrightness);
//	printf("Brightness PWM = %d\r\n",(unsigned short)value);
//	printf("Bri=%d, H=%d\r\n",(unsigned short)ucBrightness,(unsigned short)value);
	if(tempbrightness < MergeOffsetLevel){
		ucBrightnessLevel = MergeOffsetLevel - tempbrightness;
	}
	else{
		ucBrightnessLevel = 0;
	}
	SetContrastRGB();
//---------------------------------	   BURST_BKL 이 Define 된 경우... 사용안하는 루틴...
#else
#define MaxBrightness 255
#define MinBrightness 48
#define MergeOffsetLevel 5
unsigned char value, ch;
idata unsigned long PWM_Total,BriFreq;

	BriFreq = 2400;
//	PWM_Total = ulDispHfreq * 10 / 25;	//250Hz					
	PWM_Total = (unsigned long)((float)ulDispHfreq * 10 / BriFreq + 0.5);

#ifdef _USE_PWM_B_
	if(PWM_Total > 255){
		value = 0x30; 
		PWM_Total >>= 1;
	}
	else{
		value = 0x10;
	}
	value |= 0x80;

	WriteIIC560(PWM_CTRL1,value);
#else
	if(PWM_Total > 255){
		value = 0x03; 
		PWM_Total >>= 1;
	}
	else{
		value = 0x01;
	}
	value |= 0x08;

	WriteIIC560(PWM_CTRL1,value);
#endif

	if ( ucBrightness > 100 ) ucBrightness=100;
	value = ((unsigned short)ucBrightness * (MaxBrightness-MinBrightness) + 50) / 100 + MinBrightness;
	value =(unsigned char)(PWM_Total*(unsigned short)value/255);

	ch = (unsigned char)(PWM_Total - value);
//	printf("Bri=%d, H/L = %d %d\r\n",(unsigned short)ucBrightness,(unsigned short)value,(unsigned short)ch);

#define INV_INVERTOR 123
#ifdef INV_INVERTOR
	#ifdef _USE_PWM_B_
		WriteIIC560(PWM1_LCNT,value);	//low
		WriteIIC560(PWM1_HCNT,ch);	//high
	#else
		WriteIIC560(PWM0_LCNT,value);	//low
		WriteIIC560(PWM0_HCNT,ch);	//high
	#endif
#else
	#ifdef _USE_PWM_B_
		WriteIIC560(PWM1_LCNT,ch);	//low
		WriteIIC560(PWM1_HCNT,value);	//high
	#else
		WriteIIC560(PWM0_LCNT,ch);	//low
		WriteIIC560(PWM0_HCNT,value);	//high
	#endif
#endif

#endif
//---------------- 미사용 루틴 끝...

#ifdef BF_DYNAMIC_BACKLIGHT
	if (ucBrightness != iCurDynBk){
#if BFDYNBK_TYPE == BFDYNBK_TYPE_1
		usBF_DYMBK_Timer_10ms = 300;
#endif
		iCurDynBk = ucBrightness;
	}
#endif
#if _SmartBright_ == ON
	SetBrightOffset();
#endif
//	printf("ucBrightness = %d\r\n",(unsigned short)ucBrightness);
}


void SetPanelIDX(void)
{
#if 0
	PWM_PANELIDX = 255 - ucPanelIDX;
#else
	SetBrightness();
#endif
}

#if 0
void SetContrast(void)
{
#if 1
/*
unsigned char k;
	if(ucBrightness < 80){
		k = ucBrightness + 48;		//48 ---- 178
		WriteIIC560(BK_CTRL1,0x0c);	// Enable random gain dithering mode // Jude 03/25/2005
		WriteIIC560(0x063,k);
#ifdef Debug
		printf("Contrast of ASIC = %x\r\n",(unsigned short)k);
#endif
	}
	else{
		WriteIIC560(BK_CTRL1,0x0c);	// Enable random gain dithering mode // Jude 03/25/2005
		WriteIIC560(0x063,0x80);
	}*/
unsigned char k;
	if(ucBrightness < 50){
		k = ucBrightness + 78;		//78 ---- 128
		WriteIIC560(BK_CTRL1,0x0c);	// Enable random gain dithering mode // Jude 03/25/2005
		WriteIIC560(BK_GAIN,k);
#ifdef Debug
		printf("Contrast of ASIC = %x\r\n",(unsigned short)k);
#endif
	}
	else{
		WriteIIC560(BK_CTRL1,0x0c);	// Enable random gain dithering mode // Jude 03/25/2005
		WriteIIC560(BK_GAIN,0x80);
	}
#else
unsigned char k;
	if(ucBrightness < 50){
//		k = 255 - (50 - ucBrightness);// + 78;		//78 ---- 128
		k = ((unsigned short)(50 - ucBrightness) * 16 +25) / 50;
		k = 255 - k;// + 78;		//78 ---- 128
		WriteIIC560(BK_CTRL1,0x0c);	// Enable random gain dithering mode // Jude 03/25/2005
		WriteIIC560(0x062,k);
#ifdef Debug
		printf("ucBrightness of ASIC = %x\r\n",(unsigned short)k);
#endif
	}
	else{
		WriteIIC560(BK_CTRL1,0x0c);	// Enable random gain dithering mode // Jude 03/25/2005
		WriteIIC560(0x062,0x00);
	}
#endif
}
#endif
	
void ForceToBackground(unsigned char color)
{
///	if(((flag1 & BIT_1) == 0)||((flag3 & BIT_0) != 0)){
#if _Enable_OD_ == ON
	WriteIIC560(0x1ee,0x02);//for OD
	WriteIIC560(0x4e0,0x08);//for OD
#endif
	if ( bBGMode == FALSE ) {

		ucBGColor = color;
		if((color & BIT_0) == 0)
			WriteIIC560(DP_BG_B,0x00);
		else
			WriteIIC560(DP_BG_B,0xff);
		if((color & BIT_1) == 0)
			WriteIIC560(DP_BG_G,0x00);
		else
			WriteIIC560(DP_BG_G,0xff);
		if((color & BIT_2) == 0)
			WriteIIC560(DP_BG_R,0x00);
		else
			WriteIIC560(DP_BG_R,0xff);

		WriteIIC560(DITPLAY_CHANNEL,0x00);	//RGB
		WriteIIC560(DISPLAY_MUTE_CTRL,0x02);
		//Set fource to background
		bBGMode = TRUE;
	}
	SetFreeRun();
}

void SetFreeRun(void)
{
xdata unsigned short i;
	if(bIsFRCMode == FALSE){
		ulDotClk = FreeRunH_Freq*PanelTypHTotal;
		SetDPLL();
//		ulDispHfreq = ulDotClk / PanelTypHTotal;			// burst mode
		ulDispHfreq = FreeRunH_Freq;			// jerry
//		SetBrightness();
		WriteWordIIC560(DV_TOTAL_LI,PanelTypVTotal);		// Display Vtotal
//		i = PanelMinVSyncBackPorch + PanelMinVSyncWidth;
		WriteWordIIC560(DV_BG_BEG_LI,PanelVActiveStart);		// Display PanelVActiveStart
		WriteWordIIC560(GDV_ACT_BEG_LI,PanelVActiveStart);		// Display PanelVActiveStart
		WriteWordIIC560(DH_HTOTAL_LI,PanelTypHTotal);		// Display Htotal

		i = (PanelTypHTotal - PanelWidth) / 3;
		WriteIIC560(DH_HS_WID,i);		 // Display H Pulse Width
		i <<= 1;
		WriteWordIIC560(DH_BG_BEG_LI,i);	//PanelHActiveStart
		WriteWordIIC560(GDH_ACT_BEG_LI,i);	//PanelHActiveStart

		bIsFRCMode = TRUE;
		NVTprint("SetFreeRun\r\n");
		SetBrightness();
	}
}

void SetDisplayNormal(void)
{
unsigned short Hi_Counter,Lo_Counter;
#if 0
//-----------------------------------------------------------------
//20040908 For DVI DE mode scaler shut down and 
	unsigned char  ch;

	SYNC_INT_DISABLE();
	ch = ReadIIC560(POWER_CTRL1);
	WriteIIC560(POWER_CTRL1,ch|BIT_5);	//chip warm reset
	WriteIIC560(POWER_CTRL1,ch);	//chip warm reset

#if DVI_MODE == DVI_DE_MODE
	// Jacky 20040623 For DE mode scaler shut down
	if(ucSignalType == sigDVI)	//DVI
	{
		//WriteIIC560(0x1a9,0x00);	//disable IRQ interrupt
		//WriteIIC560(0x1aa,0x00);
		ch = ReadIIC560(GI_SYNC_CTRL);
		WriteIIC560(GI_SYNC_CTRL,0x94);
		Sleep(20);
		WriteIIC560(GI_SYNC_CTRL,ch&(~BIT_7));
	}
#endif
	Sleep(80);
	WriteIIC560(SYNC_INT_FLAG1,0x3f);	//clear IRQ
	WriteIIC560(SYNC_INT_FLAG2,0x1f);
	SYNC_INT_ENABLE();
//-----------------------------------------------------------------
#endif

	//bDCReset = FALSE;
	bBGMode = FALSE;
	WriteIIC560(DISPLAY_MUTE_CTRL,0x00);		//comeback to image
//	Sleep(160);
	ucTime2Backlight = 128;
//	ucTime2Backlight = PowerUpInvTiming/10;
//ucTime2Backlight = 10;


//20050409 mingyu check the incorrect SOG signal in the white pattern.
	if(ucSignalType == sigSOG){
		Set_usTimer1_1ms(40);
		Hi_Counter = 0;
		Lo_Counter = 0;
		while(Get_usTimer1_1ms() != 0){

			if ( GetHsyncLevel == FALSE ) {
				Lo_Counter ++;
			}
			else{
				Hi_Counter ++;
			}
		}

		NVTprint1("H4 = %d\r\n", Hi_Counter);
		NVTprint1("L4 = %d\r\n", Lo_Counter);

		Hi_Counter >>= 2;
		if((Hi_Counter > Lo_Counter)&&( Lo_Counter > 100)){

			NVTprint("Sync on green\r\n");

		}
		else{
			GoToSeparateSync();		//goto the Separate mode
		}
	}

	CheckModeChange();
	
	WriteIIC560(DITPLAY_CHANNEL, 0x80);
#if PanelID == CMO_M190E5_L0E  //neo 060811
	ScalerOutputON(1);
#endif
//--------------------------------------------------------------------------	

#if _Enable_OD_ == ON
	WriteIIC560(0x1ee,0x00);//for OD
	WriteIIC560(0x4e0,0x09);//for OD
#endif
	NVTprint("Set Display Normal\r\n");

}

void PowerSaving(void)
{
	WriteIIC560(OSD_CTRL1,0x00);
	if(!bStandalone){
		PWM_VOLUME = 0xff;
		AUDIO_MUTE();
		AMP_STBY();
	}

	if(ucIsLFDemoMode) LFLeaveDemoMode(0);
	
//#if PanelID==AUO_M170EG01V8 || PanelID==AUO_M190EG02V0 ||  PanelID==LPL_LM170E01_TLBL  || PanelID == CPT_CLAA170EA07Q//neo 060530 addd CPT
//	BackLightOff();
//	Sleep(PowerDownInvTiming-PowerDownWhitePtn);
//	ForceToBackground(0x07);		// AU PANEL: GARBAGE WHEN DC ON/OFF
//	Sleep(PowerDownWhitePtn);
//#else
	BackLightOff();
	ForceToBackground(0x00);
	Sleep(PowerDownInvTiming);
//#endif
  

	ScalerPowerDown();					
	Set_usPoSvTimer(0);

//	if ( SCALER_VER >= VER_G )		
		WriteIIC560(DVI_CTRL13,0x00);
	WriteIIC560(POWER_CTRL2,(ReadIIC560(POWER_CTRL2) & ~BIT_1));	//DVI power down

#if _SmartBright_ == ON
	LightSensorOff();
#endif

	//-------------- +jwshin 120228   음 차단을 위해, PWM Value 강제로 Write...
	WriteIIC560(PWM0_LCNT,0xff);
	WriteIIC560(PWM0_HCNT,0);
	//-----------------------------------
	AUDIO_MUTE();
	AMP_STBY();


	printf("Power Saving\r\n");				// +jwshin 120228
}

void ScalerPowerDown(void)
{

//#if (ModelName==H190B7 && PanelID==AUO_M190EG02V0) || (PanelID == CPT_CLAA170EA07Q) //neo 060605
	WriteIIC560(0x154, 0xb1);//0x11
	Sleep(50);
//#endif

//	WriteIIC560(GPIO_CTRL,0x0c);							// -jwshin 120302					Sound Cotrol을 위해 PowerDown시 Port 초기화 Remark.
		//------------------ EMI 나 Energy Star Test 시에는 다시 Open할 것.~!
	WriteIIC560(LVDS_MISC_CTRL3,0x00);	//	output port pull low
	WriteIIC560(POWER_CTRL1,0x00);	//	output port power down
	WriteIIC560(LVDS_MISC_CTRL1,0x15);	//	output port pull low
	WriteIIC560(POWER_CTRL1,0x07);
//#if NT68167
//	WriteIIC560(POWER_CTRL2,0x41);
//#else
	WriteIIC560(POWER_CTRL2,0x00);
//#endif
	WriteIIC560(DPLL_CTRL1,0x00);
	WriteIIC560(DVI_CTRL12,0xa0);
	WriteIIC560(DISPLAY_CTRL,0x00);
#if NT68167
	WriteIIC560(ADC_POWER_UP,0x40);//0x00
	WriteIIC560(ADC_VREF_TEST, 0x57);
#else
	WriteIIC560(ADC_POWER_UP,0x00);
#endif

	Sleep(PowerDownPanelTiming);


//#if (ModelName==H190B7 && PanelID==AUO_M190EG02V0) || (PanelID == CPT_CLAA170EA07Q) //neo 060605
	WriteIIC560(0x154, 0x02);
//#endif

	PanelPowerOff();		//panle power off
	ucSyncStableTimer_10ms = 95;		//delay 1 second for power on/off

}

void ScalerPowerUp(void)
{
//printf("ScalerPowerUp\r\n");
#if NT68167
	if(ReadIIC560(ADC_POWER_UP) == 0x40){
#else
	if(ReadIIC560(ADC_POWER_UP) == 0){
#endif
		LED_GrnOn();
		LED_RedOff();

		ucSyncStableTimer_10ms += 20;
		while (ucSyncStableTimer_10ms!= 0);	// the time for DC [OFF --- ON] > 1second
		InitScaler();
		SetContrastRGB();

//		SelectGamma();
	}
	Set_usPoSvTimer(500);
	bVideoMuted = FALSE;
	usTmpHSync = 0xffff;
	usTmpVSync = 0xffff;
	NVTprint("WakeUp\r\n");
}

void LoadADC_Gain(void)
{
	//offset
		ucR_ADC_Offset = Read24C16(EPADDR_ADCR_OFFSET);	//0x4a = ADC r offset
		ucG_ADC_Offset = Read24C16(EPADDR_ADCG_OFFSET);	//0x4b = ADC g offset
		ucB_ADC_Offset = Read24C16(EPADDR_ADCB_OFFSET);	//0x4c = ADC b offset
	//gain
		ucR_ADC_Gain = Read24C16(EPADDR_ADCR_GAIN);	//0x4d = ADC r gain
		ucG_ADC_Gain = Read24C16(EPADDR_ADCG_GAIN);	//0x4e = ADC g gain
		ucB_ADC_Gain = Read24C16(EPADDR_ADCB_GAIN);	//0x4f = ADC b gain
	
	
//	WriteIIC560(BK_GAIN, 0x78);		// 2005-11-22 jerry		for ghost noise issue testing...
	
	WriteIIC560(ROFFSET,ucR_ADC_Offset);
	WriteIIC560(GOFFSET,ucG_ADC_Offset);
	WriteIIC560(BOFFSET,ucB_ADC_Offset);
	WriteIIC560(RGAIN_HI,ucR_ADC_Gain);
	WriteIIC560(GGAIN_HI,ucG_ADC_Gain);
	WriteIIC560(BGAIN_HI,ucB_ADC_Gain);
}

void SetVolume(void)
{
/*	
unsigned char value;

	if(bMute || ucVolume == 0){
		//PWM_VOLUME = 0;
		AUDIO_MUTE();
		AMP_STBY();
//printf("SetVolume=MUTE\r\n");
	}
	else{
#if 1
		if ( ucVolume> 60)
			value = (((unsigned short)(ucVolume-60)*3)>>2)+204;
		else
			value = (((unsigned short)ucVolume*4)/3)+124;
#else
//		value = 255 - ((unsigned short)ucVolume * 255 / 100);
		value = 255 - ((unsigned short)ucVolume * 192 / 100);
#endif
		PWM_VOLUME = value;

		AMP_On();
		AUDIO_On();
//printf("SetVolume=%d\r\n",(unsigned short)ucVolume);		
	}
*/
//---------------------- -jwshin 111214    PWMB를 이용한 Volume제어를 위해 기존 Routine은 Remark...


//-------------- +jwshin 111214
	unsigned char value;
	if(bMute || ucVolume == 0) {
		AUDIO_MUTE();
		AMP_STBY();
	}
	
	else {
		value = 255 - ((unsigned short)ucVolume * 255 / 100);
		
		WriteIIC560(PWM0_LCNT,value);
		WriteIIC560(PWM0_HCNT,255-value);
		
		AMP_On();
		AUDIO_On();
	}
//	printf("SetVolume=%d\r\n",(unsigned short)ucVolume);		
//-------------------------------------------------------------		

	
}

/*
//	NT68665 SPEC. CHANGED
void SetScalerOffset(void)
{
unsigned char value;
//	value = Read24C16(EPADDR_SCALER_OFFSET);//0x17 = Scaler Offset
	value = ucBlackLevel ^ BIT_7;
	WriteIIC560(BK_CTRL1,0x0c);	// Enable random gain dithering mode // Jude 03/25/2005
	WriteIIC560(BK_OFFSET,value);
}
*/
#if NT68665
void CheckRegPage(unsigned short addr)
{
unsigned char page;
	page = (unsigned char)(addr>>8);
	if(page != ucRegPage){
		ucRegPage = page;
#if NT68665
		WriteIIC(SCALER_I2C_ADDR,0xff,ucRegPage);
#else
		SC_RegPage = ucRegPage;
#endif
	}
}
#endif
void WriteIIC560(unsigned short addr,unsigned char ch)
{
#if NT68665
	CheckRegPage(addr);
	WriteIIC(SCALER_I2C_ADDR,addr,ch);
#else
	unsigned char volatile *pBus;
	SC_RegPage = (unsigned char)(addr>>8);
	pBus = &SC_StarAddress;
	pBus += (unsigned char)addr;
	*pBus = ch;
#endif
}

void WriteWordIIC560(unsigned short addr,unsigned short value)
{
#if NT68665
	CheckRegPage(addr);
	WriteWordIIC(SCALER_I2C_ADDR,addr,value );
#else
	unsigned char volatile *pBus;
	SC_RegPage = (unsigned char)(addr>>8);
	pBus = &SC_StarAddress;
	pBus += (unsigned char)addr;
	*pBus = (unsigned char)value;
	pBus++;
	*pBus = (value >> 8);
#endif
}

#if 0//PBusProtocol
/*===============================================
===============================================*/
void SetDataPortAddr(void)
{
	Union Page;

	Page.w = 0x3B2;
	Pbus_Code = 0x80ff;
	*Pbus_Code = Page.b[0];
	Pbus_Code = 0x8000 + Page.b[1];
}
/*===============================================
===============================================*/
void SetDataPortData(unsigned char Data)
{	
	*Pbus_Code = Data;
}
/*===============================================
===============================================*/
unsigned char GetDataPortData(void)
{
	return *Pbus_Code;
}
/*===============================================
===============================================*/
#endif
/*===============================================
===============================================*/
/*
void ReadDataPort(void)
{
	unsigned char i;
	union {
		unsigned char UByte[4];
		unsigned long ULong;
	}temp;
	temp.ULong=0;

	//for(i = 0; i < ACE_PARTITIONS; i++)	// mark at 070702 by evan
	//	ulCurHisgrm[i] = 0;
#if PBusProtocol
	SetDataPortAddr();
	SetDataPortData(0x00);
	SetDataPortData(0x00);
#endif	
	for(i = 0; i < ACE_PARTITIONS; i++)
    	{
#if PBusProtocol
		temp.UByte[3] = GetDataPortData();
		Sleep(1);
		temp.UByte[2] = GetDataPortData();
		Sleep(1);
    		temp.UByte[1] = GetDataPortData();
#else
		temp.UByte[3] = ReadIIC560(0x3B2);
    		temp.UByte[2] = ReadIIC560(0x3B2);
    		temp.UByte[1] = ReadIIC560(0x3B2);

#endif
		ulCurHisgrm[i] = temp.ULong;
    		ulCurHisgrmTotal += ulCurHisgrm[i];
		//printf("histogram = %bd  %bx   %bx   %bx       %ld\n\r",i,temp.UByte[3],temp.UByte[2],temp.UByte[1],ulCurHisgrmTotal);
	}
}
*/
/*===============================================
===============================================*/
unsigned char ReadIIC560(unsigned short addr)
{
#if NT68665
unsigned char value;
	CheckRegPage(addr);
	value = ReadIIC(SCALER_I2C_ADDR,addr);
	return value;
#else
unsigned char value;
unsigned char volatile *pBus;
	SC_RegPage = (unsigned char)(addr>>8);
	pBus = &SC_StarAddress;
	pBus += (unsigned char)addr;
	value = *pBus;
	return value;
#endif
}

unsigned short ReadWordIIC560(unsigned short addr)
{
#if NT68665
unsigned short value;
	CheckRegPage(addr);
	value = ReadWordIIC(SCALER_I2C_ADDR,addr);
	return value;
#else
unsigned short value;
unsigned char volatile *pBus;
unsigned char ch;
	SC_RegPage = (unsigned char)(addr>>8);
	pBus = &SC_StarAddress;
	pBus += (unsigned char)addr;
	ch = *pBus;
	pBus++;
	value = *pBus;
	value <<= 8;
	value |= ch;
	return value;
#endif
}

void SetInterface(void)
{
#if PBusProtocol
	#define REG_072	0x00
#else
#if _INTERNAL_LDO_
	#define REG_072	0x00
#else
	#define REG_072	0x60
#endif
#endif

#if NT68667
	#if _INTERNAL_LDO_
		#define REG_1E6	0x01
	#else
		#define REG_1E6	0xa1
	#endif
#else
	#if _INTERNAL_LDO_
		#define REG_1E6	0x01
	#else
		#define REG_1E6	0x81
	#endif
#endif


//code unsigned short InterfaceTab[]={
//	0x000,0x020,0x021,0x023,0x196,0x012,0x072,0x028,0x1e6,0x1f4
//};
code unsigned short InterfaceTab[]={
	ADC_CTRL, GPORT_CTRL, CLAMP_BEGIN, DIGITAL_CTRL, GI_SYNC_CTRL,
	SOG_SLICER_CTRL, BP_SYNC_CTRL, 0x028, 0x1E6, 0x1F4
};
code unsigned char InterfaceDat[][10]={
#if NT68167
	{0x93,0xe1,0x81,0x00,0x64,0x00,(REG_072|BIT_0),0x01,REG_1E6,0xc0},				//sep	//0x000,0x072 from Alvin code
	{0x93,0xe1,0x81,0x40,0x65,0x00,REG_072,0x01,REG_1E6,0xc0},				//comp
//	{0x9b,0xe1,0x01,0x40,0x65,0x75,(REG_072|0x10),	0x01,(REG_1E6|0x10),	0xc0},	//SOG	//0x012=7c from Alvin code //0x012=75 from vincent reg
	{0x9b,0xe1,0x01,0x40,0x65,0xe5,(REG_072|0x10),	0x01,(REG_1E6|0x10),	0xc0},	//SOG	//0x012=e5 mingyu test
#else
	{0x02,0xe1,0x81,0x00,0x60,0x00,REG_072,0x01,REG_1E6,0xc0},				//sep
	{0x12,0xe1,0x81,0x40,0x61,0x00,REG_072,0x01,REG_1E6,0xc0},				//comp
	{0x1a,0xe1,0x01,0x40,0x61,0xb4,(REG_072|0x10),0x01,(REG_1E6|0x10),0xc0},	//SOG
#endif
#if DVI_MODE == DVI_HV_MODE
	{0x10,0xe3,0x01,0x00,0x90,0x00,REG_072,0x0f,REG_1E6,0x80},				//DVI
#elif DVI_MODE == DVI_DE_MODE
	{0x10,0xe3,0x01,0x00,0x20,0x00,REG_072,0x0f,REG_1E6,0x80},				//DVI
#elif DVI_MODE == DVI_HVDE_MODE 
	{0x10,0xe3,0x01,0x08,0x90,0x00,REG_072,0x0f,REG_1E6,0x80},				//DVI
#endif
};
unsigned char i;
//printf("SetInterface=%d\r\n",(unsigned short)ucSignalType);
	for(i=0; i<10; i++){
		WriteIIC560(InterfaceTab[i],InterfaceDat[ucSignalType][i]);
	}

	WriteIIC560(0x1D8, DT1D8);
	WriteIIC560(0x1DA, DT1DA);
	WriteIIC560(BK_CTRL1,0x08);
	WriteIIC560(0x1DB,DT1DB);	//10 bit gamma dithering mode
	
	if(ucSignalType == sigSOG)
		WriteIIC560(GOFFSET, ucG_ADC_Offset+5);
	else
		WriteIIC560(GOFFSET, ucG_ADC_Offset);
}


void ScalerON(void)
{
//printf("ScalerON\r\n");
	PanelPowerOn();
	Sleep(PowerUpPanelTiming+43);

	WriteIIC560(POWER_CTRL1,0x40);	//output port power on
#if NT68167
	#if _167_VERSION_B
		WriteIIC560(LVDS_MISC_CTRL3,0xe5);	//	output port
		WriteIIC560(LVDS_MISC_CTRL1,0x05);	//	output port
	#else
		WriteIIC560(LVDS_MISC_CTRL3,0xe0);	//	output port
		WriteIIC560(LVDS_MISC_CTRL1,0x05);	//	output port
	#endif
#elif NT68670B||NT68667
	WriteIIC560(LVDS_MISC_CTRL1,0x47);	//	output port
	WriteIIC560(LVDS_MISC_CTRL2,0x28);	//	output port
	WriteIIC560(LVDS_MISC_CTRL3,0xc0);	//	output port
#else
	WriteIIC560(LVDS_MISC_CTRL3,0xc0);	//	output port
	WriteIIC560(LVDS_MISC_CTRL1,0x05);	//	output port
#endif

#ifdef _USE_PWM_B_
//	WriteIIC560(GPIO_CTRL,0x2c);		
		WriteIIC560(GPIO_CTRL,0x3c);		// +jwshin 111214
#else	
	WriteIIC560(GPIO_CTRL,0x1c);
#endif

	Sleep(PowerUpInvTiming);
}

void InputSourceSelect(void)
{
//	switch(ucPowerStatus & ~SoftPowerOnFlag){
	switch(ucSource){
	case mSource_VGA:	//analog 0
#if SCALAR_BOARD==PCBA_Q50x50
		WriteIIC560(ADC_MID_CH_SEL,0x00);
#else
		WriteIIC560(ADC_MID_CH_SEL,0x04);
#endif
//		GoToSeparateSync();
		if(CheckSOG() == 0)
			GoToCompositeSync();
		break;
	case mSource_DVI:	//digital

//WriteIIC560(DVI_CTRL15, 0xf3);
//WriteIIC560(DVI_CTRL12,0x20);	//DVI power up
					
		GoToDVI();
		break;
	case mSource_HDMI:
		GoToDVI();
		break;
	case mSource_VIDEO:
//#ifdef AnalogPort0
		WriteIIC560(ADC_MID_CH_SEL,0x00);
//#else
//		WriteIIC560(ADC_MID_CH_SEL,0x04);
//#endif
//		GoToSeparateSync();
		if(CheckSOG() == 0)
			GoToCompositeSync();
		break;
	}
}

#if DUAL_MODE==ON
void DVIBandWidthDetection(void)
{
unsigned char DVI_ClockTemp,loop;
#if 1
	WriteIIC560(DVI_CTRL14,0x00);
	WriteIIC560(DVI_CTRL13,0x00);
	WriteIIC560(DVI_CTRL12,0xa0);	//DVI power off
	WriteIIC560(DVI_CTRL12,0x20);	//DVI power on
	Sleep(20);

	loop = 25;
	ucCurrentDVIClk = 0;
	do{
		DVI_ClockTemp = ReadIIC560(DVI_PIXELCLK);
		if(abs(ucCurrentDVIClk - DVI_ClockTemp) > 2){
			ucCurrentDVIClk = DVI_ClockTemp;
			loop = 25;
		}
		loop--;
		
	#ifdef _SCDT_SOLUTION_
		// To avoid long-time loop if clock is abnormal , escape loop by invalid DVI clock range 
		// Jude 2008/04/30
		if ((ucCurrentDVIClk < 20) || (ucCurrentDVIClk > 180)) return;
	#endif
	
	}while(loop != 0);
//	NVTprintf1("DVI_Clock = %d\r\n",(unsigned short)ucCurrentDVIClk);
	if(ucCurrentDVIClk < 20)
		return;

	if(ucCurrentDVIClk <= 50){
		WriteIIC560(DVI_CTRL13,0x04);
		WriteIIC560(DVI_CTRL14,0x03); 
		WriteIIC560(DVI_CTRL12,0xa0);	//DVI power off
		WriteIIC560(DVI_CTRL12,0x20);	//DVI power on
	}
	Sleep(180);
	if((ucCurrentDVIClk <= 140)&&(ucCurrentDVIClk >= 100)){		//2005-01-06 DVI dot flash
		WriteIIC560(DVI_CTRL4,0x0d);
	}
	else{
		WriteIIC560(DVI_CTRL4,0x00);
	}
	
#else	

	//WriteIIC560(DVI_CTRL6,0x1f);
	WriteIIC560(DVI_CTRL14,0x00);
	WriteIIC560(DVI_CTRL13,0x00);
	Sleep(20);

	loop = 25;
	ucCurrentDVIClk = 0;
	do{
		DVI_ClockTemp = ReadIIC560(DVI_PIXELCLK);
		if(abs(ucCurrentDVIClk - DVI_ClockTemp) > 2){
			ucCurrentDVIClk = DVI_ClockTemp;
			loop = 25;
		}
		loop--;
	}while(loop != 0);
//	printf("DVI_Clock = %d\r\n",(unsigned short)ucCurrentDVIClk);
	if(ucCurrentDVIClk < 20)
		return;

	if(ucCurrentDVIClk <= 50){
		WriteIIC560(DVI_CTRL13,0x04);
		WriteIIC560(DVI_CTRL14,0x03); 
	}
	Sleep(180);
	if((ucCurrentDVIClk <= 140)&&(ucCurrentDVIClk >= 100)){		//2005-01-06 DVI dot flash
		WriteIIC560(DVI_CTRL4,0x0d);
	}
	else{
		WriteIIC560(DVI_CTRL4,0x00);
	}
#endif
}
#endif

#if PanelID == CMO_M190E5_L0E  //neo 060811
void ScalerOutputON(bit WithoutDelay)
{
	if(bScalerOutput == 0){
//printf("ScalerOutputON\r\n");
		PanelPowerOn();
		Sleep(PowerUpPanelTiming);
#if NT68167
	#if _167_VERSION_B
		WriteIIC560(LVDS_MISC_CTRL3,0xe5);	//	output port
		WriteIIC560(LVDS_MISC_CTRL1,0x05);	//	output port
	#else
		WriteIIC560(LVDS_MISC_CTRL3,0xe0);	//	output port
		WriteIIC560(LVDS_MISC_CTRL1,0x05);	//	output port
	#endif
#elif NT68670B||NT68667
	WriteIIC560(LVDS_MISC_CTRL1,0x47);	//	output port
	WriteIIC560(LVDS_MISC_CTRL2,0x28);	//	output port
	WriteIIC560(LVDS_MISC_CTRL3,0xc0);	//	output port
#else
	WriteIIC560(LVDS_MISC_CTRL3,0xc0);	//	output port
	WriteIIC560(LVDS_MISC_CTRL1,0x05);	//	output port
#endif

#ifdef _USE_PWM_B_
//	WriteIIC560(GPIO_CTRL,0x2c);
	WriteIIC560(GPIO_CTRL,0x3c);		// +jwshin 111214
#else	
	WriteIIC560(GPIO_CTRL,0x1c);
#endif
		
		if(WithoutDelay == 0)
			Sleep(PowerUpInvTiming<<2);
		else
			Sleep(PowerUpInvTiming);
			
		bScalerOutput = 1;
		
	}
}

void ScalerOutputOFF(void)
{
	if((bScalerOutput != 0)&&(IsBackLightOn() == OFF)){
		WriteIIC560(GPIO_CTRL,0x0c);	// PWM0,VSO HSOoutput
		Sleep(10);
		WriteIIC560(LVDS_MISC_CTRL3,0x00);	//	output port pull low
		WriteIIC560(POWER_CTRL1,0x00);	//	output port power down
		WriteIIC560(LVDS_MISC_CTRL1,0x15);	//	output port pull low
		Sleep(PowerDownPanelTiming);
		PanelPowerOff();
		bScalerOutput = 0;
		//printf("ScalerOutputOFF\r\n");
	}
}
#endif


