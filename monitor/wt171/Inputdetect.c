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
#include	<stdlib.h>
#include	"power.h"
#include	"EEPROMadr.h"
#include "extern.h"
#include	"btc_osdmenu.h"
#include	"ttx.h"

#if	defined(MCU_MTV230)
#include	"MTV230xfr.h"
#elif		defined(MCU_MTV412)
#include	"MTV412xfr.h"
#elif	defined(MCU_NT68F63)
#include	"NT68F63.h"
#endif


//****************************************************************//
//함수선언
//****************************************************************//
void SetADCControlReg(void);
void SetADCPhaseReg(BYTE Recdata);
void SetADCHtotal(WORD Recdata);
BYTE EEPROM_Read(WORD address);
BYTE ModeTotalcount(void);
void EepromSetQue(WORD address, BYTE Recdata);

#ifdef	USE_4BitInterface								//4bit통신 함수선언
void	WriteReg4bit(BYTE address, BYTE Recdata);
#define	WriteScaler(val1,val2) WriteReg4bit(val1,val2)	
BYTE	ReadScalerParallel(BYTE address);
#define	ReadScaler	ReadScalerParallel
#else											//1bit통신 함수선언
BYTE	ReadScalerSerial(BYTE address);
#define	ReadScaler	ReadScalerSerial
void	WriteReg1bit(BYTE address, BYTE Recdata);
#define	WriteScaler(val0, val1) WriteReg1bit(val0, val1)
#endif

extern	void OsdService(void);
extern	void 	Osd_onoff(void);


void Inputdetect(void)
{
	BYTE Modecount = 0;
	static WORD CompHfreq, CompVfreq;
	static bit ST_DETBackup=0;
	static bit V_Pol=0;
	static bit H_Pol=0;
	
	bit V_polTemp;
	bit H_polTemp;
	
	//========================================================================================================================
	if(PowerOnsequence<PowerOnNormalStatus)	return;				//Power가 어느정도 진행된 후에 모드검사를 실시한다.
	//if(PowerOnsequence<PowerOnNormalStatus)
	//{DBGputs(" InputDetect > PowerOnsequence<PowerOnNormalStatus return"); return;}				//Power가 어느정도 진행된 후에 모드검사를 실시한다.
	//========================================================================================================================
	if(7<xEEPROMBuffer[MainSubInputSource]&&xEEPROMBuffer[MainSubInputSource]<20) return;		//Video(main)이면 빠져나간다.
	//if(7<xEEPROMBuffer[MainSubInputSource]&&xEEPROMBuffer[MainSubInputSource]<20) 
	//{DBGputs(" InputDetect > 7<xEEPROMBuffer[MainSubInputSource]&&xEEPROMBuffer[MainSubInputSource]<20 return"); return;}
	//========================================================================================================================
	if(VideoInitUnit!=0) return;						//PIP인 경우 디코더부터 먼저 initial하고 아래부분을..
	//if(VideoInitUnit>0)
	//{DBGputs(" InputDetect > VideoInitUnit>0 return"); return;}
	//========================================================================================================================
	if(SyncStableTimer) return;						//DVI stable(읽기위해 시간필요)
	//if(SyncStableTimer) 
	//{DBGputs(" InputDetect > SyncStableTimer return");return;}
	//========================================================================================================================
	
	
	//-------------------------------------------------------------------
	#ifdef DVI_USE
	if( 4 <=xEEPROMBuffer[MainSubInputSource]&&xEEPROMBuffer[MainSubInputSource]<=7 ||			//DVI status읽고 강제로 모드를 트리거한다.
		36<=xEEPROMBuffer[MainSubInputSource]&&xEEPROMBuffer[MainSubInputSource]<=51||
		60<=xEEPROMBuffer[MainSubInputSource]&&xEEPROMBuffer[MainSubInputSource]<=67)
	{
		if(SCDT_LOWBackup&&SCDT)	//--->rising edge
		{
			MUTEON;
			SCDT_LOWBackup=0;
			ModeTrigger;		//강제로 모드트리거한다.
			return;	
		}
		else if(SCDT_HIGHBackup&&!SCDT)	//--->falling edge
		{
			MUTEON;
			SCDT_HIGHBackup=0;
			ModeTrigger;		//강제로 모드트리거한다.	
			return;
		}
		
		V_polTemp = xHVSTUS&0x10;
		H_polTemp = xHVSTUS&0x20;
		if(V_polTemp^V_Pol)
		{
			MUTEON;
			ModeTrigger; 		//V-Polarity가 변경되면 강제로 모드를 트리거한다.
			V_Pol = xHVSTUS&0x10;
			H_Pol = xHVSTUS&0x20;
			return;
		}
		if(H_polTemp^H_Pol)
		{
			MUTEON;
			ModeTrigger; 		//H-Polarity가 변경되면 강제로 모드를 트리거한다.
			V_Pol = xHVSTUS&0x10;
			H_Pol = xHVSTUS&0x20;
			return;
		}
	}
	else													//RGB MODE!!
	#endif
	//-------------------------------------------------------------------
	{
	//DBGputs(" InputDetect > D-Sub, H, V");
		if(ST_DET^ST_DETBackup) 	//DSUB signal 이 변경되면 강제로 모드를 트리거한다.
		{
			MUTEON;
			ModeTrigger;
		}
		ST_DETBackup = ST_DET;

		V_polTemp = xHVSTUS&0x10;
		H_polTemp = xHVSTUS&0x20;
		if(V_polTemp^V_Pol)
		{
			MUTEON;
			ModeTrigger; //V-Polarity가 변경되면 강제로 모드를 트리거한다.
			V_Pol = xHVSTUS&0x10;
			H_Pol = xHVSTUS&0x20;
			return;
		}
		if(H_polTemp^H_Pol)
		{
			MUTEON;
			ModeTrigger; //H-Polarity가 변경되면 강제로 모드를 트리거한다.
			V_Pol = xHVSTUS&0x10;
			H_Pol = xHVSTUS&0x20;
			return;
		}
	}
	
#if	defined(MCU_MTV230) || defined(MCU_MTV412)	
	//*************************************************************************
	if(!(xHVSTUS&0x08)||xHCNTH&0x80)	//Hsync없거나 Hfreq overflowed
	{
		SYNC_chattering=0;
		++NoHSYNC_chattering;
		if(NoHSYNC_chattering>=0xFFFF) NoHSYNC_chattering=0xFFFE;
	}
	else NoHSYNC_chattering = 0;		//Sync exist, chattering buffer clear!

	if(!(xHVSTUS&0x04)||xVCNTH&0x80)	//Vsync없거나 Vfreq overflowed
	{
		SYNC_chattering=0;
		++NoVSYNC_chattering;
		if(NoVSYNC_chattering>=0xFFFF) NoVSYNC_chattering=0xFFFE;
	}
	else NoVSYNC_chattering = 0;	//Vsync exist->chattering buffer clear!
	//*************************************************************************
	
	//--------------------------------------------------------------------------------------------------------------------------------
	//무신호시작시 뮤트	
	//무신호시작시 OSD off
	//if(NoVSYNC_chattering==1||NoHSYNC_chattering==1) {xOSDW_OPTION[1]=0x00|0x02;MUTEON;}
	if(NoVSYNC_chattering==1||NoHSYNC_chattering==1) 
	{
		if(PipOnOffFlag) {WriteScaler(0x9a,0x00);}//Mute_SoundOff;}	//2004-06-03//test
		
		
		if(NowTopOsdOn||SubWindowMsgFlag)
		{
			NowTopOsdOn = 0;
			OSDWindows = 0;
			OSDstatus = OSDoff;
			OsdService();
			OSDOFF;
		}
		if(OSDcharacters==MuteChars||OSDstatus==MuteDisplay||SoundMuteOnFlag)
		{
			OSDstatus = OSDoff;
			Osd_onoff();
			OSDOFF;
			OSDstatus=0;
			OSDcharacters=0;
		}
		//OSDOFF;
		Mute_SoundOff;
		MUTEON;
	}
	
	if(NoVSYNC_chattering>= NoSignalCheckTime||NoHSYNC_chattering>= NoSignalCheckTime)	//Sync chattering!, Not Vsync, Green LED ON!, MUTEON!
	{
		if(NoExistHfreq||NoExistVfreq) return;
		
		if(NoHSYNC_chattering>=NoSignalCheckTime) {NoExistHfreq =1;}
		if(NoVSYNC_chattering>=NoSignalCheckTime) {NoExistVfreq =1;}
		
		NowHfreq =0;																//Mode검사용 Ram도 클리어 한다.
		NowVfreq =0;
		BeforeHfreq =0;
		BeforeVfreq =0;

		switch(xEEPROMBuffer[MainSubInputSource])
		{
			//RGB
			case 0:		//R(no frc)
			case 2:		//R(frc)
			case 20:	//R+C(Yes)
			case 22:	//R+C(No)
			case 28:	//R+SV(Yes)
			case 30:	//R+SV(No)
			case 52:	//R+TV

				PowerOnTimer=0;
				
				BackupInputStatus=xEEPROMBuffer[MainSubInputSource];			//2003-08-26
				xEEPROMBuffer[BackupMainSubInputSource]=BackupInputStatus;		//2003-10-21
				EepromSetQue(BackupMainSubInputSource_adr,BackupInputStatus);	//2003-10-21	 전상태값도 eeprom에 저장.
				
				if(DpmsPipFlag==0)
				{
				#ifdef	PipDpmsON	//r+ c/sv/tv 경우 이 루틴 적용제외 함.
				if(xEEPROMBuffer[MainSubInputSource]==20
				 ||xEEPROMBuffer[MainSubInputSource]==28
				 ||xEEPROMBuffer[MainSubInputSource]==52) {DpmsPipFlag=1; return;}//2003-10-21
				#endif					// H/Vsync없으면서 r+c(/sv/tv)의 경우임.
				}
		
				#ifdef PipDpmsON
					//...
				#else
				xEEPROMBuffer[MainSubInputSource]=2;
				CurrentFunction=Rgb_mode;
				EepromSetQue(MainSubInputSource_adr,2); //RGB로..
				#endif
				
				if(ST_DET)	//케이블이 빠진 상태.
				{
					if((PowerOnsequence==DPMSLedOnOff)||(PowerOnsequence==DPMSOff))
					{
						PowerOnsequence = WakeUpFreeRun;
						return;
					}
					PowerOnsequence = BeforeCheckCableScalerInit;
				}
				else if((PowerOnsequence==DPMSLedOnOff)||(PowerOnsequence==DPMSOff))		{ PowerOnsequence = WakeUpFreeRun;}
				else PowerOnsequence = BeforeFreeRunScalerInit;	//케이블 있는 상태에서 신호없을때	//FreeRun상항으로..

				break;

			//DVI
			#ifdef USE_DVI
			case 4:
			case 6:
			case 36:
			case 38:
			case 44:
			case 46:
			case 60:
				//DPMS상태에서 dvi건넥터를 건드리면 SCDT신호가 바뀌게 되어 이곳으로 온다.
				//DPMS관련 상태에서 No-signal의 상태가 되면 그냥 빠진다.
				//if(PowerOnsequence==FreeRunStatus	||
				//PowerOnsequence==DPMSOff			||
				//PowerOnsequence==DPMSLedOnOff) return;
				PowerOnTimer=0;
				xEEPROMBuffer[MainSubInputSource]=6;
				CurrentFunction=1;
				EepromSetQue(MainSubInputSource_adr,6);//DVI로..
				
				if((PowerOnsequence==DPMSLedOnOff)||(PowerOnsequence==DPMSOff)) PowerOnsequence = WakeUpFreeRun;
				else PowerOnsequence = BeforeFreeRunScalerInit;//FreeRun상항으로..					
				break;
			#endif
		}
		return;
	}
	//--------------------------------------------------------------------------------------------------------------------------------
	
	if(SYNC_chattering<=SyncSignalStableTime)		//일정시간동안 주파수검사	
	{	
		NowHfreq=0;
		NowVfreq=0;
		NowHfreq = 1280000L/(((xHCNTH&0x3F)<<8)|xHCNTL+1);
		NowVfreq = 625000L /(((xVCNTH&0x0F)<<8)|xVCNTL  );
		
		if(abs(CompHfreq-NowHfreq)<=5 && abs(CompVfreq-NowVfreq)<=5)
			 ++SYNC_chattering; 	//Hfreq가 0.5Khz이하, Vfreq가 0.5Hz이하이면 stable검사(100ms)
		else 	//주파수가 변경되면 mute건다...
		{
			SYNC_chattering =0;
			MUTEON;
			DpmsPipFlag=0;
			//OSDstatus=OSDoff;
			//xOSDW_OPTION[1]=0x00|0x02;
			OSDOFF;
			ModeTrigger;//강제로 모드트리거한다.	
		}
		CompHfreq = NowHfreq;
		CompVfreq = NowVfreq;
		
		
		if((PowerOnsequence==DPMSLedOnOff)||(PowerOnsequence==DPMSOff)||(PowerOnsequence==BeforeFreeRunScalerInit))
		{
			if(PowerOnsequence==BeforeFreeRunScalerInit || PowerOnsequence==DPMSOff) PowerOnTimer=100;
			else if(PowerOnsequence==DPMSLedOnOff) PowerOnTimer=0;
			PowerOnsequence = WakeUpFreeRun;
			
			//signal이 입력되면 최초로 걸리는 부분.//2003-08-25 8:47오후
			BackupInputStatus=xEEPROMBuffer[BackupMainSubInputSource];	//2003-10-21
			xEEPROMBuffer[MainSubInputSource]=BackupInputStatus;		//2003-08-26	
			EepromSetQue(BackupMainSubInputSource_adr,BackupInputStatus);	//2004-05-29	 전상태값도 eeprom에 저장.
			
			DpmsPipFlag=0;
			DpmsFlag=0;
			
			VideoActiveCompleted = 0;	//Decoder 다시 셋팅할 플레그를 리셋.
			DecoderInit=0;
			
			#ifdef USE_UART
			DBGputs(" InputDetect > DecoderInit=0;");
			#endif
		}
		return;
	}
	
#elif	defined(MCU_NT68F63)
	#include "MCU_NT68F63_proc.h"
#endif
	
	SYNC_chattering=0;
	NoExistHfreq=0;
	NoExistVfreq=0;
		
	//예전 주파수와 비교하여 Hfreq 1Khz이상, Vfreq 1Hz이상이면 새모드로 인지한다.
	if(abs(NowHfreq-BeforeHfreq)>=10 || abs(NowVfreq-BeforeVfreq)>=10)				
	{
		BeforeHfreq = NowHfreq;
		BeforeVfreq = NowVfreq;
		//LED ON                                  
		//LEDGRN(ON);
		LED_ON;//No sync일때 DVI? NoDVI?    //0820
		
		//**PC MODE**//
		if(0 <=xEEPROMBuffer[MainSubInputSource]&&xEEPROMBuffer[MainSubInputSource]<=3 ||
		   20<=xEEPROMBuffer[MainSubInputSource]&&xEEPROMBuffer[MainSubInputSource]<=35||
		   52<=xEEPROMBuffer[MainSubInputSource]&&xEEPROMBuffer[MainSubInputSource]<=59)
		{
			
			for(Modecount=0;Modecount<ModeTotalcount();Modecount++)
			{
				if(abs(ModeList[Modecount].HF-NowHfreq)<=5 && abs(ModeList[Modecount].VF-NowVfreq)<=5)	//ModeTable에서 Hfreq가 0.5Khz이하, Vfreq가 0.5Hz이하이면 success!!!
				{
					#if defined(SVGA_Panel)//SVGA Panel에 대한 입력모드제한
					if(ModeList[Modecount].IHAW>800||ModeList[Modecount].IVAW>600)
					{
						MUTEON;
						OSDWindows = AnalogPowerSaverWindow;
						OSDcharacters = OutOfFreqChars;//Out Of Mode
						OSDstatus = Nosignal_Display;
						PowerOnTimer=0;
						PowerOnsequence = OutOfFreqStatus;
						xEEPROMBuffer[MainSubInputSource]=2;
						EepromSetQue(MainSubInputSource_adr,2);//RGB로..
						CurrentFunction=0;
						return;	
					}
					#elif defined(XGA_Panel)//XGA Panel에 대한 입력모드제한
					if(ModeList[Modecount].IHAW>1024||ModeList[Modecount].IVAW>768)
					{
						MUTEON;
						OSDWindows = AnalogPowerSaverWindow;
						OSDcharacters = OutOfFreqChars;//Out Of Mode
						OSDstatus = Nosignal_Display;
						PowerOnTimer=0;
						PowerOnsequence = OutOfFreqStatus;
						xEEPROMBuffer[MainSubInputSource]=2;
						EepromSetQue(MainSubInputSource_adr,2);//RGB로..
						CurrentFunction=0;
						return;	
					}
					#elif defined(WXGA_Panel)//XGA Panel에 대한 입력모드제한
					if(ModeList[Modecount].IHAW>1280||ModeList[Modecount].IVAW>768)
					{
						MUTEON;
						OSDWindows = AnalogPowerSaverWindow;
						OSDcharacters = OutOfFreqChars;//Out Of Mode
						OSDstatus = Nosignal_Display;
						PowerOnTimer=0;
						PowerOnsequence = OutOfFreqStatus;
						xEEPROMBuffer[MainSubInputSource]=2;
						EepromSetQue(MainSubInputSource_adr,2);//RGB로..
						CurrentFunction=0;
						return;	
					}
					#elif defined(SXGA_Panel)//SXGA Panel에 대한 입력모드제한
					if(ModeList[Modecount].IHAW>1280||ModeList[Modecount].IVAW>1024)
					{
						MUTEON;
						OSDWindows = AnalogPowerSaverWindow;
						OSDcharacters = OutOfFreqChars;//Out Of Mode
						OSDstatus = Nosignal_Display;
						PowerOnTimer=0;
						PowerOnsequence = OutOfFreqStatus;
						xEEPROMBuffer[MainSubInputSource]=2;
						EepromSetQue(MainSubInputSource_adr,2);//RGB로..
						CurrentFunction=0;
						return;	
					}

					#if defined(SXGA_60HzOver_NotSuuport)
					if(ModeList[Modecount].IHAW==1280&&ModeList[Modecount].HF>650)
					{
						MUTEON;
						OSDWindows = AnalogPowerSaverWindow;
						OSDcharacters = OutOfFreqChars;//Out Of Mode
						OSDstatus = Nosignal_Display;
						PowerOnTimer=0;
						PowerOnsequence = OutOfFreqStatus;
						xEEPROMBuffer[MainSubInputSource]=2;
						EepromSetQue(MainSubInputSource_adr,2);//RGB로..
						CurrentFunction=0;
						return;
					}
					#endif

					#endif

					//Set전에 Mute하고..
					OSDstatus=OSDoff;
					MUTEON;
					InvertOff;

					//--------------------------------
					/*
					if(Modecount==0||Modecount==1)
					{
						//720
						//Hsync NEG//BIT5
						//Vsync POS//BIT4
						if((~(xHVSTUS&0x10))&&(xHVSTUS&0x10))
						{
							Modecount = Modecount+2;
						}

						DosmodeFlag=xEEPROMBuffer[Dosmode_buf];
						if(DosmodeFlag) Modecount+=4;

					}
					*/
					//----------------------------------------------------------------------------
					//2003-08-26,	[640*350](H:+,V:-),[640*400/720*400](H:-,V:+) mode 선택을 위해
					//****************************************************************************
					//	mode : 640*350		         	 //	mode : 640*400/720*400
					//	Hsync Polarity: Positive         //	Hsync Polarity: Negative
					//	Vsync Polarity: Negative         //	Vsync Polarity: Positive
					//****************************************************************************
					if(Modecount==0||Modecount==1)	
					{
						if( (~(xHVSTUS&0x20))&&(xHVSTUS&0x10) )	// [640*400/720*400]일때, xHVSTUS([5]H:-,[4]V:+)
						{					
							Modecount += 2;	

							DosmodeFlag=xEEPROMBuffer[Dosmode_buf];	// DosmodeFlag (0:640*400, 1:720*400)
							if(DosmodeFlag) Modecount+=4;		// [640*400],[720*400] mode 선택을 위해
						}
						
					}
					//----------------------------------------------------------------------------
					CurrentMode = Modecount;			//Mode #를 변수에 넣어둔다.
					NowHactive = ModeList[Modecount].IHAW;
					NowVactive = ModeList[Modecount].IVAW;
					NowHtotal = ModeList[Modecount].HTotal;
					
					
					if(NowHactive==PanelHerizontalsize)
					{
						AspectFlag=0;
						xEEPROMBuffer[Aspect_buf]=(BYTE)AspectFlag&&0x01;
						EepromSetQue(Aspect_adr,xEEPROMBuffer[Aspect_buf]);
					}
					break;
				}

			}
			if(Modecount == ModeTotalcount())				//Mode counter가 범위를 넘었으면 OUT OF MODE로 인지 한다.
			{
				MUTEON;
				OSDWindows = AnalogPowerSaverWindow;
				OSDcharacters = OutOfFreqChars;//Out Of Mode
				OSDstatus = Nosignal_Display;
				PowerOnTimer=0;
				PowerOnsequence = OutOfFreqStatus;
				xEEPROMBuffer[MainSubInputSource]=2;
				EepromSetQue(MainSubInputSource_adr,2);//RGB로..
				CurrentFunction=0;
				return;
			}
			
			//ADC set
			//1. color관련:power.c의 color temperature에서 실시될것.
			//2. control관련:
			//3. phase
			//4. clock
			
			SetADCControlReg();
			SetADCPhaseReg((BYTE)EEPROM_Read(CurrentMode*4+3));
			ADCPLL = NowHtotal+(BYTE)EEPROM_Read(CurrentMode*4+2)-0x80;
			SetADCHtotal(ADCPLL-1);//-1 total!!!
			
			PowerOnsequence = ScalerstableWait;	//Mode change 후에 scaler set!!
			PowerOnTimer = 3;				//?ms 후에 scaler set!
			
			//---------------------------------------
			//auto sequence를 강제로 disable시킨다.	//2003-07-07 7:40오후
			AutoFlag=0;
			AutoProcess=0;
			
			//PIP No-video에 대한 모드변경은 그냥 RGB로 넘긴다.
			//-----------------------------------------------------------------------------------
			#if defined(RGB_LineSync)
			if(xEEPROMBuffer[MainSubInputSource]==22||xEEPROMBuffer[MainSubInputSource]==30) 
			{
				xEEPROMBuffer[MainSubInputSource]=0; //2003-04-28 4:35오후
				EepromSetQue(MainSubInputSource_adr,0);//RGB..
			}
			#else
			if(xEEPROMBuffer[MainSubInputSource]==22||xEEPROMBuffer[MainSubInputSource]==30)	//pip composete/s-video 신호 없을 때
			{
				xEEPROMBuffer[MainSubInputSource]=2; //2003-04-28 4:35오후
				EepromSetQue(MainSubInputSource_adr,2);//RGB..
			}
			#endif			

			////PipOnOffFlag=0;	//2003-07-29
			PipOnOffFlag=(xEEPROMBuffer[PIPEN_SOURCE_buf]&0x10)>>4;	
			xEEPROMBuffer[PIPEN_SOURCE_buf]= ( (((BYTE)PipOnOffFlag&0x01)<<4) +(xEEPROMBuffer[PIPEN_SOURCE_buf]&0x0f) );
			EepromSetQue(PIPEN_SOURCE_adr,xEEPROMBuffer[PIPEN_SOURCE_buf]);
			//-----------------------------------------------------------------------------------
		}

		//**DVI MODE**//
		#ifdef	DVI_USE
		else if(4 <=xEEPROMBuffer[MainSubInputSource]&&xEEPROMBuffer[MainSubInputSource]<=7 ||
		        36<=xEEPROMBuffer[MainSubInputSource]&&xEEPROMBuffer[MainSubInputSource]<=51||
		        60<=xEEPROMBuffer[MainSubInputSource]&&xEEPROMBuffer[MainSubInputSource]<=67)
		{
			#ifdef	DviSyncCheck_IVIHID			
			if((ReadScaler(0xCA)&0x07)!=0x07) //IH,IV,IDDEXIST?
			{
				ModeTrigger;//강제로 모드트리거한다.
				return;
			}
			#endif
			//IMSI for kbchung
			WriteScaler(0xA9,0x7C);
			NowHactive = 0;
			NowVactive = 0;
			NowHtotal = 0;
			
			NowHactive = (ReadScaler(0xC4)&0x07)<<8|ReadScaler(0xC5);
			NowHactive = NowHactive*2;					//H area 곱하기 2
			NowVactive = (ReadScaler(0xC6)&0x07)<<8|ReadScaler(0xC7);	//V area
			NowHtotal  = (ReadScaler(0xC8)&0x07)<<8|ReadScaler(0xC9);	//H total
			NowHtotal  = NowHtotal*2;
			
			PowerOnsequence = ScalerstableWait;	//Mode change 후에 scaler set!!
			PowerOnTimer = 3;					//?ms 후에 scaler set!	
		}
		#endif
	}
	else return;
}
