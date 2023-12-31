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

#include	"TopHeader.h"
#include	"eepromadr.h"
#include	"TVMODE.h"

code BYTE	EEPROM_DftVal[] = //default value
{
/*0x00*/ MyboardID//EEPROMVERSION
/*0x01*/,0x55//POWERID

#if	defined(Always_RGBFirst)
/*0x02*/,0//MainSubInputSource
#elif defined(Always_FMRGBFirst)
/*0x02*/,2//MainSubInputSource
#elif defined(Always_VIDEOFirst)
/*0x02*/,8//MainSubInputSource
#elif defined(Always_FMVIDEOFirst)
/*0x02*/,10//MainSubInputSource
#elif defined(Always_DVIFirst)
/*0x02*/,4//MainSubInputSource
#elif defined(Always_FMDVIFirst)
/*0x02*/,6//MainSubInputSource
#elif defined(Always_RGBCOMPOSITEPIP)
/*0x02*/,20//MainSubInputSource
#elif defined(Always_TVFirst)
/*0x02*/,16//MainSubInputSource
#elif defined(Always_FMTVFirst)
/*0x02*/,18//MainSubInputSource
#else
/*0x02*/,2//MainSubInputSource
#endif

/*0x03*/,10	//0x0c			//OSDOFFTIME

#if defined(USE_NTSCtuner)
/*0x04*/,0x00			//LANGUAGE	//default "english"
#else
/*0x04*/,0x01			//LANGUAGE	//default "china"
#endif

/*0x05*/,ANALOGBRT_max/2	//ANALOGBRT
/*0x06*/,0x3f			//COMPOSITEBRT
/*0x07*/,ANALOGCONT_max/2	//ANALOGCONT
/*0x08*/,50//30			//COMPOSITECONT
/*0x09*/,0x01			//COLORTEMP.
/*0x0a*/,ADCREDGAIN_max/2	//33//0x20		//ADCREDGAIN
/*0x0b*/,ADCREDGAIN_max/2	//33//0x20		//ADCGREENGAIN
/*0x0c*/,ADCREDGAIN_max/2	//33//0x20		//ADCBLUEGAIN
/*0x0d*/,OSDHpos_max/2+1	//OSD H_POSITION
/*0x0e*/,OSDVpos_max/2		//OSD V_POSITION
/*0x0f*/,0x01			//COMPOSITESHARP
/*0x10*/,72			//COMPOSITECOLOR
/*0x11*/,50			//COMPOSITETINT
/*0x12*/,0x20			//VOLUME
/*0x13*/,0x11			//PIPPOSITION
/*0x14*/,0x00			//PIPSIZE_buf
/*0x15*/,0x00			//PIPBLEND
/*0x16*/,0x00			//PIPEN_SOURCE
/*0x17*/,0			//WideModeFlag_adr
/*0x18*/,(TvFineTuneValue_max/2)//NTSC_AIR fine
/*0x19*/,0	//Smart Sound
/*0x1a*/,0 	//MTS	smpark 20030722
/*0x1b*/,50	//Bass
/*0x1c*/,50	//trable
/*0x1d*/,SOUND_LOUDNESS_max	//0x00	//50  //loudness

#if defined(USE_NTSCtuner)
		/*0x1e*/,0	//TVMODE,NTSC,PAL BG,PAL DK,SECAM BG,SECAM DK
#elif defined(USE_PALSECAMtuner)
		/*0x1e*/,2	//TVMODE,NTSC,PAL BG,PAL DK,SECAM BG,SECAM DK
#endif

/*0x1f*/,5	//Sharpness	
/*0x20*/,(WhiteBlcValue_max)/2	//WhiteBalance
/*0x21*/,3	//COMPOSITESHARP
/*0x22*/,0	//SmartPicCtr
/*0x23*/,0	//Sleep

#if defined(BtcBoard_Option) 

/*0x24*/,0	//CurrentChannel	 
/*0x25*/,0	//PreChannel
#if defined(USE_NTSCtuner)
		/*0x26*/,0	//SystemCountry Korea 0
#else
			#ifdef Russia_Freq
			/*0x26*/,1	//SystemCountry China
			#else
			/*0x26*/,0	//SystemCountry China
			#endif
#endif


#ifdef FrequncyTableType
		/*0x27*/,1	//Antena
#else
		/*0x27*/,0	//Antena
#endif

/*0x28*/,BTC_Version	//
/*0x29*/,0//BscrFlag
/*0x2a*/,0x02	//DisplayAspect//2003-08-02 // [high:pip, low:tv] (0->4:3, 1->16:9, 2->normal)
/*0x2b*/,1	//DosmodeFlag	//2003-08-26	// (0:640*400, 1:720*400)
/*0x2c*/,0	//Factory reset //2003-08-27
/*0x2d*/,2	//BackupMainSubInputSource //2003-10-21

///////////////////////////////////////////////////////////////
#ifdef TempOsdMenu
		/*0x2e*/,0	//임시 OSD메뉴 //2003-10-29
		/*0x2f*/,1	//임시 OSD메뉴 //2003-10-30
#endif

#if defined	(Ccd_Vchip)&&(TempOsdMenu)
		/*0x30*/,0	//ccd
		/*0x31*/,0	//vchip
		#ifdef Wide4_3Aspect
		/*0x32*/,0x00	//[0:Aspect Ratio]//2003-12-30
		#endif
#elif defined (Ccd_Vchip)&& !defined(TempOsdMenu)		
		/*0x2e*/,0	//ccd
		/*0x2f*/,0	//vchip
		#ifdef Wide4_3Aspect
		/*0x30*/,0x00	//[0:Aspect Ratio]//2003-12-30
		#endif
#elif !defined (Ccd_Vchip)&& defined(TempOsdMenu)
		#ifdef Wide4_3Aspect
		/*0x30*/,0x00	//[0:Aspect Ratio]//2003-12-30
		#endif
#elif !defined(Ccd_Vchip)&& !defined(TempOsdMenu)
		#ifdef Wide4_3Aspect
		/*0x2e*/,0x00	//[0:Aspect Ratio]//2003-12-30
		#endif
#endif

#endif
/////////////////////////////////////////////////////////////////
};




xdata BYTE	TotalEeprom=   sizeof(EEPROM_DftVal);

/*
#ifndef BtcBoard_Option
#if	defined(USE_NTSCtuner)
code WORD TvChannelEepromAdr[] = 
{	NTSC_AIRTVchannelEepromStartAddress,
	NTSC_CATVchannelEepromStartAddress
};
//#endif

#elif	defined(USE_PALSECAMtuner)
code WORD TvChannelEepromAdr[] = 
{	PAL_ITVchannelEepromStartAddress,
	PAL_BGTVchannelEepromStartAddress,
	PAL_DKTVchannelEepromStartAddress,
	SEC_BGTVchannelEepromStartAddress,
	SEC_DKTVchannelEepromStartAddress,
	SEC_LTVchannelEepromStartAddress
};
#endif
#endif
*/