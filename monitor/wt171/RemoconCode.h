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
//Remocon 1
//****************************************************************//
#if	defined(Remocon_1st)
#define	RemoconCustomCode			0x40//custom code!!!!

/*1 */#define	TUNER_CODE				0x00//data code!!!
/*2 */#define	RGB_CODE				0x80
/*3 */#define	CHANNELandMENU_UP_CODE			0x40
/*4 */#define	CHANNELandMENU_DOWN_CODE		0xC0
/*5 */#define	MENU_CODE				0x20
/*6 */#define	SELECT_CODE				0xA0
/*7 */#define	VOLUMEandVALUE_DOWN_CODE		0xE0
/*8 */#define	VOLUMEandVALUE_UP_CODE			0x60
/*9 */#define	MUTE_CODE                       	0x10
/*10*/#define	PIP_CODE                        	0x90
/*11*/#define	POWER_CODE                      	0x50
/*12*/#define	DVI_CODE                        	0x08
/*13*/#define	VIDEO_CODE                      	0x28
/*14*/#define	NUM_0_code                      	0x78
/*15*/#define	NUM_1_code                      	0xA8
/*16*/#define	NUM_2_code                      	0x68
/*17*/#define	NUM_3_code                      	0xE8
/*18*/#define	NUM_4_code                      	0x18
/*19*/#define	NUM_5_code                      	0x98
/*20*/#define	NUM_6_code                      	0x58
/*21*/#define	NUM_7_code                      	0xD8
/*22*/#define	NUM_8_code                      	0x38
/*23*/#define	NUM_9_code                      	0xB8
/*24*/#define	ADDandDEL_code                  	0xF8

//****************************************************************//
//Remocon 2
//****************************************************************//
#elif	defined(Remocon_2nd)
#define	RemoconCustomCode			0x40//custom code!!!!
                                            		
#define	TUNER_CODE					0x70//data code!!!
#define	RGB_CODE					0xA8//
#define	CHANNELandMENU_UP_CODE		0x50//
#define	CHANNELandMENU_DOWN_CODE	0xD0//
#define	MENU_CODE					0x68//
#define	SELECT_CODE					0x98//
#define	VOLUMEandVALUE_DOWN_CODE	0xB0//
#define	VOLUMEandVALUE_UP_CODE		0x30//
#define	MUTE_CODE                       		0xF8//
#define	PIP_CODE                        		0x48//
#define	POWER_CODE                      		0xF0//
#define	DVI_CODE                        		0xD8//
#define	VIDEO_CODE                      		0x88//
#define	NUM_0_code                      		0x90//
#define	NUM_1_code                      		0x00//
#define	NUM_2_code                      		0x80//
#define	NUM_3_code                      		0x40//
#define	NUM_4_code                      		0xC0//
#define	NUM_5_code                      		0x20//
#define	NUM_6_code                      		0xA0//
#define	NUM_7_code                      		0x60//
#define	NUM_8_code                      		0xE0//
#define	NUM_9_code                      		0x10//
#define	ADDandDEL_code                  		0x1A//

#elif	defined(Remocon_3th)
#define	RemoconCustomCode			0x00//custom code!!!!

/*1 */#define	TUNER_CODE					0x00//data code!!!
/*2 */#define	RGB_CODE					0x80
/*3 */#define	CHANNELandMENU_UP_CODE		0x40
/*4 */#define	CHANNELandMENU_DOWN_CODE	0xC0
/*5 */#define	MENU_CODE					0x20
/*6 */#define	SELECT_CODE					0xA0
/*7 */#define	VOLUMEandVALUE_DOWN_CODE	0xE0
/*8 */#define	VOLUMEandVALUE_UP_CODE		0x60
/*9 */#define	MUTE_CODE                       	0x10
/*10*/#define	PIP_CODE                        	0x90
/*11*/#define	POWER_CODE                      	0x50
/*12*/#define	DVI_CODE                        	0x08
/*13*/#define	VIDEO_CODE                      	0x28
/*14*/#define	NUM_0_code                      	0x78
/*15*/#define	NUM_1_code                      	0xA8
/*16*/#define	NUM_2_code                      	0x68
/*17*/#define	NUM_3_code                      	0xE8
/*18*/#define	NUM_4_code                      	0x18
/*19*/#define	NUM_5_code                      	0x98
/*20*/#define	NUM_6_code                      	0x58
/*21*/#define	NUM_7_code                      	0xD8
/*22*/#define	NUM_8_code                      	0x38
/*23*/#define	NUM_9_code                      	0xB8
/*24*/#define	ADDandDEL_code                  	0xF8

#elif	defined(Remocon_BTC)
#if 0//---------------------------------------------------------바뀐 코드
	#define	RemoconCustomCode			0x40 //custom code

	#define	CHANNELandMENU_UP_CODE		0x08
	#define	CHANNELandMENU_DOWN_CODE	0x70	
	#define	MENU_CODE					0xC8
	#define	SELECT_CODE					0x18
	#define	VOLUMEandVALUE_DOWN_CODE	0xa8
	#define	VOLUMEandVALUE_UP_CODE		0x68
	#define	MUTE_CODE                       		0x98	// smpark 20030806
	#define	POWER_CODE                       		0x28
	#define	NUM_0_code                      		0x00
	#define	NUM_1_code                      		0x80
	#define	NUM_2_code                      		0x40
	#define	NUM_3_code                      		0xC0
	#define	NUM_4_code                      		0x20
	#define	NUM_5_code                      		0xA0
	#define	NUM_6_code                      		0x60
	#define	NUM_7_code                      		0xE0
	#define	NUM_8_code                      		0x10
	#define	NUM_9_code                      		0x90

	#define	NUM_100_code                    		0x50	//0x0A//smpark 20030729

	// 추가된 CODE  smpark

	// PIP
	#define	IR_PIP_ON_OFF                 	0xD0  // 0x0B //smpark 20030812
	#define	IR_PIP_POS_H                 	0x78  // 0x1E //smpark 20030812
	#define	IR_PIP_POS_V                 	0xF8  // 0x1F //smpark 20030812
	#define	IR_PIP_ZOOM                	0xE8 // 0x17 //smpark 20030812

/*
	#define	IR_PIP_INCREASE                0xA5  //	0x5A					
	#define	IR_PIP_DECREASE                0xD2  // 0x4B
	#define	IR_PIP_MOVE_LEFT               0xB2  // 0x4D 
	#define	IR_PIP_MOVE_RIGHT             0xBA  // 0x5D
	#define	IR_PIP_MOVE_UP                  0x3A  // 0x5C
	#define	IR_PIP_MOVE_DOWN               0x32  // 0x4C
*/
	#if	defined(USE_TTX)
		// TTX COLOR
		#define	IR_RED_TV           		     	0xE8  // 0x17
		#define	IR_GREEN_EXIT                	0xD8  // 0x1B
		#define	IR_YELLOW_SPC                	0xF0  // 0x0F
		#define	IR_CYAN                  		0xDA  // 0x5B

		// TTX
		#define	IR_TTX_TEXT_MIX_TV		0x72  // 0x4E
		#define	IR_TTX_LIST_STORE        	0xA2  // 0x45
		#define	IR_TTX_LIST_FTEXT        	0x22  // 0x44
		#define	IR_TTX_INDEX             		0xC2  // 0x43
		#define	IR_TTX_HOLD              		0xE2  // 0x47
		#define	IR_TTX_UPDATE            		0x62  // 0x46
		#define	IR_TTX_TIME              		0x12  // 0x48
		#define	IR_TTX_SIZE              		0x92  // 0x49
		#define	IR_TTX_REVEAL            		0x02  // 0x40
	#endif

	// MISCELLANEOUS
	#define	IR_SLEEP             	     		0xB0  // 0x0D
	#define	IR_MTS                  		0x30  // 0x0C //smpark 20030812
	#define	IR_RECALL                 	 	0x38  // 0x1C 
	#define IR_PRECH				0x58  // 0x1A // smpark 20030812 (코드 모름)
	#define IR_ADD					0x88  // 0x11 //smpark 20030729
	#define IR_SPC					0xF0  // 0x0f //smpark 20030729
	#define IR_SSC					0x48  // 0x12 //smpark 20030812
	#define IR_EXIT					0xD8  // 0x1B //smpark 20030729
	#define IR_WIDE					0xB8  // 0x1D //smpark 20030812
#else//--------------------------------------------------------이전코드

	#define	RemoconCustomCode			0x40 //custom code

	#define	POWER_CODE                  0x28
	#define	SELECT_CODE					0x18

	#define	MUTE_CODE                   0x98

	#define	NUM_0_code                  0x00
	#define	NUM_1_code                  0x80
	#define	NUM_2_code                  0x40
	#define	NUM_3_code                  0xC0
	#define	NUM_4_code                  0x20
	#define	NUM_5_code                  0xA0
	#define	NUM_6_code                  0x60
	#define	NUM_7_code                  0xE0
	#define	NUM_8_code                  0x10
	#define	NUM_9_code                  0x90

	#define	NUM_100_code                0x50


	#define	CHANNELandMENU_UP_CODE		0x08
	#define	CHANNELandMENU_DOWN_CODE	0x70	
	#define	MENU_CODE					0xC8
	#define	VOLUMEandVALUE_DOWN_CODE	0xa8
	#define	VOLUMEandVALUE_UP_CODE		0x68

	// MISCELLANEOUS
	#define IR_WIDE						0xB8
	#define IR_EXIT						0xD8
	#define	IR_SLEEP             	    0xB0

	#define IR_SPC						0xF0
	#define	IR_MTS                  	0x30
	#define IR_SSC						0x48

	#define	IR_RECALL                 	0x38
	#define IR_PRECH					0x58
	#define IR_ADD						0x88
	//#define IR_TV_PC					0xE8


	// PIP
	#define	IR_PIP_ON_OFF               0xD0
	#define	IR_PIP_POS_H                0x78
	#define	IR_PIP_POS_V                0xF8
	#define	IR_PIP_ZOOM                	0xE8


	#if	defined(USE_TTX)
		// TTX COLOR
		#define	IR_RED_TV           	0xE8
		#define	IR_GREEN_EXIT           0xD8
		#define	IR_YELLOW_SPC           0xF0
		#define	IR_CYAN                 0xDA

		// TTX
		#define	IR_TTX_TEXT_MIX_TV		0x72
		#define	IR_TTX_LIST_STORE       0xA2
		#define	IR_TTX_LIST_FTEXT       0x22
		#define	IR_TTX_INDEX            0xC2
		#define	IR_TTX_HOLD             0xE2
		#define	IR_TTX_UPDATE           0x62
		#define	IR_TTX_TIME             0x12
		#define	IR_TTX_SIZE             0x92
		#define	IR_TTX_REVEAL           0x02
	#endif

#endif//------------------------------------------------------------------------------------------	



#elif	defined(Remocon_PNIX)	//2004-04-28
	#define	RemoconCustomCode			0x0e //custom code

	#define	POWER_CODE                  0x14
	#define	SELECT_CODE					0x18

	#define	NUM_1_code                  0x01
	#define	NUM_2_code                  0x02
	#define	NUM_3_code                  0x03
	#define	NUM_4_code                  0x04
	#define	NUM_5_code                  0x05
	#define	NUM_6_code                  0x06
	#define	NUM_7_code                  0x07
	#define	NUM_8_code                  0x08
	#define	NUM_9_code                  0x09
	#define	NUM_0_code                  0x00
	#define	NUM_100_code                0x0a
	
	#define	IR_RECALL                 	0x1C 

	#define IR_PRECH					0x1a
	#define IR_EXIT						0x1b
	#define	MUTE_CODE                   0x19

	#define	MENU_CODE					0x13
	#define	CHANNELandMENU_UP_CODE		0x10
	#define	CHANNELandMENU_DOWN_CODE	0x0e	
	#define	VOLUMEandVALUE_DOWN_CODE	0x15
	#define	VOLUMEandVALUE_UP_CODE		0x16
	
	// MISCELLANEOUS
	#define IR_SPC						0x0f
	#define	IR_MTS                  	0x0c
	#define IR_SSC						0x12

	#define IR_WIDE						0x1d
	#define IR_ADD						0x11
	#define	IR_SLEEP             	    0x0d


	// PIP
	#define	IR_PIP_ON_OFF               0x0b
	#define	IR_PIP_POS_H                0x1e
	#define	IR_PIP_POS_V                0x1f
	#define	IR_PIP_ZOOM                	0x17
	

#endif
