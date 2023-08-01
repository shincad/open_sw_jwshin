/*=============================================================*/
/*  KD Line Printer Controller Firmware V2.2                   */
/*  TITLE    : lfproc.c                                        */
/*  ABSTRACT : Line Feed Procedure Routine                     */
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
/*                     LFProc() Routine                        */
/*=============================================================*/

LFProc()
{
	TabCt = 0;
    AutoClrCtr();
    switch(BitImgMode) {
    	case NOT_BITIMG : /* Not Bit Image */
                          break;
        case BITIMG_8   : StImg.Part     = 0;    /* 8 Bit Image */
                          StImg.Pos      = Margin.Left;
                          StImg.HaveVT   = RESET;
                          StImg.HaveVTUp = RESET;
                          SendStImg(8,STIMG_NOSWAP);
                          ClrStImg(8);
                          BitImgMode     = NOT_BITIMG;
                          return;
        case BITIMG_24  : StImg.Part     = 0;    /* 24 Bit Image */
                          StImg.Pos      = Margin.Left;
                          StImg.HaveVT   = RESET;
                          StImg.HaveVTUp = RESET;
                          SendStImg(24,STIMG_NOSWAP);
                          ClrStImg(24);
						  BitImgMode     = NOT_BITIMG;
                          return;
        default:          break;
    }
    if(EmptyImgBuff == SET) {
    	LFInfo.Sum++;
        if(LFInfo.Sum > MAX_LF_RANGE) {
        	SendSlave(LF_CMD);
            LFInfo.Sum = 0;
        }
    	return;
    }
    EmptyImgBuff = SET;
    if(StImg.Part == 0) {
    	if((StImg.HaveVTUp == SET) && (StImg.HaveVT == RESET)) {
        	StImg.Part     = 1;
            StImg.Pos      = Margin.Left;
            StImg.HaveVTUp = RESET;
        }
        else
        if(StImg.HaveVT   == SET) {
            StImg.Pos      = Margin.Left;
            StImg.HaveVT   = RESET;
            StImg.HaveVTUp = RESET;
            SendStImg(DOUBLE_BUFF,STIMG_SWAP);
            ClrStImg(DOUBLE_BUFF);
        }
        else {
            StImg.Pos = Margin.Left;
            SendStImg(SINGLE_BUFF,STIMG_NOSWAP);
            memset((&StImg.Buff[0]),0,7344);    	/* String Image Buffer Clear */
            if(SemiExp == SEMI_EXPAND) {
                memset((&StImg.ExpBuff[0]),0,9792);
            }
        }
    }
    else {
    	StImg.Part     = 0;
        StImg.Pos      = Margin.Left;
        StImg.HaveVT   = RESET;
        StImg.HaveVTUp = RESET;
        SendStImg(DOUBLE_BUFF,STIMG_NOSWAP);
        ClrStImg(DOUBLE_BUFF);
    }
    if(EscJFlag == SET) {									/* Esc J Flag */
    	LFInfo.DotLenOfLine = EscJTemp;
        EscJFlag = RESET;
    }
}
