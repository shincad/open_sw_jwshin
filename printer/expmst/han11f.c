/*=============================================================*/
/*  KD Line Printer Controller Firmware V2.2                   */
/*  TITLE    : han11f.c                                        */
/*  ABSTRACT : Hangul 10CPI 1:1 Conversion Routine             */
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
/*                 10 Cpi 1 : 1  Routine                       */
/*=============================================================*/
Han11Func(FontAdr,ChInfo)    /* Hangul Condensing */
char *FontAdr;
struct CH_IMG *ChInfo;
{
	int x=0,i,Len;
    for(i=0; i<8; i++){
    	ChInfo->Buff[x]    = *FontAdr;
        ChInfo->Buff[x+1]  = *(FontAdr+1);
        ChInfo->Buff[x+2]  = *(FontAdr+2);
        ChInfo->Buff[x+3]  = *(FontAdr+3) | *(FontAdr+6);
        ChInfo->Buff[x+4]  = *(FontAdr+4) | *(FontAdr+7);
        ChInfo->Buff[x+5]  = *(FontAdr+5) | *(FontAdr+8);
        FontAdr += 9;
        x       += 6;
    }
}
