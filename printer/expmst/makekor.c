/*=============================================================*/
/*  KD Line Printer Controller Firmware V2.5                   */
/*  TITLE    : makekor.c                                       */
/*  ABSTRACT : Hangul Font Loading & Processing Routine        */
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
/*                      MakeKor Routine                        */
/*=============================================================*/
MakeKor(Data)
union INT_UNION Data;
{
	unsigned int FontAdr;
	unsigned int OffSet1;
	unsigned int OffSet2;
    int TempVal;
	int Len;
    int x,i;
    TabFlag = KOR24;
    if((Data.Order.ChL == 0x0A0) || (Data.Order.ChL == 0x0FF)) {
    	Data.Tow = 0xB0A0;
    }
    if((Data.Order.ChL >= 0x00) && (Data.Order.ChL <= 0x9F)) {
        Data.Tow = 0xB0A0;
    }
    if((0x0B0 <= Data.Order.ChH) && (Data.Order.ChH <= 0x0C8)) {
        if(HanFont == GODIC) {
            OffSet1  = (Data.Order.ChH - 0x0B0) * 11520;
            OffSet2  = (Data.Order.ChH - 0x0B0) * 2 * 24 * 3;
            FontAdr  = FONT_GKOR_ADR + (Data.Tow - KOR_START_CODE)*
            (KorFont[CpiMode].Body)*3 - OffSet1 - OffSet2;
        }
        else {
            OffSet1  = (Data.Order.ChH - 0x0B0) * 11520;
            OffSet2  = (Data.Order.ChH - 0x0B0) * 2 * 24 * 3;
            FontAdr = FONT_MKOR_ADR + (Data.Tow - KOR_START_CODE)*
            (KorFont[CpiMode].Body)*3 - OffSet1 - OffSet2;
        }
        /*    FontPart = KOR_PART; */
    }
    else
    if((0xCA <= Data.Order.ChH) && (Data.Order.ChH <= 0xFD)) {
    	OffSet1  = (Data.Order.ChH - 0xCA) * 11520;
        OffSet2  = (Data.Order.ChH - 0xCA) * 2 * 24 * 3;
        FontAdr = FONT_CHA_ADR + (Data.Tow - CHA_START_CODE)*
        (KorFont[CpiMode].Body)*3 - OffSet1 - OffSet2;
        /*    FontPart = CHA_PART; */
    }
    else
    if((0xA1 <= Data.Order.ChH) && (Data.Order.ChH <= 0xAC)) {
        OffSet1  = (Data.Order.ChH - 0xA1) * 11520;
        OffSet2  = (Data.Order.ChH - 0xA1) * 2 * 24 * 3;
        FontAdr = FONT_SP_ADR + (Data.Tow - SP_START_CODE)*
        (KorFont[CpiMode].Body)*3 - OffSet1 - OffSet2;
        /*    FontPart = SP_PART; */
    }
    else {
        return 0;
    }
    ChImg.Col  = KorFont[CpiMode].Col;
    ChImg.Body = KorFont[CpiMode].Body;
    ChImg.Rear = KorFont[CpiMode].Col - KorFont[CpiMode].Body;
    ChImg.AdjModKor = KorFont[CpiMode].AdjMod;
    if(CpiMode == 3) {      /* 13.3CPI Adjustment Routine */
        TempVal = ChImg.AdjModKor + ChImg.AdjRemainKor;
        ChImg.AdjRemainKor = TempVal % 100;
        ChImg.Col = KorFont[CpiMode].Col + (TempVal/100);
    }
    switch(FontInfo.ScaleState =
    ScaleMode[GetDim3(FontInfo.HTCondense,FontInfo.VTDouble,FontInfo.HTDouble)])
    {
        case SM_NORMAL              : if((CpiMode == 2) || (CpiMode == 6) || (CpiMode == 7)) {
                                      	Han11Func(FontAdr,&ChImg);
                                      }
                                      else {
                                        Len = (ChImg.Body)*3;
                                        memcpy((&(ChImg.Buff[0])),FontAdr,Len);
                                      }
                                      break;
        case SM_HTDOUBLE            : HTDoubleTB(FontAdr,&ChImg);
                                      break;
        case SM_VTDOUBLE            : VTDoubleTB(FontAdr,&ChImg);
                                      break;
        case SM_HTVTDOUBLE          : HTVTDoubleTB(FontAdr,&ChImg);
                                      break;
        case SM_HTCONDENSE          : HTCondenseTB(FontAdr,&ChImg);
                                      break;
        case SM_VTDOUBLE_HTCONDENSE : VTDoubleTB(FontAdr,&ChImg);
                                      HTCondenseTB(FontAdr,&ChImg);
                                      break;
        default                     : break;
    }
    if((CpiMode == 2) || (CpiMode == 6) || (CpiMode == 7)) {
    	if((FontInfo.HTDouble == SET) || (FontInfo.VTDouble == SET) ||
        (FontInfo.HTCondense == SET)) {
    		ChImg.Col = 24;
    	}
    }
    if(SemiExp == SEMI_EXPAND) {
        ExpNorLoad();
    }
    if(Data.Order.ChH == 0xA6) {
        if(SemiExp == SEMI_EXPAND) {
            VertExpandFlag = SET;
        }
        if(VertExpandFlag == SET) {
            ExpLoad();
            ChImg.Rear = ChImg.Col - ChImg.Body;
            x = ChImg.Body*4;
            for(i=0;i<ChImg.Rear;i++) {                 /* Horizontal Expand Routine */
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
