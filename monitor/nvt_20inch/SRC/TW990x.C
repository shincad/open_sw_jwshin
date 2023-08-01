#include "tw990x.h"
#include "Scaler.H"
#include "MCU.H"
#include "UserAdj.H"
#include "MyDef.H"
#include "F63xREG.H"
#include "IIC.H"
#include "stdio.h"
#include "PANEL.H"
#include "RAM.H"
#include "sRGB.H"
#include "OSD.H"
#include "rom_map.h"
#include "Z86229.h"


//#define TW990x_Addr		0x88

//****************************************************************//
//��������
//****************************************************************//


code unsigned char TW990x_ResetTable[] =
{	      				//NTSC
//******************************************
//������ �ʱ�ȭ �Ǿ� �ϴµ� ��Ȥ �ȵǼ� ������ �ʱ�ȭ.

	0x04,				0x00,
	0x05,				0x00,
	0x06,				0x40,	
	0x07,				0x02,
	0x08,				0x15,
	0x09,				0xf0,
	0x0a,				0x80,
	0x0b,				0xd0,
	0x0c,				0x8c,
	0x0d,				0x00,
	0x0e,				0x11,
	0x0f,				0x00,
	0x10,				0x00,
	0x11,				0x60,
	0x12,				0x51,
	0x13,				0x7f,
	0x14,				0x5a,
	0x15,				0x00,
	//0x16,				0xc3,
	0x16,				0xc0,//2003-11-21
//	0x17,				0x80,
	0x18,				0x00,
	0x19,				0x58,
	0x1a,				0x80,
	0x1e,				0x00,
	0x1f,				0x00,
	//0x20,				0xa0,
	0x20,				0x57,	//2004-05-19	clamp ���������Ͽ����� Ư�����Ͽ��� ��Ģ�������ٹ��̰� ��Ÿ��.
	0x21,				0x22,
	0x22,				0xf0,
	0x23,				0xfe,
	//#ifdef WXGA_Panel
//	0x23,				0xa0,	//2003-11-18
	//#endif
	//0x24,				0x3c,
	//0x24,				0x33,	//2003-11-21
	//0x24,				0x47,	//2004-05-19
	#ifdef USE_NTSCtuner
	0x24,				0x45,	
	#else
	0x24,				0x4e,	//2004-07-01
	#endif
	0x25,				0x38,
	//0x25,				0x30,	//2003-11-05
	0x27,				0x20,
	//0x27,				0x08,	//2003-11-21
	0x28,				0x00,
	0x29,				0x15,
	0x2a,				0xa0,
	0x2b,				0x44,
	0x2c,				0x37,
	0x2d,				0x00,
	0x30,				0x00,
	0x31,				0x10,
	0x32,				0xa0,
	0x33,				0x22,
	0x34,				0x11,
	0x35,				0x35,
	0x36,				0x72,	
	0x39,				0x00,	
	//0x3B,				0x05,	//2003-09-02
	//0x3B,				0x14,	//2003-11-05
	//0x3B,				0x25,	//2003-11-05
	0x3B,				0x05,	//2004-05-19
	0x3C,				0xE3,	
	0x3D,				0x20,	
	0x3E,				0xAF,	
	0x3F,				0x00,	
	0x40,				0x00,	
	0x41,				0x40,	
	0x42,				0x40,	
	0x43,				0xC0,	
	0x44,				0x00,	
    	0x00	// �������� ��Ÿ���� ��������.
};

/*

code unsigned char TW990x_ResetTable[] =
{	      				//NTSC
		
//******************************************
//������ �ʱ�ȭ �Ǿ� �ϴµ� ��Ȥ �ȵǼ� ������ �ʱ�ȭ.

	0x04,				0x00,
	0x05,				0x00,
	0x06,				0x40,	
	0x07,				0x02,
	0x08,				0x15,
	0x09,				0xf0,
	0x0a,				0x80,
	0x0b,				0xd0,
	0x0c,				0x8c,
	0x0d,				0x00,
	0x0e,				0x11,
	0x0f,				0x00,
	0x10,				0x00,
	0x11,				0x60,
	0x12,				0x51,
	0x13,				0x7f,
	0x14,				0x5a,
	0x15,				0x00,
	0x16,				0xc3,

	0x18,				0x00,
	0x19,				0x58,
	0x1a,				0x80,

	0x1e,				0x00,
	0x1f,				0x00,
	0x20,				0xa0,
	0x21,				0x22,
	0x22,				0xf0,

	0x24,				0x3c,
	0x25,				0x38,
	
	0x27,				0x20,
	0x28,				0x00,
	0x29,				0x15,
	0x2a,				0xa0,
	0x2b,				0x44,
	0x2c,				0x37,
	0x2d,				0x00,
	
	0x30,				0x00,
	0x31,				0x10,
	0x32,				0xa0,
	0x33,				0x22,
	0x34,				0x11,
	0x35,				0x35,
	0x36,				0x72,	
	0x39,				0x00,	

	0x3B,				0x14,	
	0x3C,				0xE3,	
	0x3D,				0x20,	
	0x3E,				0xAF,	
	0x3F,				0x00,	
	0x3F,				0x00,	
	0x40,				0x00,	
	0x41,				0x40,	
	0x42,				0x40,	
	0x43,				0xC0,	
	0x44,				0x00,	
    	0x00	// �������� ��Ÿ���� ��������.
};
*/
/*
code unsigned char TW9908B_Table_Init[] =
{	      				//NTSC

//*********************************************
//���� �ʿ��� ���� 

	TW99_ACNTL,			0x40,		//
	TW99_INFORM,		0x40,
	TW99_OPFORM,		0x92,		//656 format
//	TW99_OPFORM,		0x52,		//601 format
	TW99_CROP_HI,		0x03,
	TW99_VDELAY_LO,		0x11,		//youngdo 2003.5.19
//	TW99_VACTIVE_LO,	0x10,		//youngdo 2003.5.19ntsc
	TW99_VACTIVE_LO,	0xf5,		//youngdo 2003.5.19  PAL
	TW99_HDELAY_LO,		0x7a,		//youngdo 2003.5.19 0x90,
	TW99_HACTIVE_LO,	0x00,
	TW99_CNTRL1,		0x9c,		//
	TW99_SDT,		0x07,
	TW99_SDTR,		0x7f,
	TW99_CLMPG,		0x50,
	TW99_MISSCNT,		0x4c,		//remove vcr jitter
	TW99_VCNTL,		0x02,		//aflf on.
	TW99_MISC2,		0xa9,
	TW99_MISC3,		0xE2,	// no video blue 0xe6,	
//  RGB, FB  control	
	TW9908B_SBRIGHT,		0x20,
	TW9908B_SCONTRAST,		0x70,
	TW9908B_RGBCNTL,		0x03,	//RGB on,FB disablee
	TW9908B_SCBGAIN,		0x80,	//sub is RGB
	TW9908B_SCRGAIN,		0x40,	//DAC enable
	TW99_PEAKWT,		0xe0,
	TW99_VSHARP,		0x84,
//	TW99_VSHARP,		0x80,		// smpark 20030730
	

	TW99_ACNTL,		0xc0,	
    	0x00	// �������� ��Ÿ���� ��������.
};
*/
code unsigned char TW9908C_Table_Init[] =
{	      				//NTSC

//*********************************************
//���� �ʿ��� ���� 
	TW99_INFORM,		0x40,
	TW99_OPFORM,		0x82,  //656 format
//	TW99_OPFORM,		0x52,  //601 format
	TW99_ACNTL,			0x40,		//
	TW99_SDT,			0x0f,	
	TW99_CROP_HI,		0x13,
//	TW99_VDELAY_LO,		0x02,		//youngdo 2003.5.19
	TW99_VDELAY_LO,		0x13,		//Kort 
	TW99_VACTIVE_LO,	0x10,		//youngdo 2003.5.19ntsc
//	TW99_HDELAY_LO,		0x38,		//lee 38<---36 youngdo 2003.5.19 0x90,
	TW99_HDELAY_LO,		0x94,		//lee 38<---36 youngdo 2003.5.19 0x90,
	TW99_HACTIVE_LO,	0x38,		//lee 38<---28  2004.10.27 0x90,
	TW99_SDTR,			0x7f,
	TW99_CLMPG,			0x50,
	TW99_MISSCNT,		0x4c,		//remove vcr jitter
	TW99_VCNTL,			0x02,		//aflf on.

//	TW99_VSHARP,		0x80,		// smpark 20030730
		
	TW9908C_LOOP,			0xa9,
	TW9908C_MISC2,			0xE2,		// no video blue 0xe6,	
//  RGB, FB  control	
	TW9908C_SBRIGHT,		0x20,	
	TW9908C_SCONTRAST,		0x70,
	TW9908C_SCBGAIN,		0xC0,	//sub is RGB,DAC enable
	TW99_PEAKWT,			0xe0,	
	TW99_VSHARP,		0xf7,		//  2004.3.22 youngdo
	TW99_CNTRL1,		0x9c,		//	
	TW99_SHARP	,		0x73,		//cti enable  2004.3.22 youngdo
	TW99_ACNTL,			0xc0,	
	
	 	0x00	// �������� ��Ÿ���� ��������.
    	};

	


#define TW990xWrite(_y_,_z_) 	WriteIIC(TW990x_Addr,_y_,_z_)
#define TW990xRead(_z_) 		ReadIIC(TW990x_Addr,_z_)

#define TW990x_SetBrightness(_z_) 		WriteIIC(TW990x_Addr,TW99_BRIGHT,_z_)
#define TW990x_SetContrast(_z_) 			WriteIIC(TW990x_Addr,TW99_CONTRAST,_z_)
#define TW990x_SetTint(_z_) 				WriteIIC(TW990x_Addr,TW99_HUE,_z_)






//sharpness  range is 0-7
void TW990x_SetSharpness(unsigned char value)
{
	unsigned char setvalue;
	setvalue=ReadIIC(TW990x_Addr,TW99_SHARP)&0xf8;
	setvalue+=value;
	TW990xWrite(TW99_SHARP,setvalue);
}


void TW990x_Setaturation(unsigned char value)
{
	unsigned short	bigvalue;
	bigvalue=(unsigned short)value*0x7f;	
	bigvalue/=127;
	TW990xWrite(TW99_SAT_U,(unsigned char)bigvalue);
	bigvalue=(unsigned short)value*0x5a;
	bigvalue/=127;
	TW990xWrite(TW99_SAT_V,(unsigned char)bigvalue);
}



// ���� 0�̸� wirte����ȴ�.
void TW990x_RegInit(unsigned char *B_Addr_Table)
{
	while(*B_Addr_Table){
//		printf("TW990x_RegInit B_Addr_Table=0x%x,B_Addr_Table++=0x%x\r\n",(unsigned short)*B_Addr_Table,(unsigned short)*(B_Addr_Table+1));
		TW990xWrite(*B_Addr_Table++,*B_Addr_Table++);
//		printf("After\r\n");
		Sleep(12);
		CLRWDT=0x55;
	}
}


void AVDecoderSleep(void)
{
	TW990xWrite(TW99_ACNTL,0x0f);
//	printf("TW9908 Sleep\n");
}


void AVDecoderWakeup(void)
{
	TW990xWrite(TW99_ACNTL,0xC0);
//	printf("TW9908 Wake Up\n");
}



void AVDecoder_SelectInputPort(void)
{

	unsigned char value;//,tw_id;
	value = ReadIIC(TW990x_Addr,TW99_INFORM)&0x42;  /// rev C is added YSEL2
	
//IC���� IC Type�� Ȯ����
//	tw_id=TW990xRead(TW99_ID);

	switch(FuncBuf[pVIDEOSOURCE]){
		case cANALOG:
		case cDVI:
		case cYPbPr:
			value|=0x00;		// TV_INPUT select(VIN3)	
			break;
		case cSVIDEO:
			value|=0x18; 		// S-Video select +jwshin 050726
			break;
		case cCOMPOSIT:
			value|=0x04;		// VIDEO_INPUT select(VIN2)	// 661->665�� ���� by LKE Chroma Input�� �׻� �����ϱ� ����.
			break;
		case cTV:
			value|=0x00;		// TV_INPUT select(VIN3)	
			break;
	}
	
	 TW990xWrite(TW99_INFORM,value);

}
	
void SetDecoder_Brightness(void)
{	
	unsigned char value;
	value = (FuncBuf[pBRIGHTNESS] * 2+28-128);	
	TW990x_SetBrightness( value);	
}

void SetDecoder_Contrast(void)
{
	unsigned char value;
	value = (FuncBuf[pCONTRAST] * 2);
	TW990x_SetContrast(value);	
}


void SetDecoder_Saturation(void)
{
	unsigned char  value;
	value=(FuncBuf[pSATURATION] * 2+28);		
	TW990x_Setaturation(value);		
}

void SetDecoder_Tint(void)
{
	unsigned char value;
	value = 100-FuncBuf[pTINT] * 2;
	TW990x_SetTint(value);
}


void SetDecoder_Sharpness(void)
{
	TW990x_SetSharpness(FuncBuf[pSHARPNESS]);
}

/*
void	SetBlueScrren(unsigned char MenuVal)
{

	if(MenuVal) TW990xWrite(TW99_MISC3,0xE6);
	else TW990xWrite(TW99_MISC3,0xE2);



}

*/

void Decoder_Init(void)
{
	
//	unsigned char tw_id;
//	tw_id=TW990xRead(TW99_ID);
	 
	VideoStandard=0xff;

	if(FuncBuf[pVIDEOSOURCE] < cSVIDEO) return;
	//printf("decoder init start\r\n");
	AVDecoderWakeup();
	//printf("AVDecoderWakeup\r\n");
//	ScalerPowerUp();
	if(VPXinit == 0){
		TW990x_RegInit(TW990x_ResetTable); //Parameters loading  
//				switch(tw_id) {
//			case ID_TW9908B	:   //9908B�� 9903B�� ID� ����� �
//					TW990x_RegInit(TW9908B_Table_Init); //Parameters loading  
//					Sleep(50);
//					TW990x_RegInit(TW9908B_Table_Init); //Parameters loading  
//					Sleep(50);
//					TW990x_RegInit(TW9908B_Table_Init); //Parameters loading  
//					Sleep(50);
//					TW990x_RegInit(TW9908B_Table_Init); //Parameters loading  
//					Sleep(50);
//					printf("TW9908B Init\r\n");
//					break;		
//			case ID_TW9908C	:
					TW990x_RegInit(TW9908C_Table_Init); //Parameters loading  
					Sleep(50);
/*					TW990x_RegInit(TW9908C_Table_Init); //Parameters loading  
					Sleep(50);
					TW990x_RegInit(TW9908C_Table_Init); //Parameters loading  
					Sleep(50);
					TW990x_RegInit(TW9908C_Table_Init); //Parameters loading  
					Sleep(50); */

					FB_Enable(); //test
//					printf("TW9908C Init\r\n");
//					break;	
//			}

		/*
		TW990x_RegInit(TW990x_Table_Init); //Parameters loading  
		Sleep(50);
		TW990x_RegInit(TW990x_Table_Init); //Parameters loading  
		Sleep(50);
		TW990x_RegInit(TW990x_Table_Init); //Parameters loading  
		Sleep(50);
		*/
	}
	AVDecoder_SelectInputPort();
//	printf("SelectInputPort\r\n");

//	if(ColorSystem&NTSC) {flag3 |= BIT_6;}
//	if(ColorSystem&PAL)	{
//		if(TunerBrand==SAMSUNG_TCPN9082DA27C) {flag3 |= BIT_6;}
//		else {flag3 &= ~BIT_6;}
//	}
//	if(ColorSystem&SECAM)	{
//		if(TunerBrand==SAMSUNG_TCPN9082DA27C) {flag3 |= BIT_6;}
//		else	{flag3 &= ~BIT_6;}
//	}
//	printf("color setting\r\n");

	TVColorLoad();
	SetDecoder_Brightness();
	SetDecoder_Contrast();
	SetDecoder_Saturation();
	SetDecoder_Sharpness();
	SetDecoder_Tint();
	//SetBlueScrren(xEEPROMBuffer[BscrFlag_buf]);

//	SetScalerAV();

	VPXinit = 1;
	VideoFlagTW = 0;
	SyncFlag = 0;
	WriteIIC(TW990x_Addr,TW99_OPFORM, 0x92);      //Output Enable  mode
	Z86229_Init();	// Jason Choi
}




void FB_Enable()	
{
	TW990xWrite(TW9908C_RGBCNTL,0x01);
}


void	FB_Disable()
{

			TW990xWrite(TW9908C_RGBCNTL,0x03);

}

/*
void ForceBlueScreen()
{
	TW990xWrite(TW99_MISC3,0xEA);
}

void ClearBlueScreen()
{
	//SetBlueScrren(xEEPROMBuffer[BscrFlag_buf]);
}
*/


// Sync��check�Ͽ� VideoFlag�� �����Ѵ�.
// Sync Ok --> SyncFlag,VideoFlag=1
// No Sync --> SyncFlag,VideoFlag=0 
// note:
// ntsc�� ��� : flag3 |= BIT_6,
// pal/secam�� ��� : flag3 &= ~BIT_6,
void CheckVideoSignal(void)
{
	unsigned short value;//, value1;

	// Į�� �ý��� ���� ���¸� üũ�Ѵ�. 
		//value = ReadVPX_FP(VPX_SDT)&0x007;
//		value = ReadIIC_HW(TW990x_Addr,TW99_CSTATUS)&0xef;
		value = ReadIIC(TW990x_Addr,TW99_CSTATUS)&0x81;
//		printf("TW_Cstatus=0x%x\r\n",(unsigned short)value);	
//		printf("TW_Cstatus=0x%x Val=0x%x\r\n",(unsigned short)value,(unsigned short)VideoStandard);	
		if(value != VideoStandard) {	//������ ������ Į�� �ý��۰� ���Ͽ� �ٸ��ٸ� �ٽ� �����Ѵ�.
			LCDMute();

			//--------------
//			Sleep(150);
//			value = ReadIIC_HW(TW990x_Addr,TW99_CSTATUS)&0x01;
			value =ReadIIC(TW990x_Addr,TW99_CSTATUS)&0x81;
			if(value != VideoStandard);// printf("Color Change\r\n");
			else{
//			printf("TW_Cstatus3=0x%x\r\n",(unsigned short)value);	

				LCDMuteOff();
				return;
				}
			//--------------			
//			Sleep(100);
//			value = ReadIIC_HW(TW990x_Addr,TW99_CSTATUS)&0x01;
			value =ReadIIC(TW990x_Addr,TW99_CSTATUS)&0x81;
			if(value != VideoStandard);// printf("Color Change\r\n");
			else{
//			printf("TW_Cstatus4=0x%x\r\n",(unsigned short)value);	

				LCDMuteOff();
				return;
				}
			//--------------			;
//			Sleep(100);
//			value = ReadIIC_HW(TW990x_Addr,TW99_CSTATUS)&0x01;
			value = ReadIIC(TW990x_Addr,TW99_CSTATUS)&0x81;
			if(value != VideoStandard);// printf("Color Change\r\n");
			else{
//			printf("TW_Cstatus5=0x%x\r\n",(unsigned short)value);	

				LCDMuteOff();
				return;
				}
			//--------------
			VideoFlagTW=0; 	SyncFlag=0;
			/*switch(value){
				case 0:	//NTSC M
				case 3:	//NTSC4.43
				case 4:	//PAL M
				case 6:	//PAL 60
					flag3 |= BIT_6;	break;
				case 1:	//PAL  B,D,G,H,I
				case 2:	//SECAM
				case 5:	//PAL CN
					flag3 &= ~BIT_6;	break	;							
				case 7:	//not valid
					break;
			}*/
			if((value & BIT_0) !=0) Video_60Hz = 0; // 50Hz detected...
			else Video_60Hz = 1;  // 60Hz detected...
			VideoStandard=value;
			
//			Sleep(50);
			SetScalerAV();
			BackLightOn();

			if((value & BIT_7)==0) {
				SetDisplayNormal_Video();
				TVSignalNormalFlag = 1;	

			}
			if(((value & BIT_7))&&(FuncBuf[pVIDEOSOURCE] == cTV)){
				if(TVSignalNormalFlag ==0){	
					WriteWordIIC563(0x55,0x023);
					WriteWordIIC563(0x53,0x022);
				}
				SetDisplayNormal_Video();
			}
			
//			printf("TW_Cstatus1=0x%x\r\n",(unsigned short)value);	
//			VChip_Block =0;
//			Non_VChip_Count =0;

	
		}
		else{
			value = ReadIIC(TW990x_Addr,TW99_CSTATUS);
			//------------//��ũ�� �ִٰ� ���� ��ũ�� ����� ���---------------------
			if((value & 0x80) && (VideoFlagTW == 1)){		
				LCDMute();
				VideoFlagTW=0; 	SyncFlag=0;//(0,0) -->  background color=Black, free running mode�� osd�� ���� data�� mute��Ų��.
			}

			//-----------//��ũ�� ���ٰ� ���� ��ũ�� ����� ���----------------------
			if(((value & 0x80) == 0x00) && (VideoFlagTW == 0)){	
				//printf(" B ");
				VideoFlagTW=1;	SyncFlag=1;	//delay5m(10);				
				LCDMuteOff();		
//			printf("TW_Cstatus2=0x%x\r\n",(unsigned short)value);	
			}
		}
//		ScalerAutoSync2(); // 1.22
			
}



// �� �Լ��� ���������� Sync�� ��� �� ��� �̻����ϴ� �����Ϸ��� ���ڴ��� free run�ϰ� �ϴ� �Լ�.
//�Ϻ� �����Ͼ ���Ѵ�.
/*
bit CheckTvSub(void){
		xdata unsigned char i;
		
		for (i=0;i<3;i++){
				//�����Ϸ����� ��ũ�� ����.
				if( 1  //H,V��ũ�� �ֱⰡ �´��� �˻�.					
				)
					break;
				else  
					continue;					
			}
			

	if(i>=3){	// ���� �߻�.
		//���ڴ��� ������ free run�ϵ��� ��.  
		return 1;
	}
	else{
		//�ƴ� ����.
		return 0;

	}		
}
*/
//TV Auto Setup�ÿ� ����ϱ� ���� �Լ��̴�.	//TV��ȣ�� �м��Ͽ� ������.
/*
void CheckTVSignalColor(unsigned char Count)
{		xdata unsigned char value;
		xdata unsigned char i;
		
		
		if(CheckTvSub() == 1){
			eTVSyncFlag=0;
			return;
		}

	//-----colorüũ�� ��ȣó��.(Main�� �Ǵ� ó���̴�.)-------
			
	for (i=0;i<Count;i++){
		value = ReadIIC_HW(TW990x_Addr,TW99_CSTATUS);
		if(value & 0x80 ) {	// no sync
				eTVSyncFlag=0;
			}
			else{	// Decoder h/v Locking.
				eTVSyncFlag=1;
				return;
			}
			
		}
		
}

*/
/*
//ä�κ����Ŀ� �ñ׳��� �����ϴ��� Ȯ���ϱ� ���� �Լ��̴�.	//TV��ȣ�� �м��Ͽ� ������.
void CheckTVSignal(unsigned char Count)
{		xdata unsigned char value;
		xdata unsigned char i;

	if(CheckTvSub() == 1){
		SyncFlag=0;
		VideoFlag=0;		
		return;
	}
	//-----colorüũ�� ��ȣó��.(Main�� �Ǵ� ó���̴�.)-------
		
	for (i=0;i<Count;i++){
		value = ReadIIC_HW(TW990x_Addr,TW99_CSTATUS);		
		if(value & 0x80 ) {	// no sync
				SyncFlag=0;
				VideoFlag=0;
		}
		else{	// Decoder h/v Locking.
				SyncFlag=1;
				VideoFlag=1;
			return;
		}			
	}		
}
*/
/*
// Main��ƾ���� TV�� ���� ���϶�, ����ؼ�  TV Live Signal�� �����ϱ� ���ؼ� ���Ǵ� ��ƾ�̴�.
// Vsync/Hsync����°Ͱ� ������̺� ��Ż ���� ���������� ���ο� ���ؼ� üũ�Ѵ�.
void CheckTVSignalChange()
{
	unsigned char	value;
	

	if(CheckTvSub()) {
	// �߸��� H/V Sync��ȣ�� ���ؼ� Decoder�� Lock�� �ɱ� ���ؼ� .....	
		TVSyncFlag=0;
		return;
		}
	
		//----�̺κк��� Main�� �Ǵ� �۾��� ���Ѵ�.--------
	value = ReadIIC_HW(TW990x_Addr,TW99_CSTATUS);

	//----��ũ�� ������� ���� üũ�ϴ� �κ��̴�	
	if(TVSyncFlag==1) {
		if(value & 0x80) { 
			TVSyncFlag=0; 
			return;
		}
	}

	//----��ũ�� ��Ÿ���� ���� üũ�ϴ� �κ��̴�	
	if(TVSyncFlag==0) {
		if((value & 0x80)==0) {
		//		ScalerAutoSync();	
			TVSyncFlag=1;
			}
		}	
}

*/
void	TVColorLoad(void)
{

	FuncBuf[pBRIGHTNESS] = (Word)Read24C16(ep_Video_Brightness);
 	FuncBuf[pCONTRAST] = (Word)Read24C16(ep_Video_Contrast);
	FuncBuf[pTINT] = (Word)Read24C16(ep_Video_Tint);
	FuncBuf[pSHARPNESS] =(Word)Read24C16(ep_Video_Shapness);
	FuncBuf[pSATURATION] = (Word)Read24C16(ep_Video_Saturation);

}

