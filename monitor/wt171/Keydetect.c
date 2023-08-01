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

//****************************************************************//
//화일참조
//****************************************************************//
#include	"TopHeader.h"
#include	"power.h"
#include "extern.h"

#include <stdio.h>


#if		defined(MCU_MTV230)
#include	"MTV230xfr.h"
#elif		defined(MCU_MTV412)
#include	"MTV412xfr.h"
#elif		defined(MCU_NT68F63)
#include	"NT68F63.h"
#endif


void putss(BYTE);


//****************************************************************//
//변수선언
//****************************************************************//

extern	BYTE	KEY_value;

extern	BYTE	ReadAdr;
//extern	BYTE	CurrentFunction;
extern	bit	NowTopOsdOn;
extern 	BYTE	PowerOnsequence;
extern	bit	YouGoingInitialize;
//extern	BYTE	OSDcusorPosition;
//extern	BYTE	OsdMode;
extern	bit	RepeatCodeWait;


#if defined (BtcBoard_Option)	
BYTE code KeyTab[16]={0x01, //0    0x00 ~ 0x07 (0.0000v ~ 0.20625v)
                      0x00, //1    0x08 ~ 0x0F (0.20625v ~ 0.4125v)
                      0x02, //2    0x10 ~ 0x17 (0.4125v ~ 0.61875v)
                      0x02, //3    0x18 ~ 0x1F (0.61875v ~ 0.825v)
                      0x02, //4    0x20 ~ 0x27 (0.825v ~ 1.03125v)
                      0x00, //5    0x28 ~ 0x2F (1.03125v ~ 1.2375v)
                      0x03, //6    0x30 ~ 0x37 (1.2375v ~ 1.44325v)
                      0x03, //7    0x38 ~ 0x3F (1.44325v ~ 1.65v)
                      0x03, //8    0x40 ~ 0x47 (1.65v ~ 1.85625v)
                      0x00, //9    0x48 ~ 0x4F (1.85625v ~ 2.0625v)
                      0x00, //10    0x50 ~ 0x57 (2.0625v ~ 2.26875v)
                      0x04, //11    0x58 ~ 0x5F (2.26875v ~ 2.475v)
                      0x04, //12    0x60 ~ 0x67 (2.475v ~ 2.68125v)
                      0x00, //13    0x68 ~ 0x6F (2.68125v ~ 2.8875v)
                      0x00, //14    0x70 ~ 0x77 (2.8875v ~ 3.09375v)
                      0x00};//15    0x78 ~ 0x7F (3.09375 ~ 3.3v) 

// 		  	  							 0v 		0.74v   	1.63v   	2.43v                
BYTE code ADC1_KEY[5]={	0,UpKey,	DownKey,	MenuKey,	TVpipKey};
BYTE code ADC0_KEY[5]={	0,VolumeUp,	AutoKey,	VolumeDown,	SelKey 	};
#endif




void Keydetect(void)
{

#ifdef	KEY_USE
#ifdef	MatrixLevel_KEY
	KEY4 ^= 1;
	KEY3 ^= 1;
	KEY2 ^= 1;
	
#elif	defined(MTV230_ADC_KEY)
	static bit SelChannl = 0;
	BYTE idata	ADCresult;
	
	SelChannl ^= 1;
	ADCresult = xADC&0x3F;	//[ADC]0xF10(r)[5:0] (0~63)
	
	
	if(SelChannl)	//채널"1" ADC값을 읽고...
	{				
		#if defined (BtcBoard_Option)		//2003-04-01
			#if 1
				if((xP54&0x01)==0)	{KEY_valueDetect1 = PowerKey;}
				else if(PowerOnsequence>=MainPowerON)	//Power On 상태
				{  					
					ADCresult=ADCresult>>2;	//[5:2] (0~15)
					KEY_valueDetect1=ADC1_KEY[KeyTab[ADCresult]];
					if(KEY_valueDetect1==0) 	KeyTimeBuffer1=0;
				}
				else 	//Power Off 상태에서는 그냥 벗어난다.
				{			
					KeyTimeBuffer1=0;
					KEY_valueDetect1=0;	// NoKey!
				}		
			#else
				if	(0x00<=ADCresult&&ADCresult<=0x03){KEY_valueDetect1 = UpKey;}
				else if	(0x09<=ADCresult&&ADCresult<=0x13){KEY_valueDetect1 = DownKey;}	
				else if	(0x20<=ADCresult&&ADCresult<=0x24){KEY_valueDetect1 = MenuKey;}	
				else if	(0x29<=ADCresult&&ADCresult<=0x33){KEY_valueDetect1 = TVpipKey;}	
				else {KEY_valueDetect1 = 0;KeyTimeBuffer1=0;}		// NoKey!
			#endif
						
		#endif

		//채터링 방지.
		if(KEY_valueDetect1!=KEY_valueBackup1) //매 10ms마다 체크.
		{																			
			KEY_valueBackup1=KEY_valueDetect1;	
			KeyTimeBuffer1=0;
			KeyContinueFlag=0;
		}
		else if(KEY_valueDetect1)	//Key 진행... Key chattering~
		{
			++KeyTimeBuffer1;	//매 10ms마다 1증가.
			
			if(KeyTimeBuffer1==KEY_chatteringTime)
			{																			//OneTime KEY!!	//KEY_chatteringTime=10 (100ms동안)이면.
				KEY_value = KEY_valueDetect1;			
			}	

			if( (KEY_valueDetect1==DownKey||KEY_valueDetect1==UpKey)&&(KeyTimeBuffer1>=KEY_chatteringTime) )
			{	
				if(KeyTimeBuffer1==TIMER_500ms+5)
				{
					KeyTimeBuffer1 = TIMER_500ms;
					KEY_value = KEY_valueDetect1;
					KeyContinueFlag=1;
				}
			}
			
			#ifdef MenuKeyInitialize
			else if(KEY_valueDetect1==MenuKey)
			{
				if(KeyTimeBuffer1>=(Key_MenuSystemInit/2))	//5sec동안 눌리면...
				{	
					if(PowerOnsequence>=MainPowerON)	//power가 켜져 있는 상태에서만 인이셜한다.
					{
						KeyTimeBuffer1 = 0;
						KEY_value = PowerKey;
						YouGoingInitialize=1;
						FactoryDftFlag=1;
						TransparencyOnfFlag=0;
					}
				}
			}
			#endif
			
			/*
			#ifdef	ContinueToShortKeyDefine	//2003-04-01 by thkim, ifdefine statement added
			    					//보드마다 ch 0,1 의 키상태가 다르기때문에 추가함.
			if( (KEY_valueDetect1==VolumeDown || KEY_valueDetect1==VolumeUp)&&(KeyTimeBuffer1==TIMER_500ms+5) )	//Repeat KEY!! 
			{
				KeyTimeBuffer1 = TIMER_500ms;
				KEY_value = KEY_valueDetect1;
			}
			#endif
			*/

			if(KeyTimeBuffer1>=0xfffe) KeyTimeBuffer1=0xfffe;
		}
		
		#if defined(ADCKeyChange)
			xADC = 0x80|0x01;		//채널"1" ADC start!
		#else
			xADC = 0x80|0x02;		//채널"1" ADC start!
		#endif
	}	
	else	//채널"0" ADC값을 읽고...
	{
		//if(PowerOnsequence<MainPowerON) KEY_value=0;//Power Off 상태에서는 그냥 벗어난다.
		
		#if defined (BtcBoard_Option)
	    #if 1
			  if(PowerOnsequence>=MainPowerON) 
			  {  				//Power Off 상태에서는 그냥 벗어난다.
					ADCresult=ADCresult>>2;			
					KEY_valueDetect0=ADC0_KEY[KeyTab[ADCresult]];
					if(KEY_valueDetect0==0) KeyTimeBuffer0=0;
			  }
			  else {KeyTimeBuffer0=0;KEY_valueDetect0=0;}	// NoKey!
		  #else
				if	(0x00<=ADCresult&&ADCresult<=0x03){KEY_valueDetect0 = VolumeUp;}	
				else if	(0x09<=ADCresult&&ADCresult<=0x13){KEY_valueDetect0 = AutoKey;}	
				else if	(0x20<=ADCresult&&ADCresult<=0x24){KEY_valueDetect0 = VolumeDown;}
				else if	(0x29<=ADCresult&&ADCresult<=0x33){KEY_valueDetect0 = SelKey;}
				else {KEY_valueDetect0 = 0;KeyTimeBuffer0=0}	// NoKey!
	    #endif			

		#endif

		//채터링 방지.
		if(KEY_valueDetect0!=KEY_valueBackup0) 
		{
			KEY_valueBackup0=KEY_valueDetect0;	
			KeyTimeBuffer0=0;
			KeyContinueFlag=0;
		}
		else if(KEY_valueDetect0)	//Key 진행... Key chattering~
		{
			++KeyTimeBuffer0;	//매 10ms마다 1증가.
			
			if(KeyTimeBuffer0==KEY_chatteringTime)	{KEY_value = KEY_valueDetect0;}	//OneTime KEY!! //KEY_chatteringTime=10 (100ms)이면.
			
			#ifdef	ContinueToShortKeyDefine
			if( (KEY_valueDetect0==VolumeDown||KEY_valueDetect0==VolumeUp)
					&&(KeyTimeBuffer0==TIMER_500ms+5)&&(KeyTimeBuffer0>=KEY_chatteringTime) )	//Repeat KEY!! 
			{
				KeyTimeBuffer0 = TIMER_500ms;
				KEY_value = KEY_valueDetect0;
				KeyContinueFlag=1;
			}
			#endif

			//-------------- Burning Test Mode +jwshin 040813			
			#ifdef BURNING_TEST
			if(KEY_valueDetect0==SelKey)
			{
				if( (PowerOnsequence>=MainPowerON)&&(KeyTimeBuffer0>=(Key_MenuSystemInit/2)) )
				{	//power가 켜져 있는 상태에서 //5sec...
					KeyTimeBuffer0 = 0;
					KEY_value =0;
					BurningFlag=1;
					KEY_valueDetect0 = 0;
				}
			}
			#endif
			//------------------------------------------------


			if(KeyTimeBuffer0>=0xfffe) KeyTimeBuffer0=0xfffe;
		}
		
		
		#if defined(ADCKeyChange)
			xADC = 0x80|0x02;		//채널"0" ADC start!
		#else
			xADC = 0x80|0x01;		//채널"0" ADC start!
		#endif
	}

#elif	defined(MTV412_ADC_KEY)
	static bit SelChannl = 0;
	BYTE ADCresult;
	
	SelChannl ^= 1;
	ADCresult = xADC&0x3F;
	/*
	////////////////////////////////
	/
	/	Under Construct!!
	/
	////////////////////////////////
	*/

#elif	defined(NT68F63_ADC_KEY)

#endif
#endif
}
