#ifndef	_RAM_H_
#define _RAM_H_

#include "OSD.H"

typedef struct
	{
	unsigned char Menu; // 1: normal,2:factroy
	unsigned char Page;
	unsigned char Level;
	unsigned char Ptr;
	unsigned char Op;
	}CONTROL_DEF;

extern unsigned char bdata flag1;
extern bit NoSyncFlag;
extern bit ForceToBack;  
extern bit ChangeKey; 	
extern bit VideoMute; 	
extern bit MessageShow;	
extern bit DecoderICEn;	
extern bit NewMode;			
extern bit GTmodeEn;	

extern unsigned char bdata flag2;
extern bit Abort;		
extern bit PowerDown;	
extern bit KeyLock;
extern bit OsdEnable;		
extern bit FastMuteEnable;
extern bit Interlance;	
extern bit SaveDDC1;
extern bit SaveDDC0;	

extern unsigned char bdata VideoFlag;
extern bit VideoIntLance;
extern bit Video_60Hz;
extern bit VideoUnlock;
extern bit ColorDetected;

extern bit MonoVideo;
extern bit BlueScreen;
extern bit VideoOK;
extern bit BypassSOG;
extern bit EndMute;
extern bit NonFullScreen;
extern bit BackLightTimerEn;
//extern bit KeyRepeat;
extern bit LightEn;
extern bit ScalerMode;
extern bit NoSigTogg;						// +jwshin 051101

extern unsigned char bdata StatusFlag;
extern bit PowerStatus;
extern bit BurnInMode;
extern bit FactMode;
extern bit OsdLock;
extern bit AudioMute;
extern bit AutoSetting;
extern bit TextMode;
extern bit EconomyMode;

extern idata unsigned short	NoSigTimer;			// +jwshin 051101 Nosignal timer Value added.	
extern idata unsigned char 	T0_INT_CNT;
extern idata unsigned short	OsdTimer;
extern idata unsigned char	LocalTimer;
extern idata unsigned short	PowerTimer;
extern idata unsigned short	RepeatTimer;
extern idata unsigned char  DDCTimer;
extern idata unsigned char  SaveTimer;
extern idata unsigned char	VideoTimer;
extern idata unsigned char  BurnInTimer;
extern idata unsigned char  MuteTimer;
extern idata unsigned char	T0_10ms_Cnt;
extern idata unsigned char	T0_1ms_Cnt;
extern xdata unsigned long	BackLightTimer;
extern idata unsigned char	KeyRepeatCnt;


extern xdata unsigned char	DVI_Clock;		// +jwshin 061013
extern idata unsigned short	H_SYNC;
extern idata unsigned short	V_SYNC;
extern idata unsigned short	H_SYNC_Temp;
extern idata unsigned short	V_SYNC_Temp;
extern idata unsigned short	VTotal;
extern idata unsigned short	H_Act;
extern idata unsigned char  ResolutionPtr;
extern idata unsigned char  ChangeMode;
extern idata unsigned char	HV_Pol;
extern idata unsigned char	HV_Pol_Temp;
extern idata unsigned char	ModePoint;
extern idata unsigned char	KeyBuffer;
extern idata unsigned char	PrevKey;
extern idata unsigned char  FuncPtr;
extern idata unsigned char  SavePointer;
extern idata unsigned char 	RegPage;		
extern idata unsigned char  OutOfRange;
extern idata unsigned char	SyncMode;
extern idata unsigned char  DigitalPtr;
extern idata unsigned char 	Timer1;
extern idata unsigned char 	Timer2;
extern idata unsigned char 	Timer3;
extern idata unsigned char rwbuf;
extern idata unsigned short abuf;
extern idata unsigned char dbuf;

extern xdata unsigned short	FuncBuf[42]; //Jason Choi
extern xdata unsigned short Hresolution;
extern xdata unsigned short Vresolution;
extern xdata unsigned short FuncMax;
extern xdata unsigned short FuncMin;
extern xdata unsigned short ClockBase;
extern xdata unsigned short HPositionBase;
extern xdata unsigned char BackPtr;
extern xdata unsigned char TvMode;
extern xdata unsigned char VideoSourcePtr;
extern xdata unsigned char TempPtr;
extern xdata unsigned char MaxItem;
extern xdata unsigned char BackItem;
extern xdata unsigned char UserModePtr;
extern xdata unsigned char  BurnInPattern;
extern idata unsigned char 	TempPhase;
extern xdata unsigned char SCRev;
extern CONTROL_DEF xdata MenuPtr;
extern xdata unsigned char UserModeRefReso;
extern xdata unsigned char SCFactor;
extern xdata unsigned char VideoStandard;

extern xdata unsigned char ChBuffer;
extern xdata unsigned char TV_Min;
extern xdata unsigned char TV_Max;
extern xdata unsigned char TV_Total;
extern xdata unsigned char CATV_Min;
extern xdata unsigned char CATV_Max;
extern xdata unsigned char CATV_Total;
extern xdata unsigned char PRBuffer;//Program NO. buffer
extern xdata unsigned char PR_ChBuffer;//Program NO.CH. buffer 
extern xdata unsigned char PR_TV_Max;
extern xdata unsigned char PR_CATV_Max;
extern xdata unsigned char ChSystem; 
extern xdata unsigned char ChNumCnt; 
extern xdata unsigned char CmdTxPtr1;
extern xdata unsigned char CmdTxPtr2;
extern xdata unsigned char CmdRxPtr1;
extern xdata unsigned char CmdRxPtr2;
extern xdata unsigned char	CmdTxBuffer[128];
extern xdata unsigned char	CmdRxBuffer[128];

//for CCD
extern xdata unsigned char  VChip_Data[2];
extern xdata unsigned short Non_VChip_Count;
extern xdata unsigned char  VChip_Block;
extern xdata unsigned char  VChip_Password[4];
extern xdata unsigned char  VChip_ChangePassword[4];
extern xdata unsigned char  VChip_Confirm;
extern xdata unsigned char  VChip_RatingSelected;
extern xdata unsigned char  VChip_AcquisitionMPAA;
	//0x01://MPAA_G
	//0x02://MPAA_PG
	//0x03://MPAA_PG13
	//0x04://MPAA_R
	//0x05://MPAA_NC17
	//0x06://MPAA_X
	//0x07://MPAA_NR
extern xdata unsigned char  VChip_AcquisitionTV;
	//0x01://TV_Y
	//0x02://TV_Y7
	//0x03://TV_G
	//0x04://TV_PG
	//0x05://TV_14
	//0x06://TV_MA
extern xdata unsigned char  VChip_AcquisitionTVFVVSLD;
	//BIT_1://TV_Y7_FV
	//BIT_2://TV_V
	//BIT_3://TV_S
	//BIT_4://TV_L
	//BIT_5://TV_D
extern xdata unsigned char  ResetPasswordBuff;
extern xdata unsigned char  ResetData[7];
extern xdata unsigned short VChip_Timer;
extern xdata unsigned short DevNum;
//extern xdata unsigned char  Bass;
//extern xdata unsigned char  Treble;
extern xdata unsigned char  RatingMAPP;
	//0x01://MPAA_G
	//0x02://MPAA_PG
	//0x03://MPAA_PG13
	//0x04://MPAA_R
	//0x05://MPAA_NC17
	//0x06://MPAA_X
	//0x07://MPAA_NR
extern xdata unsigned char  RatingTV;
	//0x01://TV_Y
	//0x02://TV_Y7
	//0x03//TV_Y7_FV
	//0x04://TV_G
	//0x05://TV_PG
	//0x06://TV_14
	//0x07://TV_MA
extern xdata unsigned char  RatingTVFVVSLD;
	//BIT_1://
	//BIT_2://TV_V
	//BIT_3://TV_S
	//BIT_4://TV_L
	//BIT_5://TV_D

extern xdata unsigned short IR_Timer;	
extern xdata unsigned char IR_Status;
extern xdata unsigned char cntIR_Data;
extern xdata unsigned char IR_Status;
extern xdata unsigned long IR_Data;
extern xdata unsigned long IR_Data_buffer;
extern xdata unsigned char IR_Pre_KeyBuffer;
extern xdata unsigned char IR_KeyTemp;
extern xdata unsigned char IR_WaitTimer;
extern xdata unsigned char IR_RepeatTimer;
extern xdata unsigned short IR_Number;
extern xdata unsigned char IR_Number_cnt;	

extern bit bIR_Change;
extern bit bIR_Active;
extern bit bIR_flag;


extern bit Violence;
extern bit Sexual;
extern bit Lang;
extern bit Dialogue;
extern bit CaptionFlag;



extern bit VPXinit;
extern bit VideoFlagTW;
extern bit SyncFlag;
extern bit VideoCheck;
extern bit AirCableFlag;
extern bit ChAdd_Del;
extern bit OSDZoomFlag;
extern bit TVSignalNormalFlag;
extern bit VideoTest;

extern bit MonTogg;
extern bit RGBStatus;
#endif
