/*=============================================================*/
/*  KD Line Printer Controller Firmware V2.2                   */
/*  TITLE    : gethost.c                                       */
/*  ABSTRACT : This Routine obtain data through Host Buffer    */
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
/*                    GetHostBuff Routine                      */
/*=============================================================*/
unsigned char GetHostBuff()
{
	unsigned char Data;
    if(HostPortMod == SERIAL_PORT) {
    	while(GetSIOBuff(&Data) == -1);  /* Serial Port */
    }
    else {
        while(GetPIOBuff(&Data) == -1);  /* Parallel Port */
    }
    return Data;       /* 1 Byte Data */
}
