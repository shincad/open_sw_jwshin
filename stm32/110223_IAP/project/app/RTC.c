//---------------------------------------------
//
//		IQS I/O Board Firmware
//		FileName : Rtc.c
//		Version : 1.00
//
//		Date   : 2010.12.17
//		Author : Shin Jung Wook
//						 DNP System.	
//						 
//---------------------------------------------
#include "stm32f10x_bkp.h"
#include "stm32f10x_flash.h"

#include "RTC.h"
#include "dbgprint.h"
#include "serial.h"
// test purpose
#include "printer.h"
#include "util.h"


#define	REG_YEAR		BKP_DR2
#define	REG_MONTH		BKP_DR3
#define	REG_DAY			BKP_DR4
#define	REG_HOUR		BKP_DR5
#define	REG_MINUTE		BKP_DR6
#define	REG_SECOND		BKP_DR7
#define	REG_DAYOFWEEK	BKP_DR8

//u16 DAYOFWEEK_TABLE[7] ={0XCFC0,0xF9BF,0XADC8,0XF6BC,0XF1B8,0XDDB1,0XE4C5};
u16 DAYOFWEEK_TABLE[7] ={0xc0cf,0xbfb9,0xc8ad,0xbcf6,0xb8f1,0xb1dd,0xc5e4};

void RTCTest(void);
void RTCTest2(void);					// +jwshin 101220
void RTCConfiguration();
void RTCDisable();
void RTCInit(void);
u32 GetRTCTick(void);
u16 GetDR1(void);
void SetDR1(u16 dr);
//FLASH_Status 	fs;
u16 GetDayOfWeek(u8 in);

void GetRTC(P_RTC_TIME ptime);
void SetRTC(P_RTC_TIME ptime);
void CalcNewDate(P_RTC_TIME ptime,u32 sec);

void IncDay(P_RTC_TIME ptime);
void IncMonth(P_RTC_TIME ptime);
void IncYear(P_RTC_TIME ptime);
void DbgOutRTC(P_RTC_TIME ptime);
void dbg(void);

RTC_TIME Time;

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  RTC Test를 위한 Routine1
  Arg :
	void
  Return :
	void
----------------------------------------------------------------------------------*/ 
void RTCTest(void)
{
	u8 ch;
	while(1)
	{
	  	if(kbhit())
		{
			ch = getch();
			switch(ch)
			{
			case '1':
			  	GetRTC(&Time);
				DbgOutRTC(&Time);
			  	break;
			case '2':
			  	GetPrintCounter();
				PrtInt(pcnt.cnt);
			  	PrtMsg("printer counter");
			  	break;
			case '3':
			  	PrtMsg(" RTC Counter");	
			  	PrtInt(RTC_GetCounter());
			  	break;
			default:
			  	break;
			}
		}
	}
}

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  RTC Test를 위한 Routine2
  Arg :
	void
  Return :
	void
----------------------------------------------------------------------------------*/ 
void RTCTest2(void)
{
  	u8 ch;
  	Time.year = 2010;			// Test를 위한 날짜 강제 지정...
	Time.month = 12;
	Time.day = 20;
	Time.hour = 02;
	Time.minute = 59;
	Time.second =33;

	while(1)
	{
	  	if(kbhit())
		{
			ch = getch();
			switch(ch)
			{
			case '1':
		  		SetRTC(&Time);
				break;
			case '2':
			  	GetRTC(&Time);
				DbgOutRTC(&Time);
			  	break;
			case '3':
				//				RTC_SetCounter(20000000);
				//	RTC_WaitForLastTask();
			  	GetRTC(&Time);
				DbgOutRTC(&Time);
				break;
			case '4':
				//				RTC_SetCounter(40000000);
				//	RTC_WaitForLastTask();
			  	GetRTC(&Time);
				DbgOutRTC(&Time);
			  	break;
			case '5':
			  	PrtMsg(" RTC Counter");	
			  	PrtInt(RTC_GetCounter());
			  	break;
			case '6':
			  	dbg();
			  	break;
			default:
			  	break;
			}
		}
		ch = 0;
	}
}

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  지정된 값을 RTC Register에 Write
  Arg :
	P_RTC_TIME ptime
  Return :
	void
----------------------------------------------------------------------------------*/ 
void SetRTC(P_RTC_TIME ptime)
{
    PWR_BackupAccessCmd(ENABLE);
	BKP_WriteBackupRegister(REG_YEAR,(u16)ptime->year);
	BKP_WriteBackupRegister(REG_MONTH,(u16)ptime->month);
	BKP_WriteBackupRegister(REG_DAY,(u16)ptime->day);
	BKP_WriteBackupRegister(REG_HOUR,(u16)ptime->hour);
	BKP_WriteBackupRegister(REG_MINUTE,(u16)ptime->minute);
	BKP_WriteBackupRegister(REG_SECOND,(u16)ptime->second);
	BKP_WriteBackupRegister(REG_DAYOFWEEK,(u16)ptime->dayofweek);
	RTC_SetCounter(0);
	RTC_WaitForLastTask();
}

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  RTC에서 값을 읽어오는 Routine
  Arg :
	P_RTC_TIME ptime
  Return :
	void
----------------------------------------------------------------------------------*/ 
void GetRTC(P_RTC_TIME ptime)
{
    PWR_BackupAccessCmd(ENABLE);
  	ptime->year = BKP_ReadBackupRegister(REG_YEAR);
  	ptime->month = BKP_ReadBackupRegister(REG_MONTH);
  	ptime->day = BKP_ReadBackupRegister(REG_DAY);
  	ptime->hour = BKP_ReadBackupRegister(REG_HOUR);
  	ptime->minute = BKP_ReadBackupRegister(REG_MINUTE);
  	ptime->second = BKP_ReadBackupRegister(REG_SECOND);
  	ptime->dayofweek = BKP_ReadBackupRegister(REG_DAYOFWEEK);
	CalcNewDate(ptime,RTC_GetCounter());
	// set bcd
	ptime->iYear = GetBCD32(ptime->year);
	ptime->sMonth = GetBCD16(ptime->month);
	ptime->sDay = GetBCD16(ptime->day);
//	ptime->sHour = GetBCD16(ptime->hour);
	ptime->sMinute = GetBCD16(ptime->minute);
	ptime->sSecond = GetBCD16(ptime->second);
	ptime->sDayOfWeek = GetDayOfWeek(ptime->dayofweek);
// am pm selection

	u8 TempHour;				// +jwshin 110117
	
    ptime->AmPm[0]=0xbf; 
    ptime->AmPm[1]=0xc0;
    
    TempHour = ptime->hour;
    
    if(ptime->hour>12)
    {
//        ptime->AmPm[2]=0xc8; 
//        ptime->AmPm[3]=0xc4;
        ptime->ampm=1;
        ptime->hour = ptime->hour - 12;
    }
//    else
//    {
//        ptime->AmPm[2]=0xc0; 
//        ptime->AmPm[3]=0xfc;
//    }
    if(TempHour>=12)
    {
    	ptime->AmPm[2]=0xc8;
    	ptime->AmPm[3]=0xc4;
    }
    else 
    {
    	ptime->AmPm[2]=0xc0;
    	ptime->AmPm[3]=0xfc;
    }
    
	ptime->sHour = GetBCD16(ptime->hour);
    
}

u16 GetDayOfWeek(u8 in)
{
  	u8 index;
	u16 ret;
	index = in-1;
	ret = DAYOFWEEK_TABLE[index];
	return ret;
}

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  Debugging 용 Routine
  Arg :
	void
  Return :
	void
----------------------------------------------------------------------------------*/ 
void dbg(void)
{
PrtMsg("--------------- Debug ----------------------");


PrtInt(BKP_ReadBackupRegister(REG_YEAR));
PrtMsg("");

PrtInt(BKP_ReadBackupRegister(REG_MONTH));
PrtMsg("");
}

void DbgOutRTC(P_RTC_TIME ptime)
{
// debug
PrtMsg("----------- RTC Information ----------------------");

PrtMsg("DayofWeek");
PrtInt(ptime->sDayOfWeek);
PrtMsg("");

PrtMsg("second");
PrtInt(ptime->second);
PrtMsg("");

PrtMsg("minute");
PrtInt(ptime->minute);
PrtMsg("");

PrtMsg("hour");
PrtInt(ptime->hour);
PrtMsg("");

PrtMsg("day");
PrtInt(ptime->day);
PrtMsg("");

PrtMsg("month");
PrtInt(ptime->month);
PrtMsg("");

PrtMsg("year");
PrtInt(ptime->year);
PrtMsg("");
}

void CalcNewDate(P_RTC_TIME ptime,u32 sec)
{
  	u32 tmp,min,day,hour;
	
	if(sec ==0) return;

	sec = sec + ptime->second;
	tmp = sec%60;	// sec
	min = sec/60;
	ptime->second = tmp;
	
	if(min == 0) return;

	min = min + ptime->minute;
	
	tmp = min%60;
	hour = min/60;	// minute
	ptime->minute = tmp;

	if(hour == 0) return;
	
	hour = hour + ptime->hour;
	
	tmp = hour%24;
	day = hour/24;	//hour
	ptime->hour = tmp;

	while(day!=0)
	{
	  	day--;
		IncDay(ptime);
		ptime->dayofweek++;
		if(ptime->dayofweek >= 8) ptime->dayofweek = 1;
	}
}

void IncDay(P_RTC_TIME ptime)
{
  	u8 month;
	u16 year;
	month = ptime->month;
	switch(month)	// Current Month
	{
	//------------ 1,3,5,7,8,10월은 31일 까지 
	case 1:
	case 3:
	case 5:
	case 7:
	case 8:
	case 10:
	  	ptime->day++;
		if(ptime->day >= 32)// if exceed month varier
		{
  		  	ptime->day = 1;
		 	ptime->month++;
		}
		break;
	//------------ 4,6,9,11 월은 30일 까지	
	case 4:
	case 6:
	case 9:
	case 11:	// 30day month
	  	ptime->day++;
		if(ptime->day >= 31)// if exceed month varier
		{
  		  	ptime->day = 1;
		 	ptime->month++;
		}
	  	break;
	//------------ 12월은 31일까지 이나, Year의 증가분 까지 계산해야 하기 때문에...
	case 12:
	  	ptime->day++;
		if(ptime->day >= 32)// if exceed month varier
		{
  		  	ptime->day = 1;
		 	ptime->month = 1;
			ptime->year++;
		}
		break;
	//----------- 2월은 28일까지, 4년마다 29일 증가분 계산	
	case 2:
	  	ptime->day++;
		year = ptime->year;
		if((year%4) == 0)	// leap year
		{
		  	if(ptime->day >= 30)// if exceed month varier
			{
  		  		ptime->day = 1;
			 	ptime->month++;
			}
		}
		else
		{
		  	if(ptime->day >= 29)// if exceed month varier
			{
  		  		ptime->day = 1;
			 	ptime->month++;
			}
		}
	  	break;
	default:
	  	break;
	}
}

void IncMonth(P_RTC_TIME ptime);
void IncYear(P_RTC_TIME ptime);

/*****************************************************************************************************
	Function RTCInit()
1.	Called at program start
2.  Initialize data structure using BKP Backup register

******************************************************************************************************/
void RTCInit(void)
{
  	RCC_APB1PeriphClockCmd(RCC_APB1Periph_BKP | RCC_APB1Periph_PWR,ENABLE);	

	//PrtMsg("1");
    PWR_BackupAccessCmd(ENABLE);
	
	if(GetDR1()==0)//if no initialize --> init
	{
	  	RTCConfiguration();
		SetDR1(1);
	}
}

//void SetNVRAM(char offset,
u32 GetRTCTick(void)
{
  	return 	RTC_GetCounter();
}

u16 GetDR1(void)
{
    PWR_BackupAccessCmd(ENABLE);
	return BKP_ReadBackupRegister(BKP_DR1);
}

void SetDR1(u16 dr)
{
    PWR_BackupAccessCmd(ENABLE);
	BKP_WriteBackupRegister(BKP_DR1,dr);
}


void RTCConfiguration()
{
  	u16 u16_WaitForOscSource;
	
//	My Logic

//  RCC_APB1PeriphClockCmd(RCC_APB1Periph_BKP | RCC_APB1Periph_PWR,ENABLE);
// if RTC has set before --> dont touch RTC clock register
	
    RCC_LSEConfig(RCC_LSE_ON);
  
    for(u16_WaitForOscSource=0;u16_WaitForOscSource<5000;u16_WaitForOscSource++)
    {
    }
	//PrtMsg("2");

    RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);
    /* RTC Enabled */
    RCC_RTCCLKCmd(ENABLE);
    RTC_WaitForLastTask();
    /*Wait for RTC registers synchronisation */
    RTC_WaitForSynchro();
	//PrtMsg("3");
    RTC_WaitForLastTask();
    /* Setting RTC Interrupts-Seconds interrupt enabled */
    /* Enable the RTC Second */
    RTC_ITConfig(RTC_IT_SEC , ENABLE);
    /* Wait until last write operation on RTC registers has finished */
    RTC_WaitForLastTask();
	//PrtMsg("4");
	
	RTC_SetPrescaler(32767); /* RTC period = RTCCLK/RTC_PR = (32.768 KHz)/(32767+1) */
	RTC_WaitForLastTask();
	BKP_TamperPinCmd(DISABLE);
//	return BKP_ReadBackupRegister(BKP_DR1);

}

void RTCDisable()
{
  
}
