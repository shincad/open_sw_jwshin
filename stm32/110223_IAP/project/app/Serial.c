//---------------------------------------------
//
//		IQS I/O Board Firmware
//		FileName : Serial.c
//		Version : 1.00
//
//		Date   : 2010.12.17
//		Author : Shin Jung Wook
//						 DNP System.	
//						 
//---------------------------------------------

#include "Serial.h"
#include "stm32f10x_lib.h"
#include "HostLine.h"
#include "util.h"

//char flag=0;
//char aflag = 0;


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  Function Declaration
----------------------------------------------------------------------------------*/     
void UART1RxIsr(char read);
void UART1TxIsr(void);

void UART2RxIsr(char read);
void UART2TxIsr(void);

void Com1Send(u8 ch);
void Com2Send(u8 ch);
void Com3Send(u8 ch);
void Com4Send(u8 ch);
void Com5Send(u8 ch);


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  Variable Declaration
----------------------------------------------------------------------------------*/     
u8 UART1RxBuf[UART1_RX_BUF_SIZE];
u8 UART1TxBuf[UART1_TX_BUF_SIZE];

u8 UART2TxBuf[UART2_TX_BUF_SIZE];
u8 UART2RxBuf[UART2_RX_BUF_SIZE];

u8 UART3TxBuf[UART3_TX_BUF_SIZE];
u8 UART3RxBuf[UART3_RX_BUF_SIZE];

u8 UART4TxBuf[UART4_TX_BUF_SIZE];
u8 UART4RxBuf[UART4_RX_BUF_SIZE];

u8 UART5TxBuf[UART5_TX_BUF_SIZE];
u8 UART5RxBuf[UART5_RX_BUF_SIZE];


COM_CON	COM1,COM2,COM3,COM4,COM5;

void SendHost(u8 size,u8 *buf);


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  Serial Initialization
      Serial Variable Initialization.
  Arg :
	void
  Return :
	void
----------------------------------------------------------------------------------*/     
void SerialInit(void)
{
	COM1.txp = 0;
	COM1.rxp = 0;
	COM1.rxread = 0;

	COM1.RxState = RX_IDLE;
//	COM1.TxState = 0;
//	COM1.TxSize = 0;
	COM1.RxSize = 0;

	COM2.txp = 0;
	COM2.rxp = 0;
    COM2.rxread = 0;
    
	COM2.RxState = 0;
	COM2.RxSize = 0;

	COM4.txp = 0;
	COM4.rxp = 0;
    COM4.rxread = 0;
    
	COM4.RxState = 0;
	COM4.RxSize = 0;
}


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  Com1 Transmit (Sendhost)
  	Com1을 이용해 Host(PC)로 Data를 전송.    
  Arg : 
  size / *buf
  Return :
	void
----------------------------------------------------------------------------------*/   
void SendHost(u8 size,u8 *buf)
{
    u16 tsize;
    u16 i;
    u32 timeout;
    tsize = 0;
    if(size == 0) return;
    timeout = size/1000;
    if(timeout == 0) timeout = 1;
//    DelayTick = timeout;
    DelayTick = 3;
    for(i=0;i<size;i++) UART1TxBuf[i] = buf[i];
    while(1)
    {
		FeedDog();		// WatchDog Reload
        if(USART_GetFlagStatus(USART1,USART_FLAG_TXE))
        {
            Com1Send(UART1TxBuf[tsize]);
            tsize++;
        }
        if(tsize >= size)
        {
            DelayTick = 0;
            return;
        }
        if(DelayTick==0) return;    // timeout
    }
/*  
	u8 i;
	if(size > UART1_TX_BUF_SIZE) return;


	while(COM1.TxState != TX_IDLE);
	COM1.TxState = TX_FRAME;

  	COM1.TxSize = size;
	for(i=0;i<size;i++)	UART1TxBuf[i] = buf[i];

	COM1.txp = 1;
    
	Com1Send(UART1TxBuf[0]);
*/
}

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  Com2 Transmit (SendPrinter)
  	Com2를 이용해 Printer로 Data를 전송.    
  Arg : 
  size / *buf
  Return :
	void
----------------------------------------------------------------------------------*/   
void SendPrinter(u16 size,u8 *buf)
{
    u16 tsize;
    u16 i;
    u32 timeout;
    tsize = 0;
    if(size == 0) return;
    timeout = size/1000;
    if(timeout == 0) timeout = 1;
//    DelayTick = timeout;
    DelayTick = 10;
    for(i=0;i<size;i++) UART2TxBuf[i] = buf[i];
    while(1)
    {
	  	FeedDog();
        if(USART_GetFlagStatus(USART2,USART_FLAG_TXE))
        {
            Com2Send(UART2TxBuf[tsize]);
            tsize++;
        }
        if(tsize >= size)
        {
            DelayTick = 0;
            return;
        }
        if(DelayTick==0) return;    // timeout
    }
}

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  Com4 Transmit (SendWiz)
  	Com4를 이용해 SerialtoEthernet Module로 Data 전송    
  Arg : 
  size / *buf
  Return :
	void
----------------------------------------------------------------------------------*/   
void SendWiz(u16 size,u8 *buf)
{
    u16 tsize;
    u16 i;
    u32 timeout;
    tsize = 0;
    if(size == 0) return;
    timeout = size/1000;
    if(timeout == 0) timeout = 1;
//    DelayTick = timeout;
    DelayTick = 10;
    for(i=0;i<size;i++) UART4TxBuf[i] = buf[i];
    while(1)
    {
	  	FeedDog();
        if(USART_GetFlagStatus(UART4,USART_FLAG_TXE))
        {
            Com4Send(UART4TxBuf[tsize]);
            tsize++;
        }
        if(tsize >= size)
        {
            DelayTick = 0;
            return;
        }
        if(DelayTick==0) return;    // timeout
    }
}


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  Com1 Receive
  	USART1 Interrupt를 이용해 Buffering된 Data를 Receive하는 Routine    
  Arg : 
  void
  Return :
	ret
----------------------------------------------------------------------------------*/   
u8 getch(void)
{
	char ret;
 	if(COM1.rxp == COM1.rxread) return 0;

	ret = UART1RxBuf[COM1.rxread++];
	COM1.rxread = COM1.rxread & UART1_RX_MSK;
	return ret;
}

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  Com1 data_receive
  	COM1 의 Rx Pointer와 rxread Pointer가 맞지 않을 경우, TRUE를 return하여 Data 수집
  	keyhit 감시용 Routine
  Arg : 
  void
  Return :
	u8
----------------------------------------------------------------------------------*/   
u8 kbhit(void)
{
 	if(COM1.rxp != COM1.rxread) return TRUE;
	else return 0;
}

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  UART1RxISr
  	UART1 Rx Interrupt Routine
  		실제 Com1 Rx Interrupt Routine (호출되어지는 Routine임)
  		호출하는 Handler는 (USART1_IRQHandler)
  Arg : 
  char read
  Return :
	void
----------------------------------------------------------------------------------*/   
void UART1RxIsr(char read)
{
	UART1RxBuf[COM1.rxp] = read;
	COM1.rxp++;
	COM1.rxp = COM1.rxp & UART1_RX_MSK;
}


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  UART2RxISr
  	UART2 Rx Interrupt Routine
  		실제 Com2 Rx Interrupt Routine (호출되어지는 Routine임)
  		호출하는 Handler는 (USART2_IRQHandler)
  Arg : 
  char read
  Return :
	void
----------------------------------------------------------------------------------*/   
void UART2RxIsr(char read)
{
    UART2RxBuf[COM2.rxp] = read;
    COM2.rxp++;
    COM2.rxp = COM2.rxp & UART2_RX_MSK;
}


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  UART4RxISr
  	UART4 Rx Interrupt Routine
  		실제 Com4 Rx Interrupt Routine (호출되어지는 Routine임)
  		호출하는 Handler는 (USART4_IRQHandler)
  Arg : 
  char read
  Return :
	void
	현재는 사용하지 않으므로, Remark 처리함.
----------------------------------------------------------------------------------*/   
/*
void UART4RxIsr(char read)
{
    UART4RxBuf[COM4.rxp] = read;
    COM4.rxp++;
    COM4.rxp = COM4.rxp & UART4_RX_MSK;
}
*/    // -jwshin 101210



/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  Com1Send,Com2Send,Com3Send,Com4Send,Com5Send
  	각 Serial 별 Tx 전송 Routine임.
  	현재 Tx는 Interrupt가 아닌, Polling 방식을 사용.
  Arg : 
  u8 ch
  Return :
	void
----------------------------------------------------------------------------------*/   
void Com1Send(u8 ch)
{
	USART_SendData(USART1,ch);
}
void Com2Send(u8 ch)
{
	USART_SendData(USART2,ch);
}
void Com3Send(u8 ch)
{
	USART_SendData(USART3,ch);
}
void Com4Send(u8 ch)
{
	USART_SendData(UART4,ch);
}
void Com5Send(u8 ch)
{
	USART_SendData(UART5,ch);
}

