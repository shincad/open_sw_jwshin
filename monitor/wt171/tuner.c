#include	"..\TopHeader.h"
#include	<stdlib.h>
#include	"..\power.h"
#include	"..\eepromadr.h"
#include	"..\TVMODE.h"
#include <string.h>
#include <stdio.h>
#include "..\extern.h"
#include "..\mtv230xfr.h"
#include "..\tuner.h"
#include "tools.h"
#include "btc_osdmenu.h"

//#include "BTC_230OSDdef.h"
//-----------------------------------------------

/*
#define AUTO_SEARCH_TIME 0x04	// by LKE 2/15�� 7�� fix
#define AUTO_SEARCH_TIME2 0x03//0x10	// by LKE 2/15�� 7�� fix
#define AUTO_SEARCH_TIME3 0x01//0x02	// by LKE 2/15�� 7�� fix
*/

#if defined(USE_NTSCtuner)
// �ＺƩ�ʿ� ������ ����.(ntsc tuner)  --> tuner�� ��Ʈ�� ���� AFT Curve�� ������ �ٸ���.
// �Ʒ��� �������� 4���� �Ｚ ntsc����Ʃ�ʸ� �½�Ʈ �� ��� ���� ������ ���̴�.(2003��3��4�� fix  By LKE) 
#define AFT_MAINTIME 	35
#define AFT_NORMALTIME	25
#define AFT_MAINCOUNT 	5
#define AFT_SUBCOUNT 	2

#define NUM_10 10
#define NUM_20 20
#else
// �ＺƩ�ʿ� ������ ����.(pal tuner) --> �̰��� ����.
#define AFT_MAINTIME 	35
#define AFT_NORMALTIME	25

#define AFT_MAINCOUNT 	5
#define AFT_SUBCOUNT 	2

#define NUM_10 10
#define NUM_20 20

#endif
//

#ifdef	USE_4BitInterface								//4bit��� �Լ�����
void	WriteReg4bit(BYTE address, BYTE Recdata);
#define	WriteScaler(val1,val2) WriteReg4bit(val1,val2)	
BYTE	ReadScalerParallel(BYTE address);
#define	ReadScaler	ReadScalerParallel
#else											//1bit��� �Լ�����
BYTE	ReadScalerSerial(BYTE address);
#define	ReadScaler	ReadScalerSerial
void	WriteReg1bit(BYTE address, BYTE Recdata);
#define	WriteScaler(val0, val1) WriteReg1bit(val0, val1)
#endif


//-----------------------------------------------
extern void CheckTVSignal1(BYTE Count);
BYTE TunerDataCatch();
xdata BYTE errorflag;
extern void PutStringAttr2(BYTE x,BYTE y,BYTE *Pointer);

//extern unsigned short SyncRead(void);


//extern void SetSCL(unsigned char );
//extern void SetSDA(unsigned char );
extern void MsgView(char *);
extern void PutVolume(bit);	// 2002.12.28 LKE
//extern void SoftVolume(bit);	// 1�� 17��. LEE
void EepromSetQue(WORD address, BYTE Recdata);

extern void DisplayPWMScale(BYTE,BYTE,BYTE,BYTE);	// 1�� 17��.
extern void PutString1(BYTE ,BYTE ); 	// 4�� 15��. 
//extern void DisplayChannelValue(BYTE,BYTE,BYTE);	// 1�� 17��.
extern void PowerOff();	// 1�� 17��.
extern void WarmUp();	// 1�� 17��.
extern WriteEEPROM(BYTE,BYTE,BYTE);
//extern void ShowOSDChannelYellow(unsigned char,unsigned char,Bool);
extern void ShowOSDChannel(unsigned char,unsigned char,bit,BYTE);
void TvPllOk(unsigned int Divider);
//void EepTvFillValue(WORD Addr,BYTE StartOffset,BYTE EndOffset,BYTE Value1,BYTE Value2);
BYTE AftSubFunction( WORD AFTDivider, BYTE AFTValue, bit Test);
void EMITestDataLoading(void);
void CheckTVSignal(BYTE Count);
BYTE EEPROM_Read(WORD );
void PutVolumePWM();
void putss(BYTE value);
Bool SearchPll_set();
void SearchSave();
void FillRestChannel();
void AutoChannelDisplay();
void ChannelChange(void);	//smpark 20030806
extern void MspSet();
extern void MspSelect();
//extern void ShowChannelStatus(unsigned char status);
extern 	void	PipChannelOSD(void);
extern	void ChannelOSD(BYTE HPos,  BYTE VPos );
extern	void BitWriteScaler(BYTE address, BYTE BitArry, BYTE Recdata);
extern	BYTE	KEY_value;

//--------------------------------------------------------------------------
#if defined(USE_NTSCtuner)
//--------------------------------------------------------------------------	
	#ifdef TunerRefDiv512 	//(Freq.step:62.5KHz)
	//--------------------------------------------------------------------
	//2004-01-15 made by thkim
	// NTSC USA/KOREA CableTV -->TAPC-H701F�� ���ĳ��� ���ļ� ���̺�.
	code unsigned short NTSCKORCATV[124]={	// 2003.1.14 ȭ���� FIX --(Analog Cable TV Nominal Frequencies)
	0x0650,0x06B0,0x0710,0x07B0,0x0810,0x0DD0,0x0E30,0x0E90,0x0EF0,					//2~10
	0x0F50,0x0FB0,0x1010,0x0A70,0x0AD0,0x0B30,0x0B90,0x0BF0,0x0C50,0x0CB0,	//11~
	0x0D10,0x0D70,0x1070,0x10D0,0x1130,0x1190,0x11F0,0x1250,0x12B0,0x1310,  //21~
	0x1370,0x13D0,0x1430,0x1490,0x14F0,0x1550,0x15B0,0x1610,0x1670,0x16D0,  //31~
	0x1730,0x1790,0x17F0,0x1850,0x18B0,0x1910,0x1970,0x19D0,0x1A30,0x1A90,  //41~
	0x1AF0,0x1B50,0x1BB0,0x1C10,0x1C70,0x1CD0,0x1D30,0x1D90,0x1DF0,0x1E50,  //51~
	0x1EB0,0x1F10,0x1F70,0x1FD0,0x2030,0x2090,0x20F0,0x2150,0x21B0,0x2210,  //61~
	0x2270,0x22D0,0x2330,0x2390,0x23F0,0x2450,0x24B0,0x2510,0x2570,0x25D0,  //71~
	0x2630,0x2690,0x26F0,0x2750,0x27B0,0x2810,0x2870,0x28D0,0x2930,0x2990,  //81~
	0x29F0,0x2A50,0x2AB0,0x2B10,0x0890,0x08F0,0x0950,0x09B0,0x0A10,0x2B70,  //91~
	0x2BD0,0x2C30,0x2C90,0x2CF0,0x2D50,0x2DB0,0x2E10,0x2E70,0x2ED0,0x2F30,  //101~
	0x2F90,0x2FF0,0x3050,0x30B0,0x3110,0x3170,0x31D0,0x3230,0x3290,0x32F0,  //111~
	0x3350,0x33B0,0x3410,0x3470,0x34D0																			//121~125
	};
	
	code unsigned short NTSCKORAIR[68]={	// 2004-07-16 by thkim
	0x0650,0x06B0,0x0710,0x07B0,0x0810,0x0DD0,0x0E30,0x0E90,0x0EF0,					//2~10
	0x0F50,0x0FB0,0x1010,0x2050,0x20B0,0x2110,0x2170,0x21D0,0x2230,0x2290,   //11~ 
	0x22F0,0x2350,0x23B0,0x2410,0x2470,0x24D0,0x2530,0x2590,0x25F0,0x2650,   //21~ 
	0x26B0,0x2710,0x2770,0x27D0,0x2830,0x2890,0x28F0,0x2950,0x29B0,0x2A10,   //31~ 
	0x2A70,0x2AD0,0x2B30,0x2B90,0x2BF0,0x2C50,0x2CB0,0x2D10,0x2D70,0x2DD0,   //41~ 
	0x2E30,0x2E90,0x2EF0,0x2F50,0x2FB0,0x3010,0x3070,0x30D0,0x3130,0x3190,   //51~ 
	0x31F0,0x3250,0x32B0,0x3310,0x3370,0x33D0,0x3430,0x3490,0x34F0           //61~69
	};
	//--------------------------------------------------------------------
	#else		// (Freq.step:50KHz)
	//--------------------------------------------------------------------
	// NTSC USA/KOREA CableTV -->TAPC-H701F�� ���ĳ��� ���ļ� ���̺�.
	code unsigned short NTSCKORCATV[124]={	// 2003.1.14 ȭ���� FIX --(Analog Cable TV Nominal Frequencies)
	0x07E4,0x085C,0x08D4,0x099C,0x0A14,0x1144,0x11BC,0x1234,0x12AC,
	0x1324,0x139C,0x1414,0x0D0C,0x0D84,0x0DFC,0x0E74,0x0EEC,0x0F64,0x0FDC,
	0x1054,0x10CC,0x148C,0x1504,0x157C,0x15F4,0x166C,0x16E4,0x175C,0x17D4,
	0x184C,0x18C4,0x193C,0x19B4,0x1A2C,0x1AA4,0x1B1C,0x1B94,0x1C0C,0x1C84,
	0x1CFC,0x1D74,0x1DEC,0x1E64,0x1EDC,0x1F54,0x1FCC,0x2044,0x20BC,0x2134,
	0x21AC,0x2224,0x229C,0x2314,0x238C,0x2404,0x247C,0x24F4,0x256C,0x25E4,
	0x265C,0x26D4,0x274C,0x27C4,0x283C,0x28B4,0x292C,0x29A4,0x2A1C,0x2A94,
	0x2B0C,0x2B84,0x2BFC,0x2C74,0x2CEC,0x2D64,0x2DDC,0x2E54,0x2ECC,0x2F44,
	0x2FBC,0x3034,0x30AC,0x3124,0x319C,0x3214,0x328C,0x3304,0x337C,0x33F4,
	0x346C,0x34E4,0x355C,0x35D4,0x0AB4,0x0B2C,0x0BA4,0x0C1C,0x0C94,0x364C,
	0x36C4,0x373C,0x37B4,0x382C,0x38A4,0x391C,0x3994,0x3A0C,0x3A84,0x3AFC,
	0x3B74,0x3BEC,0x3C64,0x3CDC,0x3D54,0x3DCC,0x3E44,0x3EBC,0x3F34,0x3FAC,
	0x4024,0x409C,0x4114,0x418C,0x4204
	};

	// NTSC USA/KOREA BroadCast -->TAPC-H701F�� ���ĳ��� ���ļ� ���̺�.
	code unsigned short NTSCKORAIR[68]={	// 2003.1.14 ȭ���� FIX --(Analog Boradcast Nominal Frequencies)
	0x07E4,0x085C,0x08D4,0x099C,0x0A14,0x1144,0x11BC,0x1234,0x12AC,						//2~10 
	0x1324,0x139C,0x1414,0x2864,0x28DC,0x2954,0x29CC,0x2A44,0x2ABC,0x2B34,		//11~  
	0x2BAC,0x2C24,0x2C9C,0x2D14,0x2D8C,0x2E04,0x2E7C,0x2EF4,0x2F6C,0x2FE4,    //21~  
	0x305C,0x30D4,0x314C,0x31C4,0x323C,0x32B4,0x332C,0x33A4,0x341C,0x3494,    //31~  
	0x350C,0x3584,0x35FC,0x3674,0x36EC,0x3764,0x37DC,0x3854,0x38CC,0x3944,    //41~  
	0x39BC,0x3A34,0x3AAC,0x3B24,0x3B9C,0x3C14,0x3C8C,0x3D04,0x3D7C,0x3DF4,    //51~  
	0x3E6C,0x3EE4,0x3F5C,0x3FD4,0x404C,0x40C4,0x413C,0x41B4,0x422C            //61~69
	};   
	
	//--------------------------------------------------------------------------
	// NTSC JAPAN CableTV -->TAPC-H701F�� ���ĳ��� ���ļ� ���̺�.
	code unsigned int NTSCJPNCATV[63] = {	// 2003.1.14 ȭ���� FIX --(Analog Cable TV Nominal Frequencies)
	0x0AB4,0x0B2C,0x0BA4,0x10F4,0x116C,0x11E4,0x125C,0x12AC,0x1324,0x139C,
	0x1414,0x148C,0x0C1C,0x0C94,0x0D0C,0x0D84,0x0DFC,0x0E74,0x0EEC,0x0F64,
//youngdo 3002.8.22	0x0FDC,0x107C,0x1504,0x15A4,0x161C,0x1694,0x170C,0x175C,0x17D4,0x184C,
	0x0FDC,0x107C,0x1504,0x157C,0x15F4,0x166C,0x16E4,0x175C,0x17D4,0x184C,	//youngdo 3002.8.22 �Ϻ� ä���� ���̺��� �ȸ���.
	0x18C4,0x193C,0x19B4,0x1A2C,0x1AA4,0x1B1C,0x1B94,0x1C0C,0x1C84,0x1CFC,
	0x1D74,0x1DEC,0x1E64,0x1EDC,0x1F54,0x1FCC,0x2044,0x20BC,0x2134,0x21AC,
	0x2224,0x229C,0x2314,0x238C,0x2404,0x247C,0x24F4,0x256C,0x25E4,0x265C,
	0x26D4,0x274C,0x27C4
	};
	// NTSC JAPAN  BroadCast -->TAPC-H701F�� ���ĳ��� ���ļ� ���̺�.
	code unsigned int NTSCJPNAIR[62]={	// 2003.1.14 ȭ���� FIX --(Analog Boradcast Nominal Frequencies for Japan)
	0x0AB4,0x0B2C,0x0BA4,0x10F4,0x116C,0x11E4,0x125C,0x12AC,0x1324,0x139C,
	0x1414,0x148C,0x2864,0x28DC,0x2954,0x29CC,0x2A44,0x2ABC,0x2B34,0x2BAC,
	0x2C24,0x2C9C,0x2D14,0x2D8C,0x2E04,0x2E7C,0x2EF4,0x2F6C,0x2FE4,0x305C,
	0x30D4,0x314C,0x31C4,0x323C,0x32B4,0x332C,0x33A4,0x341C,0x3494,0x350C,
	0x3584,0x35FC,0x3674,0x36EC,0x3764,0x37DC,0x3854,0x38CC,0x3944,0x39BC,
	0x3A34,0x3AAC,0x3B24,0x3B9C,0x3C14,0x3C8C,0x3D04,0x3D7C,0x3DF4,0x3E6C,
	0x3EE4,0x3F5C	
	};	
	#endif
	

	//-------------------------------------------------
	code unsigned short SECAMFRNACECATV[1]={0xffff};
	code unsigned short SECAMFRNACEAIR[1]={0xffff};	
	
	code unsigned short PALGERMANYCATV[1]={0xffff};
	code unsigned short PALGERMANYAIR[1]={0xffff};	
	
	code unsigned short PALITALYCATV[1]={0xffff};
	code unsigned short PALITALYAIR[1]={0xffff};	

	code unsigned short PALNETHERLANDCATV[1]={0xffff};
	code unsigned short PALNETHERLANDAIR[1]={0xffff};		

	code unsigned short SECAMRUSSIACATV[1]={0xffff};
	code unsigned short SECAMRUSSIAAIR[1]={0xffff};	
	
	code unsigned short PALUKCATV[1]={0xffff};
	code unsigned short PALUKAIR[1]={0xffff};	
	//-------------------------------------------------
//--------------------------------------------------------------------------
#else	//pal
//--------------------------------------------------------------------------
	//-------------------------------------------------
	//code unsigned short 	NTSCKORCATV[1]={0xffff};
	//code unsigned short 	NTSCKORAIR[1]={0xffff};
	
	//code unsigned int 		NTSCJPNCATV[1]={0xffff};
	//code unsigned int 		NTSCJPNAIR[1]={0xffff};
	//-------------------------------------------------
	
	//--------------------------------------------------------------------------
	//PAL-B/G NETHERLAND CableTV -->TCPQ9091PD28L�� ���ĳ��� ���ļ� ���̺�.
	code unsigned short PALNETHERLANDCATV[41]={	// 2003.1.14 ȭ���� FIX
	0x0B43,0x0BCF,0x0C5B,0x0CE7,0x0D73,0x0DFF,0x0E8B,0x0F17,0x0FA3,0x102F,
	0x151A,0x15A6,0x1632,0x16BE,0x174A,0x17D6,0x1862,0x18EE,0x197A,0x1A06,
	0x1ABA,0x1B5A,0x1BFA,0x1C9A,0x1D3A,0x1DDA,0x1E7A,0x1F1A,0x1FBA,0x205A,
	0x20FA,0x219A,0x223A,0x22DA,0x237A,0x241A,0x24BA,0x255A,0x25FA,0x269A,
	0x273A
	
	/*
	0x075B,0x07FB,0x0FA3,0x102F,0x10BB,0x1147,0x11D3,0x125F,0x12EB,0x1377,
	0x1402,0x148E,0x151A,0x1632,0x16BE,0x174A,0x17D6,0x1862,0x18EE,0x27DA,
	0x287A,0x28AC,0x28DE,0x291A,0x2956,0x297E,0x29BA,0x29EC,0x2A28,0x2A50,
	0x2AFA,0x2B22,0x2B9A,0x2BF4,0x2C3A,0x2CC6,0x2D11,0x2D39,0x2D7A,0x2DAC,
	0x2E1A,0x2E42,0x2E7E,0x2EBA,0x2F14,0x2F50,0x2F6E,0x2FFA,0x3022,0x309A,
	0x313A,0x319E,0x31C6,0x31E9,0x327A,0x3298,0x331A,0x332E,0x3374,0x33BA,
	0x3400,0x3450,0x3469,0x34D2,0x34FA,0x3522,0x359A,0x35EA,0x363A,0x3676,
	0x36BC,0x36DA,0x377A,0x37B1,0x381A,0x3842,0x386A,0x38BA,0x38EC,0x395A,
	0x39BE,0x39FA,0x3A22,0x3A5E,0x3A77,0x3A90,0x3A9A,0x3AF4,0x3B3A,0x3B62,
	0x3BC6,0x3C2F,0x3C7A,0x3C98,0x3D1A,0x3DBA,0x3E3C,0x3E5A,0x3EAA,0x3ED2,
	0x3EFA,0x3F22,0x3F7C,0x3F9A,0x3FF4,0x403B,0x40C7,0x4103,0x4121,0x417B,
	0x4199,0x41F3,0x421B,0x426B,0x429D,0x42BB,0x431F,0x435B,0x4397,0x43FB,
	0x442D,0x4469,0x449B,0x44F5,0x453B,0x4563,0x45DB,
	*/
	};
	//PAL-B/G NETHERLAND BroadCast -->TCPQ9091PD28L�� ���ĳ��� ���ļ� ���̺�.
	code unsigned short PALNETHERLANDAIR[72]={	// 2003.3.10 ������ FIX
	0x06CF,0x075B,0x07E7,0x10BB,0x1147,0x11D3,0x125F,0x12EB,0x1377,
	0x1402,0x148E,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x27DA,
	0x287A,0x291A,0x29BA,0x2A5A,0x2AFA,0x2B9A,0x2C3A,0x2CDA,0x2D7A,0x2E1A,
	0x2EBA,0x2F5A,0x2FFA,0x309A,0x313A,0x31DA,0x327A,0x331A,0x33BA,0x345A,
	0x34FA,0x359A,0x363A,0x36DA,0x377A,0x381A,0x38BA,0x395A,0x39FA,0x3A9A,
	0x3B3A,0x3BDA,0x3C7A,0x3D1A,0x3DBA,0x3E5A,0x3EFA,0x3F9A,0x403B,0x40DB,
	0x417B,0x421B,0x42BB,0x435B,0x43FB,0x449B,0x453B,0x45DB,0x0873,0x08FF,
	0x098B,0x0A17,0x0AA3

	/*
	0x075B,0x07FB,0x0FA3,0x102F,0x10CA,0x116A,0x120A,0x12AA,0x134A,0x13EA,
	0x1489,0x1529,0x15C9,0x1669,0x1709,0x17A9,0x1849,0x18E9,0x1989,0x2109,
	0x21A9,0x21E0,0x27DA,0x287A,0x291A,0x29BA,0x2A50,0x2AFA,0x2BA9,0x2C49,
	0x2CE9,0x2D89,0x2E29,0x2EC9,0x2F69,0x3009,0x30A9,0x3149,0x31E9,0x3289,
	0x3329,0x33C9,0x3469,0x3509,0x35A9,0x3649,0x36E9,0x3789,0x3829,0x38C9,
	0x3969,0x3A09,0x3AA9,0x3B49,0x3BE9,0x3C89,0x3D29,0x3DC9,0x3E69,0x3F09,
	0x3FA9,0x404A,0x40EA,0x418A,0x422A,0x42CA,
	*/
	};
	
	// ���� : 0x0000���� Define�Ǿ� �ִ� �κ��� ��ĳ�׽ÿ� Skip�� ��. --> Channel No ��Ȯ�ϰ� ��Ÿ����                                         
//// ���ؼ� Dummy Data�� ����Ͽ���. ���� ��쿡 Dummy Data�� 8�� �̹Ƿ� channel���� 60���� �ȴ�. ���ؼ� Dummy Data�� ����Ͽ���. ���� ��쿡
	
	//--------------------------------------------------------------------------
	//PAL-B/G GERMANY CableTV -->TCPQ9091PD28L�� ���ĳ��� ���ļ� ���̺�.
	code unsigned short PALGERMANYCATV[55]={		// 2003.1.14 ȭ���� FIX
	0x06CF,0x075B,0x07E7,0x0873,0x08FF,0x098B,0x0B43,0x0BCF,0x0C5B,0x0CE7,
	0x0D73,0x0DFF,0x0E8B,0x0F17,0x0FA3,0x102F,0x10BB,0x1147,0x11D3,0x125F,
	0x12EB,0x1377,0x1402,0x148E,0x151A,0x15A6,0x1632,0x16BE,0x174A,0x17D6,
	0x1862,0x18EE,0x197A,0x1A06,0x1ABA,0x1B5A,0x1BFA,0x1C9A,0x1D3A,0x1DDA,
	0x1E7A,0x1F1A,0x1FBA,0x205A,0x20FA,0x219A,0x223A,0x22DA,0x237A,0x241A,
	0x24BA,0x255A,0x25FA,0x269A,0x273A
	};
	//PAL-B/G GERMANY BroadCast -->TCPQ9091PD28L�� ���ĳ��� ���ļ� ���̺�.
	code unsigned short PALGERMANYAIR[68]={	// 2003.1.14 ȭ���� FIX
	0x06CF,0x075B,0x07E7,0x10BB,0x1147,0x11D3,0x125F,0x12EB,0x1377,0x1402,
	0x148E,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x27DA,
	0x287A,0x291A,0x29BA,0x2A5A,0x2AFA,0x2B9A,0x2C3A,0x2CDA,0x2D7A,0x2E1A,
	0x2EBA,0x2F5A,0x2FFA,0x309A,0x313A,0x31DA,0x327A,0x331A,0x33BA,0x345A,
	0x34FA,0x359A,0x363A,0x36DA,0x377A,0x381A,0x38BA,0x395A,0x39FA,0x3A9A,
	0x3B3A,0x3BDA,0x3C7A,0x3D1A,0x3DBA,0x3E5A,0x3EFA,0x3F9A,0x403B,0x40DB,
	0x417B,0x421B,0x42BB,0x435B,0x43FB,0x449B,0x453B,0x45DB
	};
		
	// ���� : 0x0000���� Define�Ǿ� �ִ� �κ��� ��ĳ�׽ÿ� Skip�� ��. --> Channel No ��Ȯ�ϰ� ��Ÿ����
	// ���ؼ� Dummy Data�� ����Ͽ���. ���� ��쿡 Dummy Data�� 8�� �̹Ƿ� channel���� 60���� �ȴ�.
	//--------------------------------------------------------------------------
	//PAL-B/G ITALY CableTV -->TCPQ9091PD28L�� ���ĳ��� ���ļ� ���̺�.
	code unsigned short PALITALYCATV[55]={	// 2003.1.14 ȭ���� FIX
	0x06CF,0x075B,0x07E7,0x0873,0x08FF,0x098B,0x0B43,0x0BCF,0x0C5B,0x0CE7,
	0x0D73,0x0DFF,0x0E8B,0x0F17,0x0FA3,0x102F,0x10BB,0x1147,0x11D3,0x125F,
	0x12EB,0x1377,0x1402,0x148E,0x151A,0x15A6,0x1632,0x16BE,0x174A,0x17D6,
	0x1862,0x18EE,0x197A,0x1A06,0x1ABA,0x1B5A,0x1BFA,0x1C9A,0x1D3A,0x1DDA,
	0x1E7A,0x1F1A,0x1FBA,0x205A,0x20FA,0x219A,0x223A,0x22DA,0x237A,0x241A,
	0x24BA,0x255A,0x25FA,0x269A,0x273A
	};
	//PAL-B/G ITALY BroadCast -->TCPQ9091PD28L�� ���ĳ��� ���ļ� ���̺�.
	code unsigned short PALITALYAIR[69]={	// 2003.1.14 ȭ���� FIX
	0x073D,0x07E7,0x0977,0x10BB,0x1165,0x1273,0x12C3,0x1377,0x1402,0x148E,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x27DA,0x287A,0x291A,0x29BA,0x2A5A,0x2AFA,0x2B9A,0x2C3A,0x2CDA,0x2D7A,
	0x2E1A,0x2EBA,0x2F5A,0x2FFA,0x309A,0x313A,0x31DA,0x327A,0x331A,0x33BA,
	0x345A,0x34FA,0x359A,0x363A,0x36DA,0x377A,0x381A,0x38BA,0x395A,0x39FA,
	0x3A9A,0x3B3A,0x3BDA,0x3C7A,0x3D1A,0x3DBA,0x3E5A,0x3EFA,0x3F9A,0x403B,
	0x40DB,0x417B,0x421B,0x42BB,0x435B,0x43FB,0x449B,0x453B,0x45DB
	};
	
	/////////////////////////////////////////////////////////////////////////////////
	//PAL-D/K Russia BroadCast --> TCPQ9091PD27D(T)�� ���ĳ��� ���ļ� ���̺�.
	code unsigned short	PAL_RUSSIA_TV[]=	//2004-09-15 +jwshin,+hyjeon
	{
/*		0x0587,0x0622,0x06C2,0x0742,0x07C2,0x0842,0x0882,0x0902,0x0972,	//0~9
		0x09E2,0x0A52,0x0AC2,0x0B32,0x0BA2,0x0C12,0x0C82,0x0CF2,0x0D62,0x0DE2,	//10~19
		0x0E62,0x0EE2,0x0F62,0x0FE2,0x1062,0x10E2,0x1152,0x11C2,0x1232,	//20~29
		0x12A2,0x1312,0x1382,0x13F2,0x1462,0x14D2,0x1562,0x15E2,0x1662,0x16E2,	//30~39
		0x1762,0x17E2,0x1862,0x18E2,0x1962,0x19E2,0x1A62,0x1AE2,0x1B62,0x1BE2,  //40~49
		0x1C62,0x1CE2,0x1D62,0x1DE2,0x1E62,0x1EE2,0x1F62,0x1FE2,0x2062,0x20E2,  //50~59
		0x2162,0x21E2,0x2262,0x22E2,0x2362,0x23E2,0x2462,0x24E2,0x2562,0x25E2,  //60~69
		0x2662,0x26E2,0x2762,0x27E2,0x2862,0x28E2,0x2962,0x29E2,0x2A62,0x2AE2,  //70~79
		0x2B62,0x2BE2,0x2C62,0x2CE2,0x2D62,0x2DE2,0x2E62,0x2EE2,0x2F62,0x2FE2,  //80~89
		0x3062,0x30E2,0x3162,0x31E2,0x3262,0x32E2,0x3362,0x33E2,0x3462,0x34E2,  //90~99
		0x3562,0x35E2,0x3662,0x36E2,0x3762,0x37E2 															//100~105 */
		
		0x0587,0x0622,0x0742,0x07C2,0x0842,0x0892,0x0962,0x09A2,0x0A12,0x0A82,	// 1 ~ 10
		0x0AF2,0x0B62,0x0BD7,0x0C42,0x0CC2,0x0D62,0x0DE2,0x0E62,0x0EE2,0x0F62,	// 11 ~ 20
		0x0FC2,0x1062,0x1122,0x1192,0x1202,0x1272,0x12E2,0x1352,0x13C2,0x1432,	// 21 ~ 30
		0x14A2,0x1512,0x1582,0x15F2,0x1662,0x16D2,0x1742,0x17B2,0x1822,0x1892,	// 31 ~ 40
		0x1902,0x1972,0x19E2,0x1A52,0x1AC2,0x1B32,0x1BA2,0x1C12,0x1C82,0x1CF2,	// 41 ~ 50
		0x1D62,0x1DD2,0x1E42,0x1EB2,0x1F22,0x1F92,0x1FE2,0x2062,0x20E2,0x2162,	// 51 ~ 60
		0x21E2,0x2262,0x22E2,0x2367,0x23E7,0x2467,0x24E2,0x2562,0x25E2,0x2662,	// 61 ~ 70
		0x26E2,0x2762,0x27E2,0x2862,0x28E2,0x2962,0x29E2,0x2A62,0x2AE2,0x2B62,	// 71 ~ 80
		0x2BE2,0x2C62,0x2CE2,0x2D62,0x2DE2,0x2E62,0x2EE2,0x2F62,0x2FE2,0x3062,	// 81 ~ 90
		0x30E2,0x3162,0x31E2,0x3262,0x32E2,0x3362,0x33E2,0x3462,0x34E2,0x3562,	// 91 ~ 100
		0x35E2,0x3662,0x36E2,0x3762,0x37E2 					// 101 ~ 105	
		
		
	};
	/////////////////////////////////////////////////////////////////////////////////
	
	
	// ���� : 0x0000���� Define�Ǿ� �ִ� �κ��� ��ĳ�׽ÿ� Skip�� ��. --> Channel No ��Ȯ�ϰ� ��Ÿ����
	// ���ؼ� Dummy Data�� ����Ͽ���. ���� ��쿡 Dummy Data�� 10�� �̹Ƿ� channel���� 59���� �ȴ�.
	//--------------------------------------------------------------------------
	//PAL-I UK CableTV -->TCPQ9091PD28L�� ���ĳ��� ���ļ� ���̺�.
	code unsigned short PALUKCATV[55]={	// 2003.1.14 ȭ���� FIX
	0x06CF,0x075B,0x07E7,0x0873,0x08FF,0x098B,0x0B43,0x0BCF,0x0C5B,0x0CE7,
	0x0D73,0x0DFF,0x0E8B,0x0F17,0x0FA3,0x102F,0x10BB,0x1147,0x11D3,0x125F,
	0x12EB,0x1377,0x1402,0x148E,0x151A,0x15A6,0x1632,0x16BE,0x174A,0x17D6,
	0x1862,0x18EE,0x197A,0x1A06,0x1ABA,0x1B5A,0x1BFA,0x1C9A,0x1D3A,0x1DDA,
	0x1E7A,0x1F1A,0x1FBA,0x205A,0x20FA,0x219A,0x223A,0x22DA,0x237A,0x241A,
	0x24BA,0x255A,0x25FA,0x269A,0x273A
	};
	//PAL-I UK BroadCast -->TCPQ9091PD28L�� ���ĳ��� ���ļ� ���̺�.
	code unsigned short PALUKAIR[68]={		// 2003.1.14 ȭ���� FIX
	0x06CF,0x075B,0x07E7,0x10BB,0x1147,0x11D3,0x125F,0x12EB,0x1377,0x1402,
	0x148E,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x27DA,
	0x287A,0x291A,0x29BA,0x2A5A,0x2AFA,0x2B9A,0x2C3A,0x2CDA,0x2D7A,0x2E1A,
	0x2EBA,0x2F5A,0x2FFA,0x309A,0x313A,0x31DA,0x327A,0x331A,0x33BA,0x345A,
	0x34FA,0x359A,0x363A,0x36DA,0x377A,0x381A,0x38BA,0x395A,0x39FA,0x3A9A,
	0x3B3A,0x3BDA,0x3C7A,0x3D1A,0x3DBA,0x3E5A,0x3EFA,0x3F9A,0x403B,0x40DB,
	0x417B,0x421B,0x42BB,0x435B,0x43FB,0x449B,0x453B,0x45DB
	};
	
	// ���� : 0x0000���� Define�Ǿ� �ִ� �κ��� ��ĳ�׽ÿ� Skip�� ��. --> Channel No ��Ȯ�ϰ� ��Ÿ����
	// ���ؼ� Dummy Data�� ����Ͽ���. ���� ��쿡 Dummy Data�� 8�� �̹Ƿ� channel���� 60���� �ȴ�.


	//--------------------------------------------------------------------------
	//SECAM-L FRNACE CableTV -->TCPQ9091PD28L�� ���ĳ��� ���ļ� ���̺�.
	code unsigned short SECAMFRNACECATV[41]={	// 2003.1.14 ȭ���� FIX
	0x0B43,0x0BCF,0x0C5B,0x0CE7,0x0D73,0x0DFF,0x0E8B,0x0F17,0x0FA3,0x102F,
	0x151A,0x15A6,0x1632,0x16BE,0x174A,0x17D6,0x1862,0x18EE,0x197A,0x1A06,
	0x1ABA,0x1B5A,0x1BFA,0x1C9A,0x1D3A,0x1DDA,0x1E7A,0x1F1A,0x1FBA,0x205A,
	0x20FA,0x219A,0x223A,0x22DA,0x237A,0x241A,0x24BA,0x255A,0x25FA,0x269A,
	0x273A
	
	//0x27DA,0x287A,0x291A,0x29BA,0x2A5A,0x2AFA,0x2B9A,0x2C3A,0x2CDA,0x2D7A,
	//0x2E1A,0x2EBA,0x2F5A,0x2FFA,0x309A,0x313A,0x31DA,0x327A,0x331A,0x33BA,
	//0x345A,0x34FA,0x359A,0x363A,0x36DA,0x377A,0x381A,0x38BA,0x395A,0x39FA,
	//0x3A9A,0x3B3A,0x3BDA,0x3C7A,0x3D1A,0x3DBA,0x3E5A,0x3EFA,0x3F9A,0x403B,
	//0x40DB,0x417B,0x421B,0x42BB,0x435B,0x43FB,0x449B,0x453B,0x45DB,
	
	// 1�� TEST (SOUND CARRIER���� ������.) -> ä�� ���̺� ����
	//0x2776,0x2816,0x28B6,0x2956,0x29F6,0x2A96,0x2B36,0x2BD6,0x2C76,0x2D16
	//,0x2DB6,0x2E56,0x2EF6,0x2F96,0x3036,0x30D6,0x3176,0x3216,0x32B6,0x3356
	//,0x33F6,0x3496,0x3536,0x35D6,0x3676,0x3716,0x37B6,0x3856,0x38F6,0x3996
	//,0x3A36,0x3AD6,0x3B76,0x3C16,0x3CB6,0x3D56,0x3DF6,0x3E96,0x3F36,0x3FD6
	//,0x4077,0x4117,0x41B7,0x4257,0x42F7,0x4397,0x4437,0x44D7,0x4577,


	// 1�� TEST (SOUND CARRIER���� ������.)
	//0x11FB,0x1287,0x1313,0x139F,0x142A,0x14B6,0x1542,0x15CE,0x165A,0x16E6,
	//0x1772,0x17FE,0x188A,0x1916,0x19A2,0x1A56,0x1AF6,0x1B96,0x1C36,0x1CD6,
	//0x1D76,0x1E16,0x1EB6,0x1F56,0x1FF6,0x2096,0x2136,0x21D6,0x2276,0x2316,
	//0x23B6,0x2456,0x24F6,0x2596,0x2636,0x26D6,

	//0x125F,0x12EB,0x1377,0x1402,0x148E,0x151A,0x15A6,0x1632,0x16BE,0x174A,
	//0x17D6,0x1862,0x18EE,0x197A,0x1A06,0x1ABA,0x1B5A,0x1BFA,0x1C9A,0x1D3A,
	//0x1DDA,0x1E7A,0x1F1A,0x1FBA,0x205A,0x20FA,0x219A,0x223A,0x22DA,0x237A,
	//0x241A,0x24BA,0x255A,0x25FA,0x269A,0x273A,
	};
	code unsigned short SECAMFRNACEAIR[69]={		// 2003.1.14 ȭ���� FIX
	// 1�� TEST (SOUND CARRIER���� ������.) -> ä�� ���̺� ����
	0x0661,0x0701,0x0760,0x07A1,0x10CA,0x116A,0x120A,0x12AA,0x134A,0x13EA,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x27DA,0x287A,0x291A,0x29BA,0x2A5A,0x2AFA,0x2B9A,0x2C3A,0x2CDA,0x2D7A,
	0x2E1A,0x2EBA,0x2F5A,0x2FFA,0x309A,0x313A,0x31DA,0x327A,0x331A,0x33BA,
	0x345A,0x34FA,0x359A,0x363A,0x36DA,0x377A,0x381A,0x38BA,0x395A,0x39FA,
	0x3A9A,0x3B3A,0x3BDA,0x3C7A,0x3D1A,0x3DBA,0x3E5A,0x3EFA,0x3F9A,0x403B,
	0x40DB,0x417B,0x421B,0x42BB,0x435B,0x43FB,0x449B,0x453B,0x45DB
	
	//0x0661,0x0701,0x0760,0x07A1,0x0C29,0x0D0F,0x0E09,0x0EF9,0x0FE9,0x10CA
	//,0x116A,0x11C9,0x120A,0x12AA,0x134A,0x13A9,0x13EA,0x1498,0x1588,0x1678
	//,0x1768,0x1858,0x1948,0x1A38,

	//0x0661,0x0701,0x0760,0x07A1,0x0BC5,0x0CAB,0x0DA5,0x0E95,0x0F85,0x1066
	//,0x1075,0x1106,0x1165,0x11A6,0x1246,0x1255,0x12E6,0x1345,0x1386,0x1434
	//,0x1524,0x1614,0x1704,0x17F4,0x18E4,0x19D4,

	// 1�� TEST (SOUND CARRIER���� ������.)
	//0x0661,0x0701,0x0760,0x07A1,0x0BC5,0x0CAB,0x0DA5,0x0E95,0x0F85,0x1066,
	//0x1075,0x1106,0x1165,0x11A6,0x1246,0x1255,0x1345,0x12E6,0x1386,0x1434,

	//0x06C5,0x0765,0x07C4,0x0805,0x0C29,0x0D0F,0x0E09,0x0EF9,0x0FE9,0x10CA,
	//0x10D9,0x116A,0x11C9,0x120A,0x12AA,0x12B9,0x13A9,0x134A,0x13EA,0x1498,
	};
	

	//--------------------------------------------------------------------------
	//SECAM-D/K RUSSIA CableTV -->TCPQ9091PD28L�� ���ĳ��� ���ļ� ���̺�.
	code unsigned short SECAMRUSSIACATV[41]={	// 2003.1.14 ȭ���� FIX
	0x0B43,0x0BBB,0x0C5B,0x0CFB,0x0D9B,0x0E3B,0x0EDB,0x0F7B,0x101B,0x0000,
	0x0000,0x151A,0x15BA,0x165A,0x16FA,0x179A,0x183A,0x18DA,0x197A,0x1A06,
	0x1ABA,0x1B5A,0x1BFA,0x1C9A,0x1D3A,0x1DDA,0x1E7A,0x1F1A,0x1FBA,0x205A,
	0x20FA,0x219A,0x223A,0x22DA,0x237A,0x241A,0x24BA,0x255A,0x25FA,0x269A,
	0x273A
	};
	// ���� : 0x0000���� Define�Ǿ� �ִ� �κ��� ��ĳ�׽ÿ� Skip�� ��. --> Channel No ��Ȯ�ϰ� ��Ÿ����
	// ���ؼ� Dummy Data�� ����Ͽ���. ���� ��쿡 Dummy Data�� 2�� �̹Ƿ� channel���� 39���� �ȴ�.
	//SECAM-D/K RUSSIA BroadCast -->TCPQ9091PD28L�� ���ĳ��� ���ļ� ���̺�.
	code unsigned short SECAMRUSSIAAIR[57]={		// 2003.1.14 ȭ���� FIX
	0x06ED,0x07AB,0x0913,0x09B3,0x0A53,0x10BB,0x115B,0x11FB,0x129B,0x133B,
	0x13DB,0x147A,0x27DA,0x287A,0x291A,0x29BA,0x2A5A,0x2AFA,0x2B9A,0x2C3A,
	0x2CDA,0x2D7A,0x2E1A,0x2EBA,0x327A,0x331A,0x33BA,0x345A,0x34FA,0x359A,
	0x363A,0x36DA,0x377A,0x381A,0x38BA,0x396E,0x39FA,0x3A9A,0x3B3A,0x3BDA,
	0x3C7A,0x3D1A,0x3DBA,0x3E5A,0x3EFA,0x3F9A,0x403B,0x40DB,0x4167,0x421B,
	0x42BB,0x435B,0x43FB,0x449B,0x453B,0x45DB,0x467B,
	};
	
	//#ifdef TunerRefDiv512 (Freq.step:62.5KHz)
	//--------------------------------------------------------------------
	//2004-01-15 made by thkim
	#if 0	//2004-03-17
	//PAL-D/K CHINA [CH1~57] ���ļ� ���̺�.
	code unsigned short PAL_CHINA_TV[]={			// 2004-01-15
	/*0x0500,*/0x058A,0x060A,0x068A,0x0742,0x07C2,0x0CF2,0x0D72,0x0DF2,0x0E72,
	0x0EF2,0x0F72,0x0FF2,0x1FE2,0x2062,0x20E2,0x2142,0x21E2,0x2262,0x22E2,
	0x2362,0x23E2,0x2462,0x24E2,0x2562,0x2862,0x28E2,0x2962,0x29E2,0x2A62,
	0x2AE2,0x2B62,0x2BE2,0x2C62,0x2CE2,0x2D62,0x2DE2,0x2E62,0x2EE2,0x2F62,
	0x2FE2,0x3062,0x30E2,0x3162,0x31E2,0x3262,0x32E2,0x3362,0x33E2,0x3462,
	0x34E2,0x3562,0x35E2,0x3662,0x36E2,0x3762,0x37E2,0x3862
	};
	#else
	//PAL-D/K CHINA CableTV -->TCPQ9091PD27D(T)�� ���ĳ��� ���ļ� ���̺�.
	code unsigned short PAL_CHINA_TV[]={			// 2004-01-15
	/*0x0500,*/0x058A,0x060A,0x068A,0x0742,0x07C2,0x0842,0x0972,0x09F2,0x0A72,
	0x0AF2,0x0B72,0x0BF2,0x0C72,0x0CF2,0x0D72,0x0DF2,0x0E72,0x0EF2,0x0F72,
	0x0FF2,0x1072,0x10F2,0x1172,0x11F2,0x1272,0x12F2,0x1372,0x13F2,0x1472,
	0x14F2,0x1572,0x15F2,0x1672,0x16F2,0x1772,0x17F2,0x1872,0x18F2,0x1972,
	0x19F2,0x1A72,0x1AF2,0x1B72,0x1BF2,0x1C72,0x1CF2,0x1D72,0x1DF2,0x1E72,
	0x1EF2,0x1FE2,0x2062,0x20E2,0x2162,0x21E2,0x2262,0x22E2,0x2362,0x23E2,
	0x2462,0x24E2,0x2562,0x25E2,0x2662,0x26E2,0x2762,0x27E2,0x2862,0x28E2,
	0x2962,0x29E2,0x2A62,0x2AE2,0x2B62,0x2BE2,0x2C62,0x2CE2,0x2D62,0x2DE2,
	0x2E62,0x2EE2,0x2F62,0x2FE2,0x3062,0x30E2,0x3162,0x31E2,0x3262,0x32E2,
	0x3362,0x33E2,0x3462,0x34E2,0x3562,0x35E2,0x3662,0x36E2,0x3762,0x37E2,
	0x3862
	//0x38E2,0x3962,0x39E2,0x3a62,0x3aE2,0x3b62,0x3bE2,0x3c62,0x3cE2,0x3d62,
	//0x3dE2////	/* 871.25 ~ 951.25 MHz 11�� Freq. �߰� 2004-05-13 */
	// Ʃ�ʿ��� 895.25�̻��� ������..�׷��� �������.
	};
	#endif
	//--------------------------------------------------------------------
	//#endif
	
//--------------------------------------------------------------------------
#endif
//--------------------------------------------------------------------------



//--------------------------------------------------------------------------
#if defined(USE_NTSCtuner)	//----------------------------------------------
//--------------------------------------------------------------------------
// ������ ä�� ���̺��� ���� Start Address ����.(Cable-TV, Air-TV)
code unsigned short *CATV_TAB[]={
///		0					1				2					3
	NTSCKORCATV,	NTSCJPNCATV,		SECAMFRNACECATV,	PALGERMANYCATV,
///		4					5				6					7
	PALITALYCATV,	PALNETHERLANDCATV,	SECAMRUSSIACATV,	PALUKCATV,  
};

code unsigned short *AIR_TAB[]={
///		0					1				2					3
	NTSCKORAIR,			NTSCJPNAIR,		SECAMFRNACEAIR,		PALGERMANYAIR,		
///		4					5				6					7
	PALITALYAIR,		PALNETHERLANDAIR,	SECAMRUSSIAAIR,		PALUKAIR,		
};
//----------------------------------------------------
// Country������ AFT Range������ �����ϱ� ���� ���̺�.
code BYTE  AftRangeTable[]=	{	//AftRangeTable[xEEPROMBuffer[SystemCountry]];
//---AFT Range -----------------country---------country code---AFT Range---
		45,					//KOREA(ntsc)				0  		+-2.5Mhz		// 05/08������. 2.5 ->1.5Mhz by LKE
		45,					//USA(ntsc)				1  		+-2.5Mhz		// 05/08������. 2.5 ->1.5Mhz by LKE
// Korea/Usa�� ���� ���� �ٰ�: Air�� ��쿡 Search�ÿ� 2Mhz�� ����� �����Ͱ� ������, �̰͵��� ��κ��� Catv�� Center
// ���ļ��� ���ϴ� ����. �׷��� �����ϰ� AFT RangeŰ�� �ʿ��� AFT Range�� ������.
		45,					//Japan(ntsc)				2  		+-2.5Mhz
		
		25,					//France(SECAL-L)			3  		+-2.5Mhz
		25,					//Germany(PAL-B/G)		4  		+-2.5Mhz
		25,					//Italy(PAL-B/G)			5  		+-2.5Mhz
		
		70,					//NETHERLAND(PAL-B/G)	6  		+-3.25Mhz
		25,					//Russia(SECAM-D/K)		7  		+-2.5Mhz
		25,					//UK(PAL-I)				8  		+-2.5Mhz
};
//--------------------------------------------------------------------------
// ��ä�� �ý��ۿ� ���� ��üChannel ��, Max channel, Min channel �� ���� Define.

// CableTV�� ���� Channel Table System Define
code BYTE  CatvLimitTable[]=	{
   //ä�μ�,Catv_Max,Catv_Min 		//	ChannelSystem  		Number
	//125,		125,		1,			// 	KOREA/USA		  	0
	124,		125,		2,			// 	KOREA/USA		  	0
	63,  		63,		1,			// 	JAPAN			    	1
	
	41, 		41,		1,			//    France(SECAL-L)	    	2	
	
	55,			56,		2,			//	GERMANY(PAL-B/G)	    	3
	55,  		56,		2,			//	ITALY(PAL-B/G)	    	4

   	41, 		41,		1,			//    NETHERLAND(PAL-B/G) 	5	
	//127, 	127,		1,			//    NETHERLAND(PAL-B/G) 	5	

	39, 		98,		58,			//    Russia(SECAM-D/K)	    	6	
	55,			56,		2,			//  	UK(PAL-I)			    	7
	//55,		56,		2,	//HongKong(PAL-I)	5
	//37, 		37,		1,	//China(PAL-D/K)	   	2	
	};

// BoradCast�� ���� Channel Table System Define  
code BYTE  TvLimitTable[]=	{		// 1��16�� Fix
// ä�μ�,TV_Max,TV_Min			//	ChannelSystem  		Number
	68,		69,		2,			// 	KOREA/USA		  	0
	62,		62,		1,			// 	JAPAN			  	1
	
	59, 	69,		1,			//    France(SECAL-L)	  	2	
	
	60,		69,		2,			//	GERMANY(PAL-B/G)	  	3   ä�μ� --> dummy 8�� ������ ��������.
	59,		69,		1,			//	ITALY(PAL-B/G)	  	4   ä�μ� --> dummy 10�� ������ ��������.
#if(AUTO_SETUPDEBUG==0)	
	65, 	73,		2,			//   NETHERLAND(PAL-B/G)	5	ä�μ� --> dummy 7�� ������ ��������.
	//66, 	66,		1,			//   NETHERLAND(PAL-B/G)	5	
#else
	72, 	73,		2,			//   NETHERLAND(PAL-B/G)	5	
#endif

	57, 	57,		1,			//    Russia(SECAM-D/K)	  	6	
	60,		69,		2,			//  	UK(PAL-I)			  	7
	//102,	102,	1,	//  	HongKong(PAL-I)	  5
	///57,	57,		1,	//    China(PAL-D/K)	  2	
	};

code BYTE CountryToChannel[]={		// 1��16�� Fix
//---Limit Table�� ���� offset-----country-------country code
		0,					//KOREA(ntsc)				0
		0,					//USA(ntsc)				1
		1,					//Japan(ntsc)				2
		
		2,					//France(SECAL-L)			3
		3,					//Germany(PAL-B/G)		4
		4,					//Italy(PAL-B/G)			5
		
		5,					//NETHERLAND(PAL-B/G)	6
		6,					//Russia(SECAM-D/K)		7
		7,					//UK(PAL-I)				8
};	
//--------------------------------------------------------------------------
#else	//-----------------------------------------------------------------
//--------------------------------------------------------------------------
// ������ ä�� ���̺��� ���� Start Address ����.(Cable-TV, Air-TV)
code unsigned short *CATV_TAB[]={
///		0					1				2					3
	PAL_CHINA_TV,	PAL_RUSSIA_TV,		SECAMFRNACECATV,	PALGERMANYCATV,
///		4					5				6					7
	PALITALYCATV,	PALNETHERLANDCATV,	SECAMRUSSIACATV,	PALUKCATV,  
};

code unsigned short *AIR_TAB[]={
///		0					1				2					3
	PAL_CHINA_TV,			PAL_RUSSIA_TV,		SECAMFRNACEAIR,		PALGERMANYAIR,		
///		4					5				6					7
	PALITALYAIR,		PALNETHERLANDAIR,	SECAMRUSSIAAIR,		PALUKAIR,		
};
//----------------------------------------------------
// Country������ AFT Range������ �����ϱ� ���� ���̺�.
code BYTE  AftRangeTable[]=	{	//AftRangeTable[xEEPROMBuffer[SystemCountry]];
//---AFT Range -----------------country---------country code---AFT Range---
		25,					//china				0  		+-2.5Mhz
		25,					//malaysia		1  		+-2.5Mhz
		25,					//Japan(ntsc)				2  		+-2.5Mhz
		
		25,					//France(SECAL-L)			3  		+-2.5Mhz
		25,					//Germany(PAL-B/G)		4  		+-2.5Mhz
		25,					//Italy(PAL-B/G)			5  		+-2.5Mhz
		
		70,					//NETHERLAND(PAL-B/G)	6  		+-3.25Mhz
		25,					//Russia(SECAM-D/K)		7  		+-2.5Mhz
		25,					//UK(PAL-I)				8  		+-2.5Mhz
};
//--------------------------------------------------------------------------
// ��ä�� �ý��ۿ� ���� ��üChannel ��, Max channel, Min channel �� ���� Define.

// CableTV�� ���� Channel Table System Define
code BYTE  CatvLimitTable[]=	{
   //ä�μ�,Catv_Max,Catv_Min 		//	ChannelSystem  		Number
	100,		100,		1,			//CHINA (PAL D/K)						0
	105,		105,		1,			//Russia (PAL D/K)				1
	
	41, 		41,		1,			//    France(SECAL-L)	    	2	
	
	55,			56,		2,			//	GERMANY(PAL-B/G)	    	3
	55,  		56,		2,			//	ITALY(PAL-B/G)	    	4

   	41, 		41,		1,			//    NETHERLAND(PAL-B/G) 	5	
	//127, 	127,		1,			//    NETHERLAND(PAL-B/G) 	5	

	39, 		98,		58,			//    Russia(SECAM-D/K)	    	6	
	55,			56,		2,			//  	UK(PAL-I)			    	7
	//55,		56,		2,	//HongKong(PAL-I)	5
	//37, 		37,		1,	//China(PAL-D/K)	   	2	
	};

// BoradCast�� ���� Channel Table System Define  
code BYTE  TvLimitTable[]=	{		// 1��16�� Fix
// ä�μ�,TV_Max,TV_Min			//	ChannelSystem  		Number
	//57,		57,		1,			// 	CHINA		  	0
	100,		100,		1,			//CHINA (PAL D/K)						0
	105,		105,		1,			//Russia (PAL D/K)				1

	59, 	69,		1,			//    France(SECAL-L)	  	2	
	
	60,		69,		2,			//	GERMANY(PAL-B/G)	  	3   ä�μ� --> dummy 8�� ������ ��������.
	59,		69,		1,			//	ITALY(PAL-B/G)	  	4   ä�μ� --> dummy 10�� ������ ��������.
#if(AUTO_SETUPDEBUG==0)	
	65, 	73,		2,			//   NETHERLAND(PAL-B/G)	5	ä�μ� --> dummy 7�� ������ ��������.
	//66, 	66,		1,			//   NETHERLAND(PAL-B/G)	5	
#else
	72, 	73,		2,			//   NETHERLAND(PAL-B/G)	5	
#endif

	57, 	57,		1,			//    Russia(SECAM-D/K)	  	6	
	60,		69,		2,			//  	UK(PAL-I)			  	7
	//102,	102,	1,	//  	HongKong(PAL-I)	  5
	///57,	57,		1,	//    China(PAL-D/K)	  2	
	};

code BYTE CountryToChannel[]={		// 1��16�� Fix
//---Limit Table�� ���� offset-----country-------country code
		0,					//CHINA (PAL D/K)						0
		1,					//malaysia (PAL B/G)				1
		0,					//CHINApal			2
		
		2,					//France(SECAL-L)		3
		3,					//Germany(PAL-B/G)		4
		4,					//Italy(PAL-B/G)		5
		
		5,					//NETHERLAND(PAL-B/G)	6
		6,					//Russia(SECAM-D/K)		7
		7,					//UK(PAL-I)				8
};	
//-----------------------------------------------------------------------------
#endif	//---------------------------------------------------------------------
//-----------------------------------------------------------------------------

//#if (NTSC_COUNTRY==1)
//xdata BYTE		TV_MIN;	// Channle Table�� Min Channel Number. 	//1��16��
//xdata BYTE		CATV_MIN;	// Channle Table�� Min Channel Number.  	//1��16��
//#endif



void TunnerInitialize()
{
	TunerTest();
	ATFEnable=0;	
	ChannelSel(xEEPROMBuffer[CurrentChannel]);	// Prog No�� �̿��Ͽ� --> Tunner�� �����Ѵ�.
	ATFEnable=1;
	
	#if((NTSC_COUNTRY==1)||(AUTO_SETUPDEBUG==1))
//		TV_MIN=TvLimitTable[3*CountryToChannel[xEEPROMBuffer[SystemCountry]]+2];	// Channle Table�� Min Channel Number. 	//1��16��
//		CATV_MIN=CatvLimitTable[3*CountryToChannel[xEEPROMBuffer[SystemCountry]]+2]	;	// Channle Table�� Min Channel Number.  	//1��16��
	#endif
}

void TVParameterInit()
{
	#if(NTSC_COUNTRY==1)
	//if(ColorSystem&NTSC) {	// NTSC
/*		AntenaFlag=xEEPROMBuffer[Antena];
		if(AntenaFlag) {
			CHANNEL_LIMIT=CatvLimitTable[3*CountryToChannel[xEEPROMBuffer[SystemCountry]]+0];	// CATV Total Channel �� Read
			CHANNEL_MAX=CatvLimitTable[3*CountryToChannel[xEEPROMBuffer[SystemCountry]]+1];
			CHANNEL_MIN=CatvLimitTable[3*CountryToChannel[xEEPROMBuffer[SystemCountry]]+2];			
		}
		else  {
			CHANNEL_LIMIT=TvLimitTable[3*CountryToChannel[xEEPROMBuffer[SystemCountry]]+0];			
			CHANNEL_MAX=TvLimitTable[3*CountryToChannel[xEEPROMBuffer[SystemCountry]]+1];
			CHANNEL_MIN=TvLimitTable[3*CountryToChannel[xEEPROMBuffer[SystemCountry]]+2];						
		} */  // Code Size�� ���� Routine Remark... +jwshin 040813

	#else
	//pal
		CHANNEL_LIMIT=CatvLimitTable[3*CountryToChannel[xEEPROMBuffer[SystemCountry]]+0];	//channel ��
		CHANNEL_MAX=CatvLimitTable[3*CountryToChannel[xEEPROMBuffer[SystemCountry]]+1];		//channel max
		CHANNEL_MIN=CatvLimitTable[3*CountryToChannel[xEEPROMBuffer[SystemCountry]]+2];		//channel min
	#endif
}

// by LKE 2.14
// OSD�޴����� ����ϰ�, IR Keyó�������� �����.
void CatvAirSelection(bit Selection)
{
	if(Selection==AntenaFlag) return;
	
	Mute_SoundOff;

		
	if(!Selection)
	{		// Catv --> Air��ȯ.
		AntenaFlag=(bit)0;
		#if((NTSC_COUNTRY==1)||(AUTO_SETUPDEBUG==1))
		CHANNEL_LIMIT=TvLimitTable[3*CountryToChannel[xEEPROMBuffer[SystemCountry]]+0];			
		CHANNEL_MAX=TvLimitTable[3*CountryToChannel[xEEPROMBuffer[SystemCountry]]+1];
		CHANNEL_MIN=TvLimitTable[3*CountryToChannel[xEEPROMBuffer[SystemCountry]]+2];		
		
		if(CHANNEL_MAX < xEEPROMBuffer[CurrentChannel]+CHANNEL_MIN) {xEEPROMBuffer[CurrentChannel]=0;}
		#endif
	}
	else
	{	 	// Air --> Catv��ȯ.
		AntenaFlag=(bit)1;
		#if((NTSC_COUNTRY==1)||(AUTO_SETUPDEBUG==1))
		CHANNEL_LIMIT=CatvLimitTable[3*CountryToChannel[xEEPROMBuffer[SystemCountry]]+0];	// CATV Total Channel �� Read
		CHANNEL_MAX=CatvLimitTable[3*CountryToChannel[xEEPROMBuffer[SystemCountry]]+1];
		CHANNEL_MIN=CatvLimitTable[3*CountryToChannel[xEEPROMBuffer[SystemCountry]]+2];
		#endif			
	}

	TunerProcessing	=2;
	
	EepromSetQue(Antena_adr, AntenaFlag);

	if(!IRMuteFlag)  Mute_SoundOn;//PutVolume(TRUE);
}


// ���õ� ä�θ��� �ùٸ��� ���õǾ������� üũ�ϰ� �����Ѵ�. 
//  1.ä�� ������ ��� ��� üũ :(�������۸��� ���Ѵ�.)
//	  Min���� ���� ��� : Min Channel�� fix
//     Max���� ū ��� :  Max Channel�� fix
//  2. 1�ǰ����� ��ģ �Ŀ� ����� ä��Number�� Auto Setup�ÿ� memory�� ����� ä�������� üũ�Ѵ�.
//     ����� ä���� ���  :  channel selection�� ���ϰ� --> channel�� �������� ������� ǥ��.
//     ����� ä���� �ƴѰ�� : channel selection�� ���ϰ� --> channel�� ��������� ǥ��.
/*  memory save  2003.6.3
void CheckChannelView(void){
	xBYTE tmp;
	xBYTE	TV_Max,CATV_Max,TV_Total,CATV_Total;
	
	tmp=IRDigitValue;
	//---------------ä�� ������ ��� ��� üũ�� ���ں����� ���Ѵ�.---------------
		TV_Max=TvLimitTable[3*CountryToChannel[xEEPROMBuffer[SystemCountry]]+1];		// max	// Air-TV
//		TV_MIN=TvLimitTable[3*CountryToChannel[xEEPROMBuffer[SystemCountry]]+2];		// min
		TV_Total=TvLimitTable[3*CountryToChannel[xEEPROMBuffer[SystemCountry]]+0];		// total	// Air-TV

		CATV_Max=CatvLimitTable[3*CountryToChannel[xEEPROMBuffer[SystemCountry]]+1];	// max	// CATV  
//		CATV_MIN=CatvLimitTable[3*CountryToChannel[xEEPROMBuffer[SystemCountry]]+2];	// min	
		CATV_Total=CatvLimitTable[3*CountryToChannel[xEEPROMBuffer[SystemCountry]]+0];	// total	// CATV  

	tmp=xEEPROMBuffer[CurrentChannel];	// 	// PreChannel������ ���ؼ� ���.	
#if((NTSC_COUNTRY==1)||(AUTO_SETUPDEBUG==1))
		// ntsc
		if(AntenaFlag==ANTENA_AIR){		// Air�� ��� ä�� ����
			if(IRDigitValue >= TV_Max) xEEPROMBuffer[CurrentChannel]=TV_Total-1;	// �̸� Min�� �����Ѵ�.		
			else if(IRDigitValue <= TV_MIN) xEEPROMBuffer[CurrentChannel]=0;
			else xEEPROMBuffer[CurrentChannel]=IRDigitValue-TV_MIN;
		}
		else{	// CATV�� ��� ä�� ����
			if(IRDigitValue >= CATV_Max) xEEPROMBuffer[CurrentChannel]=CATV_Total-1;		
			else if(IRDigitValue <= CATV_MIN) xEEPROMBuffer[CurrentChannel]=0;			
			else xEEPROMBuffer[CurrentChannel]=IRDigitValue-CATV_MIN;
		}
		xEEPROMBuffer[PreChannel]=tmp;		// PreChannel����.	
		EepromSetQue(CurrentChannel_adr,xEEPROMBuffer[CurrentChannel]);
		IRDigitValue=0x00;		// IRDigitValue�� ä�� ������ �ʱ�ȭ�Ѵ�.
#else	// PAL-Multi
			if(IRDigitValue > 99) xEEPROMBuffer[CurrentChannel]=99;		
			else if(IRDigitValue == 0) xEEPROMBuffer[CurrentChannel]=99;			
			else xEEPROMBuffer[CurrentChannel]=IRDigitValue-1;
			xEEPROMBuffer[PreChannel]=tmp;		// PreChannel����.	
			EepromSetQue(CurrentChannel_adr,xEEPROMBuffer[CurrentChannel]);
			IRDigitValue=0x00;		// IRDigitValue�� ä�� ������ �ʱ�ȭ�Ѵ�.
#endif
	
	//---------------ä�μ����� OSD Display---------------
	Mute_SoundOff;//PutVolume(FALSE);
	//LCDMute(0,1);//(1,0) -->  background color=Blue ,	free running mode�� osd�� ���� data�� mute��Ų��.
	ChannelSel(xEEPROMBuffer[CurrentChannel]);	
	if(CheckChMask(xEEPROMBuffer[CurrentChannel])==0) {	// Enable��  chanel�� Display// test bit=0���� �� ��� ������ �־ 1�� ������. by LKE 4/15  
		//if(ch >= CHANNELMEMORYMAX)  xEEPROMBuffer[CurrentChannel]=CHANNELMEMORYMAX-1; //channel memory�� ����� ���� ����Ʈ.
//youngdo 2003.5.28		ShowOSDChannel(CheckChCATV(xEEPROMBuffer[CurrentChannel]),GetRealChannel(xEEPROMBuffer[CurrentChannel]),1,fGREEN);	// OSD Channel Display
	}
	else{	// Disable��  chanel�� Display	// test bit=0���� �� ��� ������ �־ 1�� ������. by LKE 4/15  
		//if(ch >= CHANNELMEMORYMAX)  xEEPROMBuffer[CurrentChannel]=CHANNELMEMORYMAX-1; //channel memory�� ����� ���� ����Ʈ.	
//youngdo 2003.5.28		ShowOSDChannel(CheckChCATV(xEEPROMBuffer[CurrentChannel]),GetRealChannel(xEEPROMBuffer[CurrentChannel]),1,fYELLOW);	// OSD Channel Display
	}
	///SyncFlag=0;
	//CheckTVSignal(5);

	//LCDMuteOff();	// Mute Off	
	if(!IRMuteFlag) Mute_SoundOn; //PutVolume(TRUE);
//	OsdTmr=2;
}
*/


#define DecoderStableTime 25 // 2.15 -->25 fix by LKE
//#define DecoderStableTime2 25	//25->10			 // 2.18 -->25 fix by LKE

/*  memory save  2003.6.3
bit  ExitCondionCheck(bit NtscCable)	{	
		bit tmp;

//youngdo 2003.5.28		KeyScan();
		if(KEY_value==MenuKey || KEY_value==PowerKey) tmp=1; // ȭ���� �μ����� ���� ���� �ϱ� ���ؼ� ����. 2.24
		else tmp=0;

		if(tmp){		
			AntenaFlag=NtscCable;
//			KEY_value=MK_MENU;
			CheckTVSignal(5);	
			if(!IRMuteFlag)Mute_SoundOn;
		}
		
		return tmp;
	
}
*/

/*
void TvDataDump(void){
	WORD testcount,tempeepaddr;
	BYTE ss;

	ss=0;

	for(testcount=0; testcount<100; testcount++){
		printf(" %04d ", (WORD)EEPROM_Read(ep_ProgStart+testcount));
		if(++ss == 10){ss=0; printf("\r\n");}

	}
	
	ss=0;
	for(testcount=0; testcount<128; testcount++){
		tempeepaddr=ep_ChannelStartAir+testcount*2;		
		if(++ss == 5){ss=0; }
	}
	
		ss=0;

	for(testcount=0; testcount<128; testcount++){
		tempeepaddr=ep_ChannelStartCatv+testcount*2;		
		if(++ss == 5){ss=0; }
	}		
}

*/

// ���� ���̺� ������, Air(0)/Catv(1) �� �Ű������� �Ѱܹ޾Ƽ� Nest Channel�� �̸� �����ϴ� ����� �����Ѵ�.
/*  memory save  2003.6.3
	Bool NextChannelFreqSet(BYTE ChTblOffset, Bool CaAir){
	xdata BYTE	Ch_Total, Ch_Max, Ch_Min;
	xdata BYTE i;
	xdata WORD TDivider;
  	xdata unsigned short *p;
  	Bool TVSignalQaulity=0;
  	
	//---------�̺κп��� ���� ��ȣ��ǰ���� üũ�Ѵ�.

	//-----------------------------------


	if(CaAir==0){		//Air�� ��� 
		Ch_Total=TvLimitTable[3*CountryToChannel[xEEPROMBuffer[SystemCountry]]+0];		// total	// Air-TV
		Ch_Max=TvLimitTable[3*CountryToChannel[xEEPROMBuffer[SystemCountry]]+1];		// max
		Ch_Min=TvLimitTable[3*CountryToChannel[xEEPROMBuffer[SystemCountry]]+2];		// min
	}
	else{			// Catv�� ���.
		Ch_Total=CatvLimitTable[3*CountryToChannel[xEEPROMBuffer[SystemCountry]]+0];	// total	// CATV  
		Ch_Max=CatvLimitTable[3*CountryToChannel[xEEPROMBuffer[SystemCountry]]+1];	// max
		Ch_Min=CatvLimitTable[3*CountryToChannel[xEEPROMBuffer[SystemCountry]]+2];	// min
	}

	for(i=ChTblOffset; i < (Ch_Max-Ch_Min+1); i++){
			if( i == ChTblOffset ) continue;
 			// Channel Table�� ���� Offset���---------
 			if(CaAir==0)
				p = AIR_TAB[CountryToChannel[xEEPROMBuffer[SystemCountry]]] + (WORD)i;	// Freq. Table�� ���� �װ�(PLL Divider Value)��  ã�Ƽ�,
			else 
				p = CATV_TAB[CountryToChannel[xEEPROMBuffer[SystemCountry]]] + (WORD)i;	// Freq. Table�� ���� �װ�(PLL Divider Value)��  ã�Ƽ�,
			//---�Ｚ ntscƩ���� ��� ������ ����� ���������͸�--------
			if(CURRENT_TUNNER != SAMSUNG_TCPN9082DA27C);
			else{	// �ＺƩ�ʰ� ����Ǿ� �ִ� ��쿡, Low band 55.25Mhz�̸��� ���ļ��� ���͸��Ѵ�.(Ʃ�� ������ �����ϴ� ���ļ��̴�.)
				if(*p < 0x07E4)	continue;		// Dummy�� ����� Skip�Ѵ�.
			}
			//----���� ������ ���͸�.--------------------------------------------
			if(*p == 0)	continue;		// Dummy�� ����� Skip�Ѵ�.// PLL Divider Value�� Dummy Data���� üũ�Ѵ�. 		// 1�� 16�� Dummy Check�ϵ��� �߰���.
			else {
				TDivider = *p-AftRangeTable[xEEPROMBuffer[SystemCountry]];	
				TvPllOk(TDivider);
			}
			return TVSignalQaulity;
	}

}
*/

/*
#ifdef EMITest	//not used
void EMITestDataLoading(void){
	xdata WORD 	addr;
  	xdata unsigned short *p;
	xdata BYTE	ProgNo;
	xdata BYTE	i;


	CHANNEL_LIMIT=TvLimitTable[3*CountryToChannel[xEEPROMBuffer[SystemCountry]]+0];			

	ProgNo=1;	// Program Number�ʱ�ȭ.
	for(i=0; i < CHANNEL_LIMIT); i++){
 		// Channel Table�� ���� Offset���---------
		addr=ep_ChannelStartAir+2*i;
		p = AIR_TAB[CountryToChannel[xEEPROMBuffer[SystemCountry]]] + (WORD)i;	// Freq. Table�� ���� �װ�(PLL Divider Value)��  ã�Ƽ�,
		
		if(*p == 0){ 		// PLL Divider Value�� Dummy Data���� üũ�Ѵ�. 		// 1�� 16�� Dummy Check�ϵ��� �߰���.
			continue;				// Dummy�� ����� Skip�Ѵ�.
		}
		EepromSetQue(ep_ProgStart+ProgNo-1,i);	// Program������ Sync Channel�� ����Ѵ�.
		ProgNo++;	
		
		EepromSetQue(addr,0x01);		//  disable/air
		EepromSetQue(addr+1,AftRangeTable[xEEPROMBuffer[SystemCountry]]);	// default Fine Tune Data

		if(ProgNo > 100)break;
	}


	CHANNEL_LIMIT=CatvLimitTable[3*CountryToChannel[xEEPROMBuffer[SystemCountry]]+0];			
	for(i=0; i < CHANNEL_LIMIT; i++){
 		// Channel Table�� ���� Offset���
		addr=ep_ChannelStartCatv+2*i;
		p = CATV_TAB[CountryToChannel[xEEPROMBuffer[SystemCountry]]] + (WORD)i;	// Freq. Table�� ���� �װ�(PLL Divider Value)��  ã�Ƽ�,
		
		if(*p == 0){ 		// PLL Divider Value�� Dummy Data���� üũ�Ѵ�. 		// 1�� 16�� Dummy Check�ϵ��� �߰���.
			continue;				// Dummy�� ����� Skip�Ѵ�.
		}

		EepromSetQue(ep_ProgStart+ProgNo-1,128+i);	// Program������ Sync Channel�� ����Ѵ�.
		ProgNo++;	

		EepromSetQue(addr,0x03);		//  disable/catv
		EepromSetQue(addr+1,AftRangeTable[xEEPROMBuffer[SystemCountry]]);	// Fine Tune Data		
		if(ProgNo > 100)break;
	}

	TVParameterInit();
}
#endif
*/



#if( NTSC_COUNTRY==SAMSUNG)
#define K_STEP1 1
#else
#define K_STEP1 2
#endif

#if TvFineTuneValue_max==90
code BYTE TunerFineValueProcess[] = 
{	
	45,46, 44,47, 43,48, 42,49, 41,50,
	40,51, 39,52, 38,53, 37,54, 36,55,
	35,56, 34,57, 33,58, 32,59, 31,60,
	30,61, 29,62, 28,63, 27,64, 26,65,
	25,66, 24,67, 23,68, 22,69, 21,70,
	20,71, 19,72, 18,73, 17,74, 16,75,
	15,76, 14,77, 13,78, 12,79, 11,80,
	10,81,  9,82,  8,83,  7,84,  6,85,
	 5,86,  4,87,  3,88,  2,89,  1,90, 
};
#endif

#if TvFineTuneValue_max==48
code BYTE TunerFineValueProcess[] = 
{	
	24,25,	23,26,
	22,27,	21,28,
	20,29,	19,30,
	18,31,	17,32,
	16,33,	15,34,
	14,35,	13,36,
	12,37,	11,38,
	10,39,	9,40,
	8,41,	7,42,
	6,43,	5,44,
	4,45,	3,46,
	2,47,	1,48,
	0	
};
#endif


//  Return������ AFT Value�� �����Ѵ�.
//   Return value 0xff -> ������ļ��� ����. (�׿��� ���� Ok)
//   AUTO Search������ ����� ���. Test=0 ���� ����Ѵ�.
//   ������ AFT�� ����� ��� Test=1�� ����Ѵ�.
/*
BYTE AftSubFunction( WORD AFTDivider, BYTE AFTValue, Bool Test)
{	
#if	0	// youngdo 2003.6.2  for memory save	
	xBYTE	Tun_time,LKE_Flag;
	xBYTE	SearchOK,OldTune,NewTune;
	Bool 	first,BufferFull;
	xBYTE 	kkk,pp,CountTuneOk,Backupkkk;
	unsigned char xdata OSDStringBuff2[24];
	
	//TvPllOk(AFTDivider+AFTValue-AftRangeTable[xEEPROMBuffer[SystemCountry]]);	
	//delay5m(AFT_NORMALTIME);	// ǥ�� Ÿ�̹�.

	CheckTvSub();
	DBGputs("atf");
	if(Test==1){	// channel up/dn(selection)�ÿ� ���.
		TvPllOk(AFTDivider+AFTValue-AftRangeTable[xEEPROMBuffer[SystemCountry]]);	
		delay5m(NUM_10);
		//TvPllOk(AFTDivider+AFTValue-AftRangeTable[xEEPROMBuffer[SystemCountry]]);	
		//delay5m(NUM_10);
		pp=(0x07&ReadTuner());
		first=1;
		if((pp==0x02)){
			CheckTVSignal(AFT_MAINCOUNT);	//printf("1"); 
			return (AFTValue);
		}
	}
	else{		// auto search�ÿ� ���.
		first=0;
		AFTValue=0;				
#if (NTSC_COUNTRY == 0)
			delay5m(30);
#endif
	}
	
	// auto search������ ���� �ʱ�ȭ.
	//first=1;	// AFT�� ���� Start���� üũ�ϴ�  �÷���.
	SearchOK=0x00;		// sync search�ܰ�� ���� ���ؼ�...
			
//-------------------Sync Search�� �����Ѵ�.--------------------------------------------
// SearchOK Flag�� ���¿� ���� Description�� �Ʒ��� ����.
// 07 ��Ʃ��. --> �������۾��� �����Ѵ�.
// 00 ��ũ���� ����.  --> sync search�� �����Ѵ�.
// 01 ��ũ������ ���� ����. --> AFT�� �����ϱ� ���� �� �ܰ��۾��� �����Ѵ�.
// 02  AFT�� �����ϱ� ���� �� �ܰ��۾�. --> AFT������ ���ؼ� �����͸� üũ�Ѵ�.
// 17 ����� ���� ä�η� ó���Ѵ�.
// 03/04�� ��� --> AFT Data Search Loop�� �������̴�.
// 06 ����� �ִ� ä���̸� ���ۿ� ����� AFT Data Ž���� �����ϴ� �ܰ��̴�.--> ��Ȯ�� Auto Fine Tune Data�� ã�Ƴ���.
// 17 AFT Range Over�Ǵ� ���. --> Search Fail�� ó���Ѵ�.
	Sync_SearchStep:		// 0. IDȮ�� 	// Sync���� ��쿡 ����Ǵ� Loop
	while(SearchOK==0x00){	
			TvPllOk(AFTDivider+AFTValue-AftRangeTable[xEEPROMBuffer[SystemCountry]]);	
			delay5m(AFT_MAINTIME);
			CheckTVSignal(AFT_MAINCOUNT);
			
			if(eTVSyncFlag) {		// sync �� xx ����ÿ���..
#if(NTSC_COUNTRY==0)
				if(first){	// ó�� �������� ��ũ�� ã�� ���� �ð����� ������ ���ش�.
					TvPllOk(AFTDivider+AFTValue-AftRangeTable[xEEPROMBuffer[SystemCountry]]);
					delay5m(10);
					TvPllOk(AFTDivider+AFTValue-AftRangeTable[xEEPROMBuffer[SystemCountry]]);	
					delay5m(10);
				}
#endif
				SearchOK=0x01;
				break;
			}
			else	{AFTValue+=30;	}//No Synce��  -->  Sync Search Step=0.5Mhz	
			//}
			//else  {AFTValue+=30;}// Sync Search Step=1.5Mhz	--> ����ȣ�� 
		
			if(first){first=0;AFTValue=0;}	// Sync Search���ǿ� �������� �����ϱ� ���ؼ� AFT���� �ʱ�ȭ�� �Ѵ�.
			
			if(AFTValue>AftRangeTable[xEEPROMBuffer[SystemCountry]]*2) {SearchOK=0x17; break;}		// while loopŻ�� ����----> Sync Search����ġ(Fc+2.5Mhz)�ʰ��� ���.
	}
//------------------Auto Fine Tunning�� �����Ѵ�.-----------------------------------
	//AUTOFINE_STEP1:		// 1.Ʃ�� ������ Ȯ��.
	if(SearchOK==0x01){	// Syncã�� ��쿡�� Tuner Aft Data�� üũ�Ѵ�.
			switch(0x07 & (BYTE)ReadTuner()){
				case 4:	SearchOK=0x02;	AFTValue+=K_STEP1;	break;	// next step go go!!
				case 3:	SearchOK=0x02;						break;	// next step go go!!
				case 2:	if(first) {		//���� ���� ���ļ��� ù��° ã�� ���ϰ�, �ι�°  ���ýÿ� ã�� ���.
							//printf("2"); 
							return (AFTValue);
						}	
						SearchOK=0x02;	//SearchOK=0x07;					
						break;			// next step go go!!
				case 1:											// search failó���Ѵ�.
				case 0:	SearchOK=0x00; 					break;	// search failó���Ѵ�.		
			}
			if(SearchOK==0x00) {AFTValue+=10; goto Sync_SearchStep;}
	}
			
	//AUTOFINE_STEP2:
	if(SearchOK==0x02){	LKE_Flag=0;SearchOK=0x03;}

	AUTOFINE_STEP3:	
	while(SearchOK==0x03){		// AutoFine Tunning�� �����Ѵ�.
			Tun_time=0;
			//------���� �ʱ�ȭ.--------
			for(kkk=0;kkk<12;kkk++) OSDStringBuff2[kkk]=0x00;	// ���� �ʱ�ȭ. --> AFT ������ 
			for(        ;kkk<24;kkk++) OSDStringBuff2[kkk]=0xff;	// ���� �ʱ�ȭ. -->  Tune������ (Tune data�� 0~4�� ������ ���´�.)
			BufferFull=0;		// Buffer Full flag�� Ŭ����.
			kkk=0x00;		// AFT Data Buffer pointer�ʱ�ȭ.
			
			//-------���� AFT Data����------------------
			OldTune=0x07 & (BYTE)ReadTuner();
			OSDStringBuff2[0+kkk]=AFTValue;		// AFT ������ ����.
			OSDStringBuff2[12+kkk++]=OldTune;		//  AFT �����Ϳ� �����ϴ� Tune ������ ����.// ������ ������ ���� ������ ����.

			switch(OldTune){	// ���ļ��� �����ϴ� �������� Ʃ���� �����Ѵ�.
				case 4:	AFTValue+=K_STEP1;	break;	// good!!
				case 3:	AFTValue+=1;		break;	// good!!// Tun_time=1 --> �̼������� �Ѵ�.
				case 2:	SearchOK=0x06;		break;	//***  very good!!
				case 1:
				case 0: 	AFTValue+=10; 		goto Sync_SearchStep;			
			}
			if(SearchOK==0x03) SearchOK=0x04;
			
			//-----AFT Data�������----------
			while(SearchOK==0x04){
				if(AFTValue>(1+AftRangeTable[xEEPROMBuffer[SystemCountry]]*2)){	// AFT Range����� ��쿡�� �����Ѵ�.
					SearchOK=0x17; 	
					break;
				}
				
			if(LKE_Flag==1){	// tunning data�� 4�� �����͸� �ɷ�����.
				 	LKE_Flag=0;
					TvPllOk(AFTDivider+AFTValue-AftRangeTable[xEEPROMBuffer[SystemCountry]]);
				 	delay5m(NUM_20);//delay5m(5);
					//TvPllOk(AFTDivider+AFTValue-AftRangeTable[xEEPROMBuffer[SystemCountry]]);
				 	//delay5m(5);
			}
			else{
					TvPllOk(AFTDivider+AFTValue-AftRangeTable[xEEPROMBuffer[SystemCountry]]);
					delay5m(AFT_NORMALTIME);
				///if(Tun_time==1){ // Tun_time=1 --> �̼������� �Ѵ�.
				///	Tun_time=0;
				///	delay5m(AFT_MAINTIME);				/// --> Tun_time Data�� ���� �̼������� ���Ѵٸ� 
				///	CheckTVSignal(AFT_MAINCOUNT);	///       ///�� Ǫ�ø� �˴ϴ�.
				/// }									/// �ð��� ���̺��ϱ� ���ؼ� ���� ����. by LKE 4/16
				/// else{
					//delay5m(AFT_MAINTIME);
				 	CheckTVSignal(AFT_MAINCOUNT);
				 ///}
					if(!eTVSyncFlag) {	//No Sync �� ����Ǹ�  Sync Search�ܰ�� �ǵ��� ����.
						SearchOK=0x00; 
						goto Sync_SearchStep;
					}	
			}
				//-----New AFT Data����--------------
				NewTune=0x07 & (BYTE)ReadTuner();
				if(kkk==12) {		//���� Full���� --> ������ ó������ ������ ���ǰ����.---> AFT Data Buffer pointer�ʱ�ȭ.
					kkk=0;BufferFull=1; //printf("B");	
				}		
				OSDStringBuff2[0+kkk]=AFTValue;	// AFT ������ ����.
				OSDStringBuff2[12+kkk++]=NewTune;	// Tune ������ ����.

				//------*** AFT Data��ȭ���� üũ�ϰ�  Next Step�����ϴ� �ܰ�� ����.*** -----------
				//���� ��ȭ�� ���� ���.---> �������� ����.(���� = Zero)
				if((OldTune-NewTune)==0){ 
					//printf("0");
					switch(NewTune){	// ���ļ��� �����ϴ� �������� Ʃ���� �����Ѵ�.
						case 4:	AFTValue+=K_STEP1;	
								LKE_Flag=1; 
								SearchOK=0x03;
								goto AUTOFINE_STEP3;			// data�� 4�� ���� �����Ƿ� �����ʱ�ȭ.
						case 3:	
						case 2: 	AFTValue+=1;			break;	//*** (special case) next step go go!!
						case 1: 	
						case 0: SearchOK=0x00;			break;				
					}
				}
				LKE_Flag=0; 
				//���� ��ȭ�� �߻��� ���. --> �������� ����.(����= +)
				if(OldTune>NewTune){
					//printf("+");	
					switch(NewTune){	// ���ļ��� �����ϴ� �������� Ʃ���� �����Ѵ�.
						case 4:  AFTValue+=K_STEP1;			break;  	// --> �̰��� ����.(����)
						case 3:	AFTValue+=1;				break; 	// 4-->3���� ��ȭ �߻�.  (x�����ʱ�ȭ.)  <-- We are the world.
						case 2:	
#if( TUNER_MANUFACTURER==SAMSUNG)
								SearchOK=0x06;	break;
#else
								AFTValue+=1;	
								break; 	// 3-->2���� ��ȭ �߻�.  	want.
#endif								
						case 1:				SearchOK=0x06;	break;  	// *** next step go go!!// 2-->1�� ��ȭ �߻�.  (data�˻��� ���� )  <-- Best Choice!!
						case 0:				SearchOK=0x00;	break;  	// 1-->0�� ��ȭ �߻�.  (data�˻��� ���� )  <-- ����: �̰��� ���������� ����� ����.				
					}
				}
				
				//���� ��ȭ�� �߻��� ���. -->  No Wanted ����.(����= -)
				if(OldTune<NewTune){		// �������� ��� Tune Data�� 0-->4���� ��ȭ���� ���� �� �� �ִ�.
					//printf("-");			// �׷��� program ó�� �帧�� Negative���Ⱑ ������� �����.
					SearchOK=0x00;		// ���� Sync Search�ܰ�� ó���Ѵ�. 	
				}					

				// Sync Search�ܰ�� �ǵ�����. 
				if(SearchOK==0x00) {AFTValue+=10; goto Sync_SearchStep;}

				// Previous Tune Data����.
				OldTune=NewTune;	
			}
			//--------------
			if(AFTValue>(1+AftRangeTable[xEEPROMBuffer[SystemCountry]]*2)){SearchOK=0x17; break;}	// AFT Fine Tune data search fail�� ó���Ѵ�.
	}

//-------------������ �˻��� �����Ͽ� ����ȭ�� Tunning���� ã�´�.(SearchOK==0x06)---------------------
	if(SearchOK==0x06){	

				//----------������ ������ ����Ѵ�.
				if(BufferFull==1){
					if(kkk==0) Backupkkk=11;
					else  Backupkkk=kkk-1;	
				}
				else Backupkkk=kkk-1;	// ������ ������ ����Ѵ�.

				//-----------TEST(������ ����)--------
				//kkk=0;



				//-----���� ��Ʃ�� �������� offet(Backupkkk)�� ���������� ������ ��Ʃ�� ������ �� ����(CountTuneOk)�� ���Ѵ�.
				first=0;
				if(BufferFull==1){	// buffer full�� �߻��� �����, �����̼� üũ�� �����Ѵ�.
					kkk=Backupkkk;
					for(pp=0;pp<12;pp++){	
						if(2== OSDStringBuff2[12+kkk]) {CountTuneOk=0;break;}	// Tune data�˻�.
						if(kkk==0) kkk=11;
						else kkk--;
					}
					Backupkkk=kkk;	// ������ ��Ʃ�� �������� offet�� ����Ѵ�.
					for(;pp<12;pp++){	
						if(2== OSDStringBuff2[12+kkk]) {
							Backupkkk=kkk;
							CountTuneOk++;	// temp���� 2�� ������ ����ȴ�.
							if(kkk==0) kkk=11;
							else kkk--;	// kkK���� ���������� ���� ��Ʃ�� �������� offet�� ����ȴ�. 
						}
						else {first=1; break;}	// Tune data�˻�.
					}
				}
				else{	// normal check�� �����Ѵ�. --> ���� �����͸� ã�´�.
					kkk=0;	
					for(pp=0;pp<12;pp++){
						if(2== OSDStringBuff2[12+kkk]) {
							Backupkkk=kkk;	// ���� ��Ʃ�� �������� offet�� ����Ѵ�.
							CountTuneOk=0;
							break;
						}
						kkk++;
					}
					for(;pp<12;pp++){	
						if(2== OSDStringBuff2[12+kkk++]) {CountTuneOk++;}	// pp���� �������� ������ ��Ʃ�� �������� ���� ã�´�..
						else {first=1; break;}
					}
				}
				//------------------------------------
				if(first==1){	// ��Ʃ�� �����͸� ã�� ���.

					// CountTuneOk=>���������� ������ ��Ʃ�� ������ �� ������ Count�ϱ� ���� ��� --> ���� �ʱ�ȭ.
					// ��Ʃ�� �������� ������ ������ ������ �̿��Ͽ� AFT Fine Tune�����͸� ã�´�.
					switch(CountTuneOk){		//�Ｚ Ʃ�ʴ� 1~2���̴�.
						case 1:
						case 2:		// ��Ʃ�� �����Ͱ� 1,2���, ù��° Data�� ���Ѵ�.
							AFTValue=OSDStringBuff2[Backupkkk];break;	// AFT Data����.
						case 3:		// ��Ʃ�� �����Ͱ� 3,4�� �̸� �ι�° Data�� ���Ѵ�.
						case 4:
							if(BufferFull==1){
								if(Backupkkk==11) AFTValue=OSDStringBuff2[0];
								else   AFTValue=OSDStringBuff2[Backupkkk+1];
							}else AFTValue=OSDStringBuff2[Backupkkk+1];
							break;	// AFT Data����. 
						case 5:	// ��Ʃ�� �����Ͱ� 5�� �̸� 3��° Data�� ���Ѵ�.
							if(BufferFull==1){
								if(Backupkkk==11) AFTValue=OSDStringBuff2[1];
								else if(Backupkkk==10) AFTValue=OSDStringBuff2[0];
								else  AFTValue=OSDStringBuff2[Backupkkk+2];
							}else  AFTValue=OSDStringBuff2[Backupkkk+2];
							break;
					}

					 if((CountTuneOk>5)||(CountTuneOk==0)) {	// ��Ʃ�� �����Ͱ� 6�� �̻��� ��� --> Failó���Ѵ�.
					 	SearchOK=0x17;

					 }	
					else {
						SearchOK=0x07; 
					}
				}
				//--------------------------------------
				else{
					SearchOK=0x17;

					}

	}
		
//------------- ����ȭ�� Tunning���� �����Ѵ�.---------------------
	switch(SearchOK){
		case 0x07:
#if( TUNER_MANUFACTURER==SAMSUNG)	// �ＺƩ���� ���.(Ntsc/Pal����.)


	//#if (CURRENT_TUNNER==SAMSUNG_TCPN9082DA27C)
	//#if (1)
		// �ＺƩ���� ��� AFT������ ����Ǵ� �߿���  1step�� ������ �ִ�. --> ������.(case by case)
		// �ＺƩ���� ��� --> ��Ư���� ����  Ʃ�׵����� ����. 
		//#if (NTSC_COUNTRY==1)
			AFTValue=AFTValue;
		//#else
		//	AFTValue=AFTValue-1;		// 1step�� ������ �ִ�. -> AFT Range�����ϸ鼭����.
		//#endif
			if(AFTValue>AftRangeTable[xEEPROMBuffer[SystemCountry]]*2){return (0xff);}
 			if(Test==1){	
 				// channel up/dn(selection)�ÿ� ���.
				TvPllOk(AFTDivider+AFTValue-AftRangeTable[xEEPROMBuffer[SystemCountry]]);	
			}
			return (AFTValue);	// AFT Find.
	//#else
	//		if(AFTValue>AftRangeTable[xEEPROMBuffer[SystemCountry]]*2){return (0xff);}
 	//		if(Test==1){	
 	//			// channel up/dn(selection)�ÿ� ���.
	//			TvPllOk(AFTDivider+AFTValue-AftRangeTable[xEEPROMBuffer[SystemCountry]]);	
	//		}
	//		return (AFTValue);	// AFT Find.
	//#endif


			
#else	//�ＺƩ�ʰ� �ƴѰ�� (Ntsc/Pal����.)
 			if(Test==1){	// channel up/dn(selection)�ÿ� ���.
				if(AFTValue>AftRangeTable[xEEPROMBuffer[SystemCountry]]*2){return (0xff);}
				TvPllOk(AFTDivider+AFTValue-AftRangeTable[xEEPROMBuffer[SystemCountry]]);	
			}
			return (AFTValue);	// AFT Find.

#endif

		case 0x17: 	return (0xff);		// AFT No found.
		default:			// bug �߻�.
					return (0xff);
	}
#endif
}
*/


// by LKE 2/22 
// EEProm�� Start Offset���� End OffsetƯ�������� ä�ﶧ ����Ѵ�.  
// EEProm�� start offset ����  end offset ���� value1�� value2�� �����Ͽ� write�� ���Ѵ�.
// Note: ..
// (EEProm start address, start offset, end offset, value1, value2)
/* youngdo 2003.5.28    �ӽ÷� ���Ƶ�. ************************************
void EepTvFillValue(WORD Addr,BYTE StartOffset,BYTE EndOffset,BYTE Value1,BYTE Value2)
{
		xdata BYTE kkk;
		xdata WORD i,BackupAddr;


		return;
		
		Addr=Addr+(WORD)StartOffset;
		i=(WORD)StartOffset;

		if(i>(WORD)EndOffset) return;
		
		//------ page������ write�� �Ұ��ɽÿ��� 1BYTE������ Write�� ���Ѵ�.
		for(i=(WORD)StartOffset;i<=(WORD)EndOffset;i++) {	
			if(i>(WORD)EndOffset) return;		// ��� ä�����ٸ� ����.
			if(0x00==(Addr%16)) break;	// page �߰�...
			EepromSetQue(Addr++,Value1);	//  Nousing/Air/Disable Data, 
			EepromSetQue(Addr++,Value2);	// FineTune Data�� 50���� �ʱ�ȭ.
			i++;
		}
		
		//--------page������ Write�� ���Ѵ�.
		kkk=0;	
		for(; i <= (WORD)EndOffset; i++){
			OSDStringBuff[kkk++]=Value1; 	//  Nousing/Air/Disable Data, 
			OSDStringBuff[kkk++]=Value2;		// FineTune Data�� 50���� �ʱ�ȭ.
			i++;
			if(kkk==16){	// 16byte�� ���ۿ� ä������ write..
				kkk=0; 
				write24c16Page(Addr, OSDStringBuff);
				Addr+=16;
			}

			// EndOffset���� �Դµ�,  EndOffset�� ���� Page������ ������ offset�� ���� 
			// �������� ���� �� ����ȴ�. 
			if( i == (WORD)EndOffset){
				if((kkk < 16)&&(kkk != 0)){
					BackupAddr=Addr;
					Addr=Addr+kkk;	// Address����.
					for(;kkk<16;kkk++) 
						OSDStringBuff[kkk]=EEPROM_Read(Addr++);
					Addr=BackupAddr;
					Write24c16Page(Addr, OSDStringBuff);
				}
			}
			
		}

}

***********************************************************/

// check 2/22 by LKE
// xEEPROMBuffer[CurrentChannel]�� Tuner�����ϰ�, Channel OSD�� Display�Ѵ�. 
// ���� osd display�ϰ� Ʃ�ʼ����ϵ��� ����() --> by LKE 2.15 --> �̷��� �ϸ� vpx�� color�� ���ν����� ����.
void ViewCurrentChannel(void)		
{
//	Bool ChannelBool;
	Pre_ChannelSel(xEEPROMBuffer[CurrentChannel]);	// Pre set.
	

	//--channel osd display�� ���Ѵ�.(ntsc/pal�� ���� �ٸ��� ǥ����)
/*youngdo 2003.5.28****************************************************************
	if(OsdState==CHANNEL) ChannelBool=0;	// �̹� Channel OSD�� ���ִ� �����..
	else ChannelBool=1;	
	if(CheckChMask(xEEPROMBuffer[CurrentChannel])==0)	// Enable��  chanel�� Display --> Green ���� channel osdǥ��
		ShowOSDChannel(CheckChCATV(xEEPROMBuffer[CurrentChannel]),GetRealChannel(xEEPROMBuffer[CurrentChannel]),ChannelBool,fGREEN);	// OSD Channel Display
	else		// Disable��  chanel�� Display--> Yellow�� channel osdǥ��
		ShowOSDChannel(CheckChCATV(xEEPROMBuffer[CurrentChannel]),GetRealChannel(xEEPROMBuffer[CurrentChannel]),ChannelBool,fYELLOW);	// OSD Channel Display
*******************************************************************************/

	ChannelSel(xEEPROMBuffer[CurrentChannel]);	// Prog No�� �̿��Ͽ� --> Tunner�� �����Ѵ�.

}

BYTE  CalDispchannel()
{
	#if defined(USE_NTSCtuner)||defined(FrequncyTableType)
		return xEEPROMBuffer[CurrentChannel]+CHANNEL_MIN;
	#else
		//return EEPROM_Read(ep_ProgStart+(WORD)xEEPROMBuffer[CurrentChannel]);
		return EEPROM_Read(ep_ProgStart+(WORD)xEEPROMBuffer[CurrentChannel])+CHANNEL_MIN;	//2004-05-11
	#endif
}


//*********************************************
// TV program memory map //by thkim
// NTSC : addr0->status
//        addr1->Fine Tune
// PAL : addr0->status
//		 addr1->channel number
//		 addr2->Fine tune value
//		 addr3->reserved
//		 addr4~7->channel name
//*********************************************
// check 2/23 by LKE        
BYTE GetChannelStatus(BYTE channel)
{
	#ifndef FrequncyTableType	//+++++++++++++++++++++++++++++++++
	
	#if((NTSC_COUNTRY==1)||(AUTO_SETUPDEBUG==1))	// NTSC
		if(AntenaFlag)	return EEPROM_Read(ep_ChannelStartCatv+(WORD)channel*2 );	// catv	//ep_ChannelStartCatv:0x500
		else			return EEPROM_Read(ep_ChannelStartAir+(WORD)channel*2);		// air	//ep_ChannelStart	 :0x400
	#else		// PAL-Multi
		//xBYTE AddrEEp;
		
//		DBGputs("GetChannelStatus");
   		//AddrEEp= EEPROM_Read(ep_ProgStart+(WORD)channel);				//ep_ProgStart	 :0x300
   		//return EEPROM_Read(ep_ProgMemStart+(WORD)AddrEEp*PRMEMNUM);		//ep_ProgMemStart:0x400
   		return EEPROM_Read(ep_ProgMemStart+channel*PRMEMNUM);		//ep_ProgMemStart:0x400
	#endif
	
	#else	//+++++++++++++++++++++++++++++++++++++++++++++++++++++
		return EEPROM_Read(ep_ChannelStart+(WORD)channel*2 );
	
	#endif	//+++++++++++++++++++++++++++++++++++++++++++++++++++
}

// check 2/23 by LKE
 
void SetChannelStatus(BYTE channel,BYTE Value)
{
	#ifndef	FrequncyTableType	//+++++++++++++++++++++++++++++++++
	
	#if((NTSC_COUNTRY==1)||(AUTO_SETUPDEBUG==1))
		if(AntenaFlag)	EepromSetQue(ep_ChannelStartCatv+(WORD)channel*2 ,Value);
		else			EepromSetQue(ep_ChannelStartAir+(WORD)channel*2,Value);		
	#else
		xBYTE AddrEEp;
		AddrEEp= EEPROM_Read(ep_ProgStart+channel);
		EepromSetQue(ep_ProgMemStart+(WORD)AddrEEp*PRMEMNUM,Value);
	#endif

	#else	//+++++++++++++++++++++++++++++++++++++++++++++++++++++
		EepromSetQue(ep_ChannelStart+(WORD)channel*2,Value);		
		
	#endif	//+++++++++++++++++++++++++++++++++++++++++++++++++++
}



// check 2/23 by LKE
// 1��16�� Jho
// by Lee 2.11 void return���� Bool return���� ������.

Bool ToggleChMask()
{
	xBYTE flag;
	flag=GetChannelStatus(xEEPROMBuffer[CurrentChannel]);	
	
	if(flag & BIT_0)
	{
		SetChannelStatus(xEEPROMBuffer[CurrentChannel],flag&~BIT_0);	//make enable
		return 0;	// yes
	}
	else
	{
		SetChannelStatus(xEEPROMBuffer[CurrentChannel],flag|BIT_0);		//make disable 
		return 1;	// no
	}
	
}


// check 5/12 by LKE PAL�� ��� No-Using Channeló�� �ɼ� �߰���.
// check 2/23 by LKE
// ProNoMask_Flag�� üũ�Ѵ�.( 0 : Enable, 1 : Disable)
Bool CheckChMask(BYTE channel)
{
	xBYTE flag;
//	DBGputs("CheckChMask");
	#if((NTSC_COUNTRY==1)||(AUTO_SETUPDEBUG==1))||defined(FrequncyTableType)

		flag=GetChannelStatus(channel);
		return	(flag & BIT_0);

	#else			// PAL-Multi

		flag=GetChannelStatus(channel); //���⼭ eprom 2���д´�..
		if( (EEPROM_Read(ep_ProgStart+(WORD)channel)==0xff) || ((flag & BIT_0) != 0) )
		//if( ((flag & BIT_0) != 0) )
			return 1;	// Disable
		else 
			return 0;	// ENable

	#endif
}

// check 2/23 by LKE
// CableAir_Flag�� check�Ѵ�.(1:Cable-TV, 0:Air-TV)
Bool CheckChCATV(BYTE channel)
{
	#if( (NTSC_COUNTRY==1)||(AUTO_SETUPDEBUG==1) ||defined(FrequncyTableType) )
		// NTSC
		channel=channel+0x00;	// dummy ���ǹ��� ����. �����ϰ���ȳ���..
		if(AntenaFlag)
		{
//			DBGputs("ANTENA_CABLE\n");
			return ANTENA_CABLE;	//1
		}
		else
		{
//			DBGputs("ANTENA_AIR\n");
			return ANTENA_AIR;		//0
		}
	#else			// PAL-Multi
		xBYTE flag;
		
//		DBGputs("CheckChCATV");
		flag=GetChannelStatus(channel);
		if((flag & BIT_1) != 0)	return 1;	// catv
		else 					return 0;	// air
	#endif
}

// check 2/23 by LKE
// FineTune_Flag�� check�Ѵ�.(1:manual tune, 0:auto tune) 
Bool CheckChFineTune(BYTE channel)
{
	xBYTE flag;
//	DBGputs("CheckChFineTune");
	flag=GetChannelStatus(channel);
	return	(flag & BIT_2);
//	if(flag & BIT_2)	return 1;		//manual fine tune��  enable�Ǿ��� �ִ�.
//	else 				return 0;		// auto tune
}

void SetManualTune(BYTE channel)
{
	xBYTE flag;
//	DBGputs("SetManualTune");
	flag=GetChannelStatus(channel);
	SetChannelStatus(channel, flag|BIT_2);
}

/*
#if(NTSC_COUNTRY==0)
// check 2/22 by LKE
Bool CheckChAFT(BYTE channel)
{
	BYTE flag;
	flag=GetChannelStatus(channel);
	return (flag & BIT_3);
}
#endif
*/

#if(NTSC_COUNTRY==0)&&!defined(FrequncyTableType)
// ntsc--> ä���� ��밡�������� üũ�Ѵ�. ( 0 : Using, 1 : NoUsing) 
// program no -> ä�� �Ҵ��� �Ǿ� ���� ����.( 0 : Using, 1 : NoUsing) 
// check 2/22 by LKE
Bool CheckChNotUSE(BYTE channel)
{
	#if((NTSC_COUNTRY==1)||(AUTO_SETUPDEBUG==1))||defined(FrequncyTableType)
		xBYTE flag;
		flag=GetChannelStatus(channel);
		return	(flag & BIT_7);
	#else		
		xBYTE flag;

//		DBGputs("CheckChNotUSE");
		flag=GetChannelStatus(channel);
		//if(EEPROM_Read(ep_ProgStart+(WORD)channel)==0xff) 
		
		//if( (EEPROM_Read(ep_ProgStart+100+(WORD)channel*8+2)==0xff) || ((flag & BIT_7) != 0) )	//ep_ProgStart=0x300
		if(  ((flag & BIT_7) != 0) )	//ep_ProgStart=0x300
			  return 1;
		else  return 0;
	#endif		

}
#endif

// check 2/23 by LKE
// Program Number�� �Ҵ�Ǿ��� channel table offset�� eeprom���� ���� ��´�. 
BYTE GetRealChannel(BYTE channel)
{	
	#ifndef FrequncyTableType	//+++++++++++++++++
	
	#if((NTSC_COUNTRY==1)||(AUTO_SETUPDEBUG==1))
		return	channel;

	#else
		BYTE AddrEEp;
  	AddrEEp=EEPROM_Read(ep_ProgStart+(WORD)channel);
		return EEPROM_Read(ep_ProgMemStart+(WORD)AddrEEp*PRMEMNUM+1);
	#endif
	
	#else	//++++++++++++++++++++++++
		return	channel;
	#endif	//++++++++++++++++++++++
}

// check 2/23 by LKE
// Manual Fine Tune Data�� eeprom���� ���� Read
BYTE GetFineTune(BYTE channel)
{
	#ifndef FrequncyTableType	//++++++++++++++++++++++++++++++++++++++
	
	#if((NTSC_COUNTRY==1)||(AUTO_SETUPDEBUG==1))		// NTSC
		if(AntenaFlag)	return EEPROM_Read(ep_ChannelStartCatv+(WORD)channel*2+1);	//catv=0x500//ep_ChannelStart=0x400
		//if(AntenaFlag)	return EEPROM_Read(ep_ChannelStart+(WORD)channel*2+1);	
		else			return EEPROM_Read(ep_ChannelStartAir+(WORD)channel*2+1);			//air //ep_ChannelStart=0x400
	#else	
		BYTE AddrEEp;		// PAL-Multi
  		AddrEEp=EEPROM_Read(ep_ProgStart+(WORD)channel);				//ep_ProgStart=0x300
		return EEPROM_Read(ep_ProgMemStart+(WORD)AddrEEp*PRMEMNUM+2);	//ep_ProgMemStart=0x400
	#endif
	
	#else	//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		return EEPROM_Read(ep_ChannelStart+(WORD)channel*2+1);			//air //ep_ChannelStart=0x400
	#endif	//++++++++++++++++++++++++++++++++++++++++++++++++++++++++
}

// check 2/23 by LKE
// Fine Tune Data���� Write�Ѵ�.(flag�� �VƮ���� ����.)
 
void  SetFineTune(BYTE channel,BYTE value)
{
	#ifndef	FrequncyTableType	//++++++++++++++++++++++++++++++++
	
	#if((NTSC_COUNTRY==1)||(AUTO_SETUPDEBUG==1))		// NTSC
		if(AntenaFlag)	EepromSetQue(ep_ChannelStartCatv+(WORD)channel*2+1,value);
		//if(AntenaFlag)	EepromSetQue(ep_ChannelStart+(WORD)channel*2+1,value);
		else				EepromSetQue(ep_ChannelStartAir+(WORD)channel*2+1,value);		
	#else			// PAL-Multi
		BYTE AddrEEp;
		//if(CheckChNotUSE(channel))	;	//EepromSetQue(ep_ProgStart+100,value);	// by LKE 5/12 No-Using Channel ó�������ؼ� �߰�.
		//else	
		//{ 
			AddrEEp=EEPROM_Read(ep_ProgStart+(WORD)channel);
			EepromSetQue(ep_ProgMemStart+(WORD)AddrEEp*PRMEMNUM+2,value);	
		//}
	#endif
	
	#else	//+++++++++++++++++++++++++++++++++++++++++++++++++++++
		EepromSetQue(ep_ChannelStart+(WORD)channel*2+1,value);
	#endif	//+++++++++++++++++++++++++++++++++++++++++++++++++++
}	
 

// check 2/22 by LKE
// by LKE 2/15
// AFT data�� Write�ϰ� AFT Flag�� ��Ʈ�Ѵ�. -> AFT Falg�� ��Ʈ���� �ʴ´�. 4.24�� LKE
/*  memory save  2003.6.3
void  SetAutoFineTune(BYTE channel,BYTE value)
{
///	BYTE flag;
#if((NTSC_COUNTRY==0)&&(AUTO_SETUPDEBUG==0))
	xBYTE AddrEEp;
	AddrEEp=0;
#endif
	SetFineTune(channel,value);	// AFT�Ǵ�Fine Tune  data Write

#if((NTSC_COUNTRY==1)||(AUTO_SETUPDEBUG==1))
		// NTSC
		if(AntenaFlag)	{	// Cable
			///flag= BIT_3 | EEPROM_Read(ep_ChannelStart+(WORD)channel*2+0x100+0);
			///EepromSetQue(ep_ChannelStart+(WORD)channel*2+0x100+0,flag);
		}
		else{	// Air	
			///flag= BIT_3 | EEPROM_Read(ep_ChannelStart+(WORD)channel*2+0);
			///EepromSetQue(ep_ChannelStart+(WORD)channel*2+0,flag);		
		}
#else	// PAL-Multi
		///AddrEEp= EEPROM_Read(ep_ProgStart+(WORD)channel);
		///flag= BIT_3 | EEPROM_Read(ep_ChannelStart+(WORD)AddrEEp*2);		// flag read
		///EepromSetQue(ep_ChannelStart+(WORD)AddrEEp*2,flag);	// flag set
#endif
}
*/


// Tuner������ PLL����ȭ�Ǵ����� üũ 
void TvPllOk(unsigned int Divider)
{
	xBYTE i,j;
	j=0;

	while(1)
	{
		SetTuner(Divider);
		
		#ifdef USE_UART	//test
		DBGputss((unsigned int)Divider>>8);		
		DBGputss(Divider);DBGputs(" ");		
		#endif	
	
		for(j=0;j<5;j++)
		{
			i= 0xf0 & (BYTE)ReadTuner();
			if(errorflag==0x80) return;	// Tuner ����ȵ� ����̸� ����.
			if((i==0x50)||(i==0x70)||(i==0x60)) return;	// phase Lock OK�̸� ����.{������� lg(ntsc),samung(ntsc),samung(pal)}
		}
		break;
	}	
	
}

#if (TOTAL_CHANNEL_SEARCH_RS232==1)

#define START_VALUE 0x069d
#define END_VALUE 0x4970	// �� 901Mhz

void TunerTestSearch(void){
	xdata WORD Devider_Test=0;
	xdata WORD OLD_Value=0;
	
	for(Devider_Test=START_VALUE; Devider_Test<END_VALUE+1;Devider_Test++){
		TvPllOk(Devider_Test);
		if(errorflag==0x00) {
			if((ReadTuner()&0x07)==0x02)	{
				if((Devider_Test-OLD_Value)>50){

					delay5m(10);	// ��ũ��ġ�� ���� Ÿ�̹� �����ϰ� ��������.
					CheckTVSignal(AFT_MAINCOUNT);
					if(eTVSyncFlag && ((0x07 & ReadTuner())==0x02)){
						NT68520CmdWrite(0x6F,NT68520CmdRead(0x6F)|0x06);		// Input Timing Recalibration�� ���Ѵ�.		
						OLD_Value=Devider_Test;
					}
				}
			}
		}
	}
}
#endif



// check 2/20 by LKE  
// --> Pal-Multi�ǰ�� NoUsing Program No�� ��� Catv max ä�� ���ļ��� �����Ѵ�.
//  Pal-Multi�ǰ�� NoUsing Program No�� ���ؼ� 
//                    --->  ProgEdit�������� 0xff�� ������ �����ʹ� NoUsing Program No�� ó���Ѵ�.
// Prog No�� ���� ���� channel table offset�� ���(Manual Tune����)�Ŀ�, Tunner�� �����Ѵ�.
// Tuner ������ 0.5�� Sleep�Ѵ�.
// 3.1�� --> AFT�� ���� �ʴ� ������ �߰���.(ä���� disable�Ǿ� �ִ� ��쿡�� Center Freq�� ����)
void ChannelSel(BYTE ch)
{
	xdata unsigned short *p;
	xdata WORD	Divider;
	xBYTE  FineTune,ChannelStatus;
	
	#ifdef USE_UART	
	DBGputs("ChannelSel");
	#endif
	if(ch > CHANNEL_LIMIT)  return;		// Pal-Multi : 1��15�� 128-->100���� ����.

	//-----
	#if(NTSC_COUNTRY==0)&&!defined(FrequncyTableType)		// PAL-Multi
		if(CheckChNotUSE(ch))
		{	// no usingä�� �� ���. --> Catv max ä�� ���ļ��� �����Ѵ�. -> // 855.25Mhz�� ����. by LKE 5/12
			#ifdef TunerRefDiv512
			TvPllOk(0x38E2);//TvPllOk(*p);  // 871.25Mhz�� ����. (china max����_ch)
			//DBGputs("  TvPllOk(0x3862)");	
			#else
			TvPllOk(0x45db);//TvPllOk(*p);  // 855.25Mhz�� ����.
			#endif
			//delay5m(25);	// by LKE 2.25
			CheckTVSignal(5);	// 1.27cho
			return;
		}
	#endif
	//--------

	// Using channel...
	// Prog No�� ���� ���� channel table offset�� ��� �Ѵ�.
	if(CheckChCATV(ch)==0) 	// Air-TV�� ���
		p= AIR_TAB[CountryToChannel[xEEPROMBuffer[SystemCountry]]]+GetRealChannel(ch);
	else					// Cable-TV�� ���
		p=CATV_TAB[CountryToChannel[xEEPROMBuffer[SystemCountry]]]+GetRealChannel(ch);	
	
	Divider = *p;		// Tuner PLL Divider Value
	
	FineTune = GetFineTune(ch);
	xEEPROMBuffer[NTSC_AIRTVFine_buf]=FineTune;

	ChannelStatus=GetChannelStatus(ch);

	Divider = Divider + (WORD)FineTune - AftRangeTable[xEEPROMBuffer[SystemCountry]];
		
//		DBGputss(GetRealChannel(ch));
//		DBGputss(CheckChCATV(ch));
//		DBGputss((BYTE)(Divider>>8));
//		DBGputss((BYTE)(Divider&0xff));

	TvPllOk(Divider);
//	delay5m(25);//
		

	#if	0	// youngdo 2003.6.2   �ϴ� aft�� ���Ƴ�.
	if(((ChannelStatus&0x05) != 0) ||(ATFEnable==0) ){	// disable,finetune,AFT Disable�� ���.
		Divider = Divider + (WORD)FineTune - AftRangeTable[xEEPROMBuffer[SystemCountry]];
		TvPllOk(Divider);
		delay5m(25);
	}
	else{		// �׿ܿ��� AFT�� �����Ѵ�.
		BackupTune=FineTune;	
		FineTune=AftSubFunction(Divider,FineTune,1);
		if(FineTune==0xff) {
				FineTune=AftRangeTable[xEEPROMBuffer[SystemCountry]];
				TvPllOk(Divider);
				delay5m(25);
		}
		else if(BackupTune!=FineTune)	SetAutoFineTune(ch,FineTune);	// AFT����� Write�ϰ� aft flag�� ��Ʈ�Ѵ�.		
	}
	#endif

	CheckTVSignal(5);	// 1.27cho

}

void SetFinePLL(BYTE ch,BYTE FineTune)
{
	xdata unsigned short *p;
	xdata WORD	Divider;

	if(ch > CHANNEL_LIMIT)  return;		// Pal-Multi : 1��15�� 128-->100���� ����.

	if(CheckChCATV(ch)==0) 	// Air-TV�� ���
		p= AIR_TAB[CountryToChannel[xEEPROMBuffer[SystemCountry]]]+GetRealChannel(ch);
	else						// Cable-TV�� ���
		p=CATV_TAB[CountryToChannel[xEEPROMBuffer[SystemCountry]]]+GetRealChannel(ch);	

	Divider = *p;		// Tuner PLL Divider Value		

	Divider = Divider + (WORD)FineTune - AftRangeTable[xEEPROMBuffer[SystemCountry]];		
//	DBGputss((BYTE)(	Divider>>8));
//	DBGputss((BYTE)(	Divider&0xff));
	TvPllOk(Divider);
	idelay5m(2);
	TvPllOk(Divider);
	CheckTVSignal(1);	// 1.27cho	

	//LED_OFF;idelay5m(200);LED_ON;//test//2004-05-07 11:24����
	
}

void Pre_ChannelSel(BYTE ch)
{
	xdata unsigned short *p;
	xdata WORD	Divider;
	xBYTE  FineTune;//BackupTune,
	
	if(ch > CHANNEL_LIMIT)  return;		// Pal-Multi : 1��15�� 128-->100���� ����.

	#if(NTSC_COUNTRY==0)&&!defined(FrequncyTableType)
		// PAL-Multi
		if(CheckChNotUSE(ch))
		{	// no usingä�� �� ���. --> Catv max ä�� ���ļ��� �����Ѵ�.
			#ifdef TunerRefDiv512
			TvPllOk(0x38E2);//TvPllOk(*p);  // 871.25Mhz�� ����. (china max����_ch)
			#else
			TvPllOk(0x45db);//TvPllOk(*p);  // 855.25Mhz�� ����.
			#endif
			return;
		}
	#endif


	// Using channel...
	// Prog No�� ���� ���� channel table offset�� ��� �Ѵ�.
	if(CheckChCATV(ch)==0) 	// Air-TV�� ���
		p= AIR_TAB[CountryToChannel[xEEPROMBuffer[SystemCountry]]]+GetRealChannel(ch);
	else						// Cable-TV�� ���
		p=CATV_TAB[CountryToChannel[xEEPROMBuffer[SystemCountry]]]+GetRealChannel(ch);	
   
	Divider = *p;		// Tuner PLL Divider Value	
	FineTune = GetFineTune(ch);
//	xEEPROMBuffer[NTSC_AIRTVFine_buf]=FineTune;
	Divider = Divider + (WORD)FineTune - AftRangeTable[xEEPROMBuffer[SystemCountry]];
	TvPllOk(Divider);
}



// Fw<Fc�� ��쿡 ����Ѵ�.  LKE
//  Phase Lock�ǰ�, Power ON reset Status����üũ�Ѵ�. LKE 1.24
void WriteTun1(unsigned char DivH,unsigned char DivL,unsigned char Band)
{
	xBYTE count = 0;
	if(NoTunerFlag)	return;	
	while(count<I2CErrorTry)
	{
		++count;
		if(BTC_START_I2C(TunerAddr))	continue;

		#ifdef TunerRefDiv512
		if(CURRENT_TUNNER==LGINOTEK_TAPC_H701F)
		{
			if(BTC_WriteData(0xC6))			continue;	//Freq.step:62.5KHz
		}
		else
		{
			if(BTC_WriteData(0xCE))			continue;//2004-01-16//TunerRefDiv512(Freq.step:62.5KHz)
		}
		#else
		if(BTC_WriteData(0xCC))			continue;
		#endif
		if(BTC_WriteData(Band))			continue;
		if(BTC_WriteData(DivH))			continue;
		if(BTC_WriteData(DivL))			continue;
		BTC_STOP_I2C();	
	}

	//  	delay5m(TUNER_STABLE_TIME+2);
	//TunnerIICTimer=TUNER_STABLE_TIME;
}

// ReadTuner()���� ����ϱ� ���� ��ƾ�̴�.
// �ܼ���, Tuner Status�� �о return�Ѵ�.
BYTE TunerDataCatch(void)
{
	xBYTE count = 0;
	xBYTE Recdata = 0;
	while(count<I2CErrorTry){
		++count;
		if(BTC_START_I2C(TunerAddr|0x01))		continue;
		Recdata = (BYTE)BTC_ReadDataNAK();
		BTC_STOP_I2C();
		return Recdata;
	}
}



// errorflag�� ���� data
// 0x00 --> Phase Lock Ok, Tuner�ִ�.
// 0x01 --> Phase Lock Fail , Tuner�ִ�.
// 0x80 --> Tuner����.	���� 
// errorflag�� ������� Tuner Read Data�� ���������� return�ȴ�.
unsigned char ReadTuner(void)
{
	xBYTE BackUp1,BackUp2,i;//,TestData;
	xBYTE tmptest=0;

	i=0;
	errorflag=0x00;

	//if(NoTunerFlag) {		// �����߿��� Tuner�� üũ�ϱ� ���ؼ� ����. --> by LKE 2.14
	//	errorflag=0x80;
	//	return	0xff;
	//}

	//-------�Ʒ����� spec�������� �����͸� Ʃ�ʿ� ���ýÿ� ��Ÿ���� Ʃ�� ����� ����ϴ� �κ��̴�.
	//-------���� : �߿��ϹǷ� �ʵ�!!
	//switch(CURRENT_TUNNER){
	//	case LGINOTEK_TAPC_H701F:		// LG NTSC ����Ʃ��.
		// pll locking�� ����� �����Ϻ����� 5�̴�. 	2.13 by LKE ����.
		// ---> note:���׳��� ����ȵǾ ,Pll Locking�ȴ�.
		// locking���� �ʴ� ����, ������ ��� pll �����͸� setting�ϰų�,  system power on/off�ÿ� �߻��Ѵ�.
		// �� ���� ���� 3�̰ų� b���ȴ�.
	//		TestData=0x50; break;	
	//	case SAMSUNG_TCPQ9091PD27D:	// samsung PAL ���� Ʃ��.
		// pll locking�� ����� �����Ϻ����� 7�̴�. 	2.13 by LKE ����.
		// ---> note:���׳��� ����ȵǾ ,Pll Locking�ȴ�.
		// locking���� �ʴ� ����, ������ ��� pll �����͸� setting�ϰų�,  system power on/off�ÿ� �߻��Ѵ�.
		// �� ���� ���� 3�̰ų� b���ȴ�.			
	//		TestData=0x60; break;	// 27D(s)�� ��� 0x60 read��.
	//	case SAMSUNG_TCPN9082DA27C:	// samsung NTSC ����Ʃ��.
		// pll locking�� ����� �����Ϻ����� 7�̴�. 	2.13 by LKE ����.
		// ---> note:���׳��� ����ȵǾ ,Pll Locking�ȴ�.
		// locking���� �ʴ� ����, ������ ��� pll �����͸� setting�ϰų�,  system power on/off�ÿ� �߻��Ѵ�.
		// �� ���� ���� 3�̰ų� b���ȴ�.		
	//		TestData=0x70; break;	
	//	default:
	//		TestData=0x50; break;
	//}
	//---------------	
	while(1)
	{
			BackUp1=TunerDataCatch();
			//-------------// Tuner�� Disable�Ǿ� �ִ� ��� �ٽ� �츰��.  --> by LKE 2.14
			if((NoTunerFlag)&&(BackUp1!=0xff)) NoTunerFlag=1;	

			//----------------// Ʃ�ʰ� ���� �Ҵɵ� ��� Tuner Disable��Ų��. //--> by LKE 2.14
			if(BackUp1==0xff) 
			{		
				///BYTE tmptest=0;
				if(TunerDataCatch()==0xff) tmptest++;
				if(TunerDataCatch()==0xff) tmptest++;

				if(tmptest>=2)
				{		// Tuner disable ������ �߻��� ���.
					errorflag=0x80; 
					if(NoTunerFlag);
					else  NoTunerFlag=1;
					return(BackUp1);
				}
			}
			//---------------------
			if(i>3)
			{ 	// Tuner Spec�̿��� �����Ͱ� �� Ʃ�ʰ� �� �������� ���������� ���ϴ� ���� ���� .
					errorflag=0x01;
					return(BackUp1);
			}
			if(((BackUp1&0xF0) != 0x50)&&((BackUp1&0xF0) != 0x60) &&((BackUp1&0xF0) != 0x70) )
			{	// Phase LOCK Fail
					i++;
					continue;
			}
			else	
			{	// Phase Lock Ok�� ��� Ʃ�� �����͸� �ٽ��ѹ� Ȯ���� �� �װ��� �����Ѵ�.
				BackUp2=TunerDataCatch();
				if(BackUp1==BackUp2) 
				{// �ٽ��ѹ� Ȯ���Ѵ�.
					errorflag=0x00; 	// Sucess!!
					return(BackUp1);
				}
			}
	}

}



// Fc<Fw�� ��쿡 ����Ѵ�.  LKE
//  Phase Lock�ǰ�, Power ON reset Status����üũ�Ѵ�. LKE 1.24
void WriteTuner(unsigned char DivH,unsigned char DivL,unsigned char Band)
{	
	xdata BYTE count = 0;
	if(NoTunerFlag) return;
	while(count<I2CErrorTry)
	{
		++count;
		if(BTC_START_I2C(TunerAddr))		continue;	//0xc2
		if(BTC_WriteData(DivH))			continue;
		if(BTC_WriteData(DivL))			continue;
		#ifdef TunerRefDiv512
		if(CURRENT_TUNNER==LGINOTEK_TAPC_H701F)
		{
			if(BTC_WriteData(0xC6))			continue;	//Freq.step:62.5KHz
		}
		else
		{
			if(BTC_WriteData(0xCE))			continue;//2004-01-16//TunerRefDiv512(Freq.step:62.5KHz)
		}
		#else
		if(BTC_WriteData(0xCC))			continue;//TunerRefDiv640
		#endif
		// I/O port control !!!
		if(BTC_WriteData(Band))			continue;
		
		BTC_STOP_I2C();	
	}
//	delay5m(TUNER_STABLE_TIME);
}

// Ʃ�ʸ� Disable��ų���� �Ǵ��ϱ� ���� ��ƾ.
//
// ����� : �̷�ƾ�� system�� Power�� On �� ������ �ѹ� �� �������ش�. 
// Tuner Enable --> NoTunerFlag=0
// Tuner Disable --> NoTunerFlag=1
void TunerTest() 
{	
	xdata BYTE tmp;
	NoTunerFlag=0;
	
	SetTuner((WORD)0x2020);	// ������ PLL Divider�� �����Ѵ�.

	// SetTuner�Ŀ� errorflag�� ���¸� �о Tuner�� Disable��ų���� �����Ѵ�.

	BTC_START_I2C(TunerAddr+1);
	tmp=(BYTE)BTC_ReadDataNAK();
	BTC_STOP_I2C();

	if(tmp==0xff) NoTunerFlag=1;	// Tuner ����Ǿ� ���� ������쿡 set��Ų��.
	else	NoTunerFlag=0;

}

// PLL Divider value�� Tuner Parameter�� Tuner�� �����Ѵ�.
// 1��16�� : ��� ����Ī ������ ����.(Ʃ�ʺ��� �����Ͽ� ���õǵ��� ��.)
// 1��16�� : SAMSUNG_TCPQ9091PD28L(SamSung ����Ʃ��)������ ���� �ڵ� �߰�.
//#define sntsc_VHF 0x1090	
//#define sntsc_UHF 0x2710	
//#define spal_VHF 0x1075	
//#define spal_UHF 0x278a	
void SetTuner(unsigned int Divider)
{
	xdata unsigned char i,j,k;

	i = (unsigned char)(Divider >> 8);
	j = (unsigned char)Divider;

	switch(CURRENT_TUNNER)
	{
		//------------------------------------------
		// SAMSUNG_TCPN9082DA27C Tuner Spec����(ntsc) 
		// Band Switching�� ���� ���� ������.			 Fosc=Frf+Fif(45.75Mhz)	PLL Divider��ȯ��.
		// VHF Low: 	55.25Mhz		~ 	163.25Mhz  --> 101Mhz ~ 209Mhz    ---> 0x07e4 ~ 0x1054
		//                          sntsc_VHF 166.25Mhz   --> 212Mhz --------------> 0x1090
		// VHF High: 	169.25Mhz 	~ 	451.25Mhz  --> 215Mhz ~ 497Mhz    ----> 0x10cc ~ 0x26d4
		//                          sntsc_UHF 454.25Mhz   --> 500Mhz --------------> 0x2710
		// UHF       :  457.25Mhz 	~ 	855.25Mhz  --> 503Mhz ~ 901Mhz    ---> 0x274c ~ 0x4664
		// freq range: 0x07e4 ~ 0x4664 --> spec ������ ����� ������ ���� ������.

//		case SAMSUNG_TCPN9082DA27C:	// Ʃ�� ���� : (SAMSUNG_TCPQ9091PD27C:SamSung Ntsc����Ʃ��.)

//			if(Divider < sntsc_VHF)				k=0xa0;
//			else if(Divider < sntsc_UHF)	k=0x90;
//			else													k=0x30;
//		break;
		
		//------------------------------------------
		// SAMSUNG_TCPQ9091PD27D Tuner Spec����(pal/secam) 
		// Band Switching�� ���� ���� ������.			 Fosc=Frf+Fif(38.9Mhz)	             PLL Divider��ȯ��.
		// VHF Low: 	48.25Mhz	~	168.25Mhz  --> 87.15Mhz ~ 207.15Mhz    ---> 0x06cf ~ 0x102f (at divide 640)
		//                          spal_VHF 171.75Mhz   --> 210.65Mhz --------------> 0x1075
																					// [0x0A84(at divide 512)]
		// VHF High: 	175.25Mhz 	~ 	463.25Mhz  --> 214.15Mhz ~ 502.15Mhz    ----> 0x10bb ~ 0x273a
		//                          spal_UHF 467.25Mhz   --> 506.15Mhz --------------> 0x278a
																					// [0x1CF4(at divide 512)]
		// UHF       :  471.25Mhz 	~ 	855.25Mhz  --> 510.15Mhz ~ 894.15Mhz    ---> 0x27da ~ 0x45db
		// freq range: 0x06cf ~ 0x45db --> spec ������ ����� ������ ���� ������.
		
		case SAMSUNG_TCPQ9091PD27D:	// Ʃ�� ���� : (SAMSUNG_TCPQ9091PD27D:SamSung Pal-Multi ����Ʃ��.)		
			
		#if 0	//���� 27D(S)
			if(Divider < spal_VHF)				k=0xa0;
			else	if(Divider < spal_UHF)	k=0x90;
			else													k=0x30;
		#else	// ...27(T)
			if(Divider < spal_VHF)				k=0x41;
			else	if(Divider < spal_UHF)	k=0x42;
			else													k=0x48;
		#endif

			#if 0//(NTSC_COUNTRY==0)
			switch(ColorSystem) 
			{
				case BTC_PAL:
				case BTC_PAL_BG:
				case BTC_PAL_I:
				case BTC_PAL_DK:
				case BTC_SECAMDK:	//Audio���ð� ����Ǳ� ������ �̺κп� �����Ͽ���. -->Decoder������ ���� �ٶ�.
					k+=0x01;
					break;
				case BTC_SECAM:					
				case BTC_SECAML:
					k+=0x03;					
					break;
				case BTC_SECAMLL:
					k+=0x02;
					break;

				default: //k+=0x02;//test
						//	LED_OFF;
					break;
			}

			if(xEEPROMBuffer[SystemCountry]==3)
			{		// ������ ������ ���.
				if( Divider < 0x7b0)	{k-=0x03; k+=0x02;}
			}		
			#endif
			
		break;
		
		//------------------------------------------
//		case SAMSUNG_TCPQ9091PD28L:	// Ʃ�� ���� : (SAMSUNG_TCPQ9091PD28L:SamSung ����Ʃ��)
			
//			if(Divider < VHF1)				k=0x01;		// VHF LOW
//			else	if(Divider < UHF1)	k=0x02;		// VHF HIGH
//			else											k=0x08;		// UHF
			
//			#if 0
//			switch(ColorSystem) {			// Tuner Color System Setting.
//				case BTC_PAL:
//				case BTC_PAL_BG:
//				case BTC_PAL_I:
//				case BTC_PAL_DK:
//				case BTC_SECAMDK:	//Audio���ð� ����Ǳ� ������ �̺κп� �����Ͽ���. -->Decoder������ ���� �ٶ�.
//					k+=0x40;
//					break;
//				case BTC_SECAM:					
//				case BTC_SECAML:
//					k+=0xC0;
//					break;
//				case BTC_SECAMLL:
//					k+=0x80;
//					break;
//			}
//			#endif
//		break;
		
		//------------------------------------------
//		case LGINOTEK_TAPC_H701F:	// LG Ntsc���� Ʃ��.
//			if(Divider < VHF)				k=0x01;		// Low Band Control value
//			else	if(Divider < UHF)	k=0x02;		// Mid Band Control value
//			else										k=0x08;		// High Band Control value

//		break;
		//------------------------------------------
	}
	
	
	if(Divider >= OLDDivider) WriteTuner(i,j,k);	// Fw >= Fc�� ����� PLL Setting
	else WriteTun1(i,j,k);		// Fc > Fw�� ����� PLL Setting

	// if(abs(Divider-OLDDivider) > (WORD)1000) delay5m(20);
	OLDDivider= Divider;	// Final PLL Setting Value�� �����Ѵ�.
}


// Channel Table�� ���ǵ� PLL Divider Value�� �����Ѵ�.
/*  memory save  2003.6.3
WORD GetPLLValue()
{	
	xdata WORD *p;

	if(CheckChCATV(xEEPROMBuffer[CurrentChannel])==0) 	// Air-TV�� ���
		p= AIR_TAB[CountryToChannel[xEEPROMBuffer[SystemCountry]]]+GetRealChannel(xEEPROMBuffer[CurrentChannel]);
	else						// Cable-TV�� ���
		p=CATV_TAB[CountryToChannel[xEEPROMBuffer[SystemCountry]]]+GetRealChannel(xEEPROMBuffer[CurrentChannel]);	
		
	return *p;

}
*/


//5mS ������Ų�� ��𿡼����� �۵��ϸ� ���η����� ������Ű�� ������ �ϹǷ�  �ʿ��ѵ������� ����Ѵ�.
void idelay5m(BYTE time)
{
	 DelayTimer=time;
	 while(DelayTimer!=0) {NOP;}
}


//bit	testI2Cflag=0;	//test

void TunerProcess(void)
{
	xdata BYTE FineTuneValue; 
	xBYTE temp;
//	xBYTE	SearchCNT;
	static bit	SoundMuteChannelChange=0;

	if(PowerOnsequence < DisplayLightOnstatus) return;
	if(CurrentFunction!=4&&CurrentFunction!=7&&CurrentFunction!=10) return;
	
	++SoundMuteTvTimer;
	
	if(SoundMuteTvTimer>=0xFF) SoundMuteTvTimer=0xFE;
	
	if(SoundMuteTvTimer>=50 && !SoundMuteOnFlag)
	{
		if(SoundMuteChannelChange && !KeyContinueFlag)
		{
			SoundMuteChannelChange=0;
			
			MUTEOFF;	//main background mute
			
			if(PipOnOffFlag&&!PipMuteTimer)	PIPMuteOff;
			PutVolumePWM();
			Mute_SoundOn;	//Sound On~~
		}
	}
	if(SoundMuteTvTimer>=50 && SoundMuteOnFlag) MUTEOFF;
	//else if(SoundMuteTvTimer>=10)
	//else if(SoundMuteTvTimer>=2)
	//{
		if(TunerProcessing==1) TunerProcessing=2;
	//}
	
	switch(TunerProcessing)
	{
		case 0://Not process or Remocon Tenkey process
			break;

		case 1://Volume Mute
//					DBGputs("TunerProcessing 1");
			Mute_SoundOff;
			MUTEON;	//main background mute
			//LCDMute(0,1);

			TunerProcessTimer=1;
			break;
			
		case 2://Ʃ�ʸ� �����Ѵ�.
//					DBGputs("TunerProcessing 2");
			if(TunerProcessTimer) break;		
						
			SetToMono();
			SoundProcessStatus=0;

			ChannelScanPointer=xEEPROMBuffer[CurrentChannel];
			ChannelAdd_Del = CheckChMask(xEEPROMBuffer[CurrentChannel]);	//ChannelAdd_Del ��� �����???
							
			ViewCurrentChannel();	//  Tuner�����ϰ�, Channel OSD�� Display

			#ifdef	USE_remocon			
			ReceiveRemoconCount = 0;
			#endif
			
			//if(!KeyContinueFlag)	SoundMuteChannelChange=1;
			SoundMuteChannelChange=1;
			SoundMuteTvTimer=0;
		 	TunerProcessing = 3;				
			if(MENUstatus!=TVchannelDisplay) return;//

			OSDWindows = TunerSubWindow;
			if(CurrentFunction==Tuner_mode)			OSDcharacters = ChannelNumChars;
			else																OSDcharacters = PipRgbTunerChars;
			OSDstatus=TVchannelDisplay;
		
			break;
		
		case 3://�α� ä���� ã�´�.	
//			DBGputs("TunerProcessing 3");
//			DBGputs("xEEPROMBuffer[CurrentChannel]= 0x");DBGputss(xEEPROMBuffer[CurrentChannel]);	DBGputs("\n");
//			DBGputss(ChannelScanPointer);

			
			MspSelect();  	//sound (pal DK or I..) �ڵ��ν�����//2004-04-09
			
			//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++	
			#ifndef	FrequncyTableType
			//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++	
			///////////////////////////////////////////////////////////////////////
			#if defined (USE_NTSCtuner)
			///////////////////////////////////////////////////////////////////////
			if(!UpDownChannel) 
			{  
				//DBGputs(" Up Scan");//up key �ƴ�, �׳� ���� ä�� üũ..
				if(++ChannelScanPointer >= CHANNEL_LIMIT) 	ChannelScanPointer = 0;
				
				if(ChannelScanPointer==xEEPROMBuffer[CurrentChannel])	UpDownChannel=1;
			}
			else 
			{		
				//DBGputs(" Down Scan");	//down key �ƴ�, �׳� �Ʒ��� ä�� üũ..
				if(--ChannelScanPointer == 0xFF) ChannelScanPointer = CHANNEL_LIMIT-1; // Next Prog number Check --> Final Prog Number Over�ΰ��� Check
				//0���� 1�����Ͽ� 0xff�� �ɶ�...
				
				if(ChannelScanPointer==xEEPROMBuffer[CurrentChannel])
				{
					UpDownChannel=0;
					TunerProcessing=9;
					return;
				}			
			}

	 		if(CheckChMask(ChannelScanPointer)==0x00)
			{
				if(!UpDownChannel)	
				{
					Frontchannel=ChannelScanPointer;
					ChannelScanPointer=xEEPROMBuffer[CurrentChannel];
					UpDownChannel=1;
					TunerProcessing=3;
				}
				else
				{
					Backchannel=ChannelScanPointer;
					UpDownChannel=0;
					TunerProcessing=9;
				}
			}

			///////////////////////////////////////////////////////////////////////
			#elif defined(USE_PALSECAMtuner) && !defined(FrequncyTableType)
			///////////////////////////////////////////////////////////////////////
			//2004-06-10,by thkim :	Pal Channel �� ntsc�� �ٸ��� ����(�յ�ä�� �˻���� ����)
			if(UpDownChannel==1&&Remote1keyFlag==0) //upKey
			{  
				if(++ChannelScanPointer >= CHANNEL_LIMIT) 	ChannelScanPointer = 0;
			}
			else if(UpDownChannel==0&&Remote1keyFlag==0)  //downKey
			{		
				if(--ChannelScanPointer == 0xFF) ChannelScanPointer = CHANNEL_LIMIT-1; // Next Prog number Check --> Final Prog Number Over�ΰ��� Check
				//0���� 1�����Ͽ� 0xff�� �ɶ�...
				
				if(ChannelScanPointer==xEEPROMBuffer[CurrentChannel])
				{
					TunerProcessing=9;
					return;
				}			
			}
			NotSearchCHflag=0;
			
	 		if(CheckChMask(ChannelScanPointer)==0x00 && Remote1keyFlag==0)
			{
				if(UpDownChannel==1) //upKey
				{
					Frontchannel=ChannelScanPointer;
				}
				else //downKey
				{
					Backchannel=ChannelScanPointer;
				}
				//NotSearchCHflag=0;
				SearchCNT=0;
				TunerProcessing=9;
			}
			else if(CheckChMask(ChannelScanPointer)==0x01)
			{
				
				SearchCNT++;
				if(SearchCNT>=(CHANNEL_LIMIT+1)) 
				{
					TunerProcessing=9;
					SearchCNT=0;
					xEEPROMBuffer[PreChannel]=Frontchannel=Backchannel=0;
					NotSearchCHflag=1;
				}
				else TunerProcessing=3;
			}
			
			//�����ܿ���, (ä��,preCH,chAddDel)�� ���� ��������...
			if(Remote1keyFlag==1 && UpDownChannel2==0)
			{	//����  üũ
				if(++ChannelScanPointer >= CHANNEL_LIMIT) 	ChannelScanPointer = 0;
				if(CheckChMask(ChannelScanPointer)==0x00)
				{
					Frontchannel=ChannelScanPointer;
					
					ChannelScanPointer=xEEPROMBuffer[CurrentChannel];
					UpDownChannel2=1;
				}
				TunerProcessing=3;
			}
			else if(Remote1keyFlag==1 && UpDownChannel2==1)
			{	//�Ʒ��� üũ
				if(--ChannelScanPointer == 0xFF) ChannelScanPointer = CHANNEL_LIMIT-1;
				if(CheckChMask(ChannelScanPointer)==0x00)
				{
					Backchannel=ChannelScanPointer;
					Remote1keyFlag=0;
					
					ChannelScanPointer=xEEPROMBuffer[CurrentChannel];
					UpDownChannel2=0;
				}
				TunerProcessing=9;
			}
			#endif
			//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
			#elif defined(USE_PALSECAMtuner) && defined(FrequncyTableType)
			//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
			if(!UpDownChannel) 
			{  
				//DBGputs(" Up Scan");//up key �ƴ�, �׳� ���� ä�� üũ..
				if(++ChannelScanPointer >= CHANNEL_LIMIT) 	ChannelScanPointer = 0;
				
				if(ChannelScanPointer==xEEPROMBuffer[CurrentChannel])	UpDownChannel=1;
			}
			else 
			{		
				//DBGputs(" Down Scan");	//down key �ƴ�, �׳� �Ʒ��� ä�� üũ..
				if(--ChannelScanPointer == 0xFF) ChannelScanPointer = CHANNEL_LIMIT-1; // Next Prog number Check --> Final Prog Number Over�ΰ��� Check
				//0���� 1�����Ͽ� 0xff�� �ɶ�...
				
				if(ChannelScanPointer==xEEPROMBuffer[CurrentChannel])
				{
					UpDownChannel=0;
					TunerProcessing=9;
					return;
				}			
			}

	 		if(CheckChMask(ChannelScanPointer)==0x00)
			{
				if(!UpDownChannel)	
				{
					Frontchannel=ChannelScanPointer;
					ChannelScanPointer=xEEPROMBuffer[CurrentChannel];
					UpDownChannel=1;
					TunerProcessing=3;
					//DBGputs(" UpDownChannel==0->1 TunerProcessing=3;");
				}
				else
				{
					Backchannel=ChannelScanPointer;
					UpDownChannel=0;
					TunerProcessing=9;
					//DBGputs(" UpownChannel==1->0 TunerProcessing=9;");
				}
			}
			//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++	
			#endif
			//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++	
    
					#ifdef TestCH
					//test
					{
						extern unsigned int cnt,up_cnt,dn_cnt;	
						
						cnt++;
						if(UpDownChannel==1)	up_cnt++;
						else					dn_cnt++;
					}
					#endif
			
			break;

	
		case 9:		//���� ä���� eeprom�� �����Ѵ�.
//					DBGputs("TunerProcessing 9");
//			DBGputchar('9');
			EepromSetQue(CurrentChannel_adr,xEEPROMBuffer[CurrentChannel]);
			
			SearchCNT=0;
			
			//if( AFTenable && (!CheckChFineTune(xEEPROMBuffer[CurrentChannel])) ) //auto finetune�̸�..
			if(0)
			{
				TunerProcessing = 10;
				AutoFinePointer=0;
				FineTuneValue=GetFineTune(xEEPROMBuffer[CurrentChannel]);
				TunerProcessTimer=10;
			}			
			else TunerProcessing=0;//Not BUSY!!
			
			if(	(TvMenuNum!=tvmenu_channel_edit)&&
				(TvMenuNum!=tvmenu_auto_setup)  &&
				(CurrentFunction==4)			// TV full screen
			  ) InvertOn;
			  
					
					#ifdef TestCH
					//test
					{
						extern unsigned int cnt,up_cnt,dn_cnt;	
						
						DBGputss(cnt>>8); DBGputss(cnt); DBGputs("  == cnt"); 
						DBGputss(up_cnt>>8); DBGputss(up_cnt); DBGputs("  == UP_cnt"); 
						DBGputss(dn_cnt>>8); DBGputss(dn_cnt); DBGputs("  == DOWN_cnt"); 
					}
			  		#endif
			
			MspSelect();  	//sound (pal DK or I..) �ڵ��ν�����//2004-04-09
			  
			break;							
		

		
		case 10://Tuner adc check  
//					DBGputs("TunerProcessing 10");
			if(TunerProcessTimer) break;
//			DBGputchar('A');			
			//temp = ReadTuner()&0x07;

			temp = TunerDataCatch();
//			DBGputss(temp);					
			
			#ifndef FrequncyTableType	//+++++++++++++++++++
			
			#if defined(USE_NTSCtuner)
			if((temp&0x07)==2) //	center
			{
				xdata WORD addr;
//				DBGputs("center");								
		  	if(AntenaFlag==ANTENA_CABLE) 	addr=ep_ChannelStartCatv+2*xEEPROMBuffer[CurrentChannel];  		
		  	else 							addr=ep_ChannelStartAir+2*xEEPROMBuffer[CurrentChannel];	
				EepromSetQue(addr+1,FineTuneValue);		
				TunerProcessing = 19;  //����� ã��
			}
			#elif defined(USE_PALSECAMtuner)
			if((temp&0x47)==0x42) // center
			{	//2004-06-03
				xBYTE AddrEEp;
 				AddrEEp= EEPROM_Read(ep_ProgStart+xEEPROMBuffer[CurrentChannel]);		//ep_ProgStart	 :0x300
 				EepromSetQue(ep_ProgMemStart+(WORD)AddrEEp*PRMEMNUM+2,FineTuneValue);	//ep_ProgMemStart:0x400
				TunerProcessing = 19; //����� ã��				
			}
			#endif
			#else	//+++++++++++++++++++++++++++++++++++++++
			
			if((temp&0x07)==2) //	center
			{
				xdata WORD addr;
				addr=ep_ChannelStart+2*xEEPROMBuffer[CurrentChannel];	
				EepromSetQue(addr+1,FineTuneValue);		
				TunerProcessing = 19;  //����� ã��
			}
			#endif	//++++++++++++++++++++++++++++++++++++++			
			
			
			else //  ��Ʃ�� �ƴ�.
			{
				if(AutoFinePointer>=TvFineTuneValue_max) //��... ��Ʃ���� ����..
				{	
					#ifndef FrequncyTableType	//++++++++++++++++++++
					
					#if defined(USE_NTSCtuner)
						xdata WORD addr;

				  	if(AntenaFlag==ANTENA_CABLE) 	addr=ep_ChannelStartCatv+2*xEEPROMBuffer[CurrentChannel];  		
				  	else 							addr=ep_ChannelStartAir+2*xEEPROMBuffer[CurrentChannel];	
						EepromSetQue(addr+1,AftRangeTable[xEEPROMBuffer[SystemCountry]]);  //���� �� ����.
					#else
//todo			if(AntenaFlag==ANTENA_CABLE) 	addr=ep_ChannelStartCatv+2*xEEPROMBuffer[CurrentChannel];  		
//				  else 	addr=ep_ChannelStartAir+2*xEEPROMBuffer[CurrentChannel];	
//					EepromSetQue(addr+1,AftRangeTable[xEEPROMBuffer[SystemCountry]]);  //���� �� ����.
					#endif
					
					#else	//+++++++++++++++++++++++++
						xdata WORD addr;
				  	addr=ep_ChannelStart+2*xEEPROMBuffer[CurrentChannel];  		
					#endif	//++++++++++++++++++++++
				TunerProcessing = 19;		//aft end
				}
				else{
					TunerProcessing = 11;		//aft end
					}
			}	
			break;
		
		case 11:			//Ʃ�ʸ� �ٽ� Ʃ����. //set tunner fine tune	
//					DBGputs("TunerProcessing 11");
//			DBGputchar('B');
			if(AutoFinePointer==1) 
			{	//Fo�� ������� ��ũ�� �մ��� üũ.
				TunerProcessTimer=DecoderStableTime;
				TunerProcessing = 12;
			}
			else 
			{
				FineTuneValue=TunerFineValueProcess[AutoFinePointer];				
				SetFinePLL(xEEPROMBuffer[CurrentChannel],FineTuneValue);//
				//LED_OFF;idelay5m(50);LED_ON;idelay5m(50);LED_OFF;idelay5m(50);LED_ON;//test//2004-05-07 11:24����
				++AutoFinePointer;		
				TunerProcessTimer=10;
				TunerProcessing = 10;			
			}
			break;

		case 12:	
				
//					DBGputs("TunerProcessing 12");
			if(TunerProcessTimer) break;
//			DBGputchar('C');			
			CheckTVSignal(2);
			if(eTVSyncFlag) 
			{		// ���ڴ���  sync������ ���. --> �÷��� enable
				FineTuneValue=TunerFineValueProcess[AutoFinePointer];				
//				SetFinePLL(xEEPROMBuffer[CurrentChannel],SetFinePLL);
				SetFinePLL(xEEPROMBuffer[CurrentChannel],FineTuneValue);//
				//LED_OFF;idelay5m(150);LED_ON;idelay5m(50);LED_OFF;//test//2004-05-07 11:24����
				++AutoFinePointer;		
				TunerProcessTimer=10;
				TunerProcessing = 10;				
			}
			else 
			{			//sync�� ���� ���  �׳� ����.
				TunerProcessing = 19;		//aft end	
			}
			

			break;

		case 19:		//aft end
//					DBGputs("TunerProcessing 19");
			TunerProcessing=0;// 
			#ifdef	USE_remocon
			ReceiveRemoconCount=0;//hanjaeduc//2003-12-26 8:18����
			#endif
			break;	


			
		#ifdef	USE_remocon
		case 7:
//					DBGputs("TunerProcessing 7");
		//hanjaeduc//2003-12-26 8:18����
		if(RemoconTenKeyTimer<=600) return;
		else
		{
			Mute_SoundOff;
			if(CurrentFunction==Tuner_mode && !RepeatCodeBit)	MUTEON;	//main background mute
			ChannelChange();
			
			if(CurrentFunction==PipRnT_mode)		PipChannelOSD();
			else		ChannelOSD(80,8);
			
			RemoconTenKeyTimer=0;
			ReceiveRemoconCount = 0;//
			MspSelect();
		}
		
/*			
			if(RemoconTenKeyTimer<=600) return;
			else
			{
				RemoconTenKeyTimer=0;
				TunerProcessing = 0;		
				OSDWindows = TunerSubWindow;
				OSDcharacters = ChannelNumChars;
				OSDstatus=TVchannelDisplay;
				
				switch(SourceType)
				{
					#if defined(USE_NTSCtuner)
					case NTSC_AIR:
						if(RecmoconTVchannel<2) xEEPROMBuffer[NTSC_AIRTVCHANNEL_buf]=xEEPROMBuffer[NTSC_AIRTVCHANNEL_buf];
						else if(RecmoconTVchannel>69) xEEPROMBuffer[NTSC_AIRTVCHANNEL_buf]=xEEPROMBuffer[NTSC_AIRTVCHANNEL_buf];
						else if(xEEPROMBuffer[NTSC_AIRTVCHANNEL_buf]!=RecmoconTVchannel){xEEPROMBuffer[NTSC_AIRTVCHANNEL_buf] = RecmoconTVchannel;TunerProcessing = 1;SoundMuteTvTimer=0;}
						else xEEPROMBuffer[NTSC_AIRTVCHANNEL_buf]=xEEPROMBuffer[NTSC_AIRTVCHANNEL_buf];
						break;	
					
					case NTSC_CATV:
						if(RecmoconTVchannel<1) xEEPROMBuffer[NTSC_CATVCHANNEL_buf]=xEEPROMBuffer[NTSC_CATVCHANNEL_buf];
						else if(RecmoconTVchannel>125) xEEPROMBuffer[NTSC_CATVCHANNEL_buf]=xEEPROMBuffer[NTSC_CATVCHANNEL_buf];
						else if(xEEPROMBuffer[NTSC_CATVCHANNEL_buf]!=RecmoconTVchannel) {xEEPROMBuffer[NTSC_CATVCHANNEL_buf]=RecmoconTVchannel;TunerProcessing = 1;SoundMuteTvTimer=0;}
						else xEEPROMBuffer[NTSC_CATVCHANNEL_buf]=xEEPROMBuffer[NTSC_CATVCHANNEL_buf];
						break;
				
					#elif defined(USE_PALSECAMtuner)
					case PAL_I:
						if(RecmoconTVchannel<1) xEEPROMBuffer[PAL_ITVCHANNEL_buf+SourceType]=xEEPROMBuffer[PAL_ITVCHANNEL_buf+SourceType];
						else if(RecmoconTVchannel>62) xEEPROMBuffer[PAL_ITVCHANNEL_buf+SourceType]=xEEPROMBuffer[PAL_ITVCHANNEL_buf+SourceType];
						else if(xEEPROMBuffer[PAL_ITVCHANNEL_buf+SourceType]!=RecmoconTVchannel) {xEEPROMBuffer[PAL_ITVCHANNEL_buf+SourceType]=RecmoconTVchannel;TunerProcessing = 1;SoundMuteTvTimer=0;}
						else xEEPROMBuffer[PAL_ITVCHANNEL_buf+SourceType]=xEEPROMBuffer[PAL_ITVCHANNEL_buf+SourceType];
						break;
					
					case PAL_BG:
					case SEC_BG:
						if(RecmoconTVchannel<1) xEEPROMBuffer[PAL_ITVCHANNEL_buf+SourceType]=xEEPROMBuffer[PAL_ITVCHANNEL_buf+SourceType];
						else if(RecmoconTVchannel>106) xEEPROMBuffer[PAL_ITVCHANNEL_buf+SourceType]=xEEPROMBuffer[PAL_ITVCHANNEL_buf+SourceType];
						else if(xEEPROMBuffer[PAL_ITVCHANNEL_buf+SourceType]!=RecmoconTVchannel) {xEEPROMBuffer[PAL_ITVCHANNEL_buf+SourceType]=RecmoconTVchannel;TunerProcessing = 1;SoundMuteTvTimer=0;}
						else xEEPROMBuffer[PAL_ITVCHANNEL_buf+SourceType]=xEEPROMBuffer[PAL_ITVCHANNEL_buf+SourceType];
						break;
					
					case PAL_DK:
					case SEC_DK:	
						if(RecmoconTVchannel<1) xEEPROMBuffer[PAL_ITVCHANNEL_buf+SourceType]=xEEPROMBuffer[PAL_ITVCHANNEL_buf+SourceType];
						else if(RecmoconTVchannel>100) xEEPROMBuffer[PAL_ITVCHANNEL_buf+SourceType]=xEEPROMBuffer[PAL_ITVCHANNEL_buf+SourceType];
						else if(xEEPROMBuffer[PAL_ITVCHANNEL_buf+SourceType]!=RecmoconTVchannel) {xEEPROMBuffer[PAL_ITVCHANNEL_buf+SourceType]=RecmoconTVchannel;TunerProcessing = 1;SoundMuteTvTimer=0;}
						else xEEPROMBuffer[PAL_ITVCHANNEL_buf+SourceType]=xEEPROMBuffer[PAL_ITVCHANNEL_buf+SourceType];
						break;
					
					case SEC_L:
						if(RecmoconTVchannel<1) xEEPROMBuffer[PAL_ITVCHANNEL_buf+SourceType]=xEEPROMBuffer[PAL_ITVCHANNEL_buf+SourceType];
						else if(RecmoconTVchannel>75) xEEPROMBuffer[PAL_ITVCHANNEL_buf+SourceType]=xEEPROMBuffer[PAL_ITVCHANNEL_buf+SourceType];
						else if(xEEPROMBuffer[PAL_ITVCHANNEL_buf+SourceType]!=RecmoconTVchannel) {xEEPROMBuffer[PAL_ITVCHANNEL_buf+SourceType]=RecmoconTVchannel;TunerProcessing = 1;SoundMuteTvTimer=0;}
						else xEEPROMBuffer[PAL_ITVCHANNEL_buf+SourceType]=xEEPROMBuffer[PAL_ITVCHANNEL_buf+SourceType];
						break;
						
					#endif
				}
				RecmoconTVchannel=0;
				ReceiveRemoconCount = 0;
			}
*/			
			break;
		#endif

		case 20:		//�ڵ����� �г��� ã�´�. 
//					DBGputs("TunerProcessing 20");
			//air search�ϱ����� �ʱ�ȭ
			#ifdef USE_UART
			DBGputs("AutoSearch Start");
			#endif
			
			Mute_SoundOff;
			NowAutoChannelSearching=1;
			if(AntenaFlag==ANTENA_CABLE) 	//catv(=0x01)
			{
				TunerProcessing=23;	return;	
			}
			
			#ifdef USE_UART
			DBGputs("Air Start");
			#endif
			
			SearchChannel_Count=0;
			SearchChannel_Total=TvLimitTable[3*CountryToChannel[xEEPROMBuffer[SystemCountry]]+1];					    // max
			SearchChannel_Total=SearchChannel_Total-TvLimitTable[3*CountryToChannel[xEEPROMBuffer[SystemCountry]]+2]+1; // min

		//	PWMMax=TV_MIN+TV_Total;
		#if defined(USE_PALSECAMtuner)&&!defined(FrequncyTableType)
			ProgNo=0;
		#else
			ProgNo=1;		//search ���̶�°��� �˸���.
		#endif

//			p = AIR_TAB[CountryToChannel[xEEPROMBuffer[SystemCountry]]];
//			TDivider = *p-AftRangeTable[xEEPROMBuffer[SystemCountry]];	
//			TvPllOk(TDivider);		//tuner�� ���� ���� ���ļ��� ������.

			TunerProcessTimer=DecoderStableTime;
			TunerProcessing=21;

			break;

		case 21:		//tuner pll set	
//					DBGputs("TunerProcessing 21");		
			if(TunerProcessTimer) break;
//			DBGputss(SearchChannel_Count);
//			DBGputchar(' ');
			
			if(SearchPll_set())
			{			//pll set success
				TunerProcessTimer=DecoderStableTime;
				TunerProcessing=22;
			}
			else
			{			//no pll data
				SearchChannel_Count++;
			}
			break;
		
		case 22:		//check TV signal
//					DBGputs("TunerProcessing 22");
			if(TunerProcessTimer) break;

			//////////////////////////
			idelay5m(50);	// �˻� �ð� ������//2003-11-17
			//////////////////////////

				SearchSave();
				SearchChannel_Count++;		
				if((SearchChannel_Count < SearchChannel_Total)
					#if defined(USE_PALSECAMtuner)&&!defined(FrequncyTableType)
				&&(ProgNo < CHANNELMEMORYMAX) 
					#endif	
				)
				{			
					TunerProcessing=21;
				}
				else  
				{		//end of channel
					TunerProcessing=26;			//TO do  ���� ���� ������ �ؾ� ��.			
				}					
			break;

			
		case 23:		//cable search�ϱ����� �ʱ�ȭ  
//					DBGputs("TunerProcessing 23");

			#ifdef USE_UART
			DBGputs("Cable Start");
			#endif
			
			SearchChannel_Count=0;
			SearchChannel_Total=CatvLimitTable[3*CountryToChannel[xEEPROMBuffer[SystemCountry]]+1];		// max
			SearchChannel_Total=SearchChannel_Total-CatvLimitTable[3*CountryToChannel[xEEPROMBuffer[SystemCountry]]+2]+1;		// min

//			p = CATV_TAB[CountryToChannel[xEEPROMBuffer[SystemCountry]]];
//			TDivider = *p-AftRangeTable[xEEPROMBuffer[SystemCountry]];	
//			TvPllOk(TDivider);		//tuner�� ���� ���� ���ļ��� ������.

//			AntenaFlag=ANTENA_CABLE;
			TunerProcessTimer=DecoderStableTime;
			TunerProcessing=24;
			break;	
					
		case 24:		//tuner pll set 
//					DBGputs("TunerProcessing 24");
			if(TunerProcessTimer) break;
			
			//DBGputss(SearchChannel_Count);
			//DBGputchar(' ');
			
			if(SearchPll_set())	//pll set success
			{	
				TunerProcessTimer=DecoderStableTime;
				TunerProcessing=25;
			}
			else 				//no pll data 
			{			
				SearchChannel_Count++;		
			}
			break;			
		
		case 25:		//check CATV signal  
//					DBGputs("TunerProcessing 25");
			if(TunerProcessTimer) break;
			SearchSave();
			
			//////////////////////////////////////////
			idelay5m(50);	// �˻� �ð� ������
			//////////////////////////////////////////
			
			SearchChannel_Count++;		
			if((SearchChannel_Count < SearchChannel_Total)
					#if defined(USE_PALSECAMtuner)&&!defined(FrequncyTableType)
				&&(ProgNo < CHANNELMEMORYMAX) 
					#endif				
			  )
			{	TunerProcessing=24;	}
			else{		//end of channel
				TunerProcessing=26;	}
			break;
	
		case 26: 	// ���� ���� ������ �ؾ� ��.
//					DBGputs("TunerProcessing 26");
				if(TunerProcessTimer) break;	
				
				#ifndef FrequncyTableType	//++++++++++++++++++
				#if defined(USE_PALSECAMtuner)	//==================
				if(ProgNo < CHANNELMEMORYMAX) 
				{
					FillRestChannel();
					TunerProcessTimer=6;
					TunerProcessing=26;		
				}
				
				#else	//==================
				if(SearchChannel_Count < 128)
				{
					FillRestChannel();
				 	TunerProcessing=26;				
				}
				#endif	//==================
				#else	//++++++++++++++++++
				if(SearchChannel_Count < CHANNELMEMORYMAX)
				{
					FillRestChannel();
				 	TunerProcessing=26;				
				}
				#endif	//++++++++++++++++++
				else TunerProcessing=29;		
				break;
				
		case 29:		//autosearch �Ϸ� . 
//					DBGputs("TunerProcessing 29");
			ProgNo=0;
			KEY_value=MenuKey;	//���� �޴��� ���� 
			NowAutoChannelSearching=0;
//			AntenaFlag=xEEPROMBuffer[Antena];
			break;		

		case 30:	// Single channel change
//					DBGputs("TunerProcessing 30");
			if(SingleCH>=CHANNEL_MIN && SingleCH<=CHANNEL_MAX)
			{
				xEEPROMBuffer[CurrentChannel]=SingleCH-CHANNEL_MIN;
			}   
			
//			SingleCHflag=1;
			TunerProcessing=2;
			EepromSetQue(CurrentChannel_adr,xEEPROMBuffer[CurrentChannel]);
			break;

		default:
//					DBGputs("TunerProcessing default");
			break;
	}
}

#ifndef		FrequncyTableType	//++++++++++++++++++++++++++++++++++++++++++++

#if defined(USE_NTSCtuner)
Bool SearchPll_set()
{
  	xdata WORD 	TDivider,addr;
  	xdata unsigned short *p;
  	xdata BYTE  Mask;


	AutoChannelDisplay();

  	if(AntenaFlag==ANTENA_CABLE) 
  	{	
		addr=ep_ChannelStartCatv+2*SearchChannel_Count;
		p = CATV_TAB[CountryToChannel[xEEPROMBuffer[SystemCountry]]] + (WORD)SearchChannel_Count;	// Freq. Table�� ���� �װ�(PLL Divider Value)��  ã�Ƽ�,
		Mask=0x83;
  	}
  	else 
  	{
		addr=ep_ChannelStartAir+2*SearchChannel_Count;
		p = AIR_TAB[CountryToChannel[xEEPROMBuffer[SystemCountry]]] + (WORD)SearchChannel_Count;	// Freq. Table�� ���� �װ�(PLL Divider Value)��  ã�Ƽ�,
		Mask=0x81;
  	}
  	
		//---�Ｚ ntscƩ���� ��� ������ ����� ���������͸�--------
	if(CURRENT_TUNNER != SAMSUNG_TCPN9082DA27C);
	else{	// �ＺƩ�ʰ� ����Ǿ� �ִ� ��쿡, Low band 55.25Mhz�̸��� ���ļ��� ���͸��Ѵ�.(Ʃ�� ������ �����ϴ� ���ļ��̴�.)
		if(*p < 0x07E4){ 
			EepromSetQue(addr,Mask);		// TV Flag����.(Catv)  --> No Using
			EepromSetQue(addr+1,AftRangeTable[xEEPROMBuffer[SystemCountry]]);	// TV Fine Tune data�ʱ�ȭ..(Catv)
			return 0;				// Dummy�� ����� Skip�Ѵ�.
		}
	}
		//----���� ������ ���͸�.--------------------------------------------
	if(*p == 0){ 		// PLL Divider Value�� Dummy Data���� üũ�Ѵ�. 		// 1�� 16�� Dummy Check�ϵ��� �߰���.
		EepromSetQue(addr,Mask);		// TV Flag����.(Air-TV)  --> No Using
		EepromSetQue(addr+1,AftRangeTable[xEEPROMBuffer[SystemCountry]]);	// TV Fine Tune data�ʱ�ȭ..(Air-TV)
		return 0;				// Dummy�� ����� Skip�Ѵ�.
	}else TDivider = *p;			// Center Frequency

	TvPllOk(TDivider);
	return 1;
}

void SearchSave()
{
	xdata WORD 	addr;
//  	xdata unsigned short *p;
  	
  	if(AntenaFlag==ANTENA_CABLE) {	
		addr=ep_ChannelStartCatv+2*SearchChannel_Count;
//		p = CATV_TAB[CountryToChannel[xEEPROMBuffer[SystemCountry]]] + (WORD)SearchChannel_Count;	// Freq. Table�� ���� �װ�(PLL Divider Value)��  ã�Ƽ�,
  		}
  	else {
		addr=ep_ChannelStartAir+2*SearchChannel_Count;
//		p = AIR_TAB[CountryToChannel[xEEPROMBuffer[SystemCountry]]] + (WORD)SearchChannel_Count;	// Freq. Table�� ���� �װ�(PLL Divider Value)��  ã�Ƽ�,
  		}

	CheckTVSignal(5);

	if(eTVSyncFlag) // ���ڴ���  sync������ ���. --> �÷��� enable
	{
		if(AntenaFlag==ANTENA_CABLE)  EepromSetQue(addr,EnableCATV);		// enable/cable
		else 						  EepromSetQue(addr,EnableAIR);			// enable/air
		EepromSetQue(addr+1,AftRangeTable[xEEPROMBuffer[SystemCountry]]);	// default Fine Tune Data
	}
	else	 		// ���ڴ���  sync�������� ���� ���. --> �÷��� disable
	{
		//if (ExitCondionCheck(temp_cable)) return;	// �������� üũ 
		if(AntenaFlag==ANTENA_CABLE)  EepromSetQue(addr,DisableCATV);		// disable/cable
		else						  EepromSetQue(addr,DisableAIR);		// disable/air
		EepromSetQue(addr+1,AftRangeTable[xEEPROMBuffer[SystemCountry]]);	// default Fine Tune Data
	}
		
}

void FillRestChannel()
{
	xdata WORD 	addr;
	
	if(AntenaFlag)	addr=ep_ChannelStartCatv+(WORD)SearchChannel_Count*2;	// catv
	else			addr=ep_ChannelStartAir+(WORD)SearchChannel_Count*2;		// air
	
	EepromSetQue(addr,0x81);		// enable/cable

	#ifdef USE_UART
	DBGputss(SearchChannel_Count);	DBGputs("    fiLL!");
	#endif
	
	SearchChannel_Count++;
}
#else	//pal	--------------------------------------------------------------
Bool SearchPll_set()
{
  	xdata WORD 	TDivider;
  	xdata unsigned short *p;

//	addr=ep_ProgMemStart+PRMEMNUM*SearchChannel_Count;
	AutoChannelDisplay();
	
	/*
  	if(AntenaFlag==ANTENA_CABLE) {	
		p = CATV_TAB[CountryToChannel[xEEPROMBuffer[SystemCountry]]] + (WORD)SearchChannel_Count;	// Freq. Table�� ���� �װ�(PLL Divider Value)��  ã�Ƽ�,
  		}
  	else {
		p = AIR_TAB[CountryToChannel[xEEPROMBuffer[SystemCountry]]] + (WORD)SearchChannel_Count;	// Freq. Table�� ���� �װ�(PLL Divider Value)��  ã�Ƽ�,
  		}
  	*/	
  	p = AIR_TAB[CountryToChannel[xEEPROMBuffer[SystemCountry]]] + (WORD)SearchChannel_Count;	// Freq. Table�� ���� �װ�(PLL Divider Value)��  ã�Ƽ�,

  	
	//---�Ｚ ntscƩ���� ��� ������ ����� ���������͸�--------
	// �ＺƩ�ʰ� ����Ǿ� �ִ� ��쿡, Low band 55.25Mhz�̸��� ���ļ��� ���͸��Ѵ�.(Ʃ�� ������ �����ϴ� ���ļ��̴�.)
	if(CURRENT_TUNNER == SAMSUNG_TCPN9082DA27C)
		if(*p < 0x07E4)	return 0;
	else if(CURRENT_TUNNER ==SAMSUNG_TCPQ9091PD27D)	
		if(*p < 0x00580)	return 0;		//Low band 49.75Mhz�̸�//2004-05-04

	//----���� ������ ���͸�.--------------------------------------------	
	if(*p == 0)		// PLL Divider Value�� Dummy Data���� üũ�Ѵ�. 		// 1�� 16�� Dummy Check�ϵ��� �߰���.
		return 0;	// Dummy�� ����� Skip�Ѵ�.
	else 
		TDivider = *p;		// PLL Divider Value�� Divider�� �ε�.
	
	TvPllOk(TDivider);
	return 1;
}

void SearchSave()
{
	xdata WORD 	addr;
	
	addr=ep_ProgMemStart+PRMEMNUM*ProgNo;
	
	CheckTVSignal(5);

	if(eTVSyncFlag) 
	{		// ���ڴ���  sync������ ���. --> �÷��� enable
		if(AntenaFlag==ANTENA_CABLE)  EepromSetQue(addr,EnableCATV);	// enable/cable
		else 						  EepromSetQue(addr,EnableAIR);		// enable/air
		EepromSetQue(addr+1,SearchChannel_Count);	// Air-TV������ channel table offset����.
		EepromSetQue(addr+2,AftRangeTable[xEEPROMBuffer[SystemCountry]]);	// Fine tuning Data �ʱ�ȭ
		EepromSetQue(addr+3,0);	// reserve
		EepromSetQue(addr+4,0);	// channel name
		EepromSetQue(addr+5,0);	// channel name
		EepromSetQue(addr+6,0);	// channel name
		EepromSetQue(addr+7,0);	// channel name
		ProgNo++;		
		
		#ifdef USE_UART
		DBGputs("find !");
		#endif
	}
}

void FillRestChannel()
{
	xdata WORD 	addr;
	addr=ep_ProgMemStart+PRMEMNUM*ProgNo;
		
		EepromSetQue(addr,0x01);		// mask
		EepromSetQue(addr+1,SearchChannel_Count);	// Air-TV������ channel table offset����.
		EepromSetQue(addr+2,AftRangeTable[xEEPROMBuffer[SystemCountry]]);	// Fine tuning Data �ʱ�ȭ
//		EepromSetQue(addr+3,0);	// reserve
//		EepromSetQue(addr+4,0);	// channel name
//		EepromSetQue(addr+5,0);	// channel name
//		EepromSetQue(addr+6,0);	// channel name
//		EepromSetQue(addr+7,0);	// channel name
		ProgNo++;	
		//DBGputss(ProgNo);
		
		#ifdef USE_UART
		DBGputs("FillRestChannel");
		#endif
}
	
#endif
#else	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
Bool SearchPll_set()
{
  	xdata WORD 	TDivider,addr;
  	xdata unsigned short *p;
  	xdata BYTE  Mask;


	AutoChannelDisplay();

		addr=ep_ChannelStart+2*SearchChannel_Count;
		p = CATV_TAB[CountryToChannel[xEEPROMBuffer[SystemCountry]]] + (WORD)SearchChannel_Count;	// Freq. Table�� ���� �װ�(PLL Divider Value)��  ã�Ƽ�,
		Mask=0x83;
  	
		//---�Ｚ ntscƩ���� ��� ������ ����� ���������͸�--------
	if(CURRENT_TUNNER != SAMSUNG_TCPN9082DA27C);
	else{	// �ＺƩ�ʰ� ����Ǿ� �ִ� ��쿡, Low band 55.25Mhz�̸��� ���ļ��� ���͸��Ѵ�.(Ʃ�� ������ �����ϴ� ���ļ��̴�.)
		if(*p < 0x07E4){ 
			EepromSetQue(addr,Mask);		// TV Flag����.(Catv)  --> No Using
			EepromSetQue(addr+1,AftRangeTable[xEEPROMBuffer[SystemCountry]]);	// TV Fine Tune data�ʱ�ȭ..(Catv)
			return 0;				// Dummy�� ����� Skip�Ѵ�.
		}
	}
		//----���� ������ ���͸�.--------------------------------------------
	if(*p == 0){ 		// PLL Divider Value�� Dummy Data���� üũ�Ѵ�. 		// 1�� 16�� Dummy Check�ϵ��� �߰���.
		EepromSetQue(addr,Mask);		// TV Flag����.(Air-TV)  --> No Using
		EepromSetQue(addr+1,AftRangeTable[xEEPROMBuffer[SystemCountry]]);	// TV Fine Tune data�ʱ�ȭ..(Air-TV)
		return 0;				// Dummy�� ����� Skip�Ѵ�.
	}else TDivider = *p;			// Center Frequency

	TvPllOk(TDivider);
	return 1;
}

void SearchSave()
{
	xdata WORD 	addr;
  	
		addr=ep_ChannelStart+2*SearchChannel_Count;

	CheckTVSignal(5);

	if(eTVSyncFlag) // ���ڴ���  sync������ ���. --> �÷��� enable
	{
		EepromSetQue(addr,EnableCATV);		// enable/cable
		EepromSetQue(addr+1,AftRangeTable[xEEPROMBuffer[SystemCountry]]);	// default Fine Tune Data
	}
	else	 		// ���ڴ���  sync�������� ���� ���. --> �÷��� disable
	{
		EepromSetQue(addr,DisableCATV);		// disable/cable
		EepromSetQue(addr+1,AftRangeTable[xEEPROMBuffer[SystemCountry]]);	// default Fine Tune Data
	}
		
}

void FillRestChannel()
{
	xdata WORD 	addr;
	
	addr=ep_ChannelStart+(WORD)SearchChannel_Count*2;	// catv
	
	EepromSetQue(addr,0x81);		// enable/cable

	#ifdef USE_UART
	DBGputss(SearchChannel_Count);	DBGputs("    fiLL!");
	#endif
	
	SearchChannel_Count++;
}
#endif	//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

// Min���� Max Channel���� ������� Scan�ϸ鼭, Sync�� Detect�Ǵ����� �Ǵ��ϰ�, 
// Sync���¿� ����eeprom���� Program Edit������ sync�� ����Ǵ� ä�η� ���̺��� Update��Ų��.
// --> Fine Tune data�� 50���� �ʱ�ȭ �ȴ�.
// scan�Ϸ��Ŀ��� ������ Channel�� �ǵ�����.
// 1��16�� : Dummy Channel�� ���, Scan��  Skip�ϵ��� �����H.--> PAL Channel�� ��쿡 Dummy Channel�� ������.
/*
void AutoSearchChannel(void)
{	
	if(ColorSystem&NTSC)  	SimpleSearch();
	else	{
	xUCHAR SearchOK;
	xUCHAR AFTValue;
  	xUINT Divider,temp_pll;
  	unsigned short	*p,value;
	UCHAR	ProgNo,i;
	UCHAR	TV_Max,TV_Min,CATV_Max,CATV_Min;

//---------------Channel table total/max/min value Load ------------------------
  	//Addr=Read24c16(ep_SystemCountry);		// Country
	//TV_Total=TvLimitTable[3*CountryToChanel[SystemCountry]+0];		// total	// Air-TV
	TV_Max=TvLimitTable[3*CountryToChanel[SystemCountry]+1];		// max
	TV_Min=TvLimitTable[3*CountryToChanel[SystemCountry]+2];		// min
	//CATV_Total=CatvLimitTable[3*CountryToChanel[SystemCountry]+0];	// total	// CATV  
	CATV_Max=CatvLimitTable[3*CountryToChanel[SystemCountry]+1];	// max
	CATV_Min=CatvLimitTable[3*CountryToChanel[SystemCountry]+2];	// min
//--------------Audio Mute On--------------
	PutVolume(FALSE);

	PWMMax=TV_Max;
	PWMMin=TV_Min;
	PWMPtr=CHANNEL;
	RegBuffer[CHANNEL]=PWMMin;
	DisplayPWMScale(WIN3_L+1,WIN3_B-1,20);

//---------------AutoSearch�� �����ϱ� ���� PLL Data�� �����Ѵ�.---------------------
	i = Read24c16(ep_Currentchennel);		// Current Prog Number Read	
	if(CheckChCATV(i)==0) 	// Air-TV�� ���	// Prog No�� ���� ���� channel table offset�� ��� �Ѵ�.
			p= AIR_TAB[CountryToChanel[SystemCountry]]+GetRealChannel(i);
	else						// Cable-TV�� ���
			p=CATV_TAB[CountryToChanel[SystemCountry]]+GetRealChannel(i);	
	temp_pll = *p;		// Tuner PLL Divider Value	
//-----------------------------------------------------------


//------------------Air-TV Channel Table Scanning---------------------
	ProgNo=0;	// Program Number�ʱ�ȭ.
	PutString(7,2,"PR  0~");

	for(i=0; i < (TV_Max-TV_Min+1); i++){		// /1��16��
		KeyScan();
		if(KeyCode==MK_MENU) return;	
		// Min���� Max Channel���� ������� Scan�ϸ鼭, Sync�� Detect�Ǵ����� �Ǵ��ϰ�, 
		// Sync���¿� ����eeprom���� Program Edit������ Update�Ѵ�. 
		//ShowOSDChannel(0,i);		// OSD Channel Display(Air-TV Channel Display)	
		
		// Channel Table�� ���� Offset���
		//p = AIR_TAB[Addr] + (i - TV_Min);	// Freq. Table�� ���� �װ�(PLL Divider Value)��  ã�Ƽ�,
		p = AIR_TAB[CountryToChanel[SystemCountry]] + (UINT)i;	// Freq. Table�� ���� �װ�(PLL Divider Value)��  ã�Ƽ�,
		// Divider = *p;				// PLL Divider Value�� Divider�� �ε�.	
		
		if(*p == 0) 		// PLL Divider Value�� Dummy Data���� üũ�Ѵ�. 		// 1�� 16�� Dummy Check�ϵ��� �߰���.
			continue;	// Dummy�� ����� Skip�Ѵ�.
		else 
			Divider = *p;		// PLL Divider Value�� Divider�� �ε�.

//		ShowOSDChannel(0,i);		// OSD Channel Display(Air-TV Channel Display)	

		//----------���� Channel Setting�Ŀ� AFT���࿩�θ� üũ�Ѵ�.---------
		Timer8 = AUTO_SEARCH_TIME;	// Auto Search ���� Ž�� �ð� ����. = 0.5��	
		AFTValue=80;	SearchOK=0x00;
		SetTuner(Divider+(unsigned int)AFTValue-(unsigned int)80);
		value = SyncRead();	// Sync Status�� �Ǵ��ϱ� ���ؼ�, VPX_ASR �����Ѵ�.	
		if((value & 0x07) != 0x03){	//no sync�� ��� 
       		AFTValue=50;		// aft�� �����ϱ� ���ؼ� ���� �ʱ�ȭ �Ѵ�.
			SearchOK=0x00;	// aft flag�� ����.
		}
		else{SearchOK=0x01;}	// sync OK �� ���  
				
		//---------------------------------------------------------------
		
		if(SearchOK==0x00){	// Center Freq�� no sync�� ��� -->Sync Search
				while(SearchOK==0x00){
					SetTuner(Divider+(unsigned int)AFTValue-(unsigned int)80);
					value = SyncRead();	// Sync Status�� �Ǵ��ϱ� ���ؼ�, VPX_ASR �����Ѵ�.	
					if((value & 0x07) != 0x03){	//no sync�� ��� 
						AFTValue+=10;
					}	
					else	{SearchOK=0x01;}
					
					if(AFTValue>150) break;	// while loopŻ�� ����.			
				}

				if(SearchOK==0x01){	
					SearchOK=0x00;
//					if(PrintFlag)printf("N");		// Decoder Sync�� �Ǵ��ϱ� ���ؼ� ��� ---> test
					Write24c16(ep_ChannelStart+ProgNo*4,0x00);	// TV Flag����.(Air-TV)
					Write24c16(ep_ChannelStart+ProgNo*4+1,i);	// Air-TV������ channel table offset����.
					Write24c16(ep_ChannelStart+ProgNo*4+2,50);	// Fine tuning Data �ʱ�ȭ
					ProgNo++;	
					DisplayChannelValue(9,2,ProgNo);
				}

		}
		else{	//sync ok --> Data Save�� Finetune data�ʱ�ȭ.
//			if(PrintFlag)printf("S");		// Decoder Sync�� �Ǵ��ϱ� ���ؼ� ��� ---> test
			Write24c16(ep_ChannelStart+ProgNo*4,0x00);	// TV Flag����.(Air-TV)
			Write24c16(ep_ChannelStart+ProgNo*4+1,i);	// Air-TV������ channel table offset����.
			Write24c16(ep_ChannelStart+ProgNo*4+2,50);	// Fine tuning Data �ʱ�ȭ
			ProgNo++;	
			DisplayChannelValue(9,2,ProgNo);
		}
		//---------------------------------------------------------------
		
		Write24c16(ep_ProgNumber,ProgNo-1);	// Program�� ���ڸ� eeprom�� ����.
		if(ProgNo >= CHANNELMEMORYMAX) break;
		RegBuffer[CHANNEL]=PWMMin+i;
		DisplayPWMScale(WIN3_L+1,WIN3_B-1,20);
		
		while(Timer8 != 0){  WatchDogClear();}	// 0.5�ʰ� ������ ���� ��ٸ���.  	
		
	}

	
//------------------Cable-TV Channel Table Scanning---------------------
	PutString(9,WIN3_B,"CATV~");
	PWMMax=CATV_Max;
	PWMMin=CATV_Min;
	RegBuffer[CHANNEL]=CATV_Min;
	DisplayPWMScale(WIN3_L+1,WIN3_B-1,20);
	
	for(i=0; i<(CATV_Max-CATV_Min+1); i++){	
		KeyScan();
		if(KeyCode==MK_MENU) return;	
		if(ProgNo >= CHANNELMEMORYMAX) break;	
		// Min���� Max Channel���� ������� Scan�ϸ鼭, Sync�� Detect�Ǵ����� �Ǵ��ϰ�, 
		// Sync���¿� ����eeprom���� Program Edit������ Update�Ѵ�. 
		
		// ShowOSDChannel(1,i);		// OSD Channel Display(Cable-TV Channel Display)		
		
		// Channel Table�� ���� Offset���
		//p = CATV_TAB[CountryToChanel[SystemCountry]] + (i - CATV_Min);	// Freq. Table�� ���� �װ�(PLL Divider Value)��  ã�Ƽ�,
		p = CATV_TAB[CountryToChanel[SystemCountry]] + (UINT)i;	// Freq. Table�� ���� �װ�(PLL Divider Value)��  ã�Ƽ�,
		//Divider = *p;				// PLL Divider Value�� Divider�� �ε�.	
		if(*p == 0) 		// PLL Divider Value�� Dummy Data���� üũ�Ѵ�. 		// 1�� 16�� Dummy Check�ϵ��� �߰���.
			continue;	// Dummy�� ����� Skip�Ѵ�.
		else 
			Divider = *p;		// PLL Divider Value�� Divider�� �ε�.
			
//		ShowOSDChannel(1,i);		// OSD Channel Display(Cable-TV Channel Display)			

		//----------���� Channel Setting�Ŀ� AFT���࿩�θ� üũ�Ѵ�.---------
		Timer8 = AUTO_SEARCH_TIME;	// Auto Search ���� Ž�� �ð� ����. = 0.5��	
		AFTValue=80;	SearchOK=0x00;
		SetTuner(Divider+(unsigned int)AFTValue-(unsigned int)80);
		value = SyncRead();	// Sync Status�� �Ǵ��ϱ� ���ؼ�, VPX_ASR �����Ѵ�.	
		if((value & 0x07) != 0x03){	//no sync�� ��� 
       		AFTValue=50;		// aft�� �����ϱ� ���ؼ� ���� �ʱ�ȭ �Ѵ�.
			SearchOK=0x00;	// aft flag�� ����.
		}
		else{SearchOK=0x01;}	// sync OK �� ���  				
		//---------------------------------------------------------------

		if(SearchOK==0x00){	// Center Freq�� no sync�� ��� -->Sync Search
				while(SearchOK==0x00){
					SetTuner(Divider+(unsigned int)AFTValue-(unsigned int)80);
					value = SyncRead();	// Sync Status�� �Ǵ��ϱ� ���ؼ�, VPX_ASR �����Ѵ�.	
					if((value & 0x07) != 0x03){	//no sync�� ��� --> 500Khz Step
						AFTValue+=10;
					}
					else	{SearchOK=0x01;}
					
					if(AFTValue>150) break;	// while loopŻ�� ����.			
				}

				if(SearchOK==0x01){	
					SearchOK=0x00;
					if(PrintFlag)printf("N");		// Decoder Sync�� �Ǵ��ϱ� ���ؼ� ��� ---> test
					Write24c16(ep_ChannelStart+ProgNo*4,0x02);	// TV Flag����.(CATV-TV)
					Write24c16(ep_ChannelStart+ProgNo*4+1,i);	// Air-TV������ channel table offset����.
					Write24c16(ep_ChannelStart+ProgNo*4+2,50);	// Fine tuning Data �ʱ�ȭ
					ProgNo++;
					DisplayChannelValue(9,2,ProgNo);

				}

		}		
		else{	//sync ok --> Data Save�� Finetune data�ʱ�ȭ.
			if(PrintFlag)printf("S");		// Decoder Sync�� �Ǵ��ϱ� ���ؼ� ��� ---> test
			Write24c16(ep_ChannelStart+ProgNo*4,0x02);	// TV Flag����.(CATV-TV)
			Write24c16(ep_ChannelStart+ProgNo*4+1,i);	// Air-TV������ channel table offset����.
			Write24c16(ep_ChannelStart+ProgNo*4+2,50);	// Fine tuning Data �ʱ�ȭ
			ProgNo++;
			DisplayChannelValue(9,2,ProgNo);

		}
		//---------------------------------------------------------------
		
		Write24c16(ep_ProgNumber,ProgNo-1);	// Program�� channel ���ڸ� eeprom�� ����. -->
											// ��� channel�� sync detect�Ǿ������� Ȯ���ϱ� ���ؼ� ���.
		if(ProgNo >= CHANNELMEMORYMAX) break;
		RegBuffer[CHANNEL]=PWMMin+i;
		DisplayPWMScale(WIN3_L+1,WIN3_B-1,20);
		
		while(Timer8 != 0){  WatchDogClear();}	// 0.5�ʰ� ������ ���� ��ٸ���.  	
		
	}	
//-----------------scan �Ǿ��� Channel �̿��� Program Edit������ ���ؼ� disable���·� �����.----------
	if(ProgNo < CHANNELMEMORYMAX){ 	// 1��15��
		for(i=ProgNo;i<CHANNELMEMORYMAX;i++) {	// ��ü Channel Edit����(100 * 4bytes)�� ���Ͽ� �Ʒ��� ���� �ʱ�ȭ�� �����Ѵ�.
			// TV Flag�ʱ�ȭ�� ����.(0��° byte)	
			Write24c16(ep_ChannelStart+i*4  ,0x01);	// mask flag set
			WatchDogClear();
			// Fine tuning Data �ʱ�ȭ�� ����.(2��° byte)
			// Write24c16(ep_ChannelStart+i*4+2,50);		// �ʱⰪ = 50  ---> 50*50Khz=2.5Mhz  <-- ������ ��
		}
	}
//----------------------------------------------------------

//--------------Audio Mute Off------
	//PutVolume(TRUE);
	SoftVolume(TRUE);		// 1�� 17�� LKE
//--------------------------------

// ------------��ĵ �Ϸ��Ŀ� ������ Channel�� �ǵ�����.---------------------
//	LCDMute(0,1);	// Mute On		// --> 1��16�� ����.
//	SetTuner(temp_pll);		// --> 1��16�� ����.
//	LCDMuteOff();	// Mute Off		// --> 1��16�� ����.
//-------------Program Number�� 0���� �ʱ�ȭ �Ѵ�. ----------------------
	RegBuffer[CHANNEL]=0;
	Write24c16(ep_Currentchennel,RegBuffer[CHANNEL]);
//	ViewCurrentChannel();
//--------------------------------


	}
}
*/
// by LKE 2/15
// 16byte data�� �ѹ��� Write�� ���Ѵ�.
// ���������� 00,10,20,30...��� ���� ���� EEProm Start Address�� ������ ����Ǿ�� �Ѵ�.
//		 (start eeprom offset, 16byte data pointer)
void Write24c16Page(WORD addr, BYTE *p)
{
	BYTE i;
	BYTE DataEEp;

   	BTC_START_I2C(ep_Page(addr));
   	BTC_WriteData(ep_Addr(addr));
	for(i=0;i<16;i++){
   		DataEEp=p[i];
	   	BTC_WriteData(DataEEp);
   	}
	BTC_STOP_I2C();
	NOP;
   	idelay5m(2); 
}




// EEProm�� System County���뿡 �°Բ� EEPROM Program Memory������ �ʱ�ȭ ��Ű�� �Լ��̴�. 
// by LKE 2/15 EEPROM Write�ӵ��� �ø��� ���ؼ� page write������ ������.
// Pal-Multi/NTSC�� �������� �����ϱ� ���ؼ� ������. by LKE 2.18
// Tuner PLL Data�� dummy�� ����̰ų� ä�� ������ ����� ��쿡��  --> No Using flag�� ��Ʈ��.
// by LKE 2/22 --> �Լ��߰� EepTvFillValue()
void TVCountrySet()
{
	xdata unsigned short *p;
	xBYTE	i,j;
	xBYTE 	OSDStringBuff[16];
	xdata WORD 	addr;
	
	#if (NTSC_COUNTRY==0)&&!defined(FrequncyTableType)
  xBYTE	Channel_Count=0;
	xBYTE 	Channel_Total;
	#endif
	
	#ifdef USE_UART
	DBGputs("TVCountrySet");
	#endif
	
	//-------------------------------------------------------------------------
	#if((NTSC_COUNTRY==1)||(AUTO_SETUPDEBUG==1))
	//-------------------------------------------------------------------------
		//--------------Air EEprom �ʱ�ȭ.--------------		
		j=0;	
		addr=ep_ChannelStartAir;

		CHANNEL_LIMIT=TvLimitTable[3*CountryToChannel[xEEPROMBuffer[SystemCountry]]+0];

		for(i=0; i < CHANNEL_LIMIT; i++)
		{		// 1��16��
			
			p = AIR_TAB[CountryToChannel[xEEPROMBuffer[SystemCountry]]] + (WORD)i;		
			if(*p == 0) OSDStringBuff[j++]=0x81; 	// PLL Divider Value�� Dummy Data���� üũ�Ѵ�. 		// 1�� 16�� Dummy Check�ϵ��� �߰���.
			else OSDStringBuff[j++]=0x00; 			// Dummy�� �����  NoUsing Flag�� set�Ѵ�.
			OSDStringBuff[j++]=AftRangeTable[xEEPROMBuffer[SystemCountry]];		//  Air/Enable Data,   FineTune Data�� set�Ѵ�.

			if(j==16)
			{	// 16byte�� ���ۿ� ä������ write..
				j=0; 
				Write24c16Page(addr, OSDStringBuff);
				addr=addr+16;
			}
		}
		for(; i < 128; i++)
		{	// Tv Data �̿��� ������ ���� �ʱ�ȭ 
			OSDStringBuff[j++]=0x81; 
			OSDStringBuff[j++]=AftRangeTable[xEEPROMBuffer[SystemCountry]];		//  NoUsing/Air/Disable Data, FineTune Data
		
			if(j==16)
			{	// 16byte�� ���ۿ� ä������ write..
				j=0; 
				Write24c16Page( addr, OSDStringBuff);
				addr=addr+16;
			}
		}
		//---------------Catv EEprom �ʱ�ȭ.-------------	
		
		j=0;
		addr=ep_ChannelStartCatv;		


		CHANNEL_LIMIT=CatvLimitTable[3*CountryToChannel[xEEPROMBuffer[SystemCountry]]+0];
		
		for(i=0; i < CHANNEL_LIMIT; i++)
		{
			p = CATV_TAB[CountryToChannel[xEEPROMBuffer[SystemCountry]]] + (WORD)i;		
			if(*p == 0) OSDStringBuff[j++]=0x83; 	// PLL Divider Value�� Dummy Data���� üũ�Ѵ�. 		// 1�� 16�� Dummy Check�ϵ��� �߰���.
			else OSDStringBuff[j++]=0x02; 			// Dummy�� �����  NoUsing Flag�� set�Ѵ�.
			OSDStringBuff[j++]=AftRangeTable[xEEPROMBuffer[SystemCountry]];		//  Catv/Enable Data,   FineTune Data
			if(j==16)
			{	// 16byte�� ���ۿ� ä������ write..
				j=0; 
				Write24c16Page(addr, OSDStringBuff);
				addr=addr+16;
			}
		}
		for(; i < 128; i++)
		{	// Tv Data �̿��� ������ ���� �ʱ�ȭ 
			OSDStringBuff[j++]=0x83; OSDStringBuff[j++]=AftRangeTable[xEEPROMBuffer[SystemCountry]];		//  Nousing/Catv/Disable Data, FineTune Data
			if(j==16){	// 16byte�� ���ۿ� ä������ write..
				j=0; 
				Write24c16Page(addr, OSDStringBuff);
				addr=addr+16;
				}
		}
		//-------------------------------------------------------------------------
	#elif (NTSC_COUNTRY==0)&&!defined(FrequncyTableType)
		//---------------PAL Program Edit EEprom �ʱ�ȭ.-------------
		//	ó������ air�� ���� ä��� �״����� catv��   ä��� 

		//----���α׷� ����ũ ǥ �ʱ�ȭ 

		j=0;	
		addr=ep_ProgStart;

		for(i=0; i < 128; i++)
		{		// 1��16��
			OSDStringBuff[j++]=i;		
			
			if(j==16)
			{	// 16byte�� ���ۿ� ä������ write..
				j=0; 
				Write24c16Page(addr, OSDStringBuff);
				addr=addr+16;
			}
		}

		//--------------Air EEprom �ʱ�ȭ.--------------		
		j=0;	
		addr=ep_ProgMemStart;
		
		CHANNEL_LIMIT=TvLimitTable[3*CountryToChannel[xEEPROMBuffer[SystemCountry]]+0];
		
		for(i=0; i < CHANNEL_LIMIT; i++)
		{		// 1��16��
			p = AIR_TAB[CountryToChannel[xEEPROMBuffer[SystemCountry]]] + (WORD)i;		
			if(*p == 0) OSDStringBuff[j++]=0x81; 	// PLL Divider Value�� Dummy Data���� üũ�Ѵ�. 		// 1�� 16�� Dummy Check�ϵ��� �߰���.
			else OSDStringBuff[j++]=0x00; 			// Dummy�� �����  NoUsing Flag�� set�Ѵ�.
			OSDStringBuff[j++]=i;			//real channel 
			OSDStringBuff[j++]=AftRangeTable[xEEPROMBuffer[SystemCountry]];		//  Air/Enable Data,   FineTune Data�� set�Ѵ�.
			OSDStringBuff[j++]=0x00;		//reserved.
			
			OSDStringBuff[j++]=0x00;		///4byte ���� �� �ڸ� 
			OSDStringBuff[j++]=0x00;		//
			OSDStringBuff[j++]=0x00;		//
			OSDStringBuff[j++]=0x00;		//reserved.
			
			if(j==16)
			{	// 16byte�� ���ۿ� ä������ write..
				j=0; 
				Write24c16Page(addr, OSDStringBuff);
				addr=addr+16;
			}
		}

		//---------------Catv EEprom �ʱ�ȭ.-------------	

		//j=0;			
		Channel_Count=Channel_Total=CHANNEL_LIMIT;		
		CHANNEL_LIMIT=CatvLimitTable[3*CountryToChannel[xEEPROMBuffer[SystemCountry]]+0];
		Channel_Total+=CHANNEL_LIMIT;
		
		for(i=0; i < CHANNEL_LIMIT; i++)
		{
			Channel_Count++;
			p = CATV_TAB[CountryToChannel[xEEPROMBuffer[SystemCountry]]] + (WORD)i;		
			if(*p == 0) OSDStringBuff[j++]=0x83; 	// PLL Divider Value�� Dummy Data���� üũ�Ѵ�. 		// 1�� 16�� Dummy Check�ϵ��� �߰���.
			else OSDStringBuff[j++]=0x02; 			// Dummy�� �����  NoUsing Flag�� set�Ѵ�.
			OSDStringBuff[j++]=i;		//real channel 			
			OSDStringBuff[j++]=AftRangeTable[xEEPROMBuffer[SystemCountry]];		//  Catv/Enable Data,   FineTune Data
			OSDStringBuff[j++]=0x00;		//reserved.

			OSDStringBuff[j++]=0x00;		///4byte ���� �� �ڸ� 
			OSDStringBuff[j++]=0x00;		//
			OSDStringBuff[j++]=0x00;		//
			OSDStringBuff[j++]=0x00;		//
			
			if(j==16)
			{	// 16byte�� ���ۿ� ä������ write..
				j=0; 
				Write24c16Page(addr, OSDStringBuff);
				addr=addr+16;
			}
			
			if(Channel_Count>=Channel_Total) break;	
			if(Channel_Count>CHANNELMEMORYMAX) break;
		}
		
		if(j!=0) 		//������ ���� ���� ��  ��� 
			while(j>=16) 
			{
				OSDStringBuff[j++]=0x83; 	// PLL Divider Value�� Dummy Data���� üũ�Ѵ�. 		// 1�� 16�� Dummy Check�ϵ��� �߰���.
				OSDStringBuff[j++]=0x00;		//real channel 				
				OSDStringBuff[j++]=AftRangeTable[xEEPROMBuffer[SystemCountry]];		//  Catv/Enable Data,   FineTune Data
				OSDStringBuff[j++]=0x00;		//reserved.

				OSDStringBuff[j++]=0x00;		///4byte ���� �� �ڸ� 
				OSDStringBuff[j++]=0x00;		//
				OSDStringBuff[j++]=0x00;		//
				OSDStringBuff[j++]=0x00;		//
				Write24c16Page(addr, OSDStringBuff);
			}
	#elif (NTSC_COUNTRY==0)&&defined(FrequncyTableType)

		//--------------EEprom �ʱ�ȭ.--------------		
		j=0;	
		addr=ep_ChannelStart;

		CHANNEL_LIMIT=TvLimitTable[3*CountryToChannel[xEEPROMBuffer[SystemCountry]]+0];

		for(i=0; i < CHANNEL_LIMIT; i++)
		{		// 1��16��
			
			p = CATV_TAB[CountryToChannel[xEEPROMBuffer[SystemCountry]]] + (WORD)i;		
			if(*p == 0) OSDStringBuff[j++]=0x83; 	// PLL Divider Value�� Dummy Data���� üũ�Ѵ�. 		// 1�� 16�� Dummy Check�ϵ��� �߰���.
			else OSDStringBuff[j++]=0x02; 			// Dummy�� �����  NoUsing Flag�� set�Ѵ�.
			OSDStringBuff[j++]=AftRangeTable[xEEPROMBuffer[SystemCountry]];		//  Air/Enable Data,   FineTune Data�� set�Ѵ�.

			if(j==16)
			{	// 16byte�� ���ۿ� ä������ write..
				j=0; 
				Write24c16Page(addr, OSDStringBuff);
				addr=addr+16;
			}
		}
		for(; i < 128; i++)
		{	// Tv Data �̿��� ������ ���� �ʱ�ȭ 
			OSDStringBuff[j++]=0x83; 
			OSDStringBuff[j++]=AftRangeTable[xEEPROMBuffer[SystemCountry]];		//  NoUsing/Air/Disable Data, FineTune Data
		
			if(j==16)
			{	// 16byte�� ���ۿ� ä������ write..
				j=0; 
				Write24c16Page( addr, OSDStringBuff);
				addr=addr+16;
			}
		}

	//-------------------------------------------------------------------------
	#endif
	//-------------------------------------------------------------------------

	TVParameterInit();
}