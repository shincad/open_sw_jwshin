/*=============================================================*/
/*  KD Line Printer Controller Firmware V2.2                   */
/*  TITLE    : htdbtb.c                                        */
/*  ABSTRACT : Horizontal Expand Routine                       */
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
/*                     HTDoubleTB Routine                      */
/*=============================================================*/
HTDoubleTB(FontAdr,ChInfo)   /* Horizontal Extenstion */
char *FontAdr;
struct CH_IMG *ChInfo;
{
	int i,x=0;
    for(i=0; i<ChInfo->Body; i++){
    	ChInfo->Buff[x]   = ChInfo->Buff[x+3] = *FontAdr;
        ChInfo->Buff[x+1] = ChInfo->Buff[x+4] = *(FontAdr+1);
        ChInfo->Buff[x+2] = ChInfo->Buff[x+5] = *(FontAdr+2);
        FontAdr += 3;
        x += 6;
    }
    ChInfo->Col  *= 2;
    ChInfo->Body *= 2;
}
