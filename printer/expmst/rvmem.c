/*=============================================================*/
/*  KD Line Printer Controller Firmware V2.2                   */
/*  TITLE    : rvmem.c                                         */
/*  ABSTRACT : Font Reverse Routine                            */
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
/*                    ReverseMem Routine                       */
/*=============================================================*/
ReverseMem(ChImg)        /* Reverse Character */
struct CH_IMG *ChImg;
{
	int i,Len;
    Len = ChImg->Col * 3;
    if(FontInfo.VTDouble == SET) {
    	if(FontInfo.HTDouble == SET) {
        	for(i=0;i<Len;i++) {
            	ChImg->Buff[i]     ^= 0xFF;
                ChImg->Buff[216+i] ^= 0xFF;
            }
        }
        else {
        	for(i=0;i<Len;i++) {
        		ChImg->Buff[i]     ^= 0xFF;
            	ChImg->Buff[144+i] ^= 0xFF;
        	}
        }
    }
    else {
    	for(i=0;i<Len;i++) {
        	ChImg->Buff[i] ^= 0xFF;
        }
    }
}
