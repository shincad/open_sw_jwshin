#ifndef _OSD_H
#define _OSD_H

//define by Alvin
#define OSD_WIDTH 			31
#define OSD_HIGH 			15
#define ONE_BIT_START_ADDR 	468	// ONE_BIT_START_ADDR % 9 == 0
//#define TWO_BIT_START_ADDR 3159// (TWO_BIT_START_ADDR - ONE_BIT_START_ADDR) %9 == 0
#define TWO_BIT_START_ADDR 3159+18// (TWO_BIT_START_ADDR - ONE_BIT_START_ADDR) %9 == 0
//#define FOUR_BIT_START_ADDR 3690// (FOUR_BIT_START_ADDR - TWO_BIT_START_ADDR) %9 == 0
#define FOUR_BIT_START_ADDR 3855+45// (FOUR_BIT_START_ADDR - TWO_BIT_START_ADDR) %9 == 0
#define OFFSET_2BIT 		16
#define OFFSET_4BIT 		100
#define LANG_OFFSET			124
#define MAX_PAGE			7 //16
#define MAX_DSUB_ITEM		6 //16
#define MAX_DVI_ITEM		6 //10
#define MAX_VIDEO_ITEM		6
#define MAX_L2_ITEM			3
#define MAX_FACT_ITEM		26
#define OSD_FACT_HPOS		PanelWidth - OSD_WIDTH*12-2 //918
#define OSD_FACT_VPOS		2
#define OSD_IN_MAIN_MENU	1
#define OSD_IN_FACT_MENU	2
#define OSD_IN_ERROR_MENU	3
#define OSD_IN_OUT_MENU		4
#define OSD_IN_AUTO_MENU	5
#define OSD_IN_IMSG_MENU	6
//
#define ROW0				0
#define ROW1				OSD_WIDTH
#define ROW2				OSD_WIDTH*2
#define ROW3				OSD_WIDTH*3
#define ROW4				OSD_WIDTH*4
#define ROW5				OSD_WIDTH*5
#define ROW6				OSD_WIDTH*6
#define ROW7				OSD_WIDTH*7
#define ROW8				OSD_WIDTH*8
#define ROW9				OSD_WIDTH*9
#define ROW10				OSD_WIDTH*10
#define ROW11				OSD_WIDTH*11
#define ROW12				OSD_WIDTH*12
#define ROW13				OSD_WIDTH*13
#define ROW14				OSD_WIDTH*14
#define ROW15				OSD_WIDTH*15
#define ROW16				OSD_WIDTH*16
#define ROW17				OSD_WIDTH*17
#define ROW18				OSD_WIDTH*18
#define BAR_SEGMENT			5
#define BAR_LENGTH			7
#define CBAR_SEGMENT		5
#define CBAR_LENGTH			10
#define REG_PAGE1 			0x00
#define REG_PAGE2 			0x01
#define REG_PAGE3 			0x10
#define enOSD				0x01
#define enWIN1				0x02
#define enWIN2				0x04
#define enWIN3				0x08
#define enWIN4				0x10
//0xff Write Type flag
#define tyRED_GAMMA 		0x00
#define tyGREEN_GAMMA 		0x10
#define tyBLUE_GAMMA		0x20
#define tyRGB_GAMMA			0x30
#define tySRAM_CODE_ONLY	0x40
#define tySRAM_ATT_MSB		0x50
#define tySRAM_ATT_LSB		0x60
#define tySRAM_ATT_RW		0x70
#define tySRAM_CODE_ATT		0x80
#define tySRAM_CODE_CC_CD	0x90
#define tySRAM_1BIT			0xa0
#define tySRAM_2BIT			0xb0
#define tySRAM_4BIT			0xc0
#define tySRAM_PALETTE		0xd0
#define tyDDC0				0xe0
#define tyDDC1				0xf0
#define tyPORT_READ			0x04
#define tyPORT_WRITE		0x00
#define tyWITH_LANGTH		0x01
//0xaa window attrib
#define atWIN_TRANSLUCENT	0x10
#define atWIN_SHADOW_2L		0x00
#define atWIN_SHADOW_4L		0x04
#define atWIN_SHADOW_6L		0x08
#define atWIN_SHADOW_8L		0x0c
#define atWIN_SHADOW_EN		0x02
//WINDOW define
#define WINDOW1				0
#define WINDOW2				1
#define WINDOW3				2
#define WINDOW4				3
#define WIN4_X1				0
#define WIN4_X2				OSD_WIDTH-1
#define WIN4_Y1				0
#define WIN4_Y2				OSD_HIGH-3
#define WIN4_ATTR			atWIN_SHADOW_4L
#define WIN4_COLOR			bGRAY>>4//bBLUE>>4
#define WIN3_X1				WIN4_X1+4
#define WIN3_X2				WIN4_X2-4
#define WIN3_Y1				WIN4_Y1+9
#define WIN3_Y2				WIN4_Y2-1
#define WIN3_ATTR			atWIN_SHADOW_4L
#define WIN3_COLOR			bCYAN>>4
#define WIN2_X1				0
#define WIN2_X2				OSD_WIDTH-1
#define WIN2_Y1				0
#define WIN2_Y2				OSD_HIGH-3
#define WIN2_ATTR			atWIN_SHADOW_4L | atWIN_SHADOW_EN
#define WIN2_COLOR			bLIGHT>>4//bBLUE>>4

//OSD Position
#define OSD_X1				PanelWidth/16-1
#define OSD_X2				15*PanelWidth/16-OSD_WIDTH*12+1
#define OSD_X3				(PanelWidth-OSD_WIDTH*12)/2
#define OSD_Y1				PanelHeight/12-1
#define OSD_Y2				11*PanelHeight/12-OSD_HIGH*18+1
#define OSD_Y3				(PanelHeight-OSD_HIGH*18)/2
#define OSD_Y4				(PanelHeight-6*18)/2
#define OSD3_Px 				(PanelWidth - (12 * 4* 10))

//Code Attrib define
#define caONE_BIT_256	0x0000
#define caONE_BIT_512	0x0004
#define caTWO_BIT		0x0008
#define caFOUR_BIT		0x000c
#define caMIX			0x0002
#define caBLINK			0x0001

// OSD Palette Data
#define clBLACK			0x0000
#define clRED			0xf800
#define clGREEN			0x07e0
#define clBLUE			0x001F
#define clCYAN			(clBLUE|clGREEN)
#define clMAGENTA		(clRED|clBLUE)
#define clYELLOW		(clRED|clGREEN)
#define clWHITE			(clRED|clGREEN|clBLUE)
#define clDGREEN		0x0410
#define clGRAY			0xB596//0x8410//0x8C71
#define clLIGHT			0xCE59
#define clLBLUE			0x0010//0x02b6

#define bBLACK		0x0000
#define bRED		0x0020
#define bGREEN		0x0030
#define bBLUE		0x0040
#define bCYAN		0x0050
#define bMAGENTA	0x0060
#define bYELLOW		0x0070
#define bWHITE		0x0080
#define bDGREEN		0x0090
#define bGRAY		0x00a0
#define bLIGHT		0x00b0
#define bLBLUE		0x00c0
#define fBLACK		0x0000
#define fRED		0x0100
#define fGREEN		0x0200
#define fBLUE		0x0300
#define fCYAN		0x0400
#define fMAGENTA	0x0500
#define fYELLOW		0x0600
#define fWHITE		0x0700
#define fDGREEN		0x0900
#define fGRAY		0x0a00
#define fLIGHT		0x0b00
#define fLBLUE		0x0c00

#define BAR_COLOR		fMAGENTA|bBLACK //(13*4+OFFSET_2BIT)<<8
#define VALUE_COLOR		fMAGENTA|bBLACK
#define DESC_COLOR		fWHITE|bBLACK
#define FUN_COLOR		fWHITE|bBLACK
#define SEL_FUN_COLOR	fMAGENTA|bBLACK //(13*4+OFFSET_2BIT)<<8
#define RES_COLOR		fGREEN|bBLACK
#define MODE_COLOR		fRED|bGRAY
#define SET_ICON_COLOR	bBLUE>>4
#define WAIT_COLOR		(64+OFFSET_4BIT)<<8
#define WARING_COLOR	(80+OFFSET_4BIT)<<8
#define SOURCE_COLOR	fYELLOW|bBLACK
#define VERSION_COLOR	fWHITE|fBLACK
#define ChannelColor		fGREEN|bBLACK
#define TextColor 		fGRAY|bMAGENTA
#define TextUnable		fGRAY|bBLACK

#define MAINMENU_RES_ADDR 		ROW11+14
#define MAINMENU_DESC_ADDR		ROW4+2
#define MAINMENU_VALUE_ADDR		ROW4+25
#define MAINMENU_BAR_ADDR			ROW4+16
#define MAINMENU_MODE_ADDR		ROW12+6
#define FACTMENU_BAR_ADDR			ROW10+10
#define FACTMENU_VALUE_ADDR		ROW10+19
#define HOTKEYMENU_RES_ADDR 		ROW2+14
#define HOTKEYMENU_DESC_ADDR		ROW1+2
#define HOTKEYMENU_VALUE_ADDR	ROW1+25
#define HOTKEYMENU_BAR_ADDR		ROW1+16
#define VERSION_ADDR				ROW0+2
#define BACKLIGHTTIME_ADDR			ROW12+20

#define MSG_OUTRANGE	0
#define MSG_NOSYNC		1
#define MSG_DISCONNECT	2	
#define MSG_AUTOTUNE	3
#define MSG_AUTOCOLOR	4
#define MSG_EEPROMINIT	5
#define MSG_AUTOSET		6	//LO_CS

#define cANALOG		0
#define cDVI			1
#define cYPbPr		2
#define cSVIDEO		3
#define cCOMPOSIT	4
#define cTV			5

typedef struct{
	unsigned char Index;
	unsigned short Address;
	unsigned char L2Max;
	unsigned char Icon;
}ICONDEF;

typedef struct{
	unsigned char Index;
	unsigned short Address;
	unsigned short SelAddr;
	unsigned char *Tab;
}FACTDEF;
/***************************************************************************
*
*  Project      : NT68560
*
*  File name    : OSD_tab.H
*
* Purpose       : This is the declaration file for OSD font.
*
*  Rev  Date     Author(s)      Remark
*  ---  ------   ---------      --------------------------------------------
*
***************************************************************************/
#define _Space				0x20		/* : */
#define _DOT				0x2e		/* : */
//number
#define _0                 	0x30        /* 0 */
#define _1                 	0x31        /* 1 */
#define _2                 	0x32        /* 2 */
#define _3                 	0x33        /* 3 */
#define _4                 	0x34        /* 4 */
#define _5                	0x35        /* 5 */
#define _6                 	0x36        /* 6 */
#define _7                	0x37        /* 7 */
#define _8                 	0x38        /* 8 */
#define _9                	0x39        /* 9 */
#define _2DOT				0x3A		/* : */
 
#define _A                  0x41        // A
#define _B                  0x42        // B
#define _C                  0x43        // C
#define _D                  0x44        // D
#define _E                  0x45        // E
#define _F                  0x46        // F
#define _G                  0x47        // G
#define _H                  0x48        // H
#define _I                  0x49        // I
#define _J                  0x4A        // J
#define _K                  0x4B        // K
#define _L                  0x4C        // L
#define _M                  0x4D        // M
#define _N                  0x4E        // N
#define _O					0x4F		// O
#define _P                  0x50        // P
#define _Q                  0x51        // Q
#define _R                  0x52        // R
#define _S                  0x53        // S
#define _T                  0x54        // T
#define _U                  0x55        // U
#define _V                  0x56        // V
#define _W                  0x57        // W
#define _X                  0x58        // X
#define _Y                  0x59        // Y
#define _Z                  0x5A        // Z
#define _a                  0x61        // a
#define _b                  0x62        // b
#define _c                  0x63        // c
#define _d                  0x64        // d
#define _e                  0x65        // e
#define _f                  0x66        // f
#define _g                  0x67        // g
#define _h                  0x68        // h
#define _i                  0x69        // i
#define _j                  0x6A        // j
#define _k                  0x6B        // k
#define _l                  0x6C        // l
#define _m                  0x6D        // m
#define _n                  0x6E        // n
#define _o					0x6F		// o
#define _p                  0x70        // p
#define _q                  0x71        // q
#define _r                  0x72        // r
#define _s                  0x73        // s
#define _t                  0x74        // t
#define _u                  0x75        // u
#define _v                  0x76        // v
#define _w                  0x77        // w
#define _x                  0x78        // x
#define _y                  0x79        // y
#define _z                  0x7A        // z

#define _P00                0x7b        // B
#define _P01                0x7c        // C
#define _P02                0x7d        // C
#define _P03                0x7e        // D
#define _P04                0x7f        // E
#define _P05                0x80        // F
#define _P06                0x81        // B
#define _P07                0x82        // C
#define _P08                0x83        // D
#define _P09                0x84        // E
#define _P0a                0x85        // F
#define _P0b                0x86        // B
#define _P0c                0x87        // C
#define _P0d                0x88        // D
#define _P0e                0x89        // E
#define _P0f                0x8a        // F
#define _P10                0x8b        // F
#define _P11                0x8c        // B
#define _P12                0x8d        // C
#define _P13                0x8e        // D
#define _P14                0x8f        // E
#define _P15                0x90        // F
#define _P16                0x91        // B
#define _P17                0x92        // C
#define _P18                0x93        // D
#define _P19                0x94        // E
#define _P1a                0x95        // F
#define _P1b                0x96        // B
#define _Red0				0x97        // Ree
#define _Red1               0x98        // 
#define _Red2               0x99        // 
#define _Green0             0x9a        // Green
#define _Green1             0x9b        // 
#define _Green2             0x9c        // 
#define _Green3             0x9d        // 
#define _Blue0              0x9e        // Blue
#define _Blue1              0x9f        // 
#define _Blue2				0xa0        // 

#define _C00                0xa1        // ¨¥
#define _C01                0xa2        // ¤¤
#define _C02                0xa3        // ¤å
#define _C03                0xa4        // Â²
#define _C04                0xa5        // Ê^
#define _C05                0xc7        // Ác
#define _C06                0xc8        // Åé
#define _C07                0xc5        // ¤é
#define _C08                0xc6        // ¥»
#define _C09                0xc4        // »y
#define _C0a                0xa8        // «H
#define _C0b                0xa9        // ¸¹
#define _C0c                0xae        // ­µ
#define _C0d                0xaf        // ¶q
#define _C0e                0xb0        // ©w
#define _C0f                0xb1        // ¿ï
#define _C10                0xb2        // °Ê
#define _C11                0xb3        // ³]
#define _C12                0xb4        // ¤ô
#define _C13                0xb5        // ¥­
#define _C14                0xb6        // ¦ì
#define _C15                0xb7        // ¸m
#define _C16                0xb8        // ««
#define _C17                0xb9        // ª½
#define _C18                0xbb        // ¦Û
#define _C19                0xbe        // ½Õ
#define _C1a                0xbf        // ¾ã
#define _C1b                0xa6        // ¦â 
#define _C1c                0xaa        // «G
#define _C1d                0xab        // «×
#define _C1e                0xa0        // »y»     
#define _C1f                0xa7        // ¶}
#define _C20                0xac        // ¹ï
#define _C21                0xad        // ¤ñ
#define _C22                0xba        // ¬Û
#define _C23                0xbc        // °Ê
#define _C24                0xbd        // ½Õ
#define _C25                0xc0        // ¹Ï
#define _C26                0xc1        //¦ ¹³
#define _C27                0xc2        // ¦r
#define _C28                0xc3        // ­«
#define _C29                0xc9        // Åã
#define _C2a                0xca        // ¥Ü    
#define _C2b                0xcb        // ®É
#define _C2c                0xcc        // ¶¡
#define _C2d                0xcd        // ²M
#define _C2e                0xce        // ´·
#define _C2f                0xcf        // ·½
#define _C30                0xd0        // ¿ï
#define _C31                0xd1        // ¾Ü
#define _C32                0xd2        // ÁU
#define _C33                0xd3        // «ø
#define _C34                0xd4        // Ãþ
#define _C35                0xd5        // ¨S
#define _C36                0xd6        // ¦³
#define _C37                0xd7        // ¿é
#define _C38                0xd8        // ¶W
#define _C39                0xd9        // ¥X
#define _C3a                0xda        // ¤u
#define _C3b                0xdb        // §@
#define _C3c                0xdc        // ­S
#define _C3d                0xdd        // ³ò
#define _C3e                0xde        // µæ
#define _C3f                0xdf        // ³æ
#define _C40                0xe0        // Ãö
#define _C41                0xe1        // ÃC
#define _C42                0xe2        // ¨Ï
#define _C43                0xe3        // ¥Î
#define _C44                0xe4        // ªÌ
#define _C45                0xe5        // ³ò
#define _C46                0xe6        // ¬õ
#define _C47                0xe7        // ºñ
#define _C48                0xe8        // ÂÅ
#define _C49                0xe9        // §_
#define _C4a                0xea        // ¬O
#define _C4b                0xeb        // ¦^
#define _C4c                0xec        // ³Â
#define _C4d                0xed        // ¼e
#define _C4e                0xee        // ÃC
#define _C4f                0xef        // ºñ
#define _C50                0xf0        // ¬õ
#define _C51                0xf1        // ÂÅ
#define _C52                0xf2        // ¹ï
#define _C53                0xf3        // ÀR
#define _C54                0xf4        // ÀR
#define _C55                0xf5        // ¶}
#define _C56                0xf6        // Ãö
#define _C57                0xf7        // ¼e
#define _C58                0xf8        // Åã
#define _C59                0xf9        // ®É
#define _C5a                0xfa        // ¶¡
#define _C5b                0xfb        // ¿é
#define _C5c                0xfc        // ¤J
#define _C5d                0xfd        // °T
#define _C5e                0xfe        // ¸¹
#define _C5f                0xff        // ½d
#define _C60                0x90        // ³ò
#define _C61                0x91        // Ãþ
#define _C62                0x92        // ¼Æ
#define _C63                0x93        // ³æ
#define _C64                0x94        // ¾Ü
#define _C65                0x95        // ½d
// Japan
#define _J00                0xd0        // 
#define _J01                0xd1        // 
#define _J02                0xd2        // 
#define _J03                0xd3        // 
#define _J04                0xd4        // 
#define _J05                0xd5        // 
#define _J06                0xd6        // 
#define _J07                0xd7        // 
#define _J08                0xd8        // 
#define _J09                0xd9        // 
#define _J0a                0xda        // 
#define _J0b                0xdb        // 
#define _J0c                0xdc        // 
#define _J0d                0xdd        // 
#define _J0e                0xde        // 
#define _J0f                0xdf        // 
#define _J10                0xe0        // 
#define _J11                0xe1        // 
#define _J12                0xe2        // 
#define _J13                0xe3        // 
#define _J14                0xe4        // 
#define _J15                0xe5        // 
#define _J16                0xe6        // 
#define _J17                0xe7        // 
#define _J18                0xe8        // 
#define _J19                0xe9        // 
#define _J1a                0xea        // 
#define _J1b                0xeb        // 
#define _J1c                0xec        // 
#define _J1d                0xed        // 
#define _J1e                0xee        // 
#define _J1f                0xef        // 
#define _J20                0xf0        // 
#define _J21                0xf1        // 
#define _J22                0xf2        // 
#define _J23                0xf3        // 
#define _J24                0xf4        // 
#define _J25                0xf5        // 
#define _J26                0xf6        // 
#define _J27                0xf7        // 
#define _J28                0xf8        // 
#define _J29                0xf9        // 
#define _J2a                0xfa        // 
#define _J2b                0xfb        // 
#define _J2c                0xfc        // 
#define _J2d                0xfd        // 
#define _J2e                0xfe        // 
#define _J2f                0xff        // 
#define _J30                0x90        // 
#define _J31                0x91        // 
#define _J32                0x92        // 
#define _J33                0x93        // 
#define _J34                0x94        // 
#define _J35                0x95        // 
#define _J36                0x96        // 


void OsdInit(void);
void ClearOSD(void);
void Osd_Off(void);
void Osd_On(unsigned char);
void OsdPosition(void);
void WritePage560(unsigned char addr1,unsigned char addr2,unsigned char *p);
void OsdProcess(void);
void WriteSeqIndexPort(unsigned short,unsigned char,unsigned char *,unsigned short);
void WriteIndexPort(unsigned short,unsigned char,unsigned char);
void WriteWordIndexPort(unsigned short,unsigned char,unsigned short);
void OpenWindow(unsigned char,unsigned char,unsigned char,unsigned char,unsigned char,unsigned char,unsigned char);
void OsdPosition();
void ShowBar(unsigned short,unsigned short,unsigned short,unsigned short,unsigned short);
void ShowCBar(unsigned short,unsigned short,unsigned short,unsigned short,unsigned short);
void ShowValue(unsigned short,unsigned short,unsigned short);
void ShowMain(unsigned char);
void RefreshIcon();
void ShowDesc(unsigned char,unsigned short,unsigned short);
void ShowMode(unsigned short,unsigned short);
void ShowResolution(unsigned short,unsigned short);
//void ShowTextGraphicMode();
void ClearTextArea();
void ShowYesNo(unsigned char);
void ShowLanguage();
void ShowMessage(unsigned char);
void ShowOutOfRange();
void ShowSyncMode();
void ShowColorMenu();
void ShowRGBMenu();
void ShowFactMenu();
void ShowFact();
void ShowFactCursor();
void ShowMuteFuncOnOff();	// +jwshin 061025
void ShowMonSel();	// +jwshin 060908
void ShowRGB_A();	// +jwshin 060908
void ShowRGB_B();	// +jwshin 060908
void ShowVersion();
void ClearLine(unsigned char);
void ShowTvSystem();
void ShowBurnInPattern(bit);
void ShowOSDFrame(unsigned char);
void ShowSubMenu(unsigned char,unsigned char);
void ShowStatus(unsigned short,unsigned short);
void ShowOnOff(unsigned char);
void ShowUserRGBMenu();
void ShowKeyMenu(unsigned char,unsigned char);
void ShowOSDPosition();
void ShowBrightnessMenu();
void ShowSharpness();
void ShowTurboModeMenu();
void ShowTurboMode();
void ShowBackLightTime();
void ShowScalerMode(unsigned char);
void ShowAddDel(unsigned char );
void ShowTV_Input(unsigned char);
void ShowFineTune(void);
void ShowDesc_TV(unsigned char,unsigned short,unsigned short);
void ShowDesc_Sound(unsigned char,unsigned short,unsigned short);
void ShowSource_Video(void);
void DisplaySource(unsigned char);
void InitEDID_Save(void);
void DisplayCaption(unsigned char i);
void	ChannelMove(unsigned char No);
void ShowDigital(unsigned short value,unsigned char Cable);

void ShowDebug(unsigned short,unsigned short,unsigned short);		// +jwshin 061019

#endif
