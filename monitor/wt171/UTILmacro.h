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
/////////////////////////////////////////////////
//	Util Macro!
//
/////////////////////////////////////////////////
#define		NOP		_nop_()
#define		NOPx6	{		\
					NOP;	\
					NOP;	\
					NOP;	\
					NOP;	\
					NOP;	\
					NOP;	\
					}

#define		NOPx10	{	\
					NOP;	\
					NOP;	\
					NOP;	\
					NOP;	\
					NOP;	\
					NOP;	\
					NOP;	\
					NOP;	\
					NOP;	\
					NOP;	\
					}	

#define 	BIN_TO_BYTE(b7,b6,b5,b4,b3,b2,b1,b0) ((b7 << 7)+(b6 << 6)+(b5 << 5)+(b4 << 4)+(b3 << 3)+(b2 << 2)+(b1 << 1)+b0)
#define		Bit7th	0x80
#define		Bit6th	0x40
#define		Bit5th	0x20
#define		Bit4th	0x10
#define		Bit3rd	0x08
#define		Bit2nd	0x04
#define		Bit1st	0x02
#define		Bit0ze	0x01

/*

#endif
*/

//0x9C->8비트, 0x9D를 클리어하기 위해 writescaler를 하게 되면 여러 define문이 
//따라와서 편의상 wordwritescaler를 하게 됨.
#if 0	// PIP background를 이용
#define		MUTEON		
{	\
	void WordWriteScaler(BYTE address, WORD Recdata);\
	void BitWriteScaler(BYTE address, BYTE BitArry, BYTE Recdata);\
	void idelay5m(BYTE time);\
	idelay5m(60);\
	WordWriteScaler(0xB8,0x1);\
	WordWriteScaler(0xBA,0x7FF);\
	WordWriteScaler(0xBC,0x1);\
	WordWriteScaler(0xBE,0x7FF);\
	BitWriteScaler(0x8E,0x04,1);	\
	BitWriteScaler(0x9A,0x40,0);	\
	BitWriteScaler(0x9A,0x80,1);	\
	WordWriteScaler(0x9C,0x00);\
}


#define		MUTEOFF		
{								\
	void BitWriteScaler(BYTE address, BYTE BitArry, BYTE Recdata);\
	BitWriteScaler(0x9A,0x80,0);	\
}
					
#else	//2003-08-28	//main background를 이용
#define MUTEON WriteScaler(0x50,BIN_TO_BYTE(PanelDataSwap,PanelDualData,0,0,0,1,1,1))
#define MUTEOFF WriteScaler(0x50,BIN_TO_BYTE(PanelDataSwap,PanelDualData,0,0,0,0,1,1))
#endif	

	
#define PIPMuteOn		BitWriteScaler(0x8E,0x04,0);	//PIP display disable
#define PIPMuteOff 	BitWriteScaler(0x8E,0x04,1);	//PIP display eable

#define	OSDstart	{\
					_SCALER_CS_LOW;\
					DelayNOP20();\
					}

#define	OSDstop		{\
					DelayNOP20();\
					_SCALER_CS_HIGH;\
					}
					



					
#define		Linesync	0
#define		Frame		1
#define		FREERUN		3
#define		FrameSync	4

/*
FREENRUN:	0x2F번지 셋팅
			DCLK 셋팅
*/
#define		FreeRun	{										\
	void BitWriteScaler(BYTE address, BYTE BitArry, BYTE Recdata);	\
	BitWriteScaler(0x2F,0x08|0x10,0);			\
}
						
						
#define		ModeTrigger	{										\
			extern	WORD	idata NoHSYNC_chattering;					\
			extern	WORD	idata NoVSYNC_chattering;					\
			extern	WORD	BeforeHfreq;						\
			extern	WORD	BeforeHfreq;						\
			extern	bit		NoExistHfreq;						\
			extern	bit		NoExistVfreq;						\
			extern	WORD	SYNC_chattering;					\
			NoExistHfreq = 0;									\
			NoExistVfreq = 0;									\
			BeforeHfreq = 0xFFFF;								\
			BeforeHfreq = 0xFFFF;								\
			NoHSYNC_chattering = 0;								\
			NoVSYNC_chattering = 0;								\
			SYNC_chattering=0;									\
			}




#define	RGBMODE	(0||1||2||3)
#define DVIMODE (4||5||6||7)
#define	COMPOSITEMODE (8||9||10||11)
#define S_VIDEOMODE (12||13||14||15)
#define TUNERMODE (16||17||18||19)
#define PIPMODE (20||21||22||23||24||25||26||27||28||29||\
		30||31||32||33||34||35||36||37||38||39||\
		40||41||42||43||44||45||46||47||48||49||\
		50||51||52||53||54||55||56||57||58||59||\
		60||61||62||63||64||65||66||67)
