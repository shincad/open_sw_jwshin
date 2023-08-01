#include "Board.H"
#include "stdio.h"
#include "8051.H"
#include "RAM.H"
#include "IIC.H"
#include "MCU.H"
#include "ROM_MAP.H"
#include "NT686xx_MCU_REG.H"
#include "UserAdj.H"
#include "Scaler.H"
#include <intrins.h>

#if (!PBusProtocol) || FE2P_LIB==OFF
void IIC_Start(void)
{
/* start bit */
	ISDA = 0;		/* SDA=0 */
	IIC_DelayHigh();
	ISCL = 0;		/* SCL=0 */
}
void IIC_Stop(void)
{
/* stop bit */
	ISDA = 0;		/* SDA=0 */
	IIC_DelayHigh();
	ISCL = 1;
	SetISCL();		/* SCL=1 */
	ISDA = 1;		/* SDA=1 */
}

void WriteIIC(unsigned char device,unsigned char addr,unsigned char ch)
{
/* start bit */
	IIC_Start();
/* transmit data */
	WriteByte(device);
	WriteByte(addr);
	WriteByte(ch);
/* stop bit */
	IIC_Stop();
}

void WriteByte(unsigned char temp)
{
	ISDA = (temp & 0x80);
	_nop_();
	ISCL = 1;		/* SCL=1 */
	SetISCL();		/* SCL=1 */
	ISCL = 0;		/* SCL=0 */
	ISDA = (temp & 0x40);
	_nop_();
	ISCL = 1;		/* SCL=1 */
	SetISCL();		/* SCL=1 */
	ISCL = 0;		/* SCL=0 */
	ISDA = (temp & 0x20);
	_nop_();
	ISCL = 1;		/* SCL=1 */
	SetISCL();		/* SCL=1 */
	ISCL = 0;		/* SCL=0 */
	ISDA = (temp & 0x10);
	_nop_();
	ISCL = 1;		/* SCL=1 */
	SetISCL();		/* SCL=1 */
	ISCL = 0;		/* SCL=0 */
	ISDA = (temp & 0x08);
	_nop_();
	ISCL = 1;		/* SCL=1 */
	SetISCL();		/* SCL=1 */
	ISCL = 0;		/* SCL=0 */
	ISDA = (temp & 0x04);
	_nop_();
	ISCL = 1;		/* SCL=1 */
	SetISCL();		/* SCL=1 */
	ISCL = 0;		/* SCL=0 */
	ISDA = (temp & 0x02);
	_nop_();
	ISCL = 1;		/* SCL=1 */
	SetISCL();		/* SCL=1 */
	ISCL = 0;		/* SCL=0 */
	ISDA = (temp & 0x01);
	_nop_();
	ISCL = 1;		/* SCL=1 */
	SetISCL();		/* SCL=1 */
	ISCL = 0;		/* SCL=0 */
	IIC_DelayHigh();
	IIC_ACK();
}
#endif

#if PBusProtocol
void WriteIIC_WaitV(unsigned char device,unsigned short addr,unsigned char ch)
{
unsigned char xdata *Pbus;
Union Page;

	if(device!=SCALER_I2C_ADDR)
		return;

	#if NT68167
		usTimer1_1ms = 40;
		while( (ReadIIC560(0x187) &BIT_7) )
		{
			if(usTimer1_1ms == 0)
				break;
		}
		
		Page.w = addr;
		Pbus = 0x80ff;
		*Pbus = Page.b[0];	
		Pbus = 0x8000 + Page.b[1];
		*Pbus = ch;
	
	#else //#elif SCALAR_BOARD!=PCBA_Q80x67
	
		Page.w = addr;
		Pbus = 0x80ff;
		*Pbus = Page.b[0];	
		Pbus = 0x8000 + Page.b[1];
	
		usTimer1_1ms = 40;
		while(GetVsyncLevel != LOW)
		{
			if(usTimer1_1ms == 0)
				break;
		}
		*Pbus = ch;
	#endif
}

#else

void WriteIIC_WaitV(unsigned char device,unsigned char addr,unsigned char ch)
{
	IIC_Start();
	WriteByte(device);
	WriteByte(addr);
	WriteByteWaitV(ch);
	IIC_Stop();
}

void WriteByteWaitV(unsigned char temp)
{
unsigned char i,j;
	j=temp;
	for (i=0; i<8; i++){
//#if NT68167
//		if(i == 7){
//			usTimer1_1ms = 40;			/* timeout 40 */
//			while( (ReadIIC560(0x187) &BIT_7) ){
//				if(usTimer1_1ms == 0){
//					break;
//				}
//			}
//		}
//#elif SCALAR_BOARD!=PCBA_Q80x67
		if(i == 7){
			usTimer1_1ms = 40;			/* timeout 40 */
			while(GetVsyncLevel != LOW){
				if(usTimer1_1ms == 0){
					break;
				}
			}
		}

		if ((j & 0x80) ==0)
			ISDA = 0;	/* SDA=0 */
		else
			ISDA = 1;	/* SDA=1 */
		j = j << 1;
		ISCL = 1;
		SetISCL();		/* SCL=1 */
		ISCL = 0;		/* SCL=0 */
		IIC_DelayLow();
	}
	IIC_ACK();
}
#endif


#if (!PBusProtocol) || FE2P_LIB==OFF
void IIC_ACK(void)
{
	ISDA = 1;		/* SDA=1 */
	ISCL = 1;		/* SCL=1 */
	SetISCL();		/* SCL=1 */
	usTimer1_1ms = 10;			/* timeout 10ms */
	while(ISDA != 0){
		if(usTimer1_1ms == 0){
#ifdef Debug
			printf("ACK Fail\r\n");
#endif
			EA = 0;
			break;
		}
	}
	ISCL = 0;		/* SCL=0 */
}

void SetISCL(void)
{
	while(ISCL == 0){};
	_nop_();
	_nop_();
	_nop_();
}

unsigned char ReadIIC(unsigned char device,unsigned char addr)
{
unsigned char value;
/* start bit */
	IIC_Start();
/* transmit data */
	WriteByte(device);
	WriteByte(addr);
	ISCL = 1;
	SetISCL();		/* SCL=1 */
//	IIC_DelayHigh();
/* start bit */
	ISDA = 0;		/* SDA=0 */
	IIC_DelayHigh();
	ISCL = 0;		/* SCL=0 */
	IIC_DelayHigh();
/* transmit data */
	WriteByte(device+1);
	value=ReadByte();
/* no ack */
	MasterNACK();
/* stop bit */
	IIC_Stop();
	return(value);
}

unsigned char ReadByte(void)
{
unsigned char i,j;
	ISDA = 1;		/* SDA=1 */
	for(i=0; i<8; i++){
		ISCL = 1;
		j = j << 1;
		if(ISDA == 0)
			j &= 0xfe;	/* SDA=0 */
		else
			j |= 0x01;	/* SDA=1 */
		ISCL = 0;		/* SCL=0 */
		_nop_();
		_nop_();
		_nop_();
		_nop_();
		_nop_();
		_nop_();
	}
	return j;
}

void IIC_DelayHigh(void)
{
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
}


void MasterACK(void)
{
	ISDA = 0;		/* SDA=1 */
	ISCL = 1;
	SetISCL();		/* SCL=1 */
	ISCL = 0;		/* SCL=0 */
}

void MasterNACK(void)
{
	ISDA = 1;		/* SDA=1 */
	ISCL = 1;
	SetISCL();		/* SCL=1 */
	ISCL = 0;		/* SCL=0 */
}


#if (!PBusProtocol)
void IIC_DelayLow(void)
{
//	_nop_();
//	_nop_();
}
#endif

#if NT68665
void WriteWordIIC(unsigned char device,unsigned char addr,unsigned short value)
{
/* start bit */
	IIC_Start();
/* transmit data */
	WriteByte(device);
	WriteByte(addr);
	WriteByte((unsigned char)value);
	WriteByte((unsigned char)(value >> 8));
/* stop bit */
	IIC_Stop();
}

unsigned short ReadWordIIC(unsigned char device,unsigned char addr)
{
unsigned char ch;
unsigned short value;
/* start bit */
	IIC_Start();
/* transmit data */
	WriteByte(device);
	WriteByte(addr);
	ISCL = 1;
	SetISCL();		/* SCL=1 */
/* start bit */
	IIC_Start();
/* transmit data */
	WriteByte(device+1);
	ch = ReadByte();
	MasterACK();
	value = ReadByte();
	value <<= 8;
	value += ch;
/* no ack */
	MasterNACK();
/* stop bit */
	IIC_Stop();
	return(value);
}
#endif

#if 0
void IIC_Release(void)
{
#if 0 && (!FE2P_LIB)
//	IIC_Start();
//
unsigned char i;

	ISDA = 1;

	for (i=0;i<9;i++) {
		_nop_();
		ISCL = 1;		/* SCL=1 */
		SetISCL();		/* SCL=1 */
		ISCL = 0;		/* SCL=0 */
	}
	IIC_DelayHigh();

	ISCL = 1;		/* SCL=1 */
#endif
}
#endif

#if 0
unsigned long Read3ByteIIC(unsigned char device,unsigned char addr)
{
unsigned char ch;
unsigned long value;
/* start bit */
	IIC_Start();
/* transmit data */
	WriteByte(device);
	WriteByte(addr);
	ISCL = 1;
	SetISCL();		/* SCL=1 */
/* start bit */
	IIC_Start();
/* transmit data */
	WriteByte(device+1);
	ch = ReadByte();
	MasterACK();
	value = ch;
	ch = ReadByte();
	MasterACK();
	value = value + (unsigned short)ch * 256;
	ch = ReadByte();
/* no ack */
	MasterNACK();
/* stop bit */
	IIC_Stop();
	value = value + (unsigned short)ch * 65536;
	return(value);
}

#endif

#endif //#if (!PBusProtocol) || FE2P_LIB==OFF