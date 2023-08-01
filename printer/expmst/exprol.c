/*=============================================================*/
/*  KD Line Printer Controller Firmware V2.2                   */
/*  TITLE    : exprol.c                                        */
/*  ABSTRACT : Expand Font Rotation Routine                    */
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
#include <stdlib.h>

/*=============================================================*/
/*                      RolProc Routine                        */
/*=============================================================*/

ExpRolProc(Tab)
int Tab;
{
    int i;
    int BuffPos=0,Bpos=0,Pos=0;
    Tab   = (Tab>3)?(Tab-4)+9792:Tab;
    for(i = 0;i < 9792 ;i=i+32) {
        Pos = i +Tab;
        DSLB0 = StImg.ExpBuff[Pos];
        DSLB1 = StImg.ExpBuff[Pos+4];
        DSLB2 = StImg.ExpBuff[Pos+8];
        DSLB3 = StImg.ExpBuff[Pos+12];
        DSLB4 = StImg.ExpBuff[Pos+16];
        DSLB5 = StImg.ExpBuff[Pos+20];
        DSLB6 = StImg.ExpBuff[Pos+24];
        DSLB7 = StImg.ExpBuff[Pos+28];

        DisBuff[BuffPos] = DSLC00;
        BuffPos+=306;
        DisBuff[BuffPos] = DSLC00;
        BuffPos+=306;
        DisBuff[BuffPos] = DSLC00;
        BuffPos+=306;
        DisBuff[BuffPos] = DSLC00;
        BuffPos+=306;
        DisBuff[BuffPos] = DSLC00;
        BuffPos+=306;
        DisBuff[BuffPos] = DSLC00;
        BuffPos+=306;
        DisBuff[BuffPos] = DSLC00;
        BuffPos+=306;
        DisBuff[BuffPos] = DSLC00;
        BuffPos+=306;
        Bpos++;
        BuffPos = Bpos;
    }
}

