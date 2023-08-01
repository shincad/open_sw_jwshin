//---------------------------------------------
//
//		IQS I/O Board Firmware
//		FileName : Util.h
//		Version : 1.00
//
//		Date   : 2010.12.17
//		Author : Shin Jung Wook
//						 DNP System.	
//						 
//---------------------------------------------
#ifndef	_UTIL_H
#define	_UTIL_H

#include "stm32f10x_type.h"
#define ON  1
#define OFF 0

#define	NORMAL_MODE		1
#define	OFFLINE_MODE	0

typedef  void (*pFunction)(void);

extern vu32*	pWriter;
extern vu32 AppAdr;

extern void 	UtilInit(void);
extern void 	SetLedBits(char Freq,char NewBits);
//extern void     SetPower(u8 on);
extern u8     SetPower(u8 on);
extern vu8     Sensor;
extern void    TogglePower(u8 pin);
extern void    ClearCom1TimeOut(void);
extern void   	SetCom1TimeOut(int timeout);
extern void    CheckPowerSwitch(void);
extern void CheckDevicePower(void);		// +jwshin 110106
extern void P24V_ON(u8 pin);			// +jwshin 110104
extern void P5V_ON(u8 pin);


extern void GetCloseSensor(void);		// +jwshin 110107

extern volatile unsigned int   DelayTick;

//#define PrinterHeadMsgLocator		0x803d000;
//#define PrinterMidMsgLocator		0x803e000;
//#define PrinterTaleMsgLocator		0x803f000;

#define ApplicationAddress 			0x8002000

#define	FlashWriterAddressLocator	0x2000BFF0
#define	FlashWriterStackLocator		0x2000BFF4
#define	DownloadCodeSizeLocator		0x2000BFF8
#define	DownloadClassLocator		0x2000BFFC

extern void	JumpToApp(void);
extern void	JumpToWriter(void);
extern void SetWriterPara(vu32 Address);

extern void u32ToHex(u32 in);
extern u8 GetHex(u8 in);
extern u8 HexOut[8];
extern u32 GetBCD32(u16 count);
extern u16 GetBCD16(u8 count);

extern u8	LoopMode;

extern void SavePMode(u8 mode,u16 time);
extern void RestoreMode(void);

///////////////////////////////////////////////////
extern char EmerLedFlag;				// +jwshin 110112
extern char PeriPheralFlag;				// +jwshin 110104
extern char LedStatus;
extern  char PowerOnEvent;
extern  char PowerOffEvent;

extern void SetPowerOn(void);
extern void SetPowerOff(void);			// +jwshin 101217
extern void SetPowerOff2(void);			// +jwshin 101229
extern u8  GetPcPower(void);
extern void    delay(int time);


extern void 	FeedDog(void);
extern u8 Com2Tick;

extern u8 PowerOffOneTime;				// +jwshin 110106

#endif
