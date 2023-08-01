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

   2003-01-10 2:39����  JDHAN           Modified for Monitor-TV
****************************************************************************/

//****************************************************************//
//ȭ������
//****************************************************************//
#include	"TopHeader.h"
#include	"power.h"
#include "Tools.h"
#include "extern.h"

#if		defined(MCU_MTV230)
#include	"MTV230xfr.h"
#elif		defined(MCU_MTV412)
#include	"MTV412xfr.h"
#elif		defined(MCU_NT68F63)
#include	"NT68F63.h"
#endif

#include	"EEPROMadr.h"
#include <stdio.h>
#include "sprocessor.h"


//****************************************************************//
//�Լ�����
//****************************************************************//
#ifdef	USE_4BitInterface
void ScalerParallelMode(void);
#endif
void ScalerSet(void);
void SetParallelMode(void);
void SystemInitialize(void);

#ifdef	USE_4BitInterface						//4bit��� �Լ�����
	void	WriteReg4bit(BYTE address, BYTE Recdata);
	#define	WriteScaler(val1,val2) WriteReg4bit(val1,val2)	
	BYTE	ReadScalerParallel(BYTE address);
#define	ReadScaler	ReadScalerParallel

#else									//1bit��� �Լ�����
	void	WriteReg1bit(BYTE address, BYTE Recdata);
	#define	WriteScaler(val0, val1) WriteReg1bit(val0, val1)
	BYTE	ReadScalerSerial(BYTE address);
	#define	ReadScaler	ReadScalerSerial
#endif
void BitWriteScaler(BYTE address, BYTE BitArry, BYTE Recdata);
void 	PutVolumePWM();
void EepromSetQue(WORD address, BYTE Recdata);
BYTE EEPROM_Read(WORD address);
void InitialScaler(void);
void RamClear(void);
void SetADCGain(BYTE RecRED,BYTE RecGRN,BYTE RecBLU);
void SetADCBias(BYTE RecRED,BYTE RecGRN,BYTE RecBLU);
bit WriteI2C(BYTE sysaddr, BYTE subaddr, BYTE writedata);
void ArrangeFunctionTable(void);
void TunnerInitialize();
void SoundInit();
#if defined(VPC323x)
bit VPC323xFPWrite(WORD address,WORD Recdata);
WORD VPC323xBYTERead(BYTE address);
#endif

void SetAV_Contrast(void); 
void SetAV_Brightness(void);

//****************************************************************//
//��������
//****************************************************************//
extern 	BYTE	PowerOnsequence;
extern 	BYTE	PowerOffsequence;
extern	WORD	PowerOnTimer;
extern	BYTE	PowerOffTimer;
extern	BYTE	OSDstatus;
extern	BYTE	OSDWindows;
extern	BYTE	OSDcharacters;
extern	xdata	BYTE	xEEPROMBuffer[MaxEepromBuffer];
extern	xBYTE	HorizontalValue;
extern	xBYTE	VerticalValue;
extern	BYTE	idata	ClockValue;
extern	BYTE	idata	PhaseValue;
extern	BYTE	CurrentMode;
extern	bit		YouHaveToInitMode;
extern	bit		YouHaveToInitTVchannel;
extern	BYTE	CurrentFunction;
extern	BYTE	TunerProcessing;
extern	code	ModeTable ModeList[];
extern	BYTE	SyncStableTimer;
extern	bit		NoExistHfreq;
extern	bit		NoExistVfreq;
extern	code BYTE VideoDcoder_HueValue[31];
extern	bit	YouGoingInitialize;
extern	BYTE	KEY_value;
extern	bit		SoundMuteOnFlag;
extern	BYTE xdata SoundMuteTvTimer;
extern	void	Auto_Func(void);
extern void VideoDecoderInit(void);
extern	void	PipEnableService(void);
extern 	void idelay5m(BYTE time);
extern	void OsdService(void);

/*
�Ŀ�Ű�� ������ Ÿ�̸Ӱ��� sequence���� ������ �ȴ�.
*/

#define	LM2596Enable		_PowerON
#define	LM2596Disable		_PowerOFF


#if	defined(USE_UART)
void PrintPowerOnsequence(void)
{
		
	if(PowerOnsequence!=oldPowerOnsequence)
	{
		oldPowerOnsequence=PowerOnsequence;
		
		switch(PowerOnsequence)
		{
			case	MainPowerON:						DBGputs("MainPowerON");				break;
			case	WaitEepromInitialize:				DBGputs("WaitEepromInitialize:");	break;
			case	DevicestableWait:			        DBGputs("DevicestableWait:");	break;
			case	DecoderStableWait:                  DBGputs("DecoderStableWait:");	break;
			case	PanelPowerON:				        DBGputs("PanelPowerON:");	break;
			case	PanelLVDSON:                        DBGputs("PanelLVDSON:");	break;
			case	PanelInvertPwmON:                   DBGputs("PanelInvertPwmON:");	break;
			case	PowerOnNormalStatus:                DBGputs("PowerOnNormalStatus:");	break;
			case	ScalerstableWait:			        DBGputs("ScalerstableWait:");	break;
			case	MenuValueLoadandApply:              DBGputs("MenuValueLoadandApply:");	break;
			case	NormalDisplayPrepare:               DBGputs("NormalDisplayPrepare:");	break;
			case	DisplayLightOnstatus:               DBGputs("DisplayLightOnstatus:");	break;
			case	GeneralStatus:		                DBGputs("GeneralStatus:\n");	break;
			case	CheckCableMessage:                  DBGputs("CheckCableMessage:");	break;
			case	OutOfFreqStatus:                    DBGputs("OutOfFreqStatus:");	break;
			case	OnlyLedOnOffStatus:                 DBGputs("OnlyLedOnOffStatus:");	break;
			case	BeforeNoVideoScalerInit:            DBGputs("BeforeNoVideoScalerInit:");	break;
			case 	AfterNoVideoScalerInit:             DBGputs("AfterNoVideoScalerInit:");	break;
			case 	NoVideoStatus:	                    DBGputs("NoVideoStatus:");	break;
			case	BeforeCheckCableScalerInit:         DBGputs("BeforeCheckCableScalerInit:");	break;
			case	BeforeFreeRunScalerInit:            DBGputs("BeforeFreeRunScalerInit:");	break;
			case	FreeRunStatus:                      DBGputs("FreeRunStatus:");	break;
			case	DPMSOff:                            DBGputs("DPMSOff:\n");	break;
			case	DPMSLedOnOff:                       DBGputs("DPMSLedOnOff:");	break;
			case	WakeUpFreeRun:                      DBGputs("WakeUpFreeRun:");	break;
			default:          							DBGputs("PowerOnsequence default:");	break;
		}
	}
	if(PowerOffsequence!=oldPowerOffsequence)
	{
		oldPowerOffsequence=PowerOffsequence;
		switch(PowerOffsequence)
		{
			case	PanelInvertOFF:			DBGputs("PanelInvertOFF:");	break;      
			case	PanelInvertPwmOFF:      DBGputs("PanelInvertPwmOFF:");	break;   
			case	PanelPowerOFF:          DBGputs("PanelPowerOFF:");	break;       
			case	MainPowerOFF:           DBGputs("MainPowerOFF:");	break;        
			case	PowerOffNormalStatus:   DBGputs("PowerOffNormalStatus:");	break;
			case	SystemInitstatus:       DBGputs("SystemInitstatus:");	break;    
			default:	 					DBGputs("PowerOffsequence default:");	break;    
		}	
	}
}
#endif


//****************************************************************//
//Power-On Sequence
//****************************************************************//
void PowerSequence(void)
{
	static bit LedOnOffBit=0;
	static bit DpmsWakeUpBit=0;
		
	#if	defined(USE_UART)
	PrintPowerOnsequence();//
	#endif
	
	
	if(!PowerOnTimer)
	switch(PowerOnsequence)
	{
		case	MainPowerON:			//#define	MainPowerON	5
			LED_ON;
			LedOnOffBit=0;
			
			LM2596Enable;				//�ʱ� �Ŀ� ON!
			ModeTrigger;				//�ʱ� ������ �������� Ŭ����(�غ�)
			TW9908_RSTON;
				
			if(YouHaveToInitMode||YouHaveToInitTVchannel) {PowerOnsequence=WaitEepromInitialize;}//Eeeprom Initialize�̸�
			else{PowerOnTimer=10;PowerOnsequence=DevicestableWait;}
			break;	
		
		case	WaitEepromInitialize:
			if(YouHaveToInitMode||YouHaveToInitTVchannel) break;
			else {PowerOnsequence=DevicestableWait;PowerOnTimer=5;}
			break;
		
		case	DevicestableWait:			//main power�� Ű�� ������� �Ŀ� ADC�� enable��Ų��.

			ArrangeFunctionTable();
			
			if(CurrentFunction>=2) 
			{
				////MuteOff_VolumeDown //2003.6.23 youngdo VIDEOenable;//video decoder enable,
				Mute_SoundOff;
			}

			if(	CurrentFunction==1||
				CurrentFunction==8||
				CurrentFunction==9||
				#if defined(USE_SCART)	
				CurrentFunction==13||
				#endif
				CurrentFunction==10) 
				{
					AsyncOff;
					ADCDisable;
					DVIEnable;
					SyncStableTimer=10;
				}              
			else {
				AsyncOn;
				ADCEnable;
				DVIDisable;
			}	
			_SCALER_RST_LOW;
			TW9908_RSTOFF;	
			PowerOnTimer=10;					//20 * 5ms(timer interval)=100ms
			PowerOnsequence=DecoderStableWait;
			break;	
		
		case	DecoderStableWait:


			PowerOnTimer=2;			
			PowerOnsequence=PanelPowerON;
			break;
		
		case	PanelPowerON:					//6
			_SCALER_RST_HIGH;
			EepromSetQue(POWERID_adr,0x55);			//PowerOn ID write 				

			#ifdef	USE_4BitInterface		
			ScalerParallelMode();				//EMH1�� Power-on�� serialMode�� ���õǹǷ� parallelMode�� ������ѵд�.
			#endif

			PowerOnTimer=5;					//InitialScaler()���� �ð�(14ms)�ɸ��Ƿ� Ÿ�̸Ӱ��� ���ܰ迡 ����(���ͷ�Ʈ��ƾ�ȿ��� ���ҵǰ�)
			InitialScaler();				//EMH1A initialize..
			TunnerInitialize();
			SoundInit();
			MUTEON;						//Display Black util normal display
			PanelModulePowerOn;
			PowerOnsequence=PanelLVDSON;
			break;

		case	PanelLVDSON:
			LVDS_ON;
			PowerOnTimer=5;
			PowerOnsequence=PanelInvertPwmON;
			break;

		case	PanelInvertPwmON:
//			DBGputs(" case	PanelInvertPwmON:");
			xEEPROMBuffer[ANALOGBRT_buf]=(BYTE)EEPROM_Read(ANALOGBRT_adr);	//analog PWM 
		
			#ifdef	InvertValueSlope
				//InvertPWM(0xfc - (xEEPROMBuffer[ANALOGBRT_buf]*2.8));
				InvertPWM(0xff - (xEEPROMBuffer[ANALOGBRT_buf]*2.55));
			#else
				InvertPWM(0x3f - xEEPROMBuffer[ANALOGBRT_buf]);
			#endif
			
//			if(DpmsFlag)	{DBGputs("DpmsFlag=1");}
//			else			{DBGputs("DpmsFlag=0");}
//			if(DecoderInit) {DBGputs("DecoderInit=1");}
//			else 			{DBGputs("DecoderInit=0");}
			
			if(DpmsFlag&!DecoderInit)	//2004-05-29
			{	//1.���� ������//2.dpms�϶�.
				VideoDecoderInit();	
				DecoderInit=1;
				
				if(PipOnOffFlag) PipEnableService();
				DpmsFlag=0;
			}
             
            //if(!DpmsFlag&!DecoderInit)	DpmsWakeUpBit=1;	//2004-05-31
            	
			
			OSDstatus = OsdRamClear;			//OSD RAM clear!!
			PowerOnTimer=5;
			PowerOnsequence=PowerOnNormalStatus;
			break;
		
		case	PowerOnNormalStatus:
			//DPMS���� ������� ������ ���Ʈ����.
//			DBGputs(" case	PowerOnNormalStatus:");
			if(DpmsWakeUpBit) 				//DPMS wake-up�� ��� scaler-set�� �Ѿ��.
			{
				ModeTrigger;				//������ ���Ʈ�����Ѵ�.
				DpmsWakeUpBit=0;
				
				#ifdef USE_UART
				DBGputs(" case	PowerOnNormalStatus: ->if(DpmsWakeUpBit)");
				#endif
			}
			
			break;
		
		case	ScalerstableWait:				//ADC�� ��Ʈ�Ŀ� ������� �Ŀ� scaler�� set�Ѵ�.(scaler read�� �Ҿ����� ����)
			//���y�� ����..
			InvertOff;
			OSDstatus = OsdRamClear;			//OSD RAM clear!!
			ScalerSet();
			
			//VideoDecoderInit();//test//2003-11-17
			//PowerOnTimer=5;
			PowerOnTimer=100;
			PowerOnsequence=MenuValueLoadandApply;
			break;
		
		case	MenuValueLoadandApply:
			ArrangeFunctionTable();
			
			xEEPROMBuffer[ANALOGBRT_buf]=(BYTE)EEPROM_Read(ANALOGBRT_adr);	//analog PWM 
			
			switch(CurrentFunction)
			{
				case 0://RGB
					
					#ifdef	InvertValueSlope
					InvertPWM(0xff - (xEEPROMBuffer[ANALOGBRT_buf]*2.55));
					#else
					InvertPWM(0x3f - xEEPROMBuffer[ANALOGBRT_buf]);
					#endif
					
					#if defined(EMH1A)
					WriteScaler(0x62,xEEPROMBuffer[ANALOGCONT]|0x80);	//contrast apply!
					WriteScaler(0x63,xEEPROMBuffer[ANALOGCONT]);
					WriteScaler(0x64,xEEPROMBuffer[ANALOGCONT]);
					#elif defined(EMH2)
						#ifdef WXGA_Panel
						//WriteScaler(0x62,0x80+(100-xEEPROMBuffer[ANALOGCONT]));		//contrast apply!
						//WriteScaler(0x63,0x80+(100-xEEPROMBuffer[ANALOGCONT]));
						//WriteScaler(0x64,0x80+(100-xEEPROMBuffer[ANALOGCONT]));
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
					    
					WriteScaler(0x6b,xEEPROMBuffer[Sharpness_buf]|0x80);
					break;
				
				#ifdef DVI_USE
				case 1://DVI
					#ifdef	InvertValueSlope
					InvertPWM(0xff - (xEEPROMBuffer[ANALOGBRT_buf]*2.55));
					#else
					InvertPWM(0x3f - xEEPROMBuffer[DIGITALBRT_buf]);
					#endif

					#if defined(EMH1A)
					WriteScaler(0x62,xEEPROMBuffer[DIGITALCONT]|0x80);	//contrast apply!
					#elif defined(EMH2)
					WriteScaler(0x62,xEEPROMBuffer[DIGITALCONT]);		//contrast apply!
					#else
					WriteScaler(0x62,xEEPROMBuffer[DIGITALCONT]|0x80);	//contrast apply!
					#endif
					
					WriteScaler(0x63,xEEPROMBuffer[DIGITALCONT]);
					WriteScaler(0x64,xEEPROMBuffer[DIGITALCONT]);
					WriteScaler(0x6b,xEEPROMBuffer[Sharpness_buf]|0x80);
					break;
				#endif
				
				case 2:
				case 3://S_VIDEO
				case 4://TUNER
					InvertPWM(0);	
					
					WriteScaler(0x62,50);		//contrast apply!
					WriteScaler(0x63,50);
					WriteScaler(0x64,50);
					WriteScaler(0x6b,xEEPROMBuffer[Sharpness_buf]|0x80);
					
//					SetAV_Brightness();
//					SetAV_Contrast();					
					break;
/*  youngdo 2003.7.9	
				case 3://S_VIDEO
					#ifdef	InvertValueSlope
					InvertPWM(0xff - (xEEPROMBuffer[S_VIDEOBRT_buf]*2.55));
					#else
						InvertPWM(0x3f - xEEPROMBuffer[S_VIDEOBRT_buf]);
					#endif
					#if defined(EMH1A)
					WriteScaler(0x62,xEEPROMBuffer[S_VIDEOCONT_buf]|0x80);	//contrast apply!
					#elif defined(EMH2)
					WriteScaler(0x62,xEEPROMBuffer[S_VIDEOCONT_buf]);		//contrast apply!
					#else
					WriteScaler(0x62,xEEPROMBuffer[S_VIDEOCONT_buf]|0x80);	//contrast apply!
					#endif
					
					WriteScaler(0x63,xEEPROMBuffer[S_VIDEOCONT_buf]);
					WriteScaler(0x64,xEEPROMBuffer[S_VIDEOCONT_buf]);
					break;
				case 4://TUNER
					#ifdef	InvertValueSlope
					InvertPWM(0xff - (xEEPROMBuffer[TUNERBRT_buf]*2.55));
					#else
						InvertPWM(0x3f - xEEPROMBuffer[TUNERBRT_buf]);
					#endif
					#if defined(EMH1A)
					WriteScaler(0x62,xEEPROMBuffer[TUNERCONT_buf]|0x80);	//contrast apply!
					#elif defined(EMH2)
					WriteScaler(0x62,xEEPROMBuffer[TUNERCONT_buf]);		//contrast apply!
					#else
					WriteScaler(0x62,xEEPROMBuffer[TUNERCONT_buf]|0x80);	//contrast apply!
					#endif
					
					WriteScaler(0x63,xEEPROMBuffer[TUNERCONT_buf]);
					WriteScaler(0x64,xEEPROMBuffer[TUNERCONT_buf]);
					SoundMuteTvTimer=0;
					TunerProcessing = 1;//Tuner setting!!!
					break;
*/					
				case 5://RGB+COMPOSITE
				case 6://RGB+S-VIDEO
					#ifdef	InvertValueSlope
					InvertPWM(0xff - (xEEPROMBuffer[ANALOGBRT_buf]*2.55));
					#else
					InvertPWM(0x3f - xEEPROMBuffer[ANALOGBRT_buf]);
					#endif
					#if defined(EMH1A)
						WriteScaler(0x62,xEEPROMBuffer[ANALOGCONT]|0x80);	//contrast apply!
						WriteScaler(0x63,xEEPROMBuffer[ANALOGCONT]);
						WriteScaler(0x64,xEEPROMBuffer[ANALOGCONT]);
					#elif defined(EMH2)
						#ifdef WXGA_Panel
						//WriteScaler(0x62,0x80+(100-xEEPROMBuffer[ANALOGCONT]));		//contrast apply!
						//WriteScaler(0x63,0x80+(100-xEEPROMBuffer[ANALOGCONT]));
						//WriteScaler(0x64,0x80+(100-xEEPROMBuffer[ANALOGCONT]));
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
					
					WriteScaler(0x6b,xEEPROMBuffer[Sharpness_buf]|0x80);
					break;

				

				case 7://RGB+TUNER
					#ifdef	InvertValueSlope
					InvertPWM(0xff - (xEEPROMBuffer[ANALOGBRT_buf]*2.55));
					#else
					InvertPWM(0x3f - xEEPROMBuffer[ANALOGBRT_buf]);
					#endif
					#if defined(EMH1A)
						WriteScaler(0x62,xEEPROMBuffer[ANALOGCONT]|0x80);	//contrast apply!
						WriteScaler(0x63,xEEPROMBuffer[ANALOGCONT]);
						WriteScaler(0x64,xEEPROMBuffer[ANALOGCONT]);
					#elif defined(EMH2)
						#ifdef WXGA_Panel
						//WriteScaler(0x62,0x80+(100-xEEPROMBuffer[ANALOGCONT]));		//contrast apply!
						//WriteScaler(0x63,0x80+(100-xEEPROMBuffer[ANALOGCONT]));
						//WriteScaler(0x64,0x80+(100-xEEPROMBuffer[ANALOGCONT]));
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
					
					WriteScaler(0x6b,xEEPROMBuffer[Sharpness_buf]|0x80);
					SoundMuteTvTimer=0;
					TunerProcessing = 1;//Tuner setting!!!
					break;
					
				#ifdef DVI_USE
				case 8://DVI+COMPOSITE
					#ifdef	InvertValueSlope
					InvertPWM(0xff - (xEEPROMBuffer[ANALOGBRT_buf]*2.55));
					#else
					InvertPWM(0x3f - xEEPROMBuffer[DIGITALBRT_buf]);
					#endif
					#if defined(EMH1A)
					WriteScaler(0x62,xEEPROMBuffer[DIGITALCONT]|0x80);	//contrast apply!
					#elif defined(EMH2)
					WriteScaler(0x62,xEEPROMBuffer[DIGITALCONT]);		//contrast apply!
					#else
					WriteScaler(0x62,xEEPROMBuffer[DIGITALCONT]|0x80);	//contrast apply!
					#endif
					
					WriteScaler(0x63,xEEPROMBuffer[DIGITALCONT]);
					WriteScaler(0x64,xEEPROMBuffer[DIGITALCONT]);
					WriteScaler(0x6b,xEEPROMBuffer[Sharpness_buf]|0x80);
					break;
				case 9://DVI+S-VIDEO
					#ifdef	InvertValueSlope
					InvertPWM(0xff - (xEEPROMBuffer[ANALOGBRT_buf]*2.55));
					#else
					InvertPWM(0x3f - xEEPROMBuffer[DIGITALBRT_buf]);
					#endif
					#if defined(EMH1A)
					WriteScaler(0x62,xEEPROMBuffer[DIGITALCONT]|0x80);	//contrast apply!
					#elif defined(EMH2)
					WriteScaler(0x62,xEEPROMBuffer[DIGITALCONT]);		//contrast apply!
					#else
					WriteScaler(0x62,xEEPROMBuffer[DIGITALCONT]|0x80);	//contrast apply!
					#endif
					
					WriteScaler(0x63,xEEPROMBuffer[DIGITALCONT]);
					WriteScaler(0x64,xEEPROMBuffer[DIGITALCONT]);
					WriteScaler(0x6b,xEEPROMBuffer[Sharpness_buf]|0x80);
					break;
				case 10://DVI+TUNER
					#ifdef	InvertValueSlope
					InvertPWM(0xff - (xEEPROMBuffer[ANALOGBRT_buf]*2.55));					
					#else
					InvertPWM(0x3f - xEEPROMBuffer[DIGITALBRT_buf]);
					#endif
					#if defined(EMH1A)
					WriteScaler(0x62,xEEPROMBuffer[DIGITALCONT]|0x80);	//contrast apply!
					#elif defined(EMH2)
					WriteScaler(0x62,xEEPROMBuffer[DIGITALCONT]);		//contrast apply!
					#else
					WriteScaler(0x62,xEEPROMBuffer[DIGITALCONT]|0x80);	//contrast apply!
					#endif
					
					WriteScaler(0x63,xEEPROMBuffer[DIGITALCONT]);
					WriteScaler(0x64,xEEPROMBuffer[DIGITALCONT]);
					WriteScaler(0x6b,xEEPROMBuffer[Sharpness_buf]|0x80);
					SoundMuteTvTimer=0;
					TunerProcessing = 1;//Tuner setting!!!
					break;
				#endif
				
				#ifdef	USE_SCART
				case 11:  //SCART
					#ifdef	InvertValueSlope
						InvertPWM(0xff - (xEEPROMBuffer[COMPOSITEBRT_buf]*2.55));						
					#else
						InvertPWM(0x3f - xEEPROMBuffer[COMPOSITEBRT_buf]);
					#endif

					#if defined(EMH1A)
					WriteScaler(0x62,xEEPROMBuffer[COMPOSITECONT]|0x80);	//contrast apply!
					#elif defined(EMH2)
					WriteScaler(0x62,xEEPROMBuffer[COMPOSITECONT]);		//contrast apply!
					#else
					WriteScaler(0x62,xEEPROMBuffer[COMPOSITECONT]|0x80);	//contrast apply!
					#endif

					WriteScaler(0x63,xEEPROMBuffer[COMPOSITECONT]);
					WriteScaler(0x64,xEEPROMBuffer[COMPOSITECONT]);
					WriteScaler(0x6b,xEEPROMBuffer[Sharpness_buf]|0x80);
					
					break;
				case 12://RGB+SCART
					#ifdef	InvertValueSlope
					InvertPWM(0xff - (xEEPROMBuffer[ANALOGBRT_buf]*2.55));
					#else
					InvertPWM(0x3f - xEEPROMBuffer[ANALOGBRT_buf]);
					#endif
					#if defined(EMH1A)
					WriteScaler(0x62,xEEPROMBuffer[ANALOGCONT]|0x80);	//contrast apply!
					#elif defined(EMH2)
					WriteScaler(0x62,xEEPROMBuffer[ANALOGCONT]);		//contrast apply!
					#else
					WriteScaler(0x62,xEEPROMBuffer[ANALOGCONT]|0x80);	//contrast apply!
					#endif
					WriteScaler(0x63,xEEPROMBuffer[ANALOGCONT]);
					WriteScaler(0x64,xEEPROMBuffer[ANALOGCONT]);
					WriteScaler(0x6b,xEEPROMBuffer[Sharpness_buf]|0x80);
					
					break;
				case 13://DVI+SCART
					#ifdef	InvertValueSlope
					InvertPWM(0xff - (xEEPROMBuffer[ANALOGBRT_buf]*2.55));
					#else
					InvertPWM(0x3f - xEEPROMBuffer[DIGITALBRT_buf]);
					#endif
					#if defined(EMH1A)
					WriteScaler(0x62,xEEPROMBuffer[DIGITALCONT]|0x80);	//contrast apply!
					#elif defined(EMH2)
					WriteScaler(0x62,xEEPROMBuffer[DIGITALCONT]);		//contrast apply!
					#else
					WriteScaler(0x62,xEEPROMBuffer[DIGITALCONT]|0x80);	//contrast apply!
					#endif
					
					WriteScaler(0x63,xEEPROMBuffer[DIGITALCONT]);
					WriteScaler(0x64,xEEPROMBuffer[DIGITALCONT]);
					WriteScaler(0x6b,xEEPROMBuffer[Sharpness_buf]|0x80);
					break;
				#endif					
							
				default:
					break;
			}
			
			//ColorTemperature
			if(xEEPROMBuffer[ColorTemp]==0)     
			{
				//SetADCGain(122,145,200);	//SetADCGain(110,133,133);
				SetADCBias(114,127,127);
				SetADCBias(0x32,0x32,0x32);
				
			}//PRESET1
			else if(xEEPROMBuffer[ColorTemp]==1)
			{
				//SetADCGain(147,120,164);	//SetADCGain(133,133,110);
				SetADCBias(127,127,114);
				SetADCBias(0x32,0x32,0x32);
			}//PRESET2
			else//USER MODE                        
			{
				#ifdef	AdcGainSlope
					//SetADCGain((0xfc-(xEEPROMBuffer[ADCREDGAIN_buf]*3.6)),(0xfc-(xEEPROMBuffer[ADCGREENGAIN_buf]*3.6)),(0xfc-(xEEPROMBuffer[ADCBLUEGAIN_buf]*3.6)));
					SetADCGain((0xff-(xEEPROMBuffer[ADCREDGAIN_buf]*2.55)),(0xff-(xEEPROMBuffer[ADCGREENGAIN_buf]*2.55)),(0xff-(xEEPROMBuffer[ADCBLUEGAIN_buf]*2.55)));
					SetADCBias(0x64-xEEPROMBuffer[WhiteBlc_buf],0x64-xEEPROMBuffer[WhiteBlc_buf],0x64-xEEPROMBuffer[WhiteBlc_buf]);
				#else
					SetADCGain((0xff-xEEPROMBuffer[ADCREDGAIN_buf]),(0xff-xEEPROMBuffer[ADCGREENGAIN_buf]),(0xff-xEEPROMBuffer[ADCBLUEGAIN_buf]));
					SetADCBias(0x64-xEEPROMBuffer[WhiteBlc_buf],0x64-xEEPROMBuffer[WhiteBlc_buf],0x64-xEEPROMBuffer[WhiteBlc_buf]);
				#endif
			}
			
			HorizontalValue=(BYTE)EEPROM_Read(CurrentMode*4+0);//HORIZONTAL!(load��.. scaler_set.c����..)
			VerticalValue=(BYTE)EEPROM_Read(CurrentMode*4+1);//HORIZONTAL!(load��.. scaler_set.c����..)
			ClockValue=(BYTE)EEPROM_Read(CurrentMode*4+2);//CLOCK!(load��.. inputdectect.c����..)
			PhaseValue=(BYTE)EEPROM_Read(CurrentMode*4+3);//PHASE!(load��.. inputdectect.c����..)

			PowerOnTimer=5;
			PowerOnsequence=NormalDisplayPrepare;
			break;

		case	NormalDisplayPrepare:
			LED_ON;
			
			if(	xEEPROMBuffer[MainSubInputSource]==22||
				xEEPROMBuffer[MainSubInputSource]==30||
				xEEPROMBuffer[MainSubInputSource]==38||
				xEEPROMBuffer[MainSubInputSource]==46
			) BitWriteScaler(0x9a,0x80,1);//PIP MUTE main display
			

			#ifdef StatusDisplay
			OSDWindows = AnalogSubwindow;
			OSDstatus = NowStatusDisplay;
			
			ArrangeFunctionTable();
			switch(CurrentFunction)
			{
				case 0://ananlog
					OSDcharacters = AnalogSubChars;
					PowerOnTimer=40;
					break;
				case 1://digital
					OSDcharacters = DigitalSubChars;
					PowerOnTimer=40;
					break;
				case 2://composite
					OSDcharacters = CompositeSubChars;
					//PowerOnTimer=150;
					PowerOnTimer=100;
					break;
				case 3://s-video
					OSDcharacters = S_videoSubChars;
					//PowerOnTimer=150;
					PowerOnTimer=100;
					break;
				case 4://Tuner<channel numner display>
					OSDWindows = TunerSubWindow;
					OSDcharacters = ChannelNumChars;
					OSDstatus = TVchannelDisplay;
					PowerOnTimer=150;
					break;
				case 5://RGB+COMPOSITE
					OSDWindows = PIPSubWindow;
					OSDcharacters = PipRgbCompositeChars;
					PowerOnTimer=40;
					break;
				case 6://RGB+SVIDEO
					OSDWindows = PIPSubWindow;
					OSDcharacters = PipRgbSvideoChars;
					PowerOnTimer=40;
					break;
				case 7://RGB+TUNER
					OSDWindows = PIPSubWindow;
					OSDcharacters = PipRgbTunerChars;
					PowerOnTimer=40;
					break;
				
				#ifdef DVI_USE
				case 8://DVI+COMPOSITE
					OSDWindows = PIPSubWindow;
					OSDcharacters = PipDviCompositeChars;
					PowerOnTimer=40;
					break;
				case 9://DVI+SVIDEO
					OSDWindows = PIPSubWindow;
					OSDcharacters = PipDviSvideoChars;
					PowerOnTimer=40;
					break;
				case 10://DVI+TUNER
					OSDWindows = PIPSubWindow;
					OSDcharacters = PipDviTunerChars;
					PowerOnTimer=40;
					break;
				#endif
				
				#if defined(USE_SCART)
				case 11://composite
					OSDcharacters = ScartSubChars;
					PowerOnTimer=150;
					break;
				case 12://RGB+SCART
					OSDWindows = PIPSubWindow;
					OSDcharacters = PipRgbScartChars;
					PowerOnTimer=40;
					break;

				case 13://DVI+SCART
					OSDWindows = PIPSubWindow;
					OSDcharacters = PipDviScartChars;
					PowerOnTimer=40;
					break;
				#endif	
				
				default:
					break;				
			}
			#endif
			
			#ifdef	PipDpmsON	//r+ c/sv/tv ���
			if(~DpmsPipFlag)	MUTEOFF;
			#else
			MUTEOFF;
			#endif
			
			PowerOnsequence = DisplayLightOnstatus;
			break;
		
		case	DisplayLightOnstatus:
			ArrangeFunctionTable();
			//Volume Path����
			switch(CurrentFunction)//Volume Paht ����.
			{
				case 0://ananlog
				case 1://digital
					#if	defined(BtcBoard_Option) 		
						AudioSelection_PC;
						break;
					#endif		
											
				case 2://composite
				case 3://s-video
				case 5://RGB+COMPOSITE
				case 6://RGB+SVIDEO
				case 8://DVI+COMPOSITE
				case 9://DVI+SVIDEO				
					#if	defined(BtcBoard_Option) 		
						AudioSelection_AV;					
					#else				
						AudioSelection_LOW;
					#endif
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
				#if defined(USE_SCART)			
				case	11:               	// SCART input?
				case 	12:			//PIP R+SCART
				case	13:			//PIP D+SCART
					AudioSelection_SCART
					break;	
				#endif
				
				default:
					break;
			}
			
			InvertOn;
			
			if(!SoundMuteOnFlag)	//Not sound mute status, then Turn on sound!!
			switch(CurrentFunction)
			{
				case 0://ananlog
				case 1://digital
				case 2://composite
				case 3://s-video
				case 5://RGB+COMPOSITE
				case 6://RGB+SVIDEO
				case 8://DVI+COMPOSITE
				case 9://DVI+SVIDEO
				default:
				#if defined(USE_SCART)			
				case	11:               	// SCART input?
				case 	12:			//PIP R+SCART
				case	13:			//PIP D+SCART
				#endif
					// Sound activate.	//smpark
					SOUNDSTBY_ON;
					SOUNDSTBY_OFF;
					// DelayTimer=41;
	 				//while(DelayTimer!=0) {NOP;}
					idelay5m(30);//150ms delay
					
					Mute_SoundOn;//Sound Active!!
					PutVolumePWM();
					break;
			}
			
			PowerOnTimer=1;
			PowerOnsequence = GeneralStatus;//Goto GeneralStatus
			break;
				
		case	GeneralStatus:		//����....
			if(FactoryDftFlag&&!YouGoingInitialize)
			{
				Auto_Func();
				xEEPROMBuffer[FactoryReset_buf]=FactoryDftFlag=0;
				EepromSetQue(FactoryReset_adr,xEEPROMBuffer[FactoryReset_buf]);
			}
			break;
		
		case	CheckCableMessage:
			InvertOn;
			LED_ON;
			
			DpmsFlag=1;
			DecoderInit=0;
			
			PowerOnsequence=BeforeFreeRunScalerInit;	//2004-06-01
			#ifdef	PipDpmsON
			PowerOnsequence=FreeRunStatus;	//2003-09-24	//pip on���¿��� dpms�� ���� �����Ҷ� �������� �ϱ����� ����.
			#endif
			PowerOnTimer = 1000;	//5sec
			break;
		
		
		case	OutOfFreqStatus:
			InvertOn;
			LED_ON;
			PowerOnsequence = OnlyLedOnOffStatus;	//���״�� LED�� On<->Off, dpms(inverter off�ȵ�) �׷��� ����..
			
			#ifdef	PipDpmsON
			PowerOnsequence=FreeRunStatus;	//2003-09-24	//pip on���¿��� dpms�� ���� �����Ҷ� �������� �ϱ����� ����.
			#endif
			PowerOnTimer = 1;	//5sec
			break;
		
		case	OnlyLedOnOffStatus:
			LedOnOffBit ^= 1;
			if(LedOnOffBit) {LED_OFF;}
			else {LED_ON;}
			PowerOnTimer=200;
			break;
		
		case	BeforeNoVideoScalerInit:
			#if	defined(BtcBoard_Option) 		
			AudioSelection_PC;
			#else					
			AudioSelection_LOW;	//path����...,TV����� �̰����� �ͼ� �н��� �����ȵǰ� ������ ������
			#endif			
			
			Mute_SoundOff;		//Sound Off~~,TV������ ��µȴ�.
			InitialScaler();
			MUTEON;
			
			OSDWindows = AnalogSubwindow;
			
			ArrangeFunctionTable();
			switch(CurrentFunction)
			{
				case 2://composite
					OSDcharacters = CompositeSubChars;
					break;
				case 3://s-video
					OSDcharacters = S_videoSubChars;
					break;
				
				#if defined(USE_SCART)			
				case	11:               	// SCART input?
					OSDcharacters = ScartSubChars;
					break;	
				#endif					
			}
			OSDstatus = NowStatusDisplay;
			PowerOnsequence = AfterNoVideoScalerInit;
			PowerOnTimer=30;
			break;
		
		case AfterNoVideoScalerInit:
			InvertOn;
			PowerOnsequence = NoVideoStatus;
			PowerOnTimer=0;
			break;
		
		case NoVideoStatus:	//No-Video ����..
			Mute_SoundOff;
			break;
			
		
		case	BeforeCheckCableScalerInit:
		case	BeforeFreeRunScalerInit:
			//if(PipOnOffFlag) WriteScaler(0x9a,0x80);	//2004-06-03//test
			//BitWriteScaler(0x9a,0x80,1);

			Mute_SoundOff;	//Sound Off~~
			MUTEON;//
			InvertOff;

			ADCDisable;//2003-01-28 5:44����
			InitialScaler();
						
			MUTEON;
			
			
			OSDWindows = AnalogPowerSaverWindow;
			OSDstatus = Nosignal_Display;	//NO SIGNAL OSD display!!
			
			if(PowerOnsequence==BeforeFreeRunScalerInit)
			{
				//void idelay5m(BYTE time);////test
				switch(xEEPROMBuffer[MainSubInputSource])
				{
					
					//RGB
					case 2:	//rgb(no)
					case 22://r+c(no)
					case 30://r+sv(no)
					case 54://r+tv(no)
					//case 0:	//rgb
					//case 20://r+c
					//case 28://r+sv
					//case 52://r+tv
						OSDcharacters = AnalogPowerSaverChars;
						break;

					case 0:	//rgb
					case 20://r+c
					case 28://r+sv
					case 52://r+tv
						//PowerOnsequence=DisplayLightOnstatus;	//2003-10-21
						OSDcharacters = AnalogPowerSaverChars;
						//LED_OFF;//test
						//while(1);//test
						//return;
						break;

					
					//DVI
					case 4:
					case 6:
					case 36:
					case 38:
					case 44:
					case 46:
					case 60:
						OSDcharacters = DigitalPowerSaverChars;
						break;
				}	
				PowerOnsequence = FreeRunStatus;
				//LED_OFF;idelay5m(20);LED_ON;idelay5m(20);LED_OFF;idelay5m(20);LED_ON;idelay5m(20);//test//2004-05-14
			}
			else
			{
				PowerOnsequence = CheckCableMessage;
				OSDcharacters = CheckSignalCableChars;
			}
			PowerOnTimer = 1;
			break;

		//------------------------------------------------------------
		case	FreeRunStatus:
			InvertOn;
			Mute_SoundOff;	//Sound Off~~
			LED_ON;
			PowerOnsequence = DPMSOff;
			DecoderInit=0;//
//			DBGputs("case	FreeRunStatus: PowerOnsequence = DPMSOff");
			PowerOnTimer = 300;//1.5sec	2000;//10sec!!,  OSD on!!
			break;
			
		case	DPMSOff:
			OSDstatus = OSDoff;
			Mute_SoundOff;	//Sound Off~~
			InvertOff;				//Invert Off!!
			PanelModulePowerOff;	//PanelModule Poweroff!!
			LM2596Disable;
			DpmsFlag=1;
			DecoderInit=0;
//			DBGputs(" case DPMSOff exe.");
			
			PowerOnsequence = DPMSLedOnOff;
			PowerOnTimer = 200;
			break;
		//-------------------------------------------------------------
		case	DPMSLedOnOff:
			LedOnOffBit ^= 1;
			if(LedOnOffBit) {LED_OFF;}
			else {LED_ON;}
			PowerOnTimer=200;
			break;

		case	WakeUpFreeRun:
			NoExistHfreq=0;
			NoExistVfreq=0;
			//PIP ����� �����Ѵ�.	//2003-08-25 8:56����
			//if( !(CurrentFunction>=5&&CurrentFunction<=10) ) DpmsWakeUpBit = 1; 	// pip�� ��� ���ܽ�Ŵ.
			DpmsWakeUpBit = 1;
			PowerOnsequence = MainPowerON;

			PowerOnTimer=5;
			break;

		default:
			break;
	}


//****************************************************************//
//Power-Off Sequence
//****************************************************************//
	if(!PowerOffTimer)
	switch(PowerOffsequence)
	{
		case	PanelInvertOFF:
			//MUTEON;	//2003-08-25
			LED_OFF;
			OSDstatus = OsdRamClear;		//OSD CLEAR!!
					
			Mute_SoundOff;				//Sound Off~~
			InvertOff;
			EepromSetQue(POWERID_adr,0x00);		//PowerOff ID write 
			PowerOffTimer = 2;
			
			++PowerOffsequence;	
			break;             	
			                   	
		case	PanelInvertPwmOFF:			//#define	PanelInvertPwmOFF	5
			InvertPwmOFF;
			////MuteOff_VolumeDown //2003.6.23 youngdo  VIDEOdisable;				//VideoDiable!
			Mute_SoundOff;
 			TW9908_RSTON;
			PowerOffTimer = 2;
			++PowerOffsequence;
			break;

		case	PanelPowerOFF:
			PanelModulePowerOff;
			PowerOffTimer = 5;
			++PowerOffsequence;
			break;

		case	MainPowerOFF:
			LVDS_OFF;
			ADCDisable;
			LM2596Disable;
			DVIDisable;
			RamClear();
			ArrangeFunctionTable();
			
			++PowerOffsequence;
			break;

		case	PowerOffNormalStatus:
			if(YouGoingInitialize)
			{
				PowerOffTimer=600;
				YouGoingInitialize=0;
				PowerOffsequence=SystemInitstatus;
				SystemInitialize();
			}
			break;
		
		case	SystemInitstatus:
				PowerOffsequence=0;
				PowerOffTimer=0;
				ModeTrigger;		//������ ���Ʈ�����Ѵ�.
				KEY_value = PowerKey;	//4���Ŀ� �Ŀ��� Ų��.
			break;
			
		default:
			break;		
	}
}


void InvertSmartStart()
{
	BYTE i;
	for(i=0;i<(0xff - (xEEPROMBuffer[ANALOGBRT_buf]*2.55));i++){
	InvertPWM(i);	
	}
}

