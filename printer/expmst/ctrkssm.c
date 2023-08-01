/*=============================================================*/
/*  KD Line Printer Controller Firmware V2.2                   */
/*  TITLE    : ctrkssm.c                                       */
/*  ABSTRACT : KSSM Control Code Routine                       */
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
/*                      CtrProcKssm Routine                    */
/*=============================================================*/
CtrProcKssm(CtrData)
unsigned char CtrData;
{
	int i;
   	unsigned char TempDotLen;
   	switch(CtrData) {
   		case 0       : break;
      	case BEL_KM  : break;
      	case BS_KM   : if(TabFlag == ENG12) {
        					StImg.Pos -= Eng1Font[CpiMode].Col;
                       }
                       else
                       if(TabFlag == ENG13) {
                       		StImg.Pos -= Eng2Font[CpiMode].Col;
                       }
                       else {
                       		StImg.Pos -= KorFont[CpiMode].Col;
                       }
                       break;
        case HT_KM   : if(EscDFlag == SET) {               /* Horizontal Tab Setting */
                            if((FontInfo.HTDouble == SET) || (AutoClr.W == SET)) {       
                                if(TabFlag == ENG12) {
                                    StImg.Pos = TabValue[TabCt]*Eng1Font[CpiMode].Col*2;
                                }
                                else if(TabFlag == ENG13) {
                                    StImg.Pos = TabValue[TabCt]*Eng2Font[CpiMode].Col*2;
                                }
                                else {
                                    StImg.Pos = TabValue[TabCt]*KorFont[CpiMode].Col*2;
                                }
                                TabCt++;
                                if(TabValue[TabCt] == 0) {
                                    EscDFlag = RESET;
                                }
                            }
                            else if(FontInfo.HTCondense == SET) {
                                if(TabFlag == ENG12) {
                                    StImg.Pos = TabValue[TabCt]*Eng1Font[CpiMode].Col/2;
                                }
                                else if(TabFlag == ENG13) {
                                    StImg.Pos = TabValue[TabCt]*Eng2Font[CpiMode].Col/2;
                                }
                                else {
                                    StImg.Pos = TabValue[TabCt]*KorFont[CpiMode].Col/2;
                                }
                                TabCt++;
                                if(TabValue[TabCt] == 0) {
                                    EscDFlag = RESET;
                                }
                            }
                            else {
                                if(TabFlag == ENG12) {
                                    StImg.Pos = TabValue[TabCt]*Eng1Font[CpiMode].Col;
                                }
                                else if(TabFlag == ENG13) {
                                    StImg.Pos = TabValue[TabCt]*Eng2Font[CpiMode].Col;
                                }
                                else {
                                    StImg.Pos = TabValue[TabCt]*KorFont[CpiMode].Col;
                                }
                                TabCt++;
                                if(TabValue[TabCt] == 0) {
                                    EscDFlag = RESET;
                                }
                            }
                       }
                       else {    /* Default Horizontal Tab = 8 */
                            if((FontInfo.HTDouble == SET) || (AutoClr.W == SET)) {        
                                if(TabFlag == ENG12) {
                                    StImg.Pos += 8*TabValue[TabCt]*Eng1Font[CpiMode].Col*2;
                                }
                                else if(TabFlag == ENG13) {
                                    StImg.Pos += 8*TabValue[TabCt]*Eng2Font[CpiMode].Col*2;
                                }
                                else {
                                    StImg.Pos += 8*TabValue[TabCt]*KorFont[CpiMode].Col*2;
                                }
                            }
                            else if(FontInfo.HTCondense == SET) {
                                if(TabFlag == ENG12) {
                                    StImg.Pos += 8*TabValue[TabCt]*Eng1Font[CpiMode].Col/2;
                                }
                                else if(TabFlag == ENG13) {
                                    StImg.Pos += 8*TabValue[TabCt]*Eng2Font[CpiMode].Col/2;
                                }
                                else {
                                    StImg.Pos += 8*TabValue[TabCt]*KorFont[CpiMode].Col/2;
                                }
                            }
                            else {
                                if(TabFlag == ENG12) {
                                    StImg.Pos += 8*TabValue[TabCt]*Eng1Font[CpiMode].Col;
                                }
                                else if(TabFlag == ENG13) {
                                    StImg.Pos += 8*TabValue[TabCt]*Eng2Font[CpiMode].Col;
                                }
                                else {
                                    StImg.Pos += 8*TabValue[TabCt]*KorFont[CpiMode].Col;
                                }
                            }
                       }
                       break;
		case LF_KM   : if(AutoWrapOver==SET){
					   		for(i=0;i<288;i++) {
								ChImg.Buff[i] = 0;
							}
							AutoWrapOver = RESET;
					   }
					   LFProc();
					   break;
      	case VT_KM   : if(VTFlag == SET) {
                            if(VTabIdent == 16) {
                                VTFlag = RESET;
                                return;
                            }
                            for(i=0;i<VTab[VTabIdent];i++) {
         	           	    	LFProc();
                       		}
                       		if(VTab[VTabIdent] == 0) {
                                VTabLoad = 0;
                                VTabIdent = 0;
                                VTFlag = RESET;
                                return;
                       		}
                            VTabIdent++;
        			   }
					   else {
					   		if(AutoWrapOver==SET){
					   			for(i=0;i<288;i++) {
									ChImg.Buff[i] = 0;
								}
								AutoWrapOver = RESET;
							}
                            FontInfo.UnderLine = SET;
							LFProc();
					   }
                       break;
      	case FF_KM   : if(AutoWrapOver==SET){
           	           		for(i=0;i<288;i++) {
                        		ChImg.Buff[i] = 0;
                        	}
                        	AutoWrapOver = RESET;
                       }
                       if(BitImgMode == BITIMG_24) {
                       		TempDotLen = LFInfo.DotLenOfLine;
                        	LFInfo.DotLenOfLine = 24;
                        	LFProc();
                        	LFInfo.DotLenOfLine = TempDotLen;
                       } /* if */
                       else {
                       		if(EmptyImgBuff == SET){
                              /*  LFProc(); */
                        	}
                       }
                       SendSlave(FF_CMD);
                       TabCt = 0;
                       break;
      	case CR_KM   : if(AutoWrapOver==SET){
                	  	   for(i=0;i<288;i++) {
                           		ChImg.Buff[i] = 0;
                           }
                           AutoWrapOver = RESET;
                       }
                       StImg.Pos = Margin.Left;
                       AutoClr.So = RESET;
                       FontInfo.HTDouble = AutoClrDC[AutoClr2(AutoClr.So,AutoClr.W)];
                       break;
	    case SO_KM   : AutoClr.So = SET;
                       FontInfo.HTDouble = SET;
                       break;
        case SI_KM   : FontInfo.HTCondense = SET;
                       break;
        case DC1_KM  : break;
        case DC2_KM  : FontInfo.HTCondense = RESET;
                       break;
    	case DC3_KM  : break;
        case DC4_KM  : AutoClr.So = RESET;
                       FontInfo.HTDouble = AutoClrDC[AutoClr2(AutoClr.So,AutoClr.W)];
                       break;
        case CAN_KM  : ClrStImg(DOUBLE_BUFF);
        			   StImg.Pos = 0;
                       AutoClr.So = RESET;
                       FontInfo.HTDouble = AutoClrDC[AutoClr2(AutoClr.So,AutoClr.W)];
                       break;
        case ESC_KM  : ESCProcKssm((unsigned char(*)(void))(GetHostBuff));
                       break;
	   	case FS      : FSProc((u_char(*)(void))(GetHostBuff));
                       break;
        case DEL_KM  : if(TabFlag == ENG12) {
        					StImg.Pos -= Eng1Font[CpiMode].Col;
                       }
                       else
                       if(TabFlag == ENG13) {
                       		StImg.Pos -= Eng2Font[CpiMode].Col;
                       }
                       else {
                       		StImg.Pos -= KorFont[CpiMode].Col;
                       }
                       break;
        default      : break;
	}
}
