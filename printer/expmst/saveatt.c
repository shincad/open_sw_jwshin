/*=============================================================*/
/*  KD Line Printer Controller Firmware V2.2                   */
/*  TITLE    : saveatt.c                                       */
/*  ABSTRACT : Save Attribute Routine                           */
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
/*                  Save Attribute Routine                     */
/*=============================================================*/
SaveAtt()
{
	TempCpiMode   = CpiMode;
   	TempDotLen    = LFInfo.DotLenOfLine;
   	TempSum       = LFInfo.Sum;
   	TempAdjMod    = LFInfo.AdjMod;
   	TempAdjRemain = LFInfo.AdjRemain;
   	TempAutoWrap  = AutoWrap;
   	TempPrtSpeed  = PrtSpeed;
}
