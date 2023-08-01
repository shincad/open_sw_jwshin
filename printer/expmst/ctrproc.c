/*=============================================================*/
/*  KD Line Printer Controller Firmware V2.2                   */
/*  TITLE    : ctrproc.c                                       */
/*  ABSTRACT : KS Control Code Routine                         */
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
/*                      CtrProc Routine                        */
/*=============================================================*/
CtrProc(CtrData)
unsigned char CtrData;
{
	int i;
	unsigned char TempDotLen;
	switch(CtrData) {
   		case 0    : break;          /* Null */
      	case BEL  : break;          /* Bell */
      	case HT   : if(EscDFlag == SET) {				/* Horizontal Tab Setting */
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
      	case LF   : if(AutoWrapOver==SET){           /* Line Feed */
                  		for(i=0;i<288;i++) {
                     		ChImg.Buff[i] = 0;
                     	}
                     	AutoWrapOver = RESET;
                  	}
                  	LFProc();
                  	break;
      	case VT   : if(AutoWrapOver==SET){           /* Vertical Tab */
                  		for(i=0;i<288;i++) {
                     		ChImg.Buff[i] = 0;
                     	}
                     	AutoWrapOver = RESET;
                  	}
                 /*   LFProc(); */
                  	break;
      	case FF   : if(AutoWrapOver==SET){           /* Form Feed */
                  		for(i=0;i<288;i++) {
                     		ChImg.Buff[i] = 0;
                     	}
                     	AutoWrapOver = RESET;
                  	}
                  	if(BitImgMode == BITIMG_24) {    /* 24 Bit Image Mode */
                  		TempDotLen = LFInfo.DotLenOfLine;
                     	LFInfo.DotLenOfLine = 24;
                     	LFProc();
                     	LFInfo.DotLenOfLine = TempDotLen;
                        SendSlave(FF_CMD);
                        TabCt = 0;
                  	} /* if */
                  	else {
                        if(EmptyImgBuff == RESET){
                            BuffRemainFlagFF = SET;
                            LFProc();
                            SendSlave(DATA_FF_CMD);
                            BuffRemainFlagFF = RESET;
                     	}
                        else {
                            SendSlave(FF_CMD);     /* Transfer FF Command from Master to Slave */
                            TabCt = 0;
                        }
                    }
                  	break;
      	case CR   : if(AutoWrapOver==SET){  /* Carriage Return */
                  		for(i=0;i<288;i++) {
                     		ChImg.Buff[i] = 0;
                     	}
                     	AutoWrapOver = RESET;
                  	}
                  	StImg.Pos = Margin.Left;
                  	break;
      	case SO   : AutoClr.So = SET;            /* Horizontal Double Extension */
                  	FontInfo.HTDouble = SET;
                 	break;
      	case SI   : FontInfo.HTCondense = SET;   /* Condensing Mode */
                  	break;
      	case DC2  : FontInfo.HTCondense = RESET; /* Condensing Mode Reset */
                  	break;
      	case DC4  : AutoClr.So = RESET;          /* Horizontal Double Extension Reset */
                  	FontInfo.HTDouble = AutoClrDC[AutoClr2(AutoClr.So,AutoClr.W)];
                  	break;
      	case CAN  : ClrStImg(DOUBLE_BUFF);       /* Printing Cancel */
                  	StImg.Pos = 0;
                  	break;
      	case ESC  : ESCProc((u_char(*)(void))(GetHostBuff));   /* Escape Command */
                  	break;
      	default   : break;
	}
}
