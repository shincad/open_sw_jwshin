/*=============================================================*/
/*	KD Line Printer Controller Firmware V2.2				   */
/*	TITLE	 : send_img.c									   */
/*	ABSTRACT : Send String Image Routine					   */
/*	AUTHOR(S): Jung-Wook Shin								   */
/*	DATE	 : 1999. 1. 									   */
/*	Copyright (c) 1996-1999  by  Jung-Wook Shin 			   */
/*	Printer Lab. Phoenix Information Technology 			   */
/*	All rights reserved.									   */
/*=============================================================*/

/*=============================================================*/
/*					Include Header File 					   */
/*=============================================================*/
#include "m_define.h"
#include "mext.h"

/*=============================================================*/
/*					   SendStImg Routine					   */
/*=============================================================*/
unsigned int LFCt;

unsigned char FontLine;
unsigned int LFLen;

SendStImg(BuffLine,Swap)   /* BuffLine = 24, 48  .. , Swap = at Vertical Extension */
unsigned char BuffLine;
unsigned char Swap;
{
	int Tab;
	unsigned int LFVal;
	if(LFInfo.Sum > 0) {
		SendSlave(LF_CMD);
		LFInfo.Sum = 0;
	}
	if(BuffLine == DOUBLE_BUFF) {		  /* at Vertical Extension */
		LFVal = LFInfo.DotLenOfLine * 2 + AdjLPIErr(2);
	}
	else {
		LFVal = LFInfo.DotLenOfLine + AdjLPIErr(1);
	}
	if(BuffLine < LFVal) {
		if(PrtSpeed == SP_410LPM) {  /* at English 410 Lpm Mode */
			if(VT410Flag == SET) { /* Vertical Extension */
				FontLine = BuffLine;
				LFLen	 = LFVal - FontLine + 1;
				VT410Flag = RESET;
			}
			else {
				FontLine = 12;					  /* 8 x 12 Font */
				LFLen	 = LFVal - FontLine + 1;  /* 30 - 12 + 1 = 19 */
			}
		}
		else
		if(PrtSpeed == SP_300LPM) { /* at Hangule 300 Lpm Mode */
			if(VT300Flag == SET) {	   /* Vertical Extension */
				FontLine = BuffLine;
				LFLen	 = LFVal - FontLine + 1;
				VT300Flag = RESET;
			}
			else {
				FontLine = 18;					  /* 24 x 18 Font */
				LFLen	 = LFVal - FontLine + 1;  /* 30 - 18 + 1 = 13 */
			}
		}	/* SP_300LPM */
		else {
			FontLine = BuffLine;		  /* Eng 12 x 24 , 13 x 24 , Han 24 x 24 Font */
			LFLen	 = LFVal - BuffLine + 1;
		}
	}
	else {
		FontLine = LFVal;
		LFLen	 = 1;
	}
	LFCt = 0;
	if(Swap == SET) {									/* Vertical Extension */
		if(PrtSpeed == SP_300LPM) { 			   /* Hangule 300 Lpm Mode */
			for(Tab=3;Tab<6;Tab++) {		/* Transfer String Image Part 1 */
				RolProc(Tab);
				if(SendBuff300(FontLine,LFLen,&LFCt) == -1) {
					return;
				}
			}
			for(Tab=0;Tab<3;Tab++) {		/* Transfer String Image PArt 0 */
				RolProc(Tab);
				if(SendBuff300(FontLine,LFLen,&LFCt) == -1) {
					return;
				}
			}
		}
		else if(LFInfo.DotLenOfLine == 22) {
			for(Tab=3;Tab<6;Tab++) {		/* Transfer String Image Part 1 */
				RolProc(Tab);
				if(SendBuff8LPI(FontLine,LFLen,&LFCt) == -1) {
					return;
				}
			}
			for(Tab=0;Tab<3;Tab++) {		/* Transfer String Image PArt 0 */
				RolProc(Tab);
				if(SendBuff8LPI(FontLine,LFLen,&LFCt) == -1) {
					return;
				}
			}
		}
		else {
			for(Tab=3;Tab<6;Tab++) {
				RolProc(Tab);
				if(SendBuff(FontLine,LFLen,&LFCt) == -1) {
					return;
				}
			}
			for(Tab=0;Tab<3;Tab++) {
				RolProc(Tab);
				if(SendBuff(FontLine,LFLen,&LFCt) == -1) {
					return;
				}
			}
		}
	}
	else {
		if(BitImgMode == NOT_BITIMG) {				/* Not Bit Image Mode */
			if(PrtSpeed == SP_300LPM) { 		   /* Hangule 300 Lpm Mode */
				for(Tab=0;Tab<6;Tab++) {
					RolProc(Tab);
					if(SendBuff300(FontLine,LFLen,&LFCt) == -1) {
						return;
					}
				} /* for */
			}
			else if(LFInfo.DotLenOfLine == 22) {
				if(SemiExp == SEMI_EXPAND) {
					for(Tab=0;Tab<8;Tab++) {
						ExpRolProc(Tab);
						if(ExpSendBuff(FontLine,LFLen,&LFCt) == -1) {
							return;
						}
					}
				}
				else {
					for(Tab=0;Tab<6;Tab++) {
						RolProc(Tab);
						if(SendBuff8LPI(FontLine,LFLen,&LFCt) == -1) {
							return;
						}
					}
				}
			}
			else {
				if(SemiExp == SEMI_EXPAND) {
					for(Tab=0;Tab<8;Tab++) {
						ExpRolProc(Tab);
						if(ExpSendBuff(FontLine,LFLen,&LFCt) == -1) {
							return;
						}
					}
				}
				else {
					for(Tab=0;Tab<6;Tab++) {
						RolProc(Tab);
						if(SendBuff(FontLine,LFLen,&LFCt) == -1) {
							return;
						}
					}
				}
			}
		}
		else {
			for(Tab=0;Tab<6;Tab++) {		   /* Bit Image Mode */
				ImageRolProc(Tab);
				if(SendBuff(FontLine,LFLen,&LFCt) == -1) {
					return;
				}
			} /* for */
		}
	}
}
