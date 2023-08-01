//---------------------------------------------
//
//		IQS I/O Board Firmware
//		FileName : main.c
//		Version : 1.00
//
//		Date   : 2010.12.17
//		Author : Shin Jung Wook
//						 DNP System.	
//						 
//---------------------------------------------

#include "Serial.h"
#include "rtc.h"
#include "DbgPrint.h"
#include "printer.h"
#include "HostLine.h"
#include "util.h"
#include "CpuInit.h"
#include "wiznet.h"



//--------------------------------- Main Routine

int main()
{
	CPUInit(WORK_MODE);				// +jwshin 101217
	SerialInit();
	UtilInit();	
	RTCInit();
	PrinterInit();
	WizInit();
	
	//---------------- +jwshin 110104
	// Device Power On 
	PeriPheralFlag = 1;
	P24V_ON(1);
	P5V_ON(1);
	
	
	LoopMode = NORMAL_MODE;
	GetPrinterSensor();				
	delay(40);
	
	while(1)
	{
	  	if(LoopMode == NORMAL_MODE)
		{
		   	HostLine();
			PrinterLine();
			CheckPowerSwitch();
			CheckDevicePower();			// +jwshin 110106
		}
		else
		{
		  	FeedDog();
			AbnormalLine();
			CheckPowerSwitch();
			CheckDevicePower();			// +jwshin 110106
		}

	}
	
}

//------------------------------- Main End



