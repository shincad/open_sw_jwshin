/*=============================================================*/
/*  KD Line Printer Controller Firmware V2.2                   */
/*  TITLE    : conprn.c                                        */
/*  ABSTRACT : Printer Configuration Print Routine             */
/*  AUTHOR(S): Jung-Wook Shin                                  */
/*  DATE     : 1999. 2.                                        */
/*  Copyright (c) 1996-1999  by  Jung-Wook Shin                */
/*  Printer Lab. Phoenix Information Technology                */
/*  All rights reserved.                                       */
/*=============================================================*/


#include "m_define.h"
#include "mext.h"

unsigned char ConfigProcess(void);

char *PrtItem[16][11] = {
						  {"1.EMULATION : KS","1.EMULATION : KSSM","1.EMULATION : TG","1.EMULATION : HEXDUMP-N","1.EMULATION : HEXDUMP-W"},
						  {"2.CHAR PITCH : 10 CPI (2:1)","2.CHAR PITCH : 12 CPI (2:1)","2.CHAR PITCH : 10 CPI (1:1)",
						   "2.CHAR PITCH : 13.3 CPI (2:1)","2.CHAR PITCH : 10 CPI (3:2)","2.CHAR PITCH : 15 CPI (2:1)"},
						  {"3.LINE SPACING : 6 LPI","3.LINE SPACING : 8 LPI"},
						  {"4.PRINT MODE : NORMAL","4.PRINT MODE : COPY","4.PRINT MODE : HAN300LPM","4.PRINT MODE : ENG410LPM"},
						  {"5.AUTO WRAP : ON","5.AUTO WRAP : OFF"},
						  {"6.HANGULE TYPE : 2BYTE (WAN)","6.HANGULE TYPE : 2BYTE (JOH)","6.HANGULE TYPE : 3BYTE (JOH)",
						   "6.HANGULE TYPE : NBYTE (JOH)"},
						  {"7.HAN FONT : MYUNGJO","7.HAN FONT : GODIC"},
						  {"8.ENG FONT : PRO-ENG","8.ENG FONT : OCR B","8.ENG FONT : OCR B-1"},
						  {"9.PAGE LENGTH : 7 INCH","9.PAGE LENGTH : 7.5 INCH","9.PAGE LENGTH : 8 INCH","9.PAGE LENGTH : 8.5 INCH",
						   "9.PAGE LENGTH : 9 INCH","9.PAGE LENGTH : 9.5 INCH","9.PAGE LENGTH : 11 INCH","9.PAGE LENGTH : 11.5INCH",
						   "9.PAGE LENGTH : 12 INCH","9.PAGE LENGTH : 14 INCH"},
						  {"10.BAUDRATE : 300 BPS","10.BAUDRATE : 600 BPS","10.BAUDRATE : 1200 BPS","10.BAUDRATE : 2400 BPS",
						   "10.BAUDRATE : 4800 BPS","10.BAUDRATE : 9600 BPS","10.BAUDRATE : 19200 BPS","10.BAUDRATE : 38400 BPS"},
						  {"11.PARITY : NON","11.PARITY : ODD","11.PARITY : EVEN"},
						  {"12.DATA LENGTH : 8 BIT","12.DATA LENGTH : 7 BIT"},
						  {"13.STOP BIT : 1 STOP","13.STOP BIT : 2 STOP"},
						  {"14.PROTOCOL : XON/XOFF","14.PROTOCOL : DTR"},
						  {"15.HOST MODE : SERIAL","15.HOST MODE : PARALLEL"},
                          {"16.TIMEOUT MODE :  ON","16.TIMEOUT MODE : OFF"}
						};

int Cnt1=0;
int Index=0;

ConfigPrint()
{
   SelfSlv(0);
   Emulation((u_char(*)(void))(ConfigProcess));
}



unsigned char ConfigProcess(void)
{
   unsigned char Ch=0;
   int StrCout;
   char SaveMenu[30];
   strcpy(SaveMenu,PrtItem[Cnt1][SetItem[Cnt1]]);
   StrCout=strlen(SaveMenu);
   while(Cnt1 != 16) {
       for(;Index<=StrCout;) {
            Ch = SaveMenu[Index];
            if(Index == StrCout) {
                    Cnt1++;
                    Index = 0;
                    return(0x0a);
            }
            else {
                    Index++;
                    return(Ch);
            }
       }
   }
   if(Cnt1 == 16) {
       ConfigEvent = RESET;
       return(0x0a);
   }
}

