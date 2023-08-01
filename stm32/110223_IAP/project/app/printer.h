//---------------------------------------------
//
//		IQS I/O Board Firmware
//		FileName : Printer.h
//		Version : 1.00
//
//		Date   : 2010.12.17
//		Author : Shin Jung Wook
//						 DNP System.	
//						 
//---------------------------------------------
#ifndef	_PRINTER_H
#define _PRINTER_H

#include "stm32f10x_lib.h"

#define PrinterMsgLocator		    0x803c000;

typedef struct _PRINT_COUNT
{
 	union P_C
	{
        struct cByte{
			u8 c[4];

		};
		u32 cnt;

	};
//	u32 iCnt;
}PRINT_COUNTER,*P_PRINT_COUNTER;

extern void PrinterTest(void);
extern void PrinterLine(void);
extern void SetPrintCounter(u32 count);
extern void GetPrintCounter(void);
extern void	SetMessageSize(u8 mode,u16 size);
extern void AbnormalLine(void);
extern void PrintTest(void);
extern void WriteMessage(u8 mode,u16 index,u16 size);

extern u8 WriteDumpData(u8 *p,u16 size);

extern void SaveIndex(u8* p);
extern void	GetPrinterSensor(void);
extern void    SendDump(void);
extern void 	PrinterOut(void);
extern void PrinterOut2(void);			// +jwshin 110110
extern void 	PrinterInit(void);

extern void SendTime(void);				// +jwshin 110106
extern void SendPrtDump(void);
extern void PrintDumpTest1(void);

extern void WriteDumpFlash(void);		// +jwshin 110111

extern PRINT_COUNTER pcnt;

extern u8 PrinterSensor;
#endif
