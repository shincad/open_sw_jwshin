/*=============================================================*/
/*                  KD20B Controller Program                   */
/*                  Module Name : SLAVE                        */
/*                  Task   Name : Callmst.c                    */
/*                  Programming Date : 1997. 1. 15             */
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

CallMaster(command)
char command;
{
	INT_DIS;
   	S_M_WRITE = STX;                        /* Start Code           */
	while((RD_SM_INTACK & 0x01) == 0);      /* while Bit0 == 0      */
   	S_M_WRITE = (command + CMD_WEIGHT);     /* Command + CMD_WEIGHT */
   	while((RD_SM_INTACK & 0x01) == 0);
   	switch(command) {
    	int i;
        case SET_ITEM : for(i=0;i<=MAX_MENU;i++) {
                        	S_M_WRITE = (SetItem[i] + CMD_WEIGHT);
                            while((RD_SM_INTACK & 0x01) == 0);
                        }
                        break;
              default : break;
    }
   	S_M_WRITE = ETX;
   	INT_ENB;
}

