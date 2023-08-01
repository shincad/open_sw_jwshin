/*=============================================================*/
/*  KD Line Printer Controller Firmware V2.2                   */
/*  TITLE    : rolproc.c                                       */
/*  ABSTRACT : Font Rotation Routine                           */
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

RolProc(Tab)
int Tab;
{
	int i;
    int BuffPos=0,Bpos=0;
    unsigned char *Temp1, *Temp2;
    Tab   = (Tab>2)?(Tab-3)+7344:Tab;
    Temp2 = DisBuff;
    for(i = 0;i < 7344 ;i=i+24) {
    	Temp1 = &StImg.Buff[i+Tab];
        DSLB0 = *Temp1; Temp1 += 3;
        DSLB1 = *Temp1; Temp1 += 3;
        DSLB2 = *Temp1; Temp1 += 3;
        DSLB3 = *Temp1; Temp1 += 3;
        DSLB4 = *Temp1; Temp1 += 3;
        DSLB5 = *Temp1; Temp1 += 3;
        DSLB6 = *Temp1; Temp1 += 3;
        DSLB7 = *Temp1; Temp1 += 3;

        *Temp2 = DSLC00; Temp2 += 306;
        *Temp2 = DSLC00; Temp2 += 306;
        *Temp2 = DSLC00; Temp2 += 306;
        *Temp2 = DSLC00; Temp2 += 306;
        *Temp2 = DSLC00; Temp2 += 306;
        *Temp2 = DSLC00; Temp2 += 306;
        *Temp2 = DSLC00; Temp2 += 306;
        *Temp2 = DSLC00; Temp2 += 306;
        Bpos++;
        Temp2 = DisBuff+Bpos;
    }
}

/*=============================================================*/
/*                  Image RolProc Routine                      */
/*=============================================================*/
ImageRolProc(Tab)
int Tab;
{
	int i;
    int Pos;
    int Dot;
    int BuffPos=2142,Bpos=2142;
    Tab = (Tab>2)?(Tab-3)+7344:Tab;
    for(i = 0;i < 7344 ;i=i+24) {
    	Pos   = i + Tab;
        DSLB0 = StImg.Buff[Pos];       /* Shift Register 0 */
        DSLB1 = StImg.Buff[Pos+3];     /* Shift Register 1 */
        DSLB2 = StImg.Buff[Pos+6];     /* Shift Register 2 */
        DSLB3 = StImg.Buff[Pos+9];     /* Shift Register 3 */
        DSLB4 = StImg.Buff[Pos+12];    /* Shift Register 4 */
        DSLB5 = StImg.Buff[Pos+15];    /* Shift Register 5 */
        DSLB6 = StImg.Buff[Pos+18];    /* Shift Register 6 */
        DSLB7 = StImg.Buff[Pos+21];    /* Shift Register 7 */

        DisBuff[BuffPos] = DSLC00;
        BuffPos -=306;
        DisBuff[BuffPos] = DSLC00;
        BuffPos -=306;
        DisBuff[BuffPos] = DSLC00;
        BuffPos -=306;
        DisBuff[BuffPos] = DSLC00;
        BuffPos -=306;
        DisBuff[BuffPos] = DSLC00;
        BuffPos -=306;
        DisBuff[BuffPos] = DSLC00;
        BuffPos -=306;
        DisBuff[BuffPos] = DSLC00;
        BuffPos -=306;
        DisBuff[BuffPos] = DSLC00;
        BuffPos -=306;
        Bpos++;
        BuffPos = Bpos;
    } /* end of for(i) */
}
