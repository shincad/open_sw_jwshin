/*=============================================================*/
/*  KD Line Printer Controller Firmware V2.2                   */
/*  TITLE    : sdmem.c                                         */
/*  ABSTRACT : Shadow Font Processing Routine                  */
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
/*                    ShadowMem Routine                        */
/*=============================================================*/
ShadowMem(ChImg)           /* Shadow Character */
struct CH_IMG *ChImg;
{
	int i,Len,x=0;
    Len = ((ChImg->Col)/6);
    if(FontInfo.VTDouble == SET) {
    	if(FontInfo.HTDouble == SET) {
        	for(i=0;i<Len;i++) {
            	ChImg->Buff[x]     |= 0x88;
                ChImg->Buff[x+1]   |= 0x88;
                ChImg->Buff[x+2]   |= 0x88;
                ChImg->Buff[x+12]  |= 0x22;
                ChImg->Buff[x+13]  |= 0x22;
                ChImg->Buff[x+14]  |= 0x22;
                ChImg->Buff[x+216] |= 0x88;
                ChImg->Buff[x+217] |= 0x88;
                ChImg->Buff[x+218] |= 0x88;
                ChImg->Buff[x+228] |= 0x22;
                ChImg->Buff[x+229] |= 0x22;
                ChImg->Buff[x+230] |= 0x22;
                x+=24;
            }
        }
        else {
        	for(i=0;i<Len;i++) {
            	ChImg->Buff[x]     |= 0x88;
                ChImg->Buff[x+1]   |= 0x88;
                ChImg->Buff[x+2]   |= 0x88;
                ChImg->Buff[x+12]  |= 0x22;
                ChImg->Buff[x+13]  |= 0x22;
                ChImg->Buff[x+14]  |= 0x22;
                ChImg->Buff[x+144] |= 0x88;
                ChImg->Buff[x+145] |= 0x88;
                ChImg->Buff[x+146] |= 0x88;
                ChImg->Buff[x+156] |= 0x22;
                ChImg->Buff[x+157] |= 0x22;
                ChImg->Buff[x+158] |= 0x22;
                x+=24;
            }
        }
    }
    else {
    	for(i=0;i<Len;i++) {
        	ChImg->Buff[x]    |= 0x88;
            ChImg->Buff[x+1]  |= 0x88;
            ChImg->Buff[x+2]  |= 0x88;
            ChImg->Buff[x+12] |= 0x22;
            ChImg->Buff[x+13] |= 0x22;
            ChImg->Buff[x+14] |= 0x22;
            x+=24;
        }
    }
}
