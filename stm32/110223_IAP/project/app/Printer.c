//---------------------------------------------
//
//		IQS I/O Board Firmware
//		FileName : Printer.c
//		Version : 1.00
//
//		Date   : 2010.12.17
//		Author : Shin Jung Wook
//						 DNP System.	
//						 
//---------------------------------------------
#include "Serial.h"
#include "dbgPrint.h"
#include "PrintMsg.h"
#include "util.h"
#include "Printer.h"
#include "rtc.h"
#include "stm32f10x_flash.h"


#define	REG_COUNT				BKP_DR10
#define REG_DUMP_SIZE           BKP_DR22
#define REG_INDEX_CNT           BKP_DR14
#define REG_INDEX_YEAR          BKP_DR15
#define REG_INDEX_MONTH         BKP_DR16
#define REG_INDEX_DAY           BKP_DR17
#define REG_INDEX_AMPM          BKP_DR18
#define REG_INDEX_HOUR          BKP_DR19
#define REG_INDEX_MINUTE        BKP_DR20
#define REG_INDEX_SECOND        BKP_DR21


u8 SensorCmd[]	={0x1b,0x73}; //sensor command


//#define	PRINTER_MSG_ADR	        0x803c000
//#define	PRINTER_INDEX_ADR	    0x803b000

#define	NO_PAPER	1
#define	PAPER		0

FLASH_Status fs; 


void	GetPrinterSensor(void);
void 	PrinterTest(void);
void    CheckRxState(void);  
void    PrinterIsr(u8 read);
u32 	PrtCnt;
u16     DataPos;

u16	HeadMsgSize,MidMsgSize,TailMsgSize;
u8 PaperSensorState;

PRINT_COUNTER pcnt;

u8 		abfirst = 0;
u8 		PrinterSensor;
void 	GetPrintCounter(void);
void 	SetPrintCounter(u32 count);
void 	IncCounter(void);
void   	AbnormalIsr(u8 read);
void 	AbnormalLine(void);
void 	PrinterOut(void);
void    SendDump(void);
void  	SetPrinterTimeOut(void);


void    WriteMessage(u8 mode,u16 index,u16 size);
//    WriteDumpData(u8 *p,u16 size);

u16 	PrtSize;
void    RestoreIndex(void);
u16 	mcnt,pyear,pmonth,pday,pampm,phour,pminute,psecond;
u32 	FindIndex(u32 in,P_RTC_TIME ptime);

void    WriteDumpTest(u8 *p,u16 size);


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  Printer 초기화 Routine
  Arg :
	void
  Return :
	void
  비상발권 시 Counter를 위해, 9000으로 Setting한다.	
----------------------------------------------------------------------------------*/ 
void 	PrinterInit(void)
{
	SetPrintCounter(9000);			// +jwshin 110111 강제지정을 위해...
	

    RestoreIndex();

    PWR_BackupAccessCmd(ENABLE);
    PrtSize = BKP_ReadBackupRegister(REG_DUMP_SIZE);
    RTC_WaitForLastTask();
	
}
/*
void	EraseTest(void)
{
  	FLASH_Status fs;
  	u32 fadr;
    fadr = (u32)PrinterMsgLocator;
    fs = FLASH_ErasePage(fadr);
	delay(10);
	PrtChar(fs);
	PrtMsg("  is Erase result");
}
*/

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  현재 Thermal Printer의 상태를 알기 위해, Printer에 Status Code를 전송.
  Arg :
	void
  Return :
	void
  1b 73을 전송하면, 프린터는 상태 값을 I/O Board로 전송..	
----------------------------------------------------------------------------------*/ 
void	GetPrinterSensor(void)
{
	SendPrinter(sizeof(SensorCmd),&SensorCmd[0]);			// 0x1b, 0x73 Sensor Command Transmit
}


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  RTC에 저장되어 있는 Backup Value를 읽어들임.
  Arg :
	void
  Return :
	void
----------------------------------------------------------------------------------*/ 
void    RestoreIndex(void)
{
  
    PWR_BackupAccessCmd(ENABLE);
	
    mcnt = BKP_ReadBackupRegister(REG_INDEX_CNT);
    RTC_WaitForLastTask();

    pyear = BKP_ReadBackupRegister(REG_INDEX_YEAR);
    RTC_WaitForLastTask();

    pmonth = BKP_ReadBackupRegister(REG_INDEX_MONTH);
    RTC_WaitForLastTask();

    pday = BKP_ReadBackupRegister(REG_INDEX_DAY);
    RTC_WaitForLastTask();

    pampm = BKP_ReadBackupRegister(REG_INDEX_AMPM);
    RTC_WaitForLastTask();
  
    phour = BKP_ReadBackupRegister(REG_INDEX_HOUR);
    RTC_WaitForLastTask();

    pminute = BKP_ReadBackupRegister(REG_INDEX_MINUTE);
    RTC_WaitForLastTask();

    psecond = BKP_ReadBackupRegister(REG_INDEX_SECOND);
    RTC_WaitForLastTask();
    PWR_BackupAccessCmd(DISABLE);
}

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  Index에 맞게, RTC의 Backup Register로 Write...
  Arg :
	void
  Return :
	void
----------------------------------------------------------------------------------*/ 
void SaveIndex(u8* p)
{
    u16 stmp;
    PWR_BackupAccessCmd(ENABLE);
	
    stmp = p[0];
    stmp = stmp<<8;
    stmp = (stmp & 0xff00) | p[1]; 
    BKP_WriteBackupRegister(REG_INDEX_CNT,stmp);
    RTC_WaitForLastTask();
  
    stmp = p[2];
    stmp = stmp<<8;
    stmp = (stmp & 0xff00) | p[3]; 
    BKP_WriteBackupRegister(REG_INDEX_YEAR,stmp);
    RTC_WaitForLastTask();

    stmp = p[4];
    stmp = stmp<<8;
    stmp = (stmp & 0xff00) | p[5]; 
    BKP_WriteBackupRegister(REG_INDEX_MONTH,stmp);
    RTC_WaitForLastTask();

    stmp = p[6];
    stmp = stmp<<8;
    stmp = (stmp & 0xff00) | p[7];
    BKP_WriteBackupRegister(REG_INDEX_DAY,stmp);
    RTC_WaitForLastTask();

    stmp = p[8];
    stmp = stmp<<8;
    stmp = (stmp & 0xff00) | p[9]; 
    BKP_WriteBackupRegister(REG_INDEX_AMPM,stmp);
    RTC_WaitForLastTask();

    stmp = p[10];
    stmp = stmp<<8;
    stmp = (stmp & 0xff00) | p[11]; 
    BKP_WriteBackupRegister(REG_INDEX_HOUR,stmp);
    RTC_WaitForLastTask();

    stmp = p[12];
    stmp = stmp<<8;
    stmp = (stmp & 0xff00) | p[13]; 
    BKP_WriteBackupRegister(REG_INDEX_MINUTE,stmp);
    RTC_WaitForLastTask();

    stmp = p[14];
    stmp = stmp<<8;
    stmp = (stmp & 0xff00) | p[15]; 
    BKP_WriteBackupRegister(REG_INDEX_SECOND,stmp);
    RTC_WaitForLastTask();
    PWR_BackupAccessCmd(DISABLE);
}

void PrintTest(void)
{
	u8 ch;
	u32 a,*p;
	while(1)
	{
	  	if(kbhit())
		{
			ch = getch();
			switch(ch)
			{
			case '1':
//			  	PrtShort(GPIO_ReadInputData(GPIOD));
//				PrtLF();
//			  	PrinterOut();
				SendTime();					// +jwshin 110106	
			  	break;
			case '2':
			  	PrtMsg("Sensor value");
			  	PrtChar(Sensor);
//				PrtLF();
			  	break;
			case '3':
			  	PrinterTest();
				break;
			case '4':
				p = (u32*)PrinterMsgLocator;
				a = *p;
				PrtInt(a);
			  	break;
			default:
			  	break;
			}
		}
	}
}

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  비상 발권 모드일 때, 프린터 Line의 상태 감시...
  Arg :
	void
  Return :
	void
----------------------------------------------------------------------------------*/ 
void 	AbnormalLine(void)
{
  	u8 ch;
    if(COM2.rxp != COM2.rxread)
    {
        ch = UART2RxBuf[COM2.rxread];
        AbnormalIsr(ch);
        COM2.rxread++;
		COM2.rxread = COM2.rxread & UART2_RX_MSK;
    }
	if(PaperSensorState == NO_PAPER)
	{
		if(DelayTick == 0)
		{
		  	PaperSensorState = PAPER;
			PrinterOut();				// +jwshin 110111
		//	PrintDumpTest1();			// +jwshin 110110
			DelayTick = 200;
//			delay(200);		//2초 안에 종이 출력
		}
	}
}

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  비상 발권 모드 Service Routine
  Arg :
	void
  Return :
	void
----------------------------------------------------------------------------------*/ 

void   AbnormalIsr(u8 read)
{
   	SetPrinterTimeOut();
	if(COM2.RxState == RX_IDLE)
    {
        if(read == STX) COM2.RxState = RX_STX;
    }
    else if(COM2.RxState == RX_STX)
    {
		PrinterSensor = read;
	  	if(read == 0x80) 
	  	{
	  		PaperSensorState = NO_PAPER;
	  		LedStatus = LedStatus & 0xfe;			// +jwshin 110112
	  	}
		else if(read == 0x90) 
		{
			PaperSensorState = PAPER;
			EmerLedFlag = 1;						// +jwshin 110112
			LedStatus = LedStatus | 0x01;			// +jwshin 110112
			//---- PPOut Sensor에 용지가 걸려 있을 경우, Led를 Turn On...
			//---- Normal Mode일 때 다시 꺼줘야 한다.
		}
		//---- +jwshin 110112   감열지가 떨어졌을 때~!..	
		else if(read == 0x81) 
		{
			//---------------- 사용하지 않으므로 Remark
			/*
			UART1TxBuf[0] = STX;
			UART1TxBuf[1] = 0x02;
			UART1TxBuf[2] = 'P';
			UART1TxBuf[3] = 'E';
			UART1TxBuf[4] = ETX;
			SendHost(5,&UART1TxBuf[0]);
			*/
			//-----------------------------------------------
		}	
        COM2.RxState = WAIT_ETX;
    }
    else if(COM2.RxState == WAIT_ETX)
	{
		if(read == ETX) COM2.RxState = RX_IDLE;
	}
}

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  PrinterLine Check...
  Arg :
	void
  Return :
	void
----------------------------------------------------------------------------------*/ 
void PrinterLine(void)
{
    u8 ch,tmp;
    u16 i,index;
    if(COM2.rxp != COM2.rxread)
    {
        ch = UART2RxBuf[COM2.rxread];
   //     PrtChar(ch);					// +jwshin 110110
        PrinterIsr(ch);
        COM2.rxread++;
    }
    if(COM2.RxState == RX_FRAME)
    {
        UART1TxBuf[0] = STX;
        UART1TxBuf[1] = COM2.RxSize+2;
        UART1TxBuf[2] = 'I';
        index = 3;
        for(i=0;i<COM2.RxSize;i++)
        {
			tmp = UART2RxBuf[DataPos+i];
            UART1TxBuf[index] = tmp;
            index++;
        }
        UART1TxBuf[index] = ETX;
        SendHost(COM2.RxSize+4,&UART1TxBuf[0]);

        COM2.RxSize = 0;
        COM2.RxState = RX_IDLE;
    }
//    CheckRxState();
}

void PrinterTest(void)
{
	SendPrinter(sizeof(Dump),&Dump[0]);
}

void PrinterOut(void)
{
 
 
    u16 size;
    vu8* p;
    u8  read;
	
	RTC_TIME time;
	
    u16 i;

	
	size = PrtSize;
    p =(vu8*) PrinterMsgLocator;
	GetRTC(&time);
	
    for(i=0;i<size;i++)
    {
        i = FindIndex(i,&time);
        read = *(p+i);
		SendPrinter(1,&read);
    }

    
}


void PrinterOut2(void)
{
    u16 size;
    u8* p;
    u8  read;
	
	RTC_TIME time;
	
    u16 i;


	//--- 강제적으로 Dump Array에서 RTC에 저장되어있는 부분을 지정...
	// +jwshin 110110
	// 원칙적으로는 SaveIndex에서 해 주어야만 함...
	mcnt = 104;
	pyear = 149;
	pmonth = 154;
	pday = 157;
	pampm = 160;
	phour = 165;
	pminute = 168;
	psecond = 171;
	p = &Dump[0];
	size = sizeof(Dump);

	GetRTC(&time);
	
    for(i=0;i<size;i++)
    {
        i = FindIndex(i,&time);
        read = *(p+i);
		SendPrinter(1,&read);
    }
	
}	

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  RTC의 날짜를 Printer로 전송...
  Arg :
	void
  Return :
	void
----------------------------------------------------------------------------------*/ 
u32 FindIndex(u32 in,P_RTC_TIME ptime)
{
	PRINT_COUNTER  pc;
  	if(in == mcnt)
	{
	  	PrtCnt++;
		pc.cnt = GetBCD32(PrtCnt);
		SendPrinter(4,&pc.c[0]);
		return in+4;
	}
	else if(in == pyear)
	{
		SendPrinter(4,&(ptime->Year[0]));
		return in+4;
	}
	else if(in == pmonth)
	{
		SendPrinter(2,&(ptime->Month[0]));
		return in+2;
	}
	else if(in == pday)
	{
		SendPrinter(2,&(ptime->Day[0]));
		return in+2;
	}
	else if(in == pampm)
	{
		SendPrinter(4,&(ptime->AmPm[0]));
		return in+4;
	}
	else if(in == phour)
	{
		SendPrinter(2,&(ptime->Hour[0]));
		return in+2;
	}
	else if(in == pminute)
	{
		SendPrinter(2,&(ptime->Minute[0]));
		return in+2;
	}
	else if(in == psecond)
	{
		SendPrinter(2,&(ptime->Second[0]));
		return in+2;
	}
	return in;
}
u8   WriteDumpData(u8 *p,u16 size)
{
    u32 fadr;
    u16 s,wsize;
    u8 b;
    u16 index;
    int i;
	FLASH_Status fs;
    
    wsize = 0;
    
    PWR_BackupAccessCmd(ENABLE);
  	BKP_WriteBackupRegister(REG_DUMP_SIZE,size);
	RTC_WaitForLastTask();
	
FLASH_Unlock();

    fadr = (u32)PrinterMsgLocator;
  	fs = FLASH_ErasePage(fadr);
	delay(40);
	if(fs != FLASH_COMPLETE) return 0;
    
    index=0;

    for(i=0;i<1000;i++)
    {
	  	FeedDog();
        b = p[index++];
        s = p[index++];
        s = ((s<<8) & 0xff00);
        s = s | b;
        fs = FLASH_ProgramHalfWord(fadr,s);
		if(fs != FLASH_COMPLETE) return 0;
        fadr = fadr + 2;
        wsize = wsize +2;
        if(wsize >= size) break;
    }
FLASH_Lock();
	
	return 1;
}

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  Printer Service Routine
  Arg :
	void
  Return :
	void
----------------------------------------------------------------------------------*/ 
void    PrinterIsr(u8 read)
{
  	SetPrinterTimeOut();
	if(COM2.RxState == RX_IDLE)
    {
        if(read == STX) COM2.RxState = RX_STX;
    }
    else if(COM2.RxState == RX_STX)
    {
		PrinterSensor = read;
		//------------------ +jwshin 110112 감열지 떨어짐~!!!...
		if(read == 0x81) 
		{
			//----------------- 사용하지 않으므로 Remark
			/*
			UART1TxBuf[0] = STX;
			UART1TxBuf[1] = 0x02;
			UART1TxBuf[2] = 'P';
			UART1TxBuf[3] = 'E';
			UART1TxBuf[4] = ETX;
			SendHost(5,&UART1TxBuf[0]);
			*/
			//---------------------------------------------
		}
        COM2.RxState = WAIT_ETX;
    }
    else if(COM2.RxState == WAIT_ETX)
	{
		if(read == ETX) COM2.RxState = RX_IDLE;
	}
}

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  비상 발권을 위한, Printer Counter 강제 지정...
  Arg :
	void
  Return :
	void
----------------------------------------------------------------------------------*/ 
void SetPrintCounter(u32 count)
{
  	PrtCnt = 9000;
//	PrtCnt = count;				// -jwshin 110111
								// UART1을 통한 지정일 때, 사용할 것...
	pcnt.cnt = GetBCD32(count);
}


void GetPrintCounter(void)
{
  	u16 cnt;
	cnt = PrtCnt;
	pcnt.cnt = GetBCD32(cnt);
}

void IncCounter(void)
{
// 	u16 cnt;
	PrtCnt++;
	pcnt.cnt = GetBCD32(PrtCnt);
}

void  	SetPrinterTimeOut(void)
{
	Com2Tick = 2;  
}



/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  Thermal Printer 테스트를 위한 Routine...
  Arg :
	void
  Return :
	void
----------------------------------------------------------------------------------*/ 
void SendTime(void)
{
    u8 slash,comma,space;
    u8 Creturn,LineFeed;
    u8 Cnt;
    slash=0x2d;
    comma = 0x3a;
    space = 0x20;
    Creturn = 0x0d;
    LineFeed = 0x0a;
//	SendPrinter(sizeof(PreTimeMsg),&PreTimeMsg[0]);
	RTC_TIME time;
	GetRTC(&time);
    
    for(Cnt=0;Cnt<20;Cnt++) 
    {
		SendPrinter(4,&time.Year[0]);
		SendPrinter(1,&slash);
	
		SendPrinter(2,&time.Month[0]);
		SendPrinter(1,&slash);
	//	SendPrinter(sizeof(MsgMonth),&MsgMonth[0]);
		
		SendPrinter(2,&time.Day[0]);
		SendPrinter(1,&space);
	//	SendPrinter(sizeof(MsgDay),&MsgDay[0]);
	    
		SendPrinter(4,&time.AmPm[0]);
		SendPrinter(1,&space);
	
		SendPrinter(2,&time.Hour[0]);
		SendPrinter(1,&comma);
	//	SendPrinter(sizeof(MsgHour),&MsgHour[0]);
	
		SendPrinter(2,&time.Minute[0]);
		SendPrinter(1,&comma);
	//	SendPrinter(sizeof(MsgMinute),&MsgMinute[0]);
		
		SendPrinter(2,&time.Second[0]);
	//	SendPrinter(sizeof(MsgSecond),&MsgSecond[0]);
	
		SendPrinter(1,&Creturn);			// +jwshin 110106
		SendPrinter(1,&LineFeed);
	}
	SendPrinter(sizeof(CutCmd),&CutCmd[0]);			// Cutting...
	
}

void SendPrtDump(void)
{
 //   SendPrinter(sizeof(MyDump5b),&MyDump5b[0]);
 	SendPrinter(sizeof(HeadMsg),&HeadMsg[0]);
 	SendPrinter(sizeof(NumberMsg),&NumberMsg[0]);
 	SendPrinter(sizeof(EndMsg),&EndMsg[0]);
    SendPrinter(sizeof(CutCmd),&CutCmd[0]);			// Cutting...
}

void PrintDumpTest1(void)
{
	SendPrinter(sizeof(Dump),&Dump[0]);
 //   SendPrinter(sizeof(CutCmd),&CutCmd[0]);			// Cutting...
 
}

void WriteDumpFlash(void)
{
	WriteDumpData(&Dump[0],sizeof(Dump));
	
}
