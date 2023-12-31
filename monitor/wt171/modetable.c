/****************************************************************************
   +----------------------------------------------------------------------+
   | Copyright EDtech co.ltd 2002                                         |
   | EDtech co.ltd reserves the right to change products                  |
   | or specifications without notice.                                    |
   +----------------------------------------------------------------------+
   Project    : TFT LCD monitor & TV
   Version    : 
   File Name  : 
   Functions  : 
   Revision   :

   2003-01-10 2:39오후  JDHAN           Modified for Monitor-TV
****************************************************************************/

#include	"TopHeader.h"

/*
typedef struct
{
	BYTE Phase;
	WORD HF;
	WORD VF;
	WORD HTotal;
	WORD IHAS;
	WORD IVAS;
	WORD IHAW;
	WORD IVAW;
	BYTE IClkDly;
}	ModeTable;
*/
//sizeof(ModeList)/sizeof(ModeTable)
//ModeTable의 structure구조는 위와 같이 선언하였다....(참고할것)

#if 1
				// btc 보드
#ifndef WXGA_Panel	//************
code ModeTable	ModeList[]=
{
//-----------------------------------------------------------------------------------------------------
//640x350
//-----------------------------------------------------------------------------------------------------
//	  Phase	ihf     ivf     Ht     IHAS   IVAS  IHAW    IVAW 	IclkDly
//-----------------------------------------------------------------------------------------------------
	 {0x06,	315,	701,	800,	111,	58,	640,	350,	5}	//640x350@70 //NOT VESA
	,{0x06,	379,	851,	832,	 78,	55,	640,	350,	5}	//640x350@85 //NOT VESA
//-----------------------------------------------------------------------------------------------------
//640x400
//-----------------------------------------------------------------------------------------------------
//	  Phase	ihf     ivf     Ht     IHAS   IVAS  IHAW    IVAW 	IclkDly  
//-----------------------------------------------------------------------------------------------------
	,{0x06,	315,	701,	800,	111,	40,	640,	400,	5}	//640x400@70 //DOS640
	,{0x06,	379,	851,	832,	142,	39,	640,	400,	5}	//640x400@85 //DOS640
	,{0x06,	311,	749,	800,	 90,	30,	640,	400,	5}	//??75
	,{0x06,	352,	785,	800,	122,	32,	640,	400,	5}	//??78
//-----------------------------------------------------------------------------------------------------
//720x400
//-----------------------------------------------------------------------------------------------------
//	  Phase	ihf     ivf     Ht     IHAS   IVAS  IHAW    IVAW 	IclkDly  
//-----------------------------------------------------------------------------------------------------

	//,{0x06,	315,	701,	900,	129,	50,	720,	400,	5}	//720x400@70 //DOS720
	,{0x06,	315,	701,	904,	129,	50,	720,	400,	5}	//720x400@70 //DOS720
	,{10,	379,	850,	936,	142,	40,	720,	400,	5}	//720x400@85 //DOS720
//-----------------------------------------------------------------------------------------------------
//640x480
//-----------------------------------------------------------------------------------------------------
//	  Phase	ihf     ivf     Ht     IHAS   IVAS    	IHAW    IVAW 	IclkDly  
//-----------------------------------------------------------------------------------------------------
	,{21,	315,	600,	800,	106,	30,	640,	480,	4}	//640x480@60 //VESA
	,{25,	350,	667,	832,	126,	26,	640,	480,	5}	//add 640x480@66 //VESA
	,{0x06,	349,	699,	832,	123,	19,	640,	480,	5}	//add 640x480@70 //VESA
	,{25,	378,	728,	832,	129,	26,	640,	480,	5}	//640x480@72 //VESA
	,{25,	375,	750,	840,	145,	14,	640,	480,	5}	//640x480@75 //VESA
	,{19,	433,	850,	832,	98,		43,	640,	480,	0}	//640x480@85 //VESA
//-----------------------------------------------------------------------------------------------------
//800x600
//-----------------------------------------------------------------------------------------------------
//	  Phase	ihf     ivf     Ht     IHAS   IVAS    	IHAW    IVAW 	IclkDly  
//-----------------------------------------------------------------------------------------------------
	,{0x06,	352,	562,	1024,	162,	19,	800,	600,	3}	//800x600@56 //VESA
	,{0x06,	379,	600,	1056,	178,	22,	800,	600,	0}	//800x600@60 //VESA
	,{0x09,	446,	701,	1040,	161,	19,	800,	600,	0}	//Radeon
	,{6,	481,	722,	1040,	146,	24,	800,	600,	0}	//800x600@72 //VESA
	,{6,	469,	750,	1056,	202,	19,	800,	600,	0}	//800x600@75 //VESA
	,{25,	537,	851,	1048,	177,	25,	800,	600,	5}	//800x600@85 //VESA
//-----------------------------------------------------------------------------------------------------
//1024x768
//-----------------------------------------------------------------------------------------------------
//	  Phase	ihf     ivf     Ht     IHAS   IVAS    	IHAW    IVAW 	IclkDly  
//-----------------------------------------------------------------------------------------------------
	,{17,	484,	603,	1344,	256,	30,	1024,	768,	6}	//1024x768@60//VESA
	,{10,	565,	701,	1328,	240,	30,	1024,	768,	5}	//1024x768@70//VESA
	,{0x03,	575,	715,	1360,	238,	27,	1024,	768,	5}	//Radeon
	,{13,	600,	750,	1312,	232,	26,	1024,	768,	5}	//1024x768@75//VESA
	,{31,	687,	850,	1376,	263,	34,	1024,	768,	5}	//1024x768@85//VESA
//-----------------------------------------------------------------------------------------------------
//1152x 864 
//-----------------------------------------------------------------------------------------------------
//	  Phase	ihf     ivf     Ht     IHAS   IVAS    	IHAW    IVAW 	IclkDly  
//-----------------------------------------------------------------------------------------------------
	,{0x06,	538,	599,	1520,	275,	32,	1152,	864,	5}	//GeForce2GTS	//03-08-06
	,{0x06,	629,	699,	1536,	270,	34,	1152,	864,	3}	//GeForce2MX
	,{0x06,	649,	720,	1544,	320,	36,	1152,	864,	5}	//GeForce2MX
	,{20,	675,	750,	1600,	343,	30,	1152,	864,	0}	//1152x864@75//VESA
	,{0x06,	771,	850,	1552,	280,	38,	1152,	864,	5}	//VESA ??
//-----------------------------------------------------------------------------------------------------
//1280x768
//-----------------------------------------------------------------------------------------------------
//	  Phase	ihf     ivf     Ht     IHAS   IVAS  IHAW    IVAW 	IclkDly   
//-----------------------------------------------------------------------------------------------------
	//,{20,	477,	599,	1680,	383,	34,	1280,	768,	3}	//1280x768@60	//WXGA //2003-11-25
	,{20,	477,	599,	1680,	294,	21,	1280,	768,	3}	//1280x768@60	//WXGA //2003-11-25
//	,{20,	561,	700,	1696,	346,	34,	1280,	768,	3}	//1280x768@60	//WXGA //2004-06-11
//	,{20,	601,	750,	1712,	322,	34,	1280,	768,	3}	//1280x768@60	//WXGA 
//	,{20,	686,	851,	1712,	322,	34,	1280,	768,	3}	//1280x768@60	//WXGA 
/-----------------------------------------------------------------------------------------------------
//1280x960
//-----------------------------------------------------------------------------------------------------
//	  Phase	ihf     ivf     Ht     IHAS   IVAS    	IHAW    IVAW 	IclkDly   
//-----------------------------------------------------------------------------------------------------
	,{20,	600,	600,	1800,	383,	34,	1280,	960,	3}	//1280x960@60//VESA
	,{0x06,	699,	698,	1728,	364,	38,	1280,	960,	0}	//GeForce2MX
	,{0x06,	721,	720,	1728,	384,	40,	1280,	960,	0}	//GeForce2MX
	,{0x06,	751,	750,	1728,	320,	40,	1280,	960,	0}	//GeForce2GTS
	,{19,	860,	850,	1728,	342,	45,	1280,	960,	0}	//1280x960@85//VESA
//-----------------------------------------------------------------------------------------------------
//1280x1024
//-----------------------------------------------------------------------------------------------------
//	  Phase	ihf     ivf     Ht     IHAS   IVAS    	IHAW    IVAW 	IclkDly   
//-----------------------------------------------------------------------------------------------------
	,{20,	640,	600,	1688,	319,	36,	1280,	1024,	1}	//1280x1024@60//VESA
	,{0x06,	749,	698,	1728,	311,	37,	1280,	1024,	1}	//add 1280x1024@70//VESA
	,{0x06,	768,	720,	1688,	311,	37,	1280,	1024,	1}	//add 1280x1024@72//VESA
	,{30,	800,	750,	1688,	350,	36,	1280,	1024,	1}	//1280x1024@75//VESA
//-----------------------------------------------------------------------------------------------------
//other's 
//-----------------------------------------------------------------------------------------------------
//	  Phase	ihf     ivf     Ht     IHAS   IVAS    	IHAW    IVAW 	IclkDly  
//-----------------------------------------------------------------------------------------------------
	,{0x06,	350,	666,	864,	160,	42,	640,	480,	5}	//MAC
	,{0x06,	497,	745,	1152,	288,	42,	832,	624,	5}	//MAC
	,{0x06,	686,	750,	1456,	272,	42,	1152,	870,	5}	//MAC
	,{0x06,	686,	750,	1456,	272,	42,	1152,	870,	5}	//MAC
	//etc GraphicCards
	,{0x06,	350,	700,	816,	144,	30,	640,	480,	5}	//GeForce2GTS
	,{0x06,	437,	700,	1040,	198,	25,	800,	600,	3}	//GeForce2GTS
	,{0x06,	577,	720,	1362,	280,	32,	1024,	768,	5}	//GeForce2GTS
	,{0x06,	447,	599,	1668,	330,	30,	1280,	720,	5}	//GeForce2GTS
	,{0x06,	525,	699,	1694,	340,	30,	1280,	720,	5}	//GeForce2GTS
	,{0x06,	541,	720,	1698,	334,	30,	1280,	720,	5}	//GeForce2GTS
	,{0x06,	564,	750,	1774,	387,	31,	1280,	720,	5}	//GeForce2GTS
	,{0x06,	769,	720,	1732,	354,	43,	1280,	1024,	3}	//GeForce2MX
	,{0x06,	379,	700,	763,	108,	52,	640,	480,	5}	//GeForce2MX
	,{0x06,	577,	720,	1358,	278,	32,	1024,	768,	5}	//GeForce2MX,GeForce2GTS
	,{0x06,	355,	435,	1264,	232,	48,	1024,	768,	3}	//GeForce2MX
	//etc VESA
	                                           	
	,{0x06,	394,	750,	800,	144,	34,	640,	480,	3}	//VESA ??
	,{0x06,	310,	600,	1000,	64,	34,	848,	480,	5}	//VESA ??
	,{0x06,	459,	885,	1088,	140,	26,	848,	480,	5}	//VESA ??
	,{0x06,	355,	435,	1264,	232,	48,	1024,	380,	5}	//VESA ??
	,{0x06,	642,	850,	1712,	314,	31,	1280,	720,	5}	//VESA ??
	,{0x06,	498,	868,	1632,	284,	43,	1280,	1024,	5}	//VESA ??
//-----------------------------------------------------------------------------------------------------	
};
#else	//************	// ss17 wide //*************
code ModeTable	ModeList[]=
{
//-----------------------------------------------------------------------------------------------------
//640x350
//-----------------------------------------------------------------------------------------------------
//	  Phase	ihf     ivf     Ht     IHAS   IVAS    	IHAW    IVAW 	IclkDly  
//-----------------------------------------------------------------------------------------------------
	 {0x06,	315,	701,	800,	111,	58,	640,	350,	5}	//640x350@70 //NOT VESA
	,{0x06,	379,	851,	832,	 78,	55,	640,	350,	5}	//640x350@85 //NOT VESA
//-----------------------------------------------------------------------------------------------------
//640x400
//-----------------------------------------------------------------------------------------------------
//	  Phase	ihf     ivf     Ht     IHAS   IVAS    	IHAW    IVAW 	IclkDly  
//-----------------------------------------------------------------------------------------------------
	,{0x06,	315,	701,	800,	111,	40,	640,	400,	5}	//640x400@70 //DOS640
	,{0x06,	379,	851,	832,	142,	39,	640,	400,	5}	//640x400@85 //DOS640
	,{0x06,	311,	749,	800,	 90,	30,	640,	400,	5}	//??75
	,{0x06,	352,	785,	800,	122,	32,	640,	400,	5}	//??78
//-----------------------------------------------------------------------------------------------------
//720x400
//-----------------------------------------------------------------------------------------------------
//	  Phase	ihf     ivf     Ht     IHAS   IVAS    	IHAW    IVAW 	IclkDly  
//-----------------------------------------------------------------------------------------------------

	,{0x06,	315,	701,	898,	129,	50,	720,	400,	0}	//720x400@70 //DOS720
	,{10,	379,	850,	934,	142,	40,	720,	400,	0}	//720x400@85 //DOS720
//-----------------------------------------------------------------------------------------------------
//640x480
//-----------------------------------------------------------------------------------------------------
//	  Phase	ihf     ivf     Ht     IHAS   IVAS    	IHAW    IVAW 	IclkDly  
//-----------------------------------------------------------------------------------------------------
	,{21,	315,	600,	800,	106,	30,	640,	480,	4}	//640x480@60 //VESA
	,{25,	350,	667,	832,	126,	26,	640,	480,	5}	//add 640x480@66 //VESA
	,{0x06,	349,	699,	832,	123,	19,	640,	480,	5}	//add 640x480@70 //VESA
	,{25,	378,	728,	832,	129,	26,	640,	480,	5}	//640x480@72 //VESA
	,{25,	375,	750,	840,	145,	14,	640,	480,	5}	//640x480@75 //VESA
	,{19,	433,	850,	832,	98,	43,	640,	480,	0}	//640x480@85 //VESA
//-----------------------------------------------------------------------------------------------------
//800x600
//-----------------------------------------------------------------------------------------------------
//	  Phase	ihf     ivf     Ht     IHAS   IVAS  IHAW    IVAW 	IclkDly  
//-----------------------------------------------------------------------------------------------------
	,{0x06,	352,	562,	1024,	162,	19,	800,	600,	3}	//800x600@56 //VESA
	,{0x06,	379,	600,	1056,	178,	22,	800,	600,	0}	//800x600@60 //VESA
	,{0x09,	446,	701,	1040,	161,	19,	800,	600,	0}	//Radeon
	,{6,	481,	722,	1040,	146,	24,	800,	600,	0}	//800x600@72 //VESA
	,{6,	469,	750,	1056,	202,	19,	800,	600,	0}	//800x600@75 //VESA
	,{25,	537,	851,	1048,	177,	25,	800,	600,	5}	//800x600@85 //VESA
//-----------------------------------------------------------------------------------------------------
//1024x768
//-----------------------------------------------------------------------------------------------------
//	  Phase	ihf     ivf     Ht     IHAS   IVAS  IHAW    IVAW 	IclkDly  
//-----------------------------------------------------------------------------------------------------
	,{17,	484,	603,	1344,	256,	30,	1024,	768,	6}	//1024x768@60//VESA
	,{10,	565,	701,	1328,	240,	30,	1024,	768,	5}	//1024x768@70//VESA
	,{0x03,	575,	715,	1360,	238,	27,	1024,	768,	5}	//Radeon
	,{13,	600,	750,	1312,	232,	26,	1024,	768,	5}	//1024x768@75//VESA
	,{31,	687,	850,	1376,	263,	34,	1024,	768,	5}	//1024x768@85//VESA
//-----------------------------------------------------------------------------------------------------
//1152x 864 
//-----------------------------------------------------------------------------------------------------
//	  Phase	ihf     ivf     Ht     IHAS   IVAS  IHAW    IVAW 	IclkDly  
//-----------------------------------------------------------------------------------------------------
	,{0x06,	538,	599,	1520,	275,	32,	1152,	864,	5}	//GeForce2GTS	//03-08-06
	,{0x06,	629,	699,	1536,	270,	34,	1152,	864,	3}	//GeForce2MX
	,{0x06,	649,	720,	1544,	320,	36,	1152,	864,	5}	//GeForce2MX
	,{20,	675,	750,	1600,	343,	30,	1152,	864,	0}	//1152x864@75//VESA
	,{0x06,	771,	850,	1552,	280,	38,	1152,	864,	5}	//VESA ??
//-----------------------------------------------------------------------------------------------------
//1280x768
//-----------------------------------------------------------------------------------------------------
//	  Phase	ihf     ivf     Ht     IHAS   IVAS    	IHAW    IVAW 	IclkDly   
//-----------------------------------------------------------------------------------------------------
	//,{20,	477,	599,	1680,	383,	34,	1280,	768,	3}	//1280x768@60	//WXGA //2003-11-25
	,{20,	477,	599,	1664,	278,	22,	1280,	768,	3}	//1280x768@60	//WXGA //2003-11-25
	//,{20,	477,	599,	1664,	278,	22,	1280,	768,	3}	//1280x768@60	//WXGA //2003-11-25
//	,{20,	561,	700,	1696,	346,	34,	1280,	768,	3}	//1280x768@60	//WXGA //2004-06-11
//	,{20,	601,	750,	1712,	322,	34,	1280,	768,	3}	//1280x768@60	//WXGA 
//	,{20,	686,	851,	1712,	322,	34,	1280,	768,	3}	//1280x768@60	//WXGA 
	
//-----------------------------------------------------------------------------------------------------
//1280x960
//-----------------------------------------------------------------------------------------------------
//	  Phase	ihf     ivf     Ht     IHAS   IVAS    	IHAW    IVAW 	IclkDly   
//-----------------------------------------------------------------------------------------------------
	,{20,	600,	600,	1800,	383,	34,	1280,	960,	3}	//1280x960@60//VESA
	,{0x06,	699,	698,	1728,	364,	38,	1280,	960,	0}	//GeForce2MX
	,{0x06,	721,	720,	1728,	384,	40,	1280,	960,	0}	//GeForce2MX
	,{0x06,	751,	750,	1728,	320,	40,	1280,	960,	0}	//GeForce2GTS
	,{19,	860,	850,	1728,	342,	45,	1280,	960,	0}	//1280x960@85//VESA
//-----------------------------------------------------------------------------------------------------
//1280x1024
//-----------------------------------------------------------------------------------------------------
//	  Phase	ihf     ivf     Ht     IHAS   IVAS    	IHAW    IVAW 	IclkDly   
//-----------------------------------------------------------------------------------------------------
	,{20,	640,	600,	1688,	319,	36,	1280,	1024,	1}	//1280x1024@60//VESA
	,{0x06,	749,	698,	1728,	311,	37,	1280,	1024,	1}	//add 1280x1024@70//VESA
	,{0x06,	768,	720,	1688,	311,	37,	1280,	1024,	1}	//add 1280x1024@72//VESA
	,{30,	800,	750,	1688,	350,	36,	1280,	1024,	1}	//1280x1024@75//VESA
//-----------------------------------------------------------------------------------------------------
//other's 
//-----------------------------------------------------------------------------------------------------
//	  Phase	ihf     ivf     Ht     IHAS   IVAS    	IHAW    IVAW 	IclkDly  
//-----------------------------------------------------------------------------------------------------
	,{0x06,	350,	666,	864,	160,	42,	640,	480,	5}	//MAC
	,{0x06,	497,	745,	1152,	288,	42,	832,	624,	5}	//MAC
	,{0x06,	686,	750,	1456,	272,	42,	1152,	870,	5}	//MAC
	,{0x06,	686,	750,	1456,	272,	42,	1152,	870,	5}	//MAC
	//etc GraphicCards
	,{0x06,	350,	700,	816,	144,	30,	640,	480,	5}	//GeForce2GTS
	,{0x06,	437,	700,	1040,	198,	25,	800,	600,	3}	//GeForce2GTS
	,{0x06,	577,	720,	1362,	280,	32,	1024,	768,	5}	//GeForce2GTS
	,{0x06,	447,	599,	1668,	330,	30,	1280,	720,	5}	//GeForce2GTS
	,{0x06,	525,	699,	1694,	340,	30,	1280,	720,	5}	//GeForce2GTS
	,{0x06,	541,	720,	1698,	334,	30,	1280,	720,	5}	//GeForce2GTS
	,{0x06,	564,	750,	1774,	387,	31,	1280,	720,	5}	//GeForce2GTS
	,{0x06,	769,	720,	1732,	354,	43,	1280,	1024,	3}	//GeForce2MX
	,{0x06,	379,	700,	763,	108,	52,	640,	480,	5}	//GeForce2MX
	,{0x06,	577,	720,	1358,	278,	32,	1024,	768,	5}	//GeForce2MX,GeForce2GTS
	,{0x06,	355,	435,	1264,	232,	48,	1024,	768,	3}	//GeForce2MX
	//etc VESA
	                                           	
	,{0x06,	394,	750,	800,	144,	34,	640,	480,	3}	//VESA ??
	,{0x06,	310,	600,	1000,	64,	34,	848,	480,	5}	//VESA ??
	,{0x06,	459,	885,	1088,	140,	26,	848,	480,	5}	//VESA ??
	,{0x06,	355,	435,	1264,	232,	48,	1024,	380,	5}	//VESA ??
	,{0x06,	642,	850,	1712,	314,	31,	1280,	720,	5}	//VESA ??
	,{0x06,	498,	868,	1632,	284,	43,	1280,	1024,	5}	//VESA ??
//-----------------------------------------------------------------------------------------------------	
};
#endif	//************


#else

code ModeTable	ModeList[]=
{//	  Phase	ihf     ivf     Ht     Ihas   Ivas    	Ihaw    Ivaw 	icd   
//	 {0x06,	315,	701,	800,	111,	58,	640,	350,	5}	//640x350@70 //NOT VESA
//	,{0x06,	379,	851,	832,	 78,	55,	640,	350,	5}	//640x350@85 //NOT VESA
	 {0x06,	315,	701,	800,	111,	40,	640,	400,	5}	//640x400@70 //DOS640
	,{0x06,	379,	851,	832,	 78,	55,	640,	400,	5}	//640x400@85 //DOS640
	,{0x06,	315,	701,	900,	129,	50,	720,	400,	5}	//720x400@85 //DOS720
	,{0x06,	379,	850,	936,	137,	45,	720,	400,	5}	//720x400@85 //DOS720
	,{0x06,	311,	749,	800,	 90,	30,	640,	400,	5}	//??
	,{0x06,	352,	785,	800,	122,	32,	640,	400,	5}	//??
	,{0x06,	315,	600,	800,	111,	23,	640,	480,	4}	//640x480@60 //VESA
	,{0x06,	378,	728,	832,	123,	19,	640,	480,	5}	//640x480@72 //VESA
	,{0x06,	375,	750,	840,	147,	15,	640,	480,	5}	//640x480@75 //VESA
	,{0x06,	433,	850,	832,	111,	43,	640,	480,	5}	//640x480@85 //VESA
	,{0x06,	352,	562,	1024,	163,	20,	800,	600,	3}	//800x600@56 //VESA
	,{0x06,	379,	600,	1056,	179,	23,	800,	600,	3}	//800x600@60 //VESA
	,{0x06,	481,	722,	1040,	146,	25,	800,	600,	3}	//800x600@72 //VESA
	,{0x06,	469,	750,	1056,	201,	20,	800,	600,	3}	//800x600@75 //VESA
	,{0x06,	537,	851,	1048,	182,	23,	800,	600,	3}	//800x600@85 //VESA
	,{0x06,	484,	603,	1344,	257,	31,	1024,	768,	6}	//1024x768@60//VESA
	,{23,	565,	701,	1328,	237,	31,	1024,	768,	5}	//1024x768@70//VESA
	,{15,	600,	750,	1312,	232,	27,	1024,	768,	5}	//1024x768@75//VESA
	,{0x06,	687,	850,	1376,	236,	27,	1024,	768,	5}	//1024x768@85//VESA
	,{0x06,	675,	750,	1600,	236,	27,	1152,	864,	5}	//1152x864@75//VESA
	,{0x06,	600,	600,	1800,	311,	37,	1280,	960,	5}	//1280x960@60//VESA
	,{0x06,	860,	850,	1728,	311,	37,	1280,	960,	5}	//1280x960@85//VESA

	,{0x06,	640,	600,	1688,	311,	37,	1280,	1024,	5}	//1280x1024@60//VESA
	,{0x06,	800,	750,	1688,	311,	37,	1280,	1024,	3}	//1280x1024@75//VESA


	,{0x06,	350,	666,	864,	160,	42,	640,	480,	5}	//MAC
	,{0x06,	497,	745,	1152,	288,	42,	832,	624,	5}	//MAC
	,{0x06,	686,	750,	1456,	272,	42,	1152,	870,	5}	//MAC
	,{0x06,	686,	750,	1456,	272,	42,	1152,	870,	5}	//MAC
	//etc GraphicCards                         	
	,{0x06,	350,	700,	816,	144,	30,	640,	480,	5}	//GeForce2GTS
	,{0x06,	437,	700,	1040,	198,	25,	800,	600,	3}	//GeForce2GTS
	                                           	
	,{0x06,	577,	720,	1362,	280,	32,	1024,	768,	5}	//GeForce2GTS
	,{0x06,	538,	599,	1596,	290,	32,	1152,	864,	5}	//GeForce2GTS
	,{0x06,	447,	599,	1668,	330,	30,	1280,	720,	5}	//GeForce2GTS
	,{0x06,	525,	699,	1694,	340,	30,	1280,	720,	5}	//GeForce2GTS
	,{0x06,	541,	720,	1698,	334,	30,	1280,	720,	5}	//GeForce2GTS
	,{0x06,	564,	750,	1774,	387,	31,	1280,	720,	5}	//GeForce2GTS
	,{0x06,	751,	750,	1732,	320,	40,	1280,	960,	5}	//GeForce2GTS
	,{0x06,	769,	720,	1732,	354,	43,	1280,	1024,	3}	//GeForce2MX
	,{0x06,	379,	700,	763,	108,	52,	640,	480,	5}	//GeForce2MX
	,{0x06,	577,	720,	1358,	278,	32,	1024,	768,	5}	//GeForce2MX,GeForce2GTS
	,{0x06,	629,	699,	1496,	270,	34,	1152,	864,	5}	//GeForce2MX
	,{0x06,	699,	700,	1732,	364,	38,	1280,	960,	5}	//GeForce2MX
	,{0x06,	721,	720,	1712,	384,	40,	1280,	960,	5}	//GeForce2MX
	,{0x06,	649,	720,	1544,	320,	36,	1152,	864,	5}	//GeForce2MX
	,{0x06,	355,	435,	1264,	232,	48,	1024,	768,	3}	//GeForce2MX
	//etc VESA                                 	
	                                           	
	,{0x06,	394,	750,	800,	144,	34,	640,	480,	3}	//VESA ??
	,{0x06,	310,	600,	1000,	64,	34,	848,	480,	5}	//VESA ??
	,{0x06,	459,	885,	1088,	140,	26,	848,	480,	5}	//VESA ??
	,{0x06,	355,	435,	1264,	232,	48,	1024,	380,	5}	//VESA ??
	,{0x06,	771,	850,	1552,	280,	38,	1152,	864,	5}	//VESA ??
	,{0x06,	642,	850,	1712,	314,	31,	1280,	720,	5}	//VESA ??
	,{0x06,	498,	868,	1632,	284,	43,	1280,	1024,	5}	//VESA ??
}; 

#endif

	
BYTE ModeTotalcount(void)
{
	return(sizeof(ModeList)/sizeof(ModeTable));	//mode감사할때 총 모드테이블숫자를 카운터할때 이용하는 함수,, 그곳에서 토탈모드갯수를 카운터할순없다!!,
}


code PipHVwidth	PipHVawList[]=
{
	{512,384},	{400,300},	{320,240},	//4:3	//0,1,2	(L,M,S)
	{512,288},	{400,225},	{320,180}	//16:9	//3,4,5		//added 16:9 pipsize //2003-08-02
};
