/*=============================================================*/
/*  KD Line Printer Controller Firmware V2.2                   */
/*  TITLE    : tostimg.c                                       */
/*  ABSTRACT : Character Buffer to String Buffer Transference  */
/*  AUTHOR(S): Jung-Wook Shin                                  */
/*  DATE     : 1999. 1.                                        */
/*  Debugging: 1999. 3.                                        */
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
/*                      ToStImg Routine                        */
/*=============================================================*/

ToStImg(ChImg)
struct CH_IMG *ChImg;
{
	int x,i;
    unsigned int Len,Dest;
    if((StImg.Pos + (ChImg->Col)) > (PAPER_DOT_WIDTH - Margin.Right)) {
    	return OVER_RANGE;
    }
    if(StImg.Part == 0) {
    	if(FontInfo.VTUp == SET) {
        	CopyToStImg(ST_IMG_PART0_BASE,CH_IMG_PART0_BASE,ChImg->Col);
            StImg.HaveVTUp = SET;
        }
        else
        if(FontInfo.VTDn == SET) {
            CopyToStImg(ST_IMG_PART0_BASE,CH_IMG_PART1_BASE,ChImg->Col);
        }
        else
        if(FontInfo.VTDouble == SET) {
            if(FontInfo.HTDouble == SET) {
            	CopyToStImg(ST_IMG_PART1_BASE,CH_IMG_PART0_BASE,ChImg->Col);
                StImg.Pos -= ChImg->Col;
                CopyToStImg(ST_IMG_PART0_BASE,216,ChImg->Col);
                StImg.HaveVT = SET;
            }
            else {
                CopyToStImg(ST_IMG_PART1_BASE,CH_IMG_PART0_BASE,ChImg->Col);
                StImg.Pos -= ChImg->Col;
                CopyToStImg(ST_IMG_PART0_BASE,CH_IMG_PART1_BASE,ChImg->Col);
                StImg.HaveVT = SET;
            }
        }
        else {
                if(SemiExp == SEMI_EXPAND) {
                    Len = (ChImg->Col*4);
                    Dest = StImg.Pos*4;
                    memcpy( &(StImg.ExpBuff[Dest]), &(ChImg->ExpBuff[0]),Len);
                    memset( &(ChImg->ExpBuff[0]), 0 , Len);
                    memset( &(ChImg->Buff[0]) , 0 , (ChImg->Col*3));
                    StImg.Pos += ChImg->Col;
                }
                else {
                    Len = (ChImg->Col*3);
                    Dest = StImg.Pos*3;
                    memcpy( &(StImg.Buff[Dest]), &(ChImg->Buff[0]),Len);
                    memset( &(ChImg->Buff[0]), 0 , Len);
                    StImg.Pos += ChImg->Col;
                }
        }
    }  /* End Of If(StImg.Part == 0) */
    else {  /* if(StImg.Part == 1) */
    	if(FontInfo.VTUp == SET) {
        	if(FontInfo.VTDn == SET) {
                if(FontInfo.HTDouble == SET) {
                    CopyToStImg(ST_IMG_PART1_BASE,216,ChImg->Col);
                }
                else {
                    CopyToStImg(ST_IMG_PART1_BASE,CH_IMG_PART1_BASE,ChImg->Col);
                }
            }
            else {
                CopyToStImg(ST_IMG_PART1_BASE,CH_IMG_PART0_BASE,ChImg->Col);
            }
        }
        else
        if(FontInfo.VTDn == SET) {
                CopyToStImg(ST_IMG_PART1_BASE,CH_IMG_PART1_BASE,ChImg->Col);
        }
        else
        if(FontInfo.VTDouble == SET) {
                CopyToStImg(ST_IMG_PART1_BASE,CH_IMG_PART1_BASE,ChImg->Col);
        }
        else {
                CopyToStImg(ST_IMG_PART1_BASE,CH_IMG_PART0_BASE,ChImg->Col);
        }
    }  /* End Of If(StImg.Part == 1) */
    EmptyImgBuff = RESET;
}
