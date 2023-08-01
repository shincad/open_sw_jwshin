/*=============================================================*/
/*  KD Line Printer Controller Firmware V2.2                   */
/*  TITLE    : bfmem.c                                         */
/*  ABSTRACT : BoldFace Font Loading Routine                   */
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
/*                    BoldFaceMem Routine                      */
/*=============================================================*/
BoldFaceMem(ChImg)         /* BoldFace Character */
struct CH_IMG *ChImg;
{
	int i,x=0;
   	if(FontInfo.VTDouble == SET) {       /* Vertical Double Extension */
   		if(FontInfo.HTDouble == SET) {   /* Horizontal Double Extension */
      		for(i=0;i<ChImg->Col;i++) {
         		ChImg->Buff[x]     |= ChImg->Buff[x+3];
            	ChImg->Buff[x+1]   |= ChImg->Buff[x+4];
            	ChImg->Buff[x+2]   |= ChImg->Buff[x+5];
            	ChImg->Buff[x+216] |= ChImg->Buff[x+219];
            	ChImg->Buff[x+217] |= ChImg->Buff[x+220];
            	ChImg->Buff[x+218] |= ChImg->Buff[x+221];
            	x += 6;
         	} /* for */
      	} /* if */
    	else {
			for(i=0;i<ChImg->Col;i++) {
        		ChImg->Buff[x]     |= ChImg->Buff[x+3];
         		ChImg->Buff[x+1]   |= ChImg->Buff[x+4];
         		ChImg->Buff[x+2]   |= ChImg->Buff[x+5];
         		ChImg->Buff[x+144] |= ChImg->Buff[x+147];
         		ChImg->Buff[x+145] |= ChImg->Buff[x+148];
         		ChImg->Buff[x+146] |= ChImg->Buff[x+149];
         		x += 6;
        	} /* for */
    	} /* else */
   	} /* if */
   	else {                      /* Normal Character */
   		for(i=0;i<ChImg->Col;i++) {
      		ChImg->Buff[x]   |= ChImg->Buff[x+3];
         	ChImg->Buff[x+1] |= ChImg->Buff[x+4];
         	ChImg->Buff[x+2] |= ChImg->Buff[x+5];
         	x += 6;
      	} /* for */
   	} /* else */
}
