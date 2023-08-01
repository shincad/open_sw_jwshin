#include "RAM.H"
#include "MyDef.H"
#include "NT686xx_MCU_REG.H"
#include "NVRAM.H"
#include "Board.H"
//#include "stdio.H"
#include "8051.H"
#include "Rom_map.H"
#include "math.H"
#include "SmartBright.H"
#include "Scaler.H"
#include "OSD.H"

//#define SmartBrightDebug
#ifdef SmartBrightDebug
	#define NVTprintf(s) printf(s)
	#define NVTprintf1(s,a1) printf(s,a1)
	#define NVTprintf2(s,a1,a2) printf(s,a1,a2)
#else
	#define NVTprintf(s)
	#define NVTprintf1(s,a)
	#define NVTprintf2(s,a1,a2)
#endif

//------------------------------------------
// SMART BRIGHTNESS ( 190P7 ONLY )
//------------------------------------------
#if _SmartBright_ == ON
idata bit bSmartBrightEnable;
idata bit bSaveSmartBright;
xdata unsigned long ulBrightV;
xdata unsigned char ucBrightValue;
xdata unsigned short usBrightCounter;
xdata unsigned char ucTempBrightValue;
xdata unsigned char ucSmartBrightStart;
xdata unsigned char ucSmartBrightEnd;
xdata unsigned char ucBrightADC;
xdata unsigned char ucTempBrightADC;
xdata unsigned short usBrightOffset;
xdata unsigned char ucSmartBrightValue;
//xdata unsigned char ucADCCounter;
//xdata unsigned char ucBrightADC1;
#endif


//
//	ucBrightADC = input from light sensor [0..127]
//
//	ucBrightValue = average for Range(ucBrightADC) for BrightTimes time [MinBrightValue..MaxBrightValue] (covered by 0..127)
//	
//	ucSmartBrightValue [MinBrightness..MaxBrightness]
//
//	ucSmartBrightStart = ucBrightness NOW
//
//	ucSmartBrightEnd = ucBrightness Final
//
//	usBrightOffset = 100    +/-    | ucSmartBrightValue - ucBrightness(Final) |
//
//
#if _SmartBright_ == ON

void SmartBright(void)
{
unsigned short temp;
	if((ucColorTemperature != COLOR_SRGB)&&(bSmartBrightEnable == ON)){
		if(abs(ucTempBrightADC-ucBrightADC) > deltaBright){
			//printf("Counter reset=%d,last=%d\r\n",(unsigned short)ucBrightADC ,(unsigned short)ucTempBrightADC);
			usBrightCounter = 0;
			ulBrightV = 0;
			ucTempBrightADC = ucBrightADC;
		}
		ulBrightV += ucBrightADC;
		if(++usBrightCounter > BrightTimes){
			usBrightCounter = 0;
			ucTempBrightValue = (unsigned char)((float)ulBrightV / BrightTimes + 0.5);
			ulBrightV = 0;
			//printf("BrightValue = %d,ucTempBrightValue=%d\r\n",(unsigned short)ucBrightValue,(unsigned short)ucTempBrightValue);
			//if(abs(ucTempBrightValue-ucBrightValue) > deltaBright){
			if(abs(ucTempBrightValue-ucBrightValue) > DifferenceBrightness){
				ucBrightValue = ucTempBrightValue;
				if(ucBrightValue > MaxBrightValue)
					ucBrightValue = MaxBrightValue;
				else if(ucBrightValue < MinBrightValue)
					ucBrightValue = MinBrightValue;
				ucSmartBrightStart = ucBrightness;
				ucSmartBrightValue = (unsigned char)((float)(ucMaxBrightness - (ucMinBrightness+20)) * (ucBrightValue - MinBrightValue) / (MaxBrightValue - MinBrightValue) + (ucMinBrightness+20) + 0.5);
				if(abs(ucSmartBrightStart - ucSmartBrightValue) > DifferenceBrightness){
//					ucSmartBrightEnd = ucSmartBrightValue;
					temp = (unsigned short)ucSmartBrightValue + usBrightOffset;
					if(temp < 100)
						temp = 0;
					else
						temp -= 100;
					if(temp > ucMaxBrightness)
						ucSmartBrightEnd = ucMaxBrightness;
					else if(temp < ucMinBrightness)
						ucSmartBrightEnd = ucMinBrightness;
					else
						ucSmartBrightEnd = temp;

					bSaveSmartBright = 1;
					//printf("ucSmartBrightStart = %d\r\n",(unsigned short)ucSmartBrightStart);
					//printf("ucSmartBrightEnd = %d\r\n",(unsigned short)ucSmartBrightEnd);
					//printf("ucSmartBrightValue = %d\r\n",(unsigned short)ucSmartBrightValue);
					//printf("usBrightOffset = %d\r\n",(unsigned short)usBrightOffset);
				}
				else{
					ucSmartBrightEnd = ucSmartBrightStart;
				}
			}
		}
		if(ucSmartBrightStart > ucSmartBrightEnd){	//down
			ucSmartBrightStart--;
			ucBrightness = ucSmartBrightStart;
			SetBrightness();
		}
		else if(ucSmartBrightStart < ucSmartBrightEnd){	//up
			ucSmartBrightStart++;
			ucBrightness = ucSmartBrightStart;
			SetBrightness();
		}
		else{
			if(bSaveSmartBright == 1){
				bSaveSmartBright = 0;
				if (bFactoryMode)		ucSavePointer = svBRIGHTNESS_F;	//Brightness
				else					ucSavePointer = svBRIGHTNESS;		//Brightness
				SaveData();
				//Write24C16(EPADDR_BRIGHT,ucBrightness);//0x08 = brightness
				//Write24C16(EPADDR_BRIGHT_USER,ucBrightness);//0x36 = brightness user
				NVTprintf("bSaveSmartBright\r\n");
			}
		}
	}
}

#endif
