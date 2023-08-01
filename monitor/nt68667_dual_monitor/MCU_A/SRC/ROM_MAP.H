#ifndef _ROM_MAP_H_
#define  _ROM_MAP_H_

// 0x000 ... 0x07f ==>mode independent settings
// 0x080 ... 0x0cf ==>h_sync,hv_pol,v_sync (5 * 16 = 80 total 16 new mode)   !!!???
// 0x0d0 ... 0x0ef ==>VTotal (2 * 16 = 32 total 16 new mode)
// 0x0f0 ... 0x0ff ==>
// 0x100 ... 0x41f ==>lcd timing (8 x 100 = 800 total 100 mode)
// 0x420 ... 0x46f ==>
// 0x470 ... 0x4cf ==>ture color
// 0x4d0 ... 0x597 ==>HTotal for 50% (2 x 100 = 200 total 100 mode)
// 0x598 ... 0x5ff ==>
// 0x600 ... 0x720 ==>HDCP key
// 0x721 ... 0x7fd ==>
// 0x7fe ... 0x7ff ==>ture color CK



#define NVRAM_SYNC(m)			(unsigned short)(0x80 + (m)*5)	//16 timeing: 0x80...0xcf
	#define NVRAM_HS(m)			(NVRAM_SYNC(m) + 0)
	#define NVRAM_VS(m)			(NVRAM_SYNC(m) + 2)
	#define NVRAM_POL(m)        (NVRAM_SYNC(m) + 4)

#define NVRAM_VTOTAL(m)			(0x0d0 + (m)*2)	//16 timeing: 0xd0...0xef

#define NVRAM_TIMING(m)			(0x100 + (m)*8)	//100 timeing: 0x100...0x41f
	#define NVRAM_HPSTART(m)	(NVRAM_TIMING(m) + 0)
	#define NVRAM_RESOLU(m)   	(NVRAM_TIMING(m) + 2)
	#define NVRAM_PHASE(m)     	(NVRAM_TIMING(m) + 3)
	#define NVRAM_HTOTAL(m)		(NVRAM_TIMING(m) + 4)
	#define NVRAM_VPSTART(m) 	(NVRAM_TIMING(m) + 6)


#define NVRAM_TRUECOLOR			0x470	//0x60 byte: 0x470...0x4cf
#define NVRAM_TRUECOLOR_CK		0x7fe

#define NVRAM_HTOTAL50(m)		(0x4d0 + (m)*2)	//100 timing: 0x4d0...0x597
#define NVRAM_HDCP_KEY			0x600
#define NVRAM_HDCP_KEY_CRC		0x730	//FOR TPV


//#define NVRAM_TIMING_ALTER(m) (0x7A4+m)
//#define NVRAM_HP50(m)			(0x560 + m*2)	//70
//#define NVRAM_AUTOADJ(m)		(0x5b0 + (m/8))
//	#define NVRAM_AUTOADJ_S		0x5b0
//	#define NVRAM_AUTOADJ_E		0x5be
//#define NVRAM_SCALER			0x5fe
#ifndef Use24C02
#define NVRAM_ANA_DDC			0x700
#define NVRAM_DIG_DDC			0x780
#define DDC_ADDR_ANALOG NVRAM_ANA_DDC
#define DDC_ADDR_DIGITAL NVRAM_DIG_DDC
#endif


typedef struct {
	unsigned short usHStart;       //HStart
	unsigned short usHTotal;       //HTotal,
	unsigned short usVStart;       //VStart,
	unsigned short usHFreq;        //HFreq,
 	unsigned short usVFreq;        //VFreq,
 	unsigned short usVTotal;       //VTotal,
 	unsigned char ucSyncPolarity; //SyncPolarity,
	unsigned char ucResolution;   //Resolution
	unsigned char ucRange;
} _Monitor_Timing_ ;

extern code _Monitor_Timing_ EEPROM_TimingTable[];

#define HnVn 0
#define HnVp 1
#define HpVn 2
#define HpVp 3

enum _RESOLUTION_TABLE_ {
R640x350= 0,
R720x400,
R640x480,
R800x600,
R832x624,
R1024x768,
R1152x864,
R1152x870,
R1152x900,
R1280x960,

R1280x1024,
R688x556,
R1280x720,
R1600x1200,
R1280x768,
R848X480,
R720x576,
R1088x612,
R1280x800,
R640x400,

R1360x768,//20
R1400x1050,
R1440x900,
R1680x1050,
R1792x1344,
R1856x1392,
R1920x1080,
R1920x1200,
R1920x1440,
R1280x1026,

R960x720,
R1600x1000,
R720x350,
TOTAL_RESOLUTION
};


#define BEST_RESOLUTION	R1280x1024//R1680x1050//R1280x1024

#define M720x576_60		35
#define M1024x768_76	16
#define M1440x900_60R	45
#define M1440x900_60	46
#define M1280x1024_60	26
#define M1680x1050_60	48


extern code unsigned char _Default_Analog_EDID[128];
extern code unsigned char _Default_Digital_EDID[128];
extern code unsigned char _Default_TrueColor_Value[96];
//extern code unsigned char _SerialNum[15];//NEO 060607

extern code unsigned char MCU_DataMap[];
//extern code unsigned char DDC_Tab[];

#endif
