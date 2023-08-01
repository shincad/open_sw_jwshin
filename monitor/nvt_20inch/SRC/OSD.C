#include "stdio.h"
#include "OSD.H"
#include "Scaler.H"
#include "IIC.H"
#include "MyDef.H"
#include "RAM.H"
#include "F63XREG.H"
#include "F63XDEF.H"
#include "MCU.H"
#include "OSD_TAB.H"
#include "OSD_TAB2.H"
#include "ROM_MAP.H"
#include "PANEL.H"
#include "UserAdj.H"
#include "ModeHandle.H"
#include "Tuner.h"
#include "Z86229.h"


	
void OsdProcess()
{
	if(MenuPtr.Op == 0)
		return;
	if(MenuPtr.Menu == 1)
		{
		if(MenuPtr.Level == 0)
			{
			switch(MenuPtr.Op)
				{
				case oUPDATEALL:
					ShowMain(MenuPtr.Page);
					Osd_On(enWIN4|enWIN2);	//win4 background /win3 select icon 
					TempPtr = FuncBuf[pVIDEOSOURCE];
					break;
				case oUPDATE:
					ShowKeyMenu(MenuPtr.Page,MenuPtr.Level);	//when change page
				case oINCPAGE:
				case oDECPAGE:
					ClearTextArea();
					RefreshIcon();	
					ShowSubMenu(MenuPtr.Page,MenuPtr.Ptr);
					break;
				};
			}
		if(MenuPtr.Level == 1)
			{
			switch(MenuPtr.Op)
				{
				case oENTER:
				case oUPDATEALL:
					ShowKeyMenu(MenuPtr.Page,MenuPtr.Level);	//when chane level 0 -->level 1
				case oDECFUNC:
				case oINCFUNC:
					ShowSubMenu(MenuPtr.Page,MenuPtr.Ptr);
					break;
				case oUPDATE:
				case oINCVAL://do not add 'break' here
				case oDECVAL:
					switch(FuncPtr)
						{
						//case pTEXTMODE:
						//	ShowTextGraphicMode();
						//	break;
						case pRECALL:
							ShowYesNo(0);
							ShowSubMenu(MenuPtr.Page,MenuPtr.Ptr);
							break;
						case pLANGUAGE:
							ShowLanguage();
							break;
						case pVIDEOSOURCE:
							ShowSyncMode();
							break;
						case pCOLORTEMP:
							if(FuncBuf[pCOLORTEMP] == 3 || FuncBuf[pCOLORTEMP] == 0 )//change key when first and user item 
								ShowKeyMenu(2,MenuPtr.Level);
							ShowColorMenu();
							break;
						case pMUTE:
							ShowOnOff(AudioMute);
							ShowStatus(ROW11+2,fGREEN|bBLACK);
							break;
						case pAUTOSETTING:
							ShowOnOff(AutoSetting);
							break;
						case pOSDHPOSITION:
							ShowOSDPosition();
							break;
						case pSHARPNESS:
							if(FuncBuf[pVIDEOSOURCE] < cSVIDEO)
								ShowSharpness();
							else{
								ShowBar(MAINMENU_BAR_ADDR+(OSD_WIDTH*MenuPtr.Ptr),BAR_COLOR,FuncMin,FuncMax,FuncBuf[FuncPtr]);
								ShowValue(MAINMENU_VALUE_ADDR+(OSD_WIDTH*MenuPtr.Ptr),VALUE_COLOR,FuncBuf[FuncPtr]);
							}
							break;
						case pLIGHTEN:
							ShowOnOff(LightEn);
							break;
						case pSCALERMODE:
//							ShowScalerMode(ScalerMode);
							break;
						case pCAPTION:
							ShowOnOff(CaptionFlag);
							break;	
	//					case pVOLUME:
/*						case pTreble:
							ShowBar(MAINMENU_BAR_ADDR+(OSD_WIDTH*MenuPtr.Ptr),BAR_COLOR,FuncMin,FuncMax,FuncBuf[pTreble] );
							ShowValue(MAINMENU_VALUE_ADDR+(OSD_WIDTH*MenuPtr.Ptr),VALUE_COLOR,Treble);
							break;
						case pBass:	
							ShowBar(MAINMENU_BAR_ADDR+(OSD_WIDTH*MenuPtr.Ptr),BAR_COLOR,FuncMin,FuncMax,FuncBuf[pBass] );
							ShowValue(MAINMENU_VALUE_ADDR+(OSD_WIDTH*MenuPtr.Ptr),VALUE_COLOR,Bass);
							break;
//							ShowOnOff(AudioMute);
//							ShowStatus(ROW11+2,fGREEN|bBLACK);
						//	break;
*/
						default:
							ShowBar(MAINMENU_BAR_ADDR+(OSD_WIDTH*MenuPtr.Ptr),BAR_COLOR,FuncMin,FuncMax,FuncBuf[FuncPtr]);
							ShowValue(MAINMENU_VALUE_ADDR+(OSD_WIDTH*MenuPtr.Ptr),VALUE_COLOR,FuncBuf[FuncPtr]);
							break;
						};
					break;
				};
			}
		if(MenuPtr.Level == 2)
			{
			switch(MenuPtr.Op)
				{
				case oUPDATE:
					ShowKeyMenu(2,MenuPtr.Level);
				case oDECFUNC:
				case oINCFUNC:
					if(FuncBuf[pCOLORTEMP] == 3)
						ShowUserRGBMenu();
					break;
				case oINCVAL://do not add 'break' here
				case oDECVAL:
					switch(FuncPtr)
						{
						case pRCOLOR:
						case pGCOLOR:
						case pBCOLOR:
							if(FuncBuf[pCOLORTEMP] == 3)
								ShowRGBMenu();
							break;
						case pVIDEOSOURCE:
							ShowSyncMode();
							break;
						};
					break;
				};
			}
		}
	if(MenuPtr.Menu == 2)	//fact menu
		{
		if(MenuPtr.Level == 0)
			{
			switch(MenuPtr.Op)
				{
				case oUPDATEALL:
					ShowFactMenu();
					Osd_On(enWIN4|enWIN3);		
					break;
				case oUPDATE:
				case oENTER:
				case oINCFUNC:
				case oDECFUNC:
					ShowFact();
					break;
				};
			}
		if(MenuPtr.Level == 1)
			{
			switch(MenuPtr.Op)
				{
				case oENTER:
				case oDECVAL:
				case oINCVAL:
					ShowFact();
					break;
				}
			}
		}
	if(MenuPtr.Menu == 3)
	{
		if(MenuPtr.Level == 0)
			{
			switch(MenuPtr.Op)
				{
				case oUPDATEALL:
					ShowBrightnessMenu();
					Osd_On(enWIN4);	//win4 background /win3 select icon 
					TempPtr = FuncBuf[pVIDEOSOURCE];
					break;
				case oINCVAL://do not add 'break' here
				case oDECVAL:
					ShowBar(MAINMENU_BAR_ADDR,BAR_COLOR,FuncMin,FuncMax,FuncBuf[FuncPtr]);
					ShowValue(MAINMENU_VALUE_ADDR,VALUE_COLOR,FuncBuf[FuncPtr]);
					break;
				};
			}
		if(MenuPtr.Level == 1)
			{
			switch(MenuPtr.Op)
				{
				case oUPDATEALL:
					ShowBrightnessMenu();
					Osd_On(enWIN4);	//win4 background /win3 select icon 
					break;
				case oDECFUNC:
				case oINCFUNC:
					ClearLine(1);
					ShowDesc(FuncPtr,HOTKEYMENU_DESC_ADDR,SEL_FUN_COLOR);
					ShowKeyMenu(0,MenuPtr.Level);
				case oINCVAL://do not add 'break' here
				case oDECVAL:
					ShowBar(HOTKEYMENU_BAR_ADDR,BAR_COLOR,FuncMin,FuncMax,FuncBuf[FuncPtr]);
					ShowValue(HOTKEYMENU_VALUE_ADDR,VALUE_COLOR,FuncBuf[FuncPtr]);
					break;
				};
			}
		}
	
	if(MenuPtr.Menu == 4)
	{
		switch(MenuPtr.Op)
			{
			case oUPDATEALL:
				ShowTurboModeMenu();
				Osd_On(enWIN4);	//win4 background /win3 select icon 
				break;
			case oINCVAL://do not add 'break' here
			case oDECVAL:
				ShowTurboMode();
				break;
			};
	}

	if(MenuPtr.Menu == 5)
	{
		switch(MenuPtr.Op)
			{
			case oUPDATEALL:
				ShowMain(MenuPtr.Page);
				Osd_On(enWIN4|enWIN2);	//win4 background /win3 select icon 
				//TempPtr = FuncBuf[pVIDEOSOURCE];
			case oENTER:
			case oDECFUNC:
			case oINCFUNC:
				ShowKeyMenu(MenuPtr.Page,MenuPtr.Level);
				ShowSubMenu(MenuPtr.Page,MenuPtr.Ptr);
				break;
			};
	}
	
//---------------------------- +jwshin 050801
	if(MenuPtr.Menu == 6)
	{
		if(MenuPtr.Level == 0)
			{
			switch(MenuPtr.Op)
				{
				case oUPDATEALL:
						WriteIIC563(0x080,0); // OSD disable
						ClearOSD();
						WriteIIC563(0x090,0x00);  // zooming off
						ShowOSDFrame(1);
						OsdPosition();
						OpenWindow(WINDOW4,WIN4_X1,WIN4_X2,WIN4_Y1,WIN4_Y2-9,WIN4_ATTR,WIN4_COLOR);
						OpenWindow(WINDOW3,WIN3_X1,WIN3_X2,WIN3_Y1,WIN3_Y2,WIN3_ATTR,WIN3_COLOR);
						if(FuncBuf[pVIDEOSOURCE] < cSVIDEO){
							//ShowResolution(HOTKEYMENU_RES_ADDR,RES_COLOR);
							ShowStatus(ROW2+2,fGREEN|bBLACK);
						}
						//else
						//	ShowTvSystem();
						ShowKeyMenu(1,MenuPtr.Level);
						
						FuncPtr = Page1Item[MenuPtr.Ptr];
						ShowDesc(FuncPtr,HOTKEYMENU_DESC_ADDR,SEL_FUN_COLOR);
						GetFuncRange(FuncPtr);
						ShowBar(HOTKEYMENU_BAR_ADDR,SEL_FUN_COLOR,FuncMin,FuncMax,FuncBuf[FuncPtr]);
						ShowValue(HOTKEYMENU_VALUE_ADDR,SEL_FUN_COLOR,FuncBuf[FuncPtr]);
					Osd_On(enWIN4);	//win4 background /win3 select icon 
					TempPtr = FuncBuf[pVIDEOSOURCE];
					break;
				case oINCVAL://do not add 'break' here
				case oDECVAL:
					ShowBar(MAINMENU_BAR_ADDR,BAR_COLOR,FuncMin,FuncMax,FuncBuf[FuncPtr]);
					ShowValue(MAINMENU_VALUE_ADDR,VALUE_COLOR,FuncBuf[FuncPtr]);
					break;
				};
			}
		if(MenuPtr.Level == 1)
			{
			switch(MenuPtr.Op)
				{
				case oUPDATEALL:
						WriteIIC563(0x080,0); // OSD disable
						ClearOSD();
						WriteIIC563(0x090,0x00);  // zooming off
						ShowOSDFrame(1);
						OsdPosition();
						OpenWindow(WINDOW4,WIN4_X1,WIN4_X2,WIN4_Y1,WIN4_Y2-9,WIN4_ATTR,WIN4_COLOR);
						OpenWindow(WINDOW3,WIN3_X1,WIN3_X2,WIN3_Y1,WIN3_Y2,WIN3_ATTR,WIN3_COLOR);
						if(FuncBuf[pVIDEOSOURCE] < cSVIDEO){
							//ShowResolution(HOTKEYMENU_RES_ADDR,RES_COLOR);
							ShowStatus(ROW2+2,fGREEN|bBLACK);
						}
						//else
						//	ShowTvSystem();
						ShowKeyMenu(1,MenuPtr.Level);
						
						FuncPtr = Page1Item[MenuPtr.Ptr];
						ShowDesc(FuncPtr,HOTKEYMENU_DESC_ADDR,SEL_FUN_COLOR);
						GetFuncRange(FuncPtr);
						ShowBar(HOTKEYMENU_BAR_ADDR,SEL_FUN_COLOR,FuncMin,FuncMax,FuncBuf[FuncPtr]);
						ShowValue(HOTKEYMENU_VALUE_ADDR,SEL_FUN_COLOR,FuncBuf[FuncPtr]);
						Osd_On(enWIN4);	//win4 background /win3 select icon 
						break;
				case oDECFUNC:
				case oINCFUNC:
					ClearLine(1);
					ShowDesc(FuncPtr,HOTKEYMENU_DESC_ADDR,SEL_FUN_COLOR);
					ShowKeyMenu(1,MenuPtr.Level);
				case oINCVAL://do not add 'break' here
				case oDECVAL:
					ShowBar(HOTKEYMENU_BAR_ADDR,BAR_COLOR,FuncMin,FuncMax,FuncBuf[FuncPtr]);
					ShowValue(HOTKEYMENU_VALUE_ADDR,VALUE_COLOR,FuncBuf[FuncPtr]);
					break;
				};
			}
	}	
//------------------------------------	
	
	
	MenuPtr.Op = 0;
}

void ShowSyncMode()
{
	Byte code ENG_ANALOG[]={
		6,"Analog"
	};
	Byte code FRA_ANALOG[]={
		10,"Analogique"
	};
	Byte code DEU_ANALOG[]={
		5,"Analog"
	};
	Byte code ESP_ANALOG[]={
		9,"Analgica"
	};
	Byte code ITA_ANALOG[]={
		9,"Analogico"
	};
	Byte code JAP_ANALOG[]={
		4,_J19,_J1a,_J10,_J13
	};
	Byte code RUS_ANALOG[]={
		10,_A,_P04,_a,_P19,_o,_P0a,_o,_P07,_P1a,_P02
	};
	Byte code CHT_ANALOG[]={
		2,_C61,_C21
	};
	Byte code CHI_ANALOG[]={
		2,_C32,_C33
	};
	Byte code ENG_DVI[]={
	7,"DigitalL"
	};
	Byte code FRA_DVI[]={
	9,"Numrique"
	};
	Byte code DEU_DVI[]={
	7,"Digital"
	};
	Byte code ESP_DVI[]={
	7,"Digital"
	};
	Byte code ITA_DVI[]={
	8,"Digitale"
	};
	Byte code JAP_DVI[]={
	4,_J14,_J1b,_J1c,_J18
	};
	Byte code RUS_DVI[]={
	6,_P06,_P03,_P15,_p,_o,_P07,_o,_P02
	};
	Byte code CHT_DVI[]={
	2,_C62,_C14
	};
	Byte code CHI_DVI[]={
	2,_C34,_C27
	};
	Byte code ENG_YPbPr[]={
	5,"YPbPr"
	};
	Byte code ENG_CVBS[]={
		5,"Video"
	};
	Byte code ENG_SVIDEO[]={
		7,"S-Video"
	};
	Byte code TXT_TV[]={
		2,"TV"
	};
code unsigned char *SourceTab[][9]={
	{ENG_ANALOG,FRA_ANALOG,DEU_ANALOG,ESP_ANALOG,ITA_ANALOG,JAP_ANALOG,RUS_ANALOG,CHT_ANALOG,CHI_ANALOG},
	{ENG_DVI,FRA_DVI,DEU_DVI,ESP_DVI,ITA_DVI,JAP_DVI,RUS_DVI,CHT_DVI,CHI_DVI},
	{ENG_YPbPr,ENG_YPbPr,ENG_YPbPr,ENG_YPbPr,ENG_YPbPr,ENG_YPbPr,ENG_YPbPr,ENG_YPbPr,ENG_YPbPr},
	{ENG_SVIDEO,ENG_SVIDEO,ENG_SVIDEO,ENG_SVIDEO,ENG_SVIDEO,ENG_SVIDEO,ENG_SVIDEO,ENG_SVIDEO,ENG_SVIDEO},
	{ENG_CVBS,ENG_CVBS,ENG_CVBS,ENG_CVBS,ENG_CVBS,ENG_CVBS,ENG_CVBS,ENG_CVBS,ENG_CVBS},
	{TXT_TV,TXT_TV,TXT_TV,TXT_TV,TXT_TV,TXT_TV,TXT_TV,TXT_TV,TXT_TV}
};

	Byte i,End,x,y,*Offset,Length;
	Word code SyncModeAddr[6]={ROW4+2,ROW5+2,ROW6+2,ROW7+2,ROW8+2,ROW9+2};


	Osd_On(enWIN4|enWIN2);
	if(DecoderICEn)
		End = 6;
	else
		End = 3;
	//i = TempPtr;
	i = MenuPtr.Ptr;
	x = SyncModeAddr[i] % OSD_WIDTH;
	y = SyncModeAddr[i] / OSD_WIDTH;
	//if(MenuPtr.Level == 1) 
		//OpenWindow(WINDOW3,x,x+10,y,y,atWIN_SHADOW_4L,WIN3_COLOR);
//	x = Read24C16(ep_Sync_Source);
	for(i=0;i<End;i++)
		{
		Offset = SourceTab[i][FuncBuf[pLANGUAGE]];
		Length = *Offset;
		Offset++;
//		if(MenuPtr.Level == 1)
//			if(i == MenuPtr.Ptr)
//				WriteWordIIC563(0x0cc,fMAGENTA|fBLACK);
//			else
//				WriteWordIIC563(0x0cc,fWHITE|fBLACK);
//		else
//			if(FuncBuf[pVIDEOSOURCE] == i)
//				WriteWordIIC563(0x0cc,fGREEN|fBLACK);
//			else			
//				WriteWordIIC563(0x0cc,fWHITE|fBLACK);
		if(i == MenuPtr.Ptr && MenuPtr.Level == 1)
			WriteWordIIC563(0x0cc,fMAGENTA|fBLACK);
		else if(FuncBuf[pVIDEOSOURCE] == i && MenuPtr.Level == 0)
			WriteWordIIC563(0x0cc,fGREEN|fBLACK);
		else			
			WriteWordIIC563(0x0cc,fWHITE|fBLACK);
		//if(i == FuncBuf[pVIDEOSOURCE])
//		if(i == MenuPtr.Ptr && MenuPtr.Level == 1)
//			WriteWordIIC563(0x0cc,fMAGENTA|fBLACK);
//		else			
//			WriteWordIIC563(0x0cc,fWHITE|fBLACK);
		WriteSeqIndexPort(SyncModeAddr[i],tySRAM_CODE_CC_CD,Offset,Length);
		}
	if(MenuPtr.Level == 1) 
		Osd_On(enWIN4|enWIN2);
}
/*
void ShowTextGraphicMode()
{
	Byte code TextModeTab[]={"Text"};
	Byte code GraphicModeTab[]={"Graphic"};
	if(TextMode && GTmodeEn)
		WriteWordIIC563(0x0cc,fRED|fBLACK);
	else
		WriteWordIIC563(0x0cc,fYELLOW|fBLACK);
	WriteSeqIndexPort(ROW9+16,tySRAM_CODE_CC_CD,TextModeTab,4);
	if(!TextMode && GTmodeEn)
		WriteWordIIC563(0x0cc,fRED|fBLACK);
	else
		WriteWordIIC563(0x0cc,fYELLOW|fBLACK);
	WriteSeqIndexPort(ROW9+7,tySRAM_CODE_CC_CD,GraphicModeTab,7);
}
*/
void ShowYesNo(Byte Ptr)
{
code unsigned char ENG_NO[]={
	2,"No"
};
code unsigned char FRA_NO[]={
	3,"Non"
};
code unsigned char DEU_NO[]={
	4,"Nein"
};
code unsigned char ESP_NO[]={
	2,"No."
};
code unsigned char ITA_NO[]={
	2,"No"
};
code unsigned char JAP_NO[]={
	2,"No"
};
code unsigned char RSU_NO[]={
	3,_H,_e,_P05
};
code unsigned char CHT_NO[]={
	1,_C49
};
code unsigned char CHI_NO[]={
	1,_C49
};

code unsigned char ENG_YES[]={
	3,"Yes"
};
code unsigned char FRA_YES[]={
	3,"Oui"
};
code unsigned char DEU_YES[]={
	2,"Ja"
};
code unsigned char ESP_YES[]={
	2,"Si"
};
code unsigned char ITA_YES[]={
	2,"Si"
};
code unsigned char JAP_YES[]={
	3,"Yes"
};
code unsigned char RSU_YES[]={
	2,_P0f,_a
};
code unsigned char CHT_YES[]={
	1,_C4a
};
code unsigned char CHI_YES[]={
	1,_C4a
};

code unsigned char *YesNoTab[][9]={
	{ENG_NO,FRA_NO,DEU_NO,ESP_NO,ITA_NO,JAP_NO,RSU_NO,CHT_NO,CHI_NO},
	{ENG_YES,FRA_YES,DEU_YES,ESP_YES,ITA_YES,JAP_YES,RSU_YES,CHT_YES,CHI_YES}
};
	Byte i;
	Word code YesNoAddr[]={ROW8+17,ROW8+24};
	Byte *Offset,Length;

	
	for(i=0;i<2;i++)
	{
		Offset = YesNoTab[i][FuncBuf[pLANGUAGE]];
		Length = *Offset;
		Offset++;
		if(Ptr == i)
			if(((FuncPtr == pRECALL && MenuPtr.Ptr == 4)) && MenuPtr.Level == 1)
				WriteWordIIC563(0x0cc,fMAGENTA|fBLACK);
			else
				WriteWordIIC563(0x0cc,fGREEN|fBLACK);
		else
			WriteWordIIC563(0x0cc,fWHITE|fBLACK);
		WriteSeqIndexPort(YesNoAddr[i],tySRAM_CODE_CC_CD,Offset,Length);
	}
}

void ShowLanguage()
{
code unsigned char ENGStr[]={
	8,"English "
};
code unsigned char FRAStr[]={
	8,"Franais"
};
code unsigned char DEUStr[]={
	8,"Deutsch "
};
code unsigned char ESPStr[]={
	8,"Espaol "
};
code unsigned char ITAStr[]={
	8,"Italiano"
};
code unsigned char JAPStr[]={
	3,_C07,_C08,_C09
};
code unsigned char RUSStr[]={
	7,_P,_y,_c,_c,_P00,_P03,_P02
};
code unsigned char CHTStr[]={
	4,_C05,_C06,_C01,_C02
};
code unsigned char CHIStr[]={
	4,_C03,_C04,_C01,_C02
};
	Byte code *LanguageTab[]={
	ENGStr,FRAStr,DEUStr,ESPStr,ITAStr,JAPStr,RUSStr,CHTStr,CHIStr
};

	Word code LanguageAddr[9]={ROW4+2,ROW5+2,ROW6+2,ROW7+2,ROW8+2,ROW4+15,ROW5+15,ROW6+15,ROW7+15};
	Byte *Offset,i,Length;

	for(i=0;i<MAX_LANGUAGE;i++)
		{
//		if(i == MenuPtr.Ptr && MenuPtr.Level == 1)
//			WriteWordIIC563(0x0cc,fMAGENTA|fBLACK);
//		else			
//			WriteWordIIC563(0x0cc,fWHITE|fBLACK);
		if(FuncBuf[pLANGUAGE] == i)
			if(MenuPtr.Level == 1)
				WriteWordIIC563(0x0cc,fMAGENTA|fBLACK);
			else
				WriteWordIIC563(0x0cc,fGREEN|fBLACK);
		else			
			WriteWordIIC563(0x0cc,fWHITE|fBLACK);
		Offset = LanguageTab[i];
		Length = *Offset;
		Offset++;
		WriteSeqIndexPort(LanguageAddr[i],tySRAM_CODE_CC_CD,Offset,Length);
	}
	if(MenuPtr.Level !=0)
		ShowKeyMenu(3,MenuPtr.Level);
}

void ShowColorMenu()
{
	Byte i,*Offset,Length;
	Byte code ColorTab[][5]={{"9300K"},{"7500K"},{"6500K"},{"     "}};
	Word code ColorAddr[]={ROW4+2,ROW5+2,ROW6+2,ROW7+2};
	ClearLine(7);
	for(i=0;i<MAX_COLOR_TEMP;i++)
		{
		if(FuncBuf[pCOLORTEMP] == i)
			if(MenuPtr.Level == 1)
			WriteWordIIC563(0x0cc,fMAGENTA|fBLACK);
			else
			WriteWordIIC563(0x0cc,fGREEN|fBLACK);
		else			
			WriteWordIIC563(0x0cc,fWHITE|fBLACK);
		WriteSeqIndexPort(ColorAddr[i],tySRAM_CODE_CC_CD,ColorTab[i],4);
		}
	Offset = UserTab[FuncBuf[pLANGUAGE]];
	Length = *Offset++;
	WriteSeqIndexPort(ColorAddr[3],tySRAM_CODE_CC_CD,Offset,Length);
	ShowStatus(ROW11+2,fGREEN|bBLACK);
//	if(MenuPtr.Level ==1&& (FuncBuf[pCOLORTEMP]>2||FuncBuf[pCOLORTEMP]<1) )//change key when first and user item 
//		ShowKeyMenu(2,MenuPtr.Level);
}

void ShowTVMenu()
{
	Byte i;
	Byte code TV_Menu_Tab[][9]={{"CH SEARCH"},{"CH EDIT  "},{"FINE TUNE"},{"TV INPUT "}};
	Word code TV_Addr[]={ROW4+2,ROW5+2,ROW6+2,ROW7+2};
	ClearLine(7);
//	FuncBuf[pTVFUNCTION] = 0;
	for(i=0;i<4;i++)
		{
		if(FuncBuf[pTVFUNCTION] == i)
			if(MenuPtr.Level == 1)
			WriteWordIIC563(0x0cc,fMAGENTA|fBLACK);
			else
			WriteWordIIC563(0x0cc,fGREEN|fBLACK);
		else			
			WriteWordIIC563(0x0cc,fWHITE|fBLACK);
		WriteSeqIndexPort(TV_Addr[i],tySRAM_CODE_CC_CD,TV_Menu_Tab[i],9);
		}
}
void ShowRGBMenu()
{
	//Byte *Offset,i,Length;
	Word code RGBAddr[4]={ROW8+6,ROW9+6,ROW10+6,ROW11+6};
/*
	for(i=1;i<4;i++)
		{
		if((((i+3) == MenuPtr.Ptr) && (MenuPtr.Level == 2))||((i == MenuPtr.Ptr+1) && (MenuPtr.Level == 1)&& (MenuPtr.Menu == 2)))
			WriteWordIIC563(0x0cc,fMAGENTA|fBLACK);
		else			
			WriteWordIIC563(0x0cc,fWHITE|fBLACK);
		Offset = Tab_RGB[FuncBuf[pLANGUAGE]*3+(i-1)];
		Length = *Offset;
		Offset++;
		if(MenuPtr.Menu != 2)			
			WriteSeqIndexPort(RGBAddr[i-1],tySRAM_CODE_CC_CD,Offset,Length);
		else
			WriteSeqIndexPort(RGBAddr[i],tySRAM_CODE_CC_CD,Offset,Length);
		}
*/
//	if(MenuPtr.Menu != 2)
//	{
		switch(MenuPtr.Ptr){
			case 4:
//				if((MenuPtr.Ptr == 4) && (MenuPtr.Level == 2)){
					ShowBar(RGBAddr[0]+10,fMAGENTA|fBLACK,FuncMin,FuncMax,FuncBuf[pRCOLOR]);
					ShowValue(RGBAddr[0]+19,fMAGENTA|fBLACK,FuncBuf[pRCOLOR]);		
//				}
//				else{
//					ShowBar(RGBAddr[0]+10,fWHITE|fBLACK,FuncMin,FuncMax,FuncBuf[pRCOLOR]);
//					ShowValue(RGBAddr[0]+19,fWHITE|fBLACK,FuncBuf[pRCOLOR]);
//				}
			break;
			case 5:
//				if((MenuPtr.Ptr == 5) && (MenuPtr.Level == 2)){
					ShowBar(RGBAddr[1]+10,fMAGENTA|fBLACK,FuncMin,FuncMax,FuncBuf[pGCOLOR]);
					ShowValue(RGBAddr[1]+19,fMAGENTA|fBLACK,FuncBuf[pGCOLOR]);
//				}
//				else{
//					ShowBar(RGBAddr[1]+10,fWHITE|fBLACK,FuncMin,FuncMax,FuncBuf[pGCOLOR]);
//					ShowValue(RGBAddr[1]+19,fWHITE|fBLACK,FuncBuf[pGCOLOR]);
//				}
				break;
			case 6:
//				if((MenuPtr.Ptr == 6) && (MenuPtr.Level == 2)){
					ShowBar(RGBAddr[2]+10,fMAGENTA|fBLACK,FuncMin,FuncMax,FuncBuf[pBCOLOR]);
					ShowValue(RGBAddr[2]+19,fMAGENTA|fBLACK,FuncBuf[pBCOLOR]);
//				}
//				else{
//					ShowBar(RGBAddr[2]+10,fWHITE|fBLACK,FuncMin,FuncMax,FuncBuf[pBCOLOR]);
//					ShowValue(RGBAddr[2]+19,fWHITE|fBLACK,FuncBuf[pBCOLOR]);
//				}
				break;
		}
//		}
//	else
//	{
		//ShowBar(RGBAddr[1]+10,fWHITE|fBLACK,FuncMin,FuncMax,FuncBuf[pRCOLOR]);
		//ShowBar(RGBAddr[2]+10,fWHITE|fBLACK,FuncMin,FuncMax,FuncBuf[pGCOLOR]);
		//ShowBar(RGBAddr[3]+10,fWHITE|fBLACK,FuncMin,FuncMax,FuncBuf[pBCOLOR]);
//		ShowValue(RGBAddr[1]+19,fWHITE|fBLACK,FuncBuf[pRCOLOR]);
//		ShowValue(RGBAddr[2]+19,fWHITE|fBLACK,FuncBuf[pGCOLOR]);
//		ShowValue(RGBAddr[3]+19,fWHITE|fBLACK,FuncBuf[pBCOLOR]);
//	}
}

void ClearOSD(void)
{
// Clear osd ram
	WriteWordIIC563(0x0cc,fBLACK|bBLACK|caMIX);
	WriteIIC563(0x0ce,0x20);
	WriteIIC563(0x0cf,0x01);
	// Wait for Clear Ready....
	LocalTimer = 10;
	while(((ReadIIC563(0x0cf) & BIT_0) != 0) && LocalTimer != 0){
		if(FuncBuf[pVIDEOSOURCE] <cSVIDEO) //jacky20040324
			CheckModeChange();
	}
	//Sleep(1);
}

void ClearTextArea()
{
	WriteWordIIC563(0x0cc,fBLACK|fBLACK);
	WriteSeqIndexPort(ROW4+1,tySRAM_CODE_CC_CD,SPACE,28);
	WriteSeqIndexPort(ROW5+1,tySRAM_CODE_CC_CD,SPACE,28);
	WriteSeqIndexPort(ROW6+1,tySRAM_CODE_CC_CD,SPACE,28);
	WriteSeqIndexPort(ROW7+1,tySRAM_CODE_CC_CD,SPACE,28);
	WriteSeqIndexPort(ROW8+1,tySRAM_CODE_CC_CD,SPACE,28);
	WriteSeqIndexPort(ROW9+1,tySRAM_CODE_CC_CD,SPACE,28);
	WriteSeqIndexPort(ROW10+1,tySRAM_CODE_CC_CD,SPACE,28);
}

void ClearLine(Byte Line)
{
	WriteWordIIC563(0x0cc,fBLACK|fBLACK);
	WriteSeqIndexPort(Line*OSD_WIDTH+1,tySRAM_CODE_CC_CD,SPACE,28);
}

void OsdInit(void)
{
	Byte i;
	FuncBuf[pTRANSOSD] = Read24C16(ep_Osd_Effect);
	SetOsdTrans();
	ClearOSD();
	ShowOSDFrame(0);
	WriteIIC563(0x080,0);
	WriteIIC563(0x090,0x00);  // zooming off
	WriteIIC563(0x095,0x55);
	WriteIIC563(0x083,OSD_WIDTH-1);
	WriteIIC563(0x086,OSD_HIGH-1);
	WriteIIC563(0x0a2,0);
	WriteWordIIC563(0x088,ONE_BIT_START_ADDR);
	WriteWordIIC563(0x08a,TWO_BIT_START_ADDR);
	WriteWordIIC563(0x08c,FOUR_BIT_START_ADDR);
	for(i=0;i<13;i++)
		WriteWordIndexPort(i,tySRAM_PALETTE,Palette1Bit[i]);
	for(i=0;i<14*4;i++)
		WriteWordIndexPort(i+OFFSET_2BIT,tySRAM_PALETTE,Palette2Bit[i]);
//	for(i=0;i<6*16;i++)
//		WriteWordIndexPort(i+OFFSET_4BIT,tySRAM_PALETTE,Palette4Bit[i]);
	WriteSeqIndexPort(0,tySRAM_1BIT,OneBitFont,156*27);
	WriteSeqIndexPort(0xa0,tySRAM_1BIT,OneBitFont2,48*27);
	if(FuncBuf[pLANGUAGE]== 5){
		WriteSeqIndexPort(0xd0,tySRAM_1BIT,OneBitFontJP,45*27);
		WriteSeqIndexPort(0x90,tySRAM_1BIT,OneBitFontJP2,7*27);
	}
	else if((FuncBuf[pLANGUAGE] == 7)||(FuncBuf[pLANGUAGE] == 8)){
		WriteSeqIndexPort(0xd0,tySRAM_1BIT,OneBitFontCH2,48*27);
		WriteSeqIndexPort(0x90,tySRAM_1BIT,OneBitFontCH3,6*27);
	}
	else
		WriteSeqIndexPort(0x90,tySRAM_1BIT,OneBitFontPY,7*27);
	//WriteSeqIndexPort(0x100,tySRAM_1BIT,OneBitIcon,99*27);
	WriteSeqIndexPort(0x100,tySRAM_1BIT,OneBitIcon,45*27);
	WriteSeqIndexPort(0,tySRAM_2BIT,TwoBitFont,15*54);
	WriteSeqIndexPort(15,tySRAM_2BIT,TwoBitIcon,36*54);
//	WriteSeqIndexPort(0,tySRAM_4BIT,FourBitFont,3*6*108);
	OsdPosition();
	MenuPtr.Menu = 0;
	MenuPtr.Level = 0;
	MenuPtr.Ptr = 0;
	MenuPtr.Op = 0;
}

void OsdPosition()
{
/*	
	#ifdef X15
	Word code OSD_PX[]={
		64,600,332,64,600
	};
	Word code OSD_PY[]={
		64,64,249,434,434
	};
	Word code OSD_PY1[]={
		64,64,330,434,434
	};
	#endif
	#ifdef X17
	Word code OSD_PX[]={
		80,840,460,80,840
	};
	Word code OSD_PY[]={
		85,85,375,669,669
	};
	Word code OSD_PY1[]={
		85,85,458,669,669
	};
	#endif
	#ifdef X19
	Word code OSD_PX[]={
		80,840,460,80,840
	};
	Word code OSD_PY[]={
		85,85,375,669,669
	};
	Word code OSD_PY1[]={
		85,85,458,669,669
	};
	#endif
	#ifdef X21
	Word code OSD_PX[]={
		99,1129,614,99,1129
	};
	Word code OSD_PY[]={
		99,99,465,831,831
	};
	Word code OSD_PY1[]={
		99,99,548,831,831
	};
	#endif
*/	
	Word code OSD_PX[]={
		OSD_X1, OSD_X2, OSD_X3, OSD_X1, OSD_X2
	};
	Word code OSD_PY[]={
		OSD_Y1, OSD_Y1, OSD_Y3, OSD_Y2, OSD_Y2
	};
	Word code OSD_PY1[]={
		OSD_Y1, OSD_Y1, OSD_Y4, OSD_Y2, OSD_Y2
	};

	Word OSD_HPOS,OSD_VPOS;
	Byte Temp;

	Temp = ReadIIC563(0x080);
	WriteIIC563(0x080,(Temp & (~enOSD))); // OSD disable
	OSD_HPOS = OSD_PX[FuncBuf[pOSDHPOSITION]];
	if(MenuPtr.Menu == 3)
		OSD_VPOS = OSD_PY1[FuncBuf[pOSDHPOSITION]];
	else
		OSD_VPOS = OSD_PY[FuncBuf[pOSDHPOSITION]];
	if(OSD_HPOS < (PanelWidth-OSD_WIDTH*12))
		WriteWordIIC563(0x081,OSD_HPOS);
	else
		WriteWordIIC563(0x081,PanelWidth-OSD_WIDTH*12);
	if(OSD_VPOS < (PanelHeight-OSD_HIGH*18))
		WriteWordIIC563(0x084,OSD_VPOS);
	else
		WriteWordIIC563(0x084,PanelHeight-OSD_HIGH*18);

	WriteIIC563(0x080,Temp); // OSD enable
/*
	if(FuncBuf[pOSDHPOSITION] < (PanelWidth-OSD_WIDTH*12)/5)
		WriteWordIIC563(0x081,FuncBuf[pOSDHPOSITION]*5);
	else
		WriteWordIIC563(0x081,PanelWidth-OSD_WIDTH*12);
	if(FuncBuf[pOSDVPOSITION] < (PanelHeight-OSD_HIGH*18)/5)
		WriteWordIIC563(0x084,FuncBuf[pOSDVPOSITION]*5);
	else
		WriteWordIIC563(0x084,PanelHeight-OSD_HIGH*18);
*/
}

void Osd_On(Byte Win)
{
	WriteIIC563(0x080,enOSD|Win);
	OsdEnable = 1;
}

void Osd_Off(void)
{
	WriteIIC563(0x080,0);
	MenuPtr.Menu = 0;
	MenuPtr.Level = 0;
	MenuPtr.Ptr = 0;
	MenuPtr.Op = 0;
	OsdEnable = 0;
	OSDZoomFlag = 0;
}

void ShowIcon(Byte Ptr)
{
	Word Addr,Attr;
	Byte Icon;
	if((FuncBuf[pVIDEOSOURCE]==cTV)&&(Ptr == 2))
		Icon = 7;
	else
		{
		Icon = MenuItem[Ptr].Icon;
//		printf("Icon=%d\r\n",(Word)Icon);
	}
	
	Addr = MenuItem[Ptr].Address;
	//if(Icon == 6)///1bit
	//	{
	//	Attr = ((Icon-6)*16)<<8;
		//Icon = Icon -6;
	//	WriteWordIIC563(0x0cc,Attr|caFOUR_BIT);
	//	}
	//else
	//	{
		Attr = (Icon*4+OFFSET_2BIT+8)<<8;
	//	}

	Icon = Icon*6+15;
	if(MenuPtr.Page == Ptr)
		{
		if(Icon == 51)///1bit
		{
			Icon = 0;
			WriteWordIIC563(0x0cc,Attr|caONE_BIT_512|caBLINK);
		}
		else if(Icon == 57){ // 7x6+15 = 57
			Icon = 39;
				
			WriteWordIIC563(0x0cc,Attr|caONE_BIT_512|caBLINK);

		}
		else
			WriteWordIIC563(0x0cc,Attr|caTWO_BIT|caBLINK);
		//WriteWordIIC563(0x0cc,fCYAN|caONE_BIT_512);
		//WriteWordIIC563(0x0cc,fCYAN|caTWO_BIT);
		}
	else
		{
		if(Icon == 51)///1bit
		{
			Icon = 0;
			WriteWordIIC563(0x0cc,Attr|caONE_BIT_512);
		}
		else if(Icon == 57){ // 7x6+15 = 57
			Icon = 39;
			WriteWordIIC563(0x0cc,Attr|caONE_BIT_512);

		}
		else
			WriteWordIIC563(0x0cc,Attr|caTWO_BIT);
		//WriteWordIIC563(0x0cc,fWHITE|caONE_BIT_512);
		//WriteWordIIC563(0x0cc,fWHITE|caTWO_BIT);
		}
	WriteIndexPort(Addr,tySRAM_CODE_CC_CD,Icon);
	WriteIndexPort(Addr+1,tySRAM_CODE_CC_CD,Icon+1);
	WriteIndexPort(Addr+2,tySRAM_CODE_CC_CD,Icon+2);
	WriteIndexPort(Addr+ROW1,tySRAM_CODE_CC_CD,Icon+3);
	WriteIndexPort(Addr+ROW1+1,tySRAM_CODE_CC_CD,Icon+4);
	WriteIndexPort(Addr+ROW1+2,tySRAM_CODE_CC_CD,Icon+5);
}

void ShowMain(Byte Page)
{
	//Byte code MaxItemTab[]={MAX_DSUB_ITEM,MAX_DVI_ITEM,MAX_VIDEO_ITEM,MAX_VIDEO_ITEM};
	Byte i,temp;

	WriteIIC563(0x080,0); // OSD disable
	ClearOSD();
	WriteIIC563(0x090,0x00);  // zooming off
	ShowOSDFrame(0);
//	if(FuncBuf[pVIDEOSOURCE] < 2)
//		{
//		for(i=0;i<4;i++)
			WriteWordIndexPort(i+OFFSET_2BIT,tySRAM_PALETTE,Palette2Bit[i]);
//		for(i=0;i<16;i++)
//			WriteWordIndexPort(i+OFFSET_4BIT,tySRAM_PALETTE,Palette4Bit[i]);
		WriteSeqIndexPort(0,tySRAM_2BIT,TwoBitFont,15*54);
//		WriteSeqIndexPort(0,tySRAM_4BIT,FourBitFont,2*6*108);
//		}
//	else
//		{
//		for(i=0;i<4;i++)
//			WriteWordIndexPort(i+OFFSET_2BIT,tySRAM_PALETTE,Palette2Bit[i+4*14]);
//		for(i=0;i<16;i++)
//			WriteWordIndexPort(i+OFFSET_4BIT,tySRAM_PALETTE,Palette4Bit[i+16*6]);
//		WriteSeqIndexPort(0,tySRAM_2BIT,TwoBitFont+(13*6+7)*54,1*6*54);
//		WriteSeqIndexPort(0,tySRAM_4BIT,FourBitFont+5*6*108,1*6*108);	//Hue
//		WriteSeqIndexPort(6,tySRAM_4BIT,FourBitFont+1*6*108,1*6*108);	//OSD Trans
//		}
	OsdPosition();
	OpenWindow(WINDOW4,WIN4_X1,WIN4_X2,WIN4_Y1,WIN4_Y2,WIN4_ATTR,WIN4_COLOR);
	temp = FuncBuf[pVIDEOSOURCE]; 
	if(FuncBuf[pVIDEOSOURCE] == cDVI)	//DVI
		FuncBuf[pVIDEOSOURCE] = cANALOG;	//DSUB / DVI show same menu
	//for(i=0;i<MaxItemTab[FuncBuf[pVIDEOSOURCE]];i++)
	//	ShowIcon(i);
	RefreshIcon();	
	FuncBuf[pVIDEOSOURCE] = temp;
	ShowKeyMenu(Page,MenuPtr.Level);	//first enter page 0 set 
	ShowSubMenu(Page,0);
	if(FuncBuf[pVIDEOSOURCE] < cSVIDEO){
		ShowResolution(MAINMENU_RES_ADDR,RES_COLOR);
		ShowStatus(ROW11+2,fGREEN|bBLACK);
	}
	else
		ShowTvSystem();
}

void ShowTvSystem()
{
	Byte code SourceTab1[][7]={" D-SUB ","  DVI  "," YPbPr ","S-Video","Video  ","   TV  "};
//	Byte code TvTab[][9]={"PAL 4.43 ","NTSC 4.43"," NTSC N  ","  SECAM  "," UNKNOW  "," SECAM   ","  MONO   ",
//						  " NTSC M  ","PAL 4.43 ","NTSC 4.43","  PAL M  "," NTSC J  "," UNKNOW  ","  MONO   "};
	WriteWordIIC563(0x0cc,RES_COLOR);
//	WriteSeqIndexPort(MAINMENU_RES_ADDR-3,tySRAM_CODE_CC_CD,TvTab[TvMode],9);
	WriteSeqIndexPort(MAINMENU_RES_ADDR+7,tySRAM_CODE_CC_CD,SourceTab1[FuncBuf[pVIDEOSOURCE]],7);
}

void ShowFactMenu()
{
	Byte i;
	Byte code FactTab[][7]={{"AdcOft "},{"AdcGain"},{"9300K  "},{"7500K  "},{"6500K  "},{"Cont.  "},{"Brig.  "}};
	Word code FactAddr[]={ROW5+1,ROW6+1,ROW7+1,ROW8+1,ROW9+1,ROW10+1,ROW11+1};
	Byte *Offset,Length;//,Win_X1,Win_X2,Win_Y1,Win_Y2;

	ClearOSD();
	//ShowOSDFrame(0);
	WriteIIC563(0x090,0x00);  // zooming off
	WriteWordIIC563(0x081,OSD_FACT_HPOS);
	WriteWordIIC563(0x084,OSD_FACT_VPOS);
	OpenWindow(WINDOW4,WIN4_X1,WIN4_X2,WIN4_Y1,WIN4_Y2,WIN4_ATTR,WIN4_COLOR);
	//OpenWindow(WINDOW3,WIN3_X1,WIN3_X2,WIN3_Y1,WIN3_Y2,WIN3_ATTR,WIN3_COLOR);
	ShowVersion();
	ShowMode(ROW12+1,MODE_COLOR);
	ShowBackLightTime();
	for(i=0;i<7;i++)
	{
//		if(i < 3)
//			WriteWordIIC563(0x0cc,fYELLOW|bBLUE);
//		else			
		WriteWordIIC563(0x0cc,fWHITE|bBLUE);
		WriteSeqIndexPort(FactAddr[i],tySRAM_CODE_CC_CD,FactTab[i],7);
	}
	for(i=0;i<MAX_FACT_ITEM;i++)
	{
//		Addr = FactItem[i].Address;
		Offset = FactItem[i].Tab;
		Length = *Offset;
		Offset++;
		if(i == MenuPtr.Ptr && MenuPtr.Level == 0)
		{
			WriteWordIIC563(0x0cc,fYELLOW|bLBLUE);
			WriteSeqIndexPort(FactItem[i].Address,tySRAM_CODE_CC_CD,Offset,Length);
		}
		else
		{
			WriteWordIIC563(0x0cc,fYELLOW|bBLUE);
			WriteSeqIndexPort(FactItem[i].Address,tySRAM_CODE_CC_CD,Offset,Length);
		}
		if(i > 2 && i != 26){
			if(i >= 11 && i <= 19){
				FuncBuf[pCOLORTEMP] = (i - 11)/3;
				LoadColor(FuncBuf[pCOLORTEMP]);
			}
			else{
				FuncBuf[pCOLORTEMP] = 2;
				LoadColor(FuncBuf[pCOLORTEMP]);
			}
			FuncPtr = FactItem[i].Index;
			GetFuncRange(FuncPtr);
			//GetFuncRange(FactItem[i].Index);		
			if(i == MenuPtr.Ptr && MenuPtr.Level == 1)
			{
				ShowValue(FactItem[i].SelAddr,fYELLOW|bLBLUE,FuncBuf[FactItem[i].Index]);
			}
			else
			{
				ShowValue(FactItem[i].SelAddr,fWHITE|bBLUE,FuncBuf[FactItem[i].Index]);
			}
		}
	}

	ShowFactCursor();
}

void ShowFact()
{
	//Byte *Offset,Length,Win_X1,Win_X2,Win_Y1,Win_Y2;
	
	if(MenuPtr.Ptr > 2 && MenuPtr.Level == 1)
	{
		ShowValue(FactItem[MenuPtr.Ptr].SelAddr,fWHITE|bBLUE,FuncBuf[FactItem[MenuPtr.Ptr].Index]);
	}
	
	if(MenuPtr.Op != oDECVAL && MenuPtr.Op != oINCVAL){
		ShowFactCursor();
	}
}
void ShowFactCursor()
{
	Byte *Offset,Length,Win_X1,Win_X2,Win_Y1,Win_Y2;
	Osd_On(enWIN4); 	
	Offset = FactItem[MenuPtr.Ptr].Tab;
	Length = *Offset;
	if(MenuPtr.Level == 1 && MenuPtr.Ptr > 2){
		Win_X1 = FactItem[MenuPtr.Ptr].SelAddr % OSD_WIDTH;
		Win_X2 = Win_X1 + 2;
	}
	else{
		Win_X1 = FactItem[MenuPtr.Ptr].Address % OSD_WIDTH;
		Win_X2 = Win_X1 + Length - 1;
	}
	Win_Y1 = FactItem[MenuPtr.Ptr].SelAddr / OSD_WIDTH;
	Win_Y2 = FactItem[MenuPtr.Ptr].SelAddr / OSD_WIDTH;
	OpenWindow(WINDOW3,Win_X1,Win_X2,Win_Y1,Win_Y2,WIN3_ATTR,WIN3_COLOR);
	Osd_On(enWIN4|enWIN3);	
}
void RefreshIcon()
{
	Byte i,x,y;

	for(i=0;i<7;i++)
		ShowIcon(i);
	x = MenuItem[MenuPtr.Page].Address % OSD_WIDTH;
	y = MenuItem[MenuPtr.Page].Address / OSD_WIDTH;
	Osd_On(enWIN4);
	OpenWindow(WINDOW2,x,x+2,y,y+1,WIN2_ATTR,SET_ICON_COLOR);

	Osd_On(enWIN4|enWIN2);
}

void ShowDesc(Byte Ptr,Word Addr,Word Attr)
{
	Byte *Offset,Length;
	Offset = DescTab[Ptr][FuncBuf[pLANGUAGE]];
	Length = *Offset;
	Offset++;
	WriteWordIIC563(0x0cc,Attr);
	WriteSeqIndexPort(Addr,tySRAM_CODE_CC_CD,Offset,Length);
}

void ShowDesc_TV(Byte Ptr,Word Addr,Word Attr)
{
	Byte *Offset,Length;
	Offset = DescTab_TV[Ptr][FuncBuf[pLANGUAGE]];
	Length = *Offset;
	Offset++;
	WriteWordIIC563(0x0cc,Attr);
	WriteSeqIndexPort(Addr,tySRAM_CODE_CC_CD,Offset,Length);
}

void ShowDesc_Sound(Byte Ptr,Word Addr,Word Attr)
{
	Byte *Offset,Length;
	Offset = DescTab_Sound[Ptr][FuncBuf[pLANGUAGE]];
	Length = *Offset;
	Offset++;
	WriteWordIIC563(0x0cc,Attr);
	WriteSeqIndexPort(Addr,tySRAM_CODE_CC_CD,Offset,Length);
}

void WriteIndexPort(Word Addr,Byte Type,Byte Ch)
{
	CheckRegPage(0xe0);
	IIC_Start();
	IIC_Tx(SCALER_ADDR);
	IIC_Tx(0xe0);
	IIC_Tx(Type);
	IIC_Tx(Addr&0x00ff);
	IIC_Tx(Addr>>8);
	IIC_Tx(Ch);
	IIC_Stop();
}

void WriteWordIndexPort(Word Addr,Byte Type,Word Ch)
{
	CheckRegPage(0xe0);
	IIC_Start();
	IIC_Tx(SCALER_ADDR);
	IIC_Tx(0xe0);
	IIC_Tx(Type);
	IIC_Tx(Addr&0x00ff);
	IIC_Tx(Addr>>8);
	IIC_Tx(Ch&0x00ff);
	IIC_Tx(Ch>>8);
	IIC_Stop();
}

void WriteSeqIndexPort(Word Addr,Byte Type,Byte *Ptr,Word Leng)
{
	Word i;
	CheckRegPage(0xe0);
	IIC_Start();
	IIC_Tx(SCALER_ADDR);
	IIC_Tx(0xe0);
	IIC_Tx(Type&(~tyWITH_LANGTH));
	if(Type & tyWITH_LANGTH)	//if(tyWITH_LENGH) get string length from table 
		Leng = *Ptr++;
	IIC_Tx(Addr&0x00ff);
	IIC_Tx(Addr>>8);
	for(i=0; i<Leng; i++)
		IIC_Tx(*Ptr++);
	IIC_Stop();
}

void OpenWindow(Byte Win,Byte x1,Byte x2,Byte y1,Byte y2,Byte Attr,Byte Col)
{
	CheckRegPage(0xe0);
	IIC_Start();
	IIC_Tx(SCALER_ADDR);
	IIC_Tx(0xa5);
	IIC_Tx(Win);
	IIC_Tx(x1);
	IIC_Tx(x2);
	IIC_Tx(y1);
	IIC_Tx(y2);
	if(FuncBuf[pTRANSOSD] != 0 && Win == WINDOW4)
		IIC_Tx(Attr|0x10);
	else
		IIC_Tx(Attr);
	IIC_Tx(Col);
	IIC_Stop();
}

void BCD(Word Value,Byte *VaSeq,Byte Zero)
{
	Byte temp,i;
	for(i=5;i>0;i--)
		{
		temp = Value % 10;
		*(VaSeq+i-1) =  temp+'0';
		Value /= 10;
		}
	for(i=0;i<(5-Zero);i++)
		{
		if(*(VaSeq+i) == '0')
			*(VaSeq+i) = ' ';
		else
			break;
		}
}

void ShowValue(Word Addr,Word Attr,Word Value)
{
	Word Percent;
	unsigned long temp;
	Byte Ptr[5];

	if(MenuPtr.Menu != 2 || FuncPtr == pCONTRAST){
		Percent = Value - FuncMin;
		temp = Percent * 100;
	}
	else{
		Percent = Value;
		temp = Percent * FuncMax;
	}
	
	Percent = temp / (FuncMax - FuncMin);
	switch(FuncPtr)
		{
		case pHPOSITION:
// Jacky 0201 removed
//		case pOSDVPOSITION:
			Percent = 100 - Percent;
			break;
		case pOSDTIMER:
			Percent = Value;
			temp = Percent * FuncMax;
			Percent = temp / (FuncMax - 0);
			break;
		case pVCMVOL:
		case pVIDEOSOURCE:  // channel No display
		//case pLIGHTHSTART:
		//case pLIGHTHWIDTH:
		//case pLIGHTVSTART:
		//case pLIGHTVHIGHT:
			Percent = Value;
			break;
//		default:
//			Percent = Value;

		};
	WriteWordIIC563(0x0cc,Attr);
	BCD(Percent,Ptr,1);
	WriteSeqIndexPort(Addr,tySRAM_CODE_CC_CD,Ptr+2,3);
}

void ShowBar(Word Addr,Word Attr,Word Min,Word Max,Word Value)
{
	Byte i,Ptr;
	Word Percent,temp;
	unsigned long Wtemp;
	WriteWordIIC563(0x0cc,Attr);
	temp = (Value - Min);
	Wtemp = temp * BAR_LENGTH * BAR_SEGMENT;
 	Percent = Wtemp / (Max-Min);
	if(Percent > (BAR_LENGTH * BAR_SEGMENT))
		Percent = BAR_LENGTH * BAR_SEGMENT;
	//reverse
	switch(FuncPtr)
		{
		case pHPOSITION:
// Jacky 0201 removed
//		case pOSDVPOSITION:
			Percent = (BAR_LENGTH*BAR_SEGMENT) - Percent;
			break;
		};
	IIC_Start();
	IIC_Tx(SCALER_ADDR);
	IIC_Tx(0xe0);
	IIC_Tx(tySRAM_CODE_CC_CD);
	IIC_Tx(Addr&0x00ff);	
	IIC_Tx(Addr>>8);
	IIC_Tx(0x19);		//bar '['	Data
	Ptr = Percent / BAR_SEGMENT;
	for(i=0;i<Ptr;i++)
		temp = IIC_Tx(0x1e);	//bar full icon Data
	Ptr = Percent % BAR_SEGMENT;
	//if(Ptr == 6)
	//	Ptr --;
	if(Percent<(BAR_LENGTH * BAR_SEGMENT) && Percent>0)
		{
		IIC_Tx(0x1a+Ptr);	//bar mid icon Data
		i++;
		}
	for(;i<BAR_LENGTH;i++)
		IIC_Tx(0x1a);	//bar empty icon Data
	IIC_Tx(0x1f);		//bar ']' icon Data
	IIC_Stop();	
}

/*
void ShowCBar(Word Addr,Word Attr,Word Min,Word Max,Word Value)
{
	Byte i,Ptr;
	Word Percent,temp;
	unsigned long Wtemp;
	WriteWordIIC563(0x0cc,Attr);
	temp = (Value - Min);
	Wtemp = temp * CBAR_LENGTH * CBAR_SEGMENT;
 	Percent = Wtemp / (Max-Min);
	if(Percent > (CBAR_LENGTH * CBAR_SEGMENT))
		Percent = CBAR_LENGTH * CBAR_SEGMENT;
	IIC_Start();
	IIC_Tx(SCALER_ADDR);
	IIC_Tx(0xe0);
	IIC_Tx(tySRAM_CODE_CC_CD);
	IIC_Tx(Addr&0x00ff);	
	IIC_Tx(Addr>>8);
	IIC_Tx(0x19);		//bar '['	Data
	Ptr = Percent / CBAR_SEGMENT;
	for(i=0;i<Ptr;i++)
		temp = IIC_Tx(0x1e);	//bar full icon Data
	Ptr = Percent % CBAR_SEGMENT;
	//if(Ptr == 6)
	//	Ptr --;
	if(Percent<(CBAR_LENGTH * CBAR_SEGMENT) && Percent>0)
		{
		IIC_Tx(0x1a+Ptr);	//bar mid icon Data
		i++;
		}
	for(;i<CBAR_LENGTH;i++)
		IIC_Tx(0x1a);	//bar empty icon Data
	IIC_Tx(0x1f);		//bar ']' icon Data
	IIC_Stop();	
}
*/

void ShowDebug(Word Addr,Word Attr,Word Val)		// +jwshin 061019
{
	Byte VaSeq[5];
	WriteWordIIC563(0x0cc,Attr);
	BCD(Val,VaSeq,2);
	WriteSeqIndexPort(Addr,tySRAM_CODE_CC_CD,VaSeq+1,4);
	
}


void ShowResolution(Word Addr,Word Attr)
{
	Byte VaSeq[5];
	WriteWordIIC563(0x0cc,Attr);
	BCD(Hresolution,VaSeq,2);
	WriteSeqIndexPort(Addr,tySRAM_CODE_CC_CD,VaSeq+1,4);
	WriteIndexPort(Addr+4,tySRAM_CODE_CC_CD,'x');
	BCD(Vresolution,VaSeq,2);
	WriteSeqIndexPort(Addr+5,tySRAM_CODE_CC_CD,VaSeq+1,4);
	WriteIndexPort(Addr+9,tySRAM_CODE_CC_CD,'@');
	BCD(V_SYNC,VaSeq,2);
	WriteSeqIndexPort(Addr+10,tySRAM_CODE_CC_CD,VaSeq+2,2);
//	WriteIndexPort(Addr+14,tySRAM_CODE_CC_CD,VaSeq[4]);
	WriteIndexPort(Addr+12,tySRAM_CODE_CC_CD,'H');
	WriteIndexPort(Addr+13,tySRAM_CODE_CC_CD,'z');
}

void ShowMode(Word Addr,Word Attr)
{
	Byte VaSeq[5];
	WriteWordIIC563(0x0cc,Attr);
	BCD(ModePoint,VaSeq,2);
	if(ModePoint < UserModeSt)
		WriteSeqIndexPort(Addr,tySRAM_CODE_CC_CD,"Preset Mode:",12);
	else
		WriteSeqIndexPort(Addr,tySRAM_CODE_CC_CD,"  User Mode:",12);
	WriteSeqIndexPort(Addr+12,tySRAM_CODE_CC_CD,VaSeq+3,2);
}

void ShowMessage(Byte No)
{
	Byte code SourceTab[][7]={"Analog ","DVI    "," YPBPR ","S-Video"};		// +jwshin 061018
	Byte code MsgIcon[]={0,0,0,6,6,6};
	Byte code FuncCode[]={pOUTOFRANGE,pNOSIGNAL,pNOSIGNAL,pAUTOADJUST,pAUTOCOLOR ,pEEPROMINIT};
	WriteIIC563(0x090,0x00);  // zooming off
	if(No == MSG_OUTRANGE)
		ShowOutOfRange();
	else{
		ClearOSD();
		WriteWordIIC563(0x081,(PanelWidth-30*12)/2);
		WriteWordIIC563(0x084,(PanelHeight-5*18)/2);
		OpenWindow(WINDOW4,0,29,0,4,atWIN_SHADOW_4L,bLIGHT>>4);
		WriteWordIIC563(0x0cc,fMAGENTA|caONE_BIT_512);

		WriteIndexPort(ROW1+3,tySRAM_CODE_CC_CD,MsgIcon[No]);
		WriteIndexPort(ROW1+4,tySRAM_CODE_CC_CD,MsgIcon[No]+1);
		WriteIndexPort(ROW1+5,tySRAM_CODE_CC_CD,MsgIcon[No]+2);
		WriteIndexPort(ROW2+3,tySRAM_CODE_CC_CD,MsgIcon[No]+3);
		WriteIndexPort(ROW2+4,tySRAM_CODE_CC_CD,MsgIcon[No]+4);
		WriteIndexPort(ROW2+5,tySRAM_CODE_CC_CD,MsgIcon[No]+5);
		ShowDesc(FuncCode[No],ROW2+7,fWHITE|bBLACK);
		if(No == MSG_NOSYNC) {						// +jwshin 061018	
			WriteSeqIndexPort(ROW0+12,tySRAM_CODE_CC_CD,SourceTab[FuncBuf[pVIDEOSOURCE]],7);
		}
	}
	if(No == MSG_OUTRANGE)
		ShowStatus(ROW5+2,fWHITE|bBLACK);
//	if(No != MSG_NOSYNC)
//		if(No != MSG_OUTRANGE)
//			ShowStatus(ROW3+2,fGREEN|bBLACK);
//		else
//			ShowStatus(ROW6+2,fWHITE|bBLACK);
	Osd_On(enWIN4);
}

void ShowOutOfRange()
{
	Byte i;
	Byte VaSeq[5];
	
	ClearOSD();
	WriteIIC563(0x090,0x00);  // zooming off
	WriteWordIIC563(0x081,(PanelWidth-30*12)/2);
	WriteWordIIC563(0x084,(PanelHeight-7*18)/2);
	OpenWindow(WINDOW4,0,29,0,6,atWIN_SHADOW_4L,bRED>>4);
	WriteWordIIC563(0x0cc,fWHITE|caONE_BIT_512);
	
	for(i=0;i<3;i++){
		WriteIndexPort(ROW2+3+i,tySRAM_CODE_CC_CD,i);
		WriteIndexPort(ROW3+3+i,tySRAM_CODE_CC_CD,3+i);
		//WriteIndexPort(ROW4+3+i,tySRAM_CODE_CC_CD,51+i);
		//WriteIndexPort(ROW5+3+i,tySRAM_CODE_CC_CD,57+i);
	}

	ShowDesc(pOUTOFRANGE,ROW1+10,fWHITE|bBLACK);

	WriteWordIIC563(0x0cc,fWHITE|bBLACK);
	
	WriteSeqIndexPort(ROW3+12,tySRAM_CODE_CC_CD,"H:",2);
	BCD(H_SYNC,VaSeq,2);
	WriteSeqIndexPort(ROW3+14,tySRAM_CODE_CC_CD,VaSeq+1,3);
	WriteIndexPort(ROW3+17,tySRAM_CODE_CC_CD,'.');
	WriteIndexPort(ROW3+18,tySRAM_CODE_CC_CD,VaSeq[4]);
	WriteSeqIndexPort(ROW3+19,tySRAM_CODE_CC_CD,"KHz",3);
	WriteSeqIndexPort(ROW4+12,tySRAM_CODE_CC_CD,"V:",2);
	BCD(V_SYNC,VaSeq,2);
	WriteSeqIndexPort(ROW4+14,tySRAM_CODE_CC_CD,VaSeq+1,3);
	WriteIndexPort(ROW4+17,tySRAM_CODE_CC_CD,'.');
	WriteIndexPort(ROW4+18,tySRAM_CODE_CC_CD,VaSeq[4]);
	WriteSeqIndexPort(ROW4+19,tySRAM_CODE_CC_CD,"Hz",2);
	WriteSeqIndexPort(ROW5+12,tySRAM_CODE_CC_CD,"Max:",4);
	BCD(PanelWidth,VaSeq,2);
	WriteSeqIndexPort(ROW5+16,tySRAM_CODE_CC_CD,VaSeq+1,4);
	WriteIndexPort(ROW5+20,tySRAM_CODE_CC_CD,'x');
	BCD(PanelHeight,VaSeq,2);
	WriteSeqIndexPort(ROW5+21,tySRAM_CODE_CC_CD,VaSeq+1,4);
}
/*
void WritePage560(unsigned char addr1,unsigned char addr2,unsigned char *p)
{
unsigned char i,ch;
	IIC_Start();
	IIC_Tx(SCALER_ADDR);
	IIC_Tx(addr1);
	for(i=0; i<16; i++){
		ch = p[addr2 + i];
		IIC_Tx(ch);
	}
	IIC_Stop();
}
*/
/*
void ShowSource()
{

	Byte code SourceTab[][7]={"Analog ","Digital"," CVBS  ","S-Video"};
	ClearOSD();
	WriteWordIIC563(0x081,PanelWidth-8*12);
	WriteWordIIC563(0x084,5);
	WriteWordIIC563(0x0cc,SOURCE_COLOR);
	WriteSeqIndexPort(ROW0,tySRAM_CODE_CC_CD,SourceTab[FuncBuf[pVIDEOSOURCE]],7);
	Osd_On(0);
	OsdTimer = 200;

}
*/

//--------------------- +jwshin 061025   Mute Function Added...
void ShowMuteFuncOnOff()
{
	if(AudioMute) {
		AudioMute = 0;
	}
	else {
		AudioMute = 1;
	}
	SetAudioMute();
	Write24C16(ep_Status,StatusFlag);
	WriteIIC563(0x090,0x00);	// zooming off
	ClearOSD();
	WriteWordIIC563(0x081,(PanelWidth-30*12));
	WriteWordIIC563(0x084,(PanelHeight-5*18));
	WriteWordIIC563(0x0cc,MODE_COLOR);
	if(AudioMute) {
		WriteSeqIndexPort(ROW1+3,tySRAM_CODE_CC_CD,"  Mute On  ",11);
	}
	else {
		WriteSeqIndexPort(ROW1+3,tySRAM_CODE_CC_CD,"  Mute Off ",11);
	}
	Osd_On(0);
	OsdTimer = 200;
}
//----------------------
void ShowMonSel()
{
	
	WriteIIC563(0x090,0x00);  // zooming off
	ClearOSD();
	WriteWordIIC563(0x081,(PanelWidth-30*12));
	WriteWordIIC563(0x084,(PanelHeight-5*18));
	WriteWordIIC563(0x0cc,SOURCE_COLOR);
	if(MonTogg == 1) {
		WriteSeqIndexPort(ROW1+3,tySRAM_CODE_CC_CD,"  Monitor B",11);
	}
	else {
		WriteSeqIndexPort(ROW1+3,tySRAM_CODE_CC_CD,"  Monitor A",11);
	}
	Osd_On(0);
	OsdTimer = 200;

}
// ----------------------------- +jwshin 060908
void ShowRGB_A()
{
	WriteIIC563(0x090,0x00);  // zooming off
	ClearOSD();
	WriteWordIIC563(0x081,(PanelWidth-30*12));
	WriteWordIIC563(0x084,(PanelHeight-5*18));
	WriteWordIIC563(0x0cc,SOURCE_COLOR);
	WriteSeqIndexPort(ROW1+3,tySRAM_CODE_CC_CD,"  RGB A",7);
	Osd_On(0);
	OsdTimer = 200;
}

void ShowRGB_B()
{
	WriteIIC563(0x090,0x00);  // zooming off
	ClearOSD();
	WriteWordIIC563(0x081,(PanelWidth-30*12));
	WriteWordIIC563(0x084,(PanelHeight-5*18));
	WriteWordIIC563(0x0cc,SOURCE_COLOR);
	WriteSeqIndexPort(ROW1+3,tySRAM_CODE_CC_CD,"  RGB B",7);
	Osd_On(0);
	OsdTimer = 200;
}
//----------------------------------
void ShowVersion()
{
	Byte VaSeq[5];
	WriteWordIIC563(0x0cc,VERSION_COLOR);
	BCD(Year,VaSeq,4);
	WriteSeqIndexPort(VERSION_ADDR-1,tySRAM_CODE_CC_CD,VaSeq+1,4);
	WriteIndexPort(VERSION_ADDR+3,tySRAM_CODE_CC_CD,'/');
	BCD(Month,VaSeq,2);
	WriteSeqIndexPort(VERSION_ADDR+4,tySRAM_CODE_CC_CD,VaSeq+3,2);
	WriteIndexPort(VERSION_ADDR+6,tySRAM_CODE_CC_CD,'/');
	BCD(Date,VaSeq,2);
	WriteSeqIndexPort(VERSION_ADDR+7,tySRAM_CODE_CC_CD,VaSeq+3,2);

	WriteSeqIndexPort(VERSION_ADDR+12,tySRAM_CODE_CC_CD,ModelName,8);
	WriteIndexPort(VERSION_ADDR+21,tySRAM_CODE_CC_CD,'V');
	BCD(Version,VaSeq,1);
	WriteIndexPort(VERSION_ADDR+22,tySRAM_CODE_CC_CD,VaSeq[4]);
	WriteIndexPort(VERSION_ADDR+23,tySRAM_CODE_CC_CD,'.');
	BCD(Reversion,VaSeq,2);
	WriteSeqIndexPort(VERSION_ADDR+24,tySRAM_CODE_CC_CD,VaSeq+3,2);

/*	
	WriteIndexPort(VERSION_ADDR+10,tySRAM_CODE_CC_CD,'V');
	BCD(Version,VaSeq,1);
	WriteIndexPort(VERSION_ADDR+11,tySRAM_CODE_CC_CD,VaSeq[4]);
	WriteIndexPort(VERSION_ADDR+12,tySRAM_CODE_CC_CD,'.');
	BCD(Reversion,VaSeq,2);
	WriteSeqIndexPort(VERSION_ADDR+13,tySRAM_CODE_CC_CD,VaSeq+3,2);
	WriteSeqIndexPort(VERSION_ADDR+16,tySRAM_CODE_CC_CD,ModelName,11);
*/
	//WriteSeqIndexPort(VERSION_ADDR+16,tySRAM_CODE_CC_CD,"Build:",6);
	//BCD(Build,VaSeq,3);
	//WriteSeqIndexPort(VERSION_ADDR+22,tySRAM_CODE_CC_CD,VaSeq+1,4);

}

void ShowBurnInPattern(bit Init)
{
	unsigned char temp;
	
	VideoMute = 1;
	if(Init)
		{
		Osd_Off();
		ForceToBackground(0,0,0);
		BurnInPattern = 0;
		BurnInTimer = 0;
		//FastMuteOff();
		BackLightOn();
		}
	if(BurnInPattern > 4)
		BurnInPattern = 0;
	BurnInTimer = BURN_IN_TIME;
	temp = ReadIIC563(0x159) & 0xc0;
	if(BurnInPattern == 0){
		WriteIIC563(0x154,0x09);
		//temp = temp | BurnInPattern;
	}
	else{
		WriteIIC563(0x154,0xb1);
		temp = temp | ((BurnInPattern-1) & 0x07);
	}
	WriteIIC563(0x159,temp);	//RGB
	BurnInPattern++;
}
	
void ShowOSDFrame(Byte Type)
{
	Byte code LeftLine[]={
		0x00,0x08,0x08,0x03,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x0e,0x0d,0x09
	};
	Byte code RightLine[]={
		0x02,0x08,0x08,0x05,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x07,0x0c,0x0b
	};
	Byte code LeftLine2[]={
		0x00,0x08,0x08,0x0e,0x0d,0x09
	};
	Byte code RightLine2[]={
		0x02,0x08,0x08,0x07,0x0c,0x0b
	};
	Byte code LeftLine3[]={
		0x00,0x08,0x08,0x08,0x09
	};
	Byte code RightLine3[]={
		0x02,0x08,0x08,0x08,0x0b
	};
	Byte code Line0[]={
		0x01
	};
	Byte code Line3[]={
		0x04
	};
	Byte code Line12[]={
		0x06
	};
	Byte code Line14[]={
		0x0a
	};
	
	Byte i,End;
	Word Attr;
	
	Attr = OFFSET_2BIT<<8;
	WriteWordIIC563(0x0cc,Attr|caTWO_BIT);
	for(i=1; i<30; i++){
		WriteIndexPort(ROW0+i,tySRAM_CODE_CC_CD,Line0[0]);
		if(Type == 0)
			WriteIndexPort(ROW3+i,tySRAM_CODE_CC_CD,Line3[0]);
		if(Type != 2){
			if(Type == 0)
				WriteIndexPort(ROW12+i,tySRAM_CODE_CC_CD,Line12[0]);
			else
				WriteIndexPort(ROW3+i,tySRAM_CODE_CC_CD,Line12[0]);
		}
	}

	if(Type == 2){
		WriteSeqIndexPort(9,tySRAM_2BIT,TwoBitFont2,3*54);
		WriteSeqIndexPort(0x100,tySRAM_1BIT,OneBitIcon+45*27,6*27);
		//Attr = (OFFSET_2BIT+4)<<8;
		//WriteWordIIC563(0x0cc,Attr|caTWO_BIT);
	}
	else{
		WriteSeqIndexPort(9,tySRAM_2BIT,TwoBitFont+9*54,3*54);
		WriteSeqIndexPort(0x100,tySRAM_1BIT,OneBitIcon,6*27);
	}
	for(i=1; i<30; i++){
		if(Type == 0)
			WriteIndexPort(ROW14+i,tySRAM_CODE_CC_CD,Line14[0]);
		else if(Type == 1)
			WriteIndexPort(ROW5+i,tySRAM_CODE_CC_CD,Line14[0]);
		else
			WriteIndexPort(ROW4+i,tySRAM_CODE_CC_CD,Line14[0]);
	}
	
	switch(Type)
		{
		case 0:
			End = 15;
			break;
		case 1:
			End = 6;
			break;
		case 2:
			End = 5;
			break;
		};
	for(i=0; i<End; i++){
		if(Type == 0){
			WriteIndexPort(OSD_WIDTH*i,tySRAM_CODE_CC_CD,LeftLine[i]);
			WriteIndexPort(OSD_WIDTH*i+(OSD_WIDTH-1),tySRAM_CODE_CC_CD,RightLine[i]);
		}
		else if(Type == 1){
			WriteIndexPort(OSD_WIDTH*i,tySRAM_CODE_CC_CD,LeftLine2[i]);
			WriteIndexPort(OSD_WIDTH*i+(OSD_WIDTH-1),tySRAM_CODE_CC_CD,RightLine2[i]);
		}
		else{
			WriteIndexPort(OSD_WIDTH*i,tySRAM_CODE_CC_CD,LeftLine3[i]);
			WriteIndexPort(OSD_WIDTH*i+(OSD_WIDTH-1),tySRAM_CODE_CC_CD,RightLine3[i]);
		}
	}

	WriteWordIIC563(0x0cc,Attr|0x0110);
	if(Type == 0)
		WriteSeqIndexPort(ROW13+1,tySRAM_CODE_CC_CD,SPACE,OSD_WIDTH-2);
	else if(Type == 1)
		WriteSeqIndexPort(ROW4+1,tySRAM_CODE_CC_CD,SPACE,OSD_WIDTH-2);

	
/*	
	Byte code Line1[]={
		0x00,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,
		0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x02
	};
	Byte code LeftLine[]={
		0x08 //0x03
	};
	Byte code RightLine[]={
		0x08,0x08,0x05,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x07,0x0c
	};
	Byte code RightLine2[]={
		0x08,0x08,0x07,0x0c
	};
	Byte code Line2[]={
		0x04
	};
	Byte code Line3[]={
		0x06
	};
	Byte code Line4[]={
		0x09,0x0a,0x0a,0x0a,0x0a,0x0a,0x0a,0x0a,0x0a,0x0a,0x0a,0x0a,0x0a,0x0a,0x0a,0x0a,
		0x0a,0x0a,0x0a,0x0a,0x0a,0x0a,0x0a,0x0a,0x0a,0x0a,0x0a,0x0a,0x0a,0x0b
	};
	
	Byte i,End;
	Word Attr;
	
	Attr = OFFSET_2BIT<<8;
	WriteWordIIC563(0x0cc,Attr|caTWO_BIT);
	WriteSeqIndexPort(ROW0,tySRAM_CODE_CC_CD,Line1,30);
	switch(Type)
		{
		case 0:
			End = 14;
			break;
		case 1:
			End = 5;
			break;
		};
	for(i=1; i<End; i++){
		WriteIndexPort(OSD_WIDTH*i,tySRAM_CODE_CC_CD,LeftLine[0]);
		if(Type == 0)
			WriteIndexPort((OSD_WIDTH*(i+1))-1,tySRAM_CODE_CC_CD,RightLine[i-1]);
		else if(Type == 1)
			WriteIndexPort((OSD_WIDTH*(i+1))-1,tySRAM_CODE_CC_CD,RightLine2[i-1]);
	}
	for(i=1; i<29; i++){
		if(Type == 0)
			WriteIndexPort(ROW3+i,tySRAM_CODE_CC_CD,Line2[0]);
		if(Type != 2){
			if(Type == 0)
				WriteIndexPort(ROW12+i,tySRAM_CODE_CC_CD,Line3[0]);
			else
				WriteIndexPort(ROW3+i,tySRAM_CODE_CC_CD,Line3[0]);
		}
	}
	if(Type == 0)
		WriteSeqIndexPort(ROW14,tySRAM_CODE_CC_CD,Line4,30);
	else if(Type == 1)
		WriteSeqIndexPort(ROW5,tySRAM_CODE_CC_CD,Line4,30);
	WriteWordIIC563(0x0cc,Attr|0x0110);
	if(Type == 0)
		WriteSeqIndexPort(ROW13+1,tySRAM_CODE_CC_CD,SPACE,28);
	else if(Type == 1)
		WriteSeqIndexPort(ROW4+1,tySRAM_CODE_CC_CD,SPACE,28);
*/
}

// 0x100 ...0x17f ==> TV channel fine tune,PR. NO. TV CH.
// 0x180 ...0x1ff ==> CATV channel fine tune,PR. NO. CATV CH.
// 0x280 ... 0x28f ==>TV channel mask(ADD/DEL),PR. NO. TV channel mask
// 0x290 ... 0x29f ==>CATV channel mask(ADD/DEL),PR. NO. CATV channel mask

void ShowFineTune(void)
{
	unsigned char i;
	Word temp;
	if((ChSystem==CH_USA)||(ChSystem==CH_JPN))
		i = Read24C16(0x209); // ch No
	else	{
		i = Read24C16(0x207);//PR Channel No
		if((Read24C16(ep_Input_CH_Sys) &0x80) == 0)
			i = Read24C16(0x100+(i - 1));//PR TV CH NO.
		else		i = Read24C16(0x180+(i - 1));//PR CATV CH NO.
	}

	if((Read24C16(ep_Input_CH_Sys) &0x80) == 0){
		i = i - TV_Min;
		FuncBuf[pCHFINETUNE] = Read24C16(0x100+i);	
	}
	else{
		i = i - CATV_Min;
		FuncBuf[pCHFINETUNE] = Read24C16(0x180+i);
	}	

	if(MenuPtr.Ptr == 2)
		temp = BAR_COLOR;
	else 
		temp = FUN_COLOR;

	ShowBar(MAINMENU_BAR_ADDR+(OSD_WIDTH*2),temp,0,100,FuncBuf[pCHFINETUNE]);
	ShowValue(MAINMENU_VALUE_ADDR+(OSD_WIDTH*2),temp,FuncBuf[pCHFINETUNE]);
}




void ShowSubMenu(Byte Page, Byte Ptr)
{
	Byte i,j,FuncPtrTemp;
	Word Attr;

	//ClearTextArea();
	//ShowKeyMenu(Page,MenuPtr.Level);
	FuncPtrTemp = FuncPtr;
	if(Page == 0){
		for(i=0; i<7; i++){
			if(Ptr==i && MenuPtr.Level == 1 )
				Attr = SEL_FUN_COLOR;
			else
				Attr = FUN_COLOR;
			if(FuncBuf[pVIDEOSOURCE]==cANALOG)
				FuncPtr = Page0Item[i];
			else if(FuncBuf[pVIDEOSOURCE]==cDVI)
				FuncPtr = Page0ItemD[i];
			else if(FuncBuf[pVIDEOSOURCE]==cYPbPr)
				FuncPtr = Page0ItemY[i];
			else
				FuncPtr = Page0ItemV[i];
			ShowDesc(FuncPtr,MAINMENU_DESC_ADDR+(OSD_WIDTH*i),Attr);
			switch(FuncPtr)
			{
				case pSHARPNESS:
					GetFuncRange(FuncPtr);
					if(FuncBuf[pVIDEOSOURCE] < cSVIDEO)
						ShowSharpness();
					else{
						ShowBar(MAINMENU_BAR_ADDR+(OSD_WIDTH*i),Attr,FuncMin,FuncMax,FuncBuf[FuncPtr]);
						ShowValue(MAINMENU_VALUE_ADDR+(OSD_WIDTH*i),Attr,FuncBuf[FuncPtr]);
					}
					break;
				default:
					GetFuncRange(FuncPtr);
					ShowBar(MAINMENU_BAR_ADDR+(OSD_WIDTH*i),Attr,FuncMin,FuncMax,FuncBuf[FuncPtr]);
					ShowValue(MAINMENU_VALUE_ADDR+(OSD_WIDTH*i),Attr,FuncBuf[FuncPtr]);
					break;
			};

			if(FuncBuf[pVIDEOSOURCE] == cDVI && i == 2)
				i = 7;
			else if(FuncBuf[pVIDEOSOURCE] >= cYPbPr && i == 4)	// +jwshin 061009
				i = 7;
		}
	}
	if(Page == 1){
		for(i=0; i<4; i++){
//		for(i=0; i<2; i++){

		
			if(Ptr==i && MenuPtr.Level == 1 )
				Attr = SEL_FUN_COLOR;
			else
				Attr = FUN_COLOR;
			FuncPtr = Page1Item[i];
			ShowDesc_Sound(i,MAINMENU_DESC_ADDR+(OSD_WIDTH*i),Attr);
//			ShowDesc(FuncPtr,MAINMENU_DESC_ADDR+(OSD_WIDTH*i),Attr);
			switch(FuncPtr)
				{
				case pMUTE:
					ShowOnOff(AudioMute);
					break;
				default:
					GetFuncRange(FuncPtr);
					ShowBar(MAINMENU_BAR_ADDR+(OSD_WIDTH*i),Attr,FuncMin,FuncMax,FuncBuf[FuncPtr]);
					ShowValue(MAINMENU_VALUE_ADDR+(OSD_WIDTH*i),Attr,FuncBuf[FuncPtr]);
//					printf("FuncBuf[FuncPtr]=%d\r\n",(unsigned short)FuncBuf[FuncPtr]);

					break;
				};
			}
	}

	if(Page == 2){
		if(FuncBuf[pVIDEOSOURCE]==cTV){
//			printf("Ptr=%d,MenuPtr.Level=%d\r\n",(Word)Ptr,(Word)MenuPtr.Level);

			ShowTVMenu();
			for(i=0; i<4; i++){
				if(Ptr==i && MenuPtr.Level == 1 )
					Attr = SEL_FUN_COLOR;
				else
					Attr = FUN_COLOR;
	
					FuncPtr = Page7Item[i];
				ShowDesc_TV(i,MAINMENU_DESC_ADDR+(OSD_WIDTH*i),Attr);
				switch(FuncPtr)
				{
					case pCHSEARCH:
						ShowOnOff(0);
						break;
					case pCHEDIT:
						ChAdd_Del = CheckChMask();
						ShowAddDel(ChAdd_Del);
						break;
					case pCHFINETUNE:
						GetFuncRange(FuncPtr);
						ShowFineTune();
						break;	
					case pINPUT:
						if((Read24C16(ep_Input_CH_Sys) & 0x80) == 0) j =0;
						else j = 1;
//						printf("j=%d\r\n",(Word)j);
						ShowTV_Input(j);
//						if(MenuPtr.Level == 2 )
						break;
				};
			}

		}
		else{
			for(i=0; i<7; i++){
				if(Ptr==i && MenuPtr.Level == 1 )
					Attr = SEL_FUN_COLOR;
				else
					Attr = FUN_COLOR;
	
					FuncPtr = Page2Item[i];
//				ShowDesc(FuncPtr,MAINMENU_DESC_ADDR+(OSD_WIDTH*i),Attr);
				switch(FuncPtr)
				{
					case pCOLORTEMP:
						ShowColorMenu();
						break;
					case pRCOLOR:
					case pGCOLOR:
					case pBCOLOR:
//						if(MenuPtr.Level == 2 )
						ShowUserRGBMenu();
						break;
					default:
						GetFuncRange(FuncPtr);
						ShowBar(MAINMENU_BAR_ADDR+(OSD_WIDTH*i),Attr,FuncMin,FuncMax,FuncBuf[FuncPtr]);
						ShowValue(MAINMENU_VALUE_ADDR+(OSD_WIDTH*i),Attr,FuncBuf[FuncPtr]);
						break;
				};
			}
		}
	}
	if(Page == 3){
			ShowLanguage();
	}
	if(Page == 4){
		if(FuncBuf[pVIDEOSOURCE] > cYPbPr){	
		for(i=0; i<5; i++){	// for(i=0; i<7; i++){	// +jwshin 050729
			if(Ptr==i && MenuPtr.Level == 1 )
				Attr = SEL_FUN_COLOR;
			else
				Attr = FUN_COLOR;
			
			FuncPtr = Page4ItemTV[i];
			ShowDesc(FuncPtr,MAINMENU_DESC_ADDR+(OSD_WIDTH*i),Attr);
			switch(FuncPtr)
				{
				case pRECALL:
					ShowYesNo(0);
					break;
				case pAUTOSETTING:
					ShowOnOff(AutoSetting);
					break;
				case pOSDHPOSITION:
					GetFuncRange(FuncPtr);
					ShowOSDPosition();
					break;
				case pSCALERMODE:
//					ShowScalerMode(ScalerMode);
					break;
/*				case pCAPTION:				// -jwshin 050729
					CaptionFlag= Read24C16(0x7f0);
					ShowOnOff(CaptionFlag);
					break; */
				default:
					GetFuncRange(FuncPtr);
					ShowBar(MAINMENU_BAR_ADDR+(OSD_WIDTH*i),Attr,FuncMin,FuncMax,FuncBuf[FuncPtr]);
					ShowValue(MAINMENU_VALUE_ADDR+(OSD_WIDTH*i),Attr,FuncBuf[FuncPtr]);
					break;
				}
			}
			}
			else{
			for(i=0; i<5; i++){		// +jwshin 050729
			if(Ptr==i && MenuPtr.Level == 1 )
				Attr = SEL_FUN_COLOR;
			else
				Attr = FUN_COLOR;
					FuncPtr = Page4Item[i];
			if((FuncPtr==pSCALERMODE)&&(!(ResolutionPtr == 4 ||(ResolutionPtr >= 6 && ResolutionPtr < 13)))){
					Attr=TextUnable;
			}
			ShowDesc(FuncPtr,MAINMENU_DESC_ADDR+(OSD_WIDTH*i),Attr);
			switch(FuncPtr)
				{
				case pRECALL:
					ShowYesNo(0);
					break;
				case pAUTOSETTING:
					ShowOnOff(AutoSetting);
					break;
				case pOSDHPOSITION:
					GetFuncRange(FuncPtr);
					ShowOSDPosition();
					break;
				case pSCALERMODE:
//					ShowScalerMode(ScalerMode);
					break;
				default:
					GetFuncRange(FuncPtr);
					ShowBar(MAINMENU_BAR_ADDR+(OSD_WIDTH*i),Attr,FuncMin,FuncMax,FuncBuf[FuncPtr]);
					ShowValue(MAINMENU_VALUE_ADDR+(OSD_WIDTH*i),Attr,FuncBuf[FuncPtr]);
					break;
				};
				}
				}
		}
	if(Page == 5){
		ShowSyncMode();
	}
	if(Page == 6){
		for(i=0; i<7; i++){
			if(Ptr==i && MenuPtr.Level == 1 )
				Attr = SEL_FUN_COLOR;
			else
				Attr = FUN_COLOR;
			FuncPtr = Page6Item[i];
			ShowDesc(FuncPtr,MAINMENU_DESC_ADDR+(OSD_WIDTH*i),Attr);
			switch(FuncPtr)
			{
				case pLIGHTEN:
					ShowOnOff(LightEn);
					break;
				default:
					GetFuncRange(FuncPtr);
					ShowBar(MAINMENU_BAR_ADDR+(OSD_WIDTH*i),Attr,FuncMin,FuncMax,FuncBuf[FuncPtr]);
					ShowValue(MAINMENU_VALUE_ADDR+(OSD_WIDTH*i),Attr,FuncBuf[FuncPtr]);
					break;
			};

		}
	}

	ShowStatus(ROW11+2,fGREEN|bBLACK);
	
	FuncPtr = FuncPtrTemp;
	
}

void ShowStatus(Word Addr,Word Attr)
{
code unsigned char IPSourceIcon[][2]={
	//0x30,0x31,
	//0x32,0x33,
		12,13,
		14,15,
};
code unsigned char AudioStatusIcon[][2]={
	//0x34,0x35,
	//0x36,0x37,
		16,17,
		18,19,
};
code unsigned char ColorStatusIcon[][2]={
	//0x3c,0x3d,
	//0x3a,0x3b,
	//0x38,0x39,
	//0x40,0x41,
		24,25,
		22,23,
		20,21,
		28,29,
};

//unsigned char i;

	WriteWordIIC563(0x0cc,Attr|caONE_BIT_512);
	if(FuncBuf[pVIDEOSOURCE]==cANALOG)
		WriteSeqIndexPort(Addr,tySRAM_CODE_CC_CD,IPSourceIcon[0],2);
	else if(FuncBuf[pVIDEOSOURCE]==cDVI)
		WriteSeqIndexPort(Addr,tySRAM_CODE_CC_CD,IPSourceIcon[1],2);

	WriteSeqIndexPort(Addr+2,tySRAM_CODE_CC_CD,ColorStatusIcon[FuncBuf[pCOLORTEMP]],2);
	if(AudioMute)
		WriteSeqIndexPort(Addr+4,tySRAM_CODE_CC_CD,AudioStatusIcon[0],2);
	else
		WriteSeqIndexPort(Addr+4,tySRAM_CODE_CC_CD,AudioStatusIcon[1],2);

}
void ShowOnOff(Byte Ptr)
{

code unsigned char ENG_ON[]={
	2,"On"
};
code unsigned char FRA_ON[]={
	2,"On"
};
code unsigned char DEU_ON[]={
	3,"Ein"
};
code unsigned char ESP_ON[]={
	4,"Act."
};
code unsigned char ITA_ON[]={
	2,"On"
};
code unsigned char JAP_ON[]={
	2,"ON"
};
code unsigned char RSU_ON[]={
	4,_B,_P00,_P19,_DOT
};
code unsigned char CHT_ON[]={
	1,_C55
};
code unsigned char CHI_ON[]={
	1,_C1f
};

code unsigned char ENG_OFF[]={
	3,"Off"
};
code unsigned char FRA_OFF[]={
	3,"Off"
};
code unsigned char DEU_OFF[]={
	3,"Aus"
};
code unsigned char ESP_OFF[]={
	6,"Desac."
};
code unsigned char ITA_OFF[]={
	3,"Off"
};
code unsigned char JAP_OFF[]={
	3,"OFF"
};
code unsigned char RSU_OFF[]={
	5,_B,_P1a,_P00,_P19,_DOT
};
code unsigned char CHT_OFF[]={
	1,_C56
};
code unsigned char CHI_OFF[]={
	1,_C40
};

code unsigned char *OnOffTab[][9]={
	{ENG_OFF,FRA_OFF,DEU_OFF,ESP_OFF,ITA_OFF,JAP_OFF,RSU_OFF,CHT_OFF,CHI_OFF},
	{ENG_ON,FRA_ON,DEU_ON,ESP_ON,ITA_ON,JAP_ON,RSU_ON,CHT_ON,CHI_ON}
};
	Byte i;
	Word code OnOffAddr[]={ROW5+17,ROW5+24};
	Word code CaptionModeAddr[]={ROW10+17,ROW10+24}; //Jason Choi
	Word code OnOffAddr2[]={ROW7+17,ROW7+24};
	Word code OnOffAddr3[]={ROW4+17,ROW4+24};
	Byte *Offset,Length;

	
	for(i=0;i<2;i++)
	{
		Offset = OnOffTab[i][FuncBuf[pLANGUAGE]];
		Length = *Offset;
		Offset++;
		if(Ptr == i)
			if(((FuncPtr == pMUTE && MenuPtr.Ptr == 1)||(FuncPtr == pAUTOSETTING && MenuPtr.Ptr == 3)||(FuncPtr == pCHSEARCH&& MenuPtr.Ptr == 0)||(FuncPtr == pCAPTION&&MenuPtr.Ptr == 6)) && MenuPtr.Level == 1)//||(pViolence_R<=FuncPtr>=pDialog_R)
				WriteWordIIC563(0x0cc,fMAGENTA|fBLACK);
			else
				WriteWordIIC563(0x0cc,fGREEN|fBLACK);
		else
			WriteWordIIC563(0x0cc,fWHITE|fBLACK);
		if(FuncPtr == pMUTE || FuncPtr == pVOLUME)
			WriteSeqIndexPort(OnOffAddr[i],tySRAM_CODE_CC_CD,Offset,Length);
		else if(FuncPtr == pAUTOSETTING)
			WriteSeqIndexPort(OnOffAddr2[i],tySRAM_CODE_CC_CD,Offset,Length);
		else if((FuncPtr == pLIGHTEN)||(FuncPtr == pCHSEARCH))
			WriteSeqIndexPort(OnOffAddr3[i],tySRAM_CODE_CC_CD,Offset,Length);
		else if(FuncPtr == pCAPTION)
			WriteSeqIndexPort(CaptionModeAddr[i],tySRAM_CODE_CC_CD,Offset,Length);
	}
}

void ShowTV_Input(unsigned char Ptr)
{
	Byte i;
	Word code TV_INPUT_Addr[]={ROW7+17,ROW7+24};
	Byte *Offset,Length;

code unsigned char ENG_AIR[]={
	3,"Air"
};
code unsigned char ENG_CABLE[]={
	5,"Cable"
};
code unsigned char *TV_INPUT_Tab[2]={
	ENG_AIR,ENG_CABLE
};
//printf("ShowTV_Input\r\n");
	for(i=0;i<2;i++)
	{
		Offset = TV_INPUT_Tab[i];
		Length = *Offset;
		Offset++;
		if(Ptr == i)
			if(MenuPtr.Ptr == 3)
				WriteWordIIC563(0x0cc,fMAGENTA|fBLACK);
			else
				WriteWordIIC563(0x0cc,fGREEN|fBLACK);
		else
			WriteWordIIC563(0x0cc,fWHITE|fBLACK);
		if(FuncPtr == pINPUT)
			WriteSeqIndexPort(TV_INPUT_Addr[i],tySRAM_CODE_CC_CD,Offset,Length);
	}
}

void ShowAddDel(unsigned char Ptr)
{
	Byte i;
	Word code AddDelAddr[]={ROW5+17,ROW5+24};
	Byte *Offset;

code unsigned char ENG_ADD[]={
	"Add"
};
code unsigned char ENG_DEL[]={
	"Del"
};
code unsigned char *AddDelTab[2]={
	ENG_DEL,ENG_ADD
};
//printf("ShowAddDel\r\n");
	for(i=0;i<2;i++)
	{
		Offset = AddDelTab[i];
		if(Ptr == i)
			if(MenuPtr.Ptr == 1)
				WriteWordIIC563(0x0cc,fMAGENTA|fBLACK);
			else
				WriteWordIIC563(0x0cc,fGREEN|fBLACK);
		else
			WriteWordIIC563(0x0cc,fWHITE|fBLACK);
		if(FuncPtr == pCHEDIT)
			WriteSeqIndexPort(AddDelAddr[i],tySRAM_CODE_CC_CD,Offset,3);
	}
}

void ShowUserRGBMenu()
{
	Byte *Offset,i,Length;
	Word RColor,GColor,BColor;
	Word code RGBAddr[3]={ROW8+6,ROW9+6,ROW10+6};

	for(i=4;i<7;i++)
		{
		if((i == (MenuPtr.Ptr)) && (MenuPtr.Level == 2))
			WriteWordIIC563(0x0cc,fMAGENTA|fBLACK);
		else			
			WriteWordIIC563(0x0cc,fWHITE|fBLACK);
		Offset = Tab_RGB[FuncBuf[pLANGUAGE]*3+(i-4)];
		Length = *Offset;
		Offset++;
		WriteSeqIndexPort(RGBAddr[i-4],tySRAM_CODE_CC_CD,Offset,Length);
		}
	//Show user pRCOLOR,pGCOLOR,pBCOLOR
	if(MenuPtr.Ptr < 4){
		RColor = Read24C16(ep_Color4_R);
		GColor = Read24C16(ep_Color4_G);
		BColor = Read24C16(ep_Color4_B);
	}
	else{
		RColor = FuncBuf[pRCOLOR];
		GColor = FuncBuf[pGCOLOR];
		BColor = FuncBuf[pBCOLOR];
	}
	GetFuncRange(pRCOLOR);
	if(MenuPtr.Level == 2){	//change set color on user color
		if(MenuPtr.Ptr == 4){
			ShowBar(RGBAddr[0]+10,fMAGENTA|fBLACK,FuncMin,FuncMax,RColor);
			ShowValue(RGBAddr[0]+19,fMAGENTA|fBLACK,RColor);		
			ShowBar(RGBAddr[1]+10,fWHITE|fBLACK,FuncMin,FuncMax,GColor);
			ShowValue(RGBAddr[1]+19,fWHITE|fBLACK,GColor);
			ShowBar(RGBAddr[2]+10,fWHITE|fBLACK,FuncMin,FuncMax,BColor);
			ShowValue(RGBAddr[2]+19,fWHITE|fBLACK,BColor);
		}
		if(MenuPtr.Ptr == 5){
			ShowBar(RGBAddr[0]+10,fWHITE|fBLACK,FuncMin,FuncMax,RColor);
			ShowValue(RGBAddr[0]+19,fWHITE|fBLACK,RColor);
			ShowBar(RGBAddr[1]+10,fMAGENTA|fBLACK,FuncMin,FuncMax,GColor);
			ShowValue(RGBAddr[1]+19,fMAGENTA|fBLACK,GColor);
			ShowBar(RGBAddr[2]+10,fWHITE|fBLACK,FuncMin,FuncMax,BColor);
			ShowValue(RGBAddr[2]+19,fWHITE|fBLACK,BColor);
		}
		if(MenuPtr.Ptr == 6){
			ShowBar(RGBAddr[0]+10,fWHITE|fBLACK,FuncMin,FuncMax,RColor);
			ShowValue(RGBAddr[0]+19,fWHITE|fBLACK,RColor);
			ShowBar(RGBAddr[1]+10,fWHITE|fBLACK,FuncMin,FuncMax,GColor);
			ShowValue(RGBAddr[1]+19,fWHITE|fBLACK,GColor);
			ShowBar(RGBAddr[2]+10,fMAGENTA|fBLACK,FuncMin,FuncMax,BColor);
			ShowValue(RGBAddr[2]+19,fMAGENTA|fBLACK,BColor);
		}
		//ShowKeyMenu(2,MenuPtr.Level);
	}
	else{		//the user set white char on color temp 
		ShowBar(RGBAddr[0]+10,fWHITE|fBLACK,FuncMin,FuncMax,RColor);
		ShowValue(RGBAddr[0]+19,fWHITE|fBLACK,RColor);
		ShowBar(RGBAddr[1]+10,fWHITE|fBLACK,FuncMin,FuncMax,GColor);
		ShowValue(RGBAddr[1]+19,fWHITE|fBLACK,GColor);
		ShowBar(RGBAddr[2]+10,fWHITE|fBLACK,FuncMin,FuncMax,BColor);
		ShowValue(RGBAddr[2]+19,fWHITE|fBLACK,BColor);
	}
//	ShowBar(RGBAddr[0]+10,fWHITE|fBLACK,FuncMin,FuncMax,RColor);
//	ShowBar(RGBAddr[1]+10,fWHITE|fBLACK,FuncMin,FuncMax,GColor);
//	ShowBar(RGBAddr[2]+10,fWHITE|fBLACK,FuncMin,FuncMax,BColor);
//	ShowValue(RGBAddr[0]+19,fWHITE|fBLACK,RColor);
//	ShowValue(RGBAddr[1]+19,fWHITE|fBLACK,GColor);
//	ShowValue(RGBAddr[2]+19,fWHITE|fBLACK,BColor);
		

	//ShowKeyMenu(2,MenuPtr.Level);

}

void ShowKeyMenu(Byte Page, Byte Level)
{
	Byte *Offset,Length;
	Byte code IncDecIcon[3]={
	//0x42,0x43,0x44
	30,31,32
	};
	Byte code MenuIcon[3]={
	//0x45,0x46,0x47
	33,34,35
	};
//	Byte code KeyStr[][6]={"Enter ","Select","Adjust"};

	WriteWordIIC563(0x0cc,fBLACK|bGRAY);
	if((MenuPtr.Menu == 3)||(MenuPtr.Menu == 6)) {
		WriteSeqIndexPort(ROW4+1,tySRAM_CODE_CC_CD,SPACE,28);
	}
	else {
		WriteSeqIndexPort(ROW13+1,tySRAM_CODE_CC_CD,SPACE,28);
	}
	
	WriteWordIIC563(0x0cc,fBLACK|bGRAY|caONE_BIT_512);

	if((MenuPtr.Menu == 3)||(MenuPtr.Menu == 6)){
		WriteSeqIndexPort(ROW4+1,tySRAM_CODE_CC_CD,MenuIcon,3);
		WriteSeqIndexPort(ROW4+15,tySRAM_CODE_CC_CD,IncDecIcon,3);
	}
 	else{
		WriteSeqIndexPort(ROW13+1,tySRAM_CODE_CC_CD,MenuIcon,3);
		if((Level == 0) ||(Level == 2)||(Page != 2 && Page != 3)||((Page == 2 && FuncBuf[pCOLORTEMP] == 3) ))
			WriteSeqIndexPort(ROW13+15,tySRAM_CODE_CC_CD,IncDecIcon,3);
//		else 
//			if(Page != 2 && Page != 3)
//				WriteSeqIndexPort(ROW13+18,tySRAM_CODE_CC_CD,IncDecIcon,3);
//			else if((Page == 2 && FuncBuf[pCOLORTEMP] == 3) && (Page != 3))
//				WriteSeqIndexPort(ROW13+18,tySRAM_CODE_CC_CD,IncDecIcon,3);
	}
	WriteWordIIC563(0x0cc,fBLACK|bGRAY);
	if(MenuPtr.Menu == 3){
		Offset = KeyStrTab[FuncBuf[pLANGUAGE]*3+2];
		Length = *Offset++;
		if(MenuPtr.Ptr == 0 ){
			ShowDesc(pCONTRAST,ROW4+4,fBLACK|bGRAY);
			//WriteSeqIndexPort(ROW4+21,tySRAM_CODE_CC_CD,KeyStr[2],6);
		}
		else if(MenuPtr.Ptr == 1 ){
			ShowDesc(pBACKLIGHT,ROW4+4,fBLACK|bGRAY);
			//WriteSeqIndexPort(ROW4+21,tySRAM_CODE_CC_CD,KeyStr[2],6);
		}
		WriteSeqIndexPort(ROW4+18,tySRAM_CODE_CC_CD,Offset,Length);
	}		
//------------------------	
	else if(MenuPtr.Menu == 6) {			// +jwshin 050802
		Offset = KeyStrTab[FuncBuf[pLANGUAGE]*3+2];
		Length = *Offset++;
		ShowDesc(pVOLUME,ROW4+4,fBLACK|bGRAY);
		WriteSeqIndexPort(ROW4+18,tySRAM_CODE_CC_CD,Offset,Length);
	}
//------------------------	
	else
	{
		if(Level == 0 )
		{
			Offset = KeyStrTab[FuncBuf[pLANGUAGE]*3];
			Length = *Offset++;
			WriteSeqIndexPort(ROW13+4,tySRAM_CODE_CC_CD,Offset,Length);
			//WriteSeqIndexPort(ROW13+4,tySRAM_CODE_CC_CD,KeyStr[0],6);
			Offset = KeyStrTab[FuncBuf[pLANGUAGE]*3+1];
			Length = *Offset++;
			WriteSeqIndexPort(ROW13+18,tySRAM_CODE_CC_CD,Offset,Length);
			//WriteSeqIndexPort(ROW13+18,tySRAM_CODE_CC_CD,KeyStr[1],6);
		}
		else if(Level == 1)
		{
			if((Page == 0) || (Page == 1) || (Page == 4) || (Page == 6)){
				Offset = KeyStrTab[FuncBuf[pLANGUAGE]*3+1];
				Length = *Offset++;
				WriteSeqIndexPort(ROW13+4,tySRAM_CODE_CC_CD,Offset,Length);
				Offset = KeyStrTab[FuncBuf[pLANGUAGE]*3+2];
				Length = *Offset++;
				WriteSeqIndexPort(ROW13+18,tySRAM_CODE_CC_CD,Offset,Length);
			}
			else if(Page == 5){
				Offset = KeyStrTab[FuncBuf[pLANGUAGE]*3+1];
				Length = *Offset++;
				WriteSeqIndexPort(ROW13+4,tySRAM_CODE_CC_CD,Offset,Length);
				Offset = KeyStrTab[FuncBuf[pLANGUAGE]*3];
				Length = *Offset++;
				WriteSeqIndexPort(ROW13+18,tySRAM_CODE_CC_CD,Offset,Length);
			}
			else{
				Offset = KeyStrTab[FuncBuf[pLANGUAGE]*3+1];
				Length = *Offset++;
				WriteSeqIndexPort(ROW13+4,tySRAM_CODE_CC_CD,Offset,Length);
				if(Page == 2 && FuncBuf[pCOLORTEMP] == 3){
					Offset = KeyStrTab[FuncBuf[pLANGUAGE]*3];
					Length = *Offset++;
					WriteSeqIndexPort(ROW13+18,tySRAM_CODE_CC_CD,Offset,Length);
				}
			}
		}
		else
		{
			Offset = KeyStrTab[FuncBuf[pLANGUAGE]*3+1];
			Length = *Offset++;
			WriteSeqIndexPort(ROW13+4,tySRAM_CODE_CC_CD,Offset,Length);
			Offset = KeyStrTab[FuncBuf[pLANGUAGE]*3+2];
			Length = *Offset++;
			WriteSeqIndexPort(ROW13+18,tySRAM_CODE_CC_CD,Offset,Length);
		}
	}
}

void ShowOSDPosition()
{
code unsigned char OSDPos1Str[]={
	1,"1"
};
code unsigned char OSDPos2Str[]={
	1,"2"
};
code unsigned char OSDPos3Str[]={
	1,"3"
};
code unsigned char OSDPos4Str[]={
	1,"4"
};
code unsigned char OSDPos5Str[]={
	1,"5"
};
	Byte code *OSDPosTab[]={
	OSDPos1Str,OSDPos2Str,OSDPos3Str,OSDPos4Str,OSDPos5Str
};

	Word code OSDPosAddr[5]={ROW5+17,ROW5+19,ROW5+21,ROW5+23,ROW5+25};
	Byte *Offset,i,Length;

	for(i=0;i<5;i++)
		{
		if(FuncBuf[pOSDHPOSITION] == i)
			if(MenuPtr.Ptr == 1 && MenuPtr.Level == 1)
				WriteWordIIC563(0x0cc,fMAGENTA|fBLACK);
			else
				WriteWordIIC563(0x0cc,fGREEN|fBLACK);
		else			
			WriteWordIIC563(0x0cc,fWHITE|fBLACK);
		Offset = OSDPosTab[i];
		Length = *Offset;
		Offset++;
		WriteSeqIndexPort(OSDPosAddr[i],tySRAM_CODE_CC_CD,Offset,Length);
		}
}
void ShowBrightnessMenu()
{
	WriteIIC563(0x080,0); // OSD disable
	ClearOSD();
	WriteIIC563(0x090,0x00);  // zooming off
	ShowOSDFrame(1);
	OsdPosition();
	OpenWindow(WINDOW4,WIN4_X1,WIN4_X2,WIN4_Y1,WIN4_Y2-9,WIN4_ATTR,WIN4_COLOR);
	OpenWindow(WINDOW3,WIN3_X1,WIN3_X2,WIN3_Y1,WIN3_Y2,WIN3_ATTR,WIN3_COLOR);
	if(FuncBuf[pVIDEOSOURCE] < cSVIDEO){
		//ShowResolution(HOTKEYMENU_RES_ADDR,RES_COLOR);
		ShowStatus(ROW2+2,fGREEN|bBLACK);
	}
	//else
	//	ShowTvSystem();
	ShowKeyMenu(0,MenuPtr.Level);
	
	FuncPtr = Page0Item[MenuPtr.Ptr];
	ShowDesc(FuncPtr,HOTKEYMENU_DESC_ADDR,SEL_FUN_COLOR);
	GetFuncRange(FuncPtr);
	ShowBar(HOTKEYMENU_BAR_ADDR,SEL_FUN_COLOR,FuncMin,FuncMax,FuncBuf[FuncPtr]);
	ShowValue(HOTKEYMENU_VALUE_ADDR,SEL_FUN_COLOR,FuncBuf[FuncPtr]);
}
void ShowSharpness()
{
code unsigned char Sharp1Str[]={
	1,"1"
};
code unsigned char  Sharp2Str[]={
	1,"2"
};
code unsigned char  Sharp3Str[]={
	1,"3"
};
code unsigned char  Sharp4Str[]={
	1,"4"
};
code unsigned char  Sharp5Str[]={
	1,"5"
};
	Byte code * SharpTab[]={
	 Sharp1Str, Sharp2Str, Sharp3Str, Sharp4Str, Sharp5Str
};

	Word code  SharpAddr[5]={17,19,21,23,25};
	//Word code  SharpAddr_D[5]={ROW6+17,ROW6+19,ROW6+21,ROW6+23,ROW6+25};
	//Word code  SharpAddr_V[5]={ROW8+17,ROW8+19,ROW8+21,ROW8+23,ROW8+25};
	Byte *Offset,i,Length;

	for(i=0;i<5;i++)
	{
		if(FuncBuf[pSHARPNESS] == i)
			if((MenuPtr.Ptr == 6 && MenuPtr.Level == 1)||
				(SyncMode == 3 && MenuPtr.Ptr == 2 && MenuPtr.Level == 1)||
				(FuncBuf[pVIDEOSOURCE]>cYPbPr&& MenuPtr.Ptr == 4 && MenuPtr.Level == 1))
				WriteWordIIC563(0x0cc,fMAGENTA|fBLACK);
			else
				WriteWordIIC563(0x0cc,fGREEN|fBLACK);
		else
			WriteWordIIC563(0x0cc,fWHITE|fBLACK);
			
		Offset = SharpTab[i];
		Length = *Offset;
		Offset++;
		if(FuncBuf[pVIDEOSOURCE]==cANALOG)//for DVI = 0
			WriteSeqIndexPort( ROW10+SharpAddr[i],tySRAM_CODE_CC_CD,Offset,Length);
		else if(FuncBuf[pVIDEOSOURCE]==cDVI)
			WriteSeqIndexPort( ROW6+SharpAddr[i],tySRAM_CODE_CC_CD,Offset,Length);
		else if(FuncBuf[pVIDEOSOURCE]==cYPbPr)
			WriteSeqIndexPort( ROW8+SharpAddr[i],tySRAM_CODE_CC_CD,Offset,Length);
		else
			WriteSeqIndexPort( ROW8+SharpAddr[i],tySRAM_CODE_CC_CD,Offset,Length);
	}
}

void ShowTurboModeMenu()
{
	Byte i;
	//Byte *Offset,Length;

	WriteIIC563(0x080,0); // OSD disable
	ClearOSD();
	WriteIIC563(0x090,0x00);  // zooming off
	ShowOSDFrame(2);
//	OsdPosition();
	WriteWordIIC563(0x081,460);
	WriteWordIIC563(0x084,467);
	OpenWindow(WINDOW4,WIN4_X1,WIN4_X2,WIN4_Y1,WIN4_Y2-8,WIN4_ATTR,WIN4_COLOR);
	OpenWindow(WINDOW3,WIN3_X1,WIN3_X2,WIN3_Y1,WIN3_Y2,WIN3_ATTR,WIN3_COLOR);

	WriteWordIIC563(0x0cc,fMAGENTA|caONE_BIT_512);
	for(i=0;i<3;i++){
		WriteIndexPort(ROW1+3+i,tySRAM_CODE_CC_CD,i);
		WriteIndexPort(ROW2+3+i,tySRAM_CODE_CC_CD,3+i);
	}
	ShowTurboMode();
	ShowStatus(ROW3+2,fGREEN|bBLACK);
}

void ShowTurboMode()
{
	Byte *Offset,Length;
	Word temp;

	
	//show description
	WriteWordIIC563(0x0cc,fWHITE|bBLACK);
	WriteSeqIndexPort(ROW2+8,tySRAM_CODE_CC_CD,SPACE,20);
	
	if(!TextMode && !EconomyMode)
		temp = FuncBuf[pLANGUAGE]*3+0;
		//Offset = TurboStrTab[FuncBuf[pLANGUAGE]*3+0];
	else if(TextMode && !EconomyMode)
		temp = FuncBuf[pLANGUAGE]*3+1;
		//Offset = TurboStrTab[FuncBuf[pLANGUAGE]*3+1];
	else
		temp = FuncBuf[pLANGUAGE]*3+2;
		//Offset = TurboStrTab[FuncBuf[pLANGUAGE]*3+2];
	Offset = TurboStrTab[temp];
	Length = *Offset++;
	WriteSeqIndexPort(ROW2+7,tySRAM_CODE_CC_CD,Offset,Length);
}

void ShowBackLightTime()
{
	Byte VaSeq[5],Minute,Second;
	unsigned long Hour;

	Second = (Byte)(BackLightTimer % 60);
	Minute = (Byte) ((BackLightTimer / 60) % 60);
	//Hour = BackLightTimer / 3600;
	
	WriteWordIIC563(0x0cc,fGREEN|bBLACK);
	Hour = BackLightTimer /3600 / 10000;
	BCD(Hour,VaSeq,5);
	WriteSeqIndexPort(BACKLIGHTTIME_ADDR,tySRAM_CODE_CC_CD,VaSeq+4,1);
	Hour = (BackLightTimer /3600) % 10000;
	BCD(Hour,VaSeq,5);
	WriteSeqIndexPort(BACKLIGHTTIME_ADDR+1,tySRAM_CODE_CC_CD,VaSeq+1,4);
	WriteIndexPort(BACKLIGHTTIME_ADDR+5,tySRAM_CODE_CC_CD,':');
	BCD(Minute,VaSeq,2);
	WriteSeqIndexPort(BACKLIGHTTIME_ADDR+6,tySRAM_CODE_CC_CD,VaSeq+3,2);

	WriteSeqIndexPort(BACKLIGHTTIME_ADDR-4,tySRAM_CODE_CC_CD,"B/L",3);
	//WriteIndexPort(BACKLIGHTTIME_ADDR-4,tySRAM_CODE_CC_CD,'B');
	//WriteIndexPort(BACKLIGHTTIME_ADDR-3,tySRAM_CODE_CC_CD,OSD_index_general+11);//"/"
	//WriteIndexPort(BACKLIGHTTIME_ADDR-2,tySRAM_CODE_CC_CD,'L');
#if 0	
	WriteIndexPort(ACKLIGHTTIME_ADDR+7,tySRAM_CODE_CC_CD,':');
	BCD(Second,VaSeq,2);
	WriteSeqIndexPort(ACKLIGHTTIME_ADDR+8,tySRAM_CODE_CC_CD,VaSeq+3,2);
	Hour = BackLightTimer / 10000;
	BCD(Hour,VaSeq,5);
	WriteSeqIndexPort(ROW1+19,tySRAM_CODE_CC_CD,VaSeq,5);
	Hour = BackLightTimer % 10000;
	BCD(Hour,VaSeq,4);
	WriteSeqIndexPort(ROW1+24,tySRAM_CODE_CC_CD,VaSeq+1,4);
#endif	
}

void ShowScalerMode(Byte Ptr)
{
code unsigned char ENG_43[]={
	3,"4:3"
};
code unsigned char ENG_54[]={
	3,"5:4"
};


code unsigned char *ScalerModeTab[]={
	ENG_43,ENG_54,
};
	Byte i;
	Word code ScalerModeAddr[]={ROW9+17,ROW9+24};
	Byte *Offset,Length;

//	if(!(ResolutionPtr == 4 ||(ResolutionPtr >= 6 && ResolutionPtr < 13))) Ptr = 1; // make 5:4 °­Á¦ÀûÀ¸·Î 
	
	for(i=0;i<2;i++)
	{
		Offset = ScalerModeTab[i];
		Length = *Offset;
		Offset++;
		if(Ptr == i)
			if(((FuncPtr == pSCALERMODE && MenuPtr.Ptr == 5)) && MenuPtr.Level == 1)
				WriteWordIIC563(0x0cc,fMAGENTA|fBLACK);
			else
				WriteWordIIC563(0x0cc,fGREEN|fBLACK);
		else{
			if(ResolutionPtr == 4 ||(ResolutionPtr >= 6 && ResolutionPtr < 13))
				WriteWordIIC563(0x0cc,fWHITE|fBLACK);
			else
				WriteWordIIC563(0x0cc,TextUnable);

		}
		WriteSeqIndexPort(ScalerModeAddr[i],tySRAM_CODE_CC_CD,Offset,Length);
	}
}

void DisplaySource(unsigned char i)
	//Souce Select½Ã sourceÇ¥½Ã 
	
{
//	Byte VaSeq[5];
//	printf("DisplaySource\r\n");
//	OSD_Type = oCHANNEL;
	ClearOSD();
	WriteWordIIC563(0x081,OSD3_Px);
	WriteWordIIC563(0x084,0);
	OpenWindow(WINDOW1,0,29,0,4,atWIN_TRANSLUCENT,ChannelColor);

//		ShowDesc(pVIDEOSOURCE,ROW1+10,clGREEN|bBLACK);
//	ShowDesc(pVIDEOSOURCE,ROW0,clGREEN);
	WriteIIC563(0x090,0x03);  // OSD zooming on
	WriteIIC563(0x095,0xFF); // OSD Font Zoowing On
	WriteIIC563(0xC2,0x1); // 0 Row Border enable 
	WriteWordIIC563(0xcc,ChannelColor);
	
	if(i==cANALOG){  //pc
		WriteSeqIndexPort(ROW0+2,tySRAM_CODE_CC_CD,"  Analog",8);
		}
	else if(i==cDVI){//PC-dvi
		WriteSeqIndexPort(ROW0+2,tySRAM_CODE_CC_CD,"     DVI",8);
		}
	else if(i==cYPbPr){//YPbPr
		WriteSeqIndexPort(ROW0+2,tySRAM_CODE_CC_CD,"   YPbPr",8);
		}
	else if(i==cSVIDEO){//S-Video 
		WriteSeqIndexPort(ROW0+1,tySRAM_CODE_CC_CD,"  S-Video",9);
		}
	else if(i==cCOMPOSIT){ //video
		WriteSeqIndexPort(ROW0+2,tySRAM_CODE_CC_CD,"   Video",8);
		}
	else if(i==cTV){ //TV
		ShowSource_Video(); //TV Select½Ã TV Channel º¸¿©ÁÜ
//		printf("ChBuffer=%d from h\r\n",(unsigned short)ChBuffer);
		FuncPtr = pVIDEOSOURCE;
		ShowValue(ROW0+7, ChannelColor, ChBuffer);
		}
	
	
	Osd_On(enOSD); //OSD ON
	OsdTimer = 500;
	OSDZoomFlag = 1;

//	printf("OsdTimer=%d\r\n",(unsigned short)OsdTimer);
//	WriteIIC563(0x090,0x00);  // zooming on
	}

void ShowSource_Video(void)
{
//	Byte VaSeq[5];
	ClearOSD();
	WriteWordIIC563(0xcc,ChannelColor);
	if((Read24C16(0x208) & 0x80) == 0)
		WriteSeqIndexPort(ROW0+3,tySRAM_CODE_CC_CD,"  CH",4);
	else		 
		WriteSeqIndexPort(ROW0+3,tySRAM_CODE_CC_CD,"CATV",4);
}

void DisplayCaption(unsigned char i) //EEPROM¿¡ ¹Ù·Î ÀúÀå 
{
	if(i==0){
		if(i!=Read24C16(0x7f0)){
		Write24C16(0x7f0,0x00);}
		Z86229_Init();
		}
	else if(i==1){
		if(i!=Read24C16(0x7f0)){
		Write24C16(0x7f0,0x01);}
		Z86229_Init();
		}
}
/*
void InitEDID_Save(void)
{
	Byte xdata *DDCptr;
	Byte i;
	DDC_CTL0 = 0;		//disable DDC
	DDC_CTL1 = 0;		//disable DDC
	DDCptr = 0xf800;  
	for(i=0;i<128;i++)
		{
		CLRWDT = 0x55;
		*DDCptr++ = DVI_EDID[i];
		}
	DDC_CTL0 = (EN_DDC|CLR_UPD|CLR_PTR);	
	DDC_CTL1 = (EN_DDC|CLR_UPD|CLR_PTR);	
	SaveDDCData(0);

}
*/

void	ChannelMove(unsigned char No)
{
	if(IR_Number_cnt == 1){
			IR_Number = No;
			WriteWordIIC563(0x081,OSD3_Px);
			WriteWordIIC563(0x084,0);
			OpenWindow(WINDOW1,0,29,0,4,atWIN_TRANSLUCENT,ChannelColor);

			WriteIIC563(0x090,0x03);  // OSD zooming on
			WriteIIC563(0x095,0xFF); // OSD Font Zoowing On
			WriteIIC563(0xC2,0x1); // 0 Row Border enable 
			WriteWordIIC563(0xcc,ChannelColor);
	}
	else{
			IR_Number = IR_Number * 10;
			IR_Number += No;
	}
		
	if((Read24C16(ep_Input_CH_Sys) & 0x80)!= 0) { // cable
		if(IR_Number <CATV_Max){
			if(IR_Number_cnt ==3) {
				ForceToBackground(0,0,0);
				WriteWordIIC563(0xcc,ChannelColor);
				ShowSource_Video();
				ChBuffer = IR_Number;
				FuncPtr = pVIDEOSOURCE;
				ShowValue(ROW0+7,ChannelColor,ChBuffer);
				ChannelSel(ChBuffer);
				Write24C16(0x209,ChBuffer);
				Sleep(100);
				SetDisplayNormal_Video();
				OsdTimer = 500;
				Osd_On(enOSD); //OSD ON
			}
			else{
				ShowDigital(IR_Number,1);
				Osd_On(enOSD); //OSD ON
			}
		}
		else {
			IR_Number_cnt = 0;
			Osd_Off();
		}
		if((IR_Number_cnt ==3)&&(IR_Number <CATV_Min)){
			IR_Number_cnt = 0;
			Osd_Off();
		}
	}
	else {	
		if(IR_Number <TV_Max){
			if(IR_Number_cnt ==2) {
				ForceToBackground(0,0,0);
				WriteWordIIC563(0xcc,ChannelColor);
				ShowSource_Video();
				ChBuffer = IR_Number;
				FuncPtr = pVIDEOSOURCE;
				ShowValue(ROW0+7,ChannelColor,ChBuffer);
				ChannelSel(ChBuffer);
				Write24C16(0x209,ChBuffer);
				Sleep(100);
				SetDisplayNormal_Video();
				OsdTimer= 500;
				Osd_On(enOSD); //OSD ON
			}
			else{
				ShowDigital(IR_Number,0);
				Osd_On(enOSD); //OSD ON
			}
		}
		else {
			IR_Number_cnt = 0;
			Osd_Off();
		}
		if((IR_Number_cnt ==2)&&(IR_Number <TV_Min)){
			IR_Number_cnt = 0;
			Osd_Off();
		}
	}
}
void ShowDigital(unsigned short value,unsigned char Cable)
{
unsigned char i,ch;
unsigned char buff[3];
//	sprintf(buff,"%3d",(unsigned short)value);
//show value
	CheckRegPage(0xe0);
	IIC_Start();
	IIC_Tx(SCALER_ADDR);
	IIC_Tx(0xe0);
	IIC_Tx(tySRAM_CODE_CC_CD&(~tyWITH_LANGTH));
	IIC_Tx((ROW0+7)&0x00ff);
	IIC_Tx((ROW0+7)>>8);
	if(Cable){ // cable
		if(value <10){
				if(IR_Number_cnt ==1){
					buff[0] = buff[2];
					buff[1] = '-';
					buff[2] = '-';
				}
				else if(IR_Number_cnt ==2){
					buff[0] = '0';
					buff[1] = buff[2];
					buff[2] = '-';
				}
				else if(IR_Number_cnt ==3){
					buff[0] = '0';
					buff[1] = '0';
					buff[2] =buff[2];
				}
		}
		else if(value <100){
				if(IR_Number_cnt ==2){
					buff[0] = buff[1];
					buff[1] = buff[2];
					buff[2] = '-';
				}
				else if(IR_Number_cnt == 3){
					buff[0] = '0';
					buff[1] = buff[1];
					buff[2] = buff[2];
				}
		}
		for(i=0; i<3; i++){
			ch = buff[i];
			IIC_Tx(ch);
		}
	}
	else{	// Air
		if(value <10){
				if(IR_Number_cnt ==1){
					buff[0] = buff[2];
					buff[1] = '-';
				}
				else{
					buff[0] = '0';
					buff[1] = buff[2];
				}
		}
		else if(value <100){
				buff[0] = buff[1];
				buff[1] = buff[2];
		}
		else return;
		for(i=0; i<2; i++){
			ch = buff[i];
			IIC_Tx(ch);
		}

	}
	IIC_Stop();

}

