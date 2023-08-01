/****************************************************************************
   +----------------------------------------------------------------------+
   | Copyright EDtech co.ltd 2002                                         |
   | EDtech co.ltd reserves the right to change products                  |
   | or specifications without notice.                                    |
   +----------------------------------------------------------------------+
   Project    : TFT LCD monitor & TV
   Version    : 
   File Name  : 
   Functions  : 
   Revision   :

   2003-01-10 2:39오후  JDHAN           Modified for Monitor-TV
****************************************************************************/

//****************************************************************//
//화일참조
//****************************************************************//
#include	"TopHeader.h"
//--------------------------------------------------
#ifdef	MCU_MTV230
//--------------------------------------------------
#include	"MTV230xfr.h"
/////////////////////////////////////////////////
//	Master Mode IIC Function Block
//
//	To write IIC Device.
//	1. write MBUF the slave address.
//	2. Set S bit to start.
//	3. After the MTV212M64i transmit this byte, a Mbufl interrupt will be triggered.
//	4. Program can write MBUF to transfer next byte or set P bit to stop.
//	
//	To read IIC Device
//	1. write MBUF the slave address
//	2. Set S bit to start.
//	3. After the MTV212M64i transmit this byte, a Mbufl interrupt will be triggered.
//	4. Set or reset the MAckO flag according to the IIC protocol
//	5. Read out MBUF the useless byte to continue the data transfer.
//	6. After the MTV212M64i receives a new byte, the Mbufl interrupt is triggered again.
//	7. Read MBUF also trigger the next receive operation, but set P bit before read can terminate the operation 
//	
//	To write 
//	START -> systemAddr -> subAddr -> Data -> STOP
//	
//
//
/////////////////////////////////////////////////
#if defined(HARDWAREI2C)
bit BufferSendComplete(void)
{
	WORD TimerI2C = 0xFFFF;	
	EX1 = 0;						//External Interrupt disable(플레그를 기다리는 동안 인터럽트를 ....)
	while(!(xINTFLGI2C&0x01)){		//MBUF가 empty? or full?
		if(--TimerI2C==0) return 1;	//Fail(timer over!)
	}
	EX1 = 1;	
	return 0;
}

bit START_I2C(BYTE sysaddr)
{
	xIICCTR = 0;
	xINTFLGI2C = 0xfe;				//MBuf관련 플레그 지우고!
	xMBUF = sysaddr;	
	xIICCTR = 0x01;					//Start신호를 때리다!
	if(BufferSendComplete()) return 1;//fail
	xINTFLGI2C = 0xfe;
	return (xIICSTUS&0x80);			//ACK를 검사해서....
}

void STOP_I2C(void)
{
	xIICCTR = 0;
	xIICCTR = 0x02;					//Stop신호를 때린다. [0x01:start,0x02:stop]
}

bit WriteData(BYTE temp)
{
	xMBUF = temp;
	if(BufferSendComplete()) return 1;//fail
	xINTFLGI2C = 0xfe;	
	return (xIICSTUS&0x80);			//ACK를 검사해서....
}


/*
Hint:
	continue문은 for,while,do 루프내에서 사용된다.
	keil compiler는 continue문에서 걸리면 제어 처음으로 돌린다.
*/


bit WriteI2C(BYTE sysaddr, BYTE subaddr, BYTE writedata)
{
	BYTE	count =0;
	while(count<I2CErrorTry){	
	++count;
	if(START_I2C(sysaddr))		continue;//Ack가 안왔다!!
	if(WriteData(subaddr))		continue;//Ack가 안왔다!!
	if(WriteData(writedata))	continue;//Ack가 안왔다!!
	STOP_I2C();
	return 0;
	}
	return 1;
}

#if	defined(VPC323x)
WORD ReadDataACK(void)
{
	WORD Recdata;
	xIICCTR|=0x00;					//next cycle is last(nak)
	Recdata =xMBUF;					//trigger
	Recdata =0;
	if(BufferSendComplete()) {return 0xffff;}//fail
	xINTFLGI2C = 0xfe;
	Recdata = xMBUF;				//Ack주고 값을 읽는다?
	return Recdata;
}
#endif

WORD ReadDataNAK(void)
{
	WORD Recdata;
	
	xIICCTR|=0x04;					//next cycle is last(nak)
	Recdata =xMBUF;					//trigger
	Recdata =0;
	if(BufferSendComplete()) return 0xffff;//fail
	xINTFLGI2C=0xfe;
	STOP_I2C();						//마지막 STOP하고 버퍼값을 읽는다(마이컴이 번잡!!)
	Recdata = xMBUF;
	return Recdata;
}

WORD ReadI2C(BYTE SystemAdr, WORD address)
{
	WORD Readdata =0;
	BYTE tempadr=0;
	tempadr = (BYTE)(address>>8);
	tempadr	= ((tempadr<<1)&0xfe)|SystemAdr;				//Read Mode( In ReadI2C )

	START_I2C(tempadr);
	WriteData(address);
	START_I2C(tempadr|0x01);								//Read MODE( |0x01)
	xIICCTR|=0x04;											//next cycle is last(nak), From chung!
	Readdata=xMBUF;											//trigger, From chung!
	Readdata=0;
	if(BufferSendComplete()) {return 0xffff;}//fail
	xINTFLGI2C=0xfe;
	STOP_I2C();												//last read & stop
	Readdata = xMBUF;
	return Readdata;
}

#else	//SOFTWARE I2C


void DelayNOP20();		// Lcall is 4byte 4cycle
void DelayNOP10();		// Lcall is 4byte 4cycle
void DelayNOP6();		// Lcall is 4byte 4cycle
void DelayNOP12();

//BYTE	bdata	I2Cdata;
//sbit  I2Cdata7 =I2Cdata^7;//MSB
//sbit  I2Cdata6 =I2Cdata^6;
//sbit  I2Cdata5 =I2Cdata^5;
//sbit  I2Cdata4 =I2Cdata^4;
//sbit  I2Cdata3 =I2Cdata^3;
//sbit  I2Cdata2 =I2Cdata^2;
//sbit  I2Cdata1 =I2Cdata^1;
//sbit  I2Cdata0 =I2Cdata^0;//LSB

bit WriteData(BYTE temp)
{

	data BYTE count;
	
	for(count=0;count<8;count++) 
	{
		SDA = ((temp&0x80)?1:0);//MSB
		DelayNOP6();
		SCL = 1;
		DelayNOP6();	
		SCL = 0;
		temp<<=1;
	}
	//DelayNOP6();
	//SDA = 1;		//Force to high!
	DelayNOP12();
	SCL = 1;
	DelayNOP6();
	if(SDA)//fail(Not ack!)
	{
		DelayNOP12();
		SCL=0;
		return 1;	//Nack
	}
	else//success
	{
		DelayNOP12();
		SCL=0;
		return 0;	//Ack
	}
}

bit START_I2C(BYTE sysaddr)
{
	DelayNOP12();

	//SCL = 1;//Critical Issue!!
	//SDA = 1;
	SDA = 1;
	SCL = 1;

	DelayNOP12();
	SDA = 0;		//START!
	DelayNOP12();
	SCL = 0;
	DelayNOP12();
	if(WriteData(sysaddr)) return 1;//fail!!
	else	return 0;				//success!!
}

void STOP_I2C(void)
{
	DelayNOP12();
	//SCL = 1;//Critical Issue!!
	//SDA = 0;
	SDA = 0;
	SCL = 1;
	DelayNOP12();
	SDA = 1;		//STOP!
	DelayNOP12();
}


WORD ReadDataACK(void)
{
	data BYTE count;
	BYTE idata IICdata;
	
	for(count=0;count<8;count++) 
	{
		IICdata<<= 1;
		SCL = 1;
		DelayNOP6();
		IICdata |= SDA;
		DelayNOP6();
		SCL = 0;
		DelayNOP6();
	}

	SDA = 0;	//ACK!!!를 준다.
	DelayNOP6();
	SCL = 1;
	DelayNOP12();
	SCL = 0;
	DelayNOP6();
	SDA = 1;
	return (IICdata);
}


WORD ReadDataNAK(void)
{
	data BYTE count;
	BYTE idata IICdata;
	
	for(count=0;count<8;count++) 
	{
		IICdata<<= 1;
		SCL = 1;
		DelayNOP6();
		IICdata |= SDA;
		DelayNOP6();
		SCL = 0;
		DelayNOP6();
	}
	SDA = 1;	//ACK!!!를 안준다.(NACK를 준다)
	DelayNOP6();
	SCL = 1;
	DelayNOP12();
	SCL = 0;
	STOP_I2C();
	return (IICdata);
}

bit WriteI2C(BYTE sysaddr, BYTE subaddr, BYTE writedata)
{
	BYTE	count =0;
	while(count<I2CErrorTry){	
		++count;
		NOP;
		if(START_I2C(sysaddr))		continue;//Ack가 안왔다!!
		if(WriteData(subaddr))		continue;//Ack가 안왔다!!
		if(WriteData(writedata))	continue;//Ack가 안왔다!!
		STOP_I2C();
		NOP;
		return 0;
	}
	return 1;
}

WORD ReadI2C(BYTE SystemAdr, WORD address)
{	//2004-06-09//2004-05-15 스텍부족으로 data영역에서 xdata영역으로 변경..(가끔 다운현상의 원인.)
	data WORD Readdata =0;
	BYTE tempadr=0;
	BYTE count =0;
	tempadr = (BYTE)(address>>8);
	tempadr	= ((tempadr<<1)&0xfe)|SystemAdr;				//Read Mode( In ReadI2C )
	
	while(count<I2CErrorTry){
		++count;
		if(START_I2C(tempadr)) 		continue;
		if(WriteData(address)) 		continue;
		if(START_I2C(tempadr|0x01)) continue;					//Read MODE( |0x01)
		//Readdata = ReadDataACK();
		//STOP_I2C();
		Readdata = ReadDataNAK();
		//STOP_I2C();	//2004-05-14 10:14오후
		return (Readdata);
	}
	NOP;
}
#endif
//--------------------------------------------------
#endif
//--------------------------------------------------