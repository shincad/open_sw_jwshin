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

   2003-04-11 2:45오후 by thkim          Modified for Monitor-TV
****************************************************************************/

//****************************************************************//
//화일참조
//****************************************************************//
#include	"TopHeader.h"
#include "extern.h"

#if !defined(NoOsdMenu)
//------------------------------------------------------------------------------------------------------------------
#if	defined(BtcBoard_Option)
//------------------------------------------------------------------------------------------------------------------

#include	"btc_osdmenu.h"	//2003-04-17

#include	"TVMODE.h"
#include	"BTC_230OSDdef.h"
#include	"EEPROMadr.h"
#include	"power.h"

#include "TW990X.H"
#include "eepromadr.h"
#include "tuner.h"
#if defined(INT_EXTOSD)
#include	"internalosd.h"
#endif

#if		defined(MCU_MTV230)
#include	"MTV230xfr.h"
#elif		defined(MCU_MTV412)
#include	"MTV412xfr.h"
#elif		defined(MCU_NT68F63)
#include	"NT68F63.h"
#endif

#include "tuner.h"
#include "Sprocessor.h"

//****************************************************************//
//함수선언
//****************************************************************//
#if !defined(INT_EXTOSD)
void OSDWINDOW(BYTE *Recdata);
#else
void OSDWINDOW(BYTE *Recdata, BYTE INTor230);
#endif
void OSDWINDOW_OPTION(BYTE *Recdata);
void OSD230DatPtrSend(BYTE *Recdata2,BYTE Recdata3);
void OSD230PtrSend(BYTE Recdata0,BYTE Recdata1,BYTE *Recdata2,BYTE Recdata3);
void OSD230SeqSend(BYTE Recdata0,BYTE Recdata1,BYTE Recdata2,BYTE Recdata3);
void OSD230SeqSend2(BYTE Recdata0,BYTE Recdata1,BYTE Recdata2,BYTE Recdata3);//test
void I_OSDWINDOW(BYTE *ta);	//내부

BYTE calToChar(DWORD Recdata);
void OSD230DataSend(BYTE Recdata);
void OSD230RowSend(BYTE Recdata);
void OSD230ColSend(BYTE Recdata);
BYTE EEPROM_Read(WORD address);
void BitWriteScaler(BYTE address, BYTE BitArry, BYTE Recdata);
void ArrangeFunctionTable(void);
void Displaycusor(void);
//void DisplayBarandPercent(void);
void SetUpListFunction(void);
void Displaybar2(BYTE Recdata0,BYTE Recdata1,BYTE Recdata2,BYTE Recdata3,BYTE Recdata4);
void DisplayPercent(BYTE Recdata0,BYTE Recdata1,BYTE Recdata2,BYTE Recdata3,BYTE Recdata4);
void ProgEditCh_display(void);
void OsdService(void);

#ifdef	BtcBoard_Option
void 	PutVolumePWM();
void	osd_menu_on(void);
void	power_onoff(void);
void	updown_svc(void);
void	leftright_svc(void);
void 	DisplayInfo(BYTE count);	//2003-04-15
void 	Display_BottomCurrentInfo(void);	//2003-04-18
void 	IconSel(void);
void	Display_TopMenuIcon(void);
//void 	DisplayMenu(void);		//2003-04-21
void 	PutData(void);
void	Display_MenuDescription(void);
void 	Display_AdjustInfo(void);
void	Display_MenuBarPercent(void);
void 	MenuSel(void);
void 	OsdAttrClear(void);
void 	DisplayPercent2(BYTE RecMin,BYTE RecMax,BYTE Recdata,BYTE RecRow,BYTE RecCol,BYTE RecColor);
void 	DisplayMenuWindow(void);
void	Display_TvMenuDescription(void);

extern	void 	OSDMENU_FONT(BYTE *addr);	
//void	MiddleAlign(BYTE total, BYTE *Recdata);//2003-04-25   

extern	void OSD230DataSendHigh(BYTE Recdata);
extern	void OSD230Data2SendHigh(BYTE Recdata0,BYTE Recdata1);
extern	void	PipSourceSelService(void);
//extern	void	PipEnableService(void);
extern	void	PipSizeSelService(void);
extern	void	PipAspectSelService(void);
extern	void 	TvAspectRatioService(void);		//2003-08-04
//extern	void	Internal_OsdTableWrite(BYTE *Recdata);
extern	void	OsdTableWrite(BYTE Recdata);
extern	WORD MSP34xyDSPRead(unsigned char SubAddr,WORD RegAddr);
extern	BYTE TW990xRead(BYTE SubAddr);


void CatvAirSelection(bit Selection);
#endif

#ifdef test_function
void	MenuNum_display(void);//test
#endif

//OSD&system write/read interface function define!!

#ifdef	USE_4BitInterface	//=================================
										//4bit통신 함수선언
void	WriteReg4bit(BYTE address, BYTE Recdata);
#define	WriteScaler(val1,val2) WriteReg4bit(val1,val2)	
BYTE	ReadScalerParallel(BYTE address);
#define	ReadScaler	ReadScalerParallel
void WriteOsdAdr4bit(BYTE address);
void WriteOsdDat4bit(BYTE Recdata);
#define	OsdAdrSend(val)	WriteOsdAdr4bit(val)
#define	OsdDatSend(val)	WriteOsdDat4bit(val)

#else	//==========================================================//btc의 경우 undefined
										//1bit통신 함수선언
void	WriteReg1bit(BYTE address, BYTE Recdata);
#define	WriteScaler(val0, val1) WriteReg1bit(val0, val1)
BYTE	ReadScalerSerial(BYTE address);
#define	ReadScaler	ReadScalerSerial
void WriteOsdAdr1bit(BYTE Recdata);
void WriteOsdDat1bit(BYTE Recdata);
#define	OsdAdrSend(val)	WriteOsdAdr1bit(val)
#define	OsdDatSend(val) WriteOsdDat1bit(val)

#endif	//==========================================================


void EepromSetQue(WORD address, BYTE Recdata);
void SetADCGain(BYTE RecRED,BYTE RecGRN,BYTE RecBLU);
extern void SetADCBias(BYTE RecRED,BYTE RecGRN,BYTE RecBLU);	//Offset set, Bigger vales give less brightness @AD9883
void SetADCHtotal(WORD Recdata);
void SetADCPhaseReg(BYTE Recdata);
void WordWriteScaler(BYTE address, WORD Recdata);
bit WriteI2C(BYTE sysaddr, BYTE subaddr, BYTE writedata);

#if defined(VPC323x)
bit VPC323xFPWrite(WORD address,WORD Recdata);
WORD VPC323xBYTERead(BYTE address);
#endif



void DelayNOP20();
void DelayNOP10();		// Lcall is 4byte 4cycle

extern	void 	Osd_onoff(void);
extern	void OSDSeqSend(BYTE Row,BYTE Col,BYTE Data,BYTE Count);

extern bit	ThreeDigit;	//smpark 20030807
extern bit	RemAddBtn;

void ShowChannelStatus(unsigned char status);	// smpark 20030808
void ChannelOSD(BYTE HPos,  BYTE VPos );		// smpark 20030810

void TVChannelAdd(void);						// smpark 20030825
void MTSDisplay(void);						// smpark 20030825
void Recall(void);

//void  DisplayChannelStatus(BYTE CHStatus );
void MTSService(void);

//--------------------------------------------------------------------------------------------------

/*  for memory save 2003.6.5
BYTE GetMenuStart(BYTE mnum)
{
	if(mnum<=TopMenuEnd) 		return MENU_DISPLAY;
	if(mnum<=DisplayMenuEnd) 	return menu_brightness;
	if(mnum<=RgbMenuEnd) 		return menu_white_balance;
	if(mnum<=OsdMenuEnd) 		return menu_language;
	if(mnum<=PipMenuEnd) 		return menu_pip_enable;
	if(mnum<=ToolsMenuEnd) 		return menu_auto_adjust;                        
}       	                
*/
/*      TvToolsStart	
BYTE GetTvToolsEnd	MenuStart(void)
{
	if(MenuNum<=DisplayMenuEnd) 	return MenuNum= menu_brightness;
	if(MenuNum<=RgbMenuEnd) 	return MenuNum= menu_white_balance;
	if(MenuNum<=OsdMenuEnd) 	return MenuNum= menu_language;
	if(MenuNum<=PipMenuEnd) 	return MenuNum= menu_pip_enable;
	if(MenuNum<=ToolsMenuEnd) 	return MenuNum= menu_auto_adjust;
}*/
/*
BYTE GetMenuStart(void)
{
	if(MenuNum<=DisplayMenuEnd) 	return MenuNum= menu_brightness;
	if(MenuNum<=RgbMenuEnd) 	return MenuNum= menu_white_balance;
	if(MenuNum<=OsdMenuEnd) 	return MenuNum= menu_language;
	if(MenuNum<=PipMenuEnd) 	return MenuNum= menu_pip_enable;
	if(MenuNum<=ToolsMenuEnd) 	return MenuNum= menu_auto_adjust;
}
*/
BYTE GetMenuStart2(void)
{
	switch(MenuNum)
	{
		case MENU_DISPLAY:	return MenuNum= menu_brightness;   
		case MENU_RGB:    	return MenuNum= menu_white_balance;     
		case MENU_OSD:    	return MenuNum= menu_language;     
		case MENU_PIP:    	return MenuNum= menu_pip_enable;   
		case MENU_TOOLS:  	return MenuNum= menu_auto_adjust;
		case MENU_SOUND:	return MenuNum= menu_Treble;	// smpark 20030708
	}
}

/*  for memory save 2003.6.5
BYTE GetMenuEnd(void)
{
	if(MenuNum<=TopMenuEnd) 	return TopMenuEnd;              
	if(MenuNum<=DisplayMenuEnd) 	return DisplayMenuEnd;        
	if(MenuNum<=RgbMenuEnd) 	return RgbMenuEnd; 
	if(MenuNum<=OsdMenuEnd) 	return menu_osd_transparency; 
	if(MenuNum<=PipMenuEnd) 	return PipMenuEnd;    
	if(MenuNum<=ToolsMenuEnd) 	return ToolsMenuEnd;  
}
*/

BYTE GetTopMenu(void)
{
	if(MenuNum<=TopMenuEnd) 	return MenuNum;
	if(MenuNum<=DisplayMenuEnd) 	return MENU_DISPLAY;
	if(MenuNum<=RgbMenuEnd) 	return MENU_RGB;
	if(MenuNum<=OsdMenuEnd) 	return MENU_OSD;
	if(MenuNum<=PipMenuEnd) 	return MENU_PIP;
	if(MenuNum<=ToolsMenuEnd) 	return MENU_TOOLS;
	if(MenuNum<=SoundMenuEnd)	return MENU_SOUND;	//smpark 20030708
	
}

/*  for memory save 2003.6.5

BYTE GetSubMenu(void)
{
	switch(MenuNum)
	{
		case MENU_DISPLAY:	return menu_brightness;   
		case MENU_RGB:    	return menu_white_balance;
		case MENU_OSD:    	return menu_language;     
		case MENU_PIP:    	return menu_pip_enable;   
		case MENU_TOOLS:  	return menu_auto_adjust;
	}
		//default:
		return GetTopMenu();
}
*/

	
	
/*  for memory save 2003.6.5                
BYTE GetTvMenuStart(BYTE mnum)
{
	if(mnum<=TvTopMenuEnd) 		return TVMENU_PICTURE;
	if(mnum<=TvPictureEnd) 		return tvmenu_tint;                                                 
	if(mnum<=TvSetupEnd) 		return tvmenu_finetune;                                             
	if(mnum<=TvToolsEnd) 		return tvmenu_sleep;	                                        
}       	                
*/


BYTE GetTvMenuStart2(void)
{
	switch(TvMenuNum)
	{
		case TVMENU_PICTURE:    return TvMenuNum= tvmenu_brightness;
		case TVMENU_SETUP:    	return TvMenuNum= tvmenu_country;
		case TVMENU_TOOLS:    	return TvMenuNum= tvmenu_lang;//tvmenu_ttx;
		case TVMENU_SOUND:    	return TvMenuNum= tvmenu_Treble;
	}
}

/*  for memory save 2003.6.5
BYTE GetTvMenuEnd(void)
{  
	if(TvMenuNum<=TvTopMenuEnd) 	return TvTopMenuEnd;            
	if(TvMenuNum<=TvPictureEnd) 	return tvmenu_tint; 
	if(TvMenuNum<=TvSetupEnd) 	return tvmenu_finetune;
	if(TvMenuNum<=TvToolsEnd) 	return tvmenu_sleep;
}
*/


BYTE GetTvTopMenu(void)
{
	if(TvMenuNum<=TvTopMenuEnd) 	return TvMenuNum;
	if(TvMenuNum<=TvPictureEnd) 	return TVMENU_PICTURE; 
	if(TvMenuNum<=TvSetupEnd) 	return TVMENU_SETUP;
	if(TvMenuNum<=TvToolsEnd) 	return TVMENU_TOOLS;
	if(TvMenuNum<=TvSoundEnd) 	return TVMENU_SOUND;		// smpark 20030715
	
}
/*  for memory save 2003.6.5
BYTE GetTvSubMenu(void)
{
	switch(TvMenuNum)
	{
		case TVMENU_PICTURE:    return tvmenu_brightness;                                                 
		case TVMENU_SETUP:    	return tvmenu_country;                                             
		case TVMENU_TOOLS:    	return tvmenu_ttx;		
	}
		//default:
		return GetTvTopMenu();
}
                */
/* 
typedef struct {   
	BYTE ChEdit_CursorNum;
	BYTE ChEdit_ChNum;
	BYTE ChEdit_ChName[5];
	bit  ChEdit_SkipFlag;
} ChEdit_Info;
*/	 
//--------------------------------------------------------------------------------------------------
#if 0
typedef struct
{
	BYTE CursorWinROWSTART0;	//1
	BYTE CursorWinROWEND0;		//2
	BYTE CursorWinCOLSTART0;	//3
	BYTE CursorWinCOLEND0;		//4
	BYTE CursorWinColor0;		//5
	BYTE CursorAttROWSTART0;	//6
	BYTE CursorAttCOLSTART0;	//7
	BYTE CursorAttCOLEND0;		//8
	BYTE CursorAttColor0;		//9
	                                
	BYTE CursorWinROWSTART1;	//10
	BYTE CursorWinROWEND1;		//11
	BYTE CursorWinCOLSTART1;	//12
	BYTE CursorWinCOLEND1;  	//13
	BYTE CursorWinColor1;   	//14
	BYTE CursorAttROWSTART1;	//15
	BYTE CursorAttCOLSTART1;	//16
	BYTE CursorAttCOLEND1;  	//17
	BYTE CursorAttColor1;   	//18
}	CursorTable;


code CursorTable CursorList[]=
{
 {0,0,0,0,0,0,0,0,0,0,0,0}//0
 //analog main
,{WIN_SROW3,WIN_EROW3,WIN_COL0,WIN_COL25,OSD_BLUE,ATTR_ROW3,CII_COL0,30,OSD_WHITE, WIN_SROW3,WIN_EROW3,WIN_COL0,WIN_COL25,OSD_BLUE,ATTR_ROW3,CII_COL0,28,OSD_WHITE}
,{WIN_SROW3,WIN_EROW3,WIN_COL0,WIN_COL25,OSD_BLUE,ATTR_ROW3,CII_COL0,30,OSD_WHITE, WIN_SROW3,WIN_EROW3,WIN_COL0,WIN_COL25,OSD_BLUE,ATTR_ROW3,CII_COL0,28,OSD_WHITE}
,{WIN_SROW4,WIN_EROW4,WIN_COL0,WIN_COL25,OSD_BLUE,ATTR_ROW4,CII_COL0,30,OSD_WHITE, WIN_SROW4,WIN_EROW4,WIN_COL0,WIN_COL25,OSD_BLUE,ATTR_ROW4,CII_COL0,28,OSD_WHITE}
,{WIN_SROW5,WIN_EROW5,WIN_COL0,WIN_COL25,OSD_BLUE,ATTR_ROW5,CII_COL0,30,OSD_WHITE, WIN_SROW5,WIN_EROW5,WIN_COL0,WIN_COL25,OSD_BLUE,ATTR_ROW5,CII_COL0,28,OSD_WHITE}
,{WIN_SROW6,WIN_EROW6,WIN_COL0,WIN_COL25,OSD_BLUE,ATTR_ROW6,CII_COL0,30,OSD_WHITE, WIN_SROW6,WIN_EROW6,WIN_COL0,WIN_COL25,OSD_BLUE,ATTR_ROW6,CII_COL0,28,OSD_WHITE}

//analog bright/contrast sub
,{WIN_SROW2,WIN_EROW2,WIN_COL1,WIN_COL10,OSD_BLUE,ATTR_ROW2,CII_COL0,11,OSD_WHITE, WIN_SROW2,WIN_EROW2,WIN_COL1,WIN_COL22,OSD_BLUE,ATTR_ROW2,CII_COL0,28,OSD_WHITE}
,{WIN_SROW3,WIN_EROW3,WIN_COL1,WIN_COL10,OSD_BLUE,ATTR_ROW3,CII_COL0,11,OSD_WHITE, WIN_SROW3,WIN_EROW3,WIN_COL1,WIN_COL22,OSD_BLUE,ATTR_ROW3,CII_COL0,28,OSD_WHITE}
,{WIN_SROW4,WIN_EROW4,WIN_COL1,WIN_COL10,OSD_BLUE,ATTR_ROW4,CII_COL0,11,OSD_WHITE, WIN_SROW4,WIN_EROW4,WIN_COL1,WIN_COL22,OSD_BLUE,ATTR_ROW4,CII_COL0,28,OSD_WHITE}

//analog color sub
,{WIN_SROW2,WIN_EROW2,WIN_COL1,WIN_COL7,OSD_BLUE,ATTR_ROW2,CII_COL0,10,OSD_WHITE, WIN_SROW2,WIN_EROW2,WIN_COL1,WIN_COL7,OSD_BLUE,ATTR_ROW2,CII_COL0,10,OSD_WHITE}
,{WIN_SROW2,WIN_EROW2,WIN_COL11,WIN_COL17,OSD_BLUE,ATTR_ROW2,CII_COL11,10,OSD_WHITE, WIN_SROW2,WIN_EROW2,WIN_COL11,WIN_COL17,OSD_BLUE,ATTR_ROW2,CII_COL11,10,OSD_WHITE}
,{WIN_SROW3,WIN_EROW3,WIN_COL1,WIN_COL10,OSD_BLUE,ATTR_ROW3,CII_COL0,11,OSD_WHITE, WIN_SROW3,WIN_EROW3,WIN_COL1,WIN_COL22,OSD_BLUE,ATTR_ROW3,CII_COL0,28,OSD_WHITE}
,{WIN_SROW4,WIN_EROW4,WIN_COL1,WIN_COL10,OSD_BLUE,ATTR_ROW4,CII_COL0,11,OSD_WHITE, WIN_SROW4,WIN_EROW4,WIN_COL1,WIN_COL22,OSD_BLUE,ATTR_ROW4,CII_COL0,28,OSD_WHITE}
,{WIN_SROW5,WIN_EROW5,WIN_COL1,WIN_COL10,OSD_BLUE,ATTR_ROW5,CII_COL0,11,OSD_WHITE, WIN_SROW5,WIN_EROW5,WIN_COL1,WIN_COL22,OSD_BLUE,ATTR_ROW5,CII_COL0,28,OSD_WHITE}
,{WIN_SROW6,WIN_EROW6,WIN_COL1,WIN_COL10,OSD_BLUE,ATTR_ROW6,CII_COL0,11,OSD_WHITE, WIN_SROW6,WIN_EROW6,WIN_COL1,WIN_COL22,OSD_BLUE,ATTR_ROW6,CII_COL0,28,OSD_WHITE}

//analog position sub
,{WIN_SROW2,WIN_EROW2,WIN_COL1,WIN_COL10,OSD_BLUE,ATTR_ROW2,CII_COL0,11,OSD_WHITE, WIN_SROW2,WIN_EROW2,WIN_COL1,WIN_COL22,OSD_BLUE,ATTR_ROW2,CII_COL0,28,OSD_WHITE}
,{WIN_SROW3,WIN_EROW3,WIN_COL1,WIN_COL10,OSD_BLUE,ATTR_ROW3,CII_COL0,11,OSD_WHITE, WIN_SROW3,WIN_EROW3,WIN_COL1,WIN_COL22,OSD_BLUE,ATTR_ROW3,CII_COL0,28,OSD_WHITE}
,{WIN_SROW4,WIN_EROW4,WIN_COL1,WIN_COL10,OSD_BLUE,ATTR_ROW4,CII_COL0,11,OSD_WHITE, WIN_SROW4,WIN_EROW4,WIN_COL1,WIN_COL22,OSD_BLUE,ATTR_ROW4,CII_COL0,28,OSD_WHITE}
,{WIN_SROW5,WIN_EROW5,WIN_COL1,WIN_COL10,OSD_BLUE,ATTR_ROW5,CII_COL0,11,OSD_WHITE, WIN_SROW5,WIN_EROW5,WIN_COL1,WIN_COL22,OSD_BLUE,ATTR_ROW5,CII_COL0,28,OSD_WHITE}
,{WIN_SROW6,WIN_EROW6,WIN_COL1,WIN_COL10,OSD_BLUE,ATTR_ROW6,CII_COL0,11,OSD_WHITE, WIN_SROW6,WIN_EROW6,WIN_COL1,WIN_COL22,OSD_BLUE,ATTR_ROW6,CII_COL0,28,OSD_WHITE}
                                                                                   
//analog setup sub                                                                 
,{WIN_SROW2,WIN_EROW2,WIN_COL1,WIN_COL13,OSD_BLUE,ATTR_ROW2,CII_COL0,14,OSD_WHITE, WIN_SROW2,WIN_EROW2,WIN_COL1,WIN_COL22,OSD_BLUE,ATTR_ROW2,CII_COL0,28,OSD_WHITE}
,{WIN_SROW3,WIN_EROW3,WIN_COL1,WIN_COL13,OSD_BLUE,ATTR_ROW3,CII_COL0,14,OSD_WHITE, WIN_SROW3,WIN_EROW3,WIN_COL1,WIN_COL23,OSD_BLUE,ATTR_ROW3,CII_COL0,28,OSD_WHITE}
,{WIN_SROW4,WIN_EROW4,WIN_COL1,WIN_COL13,OSD_BLUE,ATTR_ROW4,CII_COL0,14,OSD_WHITE, WIN_SROW4,WIN_EROW4,WIN_COL1,WIN_COL22,OSD_BLUE,ATTR_ROW4,CII_COL0,28,OSD_WHITE}
,{WIN_SROW5,WIN_EROW5,WIN_COL1,WIN_COL13,OSD_BLUE,ATTR_ROW5,CII_COL0,14,OSD_WHITE, WIN_SROW5,WIN_EROW5,WIN_COL1,WIN_COL25,OSD_BLUE,ATTR_ROW5,CII_COL0,30,OSD_WHITE}
,{WIN_SROW6,WIN_EROW6,WIN_COL1,WIN_COL13,OSD_BLUE,ATTR_ROW6,CII_COL0,14,OSD_WHITE, WIN_SROW6,WIN_EROW6,WIN_COL1,WIN_COL22,OSD_BLUE,ATTR_ROW6,CII_COL0,28,OSD_WHITE}
                                                                                   
//Tuner main                                                                       
,{WIN_SROW2,WIN_EROW2,WIN_COL0,WIN_COL25,OSD_BLUE,ATTR_ROW2,CII_COL0,30,OSD_WHITE, WIN_SROW2,WIN_EROW2,WIN_COL0,WIN_COL25,OSD_BLUE,ATTR_ROW2,CII_COL0,28,OSD_WHITE}
,{WIN_SROW3,WIN_EROW3,WIN_COL0,WIN_COL25,OSD_BLUE,ATTR_ROW3,CII_COL0,30,OSD_WHITE, WIN_SROW3,WIN_EROW3,WIN_COL0,WIN_COL25,OSD_BLUE,ATTR_ROW3,CII_COL0,28,OSD_WHITE}
,{WIN_SROW4,WIN_EROW4,WIN_COL0,WIN_COL25,OSD_BLUE,ATTR_ROW4,CII_COL0,30,OSD_WHITE, WIN_SROW4,WIN_EROW4,WIN_COL0,WIN_COL25,OSD_BLUE,ATTR_ROW4,CII_COL0,28,OSD_WHITE}
,{WIN_SROW5,WIN_EROW5,WIN_COL0,WIN_COL25,OSD_BLUE,ATTR_ROW5,CII_COL0,30,OSD_WHITE, WIN_SROW5,WIN_EROW5,WIN_COL0,WIN_COL25,OSD_BLUE,ATTR_ROW5,CII_COL0,28,OSD_WHITE}
,{WIN_SROW6,WIN_EROW6,WIN_COL0,WIN_COL25,OSD_BLUE,ATTR_ROW6,CII_COL0,30,OSD_WHITE, WIN_SROW6,WIN_EROW6,WIN_COL0,WIN_COL25,OSD_BLUE,ATTR_ROW6,CII_COL0,28,OSD_WHITE}

//tuner bright/contrast sub
,{WIN_SROW2,WIN_EROW2,WIN_COL1,WIN_COL10,OSD_BLUE,ATTR_ROW2,CII_COL0,11,OSD_WHITE, WIN_SROW2,WIN_EROW2,WIN_COL1,WIN_COL22,OSD_BLUE,ATTR_ROW2,CII_COL0,28,OSD_WHITE}
,{WIN_SROW3,WIN_EROW3,WIN_COL1,WIN_COL10,OSD_BLUE,ATTR_ROW3,CII_COL0,11,OSD_WHITE, WIN_SROW3,WIN_EROW3,WIN_COL1,WIN_COL22,OSD_BLUE,ATTR_ROW3,CII_COL0,28,OSD_WHITE}
,{WIN_SROW4,WIN_EROW4,WIN_COL1,WIN_COL10,OSD_BLUE,ATTR_ROW4,CII_COL0,11,OSD_WHITE, WIN_SROW4,WIN_EROW4,WIN_COL1,WIN_COL22,OSD_BLUE,ATTR_ROW4,CII_COL0,28,OSD_WHITE}
                                                                                   
//tuner color sub                                                                  
,{WIN_SROW2,WIN_EROW2,WIN_COL1,WIN_COL10,OSD_BLUE,ATTR_ROW2,CII_COL0,11,OSD_WHITE, WIN_SROW2,WIN_EROW2,WIN_COL1,WIN_COL22,OSD_BLUE,ATTR_ROW2,CII_COL0,28,OSD_WHITE}
,{WIN_SROW3,WIN_EROW3,WIN_COL1,WIN_COL10,OSD_BLUE,ATTR_ROW3,CII_COL0,11,OSD_WHITE, WIN_SROW3,WIN_EROW3,WIN_COL1,WIN_COL22,OSD_BLUE,ATTR_ROW3,CII_COL0,28,OSD_WHITE}
,{WIN_SROW4,WIN_EROW4,WIN_COL1,WIN_COL10,OSD_BLUE,ATTR_ROW4,CII_COL0,11,OSD_WHITE, WIN_SROW4,WIN_EROW4,WIN_COL1,WIN_COL22,OSD_BLUE,ATTR_ROW4,CII_COL0,28,OSD_WHITE}
,{WIN_SROW5,WIN_EROW5,WIN_COL1,WIN_COL10,OSD_BLUE,ATTR_ROW5,CII_COL0,11,OSD_WHITE, WIN_SROW5,WIN_EROW5,WIN_COL1,WIN_COL22,OSD_BLUE,ATTR_ROW5,CII_COL0,28,OSD_WHITE}
                                                                                   
//tuner channel sub                                                                
,{WIN_SROW2,WIN_EROW2,WIN_COL1,WIN_COL14,OSD_BLUE,ATTR_ROW2,CII_COL0,15,OSD_WHITE, WIN_SROW2,WIN_EROW2,WIN_COL1,WIN_COL25,OSD_BLUE,ATTR_ROW2,CII_COL0,30,OSD_WHITE}
,{WIN_SROW3,WIN_EROW3,WIN_COL1,WIN_COL14,OSD_BLUE,ATTR_ROW3,CII_COL0,15,OSD_WHITE, WIN_SROW3,WIN_EROW3,WIN_COL1,WIN_COL25,OSD_BLUE,ATTR_ROW3,CII_COL0,30,OSD_WHITE}
,{WIN_SROW4,WIN_EROW4,WIN_COL1,WIN_COL14,OSD_BLUE,ATTR_ROW4,CII_COL0,15,OSD_WHITE, WIN_SROW4,WIN_EROW4,WIN_COL1,WIN_COL23,OSD_BLUE,ATTR_ROW4,CII_COL0,28,OSD_WHITE}
,{WIN_SROW4,WIN_EROW4,WIN_COL1,WIN_COL14,OSD_BLUE,ATTR_ROW4,CII_COL0,15,OSD_WHITE, WIN_SROW4,WIN_EROW4,WIN_COL1,WIN_COL23,OSD_BLUE,ATTR_ROW4,CII_COL0,28,OSD_WHITE}
,{WIN_SROW4,WIN_EROW4,WIN_COL1,WIN_COL14,OSD_BLUE,ATTR_ROW4,CII_COL0,15,OSD_WHITE, WIN_SROW4,WIN_EROW4,WIN_COL1,WIN_COL23,OSD_BLUE,ATTR_ROW4,CII_COL0,28,OSD_WHITE}
,{WIN_SROW5,WIN_EROW5,WIN_COL1,WIN_COL14,OSD_BLUE,ATTR_ROW5,CII_COL0,15,OSD_WHITE, WIN_SROW5,WIN_EROW5,WIN_COL1,WIN_COL23,OSD_BLUE,ATTR_ROW5,CII_COL0,28,OSD_WHITE}
,{WIN_SROW6,WIN_EROW6,WIN_COL1,WIN_COL14,OSD_BLUE,ATTR_ROW6,CII_COL0,15,OSD_WHITE, WIN_SROW6,WIN_EROW6,WIN_COL1,WIN_COL23,OSD_BLUE,ATTR_ROW6,CII_COL0,28,OSD_WHITE}
                                                                                   
//tuner setup sub                                                                  
,{WIN_SROW2,WIN_EROW2,WIN_COL1,WIN_COL13,OSD_BLUE,ATTR_ROW2,CII_COL0,14,OSD_WHITE, WIN_SROW2,WIN_EROW2,WIN_COL1,WIN_COL22,OSD_BLUE,ATTR_ROW2,CII_COL0,28,OSD_WHITE}
,{WIN_SROW3,WIN_EROW3,WIN_COL1,WIN_COL13,OSD_BLUE,ATTR_ROW3,CII_COL0,14,OSD_WHITE, WIN_SROW3,WIN_EROW3,WIN_COL1,WIN_COL23,OSD_BLUE,ATTR_ROW3,CII_COL0,28,OSD_WHITE}
,{WIN_SROW4,WIN_EROW4,WIN_COL1,WIN_COL13,OSD_BLUE,ATTR_ROW4,CII_COL0,14,OSD_WHITE, WIN_SROW4,WIN_EROW4,WIN_COL1,WIN_COL22,OSD_BLUE,ATTR_ROW4,CII_COL0,28,OSD_WHITE}
,{WIN_SROW5,WIN_EROW5,WIN_COL1,WIN_COL13,OSD_BLUE,ATTR_ROW5,CII_COL0,14,OSD_WHITE, WIN_SROW5,WIN_EROW5,WIN_COL1,WIN_COL25,OSD_BLUE,ATTR_ROW5,CII_COL0,30,OSD_WHITE}
,{WIN_SROW6,WIN_EROW6,WIN_COL1,WIN_COL13,OSD_BLUE,ATTR_ROW6,CII_COL0,14,OSD_WHITE, WIN_SROW6,WIN_EROW6,WIN_COL1,WIN_COL22,OSD_BLUE,ATTR_ROW6,CII_COL0,28,OSD_WHITE}
                                                                                   
 //digital main                                                                    
,{WIN_SROW2,WIN_EROW2,WIN_COL0,WIN_COL25,OSD_BLUE,ATTR_ROW2,CII_COL0,30,OSD_WHITE, WIN_SROW2,WIN_EROW2,WIN_COL0,WIN_COL25,OSD_BLUE,ATTR_ROW2,CII_COL0,28,OSD_WHITE}
,{WIN_SROW3,WIN_EROW3,WIN_COL0,WIN_COL25,OSD_BLUE,ATTR_ROW3,CII_COL0,30,OSD_WHITE, WIN_SROW3,WIN_EROW3,WIN_COL0,WIN_COL25,OSD_BLUE,ATTR_ROW3,CII_COL0,28,OSD_WHITE}
,{WIN_SROW4,WIN_EROW4,WIN_COL0,WIN_COL25,OSD_BLUE,ATTR_ROW4,CII_COL0,30,OSD_WHITE, WIN_SROW4,WIN_EROW4,WIN_COL0,WIN_COL25,OSD_BLUE,ATTR_ROW4,CII_COL0,28,OSD_WHITE}
,{WIN_SROW5,WIN_EROW5,WIN_COL0,WIN_COL25,OSD_BLUE,ATTR_ROW5,CII_COL0,30,OSD_WHITE, WIN_SROW5,WIN_EROW5,WIN_COL0,WIN_COL25,OSD_BLUE,ATTR_ROW5,CII_COL0,28,OSD_WHITE}
,{WIN_SROW6,WIN_EROW6,WIN_COL0,WIN_COL25,OSD_BLUE,ATTR_ROW6,CII_COL0,30,OSD_WHITE, WIN_SROW6,WIN_EROW6,WIN_COL0,WIN_COL25,OSD_BLUE,ATTR_ROW6,CII_COL0,28,OSD_WHITE}
                                                                                   
//digital bright/contrast sub                                                      
,{WIN_SROW2,WIN_EROW2,WIN_COL1,WIN_COL10,OSD_BLUE,ATTR_ROW2,CII_COL0,11,OSD_WHITE, WIN_SROW2,WIN_EROW2,WIN_COL1,WIN_COL22,OSD_BLUE,ATTR_ROW2,CII_COL0,28,OSD_WHITE}
,{WIN_SROW3,WIN_EROW3,WIN_COL1,WIN_COL10,OSD_BLUE,ATTR_ROW3,CII_COL0,11,OSD_WHITE, WIN_SROW3,WIN_EROW3,WIN_COL1,WIN_COL22,OSD_BLUE,ATTR_ROW3,CII_COL0,28,OSD_WHITE}
,{WIN_SROW4,WIN_EROW4,WIN_COL1,WIN_COL10,OSD_BLUE,ATTR_ROW4,CII_COL0,11,OSD_WHITE, WIN_SROW4,WIN_EROW4,WIN_COL1,WIN_COL22,OSD_BLUE,ATTR_ROW4,CII_COL0,28,OSD_WHITE}
                                                                                   
//digital setup sub                                                                
,{WIN_SROW2,WIN_EROW2,WIN_COL1,WIN_COL13,OSD_BLUE,ATTR_ROW2,CII_COL0,14,OSD_WHITE, WIN_SROW2,WIN_EROW2,WIN_COL1,WIN_COL22,OSD_BLUE,ATTR_ROW2,CII_COL0,28,OSD_WHITE}
,{WIN_SROW3,WIN_EROW3,WIN_COL1,WIN_COL13,OSD_BLUE,ATTR_ROW3,CII_COL0,14,OSD_WHITE, WIN_SROW3,WIN_EROW3,WIN_COL1,WIN_COL23,OSD_BLUE,ATTR_ROW3,CII_COL0,28,OSD_WHITE}
,{WIN_SROW4,WIN_EROW4,WIN_COL1,WIN_COL13,OSD_BLUE,ATTR_ROW4,CII_COL0,14,OSD_WHITE, WIN_SROW4,WIN_EROW4,WIN_COL1,WIN_COL22,OSD_BLUE,ATTR_ROW4,CII_COL0,28,OSD_WHITE}
,{WIN_SROW5,WIN_EROW5,WIN_COL1,WIN_COL13,OSD_BLUE,ATTR_ROW5,CII_COL0,14,OSD_WHITE, WIN_SROW5,WIN_EROW5,WIN_COL1,WIN_COL25,OSD_BLUE,ATTR_ROW5,CII_COL0,30,OSD_WHITE}
,{WIN_SROW6,WIN_EROW6,WIN_COL1,WIN_COL13,OSD_BLUE,ATTR_ROW6,CII_COL0,14,OSD_WHITE, WIN_SROW6,WIN_EROW6,WIN_COL1,WIN_COL22,OSD_BLUE,ATTR_ROW6,CII_COL0,28,OSD_WHITE}
                                                                                   
 //composite main                                                                  
,{WIN_SROW2,WIN_EROW2,WIN_COL0,WIN_COL25,OSD_BLUE,ATTR_ROW2,CII_COL0,30,OSD_WHITE, WIN_SROW2,WIN_EROW2,WIN_COL0,WIN_COL25,OSD_BLUE,ATTR_ROW2,CII_COL0,28,OSD_WHITE}
,{WIN_SROW3,WIN_EROW3,WIN_COL0,WIN_COL25,OSD_BLUE,ATTR_ROW3,CII_COL0,30,OSD_WHITE, WIN_SROW3,WIN_EROW3,WIN_COL0,WIN_COL25,OSD_BLUE,ATTR_ROW3,CII_COL0,28,OSD_WHITE}
,{WIN_SROW4,WIN_EROW4,WIN_COL0,WIN_COL25,OSD_BLUE,ATTR_ROW4,CII_COL0,30,OSD_WHITE, WIN_SROW4,WIN_EROW4,WIN_COL0,WIN_COL25,OSD_BLUE,ATTR_ROW4,CII_COL0,28,OSD_WHITE}
,{WIN_SROW5,WIN_EROW5,WIN_COL0,WIN_COL25,OSD_BLUE,ATTR_ROW5,CII_COL0,30,OSD_WHITE, WIN_SROW5,WIN_EROW5,WIN_COL0,WIN_COL25,OSD_BLUE,ATTR_ROW5,CII_COL0,28,OSD_WHITE}
,{WIN_SROW6,WIN_EROW6,WIN_COL0,WIN_COL25,OSD_BLUE,ATTR_ROW6,CII_COL0,30,OSD_WHITE, WIN_SROW6,WIN_EROW6,WIN_COL0,WIN_COL25,OSD_BLUE,ATTR_ROW6,CII_COL0,28,OSD_WHITE}
                                                                                   
//composite bright/contrast sub                                                    
,{WIN_SROW2,WIN_EROW2,WIN_COL1,WIN_COL10,OSD_BLUE,ATTR_ROW2,CII_COL0,11,OSD_WHITE, WIN_SROW2,WIN_EROW2,WIN_COL1,WIN_COL22,OSD_BLUE,ATTR_ROW2,CII_COL0,28,OSD_WHITE}
,{WIN_SROW3,WIN_EROW3,WIN_COL1,WIN_COL10,OSD_BLUE,ATTR_ROW3,CII_COL0,11,OSD_WHITE, WIN_SROW3,WIN_EROW3,WIN_COL1,WIN_COL22,OSD_BLUE,ATTR_ROW3,CII_COL0,28,OSD_WHITE}
,{WIN_SROW4,WIN_EROW4,WIN_COL1,WIN_COL10,OSD_BLUE,ATTR_ROW4,CII_COL0,11,OSD_WHITE, WIN_SROW4,WIN_EROW4,WIN_COL1,WIN_COL22,OSD_BLUE,ATTR_ROW4,CII_COL0,28,OSD_WHITE}
                                                                                   
//composite Color sub
,{WIN_SROW2,WIN_EROW2,WIN_COL1,WIN_COL9,OSD_BLUE,ATTR_ROW2,CII_COL0,10,OSD_WHITE, WIN_SROW2,WIN_EROW2,WIN_COL1,WIN_COL22,OSD_BLUE,ATTR_ROW2,CII_COL0,28,OSD_WHITE}
,{WIN_SROW3,WIN_EROW3,WIN_COL1,WIN_COL9,OSD_BLUE,ATTR_ROW3,CII_COL0,10,OSD_WHITE, WIN_SROW3,WIN_EROW3,WIN_COL1,WIN_COL22,OSD_BLUE,ATTR_ROW3,CII_COL0,28,OSD_WHITE}
,{WIN_SROW4,WIN_EROW4,WIN_COL1,WIN_COL9,OSD_BLUE,ATTR_ROW4,CII_COL0,10,OSD_WHITE, WIN_SROW4,WIN_EROW4,WIN_COL1,WIN_COL22,OSD_BLUE,ATTR_ROW4,CII_COL0,28,OSD_WHITE}
,{WIN_SROW5,WIN_EROW5,WIN_COL1,WIN_COL9,OSD_BLUE,ATTR_ROW5,CII_COL0,10,OSD_WHITE, WIN_SROW5,WIN_EROW5,WIN_COL1,WIN_COL22,OSD_BLUE,ATTR_ROW5,CII_COL0,28,OSD_WHITE}
                                                                                  
//composite setup sub                                                             
,{WIN_SROW2,WIN_EROW2,WIN_COL1,WIN_COL13,OSD_BLUE,ATTR_ROW2,CII_COL0,14,OSD_WHITE, WIN_SROW2,WIN_EROW2,WIN_COL1,WIN_COL22,OSD_BLUE,ATTR_ROW2,CII_COL0,28,OSD_WHITE}
,{WIN_SROW3,WIN_EROW3,WIN_COL1,WIN_COL13,OSD_BLUE,ATTR_ROW3,CII_COL0,14,OSD_WHITE, WIN_SROW3,WIN_EROW3,WIN_COL1,WIN_COL23,OSD_BLUE,ATTR_ROW3,CII_COL0,28,OSD_WHITE}
,{WIN_SROW4,WIN_EROW4,WIN_COL1,WIN_COL13,OSD_BLUE,ATTR_ROW4,CII_COL0,14,OSD_WHITE, WIN_SROW4,WIN_EROW4,WIN_COL1,WIN_COL22,OSD_BLUE,ATTR_ROW4,CII_COL0,28,OSD_WHITE}
,{WIN_SROW5,WIN_EROW5,WIN_COL1,WIN_COL13,OSD_BLUE,ATTR_ROW5,CII_COL0,14,OSD_WHITE, WIN_SROW5,WIN_EROW5,WIN_COL1,WIN_COL25,OSD_BLUE,ATTR_ROW5,CII_COL0,30,OSD_WHITE}
,{WIN_SROW6,WIN_EROW6,WIN_COL1,WIN_COL13,OSD_BLUE,ATTR_ROW6,CII_COL0,14,OSD_WHITE, WIN_SROW6,WIN_EROW6,WIN_COL1,WIN_COL22,OSD_BLUE,ATTR_ROW6,CII_COL0,28,OSD_WHITE}
                                                                                   
 //s-video main                                                                    
,{WIN_SROW2,WIN_EROW2,WIN_COL0,WIN_COL25,OSD_BLUE,ATTR_ROW2,CII_COL0,30,OSD_WHITE, WIN_SROW2,WIN_EROW2,WIN_COL0,WIN_COL25,OSD_BLUE,ATTR_ROW2,CII_COL0,28,OSD_WHITE}
,{WIN_SROW3,WIN_EROW3,WIN_COL0,WIN_COL25,OSD_BLUE,ATTR_ROW3,CII_COL0,30,OSD_WHITE, WIN_SROW3,WIN_EROW3,WIN_COL0,WIN_COL25,OSD_BLUE,ATTR_ROW3,CII_COL0,28,OSD_WHITE}
,{WIN_SROW4,WIN_EROW4,WIN_COL0,WIN_COL25,OSD_BLUE,ATTR_ROW4,CII_COL0,30,OSD_WHITE, WIN_SROW4,WIN_EROW4,WIN_COL0,WIN_COL25,OSD_BLUE,ATTR_ROW4,CII_COL0,28,OSD_WHITE}
,{WIN_SROW5,WIN_EROW5,WIN_COL0,WIN_COL25,OSD_BLUE,ATTR_ROW5,CII_COL0,30,OSD_WHITE, WIN_SROW5,WIN_EROW5,WIN_COL0,WIN_COL25,OSD_BLUE,ATTR_ROW5,CII_COL0,28,OSD_WHITE}
,{WIN_SROW6,WIN_EROW6,WIN_COL0,WIN_COL25,OSD_BLUE,ATTR_ROW6,CII_COL0,30,OSD_WHITE, WIN_SROW6,WIN_EROW6,WIN_COL0,WIN_COL25,OSD_BLUE,ATTR_ROW6,CII_COL0,28,OSD_WHITE}
                                                                                   
//s-video bright/contrast sub                                                      
,{WIN_SROW2,WIN_EROW2,WIN_COL1,WIN_COL10,OSD_BLUE,ATTR_ROW2,CII_COL0,11,OSD_WHITE, WIN_SROW2,WIN_EROW2,WIN_COL1,WIN_COL22,OSD_BLUE,ATTR_ROW2,CII_COL0,28,OSD_WHITE}
,{WIN_SROW3,WIN_EROW3,WIN_COL1,WIN_COL10,OSD_BLUE,ATTR_ROW3,CII_COL0,11,OSD_WHITE, WIN_SROW3,WIN_EROW3,WIN_COL1,WIN_COL22,OSD_BLUE,ATTR_ROW3,CII_COL0,28,OSD_WHITE}
,{WIN_SROW4,WIN_EROW4,WIN_COL1,WIN_COL10,OSD_BLUE,ATTR_ROW4,CII_COL0,11,OSD_WHITE, WIN_SROW4,WIN_EROW4,WIN_COL1,WIN_COL22,OSD_BLUE,ATTR_ROW4,CII_COL0,28,OSD_WHITE}
                                                                                   
//tuner color sub                                                                  
,{WIN_SROW2,WIN_EROW2,WIN_COL1,WIN_COL10,OSD_BLUE,ATTR_ROW2,CII_COL0,11,OSD_WHITE, WIN_SROW2,WIN_EROW2,WIN_COL1,WIN_COL22,OSD_BLUE,ATTR_ROW2,CII_COL0,28,OSD_WHITE}
,{WIN_SROW3,WIN_EROW3,WIN_COL1,WIN_COL10,OSD_BLUE,ATTR_ROW3,CII_COL0,11,OSD_WHITE, WIN_SROW3,WIN_EROW3,WIN_COL1,WIN_COL22,OSD_BLUE,ATTR_ROW3,CII_COL0,28,OSD_WHITE}
,{WIN_SROW4,WIN_EROW4,WIN_COL1,WIN_COL10,OSD_BLUE,ATTR_ROW4,CII_COL0,11,OSD_WHITE, WIN_SROW4,WIN_EROW4,WIN_COL1,WIN_COL22,OSD_BLUE,ATTR_ROW4,CII_COL0,28,OSD_WHITE}
,{WIN_SROW5,WIN_EROW5,WIN_COL1,WIN_COL10,OSD_BLUE,ATTR_ROW5,CII_COL0,11,OSD_WHITE, WIN_SROW5,WIN_EROW5,WIN_COL1,WIN_COL22,OSD_BLUE,ATTR_ROW5,CII_COL0,28,OSD_WHITE}
                                                                                   
//composite setup sub                                                              
,{WIN_SROW2,WIN_EROW2,WIN_COL1,WIN_COL13,OSD_BLUE,ATTR_ROW2,CII_COL0,14,OSD_WHITE, WIN_SROW2,WIN_EROW2,WIN_COL1,WIN_COL22,OSD_BLUE,ATTR_ROW2,CII_COL0,28,OSD_WHITE}
,{WIN_SROW3,WIN_EROW3,WIN_COL1,WIN_COL13,OSD_BLUE,ATTR_ROW3,CII_COL0,14,OSD_WHITE, WIN_SROW3,WIN_EROW3,WIN_COL1,WIN_COL23,OSD_BLUE,ATTR_ROW3,CII_COL0,28,OSD_WHITE}
,{WIN_SROW4,WIN_EROW4,WIN_COL1,WIN_COL13,OSD_BLUE,ATTR_ROW4,CII_COL0,14,OSD_WHITE, WIN_SROW4,WIN_EROW4,WIN_COL1,WIN_COL22,OSD_BLUE,ATTR_ROW4,CII_COL0,28,OSD_WHITE}
,{WIN_SROW5,WIN_EROW5,WIN_COL1,WIN_COL13,OSD_BLUE,ATTR_ROW5,CII_COL0,14,OSD_WHITE, WIN_SROW5,WIN_EROW5,WIN_COL1,WIN_COL25,OSD_BLUE,ATTR_ROW5,CII_COL0,30,OSD_WHITE}
,{WIN_SROW6,WIN_EROW6,WIN_COL1,WIN_COL13,OSD_BLUE,ATTR_ROW6,CII_COL0,14,OSD_WHITE, WIN_SROW6,WIN_EROW6,WIN_COL1,WIN_COL22,OSD_BLUE,ATTR_ROW6,CII_COL0,28,OSD_WHITE}
                                                                                   
//PIP main                                                                         
,{WIN_SROW2,WIN_EROW2,WIN_COL0,WIN_COL25,OSD_BLUE,ATTR_ROW2,CII_COL0,30,OSD_WHITE, WIN_SROW2,WIN_EROW2,WIN_COL0,WIN_COL25,OSD_BLUE,ATTR_ROW2,CII_COL0,28,OSD_WHITE}
,{WIN_SROW3,WIN_EROW3,WIN_COL0,WIN_COL25,OSD_BLUE,ATTR_ROW3,CII_COL0,30,OSD_WHITE, WIN_SROW3,WIN_EROW3,WIN_COL0,WIN_COL25,OSD_BLUE,ATTR_ROW3,CII_COL0,28,OSD_WHITE}
,{WIN_SROW4,WIN_EROW4,WIN_COL0,WIN_COL25,OSD_BLUE,ATTR_ROW4,CII_COL0,30,OSD_WHITE, WIN_SROW4,WIN_EROW4,WIN_COL0,WIN_COL25,OSD_BLUE,ATTR_ROW4,CII_COL0,28,OSD_WHITE}
,{WIN_SROW5,WIN_EROW5,WIN_COL0,WIN_COL25,OSD_BLUE,ATTR_ROW5,CII_COL0,30,OSD_WHITE, WIN_SROW5,WIN_EROW5,WIN_COL0,WIN_COL25,OSD_BLUE,ATTR_ROW5,CII_COL0,28,OSD_WHITE}
,{WIN_SROW6,WIN_EROW6,WIN_COL0,WIN_COL25,OSD_BLUE,ATTR_ROW6,CII_COL0,30,OSD_WHITE, WIN_SROW6,WIN_EROW6,WIN_COL0,WIN_COL25,OSD_BLUE,ATTR_ROW6,CII_COL0,28,OSD_WHITE}
                                                                                   
//PIP sub                                                                          
,{WIN_SROW2,WIN_EROW2,WIN_COL1,WIN_COL11,OSD_BLUE,ATTR_ROW2,CII_COL0,11,OSD_WHITE, WIN_SROW2,WIN_EROW2,WIN_COL1,WIN_COL24,OSD_BLUE,ATTR_ROW2,CII_COL0,28,OSD_WHITE}
,{WIN_SROW3,WIN_EROW3,WIN_COL1,WIN_COL11,OSD_BLUE,ATTR_ROW3,CII_COL0,11,OSD_WHITE, WIN_SROW3,WIN_EROW3,WIN_COL1,WIN_COL24,OSD_BLUE,ATTR_ROW3,CII_COL0,28,OSD_WHITE}
,{WIN_SROW4,WIN_EROW4,WIN_COL1,WIN_COL11,OSD_BLUE,ATTR_ROW4,CII_COL0,11,OSD_WHITE, WIN_SROW4,WIN_EROW4,WIN_COL1,WIN_COL24,OSD_BLUE,ATTR_ROW4,CII_COL0,28,OSD_WHITE}
,{WIN_SROW5,WIN_EROW5,WIN_COL0,WIN_COL25,OSD_BLUE,ATTR_ROW5,CII_COL0,30,OSD_WHITE, WIN_SROW5,WIN_EROW5,WIN_COL0,WIN_COL25,OSD_BLUE,ATTR_ROW5,CII_COL0,28,OSD_WHITE}
,{WIN_SROW6,WIN_EROW6,WIN_COL1,WIN_COL11,OSD_BLUE,ATTR_ROW6,CII_COL0,11,OSD_WHITE, WIN_SROW6,WIN_EROW6,WIN_COL1,WIN_COL24,OSD_BLUE,ATTR_ROW6,CII_COL0,28,OSD_WHITE}
                                                                                   
//PIP control
//,{WIN_SROW2,WIN_EROW2,WIN_COL1,WIN_COL12,OSD_BLUE,ATTR_ROW2,CII_COL0,13,OSD_WHITE,WIN_SROW2,WIN_EROW2,WIN_COL1,WIN_COL22,OSD_BLUE,ATTR_ROW2,CII_COL0,28,OSD_WHITE}
,{WIN_SROW2,WIN_EROW2,WIN_COL1,WIN_COL12,OSD_BLUE,ATTR_ROW2,CII_COL0,13,OSD_WHITE, WIN_SROW2,WIN_EROW2,WIN_COL1,WIN_COL22,OSD_BLUE,ATTR_ROW2,CII_COL0,28,OSD_WHITE}
,{WIN_SROW3,WIN_EROW3,WIN_COL1,WIN_COL9, OSD_BLUE,ATTR_ROW3,CII_COL0,10,OSD_WHITE, WIN_SROW3,WIN_EROW3,WIN_COL1,WIN_COL22,OSD_BLUE,ATTR_ROW3,CII_COL0,28,OSD_WHITE}
,{WIN_SROW4,WIN_EROW4,WIN_COL1,WIN_COL9, OSD_BLUE,ATTR_ROW4,CII_COL0,10,OSD_WHITE, WIN_SROW4,WIN_EROW4,WIN_COL1,WIN_COL22,OSD_BLUE,ATTR_ROW4,CII_COL0,28,OSD_WHITE}
                                                                                   
//PIP setup sub                                                                    
,{WIN_SROW2,WIN_EROW2,WIN_COL1,WIN_COL13,OSD_BLUE,ATTR_ROW2,CII_COL0,14,OSD_WHITE, WIN_SROW2,WIN_EROW2,WIN_COL1,WIN_COL22,OSD_BLUE,ATTR_ROW2,CII_COL0,28,OSD_WHITE}
,{WIN_SROW3,WIN_EROW3,WIN_COL1,WIN_COL13,OSD_BLUE,ATTR_ROW3,CII_COL0,14,OSD_WHITE, WIN_SROW3,WIN_EROW3,WIN_COL1,WIN_COL23,OSD_BLUE,ATTR_ROW3,CII_COL0,28,OSD_WHITE}
,{WIN_SROW4,WIN_EROW4,WIN_COL1,WIN_COL13,OSD_BLUE,ATTR_ROW4,CII_COL0,14,OSD_WHITE, WIN_SROW4,WIN_EROW4,WIN_COL1,WIN_COL22,OSD_BLUE,ATTR_ROW4,CII_COL0,28,OSD_WHITE}
,{WIN_SROW5,WIN_EROW5,WIN_COL1,WIN_COL13,OSD_BLUE,ATTR_ROW5,CII_COL0,14,OSD_WHITE, WIN_SROW5,WIN_EROW5,WIN_COL1,WIN_COL25,OSD_BLUE,ATTR_ROW5,CII_COL0,30,OSD_WHITE}
,{WIN_SROW6,WIN_EROW6,WIN_COL1,WIN_COL13,OSD_BLUE,ATTR_ROW6,CII_COL0,14,OSD_WHITE, WIN_SROW6,WIN_EROW6,WIN_COL1,WIN_COL22,OSD_BLUE,ATTR_ROW6,CII_COL0,28,OSD_WHITE}

//VOLUME
,{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}

//PIP SUB-WINDOW MENU
,{WIN_SROW2,WIN_EROW2,WIN_COL0,WIN_COL25,OSD_BLUE,ATTR_ROW2,CII_COL0,30,OSD_WHITE, WIN_SROW2,WIN_EROW2,WIN_COL1,WIN_COL25,OSD_BLUE,ATTR_ROW2,CII_COL0,30,OSD_WHITE}
,{WIN_SROW3,WIN_EROW3,WIN_COL0,WIN_COL25,OSD_BLUE,ATTR_ROW3,CII_COL0,30,OSD_WHITE, WIN_SROW3,WIN_EROW3,WIN_COL1,WIN_COL25,OSD_BLUE,ATTR_ROW3,CII_COL0,30,OSD_WHITE}
,{WIN_SROW4,WIN_EROW4,WIN_COL0,WIN_COL25,OSD_BLUE,ATTR_ROW4,CII_COL0,30,OSD_WHITE, WIN_SROW4,WIN_EROW4,WIN_COL1,WIN_COL25,OSD_BLUE,ATTR_ROW4,CII_COL0,30,OSD_WHITE}
,{WIN_SROW5,WIN_EROW5,WIN_COL0,WIN_COL25,OSD_BLUE,ATTR_ROW5,CII_COL0,30,OSD_WHITE, WIN_SROW5,WIN_EROW5,WIN_COL1,WIN_COL25,OSD_BLUE,ATTR_ROW5,CII_COL0,30,OSD_WHITE}
,{WIN_SROW6,WIN_EROW6,WIN_COL0,WIN_COL25,OSD_BLUE,ATTR_ROW6,CII_COL0,30,OSD_WHITE, WIN_SROW6,WIN_EROW6,WIN_COL1,WIN_COL25,OSD_BLUE,ATTR_ROW6,CII_COL0,30,OSD_WHITE}
,{WIN_SROW7,WIN_EROW7,WIN_COL0,WIN_COL25,OSD_BLUE,ATTR_ROW7,CII_COL0,30,OSD_WHITE, WIN_SROW7,WIN_EROW7,WIN_COL1,WIN_COL25,OSD_BLUE,ATTR_ROW7,CII_COL0,30,OSD_WHITE}
,{WIN_SROW8,WIN_EROW8,WIN_COL0,WIN_COL25,OSD_BLUE,ATTR_ROW8,CII_COL0,30,OSD_WHITE, WIN_SROW8,WIN_EROW8,WIN_COL1,WIN_COL25,OSD_BLUE,ATTR_ROW8,CII_COL0,30,OSD_WHITE}
,{WIN_SROW9,WIN_EROW9,WIN_COL0,WIN_COL25,OSD_BLUE,ATTR_ROW9,CII_COL0,30,OSD_WHITE, WIN_SROW9,WIN_EROW9,WIN_COL1,WIN_COL25,OSD_BLUE,ATTR_ROW9,CII_COL0,30,OSD_WHITE}
};
#endif

//----------------------------------------
#ifdef test_function	

#if 0
void delay1ms(void)
{
	BYTE i;
	i = 165;
	while(i--);
}
void delay10ms(void)
{
	BYTE i;
	i =10;
	while(i--)delay1ms();
	
}

void delay100ms(void)
{
	BYTE i;
	i =10;
	while(i--)delay10ms();
	
}

void delay1000ms(void)
{
	BYTE i;
	i =10;
	while(i--)delay100ms();
	
}
#endif
#endif
//----------------------------------------
/*
void OsdPositionFunction(BYTE Recdata)
{
	#if defined(SXGA_Panel)
	switch(Recdata)
	{
		case 0:
			xOSD_WIN_REG[0x0D]=0x47;//H
			xOSD_WIN_REG[0x0C]=0x6c;//Y
			break;
		case 1:
			xOSD_WIN_REG[0x0D]=0x8c;//H
			xOSD_WIN_REG[0x0C]=0x0e;//Y
			break;
		case 2:
			xOSD_WIN_REG[0x0D]=0x8c;//H
			xOSD_WIN_REG[0x0C]=0xc9;//Y
			break;
		case 3:
			xOSD_WIN_REG[0x0D]=0x02;//H
			xOSD_WIN_REG[0x0C]=0xc9;//Y
			break;
		case 4:
			xOSD_WIN_REG[0x0D]=0x02;//H
			xOSD_WIN_REG[0x0C]=0x0e;//Y
			break;
		default:
			xOSD_WIN_REG[0x0D]=0x47;//H
			xOSD_WIN_REG[0x0C]=0x6c;//Y
			break;
	}
	#elif defined(XGA_Panel)
	switch(Recdata)
	{
		case 0:
			xOSD_WIN_REG[0x0D]=0x1F;//H
			xOSD_WIN_REG[0x0C]=0x3C;//Y
			break;
		case 1:
			xOSD_WIN_REG[0x0D]=0x48;//H
			xOSD_WIN_REG[0x0C]=0x99;//Y
			break;
		case 2:
			xOSD_WIN_REG[0x0D]=0x48;//H
			xOSD_WIN_REG[0x0C]=0x70;//Y
			break;
		case 3:
			xOSD_WIN_REG[0x0D]=0xa2;//H
			xOSD_WIN_REG[0x0C]=0x70;//Y
			break;
		case 4:
			xOSD_WIN_REG[0x0D]=0xa2;//H
			xOSD_WIN_REG[0x0C]=0x99;//Y
			break;
		default:
			xOSD_WIN_REG[0x0D]=0x1F;//H
			xOSD_WIN_REG[0x0C]=0x3C;//Y
			break;
	}	
	#elif defined(SVGA_Panel)
	switch(Recdata)
	{
		case 0:
			xOSD_WIN_REG[0x0D]=0x1F;//H
			xOSD_WIN_REG[0x0C]=0x3C;//Y
			break;
		case 1:
			xOSD_WIN_REG[0x0D]=0x48;//H
			xOSD_WIN_REG[0x0C]=0x99;//Y
			break;
		case 2:
			xOSD_WIN_REG[0x0D]=0x48;//H
			xOSD_WIN_REG[0x0C]=0x70;//Y
			break;
		case 3:
			xOSD_WIN_REG[0x0D]=0xa2;//H
			xOSD_WIN_REG[0x0C]=0x70;//Y
			break;
		case 4:
			xOSD_WIN_REG[0x0D]=0xa2;//H
			xOSD_WIN_REG[0x0C]=0x99;//Y
			break;
		default:
			xOSD_WIN_REG[0x0D]=0x1F;//H
			xOSD_WIN_REG[0x0C]=0x3C;//Y
			break;
	}
	#endif
}
*/
void OsdDataClear(void)
{
	BYTE  i;
	for (i=0;i<12;i++) 
		OSD230SeqSend(DSP_ROW0+i,CII_COL0,0x00,30);//clear
//	OSD230SeqSend(DSP_ROW1,CII_COL0,0x00,30);//clear
//	OSD230SeqSend(DSP_ROW2,CII_COL0,0x00,30);
//	OSD230SeqSend(DSP_ROW3,CII_COL0,0x00,30);
//	OSD230SeqSend(DSP_ROW4,CII_COL0,0x00,30);
//	OSD230SeqSend(DSP_ROW5,CII_COL0,0x00,30);
//	OSD230SeqSend(DSP_ROW6,CII_COL0,0x00,30);
//	OSD230SeqSend(DSP_ROW7,CII_COL0,0x00,30);
//	OSD230SeqSend(DSP_ROW8,CII_COL0,0x00,30);
//	OSD230SeqSend(DSP_ROW9,CII_COL0,0x00,30);
//	OSD230SeqSend(DSP_ROW10,CII_COL0,0x00,30);
//	OSD230SeqSend(DSP_ROW11,CII_COL0,0x00,30);
//	OSD230SeqSend(DSP_ROW12,CII_COL0,0x00,30);
	//Clear->On(toggle)
}

void OsdDataWindowClear(void)		// 3~9 line	//2003-04-18
{
	BYTE  i;
	for (i=0;i<7;i++) 
		OSD230SeqSend(DSP_ROW3+i,CII_COL0,0x00,30);
//	OSD230SeqSend(DSP_ROW4,CII_COL0,0x00,30);
//	OSD230SeqSend(DSP_ROW5,CII_COL0,0x00,30);
//	OSD230SeqSend(DSP_ROW6,CII_COL0,0x00,30);
//	OSD230SeqSend(DSP_ROW7,CII_COL0,0x00,30);
//	OSD230SeqSend(DSP_ROW8,CII_COL0,0x00,30);
//	OSD230SeqSend(DSP_ROW9,CII_COL0,0x00,30);
}

void OsdDataWindowClear2(void)		// 10~11 line
{
	/*
	if(OsdGrade<=2)
	{
		OSD230SeqSend(DSP_ROW10,CII_COL0,0x00,30);
	}
	else if(OsdGrade==3)
	{
	*/	OSD230SeqSend(DSP_ROW10,CII_COL0,0x00,30);
		OSD230SeqSend(DSP_ROW11,CII_COL0,0x00,30);
	//}
}

//#ifndef savememory
void OsdEditWindowDataClear(void)		// 13~14 line
{
	OSD230SeqSend(DSP_ROW13,CII_COL0,0x00,30);
	OSD230SeqSend(DSP_ROW14,CII_COL0,0x00,30);
}
//#endif


void ClearMenuDescription(void)
{
	#ifdef OsdMenuType1
	OSD230SeqSend(DSP_ROW10,CII_COL0,0x00,30);	// 메뉴 아래부분의 메뉴설명부분 삭제
	#else
	OSD230SeqSend(DSP_ROW11,CII_COL0,0x00,30);	// 메뉴 아래부분의 메뉴설명부분 삭제
	#endif
}

void OsdAttrClear(void)
{
	BYTE  i;
	for (i=0;i<7;i++) 
	{
		#ifdef IntOsdBar
		OSDSeqSend(IN_ATTR_ROW3+i,IN_CII_COL0,0x00,30); //내부
		#endif
		OSD230SeqSend(ATTR_ROW3+i,CII_COL0,0x00,30);
	}
//	OSD230SeqSend(ATTR_ROW4,CII_COL0,0x00,30);
//	OSD230SeqSend(ATTR_ROW5,CII_COL0,0x00,30);
//	OSD230SeqSend(ATTR_ROW6,CII_COL0,0x00,30);
//	OSD230SeqSend(ATTR_ROW7,CII_COL0,0x00,30);
//	OSD230SeqSend(ATTR_ROW8,CII_COL0,0x00,30);
//	OSD230SeqSend(ATTR_ROW9,CII_COL0,0x00,30);
	//Clear->On(toggle)
}


void OsdAllAttrClear(void)
{
	BYTE  i;
	for (i=0;i<12;i++) 
	{
		#ifdef IntOsdBar
		OSDSeqSend(IN_ATTR_ROW0+i,IN_CII_COL0,0x00,30); //내부
		#endif
		OSD230SeqSend(ATTR_ROW0+i,CII_COL0,0x00,30);
	}
}
void OsdAttr_row10_Clear(void)
{
	OSD230SeqSend(ATTR_ROW10,CII_COL0,0x00,30);
}

#ifndef savememory
void OsdAttr_RowXX_Clear(BYTE ClearRow)
{
	OSD230SeqSend(ClearRow,CII_COL0,0x00,30);
}
#endif

void DisplayWindow(void)	//넘겨받은 OSDwindows값에 따라 윈도우를 그린다.
{
	switch(OSDWindows)
	{
	#if !defined(INT_EXTOSD)	// 외부OSD olny
		case	AnalogMainWindow:
		case	DigitalMainWindow:
		case	PIPMainWindow:
				OSDWINDOW(TOPWINDOW);
				OSDWINDOW_OPTION(TOPWINDOW_OPTION);
				break;

		case	CompositeMainwindow:
		case	S_videoMainWindow:
		case	TunerMainWindow:
				OSDWINDOW(TVTOPWINDOW);
				OSDWINDOW_OPTION(TVWINDOW_OPTION);
				break;
			
		case	AnalogSubwindow:
		case	DigitalSubWindow:
		case	CompositeSubwindow:
		case	CompositeNoVidSubwindow:
		case	S_videoSubwindow:
		case	S_videoNoVidSubwindow:
		case	ChannelNumWindow:
		case	PIPNoVideoWindow:
		case       RecallWindow:			// smpark 20030823
				//OSDWINDOW(SUBWINDOW);
				OSDWINDOW_OPTION(INPUTWINDOW_OPTION);//Dummy
				break;
			
		case	AnalogPowerSaverWindow:
		case	AnalogOutofFreqWindow:
		case	AnalogSelfDigWindow:
		case	DigitalPowerSaverWindow:
		case	DigitalSelfDigWindow:
				OSDWINDOW(INFOWINDOW);
				OSDWINDOW_OPTION(INFOWINDOW_OPTION);
				break;
			
		//case	AutoTuneMainWindow:
		//		OSDWINDOW(AUTOTUNEWINDOW);
		//		OSDWINDOW_OPTION(AUTOTUNEWINDOW_OPTION);
		//		break;
			
		case	VolumeWindow:
		case	MuteWindow:
				//OSDWINDOW(VOLUMEWINDOW);
				OSDWINDOW_OPTION(VOLUMEWINDOW_OPTION);
				break;
				
		case	SscWindow:	//03-08-06
		case	SpcWindow:
		case	MtsWindow:
		case	SleepWindow:
				//OSDWINDOW(SUB_CHAR_WINDOW);
				OSDWINDOW_OPTION(SUB_CHAR_WINDOW_OPTION);
				break;
		
		case	PipSelectionGuideWindow:
				OSDWINDOW(PIPSELECTIONGUIDEWINDOW);
				OSDWINDOW_OPTION(PIPSELECTIONGUIDEWINDOW_OPTION);
				break;
		
		case	PIPSubWindow:
				//OSDWINDOW(PIPSUBWINDOW);
				OSDWINDOW_OPTION(PIPSUBWINDOW_OPTION);//Dummy
				break;
		
		case	TunerSubWindow:
				OSDWINDOW(TUNERWINDOW);
				OSDWINDOW_OPTION(SUBWINDOW_OPTION);//channel displayb sub windows
				break;
		case	OSDHotkeyMessageWindow:
		case	AutoTuneMainWindow:
				OSDWINDOW(OSDHOTKEYMSGWINDOW);
				OSDWINDOW_OPTION(OSDHOTKEYMSG_OPTION);//Dummy
				break;
		default:
				break;
	#else	//---------------------------------------------------------for EMH2 (int_osd) // 내부+외부
		case	AnalogMainWindow:
		case	DigitalMainWindow:
		case	PIPMainWindow:
				//OSDWINDOW(TOPWINDOW,0);
				OSDWINDOW_OPTION(TOPWINDOW_OPTION);
				OSDWINDOW(IN_TOPWINDOW,1);	//내부	//For EMH2, INT_EXTOSD
				
				break;

		case	CompositeMainwindow:
		case	S_videoMainWindow:
		case	TunerMainWindow:
			#ifndef	TempOsdMenu
				#ifdef SSwideOsdtype 
				OSDWINDOW(TVTOPWINDOW2,0);	// 외부
				OSDWINDOW_OPTION(TVWINDOW_OPTION);
				
				OSDWINDOW(IN_TVTOPWINDOW,1);	// 내부
				OSDWINDOW(IN_WINDOW2_ColorWhite,1);	// 내부
				OSDWINDOW(IN_WINDOW1_ColorExtWhite,1);	// 내부
				#else
				OSDWINDOW(TVTOPWINDOW,0);	// 외부
				OSDWINDOW_OPTION(TVWINDOW_OPTION);
				OSDWINDOW(IN_TVTOPWINDOW,1);	// 내부
				#endif
				break;
			#else

			switch(TempOsdNum)
			{
			case	0:
				OSDWINDOW(TVTOPWINDOW,0);	// 외부
				OSDWINDOW_OPTION(TVWINDOW_OPTION);
				OSDWINDOW(IN_TVTOPWINDOW,1);	// 내부
				break;
			
			//-------------
			case	1:
				OSDWINDOW(TVTOPWINDOW2,0);	// 외부
				OSDWINDOW_OPTION(TVWINDOW_OPTION);
				
				OSDWINDOW(IN_TVTOPWINDOW,1);	// 내부
				OSDWINDOW(IN_WINDOW2_ColorWhite,1);	// 내부
				OSDWINDOW(IN_WINDOW1_ColorExtWhite,1);	// 내부
				break;
			
			case	2:
				OSDWINDOW(TVTOPWINDOW2,0);	// 외부
				OSDWINDOW_OPTION(TVWINDOW_OPTION);
				
				OSDWINDOW(IN_TVTOPWINDOW,1);	// 내부
				OSDWINDOW(IN_WINDOW2_ColorExtWhite,1);	// 내부
				OSDWINDOW(IN_WINDOW1_ColorWhite,1);	// 내부
				break;
				
			case	3:
				OSDWINDOW(TVTOPWINDOW2,0);	// 외부
				OSDWINDOW_OPTION(TVWINDOW_OPTION);
				
				OSDWINDOW(IN_TVTOPWINDOW,1);	// 내부
				OSDWINDOW(IN_WINDOW2_ColorExtWhite,1);	// 내부
				OSDWINDOW(IN_WINDOW1_ColorExtWhite,1);	// 내부
				break;
			
			case	4:
				OSDWINDOW(TVTOPWINDOW2,0);	// 외부
				OSDWINDOW_OPTION(TVWINDOW_OPTION);
				
				OSDWINDOW(IN_TVTOPWINDOW,1);	// 내부
				OSDWINDOW(IN_WINDOW3_ColorExtWhite,1);	// 내부
				OSDWINDOW(IN_WINDOW2_ColorWhite,1);	// 내부
				OSDWINDOW(IN_WINDOW1_ColorWhite,1);	// 내부
				break;
			//------------------------------------------------	
			case	5:
				OSDWINDOW(TVTOPWINDOW2,0);	// 외부
				OSDWINDOW_OPTION(TVWINDOW_OPTION);
				OSDWINDOW(IN_TVTOPWINDOW2,1);	// 내부
				break;
			
			case	6:
				OSDWINDOW(TVTOPWINDOW2,0);	// 외부
				OSDWINDOW_OPTION(TVWINDOW_OPTION);
				
				OSDWINDOW(IN_TVTOPWINDOW2,1);	// 내부
				OSDWINDOW(IN_WINDOW2_ColorWhite2,1);	// 내부
				OSDWINDOW(IN_WINDOW1_ColorExtWhite2,1);	// 내부
				break;
			
			case	7:
				OSDWINDOW(TVTOPWINDOW2,0);	// 외부
				OSDWINDOW_OPTION(TVWINDOW_OPTION);
				
				OSDWINDOW(IN_TVTOPWINDOW2,1);	// 내부
				OSDWINDOW(IN_WINDOW2_ColorExtWhite2,1);	// 내부
				OSDWINDOW(IN_WINDOW1_ColorWhite2,1);	// 내부
				break;
				
			case	8:
				OSDWINDOW(TVTOPWINDOW2,0);	// 외부
				OSDWINDOW_OPTION(TVWINDOW_OPTION);
				
				OSDWINDOW(IN_TVTOPWINDOW2,1);	// 내부
				OSDWINDOW(IN_WINDOW2_ColorExtWhite2,1);	// 내부
				OSDWINDOW(IN_WINDOW1_ColorExtWhite2,1);	// 내부
				break;
			
			case	9:
				OSDWINDOW(TVTOPWINDOW2,0);	// 외부
				OSDWINDOW_OPTION(TVWINDOW_OPTION);
				
				OSDWINDOW(IN_TVTOPWINDOW2,1);	// 내부
				OSDWINDOW(IN_WINDOW3_ColorExtWhite2,1);	// 내부
				OSDWINDOW(IN_WINDOW2_ColorWhite2,1);	// 내부
				OSDWINDOW(IN_WINDOW1_ColorWhite2,1);	// 내부
				break;
			//--------
			case	10:
				OSDWINDOW(TVTOPWINDOW2,0);	// 외부
				OSDWINDOW_OPTION(TVWINDOW_OPTION);
				
				OSDWINDOW(IN_TVTOPWINDOW,1);	// 내부
				OSDWINDOW(IN_WINDOW1_ColorExtWhite,1);	// 내부
				OSDWINDOW(IN_WINDOW2_ColorWhite,1);	// 내부
				OSDWINDOW(IN_WINDOW3_ColorExtMagenta,1);	// 내부
				OSDWINDOW(IN_WINDOW4_BgBlack,1);	// 내부
				break;
			
			case	11:
				OSDWINDOW(TVTOPWINDOW2,0);	// 외부
				OSDWINDOW_OPTION(TVWINDOW_OPTION);
				
				OSDWINDOW(IN_TVTOPWINDOW,1);	// 내부
				OSDWINDOW(IN_WINDOW1_ColorWhite,1);	// 내부
				OSDWINDOW(IN_WINDOW2_ColorExtWhite,1);	// 내부
				OSDWINDOW(IN_WINDOW3_ColorExtMagenta,1);	// 내부
				break;

			case	12:
				OSDWINDOW(TVTOPWINDOW2,0);	// 외부
				OSDWINDOW_OPTION(TVWINDOW_OPTION);

				OSDWINDOW(IN_TVTOPWINDOW2,1);	// 내부
				OSDWINDOW(IN_WINDOW1_ColorWhite2,1);	// 내부
				OSDWINDOW(IN_WINDOW2_ColorExtWhite2,1);	// 내부
				OSDWINDOW(IN_WINDOW3_ColorExtMagenta2,1);	// 내부
				break;
			case	13:
				OSDWINDOW(TVTOPWINDOW2,0);	// 외부
				OSDWINDOW_OPTION(TVWINDOW_OPTION);

				OSDWINDOW(IN_TVTOPWINDOW2,1);	// 내부
				OSDWINDOW(IN_WINDOW1_ColorExtWhite2,1);	// 내부
				OSDWINDOW(IN_WINDOW2_ColorWhite2,1);	// 내부
				OSDWINDOW(IN_WINDOW3_ColorExtMagenta2,1);	// 내부
				break;
			case	14:
				OSDWINDOW(TVTOPWINDOW2,0);	// 외부
				OSDWINDOW_OPTION(TVWINDOW_OPTION);

				OSDWINDOW(IN_TVTOPWINDOW2,1);	// 내부
				OSDWINDOW(IN_WINDOW1_ColorWhite2,1);	// 내부
				OSDWINDOW(IN_WINDOW2_ColorWhite2,1);	// 내부
				OSDWINDOW(IN_WINDOW3_ColorExtMagenta2,1);	// 내부
				break;
			//--------			
			case	15:
				OSDWINDOW(TVTOPWINDOW,0);	// 외부
				OSDWINDOW_OPTION(TVWINDOW_OPTION);
				
				OSDWINDOW(IN_TVTOPWINDOW,1);	// 내부
				OSDWINDOW(IN_WINDOW1_ColorExtWhite,1);	// 내부
				break;
			//--------
			
			}
			
			#endif
			break;	
			
		case	AnalogSubwindow:
		case	DigitalSubWindow:
		case	CompositeSubwindow:
		case	CompositeNoVidSubwindow:
		case	S_videoSubwindow:
		case	S_videoNoVidSubwindow:
		case	ChannelNumWindow:
		case	PIPNoVideoWindow:
				//OSDWINDOW(SUBWINDOW);
				OSDWINDOW_OPTION(INPUTWINDOW_OPTION);//Dummy
				break;
			
		case	AnalogPowerSaverWindow:
		case	AnalogOutofFreqWindow:
		case	AnalogSelfDigWindow:
		case	DigitalPowerSaverWindow:
		case	DigitalSelfDigWindow:
				OSDWINDOW(INFOWINDOW,0);
				OSDWINDOW_OPTION(INFOWINDOW_OPTION);
				break;
			
		//case	AutoTuneMainWindow:
		//		OSDWINDOW(AUTOTUNEWINDOW,0);
		//		OSDWINDOW_OPTION(AUTOTUNEWINDOW_OPTION);
		//		break;
			
		case	VolumeWindow:
		//case	MuteWindow:
				//OSDWINDOW(VOLUMEWINDOW,0);
				if( (CurrentFunction!=Tuner_mode)&&(CurrentFunction!=Composite_mode)&&(CurrentFunction!=Svideo_mode) )
					OSDWINDOW_OPTION(VOLUMEWINDOW_OPTION);
				else{
					OSDWINDOW_OPTION(VOLUMEWINDOW_OPTION);
					OSDWINDOW(IN_VOLUMEWINDOW,1);	// 내부
				}
				break;

		case	MuteWindow:
				OSDWINDOW_OPTION(VOLUMEWINDOW_OPTION);
				OSDWINDOW(IN_WINDOW_OFF,1);	// 내부 //test
				break;
				
		case	SscWindow:	//03-08-06
		case	SpcWindow:
		case	MtsWindow:
		case	SleepWindow:
				//OSDWINDOW(SUB_CHAR_WINDOW,0);	// 0:외부, 1:내부
				OSDWINDOW_OPTION(SUB_CHAR_WINDOW_OPTION);
				break;
				
		case	PipSelectionGuideWindow:
				OSDWINDOW(PIPSELECTIONGUIDEWINDOW,0);
				OSDWINDOW_OPTION(PIPSELECTIONGUIDEWINDOW_OPTION);
				break;
		
		case	PIPSubWindow:
				//OSDWINDOW(PIPSUBWINDOW,0);
				OSDWINDOW_OPTION(PIPSUBWINDOW_OPTION);//Dummy
				break;
		
		case	TunerSubWindow:
				OSDWINDOW(TUNERWINDOW,0);
				OSDWINDOW_OPTION(SUBWINDOW_OPTION);//channel displayb sub windows
				break;
		case	OSDHotkeyMessageWindow:
		case	AutoTuneMainWindow:
				OSDWINDOW(OSDHOTKEYMSGWINDOW,0);
				OSDWINDOW_OPTION(OSDHOTKEYMSG_OPTION);//Dummy
				break;
		default:
				break;
	#endif
				
		
	}
}


#if 0
void Displaybar(BYTE Recdata0,BYTE Recdata1,BYTE Recdata2,BYTE Recdata3,BYTE Recdata4)
{
	signed int temp=0;
	BYTE index=0;
	
	OSD230SeqSend(Recdata3,Recdata4,_LTriAngle,1);
	OSD230SeqSend(Recdata3,Recdata4+1+10,_RTriAngle,1);
	
	temp=(40*Recdata2);
	temp=temp/(Recdata1-Recdata0);
	
	OSD230RowSend(Recdata3);
	OSD230ColSend(Recdata4+1);
	HighOSDArea = 0;
	
	if(temp==0) OSD230SeqSend(Recdata3,Recdata4+1,_4LPrgsBarMin,10);
	else
	while(1)
	{
		if(temp >4)		{OSD230DataSend(_4LPrgsBarMax);}
		else if(temp==4)	{OSD230DataSend(_4LPrgsBarMax);}
		else if(temp==3)	{OSD230DataSend(_4LPrgsBar3);}
		else if(temp==2)	{OSD230DataSend(_4LPrgsBar2);}
		else if(temp==1)	{OSD230DataSend(_4LPrgsBar1);}
		
		temp=(temp-4);
		++index;
		if(temp<=0)
		{
			while(index<10)
			{
				++index;
				OSD230DataSend(_4LPrgsBarMin);
			}
			break;
		}	
	}
	
}
#else		
void Displaybar(BYTE RecMin,BYTE RecMax,BYTE RecData,BYTE RecRow,BYTE RecCol)	//by thkim	
{										//증가할 때 꽉채워지는 메뉴바
	signed int temp=0;
	idata	BYTE index=0;
	idata	BYTE size=28;
	
	OSD230SeqSend(RecRow,RecCol,_6LBarLend,1);
	OSD230SeqSend(RecRow,RecCol+1+size,_6LBarRend,1);
	
	temp=(6*size*RecData);
	temp=temp/(RecMax-RecMin);
	
	OSD230RowSend(RecRow);
	OSD230ColSend(RecCol+1);
	HighOSDArea = 0;
	                                                     
	if(temp==0) OSD230SeqSend(RecRow,RecCol+1,_6LBarNull,size);
	else
	
	while(1)
	{
		if(temp >6)		{OSD230DataSend(_6LBarFull);}
		else if(temp==6)	{OSD230DataSend(_6LBarFull);}
		else if(temp==5)	{OSD230DataSend(_6LBar5);}
		else if(temp==4)	{OSD230DataSend(_6LBar4);}
		else if(temp==3)	{OSD230DataSend(_6LBar3);}
		else if(temp==2)	{OSD230DataSend(_6LBar2);}
		else if(temp==1)	{OSD230DataSend(_6LBar1);}
		
		temp=(temp-6);
		++index;
		if(temp<=0)
		{
			while(index<size)
			{
				++index;
				OSD230DataSend(_6LBarNull);
			}
			break;
		}	
	}
	
}
#endif

#if 0
void Displaybar2(BYTE RecMin,BYTE RecMax,BYTE RecData,BYTE RecRow,BYTE RecCol)
{
	signed int temp=0;
	BYTE index=0;
	
	OSD230SeqSend(RecRow,RecCol,_LTriAngle,1);
	OSD230SeqSend(RecRow,RecCol+1+12,_RTriAngle,1);
	
	temp=(48*RecData);
	temp=temp/(RecMax-RecMin);
	
	OSD230RowSend(RecRow);
	OSD230ColSend(RecCol+1);
	HighOSDArea = 0;
	
	if(temp==0) OSD230SeqSend(RecRow,RecCol+1,_4LPrgsBarMin,12);
	else
	
	while(1)
	{
		if(temp >4)		{OSD230DataSend(_4LPrgsBarMax);}
		else if(temp==4)	{OSD230DataSend(_4LPrgsBarMax);}
		else if(temp==3)	{OSD230DataSend(_4LPrgsBar3);}
		else if(temp==2)	{OSD230DataSend(_4LPrgsBar2);}
		else if(temp==1)	{OSD230DataSend(_4LPrgsBar1);}
		
		temp=(temp-4);
		++index;
		if(temp<=0)
		{
			while(index<12)
			{
				++index;
				OSD230DataSend(_4LPrgsBarMin);
			}
			break;
		}	
	}
}
#else

void Displaybar2(BYTE RecMin,BYTE RecMax,BYTE RecData,BYTE RecRow,BYTE RecCol)	//by thkim	
{										//증가할 때 꽉채워지는 메뉴바
	signed int temp=0;
	BYTE index=0;
	
	//OSD230SeqSend(RecRow,RecCol,_LTriAngle,1);
	//OSD230SeqSend(RecRow,RecCol+1+12,_RTriAngle,1);
	
	temp=(42*RecData);
	temp=temp/(RecMax-RecMin);
	
	OSD230RowSend(RecRow);
	OSD230ColSend(RecCol+1);
	HighOSDArea = 0;
	
	if(temp==0) OSD230SeqSend(RecRow,RecCol+1,_3LBarNull,14);
	else
	
	while(1)
	{
		if(temp >3)		{OSD230DataSend(_3LBarFull);}
		else if(temp==3)	{OSD230DataSend(_3LBarFull);}
		else if(temp==2)	{OSD230DataSend(_3LBarL2);}
		else if(temp==1)	{OSD230DataSend(_3LBarL1);}
		
		temp=(temp-3);
		++index;
		if(temp<=0)
		{
			while(index<14)
			{
				++index;
				OSD230DataSend(_3LBarNull);
			}
			break;
		}	
	}
	
}
#endif

void Displaybar3(BYTE RecMin,BYTE RecMax,BYTE RecData,BYTE RecRow,BYTE RecCol)	//2003-05-09 by thkim	
{										//증감할 때 해당값만 표시하는 메뉴바
	signed int temp=0;
	BYTE index=0;
	
	//OSD230SeqSend(RecRow,RecCol,_LTriAngle,1);
	//OSD230SeqSend(RecRow,RecCol+1+12,_RTriAngle,1);
	
	temp=(42*RecData);
	temp=temp/(RecMax-RecMin);
	
	OSD230RowSend(RecRow);
	OSD230ColSend(RecCol+1);
	HighOSDArea = 0;
	
	if(temp==0) 	
	{
		OSD230SeqSend(RecRow,RecCol+1,_3LBarNull,14);
		OSD230SeqSend(RecRow,RecCol+1,_3LBarL1,1);
	}
	else if(temp==42)
	{
		OSD230SeqSend(RecRow,RecCol+1,_3LBarNull,14);
		OSD230SeqSend(RecRow,RecCol+14,_3LBarR1,1);
	}
	else
	{
		OSD230SeqSend(RecRow,RecCol+1,_3LBarNull,14);
		if(temp%3==0)
		{
			OSD230SeqSend(RecRow,RecCol+(temp/3)+1,_3LBarL1,1);
		}
		else if(temp%3==1)
		{
			OSD230SeqSend(RecRow,RecCol+(temp/3)+1,_3LBarMid,1);
		}
		else if(temp%3==2)
		{
			OSD230SeqSend(RecRow,RecCol+(temp/3)+1,_3LBarR1,1);
		}
		OSD230SeqSend(RecRow,RecCol+(temp/3)+2,_3LBarNull,13-(temp/3));
	}
}

#if 0	//test
void DisplaybarWord(BYTE RecMin,WORD RecMax,WORD RecData,BYTE RecRow,BYTE RecCol)	//by thkim	
{										//증가할 때 꽉채워지는 메뉴바
	signed int temp=0;
	BYTE index=0;
	
	//OSD230SeqSend(RecRow,RecCol,_LTriAngle,1);
	//OSD230SeqSend(RecRow,RecCol+1+12,_RTriAngle,1);
	
	temp=(42*RecData);
	temp=temp/(RecMax-RecMin);
	
	OSD230RowSend(RecRow);
	OSD230ColSend(RecCol+1);
	HighOSDArea = 0;
	
	if(temp==0) OSD230SeqSend(RecRow,RecCol+1,_3LBarNull,14);
	else
	
	while(1)
	{
		if(temp >3)		{OSD230DataSend(_3LBarFull);}
		else if(temp==3)	{OSD230DataSend(_3LBarFull);}
		else if(temp==2)	{OSD230DataSend(_3LBarL2);}
		else if(temp==1)	{OSD230DataSend(_3LBarL1);}
		
		temp=(temp-3);
		++index;
		if(temp<=0)
		{
			while(index<14)
			{
				++index;
				OSD230DataSend(_3LBarNull);
			}
			break;
		}	
	}
	
}
#endif

void DisplayPercent(BYTE Recdata0,BYTE Recdata1,BYTE Recdata2,BYTE Recdata3,BYTE Recdata4)	
{			//  Min,	Max,		data,		Row,	   Col
	WORD temp;
	BYTE count=0;
	BYTE index=0;
	
	temp = (WORD)(Recdata2*100);
	temp = (BYTE)(temp/(Recdata1-Recdata0));
	
	#ifndef OsdMenuFullBar//--------------------
	#ifdef	ValuePercentChar_Blue
		OSD230SeqSend(Recdata3|0x40,Recdata4,OSD_BLUE,3);//attribute!!
	#else
		OSD230SeqSend(Recdata3|0x40,Recdata4,OSD_RED,3);//attribute
	#endif
	#else	//----------------------------------
	#endif	//----------------------------------
	
	#ifndef	PercentDigitArray
	OSD230RowSend(Recdata3);
	OSD230ColSend(Recdata4);
	#endif
	
	count = calToChar(temp);
	HighOSDArea=0;//Low Display data.
	
	#ifdef	PercentDigitArray
	switch(count)
	{
		case 1:
			OSD230RowSend(Recdata3);
			OSD230ColSend(Recdata4+1);
			OSD230DataSend(0x00);//clear next(00)->(0)
			break;
		
		case 2:
			OSD230RowSend(Recdata3);
			OSD230ColSend(Recdata4+0);
			OSD230DataSend(0x00);//clear next(00)->(0)
			break;
		
		case 3:
			OSD230RowSend(Recdata3);
			OSD230ColSend(Recdata4);
			break;	
	}
	#endif
	
	//----------------------------------------------------------------
	#if 1		//2003-04-23 by thkim	// % 숫자 오른쪽 정렬 표시
	//----------------------------------------------------------------
		OSD230SeqSend(Recdata3,Recdata4,0x00,(3-count));
		OSD230ColSend(Recdata4+(3-count));
		while(count--)
		{
			OSD230DataSend(CalBuffer[index]+0x01);
			index++;
		}
	#else	//--------------------------------------------------------
		while(count--)			// % 숫자 왼쪽 정렬 표시
		{
			OSD230DataSend(CalBuffer[index]+0x01);
			index++;
		}
	#endif	//--------------------------------------------------------	


	#ifndef	PercentDigitArray
	OSD230DataSend(0x00);//clear next(00)->(0)
	#endif
	
	// Up/Down을 위해 버퍼에 항상 넣어둔다.
	MenuVal =  Recdata2;
	MenuMaxVal=Recdata1;
	MenuMinVal=Recdata0;
}

void DisplayPercent2(BYTE RecMin,BYTE RecMax,BYTE Recdata,BYTE RecRow,BYTE RecCol,BYTE RecColor)	//2003-04-23
{
	idata WORD temp;
	BYTE count=0;
	BYTE index=0;
	
	temp = (WORD)(Recdata*100);
	temp = (BYTE)(temp/(RecMax-RecMin));
	
	OSD230SeqSend(RecRow|0x40,RecCol,RecColor,3);//attribute!!
	
	#ifndef	PercentDigitArray
	OSD230RowSend(RecRow);
	OSD230ColSend(RecCol);
	#endif
	
	count = calToChar(temp);
	HighOSDArea=0;//Low Display data.
	
	#ifdef	PercentDigitArray
	switch(count)
	{
		case 1:
			OSD230RowSend(RecRow);
			OSD230ColSend(RecCol+1);
			OSD230DataSend(0x00);//clear next(00)->(0)
			break;
		
		case 2:
			OSD230RowSend(RecRow);
			OSD230ColSend(RecCol+0);
			OSD230DataSend(0x00);//clear next(00)->(0)
			break;
		
		case 3:
			OSD230RowSend(RecRow);
			OSD230ColSend(RecCol);
			break;	
	}
	#endif
	
	//----------------------------------------------------------------
	#if 1		//2003-04-23 by thkim	// % 숫자 오른쪽 정렬 표시
	//----------------------------------------------------------------
		OSD230SeqSend(RecRow,RecCol,0x00,(3-count));
		OSD230ColSend(RecCol+(3-count));
		while(count--)
		{
			OSD230DataSend(CalBuffer[index]+0x01);
			index++;
		}
	#else	//--------------------------------------------------------
		while(count--)			// % 숫자 왼쪽 정렬 표시
		{
			OSD230DataSend(CalBuffer[index]+0x01);
			index++;
		}
	#endif	//--------------------------------------------------------	


	#ifndef	PercentDigitArray
	OSD230DataSend(0x00);//clear next(00)->(0)
	#endif
	
	// Up/Down을 위해 버퍼에 항상 넣어둔다.
	MenuVal =  Recdata;
	MenuMaxVal=RecMax;
	MenuMinVal=RecMin;
}

#if 0	//test
void DisplayPercentWord(BYTE RecMin,WORD RecMax,WORD Recdata,BYTE RecRow,BYTE RecCol,BYTE RecColor)
{
	idata WORD temp;
	idata BYTE count=0;
	idata BYTE index=0;
	
	temp = (WORD)(Recdata*100);
	temp = (WORD)(temp/(RecMax-RecMin));
	OSD230SeqSend(RecRow|0x40,RecCol,RecColor,3);//attribute!!

	#ifndef	PercentDigitArray
	OSD230RowSend(RecRow);
	OSD230ColSend(RecCol);
	#endif
	
	count = calToChar(temp);
	HighOSDArea=0;//Low Display data.
	
	#ifdef	PercentDigitArray
	switch(count)
	{
		case 1:
			OSD230RowSend(RecRow);
			OSD230ColSend(RecCol+1);
			OSD230DataSend(0x00);//clear next(00)->(0)
			break;
		
		case 2:
			OSD230RowSend(RecRow);
			OSD230ColSend(RecCol+0);
			OSD230DataSend(0x00);//clear next(00)->(0)
			break;
		
		case 3:
			OSD230RowSend(RecRow);
			OSD230ColSend(RecCol);
			break;	
	}
	#endif
	
	//----------------------------------------------------------------
	#if 1		//2003-04-23 by thkim	// % 숫자 오른쪽 정렬 표시
	//----------------------------------------------------------------
		OSD230SeqSend(RecRow,RecCol,0x00,(3-count));
		OSD230ColSend(RecCol+(3-count));
		while(count--)
		{
			OSD230DataSend(CalBuffer[index]+0x01);
			index++;
		}
	#else	//--------------------------------------------------------
		while(count--)			// % 숫자 왼쪽 정렬 표시
		{
			OSD230DataSend(CalBuffer[index]+0x01);
			index++;
		}
	#endif	//--------------------------------------------------------	


	#ifndef	PercentDigitArray
	OSD230DataSend(0x00);//clear next(00)->(0)
	#endif
	
	// Up/Down을 위해 버퍼에 항상 넣어둔다.
	WordMenuVal =  Recdata;
	WordMenuMaxVal=RecMax;
	MenuMinVal=RecMin;
}
#endif

void	DisplayInfo(BYTE count)		//2003-04-15 by thkim
{
	BYTE index;
	
	HighOSDArea=0;	//Low Display data.
	index = 0;
	while(count--)
	{
		OSD230DataSend(CalBuffer[index]+0x01);
		index++;
	}
}

void OSDAngleDraw(BYTE Row,BYTE colum,BYTE size)
{
	OSD230SeqSend(Row,colum,_LTriAngle,1);
	OSD230SeqSend(Row,CII_COL25,_RTriAngle,1);
	OSD230SeqSend(Row,colum+1,0x00,size);
}	

void	ColorTempFunc(void)	//2003-04-29
{
	BYTE idata position=0;
	BYTE idata total_size=0;
	
	MenuMinVal=CT_WARM;
	MenuMaxVal=CT_USER;
	MenuVal=xEEPROMBuffer[ColorTemp];
	
	total_size=CII_COL25-CII_COL12-1;

	OSDAngleDraw(DSP_ROW7,CII_COL12,total_size);
//	OSD230SeqSend(DSP_ROW7,CII_COL12,_LTriAngle,1);
//	OSD230SeqSend(DSP_ROW7,CII_COL25,_RTriAngle,1);
//	OSD230SeqSend(DSP_ROW7,CII_COL13,0x00,total_size);
	//OSD230ColSend(CII_COL15);

	if(xEEPROMBuffer[LANGUAGE_buf]!=English) HighOSDArea=1;	// +jwshin 040730
	else HighOSDArea=0;
	
	switch(xEEPROMBuffer[ColorTemp])
	{
	#ifdef  USE_PALSECAMtuner				//color temperature cahr. 가운데 정렬
								// Chinese,English Font Apply... 040731 +jwshin
		case CT_WARM:
			OSD230PtrSend(DSP_ROW7,CII_COL13+(total_size-CTwarm_Sizeof[xEEPROMBuffer[LANGUAGE_buf]])/2,CTwarm[xEEPROMBuffer[LANGUAGE_buf]],CTwarm_Sizeof[xEEPROMBuffer[LANGUAGE_buf]]);
			break;
        	case CT_STANDARD:
			OSD230PtrSend(DSP_ROW7,CII_COL13+(total_size-CTstandard_Sizeof[xEEPROMBuffer[LANGUAGE_buf]])/2,CTstandard[xEEPROMBuffer[LANGUAGE_buf]],CTstandard_Sizeof[xEEPROMBuffer[LANGUAGE_buf]]);
			break;
		case CT_COOL:
			OSD230PtrSend(DSP_ROW7,CII_COL13+(total_size-CTcool_Sizeof[xEEPROMBuffer[LANGUAGE_buf]])/2,CTcool[xEEPROMBuffer[LANGUAGE_buf]],CTcool_Sizeof[xEEPROMBuffer[LANGUAGE_buf]]);
			break;
		case CT_USER:
			OSD230PtrSend(DSP_ROW7,CII_COL13+(total_size-User_Sizeof[xEEPROMBuffer[LANGUAGE_buf]])/2,User[xEEPROMBuffer[LANGUAGE_buf]],User_Sizeof[xEEPROMBuffer[LANGUAGE_buf]]);
			//OSD230PtrSend(DSP_ROW7,CII_COL13+(total_size-sizeof(User))/2,User,sizeof(User));
			break;	
	#else				//color temperature cahr. 왼쪽 정렬
/*		case CT_WARM:
			OSD230PtrSend(DSP_ROW7,CII_COL14,CTwarm[0],CTwarm_Sizeof[0]);
			break;
        	case CT_STANDARD:
			OSD230PtrSend(DSP_ROW7,CII_COL14,CTstandard[0],CTstandard_Sizeof[0]);
			break;
		case CT_COOL:
			OSD230PtrSend(DSP_ROW7,CII_COL14,CTcool[0],CTcool_Sizeof[0]);
			break;
		case CT_USER:
			//OSD230PtrSend(DSP_ROW7,CII_COL13+(total_size-User_Sizeof[0])/2,User[0],User_Sizeof[0]);
			OSD230PtrSend(DSP_ROW7,CII_COL13+(total_size-sizeof(User))/2,User,sizeof(User)); */
	#endif
	}
	HighOSDArea=0;
}

void	LanguageFunc(void)	//2003-04-30
{
	BYTE idata position=0;
	BYTE idata total_size=0;

    #if defined (USE_NTSCtuner)
	MenuMinVal=English;
	MenuMaxVal=Japan;
    #elif defined (USE_PALSECAMtuner)
	MenuMinVal=English;
	MenuMaxVal=China;
	//MenuMaxVal=English;	//임시 변경//2003-12-24 1:49오후
    #endif
	
	MenuVal=xEEPROMBuffer[LANGUAGE_buf];
	//MenuVal^=xEEPROMBuffer[LANGUAGE_buf];
    
	total_size=CII_COL25-CII_COL12-1;
	OSDAngleDraw(DSP_ROW3,CII_COL12,total_size);

	switch(xEEPROMBuffer[LANGUAGE_buf])
	{
	#if defined (USE_NTSCtuner)
				//color temperature cahr. 가운데 정렬
		case English:
			OSD230PtrSend(DSP_ROW3,CII_COL14+(total_size-LangEng_Sizeof[0])/2,LangEng[0],LangEng_Sizeof[0]);
			//LangSelect=English;//??
			break;
        	case Korea:
			OSD230PtrSend(DSP_ROW3,CII_COL14+(total_size-LangKor_Sizeof[0])/2,LangKor[0],LangKor_Sizeof[0]);	
			//LangSelect=Korea;//??
			break;
		case Japan:
			OSD230PtrSend(DSP_ROW3,CII_COL14+(total_size-LangJap_Sizeof[0])/2,LangJap[0],LangJap_Sizeof[0]);
			//LangSelect=Japan;//??
			break;

	#elif defined (USE_PALSECAMtuner)
		case English:
			OSD230PtrSend(DSP_ROW3,CII_COL14+(total_size-LangEng_Sizeof[0])/2,LangEng[0],LangEng_Sizeof[0]);
			break;
/*        	case France:
			OSD230PtrSend(DSP_ROW3,CII_COL14+(total_size-LangFrance_Sizeof[0])/2,LangFrance[0],LangFrance_Sizeof[0]);
			break;
		case German:
			OSD230PtrSend(DSP_ROW3,CII_COL14+(total_size-LangGerman_Sizeof[0])/2,LangGerman[0],LangGerman_Sizeof[0]);
			break;
		case Italia:
			OSD230PtrSend(DSP_ROW3,CII_COL14+(total_size-LangItalia_Sizeof[0])/2,LangItalia[0],LangItalia_Sizeof[0]);
			break;
        	
		case Netherlands:
			OSD230PtrSend(DSP_ROW3,CII_COL14+(total_size-LangNetherlands_Sizeof[0])/2,LangNetherlands[0],LangNetherlands_Sizeof[0]);
			break;

		case Russia:
			OSD230PtrSend(DSP_ROW3,CII_COL14+(total_size-LangRussia_Sizeof[0])/2,LangRussia[0],LangRussia_Sizeof[0]);
			break;
*/
		case China:
			HighOSDArea=1;
			OSD230PtrSend(DSP_ROW3,CII_COL14+(total_size-LangChina_Sizeof[1])/2,LangChina[1],LangChina_Sizeof[1]);
			HighOSDArea=0;
			break;		
	#endif

	}
	Display_AdjustInfo();
}	

void	OnoffDisplayFunc(BYTE RecRow, BYTE RecCol, BYTE RecOnOffFlag)
{
	BYTE idata position=0;
	BYTE idata total_size=0;
	
	MenuMinVal=OffFlag;
	MenuMaxVal=OnFlag;
	MenuVal=RecOnOffFlag;	// On Off Flag
	total_size=CII_COL25-RecCol-1;
	
	if(TvMenuNum==tvmenu_channel_edit)
	{
		//OSD230SeqSend(RecRow,RecCol+1,0x00,total_size);
		if(!RecOnOffFlag)	OSD230PtrSend(RecRow,RecCol,Yes[0],Yes_Sizeof[0]);   
		else			OSD230PtrSend(RecRow,RecCol,No[0],No_Sizeof[0]);
	}
	else
	{
		OSDAngleDraw(RecRow,RecCol,total_size);
		//OSD230SeqSend(RecRow,RecCol,_LTriAngle,1);
		//OSD230SeqSend(RecRow,CII_COL25,_RTriAngle,1);
		//OSD230SeqSend(RecRow,RecCol+1,0x00,total_size);
					//cahr. 가운데 정렬
		
		if(xEEPROMBuffer[LANGUAGE_buf]!=English) HighOSDArea=1;
		else HighOSDArea=0;
		
		#if defined(USE_NTSCtuner)		
		HighOSDArea=0;
		if(RecOnOffFlag)	OSD230PtrSend(RecRow,RecCol+1+(total_size-On_Sizeof[0])/2,On[0],On_Sizeof[0]);
		else			OSD230PtrSend(RecRow,RecCol+1+(total_size-Off_Sizeof[0])/2,Off[0],Off_Sizeof[0]);
		#else
		if(RecOnOffFlag)	OSD230PtrSend(RecRow,RecCol+1+(total_size-On_Sizeof[xEEPROMBuffer[LANGUAGE_buf]])/2,On[xEEPROMBuffer[LANGUAGE_buf]],On_Sizeof[xEEPROMBuffer[LANGUAGE_buf]]);
		else			OSD230PtrSend(RecRow,RecCol+1+(total_size-Off_Sizeof[xEEPROMBuffer[LANGUAGE_buf]])/2,Off[xEEPROMBuffer[LANGUAGE_buf]],Off_Sizeof[xEEPROMBuffer[LANGUAGE_buf]]);		
		#endif
		
		HighOSDArea=0;
	}
}

void	PipOnoffFunc(BYTE RecRow, BYTE RecCol, BYTE RecOnOffFlag)
{
	BYTE idata position=0;
	BYTE idata total_size=0;
	
	//PipOnOffFlag=(xEEPROMBuffer[PIPEN_SOURCE_buf]&0x10)>>4;	
	
	MenuMinVal=OffFlag;
	MenuMaxVal=OnFlag;
	MenuVal=RecOnOffFlag;	// On Off Flag
	total_size=CII_COL25-RecCol-1;
	OSDAngleDraw(RecRow,RecCol,total_size);
	//OSD230SeqSend(RecRow,RecCol,_LTriAngle,1);
	//OSD230SeqSend(RecRow,CII_COL25,_RTriAngle,1);
	//OSD230SeqSend(RecRow,RecCol+1,0x00,total_size);
	
	//RecOnOffFlag ^=1;
				//cahr. 가운데 정렬
	if(xEEPROMBuffer[LANGUAGE_buf]!=English) HighOSDArea=1;
	else HighOSDArea=0;
		
	#if defined(USE_NTSCtuner)		
	HighOSDArea=0;
	if(RecOnOffFlag)	OSD230PtrSend(RecRow,RecCol+1+(total_size-On_Sizeof[0])/2,On[0],On_Sizeof[0]);
	else			OSD230PtrSend(RecRow,RecCol+1+(total_size-Off_Sizeof[0])/2,Off[0],Off_Sizeof[0]);
	#else
	if(RecOnOffFlag)	OSD230PtrSend(RecRow,RecCol+1+(total_size-On_Sizeof[xEEPROMBuffer[LANGUAGE_buf]])/2,On[xEEPROMBuffer[LANGUAGE_buf]],On_Sizeof[xEEPROMBuffer[LANGUAGE_buf]]);
	else			OSD230PtrSend(RecRow,RecCol+1+(total_size-Off_Sizeof[xEEPROMBuffer[LANGUAGE_buf]])/2,Off[xEEPROMBuffer[LANGUAGE_buf]],Off_Sizeof[xEEPROMBuffer[LANGUAGE_buf]]);
	#endif
	HighOSDArea=0;
}

void	DosmodeDisplay(BYTE RecRow, BYTE RecCol, BYTE DosmodeFlag)
{
	BYTE idata position=0;
	BYTE idata total_size=0;
	
	(BYTE)DosmodeFlag=xEEPROMBuffer[Dosmode_buf];
	
	//MenuMinVal=0;
	//MenuMaxVal=1;
	//MenuVal=DosmodeFlag;
	total_size=CII_COL25-RecCol-1;
	OSDAngleDraw(RecRow,RecCol,total_size);

	if(LangBuf !=English)
	{
		
		if(DosmodeFlag)
		{
			OSD230PtrSend(RecRow,RecCol+4,Dos720[0],Dos720_Sizeof[0]);
			HighOSDArea=1;
			OSD230PtrSend(RecRow,RecCol+8,Mode[LangBuf],Mode_Sizeof[LangBuf]);
		}
		else
		{
			OSD230PtrSend(RecRow,RecCol+4,Dos640[0],Dos640_Sizeof[0]);
			HighOSDArea=1;
			OSD230PtrSend(RecRow,RecCol+8,Mode[LangBuf],Mode_Sizeof[LangBuf]);
		}
	}
	else
	{
		HighOSDArea=0;
		if(DosmodeFlag)
		{
			OSD230PtrSend(RecRow,RecCol+3,Dos720[0],Dos720_Sizeof[0]);
			OSD230PtrSend(RecRow,RecCol+7,Mode[0],Mode_Sizeof[0]);
		}
		else
		{
			OSD230PtrSend(RecRow,RecCol+3,Dos640[0],Dos640_Sizeof[0]);
			OSD230PtrSend(RecRow,RecCol+7,Mode[0],Mode_Sizeof[0]);
		}
	}
	HighOSDArea=0;
}

void	AspectRatioFunc(BYTE RecRow, BYTE RecCol, BYTE AspectFlag)
{
	BYTE idata position=0;
	BYTE idata total_size=0;
	
	(BYTE)AspectFlag=xEEPROMBuffer[Aspect_buf]&&0x01;
	
	MenuMinVal=OffFlag;
	MenuMaxVal=OnFlag;
	MenuVal=AspectFlag;
	
	total_size=CII_COL25-RecCol-1;
	OSDAngleDraw(RecRow,RecCol,total_size);

				//cahr. 가운데 정렬
	if(AspectFlag)	OSD230PtrSend(RecRow,RecCol+1+(total_size-Aspect4_3_Sizeof[0])/2,Aspect4_3[0],Aspect4_3_Sizeof[0]);
	else			OSD230PtrSend(RecRow,RecCol+1+(total_size-sizeof(Wide_Eng))/2,Wide_Eng,sizeof(Wide_Eng));
}

void	PipSourceSelFunc(void)
{
	BYTE idata RecRow=DSP_ROW4;
	BYTE idata RecCol=CII_COL12;
	BYTE idata position=0;
	BYTE idata total_size=0;
	
//test2004-06-29	PipInputSource=xEEPROMBuffer[PIPEN_SOURCE_buf]&0x03;	//2003-07-31
	
	MenuMinVal=SourceComposite;
	MenuMaxVal=SourceTuner;
	MenuVal=PipInputSource;
	total_size=CII_COL25-RecCol-1;
	OSDAngleDraw(RecRow,RecCol,total_size);
	//OSD230SeqSend(RecRow,RecCol,_LTriAngle,1);
	//OSD230SeqSend(RecRow,CII_COL25,_RTriAngle,1);
	//OSD230SeqSend(RecRow,RecCol+1,0x00,total_size);
	//OSD230ColSend(CII_COL15);
	// --------------------------------------------- 040801 +jwshin modified....
	if(xEEPROMBuffer[LANGUAGE_buf]!=English) HighOSDArea=1;
	else HighOSDArea=0;
		
	switch(PipInputSource)
	{
				//color temperature cahr. 가운데 정렬
    	case SourceComposite:
			OSD230PtrSend(RecRow,RecCol+2+(total_size-Composite_Sizeof[LangBuf])/2,Composite[LangBuf],Composite_Sizeof[LangBuf]);
			//OSD230PtrSend(RecRow,RecCol+2+(total_size-Composite_Sizeof[0])/2,Composite[0],Composite_Sizeof[0]);
			break;
		case SourceSvideo:
			if(xEEPROMBuffer[LANGUAGE_buf]!=English)  {
				HighOSDArea=0;
				OSD230PtrSend(RecRow,RecCol+(total_size-SOnly_Sizeof[0])/2,SOnly[0],SOnly_Sizeof[0]);	
				HighOSDArea=1;
				OSD230PtrSend(RecRow,RecCol+3+(total_size-Svideo_Sizeof[LangBuf])/2,Svideo[LangBuf],Svideo_Sizeof[LangBuf]);		
			}
			else {
				HighOSDArea=0;
				OSD230PtrSend(RecRow,RecCol+2+(total_size-Svideo_Sizeof[LangBuf])/2,Svideo[LangBuf],Svideo_Sizeof[LangBuf]);
			}
			//OSD230PtrSend(RecRow,RecCol+2+(total_size-Svideo_Sizeof[0])/2,Svideo[0],Svideo_Sizeof[0]);
			break;
		case SourceTuner:
			OSD230PtrSend(RecRow,RecCol+2+(total_size-Tuner_Sizeof[LangBuf])/2,Tuner[LangBuf],Tuner_Sizeof[LangBuf]);
			//OSD230PtrSend(RecRow,RecCol+2+(total_size-Tuner_Sizeof[0])/2,Tuner[0],Tuner_Sizeof[0]);
			break;
	}
	HighOSDArea=0;
}	

void	PipSizeSelFunc(void)
{
	BYTE idata RecRow=DSP_ROW5;
	BYTE idata RecCol=CII_COL12;
	BYTE idata position=0;
	BYTE idata total_size=0;
	
	PipSizeNum=xEEPROMBuffer[PIPSIZE_buf]&0x03;
	
	MenuMinVal=SizeLarge;
	MenuMaxVal=SizeSmall;
	MenuVal=PipSizeNum;
	total_size=CII_COL25-RecCol-1;
	OSDAngleDraw(RecRow,RecCol,total_size);
	//OSD230SeqSend(RecRow,RecCol,_LTriAngle,1);
	//OSD230SeqSend(RecRow,CII_COL25,_RTriAngle,1);
	//OSD230SeqSend(RecRow,RecCol+1,0x00,total_size);
	//OSD230ColSend(CII_COL15);

	#ifndef USE_NTSCTuner
	if(xEEPROMBuffer[LANGUAGE_buf]!=English) HighOSDArea=1;
	else HighOSDArea=0;
	#endif

	switch(PipSizeNum)
	{
		#ifdef USE_NTSCTuner
				//color temperature cahr. 가운데 정렬
		case SizeLarge:
			OSD230PtrSend(RecRow,RecCol+2+(total_size-Large_Sizeof[0])/2,Large[0],Large_Sizeof[0]);
			break;
        	case SizeMiddle:
			OSD230PtrSend(RecRow,RecCol+2+(total_size-Middle_Sizeof[0])/2,Middle[0],Middle_Sizeof[0]);
			break;
		case SizeSmall:
			OSD230PtrSend(RecRow,RecCol+2+(total_size-Small_Sizeof[0])/2,Small[0],Small_Sizeof[0]);
			break;
		#else	
		case SizeLarge:
			OSD230PtrSend(RecRow,RecCol+2+(total_size-Large_Sizeof[LangBuf])/2,Large[LangBuf],Large_Sizeof[LangBuf]);
			break;
        	case SizeMiddle:
			OSD230PtrSend(RecRow,RecCol+2+(total_size-Middle_Sizeof[LangBuf])/2,Middle[LangBuf],Middle_Sizeof[LangBuf]);
			break;
		case SizeSmall:
			OSD230PtrSend(RecRow,RecCol+2+(total_size-Small_Sizeof[LangBuf])/2,Small[LangBuf],Small_Sizeof[LangBuf]);
			break;
		#endif
	}
	HighOSDArea=0;
}	

void	PipAspectSelFunc(void)
{
	BYTE idata RecRow=DSP_ROW8;
	BYTE idata RecCol=CII_COL12;
	BYTE idata position=0;
	BYTE idata total_size=0;
	
	//(BYTE)PipAspectFlag=(xEEPROMBuffer[PIPSIZE_buf]&0x10)>>4;
	
	MenuMinVal=aspect4_3;
	MenuMaxVal=aspect16_9;
	MenuVal=PipAspectFlag;
	total_size=CII_COL25-RecCol-1;
	OSDAngleDraw(RecRow,RecCol,total_size);
	//OSD230SeqSend(RecRow,RecCol,_LTriAngle,1);
	//OSD230SeqSend(RecRow,CII_COL25,_RTriAngle,1);
	//OSD230SeqSend(RecRow,RecCol+1,0x00,total_size);

	switch((BYTE)PipAspectFlag)
	{
				//color temperature cahr. 가운데 정렬
		case aspect4_3:
			OSD230PtrSend(RecRow,RecCol+2+(total_size-Aspect4_3_Sizeof[0])/2,Aspect4_3[0],Aspect4_3_Sizeof[0]);
			break;
        	case aspect16_9:
			OSD230PtrSend(RecRow,RecCol+1+(total_size-Aspect16_9_Sizeof[0])/2,Aspect16_9[0],Aspect16_9_Sizeof[0]);
			break;
	}
}	


void	PipHPosSelFunc(void)
{
	BYTE idata RecRow=DSP_ROW6;
	BYTE idata RecCol=CII_COL12;
	BYTE idata position=0;
	BYTE idata total_size=0;
	
	MenuMinVal=LeftPosition;
	MenuMaxVal=RightPosition;
	MenuVal=PipHPositionNum;
	total_size=CII_COL25-RecCol-1;
	OSDAngleDraw(RecRow,RecCol,total_size);
	//OSD230SeqSend(RecRow,RecCol,_LTriAngle,1);
	//OSD230SeqSend(RecRow,CII_COL25,_RTriAngle,1);
	//OSD230SeqSend(RecRow,RecCol+1,0x00,total_size);

	#ifndef USE_NTSCTuner
	if(xEEPROMBuffer[LANGUAGE_buf]!=English) HighOSDArea=1;
	else HighOSDArea=0;
	#endif
	switch(PipHPositionNum)
	{
				//color temperature cahr. 가운데 정렬
		#ifdef USE_PALSECAMtuner
		case LeftPosition:
			OSD230PtrSend(RecRow,RecCol+2+(total_size-Left_Sizeof[LangBuf])/2,Left[LangBuf],Left_Sizeof[LangBuf]);
			break;
        case CenterPos:
			OSD230PtrSend(RecRow,RecCol+2+(total_size-Center_Sizeof[LangBuf])/2,Center[LangBuf],Center_Sizeof[LangBuf]);
			break;
		case RightPosition:
			OSD230PtrSend(RecRow,RecCol+2+(total_size-Right_Sizeof[LangBuf])/2,Right[LangBuf],Right_Sizeof[LangBuf]);
			break;
		#else
		case LeftPosition:
			OSD230PtrSend(RecRow,RecCol+2+(total_size-sizeof(Left))/2,Left,sizeof(Left));
			break;
        case CenterPos:
			OSD230PtrSend(RecRow,RecCol+2+(total_size-sizeof(Center))/2,Center,sizeof(Center));
			break;
		case RightPosition:
			OSD230PtrSend(RecRow,RecCol+2+(total_size-sizeof(Right))/2,Right,sizeof(Right));
			break;
		#endif
	}
	HighOSDArea=0;
}

void	PipVPosSelFunc(void)
{
	BYTE idata RecRow=DSP_ROW7;
	BYTE idata RecCol=CII_COL12;
	BYTE idata position=0;
	BYTE idata total_size=0;
	
	MenuMinVal=TopPosition;
	MenuMaxVal=BottomPosition;
	MenuVal=PipVPositionNum;
	total_size=CII_COL25-RecCol-1;
	OSDAngleDraw(RecRow,RecCol,total_size);
	//OSD230SeqSend(RecRow,RecCol,_LTriAngle,1);
	//OSD230SeqSend(RecRow,CII_COL25,_RTriAngle,1);
	//OSD230SeqSend(RecRow,RecCol+1,0x00,total_size);

	#ifndef USE_NTSCTuner
	if(xEEPROMBuffer[LANGUAGE_buf]!=English) HighOSDArea=1;
	else HighOSDArea=0;
	#endif
	
	switch(PipVPositionNum)
	{
		#ifdef USE_NTSCTuner
				//color temperature cahr. 가운데 정렬
		case TopPosition:
			OSD230PtrSend(RecRow,RecCol+2+(total_size-Top_Sizeof[0])/2,Top[0],Top_Sizeof[0]);
			break;
        	case MidPos:
			OSD230PtrSend(RecRow,RecCol+2+(total_size-Middle_Sizeof[0])/2,Middle[0],Middle_Sizeof[0]);
			break;
		case BottomPosition:
			OSD230PtrSend(RecRow,RecCol+2+(total_size-Bottom_Sizeof[0])/2,Bottom[0],Bottom_Sizeof[0]);
			break;
		#else
		case TopPosition:
			OSD230PtrSend(RecRow,RecCol+2+(total_size-Top_Sizeof[LangBuf])/2,Top[LangBuf],Top_Sizeof[LangBuf]);
			break;
        	case MidPos:
			OSD230PtrSend(RecRow,RecCol+2+(total_size-Middle_Sizeof[LangBuf])/2,Middle[LangBuf],Middle_Sizeof[LangBuf]);
			break;
		case BottomPosition:
			OSD230PtrSend(RecRow,RecCol+2+(total_size-Bottom_Sizeof[LangBuf])/2,Bottom[LangBuf],Bottom_Sizeof[LangBuf]);
			break;
		#endif
	}
	HighOSDArea=0;
}	

void	PipBlendSelFunc(void)
{
	MenuMinVal=0;
	MenuMaxVal=3;
	MenuVal=xEEPROMBuffer[PIPBLEND_buf];
	
	#ifdef OsdMenuType1
		#if defined(OsdColor_Red)
	if( (MenuNum==menu_pip_blend)&&(OsdGrade==2) ) DisplayPercent2(MenuMinVal,MenuMaxVal,xEEPROMBuffer[PIPBLEND_buf],DSP_ROW9,CII_COL7,OSD_RED_BG|OSD_WHITE);
		#else
	if( (MenuNum==menu_pip_blend)&&(OsdGrade==2) ) DisplayPercent2(MenuMinVal,MenuMaxVal,xEEPROMBuffer[PIPBLEND_buf],DSP_ROW9,CII_COL7,OSD_BLUE_BG|OSD_WHITE);
		#endif
	else	DisplayPercent2(MenuMinVal,MenuMaxVal,xEEPROMBuffer[PIPBLEND_buf],DSP_ROW9,CII_COL7,OSD_BLACK);
	#else
	if( (MenuNum==menu_pip_blend)&&(OsdGrade==2) ) DisplayPercent(MenuMinVal,MenuMaxVal,xEEPROMBuffer[PIPBLEND_buf],DSP_ROW9,CII_COL7);
	else	DisplayPercent(MenuMinVal,MenuMaxVal,xEEPROMBuffer[PIPBLEND_buf],DSP_ROW9,CII_COL7);
	#endif
	Displaybar2(MenuMinVal,MenuMaxVal,xEEPROMBuffer[PIPBLEND_buf],DSP_ROW9,CII_COL11);
}

void	SmartPicCtrFunc(void)
{
	BYTE idata position=0;
	BYTE idata total_size=0;
	
	MenuMinVal=SPCNormal;
	MenuMaxVal=SPCUser;
	MenuVal=xEEPROMBuffer[SmartPicCtr_buf];
	total_size=CII_COL25-CII_COL12-1;
	OSDAngleDraw(DSP_ROW8,CII_COL12,total_size);
	//OSD230SeqSend(DSP_ROW8,CII_COL12,_LTriAngle,1);
	//OSD230SeqSend(DSP_ROW8,CII_COL25,_RTriAngle,1);
	//OSD230SeqSend(DSP_ROW8,CII_COL13,0x00,total_size);

	if(xEEPROMBuffer[LANGUAGE_buf]!=English) HighOSDArea=1;
	else HighOSDArea=0;
	switch(xEEPROMBuffer[SmartPicCtr_buf])
	{
				//color temperature cahr. 가운데 정렬
		#ifdef USE_NTSCtuner
		case SPCNormal:
			OSD230PtrSend(DSP_ROW8,CII_COL13+(total_size-sizeof(Normal))/2,Normal,sizeof(Normal));
			break;                
        	case SPCDynamic:              
			OSD230PtrSend(DSP_ROW8,CII_COL13+(total_size-sizeof(Dynamic))/2,Dynamic,sizeof(Dynamic));
			break;                
		case SPCCinema:               
			OSD230PtrSend(DSP_ROW8,CII_COL13+(total_size-sizeof(Cinema))/2,Cinema,sizeof(Cinema));
			break;                
		case SPCUser:                 
			OSD230PtrSend(DSP_ROW8,CII_COL13+(total_size-sizeof(User))/2,User,sizeof(User));
			break;
		#else
		case SPCNormal:
			OSD230PtrSend(DSP_ROW8,CII_COL13+(total_size-Normal_Sizeof[xEEPROMBuffer[LANGUAGE_buf]])/2,Normal[xEEPROMBuffer[LANGUAGE_buf]],Normal_Sizeof[xEEPROMBuffer[LANGUAGE_buf]]);
			break;                
        	case SPCDynamic:              
			OSD230PtrSend(DSP_ROW8,CII_COL13+(total_size-Dynamic_Sizeof[xEEPROMBuffer[LANGUAGE_buf]])/2,Dynamic[xEEPROMBuffer[LANGUAGE_buf]],Dynamic_Sizeof[xEEPROMBuffer[LANGUAGE_buf]]);
			break;                
		case SPCCinema:               
			OSD230PtrSend(DSP_ROW8,CII_COL13+(total_size-Cinema_Sizeof[xEEPROMBuffer[LANGUAGE_buf]])/2,Cinema[xEEPROMBuffer[LANGUAGE_buf]],Cinema_Sizeof[xEEPROMBuffer[LANGUAGE_buf]]);
			break;                
		case SPCUser:                 
			OSD230PtrSend(DSP_ROW8,CII_COL13+(total_size-User_Sizeof[xEEPROMBuffer[LANGUAGE_buf]])/2,User[xEEPROMBuffer[LANGUAGE_buf]],User_Sizeof[xEEPROMBuffer[LANGUAGE_buf]]);
			break;
		#endif
	}
	HighOSDArea=0;
}	

// smpark 
void	SmartSoundCtrFunc(void)
{
	BYTE idata position=0;
	BYTE idata total_size=0;
	
	MenuMinVal=SSCNormal;
	MenuMaxVal=SSCUser;
	MenuVal=xEEPROMBuffer[SSC];
	total_size=CII_COL25-CII_COL12-1;
	OSDAngleDraw(DSP_ROW6,CII_COL12,total_size);
	//OSD230SeqSend(DSP_ROW6,CII_COL12,_LTriAngle,1);
	//OSD230SeqSend(DSP_ROW6,CII_COL25,_RTriAngle,1);
	//OSD230SeqSend(DSP_ROW6,CII_COL13,0x00,total_size);
	
	if(xEEPROMBuffer[LANGUAGE_buf]!=English) HighOSDArea=1;
	else HighOSDArea=0;
	switch(xEEPROMBuffer[SSC])
	{
				//color temperature cahr. 가운데 정렬
		#ifdef USE_NTSCtuner
		case SSCNormal:
			OSD230PtrSend(DSP_ROW6,CII_COL13+(total_size-sizeof(Normal))/2,Normal,sizeof(Normal));
			break;
        	case SSCMusic:
			OSD230PtrSend(DSP_ROW6,CII_COL13+(total_size-sizeof(Music))/2,Music,sizeof(Music));
			break;
		case SSCCinema:
			OSD230PtrSend(DSP_ROW6,CII_COL13+(total_size-sizeof(Cinema))/2,Cinema,sizeof(Cinema));
			break;
		case SSCNews:
			OSD230PtrSend(DSP_ROW6,CII_COL13+(total_size-sizeof(News))/2,News,sizeof(News));
			break;
		case SSCUser:
			OSD230PtrSend(DSP_ROW6,CII_COL13+(total_size-sizeof(User))/2,User,sizeof(User));
			break;
		#else	//old
		case SSCNormal:
			OSD230PtrSend(DSP_ROW6,CII_COL13+(total_size-Normal_Sizeof[xEEPROMBuffer[LANGUAGE_buf]])/2,Normal[xEEPROMBuffer[LANGUAGE_buf]],Normal_Sizeof[xEEPROMBuffer[LANGUAGE_buf]]);
			break;
        	case SSCMusic:
			OSD230PtrSend(DSP_ROW6,CII_COL13+(total_size-Music_Sizeof[xEEPROMBuffer[LANGUAGE_buf]])/2,Music[xEEPROMBuffer[LANGUAGE_buf]],Music_Sizeof[xEEPROMBuffer[LANGUAGE_buf]]);
			break;
		case SSCCinema:
			OSD230PtrSend(DSP_ROW6,CII_COL13+(total_size-Cinema_Sizeof[xEEPROMBuffer[LANGUAGE_buf]])/2,Cinema[xEEPROMBuffer[LANGUAGE_buf]],Cinema_Sizeof[xEEPROMBuffer[LANGUAGE_buf]]);
			break;
		case SSCNews:		//+jwshin 040801
			OSD230PtrSend(DSP_ROW6,CII_COL13+(total_size-News_Sizeof[xEEPROMBuffer[LANGUAGE_buf]])/2,News[xEEPROMBuffer[LANGUAGE_buf]],News_Sizeof[xEEPROMBuffer[LANGUAGE_buf]]);
			break;
		case SSCUser:
			OSD230PtrSend(DSP_ROW6,CII_COL13+(total_size-User_Sizeof[xEEPROMBuffer[LANGUAGE_buf]])/2,User[xEEPROMBuffer[LANGUAGE_buf]],User_Sizeof[xEEPROMBuffer[LANGUAGE_buf]]);
			break;
		#endif
	}
	HighOSDArea=0;
}	

/*
void	MTSFunc(void)
{
	BYTE idata position=0;
	BYTE idata total_size=0;
	
	MenuMinVal=MTSMono;
	MenuMaxVal=MTSBilingual;
	MenuVal=xEEPROMBuffer[MTS];
	total_size=CII_COL25-CII_COL12-1;
	
	OSD230SeqSend(DSP_ROW7,CII_COL12,_LTriAngle,1);
	OSD230SeqSend(DSP_ROW7,CII_COL25,_RTriAngle,1);
	OSD230SeqSend(DSP_ROW7,CII_COL13,0x00,total_size);

	switch(xEEPROMBuffer[MTS])
	{
				//color temperature cahr. 가운데 정렬
		case MTSMono:
			OSD230PtrSend(DSP_ROW7,CII_COL13+(total_size-Mono_Sizeof[0])/2,Mono[0],Mono_Sizeof[0]);
			break;
        	case MTSStereo:
			OSD230PtrSend(DSP_ROW7,CII_COL13+(total_size-Stereo_Sizeof[0])/2,Stereo[0],Stereo_Sizeof[0]);
			break;
		case MTSBilingual:
			OSD230PtrSend(DSP_ROW7,CII_COL13+(total_size-Bilingual_Sizeof[0])/2,Bilingual[0],Bilingual_Sizeof[0]);
			break;
	}
}	
*/

#if 0
void	WideOnFunc(void)
{
	BYTE idata position=0;
	BYTE idata total_size=0;
	
	MenuMinVal=ScrNormal;
	MenuMaxVal=ScrWide;
	MenuVal=xEEPROMBuffer[WideModeFlag_buf];
	total_size=CII_COL25-CII_COL12-1;
	
	OSD230SeqSend(DSP_ROW5,CII_COL12,_LTriAngle,1);
	OSD230SeqSend(DSP_ROW5,CII_COL25,_RTriAngle,1);
	OSD230SeqSend(DSP_ROW5,CII_COL13,0x00,total_size);

	switch(xEEPROMBuffer[WideModeFlag_buf]) {
				//color temperature cahr. 가운데 정렬
		case ScrNormal:
			OSD230PtrSend(DSP_ROW5,CII_COL13+(total_size-Normal_Sizeof[0])/2,Normal[0],Normal_Sizeof[0]);
			break;
        	case ScrWide:
			OSD230PtrSend(DSP_ROW5,CII_COL13+(total_size-Wide_Sizeof[0])/2,Wide[0],Wide_Sizeof[0]);
			break;
	}
}	
#endif

void	SleepFunc(void)
{
	BYTE temp0=0, temp1=0;
	
	MenuMinVal=Sleep_min;
	MenuMaxVal=Sleep_max;
	MenuVal=xEEPROMBuffer[Sleep_buf];

	OSDAngleDraw(DSP_ROW6,CII_COL12,CII_COL25-CII_COL12-1);
	//OSD230SeqSend(DSP_ROW6,CII_COL12,_LTriAngle,1);
	//OSD230SeqSend(DSP_ROW6,CII_COL25,_RTriAngle,1);
	OSD230ColSend(CII_COL15);
	OSD230DataSend(0x00);
	temp0 = calToChar(xEEPROMBuffer[Sleep_buf]);
	HighOSDArea=0;//Low Display data.
	temp1 = 0;
	

	if(temp0==1)
	{
		OSD230SeqSend2(DSP_ROW6,CII_COL15+(3-temp0-1),_minus,_minus);
		//OSD230SeqSend2(DSP_ROW7,CII_COL15+(3-temp0-1),_minus,0);
	}
	else
	{		
		OSD230SeqSend(DSP_ROW6,CII_COL15,0x00,(3-temp0));
		OSD230ColSend(CII_COL15+(3-temp0));
		while(temp0--)
		{
			OSD230DataSend(CalBuffer[temp1]+0x01);
			temp1++;
		}
	}
	if(xEEPROMBuffer[LANGUAGE_buf]!=English) HighOSDArea=1;
	else HighOSDArea=0;
		
	OSD230PtrSend(DSP_ROW6,CII_COL19,Minute[xEEPROMBuffer[LANGUAGE_buf]],Minute_Sizeof[xEEPROMBuffer[LANGUAGE_buf]]);
	HighOSDArea=0;
}                         

#ifdef TempOsdMenu
void	TempOsdSelFunc(void)
{
	BYTE idata RecRow=DSP_ROW7;
	BYTE idata RecCol=CII_COL12;
	BYTE idata position=0;
	BYTE idata total_size=0;

	MenuMinVal=0;
	MenuMaxVal=TempOsdTotal;
	MenuVal=TempOsdNum;
	total_size=CII_COL25-RecCol-1;
	OSDAngleDraw(RecRow,RecCol,total_size);

	OSD230SeqSend(RecRow,RecCol+3,0x00,4); 		//Attribute data
	HighOSDArea=0;
	OSD230SeqSend2(RecRow,RecCol+4,_T,_Y); 		//Display data
	OSD230SeqSend2(RecRow,RecCol+6,_P,_E); 		//Display data
	
	switch(TempOsdNum)
	{
				//color temperature cahr. 가운데 정렬
		case 0:
			OSD230SeqSend2(RecRow,RecCol+8,_1,0); 		//Display data
			break;
        	case 1:
        		OSD230SeqSend2(RecRow,RecCol+8,_2,0); 		//Display data
			break;
        	case 2:
			OSD230SeqSend2(RecRow,RecCol+8,_3,0); 		//Display data
			break;
		case 3:
			OSD230SeqSend2(RecRow,RecCol+8,_4,0); 		//Display data
			break;
        	case 4:
        		OSD230SeqSend2(RecRow,RecCol+8,_5,0); 		//Display data
			break;
		case 5:
			OSD230SeqSend2(RecRow,RecCol+8,_6,0); 		//Display data
			break;
        	case 6:
        		OSD230SeqSend2(RecRow,RecCol+8,_7,0); 		//Display data
			break;
        	case 7:
			OSD230SeqSend2(RecRow,RecCol+8,_8,0); 		//Display data
			break;
		case 8:
			OSD230SeqSend2(RecRow,RecCol+8,_9,0); 		//Display data
			break;
        	case 9:
        		OSD230SeqSend2(RecRow,RecCol+8,_1,_0); 		//Display data
			break;
		case 10:
        		OSD230SeqSend2(RecRow,RecCol+8,_1,_1); 		//Display data
			break;
        	case 11:
        		OSD230SeqSend2(RecRow,RecCol+8,_1,_2); 		//Display data
			break;
        	case 12:
			OSD230SeqSend2(RecRow,RecCol+8,_1,_3); 		//Display data
			break;
        	case 13:
			OSD230SeqSend2(RecRow,RecCol+8,_1,_4); 		//Display data
			break;
        	case 14:
			OSD230SeqSend2(RecRow,RecCol+8,_1,_5); 		//Display data
			break;
        	case 15:
			OSD230SeqSend2(RecRow,RecCol+8,_1,_6); 		//Display data
			break;

	}
}     


void	TempOsdBlendFunc(void)
{
	OnoffDisplayFunc(DSP_ROW8,CII_COL12,xEEPROMBuffer[TempOsdBlend_buf]);
	if(xEEPROMBuffer[TempOsdBlend_buf])
	{
		//OSD230PtrSend(DSP_ROW8,CII_COL12+4,On[0],On_Sizeof[0]);
		WriteScaler(0x73,0x10);//IntOsd_Blend (high nibble: 0x0x(100%) 1x(75%) 2x(50%) 3x(25%) )
	}
	else	
	{
		//OSD230PtrSend(DSP_ROW8,CII_COL12+4,Off[0],Off_Sizeof[0]);
		WriteScaler(0x73,0x00);//IntOsd_Blend (high nibble: 0x0x(100%) 1x(75%) 2x(50%) 3x(25%) )
	}

}

#endif



#ifdef Ccd_Vchip
void	CcdCaptionSelFunc(void)
{
	BYTE idata RecRow=DSP_ROW5;
	BYTE idata RecCol=CII_COL17;
	BYTE idata position=0;
	BYTE idata total_size=0;

	
	if(CcdCaptionFlag) {LED_ON;}//CcdCaptionFlag=0;}
	else		{LED_OFF;}//CcdCaptionFlag=1;}
	
	OSD230SeqSend(RecRow,CII_COL15,_RTriAngle,1);
//	OSD230SeqSend(RecRow,RecCol+3,0x00,4); 		//Attribute data
	
	if(CcdCaptionFlag)	OSD230PtrSend(RecRow,RecCol,Yes[0],Yes_Sizeof[0]);   
	else			OSD230PtrSend(RecRow,RecCol,No[0],No_Sizeof[0]);
}
void	CcdModeSelFunc(void)
{
	BYTE idata RecRow=DSP_ROW6;
	BYTE idata RecCol=CII_COL17;
	BYTE idata position=0;
	BYTE idata total_size=0;
	OSD230SeqSend(RecRow,CII_COL15,_RTriAngle,1);

	if(CcdModeFlag)	OSD230PtrSend(RecRow,RecCol,CcdCaption[0],CcdCaption_Sizeof[0]);   
	else			OSD230PtrSend(RecRow,RecCol,CcdText[0],CcdText_Sizeof[0]);
}
void	CcdChannelSelFunc(void)
{
	BYTE idata RecRow=DSP_ROW7;
	BYTE idata RecCol=CII_COL17;
	BYTE idata position=0;
	BYTE idata total_size=0;
	OSD230SeqSend(RecRow,CII_COL15,_RTriAngle,1);
	if(CcdChannelFlag)	
	{
		OSD230SeqSend(RecRow,RecCol,0x00,6); 	//Attribute data
		OSD230SeqSend2(RecRow,RecCol,_1,0); 	//Display data
	}
	else
	{
		OSD230SeqSend(RecRow,RecCol,0x00,6); 	//Attribute data
		OSD230SeqSend2(RecRow,RecCol,_2,0); 	//Display data
	}
}
void	CcdFieldSelFunc(void)
{
	BYTE idata RecRow=DSP_ROW8;
	BYTE idata RecCol=CII_COL17;
	BYTE idata position=0;
	BYTE idata total_size=0;
	OSD230SeqSend(RecRow,CII_COL15,_RTriAngle,1);
	if(CcdFieldFlag)
	{
		OSD230SeqSend(RecRow,RecCol,0x00,6); 	//Attribute data
		OSD230SeqSend2(RecRow,RecCol,_1,0); 	//Display data
	}
	else
	{
		OSD230SeqSend(RecRow,RecCol,0x00,6); 	//Attribute data
		OSD230SeqSend2(RecRow,RecCol,_2,0); 	//Display data
	}
}
void	CcdDisplaySelFunc(void)
{
	BYTE idata RecRow=DSP_ROW9;
	BYTE idata RecCol=CII_COL17;
	BYTE idata position=0;
	BYTE idata total_size=0;
	OSD230SeqSend(RecRow,CII_COL15,_RTriAngle,1);
	if(CcdDisplayFlag)	OSD230PtrSend(RecRow,RecCol,CcdBox[0],CcdBox_Sizeof[0]);   
	else			OSD230PtrSend(RecRow,RecCol,CcdShadow[0],CcdShadow_Sizeof[0]);
}
#endif

void	TvAspectRatioSelFunc(void)
{
	BYTE idata RecRow=DSP_ROW5;
	BYTE idata RecCol=CII_COL12;
	BYTE idata position=0;
	BYTE idata total_size=0;
	
	DisplayAspectRatioNum=xEEPROMBuffer[DisplayAspcet_buf]&0x03;
	
	MenuMinVal=aspect4_3;
	MenuMaxVal=aspect_full;
	MenuVal=DisplayAspectRatioNum;
	total_size=CII_COL25-RecCol-1;
	OSDAngleDraw(RecRow,RecCol,total_size);
//	OSD230SeqSend(RecRow,RecCol,_LTriAngle,1);
//	OSD230SeqSend(RecRow,CII_COL25,_RTriAngle,1);
//	OSD230SeqSend(RecRow,RecCol+1,0x00,total_size);

	switch(DisplayAspectRatioNum)
	{
				//color temperature cahr. 가운데 정렬
		case aspect4_3:
			OSD230PtrSend(RecRow,RecCol+2+(total_size-Aspect4_3_Sizeof[0])/2,Aspect4_3[0],Aspect4_3_Sizeof[0]);
			break;
        	case aspect16_9:
			OSD230PtrSend(RecRow,RecCol+1+(total_size-Aspect16_9_Sizeof[0])/2,Aspect16_9[0],Aspect16_9_Sizeof[0]);
			break;
        	case aspect_full:
			
			if(xEEPROMBuffer[LANGUAGE_buf]!=English) HighOSDArea=1;
			else HighOSDArea=0;
			OSD230PtrSend(RecRow,RecCol+1+(total_size-Full_Sizeof[xEEPROMBuffer[LANGUAGE_buf]])/2,Full[xEEPROMBuffer[LANGUAGE_buf]],Full_Sizeof[xEEPROMBuffer[LANGUAGE_buf]]);
			HighOSDArea=0;
			break;
	}
}                     

void	StartCharDisplayFunc(BYTE RecRow, BYTE RecRowAttr)
{
	OSD230SeqSend(RecRow,CII_COL12,_LTriAngle,1);                       
	OSD230SeqSend(RecRow,CII_COL25,_RTriAngle,1);                       
	OSD230SeqSend(RecRowAttr,CII_COL1,0x00,6); 		//Attribute data
	
	if(xEEPROMBuffer[LANGUAGE_buf]!=English) HighOSDArea=1;
	else HighOSDArea=0;
	OSD230PtrSend(RecRow,CII_COL12+4,Start[xEEPROMBuffer[LANGUAGE_buf]],Start_Sizeof[xEEPROMBuffer[LANGUAGE_buf]]);
	HighOSDArea=0;
	
	//OSD230SeqSend2(RecRow,CII_COL12+4,_S,_T); 		//Display data
	//OSD230SeqSend2(RecRow,CII_COL12+6,_A,_R); 		//Display data
	//OSD230SeqSend2(RecRow,CII_COL12+8,_T,0); 		//Display data
}
        
#if defined (USE_NTSCtuner)
void	AntenaSelFunc(void)
{       
	BYTE idata position=0;
	BYTE idata total_size=0;
	
	MenuMinVal=AtnAir;
	MenuMaxVal=AtnCable;
	MenuVal=(BYTE)AntenaFlag;
	total_size=CII_COL25-CII_COL12-1;
	OSDAngleDraw(DSP_ROW6,CII_COL12,total_size);
	//OSD230SeqSend(DSP_ROW6,CII_COL12,_LTriAngle,1);
	//OSD230SeqSend(DSP_ROW6,CII_COL25,_RTriAngle,1);
	//OSD230SeqSend(DSP_ROW6,CII_COL13,0x00,total_size);

	switch((BYTE)AntenaFlag)
	{
				//color temperature cahr. 가운데 정렬
		case AtnAir:
		OSD230PtrSend(DSP_ROW6,CII_COL13+(total_size-Air_Sizeof[0])/2,Air[0],Air_Sizeof[0]);
		break;
        	case AtnCable:
		OSD230PtrSend(DSP_ROW6,CII_COL13+(total_size-Cable_Sizeof[0])/2,Cable[0],Cable_Sizeof[0]);
		break;
	}
}
#endif

void	Auto_Func(void)
{
	#if 1	//바로 auto hot message 표시/실행
		OsdAttrClear();
		OSDstatus = OsdRamClear;
		Osd_onoff();
		
	#else	//main menu 상에서 message 표시/실행
		OsdDataWindowClear();
		
		OSD230SeqSend(ATTR_ROW5,CII_COL0,OSD_BLUE,30);
		OSD230PtrSend(DSP_ROW5,CII_COL7,AutoAdjust[xEEPROMBuffer[LANGUAGE_buf]],AutoAdjust_Sizeof[xEEPROMBuffer[LANGUAGE_buf]]);
		
		OSD230SeqSend(ATTR_ROW6,CII_COL0+(29-Processing_Sizeof[xEEPROMBuffer[LANGUAGE_buf]])/2,OSD_BLUE,Processing_Sizeof[xEEPROMBuffer[LANGUAGE_buf]]);
		OSD230PtrSend(DSP_ROW6,CII_COL0+(29-Processing_Sizeof[xEEPROMBuffer[LANGUAGE_buf]])/2,Processing[xEEPROMBuffer[LANGUAGE_buf]],Processing_Sizeof[xEEPROMBuffer[LANGUAGE_buf]]);
	#endif
	AutoFlag = 1;
	PutData(); 
	DisplayMenuWindow();         
}
			

code BYTE BarTable[][5]={
	//	mim value	,max value		,Row	colum start, colum end
	ANALOGBRT_min		,ANALOGBRT_max		,DSP_ROW3,CII_COL7,CII_COL11,//ANALOGBRT
	ANALOGCONT_min		,ANALOGCONT_max		,DSP_ROW4,CII_COL7,CII_COL11,
	SharpValue_min		,SharpValue_max		,DSP_ROW5,CII_COL7,CII_COL11,
	PhaseValue_min		,PhaseValue_max		,DSP_ROW6,CII_COL7,CII_COL11,
	ClockValue_min		,ClockValue_max		,DSP_ROW7,CII_COL7,CII_COL11,//4//4
	HorizontalValue_min	,HorizontalValue_max	,DSP_ROW8,CII_COL7,CII_COL11,
	VerticalValue_min	,VerticalValue_max	,DSP_ROW9,CII_COL7,CII_COL11,

	WhiteBlcValue_min	,WhiteBlcValue_max	,DSP_ROW3,CII_COL7,CII_COL11,//7
	ADCREDGAIN_min		,ADCREDGAIN_max		,DSP_ROW4,CII_COL7,CII_COL11,//8
	ADCGREENGAIN_min	,ADCGREENGAIN_max	,DSP_ROW5,CII_COL7,CII_COL11,//9
	ADCBLUEGAIN_min		,ADCBLUEGAIN_max	,DSP_ROW6,CII_COL7,CII_COL11,//10
	OSDVpos_min			,OSDVpos_max		,DSP_ROW5,CII_COL7,CII_COL11,

	SOUND_TREBLE_min	,SOUND_TREBLE_max	,DSP_ROW3,CII_COL7,CII_COL11,
	SOUND_BASS_min		,SOUND_BASS_max		,DSP_ROW4,CII_COL7,CII_COL11,	//13
	SOUND_LOUDNESS_min	,SOUND_LOUDNESS_max	,DSP_ROW5,CII_COL7,CII_COL11,	//14

	COMPOSITEBRT_min	,COMPOSITEBRT_max	,DSP_ROW3,CII_COL7,CII_COL11,
	COMPOSITECONT_min	,COMPOSITECONT_max	,DSP_ROW4,CII_COL7,CII_COL11,//16
	COMPOSITESHARP_min	,COMPOSITESHARP_max	,DSP_ROW5,CII_COL7,CII_COL11,//17
	COMPOSITECOLOR_min	,COMPOSITECOLOR_max	,DSP_ROW6,CII_COL7,CII_COL11,//18
};

void BarAndPersent(BYTE tablevalue,BYTE value)
{
	DisplayPercent(BarTable[tablevalue][0],BarTable[tablevalue][1],value,BarTable[tablevalue][2],CII_COL7);//percent
	Displaybar2(BarTable[tablevalue][0],BarTable[tablevalue][1],value,BarTable[tablevalue][2],CII_COL11);//bar
	BarFlag=1;
}


void	Display_MenuBarPercent(void)	//menu bar & percent neumber display //2003-04-21
{
	BYTE xdata temp0=0;
	BYTE xdata temp1=0;
	if( (NowTopOsdOn)&&(xEEPROMBuffer[MainSubInputSource]!=10)&&(xEEPROMBuffer[MainSubInputSource]!=14)&&(xEEPROMBuffer[MainSubInputSource]!=18) )
	{
	
		switch(MenuNum)
		{
			case 	menu_brightness:
				BarAndPersent(0,xEEPROMBuffer[ANALOGBRT_buf]);
				//DisplayPercent(ANALOGBRT_min,ANALOGBRT_max,xEEPROMBuffer[ANALOGBRT_buf],DSP_ROW3,CII_COL7);//percent
				//Displaybar2(ANALOGBRT_min,ANALOGBRT_max,xEEPROMBuffer[ANALOGBRT_buf],DSP_ROW3,CII_COL11);//bar
				//BarFlag=1;
				break;
			case	menu_contrast:
				BarAndPersent(1,xEEPROMBuffer[ANALOGCONT]);
				//DisplayPercent(ANALOGCONT_min,ANALOGCONT_max,xEEPROMBuffer[ANALOGCONT],DSP_ROW4,CII_COL7);
				//Displaybar2(ANALOGCONT_min,ANALOGCONT_max,xEEPROMBuffer[ANALOGCONT],DSP_ROW4,CII_COL11);
				//BarFlag=1;
				break;
			case	menu_sharpness:
				BarAndPersent(2,xEEPROMBuffer[Sharpness_buf]);
				//DisplayPercent(SharpValue_min,SharpValue_max,xEEPROMBuffer[Sharpness_buf],DSP_ROW5,CII_COL7);//////
				//Displaybar2(SharpValue_min,SharpValue_max,xEEPROMBuffer[Sharpness_buf],DSP_ROW5,CII_COL11);
				//BarFlag=1;
				break;
			case	menu_phase:
				BarAndPersent(3,PhaseValue);
				//DisplayPercent(PhaseValue_min,PhaseValue_max,PhaseValue,DSP_ROW6,CII_COL7);
				//Displaybar2(PhaseValue_min,PhaseValue_max,PhaseValue,DSP_ROW6,CII_COL11);
				//BarFlag=1;
				break;			
			case	menu_clock:
				BarAndPersent(4,ClockValue);
				//DisplayPercent(ClockValue_min,ClockValue_max,ClockValue,DSP_ROW7,CII_COL7);
				//Displaybar2(ClockValue_min,ClockValue_max,ClockValue,DSP_ROW7,CII_COL11);
				//BarFlag=1;
				break;
			case	menu_Hposition:
				BarAndPersent(5,HorizontalValue);
				//DisplayPercent(HorizontalValue_min,HorizontalValue_max,HorizontalValue,DSP_ROW8,CII_COL7);
				//Displaybar2(HorizontalValue_min,HorizontalValue_max,HorizontalValue,DSP_ROW8,CII_COL11);
				//BarFlag=1;
				break;
			case	menu_Vposition:
				BarAndPersent(6,VerticalValue);
				//DisplayPercent(VerticalValue_min,VerticalValue_max,VerticalValue,DSP_ROW9,CII_COL7);
				//Displaybar2(VerticalValue_min,VerticalValue_max,VerticalValue,DSP_ROW9,CII_COL11);
				//BarFlag=1;
				break;
			case	menu_white_balance:
				BarAndPersent(7,xEEPROMBuffer[WhiteBlc_buf]);
				//DisplayPercent(WhiteBlcValue_min,WhiteBlcValue_max,xEEPROMBuffer[WhiteBlc_buf],DSP_ROW3,CII_COL7);
				//Displaybar2(WhiteBlcValue_min,WhiteBlcValue_max,xEEPROMBuffer[WhiteBlc_buf],DSP_ROW3,CII_COL11);
				//BarFlag=1;
				break;
			case	menu_Rgain:	
				BarAndPersent(8,xEEPROMBuffer[ADCREDGAIN_buf]+ADCREDGAIN_offset);
				//DisplayPercent(ADCREDGAIN_min,ADCREDGAIN_max,xEEPROMBuffer[ADCREDGAIN_buf]+ADCREDGAIN_offset,DSP_ROW4,CII_COL7);
				//Displaybar2(ADCREDGAIN_min,ADCREDGAIN_max,xEEPROMBuffer[ADCREDGAIN_buf]+ADCREDGAIN_offset,DSP_ROW4,CII_COL11);
				//BarFlag=1;
				break;
			case	menu_Ggain:	
				BarAndPersent(9,xEEPROMBuffer[ADCGREENGAIN_buf]+ADCREDGAIN_offset);
				//DisplayPercent(ADCGREENGAIN_min,ADCGREENGAIN_max,xEEPROMBuffer[ADCGREENGAIN_buf]+ADCREDGAIN_offset,DSP_ROW5,CII_COL7);
				//Displaybar2(ADCGREENGAIN_min,ADCGREENGAIN_max,xEEPROMBuffer[ADCGREENGAIN_buf]+ADCREDGAIN_offset,DSP_ROW5,CII_COL11);
				//BarFlag=1;
				break;
			case	menu_Bgain:	
				BarAndPersent(10,xEEPROMBuffer[ADCBLUEGAIN_buf]+ADCREDGAIN_offset);
				//DisplayPercent(ADCBLUEGAIN_min,ADCBLUEGAIN_max,xEEPROMBuffer[ADCBLUEGAIN_buf]+ADCREDGAIN_offset,DSP_ROW6,CII_COL7);
				//Displaybar2(ADCBLUEGAIN_min,ADCBLUEGAIN_max,xEEPROMBuffer[ADCBLUEGAIN_buf]+ADCREDGAIN_offset,DSP_ROW6,CII_COL11);
				//BarFlag=1;
				break;
			case	menu_color_temperture:
				ColorTempFunc();   
				BarFlag=0;
				break;

			case	menu_language:
				LanguageFunc();
				Display_MenuDescription();	// PC 모드
				//Display_AdjustInfo();	//smpark 20030821
				
				BarFlag=0;
				break;

			case	menu_osd_Hposition:
				#if 0	//외부
				DisplayPercent(OSDHpos_min,OSDHpos_max,xEEPROMBuffer[OSDHPOSITION_buf],DSP_ROW4,CII_COL7);
				Displaybar2(OSDHpos_min,OSDHpos_max,xEEPROMBuffer[OSDHPOSITION_buf],DSP_ROW4,CII_COL11);

				#else	//내부 + 외부
				MenuMinVal=OSDHpos_min;
				MenuMaxVal=OSDHpos_max;
				MenuVal=xEEPROMBuffer[OSDHPOSITION_buf];
				
				if((MenuVal%5==1)||(MenuVal==PhaseValue_min))
				{
					DisplayPercent(OSDHpos_min,OSDHpos_max,xEEPROMBuffer[OSDHPOSITION_buf],DSP_ROW4,CII_COL7);
					Displaybar2(OSDHpos_min,OSDHpos_max,xEEPROMBuffer[OSDHPOSITION_buf],DSP_ROW4,CII_COL11);				
					#ifdef WXGA_Panel
					OSDSeqSend(IN_ATTR_ROW15,IN_CII_COL15,(4+(xEEPROMBuffer[OSDHPOSITION_buf]/5)*3),1);//horizontal //내부
					#else
					OSDSeqSend(IN_ATTR_ROW15,IN_CII_COL15,(4+(xEEPROMBuffer[OSDHPOSITION_buf]/5)*3),1);//horizontal
					#endif
				}
				#endif
				
				BarFlag=1;
				break;

			case	menu_osd_Vposition:
				BarAndPersent(11,xEEPROMBuffer[OSDVPOSITION_buf]);
				//DisplayPercent(OSDVpos_min,OSDVpos_max,xEEPROMBuffer[OSDVPOSITION_buf],DSP_ROW5,CII_COL7);
				//Displaybar2(OSDVpos_min,OSDVpos_max,xEEPROMBuffer[OSDVPOSITION_buf],DSP_ROW5,CII_COL11);
				
				#if 1	//내부+외부 osd사용시 내부 윈도우를 위해.
				OSDSeqSend(IN_ATTR_ROW15,IN_CII_COL14,xEEPROMBuffer[OSDVPOSITION_buf]-1,1);//vertical	//내부
				#endif
				//BarFlag=1;
				break;

			case	menu_osd_time:		
				MenuMinVal=OSDOFFTIME_min;
				MenuMaxVal=OSDOFFTIME_max;
				MenuVal=xEEPROMBuffer[OSDOFFTIME_buf];
				OSD230SeqSend(DSP_ROW6,CII_COL12,_LTriAngle,1);
				OSD230SeqSend(DSP_ROW6,CII_COL25,_RTriAngle,1);
				OSD230ColSend(CII_COL15);
				OSD230DataSend(0x00);
				temp0 = calToChar(xEEPROMBuffer[OSDOFFTIME_buf]);
				HighOSDArea=0;//Low Display data.
				temp1 = 0;
				OSD230SeqSend(DSP_ROW6,CII_COL15,0x00,(3-temp0));
				OSD230ColSend(CII_COL15+(3-temp0));
				while(temp0--)
				{
					OSD230DataSend(CalBuffer[temp1]+0x01);
					temp1++;
				}
				temp1 = calToChar(xEEPROMBuffer[OSDOFFTIME_buf]);
				
				#if defined (USE_PALSECAMtuner)
				if(xEEPROMBuffer[LANGUAGE_buf]!=English) HighOSDArea=1;
				else HighOSDArea=0;
				OSD230PtrSend(DSP_ROW6,CII_COL18,Sec[xEEPROMBuffer[LANGUAGE_buf]],Sec_Sizeof[xEEPROMBuffer[LANGUAGE_buf]]);
				HighOSDArea=0;
				#else
				OSD230PtrSend(DSP_ROW6,CII_COL18,Sec[0],Sec_Sizeof[0]);
				#endif
				
				BarFlag=1;
				break;

			case	menu_osd_transparency:   
				OnoffDisplayFunc(DSP_ROW7,CII_COL12,(BYTE)TransparencyOnfFlag);
				if(TransparencyOnfFlag)
				{
					WriteScaler(0x73,0x20);//IntOsd_Blend (high nibble: 0x0x(100%) 1x(75%) 2x(50%) 3x(25%) )
				}
				else	WriteScaler(0x73,0x00);//IntOsd_Blend (high nibble: 0x0x(100%) 1x(75%) 2x(50%) 3x(25%) )
				
				
				BarFlag=0; 	
				break;
                        	
			case	menu_pip_enable:
				PipOnOffFlag=(xEEPROMBuffer[PIPEN_SOURCE_buf]&0x10)>>4;	
				PipOnoffFunc(DSP_ROW3,CII_COL12,(BYTE)PipOnOffFlag); 
				Display_BottomCurrentInfo();
				BarFlag=0;	
				break;
				
			case	menu_pip_source:
				PipSourceSelFunc();
				Display_BottomCurrentInfo();
				BarFlag=0;
				break;
			
			case	menu_pip_size:
				PipSizeSelFunc();
				BarFlag=0;		
				break;
			
			case	menu_pip_AspectRatio:
				PipAspectSelFunc();
				BarFlag=0;
				break;
						
			case	menu_pip_blend:
				PipBlendSelFunc();
				BarFlag=1;
				break;
						
			case	menu_pip_Hposition:
				#if 1	// '좌,중,우'로 표시
				PipHPosSelFunc();
				#else	// 바형식 표시
				DisplayPercent(PipHposition_min,PipHposition_max,PipHPositionNum,DSP_ROW6,CII_COL7);
				Displaybar2(PipHposition_min,PipHposition_max,PipHPositionNum,DSP_ROW6,CII_COL11);
				#endif
				
				BarFlag=0;
				break;
			
			case	menu_pip_Vposition:
				#if 1	// '상, 중, 하'로 표시
				PipVPosSelFunc();
				#else	// 바형식 표시
				DisplayPercent(PipVposition_min,PipVposition_max,PipVPositionNum,DSP_ROW7,CII_COL7);
				Displaybar2(PipVposition_min,PipVposition_max,PipVPositionNum,DSP_ROW7,CII_COL11);
				#endif

				BarFlag=0;
				break;
			
			case	menu_auto_adjust:
				OnoffDisplayFunc(DSP_ROW3,CII_COL12,(BYTE)AutoFlag);
				BarFlag=0;
				break;
				
			case	menu_factory_default:
				OnoffDisplayFunc(DSP_ROW4,CII_COL12,(BYTE)FactoryDftFlag);
				BarFlag=0;
				break;

			case	menu_dosmode:
				DosmodeDisplay(DSP_ROW5,CII_COL12,(BYTE)DosmodeFlag);
				BarFlag=0;
				break;
			
			#ifdef Wide4_3Aspect
			case	menu_AspectRatio:
				AspectRatioFunc(DSP_ROW6,CII_COL12,(BYTE)AspectFlag);
				BarFlag=0;
				break;
			#endif	
			// smpark 20030721
			case menu_Treble:
				BarAndPersent(12,xEEPROMBuffer[TREBLE]);
				//DisplayPercent(SOUND_TREBLE_min,SOUND_TREBLE_max,xEEPROMBuffer[TREBLE],DSP_ROW3,CII_COL7);//percent
				//Displaybar2(SOUND_TREBLE_min,SOUND_TREBLE_max,xEEPROMBuffer[TREBLE],DSP_ROW3,CII_COL11);//bar
				//BarFlag=1;
				break;
				
			case menu_Bass:
				BarAndPersent(13,xEEPROMBuffer[BASS]);
				//DisplayPercent(SOUND_BASS_min,SOUND_BASS_max,xEEPROMBuffer[BASS],DSP_ROW4,CII_COL7);//percent
				//Displaybar2(SOUND_BASS_min,SOUND_BASS_max,xEEPROMBuffer[BASS],DSP_ROW4,CII_COL11);//bar
				//BarFlag=1;
				break;
				
			case menu_Loudness:
				#ifdef LoudBarType
				DisplayPercent(SOUND_LOUDNESS_min,SOUND_LOUDNESS_max,xEEPROMBuffer[LOUDNESS],DSP_ROW5,CII_COL7);//percent
				Displaybar2(SOUND_LOUDNESS_min,SOUND_LOUDNESS_max,xEEPROMBuffer[LOUDNESS],DSP_ROW5,CII_COL11);//bar
				BarFlag=1;
				#else
				OnoffDisplayFunc(DSP_ROW5,CII_COL12, xEEPROMBuffer[LOUDNESS]);
				#endif
				break;
				
			case menu_SSC:
				SmartSoundCtrFunc();
				BarFlag=0;
				break;
/*				
			case menu_MTS:
				MTSFunc();
				BarFlag=0;
				break;
*/				
		}
	}
	//else if( (NowTopOsdOn)&&((xEEPROMBuffer[MainSubInputSource]==10)||(xEEPROMBuffer[MainSubInputSource]==14)||(xEEPROMBuffer[MainSubInputSource]==18)) )
	else if( (NowTopOsdOn)&&(CurrentFunction==Composite_mode||CurrentFunction==Svideo_mode||CurrentFunction==Tuner_mode) )
	{
		switch(TvMenuNum)
		{
			case	tvmenu_brightness:
				BarAndPersent(15,xEEPROMBuffer[COMPOSITEBRT_buf]);
				//Displaybar2(COMPOSITEBRT_min,COMPOSITEBRT_max,xEEPROMBuffer[COMPOSITEBRT_buf],DSP_ROW3,CII_COL11);
				//DisplayPercent(COMPOSITEBRT_min,COMPOSITEBRT_max,xEEPROMBuffer[COMPOSITEBRT_buf],DSP_ROW3,CII_COL7);
				//BarFlag=1;
				break;	
			case	tvmenu_contrast:
				BarAndPersent(16,xEEPROMBuffer[COMPOSITECONT]);
				//Displaybar2(COMPOSITECONT_min,COMPOSITECONT_max,xEEPROMBuffer[COMPOSITECONT],DSP_ROW4,CII_COL11);
				//DisplayPercent(COMPOSITECONT_min,COMPOSITECONT_max,xEEPROMBuffer[COMPOSITECONT],DSP_ROW4,CII_COL7);
				//BarFlag=1;
				break;  	
			case	tvmenu_sharpness:
				BarAndPersent(17,xEEPROMBuffer[AVSharpness]);
				//Displaybar2(COMPOSITESHARP_min,COMPOSITESHARP_max,xEEPROMBuffer[AVSharpness],DSP_ROW5,CII_COL11);
				//DisplayPercent(COMPOSITESHARP_min,COMPOSITESHARP_max,xEEPROMBuffer[AVSharpness],DSP_ROW5,CII_COL7);
				//BarFlag=1;
				break; 
			case	tvmenu_color:
				BarAndPersent(18,xEEPROMBuffer[AVCOLOR]);
				//Displaybar2(COMPOSITECOLOR_min,COMPOSITECOLOR_max,xEEPROMBuffer[AVCOLOR],DSP_ROW6,CII_COL11);
				//DisplayPercent(COMPOSITECOLOR_min,COMPOSITECOLOR_max,xEEPROMBuffer[AVCOLOR],DSP_ROW6,CII_COL7);
				//BarFlag=1;
				break;     	
			case	tvmenu_tint:
				Displaybar3(COMPOSITETINT_min,COMPOSITETINT_max,xEEPROMBuffer[AVTINT],DSP_ROW7,CII_COL11);
				DisplayPercent(COMPOSITETINT_min,COMPOSITETINT_max,xEEPROMBuffer[AVTINT],DSP_ROW7,CII_COL7);
				BarFlag=1;
				break;  
         		case tvmenu_country:
				BarFlag=0;			
				break;	   
			case tvmenu_auto_setup:
				BarFlag=0;
				break;  
			case tvmenu_channel_edit:
				BarFlag=0;
				break;
			
		#if defined (USE_NTSCtuner)	
			case tvmenu_antena_input:	//이 메뉴는 NTSC에서만 존재..
				AntenaSelFunc();
				BarFlag=0;
				break;
			
			case	tvmenu_finetune:			
				Displaybar3(TvFineTuneValue_min2,TvFineTuneValue_max2,xEEPROMBuffer[NTSC_AIRTVFine_buf],DSP_ROW7,CII_COL11);
				#ifdef OsdMenuType1
					#if defined(OsdColor_Red)
				if(OsdGrade<=1)	DisplayPercent2(TvFineTuneValue_min2,TvFineTuneValue_max2,xEEPROMBuffer[NTSC_AIRTVFine_buf],DSP_ROW7,CII_COL7,OSD_RED_BG|OSD_WHITE);
					#else
				if(OsdGrade<=1)	DisplayPercent2(TvFineTuneValue_min2,TvFineTuneValue_max2,xEEPROMBuffer[NTSC_AIRTVFine_buf],DSP_ROW7,CII_COL7,OSD_BLUE_BG|OSD_WHITE);
					#endif
				else DisplayPercent2(TvFineTuneValue_min2,TvFineTuneValue_max2,xEEPROMBuffer[NTSC_AIRTVFine_buf],DSP_ROW7,CII_COL7,OSD_BLUE);
				#else
				DisplayPercent(TvFineTuneValue_min2,TvFineTuneValue_max2,xEEPROMBuffer[NTSC_AIRTVFine_buf],DSP_ROW7,CII_COL7);
				#endif
				BarFlag=1;
				break; 
		#else
			case	tvmenu_finetune:
				Displaybar3(TvFineTuneValue_min2,TvFineTuneValue_max2,xEEPROMBuffer[NTSC_AIRTVFine_buf],DSP_ROW6,CII_COL11);
				//DisplayPercent2(TvFineTuneValue_min2,TvFineTuneValue_max2,xEEPROMBuffer[NTSC_AIRTVFine_buf],DSP_ROW7,CII_COL7,OSD_BLUE);
				DisplayPercent(TvFineTuneValue_min2,TvFineTuneValue_max2,xEEPROMBuffer[NTSC_AIRTVFine_buf],DSP_ROW6,CII_COL7);
				BarFlag=1;
				break;    
		#endif 
		
		#ifdef	Ccd_Vchip
			case	tvmenu_Ccd:
				BarFlag=0;
				break;
		
			case	tvmenu_Vchip:
				BarFlag=0;
				break;
		#endif
			
			case	tvmenu_lang://tvmenu_ttx:
				LanguageFunc();
				Display_TvMenuDescription();
				Display_AdjustInfo();	//smpark 20030821
				BarFlag=0;
				break;			
			case	tvmenu_blue_screen:
				OnoffDisplayFunc(DSP_ROW4,CII_COL12, xEEPROMBuffer[BscrFlag_buf]);
				BarFlag=0;
				break;              
			case	tvmenu_screen_mode:
				//WideOnFunc();
				TvAspectRatioSelFunc();
				BarFlag=0;
				break;              
			case	tvmenu_smart_picture_control:
				SmartPicCtrFunc();
				BarFlag=0;
				break;    
			case	tvmenu_sleep:
				SleepFunc();
				BarFlag=0;
				break;	
			#ifdef TempOsdMenu
			case	tvmenu_TempOsd:
				TempOsdSelFunc();	//임시osd 함수...
				BarFlag=0;
				break;
				
			case	tvmenu_OsdBlend:
				TempOsdBlendFunc();
				BarFlag=0;
				break;
			#endif
				
	
				
				
				
			#if 0
			case	tvmenu_aspect:
				TvAspectRatioSelFunc();
				BarFlag=0;
				break;
			#endif				
			
			// added by smpark 20030721
			case tvmenu_Treble:
				BarAndPersent(12,xEEPROMBuffer[TREBLE]);
				//DisplayPercent(SOUND_TREBLE_min,SOUND_TREBLE_max,xEEPROMBuffer[TREBLE],DSP_ROW3,CII_COL7);//percent
				//Displaybar2(SOUND_TREBLE_min,SOUND_TREBLE_max,xEEPROMBuffer[TREBLE],DSP_ROW3,CII_COL11);//bar
				//BarFlag=1;
				break;
				
			case tvmenu_Bass:
				BarAndPersent(13,xEEPROMBuffer[BASS]);
				//DisplayPercent(SOUND_BASS_min,SOUND_BASS_max,xEEPROMBuffer[BASS],DSP_ROW4,CII_COL7);//percent
				//Displaybar2(SOUND_BASS_min,SOUND_BASS_max,xEEPROMBuffer[BASS],DSP_ROW4,CII_COL11);//bar
				//BarFlag=1;
				break;
				
			case tvmenu_Loudness:
				#ifdef LoudBarType
				DisplayPercent(SOUND_LOUDNESS_min,SOUND_LOUDNESS_max,xEEPROMBuffer[LOUDNESS],DSP_ROW5,CII_COL7);//percent
				Displaybar2(SOUND_LOUDNESS_min,SOUND_LOUDNESS_max,xEEPROMBuffer[LOUDNESS],DSP_ROW5,CII_COL11);//bar
				BarFlag=1; 
				#else
				OnoffDisplayFunc(DSP_ROW5,CII_COL12, xEEPROMBuffer[LOUDNESS]);
				BarFlag=0;
				#endif
				break;
				
			case tvmenu_SSC:
				SmartSoundCtrFunc();
				BarFlag=0;
				break;
/*				
			case tvmenu_MTS:
				MTSFunc();
				BarFlag=0;
				break;
*/				
		}
	}		
	
	else
	{
		
		switch(OsdMode)
		{
			case volume_mode:
				MenuMinVal=VOLUME_min;
				MenuMaxVal=VOLUME_max;
				MenuVal=xEEPROMBuffer[VOLUME_buf];
				BarFlag=1;
				OsdGrade=0;
				xOSD_WIN_REG[0x0E] = 0x1f;	//character height
				
				//xOSDRA=ATTR_ROW1;
				//xOSDCA=10;
				//xOSDDT0=0x02;				

				OSD230SeqSend(ATTR_ROW0,CII_COL1,OSD_GREEN,2); 	//Attribute data
				OSD230SeqSend(DSP_ROW0,CII_COL1,_SpeakerOn,1); 	//Display data  //Speaker icon

				DisplayPercent2(VOLUME_min,VOLUME_max,xEEPROMBuffer[VOLUME_buf],DSP_ROW0,CII_COL26,OSD_GREEN);//percent nember(%)
				
				OSD230SeqSend(ATTR_ROW1,CII_COL0,OSD_GREEN,30);//attribute!!	
				Displaybar(VOLUME_min,VOLUME_max,xEEPROMBuffer[VOLUME_buf],DSP_ROW1,CII_COL0);//bar
				break;
		}

	}
}


void WriteMenu(BYTE textsize, BYTE *textdata)
{
	BYTE	xdata coldata=0;

	if(textsize%2)	coldata=(WIN_SIZE-textsize)/2;		//해당글자가 홀수 일때
	else		coldata=(WIN_SIZE-textsize)/2-1;	//해당글자가 짝수 일때
	
	#ifdef OsdMenuType1
	OSD230SeqSend(ATTR_ROW10,coldata,0x01,textsize); //Attribute data
	OSD230PtrSend(DSP_ROW10,coldata,textdata,textsize); //Display data
	#else
	OSD230SeqSend(ATTR_ROW11,coldata,0x01,textsize); //Attribute data
	OSD230PtrSend(DSP_ROW11,coldata,textdata,textsize); //Display data
	#endif
}


void	Display_MenuDescription(void)
{
	BYTE	xdata coldata=0;
	#ifdef OsdMenuType1
	OSD230SeqSend(DSP_ROW10,CII_COL0,0x00,30);//clear
	#else
	OSD230SeqSend(DSP_ROW11,CII_COL0,0x00,30);//clear
	#endif

	//if(xEEPROMBuffer[LANGUAGE_buf]!=English) HighOSDArea=1;
	//else HighOSDArea=0;

	switch(MenuNum)
	{

		case 	menu_brightness:
			//BRIGHTNESS
			if(xEEPROMBuffer[LANGUAGE_buf]!=English) HighOSDArea=1;
				else HighOSDArea=0;
			WriteMenu(Brightness_Sizeof[LangBuf], Brightness[LangBuf]);
			//coldata=(WIN_SIZE-Brightness_Sizeof[0/*LangSelect*/])/2-1;
			//OSD230SeqSend(ATTR_ROW11,coldata,0x01,Brightness_Sizeof[LangSelect]); //Attribute data
			//OSD230PtrSend(DSP_ROW11,coldata,Brightness[LangSelect],Brightness_Sizeof[LangSelect]); //Display data
			HighOSDArea=0;
			break;
		
		case	menu_contrast:
			//CONTRAST
			if(xEEPROMBuffer[LANGUAGE_buf]!=English) HighOSDArea=1;
				else HighOSDArea=0;
			WriteMenu(Contrast_Sizeof[LangBuf], Contrast[LangBuf]);
			//coldata=(WIN_SIZE-Contrast_Sizeof[LangSelect])/2-1;
			//OSD230SeqSend(ATTR_ROW11,coldata,0x01,Contrast_Sizeof[LangSelect]); //Attribute data
			//OSD230PtrSend(DSP_ROW11,coldata,Contrast[LangSelect],Contrast_Sizeof[LangSelect]); //Display data
			HighOSDArea=0;
			break;		
		case	menu_sharpness:
			//Sharpness
			WriteMenu(Sharpness_Sizeof[0/*0/*LangSelect*/], Sharpness[0/*0/*LangSelect*/]);
			//coldata=(WIN_SIZE-Sharpness_Sizeof[0/*LangSelect*/])/2-1;
			//OSD230SeqSend(ATTR_ROW11,coldata,0x01,Sharpness_Sizeof[LangSelect]); //Attribute data
			//OSD230PtrSend(DSP_ROW11,coldata,Sharpness[xEEPROMBuffer[LANGUAGE_buf]],Sharpness_Sizeof[LangSelect]); //Display data
			break;		
		case	menu_phase:
			//Phase
			WriteMenu(Phase_Sizeof[0/*LangSelect*/], Phase[0/*LangSelect*/]);
			//coldata=(WIN_SIZE-Phase_Sizeof[xEEPROMBuffer[LANGUAGE_buf]])/2-1;
			//OSD230SeqSend(ATTR_ROW11,coldata,0x01,Phase_Sizeof[xEEPROMBuffer[LANGUAGE_buf]]); //Attribute data
			//OSD230PtrSend(DSP_ROW11,coldata,Phase[xEEPROMBuffer[LANGUAGE_buf]],Phase_Sizeof[LangSelect]); //Display data
			break;			
		case	menu_clock:
			//Clock
			WriteMenu(Clock_Sizeof[0/*LangSelect*/], Clock[0/*LangSelect*/]);
			//coldata=(WIN_SIZE-Clock_Sizeof[xEEPROMBuffer[LANGUAGE_buf]])/2-1;
		//	OSD230SeqSend(ATTR_ROW11,coldata,0x01,Clock_Sizeof[LangSelect]); //Attribute data
			//OSD230PtrSend(DSP_ROW11,coldata,Clock[LangSelect],Clock_Sizeof[LangSelect]); //Display data
			break;		
		case	menu_Hposition:
			//H-Position
			if(xEEPROMBuffer[LANGUAGE_buf]!=English) HighOSDArea=1;
				else HighOSDArea=0;
			WriteMenu(Horizontal_Sizeof[LangBuf], Horizontal[LangBuf]);
			//coldata=(WIN_SIZE-Horizontal_Sizeof[LangSelect])/2-1;
			//OSD230SeqSend(ATTR_ROW11,coldata,0x01,Horizontal_Sizeof[LangSelect]); //Attribute data
			//OSD230PtrSend(DSP_ROW11,coldata,Horizontal[LangSelect],Horizontal_Sizeof[LangSelect]); //Display data
			HighOSDArea=0;
			break;		
		case	menu_Vposition:
			//V-Position
			if(xEEPROMBuffer[LANGUAGE_buf]!=English) HighOSDArea=1;
				else HighOSDArea=0;
			WriteMenu(Vertical_Sizeof[LangBuf], Vertical[LangBuf]);
			//coldata=(WIN_SIZE-Vertical_Sizeof[LangSelect])/2-1;
			//OSD230SeqSend(ATTR_ROW11,coldata,0x01,Vertical_Sizeof[LangSelect]); //Attribute data
			//OSD230PtrSend(DSP_ROW11,coldata,Vertical[LangSelect],Vertical_Sizeof[LangSelect]); //Display data
			HighOSDArea=0;
			break;	

		case	menu_white_balance:
			WriteMenu(WhiteBalance_Sizeof[0/*LangSelect*/], WhiteBalance[0/*LangSelect*/]);
			//coldata=(WIN_SIZE-WhiteBalance_Sizeof[LangSelect])/2-1;
			//OSD230SeqSend(ATTR_ROW11,coldata,0x01,WhiteBalance_Sizeof[LangSelect]); //Attribute data
			//OSD230PtrSend(DSP_ROW11,coldata,WhiteBalance[LangSelect],WhiteBalance_Sizeof[LangSelect]); //Display data
			break;	
		case	menu_Rgain:	
			if(xEEPROMBuffer[LANGUAGE_buf]!=English) HighOSDArea=1;
				else HighOSDArea=0;
			WriteMenu(Rgain_Sizeof[LangBuf], Rgain[LangBuf]);
			//coldata=(WIN_SIZE-Rgain_Sizeof[LangSelect])/2-1;
			//OSD230SeqSend(ATTR_ROW11,coldata,0x01,Rgain_Sizeof[LangSelect]); //Attribute data
			//OSD230PtrSend(DSP_ROW11,coldata,Rgain[xEEPROMBuffer[LANGUAGE_buf]],Rgain_Sizeof[LangSelect]); //Display data
			HighOSDArea=0;
			break;	
		case	menu_Ggain:		
			
			if(xEEPROMBuffer[LANGUAGE_buf]!=English) HighOSDArea=1;
				else HighOSDArea=0;WriteMenu(Ggain_Sizeof[LangBuf], Ggain[LangBuf]);
			//coldata=(WIN_SIZE-Ggain_Sizeof[LangSelect])/2-1;
			//OSD230SeqSend(ATTR_ROW11,coldata,0x01,Ggain_Sizeof[LangSelect]); //Attribute data
			//OSD230PtrSend(DSP_ROW11,coldata,Ggain[LangSelect],Ggain_Sizeof[LangSelect]); //Display data
			HighOSDArea=0;
			break;	
		case	menu_Bgain:
			if(xEEPROMBuffer[LANGUAGE_buf]!=English) HighOSDArea=1;
				else HighOSDArea=0;	
			WriteMenu(Bgain_Sizeof[LangBuf], Bgain[LangBuf]);
			//coldata=(WIN_SIZE-Bgain_Sizeof[LangSelect])/2-1;
			//OSD230SeqSend(ATTR_ROW11,coldata,0x01,Bgain_Sizeof[LangSelect]); //Attribute data
			//OSD230PtrSend(DSP_ROW11,coldata,Bgain[LangSelect],Bgain_Sizeof[LangSelect]); //Display data
			HighOSDArea=0;
			break;	
		case	menu_color_temperture:
			if(xEEPROMBuffer[LANGUAGE_buf]!=English) HighOSDArea=1;
				else HighOSDArea=0;
			WriteMenu(Color_Sizeof[LangBuf], Color[LangBuf]);
			//coldata=(WIN_SIZE-Color_Sizeof[LangSelect])/2-1;
			//OSD230SeqSend(ATTR_ROW11,coldata,0x01,Color_Sizeof[LangSelect]); //Attribute data
			//OSD230PtrSend(DSP_ROW11,coldata,Color[LangSelect],Color_Sizeof[LangSelect]); //Display data
			HighOSDArea=0;
			break;	
		                        
		case	menu_language:
			if(xEEPROMBuffer[LANGUAGE_buf]!=English) HighOSDArea=1;
				else HighOSDArea=0;
			WriteMenu(OsdLanguage_Sizeof[LangBuf], OsdLanguage[LangBuf]);
			//coldata=(WIN_SIZE-OsdLanguage_Sizeof[0])/2-1;
			//OSD230SeqSend(ATTR_ROW11,coldata,0x01,OsdLanguage_Sizeof[0]); //Attribute data
			//OSD230PtrSend(DSP_ROW11,coldata,OsdLanguage[0],OsdLanguage_Sizeof[0]); //Display data
			HighOSDArea=0;
			break;	

			
		case	menu_osd_Hposition:
			WriteMenu(OsdHPosition_Sizeof[0/*LangSelect*/], OsdHPosition[0/*LangSelect*/]);
			//coldata=(WIN_SIZE-OsdHPosition_Sizeof[LangSelect])/2-1;
			//OSD230SeqSend(ATTR_ROW11,coldata,0x01,OsdHPosition_Sizeof[LangSelect]); //Attribute data
			//OSD230PtrSend(DSP_ROW11,coldata,OsdHPosition[LangSelect],OsdHPosition_Sizeof[LangSelect]); //Display data
			break;	
		case	menu_osd_Vposition:	
			WriteMenu(OsdVPosition_Sizeof[0/*LangSelect*/], OsdVPosition[0/*LangSelect*/]);
			//coldata=(WIN_SIZE-OsdVPosition_Sizeof[LangSelect])/2-1;
			//OSD230SeqSend(ATTR_ROW11,coldata,0x01,OsdVPosition_Sizeof[LangSelect]); //Attribute data
			//OSD230PtrSend(DSP_ROW11,coldata,OsdVPosition[LangSelect],OsdVPosition_Sizeof[LangSelect]); //Display data
			break;	
		case	menu_osd_time:	
			WriteMenu(OsdTime_Sizeof[0/*LangSelect*/], OsdTime[0/*LangSelect*/]);
			//coldata=(WIN_SIZE-OsdTime_Sizeof[0])/2-1;
			//OSD230SeqSend(ATTR_ROW11,coldata,0x01,OsdTime_Sizeof[0]); //Attribute data
			//OSD230PtrSend(DSP_ROW11,coldata,OsdTime[0],OsdTime_Sizeof[0]); //Display data
			break;	
		case	menu_osd_transparency:
			WriteMenu(OsdTransparency_Sizeof[0/*LangSelect*/], OsdTransparency[0/*LangSelect*/]);
			//coldata=(WIN_SIZE-OsdTransparency_Sizeof[LangSelect])/2-1;
			//OSD230SeqSend(ATTR_ROW11,coldata,0x01,OsdTransparency_Sizeof[LangSelect]); //Attribute data
			//OSD230PtrSend(DSP_ROW11,coldata,OsdTransparency[0/*LangSelect*/],OsdTransparency_Sizeof[LangSelect]); //Display data
			break;	
		                        
		case	menu_pip_enable: 
			WriteMenu(PipEnable_Sizeof[0/*LangSelect*/], PipEnable[0/*LangSelect*/]);
			//coldata=(WIN_SIZE-PipEnable_Sizeof[0])/2-1;
			//OSD230SeqSend(ATTR_ROW11,coldata,0x01,PipEnable_Sizeof[0]); //Attribute data
			//OSD230PtrSend(DSP_ROW11,coldata,PipEnable[0],PipEnable_Sizeof[0]); //Display data
			break;	
		case	menu_pip_source:        
			WriteMenu(PipSource_Sizeof[0/*LangSelect*/], PipSource[0/*LangSelect*/]);
			//coldata=(WIN_SIZE-PipSource_Sizeof[0])/2-1;
			//OSD230SeqSend(ATTR_ROW11,coldata,0x01,PipSource_Sizeof[0]); //Attribute data
			//OSD230PtrSend(DSP_ROW11,coldata,PipSource[0],PipSource_Sizeof[0]); //Display data
			break;	
		case	menu_pip_size:
			WriteMenu(PipSize_Sizeof[0/*LangSelect*/], PipSize[0/*LangSelect*/]);
			//coldata=(WIN_SIZE-PipSize_Sizeof[0])/2-1;
			//OSD230SeqSend(ATTR_ROW11,coldata,0x01,PipSize_Sizeof[0]); //Attribute data
			//OSD230PtrSend(DSP_ROW11,coldata,PipSize[0],PipSize_Sizeof[0]); //Display data
			break;	
		case	menu_pip_AspectRatio:        
			WriteMenu(PipAspect_Sizeof[0/*LangSelect*/], PipAspect[0/*LangSelect*/]);
			//coldata=(WIN_SIZE-PipAspect_Sizeof[0])/2-1;
			//OSD230SeqSend(ATTR_ROW11,coldata,0x01,PipAspect_Sizeof[0]); //Attribute data
			//OSD230PtrSend(DSP_ROW11,coldata,PipAspect[0],PipAspect_Sizeof[0]); //Display data
			break;	

		case	menu_pip_blend:        
			WriteMenu(PipBlend_Sizeof[0/*LangSelect*/], PipBlend[0/*LangSelect*/]);
			//coldata=(WIN_SIZE-PipBlend_Sizeof[0])/2-1;
			//OSD230SeqSend(ATTR_ROW11,coldata,0x01,PipBlend_Sizeof[0]); //Attribute data
			//OSD230PtrSend(DSP_ROW11,coldata,PipBlend[0],PipBlend_Sizeof[0]); //Display data
			break;	

		case	menu_pip_Hposition:
			WriteMenu(PipHPosition_Sizeof[0/*LangSelect*/], PipHPosition[0/*LangSelect*/]);
			//coldata=(WIN_SIZE-PipHPosition_Sizeof[0])/2-1;
			//OSD230SeqSend(ATTR_ROW11,coldata,0x01,PipHPosition_Sizeof[0]); //Attribute data
			//OSD230PtrSend(DSP_ROW11,coldata,PipHPosition[0],PipHPosition_Sizeof[0]); //Display data
			break;	
		case	menu_pip_Vposition:	
			WriteMenu(PipVPosition_Sizeof[0/*LangSelect*/], PipVPosition[0/*LangSelect*/]);
			//coldata=(WIN_SIZE-PipVPosition_Sizeof[0])/2-1;
			//OSD230SeqSend(ATTR_ROW11,coldata,0x01,PipVPosition_Sizeof[0]); //Attribute data
			//OSD230PtrSend(DSP_ROW11,coldata,PipVPosition[0],PipVPosition_Sizeof[0]); //Display data
			break;	
		                        
		case	menu_auto_adjust:
			if(xEEPROMBuffer[LANGUAGE_buf]!=English) HighOSDArea=1;		//+jwshin 040801
			else HighOSDArea=0;	
			WriteMenu(AutoTune_Sizeof[xEEPROMBuffer[LANGUAGE_buf]], AutoTune[xEEPROMBuffer[LANGUAGE_buf]]);
			//coldata=(WIN_SIZE-AutoTune_Sizeof[0/*LangSelect*/])/2-1;
			//OSD230SeqSend(ATTR_ROW11,coldata,0x01,AutoTune_Sizeof[0/*LangSelect*/]); //Attribute data
			//OSD230PtrSend(DSP_ROW11,coldata,AutoTune[0/*LangSelect*/],AutoTune_Sizeof[0/*LangSelect*/]); //Display data
			break;	
		case	menu_factory_default:
			if(xEEPROMBuffer[LANGUAGE_buf]!=English) HighOSDArea=1;
				else HighOSDArea=0;
			WriteMenu(Factory_Sizeof[LangBuf], Factory[LangBuf]);
			//coldata=(WIN_SIZE-Factory_Sizeof[0])/2-1;
			//OSD230SeqSend(ATTR_ROW11,coldata,0x01,Factory_Sizeof[0]); //Attribute data			
			//OSD230PtrSend(DSP_ROW11,coldata,Factory[0],Factory_Sizeof[0]); //Display data
			HighOSDArea=0;
			break;
			
		case	menu_dosmode:
			if(xEEPROMBuffer[LANGUAGE_buf]!=English) HighOSDArea=1;		//+jwshin 040801
			else HighOSDArea=0;
			WriteMenu(Dosmode_Sizeof[xEEPROMBuffer[LANGUAGE_buf]], Dosmode[xEEPROMBuffer[LANGUAGE_buf]]);
			break;
		
		#ifdef Wide4_3Aspect	
		case	menu_AspectRatio:
//			WriteMenu(sizeof(ScreenMode_Eng), ScreenMode_Eng);
			if(xEEPROMBuffer[LANGUAGE_buf]!=English) HighOSDArea=1;		//+jwshin 040801
			else HighOSDArea=0;
			WriteMenu(ScreenMode_Sizeof[xEEPROMBuffer[LANGUAGE_buf]],ScreenMode[xEEPROMBuffer[LANGUAGE_buf]]);
			break;
		#endif
		// added by smpark 20030719
		case menu_Treble:
			if(xEEPROMBuffer[LANGUAGE_buf]!=English) HighOSDArea=1;		//+jwshin 040801
			else HighOSDArea=0;
			WriteMenu(Treble_Sizeof[xEEPROMBuffer[LANGUAGE_buf]], Treble[xEEPROMBuffer[LANGUAGE_buf]]);
			//coldata=(WIN_SIZE-Treble_Sizeof[0/*LangSelect*/])/2-1;
			//OSD230SeqSend(ATTR_ROW11,coldata,0x01,Treble_Sizeof[0/*LangSelect*/]); //Attribute data
			//OSD230PtrSend(DSP_ROW11,coldata,Treble[0/*LangSelect*/],Treble_Sizeof[0/*LangSelect*/]); //Display data
			break;

		case menu_Bass:
			if(xEEPROMBuffer[LANGUAGE_buf]!=English) HighOSDArea=1;		//+jwshin 040801
			else HighOSDArea=0;
			WriteMenu(Bass_Sizeof[xEEPROMBuffer[LANGUAGE_buf]], Bass[xEEPROMBuffer[LANGUAGE_buf]]);
			//coldata=(WIN_SIZE-Bass_Sizeof[0/*LangSelect*/])/2-1;
			//OSD230SeqSend(ATTR_ROW11,coldata,0x01,Bass_Sizeof[0/*LangSelect*/]); //Attribute data
			//OSD230PtrSend(DSP_ROW11,coldata,Bass[0/*LangSelect*/],Bass_Sizeof[0/*LangSelect*/]); //Display data
			break;

		case menu_Loudness:		//+jwshin 040801
			if(xEEPROMBuffer[LANGUAGE_buf]!=English) HighOSDArea=1;
			else HighOSDArea=0;
			WriteMenu(Loudness_Sizeof[xEEPROMBuffer[LANGUAGE_buf]], Loudness[xEEPROMBuffer[LANGUAGE_buf]]);
			//coldata=(WIN_SIZE-Loudness_Sizeof[0/*LangSelect*/])/2-1;
			//OSD230SeqSend(ATTR_ROW11,coldata,0x01,Loudness_Sizeof[0/*LangSelect*/]); //Attribute data
			//OSD230PtrSend(DSP_ROW11,coldata,Loudness[0/*LangSelect*/],Loudness_Sizeof[0/*LangSelect*/]); //Display data
			break;

     		case menu_SSC:			//+jwshin 040801
     			if(xEEPROMBuffer[LANGUAGE_buf]!=English) HighOSDArea=1;
			else HighOSDArea=0;
			WriteMenu(SmartSound_Sizeof[xEEPROMBuffer[LANGUAGE_buf]], SmartSound[xEEPROMBuffer[LANGUAGE_buf]]);
			//coldata=(WIN_SIZE-SmartSound_Sizeof[LangSelect])/2-1;
			//OSD230SeqSend(ATTR_ROW11,coldata,0x01,SmartSound_Sizeof[LangSelect]); //Attribute data
			//OSD230PtrSend(DSP_ROW11,coldata,SmartSound[LangSelect],SmartSound_Sizeof[LangSelect]); //Display data
    			break;
   	}

	HighOSDArea=0;
}

void	Display_TvMenuDescription()
{
#ifndef OsdMenuType1
	BYTE	coldata=0;
	
	OSD230SeqSend(DSP_ROW11,CII_COL0,0x00,30);//clear

	if(xEEPROMBuffer[LANGUAGE_buf]!=English) HighOSDArea=1;
	else HighOSDArea=0;

	switch(TvMenuNum)
	{
		case 	tvmenu_brightness:
			WriteMenu(Brightness_Sizeof[xEEPROMBuffer[LANGUAGE_buf]], Brightness[xEEPROMBuffer[LANGUAGE_buf]]);
			break;
			
		case 	tvmenu_contrast:
			WriteMenu(Contrast_Sizeof[xEEPROMBuffer[LANGUAGE_buf]], Contrast[xEEPROMBuffer[LANGUAGE_buf]]);
			break;
			
		case 	tvmenu_sharpness:
			WriteMenu(Sharpness_Sizeof[xEEPROMBuffer[LANGUAGE_buf]], Sharpness[xEEPROMBuffer[LANGUAGE_buf]]);
			break;
			
		case 	tvmenu_color:
			WriteMenu(TvColor_Sizeof[xEEPROMBuffer[LANGUAGE_buf]], TvColor[xEEPROMBuffer[LANGUAGE_buf]]);
			break;
			
		case 	tvmenu_tint:
			WriteMenu(Tint_Sizeof[xEEPROMBuffer[LANGUAGE_buf]], Tint[xEEPROMBuffer[LANGUAGE_buf]]);
			break;  
			
		case 	tvmenu_country:
			WriteMenu(Country_Sizeof[xEEPROMBuffer[LANGUAGE_buf]], Country[xEEPROMBuffer[LANGUAGE_buf]]);
			break;
			
		case 	tvmenu_auto_setup:
			WriteMenu(AutoSetup_Sizeof[xEEPROMBuffer[LANGUAGE_buf]], AutoSetup[xEEPROMBuffer[LANGUAGE_buf]]);
			break;  

		#if defined (USE_NTSCtuner)
		case 	tvmenu_channel_edit:
			WriteMenu(ChannelEdit_Sizeof[xEEPROMBuffer[LANGUAGE_buf]], ChannelEdit[xEEPROMBuffer[LANGUAGE_buf]]);
			break;

	#else
		case 	tvmenu_channel_edit:
			#ifndef PalCountry_ChinaOnly
			WriteMenu(ProgrammEdit_Sizeof[xEEPROMBuffer[LANGUAGE_buf]], ProgrammEdit[xEEPROMBuffer[LANGUAGE_buf]]);
			#else
			WriteMenu(ChannelEdit_Sizeof[xEEPROMBuffer[LANGUAGE_buf]], ChannelEdit[xEEPROMBuffer[LANGUAGE_buf]]);
			#endif
			break;

	#endif


	#if defined (USE_NTSCtuner)
		case 	tvmenu_antena_input:
			WriteMenu(AntenaInput_Sizeof[xEEPROMBuffer[LANGUAGE_buf]], AntenaInput[xEEPROMBuffer[LANGUAGE_buf]]);
			break;

	#endif

	#ifdef	Ccd_Vchip
		case	tvmenu_Ccd:
			WriteMenu(Ccd_Sizeof[0], Ccd[0]);
			break;
	
		case	tvmenu_Vchip:
			WriteMenu(Vchip_Sizeof[0], Vchip[0]);
			break;
	#endif
	
	
		case 	tvmenu_finetune:
			WriteMenu(FineTune_Sizeof[xEEPROMBuffer[LANGUAGE_buf]], FineTune[xEEPROMBuffer[LANGUAGE_buf]]);
			break;    

		case	tvmenu_lang:
			WriteMenu(OsdLanguage_Sizeof[xEEPROMBuffer[LANGUAGE_buf]],OsdLanguage[xEEPROMBuffer[LANGUAGE_buf]]);
			break;			

		case 	tvmenu_blue_screen:
			WriteMenu(BlueScreen_Sizeof[xEEPROMBuffer[LANGUAGE_buf]], BlueScreen[xEEPROMBuffer[LANGUAGE_buf]]);
			break;              

		case 	tvmenu_screen_mode:
			WriteMenu(ScreenMode_Sizeof[xEEPROMBuffer[LANGUAGE_buf]], ScreenMode[xEEPROMBuffer[LANGUAGE_buf]]);
			break;             

		case 	tvmenu_smart_picture_control:
			WriteMenu(SmartPicture_Sizeof[xEEPROMBuffer[LANGUAGE_buf]], SmartPicture[xEEPROMBuffer[LANGUAGE_buf]]);
			break;    

		case 	tvmenu_sleep:
			WriteMenu(Sleep_Sizeof[xEEPROMBuffer[LANGUAGE_buf]], Sleep[xEEPROMBuffer[LANGUAGE_buf]]);
			break;	
			
		#ifdef TempOsdMenu
		case	tvmenu_TempOsd:
			//
			break;
		
		case	tvmenu_OsdBlend:
			//
			break;
		
		#endif

		#if 0
		case 	tvmenu_aspect:
			WriteMenu(DisplayAspect_Sizeof[xEEPROMBuffer[LANGUAGE_buf]], DisplayAspect[xEEPROMBuffer[LANGUAGE_buf]]);
			//coldata=(WIN_SIZE-DisplayAspect_Sizeof[0])/2-1;
			//OSD230SeqSend(ATTR_ROW11,coldata,0x01,DisplayAspect_Sizeof[0]); //Attribute data
			//OSD230PtrSend(DSP_ROW11,coldata,DisplayAspect[0],DisplayAspect_Sizeof[0]); //Display data
			break;	
		#endif

		// added by smpark 20030719
		case tvmenu_Treble:
			WriteMenu(Treble_Sizeof[xEEPROMBuffer[LANGUAGE_buf]], Treble[xEEPROMBuffer[LANGUAGE_buf]]);
			break;

		case tvmenu_Bass:
			WriteMenu(Bass_Sizeof[xEEPROMBuffer[LANGUAGE_buf]], Bass[xEEPROMBuffer[LANGUAGE_buf]]);
			break;

		case tvmenu_Loudness:
			HighOSDArea=0;
			WriteMenu(Loudness_Sizeof[xEEPROMBuffer[LANGUAGE_buf]], Loudness[xEEPROMBuffer[LANGUAGE_buf]]);
			break;

     	case tvmenu_SSC:
			WriteMenu(SmartSound_Sizeof[xEEPROMBuffer[LANGUAGE_buf]], SmartSound[xEEPROMBuffer[LANGUAGE_buf]]);
    		break;			
	}
	HighOSDArea=0;
#endif	
}

/*
void	MiddleAlign(BYTE total, BYTE *Recdata)
{
	return (total-*Recdata)/2;
}
*/

// modified by smpark 20030714 
void	IconSel()
{
	
#ifdef VideoDoubleOSD	//double
	//if( (xEEPROMBuffer[MainSubInputSource]!=10)&&(xEEPROMBuffer[MainSubInputSource]!=14)&&(xEEPROMBuffer[MainSubInputSource]!=18) )
	if( (CurrentFunction!=Tuner_mode)&&(CurrentFunction!=Composite_mode)&&(CurrentFunction!=Svideo_mode) )
	{	// PC
		if(OsdGrade==0)
		{
			OSD230SeqSend(ATTR_ROW2,CII_COL1+(MenuNum*4),OSD_BLUE,4);
			//OSD230SeqSend(DSP_ROW11,CII_COL0,0x00,30);//clear
		}
		else
		{
			OSD230SeqSend(ATTR_ROW2,CII_COL1+(GetTopMenu()*4),OSD_BLUE,4);
		}
	}
	else	// Video
	{
		if(CurrentFunction==Tuner_mode)	// Tv 일때
		{
			if(OsdGrade==0)
				OSD230SeqSend(ATTR_ROW2,CII_COL5+(TvMenuNum*6),OSD_BLUE,2);
			else	OSD230SeqSend(ATTR_ROW2,CII_COL5+(GetTvTopMenu()*6),OSD_BLUE,4);
		}
		else if(CurrentFunction==Composite_mode||CurrentFunction==Svideo_mode)	// AV1,2 일때
		{
			if(TvMenuNum==TvTopMenuStart)
			{
				if(OsdGrade==0)
					OSD230SeqSend(ATTR_ROW2,CII_COL7+(TvMenuNum*6),OSD_BLUE,2);
				else	OSD230SeqSend(ATTR_ROW2,CII_COL7+(GetTvTopMenu()*6),OSD_BLUE,4);
			}
			else	//두번째가 tv이므로 제외하기 위하여
			{
				if(OsdGrade==0)
					OSD230SeqSend(ATTR_ROW2,CII_COL7+((TvMenuNum-1)*6),OSD_BLUE,2);
				else	OSD230SeqSend(ATTR_ROW2,CII_COL7+((GetTvTopMenu()-1)*6),OSD_BLUE,4);
			}
		}               
	}                       
#else	//normal
	//if( (xEEPROMBuffer[MainSubInputSource]!=10)&&(xEEPROMBuffer[MainSubInputSource]!=14)&&(xEEPROMBuffer[MainSubInputSource]!=18) )
	#if defined(OsdColor_Red)//------------------------------------
	if( (CurrentFunction!=Tuner_mode)&&(CurrentFunction!=Composite_mode)&&(CurrentFunction!=Svideo_mode) )
	{	// PC
		if(OsdGrade==0)	OSD230SeqSend(ATTR_ROW2,CII_COL1+(MenuNum*4),OSD_RED,4);
		else		OSD230SeqSend(ATTR_ROW2,CII_COL1+(GetTopMenu()*4),OSD_RED,4);
	}
	else	// Video
	{
		if(CurrentFunction==Tuner_mode)	// Tv 일때
		{
			if(OsdGrade==0)	OSD230SeqSend(ATTR_ROW2,CII_COL5+(TvMenuNum*6),OSD_RED,2);
			else		OSD230SeqSend(ATTR_ROW2,CII_COL5+(GetTvTopMenu()*6),OSD_RED,4);
		}
		else if(CurrentFunction==Composite_mode||CurrentFunction==Svideo_mode)	// AV1,2 일때
		{
			if(TvMenuNum==TvTopMenuStart)
			{
				if(OsdGrade==0)	OSD230SeqSend(ATTR_ROW2,CII_COL7+(TvMenuNum*6),OSD_RED,2);
				else		OSD230SeqSend(ATTR_ROW2,CII_COL7+(GetTvTopMenu()*6),OSD_RED,4);

			}
			else	//두번째가 tv이므로 제외하기 위하여
			{
				if(OsdGrade==0)	OSD230SeqSend(ATTR_ROW2,CII_COL7+((TvMenuNum-1)*6),OSD_RED,2);
				else		OSD230SeqSend(ATTR_ROW2,CII_COL7+((GetTvTopMenu()-1)*6),OSD_RED,4);
			}
		}               
	}
	#else	//---------------------------------------------------------------
	if( (CurrentFunction!=Tuner_mode)&&(CurrentFunction!=Composite_mode)&&(CurrentFunction!=Svideo_mode) )
	{	// PC
		if(OsdGrade==0)	OSD230SeqSend(ATTR_ROW2,CII_COL1+(MenuNum*4),OSD_BLUE,4);
		else		OSD230SeqSend(ATTR_ROW2,CII_COL1+(GetTopMenu()*4),OSD_BLUE,4);
	}
	else	// Video
	{
		if(CurrentFunction==Tuner_mode)	// Tv 일때
		{
			if(OsdGrade==0)	OSD230SeqSend(ATTR_ROW2,CII_COL5+(TvMenuNum*6),OSD_BLUE,2);
			else		OSD230SeqSend(ATTR_ROW2,CII_COL5+(GetTvTopMenu()*6),OSD_BLUE,4);
		}
		else if(CurrentFunction==Composite_mode||CurrentFunction==Svideo_mode)	// AV1,2 일때
		{
			if(TvMenuNum==TvTopMenuStart)
			{
				if(OsdGrade==0)	OSD230SeqSend(ATTR_ROW2,CII_COL7+(TvMenuNum*6),OSD_BLUE,2);
				else		OSD230SeqSend(ATTR_ROW2,CII_COL7+(GetTvTopMenu()*6),OSD_BLUE,4);

			}
			else	//두번째가 tv이므로 제외하기 위하여
			{
				if(OsdGrade==0)	OSD230SeqSend(ATTR_ROW2,CII_COL7+((TvMenuNum-1)*6),OSD_BLUE,2);
				else		OSD230SeqSend(ATTR_ROW2,CII_COL7+((GetTvTopMenu()-1)*6),OSD_BLUE,4);
			}
		}               
	}
	#endif	//---------------------------------------------------------
#endif
}

void Hue_ColorBar(void)
{
	#ifndef OsdMenuFullBar	//-------------
	if(OsdGrade==1)		OSD230SeqSend(ATTR_ROW7,CII_COL0,OSD_RED,10);
	else if(OsdGrade==2)	OSD230SeqSend(ATTR_ROW7,CII_COL0,OSD_RED,5);
	
	if(xEEPROMBuffer[AVTINT]==50)	  OSD230SeqSend(ATTR_ROW7,CII_COL11,OSD_BLUE_BG|OSD_WHITE,16);
	else if(xEEPROMBuffer[AVTINT]>50) OSD230SeqSend(ATTR_ROW7,CII_COL11,OSD_GREEN_BG|OSD_WHITE,16);
	else if(xEEPROMBuffer[AVTINT]<50) OSD230SeqSend(ATTR_ROW7,CII_COL11,OSD_RED_BG|OSD_WHITE,16);
	#else	//-----------------------------
		#if defined(OsdColor_Red)
	OSD230SeqSend(ATTR_ROW7,CII_COL0,OSD_RED_BG|OSD_WHITE,29);
		#else
	if(xEEPROMBuffer[AVTINT]==50)	  OSD230SeqSend(ATTR_ROW7,CII_COL0,OSD_BLUE_BG|OSD_WHITE,29);
	else if(xEEPROMBuffer[AVTINT]>50) OSD230SeqSend(ATTR_ROW7,CII_COL0,OSD_GREEN_BG|OSD_WHITE,29);
	else if(xEEPROMBuffer[AVTINT]<50) OSD230SeqSend(ATTR_ROW7,CII_COL0,OSD_RED_BG|OSD_WHITE,29);
		#endif
	#endif	//-----------------------------
}
       
void	MenuSel()
{               
	BYTE count=0;
		
	if(OsdGrade==3 && TvMenuNum==tvmenu_channel_edit)
	{
		//OSD230SeqSend(ATTR_ROW5,CII_COL0,0x00,30);
	}
	else	OsdAttrClear();

	if((TvMenuNum == tvmenu_channel_edit)&&(OsdGrade==2)) OsdAttr_row10_Clear();
	//---------------------------------------------------------------------------------
	//if( (xEEPROMBuffer[MainSubInputSource]!=10)&&(xEEPROMBuffer[MainSubInputSource]!=14)&&(xEEPROMBuffer[MainSubInputSource]!=18) )	// PC일때
	if( (CurrentFunction!=Tuner_mode)&&(CurrentFunction!=Composite_mode)&&(CurrentFunction!=Svideo_mode) )
	{	// PC일때
		switch( GetTopMenu() )
		{       
			case MENU_DISPLAY:
				count=MenuNum-DisplayMenuStart;
				break;
			case MENU_RGB:
				count=MenuNum-RgbMenuStart;
				break;
			case MENU_OSD:
				count=MenuNum-OsdMenuStart;
				break;
			case MENU_PIP:
				count=MenuNum-PipMenuStart;
				break;
			case MENU_TOOLS:
				count=MenuNum-ToolsMenuStart;
				break;
			case MENU_SOUND:				//added smpark 20030708
				count=MenuNum-SoundMenuStart;
				break;
		}
	}
	else	// TV, video 일때//---------------------------------------------------------------------------------
	{
		switch( GetTvTopMenu() )
		{       
			case TVMENU_PICTURE:
				count=TvMenuNum-TvPictureStart;
				break;
			case TVMENU_SETUP:
				count=TvMenuNum-TvSetupStart;
				break;
			case TVMENU_TOOLS:
				count=TvMenuNum-TvToolsStart;
				break;			// smpark 20030722
			case TVMENU_SOUND:	//smpark 20030719
				count=TvMenuNum-TvSoundStart;
				break;
		}
	}
	
#ifdef IntOsdBar		//내부osd의 글자 백그라운드를 이용한 메뉴바..
	//---------------------------------------------------------------------------------
	//	메뉴 선택시 선택된 메뉴바의 형태&색깔 지정
	//---------------------------------------------------------------------------------
	if( (TvMenuNum == tvmenu_country)&&(OsdGrade==2) )	// tv -> country (language)
	{
		MenuVal=xEEPROMBuffer[LANGUAGE_buf];
		
		#if defined (USE_NTSCtuner)
			if(KEY_value == DownKey)
			{
				if(MenuVal >=TV_JAPAN) MenuVal = TV_USA;
				else MenuVal++;
			}
			else if(KEY_value == UpKey)
			{
				if(MenuVal <= TV_USA) MenuVal = TV_JAPAN;
				else MenuVal--;
			}
		
			#ifndef	OsdMenuFullBar
			OSD230SeqSend(ATTR_ROW4+MenuVal,CII_COL0,OSD_RED,29);
			#else
				#if defined (OsdColor_Red)
			OSD230SeqSend(ATTR_ROW4+MenuVal,CII_COL5,OSD_RED_BG|OSD_WHITE,9);	//OsdMenuFullBar
				#else
			OSD230SeqSend(ATTR_ROW4+MenuVal,CII_COL5,OSD_BLUE_BG|OSD_WHITE,9);	//OsdMenuFullBar
				#endif
			#endif			
		#elif defined	(USE_PALSECAMtuner)
			
			if(KEY_value == DownKey)
			{
				if(MenuVal >=China) MenuVal = English;
				else MenuVal++;
			}
			else if(KEY_value == UpKey)
			{
				if(MenuVal <= English) MenuVal = China;
				else MenuVal--;
			}
			
			//MenuVal = English;	//임시 변경//2003-12-24 4:17오후

			#ifndef	OsdMenuFullBar
			OSD230SeqSend(ATTR_ROW4+MenuVal,CII_COL0,OSD_RED,29);
			#else
				#if defined (OsdColor_Red)
			OSD230SeqSend(ATTR_ROW4+MenuVal,CII_COL5,OSD_RED_BG|OSD_WHITE,15);	//OsdMenuFullBar
				#else
			OSD230SeqSend(ATTR_ROW4+MenuVal,CII_COL5,OSD_BLUE_BG|OSD_WHITE,15);	//OsdMenuFullBar
				#endif
			#endif	
		#endif	
		
		PutData();
	}
    #ifdef Ccd_Vchip
	else if( (TvMenuNum == tvmenu_Ccd)&&(OsdGrade==2) )
	{
		if(KEY_value == DownKey)
		{
			if(SubMenuVal >= ccd_display) SubMenuVal = ccd_caption;
			else SubMenuVal++;
		}
		else if(KEY_value == UpKey)
		{
			if(SubMenuVal <= ccd_caption) SubMenuVal = ccd_display;
			else SubMenuVal--;
		}
		
		//OSD230SeqSend(ATTR_ROW5+MenuVal,CII_COL0,OSD_BLUE_BG|OSD_WHITE,29);
		OSD230SeqSend(ATTR_ROW5+SubMenuVal,CII_COL0,OSD_CYAN_BG|OSD_BLUE,29);
	}
    #endif
	else if( TvMenuNum == tvmenu_tint )	//2003-09-09
	{
		Hue_ColorBar();
	}
	else if( (TvMenuNum == tvmenu_channel_edit)&&(OsdGrade>=2) )	// tv -> Program edit, PAL_ITVCHANNEL_adr:0x24
	{
		if(OsdGrade==2)
		{
		#ifdef OsdMenuType1
			#ifndef	OsdMenuFullBar
			OSD230SeqSend(ATTR_ROW5+(xEEPROMBuffer[CurrentChannel]%5),CII_COL0,OSD_RED,29);
			#else
				#if defined(OsdColor_Red)
			OSD230SeqSend(ATTR_ROW5+(xEEPROMBuffer[CurrentChannel]%5),CII_COL2,OSD_RED_BG|OSD_WHITE,25);	//OsdMenuFullBar
				#else
			OSD230SeqSend(ATTR_ROW5+(xEEPROMBuffer[CurrentChannel]%5),CII_COL2,OSD_BLUE_BG|OSD_WHITE,25);	//OsdMenuFullBar
				#endif
			#endif			
		#else
			#ifndef	OsdMenuFullBar
			OSD230SeqSend(ATTR_ROW6+(xEEPROMBuffer[CurrentChannel]%5),CII_COL0,OSD_RED,29);
			#else
				#if defined(OsdColor_Red)
			OSD230SeqSend(ATTR_ROW6+(xEEPROMBuffer[CurrentChannel]%5),CII_COL2,OSD_RED_BG|OSD_WHITE,25);	//OsdMenuFullBar
				#else
			OSD230SeqSend(ATTR_ROW6+(xEEPROMBuffer[CurrentChannel]%5),CII_COL2,OSD_BLUE_BG|OSD_WHITE,25);	//OsdMenuFullBar
				#endif
			//OSD230SeqSend(ATTR_ROW6+(xEEPROMBuffer[CurrentChannel]%5),CII_COL2,OSD_BLUE_BG|OSD_YELLOW,25);	//OsdMenuFullBar
			#endif
		#endif
		}
		else
		{

		}
	}

	else if( ((tvmenu_brightness <= TvMenuNum)&&(TvMenuNum < MaxTvMenuNum)) && OsdGrade==1 )
	{
		#ifndef OsdMenuFullBar
		OSD230SeqSend(ATTR_ROW3+count,CII_COL0,OSD_RED,10);
			#if deifned(OsdColor_Red)
		OSD230SeqSend(ATTR_ROW3+count,CII_COL11,OSD_RED_BG|OSD_WHITE,16);
			#else
		OSD230SeqSend(ATTR_ROW3+count,CII_COL11,OSD_BLUE_BG|OSD_WHITE,16);
			#endif
		#else
			#if defined(OsdColor_Red)
		OSD230SeqSend(ATTR_ROW3+count,CII_COL0,OSD_RED_BG|OSD_WHITE,29);	//OsdMenuFullBar
			#else
		OSD230SeqSend(ATTR_ROW3+count,CII_COL0,OSD_BLUE_BG|OSD_WHITE,29);	//OsdMenuFullBar
			#endif
		#endif
	}

	else if(MenuNum==menu_Rgain)
	{
		#ifndef	OsdMenuFullBar
		OSD230SeqSend(ATTR_ROW3+count,CII_COL0,OSD_RED,4);
		OSD230SeqSend(ATTR_ROW3+count,CII_COL11,OSD_RED_BG|OSD_WHITE,16);
		#else
		OSD230SeqSend(ATTR_ROW3+count,CII_COL0,OSD_RED,29);	//OsdMenuFullBar
		OSDSeqSend(IN_ATTR_ROW3+count,IN_CII_COL0,OSD_WHITE_BG,29); //내부
		#endif
	}
	else if(MenuNum==menu_Ggain)
	{
		#ifndef	OsdMenuFullBar
		OSD230SeqSend(ATTR_ROW3+count,CII_COL0,OSD_GREEN,4);
		OSD230SeqSend(ATTR_ROW3+count,CII_COL11,OSD_GREEN_BG|OSD_WHITE,16);
		#else
		OSD230SeqSend(ATTR_ROW3+count,CII_COL0,OSD_GREEN,29);	//OsdMenuFullBar
		OSDSeqSend(IN_ATTR_ROW3+count,IN_CII_COL0,OSD_WHITE_BG,29); //내부
		#endif
	}
	else if(MenuNum==menu_Bgain)
	{
		#ifndef	OsdMenuFullBar
		OSD230SeqSend(ATTR_ROW3+count,CII_COL0,OSD_BLUE,4);
		OSD230SeqSend(ATTR_ROW3+count,CII_COL11,OSD_BLUE_BG|OSD_WHITE,16);
		#else
		OSD230SeqSend(ATTR_ROW3+count,CII_COL0,OSD_BLUE,29);	//OsdMenuFullBar
		OSDSeqSend(IN_ATTR_ROW3+count,IN_CII_COL0,OSD_WHITE_BG,29); //내부
		#endif
	}
	//else if(GetTopMenu()==MENU_PIP && MenuNum!=menu_pip_enable && OsdGrade==1 && !PipOnOffFlag)	return;
	else
	{
		#ifndef	OsdMenuFullBar
		OSD230SeqSend(ATTR_ROW3+count,CII_COL0,OSD_RED,29);
		#else
			#if defined(OsdColor_Red)
		OSD230SeqSend(ATTR_ROW3+count,CII_COL0,OSD_WHITE,29);	//OsdMenuFullBar
		OSDSeqSend(IN_ATTR_ROW3+count,IN_CII_COL0,OSD_RED_BG,29); //내부
			#else
		OSD230SeqSend(ATTR_ROW3+count,CII_COL0,OSD_WHITE,29);	//OsdMenuFullBar
		OSDSeqSend(IN_ATTR_ROW3+count,IN_CII_COL0,OSD_BLUE_BG,29); //내부
			#endif
		#endif
	}
#else
	//---------------------------------------------------------------------------------
	//	메뉴 선택시 선택된 메뉴바의 형태&색깔 지정
	//---------------------------------------------------------------------------------
	if( (TvMenuNum == tvmenu_country)&&(OsdGrade==2) )	// tv -> country (language)
	{
		MenuVal=xEEPROMBuffer[LANGUAGE_buf];
		
		#if defined (USE_NTSCtuner)
			if(KEY_value == DownKey)
			{
				if(MenuVal >=TV_JAPAN) MenuVal = TV_USA;
				else MenuVal++;
			}
			else if(KEY_value == UpKey)
			{
				if(MenuVal <= TV_USA) MenuVal = TV_JAPAN;
				else MenuVal--;
			}
		
			#ifndef	OsdMenuFullBar
			OSD230SeqSend(ATTR_ROW4+MenuVal,CII_COL0,OSD_RED,29);
			#else
				#if defined (OsdColor_Red)
			OSD230SeqSend(ATTR_ROW4+MenuVal,CII_COL5,OSD_RED_BG|OSD_WHITE,9);	//OsdMenuFullBar
				#else
			OSD230SeqSend(ATTR_ROW4+MenuVal,CII_COL5,OSD_BLUE_BG|OSD_WHITE,9);	//OsdMenuFullBar
				#endif
			#endif			
		#elif defined	(USE_PALSECAMtuner)
			
			if(KEY_value == DownKey)
			{
				if(MenuVal >=China) MenuVal = English;
				else MenuVal++;
			}
			else if(KEY_value == UpKey)
			{
				if(MenuVal <= English) MenuVal = China;
				else MenuVal--;
			}
			
			//MenuVal = English;	//임시 변경//2003-12-24 4:17오후

			#ifndef	OsdMenuFullBar
			OSD230SeqSend(ATTR_ROW3+MenuVal,CII_COL0,OSD_RED,29);
			#else
				#if defined (OsdColor_Red)
			OSD230SeqSend(ATTR_ROW3+MenuVal,CII_COL5,OSD_RED_BG|OSD_WHITE,15);	//OsdMenuFullBar
				#else
			OSD230SeqSend(ATTR_ROW3+MenuVal,CII_COL5,OSD_BLUE_BG|OSD_WHITE,15);	//OsdMenuFullBar
				#endif
			#endif	
		#endif	
		
		PutData();
	}
    #ifdef Ccd_Vchip
	else if( (TvMenuNum == tvmenu_Ccd)&&(OsdGrade==2) )
	{
		if(KEY_value == DownKey)
		{
			if(SubMenuVal >= ccd_display) SubMenuVal = ccd_caption;
			else SubMenuVal++;
		}
		else if(KEY_value == UpKey)
		{
			if(SubMenuVal <= ccd_caption) SubMenuVal = ccd_display;
			else SubMenuVal--;
		}
		
		//OSD230SeqSend(ATTR_ROW5+MenuVal,CII_COL0,OSD_BLUE_BG|OSD_WHITE,29);
		OSD230SeqSend(ATTR_ROW5+SubMenuVal,CII_COL0,OSD_CYAN_BG|OSD_BLUE,29);
	}
    #endif
	else if( TvMenuNum == tvmenu_tint )	//2003-09-09
	{
		Hue_ColorBar();
	}
	else if( (TvMenuNum == tvmenu_channel_edit)&&(OsdGrade>=2) )	// tv -> Program edit, PAL_ITVCHANNEL_adr:0x24
	{
		if(OsdGrade==2)
		{
		#ifdef OsdMenuType1
			#ifndef	OsdMenuFullBar
			OSD230SeqSend(ATTR_ROW5+(xEEPROMBuffer[CurrentChannel]%5),CII_COL0,OSD_RED,29);
			#else
				#if defined(OsdColor_Red)
			OSD230SeqSend(ATTR_ROW5+(xEEPROMBuffer[CurrentChannel]%5),CII_COL2,OSD_RED_BG|OSD_WHITE,25);	//OsdMenuFullBar
				#else
			OSD230SeqSend(ATTR_ROW5+(xEEPROMBuffer[CurrentChannel]%5),CII_COL2,OSD_BLUE_BG|OSD_WHITE,25);	//OsdMenuFullBar
				#endif
			#endif			
		#else
			#ifndef	OsdMenuFullBar
			OSD230SeqSend(ATTR_ROW6+(xEEPROMBuffer[CurrentChannel]%5),CII_COL0,OSD_RED,29);
			#else
				#if defined(OsdColor_Red)
			OSD230SeqSend(ATTR_ROW6+(xEEPROMBuffer[CurrentChannel]%5),CII_COL2,OSD_RED_BG|OSD_WHITE,25);	//OsdMenuFullBar
				#else
			OSD230SeqSend(ATTR_ROW6+(xEEPROMBuffer[CurrentChannel]%5),CII_COL2,OSD_BLUE_BG|OSD_WHITE,25);	//OsdMenuFullBar
				#endif
			//OSD230SeqSend(ATTR_ROW6+(xEEPROMBuffer[CurrentChannel]%5),CII_COL2,OSD_BLUE_BG|OSD_YELLOW,25);	//OsdMenuFullBar
			#endif
		#endif
		}
		else
		{

		}
	}

	else if( ((tvmenu_brightness <= TvMenuNum)&&(TvMenuNum < MaxTvMenuNum)) && OsdGrade==1 )
	{
		#ifndef OsdMenuFullBar
		OSD230SeqSend(ATTR_ROW3+count,CII_COL0,OSD_RED,10);
			#if deifned(OsdColor_Red)
		OSD230SeqSend(ATTR_ROW3+count,CII_COL11,OSD_RED_BG|OSD_WHITE,16);
			#else
		OSD230SeqSend(ATTR_ROW3+count,CII_COL11,OSD_BLUE_BG|OSD_WHITE,16);
			#endif
		#else
			#if defined(OsdColor_Red)
		OSD230SeqSend(ATTR_ROW3+count,CII_COL0,OSD_RED_BG|OSD_WHITE,29);	//OsdMenuFullBar
			#else
		OSD230SeqSend(ATTR_ROW3+count,CII_COL0,OSD_BLUE_BG|OSD_WHITE,29);	//OsdMenuFullBar
			#endif
		#endif
	}

	else if(MenuNum==menu_Rgain)
	{
		#ifndef	OsdMenuFullBar
		OSD230SeqSend(ATTR_ROW3+count,CII_COL0,OSD_RED,4);
		OSD230SeqSend(ATTR_ROW3+count,CII_COL11,OSD_RED_BG|OSD_WHITE,16);
		#else
		OSD230SeqSend(ATTR_ROW3+count,CII_COL0,OSD_WHITE_BG|OSD_RED,29);	//OsdMenuFullBar
		#endif
	}
	else if(MenuNum==menu_Ggain)
	{
		#ifndef	OsdMenuFullBar
		OSD230SeqSend(ATTR_ROW3+count,CII_COL0,OSD_GREEN,4);
		OSD230SeqSend(ATTR_ROW3+count,CII_COL11,OSD_GREEN_BG|OSD_WHITE,16);
		#else
		OSD230SeqSend(ATTR_ROW3+count,CII_COL0,OSD_WHITE_BG|OSD_GREEN,29);	//OsdMenuFullBar
		#endif
	}
	else if(MenuNum==menu_Bgain)
	{
		#ifndef	OsdMenuFullBar
		OSD230SeqSend(ATTR_ROW3+count,CII_COL0,OSD_BLUE,4);
		OSD230SeqSend(ATTR_ROW3+count,CII_COL11,OSD_BLUE_BG|OSD_WHITE,16);
		#else
		OSD230SeqSend(ATTR_ROW3+count,CII_COL0,OSD_WHITE_BG|OSD_BLUE,29);	//OsdMenuFullBar
		#endif
	}
	else
	{
		#ifndef	OsdMenuFullBar
		OSD230SeqSend(ATTR_ROW3+count,CII_COL0,OSD_RED,29);
		#else
			#if defined(OsdColor_Red)
		OSD230SeqSend(ATTR_ROW3+count,CII_COL0,OSD_RED_BG|OSD_WHITE,29);	//OsdMenuFullBar
		//OSDSeqSend(IN_ATTR_ROW3+count,IN_CII_COL0,IN_OSD_RED_BG|IN_OSD_WHITE,29); //내부
			#else
		OSD230SeqSend(ATTR_ROW3+count,CII_COL0,OSD_BLUE_BG|OSD_WHITE,29);	//OsdMenuFullBar
			#endif
		#endif
	}
#endif
}


void	Display_TopMenuIcon(void)
{
	//-------------top title + icon display
	//MAIN MENU(PC ADJUST)
	OSD230SeqSend(ATTR_ROW1,CII_COL10,OSD_WHITE,Mainmenu_Sizeof[xEEPROMBuffer[LANGUAGE_buf]]); 			//Attribute data
	OSD230SeqSend(DSP_ROW1,CII_COL0,0x00,30);
	//if(NowTopOsdOn&&OsdMenuOnFlag==0)
	//{
	//	OsdMenuOnFlag=1;
	
	//--------------------- OSD English , Other Country Select ... OSD High Area Select 040728 +jwshin
	if(xEEPROMBuffer[LANGUAGE_buf]!=English) HighOSDArea=1;
	else HighOSDArea=0;
	//--------------------- End...
	
		OSD230PtrSend(DSP_ROW1,CII_COL10,Mainmenu[xEEPROMBuffer[LANGUAGE_buf]],Mainmenu_Sizeof[xEEPROMBuffer[LANGUAGE_buf]]); 	//Display data
	HighOSDArea=0;	//----------- OSD High Area Select Release +jwshin
		
	//}
	//Main ICON menu 
	OSD230SeqSend(ATTR_ROW2,CII_COL0,OSD_BLACK,30);	//Attribute data, top icon color
	xOSDRA=DSP_ROW2;
	xOSDCA=CII_COL30;
	xOSDDT0=HVchar_dbl;	//double hieght,width (0x03)
//	OSD230PtrSend(DSP_ROW2,CII_COL0+2,MainIconMenu[0],MainIconMenu_Sizeof[0]);//Display data
	OSD230PtrSend(DSP_ROW2,CII_COL0,MainIconMenu[0],MainIconMenu_Sizeof[0]);//smpark
	//--------------
	
}
void	Display_TvTopMenuIcon(void)
{
	//-------------top title + icon display
	//MAIN MENU(TV ADJUST)
	OSD230SeqSend(ATTR_ROW1,CII_COL10,OSD_WHITE,TvMainmenu_Sizeof[0]); 			//Attribute data
	OSD230SeqSend(DSP_ROW1,CII_COL0,0x00,30);
	
	#ifdef	OsdMenuType1
	switch(xEEPROMBuffer[MainSubInputSource])
	{
		case 8://COMPOSITE
		case 10:
			OSD230SeqSend(ATTR_ROW1,CII_COL0,OSD_WHITE,30);	//Attribute(black) data(total black!!)
			OSD230SeqSend(DSP_ROW1, CII_COL0,0x00,30);	//Clear
			
			OSD230PtrSend(DSP_ROW1,(30-Composite_Sizeof[0])/2,Composite[0],Composite_Sizeof[0]); //Display data
			break;
		
		case 12://S-video
		case 14:
			OSD230SeqSend(ATTR_ROW1,CII_COL0,OSD_WHITE,30);	//Attribute(black) data(total black!!)
			OSD230SeqSend(DSP_ROW1, CII_COL0,0x00,30);	//Clear
			
			OSD230PtrSend(DSP_ROW1,(30-Svideo_Sizeof[0])/2,Svideo[0],Svideo_Sizeof[0]); //Display data
			break;
			
		case 16://TUNER
		case 18:
			OSD230SeqSend(ATTR_ROW1,CII_COL0,OSD_WHITE,30);	//Attribute(black) data(total black!!)
			OSD230SeqSend(DSP_ROW1, CII_COL0,0x00,30);	//Clear
			
			OSD230PtrSend(DSP_ROW1,(30-Tuner_Sizeof[0])/2,Tuner[0],Tuner_Sizeof[0]); //Display data
			break;
	}
	#else
	//if(NowTopOsdOn&&OsdMenuOnFlag==0)
	if(NowTopOsdOn)
	{
		//OsdMenuOnFlag=1;
		if(CurrentFunction==Tuner_mode)
			OSD230PtrSend(DSP_ROW1,CII_COL10,TvMainmenu[0],TvMainmenu_Sizeof[0]); 	//Display data
		else if(CurrentFunction==Composite_mode || CurrentFunction==Svideo_mode)
			OSD230PtrSend(DSP_ROW1,CII_COL10,AvMainmenu[0],AvMainmenu_Sizeof[0]); 	//Display data
	}
	#endif
	//Main ICON menu
	OSD230SeqSend(ATTR_ROW2,CII_COL0,OSD_BLACK,30); 	//Attribute data
	//xOSDRA=DSP_ROW2;
	//xOSDCA=CII_COL30;
	//xOSDDT0=VHchar_dbl;	//double hieght,width (0x03)
	
	#if defined(VideoDoubleOSD)
	//----------------
	#if 1
	xOSD_WIN_REG[0x0E] = 0x0f;	//character height
	#else
	xOSDRA=DSP_ROW1; xOSDCA=CII_COL30; xOSDDT0=Vchar_dbl;
	xOSDRA=DSP_ROW2; xOSDCA=CII_COL30; xOSDDT0=Vchar_dbl;
	xOSDRA=DSP_ROW3; xOSDCA=CII_COL30; xOSDDT0=Vchar_dbl;
	xOSDRA=DSP_ROW4; xOSDCA=CII_COL30; xOSDDT0=Vchar_dbl;
	xOSDRA=DSP_ROW5; xOSDCA=CII_COL30; xOSDDT0=Vchar_dbl;
	xOSDRA=DSP_ROW6; xOSDCA=CII_COL30; xOSDDT0=Vchar_dbl;
	xOSDRA=DSP_ROW7; xOSDCA=CII_COL30; xOSDDT0=Vchar_dbl;
	xOSDRA=DSP_ROW8; xOSDCA=CII_COL30; xOSDDT0=Vchar_dbl;
	xOSDRA=DSP_ROW9; xOSDCA=CII_COL30; xOSDDT0=Vchar_dbl;
	xOSDRA=DSP_ROW10; xOSDCA=CII_COL30; xOSDDT0=Vchar_dbl;
	xOSDRA=DSP_ROW11; xOSDCA=CII_COL30; xOSDDT0=Vchar_dbl;
	xOSDRA=DSP_ROW12; xOSDCA=CII_COL30; xOSDDT0=Vchar_dbl;
	#endif
	//----------------
	#else
	xOSD_WIN_REG[0x0E] = 0x00;	//character height
	#endif
	OSD230SeqSend(ATTR_ROW2,CII_COL0,OSD_BLACK,30); 
	
	//Tv 메뉴와 Av 메뉴 분리,	2003-09-08
	if(CurrentFunction==Tuner_mode)	
		OSD230PtrSend(DSP_ROW2,CII_COL5,TvMainIconMenu[0],TvMainIconMenu_Sizeof[0]);
	else if(CurrentFunction==Composite_mode || CurrentFunction==Svideo_mode)
		OSD230PtrSend(DSP_ROW2,CII_COL7, AvMainIconMenu[0],AvMainIconMenu_Sizeof[0]);

	xOSDRA=DSP_ROW2; xOSDCA=CII_COL30; xOSDDT0=Vchar_dbl;
	//--------------
}


#ifdef test_function
#if 1
void	MenuNum_display(void)//test
{
	BYTE	count;
	BYTE	mnum;
	unsigned int CheckPageNum=(xEEPROMBuffer[CurrentChannel]/5);//test
	
	if( (xEEPROMBuffer[MainSubInputSource]!=10)&&(xEEPROMBuffer[MainSubInputSource]!=14)&&(xEEPROMBuffer[MainSubInputSource]!=18) )
	{
		mnum=MenuNum;
	}
	else
	{
		mnum=TvMenuNum;
	}
	OSD230SeqSend(DSP_ROW1,CII_COL0,0x00,5);//clear
	
	OSD230SeqSend(ATTR_ROW1,CII_COL0,OSD_WHITE,30);//color
	
	OSD230RowSend(DSP_ROW1);
	OSD230ColSend(CII_COL1);
	count = calToChar(mnum);
	DisplayInfo(count);
	
	OSD230ColSend(CII_COL4);
	count = calToChar(xEEPROMBuffer[SystemCountry]);
	DisplayInfo(count);
	
	//OSD230ColSend(CII_COL7);
	//count = calToChar(xEEPROMBuffer[ColorTemp]);
	//DisplayInfo(count);
	
	//OSD230ColSend(CII_COL7);
	//count = calToChar(xEEPROMBuffer[MainSubInputSource]);//CurrentFunction;
	//DisplayInfo(count);
	
	//OSD230ColSend(CII_COL6);
	//count = calToChar(PipOnOffFlag);
	//DisplayInfo(count);
	
	//OSD230ColSend(CII_COL20);
	//count = calToChar(PipHPositionNum);
	//DisplayInfo(count);

//	OSD230SeqSend(DSP_ROW1,CII_COL20,0x00,2);
//	OSD230ColSend(CII_COL20);
//	count = calToChar(TvMenuNum);
//	DisplayInfo(count);

	//OSD230SeqSend(DSP_ROW1,CII_COL22,0x00,2);
	//OSD230ColSend(CII_COL22);
	//count = calToChar(ChEdit_CharNum);
	//DisplayInfo(count);

//	OSD230SeqSend(DSP_ROW1,CII_COL22,0x00,2);
//	OSD230ColSend(CII_COL22);
//	count = calToChar(MenuNum);
//	DisplayInfo(count);
}

#endif

#if 0
if(MenuNum==menu_pip_enable)
{ 
{
	#define	DSP_ROW1	0x01
	#define	CII_COL4	0x04
	
	idata BYTE count;
	void OSD230SeqSend(BYTE Recdata0,BYTE Recdata1,BYTE Recdata2,BYTE Recdata3);
	void OSD230ColSend(BYTE Recdata);
	BYTE calToChar(DWORD Recdata);
	void 	DisplayInfo(BYTE count);
	
	OSD230SeqSend(DSP_ROW1,CII_COL4,0x00,2);
	OSD230ColSend(CII_COL4);
	count = calToChar(PipOnOffFlag);
	DisplayInfo(count);
	
	//LED_OFF;idelay5m(10);LED_ON;	//test
	//while(1);	//test
}
}//test	
#endif

#endif

void Display_AdjustInfo(void)	//main menu 조정 설명.
{
#ifndef	OsdMenuType1	//test2003-10-27
	HighOSDArea=0;
	OSD230SeqSend(ATTR_ROW10,CII_COL0,OSD_BLACK,30);
	OSD230SeqSend(DSP_ROW10,CII_COL0,OSD_BLACK,30); 
	
	OSD230SeqSend2(DSP_ROW10,CII_COL0,_LTriAngle,_RTriAngle);
	OSD230SeqSend2(DSP_ROW10,CII_COL9,_LRectAngle,_M);
	OSD230SeqSend2(DSP_ROW10,CII_COL11,_RRectAngle,0);
	OSD230SeqSend2(DSP_ROW10,CII_COL19,_UpTriAngle,_DnTriAngle);

	switch(xEEPROMBuffer[LANGUAGE_buf]){	// smpark 20030821
		case English:
			HighOSDArea=0;
			break;
			
		#ifdef USE_NTSCtuner
		case Korea:
		case Japan:
			HighOSDArea=1;
			break;
		#endif
	}
	
	OSD230PtrSend(DSP_ROW10,CII_COL2,Adjust[xEEPROMBuffer[LANGUAGE_buf]],Adjust_Sizeof[xEEPROMBuffer[LANGUAGE_buf]]);		// ADJUST
	OSD230PtrSend(DSP_ROW10,CII_COL12,Return[xEEPROMBuffer[LANGUAGE_buf]],Return_Sizeof[xEEPROMBuffer[LANGUAGE_buf]]);		// RETURN
	OSD230PtrSend(DSP_ROW10,CII_COL21,Position[xEEPROMBuffer[LANGUAGE_buf]],Position_Sizeof[xEEPROMBuffer[LANGUAGE_buf]]);		// POSITION
	
	HighOSDArea=0;
#endif
}

void Display_CountyrBottomInfo(void)	//main menu 조정 설명.
{
	OSD230SeqSend(ATTR_ROW8,CII_COL0,0x00,30); 				//Attribute data
	OSD230PtrSend(DSP_ROW8,CII_COL0+(30-CountryBottomInfo_Sizeof[0])/2,CountryBottomInfo[0],CountryBottomInfo_Sizeof[0]); 	//Display data
	//OSD230PtrSend(DSP_ROW8,CII_COL0,CountryBottomInfo[xEEPROMBuffer[LANGUAGE_buf]],CountryBottomInfo_Sizeof[xEEPROMBuffer[LANGUAGE_buf]]); 	//Display data
}

void Display_BottomCurrentInfo(void)	//main menu 제일 아래부분에 화면 정보 표시.
{
#if 1	//test2003-10-27
	idata	BYTE count,temp,DisplayRow,DisplayRowAttr;
	#ifdef	OsdMenuType1
	DisplayRowAttr=ATTR_ROW11;
	DisplayRow=DSP_ROW11;
	#else
	DisplayRowAttr=ATTR_ROW12;
	DisplayRow=DSP_ROW12;
	#endif
	
			//****************************************************************//
			//TOPMENU상에서 하단 information 표시문구
			//****************************************************************//
			if( !((TopMenuStart<=MenuNum)&&(MenuNum<=TopMenuEnd)) )
			{
				OSD230SeqSend(DisplayRow,CII_COL0,OSD_BLACK,30);
			}
			
			switch(xEEPROMBuffer[MainSubInputSource])
			{
				case 0://RGB
				case 2://RGB
				case 6://DVI
					//****************************************************************//
					//resolution display
					//****************************************************************//
					OSD230SeqSend(DisplayRowAttr,CII_COL0,OSD_WHITE,30);	//character color
					//OSD230SeqSend(DisplayRow, CII_COL0,_,30);		//Clear
					
					
					OSD230RowSend(DisplayRow);
					OSD230ColSend(CII_COL2);
					count = calToChar(NowHactive);
					//OSD230SeqSend(ATTR_ROW12,CII_COL1,OSD_WHITE,count); //Attribute data
					temp=CII_COL2+count;	//나중에 칼럼위치 변경 요망-> 가운데 정렬로.
					
					DisplayInfo(count);	//Hactive
					
					count = calToChar(NowHactive);
					OSD230RowSend(DisplayRow);
					OSD230ColSend(CII_COL2+count);
					OSD230DataSend(_x);
            		
					//count = calToChar(NowHactive)+1;
					OSD230RowSend(DisplayRow);
					OSD230ColSend(CII_COL2+count+1);
					count = calToChar(NowVactive);
					temp=temp+count;
					
					DisplayInfo(count);	//Vactive
					
					temp=temp+1;								//jump
					OSD230RowSend(DisplayRow);
					OSD230ColSend(temp);
					OSD230DataSend(_);
					
					//****************************************************************//
					//Frequency display(Hfre)
					//****************************************************************//
					count = calToChar((BYTE)(NowHfreq/10));		
					
					OSD230RowSend(DisplayRow);
					OSD230ColSend(temp+1);
					temp = count+temp;
					
					DisplayInfo(count);	//Hfreq 상수
					
					temp=temp+1;
					OSD230RowSend(DisplayRow);
					OSD230ColSend(temp);
					OSD230DataSend(_dot);						//dot
					
					temp=temp+1;
					count = calToChar((BYTE)(NowHfreq%10));
					OSD230RowSend(DisplayRow);
					OSD230ColSend(temp);
					temp = temp+count;
										
					DisplayInfo(count);	//Hfreq 소수
					
					OSD230PtrSend(DisplayRow,temp,kHz[0],kHz_Sizeof[0]); //Khz
					
		//			temp = temp+kHz_Sizeof[xEEPROMBuffer[LANGUAGE_buf]];
					temp = temp+kHz_Sizeof[0];
					OSD230RowSend(DisplayRow);
					OSD230ColSend(temp);
					OSD230DataSend(_slash);						//slash
            		
					temp=temp+1;
					count = calToChar((BYTE)(NowVfreq/10));		
					OSD230RowSend(DisplayRow);
					OSD230ColSend(temp);
					temp = temp+count;
					
					DisplayInfo(count);	//Vfreq 상수
					
					OSD230PtrSend(DisplayRow,temp,Hz[0],Hz_Sizeof[0]); //Hz
					break;

				#ifdef OsdMenuType1	//-------------------
				case 8://COMPOSITE
				case 10:
					OSD230SeqSend(ATTR_ROW1,CII_COL0,OSD_WHITE,30);	//Attribute(black) data(total black!!)
					OSD230SeqSend(DSP_ROW1, CII_COL0,0x00,30);	//Clear
					
					OSD230PtrSend(DSP_ROW1,(30-Composite_Sizeof[0])/2,Composite[0],Composite_Sizeof[0]); //Display data
					break;
				
				case 12://S-video
				case 14:
					OSD230SeqSend(ATTR_ROW1,CII_COL0,OSD_WHITE,30);	//Attribute(black) data(total black!!)
					OSD230SeqSend(DSP_ROW1, CII_COL0,0x00,30);	//Clear
					
					OSD230PtrSend(DSP_ROW1,(30-Svideo_Sizeof[0])/2,Svideo[0],Svideo_Sizeof[0]); //Display data
					break;
					
				case 16://TUNER
				case 18:
					OSD230SeqSend(ATTR_ROW1,CII_COL0,OSD_WHITE,30);	//Attribute(black) data(total black!!)
					OSD230SeqSend(DSP_ROW1, CII_COL0,0x00,30);	//Clear
					
					OSD230PtrSend(DSP_ROW1,(30-Tuner_Sizeof[0])/2,Tuner[0],Tuner_Sizeof[0]); //Display data
					break;
				#else	//-------------------------------------------
				case 8://COMPOSITE
				case 10:
					OSD230SeqSend(ATTR_ROW12,CII_COL0,OSD_WHITE,30);	//Attribute(black) data(total black!!)
					OSD230SeqSend(DSP_ROW12, CII_COL0,0x00,30);	//Clear
					
					OSD230PtrSend(DSP_ROW12,CII_COL1,Composite[0],Composite_Sizeof[0]); //Display data
					//OSD230DataSend(0x00);//
					//OSD230DataSend(0x00);
					//OSD230PtrSend(DSP_ROW7,CII_COL1+Composite_Sizeof[xEEPROMBuffer[LANGUAGE_buf]]+2,Ntsc[xEEPROMBuffer[LANGUAGE_buf]],Ntsc_Sizeof[xEEPROMBuffer[LANGUAGE_buf]]); //Display data
					break;
				
				case 12://S-video
				case 14:
					OSD230SeqSend(ATTR_ROW12,CII_COL0,OSD_WHITE,30);	//Attribute(black) data(total black!!)
					OSD230SeqSend(DSP_ROW12, CII_COL0,0x00,30);	//Clear
					
					OSD230PtrSend(DSP_ROW12,CII_COL1,Svideo[0],Svideo_Sizeof[0]); //Display data
					//OSD230DataSend(0x00);//
					//OSD230DataSend(0x00);
					//OSD230PtrSend(DSP_ROW7,CII_COL1+Svideo_Sizeof[xEEPROMBuffer[LANGUAGE_buf]]+2,Ntsc[xEEPROMBuffer[LANGUAGE_buf]],Ntsc_Sizeof[xEEPROMBuffer[LANGUAGE_buf]]); //Display data
					break;
					
				case 16://TUNER
				case 18:
					OSD230SeqSend(ATTR_ROW12,CII_COL0,OSD_WHITE,30);	//Attribute(black) data(total black!!)
					OSD230SeqSend(DSP_ROW12, CII_COL0,0x00,30);	//Clear
					
					OSD230PtrSend(DSP_ROW12,CII_COL1,Tuner[0],Tuner_Sizeof[0]); //Display data
					//OSD230DataSend(0x00);//
					//OSD230DataSend(0x00);
					
					/*
					#if defined(USE_NTSCtuner)
					OSD230PtrSend(DSP_ROW12,CII_COL1+Tuner_Sizeof[0]+2,Ntsc[0],Ntsc_Sizeof[0]); //Display data
					#elif defined(USE_PALSECAMtuner)
					OSD230PtrSend(DSP_ROW12,CII_COL1+PalSecam_Sizeof[0]+2,PalSecam[0],PalSecam_Sizeof[0]); //Display data
					#endif
					*/
					break;
				#endif	//--------------------------------------
				
				default://PIP
					//OSD230SeqSend(ATTR_ROW7,CII_COL0,0x00,30);	//Attribute(black) data(total black!!)
					//OSD230SeqSend(DSP_ROW7, CII_COL0,0x00,30);	//Clear
					
					//OSD230PtrSend(DSP_ROW7,CII_COL1,PipSub[xEEPROMBuffer[LANGUAGE_buf]],PipSub_Sizeof[xEEPROMBuffer[LANGUAGE_buf]]); //Display data
					//OSD230DataSend(0x00);//
					//OSD230DataSend(0x00);

					//OSD230SeqSend(DSP_ROW12,CII_COL0,0x00,30);
					
					
					#ifdef OsdMenuType1	//-------------------
					OSD230SeqSend(ATTR_ROW11,CII_COL0,OSD_WHITE,30);	//Attribute(black) data(total black!!)
					OSD230PtrSend(DSP_ROW11,CII_COL1,PipSub[0],PipSub_Sizeof[0]); //Display data
					if(PipInputSource==SourceComposite)
					{
						OSD230PtrSend(DSP_ROW11,CII_COL5,Composite[0],Composite_Sizeof[0]); //Display data
					}
					else if(PipInputSource==SourceSvideo)
					{
						OSD230PtrSend(DSP_ROW11,CII_COL5,Svideo[0],Svideo_Sizeof[0]); //Display data
					}
					if(PipInputSource==SourceTuner)
					{
						OSD230PtrSend(DSP_ROW11,CII_COL5,Tuner[0],Tuner_Sizeof[0]); //Display data
					}
					#else	//------------------------------------
					OSD230SeqSend(ATTR_ROW12,CII_COL0,OSD_WHITE,30);	//Attribute(black) data(total black!!)
					OSD230PtrSend(DSP_ROW12,CII_COL1,PipSub[0],PipSub_Sizeof[0]); //Display data
					if(PipInputSource==SourceComposite)
					{
						OSD230PtrSend(DSP_ROW12,CII_COL5,Composite[0],Composite_Sizeof[0]); //Display data
					}
					else if(PipInputSource==SourceSvideo)
					{
						OSD230PtrSend(DSP_ROW12,CII_COL5,Svideo[0],Svideo_Sizeof[0]); //Display data
					}
					if(PipInputSource==SourceTuner)
					{
						OSD230PtrSend(DSP_ROW12,CII_COL5,Tuner[0],Tuner_Sizeof[0]); //Display data
						/*
						#if defined(USE_NTSCtuner)
						OSD230PtrSend(DSP_ROW12,CII_COL5,Ntsc[0],Ntsc_Sizeof[0]); //Display data
						#elif defined(USE_PALSECAMtuner)
						OSD230PtrSend(DSP_ROW12,CII_COL5,PalSecam[0],PalSecam_Sizeof[0]); //Display data
						#endif
						*/
					}
					#endif	//------------------------------------
					break;
			}
#endif			
}
		
void	PipHVPosition(void)
{
	xBYTE pipBPOSoffset;
	
	#if defined(SXGA_Panel)
		#define H_start 	45
	#elif defined(WXGA_Panel)
		#define H_start 	25
	#else
		#define H_start 	25
	#endif
	
	#define V_start 	6
	#define HVmargin	5
	
	#ifdef PIPstyle2
		pipBPOSoffset=4;
	#else
		pipBPOSoffset=2;
	#endif
		
	
	#if 0
	xEEPROMBuffer[PIPPOSITION] = ( ((PipHPositionNum&0x03)<<4)|(PipVPositionNum&0x03) );
	#endif
	PipHPositionNum=(xEEPROMBuffer[PIPPOSITION]&0x30)>>4;
	PipVPositionNum=xEEPROMBuffer[PIPPOSITION]&0x03;

	#if 0
		switch(xEEPROMBuffer[PIPPOSITION])	//고정 위치 (상,중,하/좌,중,우)
		{
			case 0x00://left-top	//-----------------------------
				WordWriteScaler(0x80,H_start+HVmargin);//main Hstart!
				WordWriteScaler(0x84,V_start+HVmargin);//main Vstart!
				break;

			case 0x01://left-middle
				WordWriteScaler(0x80,H_start+HVmargin);//main Hstart!
				WordWriteScaler(0x84,(ModeList[CurrentMode].IVAW-PipHVawList[xEEPROMBuffer[PIPSIZE_buf]+(BYTE)PipAspectFlag*3].PipVwidth)/2+V_start);//main Vstart!
				break;
														
			case 0x02://left-bottom
				WordWriteScaler(0x80,H_start+HVmargin);//main Hstart!
				WordWriteScaler(0x84,ModeList[CurrentMode].IVAW-PipHVawList[xEEPROMBuffer[PIPSIZE_buf]+(BYTE)PipAspectFlag*3].PipVwidth+V_start-HVmargin);//main Vstart!
				break;
			
			case 0x10://mid-top	//-----------------------------
				WordWriteScaler(0x80,(ModeList[CurrentMode].IHAW-PipHVawList[xEEPROMBuffer[PIPSIZE_buf]+(BYTE)PipAspectFlag*3].PipHwidth)/2+H_start);//main Hstart!
				WordWriteScaler(0x84,V_start+HVmargin);//main Vstart!
				break;
														
			case 0x11://center
				WordWriteScaler(0x80,(ModeList[CurrentMode].IHAW-PipHVawList[xEEPROMBuffer[PIPSIZE_buf]+(BYTE)PipAspectFlag*3].PipHwidth)/2+H_start);//main Hstart!
				WordWriteScaler(0x84,(ModeList[CurrentMode].IVAW-PipHVawList[xEEPROMBuffer[PIPSIZE_buf]+(BYTE)PipAspectFlag*3].PipVwidth)/2+V_start);//main Vstart!
				break;

			case 0x12://mid-bottom
				WordWriteScaler(0x80,(ModeList[CurrentMode].IHAW-PipHVawList[xEEPROMBuffer[PIPSIZE_buf]+(BYTE)PipAspectFlag*3].PipHwidth)/2+H_start);//main Hstart!
				WordWriteScaler(0x84,ModeList[CurrentMode].IVAW-PipHVawList[xEEPROMBuffer[PIPSIZE_buf]+(BYTE)PipAspectFlag*3].PipVwidth+V_start-HVmargin);//main Vstart!
				break;					

				
			case 0x20://right-top	//-----------------------------
				WordWriteScaler(0x80,ModeList[CurrentMode].IHAW-PipHVawList[xEEPROMBuffer[PIPSIZE_buf]+(BYTE)PipAspectFlag*3].PipHwidth+H_start-HVmargin-1);//main Hstart!
				WordWriteScaler(0x84,V_start+HVmargin);//main Vstart!
				break;

			case 0x21://right-middle
				WordWriteScaler(0x80,ModeList[CurrentMode].IHAW-PipHVawList[xEEPROMBuffer[PIPSIZE_buf]+(BYTE)PipAspectFlag*3].PipHwidth+H_start-HVmargin-1);//main Hstart!
				WordWriteScaler(0x84,(ModeList[CurrentMode].IVAW-PipHVawList[xEEPROMBuffer[PIPSIZE_buf]+(BYTE)PipAspectFlag*3].PipVwidth)/2+V_start);//main Vstart!
				break;
				
			case 0x22://right-bottom
				WordWriteScaler(0x80,ModeList[CurrentMode].IHAW-PipHVawList[xEEPROMBuffer[PIPSIZE_buf]+(BYTE)PipAspectFlag*3].PipHwidth+H_start-HVmargin-1);//main Hstart!
				WordWriteScaler(0x84,ModeList[CurrentMode].IVAW-PipHVawList[xEEPROMBuffer[PIPSIZE_buf]+(BYTE)PipAspectFlag*3].PipVwidth+V_start-HVmargin);//main Vstart!
				break;

			default://center
				WordWriteScaler(0x80,(ModeList[CurrentMode].IHAW-PipHVawList[xEEPROMBuffer[PIPSIZE_buf]+(BYTE)PipAspectFlag*3].PipHwidth)/2+H_start);//main Hstart!
				WordWriteScaler(0x84,(ModeList[CurrentMode].IVAW-PipHVawList[xEEPROMBuffer[PIPSIZE_buf]+(BYTE)PipAspectFlag*3].PipVwidth)/2+V_start);//main Vstart!
				break;
			}
	#else		// 위를 간단하게 코딩.	
		switch(PipHPositionNum)	//고정 위치 (상,중,하/좌,중,우)
		{
			case 0:
				WordWriteScaler(0x80,H_start+HVmargin);//main Hstart!
				break;
				
			case 1:
			default:
				WordWriteScaler(0x80,(PanelHerizontalsize-PipHVawList[xEEPROMBuffer[PIPSIZE_buf]+(BYTE)PipAspectFlag*3].PipHwidth)/2+H_start);//main Hstart!
				break;
				
			case 2:
				WordWriteScaler(0x80,PanelHerizontalsize-PipHVawList[xEEPROMBuffer[PIPSIZE_buf]+(BYTE)PipAspectFlag*3].PipHwidth+H_start-HVmargin-1);//main Hstart!
				break;
		}
		
		switch(PipVPositionNum)	//고정 위치 (상,중,하/좌,중,우)
		{
			case 0:
				WordWriteScaler(0x84,V_start+HVmargin);//main Vstart!
				break;
				
			case 1:
			default:
				WordWriteScaler(0x84,(PanelVerticalsize-PipHVawList[xEEPROMBuffer[PIPSIZE_buf]+(BYTE)PipAspectFlag*3].PipVwidth)/2+V_start);//main Vstart!
				break;
				
			case 2:
				WordWriteScaler(0x84,PanelVerticalsize-PipHVawList[xEEPROMBuffer[PIPSIZE_buf]+(BYTE)PipAspectFlag*3].PipVwidth+V_start-HVmargin);//main Vstart!
				break;
		}
	#endif

		// FeildToggleLine - pip tearing 방지
		switch(PipVPositionNum)	//고정 위치 (상,중,하/좌,중,우)
		{
			case 0:
				WordWriteScaler(0xd9,0x0100); //FeildToggleLine[10:0]	//2004-01-20 //pip tearing 방지
				break;
				
			case 1:
			default:
				WordWriteScaler(0xd9,0x0070); //FeildToggleLine[10:0]
				break;
				
			case 2:
				WordWriteScaler(0xd9,0x0070); //FeildToggleLine[10:0]
				break;
		}
	
	//background position	//2003-08-20
	#ifdef	PipDpmsON	//2003-10-21
		WordWriteScaler(0xb8,0);//main Hstart!
		WordWriteScaler(0xbc,1);//main Vstart!
	
	#else
	switch(PipHPositionNum)	//고정 위치 (상,중,하/좌,중,우)
	{
		case 0:
			WordWriteScaler(0xb8,H_start+HVmargin+10-pipBPOSoffset);//main Hstart!
			break;
			
		case 1:
		default:
			WordWriteScaler(0xb8,(PanelHerizontalsize-PipHVawList[xEEPROMBuffer[PIPSIZE_buf]+(BYTE)PipAspectFlag*3].PipHwidth)/2+H_start+10-pipBPOSoffset);//main Hstart!
			break;
			
		case 2:
			WordWriteScaler(0xb8,PanelHerizontalsize-PipHVawList[xEEPROMBuffer[PIPSIZE_buf]+(BYTE)PipAspectFlag*3].PipHwidth+H_start-HVmargin-1+10-pipBPOSoffset);//main Hstart!
			break;
	}
	switch(PipVPositionNum)	//고정 위치 (상,중,하/좌,중,우)
	{
		case 0:
			WordWriteScaler(0xbc,V_start+HVmargin-pipBPOSoffset);//main Vstart!
			break;
			
		case 1:
		default:
			WordWriteScaler(0xbc,(PanelVerticalsize-PipHVawList[xEEPROMBuffer[PIPSIZE_buf]+(BYTE)PipAspectFlag*3].PipVwidth)/2+V_start-pipBPOSoffset);//main Vstart!
			break;
			
		case 2:
			WordWriteScaler(0xbc,PanelVerticalsize-PipHVawList[xEEPROMBuffer[PIPSIZE_buf]+(BYTE)PipAspectFlag*3].PipVwidth+V_start-HVmargin-pipBPOSoffset);//main Vstart!
			break;
	}
	#endif
			
}
		
void	PipPositionService(void)
{
	switch(xEEPROMBuffer[MainSubInputSource])
	{
		case 20://RGB+COMPOSITE(PIP)
		case 28://RGB+SVIDEO(PIP)
		case 52://RGB+TUNER(PIP)
		case 36://DVI+COMPOSITE
		case 44://DVI+SIVIDEO
		case 60://DVI+TUNER
	    		//고정 위치 (상,중,하/좌,중,우)

//test2003-10-16	if(MenuNum==menu_pip_size||MenuNum==menu_pip_AspectRatio) WriteScaler(0x9a,0x00);//PIP OFF

			PipHVPosition();
			
//test2003-10-16	if(MenuNum==menu_pip_size||MenuNum==menu_pip_AspectRatio||MenuNum==menu_pip_source) idelay5m(80);//2003-08-01
	}		
}	

#ifndef savememory
void SetUpListFunction(void)//동일하게 사용되는 부분이 있으므로 함수를 만들었음.
{
	BYTE idata temp0,temp1;
	
	OSD230SeqSend(DSP_ROW2,CII_COL14,_RTriAngle,1);
	switch(xEEPROMBuffer[OSDHPOSITION_buf])
	{
		case 0://center
			temp0=_2iCenterPositionL;
			temp1=_2iCenterPositionR;
			break;
		case 1://right-top
			temp0=_2iRightTopPositionL;
			temp1=_2iRightTopPositionR;
			break;
		case 2://right-bottom
			temp0=_2iRightTopPositionL;
			temp1=_2iRightBottomPositionR;
			break;
		case 3://left-bottom
			temp0=_2iLeftBottomPositionL;
			temp1=_2iLeftBottomPositionR;
			break;		
		case 4://left-top
			temp0=_2iLeftTopPositionL;
			temp1=_2iLeftTopPositionR;
			break;
	}
	OSD230DataSend(0x00);
	OSD230DataSend(temp0);
	OSD230DataSend(temp1);
	
	//---------------------------------------------------
	OSD230SeqSend(DSP_ROW3,CII_COL14,_RTriAngle,1);
	OSD230DataSend(0x00);
	OSD230DatPtrSend(Language[xEEPROMBuffer[LANGUAGE_buf]],Language_Sizeof[xEEPROMBuffer[LANGUAGE_buf]]);
	OSD230DataSend(0x00);
	OSD230DataSend(0x00);	
	
	//---------------------------------------------------
	OSD230SeqSend(DSP_ROW4,CII_COL14,_RTriAngle,1);
	OSD230DataSend(0x00);
	temp0 = calToChar(xEEPROMBuffer[OSDOFFTIME_buf]);
	HighOSDArea=0;//Low Display data.
	temp1 = 0;
	while(temp0--)
	{
		OSD230DataSend(CalBuffer[temp1]+0x01);
		temp1++;
	}
	temp1 = calToChar(xEEPROMBuffer[OSDOFFTIME_buf]);
	OSD230DatPtrSend(Sec[xEEPROMBuffer[LANGUAGE_buf]],Sec_Sizeof[xEEPROMBuffer[LANGUAGE_buf]]);
	//---------------------------------------------------
	
	//---------------------------------------------------
	OSD230SeqSend(DSP_ROW5,CII_COL14,_RTriAngle,1);
	OSD230DataSend(0x00);
	
	//메뉴처음진입시 현재펑션값을 CurrentFunction에 넣어둔다.
	ArrangeFunctionTable();
	//------------------------------------------//2003-08-08
	xOSD_WIN_REG[0x0E] = 0x1f;	//hieght
	xOSDRA=DSP_ROW2;
	xOSDCA=CII_COL30;
	xOSDDT0=HVchar_dbl;
	//------------------------------------------
	switch(CurrentFunction)
	{
		case Rgb_mode://RGB
			OSD230DatPtrSend(Analog[0],Analog_Sizeof[0]);
			break;
		#ifdef	DVI_USE
		case Dvi_mode://DVI
			OSD230DatPtrSend(Digital[xEEPROMBuffer[LANGUAGE_buf]],Digital_Sizeof[xEEPROMBuffer[LANGUAGE_buf]]);
			break;
		#endif
		case Composite_mode://COMPOSITE
			OSD230DatPtrSend(Composite[0],Composite_Sizeof[0]);
			break;
		case Svideo_mode://S_VIDEO
			OSD230DatPtrSend(Svideo[0],Svideo_Sizeof[0]);
			break;
		case Tuner_mode://TUNER
			OSD230DatPtrSend(Tuner[0],Tuner_Sizeof[0]);
			break;
		case PipRnC_mode://PIP R+C
			OSD230DatPtrSend(PipRpC[0],PipRpC_Sizeof[0]);
			break;
		case PipRnS_mode://PIP R+S
			OSD230DatPtrSend(PipRpS[0],PipRpS_Sizeof[0]);
			break;
		case PipRnT_mode://PIP R+T
			OSD230DatPtrSend(PipRpT[0],PipRpT_Sizeof[0]);
			break;
		
		#ifdef DVI_USE
		case PipDnC_mode://PIP D+C
			OSD230DatPtrSend(PipDpC[0],PipDpC_Sizeof[0]);
			break;
		case PipDnS_mode://PIP D+S
			OSD230DatPtrSend(PipDpS[0],PipDpS_Sizeof[0]);
			break;
		case PipDnT_mode://PIP D+T
			OSD230DatPtrSend(PipDpT[0],PipDpT_Sizeof[0]);
			break;
		#endif

#if defined(USE_SCART)	
		case Scart_mode://SCART
			OSD230DatPtrSend(Scart[0],PipDpSC_Sizeof[0]);
			break;
		case PipRnSC_mode://PIP R+SC
			OSD230DatPtrSend(PipDpSC[0],PipDpSC_Sizeof[0]);
			break;
		case PipDnSC_mode://PIP D+SC
			OSD230DatPtrSend(PipDpSC[0],PipDpSC_Sizeof[0]);
			break;
		#endif
			
	}
}
#endif


/*  for memory save 2003.6.5
void DisplayBarandPercentClear(void)//selkey를 토글하게 되면 바(Bar)다음엔 퍼센트는 지운다.
{
	switch(OSDcusorPosition)
	{
		case 6:
		case 15:
		case 30:
		case 33:
		case 54:
		case 67:
		case 70:
		case 84:
		case 87:
			OSD230SeqSend(DSP_ROW2,CII_COL23,0x00,7);//clear
			break;
					
		case 7:
		case 11:
		case 16:
		case 31:
		case 34:
		case 55:
		case 68:
		case 71:
		case 85:
		case 88:
		case 107:
			OSD230SeqSend(DSP_ROW3,CII_COL23,0x00,7);//clear
			break;
			
		case 12:
		case 17:
		case 35:
		case 72:
		case 89:
			OSD230SeqSend(DSP_ROW4,CII_COL23,0x00,7);//clear
			break;
			
		case 13:
		case 18:
			OSD230SeqSend(DSP_ROW5,CII_COL23,0x00,7);//clear
			break;
	}
}	
*/	
	

/*
Osd On/Off 함수:
	이함수내에서 Osd clear(램클리어),OSD off, Osd enable을 병행한다.
*/

void InitOsdRam(void)
{
	idata	BYTE temp=0;
	for(temp=0;temp<15;temp++)	xOSD_WIN_REG[temp]=0x00;
	for(temp=0;temp<15;temp++) 	OSD230SeqSend(temp,CII_COL0,0x00,30);
	for(temp=0;temp<15;temp++) 	OSD230SeqSend(temp+0x40,CII_COL0,0x00,30);
}

void ClearOsd(void)
{
	BYTE i,cnt;
	for(i=IN_DSP_ROW0; i<=IN_DSP_ROW14;i++)		//disp clear
	{
		OSDstart;
		WriteOsdAdr1bit(i);
		WriteOsdAdr1bit(IN_CII_COL0);
		cnt=30;
		while(cnt--) WriteOsdDat1bit(0x00);
		OSDstop;
	}

	for(i=IN_ATTR_ROW0; i<=IN_ATTR_ROW15;i++)	//all attr clear
	{
		OSDstart;
		WriteOsdAdr1bit(i);
		WriteOsdAdr1bit(IN_CII_COL0);
		cnt=30;
		while(cnt--) WriteOsdDat1bit(0x00);
		OSDstop;
	}
}

void IntOsdOn(void)
{
	OSDstart;
	WriteOsdAdr1bit(IN_ATTR_ROW15);
	WriteOsdAdr1bit(IN_CII_COL17);
	WriteOsdDat1bit(0x80);
	OSDstop;
}

void IntOsdOff(void)
{
	OSDstart;
	WriteOsdAdr1bit(IN_ATTR_ROW15);
	WriteOsdAdr1bit(IN_CII_COL17);
	WriteOsdDat1bit(0x00);
	OSDstop;	
}


void Osd_onoff(void)
{
	#ifdef MicomXFRbackup
	BYTE temp1=0;
	#endif
	
	//----------------------------------------------------------------------------------------------------
	#if	!defined(INT_EXTOSD)		// 외부 OSD only
	//----------------------------------------------------------------------------------------------------
	switch(OSDstatus)
	{
		case	TopMenuWindow:
				xOSDW_OPTION[1]=0x80; //ON
				
				#ifdef MicomXFRbackup
				temp1=&xOSDW_OPTION[1];
				xMicomBuffer[temp1]=0x80;
				#endif
			
				break;
		
		case	OsdRamClear: //Ramclear
				xOSDW_OPTION[1]=0x00|0x2;
				InitOsdRam();
				
				#ifdef MicomXFRbackup
				temp1=&xOSDW_OPTION[1];
				xMicomBuffer[temp1]=0x02|0x04;
				#endif
				
				break;
			
		case	OSDoff:
				xOSDW_OPTION[1]=0x00|0x02;
				InitOsdRam();
				
				#ifdef MicomXFRbackup
				temp1=&xOSDW_OPTION[1];
				xMicomBuffer[temp1]=0x02|0x04;
				#endif
				
				NowTopOsdOn = 0;
				//OsdMenuOnFlag=0;
				
				SubWindowMsgFlag=0;
				ChdotDisplayFlag=0;//
				
				RecallFlag=0;
				OsdGrade=0;			
				break;
		
		
		case	NowStatusDisplay:
				xOSDW_OPTION[1]=0x80|0x40;
				#ifdef MicomXFRbackup
				temp1=&xOSDW_OPTION[1];
				xMicomBuffer[temp1]=0x80;
				#endif
				
				break;
				
		default://ON
				xOSDW_OPTION[1]=0x80;
//				xOSDW_OPTION[1]=0x80|0x40;
				
				#ifdef MicomXFRbackup
				temp1=&xOSDW_OPTION[1];
				xMicomBuffer[temp1]=0x80;
				#endif
				
			
				break;
	}
	//----------------------------------------------------------------------------------------------------
	#else				// 내부 + 외부
	//----------------------------------------------------------------------------------------------------
	switch(OSDstatus)
	{
		case	TopMenuWindow:
			if( (xEEPROMBuffer[MainSubInputSource]!=10)&&(xEEPROMBuffer[MainSubInputSource]!=14)&&(xEEPROMBuffer[MainSubInputSource]!=18) )	//COMPOSITE,S-VIDEO,TUNER 이외의 입력 
			{	// PC mode
				#ifdef WXGA_Panel
				WriteScaler(0x51,BIN_TO_BYTE(1,1,0,0,0,0,0,1));
				#else
				WriteScaler(0x51,BIN_TO_BYTE(1,1,0,0,0,0,1,1));
				#endif

				if(TransparencyOnfFlag)
				{
					WriteScaler(0x73,0x20);//IntOsd_Blend (high nibble: 0x0x(100%) 1x(75%) 2x(50%) 3x(25%) )
				}
				else	WriteScaler(0x73,0x00);
			}
			else	//video mode
			{
				WriteScaler(0x51,BIN_TO_BYTE(1,1,0,0,0,0,0,1));
				#if defined(TempOsdMenu)||defined(SSwideOsdtype)
				WriteScaler(0x73,0x10);	//75%
				#else
				WriteScaler(0x73,0x20);	//50%
				#endif
				
				#ifdef	VideoDoubleOSD	
				xOSD_WIN_REG[0x0E] = 0x0f;	//character height,	tv에서 높이 더블(내부/외부 크기같게..안그러면 튀는게 보임)
				#else
				xOSD_WIN_REG[0x0E] = 0x00;
				#endif
				xOSDRA=DSP_ROW2; xOSDCA=CII_COL30; xOSDDT0=Vchar_dbl;	//tv에서 row2에 icon 높이가 더블(OSD단계별 보임 방지)
			}
			
		
			IntOsdOn();
			idelay5m(4);

			xOSDW_OPTION[1]=0x80;//ON
			#ifdef MicomXFRbackup
			temp1=&xOSDW_OPTION[1];
			xMicomBuffer[temp1]=0x80|0x40|0x20;
			#endif

			break;
		
		case	OSDoff:
			IntOsdOff();
			
			xOSDW_OPTION[1]=0x00|0x02;
			InitOsdRam();
			OsdGrade=0;
			//NowTopOsdOn = 0;
//			OsdMenuOnFlag=0;
			//SubWindowMsgFlag=0;//
			RecallFlag=0;
			#ifdef MicomXFRbackup
			temp1=&xOSDW_OPTION[1];
			xMicomBuffer[temp1]=0x02|0x04;
			#endif
			break;

		case	OsdRamClear://Ramclear
				IntOsdOff();
			
				xOSDW_OPTION[1]=0x00|0x2;
				InitOsdRam();
				
				#ifdef MicomXFRbackup
				temp1=&xOSDW_OPTION[1];
				xMicomBuffer[temp1]=0x02|0x04;
				#endif			
				
				ClearOsd(); 
			break;

		case	NowStatusDisplay:
				if( (xEEPROMBuffer[MainSubInputSource]!=10)&&(xEEPROMBuffer[MainSubInputSource]!=14)&&(xEEPROMBuffer[MainSubInputSource]!=18) )	//COMPOSITE,S-VIDEO,TUNER 이외의 입력 
				{
					WriteScaler(0x51,BIN_TO_BYTE(1,1,0,0,0,0,1,1));
					if(TransparencyOnfFlag)
					{
						WriteScaler(0x73,0x20);//IntOsd_Blend (high nibble: 0x0x(100%) 1x(75%) 2x(50%) 3x(25%) )
					}
					else	WriteScaler(0x73,0x00);	
				}
				else	//video mode
				{
					WriteScaler(0x51,BIN_TO_BYTE(1,1,0,0,0,0,0,1));
					WriteScaler(0x73,0x20);
				}
		
				IntOsdOn();
				idelay5m(4);

			
				xOSDW_OPTION[1]=0x80|0x40;
				#ifdef MicomXFRbackup
				temp1=&xOSDW_OPTION[1];
				xMicomBuffer[temp1]=0x80|0x40|0x20;
				#endif
			
			
				
				break;
			
		default://ON
			IntOsdOn();
			idelay5m(4);
			
//			xOSDW_OPTION[1]=0x80|0x40;
			xOSDW_OPTION[1]=0x80;
			#ifdef MicomXFRbackup
			temp1=&xOSDW_OPTION[1];
			xMicomBuffer[temp1]=0x80;
			#endif
			
			break;
	}
	#endif
	
}

void	OsdTimeout(void)
{
	idata	BYTE temp0=0, temp1=0;
	
	MenuMinVal=OSDOFFTIME_min;
	MenuMaxVal=OSDOFFTIME_max;
	MenuVal=xEEPROMBuffer[OSDOFFTIME_buf];
	OSD230SeqSend(DSP_ROW6,CII_COL12,_LTriAngle,1);
	OSD230SeqSend(DSP_ROW6,CII_COL25,_RTriAngle,1);
	OSD230ColSend(CII_COL15);
	OSD230DataSend(0x00);
	temp0 = calToChar(xEEPROMBuffer[OSDOFFTIME_buf]);
	HighOSDArea=0;//Low Display data.
	temp1 = 0;
	OSD230SeqSend(DSP_ROW6,CII_COL15,0x00,(3-temp0));
	OSD230ColSend(CII_COL15+(3-temp0));
	while(temp0--)
	{
		OSD230DataSend(CalBuffer[temp1]+0x01);
		temp1++;
	}
	temp1 = calToChar(xEEPROMBuffer[OSDOFFTIME_buf]);
	
	
	#ifdef USE_NTSCTuner
	OSD230PtrSend(DSP_ROW6,CII_COL18,Sec[0],Sec_Sizeof[0]);				
	#else
	if(xEEPROMBuffer[LANGUAGE_buf]!=English) HighOSDArea=1;
	else HighOSDArea=0;
	OSD230PtrSend(DSP_ROW6,CII_COL18,Sec[xEEPROMBuffer[LANGUAGE_buf]],Sec_Sizeof[xEEPROMBuffer[LANGUAGE_buf]]);				
	#endif
	
	HighOSDArea=0;
	//OSD230DatPtrSend(Sec[xEEPROMBuffer[LANGUAGE_buf]],Sec_Sizeof[xEEPROMBuffer[LANGUAGE_buf]]);
	//OSD230DataSend(0x00);//SECC방지
	
}

				

void	DisplayInformation(void)
{
	if( (xEEPROMBuffer[MainSubInputSource]!=10)&&(xEEPROMBuffer[MainSubInputSource]!=14)&&(xEEPROMBuffer[MainSubInputSource]!=18) )	//COMPOSITE,S-VIDEO,TUNER 이외의 입력 
	{
		if( (TopMenuStart<=MenuNum) && (MenuNum<=SoundMenuEnd) && NowTopOsdOn )
		{	
			//xOSD_WIN_REG[0x0E] = 0x01;	//(char Normal,channel display단은 크게 하고) 나머진 보통...
			OsdDataWindowClear();		//Menu data window clear
							
//			if(xEEPROMBuffer[LANGUAGE_buf]!=English) HighOSDArea=1;
//			else HighOSDArea=0;

			Display_AdjustInfo();
			Display_BottomCurrentInfo();
//			HighOSDArea = 0;
		}
	}
	else	//COMPOSITE,S-VIDEO,TUNER
	{
		if( (TvTopMenuStart<=TvMenuNum) && (TvMenuNum<=SoundMenuEnd) && NowTopOsdOn )
		{	
			//xOSD_WIN_REG[0x0E] = 0x01;	//(char Normal,channel display단은 크게 하고) 나머진 보통...
			OsdDataWindowClear();		//Menu data window clear

//			if(xEEPROMBuffer[LANGUAGE_buf]!=English) HighOSDArea=1;
//			else HighOSDArea=0;

			Display_AdjustInfo();
			Display_BottomCurrentInfo();
//			HighOSDArea = 0;
		}
	}	
}

void WriteCharactor(BYTE row,BYTE value1,BYTE value2)
{
	OSD230SeqSend(row+ATTR_ROW0-DSP_ROW0,CII_COL1,0x00,2);	//Attribute data
	OSD230SeqSend2(row,CII_COL1,value1,value2);//Display data
}

void	MenuCharacter(void)
{
	switch( GetTopMenu() )
	{
		case	MENU_DISPLAY:	//icon display
			WriteCharactor(DSP_ROW3,_2I_BRIGHTNESS);
			WriteCharactor(DSP_ROW4,_2I_CONTRAST);
			WriteCharactor(DSP_ROW5,_2I_SHARPNESS);
			WriteCharactor(DSP_ROW6,_2I_COLCK);
			WriteCharactor(DSP_ROW7,_2I_PHASE);
			WriteCharactor(DSP_ROW8,_2I_HPOSITION);
			WriteCharactor(DSP_ROW9,_2I_VPOSITION);
			break;
			
		case	MENU_RGB:
			WriteCharactor(DSP_ROW3,_W,_B);
			WriteCharactor(DSP_ROW4,_I_R,0);
			WriteCharactor(DSP_ROW5,_I_G,0);
			WriteCharactor(DSP_ROW6,_I_B,0);
			WriteCharactor(DSP_ROW7,_I_Ctemp,0);
			break;
	 	
	 	case	MENU_OSD:
			//Language
			OSD230SeqSend(ATTR_ROW3,CII_COL1,0x00,2); 		//Attribute data
			
			OSD230RowSend(DSP2_ROW3); OSD230ColSend(CII_COL1);
			OSD230Data2SendHigh(_2I_LANGUAGE);

			WriteCharactor(DSP_ROW4,_2I_HPOSITION2);	
			WriteCharactor(DSP_ROW5,_2I_VPOSITION2);
			WriteCharactor(DSP_ROW6,_2I_WATCH);
			WriteCharactor(DSP_ROW7,_2I_Transparency);
	 		break;

	 	case	MENU_PIP:
			WriteCharactor(DSP_ROW3,_2I_PIP);
			WriteCharactor(DSP_ROW4,_2I_SOURCE);
			WriteCharactor(DSP_ROW5,_2I_SIZE);
			WriteCharactor(DSP_ROW6,_2I_HPOSITION2);
			WriteCharactor(DSP_ROW7,_2I_VPOSITION2);
			WriteCharactor(DSP_ROW8,_2I_WIDE);
			WriteCharactor(DSP_ROW9,_2I_Transparency);
	 		break;
	 		
	 	case	MENU_TOOLS:
			if(xEEPROMBuffer[LANGUAGE_buf]==English) 
			{
				HighOSDArea=0;
				//auto
				OSD230SeqSend(ATTR_ROW3,CII_COL1,0x00,4); 		//Attribute data
				OSD230SeqSend2(DSP_ROW3,CII_COL1,_A,_U); 	//Display data
				OSD230SeqSend2(DSP_ROW3,CII_COL3,_T,_O); 	//Display data
			
				//factory default
				OSD230SeqSend(ATTR_ROW4,CII_COL1,0x00,4); 		//Attribute data
				OSD230SeqSend2(DSP_ROW4,CII_COL1,_I,_N); 	//Display data
				OSD230SeqSend2(DSP_ROW4,CII_COL3,_I,_T); 	//Display data
				
				//dos mode
				OSD230SeqSend(ATTR_ROW5,CII_COL1,0x00,8); 		//Attribute data
				//WriteMenu(Dosmode_Sizeof[xEEPROMBuffer[LANGUAGE_buf]], Dosmode[xEEPROMBuffer[LANGUAGE_buf]]);
				OSD230SeqSend2(DSP_ROW5,CII_COL1,_D,_O); 	//Display data
				OSD230SeqSend2(DSP_ROW5,CII_COL3,_S,0); 	//Display data
				OSD230SeqSend2(DSP_ROW5,CII_COL5,_M,_O); 	//Display data
				OSD230SeqSend2(DSP_ROW5,CII_COL7,_D,_E); 	//Display data
				#ifdef Wide4_3Aspect
				OSD230PtrSend(DSP_ROW6,CII_COL1,Aspect[0], Aspect_Sizeof[0]); 	//Display data
				#endif
			}
			else {					// +jwshin 040801 modified...
				HighOSDArea=1;
				//auto
				OSD230SeqSend(ATTR_ROW3,CII_COL1,0x00,4); 		//Attribute data
				OSD230SeqSend2(DSP_ROW3,CII_COL1,0x27,_BK); 	//Display data
				OSD230SeqSend2(DSP_ROW3,CII_COL3,0x28,_BK); 	//Display data
				
			
				//factory default
				OSD230SeqSend(ATTR_ROW4,CII_COL1,0x00,4); 		//Attribute data
				OSD230SeqSend2(DSP_ROW4,CII_COL1,0xb0,0x96); 	//Display data
				OSD230SeqSend2(DSP_ROW4,CII_COL3,0x49,0x4a); 	//Display data
				
				//dos mode
				OSD230SeqSend(ATTR_ROW5,CII_COL1,0x00,8); 		//Attribute data
				//WriteMenu(Dosmode_Sizeof[xEEPROMBuffer[LANGUAGE_buf]], Dosmode[xEEPROMBuffer[LANGUAGE_buf]]);
				OSD230SeqSend2(DSP_ROW5,CII_COL1,0x2c,0x2d); 	//Display data
				OSD230SeqSend2(DSP_ROW5,CII_COL3,0x2e,0x2f); 	//Display data
				#ifdef Wide4_3Aspect
				if(xEEPROMBuffer[LANGUAGE_buf]==English) HighOSDArea=0;
				else HighOSDArea=1;
				OSD230PtrSend(DSP_ROW6,CII_COL1,Aspect[LangBuf], Aspect_Sizeof[LangBuf]); 	//Display data
				#endif
			}
			HighOSDArea=0;
			break;
			

		case MENU_SOUND:		// smpark 20030714
			if(xEEPROMBuffer[LANGUAGE_buf]==English) 	// +jwshin 040801 Modified...
			{
				HighOSDArea=0;
				// TREBLE
				OSD230SeqSend(ATTR_ROW3,CII_COL1,0x00,6); 		//Attribute data
				OSD230SeqSend2(DSP_ROW3,CII_COL1,_T,_R); 	//Display data
				OSD230SeqSend2(DSP_ROW3,CII_COL3,_E,_B); 	//Display data
				OSD230SeqSend2(DSP_ROW3,CII_COL5,_L,_E); 	//Display data
				// BASS
				OSD230SeqSend(ATTR_ROW4,CII_COL1,0x00,4); 		//Attribute data
				OSD230SeqSend2(DSP_ROW4,CII_COL1,_B,_A); 	//Display data
				OSD230SeqSend2(DSP_ROW4,CII_COL3,_S,_S); 	//Display data
				// LOUDNESS
				OSD230SeqSend(ATTR_ROW5,CII_COL1,0x00,4); 	// attribute
				OSD230SeqSend2(DSP_ROW5,CII_COL1,_L,_O); 	// data
				OSD230SeqSend2(DSP_ROW5,CII_COL3,_U,_D); 	//Display data
				// SMART SOUND CONTROL
				OSD230SeqSend(ATTR_ROW6,CII_COL1,0x00,4); 		//Attribute data
				OSD230SeqSend2(DSP_ROW6,CII_COL1,_S,_S); 	//Display data
				OSD230SeqSend2(DSP_ROW6,CII_COL3,_C,0); 	//Display data
			}
			else {
				HighOSDArea=1;
				OSD230SeqSend(ATTR_ROW3,CII_COL1,0x00,6); 		//Attribute data
				OSD230SeqSend2(DSP_ROW3,CII_COL1,0xCA,0xCB); 	//Display data
				
				OSD230SeqSend(ATTR_ROW4,CII_COL1,0x00,4); 		//Attribute data
				OSD230SeqSend2(DSP_ROW4,CII_COL1,0xCC,0xCB); 	//Display data
				
				OSD230SeqSend(ATTR_ROW5,CII_COL1,0x00,4); 	// attribute
				OSD230SeqSend2(DSP_ROW5,CII_COL1,0xcb,0x35); 	// data
				
				OSD230SeqSend(ATTR_ROW6,CII_COL1,0x00,4); 		//Attribute data
				OSD230SeqSend2(DSP_ROW6,CII_COL1,0x36,0x37); 	//Display data
				OSD230SeqSend2(DSP_ROW6,CII_COL3,0xcb,0x38); 	//Display data
				OSD230SeqSend2(DSP_ROW6,CII_COL5,0x39,0x3A); 	//Display data
				
			}
			HighOSDArea=0;
			break;
			
		default:
			break;
		}
	}

void	TvMenuCharacter(void)
{
		switch(GetTvTopMenu())
		{
	 		case	TVMENU_PICTURE:

				WriteCharactor(DSP_ROW3,_2I_BRIGHTNESS);
				WriteCharactor(DSP_ROW4,_2I_CONTRAST);
				WriteCharactor(DSP_ROW5,_2I_SHARPNESS);
				//Color
//				OSD230SeqSend(ATTR_ROW6,CII_COL1,0x00,2); 		//Attribute data
//				OSD230SeqSend2(DSP_ROW6,CII_COL1,_2I_Color); 		//Display data
			
				OSD230SeqSend(ATTR_ROW3,CII_COL1,0x00,2); 		//Attribute data
				OSD230RowSend(DSP2_ROW6);
				OSD230ColSend(CII_COL1);
				OSD230Data2SendHigh(0x04,0x05);

				WriteCharactor(DSP_ROW7,_2I_Tint);
				//smart picture control
				OSD230SeqSend(ATTR_ROW8,CII_COL1,0x00,4); 		//Attribute data
				OSD230SeqSend2(DSP_ROW8,CII_COL1,_S,_P); 		//Display data
				OSD230SeqSend2(DSP_ROW8,CII_COL3,_C,0); 		//Display data
				
	 			break;
	 			
	 		case	TVMENU_SETUP:
				#ifndef Country2TVtype
				//country
				OSD230SeqSend(ATTR_ROW3,CII_COL1,0x00,7); 		//Attribute data
				OSD230SeqSend2(DSP_ROW3,CII_COL1,_C,_O); 		//Display data
				OSD230SeqSend2(DSP_ROW3,CII_COL3,_U,_N); 		//Display data
				OSD230SeqSend2(DSP_ROW3,CII_COL5,_T,_R); 		//Display data
				OSD230SeqSend2(DSP_ROW3,CII_COL7,_Y,0); 		//Display data
				#else
				if(xEEPROMBuffer[LANGUAGE_buf]!=English) {
					HighOSDArea=1;
					OSD230SeqSend(ATTR_ROW3,CII_COL1,0x00,7); 		//Attribute data
					OSD230SeqSend2(DSP_ROW3,CII_COL1,0x08,0x45); 		//Display data
					OSD230SeqSend2(DSP_ROW3,CII_COL3,0x48,0x2f); 		//Display data
				}
				else	{
					HighOSDArea=0;
					OSD230SeqSend(ATTR_ROW3,CII_COL1,0x00,7); 		//Attribute data
					OSD230SeqSend2(DSP_ROW3,CII_COL1,_T,_V); 		//Display data
					OSD230SeqSend2(DSP_ROW3,CII_COL3,_minus,_T); 		//Display data
					OSD230SeqSend2(DSP_ROW3,CII_COL5,_Y,_P); 		//Display data
					OSD230SeqSend2(DSP_ROW3,CII_COL7,_E,0); 		//Display data
				}
				#endif
				
				if(xEEPROMBuffer[LANGUAGE_buf]!=English) {
					HighOSDArea=1;
					OSD230SeqSend(ATTR_ROW4,CII_COL1,0x00,5); 		//Attribute data
					OSD230SeqSend2(DSP_ROW4,CII_COL1,0x49,0x4a); 		//Display data
				}
				else {
					HighOSDArea=0;
					//auto setup
					OSD230SeqSend(ATTR_ROW4,CII_COL1,0x00,5); 		//Attribute data
					OSD230SeqSend2(DSP_ROW4,CII_COL1,_S,_E); 		//Display data
					OSD230SeqSend2(DSP_ROW4,CII_COL3,_T,_U); 		//Display data
					OSD230SeqSend2(DSP_ROW4,CII_COL5,_P,0); 		//Display data
				}
				
				if(xEEPROMBuffer[LANGUAGE_buf]!=English) {
					HighOSDArea=1;
					OSD230SeqSend(ATTR_ROW5,CII_COL1,0x00,4); 		//Attribute data
					OSD230SeqSend2(DSP_ROW5,CII_COL1,0xd6,0xd7); 		//Display data
					OSD230SeqSend2(DSP_ROW5,CII_COL3,0xd8,_BK); 		//Display data
				}
				else {
					HighOSDArea=0;
					//channel edit
					OSD230SeqSend(ATTR_ROW5,CII_COL1,0x00,4); 		//Attribute data
					OSD230SeqSend2(DSP_ROW5,CII_COL1,_E,_D); 		//Display data
					OSD230SeqSend2(DSP_ROW5,CII_COL3,_I,_T); 		//Display data
				}
				
				#if defined (USE_NTSCtuner)
				//antena input
				OSD230SeqSend(ATTR_ROW6,CII_COL1,0x00,9); 		//Attribute data
				OSD230SeqSend2(DSP_ROW6,CII_COL1,_R,_E); 		//Display data
				OSD230SeqSend2(DSP_ROW6,CII_COL3,_C,_E); 		//Display data
				OSD230SeqSend2(DSP_ROW6,CII_COL5,_P,_T); 		//Display data
				OSD230SeqSend2(DSP_ROW6,CII_COL7,_I,_O); 		//Display data
				OSD230SeqSend2(DSP_ROW6,CII_COL9,_N,0); 		//Display data
				
				//fine turn
				OSD230SeqSend(ATTR_ROW7,CII_COL1,0x00,4); 		//Attribute data
				OSD230SeqSend2(DSP_ROW7,CII_COL1,_F,_I); 		//Display data
				OSD230SeqSend2(DSP_ROW7,CII_COL3,_N,_E); 		//Display data
				#else
				//fine turn
				if(xEEPROMBuffer[LANGUAGE_buf]!=English) {
					HighOSDArea=1;
					OSD230SeqSend(ATTR_ROW6,CII_COL1,0x00,4); 		//Attribute data
					OSD230SeqSend2(DSP_ROW6,CII_COL1,0x4c,0x4d); 		//Display data
				}
				else {
					HighOSDArea=0;
					OSD230SeqSend(ATTR_ROW6,CII_COL1,0x00,4); 		//Attribute data
					OSD230SeqSend2(DSP_ROW6,CII_COL1,_F,_I); 		//Display data
					OSD230SeqSend2(DSP_ROW6,CII_COL3,_N,_E); 		//Display data
				}
				#endif
				HighOSDArea=0;
				//---------------
				//LanguageFunc();
				/*
				OSD230SeqSend(DSP_ROW3,CII_COL12,_LTriAngle,1);
				OSD230SeqSend(DSP_ROW3,CII_COL25,_RTriAngle,1);
				OSD230SeqSend(ATTR_ROW3,CII_COL1,0x00,6); 		//Attribute data
				OSD230SeqSend2(DSP_ROW3,CII_COL12+4,_S,_E); 		//Display data
				OSD230SeqSend2(DSP_ROW3,CII_COL12+6,_L,_E); 		//Display data
				OSD230SeqSend2(DSP_ROW3,CII_COL12+8,_C,_T); 		//Display data
				*/
				#if defined	(USE_PALSECAMtuner)
				if(xEEPROMBuffer[LANGUAGE_buf]==China) {HighOSDArea=1;}
				else	{HighOSDArea=0;}
				#endif
				
				
				#ifdef PalCountry_ChinaOnly
					#if defined(Country2TVtype)
//					HighOSDArea=0;
//					if(xEEPROMBuffer[LANGUAGE_buf]!=English) HighOSDArea=1;
//					else HighOSDArea=0;
					OSD230PtrSend(DSP_ROW3,CII_COL12+(CII_COL25-CII_COL12-PalTVtype_Sizeof[xEEPROMBuffer[LANGUAGE_buf]])/2,PalTVtype[xEEPROMBuffer[LANGUAGE_buf]],PalTVtype_Sizeof[xEEPROMBuffer[LANGUAGE_buf]]);	//+jwshin 040801
					#else
					HighOSDArea=0;
					OSDAngleDraw(DSP_ROW3,CII_COL12,LangChina_Sizeof[xEEPROMBuffer[LANGUAGE_buf]]);	//coutry
					if(xEEPROMBuffer[LANGUAGE_buf]==China)	HighOSDArea=1;
					OSD230PtrSend(DSP_ROW3,CII_COL12+(CII_COL25-CII_COL12-CtyChina_Sizeof[xEEPROMBuffer[LANGUAGE_buf]])/2,CtyChina[xEEPROMBuffer[LANGUAGE_buf]],CtyChina_Sizeof[xEEPROMBuffer[LANGUAGE_buf]]); 	//Display data
					//OSD230PtrSend(DSP_ROW3,CII_COL12+(CII_COL25-CII_COL12-sizeof(CtyChina_Chi))/2,CtyChina_Chi,sizeof(CtyChina_Chi));	
					#endif
				#else
					OSD230PtrSend(DSP_ROW3,CII_COL12,Select[xEEPROMBuffer[LANGUAGE_buf]],Select_Sizeof[xEEPROMBuffer[LANGUAGE_buf]]); 	//Display data
				#endif
				HighOSDArea=0;
				
                #ifdef	Ccd_Vchip
				//CCD
				OSD230SeqSend(ATTR_ROW8,CII_COL1,0x00,3); 		//Attribute data
				OSD230SeqSend2(DSP_ROW8,CII_COL1,_C,_C); 		//Display data
				OSD230SeqSend2(DSP_ROW8,CII_COL3,_D,0); 		//Display data
				//if(xEEPROMBuffer[LANGUAGE_buf]==China) {HighOSDArea=1;}
				//else	{HighOSDArea=0;}
				OSD230PtrSend(DSP_ROW8,CII_COL12,Select[xEEPROMBuffer[LANGUAGE_buf]],Select_Sizeof[xEEPROMBuffer[LANGUAGE_buf]]); 	//Display data
				HighOSDArea=0;
				//V-chip
				/*
				OSD230SeqSend(ATTR_ROW9,CII_COL1,0x00,6); 		//Attribute data
				OSD230SeqSend2(DSP_ROW9,CII_COL1,_V,_minus); 		//Display data
				OSD230SeqSend2(DSP_ROW9,CII_COL3,_c,_h); 		//Display data
				OSD230SeqSend2(DSP_ROW9,CII_COL5,_i,_p); 		//Display data
				*/
				OSD230PtrSend(DSP_ROW9,CII_COL1,Vchip[0], Vchip_Sizeof[0]); 	//Display data
				//if(xEEPROMBuffer[LANGUAGE_buf]==China) {HighOSDArea=1;}
				//else	{HighOSDArea=0;}
				OSD230PtrSend(DSP_ROW9,CII_COL12,Select[xEEPROMBuffer[LANGUAGE_buf]],Select_Sizeof[xEEPROMBuffer[LANGUAGE_buf]]); 	//Display data
				HighOSDArea=0;
				#endif

	 			break;
                	
				
	 		case	TVMENU_TOOLS:
				// Language
				OSD230SeqSend(ATTR_ROW3,CII_COL1,0x00,2); 		//Attribute data
				HighOSDArea=1;
				OSD230SeqSend2(DSP2_ROW3,CII_COL1,_2I_LANGUAGE); 	//Display data
				OSD230RowSend(DSP2_ROW3);
				OSD230ColSend(CII_COL1);
				OSD230Data2SendHigh(_2I_LANGUAGE);
				HighOSDArea=0;

				// Blue screen
				if(xEEPROMBuffer[LANGUAGE_buf]!=English) {			//+jwshin 040801
					HighOSDArea=1;
					OSD230SeqSend(ATTR_ROW4,CII_COL1,0x00,4); 		//Attribute data
					OSD230SeqSend2(DSP_ROW4,CII_COL1,0xaa,0xa9); 		//Display data
					OSD230SeqSend2(DSP_ROW4,CII_COL3,_BK,_BK); 		//Display data
					HighOSDArea=0;
				}
				else {
					HighOSDArea=0;
					OSD230SeqSend(ATTR_ROW4,CII_COL1,0x00,4); 		//Attribute data
					OSD230SeqSend2(DSP_ROW4,CII_COL1,_B,_L); 		//Display data
					OSD230SeqSend2(DSP_ROW4,CII_COL3,_U,_E); 		//Display data
				}

				//screen mode
				OSD230SeqSend(ATTR_ROW5,CII_COL1,0x00,2); 		//Attribute data
				OSD230SeqSend2(DSP_ROW5,CII_COL1,_2I_WIDE); 		//Display data

				//sleep
				OSD230SeqSend(ATTR_ROW6,CII_COL1,0x00,2); 		//Attribute data
				OSD230SeqSend2(DSP_ROW6,CII_COL1,_2I_WATCH); 		//Display data
				
				#if 0
				//aspect
				OSD230SeqSend(ATTR_ROW8,CII_COL1,0x00,6); 		//Attribute data
				OSD230SeqSend2(DSP_ROW8,CII_COL1,_A,_S); 		//Display data
				OSD230SeqSend2(DSP_ROW8,CII_COL3,_P,_E); 		//Display data
				OSD230SeqSend2(DSP_ROW8,CII_COL5,_C,_T); 		//Display data
				#endif
	 			break;

			case  TVMENU_SOUND:		// smpark 20030715	+jwshin 040801
				if(xEEPROMBuffer[LANGUAGE_buf]==English) 	// +jwshin 040801 Modified...
				{
					HighOSDArea=0;
					// TREBLE
					OSD230SeqSend(ATTR_ROW3,CII_COL1,0x00,6); 		//Attribute data
					OSD230SeqSend2(DSP_ROW3,CII_COL1,_T,_R); 	//Display data
					OSD230SeqSend2(DSP_ROW3,CII_COL3,_E,_B); 	//Display data
					OSD230SeqSend2(DSP_ROW3,CII_COL5,_L,_E); 	//Display data
					// BASS
					OSD230SeqSend(ATTR_ROW4,CII_COL1,0x00,4); 		//Attribute data
					OSD230SeqSend2(DSP_ROW4,CII_COL1,_B,_A); 	//Display data
					OSD230SeqSend2(DSP_ROW4,CII_COL3,_S,_S); 	//Display data
					// LOUDNESS
					OSD230SeqSend(ATTR_ROW5,CII_COL1,0x00,4); 	// attribute
					OSD230SeqSend2(DSP_ROW5,CII_COL1,_L,_O); 	// data
					OSD230SeqSend2(DSP_ROW5,CII_COL3,_U,_D); 	//Display data
	
					// SMART SOUND CONTROL
					OSD230SeqSend(ATTR_ROW6,CII_COL1,0x00,4); 		//Attribute data
					OSD230SeqSend2(DSP_ROW6,CII_COL1,_S,_S); 	//Display data
					OSD230SeqSend2(DSP_ROW6,CII_COL3,_C,0); 	//Display data
				}
				else {
					HighOSDArea=1;
					OSD230SeqSend(ATTR_ROW3,CII_COL1,0x00,6); 		//Attribute data
					OSD230SeqSend2(DSP_ROW3,CII_COL1,0xCA,0xCB); 	//Display data
					
					OSD230SeqSend(ATTR_ROW4,CII_COL1,0x00,4); 		//Attribute data
					OSD230SeqSend2(DSP_ROW4,CII_COL1,0xCC,0xCB); 	//Display data
					
					OSD230SeqSend(ATTR_ROW5,CII_COL1,0x00,4); 	// attribute
					OSD230SeqSend2(DSP_ROW5,CII_COL1,0xcb,0x35); 	// data
					
					OSD230SeqSend(ATTR_ROW6,CII_COL1,0x00,4); 		//Attribute data
					OSD230SeqSend2(DSP_ROW6,CII_COL1,0x36,0x37); 	//Display data
					OSD230SeqSend2(DSP_ROW6,CII_COL3,0xcb,0x38); 	//Display data
					OSD230SeqSend2(DSP_ROW6,CII_COL5,0x39,0x3A); 	//Display data
					
				}
				HighOSDArea=0;

				#ifdef TempOsdMenu
				//OSD230SeqSend(ATTR_ROW7,CII_COL1,0x00,4); 		//Attribute data
				HighOSDArea=1;
				OSD230SeqSend2(DSP_ROW7,CII_COL1,_TEMPkor); 		//Display data
				HighOSDArea=0;
				OSD230SeqSend2(DSP_ROW7,CII_COL3,_2I_OSD); 		//Display data
				OSD230SeqSend2(DSP_ROW7,CII_COL5,_D,_E); 		//Display data
				OSD230SeqSend2(DSP_ROW7,CII_COL7,_M,_O); 		//Display data
				//---
				HighOSDArea=1;
				OSD230SeqSend2(DSP_ROW8,CII_COL1,_TEMPkor); 		//Display data
				HighOSDArea=0;
				OSD230SeqSend2(DSP_ROW8,CII_COL3,_2I_OSD); 		//Display data
				OSD230SeqSend2(DSP_ROW8,CII_COL5,_B,_L); 		//Display data
				OSD230SeqSend2(DSP_ROW8,CII_COL7,_E,_N); 		//Display data
				OSD230SeqSend2(DSP_ROW8,CII_COL9,_D,0); 		//Display data
				#endif
				

				break;
		default:      
			break;
	}       	

}




void BarandPersent2(BYTE tablevalue,BYTE value,BYTE color)
{
	DisplayPercent2(BarTable[tablevalue][0],BarTable[tablevalue][1],value,BarTable[tablevalue][2],CII_COL7,color);//percent
	Displaybar2(BarTable[tablevalue][0],BarTable[tablevalue][1],value,BarTable[tablevalue][2],CII_COL11);//bar
}

void	MenuBarValue(void)
{
	switch( GetTopMenu() )
	{
		case	MENU_DISPLAY:	//icon display
			BarandPersent2(0,xEEPROMBuffer[ANALOGBRT_buf],OSD_BLACK);
			BarandPersent2(1,xEEPROMBuffer[ANALOGCONT],OSD_BLACK);
			BarandPersent2(2,xEEPROMBuffer[Sharpness_buf],OSD_BLACK);
			BarandPersent2(3,PhaseValue,OSD_BLACK);
			BarandPersent2(4,ClockValue,OSD_BLACK);
			BarandPersent2(5,HorizontalValue,OSD_BLACK);
			BarandPersent2(6,VerticalValue,OSD_BLACK);
			break;
		
		case	MENU_RGB:
			BarandPersent2(7,xEEPROMBuffer[WhiteBlc_buf],OSD_BLACK);
			BarandPersent2(8,xEEPROMBuffer[ADCREDGAIN_buf]+ADCREDGAIN_offset,OSD_BLACK);
			BarandPersent2(9,xEEPROMBuffer[ADCGREENGAIN_buf]+ADCREDGAIN_offset,OSD_BLACK);
			BarandPersent2(10,xEEPROMBuffer[ADCBLUEGAIN_buf]+ADCREDGAIN_offset,OSD_BLACK);			
			ColorTempFunc();
			break;
	 	
	 	case	MENU_OSD:
			LanguageFunc();
			//DisplayPercent2(OSDHpos_min,OSDHpos_max,xEEPROMBuffer[OSDHPOSITION_buf],DSP_ROW4,CII_COL7,OSD_BLACK);
			//Displaybar2(OSDHpos_min,OSDHpos_max,xEEPROMBuffer[OSDHPOSITION_buf],DSP_ROW4,CII_COL11);
			//if((MenuVal%5==1)||(MenuVal==PhaseValue_min))
			{
				DisplayPercent2(OSDHpos_min,OSDHpos_max,xEEPROMBuffer[OSDHPOSITION_buf],DSP_ROW4,CII_COL7,OSD_BLACK);
				Displaybar2(OSDHpos_min,OSDHpos_max,xEEPROMBuffer[OSDHPOSITION_buf],DSP_ROW4,CII_COL11);				
				#ifdef WXGA_Panel
				OSDSeqSend(IN_ATTR_ROW15,IN_CII_COL15,(4+(xEEPROMBuffer[OSDHPOSITION_buf]/5)*3),1);//horizontal //내부
				#else
				OSDSeqSend(IN_ATTR_ROW15,IN_CII_COL15,(4+(xEEPROMBuffer[OSDHPOSITION_buf]/5)*3),1);//horizontal
				#endif
			}
			BarandPersent2(11,xEEPROMBuffer[OSDVPOSITION_buf],OSD_BLACK);
			
			//OSDSeqSend(IN_ATTR_ROW15,IN_CII_COL15,(xEEPROMBuffer[OSDHPOSITION_buf]-0x1b)&0x7f,1);//horizontal
			OSDSeqSend(IN_ATTR_ROW15,IN_CII_COL14,xEEPROMBuffer[OSDVPOSITION_buf]-1,1);//vertical
			
			OsdTimeout();
			OnoffDisplayFunc(DSP_ROW7,CII_COL12,(BYTE)TransparencyOnfFlag);
	 		break;

	 	case	MENU_PIP:

			//-------------------------------
			PipOnOffFlag=(xEEPROMBuffer[PIPEN_SOURCE_buf]&0x10)>>4;	
			PipOnoffFunc(DSP_ROW3,CII_COL12,(BYTE)PipOnOffFlag);
			
			PipSourceSelFunc();
			if(PipOnOffFlag)PipSourceSelService();//

			PipSizeSelFunc();
			PipSizeSelService();

			#if 1	// 상중하/좌중우 형식 표시
			PipHPosSelFunc();
			PipVPosSelFunc();

			#else	// 바형식 표시
			PipHPositionNum=(xEEPROMBuffer[PIPPOSITION]&0x30)>>4;
			#ifdef OsdMenuType1
			DisplayPercent2(PipHposition_min,PipHposition_max,PipHPositionNum,DSP_ROW6,CII_COL7,0);
			#else
			DisplayPercent(PipHposition_min,PipHposition_max,PipHPositionNum,DSP_ROW6,CII_COL7,0);
			#endif
			Displaybar2(PipHposition_min,PipHposition_max,PipHPositionNum,DSP_ROW6,CII_COL11);
			
			PipVPositionNum=xEEPROMBuffer[PIPPOSITION]&0x03;				
			#ifdef OsdMenuType1
			DisplayPercent2(PipVposition_min,PipVposition_max,PipVPositionNum,DSP_ROW7,CII_COL7,0);
			#else
			DisplayPercent2(PipVposition_min,PipVposition_max,PipVPositionNum,DSP_ROW7,CII_COL7);
			#endif
			Displaybar2(PipVposition_min,PipVposition_max,PipVPositionNum,DSP_ROW7,CII_COL11);
			#endif

			PipAspectSelFunc();	
			PipBlendSelFunc();	//2003-08-19
			
			//-------------------------------
	 		break;
	 		
	 	case	MENU_TOOLS:
			OnoffDisplayFunc(DSP_ROW3,CII_COL12,(BYTE)AutoFlag);
			OnoffDisplayFunc(DSP_ROW4,CII_COL12,(BYTE)FactoryDftFlag);  
			DosmodeDisplay(DSP_ROW5,CII_COL12,(BYTE)DosmodeFlag);
			#ifdef Wide4_3Aspect
			AspectRatioFunc(DSP_ROW6,CII_COL12,(BYTE)AspectFlag);
			#endif
			break;

		case MENU_SOUND:		// smpark 20030714
				BarandPersent2(12,xEEPROMBuffer[TREBLE],OSD_BLACK);			
				BarandPersent2(13,xEEPROMBuffer[BASS],OSD_BLACK);		
				
				#ifdef LoudBarType
				BarandPersent2(14,xEEPROMBuffer[LOUDNESS],OSD_BLACK);
				#else
				OnoffDisplayFunc(DSP_ROW5,CII_COL12, xEEPROMBuffer[LOUDNESS]);
				#endif
	 			SmartSoundCtrFunc();
 			//MTSFunc();		// smpark 20030716 			
			break;
			
		default:
			break;
	}
}




void	TvMenuBarValue(void)
{
	switch(GetTvTopMenu())
	{
		case	TVMENU_PICTURE:
			BarandPersent2(15,xEEPROMBuffer[COMPOSITEBRT_buf],OSD_BLACK);
			BarandPersent2(16,xEEPROMBuffer[COMPOSITECONT],OSD_BLACK);
			BarandPersent2(17,xEEPROMBuffer[AVSharpness],OSD_BLACK);
			BarandPersent2(18,xEEPROMBuffer[AVCOLOR],OSD_BLACK);
			Displaybar3(COMPOSITETINT_min,COMPOSITETINT_max,xEEPROMBuffer[AVTINT],DSP_ROW7,CII_COL11);
			DisplayPercent2(COMPOSITETINT_min,COMPOSITETINT_max,xEEPROMBuffer[AVTINT],DSP_ROW7,CII_COL7,OSD_BLACK);
			
			SmartPicCtrFunc();
			break;
			
		case	TVMENU_SETUP:
			#ifdef PalCountry_ChinaOnly
			//OSDAngleDraw(DSP_ROW3,CII_COL12,LangChina_Sizeof[xEEPROMBuffer[LANGUAGE_buf]]);	//coutry
			#endif
			StartCharDisplayFunc(DSP_ROW4,ATTR_ROW4);	//setup
			StartCharDisplayFunc(DSP_ROW5,ATTR_ROW5);	//edit
			
			#if	defined (USE_NTSCtuner)
			AntenaSelFunc();
			Displaybar3(TvFineTuneValue_min2,TvFineTuneValue_max2,xEEPROMBuffer[NTSC_AIRTVFine_buf],DSP_ROW7,CII_COL11);
			//DisplayPercent2(TvFineTuneValue_min2,TvFineTuneValue_max2,xEEPROMBuffer[NTSC_AIRTVFine_buf],DSP_ROW7,CII_COL7,OSD_BLACK);
			DisplayPercent(TvFineTuneValue_min2,TvFineTuneValue_max2,xEEPROMBuffer[NTSC_AIRTVFine_buf],DSP_ROW7,CII_COL7);
			#else
			Displaybar3(TvFineTuneValue_min2,TvFineTuneValue_max2,xEEPROMBuffer[NTSC_AIRTVFine_buf],DSP_ROW6,CII_COL11);
			//DisplayPercent2(TvFineTuneValue_min2,TvFineTuneValue_max2,xEEPROMBuffer[NTSC_AIRTVFine_buf],DSP_ROW6,CII_COL7,OSD_BLACK);
			DisplayPercent(TvFineTuneValue_min2,TvFineTuneValue_max2,xEEPROMBuffer[NTSC_AIRTVFine_buf],DSP_ROW6,CII_COL7);
			#endif
			
			
			break;
        	
		case	TVMENU_TOOLS:
			LanguageFunc();
			OnoffDisplayFunc(DSP_ROW4,CII_COL12, xEEPROMBuffer[BscrFlag_buf]);
			TvAspectRatioSelFunc();	// OSD
			TvAspectRatioService();	// FUNCTION
			
			SleepFunc();
			
			break;

		case  TVMENU_SOUND:		// smpark 20030715
			BarandPersent2(12,xEEPROMBuffer[TREBLE],OSD_BLACK);
			BarandPersent2(13,xEEPROMBuffer[BASS],OSD_BLACK);
			
			#ifdef LoudBarType
			BarandPersent2(14,xEEPROMBuffer[LOUDNESS],OSD_BLACK);
			#else
			OnoffDisplayFunc(DSP_ROW5,CII_COL12, xEEPROMBuffer[LOUDNESS]);
			#endif
			
			SmartSoundCtrFunc();
			//MTSFunc();		// smpark 20030716

			#ifdef TempOsdMenu
			TempOsdSelFunc();	//임시osd 함수...
			TempOsdBlendFunc();
			#endif

			break;
	}
}

void	PipChannelOSD(void)	//2004-06-22
{
		xBYTE	Hpos=0,Vpos=0;
		
		PipHPositionNum=(xEEPROMBuffer[PIPPOSITION]&0x30)>>4;
		PipVPositionNum=xEEPROMBuffer[PIPPOSITION]&0x03;
		PipSizeNum=xEEPROMBuffer[PIPSIZE_buf]&0x03;
		
			switch(PipHPositionNum)	//고정 위치 (좌,중,우)
			{
				case 0:
									if(PipSizeNum==SizeLarge)				Hpos=0x15;
									else if(PipSizeNum==SizeMiddle)	Hpos=0x0c;
									else	Hpos=0x05;
					break;
					
				case 1:
				default:
									if(PipSizeNum==SizeLarge)				Hpos=0x35;
									else if(PipSizeNum==SizeMiddle)	Hpos=0x30;
									else	Hpos=0x2d;
					break;
					
				case 2:
								Hpos=0x54;
					break;
			}
			
			switch(PipVPositionNum)	//고정 위치 (상,중,하)
			{
				case 0:
									Vpos=4;
					break;

				case 1:
				default:
								switch((BYTE)PipAspectFlag)
								{
									case aspect4_3:
												if(PipSizeNum==SizeLarge)				Vpos=0x34;
												else if(PipSizeNum==SizeMiddle)	Vpos=0x3e;
												else	Vpos=0x44;
									break;
									
        					case aspect16_9:
												if(PipSizeNum==SizeLarge)				Vpos=0x3f;
												else if(PipSizeNum==SizeMiddle)	Vpos=0x47;
												else	Vpos=0x4c;
									break;
								}
					break;
								
				case 2:
								switch((BYTE)PipAspectFlag)
								{
									case aspect4_3:
												if(PipSizeNum==SizeLarge)				Vpos=0x63;
												else if(PipSizeNum==SizeMiddle)	Vpos=0x77;
												else	Vpos=0x86;
									break;
									
        					case aspect16_9:
												if(PipSizeNum==SizeLarge)				Vpos=0x7a;
												else if(PipSizeNum==SizeMiddle)	Vpos=0x89;
												else	Vpos=0x94;
									break;
								}
					break;
			}
			
			ChannelOSD(Hpos,Vpos);
						
}

void	DisplayMenuWindow(void)
{
	//BYTE temp0=0, temp1=0;
	idata	BYTE count=0, index=0, temp=0;
	
	if( (!AutoFlag)&&(xEEPROMBuffer[MainSubInputSource]!=10)&&(xEEPROMBuffer[MainSubInputSource]!=14)&&(xEEPROMBuffer[MainSubInputSource]!=18) )	//COMPOSITE,S-VIDEO,TUNER 이외의 입력 
	{
		if( (TopMenuStart<=MenuNum) && (MenuNum<=ToolsMenuEnd) && NowTopOsdOn )
		{	
			//xOSD_WIN_REG[0x0E] = 0x01;	//(char Normal,channel display단은 크게 하고) 나머진 보통...
			
			if(OsdGrade==0)		OsdDataWindowClear();		//Menu data window clear
							
			HighOSDArea = 0;//Font High or Low?
			//Display_TopMenuIcon();
		//	Display_AdjustInfo();
		//	Display_BottomCurrentInfo();
		}
	}
	else	//COMPOSITE,S-VIDEO,TUNER
	{
		if( (TvTopMenuStart<=TvMenuNum) && (TvMenuNum<=TvToolsEnd) && NowTopOsdOn )
		{ 
			//xOSD_WIN_REG[0x0E] = 0x01;	//(char Normal,channel display단은 크게 하고) 나머진 보통...
			
			if(OsdGrade==0)		OsdDataWindowClear();		//Menu data window clear
							
			HighOSDArea = 0;//Font High or Low?
			//Display_TvTopMenuIcon();
		//	Display_AdjustInfo();
		//	Display_BottomCurrentInfo();
		}
	}  
			                                                                  
	if( (NowTopOsdOn)&&(!AutoFlag)&&(xEEPROMBuffer[MainSubInputSource]!=10)&&(xEEPROMBuffer[MainSubInputSource]!=14)&&(xEEPROMBuffer[MainSubInputSource]!=18) )
	{	// PC mode
		if(OsdGrade==0)	OsdAttrClear();
		
		MenuCharacter();	//2003-08-07	//메뉴상의 글자와 숫자/표시바를 각각 함수로 나누어 사용.
		MenuBarValue();		//2003-08-07
	}
	else if( (NowTopOsdOn)&&(!AutoFlag)&&((xEEPROMBuffer[MainSubInputSource]==10)||(xEEPROMBuffer[MainSubInputSource]==14)||(xEEPROMBuffer[MainSubInputSource]==18)) )
	{	// tv, video의 경우
		if(OsdGrade==0)	OsdAttrClear();
		
		TvMenuCharacter();
		TvMenuBarValue();
	 }	
	else
	{
		
		
		switch(OSDcharacters)	// TopOSD 이외의 osd  char. attr. ...
		{

		//****************************************************************//
		//Volume&Mute
		//****************************************************************//
		case	VolumeChars:
			//OSD230SeqSend(ATTR_ROW3,CII_COL3,0x00,30);
			//OSD230PtrSend(DSP_ROW3,CII_COL3,Volume[xEEPROMBuffer[LANGUAGE_buf]],Volume_Sizeof[xEEPROMBuffer[LANGUAGE_buf]]);
			break;
		
		case	MuteChars:
			OSD230SeqSend(ATTR_ROW1,CII_COL1,0x04,Mute_Sizeof[xEEPROMBuffer[LANGUAGE_buf]]);
			OSD230PtrSend(DSP_ROW1,CII_COL1,Mute[xEEPROMBuffer[LANGUAGE_buf]],Mute_Sizeof[xEEPROMBuffer[LANGUAGE_buf]]);
			break;	

		case	OSDHotkeyMsgChar:
			OSD230SeqSend(ATTR_ROW1,CII_COL0,OSD_BLUE,30);
			OSD230PtrSend(DSP_ROW1,CII_COL7,AutoAdjust[xEEPROMBuffer[LANGUAGE_buf]],AutoAdjust_Sizeof[xEEPROMBuffer[LANGUAGE_buf]]);
			OSD230SeqSend(ATTR_ROW3,CII_COL0,OSD_WHITE,30);
			OSD230PtrSend(DSP_ROW3,CII_COL1,OSDHotkeyMsg1,sizeof(OSDHotkeyMsg1));
			OSD230SeqSend(ATTR_ROW4,CII_COL0,OSD_WHITE,30);
			OSD230PtrSend(DSP_ROW4,CII_COL1,OSDHotkeyMsg2,sizeof(OSDHotkeyMsg2));
			break;

		case	AutoTuneChars:
			OSD230SeqSend(ATTR_ROW1,CII_COL0,OSD_BLUE,30);//temp
			OSD230PtrSend(DSP_ROW1,CII_COL7,AutoAdjust[xEEPROMBuffer[LANGUAGE_buf]],AutoAdjust_Sizeof[xEEPROMBuffer[LANGUAGE_buf]]);

			OSD230SeqSend(ATTR_ROW3,CII_COL0+(29-Processing_Sizeof[xEEPROMBuffer[LANGUAGE_buf]])/2,OSD_WHITE,Processing_Sizeof[xEEPROMBuffer[LANGUAGE_buf]]);
			OSD230PtrSend(DSP_ROW3,CII_COL0+(29-Processing_Sizeof[xEEPROMBuffer[LANGUAGE_buf]])/2,Processing[xEEPROMBuffer[LANGUAGE_buf]],Processing_Sizeof[xEEPROMBuffer[LANGUAGE_buf]]);
			
			//OSD230SeqSend(ATTR_ROW5,CII_COL0+((25-0+1)-AutoConfig_Sizeof[xEEPROMBuffer[LANGUAGE_buf]])/2,OSD_WHITE,AutoConfig_Sizeof[xEEPROMBuffer[LANGUAGE_buf]]);
			//OSD230PtrSend(DSP_ROW5,CII_COL0+((25-0+1)-AutoConfig_Sizeof[xEEPROMBuffer[LANGUAGE_buf]])/2,AutoConfig[xEEPROMBuffer[LANGUAGE_buf]],AutoConfig_Sizeof[xEEPROMBuffer[LANGUAGE_buf]]);
			break;
		#if 0	//---------------------------------
		case	SscChar:
			//OSD230SeqSend(ATTR_ROW2,CII_COL0,OSD_BLUE,Pc_Sizeof[0]);
			
			xOSD_WIN_REG[0x0E] = 0x1f;		//hieght
			xOSDRA=DSP_ROW1;xOSDCA=CII_COL30;	//Attr
			xOSDDT0=HVchar_dbl;			//가로,세로 2배 확대
			
			//OSD230PtrSend(DSP_ROW2,CII_COL0,Pc[0],Pc_Sizeof[0]);
			SubWindowMsgFlag=1;
		
			break;
		
		case	SpcChar:
			SubWindowMsgFlag=1;
			break;
			
		case	MtsChar:
			SubWindowMsgFlag=1;
			break;
			
		case	SleepChar:
			SubWindowMsgFlag=1;
			break;
		#endif	//----------------------------------
			
		//****************************************************************//
		//우측 상단 평션 표시문구, window내에 char를 중앙에 위치시키기위해 고렴함.
		//****************************************************************//
		case	PcChar:
		//case	PipRgbCompositeChars:
		//case	PipRgbSvideoChars:
		//case	PipRgbTunerChars:
		case	AnalogSubChars:	
			if(!(PipOnOffFlag&&!NowTopOsdOn))
			{
				//OSD230SeqSend(ATTR_ROW1,CII_COL0/*((10-0+1)-Pc_Sizeof[0])/2*/,OSD_BLUE,Pc_Sizeof[0]);
				
				xOSD_WIN_REG[0x0D]=80;//H
				xOSD_WIN_REG[0x0C]=0;//V				
				
				OSD230SeqSend(ATTR_ROW0,CII_COL0,0x00,30);
				OSD230SeqSend(DSP_ROW0,CII_COL0,0x00,30);
				//OsdAllAttrClear();//test
				//OsdDataClear();//test
				
				OSD230SeqSend(ATTR_ROW1,CII_COL0,OSD_BLUE,sizeof(Pc));
				OSD230SeqSend(DSP_ROW1,CII_COL3,0x00,10);
				
				xOSD_WIN_REG[0x0E] = 0x1f;	//hieght
				xOSDRA=DSP_ROW1;xOSDCA=CII_COL30;
				xOSDDT0=HVchar_dbl;			//가로,세로 2배 확대
				

				//OSD230PtrSend(DSP_ROW1,CII_COL0/*((10-0+1)-Pc_Sizeof[0])/2*/,Pc[0],Pc_Sizeof[0]);
				if(xEEPROMBuffer[LANGUAGE_buf]!=English) HighOSDArea=1;		//+jwshin 040801
				else HighOSDArea=0;	
				OSD230PtrSend(DSP_ROW1,CII_COL0,Pc[xEEPROMBuffer[LANGUAGE_buf]],Pc_Sizeof[xEEPROMBuffer[LANGUAGE_buf]]);
				HighOSDArea=0;				
				SubWindowMsgFlag=1;
			}
			break;
	
		case	PipRgbTunerChars:
			xOSDW_OPTION[1]=0x00;

			xOSDRA=DSP_ROW0;xOSDCA=CII_COL30;
			xOSDDT0=0x00;
		
			PipChannelOSD();				//ChannelOSD(10,0);

			
			xOSDW_OPTION[1]=0x80|0x40;
			SubWindowMsgFlag=1;
			break;

#if	0
		case	PipRgbCompositeChars:
		case	PipRgbSvideoChars:
			xOSDW_OPTION[1]=0x00;

			xOSDRA=DSP_ROW0;xOSDCA=CII_COL30;
			xOSDDT0=0x00;
		
			//PipChannelOSD();				//ChannelOSD(10,0);
			if(OSDcharacters==PipRgbCompositeChars)	OSD230SeqSend(ATTR_ROW0,CII_COL0,OSD_BLUE,sizeof(Av1));
			else	OSD230PtrSend(DSP_ROW0,CII_COL0,Av1,sizeof(Av1));
			
			
			xOSDW_OPTION[1]=0x80|0x40;
			SubWindowMsgFlag=1;
			break;
#endif
			
		case	TvChar:
		case	TunerSubChars:

			//OSD230SeqSend(ATTR_ROW1,CII_COL0/*((10-0+1)-Tv_Sizeof[0])/2*/,OSD_BLUE,Tv_Sizeof[0]);
			OSD230SeqSend(ATTR_ROW1,CII_COL0,OSD_BLUE,sizeof(Tv));
			
			
			xOSD_WIN_REG[0x0E] = 0x1f;	//hieght
			xOSDRA=DSP_ROW1;
			xOSDCA=CII_COL30;
			xOSDDT0=HVchar_dbl;


			//OSD230PtrSend(DSP_ROW1,CII_COL0/*((10-0+1)-Tv_Sizeof[0])/2*/,Tv[0],Tv_Sizeof[0]);
			OSD230PtrSend(DSP_ROW1,CII_COL0,Tv,sizeof(Tv));

			SubWindowMsgFlag=1;
			break;
			
		case	Av1Char:
		case	CompositeSubChars:
			
			#ifdef char_AVx
			//OSD230SeqSend(ATTR_ROW1,CII_COL0/*+((10-0+1)-Av1_Sizeof[0])/2*/,OSD_BLUE,Av1_Sizeof[0]);
			OSD230SeqSend(ATTR_ROW1,CII_COL0,OSD_BLUE,sizeof(Av1));
			#else
			OSD230SeqSend(ATTR_ROW1,CII_COL0,OSD_BLUE,Composite_Sizeof[0]);
			#endif
			
			xOSD_WIN_REG[0x0E] = 0x1f;	//hieght
			xOSDRA=DSP_ROW1;
			xOSDCA=CII_COL30;
			
			#ifdef char_AVx
			xOSDDT0=HVchar_dbl;
			//xOSDDT0=Vchar_dbl;
			#endif
			
			#ifdef char_AVx
			//OSD230PtrSend(DSP_ROW1,CII_COL0/*+((10-0+1)-Av1_Sizeof[0])/2*/,Av1[0],Av1_Sizeof[0]);
			OSD230PtrSend(DSP_ROW1,CII_COL0,Av1,sizeof(Av1));
			#else
			OSD230PtrSend(DSP_ROW1,CII_COL0,Composite[0],Composite_Sizeof[0]);
			#endif
			
			SubWindowMsgFlag=1;
			break;

		case	Av2Char:
		case	S_videoSubChars:
			
			#ifdef char_AVx
			//OSD230SeqSend(ATTR_ROW1,CII_COL0/*+((10-0+1)-Av1_Sizeof[0])/2*/,OSD_BLUE,Av1_Sizeof[0]);
			OSD230SeqSend(ATTR_ROW1,CII_COL0,OSD_BLUE,sizeof(Av2));
			#else
			OSD230SeqSend(ATTR_ROW1,CII_COL0,OSD_BLUE,Svideo_Sizeof[0]);
			#endif
			
			xOSD_WIN_REG[0x0E] = 0x1f;	//hieght
			xOSDRA=DSP_ROW1;
			xOSDCA=CII_COL30;
			
			#ifdef char_AVx
			xOSDDT0=HVchar_dbl;
			//xOSDDT0=Vchar_dbl;
			#endif
			
			#ifdef char_AVx
			//OSD230PtrSend(DSP_ROW1,CII_COL0/*+((10-0+1)-Av1_Sizeof[0])/2*/,Av1[0],Av1_Sizeof[0]);
			OSD230PtrSend(DSP_ROW1,CII_COL0,Av2,sizeof(Av2));
			#else
			OSD230PtrSend(DSP_ROW1,CII_COL0,Svideo[0],Svideo_Sizeof[0]);
			#endif
			SubWindowMsgFlag=1;
			break;			

									
/*		#if 0	//사용안함.	/////////////////////////////////////////////////////////////
		case	AnalogSubChars:
			//OSD230SeqSend(ATTR_ROW3,CII_COL0+((10-0+1)-Analog_Sizeof[xEEPROMBuffer[LANGUAGE_buf]])/2,0x00,Analog_Sizeof[xEEPROMBuffer[LANGUAGE_buf]]);
			//OSD230PtrSend(DSP_ROW3,CII_COL0+((10-0+1)-Analog_Sizeof[xEEPROMBuffer[LANGUAGE_buf]])/2,Analog[xEEPROMBuffer[LANGUAGE_buf]],Analog_Sizeof[xEEPROMBuffer[LANGUAGE_buf]]);
			OSD230SeqSend(ATTR_ROW2,CII_COL0+((10-0+1)-Pc_Sizeof[0])/2,0x01,Pc_Sizeof[0]);
			xOSD_WIN_REG[0x0E] = 0x1f;
			xOSDRA=DSP_ROW2;
			xOSDCA=CII_COL30;
			xOSDDT0=0x03;
			OSD230PtrSend(DSP_ROW2,CII_COL0+((10-0+1)-Pc_Sizeof[0])/2,Pc[0],Pc_Sizeof[0]);
			SubWindowMsgFlag=1;
			break;
		
		#ifdef	DVI_USE
		case	DigitalSubChars:
			OSD230SeqSend(ATTR_ROW3,CII_COL0+((10-0+1)-Digital_Sizeof[xEEPROMBuffer[LANGUAGE_buf]])/2,0x00,Digital_Sizeof[xEEPROMBuffer[LANGUAGE_buf]]);
			OSD230PtrSend(DSP_ROW3,CII_COL0+((10-0+1)-Digital_Sizeof[xEEPROMBuffer[LANGUAGE_buf]])/2,Digital[xEEPROMBuffer[LANGUAGE_buf]],Digital_Sizeof[xEEPROMBuffer[LANGUAGE_buf]]);
			SubWindowMsgFlag=1;
			break;
		#endif
		
		case	TunerSubChars:
			//OSD230SeqSend(ATTR_ROW3,CII_COL1,0x00,Tuner_Sizeof[xEEPROMBuffer[LANGUAGE_buf]]);
			//OSD230PtrSend(DSP_ROW3,CII_COL1,Tuner[0],Tuner_Sizeof[0]);
			//OSD230SeqSend(ATTR_ROW2,CII_COL0+((10-0+1)-Tv_Sizeof[0])/2,0x01,Tv_Sizeof[0]);
			OSD230SeqSend(ATTR_ROW2,CII_COL0+((10-0+1)-sizeof(Tv))/2,0x01,sizeof(Tv));
			xOSD_WIN_REG[0x0E] = 0x1f;
			xOSDRA=DSP_ROW2;
			xOSDCA=CII_COL30;
			xOSDDT0=0x03;
			//OSD230PtrSend(DSP_ROW2,CII_COL0+((10-0+1)-Tv_Sizeof[0])/2,Tv[0],Tv_Sizeof[0]);			
			OSD230PtrSend(DSP_ROW2,CII_COL0+((10-0+1)-sizeof(Tv))/2,Tv,sizeof(Tv));
			SubWindowMsgFlag=1;
			break;
		case	CompositeSubChars:
			//OSD230SeqSend(ATTR_ROW3,CII_COL0+((10-0+1)-Composite_Sizeof[xEEPROMBuffer[LANGUAGE_buf]])/2,0x00,Composite_Sizeof[xEEPROMBuffer[LANGUAGE_buf]]);
			//OSD230PtrSend(DSP_ROW3,CII_COL0+((10-0+1)-Composite_Sizeof[0])/2,Composite[0],Composite_Sizeof[0]);
			OSD230SeqSend(ATTR_ROW2,CII_COL0+((10-0+1)-Av1_Sizeof[0])/2,0x01,Av1_Sizeof[0]);
			xOSD_WIN_REG[0x0E] = 0x1f;	
			xOSDRA=DSP_ROW2;
			xOSDCA=CII_COL30;
			xOSDDT0=0x03;
			OSD230PtrSend(DSP_ROW2,CII_COL0+((10-0+1)-Av1_Sizeof[0])/2,Av1[0],Av1_Sizeof[0]);
			SubWindowMsgFlag=1;
			break;
		case	S_videoSubChars:
			//OSD230SeqSend(ATTR_ROW3,CII_COL0+((10-0+1)-Svideo_Sizeof[xEEPROMBuffer[LANGUAGE_buf]])/2,0x00,Svideo_Sizeof[xEEPROMBuffer[LANGUAGE_buf]]);
			//OSD230PtrSend(DSP_ROW3,CII_COL0+((10-0+1)-Svideo_Sizeof[0])/2,Svideo[0],Svideo_Sizeof[0]);
			OSD230SeqSend(ATTR_ROW2,CII_COL0+((10-0+1)-Av2_Sizeof[0])/2,0x01,Av2_Sizeof[0]);
			xOSD_WIN_REG[0x0E] = 0x1f;			
			xOSDRA=DSP_ROW2;
			xOSDCA=CII_COL30;
			xOSDDT0=0x03;
			OSD230PtrSend(DSP_ROW2,CII_COL0+((10-0+1)-Av2_Sizeof[0])/2,Av2[0],Av2_Sizeof[0]);			
			SubWindowMsgFlag=1;
			break;
		
		case	PipRgbCompositeChars:
			OSD230SeqSend(ATTR_ROW3,CII_COL0+((16-0+1)-RgbComposite_Sizeof[xEEPROMBuffer[LANGUAGE_buf]])/2,0x00,RgbComposite_Sizeof[xEEPROMBuffer[LANGUAGE_buf]]);
			OSD230PtrSend(DSP_ROW3,CII_COL0+((16-0+1)-RgbComposite_Sizeof[0])/2,RgbComposite[0],RgbComposite_Sizeof[0]);
			break;
		
		case	PipRgbSvideoChars:
			OSD230SeqSend(ATTR_ROW3,CII_COL0+((16-0+1)-RgbSvideo_Sizeof[0])/2,0x00,RgbSvideo_Sizeof[0]);
			OSD230PtrSend(DSP_ROW3,CII_COL0+((16-0+1)-RgbSvideo_Sizeof[0])/2,RgbSvideo[0],RgbSvideo_Sizeof[0]);
			break;
		
		case	PipRgbTunerChars:
			OSD230SeqSend(ATTR_ROW3,CII_COL0+((16-0+1)-RgbTuner_Sizeof[0])/2,0x00,RgbTuner_Sizeof[0]);
			OSD230PtrSend(DSP_ROW3,CII_COL0+((16-0+1)-RgbTuner_Sizeof[0])/2,RgbTuner[0],RgbTuner_Sizeof[0]);
			break;
		#endif	///////////////////////////////////////////////////////////////////////////////////
*/		
		#ifdef DVI_USE
		case	PipDviCompositeChars:
			OSD230SeqSend(ATTR_ROW1,CII_COL0+((16-0+1)-DviComposite_Sizeof[xEEPROMBuffer[LANGUAGE_buf]])/2,0x00,DviComposite_Sizeof[xEEPROMBuffer[LANGUAGE_buf]]);
			OSD230PtrSend(DSP_ROW1,CII_COL0+((16-0+1)-DviComposite_Sizeof[xEEPROMBuffer[LANGUAGE_buf]])/2,DviComposite[xEEPROMBuffer[LANGUAGE_buf]],DviComposite_Sizeof[xEEPROMBuffer[LANGUAGE_buf]]);
			break;
		
		case	PipDviSvideoChars:
			OSD230SeqSend(ATTR_ROW1,CII_COL0+((16-0+1)-DviSvideo_Sizeof[xEEPROMBuffer[LANGUAGE_buf]])/2,0x00,DviSvideo_Sizeof[xEEPROMBuffer[LANGUAGE_buf]]);
			OSD230PtrSend(DSP_ROW1,CII_COL0+((16-0+1)-DviSvideo_Sizeof[xEEPROMBuffer[LANGUAGE_buf]])/2,DviSvideo[xEEPROMBuffer[LANGUAGE_buf]],DviSvideo_Sizeof[xEEPROMBuffer[LANGUAGE_buf]]);
			break;
		
		case	PipDviTunerChars:
			OSD230SeqSend(ATTR_ROW1,CII_COL0+((16-0+1)-DviTuner_Sizeof[xEEPROMBuffer[LANGUAGE_buf]])/2,0x00,DviTuner_Sizeof[xEEPROMBuffer[LANGUAGE_buf]]);
			OSD230PtrSend(DSP_ROW1,CII_COL0+((16-0+1)-DviTuner_Sizeof[xEEPROMBuffer[LANGUAGE_buf]])/2,DviTuner[xEEPROMBuffer[LANGUAGE_buf]],DviTuner_Sizeof[xEEPROMBuffer[LANGUAGE_buf]]);
			break;			
		#endif
		
	//--------------------------------------------------------------------------------------------------------
	#if 1
		//TV로 들어가면 우측상단에 현재 채널번호 표시
		//TV상에서 메뉴키 혹은 리모콘에 의한 채널변경시 우측상단 채널번호 표시
		case	ChannelOnlyNumber:
		case	ChannelNumChars:
			xOSDW_OPTION[1]=0x00; 	// smpark 20030818			

			#ifndef	ChannelDisplayDouble
					if(CurrentFunction==Tuner_mode)
					{
							ChannelOSD(80,8);
					}
					else		PipChannelOSD();



				
			#else
				//if(CheckChCATV(xEEPROMBuffer[CurrentChannel])) ChannelOSD(66,1);
				//else	ChannelOSD(70,1);;	//air
				ChannelOSD(64,1);
			#endif

			xOSDW_OPTION[1]=0x80|0x40; 	// smpark 20030818
			SubWindowMsgFlag=1;
			break;
		#endif
	//--------------------------------------------------------------------------------------------------------		
		//****************************************************************//
		//Ananlog&Digital&Pip No-signal
		//****************************************************************//
		case	AnalogPowerSaverChars:
			OSD230SeqSend(ATTR_ROW3,CII_COL0+((25-0+1)-Analog_Sizeof[0])/2,0x00,Analog_Sizeof[0]);
			OSD230PtrSend(DSP_ROW3,CII_COL0+((25-0+1)-Analog_Sizeof[0])/2,Analog[0],Analog_Sizeof[0]);
			OSD230SeqSend(ATTR_ROW5,CII_COL0+((25-0+1)-PowerSaverMode_Sizeof[0])/2,0x00,PowerSaverMode_Sizeof[0]);
			OSD230PtrSend(DSP_ROW5,CII_COL0+((25-0+1)-PowerSaverMode_Sizeof[0])/2,PowerSaverMode[0],PowerSaverMode_Sizeof[0]);
			SubWindowMsgFlag=1;
			break;
		
		#ifdef	DVI_USE
		case	DigitalPowerSaverChars:
			OSD230SeqSend(ATTR_ROW3,CII_COL0+((25-0+1)-Digital_Sizeof[xEEPROMBuffer[LANGUAGE_buf]])/2,0x00,Digital_Sizeof[xEEPROMBuffer[LANGUAGE_buf]]);
			OSD230PtrSend(DSP_ROW3,CII_COL0+((25-0+1)-Digital_Sizeof[xEEPROMBuffer[LANGUAGE_buf]])/2,Digital[xEEPROMBuffer[LANGUAGE_buf]],Digital_Sizeof[xEEPROMBuffer[LANGUAGE_buf]]);
			OSD230SeqSend(ATTR_ROW5,CII_COL0+((25-0+1)-PowerSaverMode_Sizeof[xEEPROMBuffer[LANGUAGE_buf]])/2,0x00,PowerSaverMode_Sizeof[xEEPROMBuffer[LANGUAGE_buf]]);
			OSD230PtrSend(DSP_ROW5,CII_COL0+((25-0+1)-PowerSaverMode_Sizeof[xEEPROMBuffer[LANGUAGE_buf]])/2,PowerSaverMode[xEEPROMBuffer[LANGUAGE_buf]],PowerSaverMode_Sizeof[xEEPROMBuffer[LANGUAGE_buf]]);
			SubWindowMsgFlag=1;
			break;
		#endif
		case	OutOfFreqChars:
			OSD230SeqSend(ATTR_ROW3,CII_COL0+((25-0+1)-OutOfFreq_Sizeof[xEEPROMBuffer[LANGUAGE_buf]])/2,0x00,OutOfFreq_Sizeof[xEEPROMBuffer[LANGUAGE_buf]]);
			OSD230PtrSend(DSP_ROW3,CII_COL0+((25-0+1)-OutOfFreq_Sizeof[xEEPROMBuffer[LANGUAGE_buf]])/2,OutOfFreq[xEEPROMBuffer[LANGUAGE_buf]],OutOfFreq_Sizeof[xEEPROMBuffer[LANGUAGE_buf]]);
			
			OSD230SeqSend(ATTR_ROW5,CII_COL7,0x00,15);
			//****************************************************************//
			//Frequency display(Hfre)
			//****************************************************************//
			count = calToChar((BYTE)(NowHfreq/10));		
			
			OSD230RowSend(DSP_ROW5);
			OSD230ColSend(CII_COL7);
			temp = CII_COL7+count;
			
			index = 0;
			HighOSDArea=0;//Low Display data.
			while(count--)								 //Hfreq 상수.
			{
				OSD230DataSend(CalBuffer[index]+0x01);
				index++;
			}
			OSD230RowSend(DSP_ROW5);
			OSD230ColSend(temp);
			OSD230DataSend(_dot);						//dot
			
			temp=temp+1;
			count = calToChar((BYTE)(NowHfreq%10));
			OSD230RowSend(DSP_ROW5);
			OSD230ColSend(temp);
			temp = temp+count;
			index = 0;
			HighOSDArea=0;//Low Display data.
			while(count--)								 //Hfreq 소수.
			{
				OSD230DataSend(CalBuffer[index]+0x01);
				index++;
			}
			
			OSD230PtrSend(DSP_ROW5,temp,kHz[0],kHz_Sizeof[0]); //Khz
			
			temp = temp+kHz_Sizeof[xEEPROMBuffer[LANGUAGE_buf]];
			OSD230RowSend(DSP_ROW5);
			OSD230ColSend(temp);
			OSD230DataSend(_slash);						//slash
            
			temp=temp+1;
			count = calToChar((BYTE)(NowVfreq/10));		
			OSD230RowSend(DSP_ROW5);
			OSD230ColSend(temp);
			temp = temp+count;
			index = 0;
			HighOSDArea=0;//Low Display data.
			while(count--)								 //Vfreq 상수.
			{
				OSD230DataSend(CalBuffer[index]+0x01);
				index++;
			}
			OSD230PtrSend(DSP_ROW5,temp,Hz[0],Hz_Sizeof[0]); //Hz
			SubWindowMsgFlag=1;
			break;
		
		case	CheckSignalCableChars:
			//OsdAttrClear();
			//OsdDataClear();

			OSD230SeqSend(ATTR_ROW3,CII_COL0+((25-0+1)-Analog_Sizeof[0])/2,0x00,Analog_Sizeof[0]);
			OSD230PtrSend(DSP_ROW3,CII_COL0+((25-0+1)-Analog_Sizeof[0])/2,Analog[0],Analog_Sizeof[0]);
			//OSD230SeqSend(ATTR_ROW5,CII_COL0+((25-0+1)-CheckSignalCable_Sizeof[xEEPROMBuffer[LANGUAGE_buf]])/2,0x00,CheckSignalCable_Sizeof[xEEPROMBuffer[LANGUAGE_buf]]);
			OSD230SeqSend(ATTR_ROW5,CII_COL0,0x00,30);
			OSD230PtrSend(DSP_ROW5,CII_COL0+((25-0+1)-CheckSignalCable_Sizeof[xEEPROMBuffer[LANGUAGE_buf]])/2,CheckSignalCable[xEEPROMBuffer[LANGUAGE_buf]],CheckSignalCable_Sizeof[xEEPROMBuffer[LANGUAGE_buf]]);
			SubWindowMsgFlag=1;
			break;
	//--------------------------------------------------------------------------------------------------------		
	#if 0	
		//****************************************************************//
		//TUNER's CHANNEL sub characters
		//****************************************************************//
		case	TunerChanChars:
			
			OsdDataClear();//clear
			xOSD_WIN_REG[1]=WIN_COL0&WIN_DIS|WIN_INT&WIN_UNSHD;//window1 clear!!
			xOSD_WIN_REG[3]=WIN_SROW1|WIN_EROW7;//window2 enlarge!!
/*	//smpark 20030814			
			#if	defined(USE_NTSCtuner)
			//AIR/CATV
			OSD230SeqSend(ATTR_ROW1,CII_COL1,0x00,AirCatv_Sizeof[0]);
			OSD230PtrSend(DSP_ROW1,CII_COL1,AirCatv[0],AirCatv_Sizeof[0]);
			#elif defined(USE_PALSECAMtuner)
			//SYSTEM
			OSD230SeqSend(ATTR_ROW1,CII_COL1,0x00,System_Sizeof[0]);
			OSD230PtrSend(DSP_ROW1,CII_COL1,System[0],System_Sizeof[0]);
			#endif
*/			
			//AUTO CHANNEL
			OSD230SeqSend(ATTR_ROW3,CII_COL1,0x00,AutoChannel_Sizeof[xEEPROMBuffer[LANGUAGE_buf]]);
			OSD230PtrSend(DSP_ROW3,CII_COL1,AutoChannel[xEEPROMBuffer[LANGUAGE_buf]],AutoChannel_Sizeof[xEEPROMBuffer[LANGUAGE_buf]]);
			//MANUAL CHANNEL
			OSD230SeqSend(ATTR_ROW4,CII_COL1,0x00,ManualChannel_Sizeof[xEEPROMBuffer[LANGUAGE_buf]]);
			OSD230PtrSend(DSP_ROW4,CII_COL1,ManualChannel[xEEPROMBuffer[LANGUAGE_buf]],ManualChannel_Sizeof[xEEPROMBuffer[LANGUAGE_buf]]);
			//FINE
			OSD230SeqSend(ATTR_ROW5,CII_COL1,0x00,Fine_Sizeof[xEEPROMBuffer[LANGUAGE_buf]]);
			OSD230PtrSend(DSP_ROW5,CII_COL1,Fine[xEEPROMBuffer[LANGUAGE_buf]],Fine_Sizeof[xEEPROMBuffer[LANGUAGE_buf]]);
			//EXIT
			OSD230SeqSend(ATTR_ROW6,CII_COL1,0x00,ExitSub_Sizeof[xEEPROMBuffer[LANGUAGE_buf]]); //Attribute data
			OSD230PtrSend(DSP_ROW6,CII_COL1,ExitSub[xEEPROMBuffer[LANGUAGE_buf]],ExitSub_Sizeof[xEEPROMBuffer[LANGUAGE_buf]]); //Display data
			
			break;
			
		
		//****************************************************************//
		//TUNER,COMPOSITE,S-VIDEO's COLOR sub characters
		//****************************************************************//
		case	TunerColChars:
		case	CompositeColChars:
		case	S_videoColChars:
			OsdDataClear();//clear
			xOSD_WIN_REG[1]=WIN_COL0&WIN_DIS|WIN_INT&WIN_UNSHD;//window1 clear!!
			xOSD_WIN_REG[3]=WIN_SROW1|WIN_EROW7;//window2 enlarge!!

			//SHARPNESS
			OSD230SeqSend(ATTR_ROW2,CII_COL1,0x00,Sharpness_Sizeof[xEEPROMBuffer[LANGUAGE_buf]]); //Attribute data
			OSD230PtrSend(DSP_ROW2,CII_COL1,Sharpness[xEEPROMBuffer[LANGUAGE_buf]],Sharpness_Sizeof[xEEPROMBuffer[LANGUAGE_buf]]); //Display data
			//COLOR
			OSD230SeqSend(ATTR_ROW3,CII_COL1,0x00,ColorSub_Sizeof[xEEPROMBuffer[LANGUAGE_buf]]); //Attribute data
			OSD230PtrSend(DSP_ROW3,CII_COL1,ColorSub[xEEPROMBuffer[LANGUAGE_buf]],ColorSub_Sizeof[xEEPROMBuffer[LANGUAGE_buf]]); //Display data
			//TINT
			OSD230SeqSend(ATTR_ROW4,CII_COL1,0x00,Tint_Sizeof[xEEPROMBuffer[LANGUAGE_buf]]); //Attribute data
			OSD230PtrSend(DSP_ROW4,CII_COL1,Tint[xEEPROMBuffer[LANGUAGE_buf]],Tint_Sizeof[xEEPROMBuffer[LANGUAGE_buf]]); //Display data
			//EXIT
			OSD230SeqSend(ATTR_ROW5,CII_COL1,0x00,ExitSub_Sizeof[xEEPROMBuffer[LANGUAGE_buf]]); //Attribute data
			OSD230PtrSend(DSP_ROW5,CII_COL1,ExitSub[xEEPROMBuffer[LANGUAGE_buf]],ExitSub_Sizeof[xEEPROMBuffer[LANGUAGE_buf]]); //Display data
			break;
		
		
		//****************************************************************//
		//PIP's PIP sub characters
		//****************************************************************//
		case	PIPPipChars:
			OsdDataClear();//clear
			xOSD_WIN_REG[1]=WIN_COL0&WIN_DIS|WIN_INT&WIN_UNSHD;//window1 clear!!
			xOSD_WIN_REG[3]=WIN_SROW1|WIN_EROW7;//window2 enlarge!!

			//PIP ON/OFF
			OSD230SeqSend(ATTR_ROW2,CII_COL1,0x00,PipOnOff_Sizeof[xEEPROMBuffer[LANGUAGE_buf]]);
			//OSD230PtrSend(DSP_ROW2,CII_COL1,PipOnOff[xEEPROMBuffer[LANGUAGE_buf]],PipOnOff_Sizeof[xEEPROMBuffer[LANGUAGE_buf]]);
			OSD230PtrSend(DSP_ROW2,CII_COL1,PipOnOff[0],PipOnOff_Sizeof[0]);
			//PIP SOURCE
			OSD230SeqSend(ATTR_ROW3,CII_COL1,0x00,PipSource_Sizeof[xEEPROMBuffer[LANGUAGE_buf]]);
			OSD230PtrSend(DSP_ROW3,CII_COL1,PipSource[0],PipSource_Sizeof[0]);
			//PIP SIZE
			OSD230SeqSend(ATTR_ROW4,CII_COL1,0x00,PipSize_Sizeof[xEEPROMBuffer[LANGUAGE_buf]]);
			OSD230PtrSend(DSP_ROW4,CII_COL1,PipSize[0],PipSize_Sizeof[0]);
			//PIP CONTROL
			OSD230SeqSend(ATTR_ROW5,CII_COL1,0x00,PipControl_Sizeof[xEEPROMBuffer[LANGUAGE_buf]]);
			OSD230PtrSend(DSP_ROW5,CII_COL1,PipControl[0],PipControl_Sizeof[0]);
			//EXIT
			OSD230SeqSend(ATTR_ROW6,CII_COL1,0x00,ExitSub_Sizeof[xEEPROMBuffer[LANGUAGE_buf]]); //Attribute data
			OSD230PtrSend(DSP_ROW6,CII_COL1,ExitSub[xEEPROMBuffer[LANGUAGE_buf]],ExitSub_Sizeof[xEEPROMBuffer[LANGUAGE_buf]]); //Display data
			break;
		
		
		//****************************************************************//
		//PIP's PIP CONTROL sub characters
		//****************************************************************//
		case	PIPControl:
			OsdDataClear();//clear
			xOSD_WIN_REG[1]=WIN_COL0&WIN_DIS|WIN_INT&WIN_UNSHD;//window1 clear!!
			xOSD_WIN_REG[3]=WIN_SROW1|WIN_EROW7;//window2 enlarge!!

			//PIP SWAP
			//OSD230SeqSend(ATTR_ROW2,CII_COL1,0x00,PipSwap_Sizeof[xEEPROMBuffer[LANGUAGE_buf]]);
			//OSD230PtrSend(DSP_ROW2,CII_COL1,PipSwap[xEEPROMBuffer[LANGUAGE_buf]],PipSwap_Sizeof[xEEPROMBuffer[LANGUAGE_buf]]);
			//PIP POSITION
			OSD230SeqSend(ATTR_ROW2,CII_COL1,0x00,PipPosition_Sizeof[0]);
			OSD230PtrSend(DSP_ROW2,CII_COL1,PipPosition[0],PipPosition_Sizeof[0]);
			//PIP BLEND
			OSD230SeqSend(ATTR_ROW3,CII_COL1,0x00,PipBlend_Sizeof[0]);
			OSD230PtrSend(DSP_ROW3,CII_COL1,PipBlend[0],PipBlend_Sizeof[0]);
			//EXIT
			OSD230SeqSend(ATTR_ROW4,CII_COL1,0x00,ExitSub_Sizeof[xEEPROMBuffer[LANGUAGE_buf]]); //Attribute data
			OSD230PtrSend(DSP_ROW4,CII_COL1,ExitSub[xEEPROMBuffer[LANGUAGE_buf]],ExitSub_Sizeof[xEEPROMBuffer[LANGUAGE_buf]]); //Display data
			break;
	#endif		
	//--------------------------------------------------------------------------------------------------------
		//channel display
		case	AutoSearchChannelChars:
			//char display
			OSD230SeqSend(DSP_ROW4,CII_COL15,_RTriAngle,1);
			OSD230DataSend(0x00);
			MenuVal=xEEPROMBuffer[CurrentChannel];
			count = calToChar(xEEPROMBuffer[CurrentChannel]);			
			
			switch(xEEPROMBuffer[TVMODE])
			{
				#if defined(USE_NTSCtuner)
				case NTSC_AIR:
					OSD230DataSend(_A);
					break;
				case NTSC_CATV:
					OSD230DataSend(_C);
					break;
				
				#elif defined(USE_PALSECAMtuner)
				case PAL_I:
				case PAL_BG:
				case PAL_DK:
					OSD230DataSend(_P);
					break;
				
				case SEC_BG:
				case SEC_DK:
				case SEC_L:
					OSD230DataSend(_S);
					break;
				#endif
			}
			
			HighOSDArea=0;//Low Display data.
			index = 0;
			while(count--)
			{
				OSD230DataSend(CalBuffer[index]+0x01);
				index++;
			}
			if(index<2) OSD230DataSend(0x00);//A11EL(x), A11DEL(o)
			if(index<3)OSD230DataSend(0x00);
			break;
		
		
		//searching  press select to stop
		case	AutoChannelChars:
			OSD230SeqSend(DSP_ROW3,CII_COL15,_RTriAngle,1);//SEARCH
			OSD230DataSend(0x00);
			OSD230DatPtrSend(Searching[xEEPROMBuffer[LANGUAGE_buf]],Searching_Sizeof[xEEPROMBuffer[LANGUAGE_buf]]);
			OSD230SeqSend(DSP_ROW3,CII_COL15+Searching_Sizeof[xEEPROMBuffer[LANGUAGE_buf]]+2,0x00,CII_COL30-(CII_COL15+Searching_Sizeof[xEEPROMBuffer[LANGUAGE_buf]]+2));	//Clear
			
			OSD230PtrSend(DSP_ROW7,CII_COL1,Press[xEEPROMBuffer[LANGUAGE_buf]],Press_Sizeof[xEEPROMBuffer[LANGUAGE_buf]]);
			OSD230SeqSend(ATTR_ROW7,CII_COL1,0x01,Press_Sizeof[xEEPROMBuffer[LANGUAGE_buf]]);
			OSD230DataSend(0x00);
			break;
			
		}
		return;
	}
}
	
//#ifndef savememory
void ChEdit_WindowOn(void)
{
	xOSD_WIN_REG[1]=WIN_COL0|WIN_ENA|WIN_INT|WIN_SHD;	//window1 display( channel edit windows)
}
//#endif
void ChEdit_WindowOff(void)
{
	#if defined (USE_NTSCtuner)
		xOSD_WIN_REG[10]=WIN_COL0&WIN_DIS|WIN_INT&WIN_UNSHD;	//window4 display (for channel edit)
	#elif defined (USE_PALSECAMtuner)
		//xOSD_WIN_REG[1]=WIN_COL0&WIN_DIS|WIN_INT|WIN_SHD;	//window1 display( channel edit windows)
		OsdEditWindowDataClear();
	#endif
}
	

//#ifndef  savememory	
void ChEdit_CursorFunc(void)
{
	#if defined (USE_NTSCtuner)	
//		if(ChEdit_CursorNum==1)
//		{
//			OSD230SeqSend(ATTR_ROW6+(xEEPROMBuffer[CurrentChannel]%5),CII_COL0,OSD_RED,30);
//			OSD230SeqSend(ATTR_ROW6+(xEEPROMBuffer[CurrentChannel]%5),CII_COL20,0x10|OSD_BLACK,3);	//커서 위치: Add (Yes/No)
//		}
//		else if(ChEdit_CursorNum==0)
//		{
//			OSD230SeqSend(ATTR_ROW6+(xEEPROMBuffer[CurrentChannel]%5),CII_COL0,OSD_RED,30);
//		}
	
	#elif defined (USE_PALSECAMtuner)
	
	if((ChEdit_CursorNum!=0)&&(ChEdit_CursorNum!=6))		// edit window + char.(A~9)
	{
		ChEdit_WindowOn();
		
		OSD230SeqSend(ATTR_ROW13,CII_COL0,OSD_BLACK,30);				//Attribute data
		OSD230PtrSend(DSP_ROW13,CII_COL4,EditWindowChar1[0],EditWindowChar1_Sizeof[0]);	//Display data (A~T)

		OSD230SeqSend(ATTR_ROW14,CII_COL0,OSD_BLACK,30);				//Attribute data
		OSD230PtrSend(DSP_ROW14,CII_COL4,EditWindowChar2[0],EditWindowChar2_Sizeof[0]);	//Display data (U~9)
	}
	
	if( (0<ChEdit_CursorNum)&&(ChEdit_CursorNum<=5) )
	{
		OSD230SeqSend(ATTR_ROW6+(xEEPROMBuffer[CurrentChannel]%5),CII_COL0,OSD_RED,30);
		OSD230SeqSend(ATTR_ROW6+(xEEPROMBuffer[CurrentChannel]%5),CII_COL16+ChEdit_CursorNum,0x10|OSD_BLACK,1);	//커서 위치: name(5)
	}
	else if(ChEdit_CursorNum==6)
	{
		OSD230SeqSend(ATTR_ROW6+(xEEPROMBuffer[CurrentChannel]%5),CII_COL0,OSD_RED,30);
		OSD230SeqSend(ATTR_ROW6+(xEEPROMBuffer[CurrentChannel]%5),CII_COL23,0x10|OSD_BLACK,4);	//커서 위치: skip (Yes/No)
	}
	else if(ChEdit_CursorNum==0)
	{
		OSD230SeqSend(ATTR_ROW6+(xEEPROMBuffer[CurrentChannel]%5),CII_COL0,OSD_RED,30);
	}
	#endif
}
//#endif


//void ChEdit_CharWin(void)
//{
//	OSD230SeqSend(ATTR_ROW13,CII_COL4+ChEdit_CharNum,0x70|OSD_BLACK,1);	
//}

void calToCharChannel(WORD Recdata)
{
	unsigned char Retdata;
	
	if(Recdata>0)				Retdata = 1;
	if(Recdata>=10)				Retdata = 2;
	if(Recdata>=100)				Retdata = 3;
	
	switch(Retdata)
	{
		case	1:
			CalBuffer[0] = 0xff;
			CalBuffer[1] = 0;			
			CalBuffer[2] = Recdata;
			break;
		
		case	2:
			CalBuffer[0] = 0xff;
			CalBuffer[1] = (Recdata/10);
			CalBuffer[2] = (Recdata%10);
			break;
		
		case	3:
			CalBuffer[0] = (Recdata/100);
			CalBuffer[1] = (Recdata%100)/10;
			CalBuffer[2] = (Recdata%10);
			break;

	}
}

#ifdef USE_NTSCtuner
void ProgEditCh_display(void)
{
	idata	BYTE	i,temp=0;
	
	//-------------------------------------------------------
	//	한 화면에 5라인씩 표시.		//2003-06-26   //
	//-------------------------------------------------------
	PageNum = (xEEPROMBuffer[CurrentChannel]/5);
	temp = PageNum*5+CHANNEL_MIN;
	
	#ifdef OsdMenuType1				
	for(i=0;i<5;i++)
	{
		if(temp>CHANNEL_MAX) {			
			OSD230RowSend(DSP_ROW5+i);
			OSD230ColSend(CII_COL5);	
			OSD230DataSend(_space);
			OSD230DataSend(_space);	
			OSD230DataSend(_space);
			OSD230DataSend(_space);	
			OSD230DataSend(_space);
			
			OSD230ColSend(CII_COL20);
			OSD230DataSend(_space);
			OSD230DataSend(_space);
			OSD230DataSend(_space);
		}
		else 
		{
			OSD230SeqSend(ATTR_ROW5+i,CII_COL0,OSD_BLACK,30);		//Attribute data
			if(AntenaFlag==AtnAir)	OSD230SeqSend2(DSP_ROW5+i,CII_COL5,_C,_H); 		//Display data		
			else  			OSD230SeqSend2(DSP_ROW5+i,CII_COL0+5,_C,_A); 		//Display data								
	
			OSD230SeqSend(ATTR_ROW5+i,CII_COL7,OSD_BLACK,3);
			OSD230RowSend(DSP_ROW5+i);
			
			OSD230ColSend(CII_COL7);
				
			calToCharChannel(temp++);
			DisplayInfo(3);	// display
			OnoffDisplayFunc(DSP_ROW5+i,CII_COL20,(BYTE)CheckChMask(PageNum*5+i)); //메모리작업요망.
		}

	}
	#else
		for(i=0;i<5;i++)
	{
		if(temp>CHANNEL_MAX) {			
			OSD230RowSend(DSP_ROW6+i);
			OSD230ColSend(CII_COL5);	
			OSD230DataSend(_space);
			OSD230DataSend(_space);	
			OSD230DataSend(_space);
			OSD230DataSend(_space);	
			OSD230DataSend(_space);
			
			OSD230ColSend(CII_COL20);
			OSD230DataSend(_space);
			OSD230DataSend(_space);
			OSD230DataSend(_space);
		}
		else 
		{
			OSD230SeqSend(ATTR_ROW6+i,CII_COL0,OSD_BLACK,30);		//Attribute data
			if(AntenaFlag==AtnAir)	OSD230SeqSend2(DSP_ROW6+i,CII_COL5,_C,_H); 		//Display data		
			else  			OSD230SeqSend2(DSP_ROW6+i,CII_COL0+5,_C,_A); 		//Display data								
	
			OSD230SeqSend(ATTR_ROW6+i,CII_COL7,OSD_BLACK,3);
			OSD230RowSend(DSP_ROW6+i);
			
			OSD230ColSend(CII_COL7);
				
			calToCharChannel(temp++);
			DisplayInfo(3);	// display
			OnoffDisplayFunc(DSP_ROW6+i,CII_COL20,(BYTE)CheckChMask(PageNum*5+i)); //메모리작업요망.
		}

	}
	#endif
	//--------------------------------------------------
}	
#else 	//pal_tuner...
	#if !defined(PalCountry_ChinaOnly) //++++++++++++++++++++++++++++++++++++++++++
void ProgEditCh_display(void)
{
	idata	BYTE	count,i,j,temp=0;
	j=0;

	//-------------------------------------------------------
	//	한 화면에 5라인씩 표시.		//2003-06-26   //
	//-------------------------------------------------------
	PageNum = (xEEPROMBuffer[CurrentChannel]/5);

	//count = calToChar(xEEPROMBuffer[CurrentChannel]);
	count = calToChar(PageNum*5);

	//OSD230SeqSend(DSP_ROW5+i,CII_COL5,0x00,2);	//clear

	temp = PageNum*5;
	if(count==1)		// 1자리 숫자일때 
	{
		for(i=0;i<5;i++)
		{
			OSD230SeqSend(ATTR_ROW5+i,CII_COL5+j,OSD_BLACK,1);
			OSD230SeqSend(DSP_ROW5+i,CII_COL5+j,_0,1);	// '0'dispaly
			
			OSD230SeqSend(ATTR_ROW5+i,CII_COL6+j,OSD_BLACK,1);
			OSD230RowSend(DSP_ROW5+i);
			OSD230ColSend(CII_COL6+j);
			
			if(i==0)
			{
				DisplayInfo(count);	// display
			}
			else
			{
				count = calToChar(++temp);
				DisplayInfo(count);		// 2~5 line
			}
		}
		
		
	}
	else if(count==2)	//2자리 숫자일때
	{
		for(i=0;i<5;i++)
		{
			OSD230SeqSend(ATTR_ROW5+i,CII_COL5+j,OSD_BLACK,2);
			OSD230RowSend(DSP_ROW5+i);
			OSD230ColSend(CII_COL5+j);
			
			if(i==0)
			{
				DisplayInfo(count);
			}
			else
			{
				count = calToChar(++temp);
				DisplayInfo(count);
			}
		}
	}
	//--------------------------------------------------
}
	#else	//+++++++++++++++++++++++++++++++
void ProgEditCh_display(void)
{
	idata	BYTE	i,temp=0;
	
	//-------------------------------------------------------
	//	한 화면에 5라인씩 표시.		//2003-06-26   //
	//-------------------------------------------------------
	PageNum = (xEEPROMBuffer[CurrentChannel]/5);
	temp = PageNum*5+CHANNEL_MIN;

//	DBGputs("xEEPROMBuffer[CurrentChannel]=0x");DBGputss(xEEPROMBuffer[CurrentChannel]);	DBGputs("\n");
//	DBGputss(PageNum);	DBGputs("\n");
//	DBGputss(temp);	DBGputs("\n");

	#ifdef OsdMenuType1
	for(i=0;i<5;i++)
	{
		if(temp>CHANNEL_MAX) {			
			OSD230RowSend(DSP_ROW5+i);
			OSD230ColSend(CII_COL5);	
			OSD230DataSend(_space);
			OSD230DataSend(_space);	
			OSD230DataSend(_space);	
			OSD230DataSend(_space);	
			OSD230DataSend(_space);
			
			OSD230ColSend(CII_COL20);
			OSD230DataSend(_space);
			OSD230DataSend(_space);
			OSD230DataSend(_space);
		}
		else 
		{
			OSD230SeqSend(ATTR_ROW5+i,CII_COL0,OSD_BLACK,30);		//Attribute data
			if(AntenaFlag==AtnAir)	OSD230SeqSend2(DSP_ROW5+i,CII_COL5,_C,_H); 		//Display data		
			else  			OSD230SeqSend2(DSP_ROW5+i,CII_COL0+5,_C,_A); 		//Display data								
	
			OSD230SeqSend(ATTR_ROW5+i,CII_COL7,OSD_BLACK,3);
			OSD230RowSend(DSP_ROW5+i);
			
			OSD230ColSend(CII_COL7);
				
			calToCharChannel(temp++);
			DisplayInfo(3);	// display
			OnoffDisplayFunc(DSP_ROW5+i,CII_COL20,(BYTE)CheckChMask(PageNum*5+i)); //메모리작업요망.
		}

	}
	#else
		for(i=0;i<5;i++)
	{
		if(temp>CHANNEL_MAX) {			
			OSD230RowSend(DSP_ROW6+i);
			OSD230ColSend(CII_COL5);	
			OSD230DataSend(_space);
			OSD230DataSend(_space);	
			OSD230DataSend(_space);
			OSD230DataSend(_space);	
			OSD230DataSend(_space);
			
			OSD230ColSend(CII_COL20);
			OSD230DataSend(_space);
			OSD230DataSend(_space);
			OSD230DataSend(_space);
		}
		else 
		{
			OSD230SeqSend(ATTR_ROW6+i,CII_COL0,OSD_BLACK,30);		//Attribute data
			if(AntenaFlag==AtnAir)	OSD230SeqSend2(DSP_ROW6+i,CII_COL5,_C,_H); 		//Display data		
			else  			OSD230SeqSend2(DSP_ROW6+i,CII_COL0+5,_C,_A); 		//Display data								
	
			OSD230SeqSend(ATTR_ROW6+i,CII_COL7,OSD_BLACK,3);
			OSD230RowSend(DSP_ROW6+i);
			
			OSD230ColSend(CII_COL7);
				
			calToCharChannel(temp++);
			DisplayInfo(3);	// display
			OnoffDisplayFunc(DSP_ROW6+i,CII_COL20,(BYTE)CheckChMask(PageNum*5+i)); //메모리작업요망.
		}

	}
	#endif
	//--------------------------------------------------
}	
	#endif	//++++++++++++++++++++++++++++++++++++	
	
void	ChEdit_CharFunc(void)
{
#ifdef	OsdMenuType1
	if(KEY_value==RightKey)
	{
		OSD230PtrSend(DSP_ROW5+(xEEPROMBuffer[CurrentChannel]%5),CII_COL16+ChEdit_CursorNum-1,ChEditChar+ChEdit_CharNum,1);
	}
	else if(KEY_value==LeftKey)
	{
		OSD230PtrSend(DSP_ROW5+(xEEPROMBuffer[CurrentChannel]%5),CII_COL16+ChEdit_CursorNum+1,ChEditChar+ChEdit_CharNum,1);
	}
#else
	if(KEY_value==RightKey)
	{
		OSD230PtrSend(DSP_ROW6+(xEEPROMBuffer[CurrentChannel]%5),CII_COL16+ChEdit_CursorNum-1,ChEditChar+ChEdit_CharNum,1);
	}
	else if(KEY_value==LeftKey)
	{
		OSD230PtrSend(DSP_ROW6+(xEEPROMBuffer[CurrentChannel]%5),CII_COL16+ChEdit_CursorNum+1,ChEditChar+ChEdit_CharNum,1);
	}
#endif
}
#endif

	
void	SubWindowDisplay(void)
{
	idata	BYTE i=0;
	OsdGrade=2;
	

	switch( TvMenuNum )
	{
		case	tvmenu_country:
			
			#ifdef	USE_NTSCtuner

				//OSD230SeqSend(ATTR_ROW3,CII_COL0,OSD_BLACK,30);
				//OSD230PtrSend(DSP_ROW3,CII_COL7,Country[0],Country_Sizeof[0]);
				
				OSD230SeqSend(ATTR_ROW4,CII_COL0,OSD_BLACK,30);
				OSD230PtrSend(DSP_ROW4,CII_COL7,CountryUSA [0],CountryUSA_Sizeof[0]);

				OSD230SeqSend(ATTR_ROW5,CII_COL0,OSD_BLACK,30);
				OSD230PtrSend(DSP_ROW5,CII_COL7,LangKor[0],LangKor_Sizeof[0]);

				OSD230SeqSend(ATTR_ROW6,CII_COL0,OSD_BLACK,30);
				OSD230PtrSend(DSP_ROW6,CII_COL7,LangJap[0],LangJap_Sizeof[0]);
				
				Display_CountyrBottomInfo();	// 설명제거로 인해 내용의 명확성을 위해 추가함. 2003-11-17
				


			#elif defined USE_PALSECAMtuner
				OSD230SeqSend(ATTR_ROW4,CII_COL0,OSD_BLACK,30);
				//OSD230PtrSend(DSP_ROW4,CII_COL7,LangEng[0],LangEng_Sizeof[0]);
				OSD230PtrSend(DSP_ROW4,CII_COL7,CountryUSA [0],CountryUSA_Sizeof[0]);

/*				OSD230SeqSend(ATTR_ROW4,CII_COL0,OSD_BLACK,30);
				OSD230PtrSend(DSP_ROW4,CII_COL7,LangFrance[0],LangFrance_Sizeof[0]);

				OSD230SeqSend(ATTR_ROW5,CII_COL0,OSD_BLACK,30);
				OSD230PtrSend(DSP_ROW5,CII_COL7,LangGerman[0],LangGerman_Sizeof[0]);

				OSD230SeqSend(ATTR_ROW6,CII_COL0,OSD_BLACK,30);
				OSD230PtrSend(DSP_ROW6,CII_COL7,LangItalia[0],LangItalia_Sizeof[0]);
				
				OSD230SeqSend(ATTR_ROW7,CII_COL0,OSD_BLACK,30);
				OSD230PtrSend(DSP_ROW7,CII_COL7,LangNetherlands[0],LangNetherlands_Sizeof[0]);

				OSD230SeqSend(ATTR_ROW8,CII_COL0,OSD_BLACK,30);
				OSD230PtrSend(DSP_ROW8,CII_COL7,LangRussia[0],LangRussia_Sizeof[0]);
*/
				//HighOSDArea=1;
				OSD230SeqSend(ATTR_ROW5,CII_COL0,OSD_BLACK,30);
				//OSD230PtrSend(DSP_ROW5,CII_COL7,LangChina[0],LangChina_Sizeof[0]);
				OSD230PtrSend(DSP_ROW5,CII_COL7,CtyChina_Chi,sizeof(CtyChina_Chi));
				//HighOSDArea=0;

				
			#endif
			
				break;
				
		case	tvmenu_auto_setup:
				OSD230SeqSend(ATTR_ROW3,CII_COL1+10,0x00,8); 		//Attribute data
				OSD230SeqSend2(DSP_ROW3,CII_COL1+10,_C,_H); 		//Display data
				
				OSD230SeqSend(ATTR_ROW5,CII_COL1+8,0x00,12); 		//Attribute data
				OSD230SeqSend2(DSP_ROW5,CII_COL1+8,_P,_L); 		//Display data
				OSD230SeqSend2(DSP_ROW5,CII_COL3+8,_E,_A); 		//Display data
				OSD230SeqSend2(DSP_ROW5,CII_COL5+8,_S,_E); 		//Display data
				OSD230SeqSend2(DSP_ROW5,CII_COL7+8,0,_W); 		//Display data
				OSD230SeqSend2(DSP_ROW5,CII_COL9+8,_A,_I); 		//Display data
				OSD230SeqSend2(DSP_ROW5,CII_COL11+8,_T,0); 		//Display data



				OSD230SeqSend(ATTR_ROW6,CII_COL1+5,0x00,18); 		//Attribute data
				OSD230SeqSend2(DSP_ROW6,CII_COL1+5,_P,_R); 		//Display data
				OSD230SeqSend2(DSP_ROW6,CII_COL3+5,_E,_S); 		//Display data
				OSD230SeqSend2(DSP_ROW6,CII_COL5+5,_S,0); 		//Display data
				OSD230SeqSend2(DSP_ROW6,CII_COL7+5,_LRectAngle,_M); 	//Display data
				OSD230SeqSend2(DSP_ROW6,CII_COL9+5,_RRectAngle,0); 	//Display data
				OSD230SeqSend2(DSP_ROW6,CII_COL11+5,_T,_O); 	//Display data
				OSD230SeqSend2(DSP_ROW6,CII_COL13+5,0,_S); 		//Display data
				OSD230SeqSend2(DSP_ROW6,CII_COL15+5,_T,_O); 		//Display data
				OSD230SeqSend2(DSP_ROW6,CII_COL17+5,_P,0); 		//Display data

				OSD230SeqSend(ATTR_ROW8,CII_COL1+8,0x00,12); 		//Attribute data
				OSD230SeqSend2(DSP_ROW8,CII_COL1+8,_T,_U); 		//Display data
				OSD230SeqSend2(DSP_ROW8,CII_COL3+8,_R,_B); 		//Display data
				OSD230SeqSend2(DSP_ROW8,CII_COL5+8,_O,0); 		//Display data
				OSD230SeqSend2(DSP_ROW8,CII_COL7+8,_S,_E); 		//Display data
				OSD230SeqSend2(DSP_ROW8,CII_COL9+8,_T,_U); 		//Display data
				OSD230SeqSend2(DSP_ROW8,CII_COL11+8,_P,0); 		//Display data
	
				break;
		
		case	tvmenu_channel_edit:
			#if defined (USE_NTSCtuner)

				#ifdef	OsdMenuType1
				OSD230SeqSend(ATTR_ROW3,CII_COL0,OSD_BLACK,30);
				OSD230PtrSend(DSP_ROW3,CII_COL8,ChannelEdit[0],ChannelEdit_Sizeof[0]);
				OSD230SeqSend(ATTR_ROW4,CII_COL0,OSD_BLACK,30);
				OSD230PtrSend(DSP_ROW4,CII_COL0+4,CHedit_ch_add[0],CHedit_ch_add_Sizeof[0]);

				#else
				OSD230SeqSend(ATTR_ROW3,CII_COL0,OSD_BLACK,30);
				OSD230PtrSend(DSP_ROW3,CII_COL8,ChannelEdit[0],ChannelEdit_Sizeof[0]);
				OSD230SeqSend(ATTR_ROW5,CII_COL0,OSD_BLACK,30);
				OSD230PtrSend(DSP_ROW5,CII_COL0+4,CHedit_ch_add[0],CHedit_ch_add_Sizeof[0]);
				#endif

				RemAddBtn=1;
				ProgEditCh_display();
			
			#elif defined (USE_PALSECAMtuner)
				#ifndef PalCountry_ChinaOnly	//+++++++++++++++++++++
				OSD230SeqSend(ATTR_ROW3,CII_COL0,OSD_BLACK,30);
				OSD230PtrSend(DSP_ROW3,CII_COL8,ProgrammEdit[0],ProgrammEdit_Sizeof[0]);

				OSD230SeqSend(ATTR_ROW4,CII_COL0,OSD_BLACK,30);
				OSD230PtrSend(DSP_ROW4,CII_COL0+3,PRedit_ch_name[0],PRedit_ch_name_Sizeof[0]);

				for(i=0;i<5;i++)	//6~10 line(i=0~4) ->>//5~9
				{
					OSD230SeqSend(ATTR_ROW5+i,CII_COL0,OSD_BLACK,30);		//Attribute data
					OSD230SeqSend2(DSP_ROW5+i,CII_COL0+3,_P,_R); 		//Display data
					OSD230SeqSend2(DSP_ROW5+i,CII_COL0+3+5,0,_C); 		//Display data
				}

				ProgEditCh_display();
				
				
				#else	//+++++++++++++++++++++++
				
				#ifdef	OsdMenuType1
				OSD230SeqSend(ATTR_ROW3,CII_COL0,OSD_BLACK,30);
				OSD230PtrSend(DSP_ROW3,CII_COL8,ChannelEdit[0],ChannelEdit_Sizeof[0]);
				OSD230SeqSend(ATTR_ROW4,CII_COL0,OSD_BLACK,30);
				OSD230PtrSend(DSP_ROW4,CII_COL0+4,CHedit_ch_add[0],CHedit_ch_add_Sizeof[0]);
				#else
				OSD230SeqSend(ATTR_ROW3,CII_COL0,OSD_BLACK,30);
				OSD230PtrSend(DSP_ROW3,CII_COL8,ChannelEdit[0],ChannelEdit_Sizeof[0]);
				OSD230SeqSend(ATTR_ROW5,CII_COL0,OSD_BLACK,30);
				OSD230PtrSend(DSP_ROW5,CII_COL0+4,CHedit_ch_add[0],CHedit_ch_add_Sizeof[0]);
				#endif
				RemAddBtn=1;
				ProgEditCh_display();
				#endif	//++++++++++++++++++++++++
			#endif			
				
				break;
			
			#if defined (USE_NTSCtuner)
		case	tvmenu_antena_input:
				break;
			#endif
			
			#ifdef	Ccd_Vchip
	 	case	tvmenu_Ccd:
	 		OSD230SeqSend(ATTR_ROW3,CII_COL1+6,0x00,14); 		//Attribute data
			OSD230SeqSend2(DSP_ROW3,CII_COL1+6,_C,_l); 		//Display data
			OSD230SeqSend2(DSP_ROW3,CII_COL3+6,_o,_s); 		//Display data
			OSD230SeqSend2(DSP_ROW3,CII_COL5+6,_e,_d); 		//Display data
			OSD230SeqSend2(DSP_ROW3,CII_COL7+6,0,_C); 		//Display data
			OSD230SeqSend2(DSP_ROW3,CII_COL9+6,_a,_p); 		//Display data
			OSD230SeqSend2(DSP_ROW3,CII_COL11+6,_t,_i); 		//Display data
			OSD230SeqSend2(DSP_ROW3,CII_COL13+6,_o,_n); 		//Display data
			
	 		OSD230SeqSend(ATTR_ROW5,CII_COL1+4,0x00,7); 		//Attribute data
			OSD230SeqSend2(DSP_ROW5,CII_COL1+4,_C,_A); 		//Display data
			OSD230SeqSend2(DSP_ROW5,CII_COL3+4,_P,_T); 		//Display data
			OSD230SeqSend2(DSP_ROW5,CII_COL5+4,_I,_O); 		//Display data
			OSD230SeqSend2(DSP_ROW5,CII_COL7+4,_N,0); 		//Display data
			CcdCaptionSelFunc();
			
	 		OSD230SeqSend(ATTR_ROW6,CII_COL1+4,0x00,4); 		//Attribute data
			OSD230SeqSend2(DSP_ROW6,CII_COL1+4,_M,_O); 		//Display data
			OSD230SeqSend2(DSP_ROW6,CII_COL3+4,_D,_E); 		//Display data
			CcdModeSelFunc();
			
	 		OSD230SeqSend(ATTR_ROW7,CII_COL1+4,0x00,7); 		//Attribute data
			OSD230SeqSend2(DSP_ROW7,CII_COL1+4,_C,_H); 		//Display data
			OSD230SeqSend2(DSP_ROW7,CII_COL3+4,_A,_N); 		//Display data
			OSD230SeqSend2(DSP_ROW7,CII_COL5+4,_N,_E); 		//Display data
			OSD230SeqSend2(DSP_ROW7,CII_COL7+4,_L,0); 		//Display data
			CcdChannelSelFunc();
			
	 		OSD230SeqSend(ATTR_ROW8,CII_COL1+4,0x00,5); 		//Attribute data
			OSD230SeqSend2(DSP_ROW8,CII_COL1+4,_F,_I); 		//Display data
			OSD230SeqSend2(DSP_ROW8,CII_COL3+4,_E,_L); 		//Display data
			OSD230SeqSend2(DSP_ROW8,CII_COL5+4,_D,0); 		//Display data
			CcdFieldSelFunc();
			
	 		OSD230SeqSend(ATTR_ROW9,CII_COL1+4,0x00,7); 		//Attribute data
			OSD230SeqSend2(DSP_ROW9,CII_COL1+4,_D,_I); 		//Display data
			OSD230SeqSend2(DSP_ROW9,CII_COL3+4,_S,_P); 		//Display data
			OSD230SeqSend2(DSP_ROW9,CII_COL5+4,_L,_A); 		//Display data
			OSD230SeqSend2(DSP_ROW9,CII_COL7+4,_Y,0); 		//Display data
			CcdDisplaySelFunc();
	 		break;
	                
	 	case	tvmenu_Vchip:
	 	/*
	 		OSD230SeqSend(ATTR_ROW4,CII_COL1+4,0x00,7); 		//Attribute data
			OSD230SeqSend2(DSP_ROW4,CII_COL1+4,_V,_minus); 		//Display data
			OSD230SeqSend2(DSP_ROW4,CII_COL3+4,_c,_h); 		//Display data
			OSD230SeqSend2(DSP_ROW4,CII_COL5+4,_i,_p); 		//Display data
			OSD230SeqSend2(DSP_ROW4,CII_COL7+4,_Y,0); 		//Display data
			*/
#if 1//2003-11-28
			OSD230PtrSend(DSP_ROW4,CII_COL11, Vchip[0], Vchip_Sizeof[0]); 	//Display data
			
	 		OSD230SeqSend(ATTR_ROW6,CII_COL1+5,0x00,16); 		//Attribute data
			OSD230SeqSend2(DSP_ROW6,CII_COL1+5,_E,_n); 		//Display data
			OSD230SeqSend2(DSP_ROW6,CII_COL3+5,_t,_e); 		//Display data
			OSD230SeqSend2(DSP_ROW6,CII_COL5+5,_r,0); 		//Display data
			OSD230SeqSend2(DSP_ROW6,CII_COL7+5,_P,_i); 		//Display data
			OSD230SeqSend2(DSP_ROW6,CII_COL9+5,_n,0); 		//Display data
			OSD230SeqSend2(DSP_ROW6,CII_COL11+5,_Colon,0); 		//Display data
			OSD230SeqSend2(DSP_ROW6,CII_COL13+5,_UnderBar,_UnderBar); 		//Display data
			OSD230SeqSend2(DSP_ROW6,CII_COL15+5,_UnderBar,_UnderBar); 		//Display data
			
#endif	
	 		break;
			#endif
		
		case	tvmenu_finetune:
			break;
	}
}

void	MuteFunc(void)	//2003-05-30 by thkim	//sound mute
{
	xOSD_WIN_REG[0x0E] = 0x1f;
	
	OSD230SeqSend(DSP_ROW0,CII_COL0,0x00,30);	//clear
	OSD230SeqSend(DSP_ROW1,CII_COL0,0x00,30);

	OSD230SeqSend(ATTR_ROW0,CII_COL1,OSD_RED,2); 	//Attribute data
	OSD230SeqSend(DSP_ROW0,CII_COL1,_SpeakerOff,1); //Display data  	//스피커 아이콘

	OSDcharacters=MuteChars;
	if(SoundMuteOnFlag)	DisplayMenuWindow();	//뮤트 글자
}
			
	
void	MuteExe(void)	//2004-05-28
{
	SoundMuteOnFlag ^=1;			//1:ON, 0:Off
	if(SoundMuteOnFlag)
	{	//mute 설정
//		OSDSelKeyin=0;
		OSDWindows = MuteWindow;
		OSDcharacters = MuteChars;
		//if(MENUstatus==VolumeDisplay||MENUstatus==ValueDisplay) OSDstatus = ReMuteDisplay;
		if(MENUstatus==VolumeDisplay) OSDstatus = ReMuteDisplay;
		else OSDstatus = MuteDisplay;
		Mute_SoundOff;
	}
	else
	{	//mute 해제
//		OSDSelKeyin=0;
		OSDWindows = VolumeWindow;
		OSDcharacters = VolumeChars;
		if(MENUstatus==MuteDisplay) OSDstatus = ReVolumeDisplay;
		else OSDstatus = VolumeDisplay;
		OsdMode = volume_mode;
		
		ArrangeFunctionTable();
		switch(CurrentFunction)//Volume Paht 정리.
		{
			case 0://ananlog
			case 1://digital
				AudioSelection_PC;
				PutVolumePWM();
				break;
			case 2://composite
			case 3://s-video
			case 5://RGB+COMPOSITE
			case 6://RGB+SVIDEO
			case 8://DVI+COMPOSITE
			case 9://DVI+SVIDEO
				AudioSelection_AV;
				PutVolumePWM();
				break;
				
			case 4://Tuner<channel numner display>
			case 7://RGB+TUNER
			case 10://DVI+TUNER
			#if	defined(BtcBoard_Option) 		
				AudioSelection_TV;
			#else							
				AudioSelection_HIGH;
			#endif						
				break;
		}
		Mute_SoundOn;
		PutVolumePWM();
	}
}
	
void	SscSelFunc(void)		//2003-08-08 by thkim
{
	MenuMinVal=SSCNormal;
	MenuMaxVal=SSCUser;
	MenuVal=xEEPROMBuffer[SSC];

	
	xOSD_WIN_REG[0x0E] = 0x1f;		//hieght
	xOSDRA=DSP_ROW1;xOSDCA=CII_COL30;	//Attr
	xOSDDT0=HVchar_dbl;			//가로,세로 2배 확대
	
//	OSD230SeqSend(ATTR_ROW1,CII_COL0,OSD_BLUE,30);	//색깔
	//xOSDW_OPTION[1]=0x80|0x40;

	switch(xEEPROMBuffer[SSC])
	{
		#if 0
		case SSCNormal:
			OSD230SeqSend(ATTR_ROW1,CII_COL0,OSD_BLUE,30);	//색깔
			OSD230PtrSend(DSP_ROW1,CII_COL0,Normal2,sizeof(Normal2));
			break;
        	case SSCMusic:
			OSD230SeqSend(ATTR_ROW1,CII_COL0,OSD_RED,30);	//색깔
			OSD230PtrSend(DSP_ROW1,CII_COL0,Music2,sizeof(Music2));
			break;
		case SSCCinema:
			OSD230SeqSend(ATTR_ROW1,CII_COL0,OSD_GREEN,30);	//색깔
			OSD230PtrSend(DSP_ROW1,CII_COL0,Cinema2,sizeof(Cinema2));
			break;
		case SSCNews:
			OSD230SeqSend(ATTR_ROW1,CII_COL0,OSD_CYAN,30);	//색깔
			OSD230PtrSend(DSP_ROW1,CII_COL0,News2,sizeof(News2));
			break;
		case SSCUser:
			OSD230SeqSend(ATTR_ROW1,CII_COL0,OSD_YELLOW,30);	//색깔
			OSD230PtrSend(DSP_ROW1,CII_COL0,User2,sizeof(User2));
			break;
		#else
		case SSCNormal:
			OSD230SeqSend(ATTR_ROW1,CII_COL0,OSD_BLUE,30);	//색깔
			OSD230PtrSend(DSP_ROW1,CII_COL0,Normal2[0],Normal2_Sizeof[0]);
			break;
        	case SSCMusic:
			OSD230SeqSend(ATTR_ROW1,CII_COL0,OSD_RED,30);	//색깔
			OSD230PtrSend(DSP_ROW1,CII_COL0,Music2[0],Music2_Sizeof[0]);
			break;
		case SSCCinema:
			OSD230SeqSend(ATTR_ROW1,CII_COL0,OSD_GREEN,30);	//색깔
			OSD230PtrSend(DSP_ROW1,CII_COL0,Cinema2[0],Cinema2_Sizeof[0]);
			break;
		case SSCNews:
			OSD230SeqSend(ATTR_ROW1,CII_COL0,OSD_CYAN,30);	//색깔
			OSD230PtrSend(DSP_ROW1,CII_COL0,News2[0],News2_Sizeof[0]);
			break;
		case SSCUser:
			OSD230SeqSend(ATTR_ROW1,CII_COL0,OSD_YELLOW,30);	//색깔
			OSD230PtrSend(DSP_ROW1,CII_COL0,User2[0],User2_Sizeof[0]);
			break;
		#endif
	}
}



void	SscService(void)	//2003-08-08	by thkim
{
	if(NowTopOsdOn)
	{
		NowTopOsdOn = 0;
		OSDWindows = 0;
		OSDstatus = OSDoff;
		OsdService();
	}

	OSDWindows = SscWindow;
	OSDstatus = SscWindowDisplay;
	OsdMode = SscWindowDisplay;
	OSDcharacters = SscChar;
	
	if(SubWindowMsgFlag)
	{
		if(xEEPROMBuffer[SSC]<SSCUser) xEEPROMBuffer[SSC]++;
		else xEEPROMBuffer[SSC]=SSCNormal;
	}
	
	OSDstatus = OsdRamClear;
	Osd_onoff();

	NowTopOsdOn = 0;
	OsdGrade=0;

	DisplayWindow();				
			
	#if defined(SXGA_Panel)
	xOSD_WIN_REG[0x0D]=37;//Center-Bottom
	xOSD_WIN_REG[0x0C]=0xd7;
	#elif defined(WXGA_Panel)
	xOSD_WIN_REG[0x0D]=0x26;	//H
	xOSD_WIN_REG[0x0C]=0x99;	//V
	#elif defined(XGA_Panel)
	xOSD_WIN_REG[0x0D]=0x22;//Center-Bottom
	xOSD_WIN_REG[0x0C]=0x7E;
	#elif defined(SVGA_Panel)
	xOSD_WIN_REG[0x0D]=0x22;//Center-Bottom
	xOSD_WIN_REG[0x0C]=0x7E;
	#endif
			
	idelay5m(6);

	SscSelFunc();

	SoundMuteOnFlag=0;	//2003-10-17
	Mute_SoundOn;				//2003-10-17
	PutVolumePWM();			//2003-10-17
	SoundSet();	// smpark 20030809

	OSDstatus = NowStatusDisplay;
	Osd_onoff();

	SubWindowMsgFlag=1;
	
	OSDstatus = OSDexpire_timer;
	OSDofftimer = 3*200;//3sec!
	MENUstatus = SscWindowDisplay;
}


void	SpcSelFunc(void)		//2003-08-08 by thkim
{
	MenuMinVal=SPCNormal;
	MenuMaxVal=SPCUser;
	MenuVal=xEEPROMBuffer[SmartPicCtr_buf];

	xOSD_WIN_REG[0x0E] = 0x1f;		//hieght
	xOSDRA=DSP_ROW1;xOSDCA=CII_COL30;	//Attr
	xOSDDT0=HVchar_dbl;			//가로,세로 2배 확대
	
//	OSD230SeqSend(ATTR_ROW1,CII_COL0,OSD_BLUE,30);	//색깔


	switch(xEEPROMBuffer[SmartPicCtr_buf])
	{
		#if 0
		case SPCNormal:
			OSD230SeqSend(ATTR_ROW1,CII_COL0,OSD_BLUE,30);	//색깔
			OSD230PtrSend(DSP_ROW1,CII_COL0,Normal2,sizeof(Normal2));
			break;
        	case SPCDynamic:
			OSD230SeqSend(ATTR_ROW1,CII_COL0,OSD_RED,30);	//색깔
			OSD230PtrSend(DSP_ROW1,CII_COL0,Dynamic2,sizeof(Dynamic2));
			break;
		case SPCCinema:
			OSD230SeqSend(ATTR_ROW1,CII_COL0,OSD_GREEN,30);	//색깔
			OSD230PtrSend(DSP_ROW1,CII_COL0,Cinema2,sizeof(Cinema2));
			break;
		case SPCUser:
			OSD230SeqSend(ATTR_ROW1,CII_COL0,OSD_YELLOW,30);	//색깔
			OSD230PtrSend(DSP_ROW1,CII_COL0,User2,sizeof(User2));
			break;
		#else
		
		case SPCNormal:
			OSD230SeqSend(ATTR_ROW1,CII_COL0,OSD_BLUE,30);	//색깔
			OSD230PtrSend(DSP_ROW1,CII_COL0,Normal2[0],Normal2_Sizeof[0]);
			break;
        	case SPCDynamic:
			OSD230SeqSend(ATTR_ROW1,CII_COL0,OSD_RED,30);	//색깔
			OSD230PtrSend(DSP_ROW1,CII_COL0,Dynamic2[0],Dynamic2_Sizeof[0]);
			break;
		case SPCCinema:
			OSD230SeqSend(ATTR_ROW1,CII_COL0,OSD_GREEN,30);	//색깔
			OSD230PtrSend(DSP_ROW1,CII_COL0,Cinema2[0],Cinema2_Sizeof[0]);
			break;
		case SPCUser:
			OSD230SeqSend(ATTR_ROW1,CII_COL0,OSD_YELLOW,30);	//색깔
			OSD230PtrSend(DSP_ROW1,CII_COL0,User2[0],User2_Sizeof[0]);
			break;
		#endif
	}


}
	
void	SpcService(void)	//2003-08-08	by thkim
{
	if(NowTopOsdOn)
	{
		NowTopOsdOn = 0;
		OSDWindows = 0;
		OSDstatus = OSDoff;
		OsdService();
	}


	OSDWindows = SpcWindow;
	OSDstatus = SpcWindowDisplay;
	OsdMode = SpcWindowDisplay;
	OSDcharacters = SpcChar;
	
	if(SubWindowMsgFlag)
	{
		if(xEEPROMBuffer[SmartPicCtr_buf]<SPCUser) xEEPROMBuffer[SmartPicCtr_buf]++;
		else xEEPROMBuffer[SmartPicCtr_buf]=SPCNormal;
	}
	
	OSDstatus = OsdRamClear;
	Osd_onoff();

	NowTopOsdOn = 0;
	OsdGrade=0;
				
	DisplayWindow();
			
			
	#if defined(SXGA_Panel)
	xOSD_WIN_REG[0x0D]=37;//Center-Bottom
	xOSD_WIN_REG[0x0C]=0xd7;
	#elif defined(WXGA_Panel)
	xOSD_WIN_REG[0x0D]=0x26;	//H
	xOSD_WIN_REG[0x0C]=0x99;	//V
	#elif defined(XGA_Panel)
	//xOSD_WIN_REG[0x0D]=0x22;//Center-Bottom
	//xOSD_WIN_REG[0x0C]=0x7E;
	#elif defined(SVGA_Panel)
	//xOSD_WIN_REG[0x0D]=0x22;//Center-Bottom
	//xOSD_WIN_REG[0x0C]=0x7E;
	#endif
			
	idelay5m(6);
	
	SpcSelFunc();
	TVColorSet();		// smpark 20030809

	OSDstatus = NowStatusDisplay;
	Osd_onoff();

	SubWindowMsgFlag=1;
	
	OSDstatus = OSDexpire_timer;
	OSDofftimer = 3*200;//3sec!
	MENUstatus = SscWindowDisplay;
}

void	SleepSelFunc(void)		//2003-08-08 	by thkim
{
	BYTE temp0=0, temp1=0;
	
	MenuMinVal=Sleep_min;
	MenuMaxVal=Sleep_max;
	MenuVal=xEEPROMBuffer[Sleep_buf];

	xOSD_WIN_REG[0x0E] = 0x1f;		//hieght
	xOSDRA=DSP_ROW1;xOSDCA=CII_COL30;	//Attr
	xOSDDT0=HVchar_dbl;			//가로,세로 2배 확대
	
	OSD230SeqSend(ATTR_ROW1,CII_COL0,OSD_GREEN,30);	//색깔

	OSD230SeqSend2(DSP_ROW0,CII_COL0,0,0);	// smpark 20030827
	OSD230PtrSend(DSP_ROW1,CII_COL0,Sleep2[0],Sleep2_Sizeof[0]);

	temp0 = calToChar(xEEPROMBuffer[Sleep_buf]);
	HighOSDArea=0;//Low Display data.
	temp1 = 0;

	if(temp0==1)
	{
		OSD230SeqSend2(DSP_ROW1,CII_COL10+(3-temp0)*2,_minus,0);
		OSD230SeqSend2(DSP_ROW1,CII_COL10+(3-temp0-1)*2,_minus,0);
	}
	else
	{
		OSD230SeqSend(DSP_ROW1,CII_COL10,0x00,10);	// 위치지정
		OSD230ColSend(CII_COL10+(3-temp0)*2);

		while(temp0--)
		{
			OSD230DataSend(CalBuffer[temp1]+0x01);	//실제 값 표시
			temp1++;
			
			OSD230ColSend(CII_COL10+(3-temp0)*2);	//2003-08-12, 가로확대로 인해 두번째숫자 안나오는것 보정위해.
		}
	}
}

void	SleepService(void)	//2003-08-08	by thkim
{
	if(NowTopOsdOn)
	{
		NowTopOsdOn = 0;
		OSDWindows = 0;
		OSDstatus = OSDoff;
		OsdService();
	}

	if(OsdMode != SleepWindowDisplay ||OSDcharacters!=SleepChar)
	{
		OSDstatus = OsdRamClear;
		Osd_onoff();
	}

	OSDWindows = SleepWindow;
	OSDstatus = SleepWindowDisplay;
	OsdMode = SleepWindowDisplay;
	OSDcharacters = SleepChar;
	
	if(SubWindowMsgFlag)
	{
		if(xEEPROMBuffer[Sleep_buf]<Sleep_max) xEEPROMBuffer[Sleep_buf]+=10;
		else xEEPROMBuffer[Sleep_buf]=Sleep_min;
		
		SleepTimer=(xEEPROMBuffer[Sleep_buf])*step_1min;
	}
	

	NowTopOsdOn = 0;
	OsdGrade=0;
				
	DisplayWindow();
			
			
	#if defined(SXGA_Panel)||defined(WXGA_Panel)
	xOSD_WIN_REG[0x0D]=60;//Center-Bottom
	xOSD_WIN_REG[0x0C]=0x01;
	#elif defined(XGA_Panel)
	//xOSD_WIN_REG[0x0D]=0x22;//Center-Bottom
	//xOSD_WIN_REG[0x0C]=0x7E;
	#elif defined(SVGA_Panel)
	//xOSD_WIN_REG[0x0D]=0x22;//Center-Bottom
	//xOSD_WIN_REG[0x0C]=0x7E;
	#endif
			
	idelay5m(6);
	
	SleepSelFunc();
	
	SubWindowMsgFlag=1;
	
	OSDstatus = OSDexpire_timer;
	OSDofftimer = 3*200;//3sec!
	MENUstatus = SleepWindowDisplay;
}
			
void OsdService(void)
{
	switch(OSDstatus)
	{
		case	TopMenuWindow:			//main osd menu window그리기
			xOSDW_OPTION[1]=0x00; 	// smpark 20030818 튀는것 방지용
			//xEEPROMBuffer[OSDOFFTIME_buf]=60;
			NowTopOsdOn = 1;
			OsdGrade=0;//2003-05-27 3:24오후
			
			OSDstatus = OsdRamClear;	//우선 지우고..
			Osd_onoff();

//			OSDstatus = OSDoff;	//우선 지우고..
//			Osd_onoff();

			if((xEEPROMBuffer[MainSubInputSource]!=10)&&(xEEPROMBuffer[MainSubInputSource]!=14)&&(xEEPROMBuffer[MainSubInputSource]!=18) )	//COMPOSITE,S-VIDEO,TUNER 이외의 입력 
			{	// PC
				//OsdPositionFunction(xEEPROMBuffer[OSDHPOSITION_buf]);
				xOSD_WIN_REG[0x0D]=xEEPROMBuffer[OSDHPOSITION_buf]+1;//H
				xOSD_WIN_REG[0x0C]=xEEPROMBuffer[OSDVPOSITION_buf];//V
			}
			else	// Video
			{
			#if defined(VideoDoubleOSD)
				#if defined(SXGA_Panel)
				xOSD_WIN_REG[0x0D]=21;//20;//H
				xOSD_WIN_REG[0x0C]=65;//V
				#elif defined(WXGA_Panel)
				xOSD_WIN_REG[0x0D]=21;//20;//H
				xOSD_WIN_REG[0x0C]=34;//V
				#elif defined(XGA_Panel)
				xOSD_WIN_REG[0x0D]=15;//20;//H
				xOSD_WIN_REG[0x0C]=34;//V
				#endif
			#else	// normal size
				#if defined(SXGA_Panel)
				xOSD_WIN_REG[0x0D]=79;//H
				xOSD_WIN_REG[0x0C]=0x5e;//V
				#elif defined(WXGA_Panel)
				xOSD_WIN_REG[0x0D]=76;//H
				xOSD_WIN_REG[0x0C]=0x43;//V
				#elif defined(XGA_Panel)
				xOSD_WIN_REG[0x0D]=15;//H
				xOSD_WIN_REG[0x0C]=0x5e;//V
				#endif

			#endif
			}
						
			DisplayWindow();
			
			if( (xEEPROMBuffer[MainSubInputSource]!=10)&&(xEEPROMBuffer[MainSubInputSource]!=14)&&(xEEPROMBuffer[MainSubInputSource]!=18) )	//COMPOSITE,S-VIDEO,TUNER 이외의 입력 
			{	//PC
				//OSDSeqSend(IN_ATTR_ROW15,IN_CII_COL15,(xEEPROMBuffer[OSDHPOSITION_buf]-0x1b)&0x7f,1);//horizontal
				OSDSeqSend(IN_ATTR_ROW15,IN_CII_COL15,(4+(xEEPROMBuffer[OSDHPOSITION_buf]/5)*3),1);//horizontal

				OSDSeqSend(IN_ATTR_ROW15,IN_CII_COL14,xEEPROMBuffer[OSDVPOSITION_buf]-1,1);//vertical
			}
				
			if( (xEEPROMBuffer[MainSubInputSource]!=10)&&(xEEPROMBuffer[MainSubInputSource]!=14)&&(xEEPROMBuffer[MainSubInputSource]!=18) )	//COMPOSITE,S-VIDEO,TUNER 이외의 입력 
			{	//PC
				Display_TopMenuIcon();
			}
			else	Display_TvTopMenuIcon();	//VIDEO
			
			OSDstatus = TopMenuWindow;	
			Osd_onoff();//
			
			DisplayInformation();
			
			DisplayMenuWindow();
			
			IconSel();
			
			SubWindowMsgFlag=0;
			OSDofftimer = (WORD)xEEPROMBuffer[OSDOFFTIME_buf]*200;
			OSDstatus = OSDexpire_timer;
			MENUstatus = TopMenuWindow;

			xOSDW_OPTION[1]=0x80; 	// smpark 20030818
			break;
		
		case	SubMenuWindows:

			OsdGrade=1;
			
			//DisplayInformation();
			DisplayMenuWindow();
			
			Display_MenuBarPercent();
			
			SubWindowMsgFlag=0;
			OSDofftimer = (WORD)xEEPROMBuffer[OSDOFFTIME_buf]*200;
			OSDstatus = OSDexpire_timer;
			MENUstatus = SubMenuWindows;
			break;


		case	SubMenuWindows2:
			
			OsdGrade=2;

			if( (MenuNum==menu_language)||(GetTopMenu()==MENU_PIP && (CurrentFunction>=PipRnC_mode && CurrentFunction<=PipDnT_mode)) )
			{
				//DisplayMenuWindow();	//
				MenuBarValue();
			}
			if(TvMenuNum==tvmenu_lang)	TvMenuBarValue();
			Display_MenuBarPercent();
			
			SubWindowMsgFlag=0;
			OSDofftimer = (WORD)xEEPROMBuffer[OSDOFFTIME_buf]*200;
			OSDstatus = OSDexpire_timer;
			MENUstatus = SubMenuWindows2;

			break;
		
		case	ColorTempWindow:

			//IconSel();//Displaycusor();
			
			OsdGrade=2;

			Display_MenuBarPercent();
			
			SubWindowMsgFlag=0;
			OSDofftimer = (WORD)xEEPROMBuffer[OSDOFFTIME_buf]*200;
			OSDstatus = OSDexpire_timer;
			MENUstatus = ColorTempWindow;

			break;

		case	CountryWindow:

			//IconSel();//Displaycusor();
			
			OsdGrade=2;
			
			//Display_MenuBarPercent();
			//if(OSDSelKeyin) DisplayBarandPercent();
			//else DisplayBarandPercentClear();
			
			SubWindowMsgFlag=0;
			OSDofftimer = (WORD)xEEPROMBuffer[OSDOFFTIME_buf]*200;
			OSDstatus = OSDexpire_timer;
			MENUstatus = CountryWindow;

			break;
			
		case	AutoChSetupWindow:

/*			IconSel();//Displaycusor();
			
			OsdGrade=2;
			
			Display_MenuBarPercent();
			//if(OSDSelKeyin) DisplayBarandPercent();
			//else DisplayBarandPercentClear();
			
			OSDofftimer = (WORD)xEEPROMBuffer[OSDOFFTIME_buf]*200;
			OSDstatus = OSDexpire_timer;
*/			MENUstatus = AutoChSetupWindow;

			break;
			
			
		case	AUTOTuneOSD://AUTO
			
			//OSDstatus = OsdRamClear;
			//Osd_onoff();
			
			#if defined(SXGA_Panel)
			xOSD_WIN_REG[0x0D]=0x47;//H
			xOSD_WIN_REG[0x0C]=0x6c;//V
			#elif defined(WXGA_Panel)  
			xOSD_WIN_REG[0x0D]=0x48;//H
			xOSD_WIN_REG[0x0C]=0x4f;//V
			#elif defined(XGA_Panel)
			xOSD_WIN_REG[0x0D]=0x1F;//H
			xOSD_WIN_REG[0x0C]=0x3C;//V
			#elif defined(SVGA_Panel)  
			xOSD_WIN_REG[0x0D]=0x1F;//H
			xOSD_WIN_REG[0x0C]=0x3C;//V
			#endif
			
			OSDstatus=AUTOTuneOSD;
			OSD230SeqSend(DSP_ROW3,CII_COL0,0x00,30);
			OSD230SeqSend(DSP_ROW4,CII_COL0,0x00,30);
			
			DisplayWindow();
			DisplayMenuWindow();
			//Osd_onoff();

			OSDstatus = 100;//Never stop,(Auto 종료후에..)
			MENUstatus = AUTOTuneOSD;
			break;
			
		case	OSDHotkeyMessageWindow:
			
			OSDstatus = OsdRamClear;
			Osd_onoff();
			
			#if defined(SXGA_Panel)
			xOSD_WIN_REG[0x0D]=0x47;//H
			xOSD_WIN_REG[0x0C]=0x6c;//V
			#elif defined(WXGA_Panel)  
			xOSD_WIN_REG[0x0D]=0x48;//H
			xOSD_WIN_REG[0x0C]=0x4f;//V
			#elif defined(XGA_Panel) 
			xOSD_WIN_REG[0x0D]=0x1F;//H
			xOSD_WIN_REG[0x0C]=0x3C;//V
			#elif defined(SVGA_Panel)  
			xOSD_WIN_REG[0x0D]=0x1F;//H
			xOSD_WIN_REG[0x0C]=0x3C;//V
			#endif

			OSDstatus=OSDHotkeyMessageWindow;
			DisplayWindow();
			DisplayMenuWindow();//Displaycharacter();
			//Osd_onoff();
			//OSDstatus = 100;//Never stop,(Auto 종료후에..)
			//MENUstatus = OSDHotkeyMessageWindow;

			OSDofftimer = (WORD)xEEPROMBuffer[OSDOFFTIME_buf]*200;
			OSDstatus = OSDexpire_timer;
			MENUstatus=OSDHotkeyMessageWindow;
			break;		

		case	FactoryRstOSD:
		
			OSDstatus = OsdRamClear;
			Osd_onoff();
			
			#if defined(SXGA_Panel)
			xOSD_WIN_REG[0x0D]=0x47;//H
			xOSD_WIN_REG[0x0C]=0x6c;//V
			#elif defined(WXGA_Panel)  
			xOSD_WIN_REG[0x0D]=0x48;//H
			xOSD_WIN_REG[0x0C]=0x4f;//V
			#elif defined(XGA_Panel)
			xOSD_WIN_REG[0x0D]=0x1F;//H
			xOSD_WIN_REG[0x0C]=0x3C;//V
			#elif defined(SVGA_Panel)
			xOSD_WIN_REG[0x0D]=0x1F;//H
			xOSD_WIN_REG[0x0C]=0x3C;//V
			#endif
			
			OSDstatus=FactoryRstOSD;
			DisplayWindow();
			DisplayMenuWindow();//Displaycharacter();
			Osd_onoff();
			OSDstatus = 100;//Never stop,(Auto 종료후에..)
			MENUstatus = FactoryRstOSD;
			break;


		case	OSDCharArray://window내에 위치되는 char array
			
			DisplayMenuWindow();//Displaycharacter();
			//Displaycusor();
			//DisplayBarandPercent();
			//DisplayMenu();
			Display_MenuBarPercent();
			
			Osd_onoff();
			
			OSDofftimer = (WORD)xEEPROMBuffer[OSDOFFTIME_buf]*200;
			OSDstatus = OSDexpire_timer;
			MENUstatus = OSDCharArray;
			break;
		
		case	Cursermove:
			
			//Displaycusor();
//			if(OSDSelKeyin) DisplayBarandPercent();
			//else DisplayBarandPercentClear();
			
			OSDofftimer = (WORD)xEEPROMBuffer[OSDOFFTIME_buf]*200;
			OSDstatus = OSDexpire_timer;
			MENUstatus = Cursermove;
			break;

		case	ValueDisplay:
			
			//PutValueToDevices();
			PutData();
			
			//DisplayBarandPercent();
			Display_MenuBarPercent();
			
			OSDstatus = OSDexpire_timer;
			
			if(MENUstatus!=VolumeDisplay) {MENUstatus = ValueDisplay;OSDofftimer = (WORD)xEEPROMBuffer[OSDOFFTIME_buf]*200;}
			else OSDofftimer =  3*200;//3sec!,volume오프타이머값.
			break;
		
		case	MinMaxValueNotApply:
			OSDofftimer = (WORD)xEEPROMBuffer[OSDOFFTIME_buf]*200;
			OSDstatus = OSDexpire_timer;
			if(MENUstatus!=VolumeDisplay) MENUstatus = ValueDisplay;
			break;
			
		case	SscWindowDisplay:
			
			OSDstatus = OsdRamClear;
			Osd_onoff();
			NowTopOsdOn = 0;
			OsdGrade=0;
			
			#if defined(SXGA_Panel)
			xOSD_WIN_REG[0x0D]=17;//Center-Bottom
			xOSD_WIN_REG[0x0C]=0xe0;
			#elif defined(WXGA_Panel)
			xOSD_WIN_REG[0x0D]=30;//Center-Bottom
			xOSD_WIN_REG[0x0C]=0xe0;
			#elif defined(XGA_Panel)
			xOSD_WIN_REG[0x0D]=0x22;//Center-Bottom
			xOSD_WIN_REG[0x0C]=0x7E;
			#elif defined(SVGA_Panel)
			xOSD_WIN_REG[0x0D]=0x22;//Center-Bottom
			xOSD_WIN_REG[0x0C]=0x7E;
			#endif
			OSDstatus = OSDexpire_timer;
			DisplayWindow();

			SscSelFunc();
			DisplayMenuWindow();
			Osd_onoff();
			
			SubWindowMsgFlag=1;
			OSDofftimer = 3*200;//3sec!
			MENUstatus = SscWindowDisplay;
			break;
		
		//case	SpcWindowDisplay:
		//	break;
		
		//case	MtsWindowDisplay:
		//	break;
		
		//case	SleepWindowDisplay:
		//	break;
			
		//case 	RecallWindowDisplay:	//smpark 20030823
		//	break;

		//case 	AddDelWindowDisplay:
		//	break;

		//case	ChannelStatusDisplay:
		//	break;
			
		case	VolumeDisplay:
//			if(PreOSDstatus != VolumeDisplay){	// smpark 20030818
				InitOsdRam();	
//			}
			
			OSDstatus = OsdRamClear;
			Osd_onoff();
			NowTopOsdOn = 0;
			OsdGrade=0;
			ArrangeFunctionTable();//volume을 하면서 현재 모드(기능)를 CurrentFunction에 넣어둔다.
			
			#if defined(SXGA_Panel)
			xOSD_WIN_REG[0x0D]=0x13;//0x45;	//H
			xOSD_WIN_REG[0x0C]=0xe0;//0xE8;	//V
			#elif defined(WXGA_Panel)
			xOSD_WIN_REG[0x0D]=0x10;//Center-Bottom
			xOSD_WIN_REG[0x0C]=0xa2;
			#elif defined(XGA_Panel)
			xOSD_WIN_REG[0x0D]=0x9;//Center-Bottom
			xOSD_WIN_REG[0x0C]=0xa2;
			#elif defined(SVGA_Panel)
			xOSD_WIN_REG[0x0D]=0x7;//Center-Bottom
			xOSD_WIN_REG[0x0C]=0x7E;
			#endif
			
			OSDstatus = OSDexpire_timer;
			DisplayWindow();
			Display_MenuBarPercent();
			Osd_onoff();
			
			SubWindowMsgFlag=1;
			OSDofftimer = 3*200;//3sec!
			MENUstatus = VolumeDisplay;
			xOSDW_OPTION[1]=0x80|0x40;	//2003-09-16
//			PreOSDstatus = VolumeDisplay;	// smpark 20030818

			break;
		
		case	MuteDisplay:

			OSDstatus = OsdRamClear;
			Osd_onoff();
			NowTopOsdOn = 0;
			ArrangeFunctionTable();//mute 하면서 현재 모드(기능)를 CurrentFunction에 넣어둔다.
			
			#if defined(SXGA_Panel)
			xOSD_WIN_REG[0x0D]=0x13;//0x45;	//H
			xOSD_WIN_REG[0x0C]=0xe0;//0xE8;	//V
			#elif defined(WXGA_Panel)
			xOSD_WIN_REG[0x0D]=0x10;//Center-Bottom
			xOSD_WIN_REG[0x0C]=0xa2;
			#elif defined(XGA_Panel)
			xOSD_WIN_REG[0x0D]=0x9;//Center-Bottom
			xOSD_WIN_REG[0x0C]=0xa2;
			#elif defined(SVGA_Panel)
			xOSD_WIN_REG[0x0D]=0x22;//Center-Bottom
			xOSD_WIN_REG[0x0C]=0x7E;
			#endif
			
			DisplayWindow();

			MuteFunc();
			SubWindowMsgFlag=1;
			OSDstatus = 100;//Never OSD off!!
			MENUstatus = MuteDisplay;
			Osd_onoff();
			xOSDW_OPTION[1]=0x80|0x40;	//2003-09-16
			break;
		
		case	ReMuteDisplay:

			#if defined(SXGA_Panel)
			xOSD_WIN_REG[0x0D]=0x13;//0x45;	//H
			xOSD_WIN_REG[0x0C]=0xe0;//0xE8;	//V
			#elif defined(WXGA_Panel)
			xOSD_WIN_REG[0x0D]=0x10;//Center-Bottom
			xOSD_WIN_REG[0x0C]=0xa2;
			#elif defined(XGA_Panel)
			xOSD_WIN_REG[0x0D]=0x9;//Center-Bottom
			xOSD_WIN_REG[0x0C]=0xa2;
			#elif defined(SVGA_Panel)
			#elif defined(SVGA_Panel)
			xOSD_WIN_REG[0x0D]=0x22;//Center-Bottom
			xOSD_WIN_REG[0x0C]=0x7E;
			#endif

			OSD230SeqSend(DSP_ROW1,CII_COL0,0x00,30);
			DisplayWindow();
			
			MuteFunc();
			
			OSDstatus = 100;//Never OSD off!!
			MENUstatus = MuteDisplay;
			SubWindowMsgFlag=1;
			Osd_onoff();
			xOSDW_OPTION[1]=0x80|0x40;	//2003-09-16
			break;

		case	ReVolumeDisplay:
			
			#if defined(SXGA_Panel)
			xOSD_WIN_REG[0x0D]=0x13;//0x45;	//H
			xOSD_WIN_REG[0x0C]=0xe0;//0xE8;	//V
			#elif defined(WXGA_Panel)
			xOSD_WIN_REG[0x0D]=0x10;//Center-Bottom
			xOSD_WIN_REG[0x0C]=0xa2;
			#elif defined(XGA_Panel)
			xOSD_WIN_REG[0x0D]=0x9;//Center-Bottom
			xOSD_WIN_REG[0x0C]=0xa2;
			#elif defined(SVGA_Panel)
			#elif defined(SVGA_Panel)
			xOSD_WIN_REG[0x0D]=0x22;//Center-Bottom
			xOSD_WIN_REG[0x0C]=0x7E;
			#endif
			
			DisplayWindow();
			DisplayMenuWindow();//Displaycharacter();
			//DisplayBarandPercent();
			                         
			Display_MenuBarPercent();
			
			Osd_onoff();
			
			SubWindowMsgFlag=1;
			OSDstatus = OSDexpire_timer;
			OSDofftimer = 3*200;//3sec!
			MENUstatus = VolumeDisplay;
			xOSDW_OPTION[1]=0x80|0x40;	//2003-09-16
			break;
			
		case	AddSelChannelDisplay:
/*	youngdo 2003.8.20  사용안함.  memory save
			NowTopOsdOn = 1;
			OSDstatus = OsdRamClear;//우선 지우고..
			Osd_onoff();
			
			OsdPositionFunction(xEEPROMBuffer[OSDHPOSITION_buf]);
			OSDstatus = TopMenuWindow;
			DisplayWindow();
			DisplayMenuWindow();//Displaycharacter();
			//Displaycusor();
			//DisplayBarandPercent();
			Display_MenuBarPercent();
			
			Osd_onoff();
			
			OSDofftimer = (WORD)xEEPROMBuffer[OSDOFFTIME_buf]*200;
			OSDstatus = OSDexpire_timer;
			MENUstatus = TopMenuWindow;
			break;
*/
		case	TVchannelDisplay:
			
#if 0			
			if(MENUstatus != TVchannelDisplay)
			{
				OSDstatus = OsdRamClear;
				Osd_onoff();
				NowTopOsdOn = 0;
			}
			else{
				OSD230SeqSend(DSP_ROW0,CII_COL3,0x00,10);	//2003-08-08
				OSD230SeqSend(DSP_ROW1,CII_COL3,0x00,10);	//smpark 20030809 
			}
#endif				
			ArrangeFunctionTable();
			/*switch(CurrentFunction)
			{
				case 7://RGB+TUNER
				case 10://DVI+TUNER
				
				default:
					xOSD_WIN_REG[0x0D]=80;//test
					xOSD_WIN_REG[0x0C]=0;//test
					break;
/*
					#if defined(SXGA_Panel)
					switch(xEEPROMBuffer[PIPPOSITION])	
					{
						case 0://center
							if(xEEPROMBuffer[PIPSIZE_buf]) {xOSD_WIN_REG[0x0D]=0x60;xOSD_WIN_REG[0x0C]=0x4B;}//SMALL
							else 			{xOSD_WIN_REG[0x0D]=0x73;xOSD_WIN_REG[0x0C]=0x2E;}//LARGE
							break;
							
						case 1://right-top
							if(xEEPROMBuffer[PIPSIZE_buf]) {xOSD_WIN_REG[0x0D]=0xB6;xOSD_WIN_REG[0x0C]=0xEB;}
							else 			{xOSD_WIN_REG[0x0D]=0xB6;xOSD_WIN_REG[0x0C]=0xEB;}
							break;
							
						case 2://right-bottom
							if(xEEPROMBuffer[PIPSIZE_buf]) {xOSD_WIN_REG[0x0D]=0xB6;xOSD_WIN_REG[0x0C]=0xAC;}
							else 			{xOSD_WIN_REG[0x0D]=0xB6;xOSD_WIN_REG[0x0C]=0x7d;}
							break;
							
						case 3://left-bottom
							if(xEEPROMBuffer[PIPSIZE_buf]) {xOSD_WIN_REG[0x0D]=0x0E;xOSD_WIN_REG[0x0C]=0xAC;}
							else 			{xOSD_WIN_REG[0x0D]=0x35;xOSD_WIN_REG[0x0C]=0x7d;}
							break;
							
						case 4://left-top
							if(xEEPROMBuffer[PIPSIZE_buf]) {xOSD_WIN_REG[0x0D]=0x0E;xOSD_WIN_REG[0x0C]=0xEB;}
							else 			{xOSD_WIN_REG[0x0D]=0x35;xOSD_WIN_REG[0x0C]=0xEB;}
							break;
					}
					#elif defined(XGA_Panel)//SVGA panel은 PIP화면과 연동하게 이동하지 않고 Right-Top으로 한다.
					xOSD_WIN_REG[0x0D]=0x69;//Right-Top
					xOSD_WIN_REG[0x0C]=0x86;		
					#elif defined(SVGA_Panel)//SVGA panel은 PIP화면과 연동하게 이동하지 않고 Right-Top으로 한다.
					xOSD_WIN_REG[0x0D]=0x69;//Right-Top
					xOSD_WIN_REG[0x0C]=0x86;		
					#endif
					break;
					
				default:
					#if defined(SXGA_Panel)
					xOSD_WIN_REG[0x0D]=0xB0;//Right-Top//0xEF, 0xB0
					xOSD_WIN_REG[0x0C]=0;//0xEF;	
					#elif defined(XGA_Panel)
					xOSD_WIN_REG[0x0D]=0x69;//Right-Top
					xOSD_WIN_REG[0x0C]=0x86;			
					#elif defined(SVGA_Panel)
					xOSD_WIN_REG[0x0D]=0x69;//Right-Top
					xOSD_WIN_REG[0x0C]=0x86;		
					#endif
					break;
		
			}
			*/
			
			//OSD색깔정리.
			//green (메모리된채널)
			//yellow (메모리안된채널),,,
			DisplayWindow();
			if(SubWindowMsgFlag==0) DisplayMenuWindow();//Displaycharacter();

			SubWindowMsgFlag=1;	//2003-10-17

//test2004-06-23			OSDstatus = NowStatusDisplay;
//test2004-06-23			Osd_onoff();

			OSDofftimer = 5*200;//5sec
			OSDstatus = OSDexpire_timer;
			MENUstatus = TVchannelDisplay;
			break;
		
		case	AutoSearchChannelDisplay:
			
			OSDcharacters = AutoSearchChannelChars;
			DisplayMenuWindow();//Displaycharacter();
			
			OSDofftimer = (WORD)xEEPROMBuffer[OSDOFFTIME_buf]*200;
			OSDstatus = OSDexpire_timer;
			MENUstatus = Cursermove;
			break;
		
		case	SearchingDisplay:
			
			OSDcharacters = AutoChannelChars;//searching, press select to stop
			DisplayMenuWindow();//Displaycharacter();
			
			OSDofftimer = (WORD)xEEPROMBuffer[OSDOFFTIME_buf]*200;
			OSDstatus = OSDexpire_timer;
			MENUstatus = Cursermove;
			break;
			
		case	NowStatusDisplay:					//모드변경마다 우측상단에 상황표를 띄운다.
	
			OSDstatus = OsdRamClear;
			Osd_onoff();
		
//		OsdAllAttrClear();//test2004-07-07
//		OsdDataClear();

			NowTopOsdOn = 0;
			DelayNOP10();
			
		 if( (CurrentFunction!=PipRnT_mode)||(CurrentFunction!=PipRnC_mode)||(CurrentFunction!=PipRnS_mode) )
		 {
		 		xOSD_WIN_REG[0x0D]=80;//180;//H	//Av1/2로 표시할때...
				//xOSD_WIN_REG[0x0D]=0x40;//H		//Composite/S-video로 표시할때..(가로확대시..)
				xOSD_WIN_REG[0x0C]=0;//V
			}
			
			DisplayWindow();
			if(CurrentFunction!=PipRnT_mode)	DisplayMenuWindow();		//현재상태표시

			//OSDstatus = NowStatusDisplay;
			//Osd_onoff();
			xOSDW_OPTION[1]=0x80|0x40;
			
			OSDofftimer = 3*200;//3sec!
			if(PowerOnsequence>=BeforeNoVideoScalerInit) OSDstatus = OSDwait;//No-video status OSD never stop
			else OSDstatus = OSDexpire_timer;

			MENUstatus = NowStatusDisplay;
			break;
			
		case	OSDoff:
			
//			OSDSelKeyin=0;			//OFF하면서 OSD관련 clear!!
			//OsdGrade = 0;
			Osd_onoff();
			OSDstatus = OSDwait;
			MENUstatus = NotBUSY;
			ArrangeFunctionTable();		//osd를 off하면서 현재 모드(기능)를 CurrentFunction에 넣어둔다.
			NowTopOsdOn = 0;
			//SubWindowMsgFlag=0;

			if(PowerOnsequence==NoVideoStatus) //recall
			{
				OSDWindows = AnalogSubwindow;
				switch(CurrentFunction)
				{
					case 2://composite
						OSDcharacters = CompositeSubChars;
						break;
					case 3://s-video
						OSDcharacters = S_videoSubChars;
						break;
					
					#if defined(USE_SCART)	
					case Scart_mode:  //SCART
						OSDcharacters = ScartSubChars;
						break;
					#endif
				}
				OSDstatus = NowStatusDisplay;
			}
			else
			{
				//MUTE일 경우 MUTE recall	
				if(SoundMuteOnFlag)
				{
//					OSDSelKeyin=0;
					OSDWindows = MuteWindow;
					//OSDcharacters = MuteChars;
					OSDcharacters = CompositeSubChars;
					OSDstatus = MuteDisplay;
				}
			}
			AutoToggle=1;
			break;
		
		case	OsdRamClear:
			
			Osd_onoff();
			NowTopOsdOn = 0;
			OSDstatus = OSDwait;
			MENUstatus = NotBUSY;
			break;
		
		case	CheckCableDisplay:
			
			OSDstatus = OsdRamClear;				//RamClear -> window -> char(NO SIGNAL) Display
			Osd_onoff();
			DelayNOP10();
			
			#if defined(SXGA_Panel)
			xOSD_WIN_REG[0x0D]=0x47;//H
			xOSD_WIN_REG[0x0C]=0x6c;//Y
			#elif defined(WXGA_Panel)  
			xOSD_WIN_REG[0x0D]=0x48;//H
			xOSD_WIN_REG[0x0C]=0x4f;//V
			#elif defined(XGA_Panel)
			xOSD_WIN_REG[0x0D]=0x1F;//H
			xOSD_WIN_REG[0x0C]=0x3C;//Y
			#elif defined(SVGA_Panel)
			xOSD_WIN_REG[0x0D]=0x1F;//H
			xOSD_WIN_REG[0x0C]=0x3C;//Y
			#endif
						
			DisplayWindow();
			DisplayMenuWindow();
			OSDstatus = Nosignal_Display;
			Osd_onoff();
			OSDstatus = OSDwait;//never stop
			MENUstatus = Nosignal_Display;
			break;
			
		case	Nosignal_Display:
			
			OSDstatus = OsdRamClear;				//RamClear -> window -> char(NO SIGNAL) Display
			Osd_onoff();
			DelayNOP10();
			
			if(CurrentFunction==2||CurrentFunction==3)
			{
				#if defined(SXGA_Panel)
				xOSD_WIN_REG[0x0D]=0xA6;//Right-Top
				xOSD_WIN_REG[0x0C]=0xFB;
				#elif defined(WXGA_Panel)  
				xOSD_WIN_REG[0x0D]=0x48;//H
				xOSD_WIN_REG[0x0C]=0x4f;//V
				#elif defined(XGA_Panel)
				xOSD_WIN_REG[0x0D]=0x59;//Right-Top
				xOSD_WIN_REG[0x0C]=0x95;
				#elif defined(SVGA_Panel)
				xOSD_WIN_REG[0x0D]=0x59;//Right-Top
				xOSD_WIN_REG[0x0C]=0x95;
				#endif
				}
			else
			{
				#if defined(SXGA_Panel)
				xOSD_WIN_REG[0x0D]=0x47;//H
				xOSD_WIN_REG[0x0C]=0x6c;//Y
				#elif defined(WXGA_Panel)  
				xOSD_WIN_REG[0x0D]=0x48;//H
				xOSD_WIN_REG[0x0C]=0x4f;//V
				#elif defined(XGA_Panel)
				xOSD_WIN_REG[0x0D]=0x1F;//H
				xOSD_WIN_REG[0x0C]=0x3C;//Y
				#elif defined(SVGA_Panel)
				xOSD_WIN_REG[0x0D]=0x1F;//H
				xOSD_WIN_REG[0x0C]=0x3C;//Y
				#endif
			}
			
			
			DisplayWindow();
			DisplayMenuWindow();
			OSDstatus = Nosignal_Display;
			Osd_onoff();
			OSDstatus = OSDwait;//never stop
			
			SubWindowMsgFlag=1;
			MENUstatus = Nosignal_Display;
			break;
		
		case	OSDexpire_timer:
			#ifndef TestOsdAlwayOn	//test를 위해..
			if(OSDofftimer==0) 
			{
				OSDstatus = OSDoff;
				SubWindowMsgFlag=0;
			}
			#endif
			//SubWindowMsgFlag=0;//2003-10-06
			break;
		
		default:
			break;
	}
//	PreOSDstatus = OSDstatus;	// smpark 20030818

}

void AutoChannelDisplay()
{
	OSD230SeqSend(ATTR_ROW3,CII_COL14,OSD_BLACK,3);
	OSD230RowSend(DSP_ROW3);
	OSD230ColSend(CII_COL14);
			
//test2004-07-08	TVParameterInit();	//2003-12-26
	calToCharChannel(SearchChannel_Count+CHANNEL_MIN);
	DisplayInfo(3);	// display
}	

void	SaveColorTemp(void)	//2003-08-07
{
	EepromSetQue(ADCREDGAIN_adr,xEEPROMBuffer[ADCREDGAIN_buf]);
	EepromSetQue(ADCGREENGAIN_adr,xEEPROMBuffer[ADCGREENGAIN_buf]);
	EepromSetQue(ADCBLUEGAIN_adr,xEEPROMBuffer[ADCBLUEGAIN_buf]);

	xEEPROMBuffer[ColorTemp]=CT_USER;
	EepromSetQue(ColorTemp_addr,xEEPROMBuffer[ColorTemp]);
}

void PutData(void)
{
	//BYTE temp0;
	
	if( (NowTopOsdOn&&(OsdGrade==1 || OsdGrade==2))
		&&(xEEPROMBuffer[MainSubInputSource]!=10)&&(xEEPROMBuffer[MainSubInputSource]!=14)&&(xEEPROMBuffer[MainSubInputSource]!=18) )
	{	// PC mode
		switch(MenuNum)
		{
			case 	menu_brightness:
				xEEPROMBuffer[ANALOGBRT_buf] = MenuVal;
				#ifdef	InvertValueSlope
					//InvertPWM(0xfc - (xEEPROMBuffer[ANALOGBRT_buf]*2.8));
					InvertPWM(0xff - (xEEPROMBuffer[ANALOGBRT_buf]*2.55));
				#else
					InvertPWM(0x3f - xEEPROMBuffer[ANALOGBRT_buf]);
				#endif
				
				//WriteScaler(0x65,value);	//r
				//WriteScaler(0x66,value);	//g
				//WriteScaler(0x67,value);	//b
				EepromSetQue(ANALOGBRT_adr,xEEPROMBuffer[ANALOGBRT_buf]);
				break;

			case	menu_contrast:
				xEEPROMBuffer[ANALOGCONT]=MenuVal;
				#if defined(EMH1A)
					WriteScaler(0x62,xEEPROMBuffer[ANALOGCONT]|0x80);	//contrast apply!
					WriteScaler(0x63,xEEPROMBuffer[ANALOGCONT]);
					WriteScaler(0x64,xEEPROMBuffer[ANALOGCONT]);
				#elif defined(EMH2)
					#ifdef WXGA_Panel
					//WriteScaler(0x62,xEEPROMBuffer[ANALOGCONT]+0x9b);		//contrast apply!
					//WriteScaler(0x63,xEEPROMBuffer[ANALOGCONT]+0x9b);
					//WriteScaler(0x64,xEEPROMBuffer[ANALOGCONT]+0x9b);
					////WriteScaler(0x62,0x80+(100-xEEPROMBuffer[ANALOGCONT]));		//contrast apply!
					////WriteScaler(0x63,0x80+(100-xEEPROMBuffer[ANALOGCONT]));
					////WriteScaler(0x64,0x80+(100-xEEPROMBuffer[ANALOGCONT]));
					if( (0xff-xEEPROMBuffer[ANALOGCONT]*1.54) >= 128)
					{
						WriteScaler(0x62,(0xff-xEEPROMBuffer[ANALOGCONT]*1.54));		//contrast apply!
						WriteScaler(0x63,(0xff-xEEPROMBuffer[ANALOGCONT]*1.54));
						WriteScaler(0x64,(0xff-xEEPROMBuffer[ANALOGCONT]*1.54));
					}
					else
					{
						WriteScaler(0x62,(xEEPROMBuffer[ANALOGCONT]*1.54)-(54+73));		//contrast apply!
						WriteScaler(0x63,(xEEPROMBuffer[ANALOGCONT]*1.54)-(54+73));
						WriteScaler(0x64,(xEEPROMBuffer[ANALOGCONT]*1.54)-(54+73));
					}					

					#else
					WriteScaler(0x62,xEEPROMBuffer[ANALOGCONT]);		//contrast apply!
					WriteScaler(0x63,xEEPROMBuffer[ANALOGCONT]);
					WriteScaler(0x64,xEEPROMBuffer[ANALOGCONT]);
					#endif
				#else
					WriteScaler(0x62,xEEPROMBuffer[ANALOGCONT]|0x80);	//contrast apply!
					WriteScaler(0x63,xEEPROMBuffer[ANALOGCONT]);
					WriteScaler(0x64,xEEPROMBuffer[ANALOGCONT]);
				#endif
				
				EepromSetQue(ANALOGCONT_adr,xEEPROMBuffer[ANALOGCONT]);
				break;

			case	menu_sharpness:
				xEEPROMBuffer[Sharpness_buf] = MenuVal;
				WriteScaler(0x6b,xEEPROMBuffer[Sharpness_buf]|0x80);
				EepromSetQue(Sharpness_adr,xEEPROMBuffer[Sharpness_buf]);
				break;
			
			case	menu_phase:
				PhaseValue=MenuVal;
				SetADCPhaseReg(PhaseValue);
				EepromSetQue(CurrentMode*4+3,PhaseValue);
				break;			
			
			case	menu_clock:
				ClockValue=MenuVal;
				ADCPLL = ModeList[CurrentMode].HTotal+ClockValue-0x80;
				SetADCHtotal(ADCPLL-1);
				EepromSetQue(CurrentMode*4+2,ClockValue);
				break;
				
			case	menu_Hposition:
				HorizontalValue=MenuVal;
				//WordWriteScaler(0x02,(ModeList[CurrentMode].IHAS+HorizontalValue))-0x80);
				WordWriteScaler(0x02, ModeList[CurrentMode].IHAS+0x80-HorizontalValue);	//2003-05-30 
				EepromSetQue(CurrentMode*4+0,HorizontalValue);
				break;
				
			case	menu_Vposition:
				VerticalValue=MenuVal;
				WordWriteScaler(0x06,VerticalValue);
				WordWriteScaler(0x08,VerticalValue);
				EepromSetQue(CurrentMode*4+1,VerticalValue);
				break;

        	case	menu_white_balance:
				xEEPROMBuffer[WhiteBlc_buf] = MenuVal;
				//ADC brightness
				SetADCBias(0x64-xEEPROMBuffer[WhiteBlc_buf],0x64-xEEPROMBuffer[WhiteBlc_buf],0x64-xEEPROMBuffer[WhiteBlc_buf]);
				EepromSetQue(WhiteBlc_adr,xEEPROMBuffer[WhiteBlc_buf]);
				break;
			
			case	menu_Rgain:			
				xEEPROMBuffer[ADCREDGAIN_buf]=MenuVal-ADCREDGAIN_offset;
				
				#ifdef	AdcGainSlope
					//WriteI2C(ADC_sysaddress,0x08,(0xfc-(xEEPROMBuffer[ADCREDGAIN_buf]*3.6)));
					WriteI2C(ADC_sysaddress,0x08,(0xff-(xEEPROMBuffer[ADCREDGAIN_buf]*2.55)));
				#else
					WriteI2C(ADC_sysaddress,0x08,(0xff-xEEPROMBuffer[ADCREDGAIN_buf]));
				#endif

				if(xEEPROMBuffer[ColorTemp]!=CT_USER)
				{
					SaveColorTemp();
					ColorTempFunc();
				}	
				else	EepromSetQue(ADCREDGAIN_adr,xEEPROMBuffer[ADCREDGAIN_buf]);
				break;
			
			case	menu_Ggain:			
				xEEPROMBuffer[ADCGREENGAIN_buf]=MenuVal-ADCREDGAIN_offset;
				#ifdef	AdcGainSlope
					//WriteI2C(ADC_sysaddress,0x09,(0xfc-(xEEPROMBuffer[ADCGREENGAIN_buf]*3.6)));
					WriteI2C(ADC_sysaddress,0x09,(0xff-(xEEPROMBuffer[ADCGREENGAIN_buf]*2.55)));
				#else
					WriteI2C(ADC_sysaddress,0x09,(0xff-xEEPROMBuffer[ADCGREENGAIN_buf]));
				#endif
				
				if(xEEPROMBuffer[ColorTemp]!=CT_USER)
				{
					SaveColorTemp();
					ColorTempFunc();
				}	
				else	EepromSetQue(ADCGREENGAIN_adr,xEEPROMBuffer[ADCGREENGAIN_buf]);
				break;

			case	menu_Bgain:			
				xEEPROMBuffer[ADCBLUEGAIN_buf]=MenuVal-ADCREDGAIN_offset;
				#ifdef	AdcGainSlope
					//WriteI2C(ADC_sysaddress,0x0a,(0xfc-(xEEPROMBuffer[ADCBLUEGAIN_buf]*3.6)));
					WriteI2C(ADC_sysaddress,0x0a,(0xff-(xEEPROMBuffer[ADCBLUEGAIN_buf]*2.55)));
				#else
					WriteI2C(ADC_sysaddress,0x0a,(0xff-xEEPROMBuffer[ADCBLUEGAIN_buf]));
				#endif
				
				if(xEEPROMBuffer[ColorTemp]!=CT_USER)
				{
					SaveColorTemp();
					ColorTempFunc();
				}	
				else	EepromSetQue(ADCBLUEGAIN_adr,xEEPROMBuffer[ADCBLUEGAIN_buf]);
				break;
				
			case	menu_color_temperture:
				xEEPROMBuffer[ColorTemp]=MenuVal;
				
				switch(xEEPROMBuffer[ColorTemp])
				{
					case CT_WARM:
						xEEPROMBuffer[ADCREDGAIN_buf]	=55;//52;
						xEEPROMBuffer[ADCGREENGAIN_buf]	=50;//43;
						xEEPROMBuffer[ADCBLUEGAIN_buf]	=50;//21;
						break;
                        	
	                case CT_STANDARD:
						xEEPROMBuffer[ADCREDGAIN_buf]	=50;
						xEEPROMBuffer[ADCGREENGAIN_buf]	=50;
						xEEPROMBuffer[ADCBLUEGAIN_buf]	=50;
						break;
				
					case CT_COOL:
						xEEPROMBuffer[ADCREDGAIN_buf]	=50;//42;
						xEEPROMBuffer[ADCGREENGAIN_buf]	=50;//53;
						xEEPROMBuffer[ADCBLUEGAIN_buf]	=55;//35;
						break;
					
					case CT_USER:
					default:
						xEEPROMBuffer[ADCREDGAIN_buf]	=EEPROM_Read(ADCREDGAIN_adr);
						xEEPROMBuffer[ADCGREENGAIN_buf]	=EEPROM_Read(ADCGREENGAIN_adr);
						xEEPROMBuffer[ADCBLUEGAIN_buf]	=EEPROM_Read(ADCBLUEGAIN_adr);
						break;
					
				}

				//SetADCGain(xEEPROMBuffer[ADCREDGAIN_buf],xEEPROMBuffer[ADCGREENGAIN_buf],xEEPROMBuffer[ADCBLUEGAIN_buf]);
				WriteI2C(ADC_sysaddress,0x08,(0xff-(xEEPROMBuffer[ADCREDGAIN_buf]*2.55)));	//ADC contrast
				WriteI2C(ADC_sysaddress,0x09,(0xff-(xEEPROMBuffer[ADCGREENGAIN_buf]*2.55)));
				WriteI2C(ADC_sysaddress,0x0a,(0xff-(xEEPROMBuffer[ADCBLUEGAIN_buf]*2.55)));

				EepromSetQue(ColorTemp_addr,xEEPROMBuffer[ColorTemp]);
				
				MenuBarValue();
				break;

			case	menu_language:
				xEEPROMBuffer[LANGUAGE_buf]=MenuVal;
				//xEEPROMBuffer[LANGUAGE_buf]=0;//임시 변경 //2003-12-24 1:55오후
	
				switch(xEEPROMBuffer[LANGUAGE_buf])
				{
				  #if defined (USE_NTSCtuner)
							// cahr. 가운데 정렬
			 		case English:
			 		EepromSetQue(LANGUAGE_adr,xEEPROMBuffer[LANGUAGE_buf]);
			 		break;
			         	case Korea:
			 		EepromSetQue(LANGUAGE_adr,xEEPROMBuffer[LANGUAGE_buf]);
			 		break;
			 		case Japan:
			 		EepromSetQue(LANGUAGE_adr,xEEPROMBuffer[LANGUAGE_buf]);
			 		break;
			 	  #elif defined (USE_PALSECAMtuner)
					case English:
        			//	case France:
				//	case German:
				//	case Italia:
				//	case Netherlands:
				//	case Russia:
					case China:
						EepromSetQue(LANGUAGE_adr,xEEPROMBuffer[LANGUAGE_buf]);
						break;	
			 		

			 	  #endif
			 	}
				break;

			case	menu_osd_Hposition:
				xEEPROMBuffer[OSDHPOSITION_buf]=MenuVal;
				EepromSetQue(OSDHPOSITION_adr,xEEPROMBuffer[OSDHPOSITION_buf]);
				
				if((MenuVal%5==1)||(MenuVal==OSDHpos_min))
				{
					#ifdef WXGA_Panel
					xOSD_WIN_REG[0x0D]=xEEPROMBuffer[OSDHPOSITION_buf]+1;//H	//외부
					OSDSeqSend(IN_ATTR_ROW15,IN_CII_COL15,(4+(xEEPROMBuffer[OSDHPOSITION_buf]/5)*3),1);//horizontal //내부
					#else
					xOSD_WIN_REG[0x0D]=xEEPROMBuffer[OSDHPOSITION_buf];//H	//외부
					OSDSeqSend(IN_ATTR_ROW15,IN_CII_COL15,(4+(xEEPROMBuffer[OSDHPOSITION_buf]/5)*3),1);//horizontal //내부
					#endif
				}
				break;

			case	menu_osd_Vposition:		
				xEEPROMBuffer[OSDVPOSITION_buf]=MenuVal;
				xOSD_WIN_REG[0x0C]=xEEPROMBuffer[OSDVPOSITION_buf];//V
				EepromSetQue(OSDVPOSITION_adr,xEEPROMBuffer[OSDVPOSITION_buf]);
				
				OSDSeqSend(IN_ATTR_ROW15,IN_CII_COL14,xEEPROMBuffer[OSDVPOSITION_buf]-1,1);//vertical
				break;

			case	menu_osd_time:
				xEEPROMBuffer[OSDOFFTIME_buf]=MenuVal;
				OSDofftimer = (WORD)xEEPROMBuffer[OSDOFFTIME_buf]*200;//5ms timing일때...(초->ms)
				EepromSetQue(OSDOFFTIME_adr,xEEPROMBuffer[OSDOFFTIME_buf]);
				break;

			case	menu_osd_transparency:
				TransparencyOnfFlag=MenuVal;
				
				//EepromSetQue(ANALOGCONT_adr,xEEPROMBuffer[ANALOGCONT]);
				break;
                        	
			case	menu_pip_enable:	// PIPEN_SOURCE_buf of high bit
				PipOnOffFlag=MenuVal;
				//PipOnOffFlag=1;
				xEEPROMBuffer[PIPEN_SOURCE_buf]= ( (((BYTE)PipOnOffFlag&0x01)<<4)&0xf0 +(xEEPROMBuffer[PIPEN_SOURCE_buf]&0x0f) );
				EepromSetQue(PIPEN_SOURCE_adr,xEEPROMBuffer[PIPEN_SOURCE_buf]);
				break;
				
			case	menu_pip_source:  	// PIPEN_SOURCE_buf of low bit
				PipInputSource=MenuVal;
				xEEPROMBuffer[PIPEN_SOURCE_buf]= ( (PipInputSource&0x03) + (xEEPROMBuffer[PIPEN_SOURCE_buf]&0xf0) );
				EepromSetQue(PIPEN_SOURCE_adr,xEEPROMBuffer[PIPEN_SOURCE_buf]);
				break;
				
			case	menu_pip_size:		// PIPSIZE_buf of low_bit
				PipSizeNum=MenuVal;
				xEEPROMBuffer[PIPSIZE_buf]= ( (PipSizeNum&0x03) | (xEEPROMBuffer[PIPSIZE_buf]&0xf0) );
				EepromSetQue(PIPSIZE_adr,xEEPROMBuffer[PIPSIZE_buf]);
				break;
				
			case	menu_pip_AspectRatio:  	// PIPSIZE_buf of high_bit
				PipAspectFlag=MenuVal;
				//xEEPROMBuffer[PIPSIZE_buf]= ( (PipSizeNum&0x03)+((BYTE)PipAspectFlag&0x01<<4) );
				
				xEEPROMBuffer[PIPSIZE_buf]= ( ((BYTE)PipAspectFlag&0x01<<4) + (PipSizeNum&0x03) );
				//xEEPROMBuffer[PIPSIZE_buf]= ( ((BYTE)PipAspectFlag&0x01)<<4 + (PipSizeNum&0x03) );
				//PipAspectSelService();

				EepromSetQue(PIPSIZE_adr,xEEPROMBuffer[PIPSIZE_buf]);
				break; 
				
			case	menu_pip_blend:  	// PIP blending
				PipBlendNum=MenuVal;
				xEEPROMBuffer[PIPBLEND_buf]=PipBlendNum;
				EepromSetQue(PIPBLEND_adr,xEEPROMBuffer[PIPBLEND_buf]);
				break; 
				
			case	menu_pip_Hposition:

				#if 1
					PipHPositionNum=MenuVal;
					xEEPROMBuffer[PIPPOSITION]= ( ((PipHPositionNum&0x03)<<4)+(PipVPositionNum&0x03) );
					PipPositionService();
					EepromSetQue(PIPPOSITION_adr,xEEPROMBuffer[PIPPOSITION]);
				#else	//test

					PipHPositionNum=WordMenuVal;
					xEEPROMBuffer[0x38]= PipHPositionNum;		//low nibble
					xEEPROMBuffer[0x39]= PipHPositionNum>>4;	//high nibble
					PipPositionService();
					EepromSetQue(PIPH0POSITION_adr,xEEPROMBuffer[0x38]);
					EepromSetQue(PIPH1POSITION_adr,xEEPROMBuffer[0x39]);
				#endif
				break;             
			
			case	menu_pip_Vposition:   

				#if 1
					PipVPositionNum=MenuVal;
					xEEPROMBuffer[PIPPOSITION]= ( ((PipHPositionNum&0x03)<<4)+(PipVPositionNum&0x03) );
					PipPositionService();
					EepromSetQue(PIPPOSITION_adr,xEEPROMBuffer[PIPPOSITION]);
				#else	//test


 					PipVPositionNum=WordMenuVal;
					xEEPROMBuffer[0x3a]=PipVPositionNum;
					xEEPROMBuffer[0x3b]=PipVPositionNum>>4;
					PipPositionService();
					EepromSetQue(PIPV0POSITION_adr,xEEPROMBuffer[0x3a]);
					EepromSetQue(PIPV1POSITION_adr,xEEPROMBuffer[0x3b]);


				#endif
				break;             
			                           
			case	menu_auto_adjust:  
				AutoFlag=MenuVal;
				break;             
			
			case	menu_factory_default:
				FactoryDftFlag=MenuVal;
				xEEPROMBuffer[FactoryReset_buf]=FactoryDftFlag;//test
				EepromSetQue(FactoryReset_adr,xEEPROMBuffer[FactoryReset_buf]);
				break;

			case	menu_dosmode:	//2003-08-26
				//DosmodeFlag=MenuVal;
				DosmodeFlag ^= 1;
				xEEPROMBuffer[Dosmode_buf]=DosmodeFlag;
				EepromSetQue(Dosmode_adr,xEEPROMBuffer[Dosmode_buf]);
				break;
			#ifdef Wide4_3Aspect			
			case	menu_AspectRatio:
				AspectFlag=MenuVal;
				xEEPROMBuffer[Aspect_buf]=AspectFlag;
				EepromSetQue(Aspect_adr,xEEPROMBuffer[Aspect_buf]);
				break;
			#endif
			
			// added by smpark 20030721
			case  menu_Treble:
				xEEPROMBuffer[TREBLE] = MenuVal;
				SoundSetTreble();
				if(xEEPROMBuffer[SSC]!=SSCUser) 
				{
					SaveCurrentSSCToUser();
					SmartSoundCtrFunc();
				}
				else EepromSetQue(TREBLE_adr,xEEPROMBuffer[TREBLE]); 
				break;

     			case menu_Bass:
				xEEPROMBuffer[BASS] = MenuVal;
				SoundSetBass();
				if(xEEPROMBuffer[SSC]!=SSCUser) 
				{
					SaveCurrentSSCToUser();
					SmartSoundCtrFunc();
				}
				else 	EepromSetQue(BASS_adr,xEEPROMBuffer[BASS]);     				
     				break;

   			case menu_Loudness:
				xEEPROMBuffer[LOUDNESS] = MenuVal;
				SoundSetLoudness();
				if(xEEPROMBuffer[SSC]!=SSCUser) 
				{
					SaveCurrentSSCToUser();
					SmartSoundCtrFunc();
				}
				else EepromSetQue(LOUDNESS_adr,xEEPROMBuffer[LOUDNESS]);     	
				break;

   			case menu_SSC:
				xEEPROMBuffer[SSC]=MenuVal;
				EepromSetQue(SSC_adr, MenuVal);
				SoundSet();	//smpark20030721  		
				MenuBarValue();	//2003-08-07
     				break;

			default:
				//LED_OFF;//test
				//power_onoff();
				break;

		}	
		
		
	}
	#ifdef Ccd_Vchip
	else if( (NowTopOsdOn&&(OsdGrade==1 || OsdGrade==2 ||(TvMenuNum==tvmenu_Ccd&&OsdGrade==3)))
	#else
	else if( (NowTopOsdOn&&(OsdGrade==1 || OsdGrade==2) )
	#endif
		&&((xEEPROMBuffer[MainSubInputSource]==10)||(xEEPROMBuffer[MainSubInputSource]==14)||(xEEPROMBuffer[MainSubInputSource]==18)) )
	{	// video mode
		switch(TvMenuNum)
		{
			case tvmenu_brightness:
				xEEPROMBuffer[COMPOSITEBRT_buf] = MenuVal;
			 	SetAV_Brightness();				
				if(xEEPROMBuffer[SmartPicCtr_buf]!=SPCUser) {
					SaveCurrentColorToUser();
					SmartPicCtrFunc();	}
				else EepromSetQue(COMPOSITEBRT_adr,xEEPROMBuffer[COMPOSITEBRT_buf]);
				break;	

			case tvmenu_contrast:
				xEEPROMBuffer[COMPOSITECONT] = MenuVal;
				SetAV_Contrast();
				if(xEEPROMBuffer[SmartPicCtr_buf]!=SPCUser) 
				{
					SaveCurrentColorToUser();
					SmartPicCtrFunc();	
				}
				else EepromSetQue(COMPOSITECONT_adr,xEEPROMBuffer[COMPOSITECONT]);				
				break;  	

			case tvmenu_sharpness:
				xEEPROMBuffer[AVSharpness] = MenuVal;
				
				#if defined(SAA7114)
				WriteI2C(SAA7114_sysaddress,0x09,0x40|xEEPROMBuffer[AVSharpness]);
				#elif defined(SAA7115)
				WriteI2C(SAA7115_sysaddress,0x09,0x40|xEEPROMBuffer[AVSharpness]);
				#elif defined(TW9908)
				SetAV_Sharpness();
				#endif
				if(xEEPROMBuffer[SmartPicCtr_buf]!=SPCUser) {
					SaveCurrentColorToUser();
					SmartPicCtrFunc();	}
				else EepromSetQue(COMPOSITESHARP_adr,xEEPROMBuffer[AVSharpness]);
				break; 	

			case tvmenu_color:
				xEEPROMBuffer[AVCOLOR] = MenuVal;
				#if defined(SAA7114)
				WriteI2C(SAA7114_sysaddress,0x0C,xEEPROMBuffer[AVCOLOR]*2);//max 0x3F
				#elif defined(SAA7115)
				WriteI2C(SAA7115_sysaddress,0x0C,xEEPROMBuffer[AVCOLOR]*2);//max 0x3F
				#elif defined(VPC323x)
					#if defined(FPSTATUS_ReadOK)
					while(VPC323xBYTERead(0x35)&0x04);	//Busy? then wait!!
					#endif
				VPC323xFPWrite(0x30,2070+((int)xEEPROMBuffer[AVCOLOR]-0x80)*10);
				#elif defined(TW9908)
				SetAV_Saturation();	
				#endif
				if(xEEPROMBuffer[SmartPicCtr_buf]!=SPCUser) {
					SaveCurrentColorToUser();
					SmartPicCtrFunc();	}
				else EepromSetQue(COMPOSITECOLOR_adr,xEEPROMBuffer[AVCOLOR]);
				break;     	

			case tvmenu_tint:
				xEEPROMBuffer[AVTINT] = MenuVal;
				#if defined(TW9908)
				SetAV_Tint();
				#endif
				
				if(xEEPROMBuffer[SmartPicCtr_buf]!=SPCUser) {
					SaveCurrentColorToUser();
					SmartPicCtrFunc();	}
				else EepromSetQue(COMPOSITETINT_adr,xEEPROMBuffer[AVTINT]);
				break;      	
			                                
			case tvmenu_country:
				xEEPROMBuffer[SystemCountry]=MenuVal;
				break;	   
				
			case tvmenu_auto_setup:
				break;         
			
			case tvmenu_channel_edit:
				SoundMuteTvTimer=0;								
				TunerProcessing=1;
				EepromSetQue(CurrentChannel_adr,xEEPROMBuffer[CurrentChannel]);
				
				break;       
			
			#if defined (USE_NTSCtuner)
			case tvmenu_antena_input:
				//AntenaFlag=MenuVal;	//youngdo 2003.5.28
				CatvAirSelection(MenuVal);
				break;       
			#endif
			
			#ifdef	Ccd_Vchip
			case	tvmenu_Ccd:
				//CcdCaptionFlag = MenuVal;
				if(OsdGrade==3)
				{
				  switch(SubMenuVal)
				  {
					case 0:	xEEPROMBuffer[Ccd_buf]=(xEEPROMBuffer[Ccd_buf]&0xfe)|((BYTE)CcdCaptionFlag&0x01);
						break;
					case 1:	xEEPROMBuffer[Ccd_buf]=(xEEPROMBuffer[Ccd_buf]&0xfd)|((BYTE)CcdModeFlag&0x01)<<1;
						break;
					case 2:	xEEPROMBuffer[Ccd_buf]=(xEEPROMBuffer[Ccd_buf]&0xfb)|((BYTE)CcdChannelFlag&0x01)<<2;
						break;
					case 3:	xEEPROMBuffer[Ccd_buf]=(xEEPROMBuffer[Ccd_buf]&0xf7)|((BYTE)CcdFieldFlag&0x01)<<3;
						break;
					case 4:	xEEPROMBuffer[Ccd_buf]=(xEEPROMBuffer[Ccd_buf]&0xef)|((BYTE)CcdDisplayFlag&0x01)<<4;
						break;
				
				  }
				  
				}
				EepromSetQue(Ccd_adr,xEEPROMBuffer[Ccd_buf]);
				break;
		
			case	tvmenu_Vchip:
				break;
			#endif
			
			case tvmenu_finetune:
				xEEPROMBuffer[NTSC_AIRTVFine_buf]=MenuVal;
				SetFineTune(xEEPROMBuffer[CurrentChannel],MenuVal);
				SetFinePLL(xEEPROMBuffer[CurrentChannel],MenuVal);
				SetManualTune(xEEPROMBuffer[CurrentChannel]);
				break;
			case tvmenu_lang://tvmenu_ttx:
				xEEPROMBuffer[LANGUAGE_buf]=MenuVal;
				EepromSetQue(LANGUAGE_adr,xEEPROMBuffer[LANGUAGE_buf]);
				break;
							
			case tvmenu_blue_screen:
				xEEPROMBuffer[BscrFlag_buf]=MenuVal;
				SetBlueScrren(MenuVal);
				//if( MSP34xyDSPRead(0x11,0x7e)==0x0000 && xEEPROMBuffer[BscrFlag_buf]==1)
				
				{
				
					BYTE temp;
					temp=TW990xRead(0x01);

				if( ((((temp&0x68)==0x00)||(temp&0x80)==0x80)) && xEEPROMBuffer[BscrFlag_buf]==1 )
				{
						MSP34xyDSPWrite(0x10,0x0024,0x0000);	//Carrier Mute On
				}
				else	MSP34xyDSPWrite(0x10,0x0024,0x07ff);	//Carrier Mute Off
				
				}
				
				EepromSetQue(BscrFlag_adr, MenuVal);
				break;
				              
			case tvmenu_screen_mode:
				#if 0
				//xEEPROMBuffer[WideModeFlag_buf]=MenuVal;
				//EepromSetQue(WideModeFlag_adr, MenuVal);
				#endif
				DisplayAspectRatioNum=MenuVal;
				xEEPROMBuffer[DisplayAspcet_buf]= (DisplayAspectRatioNum&0x03)+(xEEPROMBuffer[DisplayAspcet_buf]&0xf0);
				EepromSetQue(DisplayAspcet_adr,xEEPROMBuffer[DisplayAspcet_buf]);
				break;  
				            
			case tvmenu_smart_picture_control:
				xEEPROMBuffer[SmartPicCtr_buf]=MenuVal;
				EepromSetQue(SmartPicCtr_adr, MenuVal);
				TVColorSet();
				TvMenuBarValue();	//2003-08-19
				break;
				    
			case tvmenu_sleep:
				xEEPROMBuffer[Sleep_buf]=MenuVal;
				SleepTimer=(xEEPROMBuffer[Sleep_buf])*step_1min;	//1분단위(6x10^4ms을 5ms마다 감소)//2003-07-31
				break;			
			
			
			#ifdef TempOsdMenu
			case	tvmenu_TempOsd:
				xEEPROMBuffer[TempOsd_buf]=MenuVal;//
				TempOsdNum = MenuVal;
				EepromSetQue(TempOsd_adr,xEEPROMBuffer[TempOsd_buf]);
				
				DisplayWindow();
				
				break;
				
			case	tvmenu_OsdBlend:
				xEEPROMBuffer[TempOsdBlend_buf]=MenuVal;//
				EepromSetQue(TempOsdBlend_adr,xEEPROMBuffer[TempOsdBlend_buf]);
				DisplayWindow();
				break;
				
			#endif
			
			
			#if 0
			case tvmenu_aspect:
				DisplayAspectRatioNum=MenuVal;
				xEEPROMBuffer[DisplayAspcet_buf]= (DisplayAspectRatioNum&0x03)+(xEEPROMBuffer[DisplayAspcet_buf]&0xf0);
				EepromSetQue(DisplayAspcet_adr,xEEPROMBuffer[DisplayAspcet_buf]);
				break;
			#endif
			
			// added by smpark 20030721
			case  tvmenu_Treble:
				xEEPROMBuffer[TREBLE] = MenuVal;
				// Tr control 추가
				SoundSetTreble()	;
				if(xEEPROMBuffer[SSC]!=SSCUser) {
					SaveCurrentSSCToUser();
					SmartSoundCtrFunc();
					}
				else EepromSetQue(TREBLE_adr,xEEPROMBuffer[TREBLE]);
				break;

     		case tvmenu_Bass:
				xEEPROMBuffer[BASS] = MenuVal;
				// Bass control //sm
				SoundSetBass();
				if(xEEPROMBuffer[SSC]!=SSCUser) {
					SaveCurrentSSCToUser();
					SmartSoundCtrFunc();
					}
				else EepromSetQue(BASS_adr,xEEPROMBuffer[BASS]);     				
     				break;

     		case tvmenu_Loudness:
				xEEPROMBuffer[LOUDNESS] = MenuVal;
				// Louddness control 추가
				SoundSetLoudness();
				if(xEEPROMBuffer[SSC]!=SSCUser) {
					SaveCurrentSSCToUser();
					SmartSoundCtrFunc();
					}
				else EepromSetQue(LOUDNESS_adr,xEEPROMBuffer[LOUDNESS]);     	
				break;

     		case tvmenu_SSC:
				xEEPROMBuffer[SSC]=MenuVal;
				EepromSetQue(SSC_adr, MenuVal);
				SoundSet();     		//smpark 20030722		
				TvMenuBarValue();	//2003-08-07
     				break;
		
			default:
				//LED_OFF;//test
		

				
//				power_onoff();
				break;
		}
	}			
	else
	{
		switch(OsdMode)
		{
			case volume_mode:
				xEEPROMBuffer[VOLUME_buf]=MenuVal;
				EepromSetQue(VOLUME_adr,xEEPROMBuffer[VOLUME_buf]);
				PutVolumePWM();
				break;

			default:
				//LED_OFF;//test
				//power_onoff();
				break;
			
		}
	}
}

//----------------------------------------------------------------------------------------
#ifndef ChannelDisplayDouble
//----------------------------------------------------------------------------------------
void ChannelOSD(BYTE HPos,  BYTE VPos )
{
	BYTE count=0, index=0;
	InitOsdRam();
	
	xOSDW_OPTION[1]=0x00;	
	
	xOSD_WIN_REG[0x0D]=HPos;
	xOSD_WIN_REG[0x0C]=VPos;
	xOSD_WIN_REG[0x0E] = 0x1f;//char bigger!!
	
	xOSDRA=DSP_ROW0;xOSDCA=CII_COL30;	//20030729
	
	if((OSDcharacters==PipRgbTunerChars)||(CurrentFunction==PipRnT_mode))			xOSDDT0=0x00;
	else			xOSDDT0=Vchar_dbl;			//세로확대만..
	
	
	// 채널 출력
	if(CheckChMask(xEEPROMBuffer[CurrentChannel])){
		OSD230SeqSend(ATTR_ROW0,CII_COL0,OSD_YELLOW,30);	//색깔
	}else{
		OSD230SeqSend(ATTR_ROW0,CII_COL0,OSD_GREEN,30);	//색깔
	}
	

	
	#if defined(USE_NTSCtuner)

		if(CheckChCATV(xEEPROMBuffer[CurrentChannel]))	//cable
		{			
			OSD230PtrSend(DSP_ROW0,CII_COL1,Catv[0],Catv_Sizeof[0]);

			if(RemoconDigit)	// 리모컨 숫자키
				count = calToChar(RecmoconTVchannel);	
			else 			// key 조작  
				count = calToChar( CalDispchannel());
		}
		else	//air
		{
			//OSD230PtrSend(DSP_ROW1,CII_COL1,Chdot[0],Chdot_Sizeof[0]);
			OSD230PtrSend(DSP_ROW0,CII_COL1,Chdot,sizeof(Chdot));
			if(RemoconDigit) 
				count = calToChar(RecmoconTVchannel);
			else 
				count = calToChar(CalDispchannel());
		}	
	#elif defined(USE_PALSECAMtuner)

		if(!SubWindowMsgFlag) OSD230PtrSend(DSP_ROW0,CII_COL1,Chdot,sizeof(Chdot));
		if(SubWindowMsgFlag)	OSD230PtrSend(DSP_ROW0,CII_COL1,Chdot,sizeof(Chdot));
		
		ChdotDisplayFlag=1;
		
		if(RemoconDigit) 
			count = calToChar(RecmoconTVchannel);
		else 
			count = calToChar(CalDispchannel());

	#endif



	// 숫자 출력
	OSD230DataSend(0x00);
	HighOSDArea=0;//Low Display data.
	index = 0;
	while(count--){
		OSD230DataSend(CalBuffer[index]+0x01);
		index++;
	}

	if(OSDcharacters!=ChannelOnlyNumber) return;

	// remocon text 출력 
	#if defined(USE_remocon)
		#if defined(USE_NTSCtuner)
			if(CheckChCATV(xEEPROMBuffer[CurrentChannel]))				
			{
	//			OSD230SeqSend(ATTR_ROW1,CII_COL0,OSD_GREEN,30);	//색깔
				if(ThreeDigit)
				{
					if(ReceiveRemoconCount==1){
						OSD230DataSend(_minus);
						OSD230DataSend(_minus);
					}else if(ReceiveRemoconCount==2){
						OSD230DataSend(_minus);
					}
				}else
				{
					if(ReceiveRemoconCount==1) OSD230DataSend(_minus);
				}
			}else{
				if(ReceiveRemoconCount==1) OSD230DataSend(_minus);
			}
		#else		
			/*
			//if(ReceiveRemoconCount==1&&RecmoconTVchannel<2)
			//{
				//OSD230DataSend(_minus);
				//OSD230DataSend(_minus);
			//}
			//else if(ReceiveRemoconCount==1&&RecmoconTVchannel>1) OSD230DataSend(_minus);
			*/
			if(!ThreeDigit&&ReceiveRemoconCount==1)	OSD230DataSend(_minus);
		#endif
	#endif

	xOSDW_OPTION[1]=0x00|0x80|0x40; 	// smpark 20030818

}
//----------------------------------------------------------------------------------------
#else
//----------------------------------------------------------------------------------------
void ChannelOSD(BYTE HPos,  BYTE VPos )
{
	BYTE count=0, index=0;
	InitOsdRam();

	//xOSD_WIN_REG[0x0D]=66;		//H position
	//xOSD_WIN_REG[0x0C]=1;		//V position
	xOSD_WIN_REG[0x0D]=HPos;
	xOSD_WIN_REG[0x0C]=VPos;
	xOSD_WIN_REG[0x0E] = 0x1f;		//char hight
	xOSDRA=DSP_ROW0;xOSDCA=CII_COL30;
	//xOSDDT0=HVchar_dbl;			//가로,세로 2배 확대
	xOSDDT0=Vchar_dbl;	
	

	// 채널 출력

	if(CheckChMask(xEEPROMBuffer[CurrentChannel]))	OSD230SeqSend(ATTR_ROW0,CII_COL0,OSD_YELLOW,30);	//색깔
	else						OSD230SeqSend(ATTR_ROW0,CII_COL0,OSD_GREEN,30);		//색깔
	
	#if defined(USE_NTSCtuner)
		if(CheckChCATV(xEEPROMBuffer[CurrentChannel]))	//cable
		{			
			//OSD230PtrSend(DSP_ROW1,CII_COL0,Catv[xEEPROMBuffer[LANGUAGE_buf]],Catv_Sizeof[xEEPROMBuffer[LANGUAGE_buf]]);
			OSD230PtrSend(DSP_ROW0,CII_COL0,Catv2[0],Catv2_Sizeof[0]);
			if(OSDcharacters==ChannelNumChars) 		count = calToChar( CalDispchannel());
			else if(OSDcharacters==ChannelOnlyNumber) 	count = calToChar(RecmoconTVchannel);
		}
		else	//air
		{
			OSD230PtrSend(DSP_ROW0,CII_COL4,Chdot2[0],Chdot2_Sizeof[0]);
			if(OSDcharacters==ChannelNumChars) 		count = calToChar(CalDispchannel());
			else if(OSDcharacters==ChannelOnlyNumber) 	count = calToChar(RecmoconTVchannel);
		}				
	#elif defined(USE_PALSECAMtuner)
		OSD230PtrSend(DSP_ROW0,CII_COL0,Chdot2[0]+4,Chdot2_Sizeof[0]);
		if(OSDcharacters==ChannelNumChars) 		count = calToChar(CalDispchannel());
		else if(OSDcharacters==ChannelOnlyNumber) 	count = calToChar(RecmoconTVchannel);
	#endif

	// 숫자 출력
	OSD230DataSend(0x00);
	HighOSDArea=0;		//Low Display data.
	index = 0;
#if 1
	if(CheckChCATV(xEEPROMBuffer[CurrentChannel]))	//cable
	{
		OSD230SeqSend(DSP_ROW0,CII_COL8,0x00,10);	// 위치지정//2003-08-12
		OSD230ColSend(CII_COL8+1*2);		//
	}
	else	//air
	{
		OSD230SeqSend(DSP_ROW0,CII_COL4+4,0x00,10);	// 위치지정//2003-08-12
		OSD230ColSend(CII_COL4+4+1*2);
	}
#endif
	while(count--)
	{
		OSD230DataSend(CalBuffer[index]+0x01);
		index++;
		
		if(CheckChCATV(xEEPROMBuffer[CurrentChannel]))	//cable
		{
			OSD230ColSend(CII_COL8+(3-count)*2);	//2003-08-12
		}
		else	//air
		{
			OSD230ColSend(CII_COL4+4+(3-count)*2);
		}
	}

	if(OSDcharacters!=ChannelOnlyNumber) return;

	#if defined(USE_remocon)&&defined(USE_NTSCtuner)
		if(CheckChCATV(xEEPROMBuffer[CurrentChannel]))				
		{
			//OSD230SeqSend(ATTR_ROW1,CII_COL0,OSD_GREEN,30);	//색깔
			if(ThreeDigit)
			{
				if(ReceiveRemoconCount==1)
				{
					OSD230DataSend(_minus);
					OSD230DataSend(_minus);
				}
				else if(ReceiveRemoconCount==2)
				{
					OSD230DataSend(_minus);
				}
			}
			else
			{
				if(ReceiveRemoconCount==1) OSD230DataSend(_minus);
			}
		}
		else
		{
			if(ReceiveRemoconCount==1) OSD230DataSend(_minus);
		}
	#elif defined(USE_remocon)&&defined(USE_PALSECAMtuner)
		if(ThreeDigit)
		{
				if(ReceiveRemoconCount==1&&RecmoconTVchannel<2)
				{
					OSD230DataSend(_minus);
					OSD230DataSend(_minus);
				}
				else if(ReceiveRemoconCount==2||RecmoconTVchannel>1)
				{
					OSD230DataSend(_minus);
				}
		}
		else if(ReceiveRemoconCount==1) OSD230DataSend(_minus);
	#endif
}
//----------------------------------------------------------------------------------------
#endif
//----------------------------------------------------------------------------------------

// 20030818 smaprk 
void ShowChannelStatus(unsigned char status)
{
	xOSDW_OPTION[1]=0x00; 	// smpark 20030818
	
	#ifndef	ChannelDisplayDouble
			if(CurrentFunction==PipRnT_mode)		PipChannelOSD();
			else		ChannelOSD(80,8);
	#else
		//if(CheckChCATV(xEEPROMBuffer[CurrentChannel])) ChannelOSD(66,1);
		//else	ChannelOSD(70,1);;	//air
		ChannelOSD(64,1);
	#endif
	
	switch(status){
		case DISPLAY_ADD_DEL:	//Channel add/erase
			if(CheckChMask(xEEPROMBuffer[CurrentChannel]))
			{	// 저장된 채널
				OSD230SeqSend(ATTR_ROW0,CII_COL0,OSD_GREEN,30);	//색깔
				OSD230SeqSend(ATTR_ROW1,CII_COL0,OSD_GREEN,30);	//색깔
				
				OSD230SeqSend(DSP_ROW1,CII_COL0,0x00,30);
				OSD230PtrSend(DSP_ROW1,CII_COL1,Add[0],Add_Sizeof[0]);
	
			}else
			{	// 저장되지 않은 채널
				OSD230SeqSend(ATTR_ROW0,CII_COL0,OSD_YELLOW,30);	//색깔
				OSD230SeqSend(ATTR_ROW1,CII_COL0,OSD_YELLOW,30);	//색깔
				
				OSD230SeqSend(DSP_ROW1,CII_COL0,0x00,30);
				OSD230PtrSend(DSP_ROW1,CII_COL1,Erase[0],Erase_Sizeof[0]);				
			}
			break;
			
		case DISPLAY_MTS:	// MTS
			if(MTS_Stereo)
			{
				if(MTS_Stereo==MTS_STEREO_ON)
				{
					OSD230SeqSend(ATTR_ROW1,CII_COL0,OSD_RED,30);
					OSD230SeqSend(DSP_ROW1,CII_COL0,0x00,30);
					OSD230PtrSend(DSP_ROW1,CII_COL0+1,Stereo,sizeof(Stereo));
				}
				else if(MTS_Stereo==MTS_STEREO_OFF)
				{
					OSD230SeqSend(ATTR_ROW1,CII_COL0,OSD_BLUE,30);
					OSD230SeqSend(DSP_ROW1,CII_COL0,0x00,30);
					OSD230PtrSend(DSP_ROW1,CII_COL0+1,Mono,sizeof(Mono));
				}
			}
			else  if(MTS_Bilingual)
			{
				if(MTS_Bilingual==MTS_LANG_A)
				{
					OSD230SeqSend(ATTR_ROW1,CII_COL0,OSD_CYAN,30);
					OSD230SeqSend(DSP_ROW1,CII_COL0,0x00,30);
					OSD230PtrSend(DSP_ROW1,CII_COL0+1,LangA[0],LangA_Sizeof[0]);
				}
				else if(MTS_Bilingual==MTS_LANG_B)
				{
					OSD230SeqSend(ATTR_ROW1,CII_COL0,OSD_CYAN,30);
					OSD230SeqSend(DSP_ROW1,CII_COL0,0x00,30);
					OSD230PtrSend(DSP_ROW1,CII_COL0+1,LangB[0],LangB_Sizeof[0]);
				}
				else if(MTS_Bilingual==MTS_LANG_AB)
				{
					OSD230SeqSend(ATTR_ROW1,CII_COL0,OSD_CYAN,30);
					OSD230SeqSend(DSP_ROW1,CII_COL0,0x00,30);
					OSD230PtrSend(DSP_ROW1,CII_COL0+1,LangAB[0],LangAB_Sizeof[0]);
				}
			} 
			break;
		
		case 3:	//
			break;
	}
	
	OSDstatus = OSDexpire_timer;
	OSDofftimer = 3*200;	// smpark 20030818 
	xOSDW_OPTION[1]=0x00|0x80; 	// smpark 20030818
}                


void	Recall(void)
{
	if(NowTopOsdOn)
	{
		NowTopOsdOn = 0;
		OSDWindows = 0;
		OSDstatus = OSDoff;
		OsdService();
	}

	#if 1	//2003-10-17
	if(MENUstatus==MuteDisplay)
	{
		OSDWindows = VolumeWindow;
		OSDcharacters = VolumeChars;
		OSDstatus = OSDoff;
		Osd_onoff();
	}	
	else if(RecallFlag||SubWindowMsgFlag)//&&DataCode!=IR_PRECH) )
	{
		//OSD230SeqSend(DSP_ROW1,CII_COL3,0x00,10);
		
		OSDstatus = OSDoff;
		Osd_onoff();
		//SubWindowMsgFlag=0;
		//return;
	}
	#endif	

	OSDWindows = TunerSubWindow;
	//OSDstatus = RecallWindowDisplay;//2003-10-17 removed
	OsdMode = RecallWindowDisplay;	
	
	OSDstatus = OsdRamClear;
	Osd_onoff();

	NowTopOsdOn = 0;
	OsdGrade=0;
				
	DisplayWindow();

	RemoconDigit=0;	// smpark 20030827

#if 1	//2003-10-17
	if(CurrentFunction==Tuner_mode||CurrentFunction==PipRnT_mode)//2003-10-06
	{
		ShowChannelStatus(DISPLAY_MTS);

		OSDstatus = NowStatusDisplay;
		Osd_onoff();
	}
	else
	{
		OSDstatus = NowStatusDisplay;
		OsdService();
		
		ArrangeFunctionTable();
		if(CurrentFunction==Rgb_mode) OSDcharacters=PcChar;
		else if(CurrentFunction==Composite_mode) OSDcharacters=Av1Char;
		else if(CurrentFunction==Svideo_mode) OSDcharacters=Av2Char;
		//else if(CurrentFunction==PipRnC_mode) OSDcharacters=Av1Char;
		//else if(CurrentFunction==PipRnS_mode) OSDcharacters=Av2Char;
		DisplayMenuWindow();
	}

#endif	


	SubWindowMsgFlag=1;
	RecallFlag=1;
	
	OSDstatus = OSDexpire_timer;
	OSDofftimer = 3*200;//3sec!
	MENUstatus = RecallWindowDisplay;
}                

void  TVChannelAdd()
{
	if(NowTopOsdOn)
	{
		NowTopOsdOn = 0;
		OSDWindows = 0;
		OSDstatus = OSDoff;
		OsdService();
	}
	
	OSDWindows = TunerSubWindow;
	OSDstatus = AddDelWindowDisplay;
	OsdMode = AddDelWindowDisplay;	
	
	OSDstatus = OsdRamClear;
	Osd_onoff();

	NowTopOsdOn = 0;
	OsdGrade=0;
				
	DisplayWindow();
	
	RemoconDigit=0;	// smpark 20030827
	ToggleChMask();
	ShowChannelStatus(DISPLAY_ADD_DEL);

	OSDstatus = NowStatusDisplay;
	Osd_onoff();
		
	SubWindowMsgFlag=1;
	
	OSDstatus = OSDexpire_timer;
	OSDofftimer = 3*200;//3sec!
	MENUstatus = AddDelWindowDisplay;
}


void MTSDisplay()
{
	if( !(CurrentFunction==Tuner_mode || CurrentFunction==PipRnT_mode) )	return;
	
	if(NowTopOsdOn)	{
		NowTopOsdOn = 0;
		OSDWindows = 0;
		OSDstatus = OSDoff;
		OsdService();
	}

	OSDWindows = TunerSubWindow;
	OSDstatus = MtsWindowDisplay;
	OsdMode = MtsWindowDisplay;
	OSDcharacters = SscChar;
		
	OSDstatus = OsdRamClear;
	Osd_onoff();

	NowTopOsdOn = 0;
	OsdGrade=0;
				
	DisplayWindow();
	
	RemoconDigit=0;	// smpark 20030827
	MTSService();

	OSDstatus = NowStatusDisplay;
	Osd_onoff();

	SubWindowMsgFlag=1;
	
	OSDstatus = OSDexpire_timer;
	OSDofftimer = 3*200;//3sec!
	MENUstatus = MtsWindowDisplay;
}

void MTSService()
{
	if(MTS_Stereo)
	{
		MTS_Bilingual=MTS_NONE;
		if(MTS_Stereo==MTS_STEREO_ON) 		MTS_Stereo=MTS_STEREO_OFF;
 		else if(MTS_Stereo==MTS_STEREO_OFF)	MTS_Stereo=MTS_STEREO_ON;
	
		ShowChannelStatus(DISPLAY_MTS);
		StereoSet();
  }
  else  if(MTS_Bilingual)
  {
		MTS_Stereo=MTS_NONE;
 		if(MTS_Bilingual==MTS_LANG_A) 		MTS_Bilingual=MTS_LANG_B;
 		else if(MTS_Bilingual==MTS_LANG_B) 	MTS_Bilingual=MTS_LANG_AB;
 		else if(MTS_Bilingual==MTS_LANG_AB) 	MTS_Bilingual=MTS_LANG_A;
	
		ShowChannelStatus(DISPLAY_MTS);
		BilingualSet();
	}
}

/*
void  DisplayChannelStatus(BYTE CHStatus )
{
	// 0: RECALL
   	// 1: ADD /DEL
	// 2: MTS

	if(NowTopOsdOn)
	{
		NowTopOsdOn = 0;
		OSDWindows = 0;
		OSDstatus = OSDoff;
		OsdService();
	}
	OSDWindows = TunerSubWindow;

	OSDstatus = ChannelStatusDisplay;
	OsdMode = ChannelStatusDisplay;	
	
	//OSDstatus = OsdRamClear;	//2003-08-28
	//Osd_onoff();

	NowTopOsdOn = 0;
	OsdGrade=0;
				
	DisplayWindow();

	switch(CHStatus){

	case 0:	// RECALL
		ShowChannelStatus(DISPLAY_MTS);
		break;

	case 1:	// ADD DEL
		ToggleChMask();
		ShowChannelStatus(DISPLAY_ADD_DEL);
		break;

	case 2:	// MTS
		MTSService();
		break;
	}

	OSDstatus = NowStatusDisplay;
	Osd_onoff();

	SubWindowMsgFlag=1;
	
	OSDstatus = OSDexpire_timer;
	OSDofftimer = 3*200;//3sec!
	MENUstatus = ChannelStatusDisplay;
}
*/			
//------------------------------------------------------------------------------------------------------------------
#endif
//------------------------------------------------------------------------------------------------------------------

#endif
