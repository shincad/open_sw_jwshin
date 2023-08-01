/*=============================================================*/
/*  KD Line Printer Controller Firmware V2.2                   */
/*  TITLE    : selfslv.c                                       */
/*  ABSTRACT : This Routine transferred Selftest Data from     */
/*             master to slave.                                */
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
/*                  SelfTest to Slave Routine                  */
/*=============================================================*/
SelfSlv(Cmd)
unsigned char Cmd;
{
	union REG_UNION Reg0;
   	SendFIFO(STX);
   	SendFIFO(Cmd);
   	SendFIFO(0);
   	Reg0.Two = 1;
   	SendFIFO(Reg0.Order.Hi);
   	SendFIFO(Reg0.Order.Low);
}
