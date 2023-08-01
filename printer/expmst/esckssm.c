/*=============================================================*/
/*  KD Line Printer Controller Firmware V2.2                   */
/*  TITLE    : esckssm.c                                       */
/*  ABSTRACT : KSSM Esc Code Control Routine                   */
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
/*                    ESCProcKssm Routine                      */
/*=============================================================*/
ESCProcKssm(unsigned char (*GetData)(void))
{
    unsigned char ActValue;
    unsigned char ImgHigh;
    unsigned char ImgLow;
    unsigned int NullCnt;
    unsigned int Column;
    unsigned int Cnt;
    unsigned int i;
    unsigned char TempValue;
    /*---------- Esc ECM Variable -*/
    unsigned int BitValue1,TempVal,ActVal,BitCnt;
    unsigned char BitValue[8];

    switch((*GetData)()) {
    	case ESCKM_A   : EscATemp = ((*GetData)());	  /* n/60 inch Line Feed setting */
                         LFInfo.DotLenOfLine = 3 * EscATemp; /* 180 * (n/60) */
                         LFInfo.AdjMod = (((EscATemp*180)%60)*100)/60;
                         LFInfo.AdjRemain = 0;
                         EscATempFlag = SET;
                         break;
        case ESCKM_a   : ActValue = ((*GetData)());	  /* Position arrange select */
                         if(ActValue == 0) {
                         	StImg.Pos = Margin.Left;
                         }
						 else
                         if(ActValue == 1) {
						 	StImg.Pos = 1200;
						 }
						 else
                         if(ActValue == 2) {
						 	StImg.Pos = 2000;
						 }
                         break;
        case ESCKM_B   : VTFlag = SET;
                         while((ActValue = ((*GetData)())) != 0) {
                         	if(VTabLoad < 16) {    /* Vertical Tab Setting */
                            	VTab[VTabLoad] = ActValue;
								VTabLoad++;
                            }
                         }
                         for(;VTabLoad<16;VTabLoad++) {
                         		VTab[VTabLoad] = Margin.Left;
                         }
                         break;
        case ESCKM_b   : /* VFU Tab Setting */
                         VTFlag = SET;
                         while((ActValue = ((*GetData)())) != 0) {
                         	if(VTabLoad < 16) {
                            	VTab[VTabLoad] = ActValue;
                                VTabLoad++;
                            }
                         }
                         for(;VTabLoad<16;VTabLoad++) {
                                VTab[VTabLoad] = Margin.Left;
                         }
                         break;
        case ESCKM_C   : ActValue = ((*GetData)());	        /* Page Length Setting */
                         if(ActValue == 0) {
                            ActValue = ((*GetData)());
                            PageLen = ActValue * 180;
                            SendSlave(PL_CMD);
                         }
                         else {
                            PageLen  = ((ActValue * LFInfo.DotLenOfLine) + ((LFInfo.AdjMod * ActValue)/100));
                            SendSlave(PL_CMD);
                         }
                         break;
        case ESCKM_D   : while((ActValue = ((*GetData)())) != 0) {
                         	if(TabLoad < 20) { /* Horizontal Tab Setting */
                            	TabValue[TabLoad] = ActValue;
                                TabLoad++;
							}
                         }
                         for(;TabLoad<20;TabLoad++)TabValue[TabLoad] = Margin.Left;
                         EscDFlag = SET;
                         break;
        case ESCKM_d   : ActValue = ((*GetData)());	 /* Autowrap around mode set/reset */
                         if((ActValue == SET) || (ActValue == 0x31)) {
                         	AutoWrap = SET;
                         }
                         else {
                            AutoWrap = RESET;
                         }
                         break;
        case ESCKM_E   : FontInfo.BoldFace = SET;      /* Emphasis Mode set */
                         break;
        case ESCKM_EM  : 							   /* No Function */
                         break;
        case ESCKM_F   : FontInfo.BoldFace = RESET;	   /* Emphasis Mode reset */
                         break;
        case ESCKM_G   : FontInfo.BoldFace = SET;	   /* Double print mode set */
                         break;
        case ESCKM_g   : CpiMode = 5;  				   /* 15 CPI Mode */
                         break;
        case ESCKM_H   : FontInfo.BoldFace = RESET;	   /* Double print mode reset */
                         break;
        case ESCKM_J   : ActValue = ((*GetData)());	   /* n/180 inch paper feed */
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
                         break;
        case ESCKM_K   : BitImgMode = BITIMG_8;        /* 8 Dot bit image mode */
                         ImgLow     = ((*GetData)());
                         ImgHigh    = ((*GetData)());
                         Column     = ImgLow + ImgHigh*256;
                         for(i=0;i<Column;i++) {
   		                 	StImg.Buff[i] = ((*GetData)());
                         }
                         InstallItem();
                         break;
        case ESCKM_k   : ActValue = ((*GetData)());	   /* character type select */
                         break;
        case ESCKM_L   : BitImgMode = BITIMG_8;        /* 8 Dot two times bit image mode */
                         ImgLow     = ((*GetData)());
                         ImgHigh    = ((*GetData)());
                         Column     = ImgLow + ImgHigh*256;
                         for(i=0;i<Column;i++) {
       		             	StImg.Buff[i] = ((*GetData)());
                         }
                         InstallItem();
                         break;
        case ESCKM_l   : ActValue = ((*GetData)());	   /* Left Margin setting */
                         if(TabFlag == ENG12) {
                         	StImg.Pos   = StImg.Pos+ActValue*Eng1Font[CpiMode].Col;
                            Margin.Left = ActValue*Eng1Font[CpiMode].Col;
                         }
                         else
                         if(TabFlag == ENG13) {
                            StImg.Pos   = StImg.Pos + ActValue*Eng2Font[CpiMode].Col;
                            Margin.Left = ActValue*Eng2Font[CpiMode].Col;
                         }
                         else {
                            StImg.Pos   = StImg.Pos + ActValue*KorFont[CpiMode].Col;
                            Margin.Left = ActValue*KorFont[CpiMode].Col;
                         }
                         break;
        case ESCKM_M   : CpiMode = 1;				   /* 12 CPI set */
                         break;
        case ESCKM_N   : ActValue = ((*GetData)());	   /* Line Unit Moving set */
                         if(ActValue>=(PageLen/LFInfo.DotLenOfLine)){
                         }
                         else {
                         }
                         break;
        case ESCKM_O   : break;						   /* Line Unit Moving reset */
        case ESCKM_P   : CpiMode = 0;				   /* 10 CPI set */
                         break;
        case ESCKM_p   : ActValue = ((*GetData)());/* Proportional character set/reset */
                         break;
        case ESCKM_Q   : ActValue = ((*GetData)());	   /* Right Margin setting */
                         if(TabFlag == ENG12) {
                         	Margin.Right=PAPER_DOT_WIDTH-(ActValue*Eng1Font[CpiMode].Col);
                         }
                         else
                         if(TabFlag == ENG13) {
                         	Margin.Right=PAPER_DOT_WIDTH-(ActValue*Eng2Font[CpiMode].Col);
                         }
                         else {
                            Margin.Right=PAPER_DOT_WIDTH-(ActValue*KorFont[CpiMode].Col);
                         }
                         break;
        case ESCKM_q   : ActValue = ((*GetData)());	   /* character style select */
                         break;
        case ESCKM_R   : ActValue = ((*GetData)());	   /* International character select */
                         break;
        case ESCKM_r   : ActValue = ((*GetData)());	   /* Color print set */
                         break;
        case ESCKM_S   : ActValue = ((*GetData)());    /* Super/Sub script set */
                         if(ActValue == SET) {
      	                 	PrtSpeed   = SP_410LPM;
                            VT410Flag  = SET;
                            StImg.Part = 1;
                         }
                         else {
                            PrtSpeed   = SP_410LPM;
                            VT410Flag  = SET;
                            StImg.Part = 0;
                         }
                         break;
        case ESCKM_SI  : FontInfo.HTCondense = SET;	   /* Condensing Mode Set */
                         break;
        case ESCKM_SO  : AutoClr.So = SET;			   /* Horizontal Double extension */
                         FontInfo.HTDouble = SET;
                         break;
        case ESCKM_SP  : ActValue = ((*GetData)());    /* Character Space set */
                         if(ActValue == 0) {
                         	EscSPFlag = RESET;
                         }
                         else {
                            TempColumn = ActValue;
                            EscSPFlag = SET;
                         }
                         break;
        case ESCKM_T   : PrtSpeed = NORMAL;
                         VT410Flag = RESET;
                         StImg.Part = 0;
                         break;                         /* Super/Sub script reset */
        case ESCKM_t   : ActValue = ((*GetData)());		/* character code table select */
                         break;
        case ESCKM_U   : ActValue = ((*GetData)());		/* no function */
                         break;
        case ESCKM_W   : ActValue = ((*GetData)());		/* Horizontal Double extension */
                         if((ActValue == SET) || (ActValue == 0x31)) {
                         	AutoClr.W = SET;
                            FontInfo.HTDouble = SET;
                         }
                         else {
                            AutoClr.W = RESET;
						 	FontInfo.HTDouble = AutoClrW[AutoClr2(AutoClr.So,AutoClr.W)];
                         }
                         break;
        case ESCKM_w   : ActValue = ((*GetData)());		/* Vertical Double extension */
                         if((ActValue == SET) || (ActValue == 0x31))  {
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
        case ESCKM_x   : ActValue = ((*GetData)());		/* LQ,Draft mode select */
                         break;
        case ESCKM_Y   : BitImgMode = BITIMG_8;/*8Dot two times density bit image mode */
                         ImgLow     = ((*GetData)());
                         ImgHigh    = ((*GetData)());
                         Column     = ImgLow + ImgHigh*256;
                         for(i=0;i<Column;i++) {
                         	StImg.Buff[i] = ((*GetData)());
                         }
                         InstallItem();
                         break;
        case ESCKM_Z   : BitImgMode = BITIMG_8;/*8Dot four times density bit image mode */
                         ImgLow     = ((*GetData)());
                         ImgHigh    = ((*GetData)());
                         Column     = ImgLow + ImgHigh*256;
                         for(i=0;i<Column;i++) {
                         	StImg.Buff[i] = ((*GetData)());
                         }
                         InstallItem();
                         break;
        case ESCKM_0   : LFInfo.DotLenOfLine = 180/8; /* 1/8 inch */
                         LFInfo.AdjMod = ((180 % 8)*100)/8;
                         LFInfo.AdjRemain = 0;
                         break;
        case ESCKM_1   : LFInfo.DotLenOfLine = 17; /* 17/180 inch */
                         LFInfo.AdjMod = (((17*180)%180)*100)/180;
                         LFInfo.AdjRemain = 0;
                         break;
        case ESCKM_2   : if(EscATempFlag == SET) {
                         	LFInfo.DotLenOfLine = 3 * EscATemp; /* 180 * (n/60) */
                            LFInfo.AdjMod = (((EscATemp*180)%60)*100)/60;
                            LFInfo.AdjRemain = 0;
                         }
                         else {
                            LFInfo.DotLenOfLine = 30;
                            LFInfo.AdjMod = 0;
                            LFInfo.AdjRemain = 0;
                         }
                         break;
        case ESCKM_3   : ActValue = ((*GetData)());
                         LFInfo.DotLenOfLine = ActValue;/*(ActValue*180)/180,n/180 inch*/
                         LFInfo.AdjMod = (((ActValue*180)%180)*100)/180;
                         LFInfo.AdjRemain = 0;
                         break;
        case ESCKM_4   : break;						/* Italic Setting */
        case ESCKM_5   : break;						/* Italic Font Reset */
        case ESCKM_6   : break;						/* Upper Control Code Reset */
        case ESCKM_7   : break;						/* Upper Control Code Set */
        case ESCKM_ECM : BitCnt = 0;				/* Bundle Setting */
                         BitValue1 = 0;
                         ActVal = ((*GetData)());
                         TempVal = ActVal;
                         while(BitCnt < 8) {
                            BitValue1 = TempVal % 2;
                            TempVal   = TempVal / 2;
                            BitValue[BitCnt] = BitValue1;
                            BitCnt++;
                         }
                         for(i=0;i<BitCnt;i++) {
                         	switch(i) {
                                       case CPI : if(BitValue[CPI] == SET) {
                                		   		  		CpiMode = 1;
                                       			  }
                                                  else {
                                                		CpiMode = 0;
                                            	  }
                                                  break;
                                case PROPORTION : if(BitValue[PROPORTION] == SET) {
                                                  }
                                                  else {
                                                  }
                                                  break;
                                    case CONDEN : if(BitValue[CONDEN] == SET) {
                                                  		FontInfo.HTCondense = SET;
                                                  }
                                                  else {
                                                        FontInfo.HTCondense = RESET;
                                                  }
                                                  break;
                                     case EMPHA : if(BitValue[EMPHA] == SET) {
                                                        FontInfo.BoldFace = SET;
                                                  }
                                                  else {
                                                        FontInfo.BoldFace = RESET;
                                                  }
                                                  break;
                                   case DBPRINT : if(BitValue[DBPRINT] == SET) {
                                                        FontInfo.BoldFace = SET;
                                                  }
                                                  else {
                                                        FontInfo.BoldFace = RESET;
                                                  }
                                                  break;
                                  case HTDOUBLE : if(BitValue[HTDOUBLE] == SET) {
                                                        AutoClr.W = SET;
                                                        FontInfo.HTDouble = SET;
                                                  }
                                                  else {
                                                        AutoClr.W = RESET;
                                                        FontInfo.HTDouble = RESET;
                                                  }
                                                  break;
                                    case ITALIC : if(BitValue[ITALIC] == SET) {
                                                  }
                                                  else {
                                                  }
                                                  break;
                                 case UNDERLINE : if(BitValue[UNDERLINE] == SET) {
                                                        FontInfo.UnderLine = SET;
                                                  }
                                                  else {
                                                        FontInfo.UnderLine = RESET;
                                                  }
                                                  break;
                            }
                         }
				         break;
        case ESCKM_UL  : ActValue = ((*GetData)());			/* UnderLine Setting */
                         if((ActValue == SET) || (ActValue == 0x31)) {
                         	FontInfo.UnderLine = SET;
                         }
                         else {
                            FontInfo.UnderLine = RESET;
                         }
                         break;
        case ESCKM_CLN : ActValue  = ((*GetData)());         /* No Function */
                         ActValue  = ((*GetData)());
                         ActValue  = ((*GetData)());
                         break;
        case ESCKM_EMP : break;                    			/* No Function */
        case ESCKM_PST : ActValue  = ((*GetData)());         /* No Function */
                         break;
        case ESCKM_SLH : break;                             /* No Function */
        case ESCKM_DLR : ActValue  = ((*GetData)());			/* Absolute Position */
                         TempValue = ((*GetData)());
                         StImg.Pos = (ActValue + TempValue*256)*3;
                         break;
        case ESCKM_RSLH: ActValue   = ((*GetData)());			/* Relative Position */
                         TempValue  = ((*GetData)());
                         StImg.Pos += ((ActValue + TempValue*256)/60)*24*3;
                         break;
        case ESCKM_AST : BitImgMode = BITIMG_24;			/* Bit Image Mode */
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
        case ESCKM_QM  : ActValue = ((*GetData)());			/* Bit Image Conversion */
                         ActValue = ((*GetData)());
                         break;
        case ESCKM_xX  : ActValue = ((*GetData)());			/* Background Select */
                         ActValue = ((*GetData)());
                         ActValue = ((*GetData)());
                         ActValue = ((*GetData)());
                         ActValue = ((*GetData)());
                         break;
        case ESCKM_LT  : /* No Function */
                         break;
        case ESCKM_ALP : TempInit();						/* Initialization */
                         InstallItem();
                         break;
        default        : break;
    }
}
