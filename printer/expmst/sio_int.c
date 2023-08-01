/*=============================================================*/
/*  KD Line Printer Controller Firmware V2.2                   */
/*  TITLE    : sio_int.c                                       */
/*  ABSTRACT : Serial Interrupt Routine                        */
/*  AUTHOR(S): Jung-Wook Shin                                  */
/*  DATE     : 1999. 1.                                        */
/*  Copyright (c) 1996-1999  by  Jung-Wook Shin                */
/*  Printer Lab. Phoenix Information Technology                */
/*  All rights reserved.                                       */
/*=============================================================*/

/*=============================================================*/
/*                   Include Header File                       */
/*=============================================================*/
#include "m_define.h"
#include "mext.h"

/*=============================================================*/
/*                  Serial Interrupt Routine                   */
/*=============================================================*/

void interrupt Serial(void)
{
	INT_DIS;
    while((ACIASR & 0x01) != 1);      /* Received data register full */
    HostBuff[HWp++] = ACIADR;         /* From Data Register to Buffer */
    if(HWp > MAX_HBUFF) {
    	HWp = 0;
    }
    Gap = HWp - HRp;
    if(Gap >= 0) {
    	if((Gap > P_DEAD) && (HProtect == RESET)) {
        	HProtect = SET;
            if(Protocol == DTR_MODE) {
            	ACIACR = 0xD5;  /* DTR = H */
            }
            else {
                while((ACIASR & 0x02) != 0);
                ACIADR = XOFF;
            }
        }
    }
    else {
    	if((Gap > -N_DEAD) && (HProtect == RESET)) {
        	HProtect = SET;
            if(Protocol == DTR_MODE) {
            	ACIACR = 0xD5;
            }
            else {
            	while((ACIASR & 0x02) != 0);
                ACIADR = XOFF;
            }
        }
    }
    INT_ENB;
}

void interrupt Parallel(void)
{
}
