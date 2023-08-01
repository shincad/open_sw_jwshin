//---------------------------------------------
//
//		IQS I/O Board Firmware
//		FileName : HostLine.h
//		Version : 1.00
//
//		Date   : 2010.12.17
//		Author : Shin Jung Wook
//						 DNP System.	
//						 
//---------------------------------------------
#ifndef	_HOST_LINE_H
#define	_HOST_LINE_H

#include "stm32f10x_type.h"

#define	STX	0x02
#define	ETX	0x03
#define	ACK	0x06
#define	NAK	0x15
#define	ENQ	0x05
#define NULL	0




extern void 	HostLineIsr(char read);
extern void		HostLine(void);

extern void 	SendNAK(void);
extern void 	SendACK(void);

#endif
