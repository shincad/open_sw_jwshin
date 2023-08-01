/*=============================================================*/
/*  KD Line Printer Controller Firmware V2.6                   */
/*  TITLE    : makeeng.c                                       */
/*  ABSTRACT : English Font Loading & Processing Routine       */
/*  AUTHOR(S): Jung-Wook Shin                                  */
/*  DATE     : 1999. 1.                                        */
/*  DEBUG    : 1999. 4.                                        */
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
/*                      MakeEng Routine                        */
/*=============================================================*/

MakeEng(Data)
union INT_UNION Data;
{
	unsigned int FontAdr;
    unsigned int TempValEng;
	int Len;
    int x,i;
    if(Data.Order.ChH >= 0x80) {
    	if(PrtSpeed == SP_410LPM) {
        	FontAdr = FONT_410_ADR + (Data.Order.ChH - ENG_START_CODE)*8*3 +(3*8*3);
            ChImg.Col    = Eng1Font[CpiMode].Col;
            ChImg.Body   = 8;
            ChImg.AdjMod = Eng1Font[CpiMode].AdjMod;
        }
        else {
            if(SemiMode == 1) {
                FontAdr = FONT_SEMI1_ADR + (Data.Order.ChH - SEMI_START_CODE)*
                (SemiFont[CpiMode].Body)*3;
                ChImg.Col    = SemiFont[CpiMode].Col;
                ChImg.Body   = SemiFont[CpiMode].Body;
                ChImg.AdjMod = SemiFont[CpiMode].AdjMod;
                if(CpiMode == 3) {      /* 13.3CPI Adjustment Routine */
                    TempValEng = ChImg.AdjMod + ChImg.AdjRemain;
                    ChImg.AdjRemain = TempValEng % 100;
                    ChImg.Col = SemiFont[CpiMode].Col + (TempValEng/100);
                }
                TabFlag = ENG12;
                /*----------- 1999. 4. 2 ----- debug Shin.. --- */

            } /* if */
            else {
                FontAdr = FONT_SEMI2_ADR + (Data.Order.ChH - SEMI_START_CODE)*
                (SemiFont[CpiMode].Body)*3;
                ChImg.Col    = SemiFont[CpiMode].Col;
                ChImg.Body   = SemiFont[CpiMode].Body;
                ChImg.AdjMod = SemiFont[CpiMode].AdjMod;
                if(CpiMode == 3) {      /* 13.3CPI Adjustment Routine */
                    TempValEng = ChImg.AdjMod + ChImg.AdjRemain;
                    ChImg.AdjRemain = TempValEng % 100;
                    ChImg.Col = SemiFont[CpiMode].Col + (TempValEng/100);
                }
                TabFlag = ENG12;
                /*----------- 1999. 4. 2 ----- debug Shin.. --- */

            } /* else */
        }
    }
    else if(PrtSpeed == SP_410LPM) {
    	FontAdr = FONT_410_ADR + (Data.Order.ChH - ENG_START_CODE)*8*3 +(3*8*3);
        ChImg.Col    = Eng1Font[CpiMode].Col;
        ChImg.Body   = 8;
        ChImg.AdjMod = Eng1Font[CpiMode].AdjMod;
    }
    else {
        switch(EngFont) {
        	case ENG1FONT : FontAdr = FONT_ENG1_ADR + (Data.Order.ChH - ENG_START_CODE)*
            				(Eng1Font[CpiMode].Body)*3;
                            ChImg.Col    = Eng1Font[CpiMode].Col;
                            ChImg.Body   = Eng1Font[CpiMode].Body;
                            ChImg.AdjMod = Eng1Font[CpiMode].AdjMod;
                            if(CpiMode == 3) {      /* 13.3CPI Adjustment Routine */
                                TempValEng = ChImg.AdjMod + ChImg.AdjRemain;
                                ChImg.AdjRemain = TempValEng % 100;
                                ChImg.Col = Eng1Font[CpiMode].Col + (TempValEng/100);
                            }
                            TabFlag = ENG12;
                            break;
            case ENG2FONT : FontAdr = FONT_ENG2_ADR + (Data.Order.ChH - ENG_START_CODE)*
            				(Eng2Font[CpiMode].Body)*3;
                            ChImg.Col    = Eng2Font[CpiMode].Col;
                            ChImg.Body   = Eng2Font[CpiMode].Body;
                            ChImg.AdjMod = Eng2Font[CpiMode].AdjMod;
                            if(CpiMode == 3) {
                                TempValEng = ChImg.AdjMod + ChImg.AdjRemain;
                                ChImg.AdjRemain = TempValEng % 100;
                                ChImg.Col = Eng2Font[CpiMode].Col + (TempValEng/100);
                            }
                            TabFlag = ENG13;
                            break;
            case OCRFONT  : FontAdr = FONT_OCR_ADR + (Data.Order.ChH - ENG_START_CODE)*
            				(OcrFont[CpiMode].Body)*3;
                            ChImg.Col    = OcrFont[CpiMode].Col;
                            ChImg.Body   = OcrFont[CpiMode].Body;
                            ChImg.AdjMod = OcrFont[CpiMode].AdjMod;
                            if(CpiMode == 3) {
                                TempValEng = ChImg.AdjMod + ChImg.AdjRemain;
                                ChImg.AdjRemain = TempValEng % 100;
                                ChImg.Col = OcrFont[CpiMode].Col + (TempValEng/100);
                            }
                            TabFlag = ENG12;
                            break;
            default       : break;
        } /* End Of Switch */
    }
    switch(FontInfo.ScaleState =
    ScaleMode[GetDim3(FontInfo.HTCondense,FontInfo.VTDouble,FontInfo.HTDouble)])
    {
    	case SM_NORMAL              : Len = (ChImg.Body)*3;
                                      memcpy((&(ChImg.Buff[0])),FontAdr,Len);
                                      break;
        case SM_HTDOUBLE            : HTDoubleTB(FontAdr,&ChImg);
                                      break;
        case SM_VTDOUBLE            : VTDoubleTB(FontAdr,&ChImg);
                                      break;
        case SM_HTVTDOUBLE          : HTVTDoubleTB(FontAdr,&ChImg);
                                     /*  HTScaleState = SET; */
                                      break;
        case SM_HTCONDENSE          : HTCondenseTB(FontAdr,&ChImg);
                                      break;
        case SM_VTDOUBLE_HTCONDENSE : VTDoubleTB(FontAdr,&ChImg);
                                      HTCondenseTB(FontAdr,&ChImg);
                                      break;
        default                     : break;
    }
    if(SemiExp == SEMI_EXPAND) {
        ExpNorLoad();
    }
    if((Data.Order.ChH >= 0xB3) && (Data.Order.ChH <= 0xDF)) {
        if(SemiExp == SEMI_EXPAND) {
            VertExpandFlag = SET;
        }
        if(VertExpandFlag == SET) {
            ExpLoad();
            ChImg.Rear = ChImg.Col - ChImg.Body;
            x = ChImg.Body*4;
            for(i=0;i<ChImg.Rear;i++) {
                ChImg.ExpBuff[x]   = ChImg.ExpBuff[(ChImg.Body*4)-4];
                ChImg.ExpBuff[x+1] = ChImg.ExpBuff[(ChImg.Body*4)-3];
                ChImg.ExpBuff[x+2] = ChImg.ExpBuff[(ChImg.Body*4)-2];
                ChImg.ExpBuff[x+3] = ChImg.ExpBuff[(ChImg.Body*4)-1];
                x += 4;
            }
            VertExpandFlag = RESET;
        }
        else {
            ChImg.Rear = ChImg.Col - ChImg.Body;
            x = ChImg.Body*3;
            for(i=0;i<ChImg.Rear;i++) {
                ChImg.Buff[x]   = ChImg.Buff[(ChImg.Body*3)-3];
                ChImg.Buff[x+1] = ChImg.Buff[(ChImg.Body*3)-2];
                ChImg.Buff[x+2] = ChImg.Buff[(ChImg.Body*3)-1];
                x += 3;
            }
        }
    }
    if(FontInfo.UnderLine == SET) {
    	UnderLineMem(&ChImg);
    }
    if(FontInfo.BoldFace == SET) {
        BoldFaceMem(&ChImg);
    }
    if(FontInfo.Shadow == SET) {
        ShadowMem(&ChImg);
    }
    if(FontInfo.Reverse == SET) {
        ReverseMem(&ChImg);
    }
    if(EscSPFlag == SET) {
        ChImg.Col += TempColumn;
    }
    if(ToStImg(&ChImg) == OVER_RANGE) {
    	if(AutoWrap == SET) {
        	LFProc();
            ToStImg(&ChImg);
        }
        else {
            AutoWrapOver = SET;
        }
    }
}
