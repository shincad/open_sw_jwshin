/*=============================================================*/
/*                  KD20B Controller Program                   */
/*                  Module Name : SLAVE                        */
/*                  Task   Name : Main.c                       */
/*                  Programming Date : 1997. 1.                */
/*                  Program Upgrade : 1998. 6.
/*                  Kia Information Systems.                   */
/*                  Printer Development Team.                  */
/*                  Programmed by Shin Jung Wook               */
/*=============================================================*/

/*=============================================================*/
/*                       Include Part                          */
/*=============================================================*/

#include <stdio.h>
#include "define.h"
#include "variable.mem"
#include "extern.h"

/*--------------------------------------------- OutData Macro -*/

#define OutData(data) while((RD_LPSTA&0x20)>0);INT_DIS;WR_LPDATA=data;WR_LPSTB=0;INT_DIS_PANEL

/*=============================================================*/
/*                   Function Declaration                      */
/*=============================================================*/

Initialize();
OutFunc(u_char);
OutLF(u_int);
FormFeed(u_int);
LineFeed(u_int);
PrintDataFrame();

/*=============================================================*/
/*                       Main Routine                          */
/*=============================================================*/

main()
{
	union REG_UNION Reg0;
/*--------------------------------------- Printer Initialization */
    Initialize();

/*------------------------------------------------ Infinite Loop */
    while(1) {
    	FIFO_EMPTY_CHK;         /* FIFO Empty Flag Check  */
        if(RD_FIFO == STX) {    /* STX Read FIFO          */
        	FIFO_EMPTY_CHK;
            MCmd1 = RD_FIFO;  /* Command1 Read FIFO  */
            FIFO_EMPTY_CHK;
            MCmd2 = RD_FIFO;  /* Command2 Read FIFO  */
            switch(MCmd1) {
            	case SELF_TEST_START : DisClr();
                                       Display(DSP_SELF_TEST);
                                       OpMode = SELF_TEST_RUN;
                                       break;
                case SELF_TEST_STOP  : DisClr();
                                       Display(DSP_ONLINE);
                                       OP_LED1 = ONLINE_ON;
                                       OpMode  = NORMAL;
                                       break;
                case SELF_TEST_RUN   : break;
                default              : break;
            }
            FIFO_EMPTY_CHK;
            Reg0.Order.Hi  = RD_FIFO;     /* Line Feed Value Read FIFO */
            FIFO_EMPTY_CHK;
            Reg0.Order.Low = RD_FIFO;
            switch(MCmd2) {
            	case LPI_CMD     : CharDotLen = Reg0.Two;
                                   break;
                case PL_CMD      : PageDotLen = Reg0.Two;
                                   CurPos = 0; 
                                   break;
                case LF_CMD      : LineFeed(Reg0.Two);
                                   break;
                case FF_CMD      : FormFeed(Reg0.Two);
                                   break;
                case DATA_LF_CMD : INT_DIS_PANEL;
                                   
                                   
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                                    FIFO_EMPTY_CHK;
                                    OutData(RD_FIFO);
                            
                            /*---------------------------- if Last Data of FIFO is not ETX */
                                FIFO_EMPTY_CHK;
                                if(RD_FIFO != ETX) {
                                    INT_DIS;
                                    DisClr();
                                    Display(MST_ETX_ERR);
                                    while(1);
                                }
                                   LineFeed(Reg0.Two);
                                   INT_ENB;
                                   break;
                case DATA_FF_CMD : INT_DIS_PANEL;
                                   /* PrintDataFrame(); */
                                   FormFeed(Reg0.Two);
                                   INT_ENB;
                                   break;
                default          : break;
            }
        }
        else {    /* if First Data of FIFO is not STX */
        	INT_DIS;
            DisClr();
            Display(MST_STX_ERR);
            while(1); /* Infinite Loop */
        }
    }
}

/*=============================================================*/
/*                  Initialization Routine                     */
/*=============================================================*/

Initialize()
{
    INT_DIS;                               /* Interrupt Disable   */
    OnLineFlag = FLAG_SET;                 /* OnlineFlag Set      */
    OpMode     = NORMAL;                   /* OpMode Normal       */
    InitOption = 0;                        /* InitOption disable  */

/*-------------------------------------------- LCD Initialization */
    Init_Lcd();

/*------------------------------------------- Mode Key + Power ON */
    if((OP_LED2 & 0x40) == 0) {
    	DisClr();
        StrOut(DSP_INITEEPROM);      /* Init Eeprom Message   */
        DefaultSetItem();            /* Default Value Loading */
        SaveSetItem();               /* Write to Eeprom       */
    }                                    /* Normal                */

/*-------------------------------------------------------- Normal */
    else {
        DisClr();
        StrOut(DSP_INITIALIZE);
        LoadSetItem();               /* Load Eeprom...        */
    }

    Delay2(200);
    CurHome2();
    StrOut(DSP_KDLOGO);
    Delay2(200);
    CurHome2();
    StrOut("                ");
/*----------------------------------------------------------------*/
    if((OP_LED2 & 0x80) == 0) {
    	DisClr();
        Display("CONFIGURATION..");
        InitOption = 1;
    }
    OP_LED2 = LED_OFF;

/*------------------------------------------------- Printer Ready */
    while((RD_LPSTA & 0x04) > 0) {
    	FUNC_CS   = 1;
        WR_LPDATA = DC1;          /* send DC1     */
        WR_LPSTB  = 0;
        FUNC_CS   = 0;
        Delay3();                 /* 100ms Delay  */
    }

    CallMaster(SET_ITEM);             /* S -> M SET_ITEM's value write */

    ACK_CHK;

/*--------------------------------------------- Paper End Process */
    while((RD_LPSTA & 0x02) == 0) {
    	INT_DIS_PANEL;
        CurHome1();
        StrOut(DSP_PAPER_END);
        INT_DIS;
    }

/*    ModeLedPos = -1; */
    CurPos     = 0;
    EqualFlag  = RESET;
    OP_LED1     = ONLINE_ON;
    if(SetItem[MAX_MENU+1] == 1) {
    	OP_LED2    = HIGHSP_LED;
        PModeSave2 = HIGHSP_LED;
        FUNC_CS    = 1;
        PanelOutData(ESC);
        PanelOutData('D');
        FUNC_CS    = 0;
        ModeLedPos = 0;
    }
    else
    if(SetItem[MAX_MENU+1] == 2) {
        OP_LED2    = HIGHDS_LED;
        PModeSave2 = HIGHDS_LED;
        FUNC_CS    = 1;
        PanelOutData(ESC);
        PanelOutData('N');
        FUNC_CS    = 0;
        ModeLedPos = 1;
    }
    else {
        OP_LED2    = STAND_LED;
        PModeSave2 = STAND_LED;
        FUNC_CS    = 1;
        PanelOutData(ESC);
        PanelOutData('H');
        FUNC_CS    = 0;
        ModeLedPos = -1;
    }
    DisClr();
    Display(DSP_ONLINE);                /* OnLine Message Display */
/*------------------------------------------ Configuration Output */
    if(InitOption == 1) {
    	CallMaster(CONFIG);
    }
    else {
        CallMaster(START);
    }
    INT_ENB;
}


/*=============================================================*/
/*                   OutPut LPFUNC Function                    */
/*=============================================================*/

OutFunc(data)
u_char data;
{
    ACK_CHK;
    INT_DIS;
    FUNC_CS   = 1;
    WR_LPDATA = data;
    WR_LPSTB  = 0;
    FUNC_CS   = 0;
    INT_DIS_PANEL;          /* Panel Int Disable, PFault Int Enable */
}

/*=============================================================*/
/*                      OutLF Function                         */
/*=============================================================*/

OutLF(Value)
u_int Value;
{
    FUNC_CS   = 1;
    ACK_CHK;
    INT_DIS;
    WR_LPDATA = ESC;
    WR_LPSTB  = 0;
    INT_DIS_PANEL;          /* Panel Int Disable, PFault Int Enable */
    ACK_CHK;
    INT_DIS;
    WR_LPDATA = '_';
    WR_LPSTB  = 0;
    INT_DIS_PANEL;          /* Panel Int Disable, PFault Int Enable */
    ACK_CHK;
    INT_DIS;
    WR_LPDATA = ((u_char)(Value >> 8));
    WR_LPSTB  = 0;
    INT_DIS_PANEL;          /* Panel Int Disable, PFault Int Enable */
    ACK_CHK;
    INT_DIS;
    WR_LPDATA = ((u_char)Value);
    WR_LPSTB  = 0;
    INT_DIS_PANEL;          /* Panel Int Disable, PFault Int Enable */
    FUNC_CS = 0;
    OutFunc(NL);
    INT_ENB;
}

/*=============================================================*/
/*                      FormFeed Function                      */
/*=============================================================*/

FormFeed(Value)
u_int Value;
{
    if(EqualFlag == RESET)
    {
        LineFeed(PageDotLen-CurPos);       /* Paper Length - Current Position */
    }
    EqualFlag = RESET;
    Value = Value - 1; 
    while(Value != 0) {
    	Value--;
        LineFeed(PageDotLen);
    }
}

/*=============================================================*/
/*                      LineFeed Function                      */
/*=============================================================*/

LineFeed(Value)
u_int Value;
{
    if(Value == 0) {
    	return 0;
    }
    RLen = PageDotLen - CurPos;
    if(CurPos > (PageDotLen-CharDotLen)) 
    {
        EqualFlag = SET;
    }
/*-------------------------------------------------- Paper End */
    if((RD_LPSTA & 0x02) == 0) {
        if(Value >= RLen) {
            OutLF(RLen);
            OutFunc(EM);
            CurPos = Value - RLen;
            ACK_CHK;
            while((RD_LPSTA & 0x02) == 0){
            	CurHome1();
                Display(DSP_PAPER_END);
            }
            DisClr();
            Display(DSP_ONLINE);
            OutLF(CurPos);
            return 0;
        }
        else {
            OutLF(Value);
            CurPos += Value;
            return 0;
        }
    }

/*-------------------------------------------------------------*/
    if(Value >= RLen) {
    	if(RLen > 270) {
        	OutLF(RLen);
            OutFunc(EM);
            CurPos = Value - RLen;
            ACK_CHK;
            while((RD_LPSTA & 0x02) == 0) {
            	CurHome1();
                Display(DSP_PAPER_END);
            }
            DisClr();
            Display(DSP_ONLINE);
            OutLF(CurPos);
            return 0;
        }
        else {
        	OutLF(RLen);
            CurPos = Value - RLen;
            return 0;
        }
    }
    OutLF(Value);
    CurPos += Value;
}

/*=============================================================*/
/*                  PrintDataFrame Function                    */
/*=============================================================*/

PrintDataFrame()
{
/*-------------------------------------------- 306 Byte Output */
/*        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
    	FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
    	FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
    	FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
    	FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
    	FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);
        FIFO_EMPTY_CHK;
        OutData(RD_FIFO);   */

/*---------------------------- if Last Data of FIFO is not ETX */
    FIFO_EMPTY_CHK;
    if(RD_FIFO != ETX) {
    	INT_DIS;
        DisClr();
        Display(MST_ETX_ERR);
        while(1);
    }
}
