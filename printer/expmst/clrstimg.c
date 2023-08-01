/*=============================================================*/
/*  KD Line Printer Controller Firmware V2.2                   */
/*  TITLE    : clrstimg.c                                      */
/*  ABSTRACT : String Image Buffer Clear Routine               */
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
/*                      ClrStImg Routine                       */
/*=============================================================*/

ClrStImg(BuffLine)      /* String Image Buffer Clear Function */
unsigned char BuffLine;
{
	register int i, j, Len = 0;
   	unsigned char *temp;
   	Len = (BuffLine/8) * 2448;
   	memset((&StImg.Buff[i]),0,Len);
}
