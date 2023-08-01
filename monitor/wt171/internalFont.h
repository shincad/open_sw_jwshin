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

   2003-01-10 2:39坷饶  JDHAN           Modified for Monitor-TV
****************************************************************************/
//------------------------------------------------------------------------------
// ROW ADDRESSING FOR ATTRIBUTE REGISTERS
//------------------------------------------------------------------------------
#define	IN_ATTR_ROW0	0xA0
#define	IN_ATTR_ROW1	0xA1
#define	IN_ATTR_ROW2	0xA2
#define	IN_ATTR_ROW3	0xA3
#define	IN_ATTR_ROW4	0xA4
#define IN_ATTR_ROW5	0xA5
#define	IN_ATTR_ROW6	0xA6
#define	IN_ATTR_ROW7	0xA7
#define	IN_ATTR_ROW8	0xA8
#define	IN_ATTR_ROW9	0xA9
#define	IN_ATTR_ROW10	0xAA
#define	IN_ATTR_ROW11	0xAB
#define	IN_ATTR_ROW12	0xAC
#define	IN_ATTR_ROW13	0xAD
#define	IN_ATTR_ROW14	0xAE
#define	IN_ATTR_ROW15	0xAF

//------------------------------------------------------------------------------
// ROW ADDRESSING FOR DISPLAY AREA
//------------------------------------------------------------------------------
#define	IN_DSP_ROW0	0x80
#define	IN_DSP_ROW1	0x81
#define	IN_DSP_ROW2	0x82
#define	IN_DSP_ROW3	0x83
#define	IN_DSP_ROW4	0x84
#define	IN_DSP_ROW5	0x85
#define	IN_DSP_ROW6	0x86
#define	IN_DSP_ROW7	0x87
#define	IN_DSP_ROW8	0x88
#define	IN_DSP_ROW9	0x89
#define IN_DSP_ROW10 	0x8A
#define	IN_DSP_ROW11 	0x8B
#define	IN_DSP_ROW12 	0x8C
#define	IN_DSP_ROW13 	0x8D
#define	IN_DSP_ROW14 	0x8E
#define	IN_DSP_ROW15 	0x8F	// DUMMY 

//------------------------------------------------------------------------------
// CIC & RCI COLUMN ADDRESSING FOR DATA AREA  (A,B 规过)
//------------------------------------------------------------------------------
#define	IN_CIC_COL0	0x00
#define	IN_CIC_COL1	0x01
#define	IN_CIC_COL2	0x02
#define	IN_CIC_COL3	0x03
#define	IN_CIC_COL4	0x04
#define	IN_CIC_COL5	0x05
#define	IN_CIC_COL6	0x06
#define	IN_CIC_COL7	0x07
#define IN_CIC_COL8	0x08
#define	IN_CIC_COL9	0x09
#define	IN_CIC_COL10	0x0A
#define	IN_CIC_COL11	0x0B
#define	IN_CIC_COL12	0x0C
#define	IN_CIC_COL13	0x0D
#define	IN_CIC_COL14	0x0E
#define	IN_CIC_COL15	0x0F
#define	IN_CIC_COL16	0x10
#define	IN_CIC_COL17	0x11
#define	IN_CIC_COL18	0x12
#define	IN_CIC_COL19	0x13
#define	IN_CIC_COL20	0x14
#define	IN_CIC_COL21	0x15
#define	IN_CIC_COL22	0x16
#define	IN_CIC_COL23	0x17
#define	IN_CIC_COL24	0x18
#define IN_CIC_COL25	0x19
#define	IN_CIC_COL26	0x1A
#define	IN_CIC_COL27	0x1B
#define	IN_CIC_COL28	0x1C
#define	IN_CIC_COL29	0x1D
#define	IN_CIC_COL30	0x1E
#define	IN_CIC_COL31	0x1F	// DUMMY 

//------------------------------------------------------------------------------
// CII COLUMN ADDRESSING FOR DISPLAY AREA ( C 规过)
//------------------------------------------------------------------------------
#define	IN_CII_COL0	0x40
#define	IN_CII_COL1	0x41
#define	IN_CII_COL2	0x42
#define	IN_CII_COL3	0x43
#define	IN_CII_COL4	0x44
#define	IN_CII_COL5	0x45
#define	IN_CII_COL6	0x46
#define IN_CII_COL7	0x47
#define	IN_CII_COL8	0x48
#define	IN_CII_COL9	0x49
#define	IN_CII_COL10	0x4A
#define	IN_CII_COL11	0x4B
#define	IN_CII_COL12	0x4C
#define	IN_CII_COL13	0x4D
#define	IN_CII_COL14	0x4E
#define	IN_CII_COL15	0x4F
#define	IN_CII_COL16	0x50
#define	IN_CII_COL17	0x51
#define	IN_CII_COL18	0x52
#define	IN_CII_COL19	0x53
#define	IN_CII_COL20	0x54
#define	IN_CII_COL21	0x55
#define	IN_CII_COL22	0x56
#define	IN_CII_COL23	0x57
#define IN_CII_COL24	0x58
#define	IN_CII_COL25	0x59
#define	IN_CII_COL26	0x5A
#define	IN_CII_COL27	0x5B
#define	IN_CII_COL28	0x5C
#define	IN_CII_COL29	0x5D
#define	IN_CII_COL30	0x5E
#define	IN_CII_COL31	0x5F	// DUMMY 

//------------------------------------------------------------------------------
// WINDOW START OF ROW
//------------------------------------------------------------------------------
#define	IN_WIN_SROW0	0x00
#define	IN_WIN_SROW1	0x10
#define	IN_WIN_SROW2	0x20
#define	IN_WIN_SROW3	0x30
#define	IN_WIN_SROW4	0x40
#define	IN_WIN_SROW5	0x50
#define	IN_WIN_SROW6	0x60
#define IN_WIN_SROW7	0x70
#define	IN_WIN_SROW8	0x80
#define	IN_WIN_SROW9	0x90
#define	IN_WIN_SROW10	0xA0
#define	IN_WIN_SROW11	0xB0
#define	IN_WIN_SROW12	0xC0
#define	IN_WIN_SROW13	0xD0
#define	IN_WIN_SROW14	0xE0

//------------------------------------------------------------------------------
// WINDOW END OF ROW
//------------------------------------------------------------------------------
#define	IN_WIN_EROW0	0x00
#define	IN_WIN_EROW1	0x01
#define	IN_WIN_EROW2	0x02
#define	IN_WIN_EROW3	0x03
#define	IN_WIN_EROW4	0x04
#define	IN_WIN_EROW5	0x05
#define IN_WIN_EROW6	0x06
#define	IN_WIN_EROW7	0x07
#define	IN_WIN_EROW8	0x08
#define	IN_WIN_EROW9	0x09
#define	IN_WIN_EROW10	0x0A
#define	IN_WIN_EROW11	0x0B
#define	IN_WIN_EROW12	0x0C
#define	IN_WIN_EROW13	0x0D
#define	IN_WIN_EROW14	0x0E
#define	IN_WIN_EROW15	0x0F

/*
#define	IN_WIN_EROW0	0x01
#define	IN_WIN_EROW1	0x02
#define	IN_WIN_EROW2	0x03
#define	IN_WIN_EROW3	0x04
#define	IN_WIN_EROW4	0x05
#define	IN_WIN_EROW5	0x06
#define IN_WIN_EROW6	0x07
#define	IN_WIN_EROW7	0x08
#define	IN_WIN_EROW8	0x09
#define	IN_WIN_EROW9	0x0A
#define	IN_WIN_EROW10	0x0B
#define	IN_WIN_EROW11	0x0C
#define	IN_WIN_EROW12	0x0D
#define	IN_WIN_EROW13	0x0E
#define	IN_WIN_EROW14	0x0F
*/                    
//------------------------------------------------------------------------------
// WINDOW COLUMN NO.
//------------------------------------------------------------------------------
#define	IN_WIN_COL0	0x00
#define	IN_WIN_COL1	0x08
#define	IN_WIN_COL2	0x10
#define	IN_WIN_COL3	0x18
#define	IN_WIN_COL4	0x20
#define IN_WIN_COL5	0x28
#define	IN_WIN_COL6	0x30
#define	IN_WIN_COL7	0x38
#define	IN_WIN_COL8	0x40
#define	IN_WIN_COL9	0x48
#define	IN_WIN_COL10	0x50
#define	IN_WIN_COL11	0x58
#define	IN_WIN_COL12	0x60
#define	IN_WIN_COL13	0x68
#define	IN_WIN_COL14	0x70
#define	IN_WIN_COL15	0x78
#define	IN_WIN_COL16	0x80
#define	IN_WIN_COL17	0x88
#define	IN_WIN_COL18	0x90
#define	IN_WIN_COL19	0x98
#define	IN_WIN_COL20	0xA0
#define	IN_WIN_COL21	0xA8
#define IN_WIN_COL22	0xB0
#define	IN_WIN_COL23	0xB8
#define	IN_WIN_COL24	0xC0
#define	IN_WIN_COL25	0xC8
#define	IN_WIN_COL26	0xD0
#define	IN_WIN_COL27	0xD8
#define	IN_WIN_COL28	0xE0
#define	IN_WIN_COL29	0xE8
#define	IN_WIN_COL30	0xF0
#define	IN_WIN_COL31	0xF8

//------------------------------------------------------------------------------
// WINDOW REGISTER
//------------------------------------------------------------------------------
#define	IN_WIN_CTRL	IN_ATTR_ROW15
#define	IN_WIN_ENB	0x04	// %00000100
#define	IN_WIN_DIS	0x04^0xFF
#define	IN_WIN_INT	0x02	// %00000010
#define	IN_WIN_UNINT	0x02^0xFF
#define	IN_WIN_COLOREXT	0x01	// %00000001
#define IN_WIN_COLORUNEXT	0x01^0xFF

//------------------------------------------------------------------------------
// Color Define
//------------------------------------------------------------------------------
#define OSDFBLACK	0		//%00000000
#define	OSDFRED		0x04		//%00000100
#define	OSDFGREEN	0x02		//%00000010
#define	OSDFBLUE	0x01		//%00000001
#define	OSDFMAGEN	(OSDFRED+OSDFBLUE)
#define	OSDFCYAN	(OSDFBLUE+OSDFGREEN)
#define	OSDFYELLOW	(OSDFRED+OSDFGREEN)
#define	OSDFWHITE	(OSDFRED+OSDFGREEN+OSDFBLUE)

#define	IN_OSD_RED		0x04			//%00000100
#define	IN_OSD_GREEN	0x02			//%00000010
#define	IN_OSD_BLUE		0x01			//%00000001
#define	IN_OSD_BLACK	0x00
#define	IN_OSD_MAGEN	IN_OSD_RED+IN_OSD_BLUE
#define	IN_OSD_CYAN	IN_OSD_BLUE+IN_OSD_GREEN
#define	IN_OSD_YELLOW	IN_OSD_RED+IN_OSD_GREEN
#define	IN_OSD_WHITE	IN_OSD_RED+IN_OSD_BLUE+IN_OSD_GREEN


//------------------------------------------------------------------------------
// OSD Delay
//------------------------------------------------------------------------------
#define	IN_OsdVDelay  	0x67
#define	IN_OsdHDelay  	0x30


//------------------------------------------------------------------------------
// Font Define
//------------------------------------------------------------------------------	
//------------------------------------------------------------------------------
// Font Define
//------------------------------------------------------------------------------	
#define	_4LPrgsBarMax_IN	0x0D
#define	_4LPrgsBar3_IN		0x0C
#define	_4LPrgsBar2_IN		0x0B
#define	_4LPrgsBar1_IN		0x0A
			
#define	_plus_IN		0x2B
#define	_minus_IN		0x2D
#define	_dot_IN			0x2E
#define	_slash_IN		0x2F
#define	_Chdot_IN		0x3A
#define	_rightangle_IN		0x3E
#define	_LTriAngle_IN		0x5E
#define	_RTriAngle_IN		0x5F

#define	_bar2_IN		0x7B
#define	_bar1arr_IN		0x7C
#define	_arrbar_IN		0x7D

#define	_righthand_IN		0x97
#define	_2iPipL_IN		0xC8
#define	_2iPipR_IN		0xC9
#define	_2iPositionL_IN		0xCA
#define	_2iPositionR_IN		0xCB
#define	_2iSetupL_IN		0xD4
#define	_2iSetupR_IN		0xD5
#define	_2iBrightnessL_IN	0xDE
#define	_2iBrightnessR_IN	0xDF
#define	_2iColorL_IN		0xE0
#define	_2iColorR_IN		0xE1
#define	_2iExitL_IN		0xE2
#define	_2iExitR_IN		0xE3
#define	_2iChannelL_IN		0xF0
#define	_2iChannelR_IN		0xF1
#define	_2iLockMenuL_IN		0xF2
#define	_2iLockMenuR_IN		0xF3

#define	_2iCenterPositionL_IN		0x00
#define	_2iCenterPositionR_IN		0x00
#define	_2iRightTopPositionR_IN		0x00
#define	_2iRightTopPositionL_IN		0x00
#define	_2iRightBottomPositionR_IN	0x00
#define	_2iLeftBottomPositionL_IN	0x00
#define	_2iLeftBottomPositionR_IN	0x00
#define	_2iLeftTopPositionL_IN		0x00
#define	_2iLeftTopPositionR_IN		0x00			