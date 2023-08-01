/*=============================================================*/
/*  KD Line Printer Controller Firmware V2.2                   */
/*  TITLE    : esctg.c                                         */
/*  ABSTRACT : TG Esc Code Control Routine                     */
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
/*                    ESCProcTg Routine                        */
/*=============================================================*/
ESCProcTg(unsigned char (*GetData)(void))
{
	unsigned char ActValue;
	unsigned char ImgHigh;
	unsigned char ImgLow;
	unsigned int NullCnt;
	unsigned int Column;
	unsigned int Cnt;
	int i;
    unsigned char TgTabVal1,TgTabVal2,TgTabVal3;
    unsigned short int TabVal;
	switch((*GetData)()) {
        case ESCTG_h      : HanFont = BYTE_2_JOH;
                            break;
        case ESCTG_e      : HanFont = BYTE_2_WAN;
                            break;
		case ESCTG_W 	  : CpiMode = 1;
							break;
		case ESCTG_w  	  : CpiMode = 0;
							break;
		case ESCTG_I 	  : CpiMode = 2;
							break;
		case ESCTG_i 	  : CpiMode = 0;
							break;
        case ESCTG_T      : TgTabVal1 = ((*GetData)());
                            TgTabVal1 -= 0x30;
                            TgTabVal1 *= 100;
                            TgTabVal2 = ((*GetData)());
                            TgTabVal2 -= 0x30;
                            TgTabVal2 *= 10;
                            TgTabVal3 = ((*GetData)());
                            TgTabVal3 -= 0x30;
                            TabVal = TgTabVal1 + TgTabVal2 + TgTabVal3 - 1;
                            if(TabFlag == ENG12) {
                                StImg.Pos = TabVal*Eng1Font[CpiMode].Col;
                            }
                            else
                            if(TabFlag == ENG13) {
                                StImg.Pos = TabVal*Eng2Font[CpiMode].Col;
                            }
                            else {
                                StImg.Pos = TabVal*KorFont[CpiMode].Col;
                            } 
                            break;
        case ESCTG_D      : AutoClr.So = SET;
                            FontInfo.HTDouble = SET;
                            break;
        case ESCTG_L      : AutoClr.So = SET;
                            FontInfo.HTDouble = SET;
                            break;
        case ESCTG_d      : AutoClr.So = RESET; /* Horizontal Double Extension Reset */
                            FontInfo.HTDouble = AutoClrDC[AutoClr2(AutoClr.So,AutoClr.W)];
                            break;
        case ESCTG_N      : AutoClr.So = RESET; /* Horizontal Double Extension Reset */
                            FontInfo.HTDouble = AutoClrDC[AutoClr2(AutoClr.So,AutoClr.W)];
                            break;
		case ESCTG_j  	  : break;
		case ESCTG_k 	  : break;
        case ESCTG_6      : FontInfo.VTDouble = SET;
                            VT410Flag = SET;
                            VT300Flag = SET;
                            break;
        case ESCTG_7      : FontInfo.VTDouble = SET;
                            VT410Flag = SET;
                            VT300Flag = SET;
                            break;
        case ESCTG_c      : FontInfo.VTDouble = RESET;
                            VT410Flag = RESET;
                            VT300Flag = RESET;
                            break;
        case ESCTG_G      : HanFont = GODIC;
                            break;
        case ESCTG_g      : HanFont = MYUNGJO;
                            break;
        case ESCTG_U      : FontInfo.UnderLine = SET;
                            break;
        case ESCTG_u      : FontInfo.UnderLine = RESET;
                            break;
		case ESC_BLACKET1 : switch((*GetData)()) {
                                case ESCTG_BK_R : FontInfo.Reverse = SET;
                                                  break;
                                case ESCTG_BK_r : FontInfo.Reverse = RESET;
                                                  break;
							}
							break;
        case ESCTG_F      : FontInfo.Shadow = SET;
                            break;
        case ESCTG_f      : FontInfo.Shadow = RESET;
        case ESCTG_B      : FontInfo.BoldFace = SET;
                            break;
        case ESCTG_b      : FontInfo.BoldFace = RESET;
                            break;
        case ESCTG_S      : FontInfo.HTCondense = SET;
                            break;
        case ESCTG_s      : FontInfo.HTCondense = RESET;
                            break;
		case ESCTG_V	  : break;
		case ESCTG_v      : break;
		case ESC_BLACKET2 : switch((*GetData)()) {
						    	case ESCTG_BK_M : break;
								case ESCTG_BK_m : break;
							}
							break;
		default			  : break;

	}
}
