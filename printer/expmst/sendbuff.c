/*=============================================================*/
/*  KD Line Printer Controller Firmware V2.2                   */
/*  TITLE    : sendbuff.c                                      */
/*  ABSTRACT : Send Buffer(LP Engine) Routine                  */
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
/*                    SendBuff Routine                         */
/*=============================================================*/

char SendBuff(FontLine,LFLen,LFCt)
unsigned char FontLine;
unsigned int LFLen;
unsigned int *LFCt;
{
	union REG_UNION Reg0;
    unsigned int j,Ct=0;
    unsigned char *Temp;
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
        Temp = DisBuff;
        for(j=0;j<6;j++) {
        	SendFIFO(*(Temp+(Ct*306)));
            Temp++;
            SendFIFO(*(Temp+(Ct*306)));
            Temp++;
            SendFIFO(*(Temp+(Ct*306)));
            Temp++;
            SendFIFO(*(Temp+(Ct*306)));
            Temp++;
            SendFIFO(*(Temp+(Ct*306)));
            Temp++;
            SendFIFO(*(Temp+(Ct*306)));
            Temp++;
            SendFIFO(*(Temp+(Ct*306)));
            Temp++;
            SendFIFO(*(Temp+(Ct*306)));
            Temp++;
            SendFIFO(*(Temp+(Ct*306)));
            Temp++;
            SendFIFO(*(Temp+(Ct*306)));
            Temp++;
            SendFIFO(*(Temp+(Ct*306)));
            Temp++;
            SendFIFO(*(Temp+(Ct*306)));
            Temp++;
            SendFIFO(*(Temp+(Ct*306)));
            Temp++;
            SendFIFO(*(Temp+(Ct*306)));
            Temp++;
            SendFIFO(*(Temp+(Ct*306)));
            Temp++;
            SendFIFO(*(Temp+(Ct*306)));
            Temp++;
            SendFIFO(*(Temp+(Ct*306)));
            Temp++;
            SendFIFO(*(Temp+(Ct*306)));
            Temp++;
            SendFIFO(*(Temp+(Ct*306)));
            Temp++;
            SendFIFO(*(Temp+(Ct*306)));
            Temp++;
            SendFIFO(*(Temp+(Ct*306)));
            Temp++;
            SendFIFO(*(Temp+(Ct*306)));
            Temp++;
            SendFIFO(*(Temp+(Ct*306)));
            Temp++;
            SendFIFO(*(Temp+(Ct*306)));
            Temp++;
            SendFIFO(*(Temp+(Ct*306)));
            Temp++;
            SendFIFO(*(Temp+(Ct*306)));
            Temp++;
            SendFIFO(*(Temp+(Ct*306)));
            Temp++;
            SendFIFO(*(Temp+(Ct*306)));
            Temp++;
            SendFIFO(*(Temp+(Ct*306)));
            Temp++;
            SendFIFO(*(Temp+(Ct*306)));
            Temp++;
            SendFIFO(*(Temp+(Ct*306)));
            Temp++;
            SendFIFO(*(Temp+(Ct*306)));
            Temp++;
            SendFIFO(*(Temp+(Ct*306)));
            Temp++;
            SendFIFO(*(Temp+(Ct*306)));
            Temp++;
            SendFIFO(*(Temp+(Ct*306)));
            Temp++;
            SendFIFO(*(Temp+(Ct*306)));
            Temp++;
            SendFIFO(*(Temp+(Ct*306)));
            Temp++;
            SendFIFO(*(Temp+(Ct*306)));
            Temp++;
            SendFIFO(*(Temp+(Ct*306)));
            Temp++;
            SendFIFO(*(Temp+(Ct*306)));
            Temp++;
            SendFIFO(*(Temp+(Ct*306)));
            Temp++;
            SendFIFO(*(Temp+(Ct*306)));
            Temp++;
            SendFIFO(*(Temp+(Ct*306)));
            Temp++;
            SendFIFO(*(Temp+(Ct*306)));
            Temp++;
            SendFIFO(*(Temp+(Ct*306)));
            Temp++;
            SendFIFO(*(Temp+(Ct*306)));
            Temp++;
            SendFIFO(*(Temp+(Ct*306)));
            Temp++;
            SendFIFO(*(Temp+(Ct*306)));
            Temp++;
            SendFIFO(*(Temp+(Ct*306)));
            Temp++;
            SendFIFO(*(Temp+(Ct*306)));
            Temp++;
            SendFIFO(*(Temp+(Ct*306)));
            Temp++;
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
