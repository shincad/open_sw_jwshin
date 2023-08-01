/*=============================================================*/
/*  KD Line Printer Controller Firmware V2.2                   */
/*  TITLE    : copyimg.c                                       */
/*  ABSTRACT : CharacterImgBuffer ---> StImgBuffer Copy        */
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
/*                   CopyToStImg Routine                       */
/*=============================================================*/
/*     From Character Image Buffer to String Image Buffer      */

CopyToStImg(DestBase,SourBase,Col)
unsigned int DestBase;
unsigned int SourBase;
unsigned int Col;
{
	unsigned int Len;
    Len = SourBase + (Col*3);
    DestBase = DestBase + (StImg.Pos*3);
    memcpy( &(StImg.Buff[DestBase]), &(ChImg.Buff[SourBase]),Len-SourBase);
    memset( &(ChImg.Buff[SourBase]), 0 , Len-SourBase);
    StImg.Pos += ChImg.Col;
}
