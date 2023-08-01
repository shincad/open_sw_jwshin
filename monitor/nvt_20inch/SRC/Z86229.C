#include "Z86229.H"
#include "MyDef.H"
#include "RAM.H"
#include "IIC.H"
#include "stdio.h"
#include "8051.H"
#include "MCU.H"
#include "Scaler.H"
#include "F63xREG.H"
#include "PANEL.H"
#include "osd.h"
#include "useradj.h"
#include "TW990x.h"

void Z86229_Init(void)
{
	VChip_Data[0]=0;
	VChip_Data[1]=0;
	Non_VChip_Count =0;
	VChip_Block =0;
	VChip_Password[0]=0x0f;VChip_Password[1]=0x0f;VChip_Password[2]=0x0f;VChip_Password[3]=0x0f;
	VChip_ChangePassword[0]=0x0f;VChip_ChangePassword[1]=0x0f;VChip_ChangePassword[2]=0x0f;VChip_ChangePassword[3]=0x0f;
	VChip_Confirm =0;
	VChip_RatingSelected =0;
	VChip_AcquisitionMPAA =0;
	VChip_AcquisitionTV =0;
	VChip_AcquisitionTVFVVSLD =0;
	ResetPasswordBuff =0;
	ResetData[0] =0;ResetData[1] =0;ResetData[2] =0;ResetData[3] =0;ResetData[4] =0;ResetData[5] =0;
	
	/*//RESET
	Write_Z86229_1Byte(Z86229_SLAVE, 0xFB);
	Write_Z86229_1Byte(Z86229_SLAVE, 0xFC);
	Write_Z86229_1Byte(Z86229_SLAVE, 0x00);
	Sleep(10);//delay10ms();*/

	
//	if(0x00 == Read24C16(0x7f0)){//caption on status
//		SetCaptionTextDispMode(Read24C16(0x7f1));//direct write to Z86229
//		FB_Enable();
//		printf("SetCaptionTextDispMode ==0\r\n");
//	}
//	else {
//		SetCaptionTextDispMode(0x00);//caption off
//		FB_Disable();
//	}
	if(0x00 < Read24C16(0x7f0)){//caption on status //Debug by Jason Choi
		SetCaptionTextDispMode(Read24C16(0x7f1));//direct write to Z86229
		FB_Enable();
//		printf("SetCaptionTextDispMode =0N\r\n");
	}
	else {
		SetCaptionTextDispMode(0x00);//caption off
//				printf("SetCaptionTextDispMode =0FF\r\n");

		FB_Disable();
	}
	
	if(0x00 == Read24C16(0x7f2)){
		Write_Z86229_2Byte(Z86229_SLAVE, 0xc1, 0xC0);//for box
//		printf("box...\r\n");
	}else{
		Write_Z86229_2Byte(Z86229_SLAVE, 0xc1, 0xC9);//for shadow
//		printf("shadow...\r\n");
	}
	//Write_Z86229_1Byte(Z86229_SLAVE, 0x24);//for closed-caption not erase
	//Sleep(100);//delay10ms();
	Write_Z86229_2Byte(Z86229_SLAVE, 0xC0, 0x02);//Horizontal signal source =>HIN

	//Write_Z86229_2Byte(Z86229_SLAVE, 0xc1, 0x92);//for box
	Write_Z86229_2Byte(Z86229_SLAVE, 0xc2, 0x29);//for Horizontal Position
}

//Caption/Text Display Mode
void SetCaptionTextDispMode(unsigned char ucMode)
{
	unsigned char ucCommand;
	switch ( ucMode )
	{
		case 0x01://CC1
			ucCommand = 0x17;
			break;
		case 0x02: //CC2:
			ucCommand = 0x15;
			break;
		case 0x03: //CC3:
			ucCommand = 0x1f;
			break;
		case 0x04: //CC4:
			ucCommand = 0x1d;
			break;
			
		case 0x05: //T1:
			ucCommand = 0x13;
			break;
		case 0x06: //T2:
			ucCommand = 0x11;
			break;
		case 0x07: //T3:
			ucCommand = 0x1b;
			break;
		case 0x08: //T4:
			ucCommand = 0x19;
			break;			
		case 0x00: // CC_TEXT_OFF:
		default:
			ucCommand = 0x16;
			break;	
	}
	Write_Z86229_1Byte(Z86229_SLAVE, ucCommand);
//	printf("SetCaptionTextDispMode=%x\r\n",(unsigned short)ucCommand);
}

void Write_Z86229_1Byte(unsigned char device, unsigned char ucCommand)
{
	unsigned char i,SS;
	for ( i = 0; i < 10; i++) {
		SS = Read_Z86229_1Byte(Z86229_SLAVE);
		if ( (SS&0x80) == 0x80 ) { // RDY
		IIC_Start();
		WriteByte(device);
		IIC_ACK();
		WriteByte(ucCommand);
		IIC_ACK();
		IIC_Stop();
//printf("write Z86229\r\n");
			break;
		}
		Sleep(10);//delay_10ms(1);
	}
	Sleep(10);//delay_10ms(1);
}

void Check_VChip(void)
{
	unsigned char SS,data1,data2;
	Write_Z86229_2Byte(Z86229_SLAVE, 0xC5, 0x61);	
	SS = Read_Z86229_1Byte(Z86229_SLAVE);
//	printf("SS=%x\r\n",(unsigned short)SS);
	if ( (SS&0x40) == 0x40 ) { // Data is available to be read out..
		if ( (SS&0x20) == 0x20 ) { // Check.. number of bytes available for output..
			SS = Read_Z86229_3Byte(Z86229_SLAVE,&data1,&data2);
			Non_VChip_Count =0;
			if ( (data1 & 0x40) == 0x40 ){
				data1 &= 0x7F; data2 &= 0x7F;
				VChip_Data[0] = data1;
				VChip_Data[1] = data2;
			}//else SetDisplayNormal();
			if ( (SS&0x40) == 0x40 ) { // Data is available to be read out..
				if ( (SS&0x20) == 0x20 ){  // Check.. number of bytes available for output..
					Read_Z86229_3Byte(Z86229_SLAVE,&data1,&data2);
					data1 &= 0x7F; data2 &= 0x7F;
					if ( CheckSum_Z86229(data1,data2) == 0x01 ){
					//	printf("data1=%x,data1=%x\r\n",(unsigned short)data1,(unsigned short)data2);
						if(Decision_VChip(VChip_Data[0],VChip_Data[1]) == 0x01){
							Acquisition_VChipData(VChip_Data[0],VChip_Data[1]);
						       ForceToBackground(0,0,0);
							
						}else{
							if(VChip_Block == 1){
								WriteIIC563(0x080,0);
								OsdInit();
							}
							SetDisplayNormal_Video();
							VChip_Block =0;
							Non_VChip_Count =0;
						}
					}
				}
			}


		} else {
			Read_Z86229_2Byte(Z86229_SLAVE,&data1);
		}
	}
	else{
			Non_VChip_Count++;
		}
	//return ucReturn ;
}

// Return Value : Serial Status(SS) Register 
unsigned char Read_Z86229_1Byte(unsigned char device)
{
unsigned char value;

	IIC_Start();
	WriteByte(device+1);
	IIC_ACK();
	value=ReadByte();
	MasterNACK();
	IIC_Stop();
	return(value);

//printf("Z86229=%x\r\n",(unsigned short)value);

}

// Return Value : Serial Status(SS) Register 
unsigned char Read_Z86229_2Byte(unsigned char device,unsigned char *pData)
{
unsigned char value;

	IIC_Start();
	WriteByte(device+1);
	IIC_ACK();
	value=ReadByte();
	MasterACK();
	*pData=ReadByte();
	MasterNACK();
	IIC_Stop();
	return(value);
}

// Return Value : Serial Status(SS) Register 
unsigned char Read_Z86229_3Byte(unsigned char device,unsigned char *pData1,unsigned char *pData2)
{
unsigned char value;

	IIC_Start();
	WriteByte(device+1);
	IIC_ACK();
	
	value=ReadByte();
	MasterACK();

	*pData1=ReadByte();
	MasterACK();

	*pData2=ReadByte();
	MasterNACK();

	IIC_Stop();

	return(value);
}

unsigned char CheckSum_Z86229(unsigned char data1,unsigned char data2)
{
	unsigned char Value = 0x00; // FALSE..
	unsigned int Data = 0x00;
	data1 &= 0x7F;
	data2 &= 0x7F;
			// Checksum Validity Check..
			Data = 0x01 + 0x05 + VChip_Data[0] + VChip_Data[1] + data1 + data2 ;
			if ( (Data & 0x7F) == 0x00 ) Value = 0x01 ;
			else Value = 0;
	return Value;	
}

// Return Value : 
//	0x00 : Block is not necessary.
//	0x01 : Block is necessary.
unsigned char Decision_VChip(unsigned char data1,unsigned char data2)
{
	if ( (data1 & 0x40) == 0x00 ) return 0x00; 
	switch ( data1 & 0x18 )
	{
		case 0x00 : // MPAA
		case 0x10 : // MPAA with EIA-608 compatibility
			switch ( data1 & 0x07){
				case 0x00://N/A(Not Applicable)
					return 0x00; // Blocking is not necessary..
					break;
				case 0x01://MPAA_G
					if((Read24C16(0x7f8)&BIT_0) ==BIT_0){//MPAA_G
						return 0x01;
					}
					break;
				case 0x02://MPAA_PG
					if((Read24C16(0x7f8)&BIT_1) ==BIT_1){//MPAA_PG
						return 0x01;
					}
					break;
				case 0x03://MPAA_PG13
					if((Read24C16(0x7f8)&BIT_2) ==BIT_2){//MPAA_PG13
						return 0x01;
					}
					break;
				case 0x04://MPAA_R
					if((Read24C16(0x7f8)&BIT_3) ==BIT_3){//MPAA_R
						return 0x01;
					}
					break;
				case 0x05://MPAA_NC17
					if((Read24C16(0x7f8)&BIT_4) ==BIT_4){//MPAA_NC17
						return 0x01;
					}
					break;
				case 0x06://MPAA_X
					if((Read24C16(0x7f8)&BIT_5) ==BIT_5){//MPAA_X
						return 0x01;
					}
					break;
				case 0x07://MPAA_NR
					if((Read24C16(0x7f8)&BIT_6) ==BIT_6){//MPAA_NR
						return 0x01;
					}
					break;
			}
			break;
	}
	switch ( data1 & 0x18 )
	{
		case 0x08 : // TV Parental Guidelines
			switch ( data2 & 0x07){
				case 0x00:
				case 0x07:
					return 0x00; // Blocking is not necessary..
					break;
				case 0x01://TV-Y
					if((Read24C16(0x7f9)&BIT_0) ==BIT_0){//TV-Y
						return 0x01;
					}
					break;
				case 0x02://TV-Y7
					if((Read24C16(0x7f9)&BIT_1) ==BIT_1){//TV-Y7
						return 0x01;
					}
					if ( (data2 & 0x20) == 0x20) { // (F)V
						if((Read24C16(0x7f9)&BIT_2) ==BIT_2){//TV-Y7-FV
							return 0x01;
						}
					}
					break;
				case 0x03://TV-G
					if((Read24C16(0x7f9)&BIT_4) ==BIT_4){//TV-G
						return 0x01;
					}
					break;
				case 0x04://TV-PG
					if((Read24C16(0x7f9)&BIT_5) ==BIT_5){//TV-PG
						return 0x01;
					}
					if ( (data2 & 0x20) == 0x20) { //TV-PG-V
						if((Read24C16(0x7fa)&BIT_0) ==BIT_0){//TV-PG-V
							return 0x01;
						}
					}
					if ( (data2 & 0x10) == 0x10) { //TV-PG-S
						if((Read24C16(0x7fa)&BIT_4) ==BIT_4){//TV-PG-S
							return 0x01;
						}
					}
					if ( (data2 & 0x08) == 0x08) { //TV-PG-L
						if((Read24C16(0x7fb)&BIT_0) ==BIT_0){//TV-PG-L
							return 0x01;
						}
					}
					if ( (data1 & 0x20) == 0x20) { //TV-PG-D
						if((Read24C16(0x7fb)&BIT_4) ==BIT_4){//TV-PG-D
							return 0x01;
						}
					}
					break;
				case 0x05://TV-14
					if((Read24C16(0x7f9)&BIT_6) ==BIT_6){//TV-14
						return 0x01;
					}
					if ( (data2 & 0x20) == 0x20) { //TV-14-V
						if((Read24C16(0x7fa)&BIT_1) ==BIT_1){//TV-14-V
							return 0x01;
						}
					}
					if ( (data2 & 0x10) == 0x10) { //TV-14-S
						if((Read24C16(0x7fa)&BIT_5) ==BIT_5){//TV-14-S
							return 0x01;
						}
					}
					if ( (data2 & 0x08) == 0x08) { //TV-14-L
						if((Read24C16(0x7fb)&BIT_1) ==BIT_1){//TV-14-L
							return 0x01;
						}
					}
					if ( (data1 & 0x20) == 0x20) { //TV-14-D
						if((Read24C16(0x7fb)&BIT_5) ==BIT_5){//TV-14-D
							return 0x01;
						}
					}
					break;
				case 0x06://TV-MA
					if((Read24C16(0x7f9)&BIT_7) ==BIT_7){//TV-MA
						return 0x01;
					}
					if ( (data2 & 0x20) == 0x20) { //TV-MA-V
						if((Read24C16(0x7fa)&BIT_2) ==BIT_2){//TV-MA-V
							return 0x01;
						}
					}
					if ( (data2 & 0x10) == 0x10) { //TV-MA-S
						if((Read24C16(0x7fa)&BIT_6) ==BIT_6){//TV-MA-S
							return 0x01;
						}
					}
					if ( (data2 & 0x08) == 0x08) { //TV-MA-L
						if((Read24C16(0x7fb)&BIT_2) ==BIT_2){//TV-MA-L
							return 0x01;
						}
					}
					break;
			}
			break;
	}
	return 0x00;
}

unsigned char Acquisition_VChipData(unsigned char data1,unsigned char data2)
{
	if ( (data1 & 0x40) == 0x00 ) return 0x00; 
	switch ( data1 & 0x18 )
	{
		case 0x00 : // MPAA
		case 0x10 : // MPAA with EIA-608 compatibility
			switch ( data1 & 0x07){
				case 0x00://N/A(Not Applicable)
					break;
				case 0x01://MPAA_G
					//if((Read24C16(0x728)&BIT_0) ==BIT_0){//MPAA_G
						VChip_AcquisitionMPAA = 0x01;
					//}
					break;
				case 0x02://MPAA_PG
					//if((Read24C16(0x728)&BIT_1) ==BIT_1){//MPAA_PG
						VChip_AcquisitionMPAA = 0x02;
					//}
					break;
				case 0x03://MPAA_PG13
					//if((Read24C16(0x728)&BIT_2) ==BIT_2){//MPAA_PG13
						VChip_AcquisitionMPAA = 0x03;
					//}
					break;
				case 0x04://MPAA_R
					//if((Read24C16(0x728)&BIT_3) ==BIT_3){//MPAA_R
						VChip_AcquisitionMPAA = 0x04;
					//}
					break;
				case 0x05://MPAA_NC17
					//if((Read24C16(0x728)&BIT_4) ==BIT_4){//MPAA_NC17
						VChip_AcquisitionMPAA = 0x05;
					//}
					break;
				case 0x06://MPAA_X
					//if((Read24C16(0x728)&BIT_5) ==BIT_5){//MPAA_X
						VChip_AcquisitionMPAA = 0x06;
					//}
					break;
				case 0x07://MPAA_NR
					//if((Read24C16(0x728)&BIT_6) ==BIT_6){//MPAA_NR
						VChip_AcquisitionMPAA = 0x07;
					//}
					break;
			}
			break;
	}
	switch ( data1 & 0x18 )
	{
		case 0x08 : // TV Parental Guidelines
			switch ( data2 & 0x07){
				case 0x00:
				case 0x07:
					return 0x00; // Blocking is not necessary..
					break;
				case 0x01://TV-Y
					//if((Read24C16(0x729)&BIT_0) ==BIT_0){//TV-Y
						VChip_AcquisitionTV = 0x01;
					//}
					break;
				case 0x02://TV-Y7
					//if((Read24C16(0x729)&BIT_1) ==BIT_1){//TV-Y7
						VChip_AcquisitionTV = 0x02;
					//}
					if ( (data2 & 0x20) == 0x20) { // (F)V
						//if((Read24C16(0x729)&BIT_2) ==BIT_2){//TV-Y7-FV
							VChip_AcquisitionTVFVVSLD |= BIT_0;
						//}
					}
					break;
				case 0x03://TV-G
					//if((Read24C16(0x729)&BIT_4) ==BIT_4){//TV-G
						VChip_AcquisitionTV = 0x03;
					//}
					break;
				case 0x04://TV-PG
					//if((Read24C16(0x729)&BIT_5) ==BIT_5){//TV-PG
						VChip_AcquisitionTV = 0x04;
					//}
					if ( (data2 & 0x20) == 0x20) { //TV-PG-V
						//if((Read24C16(0x72a)&BIT_0) ==BIT_0){//TV-PG-V
							VChip_AcquisitionTVFVVSLD |= BIT_1;
						//}
					}
					if ( (data2 & 0x10) == 0x10) { //TV-PG-S
						//if((Read24C16(0x72a)&BIT_4) ==BIT_4){//TV-PG-S
							VChip_AcquisitionTVFVVSLD |= BIT_2;
						//}
					}
					if ( (data2 & 0x08) == 0x08) { //TV-PG-L
						//if((Read24C16(0x72b)&BIT_0) ==BIT_0){//TV-PG-L
							VChip_AcquisitionTVFVVSLD |= BIT_3;
						//}
					}
					if ( (data1 & 0x20) == 0x20) { //TV-PG-D
						//if((Read24C16(0x72b)&BIT_4) ==BIT_4){//TV-PG-D
							VChip_AcquisitionTVFVVSLD |= BIT_4;
						//}
					}
					break;
				case 0x05://TV-14
					//if((Read24C16(0x729)&BIT_6) ==BIT_6){//TV-14
						VChip_AcquisitionTV = 0x05;
					//}
					if ( (data2 & 0x20) == 0x20) { //TV-14-V
						//if((Read24C16(0x72a)&BIT_1) ==BIT_1){//TV-14-V
							VChip_AcquisitionTVFVVSLD |= BIT_1;
						//}
					}
					if ( (data2 & 0x10) == 0x10) { //TV-14-S
						//if((Read24C16(0x72a)&BIT_5) ==BIT_5){//TV-14-S
							VChip_AcquisitionTVFVVSLD |= BIT_2;
						//}
					}
					if ( (data2 & 0x08) == 0x08) { //TV-14-L
						//if((Read24C16(0x72b)&BIT_1) ==BIT_1){//TV-14-L
							VChip_AcquisitionTVFVVSLD |= BIT_3;
						//}
					}
					if ( (data1 & 0x20) == 0x20) { //TV-14-D
						//if((Read24C16(0x72b)&BIT_5) ==BIT_5){//TV-14-D
							VChip_AcquisitionTVFVVSLD |= BIT_4;
						//}
					}
					break;
				case 0x06://TV-MA
					//if((Read24C16(0x729)&BIT_7) ==BIT_7){//TV-MA
						VChip_AcquisitionTV = 0x06;
					//}
					if ( (data2 & 0x20) == 0x20) { //TV-MA-V
						//if((Read24C16(0x72a)&BIT_2) ==BIT_2){//TV-MA-V
							VChip_AcquisitionTVFVVSLD |= BIT_1;
						//}
					}
					if ( (data2 & 0x10) == 0x10) { //TV-MA-S
						//if((Read24C16(0x72a)&BIT_6) ==BIT_6){//TV-MA-S
							VChip_AcquisitionTVFVVSLD |= BIT_2;
						//}
					}
					if ( (data2 & 0x08) == 0x08) { //TV-MA-L
						//if((Read24C16(0x72b)&BIT_2) ==BIT_2){//TV-MA-L
							VChip_AcquisitionTVFVVSLD |= BIT_3;
						//}
					}
					break;
			}
			break;
	}
	return 0x00;
}

void Write_Z86229_2Byte(unsigned char device, unsigned char ucCommand, unsigned char wrData)
{
	unsigned char i,SS;
	for ( i = 0; i < 10; i++) {

		SS = Read_Z86229_1Byte(Z86229_SLAVE);
		if ( (SS&0x80) == 0x80 ) { // RDY is Set ???
			IIC_Delay();
			// start bit   
			IIC_Start();
			// transmit data   
			WriteByte(device);
			IIC_ACK();
			WriteByte(ucCommand);
			IIC_ACK();
			WriteByte(wrData);
			IIC_ACK();
			// stop bit   
			IIC_Stop();
//printf("write2 Z86229\r\n");
			break;
		}
		//Sleep(10);//delay_10ms(1);
	}

}


void	GetRating(void)
{
	unsigned char temp2,temp3;
	RatingMAPP = Read24C16(0x7F8);
	RatingTV = Read24C16(0x7F9);

	temp2 =  Read24C16(0x7FA);
	temp3 =  Read24C16(0x7FB);
	Violence = 0;
	Sexual= 0;
	Lang= 0;
	Dialogue= 0;

	if(RatingTV == cTV_PG){	//3 //TV-PG
		if(temp2 & BIT_0) Violence =1;
		if(temp2 & BIT_4) Sexual= 1;
		if(temp3 & BIT_0) Lang= 1;
		if(temp3 & BIT_4)	Dialogue= 1;
	}
	if(RatingTV == cTV_14){	//RatingTV = 5	//3//TV-14
		if(temp2 & BIT_1) Violence =1;
		if(temp2 & BIT_5) Sexual= 1;
		if(temp3 & BIT_1) Lang= 1;
		if(temp3 & BIT_5) Dialogue= 1;
	}
	if(RatingTV == cTV_MA){	//		RatingTV = 6	//3//TV-MA
		if(temp2 & BIT_2) Violence =1;
		if(temp2 & BIT_6) Sexual= 1;
		if(temp3 & BIT_2) Lang= 1;
	}
	RatingTVFVVSLD= RatingTV; // make same data..
}


