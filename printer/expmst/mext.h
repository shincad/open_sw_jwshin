/*=============================================================*/
/*  KD Line Printer Controller Firmware V2.2                   */
/*  TITLE    : mext.h                                          */
/*  ABSTRACT : Master Extern Declaration File                  */
/*  AUTHOR(S): Jung-Wook Shin                                  */
/*  DATE     : 1999. 1.                                        */
/*  Copyright (c) 1996-1999  by  Jung-Wook Shin                */
/*  Printer Lab. Phoenix Information Technology                */
/*  All rights reserved.                                       */
/*=============================================================*/

#include "m_define.h"

extern unsigned char HProtect;
extern unsigned char HostBuff[MAX_HBUFF+1];
extern int HRp;
extern int HWp;
extern int Gap;
extern unsigned long TimeOut;
extern unsigned char TimeOutMode;
extern unsigned char EmptyState;
extern unsigned char HostPortMod;
extern unsigned char HexDumpMode;

extern unsigned char CpiMode;
extern unsigned char KorEngMode;
extern unsigned char PrtSpeed;
extern unsigned char TempPrtSpeed;
extern unsigned char HostPortMode;
extern unsigned char BitImgMode;
extern unsigned char HanFont;
extern unsigned char EngFont;
extern unsigned char SemiExp;
extern unsigned char SemiMode;
extern unsigned char EmulationMode;
extern unsigned char AutoWrap;
extern unsigned char HanStyle;
extern unsigned char Protocol;
extern unsigned char AutoWrapOver;
extern unsigned int  EscATemp;
extern unsigned int  EscJTemp;
extern unsigned char EscJFlag;
extern unsigned char VT410Flag;
extern unsigned char VT300Flag;
extern unsigned char Skip11Flag;
extern unsigned char HTScaleState;

extern unsigned char EmptyImgBuff;
extern unsigned char DisBuff[2448];

extern unsigned char HanStyle;

extern unsigned int  PageLen;

extern unsigned char ScaleMode[8];
extern unsigned char AutoClrLF[4];
extern unsigned char AutoClrDC[4];
extern unsigned char AutoClrW[4];


/*---------------------------------------Vertical Extension ---*/
extern unsigned char VTFontTB[16];

/*---------------------------------------Tab Value ------------*/
extern unsigned int TabValue[20];
extern unsigned int TabCt;
extern unsigned int TabLoad;
extern u_char TabFlag;
extern unsigned int VTab[16];
extern unsigned int VTabCt;
extern unsigned int VTabLoad;
extern unsigned int VTabIdent;
extern u_char VTFlag;

/*--------------------------------------------- S_M_Interrupt -*/
extern unsigned char ItemEvent;
extern unsigned char SelfTestEvent;
extern unsigned char ConfigEvent;
extern unsigned char StartEvent;
extern unsigned char SetItem[30];
extern unsigned char SetTempItem[30];
extern unsigned char CmdBuf[30];
extern unsigned char CmdCt;

/*--------------------------------------- Previous Value Save -*/
extern u_char TempCpiMode;
extern u_int  TempDotLen;
extern u_int  TempSum;
extern u_int  TempAdjMod;
extern u_int  TempAdjRemain;
extern u_char TempAutoWrap;

extern u_char EscATempFlag;
extern u_char EscDFlag;
extern u_char OrFlag;
extern u_char EscSPFlag;
extern u_char TempColumn;
extern unsigned short int ConvTable[25][94];

extern u_char VertExpandFlag;
extern u_char BuffRemainFlagFF;

/*------------------ Structure and Union External Declaration -*/
extern struct FONT_INFO FontInfo;
extern struct CH_IMG ChImg;
extern struct ST_IMG StImg;
extern struct LF_INFO LFInfo;
extern struct AUTOCLR_CTR AutoClr;
extern struct MARGIN Margin;
extern union  INT_UNION Data;
extern struct FONTCPI_INFO Eng1Font[8];
extern struct FONTCPI_INFO Eng2Font[8];
extern struct FONTCPI_INFO OcrFont[8];
extern struct FONTCPI_INFO SemiFont[8];
extern struct FONTCPI_INFO KorFont[8];

extern void interrupt Serial(void);
extern void interrupt S_M_Int(void);
char GetSIOBuff(u_char *);
char SendBuff(u_char,u_int,u_int *);
char ExpSendBuff(u_char,u_int,u_int *);
u_char GetHostBuff(void);
u_char HexTest(void);
u_char Test(void);
