/*=============================================================*/
/*  KD Line Printer Controller Firmware V2.2                   */
/*  TITLE    : vtdbtb.c                                        */
/*  ABSTRACT : Vertical Extend Routine                         */
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
/*                    VTDoubleTB Routine                       */
/*=============================================================*/
VTDoubleTB(FontAdr,ChInfo)   /* Vertical Extension */
char *FontAdr;
struct CH_IMG *ChInfo;
{
	int i,x=0;
    for(i=0; i<(ChInfo->Body);i++){
    	ChInfo->Buff[x]     = VTFontTB[(*FontAdr)&0x0F];
        ChInfo->Buff[x+1]   = VTFontTB[((*FontAdr)&0xF0)>>4];
        ChInfo->Buff[x+2]   = VTFontTB[(*(FontAdr+1))&0x0F];
        ChInfo->Buff[x+144] = VTFontTB[((*(FontAdr+1))&0xF0)>>4];
        ChInfo->Buff[x+145] = VTFontTB[(*(FontAdr+2))&0x0F];
        ChInfo->Buff[x+146] = VTFontTB[((*(FontAdr+2))&0xF0)>>4];
        FontAdr += 3;
        x += 3;
    }
}
