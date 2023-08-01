/*=============================================================*/
/*  KD Line Printer Controller Firmware V2.2                   */
/*  TITLE    : fsproc.c                                        */
/*  ABSTRACT : TG FS Code Control Routine                      */
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
/*                 		FSProc Routine  	                   */
/*=============================================================*/

FSProc(unsigned char (*GetData)(void))
{
	unsigned char ActValue;
	unsigned char ImgHigh;
	unsigned char ImgLow;
	unsigned int NullCnt;
	unsigned int Column;
	unsigned int Cnt;
	int i;
    unsigned char TempValue;
	/*---------- FS ECM Variable -*/
	int BitValue1,TempVal,BitCnt;
	unsigned char BitValue[8];

	switch((*GetData)()) {
		case FS_a 	: ActValue = ((*GetData)()); /* ASCII character Setting */
					  break;
		case FS_D 	: ActValue = ((*GetData)());
					  ActValue = ((*GetData)());
					  break;
		case FS_DC2 : break;
	  	case FS_DC4 : AutoClr.So = RESET;
					  FontInfo.HTDouble = AutoClrDC[AutoClr2(AutoClr.So,AutoClr.W)];
					  break;
	  	case FS_J	: break;
	  	case FS_K	: break;
	   	case FS_k	: ActValue = ((*GetData)());
					  if((ActValue == SET) || (ActValue == 0x31)) {
					  	HanFont = GODIC;
					  }
					  else {
					  	HanFont = MYUNGJO;
					  }
					  break;
		case FS_M	: ActValue = ((*GetData)());
					  ActValue = ((*GetData)());
					  ActValue = ((*GetData)());
					  break;
		case FS_r	: ActValue = ((*GetData)());
					  break;
  		case FS_S	: ActValue  = ((*GetData)());
                      TempValue = ((*GetData)());
                      if(TabFlag == ENG12) {
                        Margin.Left = ActValue*Eng1Font[CpiMode].Col;
                        Margin.Right = TempValue*Eng1Font[CpiMode].Col; 
                      }
                      else
                      if(TabFlag == ENG13) {
                        Margin.Left = ActValue*Eng2Font[CpiMode].Col;
                        Margin.Right= TempValue*Eng2Font[CpiMode].Col;
                      }
                      else {
                        Margin.Left = ActValue*KorFont[CpiMode].Col;
                        Margin.Right= TempValue*KorFont[CpiMode].Col;
                      } 
					  break;
		case FS_SI	: FontInfo.HTCondense = SET;
					  break;
		case FS_SO	: AutoClr.So = SET;
					  FontInfo.HTDouble = SET;
					  break;
        case FS_T   : ActValue  = ((*GetData)());
                      TempValue = ((*GetData)());
                      if(TabFlag == ENG12) {
                        Margin.Left = ActValue*Eng1Font[CpiMode].Col;
                        Margin.Right = TempValue*Eng1Font[CpiMode].Col; 
                      }
                      else
                      if(TabFlag == ENG13) {
                        Margin.Left = ActValue*Eng2Font[CpiMode].Col;
                        Margin.Right= TempValue*Eng2Font[CpiMode].Col;
                      }
                      else {
                        Margin.Left = ActValue*KorFont[CpiMode].Col;
                        Margin.Right= TempValue*KorFont[CpiMode].Col;
                      } 
					  break;
		case FS_t	: ActValue = ((*GetData)());
                      if((ActValue == SET) || (ActValue == 0x31)) {
                        HanFont = BYTE_2_JOH;
                      }
                      else {
                        HanFont = BYTE_2_WAN;
                      }    
					  break;
	  	case FS_U	: break;
		case FS_V	: break;
		case FS_v	: ActValue = ((*GetData)());
					  break;
		case FS_W	: ActValue = ((*GetData)());
					  if((ActValue == SET) || (ActValue == 0x31)) {
					  	FontInfo.HTDouble = SET;
						FontInfo.VTDouble = SET;
					  }
					  else {
					  	FontInfo.HTDouble = RESET;
					  	FontInfo.VTDouble = RESET;
					  }
					  break;
		case FS_X	: ActValue = ((*GetData)()); /* Partial Vertical Double Extension */
					  if((ActValue == 1) || (ActValue == 0x31)) {
					  	FontInfo.VTUp = SET;
						FontInfo.VTDouble = SET;
					  }
					  else
					  if((ActValue == 2) || (ActValue == 0x32)) {
					  	FontInfo.VTDn = SET;
						FontInfo.VTDouble = SET;
					  }
					  else
					  if((ActValue == 3) || (ActValue == 0x33)) {
					  	FontInfo.VTDouble = SET;
					  }
					  else {
					  	FontInfo.VTUp = RESET;
					    FontInfo.VTDn = RESET;
						FontInfo.VTDouble = RESET;
					  }
					  break;
  		case FS_x	: ActValue = ((*GetData)());
					  break;
		case FS_2	: ActValue = ((*GetData)());
					  ActValue = ((*GetData)());
					  for(i=0;i<72;i++) {
					  	ActValue = ((*GetData)());
					  }
					  break;
		case FS_ECM : BitCnt = 0;
					  BitValue1 = 0;
					  ActValue = ((*GetData)());
					  TempValue = ActValue;
					  while(BitCnt < 8) {
					  	BitValue1 = TempValue % 2;
						TempValue = TempValue / 2;
						BitValue[BitCnt] = BitValue1;
						BitCnt++;
					  }
					  for(i=0;i<BitCnt;i++) {
					  	switch(i) {
					  		case HT_WRITE : if(BitValue[HT_WRITE] == SET) {
											}
											else {
											}
											break;
							case SEMI_CT  : if(BitValue[SEMI_CT] == SET) {
   											}
   											else {
   											}
   											break;
   							case HT_DB    : if(BitValue[HT_DB] == SET) {
   												FontInfo.HTDouble = SET;
											}
											else {
												FontInfo.HTDouble = RESET;
											}
											break;
							case VT_DB    : if(BitValue[VT_DB] == SET) {
												FontInfo.VTDouble = SET;
											}
											else {
												FontInfo.VTDouble = RESET;
											}
											break;
							case QUARTER1 : if(BitValue[QUARTER1] == SET) {
											}
											else {
											}
											break;
							case QUARTER2 : if(BitValue[QUARTER2] == SET) {
											}
											else {
											}
											break;
							case NOTUSED  : if(BitValue[NOTUSED] == SET) {
											}
											else {
											}
											break;
							case ULINE    : if(BitValue[ULINE] == SET) {
												FontInfo.UnderLine = SET;
											}
											else {
												FontInfo.UnderLine = RESET;
											}
											break;
					    }
					  }
					  break;
	     case FS_UL : ActValue = ((*GetData)());
					  if((ActValue == SET) || (ActValue == 0x31)) {
					  	FontInfo.UnderLine = SET;
					  }
					  else {
					  	FontInfo.UnderLine = RESET;
					  }
					  break;
		case FS_EMP : KorEngMode = KORENG_MODE;
					  break;
        case FS_DLR : ActValue = ((*GetData)());
                      StImg.Pos += 12*ActValue;
					  break;
		case FS_PNT	: KorEngMode = ONLY_ENGLISH_MODE;
    				  break;
		default 	: break;
	}
}





