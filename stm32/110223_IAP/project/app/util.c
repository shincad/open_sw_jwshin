//---------------------------------------------
//
//		IQS I/O Board Firmware
//		FileName : Util.c
//		Version : 1.00
//
//		Date   : 2010.12.17
//		Author : Shin Jung Wook
//						 DNP System.	
//						 
//---------------------------------------------
#include "Util.h"
#include "Serial.h"
#include "stm32f10x_lib.h"
#include "stm32f10x_pwr.h"
#include "printer.h"
#include "DbgPrint.h"

#define    PC_POWER_TIME_OUT   100      // 1sec

#define 	REG_PC_CONTROL           	BKP_DR25
#define 	REG_PC_OUT_TIME_LSB        	BKP_DR26
#define 	REG_PC_OUT_TIME_MSB        	BKP_DR27

#define		PC_CONTROL_NORMAL	0
#define		PC_CONTROL_OFF		1
#define		PC_CONTROL_RESET	2

u8	bPcControlState;
u16	sPcControlTimeOut;
u8	Com2Tick;
void SavePMode(u8 mode,u16 time);
void RestoreMode(void);
u8 PowerOffOneTime;				// +jwshin 110106

////////////////////////////////////////
void 	TickIsr(void);
void 	SetLedBits(char Freq,char NewBits);
void 	SetLedToggle(void);
void	GetSensor(void);
void 	FeedDog(void);

u8 HexOut[8];
void u32ToHex(u32 in);
u8 GetHex(u8 in);
u16 PowerTick;
//char	TickCnt;
volatile unsigned int DelayTick,SystemTick,Com1Tick;

void    delay(int time);
/********************************************/
/* function for long jump					*/
/*********************************************/
vu32 AppAdr;
pFunction App;

vu32*	pWriter;
pFunction Writer;
//////////////////////////////////////////////
char LedCnt;
char LedFreq;
char LedStatus;
char LedToggle;
char EmerLedFlag;
void  LedIsr(void);
void    TogglePower(u8 pin);
void    ClearCom1TimeOut(void);
void    CheckPowerSwitch(void);
u32 GetBCD(u16 count);
vu8 Sensor,OldSensor;
vu8 SensorClose,OldSensorClose;			// +jwshin 110107

//void SetPower(u8 on);
u8 SetPower(u8 on);
u8	LoopMode;

void SetWriterPara(vu32 Address);
u32 stack;
u8 GetPCPowerState(void);
void CheckBisangMode(void);

u8 GetBiSang(void);
void SetPowerOn(void);

//////////////////////////////////////////////////
char PeriPheralFlag;

char PowerOnEvent;
char PowerOffEvent;
//char BiSangEvent;

u8  GetPcPower(void);


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  PC Power Switch�� ����.
----------------------------------------------------------------------------------*/   
void    CheckPowerSwitch(void)
{
    CheckBisangMode();			// �߱���ȯ����ġ ����.
    if(GetPcPower() != 0) 
    {
    	LedStatus = LedStatus | 0x10;	// +jwshin 101230 PC�� On�̸�, LED(PE4) Flickering...	
    }
 	if(GetPcPower() == 0)		// ���� PCPower�� Off �̸� Led Off;
	{							// GetPcPower() == 1 �̸� PC ON
	//	LedStatus = 0;			// GetPcPower() == 0 �̸� PC OFF
	// +jwshin 110104    --> Device Power LED���� ������ ��ġ�� �ʵ��� Masking ó���ؼ� ���.
	// PE4�� ����~!
		LedStatus = LedStatus & 0xef;			
	}

	if(PowerOnEvent)
	{
        if(GetPcPower()==0) 
        {		// PC�� Off ������ ����, PC ���� On Signal ����.
            SetPowerOn();
	        PowerOnEvent = 0;
		  	PowerOffEvent = 0;
        }
	}
	if(PowerOffEvent)
	{
// check pc power and clear power off event
	 	if(GetPcPower() == 0)
		{
		  	PowerOnEvent = 0;
		  	PowerOffEvent = 0;
			LedStatus = 0;
		}
		else 
		{				// PC�� TurnOff�� ��, �ѹ� �� Power Signal�� Triggering�� ��~!.
			if(PowerOffOneTime) 
			{
				// SetPowerOn �ϱ� ���� Serial�� PC���� �ٸ� PC�� WOL(WakeOn LAN)�� �ϵ���
				// �ݵ�� ���ø� �� ��� �Ѵ�.
				// �ణ�� Delay�� �����..
				UART1TxBuf[0] = STX;
				UART1TxBuf[1] = 0x02;
				UART1TxBuf[2] = 'W';
				UART1TxBuf[3] = 'O';
				UART1TxBuf[4] = ETX;
				SendHost(5,&UART1TxBuf[0]);
				delay(600);						// 6�ʰ� PC�� �ٸ� Host�� Wake On LAN �ϵ��� ���...
				SetPowerOn();
				PowerOffOneTime = 0;			// +jwshin 110106
			}
		}
/*		
		if(bPcControlState == PC_CONTROL_OFF)
		{
		  	if(PowerTick == 0)
			{
			  	if(GetPcPower())
				{
				  	PowerOffEvent = 0;
					SetPowerOn();
					DelayTick = 300;
					while(GetPcPower())	// wait while power off;
					{
						if(DelayTick == 0) break;
					  	FeedDog();
					}
					LedStatus = 0;			
				}
			}
			PowerOffEvent = 0;
		}
		
		else if(bPcControlState == PC_CONTROL_RESET)
		{
		  	if(PowerTick == 0)
			{
			  	if(GetPcPower())
				{
				   	PowerOffEvent = 0;
					SetPowerOn();
					while(GetPcPower());	// wait while power on;
					LedStatus = 0;			
					delay(200);
					SetPowerOn();
					while(!GetPcPower());	// wait while power off till on;
				}
			}
		}
*/		 
	}

}

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  PC VCC Investigation.
      PD10 : High --> return 0			(PC VCC ������)
      PD10 : Low  --> return 1			(PC VCC ����)
  Arg :
	void
  Return :
	void
----------------------------------------------------------------------------------*/   
u8  GetPcPower(void)
{	// PD10 Port Detection
    if(GPIO_ReadInputData(GPIOD)&0x400) return 0;
    else return 1;
}

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  Flash Write Function
  (�̻��)
  Arg :
	vu32 Addess
  Return :
	void
----------------------------------------------------------------------------------*/ 
void SetWriterPara(vu32 Address)
{
  	pWriter = (vu32*)(FlashWriterAddressLocator);
  	*pWriter = (vu32)Address;
	stack = __MRS_PSP();
  	pWriter = (vu32*)(FlashWriterStackLocator);
  	*pWriter = (vu32)stack;
}

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  Util Function���� ����ϴ� Variable Initialization
  Arg :
	vu32 Addess
  Return :
	void
----------------------------------------------------------------------------------*/ 
void UtilInit(void)
{
	SystemTick = 0;
	LedCnt = 0;
	LedFreq = 10;		// +jwshin 110119
	LedToggle = 0;
	LedStatus = 0;
	Com1Tick = 0;
	Com2Tick = 0;
    DelayTick = 0;

	EmerLedFlag = 0;			// +jwshin 110112
	PowerOffOneTime = 0;
	PeriPheralFlag = 0;			// +jwshin 110104 
	PowerOnEvent = 0;
	PowerTick = 0;
	OldSensor = GPIO_ReadInputData(GPIOC);
	Sensor = GPIO_ReadInputData(GPIOC);						// PortC Data Read
	
	OldSensorClose = GPIO_ReadInputData(GPIOC);					// +jwshin 110107
	SensorClose = GPIO_ReadInputData(GPIOC);						// PortC Data Read
	
	
	RestoreMode();		// PC�� TurnOn ���¸� RTC Data Register�� ���� �о����.
/*
    LedToggle = 1;
    LedStatus = 0xff;
    SetLedToggle();
    delay(100);
    LedStatus = 0x00;
    SetLedToggle();
*/    
//    TogglePower(0);
//    Delay(10);
//    TogglePower(1);

//	LedStatus = 0x3f;
/*    
    TogglePower(0);
    Delay(10);
    TogglePower(1);
*/    
}
/*********************************************************************************/
// Function  for Long jump --> for program download
//
/*********************************************************************************/
void JumpToApp(void)
{
	AppAdr = *(vu32*)(ApplicationAddress+4);
	// Set Application Stack Pointer
    __MSR_MSP(*(vu32*) ApplicationAddress); 
	App =(pFunction)AppAdr;
	App();
}


void JumpToWriter(void)
{
	pWriter = (vu32*)(FlashWriterAddressLocator);
	AppAdr = *pWriter;
	App = (pFunction)AppAdr;
	App();
}
/*************************************************************************************/

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  PC1 Port�� �����Ͽ� device���� ����ġ�� ���¸� �ݿ�.
  Arg :
	void
  Return :
	void
  ��� �ÿ��� �׻� On���� �Ǿ� �ִ�. (�������� �ÿ��� Off) 	
----------------------------------------------------------------------------------*/ 
void CheckDevicePower(void)
{
	if((Sensor&0x02) == 0) 
	{				// + jwshin 110106    DevicePower On
		PeriPheralFlag = 1;
		P24V_ON(1);
		P5V_ON(1); 	
		LedStatus = LedStatus | 0x20;
	}
	else									// DevicePower Off
	{
		PeriPheralFlag = 0;
		P24V_ON(0);
		P5V_ON(0); 	
		LedStatus = LedStatus & 0xdf;
	}
	
}



/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  PC4 Port�� �����Ͽ� �߱���ȯ����ġ�� ���¸� �ݿ�.(On/OffLine)
  Arg :
	void
  Return :
	void
  �߱���ȯ����ġ�� ��� �� OFF ���°� �����ǰ�, MCU���� High���޵Ǿ� ��� ���¸� �����Ѵ�.
  �߱���ȯ����ġ�� ON ���°� �Ǹ�, MCU���� Low ���޵Ǿ� LoopMode�� OffLine ���� ����.
  �� ��, PrinterOut Function Call.
----------------------------------------------------------------------------------*/ 
void CheckBisangMode(void)
{
  	if(LoopMode == NORMAL_MODE)
	{
		if((Sensor&0x10) == 0)					// PC4 �߱���ȯ����ġ�� Low�̸�, Offline ���� ����.
		{		
			delay(20);
			if((Sensor&0x10) == 0) 				// +jwshin 110118 Switch Chattering ����...
			{		
			  	LoopMode = OFFLINE_MODE;
				PrinterOut();
	//			PrintDumpTest1();			// +jwshin 110110
	//			PrtMsg("abnormal");
			}
		}
	}
	else if(LoopMode == OFFLINE_MODE)		// PC4 �߱���ȯ����ġ�� High�̸�, Online ���� ����.
	{
		if((Sensor&0x10) != 0) 
		{
			delay(20);
			if((Sensor&0x10) != 0) 
			{
			  	LoopMode = NORMAL_MODE;
			  	if(EmerLedFlag==1) 
			  	{			// +jwshin 110112  ���߱� �� Turn On�� LED�� Off...
			  		LedStatus = LedStatus & 0xfe;
			  		EmerLedFlag = 0;
			  	}
	//			PrtMsg("Normal");
			}
		}
	}
/*  
    if((GPIO_ReadInputData(GPIOC)&0x10) == 0)
    {
        while((GPIO_ReadInputData(GPIOC)&0x10) == 0);
        if(LoopMode == NORMAL_MODE)     LoopMode = OFFLINE_MODE;
        else LoopMode = NORMAL_MODE;
//        Sensor = GPIO_ReadInputData(GPIOC);
    }
*/
}


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  Com1 Timeout Set/Reset
  Arg :
	int timeout
  Return :
	void
----------------------------------------------------------------------------------*/ 
void   	SetCom1TimeOut(int timeout)
{
	Com1Tick = timeout;
}
void    ClearCom1TimeOut(void)
{
    Com1Tick = 0;  
}

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  System Tick Interrupt Routine
  	�� �Լ��� SysTickHandler() ���� ȣ��ȴ�.
  Arg :
	void
  Return :
	void
----------------------------------------------------------------------------------*/ 
void TickIsr(void)
{
	SystemTick++;

    if(DelayTick!=0)    DelayTick--;
    if(PowerTick!=0)    PowerTick--;

    LedIsr();    			// Led Flicking

	GetSensor();				// Sensor Value Read
	
	GetCloseSensor();			// CloseSensor Value Read +jwshin 110107


	if(Com1Tick!=0)			// Com1 Tick
	{
	  	Com1Tick--;
		if(Com1Tick == 0)
		{
			COM1.rxp = 0;
			COM1.rxread = 0;
			COM1.RxState = RX_ERROR;
			COM1.RxSize = 0;
		}
	}
	if(Com2Tick!=0)			// Com2 Tick
	{
	  	Com2Tick--;
		if(Com2Tick == 0)
		{
			COM2.rxp = 0;
			COM2.rxread = 0;
			COM2.RxState = RX_IDLE;
			COM2.RxSize = 0;
		}
	}
//}
}

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  LED Flicking Service Routine
  Arg :
	void
  Return :
	void
----------------------------------------------------------------------------------*/ 
void  LedIsr(void)
{
	LedCnt++;
//	LedStatus = 0x3f;			// +jwshin 101222
	if(LedCnt == LedFreq)
	{
		SetLedToggle();
        LedCnt = 0;
    }
}


/*
{
	if(PowerOnEvent)
	{
//        if(GetPcPower()==0) {
            SetPowerOn();
	        PowerOnEvent = 0;
//        }
	}
    CheckBisangMode();
//    
	if(PowerOffEvent)
	{	
		if(PowerTick == 0)
		{
			PowerOffEvent = 0;
//			if(GetPcPower()!=0) 
              SetPowerOn();
		}
	}
 //   
// }
*/

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  GetSensor
  	PC5 (PC_ON_SW) �� ���¸� �����Ѵ�.
  Arg :
	void
  Return :
	void
----------------------------------------------------------------------------------*/ 
void	GetSensor(void)
{
//  	if((Sensor&0x10)==0)
	Sensor = GPIO_ReadInputData(GPIOC);

  	if((Sensor&0x20)==0)				// PC5 : PC_ON_SW ���� ����. 0�϶� SW ON
    {
	  	if((OldSensor&0x20)!=0)
		{
			PowerOnEvent = 1;
			PowerOffEvent = 0;
		}
    }
    else{
	  	if((OldSensor&0x20)==0) 
		{
			PowerOnEvent = 0;			// +jwshin 110106
			PowerOffEvent = 1;
			PowerTick = sPcControlTimeOut;
            PowerOffOneTime = 1;                    // +jwshin 110106
		}
	}
	OldSensor = Sensor;
}

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  GetCloseSensor
  	PC0 (Close_Sen) �� ���¸� �����Ѵ�.
  Arg :
	void
  Return :
	void
	Old���� ���Ͽ� �ѹ��� ������ �ǵ���, Edge Trigger�� �ǵ��� Routine�� ����...	
----------------------------------------------------------------------------------*/ 
void	GetCloseSensor(void)
{
	SensorClose = GPIO_ReadInputData(GPIOC);

	if((SensorClose&0x01)==0)				
	{
		if((OldSensorClose&0x01)!=0)			
		{									
			//----- ���� Sensor�� �����Ǿ��� ���, �ѹ��� Serial Packet�� Host�� ����...
			UART1TxBuf[0] = STX;
			UART1TxBuf[1] = 0x02;
			UART1TxBuf[2] = 'C';
			UART1TxBuf[3] = 'S';
			UART1TxBuf[4] = ETX;
			SendHost(5,&UART1TxBuf[0]);
		}
	}
	else 
	{
		if((OldSensorClose&0x01)==0)
		{
		}
	}
	OldSensorClose = SensorClose;
}

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  SedLedToggle
  	PE0,1,2,3,4,5 LED�� Flicking �Ѵ�.
  Arg :
	void
  Return :
	void
----------------------------------------------------------------------------------*/ 
void 	SetLedToggle(void)
{
	if(LedToggle)// selected on
	{
		GPIO_SetBits(GPIOE,(LedStatus & 0x3f));	  
	}
	else	// all off
	{
		GPIO_ResetBits(GPIOE,0x3f);	  
	}
	LedToggle = 1 - LedToggle;
}


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  SetLedBits
  	LED Flickering Routine
  Arg :
	char Freq / char NewBits
  Return :
	void
----------------------------------------------------------------------------------*/ 
void 	SetLedBits(char Freq,char NewBits)
{
  	LedStatus = NewBits;
	LedFreq = Freq;
	LedCnt = 0;
	LedToggle = 1;
	SetLedToggle();
}

void SetPowerOn(void)
{
    TogglePower(1);
    delay(10);
    TogglePower(0);
    delay(10);
}



void SetPowerOff(void)
{
    TogglePower(0);
    delay(100);
    TogglePower(1);
}

//---------------------------- +jwshin 101229
void SetPowerOff2(void)
{
	TogglePower(0);
	delay(150);
	TogglePower(1);
	delay(600);			// ���� Power Off�� ���� ����� Delay...
	TogglePower(0);
}

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  SetPower
  	Power�� TurnOn �� �� ����ϴ� Routine
  	���� ������� �ʴ´�.
  Arg :
	u8 on
  Return :
	void
----------------------------------------------------------------------------------*/ 
u8 SetPower(u8 on)
{
    char tmp;

    tmp = Sensor;
    tmp = tmp & 0x02;

    DelayTick = 10;
    if(on)  //ON
    {
        if(tmp != 0) return 1;    // already on
        TogglePower(0);
        while(DelayTick!=0)
        {
            tmp = Sensor & 0x02;	// if turn on
            if(tmp !=0) return 1;
        }
        delay(2);
        TogglePower(1);
        return 0;
    }
    else   // if off command
    {
        if( tmp == 0) return 0;      // already off
        TogglePower(0);
        while(DelayTick!=0)
		{
            tmp = Sensor & 0x02;
            if(tmp ==0) return 0;
        }
        delay(2);
        TogglePower(1);
        return 1;
    }
}
/*
u8 GetPCPowerState(void)
{
  	u16 tmp = GPIO_ReadInputData(GPIOD);
	if((tmp&0x400)!=0)     return 0;
	else return 1;
}
*/

/*
void SetPower(u8 on)
{
    char tmp;

    tmp = Sensor;
    tmp = tmp & 0x02;

    DelayTick = 100;
    if(on)  //ON
    {
        if(tmp != 0) return;    // already on
        TogglePower(0);
        while(DelayTick!=0){
            tmp = Sensor & 0x02;	// if turn on
            if(tmp !=0) break;
        }
        delay(2);
        TogglePower(1);
        return;
    }else   // if off command
    {
        if( tmp == 0) return;      // already off

        TogglePower(0);
        while(DelayTick!=0)
		{
            tmp = Sensor & 0x02;
            if(tmp ==0) break;
        }
        delay(2);
        TogglePower(1);
        return;
    }
}
*/

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  TogglePower
  	PD11 : PC_ON TurnON Signal     
  Arg :
	u8 pin
  Return :
	void
----------------------------------------------------------------------------------*/ 
void    TogglePower(u8 pin)
{
    if(pin == 1) 	GPIO_WriteBit(GPIOD,GPIO_Pin_11,Bit_SET);	// PC Wakeup Default - NONE;
   	else    GPIO_WriteBit(GPIOD,GPIO_Pin_11,Bit_RESET);	// set zero
}

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  PRT/MSIC/MSR/RFID Power Turn On/Off
  	PD12 : +5V On/Off    PD13 : +24V On/Off     
  Arg :
	u8 pin
  Return :
	void
----------------------------------------------------------------------------------*/ 
void P24V_ON(u8 pin)
{
	if(pin == 1)	GPIO_WriteBit(GPIOD,GPIO_Pin_13,Bit_SET);
	else			GPIO_WriteBit(GPIOD,GPIO_Pin_13,Bit_RESET);
}

void P5V_ON(u8 pin)
{
	if(pin == 1)	GPIO_WriteBit(GPIOD,GPIO_Pin_12,Bit_SET);
	else			GPIO_WriteBit(GPIOD,GPIO_Pin_12,Bit_RESET);
}


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  delay Routine
  Arg :
	int time
  Return :
	void
----------------------------------------------------------------------------------*/ 
void    delay(int time)
{
    DelayTick = time;
    while(DelayTick !=0)
	{
	  	FeedDog();
	}
}



/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  ���� Code Conversion Routine
----------------------------------------------------------------------------------*/ 
void u32ToHex(u32 in)
{
	HexOut[7] = GetHex((u8)in);
	in = in>>4;

	HexOut[6] = GetHex((u8)in);
	in = in>>4;

	HexOut[5] = GetHex((u8)in);
	in = in>>4;

	HexOut[4] = GetHex((u8)in);
	in = in>>4;

	HexOut[3] = GetHex((u8)in);
	in = in>>4;

	HexOut[2] = GetHex((u8)in);
	in = in>>4;

	HexOut[1] = GetHex((u8)in);
	in = in>>4;

	HexOut[0] = GetHex((u8)in);
	in = in>>4;
	
}

u8 GetHex(u8 in)
{
 	u8 tmp;
	tmp = in & 0x0f;
	if(tmp <10) tmp = tmp +0x30;
	else tmp= tmp + 55;
	return tmp;
}

u32 GetBCD32(u16 count)
{
  	u32 odd,ret;
	vu8 ten,hund,thou;
	vu8 tmp;	
	
	if(count>=1000)
	{
	  	thou = count/1000;
		odd = count%1000;
	}
	else
	{
	  	thou = 0;
		odd = count;
	}

	if(odd>=100)
	{
	  	hund = odd/100;
		odd = odd%100;
	}
	else
	{
	  	hund = 0;
		odd = odd;
	}

	if(odd>=10)
	{
	  	ten = odd/10;
		odd = odd%10;
	}
	else
	{
	  	ten = 0;
	}
	/*
	PrtMsg("GetBCD ");
	PrtChar(odd);
	PrtSpace();
	PrtChar(ten);
	PrtSpace();
	PrtChar(hund);
	PrtSpace();
	PrtChar(thou);
	PrtSpace();
	*/	
	ret = GetHex(odd&0x0f);
	ret = ret<<8;

	tmp = GetHex(ten&0x0f);
	ret = ret | tmp;
	ret = ret<<8;

	tmp = GetHex(hund&0x0f);
	ret = ret | tmp;
	ret = ret<<8;
	
	tmp = GetHex(thou&0x0f);
	ret = ret | tmp;
	
	return ret;
}

u16 GetBCD16(u8 count)
{
  	u32 odd,ret;
	u8 ten;
	
	if(count>=10)
	{
	  	ten = count/10;
		odd = count%10;
	}
	else
	{
	  	ten = 0;
		odd = count;
	}
	ret = GetHex(odd&0x0f);

	ret = ret<<8;
	ret = ret | GetHex(ten);

	return ret;
}

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  SavePMode Routine
  	RTC �� Data Backup
  Arg :
	u8 mode / u16 time
  Return :
	void
----------------------------------------------------------------------------------*/ 
void SavePMode(u8 mode,u16 time)
{
	u8 lsb,msb;
    PWR_BackupAccessCmd(ENABLE);
	lsb = (u8)time;
	time = time>>8;
	msb = (u8)time;
    BKP_WriteBackupRegister(REG_PC_CONTROL,mode);
    RTC_WaitForLastTask();
    BKP_WriteBackupRegister(REG_PC_OUT_TIME_LSB,lsb);
    RTC_WaitForLastTask();
    BKP_WriteBackupRegister(REG_PC_OUT_TIME_MSB,msb);
    RTC_WaitForLastTask();

	bPcControlState = mode;
	sPcControlTimeOut = time;
}

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  RestoreMode Routine
  	RTC �� Backup�� Data�� �ҷ��鿩���� Routine
  Arg :
	void
  Return :
	void
----------------------------------------------------------------------------------*/ 
void RestoreMode(void)
{
	u8 lsb,msb;
	u16 tmp;

    PWR_BackupAccessCmd(ENABLE);
    bPcControlState = BKP_ReadBackupRegister(REG_PC_CONTROL);
    lsb = BKP_ReadBackupRegister(REG_PC_OUT_TIME_LSB);
    msb = BKP_ReadBackupRegister(REG_PC_OUT_TIME_MSB);
	tmp = msb;
	tmp = tmp<<8;
	tmp = tmp | lsb;
	sPcControlTimeOut = tmp;
}

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  FeedDog Routine
  	WatchDog Refresh Routine
  Arg :
	void
  Return :
	void
----------------------------------------------------------------------------------*/ 
void 	FeedDog(void)
{
	IWDG_ReloadCounter();
}



/*
	if(TickCnt>10)
	{
		LedCnt++;
		GetSensor();
		if(LedCnt == LedFreq)
		{
		   	SetLedToggle();
			LedCnt = 0;
		}
                TickCnt = 0;
	}
*/ 
