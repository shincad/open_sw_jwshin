/****************************************************************************
   +----------------------------------------------------------------------+
   | Copyright EDtech co.ltd 2002                                         |
   | EDtech co.ltd reserves the right to change products                  |
   | or specifications without notice.                                    |
   +----------------------------------------------------------------------+
   Project    : TFT LCD monitor & TV
   Version    : 
   File Name  : 
   Functions  : 
   Revision   :

   2003-01-10 2:39¿ÀÈÄ  JDHAN           Modified for Monitor-TV
****************************************************************************/

#ifdef MCU_MTV230

extern	xdata	BYTE	xADC;
extern	xdata	BYTE	xDAC[4];
extern	xdata	BYTE	xPADMOD1;
extern	xdata	BYTE	xPADMOD2;
extern	xdata	BYTE	xPADMOD3;
extern	xdata	BYTE	xPADMOD4;
extern	xdata	BYTE	xOPTION1;

extern	xdata	BYTE	xHVSTUS;
extern	xdata	BYTE	xHCNTH;
extern	xdata	BYTE	xHCNTL;
extern	xdata	BYTE	xVCNTH;
extern	xdata	BYTE	xVCNTL;
extern	xdata	BYTE	xINTFLG;
extern	xdata	BYTE	xINTEN;

extern	xdata	BYTE	xWDT;

extern	xdata	BYTE	xIICCTR;
extern	xdata	BYTE	xIICSTUS1st;
extern	xdata	BYTE	xIICSTUS;
extern	xdata	BYTE	xINTFLGI2C;
extern	xdata	BYTE	xINTENI2C;
extern	xdata	BYTE	xMBUF;

extern	xdata	BYTE	xRXABUF;
extern	xdata	BYTE	xSLVAADR;
extern	xdata	BYTE	xRXBBUF;
extern	xdata 	BYTE	xSLVBADR;


extern	xdata	BYTE	xISPSLV;
extern	xdata	BYTE	xISPEN;

extern	xdata	BYTE	xP60;
extern	xdata	BYTE	xP61;
extern	xdata	BYTE	xP62;

extern	xdata	BYTE	xP40;
extern	xdata	BYTE	xP41;
extern	xdata	BYTE	xP42;
extern	xdata	BYTE	xP43;
extern	xdata	BYTE	xP44;
extern	xdata	BYTE	xP45;
extern	xdata	BYTE	xP46;
extern	xdata	BYTE	xP47;

extern	xdata	BYTE	xP50;
extern	xdata	BYTE	xP51;
extern	xdata	BYTE	xP52;
extern	xdata	BYTE	xP53;
extern	xdata	BYTE	xP54;
extern	xdata	BYTE	xP55;
extern	xdata	BYTE	xP56;
extern	xdata	BYTE	xP57;

extern	xdata	BYTE	xOSDRA;
extern	xdata	BYTE	xOSDCA;
extern	xdata	BYTE	xOSDDT0;
extern	xdata	BYTE	xOSDDT1;
extern	xdata	BYTE	xOSD_WIN_REG[15];
extern	xdata	BYTE	xOSDW_OPTION[10];

#endif