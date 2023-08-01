/*=============================================================*/
/*  KD Line Printer Controller Firmware V2.51                  */
/*  TITLE    : autoclr.c                                       */
/*  ABSTRACT : Esc W,SO,Esc y Auto Clear Routine               */
/*  AUTHOR(S): Jung-Wook Shin                                  */
/*  DATE     : 1999. 1.                                        */
/*  Update   : 1999. 3.                                        */
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
/*                   AutoClrCtr Routine                        */
/*=============================================================*/
AutoClrCtr()    /* Esc W,SO,Esc y Auto Clear Code */
{
	AutoClr.So = RESET;
  	FontInfo.HTDouble = AutoClrLF[AutoClr2(AutoClr.So,AutoClr.W)];
    FontInfo.VTDouble = RESET;
    ChImg.AdjRemain = 0;      /* 13.3 CPI Adjustment Remain Value Clear */
    ChImg.AdjRemainKor = 0;   /* 13.3 CPI Hangul Adjustment Remain Value Clear */
}
