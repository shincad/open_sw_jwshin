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

   2003-01-10 2:39오후  JDHAN           Modified for Monitor-TV
****************************************************************************/

//****************************************************************//
//화일참조
//****************************************************************//
#include	"TopHeader.h"
#include "extern.h"
#include	"power.h"
#include	"EEPROMadr.h"
#include	"TVMODE.h"
#include	"osd_def_val.h"
#include	"btc_osdmenu.h"
#include "stdio.h"
#include "tw990x.h"
#include "sprocessor.h"
#include "tuner.h"

#if		defined(MCU_MTV230)
#include	"MTV230xfr.h"
#elif		defined(MCU_MTV412)
#include	"MTV412xfr.h"
#elif		defined(MCU_NT68F63)
#include	"NT68F63.h"
#endif

#include "scaler_set.h"

//****************************************************************//
//함수선언
//****************************************************************//
void BitWriteScaler(BYTE address, BYTE BitArry, BYTE Recdata);
void EepromSetQue(WORD address, BYTE Recdata);
void SetScalerPIPOutputCondition(BYTE Recdata);
void SetScalerZoomFactor(BYTE Recdata);
void ChangeToRgbOnly(void);
void ChangeToCompositeOnly(void);
void ChangeToSvideoOnly(void);
void ChangeToTunerOnly(void);
//void ChangeToPipRgbTuner(void);
void ChangeToPipRgbTunerFast(void);
void ChangeToPipRgbComposite(void);
void ChangeToPipRgbCompositeFast(void);
void ChangeToPipRgbSvideo(void);
void ChangeToPipRgbSvideoFast(void);
void SDA555xModeChange();
void ArrangeFunctionTable();
//void AutoDisplayadjust(void);
//void	SubWindowDisplay(void);
void OSD230SeqSend(BYTE Recdata0,BYTE Recdata1,BYTE Recdata2,BYTE Recdata3);
void	OnoffDisplayFunc(BYTE RecRow, BYTE RecCol, BYTE RecOnOffFlag);
void Write24c16Page(WORD addr, BYTE *p);
void	PipSourceSelService(void);



#ifdef DVI_USE
void ChangeToDviOnly(void);
void ChangeToPipDviTuner(void);
void ChangeToPipDviTunerFast(void);
void ChangeToPipDviComposite(void);
void ChangeToPipDviCompositeFast(void);
void ChangeToPipDviSvideo(void);
void ChangeToPipDviSvideoFast(void);
#endif

void ChangeToVideo50Hz60HzSystem(void);

bit WriteI2C(BYTE sysaddr, BYTE subaddr, BYTE writedata);

#ifdef	USE_4BitInterface						//4bit통신 함수선언
void	WriteReg4bit(BYTE address, BYTE Recdata);
#define	WriteScaler(val1,val2) WriteReg4bit(val1,val2)	
#else									//1bit통신 함수선언
void	WriteReg1bit(BYTE address, BYTE Recdata);
#define	WriteScaler(val0, val1) WriteReg1bit(val0, val1)
#endif

#ifdef	BtcBoard_Option		//-----------------------------
void	osd_menu_on(void);
void	power_onoff(void);
void	updown_svc(void);
void	leftright_svc(void);
void	volume_svc(void);

void PipSizeSelService(void)	;
void	PipSourceSelService(void);

void	Displaycharacter(void);
void	Displaycusor(void);

void	UpdownMenu(BYTE MenuStart, BYTE MenuEnd);
void	OsdOnoff(void);
void	OsdService(void);
void 	PutData(void);
void 	OSDMENU_FONT(BYTE *addr);
void 	PutVolumePWM();
//void 	PreInit(void);
	
extern	void	Display_MenuDescription(void);
extern	void	Display_TvMenuDescription(void);
extern	void	Display_MenuBarPercent(void);
extern	void 	MenuSel(void);
extern	void 	OsdDataWindowClear(void);
extern	void 	OsdDataWindowClear2(void);
extern	void 	OsdAttrClear(void);
extern	void 	OsdAttr_row10_Clear(void);
extern	void 	OsdDataClear(void);
extern	void	SubWindowDisplay(void);
extern	void	DisplayInformation(void);

extern	void	Display_TopMenuIcon(void);
extern	void	Display_TvTopMenuIcon(void);
extern	void 	DisplayMenuWindow(void);
extern	void 	DisplayWindow(void);
extern	void 	IconSel(void);
extern	void	Auto_Func(void);
extern	void 	PipSubRegisterSet(void);
extern	void	ClearMenuDescription(void);
extern	void 	Osd_onoff(void);
extern	void 	ProgEditCh_display(void);
extern	void	ChEdit_CursorFunc(void);
extern	void	MenuBarValue(void);
extern	void 	Display_AdjustInfo(void);
extern	void	TvMenuBarValue(void);
extern	void	CcdCaptionSelFunc(void);
extern	void	CcdModeSelFunc(void);
extern	void	CcdChannelSelFunc(void);
extern	void	CcdFieldSelFunc(void);
extern	void	CcdDisplaySelFunc(void);

extern	void 	ChEdit_WindowOn(void);
extern	void 	ChEdit_WindowOff(void);
extern	void 	OSD230PtrSend(BYTE Recdata0,BYTE Recdata1,BYTE *Recdata2,BYTE Recdata3);
extern	void ChangeToVideo50Hz60HzSystem(void);
extern	void Hue_ColorBar(void);

extern	BYTE GetMenuStart(void);
extern	BYTE GetMenuStart2(void);
extern	BYTE GetTopMenu(void);
extern	BYTE GetTvTopMenu(void);
extern	BYTE GetTvMenuStart(void);
extern	BYTE GetTvMenuStart2(void);

extern  void	PipOnoffFunc(unsigned char RecRow, unsigned char RecCol, unsigned char RecOnOffFlag);
extern void 	Display_BottomCurrentInfo(void);
extern	void PipPositionService(void);
extern	void	DosmodeDisplay(BYTE RecRow, BYTE RecCol, BYTE DosmodeFlag);
extern	void PowerSequence(void);
extern	void Keydetect(void);
extern	void	MuteExe(void);	//2004-05-28
extern void VideoDecoderInit(void);
extern void Recall(void);
extern	void	PipBlendFunc(void);
extern	void	PipEnableFunc(void);
extern	void IntOsdOff(void);

extern void SoundSetVolume(void);	//smaprk 20030923

#ifdef test_function
extern	void	MenuNum_display(void);//test
	#endif

extern	void	ChEdit_CharFunc(void);
extern	bit	EditWindowFlag;
extern bit	RemAddBtn;		// smpark 20030808


extern xBYTE PreSoundMode;	// smpark 20030811

extern void ShowChannelStatus(unsigned char status);	// smpark 20030808
extern	void	PipAspectSelFunc(void);
extern code BYTE * code Wait[];
extern code BYTE Wait_Sizeof[];

//extern	void	TvAspectRatioSelFunc(void);
extern void TVChannelAdd(void);	// smpark 20030825
//extern 	void  DisplayChannelStatus(BYTE CHStatus );	// smpark 20030825
extern	void WordWriteScaler(BYTE address, WORD Recdata);//test

#endif	//-----------------------------------------------------


extern BYTE code VolumeTable[];
extern	BYTE EEPROM_Read(WORD address);


#define	InputSourceChangeToDVIMode 			xEEPROMBuffer[MainSubInputSource] = 6
#define	InputSourceChangeToCompositeMode		xEEPROMBuffer[MainSubInputSource] = 10
#define	InputSourceChangeToSvideoMode			xEEPROMBuffer[MainSubInputSource] = 14
#define	InputSourceChangeToTunermode			xEEPROMBuffer[MainSubInputSource] = 18
#define InputSourceChangeToPIPmode			xEEPROMBuffer[MainSubInputSource] = 52
#define	InputSourceChangeToRGBmode			xEEPROMBuffer[MainSubInputSource] = 2



/*
typedef	struct{
	BYTE	TopMenu;
	BYTE	Start;
	BYTE	End;
}MenuPosition;

code MenuPosition MenuDown[TopMenuEnd+1]=
{
	 {MENU_DISPLAY,DisplayMenuStart,DisplayMenuEnd}		
	,{MENU_RGB,RgbMenuStart,RgbMenuEnd}
	,{MENU_OSD,OsdMenuStart,OsdMenuEnd}	
	,{MENU_PIP,PipMenuStart,PipMenuEnd}	
	,{MENU_TOOLS,ToolsMenuStart,ToolsMenuEnd}
};
*/

//****************************************************************//
//System Initialzie
//****************************************************************//
void SystemInitialize(void)
{
	BYTE idata temp = 0;	
	xBYTE 	EEpromBuff[16],j;
	WORD xdata addr;
	
	#ifdef USE_UART
	DBGputs("SystemInitialize ");
	#endif
	
	j=0;
	addr=BaseEEPROM_adr;

	do
	{
		//EepromSetQue(BaseEEPROM_adr+(temp),EEPROM_DftVal[temp]);
		EEpromBuff[j++]=EEPROM_DftVal[temp];
		xEEPROMBuffer[temp] = EEPROM_DftVal[temp]; //code영역에서 buffer로 데이타를 옮겨놓는다.
		temp++;
		if(j==16){	// 16byte가 버퍼에 채워지면 write..
			j=0; 
			Write24c16Page(addr, EEpromBuff);
			addr=addr+16;
		}
	}
	while(temp<TotalEeprom);

	if(j!=0)
	{	// 조금 남은것 처리 
		Write24c16Page(addr, EEpromBuff);
	}
	
	TVCountrySet();
	
	//기타 Flag 초기화
	AspectFlag=0;
	DosmodeFlag=1;
	TransparencyOnfFlag=0;
	AntenaFlag=0;
	PipOnOffFlag=0;
	PipAspectFlag=0;
	PipBlendNum=0;
	PipHposUpdownFlag=1;
	PipVposUpdownFlag=1;
	PipZoomUpdownFlag=1;
	PipSmallLargeFlag=0;
	DpmsPipFlag=0;
	DpmsFlag=0;
	PipInputSource=0;
	PipSizeNum=0;
	PipHPositionNum=1;
	PipVPositionNum=1;
	MenuNum=0;            
	TvMenuNum=0;          
	OsdGrade=0;           
	SProcessor =0;        
	SoundProcessTimer=0;  
	SoundProcessStatus=0; 
	//Backchannel=Frontchannel=0;
	
	LED_OFF;
	YouHaveToInitMode=1;//Mode Clock,Phase,H-pos,V-pos,Pre-auto initial
	YouHaveToInitTVchannel=0;//Mode eeprom initialize한후....
}

/*
void PreInit(void)
{
//	xEEPROMBuffer[ColorTemp]=1;			//초기화//2003-04-29
//	PipOnOffFlag=(xEEPROMBuffer[PIPEN_SOURCE_buf]&0x1f)>>4;	//2003-07-31
	//PipInputSource=xEEPROMBuffer[PIPEN_SOURCE_buf]&0x03;
	#ifdef TempOsdMenu
//	xEEPROMBuffer[TempOsdBlend_buf]=1;
	#endif	
}
*/

//******************************************
//현재 저장된 값으로 볼륨을 출력한다 
//**********************************************
void PutVolumePWM()
{
	//VolumePWM(xEEPROMBuffer[VOLUME_buf]*3.6);
	//lumePWM(xEEPROMBuffer[VOLUME_buf]*2.55);
	//VolumePWM(xEEPROMBuffer[VOLUME_buf]*2.22+33);


	// smpark 20030923
#ifdef VOLUME_PWM
	VolumePWM(VolumeTable[xEEPROMBuffer[VOLUME_buf]])
#else
	SoundSetVolume();
//	xEEPROMBuffer[VOLUME_buf]=MenuVal;//
//	EepromSetQue(VOLUME_adr,xEEPROMBuffer[VOLUME_buf]);//
#endif
}

void	PipEnableService(void)
{
	//if(DpmsFlag!=1)	PipOnOffFlag ^= 1;
	if(PipOnOffFlag)	//pip on
	{
		Mute_SoundOff;//	VIDEOenable;
			
		CurrentFunction=5;
		
		//xEEPROMBuffer[MainSubInputSource] = 20;


//test2004-06-29		PipInputSource=xEEPROMBuffer[PIPEN_SOURCE_buf]&0x03;//
		
		switch(PipInputSource)
		{
			case		SourceComposite:
								xEEPROMBuffer[MainSubInputSource]=20;
							break;
							
			case		SourceSvideo:
								xEEPROMBuffer[MainSubInputSource]=28;
							break;
			case		SourceTuner:
								xEEPROMBuffer[MainSubInputSource]=52;
							break;
		}
		
		
		//ArrangeFunctionTable();

		VideoActiveCompleted = 0;
		
		#if defined(SAA7114)
		WriteI2C(SAA7114_sysaddress,0x02,0xc4);//Input change!
		#elif defined(SAA7115)
		WriteI2C(SAA7115_sysaddress,0x02,0xc4);//Input change!
		#elif defined(TW9908)
		    //
		#endif
		
		EepromSetQue(MainSubInputSource_adr,20);	
		PipFastChange = 1;
		
		//OSD status 
		//Volume Path
		//OSDWindows = AnalogSubwindow;
		
		if(CurrentFunction==PipRnT_mode)
		{
				OSDstatus = TVchannelDisplay;
		}
		else		OSDstatus = NowStatusDisplay;
		
		OSDWindows = PIPSubWindow;
		//OSDcharacters = PipRgbCompositeChars;
		
	
//PipSizeSelService();	
//PipSourceSelService();
	
		//SetScalerPIPOutputCondition(xEEPROMBuffer[MainSubInputSource]);	//PIP on
		PipSubRegisterSet();

		//PipBlendFunc();
		//WriteScaler(0x99,0x20);	//PIP16bit , Deinterlaced
		//PipEnableFunc();

		//if(CurrentFunction==PipRnT_mode)	Recall();

		#ifdef BtcBoard_Option
		AudioSelection_PC;
		#else
		AudioSelection_LOW;
		#endif

//PIPMuteOff;//test2004-07-06
		if(!SoundMuteOnFlag)	//MUTE가 아닌경우.
		{
			Mute_SoundOn;	//Sound On~~
			PutVolumePWM();
		}
		
	}
	else		// PIP OFF
	{
		//ChangeToRgbOnly();
		Mute_SoundOff;	//VIDEOdisable;
		//TW9908_RSTON;
		VideoActiveCompleted = 0;
		
		OSDstatus = OSDoff;
		
		#ifdef BtcBoard_Option
			AudioSelection_PC;
		#else			
			AudioSelection_LOW;
		#endif

		PutVolumePWM();
		if(SoundMuteOnFlag==0)	Mute_SoundOn;	//Mute가 아니면..
		
		switch(xEEPROMBuffer[MainSubInputSource])
		{
			case 20://RGB+COMPOSITE->RGB
			case 28://RGB+SVIDEO->RGB
			case 52://RGB+TUNER->RGB
				//WriteScaler(0x8E,0x00);//PIP OFF
				PIPMuteOn;PipMuteTimer=40;	//BitWriteScaler(0x8E,0x04,0);	//PIP display disable
				BitWriteScaler(0x9A,0x80,0);//pip BG off	//2003-08-20
				
				xEEPROMBuffer[MainSubInputSource] = 2;
				CurrentFunction=0;
				EepromSetQue(MainSubInputSource_adr,2);
				break;
			
			#ifdef DVI_USE
			case 36://DVI+COMPOSITE->DVI
			case 44://DVI+SVIDEO->DVI
			case 60://DVI+TUNER->DVI
				//WriteScaler(0x8E,0x00);//PIP OFF
				PIPMuteOn;PipMuteTimer=40;	//BitWriteScaler(0x8E,0x04,0);	//PIP display disable
				
				xEEPROMBuffer[MainSubInputSource] = 4;
				CurrentFunction=1;
				EepromSetQue(MainSubInputSource_adr,4);
				break;
			#endif
		}
	}
}

void	PipSourceSelService(void)
{
	switch(PipInputSource)
	{
		case SourceComposite://
            		//AudioSelection_AV;	// 20030930 smpark 
            		
			switch(CurrentFunction)
			{
				case 5://현재상태가 composite를 키고 있으면 그냥 빠진다.
				case 8:
					OSDstatus = Cursermove;
					KEY_value=0;
					break;					
				#ifdef DVI_USE				
				case 9:	//PIP D+S
				case 10://PIP D+T
				case 13://PIP D+SC
//					OSDSelKeyin = 0;
					#ifdef DVI_USE
						ChangeToPipDviCompositeFast();
					#endif
					break;
				#endif
				
				case 6:
				case 7:
				case 12://PIP R+SC	
//					OSDSelKeyin = 0;
					ChangeToPipRgbCompositeFast();
					break;				
				
				default:

					OSDstatus = Cursermove;
					KEY_value=0;
					break;
			}
			AudioSelection_AV;
			
			break;
		
		case SourceSvideo:
			//AudioSelection_AV;	// 20030930 smpark
			switch(CurrentFunction)
			{
				case 6://현재상태가 s-video를 키고 있으면 그냥 빠진다.
				case 9:
					OSDstatus = Cursermove;
					KEY_value=0;
					break;
					
				case 8:
				case 10:
				case 13://PIP D+SC
//					OSDSelKeyin = 0;
					#ifdef DVI_USE
					//if(xEEPROMBuffer[MainSubInputSource]==4||xEEPROMBuffer[MainSubInputSource]==6) ChangeToPipDviSvideoFast();
					//else ChangeToPipDviSvideo();
					//MUTEON;
					ChangeToPipDviSvideoFast();
					#endif
					break;
				
				case 5:
				case 7:
				case 12://PIP R+SC
//					OSDSelKeyin = 0;
					//if(xEEPROMBuffer[MainSubInputSource]==0||xEEPROMBuffer[MainSubInputSource]==2) ChangeToPipRgbSvideoFast();
					//else ChangeToPipRgbSvideo();
					ChangeToPipRgbSvideoFast();
					break;	
			}
			AudioSelection_AV;
			break;
		
		case SourceTuner:
			//AudioSelection_TV;	// 20030930 smpark
			switch(CurrentFunction)
			{
				case 7://현재상태가 tuner를 키고 있으면 그냥 빠진다.
				case 10:
					OSDstatus = Cursermove;
					KEY_value=0;
					break;
					
				case 8:
				case 9:
				case 13://PIP D+SC
//					OSDSelKeyin = 0;
					#ifdef DVI_USE
					//if(xEEPROMBuffer[MainSubInputSource]==4||xEEPROMBuffer[MainSubInputSource]==6) ChangeToPipDviTunerFast();
					//else ChangeToPipDviTuner();
					ChangeToPipDviTunerFast();
					#endif
					break;
				
				case 5:
				case 6:
				case 12://PIP R+SC
//					OSDSelKeyin = 0;
					//if(xEEPROMBuffer[MainSubInputSource]==0||xEEPROMBuffer[MainSubInputSource]==2) ChangeToPipRgbTunerFast();
					//else ChangeToPipRgbTuner();
				
					ChangeToPipRgbTunerFast();
					break;	
			}
			AudioSelection_TV;
			break;

		#if defined(USE_SCART)
		case SourceScart:

			switch(CurrentFunction)
			{
				case 11:
				case 12:		//현재 상태가 SCART면 그냥 빠진다.
				case 13:
					OSDstatus = Cursermove;
					KEY_value=0;					
					break;
				case 8:					
				case 9:	//PIP D+S
				case 10://PIP D+T
				
//					OSDSelKeyin = 0;
					#ifdef DVI_USE
					ChangeToPipDviScartFast();
					#endif
					break;
				
				case 5:
				case 6:
				case 7:					
//					OSDSelKeyin = 0;
					ChangeToPipRgbScartFast();
					break;						
			}
			break;

		#endif	
	}
	
	//if(MenuNum==menu_pip_source||OsdGrade>=1)	
	//{
		//WriteScaler(0x8E,0x00);//PIP OFF
		//idelay5m(10);//test
	//}
	
}

void PipSizeSelService(void)		//OSD Large or Small
{
	//BitWriteScaler(0x9A,0x80,0);//pip BG off	//2003-08-20
	//BitWriteScaler(0x9A,0x40,0);//pip off	//2003-08-20
	//idelay5m(10);
	//OSDstatus = Cursermove;
	xEEPROMBuffer[PIPSIZE_buf]= ( (PipSizeNum&0x03)+(xEEPROMBuffer[PIPSIZE_buf]&0xf0) );
	
	EepromSetQue(PIPSIZE_adr,xEEPROMBuffer[PIPSIZE_buf]);


	//if(MenuNum==menu_pip_size||MenuNum==menu_pip_AspectRatio) WriteScaler(0x9a,0x00);//PIP OFF//2003-10-16
	if(MenuNum==menu_pip_size||MenuNum==menu_pip_AspectRatio)	
	{		//2004-06-23
			BitWriteScaler(0x9A,0x80,0);//pip BG off
			BitWriteScaler(0x9A,0x40,0);//pip disable
	}
	
	SetScalerZoomFactor(xEEPROMBuffer[MainSubInputSource]);
	SetScalerPIPOutputCondition(xEEPROMBuffer[MainSubInputSource]);	//PIP on
}									


void PipAspectSelService(void)
{
	xEEPROMBuffer[PIPSIZE_buf]= ( (PipSizeNum&0x03)|((BYTE)PipAspectFlag&0x01<<4) );
	EepromSetQue(PIPSIZE_adr,xEEPROMBuffer[PIPSIZE_buf]);
}

void AspectRatioService(void)
{
	SetScalerZoomFactor(xEEPROMBuffer[MainSubInputSource]);
}

void TvAspectRatioService(void)	//2003-08-04
{
	if(NowTopOsdOn)	OSDstatus = Cursermove;
	else		OSDstatus = OSDoff;
	xEEPROMBuffer[DisplayAspcet_buf]= ( (DisplayAspectRatioNum&0x03)+(xEEPROMBuffer[DisplayAspcet_buf]&0xf0) );
	EepromSetQue(PIPSIZE_adr,xEEPROMBuffer[DisplayAspcet_buf]);
	
//test//2004-05-10	ChangeToVideo50Hz60HzSystem();	//2003-08-14 	//!!!
	SetScalerZoomFactor(xEEPROMBuffer[MainSubInputSource]);	//☆☆☆
	idelay5m(16);
}

void	OsdOnoff(void)
{
	if(NowTopOsdOn) //MENU ON->OFF
	{
		NowTopOsdOn = 0;
		OSDWindows = 0;
		OSDstatus = OSDoff;
		KEY_value = 0;
		RemAddBtn=0;
	}
	else //OFF->MENU
	{
		osd_menu_on();
		
		OSDstatus = TopMenuWindow;
		KEY_value = 0;
		RemAddBtn=0;
	}
}
		


void	osd_menu_on(void)
{
	if(MENUstatus==Nosignal_Display) 	//No-RGB,No-DVI,No-COMPOSITE,NO-SVIDEO일 경우 그냥빠짐
	{
		KEY_value=0;	
		return;
	}	
	
	if	( 0<=xEEPROMBuffer[MainSubInputSource]&&xEEPROMBuffer[MainSubInputSource]<=2 ) 	//RGB MODE
	{
		OSDWindows = AnalogMainWindow;	
		OSDcharacters = AnalogMainChars; 
		//OSDcusorPosition = 0;//MenuNum;//1;//TopMenuStart;
	}										
	else if	( 4<=xEEPROMBuffer[MainSubInputSource]&&xEEPROMBuffer[MainSubInputSource]<=6 ) 	//DVI MODE
	{
		OSDWindows = DigitalMainWindow;	
		OSDcharacters = DigitalMainChars; 
		//OSDcusorPosition = 49;
	}										
	else if	( 8<=xEEPROMBuffer[MainSubInputSource]&&xEEPROMBuffer[MainSubInputSource]<=11) 	//COMPOSITE MODE
	{
		OSDWindows = CompositeMainwindow; 
		OSDcharacters = CompositeMainChars; 
		//OSDcusorPosition =62;
	}										
	else if	(12<=xEEPROMBuffer[MainSubInputSource]&&xEEPROMBuffer[MainSubInputSource]<=15) 	//S_VIDEO MODE
	{
		OSDWindows = S_videoMainWindow;	
		OSDcharacters = S_videoMainChars; 
		//OSDcusorPosition =79;
	}										
	else if	(16<=xEEPROMBuffer[MainSubInputSource]&&xEEPROMBuffer[MainSubInputSource]<=19) 	//TUNER MODE
	{
		OSDWindows = TunerMainWindow;	
		OSDcharacters = TunerMainChars;	
		//OSDcusorPosition = 25;
	}										
	else if	(20<=xEEPROMBuffer[MainSubInputSource]&&xEEPROMBuffer[MainSubInputSource]<=67) 	//PIP MODE
	{
		OSDWindows = PIPMainWindow;	
		OSDcharacters = PIPMainChars;	
		//OSDcusorPosition = 98;
	}
}

void	power_onoff()
{
	if(PowerOnsequence<MainPowerON)			//off->ON
	{
		PowerOnTimer = 20;
		PowerOnsequence = MainPowerON;
		PowerOffsequence = 0;			//Noting!
		PowerONF = 1;
		
		#if	defined(USE_UART)
		xPADMOD1 = 0x01;		//UART
		#endif
		
		SOUNDSTBY_OFF;
		//idelay5m(400);		// smpark 20030925
		
		TunerPowerOn;
		EepromSetQue(POWERID_adr,0x55);
	}
	else if(PowerOnsequence>=MainPowerON)		//ON->off
	{
		SoundFastMute();	//smpark 20030925
		Mute_SoundOff;	//smpark 20030925
		
		idelay5m(8);	
		
		PowerOffTimer = 5;
		PowerOffsequence = PanelInvertOFF;
		PowerOnsequence =0;			//Noting!
		PowerONF = 0;
		
		#if	defined(USE_UART)
		xPADMOD1 = 0x81;		//DDC
		#endif
		
		SOUNDSTBY_ON;
		TunerPowerOff;
		xEEPROMBuffer[Sleep_buf]=0;	//sleep value Init.
		EepromSetQue(POWERID_adr,0x0);
	}
}

void	UpdownMenu(BYTE MenuStart, BYTE MenuEnd)
{
	if( (xEEPROMBuffer[MainSubInputSource]!=10)&&(xEEPROMBuffer[MainSubInputSource]!=14)&&(xEEPROMBuffer[MainSubInputSource]!=18) )	//PC
	{
		if(KEY_value==DownKey)
		{
			if( (TopMenuStart<=MenuNum)&&(MenuNum<=TopMenuEnd) )GetMenuStart2();
			
			if( (MenuNum>=MenuEnd)||((MenuNum==MenuStart)&&(OsdGrade==0)) ) {MenuNum=MenuStart;OsdGrade=1;}
			else MenuNum++;
		}
		else if(KEY_value==UpKey)
		{
			#if 1
				if( (TopMenuStart<=MenuNum)&&(MenuNum<=TopMenuEnd) )GetMenuStart2();
				
				if( (MenuNum<=MenuStart)||((MenuNum==MenuStart)&&(OsdGrade==0)) ) {MenuNum=MenuEnd;OsdGrade=1;}
				else MenuNum--;
			#else
				if( (TopMenuStart<=MenuNum)&&(MenuNum<=TopMenuEnd)||(OsdGrade==0) )return;	//첫메뉴에서 up key 작동 안되게
                        	
				if(MenuNum<=MenuStart) MenuNum=MenuEnd;
				else MenuNum--;
			#endif


		}
	}
	else		//TV
	{
		if(KEY_value==DownKey)
		{
			if( (TvTopMenuStart<=TvMenuNum)&&(TvMenuNum<=TvTopMenuEnd) ){
				GetTvMenuStart2();
			}if( (TvMenuNum>=MenuEnd)||((TvMenuNum==MenuStart)&&(OsdGrade==0)) ) {
				TvMenuNum=MenuStart;
				OsdGrade=1;
			}else{
				TvMenuNum++;
			}
		}
		else if(KEY_value==UpKey)
		{
			#if 1
				if( (TvTopMenuStart<=TvMenuNum)&&(TvMenuNum<=TvTopMenuEnd) )GetTvMenuStart2();
				
				if( (TvMenuNum<=MenuStart)||((TvMenuNum==MenuStart)&&(OsdGrade==0)) ) {TvMenuNum=MenuEnd;OsdGrade=1;}
				else TvMenuNum--;
			#else
				if( (TvTopMenuStart<=TvMenuNum)&&(TvMenuNum<=TvTopMenuEnd)||(OsdGrade==0) )return;	//첫메뉴에서 up key 작동 안되게
				
				if(TvMenuNum<=MenuStart) TvMenuNum=MenuEnd;
				else TvMenuNum--;
			#endif

			
		}
	}
}
	
void ChEdit_Updown(void)
{

	#ifdef USE_NTSCtuner

	
		if(KEY_value == DownKey)
		{
			if(xEEPROMBuffer[CurrentChannel] >= (CHANNEL_LIMIT-1)) xEEPROMBuffer[CurrentChannel] = 0;
			else xEEPROMBuffer[CurrentChannel]++;
		}
		else if(KEY_value == UpKey)
		{
			if(xEEPROMBuffer[CurrentChannel] <= 0) xEEPROMBuffer[CurrentChannel] = CHANNEL_LIMIT-1;
			else xEEPROMBuffer[CurrentChannel]--;
		}
		//OSD230SeqSend(ATTR_ROW6+(xEEPROMBuffer[CurrentChannel]%5),CII_COL0,OSD_RED,29);
	
	#else
	
		if(KEY_value == DownKey)
		{
			if(xEEPROMBuffer[CurrentChannel] >= CHANNEL_LIMIT-1) xEEPROMBuffer[CurrentChannel] = 0;
			else xEEPROMBuffer[CurrentChannel]++;
		}
		else if(KEY_value == UpKey)
		{
			if(xEEPROMBuffer[CurrentChannel] <= 0) xEEPROMBuffer[CurrentChannel] = CHANNEL_LIMIT-1;
			else xEEPROMBuffer[CurrentChannel]--;
		}
		//OSD230SeqSend(ATTR_ROW6+(xEEPROMBuffer[CurrentChannel]%5),CII_COL0,OSD_RED,29);
		
	#endif

	
} 

	
void	updown_svc()	// Up/Down Key || Channel Up/Down Key	//2003-04-16 made by thkim
{
	unsigned int CheckPageNum=(xEEPROMBuffer[CurrentChannel]/5);
		
	if( (xEEPROMBuffer[MainSubInputSource]!=10)&&(xEEPROMBuffer[MainSubInputSource]!=14)&&(xEEPROMBuffer[MainSubInputSource]!=18) )
	{
		switch( GetTopMenu() )
		{
			case MENU_DISPLAY:
				UpdownMenu(DisplayMenuStart,DisplayMenuEnd);
				break;
			case MENU_RGB:
				UpdownMenu(RgbMenuStart,RgbMenuEnd);
				break;
			case MENU_OSD:
				UpdownMenu(OsdMenuStart,OsdMenuEnd);
				break;
			case MENU_PIP:
				if(PipOnOffFlag==0)
				{
						if(MenuNum!=menu_pip_enable && OsdGrade==0)	UpdownMenu(PipMenuStart,PipMenuStart);
						else	return;
				}
				else	UpdownMenu(PipMenuStart,PipMenuEnd);
				break;
			case MENU_TOOLS:
				UpdownMenu(ToolsMenuStart,ToolsMenuEnd);
				break;
			case MENU_SOUND:	//smpark
				UpdownMenu(SoundMenuStart,SoundMenuEnd);
				break;
		}
		OSDofftimer = (WORD)xEEPROMBuffer[OSDOFFTIME_buf]*200;
		OSDstatus = OSDexpire_timer;
		OsdGrade=1;
	}
	else
	{
		switch( GetTvTopMenu() )
		{
			case TVMENU_PICTURE:
				UpdownMenu(TvPictureStart,TvPictureEnd);
				break;
			case TVMENU_SETUP:
				
				if(OsdGrade==2)
				{
					if(TvMenuNum==tvmenu_country)
					{
						
						return;
					}
					else if(TvMenuNum==tvmenu_auto_setup)
					{
						return;
					}
					else if(TvMenuNum==tvmenu_channel_edit)
					{
						ChEdit_Updown();
						PutData();

						ProgEditCh_display();
                                               	
						ChEdit_CharNum=0;

						return;
					}
					#ifdef Ccd_Vchip
					else if(TvMenuNum==tvmenu_Ccd)
					{
						return;
					}
					else if(TvMenuNum==tvmenu_Vchip)
					{
						return;
					}
					#endif
					

				}
				#ifndef PalCountry_ChinaOnly //====================================
				else if(OsdGrade==3 && TvMenuNum==tvmenu_channel_edit)
				{
				#if defined (USE_NTSCtuner)
//					if(OsdGrade==3&&ChEdit_CursorNum==1)
//					{
//						SkipFlag ^= 1;
//						OnoffDisplayFunc(DSP_ROW6+(xEEPROMBuffer[CurrentChannel]%5),CII_COL20,(BYTE)SkipFlag); //메모리작업요망.
//						return;
//					}
//					if(OsdGrade==3&&ChEdit_CursorNum==0)
//					{
//						OsdGrade=2;
//						//ChEdit_Updown();	//나중에 작업요망 (up후 down시 2차이)
//						return;
//					}

				#elif defined (USE_PALSECAMtuner)

					if( (OsdGrade==3)&&(ChEdit_CursorNum!=0)&&(ChEdit_CursorNum<6) )
					{
						
						EditWindowFlag=1;
						
						if(ChEditChar1Start<=ChEdit_CharNum && ChEdit_CharNum<=ChEditChar1End)
						{
							if(KEY_value==UpKey)
							{
								if(ChEdit_CharNum>=ChEditChar1End) ChEdit_CharNum=ChEditChar2Start;
								else	ChEdit_CharNum++;
							}
							else if(KEY_value==DownKey)
							{
								if(ChEdit_CharNum<=ChEditChar1Start) ChEdit_CharNum=ChEditChar2End;
								else	ChEdit_CharNum--;
							}
						}
						else if(ChEditChar2Start<=ChEdit_CharNum && ChEdit_CharNum<=ChEditChar2End)
						{
							if(KEY_value==UpKey)
							{
								if(ChEdit_CharNum>=ChEditChar2End) ChEdit_CharNum=ChEditChar1Start;
								else	ChEdit_CharNum++;
							}
							else if(KEY_value==DownKey)
							{
								if(ChEdit_CharNum<=ChEditChar2Start) ChEdit_CharNum=ChEditChar1End;
								else	ChEdit_CharNum--;
							}							
						}
						

						OSD230SeqSend(ATTR_ROW13,CII_COL0,OSD_BLACK,30);
						OSD230SeqSend(ATTR_ROW14,CII_COL0,OSD_BLACK,30);
						if(ChEditChar1Start<=ChEdit_CharNum && ChEdit_CharNum<=ChEditChar1End)	//첫줄
						{
							OSD230SeqSend(ATTR_ROW13,CII_COL4+ChEdit_CharNum,0x70|OSD_BLACK,1);
						}
						else if(ChEditChar2Start<=ChEdit_CharNum && ChEdit_CharNum<=ChEditChar2End) //둘째줄
						{	
							OSD230SeqSend(ATTR_ROW14,CII_COL4+ChEdit_CharNum-ChEditChar1End-1,0x70|OSD_BLACK,1);
						}						
						
						return;
					}
					if(OsdGrade==3&&ChEdit_CursorNum==6)
					{
						SkipFlag ^= 1;
						OnoffDisplayFunc(DSP_ROW6+(xEEPROMBuffer[CurrentChannel]%5),CII_COL23+1,(BYTE)SkipFlag); //메모리작업요망.
						ChEdit_CursorFunc();
						
						return;
					}
					if(OsdGrade==3&&ChEdit_CursorNum==0)
					{
						OsdGrade=2;
						return;
					}
				#endif				
					
				}
				#endif	//=====================================
				
				#ifdef Ccd_Vchip
				else if(OsdGrade==3 && TvMenuNum==tvmenu_Ccd)
				{
					OsdGrade=2;
					return;
				}
				#endif
				
				#ifdef Country2TVtype
				else	UpdownMenu(TvSetupStart+1,TvSetupEnd);
				#else
				else	UpdownMenu(TvSetupStart,TvSetupEnd);   
				#endif
				
				break;

			case TVMENU_TOOLS:
				UpdownMenu(TvToolsStart,TvToolsEnd);
				break;

			case TVMENU_SOUND:	//smpark 20030715
				UpdownMenu(TvSoundStart,TvSoundEnd);
				break;
		}
		OSDofftimer = (WORD)xEEPROMBuffer[OSDOFFTIME_buf]*200;
		OSDstatus = OSDexpire_timer;
		OsdGrade=1;
	}		
}

void	LeftRightKey()
{
	if(BarFlag)			//값 증감 -> 위 아래 범위 제한(if, BarFlag=1)
	{
		if(KEY_value==LeftKey)     
		{
			if(MenuVal>MenuMinVal) MenuVal--;
			//if(MenuVal>MenuMinVal&&MenuNum) MenuVal--;//??MenuNum
			else OSDstatus=MinMaxValueNotApply;
		}
		else if(KEY_value==RightKey)
		{
			if(MenuVal<MenuMaxVal) MenuVal++;
			//if(MenuVal<MenuMaxVal&&MenuNum) MenuVal++;
			else OSDstatus=MinMaxValueNotApply;
		} 
	}
	else				//값 증감 -> 회전.	(if, BarFlag=0)
	{	
		#if 1
		if(KEY_value==LeftKey)
		{
			if(MenuVal<=MenuMinVal) MenuVal=MenuMaxVal;
			else MenuVal--;
		}
		else if(KEY_value==RightKey)
		{
			if(MenuVal>=MenuMaxVal) MenuVal=MenuMinVal;
			else  MenuVal++;
		}		
		
		#else
		if(KEY_value==LeftKey)
		{
			if(MenuVal>MenuMinVal) MenuVal--;
			else MenuVal=MenuMaxVal;
		}
		else if(KEY_value==RightKey)
		{
			if(MenuVal<MenuMaxVal) MenuVal++;
			else MenuVal=MenuMinVal;
		}		
		#endif
	}

}

void	LeftRightKey10()		//증감폭 10step
{
	if(BarFlag)			//값 증감 -> 위 아래 범위 제한
	{
		if(KEY_value==LeftKey)     
		{
			if(MenuVal>MenuMinVal) MenuVal=-10;
			else OSDstatus=MinMaxValueNotApply;
		}
		else if(KEY_value==RightKey)
		{
			if(MenuVal<MenuMaxVal) MenuVal=+10;
			else OSDstatus=MinMaxValueNotApply;
		}
		
	}
	else				//값 증감 -> 회전.
	{	
		#if 1
		if(KEY_value==LeftKey)
		{
			if(MenuVal<=MenuMinVal) MenuVal=MenuMaxVal;
			else MenuVal-=10;
		}
		else if(KEY_value==RightKey)
		{
			if(MenuVal>=MenuMaxVal) MenuVal=MenuMinVal;
			else MenuVal+=10;
		}		
		#else
		if(KEY_value==LeftKey)
		{
			if(MenuVal>MenuMinVal) MenuVal=-10;
			else MenuVal=MenuMaxVal;
		}
		else if(KEY_value==RightKey)
		{
			if(MenuVal<MenuMaxVal) MenuVal=+10;
			else MenuVal=MenuMinVal;
		}		
		#endif
	}
}

#if 0
void	WordLeftRightKey(void)
{
	if(BarFlag)			//값 증감 -> 위 아래 범위 제한
	{
		if(KEY_value==LeftKey)     
		{
			if(WordMenuVal>MenuMinVal) WordMenuVal--;
			else OSDstatus=MinMaxValueNotApply;
		}
		else if(KEY_value==RightKey)
		{
			if(WordMenuVal<MenuMaxVal) WordMenuVal++;
			else OSDstatus=MinMaxValueNotApply;
		}
		
	}
	else				//값 증감 -> 회전.
	{	
		#if 1
		if(KEY_value==LeftKey)
		{
			if(WordMenuVal<=MenuMinVal) WordMenuVal=MenuMaxVal;
			else WordMenuVal--;
		}
		else if(KEY_value==RightKey)
		{
			if(WordMenuVal>=MenuMaxVal) WordMenuVal=MenuMinVal;
			else WordMenuVal++;
		}		
		#else
		if(KEY_value==LeftKey)
		{
			if(WordMenuVal>MenuMinVal) WordMenuVal--;
			else WordMenuVal=MenuMaxVal;
		}
		else if(KEY_value==RightKey)
		{
			if(WordMenuVal<MenuMaxVal) WordMenuVal++;
			else WordMenuVal=MenuMinVal;
		}		
		#endif
	}
}
#endif

void	leftright_svc()		// Right/Left Key || Volume Up/Down Key 	//2003-04-16 made by thkim
{
	if( (NowTopOsdOn==0)&&PowerONF )
	{
		volume_svc();
	}
	else if( (NowTopOsdOn==1)&&(GetTopMenu()!=MENU_TOOLS)&&(GetTopMenu()!=MENU_PIP) )
	{
		if(OsdGrade==0)
		{
			if(KEY_value==LeftKey)
			{
				if(MenuNum<=TopMenuStart) MenuNum=TopMenuEnd;
				else MenuNum--;
			}
			else if(KEY_value==RightKey)
			{
				if(MenuNum>=TopMenuEnd) MenuNum=TopMenuStart;
				else MenuNum++;
			}
			Display_TopMenuIcon();
			DisplayMenuWindow();
		}

		else if( (OsdGrade==1||OsdGrade==2)&&(MenuNum==menu_osd_Hposition) )
		{
				/*if(KEY_value==LeftKey)     
				{
					if(MenuVal>OSDHpos_min+1) MenuVal=MenuVal-5;
					else MenuVal=OSDHpos_min;
				}
				else if(KEY_value==RightKey)
				{
					if(MenuVal<MenuMaxVal) MenuVal=MenuVal+5;
					else MenuVal=OSDHpos_max;
				}
				*/
				if(KEY_value==LeftKey)     
				{
					if(MenuVal>OSDHpos_min+1) MenuVal=MenuVal-5;
					else MenuVal=OSDHpos_min+1;
				}
				else if(KEY_value==RightKey)
				{
					if(MenuVal<MenuMaxVal) MenuVal=MenuVal+5;
					else MenuVal=OSDHpos_max;
				}
				
			PutData();
			OSDstatus = SubMenuWindows2;
		}
		else if( (OsdGrade==1||OsdGrade==2)&&(MenuNum==menu_osd_Vposition) )
		{
			
				if(KEY_value==LeftKey)     
				{
					if(MenuVal>OSDVpos_min+4) MenuVal=MenuVal-5;
					else MenuVal=OSDVpos_min;
				}
				else if(KEY_value==RightKey)
				{
					if(MenuVal<MenuMaxVal-4) MenuVal=MenuVal+5;
					else MenuVal=OSDVpos_max;
				}
			PutData();
			OSDstatus = SubMenuWindows2;
		}
		
		else if( (OsdGrade==1||OsdGrade==2)&&((MenuNum!=menu_color_temperture)||(MenuNum!=menu_language)) )
		{
			LeftRightKey();
			PutData();
			OSDstatus = SubMenuWindows2;
		}
		else if( (MenuNum==menu_color_temperture)||(MenuNum==menu_language) )
		{
			LeftRightKey();

			PutData();
			//OSDstatus = ColorTempWindow;
			OSDstatus = SubMenuWindows2;
		}
		
	}
	else if( (NowTopOsdOn==1)&&(GetTopMenu()==MENU_TOOLS) )
	{
		if(OsdGrade==0)
		{
			if(KEY_value==LeftKey)
			{
				if(MenuNum<=TopMenuStart) MenuNum=TopMenuEnd;
				else MenuNum--;
			}
			else if(KEY_value==RightKey)
			{
				if(MenuNum>=TopMenuEnd) MenuNum=TopMenuStart;
				else MenuNum++;
			}
			Display_TopMenuIcon();
			DisplayMenuWindow();
		}
		else
		{	
			if(MenuNum==menu_auto_adjust)	//auto turn
			{
				LeftRightKey();
				Auto_Func();
			}
			else if(MenuNum==menu_factory_default)	//sys. initial
			{
				LeftRightKey();
				PutData();
				//DisplayMenuWindow();
				MenuBarValue();
				
				KEY_value = 0;//PowerKey;
		
				PowerOffTimer=0;
				KeyActionTimer=0;
				YouGoingInitialize=1;
				
				FactoryDftFlag=1;
				TransparencyOnfFlag=0;
				xEEPROMBuffer[FactoryReset_buf]=FactoryDftFlag;
				EepromSetQue(FactoryReset_adr,xEEPROMBuffer[FactoryReset_buf]);
			
				PowerOffsequence=SystemInitstatus;
				SystemInitialize();
			}
			else if(MenuNum==menu_dosmode)	//2003-08-26
			{
				if( (NowHfreq>=305&&NowHfreq<=325)&&(NowVfreq>=681&&NowVfreq<=721) 	\
				  ||(NowHfreq>=359&&NowHfreq<=399)&&(NowVfreq>=831&&NowVfreq<=871) ) 
				{
					ModeTrigger;
				}
				
				PutData();
				//DisplayMenuWindow();
				MenuBarValue();
			}
			else if(MenuNum==menu_AspectRatio)
			{
				if(NowHactive==PanelHerizontalsize) return;	//=1280이면 동작안함.(1:1입출력은 4:3으로 볼필요없기때문)
				LeftRightKey();
				PutData();
				AspectRatioService();
				//SetScalerZoomFactor(xEEPROMBuffer[MainSubInputSource]);
				OSDstatus = SubMenuWindows2;
			}
			//PutData();
			//OSDstatus = SubMenuWindows2;
			//DisplayMenuWindow();
		}
	}
	else if( (NowTopOsdOn==1)&&(GetTopMenu()==MENU_PIP) )
	{
		if(OsdGrade==0)
		{
			if(KEY_value==LeftKey)
			{
				if(MenuNum<=TopMenuStart) MenuNum=TopMenuEnd;
				else MenuNum--;
			}
			else if(KEY_value==RightKey)
			{
				if(MenuNum>=TopMenuEnd) MenuNum=TopMenuStart;
				else MenuNum++;
			}
			Display_TopMenuIcon();
			DisplayMenuWindow();////
		}
		else if( (OsdGrade==1||OsdGrade==2) )
		{
			
			LeftRightKey();
			
			if(MenuNum==menu_pip_enable)
			{
				PutData();
			
				PipEnableService();
			}
			else if(MenuNum==menu_pip_source)
			{
				
//				TunerTest();	//tuner가 없으면 건너뛰도록..
//				if(NoTunerFlag && PipInputSource==SourceTuner)
//				{
//						PipInputSource=SourceComposite;
//				}
//				else		PipInputSource=xEEPROMBuffer[PIPEN_SOURCE_buf]&0x03;	
				
				PipInputSource=xEEPROMBuffer[PIPEN_SOURCE_buf]&0x03;	
					
				if(PipOnOffFlag)PipSourceSelService();
			}
			else if(MenuNum==menu_pip_size)
			{
			}
			else if(MenuNum==menu_pip_Hposition)
			{
				
			}
			else if(MenuNum==menu_pip_Vposition)
			{
				
			}
			else if(MenuNum==menu_pip_AspectRatio)
			{
				PipAspectFlag=MenuVal;
				PipAspectSelFunc();//
			}
			else if(MenuNum==menu_pip_blend)
			{
				
			}

			
			if(MenuNum!=menu_pip_enable)PutData();
			OSDstatus = SubMenuWindows2;
		}
	}
}



void	tvleftright_svc()		// Right/Left Key || Volume Up/Down Key
{		
	if( (NowTopOsdOn==0)&&PowerONF )
	{
		volume_svc();
	}
	else if( (NowTopOsdOn==1) )
	{
		if(OsdGrade==0)
		{
			//if( xEEPROMBuffer[MainSubInputSource]==18 )
			if(CurrentFunction==Tuner_mode)
			{	// Tuner mode일 경우 tv 메뉴활성
				
				if(KEY_value==LeftKey)
				{              
					if(TvMenuNum<=TvTopMenuStart) TvMenuNum=TvTopMenuEnd;
					else TvMenuNum--;
				}              
				else if(KEY_value==RightKey)
				{              
					if(TvMenuNum>=TvTopMenuEnd) TvMenuNum=TvTopMenuStart;
					else TvMenuNum++;
				}       	       
			        	       
			}
			else	// av1, av2일때	//2003-08-18, tv 메뉴 비활성
			{
				if(KEY_value==LeftKey)
				{              
					if(TvMenuNum<=TvTopMenuStart) TvMenuNum=TvTopMenuEnd;
					else if(TvMenuNum==TVMENU_TOOLS) TvMenuNum=TvTopMenuStart;
					else TvMenuNum--;
				}              
				else if(KEY_value==RightKey)
				{              
					if(TvMenuNum>=TvTopMenuEnd) TvMenuNum=TvTopMenuStart;
					else if(TvMenuNum==TvTopMenuStart) TvMenuNum=TVMENU_TOOLS;
					else TvMenuNum++;
				}       	       
			}
			 
			Display_TvTopMenuIcon();
			DisplayMenuWindow();
		}

		else if( (OsdGrade==1||OsdGrade==2)&&(GetTvTopMenu()==TVMENU_PICTURE) )
		{
			LeftRightKey();
			PutData();
			if(TvMenuNum==tvmenu_tint )	Hue_ColorBar();
			OSDstatus = SubMenuWindows2;
		}
		else if( (NowTopOsdOn==1)&&(GetTvTopMenu()==TVMENU_SETUP) )
		{
			LeftRightKey();
			
			if((TvMenuNum==tvmenu_country) && (OSDstatus != CountryWindow))
			{	
				#ifdef PalCountry_ChinaOnly	
				return;
				#endif
				OsdDataWindowClear();				
				SubWindowDisplay();
				
				MenuSel();
				OSDstatus = CountryWindow;
			}
			else if(TvMenuNum==tvmenu_auto_setup)
			{
				//autosearch start//		
				
				TunerProcessing=20;
				
				Mute_SoundOff;
				OsdDataWindowClear();
				OSD230SeqSend(ATTR_ROW4,CII_COL0,OSD_WHITE,30);
				SubWindowDisplay();	
				OSDstatus = AutoChSetupWindow;
			}
			//**************************************************************************************//
			else if( (TvMenuNum==tvmenu_channel_edit) )
			{
			//------------------------------------------------------------------------------
			#if defined (USE_NTSCtuner)
			//------------------------------------------------------------------------------
				if(OsdGrade==1)
				{
					OsdDataWindowClear();
					OsdDataWindowClear2();
					ChEdit_WindowOff();	//window4 off
					SubWindowDisplay();
					MenuSel();
				}
				else if(OsdGrade>=2)
				{
					#ifdef OsdMenuType1
					OnoffDisplayFunc(DSP_ROW5+(xEEPROMBuffer[CurrentChannel]%5),CII_COL20,(BYTE)ToggleChMask()); 
					#else
					OnoffDisplayFunc(DSP_ROW6+(xEEPROMBuffer[CurrentChannel]%5),CII_COL20,(BYTE)ToggleChMask()); 
					#endif
				}
				
				//OSDstatus = AutoChSetupWindow;
			//------------------------------------------------------------------------------
			#elif defined (USE_PALSECAMtuner)
			//------------------------------------------------------------------------------
				#ifndef PalCountry_ChinaOnly//++++++++++++++++++++++++++++++++++
				if(OsdGrade==1)
				{
					OsdDataWindowClear();
					OsdDataWindowClear2();
					SubWindowDisplay();
					//MenuSel();
				}
				else if((KEY_value==RightKey)&&(OsdGrade>=2))
				{
					OsdGrade=3;
					if(ChEdit_CursorNum==6)
					{
						ChEdit_WindowOff();
						ChEdit_CursorNum=0;
						ChEdit_CursorFunc();
						
						
					}
					else if(ChEdit_CursorNum!=6)	//ChEdit_CursorNum 유효범위 : 1~5
					{
						ChEdit_CursorNum++;
						
						
						if(0<ChEdit_CursorNum&&ChEdit_CursorNum<=5)		//name 입력.
						{
							
							ChEdit_CursorFunc();
							
							if(EditWindowFlag&&(ChEdit_CursorNum!=1)) ChEdit_CharFunc();
						}
						else if(ChEdit_CursorNum==6)	//name이 끝나고 skip menu로 이동.
						{
							ChEdit_WindowOff();
							ChEdit_CursorFunc();
							
							if(EditWindowFlag) ChEdit_CharFunc();
						}
						else if(ChEdit_CursorNum==0)	//name이 끝나고 skip menu로 이동.
						{
							ChEdit_WindowOff();
							ChEdit_CursorFunc();
						}
						else	ChEdit_CursorNum=0;
						
						EditWindowFlag=0;
					}

				}
				else if((KEY_value==LeftKey)&&(OsdGrade>=2))
				{
					OsdGrade=3;
					if( ChEdit_CursorNum==0 )	//ChEdit_CursorNum=0이면 skip menu..
					{
						ChEdit_WindowOff();
						ChEdit_CursorNum=6;
						ChEdit_CursorFunc();
						
					}
					else if(ChEdit_CursorNum!=0)
					{
						ChEdit_CursorNum--;
						
						if(0<ChEdit_CursorNum&&ChEdit_CursorNum<=5)		//name 입력.
						{
							ChEdit_CursorFunc();
							if(EditWindowFlag) ChEdit_CharFunc();
						}
						else if(ChEdit_CursorNum==6)	//name이 끝나고 skip menu로 이동.
						{
							ChEdit_WindowOff();
							ChEdit_CursorFunc();
						}
						else if(ChEdit_CursorNum==0)
						{
							ChEdit_WindowOff();
							ChEdit_CursorFunc();
							
							if(EditWindowFlag) ChEdit_CharFunc();
						}
						else	ChEdit_CursorNum=0;
						
						EditWindowFlag=0;

					}
				}
				else	ChEdit_CursorNum=0;
				
				OSDstatus = AutoChSetupWindow;
				#else	//++++++++++++++++++++++++++++++++++
				//------------------------------------------------------------------------------
				if(OsdGrade==1)
				{
					OsdDataWindowClear();
					OsdDataWindowClear2();
					ChEdit_WindowOff();	//window4 off
					SubWindowDisplay();
					MenuSel();
				}
				else if(OsdGrade>=2)
				{
					#ifdef OsdMenuType1
					OnoffDisplayFunc(DSP_ROW5+(xEEPROMBuffer[CurrentChannel]%5),CII_COL20,(BYTE)ToggleChMask()); 
					#else
					OnoffDisplayFunc(DSP_ROW6+(xEEPROMBuffer[CurrentChannel]%5),CII_COL20,(BYTE)ToggleChMask()); 
					#endif
				}
				
				//OSDstatus = AutoChSetupWindow;
				//------------------------------------------------------------------------------
				#endif	//++++++++++++++++++++++++++++++++++
				
			//-------------------------------------------------------------------------------
			#endif
			//-------------------------------------------------------------------------------
			}
			//**************************************************************************************//
			
			#if defined (USE_NTSCtuner)
			else if(TvMenuNum==tvmenu_antena_input)		//이 메뉴는 NTSC에서만 존재..
			{
				PutData();
				//youngdo 2003.8.19	OSDstatus = SubMenuWindows2;	
				Display_MenuBarPercent();	//youngdo 2003.8.19
				
				//TvMenuNum = GetTvTopMenu();
				//TvMenuNum=tvmenu_finetune;
				//TvMenuBarValue();	//2003-09-30
				//Display_MenuBarPercent();
				//TvMenuNum=tvmenu_antena_input;

			}
			#endif
			else if(TvMenuNum==tvmenu_finetune)
			{
				PutData();				
				Display_MenuBarPercent();	//youngdo 2003.8.19
				//MenuSel();	//2003-09-09	//2003-09-30 removed
				//youngdo 2003.8.19	OSDstatus = SubMenuWindows2;
			}
			
			#ifdef Ccd_Vchip
			else if(TvMenuNum==tvmenu_Ccd)
			{
				if(OsdGrade==1)
				{
					OsdDataWindowClear();
					//OsdDataWindowClear2();
					SubWindowDisplay();
					SubMenuVal = ccd_caption;
					MenuSel();
					
					CcdCaptionSelFunc();	//처음 CCD 메뉴 진입시 기존 세팅값 표시.
				}
				else if((KEY_value==LeftKey || KEY_value==RightKey)&&(OsdGrade>=2))
				{
					OsdGrade=3;
					
					switch(SubMenuVal)
					{
						case ccd_caption:
							(BYTE)CcdCaptionFlag=xEEPROMBuffer[Ccd_buf]&0x01;
							CcdCaptionFlag ^=1;
							CcdCaptionSelFunc();
							break;
						case ccd_mode:
							(BYTE)CcdModeFlag=(xEEPROMBuffer[Ccd_buf]&0x02)>>1;
							CcdModeFlag ^=1;
							CcdModeSelFunc();
							break;
						case ccd_channel:
							(BYTE)CcdChannelFlag=(xEEPROMBuffer[Ccd_buf]&0x04)>>2;
							CcdChannelFlag ^=1;
							CcdChannelSelFunc();
							break;
						case ccd_field:
							(BYTE)CcdFieldFlag=(xEEPROMBuffer[Ccd_buf]&0x08)>>3;
							CcdFieldFlag ^=1;
							CcdFieldSelFunc();
							break;
						case ccd_display:
							(BYTE)CcdDisplayFlag=(xEEPROMBuffer[Ccd_buf]&0x10)>>1;
							CcdDisplayFlag ^=1;
							CcdDisplaySelFunc();
							break;
					}
				}
			}
			else if(TvMenuNum==tvmenu_Vchip)
			{
				if(OsdGrade==1)
				{
					OsdDataWindowClear();
					OsdAttrClear();
					SubWindowDisplay();
					//MenuSel();
				}
			}
			#endif
			
			//PutData();			
		}
		else if( (OsdGrade==1||OsdGrade==2)&&(GetTvTopMenu()==TVMENU_TOOLS) )
		{
			if(TvMenuNum == tvmenu_blue_screen && CurrentFunction==Svideo_mode) return;
			
			if(TvMenuNum == tvmenu_sleep)	LeftRightKey10();
			//else if(TvMenuNum==tvmenu_lang) {LeftRightKey();PutData();Display_MenuBarPercent();OSDstatus = SubMenuWindows2;return;}
			else	LeftRightKey();
			
			PutData();
			
			if(TvMenuNum==tvmenu_screen_mode)
			{
				InvertOff;	//2003-08-20
				//MUTEON;
				TvAspectRatioService();
				InvertOn;
				//MUTEOFF;
			}
			//PutData();
			OSDstatus = SubMenuWindows2;
		}
		else if( (OsdGrade==1||OsdGrade==2)&&(GetTvTopMenu()==TVMENU_SOUND) )	//smpark
		{
			LeftRightKey();
			PutData();
			OSDstatus = SubMenuWindows2;
		}
	}
}

void	volume_svc()
{
		OSDWindows = VolumeWindow;
		OSDstatus = VolumeDisplay;
		OsdMode = volume_mode;
		OsdGrade = 0;
		//NowVolumOsdOn = 1;	//어떻게 이용할지 정의필요!!!
		
		WriteScaler(0x73,0x20);	//50%	//2003-11-13
		
		if(MENUstatus==VolumeDisplay)	//volume 윈도우가 온상태에선 볼륨바만 보인다.
		{
			OSDstatus=ValueDisplay;
			MENUstatus = VolumeDisplay;
			if(KEY_value==LeftKey)
			{
				if(MenuVal>MenuMinVal) --MenuVal;
				else OSDstatus=MinMaxValueNotApply;
			}
			else if(KEY_value==RightKey)
			{
				if(MenuVal<MenuMaxVal) ++MenuVal;
				else OSDstatus=MinMaxValueNotApply;
			}
			//xEEPROMBuffer[VOLUME_buf]=MenuVal;//
			//EepromSetQue(VOLUME_adr,xEEPROMBuffer[VOLUME_buf]);//
			//PutVolumePWM();//
			PutData();
		}
		else if(MENUstatus==MuteDisplay)
		{
//			OSDSelKeyin=0;
			OSDcharacters = VolumeChars;
			OSDstatus = ReVolumeDisplay;
			//OsdMode = volume_mode;//
			SoundMuteOnFlag=0;
			Mute_SoundOn;
			PutVolumePWM();
			SoundMuteOnFlag=0;
		}
		else if(MENUstatus!=ValueDisplay)
		{
//			OSDSelKeyin=0;
			OSDWindows = VolumeWindow;
			OSDcharacters = VolumeChars;
			//OsdMode = volume_mode;//
			OSDstatus = VolumeDisplay;
			SoundMuteOnFlag=0;
			Mute_SoundOn;
			PutVolumePWM();
			SoundMuteOnFlag=0;
		}
}

#ifdef TestCH
unsigned int cnt=0;	
unsigned int up_cnt=0;	
unsigned int dn_cnt=0;	
#endif


void MenuPan(void)
{
	idata bit temp;
	if(KEY_value==0) return;
				
	//TV auto channel searching중 일때 ->  MenuKey/power key만 동작하도록.
	if(NowAutoChannelSearching)
	{
		if(KEY_value!=PowerKey&&KEY_value!=MenuKey)
		{
			KEY_value = 0;
			return;
		}
	}
	
	if(AutoFlag) 
	{
		if(KEY_value!=PowerKey)
		{
			KEY_value = 0;
			return;
		}
	}
	
	if(PowerOnsequence == NoVideoStatus || DpmsFlag)
	{
		if(KEY_value!=PowerKey&&KEY_value!=SelKey)
		{
			KEY_value = 0;
			return;
		}
	}
	
	/*
	if( (OSDWindows==OSDHotkeyMessageWindow)&&(OSDcharacters==OSDHotkeyMsgChar)&&(AutoToggle)&&(KEY_value!=AutoKey) )
	{
		OSDstatus = OsdRamClear;
		Osd_onoff();
		LED_OFF;
		KEY_value=0;
		return;
	}
	*/	
	
//test2004-07-15					if(KeyActionTimer) {KEY_value=0;return;}
	if( (KeyTimeBuffer1<KEY_chatteringTime)&&(KeyTimeBuffer0<KEY_chatteringTime) ) KeyActionTimer=20;	//100ms(20*5m)	
		
	switch(KEY_value)
	{
		case	MenuKey:
			if(PowerOnsequence != GeneralStatus) {			// +jwshin 040812 TV 모드 전환 후 바로 menu_key를 누를 경우 OSD 깨지는 증상 제거...
				KEY_value = 0;
				return;
			}
		
			if( (OSDcharacters==CheckSignalCableChars)||(OSDcharacters==AnalogPowerSaverChars) )
			//	||((NoExistHfreq||NoExistVfreq)&&(~DpmsPipFlag&&SubWindowMsgFlag)) )
			{
				KEY_value = 0;
				return;
			}
			
			if(!NowTopOsdOn)	{OSDstatus = OsdRamClear;OsdService();}	//2003-08-22
			
			if( (xEEPROMBuffer[MainSubInputSource]!=10)&&(xEEPROMBuffer[MainSubInputSource]!=14)&&(xEEPROMBuffer[MainSubInputSource]!=18) )
			{	// PC mode
				if(OsdGrade==0)OsdOnoff();
				else if(OsdGrade==1)
				{
					//MenuNum = GetTopMenu();
					OsdAttrClear();
					//ClearMenuDescription();	//clear information of select menu
				}
				else if(OsdGrade==2)
				{
					MenuSel();
				}
				MenuNum = GetTopMenu();
				OsdAttrClear();
				ClearMenuDescription();	//clear information of select menu
				//DisplayMenuWindow();
			}
			else	// Video mode
			{
				RemAddBtn=0;		// Channel Edit 에서 add 버튼 동작 
				if( OsdGrade==0 )OsdOnoff();
				else if(OsdGrade==1)
				{
					//TvMenuNum = GetTvTopMenu();
					OsdAttrClear();
					//OsdDataClear();
					//ClearMenuDescription();	//clear information of select menu
				}
				else if(OsdGrade>=2)
				{
					if(TvMenuNum==tvmenu_country) 
					{
						if(xEEPROMBuffer[SystemCountry]!=EEPROM_Read(SystemCountry_adr)) 
						{
							EepromSetQue(SystemCountry_adr,xEEPROMBuffer[SystemCountry]);
							
							OSD230SeqSend(ATTR_ROW3,CII_COL9,0x01,Wait_Sizeof[xEEPROMBuffer[LANGUAGE_buf]]); //Attribute data
							OSD230PtrSend(DSP_ROW3,CII_COL9,Wait[xEEPROMBuffer[LANGUAGE_buf]],Wait_Sizeof[xEEPROMBuffer[LANGUAGE_buf]]); //Display data
							TVParameterInit();
							//SetColorSystem();
							TVCountrySet();
							
							TunerProcessing	=2;
						}
						OsdDataWindowClear();
					}
					if(TvMenuNum==tvmenu_auto_setup) 
					{
						SoundMuteTvTimer=0;
						TunerProcessing=1;				
						NowAutoChannelSearching=0;
						OSDstatus = OSDexpire_timer;
						OsdDataWindowClear();
					}
					if(TvMenuNum==tvmenu_channel_edit)
					{
						OsdDataWindowClear();
						Display_AdjustInfo();
					}
					#ifdef Ccd_Vchip
					if(TvMenuNum==tvmenu_Ccd||TvMenuNum==tvmenu_Vchip) 
					{
						OsdDataWindowClear();
					}
					#endif
					ChEdit_CursorNum=0;
				}
		
				TvMenuNum = GetTvTopMenu();
				OsdAttrClear();
				ClearMenuDescription();	//clear information of select menu

				#ifdef USE_PALSECAMtuner
					ChEdit_WindowOff();
				#elif defined (USE_NTSCtuner)&& !defined(OsdMenuType1)
					xOSD_WIN_REG[10]=WIN_COL0|WIN_ENA|WIN_INT&WIN_UNSHD;	//window4 display (for channel edit)
				#endif
				Display_TvTopMenuIcon();
				IconSel();
				DisplayMenuWindow();
			}
			
			#if 0
				//if(OsdGrade!=0)OsdGrade--;	// menu key 누르면 바로 위단계로.. 
			#else
				if(OsdGrade!=0)OsdGrade=0;	//∵ menu key 누르면 무조건 최상위로.. 
			#endif
					
			if(OsdGrade==0)AutoToggle=1;
			OSDofftimer = (WORD)xEEPROMBuffer[OSDOFFTIME_buf]*200;
			KEY_value = 0;			
			break;

		
		case	SelKey:
			
			Mute_SoundOff;//
			idelay5m(30);
			
			#if 0
//			if( (NoExistHfreq||NoExistVfreq)&&(~DpmsPipFlag&&SubWindowMsgFlag) ) {KEY_value=0;return;}
			#else
			if( (NoExistHfreq||NoExistVfreq)&&(~DpmsPipFlag||SubWindowMsgFlag)&&!PipOnOffFlag)
			{
				KEY_value = 0;
				DpmsPipFlag=0;
				PowerOnsequence = MainPowerON;
				PowerOnTimer = 5;
			}
			else if( (NoExistHfreq||NoExistVfreq)&&(~DpmsPipFlag||SubWindowMsgFlag)&&PipOnOffFlag ) 
			{
				DpmsPipFlag=0;
				PipOnOffFlag=0;
				xEEPROMBuffer[PIPEN_SOURCE_buf]= ( (((BYTE)PipOnOffFlag&0x01)<<4)&0xf0 +(xEEPROMBuffer[PIPEN_SOURCE_buf]&0x0f) );
				EepromSetQue(PIPEN_SOURCE_adr,xEEPROMBuffer[PIPEN_SOURCE_buf]);
				PowerOnsequence = MainPowerON;
				//PowerOnTimer = 5;
				return;
			}
			#endif
			
			
			if(PipOnOffFlag&!DpmsFlag)	//pip on 상태에서는 pip 입력소스 변경.
			{
				if(NowTopOsdOn||SubWindowMsgFlag)
				{				// osd window on 상태에서는 osd off	//2003-08-25
					NowTopOsdOn = 0;
					OSDWindows = 0;
					SubWindowMsgFlag=0;
					OSDstatus = OSDoff;
					Osd_onoff();
				}

				if(PipInputSource<MaxPipNum-1)	PipInputSource++;
				else PipInputSource=SourceComposite;
				
				if(PipInputSource==SourceTuner && NowTopOsdOn==0) TunerTest();	//tuner가 없으면 건너뛰도록..
				if(NoTunerFlag && PipInputSource==SourceTuner)
				{
						PipInputSource=SourceComposite;
				}
					
				
				PipSourceSelService();
				//PutData();//test
				xEEPROMBuffer[PIPEN_SOURCE_buf]= ( (PipInputSource&0x03) + (xEEPROMBuffer[PIPEN_SOURCE_buf]&0xf0) );
				EepromSetQue(PIPEN_SOURCE_adr,xEEPROMBuffer[PIPEN_SOURCE_buf]);
				KEY_value = 0; return;
			}
			//else if(!PipOnOffFlag || (PipOnOffFlag&DpmsFlag) )	//pip off상태 또는 on,+ dpms
			else if(!PipOnOffFlag)
			{
				TvMenuNum=0;
				switch(CurrentFunction)
				{			//2003-08-08, Changed SelKey, 전환순서: RGB->(DVI)->TUNER->COMPOSITE->S-VIDEO->(SCART)
					case Rgb_mode://RGB->(DVI)->Tuner...
					case PipRnC_mode:
					case PipRnS_mode:
					case PipRnT_mode:
						#ifdef DVI_USE
						ChangeToDviOnly();
						#else
						
						TunerTest();	//tuner가 없으면 건너뛰도록..
						if(NoTunerFlag)
						{
								ChangeToCompositeOnly();
								break;
						}
						
						ChangeToTunerOnly();
						#endif
						break;
					
					#ifdef DVI_USE
					case Dvi_mode://DVI
						ChangeToRgbOnly();
						break;
					#endif
					
					case Composite_mode://COMPOSITE
						ChangeToSvideoOnly();
						break;
						
					case Svideo_mode://S_VIDEO
						#if defined(USE_SCART)	
						ChangeToScartOnly();
						#else
						ChangeToRgbOnly();
						#endif											
						break;

					#ifdef USE_SCART
					case Scart_mode://SCART
						ChangeToRgbOnly();
						break;
					#endif
						
					case Tuner_mode://TUNER
						ChangeToCompositeOnly();
						break;
						
					default:
						ChangeToRgbOnly();
						break;
				}
			}
			
			PipOnOffFlag=0;//
			
			OSDofftimer = (WORD)xEEPROMBuffer[OSDOFFTIME_buf]*200;
			KEY_value=0;
		
			break;
		
		
		
		case	DownKey://==ChannelDown
		case	UpKey:	//==ChannelUp

	 		if( !NowTopOsdOn&&(CurrentFunction==PipRnC_mode||CurrentFunction==PipRnS_mode) )
	 			//|| ((NoExistHfreq||NoExistVfreq)&&(~DpmsPipFlag||SubWindowMsgFlag)&&xEEPROMBuffer[MainSubInputSource]==52) )
			{	// PIP(av1,2) mode
				KEY_value=0;
				return;
			}
			
			if(!NowTopOsdOn)
			{
				if(	(CurrentFunction==Tuner_mode
					||CurrentFunction==PipRnT_mode
					||CurrentFunction==PipDnT_mode)		\
				      &&(MENUstatus==TVchannelDisplay||MENUstatus==NotBUSY||MENUstatus==NowStatusDisplay	\
					||MENUstatus==VolumeDisplay||MENUstatus==MuteDisplay||MENUstatus==ChannelStatusDisplay 
					|| MENUstatus==RecallWindowDisplay || MENUstatus==AddDelWindowDisplay)	)

				{
					if(KeyStepTimer) {KEY_value=0;return;}
					KeyStepTimer=100;	//400ms(80*5m) 채널이 변화하여, 모든 동작이 완료될 시간을 위함.

					Mute_SoundOff;
					//if(CurrentFunction==Tuner_mode && !RepeatCodeBit)	MUTEON;	//main background mute
					if(CurrentFunction==Tuner_mode && !KeyContinueFlag)	MUTEON;	//main background mute
															
					// OSD Clear smpark 20030822 //-------!!
					xOSDW_OPTION[1]=0x00;	// smpark 20030827
					//SoundTimer=500;			// smpark 20030827

					NowTopOsdOn = 0;
					OSDWindows = 0;
					OSDstatus = OSDoff;
					IntOsdOff();//2004-06-28
	                //--------------------------------------
					SoundMuteTvTimer=0;
					TunerProcessing=1;
	
					// sound check option clear				
					SoundMode=0;
//					SoundModeCnt=0;
					PreSoundMode=0xff;	// smpark 20030811
					
					// Sound 설정 초기화 // smpark 20030829
					SoundProcessStatus = SoundType_MONO;
					MTS_Stereo=MTS_NONE;
					MTS_Bilingual=MTS_NONE;
					SoundTimer=500;
					
					#ifndef FrequncyTableType	//++++++++++++++++++++++++

					#if defined (USE_NTSCtuner)
					if(KEY_value==UpKey) 
					{		//upkey
					
						xEEPROMBuffer[PreChannel]=Backchannel=xEEPROMBuffer[CurrentChannel];
						xEEPROMBuffer[CurrentChannel]=Frontchannel;
					}
					else  
					{						//down key
						xEEPROMBuffer[PreChannel]=Frontchannel=xEEPROMBuffer[CurrentChannel];
						xEEPROMBuffer[CurrentChannel]=Backchannel;
					}
					
					#elif defined (USE_PALSECAMtuner)
					if(KEY_value==UpKey) 
					{		//upkey
						if(AddDelFlag==0)	Backchannel=xEEPROMBuffer[PreChannel]=xEEPROMBuffer[CurrentChannel];
						xEEPROMBuffer[CurrentChannel]=Frontchannel;
						UpDownChannel=1;	//2004-06-09
					}
					else  
					{						//down key
						if(AddDelFlag==0)	Frontchannel=xEEPROMBuffer[PreChannel]=xEEPROMBuffer[CurrentChannel];
						xEEPROMBuffer[CurrentChannel]=Backchannel;
						UpDownChannel=0;
					}
					#endif
					
					#else	//+++++++++++++++++++++++++++++
					if(KEY_value==UpKey) 
					{		//upkey
					
						xEEPROMBuffer[PreChannel]=Backchannel=xEEPROMBuffer[CurrentChannel];
						xEEPROMBuffer[CurrentChannel]=Frontchannel;
					}
					else  
					{						//down key
						xEEPROMBuffer[PreChannel]=Frontchannel=xEEPROMBuffer[CurrentChannel];
						xEEPROMBuffer[CurrentChannel]=Backchannel;
					}
					#endif	//+++++++++++++++++++++++
					
					//
					OSDWindows = TunerSubWindow;
					if(CurrentFunction==Tuner_mode)			OSDcharacters = ChannelNumChars;
					else 																OSDcharacters = PipRgbTunerChars;
					OSDstatus = TVchannelDisplay;

					RemoconDigit=0;	// smpark 20030827
					AddDelFlag=0;
					SubWindowMsgFlag=0;//
					
					KEY_value=0;		
					
					
					
					#ifdef TestCH	//test
					{
						cnt =up_cnt =dn_cnt = 0;
					}
					#endif
					
					return;
				}
			}


			if( (SubWindowMsgFlag)&&(MENUstatus!=OSDHotkeyMessageWindow) )
			{

				if(OsdMode!=volume_mode)
				{	
					OSDstatus = OsdRamClear;
					Osd_onoff();
				}
				KEY_value=0;return;
			}
			
			if( MENUstatus==OSDHotkeyMessageWindow )
			{
				OSDstatus = OsdRamClear;
				Osd_onoff();
				AutoToggle=1;
				KEY_value=0;
				return;
			}


			#if 0
			if( KEY_value==UpKey&&OsdGrade==0) {KEY_value=0;return;}
			#endif
			
			
			updown_svc();

			if(NowTopOsdOn&& (xEEPROMBuffer[MainSubInputSource]!=10)&&(xEEPROMBuffer[MainSubInputSource]!=14)&&(xEEPROMBuffer[MainSubInputSource]!=18) )
			{	// PC mode
				Display_MenuDescription();
			}
			else if( (xEEPROMBuffer[MainSubInputSource]==10)||(xEEPROMBuffer[MainSubInputSource]==14)||(xEEPROMBuffer[MainSubInputSource]==18) )
			{	// Video mode
				if((TvMenuNum!=tvmenu_channel_edit)&&(OsdGrade!=2)) Display_TvMenuDescription();
			}
			
			Display_MenuBarPercent();
			
			MenuSel();

			OSDofftimer = (WORD)xEEPROMBuffer[OSDOFFTIME_buf]*200;
			KEY_value=0;
			
			break;
		
			
			
			
			
		case	LeftKey://==VolumeDown	
		case	RightKey://==VolumeUp

//			RemVolume=0;
			
			//if( (SubWindowMsgFlag)&&(OSDstatus!=VolumeWindow || OSDstatus!=MuteDisplay
			//	|| OSDstatus!=ReMuteDisplay || OSDstatus!=ReVolumeDisplay) )
			
			if( (MENUstatus==Nosignal_Display)||(OSDcharacters==CheckSignalCableChars) )
			//	|| ((NoExistHfreq||NoExistVfreq)&&(~DpmsPipFlag)) )//||SubWindowMsgFlag)) )
			{
				KEY_value=0;return;
			}
			if( (xEEPROMBuffer[MainSubInputSource]!=10)&&(xEEPROMBuffer[MainSubInputSource]!=14)&&(xEEPROMBuffer[MainSubInputSource]!=18) )
			{
				leftright_svc();
			}
			else	tvleftright_svc();
			//DisplayMenuWindow();
			
			IconSel();
			
			#ifdef test_function
			if(OSDWindows != VolumeWindow)	MenuNum_display();//test
			#endif
			
			if(OsdGrade==0)AutoToggle=1;
			KEY_value=0;
			OSDofftimer = (WORD)xEEPROMBuffer[OSDOFFTIME_buf]*200;

//			RemVolume=1;
			break;
		


		case	AutoKey:
			

			if( (xEEPROMBuffer[MainSubInputSource]==10)||(xEEPROMBuffer[MainSubInputSource]==14)||(xEEPROMBuffer[MainSubInputSource]==18) )
				//||SubWindowMsgFlag )//(OSDcharacters==CheckSignalCableChars)||(OSDcharacters==AnalogPowerSaverChars) )		
			{
				#ifdef USE_TTX
		 		SDA555xModeChange();
				#endif
				MuteExe();
				KEY_value=0;
				return;
			}

			if(xEEPROMBuffer[MainSubInputSource]>=20)
			{
				MuteExe();
				KEY_value=0;  
				return;
			}
		
			temp=AutoToggle;
			OSDstatus =OSDoff;
			OsdService();	//OSDoff
			AutoToggle=temp;

			OSDstatus=OSDHotkeyMessageWindow;
			OSDWindows=OSDHotkeyMessageWindow;
			OSDcharacters = OSDHotkeyMsgChar;
			OsdService();  
		
			AutoToggle^=1;
			
			if(AutoToggle)AutoFlag = 1;
			
			KEY_value=0;
			
			break;
		
		case	PowerKey:
			#if 0	//test
//			xEEPROMBuffer[VOLUME_buf]=50;//test
//			EepromSetQue(VOLUME_adr,xEEPROMBuffer[VOLUME_buf]);//test
			#endif

			power_onoff();
			KEY_value = 0;
			break;

		//--------------------------------------------------------------
		case OSD_ADD:	// smpark 20030808
			
			if(NowTopOsdOn)
			{				//OSD EDIT에서 toggle
				if((TvMenuNum==tvmenu_channel_edit)&&(RemAddBtn==1))
				{
					/*#ifdef OsdMenuType1
					if((BYTE)CheckChMask(xEEPROMBuffer[CurrentChannel])){		
						OnoffDisplayFunc(DSP_ROW5+(xEEPROMBuffer[CurrentChannel]%5),CII_COL20,0);
						ToggleChMask();
					}else{
						OnoffDisplayFunc(DSP_ROW5+(xEEPROMBuffer[CurrentChannel]%5),CII_COL20,1);
						ToggleChMask();
					#else 
					*/
					if((BYTE)CheckChMask(xEEPROMBuffer[CurrentChannel]))
					{		
						OnoffDisplayFunc(DSP_ROW6+(xEEPROMBuffer[CurrentChannel]%5),CII_COL20,0);
						//ToggleChMask();
					}
					else
					{
						OnoffDisplayFunc(DSP_ROW6+(xEEPROMBuffer[CurrentChannel]%5),CII_COL20,1);
						//ToggleChMask();
					//#endif
					}
					ToggleChMask();
					
				}
			}
			else
			{				// TV 채널 toggle	(remocon)
				TVChannelAdd();
//				DisplayChannelStatus(1 );
			}
			AddDelFlag=1;
			
			KEY_value=0;
			break;

		default:
			KEY_value=0;
			break;		
		//--------------------------------------------------------------	
				
	}
}	


//-----------------------------------------------------------------------------------------------
#ifdef BURNING_TEST
void	WriteRGBMute(BYTE Rval, Gval, Bval)	//2003-09-02
{
	WriteScaler(0x9b,Rval);	WriteScaler(0x9c,Gval);	WriteScaler(0x9d,Bval);	
	idelay5m(500);
}

void	RGBPageMute(void)	//2003-09-02
{
//	LED_OFF;
	WriteRGBMute(255,0,0);		//R
	WriteRGBMute(0,255,0);		//G
//	LED_ON;
	WriteRGBMute(0,0,255);		//B
//	WriteRGBMute(255,255,0);	//Yellow
//	LED_OFF;
//	WriteRGBMute(0,255,255);	//Cyan
//	WriteRGBMute(255,0,255);	//Magenta
//	LED_ON;
//	WriteRGBMute(255,255,255);	//White
//	WriteRGBMute(0,0,0);		//Black
}

#if 0	
void	RGBMute(BYTE color_val, BYTE Rval, BYTE Gval, BYTE Bval)	//2003-09-02
{
	BYTE idata	i,swap_buf;
	i=swap_buf=0;
	
	switch(color_val)
	{
		case	0:	swap_buf=Rval;	Rval=0;	break;
		case	1:	swap_buf=Gval;	Gval=0;	break;			
		case	2:	swap_buf=Bval;	Bval=0;	break;
	}
	for(i=swap_buf;i<255;i++)
	{
		switch(color_val)
		{
			case	0:	Rval=i;	break;
			case	1:	Gval=i;	break;			
			case	2:	Bval=i;	break;
		}
		WriteScaler(0x9b,Rval);	WriteScaler(0x9c,Gval);	WriteScaler(0x9d,Bval);	idelay5m(3);
		if(i==0)LED_OFF;
	}
	for(i=255;i>swap_buf;i--)
	{
		switch(color_val)
		{
			case	0:	Rval=i;	break;
			case	1:	Gval=i;	break;			
			case	2:	Bval=i;	break;
		}
		WriteScaler(0x9b,Rval);	WriteScaler(0x9c,Gval);	WriteScaler(0x9d,Bval);	idelay5m(3);
		if(i==255)LED_ON;
	}
}
#endif

void	BunrningProcess(void)	// by thkim, 2003-09-01
{
	OSDstatus = OsdRamClear;
	Osd_onoff();

	WriteScaler(0x2F,BIN_TO_BYTE(0,0,0,1,0,1,0,0));	//freerun mode
	MUTEON;
	
	#if 1
	RGBPageMute();	// 한 화면에 한 색깔씩 표현.
	#endif 
	#if 0	// Liner하게 변화.	
	RGBMute(0,0,0,0);
	RGBMute(1,0,0,0);
	RGBMute(2,0,0,0);
		
	RGBMute(0,112,0,0);	RGBMute(1,112,0,0);	RGBMute(2,112,0,0);
	RGBMute(0,0,112,0);	RGBMute(1,0,112,0);	RGBMute(2,0,112,0);
	RGBMute(0,0,0,112);	RGBMute(1,0,0,112);	RGBMute(2,0,0,112);
	RGBMute(0,112,255,0);	RGBMute(1,112,255,0);	RGBMute(2,112,255,0);
	RGBMute(0,255,112,0);	RGBMute(1,255,112,0);	RGBMute(2,255,112,0);
	RGBMute(0,255,0,112);	RGBMute(1,255,0,112);	RGBMute(2,255,0,112);
	#endif
	
}                       
#endif
//-----------------------------------------------------------------------------------------------