/*=============================================================*/
/*  KD Line Printer Controller Firmware V2.2                   */
/*  TITLE    : escproc.c                                       */
/*  ABSTRACT : KS Esc Code Control Routine                     */
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
/*                    ESCProc Routine                          */
/*=============================================================*/
ESCProc(unsigned char (*GetData)(void))
{
	unsigned char ActValue;
    unsigned char ImgHigh;
    unsigned char ImgLow;
    unsigned int NullCnt;
    unsigned int Column;
    unsigned int Cnt;
    int i;
    unsigned char TempValue1;
    unsigned char TempValue2;
    unsigned char TempValue3;
    switch((*GetData)()) {
        case ESC_AST   : BitImgMode = BITIMG_24;            /* Bit Image Mode */
                         ActValue   = ((*GetData)());  /* m Value */
                         ImgLow     = ((*GetData)());
                         ImgHigh    = ((*GetData)());
                         Column     = ImgLow + ImgHigh*256;
                         Cnt = Column * 3;
                         for(i=0;i<Cnt;i++) {
                         	StImg.Buff[i] = ((*GetData)());
                         }
                         InstallItem();
                         break;
        case ESC_UL    : ActValue = ((*GetData)());      /* Under Line */
                         if((ActValue == SET) || (ActValue == 0x31)) {
                         	FontInfo.UnderLine = SET;
                         }
                         else {
                            FontInfo.UnderLine = RESET;
                         }
						 break;
        case ESC_0     : LFInfo.DotLenOfLine = 180/8; /* 1/8 inch */
                         LFInfo.AdjMod = ((180 % 8)*100)/8;
                         LFInfo.AdjRemain = 0;
                         SendSlave(LPI_CMD);
                         break;
        case ESC_1     : LFInfo.DotLenOfLine = 18; /* 1/10 inch */
                         LFInfo.AdjMod = 0;
                         LFInfo.AdjRemain = 0;
                         SendSlave(LPI_CMD);
                         break;
        case ESC_2     : if(EscATempFlag == SET) {
                         	LFInfo.DotLenOfLine = 3 * EscATemp; /* 180 * (n/60) */
                            LFInfo.AdjMod = (((EscATemp*180)%60)*100)/60;
                            LFInfo.AdjRemain = 0;
                         }
                         else {
                            LFInfo.DotLenOfLine = 30;
                            LFInfo.AdjMod = 0;
                            LFInfo.AdjRemain = 0;
                         }
                         SendSlave(LPI_CMD);
                         break;
        case ESC_3     : ActValue = ((*GetData)());
                         LFInfo.DotLenOfLine = ActValue; /*(ActValue*180)/180,n/180 inch*/
                         LFInfo.AdjMod = (((ActValue*180)%180)*100)/180;
                         LFInfo.AdjRemain = 0;
                         SendSlave(LPI_CMD);
                         break;
        case ESC_6     : SemiMode = 1;    /* English Mode character SET II */
                         break;
        case ESC_7     : SemiMode = 0;    /* English Mode character SET I  */
                         break;
        case ESC_A     : EscATemp = ((*GetData)());  /* n/60 inch Row Space Set */
                         EscATempFlag = SET;
                         break;
        case ESC_C     : ActValue = ((*GetData)());  /* Page Length set */
                         PageLen  = (ActValue * LFInfo.DotLenOfLine) + ((LFInfo.AdjMod * ActValue)/100);
                         SendSlave(PL_CMD);
                         break;
        case ESC_D     : while((ActValue = ((*GetData)())) != 0) {
                         	if(TabLoad < 20) { /* Horizontal Tab position setting */
                                TabValue[TabLoad] = ActValue;
                                TabLoad++;
                            }
                         }
                         for(;TabLoad<20;TabLoad++)TabValue[TabLoad] = Margin.Left;
                         EscDFlag = SET;
                         break;
        case ESC_E     : FontInfo.BoldFace = SET;   /* Emphasis character setting */
                         break;
        case ESC_F     : FontInfo.BoldFace = RESET; /* Emphasis character reset */
                         break;
        case ESC_G     : FontInfo.BoldFace = SET;   /* Double printing setting */
                         break;
        case ESC_H     : FontInfo.BoldFace = RESET; /* Double printing reset */
                         break;
        case ESC_J     : ActValue = ((*GetData)()); /* n/180 inch paper feed */
                         if(ActValue < 24) {
                         	EscJTemp = LFInfo.DotLenOfLine;
                            LFInfo.DotLenOfLine = 24;
                         }
                         else {
                            EscJTemp = LFInfo.DotLenOfLine;
                            LFInfo.DotLenOfLine = ActValue;
                         }
                         EscJFlag = SET;
                         LFProc();
                         /*  LFInfo.DotLenOfLine = EscJTemp; */
                         break;
        case ESC_K     : BitImgMode = BITIMG_8;   
                         ImgLow     = ((*GetData)());
                         ImgHigh    = ((*GetData)());
                         Column     = ImgLow + ImgHigh*256;
                         Cnt = Column;
                         for(i=0;i<Cnt;i++) {
                           StImg.Buff[i] = ((*GetData)());
                         }
                         InstallItem();
                         break;
                         /* 8 Bit Single Density Image */
        case ESC_L     : BitImgMode = BITIMG_8;
                         ImgLow     = ((*GetData)());
                         ImgHigh    = ((*GetData)());
                         Column     = ImgLow + ImgHigh*256;
                         Cnt = Column;
                         for(i=0;i<Cnt;i++) {
                           StImg.Buff[i] = ((*GetData)());
                         }
                         InstallItem();
                         /* 8 Bit Double Density Image */
        				 break;
        case ESC_S     : ActValue = ((*GetData)());
                         break;
        case ESC_T     : ActValue = ((*GetData)());
                         break;
        case ESC_U     : ActValue = ((*GetData)()); /* No Function */
                         break;
        case ESC_W     : ActValue = ((*GetData)()); /* Horizontal Double Extension */
                         if((ActValue == SET) || (ActValue == 0x31)) {
                         	AutoClr.W = SET;
                            FontInfo.HTDouble = SET;
                         }
                         else {
                            AutoClr.W = RESET;
                            FontInfo.HTDouble = AutoClrW[AutoClr2(AutoClr.So,AutoClr.W)];
                         }
                         break;
        case ESC_c     : ActValue = ((*GetData)()); /* 1/n inch Row Space Setting */
                         if((ActValue==3)||(ActValue==4)||(ActValue==5)||
                         (ActValue==6)||(ActValue==8)||(ActValue==60)) {
                         	LFInfo.DotLenOfLine = 180/ActValue;
                            LFInfo.AdjMod = ((180%ActValue)*100)/ActValue;
                            LFInfo.AdjRemain = 0;
                         }
                         break;
        case ESC_d     : ActValue = ((*GetData)()); /* Auto wrap around */
                         if((ActValue == SET) || (ActValue == 0x31)) {
                         	AutoWrap = SET;
                         }
                         else {
                            AutoWrap = RESET;
                         }
                         break;
        case ESC_h     : ActValue = ((*GetData)()); /*KoreanEnglish,EnglishMode Setting*/
                         if((ActValue == SET) || (ActValue == 0x31)) {
                         	KorEngMode = KORENG_MODE;
                         }
                         else {
                            KorEngMode = ONLY_ENGLISH_MODE;
                         }
                         break;
        case ESC_i     : ActValue = ((*GetData)()); /*Partial Vertical Double Extension*/
                         	if((ActValue == 1) || (ActValue == 0x31)) {
                            	FontInfo.VTUp = SET;          /* Upper Part extension */
                                FontInfo.VTDouble = SET;
                                VT300Flag = SET;
                                VT410Flag = SET;
                            }
                            else
                            if((ActValue == 2) || (ActValue == 0x32)) {
                                FontInfo.VTDn = SET;          /* Lower Part extension */
                                FontInfo.VTDouble = SET;
                                VT300Flag = SET;
                                VT410Flag = SET;
                            }
                            else {
                                FontInfo.VTUp = RESET;
                                FontInfo.VTDn = RESET;
                                FontInfo.VTDouble = RESET;
                                VT300Flag = RESET;
                                VT410Flag = RESET;
                            }
                         break;
        case ESC_j     : ActValue = ((*GetData)());
                         break;
        case ESC_n     : BitImgMode = BITIMG_24;   /* 24 Bit Image Mode */
                         ImgLow     = ((*GetData)());
                         ImgHigh    = ((*GetData)());
                         Column     = ImgLow + ImgHigh*256;
                         Cnt = Column * 3;
                         for(i=0;i<Cnt;i++) {
                           StImg.Buff[i] = ((*GetData)());
                         }
                         InstallItem();
                         break;
        case ESC_q     : ActValue = ((*GetData)()); /* Mode Change */
                         switch(ActValue) {
                             case 0    : CpiMode = 0;    /* 10 CPI 2:1 */
                                         break;
                             case 1    : CpiMode = 1;    /* 12 CPI 2:1 */
                                         break;
                             case 2    : CpiMode = 2;    /* 10 CPI 1:1 */
                                         break;
                             case 3    : CpiMode = 3;    /* 13.3 CPI 2:1 */
                                         break;
                             case 4    : CpiMode = 4;    /* 10 CPI 3:2 */
                                         break;
                             case 5    : CpiMode = 5;    /* 15 CPI 2:1 */
                                         break;
                             case 6    : CpiMode = 6;    /* 18 CPI 2:1 */
                                         break;
                             case 7    : CpiMode = 7;    /* 20 CPI 2:1 */
                                         break;
                             case 0x30 : CpiMode = 0;
                                         break;
                             case 0x31 : CpiMode = 1;
                                         break;
                             case 0x32 : CpiMode = 2;
                                         break;
                             case 0x33 : CpiMode = 3;
                                         break;
                             case 0x34 : CpiMode = 4;
                                         break;
                             case 0x35 : CpiMode = 5;
                                         break;
                             case 0x36 : CpiMode = 6;
                                         break;
                             case 0x37 : CpiMode = 7;
                                         break;
                         }
                         if((FontInfo.HTCondense == 1) && ((ActValue == 2) ||
                         (ActValue == 0x32))) {
                             CpiMode = 6;    /* Korean 10 CPI , English 20 CPI */
                         }
                         break;
        case ESC_m     : ActValue = ((*GetData)());  /* Hangule godic and myung jo */
                         if((ActValue == SET) || (ActValue == 0x31)) {
                             HanFont = GODIC;
                         }
                         else {
                             HanFont = MYUNGJO;
                         }
                         break;
        case ESC_r     : ActValue = ((*GetData)()); /* reverse printing mode */
                         if((ActValue == SET) || (ActValue == 0x31)) {
                             FontInfo.BoldFace = SET;
                             FontInfo.Reverse  = SET;
                         }
                         else {
                             FontInfo.BoldFace = RESET;
                             FontInfo.Reverse  = RESET;
                         }
                         break;
        case ESC_s     : ActValue = ((*GetData)()); /* 1.5 Expansion mode */
                         if((ActValue == SET) || (ActValue == 0x31)) {
                         	AutoClr.W = SET;
                            FontInfo.HTDouble = SET;
                         }
                         else {
                            AutoClr.W = RESET;
                            FontInfo.HTDouble = AutoClrW[AutoClr2(AutoClr.So,AutoClr.W)];
                         }
                         break;
        case ESC_t     : TempValue1 = ((*GetData)());
                         TempValue1 = TempValue1 - 0x30;
                         TempValue2 = ((*GetData)());
                         TempValue2 = TempValue2 - 0x30;
                         TempValue3 = ((*GetData)());
                         TempValue3 = TempValue3 - 0x30;
                         ActValue = TempValue1*100 + TempValue2*10 + (TempValue3-1);
                         /* character unit print head position moving */
                         if((FontInfo.HTDouble == SET) || (AutoClr.W == SET)) 
                         {
                            if(TabFlag == ENG12) 
                            {
                                StImg.Pos = ActValue*Eng1Font[CpiMode].Col*2;
                            }
                            else if(TabFlag == ENG13)
                            {
                                StImg.Pos = ActValue*Eng2Font[CpiMode].Col*2;
                            }
                            else
                            {
                                StImg.Pos = ActValue*KorFont[CpiMode].Col*2;
                            }   
                         }
                         else if(FontInfo.HTCondense == SET)
                         {
                            if(TabFlag == ENG12) 
                            {
                                StImg.Pos = ActValue*Eng1Font[CpiMode].Col/2;
                            }
                            else if(TabFlag == ENG13)
                            {
                                StImg.Pos = ActValue*Eng2Font[CpiMode].Col/2;
                            }
                            else
                            {
                                StImg.Pos = ActValue*KorFont[CpiMode].Col/2;
                            }  
                         }
                         else
                         {
                             if(TabFlag == ENG12) {
                                 StImg.Pos = ActValue*Eng1Font[CpiMode].Col;
                             }
                             else
                             if(TabFlag == ENG13) {
                                 StImg.Pos = ActValue*Eng2Font[CpiMode].Col;
                             }
                             else {
                                 StImg.Pos = ActValue*KorFont[CpiMode].Col;
                             }
                         }
                         break;
        case ESC_u     : ActValue = ((*GetData)()); /* n/120 inch Row Space Setting */
                         LFInfo.DotLenOfLine = (ActValue*180)/120;
                         LFInfo.AdjMod = (((ActValue*180)%120)*100)/120;
                         LFInfo.AdjRemain = 0;
                         break;
        case ESC_v     : ActValue = ((*GetData)());
                         if((ActValue == SET) || (ActValue == 0x31)) {
                            SemiExp = SEMI_EXPAND;
                         }
                         else {
                            SemiExp = RESET;
                            VertExpandFlag = RESET;
                         }
                         break;
        case ESC_w     : ActValue = ((*GetData)());
                         break;
        case ESC_x     : ActValue = ((*GetData)()); /* LQ,DRAFT Mode Setting */
                         break;
        case ESC_y     : ActValue = ((*GetData)()); /* Vertical Extension */
                         if((ActValue == SET) || (ActValue == 0x31)) {
                             FontInfo.VTDouble = SET;
                             VT410Flag = SET;
                             VT300Flag = SET;
                         }
                         else {
                             FontInfo.VTDouble = RESET;
                             VT410Flag = RESET;
                             VT300Flag = RESET;
                         }
                         break;
        case ESC_z     : ActValue = ((*GetData)());          /* Shadow character */
                         if((ActValue == SET) || (ActValue == 0x31)) {
                             FontInfo.Shadow = SET;
                         }
                         else {
                             FontInfo.Shadow = RESET;
                         }
                         break;
        case ESC_HEAD  : StImg.Pos = 0;  /* Printer Head Return */
                         break;
        /* Wrong Code Emul -- 1999. 4. 2 JinWoong */
        case 0x5B      : ActValue = ((*GetData)());
                         ActValue = ((*GetData)());
                         break;
        default        : break;
	}
}
