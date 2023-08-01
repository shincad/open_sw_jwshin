/*=============================================================*/
/*  KD Line Printer Controller Firmware V2.2                   */
/*  TITLE    : ulmem.c                                         */
/*  ABSTRACT : UnderLine Processing Routine                    */
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
/*                    UnderLineMem Routine                     */
/*=============================================================*/
UnderLineMem(ChImg)      /* UnderLine Character */
struct CH_IMG *ChImg;
{
	int i,x;
    if(PrtSpeed == SP_410LPM) {
    	if(FontInfo.VTDouble == SET) {
        	if(FontInfo.HTDouble == SET) {
            	x = 2;
                for(i=0;i<ChImg->Col;i++) {
                	ChImg->Buff[x] |= 0x80;
                    x += 3;
                }
            }
            else {
            	x = 2;
                for(i=0;i<ChImg->Col;i++) {
                	ChImg->Buff[x] |= 0x80;
                    x += 3;
                }
            }
        }
        else {
        	x = 1;
            for(i=0;i<ChImg->Col;i++) {
            	ChImg->Buff[x] |= 0x08;
                x += 3;
            }
        }
    }
    else {
    	if(FontInfo.VTDouble == SET) {
        	if(FontInfo.HTDouble == SET) {
            	x = 218;
                for(i=0;i<ChImg->Col;i++) {
                	ChImg->Buff[x] |= 0x80;
                    x += 3;
                }
            }
            else {
            	x = 146;
                for(i=0;i<ChImg->Col;i++) {
                	ChImg->Buff[x] |= 0x80;
                    x += 3;
                }
            }
        }
        else {
        	x = 2;
            for(i=0;i<ChImg->Col;i++) {
            	ChImg->Buff[x] |= 0x80;
                x += 3;
            }
        }
    }
}
