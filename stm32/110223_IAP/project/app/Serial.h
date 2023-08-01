#ifndef	_SERIAL_H
#define	_SERIAL_H

#include "stm32f10x_type.h"

#define	STX	0x02
#define	ETX	0x03
#define	ACK	0x06
#define	NAK	0x15
#define	ENQ	0x05


#define		UART1_TX_BUF_SIZE	0x400
#define		UART1_TX_MSK		UART1_TX_BUF_SIZE - 1

#define		UART1_RX_BUF_SIZE	0x400
#define		UART1_RX_MSK		UART1_RX_BUF_SIZE - 1

#define		UART2_TX_BUF_SIZE	0x400
#define		UART2_TX_MSK		UART2_TX_BUF_SIZE - 1

#define		UART2_RX_BUF_SIZE	0x20
#define     UART2_RX_MSK        UART2_RX_BUF_SIZE - 1;

#define		UART3_TX_BUF_SIZE	0x80
#define		UART3_RX_BUF_SIZE	0x80

#define		UART4_TX_BUF_SIZE	0x400
#define		UART4_TX_MSK		UART4_TX_BUF_SIZE - 1

#define		UART4_RX_BUF_SIZE	0x400
#define		UART4_RX_MSK		UART4_RX_BUF_SIZE - 1

#define		UART5_TX_BUF_SIZE	0x80
#define		UART5_RX_BUF_SIZE	0x80

#define     XON     0x11
#define     XOFF    0x13


enum {RX_IDLE,RX_STX,RX_LI_MSB,RX_LI_LSB,RX_DATA,WAIT_ETX,RX_FRAME,RX_ENQ,RX_ERROR};
enum {TX_IDLE,TX_FRAME};

typedef	struct _COM_CON
{
 	u16 txp,rxp,rxread;
	u8  RxState;
	u8 	TxState;
//	u8  TxSize;
	u16 RxSize;
	
} COM_CON,*PCOM_CON;

//enum{
extern void InitPort(u16 BaudRate, u8 StopBits,u8 BitsPerCharacter,u8 Parity,u8 FlowControl);
extern void SendHost(u8 size,u8 *buf);
extern void SendPrinter(u16 size,u8 *buf);
extern void SendWiz(u16 size,u8 *buf);


extern COM_CON	COM1,COM2,COM3,COM4,COM5;


extern u8 UART1RxBuf[UART1_RX_BUF_SIZE];
extern u8 UART1TxBuf[UART1_TX_BUF_SIZE];

extern u8 UART2TxBuf[UART2_TX_BUF_SIZE];
extern u8 UART2RxBuf[UART2_RX_BUF_SIZE];


extern u8 UART4TxBuf[UART4_TX_BUF_SIZE];
extern u8 UART4RxBuf[UART4_RX_BUF_SIZE];

extern void SerialInit(void);

extern u8 getch(void);
extern u8 kbhit(void);


extern void Com1Send(u8 ch);

#endif
