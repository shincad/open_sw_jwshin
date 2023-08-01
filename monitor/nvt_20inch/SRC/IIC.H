#ifndef _IIC_H_
#define  _IIC_H_

#define EEPROM	0xa0
#define NACK 1
#define ACK 0
#define SOFTWAREIIC_220K 0 

unsigned char Read24C16(unsigned short addr16);
void InitEEPROM(void);
void Write24C16(unsigned short k,unsigned char ch);
//void WritePage24C16(unsigned short addr1,unsigned short addr2,unsigned char *p);

void LoadDDCData();
void SaveDDCData(bit);
void WriteWordIIC(unsigned char device,unsigned char addr,unsigned short value);
void WriteIIC(unsigned char device,unsigned char addr,unsigned char ch);
unsigned char ReadIIC(unsigned char device,unsigned char addr);
void WriteIIC563(unsigned short addr,unsigned char ch);
void CheckRegPage(unsigned short addr);
void WriteWordIIC563(unsigned short addr,unsigned short value);
unsigned char ReadIIC563(unsigned short addr);
unsigned short ReadWordIIC563(unsigned short addr);
void IIC_Start();
void IIC_Stop();
unsigned char IIC_Tx(unsigned char);
unsigned char IIC_TxV(unsigned char);
unsigned char IIC_Rx(bit);
void DDC2(void);
void CheckIIC(void);
void CheckVersion();
void CheckDevice(void);
void SetISCL(void);
void IIC_Delay(void);
void IIC_ACK(void);
void WriteByte(unsigned char temp);
unsigned char ReadByte(void);
void Fill24C16(unsigned short addr,unsigned char ch);
void MasterNACK(void);
void MasterACK(void);

#endif
