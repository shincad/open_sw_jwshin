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
#include "FactoryAlignment.h"
#include "Mis.h"  //Mintz 0505
#include "BFControl.H"


//#ifdef NOVATEK_HDCP_WRITER
#include "HDCP.h"
//#endif

#ifdef BenQ_FACTORY
void BenQ_FactoryAlignment(void)
{
//#ifdef PHP_AUTO	
 unsigned short addr;
 unsigned char TempData;

	IIC0_ADDR = BenQ_ADDR;	//stop iic for Alignment busy
	IIC1_ADDR = BenQ_ADDR;	//stop iic for Alignment busy
	SendNullCmd(BenQ_ADDR);
//check sum ok. Vender command
//	printf("%x %x %x %x\r\n",(unsigned short)ucDDCCiRxBuffer[0],(unsigned short)ucDDCCiRxBuffer[1],(unsigned short)ucDDCCiRxBuffer[2],(unsigned short)ucDDCCiRxBuffer[3]);
	ucDDCCiRxChecksum = ucDDCCiRxBuffer[0]+ucDDCCiRxBuffer[1]+ucDDCCiRxBuffer[2];
	if(ucDDCCiRxBuffer[3] != ucDDCCiRxChecksum){
		ucDDCCiTxBuffer[0] = 0xfc;
		ucDDCCiTxBuffer[1] = 0xaa;
		ucDDCCiTxChecksum = 0x50;
		ucDDCCiTxOut = 0;
		ucDDCCiTxIn = 2;
	}
	else{
//		if((ucDDCCiRxBuffer[0] > 0xaf)&&(ucDDCCiRxBuffer[0] < 0xc0)){
		if((ucDDCCiRxBuffer[0] > 0xaf)&&(ucDDCCiRxBuffer[0] < 0xc0)){
			addr = ucDDCCiRxBuffer[0] & 0x07;
			addr <<= 8;
			addr |= ucDDCCiRxBuffer[1];
			if((ucDDCCiRxBuffer[0] & BIT_3) != 0){	//write
				Write24C16(addr,ucDDCCiRxBuffer[2]);
				SendResponseCmd();
			}
			else{
				TempData = Read24C16(addr);
				ucDDCCiTxBuffer[0] = TempData;
				if(ucDDCCiTxBuffer[0] == 0xfc)
					ucDDCCiTxBuffer[1] = 0xcf;
				else
					ucDDCCiTxBuffer[1] = 0xfc;
				ucDDCCiTxChecksum = 0x50;
				ucDDCCiTxOut = 0;
				ucDDCCiTxIn = 2;
			}
		}
		else{
			switch(ucDDCCiRxBuffer[0]){
			case 0xCA:
				switch(ucDDCCiRxBuffer[1]){
				case 0x55:
					ucContrast = ucDDCCiRxBuffer[2];
					SetContrastRGB();
					break;
				case 0x56:
					ucBrightness = ucDDCCiRxBuffer[2];
					SetBrightness();
#if _SmartBright_ == ON
					SetBrightOffset();
#endif
					break;
				case 0x57:
					ucR_Gain = ucDDCCiRxBuffer[2];
					SetContrastRGB();
					break;
				case 0x58:
					ucG_Gain = ucDDCCiRxBuffer[2];
					SetContrastRGB();
					break;
				case 0x59:
					ucB_Gain = ucDDCCiRxBuffer[2];
					SetContrastRGB();
					break;
				case 0x9c:
					ucBrightness = ucDDCCiRxBuffer[2];
					SetBrightness();
					Write24C16(EPADDR_BRIGHT_USER, ucBrightness);
					Write24C16(EPADDR_BRIGHT_SRGB, ucBrightness);
#if _SmartBright_ == ON
					SetBrightOffset();
#endif
					break;
				}
				break;
			case 0xC3:
				switch(ucDDCCiRxBuffer[1]){
				case 0x55:
					ucDDCCiRxBuffer[2] = ucContrast;
					break;
				case 0x56:
					ucDDCCiRxBuffer[2] = ucBrightness;
					break;
				case 0x57:
					ucDDCCiRxBuffer[2] = ucR_Gain;
					break;
				case 0x58:
					ucDDCCiRxBuffer[2] = ucG_Gain;
					break;
				case 0x59:
					ucDDCCiRxBuffer[2] = ucB_Gain;
					break;
				case 0x9c:
					ucBrightness = Read24C16(EPADDR_BRIGHT_USER);
					ucDDCCiRxBuffer[2] = ucBrightness;
					SetBrightness();
#if _SmartBright_ == ON
					SetBrightOffset();
#endif
					break;
				}
				break;
			case 0xAA:
				TempData = ucDDCCiRxBuffer[1];
				if(TempData < 0x0d){
					ucSerialNum[TempData] = ucDDCCiRxBuffer[2];
					Write24C16(EPADDR_SN0+TempData,ucDDCCiRxBuffer[2]);
				}
				else{
					switch(ucDDCCiRxBuffer[1]){
					case 0x3c:
						ucR_Gain = ucDDCCiRxBuffer[2];
						SetContrastRGB();
						ucR_Gain9300K = ucR_Gain;
						Write24C16(EPADDR_RGAIN_9300, ucR_Gain);
						break;
					case 0x3d:
						ucG_Gain = ucDDCCiRxBuffer[2];
						SetContrastRGB();
						ucG_Gain9300K = ucG_Gain;
						Write24C16(EPADDR_GGAIN_9300, ucG_Gain);
						break;
					case 0x3e:
						ucB_Gain = ucDDCCiRxBuffer[2];
						SetContrastRGB();
						ucB_Gain9300K = ucB_Gain;
						Write24C16(EPADDR_BGAIN_9300, ucB_Gain);
						break;
					case 0x4c:
						ucR_Gain = ucDDCCiRxBuffer[2];
						SetContrastRGB();
						ucR_GainsRGB = ucR_Gain;
						Write24C16(EPADDR_RGAIN_SRGB, ucR_Gain);
						break;
					case 0x4d:
						ucG_Gain = ucDDCCiRxBuffer[2];
						SetContrastRGB();
						ucG_GainsRGB = ucG_Gain;
						Write24C16(EPADDR_GGAIN_SRGB, ucG_Gain);
						break;
					case 0x4e:
						ucB_Gain = ucDDCCiRxBuffer[2];
						SetContrastRGB();
						ucB_GainsRGB = ucB_Gain;
						Write24C16(EPADDR_BGAIN_SRGB, ucB_Gain);
						break;
					case 0x5c:
						ucR_Gain = ucDDCCiRxBuffer[2];
						SetContrastRGB();
						ucR_Gain6500K = ucR_Gain;
						Write24C16(EPADDR_RGAIN_6500, ucR_Gain);
						break;
					case 0x5d:
						ucG_Gain = ucDDCCiRxBuffer[2];
						SetContrastRGB();
						ucG_Gain6500K = ucG_Gain;
						Write24C16(EPADDR_GGAIN_6500, ucG_Gain);
						break;
					case 0x5e:
						ucB_Gain = ucDDCCiRxBuffer[2];
						SetContrastRGB();
						ucB_Gain6500K = ucB_Gain;
						Write24C16(EPADDR_BGAIN_6500, ucB_Gain);
						break;
					case 0x6c:
						ucR_Gain = ucDDCCiRxBuffer[2];
						SetContrastRGB();
						ucR_GainUser = ucR_Gain;
						Write24C16(EPADDR_RGAIN_USER, ucR_Gain);
						break;
					case 0x6d:
						ucG_Gain = ucDDCCiRxBuffer[2];
						SetContrastRGB();
						ucG_GainUser = ucG_Gain;
						Write24C16(EPADDR_GGAIN_USER, ucG_Gain);
						break;
					case 0x6e:
						ucB_Gain = ucDDCCiRxBuffer[2];
						SetContrastRGB();
						ucB_GainUser = ucB_Gain;
						Write24C16(EPADDR_BGAIN_USER, ucB_Gain);
						break;
					case 0x92:
						ucContrast = ucDDCCiRxBuffer[2];
						SetContrastRGB();
						ucSavePointer = svCONTRAST;
						SaveData();
						break;
					case 0x93:
						ucBrightness = ucDDCCiRxBuffer[2];
						SetBrightness();
						ucSavePointer = svBRIGHTNESS;
						SaveData();
						break;
					case 0x94:
						switch(ucDDCCiRxBuffer[2]){
						case 0x01:
							ucColorTemperature = COLOR_5000;
							break;
						case 0x02:
							ucColorTemperature = COLOR_6500;
							break;
						case 0x03:
							ucColorTemperature = COLOR_7500;
							break;
						case 0x04:
							ucColorTemperature = COLOR_8200;
							break;
						case 0x05:
							ucColorTemperature = COLOR_9300;
							break;
						case 0x06:
							ucColorTemperature = COLOR_11500;
							break;
						case 0x07:
							ucColorTemperature = COLOR_ORIGIN;
							break;
						case 0x08:
							ucColorTemperature = COLOR_SRGB;
							break;
						case 0x09:
							ucColorTemperature = COLOR_USER;
							break;
						}
						SetColorTemp(ucColorTemperature);
						Write24C16(EPADDR_COLOR_TEMP, ucColorTemperature);
						break;
					case 0x95:
						ucOSDXPos = ucDDCCiRxBuffer[2];
						SetPosition(ucOSDXPos,ucOSDYPos);
						Write24C16(EPADDR_OSDX, ucOSDXPos);
						break;
					case 0x96:
						ucOSDYPos = ucDDCCiRxBuffer[2];
						SetPosition(ucOSDXPos,ucOSDYPos);
						Write24C16(EPADDR_OSDY, ucOSDYPos);
						break;
					case 0x97:
						ucLanguage = ucDDCCiRxBuffer[2];
						if(ucLanguage > 7)
							ucLanguage = 0;
						Write24C16(EPADDR_OSDLANG,ucLanguage);
						break;
					case 0x98:
						ucOSDTimer = ucDDCCiRxBuffer[2];
						Write24C16(EPADDR_OSDTIMER, ucOSDTimer);
						break;
					case 0x99:
						ucVolume = ucDDCCiRxBuffer[2];
						SetVolume();
						Write24C16(EPADDR_VOLUME, ucVolume);		   
						break;
					case 0x9c:
						ucBrightness = ucDDCCiRxBuffer[2];
						SetBrightness();
						Write24C16(EPADDR_BRIGHT_USER, ucBrightness);
						Write24C16(EPADDR_BRIGHT_SRGB, ucBrightness);
#if _SmartBright_ == ON
						SetBrightOffset();
#endif
						break;
					case 0x9e:
						ucTransparency = ucDDCCiRxBuffer[2];
						if(ucTransparency > 4)
							ucTransparency = 4;
						SetTransparency();
						Write24C16(EPADDR_TRANSPARENCY,ucTransparency);
						break;
					}
				}
				break;
			case 0xA3:
				TempData = ucDDCCiRxBuffer[1];
				if(TempData < 0x0d){
					ucDDCCiRxBuffer[2] = ucSerialNum[TempData];
				}
				else{
					switch(ucDDCCiRxBuffer[1]){
					case 0x3c:
						ucR_Gain = Read24C16(EPADDR_RGAIN_9300);
						SetContrastRGB();
						ucR_Gain9300K = ucR_Gain;
						ucDDCCiRxBuffer[2] = ucR_Gain;
						break;
					case 0x3d:
						ucG_Gain = Read24C16(EPADDR_GGAIN_9300);
						SetContrastRGB();
						ucG_Gain9300K = ucG_Gain;
						ucDDCCiRxBuffer[2] = ucG_Gain;
						break;
					case 0x3e:
						ucB_Gain = Read24C16(EPADDR_BGAIN_9300);
						SetContrastRGB();
						ucB_Gain9300K = ucB_Gain;
						ucDDCCiRxBuffer[2] = ucB_Gain;
						break;
					case 0x4c:
						ucR_Gain = Read24C16(EPADDR_RGAIN_SRGB);
						SetContrastRGB();
						ucR_GainsRGB = ucR_Gain;
						ucDDCCiRxBuffer[2] = ucR_Gain;
						break;
					case 0x4d:
						ucG_Gain = Read24C16(EPADDR_GGAIN_SRGB);
						SetContrastRGB();
						ucG_GainsRGB = ucG_Gain;
						ucDDCCiRxBuffer[2] = ucG_Gain;
						break;
					case 0x4e:
						ucB_Gain = Read24C16(EPADDR_BGAIN_SRGB);
						SetContrastRGB();
						ucB_GainsRGB = ucB_Gain;
						ucDDCCiRxBuffer[2] = ucB_Gain;
						break;
					case 0x5c:
						ucR_Gain = Read24C16(EPADDR_RGAIN_6500);
						SetContrastRGB();
						ucR_Gain6500K = ucR_Gain;
						ucDDCCiRxBuffer[2] = ucR_Gain;
						break;
					case 0x5d:
						ucG_Gain = Read24C16(EPADDR_GGAIN_6500);
						SetContrastRGB();
						ucG_Gain6500K = ucG_Gain;
						ucDDCCiRxBuffer[2] = ucG_Gain;
						break;
					case 0x5e:
						ucB_Gain = Read24C16(EPADDR_BGAIN_6500);
						SetContrastRGB();
						ucB_Gain6500K = ucB_Gain;
						ucDDCCiRxBuffer[2] = ucB_Gain;
						break;
					case 0x6c:
						ucR_Gain = Read24C16(EPADDR_RGAIN_USER);
						SetContrastRGB();
						ucR_GainUser = ucR_Gain;
						ucDDCCiRxBuffer[2] = ucR_Gain;
						break;
					case 0x6d:
						ucG_Gain = Read24C16(EPADDR_GGAIN_USER);
						SetContrastRGB();
						ucG_GainUser = ucG_Gain;
						ucDDCCiRxBuffer[2] = ucG_Gain;
						break;
					case 0x6e:
						ucB_Gain = Read24C16(EPADDR_BGAIN_USER);
						SetContrastRGB();
						ucB_GainUser = ucB_Gain;
						ucDDCCiRxBuffer[2] = ucB_Gain;
						break;
					case 0x92:
						ucContrast = Read24C16(EPADDR_CONTRAST);
						SetContrastRGB();
						ucDDCCiRxBuffer[2] = ucContrast;
						break;
					case 0x93:
						ucBrightness = Read24C16(EPADDR_BRIGHT);
						SetBrightness();
						ucDDCCiRxBuffer[2] = ucBrightness;
						break;
					case 0x94:
						ucColorTemperature = Read24C16(EPADDR_COLOR_TEMP);
						SetColorTemp(ucColorTemperature);
						ucDDCCiRxBuffer[2] = ucColorTemperature;
						break;
					case 0x95:
						ucOSDXPos = Read24C16(EPADDR_OSDX);
						SetPosition(ucOSDXPos,ucOSDYPos);
						ucDDCCiRxBuffer[2] = ucOSDXPos;
						break;
					case 0x96:
						ucOSDYPos = Read24C16(EPADDR_OSDY);
						SetPosition(ucOSDXPos,ucOSDYPos);
						ucDDCCiRxBuffer[2] = ucOSDYPos;
						break;
					case 0x97:
						ucLanguage = Read24C16(EPADDR_OSDLANG);
						ucDDCCiRxBuffer[2] = ucLanguage;
						break;
					case 0x98:
						ucOSDTimer = Read24C16(EPADDR_OSDTIMER);
						ucDDCCiRxBuffer[2] = ucOSDTimer;
						break;			
					case 0x99:
						ucVolume = Read24C16(EPADDR_VOLUME);		
						SetVolume();
						ucDDCCiRxBuffer[2] = ucVolume;
						break;
					case 0x9c:
						ucBrightness = Read24C16(EPADDR_BRIGHT_USER);
						SetBrightness();
						ucDDCCiRxBuffer[2] = ucBrightness;
#if _SmartBright_ == ON
						SetBrightOffset();
#endif
						break;
					case 0x9e:
						ucTransparency = Read24C16(EPADDR_TRANSPARENCY);
						SetTransparency();
						ucDDCCiRxBuffer[2] = ucTransparency;
						break;
					}
				}
				break;
			case 0xCC:
				switch(ucDDCCiRxBuffer[1]){
				case 0x01:
					ucColorTemperature = COLOR_5000;
         			break;
				case 0x02:
					ucColorTemperature = COLOR_6500;
					break;
				case 0x03:
					ucColorTemperature = COLOR_7500;
					break;
				case 0x04:
					ucColorTemperature = COLOR_8200;
					break;
				case 0x05:
					ucColorTemperature = COLOR_9300;
					break;
				case 0x06:
					ucColorTemperature = COLOR_11500;
					break;
				case 0x07:
					ucColorTemperature = COLOR_ORIGIN;
					break;
				case 0x08:
					ucColorTemperature = COLOR_SRGB;
					break;
				case 0x09:
					ucColorTemperature = COLOR_USER;
          			break;
      			}
				SetColorTemp(ucColorTemperature);
				Write24C16(EPADDR_COLOR_TEMP, ucColorTemperature);
				break;
			case 0xCD:
				switch(ucDDCCiRxBuffer[1]){
				case 0x01:
					GoToSeparateSync();
					break;
				case 0x02:
					GoToDVI();
					break;
          		}
				break;
			case 0xCE:
				if(ucDDCCiRxBuffer[1] == 1){
					bIsBurnInEnabled = TRUE;
					Write24C16(EPADDR_BURNIN,bIsBurnInEnabled);				
				}
          		else{
					bIsBurnInEnabled = FALSE;
					Write24C16(EPADDR_BURNIN,bIsBurnInEnabled);				
//					Write24C16(EPADDR_FACTORY, 0 );
				}
          		break;
			case 0xCF:
				if(ucDDCCiRxBuffer[1] == 1){
					OSD_OFF();
					PowerSaving();
//					ClearNewModeLED();
//					LED_GrnOff();					// -jwshin 111213
//					LED_RedOn();
					bForceToSleep= TRUE;
					//printf("force to sleep=%d\r\n",(unsigned short)ucSignalType);
     			}
				else{
					bForceToSleep = FALSE;
					ScalerPowerUp();
         		}
				break;
			case 0x11:
				if(ucDDCCiRxBuffer[1]==0x5a)
					AutoTune();
				break;
			case 0x1A:
				if(ucDDCCiRxBuffer[1] == 0x5a)
					AutoColor();
				break;
			case 0x1B:
				if(ucDDCCiRxBuffer[1] == 0x5a)
					AutoColor();
				break;
			case 0x1E:
				if(ucDDCCiRxBuffer[1] == 0x5a)
					ReleaseFactoryMode();
				break;
			case 0x1F:
				if(ucDDCCiRxBuffer[1] == 0x5a){
					Recall();
					FactoryReset();
				}
           		break;
			case 0xAE:
				switch(ucDDCCiRxBuffer[1]){
				case 0x13:
					ucDDCCiRxBuffer[2] = 255 - ucR_ADC_Offset;
					break;
				case 0x14:
					ucDDCCiRxBuffer[2] = 255 - ucG_ADC_Offset;
					break;
				case 0x15:
					ucDDCCiRxBuffer[2] = 255 - ucB_ADC_Offset;
					break;
				case 0x33:
					ucDDCCiRxBuffer[2] = 255 - ucR_ADC_Gain;
					break;
				case 0x34:
					ucDDCCiRxBuffer[2] = 255 - ucG_ADC_Gain;
					break;
				case 0x35:
					ucDDCCiRxBuffer[2] = 255 - ucB_ADC_Gain;
					break;
          		}
				break;
			case 0xAF:
				switch(ucDDCCiRxBuffer[1]){
				case 0x13:
					ucR_ADC_Offset = 255 - ucDDCCiRxBuffer[2];
					WriteIIC560(ROFFSET,ucR_ADC_Offset);
					Write24C16(EPADDR_ADCR_OFFSET,ucR_ADC_Offset);
					break;
				case 0x14:
					ucG_ADC_Offset = 255 - ucDDCCiRxBuffer[2];
					WriteIIC560(GOFFSET,ucG_ADC_Offset);
					Write24C16(EPADDR_ADCG_OFFSET,ucG_ADC_Offset);
					break;
				case 0x15:
					ucB_ADC_Offset = 255 - ucDDCCiRxBuffer[2];
					WriteIIC560(BOFFSET,ucB_ADC_Offset);
					Write24C16(EPADDR_ADCB_OFFSET,ucB_ADC_Offset);
					break;
				case 0x33:
					ucR_ADC_Gain = 255 - ucDDCCiRxBuffer[2];
					WriteIIC560(RGAIN_HI,ucR_ADC_Gain);
					Write24C16(EPADDR_ADCR_GAIN,ucR_ADC_Gain);
					break;
				case 0x34:
					ucG_ADC_Gain = 255 - ucDDCCiRxBuffer[2];
					WriteIIC560(GGAIN_HI,ucG_ADC_Gain);
					Write24C16(EPADDR_ADCG_GAIN,ucG_ADC_Gain);
					break;
				case 0x35:
					ucB_ADC_Gain = 255 - ucDDCCiRxBuffer[2];
					WriteIIC560(BGAIN_HI,ucB_ADC_Gain);
					Write24C16(EPADDR_ADCB_GAIN,ucB_ADC_Gain);
					break;
          		}
				break;
			case 0xFF:
				if((ucDDCCiRxBuffer[1]==0x04)&&(ucDDCCiRxBuffer[2]==0x00))
					InitEEPROM(0);
				break;
			}
			SendResponseCmd();
		}
	}
	if((IIC0_ADDR == BenQ_ADDR)||(IIC1_ADDR == BenQ_ADDR)){	//restart Alignment

		IIC0_ADDR = BenQ_ADDR;			//stop iic for Alignment busy
		IIC0_ADDR = BenQ_ADDR | ENIIC;
		IIC0INT_CLR = 0xff;
		IIC0_INT_EN = 0xf8;
		IIC1_ADDR = BenQ_ADDR;			//stop iic for Alignment busy
		IIC1_ADDR = BenQ_ADDR | ENIIC;
		IIC1INT_CLR = 0xff;
		IIC1_INT_EN = 0xf8;
	}
}


void SendResponseCmd(void)
{
	Set_usTimer1_1ms(100);
	while(ucDDCCiTxOut != 0){
		if(Get_usTimer1_1ms() == 0)
            break;
	}

	ucDDCCiTxBuffer[0] = ucDDCCiRxBuffer[2];
	if(ucDDCCiTxBuffer[0] == 0xfc)
		ucDDCCiTxBuffer[1] = 0xcf;
	else
		ucDDCCiTxBuffer[1] = 0xfc;
	ucDDCCiTxChecksum = 0x50;
	ucDDCCiTxOut = 0;
	ucDDCCiTxIn = 2;
		
}

void BenQ_EnterFactoryMode(void)
{
	bFactoryModeType = FACTORY_4BYTE;
//	EDIDa_WP_OFF();
//	EDIDb_WP_OFF();
/////////////////////////////////////////////////////////

	IIC0_ADDR = BenQ_ADDR;			//stop iic for Alignment busy
	IIC0_ADDR = BenQ_ADDR | ENIIC;
	IIC0INT_CLR = 0xff;
	IIC0_INT_EN = 0xf8;
	IIC1_ADDR = BenQ_ADDR;			//stop iic for Alignment busy
	IIC1_ADDR = BenQ_ADDR | ENIIC;
	IIC1INT_CLR = 0xff;
	IIC1_INT_EN = 0xf8;
	SendNullCmd(BenQ_ADDR);
//////////////////////////////////////////////////////////
//	printf("EntryFactoryMode %x\r\n",(unsigned short)IIC0_ADDR);
}
#endif


