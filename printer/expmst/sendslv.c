/*=============================================================*/
/*  KD Line Printer Controller Firmware V2.2                   */
/*  TITLE    : sendslv.c                                       */
/*  ABSTRACT : This Routine transferred Printer Setting Value  */
/*             from master to slave.                           */
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
/*                     SendSlave Routine                       */
/*=============================================================*/
SendSlave(Value)
unsigned char Value;
{
	union REG_UNION Reg0;
    SendFIFO(STX);              /* Start Code to Slave */
    SendFIFO(0);                /* Normal Code to Slave */
    switch(Value) {
    	case LPI_CMD :  SendFIFO(LPI_CMD);      /* Change LPI */
                        Reg0.Two = LFInfo.DotLenOfLine;
                        SendFIFO(Reg0.Order.Hi);   /* High 1 Byte */
                        SendFIFO(Reg0.Order.Low);  /* Low  1 Byte */
                        break;
        case PL_CMD  :  SendFIFO(PL_CMD);       /* Change Paper Length */
                        Reg0.Two = PageLen;
                        SendFIFO(Reg0.Order.Hi);
                        SendFIFO(Reg0.Order.Low);
                        break;
        case LF_CMD  :  SendFIFO(LF_CMD);       /* Line Feed */
                        Reg0.Two = (LFInfo.DotLenOfLine * LFInfo.Sum +
                        AdjLPIErr(LFInfo.Sum));
                        SendFIFO(Reg0.Order.Hi);
                        SendFIFO(Reg0.Order.Low);
                        break;
        case FF_CMD  :  SendFIFO(FF_CMD);       /* Form Feed */
                        SendFIFO(0);
                        SendFIFO(1);
                        break;
        case DATA_FF_CMD : SendFIFO(DATA_FF_CMD);
                           SendFIFO(0);
                           SendFIFO(1);
                           break;
    }
}
