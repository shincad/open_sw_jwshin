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

   2003-01-10 2:39오후  JDHAN           Modified for Monitor-TV
****************************************************************************/

//****************************************************************//
//화일참조
//****************************************************************//
#include	"TopHeader.h"
#include "extern.h"


#if		defined(MCU_MTV230)
#include	"MTV230xfr.h"
#elif		defined(MCU_MTV412)
#include	"MTV412xfr.h"
#elif		defined(MCU_NT68F63)
#include	"NT68F63.h"
#endif
#include	"eepromadr.h"

#ifdef	AD9883			//AD9883 ADC
#define	DirectHS


//****************************************************************//
//함수선언
//****************************************************************//
BYTE EEPROM_Read(WORD address);
bit WriteI2C(BYTE sysaddr, BYTE subaddr, BYTE writedata);

#ifdef	USE_4BitInterface								//4bit통신 함수선언
void	WriteReg4bit(BYTE address, BYTE Recdata);
#define	WriteScaler(val1,val2) WriteReg4bit(val1,val2)	
BYTE	ReadScalerParallel(BYTE address);
#define	ReadScaler	ReadScalerParallel

#else													//1bit통신 함수선언
void	WriteReg1bit(BYTE address, BYTE Recdata);
#define	WriteScaler(val0, val1) WriteReg1bit(val0, val1)
BYTE	ReadScalerSerial(BYTE address);
#define	ReadScaler	ReadScalerSerial
#endif


//****************************************************************//
//변수선언
//****************************************************************//




void SetADCBias(BYTE RecRED,BYTE RecGRN,BYTE RecBLU)	//Offset set, Bigger vales give less brightness @AD9883
{
	WriteI2C(ADC_sysaddress,0x0B,RecRED<<1);
	WriteI2C(ADC_sysaddress,0x0C,RecGRN<<1);
	WriteI2C(ADC_sysaddress,0x0D,RecBLU<<1);
}

void SetADCGain(BYTE RecRED,BYTE RecGRN,BYTE RecBLU)	//Gain set, Bigger values give less contrast @AD9883
{
	WriteI2C(ADC_sysaddress,0x08,RecRED);
	WriteI2C(ADC_sysaddress,0x09,RecGRN);
	WriteI2C(ADC_sysaddress,0x0A,RecBLU);
}

void SetADCColorReg(void)
{
	//ColorTemperature
	if(xEEPROMBuffer[ColorTemp]==0)     {SetADCGain(114,127,127);SetADCBias(0x32,0x32,0x32);}//6500K,warm
	//{SetADCGain(122,145,200);SetADCBias(0x32,0x32,0x32);}//6500K,warm
	else if(xEEPROMBuffer[ColorTemp]==1)	{SetADCGain(127,127,114);SetADCBias(0x32,0x32,0x32);}//9300K,cool
	//{SetADCGain(147,120,164);SetADCBias(0x32,0x32,0x32);}//9300K,cool
	else//USER MODE                        
	{
		#ifdef	AdcGainSlope
			//SetADCGain((0xfc-(xEEPROMBuffer[ADCREDGAIN_buf]*3.6)),(0xfc-(xEEPROMBuffer[ADCGREENGAIN_buf]*3.6)),(0xfc-(xEEPROMBuffer[ADCBLUEGAIN_buf]*3.6)));
			SetADCGain((0xff-(xEEPROMBuffer[ADCREDGAIN_buf]*2.55)),(0xff-(xEEPROMBuffer[ADCGREENGAIN_buf]*2.55)),(0xff-(xEEPROMBuffer[ADCBLUEGAIN_buf]*2.55)));
			SetADCBias(0x32,0x32,0x32);
		#else
			SetADCGain((0xff-xEEPROMBuffer[ADCREDGAIN_buf]),(0xff-xEEPROMBuffer[ADCGREENGAIN_buf]),(0xff-xEEPROMBuffer[ADCBLUEGAIN_buf]));
			SetADCBias(0x32,0x32,0x32);
		#endif
	}
}

void SetADCControlReg(void)
{
	WriteI2C(ADC_sysaddress,0x0F, 0x2A);	//check Bit5(In spec(AD9883) must be set to "0", but other sources set to "1")
	WriteI2C(ADC_sysaddress,0x05, 0x10);	//Clamp placement
	WriteI2C(ADC_sysaddress,0x06, 0x10);	//Clamp duration
	WriteI2C(ADC_sysaddress,0x07, 0x20);	//HsyncWidth
	//WriteI2C(ADC_sysaddress,0x0F, 0x2E);	//check Bit5(In spec(AD9883) must be set to "0", but other sources set to "1")
	#ifdef	DirectHS						//Fr DSUB
	WriteI2C(ADC_sysaddress,0x0E,0x00);
	#else									//Fr u-com
	WriteI2C(ADC_sysaddress,0x0E,0x00);
	#endif
	
	WriteI2C(ADC_sysaddress,0x15, 0x02);	//YUV &&
}

void SetADCPhaseReg(BYTE Recdata)
{
	WORD idata AdcFreq;
	
	WriteI2C(ADC_sysaddress,0x04,Recdata<<3);

/*
		**AD9883
		Freq				VCO	CURRENT
		F<31.5Mhz			00	101
		31.5Mhz<=F<40.0Mhz	00	110
		40.0Mhz<=F<56.2Mhz	01	100	
		56.2Mhz<=F<65.0Mhz	01	101
		65.0Mhz<=F<75.0Mhz	01	110
		75.0Mhz<=F<108.0Mhz	10	100
		F>=108.0Mhz			10	110

Reg0x03	Bit[7:6]VCO,Bit[5:3]CURRENT
*/
	AdcFreq=((DWORD)ModeList[CurrentMode].HF*ModeList[CurrentMode].HTotal)/1000;
	
	     if(AdcFreq<315) AdcFreq=(0<<6)|(5<<3);
	else if(AdcFreq<400) AdcFreq=(0<<6)|(6<<3);
	else if(AdcFreq<562) AdcFreq=(1<<6)|(4<<3);
	else if(AdcFreq<650) AdcFreq=(1<<6)|(5<<3);
	else if(AdcFreq<750) AdcFreq=(1<<6)|(6<<3);
	else if(AdcFreq<1080) AdcFreq=(2<<6)|(4<<3);
	else AdcFreq=(2<<6)|(6<<3);
	WriteI2C(ADC_sysaddress,0x03,AdcFreq);
}

void SetLinerate(BYTE Recdata)
{
WORD	IV_TOTAL;
unsigned int OV_TOTAL ;
DWORD	LINERATE;

	switch(Recdata)
	{
		case	0:
		case	1:
		case	2:
		case	3:
		case	4:
		case	6:
		case	20://RGB+COMPOSITE
		case	28://RGB+SVIDEO
		case	52://RGB +TUNER
		case	22://RGB+COMPOSITE(NO)
		case	30://RGB+SVIDEO(NO)
			IV_TOTAL=((ReadScaler(0x6F)&0x07)<<8)|ReadScaler(0x70);
			OV_TOTAL = (float)(PanelVerticalsize/(float)NowVactive) * (float)IV_TOTAL ;

			LINERATE = ((0x80000000/(((NowHtotal-1+1)/2)*2)) * OV_TOTAL /IV_TOTAL);
			LINERATE <<= 2;
			WriteScaler(0x31,LINERATE>>24); 
			WriteScaler(0x32,LINERATE>>16); 
			WriteScaler(0x33,LINERATE>>8); 
			WriteScaler(0x34,LINERATE);
			break;
		
		case	8://composite linesync
		case	10://composite framesync
		case	12://s-video linesync
		case	14://s-video framesync
		case	16://tuner linesync
		case	18://tuner framesync
		
			LINERATE = ((0xfffffffful/858)/((DWORD)BIVAW)) * (PanelVerticalsize*2);
			WriteScaler(0x31,LINERATE>>24); 
			WriteScaler(0x32,LINERATE>>16); 
			WriteScaler(0x33,LINERATE>>8); 
			WriteScaler(0x34,LINERATE);
			break;

		default:
			break;
	}
}

void SetADCHtotal(WORD Recdata)
{
	//ADC total set
	WriteI2C(ADC_sysaddress,0x01,(BYTE)(Recdata>>4));
	WriteI2C(ADC_sysaddress,0x02,(BYTE)((Recdata<<4)&0xF0));
	SetLinerate(xEEPROMBuffer[MainSubInputSource]);
}

#endif
