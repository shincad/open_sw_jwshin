/*=============================================================*/
/*  KD Line Printer Controller Firmware V2.2                   */
/*  TITLE    : cjt.c                                           */
/*  ABSTRACT : Johab to Wansung Convert Routine                */
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
/*               2 Byte Johab Code Conversion                  */
/*=============================================================*/

unsigned short int ConvJoToWan(Data)
union INT_UNION Data;
{
	unsigned char NextAreaFlag = RESET;
	unsigned char ChkVal;
	unsigned short int CmpCnt = 0;
	ChkVal = Data.Order.ChH;
	if((0x88 <= ChkVal) && (ChkVal <= 0x89)) {
		while(Data.Tow != (ConvTable[0][CmpCnt])) {
			if(CmpCnt == 93) {
				NextAreaFlag = SET;
				break;
			}
			CmpCnt++;
		}
		if(NextAreaFlag == SET) {
			CmpCnt = 0;
			NextAreaFlag = RESET;
			while(Data.Tow != (ConvTable[1][CmpCnt])) {
				CmpCnt++;
			}
			Data.Order.ChH = 1;
		}
		else {
			Data.Order.ChH = 0;
		}
	}
	else
	if((0x89 <= ChkVal) && (ChkVal <= 0x8C)) {
		CmpCnt = 0;
		while(Data.Tow != (ConvTable[1][CmpCnt])) {
			if(CmpCnt == 93) {
				NextAreaFlag = SET;
				break;
			}
			CmpCnt++;
		}
		if(NextAreaFlag == SET) {
			CmpCnt = 0;
			NextAreaFlag = RESET;
			while(Data.Tow != (ConvTable[2][CmpCnt])) {
				CmpCnt++;
			}
			Data.Order.ChH = 2;
		}
		else {
			Data.Order.ChH = 1;
		}
	}
	else
	if((0x8C <= ChkVal) && (ChkVal <= 0x8F)) {
		CmpCnt = 0;
		while(Data.Tow != (ConvTable[2][CmpCnt])) {
			if(CmpCnt == 93) {
				NextAreaFlag = SET;
				break;
			}
			CmpCnt++;
		}
		if(NextAreaFlag == SET) {
			CmpCnt = 0;
			NextAreaFlag = RESET;
			while(Data.Tow != (ConvTable[3][CmpCnt])) {
				CmpCnt++;
			}
			Data.Order.ChH = 3;
		}
		else {
			Data.Order.ChH = 2;
		}
	}
	else
	if((0x8F <= ChkVal) && (ChkVal <= 0x92)) {
		CmpCnt = 0;
		while(Data.Tow != (ConvTable[3][CmpCnt])) {
			if(CmpCnt == 93) {
				NextAreaFlag = SET;
				break;
			}
			CmpCnt++;
		}
		if(NextAreaFlag == SET) {
			CmpCnt = 0;
			NextAreaFlag = RESET;
			while(Data.Tow != (ConvTable[4][CmpCnt])) {
				CmpCnt++;
			}
			Data.Order.ChH = 4;
		}
		else {
			Data.Order.ChH = 3;
		}
	}
	else
	if((0x92 <= ChkVal) && (ChkVal <= 0x94)) {
		CmpCnt = 0;
		while(Data.Tow != (ConvTable[4][CmpCnt])) {
			if(CmpCnt == 93) {
				NextAreaFlag = SET;
				break;
			}
			CmpCnt++;
		}
		if(NextAreaFlag == SET) {
			CmpCnt = 0;
			NextAreaFlag = RESET;
			while(Data.Tow != (ConvTable[5][CmpCnt])) {
				CmpCnt++;
			}
			Data.Order.ChH = 5;
		}
		else {
			Data.Order.ChH = 4;
		}
	}
	else
	if((0x94 <= ChkVal) && (ChkVal <= 0x98)) {
		CmpCnt = 0;
		while(Data.Tow != (ConvTable[5][CmpCnt])) {
			if(CmpCnt == 93) {
				NextAreaFlag = SET;
				break;
			}
			CmpCnt++;
		}
		if(NextAreaFlag == SET) {
			CmpCnt = 0;
			NextAreaFlag = RESET;
			while(Data.Tow != (ConvTable[6][CmpCnt])) {
				CmpCnt++;
			}
			Data.Order.ChH = 6;
		}
		else {
			Data.Order.ChH = 5;
		}
	}
	else
	if((0x98 <= ChkVal) && (ChkVal <= 0x9C)) {
		CmpCnt = 0;
		while(Data.Tow != (ConvTable[6][CmpCnt])) {
			if(CmpCnt == 93) {
				NextAreaFlag = SET;
				break;
			}
			CmpCnt++;
		}
		if(NextAreaFlag == SET) {
			CmpCnt = 0;
			NextAreaFlag = RESET;
			while(Data.Tow != (ConvTable[7][CmpCnt])) {
				CmpCnt++;
			}
			Data.Order.ChH = 7;
		}
		else {
			Data.Order.ChH = 6;
		}
	}
	else
	if((0x9C <= ChkVal) && (ChkVal <= 0x9F)) {
		CmpCnt = 0;
		while(Data.Tow != (ConvTable[7][CmpCnt])) {
			if(CmpCnt == 93) {
				NextAreaFlag = SET;
				break;
			}
			CmpCnt++;
		}
		if(NextAreaFlag == SET) {
			CmpCnt = 0;
			NextAreaFlag = RESET;
			while(Data.Tow != (ConvTable[8][CmpCnt])) {
				CmpCnt++;
			}
			Data.Order.ChH = 8;
		}
		else {
			Data.Order.ChH = 7;
		}
	}
	else
	if((0x9F <= ChkVal) && (ChkVal <= 0xA2)) {
		CmpCnt = 0;
		while(Data.Tow != (ConvTable[8][CmpCnt])) {
			if(CmpCnt == 93) {
				NextAreaFlag = SET;
				break;
			}
			CmpCnt++;
		}
		if(NextAreaFlag == SET) {
			CmpCnt = 0;
			NextAreaFlag = RESET;
			while(Data.Tow != (ConvTable[9][CmpCnt])) {
				CmpCnt++;
			}
			Data.Order.ChH = 9;
		}
		else {
			Data.Order.ChH = 8;
		}
	}
	else
	if((0xA2 <= ChkVal) && (ChkVal <= 0xA4)) {
		CmpCnt = 0;
		while(Data.Tow != (ConvTable[9][CmpCnt] )) {
			if(CmpCnt == 93) {
				NextAreaFlag = SET;
				break;
			}
			CmpCnt++;
		}
		if(NextAreaFlag == SET) {
			CmpCnt = 0;
			NextAreaFlag = RESET;
			while(Data.Tow != (ConvTable[10][CmpCnt])) {
				CmpCnt++;
			}
			Data.Order.ChH = 10;
		}
		else {
			Data.Order.ChH = 9;
		}
	}
	else
	if((0xA4 <= ChkVal) && (ChkVal <= 0xA8)) {
		CmpCnt = 0;
		while(Data.Tow != (ConvTable[10][CmpCnt] )) {
			if(CmpCnt == 93) {
				NextAreaFlag = SET;
				break;
			}
			CmpCnt++;
		}
		if(NextAreaFlag == SET) {
			CmpCnt = 0;
			NextAreaFlag = RESET;
			while(Data.Tow != (ConvTable[11][CmpCnt])) {
				CmpCnt++;
			}
			Data.Order.ChH = 11;
		}
		else {
			Data.Order.ChH = 10;
		}
	}
	else
	if((0xA8 <= ChkVal) && (ChkVal <= 0xAC)) {
		CmpCnt = 0;
		while(Data.Tow != (ConvTable[11][CmpCnt] )) {
			if(CmpCnt == 93) {
				NextAreaFlag = SET;
				break;
			}
			CmpCnt++;
		}
		if(NextAreaFlag == SET) {
			CmpCnt = 0;
			NextAreaFlag = RESET;
			while(Data.Tow != (ConvTable[12][CmpCnt])) {
				CmpCnt++;
			}
			Data.Order.ChH = 12;
		}
		else {
			Data.Order.ChH = 11;
		}
	}
	else
	if((0xAC <= ChkVal) && (ChkVal <= 0xAE)) {
		CmpCnt = 0;
		while(Data.Tow != (ConvTable[12][CmpCnt] )) {
			if(CmpCnt == 93) {
				NextAreaFlag = SET;
				break;
			}
			CmpCnt++;
		}
		if(NextAreaFlag == SET) {
			CmpCnt = 0;
			NextAreaFlag = RESET;
			while(Data.Tow != (ConvTable[13][CmpCnt])) {
				CmpCnt++;
			}
			Data.Order.ChH = 13;
		}
		else {
			Data.Order.ChH = 12;
		}
	}
	else
	if((0xAE <= ChkVal) && (ChkVal <= 0xB2)) {
		CmpCnt = 0;
		while(Data.Tow != (ConvTable[13][CmpCnt] )) {
			if(CmpCnt == 93) {
				NextAreaFlag = SET;
				break;
			}
			CmpCnt++;
		}
		if(NextAreaFlag == SET) {
			CmpCnt = 0;
			NextAreaFlag = RESET;
			while(Data.Tow != (ConvTable[14][CmpCnt])) {
				CmpCnt++;
			}
			Data.Order.ChH = 14;
		}
		else {
			Data.Order.ChH = 13;
		}
	}
	else
	if((0xB2 <= ChkVal) && (ChkVal <= 0xB4)) {
		CmpCnt = 0;
		while(Data.Tow != (ConvTable[14][CmpCnt] )) {
			if(CmpCnt == 93) {
				break;
			}
			CmpCnt++;
		}
		Data.Order.ChH = 14;
	}
	else
	if((0xB5 <= ChkVal) && (ChkVal <= 0xB6)) {
		CmpCnt = 0;
		while(Data.Tow != (ConvTable[15][CmpCnt] )) {
			if(CmpCnt == 93) {
				NextAreaFlag = SET;
				break;
			}
			CmpCnt++;
		}if(NextAreaFlag == SET) {
			CmpCnt = 0;
			NextAreaFlag = RESET;
			while(Data.Tow != (ConvTable[16][CmpCnt])) {
				CmpCnt++;
			}
			Data.Order.ChH = 16;
		}
		else {
			Data.Order.ChH = 15;
		}
	}
	else
	if((0xB6 <= ChkVal) && (ChkVal <= 0xB8)) {
		CmpCnt = 0;
		while(Data.Tow != (ConvTable[16][CmpCnt] )) {
			if(CmpCnt == 93) {
				NextAreaFlag = SET;
				break;
			}
			CmpCnt++;
		}
		if(NextAreaFlag == SET) {
			CmpCnt = 0;
			NextAreaFlag = RESET;
			while(Data.Tow != (ConvTable[17][CmpCnt])) {
				CmpCnt++;
			}
			Data.Order.ChH = 17;
		}
		else {
			Data.Order.ChH = 16;
		}
	}
	else
	if((0xB8 <= ChkVal) && (ChkVal <= 0xBB)) {
		CmpCnt = 0;
		while(Data.Tow != (ConvTable[17][CmpCnt] )) {
			if(CmpCnt == 93) {
				NextAreaFlag = SET;
				break;
			}
			CmpCnt++;
		}
		if(NextAreaFlag == SET) {
			CmpCnt = 0;
			NextAreaFlag = RESET;
			while(Data.Tow != (ConvTable[18][CmpCnt])) {
				CmpCnt++;
			}
			Data.Order.ChH = 18;
		}
		else {
			Data.Order.ChH = 17;
		}
	}
	else
	if((0xBB <= ChkVal) && (ChkVal <= 0xC0)) {
		CmpCnt = 0;
		while(Data.Tow != (ConvTable[18][CmpCnt])) {
			if(CmpCnt == 93) {
				NextAreaFlag = SET;
				break;
			}
			CmpCnt++;
		}
		if(NextAreaFlag == SET) {
			CmpCnt = 0;
			NextAreaFlag = RESET;
			while(Data.Tow != (ConvTable[19][CmpCnt])) {
				CmpCnt++;
			}
			Data.Order.ChH = 19;
		}
		else {
			Data.Order.ChH = 18;
		}
	}
	else
	if((0xC0 <= ChkVal) && (ChkVal <= 0xC3)) {
		CmpCnt = 0;
		while(Data.Tow != (ConvTable[19][CmpCnt])) {
			if(CmpCnt == 93) {
				NextAreaFlag = SET;
				break;
			}
			CmpCnt++;
		}
		if(NextAreaFlag == SET) {
			CmpCnt = 0;
			NextAreaFlag = RESET;
			while(Data.Tow != (ConvTable[20][CmpCnt])) {
				CmpCnt++;
			}
			Data.Order.ChH = 20;
		}
		else {
			Data.Order.ChH = 19;
		}
	}
	else
	if((0xC3 <= ChkVal) && (ChkVal <= 0xC6)) {
		CmpCnt = 0;
		while(Data.Tow != (ConvTable[20][CmpCnt])) {
			if(CmpCnt == 93) {
				NextAreaFlag = SET;
				break;
			}
			CmpCnt++;
		}
		if(NextAreaFlag == SET) {
			CmpCnt = 0;
			NextAreaFlag = RESET;
			while(Data.Tow != (ConvTable[21][CmpCnt])) {
				CmpCnt++;
			}
			Data.Order.ChH = 21;
		}
		else {
			Data.Order.ChH = 20;
		}
	}
	else
	if((0xC6 <= ChkVal) && (ChkVal <= 0xCA)) {
		CmpCnt = 0;
		while(Data.Tow != (ConvTable[21][CmpCnt])) {
			if(CmpCnt == 93) {
				NextAreaFlag = SET;
				break;
			}
			CmpCnt++;
		}
		if(NextAreaFlag == SET) {
			CmpCnt = 0;
			NextAreaFlag = RESET;
			while(Data.Tow != (ConvTable[22][CmpCnt])) {
				CmpCnt++;
			}
			Data.Order.ChH = 22;
		}
		else {
			Data.Order.ChH = 21;
		}
	}
	else
	if((0xCA <= ChkVal) && (ChkVal <= 0xCD)) {
		CmpCnt = 0;
		while(Data.Tow != (ConvTable[22][CmpCnt])) {
			if(CmpCnt == 93) {
				NextAreaFlag = SET;
				break;
			}
			CmpCnt++;
		}
		if(NextAreaFlag == SET) {
			CmpCnt = 0;
			NextAreaFlag = RESET;
			while(Data.Tow != (ConvTable[23][CmpCnt])) {
				CmpCnt++;
			}
			Data.Order.ChH = 23;
		}
		else {
			Data.Order.ChH = 22;
		}
	}
	else
	if((0xCD <= ChkVal) && (ChkVal <= 0xD1)) {
		CmpCnt = 0;
		while(Data.Tow != (ConvTable[23][CmpCnt])) {
			if(CmpCnt == 93) {
				NextAreaFlag = SET;
				break;
			}
			CmpCnt++;
		}
		if(NextAreaFlag == SET) {
			CmpCnt = 0;
			NextAreaFlag = RESET;
			while(Data.Tow != (ConvTable[24][CmpCnt])) {
				CmpCnt++;
			}
			Data.Order.ChH = 24;
		}
		else {
			Data.Order.ChH = 23;
		}
	}
	else
	if((0xD1 <= ChkVal) && (ChkVal <= 0xD3)) {
		CmpCnt = 0;
		while(Data.Tow != (ConvTable[24][CmpCnt])) {
			if(CmpCnt == 93) {
				break;
			}
			CmpCnt++;
		}
		Data.Order.ChH = 24;
	}
	Data.Order.ChH = 0xB0 + Data.Order.ChH;
	Data.Order.ChL = 0xA1 + CmpCnt ;
    
    return Data.Tow;
}



























