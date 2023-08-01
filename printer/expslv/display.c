/*=============================================================*/
/*                  KD20B Controller Program                   */
/*                  Module Name : SLAVE                        */
/*                  Task   Name : Display.c                    */
/*                  Programming Date : 1997. 1. 15             */
/*                  Kia Information Systems.                   */
/*                  Printer Development Team.                  */
/*                  Programmed by Shin Jung Wook               */
/*=============================================================*/

/*=============================================================*/
/*                       Include Part                          */
/*=============================================================*/

#include <stdio.h>
#include <string.h>
#include "define.h"
#include "extern.h"

/*=============================================================*/
/*                     Function Declaration                    */
/*=============================================================*/

Init_Lcd();
DisClr();
CurHome1();
CurHome2();
DisOn();
DisOff();
EntMode();
CharOut(char);
StrOut(char *);
Bf_Chk();

/*=============================================================*/
/*              LCD Initialization Routine                     */
/*=============================================================*/

Init_Lcd()
{
	PModeSave1 = 0xFF;
   	PModeSave2 = 0xFF;
   	OP_LED2 = 0xFC;             /* 1111$1100B        */
   	S_OPCS  = 0x30;             /* 0011$0000B        */
   	Delay(2232);                /* 5ms Delay         */
   	OP_LED2 = 0xFC;
   	S_OPCS  = 0x30;
   	Delay(56);                  /* 100us Delay       */
   	OP_LED2 = 0xFC;
   	S_OPCS  = 0x30;
   	Delay(6696);                /* 15ms Delay        */
   	OP_LED2 = 0xFC;
   	S_OPCS  = 0x38;
   	Delay(1831);                /* 4.1ms Delay       */
   	OP_LED2 = 0xFC;
   	S_OPCS  = 0x38;
   	Delay(56);                  /* 100us Delay       */
   	OP_LED2 = 0xFC;
   	S_OPCS  = 0x38;
   	Bf_Chk();                   /* Busy Flag Check   */
   	DisOn();                    /* LCD Display On    */
   	Bf_Chk();
   	DisClr();                   /* LCd Display Clear */
}

/*=============================================================*/
/*                  Display Clear (LCD)                        */
/*=============================================================*/

DisClr()
{
   	Bf_Chk();
   	PModeSave2 = PModeSave2 & 0xFC;
   	OP_LED2    = PModeSave2;
   	S_OPCS     = 0x01;
}

/*=============================================================*/
/*                  Cursor Home (1'ST Line)                    */
/*=============================================================*/

CurHome1()
{
   	Bf_Chk();
   	PModeSave2 = PModeSave2 & 0xFC;
   	OP_LED2    = PModeSave2;
   	S_OPCS     = 0x02;
}

/*=============================================================*/
/*                  Cursor Home (2'ND Line)                    */
/*=============================================================*/

CurHome2()
{
   	Bf_Chk();
   	PModeSave2 = PModeSave2 & 0xFC;
   	OP_LED2    = PModeSave2;
   	S_OPCS     = 0xC0;
}

/*=============================================================*/
/*                  Display On Routine (LCD)                   */
/*=============================================================*/

DisOn()
{
   	Bf_Chk();
   	PModeSave2 = PModeSave2 & 0xFC;
   	OP_LED2    = PModeSave2;
   	S_OPCS     = 0x0C;
}

/*=============================================================*/
/*                  Display Off Routine (LCD)                  */
/*=============================================================*/

DisOff()
{
   	Bf_Chk();
   	PModeSave2 = PModeSave2 & 0xFC;
   	OP_LED2    = PModeSave2;
   	S_OPCS     = 0x08;
}

/*=============================================================*/
/*                  Entry Mode (LCD)                           */
/*=============================================================*/

EntMode()
{
   	Bf_Chk();
   	PModeSave2 = PModeSave2 & 0xFC;
   	OP_LED2    = PModeSave2;
   	S_OPCS     = 0x06;
}

/*=============================================================*/
/*                  One Character Output (LCD)                 */
/*=============================================================*/

CharOut(ch)
char ch;
{
   	Bf_Chk();
   	PModeSave2 = PModeSave2 & 0xFD;
   	PModeSave2 = PModeSave2 | 0x0D;
   	OP_LED2    = PModeSave2;
   	S_OPCS     = ch;
}

/*=============================================================*/
/*                  String Output Routine (LCD)                */
/*=============================================================*/

StrOut(str)
char *str;
{
	int i = 0;
   	do {
    	CharOut(str[i]);
   	}while(str[++i] != '\0');
}

/*=============================================================*/
/*                  LCD Busy Flag Check Routine                */
/*=============================================================*/

Bf_Chk()
{
	Delay(600);
   	PModeSave2 = PModeSave2 & 0xFE;
   	PModeSave2 = PModeSave2 | 0x0E;
   	OP_LED2    = PModeSave2;
   	while(S_OPCS & 0x80);
}


/*=============================================================*/
/*                  Display Routine (LCD)                      */
/*=============================================================*/

Display(msg)
char *msg;
{
	if(OnLineFlag == FLAG_SET) {
    	INT_DIS;
   	}
   	strcpy(DspMsg1,msg);
   	StrOut(DspMsg1);
   	if(SetItem[PRINT_MODE] != NORMAL) {  /* if Copy Mode is not Normal */
    	switch (SetItem[PRINT_MODE]) {
        	case COPY_ITEM   :  CurHome2();
            					StrOut(DSP_COPY_ITEM);
                                break;
            case HAN300_ITEM :  CurHome2();
                                StrOut(DSP_HAN300_ITEM);
                                break;
            case ENG410_ITEM :  CurHome2();
                                StrOut(DSP_ENG410_ITEM);
                                break;
        }
   	}
   	if(OnLineFlag == FLAG_SET) {
    	INT_ENB;
   	}
}

