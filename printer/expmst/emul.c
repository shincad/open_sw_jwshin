/*=============================================================*/
/*  KD Line Printer Controller Firmware V2.4                   */
/*  TITLE    : emul.c                                          */
/*  ABSTRACT : Code Emulation Routine                          */
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
/*                      Emulation Routine                      */
/*=============================================================*/

Emulation(unsigned char (*GetData)(void))
{
    if(KorEngMode == ONLY_ENGLISH_MODE) {
   		Data.Order.ChH = ((*GetData)());
        if(Data.Order.ChH == 0x7F) {
            CtrProcKssm(Data.Order.ChH);
        }
        if(Data.Order.ChH < 0x20) {          /* Control Code */
      		switch(EmulationMode) {
                case KS        : CtrProc(Data.Order.ChH);         /* KS Control Code */
                                 break;
                case KSSM      : CtrProcKssm(Data.Order.ChH);     /* KSSM Control Code */
                                 break;
                case TG        : CtrProcTg(Data.Order.ChH);       /* TG Control Code */
                                 break;
                case HEXDUMP_N : if(Data.Order.ChH == 0x1B) {
                                    Data.Order.ChH = 0xEE;
                                    MakeEng(Data);
                                 }
                                 else {
                                    Data.Order.ChH = 0xF9;
                                    MakeEng(Data);
                                 }
                                 break;
                default        : break;
         	}
         	return;
      	}
      	else {
      		if(AutoWrapOver == SET) {
         		return;
         	}
         	else {
            	MakeEng(Data);    /* English Font Handling */
         		return;
         	}
      	}
	}
   	else {                                            /* Korean English Mode */
   		Data.Order.ChH = ((*GetData)());
      	if(Data.Order.ChH > 0x80) {
            Data.Order.ChL = ((*GetData)());
            if((Data.Order.ChL >= 0x00) && (Data.Order.ChL <= 0x9F)) {
                Data.Order.ChH = Data.Order.ChL;
                if(Data.Order.ChH < 0x20) {
                    CtrProc(Data.Order.ChH);
                }
                return;
            }
            if(HanStyle == BYTE_2_JOH) { 
                Data.Tow = ConvJoToWan(Data);
            } 
            if(AutoWrapOver == SET) {
         		return;
         	}
         	else {
            	MakeKor(Data);    /* Korean Font Handling */
            	return;
         	}
      	}
        if(Data.Order.ChH == 0x7F) {
            CtrProcKssm(Data.Order.ChH);
        }
        else
      	if(Data.Order.ChH < 0x20) {           /* Control Code */
            if((Data.Order.ChH == 0x01) || (Data.Order.ChH == 0x02) ||
               (Data.Order.ChH == 0x03) || (Data.Order.ChH == 0x04) ||
               (Data.Order.ChH == 0x05) || (Data.Order.ChH == 0x06) ||
               (Data.Order.ChH == 0x10) || (Data.Order.ChH == 0x15) ||
               (Data.Order.ChH == 0x16) || (Data.Order.ChH == 0x17) ||
               (Data.Order.ChH == 0x19)) {
                    if(SemiExp == SEMI_EXPAND) {
                        VertExpandFlag = SET;
                    }
                    switch(Data.Order.ChH) {
                        case 0x01 : Data.Order.ChH = 0xDA;
                                    break;
                        case 0x02 : Data.Order.ChH = 0xBF;
                                    break;
                        case 0x03 : Data.Order.ChH = 0xC0;
                                    break;
                        case 0x04 : Data.Order.ChH = 0xD9;
                                    break;
                        case 0x05 : Data.Order.ChH = 0xB3;
                                    break;
                        case 0x06 : Data.Order.ChH = 0xC4;
                                    break;
                        case 0x10 : Data.Order.ChH = 0xC5;
                                    break;
                        case 0x15 : Data.Order.ChH = 0xC1;
                                    break;
                        case 0x16 : Data.Order.ChH = 0xC2;
                                    break;
                        case 0x17 : Data.Order.ChH = 0xB4;
                                    break;
                        case 0x19 : Data.Order.ChH = 0xC3;
                                    break;
                        default   : break;
                    }
                    if(AutoWrapOver == SET) {
                        return;
                    }
                    else {
                        MakeEng(Data);    /* English Font Handling */
                        return;
                    }
            }
            switch(EmulationMode) {
         		case KS      : CtrProc(Data.Order.ChH);
                		       break;
            	case KSSM    : CtrProcKssm(Data.Order.ChH);
                               break;
                case TG      : CtrProcTg(Data.Order.ChH);
                               break; 
            	default      : break;
         	}
         	return;
      	}
      	else {
        	if(AutoWrapOver == SET) {
         		return;
         	}
         	else {
         		MakeEng(Data);    /* English Font Handling */
            	return;
         	}
      	}
	}
}
