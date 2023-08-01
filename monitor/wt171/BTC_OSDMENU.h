//--------------------------------------------------------------------------------------------------
typedef enum		//2003-04-16 made by thkim
{
	  MENU_DISPLAY		//0
	 ,MENU_RGB		//1
	 ,MENU_OSD		//2
	 ,MENU_PIP		//3
	 ,MENU_TOOLS		//4
	 ,MENU_SOUND		//5	// smpark 20030708
	 
	 ,menu_brightness	//6
	 ,menu_contrast		//7 
	 ,menu_sharpness	//8 
	 ,menu_phase		//9 
	 ,menu_clock		//10
	 ,menu_Hposition	//11
	 ,menu_Vposition	//12
                                  
	 ,menu_white_balance	//13
	 ,menu_Rgain		//14
	 ,menu_Ggain		//15
	 ,menu_Bgain		//16
	 ,menu_color_temperture	//17
	                          
	 ,menu_language		//18
	 ,menu_osd_Hposition	//19
	 ,menu_osd_Vposition	//20
	 ,menu_osd_time		//21
	 ,menu_osd_transparency	//22
	                          
	 ,menu_pip_enable	//23
	 ,menu_pip_source	//24
	 ,menu_pip_size		//25
	 ,menu_pip_Hposition	//26
	 ,menu_pip_Vposition	//27
	 ,menu_pip_AspectRatio	//28	//2003-07-31 menu added for "pip aspect 16:9"
	 ,menu_pip_blend		//2003-08-19
		                          
	 ,menu_auto_adjust	//29
	 ,menu_factory_default	//30
	 ,menu_dosmode			//2003-08-26
	 #ifdef	Wide4_3Aspect
	 ,menu_AspectRatio		//2003-12-30
	 #endif
	                          
	 					 // Added by smpark 2003.07.08
     ,menu_Treble		//31
     ,menu_Bass		//32
     ,menu_Loudness		//33
     ,menu_SSC		//34
//     	,menu_MTS

	,MaxMenuNum		
}PcMenuCode;

	 
#define TopMenuStart		MENU_DISPLAY	// 0
#define TopMenuEnd			MENU_SOUND	// MENU_TOOLS	//smpark 20030714

#define	DisplayMenuStart	menu_brightness
#define	DisplayMenuEnd		menu_Vposition

#define	RgbMenuStart		menu_white_balance
#define	RgbMenuEnd			menu_color_temperture

#define	OsdMenuStart		menu_language
#define	OsdMenuEnd			menu_osd_transparency

#define	PipMenuStart		menu_pip_enable
//#define	PipMenuEnd		menu_pip_AspectRatio
#define	PipMenuEnd			menu_pip_blend

#define	ToolsMenuStart		menu_auto_adjust
	#ifdef	Wide4_3Aspect
#define	ToolsMenuEnd		menu_AspectRatio	
	#else
#define	ToolsMenuEnd		menu_dosmode	//menu_factory_default
	#endif

// Added by smpark 20030708
#define	SoundMenuStart		menu_Treble
#define	SoundMenuEnd		menu_SSC//	menu_MTS	//smpark 20030716

typedef enum		
{
	  TVMENU_PICTURE	//0
	 ,TVMENU_SETUP		//1
	 ,TVMENU_TOOLS		//2
	 ,TVMENU_SOUND		//3	smpark 20030715
	 
	 ,tvmenu_brightness	//4							
	 ,tvmenu_contrast  	//5							
	 ,tvmenu_sharpness 	//6							
	 ,tvmenu_color     	//7							
	 ,tvmenu_tint      	//8							
	 ,tvmenu_smart_picture_control  //17	//2003-08-18 메뉴위치 변경
	 
	 ,tvmenu_country	//9
	 ,tvmenu_auto_setup     //10
	 ,tvmenu_channel_edit   //11
	#if defined (USE_NTSCtuner)
	 ,tvmenu_antena_input   //12
	#endif
	 ,tvmenu_finetune      //13
	 
	 ,tvmenu_lang //tvmenu_ttx			//14
	 ,tvmenu_blue_screen            //15
	 ,tvmenu_screen_mode            //16
	 //,tvmenu_smart_picture_control  //17
	 ,tvmenu_sleep			//18
	 //,tvmenu_aspect			//19	//2003-08-02 added	//03-08-06 removed 
	#ifdef Ccd_Vchip		//2003-11-27
	 ,tvmenu_Ccd
	 ,tvmenu_Vchip
	#endif

	   // Added by smpark 2003.07.15
     	 ,tvmenu_Treble
     	 ,tvmenu_Bass
     	 ,tvmenu_Loudness
     	 ,tvmenu_SSC
//     	 ,tvmenu_MTS

	 #ifdef TempOsdMenu
	 ,tvmenu_TempOsd	//2003-10-29
	 ,tvmenu_OsdBlend	//2003-10-30
	 #endif

	 ,MaxTvMenuNum			//18
}TvMenuCode;


#define TvTopMenuStart		TVMENU_PICTURE
#define TvTopMenuEnd		TVMENU_SOUND		// smpark 20030715
	 
#define TvPictureStart		tvmenu_brightness
#define TvPictureEnd		tvmenu_smart_picture_control	//2003-08-18
        
#define TvSetupStart		tvmenu_country
#define TvSetupEnd			tvmenu_finetune

        
#define TvToolsStart		tvmenu_lang ///tvmenu_ttx
	#ifdef Ccd_Vchip
#define TvToolsEnd			tvmenu_Vchip
	#else
#define TvToolsEnd			tvmenu_sleep
	#endif
	 
#define TvSoundStart		tvmenu_Treble		// smpark 20030715
	#ifdef TempOsdMenu
#define TvSoundEnd			tvmenu_OsdBlend
	#else
#define TvSoundEnd			tvmenu_SSC	//tvmenu_MTS	 		// smpark 20030715
	#endif
	 
//-------------------------------------------------------------------------------------

typedef enum
{
	 warm
	,standard
	,cool
	,temp_user
	,MaxCtempNum
}ColorTempnum;

#define CT_WARM		warm		//6500K
#define	CT_STANDARD	standard	//8000K
#define	CT_COOL		cool		//9300K
#define CT_USER		temp_user		//2003-08-07 added


#ifdef Ccd_Vchip
typedef enum			//2003-11-27
{
	ccd_caption,
	ccd_mode,
	ccd_channel,
	ccd_field,
	ccd_display
}Ccd_menu;

typedef enum
{
	vchip_MotionPictureOnOff,
	vchip_MotionPictureRating,
	vchip_ParentalGuideOnOff,
	vchip_ParentalGuideRating,
	vchip_ChangeCode
}VchipMenu;

typedef enum
{
	vchip_NoRating,
	vchip_G,
	vchip_PG,
	vchip_PG13,
	vchip_R,
	vchip_NC17,
	vchip_X
}VchipSubMenu1;

typedef enum
{
	vchip_tvY,
	vchip_tvY7,
	vchip_tvG,
	vchip_tvPG,
	vchip_tv14,
	vchip_tvMA
}VchipSubMenu2;
#endif

#if defined (USE_NTSCtuner)
typedef enum
{
	 TV_USA
	,TV_KOREA
	,TV_JAPAN
	,MaxCountryNum
}Country_Ntsc;
/*
#elif defined	(USE_PALSECAMtuner)
typedef enum
{
	 English
	,France
	,German	
	,Italia
	,Netherlands
	,Russia
	,China
	,MaxCountryNum
}Country_Pal;
*/
#endif



#if defined (USE_NTSCtuner)
typedef enum
{
	 English
	,Korea
	,Japan
	,MaxLangNum
}Language_Ntsc;
#elif defined	(USE_PALSECAMtuner)
typedef enum
{
	 English
	//,France
	//,German	
	//,Italia
	//,Netherlands
	//,Russia
	,China
	,MaxLangNum
}Language_Pal;
#endif

typedef enum
{
	 OffFlag
	,OnFlag
	,MaxOnoffNum
}OnOFF;

typedef enum
{
	 SourceComposite
	,SourceSvideo
	,SourceTuner
#if defined(USE_SCART)	
	,SourceScart
#endif
	,MaxPipNum
}VideoSource;

typedef enum
{
	 SizeLarge
	,SizeMiddle
	,SizeSmall
	,MaxSizeNum
}SizeEnum;

typedef enum	//2003-07-31
{
	 aspect4_3	//0
	,aspect16_9	//1
	,aspect_full	//2	//tv에서
	,MaxAspectNum
}AspectEnum;

typedef enum
{
	 TopPos
	,MidPos
	,BotPos
	,MaxPipVPosNum
}PipVPostionEnum;

typedef enum
{
	 LeftPos
	,CenterPos
	,RightPos
	,MaxPipHPosNum
}PipHPostionEnum;

#define	TopPosition	TopPos
#define	BottomPosition	BotPos
#define	LeftPosition	LeftPos
#define	RightPosition	RightPos


typedef enum
{

	SPCNormal
	,SPCDynamic
	,SPCCinema
	,SPCUser
	,MaxSmartNum
}SmartEnum;

#define SPC_NORMAL 	SPCNormal
#define SPC_DYNAMIC 	SPCDynamic
#define SPC_CINEMA 	SPCCinema
#define SPC_USER 	SPCUser

// smpark 20030715
typedef enum
{
	 SSCNormal
	,SSCMusic
	,SSCCinema
	,SSCNews
	,SSCUser
	,MaxSSCNum
}SSCEnum;

#define SSC_NORMAL		SSCNorml
#define	SSC_MUSIC		SSCMusic
#define	SSC_CINEMA		SSCCinema
#define SSC_NEWS			SSCNews
#define  SSC_USER		SSCUser

// smpark 20030721
typedef enum
{
	 MTSMono
	,MTSStereo
	,MTSBilingual
	,MaxMTSNum
}MTSEnum;

//#define	LoudNormal 0x00
//#define	LoudOn 0x01

#define MTS_MONO			MTSMono
#define	MTS_STEREO		MTSStereo
#define	MTS_BILINGUAL	MTSBilingual

typedef enum
{
	 ScrNormal
	,ScrWide
	,MaxScrModeNum
}ScrModeEnum;


typedef enum
{
	 AtnAir
	,AtnCable
	,MaxAtnSelNum
}AtnSelEnum;


typedef enum
{					// ArrangeFunctionTable() 에서...
/*0*/	 Rgb_mode			//(0<=xEEPROMBuffer[MainSubInputSource]&&xEEPROMBuffer[MainSubInputSource]<=3)   CurrentFunction= 0;//RGB      
/*1*/	,Dvi_mode                       //(4<=xEEPROMBuffer[MainSubInputSource]&&xEEPROMBuffer[MainSubInputSource]<=7)   CurrentFunction= 1;//DVI      
/*2*/	,Composite_mode                 //(8<=xEEPROMBuffer[MainSubInputSource]&&xEEPROMBuffer[MainSubInputSource]<=11)  CurrentFunction= 2;//COMPOSITE
/*3*/	,Svideo_mode                    //(12<=xEEPROMBuffer[MainSubInputSource]&&xEEPROMBuffer[MainSubInputSource]<=15) CurrentFunction= 3;//S-VIDEO 
/*4*/	,Tuner_mode                     //(16<=xEEPROMBuffer[MainSubInputSource]&&xEEPROMBuffer[MainSubInputSource]<=19) CurrentFunction= 4;//TUNER
	   
/*5*/	,PipRnC_mode                    //(20<=xEEPROMBuffer[MainSubInputSource]&&xEEPROMBuffer[MainSubInputSource]<=27) CurrentFunction= 5;//PIP R+C 
/*6*/	,PipRnS_mode                    //(28<=xEEPROMBuffer[MainSubInputSource]&&xEEPROMBuffer[MainSubInputSource]<=35) CurrentFunction= 6;//PIP R+S 
/*7*/	,PipRnT_mode                    //(52<=xEEPROMBuffer[MainSubInputSource]&&xEEPROMBuffer[MainSubInputSource]<=59) CurrentFunction= 7;//PIP R+T 
/*8*/	,PipDnC_mode                    //(36<=xEEPROMBuffer[MainSubInputSource]&&xEEPROMBuffer[MainSubInputSource]<=43) CurrentFunction= 8;//PIP D+C 
/*9*/	,PipDnS_mode                    //(44<=xEEPROMBuffer[MainSubInputSource]&&xEEPROMBuffer[MainSubInputSource]<=51) CurrentFunction= 9;//PIP D+S 
/*10*/	,PipDnT_mode                    //(60<=xEEPROMBuffer[MainSubInputSource]&&xEEPROMBuffer[MainSubInputSource]<=67) CurrentFunction= 10;//PIP D+T
#if defined(USE_SCART)	
/*11*/	,Scart_mode			//(68<=xEEPROMBuffer[MainSubInputSource]&&xEEPROMBuffer[MainSubInputSource]<=71) CurrentFunction= 11;//SCART  
/*12*/	,PipRnSC_mode 			//(72<=xEEPROMBuffer[MainSubInputSource]&&xEEPROMBuffer[MainSubInputSource]<=79) CurrentFunction= 12;//PIP R+SC
/*13*/	,PipDnSC_mode 			//(80<=xEEPROMBuffer[MainSubInputSource]&&xEEPROMBuffer[MainSubInputSource]<=87) CurrentFunction= 13;//PIP D+SC
#endif
	,MaxCurrentFunctionNum
}CurrentFunctionEnum;

#if defined	(USE_PALSECAMtuner)
typedef enum
{
	_A,		//0
	_B,		//1
	_C,		//2
	_D,		//3
	_E,		//4
	_F,		//5
	_G,		//6
	_H,		//7
	_I,		//8
	_J,		//9
	_K,		//10
	_L,		//11
	_M,		//12
	_N,		//13
	_O,		//14
	_P,		//15
	_Q,		//16
	_R,		//17
	_S,		//18
	_T,		//19
	_U,		//20
	_V,		//21
	_W,		//22
	_X,		//23
	_Y,		//24
	_Z,		//25
	_plus,	//26
	_minus,	//27
	_dot,	//28
	_space,	//29
	_0,		//30
	_1,		//31
	_2,		//32
	_3,		//33
	_4,		//34
	_5,		//35
	_6,		//36
	_7,		//37
	_8,		//38
	_9, 		//39
	MaxEditCharNum
}EditCharEnum;

#define ChEditChar1Start	0//_A
#define ChEditChar1End		19//_T
#define ChEditChar2Start	20//_U
#define ChEditChar2End		39//_9
#endif


//-------------------------------------------------------------------------------------
#define	WIN_SIZE	30

#ifdef TempOsdMenu
#define TempOsdTotal	15
#endif
//-------------------------------------------------------------------------------------
