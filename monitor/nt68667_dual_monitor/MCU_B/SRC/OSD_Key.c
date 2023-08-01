#include "RAM.H"
#include "OSD.H"
#include "NT686xx_MCU_REG.H"
#include "NT686xx_SC_REG.H"
#include "Scaler.H"
#include "UserAdj.H"
#include "OSD_TAB.H"
#include "factory.H"
#include "nvram.H"
#include "rom_map.H"
#include "Mis.H"
#include "BFControl.H"
#include "smartbright.H"
#if _Enable_OD_ == ON
#include "OD.H"
#endif

code unsigned char SubItemTab[]={
	mLuminance_Tint ,mPicture_VPos, mColor_User_B, mOSDSetting_OSDTimeout, mSetup_Reset
};

void ItemUp(void)
{
unsigned char i;
	if(ucOSDType == MAIN_MENU){
		if(++ucOSDLvl1_Cursor > mSETUP){
			ucOSDLvl1_Cursor = mLUMINANCE;
		}
		if(((ucSource == mSource_DVI)||(ucSource == mSource_HDMI))&&(ucOSDLvl1_Cursor == mPICTURE))
			ucOSDLvl1_Cursor++;
		SelectMainIcon();
	}
	else if(ucOSDType == SUB_MENU){
		i = SubItemTab[ucOSDLvl1_Cursor];
		if((bFactoryMode == TRUE)&&(ucOSDLvl1_Cursor == mLUMINANCE)){
			i++;
		}
		else if((ucColorTemperature != COLOR_USER)&&(ucOSDLvl1_Cursor == mCOLOR)){
			i = 0;
		}
		if(++ucOSDLvl2_Cursor > i){
			ucOSDLvl2_Cursor = 0;
		}
		if((ucOSDLvl1_Cursor == mLUMINANCE)&&(ucSource < mSource_VIDEO)){
			if(ucOSDLvl2_Cursor == mLuminance_Saturation){
				if(bFactoryMode == TRUE){
					ucOSDLvl2_Cursor = mFactory;
				}
				else{
					ucOSDLvl2_Cursor = mLuminance_Brightness;
				}
			}
		}
		SelectSubItem();
	}
	else if(ucOSDType == SHOW_SLDR){
		switch(ucOSDLvl1_Cursor){
		case mLUMINANCE:
			switch(ucOSDLvl2_Cursor){
			case mLuminance_Brightness:
				BrightnessUp();
				break;
			case mLuminance_Contrast:
				ContrastUp();
				break;
			case mLuminance_Saturation:
				SaturationUp();
				break;
			case mLuminance_Tint:
				TintUp();
				break;
			}
			break;
		case mPICTURE:
			switch(ucOSDLvl2_Cursor){
			case mPicture_Phase:
				PhaseUp();
				break;
			case mPicture_Clock:
				ClockUp();
				break;
			case mPicture_HPos:
				HP_Up();
				break;
			case mPicture_VPos:
				VP_Up();
				break;
			}
			break;
		case mCOLOR:
			switch(ucOSDLvl2_Cursor){
			case mColor_Tempk:
				ColorTempUp();
				break;
			case mColor_User_R:
				ColorRedUp();
				break;
			case mColor_User_G:
				ColorGreenUp();
				break;
			case mColor_User_B:
				ColorBlueUp();
				break;
			}
			break;
		case mOSDSETTING:
			switch(ucOSDLvl2_Cursor){
			case mOSDSetting_Horizontal:
				OSD_X_Up();
				break;
			case mOSDSetting_Vertical:
				OSD_Y_Up();
				break;
			case mOSDSetting_Transparency:
				TransparencyUp();
				break;
			case mOSDSetting_OSDTimeout:
				OSD_TimerUp();
				break;
			}
			break;
		case mSETUP:
			switch(ucOSDLvl2_Cursor){
			case mSetup_Language:
				//LanguageUp();
				//---- -jwshin 111214	
				break;
			case mSetup_AudioMute:
				ucOSDLvl3_Cursor ^= BIT_0;
				SelectYesNo();
				bMute = (bit)ucOSDLvl3_Cursor;
				if(bMute){
					AUDIO_MUTE();
					AMP_STBY();
					printf("SetVolume=MUTE\r\n");
				}
				else {
					AMP_On();
					AUDIO_On();
					printf("SetVolume=MUTE Off\r\n");
				}				
				ucSavePointer = svMUTE;
				break;
			case mSetup_Input:
				InputSourceUp();
				break;
			case mSetup_DCR:
				ucOSDLvl3_Cursor ^= BIT_0;
				SelectYesNo();
				ucDynBKMode = ucOSDLvl3_Cursor;
				ucSavePointer = svDYBK;
				//LFEnableSettings();
				if((ucLFMode != LF_MODE_OFF || ucDynBKMode)){
					BF_DisableWindow(BF_WINDOW_2);
					BF_EnableWindow(BF_WINDOW_1);
					BF_SetActiveWindow(BF_WINDOW_1);
				}
				if(ucDynBKMode == 0){
					SetBrightness();
					iCurDynBk = ucBrightness;
				}
				break;
#if _Enable_OD_ == ON
			case mSetup_OD:
				bSmartResponse ^= BIT_0;
				ucOSDLvl3_Cursor = bSmartResponse;
				SelectYesNo();
				Write24C16(EPADDR_OD_ONOFF, ucOSDLvl3_Cursor);
				if(ucOSDLvl3_Cursor == 0)
					DisableOD();
				else
					EnableOD();
				break;
#endif
			case mSetup_Reset:
				ucOSDLvl3_Cursor ^= BIT_0;
				SelectYesNo();
				break;
			}
			break;
		}
	}
	else if(ucOSDType == LF_MAIN_MENU){
		LFMenuControl(LFUp);
	}
	// ---- -jwshin 120224 B Scaler 에서는 Volume 제어 안함..
	/*
	else if(ucOSDType == OSDOFF){
		ShowDirectVolumeMenu();				// +jwshin 120224
		
	}
	*/
	else if(ucOSDType == DIRECT_MENU){
		if(ucOSDLvl1_Cursor == mDirect_Source){
			if(--ucOSDLvl2_Cursor > mSource_VIDEO)
				ucOSDLvl2_Cursor = mSource_VIDEO;
			SelectLFMITM();
		}
		else if(ucOSDLvl1_Cursor == mDirect_Volume){
			DirectVolumeUp();
		}
		else if(ucOSDLvl1_Cursor == mDirect_Brightness){
			DirectBrightnessUp();
		}
	}
	else if(ucOSDType == FACTORY){
		FactoryItemUp();
	}
	

	if((ucOSDType == LF_MAIN_MENU)||(ucOSDType == DIRECT_MENU) || (ucOSDType == SOURCE_MSG))			// +jwshin 120313
	{
		if(bInSync == FALSE) 
		{
			Set_usOSDTimer_10ms((unsigned short)ucOSDTimer*100);
		}
		else
		{
			Set_usOSDTimer_10ms(300);
		}
	}
	else
	{
		Set_usOSDTimer_10ms((unsigned short)ucOSDTimer*100);
	}

}

void ItemDown(void)
{
unsigned char i;
	if(ucOSDType == MAIN_MENU){
		if(--ucOSDLvl1_Cursor > mSETUP){
			ucOSDLvl1_Cursor = mSETUP;
		}
		if(((ucSource == mSource_DVI)||(ucSource == mSource_HDMI))&&(ucOSDLvl1_Cursor == mPICTURE))
			ucOSDLvl1_Cursor--;
		SelectMainIcon();
	}
	else if(ucOSDType == SUB_MENU){
		i = SubItemTab[ucOSDLvl1_Cursor];
		if((bFactoryMode == TRUE)&&(ucOSDLvl1_Cursor == mLUMINANCE)){
			i++;
		}
		else if((ucColorTemperature != COLOR_USER)&&(ucOSDLvl1_Cursor == mCOLOR)){
			i = 0;
		}
		if(--ucOSDLvl2_Cursor > i){
			ucOSDLvl2_Cursor = i;
		}
		if((ucOSDLvl1_Cursor == mLUMINANCE)&&(ucSource < mSource_VIDEO)){
			if(ucOSDLvl2_Cursor == mLuminance_Tint){
				ucOSDLvl2_Cursor = mLuminance_Contrast;
			}
		}
		SelectSubItem();
	}
	else if(ucOSDType == SHOW_SLDR){
		switch(ucOSDLvl1_Cursor){
		case mLUMINANCE:
			switch(ucOSDLvl2_Cursor){
			case mLuminance_Brightness:
				BrightnessDown();
				break;
			case mLuminance_Contrast:
				ContrastDown();
				break;
			case mLuminance_Saturation:
				SaturationDown();
				break;
			case mLuminance_Tint:
				TintDown();
				break;
			}
			break;
		case mPICTURE:
			switch(ucOSDLvl2_Cursor){
			case mPicture_Phase:
				PhaseDown();
				break;
			case mPicture_Clock:
				ClockDown();
				break;
			case mPicture_HPos:
				HP_Down();
				break;
			case mPicture_VPos:
				VP_Down();
				break;
			}
			break;
		case mCOLOR:
			switch(ucOSDLvl2_Cursor){
			case mColor_Tempk:
				ColorTempDown();
				break;
			case mColor_User_R:
				ColorRedDown();
				break;
			case mColor_User_G:
				ColorGreenDown();
				break;
			case mColor_User_B:
				ColorBlueDown();
				break;
			}
			break;
		case mOSDSETTING:
			switch(ucOSDLvl2_Cursor){
			case mOSDSetting_Horizontal:
				OSD_X_Down();
				break;
			case mOSDSetting_Vertical:
				OSD_Y_Down();
				break;
			case mOSDSetting_Transparency:
				TransparencyDown();
				break;
			case mOSDSetting_OSDTimeout:
				OSD_TimerDown();
				break;
			}
			break;
		case mSETUP:
			switch(ucOSDLvl2_Cursor){
			case mSetup_Language:
				//LanguageDown();
				//---- -jwshin 111214
				break;
			case mSetup_AudioMute:
				ucOSDLvl3_Cursor ^= BIT_0;
				SelectYesNo();
				bMute = (bit)ucOSDLvl3_Cursor;
				if(bMute){
					AUDIO_MUTE();
					AMP_STBY();
			  	printf("SetVolume=MUTE\r\n");
				}
				else {
					AMP_On();
					AUDIO_On();
					printf("SetVolume=MUTE Off\r\n");
				}
				ucSavePointer = svMUTE;
				break;
			case mSetup_Input:
				InputSourceDown();
				break;
			case mSetup_DCR:
				ucOSDLvl3_Cursor ^= BIT_0;
				SelectYesNo();
				ucDynBKMode = ucOSDLvl3_Cursor;
				ucSavePointer = svDYBK;
				//LFEnableSettings();
				if((ucLFMode != LF_MODE_OFF || ucDynBKMode)){
					BF_DisableWindow(BF_WINDOW_2);
					BF_EnableWindow(BF_WINDOW_1);
					BF_SetActiveWindow(BF_WINDOW_1);
				}
				if(ucDynBKMode == 0){
					SetBrightness();
					iCurDynBk = ucBrightness;
				}
				break;
#if _Enable_OD_ == ON
			case mSetup_OD:
				bSmartResponse ^= BIT_0;
				ucOSDLvl3_Cursor = bSmartResponse;
				SelectYesNo();
				Write24C16(EPADDR_OD_ONOFF, ucOSDLvl3_Cursor);
				if(ucOSDLvl3_Cursor == 0)
					DisableOD();
				else
					EnableOD();
				break;
#endif
			case mSetup_Reset:
				ucOSDLvl3_Cursor ^= BIT_0;
				SelectYesNo();
				break;
			}
			break;
		}
	}
	else if(ucOSDType == LF_MAIN_MENU){
		LFMenuControl(LFDown);
	}
/*	else if(ucOSDType == OSDOFF){
		ShowDirectVolumeMenu();
	} */
	else if(ucOSDType == DIRECT_MENU){
		if(ucOSDLvl1_Cursor == mDirect_Source){
			if(++ucOSDLvl2_Cursor > mSource_VIDEO)
				ucOSDLvl2_Cursor = mSource_VGA;
			SelectLFMITM();
		}
		else if(ucOSDLvl1_Cursor == mDirect_Volume){
			DirectVolumeDown();
		}
		else if(ucOSDLvl1_Cursor == mDirect_Brightness){
			DirectBrightnessDown();
		}
	}
	//--------------- RGB Signal Switching 을 위한 Routine... +jwshin 120224				B Scaler에서는 OSDOFF Mode에서 Switching함..
	else if((ucOSDType == OSDOFF)||(ucOSDType == OUT_RANGE)){
		OSD_OFF();
		if((bB_Screen_ReverseFlag == 0) && (bCopy_Flag == 0) && (bRGB_SW_Flag == 0)) {
			bB_Screen_ReverseFlag = 1;
			Write24C16(EPADDR_B_SCREEN_REV,bB_Screen_ReverseFlag);
			bRGB_SW_Flag = 1;
			Write24C16(EPADDR_RGB_SW1,bRGB_SW_Flag);
			RGB_SW1_RGB1();
		}
		else if((bB_Screen_ReverseFlag == 0) && (bCopy_Flag == 1) && (bRGB_SW_Flag == 1)) {
			bB_Screen_ReverseFlag = 1;
			Write24C16(EPADDR_B_SCREEN_REV,bB_Screen_ReverseFlag);
			bRGB_SW_Flag = 0;
			Write24C16(EPADDR_RGB_SW1,bRGB_SW_Flag);
			RGB_SW1_RGB2();	
		}
		else if((bB_Screen_ReverseFlag == 1) && (bCopy_Flag == 0) && (bRGB_SW_Flag == 1)) {
			bB_Screen_ReverseFlag = 0;
			Write24C16(EPADDR_B_SCREEN_REV,bB_Screen_ReverseFlag);
			bRGB_SW_Flag = 0;
			Write24C16(EPADDR_RGB_SW1,bRGB_SW_Flag);
			RGB_SW1_RGB2();	
		}
		else if((bB_Screen_ReverseFlag == 1) && (bCopy_Flag == 1) && (bRGB_SW_Flag == 0)) {
			bB_Screen_ReverseFlag = 0;
			Write24C16(EPADDR_B_SCREEN_REV,bB_Screen_ReverseFlag);
			bRGB_SW_Flag = 1;
			Write24C16(EPADDR_RGB_SW1,bRGB_SW_Flag);
			RGB_SW1_RGB1();	
		}
		else
		{}
		
		ShowSourceMsg();				// +jwshin 120227 Mode 전환 시 화면 상태를 Display해 주기 위해... 삽입...
		
		if(bInSync == FALSE) {
			ucOSDType = OUT_RANGE;						// +jwshin 120313    신호가 없을 경우~!
			Set_usOSD2Timer_10ms((unsigned short)ucOSDTimer*100);				// +jwshin 120302
		}
		else {
			Set_usOSD2Timer_10ms(300);				// +jwshin 120302
		}
		//ucOSDType = OSDOFF;
	}	
	//----------------------------------------------
	
	else if(ucOSDType == FACTORY){
		FactoryItemDown();
	}

	if((ucOSDType == LF_MAIN_MENU)||(ucOSDType == DIRECT_MENU)||(ucOSDType == SOURCE_MSG))				// +jwshin 120313
	{
		if(bInSync == FALSE) 
		{
			Set_usOSDTimer_10ms((unsigned short)ucOSDTimer*100);
		}
		else
		{
			Set_usOSDTimer_10ms(300);
		}
	}
	else
		Set_usOSDTimer_10ms((unsigned short)ucOSDTimer*100);

}


void MainMenu(void)
{
//unsigned char i;
	switch(ucOSDType){
	case OSDOFF: 
		ucOSDType = MAIN_MENU;
		ucOSDLvl1_Cursor = 0;
		
		MainOSD();
		OSD_ON();

		break;
	case MAIN_MENU:
		ucOSDType = SUB_MENU;
		SelectSubItem();

	
		break;
	case SUB_MENU:
		if(ucOSDLvl1_Cursor == mLUMINANCE && ucOSDLvl2_Cursor == mFactory){
			SubIconWinOff();
			MainIconWinOff();
			FactoryShowMenu();
			break;
		}
		else{
			ucOSDType = SHOW_SLDR;
			ShowAdjustMenu();
		}
		break;
	case SHOW_SLDR:
		SaveData();
		ucOSDType = SUB_MENU;
		if(((ucOSDLvl1_Cursor == mCOLOR)&&(ucOSDLvl2_Cursor == mColor_Tempk))||(ucOSDLvl1_Cursor == mSETUP))
			SubIconWinOff();
		if(ucOSDLvl1_Cursor == mSETUP){
			if(ucOSDLvl2_Cursor == mSetup_Input){
				if(ucSource != (ucPowerStatus & ~SoftPowerOnFlag)){
					ucPowerStatus = ucSource | SoftPowerOnFlag;
					InputSourceSelect();
				}
			}
			else if(ucOSDLvl2_Cursor == mSetup_Reset){
				if(ucOSDLvl3_Cursor != mNo){
					Recall();
				}
			}
		}
		ShowSubMenu();
		SelectSubItem();
		break;
	case DIRECT_MENU:
		if(ucOSDLvl1_Cursor == mDirect_Source){
			if((ucPowerStatus & ~SoftPowerOnFlag) != ucSource){
				ChangeInputSource();
			}
			else{
				ucSource = ucOSDLvl2_Cursor;
				ucSavePointer = svSOURCE;
				OSD_OFF();
				
				if(usVSync > V_UPPER_BOUND){	//BACK TO OUTOFRANGE85HZ AFTER SOURCE MENU TIMEOUT
					ucOSDType = OUT_RANGE2;
				}
				else if(bOutOfLimit){	//SHOW OUTOFRANGE AFTER SOURCE MENU TIMEOUT
					bShowOutRange = FALSE;
					Set_usPoSvTimer(500);
				}
			}
		}
		else
			OSD_OFF();
		break;
	case DDCCI_MSG:
	case LOCK_MSG:
	case LF_MAIN_MENU:
		OSD_OFF();
		break;
	case FACTORY:
		FactoryEnter();
		break;
		
	}
	ucCurKey = IGNORE_KEY;
}


void ExitKey()
{
	switch(ucOSDType){
	case MAIN_MENU: 
		OSD_OFF();
		ucOSDLvl1_Cursor = 0;
		break;
	case SUB_MENU:
		SubIconWinOff();
		ucOSDType = MAIN_MENU;
		ucOSDLvl2_Cursor = 0;
		break;
	case SHOW_SLDR:
		SaveData();
		ucOSDType = SUB_MENU;
		ShowSubMenu();
		SelectSubItem();
		ucOSDLvl3_Cursor = 0;
		break;
	}
	
	ucCurKey = IGNORE_KEY;
		
}






	










		
		

