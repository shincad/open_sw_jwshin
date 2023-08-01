/*********************************************************************
  (c) copyright	ED-Tech	Company	2002   ALL RIGHTS RESERVED
 *********************************************************************
	EMH1A Demonstration	Program(Inno version)
	LG LM171W01-B3 WXGA	panel
	Spec Ver. 0.1(Apr. 02,2002)
 *********************************************************************/

#define		GAMMA_LINEAR
//#define		GAMMA_1
//#define		GAMMA_4

#define		PanelWidth					1280
#define		PanelHeight					768

#define		PanelDualData				0x00		// Data	output signal is single	or dual
#define		PanelDataSwap				SinglePanelDataSwap	//it's board option!,move to "spec.h"
#define		PanelNegativeHS				0xff		// Hsync Polarity is Neg or	Pog
#define		PanelNegativeVS				0xff		// Vsync Polarity is Neg or	Pog

#define		PanelDepth6bit				0x00		// determine 6bit or 8bit panel
#define		PanelDitherEnable			0x00

#define		PanelMinHTotal				1344  //1420  //1344		//1312//set Panel	min	Htotal size
#define		PanelMinVTotal				774			//773//set Panel	Vtotal size

//#define	PanelMaxHTotal				2047		// Maxium Htotal as	possible input
//#define	PanelMaxHTotal				1720		// Maxium Htotal as	possible input
//#define	PanelMaxVTotal				1330 //1062		// Maxium Vtotal as	possible input
//#define	PanelMaxVTotal				1600 //1062		// Maxium Vtotal as	possible input

// hs width	= PanelHSWidth *4 -2	,minimum is	6
#define		PanelHSWidth				10
// OVHS(HS + back porch) = PanelHBackPorch+1
// if dual pixel mode, OVHS	(PanelHBackPorch+1)	& (~1) => even number!
// minimum PanelHBackPorch is 4
#define		PanelHBackPorch				10		//&&&&must even	value for odd active start(for use bkg match)

#define		PanelVSWidth				1		//2
#define		PanelVBackPorch				1   //0		//2

#define		PanelFMHSWidth				PanelHSWidth
#define		PanelFMHBackPorch			PanelHBackPorch	//if memory	mode,OHActiveStart min is 15.
#define		PanelFMVSWidth				PanelVSWidth	//1
#define		PanelFMVBackPorch			(PanelVBackPorch+2)	//0

//#define	PanelHSyncWidth				8  //16
//#define	PanelHSyncBackPorch			7  //7//31
//#define	PanelVSyncWidth				2
//#define	PanelVSyncBackPorch			3
//
////[t22]
//#define	FM_PanelHSyncBackPorch		10	//7//31
//#define	FM_PanelVSyncWidth			3
//#define	FM_PanelVSyncBackPorch		10
////[t22]

#define		PanelVSHSDisplace			0
#define		PanelDClkPhase				0x1			// range : 0 ~ 3		// Dclk1 phase

// Out Of Range	Control	Parameter
#define		PanelMaxVFrequency			86		// hz
//#define		PanelMaxDClkFrequency		80		// Mhz
//#define		PanelMaxDClk			(BYTE)((float)PanelHeight /	(float)IVAW) * ((float)Now_hf/100.0) * ((float)PanelMinHTotal/100.0)

// Power Management	Parameter
#define		PanelPowerManStep0			2	// 1 = 10mS
#define		PanelPowerManStep1			10	// T1
#define		PanelPowerManStep2			1	// T2
#define		PanelPowerManStep3			1	// T3
#define		PanelMinOffDuration			100		// Minimum off time, in	(10msec	periods)

//Panel	resolution Parameter
//#define	PanelSxga
#define		PanelXga
//#define	PanelSvga
//#define	PanelVga


//#define DEFAULT_PCFM

