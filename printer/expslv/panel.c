/*=============================================================*/
/*                  KD20B Controller Program                   */
/*                  Module Name : SLAVE                        */
/*                  Task   Name : Panel.c                      */
/*                  Programming Date : 1997. 1.                */
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
/*                    Function Declaration                     */
/*=============================================================*/

u_char ReadKey();
NorFunc();
u_char ModeKey();
OnLineKey(int *,u_char);
u_char MenuKey(int *,int *,u_char);
u_char ItemKey(int *,int *,u_char);
u_char SetItemKey(int *,int *);
BeepBuz();

/*=============================================================*/
/*                       Variable                              */
/*=============================================================*/

u_char CurKey1 = 0x00;        /* Current Key1 Status */
u_char CurKey2 = 0x00;        /* Current Key2 Status */

/*=============================================================*/
/*               Interrupt Extern Declaration                  */
/*=============================================================*/

extern  void    interrupt   LpPe(void);
extern  void    interrupt   SOpInt(void);
extern  void    interrupt   PFault(void);

/*=============================================================*/
/*                  Interrupt Routine                          */
/*=============================================================*/

/*--------------------------------------- Paper End Interrupt -*/
void interrupt LpPe(void)
{
/*  Not Used......   */

}

/*----------------------------------- Printer Fault Interrupt -*/
void interrupt PFault(void)
{
    INT_DIS;                          /* All Interrupt Disable */
    DisClr();                         /* Display Clear         */
    ErrCode = S_STABIT & 0x3F;
    switch(ErrCode) {
		case PAPER_END     : StrOut(ErrorMenu[0]);
							 break;
		case PLATEN_OPEN   : StrOut(ErrorMenu[1]);
							 break;
        case PAPER_NEA_END : /* StrOut(ErrorMenu[2]); */
                             StrOut("PAPER END.....");
                             while((RD_LPSTA & 0x02) == 0)
                             {
                                BeepBuz();
                             }
                             WR_LPPRIME = 0;
							 break;
		case PAPER_PH_OPEN : StrOut(ErrorMenu[3]);
							 break;
		case FORMS_CHECK   : StrOut(ErrorMenu[4]);
							 break;
		case RIBBON_CHECK  : StrOut(ErrorMenu[5]);
							 break;
		case IF_PARITY_ERR : StrOut(ErrorMenu[6]);
							 break;
		case BUFFER_FULL   : StrOut(ErrorMenu[7]);
							 break;
		case INV_FUNC_CODE : StrOut(ErrorMenu[8]);
							 break;
		case SHUTTLE_LOCK  : StrOut(ErrorMenu[9]);
							 break;
		case HD_FIRE_ERROR : StrOut(ErrorMenu[10]);
							 break;
		case HD_OVER_HEAT  : StrOut(ErrorMenu[11]);
							 break;
		case SHTTL_SNS_ERR : StrOut(ErrorMenu[13]);
							 break;
		case SHTTL_SPD_ERR : StrOut(ErrorMenu[15]);
							 break;
		case HD_REG_ERROR  : StrOut(ErrorMenu[17]);
							 break;
		case HD_EOH_CHK    : StrOut(ErrorMenu[18]);
							 break;
		case MEMORY_ERROR  : StrOut(ErrorMenu[19]);
							 break;
		case BLOWER_STOP   : StrOut(ErrorMenu[20]);
							 break;
		case SHTTL_DRV_ERR1: StrOut(ErrorMenu[21]);
							 break;
		case TR_DRIVER_ERR : StrOut(ErrorMenu[22]);
							 break;
        case H_TR_ERROR    : StrOut(ErrorMenu[23]);
                             break;                     
        case HD_TR_CHK     : StrOut(ErrorMenu[24]);
							 break;
        case SLNID_DRV_ERR : StrOut(ErrorMenu[25]);
							 break;
        case SLV_INVAL_ERR : StrOut(ErrorMenu[26]);
							 break;
        case SLAVE_CPU_ERR : StrOut(ErrorMenu[27]);
							 break;
        case MASTR_CPU_ERR : StrOut(ErrorMenu[30]);
							 break;
        case POWER_ALARM1  : StrOut(ErrorMenu[31]);
							 break;
        case RBN_DRVER_ERR : StrOut(ErrorMenu[33]);
							 break;
        case SHTTL_DRV_ERR2: StrOut(ErrorMenu[34]);
							 break;
        case EEPROM_ERROR  : StrOut(ErrorMenu[37]);
							 break;
        case FAN_STOP      : StrOut(ErrorMenu[40]);
							 break;
        case POWER_ALARM2  : StrOut(ErrorMenu[48]);
							 break;
	}
	PFAULT_CHK;                       /* PFault Port Check     */
	FUNC_CS   = 1;
	WR_LPDATA = DC1;     		      /* send DC1              */
    WR_LPSTB  = 0;           		  /* Strobe Active         */
    FUNC_CS   = 0;
    SLCT_PFAULT_CHK;                  /* Select,PFault Check   */
    ACK_CHK;                          /* ACK Check             */
    DisClr();                         /* Display Clear         */
    StrOut(DspMsg1);                  /* Previous Message      */
    INT_ENB;                          /* Interrupt Enable      */
}

/*-------------------------------------- OnLine Key Interrupt -*/
void interrupt SOpInt(void)
{
   	INT_DIS_PANEL;                     /* Panel Int Disable     */
   	ON_LINE_KEY_WAIT;                  /* OnLine Key 0 -> 1     */
   	Delay2(12);
   	OnLineFlag = FLAG_RESET;           /* OnLineFlag Reset      */
   	switch(OpMode) {
    	case NORMAL          : ON_LINE_KEY_WAIT;
                               NorFunc();
                               break;
        case SELF_TEST_START : break;
        case SELF_TEST_STOP  : break;
        case SELF_TEST_RUN   : OpMode = SELF_TEST_STOP;
                               DisClr();
                               Display(DSP_ONLINE_WAIT);
                               CallMaster(SELF_TEST_STOP_CMD);
                               break;
        default              : break;
   	}
   	INT_ENB;                           /* Interrupt Enable      */
}

/*=============================================================*/
/*                  Normal Function Routine                    */
/*=============================================================*/

NorFunc()
{

/*----------------------------------------------- Variable Declare  */
    int MenuPos = -1;                     /* MenuPosition Init      */
    int ItemPos = -1;                     /* ItemPosition Init      */
    int DotLineNum = 0;
    u_char MenuFlag       = FLAG_RESET;   /* MenuFlag Reset         */
    u_char KeyState       = RESET;        /* KeyState Reset         */
    u_char ItemFlag       = FLAG_RESET;   /* ItemFlag Reset         */
    u_char UpDateItemFlag = FLAG_RESET;   /* UpDateItemFlag Reset   */

/*---------------------- OnLine Led Off and OffLine Message Output  */
    OP_LED1  = LED_OFF;                   /* OnLine Led Off         */
    DisClr();
    strcpy(DspMsg1,DSP_OFFLINE);          /* Previous Message Display after Platen Open  */
    StrOut(DSP_OFFLINE);                  /* Copy Mode Message Off at OffLine */

/*--------------------------------------------------- Key Operation */
    while(OnLineFlag == FLAG_RESET) {     /* while OnlineFlag == 0  */
    	KeyState = ReadKey(); 	          /* Push Key to Ready      */
        switch(KeyState) {
        	case ONLINE_KEY    :   OnLineKey(&MenuPos,UpDateItemFlag);
                                   break;
            case PRT_MODE_KEY  :   PRINT_MODE_KEY_WAIT;
                                   UpDateItemFlag = ModeKey();
                                   break;
            case MODE_KEY      :   MenuFlag = MenuKey(&MenuPos,&ItemPos,PLUS_DIRECTION);
                                   ItemFlag = FLAG_SET;
                                   break;
            case TEST_KEY      :   if(MenuFlag == FLAG_SET) {
                                   		MenuKey(&MenuPos,&ItemPos,MINUS_DIRECTION);
                                   }
                                   else {
                                   		SelfTestKey();
                                        return;
                                   }
                                   break;
            case TOP_KEY       :   if(ItemFlag == FLAG_SET) {
                                   		UpDateItemFlag = SetItemKey(&MenuPos,&ItemPos);
                                   }
                                   else {
                                        SetTopPage();
                                   }
                                   break;
            case MISE_UP_KEY   :   if(MenuFlag == FLAG_SET) {
                                   		ItemFlag=ItemKey(&MenuPos,&ItemPos,PLUS_DIRECTION);
                                   }
                                   else {
                   /* 1 Dot Line */     DotLineNum = 1;
                                        MiseSkipKey(PLUS_DIRECTION,&DotLineNum);
                                   }
                                   break;
            case MISE_DOWN_KEY :   if(MenuFlag == FLAG_SET) {
         	                            ItemFlag=ItemKey(&MenuPos,&ItemPos,MINUS_DIRECTION);
                                   }
                                   else {
                   /* 1 Dot Line */     DotLineNum = 1;
                                        MiseSkipKey(MINUS_DIRECTION,&DotLineNum);
                                   }
                                   break;
            case LF_KEY        :   if(MenuFlag == FLAG_RESET) {
                                        SkipKey(&CharDotLen);
                                   }
                                   break;
            case FF_KEY        :   if(MenuFlag == FLAG_RESET) {
                                        SkipKey(&PageDotLen);
                                   }
                                   break;
            default            :   break;
        }
    }
}

/*=============================================================*/
/*                   ReadKey Function Routine                  */
/*=============================================================*/

u_char ReadKey()
{
	OldKey1 = CurKey1;
   	OldKey2 = CurKey2;

   	CurKey1 = OP_LED1;
   	CurKey2 = OP_LED2;

/*------------------------------------------------- OnLine Key */
   	if((OldKey1 & 0x40) == 0) {
    	if((CurKey1 & 0x40) == 0) {
        	Delay2(12);
            return ONLINE_KEY;
        }
   	}

/*--------------------------------------------- Print Mode Key */
   	else
    if((OldKey2 & 0x10) == 0) {
    	if((CurKey2 & 0x10) == 0x10) {
        	Delay2(12);
            return PRT_MODE_KEY;
        }
   	}

/*--------------------------------------------------- Mode Key */
   	else
    if((OldKey2 & 0x40) == 0) {
    	if((CurKey2 & 0x40) == 0x40) {
        	Delay2(12);
            return MODE_KEY;
        }
   	}

/*--------------------------------------------------- Test Key */
   	else
    if((OldKey2 & 0x80) == 0) {
    	if((CurKey2 & 0x80) == 0x80) {
        	Delay2(12);
            return TEST_KEY;
        }
   	}

/*---------------------------------------------------- Top Key */
   	else
    if((OldKey1 & 0x01) == 0) {
    	if((CurKey1 & 0x01) == 0x01) {
        	Delay2(12);
            return TOP_KEY;
        }
   	}

/*------------------------------------------------ Mise Up Key */
   	else
    if((CurKey1 & 0x04) == 0) {
    	Delay2(12);
        return MISE_UP_KEY;
   	}

/*---------------------------------------------- Mise Down Key */
   	else
    if((CurKey1 & 0x02) == 0) {
    	Delay2(12);
        return MISE_DOWN_KEY;
   	}

/*----------------------------------------------------- LF Key */
   	else
    if((CurKey1 & 0x08) == 0) {
    	if((CurKey1 & 0x08) == 0) {
        	return LF_KEY;
        }
   	}

/*----------------------------------------------------- FF Key */
   	else
    if((OldKey1 & 0x10) == 0) {
    	if((CurKey1 & 0x10) == 0x10) {
        	Delay2(12);
            return FF_KEY;
        }
   	}

/*-------------------------------------------------------------*/
   	else {
    	return 0;
   	}
}

/*=============================================================*/
/*                   Mode Key Function                         */
/*=============================================================*/

u_char ModeKey()
{
    PRINT_MODE_KEY_WAIT;
    ModeLedPos++;
    if(ModeLedPos > 2) {
    	ModeLedPos = 0;
    }
    switch(ModeLedPos) {

        /*----------- GOSOK Mode ------------*/
    	case GOSOK   : OP_LED2    = HIGHSP_LED;
                       PModeSave2 = HIGHSP_LED;
                       FUNC_CS    = 1;
                       PanelOutData(ESC);
                       PanelOutData('D');
                       FUNC_CS    = 0;
                       SetItem[MAX_MENU+1] = 1;
                       break;
        /*----------- GOPUMWI Mode ----------*/
        case GOPUMWI : OP_LED2    = HIGHDS_LED;
                       PModeSave2 = HIGHDS_LED;
                       FUNC_CS    = 1;
                       PanelOutData(ESC);
                       PanelOutData('N');
                       FUNC_CS    = 0;
                       SetItem[MAX_MENU+1] = 2;
                       break;
        /*----------- BOTONG Mode -----------*/
        case BOTONG  : OP_LED2    = STAND_LED;
                       PModeSave2 = STAND_LED;
                       FUNC_CS    = 1;
                       PanelOutData(ESC);
                       PanelOutData('H');
                       FUNC_CS    = 0;
                       SetItem[MAX_MENU+1] = 0;
                       break;
    }
    return FLAG_SET;
}

/*=============================================================*/
/*                  OnLine Key Function                        */
/*=============================================================*/

OnLineKey(MenuPos,UpDateItemFlag)
int *MenuPos;
u_char UpDateItemFlag;
{
    ON_LINE_KEY_WAIT;
    if(UpDateItemFlag == FLAG_SET) {
    	DisClr();
        Display(DSP_SAVING);
        SaveSetItem();        /* Change Item Save to Eeprom */
        CallMaster(SET_ITEM);
    }
    DisClr();
    Display(DSP_ONLINE);
    OP_LED1 = ONLINE_ON;
    OnLineFlag = FLAG_SET;
}

/*=============================================================*/
/*                    MenuKey Function                         */
/*=============================================================*/

u_char MenuKey(MenuPos,ItemPos,MenuDirectFlag)
int *MenuPos;
int *ItemPos;
u_char MenuDirectFlag;
{
    int i;
    u_char MenuFlag = FLAG_RESET;
    char TempMsg[17];
    if(MenuDirectFlag == PLUS_DIRECTION) {       /* Plus Direction */
    	(*MenuPos)++;
        if(*MenuPos > MAX_MENU) {
        	*MenuPos = 0;
        }
    }
    else {                                       /* Minus Direction */
    	(*MenuPos)--;
        if(*MenuPos < 0) {
        	*MenuPos = MAX_MENU;
        }
    }
    *ItemPos = 0;
    strcpy(TempMsg,DspItem[*MenuPos][*ItemPos]);
    if(SetItem[*MenuPos] == *ItemPos) {
    	for(i = strlen( TempMsg ); i < 15; i++) {
        	TempMsg[i] = ' ';
        }
        TempMsg[15] = '*';
    }     /* Setting Item '*' Display */
    MODE_KEY_WAIT;
    TEST_KEY_WAIT;
    BeepBuz();
    DisClr();
    StrOut(DspMenu[*MenuPos]);     /* Upper Menu Display */
    CurHome2();
    StrOut(TempMsg);               /* Lower Menu Message */
    MenuFlag = FLAG_SET;
    return MenuFlag;
}

/*=============================================================*/
/*                     ItemKey Function                        */
/*=============================================================*/

u_char ItemKey(MenuPos,ItemPos,ItemDirectFlag)
int *MenuPos;
int *ItemPos;
u_char ItemDirectFlag;
{
    int i;
    u_char ItemFlag = FLAG_RESET;
    char TempMsg[17];              /* Temporary Space */
    if(ItemDirectFlag == PLUS_DIRECTION) {
    	(*ItemPos)++;
        if(*DspItem[*MenuPos][*ItemPos] == '\0') {
        	*ItemPos = 0;
        }
    }
    else {
    	(*ItemPos)--;
        if(*ItemPos < 0) {
        	for(i=0;i<MAX_ITEM;i++) {
            	if(*DspItem[*MenuPos][i] == '\0') {
                	*ItemPos = i - 1;
                    i = MAX_ITEM;
                }
            }
        }
    }
    strcpy(TempMsg,DspItem[*MenuPos][*ItemPos]);
    if(SetItem[*MenuPos] == *ItemPos) {
    	for(i = strlen( TempMsg ); i < 15; i++) {
        	TempMsg[i] = ' ';
        }
        TempMsg[15] = '*';
    }      /* Setting Item '*' Display */
    MISE_UP_KEY_WAIT;
    MISE_DOWN_KEY_WAIT;
    BeepBuz();
    DisClr();
    CurHome1();
    StrOut(DspMenu[*MenuPos]);    /* Upper Menu Display */
    CurHome2();
    StrOut(TempMsg);              /* Lower Menu Display */
    ItemFlag = FLAG_SET;
    return ItemFlag;
}

/*=============================================================*/
/*                         SetItemKey                          */
/*=============================================================*/

u_char SetItemKey(MenuPos,ItemPos)
int *MenuPos;
int *ItemPos;
{
    int i;
    char TempMsg[17];
    SetItem[*MenuPos] = *ItemPos;
    strcpy(TempMsg,DspItem[*MenuPos][*ItemPos]);
    for( i = strlen( TempMsg ); i < 15; i++) {
    	TempMsg[i] = ' ';
    }
    TempMsg[15] = '*';
    TOP_KEY_WAIT;
    BeepBuz();
    CurHome2();
    StrOut(TempMsg);
    return FLAG_SET;
}

/*=============================================================*/
/*                      Beep Buzzer Function                   */
/*=============================================================*/

BeepBuz()
{
    PModeSave2 = PModeSave2 & 0xf7;
    OP_LED2    = PModeSave2;
    Delay2(1);
    PModeSave2 = PModeSave2 & 0xff;
    OP_LED2    = PModeSave2;

}

/*=============================================================*/
/*                     MiseSkipKey Function                    */
/*=============================================================*/

MiseSkipKey(SkipDirectFlag,DotLineNum)
u_char SkipDirectFlag;
int *DotLineNum;
{
    if(SkipDirectFlag == PLUS_DIRECTION) {
    	CurPos += *DotLineNum;
        if(CurPos >= PageDotLen) {
        	CurPos = CurPos - PageDotLen;
        }
        FUNC_CS  = 1;
        PanelOutData(ESC);
        PanelOutData('F');
        FUNC_CS  = 0;
  	}
    else {
    	CurPos -= *DotLineNum;
        if(CurPos < 0) {
        	CurPos = PageDotLen + CurPos;
        }
        FUNC_CS  = 1;
        PanelOutData(ESC);
        PanelOutData('B');
        FUNC_CS  = 0;
    }

}

/*=============================================================*/
/*                      SkipKey Function                       */
/*=============================================================*/

SkipKey(DotLineNum)
int *DotLineNum;
{
    Delay2(9);
    CurPos += *DotLineNum;
    if(CurPos >= PageDotLen) {
    	CurPos = CurPos - PageDotLen;
    }
    PanelOutLF(*DotLineNum);
}

/*=============================================================*/
/*                    SetTopPage Function                      */
/*=============================================================*/

SetTopPage()
{
    PModeSave1 = PModeSave1 & TOPLED_ON;
    OP_LED1    = PModeSave1;
    CurPos     = 0;
}

/*=============================================================*/
/*                     SelfTestKey Function                    */
/*=============================================================*/

SelfTestKey()
{
/*    OpMode = SELF_TEST_START; */
    DisClr();
    Display(DSP_SELF_TEST_WAIT);
    CallMaster(SELF_TEST_START_CMD);
}

/*=============================================================*/
/*                   PanelOutData Function                     */
/*=============================================================*/

PanelOutData(data)
u_char data;
{
    ACK_CHK;
    WR_LPDATA = data;
    WR_LPSTB  = 0;
}

/*=============================================================*/
/*                      PanelOutLF Function                    */
/*=============================================================*/

PanelOutLF(Value)
u_int Value;
{
    FUNC_CS = 1;
    PanelOutData(ESC);
    PanelOutData('_');
    PanelOutData((u_char)(Value >> 8));
    PanelOutData((u_char)Value);
    FUNC_CS = 0;
    OutFunc(NL);
}
