#ifndef _MyDef_H
#define  _MyDef_H

typedef bit             Bit;
typedef bit             Bool;
typedef unsigned char   Byte;
typedef unsigned short  Word;
typedef code            Code;

#define TRUE        ((Bool)1)
#define FALSE       ((Bool)0)

#define BIT_0	0x01
#define BIT_1	0x02
#define BIT_2	0x04
#define BIT_3	0x08
#define BIT_4	0x10
#define BIT_5	0x20
#define BIT_6	0x40
#define BIT_7	0x80

//#define ModelName				"NT68563E"
#define ModelName				"DNPSYS  "
#define Version 1	
#define Reversion 0	
#define Build	1
#define Year	2005
#define Month	8
#define Date	10
#define ModeNum 90
#define UserModeSt 76//61	// +jwshin 061002	
#define SAVE_DDC_TIME	100
#define SAVE_FUNC_TIME  10
#define BURN_IN_TIME 200
#define POWER_TIME	7000
#define MUTE_DELAY_TIME 50
#define RES_TABLE_COUNT	15
#define MAX_COLOR_TEMP 	4
#define MAX_LANGUAGE 9

//show video & message
#define	H_Min 140//240//290	//KHz
//#define	H_Max 830	//KHz
#define	H_Max 1000	//KHz
#define	V_Min 490	//Hz
#define	V_Max 780	//Hz
//#define	V_Max 860	//Hz
//mute screen
#define H_LO 270
#define H_HI 940
#define V_LO 450	
#define V_HI 860
//#define P_Max 1600	//MHz
#define P_Max 2050	//MHz

#define SCALER_ADDR		0xB0
#define Scaler_Addr 		0xB0
#define NOVATEK_Addr	0x40	// for Utility Alignment command
#define TW990x_Addr		0x8A
#define TDA7440D_Addr	0x88

//audio control subAddress lists
#define A_InputSel	0x00
#define A_InputGain	0x01
#define A_Volume	0x02
#define A_Bass		0x03
#define A_Treble	0x05
#define A_AttR		0x06
#define A_AttL		0x07

//KeyPad
#define vkPOWER		0x01
#define vkMENU		0x08
#define vkSOURCE	0x02
#define vkLEFT		0x9a		// +jwshin 061025
#define vkRIGHT		0x9b		// +jwshin 061025
#define vkVALUP		0x10
#define vkVADOWN	0x20
#define vkAUTO		0x40
#define vkMONSEL	0x93
#define vVOLUME		0x04

#define vIR_POWER		0x90
#define vIR_MENU		0x92
#define vIR_SELECT		0x91
#define vIR_LEFT		0xa1
#define vIR_RIGHT		0xa0
#define vIR_UP			0x9c
#define vIR_DOWN		0x9d
#define vIR_MUTE		0x8f
#define vIR_1			0x81
#define vIR_2			0x82
#define vIR_3			0x83
#define vIR_4			0x84
#define vIR_5			0x85
#define vIR_6			0x86
#define vIR_7			0x87
#define vIR_8			0x88
#define vIR_9			0x89
#define vIR_0			0x80
#define vIR_10			0x8a
#define vIR_11			0x8b
#define vIR_12			0x8c
#define vIR_CHSearch		0x9e
#define vIR_Analog		0x95
#define vIR_DVI			0x96
#define vIR_SVideo		0x98
#define vIR_Video		0x97
#define vIR_TV			0x99



#define KeyStabTime 50		// 50ms
#define KeyHoldTime 100		// 1 sec.
#define KeyRepeatTime 0		// 0.08 sec.
#define KeyMenuTime 20
#define SourceKeyTime 5000		//0.08 sec.
// ADC PLL
#define AnalogPLL 0
#define DigitalPLL 1

#define ADC_PLL DigitalPLL
//DVI
#define HVmode 0
#define DEmode 1

#define DVImode DEmode

//Contrast control
#define BackEndGain 0
#define sRGBGain 1

#define ContrastBlock sRGBGain

#define AutoClock_Step 7   //rev3

//Auto Color control
#define GaugeGain 0
#define AutoGain 1

#define AUTO_COLOR GaugeGain
//Panel power active control
#define Low 0
#define High 1
#define PanelPowerActive High

//debug
#define PRINT_MESSAGE 1

//CONTROL DEFINE ------------
//analog
#define pBRIGHTNESS		0 	
#define pCONTRAST 		1	
#define pPHASE		 	2
#define pCLOCK			3
#define pBACKLIGHT		4
#define pHPOSITION 		5
#define pVPOSITION		6
#define pOSDHPOSITION	7
#define pOSDVPOSITION	8
#define pOSDTIMER		9
#define pSATURATION		10
#define pTINT			11
#define pRCOLOR			12
#define pGCOLOR			13
#define pBCOLOR			14
#define pCOLORTEMP		15
#define pLANGUAGE		16
#define pSHARPNESS		17
#define pRADC			18
#define pGADC			19
#define pBADC			20
#define pVOLUME			21
#define pTRANSOSD		22
#define pVIDEOSOURCE	23
#define pBACKLIGHT2		24
#define pVCMVOL			25
#define pROFFSET		26
#define pGOFFSET		27
#define pBOFFSET		28
#define pContMax			29
#define pContMin			30
#define pBrigMax			31
#define pBrigMin			32
#define pLIGHTCONTRAST	33
#define pLIGHTBRIGHT	34
#define pLIGHTHSTART	35
#define pLIGHTHWIDTH	36
#define pLIGHTVSTART	37
#define pLIGHTVHIGHT	38
#define pCHFINETUNE		39
#define pTreble			40
#define pBass			41

//digital
#define pFACTMENU		pBass+1
#define pMUTE			pFACTMENU+1
#define pAUTOSETTING	pMUTE+1
#define pRECALL			pAUTOSETTING+1
#define pAUTOCOLOR		pRECALL+1
#define pAUTOADJUST	pAUTOCOLOR+1
#define pTEXTMODE		pAUTOADJUST+1
#define pLIGHTEN		pTEXTMODE+1
#define pSCALERMODE	pLIGHTEN+1
#define pINFORMATION	pSCALERMODE+1
#define pEXIT			pINFORMATION+1
#define pOUTOFRANGE	pEXIT+1
#define pNOSIGNAL		pOUTOFRANGE+1
#define pEEPROMINIT		pNOSIGNAL+1
//#define pFACAUTOSET	53		//LO_CS 0309

#define pCHSEARCH		pEEPROMINIT+1
#define pCHEDIT			pCHSEARCH+1
//#define pCHFINETUNE	55
#define pINPUT			pCHEDIT+1
#define pTVFUNCTION		pINPUT+1

//For Vchip
#define pCAPTION              pTVFUNCTION+1
#define pMPAARATING       pCAPTION+1
#define pTVRATING		pMPAARATING+1
#define pViolence_R          pTVRATING+1
#define pSexual_R		pViolence_R+1
#define pLanguage_R		pSexual_R+1
#define pDialog_R		pLanguage_R+1

//OSD OP CODE DEFINE ----------
#define oVOID			0
#define oUPDATEALL		1
#define oUPDATE			2
#define oCHECKED		3
#define oINCVAL			4
#define oDECVAL			5
#define oINCFUNC		6
#define oDECFUNC		7
#define oINCPAGE		8
#define oDECPAGE		9
#define oENTER			10
#define oRETURN			11

#define cMPAA_G		1
#define cMPAA_PG	2
#define cMPAA_PG13	3
#define cMPAA_R		4
#define cMPAA_NC17	5
#define cMPAA_X		6
#define cMPAA_NR	7
#define cTV_Y		1
#define cTV_Y7		2
#define cTV_Y7_FV	3
#define cTV_G		4
#define cTV_PG		5
#define cTV_14		6
#define cTV_MA		7

enum {
	CH_CCIR,
	CH_FRA,
	CH_ITA,
	CH_GBR,
	CH_AUS,
	CH_NZL,
	CH_RUS,
	CH_USA,
	CH_JPN
};	
#define NTSC 0
#define PAL 1
#define SECAM 2

#define cIR_Dummy		0
#define cIR_START 		1
#define cIR_COMMAND	2
#define cIR_DATA		3

#define Disp_resolution		1		// +jwshin 061002
#endif
