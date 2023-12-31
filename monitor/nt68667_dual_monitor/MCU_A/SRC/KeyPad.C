#include "RAM.H"
#include "sRGB.H"
#include "NT686xx_MCU_REG.H"
#include "NVRAM.H"
#include "Scaler.H"
#include "AutoAdj.H"
#include "OSD.H"
#include "UserAdj.H"
#include "Board.H"
//#include "stdio.H"
#include "mis.H"
#include "ddc_ci.H"
#include "8051.H"	// EA
#include "ROM_Map.H"
#include "factory.H"
#include "modehandle.H"
#include "SmartBright.H"
#include "NT686xx_SC_REG.H"
#include "BFControl.H"
#include "OSD_LF.H"
#include "MCU.H"
//#define KeyPadDebug

#ifdef KeyPadDebug
	#define NVTprint(s,a1) printf(s,a1)
#else
	#define NVTprint(s,a1)
#endif


void ScanKeyPad(void)
{

#define KeyTypLevel0 0x02//0x0b//0x02//0x13
#define KeyTypLevel1 0x16//0x1e//0x2c
#define KeyTypLevel2 0x34//0x2c//0x5b
#define KeyTypLevel3 0x5f
#define KeyTypLevel4 0x6f
#define KeyTypLevel5 0x7f

#define KeyMinLevel0 ((KeyTypLevel0+KeyTypLevel1)/2)				//0x0c
#define KeyMinLevel1 ((KeyTypLevel1+KeyTypLevel2)/2)				//0x25			
#define KeyMinLevel2 ((KeyTypLevel2+KeyTypLevel3)/2)				//0x49
#define KeyMinLevel3 ((KeyTypLevel3+KeyTypLevel4)/2)				//0x67
#define KeyMinLevel4 ((KeyTypLevel4+KeyTypLevel5)/2)				//0x77

unsigned char KeyPad1,KeyPad2;

	Set_usTimer1_1ms(0);
	do{	
		WaitADConversion();

		KeyPad1 = Key1_Input();
		KeyPad2 = Key2_Input();

		//------------- Power Button Check  +jwshin 120223
		if(!(PortC & BIT_2))
		{
			KeyPad2 = 0x02;			
			//----------- +jwshin PortC의 Bit2를 검지해서, 강제로 A/D Value를 입력함.							
		}
		
		//------------------------ +jwshin 120223
		if((Button_Select_A() == LOW))
		{	
			KeyPad1 = 0x35;
		}
		else if((Button_Select_B() == LOW))
		{
			KeyPad1 = 0x4c;
		}
		else
		{}
		//-----------------------------------------



		//--------- A/D Value를 읽기위해, Routine Call..~!!!
//		ShowOSD_Debug(KeyPad2);				// +jwshin 110418
		
//  	printf("1");
		
		
		if(IsAC_PowerOff()){
			bExitSysLoop = TRUE;
			printf("LowPower\r\n");
			return;
		}

#if _SmartBright_ == ON
		// SmartBrightControl
		ucBrightADC = Bright_Input();
#if 1
		SmartBright();
#else		
		if(ucBrightADC1 < ucBrightADC) ucBrightADC1=ucBrightADC;

		if(++ucADCCounter > 3){ 
			ucBrightADC = ucBrightADC1;
			ucADCCounter = 0;
			ucBrightADC1 = 0;
			//printf("ucBrightADC(MAX)=%d\r\n",(unsigned short)ucBrightADC);
			SmartBright();
		}
#endif
#endif
	
		//printf("KeyInput=%02x,%02x\r\n",(unsigned short)KeyPad1,(unsigned short)KeyPad2);		// +jwshin 110526
	
		ADC_CON = DEFAULT_ADC_CON;		//Channel;  // Start AD Convert
		
		
		if(KeyPad1 < KeyMinLevel0)
			KeyTemp1 = 0x01;
		else if(KeyPad1 < KeyMinLevel1)
			KeyTemp1 = 0x02;
		else if(KeyPad1 < KeyMinLevel2)
			KeyTemp1 = 0x08;
		//---------- +jwshin 120223	
		else if(KeyPad1 < KeyMinLevel3)
			KeyTemp1 = 0x09;	
		//----------------------------	
		else
			KeyTemp1 = 0x00;
			
		if(KeyPad2 < KeyMinLevel0)
			KeyTemp1 |= 0x10;
		else if(KeyPad2 < KeyMinLevel1)
			KeyTemp1 |= 0x20;
		else if(KeyPad2 < KeyMinLevel2)
			KeyTemp1 |= 0x30;
		else
			KeyTemp1 |= 0x00;

		if(KeyTemp1 != KeyTemp2){
//			printf("KeyInput=%02x,%02x\r\n",(unsigned short)KeyPad1,(unsigned short)KeyPad2);		// +jwshin 110526
//			printf("KeyTemp=%02x,%02x\r\n",(unsigned short)KeyTemp1,(unsigned short)KeyTemp2);		// +jwshin 110526
			KeyTemp2 = KeyTemp1;
			bKeyChanged = TRUE;
			Set_usTimer1_1ms(KEY_STABLE_TIME);
		}
		
		
#if 0
//--------------------------------- -jwshin 111208 이 Routine은 사용하지 않음...
//check power key
//	-----------------------------------
//		Power button down
 		if((GetPowerKeyStatus() == LOW)&&( bPowerKeyFlag == FALSE) ){
			bPowerKeyFlag = TRUE;
			bKeyChanged = TRUE;
			Set_usTimer1_1ms(KEY_STABLE_TIME);
//			printf("bPowerKeyFlag == TRUE\r\n");
		}

//	-----------------------------------
//		Power button up
	//	printf("test %x\r\n", (unsigned short)bPowerKeyFlag);
		if((GetPowerKeyStatus() != LOW)&&(bPowerKeyFlag == TRUE)){
			bPowerKeyFlag = FALSE;
			bKeyChanged = TRUE;
			Set_usTimer1_1ms(KEY_STABLE_TIME);
	//		printf("bPowerKeyFlag == FALSE\r\n");
		}
//---------------------------------------------------------------------------------		
#endif
	}while(Get_usTimer1_1ms() != 0);

//change key
	if(bKeyChanged == TRUE){
		bKeyChanged = FALSE;
		ucCurKey = KeyTemp2;
		//--------------- +jwshin 111208
		if(ucCurKey == FactoryKey) {
			printf("EEPROM Init...2011.12 jwshin...\r\n");			// +jwshin 111208
			InitEEPROM(1);
			ucCurKey = IGNORE_KEY;
		}
		//----------------------------------------
		
		
		
		//--------------------- bPowerKeyFlag 도 사용하지 않음...
		if(bPowerKeyFlag == TRUE){
//			printf("bPowerKeyFlag\r\n");
		if((ucCurKey == FactoryKey)&&(ucPowerStatus < 0x80)){	//entry factory mode
			FactoryEnterMode();								
#ifdef BenQ_FACTORY
			BenQ_EnterFactoryMode();
#endif

			}
			ucCurKey = POWER_KEY;
		}
		//------------------------------------------------
		else{
		if((bVideoMuted == TRUE)&&(bIsBurnInEnabled == TRUE)&&(ucCurKey == QuitBurninKey)&&(bShowAging == TRUE)){
			bIsBurnInEnabled = FALSE;
			Write24C16(EPADDR_BURNIN, bIsBurnInEnabled);//0x14 = Burn-in mode		
//			Write24C16(EPADDR_FACTORY, 0 );
			ucCurKey = IGNORE_KEY;
		} 
		}

		if ((ucCurKey == IGNORE_KEY) && (ucPrevKey == FUNC_KEY) && !bIsOSDLocked)
			ucCurKey = LF_KEY;

		if (ucOSDType == LFDEMO && ucCurKey != FUNC_KEY )
			ucCurKey = IGNORE_KEY;

#ifdef ENABLE_TD_			//	THEFT DETERRENCE
		if(ucTD_State == TD_THEFT){
			ucCurKey = IGNORE_KEY;
		}
#endif
//printf("ucCurKey=%02x,%02x\r\n",(unsigned short)ucCurKey,(unsigned short)ucPrevKey);	// +jwshin 110526
		
// set repeat timer
		ucPrevKey = ucCurKey;
		if (ucCurKey == FUNC_KEY)
			ucTime2RepeatKey = 255;
		else
			ucTime2RepeatKey = KEY_HOLDING_TIME;
//release Repeat mark
	//	THEFT DETERRENCE
//		if(ucCurKey == MENU_KEY || ucCurKey == DDCCiHotKey ||ucCurKey == TDResetKey||ucCurKey == QuickResetKey)
		if(ucCurKey == MENU_KEY || ucCurKey == DDCCiHotKey ||ucCurKey == QuickResetKey )
		{
			RepeatCounter = 60;
		}
		else if ( ucCurKey==IGNORE_KEY ){
		}
	}
	//---------------------------------- Power Key가 On되면, 여기로 진입..~!
	else if((ucPowerStatus & SoftPowerOnFlag) !=0){	// ONLY IN DC ON
		if(ucTime2RepeatKey == 0){
			if((ucPrevKey == MENU_KEY)&&(bVideoMuted == FALSE)){
				ucTime2RepeatKey = 10;  //6 Sec
				if(RepeatCounter != 0){
					if(--RepeatCounter == 0){
						if(bIsOSDLocked == FALSE){
							bIsOSDLocked = TRUE;		//change to osd lock
							Write24C16(EPADDR_OSDLOCK, bIsOSDLocked);//0x05 = osd lock
						}
						else{
							bIsOSDLocked = FALSE;		//change to osd unlock
							Write24C16(EPADDR_OSDLOCK, bIsOSDLocked);//0x05 = osd lock
						}
						ShowOSD_Lock();
						ucCurKey = IGNORE_KEY;
						ucPrevKey = IGNORE_KEY;
					}
				}
			}
//#ifdef ENABLE_TD_			//	THEFT DETERRENCE
			else if((ucPrevKey == DDCCiHotKey)&&(bVideoMuted == FALSE)){
				ucTime2RepeatKey = 10;	//6 Sec
				if(RepeatCounter != 0){
					if(--RepeatCounter == 0){
						if(bIsDDCCiSupported == FALSE){
							bIsDDCCiSupported = TRUE;		//change to osd lock
							Write24C16(EPADDR_DDCCI, bIsDDCCiSupported);//0x05 = osd lock
							StartDDCCI();
						}
						else{
							bIsDDCCiSupported = FALSE;		//change to osd unlock
							Write24C16(EPADDR_DDCCI, bIsDDCCiSupported);//0x05 = osd lock
							StopDDCCI();
						}
						OSD_OFF();	// RELOAD FONT AFTER SOURCE MENU
						ShowDDCCiOnOff();
						ucCurKey = IGNORE_KEY;
						ucPrevKey = IGNORE_KEY;
					}
				}
			}
			else if(ucPrevKey == FUNC_KEY){
				ucCurKey = LF_DEMO_KEY;
				ucPrevKey = LF_DEMO_KEY;
			}
			else if(((ucOSDType >= OSDOFF)&&(ucOSDType <= DIRECT_MENU))||
				(ucOSDType == FACTORY) ||
				(ucOSDType == OUT_RANGE2)){
				switch(ucPrevKey){
				case UpKey:
				case DownKey:
					//if (ucOSDType==DIRECT_MENU&&ucOSDLvl1_Cursor == mDirect_Source) break;

					ucCurKey = ucPrevKey;

					if( ucOSDType==MAIN_MENU || ucOSDType ==SUB_MENU )
						ucTime2RepeatKey = 50;
					else
						ucTime2RepeatKey = KEY_REPEATING_TIME;
					break;
				}
			}
		}
	}
}

void CheckKey(void)
{

	ScanKeyPad();

//	if ( ucCurKey == IGNORE_KEY ) return;
//power saving
	if((ucPowerStatus & SoftPowerOnFlag) == 0){
		if(ucCurKey == UpKey){
			ucModeNumber = 0xff;
		}
		if(ucCurKey == DownKey){
			ucModeNumber--;
		}
		if(ucCurKey != POWER_KEY){
			ucCurKey = IGNORE_KEY;
		}
	}
	else if(bIsOSDLocked && ucCurKey!=IGNORE_KEY ){
		if(!bVideoMuted){
			if(ucOSDType != OSDOFF )
				OSD_OFF();
			else 
				ShowOSD_Lock();
		}
		 ucCurKey = IGNORE_KEY;
	}
	else if((IsPanelPowerOn() == OFF)||
		(bOutOfLimit && !(ucOSDType == DIRECT_MENU && ucOSDLvl1_Cursor == mDirect_Source)) || (bInSync == FALSE)) {
//		(bVideoMuted == TRUE)){			// -jwshin 120228
		


		if(ucCurKey==INPUT_KEY && !bDCReset){
			bForceToSleep = FALSE;
			ScalerPowerUp();
		
			if(bOutOfLimit){
				Set_usPoSvTimer(0);	//LET ShowOutOfRangeOver() DISABLED
			}	
		
			OSD_OFF();
			bBGMode = FALSE;
			ForceToBackground(0);
			SourceMenu();
			BackLightOn();
			
			Set_usOSDTimer_10ms(500);
			ucPrevKey = IGNORE_KEY;
		}

		//printf("%d , %d \r\n",(unsigned short)bInSync,(unsigned short)bForceToSleep);
		if(ucCurKey != POWER_KEY){						// +jwshin 120227						 PowerSaving 모드에서 Power Key를 제외한 모든 Key Disable...
			if((bInSync==FALSE)&&(bPowerSaveFlag==FALSE)) {						// +jwshin 120227 					 단, No Signal 이고, PowerSaving 이 아닌 상태에서는 Mode 전환 진입 허용
			}
			else {
				ucCurKey = IGNORE_KEY;
			}
		}
	}

//if ( ucOSDType==DIRECT_MENU&&ucOSDLvl1_Cursor == mDirect_Source )	printf("usOSDTimer_10ms=%d\r\n",usOSDTimer_10ms);

	if(ucCurKey != IGNORE_KEY && ucCurKey !=POWER_KEY ){
		if(ucCurKey != AUTO_KEY && usVSync > V_UPPER_BOUND && !(ucOSDType==DIRECT_MENU&&ucOSDLvl1_Cursor == mDirect_Source)){
			//if ( bShowOutRange85 && ucCurKey== DownKey )
			if(ucCurKey==INPUT_KEY){
				if(bShowOutRange85){
					OSD_OFF();
					bShowOutRange85 = FALSE;
				}
			}
			else{
				if(bShowOutRange85 ==  FALSE)
					ShowOutOfRange85Hz();
				ucCurKey = IGNORE_KEY;
			}
		}
		else if(ucOSDType==SOURCE_MSG || ucOSDType==BEST_MSG){
			OSD_OFF();
			ucCurKey = IGNORE_KEY;
		}
	}
	switch(ucCurKey){
//	printf("%d \n",ucCurKey);			// +jwshin 110527	
	case POWER_KEY:		//POWER
		ucCurKey = IGNORE_KEY;
		bShowAging = 0;
		if((ucPowerStatus & SoftPowerOnFlag) == 0){
			ucPowerStatus |= SoftPowerOnFlag;	//normal
			Write24C16(EPADDR_POWER, ucPowerStatus);//0x04 = Power Status
			bInSync = FALSE;
			
			if(bVideoMuted == FALSE){
				bVideoMuted = TRUE;
				Set_usPoSvTimer(500);
			}

			bBGMode = FALSE;
			ForceToBackground(0);	//Set fource to background
			ScalerPowerUp();
			if(ucModeNumber == 0xfc){
//				LED_RedOn();				// -jwshin 111213
				InitEEPROM(1);			
				EA = 0;
				while(1){};
			}
			
			ucModeNumber = 0xff;
			
	//SLOW UP FOR BOBO
/*		if((!bMute)&&(bStandalone == 0)){
			if(ucVolume!=0){
				ucVolume = 1;
				SetVolume();
			}
		} */					//-jwshin 111214

			bShowDiscon = FALSE;	//clear display flag
			bShowOutRange = FALSE;
			bShowOutRange85 = FALSE;
			bDCReset = TRUE;
			//InputSourceSelect();
			if(Read24C16(EPADDR_BURNIN) != 0){
				FactoryEnterMode();			
		#ifdef BenQ_FACTORY
				BenQ_EnterFactoryMode();
		#endif								
			}

			LoadModeIndependentSettings();
			LoadFont();

/*			if(ucSource == mSource_DVI)
				ucPowerStatus |= InputSourceDVI;
			else
				ucPowerStatus &= ~InputSourceDVI;*/
			InputSourceSelect();			
		}
	    else{
			OSD_OFF();

			ucPowerStatus &= ~SoftPowerOnFlag;	//power off
			Write24C16(EPADDR_POWER, ucPowerStatus);//0x04 = Power Status

			BF_DisableWindow(BF_WINDOW_1);
			BF_DisableWindow(BF_WINDOW_2);

			if(bFactoryMode == TRUE){
				ReleaseFactoryMode();
			}
			PowerSaving();
			WriteIIC560(DVI_CTRL15,0xb3);	// DVI Power Consumptipn 2006-03-27
			bStatusReport = 0;	
//			ClearNewModeLED();
			LED_RedOff();
			LED_GrnOff();
			SEL1_GrnOff();			// +jwshin 120224
			SEL2_GrnOff();

			AUDIO_MUTE();
			AMP_STBY();

		}
		break;
	case MENU_KEY:		//MENNU 
		MainMenu();
		Set_usOSDTimer_10ms((unsigned short)ucOSDTimer*100);
		ucCurKey = IGNORE_KEY;
		break;
	case UpKey:		//up
		ItemUp();
		ucCurKey = IGNORE_KEY;
		break;
	case DownKey:		//Down
		ItemDown();
		ucCurKey = IGNORE_KEY;
		break;
	case INPUT_KEY:
		if(bFactoryMode == TRUE){
			if(ucOSDType==OSDOFF||ucOSDType==OUT_RANGE2){
				FactoryShowMenu();
			}
		}
		else{
			if(ucOSDType==OSDOFF||ucOSDType==OUT_RANGE2){
				OSD_OFF();
				SourceMenu();
			}
			else if((ucOSDType == DIRECT_MENU)&&(ucOSDLvl1_Cursor == mDirect_Source)){
				if(++ucOSDLvl2_Cursor > mSource_VIDEO )
					ucOSDLvl2_Cursor = mSource_VGA;
				SelectLFMITM();
			}
			else{
				OSD_OFF();
			}
			Set_usOSDTimer_10ms(500);
		}
		ucCurKey = IGNORE_KEY;
		break;
	case LF_KEY:
		if(ucOSDType == LF_MAIN_MENU){
			LFMenuControl(LFDown);			
			Set_usOSDTimer_10ms(500);
		}
		else if(ucIsLFDemoMode == FALSE){
			LFMenuControl(LFOpen);
			Set_usOSDTimer_10ms(500);
		}
		ucCurKey = IGNORE_KEY;
		break;
	case LF_DEMO_KEY:

		if (ucOSDType == LFDEMO)
			LFLeaveDemoMode(1);
		else if (ucOSDType == OSDOFF)
			LFEnterDemoMode(1);

		ucCurKey = IGNORE_KEY;
		break;

	case AUTO_KEY:			//Auto

		if(ucOSDType == FACTORY)		// disable AutoKey in Factory Mode
			return;
			
		
		if(ucOSDType >= MAIN_MENU &&  ucOSDType <= SHOW_SLDR){
			ExitKey();
			Set_usOSDTimer_10ms((unsigned short)ucOSDTimer*100);
			break;
		}
		else if((ucSignalType != sigDVI)&&(ucOSDType == OSDOFF)&&(bBGMode == FALSE)){
			LED_GrnOn();
			OSD_OFF();
			ShowAutoAdj();
			AutoTune();
			OSD_OFF();
			if(usVSync > V_UPPER_BOUND) ucOSDType = OUT_RANGE2;
		}
		else if(bInSync==FALSE) {				// +jwshin 120227 신호 없을 때...		Sync Signal이 없을 때...
		}
		else
			OSD_OFF();
		ucCurKey = IGNORE_KEY;
		break;
		
		
	//-------------- +jwshin 120223
	case BUTTON_SEL_KEY_A :
		//--------------- +jwshin 120224 Select Button A가 선택되었을 경우...
		Button_En_SelA();
		SEL1_GrnOn();
		SEL2_GrnOff();
		ShowMonSelMsg(0);
		Write24C16(EPADDR_BUTTON_STATUS,0x01);
		ucCurKey = IGNORE_KEY;	
		break;
	case BUTTON_SEL_KEY_B :
		//--------------- +jwshin 120224 Select Button B가 선택되었을 경우...
		Button_En_SelB();
		SEL2_GrnOn();
		SEL1_GrnOff();
		ShowMonSelMsg(1);
		Write24C16(EPADDR_BUTTON_STATUS,0x00);
		ucCurKey = IGNORE_KEY;
		break;
	//------------------------------		
	}
}

