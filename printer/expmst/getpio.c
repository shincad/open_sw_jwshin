/*=============================================================*/
/*  KD Line Printer Controller Firmware V2.2                   */
/*  TITLE    : getpio.c                                        */
/*  ABSTRACT : This Routine obtain data through Parallel I/F   */
/*  AUTHOR(S): Jung-Wook Shin                                  */
/*  DATE     : 1999. 1.                                        */
/*  Copyright (c) 1996-1999  by  Jung-Wook Shin                */
/*  Printer Lab. Phoenix Information Technology                */
/*  All rights reserved.                                       */
/*=============================================================*/

/*=============================================================*/
/*                  Include Header File                        */
/*=============================================================*/
#include "m_define.h"
#include "mext.h"

/*=============================================================*/
/*                    From GetPIOBuff[] to FIFO                */
/*=============================================================*/

char GetPIOBuff(Ch)     /* Parallel(FIFO) Routine */
unsigned char *Ch;
{
	unsigned char EmptyFlag;
   	unsigned char ExOrVal;
   	EmptyFlag = (M_6821CS & 0x01); /* Flag Check */
   	if(EmptyFlag == 0) {
    	return -1;
   	}
   	*Ch = 0xFF ^ P_RD_FIFO;        /* Signal Reverse */
   	return 0;
}
