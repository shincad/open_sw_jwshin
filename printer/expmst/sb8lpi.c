/*=============================================================*/
/*  KD Line Printer Controller Firmware V2.5                   */
/*  TITLE    : sb8lpi.c                                        */
/*  ABSTRACT : 8 LPI SendBuff Routine                          */
/*  AUTHOR(S): Jung-Wook Shin                                  */
/*  DATE     : 1999. 2.                                        */
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
/*                    SendBuff8LPI Routine                     */
/*=============================================================*/

char SendBuff8LPI(FontLine,LFLen,LFCt)
unsigned char FontLine;
unsigned int LFLen;
unsigned int *LFCt;
{
	union REG_UNION Reg0;
    unsigned int j,Ct=0;
    while((*LFCt) < FontLine) {
    	SendFIFO(STX);
        SendFIFO(0);
        SendFIFO(5);
        if((*LFCt) == (FontLine-1)) {
        	Reg0.Two = LFLen;
            SendFIFO(Reg0.Order.Hi);
            SendFIFO(Reg0.Order.Low);
        }
        else {
             SendFIFO(0);
             SendFIFO(1);
        }
        for(j=0;j<306;j++) {
             SendFIFO(DisBuff[Ct*306+j]);
        } /* end of for(j) */
        if(OrFlag == SET) {
        	Ct++;
            OrFlag = RESET;
        }
        SendFIFO(ETX);
        if((*LFCt==0)||(*LFCt==4)) {
            for(j=0;j<306;j++) {
                DisBuff[(Ct+1)*306+j] = DisBuff[(Ct+1)*306+j] | DisBuff[(Ct+2)*306+j];
                OrFlag = SET;
            }
        }
/*        if((*LFCt) == 17) {
        	return -1;
        } */
        if(Ct == 7) {
        	(*LFCt)++;
            return 0;
        }
        Ct++;
        (*LFCt)++;
    } /* end of while */
    return -1;
}
