#include "8051.H"
#include "stdio.h"
#include "MyDef.H"
#include "F63XREG.H"
#include "F63XDEF.H"
#include "MCU.H"
#include "RAM.H"
#include "IIC.H"
#include "UserAdj.H"
#include "ModeHandle.H"
#include "Scaler.H"
#include "OSD.H"
#include "sRGB.H"
#include "ROM_MAP.H"
#include "TW990x.H"
#include "Z86229.h"
#include "AutoAdj.H"
//#include "dvKeypad.h"

extern WarmUp();

void main(void) using 0
{
//   Byte value;
	EA = 0;
	InitMCU();
	BackLightTimerEn = 0;
//	#if PRINT_MESSAGE
//		printf("Start Program\n");
//	#endif
	AUDIO_MUTE();
	CheckIIC();
//	DDC2();		// -jwshin 050729
	CLRWDT = 0x55;
	flag1 = 0;
	flag2 = 0;
	KeyBuffer = 0 ;
	ChangeMode = 1;
	VideoMute = 1;
	H_SYNC = 0x5555;
	V_SYNC = 0x5555;
	SavePointer = 0xff;
	RegPage = 0x55;
	TvMode = 0;
	FastMuteEnable = 0;
	BypassSOG = 0;
	BurnInPattern = 0;
	LoadDDCData();
 	LocalTimer = 10;
	VPXinit = 0;
	OSDZoomFlag = 0;

/*
	while(LocalTimer != 0)
		{
		MiscProcess(0);
		ADC_CON = (STRT_ADC | EN_ADC0);		//Channel;  // Start AD Convert
		while(!(ADC3_REG & CMP_ADC));
		if((ADC0_REG & 0x7f) < 0x40)
 		 	LocalTimer = 25;
		}
*/
	#if PRINT_MESSAGE
		printf("Main power OK.\n");
	#endif
	ResetOn();	//reset scaler
//	Sleep(50);	// -jwshin 050729
	ResetOff();
//	Sleep(50);	// -jwshin 050729
//------------------------------ +jwshin 060905
	MonTogg = 1;
	RGB_SW1_RGB1();
	Button_En1_Act();
	Button_En2_InAct();
//------------------------------
	
	CheckDevice();
	FuncBuf[pBass]= Read24C16(ep_Bass);			//0xe4= Bass
	FuncBuf[pTreble] = Read24C16(ep_Treble);		//0xe5 = Treble
	FuncBuf[pVCMVOL] = Read24C16(ep_VCMVol);	// Volume

//	printf("pTreble=%d\r\n",(unsigned short)FuncBuf[pTreble]);
//	printf("pBass=%d\r\n",(unsigned short)FuncBuf[pBass]);

//	Bass = Read24C16(ep_Bass);			//0xe4= Bass
//	Treble = Read24C16(ep_Treble);		//0xe5 = Treble
//	if((FuncBuf[pBass] !=0)||(FuncBuf[pTreble]  !=0)){
//	Write24C16(ep_Treble,0);// 0x247....Treble
//	Write24C16(ep_Bass,0);// bass
//		}
// inital TDA7440
	WriteIIC(TDA7440D_Addr,A_InputGain,0x00);//0dB 0dB ~ +30dB
	WriteIIC(TDA7440D_Addr,A_Volume,FuncBuf[pVCMVOL]);//0dB 0dB ~ -40dB
	WriteIIC(TDA7440D_Addr,A_Bass,TDA7440D_Tab[FuncBuf[pBass]]);//0dB -14dB~+14dB
	WriteIIC(TDA7440D_Addr,A_Treble,TDA7440D_Tab[FuncBuf[pTreble]]);//0dB -14dB~+14dB
	WriteIIC(TDA7440D_Addr,A_AttR,0x00);//0dB  0dB~ -72dB
	WriteIIC(TDA7440D_Addr,A_AttL,0x00);//0dB  0dB~ -72dB

//	WriteIIC563(0x101, 0x20);
//	Sleep(12);
//	WriteIIC563(0x101, 0x0f);
	ScanKeyPad();
//			printf("ScanKeyPad\r\n");
//KeyScan();
//	if(KeyBuffer == (vkMENU|vkVADOWN|vkPOWER))
//	if(KeyBuffer == (vkAUTO|vkVALUP))
//		InitEEPROM();
	//		printf("InitEEPROM\r\n");
	CheckVersion();
	//Read the scaler version

//	Write24C16(ep_Sync_Source,0);

	SCRev = (ReadIIC563(0x100) >> 4);
//printf("SCRev\r\n");
	UserModePtr = Read24C16(ep_User_Ptr);
//printf("UserModePtr\r\n");
	StatusFlag = Read24C16(ep_Status);
	BurnInMode = 0;				// +jwshin 050805
	FuncBuf[pVIDEOSOURCE] = Read24C16(ep_Sync_Source);   
//	FuncBuf[pVIDEOSOURCE] = cSVIDEO;		// +jwshin 강제 DVI 진입...
//	PowerStatus = 1;	
	if(!PowerStatus){				
//			printf("PowerOffProcess\r\n");
		PowerOffProcess();

	}
	if(FuncBuf[pVIDEOSOURCE] == cDVI)	//DVI
		SyncMode = 3;
	else if(FuncBuf[pVIDEOSOURCE] == cYPbPr)	//YPbPr
		SyncMode = 4;			// +jwshin 060926
	else
		SyncMode = 0;
	if(KeyBuffer == vkMENU)		// +jwshin 061009
		{
		FactMode = 1;
		Write24C16(ep_Status,StatusFlag);
		}
	if(FactMode)
		{	//factory mode befor power off
		FuncBuf[pCOLORTEMP] = 2;	
		FuncBuf[pLANGUAGE] = 0;
		Write24C16(ep_Color_Ptr,2);
		#if PRINT_MESSAGE
			printf("Factory mode\n");
		#endif
		}
	LED_GrnOn();	// +jwshin 060908
//			printf("LED_GrnOn\r\n");
	LoadModeIndependentSettings();
	PanelPowerOn();
	//XAO_On();
	InitScaler();
//			printf("InitScaler\r\n");
	OsdInit();
//			printf("OsdInit\r\n");
#if PRINT_MESSAGE
		printf("Test for debug.\n");
#endif
	SetInverter();
	LoadADC_Gain();
//	Z86229_Init();	// test		// -jwshin 050729
	PowerTimer = POWER_TIME-100;	//search sync start
//	CheckSaa7114();
				// ---- -jwshin 060929
	if(BurnInMode)
		FuncBuf[pVIDEOSOURCE] = cANALOG;
	if(DecoderICEn && FuncBuf[pVIDEOSOURCE] >= cYPbPr)	// +jwshin 060929
		SourceSelect();
	else
		{
		if(!DecoderICEn && FuncBuf[pVIDEOSOURCE] > cYPbPr)
			{
			FuncBuf[pVIDEOSOURCE] = cANALOG;
			Write24C16(ep_Sync_Source,0);
			}
		SetBrightness();
		SetContrast();
		}

//	FuncBuf[pVOLUME] = 100;
//	SetAudioVolume();
	//SetAudioMute();
	SetVCM_Vol();
	FuncBuf[pVOLUME] = Read24C16(ep_Volume);//Jason Choi
//	printf("FuncBuf[pVolume]=%x\n",FuncBuf[pVOLUME]);
		AudioMute=0; //Jason Choi 다시켤 檍ㅉ때 mute풀림 
	SetAudioVolume();
//	AUDIO_On();
	SetLightBrightness();
	SetLightContrast();
	SetLightHS();
	SetLightHW();
	SetLightVS();
	SetLightVH();

	CaptionFlag= Read24C16(0x7f0);
	GetRating(); //Get Raing from V-chip

//	WriteIIC563(0x001,0x45);
//	value = ReadIIC563(0x001);
//	printf("value=%x\r\n",(unsigned short)value);
#if ContrastBlock == BackEndGain
	sRGB(50,128,128,128);
#endif
	if(BurnInMode)
		ShowBurnInPattern(1);
		
		
	while(1)
	{

		if(DecoderICEn &&( FuncBuf[pVIDEOSOURCE] > cYPbPr)){
			if(VideoTest == 1){
				CheckVideoSignal();
				VideoCheck = 0;
				if(VideoCheck){
//					if(Read24C16(0x7F3) == 1){
						if(VideoMute == 0){
							if(VChip_Timer>20){
								if(VideoCheck == 1)Check_VChip();
								VChip_Timer=0;
							}
						}
//					}
				}
			}
		}
		else{
				if(NoSyncFlag==0) {		// +jwshin 060908
					LED_GrnOn();
				}
				CheckFreq();
				//if(!FactMode)
					PowerSaveingProcess();
				SyncSource(0);
		}
		//KeyScan();
		//if(KeyBuffer & 0x80){
		//KeyBuffer &= 0x7F;
		KeyProcess();
		AdjustProcess();
		OsdProcess();
		//	}
		MiscProcess(1);
		LocalTimer = 10;
//		printf("MiscProcess\n");
//		while(LocalTimer != 0)
//		{
//			ADC_CON = (STRT_ADC | EN_ADC3);		//Channel;  // Start AD Convert
//			while(!(ADC3_REG & CMP_ADC));
//			if((ADC3_REG & 0x7f) < 0x40){
//	  		 	LocalTimer = 25;
//				WarmUp();
//			}
//		}


		//if(FactMode && (MenuPtr.Menu == 2))
		//{
		//	ShowBackLightTime();
		//}
		CheckRCV(); //Jason Choi		// -jwshin 050722
	//	CheckDDC2Bi();
	
	} 
	
		
		
}

