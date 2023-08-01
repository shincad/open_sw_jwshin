#include "8051.H"
#include "STDIO.H"
#include "RAM.H"
#include "MCU.H"
#include "MyDef.H"
#include "IIC.H"
#include "F63XREG.H"
#include "F63XDEF.H"
#include "UserAdj.H"
#include "Scaler.H"
#include "rom_map.h"
#include "AutoAdj.H"
#include "OSD.H"
#include "OSD_TAB.H"
#include "OSD_TAB2.H"
#include "MODEHANDLE.H"
#include "Tuner.h"
//#include "dvKeypad.h"
#include "PANEL.H"

/*
code unsigned short LG_IR_Tab[]={
	0x08f7,0x8877,0x48b7,0xc837,0x28d7,0xa857,0x6897,0xe817,
	0x18e7,0x9867,0x58a7,0xffff,0xffff,0xffff,0xd02f,0x906f,
	0x10ef,0xffff,0x22dd,0xc23d,0xaa55,0xffff,0xffff,0xffff,
	0xffff,0xffff,0xffff,0xffff,0x00ff,0x807f,0x2ad5,0xaa55,
	0x40bf,0xc03f,0x708f,0xf00f,0xffff,0xffff,0xffff,0xffff,
};
code unsigned char IR_KeyTab[]={
	0x80,  0x81,  0x82,  0x83,  0x84,  0x85,  0x86,  0x87,
	//0,        1,        2,        3,       4,       5,       6,       7,
	0x88,  0x89,  0x8a,  0x8b,  0x8c,  0x8d,  0x8e,  0x8f,
	//  8,       9,    10,	   11 ,	 12   , pre   ,source,   mute,
	0x90,  0x91,   0x92,  0x93,  0x94,  0x95,  0x96,  0x97,
	//pwr, Set,  menu,   auto, display,Analog, DVI, Video,
	0x98,  0x99,  0x9a,  0x9b,  0x9c,  0x9d,  0x9e,  0x9f,
	//S-vi, TV  ,         ,         ,ch-up,   ch-d, 자동체널, exit,
	0xa0,  0xa1,  0xa2,  0xa3,  0xa4,  0xa5,  0xa6,  0xa7
 //vol-u, vol-d, sleep, Air-Cable,
};
*/
code unsigned short LG_IR_Tab[]={			// Platys Remocon Value 적용 +jwshin 051028
	0x28D7,0x18e7,0x9867,0x00ff,0x807f,0x40bf,0xc03f,0x20df,	//power,source,mute,0,1,2,3,4
	0xa05f,0x609f,0xe01f,0x10ef,0x906f,0x08f7,0x708f,	//5,6,7,8,9,ch up,ch down
	0xc837,0xa857,0x6897,0xd827,					//menu,vol down,vol up,exit
};
code unsigned char IR_KeyTab[]={
	0x28,0x18,0x98,0x00,0x80,0x40,0xc0,0x20,
	0xa0,0x60,0xe0,0x10,0x90,0x08,0x70,
	0xc8,0xa8,0x68,0xd8,				
};

code unsigned char IR_CodeTab[]={
	0x90,0x91,0x8f,0x80,0x81,0x82,0x83,0x84,
	0x85,0x86,0x87,0x88,0x89,0x9c,0x9d,
	0x92,0xa1,0xa0,0x40,
};

extern WarmUp();

void InitMCU(void)
{
	Byte xdata *Addr;
	Byte i;
	Addr = 0xf000;
	for(i=0; i<0x23; i++){
		*Addr++ = McuRegTab[i];
	}
// set timer 0
 	SCON = 0x52;
 	TMOD = 0x22;	//timer0 /timer1 8 bits auto reload
// 	TMOD = 0x21;	//timer0 16 bits/timer1 8 bits auto reload
 	PCON = 0x80;
// timer0 8 bits auto reload
	TL0 = -200;
	TH0 =-200;
//	TL0 = 256-(CPU_CLK/1000*100/12000); //time base 100us
//	TH0 = 256-(CPU_CLK/1000*100/12000);

// timer0 16 bits
//	TL0 = (65536-CPU_CLK/1200)%256;	//time base 10ms
//	TH0 = (65536-CPU_CLK/1200)/256;

// For 12.000 MHz 
 	TL1 = 256-(2*CPU_CLK/384/9600);
 	TH1 = 256-(2*CPU_CLK/384/9600);
// For 14.318 MHz 
 	//TL1 = 256-(2*CPU_CLK/384/4800);
 	//TH1 = 256-(2*CPU_CLK/384/4800);
	TR0 = 1;		//start timer0
 	TR1 = 1;		//start timer1
// set interrupt
	EX1 = 1;		//enable External interrupt1
	ET0 = 1;		//enable timer0 interrupt
	EA = 1;			//enable all interrupt
	T0_INT_CNT = 0;
	T0_10ms_Cnt = 0;
	cntIR_Data = 0;
	IR_Status = cIR_START;
//	IR_KeyBuffer = 0xff;
	IR_KeyTemp = 0xfb;
	IR_RepeatTimer = 40;
	bIR_Change=0;
	bIR_Active = 0;
	VideoTest = 1;
//	Sleep(50);	// -jwshin 050729
	NoSigTimer = 100;		// +jwshin 051101 Added...
	SoundRGB();			// 74HC4052 Port Initialization...    +jwshin 051128
	Sleep(50);
	SoundRGB();			// Re-Initialization...		한번 더 Port 초기화...  +jwshin 051128
	StatusFlag = 0;			// Initialization... +jwshin 051128
	
}

void Timer0(void) interrupt 1 using 2
{
#if 1	//Used mode2--auto reload
	if(IR_Timer != 0xfff)
		IR_Timer++;
	if(++T0_INT_CNT >= 10){
		T0_INT_CNT = 0;
		if(Timer1 != 0)			// 1ms
			Timer1--;
		if(++T0_1ms_Cnt >= 10){	// 10ms
			CLRWDT = 0x55;
			T0_1ms_Cnt = 0;
			if(Timer2 != 0)
				Timer2--;
			if(Timer3 != 0)
				Timer3--;

			if(++T0_10ms_Cnt >= 100){//--1s
				T0_10ms_Cnt = 0;
				if(BackLightTimerEn){
					if(BackLightTimer < 360000000)
						BackLightTimer += 1;
					else
						BackLightTimer = 0;
				}
			}
			if(NoSigTimer > 0) 	// +jwshin 051101 Added...
				NoSigTimer--;
			if(OsdTimer > 0)
				OsdTimer--;
			if(LocalTimer > 0)
				LocalTimer--;
			if(PowerTimer > 0)
				PowerTimer--;
			if(RepeatTimer > 0)
				RepeatTimer--;
			if(DDCTimer > 0)
				DDCTimer--;
			if(SaveTimer > 0)
				SaveTimer--;
			if(VideoTimer > 0)
				VideoTimer--;
			if(BurnInTimer > 0)
				BurnInTimer--;
			if(MuteTimer > 0)
				MuteTimer--;		
			if(IR_RepeatTimer > 0) 
				IR_RepeatTimer--;
			if(IR_WaitTimer>0) IR_WaitTimer--;
			
		}
	}

#else	//Used mode1--16 bits counter
	TL0 = (65536-CPU_CLK/1200)%256; //time base 10ms
	TH0 = (65536-CPU_CLK/1200)/256;
	CLRWDT = 0x55;
	if(++T0_10ms_Cnt >= 100){
		T0_10ms_Cnt = 0;
		if(BackLightTimerEn){
			if(BackLightTimer < 360000000)
				BackLightTimer += 1;
			else
				BackLightTimer = 0;
		}
	}
	if(OsdTimer > 0)
		OsdTimer--;
	if(LocalTimer > 0)
		LocalTimer--;
	if(RepeatTimer > 0)
		RepeatTimer--;
	if(PowerTimer > 0)
		PowerTimer--;
	if(DDCTimer > 0)
		DDCTimer--;
	if(SaveTimer > 0)
		SaveTimer--;
	if(VideoTimer > 0)
		VideoTimer--;
	if(BurnInTimer > 0)
		BurnInTimer--;
	if(MuteTimer > 0)
		MuteTimer--;
#endif
	
}

void Sleep(Word T)
{
	Word i,j;
	for(j=0;j<T;j++)
		for(i=0;i<53*(CPU_CLK/20000000);i++)
			CLRWDT=0x55;
}

void WaitSetup(unsigned short time)
{
	LocalTimer = time;			/* timeout n ms */
	while(LocalTimer != 0){
		if(FuncBuf[pVIDEOSOURCE] < cSVIDEO) //jacky20040324
			CheckModeChange();
	}
}

Byte GetKey()
{
 	Byte i,KeyTemp,KeyTemp2;
	i = 0;
 /*
 	while(i < 10)
		{
		KeyTemp = 0;
		if(!(PTA_REG & PA5))
			KeyTemp = vkSOURCE;
		if(!(PTA_REG & PA0))
			KeyTemp = vkMENU;
		if(!(PTA_REG & PA4))
			KeyTemp = vkAUTO;
		if(!(PTA_REG & PA3))
			KeyTemp = vkPOWER;
		if(!(PTA_REG & PA1))
			KeyTemp = vkVALUP;
		if(!(PTA_REG & PA2))
			KeyTemp = vkVADOWN;
		if(!(PTA_REG & PA3))
			KeyTemp = vkPOWER;
		if(!(PTD_REG & PD0))
			KeyTemp = vVOLUME;
		if(!(PTD_REG & PD6))
			KeyTemp = vkMONSEL;
		if(KeyTemp != KeyTemp2)
			{
			KeyTemp2 = KeyTemp;
			i = 0;
			}
		i++;
 		}  */
 	while(i < 10) {
 	//-------------------------------- +jwshin 061025   AD Method로 인한 routine 변경...	
 		KeyTemp = 0;
		ADC_CON = (STRT_ADC | EN_ADC1);		//Channel;  // Start AD Convert
//		ShowDebug(MAINMENU_RES_ADDR,RES_COLOR,(ADC1_REG & 0x7f));		// +jwshin 061019
		if((ADC1_REG & 0x7f) == 0) {
			KeyTemp = vkPOWER;
		}
		if((ADC1_REG & 0x7f) >= 36 && (ADC1_REG & 0x7f) <= 38) {
			KeyTemp =  vkSOURCE;
		}
		if((ADC1_REG & 0x7f) >= 95 && (ADC1_REG & 0x7f) <= 97) {
			KeyTemp =  vkVALUP;
		} 
		if((ADC1_REG & 0x7f) >= 108 && (ADC1_REG & 0x7f) <= 110) {
			KeyTemp =  vkVADOWN;
		}
		if((ADC1_REG & 0x7f) >= 118 && (ADC1_REG & 0x7f) <= 120) {
			KeyTemp =  vkMENU;
		}
		if((ADC1_REG & 0x7f) >= 59 && (ADC1_REG & 0x7f) <= 61) {
			KeyTemp = vkRIGHT;
		}
		if((ADC1_REG & 0x7f) >= 78 && (ADC1_REG & 0x7f) <= 80) {
			KeyTemp = vkLEFT;
		} 
/*		
		if((ADC1_REG & 0x7f) >= 101 && (ADC1_REG & 0x7f) <= 103) {
			KeyTemp = vkPOWER;
		}
		if((ADC1_REG & 0x7f) >= 111 && (ADC1_REG & 0x7f) <= 113) {
			KeyTemp =  vkSOURCE;
		}
		if((ADC1_REG & 0x7f) >= 98 && (ADC1_REG & 0x7f) <= 100) {
			KeyTemp =  vkVALUP;
		} 
		if((ADC1_REG & 0x7f) >= 93 && (ADC1_REG & 0x7f) <= 95) {
			KeyTemp =  vkVADOWN;
		}
		if((ADC1_REG & 0x7f) >= 88 && (ADC1_REG & 0x7f) <= 90) {
			KeyTemp =  vkMENU;
		}
		if((ADC1_REG & 0x7f) >= 104 && (ADC1_REG & 0x7f) <= 106) {
			KeyTemp = vkRIGHT;
		}
		if((ADC1_REG & 0x7f) >= 109 && (ADC1_REG & 0x7f) <= 111) {
			KeyTemp = vkLEFT;
		}
*/		
		
		
		if(KeyTemp != KeyTemp2)
			{
			KeyTemp2 = KeyTemp;
			i = 0;
			}
		i++;
	//----------------------------------
 	}
	return KeyTemp;
}


void ScanKeyPad(void)	//2003/5/19 alvin
{
	Byte KeyTemp;
	KeyTemp = GetKey();
//	CheckIR();
	if(PrevKey!=KeyTemp)
	{
		KeyLock = 0;
 		ChangeKey = 1;	//change key
//			printf("PrevKey=0x%x,KeyTemp=0x%x,KeyRepeatCnt=%d\r\n",(Word)PrevKey,(Word)KeyTemp,(Word)KeyRepeatCnt);
		if(PrevKey == vkSOURCE && KeyTemp == 0 && KeyRepeatCnt < 10){
			PrevKey = KeyTemp;
			KeyBuffer = vkSOURCE;
			KeyRepeatCnt = 0;
			OsdTimer = FuncBuf[pOSDTIMER] * 100;
			//OsdTimer = 3 * 100;
//			printf("KeyBuffer=%x,KeyRepeatCnt=%d\r\n",(Word)KeyBuffer,(Word)KeyRepeatCnt);
		}
		else if(KeyTemp == vkSOURCE){
			PrevKey = KeyTemp;
			KeyBuffer = 0;
//			printf("vkSOURCE2,KeyRepeatCnt=%d\r\n",(Word)KeyRepeatCnt);
			//OsdTimer = 3 * 100;
		}
		else{
			PrevKey = KeyTemp;
			KeyBuffer = KeyTemp;
			KeyRepeatCnt = 0;
//			if(KeyBuffer ==vkMENU)
			if(OSDZoomFlag)
				OsdTimer = 3 * 100;  // Ch show and Video source..
			else
				OsdTimer = FuncBuf[pOSDTIMER] * 100;

		}
		RepeatTimer = KeyHoldTime;
	}

	else if((IR_Pre_KeyBuffer!= IR_KeyTemp)&&(!bIR_Change)){
 		KeyLock = 0;
		bIR_Change = 1;
		IR_Pre_KeyBuffer = IR_KeyTemp;
		KeyRepeatCnt = 0;
		RepeatTimer = 5;
//		printf("IRK00=%x\r\n",(Word)IR_Pre_KeyBuffer);

	}
	else if((bIR_Change)/*||(bIR_Active)*/){
		KeyBuffer = 0;
//		printf("IRK11=%x\r\n",(Word)IR_Pre_KeyBuffer);
//		printf("rt=%x\r\n",(Word)RepeatTimer);
		if(RepeatTimer==0){
			bIR_Change = 0;
			switch(IR_Pre_KeyBuffer){
				case vIR_POWER:
					if(!KeyLock)
						KeyBuffer = IR_Pre_KeyBuffer;
					RepeatTimer = KeyHoldTime;
					break;
				case vIR_MENU:
				case vIR_SELECT:
				case vIR_MUTE:
				case vIR_UP:
				case vIR_DOWN:
				case vIR_CHSearch:
				case vIR_Analog:
				case vIR_DVI:
				case vIR_SVideo:
				case vIR_Video:
				case vIR_TV:
					if(!KeyLock)
						KeyBuffer = IR_Pre_KeyBuffer;
					RepeatTimer = KeyHoldTime;
					RepeatTimer = 5;
					if(OSDZoomFlag)
						OsdTimer = 3 * 100;  // Ch show and Video source..
					else
						OsdTimer = FuncBuf[pOSDTIMER] * 100;
					break;
				case vIR_1:
				case vIR_2:
				case vIR_3:
				case vIR_4:
				case vIR_5:
				case vIR_6:
				case vIR_7:
				case vIR_8:
				case vIR_9:
				case vIR_0:
				case vIR_10:
				case vIR_11:
				case vIR_12:
					if(!KeyLock)
						KeyBuffer = IR_Pre_KeyBuffer;
					RepeatTimer = KeyHoldTime;
					RepeatTimer = 2;
					if(OSDZoomFlag)
						OsdTimer = 3 * 100;  // Ch show and Video source..
					else
						OsdTimer = FuncBuf[pOSDTIMER] * 100;
					break;
				case vIR_LEFT:
				case vIR_RIGHT:
					if(!KeyLock){
						KeyBuffer = IR_Pre_KeyBuffer;
						KeyRepeatCnt += 1;
					}
					else KeyRepeatCnt = 1;
					if(KeyRepeatCnt<3) RepeatTimer = KeyMenuTime;
					else RepeatTimer = KeyRepeatTime;
					if(OSDZoomFlag)
						OsdTimer = 3 * 100;  // Ch show and Video source..
					else
						OsdTimer = FuncBuf[pOSDTIMER] * 100;
					break;
			}

		}

	}

	else
	{
		KeyBuffer = 0;	//the other key
		if((RepeatTimer == 0))//&& MenuPtr.Menu > 0)
			{
			switch(KeyTemp)
				{
				case vkSOURCE:
					if(KeyRepeatCnt < 10){
						KeyBuffer = KeyTemp;
						RepeatTimer = 30;//KeyMenuTime;
						if(!KeyLock)
							KeyRepeatCnt = 10;
						else
							KeyRepeatCnt += 1;
					}
					OsdTimer = FuncBuf[pOSDTIMER] * 100;
					break;
				//--------------------------- +jwshin 061025	
				case vkLEFT:
				case vkRIGHT:
					if(!KeyLock)
						KeyBuffer = KeyTemp;
					RepeatTimer = KeyRepeatTime;
					OsdTimer = FuncBuf[pOSDTIMER] * 100;
					break;
				//----------------------------	
				case vkMENU:
					if(!KeyLock)
						KeyBuffer = KeyTemp;
					RepeatTimer = KeyMenuTime;
					OsdTimer = FuncBuf[pOSDTIMER] * 100;
					break;
				case vkVADOWN:
				case vkVALUP:
					if(!KeyLock)
						KeyBuffer = KeyTemp;
					RepeatTimer = KeyRepeatTime;
					OsdTimer = FuncBuf[pOSDTIMER] * 100;
					break;
//				case (vkMENU|vkLEFT|vkVALUP):
//					if(!KeyLock)
//						KeyBuffer = KeyTemp;
//					break;
				};
			}
		}
}


void KeyProcess(void)
{
 //	unsigned char caption;
	Byte code MaxItemsTabTV[]={7,4,4,9,5,6,7,MAX_FACT_ITEM}; //Jason Choi	// -jwshin 050729 closed caption menu erase
//	Byte code MaxItemsTabTV[]={7,2,4,9,7,6,7,MAX_FACT_ITEM}; //Jason Choi
	Byte code MaxItemsTab[]=    {7,4,4,9,5,6,7,MAX_FACT_ITEM};	// -jwshin 050729 closed caption menu erase
//	Byte code MaxItemsTab[]=    {7,4,4,9,5,2,7,MAX_FACT_ITEM};	// +jwshin 061030 Only RGB,DVI Version...
//	Byte code MaxItemsTab[]={7,2,4,9,6,6,7,MAX_FACT_ITEM};
	Byte temp;
	ScanKeyPad();
//	printf("KeyBuffer2=0x%x\r\n",(Word)KeyBuffer);
//	if(OsdLock && KeyBuffer != (vkMENU|vkLEFT|vkVALUP)){		// -jwshin 060908
//		KeyBuffer = 0;
//		printf("OsdLock==1 &&KeyBuffer=0x%x\r\n",(Word)KeyBuffer);

//	}
//	if((KeyRepeatCnt == 1) && KeyBuffer == vkSOURCE))
//		KeyBuffer == 0;
//	if(PowerDown && KeyBuffer != 0)	//power down press any key
//		if(KeyBuffer != vkPOWER)
//			WarmUp();
//	printf("KeyBuffer11=0x%x\r\n",(Word)KeyBuffer);

//	printf("VideoMute=%d\r\n",(Word)VideoMute);
	if((VideoMute && FuncBuf[pVIDEOSOURCE]<cSVIDEO) /*|| (FuncBuf[pVIDEOSOURCE]> cDVI&& !VideoOK)*/)
		{
		switch(KeyBuffer)
			{
		//	case vkMENU:
		//	case vkMONSEL:
			case vkLEFT:			// +jwshin 061025
			case vkRIGHT:			// +jwshin 061025
			case vkVALUP:
			case vkVADOWN:
			case vkPOWER:	//burn in
			case vkSOURCE:
			case vIR_POWER:
			case vIR_MENU:
			case vIR_SELECT:
			case vIR_Analog:
			case vIR_DVI:
			case vIR_SVideo:
			case vIR_Video:
			case vIR_TV:
				break;
			default:
				KeyBuffer = 0;
				break;
			};
			
		}
//	printf("KeyBuffer22=0x%x\r\n",(Word)KeyBuffer);

	if(OutOfRange != 0 && KeyBuffer != vkPOWER)  //OutOfRange== 0 mean normal
			if(KeyBuffer != vkSOURCE)  KeyBuffer = 0;

//	printf("KeyBuffer3=0x%x\r\n",(Word)KeyBuffer);
		
	temp = MenuPtr.Page;
	if(MenuPtr.Menu == 2)
		temp = 7;
	
	if(FuncBuf[pVIDEOSOURCE] >cYPbPr) 
	MaxItem = MaxItemsTabTV[temp];
	else
	MaxItem = MaxItemsTab[temp];
	
	if(FuncBuf[pVIDEOSOURCE]==cDVI&& temp == 0)//for DVI MenuPtr.Page = 0
		MaxItem = 3;
	else if(FuncBuf[pVIDEOSOURCE]>=cYPbPr&& temp == 0)//for CAVS and S-Video MenuPtr.Page = 0  +jwshin 061009
		MaxItem = 5;
	if(!DecoderICEn && temp == 5)
		MaxItem = 3;
//		MaxItem = 2;			// +jwshin 061030 
	
	if(MenuPtr.Level == 1)	//for level1 menu
		BackPtr = MenuPtr.Ptr;
	else if(MenuPtr.Level == 2)
		BackPtr = 0;
//	printf("MenuPtr.Menu =0x%x\r\n",(Word)MenuPtr.Menu );

	if(MenuPtr.Menu == 0)
	{
//	printf("KeyBuffer3=0x%x\r\n",(Word)KeyBuffer);
	switch(KeyBuffer)	//open main menu
		{
	//------------------------------------------------ +jwshin 060905		
			case vkMONSEL:
				if(!FactMode){
					if(MonTogg) {
						ShowMonSel();
						Button_En1_InAct();
						Button_En2_Act();
						RDPA_REG = 0xcf;
						MonTogg = 0;
					}
					else {
						ShowMonSel();
						Button_En1_Act();
						Button_En2_InAct();
						RDPA_REG = 0xff;
						MonTogg = 1;
					} 
					KeyLock = 1;
				} 
	//-------------------------------------------------			
				break;
			case vkSOURCE:
				if(!FactMode){
					if(KeyRepeatCnt == 0){
				//		MenuPtr.Menu = 5;
				//		MenuPtr.Page = 5;
				//		MenuPtr.Ptr = FuncBuf[pVIDEOSOURCE];
				//		MenuPtr.Level = 1;
				//		MenuPtr.Op = oUPDATEALL;
						//------------------- +jwshin 060928
						//------------------ DPMS 모드에서 Source를 눌렀을 경우,, Scaler Up 시킨다...
						if(PowerDown == 1) {
							ScalerPowerUp();
						}
						//-------------------
						AUDIO_MUTE();
						
						FuncBuf[pVIDEOSOURCE]++;
						
				//		if(FuncBuf[pVIDEOSOURCE] < cSVIDEO) FuncBuf[pVIDEOSOURCE] = cSVIDEO; // skip DVI
				//		else if(FuncBuf[pVIDEOSOURCE] > cTV) FuncBuf[pVIDEOSOURCE] = cANALOG;
						// -------------- +jwshin 060926
				//		if(FuncBuf[pVIDEOSOURCE] == cDVI) FuncBuf[pVIDEOSOURCE] = cYPbPr;
						if(FuncBuf[pVIDEOSOURCE] > cTV) FuncBuf[pVIDEOSOURCE] = cANALOG;
				//		if(FuncBuf[pVIDEOSOURCE] > cDVI) FuncBuf[pVIDEOSOURCE] = cANALOG;	// +jwshin 061024
						if(FuncBuf[pVIDEOSOURCE] < cSVIDEO) {		// +jwshin 060907
							VideoMute = 1;
							MessageShow = 0;
							PowerTimer = POWER_TIME;
						}
//						printf("F=%d\r\n",FuncBuf[pVIDEOSOURCE]);
						Osd_Off();
						ForceToBack = 0;
						ForceToBackground(0,0,0);
//						Sleep(200);
						// ------------------ Source의 EEprom Writing 위치 변경...+jwshin 060927
						Write24C16(ep_Sync_Source,FuncBuf[pVIDEOSOURCE]); 
						SourceSelect(); 
					//	Write24C16(ep_Sync_Source,FuncBuf[pVIDEOSOURCE]); 
						KeyLock = 1; 
					}
					else if(KeyRepeatCnt == 10){
		/*				MenuPtr.Menu = 4;
						MenuPtr.Level = 0;
						MenuPtr.Op = oUPDATEALL;
						KeyLock = 1;
						OsdTimer = 3 * 100; */
						InitEEPROM();		// +jwshin 060905
					}
				}
				return;
				break;
			case vkMENU:
			case vIR_MENU:
				if(!FactMode){
//	printf("KeyBuffer3=0x%x\r\n",(Word)KeyBuffer);
					MenuPtr.Menu = 1;    // 1
					MenuPtr.Ptr = 0;     // 0
				}
				else{
//	printf("KeyBuffer4=0x%x\r\n",(Word)KeyBuffer);
					MenuPtr.Menu = 2;
					MenuPtr.Ptr = 3;
					FuncBuf[pCOLORTEMP] = 2;
					LoadColor(FuncBuf[pCOLORTEMP]);
					SetContrast();
				}

				MenuPtr.Page = 0;
				MenuPtr.Level = 0;
				MenuPtr.Op = oUPDATEALL;
				KeyLock = 1;
				return;
				break;
			case vkVALUP:
			case vIR_UP:
				if((!FactMode)&&FuncBuf[pVIDEOSOURCE] != cTV){
				/*	MenuPtr.Menu = 3;
					MenuPtr.Page = 0;
					MenuPtr.Ptr = 0;
					MenuPtr.Level = 1;
					MenuPtr.Op = oUPDATEALL;  */
					ShowMuteFuncOnOff();		// +jwshin 061025
					KeyLock = 1;
				}
				else if(FuncBuf[pVIDEOSOURCE] == cTV){
					if((ChSystem==CH_USA)||(ChSystem==CH_JPN))
							ChannelUp();
					else		
							ProgUp();
				}
				return;
				break;
			case vkVADOWN:
			case vIR_DOWN:
				if((!FactMode)&&FuncBuf[pVIDEOSOURCE] != cTV){
			/*		MenuPtr.Menu = 3;
					MenuPtr.Page = 0;
					MenuPtr.Ptr = 1;
					MenuPtr.Level = 1;
					MenuPtr.Op = oUPDATEALL; 
					KeyLock = 1; */
					if(MenuPtr.Menu == 0 && SyncMode != 3 && !FactMode)
						if(FuncBuf[pVIDEOSOURCE] == cANALOG)
						{
							KeyLock = 1;
							ShowMessage(MSG_AUTOTUNE);
							AutoTune();
						}
				}
				else if(FuncBuf[pVIDEOSOURCE] == cTV){
					if((ChSystem==CH_USA)||(ChSystem==CH_JPN))
							ChannelDown();
					else		
							ProgDown();
				}
				return;
				break;
			//-------------------- Left,Right Key 추가... +jwshin 061025
			case vkLEFT:
				MenuPtr.Menu = 6;
				MenuPtr.Page = 1;
				MenuPtr.Ptr = 0;
				MenuPtr.Level = 1;
				MenuPtr.Op = oUPDATEALL;
				return;
				break;
			case vkRIGHT:
				MenuPtr.Menu = 6;
				MenuPtr.Page = 1;
				MenuPtr.Ptr = 0;
				MenuPtr.Level = 1;
				MenuPtr.Op = oUPDATEALL;
				return;
				break;
			//-------------------------	
			case vVOLUME:				// +jwshin 050802
					MenuPtr.Menu = 6;
					MenuPtr.Page = 1;
					MenuPtr.Ptr = 0;
					MenuPtr.Level = 1;
					MenuPtr.Op = oUPDATEALL;
					KeyLock = 1;
//					printf("vVolume Key FuncBuf[pVIDEOSOURCE]=%d\r\n",(Word)FuncBuf[pVIDEOSOURCE]);
//					if(FuncBuf[pVIDEOSOURCE]==5)ScanChannel();
				return;
				break;
		};
	}
	switch(KeyBuffer)
		{
		case vkMENU:
		case vIR_MENU:
			if(MenuPtr.Menu == 2)
			{
				if(MenuPtr.Level == 0)
				{
					MenuPtr.Level= 1;
					MenuPtr.Op = oENTER;
				}
				else if(MenuPtr.Level == 1)
				{
					MenuPtr.Level= 0;
					MenuPtr.Ptr = BackPtr;
					MenuPtr.Op = oENTER;
				}
			}
			else if(MenuPtr.Menu == 5)
			{
				if(MenuPtr.Level == 0)
				{
					MenuPtr.Level= 1;
					MenuPtr.Op = oENTER;
					if(MenuPtr.Page == 5)
						MenuPtr.Ptr = FuncBuf[pVIDEOSOURCE];
				}
				else if(MenuPtr.Level == 1)
				{
					MenuPtr.Ptr++;
					if(MenuPtr.Ptr >= MaxItem)
						MenuPtr.Ptr = 0;
					MenuPtr.Op = oINCFUNC;
				}
			}				
			else if((MenuPtr.Menu > 0)&&(MenuPtr.Menu < 4))
			{
				if(MenuPtr.Level == 0)
				{
					MenuPtr.Level= 1;
					MenuPtr.Op = oENTER;
					if(MenuPtr.Page == 2){
						if((FuncBuf[pVIDEOSOURCE] != cTV)&&(FuncPtr!=pFACTMENU)) //Jason Choi
							MenuPtr.Ptr = FuncBuf[pCOLORTEMP];
						else MenuPtr.Ptr = 0;
					}
					else if(MenuPtr.Page == 3)
						MenuPtr.Ptr = FuncBuf[pLANGUAGE];
					else if(MenuPtr.Page == 5)
						MenuPtr.Ptr = FuncBuf[pVIDEOSOURCE];
					else
						MenuPtr.Ptr = 0;
				}
				else if(MenuPtr.Level == 1)
				{
//					printf("MenuPtr.Level => 1\r\n");
					if(MenuPtr.Menu == 3){
						if(!FactMode){
							if(MenuPtr.Ptr == 0)
								MenuPtr.Ptr = 1;
							else
								MenuPtr.Ptr = 0;
							MenuPtr.Op = oINCFUNC;
						}
					}
					else{
						MenuPtr.Ptr++;
						if(MenuPtr.Page == 4){
							if(!(ResolutionPtr == 4 ||(ResolutionPtr >= 6 && ResolutionPtr < 13)))
								if(MenuPtr.Ptr == 5) MenuPtr.Ptr = 6; // ration control skip
						}
						if(MenuPtr.Ptr >= MaxItem)
							MenuPtr.Ptr = 0;

						if(FuncBuf[pVIDEOSOURCE] == cTV){
							if(MenuPtr.Page == 3){
								MenuPtr.Op = oINCVAL;
//								printf("MenuPtr.Ptr2=%d\r\n",(Word)MenuPtr.Ptr);
							}
							else	{
								MenuPtr.Op = oINCFUNC;
//								printf("MenuPtr.Ptr3=%d\r\n",(Word)MenuPtr.Ptr);
							}
						}
						else{
							if((MenuPtr.Page == 3)||(MenuPtr.Page == 2))
								MenuPtr.Op = oINCVAL;
							else
								MenuPtr.Op = oINCFUNC;
						}
					}
				}
				else if(MenuPtr.Level == 2)
				{
//					printf("MenuPtr.Level => 2\r\n");
					MenuPtr.Ptr++;
					if(MenuPtr.Ptr >= 7)
						MenuPtr.Ptr = 4;
					MenuPtr.Op = oINCFUNC;
//					printf("MenuPtr.Ptr4=%d\r\n",(Word)MenuPtr.Ptr);
				}
			}
			KeyLock = 1;
			break;
		case vkVALUP:
		case vIR_UP:
		
		/*	if(MenuPtr.Menu == 6 && MenuPtr.Page == 1 && MenuPtr.Level == 1) {
				MenuPtr.Op = oINCVAL;
			}  */
			break;
		case vkVADOWN:
		case vIR_DOWN:
			
			if(MenuPtr.Level == 0 || MenuPtr.Menu == 3 || MenuPtr.Menu == 4 || MenuPtr.Menu == 5 || MenuPtr.Menu == 6)	// +jwshin 050802
				Osd_Off();
			else
			{// Jacky 1021
				if(MenuPtr.Level == 2){
					MenuPtr.Level = 1;
					MenuPtr.Ptr = FuncBuf[pCOLORTEMP];
					MenuPtr.Op = oUPDATEALL;
				}
				else{
					MenuPtr.Level = 0;
					MenuPtr.Ptr = BackPtr;
					MenuPtr.Op = oUPDATE;
				}
			}
		/*	if(MenuPtr.Menu == 6 && MenuPtr.Page == 1 && MenuPtr.Level == 1) {
				MenuPtr.Op = oDECVAL;
			} */
			break;	
		case vkLEFT:
			if(((MenuPtr.Menu > 0)&&(MenuPtr.Menu <= 5)) || (MenuPtr.Menu == 6)){
				if(MenuPtr.Level == 0)
				{
					if(MenuPtr.Menu == 2)
					{
						if(MenuPtr.Ptr==0)
							MenuPtr.Ptr = MaxItem;
						MenuPtr.Ptr--;
						MenuPtr.Op = oDECFUNC;
					}
					else
					{
						if(MenuPtr.Page==0)
							MenuPtr.Page = MAX_PAGE;
						MenuPtr.Page--;
						MenuPtr.Op = oDECPAGE;
						KeyLock = 1;
					}
				}
				else{
					if(MenuPtr.Page == 5)
						MenuPtr.Op = oUPDATE;
					else if((MenuPtr.Page == 2)&&(FuncPtr!=pFACTMENU))
					{
						if(FuncBuf[pVIDEOSOURCE] != cTV){
							if((MenuPtr.Level == 1)&&(FuncBuf[pCOLORTEMP] == 3))
							{
								MenuPtr.Level= 2;
								MenuPtr.Op = oUPDATE;
								MenuPtr.Ptr = 4;
							}
							else if(MenuPtr.Level == 2)
								MenuPtr.Op = oDECVAL;
						}
						else{
							if(MenuPtr.Level == 1)
							{
								MenuPtr.Level= 2;
								MenuPtr.Op = oDECVAL;
		//						MenuPtr.Ptr = 4;
							}
							else if(MenuPtr.Level == 2)
								MenuPtr.Op = oDECVAL;
						}
					}
					else if(MenuPtr.Page == 4){
						if((MenuPtr.Level==1)&&(FuncPtr==pCAPTION)) {
							DisplayCaption(0);
						}
						else {
							MenuPtr.Op = oDECVAL;	
						}
					}
					else if(MenuPtr.Page != 3)
						MenuPtr.Op = oDECVAL;
				}


			}
			break;
		case vkRIGHT:
			if(((MenuPtr.Menu > 0)&&(MenuPtr.Menu <= 5)) || (MenuPtr.Menu == 6)){
				if(MenuPtr.Level == 0)
				{
					if(MenuPtr.Menu == 2)
						{
						MenuPtr.Ptr++;
						if(MenuPtr.Ptr >= MaxItem)
							MenuPtr.Ptr = 0;
						MenuPtr.Op = oINCFUNC;
						}
					else
						{
						MenuPtr.Page++;
						if(MenuPtr.Page >= MAX_PAGE)
							MenuPtr.Page = 0;
						MenuPtr.Op = oINCPAGE;
						KeyLock = 1;
						}
				}
				else
				{
					if(MenuPtr.Page == 5)
						MenuPtr.Op = oUPDATE;
					else if((MenuPtr.Page == 2)&&(FuncPtr!=pFACTMENU)) //Jason Choi
					{
//						printf("MenuPtr.Page == 2\r\n");
						if(FuncBuf[pVIDEOSOURCE] != cTV){
							if((MenuPtr.Level == 1)&&(FuncBuf[pCOLORTEMP] == 3))
							{
								MenuPtr.Level= 2;
								MenuPtr.Op = oUPDATE;
								MenuPtr.Ptr = 4;
							}
							else if(MenuPtr.Level == 2)
								MenuPtr.Op = oINCVAL;
						}
						else{
							if(MenuPtr.Level == 1)
							{
								MenuPtr.Level= 2;
								MenuPtr.Op = oINCVAL;
//								printf("MenuPtr.Op = oUPDATE\r\n");
							//	MenuPtr.Ptr = 4;
							}
							else if(MenuPtr.Level == 2){
								MenuPtr.Op = oINCVAL;
//								printf("MenuPtr.Op = oINCVAL\r\n");
							}
						}
					}	
					else if(MenuPtr.Page == 4){
						if((MenuPtr.Level==1)&&(FuncPtr==pCAPTION)) {
							DisplayCaption(1);
						}
						else {
							MenuPtr.Op = oINCVAL;		
						}		
					}
					else if(MenuPtr.Page != 3)
						MenuPtr.Op = oINCVAL;
				}

			}
			break;
		case vkAUTO:
			if(MenuPtr.Menu == 0 && SyncMode != 3 && !FactMode)
				if(FuncBuf[pVIDEOSOURCE] == cANALOG)
					{
					KeyLock = 1;
					ShowMessage(MSG_AUTOTUNE);
					AutoTune();
					}
			if(MenuPtr.Level == 0 || MenuPtr.Menu == 3 || MenuPtr.Menu == 4 || MenuPtr.Menu == 5 || MenuPtr.Menu == 6)	// +jwshin 050802
				Osd_Off();
			else
				{// Jacky 1021
				if(MenuPtr.Level == 2){
					MenuPtr.Level = 1;
					MenuPtr.Ptr = FuncBuf[pCOLORTEMP];
					MenuPtr.Op = oUPDATEALL;
				}
				else{
					MenuPtr.Level = 0;
					MenuPtr.Ptr = BackPtr;
					MenuPtr.Op = oUPDATE;
				}
				}
			break;
		case vkSOURCE:
		case vIR_SELECT:
			if(MenuPtr.Menu == 4)
			{
//				if(MenuPtr.Level == 0){
					MenuPtr.Level = 1;
//					MenuPtr.Op = oINCVAL;
//				}
//				else
					MenuPtr.Op = oINCVAL;
				OsdTimer = 3 * 100;
			}
			KeyLock = 1;
//			if(MenuPtr.Menu != 4){
//					ChannelMask(ChAdd_Del);	//test
//					CheckChMask();
//					LoadChLimit();
//					ScanChannel();
//			}
			break;
		case vkPOWER:
		case vIR_POWER:
			KeyLock = 1;
			PowerOffProcess();
			break;

		case (vkVALUP|vkVADOWN):	//fact mode and clear
			if(FactMode && (MenuPtr.Menu == 2))
			{
				BackLightTimerEn = 0;
				BackLightTimer = 0;
				SaveBackLightTime();
				ShowBackLightTime();
				BackLightTimerEn = 1;
			}
			break;
		case (vkMENU|vkPOWER):
			if(NoSyncFlag && !BurnInMode && !PowerDown)
				{
				BurnInMode = 1;
				Write24C16(ep_Status,StatusFlag);
				ShowBurnInPattern(1);
				KeyLock = 1;
				} 
			break;
		case vIR_MUTE:
				AUDIO_MUTE();
			break;

		case vIR_1:
		case vIR_2:
		case vIR_3:
		case vIR_4:
		case vIR_5:
		case vIR_6:
		case vIR_7:
		case vIR_8:
		case vIR_9:
		case vIR_0:
			if((MenuPtr.Menu == 0) ||(MenuPtr.Menu  == 6)){
				Osd_Off();
				ClearOSD();
				MenuPtr.Menu = 5;
				IR_Number_cnt = 1;
				IR_WaitTimer = 500;
			}
			else if(MenuPtr.Menu  == 5){
				IR_Number_cnt ++;
				IR_WaitTimer = 500;
			}
//			printf("IR_Number_cnt=%x\n",(Word)IR_Number_cnt);
			if(((Read24C16(ep_Input_CH_Sys) & 0x80)!= 0)&&(IR_Number_cnt<4)){
														ChannelMove(KeyBuffer & 0x7F);
														/*printf("ChannelMove1\r\n");*/
			}
			else if(((Read24C16(ep_Input_CH_Sys) & 0x80) == 0)&&(IR_Number_cnt<3)){
														ChannelMove(KeyBuffer & 0x7F);
														/*printf("ChannelMove2\r\n");*/
			}
			else {
				IR_Number_cnt = 0;
				Osd_Off();
			}
			KeyLock = 1;
			Sleep(50);
			break;

			
//		case (vkMENU|vkLEFT|vkVALUP):
//			if(OsdTimer < ((FuncBuf[pOSDTIMER] * 100) - 500))
//				{
//				KeyLock = 1;
//				OsdLock = ~OsdLock;
//				Write24C16(ep_Status,StatusFlag);
//				}
//			break;
 		};
}

//--------------------- +jwshin 061030    Port Reverse
void LED_GrnOff(void)
{
unsigned char port;
	port = PTE_REG;
	port |= RDPE_REG;
	port |= PE1;
	PTE_REG = port;
}

void LED_GrnOn(void)
{
unsigned char port;
	port = PTE_REG;
	port |= RDPE_REG;
	port &= ~PE1;
	PTE_REG = port;
}
//---------------------------------
				// -jwshin 051101
void LED_RedOn(void)
{
unsigned char port;
	port = PTE_REG;
	port |= RDPE_REG;
	port |= PE0;
	PTE_REG = port;
}

void LED_RedOff(void)
{
unsigned char port;
	port = PTE_REG;
	port |= RDPE_REG;
	port &= ~PE0;
	PTE_REG = port;
}

void FLED_GrnOn(void)
{
unsigned char port;
	port = PTD_REG;
	port |= RDPD_REG;
	port |= PD4;
	PTD_REG = port;
}

void FLED_GrnOff(void)
{
unsigned char port;
	port = PTD_REG;
	port |= RDPD_REG;
	port &= ~PD4;
	PTD_REG = port;
}



//---------------------------Dual 에서 Port 제어를 위한 Routine... +jwshin 060904
void RGB_SW1_RGB1(void)
{
unsigned char port;
	port = PTD_REG;
	port |= RDPD_REG;
	port &= ~PD5;
	PTD_REG = port;
}

void RGB_SW1_RGB2(void)
{
unsigned char port;
	port = PTD_REG;
	port |= RDPD_REG;
	port |= PD5;
	PTD_REG = port;
}

void Button_En1_Act(void)
{
	unsigned char port;
	port = PTC_REG;
	port |= RDPC_REG;
	port &= ~PC7;
	PTC_REG = port;
}

void Button_En1_InAct(void)
{
	unsigned char port;
	port = PTC_REG;
	port |= RDPC_REG;
	port |= PC7;
	PTC_REG = port;
}

void Button_En2_Act(void)
{
	unsigned char port;
	port = PTD_REG;
	port |= RDPD_REG;
	port &= ~PD3;
	PTD_REG = port;
}

void Button_En2_InAct(void)
{
	unsigned char port;
	port = PTD_REG;
	port |= RDPD_REG;
	port |= PD3;
	PTD_REG = port;
}

//------------------------------------------------------------

void BackLightOn(void)
{
unsigned char port,temp;
	if(FuncBuf[pVIDEOSOURCE] < cSVIDEO){
		temp = ReadIIC563(0x020);
		WriteIIC563(0x020,temp & (~BIT_0));
		}
	else{
		temp = ReadIIC563(0x040);
		WriteIIC563(0x040,temp & (~BIT_0));
	}
	//PanelPowerOn();//lo_cs
	//DC2DCPowerOn();
	//XAO_Off();//lo_cs
	//XAO_On();//lo_cs
	WaitSetup(5);
	port = PTC_REG;
	port |= RDPC_REG;
	port |= PC0;
	PTC_REG = port;
	BackLightTimerEn = 1;
	WaitSetup(5);
	if(FuncBuf[pVIDEOSOURCE] < cSVIDEO){
		temp = ReadIIC563(0x020);
		WriteIIC563(0x020,temp|BIT_0);
		}
	else{
		temp = ReadIIC563(0x040);
		WriteIIC563(0x040,temp|BIT_0);
	}
//	printf("BackLightOn\r\n");
}

void BackLightOff(void)
{
	unsigned char port,temp;
	
	temp = ReadIIC563(0x16e);
	WriteIIC563(0x16e,temp&(~BIT_0));	//lo_cs
	port = PTC_REG;
	port |= RDPC_REG;
	port &= ~PC0;
	PTC_REG = port;

	BackLightTimerEn = 0;

//	printf("BackLightOff\r\n");
}

bit DetectBacklight()
{
	if(PTC_REG & PC0)
		return 1;
	else
		return 0;
}

#if PanelPowerActive == High
void PanelPowerOn(void)
{
unsigned char port;
	port = PTC_REG;
	port |= RDPC_REG;
	port |= PC2;
	PTC_REG = port;
	if(PanelInterface == TCON_TO_RSDS || PanelInterface == TCON_TO_TTL)
	{
		port = PTC_REG; 	
		port |= RDPC_REG;
		port |= PC4;
		PTC_REG = port;
	}
}

void PanelPowerOff(void)
{
unsigned char port;
	port = PTC_REG;
	port |= RDPC_REG;
	port &= ~PC2;
	PTC_REG = port;
	if(PanelInterface == TCON_TO_RSDS || PanelInterface == TCON_TO_TTL)
	{
		port = PTC_REG;
		port |= RDPC_REG;
		port &= ~PC4;
		PTC_REG = port;
	}
}
#else
void PanelPowerOff(void)
{
unsigned char port;
	port = PTC_REG;
	port |= RDPC_REG;
	port |= PC2;
	PTC_REG = port;
	if(PanelInterface == TCON_TO_RSDS || PanelInterface == TCON_TO_TTL)
	{
		port = PTC_REG; 	
		port |= RDPC_REG;
		port |= PC4;
		PTC_REG = port;
	}
}

void PanelPowerOn(void)
{
unsigned char port;
	port = PTC_REG;
	port |= RDPC_REG;
	port &= ~PC2;
	PTC_REG = port;
	if(PanelInterface == TCON_TO_RSDS || PanelInterface == TCON_TO_TTL)
	{
		port = PTC_REG;
		port |= RDPC_REG;
		port &= ~PC4;
		PTC_REG = port;
	}
}
#endif
#if PANEL == CMO_M170ES05
void DC2DCPowerOn(void)
{
	unsigned char port;
	
	port = PTE_REG;
	port |= RDPE_REG;
	port &= ~PE0;
	PTE_REG = port;
}

void DC2DCPowerOff(void)
{
	unsigned char port;
	
	port = PTE_REG;
	port |= RDPE_REG;
	port |= PE0;
	PTE_REG = port;
}

void XAO_On(void)
{
	Byte Port;
	Port = PTC_REG;		
	Port |= RDPC_REG;
	Port |= PC3;
	PTC_REG = Port;
}

void XAO_Off(void)
{
	Byte Port;
	Port = PTC_REG;		
	Port |= RDPC_REG;
	Port &= ~PC3;
	PTC_REG = Port;
}
#endif
void ResetOff(void)
{
unsigned char port;
	port = PTC_REG;
	port |= RDPC_REG;
	port |= PC3;
	PTC_REG = port;
}

void ResetOn(void)
{
unsigned char port;
	port = PTC_REG;
	port |= RDPC_REG;
	port &= ~PC3;
	PTC_REG = port;
}
/*
void FastMuteOn()
{
	Byte Port;
	WaitVblank();
	Port = PTD_REG;		
	Port |= RDPD_REG;
	Port |= PD4;
	PTD_REG = Port;
}

void FastMuteOff()
{
	Byte Port;
	WaitVblank();
	Port = PTD_REG;		
	Port |= RDPD_REG;
	Port &= ~PD4;
	PTD_REG = Port;
}
*/
/*
void SAA7114Off()
{
	Byte Port;
	Port = PTD_REG;		
	Port |= RDPD_REG;
	Port &= ~PD1;
	PTD_REG = Port;
}

void SAA7114On()
{
	Byte Port;
	Port = PTD_REG;		
	Port |= RDPD_REG;
	Port |= PD1;
	PTD_REG = Port;
}
*/

//**********************************
// Sound Select				// +jwshin 050802
//**********************************
void SoundRGB(void)			
{					
	Byte Port1;
	Port1 = PTD_REG;
	Port1 |= RDPD_REG;
	Port1 &= ~PD1;
	Port1 &= ~PD2;
	PTD_REG = Port1;
}	

void SoundTV(void)
{					
	Byte Port1;			
	Port1 = PTD_REG;
	Port1 |= RDPD_REG;
	Port1 &= ~PD1;
	Port1 |= PD2;
	PTD_REG = Port1;
}

void SoundComp(void)
{					
	Byte Port1;			
	Port1 = PTD_REG;
	Port1 |= RDPD_REG;
	Port1 |=  PD1;
	Port1 &= ~PD2;
	PTD_REG = Port1;
}

void SoundVideo(void)
{
	Byte Port1;			
					
	Port1 = PTD_REG;
	Port1 |= RDPD_REG;
	Port1 |= PD1;
	Port1 |= PD2;
	PTD_REG = Port1;
}

void AUDIO_MUTE(void)
{

	Byte Port;
	Port = PTC_REG;		
	Port |= RDPC_REG;
	Port |= PC1;

	PTC_REG = Port;
//	printf("Audio_Mute\r\n");

}

void AUDIO_On(void)
{

	Byte Port;
	Port = PTC_REG;		
	Port |= RDPC_REG;
	Port &= ~PC1;
	PTC_REG = Port;
//	printf("Audio_On\r\n");

}

//bit Saa7114Status()
//{
//
//	if(PTD_REG & PD1)
//		return 1;
//	else
//		return 0;

//	return 0;
//}

bit DetectDVI()
{

	if(PTD_REG & PD3)
		return 0;
	else
		return 1;

//		return 1;
}

/*
bit DetectDsub()
{
	if(PTD_REG & PD5)
		return 0;
	else
		return 1;
}
*/

bit DetectIRQ()
{
	if(PTB_REG & PB2)
		return 0;
	else
		return 1;
}
/*
bit DetectPower()
{
	if(PTB_REG & PB3)
		return 1;
	else
		return 0;
}
*/

bit VsyncValide()
{
	Word VsyncWidth;
	LocalTimer = 2;	//20ms
	while(!(PTC_REG & BIT_6))	//Vsync Lo
		{
		if(LocalTimer == 0)
			return 0;
		}
	LocalTimer = 10;	//100ms
	while(PTC_REG & BIT_6)	//Vsync Hi
		{
		if(LocalTimer == 0)
			return 0;
		}
	VsyncWidth = 0;
	while(!(PTC_REG & BIT_6))	//Vsync Hi 1:7us
		{
		VsyncWidth ++;
		if(VsyncWidth > 50)		//over 350us
			return 0;
		}
	VsyncWidth = 0;
	while(PTC_REG & BIT_6)		//Vsync Hi 1:7us
		{
		VsyncWidth ++;
		if(VsyncWidth > 714)	//over 5ms
			return 1;
		}
	return 0;
}

void WaitVblank()
{
	LocalTimer = 3;	//30ms
	while(!(PTC_REG & BIT_6))	//Vsync Lo
		{
		if(LocalTimer == 0)
			return;
		}
	LocalTimer = 5;	//50ms
	while(PTC_REG & BIT_6)	//Vsync Hi
		{
		if(LocalTimer == 0)
			return;
		}
}
void IntGroup1(void) interrupt 2 using 1
{
	Byte i;
	if(INT_SRC & INT_EXT)
		if(INTEXT_FLG & INTE0)	{
			if(FastMuteEnable){
				i = PTC_REG;		//backlight off
				i |= RDPC_REG;
				i &= ~PC0;
				PTC_REG = i;
				//Port = PTD_REG;		//fastmute on
				//Port |= RDPD_REG;
				//Port &= ~PD4;
				//PTD_REG = Port;
			}
			Abort = 1;	//abort autotune
			if(ChangeMode<10)
				ChangeMode++;
			INTEXT_FLG = INTE0;
		}
		else if(INTEXT_FLG & INTE1){
			INTEXT_FLG |= CLR_INTE1;
			if(IR_Status == cIR_Dummy){
					IR_Timer = 0;
					IR_Status = cIR_START;
					IR_Data = 0;
					cntIR_Data = 0;
//					i = INTEXT_EN;
//					i |=INTE1_EDG; // make rising edge interupt....
					INTEXT_EN |= (INTE1_EDG|BIT_1);
			}
			else if(IR_Status == cIR_START){
					if(IR_Timer >60) {
							IR_Status = cIR_Dummy;
							i = INTEXT_EN;
							i &=(~INTE1_EDG); // make falling edge interupt....
							INTEXT_EN = i |BIT_1;
							return;
					}
					IR_Status = cIR_COMMAND;
					i = INTEXT_EN;
					i &=(~INTE1_EDG); // make falling edge interupt....
					INTEXT_EN = i |BIT_1;
					IR_Timer = 0;
			}
			else if(IR_Status == cIR_COMMAND){
					if(IR_Timer >40) {
							IR_Status = cIR_Dummy;
							i = INTEXT_EN;
							i &=(~INTE1_EDG); // make falling edge interupt....
							INTEXT_EN = i |BIT_1;
							return;
					}
					IR_Status = cIR_DATA;
					IR_Timer = 0;
			}
			else if(IR_Status == cIR_DATA){
					if(IR_Timer >30) {
							IR_Status = cIR_Dummy;
							i = INTEXT_EN;
							i &=(~INTE1_EDG); // make falling edge interupt....
							INTEXT_EN = i |BIT_1;
							return;
					}
					IR_Data = IR_Data << 1;
					if(IR_Timer >20) IR_Data |= 1;
					cntIR_Data++;
					IR_Timer = 0;
					if(cntIR_Data == 31){
						bIR_flag = 1;
						IR_Data_buffer = IR_Data;
						IR_RepeatTimer = 45;		// +jwshin 051028 repeat timer value 수정.
//						IR_RepeatTimer = 10;
					}
					if(cntIR_Data > 30) IR_Status = cIR_Dummy;
					
			}
		}

}

void SetInverter(void)
{
	Byte value;
//	if(FuncBuf[pCOLORTEMP] < 4)
#if PANEL == Samsung_LTM170E4_L01 || LP_LM170E01
		value = 0x7f - FuncBuf[pBACKLIGHT];
#else
		value = FuncBuf[pBACKLIGHT];
#endif
//	else
//		value = FuncMax - FuncBuf[pBACKLIGHT2];
	PWM8_REG = value * 2;
	#if PRINT_MESSAGE
		printf("FuncBuf[pBACKLIGHT] = %x\r\n",(unsigned short)value);
	#endif
}

#define AUDIO_PWM_MAX 205
void SetAudioVolume(void)
{
unsigned char value;
	value = (((FuncBuf[pVOLUME] * AUDIO_PWM_MAX) ) / 100+ 1);
	//value = FuncBuf[pVOLUME];
	PWM9_REG = value;
//	#if PRINT_MESSAGE
//		printf("FuncBuf[pVOLUME] = %x\r\n",(unsigned short)value);
//	#endif
}

void SetVCM_Vol(void)
{
unsigned char value;
	value = FuncBuf[pVCMVOL];
	WriteIIC(TDA7440D_Addr,A_Volume,value);//0dB 0dB ~ -40dB
//	PWM9_REG = value;
//	#if PRINT_MESSAGE
//		printf("FuncBuf[pVCMVOL] = %x\r\n",(unsigned short)value);
//	#endif
}

void SetAudioMute(void)
{
	if(AudioMute)
		AUDIO_MUTE();
	else
		AUDIO_On();
	#if PRINT_MESSAGE
		printf("AudioMute = %x\r\n",(unsigned short)AudioMute);
	#endif
}

void PowerOffProcess()
{
	AUDIO_MUTE();
	Osd_Off();
	PowerStatus = 0;	//power off
	Write24C16(ep_Status,StatusFlag);
//	printf("PowerOffProcess\r\n");
	PowerSaving();
//	LED_RedOff();		// -jwshin 051101
	LED_GrnOff();
	if((FactMode)&&(!BurnInMode))//jacky0316 Item41 BurnInMode
	{
		FactMode = 0;
		FuncBuf[pCOLORTEMP] = 3;	//Colortemp user
		Write24C16(ep_Status,StatusFlag);
		Write24C16(ep_Color_Ptr,2);
		Write24C16(ep_Color4_R,Read24C16(ep_Color6_R));	//R Gain
		Write24C16(ep_Color4_G,Read24C16(ep_Color6_G));	//G Gain
		Write24C16(ep_Color4_B,Read24C16(ep_Color6_B));	//B Gain
		//Write24C16(ep_Color5_R,Read24C16(ep_Color1_R));	//R Gain
		//Write24C16(ep_Color5_G,Read24C16(ep_Color1_G));	//G Gain
		//Write24C16(ep_Color5_B,Read24C16(ep_Color1_B));	//B Gain
		#if PRINT_MESSAGE
			printf("Release Factory mode\r\n");
		#endif
		while(GetKey() == 0);
			Osd_Off();
	}
	while(1)
		{
		ScanKeyPad();
		//KeyScan();
		//KeyBuffer &= 0x7F;
		if((KeyBuffer&vkPOWER) && !KeyLock)
			{
				PowerStatus = 1;	//power on
				BurnInMode = 0;
				KeyLock = 0;		// +jwshin 050812
				Write24C16(ep_Status,StatusFlag);
				WarmUp();
		/*		if(MonTogg == 1) {
					RDPA_REG = 0xff;
				}
				else {
					RDPA_REG = 0xcf;
				} */
			}
		}
}

void CheckAnyKey()
{
	if(Abort)
		return;
	if(GetKey() == vkPOWER)
		Abort = 1;
}

void CheckIR(void)
{
	unsigned short i,value;
	unsigned char k;
		if(IR_Timer > 500) IR_Status = cIR_Dummy;

		if(bIR_flag) {
			bIR_flag = 0;
//			if(cntIR_Data>30) printf("IR_data3=0x%x,%x \r\n",IR_Data,(IR_Data>>16));
			value = IR_Data_buffer;
			i = IR_Data_buffer >>16;
//			printf("i=%x\r\n",i);
//			printf("value=%x\r\n",value);
			
			
//			if(i == 0x20df){  // LG
			if(i == 0x40ff){
				for(k=0; k<19; k++){
//					printf("LG\r\n");
					if(LG_IR_Tab[k] == (unsigned short)value){	// +jwshin Platys Remocon Code 적용 051028
						IR_KeyTemp= IR_CodeTab[k];
						bIR_Active = 1;
//						RepeatTimer = KeyHoldTime;
					}
				}
//				printf("KeyBuffer LG=%x\r\n",(unsigned short)IR_KeyTemp);

			}

		}
		else if((IR_Status == cIR_Dummy)&&(IR_RepeatTimer == 0)){
						IR_KeyTemp = 0xfb;
						bIR_Active = 0;
		}
}


/*
void CheckDDC2Bi(void)
{
unsigned char cmd;
//	if((flag3 & BIT_7) != 0){
//Wait stop
				//	printf("CmdRxPtr1=%d\n",CmdRxPtr1);
				//	printf("CmdRxPtr2=%d\n",CmdRxPtr2);

		Timer1=200;
//		Timer3 = 200;
		while(Timer3 != 0){
			if((IIC1_STATUS & BUS_STOP) != 0){
				break;
			}
		}
		if(Timer1 != 0){
		//if(Timer3 != 0){
			CmdTxBuffer[0] = 0;
			while(CmdRxPtr1 != CmdRxPtr2){
				cmd = CmdRxBuffer[CmdRxPtr2++];
				if(CmdRxPtr2 > 127)
					CmdRxPtr2 = 0;
				CheckCmd(cmd);
			}
		}
	//	flag3 &= ~BIT_7;
//	}
}
*/
