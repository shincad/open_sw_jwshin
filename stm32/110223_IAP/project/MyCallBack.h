//---------------------------------------------
//
//		IQS I/O Board Firmware
//		FileName : MyCallBack.h
//		Version : 1.00
//
//		Date   : 2010.12.17
//		Author : Shin Jung Wook
//						 DNP System.	
//						 
//---------------------------------------------
#ifndef _MY_CALL_BACK
#define _MY_CALL_BACK

extern void UART1TxIsr(void);
extern void UART1RxIsr(char read);

extern void UART2TxIsr(void);
extern void UART2RxIsr(char read);
//extern void UART4RxIsr(char read);      // - jwshin 101217

extern void TickIsr(void);

#endif
