#ifndef _IIC_H_
#define  _IIC_H_

#include "mydef.h"
#if PBusProtocol
void WriteIIC_WaitV(unsigned char device,unsigned short addr,unsigned char ch);
#else
void WriteIIC_WaitV(unsigned char device,unsigned char addr,unsigned char ch);
void WriteByteWaitV(unsigned char temp);
#endif

unsigned char ReadIIC(unsigned char device,unsigned char addr);
void IIC_Start(void);
void IIC_Stop(void);
unsigned short ReadWordIIC(unsigned char device,unsigned char addr);
void WriteWordIIC(unsigned char device,unsigned char addr,unsigned short value);
void IIC_DelayHigh(void);
void IIC_DelayLow(void);
void SetISCL(void);
void WriteByte(unsigned char temp);
void IIC_ACK(void);


unsigned char ReadByte(void);
void WriteIIC(unsigned char device,unsigned char addr,unsigned char ch);
void MasterACK(void);
void MasterNACK(void);
void IIC_Release(void);
unsigned long Read3ByteIIC(unsigned char device,unsigned char addr);

#endif
