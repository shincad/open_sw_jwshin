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


#if	defined(MCU_MTV230)
#include	"MTV230xfr.h"
#elif	defined(MCU_MTV412)
#include	"MTV412xfr.h"
#elif	defined(MCU_NT68F63)
#include	"NT68F63.h"
#endif

#include "EEPROMadr.h"
#include "extern.h"
#include <stdio.h>
#include "tw990x.h"
#include "sprocessor.h"
#include "..\tuner.h"//test
//****************************************************************//
//�Լ�����
//****************************************************************//
void Inputdetect(void);
void Keydetect(void);
void MenuPan(void);
extern	void PeriDevice_set(void);
void ExternalComm(void);
void OsdService(void);
void PutEMH2(BYTE address, BYTE Recdata);
BYTE GetEMH1A(BYTE address);
void PowerSequence(void);
BYTE EEPROM_Read(WORD address);
void EepromSetQue(WORD address, BYTE Recdata);
void AutoDisplayadjust(void);
void VideoProcess(void);
void TunerProcess(void);
void RemoconProcess(void);
void ArrangeFunctionTable(void);
void SystemInitialize(void);
void TunnerInitialize();
extern	void PutData(void);
extern	void	PipEnableService(void);
//extern 	void PreInit(void);

#if	defined(BtcBoard_Option) 
void TVParameterInit();
//void TVCountrySet();
//void SoundInit();
void	SoundProcess();
#endif
void  CheckTenMin( );
void	CheckTemMinSave();

#ifdef BURNING_TEST
void	BunrningProcess(void);
#endif
//******************************* DDC Function 2004.06.01 +jwshin *****//
#ifdef DDC_ENABLE
BYTE	mPtrDDC2	_at_	0x19;              // DDC2 counter


void InitDDC(void)
{
	xSLVBADR = 0x80|(0x54>>1); 
	                          
	xSLVAADR = 0x80|(0xa0>>1);
	xINTENI2C = 0x1C + 0xE2;                // DDC2 Interrupt Enable

	mPtrDDC2 = 0;

	EX1 = 1;
}

#endif
/////////////////////////////////////////////////////////////////////
//	Main Routine!!
/////////////////////////////////////////////////////////////////////
void main(void)
{
	BYTE temp;

//****************************************************************//
//������ XFR �ʱ�ȭ.				
//****************************************************************//

#if	defined(MCU_MTV230)
	MTV230XfrSet;

#if	defined(USE_UART) 	//youngdo 2003.5.17
	xPADMOD1 = 0x01;
#endif

#elif	defined(MCU_MTV412)
	MTV412XfrSet;
#elif	defined(MCU_NT68F63)
	NT68F63XfrSet;
#endif

//****************************************************************//
//�ý��۽����ϸ鼭 �߿��� ��Ʈ �ʱ�ȭ
//****************************************************************//
	_SCALER_RST_HIGH;		//scaler RESET Active "Low"
	_PowerON;			//LM2596 or 2576 Low active enable
	PanelModulePowerOff;		//low
	InvertOff;			//low
	InvertPwmOFF;			//stable low
	_SCALER_CS_HIGH;		//high
	LVDS_OFF;			//shutdown LVDS(low)
	SCLK =1;			//low
	CLKINV_HIGH;			//AD9884 clock invert high output
	DVIDisable;			//DVI(SIL151A)disable
	LED_OFF;	
	//MuteOff_VolumeDown; //2003.6.23 youngdo //VIDEOdisable;			//Decoder disbale(For VPC3230)
	Mute_SoundOff;			//
	
#if	defined(BtcBoard_Option) 		
	AudioSelection_PC;
#else
	AudioSelection_HIGH;
#endif
	AsyncOn;			//sync input(Fr D-SUB)
	ADCDisable;
	//MTV230OSDInit;	//2003-10-24 remoded

#if	defined(BtcBoard_Option) 
	TW9908_RSTON;
	SOUNDSTBY_ON;
#endif

//****************************************************************//
//External I2C �ʱ�ȭ �� ���ͷ�Ʈ �ο��̺�
//****************************************************************//
	EXT_I2C_Enable;


//****************************************************************//
//Timer0 �ʱ�ȭ �� ���ͷ�Ʈ �ο��̺�
//****************************************************************//
	Timer0InterruptSet;


//****************************************************************//
//Remocon���� Ÿ�̸�1,�ܺ����ͷ�Ʈ �ο��̺�
//****************************************************************//
#ifdef USE_remocon
	EXT0_Timer1InterruptSet;
#endif

#ifdef	USE_UART
	//initital UART Data for debug.....(4800.N.8.1)
	// Timer setup
	TMOD &= 0x0f;	// TMOD High nibble clear
	TMOD |= 0x20;	// Timer1 8bit Auto Reload Mode.
	TL1   =  0xf3;	//if TL1 overflow, TL1 autoreload with TH1.
	TH1   =  0xf3;	// 0xf3=4761bps, f9=8928bps  fa=10416bps, fb=12500bps, fc=15625bps, fd=20661bps(���� ������)
	TCON &= 0x3f;	// Timer1 overflow flag, Timer1 run control bit <- 0���� ����ŷ.
	TCON |= 0x40;	// Timer1 Run!
   	SCON = 0x52;
   	PCON |= 0x80;
	//UART data initial end
#endif


//****************************************************************//
//��ü���ͷ�Ʈ�ʱ�ȭ
//****************************************************************//
	EA	= 1;

//****************************************************************//
//EMH1A backup buffer Ŭ����
//****************************************************************//
	for(temp = 0; temp<0xff; temp++) //External Ram Clear,
	{
		#ifdef	MCU_NT68F63			//NovaTek�������� �����ֱ�� watchdog Ŭ����!
		WDTClear;
		#endif
		PutEMH2(temp,0x00);
	}

//****************************************************************//
//BoardID�� �о� ���� ������ �ʱ�ȭ �Ѵ�.
//mode<clock,hposition,vposition,phase���� �ʱ�ȭ�� PeriDevice_set()���� page write�� �̿��Ѵ�.
//MTV212,230,NT68F63
//MTV212(!!)�� �������� �޸��Ѵ�.
//****************************************************************//
#ifdef USE_UART
	DBGputs("Start");
#endif

#if defined(MCU_MTV230)||defined(MCU_NT68F63)||defined(MCU_MTV412)

	//DBGputss(EEPROM_Read(EEPROMVERSION_adr));DBGputs("\n");
	//DBGputss(EEPROM_Read(Version_adr));DBGputs("\n");
	
	if((EEPROM_Read(EEPROMVERSION_adr) != MyboardID)
	||( EEPROM_Read(Version_adr)!=BTC_Version))
		{	
		CheckTemMinSave();
		SystemInitialize();	
		//TVCountrySet();	
	}
	else{
		for(temp=0;temp < TotalEeprom;temp++)
		{
			 xEEPROMBuffer[temp] = (BYTE)EEPROM_Read(BaseEEPROM_adr+(temp));//EEPROM�� ����� �߿䰪�� �ø���
		}
//		LED_ON;
		YouHaveToInitMode=0;
		YouHaveToInitTVchannel=0;
	}
#endif

//*********************************************
//TW9908�� �������� �Ѵ�.
//*************************************************

#if	defined(BtcBoard_Option) 
//	AVDecoderSleep();			//poweroff �����̹Ƿ� �ʿ���� 

	TVParameterInit();
//	xEEPROMBuffer[MainSubInputSource]=2;			//for test
//	EepromSetQue(MainSubInputSource_adr,2);			//for test 
#endif

//****************************************************************//
//PowerID�� �д´�
//****************************************************************//

	#if defined(Always_PowerOn)
		KEY_value = PowerKey;
		EepromSetQue(POWERID_adr,0x55);
	#else
		temp = (BYTE)EEPROM_Read(POWERID_adr);
		//temp = xEEPROMBuffer[POWERID_buf];
		if(temp==0x55) KEY_value = PowerKey;
		else KEY_value = 0;
	#endif

//****************************************************************//
//MODE(analog, dvi, composite, s-video) ����.
//EEPROM���� �о� ������ ����� ������ �־�д�.
//OSD���� �� ��Ÿ���ۿ��� �����Ѵ�.
//****************************************************************//
	ArrangeFunctionTable();

//****************************************************************//
	//eeprom ���尪 �̿��� ���� �ʱ�ȭ
//	PreInit();
	
//****************************************************************//
#ifdef DDC_ENABLE
	InitDDC();
#endif
	while(1){
		while(!TimerBit);	//TimerBit=0�� ���ȿ� ���ѷ��� (TimerBit=1�϶����� ��ٸ���)

		#ifdef	MCU_NT68F63
		P2 = 0xF0;
		WDTClear;
		#endif
		
		LoopEnd = 0;	//<-5ms.�ֱ�� ����.
		TimerBit=0;
		if(PowerOnTimer) PowerOnTimer--;
		if(PowerOffTimer) PowerOffTimer--;
		if(OSDofftimer) OSDofftimer--;
		if(SyncStableTimer) SyncStableTimer--;
		if(TunerProcessTimer)TunerProcessTimer--;
		if(SoundProcessTimer)SoundProcessTimer--;
		// SOUND CHECK TIMER //smpark 20030725
		if(KeyStepTimer)	KeyStepTimer--;	//2004-06-18
		if(KeyActionTimer)	KeyActionTimer--;	//2004-06-30
		if(xEEPROMBuffer[Sleep_buf])				//10~90�� �϶�//2003-07-31 by thkim
		{
			SleepTimer--;
			if(SleepTimer==0)	KEY_value=PowerKey;	// SleepTimer=0�̸� power off
		}
		if(PipMuteTimer)	PipMuteTimer--;
		//****************************************************************//
		Inputdetect();		//PC,DVI H/V check.
		Keydetect();		//Key check.
		//////////////////////////////////////////////
		MenuPan();		//at "keymenu.c"
		PeriDevice_set();
		PowerSequence();

		#ifdef BURNING_TEST			// +jwshin Burning Mode 040813
		if(BurningFlag)	BunrningProcess();
		#endif
		OsdService();		//at "_osdmenu.c"
		/////////////////////////////////////////////
		AutoDisplayadjust();
		VideoProcess();
		TunerProcess();

	#ifdef	USE_remocon
		RemoconProcess();
	#endif

		if(SoundTimer==0) SoundProcess();
		
		CheckTenMin();		//youngdo 2003.8.16  ���ð� ���� 
		
/*
		switch(SoundProcessStatus){
			case SoundType_MONO:
				DBGputs("SoundType_MONO\n");
				break;
			case SoundType_SAP:
				DBGputs("SoundType_SAP\n");
				break;
			case SoundType_STEREO:
				DBGputs("SoundType_STEREO\n");
				break;
		}
*/
		LoopEnd = 1;
	}
//****************************************************************//
}

// by ohpal 1.2 New Function
void  CheckTenMin()
{
	BYTE  temp,i,Carry;
	if(SetMin==0) return;
	SetMin=0;
	temp=EEPROM_Read(TenTimeCheck_adr);
	
	if(temp < 5){
		EepromSetQue(TenTimeCheck_adr,temp+1);
	}
	else{		
		EepromSetQue(TenTimeCheck_adr,0);
		Carry=1;
        	for(i=1;i<6;i++){
			temp=EEPROM_Read(TenTimeCheck_adr+i);
        		if((temp+Carry)<10){
				//WriteEEPROM(ep_Page(TenTimeCheck_adr),ep_Addr(TenTimeCheck_adr)+i,temp+Carry);
				EepromSetQue(TenTimeCheck_adr+i,temp+Carry);
				Carry=0;
			}
			else {
				//WriteEEPROM(ep_Page(TenTimeCheck_adr),ep_Addr(TenTimeCheck_adr)+i,0);
				EepromSetQue(TenTimeCheck_adr+i,0);
				Carry=1;
			}
		}
	}
}   

