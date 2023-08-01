#ifndef __PANEL_H__
    #define __PANEL_H__

	#define TCON_TO_RSDS 	0
	#define TCON_TO_TTL		1
	#define LVDS_TO_TCON	2
	#define TTL_TO_TCON		3

    #define AU_L150X2M_1			0	// 0: 2 pixel/clk, 6 bit
    #define CMO_M150X3_T05			1   // 1: 2 pixel/clk, 6 bit
    #define HannStar_HSD150MX49_A	2   // 2: 2 pixel/clk, 8 bit
    #define HannStar_HSD150MX41_A	3   // 3: 2 pixel/clk, 6 bit
    #define HannStar_HSD150MX12_A	4   // 4: 1 pixel/clk, 8 bit
    #define CPT_CLAA150XG01			5	// 5: 2 pixel/clk, 8 bit
    #define SINAI43140CBx_1			6	// 6: 2 pixel/clk, 6 bit
	#define SINAI38951CBx			7	// 7: 2 pixel/clk, 6 bit
    #define SINAI38140CBx			8	// 8: 1 pixel/clk, 8 bit
    #define Sharp_LQ150X1DG51		9	// 9: 2 pixel/clk, 6 bit
    #define CMO_M170E4_L01			10	// 10: 2 Pixel/clk, 8 bit
    #define NL6448BC33_46			11	// 11: 1 Pixel/clk, 6 bit
    #define AU_L170EN05				12	// 10: 2 Pixel/clk, 8 bit
    #define AU_M150XN05_1			13	// 13: 2 pixel/clk, 8 bit
    #define CMO_M150X2_T05			14  // 14: 2 pixel/clk, 6 bit
    #define QD170E1 				15	// 15: 2 Pixel/clk, 8 bit
    #define Samsung_LTM170E4_L01	16	// 16: 2 Pixel/clk, 8 bit
    #define QD170ER01 				17	// 17: 2 Pixel/clk, 8 bit
    #define HyundaiHT17E12_100		18	// 18: 2 Pixel/clk, 6 bit
	#define AU_M150XN04_1			19	// 19: 2 Pixel/clk, 6 bit
	#define FLC48SXC8V_10			20	// 20: 
	#define CMO_M170ES05			21	// 21: 2 Pixel/clk, 6 bit
	#define Samsung_LTM213U4_L01	22	//22: 2 Pixel/clk, 8 bit
	#define LP_LM170E01				23	//23: 2 Pixel/clk, 6 bit
	#define FUJ_FLC43XWC8V			24	//24: 1 pixel/clk, 8bit
	#define AU_L170ES05				25	//25: 2 Pixel/clk, 6 bit
	#define AUO_M201EW01 			26	//26: 2 Pixel/clk, 8 bit
	#define Samsung_LTM150XH_L04	27	//27: 1 Pixel/clk, 6 bit
	#define Sharp_FG170M1LA04		28	//28: 2 Pixel/clk, 6 bit
	#define LP_LM201U4				29  //29 : 2pixel/clk, 8bit UXGA
	#define LP_LC260WX2 			30	//30 : 1Pixwl/clk, 8bit
	#define LP_LC260W01				31	//30 : 1Pixwl/clk, 8bit
    //**************************************************************
    //              S E L E C T E D   P A N E L
    //**************************************************************
//	#define PANEL AU_L150X2M_1
//	#define PANEL CMO_M150X3_T05
//	#define PANEL CMO_M150X2_T05
//	#define PANEL HannStar_HSD150MX49_A
//	#define PANEL HannStar_HSD150MX41_A
//	#define PANEL HannStar_HSD150MX12_A
//	#define PANEL CPT_CLAA150XG01
//	#define PANEL SINAI43140CBx_1
//	#define PANEL SINAI38951CBx
//	#define PANEL SINAI38140CBx
//	#define PANEL Sharp_LQ150X1DG51
//	#define PANEL CMO_M170E4_L01
//	#define PANEL NL6448BC33_46
//	#define PANEL AU_L170EN05
//	#define PANEL AU_M150XN05_1
#ifdef X17	//defined in Keil-c project
//	#define PANEL CMO_M170E4_L01
//	#define PANEL QD170E1
//	#define PANEL Samsung_LTM170E4_L01
//  #define PANEL LP_LC260WX2	
//	#define PANEL AU_L170EN05
	#define PANEL LP_LM170E01
//	#define PANEL CMO_M170ES05
//	#define PANEL AU_L170ES05
//#define PANEL LP_LC260W01

#endif
//	#define PANEL Samsung_LTM170E4_L01
//	#define PANEL QD170ER01
//	#define PANEL HyundaiHT17E12_100
#ifdef X15	//defined in Keil-c project
	//#define PANEL AU_M150XN04_1			//TopFly 15" panel
	//#define PANEL FUJ_FLC43XWC8V 		//TopFly 15" panel
	//#define PANEL Samsung_LTM150XH_L04
	//#define PANEL LP_LC260WX2
	#define PANEL LP_LC260W01
#endif
#ifdef X19
	#define PANEL FLC48SXC8V_10
#endif
#ifdef X21
	//#define PANEL Samsung_LTM213U4_L01
	//#define PANEL AUO_M201EW01
	//#define PANEL Sharp_FG170M1LA04
	#define PANEL LP_LM201U4
#endif

    //**************************************************************
    //            P A N E L   D E F I N I T I O N S
    //**************************************************************
#if PANEL == LP_LC260W01

	#define PanelName				"LP_LC260W01"
	#define PanelXga					0
	#define PanelSxga				1
	#define PanelUxga				0
	#define PanelTwoPixelPerClk 	0		// Double pixels output 
	#define PanelDepth				8
	#define PanelSync_DE			0		//0=H/V 1=DE

	#define PanelWidth				1280
	#define PanelHeight 				768

	#define PanelMaxVFreq			63		// Hz
	#define PanelMinVFreq			47		// Hz
	#define PanelMaxHFreq			50000	 // Hz

	#define PanelMaxPClk				82000	 // KHz

	#define PanelMinHTotal			1328//1468
	#define PanelMaxHTotal			1648//1776
	#define PanelMinHSyncWidth		8
	#define PanelMinHSyncBackPorch	12//16//24
	#define PanelHSyncStart 			PanelMinHTotal - PanelMinHSyncWidth - PanelMinHSyncBackPorch
	#define PanelHSyncEnd			PanelHSyncStart + PanelMinHSyncWidth
	#define PanelHActiveStart			PanelMinHSyncBackPorch + PanelMinHSyncWidth

	#define PanelMaxVTotal			810//1063//2047
	#define PanelTypVTotal			810//790
	#define PanelMinVTotal			775
	#define PanelMinVSyncWidth		2
	#define PanelMinVSyncBackPorch	3//4
	#define PanelVSyncStart 		PanelTypVTotal - PanelMinVSyncWidth - PanelMinVSyncBackPorch
	#define PanelVSyncEnd			PanelVSyncStart + PanelMinVSyncWidth
	#define PanelVActiveStart		PanelMinVSyncBackPorch + PanelMinVSyncWidth

	#define FreeRunH_Freq			64000		//64KHz
	#define FreeRunV_Freq			60			//60 Hz
	#define FreeRunVtotal			1240		//1066 line
		//#define Use_TCON				0
	#define PanelInterface			LVDS_TO_TCON
	#define PanelShortHsync 		0
	#define Panel_Invert_DVS		0xff
	#define Panel_Invert_DHS		0xff
	#define Panel_Invert_DCLK		0x00
	#define Panel_Invert_DEN		0x00
	#define PanelPadDrive			0x0333

	#define Panel_Spread_Spect_En	0xff	// 0xff : enable spectrum
												// 0x00 : disable spectrum
	#define PanelSpreadSpectrumCtrl 0x00
		// Value for Spread_Spectrum_Control register
		// 0x00: 0.097% ... 0x07: 12.5%

		// Panel dething mode
	#define PanelDethMode			0x31

		// define panel timing. word constant used to program registers 0xd8 and 0xd9 during power up and power down
	#define PowerUpPanelTiming		1		// 1 ms
	#define PowerUpInvTiming		250 	// 250 ms
	#define PowerDownPanelTiming	1		// 1 ms
	#define PowerDownInvTiming		250 	// 250 ms

	#define yuv2rgbXsRGB2rgb{	\
			{  0x12A1,	0x0000,  0x1989 },	\
			{  0x12A1, -0x0644, -0x0D01 },	\
			{  0x12A1,	0x2046,  0x0000 }	\
		}

#endif	

#if PANEL == LP_LC260WX2

	#define PanelName				"LP_LC260WX2"
	#define PanelXga					0
	#define PanelSxga				1
	#define PanelUxga				0
	#define PanelTwoPixelPerClk 	0		// Double pixels output 
	#define PanelDepth				8
	#define PanelSync_DE			0		//0=H/V 1=DE

	#define PanelWidth				1366
	#define PanelHeight 				768

	#define PanelMaxVFreq			63		// Hz
	#define PanelMinVFreq			47		// Hz
	#define PanelMaxHFreq			50000	 // Hz

	#define PanelMaxPClk				80000	 // KHz

	#define PanelMinHTotal			1468
	#define PanelMaxHTotal			1776
	#define PanelMinHSyncWidth		8
	#define PanelMinHSyncBackPorch	24
	#define PanelHSyncStart 			PanelMinHTotal - PanelMinHSyncWidth - PanelMinHSyncBackPorch
	#define PanelHSyncEnd			PanelHSyncStart + PanelMinHSyncWidth
	#define PanelHActiveStart			PanelMinHSyncBackPorch + PanelMinHSyncWidth

	#define PanelMaxVTotal			1063//2047
	#define PanelTypVTotal			790
	#define PanelMinVTotal			775
	#define PanelMinVSyncWidth		2
	#define PanelMinVSyncBackPorch	4
	#define PanelVSyncStart 		PanelTypVTotal - PanelMinVSyncWidth - PanelMinVSyncBackPorch
	#define PanelVSyncEnd			PanelVSyncStart + PanelMinVSyncWidth
	#define PanelVActiveStart		PanelMinVSyncBackPorch + PanelMinVSyncWidth

	#define FreeRunH_Freq			64000		//64KHz
	#define FreeRunV_Freq			60			//60 Hz
	#define FreeRunVtotal			1240		//1066 line
		//#define Use_TCON				0
	#define PanelInterface			LVDS_TO_TCON
	#define PanelShortHsync 		0
	#define Panel_Invert_DVS		0xff
	#define Panel_Invert_DHS		0xff
	#define Panel_Invert_DCLK		0x00
	#define Panel_Invert_DEN		0x00
	#define PanelPadDrive			0x0333

	#define Panel_Spread_Spect_En	0xff	// 0xff : enable spectrum
												// 0x00 : disable spectrum
	#define PanelSpreadSpectrumCtrl 0x00
		// Value for Spread_Spectrum_Control register
		// 0x00: 0.097% ... 0x07: 12.5%

		// Panel dething mode
	#define PanelDethMode			0x31

		// define panel timing. word constant used to program registers 0xd8 and 0xd9 during power up and power down
	#define PowerUpPanelTiming		1		// 1 ms
	#define PowerUpInvTiming		250 	// 250 ms
	#define PowerDownPanelTiming	1		// 1 ms
	#define PowerDownInvTiming		250 	// 250 ms

	#define yuv2rgbXsRGB2rgb{	\
			{  0x12A1,	0x0000,  0x1989 },	\
			{  0x12A1, -0x0644, -0x0D01 },	\
			{  0x12A1,	0x2046,  0x0000 }	\
		}

#endif		

#if PANEL == LP_LM201U4

	#define PanelName				"LP_LM201U4\r\n"
	#define PanelXga				0
	#define PanelSxga				0
	#define PanelUxga				1
	#define PanelTwoPixelPerClk 	1		// Double pixels output 
	#define PanelDepth				8
	#define PanelSync_DE				0		//0=H/V 1=DE

	#define PanelWidth				1600
	#define PanelHeight 			1200

	#define PanelMaxVFreq			61		// Hz
	#define PanelMinVFreq			59		// Hz
	#define PanelMaxHFreq			136000	 // Hz

	#define PanelMaxPClk			190000	 // KHz

	#define PanelMinHTotal			1664
	#define PanelMaxHTotal			1736
	#define PanelMinHSyncWidth		16
	#define PanelMinHSyncBackPorch		16
	#define PanelHSyncStart 		PanelMinHTotal - PanelMinHSyncWidth - PanelMinHSyncBackPorch
	#define PanelHSyncEnd			PanelHSyncStart + PanelMinHSyncWidth
	#define PanelHActiveStart		PanelMinHSyncBackPorch + PanelMinHSyncWidth

	#define PanelMaxVTotal			1240//2047
	#define PanelTypVTotal			1240
	#define PanelMinVTotal			1230
	#define PanelMinVSyncWidth		3
	#define PanelMinVSyncBackPorch	25
	#define PanelVSyncStart 		PanelTypVTotal - PanelMinVSyncWidth - PanelMinVSyncBackPorch
	#define PanelVSyncEnd			PanelVSyncStart + PanelMinVSyncWidth
	#define PanelVActiveStart		PanelMinVSyncBackPorch + PanelMinVSyncWidth

	#define FreeRunH_Freq			64000		//64KHz
	#define FreeRunV_Freq			60			//60 Hz
	#define FreeRunVtotal			1240		//1066 line
		//#define Use_TCON 				0
	#define PanelInterface			LVDS_TO_TCON
	#define PanelShortHsync 		0
	#define Panel_Invert_DVS		0xff
	#define Panel_Invert_DHS		0xff
	#define Panel_Invert_DCLK		0x00
	#define Panel_Invert_DEN		0x00
	#define PanelPadDrive			0x0333

	#define Panel_Spread_Spect_En	0xff	// 0xff : enable spectrum
												// 0x00 : disable spectrum
	#define PanelSpreadSpectrumCtrl 0x00
		// Value for Spread_Spectrum_Control register
		// 0x00: 0.097% ... 0x07: 12.5%

		// Panel dething mode
	#define PanelDethMode			0x31

		// define panel timing. word constant used to program registers 0xd8 and 0xd9 during power up and power down
	#define PowerUpPanelTiming		1		// 1 ms
	#define PowerUpInvTiming		250 	// 250 ms
	#define PowerDownPanelTiming	1		// 1 ms
	#define PowerDownInvTiming		250 	// 250 ms

	#define yuv2rgbXsRGB2rgb{	\
			{  0x12A1,  0x0000,  0x1989 },	\
			{  0x12A1, -0x0644, -0x0D01 },	\
			{  0x12A1,  0x2046,  0x0000 }	\
		}

#endif		


    #if PANEL == AU_L150X2M_1

		#define PanelName				"AU_L150X2M_1\r\n"
		#define PanelXga                1
		#define PanelSxga               0
		#define PanelUxga               0
		#define PanelTwoPixelPerClk     1       // Double pixels output 
		#define PanelDepth              6
		#define PanelSync_DE			0

		#define PanelWidth				1024
		#define PanelHeight				768

		#define PanelMaxVFreq           75      // Hz
		#define PanelMinVFreq           50      // Hz
		#define PanelMaxHFreq           60000   // Hz

		#define PanelMaxPClk            80000   // KHz

		#define PanelMinHTotal          1200
		#define PanelMaxHTotal          1800
		#define PanelMinHSyncWidth      80
		#define PanelMinHSyncBackPorch  80
		#define PanelHSyncStart			PanelMinHTotal - PanelMinHSyncWidth - PanelMinHSyncBackPorch
		#define PanelHSyncEnd			PanelHSyncStart + PanelMinHSyncWidth
		#define PanelHActiveStart		PanelMinHSyncBackPorch + PanelMinHSyncWidth

		#define PanelMaxVTotal			960
		#define PanelTypVTotal			800
		#define PanelMinVTotal			780
		#define PanelMinVSyncWidth      3
		#define PanelMinVSyncBackPorch  7
		#define PanelVSyncStart			PanelTypVTotal - PanelMinVSyncWidth - PanelMinVSyncBackPorch
		#define PanelVSyncEnd			PanelVSyncStart + PanelMinVSyncWidth
		#define PanelVActiveStart		PanelMinVSyncBackPorch + PanelMinVSyncWidth

		#define FreeRunH_Freq    		60000		//60KHz
		#define FreeRunV_Freq    		75			//75 Hz
		#define FreeRunVtotal    		800			//800 line
		#define PanelInterface			TTL_TO_TCON
		#define PanelShortHsync			0
		#define Panel_Invert_DVS 		0xff
		#define Panel_Invert_DHS 		0xff
		#define Panel_Invert_DCLK 		0x00
		#define Panel_Invert_DEN 		0x00
		#define PanelPadDrive 			0x0333

		#define Panel_Spread_Spect_En	0xff	// 0xff : enable spectrum
												// 0x00 : disable spectrum
		#define PanelSpreadSpectrumCtrl 0x00
		// Value for Spread_Spectrum_Control register
		// 0x00: 0.097% ... 0x07: 12.5%

		// Panel dething mode
		#define PanelDethMode			0x31

		// define panel timing. word constant used to program registers 0xd8 and 0xd9 during power up and power down
		#define PowerUpPanelTiming		1		// 1 ms
		#define PowerUpInvTiming		250		// 250 ms
		#define PowerDownPanelTiming	1		// 1 ms
		#define PowerDownInvTiming		250		// 250 ms

    #endif

    #if PANEL == CMO_M150X3_T05

		#define PanelName				"CMO_M150X3_T05\r\n"
		#define PanelXga                1
		#define PanelSxga               0
		#define PanelUxga               0
		#define PanelTwoPixelPerClk     1       // Double pixels output 
		#define PanelDepth              6
		#define PanelSync_DE			0

		#define PanelWidth				1024
		#define PanelHeight				768

		#define PanelMaxVFreq           75      // Hz
		#define PanelMinVFreq           50      // Hz
		#define PanelMaxHFreq           60000   // Hz

		#define PanelMaxPClk            80000   // KHz

		#define PanelMinHTotal          1200
		#define PanelMaxHTotal          1800
		#define PanelMinHSyncWidth      80
		#define PanelMinHSyncBackPorch  80
		#define PanelHSyncStart			PanelMinHTotal - PanelMinHSyncWidth - PanelMinHSyncBackPorch
		#define PanelHSyncEnd			PanelHSyncStart + PanelMinHSyncWidth
		#define PanelHActiveStart		PanelMinHSyncBackPorch + PanelMinHSyncWidth

		#define PanelMaxVTotal			960
		#define PanelTypVTotal			800
		#define PanelMinVTotal			780
		#define PanelMinVSyncWidth      3
		#define PanelMinVSyncBackPorch  7
		#define PanelVSyncStart			PanelTypVTotal - PanelMinVSyncWidth - PanelMinVSyncBackPorch
		#define PanelVSyncEnd			PanelVSyncStart + PanelMinVSyncWidth
		#define PanelVActiveStart		PanelMinVSyncBackPorch + PanelMinVSyncWidth

		#define FreeRunH_Freq    		60000		//60KHz
		#define FreeRunV_Freq    		75			//75 Hz
		#define FreeRunVtotal    		800			//800 line
		#define PanelInterface			TTL_TO_TCON
		#define PanelShortHsync			1
		#define Panel_Invert_DVS 		0xff
		#define Panel_Invert_DHS 		0xff
		#define Panel_Invert_DCLK 		0x00
		#define Panel_Invert_DEN 		0x00
		#define PanelPadDrive 			0x0333

		#define Panel_Spread_Spect_En	0xff	// 0xff : enable spectrum
												// 0x00 : disable spectrum
		#define PanelSpreadSpectrumCtrl 0x00
		// Value for Spread_Spectrum_Control register
		// 0x00: 0.097% ... 0x07: 12.5%

		// Panel dething mode
		#define PanelDethMode			0x31

		// define panel timing. word constant used to program registers 0xd8 and 0xd9 during power up and power down
		#define PowerUpPanelTiming		1		// 1 ms
		#define PowerUpInvTiming		250		// 250 ms
		#define PowerDownPanelTiming	1		// 1 ms
		#define PowerDownInvTiming		250		// 250 ms

    #endif

    #if PANEL == CMO_M150X2_T05

		#define PanelName				"CMO_M150X2_T05\r\n"
		#define PanelXga                1
		#define PanelSxga               0
		#define PanelUxga               0
		#define PanelTwoPixelPerClk     1       // Double pixels output 
		#define PanelDepth              6
		#define PanelSync_DE			0

		#define PanelWidth				1024
		#define PanelHeight				768

		#define PanelMaxVFreq           75      // Hz
		#define PanelMinVFreq           50      // Hz
		#define PanelMaxHFreq           60000   // Hz

		#define PanelMaxPClk            80000   // KHz

		#define PanelMinHTotal          1200
		#define PanelMaxHTotal          1800
		#define PanelMinHSyncWidth      80
		#define PanelMinHSyncBackPorch  80
		#define PanelHSyncStart			PanelMinHTotal - PanelMinHSyncWidth - PanelMinHSyncBackPorch
		#define PanelHSyncEnd			PanelHSyncStart + PanelMinHSyncWidth
		#define PanelHActiveStart		PanelMinHSyncBackPorch + PanelMinHSyncWidth

		#define PanelMaxVTotal			960
		#define PanelTypVTotal			800
		#define PanelMinVTotal			780
		#define PanelMinVSyncWidth      3
		#define PanelMinVSyncBackPorch  7
		#define PanelVSyncStart			PanelTypVTotal - PanelMinVSyncWidth - PanelMinVSyncBackPorch
		#define PanelVSyncEnd			PanelVSyncStart + PanelMinVSyncWidth
		#define PanelVActiveStart		PanelMinVSyncBackPorch + PanelMinVSyncWidth

		#define FreeRunH_Freq    		60000		//60KHz
		#define FreeRunV_Freq    		75			//75 Hz
		#define FreeRunVtotal    		800			//800 line
		#define PanelInterface			TTL_TO_TCON
		#define PanelShortHsync			1
		#define Panel_Invert_DVS 		0xff
		#define Panel_Invert_DHS 		0xff
		#define Panel_Invert_DCLK 		0x00
		#define Panel_Invert_DEN 		0x00
		#define PanelPadDrive 			0x0333

		#define Panel_Spread_Spect_En	0xff	// 0xff : enable spectrum
												// 0x00 : disable spectrum
		#define PanelSpreadSpectrumCtrl 0x00
		// Value for Spread_Spectrum_Control register
		// 0x00: 0.097% ... 0x07: 12.5%

		// Panel dething mode
		#define PanelDethMode			0x31

		// define panel timing. word constant used to program registers 0xd8 and 0xd9 during power up and power down
		#define PowerUpPanelTiming		1		// 1 ms
		#define PowerUpInvTiming		250		// 250 ms
		#define PowerDownPanelTiming	1		// 1 ms
		#define PowerDownInvTiming		250		// 250 ms

    #endif

    #if PANEL == HannStar_HSD150MX49_A

		#define PanelName				"HannStar_HSD150MX49_A\r\n"
		#define PanelXga                1
		#define PanelSxga               0
		#define PanelUxga               0
		#define PanelTwoPixelPerClk     1       // Double pixels output 
		#define PanelDepth              8
		#define PanelSync_DE			0

		#define PanelWidth				1024
		#define PanelHeight				768

		#define PanelMaxVFreq           75      // Hz
		#define PanelMinVFreq           50      // Hz
		#define PanelMaxHFreq           60000   // Hz

		#define PanelMaxPClk            80000   // KHz

		#define PanelMinHTotal          1200
		#define PanelMaxHTotal          1400
		#define PanelMinHSyncWidth      80
		#define PanelMinHSyncBackPorch  80
		#define PanelHSyncStart			PanelMinHTotal - PanelMinHSyncWidth - PanelMinHSyncBackPorch
		#define PanelHSyncEnd			PanelHSyncStart + PanelMinHSyncWidth
		#define PanelHActiveStart		PanelMinHSyncBackPorch + PanelMinHSyncWidth

		#define PanelMaxVTotal			860
		#define PanelTypVTotal			806
		#define PanelMinVTotal			780
		#define PanelMinVSyncWidth      3
		#define PanelMinVSyncBackPorch  7
		#define PanelVSyncStart			PanelTypVTotal - PanelMinVSyncWidth - PanelMinVSyncBackPorch
		#define PanelVSyncEnd			PanelVSyncStart + PanelMinVSyncWidth
		#define PanelVActiveStart		PanelMinVSyncBackPorch + PanelMinVSyncWidth

		#define FreeRunH_Freq    		60000		//60KHz
		#define FreeRunV_Freq    		75			//75 Hz
		#define FreeRunVtotal    		800			//800 line
		#define PanelInterface			TTL_TO_TCON
		#define PanelShortHsync			0
		#define Panel_Invert_DVS 		0x00
		#define Panel_Invert_DHS 		0x00
		#define Panel_Invert_DCLK 		0x00
		#define Panel_Invert_DEN 		0x00
		#define PanelPadDrive 			0x0333

		#define Panel_Spread_Spect_En	0xff	// 0xff : enable spectrum
												// 0x00 : disable spectrum
		#define PanelSpreadSpectrumCtrl 0x00
		// Value for Spread_Spectrum_Control register
		// 0x00: 0.097% ... 0x07: 12.5%

		// Panel dething mode
		#define PanelDethMode			0x31

		// define panel timing. word constant used to program registers 0xd8 and 0xd9 during power up and power down
		#define PowerUpPanelTiming		1		// 1 ms
		#define PowerUpInvTiming		250		// 250 ms
		#define PowerDownPanelTiming	1		// 1 ms
		#define PowerDownInvTiming		250		// 250 ms

    #endif

    #if PANEL == HannStar_HSD150MX41_A

		#define PanelName				"HannStar_HSD150MX41_A\r\n"
		#define PanelXga                1
		#define PanelSxga               0
		#define PanelUxga               0
		#define PanelTwoPixelPerClk     1       // Double pixels output 
		#define PanelDepth              6
		#define PanelSync_DE			0

		#define PanelWidth				1024
		#define PanelHeight				768

		#define PanelMaxVFreq           75      // Hz
		#define PanelMinVFreq           50      // Hz
		#define PanelMaxHFreq           60000   // Hz

		#define PanelMaxPClk            80000   // KHz

		#define PanelMinHTotal          1200
		#define PanelMaxHTotal          1400
		#define PanelMinHSyncWidth      80
		#define PanelMinHSyncBackPorch  80
		#define PanelHSyncStart			PanelMinHTotal - PanelMinHSyncWidth - PanelMinHSyncBackPorch
		#define PanelHSyncEnd			PanelHSyncStart + PanelMinHSyncWidth
		#define PanelHActiveStart		PanelMinHSyncBackPorch + PanelMinHSyncWidth

		#define PanelMaxVTotal			860
		#define PanelTypVTotal			806
		#define PanelMinVTotal			780
		#define PanelMinVSyncWidth      3
		#define PanelMinVSyncBackPorch  7
		#define PanelVSyncStart			PanelTypVTotal - PanelMinVSyncWidth - PanelMinVSyncBackPorch
		#define PanelVSyncEnd			PanelVSyncStart + PanelMinVSyncWidth
		#define PanelVActiveStart		PanelMinVSyncBackPorch + PanelMinVSyncWidth

		#define FreeRunH_Freq    		60000		//60KHz
		#define FreeRunV_Freq    		75			//75 Hz
		#define FreeRunVtotal    		800			//800 line
		#define PanelInterface			TTL_TO_TCON
		#define PanelShortHsync			0
		#define Panel_Invert_DVS 		0x00
		#define Panel_Invert_DHS 		0x00
		#define Panel_Invert_DCLK 		0x00
		#define Panel_Invert_DEN 		0x00
		#define PanelPadDrive 			0x0333

		#define Panel_Spread_Spect_En	0xff	// 0xff : enable spectrum
												// 0x00 : disable spectrum
		#define PanelSpreadSpectrumCtrl 0x00
		// Value for Spread_Spectrum_Control register
		// 0x00: 0.097% ... 0x07: 12.5%

		// Panel dething mode
		#define PanelDethMode			0x31

		// define panel timing. word constant used to program registers 0xd8 and 0xd9 during power up and power down
		#define PowerUpPanelTiming		1		// 1 ms
		#define PowerUpInvTiming		250		// 250 ms
		#define PowerDownPanelTiming	1		// 1 ms
		#define PowerDownInvTiming		250		// 250 ms

    #endif

    #if PANEL == HannStar_HSD150MX12_A

		#define PanelName				"HannStar_HSD150MX12_A\r\n"
		#define PanelXga                1
		#define PanelSxga               0
		#define PanelUxga               0
		#define PanelTwoPixelPerClk     0       // Signle pixels output 
		#define PanelDepth              8
		#define PanelSync_DE			0

		#define PanelWidth				1024
		#define PanelHeight				768

		#define PanelMaxVFreq           75      // Hz
		#define PanelMinVFreq           50      // Hz
		#define PanelMaxHFreq           60000   // Hz

		#define PanelMaxPClk            80000   // KHz

		#define PanelMinHTotal          1200
		#define PanelMaxHTotal          1400
		#define PanelMinHSyncWidth      80
		#define PanelMinHSyncBackPorch  80
		#define PanelHSyncStart			PanelMinHTotal - PanelMinHSyncWidth - PanelMinHSyncBackPorch
		#define PanelHSyncEnd			PanelHSyncStart + PanelMinHSyncWidth
		#define PanelHActiveStart		PanelMinHSyncBackPorch + PanelMinHSyncWidth

		#define PanelMaxVTotal			860
		#define PanelTypVTotal			806
		#define PanelMinVTotal			780
		#define PanelMinVSyncWidth      3
		#define PanelMinVSyncBackPorch  7
		#define PanelVSyncStart			PanelTypVTotal - PanelMinVSyncWidth - PanelMinVSyncBackPorch
		#define PanelVSyncEnd			PanelVSyncStart + PanelMinVSyncWidth
		#define PanelVActiveStart		PanelMinVSyncBackPorch + PanelMinVSyncWidth

		#define FreeRunH_Freq    		60000		//60KHz
		#define FreeRunV_Freq    		75			//75 Hz
		#define FreeRunVtotal    		800			//800 line
		#define PanelInterface			TTL_TO_TCON
		#define PanelShortHsync			0
		#define Panel_Invert_DVS 		0x00
		#define Panel_Invert_DHS 		0x00
		#define Panel_Invert_DCLK 		0x00
		#define Panel_Invert_DEN 		0x00
		#define PanelPadDrive 			0x0333

		#define Panel_Spread_Spect_En	0xff	// 0xff : enable spectrum
												// 0x00 : disable spectrum
		#define PanelSpreadSpectrumCtrl 0x00
		// Value for Spread_Spectrum_Control register
		// 0x00: 0.097% ... 0x07: 12.5%

		// Panel dething mode
		#define PanelDethMode			0x31

		// define panel timing. word constant used to program registers 0xd8 and 0xd9 during power up and power down
		#define PowerUpPanelTiming		1		// 1 ms
		#define PowerUpInvTiming		250		// 250 ms
		#define PowerDownPanelTiming	1		// 1 ms
		#define PowerDownInvTiming		250		// 250 ms

    #endif

    #if PANEL == CPT_CLAA150XG01

		#define PanelName				"CPT_CLAA150XG01\r\n"
		#define PanelXga                1
		#define PanelSxga               0
		#define PanelUxga               0
		#define PanelTwoPixelPerClk     1       // Double pixels output 
		#define PanelDepth              8
		#define PanelSync_DE			0

		#define PanelWidth				1024
		#define PanelHeight				768

		#define PanelMaxVFreq           75      // Hz
		#define PanelMinVFreq           55      // Hz
		#define PanelMaxHFreq           62500   // Hz

		#define PanelMaxPClk            80000   // KHz

		#define PanelMinHTotal          1200
		#define PanelMaxHTotal          1884
		#define PanelMinHSyncWidth      80
		#define PanelMinHSyncBackPorch  80
		#define PanelHSyncStart			PanelMinHTotal - PanelMinHSyncWidth - PanelMinHSyncBackPorch
		#define PanelHSyncEnd			PanelHSyncStart + PanelMinHSyncWidth
		#define PanelHActiveStart		PanelMinHSyncBackPorch + PanelMinHSyncWidth

		#define PanelMaxVTotal			1136
		#define PanelTypVTotal			806
		#define PanelMinVTotal			780
		#define PanelMinVSyncWidth      3
		#define PanelMinVSyncBackPorch  7
		#define PanelVSyncStart			PanelTypVTotal - PanelMinVSyncWidth - PanelMinVSyncBackPorch
		#define PanelVSyncEnd			PanelVSyncStart + PanelMinVSyncWidth
		#define PanelVActiveStart		PanelMinVSyncBackPorch + PanelMinVSyncWidth

		#define FreeRunH_Freq    		60000		//60KHz
		#define FreeRunV_Freq    		75			//75 Hz
		#define FreeRunVtotal    		800			//800 line
		#define PanelInterface			TTL_TO_TCON
		#define PanelShortHsync			0
		#define Panel_Invert_DVS 		0xff
		#define Panel_Invert_DHS 		0xff
		#define Panel_Invert_DCLK 		0x00
		#define Panel_Invert_DEN 		0x00
		#define PanelPadDrive 			0x0333

		#define Panel_Spread_Spect_En	0xff	// 0xff : enable spectrum
												// 0x00 : disable spectrum
		#define PanelSpreadSpectrumCtrl 0x00
		// Value for Spread_Spectrum_Control register
		// 0x00: 0.097% ... 0x07: 12.5%

		// Panel dething mode
		#define PanelDethMode			0x31

		// define panel timing. word constant used to program registers 0xd8 and 0xd9 during power up and power down
		#define PowerUpPanelTiming		1		// 1 ms
		#define PowerUpInvTiming		250		// 250 ms
		#define PowerDownPanelTiming	1		// 1 ms
		#define PowerDownInvTiming		250		// 250 ms

    #endif

    #if PANEL == SINAI43140CBx_1

		#define PanelName				"SINAI43140CBx_1\r\n"
		#define PanelXga                0
		#define PanelSxga               1
		#define PanelUxga               0
		#define PanelTwoPixelPerClk     1       // Double pixels output 
		#define PanelDepth              8
		#define PanelSync_DE			1

		#define PanelWidth				1280
		#define PanelHeight				1024

		#define PanelMaxVFreq           75      // Hz
		#define PanelMinVFreq           50      // Hz
		#define PanelMaxHFreq           62500   // Hz

		#define PanelMaxPClk            135000   // KHz

		#define PanelMinHTotal          1488
		#define PanelMaxHTotal          2400
		#define PanelMinHSyncWidth      80
		#define PanelMinHSyncBackPorch  80
		#define PanelHSyncStart			PanelMinHTotal - PanelMinHSyncWidth - PanelMinHSyncBackPorch
		#define PanelHSyncEnd			PanelHSyncStart + PanelMinHSyncWidth
		#define PanelHActiveStart		PanelMinHSyncBackPorch + PanelMinHSyncWidth

		#define PanelMaxVTotal			2000
		#define PanelTypVTotal			1066
		#define PanelMinVTotal			1040
		#define PanelMinVSyncWidth      3
		#define PanelMinVSyncBackPorch  7
		#define PanelVSyncStart			PanelTypVTotal - PanelMinVSyncWidth - PanelMinVSyncBackPorch
		#define PanelVSyncEnd			PanelVSyncStart + PanelMinVSyncWidth
		#define PanelVActiveStart		PanelMinVSyncBackPorch + PanelMinVSyncWidth

		#define FreeRunH_Freq    		64000		//64KHz
		#define FreeRunV_Freq    		60			//60 Hz
		#define FreeRunVtotal    		1066		//1066 line
		#define PanelInterface			LVDS_TO_TCON
		#define PanelShortHsync			0
		#define Panel_Invert_DVS 		0xff
		#define Panel_Invert_DHS 		0xff
		#define Panel_Invert_DCLK 		0x00
		#define Panel_Invert_DEN 		0x00
		#define PanelPadDrive 			0x0333

		#define Panel_Spread_Spect_En	0xff	// 0xff : enable spectrum
												// 0x00 : disable spectrum
		#define PanelSpreadSpectrumCtrl 0x00
		// Value for Spread_Spectrum_Control register
		// 0x00: 0.097% ... 0x07: 12.5%

		// define panel timing. word constant used to program registers 0xd8 and 0xd9 during power up and power down
		#define PowerUpPanelTiming		1		// 1 ms
		#define PowerUpInvTiming		250		// 250 ms
		#define PowerDownPanelTiming	1		// 1 ms
		#define PowerDownInvTiming		250		// 250 ms

    #endif

    #if PANEL == SINAI38951CBx

		#define PanelName				"SINAI38951CBx\r\n"
		#define PanelXga                0
		#define PanelSxga               1
		#define PanelUxga               0
		#define PanelTwoPixelPerClk     1       // Double pixels output 
		#define PanelDepth              6
		#define PanelSync_DE			1

		#define PanelWidth				1400
		#define PanelHeight				1050

		#define PanelMaxVFreq           65      // Hz
		#define PanelMinVFreq           50      // Hz
		#define PanelMaxHFreq           76000   // Hz

		#define PanelMaxPClk            114000   // KHz

		#define PanelMinHTotal          1640
		#define PanelMaxHTotal          2046
		#define PanelMinHSyncWidth      80
		#define PanelMinHSyncBackPorch  80
		#define PanelHSyncStart			PanelMinHTotal - PanelMinHSyncWidth - PanelMinHSyncBackPorch
		#define PanelHSyncEnd			PanelHSyncStart + PanelMinHSyncWidth
		#define PanelHActiveStart		PanelMinHSyncBackPorch + PanelMinHSyncWidth

		#define PanelMaxVTotal			2047
		#define PanelTypVTotal			1068
		#define PanelMinVTotal			1059
		#define PanelMinVSyncWidth      3
		#define PanelMinVSyncBackPorch  7
		#define PanelVSyncStart			PanelTypVTotal - PanelMinVSyncWidth - PanelMinVSyncBackPorch
		#define PanelVSyncEnd			PanelVSyncStart + PanelMinVSyncWidth
		#define PanelVActiveStart		PanelMinVSyncBackPorch + PanelMinVSyncWidth

		#define FreeRunH_Freq    		64000		//64KHz
		#define FreeRunV_Freq    		60			//60 Hz
		#define FreeRunVtotal    		1066		//1066 line
		#define PanelInterface			LVDS_TO_TCON
		#define PanelShortHsync			0
		#define Panel_Invert_DVS 		0x00
		#define Panel_Invert_DHS 		0x00
		#define Panel_Invert_DCLK 		0x00
		#define Panel_Invert_DEN 		0x00
		#define PanelPadDrive 			0x0333

		#define Panel_Spread_Spect_En	0xff	// 0xff : enable spectrum
												// 0x00 : disable spectrum
		#define PanelSpreadSpectrumCtrl 0x00
		// Value for Spread_Spectrum_Control register
		// 0x00: 0.097% ... 0x07: 12.5%

		// Panel dething mode
		#define PanelDethMode			0x31

		// define panel timing. word constant used to program registers 0xd8 and 0xd9 during power up and power down
		#define PowerUpPanelTiming		1		// 1 ms
		#define PowerUpInvTiming		250		// 250 ms
		#define PowerDownPanelTiming	1		// 1 ms
		#define PowerDownInvTiming		250		// 250 ms

    #endif

    #if PANEL == SINAI38140CBx

		#define PanelName				"SINAI38140CBx\r\n"
		#define PanelXga                1
		#define PanelSxga               0
		#define PanelUxga               0
		#define PanelTwoPixelPerClk     0       // Single pixels output 
		#define PanelDepth              8
		#define PanelSync_DE			0

		#define PanelWidth				1024
		#define PanelHeight				768

		#define PanelMaxVFreq           75      // Hz
		#define PanelMinVFreq           55      // Hz
		#define PanelMaxHFreq           60000   // Hz

		#define PanelMaxPClk            80000   // KHz

		#define PanelMinHTotal          1200
		#define PanelMaxHTotal          2500
		#define PanelMinHSyncWidth      80
		#define PanelMinHSyncBackPorch  80
		#define PanelHSyncStart			PanelMinHTotal - PanelMinHSyncWidth - PanelMinHSyncBackPorch
		#define PanelHSyncEnd			PanelHSyncStart + PanelMinHSyncWidth
		#define PanelHActiveStart		PanelMinHSyncBackPorch + PanelMinHSyncWidth

		#define PanelMaxVTotal			1000
		#define PanelTypVTotal			806
		#define PanelMinVTotal			780
		#define PanelMinVSyncWidth      2
		#define PanelMinVSyncBackPorch  4
		#define PanelVSyncStart			PanelTypVTotal - PanelMinVSyncWidth - PanelMinVSyncBackPorch
		#define PanelVSyncEnd			PanelVSyncStart + PanelMinVSyncWidth
		#define PanelVActiveStart		PanelMinVSyncBackPorch + PanelMinVSyncWidth

		#define FreeRunH_Freq    		60000		//60KHz
		#define FreeRunV_Freq    		75			//75 Hz
		#define FreeRunVtotal    		800			//800 line
		#define PanelInterface			TTL_TO_TCON
		#define PanelShortHsync			0
		#define Panel_Invert_DVS 		0xff
		#define Panel_Invert_DHS 		0xff
		#define Panel_Invert_DCLK 		0x00
		#define Panel_Invert_DEN 		0x00
		#define PanelPadDrive 			0x0333

		#define Panel_Spread_Spect_En	0xff	// 0xff : enable spectrum
												// 0x00 : disable spectrum
		#define PanelSpreadSpectrumCtrl 0x00
		// Value for Spread_Spectrum_Control register
		// 0x00: 0.097% ... 0x07: 12.5%

		// Panel dething mode
		#define PanelDethMode			0x31

		// define panel timing. word constant used to program registers 0xd8 and 0xd9 during power up and power down
		#define PowerUpPanelTiming		1		// 1 ms
		#define PowerUpInvTiming		250		// 250 ms
		#define PowerDownPanelTiming	1		// 1 ms
		#define PowerDownInvTiming		250		// 250 ms

    #endif

    #if PANEL == Sharp_LQ150X1DG51

		#define PanelName				"Sharp_LQ150X1DG51\r\n"
		#define PanelXga                1
		#define PanelSxga               0
		#define PanelUxga               0
		#define PanelTwoPixelPerClk     1       // Dual pixels output 
		#define PanelDepth              6
		#define PanelSync_DE			0

		#define PanelWidth				1024
		#define PanelHeight				768

		#define PanelMaxVFreq           75      // Hz
		#define PanelMinVFreq           55      // Hz
		#define PanelMaxHFreq           60000   // Hz

		#define PanelMaxPClk            80000   // KHz

		#define PanelMinHTotal          1200
		#define PanelMaxHTotal          1720
		#define PanelMinHSyncWidth      80
		#define PanelMinHSyncBackPorch  80
		#define PanelHSyncStart			PanelMinHTotal - PanelMinHSyncWidth - PanelMinHSyncBackPorch
		#define PanelHSyncEnd			PanelHSyncStart + PanelMinHSyncWidth
		#define PanelHActiveStart		PanelMinHSyncBackPorch + PanelMinHSyncWidth

		#define PanelMaxVTotal			990
		#define PanelTypVTotal			806
		#define PanelMinVTotal			780
		#define PanelMinVSyncWidth      3
		#define PanelMinVSyncBackPorch  7
		#define PanelVSyncStart			PanelTypVTotal - PanelMinVSyncWidth - PanelMinVSyncBackPorch
		#define PanelVSyncEnd			PanelVSyncStart + PanelMinVSyncWidth
		#define PanelVActiveStart		PanelMinVSyncBackPorch + PanelMinVSyncWidth

		#define FreeRunH_Freq    		60000		//60KHz
		#define FreeRunV_Freq    		75			//75 Hz
		#define FreeRunVtotal    		800			//800 line
		#define PanelInterface			TTL_TO_TCON
		#define PanelShortHsync			0
		#define Panel_Invert_DVS 		0xff
		#define Panel_Invert_DHS 		0xff
		#define Panel_Invert_DCLK 		0x00
		#define Panel_Invert_DEN 		0x00
		#define PanelPadDrive 			0x0333

		#define Panel_Spread_Spect_En	0xff	// 0xff : enable spectrum
												// 0x00 : disable spectrum
		#define PanelSpreadSpectrumCtrl 0x00
		// Value for Spread_Spectrum_Control register
		// 0x00: 0.097% ... 0x07: 12.5%

		// define panel timing. word constant used to program registers 0xd8 and 0xd9 during power up and power down
		#define PowerUpPanelTiming		1		// 1 ms
		#define PowerUpInvTiming		250		// 250 ms
		#define PowerDownPanelTiming	1		// 1 ms
		#define PowerDownInvTiming		250		// 250 ms

    #endif

    #if PANEL == CMO_M170E4_L01

		#define PanelName				"CMO_M170E4_L01\r\n"
		#define PanelXga                0
		#define PanelSxga               1
		#define PanelUxga               0
		#define PanelTwoPixelPerClk     1       // Double pixels output 
		#define PanelDepth              6
		#define PanelSync_DE            0		//0=H/V 1=DE

		#define PanelWidth				1280
		#define PanelHeight				1024

		#define PanelMaxVFreq           75      // Hz
		#define PanelMinVFreq           56      // Hz
		#define PanelMaxHFreq           82000   // Hz

		#define PanelMaxPClk            140000   // KHz

		#define PanelMinHTotal          1688
		#define PanelMaxHTotal          2046
		#define PanelMinHSyncWidth      80
		#define PanelMinHSyncBackPorch  80
		#define PanelHSyncStart			PanelMinHTotal - PanelMinHSyncWidth - PanelMinHSyncBackPorch
		#define PanelHSyncEnd			PanelHSyncStart + PanelMinHSyncWidth
		#define PanelHActiveStart		PanelMinHSyncBackPorch + PanelMinHSyncWidth

		#define PanelMaxVTotal			1274//2047
		#define PanelTypVTotal			1066
		#define PanelMinVTotal			1040
		#define PanelMinVSyncWidth      3
		#define PanelMinVSyncBackPorch  7
		#define PanelVSyncStart			PanelTypVTotal - PanelMinVSyncWidth - PanelMinVSyncBackPorch
		#define PanelVSyncEnd			PanelVSyncStart + PanelMinVSyncWidth
		#define PanelVActiveStart		PanelMinVSyncBackPorch + PanelMinVSyncWidth

		#define FreeRunH_Freq    		64000		//64KHz
		#define FreeRunV_Freq    		60			//60 Hz
		#define FreeRunVtotal    		1066		//1066 line
		#define PanelInterface			LVDS_TO_TCON
		#define PanelShortHsync			0
		#define Panel_Invert_DVS 		0x00
		#define Panel_Invert_DHS 		0x00
		#define Panel_Invert_DCLK 		0x00
		#define Panel_Invert_DEN 		0x00
		#define PanelPadDrive 			0x0333

		#define Panel_Spread_Spect_En	0xff	// 0xff : enable spectrum
												// 0x00 : disable spectrum
		#define PanelSpreadSpectrumCtrl 0x04
		// Value for Spread_Spectrum_Control register
		// 0x00: 0.097% ... 0x07: 12.5%

		// Panel dething mode
		#define PanelDethMode			0x33

		// define panel timing. word constant used to program registers 0xd8 and 0xd9 during power up and power down
		#define PowerUpPanelTiming		1		// 1 ms
		#define PowerUpInvTiming		250		// 250 ms
		#define PowerDownPanelTiming	1		// 1 ms
		#define PowerDownInvTiming		250		// 250 ms

    #endif

    #if PANEL == NL6448BC33_46

		#define PanelName				"NL6448BC33_46\r\n"
		#define PanelXga                1
		#define PanelSxga               0
		#define PanelUxga               0
		#define PanelTwoPixelPerClk     0       // Double pixels output 
		#define PanelDepth              6
		#define PanelSync_DE            0		//0=H/V 1=DE

		#define PanelWidth				640
		#define PanelHeight				480

		#define PanelMaxVFreq           62      // Hz
		#define PanelMinVFreq           58      // Hz
		#define PanelMaxHFreq           33333   // Hz

		#define PanelMaxPClk            26000   // KHz

		#define PanelMinHTotal          760
		#define PanelMaxHTotal          900
		#define PanelMinHSyncWidth      40
		#define PanelMinHSyncBackPorch  40
		#define PanelHSyncStart			PanelMinHTotal - PanelMinHSyncWidth - PanelMinHSyncBackPorch
		#define PanelHSyncEnd			PanelHSyncStart + PanelMinHSyncWidth
		#define PanelHActiveStart		PanelMinHSyncBackPorch + PanelMinHSyncWidth

		#define PanelMaxVTotal			600
		#define PanelTypVTotal			525
		#define PanelMinVTotal			492
		#define PanelMinVSyncWidth      3
		#define PanelMinVSyncBackPorch  7
		#define PanelVSyncStart			PanelTypVTotal - PanelMinVSyncWidth - PanelMinVSyncBackPorch
		#define PanelVSyncEnd			PanelVSyncStart + PanelMinVSyncWidth
		#define PanelVActiveStart		PanelMinVSyncBackPorch + PanelMinVSyncWidth

		#define FreeRunH_Freq    		64000		//64KHz
		#define FreeRunV_Freq    		60			//60 Hz
		#define FreeRunVtotal    		1066		//1066 line
		#define PanelInterface			TTL_TO_TCON
		#define PanelShortHsync			0
		#define Panel_Invert_DVS 		0xff
		#define Panel_Invert_DHS 		0xff
		#define Panel_Invert_DCLK 		0x00
		#define Panel_Invert_DEN 		0x00
		#define PanelPadDrive 			0x0333

		#define Panel_Spread_Spect_En	0xff	// 0xff : enable spectrum
												// 0x00 : disable spectrum
		#define PanelSpreadSpectrumCtrl 0x00
		// Value for Spread_Spectrum_Control register
		// 0x00: 0.097% ... 0x07: 12.5%

		// Panel dething mode
		#define PanelDethMode			0x31

		// define panel timing. word constant used to program registers 0xd8 and 0xd9 during power up and power down
		#define PowerUpPanelTiming		1		// 1 ms
		#define PowerUpInvTiming		250		// 250 ms
		#define PowerDownPanelTiming	1		// 1 ms
		#define PowerDownInvTiming		250		// 250 ms

    #endif

    #if PANEL == AU_L170EN05

		#define PanelName				"AU_L170EN05\r\n"
		#define PanelXga                0
		#define PanelSxga               1
		#define PanelUxga               0
		#define PanelTwoPixelPerClk     1       // Double pixels output 
		#define PanelDepth              6
		#define PanelSync_DE            0		//0=H/V 1=DE

		#define PanelWidth				1280
		#define PanelHeight				1024

		#define PanelMaxVFreq           75      // Hz
		#define PanelMinVFreq           56      // Hz
		#define PanelMaxHFreq           82000   // Hz

		#define PanelMaxPClk            140000   // KHz

		#define PanelMinHTotal          1688//1600
		#define PanelMaxHTotal          2046
		#define PanelMinHSyncWidth      80
		#define PanelMinHSyncBackPorch  80
		#define PanelHSyncStart			PanelMinHTotal - PanelMinHSyncWidth - PanelMinHSyncBackPorch
		#define PanelHSyncEnd			PanelHSyncStart + PanelMinHSyncWidth
		#define PanelHActiveStart		PanelMinHSyncBackPorch + PanelMinHSyncWidth

		#define PanelMaxVTotal			2047
		#define PanelTypVTotal			1066
		#define PanelMinVTotal			1040
		#define PanelMinVSyncWidth      3
		#define PanelMinVSyncBackPorch  7
		#define PanelVSyncStart			PanelTypVTotal - PanelMinVSyncWidth - PanelMinVSyncBackPorch
		#define PanelVSyncEnd			PanelVSyncStart + PanelMinVSyncWidth
		#define PanelVActiveStart		PanelMinVSyncBackPorch + PanelMinVSyncWidth

		#define FreeRunH_Freq    		64000		//64KHz
		#define FreeRunV_Freq    		60			//60 Hz
		#define FreeRunVtotal    		1066		//1066 line
		#define PanelInterface			LVDS_TO_TCON
		#define PanelShortHsync			0
		#define Panel_Invert_DVS 		0x00
		#define Panel_Invert_DHS 		0x00
		#define Panel_Invert_DCLK 		0x00
		#define Panel_Invert_DEN 		0x00
		#define PanelPadDrive 			0x0333

		#define Panel_Spread_Spect_En	0xff	// 0xff : enable spectrum
												// 0x00 : disable spectrum
		#define PanelSpreadSpectrumCtrl 0x04
		// Value for Spread_Spectrum_Control register
		// 0x00: 0.097% ... 0x07: 12.5%

		// Panel dething mode
		#define PanelDethMode			0x41

		// define panel timing. word constant used to program registers 0xd8 and 0xd9 during power up and power down
		#define PowerUpPanelTiming		1		// 1 ms
		#define PowerUpInvTiming		250		// 250 ms
		#define PowerDownPanelTiming	1		// 1 ms
		#define PowerDownInvTiming		250		// 250 ms

    #endif

    #if PANEL == AU_M150XN05_1

		#define PanelName				"AU_M150XN05_1\r\n"
		#define PanelXga                1
		#define PanelSxga               0
		#define PanelUxga               0
		#define PanelTwoPixelPerClk     1       // Double pixels output 
		#define PanelDepth              6
		#define PanelSync_DE			0		//0=H/V mode 1=DE mode
		#define PanelWidth				1024
		#define PanelHeight				768

		#define PanelMaxVFreq           76      // Hz
		#define PanelMinVFreq           50      // Hz
		#define PanelMaxHFreq           60000   // Hz

		#define PanelMaxPClk            80000   // KHz

		#define PanelMinHTotal          1200
		#define PanelMaxHTotal          1800
		#define PanelMinHSyncWidth      80
		#define PanelMinHSyncBackPorch  80
		#define PanelHSyncStart			PanelMinHTotal - PanelMinHSyncWidth - PanelMinHSyncBackPorch
		#define PanelHSyncEnd			PanelHSyncStart + PanelMinHSyncWidth
		#define PanelHActiveStart		PanelMinHSyncBackPorch + PanelMinHSyncWidth

		#define PanelMaxVTotal			960
		#define PanelTypVTotal			806
		#define PanelMinVTotal			780
		#define PanelMinVSyncWidth      3
		#define PanelMinVSyncBackPorch  7
		#define PanelVSyncStart			PanelTypVTotal - PanelMinVSyncWidth - PanelMinVSyncBackPorch
		#define PanelVSyncEnd			PanelVSyncStart + PanelMinVSyncWidth
		#define PanelVActiveStart		PanelMinVSyncBackPorch + PanelMinVSyncWidth

		#define FreeRunH_Freq    		60000		//60KHz
		#define FreeRunV_Freq    		75			//75 Hz
		#define FreeRunVtotal    		800			//800 line
		#define PanelInterface			TTL_TO_TCON
		#define PanelShortHsync			0
		#define Panel_Invert_DVS 		0xff
		#define Panel_Invert_DHS 		0xff
		#define Panel_Invert_DCLK 		0x00
		#define Panel_Invert_DEN 		0x00
		#define PanelPadDrive 			0x0333

		#define Panel_Spread_Spect_En	0xff	// 0xff : enable spectrum
												// 0x00 : disable spectrum
		#define PanelSpreadSpectrumCtrl 0x00
		// Value for Spread_Spectrum_Control register
		// 0x00: 0.097% ... 0x07: 12.5%

		// Panel dething mode
		#define PanelDethMode			0x31

		// define panel timing. word constant used to program registers 0xd8 and 0xd9 during power up and power down
		#define PowerUpPanelTiming		1		// 1 ms
		#define PowerUpInvTiming		250		// 250 ms
		#define PowerDownPanelTiming	1		// 1 ms
		#define PowerDownInvTiming		250		// 250 ms

    #endif

    #if PANEL == QD170E1

		#define PanelName				"QD170E1\r\n"
		#define PanelXga                0
		#define PanelSxga               1
		#define PanelUxga               0
		#define PanelTwoPixelPerClk     1       // Double pixels output 
		#define PanelDepth              8
		#define PanelSync_DE            0		//0=H/V 1=DE

		#define PanelWidth				1280
		#define PanelHeight				1024

		#define PanelMaxVFreq           77      // Hz
		#define PanelMinVFreq           47      // Hz
		#define PanelMaxHFreq           82000   // Hz

		#define PanelMaxPClk            140000   // KHz

		#define PanelMinHTotal          1460
		#define PanelMaxHTotal          1688
		#define PanelMinHSyncWidth      60
		#define PanelMinHSyncBackPorch  60
		#define PanelHSyncStart			PanelMinHTotal - PanelMinHSyncWidth - PanelMinHSyncBackPorch
		#define PanelHSyncEnd			PanelHSyncStart + PanelMinHSyncWidth
		#define PanelHActiveStart		PanelMinHSyncBackPorch + PanelMinHSyncWidth

		#define PanelMaxVTotal			2047
		#define PanelTypVTotal			1066
		#define PanelMinVTotal			1040
		#define PanelMinVSyncWidth      3
		#define PanelMinVSyncBackPorch  7
		#define PanelVSyncStart			PanelTypVTotal - PanelMinVSyncWidth - PanelMinVSyncBackPorch
		#define PanelVSyncEnd			PanelVSyncStart + PanelMinVSyncWidth
		#define PanelVActiveStart		PanelMinVSyncBackPorch + PanelMinVSyncWidth

		#define FreeRunH_Freq    		64000		//64KHz
		#define FreeRunV_Freq    		60			//60 Hz
		#define FreeRunVtotal    		1066		//1066 line
		#define PanelInterface			LVDS_TO_TCON
		#define PanelShortHsync			0
		#define Panel_Invert_DVS 		0xff
		#define Panel_Invert_DHS 		0xff
		#define Panel_Invert_DCLK 		0x00
		#define Panel_Invert_DEN 		0x00
		#define PanelPadDrive 			0x0333
		#define Panel_Spread_Spect_En	0xff	// 0xff : enable spectrum
												// 0x00 : disable spectrum
		#define PanelSpreadSpectrumCtrl 0x07
		// Value for Spread_Spectrum_Control register
		// 0x00: 0.097% ... 0x07: 12.5%

		// Panel dething mode
		#define PanelDethMode			0x31

		// define panel timing. word constant used to program registers 0xd8 and 0xd9 during power up and power down
		#define PowerUpPanelTiming		1		// 1 ms
		#define PowerUpInvTiming		250		// 250 ms
		#define PowerDownPanelTiming	1		// 1 ms
		#define PowerDownInvTiming		250		// 250 ms

    #endif

    #if PANEL == Samsung_LTM170E4_L01

		#define PanelName				"Samsung_LTM170E4_L01\r\n"
		#define PanelXga                0
		#define PanelSxga               1
		#define PanelUxga               0
		#define PanelTwoPixelPerClk     1       // Double pixels output 
		#define PanelDepth              6
		#define PanelSync_DE            0		//0=H/V 1=DE

		#define PanelWidth				1280
		#define PanelHeight				1024

		#define PanelMaxVFreq           75      // Hz
		#define PanelMinVFreq           56      // Hz
		#define PanelMaxHFreq           82000   // Hz

		#define PanelMaxPClk            140000   // KHz

		#define PanelMinHTotal          1520
		#define PanelMaxHTotal          1688
		#define PanelMinHSyncWidth      40
		#define PanelMinHSyncBackPorch  40
		#define PanelHSyncStart			PanelMinHTotal - PanelMinHSyncWidth - PanelMinHSyncBackPorch
		#define PanelHSyncEnd			PanelHSyncStart + PanelMinHSyncWidth
		#define PanelHActiveStart		PanelMinHSyncBackPorch + PanelMinHSyncWidth

		#define PanelMaxVTotal			1066
		#define PanelTypVTotal			1066
		#define PanelMinVTotal			1040
		#define PanelMinVSyncWidth      3
		#define PanelMinVSyncBackPorch  7
		#define PanelVSyncStart			PanelTypVTotal - PanelMinVSyncWidth - PanelMinVSyncBackPorch
		#define PanelVSyncEnd			PanelVSyncStart + PanelMinVSyncWidth
		#define PanelVActiveStart		PanelMinVSyncBackPorch + PanelMinVSyncWidth

		#define FreeRunH_Freq    		64000		//64KHz
		#define FreeRunV_Freq    		60			//60 Hz
		#define FreeRunVtotal    		1066		//1066 line
		#define PanelInterface			LVDS_TO_TCON
		#define PanelShortHsync			0
		#define Panel_Invert_DVS 		0xff
		#define Panel_Invert_DHS 		0xff
		#define Panel_Invert_DCLK 		0x00
		#define Panel_Invert_DEN 		0x00
		#define PanelPadDrive 			0x0333

		#define Panel_Spread_Spect_En	0xff	// 0xff : enable spectrum
												// 0x00 : disable spectrum
		#define PanelSpreadSpectrumCtrl 0x04
		// Value for Spread_Spectrum_Control register
		// 0x00: 0.097% ... 0x07: 12.5%

		// Panel dething mode
		#define PanelDethMode			0x33

		// define panel timing. word constant used to program registers 0xd8 and 0xd9 during power up and power down
		#define PowerUpPanelTiming		1		// 1 ms
		#define PowerUpInvTiming		250		// 250 ms
		#define PowerDownPanelTiming	1		// 1 ms
		#define PowerDownInvTiming		250		// 250 ms

    #endif

    #if PANEL == QD170ER01

		#define PanelName				"QD170ER01\r\n"
		#define PanelXga                0
		#define PanelSxga               1
		#define PanelUxga               0
		#define PanelTwoPixelPerClk     1       // Double pixels output 
		#define PanelDepth              6
		#define PanelSync_DE            0		//0=H/V 1=DE

		#define PanelWidth				1280
		#define PanelHeight				1024

		#define PanelMaxVFreq           75      // Hz
		#define PanelMinVFreq           56      // Hz
		#define PanelMaxHFreq           82000   // Hz

		#define PanelMaxPClk            140000   // KHz

		#define PanelMinHTotal          1460
		#define PanelMaxHTotal          1688
		#define PanelMinHSyncWidth      60
		#define PanelMinHSyncBackPorch  60
		#define PanelHSyncStart			PanelMinHTotal - PanelMinHSyncWidth - PanelMinHSyncBackPorch
		#define PanelHSyncEnd			PanelHSyncStart + PanelMinHSyncWidth
		#define PanelHActiveStart		PanelMinHSyncBackPorch + PanelMinHSyncWidth

		#define PanelMaxVTotal			2047
		#define PanelTypVTotal			1066
		#define PanelMinVTotal			1040
		#define PanelMinVSyncWidth      3
		#define PanelMinVSyncBackPorch  7
		#define PanelVSyncStart			PanelTypVTotal - PanelMinVSyncWidth - PanelMinVSyncBackPorch
		#define PanelVSyncEnd			PanelVSyncStart + PanelMinVSyncWidth
		#define PanelVActiveStart		PanelMinVSyncBackPorch + PanelMinVSyncWidth

		#define FreeRunH_Freq    		64000		//64KHz
		#define FreeRunV_Freq    		60			//60 Hz
		#define FreeRunVtotal    		1066		//1066 line
		#define PanelInterface			TCON_TO_RSDS
		#define PanelShortHsync			0
		#define Panel_Invert_DVS 		0xff
		#define Panel_Invert_DHS 		0xff
		#define Panel_Invert_DCLK 		0x00
		#define Panel_Invert_DEN 		0x00
		#define PanelPadDrive 			0x0333

		#define Panel_Spread_Spect_En	0xff	// 0xff : enable spectrum
												// 0x00 : disable spectrum
		#define PanelSpreadSpectrumCtrl 0x04
		// Value for Spread_Spectrum_Control register
		// 0x00: 0.097% ... 0x07: 12.5%

		// Panel dething mode
		#define PanelDethMode			0x31

		// define panel timing. word constant used to program registers 0xd8 and 0xd9 during power up and power down
		#define PowerUpPanelTiming		25		// 1 ms
		#define PowerUpInvTiming		250		// 250 ms
		#define PowerDownPanelTiming	1		// 1 ms
		#define PowerDownInvTiming		250		// 250 ms

    #endif

    #if PANEL == HyundaiHT17E12_100

		#define PanelName				"HyundaiHT17E12_100\r\n"
		#define PanelXga                0
		#define PanelSxga               1
		#define PanelUxga               0
		#define PanelTwoPixelPerClk     1       // Double pixels output 
		#define PanelDepth              6
		#define PanelSync_DE			0		//0=H/V mode 1=DE mode

		#define PanelWidth				1280
		#define PanelHeight				1024

		#define PanelMaxVFreq           75      // Hz
		#define PanelMinVFreq           50      // Hz
		#define PanelMaxHFreq           80000   // Hz

		#define PanelMaxPClk            136000   // KHz

		#define PanelMinHTotal          1480
		#define PanelMaxHTotal          2044
		#define PanelMinHSyncWidth      80
		#define PanelMinHSyncBackPorch  80
		#define PanelHSyncStart			PanelMinHTotal - PanelMinHSyncWidth - PanelMinHSyncBackPorch
		#define PanelHSyncEnd			PanelHSyncStart + PanelMinHSyncWidth
		#define PanelHActiveStart		PanelMinHSyncBackPorch + PanelMinHSyncWidth

		#define PanelMaxVTotal			1536
		#define PanelTypVTotal			1066
		#define PanelMinVTotal			1040
		#define PanelMinVSyncWidth      3
		#define PanelMinVSyncBackPorch  7
		#define PanelVSyncStart			PanelTypVTotal - PanelMinVSyncWidth - PanelMinVSyncBackPorch
		#define PanelVSyncEnd			PanelVSyncStart + PanelMinVSyncWidth
		#define PanelVActiveStart		PanelMinVSyncBackPorch + PanelMinVSyncWidth

		#define FreeRunH_Freq    		64000		//64KHz
		#define FreeRunV_Freq    		60			//60 Hz
		#define FreeRunVtotal    		1066		//1066 line
		#define PanelInterface			LVDS_TO_TCON
		#define PanelShortHsync			0
		#define Panel_Invert_DVS 		0xff
		#define Panel_Invert_DHS 		0xff
		#define Panel_Invert_DCLK 		0x00
		#define Panel_Invert_DEN 		0x00
		#define PanelPadDrive 			0x0333

		#define Panel_Spread_Spect_En	0xff	// 0xff : enable spectrum
												// 0x00 : disable spectrum
		#define PanelSpreadSpectrumCtrl 0x00
		// Value for Spread_Spectrum_Control register
		// 0x00: 0.097% ... 0x07: 12.5%

		// Panel dething mode
		#define PanelDethMode			0x31

		// define panel timing. word constant used to program registers 0xd8 and 0xd9 during power up and power down
		#define PowerUpPanelTiming		1		// 1 ms
		#define PowerUpInvTiming		250		// 250 ms
		#define PowerDownPanelTiming	1		// 1 ms
		#define PowerDownInvTiming		250		// 250 ms

		#define MinBrt 90
		#define MaxBrt 217

    #endif

    #if PANEL == AU_M150XN04_1

		#define PanelName				"AU_M150XN04_1\r\n"
		#define PanelXga                1
		#define PanelSxga               0
		#define PanelUxga               0
		#define PanelTwoPixelPerClk     1       // Double pixels output 
		#define PanelDepth              6
		#define PanelSync_DE			0

		#define PanelWidth				1024
		#define PanelHeight				768

		#define PanelMaxVFreq           75      // Hz
		#define PanelMinVFreq           48      // Hz
		#define PanelMaxHFreq           60000   // Hz

		#define PanelMaxPClk            80000   // KHz

		#define PanelMinHTotal          1200
		#define PanelMaxHTotal          1884
		#define PanelMinHSyncWidth      80
		#define PanelMinHSyncBackPorch  80
		#define PanelHSyncStart			PanelMinHTotal - PanelMinHSyncWidth - PanelMinHSyncBackPorch
		#define PanelHSyncEnd			PanelHSyncStart + PanelMinHSyncWidth
		#define PanelHActiveStart		PanelMinHSyncBackPorch + PanelMinHSyncWidth

		#define PanelMaxVTotal			1136
		#define PanelTypVTotal			806
		#define PanelMinVTotal			780
		#define PanelMinVSyncWidth      3
		#define PanelMinVSyncBackPorch  7
		#define PanelVSyncStart			PanelTypVTotal - PanelMinVSyncWidth - PanelMinVSyncBackPorch
		#define PanelVSyncEnd			PanelVSyncStart + PanelMinVSyncWidth
		#define PanelVActiveStart		PanelMinVSyncBackPorch + PanelMinVSyncWidth

		#define FreeRunH_Freq    		60000		//60KHz
		#define FreeRunV_Freq    		75			//75 Hz
		#define FreeRunVtotal    		800			//800 line
		#define PanelInterface			TTL_TO_TCON
		#define PanelShortHsync			0
		#define Panel_Invert_DVS 		0xff
		#define Panel_Invert_DHS 		0xff
		#define Panel_Invert_DCLK 		0x00
		#define Panel_Invert_DEN 		0x00
		#define PanelPadDrive 			0x0333

		#define Panel_Spread_Spect_En	0xff	// 0xff : enable spectrum
												// 0x00 : disable spectrum
		#define PanelSpreadSpectrumCtrl 0x00
		// Value for Spread_Spectrum_Control register
		// 0x00: 0.097% ... 0x07: 12.5%

		// Panel dething mode
		#define PanelDethMode			0x31

		// define panel timing. word constant used to program registers 0xd8 and 0xd9 during power up and power down
		#define PowerUpPanelTiming		1		// 1 ms
		#define PowerUpInvTiming		250		// 250 ms
		#define PowerDownPanelTiming	1		// 1 ms
		#define PowerDownInvTiming		250		// 250 ms

    #endif
    #if PANEL == FLC48SXC8V_10

		#define PanelName				"FLC48SX8V_10\r\n"
		#define PanelXga                0
		#define PanelSxga               1
		#define PanelUxga               0
		#define PanelTwoPixelPerClk     1       // Double pixels output 
		#define PanelDepth              8
		#define PanelSync_DE            0		//0=H/V 1=DE

		#define PanelWidth				1280
		#define PanelHeight				1024

		#define PanelMaxVFreq           77      // Hz
		#define PanelMinVFreq           47      // Hz
		#define PanelMaxHFreq           82000   // Hz

		#define PanelMaxPClk            140000   // KHz

		#define PanelMinHTotal          1560//1460
		#define PanelMaxHTotal          1688//1688
		#define PanelMinHSyncWidth      60
		#define PanelMinHSyncBackPorch  60
		#define PanelHSyncStart			PanelMinHTotal - PanelMinHSyncWidth - PanelMinHSyncBackPorch
		#define PanelHSyncEnd			PanelHSyncStart + PanelMinHSyncWidth
		#define PanelHActiveStart		PanelMinHSyncBackPorch + PanelMinHSyncWidth

		#define PanelMaxVTotal			2047
		#define PanelTypVTotal			1066
		#define PanelMinVTotal			1040
		#define PanelMinVSyncWidth      3
		#define PanelMinVSyncBackPorch  7
		#define PanelVSyncStart			PanelTypVTotal - PanelMinVSyncWidth - PanelMinVSyncBackPorch
		#define PanelVSyncEnd			PanelVSyncStart + PanelMinVSyncWidth
		#define PanelVActiveStart		PanelMinVSyncBackPorch + PanelMinVSyncWidth

		#define FreeRunH_Freq    		64000		//64KHz
		#define FreeRunV_Freq    		60			//60 Hz
		#define FreeRunVtotal    		1066		//1066 line
		#define PanelInterface			LVDS_TO_TCON
		#define PanelShortHsync			0
		#define Panel_Invert_DVS 		0xff
		#define Panel_Invert_DHS 		0xff
		#define Panel_Invert_DCLK 		0x00
		#define Panel_Invert_DEN 		0x00
		#define PanelPadDrive 			0x0333
		#define Panel_Spread_Spect_En	0xff	// 0xff : enable spectrum
												// 0x00 : disable spectrum
		#define PanelSpreadSpectrumCtrl 0x05
		// Value for Spread_Spectrum_Control register
		// 0x00: 0.097% ... 0x07: 12.5%

		// Panel dething mode
		#define PanelDethMode			0x31

		// define panel timing. word constant used to program registers 0xd8 and 0xd9 during power up and power down
		#define PowerUpPanelTiming		1		// 1 ms
		#define PowerUpInvTiming		250		// 250 ms
		#define PowerDownPanelTiming	1		// 1 ms
		#define PowerDownInvTiming		250		// 250 ms

    #endif
    #if PANEL == CMO_M170ES05

		#define PanelName				"CMO_M170ES05\r\n"
		#define PanelXga                0
		#define PanelSxga               1
		#define PanelUxga               0
		#define PanelTwoPixelPerClk     1       // Double pixels output 
		#define PanelDepth              6
		#define PanelSync_DE            0		//0=H/V 1=DE

		#define PanelWidth				1280
		#define PanelHeight				1024

		#define PanelMaxVFreq           75      // Hz
		#define PanelMinVFreq           56      // Hz
		#define PanelMaxHFreq           82000   // Hz

		#define PanelMaxPClk            140000   // KHz

		#define PanelMinHTotal          1688//1600
		#define PanelMaxHTotal          2046
		#define PanelMinHSyncWidth      80
		#define PanelMinHSyncBackPorch  80
		#define PanelHSyncStart			PanelMinHTotal - PanelMinHSyncWidth - PanelMinHSyncBackPorch
		#define PanelHSyncEnd			PanelHSyncStart + PanelMinHSyncWidth
		#define PanelHActiveStart		PanelMinHSyncBackPorch + PanelMinHSyncWidth

		#define PanelMaxVTotal			2047
		#define PanelTypVTotal			1066
		#define PanelMinVTotal			1040
		#define PanelMinVSyncWidth      3
		#define PanelMinVSyncBackPorch  7
		#define PanelVSyncStart			PanelTypVTotal - PanelMinVSyncWidth - PanelMinVSyncBackPorch
		#define PanelVSyncEnd			PanelVSyncStart + PanelMinVSyncWidth
		#define PanelVActiveStart		PanelMinVSyncBackPorch + PanelMinVSyncWidth

		#define FreeRunH_Freq    		64000		//64KHz
		#define FreeRunV_Freq    		60			//60 Hz
		#define FreeRunVtotal    		1066		//1066 line
		#define PanelInterface			TCON_TO_RSDS
		#define PanelShortHsync			0
		#define Panel_Invert_DVS 		0x00
		#define Panel_Invert_DHS 		0x00
		#define Panel_Invert_DCLK 		0x00
		#define Panel_Invert_DEN 		0x00
		#define PanelPadDrive 			0x0333

		#define Panel_Spread_Spect_En	0xff	// 0xff : enable spectrum
												// 0x00 : disable spectrum
		#define PanelSpreadSpectrumCtrl 0x04
		// Value for Spread_Spectrum_Control register
		// 0x00: 0.097% ... 0x07: 12.5%

		// Panel dething mode
		#define PanelDethMode			0x11

		// define panel timing. word constant used to program registers 0xd8 and 0xd9 during power up and power down
		#define PowerUpPanelTiming		60		// 1 ms
		#define PowerUpInvTiming		250		// 250 ms
		#define PowerDownPanelTiming	1		// 1 ms
		#define PowerDownInvTiming		250		// 250 ms

 		#define yuv2rgbXsRGB2rgb{	\
			{  0x12A1,  0x0000,  0x1989 },	\
			{  0x12A1, -0x0644, -0x0D01 },	\
			{  0x12A1,  0x2046,  0x0000 }	\
		}

    #endif  
    #if PANEL == Samsung_LTM213U4_L01

		#define PanelName				"Samsung_LTM213U4_L01\r\n"
		#define PanelXga                0
		#define PanelSxga               0
		#define PanelUxga               1
		#define PanelTwoPixelPerClk     1       // Double pixels output 
		#define PanelDepth              8
		#define PanelSync_DE            1		//0=H/V 1=DE

		#define PanelWidth				1600
		#define PanelHeight				1200

		#define PanelMaxVFreq           75      // Hz
		#define PanelMinVFreq           56      // Hz
		#define PanelMaxHFreq           136000   // Hz

		#define PanelMaxPClk            190000   // KHz

		#define PanelMinHTotal          1800
		#define PanelMaxHTotal          2260//2046
		#define PanelMinHSyncWidth      16
		#define PanelMinHSyncBackPorch  16
		#define PanelHSyncStart			PanelMinHTotal - PanelMinHSyncWidth - PanelMinHSyncBackPorch
		#define PanelHSyncEnd			PanelHSyncStart + PanelMinHSyncWidth
		#define PanelHActiveStart		PanelMinHSyncBackPorch + PanelMinHSyncWidth

		#define PanelMaxVTotal			1280//2047
		#define PanelTypVTotal			1066
		#define PanelMinVTotal			1207
		#define PanelMinVSyncWidth      3
		#define PanelMinVSyncBackPorch  7
		#define PanelVSyncStart			PanelTypVTotal - PanelMinVSyncWidth - PanelMinVSyncBackPorch
		#define PanelVSyncEnd			PanelVSyncStart + PanelMinVSyncWidth
		#define PanelVActiveStart		PanelMinVSyncBackPorch + PanelMinVSyncWidth

		#define FreeRunH_Freq    		64000		//64KHz
		#define FreeRunV_Freq    		60			//60 Hz
		#define FreeRunVtotal    		1066		//1066 line
		//#define Use_TCON 				0
		#define PanelInterface			LVDS_TO_TCON
		#define PanelShortHsync			0
		#define Panel_Invert_DVS 		0xff
		#define Panel_Invert_DHS 		0xff
		#define Panel_Invert_DCLK 		0x00
		#define Panel_Invert_DEN 		0x00
		#define PanelPadDrive 			0x0333

		#define Panel_Spread_Spect_En	0xff	// 0xff : enable spectrum
												// 0x00 : disable spectrum
		#define PanelSpreadSpectrumCtrl 0x00
		// Value for Spread_Spectrum_Control register
		// 0x00: 0.097% ... 0x07: 12.5%

		// Panel dething mode
		#define PanelDethMode			0x31

		// define panel timing. word constant used to program registers 0xd8 and 0xd9 during power up and power down
		#define PowerUpPanelTiming		1		// 1 ms
		#define PowerUpInvTiming		250		// 250 ms
		#define PowerDownPanelTiming	1		// 1 ms
		#define PowerDownInvTiming		250		// 250 ms

 		#define yuv2rgbXsRGB2rgb{	\
			{  0x12A1,  0x0000,  0x1989 },	\
			{  0x12A1, -0x0644, -0x0D01 },	\
			{  0x12A1,  0x2046,  0x0000 }	\
		}

    #endif    	
#if PANEL == LP_LM170E01

	#define PanelName				"LP_LM170E01\n"
	#define PanelXga				0
	#define PanelSxga				1
	#define PanelUxga				0
	#define PanelTwoPixelPerClk 	1		// Double pixels output 
	#define PanelDepth				6
	#define PanelSync_DE			0		//0=H/V 1=DE

	#define PanelWidth				1280
	#define PanelHeight 			1024

	#define PanelMaxVFreq			77		// Hz
	#define PanelMinVFreq			47		// Hz
	#define PanelMaxHFreq			82000	// Hz
	#define PanelMaxPClk			140000	 // KHz
	#define PanelMinHTotal			1480
	#define PanelMaxHTotal			1774	//1688
	#define PanelMinHSyncWidth		60
	#define PanelMinHSyncBackPorch	60
	#define PanelHSyncStart 		PanelMinHTotal - PanelMinHSyncWidth - PanelMinHSyncBackPorch
	#define PanelHSyncEnd			PanelHSyncStart + PanelMinHSyncWidth
	#define PanelHActiveStart		PanelMinHSyncBackPorch + PanelMinHSyncWidth

	#define PanelMaxVTotal			2047
	#define PanelTypVTotal			1066
	#define PanelMinVTotal			1040
	#define PanelMinVSyncWidth		3
	#define PanelMinVSyncBackPorch	7
	#define PanelVSyncStart 		PanelTypVTotal - PanelMinVSyncWidth - PanelMinVSyncBackPorch
	#define PanelVSyncEnd			PanelVSyncStart + PanelMinVSyncWidth
	#define PanelVActiveStart		PanelMinVSyncBackPorch + PanelMinVSyncWidth

	#define FreeRunH_Freq			64000		//64KHz
	#define FreeRunV_Freq			60			//60 Hz
	#define FreeRunVtotal			1066		//1066 line
	#define Use_TCON				0
	#define PanelInterface			LVDS_TO_TCON
	#define PanelShortHsync 		0
	#define Panel_Invert_DVS		0xff
	#define Panel_Invert_DHS		0xff
	#define Panel_Invert_DCLK		0x00
	#define Panel_Invert_DEN		0x00
	#define PanelPadDrive			0x0333
	#define PanelClockControl		0x20
		
	#define Panel_Spread_Spect_En	0xff	// 0xff : enable spectrum
												// 0x00 : disable spectrum
	#define PanelSpreadSpectrumCtrl 0x00
		// Value for Spread_Spectrum_Control register
		// 0x00: 0.097% ... 0x07: 12.5%

		// Panel dething mode
	#define PanelDethMode			0x23

		// define panel timing. word constant used to program registers 0xd8 and 0xd9 during power up and power down
	#define PowerUpPanelTiming		1		// 1 ms
	#define PowerUpInvTiming		250 	// 250 ms
	#define PowerDownPanelTiming	1		// 1 ms
	#define PowerDownInvTiming		250 	// 250 ms

	#define yuv2rgbXsRGB2rgb{	\
			{  0x12A1,  0x0000,  0x1989 },	\
			{  0x12A1, -0x0644, -0x0D01 },	\
			{  0x12A1,  0x2046,  0x0000 }	\
		}

#endif	  
#if PANEL == FUJ_FLC43XWC8V

	#define PanelName				"FUJ_FLC43XWC8V\r\n"
	#define PanelXga				1
	#define PanelSxga				0
	#define PanelUxga				0
	#define PanelTwoPixelPerClk 	0		// Double pixels output 
	#define PanelDepth				8
	#define PanelSync_DE			0

	#define PanelWidth				1280
	#define PanelHeight 			768

	#define PanelMaxVFreq			75		// Hz
	#define PanelMinVFreq			55		// Hz
	#define PanelMaxHFreq			62500	// Hz

	#define PanelMaxPClk			80000	// KHz

	#define PanelMinHTotal			1344
	#define PanelMaxHTotal			1884
	#define PanelMinHSyncWidth		20
	#define PanelMinHSyncBackPorch	20
	#define PanelHSyncStart 		PanelMinHTotal - PanelMinHSyncWidth - PanelMinHSyncBackPorch
	#define PanelHSyncEnd			PanelHSyncStart + PanelMinHSyncWidth
	#define PanelHActiveStart		PanelMinHSyncBackPorch + PanelMinHSyncWidth

	#define PanelMaxVTotal			1136
	#define PanelTypVTotal			806
	#define PanelMinVTotal			780
	#define PanelMinVSyncWidth		3
	#define PanelMinVSyncBackPorch	7
	#define PanelVSyncStart 		PanelTypVTotal - PanelMinVSyncWidth - PanelMinVSyncBackPorch
	#define PanelVSyncEnd			PanelVSyncStart + PanelMinVSyncWidth
	#define PanelVActiveStart		PanelMinVSyncBackPorch + PanelMinVSyncWidth

	#define FreeRunH_Freq			60000		//60KHz
	#define FreeRunV_Freq			75			//75 Hz
	#define FreeRunVtotal			800 		//800 line
	#define PanelInterface			LVDS_TO_TCON
	#define PanelShortHsync 		0
	#define Panel_Invert_DVS		0xff
	#define Panel_Invert_DHS		0xff
	#define Panel_Invert_DCLK		0x00
	#define Panel_Invert_DEN		0x00
	#define PanelPadDrive			0x0333

	#define Panel_Spread_Spect_En	0xff	// 0xff : enable spectrum
											// 0x00 : disable spectrum
	#define PanelSpreadSpectrumCtrl 0x00
	// Value for Spread_Spectrum_Control register
	// 0x00: 0.097% ... 0x07: 12.5%

	// Panel dething mode
	#define PanelDethMode			0x33

	// define panel timing. word constant used to program registers 0xd8 and 0xd9 during power up and power down
	#define PowerUpPanelTiming		1		// 1 ms
	#define PowerUpInvTiming		250 	// 250 ms
	#define PowerDownPanelTiming	1		// 1 ms
	#define PowerDownInvTiming		250 	// 250 ms

#endif
#if PANEL == AU_L170ES05

	#define PanelName				"CMO_M170ES05\r\n"
	#define PanelXga				0
	#define PanelSxga				1
	#define PanelUxga				0
	#define PanelTwoPixelPerClk 	1		// Double pixels output 
	#define PanelDepth				6
	#define PanelSync_DE			0		//0=H/V 1=DE

	#define PanelWidth				1280
	#define PanelHeight 			1024

	#define PanelMaxVFreq			75		// Hz
	#define PanelMinVFreq			56		// Hz
	#define PanelMaxHFreq			82000	// Hz

	#define PanelMaxPClk			140000	 // KHz

	#define PanelMinHTotal			1688//1600
	#define PanelMaxHTotal			2046
	#define PanelMinHSyncWidth		80
	#define PanelMinHSyncBackPorch	80
	#define PanelHSyncStart 		PanelMinHTotal - PanelMinHSyncWidth - PanelMinHSyncBackPorch
	#define PanelHSyncEnd			PanelHSyncStart + PanelMinHSyncWidth
	#define PanelHActiveStart		PanelMinHSyncBackPorch + PanelMinHSyncWidth

	#define PanelMaxVTotal			2047
	#define PanelTypVTotal			1066
	#define PanelMinVTotal			1040
	#define PanelMinVSyncWidth		3
	#define PanelMinVSyncBackPorch	7
	#define PanelVSyncStart 		PanelTypVTotal - PanelMinVSyncWidth - PanelMinVSyncBackPorch
	#define PanelVSyncEnd			PanelVSyncStart + PanelMinVSyncWidth
	#define PanelVActiveStart		PanelMinVSyncBackPorch + PanelMinVSyncWidth

	#define FreeRunH_Freq			64000		//64KHz
	#define FreeRunV_Freq			60			//60 Hz
	#define FreeRunVtotal			1066		//1066 line
	#define PanelInterface			TCON_TO_RSDS
	#define PanelShortHsync 		0
	#define Panel_Invert_DVS		0x00
	#define Panel_Invert_DHS		0x00
	#define Panel_Invert_DCLK		0x00
	#define Panel_Invert_DEN		0x00
	#define PanelPadDrive			0x0333

	#define Panel_Spread_Spect_En	0xff	// 0xff : enable spectrum
											// 0x00 : disable spectrum
	#define PanelSpreadSpectrumCtrl 0x04
	// Value for Spread_Spectrum_Control register
	// 0x00: 0.097% ... 0x07: 12.5%

	// Panel dething mode
	#define PanelDethMode			0x23

	// define panel timing. word constant used to program registers 0xd8 and 0xd9 during power up and power down
	#define PowerUpPanelTiming		60		// 1 ms
	#define PowerUpInvTiming		250 	// 250 ms
	#define PowerDownPanelTiming	1		// 1 ms
	#define PowerDownInvTiming		250 	// 250 ms

	#define yuv2rgbXsRGB2rgb{	\
		{  0x12A1,	0x0000,  0x1989 },	\
		{  0x12A1, -0x0644, -0x0D01 },	\
		{  0x12A1,	0x2046,  0x0000 }	\
	}

#endif	

#if PANEL == AUO_M201EW01

	#define PanelName				"AUO_M201EW01\r\n"
	#define PanelXga				0
	#define PanelSxga				1
	#define PanelUxga				0
	#define PanelTwoPixelPerClk 	1		// Double pixels output 
	#define PanelDepth				8
	#define PanelSync_DE			1		//0=H/V 1=DE

	#define PanelWidth				1680
	#define PanelHeight 			1050

	#define PanelMaxVFreq			75		// Hz
	#define PanelMinVFreq			56		// Hz
	#define PanelMaxHFreq			82000	// Hz

	#define PanelMaxPClk			170000	 // KHz

	#define PanelMinHTotal			1800
	#define PanelMaxHTotal			2800
	#define PanelMinHSyncWidth		40
	#define PanelMinHSyncBackPorch	40
	#define PanelHSyncStart 		PanelMinHTotal - PanelMinHSyncWidth - PanelMinHSyncBackPorch
	#define PanelHSyncEnd			PanelHSyncStart + PanelMinHSyncWidth
	#define PanelHActiveStart		PanelMinHSyncBackPorch + PanelMinHSyncWidth

	#define PanelMaxVTotal			1600
	#define PanelTypVTotal			1072
	#define PanelMinVTotal			1061
	#define PanelMinVSyncWidth		3
	#define PanelMinVSyncBackPorch	7
	#define PanelVSyncStart 		PanelTypVTotal - PanelMinVSyncWidth - PanelMinVSyncBackPorch
	#define PanelVSyncEnd			PanelVSyncStart + PanelMinVSyncWidth
	#define PanelVActiveStart		PanelMinVSyncBackPorch + PanelMinVSyncWidth

	#define FreeRunH_Freq			64000		//64KHz
	#define FreeRunV_Freq			60			//60 Hz
	#define FreeRunVtotal			1066		//1066 line
	#define PanelInterface			LVDS_TO_TCON
	#define PanelShortHsync 		0
	#define Panel_Invert_DVS		0xff
	#define Panel_Invert_DHS		0xff
	#define Panel_Invert_DCLK		0x00
	#define Panel_Invert_DEN		0x00
	#define PanelPadDrive			0x0333

	#define Panel_Spread_Spect_En	0xff	// 0xff : enable spectrum
											// 0x00 : disable spectrum
	#define PanelSpreadSpectrumCtrl 0x04
	// Value for Spread_Spectrum_Control register
	// 0x00: 0.097% ... 0x07: 12.5%

	// Panel dething mode
	#define PanelDethMode			0x33

	// define panel timing. word constant used to program registers 0xd8 and 0xd9 during power up and power down
	#define PowerUpPanelTiming		1		// 1 ms
	#define PowerUpInvTiming		250 	// 250 ms
	#define PowerDownPanelTiming	1		// 1 ms
	#define PowerDownInvTiming		250 	// 250 ms

#endif
#if PANEL == Samsung_LTM150XH_L04

	#define PanelName				"Samsung_LTM150XH_L04\r\n"
	#define PanelXga				1
	#define PanelSxga				0
	#define PanelUxga				0
	#define PanelTwoPixelPerClk 	0		// Double pixels output 
	#define PanelDepth				6
	#define PanelSync_DE			0

	#define PanelWidth				1024
	#define PanelHeight 			768

	#define PanelMaxVFreq			75		// Hz
	#define PanelMinVFreq			55		// Hz
	#define PanelMaxHFreq			62500	// Hz

	#define PanelMaxPClk			80000	// KHz

	#define PanelMinHTotal			1200
	#define PanelMaxHTotal			1800
	#define PanelMinHSyncWidth		20
	#define PanelMinHSyncBackPorch	20
	#define PanelHSyncStart 		PanelMinHTotal - PanelMinHSyncWidth - PanelMinHSyncBackPorch
	#define PanelHSyncEnd			PanelHSyncStart + PanelMinHSyncWidth
	#define PanelHActiveStart		PanelMinHSyncBackPorch + PanelMinHSyncWidth

	#define PanelMaxVTotal			1136
	#define PanelTypVTotal			806
	#define PanelMinVTotal			780
	#define PanelMinVSyncWidth		3
	#define PanelMinVSyncBackPorch	7
	#define PanelVSyncStart 		PanelTypVTotal - PanelMinVSyncWidth - PanelMinVSyncBackPorch
	#define PanelVSyncEnd			PanelVSyncStart + PanelMinVSyncWidth
	#define PanelVActiveStart		PanelMinVSyncBackPorch + PanelMinVSyncWidth

	#define FreeRunH_Freq			60000		//60KHz
	#define FreeRunV_Freq			75			//75 Hz
	#define FreeRunVtotal			800 		//800 line
	#define PanelInterface			LVDS_TO_TCON
	#define PanelShortHsync 		0
	#define Panel_Invert_DVS		0xff
	#define Panel_Invert_DHS		0xff
	#define Panel_Invert_DCLK		0x00
	#define Panel_Invert_DEN		0x00
	#define PanelPadDrive			0x0333

	#define Panel_Spread_Spect_En	0xff	// 0xff : enable spectrum
											// 0x00 : disable spectrum
	#define PanelSpreadSpectrumCtrl 0x00
	// Value for Spread_Spectrum_Control register
	// 0x00: 0.097% ... 0x07: 12.5%

	// Panel dething mode
	#define PanelDethMode			0x33

	// define panel timing. word constant used to program registers 0xd8 and 0xd9 during power up and power down
	#define PowerUpPanelTiming		1		// 1 ms
	#define PowerUpInvTiming		250 	// 250 ms
	#define PowerDownPanelTiming	1		// 1 ms
	#define PowerDownInvTiming		250 	// 250 ms

#endif
#if PANEL == Sharp_FG170M1LA04

	#define PanelName				"Sharp_FG170M1LA04\r\n"
	#define PanelXga				0
	#define PanelSxga				0
	#define PanelUxga				1
	#define PanelTwoPixelPerClk 	1		// Double pixels output 
	#define PanelDepth				6
	#define PanelSync_DE			1		//0=H/V 1=DE

	//#define PanelWidth				1600
	#define PanelWidth				1920
	#define PanelHeight 			1200

	#define PanelMaxVFreq			75		// Hz
	#define PanelMinVFreq			56		// Hz
	#define PanelMaxHFreq			136000	 // Hz

	#define PanelMaxPClk			190000	 // KHz

	#define PanelMinHTotal			1960
	//#define PanelMinHTotal		  1800
	#define PanelMaxHTotal			2260//2046
	#define PanelMinHSyncWidth		16
	#define PanelMinHSyncBackPorch	16
	#define PanelHSyncStart 		PanelMinHTotal - PanelMinHSyncWidth - PanelMinHSyncBackPorch
	#define PanelHSyncEnd			PanelHSyncStart + PanelMinHSyncWidth
	#define PanelHActiveStart		PanelMinHSyncBackPorch + PanelMinHSyncWidth

	#define PanelMaxVTotal			1280//2047
	#define PanelTypVTotal			1066
	#define PanelMinVTotal			1207
	#define PanelMinVSyncWidth		3
	#define PanelMinVSyncBackPorch	7
	#define PanelVSyncStart 		PanelTypVTotal - PanelMinVSyncWidth - PanelMinVSyncBackPorch
	#define PanelVSyncEnd			PanelVSyncStart + PanelMinVSyncWidth
	#define PanelVActiveStart		PanelMinVSyncBackPorch + PanelMinVSyncWidth

	#define FreeRunH_Freq			64000		//64KHz
	#define FreeRunV_Freq			60			//60 Hz
	#define FreeRunVtotal			1066		//1066 line
	//#define Use_TCON				0
	#define PanelInterface			LVDS_TO_TCON
	#define PanelShortHsync 		0
	#define Panel_Invert_DVS		0xff
	#define Panel_Invert_DHS		0xff
	#define Panel_Invert_DCLK		0x00
	#define Panel_Invert_DEN		0x00
	#define PanelPadDrive			0x0333

	#define Panel_Spread_Spect_En	0x00	// 0xff : enable spectrum
											// 0x00 : disable spectrum
	#define PanelSpreadSpectrumCtrl 0x00
	// Value for Spread_Spectrum_Control register
	// 0x00: 0.097% ... 0x07: 12.5%

	// Panel dething mode
	#define PanelDethMode			0x33

	// define panel timing. word constant used to program registers 0xd8 and 0xd9 during power up and power down
	#define PowerUpPanelTiming		1		// 1 ms
	#define PowerUpInvTiming		250 	// 250 ms
	#define PowerDownPanelTiming	1		// 1 ms
	#define PowerDownInvTiming		250 	// 250 ms

	#define yuv2rgbXsRGB2rgb{	\
		{  0x12A1,	0x0000,  0x1989 },	\
		{  0x12A1, -0x0644, -0x0D01 },	\
		{  0x12A1,	0x2046,  0x0000 }	\
	}

#endif	

#endif // __PANEL_H__
