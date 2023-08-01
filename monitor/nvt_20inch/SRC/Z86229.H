/****************************************************************
Filename  	: Z86229.h

Function	:  Closed Caption & V-chip

*****************************************************************/
#ifndef _Z86229_H
#define _Z86229_H
//--------------------------------------------------------------//
#define     Z86229_SLAVE         	0x28


void Z86229_Init(void);
void SetCaptionTextDispMode(unsigned char ucMode);
void Write_Z86229_1Byte(unsigned char device, unsigned char ucCommand);
void Check_VChip(void);
unsigned char Read_Z86229_1Byte(unsigned char device);
unsigned char Read_Z86229_2Byte(unsigned char device,unsigned char *pData);
unsigned char Read_Z86229_3Byte(unsigned char device,unsigned char *pData1,unsigned char *pData2);
unsigned char CheckSum_Z86229(unsigned char data1,unsigned char data2);
unsigned char Decision_VChip(unsigned char data1,unsigned char data2);
unsigned char Acquisition_VChipData(unsigned char data1,unsigned char data2);
void Write_Z86229_2Byte(unsigned char device, unsigned char ucCommand, unsigned char wrData);
void	GetRating(void);

//--------------------------------------------------------------//
#endif	/*_Z86229_H*/
