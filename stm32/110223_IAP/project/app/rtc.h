//---------------------------------------------
//
//		IQS I/O Board Firmware
//		FileName : Rtc.h
//		Version : 1.00
//
//		Date   : 2010.12.17
//		Author : Shin Jung Wook
//						 DNP System.	
//						 
//---------------------------------------------
#ifndef	_RTC_H
#define	_RTC_H
#include "stm32f10x_lib.h"


typedef struct _RTC_TIME{
//  	u32	Year;
	union	Year
	{
	  	struct cYear
		{
		  	u8 Year[4];
		};
		u32 iYear;
	};
	u16	year;
	union	Month
	{
	  	struct cMonth
		{
		  	u8 Month[2];
		};
		u16 sMonth;
	};
	u8 month;
	union	Day
	{
	  	struct cDay
		{
		  	u8 Day[2];
		};
		u16 sDay;
	};
	u8 day;
	union	Hour
	{
	  	struct cHour
		{
		  	u8 Hour[2];
		};
		u16 sHour;
	};
	u8 hour;
	
	union	Minute
	{
	  	struct cMinute
		{
		  	u8 Minute[2];
		};
		u16 sMinute;
	};
	u8 minute;
	
	union	Second
	{
	  	struct cSecond
		{
		  	u8 Second[2];
		};
		u16 sSecond;
	};
	u8 second;
	union DayOfWeek
	{
	 	struct cDayOfWeek
		{
		 	u8 DayOfWeek[2];
		};
		u16 sDayOfWeek;
	};
	u8 dayofweek;
    union AmPm
    {
        struct cAmPm
        {
            u8 AmPm[4];
        };
        u32 iAmPm;
    };
    u8 ampm;
}RTC_TIME,*P_RTC_TIME;

extern void RTCTest(void);
extern void RTCTest2(void);							// +jwshin 101220
extern void RTCConfiguration(void);
extern void RTCDisable(void);
extern void RTCInit(void);
extern void SetRTC(P_RTC_TIME ptime);
extern void GetRTC(P_RTC_TIME ptime);
extern void DbgOutRTC(P_RTC_TIME ptime);			// +jwshin 101221

#endif
