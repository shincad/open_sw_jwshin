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
// ROW ADDRESSING FOR DISPLAY AREA
//------------------------------------------------------------------------------
#define	DSP_ROW0	0x00
#define	DSP_ROW1	0x01
#define	DSP_ROW2	0x02
#define	DSP_ROW3	0x03
#define	DSP_ROW4	0x04
#define	DSP_ROW5	0x05
#define	DSP_ROW6	0x06
#define	DSP_ROW7	0x07
#define	DSP_ROW8	0x08
#define	DSP_ROW9	0x09
#define DSP_ROW10	0x0A
#define	DSP_ROW11	0x0B
#define	DSP_ROW12	0x0C
#define	DSP_ROW13	0x0D
#define	DSP_ROW14	0x0E
#define	DSP_ROW15	0x0F	// DUMMY 

//------------------------------------------------------------------------------
// ROW ADDRESSING FOR DISPLAY AREA
//------------------------------------------------------------------------------
#define	DSP2_ROW0	0x80  // 8: display register
#define	DSP2_ROW1	0x81
#define	DSP2_ROW2	0x82
#define	DSP2_ROW3	0x83
#define	DSP2_ROW4	0x84
#define	DSP2_ROW5	0x85
#define	DSP2_ROW6	0x86
#define	DSP2_ROW7	0x87
#define	DSP2_ROW8	0x88
#define	DSP2_ROW9	0x89
#define DSP2_ROW10	0x8A
#define	DSP2_ROW11	0x8B
#define	DSP2_ROW12	0x8C
#define	DSP2_ROW13	0x8D
#define	DSP2_ROW14	0x8E
#define	DSP2_ROW15	0x8F	// DUMMY 

//------------------------------------------------------------------------------
// CII COLUMN ADDRESSING FOR DISPLAY AREA
//------------------------------------------------------------------------------
#define	CII_COL0	0x00
#define	CII_COL1	0x01
#define	CII_COL2	0x02
#define	CII_COL3	0x03
#define	CII_COL4	0x04
#define	CII_COL5	0x05
#define	CII_COL6	0x06
#define CII_COL7	0x07
#define	CII_COL8	0x08
#define	CII_COL9	0x09
#define	CII_COL10	0x0A
#define	CII_COL11	0x0B
#define	CII_COL12	0x0C
#define	CII_COL13	0x0D
#define	CII_COL14	0x0E
#define	CII_COL15	0x0F
#define	CII_COL16	0x10
#define	CII_COL17	0x11
#define	CII_COL18	0x12
#define	CII_COL19	0x13
#define	CII_COL20	0x14
#define	CII_COL21	0x15
#define	CII_COL22	0x16
#define	CII_COL23	0x17
#define CII_COL24	0x18
#define	CII_COL25	0x19
#define	CII_COL26	0x1A
#define	CII_COL27	0x1B
#define	CII_COL28	0x1C
#define	CII_COL29	0x1D
#define	CII_COL30	0x1E
#define	CII_COL31	0x1F	// DUMMY 

//------------------------------------------------------------------------------
// ROW ADDRESSING FOR ATTRIBUTE REGISTERS
//------------------------------------------------------------------------------
#define	ATTR_ROW0	0x40  // 8: display register
#define	ATTR_ROW1	0x41
#define	ATTR_ROW2	0x42
#define	ATTR_ROW3	0x43
#define	ATTR_ROW4	0x44
#define	ATTR_ROW5	0x45
#define	ATTR_ROW6	0x46
#define	ATTR_ROW7	0x47
#define	ATTR_ROW8	0x48
#define	ATTR_ROW9	0x49
#define ATTR_ROW10	0x4A
#define	ATTR_ROW11	0x4B
#define	ATTR_ROW12	0x4C
#define	ATTR_ROW13	0x4D
#define	ATTR_ROW14	0x4E
#define	ATTR_ROW15	0x4F	// DUMMY

//------------------------------------------------------------------------------
// WINDOW START OF ROW
//------------------------------------------------------------------------------
#define	WIN_SROW0	0x00
#define	WIN_SROW1	0x10
#define	WIN_SROW2	0x20
#define	WIN_SROW3	0x30
#define	WIN_SROW4	0x40
#define	WIN_SROW5	0x50
#define	WIN_SROW6	0x60
#define WIN_SROW7	0x70
#define	WIN_SROW8	0x80
#define	WIN_SROW9	0x90
#define	WIN_SROW10	0xA0
#define	WIN_SROW11	0xB0
#define	WIN_SROW12	0xC0
#define	WIN_SROW13	0xD0
#define	WIN_SROW14	0xE0
#define	WIN_SROW15	0xF0

//------------------------------------------------------------------------------
// WINDOW END OF ROW
//------------------------------------------------------------------------------
#define	WIN_EROW0	0x00
#define	WIN_EROW1	0x01
#define	WIN_EROW2	0x02
#define	WIN_EROW3	0x03
#define	WIN_EROW4	0x04
#define	WIN_EROW5	0x05
#define WIN_EROW6	0x06
#define	WIN_EROW7	0x07
#define	WIN_EROW8	0x08
#define	WIN_EROW9	0x09
#define	WIN_EROW10	0x0a
#define	WIN_EROW11	0x0b
#define	WIN_EROW12	0x0c
#define	WIN_EROW13	0x0d
#define	WIN_EROW14	0x0e
#define	WIN_EROW15	0x0f
                    
//------------------------------------------------------------------------------
// WINDOW COLUMN NO.
//------------------------------------------------------------------------------
#define	WIN_COL0	0x00
#define	WIN_COL1	0x08
#define	WIN_COL2	0x10
#define	WIN_COL3	0x18
#define	WIN_COL4	0x20
#define WIN_COL5	0x28
#define	WIN_COL6	0x30
#define	WIN_COL7	0x38
#define	WIN_COL8	0x40
#define	WIN_COL9	0x48
#define	WIN_COL10	0x50
#define	WIN_COL11	0x58
#define	WIN_COL12	0x60
#define	WIN_COL13	0x68
#define	WIN_COL14	0x70
#define	WIN_COL15	0x78
#define	WIN_COL16	0x80
#define	WIN_COL17	0x88
#define	WIN_COL18	0x90
#define	WIN_COL19	0x98
#define	WIN_COL20	0xA0
#define	WIN_COL21	0xA8
#define WIN_COL22	0xB0
#define	WIN_COL23	0xB8
#define	WIN_COL24	0xC0
#define	WIN_COL25	0xC8
#define	WIN_COL26	0xD0
#define	WIN_COL27	0xD8
#define	WIN_COL28	0xE0
#define	WIN_COL29	0xE8

//------------------------------------------------------------------------------
// WINDOW REGISTER
//------------------------------------------------------------------------------
#define WIN_ENA		0x04
#define	WIN_ENB		0x04	// %00000100
#define	WIN_DIS		0xfb
#define	WIN_INT		0x02	// %00000010
#define	WIN_UNINT	0xfd
#define	WIN_SHD		0x01	// %00000001S
#define WIN_UNSHD	0xfe

//------------------------------------------------------------------------------
// Color Define
//------------------------------------------------------------------------------
#define	CH_BLINK	0x08			//%00001000
#define	CH_UNBLINK	~CH_BLINK		//%11110111
#define OSD_BLACK	0			//%00000000
#define	OSD_RED		0x04			//%00000100
#define	OSD_GREEN	0x02			//%00000010
#define	OSD_BLUE	0x01			//%00000001

#define	OSD_RED_BG		0x40			//%01000000
#define	OSD_GREEN_BG	0x20			//%00100000
#define	OSD_BLUE_BG		0x10			//%00010000

#define	OSD_WHITE_BG	OSD_RED_BG+OSD_GREEN_BG+OSD_BLUE_BG	//0x70
#define	OSD_MAGEN_BG	OSD_RED_BG+OSD_BLUE_BG	
#define	OSD_CYAN_BG	OSD_BLUE_BG+OSD_GREEN_BG
#define	OSD_YELLOW_BG	OSD_RED_BG+OSD_GREEN_BG	

#define	OSD_MAGEN	OSD_RED+OSD_BLUE		//0x05
#define	OSD_CYAN	OSD_BLUE+OSD_GREEN		//0x03
#define	OSD_YELLOW	OSD_RED+OSD_GREEN		//0x06
#define	OSD_WHITE	OSD_RED+OSD_BLUE+OSD_GREEN	//0x07

//------------------------------------------------------------------------------
// OSD double define
//------------------------------------------------------------------------------
#define	Hchar_dbl	0x01	//double hieght charater, to the respective row
#define	Vchar_dbl	0x02	//double width charater
#define	HVchar_dbl	0x03	//double hieght/width charater


//------------------------------------------------------------------------------
// OSD Delay
//------------------------------------------------------------------------------
#define	OsdVDelay  	0x67
#define	OsdHDelay  	0x30


#include "BtcFontDef.h"		//2003-04-15	font 변경


//AnalogMainWindow
//DigitalMainWindow
//CompositeMainwindow
//S_videoMainWindow
//TunerMainWindow
//PIPMainWindow
#if !defined(INT_EXTOSD)   
code BYTE TOPWINDOW[] = {
//WINDOW1
	(WIN_SROW2|WIN_EROW2),		  		//WIN1 HEIGHT
	(WIN_COL0|WIN_ENA|WIN_INT&WIN_UNSHD), 		//WIN1 COL START & CTRL
	(WIN_COL28|OSD_WHITE),//OSD_CYAN),				//WIN1 COL END & COLOR
//WINDOW2
	(WIN_SROW3|WIN_EROW9),		  		//WIN2 HEIGHT
	(WIN_COL0&WIN_DIS|WIN_INT&WIN_UNSHD), 		//WIN2 COL START & CTRL
	(WIN_COL28|OSD_WHITE),				//WIN2 COL END & COLOR
//WINDOW3
	(WIN_SROW2|WIN_EROW11),				//WIN3 HEIGHT
	(WIN_COL0&WIN_DIS|WIN_INT&WIN_UNSHD),		//WIN3 COL START & CTRL
	(WIN_COL28|OSD_WHITE),//OSD_CYAN),				//WIN3 COL END & COLOR
//WINDOW4
	(WIN_SROW1|WIN_EROW12),				//WIN4 HEIGHT
	(WIN_COL0|WIN_ENA|WIN_INT|WIN_SHD),		//WIN4 COL START & CTRL
	(WIN_COL28|OSD_BLACK),//OSD_BLUE),				//WIN4 COL END & COLOR
	F_STOP
};
#else
code BYTE TOPWINDOW[] = {
//WINDOW1
	(WIN_SROW1|WIN_EROW1),		  		//WIN1 HEIGHT
	(WIN_COL0|WIN_ENA|WIN_INT&WIN_UNSHD), 		//WIN1 COL START & CTRL
	(WIN_COL28|OSD_BLACK),//OSD_CYAN),				//WIN1 COL END & COLOR
//WINDOW2
	(WIN_SROW1|WIN_EROW2),		  		//WIN2 HEIGHT
	(WIN_COL0|WIN_ENA|WIN_INT&WIN_UNSHD), 		//WIN2 COL START & CTRL
	(WIN_COL28|OSD_WHITE),				//WIN2 COL END & COLOR
//WINDOW3
	(WIN_SROW11|WIN_EROW11),				//WIN3 HEIGHT
	(WIN_COL0|WIN_ENA|WIN_INT&WIN_UNSHD),		//WIN3 COL START & CTRL
	(WIN_COL28|OSD_WHITE),//OSD_CYAN),				//WIN3 COL END & COLOR
//WINDOW4
	(WIN_SROW11|WIN_EROW12),				//WIN4 HEIGHT
	(WIN_COL0|WIN_ENA|WIN_INT&WIN_UNSHD),		//WIN4 COL START & CTRL
	(WIN_COL28|OSD_BLACK),//OSD_BLUE),				//WIN4 COL END & COLOR
	F_STOP
};
#endif

code BYTE TOPWINDOW_OPTION[] = {
	#ifdef OsdMenuType1
	0x01,			//OSDW_OPTION[0] :RSEPACE : Row to row spacing
	#else
	0x04,			//OSDW_OPTION[0] :RSEPACE : Row to row spacing
	#endif
	0x80,//0x80|0x10|0x00,	//OSDW_OPTION[1] :OSDCON1 : OSD Control Reg1 //old : 0x80
	0x08,			//OSDW_OPTION[2] :OSDCON2 : OSD Control Reg2.//old : 0x08,0x0C
	0x00,//0x01		//OSDW_OPTION[3] :CHSC	  : Character Shadow Color select Reg.
	0x00,			//OSDW_OPTION[4] :FSSTP	  : Full Screen Self-Test Pattern
	0x00,			//OSDW_OPTION[5] :WINSW	  : Win' Shadowing width Control Reg.
	0x00,			//OSDW_OPTION[6] :WINSH	  : Win' Shadowing height Control Reg.
	0x00,//0x06,		//OSDW_OPTION[7] :WINSC1  : Win' Shadowing Color Control Reg1.
	0x00,			//OSDW_OPTION[8] :WINSC2  : Win' Shadowing Color Control Reg2.
	#ifdef	Board2nd	
	0x03,//OSDW_OPTION[9] :XDEL	  : Xin input Falling Edge Control Reg.********Very Importants
	#else
	0x07,
	#endif
	F_STOP

};


//AnalogSubwindow
//DigitalSubWindow
//CompositeSubwindow
//CompositeNoVidSubwindow
//S_videoSubwindow
//S_videoNoVidSubwindow
//ChannelNumWindow
//TunerSubWindow
//PIPSubWindow
//PIPNoVideoWindow
#if defined(INT_EXTOSD)	//------------------------------------
code BYTE TVTOPWINDOW[] = {
#ifdef OsdMenuType1
//WINDOW1
	(WIN_SROW2|WIN_EROW2),		  		//WIN1 HEIGHT
	(WIN_COL0|WIN_ENA|WIN_INT&WIN_UNSHD), 		//WIN1 COL START & CTRL
	(WIN_COL28|OSD_WHITE),				//WIN1 COL END & COLOR
//WINDOW2
	(WIN_SROW1|WIN_EROW1),		  		//WIN2 HEIGHT
	(WIN_COL0|WIN_ENA|WIN_INT&WIN_UNSHD), 		//WIN2 COL START & CTRL
	#if defined(OsdColor_Red)
	(WIN_COL28|OSD_RED),				//WIN2 COL END & COLOR
	#else
	(WIN_COL28|OSD_BLUE),				//WIN2 COL END & COLOR
	#endif
//WINDOW3
	(WIN_SROW10|WIN_EROW10),			//WIN3 HEIGHT
	(WIN_COL0|WIN_ENA|WIN_INT&WIN_UNSHD),		//WIN3 COL START & CTRL
	#if defined(OsdColor_Red)
	(WIN_COL28|OSD_RED),				//WIN2 COL END & COLOR
	#else
	(WIN_COL28|OSD_BLUE),				//WIN2 COL END & COLOR
	#endif
//WINDOW4
	(WIN_SROW9|WIN_EROW9),				//WIN4 HEIGHT
	(WIN_COL0|WIN_DIS|WIN_INT&WIN_UNSHD),		//WIN4 COL START & CTRL
	(WIN_COL28|OSD_WHITE),//OSD_BLUE),		//WIN4 COL END & COLOR
	F_STOP
#else
//WINDOW1
	(WIN_SROW2|WIN_EROW2),		  		//WIN1 HEIGHT
	(WIN_COL0|WIN_ENA|WIN_INT&WIN_UNSHD), 		//WIN1 COL START & CTRL
	(WIN_COL28|OSD_WHITE),				//WIN1 COL END & COLOR
//WINDOW2
	(WIN_SROW1|WIN_EROW1),		  		//WIN2 HEIGHT
	(WIN_COL0|WIN_ENA|WIN_INT&WIN_UNSHD), 		//WIN2 COL START & CTRL
	#if defined(OsdColor_Red)
	(WIN_COL28|OSD_RED),				//WIN2 COL END & COLOR
	#else
	(WIN_COL28|OSD_BLUE),				//WIN2 COL END & COLOR
	#endif
//WINDOW3
	(WIN_SROW12|WIN_EROW12),			//WIN3 HEIGHT
	(WIN_COL0|WIN_ENA|WIN_INT&WIN_UNSHD),		//WIN3 COL START & CTRL
	#if defined(OsdColor_Red)
	(WIN_COL28|OSD_RED),				//WIN2 COL END & COLOR
	#else
	(WIN_COL28|OSD_BLUE),				//WIN2 COL END & COLOR
	#endif
//WINDOW4
	(WIN_SROW10|WIN_EROW11),				//WIN4 HEIGHT
	(WIN_COL0|WIN_ENA|WIN_INT&WIN_UNSHD),		//WIN4 COL START & CTRL
	(WIN_COL28|OSD_WHITE),//OSD_BLUE),		//WIN4 COL END & COLOR
	F_STOP
#endif
};
#else	//-----------------------------------------------------
code BYTE TVTOPWINDOW[] = {
//WINDOW1
	(WIN_SROW13|WIN_EROW14),		  		//WIN1 HEIGHT
	(WIN_COL0&WIN_DIS|WIN_INT|WIN_SHD), 		//WIN1 COL START & CTRL
	(WIN_COL28|OSD_YELLOW),				//WIN1 COL END & COLOR
//WINDOW2
	(WIN_SROW2|WIN_EROW9),		  		//WIN2 HEIGHT
	(WIN_COL0|WIN_ENA|WIN_INT&WIN_UNSHD), 		//WIN2 COL START & CTRL
	(WIN_COL28|OSD_WHITE),				//WIN2 COL END & COLOR
//WINDOW3
	(WIN_SROW2|WIN_EROW11),				//WIN3 HEIGHT
	(WIN_COL0|WIN_ENA|WIN_INT&WIN_UNSHD),		//WIN3 COL START & CTRL
	(WIN_COL28|OSD_WHITE),//OSD_CYAN),				//WIN3 COL END & COLOR
//WINDOW4
	(WIN_SROW1|WIN_EROW12),				//WIN4 HEIGHT
	(WIN_COL0|WIN_ENA|WIN_INT|WIN_SHD),		//WIN4 COL START & CTRL
	(WIN_COL28|OSD_BLACK),//OSD_BLUE),				//WIN4 COL END & COLOR
	F_STOP
};
#endif	//----------------------------------------------------


#if defined(TempOsdMenu)||defined(SSwideOsdtype)
code BYTE TVTOPWINDOW2[] = {
//WINDOW1
	(WIN_SROW2|WIN_EROW2),		  		//WIN1 HEIGHT
	(WIN_COL0&WIN_DIS|WIN_INT&WIN_UNSHD), 		//WIN1 COL START & CTRL
	(WIN_COL28|OSD_WHITE),				//WIN1 COL END & COLOR
//WINDOW2
	(WIN_SROW1|WIN_EROW1),		  		//WIN2 HEIGHT
	(WIN_COL0&WIN_DIS|WIN_INT&WIN_UNSHD), 		//WIN2 COL START & CTRL
	(WIN_COL28|OSD_BLUE),				//WIN2 COL END & COLOR
//WINDOW3
	(WIN_SROW10|WIN_EROW10),			//WIN3 HEIGHT
	(WIN_COL0&WIN_DIS|WIN_INT&WIN_UNSHD),		//WIN3 COL START & CTRL
	(WIN_COL28|OSD_BLUE),//OSD_CYAN),		//WIN3 COL END & COLOR
//WINDOW4
	(WIN_SROW9|WIN_EROW9),				//WIN4 HEIGHT
	(WIN_COL0&WIN_DIS|WIN_INT&WIN_UNSHD),		//WIN4 COL START & CTRL
	(WIN_COL28|OSD_WHITE),//OSD_BLUE),		//WIN4 COL END & COLOR
	F_STOP
};
#endif

code BYTE TVWINDOW_OPTION[] = {
#if defined(VideoDoubleOSD)
	0x03,			//OSDW_OPTION[0] :RSEPACE : Row to row spacing
	0x80,//0x80|0x10|0x00,	//OSDW_OPTION[1] :OSDCON1 : OSD Control Reg1 //old : 0x80
	0x18,			//OSDW_OPTION[2] :OSDCON2 : OSD Control Reg2.//old : 0x08,0x0C
	0x00,//0x01		//OSDW_OPTION[3] :CHSC	  : Character Shadow Color select Reg.
	0x00,			//OSDW_OPTION[4] :FSSTP	  : Full Screen Self-Test Pattern
	0x00,			//OSDW_OPTION[5] :WINSW	  : Win' Shadowing width Control Reg.
	0x00,			//OSDW_OPTION[6] :WINSH	  : Win' Shadowing height Control Reg.
	0x00,//0x06,		//OSDW_OPTION[7] :WINSC1  : Win' Shadowing Color Control Reg1.
	0x00,			//OSDW_OPTION[8] :WINSC2  : Win' Shadowing Color Control Reg2.
	0x03,			//OSDW_OPTION[9] :XDEL	  : Xin input Falling Edge Control Reg.********Very Importants
	F_STOP
#else	//보통 크기
	0x01,			//OSDW_OPTION[0] :RSEPACE : Row to row spacing
	0x80,//0x80|0x10|0x00,	//OSDW_OPTION[1] :OSDCON1 : OSD Control Reg1 //old : 0x80
	0x08,			//OSDW_OPTION[2] :OSDCON2 : OSD Control Reg2.//old : 0x08,0x0C
	0x00,//0x01		//OSDW_OPTION[3] :CHSC	  : Character Shadow Color select Reg.
	0x00,			//OSDW_OPTION[4] :FSSTP	  : Full Screen Self-Test Pattern
	0x00,			//OSDW_OPTION[5] :WINSW	  : Win' Shadowing width Control Reg.
	0x00,			//OSDW_OPTION[6] :WINSH	  : Win' Shadowing height Control Reg.
	0x00,//0x06,		//OSDW_OPTION[7] :WINSC1  : Win' Shadowing Color Control Reg1.
	0x00,			//OSDW_OPTION[8] :WINSC2  : Win' Shadowing Color Control Reg2.
	#ifdef WXGA_Panel
	0x00,			//OSDW_OPTION[9] :XDEL	  : Xin input Falling Edge Control Reg.********Very Importants
	#else
	0x03,			//OSDW_OPTION[9] :XDEL	  : Xin input Falling Edge Control Reg.********Very Importants
	#endif
	F_STOP
#endif
};

code BYTE SUBWINDOW[] = {
//WINDOW1
	(WIN_SROW2|WIN_EROW2),		  			//WIN1 HEIGHT
	(WIN_COL0&WIN_DIS|WIN_INT&WIN_UNSHD), 	//WIN1 COL START & CTRL
	(WIN_COL25|OSD_BLUE),					//WIN1 COL END & COLOR
//WINDOW2
	(WIN_SROW2|WIN_EROW2),		  			//WIN2 HEIGHT
	(WIN_COL0|WIN_ENA|WIN_INT&WIN_UNSHD), 	//WIN2 COL START & CTRL
	(WIN_COL10|OSD_WHITE),					//WIN2 COL END & COLOR
//WINDOW3
	(WIN_SROW2|WIN_EROW13),					//WIN3 HEIGHT
	(WIN_COL0&WIN_DIS|WIN_INT&WIN_UNSHD),	//WIN3 COL START & CTRL
	(WIN_COL25|OSD_GREEN),					//WIN3 COL END & COLOR
//WINDOW4
	(WIN_SROW1|WIN_EROW7),					//WIN4 HEIGHT
	(WIN_COL0&WIN_DIS|WIN_INT&WIN_UNSHD),		//WIN4 COL START & CTRL
	(WIN_COL25|OSD_GREEN),					//WIN4 COL END & COLOR
	F_STOP
};

code BYTE SUBWINDOW_OPTION[] = {
	0x00,//OSDW_OPTION[0] :RSEPACE : Row to row spacing
	0x80|0x40,//0x80|0x10|0x00,		//OSDW_OPTION[1] :OSDCON1 : OSD Control Reg1 //old : 0x80
	0x18,//OSDW_OPTION[2] :OSDCON2 : OSD Control Reg2.//old : 0x08,0x0C
	0x00,//0x01	//OSDW_OPTION[3] :CHSC	  : Character Shadow Color select Reg.
	0x00,//OSDW_OPTION[4] :FSSTP	  : Full Screen Self-Test Pattern
	0xF0,//OSDW_OPTION[5] :WINSW	  : Win' Shadowing width Control Reg.
	0xF0,//OSDW_OPTION[6] :WINSH	  : Win' Shadowing height Control Reg.
	0x00,//0x06,	//OSDW_OPTION[7] :WINSC1  : Win' Shadowing Color Control Reg1.
	0x00,//OSDW_OPTION[8] :WINSC2  : Win' Shadowing Color Control Reg2.
	#ifdef	Board2nd	
		#ifdef WXGA_Panel
	0x00,//OSDW_OPTION[9] :XDEL	  : Xin input Falling Edge Control Reg.********Very Importants
		#else
	0x03,//OSDW_OPTION[9] :XDEL	  : Xin input Falling Edge Control Reg.********Very Importants
		#endif
	#else
	0x07,
	#endif
	F_STOP
};


code BYTE INPUTWINDOW_OPTION[] = {
	0x00,//OSDW_OPTION[0] :RSEPACE : Row to row spacing
	0x80|0x40,//|0x40,//0x80|0x10|0x00,		//OSDW_OPTION[1] :OSDCON1 : OSD Control Reg1 //old : 0x80
	0x18,//OSDW_OPTION[2] :OSDCON2 : OSD Control Reg2.//old : 0x08,0x0C
	0x00,//0x01	//OSDW_OPTION[3] :CHSC	  : Character Shadow Color select Reg.
	0x00,//OSDW_OPTION[4] :FSSTP	  : Full Screen Self-Test Pattern
	0x01,//OSDW_OPTION[5] :WINSW	  : Win' Shadowing width Control Reg.
	0x01,//OSDW_OPTION[6] :WINSH	  : Win' Shadowing height Control Reg.
	0x00,//0x06,	//OSDW_OPTION[7] :WINSC1  : Win' Shadowing Color Control Reg1.
	0x00,//OSDW_OPTION[8] :WINSC2  : Win' Shadowing Color Control Reg2.
	#ifdef	Board2nd	
	0x03,//OSDW_OPTION[9] :XDEL	  : Xin input Falling Edge Control Reg.********Very Importants
	#else
	0x07,
	#endif
	F_STOP
};

code BYTE TUNERWINDOW[] = {
//WINDOW1
	(WIN_SROW2|WIN_EROW2),		  			//WIN1 HEIGHT
	(WIN_COL0&WIN_DIS|WIN_INT&WIN_UNSHD), 	//WIN1 COL START & CTRL
	(WIN_COL25|OSD_BLUE),					//WIN1 COL END & COLOR
//WINDOW2
	(WIN_SROW2|WIN_EROW4),		  			//WIN2 HEIGHT
	(WIN_COL0&WIN_DIS|WIN_INT&WIN_UNSHD), 	//WIN2 COL START & CTRL
	(WIN_COL10|OSD_WHITE),					//WIN2 COL END & COLOR
//WINDOW3
	(WIN_SROW2|WIN_EROW13),					//WIN3 HEIGHT
	(WIN_COL0&WIN_DIS|WIN_INT&WIN_UNSHD),	//WIN3 COL START & CTRL
	(WIN_COL25|OSD_GREEN),					//WIN3 COL END & COLOR
//WINDOW4
	(WIN_SROW1|WIN_EROW7),					//WIN4 HEIGHT
	(WIN_COL0&WIN_DIS|WIN_INT&WIN_UNSHD),		//WIN4 COL START & CTRL
	(WIN_COL25|OSD_GREEN),					//WIN4 COL END & COLOR
	F_STOP
};

code BYTE PIPSUBWINDOW[] = {
//WINDOW1
	(WIN_SROW2|WIN_EROW2),		  			//WIN1 HEIGHT
	(WIN_COL0&WIN_DIS|WIN_INT&WIN_UNSHD), 	//WIN1 COL START & CTRL
	(WIN_COL25|OSD_BLUE),					//WIN1 COL END & COLOR
//WINDOW2
	(WIN_SROW2|WIN_EROW4),		  			//WIN2 HEIGHT
	(WIN_COL0|WIN_ENA|WIN_INT&WIN_UNSHD), 	//WIN2 COL START & CTRL
	(WIN_COL16|OSD_WHITE),					//WIN2 COL END & COLOR
//WINDOW3
	(WIN_SROW2|WIN_EROW13),					//WIN3 HEIGHT
	(WIN_COL0&WIN_DIS|WIN_INT&WIN_UNSHD),	//WIN3 COL START & CTRL
	(WIN_COL25|OSD_GREEN),					//WIN3 COL END & COLOR
//WINDOW4
	(WIN_SROW1|WIN_EROW7),					//WIN4 HEIGHT
	(WIN_COL0&WIN_DIS|WIN_INT&WIN_UNSHD),		//WIN4 COL START & CTRL
	(WIN_COL25|OSD_GREEN),					//WIN4 COL END & COLOR
	F_STOP
};

code BYTE PIPSUBWINDOW_OPTION[] = {
	0x00,//OSDW_OPTION[0] :RSEPACE : Row to row spacing
	0x00,//0x80|0x10|0x00,		//OSDW_OPTION[1] :OSDCON1 : OSD Control Reg1 //old : 0x80
	0x08,//OSDW_OPTION[2] :OSDCON2 : OSD Control Reg2.//old : 0x08,0x0C
	0x00,//0x01	//OSDW_OPTION[3] :CHSC	  : Character Shadow Color select Reg.
	0x00,//OSDW_OPTION[4] :FSSTP	  : Full Screen Self-Test Pattern
	0xF0,//OSDW_OPTION[5] :WINSW	  : Win' Shadowing width Control Reg.
	0xF0,//OSDW_OPTION[6] :WINSH	  : Win' Shadowing height Control Reg.
	0x00,//0x06,	//OSDW_OPTION[7] :WINSC1  : Win' Shadowing Color Control Reg1.
	0x00,//OSDW_OPTION[8] :WINSC2  : Win' Shadowing Color Control Reg2.
	#ifdef	Board2nd	
	0x00,//OSDW_OPTION[9] :XDEL	  : Xin input Falling Edge Control Reg.********Very Importants
	#else
	0x07,
	#endif
	F_STOP
};

//AnalogPowerSaverWindow
//AnalogOutofFreqWindow
//AnalogSelfDigWindow
//DigitalPowerSaverWindow
//DigitalSelfDigWindow
code BYTE INFOWINDOW[] = {
//WINDOW1
	(WIN_SROW2|WIN_EROW2),		  			//WIN1 HEIGHT
	(WIN_COL0&WIN_DIS|WIN_INT&WIN_UNSHD), 	//WIN1 COL START & CTRL
	(WIN_COL25|OSD_BLUE),					//WIN1 COL END & COLOR
//WINDOW2
	(WIN_SROW2|WIN_EROW6),		  			//WIN2 HEIGHT
	(WIN_COL0|WIN_ENA|WIN_INT&WIN_UNSHD), 	//WIN2 COL START & CTRL
	(WIN_COL25|OSD_WHITE),					//WIN2 COL END & COLOR
//WINDOW3
	(WIN_SROW2|WIN_EROW13),					//WIN3 HEIGHT
	(WIN_COL0&WIN_DIS|WIN_INT&WIN_UNSHD),	//WIN3 COL START & CTRL
	(WIN_COL25|OSD_GREEN),					//WIN3 COL END & COLOR
//WINDOW4
	(WIN_SROW1|WIN_EROW7),					//WIN4 HEIGHT
	(WIN_COL0&WIN_DIS|WIN_INT&WIN_UNSHD),		//WIN4 COL START & CTRL
	(WIN_COL25|OSD_GREEN),					//WIN4 COL END & COLOR
	F_STOP
};

code BYTE INFOWINDOW_OPTION[] = {
	0x00,//OSDW_OPTION[0] :RSEPACE : Row to row spacing
	0x00,//0x80|0x10|0x00,		//OSDW_OPTION[1] :OSDCON1 : OSD Control Reg1 //old : 0x80
	0x08,//OSDW_OPTION[2] :OSDCON2 : OSD Control Reg2.//old : 0x08,0x0C
	0x00,//0x01	//OSDW_OPTION[3] :CHSC	  : Character Shadow Color select Reg.
	0x00,//OSDW_OPTION[4] :FSSTP	  : Full Screen Self-Test Pattern
	0xF0,//OSDW_OPTION[5] :WINSW	  : Win' Shadowing width Control Reg.
	0xF0,//OSDW_OPTION[6] :WINSH	  : Win' Shadowing height Control Reg.
	0x00,//0x06,	//OSDW_OPTION[7] :WINSC1  : Win' Shadowing Color Control Reg1.
	0x00,//OSDW_OPTION[8] :WINSC2  : Win' Shadowing Color Control Reg2.
	#ifdef	Board2nd	
	0x00,//OSDW_OPTION[9] :XDEL	  : Xin input Falling Edge Control Reg.********Very Importants
	#else
	0x07,
	#endif
	F_STOP
};

//AutoTuneMainWindow
code BYTE AUTOTUNEWINDOW[] = {
//WINDOW1
	(WIN_SROW1|WIN_EROW1),		  			//WIN1 HEIGHT
	//(WIN_COL0|WIN_ENA|WIN_INT&WIN_UNSHD), 	//WIN1 COL START & CTRL
	(WIN_COL0&WIN_DIS|WIN_INT&WIN_UNSHD),	
	(WIN_COL25|OSD_WHITE),					//WIN1 COL END & COLOR
//WINDOW2
	(WIN_SROW1|WIN_EROW5),		  			//WIN2 HEIGHT
	(WIN_COL0|WIN_ENA|WIN_INT&WIN_UNSHD), 	//WIN2 COL START & CTRL
	(WIN_COL25|OSD_BLUE),					//WIN2 COL END & COLOR
//WINDOW3
	(WIN_SROW2|WIN_EROW13),					//WIN3 HEIGHT
	(WIN_COL0&WIN_DIS|WIN_INT&WIN_UNSHD),	//WIN3 COL START & CTRL
	(WIN_COL25|OSD_GREEN),					//WIN3 COL END & COLOR
//WINDOW4
	(WIN_SROW1|WIN_EROW7),					//WIN4 HEIGHT
	(WIN_COL0&WIN_DIS|WIN_INT&WIN_UNSHD),		//WIN4 COL START & CTRL
	(WIN_COL25|OSD_GREEN),					//WIN4 COL END & COLOR
	F_STOP
};

code BYTE AUTOTUNEWINDOW_OPTION[] = {
	0x02,//OSDW_OPTION[0] :RSEPACE : Row to row spacing
	0x80,//0x80|0x10|0x00,		//OSDW_OPTION[1] :OSDCON1 : OSD Control Reg1 //old : 0x80
	0x08,//OSDW_OPTION[2] :OSDCON2 : OSD Control Reg2.//old : 0x08,0x0C
	0x00,//0x01	//OSDW_OPTION[3] :CHSC	  : Character Shadow Color select Reg.
	0x00,//OSDW_OPTION[4] :FSSTP	  : Full Screen Self-Test Pattern
	0xF0,//OSDW_OPTION[5] :WINSW	  : Win' Shadowing width Control Reg.
	0xF0,//OSDW_OPTION[6] :WINSH	  : Win' Shadowing height Control Reg.
	0x00,//0x06,	//OSDW_OPTION[7] :WINSC1  : Win' Shadowing Color Control Reg1.
	0x00,//OSDW_OPTION[8] :WINSC2  : Win' Shadowing Color Control Reg2.
	#ifdef	Board2nd	
	0x00,//OSDW_OPTION[9] :XDEL	  : Xin input Falling Edge Control Reg.********Very Importants
	#else
	0x07,
	#endif
	F_STOP
};


code BYTE OSDHOTKEYMSGWINDOW[] = {
//WINDOW1
	(WIN_SROW1|WIN_EROW1),		  			//WIN1 HEIGHT
	(WIN_COL0|WIN_ENA|WIN_INT&WIN_UNSHD), 	//WIN1 COL START & CTRL
	(WIN_COL29|OSD_WHITE),					//WIN1 COL END & COLOR
//WINDOW2
	(WIN_SROW1|WIN_EROW5),		  			//WIN2 HEIGHT
	(WIN_COL0|WIN_ENA|WIN_INT|WIN_SHD), 	//WIN2 COL START & CTRL
	(WIN_COL29|OSD_BLUE),					//WIN2 COL END & COLOR
//WINDOW3
	(WIN_SROW2|WIN_EROW13),					//WIN3 HEIGHT
	(WIN_COL0&WIN_DIS|WIN_INT&WIN_UNSHD),	//WIN3 COL START & CTRL
	(WIN_COL25|OSD_GREEN),					//WIN3 COL END & COLOR
//WINDOW4
	(WIN_SROW1|WIN_EROW7),					//WIN4 HEIGHT
	(WIN_COL0&WIN_DIS|WIN_INT&WIN_UNSHD),		//WIN4 COL START & CTRL
	(WIN_COL25|OSD_GREEN),					//WIN4 COL END & COLOR
	F_STOP
};

code BYTE OSDHOTKEYMSG_OPTION[] = {
	0x02,//OSDW_OPTION[0] :RSEPACE : Row to row spacing
	0x80,//0x80|0x10|0x00,		//OSDW_OPTION[1] :OSDCON1 : OSD Control Reg1 //old : 0x80
	0x00,//OSDW_OPTION[2] :OSDCON2 : OSD Control Reg2.//old : 0x08,0x0C
	0x00,//OSDW_OPTION[3] :CHSC	  : Character Shadow Color select Reg.
	0x00,//OSDW_OPTION[4] :FSSTP	  : Full Screen Self-Test Pattern
	0x00,//OSDW_OPTION[5] :WINSW	  : Win' Shadowing width Control Reg.
	0x00,//OSDW_OPTION[6] :WINSH	  : Win' Shadowing height Control Reg.
	0x00,//OSDW_OPTION[7] :WINSC1  : Win' Shadowing Color Control Reg1.
	0x00,//OSDW_OPTION[8] :WINSC2  : Win' Shadowing Color Control Reg2.
	#ifdef	Board2nd	
	0x00,//OSDW_OPTION[9] :XDEL	  : Xin input Falling Edge Control Reg.********Very Importants
	#else
	0x07,
	#endif
	F_STOP
};

//VolumeWindow
code BYTE VOLUMEWINDOW[] = {
//WINDOW1
	(WIN_SROW2|WIN_EROW2),		  			//WIN1 HEIGHT
	(WIN_COL0&WIN_DIS|WIN_INT&WIN_UNSHD), 	//WIN1 COL START & CTRL
	(WIN_COL25|OSD_BLUE),					//WIN1 COL END & COLOR
//WINDOW2
	(WIN_SROW2|WIN_EROW4),		  			//WIN2 HEIGHT
	(WIN_COL0|WIN_ENA|WIN_INT&WIN_UNSHD), 	//WIN2 COL START & CTRL
	(WIN_COL29|OSD_WHITE),					//WIN2 COL END & COLOR
//WINDOW3
	(WIN_SROW2|WIN_EROW13),					//WIN3 HEIGHT
	(WIN_COL0&WIN_DIS|WIN_INT&WIN_UNSHD),	//WIN3 COL START & CTRL
	(WIN_COL25|OSD_GREEN),					//WIN3 COL END & COLOR
//WINDOW4
	(WIN_SROW1|WIN_EROW7),					//WIN4 HEIGHT
	(WIN_COL0&WIN_DIS|WIN_INT&WIN_UNSHD),		//WIN4 COL START & CTRL
	(WIN_COL25|OSD_GREEN),					//WIN4 COL END & COLOR
	F_STOP
};

code BYTE VOLUMEWINDOW_OPTION[] = {
	0x00,//OSDW_OPTION[0] :RSEPACE : Row to row spacing
	0x80|0x40,//0x80|0x10|0x00,		//OSDW_OPTION[1] :OSDCON1 : OSD Control Reg1 //old : 0x80
	0x10,//0x18,//OSDW_OPTION[2] :OSDCON2 : OSD Control Reg2.//old : 0x08,0x0C
	0x00,//0x01	//OSDW_OPTION[3] :CHSC	  : Character Shadow Color select Reg.
	0x00,//OSDW_OPTION[4] :FSSTP	  : Full Screen Self-Test Pattern
	0xF0,//OSDW_OPTION[5] :WINSW	  : Win' Shadowing width Control Reg.
	0xF0,//OSDW_OPTION[6] :WINSH	  : Win' Shadowing height Control Reg.
	0x00,//0x06,	//OSDW_OPTION[7] :WINSC1  : Win' Shadowing Color Control Reg1.
	0x00,//OSDW_OPTION[8] :WINSC2  : Win' Shadowing Color Control Reg2.
	#ifdef	Board2nd	
	0x01,//OSDW_OPTION[9] :XDEL	  : Xin input Falling Edge Control Reg.********Very Importants
	#else
	0x07,
	#endif
	F_STOP
};

//VolumeWindow
code BYTE SUB_CHAR_WINDOW[] = {
//WINDOW1
	(WIN_SROW2|WIN_EROW2),		  			//WIN1 HEIGHT
	(WIN_COL0&WIN_DIS|WIN_INT&WIN_UNSHD), 	//WIN1 COL START & CTRL
	(WIN_COL25|OSD_BLUE),					//WIN1 COL END & COLOR
//WINDOW2
	(WIN_SROW1|WIN_EROW2),		  			//WIN2 HEIGHT
	(WIN_COL0|WIN_ENA|WIN_INT&WIN_UNSHD), 	//WIN2 COL START & CTRL
	(WIN_COL29|OSD_WHITE),					//WIN2 COL END & COLOR
//WINDOW3
	(WIN_SROW2|WIN_EROW13),					//WIN3 HEIGHT
	(WIN_COL0&WIN_DIS|WIN_INT&WIN_UNSHD),	//WIN3 COL START & CTRL
	(WIN_COL25|OSD_GREEN),					//WIN3 COL END & COLOR
//WINDOW4
	(WIN_SROW1|WIN_EROW7),					//WIN4 HEIGHT
	(WIN_COL0&WIN_DIS|WIN_INT&WIN_UNSHD),		//WIN4 COL START & CTRL
	(WIN_COL25|OSD_GREEN),					//WIN4 COL END & COLOR
	F_STOP
};

code BYTE SUB_CHAR_WINDOW_OPTION[] = {
	0x00,//OSDW_OPTION[0] :RSEPACE : Row to row spacing
	0x80|0x40,//0x80|0x10|0x00,		//OSDW_OPTION[1] :OSDCON1 : OSD Control Reg1 //old : 0x80
	0x18,//OSDW_OPTION[2] :OSDCON2 : OSD Control Reg2.//old : 0x08,0x0C
	0x00,//0x01	//OSDW_OPTION[3] :CHSC	  : Character Shadow Color select Reg.
	0x00,//OSDW_OPTION[4] :FSSTP	  : Full Screen Self-Test Pattern
	0xF0,//OSDW_OPTION[5] :WINSW	  : Win' Shadowing width Control Reg.
	0xF0,//OSDW_OPTION[6] :WINSH	  : Win' Shadowing height Control Reg.
	0x00,//0x06,	//OSDW_OPTION[7] :WINSC1  : Win' Shadowing Color Control Reg1.
	0x00,//OSDW_OPTION[8] :WINSC2  : Win' Shadowing Color Control Reg2.
	#ifdef	Board2nd	
	0x01,//OSDW_OPTION[9] :XDEL	  : Xin input Falling Edge Control Reg.********Very Importants
	#else
	0x07,
	#endif
	F_STOP
};

code BYTE PIPSELECTIONGUIDEWINDOW[] = {
//WINDOW1
	(WIN_SROW2|WIN_EROW2),		  			//WIN1 HEIGHT
	(WIN_COL0&WIN_DIS|WIN_INT&WIN_UNSHD), 	//WIN1 COL START & CTRL
	(WIN_COL25|OSD_BLUE),					//WIN1 COL END & COLOR
//WINDOW2
	(WIN_SROW2|WIN_EROW9),		  			//WIN2 HEIGHT
	(WIN_COL0|WIN_ENA|WIN_INT&WIN_UNSHD), 	//WIN2 COL START & CTRL
	(WIN_COL25|OSD_WHITE),					//WIN2 COL END & COLOR
//WINDOW3
	(WIN_SROW2|WIN_EROW13),					//WIN3 HEIGHT
	(WIN_COL0&WIN_DIS|WIN_INT&WIN_UNSHD),	//WIN3 COL START & CTRL
	(WIN_COL25|OSD_GREEN),					//WIN3 COL END & COLOR
//WINDOW4
	(WIN_SROW1|WIN_EROW9),					//WIN4 HEIGHT
	(WIN_COL0|WIN_ENA|WIN_INT&WIN_UNSHD),		//WIN4 COL START & CTRL
	(WIN_COL25|OSD_GREEN),					//WIN4 COL END & COLOR
	F_STOP
};

code BYTE PIPSELECTIONGUIDEWINDOW_OPTION[] = {
	0x00,//OSDW_OPTION[0] :RSEPACE : Row to row spacing
	0x00,//0x80|0x10|0x00,		//OSDW_OPTION[1] :OSDCON1 : OSD Control Reg1 //old : 0x80
	0x08,//OSDW_OPTION[2] :OSDCON2 : OSD Control Reg2.//old : 0x08,0x0C
	0x00,//0x01	//OSDW_OPTION[3] :CHSC	  : Character Shadow Color select Reg.
	0x00,//OSDW_OPTION[4] :FSSTP	  : Full Screen Self-Test Pattern
	0xF0,//OSDW_OPTION[5] :WINSW	  : Win' Shadowing width Control Reg.
	0xF0,//OSDW_OPTION[6] :WINSH	  : Win' Shadowing height Control Reg.
	0x00,//0x06,	//OSDW_OPTION[7] :WINSC1  : Win' Shadowing Color Control Reg1.
	0x00,//OSDW_OPTION[8] :WINSC2  : Win' Shadowing Color Control Reg2.
	#ifdef	Board2nd	
	0x00,//OSDW_OPTION[9] :XDEL	  : Xin input Falling Edge Control Reg.********Very Importants
	#else
	0x07,
	#endif
	F_STOP
};

/////////////////////////////////////////////////////////////////////
//	5-Language?
/////////////////////////////////////////////////////////////////////
//***************************************************************************************************************
//#ifdef	MultiLanguage
// modified by S.M.PARK 14 AUG 2003 : ENGLISH KOREAN JAPANESE 
//***************************************************************************************************************
//**
//캐릭터의 롬위치 방법은 :
// 1. 캐릭터 배열을 만들고
// 2. 캐릭터의 랭귀지를 참조하게끔 포이터배열을 쓰고
// 3. 캐릭터의 총갯수를 배열시킴.
//#################################################
#if defined(USE_NTSCtuner)//#################################################
//#################################################
/////////////////////////////////////////////////////////////////////
//	MAIN MENU
/////////////////////////////////////////////////////////////////////
#ifdef	Version_Display
code BYTE Mainmenu_Eng[] = {_M,_A,_I,_N,__,_M,_E,_N,_U,0x00,0x00,0x00,0x00,0x00,0x00,0x00,	_V,_e,_r,_0,_dot,_9,_N};
code BYTE Mainmenu_Kor[] = {_M,_A,_I,_N,__,_M,_E,_N,_U,0x00,0x00,0x00,0x00,0x00,0x00,0x00,	_V,_e,_r,_0,_dot,_9,_N};
code BYTE Mainmenu_Jpn[] = {_M,_A,_I,_N,__,_M,_E,_N,_U,0x00,0x00,0x00,0x00,0x00,0x00,0x00,	_V,_e,_r,_0,_dot,_9,_N};

code BYTE * code Mainmenu[] = {
	Mainmenu_Eng,
    	Mainmenu_Kor,
	Mainmenu_Jpn
};

code BYTE Mainmenu_Sizeof[] = {
	sizeof(Mainmenu_Eng),
	sizeof(Mainmenu_Kor),
	sizeof(Mainmenu_Jpn)
};
#else

code BYTE Mainmenu_Eng[] = {_P,_C,0x00,_A,_D,_J,_U,_S,_T};
code BYTE Mainmenu_Kor[] = {_P,_C,0x00,_A,_D,_J,_U,_S,_T};
code BYTE Mainmenu_Jpn[] = {_P,_C,0x00,_A,_D,_J,_U,_S,_T};

code BYTE * code Mainmenu[] = {
	Mainmenu_Eng,
    	Mainmenu_Kor,
	Mainmenu_Jpn
};

code BYTE Mainmenu_Sizeof[] = {
	sizeof(Mainmenu_Eng),
	sizeof(Mainmenu_Kor),
	sizeof(Mainmenu_Jpn)
};
#endif

/////////////////////////////////////////////////////////
//tv main
/////////////////////////////////////////////////////////
code BYTE TvMainmenu_Eng[] = {_T,_V,0x00,_A,_D,_J,_U,_S,_T};
//code BYTE TvMainmenu_Kor[] = {_T,_V,0x00,_A,_D,_J,_U,_S,_T};
//code BYTE TvMainmenu_Jpn[] = {_T,_V,0x00,_A,_D,_J,_U,_S,_T};

code BYTE * code TvMainmenu[] = {
	TvMainmenu_Eng//,
    	//TvMainmenu_Kor,
    	//TvMainmenu_Jpn
};

code BYTE TvMainmenu_Sizeof[] = {
	sizeof(TvMainmenu_Eng)//,
	//sizeof(TvMainmenu_Kor),
	//sizeof(TvMainmenu_Jpn)
};
/////////////////////////////////////////////////////////
//Av main
/////////////////////////////////////////////////////////
code BYTE AvMainmenu_Eng[] = {_A,_V,0x00,_A,_D,_J,_U,_S,_T};
//code BYTE AvMainmenu_Kor[] = {_A,_V,0x00,_A,_D,_J,_U,_S,_T};
//code BYTE AvMainmenu_Jpn[] = {_A,_V,0x00,_A,_D,_J,_U,_S,_T};

code BYTE * code AvMainmenu[] = {
	AvMainmenu_Eng//,
    	//AvMainmenu_Kor,
    	//AvMainmenu_Jpn
};

code BYTE AvMainmenu_Sizeof[] = {
	sizeof(AvMainmenu_Eng)//,
	//sizeof(AvMainmenu_Kor),
	//sizeof(AvMainmenu_Jpn)
};

/////////////////////////////////////////////////////////////////////
//	Main ICON menu
/////////////////////////////////////////////////////////////////////
code BYTE MainIconMenu_Eng[] = {0,0,_I_lMONITOR,0,_I_rMONITOR,0,_I_lRGB,0,_I_rRGB,0,_I_lOSD,0,_I_rOSD,	\
				0,_I_lPIP,0,_I_rPIP,0,_I_lTOOLS,0,_I_rTOOLS,0,_I_lSOUND,0,_I_rSOUND};

code BYTE * code MainIconMenu[] = {
	MainIconMenu_Eng
};

code BYTE MainIconMenu_Sizeof[] = {
	sizeof(MainIconMenu_Eng)
};

/////////////////////////////////////////////////////////////////////
//	Tv Main ICON menu
/////////////////////////////////////////////////////////////////////
code BYTE TvMainIconMenu_Eng[] = {_I_lMONITOR,_I_rMONITOR,0,0,0,0,_I_lTV2,_I_rTV2,0,0,0,0,_I_lTOOLS,_I_rTOOLS,0,0,0,0,_I_lSOUND,_I_rSOUND};

code BYTE * code TvMainIconMenu[] = {
	TvMainIconMenu_Eng
};
code BYTE TvMainIconMenu_Sizeof[] = {
	sizeof(TvMainIconMenu_Eng)
};

/////////////////////////////////////////////////////////////////////
//	Av Main ICON menu
/////////////////////////////////////////////////////////////////////
code BYTE AvMainIconMenu_Eng[] = {_I_lMONITOR,_I_rMONITOR,0,0,0,0,_I_lTOOLS,_I_rTOOLS,0,0,0,0,_I_lSOUND,_I_rSOUND};

code BYTE * code AvMainIconMenu[] = {
	AvMainIconMenu_Eng
};
code BYTE AvMainIconMenu_Sizeof[] = {
	sizeof(AvMainIconMenu_Eng)
};


/////////////////////////////////////////////////////////////////////
//	Bottom Fixed Information 2(Country)
/////////////////////////////////////////////////////////////////////
#if 0
code BYTE CountryBottomInfo_Eng[] = {_UpTriAngle,_DnTriAngle,_P,_O,_S,_I,_T,_I,_O,_N,0,_LRectAngle,_M,_RRectAngle,	\
				_R,_E,_T,_U,_R,_N};
code BYTE CountryBottomInfo_Kor[] = {_UpTriAngle,_DnTriAngle,_P,_O,_S,_I,_T,_I,_O,_N,0,_LRectAngle,_M,_RRectAngle,	\
				_R,_E,_T,_U,_R,_N};
code BYTE CountryBottomInfo_Jpn[] = {_UpTriAngle,_DnTriAngle,_P,_O,_S,_I,_T,_I,_O,_N,0,_LRectAngle,_M,_RRectAngle,	\
				_R,_E,_T,_U,_R,_N};
#else
code BYTE CountryBottomInfo_Eng[] = {_UpTriAngle,_DnTriAngle,_P,_O,_S,_I,_T,_I,_O,_N,0,_LRectAngle,_M,_RRectAngle,	\
				_R,_E,_T,_U,_R,_N};
#endif
code BYTE * code CountryBottomInfo[] = {
	CountryBottomInfo_Eng//,
	//CountryBottomInfo_Kor,
	//CountryBottomInfo_Jpn
};
code BYTE CountryBottomInfo_Sizeof[] = {
	sizeof(CountryBottomInfo_Eng)//,
	//sizeof(CountryBottomInfo_Kor),
	//sizeof(CountryBottomInfo_Jpn)
};

/////////////////////////////////////////////////////////////////////
//	select
/////////////////////////////////////////////////////////////////////
code BYTE Select_Eng[] = {_LTriAngle,0,0,0,_S,_E,_L,_E,_C,_T,0,0,0,_RTriAngle};
code BYTE Select_Chi[] = {_LTriAngle,_BK,_BK,_BK,CH_SELECT,_BK,_BK,_BK,_BK,_RTriAngle};

code BYTE * code Select[] = {
	Select_Eng,
    Select_Chi
};

code BYTE Select_Sizeof[] = {
	sizeof(Select_Eng),
	sizeof(Select_Chi)
};

#ifdef	USE_PALSECAMtuner
/////////////////////////////////////////////////////////////////////
//	channel edit windows char.
/////////////////////////////////////////////////////////////////////
code BYTE EditWindowChar1_eng[] = {_A,_B,_C,_D,_E,_F,_G,_H,_I,_J,_K,_L,_M,_N,_O,_P,_Q,_R,_S,_T};
code BYTE * code EditWindowChar1[] = {
	EditWindowChar1_eng
};
code BYTE EditWindowChar1_Sizeof[] = {
	sizeof(EditWindowChar1_eng)
};

/////////////////////////////////////////////////////////////////////
//	channel edit windows char.
/////////////////////////////////////////////////////////////////////
code BYTE EditWindowChar2_eng[] = {_U,_V,_W,_X,_Y,_Z,_plus,_minus,_dot,0,_0,_1,_2,_3,_4,_5,_6,_7,_8,_9};
code BYTE * code EditWindowChar2[] = {
	EditWindowChar2_eng
};
code BYTE EditWindowChar2_Sizeof[] = {
	sizeof(EditWindowChar2_eng)
};

/////////////////////////////////////////////////////////////////////
//	channel edit char.
/////////////////////////////////////////////////////////////////////
code BYTE ChEditChar[] = {_A,_B,_C,_D,_E,_F,_G,_H,_I,_J,_K,_L,_M,_N,_O,_P,_Q,_R,_S,_T,	\
				_U,_V,_W,_X,_Y,_Z,_plus,_minus,_dot,0,_0,_1,_2,_3,_4,_5,_6,_7,_8,_9};


/////////////////////////////////////////////////////////////////////
//	PROGRAMM EDIT
/////////////////////////////////////////////////////////////////////
code BYTE ProgrammEdit_eng[] = {_P,_R,_O,_G,_R,_A,_M,0,_E,_D,_I,_T};
code BYTE * code ProgrammEdit[] = {
	ProgrammEdit_eng
};
code BYTE ProgrammEdit_Sizeof[] = {
	sizeof(ProgrammEdit_eng)
};


/////////////////////////////////////////////////////////////////////
//	PROGRAMM EDIT CHANNEL/NAME
/////////////////////////////////////////////////////////////////////
code BYTE PRedit_ch_name_eng[] = {_P,_R,0,0,0,_C,_H,_A,_N,_N,_E,_L,0,0,_N,_A,_M,_E,0,0,_S,_K,_I,_P};
code BYTE * code PRedit_ch_name[] = {
	PRedit_ch_name_eng
};
code BYTE PRedit_ch_name_Sizeof[] = {
	sizeof(PRedit_ch_name_eng)
};
#endif


// ADJUST
code BYTE Adjust_Eng[] = {_A,_D,_J,_U,_S,_T};                            
code BYTE Adjust_Kor[] = {_JO,_JUNG};  
code BYTE Adjust_Jpn[] = {J_ADJUST};  

code BYTE * code Adjust[] = {
	Adjust_Eng,
	Adjust_Kor,
	Adjust_Jpn
};

code BYTE Adjust_Sizeof[] = {
	sizeof(Adjust_Eng),
	sizeof(Adjust_Kor),
	sizeof(Adjust_Jpn)
};

// RETURN
code BYTE Return_Eng[] = {_R,_E,_T,_U,_R,_N};                            
code BYTE Return_Kor[] = {_SANG,_WI,_MAE,_NEW};
code BYTE Return_Jpn[] = {J_RETURN}; 

code BYTE * code Return[] = {
	Return_Eng,
	Return_Kor,
	Return_Jpn
};

code BYTE Return_Sizeof[] = {
	sizeof(Return_Eng),
	sizeof(Return_Kor),
	sizeof(Return_Jpn)
};

// POSITION
code BYTE Position_Eng[] = {_P,_O,_S,_I,_T,_I,_O,_N};                            
code BYTE Position_Kor[] = {_WI,_CHI};  
code BYTE Position_Jpn[] = {J_POSITION};  

code BYTE * code Position[] = {
	Position_Eng,
	Position_Kor,
	Position_Jpn
};

code BYTE Position_Sizeof[] = {
	sizeof(Position_Eng),
	sizeof(Position_Kor),
	sizeof(Position_Jpn)
};

/////////////////////////////////////////////////////////////////////
//	BRIGHTNESS
/////////////////////////////////////////////////////////////////////
code BYTE Brightness_Eng[] = {_B,_R,_I,_G,_H,_T,_N,_E,_S,_S};                            
code BYTE Brightness_Chi[] = {CH_BRIGHT};  

code BYTE * code Brightness[] = {
	Brightness_Eng,
	Brightness_Chi
};

code BYTE Brightness_Sizeof[] = {
	sizeof(Brightness_Eng),
	sizeof(Brightness_Chi)
};

/////////////////////////////////////////////////////////////////////
//	CONTRAST
/////////////////////////////////////////////////////////////////////
code BYTE Contrast_Eng[] = {_C,_O,_N,_T,_R,_A,_S,_T};   
code BYTE Contrast_Chi[] = {CH_CONTRAST};  

code BYTE * code Contrast[] = {
	Contrast_Eng,
	Contrast_Chi
};

code BYTE Contrast_Sizeof[] = {
	sizeof(Contrast_Eng),
	sizeof(Contrast_Chi)
};


/////////////////////////////////////////////////////////////////////
//	SHARPNESS
/////////////////////////////////////////////////////////////////////
code BYTE Sharpness_Eng[] = {_S,_H,_A,_R,_P,_N,_E,_S,_S};
code BYTE Sharpness_Kor[] = {_SUN,_MYUNG,_DO};
code BYTE Sharpness_Jpn[] = {J_SHARPNESS};

code BYTE * code Sharpness[] = {
	Sharpness_Eng,
    	Sharpness_Kor,
	Sharpness_Jpn
};

code BYTE Sharpness_Sizeof[] = {
	sizeof(Sharpness_Eng),
	sizeof(Sharpness_Kor),
	sizeof(Sharpness_Jpn)
};

/////////////////////////////////////////////////////////////////////
//	CLOCK
/////////////////////////////////////////////////////////////////////
code BYTE Clock_Eng[] = {_C,_L,_O,_C,_K};
code BYTE Clock_Kor[] = {_JU,_PA,_SU};
code BYTE Clock_Jpn[] = {J_CLOCK};

code BYTE * code Clock[] = {
	Clock_Eng,
	Clock_Kor,
	Clock_Jpn
};

code BYTE Clock_Sizeof[] = {
	sizeof(Clock_Eng),
	sizeof(Clock_Kor),
	sizeof(Clock_Jpn)
};

/////////////////////////////////////////////////////////////////////
//	PHASE
/////////////////////////////////////////////////////////////////////
code BYTE Phase_Eng[] = {_P,_H,_A,_S,_E};
code BYTE Phase_Kor[] = {_WI,_SANG};
code BYTE Phase_Jpn[] = {J_PHASE};

code BYTE * code Phase[] = {
	Phase_Eng,
    	Phase_Kor,
	Phase_Jpn
};

code BYTE Phase_Sizeof[] = {
	sizeof(Phase_Eng),
	sizeof(Phase_Kor),
	sizeof(Phase_Jpn)
};


/////////////////////////////////////////////////////////////////////
//	HORIZONTAL
/////////////////////////////////////////////////////////////////////
code BYTE Horizontal_Eng[] = {_H,_O,_R,_I,_Z,_O,_N,_T,_A,_L};
code BYTE Horizontal_Chi[] = {CH_HPOS};

code BYTE * code Horizontal[] = {
	Horizontal_Eng,
    Horizontal_Chi
};

code BYTE Horizontal_Sizeof[] = {
	sizeof(Horizontal_Eng),
	sizeof(Horizontal_Chi)
};

/////////////////////////////////////////////////////////////////////
//	VERTICAL
/////////////////////////////////////////////////////////////////////
code BYTE Vertical_Eng[] = {_V,_E,_R,_T,_I,_C,_A,_L};
code BYTE Vertical_Chi[] = {CH_VPOS};

code BYTE * code Vertical[] = {
	Vertical_Eng,
    Vertical_Chi
};

code BYTE Vertical_Sizeof[] = {
	sizeof(Vertical_Eng),
	sizeof(Vertical_Chi)
};


/////////////////////////////////////////////////////////////////////
//	White balance
/////////////////////////////////////////////////////////////////////
code BYTE WhiteBalance_Eng[] = {_W,_H,_I,_T,_E,0,_B,_A,_L,_A,_N,_C,_E};
code BYTE WhiteBalance_Kor[] = {_BAEK,_SAEK,_JO,_JUNG};
code BYTE WhiteBalance_Jpn[] = {J_WHITEBAL};

code BYTE * code WhiteBalance[] = {
	WhiteBalance_Eng,
	WhiteBalance_Kor,
	WhiteBalance_Jpn
};

code BYTE WhiteBalance_Sizeof[] = {
	sizeof(WhiteBalance_Eng),
	sizeof(WhiteBalance_Kor),
	sizeof(WhiteBalance_Jpn)
};

/////////////////////////////////////////////////////////////////////
//	RED GAIN
/////////////////////////////////////////////////////////////////////
code BYTE Rgain_Eng[] = {_R,_E,_D,0,_G,_A,_I,_N};
code BYTE Rgain_Chi[] = {CH_REDGAIN};

code BYTE * code Rgain[] = {
	Rgain_Eng,
    Rgain_Chi
};

code BYTE Rgain_Sizeof[] = {
	sizeof(Rgain_Eng),
	sizeof(Rgain_Chi)
};

/////////////////////////////////////////////////////////////////////
//	GREEN GAIN
/////////////////////////////////////////////////////////////////////
code BYTE Ggain_Eng[] = {_G,_R,_E,_E,_N,0,_G,_A,_I,_N};
code BYTE Ggain_Chi[] = {CH_GREENGAIN};

code BYTE * code Ggain[] = {
	Ggain_Eng,
    	Ggain_Chi
};

code BYTE Ggain_Sizeof[] = {
	sizeof(Ggain_Eng),
	sizeof(Ggain_Chi)
};

/////////////////////////////////////////////////////////////////////
//	BLUE GAIN
/////////////////////////////////////////////////////////////////////
code BYTE Bgain_Eng[] = {_B,_L,_U,_E,0,_G,_A,_I,_N};
code BYTE Bgain_Chi[] = {CH_BLUEGAIN};

code BYTE * code Bgain[] = {
	Bgain_Eng,
    	Bgain_Chi
};

code BYTE Bgain_Sizeof[] = {
	sizeof(Bgain_Eng),
	sizeof(Bgain_Chi)
};

/////////////////////////////////////////////////////////////////////
//	COLOR TEMPERATURE
code BYTE Color_Eng[] = {_C,_O,_L,_O,_R,0,_T,_E,_M,_P,_E,_R,_A,_T,_U,_R,_E};
code BYTE Color_Chi[] = {CH_COLORTEMP};

code BYTE * code Color[] = {
	Color_Eng,
    	Color_Chi
};

code BYTE Color_Sizeof[] = {
	sizeof(Color_Eng),
	sizeof(Color_Chi)
};

/////////////////////////////////////////////////////////////////////
//	COLOR
code BYTE TvColor_Eng[] = {_C,_O,_L,_O,_R};
code BYTE TvColor_Kor[] = {_SAEK,_NONG,_DO};
code BYTE TvColor_Jpn[] = {J_COLOR};

code BYTE * code TvColor[] = {
	TvColor_Eng,
    	TvColor_Kor,
	TvColor_Jpn
};

code BYTE TvColor_Sizeof[] = {
	sizeof(TvColor_Eng),
	sizeof(TvColor_Kor),
	sizeof(TvColor_Jpn)
};

/////////////////////////////////////////////////////////////////////
//	LANGUAGE
code BYTE OsdLanguage_Eng[] = {_L,_A,_N,_G,_U,_A,_G,_E};
code BYTE OsdLanguage_Chi[] = {CH_LANG};

code BYTE * code OsdLanguage[] = {
	OsdLanguage_Eng,
    	OsdLanguage_Chi
};
code BYTE OsdLanguage_Sizeof[] = {
	sizeof(OsdLanguage_Eng),
	sizeof(OsdLanguage_Chi)
};

/////////////////////////////////////////////////////////////////////
//	Country  - USA
/////////////////////////////////////////////////////////////////////
code BYTE CountryUSA_Eng[] = {_U,_S,_A};
//code BYTE CountryUSA_Kor[] = {_U,_S,_A};
//code BYTE CountryUSA_Jpn[] = {_U,_S,_A};

code BYTE * code CountryUSA[] = {
	CountryUSA_Eng//,
	//CountryUSA_Kor,
	//CountryUSA_Jpn
};

code BYTE CountryUSA_Sizeof[] = {
	sizeof(CountryUSA_Eng)//,
	//sizeof(CountryUSA_Kor),
	//sizeof(CountryUSA_Jpn)
};

#if defined (USE_NTSCtuner)
/////////////////////////////////////////////////////////////////////
//	language - english
/////////////////////////////////////////////////////////////////////
code BYTE LangEng_Eng[] = {_E,_N,_G,_L,_I,_S,_H};

code BYTE * code LangEng[] = {
	LangEng_Eng,
};

code BYTE LangEng_Sizeof[] = {
	sizeof(LangEng_Eng),
};

/////////////////////////////////////////////////////////////////////
code BYTE LangKor_Eng[] = {_K,_O,_R,_E,_A};

code BYTE * code LangKor[] = {
	LangKor_Eng,
};

code BYTE LangKor_Sizeof[] = {
	sizeof(LangKor_Eng),
};

/////////////////////////////////////////////////////////////////////
code BYTE LangJap_Eng[] = {_J,_A,_P,_A,_N};

code BYTE * code LangJap[] = {
	LangJap_Eng,
};

code BYTE LangJap_Sizeof[] = {
	sizeof(LangJap_Eng),
};

#elif defined (USE_PALSECAMtuner)

/////////////////////////////////////////////////////////////////////
//	language - English
/////////////////////////////////////////////////////////////////////
code BYTE LangEng_Eng[] = {_E,_N,_G,_L,_I,_S,_H};
code BYTE * code LangEng[] = {
	LangEng_Eng
};

code BYTE LangEng_Sizeof[] = {
	sizeof(LangEng_Eng)
};
/////////////////////////////////////////////////////////////////////

//	Language - FRANCE
/////////////////////////////////////////////////////////////////////
code BYTE LangFrance_eng[] = {_F,_R,_A,_N,_C,_E};
code BYTE * code LangFrance[] = {
	LangFrance_eng
};
code BYTE LangFrance_Sizeof[] = {
	sizeof(LangFrance_eng)
};

//	Language - German
/////////////////////////////////////////////////////////////////////
code BYTE LangGerman_eng[] = {_G,_E,_R,_M,_A,_N};
code BYTE * code LangGerman[] = {
	LangGerman_eng
};
code BYTE LangGerman_Sizeof[] = {
	sizeof(LangGerman_eng)
};

//	Language - Italia
/////////////////////////////////////////////////////////////////////
code BYTE LangItalia_eng[] = {_I,_T,_A,_L,_I,_A};
code BYTE * code LangItalia[] = {
	LangItalia_eng
};
code BYTE LangItalia_Sizeof[] = {
	sizeof(LangItalia_eng)
};

//	Language - Netherlands
/////////////////////////////////////////////////////////////////////
code BYTE LangNetherlands_eng[] = {_N,_E,_T,_H,_E,_R,_L,_A,_N,_D,_S};
code BYTE * code LangNetherlands[] = {
	LangNetherlands_eng
};
code BYTE LangNetherlands_Sizeof[] = {
	sizeof(LangNetherlands_eng)
};

//	Language - Russia
/////////////////////////////////////////////////////////////////////
code BYTE LangRussia_eng[] = {_R,_U,_S,_S,_I,_A};
code BYTE * code LangRussia[] = {
	LangRussia_eng
};
code BYTE LangRussia_Sizeof[] = {
	sizeof(LangRussia_eng)
};

//	Language - China
/////////////////////////////////////////////////////////////////////
code BYTE LangChina_eng[] = {_C,_H,_I,_N,_A};
code BYTE LangChina_Chi[] = {CH_CHINA};
code BYTE * code LangChina[] = {
	LangChina_eng,
	LangChina_Chi
};
code BYTE LangChina_Sizeof[] = {
	sizeof(LangChina_eng),
	sizeof(LangChina_Chi)
};

#if 1
//	Language - China
/////////////////////////////////////////////////////////////////////
code BYTE LangChina_eng[] = {_C,_H,_I,_N,_A};
code BYTE LangChina_Chi[] = {CH_CHINA};
code BYTE * code LangChina[] = {
	LangChina_eng,
	LangChina_Chi
};
code BYTE LangChina_Sizeof[] = {
	sizeof(LangChina_eng),
	sizeof(LangChina_Chi)
};
#endif

#endif

/////////////////////////////////////////////////////////////////////
//	OSD H-POSITION
/////////////////////////////////////////////////////////////////////
code BYTE OsdHPosition_Eng[] = {_O,_S,_D,0,_H,_minus,_P,_O,_S,_I,_T,_I,_O,_N};
code BYTE OsdHPosition_Kor[] = {_O1,_S1,_D1,_BK,_SU,_PYUNG,_WI,_CHI};
code BYTE OsdHPosition_Jpn[] = {_O1,_S1,_D1,_BK,J_OSDHPOS};

code BYTE * code OsdHPosition[] = {
	OsdHPosition_Eng,
	OsdHPosition_Kor,
	OsdHPosition_Jpn
};

code BYTE OsdHPosition_Sizeof[] = {
	sizeof(OsdHPosition_Eng),
	sizeof(OsdHPosition_Kor),
	sizeof(OsdHPosition_Jpn)
};

/////////////////////////////////////////////////////////////////////
//	V-POSITION
/////////////////////////////////////////////////////////////////////
code BYTE OsdVPosition_Eng[] = {_O,_S,_D,0,_V,_minus,_P,_O,_S,_I,_T,_I,_O,_N};
code BYTE OsdVPosition_Kor[] = {_O1,_S1,_D1,_BK,_SU,_JIK,_WI,_CHI};
code BYTE OsdVPosition_Jpn[] = {_O1,_S1,_D1,_BK,J_OSDVPOS};

code BYTE * code OsdVPosition[] = {
	OsdVPosition_Eng,
	OsdVPosition_Kor,
	OsdVPosition_Jpn
};

code BYTE OsdVPosition_Sizeof[] = {
	sizeof(OsdVPosition_Eng),
	sizeof(OsdVPosition_Kor),
	sizeof(OsdVPosition_Jpn)
};

/////////////////////////////////////////////////////////////////////
//	OSD TIME
/////////////////////////////////////////////////////////////////////
code BYTE OsdTime_Eng[] = {_O,_S,_D,0x00,_T,_I,_M,_E};
code BYTE OsdTime_Kor[] = {_O1,_S1,_D1,_BK,_PYO,_SI,_SI,_GAN};
code BYTE OsdTime_Jpn[] = {_O1,_S1,_D1,_BK,J_OSDTIME};

code BYTE * code OsdTime[] = {
	OsdTime_Eng,
    	OsdTime_Kor,
	OsdTime_Jpn
};

code BYTE OsdTime_Sizeof[] = {
	sizeof(OsdTime_Eng),
	sizeof(OsdTime_Kor),
	sizeof(OsdTime_Jpn)
};

/////////////////////////////////////////////////////////////////////
//	OSD TRANSPARENCY
/////////////////////////////////////////////////////////////////////
code BYTE OsdTransparency_Eng[] = {_O,_S,_D,0,_T,_R,_A,_N,_S,_P,_A,_R,_E,_N,_C,_Y};
code BYTE OsdTransparency_Kor[] = {_O1,_S1,_D1,_BK,_BAN,_TOU,_MYUNG};                                     
code BYTE OsdTransparency_Jpn[] = {_O1,_S1,_D1,_BK,J_OSDTRANS};

code BYTE * code OsdTransparency[] = {
	OsdTransparency_Eng,
	OsdTransparency_Kor,
	OsdTransparency_Jpn
};

code BYTE OsdTransparency_Sizeof[] = {
	sizeof(OsdTransparency_Eng),
	sizeof(OsdTransparency_Kor),
	sizeof(OsdTransparency_Jpn)
};

/////////////////////////////////////////////////////////////////////
//	PIP ENABLE
/////////////////////////////////////////////////////////////////////
code BYTE PipEnable_Eng[] = {_P,_I,_P,0,_E,_N,_A,_B,_L,_E};
code BYTE PipEnable_Kor[] = {_P1,_I1,_P1,_BK,_DONG,_JAK};
code BYTE PipEnable_Jpn[] = {J_PIP_ENABLE};

code BYTE * code PipEnable[] = {
	PipEnable_Eng,
	PipEnable_Kor,
	PipEnable_Jpn
};

code BYTE PipEnable_Sizeof[] = {
	sizeof(PipEnable_Eng),
	sizeof(PipEnable_Kor),
	sizeof(PipEnable_Jpn)
};

/////////////////////////////////////////////////////////////////////
//	PIP SOURCE
/////////////////////////////////////////////////////////////////////
code BYTE PipSource_Eng[] = {_P,_I,_P,0,_S,_O,_U,_R,_C,_E};
code BYTE PipSource_Kor[] = {_P1,_I1,_P1,_BK,_EIP,_YERK};
code BYTE PipSource_Jpn[] = {J_PIP_SOURCE};

code BYTE * code PipSource[] = {
	PipSource_Eng,
	PipSource_Kor,
	PipSource_Jpn
};

code BYTE PipSource_Sizeof[] = {
	sizeof(PipSource_Eng),
	sizeof(PipSource_Kor),
	sizeof(PipSource_Jpn)
};

/////////////////////////////////////////////////////////////////////
//	PIP SIZE
/////////////////////////////////////////////////////////////////////
code BYTE PipSize_Eng[] = {_P,_I,_P,0,_S,_I,_Z,_E};
code BYTE PipSize_Kor[] = {_P1,_I1,_P1,_BK,_KEE,_GI};
code BYTE PipSize_Jpn[] = {J_PIP_SIZE};

code BYTE * code PipSize[] = {
	PipSize_Eng,
	PipSize_Kor,
	PipSize_Jpn
};

code BYTE PipSize_Sizeof[] = {
	sizeof(PipSize_Eng),
	sizeof(PipSize_Kor),
	sizeof(PipSize_Jpn)
};

/////////////////////////////////////////////////////////////////////
//	Pip H-POSITION
/////////////////////////////////////////////////////////////////////
code BYTE PipHPosition_Eng[] = {_P,_I,_P,0,_H,_minus,_P,_O,_S,_I,_T,_I,_O,_N};
code BYTE PipHPosition_Kor[] = {_P1,_I1,_P1,_BK,_SU,_PYUNG,_WI,_CHI};
code BYTE PipHPosition_Jpn[] = {J_PIP_HPOS};

code BYTE * code PipHPosition[] = {
	PipHPosition_Eng,
	PipHPosition_Kor,
	PipHPosition_Jpn
};

code BYTE PipHPosition_Sizeof[] = {
	sizeof(PipHPosition_Eng),
	sizeof(PipHPosition_Kor),
	sizeof(PipHPosition_Jpn)
};

/////////////////////////////////////////////////////////////////////
//	V-POSITION
/////////////////////////////////////////////////////////////////////
code BYTE PipVPosition_Eng[] = {_P,_I,_P,0,_V,_minus,_P,_O,_S,_I,_T,_I,_O,_N};
code BYTE PipVPosition_Kor[] = {_P1,_I1,_P1,_BK,_SU,_JIK,_WI,_CHI};
code BYTE PipVPosition_Jpn[] = {J_PIP_VPOS};

code BYTE * code PipVPosition[] = {
	PipVPosition_Eng,
	PipVPosition_Kor,
	PipVPosition_Jpn
};

code BYTE PipVPosition_Sizeof[] = {
	sizeof(PipVPosition_Eng),
	sizeof(PipVPosition_Kor),
	sizeof(PipVPosition_Jpn)
};

/////////////////////////////////////////////////////////////////////
//	aspect
/////////////////////////////////////////////////////////////////////
code BYTE Aspect[] = {_A,_S,_P,_E,_C,_T};
/*
code BYTE * code Aspect[] = {
	Aspect_Eng
};

code BYTE Aspect_Sizeof[] = {
	sizeof(Aspect_Eng)
};
*/

/////////////////////////////////////////////////////////////////////
//	pip aspect
/////////////////////////////////////////////////////////////////////
code BYTE PipAspect_Eng[] = {_P,_I,_P,0,_A,_S,_P,_E,_C,_T};
code BYTE PipAspect_Kor[] = {_P1,_I1,_P1,_BK,_HWA,_MYUN,_BEE,_YULL};
code BYTE PipAspect_Jpn[] = {J_PIP_ASPECT};

code BYTE * code PipAspect[] = {
	PipAspect_Eng,
	PipAspect_Kor,
	PipAspect_Jpn
};

code BYTE PipAspect_Sizeof[] = {
	sizeof(PipAspect_Eng),
	sizeof(PipAspect_Kor),
	sizeof(PipAspect_Jpn)
};

/////////////////////////////////////////////////////////////////////
//	aspect (4:3)
/////////////////////////////////////////////////////////////////////
code BYTE Aspect4_3_Eng[] = {_4,_Colon,_3};
code BYTE Aspect4_3_Kor[] = {_4,_Colon,_3};
code BYTE Aspect4_3_Jpn[] = {_4,_Colon,_3};

code BYTE * code Aspect4_3[] = {
	Aspect4_3_Eng,
	Aspect4_3_Kor,
	Aspect4_3_Jpn,
};

code BYTE Aspect4_3_Sizeof[] = {
	sizeof(Aspect4_3_Eng),
	sizeof(Aspect4_3_Kor),
	sizeof(Aspect4_3_Jpn)
};

/////////////////////////////////////////////////////////////////////
//	aspect (16:9)
/////////////////////////////////////////////////////////////////////
code BYTE Aspect16_9_Eng[] = {_1,_6,_Colon,_9};
code BYTE Aspect16_9_Kor[] = {_1,_6,_Colon,_9};
code BYTE Aspect16_9_Jpn[] = {_1,_6,_Colon,_9};

code BYTE * code Aspect16_9[] = {
	Aspect16_9_Eng,
	Aspect16_9_Kor,
	Aspect16_9_Jpn
};

code BYTE Aspect16_9_Sizeof[] = {
	sizeof(Aspect16_9_Eng),
	sizeof(Aspect16_9_Kor),
	sizeof(Aspect16_9_Jpn)
};

/////////////////////////////////////////////////////////////////////
//	aspect (full)
/////////////////////////////////////////////////////////////////////
code BYTE Full_Eng[] = {_F,_U,_L,_L};
code BYTE Full_Chi[] = {CH_FULL};

code BYTE * code Full[] = {
	Full_Eng,
	Full_Chi
};

code BYTE Full_Sizeof[] = {
	sizeof(Full_Eng),
	sizeof(Full_Chi)
};

/////////////////////////////////////////////////////////////////////
//	AUTO ADJUST
/////////////////////////////////////////////////////////////////////
code BYTE AutoAdjust_Eng[] = {_A,_U,_T,_O,0x00,_A,_D,_J,_U,_S,_T,_M,_E,_N,_T};
code BYTE AutoAdjust_Kor[] = {_A,_U,_T,_O,0x00,_A,_D,_J,_U,_S,_T,_M,_E,_N,_T};
code BYTE AutoAdjust_Jpn[] = {_A,_U,_T,_O,0x00,_A,_D,_J,_U,_S,_T,_M,_E,_N,_T};

code BYTE * code AutoAdjust[] = {
	AutoAdjust_Eng,
    	AutoAdjust_Kor,
	AutoAdjust_Jpn
};

code BYTE AutoAdjust_Sizeof[] = {
	sizeof(AutoAdjust_Eng),
	sizeof(AutoAdjust_Kor),
	sizeof(AutoAdjust_Jpn)
};

//////////////////////////////////////////////////////////////////////
code BYTE OSDHotkeyMsg1[]={
	_Y,_E,_S,_Colon,_,_P,_R,_E,_S,_S,_,_A,_U,_T,_O,_,_B,_U,_T,_T,_O,_N,_,_A,_G,_A,_I,_N
};

//////////////////////////////////////////////////////////////////////
code BYTE OSDHotkeyMsg2[]={
	_N,_O,_,_Colon,_,_P,_R,_E,_S,_S,_,_O,_T,_H,_E,_R,_,_K,_E,_Y
};     

/////////////////////////////////////////////////////////////////////
//	FACTORY DEFAULT
/////////////////////////////////////////////////////////////////////
code BYTE Factory_Eng[] = {_F,_A,_C,_T,_O,_R,_Y,0,_D,_E,_F,_A,_U,_L,_T};
code BYTE Factory_Chi[] = {CH_FACTORY};

code BYTE * code Factory[] = {
	Factory_Eng,
	Factory_Chi
};
code BYTE Factory_Sizeof[] = {
	sizeof(Factory_Eng),
	sizeof(Factory_Chi)
};

/////////////////////////////////////////////////////////////////////
//	DOSMODE		//2003-08-26
/////////////////////////////////////////////////////////////////////
code BYTE Dosmode_Eng[] = {_D,_O,_S,0,_M,_O,_D,_E};
code BYTE Dosmode_Kor[] = {_D1,_O1,_S1,_BK,_MO,_DEA};
code BYTE Dosmode_Jpn[] = {J_DOS_MODE};

code BYTE * code Dosmode[] = {
	Dosmode_Eng,
	Dosmode_Kor,
	Dosmode_Jpn
};
code BYTE Dosmode_Sizeof[] = {
	sizeof(Dosmode_Eng),
	sizeof(Dosmode_Kor),
	sizeof(Dosmode_Jpn)
};

#if 0
/////////////////////////////////////////////////////////////////////
//	SETUP
/////////////////////////////////////////////////////////////////////
code BYTE Setup_Eng[] = {0x00,_2iSetupL,_2iSetupR,0x00,_S,_E,_T,_U,_P};
code BYTE Setup_Kor[] = {0x00,_2iSetupL,_2iSetupR,0x00,_S,_E,_T,_U,_P};
code BYTE Setup_Jpn[] = {0x00,_2iSetupL,_2iSetupR,0x00,_S,_E,_T,_U,_P};

code BYTE * code Setup[] = {
	Setup_Eng,
    	Setup_Kor,
    	Setup_Jpn
};

code BYTE Setup_Sizeof[] = {
	sizeof(Setup_Eng),
	sizeof(Setup_Kor),
	sizeof(Setup_Jpn)
};
#endif


/////////////////////////////////////////////////////////////////////
//	CHANNEL EDIT
/////////////////////////////////////////////////////////////////////
/*
code BYTE ChannelEdit_eng[] = {_C,_H,_A,_N,_N,_E,_L,0,_E,_D,_I,_T};
code BYTE * code ChannelEdit[] = {
	ChannelEdit_eng
};
code BYTE ChannelEdit_Sizeof[] = {
	sizeof(ChannelEdit_eng)
};
*/
/////////////////////////////////////////////////////////////////////
//	CHANNEL EDIT CHANNEL/NAME
/////////////////////////////////////////////////////////////////////
code BYTE CHedit_ch_add_eng[] = {_C,_H,_A,_N,_N,_E,_L,0,0,0,0,0,0,0,0,0,_A,_D,_D};
code BYTE * code CHedit_ch_add[] = {
	CHedit_ch_add_eng
};
code BYTE CHedit_ch_add_Sizeof[] = {
	sizeof(CHedit_ch_add_eng)
};

#if 0
/////////////////////////////////////////////////////////////////////
//	Color temperature
/////////////////////////////////////////////////////////////////////
code BYTE CTwarm_Eng[] = {_W,_A,_R,_M};
code BYTE CTwarm_Kor[] = {_W,_A,_R,_M};
code BYTE CTwarm_Jpn[] = {_W,_A,_R,_M};

code BYTE * code CTwarm[] = {
	CTwarm_Eng,
	CTwarm_Kor,
	CTwarm_Jpn
};
code BYTE CTwarm_Sizeof[] = {
	sizeof(CTwarm_Eng),
	sizeof(CTwarm_Kor),
	sizeof(CTwarm_Jpn)
};

/////////////////////////////////////////////////////////////////////
code BYTE CTstandard_Eng[] = {_S,_T,_A,_N,_D,_A,_R,_D};
code BYTE CTstandard_Kor[] = {_S,_T,_A,_N,_D,_A,_R,_D};
code BYTE CTstandard_Jpn[] = {_S,_T,_A,_N,_D,_A,_R,_D};

code BYTE * code CTstandard[] = {
	CTstandard_Eng,
	CTstandard_Kor,
	CTstandard_Jpn
};

code BYTE CTstandard_Sizeof[] = {
	sizeof(CTstandard_Eng),
	sizeof(CTstandard_Kor),
	sizeof(CTstandard_Jpn),
};

/////////////////////////////////////////////////////////////////////
code BYTE CTcool_Eng[] = {_C,_O,_O,_L};
code BYTE CTcool_Kor[] = {_C,_O,_O,_L};
code BYTE CTcool_Jpn[] = {_C,_O,_O,_L};

code BYTE * code CTcool[] = {
	CTcool_Eng,
	CTcool_Kor,
	CTcool_Jpn
};

code BYTE CTcool_Sizeof[] = {
	sizeof(CTcool_Eng),
	sizeof(CTcool_Kor),
	sizeof(CTcool_Jpn)
};
#else
/////////////////////////////////////////////////////////////////////
//	Color temperature
/////////////////////////////////////////////////////////////////////
code BYTE CTwarm_Eng[] = {_W,_A,_R,_M};
code BYTE * code CTwarm[] = {
	CTwarm_Eng
};
code BYTE CTwarm_Sizeof[] = {
	sizeof(CTwarm_Eng)
};

/////////////////////////////////////////////////////////////////////
code BYTE CTstandard_Eng[] = {_S,_T,_A,_N,_D,_A,_R,_D};

code BYTE * code CTstandard[] = {
	CTstandard_Eng
};

code BYTE CTstandard_Sizeof[] = {
	sizeof(CTstandard_Eng)
};

/////////////////////////////////////////////////////////////////////
code BYTE CTcool_Eng[] = {_C,_O,_O,_L};

code BYTE * code CTcool[] = {
	CTcool_Eng
};

code BYTE CTcool_Sizeof[] = {
	sizeof(CTcool_Eng)
};
#endif

/////////////////////////////////////////////////////////////////////
//	PC
/////////////////////////////////////////////////////////////////////
code BYTE Pc[] = {_P,0,_C};

/////////////////////////////////////////////////////////////////////
//	tv
/////////////////////////////////////////////////////////////////////
code BYTE Tv[] = {_T,0,_V};

/////////////////////////////////////////////////////////////////////
//	AV1
/////////////////////////////////////////////////////////////////////
code BYTE Av1[] = {_A,0,_V,0,_1};

/////////////////////////////////////////////////////////////////////
//	AV2
/////////////////////////////////////////////////////////////////////
code BYTE Av2[] = {_A,0,_V,0,_2};

/////////////////////////////////////////////////////////////////////
//	ANALOG
/////////////////////////////////////////////////////////////////////
code BYTE Analog_Eng[] = {_A,_N,_A,_L,_O,_G};
//code BYTE Analog_Kor[] = {_A,_N,_A,_L,_O,_G};
//code BYTE Analog_Jpn[] = {_A,_N,_A,_L,_O,_G};

code BYTE * code Analog[] = 
{
	Analog_Eng//,
    	//Analog_Kor,
    	//Analog_Jpn
};

code BYTE Analog_Sizeof[] = 
{
	sizeof(Analog_Eng)//,
	//sizeof(Analog_Kor),
	//sizeof(Analog_Jpn)
};

/////////////////////////////////////////////////////////////////////
//	TUNER
/////////////////////////////////////////////////////////////////////
code BYTE Tuner_Eng[] = {_T,_U,_N,_E,_R};
//code BYTE Tuner_Kor[] = {_T,_U,_N,_E,_R};
//code BYTE Tuner_Jpn[] = {_T,_U,_N,_E,_R};

code BYTE * code Tuner[] = {
	Tuner_Eng//,
	//Tuner_Kor,
	//Tuner_Jpn
};

code BYTE Tuner_Sizeof[] = {
	sizeof(Tuner_Eng)//,
	//sizeof(Tuner_Kor),
	//sizeof(Tuner_Jpn)
};

/////////////////////////////////////////////////////////////////////
//	COMPOSITE
/////////////////////////////////////////////////////////////////////
code BYTE Composite_Eng[] = {_C,_O,_M,_P,_O,_S,_I,_T,_E};
//code BYTE Composite_Kor[] = {_C,_O,_M,_P,_O,_S,_I,_T,_E};
//code BYTE Composite_Jpn[] = {_C,_O,_M,_P,_O,_S,_I,_T,_E};

code BYTE * code Composite[] = {
	Composite_Eng//,
	//Composite_Kor,
	//Composite_Jpn
};
code BYTE Composite_Sizeof[] = {
	sizeof(Composite_Eng)//,
	//sizeof(Composite_Kor),
	//sizeof(Composite_Jpn)
};

/////////////////////////////////////////////////////////////////////
//	S-VIDEO
/////////////////////////////////////////////////////////////////////
code BYTE Svideo_Eng[] = {_S,_minus,_V,_I,_D,_E,_O};
//code BYTE Svideo_Kor[] = {_S,_minus,_V,_I,_D,_E,_O};
//code BYTE Svideo_Jpn[] = {_S,_minus,_V,_I,_D,_E,_O};

code BYTE * code Svideo[] = {
	Svideo_Eng//,
	//Svideo_Kor,
	//Svideo_Jpn
};

code BYTE Svideo_Sizeof[] = {
	sizeof(Svideo_Eng)//,
	//sizeof(Svideo_Kor),
	//sizeof(Svideo_Jpn)
};

/*
/////////////////////////////////////////////////////////////////////
//	PIP
/////////////////////////////////////////////////////////////////////
code BYTE Pip_Eng[] = {0x00,_2iPipL,_2iPipR,0x00,_P,_I,_P};
code BYTE Pip_Kor[] = {0x00,_2iPipL,_2iPipR,0x00,_P,_I,_P};
code BYTE Pip_Jpn[] = {0x00,_2iPipL,_2iPipR,0x00,_P,_I,_P};

code BYTE * code Pip[] = {
	Pip_Eng,
	Pip_Kor,
	Pip_Jpn
};

code BYTE Pip_Sizeof[] = {
	sizeof(Pip_Eng),
	sizeof(Pip_Kor),
	sizeof(Pip_Jpn)
};
*/

/////////////////////////////////////////////////////////////////////
//	PIP
/////////////////////////////////////////////////////////////////////
code BYTE PipSub_Eng[] = {_P,_I,_P};
//code BYTE PipSub_Kor[] = {_P,_I,_P};
//code BYTE PipSub_Jpn[] = {_P,_I,_P};

code BYTE * code PipSub[] = {
	PipSub_Eng//,
	//PipSub_Kor,
	//PipSub_Jpn,
};

code BYTE PipSub_Sizeof[] = {
	sizeof(PipSub_Eng)//,
	//sizeof(PipSub_Kor),
	//sizeof(PipSub_Jpn)
};

#ifdef USE_PALSECAMtuner
/////////////////////////////////////////////////////////////////////
//	Left
/////////////////////////////////////////////////////////////////////
code BYTE Left_Eng[] = {_L,_E,_F,_T};
code BYTE Left_Chi[] = {CH_LEFT};
code BYTE * code Left[] = {
	Left_Eng,
	Left_Chi
};
code BYTE Left_Sizeof[] = {
	sizeof(Left_Eng),
	sizeof(Left_Chi)
};
/////////////////////////////////////////////////////////////////////
//	Right
/////////////////////////////////////////////////////////////////////
code BYTE Right_Eng[] = {_R,_I,_G,_H,_T};
code BYTE Right_Chi[] = {CH_RIGHT};
code BYTE * code Right[] = {
	Right_Eng,
	Right_Chi
};
code BYTE Right_Sizeof[] = {
	sizeof(Right_Eng),
	sizeof(Right_Chi)
};
/////////////////////////////////////////////////////////////////////
//	Center
/////////////////////////////////////////////////////////////////////
code BYTE Center_Eng[] = {_C,_E,_N,_T,_E,_R};
code BYTE Center_Chi[] = {CH_MIDDLE};
code BYTE * code Center[] = {
	Center_Eng,
	Center_Chi
};
code BYTE Center_Sizeof[] = {
	sizeof(Center_Eng),
	sizeof(Center_Chi)
};
#else
/////////////////////////////////////////////////////////////////////
//	Left
/////////////////////////////////////////////////////////////////////
code BYTE Left[] = {_L,_E,_F,_T};
/////////////////////////////////////////////////////////////////////
//	Right
/////////////////////////////////////////////////////////////////////
code BYTE Right[] = {_R,_I,_G,_H,_T};
/////////////////////////////////////////////////////////////////////
//	Center
/////////////////////////////////////////////////////////////////////
code BYTE Center[] = {_C,_E,_N,_T,_E,_R};
#endif


/////////////////////////////////////////////////////////////////////
//	Top
/////////////////////////////////////////////////////////////////////
code BYTE Top_Eng[] = {_T,_O,_P};
code BYTE * code Top[] = {
	Top_Eng
};
code BYTE Top_Sizeof[] = {
	sizeof(Top_Eng)
};
/////////////////////////////////////////////////////////////////////
//	Bottom
/////////////////////////////////////////////////////////////////////
code BYTE Bottom_Eng[] = {_B,_O,_T,_T,_O,_M};
code BYTE * code Bottom[] = {
	Bottom_Eng
};
code BYTE Bottom_Sizeof[] = {
	sizeof(Bottom_Eng)
};

/////////////////////////////////////////////////////////////////////
//	SEC
/////////////////////////////////////////////////////////////////////
code BYTE Sec_Eng[] = {_S,_E,_C};

code BYTE * code Sec[] = {
		Sec_Eng
};

code BYTE Sec_Sizeof[] = {
	sizeof(Sec_Eng)
};

/////////////////////////////////////////////////////////////////////
//	MINUTE
/////////////////////////////////////////////////////////////////////
code BYTE Minute_Eng[] = {_M,_I,_N};
code BYTE * code Minute[] = {
	Minute_Eng
};

code BYTE Minute_Sizeof[] = {
	sizeof(Minute_Eng)
};

/////////////////////////////////////////////////////////////////////
//	CABLE
/////////////////////////////////////////////////////////////////////
code BYTE Cable_Eng[] = {_C,_A,_B,_L,_E};
code BYTE Cable_Kor[] = {_C,_A,_B,_L,_E};
code BYTE Cable_Jpn[] = {_C,_A,_B,_L,_E};

code BYTE * code Cable[] = {
	Cable_Eng,
	Cable_Kor,
	Cable_Jpn
};

code BYTE Cable_Sizeof[] = {
	sizeof(Cable_Eng),
	sizeof(Cable_Kor),
	sizeof(Cable_Jpn)
};

#if 0		
/////////////////////////////////////////////////////////////////////
//	CHANNEL
/////////////////////////////////////////////////////////////////////
code BYTE Channel_Eng[] = {0x00,_2iChannelL,_2iChannelR,0x00,_C,_H,_A,_N,_N,_E,_L};
code BYTE Channel_Kor[] = {0x00,_2iChannelL,_2iChannelR,0x00,_C,_H,_A,_N,_N,_E,_L};
code BYTE Channel_Jpn[] = {0x00,_2iChannelL,_2iChannelR,0x00,_C,_H,_A,_N,_N,_E,_L};

code BYTE * code Channel[] = {
	Channel_Eng,
    	Channel_Kor,
    	Channel_Jpn
};

code BYTE Channel_Sizeof[] = {
	sizeof(Channel_Eng),
	sizeof(Channel_Kor),
	sizeof(Channel_Jpn)
};
#endif

/////////////////////////////////////////////////////////////////////
//	COLORSUB
/////////////////////////////////////////////////////////////////////
code BYTE ColorSub_Eng[] = {_C,_O,_L,_O,_R};
code BYTE ColorSub_Kor[] = {_SAEK,_NONG,_DO};
code BYTE ColorSub_Jpn[] = {J_COLOR};

code BYTE * code ColorSub[] = {
	ColorSub_Eng,
    	ColorSub_Kor,
	ColorSub_Jpn
};

code BYTE ColorSub_Sizeof[] = {
	sizeof(ColorSub_Eng),
	sizeof(ColorSub_Kor),
	sizeof(ColorSub_Jpn)
};

/////////////////////////////////////////////////////////////////////
//	TINT
/////////////////////////////////////////////////////////////////////
code BYTE Tint_Eng[] = {_T,_I,_N,_T};
code BYTE Tint_Kor[] = {_SAEK,_SANG};
code BYTE Tint_Jpn[] = {J_TINT};

code BYTE * code Tint[] = {
	Tint_Eng,
    	Tint_Kor,
	Tint_Jpn
};

code BYTE Tint_Sizeof[] = {
	sizeof(Tint_Eng),
	sizeof(Tint_Kor),
	sizeof(Tint_Jpn)
};

/////////////////////////////////////////////////////////////////////
//	COUNTRY
/////////////////////////////////////////////////////////////////////
code BYTE Country_Eng[] = {_C,_O,_U,_N,_T,_R,_Y};
code BYTE Country_Kor[] = {_GOOK,_GA,_SEOL,_JUNG};
code BYTE Country_Jpn[] = {J_COUNTRY};

code BYTE * code Country[] = {
	Country_Eng,
	Country_Kor,
	Country_Jpn
};

code BYTE Country_Sizeof[] = {
	sizeof(Country_Eng),
	sizeof(Country_Kor),
	sizeof(Country_Jpn)
};

/////////////////////////////////////////////////////////////////////
//	auto setup
/////////////////////////////////////////////////////////////////////
code BYTE AutoSetup_Eng[] = {_A,_U,_T,_O,0,_S,_E,_T,_U,_P};
code BYTE AutoSetup_Kor[] = {_CHAE,_NULL,_JA,_DONG,_SEOL,_JUNG};
code BYTE AutoSetup_Jpn[] = {J_AUTO_SETUP};

code BYTE * code AutoSetup[] = {
	AutoSetup_Eng,
	AutoSetup_Kor,
	AutoSetup_Jpn
};

code BYTE AutoSetup_Sizeof[] = {
	sizeof(AutoSetup_Eng),
	sizeof(AutoSetup_Kor),
	sizeof(AutoSetup_Jpn)
};

/////////////////////////////////////////////////////////////////////
//	CHANNEL EDIT
/////////////////////////////////////////////////////////////////////
code BYTE ChannelEdit_Eng[] = {_C,_H,_A,_N,_N,_E,_L,0,_E,_D,_I,_T};
code BYTE ChannelEdit_Kor[] = {_CHAE,_NULL,_PYEON,_JIP};
code BYTE ChannelEdit_Jpn[] = {J_CHANNEL_EDIT};

code BYTE * code ChannelEdit[] = {
	ChannelEdit_Eng,
	ChannelEdit_Kor,
	ChannelEdit_Jpn
};

code BYTE ChannelEdit_Sizeof[] = {
	sizeof(ChannelEdit_Eng),
	sizeof(ChannelEdit_Kor),
	sizeof(ChannelEdit_Jpn)
};

#ifdef	Ccd_Vchip
/////////////////////////////////////////////////////////////////////
//	CCD
/////////////////////////////////////////////////////////////////////
code BYTE Ccd[] = {_C,_C,_D};

code BYTE ClosedCaption[] = {_C,_l,_o,_s,_e,_d,0,_C,_a,_p,_t,_i,_o,_n};
code BYTE Caption[] = {_C,_A,_P,_T,_I,_O,_N};
code BYTE Mode[] = {_M,_O,_D,_E};
code BYTE Channel_char[] = {_C,_H,_A,_N,_N,_E,_L};
code BYTE Field[] = {_F,_I,_E,_L,_D};
code BYTE Display[] = {_D,_I,_S,_P,_L,_A,_Y};

/////////////////////////////////////////////////////////////////////
//	V-chip
/////////////////////////////////////////////////////////////////////
code BYTE Vchip[] = {_V,_minus,_c,_h,_i,_p};

//
code BYTE CcdEnterPin[] = {_E,_n,_t,_e,_r,0,_P,_i,_n,0,_Colon,0,_UnderBar,_UnderBar,_UnderBar,_UnderBar};
//code BYTE MotionPicture[] = {_M,_o,_t,_i,_o,_n,0,_P,_i,_c,_t,_u,_r,_e};
code BYTE MotionPicture[] = {_M,_O,_T,_I,_O,_N,0,_P,_I,_C,_T,_U,_R,_E};
//code BYTE ParentalGuide[] = {_T,_V,0,_P,_a,_r,_e,_n,_t,_a,_l,0,_G,_u,_i,_d,_e};
code BYTE ParentalGuide[] = {_T,_V,0,_P,_A,_R,_E,_N,_T,_A,_L,0,_G,_U,_I,_D,_E};
//code BYTE ChangeCode[] = {_C,_h,_a,_n,_g,_e,0,_C,_o,_d,_e};
code BYTE ChangeCode[] = {_C,_H,_A,_N,_G,_E,0,_C,_O,_D,_E};
//code BYTE RatingChange[] = {_RTriAngle,0,_R,_a,_t,_i,_n,_g,0,_C,_h,_a,_n,_g,_e};
code BYTE RatingChange[] = {_RTriAngle,0,_R,_A,_T,_I,_N,_G,0,_C,_H,_A,_N,_G,_E};

//code BYTE NoRating[] = {_N,_O,0,_R,_A,_T,_I,_N,_G,0,_V,_I,_E,_W};
code BYTE NoRating[] = {_N,_o,0,_R,_a,_t,_i,_n,_g,0,_V,_i,_e,_w};
code BYTE vchipGP13[] = {_P,_G,_minus,_1,_3};
code BYTE vchipNC17[] = {_N,_C,_minus,_1,_7};
#if 1
code BYTE tvY[] = {_T,_V,_minus,_Y,0,0,_UnderBar};
code BYTE tvY7[] = {_T,_V,_minus,_Y,_7,0,_UnderBar};
code BYTE tvG[] = {_T,_V,_minus,_G,0,0,_UnderBar};
code BYTE tvPG[] = {_T,_V,_minus,_P,_G,0,_UnderBar};
code BYTE tv14[] = {_T,_V,_minus,_1,_4,0,_UnderBar};
code BYTE tvMA[] = {_T,_V,_minus,_M,_A,0,_UnderBar};
code BYTE tvFV[] = {_Lbar,_F,_Rbar,_V,_UnderBar};
code BYTE tvDLSV[] = {_D,_UnderBar,0,_L,_UnderBar,0,_S,_UnderBar,0,_V,_UnderBar};
code BYTE tvLSV[] = {0,0,0,_L,_UnderBar,0,_S,_UnderBar,0,_V,_UnderBar};
#else
code BYTE tvY[] = {_T,_V,_minus,_Y,0,0,_checkOff};
code BYTE tvY7[] = {_T,_V,_minus,_Y,_7,0,_checkOff};
code BYTE tvG[] = {_T,_V,_minus,_G,0,0,_checkOff};
code BYTE tvPG[] = {_T,_V,_minus,_P,_G,0,_checkOff};
code BYTE tv14[] = {_T,_V,_minus,_1,_4,0,_checkOff};
code BYTE tvMA[] = {_T,_V,_minus,_M,_A,0,_checkOff};
code BYTE tvFV[] = {_Lbar,_F,_Rbar,_V,_checkOff};
code BYTE tvDLSV[] = {_D,_checkOff,0,_L,_checkOff,0,_S,_checkOff,0,_V,_checkOff};
code BYTE tvLSV[] = {0,0,0,_L,_checkOff,0,_S,_checkOff,0,_V,_checkOff};
#endif

code BYTE CcdOldCode[] = {_O,_L,_D,0,_C,_O,_D,_E,0,_Colon,0,_UnderBar,_UnderBar,_UnderBar,_UnderBar};
code BYTE CcdNewCode[] = {_N,_E,_W,0,_C,_O,_D,_E,0,_Colon,0,_UnderBar,_UnderBar,_UnderBar,_UnderBar};
//code BYTE CcdRepeatCode[] = {_R,_E,_P,_E,_A,_T,0,_C,_O,_D,_E,0,_Colon,0,_UnderBar,_UnderBar,_UnderBar,_UnderBar};
code BYTE CcdRepeatCode[] = {_C,_O,_N,_F,_I,_R,_M,0,0,_Colon,0,_UnderBar,_UnderBar,_UnderBar,_UnderBar};
#endif

/////////////////////////////////////////////////////////////////////
//	ANTENA INPUT
/////////////////////////////////////////////////////////////////////
code BYTE AntenaInput_Eng[] = {_A,_N,_T,_E,_N,_A,0,_I,_N,_P,_U,_T};
code BYTE AntenaInput_Kor[] = {_AHN,_TE,_NA,_EIP,_YERK};
code BYTE AntenaInput_Jpn[] = {J_ANTENA_INPUT};

code BYTE * code AntenaInput[] = {
	AntenaInput_Eng,
	AntenaInput_Kor,
	AntenaInput_Jpn
};

code BYTE AntenaInput_Sizeof[] = {
	sizeof(AntenaInput_Eng),
	sizeof(AntenaInput_Kor),
	sizeof(AntenaInput_Jpn)
};

code BYTE Normal[] = {_N,_O,_R,_M,_A,_L};
//code BYTE Normal_Chi[] = {CH_NORMAL};
//code BYTE Normal2[] = {_N,0,_O,0,_R,0,_M,0,_A,0,_L};
code BYTE Dynamic[] = {_D,_Y,_N,_A,_M,_I,_C};
//code BYTE Dynamic_Chi[] = {CH_DYNAMIC};
//code BYTE Dynamic2[] = {_D,0,_Y,0,_N,0,_A,0,_M,0,_I,0,_C};
code BYTE Cinema[] = {_C,_I,_N,_E,_M,_A};
//code BYTE Cinema_Chi[] = {CH_CINEMA};
//code BYTE Cinema2[] = {_C,0,_I,0,_N,0,_E,0,_M,0,_A};
code BYTE User[] = {_U,_S,_E,_R};
//code BYTE User_Chi[] = {CH_USER};
//code BYTE User2[] = {_U,0,_S,0,_E,0,_R};

#if 0
code BYTE Normal2[] = {_N,0,_O,0,_R,0,_M,0,_A,0,_L};
code BYTE Dynamic2[] = {_D,0,_Y,0,_N,0,_A,0,_M,0,_I,0,_C};
code BYTE Cinema2[] = {_C,0,_I,0,_N,0,_E,0,_M,0,_A};
code BYTE User2[] = {_U,0,_S,0,_E,0,_R};
#else
/////////////////////////////////////////////////////////////////////
//	NORMAL2
/////////////////////////////////////////////////////////////////////
code BYTE Normal2_Eng[] = {_N,0,_O,0,_R,0,_M,0,_A,0,_L};
code BYTE * code Normal2[] = {
	Normal2_Eng
};
code BYTE Normal2_Sizeof[] = {
	sizeof(Normal2_Eng)
};
/////////////////////////////////////////////////////////////////////
//	DYNANIC2
/////////////////////////////////////////////////////////////////////
code BYTE Dynamic2_Eng[] = {_D,0,_Y,0,_N,0,_A,0,_M,0,_I,0,_C};
code BYTE * code Dynamic2[] = {
	Dynamic2_Eng
};
code BYTE Dynamic2_Sizeof[] = {
	sizeof(Dynamic2_Eng)
};
/////////////////////////////////////////////////////////////////////
//	CINEMA2
/////////////////////////////////////////////////////////////////////
code BYTE Cinema2_Eng[] = {_C,0,_I,0,_N,0,_E,0,_M,0,_A};
code BYTE * code Cinema2[] = {
	Cinema2_Eng
};
code BYTE Cinema2_Sizeof[] = {
	sizeof(Cinema2_Eng)
};
/////////////////////////////////////////////////////////////////////
//	USER2
/////////////////////////////////////////////////////////////////////
code BYTE User2_Eng[] = {_U,0,_S,0,_E,0,_R};
code BYTE * code User2[] = {
	User2_Eng
};
code BYTE User2_Sizeof[] = {
	sizeof(User2_Eng)
};
#endif


code BYTE Wide_Eng[] = {_W,_I,_D,_E};
#if 0
/////////////////////////////////////////////////////////////////////
//	WIDE
/////////////////////////////////////////////////////////////////////
code BYTE Wide_Eng[] = {_W,_I,_D,_E};
code BYTE Wide_Kor[] = {_W,_I,_D,_E};
code BYTE Wide_Jpn[] = {_W,_I,_D,_E};

code BYTE * code Wide[] = {
	Wide_Eng,
	Wide_Kor,
	Wide_Jpn
};

code BYTE Wide_Sizeof[] = {
	sizeof(Wide_Eng),
	sizeof(Wide_Kor),
	sizeof(Wide_Jpn)
};
#endif

#ifdef  USE_NTSCtuner
code BYTE Music[] = {_M,_U,_S,_I,_C};
code BYTE News[] = {_N,_E,_W,_S};
#else	//old------------------------------
//	MUSIC : smpark 20030722
code BYTE Music_Eng[] = {_M,_U,_S,_I,_C};
code BYTE Music_Chi[] = {CH_MUSIC};
code BYTE * code Music[] = {
	Music_Eng,
	Music_Chi
};
code BYTE Music_Sizeof[] = {
	sizeof(Music_Eng),
	sizeof(Music_Chi)
};
//	NEWS : smpark 20030722
code BYTE News_Eng[] = {_N,_E,_W,_S};
code BYTE News_Chi[] = {_N,_E,_W,_S};
code BYTE * code News[] = {
	News_Eng,
	News_Chi
};
code BYTE News_Sizeof[] = {
	sizeof(News_Eng),
	sizeof(News_Chi)
};
#endif

#if 1
code BYTE Mono[] = {_M,_O,_N,_O};
code BYTE Stereo[] = {_S,_T,_E,_R,_E,_O};
#else	//old------------------------------
//	MONO : smpak 20030722
code BYTE Mono_Eng[] = {_M,_O,_N,_O};
code BYTE Mono_Chi[] = {_M,_O,_N,_O};
code BYTE * code Mono[] = {
	Mono_Eng,
	Mono_Chi
};
code BYTE Mono_Sizeof[] = {
	sizeof(Mono_Eng),
	sizeof(Mono_Chi)
};
//	STEREO: smpark 20030722
code BYTE Stereo_Eng[] = {_S,_T,_E,_R,_E,_O};
code BYTE Stereo_Chi[] = {_S,_T,_E,_R,_E,_O};
code BYTE * code Stereo[] = {
	Stereo_Eng,
	Stereo_Chi
};
code BYTE Stereo_Sizeof[] = {
	sizeof(Stereo_Eng),
	sizeof(Stereo_Chi)
};
#endif

#if 0
code BYTE Music2[] = {_M,0,_U,0,_S,0,_I,0,_C};
code BYTE News2[] = {_N,0,_E,0,_W,0,_S};
#else	//old------------------------------
code BYTE Music2_Eng[] = {_M,0,_U,0,_S,0,_I,0,_C};
code BYTE * code Music2[] = {
	Music2_Eng
};
code BYTE Music2_Sizeof[] = {
	sizeof(Music2_Eng)
};
code BYTE News2_Eng[] = {_N,0,_E,0,_W,0,_S};
code BYTE * code News2[] = {
	News2_Eng
};
code BYTE News2_Sizeof[] = {
	sizeof(News2_Eng)
};
#endif

//	LANGUAGE OPTION: smpark 20030722
//********************************************
code BYTE LangA_Eng[] = {_L,_A,_N,_G,0,_A};
code BYTE * code LangA[] = {
	LangA_Eng
};
code BYTE LangA_Sizeof[] = {
	sizeof(LangA_Eng)
};
//********************************************
code BYTE LangB_Eng[] = {_L,_A,_N,_G,0,_B};
code BYTE * code LangB[] = {
	LangB_Eng
};
code BYTE LangB_Sizeof[] = {
	sizeof(LangB_Eng)
};
//********************************************
code BYTE LangAB_Eng[] = {_L,_A,_N,_G,0,_A,_B};
code BYTE * code LangAB[] = {
	LangAB_Eng
};
code BYTE LangAB_Sizeof[] = {
	sizeof(LangAB_Eng)
};

#if 0
// 20030822
// MTS
code BYTE MultiSound_Eng[] = {_M,_T,_S};
code BYTE MultiSound_Kor[] = {_M,_T,_S};
code BYTE MultiSound_Jpn[] = {_M,_T,_S};

code BYTE * code MultiSound[] = {
	MultiSound_Eng,
	MultiSound_Kor,
	MultiSound_Jpn
};

code BYTE MultiSound_Sizeof[] = {
	sizeof(MultiSound_Eng),
	sizeof(MultiSound_Kor),
	sizeof(MultiSound_Jpn)
};
#endif

// 20030821
// TREBLE
code BYTE Treble_Eng[] = {_T,_R,_E,_B,_L,_E};
code BYTE Treble_Kor[] = {_GO,_EUM,_JO,_JUNG};
code BYTE Treble_Jpn[] = {J_TREBLE};

code BYTE * code Treble[] = {
	Treble_Eng,
	Treble_Kor,
	Treble_Jpn
};

code BYTE Treble_Sizeof[] = {
	sizeof(Treble_Eng),
	sizeof(Treble_Kor),
	sizeof(Treble_Jpn)
};

// TREBLE
code BYTE Bass_Eng[] = {_B,_A,_S,_S};
code BYTE Bass_Kor[] = {_JER,_EUM,_JO,_JUNG};
code BYTE Bass_Jpn[] = {J_BASS};

code BYTE * code Bass[] = {
	Bass_Eng,
	Bass_Kor,
	Bass_Jpn
};

code BYTE Bass_Sizeof[] = {
	sizeof(Bass_Eng),
	sizeof(Bass_Kor),
	sizeof(Bass_Jpn)
};

// LOUDNESS
code BYTE Loudness_Eng[] = {_L,_O,_U,_D,_N,_E,_S,_S};
code BYTE Loudness_Kor[] = {_L,_O,_U,_D,_N,_E,_S,_S};
code BYTE Loudness_Jpn[] = {J_LOUDNESS};

code BYTE * code Loudness[] = {
	Loudness_Eng,
	Loudness_Kor,
	Loudness_Jpn
};

code BYTE Loudness_Sizeof[] = {
	sizeof(Loudness_Eng),
	sizeof(Loudness_Kor),
	sizeof(Loudness_Jpn)
};

// SMART SOUND CONTROL
code BYTE SmartSound_Eng[] = {_S,_M,_A,_R,_T,0,_S,_O,_U,_N,_D,0,_C,_O,_N,_T,_R,_O,_L};
code BYTE SmartSound_Kor[] = {_S,_M,_A,_R,_T,0,_S,_O,_U,_N,_D,0,_C,_O,_N,_T,_R,_O,_L};		
code BYTE SmartSound_Jpn[] = {J_SSC};

code BYTE * code SmartSound[] = {
	SmartSound_Eng,
	SmartSound_Kor,
	SmartSound_Jpn
};

code BYTE SmartSound_Sizeof[] = {
	sizeof(SmartSound_Eng),
	sizeof(SmartSound_Kor),
	sizeof(SmartSound_Jpn)
};

/////////////////////////////////////////////////////////////////////
//	WAITING
/////////////////////////////////////////////////////////////////////
code BYTE Wait_Eng[] = {_P,_L,_E,_A,_S,_E,_space,_W,_A,_I,_T};
code BYTE Wait_Kor[] = {_P,_L,_E,_A,_S,_E,_space,_W,_A,_I,_T};
code BYTE Wait_Jpn[] = {_P,_L,_E,_A,_S,_E,_space,_W,_A,_I,_T};

code BYTE * code Wait[] = {
	Wait_Eng,
	Wait_Kor,
	Wait_Jpn
	
};
code BYTE Wait_Sizeof[] = {
	sizeof(Wait_Eng),
	sizeof(Wait_Kor),
	sizeof(Wait_Jpn)
};

/////////////////////////////////////////////////////////////////////
//	AIR
/////////////////////////////////////////////////////////////////////
code BYTE Air_Eng[] = {_A,_I,_R};
code BYTE Air_Kor[] = {_A,_I,_R};
code BYTE Air_Jpn[] = {_A,_I,_R};

code BYTE * code Air[] = {
	Air_Eng,
    	Air_Kor,
    	Air_Jpn
};

code BYTE Air_Sizeof[] = {
	sizeof(Air_Eng),
	sizeof(Air_Kor),
	sizeof(Air_Jpn)
};

/////////////////////////////////////////////////////////////////////
//	CATV
/////////////////////////////////////////////////////////////////////
code BYTE Catv_Eng[] = {_C,_A,_T,_V};
code BYTE Catv_Kor[] = {_C,_A,_T,_V};
code BYTE Catv_Jpn[] = {_C,_A,_T,_V};

code BYTE * code Catv[] = {
	Catv_Eng,
    	Catv_Kor,
    	Catv_Jpn
};

code BYTE Catv_Sizeof[] = {
	sizeof(Catv_Eng),
	sizeof(Catv_Kor),
	sizeof(Catv_Jpn)
};

#if 0
/////////////////////////////////////////////////////////////////////
//	CH
/////////////////////////////////////////////////////////////////////
code BYTE Ch_Eng[] = {_C,_H};
//code BYTE Ch_Kor[] = {_C,_H};
//code BYTE Ch_Jpn[] = {_C,_H};

code BYTE * code Chdot[] = {
	Ch_Eng//,
	//Ch_Kor,
	//Ch_Jpn
};

code BYTE Chdot_Sizeof[] = {
	sizeof(Ch_Eng)//,
	//sizeof(Ch_Kor),
	//sizeof(Ch_Jpn)
};

#ifdef  ChannelDisplayDouble
/////////////////////////////////////////////////////////////////////
//	CH2
/////////////////////////////////////////////////////////////////////
code BYTE Ch2_Eng[] = {_C,0,_H};
code BYTE * code Chdot2[] = {
	Ch2_Eng
};
code BYTE Chdot2_Sizeof[] = {
	sizeof(Ch2_Eng)
};

code BYTE Catv2_Eng[] = {_C,0,_A,0,_T,0,_V};
code BYTE * code Catv2[] = {
	Catv2_Eng
};
code BYTE Catv2_Sizeof[] = {
	sizeof(Catv2_Eng)
}; 
#endif  
#else//------------

/////////////////////////////////////////////////////////////////////
//	CH
code BYTE Chdot[] = {_C,_H};
#ifdef  ChannelDisplayDouble
/////////////////////////////////////////////////////////////////////
//	CH2
code BYTE Chdot2[] = {_C,0,_H};
//	CATV
code BYTE Catv2[] = {_C,0,_A,0,_T,0,_V};
#endif  

#endif	//-------------------

#if 0
/////////////////////////////////////////////////////////////////////
//	AUTO CHANNEL
/////////////////////////////////////////////////////////////////////
code BYTE AutoChannel_Eng[] = {_A,_U,_T,_O,0x00,_C,_H,_A,_N,_N,_E,_L};
code BYTE AutoChannel_Kor[] = {_A,_U,_T,_O,0x00,_C,_H,_A,_N,_N,_E,_L};
code BYTE AutoChannel_Jpn[] = {_A,_U,_T,_O,0x00,_C,_H,_A,_N,_N,_E,_L};

code BYTE * code AutoChannel[] = {
	AutoChannel_Eng,
    	AutoChannel_Kor,
	AutoChannel_Jpn
};

code BYTE AutoChannel_Sizeof[] = {
	sizeof(AutoChannel_Eng),
	sizeof(AutoChannel_Kor),
	sizeof(AutoChannel_Jpn)
};

/////////////////////////////////////////////////////////////////////
//	STOP
/////////////////////////////////////////////////////////////////////
code BYTE Stop_Eng[] = {_S,_T,_O,_P};
code BYTE Stop_Kor[] = {_S,_T,_O,_P};
code BYTE Stop_Jpn[] = {_S,_T,_O,_P};

code BYTE * code Stop[] = {
	Stop_Eng,
	Stop_Kor,
	Stop_Jpn
};

code BYTE Stop_Sizeof[] = {
	sizeof(Stop_Eng),
	sizeof(Stop_Kor),
	sizeof(Stop_Jpn)
};
/////////////////////////////////////////////////////////////////////
//	START
code BYTE Start_Eng[] = {_S,_T,_A,_R,_T};
code BYTE * code Start[] = {
	Start_Eng
};

code BYTE Start_Sizeof[] = {
	sizeof(Start_Eng)
};


#endif

/////////////////////////////////////////////////////////////////////
//	START
/////////////////////////////////////////////////////////////////////
code BYTE Start_Eng[] = {_S,_T,_A,_R,_T};
code BYTE Start_Chi[] = {CH_START};

code BYTE * code Start[] = {
		Start_Eng,
    	Start_Chi
};

code BYTE Start_Sizeof[] = {
	sizeof(Start_Eng),
	sizeof(Start_Chi)
};
/////////////////////////////////////////////////////////////////////
//	SEARCHING
/////////////////////////////////////////////////////////////////////
code BYTE Searching_Eng[] = {_S,_E,_A,_R,_C,_H};
code BYTE Searching_Kor[] = {_S,_E,_A,_R,_C,_H};
code BYTE Searching_Jpn[] = {_S,_E,_A,_R,_C,_H};

code BYTE * code Searching[] = {
	Searching_Eng,
    	Searching_Kor,
    	Searching_Jpn
};

code BYTE Searching_Sizeof[] = {
	sizeof(Searching_Eng),
	sizeof(Searching_Kor),
	sizeof(Searching_Jpn)
};

/////////////////////////////////////////////////////////////////////
//	PRESS SELECT TO STOP
/////////////////////////////////////////////////////////////////////
code BYTE Press_Eng[] = {_P,_R,_E,_S,_S,0x00,_S,_E,_L,_E,_C,_T,0x00,_T,_O,0x00,_S,_T,_O,_P};
code BYTE Press_Kor[] = {_P,_R,_E,_S,_S,0x00,_S,_E,_L,_E,_C,_T,0x00,_T,_O,0x00,_S,_T,_O,_P};
code BYTE Press_Jpn[] = {_P,_R,_E,_S,_S,0x00,_S,_E,_L,_E,_C,_T,0x00,_T,_O,0x00,_S,_T,_O,_P};

code BYTE * code Press[] = {
	Press_Eng,
    	Press_Kor,
    	Press_Jpn
};

code BYTE Press_Sizeof[] = {
	sizeof(Press_Eng),
	sizeof(Press_Kor),
	sizeof(Press_Jpn)
};

/////////////////////////////////////////////////////////////////////
//	PROCESSING
/////////////////////////////////////////////////////////////////////
code BYTE Processing_Eng[] = {_P,_R,_O,_C,_E,_S,_S,_I,_N,_G};
code BYTE Processing_Kor[] = {_P,_R,_O,_C,_E,_S,_S,_I,_N,_G};
code BYTE Processing_Jpn[] = {_P,_R,_O,_C,_E,_S,_S,_I,_N,_G};

code BYTE * code Processing[] = {
	Processing_Eng,
    	Processing_Kor,
    	Processing_Jpn,
};

code BYTE Processing_Sizeof[] = {
	sizeof(Processing_Eng),
	sizeof(Processing_Kor),
	sizeof(Processing_Jpn)
};


/////////////////////////////////////////////////////////////////////
//	AUTO CONFIGURATION
/////////////////////////////////////////////////////////////////////
code BYTE AutoConfig_Eng[] = {_A,_U,_T,_O,0x00,_C,_O,_N,_F,_I,_G,_U,_R,_A,_T,_I,_O,_N};
code BYTE AutoConfig_Kor[] = {_A,_U,_T,_O,0x00,_C,_O,_N,_F,_I,_G,_U,_R,_A,_T,_I,_O,_N};
code BYTE AutoConfig_Jpn[] = {_A,_U,_T,_O,0x00,_C,_O,_N,_F,_I,_G,_U,_R,_A,_T,_I,_O,_N};

code BYTE * code AutoConfig[] = {
	AutoConfig_Eng,
    	AutoConfig_Kor,
    	AutoConfig_Jpn
};

code BYTE AutoConfig_Sizeof[] = {
	sizeof(AutoConfig_Eng),
	sizeof(AutoConfig_Kor),
	sizeof(AutoConfig_Jpn)
};

//	AUTO TUNE
/////////////////////////////////////////////////////////////////////
code BYTE AutoTune_Eng[] = {_A,_U,_T,_O,0x00,_T,_U,_N,_E};
code BYTE AutoTune_Kor[] = {_JA,_DONG,_JO,_JUNG};
code BYTE AutoTune_Jpn[] = {J_AUTO_TUNE};

code BYTE * code AutoTune[] = {
	AutoTune_Eng,
    	AutoTune_Kor,
    	AutoTune_Jpn
};

code BYTE AutoTune_Sizeof[] = {
	sizeof(AutoTune_Eng),
	sizeof(AutoTune_Kor),
	sizeof(AutoTune_Jpn)
};

/////////////////////////////////////////////////////////////////////
//	MANUAL CHANNEL
/////////////////////////////////////////////////////////////////////
code BYTE ManualChannel_Eng[] = {_M,_A,_N,_U,_A,_L,0x00,_C,_H,_A,_N,_N,_E,_L};
code BYTE ManualChannel_Kor[] = {_M,_A,_N,_U,_A,_L,0x00,_C,_H,_A,_N,_N,_E,_L};
code BYTE ManualChannel_Jpn[] = {_M,_A,_N,_U,_A,_L,0x00,_C,_H,_A,_N,_N,_E,_L};

code BYTE * code ManualChannel[] = {
	ManualChannel_Eng,
    	ManualChannel_Kor,
	ManualChannel_Jpn
};

code BYTE ManualChannel_Sizeof[] = {
	sizeof(ManualChannel_Eng),
	sizeof(ManualChannel_Kor),
	sizeof(ManualChannel_Jpn)
};

/////////////////////////////////////////////////////////////////////
//	FINE
/////////////////////////////////////////////////////////////////////
code BYTE Fine_Eng[] = {_F,_I,_N,_E};
code BYTE Fine_Kor[] = {_F,_I,_N,_E};
code BYTE Fine_Jpn[] = {_F,_I,_N,_E};

code BYTE * code Fine[] = {
	Fine_Eng,
    	Fine_Kor,
    	Fine_Jpn
};

code BYTE Fine_Sizeof[] = {
	sizeof(Fine_Eng),
	sizeof(Fine_Kor),
	sizeof(Fine_Jpn)
};

/////////////////////////////////////////////////////////////////////
//	EXIT SUB
/////////////////////////////////////////////////////////////////////
code BYTE ExitSub_Eng[] = {_E,_X,_I,_T,0,_S,_U,_B};
code BYTE ExitSub_Kor[] = {_E,_X,_I,_T,0,_S,_U,_B};
code BYTE ExitSub_Jpn[] = {_E,_X,_I,_T,0,_S,_U,_B};

code BYTE * code ExitSub[] = {
	ExitSub_Eng,
    	ExitSub_Kor,
    	ExitSub_Jpn
};

code BYTE ExitSub_Sizeof[] = {
	sizeof(ExitSub_Eng),
	sizeof(ExitSub_Kor),
	sizeof(ExitSub_Jpn)
};

/////////////////////////////////////////////////////////////////////
//	FINE TURN
/////////////////////////////////////////////////////////////////////
code BYTE FineTune_Eng[] = {_F,_I,_N,_E,0,_T,_U,_N,_E};
code BYTE FineTune_Kor[] = {_CHAE,_NULL,_JUNG,_MIL,_JO,_JUNG};
code BYTE FineTune_Jpn[] = {J_FINE_TUNE};

code BYTE * code FineTune[] = {
	FineTune_Eng,
   	FineTune_Kor,
	FineTune_Jpn
};

code BYTE FineTune_Sizeof[] = {
	sizeof(FineTune_Eng),
	sizeof(FineTune_Kor),
	sizeof(FineTune_Jpn)
};

/////////////////////////////////////////////////////////////////////
//	BLUE SCREEN
/////////////////////////////////////////////////////////////////////
code BYTE BlueScreen_Eng[] = {_B,_L,_U,_E,0,_S,_C,_R,_E,_E,_N};
code BYTE BlueScreen_Kor[] = {_CHUNG,_SAEK,_HWA,_MYUN};
code BYTE BlueScreen_Jpn[] = {J_BLUE_SCREEN};

code BYTE * code BlueScreen[] = {
	BlueScreen_Eng,
	BlueScreen_Kor,
	BlueScreen_Jpn
};

code BYTE BlueScreen_Sizeof[] = {
	sizeof(BlueScreen_Eng),
	sizeof(BlueScreen_Kor),
	sizeof(BlueScreen_Jpn)
};

/////////////////////////////////////////////////////////////////////
//	SCREEN MODE
/////////////////////////////////////////////////////////////////////
code BYTE ScreenMode_Eng[] = {_S,_C,_R,_E,_E,_N,0,_A,_S,_P,_E,_C,_T,0,_R,_A,_T,_I,_O};
code BYTE ScreenMode_Kor[] = {_HWA,_MYUN,_BI,_YULL};
code BYTE ScreenMode_Jpn[] = {J_WIDE};

code BYTE * code ScreenMode[] = {
	ScreenMode_Eng,
	ScreenMode_Kor,
	ScreenMode_Jpn
};
code BYTE ScreenMode_Sizeof[] = {
	sizeof(ScreenMode_Eng),
	sizeof(ScreenMode_Kor),
	sizeof(ScreenMode_Jpn)
};

/////////////////////////////////////////////////////////////////////
//	SMART PICTURE CONTROL
/////////////////////////////////////////////////////////////////////
code BYTE SmartPicture_Eng[] = {_S,_M,_A,_R,_T,0,_P,_I,_C,_T,_U,_R,_E,0,_C,_O,_N,_T,_R,_O,_L};
code BYTE SmartPicture_Kor[] = {_HWA,_MYUN,_MO,_DEA};
code BYTE SmartPicture_Jpn[] = {J_SPC};

code BYTE * code SmartPicture[] = {
	SmartPicture_Eng,
	SmartPicture_Kor,
	SmartPicture_Jpn
};
code BYTE SmartPicture_Sizeof[] = {
	sizeof(SmartPicture_Eng),
	sizeof(SmartPicture_Kor),
	sizeof(SmartPicture_Jpn)
};

/////////////////////////////////////////////////////////////////////
//	SLEEP
/////////////////////////////////////////////////////////////////////
code BYTE Sleep_Eng[] = {_S,_L,_E,_E,_P};
code BYTE Sleep_Kor[] = {_TA,_YI,_MER};
code BYTE Sleep_Jpn[] = {J_SLEEP};

code BYTE * code Sleep[] = {
	Sleep_Eng,
	Sleep_Kor,
	Sleep_Jpn
};
code BYTE Sleep_Sizeof[] = {
	sizeof(Sleep_Eng),
	sizeof(Sleep_Kor),
	sizeof(Sleep_Jpn)
};

/////////////////////////////////////////////////////////////////////
//	SLEEP2
/////////////////////////////////////////////////////////////////////
code BYTE Sleep2_Eng[] = {_S,0,_L,0,_E,0,_E,0,_P};
code BYTE * code Sleep2[] = {
	Sleep2_Eng
};
code BYTE Sleep2_Sizeof[] = {
	sizeof(Sleep2_Eng)
};

/////////////////////////////////////////////////////////////////////
//	ADD
/////////////////////////////////////////////////////////////////////
code BYTE Add_Eng[] = {_A,_D,_D};
code BYTE Add_Kor[] = {_A,_D,_D};
code BYTE Add_Jpn[] = {_A,_D,_D};

code BYTE * code Add[] = {
	Add_Eng,
    	Add_Kor,
    	Add_Jpn
};

code BYTE Add_Sizeof[] = {
	sizeof(Add_Eng),
	sizeof(Add_Kor),
	sizeof(Add_Jpn)
};

/////////////////////////////////////////////////////////////////////
//	Erase
/////////////////////////////////////////////////////////////////////
code BYTE Erase_Eng[] = {_E,_R,_A,_S,_E};
code BYTE * code Erase[] = {
	Erase_Eng,
};
code BYTE Erase_Sizeof[] = {
	sizeof(Erase_Eng),
};


#ifdef USE_NTSCtuner
/////////////////////////////////////////////////////////////////////
//	ON
/////////////////////////////////////////////////////////////////////
code BYTE On_Eng[] = {_O,_N};
code BYTE * code On[] = {
	On_Eng
};
code BYTE On_Sizeof[] = {
	sizeof(On_Eng)
};

/////////////////////////////////////////////////////////////////////
//	OFF
/////////////////////////////////////////////////////////////////////
code BYTE Off_Eng[] = {_O,_F,_F};
code BYTE * code Off[] = {
	Off_Eng
};
code BYTE Off_Sizeof[] = {
	sizeof(Off_Eng)
};
#else
/////////////////////////////////////////////////////////////////////
//	ON
/////////////////////////////////////////////////////////////////////
code BYTE On_Eng[] = {_O,_N};
code BYTE On_Chi[] = {CH_ON};
code BYTE * code On[] = {
	On_Eng,
	On_Chi
};
code BYTE On_Sizeof[] = {
	sizeof(On_Eng),
	sizeof(On_Chi)
};

/////////////////////////////////////////////////////////////////////
//	OFF
/////////////////////////////////////////////////////////////////////
code BYTE Off_Eng[] = {_O,_F,_F};
code BYTE Off_Chi[] = {CH_OFF};
code BYTE * code Off[] = {
	Off_Eng,
	Off_Chi
};
code BYTE Off_Sizeof[] = {
	sizeof(Off_Eng),
	sizeof(Off_Chi)
};
#endif
/////////////////////////////////////////////////////////////////////
//	dos 640*400	//2003-08-26
/////////////////////////////////////////////////////////////////////
code BYTE Dos640_Eng[] = {_6,_4,_0};
code BYTE * code Dos640[] = {
	Dos640_Eng
};
code BYTE Dos640_Sizeof[] = {
	sizeof(Dos640_Eng)
};
/////////////////////////////////////////////////////////////////////
//	dos 720*400	//2003-08-26
/////////////////////////////////////////////////////////////////////
code BYTE Dos720_Eng[] = {_7,_2,_0};
code BYTE * code Dos720[] = {
	Dos720_Eng
};
code BYTE Dos720_Sizeof[] = {
	sizeof(Dos720_Eng)
};

///MODE/////////////////////////////////////////////////////////
code BYTE Mode_Eng[] = {_M,_O,_D,_E};
code BYTE Mode_Chi[] = {CH_MODE};
code BYTE * code Mode[] = {
	Mode_Eng,
	Mode_Chi
};
code BYTE Mode_Sizeof[] = {
	sizeof(Mode_Eng),
	sizeof(Mode_Chi)
};

/////////////////////////////////////////////////////////////////////
//	YES
/////////////////////////////////////////////////////////////////////
code BYTE Yes_Eng[] = {_Y,_E,_S};
code BYTE Yes_Kor[] = {_Y,_E,_S};
code BYTE Yes_Jpn[] = {_Y,_E,_S};

code BYTE * code Yes[] = {
	Yes_Eng,
	Yes_Kor,
	Yes_Jpn
};

code BYTE Yes_Sizeof[] = {
	sizeof(Yes_Eng),
	sizeof(Yes_Kor),
	sizeof(Yes_Jpn)
};

/////////////////////////////////////////////////////////////////////
//	No
/////////////////////////////////////////////////////////////////////
code BYTE No_Eng[] = {_N,_O,0};
code BYTE No_Kor[] = {_N,_O,0};
code BYTE No_Jpn[] = {_N,_O,0};

code BYTE * code No[] = {
	No_Eng,
	No_Kor,
	No_Jpn
};

code BYTE No_Sizeof[] = {
	sizeof(No_Eng),
	sizeof(No_Kor),
	sizeof(No_Jpn)
};

/////////////////////////////////////////////////////////////////////
//	CAPTION
/////////////////////////////////////////////////////////////////////
code BYTE CcdCaption_Eng[] = {_C,_a,_p,_t,_i,_o,_n};

code BYTE * code CcdCaption[] = {
	CcdCaption_Eng
};

code BYTE CcdCaption_Sizeof[] = {
	sizeof(CcdCaption_Eng)
};
/////////////////////////////////////////////////////////////////////
//	Text
/////////////////////////////////////////////////////////////////////
code BYTE CcdText_Eng[] = {_T,_e,_x,_t,0,0,0};

code BYTE * code CcdText[] = {
	CcdText_Eng
};

code BYTE CcdText_Sizeof[] = {
	sizeof(CcdText_Eng)
};
/////////////////////////////////////////////////////////////////////
//	CAPTION
/////////////////////////////////////////////////////////////////////
code BYTE CcdBox_Eng[] = {_B,_o,_x,0,0,0};

code BYTE * code CcdBox[] = {
	CcdBox_Eng
};

code BYTE CcdBox_Sizeof[] = {
	sizeof(CcdBox_Eng)
};
/////////////////////////////////////////////////////////////////////
//	CAPTION
/////////////////////////////////////////////////////////////////////
code BYTE CcdShadow_Eng[] = {_S,_h,_a,_d,_o,_w};

code BYTE * code CcdShadow[] = {
	CcdShadow_Eng
};

code BYTE CcdShadow_Sizeof[] = {
	sizeof(CcdShadow_Eng)
};



/////////////////////////////////////////////////////////////////////
//	PIP ON/OFF
/////////////////////////////////////////////////////////////////////
code BYTE PipOnOff_Eng[] = {_P,_I,_P,0x00,_O,_N,_slash,_O,_F,_F};
code BYTE PipOnOff_Kor[] = {_P,_I,_P,0x00,_O,_N,_slash,_O,_F,_F};
code BYTE PipOnOff_Jpn[] = {_P,_I,_P,0x00,_O,_N,_slash,_O,_F,_F};

code BYTE * code PipOnOff[] = {
	PipOnOff_Eng,
	PipOnOff_Kor,
	PipOnOff_Jpn
};

code BYTE PipOnOff_Sizeof[] = {
	sizeof(PipOnOff_Eng),
	sizeof(PipOnOff_Kor),
	sizeof(PipOnOff_Jpn)
};

/////////////////////////////////////////////////////////////////////
//	LARGE
/////////////////////////////////////////////////////////////////////
code BYTE Large_Eng[] = {_L,_A,_R,_G,_E};
code BYTE * code Large[] = {
	Large_Eng
};

code BYTE Large_Sizeof[] = {
	sizeof(Large_Eng)
};

/////////////////////////////////////////////////////////////////////
//	MIDDLE
/////////////////////////////////////////////////////////////////////
code BYTE Middle_Eng[] = {_M,_I,_D,_D,_L,_E};

code BYTE * code Middle[] = {
		Middle_Eng
};

code BYTE Middle_Sizeof[] = {
	sizeof(Middle_Eng)
};

/////////////////////////////////////////////////////////////////////
//	SMALL
/////////////////////////////////////////////////////////////////////
code BYTE Small_Eng[] = {_S,_M,_A,_L,_L};
code BYTE * code Small[] = {
	Small_Eng
};

code BYTE Small_Sizeof[] = {
	sizeof(Small_Eng)
};

/////////////////////////////////////////////////////////////////////
//	PIP CONTROL
/////////////////////////////////////////////////////////////////////
code BYTE PipControl_Eng[] = {_P,_I,_P,0x00,_C,_O,_N,_T,_R,_O,_L};
code BYTE * code PipControl[] = {
	PipControl_Eng
};
code BYTE PipControl_Sizeof[] = {
	sizeof(PipControl_Eng)
};

/*
/////////////////////////////////////////////////////////////////////
//	PIP SWAP
/////////////////////////////////////////////////////////////////////
code BYTE PipSwap_Eng[] = {_P,_I,_P,0x00,_S,_W,_A,_P};
code BYTE * code PipSwap[] = {
	PipSwap_Eng
};
code BYTE PipSwap_Sizeof[] = {
	sizeof(PipSwap_Eng)
};
*/
#if 0
/////////////////////////////////////////////////////////////////////
//	PIP POSITION
/////////////////////////////////////////////////////////////////////
code BYTE PipPosition_Eng[] = {_P,_I,_P,0x00,_P,_O,_S,_I,_T,_I,_O,_N};
code BYTE * code PipPosition[] = {
	PipPosition_Eng
};
code BYTE PipPosition_Sizeof[] = {
	sizeof(PipPosition_Eng)
};
#endif
/////////////////////////////////////////////////////////////////////
//	PIP	BELEND
/////////////////////////////////////////////////////////////////////
code BYTE PipBlend_Eng[] = {_P,_I,_P,0x00,_T,_R,_A,_N,_S,_P,_A,_R,_E,_N,_C,_Y};
code BYTE PipBlend_Kor[] = {_P1,_I1,_P1,_BK,_BAN,_TOU,_MYUNG};  
code BYTE PipBlend_Jpn[] = {J_PIP_TRANS};  

code BYTE * code PipBlend[] = {
	PipBlend_Eng,
	PipBlend_Kor,
	PipBlend_Jpn
};
code BYTE PipBlend_Sizeof[] = {
	sizeof(PipBlend_Eng),
	sizeof(PipBlend_Kor),
	sizeof(PipBlend_Jpn)
};

/*
/////////////////////////////////////////////////////////////////////
//	VOLUME
/////////////////////////////////////////////////////////////////////
code BYTE Volume_Eng[] = {_V,_O,_L,_U,_M,_E,0};
code BYTE Volume_Kor[] = {_V,_O,_L,_U,_M,_E,0};
code BYTE Volume_Jpn[] = {_V,_O,_L,_U,_M,_E,0};

code BYTE * code Volume[] = {
	Volume_Eng,
    	Volume_Kor,
    	Volume_Jpn
};

code BYTE Volume_Sizeof[] = {
	sizeof(Volume_Eng),
	sizeof(Volume_Kor),
	sizeof(Volume_Jpn)
};
*/
/////////////////////////////////////////////////////////////////////
//	MUTE
/////////////////////////////////////////////////////////////////////
code BYTE Mute_Eng[] = {_M,_U,_T,_E,0x00,0x00};
code BYTE Mute_Kor[] = {_M,_U,_T,_E,0x00,0x00};
code BYTE Mute_Jpn[] = {_M,_U,_T,_E,0x00,0x00};

code BYTE * code Mute[] = {
	Mute_Eng,
    	Mute_Kor,
    	Mute_Jpn
};

code BYTE Mute_Sizeof[] = {
	sizeof(Mute_Eng),
	sizeof(Mute_Kor),
	sizeof(Mute_Jpn)
};

/////////////////////////////////////////////////////////////////////
//	kHz
/////////////////////////////////////////////////////////////////////
code BYTE kHz_Eng[] = {_k,_H,_z};
code BYTE * code kHz[] = {
	kHz_Eng
};
code BYTE kHz_Sizeof[] = {
	sizeof(kHz_Eng)
};

/////////////////////////////////////////////////////////////////////
//	POWER SAVER MODE
/////////////////////////////////////////////////////////////////////
code BYTE PowerSaverMode_Eng[] = {_P,_O,_W,_E,_R,0x00,_S,_A,_V,_E,_R,0x00,_M,_O,_D,_E};
code BYTE PowerSaverMode_Kor[] = {_P,_O,_W,_E,_R,0x00,_S,_A,_V,_E,_R,0x00,_M,_O,_D,_E};
code BYTE PowerSaverMode_Jpn[] = {_P,_O,_W,_E,_R,0x00,_S,_A,_V,_E,_R,0x00,_M,_O,_D,_E};

code BYTE * code PowerSaverMode[] = {
	PowerSaverMode_Eng,
    	PowerSaverMode_Kor,
    	PowerSaverMode_Jpn
};

code BYTE PowerSaverMode_Sizeof[] = {
	sizeof(PowerSaverMode_Eng),
	sizeof(PowerSaverMode_Kor),
	sizeof(PowerSaverMode_Jpn)
};

///////////////////////////////////////////////////////
// No Video
///////////////////////////////////////////////////////
code BYTE NoVideo[] = {_N,_O,0x00,_V,_I,_D,_E,_O};


/////////////////////////////////////////////////////////////////////
//	CHECK SIGNAL CABLE
/////////////////////////////////////////////////////////////////////
code BYTE CheckSignalCable_Eng[] = {_C,_H,_E,_C,_K,0x00,_S,_I,_G,_N,_A,_L,0x00,_C,_A,_B,_L,_E};
code BYTE CheckSignalCable_Kor[] = {_C,_H,_E,_C,_K,0x00,_S,_I,_G,_N,_A,_L,0x00,_C,_A,_B,_L,_E};
code BYTE CheckSignalCable_Jpn[] = {_C,_H,_E,_C,_K,0x00,_S,_I,_G,_N,_A,_L,0x00,_C,_A,_B,_L,_E};

code BYTE * code CheckSignalCable[] = {
	CheckSignalCable_Eng,
    	CheckSignalCable_Kor,
	CheckSignalCable_Jpn
};

code BYTE CheckSignalCable_Sizeof[] = {
	sizeof(CheckSignalCable_Eng),
	sizeof(CheckSignalCable_Kor),
	sizeof(CheckSignalCable_Jpn)
};

/////////////////////////////////////////////////////////////////////
//	OUT OF FREQUENCY
/////////////////////////////////////////////////////////////////////
code BYTE OutOfFreq_Eng[] = {_O,_U,_T,0x00,_O,_F,0x00,_F,_R,_E,_Q,_U,_E,_N,_C,_Y};
code BYTE OutOfFreq_Kor[] = {_O,_U,_T,0x00,_O,_F,0x00,_F,_R,_E,_Q,_U,_E,_N,_C,_Y};
code BYTE OutOfFreq_Jpn[] = {_O,_U,_T,0x00,_O,_F,0x00,_F,_R,_E,_Q,_U,_E,_N,_C,_Y};

code BYTE * code OutOfFreq[] = {
	OutOfFreq_Eng,
    	OutOfFreq_Kor,
	OutOfFreq_Jpn
};

code BYTE OutOfFreq_Sizeof[] = {
	sizeof(OutOfFreq_Eng),
	sizeof(OutOfFreq_Kor),
	sizeof(OutOfFreq_Jpn)
};

/////////////////////////////////////////////////////////////////////
//	INPUT SOURCE
/////////////////////////////////////////////////////////////////////
code BYTE InputSource_Eng[] = {_I,_N,_P,_U,_T,0x00,_S,_O,_U,_R,_C,_E};
code BYTE * code InputSource[] = {
	InputSource_Eng
};
code BYTE InputSource_Sizeof[] = {
	sizeof(InputSource_Eng)
};

/////////////////////////////////////////////////////////////////////
//	DIGITAL
/////////////////////////////////////////////////////////////////////
code BYTE Digital_Eng[] = {_D,_I,_G,_I,_T,_A,_L};
code BYTE * code Digital[] = {
	Digital_Eng
};
code BYTE Digital_Sizeof[] = {
	sizeof(Digital_Eng)
};

/*
/////////////////////////////////////////////////////////////////////
//	CH
/////////////////////////////////////////////////////////////////////
code BYTE Ch2_Eng[] = {0,_C,0,_H};
code BYTE * code Chdot2[] = {
	Ch2_Eng
};
code BYTE Chdot2_Sizeof[] = {
	sizeof(Ch_Eng)
};
*/

/////////////////////////////////////////////////////////////////////
//	DEL
/////////////////////////////////////////////////////////////////////
code BYTE Del_Eng[] = {_D,_E,_L};
code BYTE * code Del[] = {
	Del_Eng
};
code BYTE Del_Sizeof[] = {
	sizeof(Del_Eng)
};

/////////////////////////////////////////////////////////////////////
//	Hz
/////////////////////////////////////////////////////////////////////
code BYTE Hz_Eng[] = {_H,_z};
code BYTE * code Hz[] = {
	Hz_Eng
};
code BYTE Hz_Sizeof[] = {
	sizeof(Hz_Eng)
};

/////////////////////////////////////////////////////////////////////
//	Hfreq:
/////////////////////////////////////////////////////////////////////
code BYTE Hfreq_Eng[] = {_H,_f,_r,_e,_q};

code BYTE * code Hfreq[] = {
	Hfreq_Eng
};
code BYTE Hfreq_Sizeof[] = {
	sizeof(Hfreq_Eng)
};

/////////////////////////////////////////////////////////////////////
//	Vfreq:
/////////////////////////////////////////////////////////////////////
code BYTE Vfreq_Eng[] = {_V,_f,_r,_e,_q};

code BYTE * code Vfreq[] = {
	Vfreq_Eng
};
code BYTE Vfreq_Sizeof[] = {
	sizeof(Vfreq_Eng)
};

//***************************************************************************************************************
//#endif
//***************************************************************************************************************


/*-------------------------------------------------------- China Version --------- +jwshin 040728 -------- */
//#################################################
#else	//#################################################
//#################################################
/////////////////////////////////////////////////////////////////////
//	MAIN MENU
/////////////////////////////////////////////////////////////////////
code BYTE Mainmenu_Eng[] = {_P,_C,0x00,_A,_D,_J,_U,_S,_T};
code BYTE Mainmenu_Kor[] = {_BK,_BK,0x08,0x09,0x0a,0x0b};

code BYTE * code Mainmenu[] = {
	Mainmenu_Eng,
    	Mainmenu_Kor
};

code BYTE Mainmenu_Sizeof[] = {
	sizeof(Mainmenu_Eng),
	sizeof(Mainmenu_Kor)
};

/////////////////////////////////////////////////////////
//tv main
/////////////////////////////////////////////////////////
code BYTE TvMainmenu_Eng[] = {_T,_V,0x00,_A,_D,_J,_U,_S,_T};
//code BYTE TvMainmenu_Kor[] = {_T,_V,0x00,_A,_D,_J,_U,_S,_T};
//code BYTE TvMainmenu_Jpn[] = {_T,_V,0x00,_A,_D,_J,_U,_S,_T};

code BYTE * code TvMainmenu[] = {
	TvMainmenu_Eng//,
    	//TvMainmenu_Kor,
    	//TvMainmenu_Jpn
};

code BYTE TvMainmenu_Sizeof[] = {
	sizeof(TvMainmenu_Eng)//,
	//sizeof(TvMainmenu_Kor),
	//sizeof(TvMainmenu_Jpn)
};
/////////////////////////////////////////////////////////
//Av main
/////////////////////////////////////////////////////////
code BYTE AvMainmenu_Eng[] = {_A,_V,0x00,_A,_D,_J,_U,_S,_T};
//code BYTE AvMainmenu_Kor[] = {_A,_V,0x00,_A,_D,_J,_U,_S,_T};
//code BYTE AvMainmenu_Jpn[] = {_A,_V,0x00,_A,_D,_J,_U,_S,_T};

code BYTE * code AvMainmenu[] = {
	AvMainmenu_Eng//,
    	//AvMainmenu_Kor,
    	//AvMainmenu_Jpn
};

code BYTE AvMainmenu_Sizeof[] = {
	sizeof(AvMainmenu_Eng)//,
	//sizeof(AvMainmenu_Kor),
	//sizeof(AvMainmenu_Jpn)
};

/////////////////////////////////////////////////////////////////////
//	Main ICON menu
/////////////////////////////////////////////////////////////////////
code BYTE MainIconMenu_Eng[] = {0,0,_I_lMONITOR,0,_I_rMONITOR,0,_I_lRGB,0,_I_rRGB,0,_I_lOSD,0,_I_rOSD,	\
				0,_I_lPIP,0,_I_rPIP,0,_I_lTOOLS,0,_I_rTOOLS,0,_I_lSOUND,0,_I_rSOUND};

code BYTE * code MainIconMenu[] = {
	MainIconMenu_Eng
};

code BYTE MainIconMenu_Sizeof[] = {
	sizeof(MainIconMenu_Eng)
};

/////////////////////////////////////////////////////////////////////
//	Tv Main ICON menu
/////////////////////////////////////////////////////////////////////
code BYTE TvMainIconMenu_Eng[] = {_I_lMONITOR,_I_rMONITOR,0,0,0,0,_I_lTV2,_I_rTV2,0,0,0,0,_I_lTOOLS,_I_rTOOLS,0,0,0,0,_I_lSOUND,_I_rSOUND};

code BYTE * code TvMainIconMenu[] = {
	TvMainIconMenu_Eng
};
code BYTE TvMainIconMenu_Sizeof[] = {
	sizeof(TvMainIconMenu_Eng)
};

/////////////////////////////////////////////////////////////////////
//	Av Main ICON menu
/////////////////////////////////////////////////////////////////////
code BYTE AvMainIconMenu_Eng[] = {_I_lMONITOR,_I_rMONITOR,0,0,0,0,_I_lTOOLS,_I_rTOOLS,0,0,0,0,_I_lSOUND,_I_rSOUND};

code BYTE * code AvMainIconMenu[] = {
	AvMainIconMenu_Eng
};
code BYTE AvMainIconMenu_Sizeof[] = {
	sizeof(AvMainIconMenu_Eng)
};


/////////////////////////////////////////////////////////////////////
//	Bottom Fixed Information 2(Country)
/////////////////////////////////////////////////////////////////////
#if 0
code BYTE CountryBottomInfo_Eng[] = {_UpTriAngle,_DnTriAngle,_P,_O,_S,_I,_T,_I,_O,_N,0,_LRectAngle,_M,_RRectAngle,	\
				_R,_E,_T,_U,_R,_N};
code BYTE CountryBottomInfo_Kor[] = {_UpTriAngle,_DnTriAngle,_P,_O,_S,_I,_T,_I,_O,_N,0,_LRectAngle,_M,_RRectAngle,	\
				_R,_E,_T,_U,_R,_N};
code BYTE CountryBottomInfo_Jpn[] = {_UpTriAngle,_DnTriAngle,_P,_O,_S,_I,_T,_I,_O,_N,0,_LRectAngle,_M,_RRectAngle,	\
				_R,_E,_T,_U,_R,_N};
#else
code BYTE CountryBottomInfo_Eng[] = {_UpTriAngle,_DnTriAngle,_P,_O,_S,_I,_T,_I,_O,_N,0,_LRectAngle,_M,_RRectAngle,	\
				_R,_E,_T,_U,_R,_N};
#endif
code BYTE * code CountryBottomInfo[] = {
	CountryBottomInfo_Eng//,
	//CountryBottomInfo_Kor,
	//CountryBottomInfo_Jpn
};
code BYTE CountryBottomInfo_Sizeof[] = {
	sizeof(CountryBottomInfo_Eng)//,
	//sizeof(CountryBottomInfo_Kor),
	//sizeof(CountryBottomInfo_Jpn)
};

/////////////////////////////////////////////////////////////////////
//	select
/////////////////////////////////////////////////////////////////////
code BYTE Select_Eng[] = {_LTriAngle,0,0,0,_S,_E,_L,_E,_C,_T,0,0,0,_RTriAngle};
code BYTE Select_Chi[] = {_LTriAngle,_BK,_BK,_BK,CH_SELECT,_BK,_BK,_BK,_BK,_RTriAngle};

code BYTE * code Select[] = {
	Select_Eng,
    Select_Chi
};

code BYTE Select_Sizeof[] = {
	sizeof(Select_Eng),
	sizeof(Select_Chi)
};

/////////////////////////////////////////////////////////////////////
//	channel edit windows char.
/////////////////////////////////////////////////////////////////////
code BYTE EditWindowChar1_eng[] = {_A,_B,_C,_D,_E,_F,_G,_H,_I,_J,_K,_L,_M,_N,_O,_P,_Q,_R,_S,_T};
code BYTE * code EditWindowChar1[] = {
	EditWindowChar1_eng
};
code BYTE EditWindowChar1_Sizeof[] = {
	sizeof(EditWindowChar1_eng)
};

/////////////////////////////////////////////////////////////////////
//	channel edit windows char.
/////////////////////////////////////////////////////////////////////
code BYTE EditWindowChar2_eng[] = {_U,_V,_W,_X,_Y,_Z,_plus,_minus,_dot,0,_0,_1,_2,_3,_4,_5,_6,_7,_8,_9};
code BYTE * code EditWindowChar2[] = {
	EditWindowChar2_eng
};
code BYTE EditWindowChar2_Sizeof[] = {
	sizeof(EditWindowChar2_eng)
};

/////////////////////////////////////////////////////////////////////
//	channel edit char.
/////////////////////////////////////////////////////////////////////
code BYTE ChEditChar[] = {_A,_B,_C,_D,_E,_F,_G,_H,_I,_J,_K,_L,_M,_N,_O,_P,_Q,_R,_S,_T,	\
				_U,_V,_W,_X,_Y,_Z,_plus,_minus,_dot,0,_0,_1,_2,_3,_4,_5,_6,_7,_8,_9};


/////////////////////////////////////////////////////////////////////
//	PROGRAMM EDIT
/////////////////////////////////////////////////////////////////////
code BYTE ProgrammEdit_eng[] = {_P,_R,_O,_G,_R,_A,_M,0,_E,_D,_I,_T};
code BYTE * code ProgrammEdit[] = {
	ProgrammEdit_eng
};
code BYTE ProgrammEdit_Sizeof[] = {
	sizeof(ProgrammEdit_eng)
};


/////////////////////////////////////////////////////////////////////
//	PROGRAMM EDIT CHANNEL/NAME
/////////////////////////////////////////////////////////////////////
code BYTE PRedit_ch_name_eng[] = {_P,_R,0,0,0,_C,_H,_A,_N,_N,_E,_L,0,0,_N,_A,_M,_E,0,0,_S,_K,_I,_P};
code BYTE * code PRedit_ch_name[] = {
	PRedit_ch_name_eng
};
code BYTE PRedit_ch_name_Sizeof[] = {
	sizeof(PRedit_ch_name_eng)
};



// ADJUST
code BYTE Adjust_Eng[] = {_A,_D,_J,_U,_S,_T};                            
code BYTE Adjust_Kor[] = {_JO,_JUNG};  

code BYTE * code Adjust[] = {
	Adjust_Eng,
	Adjust_Kor
};

code BYTE Adjust_Sizeof[] = {
	sizeof(Adjust_Eng),
	sizeof(Adjust_Kor)
};

// RETURN
code BYTE Return_Eng[] = {_R,_E,_T,_U,_R,_N};                            
code BYTE Return_Kor[] = {_SANG,_WI,_MAE,_NEW};


code BYTE * code Return[] = {
	Return_Eng,
	Return_Kor
};

code BYTE Return_Sizeof[] = {
	sizeof(Return_Eng),
	sizeof(Return_Kor)
};

// POSITION
code BYTE Position_Eng[] = {_P,_O,_S,_I,_T,_I,_O,_N};                            
code BYTE Position_Kor[] = {_WI,_CHI};  

code BYTE * code Position[] = {
	Position_Eng,
	Position_Kor
};

code BYTE Position_Sizeof[] = {
	sizeof(Position_Eng),
	sizeof(Position_Kor)
};

/////////////////////////////////////////////////////////////////////
//	BRIGHTNESS
/////////////////////////////////////////////////////////////////////
code BYTE Brightness_Eng[] = {_B,_R,_I,_G,_H,_T,_N,_E,_S,_S};                            
code BYTE Brightness_Chi[] = {CH_BRIGHT};  

code BYTE * code Brightness[] = {
	Brightness_Eng,
	Brightness_Chi
};

code BYTE Brightness_Sizeof[] = {
	sizeof(Brightness_Eng),
	sizeof(Brightness_Chi)
};

/////////////////////////////////////////////////////////////////////
//	CONTRAST
/////////////////////////////////////////////////////////////////////
code BYTE Contrast_Eng[] = {_C,_O,_N,_T,_R,_A,_S,_T};   
code BYTE Contrast_Chi[] = {CH_CONTRAST};  

code BYTE * code Contrast[] = {
	Contrast_Eng,
	Contrast_Chi
};

code BYTE Contrast_Sizeof[] = {
	sizeof(Contrast_Eng),
	sizeof(Contrast_Chi)
};


/////////////////////////////////////////////////////////////////////
//	SHARPNESS
/////////////////////////////////////////////////////////////////////
code BYTE Sharpness_Eng[] = {_S,_H,_A,_R,_P,_N,_E,_S,_S};
code BYTE Sharpness_Chi[] = {_SUN,_MYUNG,_DO};

code BYTE * code Sharpness[] = {
	Sharpness_Eng,
    	Sharpness_Chi
};

code BYTE Sharpness_Sizeof[] = {
	sizeof(Sharpness_Eng),
	sizeof(Sharpness_Chi)
};

/////////////////////////////////////////////////////////////////////
//	CLOCK
/////////////////////////////////////////////////////////////////////
code BYTE Clock_Eng[] = {_C,_L,_O,_C,_K};
code BYTE Clock_Chi[] = {_JU,_PA,_SU};

code BYTE * code Clock[] = {
	Clock_Eng,
	Clock_Chi
};

code BYTE Clock_Sizeof[] = {
	sizeof(Clock_Eng),
	sizeof(Clock_Chi)
};

/////////////////////////////////////////////////////////////////////
//	PHASE
/////////////////////////////////////////////////////////////////////
code BYTE Phase_Eng[] = {_P,_H,_A,_S,_E};
code BYTE Phase_Chi[] = {_WI,_SANG};

code BYTE * code Phase[] = {
	Phase_Eng,
    	Phase_Chi
};

code BYTE Phase_Sizeof[] = {
	sizeof(Phase_Eng),
	sizeof(Phase_Chi)
};


/////////////////////////////////////////////////////////////////////
//	HORIZONTAL
/////////////////////////////////////////////////////////////////////
code BYTE Horizontal_Eng[] = {_H,_O,_R,_I,_Z,_O,_N,_T,_A,_L};
code BYTE Horizontal_Chi[] = {CH_HPOS};

code BYTE * code Horizontal[] = {
	Horizontal_Eng,
    Horizontal_Chi
};

code BYTE Horizontal_Sizeof[] = {
	sizeof(Horizontal_Eng),
	sizeof(Horizontal_Chi)
};

/////////////////////////////////////////////////////////////////////
//	VERTICAL
/////////////////////////////////////////////////////////////////////
code BYTE Vertical_Eng[] = {_V,_E,_R,_T,_I,_C,_A,_L};
code BYTE Vertical_Chi[] = {CH_VPOS};

code BYTE * code Vertical[] = {
	Vertical_Eng,
    Vertical_Chi
};

code BYTE Vertical_Sizeof[] = {
	sizeof(Vertical_Eng),
	sizeof(Vertical_Chi)
};


/////////////////////////////////////////////////////////////////////
//	White balance
/////////////////////////////////////////////////////////////////////
code BYTE WhiteBalance_Eng[] = {_W,_H,_I,_T,_E,0,_B,_A,_L,_A,_N,_C,_E};
code BYTE WhiteBalance_Kor[] = {_BAEK,_SAEK,_JO,_JUNG};

code BYTE * code WhiteBalance[] = {
	WhiteBalance_Eng,
	WhiteBalance_Kor
};

code BYTE WhiteBalance_Sizeof[] = {
	sizeof(WhiteBalance_Eng),
	sizeof(WhiteBalance_Kor)
};

/////////////////////////////////////////////////////////////////////
//	RED GAIN
/////////////////////////////////////////////////////////////////////
code BYTE Rgain_Eng[] = {_R,_E,_D,0,_G,_A,_I,_N};
code BYTE Rgain_Chi[] = {CH_REDGAIN};

code BYTE * code Rgain[] = {
	Rgain_Eng,
    Rgain_Chi
};

code BYTE Rgain_Sizeof[] = {
	sizeof(Rgain_Eng),
	sizeof(Rgain_Chi)
};

/////////////////////////////////////////////////////////////////////
//	GREEN GAIN
/////////////////////////////////////////////////////////////////////
code BYTE Ggain_Eng[] = {_G,_R,_E,_E,_N,0,_G,_A,_I,_N};
code BYTE Ggain_Chi[] = {CH_GREENGAIN};

code BYTE * code Ggain[] = {
	Ggain_Eng,
    	Ggain_Chi
};

code BYTE Ggain_Sizeof[] = {
	sizeof(Ggain_Eng),
	sizeof(Ggain_Chi)
};

/////////////////////////////////////////////////////////////////////
//	BLUE GAIN
/////////////////////////////////////////////////////////////////////
code BYTE Bgain_Eng[] = {_B,_L,_U,_E,0,_G,_A,_I,_N};
code BYTE Bgain_Chi[] = {CH_BLUEGAIN};

code BYTE * code Bgain[] = {
	Bgain_Eng,
    	Bgain_Chi
};

code BYTE Bgain_Sizeof[] = {
	sizeof(Bgain_Eng),
	sizeof(Bgain_Chi)
};

/////////////////////////////////////////////////////////////////////
//	COLOR TEMPERATURE
code BYTE Color_Eng[] = {_C,_O,_L,_O,_R,0,_T,_E,_M,_P,_E,_R,_A,_T,_U,_R,_E};
code BYTE Color_Chi[] = {CH_COLORTEMP};

code BYTE * code Color[] = {
	Color_Eng,
    	Color_Chi
};

code BYTE Color_Sizeof[] = {
	sizeof(Color_Eng),
	sizeof(Color_Chi)
};

/////////////////////////////////////////////////////////////////////
//	COLOR
code BYTE TvColor_Eng[] = {_C,_O,_L,_O,_R};
code BYTE TvColor_Kor[] = {_SAEK,_NONG,_DO};

code BYTE * code TvColor[] = {
	TvColor_Eng,
    	TvColor_Kor
};

code BYTE TvColor_Sizeof[] = {
	sizeof(TvColor_Eng),
	sizeof(TvColor_Kor)
};

/////////////////////////////////////////////////////////////////////
//	LANGUAGE
code BYTE OsdLanguage_Eng[] = {_L,_A,_N,_G,_U,_A,_G,_E};
code BYTE OsdLanguage_Chi[] = {CH_LANG};

code BYTE * code OsdLanguage[] = {
	OsdLanguage_Eng,
    	OsdLanguage_Chi
};
code BYTE OsdLanguage_Sizeof[] = {
	sizeof(OsdLanguage_Eng),
	sizeof(OsdLanguage_Chi)
};

/////////////////////////////////////////////////////////////////////
//	Country  - USA
/////////////////////////////////////////////////////////////////////
code BYTE CountryUSA_Eng[] = {_U,_S,_A};
//code BYTE CountryUSA_Kor[] = {_U,_S,_A};
//code BYTE CountryUSA_Jpn[] = {_U,_S,_A};

code BYTE * code CountryUSA[] = {
	CountryUSA_Eng//,
	//CountryUSA_Kor,
	//CountryUSA_Jpn
};

code BYTE CountryUSA_Sizeof[] = {
	sizeof(CountryUSA_Eng)//,
	//sizeof(CountryUSA_Kor),
	//sizeof(CountryUSA_Jpn)
};


/////////////////////////////////////////////////////////////////////
//	language - English
/////////////////////////////////////////////////////////////////////
code BYTE LangEng_Eng[] = {_E,_N,_G,_L,_I,_S,_H};
code BYTE * code LangEng[] = {
	LangEng_Eng
};

code BYTE LangEng_Sizeof[] = {
	sizeof(LangEng_Eng)
};
/////////////////////////////////////////////////////////////////////

//	Language - FRANCE
/////////////////////////////////////////////////////////////////////
code BYTE LangFrance_eng[] = {_F,_R,_A,_N,_C,_E};
code BYTE * code LangFrance[] = {
	LangFrance_eng
};
code BYTE LangFrance_Sizeof[] = {
	sizeof(LangFrance_eng)
};

//	Language - German
/////////////////////////////////////////////////////////////////////
code BYTE LangGerman_eng[] = {_G,_E,_R,_M,_A,_N};
code BYTE * code LangGerman[] = {
	LangGerman_eng
};
code BYTE LangGerman_Sizeof[] = {
	sizeof(LangGerman_eng)
};

//	Language - Italia
/////////////////////////////////////////////////////////////////////
code BYTE LangItalia_eng[] = {_I,_T,_A,_L,_I,_A};
code BYTE * code LangItalia[] = {
	LangItalia_eng
};
code BYTE LangItalia_Sizeof[] = {
	sizeof(LangItalia_eng)
};

//	Language - Netherlands
/////////////////////////////////////////////////////////////////////
code BYTE LangNetherlands_eng[] = {_N,_E,_T,_H,_E,_R,_L,_A,_N,_D,_S};
code BYTE * code LangNetherlands[] = {
	LangNetherlands_eng
};
code BYTE LangNetherlands_Sizeof[] = {
	sizeof(LangNetherlands_eng)
};

//	Language - Russia
/////////////////////////////////////////////////////////////////////
code BYTE LangRussia_eng[] = {_R,_U,_S,_S,_I,_A};
code BYTE * code LangRussia[] = {
	LangRussia_eng
};
code BYTE LangRussia_Sizeof[] = {
	sizeof(LangRussia_eng)
};

//	Language - China
/////////////////////////////////////////////////////////////////////
code BYTE LangChina_eng[] = {_C,_H,_I,_N,_A};
code BYTE LangChina_Chi[] = {CH_CHINA};
code BYTE * code LangChina[] = {
	LangChina_eng,
	LangChina_Chi
};
code BYTE LangChina_Sizeof[] = {
	sizeof(LangChina_eng),
	sizeof(LangChina_Chi)
};

//	Language - China
/////////////////////////////////////////////////////////////////////
code BYTE CtyChina_eng[] = {_C,_H,_I,_N,_A};
code BYTE CtyChina_Chi[] = {CH_CHINA_CTY};
code BYTE * code CtyChina[] = {
	CtyChina_eng,
	CtyChina_Chi
};
code BYTE CtyChina_Sizeof[] = {
	sizeof(CtyChina_eng),
	sizeof(CtyChina_Chi)
};


///////////////////////////////////////////
code BYTE PalTVtype_Eng[] = {_P,_A,_L};
code BYTE PalTVtype_Chi[] = {0x46,0x47,0x48,0x2f};		//+jwshin 040801

code BYTE * code PalTVtype[] = {
	PalTVtype_Eng,
	PalTVtype_Chi
};

code BYTE PalTVtype_Sizeof[] = {
	sizeof(PalTVtype_Eng),
	sizeof(PalTVtype_Chi)
};

#if 0
code BYTE PalDK[] = {_P,_A,_L,0,_D,_slash,_K};
code BYTE PalBG[] = {_P,_A,_L,0,_B,_slash,_G};
code BYTE PalI[] = {_P,_A,_L,0,_I};
#endif

/////////////////////////////////////////////////////////////////////
//	OSD H-POSITION
/////////////////////////////////////////////////////////////////////
code BYTE OsdHPosition_Eng[] = {_O,_S,_D,0,_H,_minus,_P,_O,_S,_I,_T,_I,_O,_N};
code BYTE OsdHPosition_Kor[] = {_O1,_S1,_D1,_BK,_SU,_PYUNG,_WI,_CHI};

code BYTE * code OsdHPosition[] = {
	OsdHPosition_Eng,
	OsdHPosition_Kor
};

code BYTE OsdHPosition_Sizeof[] = {
	sizeof(OsdHPosition_Eng),
	sizeof(OsdHPosition_Kor)
};

/////////////////////////////////////////////////////////////////////
//	V-POSITION
/////////////////////////////////////////////////////////////////////
code BYTE OsdVPosition_Eng[] = {_O,_S,_D,0,_V,_minus,_P,_O,_S,_I,_T,_I,_O,_N};
code BYTE OsdVPosition_Kor[] = {_O1,_S1,_D1,_BK,_SU,_JIK,_WI,_CHI};

code BYTE * code OsdVPosition[] = {
	OsdVPosition_Eng,
	OsdVPosition_Kor
};

code BYTE OsdVPosition_Sizeof[] = {
	sizeof(OsdVPosition_Eng),
	sizeof(OsdVPosition_Kor)
};

/////////////////////////////////////////////////////////////////////
//	OSD TIME
/////////////////////////////////////////////////////////////////////
code BYTE OsdTime_Eng[] = {_O,_S,_D,0x00,_T,_I,_M,_E};
code BYTE OsdTime_Kor[] = {_O1,_S1,_D1,_BK,_PYO,_SI,_SI,_GAN};

code BYTE * code OsdTime[] = {
	OsdTime_Eng,
    	OsdTime_Kor
};

code BYTE OsdTime_Sizeof[] = {
	sizeof(OsdTime_Eng),
	sizeof(OsdTime_Kor)
};

/////////////////////////////////////////////////////////////////////
//	OSD TRANSPARENCY
/////////////////////////////////////////////////////////////////////
code BYTE OsdTransparency_Eng[] = {_O,_S,_D,0,_T,_R,_A,_N,_S,_P,_A,_R,_E,_N,_C,_Y};
code BYTE OsdTransparency_Kor[] = {_O1,_S1,_D1,_BK,_BAN,_TOU,_MYUNG};                                     

code BYTE * code OsdTransparency[] = {
	OsdTransparency_Eng,
	OsdTransparency_Kor
};

code BYTE OsdTransparency_Sizeof[] = {
	sizeof(OsdTransparency_Eng),
	sizeof(OsdTransparency_Kor)
};

/////////////////////////////////////////////////////////////////////
//	PIP ENABLE
/////////////////////////////////////////////////////////////////////
code BYTE PipEnable_Eng[] = {_P,_I,_P,0,_E,_N,_A,_B,_L,_E};
code BYTE PipEnable_Kor[] = {_P1,_I1,_P1,_BK,_DONG,_JAK};

code BYTE * code PipEnable[] = {
	PipEnable_Eng,
	PipEnable_Kor
};

code BYTE PipEnable_Sizeof[] = {
	sizeof(PipEnable_Eng),
	sizeof(PipEnable_Kor)
};

/////////////////////////////////////////////////////////////////////
//	PIP SOURCE
/////////////////////////////////////////////////////////////////////
code BYTE PipSource_Eng[] = {_P,_I,_P,0,_S,_O,_U,_R,_C,_E};
code BYTE PipSource_Kor[] = {_P1,_I1,_P1,_BK,_EIP,_YERK};

code BYTE * code PipSource[] = {
	PipSource_Eng,
	PipSource_Kor
};

code BYTE PipSource_Sizeof[] = {
	sizeof(PipSource_Eng),
	sizeof(PipSource_Kor)
};

/////////////////////////////////////////////////////////////////////
//	PIP SIZE
/////////////////////////////////////////////////////////////////////
code BYTE PipSize_Eng[] = {_P,_I,_P,0,_S,_I,_Z,_E};
code BYTE PipSize_Kor[] = {_P1,_I1,_P1,_BK,_KEE,_GI};

code BYTE * code PipSize[] = {
	PipSize_Eng,
	PipSize_Kor
};

code BYTE PipSize_Sizeof[] = {
	sizeof(PipSize_Eng),
	sizeof(PipSize_Kor)
};

/////////////////////////////////////////////////////////////////////
//	Pip H-POSITION
/////////////////////////////////////////////////////////////////////
code BYTE PipHPosition_Eng[] = {_P,_I,_P,0,_H,_minus,_P,_O,_S,_I,_T,_I,_O,_N};
code BYTE PipHPosition_Kor[] = {_P1,_I1,_P1,_BK,_SU,_PYUNG,_WI,_CHI};


code BYTE * code PipHPosition[] = {
	PipHPosition_Eng,
	PipHPosition_Kor
};

code BYTE PipHPosition_Sizeof[] = {
	sizeof(PipHPosition_Eng),
	sizeof(PipHPosition_Kor)
};

/////////////////////////////////////////////////////////////////////
//	V-POSITION
/////////////////////////////////////////////////////////////////////
code BYTE PipVPosition_Eng[] = {_P,_I,_P,0,_V,_minus,_P,_O,_S,_I,_T,_I,_O,_N};
code BYTE PipVPosition_Kor[] = {_P1,_I1,_P1,_BK,_SU,_JIK,_WI,_CHI};


code BYTE * code PipVPosition[] = {
	PipVPosition_Eng,
	PipVPosition_Kor
};

code BYTE PipVPosition_Sizeof[] = {
	sizeof(PipVPosition_Eng),
	sizeof(PipVPosition_Kor)
};

/////////////////////////////////////////////////////////////////////
//	aspect
/////////////////////////////////////////////////////////////////////
code BYTE Aspect_Eng[] = {_A,_S,_P,_E,_C,_T};
code BYTE Aspect_Chi[] = {0x30,_BK,0x31};

code BYTE * code Aspect[] = {
	Aspect_Eng,
	Aspect_Chi
};

code BYTE Aspect_Sizeof[] = {
	sizeof(Aspect_Eng),
	sizeof(Aspect_Chi)
};


/////////////////////////////////////////////////////////////////////
//	pip aspect
/////////////////////////////////////////////////////////////////////
code BYTE PipAspect_Eng[] = {_P,_I,_P,0,_A,_S,_P,_E,_C,_T};
code BYTE PipAspect_Kor[] = {_P1,_I1,_P1,_BK,_HWA,_MYUN,_BEE,_YULL};


code BYTE * code PipAspect[] = {
	PipAspect_Eng,
	PipAspect_Kor
};

code BYTE PipAspect_Sizeof[] = {
	sizeof(PipAspect_Eng),
	sizeof(PipAspect_Kor)
};

/////////////////////////////////////////////////////////////////////
//	aspect (4:3)
/////////////////////////////////////////////////////////////////////
code BYTE Aspect4_3_Eng[] = {_4,_Colon,_3};
code BYTE Aspect4_3_Kor[] = {_4,_Colon,_3};

code BYTE * code Aspect4_3[] = {
	Aspect4_3_Eng,
	Aspect4_3_Kor
};

code BYTE Aspect4_3_Sizeof[] = {
	sizeof(Aspect4_3_Eng),
	sizeof(Aspect4_3_Kor)
};

/////////////////////////////////////////////////////////////////////
//	aspect (16:9)
/////////////////////////////////////////////////////////////////////
code BYTE Aspect16_9_Eng[] = {_1,_6,_Colon,_9};
code BYTE Aspect16_9_Kor[] = {_1,_6,_Colon,_9};

code BYTE * code Aspect16_9[] = {
	Aspect16_9_Eng,
	Aspect16_9_Kor
};

code BYTE Aspect16_9_Sizeof[] = {
	sizeof(Aspect16_9_Eng),
	sizeof(Aspect16_9_Kor)
};

/////////////////////////////////////////////////////////////////////
//	aspect (full)
/////////////////////////////////////////////////////////////////////
code BYTE Full_Eng[] = {_F,_U,_L,_L};
code BYTE Full_Chi[] = {CH_FULL};

code BYTE * code Full[] = {
	Full_Eng,
	Full_Chi
};

code BYTE Full_Sizeof[] = {
	sizeof(Full_Eng),
	sizeof(Full_Chi)
};

/////////////////////////////////////////////////////////////////////
//	AUTO ADJUST
/////////////////////////////////////////////////////////////////////
code BYTE AutoAdjust_Eng[] = {_A,_U,_T,_O,0x00,_A,_D,_J,_U,_S,_T,_M,_E,_N,_T};
code BYTE AutoAdjust_Kor[] = {_A,_U,_T,_O,0x00,_A,_D,_J,_U,_S,_T,_M,_E,_N,_T};

code BYTE * code AutoAdjust[] = {
	AutoAdjust_Eng,
    	AutoAdjust_Kor
};

code BYTE AutoAdjust_Sizeof[] = {
	sizeof(AutoAdjust_Eng),
	sizeof(AutoAdjust_Kor)
};

//////////////////////////////////////////////////////////////////////
code BYTE OSDHotkeyMsg1[]={
	_Y,_E,_S,_Colon,_,_P,_R,_E,_S,_S,_,_A,_U,_T,_O,_,_B,_U,_T,_T,_O,_N,_,_A,_G,_A,_I,_N
};

//////////////////////////////////////////////////////////////////////
code BYTE OSDHotkeyMsg2[]={
	_N,_O,_,_Colon,_,_P,_R,_E,_S,_S,_,_O,_T,_H,_E,_R,_,_K,_E,_Y
};     

/////////////////////////////////////////////////////////////////////
//	FACTORY DEFAULT
/////////////////////////////////////////////////////////////////////
code BYTE Factory_Eng[] = {_F,_A,_C,_T,_O,_R,_Y,0,_D,_E,_F,_A,_U,_L,_T};
code BYTE Factory_Chi[] = {CH_FACTORY};

code BYTE * code Factory[] = {
	Factory_Eng,
	Factory_Chi
};
code BYTE Factory_Sizeof[] = {
	sizeof(Factory_Eng),
	sizeof(Factory_Chi)
};

/////////////////////////////////////////////////////////////////////
//	DOSMODE		//2003-08-26
/////////////////////////////////////////////////////////////////////
code BYTE Dosmode_Eng[] = {_D,_O,_S,0,_M,_O,_D,_E};
code BYTE Dosmode_Kor[] = {0x2c,0x2d,0x2e,0x2f};

code BYTE * code Dosmode[] = {
	Dosmode_Eng,
	Dosmode_Kor
};
code BYTE Dosmode_Sizeof[] = {
	sizeof(Dosmode_Eng),
	sizeof(Dosmode_Kor)
};

/////////////////////////////////////////////////////////////////////
//	CHANNEL EDIT CHANNEL/NAME
/////////////////////////////////////////////////////////////////////
code BYTE CHedit_ch_add_eng[] = {_C,_H,_A,_N,_N,_E,_L,0,0,0,0,0,0,0,0,0,_A,_D,_D};
code BYTE * code CHedit_ch_add[] = {
	CHedit_ch_add_eng
};
code BYTE CHedit_ch_add_Sizeof[] = {
	sizeof(CHedit_ch_add_eng)
};

#if 1		// CTWarm_Kor는 Chinese font 임.... 주의 ...
/////////////////////////////////////////////////////////////////////
//	Color temperature
/////////////////////////////////////////////////////////////////////
code BYTE CTwarm_Eng[] = {_W,_A,_R,_M};
code BYTE CTwarm_Kor[] = {0x10,_BK,_BK,_BK,0x11};
code BYTE CTwarm_Jpn[] = {_W,_A,_R,_M};

code BYTE * code CTwarm[] = {
	CTwarm_Eng,
	CTwarm_Kor,
	CTwarm_Jpn
};
code BYTE CTwarm_Sizeof[] = {
	sizeof(CTwarm_Eng),
	sizeof(CTwarm_Kor),
	sizeof(CTwarm_Jpn)
};

/////////////////////////////////////////////////////////////////////
code BYTE CTstandard_Eng[] = {_S,_T,_A,_N,_D,_A,_R,_D};
code BYTE CTstandard_Kor[] = {0xc,_BK,_BK,_BK,0xd};
code BYTE CTstandard_Jpn[] = {_S,_T,_A,_N,_D,_A,_R,_D};

code BYTE * code CTstandard[] = {
	CTstandard_Eng,
	CTstandard_Kor,
	CTstandard_Jpn
};

code BYTE CTstandard_Sizeof[] = {
	sizeof(CTstandard_Eng),
	sizeof(CTstandard_Kor),
	sizeof(CTstandard_Jpn),
};

/////////////////////////////////////////////////////////////////////
code BYTE CTcool_Eng[] = {_C,_O,_O,_L};
code BYTE CTcool_Kor[] = {0x12,_BK,_BK,_BK,0x13};
code BYTE CTcool_Jpn[] = {_C,_O,_O,_L};

code BYTE * code CTcool[] = {
	CTcool_Eng,
	CTcool_Kor,
	CTcool_Jpn
};

code BYTE CTcool_Sizeof[] = {
	sizeof(CTcool_Eng),
	sizeof(CTcool_Kor),
	sizeof(CTcool_Jpn)
};
#else
/////////////////////////////////////////////////////////////////////
//	Color temperature
/////////////////////////////////////////////////////////////////////
code BYTE CTwarm_Eng[] = {_W,_A,_R,_M};

code BYTE * code CTwarm[] = {
	CTwarm_Eng
};
code BYTE CTwarm_Sizeof[] = {
	sizeof(CTwarm_Eng)
};

/////////////////////////////////////////////////////////////////////
code BYTE CTstandard_Eng[] = {_S,_T,_A,_N,_D,_A,_R,_D};
code BYTE * code CTstandard[] = {
	CTstandard_Eng
};

code BYTE CTstandard_Sizeof[] = {
	sizeof(CTstandard_Eng),
};

/////////////////////////////////////////////////////////////////////
code BYTE CTcool_Eng[] = {_C,_O,_O,_L};
code BYTE * code CTcool[] = {
	CTcool_Eng
};

code BYTE CTcool_Sizeof[] = {
	sizeof(CTcool_Eng)
};
#endif

/////////////////////////////////////////////////////////////////////
//	PC
/////////////////////////////////////////////////////////////////////
code BYTE Pc_Eng[] = {_P,0,_C};
code BYTE Pc_Chi[] = {0x08,_BK,0x09};		// +jwshin 040801
code BYTE * code Pc[] = {
	Pc_Eng,
	Pc_Chi
};

code BYTE Pc_Sizeof[] = {
	sizeof(Pc_Eng),
	sizeof(Pc_Chi)
};



/////////////////////////////////////////////////////////////////////
//	tv
/////////////////////////////////////////////////////////////////////
code BYTE Tv[] = {_T,0,_V};

/////////////////////////////////////////////////////////////////////
//	AV1
/////////////////////////////////////////////////////////////////////
code BYTE Av1[] = {_A,0,_V,0,_1};

/////////////////////////////////////////////////////////////////////
//	AV2
/////////////////////////////////////////////////////////////////////
code BYTE Av2[] = {_A,0,_V,0,_2};

/////////////////////////////////////////////////////////////////////
//	ANALOG
/////////////////////////////////////////////////////////////////////
code BYTE Analog_Eng[] = {_A,_N,_A,_L,_O,_G};
//code BYTE Analog_Kor[] = {_A,_N,_A,_L,_O,_G};
//code BYTE Analog_Jpn[] = {_A,_N,_A,_L,_O,_G};

code BYTE * code Analog[] = 
{
	Analog_Eng//,
    	//Analog_Kor,
    	//Analog_Jpn
};

code BYTE Analog_Sizeof[] = 
{
	sizeof(Analog_Eng)//,
	//sizeof(Analog_Kor),
	//sizeof(Analog_Jpn)
};

/////////////////////////////////////////////////////////////////////
//	TUNER
/////////////////////////////////////////////////////////////////////
code BYTE Tuner_Eng[] = {_T,_U,_N,_E,_R};
code BYTE Tuner_Kor[] = {0x1b,_BK,0x17,_BK,0x1c};			// +jwshin 040801 modified...
//code BYTE Tuner_Jpn[] = {_T,_U,_N,_E,_R};

code BYTE * code Tuner[] = {
	Tuner_Eng,
	Tuner_Kor,
	//Tuner_Jpn
};

code BYTE Tuner_Sizeof[] = {
	sizeof(Tuner_Eng),
	sizeof(Tuner_Kor),
	//sizeof(Tuner_Jpn)
};

/////////////////////////////////////////////////////////////////////
//	COMPOSITE
/////////////////////////////////////////////////////////////////////
code BYTE Composite_Eng[] = {_C,_O,_M,_P,_O,_S,_I,_T,_E};
code BYTE Composite_Kor[] = {0x17,_BK,0x18,_BK,0x19,_BK,0x1a};		// +jwshin 040801 modified...
//code BYTE Composite_Jpn[] = {_C,_O,_M,_P,_O,_S,_I,_T,_E};

code BYTE * code Composite[] = {
	Composite_Eng,
	Composite_Kor,
	//Composite_Jpn
};
code BYTE Composite_Sizeof[] = {
	sizeof(Composite_Eng),
	sizeof(Composite_Kor),
	//sizeof(Composite_Jpn)
};

/////////////////////////////////////////////////////////////////////
//	S-VIDEO의 S Part
/////////////////////////////////////////////////////////////////////
code BYTE SOnly_Eng[] = {_S};

code BYTE * code SOnly[] = {
	SOnly_Eng
};

code BYTE SOnly_Sizeof[] = {
	sizeof(SOnly_Eng)
};

/////////////////////////////////////////////////////////////////////
//	S-VIDEO
/////////////////////////////////////////////////////////////////////
code BYTE Svideo_Eng[] = {_S,_minus,_V,_I,_D,_E,_O};
code BYTE Svideo_Kor[] = {0x1d,_BK,0x1e};			// +jwshin 040801 modified...
//code BYTE Svideo_Jpn[] = {_S,_minus,_V,_I,_D,_E,_O};

code BYTE * code Svideo[] = {
	Svideo_Eng,
	Svideo_Kor
	//Svideo_Jpn
};

code BYTE Svideo_Sizeof[] = {
	sizeof(Svideo_Eng),
	sizeof(Svideo_Kor)
	//sizeof(Svideo_Jpn)
};

/*
/////////////////////////////////////////////////////////////////////
//	PIP
/////////////////////////////////////////////////////////////////////
code BYTE Pip_Eng[] = {0x00,_2iPipL,_2iPipR,0x00,_P,_I,_P};
code BYTE Pip_Kor[] = {0x00,_2iPipL,_2iPipR,0x00,_P,_I,_P};
code BYTE Pip_Jpn[] = {0x00,_2iPipL,_2iPipR,0x00,_P,_I,_P};

code BYTE * code Pip[] = {
	Pip_Eng,
	Pip_Kor,
	Pip_Jpn
};

code BYTE Pip_Sizeof[] = {
	sizeof(Pip_Eng),
	sizeof(Pip_Kor),
	sizeof(Pip_Jpn)
};
*/

/////////////////////////////////////////////////////////////////////
//	PIP
/////////////////////////////////////////////////////////////////////
code BYTE PipSub_Eng[] = {_P,_I,_P};
//code BYTE PipSub_Kor[] = {_P,_I,_P};
//code BYTE PipSub_Jpn[] = {_P,_I,_P};

code BYTE * code PipSub[] = {
	PipSub_Eng//,
	//PipSub_Kor,
	//PipSub_Jpn,
};

code BYTE PipSub_Sizeof[] = {
	sizeof(PipSub_Eng)//,
	//sizeof(PipSub_Kor),
	//sizeof(PipSub_Jpn)
};

#if 1
/////////////////////////////////////////////////////////////////////
//	Left
/////////////////////////////////////////////////////////////////////
code BYTE Left_Eng[] = {_L,_E,_F,_T};
code BYTE Left_Chi[] = {CH_LEFT};
code BYTE * code Left[] = {
	Left_Eng,
	Left_Chi
};
code BYTE Left_Sizeof[] = {
	sizeof(Left_Eng),
	sizeof(Left_Chi)
};
/////////////////////////////////////////////////////////////////////
//	Right
/////////////////////////////////////////////////////////////////////
code BYTE Right_Eng[] = {_R,_I,_G,_H,_T};
code BYTE Right_Chi[] = {CH_RIGHT};
code BYTE * code Right[] = {
	Right_Eng,
	Right_Chi
};
code BYTE Right_Sizeof[] = {
	sizeof(Right_Eng),
	sizeof(Right_Chi)
};
/////////////////////////////////////////////////////////////////////
//	Center
/////////////////////////////////////////////////////////////////////
code BYTE Center_Eng[] = {_C,_E,_N,_T,_E,_R};
code BYTE Center_Chi[] = {CH_MIDDLE};
code BYTE * code Center[] = {
	Center_Eng,
	Center_Chi
};
code BYTE Center_Sizeof[] = {
	sizeof(Center_Eng),
	sizeof(Center_Chi)
};
#else
/////////////////////////////////////////////////////////////////////
//	Left
/////////////////////////////////////////////////////////////////////
code BYTE Left[] = {_L,_E,_F,_T};
/////////////////////////////////////////////////////////////////////
//	Right
/////////////////////////////////////////////////////////////////////
code BYTE Right[] = {_R,_I,_G,_H,_T};
/////////////////////////////////////////////////////////////////////
//	Center
/////////////////////////////////////////////////////////////////////
code BYTE Center[] = {_C,_E,_N,_T,_E,_R};
#endif


/////////////////////////////////////////////////////////////////////
//	Top
/////////////////////////////////////////////////////////////////////
code BYTE Top_Eng[] = {_T,_O,_P};
code BYTE Top_Chi[] = {CH_TOP};
code BYTE * code Top[] = {
	Top_Eng,
	Top_Chi
};
code BYTE Top_Sizeof[] = {
	sizeof(Top_Eng),
	sizeof(Top_Chi)
};
/////////////////////////////////////////////////////////////////////
//	Bottom
/////////////////////////////////////////////////////////////////////
code BYTE Bottom_Eng[] = {_B,_O,_T,_T,_O,_M};
code BYTE Bottom_Chi[] = {CH_BOTTOM};
code BYTE * code Bottom[] = {
	Bottom_Eng,
	Bottom_Chi
};
code BYTE Bottom_Sizeof[] = {
	sizeof(Bottom_Eng),
	sizeof(Bottom_Chi)
};

/////////////////////////////////////////////////////////////////////
//	SEC
/////////////////////////////////////////////////////////////////////
code BYTE Sec_Eng[] = {_S,_E,_C};
code BYTE Sec_Chi[] = {CH_SEC};

code BYTE * code Sec[] = {
		Sec_Eng,
    	Sec_Chi
};

code BYTE Sec_Sizeof[] = {
	sizeof(Sec_Eng),
	sizeof(Sec_Chi)
};

/////////////////////////////////////////////////////////////////////
//	MINUTE
/////////////////////////////////////////////////////////////////////
code BYTE Minute_Eng[] = {_M,_I,_N};
code BYTE Minute_Chi[] = {CH_MINUTE};

code BYTE * code Minute[] = {
	Minute_Eng,
	Minute_Chi
};

code BYTE Minute_Sizeof[] = {
	sizeof(Minute_Eng),
	sizeof(Minute_Chi)
};

/////////////////////////////////////////////////////////////////////
//	CABLE
/////////////////////////////////////////////////////////////////////
code BYTE Cable_Eng[] = {_C,_A,_B,_L,_E};
code BYTE Cable_Kor[] = {_C,_A,_B,_L,_E};

code BYTE * code Cable[] = {
	Cable_Eng,
	Cable_Kor
};

code BYTE Cable_Sizeof[] = {
	sizeof(Cable_Eng),
	sizeof(Cable_Kor)
};

#if 0		
/////////////////////////////////////////////////////////////////////
//	CHANNEL
/////////////////////////////////////////////////////////////////////
code BYTE Channel_Eng[] = {0x00,_2iChannelL,_2iChannelR,0x00,_C,_H,_A,_N,_N,_E,_L};
code BYTE Channel_Kor[] = {0x00,_2iChannelL,_2iChannelR,0x00,_C,_H,_A,_N,_N,_E,_L};
code BYTE Channel_Jpn[] = {0x00,_2iChannelL,_2iChannelR,0x00,_C,_H,_A,_N,_N,_E,_L};

code BYTE * code Channel[] = {
	Channel_Eng,
    	Channel_Kor,
    	Channel_Jpn
};

code BYTE Channel_Sizeof[] = {
	sizeof(Channel_Eng),
	sizeof(Channel_Kor),
	sizeof(Channel_Jpn)
};
#endif

/////////////////////////////////////////////////////////////////////
//	COLORSUB
/////////////////////////////////////////////////////////////////////
code BYTE ColorSub_Eng[] = {_C,_O,_L,_O,_R};
code BYTE ColorSub_Kor[] = {_SAEK,_NONG,_DO};

code BYTE * code ColorSub[] = {
	ColorSub_Eng,
    	ColorSub_Kor
};

code BYTE ColorSub_Sizeof[] = {
	sizeof(ColorSub_Eng),
	sizeof(ColorSub_Kor)
};

/////////////////////////////////////////////////////////////////////
//	TINT
/////////////////////////////////////////////////////////////////////
code BYTE Tint_Eng[] = {_T,_I,_N,_T};
code BYTE Tint_Kor[] = {_SAEK,_SANG};

code BYTE * code Tint[] = {
	Tint_Eng,
    	Tint_Kor
};

code BYTE Tint_Sizeof[] = {
	sizeof(Tint_Eng),
	sizeof(Tint_Kor)
};

/////////////////////////////////////////////////////////////////////
//	COUNTRY
/////////////////////////////////////////////////////////////////////
code BYTE Country_Eng[] = {_C,_O,_U,_N,_T,_R,_Y};
code BYTE Country_Kor[] = {_GOOK,_GA,_SEOL,_JUNG};


code BYTE * code Country[] = {
	Country_Eng,
	Country_Kor
};

code BYTE Country_Sizeof[] = {
	sizeof(Country_Eng),
	sizeof(Country_Kor)
};

/////////////////////////////////////////////////////////////////////
//	auto setup
/////////////////////////////////////////////////////////////////////
code BYTE AutoSetup_Eng[] = {_A,_U,_T,_O,0,_S,_E,_T,_U,_P};
code BYTE AutoSetup_Kor[] = {_CHAE,_NULL,_JA,_DONG,_SEOL,_JUNG};


code BYTE * code AutoSetup[] = {
	AutoSetup_Eng,
	AutoSetup_Kor
};

code BYTE AutoSetup_Sizeof[] = {
	sizeof(AutoSetup_Eng),
	sizeof(AutoSetup_Kor)
};

/////////////////////////////////////////////////////////////////////
//	CHANNEL EDIT
/////////////////////////////////////////////////////////////////////
code BYTE ChannelEdit_Eng[] = {_C,_H,_A,_N,_N,_E,_L,0,_E,_D,_I,_T};
code BYTE ChannelEdit_Kor[] = {_CHAE,_NULL,_PYEON,_JIP};

code BYTE * code ChannelEdit[] = {
	ChannelEdit_Eng,
	ChannelEdit_Kor
};

code BYTE ChannelEdit_Sizeof[] = {
	sizeof(ChannelEdit_Eng),
	sizeof(ChannelEdit_Kor)
};

#ifdef	Ccd_Vchip
/////////////////////////////////////////////////////////////////////
//	CCD
/////////////////////////////////////////////////////////////////////
code BYTE Ccd[] = {_C,_C,_D};

code BYTE ClosedCaption[] = {_C,_l,_o,_s,_e,_d,0,_C,_a,_p,_t,_i,_o,_n};
code BYTE Caption[] = {_C,_A,_P,_T,_I,_O,_N};
code BYTE Mode[] = {_M,_O,_D,_E};
code BYTE Channel_char[] = {_C,_H,_A,_N,_N,_E,_L};
code BYTE Field[] = {_F,_I,_E,_L,_D};
code BYTE Display[] = {_D,_I,_S,_P,_L,_A,_Y};

/////////////////////////////////////////////////////////////////////
//	V-chip
/////////////////////////////////////////////////////////////////////
code BYTE Vchip[] = {_V,_minus,_c,_h,_i,_p};

//
code BYTE CcdEnterPin[] = {_E,_n,_t,_e,_r,0,_P,_i,_n,0,_Colon,0,_UnderBar,_UnderBar,_UnderBar,_UnderBar};
//code BYTE MotionPicture[] = {_M,_o,_t,_i,_o,_n,0,_P,_i,_c,_t,_u,_r,_e};
code BYTE MotionPicture[] = {_M,_O,_T,_I,_O,_N,0,_P,_I,_C,_T,_U,_R,_E};
//code BYTE ParentalGuide[] = {_T,_V,0,_P,_a,_r,_e,_n,_t,_a,_l,0,_G,_u,_i,_d,_e};
code BYTE ParentalGuide[] = {_T,_V,0,_P,_A,_R,_E,_N,_T,_A,_L,0,_G,_U,_I,_D,_E};
//code BYTE ChangeCode[] = {_C,_h,_a,_n,_g,_e,0,_C,_o,_d,_e};
code BYTE ChangeCode[] = {_C,_H,_A,_N,_G,_E,0,_C,_O,_D,_E};
//code BYTE RatingChange[] = {_RTriAngle,0,_R,_a,_t,_i,_n,_g,0,_C,_h,_a,_n,_g,_e};
code BYTE RatingChange[] = {_RTriAngle,0,_R,_A,_T,_I,_N,_G,0,_C,_H,_A,_N,_G,_E};

//code BYTE NoRating[] = {_N,_O,0,_R,_A,_T,_I,_N,_G,0,_V,_I,_E,_W};
code BYTE NoRating[] = {_N,_o,0,_R,_a,_t,_i,_n,_g,0,_V,_i,_e,_w};
code BYTE vchipGP13[] = {_P,_G,_minus,_1,_3};
code BYTE vchipNC17[] = {_N,_C,_minus,_1,_7};
#if 1
code BYTE tvY[] = {_T,_V,_minus,_Y,0,0,_UnderBar};
code BYTE tvY7[] = {_T,_V,_minus,_Y,_7,0,_UnderBar};
code BYTE tvG[] = {_T,_V,_minus,_G,0,0,_UnderBar};
code BYTE tvPG[] = {_T,_V,_minus,_P,_G,0,_UnderBar};
code BYTE tv14[] = {_T,_V,_minus,_1,_4,0,_UnderBar};
code BYTE tvMA[] = {_T,_V,_minus,_M,_A,0,_UnderBar};
code BYTE tvFV[] = {_Lbar,_F,_Rbar,_V,_UnderBar};
code BYTE tvDLSV[] = {_D,_UnderBar,0,_L,_UnderBar,0,_S,_UnderBar,0,_V,_UnderBar};
code BYTE tvLSV[] = {0,0,0,_L,_UnderBar,0,_S,_UnderBar,0,_V,_UnderBar};
#else
code BYTE tvY[] = {_T,_V,_minus,_Y,0,0,_checkOff};
code BYTE tvY7[] = {_T,_V,_minus,_Y,_7,0,_checkOff};
code BYTE tvG[] = {_T,_V,_minus,_G,0,0,_checkOff};
code BYTE tvPG[] = {_T,_V,_minus,_P,_G,0,_checkOff};
code BYTE tv14[] = {_T,_V,_minus,_1,_4,0,_checkOff};
code BYTE tvMA[] = {_T,_V,_minus,_M,_A,0,_checkOff};
code BYTE tvFV[] = {_Lbar,_F,_Rbar,_V,_checkOff};
code BYTE tvDLSV[] = {_D,_checkOff,0,_L,_checkOff,0,_S,_checkOff,0,_V,_checkOff};
code BYTE tvLSV[] = {0,0,0,_L,_checkOff,0,_S,_checkOff,0,_V,_checkOff};
#endif

code BYTE CcdOldCode[] = {_O,_L,_D,0,_C,_O,_D,_E,0,_Colon,0,_UnderBar,_UnderBar,_UnderBar,_UnderBar};
code BYTE CcdNewCode[] = {_N,_E,_W,0,_C,_O,_D,_E,0,_Colon,0,_UnderBar,_UnderBar,_UnderBar,_UnderBar};
//code BYTE CcdRepeatCode[] = {_R,_E,_P,_E,_A,_T,0,_C,_O,_D,_E,0,_Colon,0,_UnderBar,_UnderBar,_UnderBar,_UnderBar};
code BYTE CcdRepeatCode[] = {_C,_O,_N,_F,_I,_R,_M,0,0,_Colon,0,_UnderBar,_UnderBar,_UnderBar,_UnderBar};
#endif

/////////////////////////////////////////////////////////////////////
//	ANTENA INPUT
/////////////////////////////////////////////////////////////////////
code BYTE AntenaInput_Eng[] = {_A,_N,_T,_E,_N,_A,0,_I,_N,_P,_U,_T};
code BYTE AntenaInput_Kor[] = {_AHN,_TE,_NA,_EIP,_YERK};

code BYTE * code AntenaInput[] = {
	AntenaInput_Eng,
	AntenaInput_Kor
};

code BYTE AntenaInput_Sizeof[] = {
	sizeof(AntenaInput_Eng),
	sizeof(AntenaInput_Kor)
};

#if 0
code BYTE Normal[] = {_N,_O,_R,_M,_A,_L};
code BYTE Normal_Chi[] = {CH_NORMAL};
code BYTE Normal2[] = {_N,0,_O,0,_R,0,_M,0,_A,0,_L};
code BYTE Dynamic[] = {_D,_Y,_N,_A,_M,_I,_C};
code BYTE Dynamic_Chi[] = {CH_DYNAMIC};
code BYTE Dynamic2[] = {_D,0,_Y,0,_N,0,_A,0,_M,0,_I,0,_C};
code BYTE Cinema[] = {_C,_I,_N,_E,_M,_A};
code BYTE Cinema_Chi[] = {CH_CINEMA};
code BYTE Cinema2[] = {_C,0,_I,0,_N,0,_E,0,_M,0,_A};
code BYTE User[] = {_U,_S,_E,_R};
code BYTE User_Chi[] = {CH_USER};
code BYTE User2[] = {_U,0,_S,0,_E,0,_R};
#else
/////////////////////////////////////////////////////////////////////
//	NORMAL
/////////////////////////////////////////////////////////////////////
code BYTE Normal_Eng[] = {_N,_O,_R,_M,_A,_L};
code BYTE Normal_Chi[] = {CH_NORMAL};
code BYTE * code Normal[] = {
	Normal_Eng,
	Normal_Chi
};
code BYTE Normal_Sizeof[] = {
	sizeof(Normal_Eng),
	sizeof(Normal_Chi)
};
/////////////////////////////////////////////////////////////////////
//	DYNANIC
/////////////////////////////////////////////////////////////////////
code BYTE Dynamic_Eng[] = {_D,_Y,_N,_A,_M,_I,_C};
code BYTE Dynamic_Chi[] = {CH_DYNAMIC};
code BYTE * code Dynamic[] = {
	Dynamic_Eng,
	Dynamic_Chi
};
code BYTE Dynamic_Sizeof[] = {
	sizeof(Dynamic_Eng),
	sizeof(Dynamic_Chi)
};

/////////////////////////////////////////////////////////////////////
//	CINEMA
/////////////////////////////////////////////////////////////////////
code BYTE Cinema_Eng[] = {_C,_I,_N,_E,_M,_A};
code BYTE Cinema_Chi[] = {CH_CINEMA};
code BYTE * code Cinema[] = {
	Cinema_Eng,
	Cinema_Chi
};
code BYTE Cinema_Sizeof[] = {
	sizeof(Cinema_Eng),
	sizeof(Cinema_Chi)
};

/////////////////////////////////////////////////////////////////////
//	USER
/////////////////////////////////////////////////////////////////////
code BYTE User_Eng[] = {_U,_S,_E,_R};
code BYTE User_Chi[] = {CH_USER};
code BYTE * code User[] = {
	User_Eng,
	User_Chi
};
code BYTE User_Sizeof[] = {
	sizeof(User_Eng),
	sizeof(User_Chi)
};

#endif

#if 0
code BYTE Normal2[] = {_N,0,_O,0,_R,0,_M,0,_A,0,_L};
code BYTE Dynamic2[] = {_D,0,_Y,0,_N,0,_A,0,_M,0,_I,0,_C};
code BYTE Cinema2[] = {_C,0,_I,0,_N,0,_E,0,_M,0,_A};
code BYTE User2[] = {_U,0,_S,0,_E,0,_R};
#else
/////////////////////////////////////////////////////////////////////
//	NORMAL2
/////////////////////////////////////////////////////////////////////
code BYTE Normal2_Eng[] = {_N,0,_O,0,_R,0,_M,0,_A,0,_L};
code BYTE * code Normal2[] = {
	Normal2_Eng
};
code BYTE Normal2_Sizeof[] = {
	sizeof(Normal2_Eng)
};
/////////////////////////////////////////////////////////////////////
//	DYNANIC2
/////////////////////////////////////////////////////////////////////
code BYTE Dynamic2_Eng[] = {_D,0,_Y,0,_N,0,_A,0,_M,0,_I,0,_C};
code BYTE * code Dynamic2[] = {
	Dynamic2_Eng
};
code BYTE Dynamic2_Sizeof[] = {
	sizeof(Dynamic2_Eng)
};
/////////////////////////////////////////////////////////////////////
//	CINEMA2
/////////////////////////////////////////////////////////////////////
code BYTE Cinema2_Eng[] = {_C,0,_I,0,_N,0,_E,0,_M,0,_A};
code BYTE * code Cinema2[] = {
	Cinema2_Eng
};
code BYTE Cinema2_Sizeof[] = {
	sizeof(Cinema2_Eng)
};
/////////////////////////////////////////////////////////////////////
//	USER2
/////////////////////////////////////////////////////////////////////
code BYTE User2_Eng[] = {_U,0,_S,0,_E,0,_R};
code BYTE * code User2[] = {
	User2_Eng
};
code BYTE User2_Sizeof[] = {
	sizeof(User2_Eng)
};
#endif


code BYTE Wide_Eng[] = {_W,_I,_D,_E};
#if 0
/////////////////////////////////////////////////////////////////////
//	WIDE
/////////////////////////////////////////////////////////////////////
code BYTE Wide_Eng[] = {_W,_I,_D,_E};
code BYTE Wide_Kor[] = {_W,_I,_D,_E};
code BYTE Wide_Jpn[] = {_W,_I,_D,_E};

code BYTE * code Wide[] = {
	Wide_Eng,
	Wide_Kor,
	Wide_Jpn
};

code BYTE Wide_Sizeof[] = {
	sizeof(Wide_Eng),
	sizeof(Wide_Kor),
	sizeof(Wide_Jpn)
};
#endif

#if 0
code BYTE Music[] = {_M,_U,_S,_I,_C};
code BYTE News[] = {_N,_E,_W,_S};
#else	//old------------------------------
//	MUSIC : smpark 20030722
code BYTE Music_Eng[] = {_M,_U,_S,_I,_C};
code BYTE Music_Chi[] = {CH_MUSIC};
code BYTE * code Music[] = {
	Music_Eng,
	Music_Chi
};
code BYTE Music_Sizeof[] = {
	sizeof(Music_Eng),
	sizeof(Music_Chi)
};
//	NEWS : smpark 20030722
code BYTE News_Eng[] = {_N,_E,_W,_S};
code BYTE News_Chi[] = {0x41,_BK,_BK,_BK,0x42};			// +jwshin 040801
code BYTE * code News[] = {
	News_Eng,
	News_Chi
};
code BYTE News_Sizeof[] = {
	sizeof(News_Eng),
	sizeof(News_Chi)
};
#endif

#if 1
code BYTE Mono[] = {_M,_O,_N,_O};
code BYTE Stereo[] = {_S,_T,_E,_R,_E,_O};
#else	//old------------------------------
//	MONO : smpak 20030722
code BYTE Mono_Eng[] = {_M,_O,_N,_O};
code BYTE Mono_Chi[] = {_M,_O,_N,_O};
code BYTE * code Mono[] = {
	Mono_Eng,
	Mono_Chi
};
code BYTE Mono_Sizeof[] = {
	sizeof(Mono_Eng),
	sizeof(Mono_Chi)
};
//	STEREO: smpark 20030722
code BYTE Stereo_Eng[] = {_S,_T,_E,_R,_E,_O};
code BYTE Stereo_Chi[] = {_S,_T,_E,_R,_E,_O};
code BYTE * code Stereo[] = {
	Stereo_Eng,
	Stereo_Chi
};
code BYTE Stereo_Sizeof[] = {
	sizeof(Stereo_Eng),
	sizeof(Stereo_Chi)
};
#endif

#if 0
code BYTE Music2[] = {_M,0,_U,0,_S,0,_I,0,_C};
code BYTE News2[] = {_N,0,_E,0,_W,0,_S};
#else	//old------------------------------
code BYTE Music2_Eng[] = {_M,0,_U,0,_S,0,_I,0,_C};
code BYTE * code Music2[] = {
	Music2_Eng
};
code BYTE Music2_Sizeof[] = {
	sizeof(Music2_Eng)
};
code BYTE News2_Eng[] = {_N,0,_E,0,_W,0,_S};
code BYTE * code News2[] = {
	News2_Eng
};
code BYTE News2_Sizeof[] = {
	sizeof(News2_Eng)
};
#endif

//	LANGUAGE OPTION: smpark 20030722
//********************************************
code BYTE LangA_Eng[] = {_L,_A,_N,_G,0,_A};
code BYTE * code LangA[] = {
	LangA_Eng
};
code BYTE LangA_Sizeof[] = {
	sizeof(LangA_Eng)
};
//********************************************
code BYTE LangB_Eng[] = {_L,_A,_N,_G,0,_B};
code BYTE * code LangB[] = {
	LangB_Eng
};
code BYTE LangB_Sizeof[] = {
	sizeof(LangB_Eng)
};
//********************************************
code BYTE LangAB_Eng[] = {_L,_A,_N,_G,0,_A,_B};
code BYTE * code LangAB[] = {
	LangAB_Eng
};
code BYTE LangAB_Sizeof[] = {
	sizeof(LangAB_Eng)
};

#if 0
// 20030822
// MTS
code BYTE MultiSound_Eng[] = {_M,_T,_S};
code BYTE MultiSound_Kor[] = {_M,_T,_S};
code BYTE MultiSound_Jpn[] = {_M,_T,_S};

code BYTE * code MultiSound[] = {
	MultiSound_Eng,
	MultiSound_Kor,
	MultiSound_Jpn
};

code BYTE MultiSound_Sizeof[] = {
	sizeof(MultiSound_Eng),
	sizeof(MultiSound_Kor),
	sizeof(MultiSound_Jpn)
};
#endif

// 20030821
// TREBLE
code BYTE Treble_Eng[] = {_T,_R,_E,_B,_L,_E};
code BYTE Treble_Kor[] = {0xCA,_BK,_BK,_BK,0xCB};		//+jwshin 040801

code BYTE * code Treble[] = {
	Treble_Eng,
	Treble_Kor
};

code BYTE Treble_Sizeof[] = {
	sizeof(Treble_Eng),
	sizeof(Treble_Kor)
};

// TREBLE
code BYTE Bass_Eng[] = {_B,_A,_S,_S};
code BYTE Bass_Kor[] = {0xCC,_BK,_BK,_BK,0xCB};			//+jwshin 040801

code BYTE * code Bass[] = {
	Bass_Eng,
	Bass_Kor
};

code BYTE Bass_Sizeof[] = {
	sizeof(Bass_Eng),
	sizeof(Bass_Kor)
};

// LOUDNESS
code BYTE Loudness_Eng[] = {_L,_O,_U,_D,_N,_E,_S,_S};
code BYTE Loudness_Kor[] = {0xcb,_BK,_BK,_BK,0x35};		//+jwshin 040801

code BYTE * code Loudness[] = {
	Loudness_Eng,
	Loudness_Kor
};

code BYTE Loudness_Sizeof[] = {
	sizeof(Loudness_Eng),
	sizeof(Loudness_Kor)
};

// SMART SOUND CONTROL
code BYTE SmartSound_Eng[] = {_S,_M,_A,_R,_T,0,_S,_O,_U,_N,_D,0,_C,_O,_N,_T,_R,_O,_L};
code BYTE SmartSound_Kor[] = {0x36,0x37,0xcb,0x38,0x39,0x3a};		//+jwshin 040801

code BYTE * code SmartSound[] = {
	SmartSound_Eng,
	SmartSound_Kor
};

code BYTE SmartSound_Sizeof[] = {
	sizeof(SmartSound_Eng),
	sizeof(SmartSound_Kor)
};

/////////////////////////////////////////////////////////////////////
//	WAITING
/////////////////////////////////////////////////////////////////////
code BYTE Wait_Eng[] = {_P,_L,_E,_A,_S,_E,_space,_W,_A,_I,_T};
code BYTE Wait_Kor[] = {_P,_L,_E,_A,_S,_E,_space,_W,_A,_I,_T};


code BYTE * code Wait[] = {
	Wait_Eng,
	Wait_Kor
	
};
code BYTE Wait_Sizeof[] = {
	sizeof(Wait_Eng),
	sizeof(Wait_Kor)
};

/////////////////////////////////////////////////////////////////////
//	AIR
/////////////////////////////////////////////////////////////////////
code BYTE Air_Eng[] = {_A,_I,_R};
code BYTE Air_Kor[] = {_A,_I,_R};


code BYTE * code Air[] = {
	Air_Eng,
    	Air_Kor
};

code BYTE Air_Sizeof[] = {
	sizeof(Air_Eng),
	sizeof(Air_Kor)
};

/////////////////////////////////////////////////////////////////////
//	CATV
/////////////////////////////////////////////////////////////////////
code BYTE Catv_Eng[] = {_C,_A,_T,_V};
code BYTE Catv_Kor[] = {_C,_A,_T,_V};

code BYTE * code Catv[] = {
	Catv_Eng,
    	Catv_Kor
};

code BYTE Catv_Sizeof[] = {
	sizeof(Catv_Eng),
	sizeof(Catv_Kor)
};

#if 0
/////////////////////////////////////////////////////////////////////
//	CH
/////////////////////////////////////////////////////////////////////
code BYTE Ch_Eng[] = {_C,_H};
//code BYTE Ch_Kor[] = {_C,_H};
//code BYTE Ch_Jpn[] = {_C,_H};

code BYTE * code Chdot[] = {
	Ch_Eng//,
	//Ch_Kor,
	//Ch_Jpn
};

code BYTE Chdot_Sizeof[] = {
	sizeof(Ch_Eng)//,
	//sizeof(Ch_Kor),
	//sizeof(Ch_Jpn)
};

#ifdef  ChannelDisplayDouble
/////////////////////////////////////////////////////////////////////
//	CH2
/////////////////////////////////////////////////////////////////////
code BYTE Ch2_Eng[] = {_C,0,_H};
code BYTE * code Chdot2[] = {
	Ch2_Eng
};
code BYTE Chdot2_Sizeof[] = {
	sizeof(Ch2_Eng)
};

code BYTE Catv2_Eng[] = {_C,0,_A,0,_T,0,_V};
code BYTE * code Catv2[] = {
	Catv2_Eng
};
code BYTE Catv2_Sizeof[] = {
	sizeof(Catv2_Eng)
}; 
#endif  
#else//------------

/////////////////////////////////////////////////////////////////////
//	CH
code BYTE Chdot[] = {_C,_H};
#ifdef  ChannelDisplayDouble
/////////////////////////////////////////////////////////////////////
//	CH2
code BYTE Chdot2[] = {_C,0,_H};
//	CATV
code BYTE Catv2[] = {_C,0,_A,0,_T,0,_V};
#endif  

#endif	//-------------------

#if 0
/////////////////////////////////////////////////////////////////////
//	AUTO CHANNEL
/////////////////////////////////////////////////////////////////////
code BYTE AutoChannel_Eng[] = {_A,_U,_T,_O,0x00,_C,_H,_A,_N,_N,_E,_L};
code BYTE AutoChannel_Kor[] = {_A,_U,_T,_O,0x00,_C,_H,_A,_N,_N,_E,_L};
code BYTE AutoChannel_Jpn[] = {_A,_U,_T,_O,0x00,_C,_H,_A,_N,_N,_E,_L};

code BYTE * code AutoChannel[] = {
	AutoChannel_Eng,
    	AutoChannel_Kor,
	AutoChannel_Jpn
};

code BYTE AutoChannel_Sizeof[] = {
	sizeof(AutoChannel_Eng),
	sizeof(AutoChannel_Kor),
	sizeof(AutoChannel_Jpn)
};

/////////////////////////////////////////////////////////////////////
//	STOP
/////////////////////////////////////////////////////////////////////
code BYTE Stop_Eng[] = {_S,_T,_O,_P};
code BYTE Stop_Kor[] = {_S,_T,_O,_P};
code BYTE Stop_Jpn[] = {_S,_T,_O,_P};

code BYTE * code Stop[] = {
	Stop_Eng,
	Stop_Kor,
	Stop_Jpn
};

code BYTE Stop_Sizeof[] = {
	sizeof(Stop_Eng),
	sizeof(Stop_Kor),
	sizeof(Stop_Jpn)
};
/////////////////////////////////////////////////////////////////////
//	START
code BYTE Start_Eng[] = {_S,_T,_A,_R,_T};
code BYTE * code Start[] = {
	Start_Eng
};

code BYTE Start_Sizeof[] = {
	sizeof(Start_Eng)
};


#endif

/////////////////////////////////////////////////////////////////////
//	START
/////////////////////////////////////////////////////////////////////
code BYTE Start_Eng[] = {_S,_T,_A,_R,_T};
code BYTE Start_Chi[] = {CH_START};

code BYTE * code Start[] = {
		Start_Eng,
    	Start_Chi
};

code BYTE Start_Sizeof[] = {
	sizeof(Start_Eng),
	sizeof(Start_Chi)
};
/////////////////////////////////////////////////////////////////////
//	SEARCHING
/////////////////////////////////////////////////////////////////////
code BYTE Searching_Eng[] = {_S,_E,_A,_R,_C,_H};
code BYTE Searching_Kor[] = {_S,_E,_A,_R,_C,_H};


code BYTE * code Searching[] = {
	Searching_Eng,
    	Searching_Kor
};

code BYTE Searching_Sizeof[] = {
	sizeof(Searching_Eng),
	sizeof(Searching_Kor)
};

/////////////////////////////////////////////////////////////////////
//	PRESS SELECT TO STOP
/////////////////////////////////////////////////////////////////////
code BYTE Press_Eng[] = {_P,_R,_E,_S,_S,0x00,_S,_E,_L,_E,_C,_T,0x00,_T,_O,0x00,_S,_T,_O,_P};
code BYTE Press_Kor[] = {_P,_R,_E,_S,_S,0x00,_S,_E,_L,_E,_C,_T,0x00,_T,_O,0x00,_S,_T,_O,_P};


code BYTE * code Press[] = {
	Press_Eng,
    	Press_Kor
};

code BYTE Press_Sizeof[] = {
	sizeof(Press_Eng),
	sizeof(Press_Kor)
};

/////////////////////////////////////////////////////////////////////
//	PROCESSING
/////////////////////////////////////////////////////////////////////
code BYTE Processing_Eng[] = {_P,_R,_O,_C,_E,_S,_S,_I,_N,_G};
code BYTE Processing_Kor[] = {_P,_R,_O,_C,_E,_S,_S,_I,_N,_G};


code BYTE * code Processing[] = {
	Processing_Eng,
    	Processing_Kor
};

code BYTE Processing_Sizeof[] = {
	sizeof(Processing_Eng),
	sizeof(Processing_Kor)
};


/////////////////////////////////////////////////////////////////////
//	AUTO CONFIGURATION
/////////////////////////////////////////////////////////////////////
code BYTE AutoConfig_Eng[] = {_A,_U,_T,_O,0x00,_C,_O,_N,_F,_I,_G,_U,_R,_A,_T,_I,_O,_N};
code BYTE AutoConfig_Kor[] = {_A,_U,_T,_O,0x00,_C,_O,_N,_F,_I,_G,_U,_R,_A,_T,_I,_O,_N};


code BYTE * code AutoConfig[] = {
	AutoConfig_Eng,
    	AutoConfig_Kor
};

code BYTE AutoConfig_Sizeof[] = {
	sizeof(AutoConfig_Eng),
	sizeof(AutoConfig_Kor)
};

//	AUTO TUNE
/////////////////////////////////////////////////////////////////////
code BYTE AutoTune_Eng[] = {_A,_U,_T,_O,0x00,_T,_U,_N,_E};
code BYTE AutoTune_Kor[] = {0x27,0x28,0x0a,0x0b};


code BYTE * code AutoTune[] = {
	AutoTune_Eng,
    	AutoTune_Kor
};

code BYTE AutoTune_Sizeof[] = {
	sizeof(AutoTune_Eng),
	sizeof(AutoTune_Kor)
};

/////////////////////////////////////////////////////////////////////
//	MANUAL CHANNEL
/////////////////////////////////////////////////////////////////////
code BYTE ManualChannel_Eng[] = {_M,_A,_N,_U,_A,_L,0x00,_C,_H,_A,_N,_N,_E,_L};
code BYTE ManualChannel_Kor[] = {_M,_A,_N,_U,_A,_L,0x00,_C,_H,_A,_N,_N,_E,_L};

code BYTE * code ManualChannel[] = {
	ManualChannel_Eng,
    	ManualChannel_Kor
};

code BYTE ManualChannel_Sizeof[] = {
	sizeof(ManualChannel_Eng),
	sizeof(ManualChannel_Kor)
};

/////////////////////////////////////////////////////////////////////
//	FINE
/////////////////////////////////////////////////////////////////////
code BYTE Fine_Eng[] = {_F,_I,_N,_E};
code BYTE Fine_Kor[] = {_F,_I,_N,_E};

code BYTE * code Fine[] = {
	Fine_Eng,
    	Fine_Kor
};

code BYTE Fine_Sizeof[] = {
	sizeof(Fine_Eng),
	sizeof(Fine_Kor)
};

/////////////////////////////////////////////////////////////////////
//	EXIT SUB
/////////////////////////////////////////////////////////////////////
code BYTE ExitSub_Eng[] = {_E,_X,_I,_T,0,_S,_U,_B};
code BYTE ExitSub_Kor[] = {_E,_X,_I,_T,0,_S,_U,_B};

code BYTE * code ExitSub[] = {
	ExitSub_Eng,
    	ExitSub_Kor
};

code BYTE ExitSub_Sizeof[] = {
	sizeof(ExitSub_Eng),
	sizeof(ExitSub_Kor)
};

/////////////////////////////////////////////////////////////////////
//	FINE TURN
/////////////////////////////////////////////////////////////////////
code BYTE FineTune_Eng[] = {_F,_I,_N,_E,0,_T,_U,_N,_E};
code BYTE FineTune_Kor[] = {_CHAE,_NULL,_JUNG,_MIL,_JO,_JUNG};


code BYTE * code FineTune[] = {
	FineTune_Eng,
   	FineTune_Kor
};

code BYTE FineTune_Sizeof[] = {
	sizeof(FineTune_Eng),
	sizeof(FineTune_Kor)
};

/////////////////////////////////////////////////////////////////////
//	BLUE SCREEN
/////////////////////////////////////////////////////////////////////
code BYTE BlueScreen_Eng[] = {_B,_L,_U,_E,0,_S,_C,_R,_E,_E,_N};
code BYTE BlueScreen_Kor[] = {_CHUNG,_SAEK,_HWA,_MYUN};


code BYTE * code BlueScreen[] = {
	BlueScreen_Eng,
	BlueScreen_Kor
};

code BYTE BlueScreen_Sizeof[] = {
	sizeof(BlueScreen_Eng),
	sizeof(BlueScreen_Kor)
};

/////////////////////////////////////////////////////////////////////
//	SCREEN MODE
/////////////////////////////////////////////////////////////////////
code BYTE ScreenMode_Eng[] = {_S,_C,_R,_E,_E,_N,0,_A,_S,_P,_E,_C,_T,0,_R,_A,_T,_I,_O};
code BYTE ScreenMode_Kor[] = {0xA2,0xA3,0x30,0x31};

code BYTE * code ScreenMode[] = {
	ScreenMode_Eng,
	ScreenMode_Kor
};
code BYTE ScreenMode_Sizeof[] = {
	sizeof(ScreenMode_Eng),
	sizeof(ScreenMode_Kor)
};

/////////////////////////////////////////////////////////////////////
//	SMART PICTURE CONTROL
/////////////////////////////////////////////////////////////////////
code BYTE SmartPicture_Eng[] = {_S,_M,_A,_R,_T,0,_P,_I,_C,_T,_U,_R,_E,0,_C,_O,_N,_T,_R,_O,_L};
code BYTE SmartPicture_Kor[] = {_HWA,_MYUN,_MO,_DEA};


code BYTE * code SmartPicture[] = {
	SmartPicture_Eng,
	SmartPicture_Kor
};
code BYTE SmartPicture_Sizeof[] = {
	sizeof(SmartPicture_Eng),
	sizeof(SmartPicture_Kor)
};

/////////////////////////////////////////////////////////////////////
//	SLEEP
/////////////////////////////////////////////////////////////////////
code BYTE Sleep_Eng[] = {_S,_L,_E,_E,_P};
code BYTE Sleep_Kor[] = {_TA,_YI,_MER};


code BYTE * code Sleep[] = {
	Sleep_Eng,
	Sleep_Kor
};
code BYTE Sleep_Sizeof[] = {
	sizeof(Sleep_Eng),
	sizeof(Sleep_Kor)
};

/////////////////////////////////////////////////////////////////////
//	SLEEP2
/////////////////////////////////////////////////////////////////////
code BYTE Sleep2_Eng[] = {_S,0,_L,0,_E,0,_E,0,_P};
code BYTE * code Sleep2[] = {
	Sleep2_Eng
};
code BYTE Sleep2_Sizeof[] = {
	sizeof(Sleep2_Eng)
};

/////////////////////////////////////////////////////////////////////
//	ADD
/////////////////////////////////////////////////////////////////////
code BYTE Add_Eng[] = {_A,_D,_D};
code BYTE Add_Kor[] = {_A,_D,_D};


code BYTE * code Add[] = {
	Add_Eng,
    	Add_Kor
};

code BYTE Add_Sizeof[] = {
	sizeof(Add_Eng),
	sizeof(Add_Kor)
};

/////////////////////////////////////////////////////////////////////
//	Erase
/////////////////////////////////////////////////////////////////////
code BYTE Erase_Eng[] = {_E,_R,_A,_S,_E};
code BYTE * code Erase[] = {
	Erase_Eng,
};
code BYTE Erase_Sizeof[] = {
	sizeof(Erase_Eng),
};

/////////////////////////////////////////////////////////////////////
//	ON
/////////////////////////////////////////////////////////////////////
code BYTE On_Eng[] = {_O,_N};
code BYTE On_Chi[] = {CH_ON};
code BYTE * code On[] = {
	On_Eng,
	On_Chi
};
code BYTE On_Sizeof[] = {
	sizeof(On_Eng),
	sizeof(On_Chi)
};

/////////////////////////////////////////////////////////////////////
//	OFF
/////////////////////////////////////////////////////////////////////
code BYTE Off_Eng[] = {_O,_F,_F};
code BYTE Off_Chi[] = {CH_OFF};
code BYTE * code Off[] = {
	Off_Eng,
	Off_Chi
};
code BYTE Off_Sizeof[] = {
	sizeof(Off_Eng),
	sizeof(Off_Chi)
};

/////////////////////////////////////////////////////////////////////
//	dos 640*400	//2003-08-26
/////////////////////////////////////////////////////////////////////
code BYTE Dos640_Eng[] = {_6,_4,_0};
code BYTE * code Dos640[] = {
	Dos640_Eng
};
code BYTE Dos640_Sizeof[] = {
	sizeof(Dos640_Eng)
};
/////////////////////////////////////////////////////////////////////
//	dos 720*400	//2003-08-26
/////////////////////////////////////////////////////////////////////
code BYTE Dos720_Eng[] = {_7,_2,_0};
code BYTE * code Dos720[] = {
	Dos720_Eng
};
code BYTE Dos720_Sizeof[] = {
	sizeof(Dos720_Eng)
};

///MODE/////////////////////////////////////////////////////////
code BYTE Mode_Eng[] = {_M,_O,_D,_E};
code BYTE Mode_Chi[] = {CH_MODE};
code BYTE * code Mode[] = {
	Mode_Eng,
	Mode_Chi
};
code BYTE Mode_Sizeof[] = {
	sizeof(Mode_Eng),
	sizeof(Mode_Chi)
};

/////////////////////////////////////////////////////////////////////
//	YES
/////////////////////////////////////////////////////////////////////
code BYTE Yes_Eng[] = {_Y,_E,_S};
code BYTE Yes_Kor[] = {_Y,_E,_S};

code BYTE * code Yes[] = {
	Yes_Eng,
	Yes_Kor
};

code BYTE Yes_Sizeof[] = {
	sizeof(Yes_Eng),
	sizeof(Yes_Kor)
};

/////////////////////////////////////////////////////////////////////
//	No
/////////////////////////////////////////////////////////////////////
code BYTE No_Eng[] = {_N,_O,0};
code BYTE No_Kor[] = {_N,_O,0};

code BYTE * code No[] = {
	No_Eng,
	No_Kor
};

code BYTE No_Sizeof[] = {
	sizeof(No_Eng),
	sizeof(No_Kor)
};

/////////////////////////////////////////////////////////////////////
//	CAPTION
/////////////////////////////////////////////////////////////////////
code BYTE CcdCaption_Eng[] = {_C,_a,_p,_t,_i,_o,_n};

code BYTE * code CcdCaption[] = {
	CcdCaption_Eng
};

code BYTE CcdCaption_Sizeof[] = {
	sizeof(CcdCaption_Eng)
};
/////////////////////////////////////////////////////////////////////
//	Text
/////////////////////////////////////////////////////////////////////
code BYTE CcdText_Eng[] = {_T,_e,_x,_t,0,0,0};

code BYTE * code CcdText[] = {
	CcdText_Eng
};

code BYTE CcdText_Sizeof[] = {
	sizeof(CcdText_Eng)
};
/////////////////////////////////////////////////////////////////////
//	CAPTION
/////////////////////////////////////////////////////////////////////
code BYTE CcdBox_Eng[] = {_B,_o,_x,0,0,0};

code BYTE * code CcdBox[] = {
	CcdBox_Eng
};

code BYTE CcdBox_Sizeof[] = {
	sizeof(CcdBox_Eng)
};
/////////////////////////////////////////////////////////////////////
//	CAPTION
/////////////////////////////////////////////////////////////////////
code BYTE CcdShadow_Eng[] = {_S,_h,_a,_d,_o,_w};

code BYTE * code CcdShadow[] = {
	CcdShadow_Eng
};

code BYTE CcdShadow_Sizeof[] = {
	sizeof(CcdShadow_Eng)
};



/////////////////////////////////////////////////////////////////////
//	PIP ON/OFF
/////////////////////////////////////////////////////////////////////
code BYTE PipOnOff_Eng[] = {_P,_I,_P,0x00,_O,_N,_slash,_O,_F,_F};
code BYTE PipOnOff_Kor[] = {_P,_I,_P,0x00,_O,_N,_slash,_O,_F,_F};

code BYTE * code PipOnOff[] = {
	PipOnOff_Eng,
	PipOnOff_Kor
};

code BYTE PipOnOff_Sizeof[] = {
	sizeof(PipOnOff_Eng),
	sizeof(PipOnOff_Kor)
};

/////////////////////////////////////////////////////////////////////
//	LARGE
/////////////////////////////////////////////////////////////////////
code BYTE Large_Eng[] = {_L,_A,_R,_G,_E};
code BYTE Large_Chi[] = {CH_LARGE};

code BYTE * code Large[] = {
	Large_Eng,
	Large_Chi
};

code BYTE Large_Sizeof[] = {
	sizeof(Large_Eng),
	sizeof(Large_Chi)
};

/////////////////////////////////////////////////////////////////////
//	MIDDLE
/////////////////////////////////////////////////////////////////////
code BYTE Middle_Eng[] = {_M,_I,_D,_D,_L,_E};
code BYTE Middle_Chi[] = {CH_MIDDLE};

code BYTE * code Middle[] = {
		Middle_Eng,
    	Middle_Chi
};

code BYTE Middle_Sizeof[] = {
	sizeof(Middle_Eng),
	sizeof(Middle_Chi)
};

/////////////////////////////////////////////////////////////////////
//	SMALL
/////////////////////////////////////////////////////////////////////
code BYTE Small_Eng[] = {_S,_M,_A,_L,_L};
code BYTE Small_Chi[] = {CH_SMALL};

code BYTE * code Small[] = {
	Small_Eng,
	Small_Chi
};

code BYTE Small_Sizeof[] = {
	sizeof(Small_Eng),
	sizeof(Small_Chi)
};

/////////////////////////////////////////////////////////////////////
//	PIP CONTROL
/////////////////////////////////////////////////////////////////////
code BYTE PipControl_Eng[] = {_P,_I,_P,0x00,_C,_O,_N,_T,_R,_O,_L};
code BYTE * code PipControl[] = {
	PipControl_Eng
};
code BYTE PipControl_Sizeof[] = {
	sizeof(PipControl_Eng)
};

/*
/////////////////////////////////////////////////////////////////////
//	PIP SWAP
/////////////////////////////////////////////////////////////////////
code BYTE PipSwap_Eng[] = {_P,_I,_P,0x00,_S,_W,_A,_P};
code BYTE * code PipSwap[] = {
	PipSwap_Eng
};
code BYTE PipSwap_Sizeof[] = {
	sizeof(PipSwap_Eng)
};
*/
#if 0
/////////////////////////////////////////////////////////////////////
//	PIP POSITION
/////////////////////////////////////////////////////////////////////
code BYTE PipPosition_Eng[] = {_P,_I,_P,0x00,_P,_O,_S,_I,_T,_I,_O,_N};
code BYTE * code PipPosition[] = {
	PipPosition_Eng
};
code BYTE PipPosition_Sizeof[] = {
	sizeof(PipPosition_Eng)
};
#endif
/////////////////////////////////////////////////////////////////////
//	PIP	BELEND
/////////////////////////////////////////////////////////////////////
code BYTE PipBlend_Eng[] = {_P,_I,_P,0x00,_T,_R,_A,_N,_S,_P,_A,_R,_E,_N,_C,_Y};
code BYTE PipBlend_Kor[] = {_P1,_I1,_P1,_BK,_BAN,_TOU,_MYUNG};  

code BYTE * code PipBlend[] = {
	PipBlend_Eng,
	PipBlend_Kor
};
code BYTE PipBlend_Sizeof[] = {
	sizeof(PipBlend_Eng),
	sizeof(PipBlend_Kor)
};

/*
/////////////////////////////////////////////////////////////////////
//	VOLUME
/////////////////////////////////////////////////////////////////////
code BYTE Volume_Eng[] = {_V,_O,_L,_U,_M,_E,0};
code BYTE Volume_Kor[] = {_V,_O,_L,_U,_M,_E,0};
code BYTE Volume_Jpn[] = {_V,_O,_L,_U,_M,_E,0};

code BYTE * code Volume[] = {
	Volume_Eng,
    	Volume_Kor,
    	Volume_Jpn
};

code BYTE Volume_Sizeof[] = {
	sizeof(Volume_Eng),
	sizeof(Volume_Kor),
	sizeof(Volume_Jpn)
};
*/
/////////////////////////////////////////////////////////////////////
//	MUTE
/////////////////////////////////////////////////////////////////////
code BYTE Mute_Eng[] = {_M,_U,_T,_E,0x00,0x00};
code BYTE Mute_Kor[] = {_M,_U,_T,_E,0x00,0x00};

code BYTE * code Mute[] = {
	Mute_Eng,
    	Mute_Kor
};

code BYTE Mute_Sizeof[] = {
	sizeof(Mute_Eng),
	sizeof(Mute_Kor)
};

/////////////////////////////////////////////////////////////////////
//	kHz
/////////////////////////////////////////////////////////////////////
code BYTE kHz_Eng[] = {_k,_H,_z};
code BYTE * code kHz[] = {
	kHz_Eng
};
code BYTE kHz_Sizeof[] = {
	sizeof(kHz_Eng)
};

/////////////////////////////////////////////////////////////////////
//	POWER SAVER MODE
/////////////////////////////////////////////////////////////////////
code BYTE PowerSaverMode_Eng[] = {_P,_O,_W,_E,_R,0x00,_S,_A,_V,_E,_R,0x00,_M,_O,_D,_E};
code BYTE PowerSaverMode_Kor[] = {_P,_O,_W,_E,_R,0x00,_S,_A,_V,_E,_R,0x00,_M,_O,_D,_E};


code BYTE * code PowerSaverMode[] = {
	PowerSaverMode_Eng,
    	PowerSaverMode_Kor
};

code BYTE PowerSaverMode_Sizeof[] = {
	sizeof(PowerSaverMode_Eng),
	sizeof(PowerSaverMode_Kor)
};

/////////////////////////////////////////////////////////////////////
//	CHECK SIGNAL CABLE
/////////////////////////////////////////////////////////////////////
code BYTE CheckSignalCable_Eng[] = {_C,_H,_E,_C,_K,0x00,_S,_I,_G,_N,_A,_L,0x00,_C,_A,_B,_L,_E};
code BYTE CheckSignalCable_Kor[] = {_C,_H,_E,_C,_K,0x00,_S,_I,_G,_N,_A,_L,0x00,_C,_A,_B,_L,_E};


code BYTE * code CheckSignalCable[] = {
	CheckSignalCable_Eng,
    	CheckSignalCable_Kor
};

code BYTE CheckSignalCable_Sizeof[] = {
	sizeof(CheckSignalCable_Eng),
	sizeof(CheckSignalCable_Kor)
};

/////////////////////////////////////////////////////////////////////
//	OUT OF FREQUENCY
/////////////////////////////////////////////////////////////////////
code BYTE OutOfFreq_Eng[] = {_O,_U,_T,0x00,_O,_F,0x00,_F,_R,_E,_Q,_U,_E,_N,_C,_Y};
code BYTE OutOfFreq_Kor[] = {_O,_U,_T,0x00,_O,_F,0x00,_F,_R,_E,_Q,_U,_E,_N,_C,_Y};


code BYTE * code OutOfFreq[] = {
	OutOfFreq_Eng,
    	OutOfFreq_Kor
};

code BYTE OutOfFreq_Sizeof[] = {
	sizeof(OutOfFreq_Eng),
	sizeof(OutOfFreq_Kor)
};

/////////////////////////////////////////////////////////////////////
//	INPUT SOURCE
/////////////////////////////////////////////////////////////////////
code BYTE InputSource_Eng[] = {_I,_N,_P,_U,_T,0x00,_S,_O,_U,_R,_C,_E};
code BYTE * code InputSource[] = {
	InputSource_Eng
};
code BYTE InputSource_Sizeof[] = {
	sizeof(InputSource_Eng)
};

/////////////////////////////////////////////////////////////////////
//	DIGITAL
/////////////////////////////////////////////////////////////////////
code BYTE Digital_Eng[] = {_D,_I,_G,_I,_T,_A,_L};
code BYTE * code Digital[] = {
	Digital_Eng
};
code BYTE Digital_Sizeof[] = {
	sizeof(Digital_Eng)
};

/*
/////////////////////////////////////////////////////////////////////
//	CH
/////////////////////////////////////////////////////////////////////
code BYTE Ch2_Eng[] = {0,_C,0,_H};
code BYTE * code Chdot2[] = {
	Ch2_Eng
};
code BYTE Chdot2_Sizeof[] = {
	sizeof(Ch_Eng)
};
*/

/////////////////////////////////////////////////////////////////////
//	DEL
/////////////////////////////////////////////////////////////////////
code BYTE Del_Eng[] = {_D,_E,_L};
code BYTE * code Del[] = {
	Del_Eng
};
code BYTE Del_Sizeof[] = {
	sizeof(Del_Eng)
};

/////////////////////////////////////////////////////////////////////
//	Hz
/////////////////////////////////////////////////////////////////////
code BYTE Hz_Eng[] = {_H,_z};
code BYTE * code Hz[] = {
	Hz_Eng
};
code BYTE Hz_Sizeof[] = {
	sizeof(Hz_Eng)
};

/////////////////////////////////////////////////////////////////////
//	Hfreq:
/////////////////////////////////////////////////////////////////////
code BYTE Hfreq_Eng[] = {_H,_f,_r,_e,_q};

code BYTE * code Hfreq[] = {
	Hfreq_Eng
};
code BYTE Hfreq_Sizeof[] = {
	sizeof(Hfreq_Eng)
};

/////////////////////////////////////////////////////////////////////
//	Vfreq:
/////////////////////////////////////////////////////////////////////
code BYTE Vfreq_Eng[] = {_V,_f,_r,_e,_q};

code BYTE * code Vfreq[] = {
	Vfreq_Eng
};
code BYTE Vfreq_Sizeof[] = {
	sizeof(Vfreq_Eng)
};

//***************************************************************************************************************
//#endif
//***************************************************************************************************************
//#################################################
#endif	//#################################################
//#################################################