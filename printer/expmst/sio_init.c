/*=============================================================*/
/*  KD Line Printer Controller Firmware V2.2                   */
/*  TITLE    : sio_init.c                                      */
/*  ABSTRACT : Serial Initialization Routine                   */
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
/*                    Serial Initialization                    */
/*=============================================================*/

SIOInit()
{
    INT_DIS;
    HRp = 0;
    HWp = 0;
    HProtect = RESET;           /* XON/XOFF */
    ACIACR   = 0x03;   /* Control Register CR1,CR0=1,1 : Mst Reset */
    ACIACR   = 0xD5;   /* Parity Bit=None,Data Bit=8,Stop Bit=1,RTS = L */
                       /* DTR = H */
                       /* Tx interrupt Disable, Rx interrupt Enable */
    INT_ENB;
}
