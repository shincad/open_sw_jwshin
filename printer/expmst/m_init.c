/*=============================================================*/
/*  KD Line Printer Controller Firmware V2.2                   */
/*  TITLE    : m_init.c                                        */
/*  ABSTRACT : Master Initialization Routine                   */
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
/*                Master Initialization Routine                */
/*=============================================================*/
Initialize()
{
	SIOInit();
    while(StartEvent != SET);
}
