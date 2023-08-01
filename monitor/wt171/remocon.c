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

#include	"TopHeader.h"
#include	"btc_osdmenu.h"


#ifdef USE_remocon
#if		defined(MCU_MTV212)
#include	"MTV212xfr.h"
#elif	defined(MCU_MTV230)
#include	"MTV230xfr.h"
#elif		defined(MCU_MTV412)
#include	"MTV412xfr.h"
#elif	defined(MCU_NT68F63)
#include	"NT68F63.h"
#endif

#include	"EEPROMadr.h"
#include	"power.h"
#include	"TVMODE.h"
#include	"RemoconCode.h"
#include "tuner.h"
#include "Sprocessor.h"
#include "ttx.h"
#include	"extern.h"	//03-08-05 4:45오후


//****************************************************************//
//함수선언
//****************************************************************//
void Inputdetect(void);
void EepromSetQue(WORD address, BYTE Recdata);
void BitWriteScaler(BYTE address, BYTE BitArry, BYTE Recdata);

#ifdef	USE_4BitInterface						//4bit통신 함수선언
void	WriteReg4bit(BYTE address, BYTE Recdata);
#define	WriteScaler(val1,val2) WriteReg4bit(val1,val2)	
BYTE	ReadScalerParallel(BYTE address);
#define	ReadScaler	ReadScalerParallel

#else									//1bit통신 함수선언
void	WriteReg1bit(BYTE address, BYTE Recdata);
#define	WriteScaler(val0, val1) WriteReg1bit(val0, val1)
BYTE	ReadScalerSerial(BYTE address);
#define	ReadScaler	ReadScalerSerial
#endif

void PutVolumePWM();
void ArrangeFunctionTable(void);    
//void ChangeToPipRgbTuner(void);
void ChangeToPipDviTuner(void);
void ChangeToPipDviTunerFast(void);
void ChangeToTunerOnly(void);
void ChangeToRgbOnly(void);
void ChangeToDviOnly(void);
void ChangeToCompositeOnly(void);
void ChangeToSvideoOnly(void);
void ChangeToPipRgbTunerFast(void);

void ChannelChange(void);	//smpark 20030806
extern void ShowChannelStatus(unsigned char status);	

//****************************************************************//
//변수선언
//****************************************************************//
extern	BYTE RemoteLongTimer;
extern	BYTE RemoteQue;
extern	bit 		RepeatCodeBit;
extern	BYTE	KEY_value;
extern	BYTE	OSDcharacters;
extern	BYTE	OsdMode;
extern	WORD	idata 	RecmoconTVchannel;
extern	BYTE	OSDWindows;
extern	BYTE	OSDstatus;
extern	WORD 	RemoconTenKeyTimer;
extern	bit		VideoActiveCompleted;
extern	BYTE	TunerProcessing;
extern	BYTE	idata ReceiveRemoconCount;
//extern	BYTE	idata RepeatCodeCount;////**CHECK 
extern	BYTE	CurrentFunction;
extern	BYTE	PowerOnsequence;
extern	WORD	PowerOnTimer;
extern	bit		AutoFlag;
extern	bit		NoExistHfreq;
extern	bit		NoExistVfreq;
extern	xdata	BYTE	xEEPROMBuffer[MaxEepromBuffer];
extern	BYTE	SyncStableTimer;
extern	bit 		SoundMuteOnFlag;
//extern	bit		OSDSelKeyin;
extern	bit		NowTopOsdOn;
//extern	bit		NowVolumOsdOn;
extern	bit		NowAutoChannelSearching;
extern	BYTE	MENUstatus;

extern	bit	RepeatCodeWait;//2003-08-09 4:44오후


//----------------------------------------03-08-05 4:48오후
extern	void	PipEnableService(void);	//03-08-05 4:42오후
extern	void 	PutData(void);
extern	void	LeftRightKey();
extern	void	PipSourceSelService(void);
extern	void 	PipPositionService(void);
extern	void	PipSizeSelFunc(void);
extern	void	PipSizeSelService(void);
//extern	void	leftright_svc(void);
//extern	void	OsdOnoff(void);
extern	void OSD230SeqSend(BYTE Recdata0,BYTE Recdata1,BYTE Recdata2,BYTE Recdata3);
extern	void OSD230ColSend(BYTE Recdata);
extern	void OSD230DataSend(BYTE Recdata);
extern	BYTE calToChar(DWORD Recdata);
extern	void OSD230PtrSend(BYTE Recdata0,BYTE Recdata1,BYTE *Recdata2,BYTE Recdata3);
extern	void SscService(void);	//2003-08-08
extern	void SpcService(void);	//2003-08-08
extern	void SleepService(void);	//2003-08-08
extern	void	PipAspectSelService(void);	//2003-08-18
extern	void 	TvAspectRatioService(void);	//2003-08-18
extern	void 	DisplayMenuWindow(void);
extern	void	Display_MenuBarPercent(void);
extern	void OsdService(void);
extern   void Recall(void);	//smpark 20030822
extern	void Osd_onoff(void);
extern	void	OsdOnoff(void);
extern	void SetScalerZoomFactor(BYTE Recdata);
extern	void SetScalerPIPOutputCondition(BYTE Recdata);     
//-----------------------------------------------------------
extern	void MTSDisplay(void);	//smpark 20030822
//extern 	void  DisplayChannelStatus(BYTE CHStatus );	// smpark 20030825
extern void Recall(void);
extern	void	MuteExe(void);	//2004-05-28
extern	void	MuteFunc(void);



#if	defined(DVI_EDIDWrite)
extern	bit		YouHaveToInitDviEDID;
extern	BYTE idata MemoryCount;
#endif
#endif

//extern WORD 	SaveRemCode;		// smpark 20030806
extern bit	ThreeDigit;	//smpark 20030807

#ifdef	USE_remocon

//============================================================================================================
#ifdef	BtcBoard_Option		//2003-04-14 Added Board Option
//============================================================================================================


void RemoconProcess(void)
{
	xBYTE CustomCode,CustomCodeBar,DataCode,DataCodeBar;//,BeforeRecdata;
	static BYTE idata BeforeRecdata;
	
	//데이타 분석 조건(32개를 받았거나, 리피트코드입력일때)
	if(RemoteQue!=32&&RepeatCodeBit!=1) return;

//=============================================================================	

	CustomCode=		(BYTE)(RemoteValue>>24);
	CustomCodeBar=(BYTE)(RemoteValue>>16);
	DataCode=			(BYTE)(RemoteValue>>8);
	DataCodeBar=	(BYTE)(RemoteValue);
	
	//커스텀,데이타코드가 일치하지 않으면 나간다.
	if(CustomCode!= RemoconCustomCode) {RemoteQue=0;return;}
	if(CustomCodeBar != 0xff) {RemoteQue=0;return;}
	if(DataCode&DataCodeBar) {RemoteQue=0;return;}

	if(RepeatCodeBit)
	{
		if(  DataCode!=VOLUMEandVALUE_DOWN_CODE &&
			DataCode!=VOLUMEandVALUE_UP_CODE && 
			DataCode!=CHANNELandMENU_DOWN_CODE &&
			DataCode!=CHANNELandMENU_UP_CODE) 
		{
			RepeatCodeBit=0;
			RemoteQue=0;
			return;
		}
	}

	RepeatCodeWait=1;	//kskim rmc 2003-08-09 5:10오후
	KeyActionTimer=0;	//2004-06-30

//-----------------------------------------------------------------------------------------------
	//power off상태에서 파워키외엔 적용안한다.
	if(DataCode!=POWER_CODE)
	{	
		if(PowerOnsequence<GeneralStatus)
		{
			RemoteQue=0;
			RepeatCodeBit=0;
			RemoteValue=0;
			return;
		}
	}
	
	//RGB auto tune중일땐 power key만 먹게..
	if(AutoFlag)
	{
		if(DataCode!=POWER_CODE)
		{
			RemoteQue=0;
			RepeatCodeBit=0;
			RemoteValue=0;
			return;
		}
	}
	
	//DPMS상태와 No video 상태에서는 power/source_select key만 동작하도록..
	if(PowerOnsequence == NoVideoStatus || DpmsFlag)
	{
		if( (DataCode!=POWER_CODE)&&(DataCode!=SELECT_CODE) )
		{
			RemoteQue=0;
			RepeatCodeBit=0;
			RemoteValue=0;
			return;
		}
	}
	
	
	//TV auto channel searching중일땐 MenuKey,power key만 먹게..
	if(NowAutoChannelSearching)
	{
		if(DataCode!=MENU_CODE&&DataCode!=POWER_CODE)
		{
			RemoteQue=0;
			RepeatCodeBit=0;
			RemoteValue=0;
			return;
		}
	}
	
	if((DataCode==NUM_1_code	||
	    DataCode==NUM_2_code	||
	    DataCode==NUM_3_code	||
	    DataCode==NUM_4_code	||
	    DataCode==NUM_5_code	||
	    DataCode==NUM_6_code	||
	    DataCode==NUM_7_code	||
	    DataCode==NUM_8_code	||
	    DataCode==NUM_9_code	||
	    DataCode==NUM_0_code	||
	    DataCode==NUM_100_code) && NowTopOsdOn)
	{
		NowTopOsdOn = 0;
		OSDWindows = 0;
		OSDstatus = OSDoff;
	}
			
				
	
	switch(DataCode)
	{
	#ifdef USE_TTX	//-----------------------------------------------------------	
		case IR_TTX_TEXT_MIX_TV:
			SDA555xModeChange();
			break;
			
		// COLOR KEY
		case IR_RED_TV:

			if(TTXMode){
				SDA555XWrite(0x00,0x14);
				idelay5m(6);
			}else{

			}
			break;

		case IR_GREEN_EXIT:
			if(TTXMode){
				SDA555XWrite(0x00,0x15);
				idelay5m(6);
			}else{

			}
			break;

		case IR_YELLOW_SPC:
			if(TTXMode){
				SDA555XWrite(0x00,0x16);
				idelay5m(6);
			}else{
			
			}
			break;
		case IR_CYAN:
			if(TTXMode){			
				SDA555XWrite(0x00,0x17);
				idelay5m(6);
			}
			break;	

		// TTX FUNCTIONS
		case IR_TTX_LIST_STORE:
			if(TTXMode){
				SDA555XWrite(0x00,0x25);
				idelay5m(6);
			}
			break;

		case IR_TTX_LIST_FTEXT:
			if(TTXMode){
				SDA555XWrite(0x00,0x29);
				idelay5m(6);
			}
			break;

		case IR_TTX_INDEX:
			if(TTXMode){
				SDA555XWrite(0x00,0x23);
				idelay5m(6);
			}
			break;

		case IR_TTX_HOLD:
			if(TTXMode){
				SDA555XWrite(0x00,0x24);
				idelay5m(6);				
			}
			break;
/*
		case IR_TTX_UPDATE:
			if(TTXMode){
				SDA555XWrite(0x00,0x16);
				idelay5m(6);				
			}
			break;
*/
		case IR_TTX_TIME:
			if(TTXMode){
				SDA555XWrite(0x00,0x26);
				idelay5m(6);
			}
			break;

		case IR_TTX_SIZE:
			if(TTXMode){
				SDA555XWrite(0x00,0x27);
				idelay5m(6);				
			}
			break;

		case IR_TTX_REVEAL:
			if(TTXMode){
				SDA555XWrite(0x00,0x28);
				idelay5m(6);				
			}
			break;
	#endif	//-----------------------------------------------------------
			
		//PIP로..
		case IR_PIP_ON_OFF:
			if( (xEEPROMBuffer[MainSubInputSource]==10)
				||(xEEPROMBuffer[MainSubInputSource]==14)
				||(xEEPROMBuffer[MainSubInputSource]==18)
				||PowerOnsequence==AnalogPowerSaverChars
				||(SubWindowMsgFlag&&(NoExistHfreq||NoExistVfreq)) )		{KEY_value = 0;return;}
		
			
			//Mute_SoundOff;
			
			
			//if(NowTopOsdOn){KEY_value = 0;return;}	//2003-08-12
			if(NowTopOsdOn||SubWindowMsgFlag)
			{	// osd window on 상태에서는 osd off	//2003-08-22
				NowTopOsdOn = 0;
				OSDWindows = 0;
				SubWindowMsgFlag=0;
				OSDstatus = OSDoff;
				Osd_onoff();
			}

			if( (NoExistHfreq||NoExistVfreq)&&DpmsPipFlag )
			{
				KEY_value = 0;
				DpmsPipFlag=0;
				if(ST_DET)	//케이블이 빠진 상태.
				{
					if((PowerOnsequence==DPMSLedOnOff)||(PowerOnsequence==DPMSOff))
					{
						PowerOnsequence = WakeUpFreeRun;
						return;
					}
					PowerOnsequence = BeforeCheckCableScalerInit;
				}
				else if((PowerOnsequence==DPMSLedOnOff)||(PowerOnsequence==DPMSOff) )//||(PowerOnsequence==BeforeFreeRunScalerInit))
				{ PowerOnsequence = WakeUpFreeRun;}
				else PowerOnsequence = BeforeFreeRunScalerInit;		//FreeRun상항으로..
				break;
			}
			
			MenuNum=menu_pip_enable;
			if(DpmsFlag!=1) PipOnOffFlag ^= 1;
			//PipOnOffFlag=(xEEPROMBuffer[PIPEN_SOURCE_buf]&0x10)>>4;	// high: On/Off
			PipEnableService();
			
			PipInputSource=xEEPROMBuffer[PIPEN_SOURCE_buf]&0x03;
			if(PipOnOffFlag)
			{
				PipSourceSelService();
				if(SoundMuteOnFlag)	
				{
					SubWindowMsgFlag=1;
					MuteFunc();
				}		//Mute 이면..
			}
			else			
			{
				AudioSelection_PC;
				PutVolumePWM();
				if(SoundMuteOnFlag==0)	Mute_SoundOn;	//Mute가 아니면..
			}

			xEEPROMBuffer[PIPEN_SOURCE_buf]= ( (((BYTE)PipOnOffFlag&0x01)<<4)+(xEEPROMBuffer[PIPEN_SOURCE_buf]&0x0f) );
			EepromSetQue(PIPEN_SOURCE_adr,xEEPROMBuffer[PIPEN_SOURCE_buf]);

			if(SubWindowMsgFlag)
			{	// pip도중 spc등.. osd menu on 되어있을 때  pip on->off시 off위해
				NowTopOsdOn = 0;
				SubWindowMsgFlag=0;
				OSDWindows = 0;
				OSDstatus = OSDoff;
			}
			//OSDofftimer = 0;
			KEY_value = 0;
			break;
			
		case IR_PIP_POS_H:
			if( (xEEPROMBuffer[MainSubInputSource]==10)||(xEEPROMBuffer[MainSubInputSource]==14)||(xEEPROMBuffer[MainSubInputSource]==18) )
			{KEY_value = 0;return;}	// Video mode일 경우 동작 안되게..
			
			PipOnOffFlag=(xEEPROMBuffer[PIPEN_SOURCE_buf]&0x10)>>4;	// high: On/Off
			if(!PipOnOffFlag){KEY_value = 0;return;}	//2003-08-12//2003-08-19
			if(NowTopOsdOn||SubWindowMsgFlag)
			{	// osd window on 상태에서는 osd off	//2003-08-22
				NowTopOsdOn = 0;
				OSDWindows = 0;
				SubWindowMsgFlag=0;
				OSDstatus = OSDoff;
				Osd_onoff();
			}
			
			MenuNum=menu_pip_Hposition;
			
			#if 1  // (좌<->우) 	//2003-08-29---------------------------------------
				if(PipHposUpdownFlag)
				{
					if((xEEPROMBuffer[PIPPOSITION]&0xf0)==0x20)
					{
						PipHposUpdownFlag^=1;
						xEEPROMBuffer[PIPPOSITION]=(xEEPROMBuffer[PIPPOSITION]&0x0f)+0x10;
					}
					else	xEEPROMBuffer[PIPPOSITION]+=0x10;
				}
				else
				{
					if((xEEPROMBuffer[PIPPOSITION]&0xf0)==0x00)
					{
						PipHposUpdownFlag^=1;
						xEEPROMBuffer[PIPPOSITION]=(xEEPROMBuffer[PIPPOSITION]&0x0f)+0x10;
					}
					else	xEEPROMBuffer[PIPPOSITION]-=0x10;
				}
			#else  // (좌->우)  -------------------------------------------------------
				if((xEEPROMBuffer[PIPPOSITION]&0xf0)==0x20)
				{
					xEEPROMBuffer[PIPPOSITION]=xEEPROMBuffer[PIPPOSITION]&0x0f;
				}
				else
				{
					xEEPROMBuffer[PIPPOSITION]+=0x10;
				}
			#endif	//-----------------------------------------------------------------
			
			PipPositionService();
			EepromSetQue(PIPPOSITION_adr,xEEPROMBuffer[PIPPOSITION]);
			KEY_value = 0;
			break;
			
		case IR_PIP_POS_V:
			if( (xEEPROMBuffer[MainSubInputSource]==10)||(xEEPROMBuffer[MainSubInputSource]==14)||(xEEPROMBuffer[MainSubInputSource]==18) )
			{KEY_value = 0;return;}	// Video mode일 경우 동작 안되게..
		
			PipOnOffFlag=(xEEPROMBuffer[PIPEN_SOURCE_buf]&0x10)>>4;	// high: On/Off
			if(!PipOnOffFlag){KEY_value = 0;return;}	//2003-08-12//2003-08-19
			if(NowTopOsdOn||SubWindowMsgFlag)
			{	// osd window on 상태에서는 osd off	//2003-08-22
				NowTopOsdOn = 0;
				OSDWindows = 0;
				SubWindowMsgFlag=0;
				OSDstatus = OSDoff;
				Osd_onoff();
			}
			
			MenuNum=menu_pip_Vposition;
			
			#if 1  // (상<->하)     //2003-08-29---------------------------------------
				if(PipVposUpdownFlag)
				{
					if((xEEPROMBuffer[PIPPOSITION]&0x0f)==0x02)
					{
						PipVposUpdownFlag^=1;
						xEEPROMBuffer[PIPPOSITION]=(xEEPROMBuffer[PIPPOSITION]&0xf0)+0x01;
					}
					else	xEEPROMBuffer[PIPPOSITION]+=0x01;
				}
				else
				{
					if((xEEPROMBuffer[PIPPOSITION]&0x0f)==0x00)
					{
						PipVposUpdownFlag^=1;
						xEEPROMBuffer[PIPPOSITION]=(xEEPROMBuffer[PIPPOSITION]&0xf0)+0x01;
					}
					else	xEEPROMBuffer[PIPPOSITION]-=0x01;
				}
			#else  // (상->하)  -------------------------------------------------------
				if((xEEPROMBuffer[PIPPOSITION]&0x0f)==0x02)
				{
					xEEPROMBuffer[PIPPOSITION]=xEEPROMBuffer[PIPPOSITION]&0xf0;
				}
				else
				{
					xEEPROMBuffer[PIPPOSITION]+=0x01;
				}
			#endif	//-----------------------------------------------------------------
			
			
			PipPositionService();
			EepromSetQue(PIPPOSITION_adr,xEEPROMBuffer[PIPPOSITION]);
			KEY_value = 0;
			break;
			
		case IR_PIP_ZOOM:
			if( (xEEPROMBuffer[MainSubInputSource]==10)||(xEEPROMBuffer[MainSubInputSource]==14)||(xEEPROMBuffer[MainSubInputSource]==18) )
			{KEY_value = 0;return;}	// Video mode일 경우 동작 안되게..

			PipOnOffFlag=(xEEPROMBuffer[PIPEN_SOURCE_buf]&0x10)>>4;	// high: On/Off
			if(!PipOnOffFlag){KEY_value = 0;return;}	//2003-08-12//2003-08-19
			if(NowTopOsdOn||SubWindowMsgFlag)
			{	// osd window on 상태에서는 osd off	//2003-08-22
				NowTopOsdOn = 0;
				OSDWindows = 0;
				SubWindowMsgFlag=0;
				OSDstatus = OSDoff;
				Osd_onoff();
			}


			MenuNum=menu_pip_size;
			PipSizeNum=xEEPROMBuffer[PIPSIZE_buf]&0x03;

			
			#if 1  // (대<->소) 	//2003-08-29---------------------------------------
				if(PipZoomUpdownFlag)
				{
					if(PipSizeNum==SizeLarge)
					{
						PipSizeNum=SizeMiddle;//SizeSmall;
						PipZoomUpdownFlag^=1;
					}
					else	PipSizeNum--;
				}
				else
				{
					if(PipSizeNum==SizeSmall)
					{
						PipSizeNum=SizeMiddle;//SizeLarge;
						PipZoomUpdownFlag^=1;
					}
					else	PipSizeNum++;
				}
			#else  // (대->소)  -------------------------------------------------------
				if(PipSizeNum>SizeSmall-1) PipSizeNum=SizeLarge;
				else	PipSizeNum++;
			#endif	//-----------------------------------------------------------------
			
			
			PipSizeSelService();

			KEY_value = 0;
			break;

			
		case MENU_CODE:
			//KEY_value = MenuKey;
			//if((xEEPROMBuffer[MainSubInputSource]==Tuner_mode||xEEPROMBuffer[MainSubInputSource]==PipRnT_mode) &&SubWindowMsgFlag)
			if(SubWindowMsgFlag& ReceiveRemoconCount==1)
			{
				LED_OFF;
				SubWindowMsgFlag=0;
				ReceiveRemoconCount=0;		// 리모컨 숫자키 초기화
				RemoconTenKeyTimer=601;		//강제로 타이머셋팅해서 튜너를 건드리게 한다.
			}
			else	KEY_value = MenuKey;
			
			break;
			
		case CHANNELandMENU_UP_CODE:
			if(!(RepeatCodeCount==0||RepeatCodeCount>=5)) return;		//2004-06-18
			KEY_value = UpKey;
			break;
			
		case CHANNELandMENU_DOWN_CODE:
			if(!(RepeatCodeCount==0||RepeatCodeCount>=5)) return;
			KEY_value = DownKey;
			break;
			
		case VOLUMEandVALUE_DOWN_CODE:
			#if 1 //kskim rmc 2003-08-09 5:12오후
				if(!(RepeatCodeCount==0||RepeatCodeCount>=5)) return;
				KEY_value = LeftKey;
			#else 
				KEY_value = LeftKey;
			#endif
			break;

		case VOLUMEandVALUE_UP_CODE:
			#if 1 //kskim rmc 2003-08-09 5:12오후
				if(!(RepeatCodeCount==0||RepeatCodeCount>=5)) return;
				KEY_value = RightKey;
			#else
				KEY_value = RightKey;
			#endif
			break;
			
		case SELECT_CODE:
			//if( (NoExistHfreq||NoExistVfreq)&&(~DpmsPipFlag&&SubWindowMsgFlag) ) {KEY_value=0;return;}
				
			if(NowTopOsdOn||SubWindowMsgFlag)
			{	// osd window on 상태에서는 osd off	//2003-08-25
				NowTopOsdOn = 0;
				OSDWindows = 0;
				SubWindowMsgFlag=0;
				OSDstatus = OSDoff;
				Osd_onoff();
			}

			KEY_value = SelKey;
			break;
		case POWER_CODE:
			KEY_value = PowerKey;
			break;
		// smpark 20030729
		case IR_SLEEP:
			SleepService();	//2003-08-08 9:52오후	by thkim
			KEY_value = 0;
			break;
		
		case IR_EXIT:
			#ifdef TestTunerSound//---------------------//2004-04-03
			{
				extern	BYTE	testI2Cflag;
				
				if(~NowTopOsdOn)
				{
					testI2Cflag^=1;
					if(testI2Cflag) {LED_OFF;}
					else	{LED_ON;}
				}
			}
			#endif
			//if(ThreeDigit==0 && ReceiveRemoconCount==2 && RecmoconTVchannel==0) return;
			if(ThreeDigit==0 && RecmoconTVchannel==0)    return;
			if(MENUstatus==MuteDisplay)	{KEY_value=0; return;}
			NowTopOsdOn = 0;
			OSDWindows = 0;
			OSDstatus = OSDoff;
			KEY_value = 0;
			ReceiveRemoconCount=0;		// 리모컨 숫자키 초기화
			ThreeDigit=0;			// 리모컨 숫자키 초기화
			RemoconTenKeyTimer=601;//강제로 타이머셋팅해서 튜너를 건드리게 한다.
			break;

		case IR_RECALL:
			//if(RecallFlag) //{KEY_value = 0;return;}
			if(ThreeDigit==0 && ReceiveRemoconCount>=1 && RecmoconTVchannel==0) return;	//+jeonhy 040801
													
			// if(ThreeDigit==0 && RecmoconTVchannel==0)    return;
			if(ReceiveRemoconCount!=0)
			{
				ThreeDigit=0;			// 리모컨 숫자키 초기화
				ReceiveRemoconCount=0;
				RemoconTenKeyTimer=601;//강제로 타이머셋팅해서 튜너를 건드리게 한다.
				KEY_value =0;
				return;
			}
			
			ReceiveRemoconCount=0;//
			Recall();
			KEY_value =0;
			break;

/*
		case IR_TV_PC:
			#if 0	//pip on시 작동 안되게...
			if(PipOnOffFlag) {KEY_value = 0; return;}	//2003-08-12
			#else	//pip on시 pip off시키고 TV로 전환.	//2003-08-12
			if(PipOnOffFlag) 
			{
				//PipOnOffFlag=0;
				MenuNum=menu_pip_enable;
				PipOnOffFlag=(xEEPROMBuffer[PIPEN_SOURCE_buf]&0x10)>>4;	// high: On/Off
				PipEnableService();
		
				xEEPROMBuffer[PIPEN_SOURCE_buf]= ( (((BYTE)PipOnOffFlag&0x01)<<4) +(xEEPROMBuffer[PIPEN_SOURCE_buf]&0x0f) );
				EepromSetQue(PIPEN_SOURCE_adr,xEEPROMBuffer[PIPEN_SOURCE_buf]);
				
			}
			#endif
			
			if(CurrentFunction==0) ChangeToTunerOnly();
			else ChangeToRgbOnly();
			KEY_value = 0;			
			break;			
*/

		case IR_WIDE:
			//--------------------------------------------------------------
			// pip wide func.	//2003-08-18 by thkim
			//--------------------------------------------------------------
			if( (CurrentFunction!=Tuner_mode)&&(CurrentFunction!=Composite_mode)&&(CurrentFunction!=Svideo_mode)
					&&(NowHactive==PanelHerizontalsize &&PipOnOffFlag==0) )
			{	// PC mode일 경우
				return;	//=1280이면 동작안함.(1:1입출력은 4:3으로 볼필요없기때문)
			}
			
			if(NowTopOsdOn)
			{	// osd window on 상태에서는 osd off
				NowTopOsdOn = 0;
				OSDWindows = 0;
				SubWindowMsgFlag=0;
				//OSDstatus = OSDoff;
				//OsdOnoff();
			}

			OSDstatus = OSDoff;
			Osd_onoff();
					
					
			if(CurrentFunction==Tuner_mode||CurrentFunction==Composite_mode||CurrentFunction==Svideo_mode)
			{	// Video mode일 경우
				DisplayAspectRatioNum=xEEPROMBuffer[DisplayAspcet_buf]&0x03;
				
				if(DisplayAspectRatioNum>aspect_full-1) DisplayAspectRatioNum=aspect4_3;
				else	DisplayAspectRatioNum++;
		        	
		 		InvertOff;	//2003-08-20
				TvAspectRatioService();
				InvertOn;
			}
			else
			{	//pc일 경우
				OSDstatus = OsdRamClear;
				OsdService();

				if(~PipOnOffFlag)
				{
					AspectFlag^=1;
					xEEPROMBuffer[Aspect_buf]=(BYTE)AspectFlag&&0x01;
					EepromSetQue(Aspect_adr,xEEPROMBuffer[Aspect_buf]);
					SetScalerZoomFactor(xEEPROMBuffer[MainSubInputSource]);
				}
				else
				{
					PipAspectFlag^=1;
					MenuNum=menu_pip_AspectRatio;
	
					if(MenuNum==menu_pip_size||MenuNum==menu_pip_AspectRatio) WriteScaler(0x9a,0x00);//PIP OFF//2003-10-16
					PipAspectSelService();
					SetScalerZoomFactor(xEEPROMBuffer[MainSubInputSource]);
					SetScalerPIPOutputCondition(xEEPROMBuffer[MainSubInputSource]);	//pip on
	
					EepromSetQue(PIPSIZE_adr,xEEPROMBuffer[PIPSIZE_buf]);
				}
				
			}

			KEY_value = 0;	
			//---------------------------------------------------------------
			break;

		case IR_ADD:
			ArrangeFunctionTable();
			if( 		CurrentFunction==Tuner_mode
				||	CurrentFunction==PipRnT_mode
				||	CurrentFunction==PipDnT_mode	) {	//2003.8.21 youngdo tv에서만 작동.
				KEY_value = OSD_ADD;	//smaprk 20030807
			}else 
				KEY_value = 0;			
			break;


		case IR_SPC:
			if( (xEEPROMBuffer[MainSubInputSource]!=10)&&(xEEPROMBuffer[MainSubInputSource]!=14)&&(xEEPROMBuffer[MainSubInputSource]!=18) )
			{	// PC mode일 경우
			
				PipOnOffFlag=(xEEPROMBuffer[PIPEN_SOURCE_buf]&0x10)>>4;	// high: On/Off   
				if(!PipOnOffFlag) {KEY_value = 0;return;}	// pip가 on일 경우만 동작되게..//2003-08-19
			}
			SpcService();	//2003-08-08 9:33오후	by thkim
			KEY_value = 0;
			break;

		case IR_MTS:
			MTSDisplay();
//			DisplayChannelStatus(2);
			
			KEY_value = 0;
			break;

		case IR_SSC:
			SscService();	//2003-08-08 4:56오후	by thkim	
			break;

		case IR_PRECH:
			if( (CurrentFunction!=Tuner_mode && CurrentFunction!=PipRnT_mode) || NotSearchCHflag)	{KEY_value=0; return;}	//2003-09-08//Tv일때만 동작하도록, or 검색된 CH이 하나도 없으면 실행안함.
			
			Mute_SoundOff;
			if(CurrentFunction==Tuner_mode)	MUTEON;	//main background mute
			
			if(NowTopOsdOn||SubWindowMsgFlag)
			{
				NowTopOsdOn = 0;
				OSDWindows = 0;
				SubWindowMsgFlag=0;
				OSDstatus = OSDoff;
				Osd_onoff();
			}
			
			CustomCodeBar=xEEPROMBuffer[CurrentChannel];
			xEEPROMBuffer[CurrentChannel]=xEEPROMBuffer[PreChannel];
			xEEPROMBuffer[PreChannel]=CustomCodeBar;	
			SoundMuteTvTimer=0;
			TunerProcessing=1;
						
			SoundMode=0;
//			SoundModeCnt=0;
			PreSoundMode=0xff;	// smpark 20030811
			//AddDelFlag=0;

			Recall();					// smpark 20030903
			
			Remote1keyFlag=1;
			SoundTimer=500;	
			
			break;					
		
		//REMOCON TEN KEY
		case NUM_1_code://"1"
			if(NowTopOsdOn)
			{
				NowTopOsdOn = 0;
				OSDWindows = 0;
				OSDstatus = OSDoff;
			}			
			RecmoconTVchannel = 1;
			break;
		case NUM_2_code://"2"
			RecmoconTVchannel = 2;
			break;
		case NUM_3_code://"3"
			RecmoconTVchannel = 3;
			break;
		case NUM_4_code://"4"
			RecmoconTVchannel = 4;
			break;
		case NUM_5_code://"5"
			RecmoconTVchannel = 5;
			break;
		case NUM_6_code://"6"
			RecmoconTVchannel = 6;
			break;
		case NUM_7_code://"7"
			RecmoconTVchannel = 7;
			break;
		case NUM_8_code://"8"
			RecmoconTVchannel = 8;
			break;
		case NUM_9_code://"9"
			RecmoconTVchannel = 9;
			break;
		case NUM_0_code://"0"
			RecmoconTVchannel = 0;
			break;
		case NUM_100_code:	// 100	//smpark 20030729
			#ifdef USE_NTSCtuner
			if((BYTE)AntenaFlag==AtnCable && xEEPROMBuffer[SystemCountry]!=Japan){	
				ThreeDigit=1;
				ReceiveRemoconCount=0;
				RecmoconTVchannel = 1;
			}else return;
			#else
				ThreeDigit=1;
				ReceiveRemoconCount=0;
				RecmoconTVchannel = 1;
			#endif
			
			break;
		
		case MUTE_CODE:
			//Volume Mute
			if(PowerOnsequence!=GeneralStatus&&PowerOnsequence!=NoVideoStatus) break;//normal status일때만 뮤트가 뜬다.
			
			MuteExe();
			break;

		default:
			break;
	}
	
	//=========Data code 영역===================================================	
	
	//TUNER를 사용할때만..
	//top menu상태가 아니고
	//0~9까지 코드이면
	if(	  (NowTopOsdOn!=1)
		&&(CurrentFunction==4||CurrentFunction==7||CurrentFunction==10)
		&&(DataCode==NUM_1_code||
		 DataCode==NUM_2_code||
		 DataCode==NUM_3_code||
		 DataCode==NUM_4_code||
		 DataCode==NUM_5_code||
		 DataCode==NUM_6_code||
		 DataCode==NUM_7_code||
		 DataCode==NUM_8_code||
		 DataCode==NUM_9_code||
		 DataCode==NUM_0_code||
		 DataCode==NUM_100_code)
		 &&(NotSearchCHflag==0)	)
	{
		SubWindowMsgFlag=0;//2004-06-23
		
		RemoconDigit=1;	//smpark 20030827
		TunerProcessing = 7;//remocon tv processing..으로...
			
		RemoconTenKeyTimer=0;
		OSDWindows = TunerSubWindow;
		OSDcharacters = ChannelOnlyNumber;
		OSDstatus = TVchannelDisplay;	
		++ReceiveRemoconCount;
		
		#if defined(USE_NTSCtuner)		
		switch((BYTE)AntenaFlag)
		{
			case AtnAir:
				if(ReceiveRemoconCount==1)
				{
					RecmoconTVchannel=RecmoconTVchannel;
					SingleCH=RecmoconTVchannel;	//smpark 20030818
				}
				else if(ReceiveRemoconCount==2)
				{
					if( ( xEEPROMBuffer[SystemCountry]!=Japan && (DataCode==NUM_0_code || DataCode==NUM_1_code) && BeforeRecdata==0)
								||( xEEPROMBuffer[SystemCountry]==Japan && DataCode==NUM_0_code && BeforeRecdata==0)
								||( xEEPROMBuffer[SystemCountry]==Japan && (DataCode!=NUM_0_code&&DataCode!=NUM_1_code&&DataCode!=NUM_2_code)&& BeforeRecdata==6) )
					{
								ReceiveRemoconCount=1;
								RemoconTenKeyTimer=0;
								RecmoconTVchannel=BeforeRecdata;
								break;
					}
					RecmoconTVchannel=(BeforeRecdata*10)+RecmoconTVchannel;
				}
				
				
				BeforeRecdata=RecmoconTVchannel;//backup
		    	
				if(ReceiveRemoconCount>=2||RecmoconTVchannel==7||RecmoconTVchannel==8||RecmoconTVchannel==9) //7,8,9일땐 바로동작..
				{
					ReceiveRemoconCount=0;
					RemoconTenKeyTimer=601;//강제로 타이머셋팅해서 튜너를 건드리게 한다.
//					SingleCH=0;	//smpark20030818
					SingleCHflag=0;
				}
				break;
			
			case AtnCable:
				if(ThreeDigit)
				{
					if(ReceiveRemoconCount==1)
					{
						RecmoconTVchannel=RecmoconTVchannel;
						SingleCH=RecmoconTVchannel*100;
					}
					else if(ReceiveRemoconCount==2)
					{
						if(DataCode==NUM_0_code||DataCode==NUM_1_code||DataCode==NUM_2_code)
						{		RecmoconTVchannel=(BeforeRecdata*10)+RecmoconTVchannel;}
						else 
						{
								ReceiveRemoconCount=1;
								RemoconTenKeyTimer=0;
								RecmoconTVchannel=BeforeRecdata;
								break;
						}
					}
					else if(ReceiveRemoconCount==3)
					{
						if( (DataCode==NUM_6_code||DataCode==NUM_7_code||DataCode==NUM_8_code||DataCode==NUM_9_code) 
								&& ((BeforeRecdata%10)==2) )
						{
								ReceiveRemoconCount=2;
								RemoconTenKeyTimer=0;
								RecmoconTVchannel=BeforeRecdata;
								break;
						}
						
						RecmoconTVchannel=(BeforeRecdata*10)+RecmoconTVchannel;
					}

					BeforeRecdata=RecmoconTVchannel;	//backup
					
					if( ReceiveRemoconCount>=3 )
					{
						ReceiveRemoconCount=0;
						RemoconTenKeyTimer=601;	//강제로 타이머셋팅해서 튜너를 건드리게 한다.
						ThreeDigit=0;
//						SingleCH=0;
						SingleCHflag=0;
					}
				}
				else
				{
					if(ReceiveRemoconCount==1)
					{
						RecmoconTVchannel=RecmoconTVchannel;
						SingleCH=RecmoconTVchannel;	//smpark 20030818
					}
					else if(ReceiveRemoconCount==2)
					{
						//switch(xEEPROMBuffer[SystemCountry]) //2004-07-20
						//{
						//	case 1:	//Korea
						//	case 0: //USA
						//	default:
						//if( (DataCode==NUM_0_code || DataCode==NUM_1_code) && BeforeRecdata==0)
						//		break;
						//	case 2: //Japan
						//if(DataCode==NUM_0_code && BeforeRecdata==0)
						//		break;
						//}
						if( ( xEEPROMBuffer[SystemCountry]!=Japan && (DataCode==NUM_0_code || DataCode==NUM_1_code) && BeforeRecdata==0)
								||( xEEPROMBuffer[SystemCountry]==Japan
										&&( (DataCode==NUM_0_code && BeforeRecdata==0)
												||(DataCode!=NUM_0_code&&DataCode!=NUM_1_code&&DataCode!=NUM_2_code&&DataCode!=NUM_3_code&& BeforeRecdata==6))  ) )
						{
								ReceiveRemoconCount=1;
								RemoconTenKeyTimer=0;
								RecmoconTVchannel=BeforeRecdata;
								break;
						}
						RecmoconTVchannel=(BeforeRecdata*10)+RecmoconTVchannel;
					}

					BeforeRecdata=RecmoconTVchannel;//backup
			    	
					if(ReceiveRemoconCount>=2 
							||xEEPROMBuffer[SystemCountry]==Japan&&(RecmoconTVchannel==7||RecmoconTVchannel==8||RecmoconTVchannel==9) )
					{
						ReceiveRemoconCount=0;
						RemoconTenKeyTimer=601;//강제로 타이머셋팅해서 튜너를 건드리게 한다.
					}
				}
				break;	
		} 
	
		#elif defined(USE_PALSECAMtuner)
				if(ThreeDigit)
				{
					if(ReceiveRemoconCount==1)
					{
						RecmoconTVchannel=RecmoconTVchannel*100;
						SingleCH=RecmoconTVchannel;
					}
					else if(ReceiveRemoconCount==2)
					{
						RecmoconTVchannel=(BeforeRecdata*10)+RecmoconTVchannel;
					}
					else if(ReceiveRemoconCount==3)
					{
						RecmoconTVchannel=(BeforeRecdata*10)+RecmoconTVchannel;
					}

					BeforeRecdata=RecmoconTVchannel;//backup
					
					#ifdef PalCountry_ChinaOnly
					if(ReceiveRemoconCount>=1){
					#else
					if(ReceiveRemoconCount>=3){
					#endif
						//ChannelChange();	//smpark 20030806
						ReceiveRemoconCount=0;
						RemoconTenKeyTimer=601;//강제로 타이머셋팅해서 튜너를 건드리게 한다.
						Remote1keyFlag=1;
						ThreeDigit=0;
//						SingleCH=0;//smpark 20030818
						SingleCHflag=0;
					}
//					Remote1keyFlag=1;
				}
				else
				{
					if(ReceiveRemoconCount==1)
					{
						RecmoconTVchannel=RecmoconTVchannel;
						SingleCH=RecmoconTVchannel;	//smpark 20030818
					}
					else if(ReceiveRemoconCount==2)
					{
						if(DataCode==NUM_0_code && BeforeRecdata==0)
						{
								ReceiveRemoconCount=1;
								RemoconTenKeyTimer=0;
								RecmoconTVchannel=BeforeRecdata;
								return;
						}
						RecmoconTVchannel=(BeforeRecdata*10)+RecmoconTVchannel;
					}
					
					BeforeRecdata=RecmoconTVchannel;//backup
			    	
					if(ReceiveRemoconCount>=2)
					{
						ReceiveRemoconCount=0;
						RemoconTenKeyTimer=601;//강제로 타이머셋팅해서 튜너를 건드리게 한다.
						Remote1keyFlag=1;
					}
				}
			#endif

		
	}
//============== TV & 10 KEy without OSD ===========================================	
	
	//Repeat code를 위해서..
//	kskim rmc 2003-08-09 5:14오후
//	if(DataCode!=VOLUMEandVALUE_DOWN_CODE&&DataCode!=VOLUMEandVALUE_UP_CODE) 
	RemoteQue=0;
	RepeatCodeBit = 0;
}

// smpark 20030806
void ChannelChange()
{
	if(	RecmoconTVchannel>=CHANNEL_MIN && RecmoconTVchannel<=CHANNEL_MAX)
	{
		xEEPROMBuffer[PreChannel]=xEEPROMBuffer[CurrentChannel];		// Pre channel에 현재 채널 설정
		xEEPROMBuffer[CurrentChannel]=RecmoconTVchannel-CHANNEL_MIN;	// Remocon에 전달 받은 채널로 전환
		SoundMuteTvTimer=0;
		TunerProcessing=1;
		ReceiveRemoconCount=0;//hanjaeduc//2003-12-26 8:18오전
		EepromSetQue(CurrentChannel_adr,xEEPROMBuffer[CurrentChannel]);	
	}
	else
	{
			NowTopOsdOn = 0;
			OSDWindows = 0;
			OSDstatus = OSDoff;
			KEY_value = 0;
			ReceiveRemoconCount=0;//hanjaeduc
			TVParameterInit();	//2003-12-26
	}
}


//============================================================================================================
#endif
//============================================================================================================
#endif
