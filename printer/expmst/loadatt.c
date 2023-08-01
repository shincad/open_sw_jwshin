/*=============================================================*/
/*  KD Line Printer Controller Firmware V2.2                   */
/*  TITLE    : loadatt.c                                       */
/*  ABSTRACT : load attribute Routine                          */
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
/*                  Load Attribute Routine                     */
/*=============================================================*/
LoadAtt()
{
	CpiMode = TempCpiMode;
   	LFInfo.DotLenOfLine = TempDotLen;
   	LFInfo.Sum = TempSum;
   	LFInfo.AdjMod = TempAdjMod;
   	LFInfo.AdjRemain = TempAdjRemain;
   	AutoWrap = TempAutoWrap;
   	PrtSpeed = TempPrtSpeed;
}
