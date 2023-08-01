/*=============================================================*/
/*  KD Line Printer Controller Firmware V2.2                   */
/*  TITLE    : setatt.c                                        */
/*  ABSTRACT : set base attribute Routine                      */
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
/*                  Set Base Attribute Routine                 */
/*=============================================================*/
SetBaseAtt()
{
	CpiMode = 0;
   	LFInfo.DotLenOfLine = 30;
   	LFInfo.AdjMod = 0;
   	LFInfo.AdjRemain = 0;
   	AutoWrap = RESET;
   	PrtSpeed = NORMAL;
}
