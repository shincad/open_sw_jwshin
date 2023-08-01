/*=============================================================*/
/*  KD Line Printer Controller Firmware V2.2                   */
/*  TITLE    : htvtdbtb.c                                      */
/*  ABSTRACT : Horizontal Vertical Expand Routine              */
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
/*                  HTVTDoubleTB Routine                       */
/*=============================================================*/
HTVTDoubleTB(FontAdr,ChInfo)   /* Horizontal , Vertical Extenstion */
char *FontAdr;
struct CH_IMG *ChInfo;
{
	int i,x=0;
	for(i=0; i<(ChInfo->Body); i++){
    	ChInfo->Buff[x]    =ChInfo->Buff[x+3] = VTFontTB[(*FontAdr)&0x0F];
        ChInfo->Buff[x+1]  =ChInfo->Buff[x+4] = VTFontTB[((*FontAdr)&0xF0)>>4];
        ChInfo->Buff[x+2]  =ChInfo->Buff[x+5] = VTFontTB[(*(FontAdr+1))&0x0F];
        ChInfo->Buff[x+216]=ChInfo->Buff[x+219] = VTFontTB[((*(FontAdr+1))&0xF0)>>4];
        ChInfo->Buff[x+217]=ChInfo->Buff[x+220] = VTFontTB[(*(FontAdr+2))&0x0F];
        ChInfo->Buff[x+218]=ChInfo->Buff[x+221] = VTFontTB[((*(FontAdr+2))&0xF0)>>4];
        FontAdr += 3;
        x += 6;
    }
    ChInfo->Col  *= 2;
    ChInfo->Body *= 2;
}
