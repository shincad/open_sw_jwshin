/*=============================================================*/
/*  KD Line Printer Controller Firmware V2.2                   */
/*  TITLE    : institem.c                                      */
/*  ABSTRACT : Printer Value Setting Routine                   */
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
/*                  InstallItem Routine                        */
/*=============================================================*/
InstallItem()
{
	unsigned char i;
    for(i=0;i<16;i++) {          /* 15's Item */
    	switch(i) {
        	case EMUL       : switch(SetItem[i]) {
                                case KS        : EmulationMode = KS;     /* KS Mode */
                                                 KorEngMode = KORENG_MODE;
                                                 break;
                                case KSSM      : EmulationMode = KSSM;   /* KSSM Mode */
                                                 KorEngMode = KORENG_MODE;
                                                 break;
                                case TG        : EmulationMode = TG;     /* TG Mode */
                                                 KorEngMode = KORENG_MODE;
                                                 break;
                                case HEXDUMP_N : EmulationMode = HEXDUMP_N;
                                                 KorEngMode = ONLY_ENGLISH_MODE;
                                                 break;
                                case HEXDUMP_W : EmulationMode = HEXDUMP_W;
                                                 KorEngMode = ONLY_ENGLISH_MODE;
                                                 break;
                                default        : break;
                              }
                              break;
            case CH_PITCH   : switch(SetItem[i]) {
                                case CPI10_2_1 : CpiMode = 0;  		/* 10 CPI 2:1 */
                                                 break;
                                case CPI12_2_1 : CpiMode = 1;  		/* 12 CPI 2:1 */
                                                 break;
                                case CPI10_1_1 : CpiMode = 2;  		/* 10 CPI 1:1 */
                                                 break;
                                case CPI13_2_1 : CpiMode = 3;	  	/* 13.3 CPI 2:1 */
                                                 break;
                                case CPI10_3_2 : CpiMode = 4;	 	/* 10 CPI 3:2 */
                                                 break;
                                case CPI15_2_1 : CpiMode = 5;		/* 15 CPI 2:1 */
                                                 break;
                                default        : break;
                              }
                              break;
            case LINE_SPACE : switch(SetItem[i]) {
                                case LPI_6 : LFInfo.DotLenOfLine = 180/6;	/* 6 LPI */
                                             LFInfo.AdjMod = ((180%6)*100)/6;
                                             LFInfo.AdjRemain = 0;
                                             SendSlave(LPI_CMD);
                                             break;
                                case LPI_8 : LFInfo.DotLenOfLine = 180/8;	/* 8 LPI */
                                             LFInfo.AdjMod = ((180%8)*100)/8;
                                             LFInfo.AdjRemain = 0;
                                             SendSlave(LPI_CMD);
                                             break;
                                default    : break;
                              }
                              break;
            case PRT_MODE   : switch(SetItem[i]) {
                                case NORMAL    : PrtSpeed = SP_NORMAL; /* Normal Mode */
                                                 break;
                                case COPY      : PrtSpeed = COPY;	   	/* Copy Mode */
                                                 break;
                                case HAN300LPM : PrtSpeed = SP_300LPM;/*Hangul 300LPM*/
                                                 break;
                                case ENG410LPM : PrtSpeed = SP_410LPM;/*English 410LPM*/
                                                 break;
                                default        : break;
                              }
                              break;
            case AUTOWRAP   : switch(SetItem[i]) {
                                case ON  : AutoWrap = SET;		/* Autowrap around SET */
                                           break;
                                case OFF : AutoWrap = RESET;   /* Autowrap around RESET */
                                           break;
                                default  : break;
                              }
                              break;
            case HAN_STYLE  : switch(SetItem[i]) {
                                case BYTE_2_WAN : HanStyle = BYTE_2_WAN;
                                                  break;        /* 2 Byte WANSUNG */
                                case BYTE_2_JOH : HanStyle = BYTE_2_JOH;
                                                  break;        /* 2 Byte JoHap */
                                case BYTE_3_JOH : HanStyle = BYTE_3_JOH;
                                                  break;        /* 3 Byte JoHap */
                                case BYTE_N_JOH : HanStyle = BYTE_N_JOH;
                                                  break;        /* N Byte JoHap */
                                default         : break;
                              }
                              break;
            case HAN_FON    : switch(SetItem[i]) {
                                case MYUNGJO : HanFont = MYUNGJO;	/* MyungJo Style */
                                               break;
                                case GODIC   : HanFont = GODIC;		/* Godic Style */
                                               break;
                                default      : break;
                              }
                              break;
            case ENG_FON    : switch(SetItem[i]) {
                                case PRO_ENG : EngFont = ENG1FONT;	 /* English Font */
                                               break;
                                case OCR_B   : EngFont = OCRFONT;	 /* OCR Font */
                                               break;
                                case OCR_B_1 : EngFont = OCRFONT;	 /* OCR Font */
                                               break;
                                default      : break;
                              }
                              break;
            case PAGE_LEN   : if(CheckHostBuff() == EMPTY) {         /* Page Length */
                              switch(SetItem[i]) {
                              	case INCH7    : PageLen = 180*7;	 /* 7 Inch */
                                                SendSlave(PL_CMD);
                                                break;
                                case INCH7_5  : PageLen = 180*7.5;	 /* 7.5 Inch */
                                                SendSlave(PL_CMD);
                                                break;
                                case INCH8    : PageLen = 180*8;	 /* 8 Inch */
                                                SendSlave(PL_CMD);
                                                break;
                                case INCH8_5  : PageLen = 180*8.5;	 /* 8.5 Inch */
                                                SendSlave(PL_CMD);
                                                break;
                                case INCH9    : PageLen = 180*9;  	 /* 9 Inch */
                                                SendSlave(PL_CMD);
                                                break;
                                case INCH9_5  : PageLen = 180*9.5;	 /* 9.5 Inch */
                                                SendSlave(PL_CMD);
                                                break;
                                case INCH11   : PageLen = 180*11;	 /* 11 Inch */
                                                SendSlave(PL_CMD);
                                                break;
                                case INCH11_5 : PageLen = 180*11.5;	 /* 11.5 Inch */
                                                SendSlave(PL_CMD);
                                                break;
                                case INCH12   : PageLen = 180*12; 	 /* 12 Inch */
                                                SendSlave(PL_CMD);
                                                break;
                                case INCH14   : PageLen = 180*14;	 /* 14 Inch */
                                                SendSlave(PL_CMD);
                                                break;
                                default       : break;
                              }
                              }
                              break;
            case B_RATE     : switch(SetItem[i]) {			   		/* Baudrate */
                              	case BPS_300   : M_BRATE = 7;       /* 300 BPS */
                                                 break;
                                case BPS_600   : M_BRATE = 6;		/* 600 BPS */
                                                 break;
                                case BPS_1200  : M_BRATE = 5;		/* 1200 BPS */
                                                 break;
                                case BPS_2400  : M_BRATE = 4;		/* 2400 BPS */
                                                 break;
                                case BPS_4800  : M_BRATE = 3;		/* 4800 BPS */
                                                 break;
                                case BPS_9600  : M_BRATE = 2;		/* 9600 BPS */
                                                 break;
                                case BPS_19200 : M_BRATE = 1;		/* 19200 BPS */
                                                 break;
                                case BPS_38400 : M_BRATE = 0;		/* 38400 BPS */
                                                 break;
                                default        : break;
                              }
                              break;
            case PARITY     : switch(SetItem[i]) {				/* Parity Bit Setting */
                                case NON  : break;
                                case ODD  : break;
                                case EVEN : break;
                                default   : break;
                              }
                              break;
            case DATA_LEN   : switch(SetItem[i]) {		     	/* Data Length */
                                case BIT_8 : break;			 	/* 8 Bit */
                                case BIT_7 : break;				/* 7 Bit */
                                default    : break;
                              }
                              break;
            case STOP_BIT   : switch(SetItem[i]) {	   			/* Stop Bit */
                                case STOP_1 : break;   			/* 1 Stop Bit */
                                case STOP_2 : break;   			/* 2 Stop Bit */
                                default     : break;
                              }
                              break;
            case PROTOCOL   : switch(SetItem[i]) {				/* Serial Protocol */
                                case XON_OFF : Protocol = XON_MODE;	/* Xon/Xoff Mode */
                                               ACIACR   = 0x03;
                                               ACIACR   = 0xD5;
                                               while((ACIASR & 0x02) != 0);
                                               ACIADR = XON;
                                               break;
                                case DTR     : Protocol = DTR_MODE;		/* DTR Mode */
                                               ACIACR   = 0x03;
                                               ACIACR   = 0x95;
                                               break;
                                default      : break;
                              }
                              break;
            case HOST_MODE  : switch(SetItem[i]) { /* Serial , Parallel Mode Selecting */
                                case SERIAL_MODE   : HostPortMod = SERIAL_PORT;
                                                     break;
                                case PARALLEL_MODE : HostPortMod = PARALLEL_PORT;
                                                     break;
                                default            : break;
                              }
                              break;
          case TIMEOUT_MODE : switch(SetItem[i]) {	/* CR = CR, CR = LF Mode Selecting */
                                case ON  : TimeOutMode = SET;
                                           break;
                                case OFF : TimeOutMode = RESET;
                                           break;
                                default  : break;
                              }
                              break;
        }

    }
}
