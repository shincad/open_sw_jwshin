#include "Scaler.H"
#include "AutoAdj.H"
#include "NVRAM.H"
#include "RAM.H"
#include "UserAdj.H"
#include "ModeHandle.H"
#include "8051.H"
#include "sRGB.H"
#include "ROM_MAP.H"
#include "OSD.H"
#include "Panel.H"
#include "NT686xx_SC_REG.H"
#include "Mis.H"
#include "Board.H"
#include "DDC_Ci.H"
#include "Factory.H"
#include "math.H"
#include "HDCP.H"
#include "smartbright.h"
#include "BFControl.H"

#define __CHECK_RESOLUTION__

//#ifdef ADC_OFFSET_DOWN
//xdata unsigned char ucR_OFFSET,ucG_OFFSET,ucB_OFFSET;
//#endif

#ifdef AUTO_OFFSET
xdata unsigned char regNR1,regNR2,regNR3,regNR4;
#endif

idata unsigned char ucAutoPct;

void CheckResolution(void);


void EndExit(unsigned char Reg0x06A)
{
	ucTime2RepeatKey = KEY_HOLDING_TIME;
	ucPrevKey = IGNORE_KEY;
	WriteIIC560(JITTER_CTRL,Reg0x06A);	//Analog de-jitter // Jude 2005/04/06
}

void AutoTuneExit()
{
	if ( bOptAbort == TRUE ) {
		if(usTmpHSync != 0xffff){
			unsigned char temp;
			ForceToBackground(0);	//Set fource to background
			temp = ucVPOffset;
			LoadModeDependentSettings();				
			ucVPOffset = temp;
			SetHP();				// 2006-01-23 RETURN H_POSITION IF AUTO_FAIL
			SetADC_PLL();
			SetADC_Phase();
			SetScaler();
			WriteIIC560(OSD_CTRL1,0x00);
			SetDisplayNormal();
		}
	}
	else{		//ok
		SaveModeDependentSettings();
		SetMinMax();
		AutoPosition();
//		AutoDelay();
	}
#if FE2P_LIB==ON
	FE2P_Process(1);	
#endif
}

#ifdef ADC_OFFSET_DOWN
void RestoreADCOffset()
{
	//WriteIIC560(ROFFSET, ucR_OFFSET);
	//WriteIIC560(GOFFSET, ucG_OFFSET);
	//WriteIIC560(BOFFSET, ucB_OFFSET);
	WriteIIC560(ROFFSET, ucR_ADC_Offset);
	WriteIIC560(GOFFSET, ucG_ADC_Offset);
	WriteIIC560(BOFFSET, ucB_ADC_Offset);
}
#endif


void AutoTune(void)
{
unsigned short HP_Temp,VP_Temp;
unsigned char Reg0x06A;

	if(ucSignalType == sigDVI)	return;

	ucAutoPct = 4;
//	ClearNewModeLED();
	Reg0x06A = ReadIIC560(JITTER_CTRL);

	if(usTmpHSync == 0xffff)	//	goto Error1;
	{
		EndExit(Reg0x06A);
		return;
	}

	//Reg0x06A = ReadIIC560(JITTER_CTRL);
	WriteIIC560(JITTER_CTRL,0x00);	//Analog de-jitter // Jude 2005/04/06
	HP_Temp = usHPStart;
	VP_Temp = usVPStart;
	bIsNonFullScreen = FALSE;
	bOptAbort = FALSE;
#ifdef __CHECK_RESOLUTION__
	CheckResolution();
#endif
	AutoPosition();

	if(usTmpHSync == 0xffff)	//	goto Error1;
	{
		EndExit(Reg0x06A);
		return;
	}
	if(bOptAbort == TRUE){
		if(bIsNonFullScreen == FALSE){
			//goto Error1;
			EndExit(Reg0x06A);
			return;
		}
	}
	
#ifdef ADC_OFFSET_DOWN
//	printf("ADC_Offset_DOWN\r\n");
	WriteIIC560(ROFFSET, ucR_ADC_Offset+16); // 2005-11-30 jerry
	WriteIIC560(GOFFSET, ucG_ADC_Offset+16);
	WriteIIC560(BOFFSET, ucB_ADC_Offset+16);
#endif

	AutoClock();


	if(usTmpHSync == 0xffff)	//	goto Error1;
	{
		EndExit(Reg0x06A);
#ifdef ADC_OFFSET_DOWN
		RestoreADCOffset();
#endif
		return;
	}
	
	if ( bOptAbort ==TRUE ) {
		if(bIsNonFullScreen == FALSE){
			//goto Error;
			AutoTuneExit();
			EndExit(Reg0x06A);
#ifdef ADC_OFFSET_DOWN
			RestoreADCOffset();
#endif
			return;
		}
		else{
			bOptAbort = FALSE;			
			AutoClockByPhase(1);
		}
	}
	else{
		AutoClockByPhase(0);
	}
	if(usTmpHSync == 0xffff)	//	goto Error1;
	{
		EndExit(Reg0x06A);
#ifdef ADC_OFFSET_DOWN
		RestoreADCOffset();
#endif
		return;
	}

	AutoPhaseFineTune();
	if(usTmpHSync == 0xffff)	//	goto Error1;
	{
		EndExit(Reg0x06A);
#ifdef ADC_OFFSET_DOWN
		RestoreADCOffset();
#endif
		return;
	}
	
	if ( bOptAbort == TRUE )	//	goto Error;
	{
		AutoTuneExit();
#ifdef ADC_OFFSET_DOWN
		RestoreADCOffset();
#endif
		return;
	}

	AutoPosition();
	if(usTmpHSync == 0xffff)	//	goto Error1;
	{
		EndExit(Reg0x06A);
#ifdef ADC_OFFSET_DOWN
		RestoreADCOffset();
#endif
		return;
	}
	
	//fail
	if((bOptAbort ==TRUE ) && (bIsNonFullScreen == TRUE)){	//fail

		usHPStart = HP_Temp;
		usVPStart = VP_Temp;
		SetHP();
		SetVP();
		bOptAbort = FALSE;
	}
	AutoTuneExit();
	EndExit(Reg0x06A);
#ifdef ADC_OFFSET_DOWN
	RestoreADCOffset();
#endif



}

void AutoPosition(void)
{
//unsigned short temph,tempv,H_Active,V_Active;
unsigned short temph,tempv,V_Active;

	WriteIIC560(GI_HMASK_BEG,0x10);  // AutoPosition Pixel mask -> H
	WriteIIC560(GI_HMASK_END,ucMinHP);  // AutoPosition Pixel mask -> H
	WriteIIC560(GI_VMASK_BEG,0x00);  // AutoPosition Pixel mask -> V
	WriteIIC560(GI_VMASK_END,0x00);  // AutoPosition Pixel mask -> V
	WriteIIC560(GI_POS_THR,0x40);  // Red Noise Margin
	WriteIIC560(GI_AUTO_TUNE_CTRL,0x00);

	CheckModeChange();
	if(bOptAbort == TRUE)
		return;
		
	if(ucSignalType == sigDVI){	//DVI
 	 	WriteIIC560(GI_AUTO_TUNE_CTRL,0x11);
		Sleep(20);
	}
	else{
		GetHmask();
  	 	WriteIIC560(GI_AUTO_TUNE_CTRL,0x41);
	}
   	ucLoopTimer_10ms = 10;
   	while((ReadIIC560(GI_AUTO_TUNE_CTRL) & BIT_0) && ucLoopTimer_10ms != 0){
		CheckModeChange();
		if ( bOptAbort == TRUE )
			return;
	}
   	if(ucLoopTimer_10ms != 0){				// Auto-Position OK
		V_Active = ReadWordIIC560(GI_POS_VLEN_LI) & 0x07ff;		//Active
		//H_Active = ReadWordIIC560(GI_POS_HWID_LI) & 0x07ff;

//		printf("ucResolution = %d\r\n", (unsigned short)ucResolution);
//		printf("V_Active = %d\r\n",V_Active);
		//printf("H_Active = %d\r\n",H_Active);

		
		tempv = ReadWordIIC560(GI_POS_VBEGO_LI) & 0x07ff;		//Back-porch
		temph = ReadWordIIC560(GI_POS_HBEG_LI) & 0x07ff;
#ifdef R640_TUNE
		if(H_ActiveTab[ucResolution] == 640) temph >>= 1;
#endif
//		printf("temph=%d,usHTotal=%d,H_ActiveTab=%d\r\n", temph,usHTotal,H_ActiveTab[ucResolution]);
//		printf("tempv=%d,usVTotal=%d,V_ActiveTab=%d\r\n", tempv,usVTotal,V_ActiveTab[ucResolution]);

		if ( ucResolution == 1 && V_Active==350 )	// 640x350 SOG==> resolution show 720x400; activeV=350
		{									// 2005-11-25 jerry
/*
			tempv = ReadWordIIC560(GI_POS_VBEGO_LI) & 0x07ff;		//Back-porch
			temph = ReadWordIIC560(GI_POS_HBEG_LI) & 0x07ff;
#ifdef R640_TUNE
			if(H_ActiveTab[ucResolution] == 640) temph >>= 1;
#endif
*/
/*
			if(temph > usMaxHP)
				usHPStart = usMaxHP;
			else if(temph < ucMinHP)
				usHPStart = ucMinHP;
			else
			usHPStart = temph;

			if(tempv > ucMaxVP)
				usVPStart = ucMaxVP;
			else if(tempv < ucMinVP)
				usVPStart = ucMinVP;
			else
				usVPStart = tempv-25;	// 720x350 => 720x400
*/
			usHPStart = temph;
			usVPStart = tempv-25;	// 720x350 => 720x400
			SetHP();
			SetVP();
			return;
		}
//		else if ( (ucResolution == 2 && (V_Active == 350 || V_Active==400)) ||   // 640x350@60, 720x400@60 ERROR TO SHOW 640x480@60
//			(ucResolution == 5  || ucResolution==14 ) )				// 1024x768 & 1280x768 for (-,+)
		else if ( (ucResolution == 2 && (V_Active == 350 || V_Active==400)))   // 640x350@60, 720x400@60 ERROR TO SHOW 640x480@60
		{
/*
			tempv = ReadWordIIC560(GI_POS_VBEGO_LI) & 0x07ff;		//Back-porch
			temph = ReadWordIIC560(GI_POS_HBEG_LI) & 0x07ff;
#ifdef R640_TUNE
			if(H_ActiveTab[ucResolution] == 640) temph >>= 1;
#endif
*/
			// THESE MODES WILL ALIGN WTHIN LEFT TOP CORNER, COMMENT 2006-02-15
			
			usHPStart = temph;
			usVPStart = tempv;

			SetHP();
			SetVP();
			return;
		}

/*
		tempv = ReadWordIIC560(GI_POS_VBEGO_LI) & 0x07ff;		//Back-porch
		temph = ReadWordIIC560(GI_POS_HBEG_LI) & 0x07ff;
#ifdef R640_TUNE
		if(H_ActiveTab[ucResolution] == 640) temph >>= 1;
#endif
		printf("temph=%d,usHTotal=%d,usActiveH=%d\r\n", temph,usHTotal,usActiveH);
		printf("tempv=%d,usVTotal=%d,usActiveV=%d\r\n", tempv,usVTotal,V_ActiveTab[ucResolution]);
*/

//		if((tempv > 0xff) || (temph > (usHTotal-usActiveH))){
		if((tempv > (usVTotal-V_ActiveTab[ucResolution])) || (temph > (usHTotal-H_ActiveTab[ucResolution]))){
			if((V_Active == V_ActiveTab[ucResolution]) && (H_ActiveTab[ucResolution] > 1152)){
				SetHP();
				SetVP();
			}
			else{
				bOptAbort = TRUE;
				bIsNonFullScreen = TRUE;
				// WHO WILL COME HERE??
			}
		}
		else{
			//--------	DOS MODE(640X480) AUTO TUNE ISSUE -------------
			if(temph > usMaxHP)
				usHPStart = usMaxHP;
			else if(temph < ucMinHP)
				usHPStart = ucMinHP;
			else
			usHPStart = temph;

			if(tempv > ucMaxVP)
				usVPStart = ucMaxVP;
			else if(tempv < ucMinVP)
				usVPStart = ucMinVP;
			else
				usVPStart = tempv;
			//--------	DOS MODE(640X480) AUTO TUNE ISSUE -------------
			
			SetHP();
			SetVP();
			if(V_Active != V_ActiveTab[ucResolution]){
				bOptAbort = TRUE;
				bIsNonFullScreen = TRUE;
			}
		}
	}
	else{				// abort
		bOptAbort = TRUE;	

	}
}

void AutoClock(void)
{
unsigned char H_Difference,i,Compare;//,k;
//unsigned short PLL_Divider,V_Act;
unsigned short H_Ref,H_temp,H_Max;

	if ( bOptAbort == TRUE)
	return;
	H_Ref = H_ActiveTab[ucResolution];
//	V_Act = V_ActiveTab[ucResolution];
	H_Max = H_Ref << 1;
// Set refance H_Active
#ifdef R640_TUNE
	if(H_ActiveTab[ucResolution] == 640)
		WriteWordIIC560(GI_CLK_REF_LI,H_Ref<<1);
	else
#endif
	WriteWordIIC560(GI_CLK_REF_LI,H_Ref);
// read pll divider
	H_temp = usHTotal;
	if(usHTotal <= H_Ref){
		usHTotal = H_Ref + usHPStart;
		SetADC_PLL();
		if(bOutOfLimit == TRUE){
			bOptAbort = TRUE;
			return;
		}
	}

	for(i=0; i<0x20; i++){
		GetHmask();
		WriteIIC560(GI_AUTO_TUNE_CTRL,0x41);
	   	ucLoopTimer_10ms = 10;
	   	while((ReadIIC560(GI_AUTO_TUNE_CTRL) & BIT_0) && ucLoopTimer_10ms != 0){
			CheckModeChange();
			if(bOptAbort == TRUE)
				return;
		}
		if(ucLoopTimer_10ms == 0){
			bOptAbort = TRUE;
			return;
		}
		usActiveH = ReadWordIIC560(GI_POS_HWID_LI) & 0x0fff;
		H_Difference = ReadIIC560(GI_CLK_RESULT);
		Compare = (H_Difference & 0xc0) >> 6;
		H_Difference = H_Difference & 0x3f;
///		if((flag3 & BIT_2) != 0x00){	
///			printf("PLL_Divider = %d\r\n",PLL_Divider);
///			printf("H_Act = %d\r\n",usActiveH);
//			printf("H_Difference = %d\r\n",(unsigned short)H_Difference);
///		}
		if(Compare==0x00){
			break; //H_Ref=usActiveH
		}
		if(Compare==0x01){
//			if(H_Difference == 0x01)
//				break;
#ifdef R640_TUNE
			if(H_ActiveTab[ucResolution] == 640)
				usHTotal = usHTotal + (H_Difference >> 1);
			else
#endif
			usHTotal = usHTotal + H_Difference;
			if(usHTotal > H_Max){//2048
				i = 0xff;
				break;
			}
		}
		if(Compare > 0x01){
//			if(H_Difference == 0x01)
//				break;
#ifdef R640_TUNE
			if(H_ActiveTab[ucResolution] == 640)
				usHTotal = usHTotal - (H_Difference >> 1);
			else
#endif
			usHTotal = usHTotal - H_Difference;
			if(usHTotal < H_Ref){
				i = 0xff;
				break;
			}
		}
		SetADC_PLL();
		if(bOutOfLimit == TRUE ) { 
			bOptAbort = TRUE;
			return;
		}
	}
	if(i == 0xff){
		bIsNonFullScreen = TRUE;
		bOptAbort = TRUE;

	}
	else{
//#if 0
//		usHTotal = (usHTotal + 2) & 0xfffc;
//#else
//		usHTotal = (usHTotal + 1) & 0xfffe;
//#endif

//		printf("usHTotal = %d\r\n",usHTotal);
		if(ucModeNumber < NUMBER_OF_USER_MODE){		
			H_Ref = EEPROM_TimingTable[ucModeNumber].usHTotal;
//			if((H_ActiveTab[ucResolution] < 1280)&&(abs(usVSync - 600) < 12))
//			if(!((H_ActiveTab[ucResolution] > 1024)&&(abs(usVSync - 600) < 12))){
			if((H_ActiveTab[ucResolution] < 800)&&(V_ActiveTab[ucResolution] < 600)){
				if(abs(usHTotal-H_Ref) > 70){
//				if(usHTotal < H_Ref){
//					if((H_Ref - usHTotal) > 70){
						usHTotal = H_temp;
						SetADC_PLL();
						if(bOutOfLimit == TRUE){
							bOptAbort = TRUE;
							return;
						}
//					}
				}
			}
		}
	}
}

void AutoPhaseFineTune(void)
{
unsigned char   qq,yy,uu,i;//,value;
//unsigned short   zz;
xdata unsigned long   Phase_0, Phase_1, Phase_2, Phase_Pre3, Phase_Now3, Phase_Delta;

	if ( bOptAbort == TRUE )
		return;

//-------------------------at color xx , calculate phase-------------------------
	Phase_1 = 0x00000000;   // (i-1)
    Phase_2 = 0x00000000;   // (i-2)
    Phase_Pre3 = 0x00000000;   // (pre sum)->(delta)->(now sum)
    Phase_Delta = 0xffffffff;   // (min delta)
	qq = ucADCPhase;
	WriteIIC560(GI_AUTO_TUNE_CTRL,0x42); // 0x01 --> 0x09
   	ucLoopTimer_10ms = 10;
	for(yy=1; yy<ucPrevKey; yy++){

if (ucAutoPct<=100)

		while((ReadIIC560(GI_AUTO_TUNE_CTRL) & BIT_1) && ucLoopTimer_10ms != 0){
			CheckModeChange();
			if ( bOptAbort == TRUE )
				return;
		}

		ucADCPhase = (qq + yy) & 0x3f;
		SetADC_Phase();
		WriteIIC560(GI_AUTO_TUNE_CTRL,0x42); // 0x01 --> 0x09
	   	ucLoopTimer_10ms = 10;
		Phase_Now3 = ReadWordIIC560(GI_PHS_SDIFF_HI0);
		Phase_Now3 <<= 16;
		Phase_Now3 += ReadWordIIC560(GI_PHS_SDIFF_LI0);
		i = (ucADCPhase - 1) & 0x3f;

//		printf("Phase %d = %ld\r\n",(unsigned short)i,Phase_Now3);	

        Phase_2 = Phase_1;  // Shift	
        Phase_1 = Phase_0;
        Phase_0 = Phase_Now3;
		Phase_Now3 = (Phase_0>>2) + (Phase_1>>1) + (Phase_2>>2); // Phase_Now3
		if(yy < 4){
			Phase_Pre3  = Phase_Now3;   // Phase_Pre3 = Phase_Now3
		}
		else{
			if(Phase_Now3 > Phase_Pre3){
				Phase_Pre3  = Phase_Now3 - Phase_Pre3;
			}
			else{
				Phase_Pre3  = Phase_Pre3 - Phase_Now3;  // Phase_Pre3=delta
			}
			if(Phase_Pre3 < Phase_Delta){
				uu = i;           
				Phase_Delta = Phase_Pre3;
			}
			Phase_Pre3  = Phase_Now3;   // Phase_Pre3 = Phase_Now3
		}     
	}
	ucADCPhase = (uu - 2) & 0x3f;
	SetADC_Phase();

	//NVTprint1("Phase ok = %d\r\n",(unsigned short)ucADCPhase);

}


void SetADC_Offset(unsigned char OffSet)
{
unsigned char i,j,k,m,n,value;
xdata unsigned long PhaseResult,Temp;

	WriteIIC560(RGAIN_HI,MCU_DataMap[EPADDR_ADCR_GAIN]);
	WriteIIC560(GGAIN_HI,MCU_DataMap[EPADDR_ADCG_GAIN]);
	WriteIIC560(BGAIN_HI,MCU_DataMap[EPADDR_ADCB_GAIN]);

	SetADC_Offset_C();
	SetADC_Gain_C();
/*
	OffSet = ReadIIC560(ROFFSET);
	value = ReadIIC560(GOFFSET);
	if(OffSet > value)
		OffSet = value;
	value = ReadIIC560(BOFFSET);
	if(OffSet > value)
		OffSet = value;
*/
//	WriteIIC560(0x0f8,0x00);
	WriteIIC560(GAUGE_OFFSET,0x00);
	for(m=0; m<3; m++){
		i = 0x003 + m * 3;	//3,6,9
		OffSet = ReadIIC560(i);
//		for(k=OffSet; k<128; k=k+8){
		for(k=OffSet; k<248; k=k+8){
			WriteIIC560(GAUGE_CTRL,0x00);
			i = 0x003 + m * 3;	//3,6,9
//			WriteIIC560(i,k*2);
			WriteIIC560(i,k);
//			WaitSetup(2);
			ucLoopTimer_10ms = 10;
			i = 0x80 + (2-m)*0x08;
//			i = 0x80 + m * 0x08;	//
			WriteIIC560(GAUGE_CTRL,i);
		   	while((ReadIIC560(GAUGE_CTRL) & BIT_7) && ucLoopTimer_10ms != 0){
				CheckModeChange();
				if(bOptAbort == TRUE)
					return;
			}
			if(ucLoopTimer_10ms == 0){
				bOptAbort = TRUE;
				return;
			}
			j = 0;
			Temp = 0;
			for(i=0; i<8; i++){		// 2005-12-16 fine tune
				WriteIIC560(GAUGE_AREA_SEL,7-i);//i
				PhaseResult = ReadWordIIC560(GAUGE_RESULT_MI);
				PhaseResult <<= 8;
				value = ReadIIC560(GAUGE_RESULT_LI);
				PhaseResult += value;
//				printf("PhaseResult %x = %x %ld\r\n",(unsigned short)m,(unsigned short)k,PhaseResult);
/*				if(PhaseResult > Temp){
					Temp = PhaseResult;
					j = i;
				}*/
//				if(i==0 && PhaseResult == 0) break;	//B/W pattern
//				if(PhaseResult > (V_ActiveTab[ucResolution] * 10)){
				if(PhaseResult > (V_ActiveTab[ucResolution] * 3)){
					j = 0xff;
					break;
				}
			}
/*
			if(Temp > (V_ActiveTab[ucResolution] * 10)){
//			if(Temp > 80){
				i = 0x003 + m*3;
//				j = k*2+j;
				j = k+j;
				WriteIIC560(i,j);
				//printf("Offset %x = %x %d\r\n",(unsigned short)m,(unsigned short)k,(unsigned short)j);

				break;
			}*/
			if(j != 0) break;
		}
		//k=j;	// 2005-12-02	//2005-12-16 fine tune
//		if(k == 128){
		if(k == 248){
			bOptAbort = TRUE;
			return;
		}
		for(n=0; n<16; n++){	//2005-12-16 fine tune
			WriteIIC560(GAUGE_CTRL,0x00);
			i = 0x003 + 3 * m;
//			WriteIIC560(i,k*2+n);
			WriteIIC560(i,k+n);
//			WaitSetup(2);
			ucLoopTimer_10ms = 10;
			i = 0x80 + (2-m)*0x08;
//			i = 0x80 + m * 0x08;
			WriteIIC560(GAUGE_CTRL,i);
		   	while((ReadIIC560(GAUGE_CTRL) & BIT_7) && ucLoopTimer_10ms != 0){
				CheckModeChange();
				if(bOptAbort == TRUE)
					return;
			}
			if(ucLoopTimer_10ms == 0){
				bOptAbort = TRUE;
				return;
			}
			j = 0;
			Temp = 0;
/*
			for(i=0; i<8; i++){
				WriteIIC560(GAUGE_AREA_SEL,i);
				PhaseResult = ReadWordIIC560(GAUGE_RESULT_MI);
				PhaseResult <<= 8;
				value = ReadIIC560(GAUGE_RESULT_LI);
				PhaseResult += value;
//				printf("PhaseResult %x = %x %ld\r\n",(unsigned short)m,(unsigned short)n,PhaseResult);
				if(PhaseResult > Temp){
					Temp = PhaseResult;
					j = i;
					if(j != 0) break;
				}
			}
			if(j == 0){
				break;
			}
*/
				WriteIIC560(GAUGE_AREA_SEL,0);
				PhaseResult = ReadWordIIC560(GAUGE_RESULT_MI);
				PhaseResult <<= 8;
				value = ReadIIC560(GAUGE_RESULT_LI);
				PhaseResult += value;
//				printf("PhaseResult %x = %x %ld\r\n",(unsigned short)m,(unsigned short)n,PhaseResult);
				if(PhaseResult > (V_ActiveTab[ucResolution] * 10)){
					break;
				}


		}
		i = 0x003 + 3 * m;
//		j = k*2+n;
		j = k+n;
		WriteIIC560(i,j);
		//printf("Offset %x = %x %d\r\n",(unsigned short)m,(unsigned short)k,(unsigned short)j);

	}

	// + black will be blacker

#ifdef MODE_OFFSET
#if PanelSxga == 1
	if ( H_ActiveTab[ucResolution] < 1280 )
#else
	if ( H_ActiveTab[ucResolution] < 1024 )
#endif
	{
		ucR_ADC_Offset = ReadIIC560(ROFFSET)+5;
		ucG_ADC_Offset = ReadIIC560(GOFFSET)+5;
		ucB_ADC_Offset = ReadIIC560(BOFFSET)+5;
		bOffsetDown = 1;
	}
	else
	{
//printf("AutoColor: Native Offset+8\r\n");
		ucR_ADC_Offset = ReadIIC560(ROFFSET)+8;
		ucG_ADC_Offset = ReadIIC560(GOFFSET)+8;
		ucB_ADC_Offset = ReadIIC560(BOFFSET)+8;
		bOffsetDown = 0;
	}
	Write24C16(EPADDR_OFFSETDOWN, bOffsetDown);
#else
#if PanelID == AUO_M220EW01_V0
	#define ADC_Offset2 4
#else
	#define ADC_Offset2 4
#endif
		ucR_ADC_Offset = ReadIIC560(ROFFSET)+ADC_Offset2;
		ucG_ADC_Offset = ReadIIC560(GOFFSET)+ADC_Offset2;//+5;	// Solve the green-ish issue over gray level pattern // Jude 2007/05/16
		ucB_ADC_Offset = ReadIIC560(BOFFSET)+ADC_Offset2;
#endif


	UpdateADCOffset();
}

void SetADC_Gain(unsigned char OffSet)
{
unsigned char i,j,k,m,n,value;
xdata unsigned long PhaseResult,Temp;

//	SetADC_Gain_C();
/*	OffSet = ReadIIC560(RGAIN_HI);
	value = ReadIIC560(GGAIN_HI);
	if(OffSet < value)
		OffSet = value;
	value = ReadIIC560(BGAIN_HI);
	if(OffSet < value)
		OffSet = value;
*/
//	WriteIIC560(0x0f8,0x00);
	WriteIIC560(GAUGE_OFFSET,0xf8);
	for(m=0; m<3; m++){
		i = 0x001 + m * 3;	//1,4,7
		OffSet = ReadIIC560(i);
		for(k=OffSet; k>7; k=k-8){
			WriteIIC560(GAUGE_CTRL,0x00);
			i = 0x001 + m * 3;	//1,4,7
			WriteIIC560(i,k);
//			WaitSetup(2);
			ucLoopTimer_10ms = 10;
			i = 0x80 + (2-m)*0x08;
//			i = 0x80 + m * 0x08;
			WriteIIC560(GAUGE_CTRL,i);
		   	while((ReadIIC560(GAUGE_CTRL) & BIT_7) && ucLoopTimer_10ms != 0){
				CheckModeChange();
				if ( bOptAbort == TRUE )
					return;
			}
			if(ucLoopTimer_10ms == 0){
				bOptAbort = TRUE;
				return;
			}
			j = 0;
			Temp = 0;
			for(i=0; i<8; i++){
				WriteIIC560(GAUGE_AREA_SEL,i);
				PhaseResult = ReadWordIIC560(GAUGE_RESULT_MI);
				PhaseResult <<= 8;
				value = ReadIIC560(GAUGE_RESULT_LI);
				PhaseResult += value;
//				//printf("PhaseResult %x = %x %ld\r\n",(unsigned short)m,(unsigned short)k,(PhaseResult));
/*				if(PhaseResult > Temp){
					Temp = PhaseResult;
					j = i;
				}*/
				if(PhaseResult > (V_ActiveTab[ucResolution] * 3)){
					j = 0xff;
					break;
				}
			}
/*			if(Temp > 0){
				i = 0x001 + m * 3;	//1,4,7
				j = k+j;

				//printf("Gain %x = %x %x\r\n",(unsigned short)m,(unsigned short)k,(unsigned short)j);
				break;
			}*/
			if(j != 0) break;
		}
		if(k == 0){
			bOptAbort = TRUE;
			return;
		}
		for(n=0; n<16; n++){
			WriteIIC560(GAUGE_CTRL,0x00);
			i = 0x001 + m * 3;	//1,4,7
			WriteIIC560(i,k-n);
//			WaitSetup(2);
			ucLoopTimer_10ms = 10;
			i = 0x80 + (2-m)*0x08;
//			i = 0x80 + m * 0x08;
			WriteIIC560(GAUGE_CTRL,i);
		   	while((ReadIIC560(GAUGE_CTRL) & BIT_7) && ucLoopTimer_10ms != 0){
				CheckModeChange();
				if(bOptAbort == TRUE)
					return;
			}
			if(ucLoopTimer_10ms == 0){
				bOptAbort = TRUE;
				return;
			}
			j = 0;
			Temp = 0;
			WriteIIC560(GAUGE_AREA_SEL,7);
			PhaseResult = ReadWordIIC560(GAUGE_RESULT_MI);
			PhaseResult <<= 8;
			value = ReadIIC560(GAUGE_RESULT_LI);
			PhaseResult += value;
//			printf("PhaseResult %x = %x %ld\r\n",(unsigned short)m,(unsigned short)n,(PhaseResult);
			if(PhaseResult > (V_ActiveTab[ucResolution] * 10)){//80
				break;
			}

		}		
		i = 0x001 + m * 3;	//1,4,7
		j = k-n;
		WriteIIC560(i,j);
		//printf("Gain %x = %x %x\r\n",(unsigned short)m,(unsigned short)k,(unsigned short)j);

	}
	// + all color will be darker;
#if PanelID==LPL_LM220WE1
	ucR_ADC_Gain = ReadIIC560(RGAIN_HI);//-4;		
	ucG_ADC_Gain = ReadIIC560(GGAIN_HI)-2;//-4;
	ucB_ADC_Gain = ReadIIC560(BGAIN_HI)+2;//-4;
#else
	ucR_ADC_Gain = ReadIIC560(RGAIN_HI);//-4;		
	ucG_ADC_Gain = ReadIIC560(GGAIN_HI);//-4;
	ucB_ADC_Gain = ReadIIC560(BGAIN_HI);//-4;
#endif

	WriteIIC560(RGAIN_HI,ucR_ADC_Gain);
	WriteIIC560(GGAIN_HI,ucG_ADC_Gain);
	WriteIIC560(BGAIN_HI,ucB_ADC_Gain);
	Write24C16(EPADDR_ADCR_GAIN,ucR_ADC_Gain);//0x4d = ADC r gain
	Write24C16(EPADDR_ADCG_GAIN,ucG_ADC_Gain);//0x4e = ADC g gain
	Write24C16(EPADDR_ADCB_GAIN,ucB_ADC_Gain);//0x4f = ADC b gain
}


bit AutoColor(void)
{
unsigned char Reg0x06A;
	if(ucSignalType == sigDVI) return FALSE;

//	OSD_OFF();	// close before auto tuning color
	
//	ucBlackLevel = MCU_DataMap[EPADDR_SCALER_OFFSET];	
//	SetScalerOffset();
//	Write24C16(EPADDR_SCALER_OFFSET, ucBlackLevel);

	Reg0x06A = ReadIIC560(JITTER_CTRL);
	WriteIIC560(JITTER_CTRL,0x00);	//Analog de-jitter // Jude 2005/04/06
	bOptAbort = FALSE;
	WriteWordIIC560(GI_CAP_HBEG_LI,usHPStart - 20);

	SetADC_Offset(0x30);

/*
	if (bOptAbort ==TRUE) {
		goto Error;
	}
	WriteWordIIC560(GI_CAP_HBEG_LI,usHPStart);
	SetADC_Gain(0xf0);
Error:
	if ( bOptAbort == TRUE ) {
		LoadADC_Gain();
	}
	WriteIIC560(JITTER_CTRL,Reg0x06A);	//Analog de-jitter	
*/	

	if(!bOptAbort){
		//WriteWordIIC560(GI_CAP_HBEG_LI,usHPStart);
		SetHP();
		SetADC_Gain(0xf0);
	}
	//else	// bOptAbort==TRUE
	
	if(bOptAbort){
		LoadADC_Gain();
	}
	WriteIIC560(JITTER_CTRL,Reg0x06A);	//Analog de-jitter
#if FE2P_LIB==ON
		FE2P_Process(1);	
#endif
	
	return !bOptAbort;
}


//////////////////////////////////////////////////////////////////////////////
void AutoClockByPhase(bit h)
{
unsigned char k,templ,temph;
unsigned short GoodDotClk,PoorDotClk;
xdata unsigned long MaxMin,Value,minMaxMin;

	if((ucModeNumber < NUMBER_OF_USER_MODE)&&(h == 1)){
//		usHTotal = EEPROM_TimingTable[(unsigned short)ucModeNumber].usHTotal;
		GoodDotClk = usHTotal;
		usHTotal = EEPROM_TimingTable[(unsigned short)ucModeNumber].usHTotal;
		if(usHTotal < H_ActiveTab[ucResolution])
			usHTotal = GoodDotClk;
	}

	GoodDotClk = usHTotal;
	PoorDotClk = usHTotal;
	MaxMin = 0;
	minMaxMin = 0xffffffff;
	usHTotal -= 2;	//2005-05-25 mingyu: reduce fine tune time change to 2 times from 5 times
	for(k=0; k<5; k++){
		SetADC_PLL();
//		WaitSetup(4);
		if ( bOptAbort == TRUE )
			return;
		Value = CheckPhaseData();
		if ( bOptAbort == TRUE )
			return;
		if(MaxMin < Value){
			GoodDotClk = usHTotal;
			MaxMin = Value;
			templ = TempValue;
			temph = TempData;
		}
		if(minMaxMin > Value){
			minMaxMin = Value;
			PoorDotClk = usHTotal;
		}
		usHTotal ++;
	}

	usHTotal = GoodDotClk;
	if(abs(GoodDotClk - PoorDotClk) != 1)
		usHTotal &= 0xfffe;
	SetADC_PLL();
	
#if 1	// 2005-12-01
	//Value = (unsigned long)H_ActiveTab[ucResolution] * V_ActiveTab[ucResolution] * 256;
	Value = (unsigned long)H_ActiveTab[ucResolution] * V_ActiveTab[ucResolution] *64;  // V028, FIND BEST IN PAT-1
//printf("Value=%ld\r\n", Value);
//printf("MaxMin=%ld\r\n", MaxMin);
	if(MaxMin < Value){
		ucADCPhase = (templ + 24) & 0x3f;
		ucPrevKey = 32;
		//printf("REVERSE 180\r\n");
	}
	else{
		ucADCPhase = (temph - 8) & 0x3f;
		ucPrevKey = 16;
		//printf("FIND BEST PHASE\r\n");
	}
#else
	ucADCPhase = (temph - 8) & 0x3f;
	ucPrevKey = 16;
#endif
/*
	ucADCPhase = (templ + 24) & 0x3f;
	ucPrevKey = 32;
*/
	SetADC_Phase();
	//NVTprint1("MinPhase = %d\r\n",(unsigned short)templ);
	//NVTprint1("MaxPhase = %d\r\n",(unsigned short)temph);
	//NVTprint1("usHTotal = %d\r\n",usHTotal);

}

unsigned long CheckPhaseData(void)
{
xdata unsigned long Value,MinValueTemp,MaxValueTemp;
	MaxValueTemp = 0;
	MinValueTemp = 0xffffffff;
	ucADCPhase = 0;
	SetADC_Phase();
//	Sleep(5);
	WriteIIC560(GI_AUTO_TUNE_CTRL,0x42); // 0x01 --> 0x09
   	ucLoopTimer_10ms = 10;
	for(ucADCPhase=4; ucADCPhase<0x42; ucADCPhase = ucADCPhase + 4){


		while((ReadIIC560(GI_AUTO_TUNE_CTRL) & BIT_1) && ucLoopTimer_10ms != 0){
			CheckModeChange();
			if ( bOptAbort == TRUE )
				return 0;
		}
		SetADC_Phase();
		WriteIIC560(GI_AUTO_TUNE_CTRL,0x42);
	   	ucLoopTimer_10ms = 10;
		Value = ReadWordIIC560(GI_PHS_SDIFF_HI0);
		Value <<= 16;
		Value += ReadWordIIC560(GI_PHS_SDIFF_LI0);
		if(Value < MinValueTemp){
			MinValueTemp = Value;
			TempValue = (ucADCPhase - 4) & 0x3f;
		}
		if(Value > MaxValueTemp){
			MaxValueTemp = Value;
			TempData = (ucADCPhase - 4) & 0x3f;
		}
	}

	Value = MaxValueTemp - MinValueTemp;

//	printf("usHTotal = %d\r\n",usHTotal);
//	printf("MaxMin = %ld\r\n",Value);

	return Value;
}

bit FindOffset()
{
	ucLoopTimer_10ms = 100;
		WriteIIC560(GI_AUTO_TUNE_CTRL,0x6a);	//minimum value
	   	while((ReadIIC560(GI_AUTO_TUNE_CTRL) & BIT_1) && ucLoopTimer_10ms != 0){
			CheckModeChange();
			if ( bOptAbort == TRUE )
				return 0;
		}
	return 1;
}

void UpdateADCOffset()
{	
	WriteIIC560(ROFFSET, ucR_ADC_Offset);
	WriteIIC560(GOFFSET, ucG_ADC_Offset);
	WriteIIC560(BOFFSET, ucB_ADC_Offset);
	
	Write24C16(EPADDR_ADCR_OFFSET, ucR_ADC_Offset);//0x4a = ADC r offset
	if(ucSignalType == sigSOG)
		Write24C16(EPADDR_ADCG_OFFSET, ucG_ADC_Offset+5);//0x4b = ADC g offset
	else
		Write24C16(EPADDR_ADCG_OFFSET, ucG_ADC_Offset);//0x4b = ADC g offset
	Write24C16(EPADDR_ADCB_OFFSET, ucB_ADC_Offset);//0x4c = ADC b offset
//printf("offset:r=%d,g=%d,b=%d\r\n", (unsigned short)r_offset,(unsigned short)g_offset,(unsigned short)b_offset);

}

#ifdef AUTO_OFFSET
void AutoOffsetExit()
{
	UpdateADCOffset();
	
	WriteIIC560(NR_CTRL,regNR1);
	WriteIIC560(NR_THR_CTRL1,regNR2);
	WriteIIC560(JITTER_CTRL,regNR3);			//Analog de-jitter
	WriteIIC560(NR_THR_CTRL2,regNR4);		//Analog de-jitter
	
	WriteIIC560(ADC_BW_CTRL,0x06);
}


void SetADC_AutoOffset(void)
{
#define OFFSET1(x) (x-40)
#define OFFSET2(x) (x-80)
#define OFFSET_DIFF 40
//unsigned char r,g,b,		// original RGB
unsigned char	r1,g1,b1,		// RGB from Offset-40
                     r2,g2,b2;		// RGB from Offset-80

//unsigned char r_offset=0, g_offset=0, b_offset=0;
float temp_offset;

	WriteIIC560(ADC_BW_CTRL,0x00);
                     
	regNR1 = ReadIIC560(NR_CTRL);
	regNR2 = ReadIIC560(NR_THR_CTRL1);
	regNR3 = ReadIIC560(JITTER_CTRL);
	regNR4 = ReadIIC560(NR_THR_CTRL2);
	
	WriteIIC560(NR_CTRL,0x3a);
	WriteIIC560(NR_THR_CTRL1,0xee);
	WriteIIC560(JITTER_CTRL,0x00);			//Analog de-jitter
	WriteIIC560(NR_THR_CTRL2,0x0e);		//Analog de-jitter
	
	ucR_ADC_Offset = ReadIIC560(ROFFSET);
	ucG_ADC_Offset = ReadIIC560(GOFFSET);
	ucB_ADC_Offset = ReadIIC560(BOFFSET);

       
//printf("offset:r=%d,g=%d,b=%d\r\n", (unsigned short)r,(unsigned short)g,(unsigned short)b);
	//--------------------------------------------
	//	1ST: OFFSET-40
	//--------------------------------------------
	WriteIIC560(ROFFSET, OFFSET1(ucR_ADC_Offset));
	WriteIIC560(GOFFSET, OFFSET1(ucG_ADC_Offset));
	WriteIIC560(BOFFSET, OFFSET1(ucB_ADC_Offset));
	
	if ( FindOffset() == 0 )
	{
		AutoOffsetExit();
		return;
	}
	
	r1 = ReadIIC560(GI_PHS_SDIFF_LI0);
	g1 = ReadIIC560(GI_PHS_SDIFF_LI1);
	b1 = ReadIIC560(GI_PHS_SDIFF_HI0);
//printf("%d,%d,%d\r\n", (unsigned short)r1, (unsigned short)g1, (unsigned short)b1);
	//--------------------------------------------
	//	2ND: OFFSET-80
	//--------------------------------------------
	WriteIIC560(ROFFSET, OFFSET2(ucR_ADC_Offset));
	WriteIIC560(GOFFSET, OFFSET2(ucG_ADC_Offset));
	WriteIIC560(BOFFSET, OFFSET2(ucB_ADC_Offset));
	
	if ( FindOffset() == 0 )
	{
		AutoOffsetExit();
		return;
	}
	
	r2 = ReadIIC560(GI_PHS_SDIFF_LI0);
	g2 = ReadIIC560(GI_PHS_SDIFF_LI1);
	b2 = ReadIIC560(GI_PHS_SDIFF_HI0);
//printf("%d,%d,%d\r\n", (unsigned short)r2, (unsigned short)g2, (unsigned short)b2);

	temp_offset = ((float)(OFFSET_DIFF)/(r2-r1)+(float)(OFFSET_DIFF)/(g2-g1)+(float)(OFFSET_DIFF)/(b2-b1))/3;
	if ( (temp_offset < 8 ) && (r1!=0 &&  g1!=0 && b1!=0 &&  r2!=0 &&  g2!=0 &&  b2!=0))
	{
//printf("%d\r\n",(unsigned short) temp_offset);
	/*
		r_offset = OFFSET1(r) + (r1+4)*(float)(OFFSET1(r)-OFFSET2(r))/(r2-r1)+0.5;
		g_offset = OFFSET1(g) + (g1+4)*(float)(OFFSET1(g)-OFFSET2(g))/(g2-g1)+0.5;
		b_offset = OFFSET1(b) + (b1+4)*(float)(OFFSET1(b)-OFFSET2(b))/(b2-b1)+0.5;
	*/
		ucR_ADC_Offset = OFFSET1(ucR_ADC_Offset) + (r1+6)*temp_offset+0.5;
		ucG_ADC_Offset = OFFSET1(ucG_ADC_Offset) + (g1+6)*temp_offset+0.5;
		ucB_ADC_Offset = OFFSET1(ucB_ADC_Offset) + (b1+6)*temp_offset+0.5;
	
	}
	
	AutoOffsetExit();
	
}
#endif


void SetADC_Offset_C(void)
{
#define MaxBlackOffset 10//8//6
#define MinBlackOffset 5//3//1
unsigned char i,k,value,rgb[3];
	rgb[0] = ReadIIC560(ROFFSET);
	rgb[1] = ReadIIC560(GOFFSET);
	rgb[2] = ReadIIC560(BOFFSET);

	for(k=32; k<240; k++){
		
		if(FindOffset() == 0) return;
		
//		printf("\r\n");
//		printf("r = %d\r\n", (unsigned short)rgb[0]);
//		printf("g = %d\r\n", (unsigned short)rgb[1]);
//		printf("b = %d\r\n", (unsigned short)rgb[2]);
		i = 0;
		value = ReadIIC560(GI_PHS_SDIFF_LI0);
//		printf("GI_PHS_SDIFF_LI0 = %d\r\n", (unsigned short)value);
		if((value < MinBlackOffset) && (rgb[0] > 8)){	// >0
			rgb[0] -= (MinBlackOffset-value);//2;
			i = 0xff;
		}
		if((value > MaxBlackOffset) && (rgb[0] < 248)){	// < 0x7f
			rgb[0] += (value - MaxBlackOffset);//2;
			i = 0xff;
		}
		value = ReadIIC560(GI_PHS_SDIFF_LI1);
//		printf("GI_PHS_SDIFF_LI1 = %d\r\n", (unsigned short)value);
		if((value < MinBlackOffset) && (rgb[1] > 8)){	// >0
			rgb[1] -= (MinBlackOffset-value);//2;
			i = 0xff;
		}
		if((value > MaxBlackOffset) && (rgb[1] < 248)){	// < 0x7F
			rgb[1] += (value - MaxBlackOffset);//2;
			i = 0xff;
		}
		value = ReadIIC560(GI_PHS_SDIFF_HI0);
//		printf("GI_PHS_SDIFF_HI0 = %d\r\n", (unsigned short)value);
		if((value < MinBlackOffset) && (rgb[2] > 8)){	// >0
			rgb[2] -= (MinBlackOffset-value);//2;
			i = 0xff;
		}
		if((value > MaxBlackOffset) && (rgb[2] < 248)){   // < 0x7f
			rgb[2] += (value - MaxBlackOffset);//2;
			i = 0xff;
		}
		if(i == 0){
			break;
		}
		else{
			WriteIIC560(ROFFSET,rgb[0]);
			WriteIIC560(GOFFSET,rgb[1]);
			WriteIIC560(BOFFSET,rgb[2]);
		}
	}

}

void SetADC_Gain_C(void)
{
#define MaxWhiteGain 0xf8//0xfa//0xfe
#define MinWhiteGain 0xf0//0xf2//0xf9

unsigned char i,k,value,rgb[3];

	rgb[0] = ReadIIC560(RGAIN_HI);
	rgb[1] = ReadIIC560(GGAIN_HI);
	rgb[2] = ReadIIC560(BGAIN_HI);

	for(k=0; k<128; k++){
		ucLoopTimer_10ms = 100;
		WriteIIC560(GI_AUTO_TUNE_CTRL,0x6e);
	   	while((ReadIIC560(GI_AUTO_TUNE_CTRL) & BIT_1) && ucLoopTimer_10ms != 0){
			CheckModeChange();
			if(bOptAbort == TRUE)
				return;
		}
//		printf("\r\n");
//		printf("r = %d\r\n", (unsigned short)rgb[0]);
//		printf("g = %d\r\n", (unsigned short)rgb[1]);
//		printf("b = %d\r\n", (unsigned short)rgb[2]);
		i = 0;
		value = ReadIIC560(GI_PHS_SDIFF_LI0);
//		printf("GI_PHS_SDIFF_LI0 = %d\r\n", (unsigned short)value);
		if((value < MinWhiteGain) && (rgb[0] > 8)){	// >0
			rgb[0] -= (MinWhiteGain-value);//2;
			i = 0xff;
		}
		if((value > MaxWhiteGain) && (rgb[0] < 248)){	// < 0xff
			rgb[0] += (value-MaxWhiteGain);//2;
			i = 0xff;
		}
		value = ReadIIC560(GI_PHS_SDIFF_LI1);
//		printf("GI_PHS_SDIFF_LI1 = %d\r\n", (unsigned short)value);
		if((value < MinWhiteGain) && (rgb[1] > 8)){
			rgb[1] -= (MinWhiteGain-value);//2;
			i = 0xff;
		}
		if((value > MaxWhiteGain) && (rgb[1] < 248)){
			rgb[1] += (value-MaxWhiteGain);//2;
			i = 0xff;
		}
		value = ReadIIC560(GI_PHS_SDIFF_HI0);
//		printf("GI_PHS_SDIFF_HI0 = %d\r\n", (unsigned short)value);
		if((value < MinWhiteGain) && (rgb[2] > 8)){
			rgb[2] -= (MinWhiteGain-value);//2;
			i = 0xff;
		}
		if((value > MaxWhiteGain) && (rgb[2] < 248)){
			rgb[2] += (value-MaxWhiteGain);//2;
			i = 0xff;
		}
		if(i == 0){
			break;
		}
		else{
			WriteIIC560(RGAIN_HI,rgb[0]);
			WriteIIC560(GGAIN_HI,rgb[1]);
			WriteIIC560(BGAIN_HI,rgb[2]);
//			Sleep(10);
		}
	}

}


void CheckClock(void)
{
unsigned char H_Difference,Compare,i;
unsigned short H_Ref,H_MAX;
unsigned long TempPhase,ScreenPixel;

	bOptAbort = FALSE;
	H_Ref = H_ActiveTab[ucResolution];
//	V_Act = V_ActiveTab[ucResolution];
	H_MAX = H_Ref << 1;
	H_MAX += H_Ref;
	ScreenPixel = (unsigned long)H_ActiveTab[ucResolution] * V_ActiveTab[ucResolution];
//	printf("Check Resolution = %d x %d\r\n",H_ActiveTab[ucResolution],V_ActiveTab[ucResolution]);
// Set refance H_Active
	WriteWordIIC560(GI_CLK_REF_LI,H_Ref);
//	printf("Check %d\r\n",H_Ref);

	WriteIIC560(GI_AUTO_TUNE_CTRL,0x41);
   	ucLoopTimer_10ms = 10;
   	while((ReadIIC560(GI_AUTO_TUNE_CTRL) & BIT_0) && ucLoopTimer_10ms != 0){
		CheckModeChange();
		if(bOptAbort == TRUE)
			return;
	}
	if(ucLoopTimer_10ms == 0){
		bOptAbort = TRUE;
		return;
	}
	usActiveH = ReadWordIIC560(GI_POS_HWID_LI) & 0x0fff;
	H_Difference = ReadIIC560(GI_CLK_RESULT);
	Compare = (H_Difference & 0xc0) >> 6;
	H_Difference = H_Difference & 0x3f;
//	printf("usHTotal = %d\r\n",usHTotal);
//	printf("H_Act = %d\r\n",usActiveH);
//	printf("H_Difference = %d\r\n",(unsigned short)H_Difference);
	if(abs(usActiveH-H_Ref) > 48){	//32
		bAutoClockResult = FALSE;
//		printf("Clock Fail\r\n");

		WriteIIC560(GI_AUTO_TUNE_CTRL,0x42); // 0x01 --> 0x09
	   	ucLoopTimer_10ms = 10;
		while((ReadIIC560(GI_AUTO_TUNE_CTRL) & BIT_1) && ucLoopTimer_10ms != 0){
			CheckModeChange();
			if(bOptAbort == TRUE)
				return;
		}
		TempPhase = ReadWordIIC560(GI_PHS_SDIFF_HI0);
		TempPhase <<= 16;
		TempPhase += ReadWordIIC560(GI_PHS_SDIFF_LI0);
//		printf("Phase %ld %ld\r\n",TempPhase,ScreenPixel);	
//		if(TempPhase < ScreenPixel){
		if(TempPhase < (ScreenPixel >> 3)){
			bOptAbort = TRUE;
//			printf("bOptAbort\r\n");	
		}
	}
	else{
		for(i=0; i<0x20; i++){
			GetHmask();
			WriteIIC560(GI_AUTO_TUNE_CTRL,0x41);
		   	ucLoopTimer_10ms = 10;
		   	while((ReadIIC560(GI_AUTO_TUNE_CTRL) & BIT_0) && ucLoopTimer_10ms != 0){
				CheckModeChange();
				if(bOptAbort == TRUE)
					return;
			}
			if(ucLoopTimer_10ms == 0){
				bOptAbort = TRUE;
				return;
			}
			usActiveH = ReadWordIIC560(GI_POS_HWID_LI) & 0x0fff;
			H_Difference = ReadIIC560(GI_CLK_RESULT);
			Compare = (H_Difference & 0xc0) >> 6;
			H_Difference = H_Difference & 0x3f;
//			printf("usHTotal = %d\r\n",usHTotal);
//			printf("H_Act = %d\r\n",usActiveH);
//			printf("H_Difference = %d\r\n",(unsigned short)H_Difference);
			if(Compare==0x00){
				break; //H_Ref=usActiveH
			}
			if(Compare==0x01){
				usHTotal = usHTotal + H_Difference;
				if(usHTotal > H_MAX){	//4096 //2048
					i = 0xff;
					break;
				}
			}
			if(Compare > 0x01){
				usHTotal = usHTotal - H_Difference;
				if(usHTotal < H_Ref){
					i = 0xff;
					break;
				}
			}
			SetADC_PLL();
			if(bOutOfLimit == TRUE){ 
				bOptAbort = TRUE;
				return;
			}
		}
		if(i == 0xff)
			bAutoClockResult = FALSE;
		else
			bAutoClockResult = TRUE;
//		printf("Clock OK\r\n");
	}
}

float CheckPhase(void)
{
xdata unsigned long Phase_Now;
xdata float Phase_average;
xdata unsigned short H_Width,V_High;

//	printf("CheckPhase\r\n");
	H_Width = ReadWordIIC560(GI_POS_HWID_LI) & 0x0fff;
	V_High = ReadWordIIC560(GI_POS_VLEN_LI) & 0x0fff;
	Phase_Now = CheckPhaseData();
//	printf("Phase %ld\r\n",Phase_Now);
	Phase_average = (float)Phase_Now / H_Width / V_High;
//	printf("Phase_average = %f\r\n",Phase_average);
	return Phase_average;
}

#ifdef __CHECK_RESOLUTION__
void CheckResolution(void)
{
code unsigned char ResolutionTab[]={
	R1024x768,R1280x768,R1280x768,R1360x768,R960x720,R1280x720,R1680x1050,R1680x1050
};

code unsigned short HTotalTab60Hz[]={
//	1024 1280 1280 1360  960 1280  1680  1680
	1344,1440,1644,1792,1288,1664,1840,2240
};
code unsigned short HTotalTab70Hz[]={
//	1024 1280 1280 1360
	1328,1696,1696,1808,
};
code unsigned short HTotalTab72Hz[]={
//	1024 1280 1280 1360
	1360,1696,1696,1808,
};
code unsigned short HTotalTab75Hz[]={
//	1024 1280 1280 1360  960 1280  1680
	1312,1696,1696,1808,1284,1696,2272
};
code unsigned short HTotalTab85Hz[]={
//	1024 1280 1280 1360
	1376,1712,1712,1808,
};
unsigned char Resolution,i,ResolutionBak;
xdata float maxPhase,temp_phase;
unsigned short HTotal_temp;//,Min_Dif,HTotal_Dif;
unsigned char min,max;
	maxPhase = 0;
	HTotal_temp = usHTotal;
	if((ucResolution == R1024x768)||(ucResolution == R1280x768)||(ucResolution == R1360x768)||
	   (ucResolution == R1400x1050)||
	   (ucResolution == R1680x1050)||
	   (ucResolution == R960x720)||
	   (ucResolution == R1280x720)){	//H/V, H+V, SOG
		
		if ((ucResolution == R1280x720) || (ucResolution == R960x720)){
			if ((usVSync > 590) && (usVSync < 610)){
				min = 4;
				max = 6;
			}
			else if ((usVSync > 740) && (usVSync < 760)){
				min = 4;
				max = 6;
			}
			else return;

			Resolution = R960x720;
		}
		else if ((ucResolution == R1680x1050) || (ucResolution == R1400x1050)){
			if ((usVSync > 590) && (usVSync < 610)){
				min = 6;
				max = 8;
			}
			else if ((usVSync > 740) && (usVSync < 760)){
				min = 6;
				max = 8;
			}
			else 
				return;
			Resolution = R1680x1050;
		}
		else{
			min = 0;
			max = 4;
			Resolution = R1024x768;
		}

		ResolutionBak = ucResolution;
		bBGMode = TRUE;
		for(i=min; i<max; i++){
			if((abs(usVSync-600) > 10)&&(i == 1)){
				i++;
			}
//			printf("i=%d\r\n",(unsigned short)i);
			ucResolution = ResolutionTab[i];
			if(usVSync < 650)
				usHTotal = HTotalTab60Hz[i];
			else if(usVSync < 710)
				usHTotal = HTotalTab70Hz[i];
			else if(usVSync < 735)
				usHTotal = HTotalTab72Hz[i];
			else if(usVSync < 800)
				usHTotal = HTotalTab75Hz[i];
			else
				usHTotal = HTotalTab85Hz[i];
			SetADC_PLL();
//			WriteWordIIC560(GI_CAP_VLEN_LI,V_ActiveTab[ucResolution]);		// Capture V_Active
//			WriteWordIIC560(GI_CAP_HWID_LI,H_ActiveTab[ucResolution]);		// Capture H_Active
			ucMinVP = 0;
			ucVPOffset = 0;
			SetScaler();
			bOptAbort = FALSE;
			AutoPosition();
			CheckClock();
			if(bOptAbort == TRUE) break;
			if(bAutoClockResult == TRUE){
				temp_phase = CheckPhase();
				if(bOptAbort == TRUE) break;
				if(maxPhase < temp_phase){
					maxPhase = temp_phase;
					HTotal_temp = usHTotal;
					Resolution = ResolutionTab[i];
//					printf("Resolution %d\r\n",(unsigned short)Resolution);
//					printf("usHTotal %d\r\n",(unsigned short)HTotal_temp);
				}
			}
		}
		ucResolution = Resolution;
//		min = ucModeNumber;
//		Min_Dif = 0xffff;
		if((ucResolution != ResolutionBak)&&(bOptAbort == FALSE)){
/*			for(ucModeNumber=0; ucModeNumber<NUMBER_OF_USER_MODE; ucModeNumber++){
				ucResolution = EEPROM_TimingTable[ucModeNumber].ucResolution;
				if(Resolution == ucResolution){
					usHTotal = EEPROM_TimingTable[ucModeNumber].usHTotal;
					HTotal_Dif = abs(usHTotal - HTotal_temp);
					if(Min_Dif > HTotal_Dif){
						Min_Dif = HTotal_Dif;
						min = ucModeNumber;
					}
				}
			}
			ucModeNumber = min;
		}*/
			usHTotal = HTotal_temp;
			HTotal_temp = (unsigned short)((float)H_ActiveTab[ucResolution] * 1.05); 
			if(usHTotal < HTotal_temp)
				usHTotal = HTotal_temp;
			Write24C16(NVRAM_RESOLU(ucModeNumber), Resolution);
			Write24C16_Short(NVRAM_HTOTAL(ucModeNumber), usHTotal);
			SetADC_PLL();
			ucMinVP = 0;
			ucVPOffset = 0;
			SetScaler();
//			printf("ModeNumberx1 %d\r\n",(unsigned short)ucModeNumber);
//			printf("Resolutionx1 %d\r\n",(unsigned short)ucResolution);
		}
		else{
			LoadModeDependentSettings();
			SetADC_PLL();
			SetScaler();
//			printf("ModeNumberx2 %d\r\n",(unsigned short)ucModeNumber);
//			printf("Resolutionx2 %d\r\n",(unsigned short)ucResolution);
		}
		bBGMode = FALSE;
	}
}
#endif
#if 0
void AutoDelay(void)
{
unsigned char Reg0x0d9,k,d;
unsigned long temp1,temp2;
	Reg0x0d9 = ReadIIC560(HPLL_PHASE_CTRL1) & 0x3f;
	WriteIIC560(HPLL_PHASE_CTRL1,Reg0x0d9);
	k = 0;
	temp2 = 0;
	for(d=0; d<0x10; d++){
		WriteIIC560(HPLL_PHASE_CTRL2,d);
		WriteIIC560(GI_AUTO_TUNE_CTRL,0x42);
		ucLoopTimer_10ms = 10;
		while((ReadIIC560(GI_AUTO_TUNE_CTRL) & BIT_1) && ucLoopTimer_10ms != 0){
			CheckModeChange();
			if(bOptAbort == TRUE )
				return;
		}
		temp1 = ReadWordIIC560(GI_PHS_SDIFF_HI0);
		temp1 <<= 16;
		temp1 += ReadWordIIC560(GI_PHS_SDIFF_LI0);
		printf("%d %ld\r\n",(unsigned short)d,temp1);
		if(temp2 < temp1){
			temp2 = temp1;
			k = d;
		}
	}
	WriteIIC560(HPLL_PHASE_CTRL2,0);//k;
	printf("r=%d\r\n",(unsigned short)k);

	WriteIIC560(HPLL_PHASE_CTRL1,(Reg0x0d9 | BIT_6));
	k = 0;
	temp2 = 0;
	for(d=0; d<0x10; d++){
		WriteIIC560(HPLL_PHASE_CTRL2,d);
		WriteIIC560(GI_AUTO_TUNE_CTRL,0x42);
		ucLoopTimer_10ms = 10;
		while((ReadIIC560(GI_AUTO_TUNE_CTRL) & BIT_1) && ucLoopTimer_10ms != 0){
			CheckModeChange();
			if(bOptAbort == TRUE )
				return;
		}
		temp1 = ReadWordIIC560(GI_PHS_SDIFF_HI0);
		temp1 <<= 16;
		temp1 += ReadWordIIC560(GI_PHS_SDIFF_LI0);
		printf("%d %ld\r\n",(unsigned short)d,temp1);
		if(temp2 < temp1){
			temp2 = temp1;
			k = d;
		}
	}
	WriteIIC560(HPLL_PHASE_CTRL2,0);//k;
	printf("g=%d\r\n",(unsigned short)k);

	WriteIIC560(HPLL_PHASE_CTRL1,(Reg0x0d9 | BIT_7));
	k = 0;
	temp2 = 0;
	for(d=0; d<0x10; d++){
		WriteIIC560(HPLL_PHASE_CTRL2,d);
		WriteIIC560(GI_AUTO_TUNE_CTRL,0x42);
		ucLoopTimer_10ms = 10;
		while((ReadIIC560(GI_AUTO_TUNE_CTRL) & BIT_1) && ucLoopTimer_10ms != 0){
			CheckModeChange();
			if(bOptAbort == TRUE )
				return;
		}
		temp1 = ReadWordIIC560(GI_PHS_SDIFF_HI0);
		temp1 <<= 16;
		temp1 += ReadWordIIC560(GI_PHS_SDIFF_LI0);
		printf("%d %ld\r\n",(unsigned short)d,temp1);
		if(temp2 < temp1){
			temp2 = temp1;
			k = d;
		}
	}
	WriteIIC560(HPLL_PHASE_CTRL2,0);//k;
	printf("b=%d\r\n",(unsigned short)k);
}

#endif

void GetHmask(void)
{

unsigned short mask,hw;
unsigned char sw;
float temp;
	WriteIIC560(GI_HMASK_BEG,0x10);  // AutoPosition Pixel mask -> H
	sw = ReadIIC560(GI_HS_WID);
//	printf("GI_HS_WID=%d\r\n",(unsigned short)sw);
	hw = ReadWordIIC560(GI_HCNT_LI) & 0x1fff;
//	printf("GI_HCNT_LI=%d\r\n",hw);
	temp = (float)usHTotal * sw * 8 / hw;
	if((abs(usVSync-600) < 11)&&((H_ActiveTab[ucResolution] == 640)&&(V_ActiveTab[ucResolution] == 480))){
		mask = (unsigned char)(temp * 11 / 10 + 0.5);
	}
	else{
		mask = (unsigned char)(temp * 12 / 10 + 0.5);
	}
	if(mask > 0xff) mask = 0xff;
	hw = usHTotal - H_ActiveTab[ucResolution] - usHPStart;
	if(mask > hw)
		mask = hw;
	WriteIIC560(GI_HMASK_END,mask);  // AutoPosition Pixel mask -> H
//	printf("mask=%d\r\n",(unsigned short)mask);

}


