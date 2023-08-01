/*=============================================================*/
/*                  KD20B Controller Program                   */
/*                  Module Name : SLAVE                        */
/*                  Task   Name : error.c                      */
/*                  Programming Date : 1997. 7.                */
/*                  Kia Information Systems.                   */
/*                  Printer Development Team.                  */
/*                  Programmed by Shin Jung Wook               */
/*=============================================================*/

/*=============================================================*/
/*                       Include Part                          */
/*=============================================================*/

#include <stdio.h>
#include "define.h"
#include "extern.h"


/*=============================================================*/
/*                  Error Code Search Routine                  */
/*=============================================================*/

ErrorCode() 
{
    unsigned char ErrCode;
    int SrCnt;
    ErrCode = S_STABIT & 0x3F;
    for(SrCnt=0;SrCnt>46;SrCnt++) {
        switch(SrCnt) {
            case     
     


