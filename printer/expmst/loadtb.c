/*=============================================================*/
/*  KD Line Printer Controller Firmware V2.2                   */
/*  TITLE    : loadtb.c                                        */
/*  ABSTRACT : Font Loading Routine                            */
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
/*                  LoadTB Routine (Font Loading)              */
/*=============================================================*/
LoadTB(FontAdr,ChInfo)    /* Font Loading */
char *FontAdr;
struct CH_IMG *ChInfo;
{
	int i = 0;
    int Len;
    Len = (ChInfo->Body)*3;
    memcpy((&(ChInfo->Buff[i])),FontAdr,Len);
}
