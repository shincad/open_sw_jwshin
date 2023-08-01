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

   2003-01-10 2:39오후  JDHAN           Modified for Monitor-TV
****************************************************************************/

//****************************************************************//
//화일참조
//****************************************************************//
#include "TopHeader.h"

#ifdef MCU_MTV230
// ****************************************************************************************
// Variable	Definition
// ****************************************************************************************
xdata	BYTE	xADC		_at_	0xF10;
xdata	BYTE	xDAC[4]		_at_	0xF20;
xdata	BYTE	xPADMOD1	_at_	0xF2B;
xdata	BYTE	xPADMOD2	_at_	0xF2C;
xdata	BYTE	xPADMOD3	_at_	0xF2D;
xdata	BYTE	xPADMOD4	_at_	0xF2E;
xdata	BYTE	xOPTION1	_at_	0xF2F;

xdata	BYTE	xHVSTUS		_at_	0xF40;
xdata	BYTE	xHCNTH		_at_	0xF41;
xdata	BYTE	xHCNTL		_at_	0xF42;
xdata	BYTE	xVCNTH		_at_	0xF43;
xdata	BYTE	xVCNTL		_at_	0xF44;
xdata	BYTE	xINTFLG		_at_	0xF48;
xdata	BYTE	xINTEN		_at_	0xF49;

xdata	BYTE	xWDT		_at_	0xF18;

xdata	BYTE	xIICCTR		_at_	0xF00;
xdata	BYTE	xIICSTUS1st	_at_	0xF01;
xdata	BYTE	xIICSTUS	_at_	0xF02;
xdata	BYTE	xINTFLGI2C	_at_	0xF03;
xdata	BYTE	xINTENI2C	_at_	0xF04;
xdata	BYTE	xMBUF		_at_	0xF05;

xdata	BYTE	xRXABUF		_at_	0xF06;
xdata	BYTE	xSLVAADR	_at_	0xF07;
xdata	BYTE	xRXBBUF   	_at_ 	0xF08;
xdata 	BYTE	xSLVBADR  	_at_ 	0xF09;


xdata	BYTE	xISPSLV		_at_	0xF0B;
xdata	BYTE	xISPEN		_at_	0xF0C;

xdata	BYTE	xP60		_at_	0xF28;
xdata	BYTE	xP61		_at_	0xF29;
xdata	BYTE	xP62		_at_	0xF2A;
                        	
xdata	BYTE	xP40		_at_	0xF30;
xdata	BYTE	xP41		_at_	0xF31;
xdata	BYTE	xP42		_at_	0xF32;
xdata	BYTE	xP43		_at_	0xF33;
xdata	BYTE	xP44		_at_	0xF34;
xdata	BYTE	xP45		_at_	0xF35;
xdata	BYTE	xP46		_at_	0xF36;
xdata	BYTE	xP47		_at_	0xF37;
                        	
xdata	BYTE	xP50		_at_	0xF38;
xdata	BYTE	xP51		_at_	0xF39;
xdata	BYTE	xP52		_at_	0xF3A;
xdata	BYTE	xP53		_at_	0xF3B;
xdata	BYTE	xP54		_at_	0xF3C;
xdata	BYTE	xP55		_at_	0xF3D;
xdata	BYTE	xP56		_at_	0xF3E;
xdata	BYTE	xP57		_at_	0xF3F;

xdata	BYTE	xOSDRA		_at_	0xFA0;
xdata	BYTE	xOSDCA		_at_	0xFA1;
xdata	BYTE	xOSDDT0		_at_	0xFA2;
xdata	BYTE	xOSDDT1		_at_	0xFA3;
xdata	BYTE	xOSD_WIN_REG[15]	_at_	0x0FC0;
xdata	BYTE	xOSDW_OPTION[10] 	_at_	0x0FD0;

#endif