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
#define AUTO_SEARCH_TIME 0x04	// by LKE 2/15일 7로 fix
#define AUTO_SEARCH_TIME2 0x03//0x10	// by LKE 2/15일 7로 fix
#define AUTO_SEARCH_TIME3 0x01//0x02	// by LKE 2/15일 7로 fix
*/

#if defined(USE_NTSCtuner)
// 삼성튜너용 시정수 정리.(ntsc tuner)  --> tuner는 셋트에 따라서 AFT Curve와 응답이 다르다.
// 아래의 시정수는 4개의 삼성 ntsc구형튜너를 태스트 한 결과 값을 정리한 것이다.(2003년3월4일 fix  By LKE) 
#define AFT_MAINTIME 	35
#define AFT_NORMALTIME	25
#define AFT_MAINCOUNT 	5
#define AFT_SUBCOUNT 	2

#define NUM_10 10
#define NUM_20 20
#else
// 삼성튜너용 시정수 정리.(pal tuner) --> 미결정 상태.
#define AFT_MAINTIME 	35
#define AFT_NORMALTIME	25

#define AFT_MAINCOUNT 	5
#define AFT_SUBCOUNT 	2

#define NUM_10 10
#define NUM_20 20

#endif
//

#ifdef	USE_4BitInterface								//4bit통신 함수선언
void	WriteReg4bit(BYTE address, BYTE Recdata);
#define	WriteScaler(val1,val2) WriteReg4bit(val1,val2)	
BYTE	ReadScalerParallel(BYTE address);
#define	ReadScaler	ReadScalerParallel
#else											//1bit통신 함수선언
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
//extern void SoftVolume(bit);	// 1월 17일. LEE
void EepromSetQue(WORD address, BYTE Recdata);

extern void DisplayPWMScale(BYTE,BYTE,BYTE,BYTE);	// 1월 17일.
extern void PutString1(BYTE ,BYTE ); 	// 4월 15일. 
//extern void DisplayChannelValue(BYTE,BYTE,BYTE);	// 1월 17일.
extern void PowerOff();	// 1월 17일.
extern void WarmUp();	// 1월 17일.
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
	// NTSC USA/KOREA CableTV -->TAPC-H701F에 맞쳐놓은 주파수 테이블.
	code unsigned short NTSCKORCATV[124]={	// 2003.1.14 화요일 FIX --(Analog Cable TV Nominal Frequencies)
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
	// NTSC USA/KOREA CableTV -->TAPC-H701F에 맞쳐놓은 주파수 테이블.
	code unsigned short NTSCKORCATV[124]={	// 2003.1.14 화요일 FIX --(Analog Cable TV Nominal Frequencies)
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

	// NTSC USA/KOREA BroadCast -->TAPC-H701F에 맞쳐놓은 주파수 테이블.
	code unsigned short NTSCKORAIR[68]={	// 2003.1.14 화요일 FIX --(Analog Boradcast Nominal Frequencies)
	0x07E4,0x085C,0x08D4,0x099C,0x0A14,0x1144,0x11BC,0x1234,0x12AC,						//2~10 
	0x1324,0x139C,0x1414,0x2864,0x28DC,0x2954,0x29CC,0x2A44,0x2ABC,0x2B34,		//11~  
	0x2BAC,0x2C24,0x2C9C,0x2D14,0x2D8C,0x2E04,0x2E7C,0x2EF4,0x2F6C,0x2FE4,    //21~  
	0x305C,0x30D4,0x314C,0x31C4,0x323C,0x32B4,0x332C,0x33A4,0x341C,0x3494,    //31~  
	0x350C,0x3584,0x35FC,0x3674,0x36EC,0x3764,0x37DC,0x3854,0x38CC,0x3944,    //41~  
	0x39BC,0x3A34,0x3AAC,0x3B24,0x3B9C,0x3C14,0x3C8C,0x3D04,0x3D7C,0x3DF4,    //51~  
	0x3E6C,0x3EE4,0x3F5C,0x3FD4,0x404C,0x40C4,0x413C,0x41B4,0x422C            //61~69
	};   
	
	//--------------------------------------------------------------------------
	// NTSC JAPAN CableTV -->TAPC-H701F에 맞쳐놓은 주파수 테이블.
	code unsigned int NTSCJPNCATV[63] = {	// 2003.1.14 화요일 FIX --(Analog Cable TV Nominal Frequencies)
	0x0AB4,0x0B2C,0x0BA4,0x10F4,0x116C,0x11E4,0x125C,0x12AC,0x1324,0x139C,
	0x1414,0x148C,0x0C1C,0x0C94,0x0D0C,0x0D84,0x0DFC,0x0E74,0x0EEC,0x0F64,
//youngdo 3002.8.22	0x0FDC,0x107C,0x1504,0x15A4,0x161C,0x1694,0x170C,0x175C,0x17D4,0x184C,
	0x0FDC,0x107C,0x1504,0x157C,0x15F4,0x166C,0x16E4,0x175C,0x17D4,0x184C,	//youngdo 3002.8.22 일부 채널이 테이블과 안맞음.
	0x18C4,0x193C,0x19B4,0x1A2C,0x1AA4,0x1B1C,0x1B94,0x1C0C,0x1C84,0x1CFC,
	0x1D74,0x1DEC,0x1E64,0x1EDC,0x1F54,0x1FCC,0x2044,0x20BC,0x2134,0x21AC,
	0x2224,0x229C,0x2314,0x238C,0x2404,0x247C,0x24F4,0x256C,0x25E4,0x265C,
	0x26D4,0x274C,0x27C4
	};
	// NTSC JAPAN  BroadCast -->TAPC-H701F에 맞쳐놓은 주파수 테이블.
	code unsigned int NTSCJPNAIR[62]={	// 2003.1.14 화요일 FIX --(Analog Boradcast Nominal Frequencies for Japan)
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
	//PAL-B/G NETHERLAND CableTV -->TCPQ9091PD28L에 맞쳐놓은 주파수 테이블.
	code unsigned short PALNETHERLANDCATV[41]={	// 2003.1.14 화요일 FIX
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
	//PAL-B/G NETHERLAND BroadCast -->TCPQ9091PD28L에 맞쳐놓은 주파수 테이블.
	code unsigned short PALNETHERLANDAIR[72]={	// 2003.3.10 월요일 FIX
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
	
	// 참고 : 0x0000으로 Define되어 있는 부분은 스캐닝시에 Skip할 것. --> Channel No 정확하게 나타내기                                         
//// 위해서 Dummy Data로 사용하였다. 위의 경우에 Dummy Data가 8개 이므로 channel수는 60개가 된다. 위해서 Dummy Data로 사용하였다. 위의 경우에
	
	//--------------------------------------------------------------------------
	//PAL-B/G GERMANY CableTV -->TCPQ9091PD28L에 맞쳐놓은 주파수 테이블.
	code unsigned short PALGERMANYCATV[55]={		// 2003.1.14 화요일 FIX
	0x06CF,0x075B,0x07E7,0x0873,0x08FF,0x098B,0x0B43,0x0BCF,0x0C5B,0x0CE7,
	0x0D73,0x0DFF,0x0E8B,0x0F17,0x0FA3,0x102F,0x10BB,0x1147,0x11D3,0x125F,
	0x12EB,0x1377,0x1402,0x148E,0x151A,0x15A6,0x1632,0x16BE,0x174A,0x17D6,
	0x1862,0x18EE,0x197A,0x1A06,0x1ABA,0x1B5A,0x1BFA,0x1C9A,0x1D3A,0x1DDA,
	0x1E7A,0x1F1A,0x1FBA,0x205A,0x20FA,0x219A,0x223A,0x22DA,0x237A,0x241A,
	0x24BA,0x255A,0x25FA,0x269A,0x273A
	};
	//PAL-B/G GERMANY BroadCast -->TCPQ9091PD28L에 맞쳐놓은 주파수 테이블.
	code unsigned short PALGERMANYAIR[68]={	// 2003.1.14 화요일 FIX
	0x06CF,0x075B,0x07E7,0x10BB,0x1147,0x11D3,0x125F,0x12EB,0x1377,0x1402,
	0x148E,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x27DA,
	0x287A,0x291A,0x29BA,0x2A5A,0x2AFA,0x2B9A,0x2C3A,0x2CDA,0x2D7A,0x2E1A,
	0x2EBA,0x2F5A,0x2FFA,0x309A,0x313A,0x31DA,0x327A,0x331A,0x33BA,0x345A,
	0x34FA,0x359A,0x363A,0x36DA,0x377A,0x381A,0x38BA,0x395A,0x39FA,0x3A9A,
	0x3B3A,0x3BDA,0x3C7A,0x3D1A,0x3DBA,0x3E5A,0x3EFA,0x3F9A,0x403B,0x40DB,
	0x417B,0x421B,0x42BB,0x435B,0x43FB,0x449B,0x453B,0x45DB
	};
		
	// 참고 : 0x0000으로 Define되어 있는 부분은 스캐닝시에 Skip할 것. --> Channel No 정확하게 나타내기
	// 위해서 Dummy Data로 사용하였다. 위의 경우에 Dummy Data가 8개 이므로 channel수는 60개가 된다.
	//--------------------------------------------------------------------------
	//PAL-B/G ITALY CableTV -->TCPQ9091PD28L에 맞쳐놓은 주파수 테이블.
	code unsigned short PALITALYCATV[55]={	// 2003.1.14 화요일 FIX
	0x06CF,0x075B,0x07E7,0x0873,0x08FF,0x098B,0x0B43,0x0BCF,0x0C5B,0x0CE7,
	0x0D73,0x0DFF,0x0E8B,0x0F17,0x0FA3,0x102F,0x10BB,0x1147,0x11D3,0x125F,
	0x12EB,0x1377,0x1402,0x148E,0x151A,0x15A6,0x1632,0x16BE,0x174A,0x17D6,
	0x1862,0x18EE,0x197A,0x1A06,0x1ABA,0x1B5A,0x1BFA,0x1C9A,0x1D3A,0x1DDA,
	0x1E7A,0x1F1A,0x1FBA,0x205A,0x20FA,0x219A,0x223A,0x22DA,0x237A,0x241A,
	0x24BA,0x255A,0x25FA,0x269A,0x273A
	};
	//PAL-B/G ITALY BroadCast -->TCPQ9091PD28L에 맞쳐놓은 주파수 테이블.
	code unsigned short PALITALYAIR[69]={	// 2003.1.14 화요일 FIX
	0x073D,0x07E7,0x0977,0x10BB,0x1165,0x1273,0x12C3,0x1377,0x1402,0x148E,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x27DA,0x287A,0x291A,0x29BA,0x2A5A,0x2AFA,0x2B9A,0x2C3A,0x2CDA,0x2D7A,
	0x2E1A,0x2EBA,0x2F5A,0x2FFA,0x309A,0x313A,0x31DA,0x327A,0x331A,0x33BA,
	0x345A,0x34FA,0x359A,0x363A,0x36DA,0x377A,0x381A,0x38BA,0x395A,0x39FA,
	0x3A9A,0x3B3A,0x3BDA,0x3C7A,0x3D1A,0x3DBA,0x3E5A,0x3EFA,0x3F9A,0x403B,
	0x40DB,0x417B,0x421B,0x42BB,0x435B,0x43FB,0x449B,0x453B,0x45DB
	};
	
	/////////////////////////////////////////////////////////////////////////////////
	//PAL-D/K Russia BroadCast --> TCPQ9091PD27D(T)에 맞쳐놓은 주파수 테이블.
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
	
	
	// 참고 : 0x0000으로 Define되어 있는 부분은 스캐닝시에 Skip할 것. --> Channel No 정확하게 나타내기
	// 위해서 Dummy Data로 사용하였다. 위의 경우에 Dummy Data가 10개 이므로 channel수는 59개가 된다.
	//--------------------------------------------------------------------------
	//PAL-I UK CableTV -->TCPQ9091PD28L에 맞쳐놓은 주파수 테이블.
	code unsigned short PALUKCATV[55]={	// 2003.1.14 화요일 FIX
	0x06CF,0x075B,0x07E7,0x0873,0x08FF,0x098B,0x0B43,0x0BCF,0x0C5B,0x0CE7,
	0x0D73,0x0DFF,0x0E8B,0x0F17,0x0FA3,0x102F,0x10BB,0x1147,0x11D3,0x125F,
	0x12EB,0x1377,0x1402,0x148E,0x151A,0x15A6,0x1632,0x16BE,0x174A,0x17D6,
	0x1862,0x18EE,0x197A,0x1A06,0x1ABA,0x1B5A,0x1BFA,0x1C9A,0x1D3A,0x1DDA,
	0x1E7A,0x1F1A,0x1FBA,0x205A,0x20FA,0x219A,0x223A,0x22DA,0x237A,0x241A,
	0x24BA,0x255A,0x25FA,0x269A,0x273A
	};
	//PAL-I UK BroadCast -->TCPQ9091PD28L에 맞쳐놓은 주파수 테이블.
	code unsigned short PALUKAIR[68]={		// 2003.1.14 화요일 FIX
	0x06CF,0x075B,0x07E7,0x10BB,0x1147,0x11D3,0x125F,0x12EB,0x1377,0x1402,
	0x148E,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x27DA,
	0x287A,0x291A,0x29BA,0x2A5A,0x2AFA,0x2B9A,0x2C3A,0x2CDA,0x2D7A,0x2E1A,
	0x2EBA,0x2F5A,0x2FFA,0x309A,0x313A,0x31DA,0x327A,0x331A,0x33BA,0x345A,
	0x34FA,0x359A,0x363A,0x36DA,0x377A,0x381A,0x38BA,0x395A,0x39FA,0x3A9A,
	0x3B3A,0x3BDA,0x3C7A,0x3D1A,0x3DBA,0x3E5A,0x3EFA,0x3F9A,0x403B,0x40DB,
	0x417B,0x421B,0x42BB,0x435B,0x43FB,0x449B,0x453B,0x45DB
	};
	
	// 참고 : 0x0000으로 Define되어 있는 부분은 스캐닝시에 Skip할 것. --> Channel No 정확하게 나타내기
	// 위해서 Dummy Data로 사용하였다. 위의 경우에 Dummy Data가 8개 이므로 channel수는 60개가 된다.


	//--------------------------------------------------------------------------
	//SECAM-L FRNACE CableTV -->TCPQ9091PD28L에 맞쳐놓은 주파수 테이블.
	code unsigned short SECAMFRNACECATV[41]={	// 2003.1.14 화요일 FIX
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
	
	// 1차 TEST (SOUND CARRIER버그 수정후.) -> 채널 태이블 변경
	//0x2776,0x2816,0x28B6,0x2956,0x29F6,0x2A96,0x2B36,0x2BD6,0x2C76,0x2D16
	//,0x2DB6,0x2E56,0x2EF6,0x2F96,0x3036,0x30D6,0x3176,0x3216,0x32B6,0x3356
	//,0x33F6,0x3496,0x3536,0x35D6,0x3676,0x3716,0x37B6,0x3856,0x38F6,0x3996
	//,0x3A36,0x3AD6,0x3B76,0x3C16,0x3CB6,0x3D56,0x3DF6,0x3E96,0x3F36,0x3FD6
	//,0x4077,0x4117,0x41B7,0x4257,0x42F7,0x4397,0x4437,0x44D7,0x4577,


	// 1차 TEST (SOUND CARRIER버그 수정후.)
	//0x11FB,0x1287,0x1313,0x139F,0x142A,0x14B6,0x1542,0x15CE,0x165A,0x16E6,
	//0x1772,0x17FE,0x188A,0x1916,0x19A2,0x1A56,0x1AF6,0x1B96,0x1C36,0x1CD6,
	//0x1D76,0x1E16,0x1EB6,0x1F56,0x1FF6,0x2096,0x2136,0x21D6,0x2276,0x2316,
	//0x23B6,0x2456,0x24F6,0x2596,0x2636,0x26D6,

	//0x125F,0x12EB,0x1377,0x1402,0x148E,0x151A,0x15A6,0x1632,0x16BE,0x174A,
	//0x17D6,0x1862,0x18EE,0x197A,0x1A06,0x1ABA,0x1B5A,0x1BFA,0x1C9A,0x1D3A,
	//0x1DDA,0x1E7A,0x1F1A,0x1FBA,0x205A,0x20FA,0x219A,0x223A,0x22DA,0x237A,
	//0x241A,0x24BA,0x255A,0x25FA,0x269A,0x273A,
	};
	code unsigned short SECAMFRNACEAIR[69]={		// 2003.1.14 화요일 FIX
	// 1차 TEST (SOUND CARRIER버그 수정후.) -> 채널 태이블 변경
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

	// 1차 TEST (SOUND CARRIER버그 수정후.)
	//0x0661,0x0701,0x0760,0x07A1,0x0BC5,0x0CAB,0x0DA5,0x0E95,0x0F85,0x1066,
	//0x1075,0x1106,0x1165,0x11A6,0x1246,0x1255,0x1345,0x12E6,0x1386,0x1434,

	//0x06C5,0x0765,0x07C4,0x0805,0x0C29,0x0D0F,0x0E09,0x0EF9,0x0FE9,0x10CA,
	//0x10D9,0x116A,0x11C9,0x120A,0x12AA,0x12B9,0x13A9,0x134A,0x13EA,0x1498,
	};
	

	//--------------------------------------------------------------------------
	//SECAM-D/K RUSSIA CableTV -->TCPQ9091PD28L에 맞쳐놓은 주파수 테이블.
	code unsigned short SECAMRUSSIACATV[41]={	// 2003.1.14 화요일 FIX
	0x0B43,0x0BBB,0x0C5B,0x0CFB,0x0D9B,0x0E3B,0x0EDB,0x0F7B,0x101B,0x0000,
	0x0000,0x151A,0x15BA,0x165A,0x16FA,0x179A,0x183A,0x18DA,0x197A,0x1A06,
	0x1ABA,0x1B5A,0x1BFA,0x1C9A,0x1D3A,0x1DDA,0x1E7A,0x1F1A,0x1FBA,0x205A,
	0x20FA,0x219A,0x223A,0x22DA,0x237A,0x241A,0x24BA,0x255A,0x25FA,0x269A,
	0x273A
	};
	// 참고 : 0x0000으로 Define되어 있는 부분은 스캐닝시에 Skip할 것. --> Channel No 정확하게 나타내기
	// 위해서 Dummy Data로 사용하였다. 위의 경우에 Dummy Data가 2개 이므로 channel수는 39개가 된다.
	//SECAM-D/K RUSSIA BroadCast -->TCPQ9091PD28L에 맞쳐놓은 주파수 테이블.
	code unsigned short SECAMRUSSIAAIR[57]={		// 2003.1.14 화요일 FIX
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
	//PAL-D/K CHINA [CH1~57] 주파수 테이블.
	code unsigned short PAL_CHINA_TV[]={			// 2004-01-15
	/*0x0500,*/0x058A,0x060A,0x068A,0x0742,0x07C2,0x0CF2,0x0D72,0x0DF2,0x0E72,
	0x0EF2,0x0F72,0x0FF2,0x1FE2,0x2062,0x20E2,0x2142,0x21E2,0x2262,0x22E2,
	0x2362,0x23E2,0x2462,0x24E2,0x2562,0x2862,0x28E2,0x2962,0x29E2,0x2A62,
	0x2AE2,0x2B62,0x2BE2,0x2C62,0x2CE2,0x2D62,0x2DE2,0x2E62,0x2EE2,0x2F62,
	0x2FE2,0x3062,0x30E2,0x3162,0x31E2,0x3262,0x32E2,0x3362,0x33E2,0x3462,
	0x34E2,0x3562,0x35E2,0x3662,0x36E2,0x3762,0x37E2,0x3862
	};
	#else
	//PAL-D/K CHINA CableTV -->TCPQ9091PD27D(T)에 맞쳐놓은 주파수 테이블.
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
	//0x3dE2////	/* 871.25 ~ 951.25 MHz 11개 Freq. 추가 2004-05-13 */
	// 튜너에서 895.25이상은 못잡음..그래서 적용안함.
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
// 각각의 채널 테이블에 대한 Start Address 저장.(Cable-TV, Air-TV)
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
// Country에따라서 AFT Range범위를 조정하기 위한 테이블.
code BYTE  AftRangeTable[]=	{	//AftRangeTable[xEEPROMBuffer[SystemCountry]];
//---AFT Range -----------------country---------country code---AFT Range---
		45,					//KOREA(ntsc)				0  		+-2.5Mhz		// 05/08수정함. 2.5 ->1.5Mhz by LKE
		45,					//USA(ntsc)				1  		+-2.5Mhz		// 05/08수정함. 2.5 ->1.5Mhz by LKE
// Korea/Usa에 대한 수정 근거: Air의 경우에 Search시에 2Mhz를 벗어나는 데이터가 많은데, 이것들은 대부분이 Catv의 Center
// 주파수에 속하는 것임. 그래서 무리하게 AFT Range키울 필요없어서 AFT Range를 조정함.
		45,					//Japan(ntsc)				2  		+-2.5Mhz
		
		25,					//France(SECAL-L)			3  		+-2.5Mhz
		25,					//Germany(PAL-B/G)		4  		+-2.5Mhz
		25,					//Italy(PAL-B/G)			5  		+-2.5Mhz
		
		70,					//NETHERLAND(PAL-B/G)	6  		+-3.25Mhz
		25,					//Russia(SECAM-D/K)		7  		+-2.5Mhz
		25,					//UK(PAL-I)				8  		+-2.5Mhz
};
//--------------------------------------------------------------------------
// 각채널 시스템에 대한 전체Channel 수, Max channel, Min channel 에 대한 Define.

// CableTV에 대한 Channel Table System Define
code BYTE  CatvLimitTable[]=	{
   //채널수,Catv_Max,Catv_Min 		//	ChannelSystem  		Number
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

// BoradCast에 대한 Channel Table System Define  
code BYTE  TvLimitTable[]=	{		// 1월16일 Fix
// 채널수,TV_Max,TV_Min			//	ChannelSystem  		Number
	68,		69,		2,			// 	KOREA/USA		  	0
	62,		62,		1,			// 	JAPAN			  	1
	
	59, 	69,		1,			//    France(SECAL-L)	  	2	
	
	60,		69,		2,			//	GERMANY(PAL-B/G)	  	3   채널수 --> dummy 8개 제거한 데이터임.
	59,		69,		1,			//	ITALY(PAL-B/G)	  	4   채널수 --> dummy 10개 제거한 데이터임.
#if(AUTO_SETUPDEBUG==0)	
	65, 	73,		2,			//   NETHERLAND(PAL-B/G)	5	채널수 --> dummy 7개 제거한 데이터임.
	//66, 	66,		1,			//   NETHERLAND(PAL-B/G)	5	
#else
	72, 	73,		2,			//   NETHERLAND(PAL-B/G)	5	
#endif

	57, 	57,		1,			//    Russia(SECAM-D/K)	  	6	
	60,		69,		2,			//  	UK(PAL-I)			  	7
	//102,	102,	1,	//  	HongKong(PAL-I)	  5
	///57,	57,		1,	//    China(PAL-D/K)	  2	
	};

code BYTE CountryToChannel[]={		// 1월16일 Fix
//---Limit Table에 대한 offset-----country-------country code
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
// 각각의 채널 테이블에 대한 Start Address 저장.(Cable-TV, Air-TV)
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
// Country에따라서 AFT Range범위를 조정하기 위한 테이블.
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
// 각채널 시스템에 대한 전체Channel 수, Max channel, Min channel 에 대한 Define.

// CableTV에 대한 Channel Table System Define
code BYTE  CatvLimitTable[]=	{
   //채널수,Catv_Max,Catv_Min 		//	ChannelSystem  		Number
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

// BoradCast에 대한 Channel Table System Define  
code BYTE  TvLimitTable[]=	{		// 1월16일 Fix
// 채널수,TV_Max,TV_Min			//	ChannelSystem  		Number
	//57,		57,		1,			// 	CHINA		  	0
	100,		100,		1,			//CHINA (PAL D/K)						0
	105,		105,		1,			//Russia (PAL D/K)				1

	59, 	69,		1,			//    France(SECAL-L)	  	2	
	
	60,		69,		2,			//	GERMANY(PAL-B/G)	  	3   채널수 --> dummy 8개 제거한 데이터임.
	59,		69,		1,			//	ITALY(PAL-B/G)	  	4   채널수 --> dummy 10개 제거한 데이터임.
#if(AUTO_SETUPDEBUG==0)	
	65, 	73,		2,			//   NETHERLAND(PAL-B/G)	5	채널수 --> dummy 7개 제거한 데이터임.
	//66, 	66,		1,			//   NETHERLAND(PAL-B/G)	5	
#else
	72, 	73,		2,			//   NETHERLAND(PAL-B/G)	5	
#endif

	57, 	57,		1,			//    Russia(SECAM-D/K)	  	6	
	60,		69,		2,			//  	UK(PAL-I)			  	7
	//102,	102,	1,	//  	HongKong(PAL-I)	  5
	///57,	57,		1,	//    China(PAL-D/K)	  2	
	};

code BYTE CountryToChannel[]={		// 1월16일 Fix
//---Limit Table에 대한 offset-----country-------country code
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
//xdata BYTE		TV_MIN;	// Channle Table의 Min Channel Number. 	//1월16일
//xdata BYTE		CATV_MIN;	// Channle Table의 Min Channel Number.  	//1월16일
//#endif



void TunnerInitialize()
{
	TunerTest();
	ATFEnable=0;	
	ChannelSel(xEEPROMBuffer[CurrentChannel]);	// Prog No를 이용하여 --> Tunner를 세팅한다.
	ATFEnable=1;
	
	#if((NTSC_COUNTRY==1)||(AUTO_SETUPDEBUG==1))
//		TV_MIN=TvLimitTable[3*CountryToChannel[xEEPROMBuffer[SystemCountry]]+2];	// Channle Table의 Min Channel Number. 	//1월16일
//		CATV_MIN=CatvLimitTable[3*CountryToChannel[xEEPROMBuffer[SystemCountry]]+2]	;	// Channle Table의 Min Channel Number.  	//1월16일
	#endif
}

void TVParameterInit()
{
	#if(NTSC_COUNTRY==1)
	//if(ColorSystem&NTSC) {	// NTSC
/*		AntenaFlag=xEEPROMBuffer[Antena];
		if(AntenaFlag) {
			CHANNEL_LIMIT=CatvLimitTable[3*CountryToChannel[xEEPROMBuffer[SystemCountry]]+0];	// CATV Total Channel 수 Read
			CHANNEL_MAX=CatvLimitTable[3*CountryToChannel[xEEPROMBuffer[SystemCountry]]+1];
			CHANNEL_MIN=CatvLimitTable[3*CountryToChannel[xEEPROMBuffer[SystemCountry]]+2];			
		}
		else  {
			CHANNEL_LIMIT=TvLimitTable[3*CountryToChannel[xEEPROMBuffer[SystemCountry]]+0];			
			CHANNEL_MAX=TvLimitTable[3*CountryToChannel[xEEPROMBuffer[SystemCountry]]+1];
			CHANNEL_MIN=TvLimitTable[3*CountryToChannel[xEEPROMBuffer[SystemCountry]]+2];						
		} */  // Code Size로 인해 Routine Remark... +jwshin 040813

	#else
	//pal
		CHANNEL_LIMIT=CatvLimitTable[3*CountryToChannel[xEEPROMBuffer[SystemCountry]]+0];	//channel 수
		CHANNEL_MAX=CatvLimitTable[3*CountryToChannel[xEEPROMBuffer[SystemCountry]]+1];		//channel max
		CHANNEL_MIN=CatvLimitTable[3*CountryToChannel[xEEPROMBuffer[SystemCountry]]+2];		//channel min
	#endif
}

// by LKE 2.14
// OSD메뉴에서 사용하고, IR Key처리에서도 사용함.
void CatvAirSelection(bit Selection)
{
	if(Selection==AntenaFlag) return;
	
	Mute_SoundOff;

		
	if(!Selection)
	{		// Catv --> Air전환.
		AntenaFlag=(bit)0;
		#if((NTSC_COUNTRY==1)||(AUTO_SETUPDEBUG==1))
		CHANNEL_LIMIT=TvLimitTable[3*CountryToChannel[xEEPROMBuffer[SystemCountry]]+0];			
		CHANNEL_MAX=TvLimitTable[3*CountryToChannel[xEEPROMBuffer[SystemCountry]]+1];
		CHANNEL_MIN=TvLimitTable[3*CountryToChannel[xEEPROMBuffer[SystemCountry]]+2];		
		
		if(CHANNEL_MAX < xEEPROMBuffer[CurrentChannel]+CHANNEL_MIN) {xEEPROMBuffer[CurrentChannel]=0;}
		#endif
	}
	else
	{	 	// Air --> Catv전환.
		AntenaFlag=(bit)1;
		#if((NTSC_COUNTRY==1)||(AUTO_SETUPDEBUG==1))
		CHANNEL_LIMIT=CatvLimitTable[3*CountryToChannel[xEEPROMBuffer[SystemCountry]]+0];	// CATV Total Channel 수 Read
		CHANNEL_MAX=CatvLimitTable[3*CountryToChannel[xEEPROMBuffer[SystemCountry]]+1];
		CHANNEL_MIN=CatvLimitTable[3*CountryToChannel[xEEPROMBuffer[SystemCountry]]+2];
		#endif			
	}

	TunerProcessing	=2;
	
	EepromSetQue(Antena_adr, AntenaFlag);

	if(!IRMuteFlag)  Mute_SoundOn;//PutVolume(TRUE);
}


// 선택된 채널명이 올바르게 선택되었는지를 체크하고 보정한다. 
//  1.채널 범위를 벗어난 경우 체크 :(숫자조작만을 행한다.)
//	  Min보다 작은 경우 : Min Channel로 fix
//     Max보다 큰 경우 :  Max Channel로 fix
//  2. 1의과정을 거친 후에 얻어진 채널Number가 Auto Setup시에 memory에 저장된 채널인지를 체크한다.
//     저장된 채널의 경우  :  channel selection을 행하고 --> channel을 정상적인 녹색으로 표시.
//     저장된 채널이 아닌경우 : channel selection을 행하고 --> channel을 노란색으로 표시.
/*  memory save  2003.6.3
void CheckChannelView(void){
	xBYTE tmp;
	xBYTE	TV_Max,CATV_Max,TV_Total,CATV_Total;
	
	tmp=IRDigitValue;
	//---------------채널 범위를 벗어난 경우 체크및 숫자보정을 행한다.---------------
		TV_Max=TvLimitTable[3*CountryToChannel[xEEPROMBuffer[SystemCountry]]+1];		// max	// Air-TV
//		TV_MIN=TvLimitTable[3*CountryToChannel[xEEPROMBuffer[SystemCountry]]+2];		// min
		TV_Total=TvLimitTable[3*CountryToChannel[xEEPROMBuffer[SystemCountry]]+0];		// total	// Air-TV

		CATV_Max=CatvLimitTable[3*CountryToChannel[xEEPROMBuffer[SystemCountry]]+1];	// max	// CATV  
//		CATV_MIN=CatvLimitTable[3*CountryToChannel[xEEPROMBuffer[SystemCountry]]+2];	// min	
		CATV_Total=CatvLimitTable[3*CountryToChannel[xEEPROMBuffer[SystemCountry]]+0];	// total	// CATV  

	tmp=xEEPROMBuffer[CurrentChannel];	// 	// PreChannel저장을 위해서 백업.	
#if((NTSC_COUNTRY==1)||(AUTO_SETUPDEBUG==1))
		// ntsc
		if(AntenaFlag==ANTENA_AIR){		// Air인 경우 채널 보정
			if(IRDigitValue >= TV_Max) xEEPROMBuffer[CurrentChannel]=TV_Total-1;	// 미리 Min을 감산한다.		
			else if(IRDigitValue <= TV_MIN) xEEPROMBuffer[CurrentChannel]=0;
			else xEEPROMBuffer[CurrentChannel]=IRDigitValue-TV_MIN;
		}
		else{	// CATV인 경우 채널 보정
			if(IRDigitValue >= CATV_Max) xEEPROMBuffer[CurrentChannel]=CATV_Total-1;		
			else if(IRDigitValue <= CATV_MIN) xEEPROMBuffer[CurrentChannel]=0;			
			else xEEPROMBuffer[CurrentChannel]=IRDigitValue-CATV_MIN;
		}
		xEEPROMBuffer[PreChannel]=tmp;		// PreChannel저장.	
		EepromSetQue(CurrentChannel_adr,xEEPROMBuffer[CurrentChannel]);
		IRDigitValue=0x00;		// IRDigitValue는 채널 보정후 초기화한다.
#else	// PAL-Multi
			if(IRDigitValue > 99) xEEPROMBuffer[CurrentChannel]=99;		
			else if(IRDigitValue == 0) xEEPROMBuffer[CurrentChannel]=99;			
			else xEEPROMBuffer[CurrentChannel]=IRDigitValue-1;
			xEEPROMBuffer[PreChannel]=tmp;		// PreChannel저장.	
			EepromSetQue(CurrentChannel_adr,xEEPROMBuffer[CurrentChannel]);
			IRDigitValue=0x00;		// IRDigitValue는 채널 보정후 초기화한다.
#endif
	
	//---------------채널선국및 OSD Display---------------
	Mute_SoundOff;//PutVolume(FALSE);
	//LCDMute(0,1);//(1,0) -->  background color=Blue ,	free running mode로 osd는 띄우고 data는 mute시킨다.
	ChannelSel(xEEPROMBuffer[CurrentChannel]);	
	if(CheckChMask(xEEPROMBuffer[CurrentChannel])==0) {	// Enable된  chanel을 Display// test bit=0으로 한 경우 문제가 있어서 1로 수정함. by LKE 4/15  
		//if(ch >= CHANNELMEMORYMAX)  xEEPROMBuffer[CurrentChannel]=CHANNELMEMORYMAX-1; //channel memory를 벗어나는 경우는 디폴트.
//youngdo 2003.5.28		ShowOSDChannel(CheckChCATV(xEEPROMBuffer[CurrentChannel]),GetRealChannel(xEEPROMBuffer[CurrentChannel]),1,fGREEN);	// OSD Channel Display
	}
	else{	// Disable된  chanel을 Display	// test bit=0으로 한 경우 문제가 있어서 1로 수정함. by LKE 4/15  
		//if(ch >= CHANNELMEMORYMAX)  xEEPROMBuffer[CurrentChannel]=CHANNELMEMORYMAX-1; //channel memory를 벗어나는 경우는 디폴트.	
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
		if(KEY_value==MenuKey || KEY_value==PowerKey) tmp=1; // 화면이 부서지는 것을 방지 하기 위해서 보완. 2.24
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

// 이전 태이블 오프셋, Air(0)/Catv(1) 을 매개변수로 넘겨받아서 Nest Channel을 미리 세팅하는 기능을 수행한다.
/*  memory save  2003.6.3
	Bool NextChannelFreqSet(BYTE ChTblOffset, Bool CaAir){
	xdata BYTE	Ch_Total, Ch_Max, Ch_Min;
	xdata BYTE i;
	xdata WORD TDivider;
  	xdata unsigned short *p;
  	Bool TVSignalQaulity=0;
  	
	//---------이부분에서 이전 신호의품질을 체크한다.

	//-----------------------------------


	if(CaAir==0){		//Air인 경우 
		Ch_Total=TvLimitTable[3*CountryToChannel[xEEPROMBuffer[SystemCountry]]+0];		// total	// Air-TV
		Ch_Max=TvLimitTable[3*CountryToChannel[xEEPROMBuffer[SystemCountry]]+1];		// max
		Ch_Min=TvLimitTable[3*CountryToChannel[xEEPROMBuffer[SystemCountry]]+2];		// min
	}
	else{			// Catv인 경우.
		Ch_Total=CatvLimitTable[3*CountryToChannel[xEEPROMBuffer[SystemCountry]]+0];	// total	// CATV  
		Ch_Max=CatvLimitTable[3*CountryToChannel[xEEPROMBuffer[SystemCountry]]+1];	// max
		Ch_Min=CatvLimitTable[3*CountryToChannel[xEEPROMBuffer[SystemCountry]]+2];	// min
	}

	for(i=ChTblOffset; i < (Ch_Max-Ch_Min+1); i++){
			if( i == ChTblOffset ) continue;
 			// Channel Table을 위한 Offset계산---------
 			if(CaAir==0)
				p = AIR_TAB[CountryToChannel[xEEPROMBuffer[SystemCountry]]] + (WORD)i;	// Freq. Table로 부터 그값(PLL Divider Value)을  찾아서,
			else 
				p = CATV_TAB[CountryToChannel[xEEPROMBuffer[SystemCountry]]] + (WORD)i;	// Freq. Table로 부터 그값(PLL Divider Value)을  찾아서,
			//---삼성 ntsc튜너의 경우 스펙을 벗어나는 데이터필터링--------
			if(CURRENT_TUNNER != SAMSUNG_TCPN9082DA27C);
			else{	// 삼성튜너가 연결되어 있는 경우에, Low band 55.25Mhz미만의 주파수는 필터링한다.(튜너 스펙을 오버하는 주파수이다.)
				if(*p < 0x07E4)	continue;		// Dummy인 경우라면 Skip한다.
			}
			//----더미 데이터 필터링.--------------------------------------------
			if(*p == 0)	continue;		// Dummy인 경우라면 Skip한다.// PLL Divider Value가 Dummy Data인지 체크한다. 		// 1월 16일 Dummy Check하도록 추가함.
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

	ProgNo=1;	// Program Number초기화.
	for(i=0; i < CHANNEL_LIMIT); i++){
 		// Channel Table을 위한 Offset계산---------
		addr=ep_ChannelStartAir+2*i;
		p = AIR_TAB[CountryToChannel[xEEPROMBuffer[SystemCountry]]] + (WORD)i;	// Freq. Table로 부터 그값(PLL Divider Value)을  찾아서,
		
		if(*p == 0){ 		// PLL Divider Value가 Dummy Data인지 체크한다. 		// 1월 16일 Dummy Check하도록 추가함.
			continue;				// Dummy인 경우라면 Skip한다.
		}
		EepromSetQue(ep_ProgStart+ProgNo-1,i);	// Program영역에 Sync Channel을 등록한다.
		ProgNo++;	
		
		EepromSetQue(addr,0x01);		//  disable/air
		EepromSetQue(addr+1,AftRangeTable[xEEPROMBuffer[SystemCountry]]);	// default Fine Tune Data

		if(ProgNo > 100)break;
	}


	CHANNEL_LIMIT=CatvLimitTable[3*CountryToChannel[xEEPROMBuffer[SystemCountry]]+0];			
	for(i=0; i < CHANNEL_LIMIT; i++){
 		// Channel Table을 위한 Offset계산
		addr=ep_ChannelStartCatv+2*i;
		p = CATV_TAB[CountryToChannel[xEEPROMBuffer[SystemCountry]]] + (WORD)i;	// Freq. Table로 부터 그값(PLL Divider Value)을  찾아서,
		
		if(*p == 0){ 		// PLL Divider Value가 Dummy Data인지 체크한다. 		// 1월 16일 Dummy Check하도록 추가함.
			continue;				// Dummy인 경우라면 Skip한다.
		}

		EepromSetQue(ep_ProgStart+ProgNo-1,128+i);	// Program영역에 Sync Channel을 등록한다.
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


//  Return값으로 AFT Value를 리턴한다.
//   Return value 0xff -> 방송주파수가 없다. (그외의 값은 Ok)
//   AUTO Search내에서 사용할 경우. Test=0 으로 사용한다.
//   순수한 AFT만 사용할 경우 Test=1로 사용한다.
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
	//delay5m(AFT_NORMALTIME);	// 표준 타이밍.

	CheckTvSub();
	DBGputs("atf");
	if(Test==1){	// channel up/dn(selection)시에 사용.
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
	else{		// auto search시에 사용.
		first=0;
		AFTValue=0;				
#if (NTSC_COUNTRY == 0)
			delay5m(30);
#endif
	}
	
	// auto search수행을 위한 초기화.
	//first=1;	// AFT가 최초 Start됨을 체크하는  플래그.
	SearchOK=0x00;		// sync search단계로 들어가기 위해서...
			
//-------------------Sync Search를 수행한다.--------------------------------------------
// SearchOK Flag의 상태에 대한 Description은 아래와 같음.
// 07 정튜닝. --> 마무리작업을 수행한다.
// 00 싱크없는 상태.  --> sync search를 수행한다.
// 01 싱크정보만 얻은 상태. --> AFT를 수행하기 위한 전 단계작업을 수행한다.
// 02  AFT를 수행하기 위한 전 단계작업. --> AFT진행을 위해서 데이터를 체크한다.
// 17 방송이 없는 채널로 처리한다.
// 03/04인 경우 --> AFT Data Search Loop를 수행중이다.
// 06 방송이 있는 채널이며 버퍼에 저장된 AFT Data 탐색을 수행하는 단계이다.--> 정확한 Auto Fine Tune Data를 찾아낸다.
// 17 AFT Range Over되는 경우. --> Search Fail로 처리한다.
	Sync_SearchStep:		// 0. ID확인 	// Sync없는 경우에 수행되는 Loop
	while(SearchOK==0x00){	
			TvPllOk(AFTDivider+AFTValue-AftRangeTable[xEEPROMBuffer[SystemCountry]]);	
			delay5m(AFT_MAINTIME);
			CheckTVSignal(AFT_MAINCOUNT);
			
			if(eTVSyncFlag) {		// sync 와 xx 검출시에만..
#if(NTSC_COUNTRY==0)
				if(first){	// 처음 구간에서 싱크를 찾을 경우는 시간적인 마진을 더준다.
					TvPllOk(AFTDivider+AFTValue-AftRangeTable[xEEPROMBuffer[SystemCountry]]);
					delay5m(10);
					TvPllOk(AFTDivider+AFTValue-AftRangeTable[xEEPROMBuffer[SystemCountry]]);	
					delay5m(10);
				}
#endif
				SearchOK=0x01;
				break;
			}
			else	{AFTValue+=30;	}//No Synce시  -->  Sync Search Step=0.5Mhz	
			//}
			//else  {AFTValue+=30;}// Sync Search Step=1.5Mhz	--> 무신호시 
		
			if(first){first=0;AFTValue=0;}	// Sync Search스탭에 본격적을 진입하기 위해서 AFT값을 초기화를 한다.
			
			if(AFTValue>AftRangeTable[xEEPROMBuffer[SystemCountry]]*2) {SearchOK=0x17; break;}		// while loop탈출 조건----> Sync Search상한치(Fc+2.5Mhz)초과한 경우.
	}
//------------------Auto Fine Tunning을 수행한다.-----------------------------------
	//AUTOFINE_STEP1:		// 1.튜너 데이터 확인.
	if(SearchOK==0x01){	// Sync찾은 경우에는 Tuner Aft Data를 체크한다.
			switch(0x07 & (BYTE)ReadTuner()){
				case 4:	SearchOK=0x02;	AFTValue+=K_STEP1;	break;	// next step go go!!
				case 3:	SearchOK=0x02;						break;	// next step go go!!
				case 2:	if(first) {		//최초 세팅 주파수로 첫번째 찾지 못하고, 두번째  세팅시에 찾은 경우.
							//printf("2"); 
							return (AFTValue);
						}	
						SearchOK=0x02;	//SearchOK=0x07;					
						break;			// next step go go!!
				case 1:											// search fail처리한다.
				case 0:	SearchOK=0x00; 					break;	// search fail처리한다.		
			}
			if(SearchOK==0x00) {AFTValue+=10; goto Sync_SearchStep;}
	}
			
	//AUTOFINE_STEP2:
	if(SearchOK==0x02){	LKE_Flag=0;SearchOK=0x03;}

	AUTOFINE_STEP3:	
	while(SearchOK==0x03){		// AutoFine Tunning을 수행한다.
			Tun_time=0;
			//------버퍼 초기화.--------
			for(kkk=0;kkk<12;kkk++) OSDStringBuff2[kkk]=0x00;	// 버퍼 초기화. --> AFT 데이터 
			for(        ;kkk<24;kkk++) OSDStringBuff2[kkk]=0xff;	// 버퍼 초기화. -->  Tune데이터 (Tune data는 0~4의 범위를 갖는다.)
			BufferFull=0;		// Buffer Full flag를 클리어.
			kkk=0x00;		// AFT Data Buffer pointer초기화.
			
			//-------최초 AFT Data저장------------------
			OldTune=0x07 & (BYTE)ReadTuner();
			OSDStringBuff2[0+kkk]=AFTValue;		// AFT 데이터 저장.
			OSDStringBuff2[12+kkk++]=OldTune;		//  AFT 데이터에 대응하는 Tune 데이터 저장.// 데이터 저장후 버터 포인터 증가.

			switch(OldTune){	// 주파수가 증가하는 방향으로 튜닝을 수행한다.
				case 4:	AFTValue+=K_STEP1;	break;	// good!!
				case 3:	AFTValue+=1;		break;	// good!!// Tun_time=1 --> 미세조정을 한다.
				case 2:	SearchOK=0x06;		break;	//***  very good!!
				case 1:
				case 0: 	AFTValue+=10; 		goto Sync_SearchStep;			
			}
			if(SearchOK==0x03) SearchOK=0x04;
			
			//-----AFT Data저장루프----------
			while(SearchOK==0x04){
				if(AFTValue>(1+AftRangeTable[xEEPROMBuffer[SystemCountry]]*2)){	// AFT Range벗어나는 경우에는 종료한다.
					SearchOK=0x17; 	
					break;
				}
				
			if(LKE_Flag==1){	// tunning data가 4인 데이터를 걸러낸다.
				 	LKE_Flag=0;
					TvPllOk(AFTDivider+AFTValue-AftRangeTable[xEEPROMBuffer[SystemCountry]]);
				 	delay5m(NUM_20);//delay5m(5);
					//TvPllOk(AFTDivider+AFTValue-AftRangeTable[xEEPROMBuffer[SystemCountry]]);
				 	//delay5m(5);
			}
			else{
					TvPllOk(AFTDivider+AFTValue-AftRangeTable[xEEPROMBuffer[SystemCountry]]);
					delay5m(AFT_NORMALTIME);
				///if(Tun_time==1){ // Tun_time=1 --> 미세조정을 한다.
				///	Tun_time=0;
				///	delay5m(AFT_MAINTIME);				/// --> Tun_time Data에 따른 미세조정을 원한다면 
				///	CheckTVSignal(AFT_MAINCOUNT);	///       ///을 푸시면 됩니다.
				/// }									/// 시간을 세이브하기 위해서 막은 것임. by LKE 4/16
				/// else{
					//delay5m(AFT_MAINTIME);
				 	CheckTVSignal(AFT_MAINCOUNT);
				 ///}
					if(!eTVSyncFlag) {	//No Sync 가 검출되면  Sync Search단계로 되돌아 간다.
						SearchOK=0x00; 
						goto Sync_SearchStep;
					}	
			}
				//-----New AFT Data저장--------------
				NewTune=0x07 & (BYTE)ReadTuner();
				if(kkk==12) {		//버퍼 Full상태 --> 포인터 처음으로 돌리는 조건검출시.---> AFT Data Buffer pointer초기화.
					kkk=0;BufferFull=1; //printf("B");	
				}		
				OSDStringBuff2[0+kkk]=AFTValue;	// AFT 데이터 저장.
				OSDStringBuff2[12+kkk++]=NewTune;	// Tune 데이터 저장.

				//------*** AFT Data변화량을 체크하고  Next Step결정하는 단계로 들어간다.*** -----------
				//값의 변화가 없는 경우.---> 정상적인 기울기.(기울기 = Zero)
				if((OldTune-NewTune)==0){ 
					//printf("0");
					switch(NewTune){	// 주파수가 증가하는 방향으로 튜닝을 수행한다.
						case 4:	AFTValue+=K_STEP1;	
								LKE_Flag=1; 
								SearchOK=0x03;
								goto AUTOFINE_STEP3;			// data가 4인 경우는 많으므로 버퍼초기화.
						case 3:	
						case 2: 	AFTValue+=1;			break;	//*** (special case) next step go go!!
						case 1: 	
						case 0: SearchOK=0x00;			break;				
					}
				}
				LKE_Flag=0; 
				//값의 변화가 발생한 경우. --> 정상적인 기울기.(기울기= +)
				if(OldTune>NewTune){
					//printf("+");	
					switch(NewTune){	// 주파수가 증가하는 방향으로 튜닝을 수행한다.
						case 4:  AFTValue+=K_STEP1;			break;  	// --> 이경우는 없다.(주의)
						case 3:	AFTValue+=1;				break; 	// 4-->3으로 변화 발생.  (x버퍼초기화.)  <-- We are the world.
						case 2:	
#if( TUNER_MANUFACTURER==SAMSUNG)
								SearchOK=0x06;	break;
#else
								AFTValue+=1;	
								break; 	// 3-->2으로 변화 발생.  	want.
#endif								
						case 1:				SearchOK=0x06;	break;  	// *** next step go go!!// 2-->1로 변화 발생.  (data검색을 시작 )  <-- Best Choice!!
						case 0:				SearchOK=0x00;	break;  	// 1-->0로 변화 발생.  (data검색을 시작 )  <-- 주의: 이경우는 현상적으로 생길수 없다.				
					}
				}
				
				//값의 변화가 발생한 경우. -->  No Wanted 기울기.(기울기= -)
				if(OldTune<NewTune){		// 정상적인 경우 Tune Data가 0-->4로의 변화만을 예측 할 수 있다.
					//printf("-");			// 그러나 program 처리 흐름상 Negative기울기가 나오기는 힘들다.
					SearchOK=0x00;		// 따라서 Sync Search단계로 처리한다. 	
				}					

				// Sync Search단계로 되돌린다. 
				if(SearchOK==0x00) {AFTValue+=10; goto Sync_SearchStep;}

				// Previous Tune Data저장.
				OldTune=NewTune;	
			}
			//--------------
			if(AFTValue>(1+AftRangeTable[xEEPROMBuffer[SystemCountry]]*2)){SearchOK=0x17; break;}	// AFT Fine Tune data search fail로 처리한다.
	}

//-------------데이터 검색을 수행하여 최적화된 Tunning값을 찾는다.(SearchOK==0x06)---------------------
	if(SearchOK==0x06){	

				//----------마지막 포인터 백업한다.
				if(BufferFull==1){
					if(kkk==0) Backupkkk=11;
					else  Backupkkk=kkk-1;	
				}
				else Backupkkk=kkk-1;	// 마지막 포인터 백업한다.

				//-----------TEST(데이터 덤프)--------
				//kkk=0;



				//-----최초 정튜닝 데이터의 offet(Backupkkk)과 연속적으로 나열된 정튜닝 데이터 의 개수(CountTuneOk)를 구한다.
				first=0;
				if(BufferFull==1){	// buffer full이 발생한 경우라면, 로테이션 체크를 수행한다.
					kkk=Backupkkk;
					for(pp=0;pp<12;pp++){	
						if(2== OSDStringBuff2[12+kkk]) {CountTuneOk=0;break;}	// Tune data검색.
						if(kkk==0) kkk=11;
						else kkk--;
					}
					Backupkkk=kkk;	// 마지막 정튜닝 데이터의 offet을 백업한다.
					for(;pp<12;pp++){	
						if(2== OSDStringBuff2[12+kkk]) {
							Backupkkk=kkk;
							CountTuneOk++;	// temp에는 2의 개수가 저장된다.
							if(kkk==0) kkk=11;
							else kkk--;	// kkK에는 최종적으로 최초 정튜닝 데이터의 offet이 저장된다. 
						}
						else {first=1; break;}	// Tune data검색.
					}
				}
				else{	// normal check를 수행한다. --> 최초 데이터를 찾는다.
					kkk=0;	
					for(pp=0;pp<12;pp++){
						if(2== OSDStringBuff2[12+kkk]) {
							Backupkkk=kkk;	// 최초 정튜닝 데이터의 offet을 백업한다.
							CountTuneOk=0;
							break;
						}
						kkk++;
					}
					for(;pp<12;pp++){	
						if(2== OSDStringBuff2[12+kkk++]) {CountTuneOk++;}	// pp에는 연속으로 나열된 정튜닝 데이터의 수를 찾는다..
						else {first=1; break;}
					}
				}
				//------------------------------------
				if(first==1){	// 정튜닝 데이터를 찾은 경우.

					// CountTuneOk=>연속적으로 나열된 정튜닝 데이터 의 개수를 Count하기 위해 사용 --> 변수 초기화.
					// 정튜닝 데이터의 개수와 포인터 정보를 이용하여 AFT Fine Tune데이터를 찾는다.
					switch(CountTuneOk){		//삼성 튜너는 1~2개이다.
						case 1:
						case 2:		// 정튜닝 데이터가 1,2라면, 첫번째 Data를 취한다.
							AFTValue=OSDStringBuff2[Backupkkk];break;	// AFT Data저장.
						case 3:		// 정튜닝 데이터가 3,4개 이면 두번째 Data를 취한다.
						case 4:
							if(BufferFull==1){
								if(Backupkkk==11) AFTValue=OSDStringBuff2[0];
								else   AFTValue=OSDStringBuff2[Backupkkk+1];
							}else AFTValue=OSDStringBuff2[Backupkkk+1];
							break;	// AFT Data저장. 
						case 5:	// 정튜닝 데이터가 5개 이면 3번째 Data를 취한다.
							if(BufferFull==1){
								if(Backupkkk==11) AFTValue=OSDStringBuff2[1];
								else if(Backupkkk==10) AFTValue=OSDStringBuff2[0];
								else  AFTValue=OSDStringBuff2[Backupkkk+2];
							}else  AFTValue=OSDStringBuff2[Backupkkk+2];
							break;
					}

					 if((CountTuneOk>5)||(CountTuneOk==0)) {	// 정튜닝 데이터가 6개 이상인 경우 --> Fail처리한다.
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
		
//------------- 최적화된 Tunning값을 리턴한다.---------------------
	switch(SearchOK){
		case 0x07:
#if( TUNER_MANUFACTURER==SAMSUNG)	// 삼성튜너인 경우.(Ntsc/Pal모함.)


	//#if (CURRENT_TUNNER==SAMSUNG_TCPN9082DA27C)
	//#if (1)
		// 삼성튜너의 경우 AFT동작이 수행되는 중에는  1step의 지연이 있다. --> 보정함.(case by case)
		// 삼성튜너의 경우 --> 동특성에 대한  튜닝데이터 보정. 
		//#if (NTSC_COUNTRY==1)
			AFTValue=AFTValue;
		//#else
		//	AFTValue=AFTValue-1;		// 1step의 지연이 있다. -> AFT Range수정하면서막음.
		//#endif
			if(AFTValue>AftRangeTable[xEEPROMBuffer[SystemCountry]]*2){return (0xff);}
 			if(Test==1){	
 				// channel up/dn(selection)시에 사용.
				TvPllOk(AFTDivider+AFTValue-AftRangeTable[xEEPROMBuffer[SystemCountry]]);	
			}
			return (AFTValue);	// AFT Find.
	//#else
	//		if(AFTValue>AftRangeTable[xEEPROMBuffer[SystemCountry]]*2){return (0xff);}
 	//		if(Test==1){	
 	//			// channel up/dn(selection)시에 사용.
	//			TvPllOk(AFTDivider+AFTValue-AftRangeTable[xEEPROMBuffer[SystemCountry]]);	
	//		}
	//		return (AFTValue);	// AFT Find.
	//#endif


			
#else	//삼성튜너가 아닌경우 (Ntsc/Pal모함.)
 			if(Test==1){	// channel up/dn(selection)시에 사용.
				if(AFTValue>AftRangeTable[xEEPROMBuffer[SystemCountry]]*2){return (0xff);}
				TvPllOk(AFTDivider+AFTValue-AftRangeTable[xEEPROMBuffer[SystemCountry]]);	
			}
			return (AFTValue);	// AFT Find.

#endif

		case 0x17: 	return (0xff);		// AFT No found.
		default:			// bug 발생.
					return (0xff);
	}
#endif
}
*/


// by LKE 2/22 
// EEProm의 Start Offset부터 End Offset특정값으로 채울때 사용한다.  
// EEProm을 start offset 부터  end offset 까지 value1과 value2로 연속하여 write를 행한다.
// Note: ..
// (EEProm start address, start offset, end offset, value1, value2)
/* youngdo 2003.5.28    임시로 막아둠. ************************************
void EepTvFillValue(WORD Addr,BYTE StartOffset,BYTE EndOffset,BYTE Value1,BYTE Value2)
{
		xdata BYTE kkk;
		xdata WORD i,BackupAddr;


		return;
		
		Addr=Addr+(WORD)StartOffset;
		i=(WORD)StartOffset;

		if(i>(WORD)EndOffset) return;
		
		//------ page단위로 write가 불가능시에는 1BYTE단위로 Write를 행한다.
		for(i=(WORD)StartOffset;i<=(WORD)EndOffset;i++) {	
			if(i>(WORD)EndOffset) return;		// 모두 채워졌다면 종료.
			if(0x00==(Addr%16)) break;	// page 발견...
			EepromSetQue(Addr++,Value1);	//  Nousing/Air/Disable Data, 
			EepromSetQue(Addr++,Value2);	// FineTune Data를 50으로 초기화.
			i++;
		}
		
		//--------page단위로 Write를 행한다.
		kkk=0;	
		for(; i <= (WORD)EndOffset; i++){
			OSDStringBuff[kkk++]=Value1; 	//  Nousing/Air/Disable Data, 
			OSDStringBuff[kkk++]=Value2;		// FineTune Data를 50으로 초기화.
			i++;
			if(kkk==16){	// 16byte가 버퍼에 채워지면 write..
				kkk=0; 
				write24c16Page(Addr, OSDStringBuff);
				Addr+=16;
			}

			// EndOffset까지 왔는데,  EndOffset의 값이 Page단위의 마지막 offset값 으로 
			// 적당하지 않을 때 수행된다. 
			if( i == (WORD)EndOffset){
				if((kkk < 16)&&(kkk != 0)){
					BackupAddr=Addr;
					Addr=Addr+kkk;	// Address지정.
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
// xEEPROMBuffer[CurrentChannel]로 Tuner세팅하고, Channel OSD를 Display한다. 
// 먼저 osd display하고 튜너세팅하도록 수정() --> by LKE 2.15 --> 이렇게 하면 vpx가 color를 잘인식하지 못함.
void ViewCurrentChannel(void)		
{
//	Bool ChannelBool;
	Pre_ChannelSel(xEEPROMBuffer[CurrentChannel]);	// Pre set.
	

	//--channel osd display를 행한다.(ntsc/pal에 따라서 다르게 표시함)
/*youngdo 2003.5.28****************************************************************
	if(OsdState==CHANNEL) ChannelBool=0;	// 이미 Channel OSD가 떠있는 경우라면..
	else ChannelBool=1;	
	if(CheckChMask(xEEPROMBuffer[CurrentChannel])==0)	// Enable된  chanel을 Display --> Green 으로 channel osd표시
		ShowOSDChannel(CheckChCATV(xEEPROMBuffer[CurrentChannel]),GetRealChannel(xEEPROMBuffer[CurrentChannel]),ChannelBool,fGREEN);	// OSD Channel Display
	else		// Disable된  chanel을 Display--> Yellow로 channel osd표시
		ShowOSDChannel(CheckChCATV(xEEPROMBuffer[CurrentChannel]),GetRealChannel(xEEPROMBuffer[CurrentChannel]),ChannelBool,fYELLOW);	// OSD Channel Display
*******************************************************************************/

	ChannelSel(xEEPROMBuffer[CurrentChannel]);	// Prog No를 이용하여 --> Tunner를 세팅한다.

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
// 1월16일 Jho
// by Lee 2.11 void return에서 Bool return으로 수정함.

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


// check 5/12 by LKE PAL의 경우 No-Using Channel처리 옵션 추가함.
// check 2/23 by LKE
// ProNoMask_Flag를 체크한다.( 0 : Enable, 1 : Disable)
Bool CheckChMask(BYTE channel)
{
	xBYTE flag;
//	DBGputs("CheckChMask");
	#if((NTSC_COUNTRY==1)||(AUTO_SETUPDEBUG==1))||defined(FrequncyTableType)

		flag=GetChannelStatus(channel);
		return	(flag & BIT_0);

	#else			// PAL-Multi

		flag=GetChannelStatus(channel); //여기서 eprom 2번읽는다..
		if( (EEPROM_Read(ep_ProgStart+(WORD)channel)==0xff) || ((flag & BIT_0) != 0) )
		//if( ((flag & BIT_0) != 0) )
			return 1;	// Disable
		else 
			return 0;	// ENable

	#endif
}

// check 2/23 by LKE
// CableAir_Flag를 check한다.(1:Cable-TV, 0:Air-TV)
Bool CheckChCATV(BYTE channel)
{
	#if( (NTSC_COUNTRY==1)||(AUTO_SETUPDEBUG==1) ||defined(FrequncyTableType) )
		// NTSC
		channel=channel+0x00;	// dummy 무의미한 실행. 컴파일경고안나게..
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
// FineTune_Flag를 check한다.(1:manual tune, 0:auto tune) 
Bool CheckChFineTune(BYTE channel)
{
	xBYTE flag;
//	DBGputs("CheckChFineTune");
	flag=GetChannelStatus(channel);
	return	(flag & BIT_2);
//	if(flag & BIT_2)	return 1;		//manual fine tune이  enable되어져 있다.
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
// ntsc--> 채널이 사용가능한지를 체크한다. ( 0 : Using, 1 : NoUsing) 
// program no -> 채널 할당이 되어 있지 않음.( 0 : Using, 1 : NoUsing) 
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
// Program Number에 할당되어진 channel table offset을 eeprom으로 부터 얻는다. 
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
// Manual Fine Tune Data를 eeprom으로 부터 Read
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
// Fine Tune Data만을 Write한다.(flag는 셑트하지 않음.)
 
void  SetFineTune(BYTE channel,BYTE value)
{
	#ifndef	FrequncyTableType	//++++++++++++++++++++++++++++++++
	
	#if((NTSC_COUNTRY==1)||(AUTO_SETUPDEBUG==1))		// NTSC
		if(AntenaFlag)	EepromSetQue(ep_ChannelStartCatv+(WORD)channel*2+1,value);
		//if(AntenaFlag)	EepromSetQue(ep_ChannelStart+(WORD)channel*2+1,value);
		else				EepromSetQue(ep_ChannelStartAir+(WORD)channel*2+1,value);		
	#else			// PAL-Multi
		BYTE AddrEEp;
		//if(CheckChNotUSE(channel))	;	//EepromSetQue(ep_ProgStart+100,value);	// by LKE 5/12 No-Using Channel 처리를위해서 추가.
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
// AFT data를 Write하고 AFT Flag를 세트한다. -> AFT Falg를 셋트하지 않는다. 4.24일 LKE
/*  memory save  2003.6.3
void  SetAutoFineTune(BYTE channel,BYTE value)
{
///	BYTE flag;
#if((NTSC_COUNTRY==0)&&(AUTO_SETUPDEBUG==0))
	xBYTE AddrEEp;
	AddrEEp=0;
#endif
	SetFineTune(channel,value);	// AFT또는Fine Tune  data Write

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


// Tuner설정후 PLL안정화되는지를 체크 
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
			if(errorflag==0x80) return;	// Tuner 연결안된 경우이면 종료.
			if((i==0x50)||(i==0x70)||(i==0x60)) return;	// phase Lock OK이면 종료.{순서대로 lg(ntsc),samung(ntsc),samung(pal)}
		}
		break;
	}	
	
}

#if (TOTAL_CHANNEL_SEARCH_RS232==1)

#define START_VALUE 0x069d
#define END_VALUE 0x4970	// 약 901Mhz

void TunerTestSearch(void){
	xdata WORD Devider_Test=0;
	xdata WORD OLD_Value=0;
	
	for(Devider_Test=START_VALUE; Devider_Test<END_VALUE+1;Devider_Test++){
		TvPllOk(Devider_Test);
		if(errorflag==0x00) {
			if((ReadTuner()&0x07)==0x02)	{
				if((Devider_Test-OLD_Value)>50){

					delay5m(10);	// 싱크서치를 위한 타이밍 적절하게 조절요함.
					CheckTVSignal(AFT_MAINCOUNT);
					if(eTVSyncFlag && ((0x07 & ReadTuner())==0x02)){
						NT68520CmdWrite(0x6F,NT68520CmdRead(0x6F)|0x06);		// Input Timing Recalibration을 행한다.		
						OLD_Value=Devider_Test;
					}
				}
			}
		}
	}
}
#endif



// check 2/20 by LKE  
// --> Pal-Multi의경우 NoUsing Program No인 경우 Catv max 채널 주파수로 세팅한다.
//  Pal-Multi의경우 NoUsing Program No에 대해서 
//                    --->  ProgEdit영역에서 0xff로 설정된 데이터는 NoUsing Program No로 처리한다.
// Prog No에 대한 실제 channel table offset을 계산(Manual Tune고려)후에, Tunner를 세팅한다.
// Tuner 세팅후 0.5초 Sleep한다.
// 3.1일 --> AFT를 하지 않는 조건을 추가함.(채널이 disable되어 있는 경우에는 Center Freq로 세팅)
void ChannelSel(BYTE ch)
{
	xdata unsigned short *p;
	xdata WORD	Divider;
	xBYTE  FineTune,ChannelStatus;
	
	#ifdef USE_UART	
	DBGputs("ChannelSel");
	#endif
	if(ch > CHANNEL_LIMIT)  return;		// Pal-Multi : 1월15일 128-->100으로 변경.

	//-----
	#if(NTSC_COUNTRY==0)&&!defined(FrequncyTableType)		// PAL-Multi
		if(CheckChNotUSE(ch))
		{	// no using채널 의 경우. --> Catv max 채널 주파수로 세팅한다. -> // 855.25Mhz로 세팅. by LKE 5/12
			#ifdef TunerRefDiv512
			TvPllOk(0x38E2);//TvPllOk(*p);  // 871.25Mhz로 세팅. (china max다음_ch)
			//DBGputs("  TvPllOk(0x3862)");	
			#else
			TvPllOk(0x45db);//TvPllOk(*p);  // 855.25Mhz로 세팅.
			#endif
			//delay5m(25);	// by LKE 2.25
			CheckTVSignal(5);	// 1.27cho
			return;
		}
	#endif
	//--------

	// Using channel...
	// Prog No에 대한 실제 channel table offset을 계산 한다.
	if(CheckChCATV(ch)==0) 	// Air-TV인 경우
		p= AIR_TAB[CountryToChannel[xEEPROMBuffer[SystemCountry]]]+GetRealChannel(ch);
	else					// Cable-TV인 경우
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
		

	#if	0	// youngdo 2003.6.2   일단 aft는 막아놈.
	if(((ChannelStatus&0x05) != 0) ||(ATFEnable==0) ){	// disable,finetune,AFT Disable된 경우.
		Divider = Divider + (WORD)FineTune - AftRangeTable[xEEPROMBuffer[SystemCountry]];
		TvPllOk(Divider);
		delay5m(25);
	}
	else{		// 그외에는 AFT를 수행한다.
		BackupTune=FineTune;	
		FineTune=AftSubFunction(Divider,FineTune,1);
		if(FineTune==0xff) {
				FineTune=AftRangeTable[xEEPROMBuffer[SystemCountry]];
				TvPllOk(Divider);
				delay5m(25);
		}
		else if(BackupTune!=FineTune)	SetAutoFineTune(ch,FineTune);	// AFT결과를 Write하고 aft flag를 세트한다.		
	}
	#endif

	CheckTVSignal(5);	// 1.27cho

}

void SetFinePLL(BYTE ch,BYTE FineTune)
{
	xdata unsigned short *p;
	xdata WORD	Divider;

	if(ch > CHANNEL_LIMIT)  return;		// Pal-Multi : 1월15일 128-->100으로 변경.

	if(CheckChCATV(ch)==0) 	// Air-TV인 경우
		p= AIR_TAB[CountryToChannel[xEEPROMBuffer[SystemCountry]]]+GetRealChannel(ch);
	else						// Cable-TV인 경우
		p=CATV_TAB[CountryToChannel[xEEPROMBuffer[SystemCountry]]]+GetRealChannel(ch);	

	Divider = *p;		// Tuner PLL Divider Value		

	Divider = Divider + (WORD)FineTune - AftRangeTable[xEEPROMBuffer[SystemCountry]];		
//	DBGputss((BYTE)(	Divider>>8));
//	DBGputss((BYTE)(	Divider&0xff));
	TvPllOk(Divider);
	idelay5m(2);
	TvPllOk(Divider);
	CheckTVSignal(1);	// 1.27cho	

	//LED_OFF;idelay5m(200);LED_ON;//test//2004-05-07 11:24오전
	
}

void Pre_ChannelSel(BYTE ch)
{
	xdata unsigned short *p;
	xdata WORD	Divider;
	xBYTE  FineTune;//BackupTune,
	
	if(ch > CHANNEL_LIMIT)  return;		// Pal-Multi : 1월15일 128-->100으로 변경.

	#if(NTSC_COUNTRY==0)&&!defined(FrequncyTableType)
		// PAL-Multi
		if(CheckChNotUSE(ch))
		{	// no using채널 의 경우. --> Catv max 채널 주파수로 세팅한다.
			#ifdef TunerRefDiv512
			TvPllOk(0x38E2);//TvPllOk(*p);  // 871.25Mhz로 세팅. (china max다음_ch)
			#else
			TvPllOk(0x45db);//TvPllOk(*p);  // 855.25Mhz로 세팅.
			#endif
			return;
		}
	#endif


	// Using channel...
	// Prog No에 대한 실제 channel table offset을 계산 한다.
	if(CheckChCATV(ch)==0) 	// Air-TV인 경우
		p= AIR_TAB[CountryToChannel[xEEPROMBuffer[SystemCountry]]]+GetRealChannel(ch);
	else						// Cable-TV인 경우
		p=CATV_TAB[CountryToChannel[xEEPROMBuffer[SystemCountry]]]+GetRealChannel(ch);	
   
	Divider = *p;		// Tuner PLL Divider Value	
	FineTune = GetFineTune(ch);
//	xEEPROMBuffer[NTSC_AIRTVFine_buf]=FineTune;
	Divider = Divider + (WORD)FineTune - AftRangeTable[xEEPROMBuffer[SystemCountry]];
	TvPllOk(Divider);
}



// Fw<Fc인 경우에 사용한다.  LKE
//  Phase Lock되고, Power ON reset Status까지체크한다. LKE 1.24
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

// ReadTuner()에서 사용하기 위한 루틴이다.
// 단순히, Tuner Status를 읽어서 return한다.
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



// errorflag에 따른 data
// 0x00 --> Phase Lock Ok, Tuner있다.
// 0x01 --> Phase Lock Fail , Tuner있다.
// 0x80 --> Tuner없다.	따라서 
// errorflag에 관계없이 Tuner Read Data는 정상적으로 return된다.
unsigned char ReadTuner(void)
{
	xBYTE BackUp1,BackUp2,i;//,TestData;
	xBYTE tmptest=0;

	i=0;
	errorflag=0x00;

	//if(NoTunerFlag) {		// 동작중에도 Tuner를 체크하기 위해서 막음. --> by LKE 2.14
	//	errorflag=0x80;
	//	return	0xff;
	//}

	//-------아래에는 spec범위내의 데이터를 튜너에 세팅시에 나타나는 튜너 상수를 기록하는 부분이다.
	//-------목적 : 중요하므로 필독!!
	//switch(CURRENT_TUNNER){
	//	case LGINOTEK_TAPC_H701F:		// LG NTSC 구형튜너.
		// pll locking된 경우의 상위니블값은 5이다. 	2.13 by LKE 결정.
		// ---> note:안테나가 연결안되어도 ,Pll Locking된다.
		// locking되지 않는 경우는, 범위를 벗어난 pll 데이터를 setting하거나,  system power on/off시에 발생한다.
		// 이 때의 값은 3이거나 b가된다.
	//		TestData=0x50; break;	
	//	case SAMSUNG_TCPQ9091PD27D:	// samsung PAL 구형 튜너.
		// pll locking된 경우의 상위니블값은 7이다. 	2.13 by LKE 결정.
		// ---> note:안테나가 연결안되어도 ,Pll Locking된다.
		// locking되지 않는 경우는, 범위를 벗어난 pll 데이터를 setting하거나,  system power on/off시에 발생한다.
		// 이 때의 값은 3이거나 b가된다.			
	//		TestData=0x60; break;	// 27D(s)의 경우 0x60 read됨.
	//	case SAMSUNG_TCPN9082DA27C:	// samsung NTSC 구형튜너.
		// pll locking된 경우의 상위니블값은 7이다. 	2.13 by LKE 결정.
		// ---> note:안테나가 연결안되어도 ,Pll Locking된다.
		// locking되지 않는 경우는, 범위를 벗어난 pll 데이터를 setting하거나,  system power on/off시에 발생한다.
		// 이 때의 값은 3이거나 b가된다.		
	//		TestData=0x70; break;	
	//	default:
	//		TestData=0x50; break;
	//}
	//---------------	
	while(1)
	{
			BackUp1=TunerDataCatch();
			//-------------// Tuner가 Disable되어 있는 경우 다시 살린다.  --> by LKE 2.14
			if((NoTunerFlag)&&(BackUp1!=0xff)) NoTunerFlag=1;	

			//----------------// 튜너가 동작 불능된 경우 Tuner Disable시킨다. //--> by LKE 2.14
			if(BackUp1==0xff) 
			{		
				///BYTE tmptest=0;
				if(TunerDataCatch()==0xff) tmptest++;
				if(TunerDataCatch()==0xff) tmptest++;

				if(tmptest>=2)
				{		// Tuner disable 조건이 발생한 경우.
					errorflag=0x80; 
					if(NoTunerFlag);
					else  NoTunerFlag=1;
					return(BackUp1);
				}
			}
			//---------------------
			if(i>3)
			{ 	// Tuner Spec이외의 데이터가 들어가 튜너가 이 루프에서 빠져나오지 못하는 것을 방지 .
					errorflag=0x01;
					return(BackUp1);
			}
			if(((BackUp1&0xF0) != 0x50)&&((BackUp1&0xF0) != 0x60) &&((BackUp1&0xF0) != 0x70) )
			{	// Phase LOCK Fail
					i++;
					continue;
			}
			else	
			{	// Phase Lock Ok인 경우 튜너 데이터를 다시한번 확인한 후 그값을 리턴한다.
				BackUp2=TunerDataCatch();
				if(BackUp1==BackUp2) 
				{// 다시한번 확인한다.
					errorflag=0x00; 	// Sucess!!
					return(BackUp1);
				}
			}
	}

}



// Fc<Fw인 경우에 사용한다.  LKE
//  Phase Lock되고, Power ON reset Status까지체크한다. LKE 1.24
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

// 튜너를 Disable시킬지를 판단하기 위한 루틴.
//
// 사용방법 : 이루틴은 system의 Power가 On 될 때마다 한번 씩 수행해준다. 
// Tuner Enable --> NoTunerFlag=0
// Tuner Disable --> NoTunerFlag=1
void TunerTest() 
{	
	xdata BYTE tmp;
	NoTunerFlag=0;
	
	SetTuner((WORD)0x2020);	// 적당한 PLL Divider로 세팅한다.

	// SetTuner후에 errorflag의 상태를 읽어서 Tuner를 Disable시킬지를 결정한다.

	BTC_START_I2C(TunerAddr+1);
	tmp=(BYTE)BTC_ReadDataNAK();
	BTC_STOP_I2C();

	if(tmp==0xff) NoTunerFlag=1;	// Tuner 연결되어 있지 않은경우에 set시킨다.
	else	NoTunerFlag=0;

}

// PLL Divider value및 Tuner Parameter를 Tuner에 세팅한다.
// 1월16일 : 밴드 스위칭 데이터 수정.(튜너별로 구분하여 선택되도록 함.)
// 1월16일 : SAMSUNG_TCPQ9091PD28L(SamSung 신형튜너)세팅을 위한 코드 추가.
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
		// SAMSUNG_TCPN9082DA27C Tuner Spec명기(ntsc) 
		// Band Switching을 위한 기준 데이터.			 Fosc=Frf+Fif(45.75Mhz)	PLL Divider변환값.
		// VHF Low: 	55.25Mhz		~ 	163.25Mhz  --> 101Mhz ~ 209Mhz    ---> 0x07e4 ~ 0x1054
		//                          sntsc_VHF 166.25Mhz   --> 212Mhz --------------> 0x1090
		// VHF High: 	169.25Mhz 	~ 	451.25Mhz  --> 215Mhz ~ 497Mhz    ----> 0x10cc ~ 0x26d4
		//                          sntsc_UHF 454.25Mhz   --> 500Mhz --------------> 0x2710
		// UHF       :  457.25Mhz 	~ 	855.25Mhz  --> 503Mhz ~ 901Mhz    ---> 0x274c ~ 0x4664
		// freq range: 0x07e4 ~ 0x4664 --> spec 범위를 벗어나는 세팅을 하지 마세요.

//		case SAMSUNG_TCPN9082DA27C:	// 튜너 구분 : (SAMSUNG_TCPQ9091PD27C:SamSung Ntsc구형튜너.)

//			if(Divider < sntsc_VHF)				k=0xa0;
//			else if(Divider < sntsc_UHF)	k=0x90;
//			else													k=0x30;
//		break;
		
		//------------------------------------------
		// SAMSUNG_TCPQ9091PD27D Tuner Spec명기(pal/secam) 
		// Band Switching을 위한 기준 데이터.			 Fosc=Frf+Fif(38.9Mhz)	             PLL Divider변환값.
		// VHF Low: 	48.25Mhz	~	168.25Mhz  --> 87.15Mhz ~ 207.15Mhz    ---> 0x06cf ~ 0x102f (at divide 640)
		//                          spal_VHF 171.75Mhz   --> 210.65Mhz --------------> 0x1075
																					// [0x0A84(at divide 512)]
		// VHF High: 	175.25Mhz 	~ 	463.25Mhz  --> 214.15Mhz ~ 502.15Mhz    ----> 0x10bb ~ 0x273a
		//                          spal_UHF 467.25Mhz   --> 506.15Mhz --------------> 0x278a
																					// [0x1CF4(at divide 512)]
		// UHF       :  471.25Mhz 	~ 	855.25Mhz  --> 510.15Mhz ~ 894.15Mhz    ---> 0x27da ~ 0x45db
		// freq range: 0x06cf ~ 0x45db --> spec 범위를 벗어나는 세팅을 하지 마세요.
		
		case SAMSUNG_TCPQ9091PD27D:	// 튜너 구분 : (SAMSUNG_TCPQ9091PD27D:SamSung Pal-Multi 구형튜너.)		
			
		#if 0	//원래 27D(S)
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
				case BTC_SECAMDK:	//Audio선택과 관계되기 때문에 이부분에 명시하였다. -->Decoder에서는 주의 바람.
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
			{		// 프랑스 지역인 경우.
				if( Divider < 0x7b0)	{k-=0x03; k+=0x02;}
			}		
			#endif
			
		break;
		
		//------------------------------------------
//		case SAMSUNG_TCPQ9091PD28L:	// 튜너 구분 : (SAMSUNG_TCPQ9091PD28L:SamSung 신형튜너)
			
//			if(Divider < VHF1)				k=0x01;		// VHF LOW
//			else	if(Divider < UHF1)	k=0x02;		// VHF HIGH
//			else											k=0x08;		// UHF
			
//			#if 0
//			switch(ColorSystem) {			// Tuner Color System Setting.
//				case BTC_PAL:
//				case BTC_PAL_BG:
//				case BTC_PAL_I:
//				case BTC_PAL_DK:
//				case BTC_SECAMDK:	//Audio선택과 관계되기 때문에 이부분에 명시하였다. -->Decoder에서는 주의 바람.
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
//		case LGINOTEK_TAPC_H701F:	// LG Ntsc구형 튜너.
//			if(Divider < VHF)				k=0x01;		// Low Band Control value
//			else	if(Divider < UHF)	k=0x02;		// Mid Band Control value
//			else										k=0x08;		// High Band Control value

//		break;
		//------------------------------------------
	}
	
	
	if(Divider >= OLDDivider) WriteTuner(i,j,k);	// Fw >= Fc인 경우의 PLL Setting
	else WriteTun1(i,j,k);		// Fc > Fw인 경우의 PLL Setting

	// if(abs(Divider-OLDDivider) > (WORD)1000) delay5m(20);
	OLDDivider= Divider;	// Final PLL Setting Value를 저장한다.
}


// Channel Table에 정의된 PLL Divider Value를 리턴한다.
/*  memory save  2003.6.3
WORD GetPLLValue()
{	
	xdata WORD *p;

	if(CheckChCATV(xEEPROMBuffer[CurrentChannel])==0) 	// Air-TV인 경우
		p= AIR_TAB[CountryToChannel[xEEPROMBuffer[SystemCountry]]]+GetRealChannel(xEEPROMBuffer[CurrentChannel]);
	else						// Cable-TV인 경우
		p=CATV_TAB[CountryToChannel[xEEPROMBuffer[SystemCountry]]]+GetRealChannel(xEEPROMBuffer[CurrentChannel]);	
		
	return *p;

}
*/


//5mS 지연시킨다 어디에서든지 작동하며 메인루프를 지연시키는 역할을 하므로  필요한데에서만 사용한다.
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
			
		case 2://튜너를 설정한다.
//					DBGputs("TunerProcessing 2");
			if(TunerProcessTimer) break;		
						
			SetToMono();
			SoundProcessStatus=0;

			ChannelScanPointer=xEEPROMBuffer[CurrentChannel];
			ChannelAdd_Del = CheckChMask(xEEPROMBuffer[CurrentChannel]);	//ChannelAdd_Del 어디서 사용해???
							
			ViewCurrentChannel();	//  Tuner세팅하고, Channel OSD를 Display

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
		
		case 3://인근 채널을 찾는다.	
//			DBGputs("TunerProcessing 3");
//			DBGputs("xEEPROMBuffer[CurrentChannel]= 0x");DBGputss(xEEPROMBuffer[CurrentChannel]);	DBGputs("\n");
//			DBGputss(ChannelScanPointer);

			
			MspSelect();  	//sound (pal DK or I..) 자동인식위해//2004-04-09
			
			//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++	
			#ifndef	FrequncyTableType
			//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++	
			///////////////////////////////////////////////////////////////////////
			#if defined (USE_NTSCtuner)
			///////////////////////////////////////////////////////////////////////
			if(!UpDownChannel) 
			{  
				//DBGputs(" Up Scan");//up key 아님, 그냥 위쪽 채널 체크..
				if(++ChannelScanPointer >= CHANNEL_LIMIT) 	ChannelScanPointer = 0;
				
				if(ChannelScanPointer==xEEPROMBuffer[CurrentChannel])	UpDownChannel=1;
			}
			else 
			{		
				//DBGputs(" Down Scan");	//down key 아님, 그냥 아래쪽 채널 체크..
				if(--ChannelScanPointer == 0xFF) ChannelScanPointer = CHANNEL_LIMIT-1; // Next Prog number Check --> Final Prog Number Over인가를 Check
				//0에서 1감소하여 0xff가 될때...
				
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
			//2004-06-10,by thkim :	Pal Channel 은 ntsc와 다르게 변경(앞뒤채널 검색방법 변경)
			if(UpDownChannel==1&&Remote1keyFlag==0) //upKey
			{  
				if(++ChannelScanPointer >= CHANNEL_LIMIT) 	ChannelScanPointer = 0;
			}
			else if(UpDownChannel==0&&Remote1keyFlag==0)  //downKey
			{		
				if(--ChannelScanPointer == 0xFF) ChannelScanPointer = CHANNEL_LIMIT-1; // Next Prog number Check --> Final Prog Number Over인가를 Check
				//0에서 1감소하여 0xff가 될때...
				
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
			
			//리모콘에서, (채널,preCH,chAddDel)을 직접 눌렀을때...
			if(Remote1keyFlag==1 && UpDownChannel2==0)
			{	//위쪽  체크
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
			{	//아래쪽 체크
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
				//DBGputs(" Up Scan");//up key 아님, 그냥 위쪽 채널 체크..
				if(++ChannelScanPointer >= CHANNEL_LIMIT) 	ChannelScanPointer = 0;
				
				if(ChannelScanPointer==xEEPROMBuffer[CurrentChannel])	UpDownChannel=1;
			}
			else 
			{		
				//DBGputs(" Down Scan");	//down key 아님, 그냥 아래쪽 채널 체크..
				if(--ChannelScanPointer == 0xFF) ChannelScanPointer = CHANNEL_LIMIT-1; // Next Prog number Check --> Final Prog Number Over인가를 Check
				//0에서 1감소하여 0xff가 될때...
				
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

	
		case 9:		//현재 채널을 eeprom에 저장한다.
//					DBGputs("TunerProcessing 9");
//			DBGputchar('9');
			EepromSetQue(CurrentChannel_adr,xEEPROMBuffer[CurrentChannel]);
			
			SearchCNT=0;
			
			//if( AFTenable && (!CheckChFineTune(xEEPROMBuffer[CurrentChannel])) ) //auto finetune이면..
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
			
			MspSelect();  	//sound (pal DK or I..) 자동인식위해//2004-04-09
			  
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
				TunerProcessing = 19;  //제대로 찾음
			}
			#elif defined(USE_PALSECAMtuner)
			if((temp&0x47)==0x42) // center
			{	//2004-06-03
				xBYTE AddrEEp;
 				AddrEEp= EEPROM_Read(ep_ProgStart+xEEPROMBuffer[CurrentChannel]);		//ep_ProgStart	 :0x300
 				EepromSetQue(ep_ProgMemStart+(WORD)AddrEEp*PRMEMNUM+2,FineTuneValue);	//ep_ProgMemStart:0x400
				TunerProcessing = 19; //제대로 찾음				
			}
			#endif
			#else	//+++++++++++++++++++++++++++++++++++++++
			
			if((temp&0x07)==2) //	center
			{
				xdata WORD addr;
				addr=ep_ChannelStart+2*xEEPROMBuffer[CurrentChannel];	
				EepromSetQue(addr+1,FineTuneValue);		
				TunerProcessing = 19;  //제대로 찾음
			}
			#endif	//++++++++++++++++++++++++++++++++++++++			
			
			
			else //  정튜닝 아님.
			{
				if(AutoFinePointer>=TvFineTuneValue_max) //에... 정튜닝이 없네..
				{	
					#ifndef FrequncyTableType	//++++++++++++++++++++
					
					#if defined(USE_NTSCtuner)
						xdata WORD addr;

				  	if(AntenaFlag==ANTENA_CABLE) 	addr=ep_ChannelStartCatv+2*xEEPROMBuffer[CurrentChannel];  		
				  	else 							addr=ep_ChannelStartAir+2*xEEPROMBuffer[CurrentChannel];	
						EepromSetQue(addr+1,AftRangeTable[xEEPROMBuffer[SystemCountry]]);  //센터 값 넣음.
					#else
//todo			if(AntenaFlag==ANTENA_CABLE) 	addr=ep_ChannelStartCatv+2*xEEPROMBuffer[CurrentChannel];  		
//				  else 	addr=ep_ChannelStartAir+2*xEEPROMBuffer[CurrentChannel];	
//					EepromSetQue(addr+1,AftRangeTable[xEEPROMBuffer[SystemCountry]]);  //센터 값 넣음.
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
		
		case 11:			//튜너를 다시 튜닝함. //set tunner fine tune	
//					DBGputs("TunerProcessing 11");
//			DBGputchar('B');
			if(AutoFinePointer==1) 
			{	//Fo를 넣은경우 싱크가 잇는지 체크.
				TunerProcessTimer=DecoderStableTime;
				TunerProcessing = 12;
			}
			else 
			{
				FineTuneValue=TunerFineValueProcess[AutoFinePointer];				
				SetFinePLL(xEEPROMBuffer[CurrentChannel],FineTuneValue);//
				//LED_OFF;idelay5m(50);LED_ON;idelay5m(50);LED_OFF;idelay5m(50);LED_ON;//test//2004-05-07 11:24오전
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
			{		// 데코더가  sync검출한 경우. --> 플래그 enable
				FineTuneValue=TunerFineValueProcess[AutoFinePointer];				
//				SetFinePLL(xEEPROMBuffer[CurrentChannel],SetFinePLL);
				SetFinePLL(xEEPROMBuffer[CurrentChannel],FineTuneValue);//
				//LED_OFF;idelay5m(150);LED_ON;idelay5m(50);LED_OFF;//test//2004-05-07 11:24오전
				++AutoFinePointer;		
				TunerProcessTimer=10;
				TunerProcessing = 10;				
			}
			else 
			{			//sync가 없는 경우  그냥 나감.
				TunerProcessing = 19;		//aft end	
			}
			

			break;

		case 19:		//aft end
//					DBGputs("TunerProcessing 19");
			TunerProcessing=0;// 
			#ifdef	USE_remocon
			ReceiveRemoconCount=0;//hanjaeduc//2003-12-26 8:18오전
			#endif
			break;	


			
		#ifdef	USE_remocon
		case 7:
//					DBGputs("TunerProcessing 7");
		//hanjaeduc//2003-12-26 8:18오전
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

		case 20:		//자동으로 패널을 찾는다. 
//					DBGputs("TunerProcessing 20");
			//air search하기위한 초기화
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
			ProgNo=1;		//search 중이라는것을 알린다.
		#endif

//			p = AIR_TAB[CountryToChannel[xEEPROMBuffer[SystemCountry]]];
//			TDivider = *p-AftRangeTable[xEEPROMBuffer[SystemCountry]];	
//			TvPllOk(TDivider);		//tuner를 가장 낮은 주파수로 설정함.

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
			idelay5m(50);	// 검색 시간 딜레이//2003-11-17
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
					TunerProcessing=26;			//TO do  남은 영역 마무리 해야 함.			
				}					
			break;

			
		case 23:		//cable search하기위한 초기화  
//					DBGputs("TunerProcessing 23");

			#ifdef USE_UART
			DBGputs("Cable Start");
			#endif
			
			SearchChannel_Count=0;
			SearchChannel_Total=CatvLimitTable[3*CountryToChannel[xEEPROMBuffer[SystemCountry]]+1];		// max
			SearchChannel_Total=SearchChannel_Total-CatvLimitTable[3*CountryToChannel[xEEPROMBuffer[SystemCountry]]+2]+1;		// min

//			p = CATV_TAB[CountryToChannel[xEEPROMBuffer[SystemCountry]]];
//			TDivider = *p-AftRangeTable[xEEPROMBuffer[SystemCountry]];	
//			TvPllOk(TDivider);		//tuner를 가장 낮은 주파수로 설정함.

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
			idelay5m(50);	// 검색 시간 딜레이
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
	
		case 26: 	// 남은 영역 마무리 해야 함.
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
				
		case 29:		//autosearch 완료 . 
//					DBGputs("TunerProcessing 29");
			ProgNo=0;
			KEY_value=MenuKey;	//상위 메뉴로 복귀 
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
		p = CATV_TAB[CountryToChannel[xEEPROMBuffer[SystemCountry]]] + (WORD)SearchChannel_Count;	// Freq. Table로 부터 그값(PLL Divider Value)을  찾아서,
		Mask=0x83;
  	}
  	else 
  	{
		addr=ep_ChannelStartAir+2*SearchChannel_Count;
		p = AIR_TAB[CountryToChannel[xEEPROMBuffer[SystemCountry]]] + (WORD)SearchChannel_Count;	// Freq. Table로 부터 그값(PLL Divider Value)을  찾아서,
		Mask=0x81;
  	}
  	
		//---삼성 ntsc튜너의 경우 스펙을 벗어나는 데이터필터링--------
	if(CURRENT_TUNNER != SAMSUNG_TCPN9082DA27C);
	else{	// 삼성튜너가 연결되어 있는 경우에, Low band 55.25Mhz미만의 주파수는 필터링한다.(튜너 스펙을 오버하는 주파수이다.)
		if(*p < 0x07E4){ 
			EepromSetQue(addr,Mask);		// TV Flag설정.(Catv)  --> No Using
			EepromSetQue(addr+1,AftRangeTable[xEEPROMBuffer[SystemCountry]]);	// TV Fine Tune data초기화..(Catv)
			return 0;				// Dummy인 경우라면 Skip한다.
		}
	}
		//----더미 데이터 필터링.--------------------------------------------
	if(*p == 0){ 		// PLL Divider Value가 Dummy Data인지 체크한다. 		// 1월 16일 Dummy Check하도록 추가함.
		EepromSetQue(addr,Mask);		// TV Flag설정.(Air-TV)  --> No Using
		EepromSetQue(addr+1,AftRangeTable[xEEPROMBuffer[SystemCountry]]);	// TV Fine Tune data초기화..(Air-TV)
		return 0;				// Dummy인 경우라면 Skip한다.
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
//		p = CATV_TAB[CountryToChannel[xEEPROMBuffer[SystemCountry]]] + (WORD)SearchChannel_Count;	// Freq. Table로 부터 그값(PLL Divider Value)을  찾아서,
  		}
  	else {
		addr=ep_ChannelStartAir+2*SearchChannel_Count;
//		p = AIR_TAB[CountryToChannel[xEEPROMBuffer[SystemCountry]]] + (WORD)SearchChannel_Count;	// Freq. Table로 부터 그값(PLL Divider Value)을  찾아서,
  		}

	CheckTVSignal(5);

	if(eTVSyncFlag) // 데코더가  sync검출한 경우. --> 플래그 enable
	{
		if(AntenaFlag==ANTENA_CABLE)  EepromSetQue(addr,EnableCATV);		// enable/cable
		else 						  EepromSetQue(addr,EnableAIR);			// enable/air
		EepromSetQue(addr+1,AftRangeTable[xEEPROMBuffer[SystemCountry]]);	// default Fine Tune Data
	}
	else	 		// 데코더가  sync검출하지 못한 경우. --> 플래그 disable
	{
		//if (ExitCondionCheck(temp_cable)) return;	// 종료조건 체크 
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
		p = CATV_TAB[CountryToChannel[xEEPROMBuffer[SystemCountry]]] + (WORD)SearchChannel_Count;	// Freq. Table로 부터 그값(PLL Divider Value)을  찾아서,
  		}
  	else {
		p = AIR_TAB[CountryToChannel[xEEPROMBuffer[SystemCountry]]] + (WORD)SearchChannel_Count;	// Freq. Table로 부터 그값(PLL Divider Value)을  찾아서,
  		}
  	*/	
  	p = AIR_TAB[CountryToChannel[xEEPROMBuffer[SystemCountry]]] + (WORD)SearchChannel_Count;	// Freq. Table로 부터 그값(PLL Divider Value)을  찾아서,

  	
	//---삼성 ntsc튜너의 경우 스펙을 벗어나는 데이터필터링--------
	// 삼성튜너가 연결되어 있는 경우에, Low band 55.25Mhz미만의 주파수는 필터링한다.(튜너 스펙을 오버하는 주파수이다.)
	if(CURRENT_TUNNER == SAMSUNG_TCPN9082DA27C)
		if(*p < 0x07E4)	return 0;
	else if(CURRENT_TUNNER ==SAMSUNG_TCPQ9091PD27D)	
		if(*p < 0x00580)	return 0;		//Low band 49.75Mhz미만//2004-05-04

	//----더미 데이터 필터링.--------------------------------------------	
	if(*p == 0)		// PLL Divider Value가 Dummy Data인지 체크한다. 		// 1월 16일 Dummy Check하도록 추가함.
		return 0;	// Dummy인 경우라면 Skip한다.
	else 
		TDivider = *p;		// PLL Divider Value를 Divider에 로드.
	
	TvPllOk(TDivider);
	return 1;
}

void SearchSave()
{
	xdata WORD 	addr;
	
	addr=ep_ProgMemStart+PRMEMNUM*ProgNo;
	
	CheckTVSignal(5);

	if(eTVSyncFlag) 
	{		// 데코더가  sync검출한 경우. --> 플래그 enable
		if(AntenaFlag==ANTENA_CABLE)  EepromSetQue(addr,EnableCATV);	// enable/cable
		else 						  EepromSetQue(addr,EnableAIR);		// enable/air
		EepromSetQue(addr+1,SearchChannel_Count);	// Air-TV영역에 channel table offset저장.
		EepromSetQue(addr+2,AftRangeTable[xEEPROMBuffer[SystemCountry]]);	// Fine tuning Data 초기화
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
		EepromSetQue(addr+1,SearchChannel_Count);	// Air-TV영역에 channel table offset저장.
		EepromSetQue(addr+2,AftRangeTable[xEEPROMBuffer[SystemCountry]]);	// Fine tuning Data 초기화
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
		p = CATV_TAB[CountryToChannel[xEEPROMBuffer[SystemCountry]]] + (WORD)SearchChannel_Count;	// Freq. Table로 부터 그값(PLL Divider Value)을  찾아서,
		Mask=0x83;
  	
		//---삼성 ntsc튜너의 경우 스펙을 벗어나는 데이터필터링--------
	if(CURRENT_TUNNER != SAMSUNG_TCPN9082DA27C);
	else{	// 삼성튜너가 연결되어 있는 경우에, Low band 55.25Mhz미만의 주파수는 필터링한다.(튜너 스펙을 오버하는 주파수이다.)
		if(*p < 0x07E4){ 
			EepromSetQue(addr,Mask);		// TV Flag설정.(Catv)  --> No Using
			EepromSetQue(addr+1,AftRangeTable[xEEPROMBuffer[SystemCountry]]);	// TV Fine Tune data초기화..(Catv)
			return 0;				// Dummy인 경우라면 Skip한다.
		}
	}
		//----더미 데이터 필터링.--------------------------------------------
	if(*p == 0){ 		// PLL Divider Value가 Dummy Data인지 체크한다. 		// 1월 16일 Dummy Check하도록 추가함.
		EepromSetQue(addr,Mask);		// TV Flag설정.(Air-TV)  --> No Using
		EepromSetQue(addr+1,AftRangeTable[xEEPROMBuffer[SystemCountry]]);	// TV Fine Tune data초기화..(Air-TV)
		return 0;				// Dummy인 경우라면 Skip한다.
	}else TDivider = *p;			// Center Frequency

	TvPllOk(TDivider);
	return 1;
}

void SearchSave()
{
	xdata WORD 	addr;
  	
		addr=ep_ChannelStart+2*SearchChannel_Count;

	CheckTVSignal(5);

	if(eTVSyncFlag) // 데코더가  sync검출한 경우. --> 플래그 enable
	{
		EepromSetQue(addr,EnableCATV);		// enable/cable
		EepromSetQue(addr+1,AftRangeTable[xEEPROMBuffer[SystemCountry]]);	// default Fine Tune Data
	}
	else	 		// 데코더가  sync검출하지 못한 경우. --> 플래그 disable
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

// Min에서 Max Channel까지 순서대로 Scan하면서, Sync가 Detect되는지를 판단하고, 
// Sync상태에 따라서eeprom상의 Program Edit영역에 sync가 검출되는 채널로 테이블을 Update시킨다.
// --> Fine Tune data는 50으로 초기화 된다.
// scan완료후에는 원래의 Channel로 되돌린다.
// 1월16일 : Dummy Channel일 경우, Scan을  Skip하도록 수정핰.--> PAL Channel의 경우에 Dummy Channel이 존재함.
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

//---------------AutoSearch를 수행하기 전의 PLL Data를 저장한다.---------------------
	i = Read24c16(ep_Currentchennel);		// Current Prog Number Read	
	if(CheckChCATV(i)==0) 	// Air-TV인 경우	// Prog No에 대한 실제 channel table offset을 계산 한다.
			p= AIR_TAB[CountryToChanel[SystemCountry]]+GetRealChannel(i);
	else						// Cable-TV인 경우
			p=CATV_TAB[CountryToChanel[SystemCountry]]+GetRealChannel(i);	
	temp_pll = *p;		// Tuner PLL Divider Value	
//-----------------------------------------------------------


//------------------Air-TV Channel Table Scanning---------------------
	ProgNo=0;	// Program Number초기화.
	PutString(7,2,"PR  0~");

	for(i=0; i < (TV_Max-TV_Min+1); i++){		// /1월16일
		KeyScan();
		if(KeyCode==MK_MENU) return;	
		// Min에서 Max Channel까지 순서대로 Scan하면서, Sync가 Detect되는지를 판단하고, 
		// Sync상태에 따라서eeprom상의 Program Edit영역을 Update한다. 
		//ShowOSDChannel(0,i);		// OSD Channel Display(Air-TV Channel Display)	
		
		// Channel Table을 위한 Offset계산
		//p = AIR_TAB[Addr] + (i - TV_Min);	// Freq. Table로 부터 그값(PLL Divider Value)을  찾아서,
		p = AIR_TAB[CountryToChanel[SystemCountry]] + (UINT)i;	// Freq. Table로 부터 그값(PLL Divider Value)을  찾아서,
		// Divider = *p;				// PLL Divider Value를 Divider에 로드.	
		
		if(*p == 0) 		// PLL Divider Value가 Dummy Data인지 체크한다. 		// 1월 16일 Dummy Check하도록 추가함.
			continue;	// Dummy인 경우라면 Skip한다.
		else 
			Divider = *p;		// PLL Divider Value를 Divider에 로드.

//		ShowOSDChannel(0,i);		// OSD Channel Display(Air-TV Channel Display)	

		//----------최초 Channel Setting후에 AFT수행여부를 체크한다.---------
		Timer8 = AUTO_SEARCH_TIME;	// Auto Search 구간 탐색 시간 설정. = 0.5초	
		AFTValue=80;	SearchOK=0x00;
		SetTuner(Divider+(unsigned int)AFTValue-(unsigned int)80);
		value = SyncRead();	// Sync Status를 판단하기 위해서, VPX_ASR 리드한다.	
		if((value & 0x07) != 0x03){	//no sync인 경우 
       		AFTValue=50;		// aft를 수행하기 위해서 값을 초기화 한다.
			SearchOK=0x00;	// aft flag를 설정.
		}
		else{SearchOK=0x01;}	// sync OK 인 경우  
				
		//---------------------------------------------------------------
		
		if(SearchOK==0x00){	// Center Freq가 no sync인 경우 -->Sync Search
				while(SearchOK==0x00){
					SetTuner(Divider+(unsigned int)AFTValue-(unsigned int)80);
					value = SyncRead();	// Sync Status를 판단하기 위해서, VPX_ASR 리드한다.	
					if((value & 0x07) != 0x03){	//no sync인 경우 
						AFTValue+=10;
					}	
					else	{SearchOK=0x01;}
					
					if(AFTValue>150) break;	// while loop탈출 조건.			
				}

				if(SearchOK==0x01){	
					SearchOK=0x00;
//					if(PrintFlag)printf("N");		// Decoder Sync을 판단하기 위해서 사용 ---> test
					Write24c16(ep_ChannelStart+ProgNo*4,0x00);	// TV Flag설정.(Air-TV)
					Write24c16(ep_ChannelStart+ProgNo*4+1,i);	// Air-TV영역에 channel table offset저장.
					Write24c16(ep_ChannelStart+ProgNo*4+2,50);	// Fine tuning Data 초기화
					ProgNo++;	
					DisplayChannelValue(9,2,ProgNo);
				}

		}
		else{	//sync ok --> Data Save및 Finetune data초기화.
//			if(PrintFlag)printf("S");		// Decoder Sync을 판단하기 위해서 사용 ---> test
			Write24c16(ep_ChannelStart+ProgNo*4,0x00);	// TV Flag설정.(Air-TV)
			Write24c16(ep_ChannelStart+ProgNo*4+1,i);	// Air-TV영역에 channel table offset저장.
			Write24c16(ep_ChannelStart+ProgNo*4+2,50);	// Fine tuning Data 초기화
			ProgNo++;	
			DisplayChannelValue(9,2,ProgNo);
		}
		//---------------------------------------------------------------
		
		Write24c16(ep_ProgNumber,ProgNo-1);	// Program된 수자를 eeprom에 저장.
		if(ProgNo >= CHANNELMEMORYMAX) break;
		RegBuffer[CHANNEL]=PWMMin+i;
		DisplayPWMScale(WIN3_L+1,WIN3_B-1,20);
		
		while(Timer8 != 0){  WatchDogClear();}	// 0.5초가 지날때 까지 기다린다.  	
		
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
		// Min에서 Max Channel까지 순서대로 Scan하면서, Sync가 Detect되는지를 판단하고, 
		// Sync상태에 따라서eeprom상의 Program Edit영역을 Update한다. 
		
		// ShowOSDChannel(1,i);		// OSD Channel Display(Cable-TV Channel Display)		
		
		// Channel Table을 위한 Offset계산
		//p = CATV_TAB[CountryToChanel[SystemCountry]] + (i - CATV_Min);	// Freq. Table로 부터 그값(PLL Divider Value)을  찾아서,
		p = CATV_TAB[CountryToChanel[SystemCountry]] + (UINT)i;	// Freq. Table로 부터 그값(PLL Divider Value)을  찾아서,
		//Divider = *p;				// PLL Divider Value를 Divider에 로드.	
		if(*p == 0) 		// PLL Divider Value가 Dummy Data인지 체크한다. 		// 1월 16일 Dummy Check하도록 추가함.
			continue;	// Dummy인 경우라면 Skip한다.
		else 
			Divider = *p;		// PLL Divider Value를 Divider에 로드.
			
//		ShowOSDChannel(1,i);		// OSD Channel Display(Cable-TV Channel Display)			

		//----------최초 Channel Setting후에 AFT수행여부를 체크한다.---------
		Timer8 = AUTO_SEARCH_TIME;	// Auto Search 구간 탐색 시간 설정. = 0.5초	
		AFTValue=80;	SearchOK=0x00;
		SetTuner(Divider+(unsigned int)AFTValue-(unsigned int)80);
		value = SyncRead();	// Sync Status를 판단하기 위해서, VPX_ASR 리드한다.	
		if((value & 0x07) != 0x03){	//no sync인 경우 
       		AFTValue=50;		// aft를 수행하기 위해서 값을 초기화 한다.
			SearchOK=0x00;	// aft flag를 설정.
		}
		else{SearchOK=0x01;}	// sync OK 인 경우  				
		//---------------------------------------------------------------

		if(SearchOK==0x00){	// Center Freq가 no sync인 경우 -->Sync Search
				while(SearchOK==0x00){
					SetTuner(Divider+(unsigned int)AFTValue-(unsigned int)80);
					value = SyncRead();	// Sync Status를 판단하기 위해서, VPX_ASR 리드한다.	
					if((value & 0x07) != 0x03){	//no sync인 경우 --> 500Khz Step
						AFTValue+=10;
					}
					else	{SearchOK=0x01;}
					
					if(AFTValue>150) break;	// while loop탈출 조건.			
				}

				if(SearchOK==0x01){	
					SearchOK=0x00;
					if(PrintFlag)printf("N");		// Decoder Sync을 판단하기 위해서 사용 ---> test
					Write24c16(ep_ChannelStart+ProgNo*4,0x02);	// TV Flag설정.(CATV-TV)
					Write24c16(ep_ChannelStart+ProgNo*4+1,i);	// Air-TV영역에 channel table offset저장.
					Write24c16(ep_ChannelStart+ProgNo*4+2,50);	// Fine tuning Data 초기화
					ProgNo++;
					DisplayChannelValue(9,2,ProgNo);

				}

		}		
		else{	//sync ok --> Data Save및 Finetune data초기화.
			if(PrintFlag)printf("S");		// Decoder Sync을 판단하기 위해서 사용 ---> test
			Write24c16(ep_ChannelStart+ProgNo*4,0x02);	// TV Flag설정.(CATV-TV)
			Write24c16(ep_ChannelStart+ProgNo*4+1,i);	// Air-TV영역에 channel table offset저장.
			Write24c16(ep_ChannelStart+ProgNo*4+2,50);	// Fine tuning Data 초기화
			ProgNo++;
			DisplayChannelValue(9,2,ProgNo);

		}
		//---------------------------------------------------------------
		
		Write24c16(ep_ProgNumber,ProgNo-1);	// Program된 channel 수자를 eeprom에 저장. -->
											// 몇개의 channel이 sync detect되었는지를 확인하기 위해서 사용.
		if(ProgNo >= CHANNELMEMORYMAX) break;
		RegBuffer[CHANNEL]=PWMMin+i;
		DisplayPWMScale(WIN3_L+1,WIN3_B-1,20);
		
		while(Timer8 != 0){  WatchDogClear();}	// 0.5초가 지날때 까지 기다린다.  	
		
	}	
//-----------------scan 되어진 Channel 이외의 Program Edit영역에 대해서 disable상태로 만든다.----------
	if(ProgNo < CHANNELMEMORYMAX){ 	// 1월15일
		for(i=ProgNo;i<CHANNELMEMORYMAX;i++) {	// 전체 Channel Edit영역(100 * 4bytes)에 대하여 아래와 같은 초기화를 수행한다.
			// TV Flag초기화및 저장.(0번째 byte)	
			Write24c16(ep_ChannelStart+i*4  ,0x01);	// mask flag set
			WatchDogClear();
			// Fine tuning Data 초기화및 저장.(2번째 byte)
			// Write24c16(ep_ChannelStart+i*4+2,50);		// 초기값 = 50  ---> 50*50Khz=2.5Mhz  <-- 주의할 것
		}
	}
//----------------------------------------------------------

//--------------Audio Mute Off------
	//PutVolume(TRUE);
	SoftVolume(TRUE);		// 1월 17일 LKE
//--------------------------------

// ------------스캔 완료후에 원래의 Channel로 되돌린다.---------------------
//	LCDMute(0,1);	// Mute On		// --> 1월16일 막음.
//	SetTuner(temp_pll);		// --> 1월16일 막음.
//	LCDMuteOff();	// Mute Off		// --> 1월16일 막음.
//-------------Program Number를 0으로 초기화 한다. ----------------------
	RegBuffer[CHANNEL]=0;
	Write24c16(ep_Currentchennel,RegBuffer[CHANNEL]);
//	ViewCurrentChannel();
//--------------------------------


	}
}
*/
// by LKE 2/15
// 16byte data를 한번에 Write를 행한다.
// 주의할점은 00,10,20,30...등과 같은 값이 EEProm Start Address의 값으로 적용되어야 한다.
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




// EEProm의 System County내용에 맞게끔 EEPROM Program Memory영역을 초기화 시키는 함수이다. 
// by LKE 2/15 EEPROM Write속도를 올리기 위해서 page write개념을 도입함.
// Pal-Multi/NTSC에 공통으로 적용하기 위해서 수정함. by LKE 2.18
// Tuner PLL Data가 dummy인 경우이거나 채널 범위를 벗어나는 경우에는  --> No Using flag를 세트함.
// by LKE 2/22 --> 함수추가 EepTvFillValue()
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
		//--------------Air EEprom 초기화.--------------		
		j=0;	
		addr=ep_ChannelStartAir;

		CHANNEL_LIMIT=TvLimitTable[3*CountryToChannel[xEEPROMBuffer[SystemCountry]]+0];

		for(i=0; i < CHANNEL_LIMIT; i++)
		{		// 1월16일
			
			p = AIR_TAB[CountryToChannel[xEEPROMBuffer[SystemCountry]]] + (WORD)i;		
			if(*p == 0) OSDStringBuff[j++]=0x81; 	// PLL Divider Value가 Dummy Data인지 체크한다. 		// 1월 16일 Dummy Check하도록 추가함.
			else OSDStringBuff[j++]=0x00; 			// Dummy인 경우라면  NoUsing Flag를 set한다.
			OSDStringBuff[j++]=AftRangeTable[xEEPROMBuffer[SystemCountry]];		//  Air/Enable Data,   FineTune Data를 set한다.

			if(j==16)
			{	// 16byte가 버퍼에 채워지면 write..
				j=0; 
				Write24c16Page(addr, OSDStringBuff);
				addr=addr+16;
			}
		}
		for(; i < 128; i++)
		{	// Tv Data 이외의 영역에 대한 초기화 
			OSDStringBuff[j++]=0x81; 
			OSDStringBuff[j++]=AftRangeTable[xEEPROMBuffer[SystemCountry]];		//  NoUsing/Air/Disable Data, FineTune Data
		
			if(j==16)
			{	// 16byte가 버퍼에 채워지면 write..
				j=0; 
				Write24c16Page( addr, OSDStringBuff);
				addr=addr+16;
			}
		}
		//---------------Catv EEprom 초기화.-------------	
		
		j=0;
		addr=ep_ChannelStartCatv;		


		CHANNEL_LIMIT=CatvLimitTable[3*CountryToChannel[xEEPROMBuffer[SystemCountry]]+0];
		
		for(i=0; i < CHANNEL_LIMIT; i++)
		{
			p = CATV_TAB[CountryToChannel[xEEPROMBuffer[SystemCountry]]] + (WORD)i;		
			if(*p == 0) OSDStringBuff[j++]=0x83; 	// PLL Divider Value가 Dummy Data인지 체크한다. 		// 1월 16일 Dummy Check하도록 추가함.
			else OSDStringBuff[j++]=0x02; 			// Dummy인 경우라면  NoUsing Flag를 set한다.
			OSDStringBuff[j++]=AftRangeTable[xEEPROMBuffer[SystemCountry]];		//  Catv/Enable Data,   FineTune Data
			if(j==16)
			{	// 16byte가 버퍼에 채워지면 write..
				j=0; 
				Write24c16Page(addr, OSDStringBuff);
				addr=addr+16;
			}
		}
		for(; i < 128; i++)
		{	// Tv Data 이외의 영역에 대한 초기화 
			OSDStringBuff[j++]=0x83; OSDStringBuff[j++]=AftRangeTable[xEEPROMBuffer[SystemCountry]];		//  Nousing/Catv/Disable Data, FineTune Data
			if(j==16){	// 16byte가 버퍼에 채워지면 write..
				j=0; 
				Write24c16Page(addr, OSDStringBuff);
				addr=addr+16;
				}
		}
		//-------------------------------------------------------------------------
	#elif (NTSC_COUNTRY==0)&&!defined(FrequncyTableType)
		//---------------PAL Program Edit EEprom 초기화.-------------
		//	처음부터 air로 전부 채우고 그다음은 catv로   채운다 

		//----프로그램 마스크 표 초기화 

		j=0;	
		addr=ep_ProgStart;

		for(i=0; i < 128; i++)
		{		// 1월16일
			OSDStringBuff[j++]=i;		
			
			if(j==16)
			{	// 16byte가 버퍼에 채워지면 write..
				j=0; 
				Write24c16Page(addr, OSDStringBuff);
				addr=addr+16;
			}
		}

		//--------------Air EEprom 초기화.--------------		
		j=0;	
		addr=ep_ProgMemStart;
		
		CHANNEL_LIMIT=TvLimitTable[3*CountryToChannel[xEEPROMBuffer[SystemCountry]]+0];
		
		for(i=0; i < CHANNEL_LIMIT; i++)
		{		// 1월16일
			p = AIR_TAB[CountryToChannel[xEEPROMBuffer[SystemCountry]]] + (WORD)i;		
			if(*p == 0) OSDStringBuff[j++]=0x81; 	// PLL Divider Value가 Dummy Data인지 체크한다. 		// 1월 16일 Dummy Check하도록 추가함.
			else OSDStringBuff[j++]=0x00; 			// Dummy인 경우라면  NoUsing Flag를 set한다.
			OSDStringBuff[j++]=i;			//real channel 
			OSDStringBuff[j++]=AftRangeTable[xEEPROMBuffer[SystemCountry]];		//  Air/Enable Data,   FineTune Data를 set한다.
			OSDStringBuff[j++]=0x00;		//reserved.
			
			OSDStringBuff[j++]=0x00;		///4byte 글자 들어갈 자리 
			OSDStringBuff[j++]=0x00;		//
			OSDStringBuff[j++]=0x00;		//
			OSDStringBuff[j++]=0x00;		//reserved.
			
			if(j==16)
			{	// 16byte가 버퍼에 채워지면 write..
				j=0; 
				Write24c16Page(addr, OSDStringBuff);
				addr=addr+16;
			}
		}

		//---------------Catv EEprom 초기화.-------------	

		//j=0;			
		Channel_Count=Channel_Total=CHANNEL_LIMIT;		
		CHANNEL_LIMIT=CatvLimitTable[3*CountryToChannel[xEEPROMBuffer[SystemCountry]]+0];
		Channel_Total+=CHANNEL_LIMIT;
		
		for(i=0; i < CHANNEL_LIMIT; i++)
		{
			Channel_Count++;
			p = CATV_TAB[CountryToChannel[xEEPROMBuffer[SystemCountry]]] + (WORD)i;		
			if(*p == 0) OSDStringBuff[j++]=0x83; 	// PLL Divider Value가 Dummy Data인지 체크한다. 		// 1월 16일 Dummy Check하도록 추가함.
			else OSDStringBuff[j++]=0x02; 			// Dummy인 경우라면  NoUsing Flag를 set한다.
			OSDStringBuff[j++]=i;		//real channel 			
			OSDStringBuff[j++]=AftRangeTable[xEEPROMBuffer[SystemCountry]];		//  Catv/Enable Data,   FineTune Data
			OSDStringBuff[j++]=0x00;		//reserved.

			OSDStringBuff[j++]=0x00;		///4byte 글자 들어갈 자리 
			OSDStringBuff[j++]=0x00;		//
			OSDStringBuff[j++]=0x00;		//
			OSDStringBuff[j++]=0x00;		//
			
			if(j==16)
			{	// 16byte가 버퍼에 채워지면 write..
				j=0; 
				Write24c16Page(addr, OSDStringBuff);
				addr=addr+16;
			}
			
			if(Channel_Count>=Channel_Total) break;	
			if(Channel_Count>CHANNELMEMORYMAX) break;
		}
		
		if(j!=0) 		//마지막 조금 남은 것  기록 
			while(j>=16) 
			{
				OSDStringBuff[j++]=0x83; 	// PLL Divider Value가 Dummy Data인지 체크한다. 		// 1월 16일 Dummy Check하도록 추가함.
				OSDStringBuff[j++]=0x00;		//real channel 				
				OSDStringBuff[j++]=AftRangeTable[xEEPROMBuffer[SystemCountry]];		//  Catv/Enable Data,   FineTune Data
				OSDStringBuff[j++]=0x00;		//reserved.

				OSDStringBuff[j++]=0x00;		///4byte 글자 들어갈 자리 
				OSDStringBuff[j++]=0x00;		//
				OSDStringBuff[j++]=0x00;		//
				OSDStringBuff[j++]=0x00;		//
				Write24c16Page(addr, OSDStringBuff);
			}
	#elif (NTSC_COUNTRY==0)&&defined(FrequncyTableType)

		//--------------EEprom 초기화.--------------		
		j=0;	
		addr=ep_ChannelStart;

		CHANNEL_LIMIT=TvLimitTable[3*CountryToChannel[xEEPROMBuffer[SystemCountry]]+0];

		for(i=0; i < CHANNEL_LIMIT; i++)
		{		// 1월16일
			
			p = CATV_TAB[CountryToChannel[xEEPROMBuffer[SystemCountry]]] + (WORD)i;		
			if(*p == 0) OSDStringBuff[j++]=0x83; 	// PLL Divider Value가 Dummy Data인지 체크한다. 		// 1월 16일 Dummy Check하도록 추가함.
			else OSDStringBuff[j++]=0x02; 			// Dummy인 경우라면  NoUsing Flag를 set한다.
			OSDStringBuff[j++]=AftRangeTable[xEEPROMBuffer[SystemCountry]];		//  Air/Enable Data,   FineTune Data를 set한다.

			if(j==16)
			{	// 16byte가 버퍼에 채워지면 write..
				j=0; 
				Write24c16Page(addr, OSDStringBuff);
				addr=addr+16;
			}
		}
		for(; i < 128; i++)
		{	// Tv Data 이외의 영역에 대한 초기화 
			OSDStringBuff[j++]=0x83; 
			OSDStringBuff[j++]=AftRangeTable[xEEPROMBuffer[SystemCountry]];		//  NoUsing/Air/Disable Data, FineTune Data
		
			if(j==16)
			{	// 16byte가 버퍼에 채워지면 write..
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