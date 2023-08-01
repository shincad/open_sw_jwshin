#include <math.h>
#include "Factory.H"
#include "RAM.H"
#include "Osd.H"
#include "ModeHandle.H"
#include "Scaler.H"
#include "NT686xx_SC_REG.H"
//#include "MyDef.H"
#include "Mis.H"
#include "NVRam.H"
#include "AutoAdj.H"	// AutoColor()
#include "sRGB.H"		// SetContrastRGB()
#include "OSD_Tab.H"	// VersionStr
#include "Panel.H"		// PanelName
#include "UserAdj.H"	// SetColorTemp()
#include "Rom_map.H"	// MCU_DATAMAP[]
#include "Board.H"
#include "8051.H"
#include "BFControl.H"
#include "OSD_LF.H"
#include "MCU.H"

code unsigned char YES[]={	3,"YES"};
code unsigned char NO[]={	2,"NO"};
code unsigned char OK[]={	2,"OK"};
//code unsigned char ReturnText[]={	6,"Return"};
code unsigned char ResetText[]={	5,"Reset"};
code unsigned char TD_ResetText[]={	8,"TD-Reset"};

idata unsigned char ucFactoryStatus;
	#define fsMENU 0
	#define fsVALUE 1


enum OSD_FACTORY {
	mfAUTO,
	mfBURNING,
	mfBLACKLEVEL,
	mfBRIGHTNESS,	mfIDX,
	mfCONTRAST,
	
	mfGAINR,	mfGAING,	mfGAINB,
	mfOFFSETR,	mfOFFSETG,	mfOFFSETB,
	mfSRGBR,	mfSRGBG,	mfSRGBB,
	mf5000R,	mf5000G,	mf5000B,
	mf6500R,	mf6500G,	mf6500B,
	mf7500R,	mf7500G,	mf7500B,
	mf8200R,	mf8200G,	mf8200B,
	mf9300R,	mf9300G,	mf9300B,
	mf11500R,	mf11500G,	mf11500B,
	
	mfADDRESS,	mfWR,
	mfRESET,
	mfTDRESET,
	mfRETURN
};
idata enum OSD_FACTORY ucFactoryIndex;


typedef struct {
	unsigned char x;
	unsigned char y;
	unsigned char len;
}_LIGHTBAR_;
	
code _LIGHTBAR_ LBar[] = {		// { X, Y, LENGTH}
		{0,4,7},
		{0,5,7},
		{0,6,7},
		{0,7,7},  {12,7,3},
		{0,8,7},
		{7,9,1},  {12,9,1},  {17,9,1},
		{7,10,1},{12,10,1},{17,10,1},
		{7,11,1},{12,11,1},{17,11,1},
		{7,12,1},{12,12,1},{17,12,1},
		{7,13,1},{12,13,1},{17,13,1},
		{7,14,1},{12,14,1},{17,14,1},
		{7,15,1},{12,15,1},{17,15,1},
		{7,16,1},{12,16,1},{17,16,1},
		{7,17,1},{12,17,1},{17,17,1},

		{0,18,7}, {20,18,3},
		{0,19,7},
		{0,20,7},
		{0,21,7},
};



// Scaler Register R/W
unsigned short reg_addr;
unsigned char reg_value;
void RegAddrInc(unsigned short*);
void RegAddrDec(unsigned short*);
void RegInc(unsigned char*);
void RegDec(unsigned char*);
void RegWrite();
void RegRead();


void FactorySelect();
void FactoryUnSelect();
void FactorySelectValue();
void FactoryUnSelectValue();
//void FactoryReset();
void	FactoryShowAutoColor(bit);
void	FactoryShowBurnin();
void FactoryShowPanel();
//void OsdInit_F(unsigned char W,unsigned char H);
void FactoryColorUp(unsigned char*);
void FactoryColorDown(unsigned char*);
void ADC_R_Down(void);
void ADC_G_Down(void);
void ADC_B_Down(void);
void ADC_R_Up(void);
void ADC_G_Up(void);
void ADC_B_Up(void);
void ADC_R_OffsetDown(void);
void ADC_G_OffsetDown(void);
void ADC_B_OffsetDown(void);
void ADC_R_OffsetUp(void);
void ADC_G_OffsetUp(void);
void ADC_B_OffsetUp(void);
//void ADC_GainOffsetUp(unsigned short addr, unsigned char *value);
//void ADC_GainOffsetDown(unsigned short addr, unsigned char *value);


// --------------------------------------------------------------------
//			FACTORY FUNCTIONS
// --------------------------------------------------------------------

void FactoryShowValue(unsigned char attr, enum OSD_FACTORY index, unsigned short value)
{
	if(index >= mfGAINR &&  index <= mfOFFSETB){
		ShowNum(attr, LBar[index].x+1, LBar[index].y, 255-value);
	}
	else if(index >= mfSRGBR &&  index <= mf11500B){
		ShowNum(attr, LBar[index].x+1, LBar[index].y, value);
	}
	else if(index == mfADDRESS){
		ShowNum(attr, LBar[index].x+LBar[index].len+2, LBar[index].y, (unsigned char)(value>>8));
		ShowNum(attr, LBar[index].x+LBar[index].len, LBar[index].y, value);
	}
	else if(index == mfWR){
		ShowNum(attr, LBar[index].x-5, LBar[index].y, value);
	}
	else{
		ShowNum(attr, LBar[index].x+LBar[index].len, LBar[index].y, value);
	}
}

void FactoryEnterMode()
{
	bFactoryMode = TRUE;
	/*
	if(ucLFMode==LF_MODE_OFF){
		ucBrightness = Read24C16(EPADDR_BRIGHT_FACTORY);
		ucContrast = Read24C16(EPADDR_CONTRAST_FACTORY);
		Write24C16(EPADDR_BRIGHT, ucBrightness);
		Write24C16(EPADDR_CONTRAST, ucContrast);
		ucBrightnessUser = ucBrightness;
		ucContrastUser = ucContrast;
		Write24C16(EPADDR_BRIGHT_USER,ucBrightnessUser);//0x36 = brightness user
		Write24C16(EPADDR_CONTRAST_USER,ucContrastUser);//0x37 = contrast user
		SetBrightness();
		SetContrastRGB();
	}
	*/
	StartDDCCI();	//START DDCCI WHEN GO INTO FACTORY MODE
}

void FactoryShowMenu()
{

code unsigned char AutoLevelText[]={10,"Auto Level"};
code unsigned char BurnInText[]={6,"Burnin"};
code unsigned char BlackLevelText[]={10,"Black Lvl."};
code unsigned char BrightnessText[]= {6,"Bright."};
code unsigned char IDXText[]={3,"IDX"};
code unsigned char ContrastText[]= {6,"Contr."};
code unsigned char GainText[]={4,"Gain"};
code unsigned char OffsetText[]={6,"Offset"};
code unsigned char SRGBText[]={4,"sRGB"};
code unsigned char Color5000Text[]={4,"5000"};
code unsigned char Color6500Text[]={4,"6500"};
code unsigned char Color7500Text[]={4,"7500"};
code unsigned char Color8200Text[]={4,"8200"};
code unsigned char Color9300Text[]={4,"9300"};
code unsigned char Color11500Text[]={5,"11500"};
code unsigned char AddressText[]={5,"Addr."};
code unsigned char WRText[]={2,"WR"};
code unsigned char POTText[]={3,"POT"};
code unsigned char ExitText[] = {4,"Exit"};

code unsigned char H_Text[]={1,"H"};
code unsigned char R_Text[]={1,"R"};
code unsigned char G_Text[]={1,"G"};
code unsigned char B_Text[]={1,"B"};
code unsigned char Symbol1[]={1,"="};
code unsigned char Scaler_Text[]={7,"NT68673"};
code unsigned char Panel_Text[]={20, PANEL_STRING};
code unsigned char HDCP_Text[]={4,"HDCP"};

unsigned char i;

	ucOSDType = FACTORY;
	ucOSDLvl1_Cursor = 0;

	OsdInit(OSD_FACTORY_W,OSD_FACTORY_H);
	// ----------------------------------------

	
	ucStrAlignment = 0;
	usFontIndex = 32;
	ucStrWidth = 1;

	WriteArialFont(ModelStrTab);
	WriteXY_String(0,0,0);
	WriteArialFont(VersionStrTab);
	WriteXY_String(0,12,0);
	WriteArialFont(Scaler_Text);
	WriteXY_String(0,0,1);
	WriteArialFont(Panel_Text);
	WriteXY_String(0,0,2);


	WriteArialFont(AutoLevelText);
	WriteXY_String(0, LBar[mfAUTO].x, LBar[mfAUTO].y);
	WriteArialFont(BurnInText);
	WriteXY_String(0, LBar[mfBURNING].x, LBar[mfBURNING].y);
	WriteArialFont(BlackLevelText);
	WriteXY_String(0, LBar[mfBLACKLEVEL].x, LBar[mfBLACKLEVEL].y);
	WriteArialFont(BrightnessText);
	WriteXY_String(0, LBar[mfBRIGHTNESS].x, LBar[mfBRIGHTNESS].y);
	WriteArialFont(IDXText);
	WriteXY_String(0, LBar[mfIDX].x, LBar[mfIDX].y);
	WriteArialFont(ContrastText);
	WriteXY_String(0, LBar[mfCONTRAST].x, LBar[mfCONTRAST].y);

	WriteArialFont(GainText);
	WriteXY_String(0,0,9);
	WriteArialFont(OffsetText);
	WriteXY_String(0,0,10);
	WriteArialFont(SRGBText);
	WriteXY_String(0,0,11);		
	WriteArialFont(Color5000Text);
	WriteXY_String(0,0,12);
	WriteArialFont(Color6500Text);
	WriteXY_String(0,0,13);
	WriteArialFont(Color7500Text);
	WriteXY_String(0,0,14);
	WriteArialFont(Color8200Text);
	WriteXY_String(0,0,15);
	WriteArialFont(Color9300Text);
	WriteXY_String(0,0,16);
	WriteArialFont(Color11500Text);
	WriteXY_String(0,0,17);

	WriteArialFont(AddressText);
	WriteXY_String(0, LBar[mfADDRESS].x, LBar[mfADDRESS].y);
	WriteArialFont(ResetText);
	WriteXY_String(0, LBar[mfRESET].x, LBar[mfRESET].y);	
	WriteArialFont(ExitText);
	WriteXY_String(0, LBar[mfRETURN].x, LBar[mfRETURN].y);
	WriteArialFont(Symbol1);
	WriteXY_String(0,12,18);
	WriteArialFont(WRText);
	WriteXY_String(0, LBar[mfWR].x, LBar[mfWR].y);
	WriteArialFont(POTText);
	WriteXY_String(0,11,19);
	WriteArialFont(H_Text);
	WriteXY_String(0,20,19);


	WriteArialFont(R_Text);
	for (i=0;i<9;i++)
		WriteXY_String(0,  7,  9+i);		
	
	WriteArialFont(G_Text);
	for (i=0;i<9;i++)
		WriteXY_String(0, 12, 9+i);
		
	WriteArialFont(B_Text);
	for (i=0;i<9;i++)
		WriteXY_String(0, 17, 9+i);

	{
		unsigned char glob_buff[SN_LEN+1];
		for (i=1; i<SN_LEN+1; i++)
		{
			glob_buff[i] = ucSerialNum[i-1];
			if ( glob_buff[i]==0x00 || glob_buff[i]==0x0A) break;
		}
		glob_buff[0] = i-1;
		WriteArialFont(glob_buff);
		WriteXY_String(0,12,1);
	}

	if ( 	Read24C16(NVRAM_HDCP_KEY+290)=='P' &&
		Read24C16(NVRAM_HDCP_KEY+291)=='H' &&
		Read24C16(NVRAM_HDCP_KEY+292)=='L' &&
		Read24C16(NVRAM_HDCP_KEY+293)=='H' &&
		Read24C16(NVRAM_HDCP_KEY+294)=='8' )
	{
		WriteArialFont(HDCP_Text);
		WriteXY_String(0,12,2);
	}
#ifdef DEMO_HDCP_KEY
	else if(Read24C16(NVRAM_HDCP_KEY+290)==0x01 &&
		Read24C16(NVRAM_HDCP_KEY+291)==0x02 &&
		Read24C16(NVRAM_HDCP_KEY+292)==0x03 &&
		Read24C16(NVRAM_HDCP_KEY+293)==0x04 &&
		Read24C16(NVRAM_HDCP_KEY+294)==0x05 )
	{
		code unsigned char HDCP_Demo_Text[]={8,"HDCPdemo"};
		WriteArialFont(HDCP_Demo_Text);
		WriteXY_String(0,12,2);
	}
#endif

	WriteArialFont(TD_ResetText);
	WriteXY_String(1, LBar[mfTDRESET].x, LBar[mfTDRESET].y);


	FactoryShowBurnin();

	FactoryShowValue(0, mfBLACKLEVEL, (unsigned short)ucBlackLevel);
	FactoryShowValue(0, mfBRIGHTNESS, (unsigned short)ucBrightness);
	FactoryShowValue(0, mfIDX, (unsigned short)ucPanelIDX);
	FactoryShowValue(0, mfCONTRAST, (unsigned short)ucRGB_OFFSET);
	FactoryShowValue(0, mfGAINR, (unsigned short)(ucR_ADC_Gain));
	FactoryShowValue(0, mfGAING, (unsigned short)(ucG_ADC_Gain));	
	FactoryShowValue(0, mfGAINB, (unsigned short)(ucB_ADC_Gain));
	FactoryShowValue(0, mfOFFSETR, (unsigned short)(ucR_ADC_Offset));
	FactoryShowValue(0, mfOFFSETG, (unsigned short)(ucG_ADC_Offset));	
	FactoryShowValue(0, mfOFFSETB, (unsigned short)(ucB_ADC_Offset));
	FactoryShowValue(0, mfSRGBR, (unsigned short)ucR_GainsRGB);
	FactoryShowValue(0, mfSRGBG, (unsigned short)ucG_GainsRGB);
	FactoryShowValue(0, mfSRGBB, (unsigned short)ucB_GainsRGB);
	FactoryShowValue(0, mf5000R, (unsigned short)ucR_Gain5000K);
	FactoryShowValue(0, mf5000G, (unsigned short)ucG_Gain5000K);
	FactoryShowValue(0, mf5000B, (unsigned short)ucB_Gain5000K);
	FactoryShowValue(0, mf6500R, (unsigned short)ucR_Gain6500K);
	FactoryShowValue(0, mf6500G, (unsigned short)ucG_Gain6500K);
	FactoryShowValue(0, mf6500B, (unsigned short)ucB_Gain6500K);
	FactoryShowValue(0, mf7500R, (unsigned short)ucR_Gain7500K);
	FactoryShowValue(0, mf7500G, (unsigned short)ucG_Gain7500K);
	FactoryShowValue(0, mf7500B, (unsigned short)ucB_Gain7500K);
	FactoryShowValue(0, mf8200R, (unsigned short)ucR_Gain8200K);
	FactoryShowValue(0, mf8200G, (unsigned short)ucG_Gain8200K);
	FactoryShowValue(0, mf8200B, (unsigned short)ucB_Gain8200K);
	FactoryShowValue(0, mf9300R, (unsigned short)ucR_Gain9300K);
	FactoryShowValue(0, mf9300G, (unsigned short)ucG_Gain9300K);
	FactoryShowValue(0, mf9300B, (unsigned short)ucB_Gain9300K);
	FactoryShowValue(0, mf11500R, (unsigned short)ucR_Gain11500K);
	FactoryShowValue(0, mf11500G, (unsigned short)ucG_Gain11500K);
	FactoryShowValue(0, mf11500B, (unsigned short)ucB_Gain11500K);

	reg_addr = 0;
	FactoryShowValue(0, mfADDRESS, (unsigned short)reg_addr);
	reg_value = 0;
	FactoryShowValue(0, mfWR, (unsigned short)reg_value);
	
	ShowNum(0, 14, 19, (unsigned char)(ulPOTTimerH>>8));
	ShowNum(0, 16, 19, (unsigned char)ulPOTTimerH);

	OSD_ON();
	
	ucFactoryStatus = fsMENU;
	ucFactoryIndex = mfAUTO;
	FactorySelect();

	usOSDTimer_10ms = 1000;

}



// **************************************
//
// 	Enter ITEM->VALUE or Leave VALUE->ITEM
//
// **************************************
void FactoryEnter()
{
bit auto_color;
	if(ucFactoryIndex == mfAUTO){
//		if((bIsBurnInEnabled == TRUE)&&(ucResolution == R1280x1024)&&(abs(usVSync-750) < 12)){
//		if((bIsBurnInEnabled == TRUE)&&(((ucResolution == R1280x1024)&&(abs(usVSync-750) < 12))||(ucResolution == R1680x1050))){
		if(1){
			ucBrightness = MCU_DataMap[EPADDR_BRIGHT];	//0x08 = brightness
			ucSavePointer = svBRIGHTNESS;
			SaveData();
			ucContrast = MCU_DataMap[EPADDR_CONTRAST];		//0x09 = contrast
			ucSavePointer = svCONTRAST;
			SaveData();
			ucLFMode = LF_MODE_OFF;
			Write24C16(EPADDR_DVI_LF_MODE, ucLFMode);
			Write24C16(EPADDR_DSUB_LF_MODE, ucLFMode);
			ucDynBKMode = 0;
			ucSavePointer = svDYBK;
			SaveData();
			LFEnableSettings();				
			ucColorTemperature = COLOR_ORIGIN;
			SetColorTemp(ucColorTemperature);
/*
			ucDynBKMode = 0;
			SetBrightness();
			iCurDynBk = ucBrightness;
			ucNewDynBk = ucBrightness;
*/
			auto_color = AutoColor();
			FactoryShowMenu();
			FactoryShowAutoColor( auto_color );
			return;
		}
		else{
			auto_color = 0;
			FactoryShowAutoColor( auto_color );
		}
	}
	else if(ucFactoryIndex == mfRESET){
		OSD_OFF();
		
		ucOSDType = FACTORY;

		FactoryReset();
		Recall();
		
		// CLEAR IN FACTORY MENU RESET
		//RecallPOT();
	
		FactoryShowMenu();
		return;
	}
	else if(ucFactoryIndex == mfRETURN){
		OSD_OFF();
		ucOSDType = MAIN_MENU;
		ucOSDLvl1_Cursor = 0;
//		bOSDReady=FALSE;
		WriteSequenceScaler(0xe0,MainIconTowBitFont);
		WriteSequenceScaler(0xe0,MainIconFourBitFont);
		MainOSD();
		OSD_ON();
		return;
	}
	else if(ucFactoryIndex == mfTDRESET){
		FactoryUnSelect();
		ucTD_ACMode = 0;
		Write24C16(EPADDR_TD_ACMODE, ucTD_ACMode);
		ucTD_State = TD_NORMAL;
		Write24C16(EPADDR_TD_STATE, ucTD_State);
		bShowTheftOSD = FALSE;
		ucCurKey = IGNORE_KEY;
		ucPrevKey = IGNORE_KEY;
		
		ucBrightness = Read24C16(EPADDR_BRIGHT);
		ucBrightnessUser = ucBrightness;
		ucContrast = Read24C16(EPADDR_CONTRAST);
		ucContrastUser = ucContrast;
		SetContrastRGB();
		SetBrightness();
		Sleep(200);
		FactorySelect();
		return;
	}

	

		if(ucFactoryStatus == fsMENU){
			FactoryUnSelect();
			FactorySelectValue();
   			ucFactoryStatus = fsVALUE;
			switch ( ucFactoryIndex ){
			case mfSRGBR:
			case mfSRGBG:
			case mfSRGBB:
				ucColorTemperature = COLOR_SRGB;
				SetColorTemp(ucColorTemperature);
//				ucR_Gain = ucR_GainsRGB;
//				ucG_Gain = ucG_GainsRGB;
//				ucB_Gain = ucB_GainsRGB;
//				SetContrastRGB();
				break;
			case mf5000R:
			case mf5000G:
			case mf5000B:
				ucColorTemperature = COLOR_5000;
				SetColorTemp(ucColorTemperature);
//				ucR_Gain = ucR_Gain5000K;
//				ucG_Gain = ucG_Gain5000K;
//				ucB_Gain = ucB_Gain5000K;
//				SetContrastRGB();
				break;
			case mf6500R:
			case mf6500G:
			case mf6500B:
				ucColorTemperature = COLOR_6500;
				SetColorTemp(ucColorTemperature);
//				ucR_Gain = ucR_Gain6500K;
//				ucG_Gain = ucG_Gain6500K;
//				ucB_Gain = ucB_Gain6500K;
//				SetContrastRGB();
				break;
			case mf7500R:
			case mf7500G:
			case mf7500B:
				ucColorTemperature = COLOR_7500;
				SetColorTemp(ucColorTemperature);
//				ucR_Gain = ucR_Gain7500K;
//				ucG_Gain = ucG_Gain7500K;
//				ucB_Gain = ucB_Gain7500K;
//				SetContrastRGB();
				break;
			case mf8200R:
			case mf8200G:
			case mf8200B:
				ucColorTemperature = COLOR_8200;
				SetColorTemp(ucColorTemperature);
//				ucR_Gain = ucR_Gain8200K;
//				ucG_Gain = ucG_Gain8200K;
//				ucB_Gain = ucB_Gain8200K;
//				SetContrastRGB();
				break;
			case mf9300R:
			case mf9300G:
			case mf9300B:
				ucColorTemperature = COLOR_9300;
				SetColorTemp(ucColorTemperature);
//				ucR_Gain = ucR_Gain9300K;
//				ucG_Gain = ucG_Gain9300K;
//				ucB_Gain = ucB_Gain9300K;
//				SetContrastRGB();
				break;
			case mf11500R:
			case mf11500G:
			case mf11500B:
				ucColorTemperature = COLOR_11500;
				SetColorTemp(ucColorTemperature);
//				ucR_Gain = ucR_Gain11500K;
//				ucG_Gain = ucG_Gain11500K;
//				ucB_Gain = ucB_Gain11500K;
//				SetContrastRGB();
				break;
			}
		}
		else {
			ucFactoryStatus = fsMENU;
			FactoryUnSelectValue();
			FactorySelect();

			// -------------------------------------------------
			//
			//  When leaving VALUE options, write it back to EEPROM
			//
			switch( ucFactoryIndex )
			{
			case mfBURNING:
				Write24C16(EPADDR_BURNIN, bIsBurnInEnabled );				
//				if(bIsBurnInEnabled == 0)
//					Write24C16(EPADDR_FACTORY, 0 );
				break;
			case mfBLACKLEVEL:
				Write24C16(EPADDR_SCALER_OFFSET, ucBlackLevel);	// 0x17
			case mfBRIGHTNESS:
				ucSavePointer = svBRIGHTNESS_F;
				SaveData();
			case mfIDX:
				ucSavePointer = svPANELIDX;
				SaveData();
			case mfCONTRAST:
				ucSavePointer = svCONTRAST_F;
				SaveData();
				break;
			case mfGAINR:
				Write24C16(EPADDR_ADCR_GAIN,ucR_ADC_Gain);//0x4d = ADC r gain
				break;
			case mfGAING:
				Write24C16(EPADDR_ADCG_GAIN,ucG_ADC_Gain);//0x4e = ADC g gain
				break;
			case mfGAINB:
				Write24C16(EPADDR_ADCB_GAIN,ucB_ADC_Gain);//0x4f = ADC b gain
				break;
			case mfOFFSETR:
				Write24C16(EPADDR_ADCR_OFFSET,ucR_ADC_Offset);//0x4a = ADC r offset
				break;
			case mfOFFSETG:
//				Write24C16(EPADDR_ADCG_OFFSET,ucG_ADC_Offset);//0x4b = ADC g offset
				if(ucSignalType == sigSOG)
					Write24C16(EPADDR_ADCG_OFFSET, ucG_ADC_Offset+5);//0x4b = ADC g offset
				else
					Write24C16(EPADDR_ADCG_OFFSET, ucG_ADC_Offset);//0x4b = ADC g offset
				break;
			case mfOFFSETB:
				Write24C16(EPADDR_ADCB_OFFSET,ucB_ADC_Offset);//0x4c = ADC b offset
				break;
			case mfSRGBR:
				ucR_GainsRGB = ucR_Gain;
				Write24C16(EPADDR_RGAIN_SRGB, ucR_Gain);
				break;
			case mfSRGBG:
				ucG_GainsRGB = ucG_Gain;
				Write24C16(EPADDR_GGAIN_SRGB, ucG_Gain);
				break;
			case mfSRGBB:
				ucB_GainsRGB = ucB_Gain;
				Write24C16(EPADDR_BGAIN_SRGB, ucB_Gain);
				break;
			case mf5000R:
				ucR_Gain5000K = ucR_Gain;
				Write24C16(EPADDR_RGAIN_5000, ucR_Gain);
				break;
			case mf5000G:
				ucG_Gain5000K = ucG_Gain;
				Write24C16(EPADDR_GGAIN_5000, ucG_Gain);
				break;
			case mf5000B:
				ucB_Gain5000K = ucB_Gain;
				Write24C16(EPADDR_BGAIN_5000, ucB_Gain);
				break;
			case mf6500R:
				ucR_Gain6500K = ucR_Gain;
				Write24C16(EPADDR_RGAIN_6500, ucR_Gain);
				break;
			case mf6500G:
				ucG_Gain6500K = ucG_Gain;
				Write24C16(EPADDR_GGAIN_6500, ucG_Gain);
				break;
			case mf6500B:
				ucB_Gain6500K = ucB_Gain;
				Write24C16(EPADDR_BGAIN_6500, ucB_Gain);
				break;
			case mf7500R:
				ucR_Gain7500K = ucR_Gain;
				Write24C16(EPADDR_RGAIN_7500, ucR_Gain);
				break;
			case mf7500G:
				ucG_Gain7500K = ucG_Gain;
				Write24C16(EPADDR_GGAIN_7500, ucG_Gain);
				break;
			case mf7500B:
				ucB_Gain7500K = ucB_Gain;
				Write24C16(EPADDR_BGAIN_7500, ucB_Gain);
				break;
			case mf8200R:
				ucR_Gain8200K = ucR_Gain;
				Write24C16(EPADDR_RGAIN_8200, ucR_Gain);
				break;
			case mf8200G:
				ucG_Gain8200K = ucG_Gain;
				Write24C16(EPADDR_GGAIN_8200, ucG_Gain);
				break;
			case mf8200B:
				ucB_Gain8200K = ucB_Gain;
				Write24C16(EPADDR_BGAIN_8200, ucB_Gain);
				break;
			case mf9300R:
				ucR_Gain9300K = ucR_Gain;
				Write24C16(EPADDR_RGAIN_9300, ucR_Gain);
				break;
			case mf9300G:
				ucG_Gain9300K = ucG_Gain;
				Write24C16(EPADDR_GGAIN_9300, ucG_Gain);
				break;
			case mf9300B:
				ucB_Gain9300K = ucB_Gain;
				Write24C16(EPADDR_BGAIN_9300, ucB_Gain);
				break;
			case mf11500R:
				ucR_Gain11500K = ucR_Gain;
				Write24C16(EPADDR_RGAIN_11500, ucR_Gain);
				break;
			case mf11500G:
				ucG_Gain11500K = ucG_Gain;
				Write24C16(EPADDR_GGAIN_11500, ucG_Gain);
				break;
			case mf11500B:
				ucB_Gain11500K = ucB_Gain;
				Write24C16(EPADDR_BGAIN_11500, ucB_Gain);
				break;
			case mfADDRESS:
//#ifdef _FULL_CODE_SIZE_			
				RegRead();
				FactoryShowValue(0, mfWR, reg_value);
//#endif
				break;
			case mfWR:
//#ifdef _FULL_CODE_SIZE_
				RegWrite();
//#endif
				break;			
			}
		}

}


void FactoryItemUp()
{
	if ( ucFactoryStatus == fsMENU )
		FactoryMoveUp();
	else
		FactoryValueUp();
}
void FactoryItemDown()
{
	if ( ucFactoryStatus == fsMENU )
		FactoryMoveDown();
	else
		FactoryValueDown();
}

void FactoryValueUp()
{

	//if ( ucFactoryStatus != fsVALUE ) return;
	
	switch( ucFactoryIndex )
	{
	case mfBURNING:
		bIsBurnInEnabled = !bIsBurnInEnabled;
		FactoryShowBurnin();
		break;
	case mfBLACKLEVEL:
		if(++ucBlackLevel == 0x00){
			ucBlackLevel = MAX_BLACKLEVEL;
		}
		else{
//			SetScalerOffset();
			SetContrastRGB();
			FactoryShowValue(0, mfBLACKLEVEL, ucBlackLevel);
		}
		break;
	case mfBRIGHTNESS:
		if(++ucBrightness > 100)
			ucBrightness = 100;
		else{
			SetBrightness();
//#if _SmartBright_ == ON
//			SetBrightOffset();
//#endif
			FactoryShowValue(0, mfBRIGHTNESS, ucBrightness);
//			ucSavePointer = svBRIGHTNESS;
		}	
		break;
	case mfIDX:
#if 0
		if(++ucPanelIDX == 0x00 )
			ucPanelIDX = 0xff;
#else
		if(++ucPanelIDX > 3 )
			ucPanelIDX = 3;
#endif
		else{
			SetPanelIDX();
			FactoryShowValue(0, mfIDX, ucPanelIDX);
		}
		break;
	case mfCONTRAST:
		if(++ucRGB_OFFSET == 0)
			ucRGB_OFFSET = 255;
		else{
			SetContrastRGB();
			FactoryShowValue(0, mfCONTRAST, ucRGB_OFFSET);
//			ucSavePointer = svCONTRAST;
		}
		break;
	case mfGAINR:
		ADC_R_Up();
		//ADC_GainOffsetUp(RGAIN_HI,&ucR_ADC_Gain);
		FactoryShowValue(0, mfGAINR, (unsigned short)ucR_ADC_Gain);
		break;
	case mfGAING:
		ADC_G_Up();
		//ADC_GainOffsetUp(GGAIN_HI,&ucG_ADC_Gain);
		FactoryShowValue(0, mfGAING, (unsigned short)ucG_ADC_Gain);		
		break;
	case mfGAINB:
		ADC_B_Up();
		//ADC_GainOffsetUp(BGAIN_HI,&ucB_ADC_Gain);
		FactoryShowValue(0, mfGAINB, (unsigned short)ucB_ADC_Gain);
		break;
	case mfOFFSETR:
		ADC_R_OffsetUp();
		//ADC_GainOffsetUp(ROFFSET,&ucR_ADC_Offset);
		FactoryShowValue(0, mfOFFSETR, (unsigned short)ucR_ADC_Offset);
		break;
	case mfOFFSETG:
		ADC_G_OffsetUp();
		//ADC_GainOffsetUp(GOFFSET,&ucG_ADC_Offset);
		FactoryShowValue(0, mfOFFSETG, (unsigned short)ucG_ADC_Offset);	
		break;
	case mfOFFSETB:
		ADC_B_OffsetUp();
		//ADC_GainOffsetUp(BOFFSET,&ucB_ADC_Offset);
		FactoryShowValue(0, mfOFFSETB, (unsigned short)ucB_ADC_Offset);			
		break;
	case mfSRGBR:
		FactoryColorUp(&ucR_Gain);
		FactoryShowValue(0, mfSRGBR, (unsigned short)ucR_Gain);
		break;
	case mfSRGBG:
		FactoryColorUp(&ucG_Gain);
		FactoryShowValue(0, mfSRGBG, (unsigned short)ucG_Gain);
		break;
	case mfSRGBB:
		FactoryColorUp(&ucB_Gain);
		FactoryShowValue(0, mfSRGBB, (unsigned short)ucB_Gain);
		break;
	case mf5000R:
		FactoryColorUp(&ucR_Gain);
		FactoryShowValue(0, mf5000R, (unsigned short)ucR_Gain);
		break;
	case mf5000G:
		FactoryColorUp(&ucG_Gain);
		FactoryShowValue(0, mf5000G, (unsigned short)ucG_Gain);
		break;
	case mf5000B:
		FactoryColorUp(&ucB_Gain);
		FactoryShowValue(0, mf5000B, (unsigned short)ucB_Gain);
		break;
	case mf6500R:
		FactoryColorUp(&ucR_Gain);
		FactoryShowValue(0, mf6500R, (unsigned short)ucR_Gain);
		break;
	case mf6500G:
		FactoryColorUp(&ucG_Gain);
		FactoryShowValue(0, mf6500G, (unsigned short)ucG_Gain);
		break;
	case mf6500B:
		FactoryColorUp(&ucB_Gain);
		FactoryShowValue(0, mf6500B, (unsigned short)ucB_Gain);
		break;
	case mf7500R:
		FactoryColorUp(&ucR_Gain);
		FactoryShowValue(0, mf7500R, (unsigned short)ucR_Gain);
		break;
	case mf7500G:
		FactoryColorUp(&ucG_Gain);
		FactoryShowValue(0, mf7500G, (unsigned short)ucG_Gain);
		break;
	case mf7500B:
		FactoryColorUp(&ucB_Gain);
		FactoryShowValue(0, mf7500B, (unsigned short)ucB_Gain);
		break;
	case mf8200R:
		FactoryColorUp(&ucR_Gain);
		FactoryShowValue(0, mf8200R, (unsigned short)ucR_Gain);
		break;
	case mf8200G:
		FactoryColorUp(&ucG_Gain);
		FactoryShowValue(0, mf8200G, (unsigned short)ucG_Gain);
		break;
	case mf8200B:
		FactoryColorUp(&ucB_Gain);
		FactoryShowValue(0, mf8200B, (unsigned short)ucB_Gain);
		break;
	case mf9300R:
		FactoryColorUp(&ucR_Gain);
		FactoryShowValue(0, mf9300R, (unsigned short)ucR_Gain);
		break;
	case mf9300G:
		FactoryColorUp(&ucG_Gain);
		FactoryShowValue(0, mf9300G, (unsigned short)ucG_Gain);
		break;
	case mf9300B:
		FactoryColorUp(&ucB_Gain);
		FactoryShowValue(0, mf9300B, (unsigned short)ucB_Gain);
		break;
	case mf11500R:
		FactoryColorUp(&ucR_Gain);
		FactoryShowValue(0, mf11500R, (unsigned short)ucR_Gain);
		break;
	case mf11500G:
		FactoryColorUp(&ucG_Gain);
		FactoryShowValue(0, mf11500G, (unsigned short)ucG_Gain);
		break;
	case mf11500B:
		FactoryColorUp(&ucB_Gain);
		FactoryShowValue(0, mf11500B, (unsigned short)ucB_Gain);
		break;
	case mfADDRESS:
//#ifdef _FULL_CODE_SIZE_
		RegAddrInc(&reg_addr);
		FactoryShowValue(0, mfADDRESS, (unsigned short)reg_addr);
		break;
//#endif
	case mfWR:
//#ifdef _FULL_CODE_SIZE_
		RegInc(&reg_value);
		FactoryShowValue(0, mfWR, (unsigned short)reg_value);
//#endif
		break;
/*		
	case mfTDRESET:
		
		Panel_PrevID();
		FactoryShowPanel();

		ucPanelIDX = Panel_t[ucPanelID].idx;

		SetPanelIDX();
		FactoryShowValue(0, mfIDX, ucPanelIDX);
//		ucSavePointer = svPANELIDX;
		break;
*/		
	}
}

void FactoryValueDown()
{

	//if ( ucFactoryStatus != fsVALUE ) return;
	
	switch( ucFactoryIndex )
	{
	case mfBURNING:
		bIsBurnInEnabled = !bIsBurnInEnabled;
		FactoryShowBurnin();
		break;
	case mfBLACKLEVEL:
		if(--ucBlackLevel == 0xFF){
			ucBlackLevel = MIN_BLACKLEVEL;
		}
		else{
//			SetScalerOffset();
			SetContrastRGB();
			FactoryShowValue(0, mfBLACKLEVEL, ucBlackLevel);
		}
		break;
	case mfBRIGHTNESS:
		if(--ucBrightness == 0xff)
			ucBrightness = 0x00;
		else{
			SetBrightness();
//#if _SmartBright_ == ON
//			SetBrightOffset();
//#endif
			FactoryShowValue(0, mfBRIGHTNESS, ucBrightness);
//			ucSavePointer = svBRIGHTNESS;
		}	
		break;
	case mfIDX:
		if(--ucPanelIDX== 0xff)
			ucPanelIDX = 0x00;
		else{
			SetPanelIDX();
			FactoryShowValue(0, mfIDX, ucPanelIDX);
		}	
		break;
	case mfCONTRAST:
		if(--ucRGB_OFFSET == 0xff)
			ucRGB_OFFSET = 0x00;
		else{
			SetContrastRGB();
			FactoryShowValue(0, mfCONTRAST, ucRGB_OFFSET);
//			ucSavePointer = svCONTRAST;
		}
		break;
	case mfGAINR:
		ADC_R_Down();
		//ADC_GainOffsetDown(RGAIN_HI,&ucR_ADC_Gain);
		FactoryShowValue(0, mfGAINR, (unsigned short)ucR_ADC_Gain);
		break;
	case mfGAING:
		ADC_G_Down();
		//ADC_GainOffsetDown(GGAIN_HI,&ucG_ADC_Gain);
		FactoryShowValue(0, mfGAING, (unsigned short)ucG_ADC_Gain);	
		break;
	case mfGAINB:
		ADC_B_Down();
		//ADC_GainOffsetDown(BGAIN_HI,&ucB_ADC_Gain);
		FactoryShowValue(0, mfGAINB, (unsigned short)ucB_ADC_Gain);
		break;
	case mfOFFSETR:
		ADC_R_OffsetDown();
		//ADC_GainOffsetDown(ROFFSET,&ucR_ADC_Offset);
		FactoryShowValue(0, mfOFFSETR, (unsigned short)ucR_ADC_Offset);
		break;
	case mfOFFSETG:
		ADC_G_OffsetDown();
		//ADC_GainOffsetDown(GOFFSET,&ucG_ADC_Offset);
		FactoryShowValue(0, mfOFFSETG, (unsigned short)ucG_ADC_Offset);
		break;
	case mfOFFSETB:
		ADC_B_OffsetDown();
		//ADC_GainOffsetDown(BOFFSET,&ucB_ADC_Offset);
		FactoryShowValue(0, mfOFFSETB, (unsigned short)ucB_ADC_Offset);
		break;
	case mfSRGBR:
		FactoryColorDown(&ucR_Gain);
		FactoryShowValue(0, mfSRGBR, (unsigned short)ucR_Gain);
		break;
	case mfSRGBG:
		FactoryColorDown(&ucG_Gain);
		FactoryShowValue(0, mfSRGBG, (unsigned short)ucG_Gain);
		break;
	case mfSRGBB:
		FactoryColorDown(&ucB_Gain);
		FactoryShowValue(0, mfSRGBB, (unsigned short)ucB_Gain);
		break;
	case mf5000R:
		FactoryColorDown(&ucR_Gain);
		FactoryShowValue(0, mf5000R, (unsigned short)ucR_Gain);
		break;
	case mf5000G:
		FactoryColorDown(&ucG_Gain);
		FactoryShowValue(0, mf5000G, (unsigned short)ucG_Gain);
		break;
	case mf5000B:
		FactoryColorDown(&ucB_Gain);
		FactoryShowValue(0, mf5000B, (unsigned short)ucB_Gain);
		break;
	case mf6500R:
		FactoryColorDown(&ucR_Gain);
		FactoryShowValue(0, mf6500R, (unsigned short)ucR_Gain);
		break;
	case mf6500G:
		FactoryColorDown(&ucG_Gain);
		FactoryShowValue(0, mf6500G, (unsigned short)ucG_Gain);
		break;
	case mf6500B:
		FactoryColorDown(&ucB_Gain);
		FactoryShowValue(0, mf6500B, (unsigned short)ucB_Gain);
		break;
	case mf7500R:
		FactoryColorDown(&ucR_Gain);
		FactoryShowValue(0, mf7500R, (unsigned short)ucR_Gain);
		break;
	case mf7500G:
		FactoryColorDown(&ucG_Gain);
		FactoryShowValue(0, mf7500G, (unsigned short)ucG_Gain);
		break;
	case mf7500B:
		FactoryColorDown(&ucB_Gain);
		FactoryShowValue(0, mf7500B, (unsigned short)ucB_Gain);
		break;
	case mf8200R:
		FactoryColorDown(&ucR_Gain);
		FactoryShowValue(0, mf8200R, (unsigned short)ucR_Gain);
		break;
	case mf8200G:
		FactoryColorDown(&ucG_Gain);
		FactoryShowValue(0, mf8200G, (unsigned short)ucG_Gain);
		break;
	case mf8200B:
		FactoryColorDown(&ucB_Gain);
		FactoryShowValue(0, mf8200B, (unsigned short)ucB_Gain);
		break;
	case mf9300R:
		FactoryColorDown(&ucR_Gain);
		FactoryShowValue(0, mf9300R, (unsigned short)ucR_Gain);
		break;
	case mf9300G:
		FactoryColorDown(&ucG_Gain);
		FactoryShowValue(0, mf9300G, (unsigned short)ucG_Gain);
		break;
	case mf9300B:
		FactoryColorDown(&ucB_Gain);
		FactoryShowValue(0, mf9300B, (unsigned short)ucB_Gain);
		break;
	case mf11500R:
		FactoryColorDown(&ucR_Gain);
		FactoryShowValue(0, mf11500R, (unsigned short)ucR_Gain);
		break;
	case mf11500G:
		FactoryColorDown(&ucG_Gain);
		FactoryShowValue(0, mf11500G, (unsigned short)ucG_Gain);
		break;
	case mf11500B:
		FactoryColorDown(&ucB_Gain);
		FactoryShowValue(0, mf11500B, (unsigned short)ucB_Gain);
		break;
	case mfADDRESS:
//#ifdef _FULL_CODE_SIZE_
		RegAddrDec(&reg_addr);
		FactoryShowValue(0, mfADDRESS, (unsigned short)reg_addr);
//#endif
		break;
	case mfWR:
//#ifdef _FULL_CODE_SIZE_
		RegDec(&reg_value);
		FactoryShowValue(0, mfWR, (unsigned short)reg_value);
//#endif
		break;

/*		
	case mfTDRESET:
		Panel_NextID();
		FactoryShowPanel();

		ucPanelIDX = Panel_t[ucPanelID].idx;

		SetPanelIDX();
		FactoryShowValue(0, mfIDX, ucPanelIDX);
//		ucSavePointer = svPANELIDX;
		break;
*/		
	}
}

void FactoryMoveUp()
{
//unsigned char color_temp = ucColorTemperature;

	//if ( ucFactoryStatus != fsMENU ) return;
	
	FactoryUnSelect();
	if(--ucFactoryIndex > mfRETURN)
		ucFactoryIndex = mfRETURN;
	FactorySelect();

	if(ucFactoryIndex == mfSRGBB){
		ucColorTemperature = COLOR_SRGB;
		SetColorTemp(ucColorTemperature);
	}
	else if(ucFactoryIndex == mf5000B){
		ucColorTemperature = COLOR_5000;
		SetColorTemp(ucColorTemperature);
	}
	else if(ucFactoryIndex == mf6500B){
		ucColorTemperature = COLOR_6500;
		SetColorTemp(ucColorTemperature);
	}
	else if(ucFactoryIndex == mf7500B){
		ucColorTemperature = COLOR_7500;
		SetColorTemp(ucColorTemperature);
	}
	else if(ucFactoryIndex == mf8200B){
		ucColorTemperature = COLOR_8200;
		SetColorTemp(ucColorTemperature);
	}
	else if(ucFactoryIndex == mf9300B){
		ucColorTemperature = COLOR_9300;
		SetColorTemp(ucColorTemperature);
	}
	else if(ucFactoryIndex == mf11500B){
		ucColorTemperature = COLOR_11500;
		SetColorTemp(ucColorTemperature);
	}
	else if(ucFactoryIndex == mfOFFSETB){
		ucColorTemperature = Read24C16(EPADDR_COLOR_TEMP);
		SetColorTemp(ucColorTemperature);
	}
	
}

void FactoryMoveDown()
{
	//if ( ucFactoryStatus != fsMENU ) return;
	
	FactoryUnSelect();
	if(++ucFactoryIndex > mfRETURN)
		ucFactoryIndex = mfAUTO;
	FactorySelect();

	if(ucFactoryIndex == mfSRGBR){
		ucColorTemperature = COLOR_SRGB;
		SetColorTemp(ucColorTemperature);
	}
	else if(ucFactoryIndex == mf5000R){
		ucColorTemperature = COLOR_5000;
		SetColorTemp(ucColorTemperature);
	}
	else if(ucFactoryIndex == mf6500R){
		ucColorTemperature = COLOR_6500;
		SetColorTemp(ucColorTemperature);
	}
	else if(ucFactoryIndex == mf7500R){
		ucColorTemperature = COLOR_7500;
		SetColorTemp(ucColorTemperature);
	}
	else if(ucFactoryIndex == mf8200R){
		ucColorTemperature = COLOR_8200;
		SetColorTemp(ucColorTemperature);
	}
	else if(ucFactoryIndex == mf9300R){
		ucColorTemperature = COLOR_9300;
		SetColorTemp(ucColorTemperature);
	}
	else if(ucFactoryIndex == mf11500R){
		ucColorTemperature = COLOR_11500;
		SetColorTemp(ucColorTemperature);
	}
	else if(ucFactoryIndex == mfADDRESS){
		ucColorTemperature = Read24C16(EPADDR_COLOR_TEMP);
		SetColorTemp(ucColorTemperature);
	}
	
}

//********************************
//
//	Move LightBar between Menu items
//
//********************************
void FactorySelect()
{
	FillLineAttr(  LBar[ucFactoryIndex].x,
				LBar[ucFactoryIndex].y,
				LBar[ucFactoryIndex].len,
				FactoryColorR);
}
	
void FactoryUnSelect()
{
	FillLineAttr(  LBar[ucFactoryIndex].x,
				LBar[ucFactoryIndex].y,
				LBar[ucFactoryIndex].len,
				FactoryColorW);
}

//********************************
//
//	Move LightBar between Item and its value
//
//********************************
void FactorySelectValue()
{
	if ( ucFactoryIndex >= mfGAINR && ucFactoryIndex <= mf9300B ) {
		FillLineAttr(	LBar[ucFactoryIndex].x+LBar[ucFactoryIndex].len,
					LBar[ucFactoryIndex].y,
					3,
					FactoryColorR);
	}
	else if ( ucFactoryIndex == mfBURNING ) {
		FillLineAttr(	LBar[ucFactoryIndex].x+LBar[ucFactoryIndex].len,
					LBar[ucFactoryIndex].y,
					5,
					FactoryColorR);
	}
	else if ( ucFactoryIndex == mfWR ) {
		FillLineAttr(	LBar[ucFactoryIndex].x-5,
					LBar[ucFactoryIndex].y,
					4,
					FactoryColorR);
	}
/*	
	else if ( ucFactoryIndex == mfTDRESET ) {
		FillLineAttr(	LBar[ucFactoryIndex].x+LBar[ucFactoryIndex].len,
					LBar[ucFactoryIndex].y,
					10,
					FactoryColorR);
	}
*/
	else
	{
		FillLineAttr(	LBar[ucFactoryIndex].x+LBar[ucFactoryIndex].len,
					LBar[ucFactoryIndex].y,
					4,
					FactoryColorR );
	}
}

void FactoryUnSelectValue()
{
	if ( ucFactoryIndex >= mfGAINR && ucFactoryIndex <= mf9300B ) {
		FillLineAttr(	LBar[ucFactoryIndex].x+LBar[ucFactoryIndex].len,
					LBar[ucFactoryIndex].y,
					3,
					FactoryColorW );
	}
	else if ( ucFactoryIndex == mfBURNING ) {
		FillLineAttr(	LBar[ucFactoryIndex].x+LBar[ucFactoryIndex].len,
					LBar[ucFactoryIndex].y,
					5,
					FactoryColorW);
	}
	else if ( ucFactoryIndex == mfWR ) {
		FillLineAttr(	LBar[ucFactoryIndex].x-5,
					LBar[ucFactoryIndex].y,
					3,
					FactoryColorW );
	}
/*	
	else if ( ucFactoryIndex == mfTDRESET) {
		FillLineAttr(	LBar[ucFactoryIndex].x+LBar[ucFactoryIndex].len,
					LBar[ucFactoryIndex].y,
					10,
					FactoryColorW);
	}
*/
	else
	{
		FillLineAttr(	LBar[ucFactoryIndex].x+LBar[ucFactoryIndex].len,
					LBar[ucFactoryIndex].y,
					4,
					FactoryColorW );
	}
}


void FactoryShowAutoColor(bit is_ok)
{
	ucStrAlignment = 0;
	ucStrWidth = 3;
 	usFontIndex = 0xf0;

	if ( is_ok )
		WriteArialFont(OK);
	else
		WriteArialFont(NO);

	WriteXY_String(0, LBar[mfAUTO].x+8, LBar[mfAUTO].y);
}

void FactoryShowBurnin()
{
	ucStrAlignment = 0;
	ucStrWidth = 3;
 	usFontIndex = 0xf8;

	if ( TRUE == bIsBurnInEnabled )
		WriteArialFont(YES);
	else
		WriteArialFont(NO);

	WriteXY_String(0, LBar[mfBURNING].x+8, LBar[mfBURNING].y);
}

#if 1

void ADC_R_Up(void)
{
	if(--ucR_ADC_Gain == 0xff){
		ucR_ADC_Gain = 0x00;
	}	
	else{
		WriteIIC560(RGAIN_HI,ucR_ADC_Gain);
	}
}

void ADC_R_Down(void)
{
	if(++ucR_ADC_Gain == 0x00){
		ucR_ADC_Gain = 0xff;
	}
	else{
		WriteIIC560(RGAIN_HI,ucR_ADC_Gain);
	}
}

void ADC_G_Up(void)
{
	if(--ucG_ADC_Gain == 0xff){
		ucG_ADC_Gain = 0x00;
	}
	else{
		WriteIIC560(GGAIN_HI,ucG_ADC_Gain);
	}
}

void ADC_G_Down(void)
{
	if(++ucG_ADC_Gain == 0x00){
		ucG_ADC_Gain = 0xff;
	}
	else{
		WriteIIC560(GGAIN_HI,ucG_ADC_Gain);
	}
}

void ADC_B_Up(void)
{
	if(--ucB_ADC_Gain == 0xff){
		ucB_ADC_Gain = 0x00;
	}
	else{
		WriteIIC560(BGAIN_HI,ucB_ADC_Gain);
	}
}

void ADC_B_Down(void)
{
	if(++ucB_ADC_Gain == 0x00){
		ucB_ADC_Gain = 0xff;
	}
	else{
		WriteIIC560(BGAIN_HI,ucB_ADC_Gain);
	}
}


void ADC_R_OffsetUp(void)
{
	if(--ucR_ADC_Offset == 0xff){
		ucR_ADC_Offset = 0x00;
	}
	else{
		WriteIIC560(ROFFSET,ucR_ADC_Offset);
	}
}

void ADC_R_OffsetDown(void)
{
	if(++ucR_ADC_Offset == 0x00){
		ucR_ADC_Offset = 0xff;
	}
	else{
		WriteIIC560(ROFFSET,ucR_ADC_Offset);
	}
}

void ADC_G_OffsetUp(void)
{
	if(--ucG_ADC_Offset == 0xff){
		ucG_ADC_Offset = 0x00;
	}
	else{
		WriteIIC560(GOFFSET,ucG_ADC_Offset);
	}
}

void ADC_G_OffsetDown(void)
{
	if(++ucG_ADC_Offset == 0x00){
		ucG_ADC_Offset = 0xff;
	}
	else{
		WriteIIC560(GOFFSET,ucG_ADC_Offset);
	}
}

void ADC_B_OffsetUp(void)
{
	if(--ucB_ADC_Offset == 0xff){
		ucB_ADC_Offset = 0x00;
	}
	else{
		WriteIIC560(BOFFSET,ucB_ADC_Offset);
	}
}

void ADC_B_OffsetDown(void)
{
	if(++ucB_ADC_Offset == 0x00){
		ucB_ADC_Offset = 0xff;
	}
	else{
		WriteIIC560(BOFFSET,ucB_ADC_Offset);
	}
}
#else

void ADC_GainOffsetUp(unsigned short addr, unsigned char *value)
{
	if(--(*value) == 0xff){
		(*value) = 0x00;
	}
	else{
		WriteIIC560(addr,(*value));
	}
}

void ADC_GainOffsetDown(unsigned short addr, unsigned char *value)
{
	if(++(*value) == 0x00){
		(*value) = 0xff;
	}
	else{
		WriteIIC560(addr,(*value));
	}
}

#endif

void FactoryColorUp(unsigned char *val)
{
	if(++(*val) == 0){
		(*val) = 255;
	}
	else{
		SetContrastRGB();
	}
}

void FactoryColorDown(unsigned char *val)
{
	if(--(*val) == 0xff){
		(*val) = 0;
	}
	else{
		SetContrastRGB();
	}
}



//#ifdef _FULL_CODE_SIZE_
void RegAddrInc(unsigned short *i)
{
	if ( ++(*i) == 0x200 )
		(*i) = 0;
}

void RegAddrDec(unsigned short *i)
{
	if ( --(*i) == 0xffff )
		(*i) = 0x1ff;
}

void RegInc(unsigned char *i)
{
	++(*i);
	//if ( ++(*i) == 0 )
	//	(*i) = 0xff;
}

void RegDec(unsigned char *i)
{
	--(*i);
	//if ( --(*i) == 0xff )
	//	(*i) = 0x00;
}

void RegWrite()
{
	if ( reg_addr == 0x0f && reg_value == 0x55 )
		ClearEEPROM();
	else
		WriteIIC560(reg_addr, reg_value);
}

void RegRead()
{
	reg_value = ReadIIC560(reg_addr);
}
//#endif

void ClearEEPROM()
{	
/*	
unsigned short i;
	for (i=0x00; i< NVRAM_FINAL_ADDR; i++ )
		Write24C16(i, 0x00);
*/
InitEEPROM(1);
EA = 0;
while(1){};

}



