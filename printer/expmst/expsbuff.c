/*=============================================================*/
/*  KD Line Printer Controller Firmware V2.2                   */
/*  TITLE    : expsbuff.c                                      */
/*  ABSTRACT : Expand Font Printing Routine                    */
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
/*                    ExpSendBuff Routine                      */
/*=============================================================*/

char ExpSendBuff(FontLine,LFLen,LFCt)
unsigned char FontLine;
unsigned int LFLen;
unsigned int *LFCt;
{
	union REG_UNION Reg0;
    unsigned int j,Ct=0;
    unsigned char *Temp;
    while((*LFCt) < (FontLine+LFLen-1)) {
    	SendFIFO(STX);
        SendFIFO(0);
        SendFIFO(5);
        SendFIFO(0);
        SendFIFO(1);
        for(j=0;j<306;j++) {
            SendFIFO(DisBuff[Ct*306+j]);
        } /* end of for(j) */
        SendFIFO(ETX);
        if(Ct == 7) {
        	(*LFCt)++;
            return 0;
        }
        Ct++;
        (*LFCt)++;
    } /* end of while */
    return -1;
}
