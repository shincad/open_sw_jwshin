//---------------------------------------------
//
//		IQS I/O Board Firmware
//		FileName : Wiznet.c
//		Version : 1.00
//
//		Date   : 2010.12.17
//		Author : Shin Jung Wook
//						 DNP System.	
//						 
//---------------------------------------------
#include "wiznet.h"
#include "serial.h"
#include "DbgPrint.h"
#include "util.h"     // +jwshin 101210
void WizTest(void);

void WizInit(void);



void WizTest(void)
{
	u8 ch;
//	u32 a,*p;   //-jwshin 101210
        u32 a;
	PrtMsg("WizTest");
	while(1)
	{
	  	FeedDog();
	  	if(kbhit())
		{
			ch = getch();
			switch(ch)
			{
			case '1':
			  	for(a=0;a<10;a++)
				{
				  	UART4TxBuf[a] = 0x30+a;
				}
				SendWiz(10,&UART4TxBuf[0]);
			  	break;
			case '2':
			  	break;
			case '3':
				break;
			case '4':
			  	break;
			default:
			  	break;
			}
		}
		if(COM4.rxp != COM4.rxread)
		{
			PrtChar(UART4RxBuf[COM4.rxread]);
			COM4.rxread++;
			COM4.rxread = COM4.rxread & UART4_RX_MSK;
		}
	}
}
  
  
  


void WizInit(void)
{
  
  
  
}
