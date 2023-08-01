#include "RAM.H"
#include "NT686xx_MCU_REG.H"
#include "MyDef.H"
#include "NVRAM.H"
#include "UserAdj.H"
#include "ModeHandle.H"
#include "Scaler.H"
#include "AutoAdj.H"
#include "sRGB.H"
#include "DDC_Ci.H"
#include "MCU.h"
#include "OSD.h"
#include "stdio.h"
#include "ROM_MAP.H"
#include "8051.H"
#include "Board.H"
#include "NT686xx_SC_REG.h"
#include "Panel.H"
#include "OSD_Tab.H"
#include "NVTDebug.h"
#include "factory.H"
#include "FactoryAlignment.h"
#include "BFControl.H"
//#ifdef NOVATEK_HDCP_WRITER
#include "HDCP.h"
//#endif
#include "Mis.h"


#ifdef BenQ_FACTORY
code unsigned char ColorTab3[]={	//factory
	1,2,4,0,3
};

#endif

static unsigned char ucClearOSDFlag;

void CheckDDC2Bi(void)
{
unsigned char cmd;
	if(bDDCCmdUpdate == TRUE){
		while(bDDCCmdUpdate){
			bDDCCmdUpdate = FALSE;
	//Wait stop
			ucLoopTimer_10ms = 100;
			while(ucLoopTimer_10ms != 0){
				if((bDDC_Ci_Channel == 0)&&((IIC0_STATUS & BUS_STOP) != 0)){
					break;
				}
				else if((bDDC_Ci_Channel == 1)&&((IIC1_STATUS & BUS_STOP) != 0)){
					break;
				}
			}
			if((ucLoopTimer_10ms != 0)&&(ucDDCCiRxIn != 0)){	//receive						
				if((bFactoryMode == FALSE) || (bFactoryModeType == FACTORY_DDCCI)){
					ucDDCCiRxChecksum = 0;
					ucDDCCiRxOut = 0;
					cmd = (ucDDCCiRxBuffer[1] & 0x7f) + 3; 
//					printf("%bx ",cmd);
					if(ucDDCCiRxIn > cmd)
						ucDDCCiRxIn = cmd;
					while(ucDDCCiRxIn != ucDDCCiRxOut){
						cmd = ucDDCCiRxBuffer[ucDDCCiRxOut++];
						ucDDCCiRxChecksum ^= cmd;
						if(ucDDCCiRxOut > DDCCi_BUFFER_SIZE-1)
							ucDDCCiRxOut = 2;
//						printf("%bx ",cmd);
					}
//					printf(":%bx ",ucDDCCiTxIn);
//					printf("\r\n");
					ucDDCCiRxIn = 0;
					//ucDDCCiRxOut = 0;
					Check2BiCmd();
			
				}
				else if(bFactoryModeType == FACTORY_4BYTE){	//Factory Alignment
//				else{	//Factory Alignment
					BenQ_FactoryAlignment();
				}
			}
		}
	}
}

code unsigned char ColorTab1[]={	//ddc/ci
	0x05,0x01,0x0b,0x02
};
code unsigned char ColorTab2[]={
	0x04,0x05,0x06,0x07,0x08,0x0a
};
//code unsigned char ColorTab2[]={	//ddc/ci
//	4,3,0,4,4,2,4,4,1,4,4,4,4,4,4,4,4
//};

void Check2BiCmd(void)
{
 unsigned char TempCK;
	TempCK = ucDDCCiRxChecksum;
//	printf("CK = %bx\r\n",TempCK);

	if((TempCK == DDCCI_ADDR)||(TempCK == DDCCI_ADDR+1)){
		ucClearOSDFlag = TRUE;
		SendNullCmd(DDCCI_ADDR);
	//check sum ok. DDCi
//printf("DDCBuf0=%02x,%02x,%02x",(unsigned short)ucDDCCiRxBuffer[6],(unsigned short)ucDDCCiRxBuffer[7],(unsigned short)ucDDCCiRxBuffer[8]);
//printf(",%02x,%02x,%02x\r\n",(unsigned short)ucDDCCiRxBuffer[9],(unsigned short)ucDDCCiRxBuffer[10],(unsigned short)ucDDCCiRxBuffer[11]);
		switch(ucDDCCiRxBuffer[2]){
		case CMDOP_GET_VCP:	//GetVCP_Feature
			GetVCP_Feature();
			break;
		case CMDOP_SET_VCP:	//SetVCP_Feature
#ifdef ENABLE_TD_	
//printf("%d,%d,%d\r\n",(unsigned short)ucTD_ACMode,(unsigned short)ucTD_State,(unsigned short)ucDDCCiRxBuffer[3]);
			if(ucTD_ACMode != TD_NORMAL && ucTD_State == TD_THEFT  && (ucDDCCiRxBuffer[3]!=VCPOP_TD_PIN_L&&ucDDCCiRxBuffer[3]!=VCPOP_TD_PIN_H) )	break;
#endif
			SetVCP_Feature();
			break;
		case CMDOP_GET_TIMING:	//GetTiming
			GetTiming();
			break;
		case CMDOP_SAVE:	//SaveCurrentSetting
			SaveCurrentSetting();
			break;
		case CMDOP_SET_CAP:	//VCPcapability
			SetVCP_Capabilities();
			break;
		default:
//			SendACKCmd();
//			printf("test\r\n");
			return;	// DO NOT GO TO OSD_OFF()
			break;
		}

#ifdef ENABLE_TD_	
		if (( ucTD_ACMode == TD_NORMAL || ucTD_State != TD_THEFT ) && ucClearOSDFlag)
#endif
			OSD_OFF();
	}
	
}

void SendNullCmd(unsigned char SlaveAddr)
{
	ucDDCCiTxBuffer[0] = SlaveAddr;
	ucDDCCiTxBuffer[1] = 0x80;
	ucDDCCiTxChecksum = 0x50;
	ucDDCCiTxOut = 0;
	ucDDCCiTxIn = 2;
}

/*
void SendACKCmd(void)
{
	if(IIC0_ADDR == DDCCI_ADDR)
		ucDDCCiTxBuffer[0] = 0x6e;
	else
		ucDDCCiTxBuffer[0] = 0x58;
	ucDDCCiTxBuffer[1] = 0x81;
	ucDDCCiTxBuffer[2] = 0x0c;
	ucDDCCiTxChecksum = 0x50;
	ucDDCCiTxOut = 0;
	ucDDCCiTxIn = 3;
}

void SendNACKCmd(void)
{
	if(IIC0_ADDR == DDCCI_ADDR)
		ucDDCCiTxBuffer[0] = 0x6e;
	else
		ucDDCCiTxBuffer[0] = 0x58;
	ucDDCCiTxBuffer[1] = 0x81;
	ucDDCCiTxBuffer[2] = 0x0b;
	ucDDCCiTxChecksum = 0x50;
	ucDDCCiTxOut = 0;
	ucDDCCiTxIn = 3;
}
*/


void ReplyNA()
{
	ucDDCCiTxBuffer[3] = 0x01;		//result code = unsupported
	ucDDCCiTxBuffer[6] = 0x00;		//maximumHi
	ucDDCCiTxBuffer[7] = 0xff;		//maximumLo
	ucDDCCiTxBuffer[8] = 0x00;		//
	ucDDCCiTxBuffer[9] = 0x00;		//
}

void GetVCP_Feature(void)
{
 unsigned short temp;
#ifdef NVT_HW_DEBUG
//	if ( bFactoryMode && ucDDCCiRxBuffer[3] == VCPOP_AOC_CMD )		//AOC Factory command: READ
	if(ucDDCCiRxBuffer[3] == VCPOP_AOC_CMD )		//AOC Factory command: READ
	{
		
		WaitDDCTxOut();
		
		if(NVTHWDebug(ucDDCCiRxBuffer, ucDDCCiTxBuffer)){
			// NVT DEBUG HERE
			ucDDCCiTxChecksum = 0x50;
			ucDDCCiTxOut = 0;
			ucDDCCiTxIn = 10;
			return;
		}
		for(temp=0; temp<8; temp++){
			ucUARTRxBuffer[temp] = ucDDCCiRxBuffer[4+temp];	//command
		}

		ucUARTRxOut = 0;
		ucUARTRxIn = 8;
		return;
	}
#endif	
	WaitDDCTxOut();
	
	ucDDCCiTxBuffer[0] = ACCESSBUS_ADDR;
	ucDDCCiTxBuffer[1] = 0x88;
	ucDDCCiTxBuffer[2] = CMDOP_VCP_RPL;
	ucDDCCiTxBuffer[3] = 0x00;		//result code = no error
	ucDDCCiTxBuffer[4] = ucDDCCiRxBuffer[3];
	ucDDCCiTxBuffer[5] = 0x00;		//vcp type = set parameter
	ucDDCCiTxChecksum = 0x50;
	ucDDCCiTxOut = 0;
	ucDDCCiTxIn = 10;

	switch(ucDDCCiRxBuffer[3]){
	case VCPOP_NEW_CTRL:	//0x02
		ucDDCCiTxBuffer[6] = 0x00;		//maximumHi
		ucDDCCiTxBuffer[7] = 0xff;		//maximumLo
		ucDDCCiTxBuffer[8] = 0x00;		//
		ucDDCCiTxBuffer[9] = ucNewControlValue;		//0xff no user control are present
		break;
	case VCPOP_COLOR_INC:	//0x0B
		ucDDCCiTxBuffer[6] = 0xff;		//maximumHi
		ucDDCCiTxBuffer[7] = 0xff;		//maximumLo
		ucDDCCiTxBuffer[8] = 0x00;		//
		ucDDCCiTxBuffer[9] = 50;		//each step = 50
		break;
	case VCPOP_COLOR_REQ:	//0x0C
		ucDDCCiTxBuffer[6] = 0xff;		//maximumHi
		ucDDCCiTxBuffer[7] = 0xff;		//maximumLo
		ucDDCCiTxBuffer[8] = 0x00;		//
		if(ucColorTemperature==COLOR_5000 )
			ucDDCCiTxBuffer[9] = 40;
		else if(ucColorTemperature==COLOR_6500 )
			ucDDCCiTxBuffer[9] = 70;
		else if(ucColorTemperature==COLOR_7500 )
			ucDDCCiTxBuffer[9] = 90;
		else if(ucColorTemperature==COLOR_8200 )
			ucDDCCiTxBuffer[9] = 104;
		else if(ucColorTemperature==COLOR_9300 )
			ucDDCCiTxBuffer[9] = 126;
		else if(ucColorTemperature==COLOR_11500 )
			ucDDCCiTxBuffer[9] = 170;
		else
			ucDDCCiTxBuffer[9] = 70;
		break;
	case VCPOP_CLOCK:	//clock
		if (ucSignalType == sigDVI){
			ReplyNA();
		}
		else{
			ucDDCCiTxBuffer[6] = 0x00;		//maximumHi
			ucDDCCiTxBuffer[7] = 100;		//maximumLo
			ucDDCCiTxBuffer[8] = 0x00;		//clockHi
			ucDDCCiTxBuffer[9] = usHTotal-usMinClk;		//clockLo
		}
		break;
	case VCPOP_BRIGHT:	//brightness
		ucDDCCiTxBuffer[6] = 0x00;		//maximumHi
		ucDDCCiTxBuffer[7] = 100;		//maximumLo
		ucDDCCiTxBuffer[8] = 0x00;		//brightnessHi
		ucDDCCiTxBuffer[9] = ucBrightness;	//brightnessLo
		break;
	case VCPOP_CONTRAST:	//contrast
		ucDDCCiTxBuffer[6] = 0x00;		//maximumHi
		ucDDCCiTxBuffer[7] = 100;		//maximumLo
		ucDDCCiTxBuffer[8] = 0x00;		//contrastHi
		ucDDCCiTxBuffer[9] = ucContrast;	//contrastLo
		break;
	case VCPOP_SEL_COLOR:	//select color preset
		ucDDCCiTxBuffer[6] = 0x00;		//maximumHi
		ucDDCCiTxBuffer[7] = 0x0b;		//maximumLo
		ucDDCCiTxBuffer[8] = 0x00;		//colorinputHi
		ucDDCCiTxBuffer[9] = ColorTab2[ucColorTemperature];
		break;
	case VCPOP_RGAIN:	//Red gain
		ucDDCCiTxBuffer[6] = 0x00;		//maximumHi
		ucDDCCiTxBuffer[7] = 100;		//maximumLo
		ucDDCCiTxBuffer[8] = 0x00;		//R_GainHi
		ucDDCCiTxBuffer[9] = ((unsigned short)ucR_GainUser * 100 + 128) / 255;	//R_GainLo	2006-11-28 VISTA
		break;
	case VCPOP_GGAIN:	//Green gain
		ucDDCCiTxBuffer[6] = 0x00;		//maximumHi
		ucDDCCiTxBuffer[7] = 100;		//maximumLo
		ucDDCCiTxBuffer[8] = 0x00;		//G_GainHi
		ucDDCCiTxBuffer[9] = ((unsigned short)ucG_GainUser * 100 + 128) / 255;	//G_GainLo	2006-11-28 VISTA
		break;
	case VCPOP_BGAIN:	//Blue gain
		ucDDCCiTxBuffer[6] = 0x00;		//maximumHi
		ucDDCCiTxBuffer[7] = 100;		//maximumLo
		ucDDCCiTxBuffer[8] = 0x00;		//B_GainHi
		ucDDCCiTxBuffer[9] = ((unsigned short)ucB_GainUser * 100 + 128) / 255;	//B_GainLo	2006-11-28 VISTA
		break;
	case VCPOP_AUTO_COLOR:			
	case VCPOP_AUTO_SET:	//autoaetup
		if(ucSignalType != sigDVI){
			ucDDCCiTxBuffer[6] = 0x00;		//maximumHi
			ucDDCCiTxBuffer[7] = 0x01;		//maximumLo
			ucDDCCiTxBuffer[8] = 0x00;		//autoaetupHi
			ucDDCCiTxBuffer[9] = 0x00;		//autoaetupLo
		}
		else{
			ReplyNA();
		}
		break;
	case VCPOP_RECALL:	//factory reset		//2004-01-27 add facrory reset
	case VCPOP_RECALL_BC:
	case VCPOP_RECALL_COLOR:
	case VCPOP_RECALL_HV_POS:
	case VCPOP_END:
		ucDDCCiTxBuffer[6] = 0x00;		//maximumHi
		ucDDCCiTxBuffer[7] = 0x01;		//maximumLo
		ucDDCCiTxBuffer[8] = 0x00;		//autoaetupHi
		ucDDCCiTxBuffer[9] = 0x00;		//autoaetupLo
		break;
	case VCPOP_H_POS:	//horizontal position
		if (ucSignalType == sigDVI){
			ReplyNA();
		}
		else{
			temp = usMaxHP - ucMinHP;
			ucDDCCiTxBuffer[6] = (unsigned char)(temp >> 8);	//maximumHi
			ucDDCCiTxBuffer[7] = (unsigned char)temp;		//maximumLo
			temp = usMaxHP - usHPStart;
			ucDDCCiTxBuffer[8] = (unsigned char)(temp >> 8);	//HpHi
			ucDDCCiTxBuffer[9] = (unsigned char)temp;		//HpLo
		}
		break;
	case VCPOP_V_POS:	//vertical position
		if (ucSignalType == sigDVI){
			ReplyNA();
		}
		else{
			temp = ucMaxVP - ucMinVP;
			ucDDCCiTxBuffer[6] = (unsigned char)(temp >> 8);	//maximumHi
			ucDDCCiTxBuffer[7] = (unsigned char)temp;		//maximumLo
			temp = usVPStart - ucMinVP;
			ucDDCCiTxBuffer[8] = (unsigned char)(temp >> 8);	//VpHi
			ucDDCCiTxBuffer[9] = (unsigned char)temp;		//VpLo
		}
		break;
	case VCPOP_H_PHASE:	//phase
		if (ucSignalType == sigDVI){
			ReplyNA();
		}
		else{
			ucDDCCiTxBuffer[6] = 0x00;		//maximumHi
			ucDDCCiTxBuffer[7] = 100;		//maximumLo
			ucDDCCiTxBuffer[8] = 0x00;		//phaseHi
			ucDDCCiTxBuffer[9] = ucADCCPhase100Pa;	//((unsigned short)ucADCPhase * 100) / 63;		//phaseLo
		}
		break;
	case VCPOP_INPUT:		//0x60
//#if DualMode==ON	
		ucDDCCiTxBuffer[6] = 0x00;		//maximumHi
		ucDDCCiTxBuffer[7] = 0x03;		//maximumLo
		ucDDCCiTxBuffer[8] = 0x00;		//
		if(ucSignalType == sigDVI)
			ucDDCCiTxBuffer[9] = 0x03;		//digital
		else
			ucDDCCiTxBuffer[9] = 0x01;		//analog
		break;
/*#else
		ucDDCCiTxBuffer[6] = 0x00;		//maximumHi
		ucDDCCiTxBuffer[7] = 0x01;		//maximumLo
		ucDDCCiTxBuffer[8] = 0x00;		//
		ucDDCCiTxBuffer[9] = 0x01;		//analog
		break;
#endif*/
case VCPOP_ROFFSET:		//0x6C
		WriteIIC560(SRGB_CTRL, 0x21);
		ucDDCCiTxBuffer[6] = 0x00;		//maximumHi
		ucDDCCiTxBuffer[7] = 0xff;		//maximumLo
		ucDDCCiTxBuffer[8] = 0x00;		//B_GainHi
		ucDDCCiTxBuffer[9] = ucBkOffset[0];
		break;
	case VCPOP_GOFFSET:		//0x6E
		WriteIIC560(SRGB_CTRL, 0x23);
		ucDDCCiTxBuffer[6] = 0x00;		//maximumHi
		ucDDCCiTxBuffer[7] = 0xff;		//maximumLo
		ucDDCCiTxBuffer[8] = 0x00;		//B_GainHi
		ucDDCCiTxBuffer[9] = ucBkOffset[1];
		break;
	case VCPOP_BOFFSET:		//0x70
		WriteIIC560(SRGB_CTRL, 0x25);
		ucDDCCiTxBuffer[6] = 0x00;		//maximumHi
		ucDDCCiTxBuffer[7] = 0xff;		//maximumLo
		ucDDCCiTxBuffer[8] = 0x00;		//B_GainHi
		ucDDCCiTxBuffer[9] = ucBkOffset[2];
		break;
	case VCPOP_H_FREQ:
		ucDDCCiTxBuffer[6] = 0xff;		//maximumHi
		ucDDCCiTxBuffer[7] = 0xff;		//maximumLo
		temp = (unsigned short)(ulDispHfreq>>1);				//Hz
		ucDDCCiTxBuffer[8] = (unsigned char)(temp>>8);	//H_Sync Hi
		ucDDCCiTxBuffer[9] = (unsigned char)temp;		//H_Sync Lo
		break;
	case VCPOP_V_FREQ:
		ucDDCCiTxBuffer[6] = 0xff;		//maximumHi
		ucDDCCiTxBuffer[7] = 0xff;		//maximumLo
		temp = usVSync * 10;			//0.01Hz
		ucDDCCiTxBuffer[8] = (unsigned char)(temp>>8);	//V_Sync Hi
		ucDDCCiTxBuffer[9] = (unsigned char)temp;		//V_Sync Lo
		break;
	case VCPOP_DISP_TYPE:	//0xB6
		ucDDCCiTxBuffer[6] = 0x00;		//maximumHi
		ucDDCCiTxBuffer[7] = 0x04;		//maximumLo
		ucDDCCiTxBuffer[8] = 0x00;		//displaytypeHi
		ucDDCCiTxBuffer[9] = 0x03;		//displaytypeLo
		break;
	case VCPOP_AUDIO:	//volume
		ucDDCCiTxBuffer[6] = 0x00;		//maximumHi
		ucDDCCiTxBuffer[7] = 100;		//maximumLo
		ucDDCCiTxBuffer[8] = 0x00;		//VolumeHi
		ucDDCCiTxBuffer[9] = ucVolume;	//VolumeLo
		break;
	case VCPOP_MUTE:	//volume
		ucDDCCiTxBuffer[6] = 0x00;		//maximumHi
		ucDDCCiTxBuffer[7] = 0x02;		//maximumLo
		ucDDCCiTxBuffer[8] = 0x00;		//VolumeHi
		ucDDCCiTxBuffer[9] = 2-(unsigned char)bMute;	//VolumeLo
		break;
	case VCPOP_USE_TIME:	//usage time
		ucDDCCiTxBuffer[6] = 0xff;		//maximumHi
		ucDDCCiTxBuffer[7] = 0xff;		//maximumLo
		temp = Get_ulPOTTimerH();
		ucDDCCiTxBuffer[8] = (unsigned char)(temp >> 8);		//displaytimeHi
		ucDDCCiTxBuffer[9] = (unsigned char)temp;		//displaytimeLo
		break;
	case VCPOP_APP_KEY:	//Application enable key
		ucDDCCiTxBuffer[6] = 0xff;		//maximumHi
		ucDDCCiTxBuffer[7] = 0xff;		//maximumLo
		ucDDCCiTxBuffer[8] = 0x00;		//
		ucDDCCiTxBuffer[9] = 0x6F;		//Philips Application enable key = 0x6f
		break;
	case VCPOP_CTRL_TYPE:	//0xC8
		ucDDCCiTxBuffer[6] = 0xff;		//maximumHi
		ucDDCCiTxBuffer[7] = 0xff;		//maximumLo
		ucDDCCiTxBuffer[8] = 0x00;		//
		ucDDCCiTxBuffer[9] = 0x12;		//DEFINE FOR PHILIPS BY PORTRAIT
		break;
	case VCPOP_FW_LEVEL:	//0xC9F/W level
		ucDDCCiTxBuffer[6] = 0xff;		//maximumHi
		ucDDCCiTxBuffer[7] = 0xff;		//maximumLo
		ucDDCCiTxBuffer[8] = 0x00;		//level 3
		ucDDCCiTxBuffer[9] = 0x03;		//level 3
		break;
	case VCPOP_OSD_LOCK:
		ucDDCCiTxBuffer[6] = 0x00;		//maximumHi
		ucDDCCiTxBuffer[7] = 0x02;		//maximumLo
		ucDDCCiTxBuffer[8] = 0x00;		//level 3
		ucDDCCiTxBuffer[9] = 2-(unsigned char)bIsOSDLocked;
		break;
	case VCPOP_LANGUAGE:
		ucDDCCiTxBuffer[6] = 0x00;		//maximumHi
		ucDDCCiTxBuffer[7] = 0xff;		//maximumLo
		ucDDCCiTxBuffer[8] = 0x00;		//level 3
		if ( ucLanguage == mENGLISH)		ucDDCCiTxBuffer[9] = 0x02;
		else if (ucLanguage == mFRENCH)		ucDDCCiTxBuffer[9] = 0x03;
		else if (ucLanguage == mGERMAN)		ucDDCCiTxBuffer[9] = 0x04;
		else if (ucLanguage == mITALIAN)		ucDDCCiTxBuffer[9] = 0x05;
		else if (ucLanguage == mPORTUGUESE)	ucDDCCiTxBuffer[9] = 0x08;
		else if (ucLanguage == mRUSSIAN)		ucDDCCiTxBuffer[9] = 0x09;
		else if (ucLanguage == mSPANISH)		ucDDCCiTxBuffer[9] = 0x0A;	
		else if (ucLanguage == mCHINESE_S)		ucDDCCiTxBuffer[9] = 0x0d;
		break;
	case VCPOP_POWER_MODE:
		ucDDCCiTxBuffer[6] = 0x00;		//maximumHi
		ucDDCCiTxBuffer[7] = 0x04;		//maximumLo
		ucDDCCiTxBuffer[8] = 0x00;		//
		if(ucPowerStatus < 0x80)
			ucDDCCiTxBuffer[9] = 0x04;		//power status off
		else if(IsPanelPowerOn() == 0)
			ucDDCCiTxBuffer[9] = 0x02;		//power status standby
		else
			ucDDCCiTxBuffer[9] = 0x01;		//power status on
		break;
	case VCPOP_SMARTIMAGE:
		ucDDCCiTxBuffer[6] = 0x00;		//maximumHi
		ucDDCCiTxBuffer[7] = 0xff;		//maximumLo
		ucDDCCiTxBuffer[8] = 0x00;		//level 3
		if ( ucLFMode == LF_MODE_OFFICE_WORK)		ucDDCCiTxBuffer[9] = 0x01;
		else if (ucLFMode == LF_MODE_ImageViewing)	ucDDCCiTxBuffer[9] = 0x02;
		else if (ucLFMode == LF_MODE_Entertainment)	ucDDCCiTxBuffer[9] = 0x03;
		else if (ucLFMode == LF_MODE_Economic)		ucDDCCiTxBuffer[9] = 0x08;
		else				ucDDCCiTxBuffer[9] = 0x00;
		break;
	case VCPOP_MCC20:	//0xDF
		ucDDCCiTxBuffer[6] = 0xff;		//maximumHi
		ucDDCCiTxBuffer[7] = 0xff;		//maximumLo
		ucDDCCiTxBuffer[8] = 0x02;		//Version 2
		ucDDCCiTxBuffer[9] = 0x00;		//reversion 0
		break;
	case VCPOP_PHP_RESOLU:
		ucDDCCiTxBuffer[6] = 0x00;		//maximumHi
		ucDDCCiTxBuffer[7] = 0x02;		//maximumLo
		ucDDCCiTxBuffer[8] = 0x00;		//Version 2
		if ( bResolutionNot )
			ucDDCCiTxBuffer[9] = 0x02;		//reversion 0
		else
			ucDDCCiTxBuffer[9] = 0x00;		//reversion 0
		break;
#ifdef ENABLE_TD_		//	THEFT DETERRENCE
	case VCPOP_TD_ACCESSMODE:
		ucClearOSDFlag = FALSE;
		ucDDCCiTxBuffer[3] = 0x00;		//result code = no error
		ucDDCCiTxBuffer[6] = 0xff;		//maximumHi
		ucDDCCiTxBuffer[7] = 0xff;		//maximumLo
		ucDDCCiTxBuffer[8] = 0x00;	
		ucDDCCiTxBuffer[9] = ucTD_ACMode;
		//printf("Read VCPOP_TD_ACCESSMODE=%d\r\n",(unsigned short)ucTD_ACMode);	
		break;
	case VCPOP_TD_TIMEOUT:
		ucClearOSDFlag = FALSE;
		ucDDCCiTxBuffer[3] = 0x00;		//result code = no error
		ucDDCCiTxBuffer[6] = 0xff;		//maximumHi
		ucDDCCiTxBuffer[7] = 0xff;		//maximumLo
		ucDDCCiTxBuffer[8] = 0x00;	
		ucDDCCiTxBuffer[9] = ucTD_Timeout;
		//printf("Read VCPOP_TD_TIMEOUT=%d\r\n",(unsigned short)ucTD_Timeout);	
		break;
#if 0
	case VCPOP_TD_PIN_L:
		ucClearOSDFlag = FALSE;
		ucDDCCiTxBuffer[3] = 0x00;		//result code = no error
		ucDDCCiTxBuffer[6] = 0xff;		//maximumHi
		ucDDCCiTxBuffer[7] = 0xff;		//maximumLo
		ucDDCCiTxBuffer[8] = usTD_PinCodeL>>8;
		ucDDCCiTxBuffer[9] = usTD_PinCodeL;
		break;
	case VCPOP_TD_PIN_H:
		ucClearOSDFlag = FALSE;
		ucDDCCiTxBuffer[3] = 0x00;		//result code = no error
		ucDDCCiTxBuffer[6] = 0xff;		//maximumHi
		ucDDCCiTxBuffer[7] = 0xff;		//maximumLo
		ucDDCCiTxBuffer[8] = usTD_PinCodeH>>8;
		ucDDCCiTxBuffer[9] = usTD_PinCodeH;
		break;
#endif

	case VCPOP_TD_STATE:
		ucClearOSDFlag = FALSE;
		ucDDCCiTxBuffer[3] = 0x00;		//result code = no error
		ucDDCCiTxBuffer[6] = 0xff;		//maximumHi
		ucDDCCiTxBuffer[7] = 0xff;		//maximumLo
		ucDDCCiTxBuffer[8] = 0x00;	
		ucDDCCiTxBuffer[9] = ucTD_State;
		//printf("Read VCPOP_TD_STATE=%d\r\n",(unsigned short)ucTD_State);	
		break;
#endif
	default:
		ReplyNA();
		break;
	}

}

void SetVCP_Feature(void)
{
 unsigned short k;
//	SendNACKCmd();
	switch(ucDDCCiRxBuffer[3]){
	case VCPOP_NEW_CTRL:
		if(ucDDCCiRxBuffer[4] == 0){
			if ( ucDDCCiRxBuffer[5]==1 || ucDDCCiRxBuffer[5]==2 || ucDDCCiRxBuffer[5]==0xff )
				ucNewControlValue = ucDDCCiRxBuffer[5];
		}
		break;
	case VCPOP_RECALL:	//recall
		RecallsRGBOffset();
		Recall();
		//OSD_OFF();
		//FactoryReset();	// 2006-01-11
		break;
	case VCPOP_RECALL_BC:	//recall brightness/contrast
			ucBrightness = MCU_DataMap[EPADDR_BRIGHT];//0x08 = brightness
			//Write24C16(EPADDR_BRIGHT,ucBrightness);//0x08 = brightness
			ucSavePointer = svBRIGHTNESS;
			SaveData();
			ucContrast = MCU_DataMap[EPADDR_CONTRAST];//0x09 = contrast
			//Write24C16(EPADDR_CONTRAST,ucContrast);//0x09 = contrast
			ucSavePointer = svCONTRAST;
			SaveData();
			SetContrastRGB();
			SetBrightness();
//#if _SmartBright_ == ON
//			SetBrightOffset();
//#endif
		break;
	case VCPOP_RECALL_HV_POS:
/*
		if((ucModeNumber < NUMBER_OF_USER_MODE)&&(ucSignalType != sigDVI)){
			//InitModeData(ucModeNumber);
			LoadModeDependentSettings();
			SetADC_PLL();
			SetHP();
			SetVP();

		}
*/
		if(ucSignalType != sigDVI) AutoPosition();
		break;
	case VCPOP_RECALL_COLOR:	//0x08
	
		RecallsRGBOffset();

		ucBrightness = MCU_DataMap[EPADDR_BRIGHT];//0x08 = brightness
		//Write24C16(EPADDR_BRIGHT,ucBrightness);//0x08 = brightness
		ucSavePointer = svBRIGHTNESS;
		SaveData();
		ucContrast = MCU_DataMap[EPADDR_CONTRAST];//0x09 = contrast
		//Write24C16(EPADDR_CONTRAST,ucContrast);//0x09 = contrast
		ucSavePointer = svCONTRAST;
		SaveData();
		
		ucR_GainUser = MCU_DataMap[EPADDR_RGAIN_USER];
		ucG_GainUser = MCU_DataMap[EPADDR_GGAIN_USER];
		ucB_GainUser = MCU_DataMap[EPADDR_BGAIN_USER];
		Write24C16(EPADDR_RGAIN_USER, ucR_GainUser);
		Write24C16(EPADDR_GGAIN_USER, ucG_GainUser);
		Write24C16(EPADDR_BGAIN_USER, ucB_GainUser);
		
		//Recall6500(1);
		ucColorTemperature = COLOR_6500;
		Write24C16(EPADDR_COLOR_TEMP, ucColorTemperature);
		SetColorTemp(ucColorTemperature);
	
		break;
	case VCPOP_COLOR_REQ:	//0x0C
		k = 3000 + (unsigned short)ucDDCCiRxBuffer[5] * 50;
		if(ucDDCCiRxBuffer[4] != 0)
			k = 0xffff;
		if ( k < 5750 )
			ucColorTemperature = COLOR_5000;
		else if ( k < 7000 )
			ucColorTemperature = COLOR_6500;
		else if ( k < 7850 )
			ucColorTemperature = COLOR_7500;
		else if ( k < 8750 )
			ucColorTemperature = COLOR_8200;
		else if ( k < 10400 )
			ucColorTemperature = COLOR_9300;
		else
			ucColorTemperature = COLOR_11500;
		SetColorTemp(ucColorTemperature);
		Write24C16(EPADDR_COLOR_TEMP, ucColorTemperature);
		break;
	case VCPOP_CLOCK:	//clock
		if(ucDDCCiRxBuffer[5] > 100)
			ucDDCCiRxBuffer[5] = 100;
		usHTotal = usMinClk + ucDDCCiRxBuffer[5] ;		//clockLo
		SetADC_PLL();
//		ucSavePointer = svCLOCK;
//		SaveData();
		break;
	case VCPOP_BRIGHT:	//brightness
		if(ucColorTemperature == COLOR_SRGB){	//sRGB
			ucColorTemperature = COLOR_6500;
			Write24C16(EPADDR_COLOR_TEMP, ucColorTemperature);//0x19 = color temperature select
			SetColorTemp(ucColorTemperature);
		}
		ucBrightness = ucDDCCiRxBuffer[5];		//brightnessLo
		if(ucBrightness > ucMaxBrightness)				ucBrightness = ucMaxBrightness;
		else if(ucBrightness < ucMinBrightness)			ucBrightness = ucMinBrightness;
		SetBrightness();
//#if _SmartBright_ == ON
//		SetBrightOffset();
//#endif
		ucSavePointer = svBRIGHTNESS;
		SaveData();
		break;
	case VCPOP_CONTRAST:	//contrast
		if(ucColorTemperature == COLOR_SRGB){	//sRGB
			ucColorTemperature = COLOR_6500;
			Write24C16(EPADDR_COLOR_TEMP, ucColorTemperature);//0x19 = color temperature select
			SetColorTemp(ucColorTemperature);
		}
		ucContrast = ucDDCCiRxBuffer[5];//contrastLo
		if(ucContrast > ucMaxContrast)				ucContrast = ucMaxContrast;
		else if(ucContrast < ucMinContrast)			ucContrast = ucMinContrast;
		SetContrastRGB();
		ucSavePointer = svCONTRAST;
		SaveData();
		break;
	case VCPOP_SEL_COLOR:	//color input
/*
01 : sRGB, 02 : Display native, 03 : 4000 K, 04 : 5000 K, 05 : 6500 K, 06 : 7500 K, 07 : 8200 K,
08 : 9300 K, 09 : 10000 K, 0A : 11500 K, 0B : User 1, 0C : User 2, 0D : User 3
*/
		switch(ucDDCCiRxBuffer[5]){
		case 0x01:
			k = COLOR_SRGB;
			break;
//		case 0x02:
//			k = COLOR_ORIGIN;
//			break;
		case 0x04:
			k = COLOR_5000;
			break;
		case 0x05:
			k = COLOR_6500;
			break;
		case 0x06:
			k = COLOR_7500;
			break;
		case 0x07:
			k = COLOR_8200;
			break;
		case 0x08:
			k = COLOR_9300;
			break;
		case 0x0a:
			k = COLOR_11500;
			break;
		case 0x0b:
			k = COLOR_USER;
			break;
		default:
			k = ucColorTemperature;
			break;
		}
		if(ucColorTemperature != k){
			ucColorTemperature = k;
			SetColorTemp(ucColorTemperature);
			Write24C16(EPADDR_COLOR_TEMP, ucColorTemperature);
//			printf("%d\r\n",(unsigned short)ucColorTemperature);
		}
		break;
	case VCPOP_RGAIN:	//red
		/*
		if(ucColorTemperature == COLOR_USER){	//user
			ucR_Gain = ((unsigned short)ucDDCCiRxBuffer[5] * 255 + 50) / 100;		//R_GainLo
			ucR_GainUser = ucR_Gain;
			SetContrastRGB();
			ucSavePointer = svRED;
			SaveData();
		}
		break;
		*/
		if(ucColorTemperature != COLOR_USER){
			ucColorTemperature = COLOR_USER;
			Write24C16(EPADDR_COLOR_TEMP, ucColorTemperature);
		}
	
		if(ucDDCCiRxBuffer[5] > 100)
			ucDDCCiRxBuffer[5] = 100;
		ucR_GainUser = ((unsigned short)ucDDCCiRxBuffer[5]* 255) / 100;
		//printf("Set ucR_GainUser=%d\r\n", (unsigned short)ucR_GainUser);
		Write24C16(EPADDR_RGAIN_USER, ucR_GainUser);
		SetColorTemp(ucColorTemperature);
		break;
	case VCPOP_GGAIN:	//green
		/*
		if(ucColorTemperature == COLOR_USER){	//user
			ucG_Gain = ((unsigned short)ucDDCCiRxBuffer[5] * 255 + 50) / 100;		//G_GainLo
			ucG_GainUser = ucG_Gain;
			SetContrastRGB();
			ucSavePointer = svGREEN;
			SaveData();
		}
		break;
		*/
		if(ucColorTemperature != COLOR_USER){
			ucColorTemperature = COLOR_USER;
			Write24C16(EPADDR_COLOR_TEMP, ucColorTemperature);
		}
	
		if(ucDDCCiRxBuffer[5] > 100)
			ucDDCCiRxBuffer[5] = 100;
		ucG_GainUser = ((unsigned short)ucDDCCiRxBuffer[5]* 255 + 50) / 100;
		Write24C16(EPADDR_GGAIN_USER, ucG_GainUser);
		SetColorTemp(ucColorTemperature);
		break;
	case VCPOP_BGAIN:	//blue
		/*
		if(ucColorTemperature == COLOR_USER){	//user
			ucB_Gain = ((unsigned short)ucDDCCiRxBuffer[5] * 255 + 50) / 100;		//B_GainLo
			ucB_GainUser = ucB_Gain;
			SetContrastRGB();
			ucSavePointer = svBLUE;
			SaveData();
		}
		break;
		*/
		if(ucColorTemperature != COLOR_USER){
			ucColorTemperature = COLOR_USER;
			Write24C16(EPADDR_COLOR_TEMP, ucColorTemperature);
		}
	
		if(ucDDCCiRxBuffer[5] > 100)
			ucDDCCiRxBuffer[5] = 100;
		ucB_GainUser = ((unsigned short)ucDDCCiRxBuffer[5]* 255 + 50) / 100;
		Write24C16(EPADDR_BGAIN_USER, ucB_GainUser);
		SetColorTemp(ucColorTemperature);
		break;
	case VCPOP_AUTO_SET:	//autosetup
		if(ucSignalType != sigDVI){
			//ShowAutoAdj();
			AutoTune();
			//bOSDReady = FALSE;			
			//MainOSD();	//  OSD in advance
			//OSD_OFF();
		}
		break;
	case VCPOP_AUTO_COLOR:	// auto color
		//if(ucSignalType != sigDVI &&(bFactoryMode) ){
		if(ucSignalType != sigDVI){	// For passing Portrait verification // Jude 07/25/2006
			OSD_OFF();
			AutoColor();
		}
		break;
	case VCPOP_H_POS:	//horizontal position
		k = usMaxHP - ucMinHP;
		usHPStart = ucDDCCiRxBuffer[4];		//HpHi
		usHPStart <<= 8;
		usHPStart |= ucDDCCiRxBuffer[5];		//HpLo
		if(usHPStart > k)
			usHPStart = k;
		usHPStart = usMaxHP - usHPStart;
		SetHP();
//		ucSavePointer = svHPOS;
//		SaveData();
		break;
	case VCPOP_V_POS:	//vertical position	//2005-01-24 mingyu
		k = ucDDCCiRxBuffer[4];		//VpHi
		k <<= 8;
		k |= ucDDCCiRxBuffer[5];	//VpLo
		if(k > ucMaxVP)
			k = ucMaxVP;
		if(k > usVPStart){
			do{
				usVPStart++;
				WaitVsync();
				SetVP();
			}while(usVPStart != k);
		}
		else if((k < usVPStart)&&(usVPStart != 0)){
			do{
				usVPStart--;
				WaitVsync();
				SetVP();
			}while(usVPStart != k);
		}
//		ucSavePointer = svVPOS;
//		SaveData();
		break;
	case VCPOP_H_PHASE:	//phase
		if(ucDDCCiRxBuffer[5] > 100)
			ucDDCCiRxBuffer[5] = 100;
		ucADCPhase = (((unsigned short)ucDDCCiRxBuffer[5] * 63) + 50) / 100;	//phaseLo
		SetADC_Phase();
		ucADCCPhase100Pa = ucDDCCiRxBuffer[5];
//		ucSavePointer = svPHASE;
//		SaveData();
		break;
	case VCPOP_INPUT:	// Jude 07/25/2006
		//ucPowerStatus_old = ucPowerStatus;
//		ucPowerStatus^= InputSourceDVI;
		if(ucDDCCiRxBuffer[5] == 0x03)
			ucPowerStatus |= InputSourceDVI;
		else
			ucPowerStatus &= ~InputSourceDVI;
		InputSourceSelect();
		break;
	case VCPOP_ROFFSET:
//		WriteIIC560(SRGB_CTRL, 0x21);
//		WriteIIC560(SRGB_COEF_OFFSET, ((unsigned short)ucDDCCiRxBuffer[5]*RGB_OFFSET_SCOPE+128)/255+RGB_OFFSET_MIN);
		ucBkOffset[0] = ucDDCCiRxBuffer[5];
		Write24C16(EPADDR_RBKOFFSET, ucBkOffset[0]);
		SetContrastRGB();
		break;
	case VCPOP_GOFFSET:
		//WriteIIC560(SRGB_CTRL, 0x23);
		//WriteIIC560(SRGB_COEF_OFFSET, ((unsigned short)ucDDCCiRxBuffer[5]*RGB_OFFSET_SCOPE+128)/255+RGB_OFFSET_MIN);
		ucBkOffset[1] = ucDDCCiRxBuffer[5];
		Write24C16(EPADDR_GBKOFFSET, ucBkOffset[1]);
		SetContrastRGB();
		break;
	case VCPOP_BOFFSET:
		//WriteIIC560(SRGB_CTRL, 0x25);
		//WriteIIC560(SRGB_COEF_OFFSET, ((unsigned short)ucDDCCiRxBuffer[5]*RGB_OFFSET_SCOPE+128)/255+RGB_OFFSET_MIN);
		ucBkOffset[2] = ucDDCCiRxBuffer[5];
		Write24C16(EPADDR_BBKOFFSET, ucBkOffset[2]);
		SetContrastRGB();
		break;
	case VCPOP_OSD_LOCK:	//0xCA
			if ( ucDDCCiRxBuffer[5]==1 )
			{
			  bIsOSDLocked = 1;
			}
			else if ( ucDDCCiRxBuffer[5]==2 )
			{
				bIsOSDLocked = 0;
			}
			Write24C16(EPADDR_OSDLOCK, bIsOSDLocked);//0x05 = osd loc

		break;
	case VCPOP_LANGUAGE:
		if ( ucDDCCiRxBuffer[5] == 0x02 )			ucLanguage = mENGLISH;
		else if ( ucDDCCiRxBuffer[5] == 0x03 )		ucLanguage = mFRENCH;
		else if ( ucDDCCiRxBuffer[5] == 0x04 )		ucLanguage = mGERMAN;
		else if ( ucDDCCiRxBuffer[5] == 0x05 )		ucLanguage = mITALIAN;
		else if ( ucDDCCiRxBuffer[5] == 0x08 )		ucLanguage = mPORTUGUESE;
		else if ( ucDDCCiRxBuffer[5] == 0x09 )		ucLanguage = mRUSSIAN;
		else if ( ucDDCCiRxBuffer[5] == 0x0A )		ucLanguage = mSPANISH;
		else if ( ucDDCCiRxBuffer[5] == 0x0D )		ucLanguage = mCHINESE_S;

		Write24C16(EPADDR_OSDLANG, ucLanguage);
		break;
	case VCPOP_POWER_MODE:		//0xD6
		if(ucDDCCiRxBuffer[5] == 1){		//power status on
			if(ucPowerStatus < 0x80)
				ucCurKey = POWER_KEY;
		}
		else if(ucDDCCiRxBuffer[5] == 2){	//power status standby
			if(ucPowerStatus > 0x7f){
				OSD_OFF();
				PowerSaving();
//				LED_GrnOff();						// -jwshin 111213
//				LED_RedOn();
				bForceToSleep = TRUE;
			}
		}
		else if(ucDDCCiRxBuffer[5] == 4){	//power status off
			if(ucPowerStatus > 0x7f)
				ucCurKey = POWER_KEY;
		}
		break;
	case VCPOP_SMARTIMAGE:
		if ( ucDDCCiRxBuffer[5]==0x00 )
			ucLFMode = LF_MODE_OFF;
		else if ( ucDDCCiRxBuffer[5]==0x01 )
			ucLFMode = LF_MODE_OFFICE_WORK;
		else if ( ucDDCCiRxBuffer[5]==0x02 )
			ucLFMode = LF_MODE_ImageViewing;
		else if ( ucDDCCiRxBuffer[5]==0x03 )
			ucLFMode = LF_MODE_Entertainment;
		else if ( ucDDCCiRxBuffer[5]==0x08 )
			ucLFMode = LF_MODE_Economic;
		else break;
		LFEnableSettings();		
		break;
	case VCPOP_PHP_RESOLU:
		if(ucDDCCiRxBuffer[5] == 2){
			bResolutionNot = 1;
		}
		else if(ucDDCCiRxBuffer[5] == 0){
			bResolutionNot = 0;
		}
		Write24C16(EPADDR_RSO_NOTF, bResolutionNot);
		break;
	case VCPOP_AUDIO:	//volume
		ucVolume = ucDDCCiRxBuffer[5];	//volumeLo
		//Write24C16(EPADDR_VOLUME, ucVolume);	//0x0c = volume
		ucSavePointer = svVOLUME;	// volume
		SaveData();
		if ( bMute )
		{
			bMute = FALSE;
			ucSavePointer = svMUTE;
			SaveData();
		}
		SetVolume();
		break;
	case VCPOP_MUTE:
		if(ucDDCCiRxBuffer[5]==1){
			  bMute = 1;
		}
		else if(ucDDCCiRxBuffer[5]==2){
				bMute = 0;
		}
		Write24C16(EPADDR_MUTE, bMute);//0x05 = osd loc
		SetVolume();
		break;
	case VCPOP_AOC_CMD:	//AOC Factory command

#ifdef NVT_HW_DEBUG
		if (!NVTHWDebug(ucDDCCiRxBuffer, NULL))	{
// RETURN 0, AOC FACTORY COMMAND GO INSIDE
#endif
			for(k=0; k<8; k++){
				ucUARTRxBuffer[k] = ucDDCCiRxBuffer[4+k];	//command
			}
	
			ucUARTRxOut = 0;
			ucUARTRxIn = 8;
#ifdef NVT_HW_DEBUG
		}
#endif
		break;

#ifdef NOVATEK_HDCP_WRITER
	case VCPOP_NVT_HDCP_START:
		StartHDCPStoring();
		break;
	case VCPOP_NVT_HDCP_WRITE:
		StoreHDCP(ucDDCCiRxBuffer+4, (ucDDCCiRxBuffer[1]&0x7f) - 2);
		break;
	case VCPOP_NVT_HDCP_CHKSUM:
		ucDDCCiTxBuffer[0] = ACCESSBUS_ADDR;
		ucDDCCiTxBuffer[1] = 0x82;
		ucDDCCiTxBuffer[2] = CMDOP_SET_VCP;
		if(CheckHDCPChkSum() != 0)
			ucDDCCiTxBuffer[3] = 0xef;
		else
			ucDDCCiTxBuffer[3] = 0xff;
		ucDDCCiTxChecksum = 0x50;
		ucDDCCiTxOut = 0;
		ucDDCCiTxIn  = 4;

		break;
#endif
#ifdef BenQ_FACTORY			
	case VCPOP_BENQ_FACTORY:	//BenQ Entry factory mode
		if((ucDDCCiRxBuffer[4] == 0x00)&&(ucDDCCiRxBuffer[5] == 0x00)){
			FactoryEnterMode();
			BenQ_EnterFactoryMode();
		}
		break;
#endif			
		

#ifdef ENABLE_TD_		//	THEFT DETERRENCE
	case VCPOP_TD_ACCESSMODE:
		ucClearOSDFlag = FALSE;
		if( ucTD_State == TD_NORMAL && ucTD_PinFailedCount==0) {
			ucTD_ACMode = ucDDCCiRxBuffer[5];
			Write24C16(EPADDR_TD_ACMODE, ucTD_ACMode);
			ucTD_State = TD_NORMAL;
			Write24C16(EPADDR_TD_STATE, ucTD_State);
		}
//		printf("ucTD_ACMode=%d(ucTD_State=%d)\r\n",(unsigned short)ucTD_ACMode,(unsigned short)ucTD_State);
		break;
	case VCPOP_TD_TIMEOUT:
		ucClearOSDFlag = FALSE;
		if(ucTD_ACMode == 0){
			
			if(ucDDCCiRxBuffer[5]==0) break;		
			
			ucTD_Timeout = ucDDCCiRxBuffer[5];
			Write24C16(EPADDR_TD_TIMEOUT, ucTD_Timeout);
		}
//		printf("VCPOP_TD_TIMEOUT=%d,%d\r\n",(unsigned short)ucTD_ACMode,(unsigned short)ucTD_Timeout);
		break;
	case VCPOP_TD_PIN_L:
		ucClearOSDFlag = FALSE;
		if(ucTD_ACMode == 0){
			Write24C16(EPADDR_TD_PINCODEL1, ucDDCCiRxBuffer[4]);
			Write24C16(EPADDR_TD_PINCODEL2, ucDDCCiRxBuffer[5]);
		}
		else{
			usTD_PinCodeL = ucDDCCiRxBuffer[4];		//HpHi
			usTD_PinCodeL <<= 8;
			usTD_PinCodeL |= ucDDCCiRxBuffer[5];		//HpLo
		}
		break;
	case VCPOP_TD_PIN_H:
		ucClearOSDFlag = FALSE;
		if(ucTD_ACMode == 0){
			Write24C16(EPADDR_TD_PINCODEH1, ucDDCCiRxBuffer[4]);
			Write24C16(EPADDR_TD_PINCODEH2, ucDDCCiRxBuffer[5]);
			ucTD_State = TD_NORMAL;
			Write24C16(EPADDR_TD_STATE, ucTD_State);
		}
		else if(ucTD_State != TD_LOG_TIMEOUT){
			if(ucTD_PinFailedTimer != 0){ 
				break;
			}
			usTD_PinCodeH = ucDDCCiRxBuffer[4];		//HpHi
			usTD_PinCodeH <<= 8;
			usTD_PinCodeH |= ucDDCCiRxBuffer[5];		//HpLo

//			printf("TD_PinCode=%x %x\r\n",usTD_PinCodeH,usTD_PinCodeL);

			if((usTD_PinCodeH == 0)&&(usTD_PinCodeL == 1711)){
				k = usTD_PinCodeL;
			}
			else{
				k = 0x0000;
			}
			if((((unsigned char)(usTD_PinCodeH>>8)) != Read24C16(EPADDR_TD_PINCODEH1) ||
			((unsigned char)usTD_PinCodeH) != Read24C16(EPADDR_TD_PINCODEH2) ||
			((unsigned char)(usTD_PinCodeL>>8)) != Read24C16(EPADDR_TD_PINCODEL1) ||
			((unsigned char)usTD_PinCodeL) != Read24C16(EPADDR_TD_PINCODEL2)) && (k == 0))
			{
				if(ucTD_PinFailedCount++ < 3){
					ucTD_PinFailedTimer = 2;
				}
				else{
					ucTD_PinFailedCount = 3;
					ucTD_PinFailedTimer = 30;
				}	
			}
			else {
					//printf("VCPOP_TD_TIMEOUT=%d,%d\r\n",(unsigned short)ucTD_ACMode,(unsigned short)ucTD_Timeout);
				ucTD_State = TD_NORMAL;
				Write24C16(EPADDR_TD_STATE, ucTD_State);
				if (bShowTheftOSD)
				{
					bShowTheftOSD = FALSE;
					OSD_OFF();
				}
				ucTD_PinFailedCount = 0;
				
				ucBrightness = Read24C16(EPADDR_BRIGHT);
				ucBrightnessUser = ucBrightness;
				//Write24C16(EPADDR_BRIGHT,ucBrightness);//0x08 = brightness
				//Write24C16(EPADDR_BRIGHT_USER, ucBrightnessUser);
				ucContrast = Read24C16(EPADDR_CONTRAST);
				ucContrastUser = ucContrast;
				//Write24C16(EPADDR_CONTRAST,ucContrast);//0x09 = contrast
				//Write24C16(EPADDR_CONTRAST_USER,ucContrastUser);
				//printf("ddc:ucBrightness=%d,%d\r\n",(unsigned short)ucBrightness,(unsigned short)ucBrightnessUser);
//				SetContrastRGB();
				ucColorTemperature = Read24C16(EPADDR_COLOR_TEMP);
				SetColorTemp(ucColorTemperature);
				SetBrightness();
			}
			//printf("VCPOP_TD_PIN_H=%04x, %04x\r\n",(unsigned short)usTD_PinCodeH,(unsigned short)usTD_PinCodeL);
		}
		break;
#if 0
	case VCPOP_TD_STATE:
		//printf("VCPOP_TD_STATE=%d\r\n",(unsigned short)ucTD_State);
		break;
#endif		
#endif
//	default:
//		SendNACKCmd();
//		break;
	}
}
	//2005-01-24 mingyu

void WaitVsync(void)
{
#if NT68665
	Set_usTimer1_1ms(40);
 	while(Get_usTimer1_1ms() != 0){
		if(GetVsyncLevel == LOW)
			break;
	}
#else
unsigned char value;
unsigned char volatile *pBus;
	SC_RegPage = 0x01;
	pBus = &SC_SYNC_INT_FLAG1;
	*pBus = BIT_1;
 	Set_usTimer1_1ms(40);
	while(Get_usTimer1_1ms() != 0){
		value = *pBus;
		if((value & BIT_1) != 0)
			break;
	}
#endif
}

void WaitDDCTxOut()
{
	Set_usTimer1_1ms(100);
	while(ucDDCCiTxOut != 0){
		if(Get_usTimer1_1ms() == 0)
			break;
	}
}

//	THEFT DETERRENCE	2007-06-06
void SetVCP_Capabilities(void)
{
code unsigned char VCP_CapTab_Analog[]={
	"(prot(monitor)"
	"type(lcd)"
	"model(Philips 190B)"
	"cmds(01 02 03 07 0C 4E F3 E3)"
	"vcp(02 04 05 06 08 0B 0C 0E 10 12 14(01 04 05 06 07 08 0A 0B) 16 18 1A 1E 20 30 3E 6C 6E 70 "
	"AC AE B6 C0 C6 C8 C9 CA CC( 00 02 03 04 05 08 09 0A 0D) D6(01 04) DC(00 01 02 03 08) DF E9(00 02) "
	"60(01 03) "
	"62 8D "
	"FA(00 01 02) FB FC FD FE(00 01 02 04) FF)"
	"mswhql(1)mccs_ver(2.0)asset_eep(32)mpu_ver(01)"
	"SmartManage(1.0))"
};
code unsigned char VCP_CapTab_DVI[]={
	"(prot(monitor)"
	"type(lcd)"

	"model(Philips 190B)"
	"cmds(01 02 03 07 0C 4E F3 E3)"
	"vcp(02 04 05 08 0B 0C 10 12 14(01 04 05 06 07 08 0A 0B) 16 18 1A 6C 6E 70 "
	"AC AE B6 C0 C6 C8 C9 CA CC( 00 02 03 04 05 08 09 0A 0D) D6(01 04) DC(00 01 02 03 08) DF E9(00 02) "
	"60(01 03) "
	"62 8D "
	"FA(00 01 02) FB FC FD FE(00 01 02 04) FF)"
	"mswhql(1)mccs_ver(2.0)asset_eep(32)mpu_ver(01)"
	"SmartManage(1.0))"
};
 unsigned char i;
 unsigned short l,offset;
 
	WaitDDCTxOut();
	
	if (ucSignalType == sigDVI)
		l = sizeof(VCP_CapTab_DVI)-1;
	else
		l = sizeof(VCP_CapTab_Analog)-1;
	offset = ucDDCCiRxBuffer[3];
	offset <<= 8;
	offset |= ucDDCCiRxBuffer[4];
	ucDDCCiTxBuffer[0] = ACCESSBUS_ADDR;
	ucDDCCiTxBuffer[2] = 0xe3;
	ucDDCCiTxBuffer[3] = ucDDCCiRxBuffer[3];
	ucDDCCiTxBuffer[4] = ucDDCCiRxBuffer[4];
	ucDDCCiTxChecksum = 0x50;
	ucDDCCiTxOut = 0;
	if(offset > l){		//end of data
		l = 32;
		ucDDCCiTxBuffer[1] = 0xa3;
		ucDDCCiTxIn = 37;
		for(i=0; i<l; i++){
			ucDDCCiTxBuffer[5+i] = 0x20;
		}
	}
	else{
		l = l - offset;
		if(l > 32){	//max.
			l = 32;
			ucDDCCiTxBuffer[1] = 0xa3;
			ucDDCCiTxIn = 37;
		}
		else{
			ucDDCCiTxBuffer[1] = 0x83 + l;
			ucDDCCiTxIn = l + 5;
		}
		
		if (ucSignalType == sigDVI)
		{
			for(i=0; i<l; i++){
				ucDDCCiTxBuffer[5+i] = VCP_CapTab_DVI[offset+i];
			}
		}
		else
		{
			for(i=0; i<l; i++){
				ucDDCCiTxBuffer[5+i] = VCP_CapTab_Analog[offset+i];
			}
		}
	
	}

}

void SaveCurrentSetting(void)
{
	Write24C16(EPADDR_BRIGHT, ucBrightness);//0x08 = brightness
	Write24C16(EPADDR_CONTRAST, ucContrast);//0x09 = contrast
	SaveModeDependentSettings();
	if(ucColorTemperature == COLOR_USER){	//user
		Write24C16(EPADDR_RGAIN_USER, ucR_Gain);//0x3e = r gain user
		Write24C16(EPADDR_GGAIN_USER, ucG_Gain);//0x3f = g gain user
		Write24C16(EPADDR_BGAIN_USER, ucB_Gain);//0x40 = b gain user
	}
}

void GetTiming(void)
{
unsigned short Temp;
	ucDDCCiTxBuffer[0] = ACCESSBUS_ADDR;
	ucDDCCiTxBuffer[1] = 0x06;
	ucDDCCiTxBuffer[2] = 0x4e;

	if ( bOutOfLimit == FALSE ) {
		ucDDCCiTxBuffer[3] = ucHVPolarity;
	}
	else{
		ucDDCCiTxBuffer[3] = ucHVPolarity | BIT_7;
	}
	
	Temp = usHSync * 10;
	ucDDCCiTxBuffer[4] = (unsigned char)(Temp >> 8);
	ucDDCCiTxBuffer[5] = (unsigned char)Temp;
	Temp = usVSync * 10;
	ucDDCCiTxBuffer[6] = (unsigned char)(Temp >> 8);
	ucDDCCiTxBuffer[7] = (unsigned char)Temp;
	ucDDCCiTxChecksum = 0x50;
	ucDDCCiTxOut = 0;
	ucDDCCiTxIn = 8;
}


void ReleaseFactoryMode(void)
{
	bFactoryMode = FALSE;
	
		ucOSDXPos = Read24C16(EPADDR_OSDX);		//0x15 = OSD position x
		ucOSDYPos = Read24C16(EPADDR_OSDY);		//0x16 = OSD position y

#ifdef BenQ_FACTORY
//	EDIDa_WP_ON();
//	EDIDb_WP_ON();
////////////////////////////////////////////////////////////
	IIC0_ADDR = DDCCI_ADDR;
	IIC0_ADDR = DDCCI_ADDR | ENIIC;
	IIC0INT_CLR = 0xff;
	IIC0_INT_EN = 0xf8;
	IIC1_ADDR = DDCCI_ADDR;
	IIC1_ADDR = DDCCI_ADDR | ENIIC;
	IIC1INT_CLR = 0xff;
	IIC1_INT_EN = 0xf8;
	SendNullCmd(DDCCI_ADDR);
/////////////////////////////////////////////////////////////
//	printf("EntryFactoryMode %x\r\n",(unsigned short)IIC0_ADDR);
#endif
}

#ifdef ENABLE_TD_	//	THEFT DETERRENCE
void TD_Init()
{
//	Write24C16(EPADDR_TD_ACMODE,0x01);
//	Write24C16(EPADDR_TD_TIMEOUT,1);
	ucTD_ACMode = Read24C16(EPADDR_TD_ACMODE);

	if(ucTD_ACMode != 0){
		ucTD_State = TD_POSSIBLE_THEFT;
		Write24C16(EPADDR_TD_STATE, ucTD_State);
		ucTD_TimeoutS = 0;
		ucTD_Timeout = Read24C16(EPADDR_TD_TIMEOUT);
//		printf("TD_POSSIBLE_THEFT=%d\r\n",(unsigned short)ucTD_Timeout);
		ucTD_PinFailedCount = 0;
		ucTD_PinFailedTimer = 0;
	}
	else{
		ucTD_State = TD_NORMAL;
		Write24C16(EPADDR_TD_STATE, ucTD_State);
		ucTD_PinFailedCount = 0;
		ucTD_PinFailedTimer = 0;
	}
	
	usTD_PinCodeL = 0;
	usTD_PinCodeH = 0;
}
#endif