/*=============================================================*/
/*  KD Line Printer Controller Firmware V2.2                   */
/*  TITLE    : sm_int.c                                        */
/*  ABSTRACT : Slave to Master Interrupt Routine               */
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
/*                    S_M_Interrupt Routine                    */
/*=============================================================*/

unsigned char Step;

void interrupt S_M_Int(void)
{
    unsigned char Data;
    unsigned char Cmd;
    INT_DIS;
    Data = S_M_READ;
    if(Data == STX) {        /* Data Transfer Package */
    	Step = 1;        /* STX/Cmd/[Data]/ETX */
        INT_ENB;
        return;
    }
    else
    if(Data == ETX) {
    	switch(Cmd) {
        	case SET_ITEM        : ItemEvent = SET;
                                   break;
            case SELF_TEST_START : SelfTestEvent = SELF_TEST_START;
                                   break;
            case SELF_TEST_STOP  : SelfTestEvent = SELF_TEST_STOP;
                                   break;
            case CONFIG          : ConfigEvent   = SET;
                                   StartEvent = SET;
                                   break;
            case START           : StartEvent    = SET;
                                   break;
            default              : break;
        }
        Step = 0;
    }
    switch(Step) {
    	case 1 : Cmd   = Data - CMD_WEIGHT;
                 Step  = 2;
                 CmdCt = 0;
                 break;
        case 2 : CmdBuf[CmdCt] = Data - CMD_WEIGHT;
                 CmdCt++;
                 ItemEvent = RESET;
                 break;
    }
    INT_ENB;
}
