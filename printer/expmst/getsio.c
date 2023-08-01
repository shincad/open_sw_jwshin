/*=============================================================*/
/*  KD Line Printer Controller Firmware V2.2                   */
/*  TITLE    : getsio.c                                        */
/*  ABSTRACT : This Routine obtain data through Serial I/F     */
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
/*                    From HostBuff[] to FIFO                  */
/*=============================================================*/

char GetSIOBuff(Ch)
unsigned char *Ch;
{
	if(HRp == HWp) {          /* Read Pointer == Write Pointer */
    	return -1;
    }
    *Ch = HostBuff[HRp++];    /* from HostBuff Data reading */
    if(HRp > MAX_HBUFF) {     /* Ring Buffer Structure */
        HRp = 0;
    }
    if(HProtect == SET) {
    	Gap = HWp - HRp;
        if(Gap >= 0) {
        	if(Gap < P_LIVE) {
            	HProtect = RESET;
                if(Protocol == DTR_MODE) {
                	 ACIACR = 0x95; /* DTR = L */
                }
                else {
                	while((ACIASR & 0x02) != 0);
                    ACIADR = XON;
                    ACIADR = XON;
                    ACIADR = XON;
                }
            }
        }
        else {
        	if(Gap < -N_LIVE) {
            	HProtect = RESET;
                if(Protocol == DTR_MODE) {
                	ACIACR = 0x95;
                }
                else {
                    while((ACIASR & 0x02) != 0);
                    ACIADR = XON;
                    ACIADR = XON;
                    ACIADR = XON;
                }
            }
        }
    }
    return 0;
}
