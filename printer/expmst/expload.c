/*=============================================================*/
/*  KD Line Printer Controller Firmware V2.2                   */
/*  TITLE    : expload.c                                       */
/*  ABSTRACT : Expand Font Loading Routine                     */
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
/*                  ExpLoad Routine (ExpFont Loading)          */
/*=============================================================*/
ExpLoad()
{
    int i,x=0;
    int Len;
    for(i=0;i<3;i++) {
                ChImg.ExpBuff[x] = ChImg.Buff[x];
                ChImg.ExpBuff[x+4] = ChImg.Buff[x+3];
                ChImg.ExpBuff[x+8] = ChImg.Buff[x+6];
                ChImg.ExpBuff[x+12] = ChImg.Buff[x+9];
                ChImg.ExpBuff[x+16] = ChImg.Buff[x+12];
                ChImg.ExpBuff[x+20] = ChImg.Buff[x+15];
                ChImg.ExpBuff[x+24] = ChImg.Buff[x+18];
                ChImg.ExpBuff[x+28] = ChImg.Buff[x+21];
                ChImg.ExpBuff[x+32] = ChImg.Buff[x+24];
                ChImg.ExpBuff[x+36] = ChImg.Buff[x+27];
                ChImg.ExpBuff[x+40] = ChImg.Buff[x+30];
                ChImg.ExpBuff[x+44] = ChImg.Buff[x+33];
                ChImg.ExpBuff[x+48] = ChImg.Buff[x+36];
                ChImg.ExpBuff[x+52] = ChImg.Buff[x+39];
                ChImg.ExpBuff[x+56] = ChImg.Buff[x+42];
                ChImg.ExpBuff[x+60] = ChImg.Buff[x+45];
                ChImg.ExpBuff[x+64] = ChImg.Buff[x+48];
                ChImg.ExpBuff[x+68] = ChImg.Buff[x+51];
                ChImg.ExpBuff[x+72] = ChImg.Buff[x+54];
                ChImg.ExpBuff[x+76] = ChImg.Buff[x+57];
                ChImg.ExpBuff[x+80] = ChImg.Buff[x+60];
                ChImg.ExpBuff[x+84] = ChImg.Buff[x+63];
                ChImg.ExpBuff[x+88] = ChImg.Buff[x+66];
                ChImg.ExpBuff[x+92] = ChImg.Buff[x+69];
                x++;
    }
    x=0;
    for(x=0;x<96;x+=4) {
        if((ChImg.ExpBuff[x+2] & 0x01) == 0x01) {
            ChImg.ExpBuff[x+3] = 0xff;
        }
        else {
            ChImg.ExpBuff[x+3] = 0;
        }
    }
}

/*=============================================================*/
/*                  ExpNorLoad Routine                         */
/*=============================================================*/
ExpNorLoad()
{
    int i,x=0,y=0;
    int Len;
    for(i=0;i<ChImg.Body;i++) {
        ChImg.ExpBuff[x] = ChImg.Buff[y];
        x+=4;
        y+=3;
    }
    x=0;
    y=0;
    for(i=0;i<ChImg.Body;i++) {
        ChImg.ExpBuff[x+1] = ChImg.Buff[y+1];
        x+=4;
        y+=3;
    }
    x=0;
    y=0;
    for(i=0;i<ChImg.Body;i++) {
        ChImg.ExpBuff[x+2] = ChImg.Buff[y+2];
        x+=4;
        y+=3;
    }
}
