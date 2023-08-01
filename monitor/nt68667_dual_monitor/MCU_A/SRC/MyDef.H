#ifndef _MyDef_H
#define  _MyDef_H

#include <stdio.h>
//#define BenQ_FACTORY				

#define BIT_0   0x01
#define BIT_1   0x02
#define BIT_2   0x04
#define BIT_3   0x08
#define BIT_4   0x10
#define BIT_5   0x20
#define BIT_6   0x40
#define BIT_7   0x80

#define TRUE    1
#define FALSE   0

#define HIGH    1
#define LOW     0

#define ON      1
#define OFF     0

#ifndef NULL
#define NULL    0
#endif

typedef union
{
    unsigned short w;
    unsigned char b[2];
}Union;


#define VERSION     0x00 //22": 0x10...0x1f
#define REVERSION   0x01 // version
#define RLS_VER_DATE "V0.01 2008-05-13"


//////////////////////////////
// M O D E L    N A M E
#define H190B8  0
#define H190C8  1
#define H190P8  2
#define H190S8  3
#define H190V8  4
#define H170A8  5
#define H170C8  6
#define H170P8  7
#define H170S8  8
#define H170V8  9
#define H220BW8 10
#define H220SW8 11
#define H220PW8 12

#define QS19    21
#define QS19W   22
#define QS22W   23
#define QS24W   24

#define QL19    31
#define QL19W   32
#define QL22W   33
#define QL24W   34

//===========[ PCB Define ]===========
#define PCBA80x67       0
#define PCBA56x57       1
#define PCBA_Q80x67     2
#define PCBA_Q50x50     3

//===========[ Scaler Define ]===========
#if ModelName==QS19 || ModelName==QS19W || ModelName==QS22W || ModelName==QS24W
#define NT68665             0
#define NT68670             0
#define NT68670B            0
#define NT68167             1
#define NT68667             0
#define DUAL_MODE           0
#define SCALAR_BOARD        PCBA_Q50x50
#define FE2P_LIB            ON
#define _INTERNAL_LDO_      1

#elif ModelName==QL19 || ModelName==QL19W || ModelName==QL22W || ModelName==QL24W
#define NT68665             0
#define NT68670             0
#define NT68670B            1
#define NT68167             0
#define NT68667             1
#define DUAL_MODE           1
#define SCALAR_BOARD        PCBA_Q80x67
#define FE2P_LIB            OFF				// +jwshin 111206     24C16 »ç¿ë..~!!!
#define _INTERNAL_LDO_      1

#define _SmartBright_				OFF			// +jwshin 111207
#endif


/*
#if ModelName==H170P8 || ModelName==H190P8 || ModelName==H220PW8
#define _SmartBright_   ON
#else
#define _SmartBright_   OFF
#endif
*/

#if DUAL_MODE
    #define _ENABLE_HDCP_ 1
    #define NOVATEK_HDCP_WRITER
    #define _SCDT_SOLUTION_
    #define _NONHDCP_SOLUTION_
#else
    #define _ENABLE_HDCP_ 0
#endif

#define _Enable_OD_ OFF					// +jwshin 110602
//#define _Enable_OD_   ON
//#define USE_GAMMA								// -jwshin 130307				LED Panel Color Balance¸¦ À§ÇØ...
//#define EDID_FROM_A_ONLY 1			// -jwshin 111209
//#define DEMO_HDCP_KEY 111
//#define NOVATEK_HDCP_WRITER


#define SCALER_VER ReadIIC560(PRODUCT_ID)
    #define NT68663_VER_F 0xC6
    #define NT68663_VER_G 0xD6
    #define NT68665_VER_E 0x17
    #define NT68665_VER_GJ 0x27

#define NUMBER_OF_USER_MODE 67//59//58 //44//64     //user mode (57 --- 99)
#define AMOUNT_OF_MODE NUMBER_OF_USER_MODE+10//100//50
//#define BEST_RESULT   26

#if ( AMOUNT_OF_MODE > 80 )
#error "TIMING BUFFER IS OVERFLOW"
#endif

//#define ModeButtom 4*AMOUNT_OF_MODE       //4*50
#define SYNC_STABLE_TIME 50     //500ms

#define SCALER_I2C_ADDR 0xB0
#define DDCCI_ADDR  0x6e    // for Utility Alignment command

//------------------ -jwshin 110425
/*
#define AUTO_KEY    0x03    //SW303 ADC2 1K
#define POWER_KEY   0x55    //SW301 ADC2 10K
#define MENU_KEY    0x30    //SW302 ADC1 1K
#define DownKey     0x01    //SW305 ADC1 10K
#define UpKey       0x02    //SW306 ADC0 1K
#define FUNC_KEY    0x10    //SW304 ADC0 10K
#define INPUT_KEY   0x40    //source
#define IGNORE_KEY  0x00
*/

//------------------- +jwshin 110425
/*
#define AUTO_KEY    1    
#define POWER_KEY   16    
#define MENU_KEY    2    
#define DownKey     48    
#define UpKey       32    
#define FUNC_KEY    0x10    
#define INPUT_KEY   0x40    
#define IGNORE_KEY  0x00
*/
//-------------------------------------  +jwshin 111207
#define AUTO_KEY    0x01    
#define POWER_KEY   0x10
#define MENU_KEY    0x02    
#define DownKey     0x30    
#define UpKey       0x20    

#define BUTTON_SEL_KEY_A		0x08	
#define BUTTON_SEL_KEY_B    0x09

#define FUNC_KEY		0x95//(AUTO_KEY|DownKey)
#define INPUT_KEY		0x91//(AUTO_KEY|UpKey)					// -jwshin 120313  Source º¯È¯ remark...
#define IGNORE_KEY	0x00


#define FactoryKey			(AUTO_KEY|DownKey)//(MENU_KEY|POWER_KEY)
#define DDCCiHotKey     0x93
#define QuickResetKey   0x97//(MENU_KEY|UpKey)
#define QuitBurninKey   0x96//(MENU_KEY|DownKey)
#define LF_KEY					0x92
#define LF_DEMO_KEY			0x94

//---------------------------------------------


/*
#define FUNC_KEY    0x10    
#define INPUT_KEY   0x40    
#define IGNORE_KEY  0x00


#define FactoryKey      (MENU_KEY|AUTO_KEY)
#define DDCCiHotKey     (DownKey|MENU_KEY)
#define QuickResetKey   (UpKey|FUNC_KEY)
#define QuitBurninKey   (MENU_KEY|AUTO_KEY)
#define LF_KEY      0x92
#define LF_DEMO_KEY 0x94
*/

#define KEY_STABLE_TIME  50      //50ms
#define KEY_HOLDING_TIME 100        //1 sec.
#define KEY_REPEATING_TIME 5//10        //0.1 sec.



//DVI
#define DVI_HV_MODE 0       //sync mode
#define DVI_DE_MODE 1       //DE mode

//#define DVImode HVmode
#define DVI_MODE DVI_DE_MODE

#define UART_TX_BUFFER_SIZE 16
#define UART_RX_BUFFER_SIZE 56
#define DDCCi_BUFFER_SIZE   40
#define FONT_BUFFER_SIZE    18


#define V_UPPER_BOUND 775 //800



//===========[ MCU Define ]===========
#define PBusProtocol        (NT68670 || NT68670B || NT68167)


#if NT68167
    #define CoreSpeed       0x03
    #define T0_Speed        3000
    #define _167_VERSION_B  1
    #define _167_VERSION_C  1
#elif NT68665
    #define CoreSpeed       0x36
#else
    #define CoreSpeed       0x24
#endif

//#define ANTI_ESD
//#define _RANGE_PCT_
#define CHECK_TIMER
//#define ADC_OFFSET_DOWN
//#define AUTO_OFFSET
//#define R640_TUNE // Dobule Sampling

#define PHILIPS_RESOLUTION_INFORMATION

//#define TCO_Test_EnableGain   //
//#define TCO_Test_6500K_USER   //
//#define TCO_Test_6500K_GAMMA  //

#if ModelName!=H190B8
//#define ENABLE_TD_
#endif

#define ActDisplay1680x1050 0
#define ActDisplay1680x1024 1
//#define bDisplaySize ActDisplay1680x1050
#define bDisplaySize ActDisplay1680x1024			// +jwshin 110419

#define GREEN_POWER
#define GREEN_POWER_BRIGHTNESS 50//70
#define BEST_MSG_TIME (10 * 4)//0.25ms x 12 = 3 Sec.
#define PURE_BLACK_LEVEL 10
#define PURE_BLACK_FRAME_NUM 200


#if NT68665
    #define SYNC_INT_DISABLE()  {WriteIIC560(SYNC_INT_EN1,0x00); \
                                WriteIIC560(SYNC_INT_EN2,0x00);}
    #define SYNC_INT_ENABLE()   {WriteIIC560(SYNC_INT_EN1,0x3c); \
                                WriteIIC560(SYNC_INT_EN2,0x03);}
    #define MCU_INT_ENABLE()    {INTEXT_FLG = INTE0; \
                                INTEXT_EN = INTE0;}
    #define MCU_INT_DISABLE()   {INTEXT_EN = 0;}
#endif
                                                        
#if (NT68670 || NT68670B || NT68667)
    #define SYNC_INT_DISABLE()      {WriteIIC560(SYNC_INT_EN1,0x80); \
                                WriteIIC560(SYNC_INT_EN2,0x00);}
    #define SYNC_INT_ENABLE()       {WriteIIC560(SYNC_INT_EN1,0xbc); \
                                WriteIIC560(SYNC_INT_EN2,0x03);}
    #define MCU_INT_ENABLE()        {INTSC_EN = SC_EN;}
    #define MCU_INT_DISABLE()       {INTSC_EN = 0;}
    //-------------- +jwshin 111208     PWMA Port »ç¿ë....     
    #define _USE_PWM_B_         111
#endif
    
#if NT68167
    #define SYNC_INT_DISABLE()  {WriteIIC560(SYNC_INT_EN1,0x80); \
                                WriteIIC560(SYNC_INT_EN2,0x00);}
    #define SYNC_INT_ENABLE()       {WriteIIC560(SYNC_INT_EN1,0xbc); \
                                WriteIIC560(SYNC_INT_EN2,0x03);}
    
#if _167_VERSION_B
    #define MCU_INT_ENABLE()        {   INTSC_EN = (SC_EN | 0x80) ; }
    #define MCU_INT_DISABLE()       {   INTSC_EN = 0x80;    }
#else
    #define MCU_INT_ENABLE()        {   INTSC_EN = SC_EN;   }
    #define MCU_INT_DISABLE()       {   INTSC_EN = 0;   }
#endif

#endif

//  NT68667 DVI OPITMAL SETTINGS
//  0x018 0x00 ¡@       
//  0x019 0x00 ¡@       
//  0x01B 0x01 ¡@       
//  0x01D 0x01 ¡@       
//  0x147 0x00 ¡@       
//  0x338[7:4] b'1111 ¡@
//  0x145 Default ¡@    
//  0x306 Default ¡@    
//  0x309~0x314 Default ¡@                
//  0x320~0x32E Default ¡@                
//  0x339 Default ¡@                
//  0x33A Default 

#endif
