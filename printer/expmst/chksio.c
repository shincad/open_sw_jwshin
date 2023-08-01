/*=============================================================*/
/*  KD Line Printer Controller Firmware V2.2                   */
/*  TITLE    : chksio.c                                        */
/*  ABSTRACT : Serial Check Routine                            */
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
/*                   CheckSIOBuff Routine                      */
/*=============================================================*/
CheckSIOBuff()
{
	if(HRp == HWp) {
   		return EMPTY;  /* Read Pointer == Write Pointer */
   	}
   	else {
     	return NOTEMPTY; /* Read Pointer != Write Pointer */
   	}
}
