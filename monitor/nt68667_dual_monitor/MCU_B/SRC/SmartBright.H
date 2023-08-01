#ifndef _SmartBright_H_
#define  _SmartBright_H_

#define DifferenceBrightness 8	//10 //4	//10
#define deltaBright 45 //20 //0x80		//20//10		Reset counter if large amount of difference occurred
#define BrightTimes 4705 //1200
#define MinBrightValue 0x04 //0x08		//0x10
#define MaxBrightValue 0x30		//0x60


//------------------------------------------
// SMART BRIGHTNESS ( 190P7 ONLY )
//------------------------------------------
#if _SmartBright_ == ON
extern idata bit bSmartBrightEnable;
extern idata bit bSaveSmartBright;
extern xdata unsigned long ulBrightV;
extern xdata unsigned char ucBrightValue;
extern xdata unsigned short usBrightCounter;
extern xdata unsigned char ucTempBrightValue;
extern xdata unsigned char ucSmartBrightStart;
extern xdata unsigned char ucSmartBrightEnd;
extern xdata unsigned char ucBrightADC;
extern xdata unsigned char ucTempBrightADC;
extern xdata unsigned short usBrightOffset;		// 120 indicates +20, 60 indicates -40
				//#define DefaultBrightOffset	100
extern xdata unsigned char ucSmartBrightValue;
//extern xdata unsigned char ucADCCounter;
//extern xdata unsigned char ucBrightADC1;
#endif

#define DefaultBrightOffset	100


void SmartBright(void);

#endif
