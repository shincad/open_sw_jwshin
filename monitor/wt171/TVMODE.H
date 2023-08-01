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

   2003-01-10 2:39¿ÀÈÄ  JDHAN           Modified for Monitor-TV
****************************************************************************/


#define	NTSC_AIR	0x00
#define	NTSC_CATV	0x01


#define	PAL_I		0x00
#define	PAL_BG		0x01
#define	PAL_DK		0x02

#define	SEC_BG		0x03
#define	SEC_DK		0x04
#define	SEC_L		0x05


/*
#ifndef BtcBoard_Option
#if	defined(USE_NTSCtuner)
#define	NTSC_AIRTVchannelEepromStartAddress	0x200
#define	NTSC_CATVchannelEepromStartAddress	0x246
#elif	defined(USE_PALSECAMtuner)
#define	PAL_ITVchannelEepromStartAddress	0x200
#define	PAL_BGTVchannelEepromStartAddress	0x23F
#define	PAL_DKTVchannelEepromStartAddress	0x2AA
#define	SEC_BGTVchannelEepromStartAddress	0x30F
#define	SEC_DKTVchannelEepromStartAddress	0x37A
#define	SEC_LTVchannelEepromStartAddress	0x3DF
#endif
#endif
*/