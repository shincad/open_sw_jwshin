//---------------------------------------------
//
//		IQS I/O Board Firmware
//		FileName : HostLine.c
//		Version : 1.00
//
//		Date   : 2010.12.17
//		Author : Shin Jung Wook
//						 DNP System.	
//						 
//---------------------------------------------
#include "HostLine.h"
#include "Serial.h"
#include "Util.h"
#include "printer.h"
#include "rtc.h"
#include "DbgPrint.h"			// +jwshin 101220

char 	VersionString[] = "DNPIOBOARD_V1";

char 	CurSensor;
//ar 	
u8 downmode;
u32 downsize;

u8 DataCnt;					// +jwshin 101221

short	CmdPos;
void 	HostLineIsr(char read);
void	HostLine(void);

void 	DoCommand(void);
void 	SendNAK(void);
void 	SendACK(void);
void 	Dbg(char in);
void 	PowerTest(u8 on);

void 	SetCom1TimeOut(int timeout);
void 	ReportVersion(void);
void 	ReportSensor(void);
void 	SetRTCValue(u8* in);

void SetRTCVal(u8 Data);			// +jwshin 101221
void  GetRTCVal(void);				// +jwshin 101221


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  HostLine Service Routine
  Arg :
	void
  Return :
	void
  실제 HostLine Service Routine
----------------------------------------------------------------------------------*/   	

//enum {RX_IDLE,RX_STX,RX_LI_MSB,RX_LI_LSB,RX_DATA,WAIT_ETX,RX_FRAME,RX_ENQ,RX_ERROR};
void 	HostLineIsr(char read)
{
  	SetCom1TimeOut(2);
  	switch(COM1.RxState){
	case RX_IDLE:
		if(read == STX)
		{
		  	COM1.RxState = RX_STX;
			COM1.RxSize = 0;
		}
		break;
	case RX_STX:	// get Li MSB
		COM1.RxSize = read;
		COM1.RxSize = COM1.RxSize<<8;
		COM1.RxSize = COM1.RxSize & 0xff00;
		COM1.RxState = RX_LI_MSB;
		break;
	case RX_LI_MSB:	// Get Li LSB
		COM1.RxSize = ((COM1.RxSize & 0xff00) | read);
		COM1.RxState = RX_DATA;
	CmdPos = COM1.rxread+1;
	//SendNAK();
		break;
	case RX_DATA:	// Get Data
	// 	UART1RxBuf[COM1.rxp++] = read;
		//----- +jwshin 101220 COM1.rxread - 2 에서 - 3으로 변경
		// DataFormat : STX/MSB/LSB/DATA../ETX ex) 02/00/02/49/56/03 --> Reportversion.
		
		if((COM1.rxread - 3) == COM1.RxSize)	//Receive all		
		{
			if(read == ETX)
			{
              COM1.RxState = RX_FRAME;
              ClearCom1TimeOut();
      		}
      		else 
			{	
				COM1.RxState = RX_ERROR;
			}
		}
		break;
	default:
	break;
	}
}

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  HostLine Command Packet Tx Routine
  Arg :
	void
  Return :
	void
  IDLE 상태에서 END 까지 I/O Board에서 Host 전송 Packet을 정의...	
----------------------------------------------------------------------------------*/   	
void	HostLine(void)
{
  	char read;
    FeedDog();
  	if(COM1.rxp != COM1.rxread)
	{
	  	read = UART1RxBuf[COM1.rxread];
		HostLineIsr(read);
		COM1.rxread++;
	}
	
  	if(COM1.RxState == RX_FRAME)
	{
//		Dbg(read+0x20);		// +jwshin 101220
		DoCommand();
//	  SendACK();
		COM1.RxState = RX_IDLE;
		COM1.RxSize = 0;
		COM1.rxp = 0;
		COM1.rxread = 0;
	}
  	else if(COM1.RxState == RX_ERROR)
	{
		SendNAK();
		COM1.RxState = RX_IDLE;
		COM1.RxSize = 0;
		COM1.rxp = 0;
		COM1.rxread = 0;
	}
}

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  Windows Application 과 통신하기위한 Protocol Command Part
  STX : 0x02 , ETX : 0x03 , ACK : 0x06 , NAK : 0x15 , ENQ : 0x05 , NULL : 0x00
  Data Format
  
  1. SendPrinter : STX/MSB/LSB/'P'/Data/ETX (0x02/0x00/0x02/'P'/Data/ETX)
  2. LedFlicker  : STX/MSB/LSB/'I'/'L'/Data1/Data2/ETX (0x02/0x00/0x04/'I'/'L'/0x30/0x3f/0x03)
  3. Show Version: STX/MSB/LSB/'I'/'V'/ETX (0x02/0x00/0x02/'I'/'V'/0x03)
  4. Show Sensor : STX/MSB/LSB/'I'/'S'/ETX (0x02/0x00/0x02/'I'/'S'/0x03)
  5. RTC Write   : STX/MSB/LSB/'I'/'T'/Data1/Data2/Data3/Data4/Data5/Data6/Data7/ETX
  				   (0x02/0x00/0x0a/'I'/'T'/yearhi/yearlow/month/day/hour/minute/second/dayofweek/0x03)
  6. RTC Read    : STX/MSB/LSB/'I'/'U'/ETX (0x02/0x00/0x02/'I'/'U'/0x03)
  7. Power Line Control(5V,24V) ON
  				 : STX/MSB/LSB/'I'/'P'/'F'/0x11/ETX (0x02/0x00/0x04/'I'/'P'/'F'/0x11/0x03)
  8. Power Line Control(5V,24V) OFF
  				 : STX/MSB/LSB/'I'/'P'/'F'/0x00/ETX (0x02/0x00/0x04/'I'/'P'/'F'/0x11/0x03)
  9. Set Printer Counter 
  				 : STX/MSB/LSB/'I'/'C'/CntMSB/CntLSB/ETX (0x02/0x00/0x04/'I'/'C'/0x00/0x05/0x03)
 10. PC Status Backup 
 				 : STX/MSB/LSB/'I'/'P'/'C'/PC_CONTROL_Status/PC_OUT_TIME_MSB/PC_OUT_TIME_LSB/ETX
 				   (0x02/0x00/0x06/'I'/'P'/'C'/0x00/0x0a/0x12/0x03)	  							 
 11. SendTime    : STX/MSB/LSB/'I'/'D'/ETX (0x02/0x00/0x02/'I'/'D'/0x03) : 현재 시간을 Thermal Printer에 인쇄...
  						
  이 Protocol Data Format 정리하여 Win Application 측에 전달.
  +jwshin 101222 Written
----------------------------------------------------------------------------------*/  
void DoCommand(void)
{
  	short TxSize;
	char Cmd,SubCmd;
	u8	btmp;
	u16 stmp;
	vu32 utmp;
//	vu32* p32;      // -jwshin 101229

	Cmd = UART1RxBuf[CmdPos];
	SubCmd = UART1RxBuf[CmdPos+1];
  	if(Cmd == 'P')
	{
      
//            PrinterTest();

          
//	  	TxSize = COM1.RxSize - 2;
		TxSize = COM1.RxSize - 1;				// +jwshin 110107
		// --- 수신 Data Size에서 1만 뺀 값을 TxSize로 함. ('P'값 제거)

		SendPrinter(TxSize,&UART1RxBuf[CmdPos+1]);
//		SendHost(TxSize,&UART1RxBuf[CmdPos+1]);			// +jwshin 110113


//while(COM2.TxState != TX_IDLE);
//while(COM2.TxState != TX_IDLE);
		SendACK();
//                
	}
	else if(Cmd == 'I')
	{
	  	switch(SubCmd){
		case 'L':
		  	SetLedBits(UART1RxBuf[CmdPos+2],UART1RxBuf[CmdPos+3]);
			SendACK();
			break;
		case 'V':
		  	ReportVersion();
		  	SendACK();
		  	break;
		case 'S':
		  	ReportSensor();
		  	SendACK();
		  	break;
		case 'O' :				// +jwshin 101229
			SetPowerOn();
			SendACK();
			break;
		case 'F' :				// +jwshin 101229
			SetPowerOff2();
			SendACK();
			break;
		case 'D':
			btmp = UART1RxBuf[CmdPos+2];
			if(btmp=='1') 
			{
				SendTime();			// +jwshin 110106
				SendACK();
			}
			else if(btmp=='2') 
			{
				PrintDumpTest1();
				SendACK();
			}
			else 
			{
				SendNAK();
			}
		  	break;
        case 'M':
        	//------ WriteDump Test를 위한 Routine...
        	btmp = UART1RxBuf[CmdPos+2];
        	if(btmp=='0') 
        	{
        		WriteDumpFlash();		// +jwshin 110111
        		SendACK();
        	}
        	else if(btmp=='1') 
        	{
        	//-------- 비상발권 시 인쇄되는 Data를 Test...	
        		PrinterOut();
        		SendACK();
        	}
        	//---- 반드시 Index를 지정해 주어야만 Flash에 저장된 Data가 인쇄됨...
        	else if(btmp=='2') 
        	{
        		SaveIndex(&UART1RxBuf[CmdPos+3]);
        		SendACK();
        	}
        	else if(btmp=='3') 
        	{
				//TxSize =  COM1.RxSize - 4;
				TxSize = COM1.RxSize - 3;		// +jwshin 110111 -3으로 수정..
				if(WriteDumpData(&UART1RxBuf[CmdPos+3],TxSize)) 
				{
					SendACK();
				}
				else 
				{
					SendNAK();
				}
        	}
        	else 
        	{
        		SendNAK();
        	}
           	break;
		case 'C':
		  	utmp = UART1RxBuf[CmdPos+2];
				utmp = utmp <<8;
		  	utmp = utmp | UART1RxBuf[CmdPos+3];
		  	SetPrintCounter(utmp);
			SendACK();
			break;
		case 'T':				
		  	SetRTCValue(&UART1RxBuf[CmdPos+2]);						
						
			SendACK();
			break;
		case 'U':				//+jwshin 101221
			GetRTCVal();		
			SendACK();
			break;		
		case 'P':
		  	btmp = UART1RxBuf[CmdPos+2];
			if(btmp=='F')
			{
				// set 5V power out to off
			  	btmp = UART1RxBuf[CmdPos+3];
				if(btmp&0x01)  						// +jwshin 110104
				{
					GPIO_WriteBit(GPIOD,GPIO_Pin_13,Bit_SET);
					PeriPheralFlag = 1;
					LedStatus = LedStatus | 0x20;			// PE5 LED Control
				}
				else 
				{	
					GPIO_WriteBit(GPIOD,GPIO_Pin_13,Bit_RESET);
					PeriPheralFlag = 0;
					LedStatus = LedStatus & 0xdf;
				}
				// set 24V power out to off
			  	btmp = UART1RxBuf[CmdPos+3];
				if(btmp&0x10)
				{	
					GPIO_WriteBit(GPIOD,GPIO_Pin_12,Bit_SET);
					PeriPheralFlag = 1;
					LedStatus = LedStatus | 0x20;
				}
				else 
				{	
					GPIO_WriteBit(GPIOD,GPIO_Pin_12,Bit_RESET);
					PeriPheralFlag = 0;
					LedStatus = LedStatus & 0xdf;
				}
				SendACK();
			}
			else if(btmp == 'C')
			{
			  	btmp = UART1RxBuf[CmdPos+3];
				stmp = UART1RxBuf[CmdPos+4];
				stmp = stmp<<8;
				stmp = stmp | UART1RxBuf[CmdPos+5];
				SavePMode((u8)btmp,(u16)stmp);
				SendACK();
			}
			else SendNAK();
		  	break;
		default:
		  	break;
		}
	}
}

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  RTC Value Writing (Using Routine)
  Arg :
	void
  Return :
	void
----------------------------------------------------------------------------------*/   
void SetRTCValue(u8* in)
{
	RTC_TIME time;
	time.year = *in;
	in++;
	time.year = time.year<<8;
	time.year = time.year | *in;
	in++;

	time.month = *in;
	in++;
	time.day = *in;
	in++;
	time.hour = *in;
	in++;
	time.minute = *in;
	in++;
	time.second = *in;
	in++;
	time.dayofweek = *in;
	SetRTC(&time);
}


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  RTC Value Writing Test Routine (Easy Routine)
  Arg :
	void
  Return :
	void
----------------------------------------------------------------------------------*/   
void SetRTCVal(u8 Data)
{
	RTC_TIME time;
	
	switch(DataCnt) {
		case 0 : 
			time.year = Data;
			break;
		case 1 :
			time.year = time.year<<8;
			time.year = time.year | Data;
			break;
		case 2 :
			time.month = Data;
			break;
		case 3 :
			time.day = Data;
			break;
		case 4 :
			time.hour = Data;
			break;
		case 5 :
			time.minute = Data;
			break;
		case 6 :
			time.second = Data;
			break;
		case 7 :
			time.dayofweek = Data;
			break;
		default :
			break;
	}
	DataCnt++;	
	if(DataCnt==8) 
	{
		SetRTC(&time);			// 실제 RTC에 Data Write...
		DataCnt=0;
	}
}					
	


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  RTC Value Reading
  Arg :
	void
  Return :
	void
----------------------------------------------------------------------------------*/   
void GetRTCVal(void)
{
	RTC_TIME	time;
	GetRTC(&time);
	DbgOutRTC(&time);
}


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  PowerTest Routine
  Arg :
	u8 on
  Return :
	void
----------------------------------------------------------------------------------*/  
void PowerTest(u8 on)
{
    if(COM2.RxSize!=0)
    {
        SendHost(COM2.RxSize,&UART2RxBuf[0]);
        COM2.RxSize = 0;
        COM2.rxp = 0;
    }
/*    if(on == ON){
        SetPower(ON);
        SendACK();
    }else{
        SetPower(OFF);
        SendNAK();
    }
 */
}


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  Report Version Routine
  Arg :
	void
  Return :
	void
----------------------------------------------------------------------------------*/  
// Send Data Packet STX/DataSize/Data.../ETX
// for Example : STX/0x07/I/V/DATA1/DATA2/DATA3/DATA4/ETX

void ReportVersion(void)
{
	UART1TxBuf[0] = STX;
	UART1TxBuf[1] = 0x0F;					// Data Size
	UART1TxBuf[2] = 'I';
	UART1TxBuf[3] = 'V';
	UART1TxBuf[4] = VersionString[0];
	UART1TxBuf[5] = VersionString[1];
	UART1TxBuf[6] = VersionString[2];
	UART1TxBuf[7] = VersionString[3];
	UART1TxBuf[8] = VersionString[4];
	UART1TxBuf[9] = VersionString[5];
	UART1TxBuf[10] = VersionString[6];
	UART1TxBuf[11] = VersionString[7];
	UART1TxBuf[12] = VersionString[8];
	UART1TxBuf[13] = VersionString[9];
	UART1TxBuf[14] = VersionString[10];
	UART1TxBuf[15] = VersionString[11];
	UART1TxBuf[16] = VersionString[12];
	UART1TxBuf[17] = ETX;
	SendHost(18,&UART1TxBuf[0]); 
}

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  Report Sensor Routine
  Arg :
	void
  Return :
	void
----------------------------------------------------------------------------------*/  

void ReportSensor(void)
{
	UART1TxBuf[0] = STX;
	UART1TxBuf[1] = 0x05;
	UART1TxBuf[2] = 'I';
	UART1TxBuf[3] = 'S';
	UART1TxBuf[4] = Sensor;						
	UART1TxBuf[5] = PrinterSensor;
	UART1TxBuf[6] = PowerOffEvent;
	UART1TxBuf[7] = ETX;
	SendHost(8,&UART1TxBuf[0]);
}

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  Send No Acknowledge
  Arg :
	void
  Return :
	void
----------------------------------------------------------------------------------*/  
void SendNAK(void)
{
 	u8 tmp = NAK;
// 	u8 tmp = 'A';
	SendHost(1,&tmp);
}

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  Send Acknowledge
  Arg :
	void
  Return :
	void
----------------------------------------------------------------------------------*/  

void SendACK(void)
{
 	u8 tmp = ACK;
// 	u8 tmp = 'a';
	SendHost(1,&tmp);
}


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  Debugging을 위한 Routine.
  Arg :
	void
  Return :
	void
----------------------------------------------------------------------------------*/  
void 	Dbg(char in)
{
 	u8 tmp = in; // + 0x30;
	SendHost(1,&tmp);
}

