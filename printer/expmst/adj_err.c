/*=============================================================*/
/*  KD Line Printer Controller Firmware V2.2                   */
/*  TITLE    : adjerr.c                                        */
/*  ABSTRACT : LPI Adjustment Routine                          */
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
/*                    AdjLPIErr Routine                        */
/*=============================================================*/

AdjLPIErr(Length)
unsigned char Length;
{
	unsigned int AdjVal;
   	if(LFInfo.AdjMod != 0) {
		AdjVal = LFInfo.AdjMod * Length + LFInfo.AdjRemain;
     	LFInfo.AdjRemain = AdjVal % 100;
    	return(AdjVal / 100);
    }
   	else {
   		return 0;
    }
}
