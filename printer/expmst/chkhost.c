/*=============================================================*/
/*  KD Line Printer Controller Firmware V2.2                   */
/*  TITLE    : chkhost.c                                       */
/*  ABSTRACT : Serial and Parallel check Routine               */
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
/*                   CheckHostBuff Routine                     */
/*=============================================================*/
CheckHostBuff()
{
	if(HostPortMod == SERIAL_PORT) {
   		EmptyState = CheckSIOBuff();  /* Serial Buffer Check */
   	}
   	else {
    	EmptyState = CheckPIOBuff();  /* Parallel FIFO Flag Check */
   	}
   	return EmptyState;
}
