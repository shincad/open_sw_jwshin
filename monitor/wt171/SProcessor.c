
#include	"TopHeader.h"
#include	<stdio.h>
//#include "SoundTable.h"
#include "Sprocessor.h"
#include "extern.h"
#include "eepromadr.h"
#include "power.h"
#include "tools.h"
#include "EEPROMadr.h"
#include "btc_osdmenu.h"
#include	"MTV230xfr.h"

#define	Controle_Addr	0x00
#define	Demodule_Addr	0x10
#define	DSP_Addr		0x12
#define   FM_PreScale		0x2400

void putss(BYTE);
void EepromSetQue(WORD address, BYTE Recdata);
BYTE EEPROM_Read(WORD address);



extern xBYTE PreSoundMode;
extern	BYTE TW990xRead(BYTE SubAddr);

extern void ShowChannelStatus(unsigned char status);
extern void Recall(void);
extern	void 	PutData(void);

#ifdef VOLUME_PWM
	BYTE code VolumeTable[101]={		// 1.3
	0,									//0
	22 ,25 ,28 ,31 ,34 ,37 ,40 ,42 ,44,46 ,	//0
	48 ,50 ,52 ,54 ,56 ,58 ,60 ,62 ,64 ,66 ,// 1	
	68 ,70 ,72 ,74 ,76 ,78 ,80 ,82 ,84 ,86 ,//2// 2
	88 ,90 ,92 ,94 ,96 ,98 ,100,102,104,106,//3// 3
	108,110,112,114,116,118,120,122,124,126,//4// 4
	128,130,132,134,136,138,140,142,144,146,//5
	148,150,152,154,156,158,160,162,164,166,//6
	168,170,172,174,176,178,180,182,184,186,//7
	188,190,192,194,196,198,200,202,204,206,//8
	208,210,212,214,216,218,220,222,224,226,//9
};
#else 
	#if defined (Voluem_downCHINA)
	WORD code VolumeTable[101]={		//by thkim
	0x0000,0x2000,0x3000,0x4000,0x4600,0x4b00,0x4f00,0x5000,0x5040,0x5080,	// 0
	0x50c0,0x5100,0x5140,0x5180,0x51c0,0x5200,0x5240,0x5280,0x52c0,0x5300,	// 1
	0x5340,0x5380,0x53c0,0x5400,0x5440,0x5480,0x54c0,0x5500,0x5540,0x5580,	// 2
	0x55c0,0x5600,0x5640,0x5680,0x56c0,0x5700,0x5740,0x5780,0x57c0,0x5800,	// 3
	0x5840,0x5880,0x58c0,0x5900,0x5940,0x5980,0x59c0,0x5a00,0x5a30,0x5a60,	// 4
	0x5a90,0x5ac0,0x5ae0,0x5b00,0x5b30,0x5b60,0x5b90,0x5bc0,0x5be0,0x5c00,	// 5
	0x5c30,0x5c60,0x5c90,0x5cc0,0x5ce0,0x5d00,0x5d30,0x5d60,0x5d90,0x5dc0,	// 6
	0x5de0,0x5e00,0x5e30,0x5e60,0x5e90,0x5ec0,0x5ee0,0x5f00,0x5f10,0x5f20,	// 7
	0x5f30,0x5f40,0x5f50,0x5f60,0x5f70,0x5f80,0x5f90,0x5fa0,0x5fb0,0x5fc0,	// 8
	0x5fd0,0x5fe0,0x6000,0x6030,0x6060,0x6090,0x60c0,0x60e0,0x6100,0x6140,	// 9
	0x6180
	};//2004-04-10 4:05오전//청각에 대해 일정한 증감
	
	#else
	/*
	WORD code VolumeTable[101]={		// 1.3
	0x0000,0x4000,0x4800,0x5400,0x5a00,0x5e00,0x5e40,0x5e80,0x5ec0,0x5f00,	// 0
	0x5f40,0x5f80,0x5fc0,0x6000,0x6040,0x6080,0x60c0,0x6100,0x6140,0x6180,	// 1
	0x61c0,0x6200,0x6240,0x6280,0x62c0,0x6300,0x6340,0x6380,0x63c0,0x6400,	// 2
	0x6440,0x6480,0x64c0,0x6500,0x6540,0x6580,0x65c0,0x6600,0x6640,0x6680,	// 3
	0x66c0,0x66e0,0x6700,0x6720,0x6740,0x6760,0x6780,0x67a0,0x67c0,0x67e0,	// 4
	0x6820,0x6860,0x68a0,0x6900,0x6940,0x6960,0x69c0,0x6a20,0x6a60,0x6aa0,	// 5
	0x6b00,0x6b80,0x6c00,0x6c80,0x6d00,0x6d80,0x6e00,0x6e80,0x6f00,0x6f80,	// 6
	0x7000,0x7080,0x7100,0x7180,0x7200,0x7280,0x7300,0x7380,0x7400,0x7480,	// 7
	0x7500,0x7580,0x7600,0x7680,0x7700,0x7780,0x7800,0x7880,0x7900,0x7980, 	// 8
	0x7a00,0x7a80,0x7b00,0x7b80,0x7c00,0x7c80,0x7d00,0x7d80,0x7e00,0x7e80, 	// 9
	0x7f00				//100
	};	//이전값
	*/
	WORD code VolumeTable[101]={		// 1.3
	0x0000,0x4000,0x4800,0x5400,0x5a00,0x5e80,0x5f00,0x5f80,0x6000,0x6080,	// 0
	0x6100,0x6180,0x6200,0x6280,0x6300,0x6380,0x6400,0x6480,0x6500,0x6580,	// 1
	0x6600,0x6680,0x6700,0x6780,0x6800,0x6880,0x6900,0x6980,0x6a00,0x6a80,	// 2
	0x6b00,0x6b40,0x6b80,0x6bc0,0x6c00,0x6c40,0x6c80,0x6cc0,0x6d00,0x6d40,	// 3
	0x6d80,0x6dc0,0x6e00,0x6e40,0x6e80,0x6ec0,0x6f00,0x6f40,0x6f80,0x6fc0,	// 4
	0x7000,0x7040,0x7080,0x70c0,0x7100,0x7140,0x7180,0x71c0,0x7200,0x7240,	// 5
	0x7280,0x72c0,0x7300,0x7340,0x7380,0x73c0,0x7400,0x7440,0x7480,0x74c0,	// 6	
	0x7500,0x7540,0x7580,0x75c0,0x7600,0x7640,0x7680,0x76c0,0x7700,0x7740,	// 7
	0x7780,0x77c0,0x7800,0x7840,0x7880,0x78c0,0x7900,0x7940,0x7980,0x79c0,	// 8
	0x7a00,0x7a80,0x7b00,0x7b80,0x7c00,0x7c80,0x7d00,0x7d80,0x7e00,0x7e80, 	// 9
	0x7f00				//100
	};//2004-05-31 증감 레벨 조정..
	#endif
	
#endif

// smpark 20030722
BYTE code BassLevelTable[101]={
0xA1,0xA2,0xA3,0xA4,0xA5,0xA6,0xA8,0xAA,0xAC,0xAE,//09
0xB0,0xB2,0xB4,0xB6,0xB8,0xBA,0xBC,0xBE,0xC0,0xC2,
0xC4,0xC6,0xC8,0xCA,0xCC,0xCE,0xD0,0xD2,0xD4,0xD6,
0xD8,0xDA,0xDC,0xDE,0xE0,0xE2,0xE4,0xE6,0xE8,0xEA,
0xEC,0xEE,0xF0,0xF2,0xF4,0xF6,0xF8,0xFA,0xFC,0xFE,//49
0x00,0x02,0x04,0x06,0x08,0x0A,0x0C,0x0E,0x10,0x12,// 59
0x14,0x16,0x18,0x1A,0x1C,0x1E,0x20,0x22,0x24,0x26,	// 69
0x28,0x2A,0x2C,0x2E,0x30,0x32,0x34,0x36,0x38,0x3A,	// 79
0x3C,0x3E,0x40,0x42,0x44,0x46,0x48,0x4A,0x4C,0x4E,	// 89
0x50,0x52,0x54,0x56,0x58,0x5A,0x5B,0x5C,0x5D,0x5E,	// 99
0x5F	// 100
};

// smpark 20030722
BYTE code TrableLevelTable[101]={
0xA0,0xA8,0xAA,0xAC,0xAE,0xB0,0xB2,0xB4,0xB6,0xB8,
0xBA,0xBC,0xBE,0xC0,0xC2,0xC4,0xC6,0xC8,0xCA,0xCB,	// 19
0xCC,0xCE,0xCF,0xD1,0xD2,0xD4,0xD5,0xD7,0xD8,0xDA,	// 29
0xDB,0xDD,0xDE,0xE0,0xE1,0xE3,0xE4,0xE6,0xE7,0xE9,	// 39
0xEA,0xEC,0xED,0xEF,0xF0,0xF2,0xF3,0xF5,0xF6,0xF8,	// 49   :  -1 dB
0x00,0x08,0x0A,0x0B,0x0D,0x0F,0x11,0x12,0x14,0x15,	// 59
0x17,0x18,0x1A,0x1B,0x1D,0x1F,0x21,0x23,0x25,0x27,	// 69
0x29,0x2B,0x2D,0x2F,0x31,0x33,0x35,0x37,0x39,0x3B,	// 79
0x3D,0x3F,0x41,0x43,0x45,0x47,0x49,0x4B,0x4D,0x4F,	// 89
0x51,0x53,0x55,0x57,0x58,0x60,0x64,0x68,0x69,0x70,	// 99 	:  14 dB
0x78	// 100 	:  15 dB 
};

#ifdef LoudBarType
// smpark 20030722
BYTE code LoudnessLevelTable[101]={
0x00,0x01,0x01,0x02,0x02,0x03,0x03,0x04,0x04,0x05,	// 9
0x06,0x06,0x07,0x08,0x08,0x09,0x0A,0x0A,0x0B,0x0C,	// 19
0x0C,0x0D,0x0E,0x0E,0x0F,0x10,0x10,0x11,0x12,0x12,	// 29
0x13,0x14,0x14,0x15,0x16,0x16,0x16,0x17,0x18,0x18,	// 39
0x19,0x1A,0x1A,0x1B,0x1C,0x1C,0x1D,0x1E,0x1E,0X1F,	// 49
0x20,0x20,0x21,0x22,0x22,0x23,0x24,0x24,0x25,0x26,	// 59
0x26,0x27,0x28,0x28,0x29,0x2A,0x2A,0x2B,0x2C,0x2C,	// 69
0x2D,0x2E,0x2E,0x2F,0x30,0x30,0x31,0x32,0x32,0x33,	// 79
0x34,0x34,0x35,0x36,0x36,0x37,0x38,0x38,0x39,0x3A,	// 89
0x3A,0x3B,0x3C,0x3C,0x3D,0x3E,0x3E,0x3F,0x3F,0x40,	// 99	:  16 dB
0x44	// 100	:  17 dB
};
#endif

bit MSP34xyControleWrite(WORD Data)
{
	xBYTE	count =0;
	while(count<I2CErrorTry){	
		++count;
		if(BTC_START_I2C(MSP34xy_Addr))		continue;//Ack가 안왔다!!
		if(BTC_WriteData(Controle_Addr))			continue;//Ack가 안왔다!!
		if(BTC_WriteData((BYTE)(Data>>8)))			continue;//Ack가 안왔다!!
		if(BTC_WriteData((BYTE)(Data&0xff)))			continue;//Ack가 안왔다!!
		BTC_STOP_I2C();
		return 0;
		}
	return 1;
}

bit MSP34xyDSPWrite(unsigned char SubAddr,unsigned int RegAddr,unsigned int Data)
{
	xBYTE	count =0;
	while(count<I2CErrorTry){	
	++count;
	if(BTC_START_I2C(MSP34xy_Addr))		continue;//Ack가 안왔다!!
	if(BTC_WriteData(SubAddr))			continue;//Ack가 안왔다!!
	if(BTC_WriteData((BYTE)(RegAddr>>8)))			continue;//Ack가 안왔다!!	//RegAddr 상위 바이트 write
	if(BTC_WriteData((BYTE)(RegAddr&0xff)))			continue;//Ack가 안왔다!!	//RegAddr 하위 바이트
	if(BTC_WriteData((BYTE)(Data>>8)))			continue;//Ack가 안왔다!!
	if(BTC_WriteData((BYTE)(Data&0xff)))			continue;//Ack가 안왔다!!
	BTC_STOP_I2C();
	return 0;
	}
	return 1;
}

/*memorysave
WORD MSP34xyControleRead()
{

	xdata WORD Readdata =0;
	xBYTE count =0;
	
	while(count<I2CErrorTry){
		++count;
		if(BTC_START_I2C(MSP34xy_Addr)) continue;
		if(BTC_WriteData(Controle_Addr)) continue;
		if(BTC_START_I2C(MSP34xy_Addr|0x01)) continue;					//Read MODE( |0x01)
		Readdata = BTC_ReadDataACK();
		Readdata=Readdata<<8;
		Readdata += BTC_ReadDataNAK();
		//BTC_STOP_I2C();
		return (Readdata);
	}
	NOP;
}
*/

WORD MSP34xyDSPRead(unsigned char SubAddr,WORD RegAddr)
{
	xdata WORD Readdata =0;
	xBYTE count =0;
	
	while(count<I2CErrorTry){
		++count;
		if(BTC_START_I2C(MSP34xy_Addr))			continue;//Ack가 안왔다!!
		if(BTC_WriteData(SubAddr))				continue;//Ack가 안왔다!!
		if(BTC_WriteData((BYTE)(RegAddr>>8)))		continue;//Ack가 안왔다!!		
		if(BTC_WriteData((BYTE)(RegAddr&0xff)))	continue;//Ack가 안왔다!!
		if(BTC_START_I2C(MSP34xy_Addr|0x01))	continue;//Read MODE( |0x01)
		Readdata = BTC_ReadDataACK()<<8;
		Readdata |= BTC_ReadDataNAK();
//		BTC_STOP_I2C();
		return (Readdata);
	}
	return 0xffff;
}

void  SoundChipTest()
{	
	xdata WORD temp;
	SProcessor=0;

		//temp=MSP34xyControleRead();
		temp= MSP34xyDSPRead(DSP_Addr|0x01,0x001F);

		switch(temp>>8)
		{
			case 0x0A:
				SProcessor=SPROCRSSOR_MSP3410;
				break;
			case 0x14:
				SProcessor=SPROCRSSOR_MSP3420;
				break;
			case 0x0F:
				SProcessor=SPROCRSSOR_MSP3415;
				break;
			case 0x19:
				SProcessor=SPROCRSSOR_MSP3425;
				break;	
			default:
				SProcessor=SPROCRSSOR_NON;
				break;					
		}
		
		#ifdef USE_UART
		switch(temp>>8)
		{
			case 0x0A:
				DBGputs("MSP3410 sound chip");
				break;
			case 0x14:
				DBGputs("MSP3420 sound chip");
				break;
			case 0x0F:
				DBGputs("MSP3415 sound chip");
				break;
			case 0x19:
				DBGputs("MSP3425 sound chip");
				break;	
			default:
				DBGputs("NO sound chip");
				break;					
		}
		#endif

}


void MspSelect(void)	//2004-04-09
{
	//xdata	WORD DetectMSP;
	BYTE temp;
	
	
	
#if defined(USE_NTSCtuner)

		switch(xEEPROMBuffer[SystemCountry]) 
		{
			case 0:	//korea
				MSP34xyDSPWrite(0x10,0x0020,0x0002);	// M-Dual FM-Stereo
				break;
			case 1: //USA
				MSP34xyDSPWrite(0x10,0x0020,0x0020);	// BTSC-Stereo
				break;
			case 2: //Japan
				MSP34xyDSPWrite(0x10,0x0020,0x0030);	// M-EIA-J Japen Stereo
				break;
			default: //auto.
				MSP34xyDSPWrite(0x10,0x0020,0x0001);	// ALL Standard
				break;
		}
	
		temp=TW990xRead(0x01);
		if( ((((temp&0x68)==0x00)||(temp&0x80)==0x80)) && xEEPROMBuffer[BscrFlag_buf]==1 )
		{
				MSP34xyDSPWrite(0x10,0x0024,0x0000);	//Carrier Mute On
		}
		else	MSP34xyDSPWrite(0x10,0x0024,0x07ff);	//Carrier Mute Off
		
#else

	//MSP34xyDSPWrite(0x10,0x0020,0x0006);	// D/K-FM-MONO (6.5MHz)
	//MSP34xyDSPWrite(0x10,0x0020,0x0004);	// D/K1 (6.5MHz)
	//MSP34xyDSPWrite(0x10,0x0020,0x0005);	// D/K2 (6.5MHz)
	//MSP34xyDSPWrite(0x10,0x0020,0x000a);	// I-NICAM-FM (6.5MHz)		((PAL I : 6.0)

	
	//DetectMSP=MSP34xyDSPRead(0x11,0x7e);	//2004-06-21
	//if(OldDetectSound!=DetectMSP)
	//{
		//OldDetectSound=DetectMSP;
	
		switch(MSP34xyDSPRead(0x11,0x7e))	//2004-04-09
		{
			#if 0
			case 0x000a: //I-Nicam-FM
				MSP34xyDSPWrite(0x10,0x0020,0x000a);
				break;
			case 0x0004: //D/K1-Dual-Stereo
				MSP34xyDSPWrite(0x10,0x0020,0x0004);
				break;
			case 0x0009: //L-Nicam-FM
			case 0x000b: //D/K-Nicam
				MSP34xyDSPWrite(0x10,0x0020,0x000d);
				break;
			#endif
			
			case 0x0000:		//not find a sound standard
				MSP34xyDSPWrite(0x10,0x0020,0x0001);	//(ALL Standard))
				if(xEEPROMBuffer[BscrFlag_buf]==0)		MSP34xyDSPWrite(0x10,0x0024,0x07ff);	//Carrier Mute Off
				else	MSP34xyDSPWrite(0x10,0x0024,0x0000);	//Carrier Mute On
				break;
				
			default:
			//LED_ON;//test
				MSP34xyDSPWrite(0x10,0x0020,0x0001);	//(ALL Standard))
				//if(  (TW990xRead(0x01)&&0x80!=0) && xEEPROMBuffer[BscrFlag_buf]==1 )
				
				temp=TW990xRead(0x01);
				
//				DBGputss(temp);//test
//				DBGputs("=temp");//test
				
				//if( (temp&0xc8!=0x48) && xEEPROMBuffer[BscrFlag_buf]==1 )
				//if(  (temp&&0x80==0x80) & xEEPROMBuffer[BscrFlag_buf]==1 )
				//if(  ((temp&0x80)==0x80)  )
				if( ((((temp&0x68)==0x00)||(temp&0x80)==0x80)) && xEEPROMBuffer[BscrFlag_buf]==1 )
				{
						MSP34xyDSPWrite(0x10,0x0024,0x0000);	//Carrier Mute On
				}
				else	
				{
						MSP34xyDSPWrite(0x10,0x0024,0x07ff);	//Carrier Mute Off
				}
				break;
		}
	//}
		
#endif
}

void SoundInit()
{

	SoundChipTest();
	if(SProcessor==SPROCRSSOR_NON)  return;

	switch(SProcessor)
		{
		case SPROCRSSOR_MSP3420:
		case SPROCRSSOR_MSP3425:
		case SPROCRSSOR_MSP3415:
			MSP34xyControleWrite(0x8000);
			MSP34xyControleWrite(0x0000);
			#ifdef USE_NTSCtuner//---------------------
			switch(xEEPROMBuffer[SystemCountry]) 
			{
				case 0:	//korea
					MSP34xyDSPWrite(0x10,0x0030,0x0002);
					break;
				case 1: //USA
					MSP34xyDSPWrite(0x10,0x0030,0x2002);
					break;
				case 2: //Japan
					MSP34xyDSPWrite(0x10,0x0030,0x4002);
					break;
				default: //auto.
					MSP34xyDSPWrite(0x10,0x0030,0x0002);
					break;
			}
			#else	//pal-----------------------------
				MSP34xyDSPWrite(0x10,0x0030,0x1002);
			#endif//------------------------------------

			//#if defined(Mono_Sound)
			//	MSP34xyDSPWrite(0x12,0x0008,0x0030);	//mono
			//#else
				MSP34xyDSPWrite(0x12,0x0008,0x0020);	//stereo
			//#endif
			
			MSP34xyDSPWrite(0x12,0x000E,FM_PreScale+0x03);	//FM presclae
			MSP34xyDSPWrite(0x12,0x0010,0x5A00);			//Nicam presclae
			
			MspSelect();
			//MSP34xyDSPWrite(0x12,0x0000,0x7300);	//Volume	// 0dB 
			//MSP34xyDSPWrite(0x12,0x0000,0x0000);	//Volume	// -114dB(mute)
			MSP34xyDSPWrite(0x12,0x0000,VolumeTable[xEEPROMBuffer[VOLUME_buf]]);	//Volume	// -114dB(mute)+volume_value
			MSP34xyDSPWrite(0x12,0x000D,0x1900);	//Scart input	// 0dB Gain	
			
			MSP34xyDSPWrite(0x12,0x0029,0x8201);	//AVC on	//2004-05-27
			break;								
		}
	SoundSet();
	
}


void MspSet(void)
{
	#ifdef USE_NTSCtuner//---------------------
	switch(xEEPROMBuffer[SystemCountry]) 
	{
		case 0:	//korea
			MSP34xyDSPWrite(0x10,0x0030,0x0002);
			break;
		case 1: //USA
			MSP34xyDSPWrite(0x10,0x0030,0x2002);
			break;
		case 2: //Japan
			MSP34xyDSPWrite(0x10,0x0030,0x4002);
			break;
		default: //auto.
			MSP34xyDSPWrite(0x10,0x0030,0x0002);
			break;
	}
	#else	//pal-----------------------------
		MSP34xyDSPWrite(0x10,0x0030,0x1002);
	#endif//------------------------------------
	MSP34xyDSPWrite(0x12,0x0008,0x0020);	//stereo
	MSP34xyControleWrite(0x8000);
	MSP34xyControleWrite(0x0000);
	
	
	MSP34xyDSPWrite(0x12,0x000E,FM_PreScale+0x03);
	MSP34xyDSPWrite(0x12,0x0010,0x5A00);
	
	MspSelect();
	
//	MSP34xyDSPWrite(0x12,0x0000,0x0000);	//Volume	// -114dB(mute)
	MSP34xyDSPWrite(0x12,0x0000,VolumeTable[xEEPROMBuffer[VOLUME_buf]]);	//Volume	// -114dB(mute)
	MSP34xyDSPWrite(0x12,0x000D,0x1900);	//Scart input	// 0dB Gain	
									

	SoundSet();
}	


// 1: SIF Stereo or A/B
// 2: AV input
// 3: SIF Stereo or A
// 4: SIF Stereo or B

void SoundInputSelection(unsigned char input)
{
	switch(SProcessor)	{
		case SPROCRSSOR_MSP3420:
		case SPROCRSSOR_MSP3425:	
		case SPROCRSSOR_MSP3415:
			//#if defined(Mono_Sound)
			//MSP34xyDSPWrite(0x12,0x0008,((WORD)input<<8)+0x30);
			//#else
			MSP34xyDSPWrite(0x12,0x0008,((WORD)input<<8)+0x20);
			//#endif
			break;
		}
}

void ScartSwitch(unsigned int ACBRegister)
{
	switch(SProcessor)	{
		case SPROCRSSOR_MSP3420:
		case SPROCRSSOR_MSP3425:		
		case SPROCRSSOR_MSP3415:	
			MSP34xyDSPWrite(0x12,0x13,ACBRegister);
			break;
		}
}

void	SoundProcess()
{
	if(PowerOnsequence<PowerOnNormalStatus) return;

	if(SoundProcessTimer!=0)	return;
			
	SoundProcessStatus=SoundGetStatus();
	SoundTimer=80;

//	MspSelect();
	
	if(SoundProcessStatus != PreSoundMode)
	{
		switch(SoundProcessStatus)
		{
			case SoundType_MONO:
				SoundMode=0;
				//  Clear MTS Status
				MTS_Stereo=MTS_NONE;		// smpark 20030818
				MTS_Bilingual=MTS_NONE; 		// smpark 20030818
				SoundSetMono();
//				ShowChannelStatus(DISPLAY_MTS);
			break;
		
		case SoundType_STEREO:
				SoundMode=2;
				//#if defined(Mono_Sound)
				//SoundSetMono();//test//2004-01-05
				//#else
				SoundSetStereo();
				//#endif
				// Set MTS status			
				MTS_Stereo=MTS_STEREO_ON;
				MTS_Bilingual=MTS_NONE; 					
				if(((NowTopOsdOn==0) && (MENUstatus ==0)) ||(MENUstatus == TVchannelDisplay)){
					// Show MTS status  
					//#ifndef Mono_Sound	//2003-10-26
					ShowChannelStatus(DISPLAY_MTS);
					Recall();
					//#endif
				}
			break;
			
		case SoundType_SAP:
			SoundMode=3;
				SoundSetMTSmain();
				// Set MTSstatus
				MTS_Stereo=MTS_NONE;
				MTS_Bilingual	=MTS_LANG_A;
				
				//#ifndef Mono_Sound	//2003-10-26
				if(((NowTopOsdOn==0) && (MENUstatus==0)) ||(MENUstatus == TVchannelDisplay))
				{
					// Show MTS status  
					ShowChannelStatus(DISPLAY_MTS);
					Recall();
					
				}
				//#endif
			break;
		}
		PreSoundMode=SoundProcessStatus;
	}

}

// smpark 20030721
//	SMART SOUND CONTROL
void SoundSet()
{
	switch(xEEPROMBuffer[SSC]){
	case 0 :	//Normal
		xEEPROMBuffer[TREBLE]=	50;
		xEEPROMBuffer[BASS]=	50;
		#ifdef LoudBarType
		xEEPROMBuffer[LOUDNESS]=SOUND_LOUDNESS_max;	//50;
		#else
		xEEPROMBuffer[LOUDNESS]=0x00;
		#endif
		break;
		
	case 1:	// Music
		xEEPROMBuffer[TREBLE]=	70;
		xEEPROMBuffer[BASS]=	80;
		#ifdef LoudBarType
		xEEPROMBuffer[LOUDNESS]=SOUND_LOUDNESS_max;	//60;
		#else
		xEEPROMBuffer[LOUDNESS]=0x01;
		#endif
		break;
		
	case 2:	// Cinema
		xEEPROMBuffer[TREBLE]=	60;
		xEEPROMBuffer[BASS]=	70;
		#ifdef LoudBarType
		xEEPROMBuffer[LOUDNESS]=SOUND_LOUDNESS_max;	//65;
		#else
		xEEPROMBuffer[LOUDNESS]=0x01;
		#endif
		break;
		
	case 3:	// News
		xEEPROMBuffer[TREBLE]=	60;
		xEEPROMBuffer[BASS]=	40;
		#ifdef LoudBarType
		xEEPROMBuffer[LOUDNESS]=SOUND_LOUDNESS_max;	//60;
		#else
		xEEPROMBuffer[LOUDNESS]=0x00;
		#endif
		break;
		
	case 4:	// User
		xEEPROMBuffer[TREBLE]=EEPROM_Read(TREBLE_adr);
		xEEPROMBuffer[BASS]=EEPROM_Read(BASS_adr);
		xEEPROMBuffer[LOUDNESS]=EEPROM_Read(LOUDNESS_adr);
		break;
		
	}
	SoundSetBass( );
	SoundSetTreble();
	SoundSetLoudness();	
}

void SetFMmatrix(BYTE value) 
{
	switch(SProcessor)	{
		case SPROCRSSOR_MSP3420:
		case SPROCRSSOR_MSP3425:
		case SPROCRSSOR_MSP3415:	
			MSP34xyDSPWrite(0x12,0x000E,FM_PreScale+value);	//FM_PreScale:0x2400
			break;
		}	

}

unsigned char  SoundGetStatus(void)	
{
	xdata WORD status;
	switch(SProcessor)	{
		case SPROCRSSOR_MSP3420:
		case SPROCRSSOR_MSP3425:
		case SPROCRSSOR_MSP3415:
		/*	
		#if	0//def TestTunerSound//---------------------//2004-04-03
		{
			extern BYTE testI2Cflag;			
			if(testI2Cflag)	status=MSP34xyDSPRead(0x11,0x0200);
			else return SoundType_MONO;
		}
		#else
			status=MSP34xyDSPRead(0x11,0x0200);
		#endif	
		*/
			status=MSP34xyDSPRead(0x11,0x0200);

			if(status&0x0100) return SoundType_SAP;
			if(status&0x0040) return SoundType_STEREO;
			else	return SoundType_MONO;
			break;
			
		default :
			return SoundType_MONO;
			break;
		}
}
void SaveCurrentSSCToUser()
{
	xEEPROMBuffer[SSC]=SSCUser;
	EepromSetQue(TREBLE_adr,xEEPROMBuffer[TREBLE]);
	EepromSetQue(BASS_adr,xEEPROMBuffer[BASS]);
	EepromSetQue(LOUDNESS_adr,xEEPROMBuffer[LOUDNESS]);
	EepromSetQue(SSC_adr, SSCUser);
}



/* memorysave
void SoundSetVolume(BYTE value )	
{
	switch(SProcessor)	{
		case SPROCRSSOR_MSP3420:
		case SPROCRSSOR_MSP3425:
		case SPROCRSSOR_MSP3415:
			MSP34xyDSPWrite(0x12,0x0000,(WORD)value<<8);
			break;
		}	
}
*/

// smpark 20030923
void SoundSetVolume()
{
	switch(SProcessor)	{
		case SPROCRSSOR_MSP3420:
		case SPROCRSSOR_MSP3425://
		case SPROCRSSOR_MSP3415:
#ifdef VOLUME_PWM
			MSP34xyDSPWrite(0x12,0x0000,(WORD)(VolumeTable[xEEPROMBuffer[VOLUME_buf]]<<8));
#else
			MSP34xyDSPWrite(0x12,0x0000,(WORD)(VolumeTable[xEEPROMBuffer[VOLUME_buf]]));
		/*	
			if(MSP34xyDSPRead(0x11,0x7e)!=0x000a)
			{
				MSP34xyDSPWrite(0x12,0x0000,(WORD)(VolumeTable[xEEPROMBuffer[VOLUME_buf]])+0x1b00);
				if(MSP34xyDSPRead(0x11,0x7e)==0x0004)
				{
					MSP34xyDSPWrite(0x12,0x000E,FM_PreScale+0x1003);
				}
			}
			else MSP34xyDSPWrite(0x12,0x0000,(WORD)(VolumeTable[xEEPROMBuffer[VOLUME_buf]]));
			*/
			EepromSetQue(VOLUME_adr,xEEPROMBuffer[VOLUME_buf]);//
			
#endif
			break;
		}	
}

// smpark 20030925
void SoundFastMute()
{
	switch(SProcessor)	{
		case SPROCRSSOR_MSP3420:
		case SPROCRSSOR_MSP3425:
		case SPROCRSSOR_MSP3415:
			MSP34xyDSPWrite(0x12,0x0000,(WORD)0xff00);
			break;
		}
}

void SoundSetBass( )	
{
	switch(SProcessor)	{
		case SPROCRSSOR_MSP3420:
		case SPROCRSSOR_MSP3425:
		case SPROCRSSOR_MSP3415:
			#ifdef LoudBarType
			MSP34xyDSPWrite(0x12,0x0002,(WORD)BassLevelTable[100-xEEPROMBuffer[BASS]]<<8);
			#else
			MSP34xyDSPWrite(0x12,0x0002,(WORD)BassLevelTable[xEEPROMBuffer[BASS]]<<8);
			#endif
			break;
		}	
}

void SoundSetTreble()	
{
	switch(SProcessor)	{
		case SPROCRSSOR_MSP3420:
		case SPROCRSSOR_MSP3425:
		case SPROCRSSOR_MSP3415:
			MSP34xyDSPWrite(0x12,0x0003,(WORD)BassLevelTable[xEEPROMBuffer[TREBLE]]<<8);
			break;
		}
}

void SoundSetLoudness()	
{
	switch(SProcessor)	{
		case SPROCRSSOR_MSP3420:
		case SPROCRSSOR_MSP3425:
		case SPROCRSSOR_MSP3415:
			
			#ifdef LoudBarType
			MSP34xyDSPWrite(0x12,0x0004,(WORD)LoudnessLevelTable[100-xEEPROMBuffer[LOUDNESS]]<<8);
			#else
			if(xEEPROMBuffer[LOUDNESS])
			{
				MSP34xyDSPWrite(0x12,0x0004,0x4404);
				//MSP34xyDSPWrite(0x12,0x0004,0x4400);
				
			}
			else
			{
				MSP34xyDSPWrite(0x12,0x0004,0x2000);
				//MSP34xyDSPWrite(0x12,0x0004,0x0000);
				
			}
			#endif
			break;
		}	
}

void SetToMono()
{
		SoundSetMono();
		SoundMode=0;
		PreSoundMode=SoundType_MONO;
		//  Clear MTS Status
		MTS_Stereo=MTS_NONE;		// smpark 20030818
		MTS_Bilingual=MTS_NONE; 		// smpark 20030818
		SoundTimer=500;			//
}

// smpark 20030825
void StereoSet()	
{
	if(MTS_Stereo==MTS_STEREO_ON){
 		//#if defined(Mono_Sound)
 		//SoundSetMono();//test//2004-01-05
 		//#else
 		SoundSetStereo();
 		//#endif
	}else if(MTS_Stereo==MTS_STEREO_OFF){
 		SoundSetMono();
	}
}

// smpark 20030825
void BilingualSet()
{
 	if(MTS_Bilingual==MTS_LANG_A){
 		SoundSetMTSmain();
 	}else if(MTS_Bilingual==MTS_LANG_B){
		SoundSetMTSsub();
 	}else if(MTS_Bilingual==MTS_LANG_AB){
		SoundSetMTSmix();
 	}
}

