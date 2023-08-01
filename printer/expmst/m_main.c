/*=============================================================*/
/*  KD Line Printer Controller Firmware V2.2                   */
/*  TITLE    : m_main.c                                        */
/*  ABSTRACT : Master Main Routine                             */
/*  AUTHOR(S): Jung-Wook Shin                                  */
/*  DATE     : 1999. 1.                                        */
/*  Copyright (c) 1996-1999  by  Jung-Wook Shin                */
/*  Printer Lab. Phoenix Information Technology                */
/*  All rights reserved.                                       */
/*=============================================================*/

/*=============================================================*/
/*                  Include Header File                        */
/*=============================================================*/
#include <stdio.h>
#include "m_define.h"
#include "mext.h"
#include "m_var.mem"

/*--------------------- HexDump Variable ----------------------*/
unsigned char Togg=0;
unsigned char HData;
unsigned char HexPrtData[16];
unsigned char HexCnt=0;
unsigned char HexNorFlag=RESET;

/*--------------------- HexSub Function Declaration -----------*/
unsigned char HexSub();
unsigned char HexTestW();

/*=============================================================*/
/*                      Main Routine                           */
/*=============================================================*/

main()
{
	int i;
    unsigned char NewItemFlag;
    unsigned char TempDotLen;   /* Dot Length Temporary Buffer */
    INT_ENB;                    /* Interrupt Enable            */
    TempInit();                 /* Variable Initialization     */
    SaveAtt();                  /* Attribute Saving            */
    Initialize();               /* Initialize                  */
    while(1) {
    	INT_DIS;
        if(ItemEvent == SET) {
        	for(i=0;i<16;i++) {
            	SetItem[i] = CmdBuf[i];
            }
            ItemEvent   = RESET;
            NewItemFlag = SET;
        }
        INT_ENB;
        if(EmptyImgBuff == SET) {
        	if(NewItemFlag == SET) {
            	NewItemFlag = RESET;
                InstallItem();
            }
        }
        while(CheckHostBuff() == EMPTY) {     /* Host Buffer Checking */
        	if((TimeOut > TIME_OUT) && (EmptyImgBuff == RESET)) {
            	TimeOut = 0;
                if(BitImgMode == BITIMG_24) {
                	TempDotLen = LFInfo.DotLenOfLine;
                    LFInfo.DotLenOfLine = 24;
                    LFProc();
                    LFInfo.DotLenOfLine = TempDotLen;
                }
                else {
                    if((EmulationMode == HEXDUMP_N) || (EmulationMode == HEXDUMP_W))
                    {
                        if(Togg==1) {
                            Emulation((u_char(*)(void))(HexTest));
                            LFProc();
                            Togg = 0;
                            HData = 0;
                            HexCnt = 0;
                        }
                    }
                    LFProc();
                }
            }
            else
            if((TimeOutMode == SET) && (EmptyImgBuff == RESET)) {
            	TimeOut++;       /* CR = LF */
            }
            else {
                TimeOut = 0;
            }
            if(ItemEvent == SET) {
            	for(i=0;i<16;i++) {
                	SetItem[i] = CmdBuf[i];
                }
                ItemEvent   = RESET;
                NewItemFlag = SET;
            }
            if(NewItemFlag == SET) {
            	NewItemFlag = RESET;
                InstallItem();
            }
            if(SelfTestEvent == SELF_TEST_START) {   /* Self Test */
            	if(EmptyImgBuff == RESET) {
                	LFProc();
                }
                else {
                    RunSelfTest();  /* Self Test Routine */
                }
            }
            if(ConfigEvent == SET) {
                ConfigPrint();
            }
        }
        if(EmulationMode == HEXDUMP_N) {                /* HexDump */
            KorEngMode = ONLY_ENGLISH_MODE;
            if(HexNorFlag == SET) {
                Emulation((u_char(*)(void))(HexSub));
            }
            else {
                Emulation((u_char(*)(void))(HexTest));
            }
            if((HexCnt==16) && (HexNorFlag==RESET)) {
                HexNorFlag = SET;
                HexCnt = 0;
                StImg.Pos += 288;
            }
            if((HexCnt==16) && (HexNorFlag==SET)) {
                HexNorFlag = RESET;
                HexCnt = 0;
                LFProc();
            }
        }
        else if(EmulationMode == HEXDUMP_W) {
            KorEngMode = ONLY_ENGLISH_MODE;
            Emulation((u_char(*)(void))(HexTestW));
        }
        else {
            Emulation((u_char(*)(void))(GetHostBuff));
        }
    }  /* while(1) */
}

/*=============================================================*/
/*                Variable Initialization Routine              */
/*=============================================================*/

TempInit()
{
	unsigned int i;
    BitImgMode = 0;
    StImg.Part = 0;
    FontInfo.VTUp = RESET;
    FontInfo.VTDn = RESET;
    StImg.HaveVTUp = RESET;
    StImg.HaveVT = RESET;
    StImg.Pos = 0;
    LFInfo.Sum = 0;
    Margin.Left = 0;
    Margin.Right = 0;
    LFInfo.AdjMod = 0;
    LFInfo.AdjRemain = 0;
    HanFont = MYUNGJO;
    EngFont = ENG1FONT;
    CpiMode = 0;
    FontInfo.HTCondense = 0;
    FontInfo.VTDouble = 0;
    FontInfo.HTDouble = 0;
    FontInfo.Reverse  = RESET;
    FontInfo.Shadow = RESET;
    FontInfo.UnderLine = RESET;
    FontInfo.BoldFace = RESET;
    KorEngMode = KORENG_MODE;
    AutoWrap = SET;
    AutoWrapOver = RESET;
    AutoClr.So = RESET;
    AutoClr.W = RESET;
    HostPortMod = SERIAL_PORT;
    M_BRATE = 2;
    Protocol = XON_MODE;
    EmptyImgBuff = SET;
    SemiMode = 1;
    TimeOutMode  = SET;
    TabCt = 0;
    TabLoad = 0;
    TimeOut = 0;
    EscJFlag = 0;
    SelfTestEvent = 0;
    ConfigEvent = 0;
    M_ACK = 0;
    M_PORTCS = 1;
    VT410Flag = RESET;
    VT300Flag = RESET;
    EscATempFlag = RESET;
    EscJFlag = RESET;
    EscSPFlag = RESET;
    HanStyle = BYTE_2_JOH;
    BuffRemainFlagFF = RESET;
    SemiExp = RESET;
    VertExpandFlag = RESET;
    HexNorFlag = RESET;
    HexCnt = 0;
    ChImg.AdjRemain = 0;
    ChImg.AdjRemainKor = 0;

    VTabIdent = 0;
    VTabLoad  = 0;
    ClrStImg(DOUBLE_BUFF);       /* String Image Buffer Clear */
    memset((&StImg.ExpBuff[i]),0,9792); /* Expand String Buffer Clear */
    for(i=0;i<20;i++) {
    	TabValue[i] = 0;
    }
    for(i=0;i<576;i++) {         /* Expand Character Buffer Clear */
        ChImg.ExpBuff[i];
    }
    for(i=0;i<432;i++) {         /* Character Buffer Clear */
        ChImg.Buff[i] = 0;
    }
    for(i=0;i<16;i++) {
        HexPrtData[i] = 0;
    }
}

/*==============================================================*/
/*                      Hex Dump Routine(Narrow)                */
/*==============================================================*/

unsigned char HexTest()
{
	unsigned char Data;
    if(Togg==0){
    	while((GetSIOBuff(&Data) == -1) && (GetPIOBuff(&Data) == -1));
        HexPrtData[HexCnt] = Data;
        HData = Data;
        Data = (Data >> 4) & 0x0F;
        if(Data>9) {
        	Data+=0x37;
        }
        else {
            Data+=0x30;
        }
    }
    else{
        Data = HData & 0x0F;
        if(Data>9) {
            Data+=0x37;
        }
        else {
            Data+=0x30;
        }
        HexCnt++;
    }
    if((StImg.Pos != 0) &&(Togg == 0)) {
    	StImg.Pos += 36;
    }
    Togg ^= 1;
    return Data;
}

/*==============================================================*/
/*                      Hex Dump Routine(Wide)                  */
/*==============================================================*/

unsigned char HexTestW()
{
	unsigned char Data;
    if(Togg==0){
    	while((GetSIOBuff(&Data) == -1) && (GetPIOBuff(&Data) == -1));
        HData = Data;
        Data = (Data >> 4) & 0x0F;
        if(Data>9) {
        	Data+=0x37;
        }
        else {
            Data+=0x30;
        }
    }
    else{
        Data = HData & 0x0F;
        if(Data>9) {
            Data+=0x37;
        }
        else {
            Data+=0x30;
        }
    }
    if((StImg.Pos != 0) &&(Togg == 0)) {
    	StImg.Pos += 36;
    }
    Togg ^= 1;
    return Data;
}

unsigned char HexSub()
{
    unsigned char Data;
    Data = HexPrtData[HexCnt];
    HexCnt++;
    StImg.Pos += 12;
    return Data;
}
