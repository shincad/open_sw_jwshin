/*=============================================================*/
/*  KD Line Printer Controller Firmware V2.2                   */
/*  TITLE    : chkpio.c                                        */
/*  ABSTRACT : Parallel Buffer Check Routine                   */
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
/*                   CheckPIOBuff Routine                      */
/*=============================================================*/
CheckPIOBuff()
{
	unsigned char EmptyFlag;
   	EmptyFlag = (M_6821CS & 0x01);   /* FIFO Flag Check */
   	if(EmptyFlag == 0) {
   		return EMPTY;
   	}
   	else {
      	return NOTEMPTY;
   	}
}
