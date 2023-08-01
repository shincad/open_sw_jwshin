
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

#define	OSD_REDBG	0x40			//%01000000
#define	OSD_GREENBG	0x20			//%00100000
#define	OSD_BLUEBG	0x10			//%00010000
#define	OSD_WHITEBG	OSD_REDBG+OSD_GREENBG+OSD_BLUEBG	//0x70

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