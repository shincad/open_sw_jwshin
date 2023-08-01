/****************************************************************************/
/*																			*/
/*			Boot Process													*/
/*																			*/
/*			Copyright	:: Phoenix Information Tecjnology					*/
/*			Cpu			:: SH3												*/
/*			Language	:: SHC												*/
/*			File Name	:: boot.c											*/
/*																			*/
/****************************************************************************/
#include "sh7709a.h"
#include "def.h"
#define Extern
#include "ext.h"
#if (_GCC_ == 1)
#include "gmachine3.h"
#endif
#if (_HITACHI_ == 1)
#include <smachine.h>
#endif

/*	Function ProtoType Declaration	*/
extern void ap_main(void);
void boot(void);

/*	Boot Function	*/
										/* SDRAM mode set Address	*/
#define SDMR3  (*(volatile char *)(0xffffe000 + (0x00000220 << 2)))
void boot(void)
{
	
	/* CPG Setting */
	CPG.WTCSR.WORD = 0xa500;		/* WatchDog Timer Stop 			*/
	CPG.WTCSR.WORD = 0xa503;		/* WatchDog Timer Divide Ratio Setting (1/32) 	*/
	CPG.WTCNT = 0x5a80;				/* WatchDog Timer Counter Setting (128)			*/
	CPG.FRQCR.WORD = 0x0112;		/* Clock Ratio  I:B:P = 8:4:2					*/
	
	/*Bus Memory Setting */
	BSC.BCR1.WORD = 0x3008;			/* Area3 SDRAM Access							*/
    BSC.BCR2.WORD = 0x39f0;         /* CS5 Bus Size 16 Bit							*/
									/* CS4 Bus Size 8 Bit 							*/
									/* CS3 Bus Size 32Bit 							*/
	BSC.BCR3.WORD = 0x1010;			/* BCR3 */
	BSC.WCR1.WORD = 0x1551;			/* Idle cycle Area1 = 1 , Area0 = 1		*/
									/* Idle cycle Area3 = 1 , Area2 = 1		*/
									/* Idle cycle Area5 = 1 , Area4 = 1		*/
									/* Idle cycle Area6 = 1					*/
	BSC.WCR2.WORD = 0xffdd;			/* Wait CAS asert time = 2 , Area0 = 6	*/
	BSC.MCR.WORD = 0x5124;			/* RAS-CAS delay 2 Cycle 				*/
									/*  Write Precharge delay 2 Cycle		*/
									/* 4M x 16Bit , CAS before RAS Refresh 	*/
	BSC.DCR.WORD = 0x4000;			/* DCR									*/
	BSC.RTCOR = 0xa53e;				/* 1 reflesh/32us						*/
									/* RTCOR=124 							*/
	BSC.RTCSR.WORD = 0xa510;		/* CKIO=32MHz,  Clock Source =1/16,		*/
									/* INT Disable ACounter Limit Value 1024	*/
	BSC.RFCR = 0xa400;
	while(BSC.RFCR < 30);			/* DRAM Access Wait						*/
	
	SDMR3 = 0x00;					/* SDRAM Mode Setting					*/
	
	/*Cache Setting */
	CCR.LONG = 0x00000008;			/* Cache All Entry Clear 				*/
	CCR.LONG = 0x00000001;			/* 8K Byte Cache ON Write Back 			*/
	
	
	ap_main();							/* main program */
	
	for(;;);
}

/*	Interrupt Disable 	*/
void di()
{
	set_cr((get_cr() | 0x10000000));
}

/*	Interrupt Enable	*/
void ei()
{
	set_cr((get_cr() & (~0x10000000)));
}
