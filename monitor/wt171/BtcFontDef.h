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

//------------------------------------------------------------------------------
//	0 page font define
//------------------------------------------------------------------------------
#define _space		0x00
#define _		_space
#define __		0x00
#define _0		0x01
#define _1		0x02
#define _2		0x03
#define _3		0x04
#define _4		0x05
#define _5		0x06
#define _6		0x07
#define _7		0x08
#define _8		0x09
#define _9		0x0a

#define _A		0x0b
#define _B		0x0c
#define _C		0x0d
#define _D		0x0e
#define _E		0x0f
#define _F		0x10
#define _G		0x11
#define _H		0x12
#define _I		0x13
#define _J		0x14
#define _K		0x15
#define _L		0x16
#define _M		0x17
#define _N		0x18
#define _O		0x19
#define _P		0x1a
#define _Q		0x1b
#define _R		0x1c
#define _S		0x1d
#define _T		0x1e
#define _U		0x1f
#define _V		0x20
#define _W		0x21
#define _X		0x22
#define _Y		0x23
#define _Z		0x24

#define _a		0x25
#define _b		0x26
#define _c		0x27
#define _d		0x28
#define _e		0x29
#define _f		0x2a
#define _g		0x2b
#define _h		0x2c
#define _i		0x2d
#define _j		0x2e
#define _k		0x2f
#define _l		0x30
#define _m		0x31
#define _n		0x32
#define _o		0x33
#define _p		0x34
#define _q		0x35
#define _r		0x36
#define _s		0x37
#define _t		0x38
#define _u		0x39
#define _v		0x3a
#define _w		0x3b
#define _x		0x3c
#define _y		0x3d
#define _z		0x3e

#define	__A		0x49
#define	__U		0x52
#define	__N_		0x71
                	
#define	_D__		0x78	//
#define	_U__		0x79
#define	_A__		0x7a

//------------------------------------------------------
//page 2 - font addr.	2003-04-16 made by thkim
//------------------------------------------------------
#define _PERSENT	0x75	// Persent(%)
#define _Quotation	0xe7	// "
#define _Exclamation 	0xe8	// !
#define _Question	0xe9	// ?
#define	_equal		0xea	// =
#define _Mul		0xeb	// X
#define _slash		0xec	// /
#define _UnderBar	0xed	// _
#define _minus		0xee	// -
#define _plus		0xef	// +

#define _Lbar		0xf0	// (
#define _Rbar		0xf1	// )
#define _Scoln		0xf2	// ;
#define _Colon		0xf3	// :
#define _Comma		0xf4	// ,
#define _dot		0xf5	// .
#define _Apst		0xf6	// '

#define	_LimitL		0x7c	// ∞
#define	_LimitR		0x7d	// ∞

#define	_SpeakerOn	0xd4	// {=
#define	_SpeakerSound	0xd5	// {=~
#define	_SpeakerOff	0xd6	// {X

#define _RTriAngle	0x87	// ▶
#define _LTriAngle	0x86	// ◀
#define _UpTriAngle	0xc8	// ▲
#define _DnTriAngle	0xc9	// ▼
#define _4LPrgsBarMax	0x88	// ||||
#define _4LPrgsBar3	0x89	// |||.
#define _4LPrgsBar2	0x8A	// ||.
#define _4LPrgsBar1	0x8B	// |...
#define _4LPrgsBarMin	0x8C	// ....

#define _6LBarLend	0xde	// [
#define _6LBarFull	0xdf	// ||||||
#define _6LBar5		0xe0	// |||||
#define _6LBar4		0xe1	// ||||
#define _6LBar3		0xe2	// |||
#define _6LBar2		0xe3	// ||
#define _6LBar1		0xe4	// |
#define _6LBarNull	0xe5	// 
#define _6LBarRend	0xe6	// ]


#define _3LBarNull	0xdd	// ...
#define _3LBarR1	0xdc	// ..|
#define _3LBarMid	0xdb	// .|.
#define _3LBarFull	0xda	// |||
#define _3LBarL2	0xd9	// ||.
#define _3LBarL1	0xd8	// |..


#define _LRectAngle	0xc6	// [
#define _RRectAngle	0xc7	// ]

#define	_I_S		0x8e
#define	_I_R		0x8f	
#define	_I_G		0x90
#define	_I_B		0x91
#define _I_Ctemp	0x8e

#define	_I_lRGB		0x9e	// Left
#define	_I_lPIP		0x9c	// Left
#define	_I_lEXIT	0xa0	// Left
#define	_I_lOSD		0xa2	// Left
#define	_I_lMONITOR	0xbe	// Left
#define	_I_lTOOLS	0xb0	// Left
#define	_I_lTV		0xd2	// Left
#define	_I_lTV2		0xf7	// Left
#define _I_lSOUND      0xc4	// left	//smpark

 
#define	_I_rRGB		0x9f	// Right
#define	_I_rPIP		0x9d	// Right
#define	_I_rEXIT	0xa1	// Right
#define	_I_rOSD		0xa3	// Right
#define	_I_rMONITOR	0xbf	// Right
#define	_I_rTOOLS	0xb1	// Right
#define	_I_rTV		0xd3	// Right
#define	_I_rTV2		0xf8	// Right
#define _I_rSOUND      0xc5	// right //smpark

#define	_2I_RGB		0x9e, 0x9f
#define	_2I_PIP		0x9c, 0x9d
#define	_2I_EXIT	0xa0, 0xa1
#define	_2I_OSD		0xa2, 0xa3
#define	_2I_MONITOR	0xbe, 0xbf
#define	_2I_TOOLS	0xb0, 0xb1

#define	_2I_PHASE	0x92, 0x93
#define	_2I_COLCK	0x9a, 0x9b
#define	_2I_BRIGHTNESS	0xae, 0xaf
#define	_2I_CONTRAST	0xd0, 0xd1
#define	_2I_SHARPNESS	0xbc, 0xbd
#define	_2I_HPOSITION	0xac, 0xad
#define	_2I_VPOSITION	0xaa, 0xab
#define	_2I_HPOSITION2	0xb2, 0xb3
#define	_2I_VPOSITION2	0xb8, 0xb9
#define	_2I_Color	0x9e, 0x9f

#define	_2I_Transparency	0xca, 0xcb
#define	_2I_Tint	0xa4, 0xa5
#define	_2I_SpMenu	0xc4, 0xc5	//speaker menu icon

#define	_2I_WATCH	0xce, 0xcf	// 시계
#define	_2I_TV		0xd2, 0xd3
#define	_2I_TV2		0xf7, 0xf8
#define	_2I_SIZE	0xa8, 0xa9
#define	_2I_SOURCE	0x96, 0x97
#define	_2I_LANGUAGE	0x00, 0x01	// (0x100,0x101)
#define	_2I_WIDE	0x84, 0x85	//2003-08-19


#define _2I_CenterPosition	0x7e, 0x7f
#define _2I_RightTopPosition	0x85, 0x84
#define _2I_RightBottomPosition	0x85, 0x83
#define _2I_LeftTopPosition	0x82, 0x81
#define _2I_LeftBottomPosition	0x80, 0x81



//old------------------------------
#define _2iCenterPositionL	0x7E
#define _2iCenterPositionR	0x7F
#define _2iRightTopPositionL	0x85
#define _2iRightTopPositionR	0x84

#define _2iRightBottomPositionL	0x84
#define _2iRightBottomPositionR	0x83

#define _2iLeftBottomPositionL	0x80
#define _2iLeftBottomPositionR	0x81

#define _2iLeftTopPositionL	0x82
#define _2iLeftTopPositionR	0x81

#define	_2iColorL	0x9E
#define	_2iColorR	0x9F

#define	_2iPositionL	0xB2
#define	_2iPositionR	0xB3

#define	_2iExitL	0xA0
#define	_2iExitR	0xA1

#define	_2iSetupL	0x96
#define	_2iSetupR	0x97

#define	_2iLockMenuL	0xCA
#define	_2iLockMenuR	0xCB

#define	_2iChannelL	0xF7
#define	_2iChannelR	0xF8

#define	_2iPipL		0xD2
#define	_2iPipR		0xD3

#define _2iBrightnessL	0xCC
#define _2iBrightnessR	0xCD	
//old end-----------------------



//-----------------





//====================< OSD FONT UPPER MEMORY AREA DEFINE >======================
//----------------------< Korean Language Font Define >--------------------------
#define _BK				0x07	//space
#define _EIM			0x08	//임(0x108)
#define	_HWA			0x09	//화(0x109)
#define _MYUN			0x0a    //면(0x10a)
#define _JO				0x0b	//조(0x10b)
#define _JUNG			0x0c	//정(0x10c)
#define _WI				0x0d	//위(0x10d)
#define _CHI			0x0e	//치(0x10e)
#define _SU				0x0f	//수(0x10f)
#define _PYUNG			0x10	//평(0x110)
#define _JIK			0x11	//직(0x111)
#define _PYO			0x12	//표(0x112)
#define _JA				0x13	//자(0x113)
#define _SI				0x14	//시(0x114)
#define _GAN			0x15	//간(0x115)
#define _UN				0x16	//언(0x116)
#define _UA				0x17	//어(0x117)
#define _SUN			0x18	//선(0x118)
#define _MYUNG			0x19	//명(0x119)
#define _DO				0x1a	//도(0x11a)
#define _BALK			0x1b	//밝(0x11b)
#define _GI				0x1c	//기(0x11c)
#define _DONG			0x1d	//동(0x11d)
#define _CHO			0x1e	//초(0x11e)
#define _JU				0x1f	//주(0x11f)
#define _PA				0x20	//파(0x120)
#define _SAEK			0x21	//색(0x121)
#define _ON				0x35	//온(0x135)
#define _SANG			0x22	//상(0x122)
#define _JUCK			0x23	//적(0x123)
#define _CHUNG			0x24	//청(0x124)
#define _SUE			0x25	//스(0x125) 
#define _NOK			0x26	//녹(0x126)
#define _KAM			0x27	//감(0x127)
#define _GER			0x28	//저(0x128)
#define _JANG			0x29	//장(0x129)
#define _TACK			0x2a	//택(0x12a)
#define _GA				0x2b	//가(0x12b)
#define _NA				0x2c	//나(0x12c)
#define _MAE			0x2d	//메(0x12d)
#define _BO				0x2e	//보(0x12e)
#define _NEW			0x2f	//뉴(0x12f)
#define _RO				0x30	//로(0x130)
#define _DEA			0x31	//드(0x131)
#define _MO				0x32	//모(0x132)
#define _DAE			0x33	//대(0x133)
#define _JIE			0x34	//지(0x134)
#define _OON			0x35	//온(0x135)
#define _BEE			0x36	//비(0x136)
#define _DEE			0x37	//디(0x137)
#define _OH				0x38	//오(0x138)
#define _BU				0x39	//부(0x139)
#define _NUNG			0x3a	//능(0x13a)
#define _TOU			0x3b	//투(0x13b)
#define _BAN			0x3c	//반(0x13c)
#define _HOO			0x3d	//호(0x13d)
#define _SHIN			0x3e	//신(0x13e)
#define _EIP			0x3f	//입(0x13f)
#define _YERK			0x40	//력(0x140)
#define _AEE			0x41	//에(0x141)
#define _TA				0x42	//타(0x142)
// 20030823
#define _ARM			0x43	//암(0x143)
#define _NONG			0x44	//농(0x143)
#define _GOOK			0x45	//국(0x143)
#define _BAEK			0x46	//백(0x143)	// * 
#define _SEOL			0x47	//설(0x143)
#define _BI				0x48	//비(0x143)	// *
#define _CHAE			0x49	//채(0x143)
#define _NULL			0x4A	//널(0x143)
#define _KEE			0x4B	//크(0x143)	// *
#define _MIL			0x4C	//밀(0x143)
#define _PYEON			0x4D	//편(0x143)
#define _JIP			0x4E	//집(0x143)
#define _EUM			0x4F	//음

#define _P1			0x85
#define _I1			0x86
#define _D1			0x87
#define _O1			0x88
#define _S1			0x89

#define _JAK			0x8A 	// 작
#define _GO			0x8B	//   

#define _JER			0xB1	// 저 
#define _AHN			0xB2	// 안
#define _TE			0xB3	// 테
//#define _NA			0xB4	// 나
//#define _TA			0xB5	// 타
#define _YI			0xB6	// 이
#define _MER			0xB7	// 머 
#define _HWANG			0xB8	// 향
#define _YULL			0xB9	// 율 

#define	_TEMPkor		0x08,0x06	//임시


//-----------------------< Korean Font Define End >--------------------------

#if defined (USE_NTSCtuner)
//----------------------< Japanese Language Font Define Start >--------------------------
//---------------------------< Display adjust menu character >---------------------------
#define J_DISADJ			0xa2,0xa3,0x6a,0x6b,_BK,0x7d,0x7e,0x7f
#define	J_BRIGHT			0x50,0x51,0x52			//(0x150 ~ 0x152)
#define J_CONTRAST			0x53,0x54,0x55,0x56,0x57,0x55	//(0x153 ~ 0x157)
#define J_PHASE				0x58,0x59,0x5a			//(0x158 ~ 0x15a)
#define J_CLOCK				0x5b,0x5c,0x5d,0x5b		//(0x15b ~ 0x15d)
#define J_HPOS				0x5e,0x5f,0x60,0x61		//(0x15e ~ 0x161)
#define J_VPOS				0x62,0x63,0x60,0x61		//(0x162 ~ 0x163)
#define J_FACTORY			0x64,0x58,0x65,0x66,0x55	//(0x164 ~ 0x166)
#define J_AUTO				0x68,0x69,0x6a,0x6b		//(0x168 ~ 0x16b)
#define J_SHARPNESS			0xd3,0xd4,0x6f,0xd0,0xce,0x57
#define J_COLOR				0x71,0xda,0xdd,0x52	
#define J_TINT				0x71,0xdb,0xdc
#define J_SPC				0xa2,0xa3,0x6e,0x6f,0x70


#define J_ADJUST				0x6a,0x6b
#define J_POSITION			0x60,0x61
#define J_RETURN				0xd2,0x60,0x7d,0x7e,0x7f,0x6f

#define J_DOS_MODE			_D1,_O1,_S1,_BK,0x6e,0x6f,0x70

#define J_AUTO_TUNE			0x68,0x69,0x7b,0xc3
#define J_FACTORY_DEFAULT	0xde,0xdf,0x77,0x9b,0xc3

//----------------------------<MISC adjust menu character >-------------------------------
#define J_MISC				0x6a,0x6b,_BK,0x7d,0x7e,0x7f
#define J_MODE				0x6e,0x6f,0x70			//(0x16e ~ 0x170)
//dithering --> english used
#define J_REDGAIN			0x74,0x71,0x6a,0x6b		//(0x174,0x171)
#define J_GREENGAIN			0x75,0x71,0x6a,0x6b		//(0x175)
#define J_BLUEGAIN			0x76,0x71,0x6a,0x6b		//(0x176)
#define	J_COLORTEMP			0x71,0x72,0x73
#define J_WHITEBAL			0x74,0x75,0x76,_BK,0x67,0x56,0x54,0x57
//----------------------------<OSD adjust menu character >--------------------------------
#define J_OSDADJ				0x7d,0x7e,0x7f
#define J_OSDHPOS			0x5e,0x5f,0x60,0x61
#define J_OSDVPOS			0x62,0x63,0x60,0x61
#define J_OSDTIME			0x81,0x82,0x83
#define J_OSDTRANS			0x84,0xac,0x50
#define J_LANG				0x6c,0x6d
// added by smpark 20030918

// PIP
#define J_PIP_ENABLE			0x85,0x86,0x85,_BK,0x69,0xbf
#define J_PIP_SOURCE			0x85,0x86,0x85,_BK,0xbb,0xbc
#define J_PIP_SIZE			0x85,0x86,0x85,_BK,0xbd,0x82,0x5a,0x6a,0x6b
#define J_PIP_HPOS			0x85,0x86,0x85,_BK,0x5e,0x5f,0x60,0x61
#define J_PIP_VPOS			0x85,0x86,0x85,_BK,0x62,0x63,0x60,0x61
#define J_PIP_ASPECT			0x85,0x86,0x85,_BK,0x93,0xbe
#define J_PIP_TRANS			0x85,0x86,0x85,_BK,0x84,0xac,0x50
 
// SOUND
#define J_TREBLE				0xca,0xcb,0x6a,0x6b
#define J_BASS				0xcc,0xcb,0x6a,0x6b
#define J_LOUDNESS			0x56,0xcd,0x70,0xce,0x57
#define J_SSC				0xcb,0xcf,0x6a,0x6b

// TV
#define J_COUNTRY			0xc0,0xc1,0xc2,0xc3
#define J_AUTO_SETUP			0x68,0x69,0xc2,0xc3
#define J_CHANNEL_EDIT		0xd5,0xd4,0x54,0xce,0x66,0xd6,0xd7,0xd8		// *
#define J_ANTENA_INPUT		0x64,0x54,0xc5,0xc6,0xbb,0xbc				// *
#define J_FINE_TUNE			0xd9,0x6a,0x6b								// *

// TOOL
#define J_BLUE_SCREEN		0x76,0x71,0xa2,0xa3
#define J_WIDE				0xc8,0x82,0x70,0x57,0x5b,0xc9,0x6f,0x54
#define J_SLEEP				0x57,0xc9,0x6f,0xd0,0x81,0x82,0xd1,0x6f
//--------------------------------------< OSD EXIT >--------------------------------------
//-----------------------< Japanese Language Font Define END >----------------------------
#endif

//-----------------------< Chinese Language Font Define Start >----------------------------------------------
//---------------------------< Display adjust menu character >--------------------------------------
//#define CH_DISADJ			0x8c,0x8d,0x8e,0x8f,0x9c,0x9d,0x9f,0x9e,0xa0,0xa1,0xa2,0xa3 
#define CH_DISADJ			0x8e,0x8f
#define CH_BRIGHT			0x90,0x91
#define CH_CONTRAST			0x92,0x93,0x91
#define CH_HPOS				0x5e,0x5f,0x60,0x94	//수평위치
#define CH_VPOS				0x5e,0x5f,0x60,0x94	//수직위치
#define CH_FACTORY			0x9b,0x96,0x97,0x98,0x99
#define CH_AUTO				0x68,0x9a,0x8e,0x8f

//----------------------------< MISC adjust menu character >--------------------------------
#define CH_MISC				0x8e,0x8f,0x9c,0x9d,0x9f,0x9e,0xa0,0xa1,0xa2,0xa3 //MISC + CH_MISC
//#define CH_MODE				0xa4,0xa5					  //DOS + CH_MODE
#define CH_DITHER			0xa6,0x9a
#define CH_REDGAIN			0xa7,0xa9,0x8e,0x8f
#define CH_GREENGAIN		0xa8,0xa9,0x8e,0x8f
#define CH_BLUEGAIN			0xaa,0xa9,0x8e,0x8f
#define CH_COLORTEMP		0xa9,0xab
//white_balance -->english used
//----------------------------< OSD adjust menu character >---------------------------------
#define CH_OSDADJ			0x8e,0x8f,0x9c,0x9d,0x9f,0x9e,0xa0,0xa1,0xa2,0xa3 //OSD + CH_OSDADJ
#define CH_OSDHPOS			0x5e,0x5f,0x60,0x94				  //OSD + CH_OSDHPOS
#define CH_OSDVPOS			0x5e,0x5f,0x60,0x94				  //OSD + CH_OSDVPOS
//#define CH_OSDTIME --> english used
#define CH_OSDTRANS			0xac,0x50,0x91
#define CH_LANG				0xae,0x6c,0x9c,0x9d
//------------------------------------------------------------------------------------------
#define	CH_SELECT			0x88,_BK,_BK,_BK,0x89			//임시 중국어폰트(글자) 적용//2004-01-07
#define	CH_START			0x8a,_BK,_BK,_BK,0x8b
#define	CH_ON				_BK,0x8a
#define CH_OFF				_BK,0x85
#define CH_MINUTE			0x80			//분
#define	CH_SEC				_BK,0x5a,_BK	//초
#define	CH_CHINA			0x81,_BK,_BK,_BK,0x82	//중문
#define	CH_CHINA_CTY		0x81,_BK,_BK,_BK,0xc0	//중국
#define	CH_FULL				0xD4,0x11	
#define CH_NORMAL			0x51,_BK,_BK,_BK,0x52
#define	CH_DYNAMIC			0x9a,_BK,_BK,_BK,0x53	
#define	CH_CINEMA			0x54,_BK,_BK,_BK,0x55
#define	CH_USER				0x56,_BK,_BK,_BK,0x57
#define	CH_MUSIC			0x58,_BK,_BK,_BK,0x59
#define	CH_TOP				0x5b		//상
#define	CH_BOTTOM			0x67		//하
#define	CH_MIDDLE			0x81		//중
#define	CH_LARGE			0x64		//대
#define	CH_SMALL			0x65		//소
#define	CH_LEFT             0x5c		//좌 左
#define	CH_RIGHT            0x5d		//우 右
#define	CH_MODE				0x70,0xa5		//模式 

//-------------------------------< OSD EXIT character >-------------------------------------
#define CH_EXIT				0xaf,0xb0

//------------------------< Chinese Language Font Define END >-----------------------------------------------
