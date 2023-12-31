#include "MCU.H"
#include "8051.H"
#include "RAM.H"
#include "NVRAM.H"
#include "sRGB.H"
#include "NT686xx_MCU_REG.H"
#include "Scaler.H"
#include "OSD.H"
#include "NT686xx_SC_REG.H"
#include "Board.H"
#include "Mis.H"
#include "stdio.H"
#include "Factory.H"
#include "OSD_TAB.H"
#include "Rom_map.H"
#include "ModeHandle.H"
#include "BFControl.H"
#include "OSD_LF.H"

void CheckPowerStatus()
{
	ADC_CON = DEFAULT_ADC_CON;		//Channel;  // Start AD Convert
	if((ucPowerStatus & SoftPowerOnFlag)== 0){
		PowerSaving();		//power saving befor power off
		LED_RedOff();
		LED_GrnOff();
//		printf("PowerOff\r\n");
	}
	else{

		LED_GrnOn();
		
//		printf("PowerOn\r\n");
	}
}

void CheckTimer()
{
	//printf(" %d \r\n", (unsigned short)ucOSDType);					// +jwshin 120302
	if((ucOSDType <= LF_MAIN_MENU)&&(ucOSDType > OSDOFF) || (ucOSDType==SOURCE_MSG)||
	(ucOSDType==LOCK_MSG)||	(ucOSDType==BEST_MSG) || (ucOSDType==DDCCI_MSG)||(ucOSDType == POWER_ON_LOGO)){			// +jwshin 120224 POWER_ON_LOGO 추가..

		if(Get_usOSDTimer_10ms() == 0){
			if(ucOSDType == DIRECT_MENU && ucOSDLvl1_Cursor == mDirect_Source){
				if((ucPowerStatus & ~SoftPowerOnFlag) != ucSource){
					ChangeInputSource();
					return;
				}
			}	
			
			OSD_OFF();
			
			if(bOutOfLimit){	//SHOW OUTOFRANGE AFTER SOURCE MENU TIMEOUT
				bShowOutRange = FALSE;
				Set_usPoSvTimer(500);
			}
			else if(usVSync > V_UPPER_BOUND){	//BACK TO OUTOFRANGE85HZ AFTER SOURCE MENU TIMEOUT
				ucOSDType = OUT_RANGE2;
			}
		}
	}
	//-------------- +jwshin 120302
	else if(ucOSDType == POWER_ON_LOGO) {
		if(bInSync == FALSE) {
			//------------------ +jwshin POWER_ON_LOGO를 위한 Mode
			if((Get_usOSD2Timer_10ms() == 0)) {
				OSD_OFF();
	
				PowerSaving();
				bForceToSleep= TRUE;
			}
			//----------------------------------
			else if((bInSync==TRUE) && (Get_usOSD2Timer_10ms() == 0)) {					// +jwshin 120302   신호가 있고, OSD2Timer가 0일 경우에는 OSD를 Off..~!
				OSD_OFF();
			}
		}
	}
	else if(ucOSDType == OUT_RANGE2){
		if(Get_usOSDTimer_10ms() == 0){			// show out 5 seconds
			bShowOutRange85 = FALSE;
			WriteIIC560(OSD_CTRL1,0x00);

			if(ucOutOfRangeTimer == 0){		// last time, show NoSync and going to PowerSaving 2005-11-30 V019b1
				bIsFRCMode = TRUE;
				ShowNoSync();
				bShowNoSync = TRUE;
				ucOSDType = OUT_RANGE;
				Set_usWarningMsgTimer_1s(10);				
	
			}
		}
		if(Get_usWarningMsgTimer_1s() == 0){		// disappear for 60 seconds
			ucOutOfRangeTimer--;
			ShowOutOfRange85Hz();
			Set_usWarningMsgTimer_1s(60);
		}
	}
	else if(ucOSDType == OUT_RANGE){
		if(Get_usWarningMsgTimer_1s() == 0){
			//	DVI disable interrupt
			if(ucSignalType == sigDVI){
				WriteIIC560(SYNC_INT_EN1,0x00);	//disable IRQ interrupt
				WriteIIC560(SYNC_INT_EN2,0x00);
				ucCurrentDVIClk = ReadIIC560(DVI_PIXELCLK);
				//printf("ucCurrentDVIClk = %d\r\n",(unsigned short)ucCurrentDVIClk);
			}
			OSD_OFF();

			PowerSaving();
//			ClearNewModeLED();
//			LED_GrnOff();						// -jwshin 111213
//			LED_RedOn();
			bForceToSleep= TRUE;
		}
	}
	else if(ucIsLFDemoMode == TRUE){
		if(ucOSDType == OSDOFF)
			ShowLFDemoOSD();
		else if(ucOSDType == LFDEMO){
			
#ifdef BF_MOVING_WINDOW

			BF_MovingWindow();

#else
			MoveLFDemoOSD();
#endif
		}
	}


//	if((bPOTUpdate == TRUE) && (bFactoryMode==FALSE)){
	if(bPOTUpdate == TRUE){
		Write24C16(EPADDR_POT_BYTE0,(unsigned char)ulPOTTimerH);//0x1a = POT byte 0
		Write24C16(EPADDR_POT_BYTE1,(unsigned char)(ulPOTTimerH >> 8));//0x1b = POT byte 1
		Write24C16(EPADDR_POT_15M, ucPOTTimerM_4);	//0x2d = POT_15M
		bPOTUpdate = FALSE;
	}


	if(ucTime2Backlight == 1){	// 1: Turn ON 0: Do nothing
	   	if(!IsBackLightOn()){
     	  	BackLightOn();
		}
#if 0
      	if(ucDynBKMode && (IsBackLightOn()) && (bVideoMuted == FALSE) && !bDDCCmdUpdate){

			if(Get_usBFTimer_10ms() == 0){
				if(ucBF_Status == 0){
					ucBF_Status = 1;
					BF_UpdateHistogram();
					Set_usBFTimer_10ms(BF_DYNAMIC_ACC_TIME);
				}
				else if(ucBF_Status == 1){
					ucBF_Status = 2;
					BF_GetHistogram();
					Set_usBFTimer_10ms(BF_DYNAMIC_ACC_TIME);
				}
				else{
					ucBF_Status = 0;
#ifdef BF_DYNAMIC_BACKLIGHT
						BF_SetDymBacklight();
#endif
					if(ucBFMode == BF_ACC_AUTO){
						unsigned char tmpReg1;
						tmpReg1 = ReadIIC560(0x130);
						if((tmpReg1 & BIT_1) != 0){	// WINDOW1
							BF_SetDymACEMode(0);
						}
					}
					Set_usBFTimer_10ms(BF_DYNAMIC_ACC_TIME);
				}
			}

		}	
#else

      	if(ucDynBKMode && (IsBackLightOn()) && (bVideoMuted == FALSE) && !bDDCCmdUpdate){
			if(Get_usBFTimer_10ms() > 2) BF_UpdateHistogram();
			if((Get_usBFTimer_10ms() == 0) && !bDDCCmdUpdate)
			//if(Get_usBFTimer_10ms() < 2)
			{
				BF_GetHistogram();
			}

#ifdef BF_DYNAMIC_BACKLIGHT
			if((ucDynBKMode == ON) && !bDDCCmdUpdate){
				BF_SetDymBacklight();
			}
#endif
			if((Get_usBFTimer_10ms() == 0) && !bDDCCmdUpdate){
				if(ucBFMode == BF_ACC_AUTO){
					unsigned char tmpReg1;
					tmpReg1 = ReadIIC560(0x130);
					if((tmpReg1 & BIT_1) != 0)	// WINDOW1
					{
						BF_SetDymACEMode(0);
					}
				}
			}

			if((Get_usBFTimer_10ms() == 0) && !bDDCCmdUpdate)
			{
				BF_UpdateHistogram(); 
				BF_GetHistogram();
				Set_usBFTimer_10ms(BF_DYNAMIC_ACC_TIME);
			}

		}	
#endif
	}



#ifdef ENABLE_TD_		//	THEFT DETERRENCE
//	printf("ucTD_Timeout=%d\r\n",(unsigned short)ucTD_Timeout);
	if(((ucTD_State == TD_POSSIBLE_THEFT && ucTD_Timeout == 0) || (ucTD_State == TD_THEFT )|| (ucTD_State == TD_LOG_TIMEOUT )) && 
		(ucOSDType != POWER_ON_LOGO) ) {

		if(ucTD_State == TD_POSSIBLE_THEFT){
			ucTD_State = TD_THEFT;
			//ucTD_State = TD_LOG_TIMEOUT;
			Write24C16(EPADDR_TD_STATE, ucTD_State);
		}

		if(!bForceToSleep && IsBackLightOn() && (bVideoMuted == FALSE)){
//			printf("usPoSvTimer=%d\r\n",(unsigned short)usPoSvTimer);
			
			if(!bShowTheftOSD){
//				ucBrightness = MIN_BRIGHTNESS;	//DIFFERENT BANK, CAN NOT USE MCU_DataMap[EPADDR_MIN_BRIGHT];	//0x08 = brightness
				ucBrightness = 0;	//DIFFERENT BANK, CAN NOT USE MCU_DataMap[EPADDR_MIN_BRIGHT];	//0x08 = brightness
				//ucSavePointer = svBRIGHTNESS;
				//SaveData();
//				ucContrast = MIN_CONTRAST;	//DIFFERENT BANK, CAN NOT USE MCU_DataMap[EPADDR_MIN_CONTRAST];		//0x09 = contrast
				ucContrast = 0;	//DIFFERENT BANK, CAN NOT USE MCU_DataMap[EPADDR_MIN_CONTRAST];		//0x09 = contrast
				//ucSavePointer = svCONTRAST;
				//SaveData();
				SetBrightness();
				ucColorTemperature = COLOR_USER;
				ucR_Gain= ucR_GainUser = 0;
				ucG_Gain= ucG_GainUser = 0;
				ucB_Gain= ucB_GainUser = 0;
				SetContrastRGB();

				ucLFMode = LF_MODE_OFF;
				ucDynBKMode = 0;
				//ucSavePointer = svDYBK;
				//SaveData();
				//LFEnableSettings();
			}

			if(ucOSDType == OSDOFF || Get_usPoSvTimer() == 0)
				ShowTheftOSD();
		}
	}
#endif


}


void LEDFlash()
{
	if(bIsLEDFlashing== TRUE){	//new mode
		if ( bGLEDState == FALSE ) {
			LED_GrnOn();
		}
		else{
			LED_GrnOff();
		}
		bIsLEDFlashing = FALSE;
	}
	
/*
	if(bIsLFLEDFlashing == TRUE){	//LF demo mode
		if ( bLFLEDState == FALSE ) {
			LED_LF_On();
		}
		else{
			LED_LF_Off();
		}
		bIsLFLEDFlashing = FALSE;
	}
*/
}

//---------------------- +jwshin 111213
//------------- LED Flicking Routine
void GrnLEDFlick()
{
	if(ucNoSigTimer==0) {	
			if(NoSigTogg) {
				LED_GrnOn();
			}
			else {
				LED_GrnOff();
			}
			NoSigTogg ^= 1;
			ucNoSigTimer = 100;
	}
	
}
	


void Sleep(unsigned short time)
{
	Set_usTimer1_1ms(time);
	while(Get_usTimer1_1ms() != 0){};
}

void Set_usTimer1_1ms(unsigned short time)
{
	usTimer1_1ms = time;			// timeout n ms
	usTimer1_1ms = time;			// timeout n ms
}

unsigned short Get_usTimer1_1ms(void)
{
unsigned short temp1,temp2;
	do{
		temp1 = usTimer1_1ms;
		temp2 = usTimer1_1ms;
	}
	while(temp1 != temp2);
	return temp1;
}

void Set_usPoSvTimer(unsigned short time)
{
	usPoSvTimer = time;			// timeout n ms
	usPoSvTimer = time;			// timeout n ms
}

unsigned short Get_usPoSvTimer(void)
{
unsigned short temp1,temp2;
	do{
		temp1 = usPoSvTimer;
		temp2 = usPoSvTimer;
	}
	while(temp1 != temp2);
	return temp1;
}

void Set_usWarningMsgTimer_1s(unsigned short time)
{
	usWarningMsgTimer_1s = time;			// timeout n ms
	usWarningMsgTimer_1s = time;			// timeout n ms
}

unsigned short Get_usWarningMsgTimer_1s(void)
{
unsigned short temp1,temp2;
	do{
		temp1 = usWarningMsgTimer_1s;
		temp2 = usWarningMsgTimer_1s;
	}
	while(temp1 != temp2);
	return temp1;
}

void Set_usOSDTimer_10ms(unsigned short time)
{
	usOSDTimer_10ms = time;			// timeout n ms
	usOSDTimer_10ms = time;			// timeout n ms
}

unsigned short Get_usOSDTimer_10ms(void)
{
unsigned short temp1,temp2;
	do{
		temp1 = usOSDTimer_10ms;
		temp2 = usOSDTimer_10ms;
	}
	while(temp1 != temp2);
	return temp1;
}

void Set_ulPOTTimerH(unsigned long time)
{
	ulPOTTimerH = time;			// timeout n ms
	ulPOTTimerH = time;			// timeout n ms
}

//-------------------- +jwshin 120302
void Set_usOSD2Timer_10ms(unsigned short time)
{
	usOSDTimer_10ms = time;			// timeout n ms
	usOSDTimer_10ms = time;			// timeout n ms
}

unsigned short Get_usOSD2Timer_10ms(void)
{
unsigned short temp1,temp2;
	do{
		temp1 = usOSDTimer_10ms;
		temp2 = usOSDTimer_10ms;
	}
	while(temp1 != temp2);
	return temp1;
}
//-----------------------------------

unsigned long Get_ulPOTTimerH(void)
{
unsigned long temp1,temp2;
	do{
		temp1 = ulPOTTimerH;
		temp2 = ulPOTTimerH;
	}
	while(temp1 != temp2);
	return temp1;
}

void Set_usBFTimer_10ms(unsigned short time)
{
	usBFTimer_10ms = time;			// timeout n ms
	usBFTimer_10ms = time;			// timeout n ms
}

unsigned short Get_usBFTimer_10ms(void)
{
unsigned short temp1,temp2;
	do{
		temp1 = usBFTimer_10ms;
		temp2 = usBFTimer_10ms;
	}
	while(temp1 != temp2);
	return temp1;
}












/*
void WriteFixString( unsigned char x, unsigned char y, unsigned char *str)
{
	xdata unsigned char buff[20];	
	unsigned char i;
	
#ifdef NO_PRINT_LIB
	buff[0]='n'; buff[1]='\0';
	StrCat(buff,str,20);
#else
	sprintf( buff, "n%s", str);
#endif

	for ( i=0;  buff[i] != '\r' && buff[i] != '\0' && buff[i]<0x80; i++);
//	for ( i=0;  buff[i] != '\r' && buff[i] != '\0'; i++)

	buff[0] = i - 1;
//	for ( j = i; j< 20; j++ ) buff[j] = 0;	fill 0's in remaining

	ucStrAlignment = 0;
	ucStrWidth = 1;

	WriteArialFont(buff);	
	WriteXY_String(1, x, y);
	
}
*/

#ifdef NO_PRINT_LIB
void UShortToStr(unsigned short us_value, unsigned char *str, unsigned int digit)
{
// us_value -> str
// if digit = 3:   us_value = 12  then str="012"
// if digit = 0:   us_value = 12 then str="12"
 //unsigned short rev_value =0;
 unsigned int doffset,total_len=0;
 unsigned short ustmp=us_value;

 
 	if (digit==0)
 	{
 		do {
 			total_len++;
 		}while ( (ustmp/=10)>0 );	
 	}
 	else
 	{
 		total_len = digit;
 	}
 
 	doffset = total_len;
 	do {
 		doffset--;
 		*(str+doffset) = (us_value%10) +'0';
	}while ( (us_value/=10)>0 );
	
	while (doffset>0) *(str+(--doffset)) = ' ';
	*(str+total_len)='\0';
	
 /*
 do
 	{ 
  		*str++ = (us_value%10) +'0';
  	}
  	while ( (us_value/=10)>0 );
 	*str = '\0';
 	
 	return (str= pStart);
*/ 	
 	
 /* 
 	do
 	{
 		rev_value = rev_value*10 + us_value%10;
 		d++;
 printf("d=%d, rev_value=%d\r\n",(unsigned short)d, (unsigned short)rev_value);
 	}
 	while ( (us_value/=10)>0 );

	if ( digit != 0 )
	{
		d = digit -d;
		while ( d--> 0 ) *str++ = ' ';
	}

 	do
 	{ 
  		*str++ = (rev_value%10) +'0';
  		printf("rev_value=%d\r\n", rev_value);
  	}
  	while ( (rev_value/=10)>0 );
 	*str = '\0';
  
 	return (str = pStart);
*/
}

void StrCat(unsigned char *p_str1,unsigned char *p_str2, unsigned int str1_len)
{
	unsigned char *ptmp1 = p_str1;
	unsigned char *ptmp2 = p_str2;
	unsigned int len = 0;

	while ( *ptmp1++ != '\0' ) len++;
	while ( *ptmp2++ != '\0' ) len++;
	if ( len >str1_len-1 ) return;

	ptmp1--;
	ptmp2 = p_str2;
	while ( (*ptmp1++ = *ptmp2++) != '\0' ) {}

}

/*
unsigned char *StrCopy(char *p_to, unsigned char *p_from)
{
	unsigned char *pStart = p_to;
		 
	while((*p_to++ = *p_from++ ) != '\0' ) {}
		 
	return (p_to=pStart);
}
*/
#endif