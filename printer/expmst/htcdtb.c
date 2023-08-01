/*=============================================================*/
/*  KD Line Printer Controller Firmware V2.2                   */
/*  TITLE    : htcdtb.c                                        */
/*  ABSTRACT : Horizontal Condensing Routine                   */
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
/*                  HTCondenseTB Routine                       */
/*=============================================================*/
HTCondenseTB(FontAdr,ChInfo)    /* Horizontal Condensing */
char *FontAdr;
struct CH_IMG *ChInfo;
{
	int x=0,i,Len;
    Len = ChInfo->Body/2;
    for(i=0; i<Len; i++){
    	ChInfo->Buff[x]   = *FontAdr     | *(FontAdr+3);
        ChInfo->Buff[x+1] = *(FontAdr+1) | *(FontAdr+4);
        ChInfo->Buff[x+2] = *(FontAdr+2) | *(FontAdr+5);
        FontAdr += 6;
        x += 3;
    }
    if(ChInfo->Body==13){
        ChInfo->Buff[x]   = *FontAdr;
        ChInfo->Buff[x+1] = *(FontAdr+1);
        ChInfo->Buff[x+2] = *(FontAdr+2);
        ChInfo->Body = 7;
        ChInfo->Col /= 2;
    }
    else{
        ChInfo->Body /= 2;
        ChInfo->Col  /= 2;
    }
}
