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

//------------------------------------------------------------------------------
// ROW ADDRESSING FOR DISPLAY AREA
//------------------------------------------------------------------------------
#define	IN_DSP_ROW0	0x80
#define	IN_DSP_ROW1	0x81
#define	IN_DSP_ROW2	0x82
#define	IN_DSP_ROW3	0x83
#define	IN_DSP_ROW4	0x84
#define	IN_DSP_ROW5	0x85
#define	IN_DSP_ROW6	0x86
#define	IN_DSP_ROW7	0x87
#define	IN_DSP_ROW8	0x88
#define	IN_DSP_ROW9	0x89
#define IN_DSP_ROW10 0x8A
#define	IN_DSP_ROW11 0x8B
#define	IN_DSP_ROW12 0x8C
#define	IN_DSP_ROW13 0x8D
#define	IN_DSP_ROW14 0x8E
#define	IN_DSP_ROW15 0x8F	// DUMMY 

//------------------------------------------------------------------------------
// CIC & RCI COLUMN ADDRESSING FOR DATA AREA
//------------------------------------------------------------------------------
#define	IN_CIC_COL0	0x00
#define	IN_CIC_COL1	0x01
#define	IN_CIC_COL2	0x02
#define	IN_CIC_COL3	0x03
#define	IN_CIC_COL4	0x04
#define	IN_CIC_COL5	0x05
#define	IN_CIC_COL6	0x06
#define	IN_CIC_COL7	0x07
#define IN_CIC_COL8	0x08
#define	IN_CIC_COL9	0x09
#define	IN_CIC_COL10	0x0A
#define	IN_CIC_COL11	0x0B
#define	IN_CIC_COL12	0x0C
#define	IN_CIC_COL13	0x0D
#define	IN_CIC_COL14	0x0E
#define	IN_CIC_COL15	0x0F
#define	IN_CIC_COL16	0x10
#define	IN_CIC_COL17	0x11
#define	IN_CIC_COL18	0x12
#define	IN_CIC_COL19	0x13
#define	IN_CIC_COL20	0x14
#define	IN_CIC_COL21	0x15
#define	IN_CIC_COL22	0x16
#define	IN_CIC_COL23	0x17
#define	IN_CIC_COL24	0x18
#define IN_CIC_COL25	0x19
#define	IN_CIC_COL26	0x1A
#define	IN_CIC_COL27	0x1B
#define	IN_CIC_COL28	0x1C
#define	IN_CIC_COL29	0x1D
#define	IN_CIC_COL30	0x1E
#define	IN_CIC_COL31	0x1F	// DUMMY 

//------------------------------------------------------------------------------
// CII COLUMN ADDRESSING FOR DISPLAY AREA
//------------------------------------------------------------------------------
#define	IN_CII_COL0	0x40
#define	IN_CII_COL1	0x41
#define	IN_CII_COL2	0x42
#define	IN_CII_COL3	0x43
#define	IN_CII_COL4	0x44
#define	IN_CII_COL5	0x45
#define	IN_CII_COL6	0x46
#define IN_CII_COL7	0x47
#define	IN_CII_COL8	0x48
#define	IN_CII_COL9	0x49
#define	IN_CII_COL10	0x4A
#define	IN_CII_COL11	0x4B
#define	IN_CII_COL12	0x4C
#define	IN_CII_COL13	0x4D
#define	IN_CII_COL14	0x4E
#define	IN_CII_COL15	0x4F
#define	IN_CII_COL16	0x50
#define	IN_CII_COL17	0x51
#define	IN_CII_COL18	0x52
#define	IN_CII_COL19	0x53
#define	IN_CII_COL20	0x54
#define	IN_CII_COL21	0x55
#define	IN_CII_COL22	0x56
#define	IN_CII_COL23	0x57
#define IN_CII_COL24	0x58
#define	IN_CII_COL25	0x59
#define	IN_CII_COL26	0x5A
#define	IN_CII_COL27	0x5B
#define	IN_CII_COL28	0x5C
#define	IN_CII_COL29	0x5D
#define	IN_CII_COL30	0x5E
#define	IN_CII_COL31	0x5F	// DUMMY 

//------------------------------------------------------------------------------
// ROW ADDRESSING FOR ATTRIBUTE REGISTERS
//------------------------------------------------------------------------------
#define	IN_ATTR_ROW0	0xA0
#define	IN_ATTR_ROW1	0xA1
#define	IN_ATTR_ROW2	0xA2
#define	IN_ATTR_ROW3	0xA3
#define	IN_ATTR_ROW4	0xA4
#define IN_ATTR_ROW5	0xA5
#define	IN_ATTR_ROW6	0xA6
#define	IN_ATTR_ROW7	0xA7
#define	IN_ATTR_ROW8	0xA8
#define	IN_ATTR_ROW9	0xA9
#define	IN_ATTR_ROW10	0xAA
#define	IN_ATTR_ROW11	0xAB
#define	IN_ATTR_ROW12	0xAC
#define	IN_ATTR_ROW13	0xAD
#define	IN_ATTR_ROW14	0xAE
#define	IN_ATTR_ROW15	0xAF

//------------------------------------------------------------------------------
// WINDOW START OF ROW
//------------------------------------------------------------------------------
#define	IN_WIN_SROW0	0x00
#define	IN_WIN_SROW1	0x10
#define	IN_WIN_SROW2	0x20
#define	IN_WIN_SROW3	0x30
#define	IN_WIN_SROW4	0x40
#define	IN_WIN_SROW5	0x50
#define	IN_WIN_SROW6	0x60
#define IN_WIN_SROW7	0x70
#define	IN_WIN_SROW8	0x80
#define	IN_WIN_SROW9	0x90
#define	IN_WIN_SROW10	0xA0
#define	IN_WIN_SROW11	0xB0
#define	IN_WIN_SROW12	0xC0
#define	IN_WIN_SROW13	0xD0
#define	IN_WIN_SROW14	0xE0

//------------------------------------------------------------------------------
// WINDOW END OF ROW
//------------------------------------------------------------------------------
//#if 1
#define	IN_WIN_EROW0	0x00
#define	IN_WIN_EROW1	0x01
#define	IN_WIN_EROW2	0x02
#define	IN_WIN_EROW3	0x03
#define	IN_WIN_EROW4	0x04
#define	IN_WIN_EROW5	0x05
#define IN_WIN_EROW6	0x06
#define	IN_WIN_EROW7	0x07
#define	IN_WIN_EROW8	0x08
#define	IN_WIN_EROW9	0x09
#define	IN_WIN_EROW10	0x0A
#define	IN_WIN_EROW11	0x0B
#define	IN_WIN_EROW12	0x0C
#define	IN_WIN_EROW13	0x0D
#define	IN_WIN_EROW14	0x0E
#define	IN_WIN_EROW15	0x0F
//#else
/*
#define	IN_WIN_EROW0	0x01
#define	IN_WIN_EROW1	0x02
#define	IN_WIN_EROW2	0x03
#define	IN_WIN_EROW3	0x04
#define	IN_WIN_EROW4	0x05
#define	IN_WIN_EROW5	0x06
#define IN_WIN_EROW6	0x07
#define	IN_WIN_EROW7	0x08
#define	IN_WIN_EROW8	0x09
#define	IN_WIN_EROW9	0x0A
#define	IN_WIN_EROW10	0x0B
#define	IN_WIN_EROW11	0x0C
#define	IN_WIN_EROW12	0x0D
#define	IN_WIN_EROW13	0x0E
#define	IN_WIN_EROW14	0x0F
*/
//#endif                    
//------------------------------------------------------------------------------
// WINDOW COLUMN NO.
//------------------------------------------------------------------------------
#define	IN_WIN_COL0	0x00
#define	IN_WIN_COL1	0x08
#define	IN_WIN_COL2	0x10
#define	IN_WIN_COL3	0x18
#define	IN_WIN_COL4	0x20
#define IN_WIN_COL5	0x28
#define	IN_WIN_COL6	0x30
#define	IN_WIN_COL7	0x38
#define	IN_WIN_COL8	0x40
#define	IN_WIN_COL9	0x48
#define	IN_WIN_COL10	0x50
#define	IN_WIN_COL11	0x58
#define	IN_WIN_COL12	0x60
#define	IN_WIN_COL13	0x68
#define	IN_WIN_COL14	0x70
#define	IN_WIN_COL15	0x78
#define	IN_WIN_COL16	0x80
#define	IN_WIN_COL17	0x88
#define	IN_WIN_COL18	0x90
#define	IN_WIN_COL19	0x98
#define	IN_WIN_COL20	0xA0
#define	IN_WIN_COL21	0xA8
#define IN_WIN_COL22	0xB0
#define	IN_WIN_COL23	0xB8
#define	IN_WIN_COL24	0xC0
#define	IN_WIN_COL25	0xC8
#define	IN_WIN_COL26	0xD0
#define	IN_WIN_COL27	0xD8
#define	IN_WIN_COL28	0xE0
#define	IN_WIN_COL29	0xE8
#define	IN_WIN_COL30	0xF0
#define	IN_WIN_COL31	0xF8

//------------------------------------------------------------------------------
// WINDOW REGISTER
//------------------------------------------------------------------------------
#define	IN_WIN_CTRL	IN_ATTR_ROW15
#define	IN_WIN_ENB		0x04	// %00000100
#define	IN_WIN_DIS		0x04^0xFF
#define	IN_WIN_INT		0x02	// %00000010
#define	IN_WIN_UNINT	0x02^0xFF
#define	IN_WIN_COLOREXT		0x01	// %00000001
#define IN_WIN_COLORUNEXT	0x01^0xFF

//------------------------------------------------------------------------------
// Color Define
//------------------------------------------------------------------------------
#define	IN_OSD_RED	0x04			//%00000100
#define	IN_OSD_GREEN	0x02			//%00000010
#define	IN_OSD_BLUE	0x01			//%00000001
#define	IN_OSD_BLACK	0x00
#define	IN_OSD_MAGEN	IN_OSD_RED+IN_OSD_BLUE
#define	IN_OSD_CYAN	IN_OSD_BLUE+IN_OSD_GREEN
#define	IN_OSD_YELLOW	IN_OSD_RED+IN_OSD_GREEN
#define	IN_OSD_WHITE	IN_OSD_RED+IN_OSD_BLUE+IN_OSD_GREEN

//------------------------------------------------------------------------------
// OSD Delay
//------------------------------------------------------------------------------
#define	IN_OsdVDelay  	0x5e//0x67
#define	IN_OsdHDelay  	0x30//0x31

//------------------------------------------------------------------------------
// Start & Stop OSD flow
//------------------------------------------------------------------------------	
//#define	IN_F_START			0x78
//#define	IN_F_STOP			0x79

//****************************************************************//
//Internal OSD, Window set.
//****************************************************************//
code BYTE IN_TOPWINDOW[] = {
	IN_ATTR_ROW15,IN_CII_COL0,		//Attribute (Row15,Col0)- 
#if defined(OsdMenuType1)
//WINDOW1
	IN_WIN_SROW3|IN_WIN_EROW10,		//0 //WIN1 HEIGHT                      
	IN_WIN_COL0|IN_WIN_ENB|IN_WIN_INT,	//1 //WIN1 COL START & CONTROL         
	IN_WIN_COL29|IN_OSD_WHITE,		//2 //WIN1 COL END & COLOR             
//WINDOW2                                                                              
	IN_WIN_SROW2|IN_WIN_EROW11,		//3 //WIN2 HEIGHT                      
	IN_WIN_COL0|IN_WIN_ENB|IN_WIN_INT,   	//4 //WIN2 COL START & CONTROL         
	IN_WIN_COL29|IN_OSD_WHITE,		//5 //WIN2 COL END & COLOR             
                                                //                                     
//WINDOW3                                       //                                     
	IN_WIN_SROW1|IN_WIN_EROW12,		//6 //WIN3 HEIGHT                      
	#if defined(OsdColor_Red)
	IN_WIN_COL0|IN_WIN_ENB|IN_WIN_INT,//&IN_WIN_COLORUNEXT, 	//7 //WIN3 COL START & CONTROL         
	IN_WIN_COL29|IN_OSD_RED,//IN_OSD_BLACK		//8 //WIN3 COL END & COLOR         
	#else
	IN_WIN_COL0|IN_WIN_ENB|IN_WIN_INT|IN_WIN_COLOREXT, 	//7 //WIN3 COL START & CONTROL         
	IN_WIN_COL29|IN_OSD_BLUE,//IN_OSD_BLACK		//8 //WIN3 COL END & COLOR         
	#endif
	                                                                               
//WINDOW4
	IN_WIN_SROW1|IN_WIN_EROW12,		//9  //WIN4 HEIGHT                     
	IN_WIN_COL0|IN_WIN_ENB|IN_WIN_INT,	//10 //WIN4 COL START & CONTROL        
	IN_WIN_COL29|IN_OSD_BLACK,		//11 //WIN4 COL END & COLOR            
	                                                    
	0x00,					//12 //slide width(win1~4)                                  
	0x00,					//13 //slide height(win1~4)                    

	#if defined(SXGA_Panel)
	0x5e,//IN_OsdVDelay, //0x48,//IN_OsdVDelay 	//14 // Vertical delay                                  
	0x31,//IN_OsdHDelay, //0x20,//IN_OsdHDelay 	//15 // Horizontal Delay                
	#elif	defined(WXGA_Panel)
	0x39,//IN_OsdVDelay, //0x48,//IN_OsdVDelay 	//14 // Vertical delay                                  
	0x29,//IN_OsdHDelay, //0x20,//IN_OsdHDelay 	//15 // Horizontal Delay                
	//0x2f,//IN_OsdHDelay, //0x20,//IN_OsdHDelay 	//15 // Horizontal Delay                
	#else
	0x39,//IN_OsdVDelay, //0x48,//IN_OsdVDelay 	//14 // Vertical delay                                  
	0x29,//IN_OsdHDelay, //0x20,//IN_OsdHDelay 	//15 // Horizontal Delay                
	#endif
	
	0x11,	//addr 16: Character height(value:0x14)
#else	//±âÁ¸ ¾ØÇÁ·»ÅØ ¸Þ´º
//WINDOW1
	IN_WIN_SROW3|IN_WIN_EROW10,		//0 //WIN1 HEIGHT                      
	IN_WIN_COL0|IN_WIN_ENB|IN_WIN_INT,	//1 //WIN1 COL START & CONTROL         
	IN_WIN_COL29|IN_OSD_WHITE,		//2 //WIN1 COL END & COLOR             
//WINDOW2                                                                              
	IN_WIN_SROW2|IN_WIN_EROW12,		//3 //WIN2 HEIGHT                      
	IN_WIN_COL0|IN_WIN_ENB|IN_WIN_INT,   	//4 //WIN2 COL START & CONTROL         
	IN_WIN_COL29|IN_OSD_WHITE,		//5 //WIN2 COL END & COLOR             
                                                //                                     
//WINDOW3                                       //                                     
	IN_WIN_SROW1|IN_WIN_EROW13,		//6 //WIN3 HEIGHT                      
	#if defined(OsdColor_Red)
	IN_WIN_COL0|IN_WIN_ENB|IN_WIN_INT,//&IN_WIN_COLORUNEXT, 	//7 //WIN3 COL START & CONTROL         
	IN_WIN_COL29|IN_OSD_RED,//IN_OSD_BLACK		//8 //WIN3 COL END & COLOR         
	#else
	IN_WIN_COL0|IN_WIN_ENB|IN_WIN_INT|IN_WIN_COLOREXT, 	//7 //WIN3 COL START & CONTROL         
	IN_WIN_COL29|IN_OSD_BLUE,//IN_OSD_BLACK		//8 //WIN3 COL END & COLOR         
	#endif
		                                                                               
//WINDOW4                                                                              
	IN_WIN_SROW1|IN_WIN_EROW13,		//9  //WIN4 HEIGHT                     
	IN_WIN_COL0|IN_WIN_ENB|IN_WIN_INT,	//10 //WIN4 COL START & CONTROL        
	IN_WIN_COL29|IN_OSD_BLACK,		//11 //WIN4 COL END & COLOR            
	                                                    
	0x00,					//12 //slide width(win1~4)                                  
	0x00,					//13 //slide height(win1~4)                    

	#if defined(SXGA_Panel)
	0x5e,//IN_OsdVDelay, //0x48,//IN_OsdVDelay 	//14 // Vertical delay                                  
	0x31,//IN_OsdHDelay, //0x20,//IN_OsdHDelay 	//15 // Horizontal Delay                
	#elif	defined(WXGA_Panel)
	0x39,//IN_OsdVDelay, //0x48,//IN_OsdVDelay 	//14 // Vertical delay                                  
	0x29,//IN_OsdHDelay, //0x20,//IN_OsdHDelay 	//15 // Horizontal Delay                
	#else
	0x39,//IN_OsdVDelay, //0x48,//IN_OsdVDelay 	//14 // Vertical delay                                  
	0x29,//IN_OsdHDelay, //0x20,//IN_OsdHDelay 	//15 // Horizontal Delay                
	#endif
	
	0x14,	//addr 16: Character height(value:0x14)
#endif
	
	//IN_F_START,IN_ATTR_ROW15,IN_CII_COL18,0x04,	//0x04:width double
	IN_F_START,IN_ATTR_ROW2,IN_CII_COL30,0x01,	//Attr. row2,col30->character height double
	IN_F_START,IN_ATTR_ROW15,IN_CII_COL12,0x40,	//Attr. row15,col12->slide width
	IN_F_START,IN_ATTR_ROW15,IN_CII_COL13,0x40,	//Attr. row15,col13->slide height
	IN_F_STOP
};

//****************************************************************//
//Internal OSD, TV Window set.
//****************************************************************//
code BYTE IN_TVTOPWINDOW[] = {
	IN_ATTR_ROW15,IN_CII_COL0,		//Attribute (Row15,Col0)- 
#if defined(OsdMenuType1)	//12*30
//WINDOW1
	IN_WIN_SROW4|IN_WIN_EROW11,		//0 //WIN1 HEIGHT                      
	IN_WIN_COL0|IN_WIN_ENB|IN_WIN_INT,	//1 //WIN1 COL START & CONTROL         
	IN_WIN_COL29|IN_OSD_WHITE,		//2 //WIN1 COL END & COLOR             
//WINDOW2                                                                              
	IN_WIN_SROW2|IN_WIN_EROW11,		//3 //WIN2 HEIGHT                      
	IN_WIN_COL0|IN_WIN_ENB|IN_WIN_INT,   	//4 //WIN2 COL START & CONTROL         
	IN_WIN_COL29|IN_OSD_WHITE,		//5 //WIN2 COL END & COLOR             
                                                //                                     
//WINDOW3                                       //                                     
	IN_WIN_SROW1|IN_WIN_EROW12,		//6 //WIN3 HEIGHT                      
	IN_WIN_COL0|IN_WIN_ENB|IN_WIN_INT|IN_WIN_COLOREXT, 	//7 //WIN3 COL START & CONTROL         
	#if defined(OsdColor_Red)
	IN_WIN_COL29|IN_OSD_RED,		//8 //WIN3 COL END & COLOR             
	#else
	IN_WIN_COL29|IN_OSD_BLUE,		//8 //WIN3 COL END & COLOR             
	#endif
	                                                                               
//WINDOW4                                                                              
	IN_WIN_SROW1|IN_WIN_EROW12,		//9  //WIN4 HEIGHT                     
	IN_WIN_COL0|IN_WIN_ENB|IN_WIN_INT,	//10 //WIN4 COL START & CONTROL        
	IN_WIN_COL29|IN_OSD_BLACK,		//11 //WIN4 COL END & COLOR            
#else	//13*30	                                                    
//WINDOW1
	IN_WIN_SROW4|IN_WIN_EROW11,		//0 //WIN1 HEIGHT                      
	IN_WIN_COL0|IN_WIN_ENB|IN_WIN_INT,	//1 //WIN1 COL START & CONTROL         
	IN_WIN_COL29|IN_OSD_WHITE,		//2 //WIN1 COL END & COLOR             
//WINDOW2                                                                              
	IN_WIN_SROW2|IN_WIN_EROW13,		//3 //WIN2 HEIGHT                      
	IN_WIN_COL0|IN_WIN_ENB|IN_WIN_INT,   	//4 //WIN2 COL START & CONTROL         
	IN_WIN_COL29|IN_OSD_WHITE,		//5 //WIN2 COL END & COLOR             
                                                //                                     
//WINDOW3                                       //                                     
	IN_WIN_SROW1|IN_WIN_EROW14,		//6 //WIN3 HEIGHT                      
	IN_WIN_COL0|IN_WIN_ENB|IN_WIN_INT, 	//7 //WIN3 COL START & CONTROL         
	#if defined(OsdColor_Red)
	IN_WIN_COL29|IN_OSD_RED,		//8 //WIN3 COL END & COLOR             
	#else
	IN_WIN_COL29|IN_OSD_BLUE,		//8 //WIN3 COL END & COLOR             
	#endif
	                                                                               
//WINDOW4                                                                              
	IN_WIN_SROW1|IN_WIN_EROW14,		//9  //WIN4 HEIGHT                     
	IN_WIN_COL0|IN_WIN_ENB|IN_WIN_INT,	//10 //WIN4 COL START & CONTROL        
	IN_WIN_COL29|IN_OSD_BLACK,		//11 //WIN4 COL END & COLOR            
#endif	                                                    
	0x00,					//12 //slide width(win1~4)                                  
	0x00,					//13 //slide height(win1~4)                    
	
	//--------------------------------
	#if defined(VideoDoubleOSD)
	//--------------------------------
	#if defined(SXGA_Panel)
	0x40,//IN_OsdVDelay, //0x48,//IN_OsdVDelay 	//14 // Vertical delay                                  
	0x1f,//IN_OsdHDelay, //0x20,//IN_OsdHDelay 	//15 // Horizontal Delay                
	#elif	defined(WXGA_Panel)
	0x21,//IN_OsdVDelay, //0x48,//IN_OsdVDelay 	//14 // Vertical delay                                  
	0x1f,//IN_OsdHDelay, //0x20,//IN_OsdHDelay 	//15 // Horizontal Delay
	#else
	0x21,//IN_OsdVDelay, //0x48,//IN_OsdVDelay 	//14 // Vertical delay                                  
	0x1f,//IN_OsdHDelay, //0x20,//IN_OsdHDelay 	//15 // Horizontal Delay
	#endif
	0x20						//addr 16: Character height(value:0x14)
	//--------------------------------
	#else //normal size
	//--------------------------------
	#if defined(SXGA_Panel)
	0x5d,				//IN_OsdVDelay 	//14 // Vertical delay                                  
	0x31,				//IN_OsdHDelay 	//15 // Horizontal Delay                
	#elif	defined(WXGA_Panel)
	0x42,				//IN_OsdVDelay 	//14 // Vertical delay                                  
	0x2f,				//IN_OsdHDelay 	//15 // Horizontal Delay
	#else
	0x42,				//IN_OsdVDelay 	//14 // Vertical delay                                  
	0x2f,				//IN_OsdHDelay 	//15 // Horizontal Delay
	#endif
	0x11,						//addr 16: Character height(value:0x14)
	//--------------------------------
	#endif
	//--------------------------------
	
	#if defined(VideoDoubleOSD)
	IN_F_START,IN_ATTR_ROW15,IN_CII_COL18,0x04,	//Attr. row15,col18->0x04:width double(o)
	IN_F_START,IN_ATTR_ROW2,IN_CII_COL30,0x01,	//Attr. row2,col30->character height double(o)
	#else
	IN_F_START,IN_ATTR_ROW15,IN_CII_COL18,0x00,	//Attr. row15,col18->0x04:width double(x)
	IN_F_START,IN_ATTR_ROW2,IN_CII_COL30,0x00,	//Attr. row2,col30->character height double(x)
	#endif
	
	IN_F_START,IN_ATTR_ROW15,IN_CII_COL12,0x40,	//Attr. row15,col12->slide width
	IN_F_START,IN_ATTR_ROW15,IN_CII_COL13,0x40,	//Attr. row15,col13->slide height
	IN_F_STOP
};


#if defined(TempOsdMenu)||defined(SSwideOsdtype)	//2003-10-29
///////////////////////WINDOW1
code BYTE IN_WINDOW1_ColorWhite[] = {
	IN_ATTR_ROW15,IN_CII_COL0,		//Attribute (Row15,Col0)- 
//WINDOW1
	IN_WIN_SROW4|IN_WIN_EROW11,		//0 //WIN1 HEIGHT                      
	IN_WIN_COL0|IN_WIN_ENB|IN_WIN_INT,	//1 //WIN1 COL START & CONTROL         
	IN_WIN_COL29|IN_OSD_WHITE,		//2 //WIN1 COL END & COLOR
	IN_F_STOP
};

code BYTE IN_WINDOW1_ColorExtWhite[] = {
	IN_ATTR_ROW15,IN_CII_COL0,
//WINDOW1
	IN_WIN_SROW4|IN_WIN_EROW11,		//0 //WIN1 HEIGHT                      
	IN_WIN_COL0|IN_WIN_ENB|IN_WIN_INT|IN_WIN_COLOREXT,	//1 //WIN1 COL START & CONTROL         
	IN_WIN_COL29|IN_OSD_WHITE,		//2 //WIN1 COL END & COLOR
	IN_F_STOP
};
///////////////////////WINDOW2
code BYTE IN_WINDOW2_ColorWhite[] = {
	IN_ATTR_ROW15,IN_CII_COL3,		//Attribute (Row15,Col0)- 
//WINDOW2
	IN_WIN_SROW2|IN_WIN_EROW11,		//3 //WIN2 HEIGHT                      
	IN_WIN_COL0|IN_WIN_ENB|IN_WIN_INT,	//1 //WIN1 COL START & CONTROL         
	IN_WIN_COL29|IN_OSD_WHITE,		//2 //WIN1 COL END & COLOR
	IN_F_STOP
};
code BYTE IN_WINDOW2_ColorExtWhite[] = {
	IN_ATTR_ROW15,IN_CII_COL3,		//Attribute (Row15,Col0)- 
//WINDOW2
	IN_WIN_SROW2|IN_WIN_EROW11,		//3 //WIN2 HEIGHT                      
	IN_WIN_COL0|IN_WIN_ENB|IN_WIN_INT|IN_WIN_COLOREXT,	//1 //WIN1 COL START & CONTROL         
	IN_WIN_COL29|IN_OSD_WHITE,		//2 //WIN1 COL END & COLOR
	IN_F_STOP
};
///////////////////////WINDOW3
code BYTE IN_WINDOW3_ColorExtWhite[] = {
	IN_ATTR_ROW15,IN_CII_COL6,		//Attribute (Row15,Col0)- 
//WINDOW3
	IN_WIN_SROW1|IN_WIN_EROW12,		//6 //WIN3 HEIGHT                      
	IN_WIN_COL0|IN_WIN_ENB|IN_WIN_INT|IN_WIN_COLOREXT,	//1 //WIN1 COL START & CONTROL         
	IN_WIN_COL29|IN_OSD_WHITE,		//2 //WIN1 COL END & COLOR
	IN_F_STOP
};
code BYTE IN_WINDOW3_ColorExtMagenta[] = {
	IN_ATTR_ROW15,IN_CII_COL6,		//Attribute (Row15,Col0)- 
//WINDOW3
	IN_WIN_SROW1|IN_WIN_EROW12,		//6 //WIN3 HEIGHT                      
	IN_WIN_COL0|IN_WIN_ENB|IN_WIN_INT|IN_WIN_COLOREXT,	//1 //WIN1 COL START & CONTROL         
	IN_WIN_COL29|IN_OSD_MAGEN,		//2 //WIN1 COL END & COLOR
	IN_F_STOP
};
//////////////////////WINDOW4
code BYTE IN_WINDOW4_BgBlack[] = {
	IN_ATTR_ROW15,IN_CII_COL9,
//WINDOW4                                                                              
	IN_WIN_SROW1|IN_WIN_EROW12,		//9  //WIN4 HEIGHT                     
	IN_WIN_COL0|IN_WIN_ENB|IN_WIN_INT,	//10 //WIN4 COL START & CONTROL        
	IN_WIN_COL29|IN_OSD_BLACK,	
	IN_F_STOP
};
//------------------------------------------------------------
code BYTE IN_TVTOPWINDOW2[] = {
	IN_ATTR_ROW15,IN_CII_COL0,		//Attribute (Row15,Col0)- 
//WINDOW1
	IN_WIN_SROW4|IN_WIN_EROW11,		//0 //WIN1 HEIGHT                      
	IN_WIN_COL0|IN_WIN_ENB|IN_WIN_INT,	//1 //WIN1 COL START & CONTROL         
	IN_WIN_COL29|IN_OSD_WHITE,		//2 //WIN1 COL END & COLOR             
//WINDOW2                                                                              
	IN_WIN_SROW2|IN_WIN_EROW11,		//3 //WIN2 HEIGHT                      
	IN_WIN_COL0|IN_WIN_ENB|IN_WIN_INT,   	//4 //WIN2 COL START & CONTROL         
	IN_WIN_COL29|IN_OSD_WHITE,		//5 //WIN2 COL END & COLOR             
                                                //                                     
//WINDOW3                                       //                                     
	IN_WIN_SROW1|IN_WIN_EROW11,		//6 //WIN3 HEIGHT                      
	IN_WIN_COL0|IN_WIN_ENB|IN_WIN_INT|IN_WIN_COLOREXT, 	//7 //WIN3 COL START & CONTROL         
	IN_WIN_COL29|IN_OSD_BLUE,		//8 //WIN3 COL END & COLOR             
	                                                                               
//WINDOW4                                                                              
	IN_WIN_SROW1|IN_WIN_EROW11,		//9  //WIN4 HEIGHT                     
	IN_WIN_COL0|IN_WIN_ENB|IN_WIN_INT,	//10 //WIN4 COL START & CONTROL        
	IN_WIN_COL29|IN_OSD_BLACK,		//11 //WIN4 COL END & COLOR   
	0x00,					//12 //slide width(win1~4)                                  
	0x00,					//13 //slide height(win1~4)                    
	
	//--------------------------------
	#if defined(VideoDoubleOSD)
	//--------------------------------
	#if defined(SXGA_Panel)
	0x40,//IN_OsdVDelay, //0x48,//IN_OsdVDelay 	//14 // Vertical delay                                  
	0x1f,//IN_OsdHDelay, //0x20,//IN_OsdHDelay 	//15 // Horizontal Delay                
	#elif	defined(WXGA_Panel)
	0x21,//IN_OsdVDelay, //0x48,//IN_OsdVDelay 	//14 // Vertical delay                                  
	0x1f,//IN_OsdHDelay, //0x20,//IN_OsdHDelay 	//15 // Horizontal Delay
	#else
	0x21,//IN_OsdVDelay, //0x48,//IN_OsdVDelay 	//14 // Vertical delay                                  
	0x1f,//IN_OsdHDelay, //0x20,//IN_OsdHDelay 	//15 // Horizontal Delay
	#endif
	0x20						//addr 16: Character height(value:0x14)
	//--------------------------------
	#else //normal size
	//--------------------------------
	#if defined(SXGA_Panel)
	0x5d,				//IN_OsdVDelay 	//14 // Vertical delay                                  
	0x31,				//IN_OsdHDelay 	//15 // Horizontal Delay                
	#elif	defined(WXGA_Panel)
	0x42,				//IN_OsdVDelay 	//14 // Vertical delay                                  
	0x2f,				//IN_OsdHDelay 	//15 // Horizontal Delay
	#else
	0x42,				//IN_OsdVDelay 	//14 // Vertical delay                                  
	0x2f,				//IN_OsdHDelay 	//15 // Horizontal Delay
	#endif
	0x11,						//addr 16: Character height(value:0x14)
	//--------------------------------
	#endif
	//--------------------------------
	
	#if defined(VideoDoubleOSD)
	IN_F_START,IN_ATTR_ROW15,IN_CII_COL18,0x04,	//Attr. row15,col18->0x04:width double(o)
	IN_F_START,IN_ATTR_ROW2,IN_CII_COL30,0x01,	//Attr. row2,col30->character height double(o)
	#else
	IN_F_START,IN_ATTR_ROW15,IN_CII_COL18,0x00,	//Attr. row15,col18->0x04:width double(x)
	IN_F_START,IN_ATTR_ROW2,IN_CII_COL30,0x00,	//Attr. row2,col30->character height double(x)
	#endif
	
	IN_F_START,IN_ATTR_ROW15,IN_CII_COL12,0x40,	//Attr. row15,col12->slide width
	IN_F_START,IN_ATTR_ROW15,IN_CII_COL13,0x40,	//Attr. row15,col13->slide height
	IN_F_STOP
};

///////////////////////WINDOW1
code BYTE IN_WINDOW1_ColorWhite2[] = {
	IN_ATTR_ROW15,IN_CII_COL0,		//Attribute (Row15,Col0)- 
//WINDOW1
	IN_WIN_SROW4|IN_WIN_EROW11,		//0 //WIN1 HEIGHT                      
	IN_WIN_COL0|IN_WIN_ENB|IN_WIN_INT,	//1 //WIN1 COL START & CONTROL         
	IN_WIN_COL29|IN_OSD_WHITE,		//2 //WIN1 COL END & COLOR
	IN_F_STOP
};

code BYTE IN_WINDOW1_ColorExtWhite2[] = {
	IN_ATTR_ROW15,IN_CII_COL0,
//WINDOW1
	IN_WIN_SROW4|IN_WIN_EROW11,		//0 //WIN1 HEIGHT                      
	IN_WIN_COL0|IN_WIN_ENB|IN_WIN_INT|IN_WIN_COLOREXT,	//1 //WIN1 COL START & CONTROL         
	IN_WIN_COL29|IN_OSD_WHITE,		//2 //WIN1 COL END & COLOR
	IN_F_STOP
};
///////////////////////WINDOW2
code BYTE IN_WINDOW2_ColorWhite2[] = {
	IN_ATTR_ROW15,IN_CII_COL3,		//Attribute (Row15,Col0)- 
//WINDOW2
	IN_WIN_SROW2|IN_WIN_EROW11,		//3 //WIN2 HEIGHT                      
	IN_WIN_COL0|IN_WIN_ENB|IN_WIN_INT,	//1 //WIN1 COL START & CONTROL         
	IN_WIN_COL29|IN_OSD_WHITE,		//2 //WIN1 COL END & COLOR
	IN_F_STOP
};
code BYTE IN_WINDOW2_ColorExtWhite2[] = {
	IN_ATTR_ROW15,IN_CII_COL3,		//Attribute (Row15,Col0)- 
//WINDOW2
	IN_WIN_SROW2|IN_WIN_EROW11,		//3 //WIN2 HEIGHT                      
	IN_WIN_COL0|IN_WIN_ENB|IN_WIN_INT|IN_WIN_COLOREXT,	//1 //WIN1 COL START & CONTROL         
	IN_WIN_COL29|IN_OSD_WHITE,		//2 //WIN1 COL END & COLOR
	IN_F_STOP
};
///////////////////////WINDOW3
code BYTE IN_WINDOW3_ColorExtWhite2[] = {
	IN_ATTR_ROW15,IN_CII_COL6,		//Attribute (Row15,Col0)- 
//WINDOW3
	IN_WIN_SROW1|IN_WIN_EROW11,		//6 //WIN3 HEIGHT                      
	IN_WIN_COL0|IN_WIN_ENB|IN_WIN_INT|IN_WIN_COLOREXT,	//1 //WIN1 COL START & CONTROL         
	IN_WIN_COL29|IN_OSD_WHITE,		//2 //WIN1 COL END & COLOR
	IN_F_STOP
};

code BYTE IN_WINDOW3_ColorExtMagenta2[] = {
	IN_ATTR_ROW15,IN_CII_COL6,		//Attribute (Row15,Col0)- 
//WINDOW3
	IN_WIN_SROW1|IN_WIN_EROW11,		//6 //WIN3 HEIGHT                      
	IN_WIN_COL0|IN_WIN_ENB|IN_WIN_INT|IN_WIN_COLOREXT,	//1 //WIN1 COL START & CONTROL         
	IN_WIN_COL29|IN_OSD_MAGEN,		//2 //WIN1 COL END & COLOR
	IN_F_STOP
};
#endif


code BYTE IN_SUBWINDOW[] = {
	IN_ATTR_ROW15,IN_CII_COL0,
//WINDOW1
	IN_WIN_SROW0|IN_WIN_EROW14,		//WIN1 HEIGHT
	IN_WIN_COL0|IN_WIN_DIS|IN_WIN_INT,	//WIN1 COL START & CONTROL
	IN_WIN_COL29|IN_OSD_BLACK,		//WIN1 COL END & COLOR
//WINDOW2
	IN_WIN_SROW0|IN_WIN_EROW14,		//WIN2 HEIGHT
	IN_WIN_COL0|IN_WIN_ENB|IN_WIN_INT,   //WIN2 COL START & CONTROL
	IN_WIN_COL29|IN_OSD_BLACK,		//WIN2 COL END & COLOR

//WINDOW3
	IN_WIN_SROW0|IN_WIN_EROW14,		//WIN3 HEIGHT
	IN_WIN_COL0|IN_WIN_DIS|IN_WIN_INT, 	//WIN3 COL START & CONTROL
	IN_WIN_COL29|IN_OSD_BLUE,			//WIN3 COL END & COLOR

//WINDOW4
	IN_WIN_SROW0|IN_WIN_EROW14,		//WIN4 HEIGHT
	IN_WIN_COL0|IN_WIN_DIS|IN_WIN_INT,	//WIN4 COL START & CONTROL
	IN_WIN_COL29|IN_OSD_MAGEN,		//WIN4 COL END & COLOR
	0,
	0,
	IN_OsdVDelay,					// Vertical delay
	IN_OsdHDelay,					// Horizontal Delay
	0x10,						// Character height

	IN_F_STOP
};

code BYTE IN_INFOWINDOW[] = {
	IN_ATTR_ROW15,IN_CII_COL0,
//WINDOW1
	IN_WIN_SROW0|IN_WIN_EROW14,		//WIN1 HEIGHT
	IN_WIN_COL0|IN_WIN_DIS|IN_WIN_INT,	//WIN1 COL START & CONTROL
	IN_WIN_COL29|IN_OSD_BLACK,		//WIN1 COL END & COLOR
//WINDOW2
	IN_WIN_SROW0|IN_WIN_EROW14,		//WIN2 HEIGHT
	IN_WIN_COL0|IN_WIN_ENB|IN_WIN_INT,   //WIN2 COL START & CONTROL
	IN_WIN_COL29|IN_OSD_BLACK,		//WIN2 COL END & COLOR

//WINDOW3
	IN_WIN_SROW0|IN_WIN_EROW14,		//WIN3 HEIGHT
	IN_WIN_COL0|IN_WIN_DIS|IN_WIN_INT, 	//WIN3 COL START & CONTROL
	IN_WIN_COL29|IN_OSD_BLUE,			//WIN3 COL END & COLOR

//WINDOW4
	IN_WIN_SROW0|IN_WIN_EROW14,		//WIN4 HEIGHT
	IN_WIN_COL0|IN_WIN_DIS|IN_WIN_INT,	//WIN4 COL START & CONTROL
	IN_WIN_COL29|IN_OSD_MAGEN,		//WIN4 COL END & COLOR
	0,
	0,
	IN_OsdVDelay,					// Vertical delay
	IN_OsdHDelay,					// Horizontal Delay
	0x10,						// Character height

	IN_F_STOP
};

code BYTE IN_AUTOTUNEWINDOW[] = {
	IN_ATTR_ROW15,IN_CII_COL0,
//WINDOW1
	IN_WIN_SROW0|IN_WIN_EROW14,		//0 //WIN1 HEIGHT
	IN_WIN_COL0|IN_WIN_DIS|IN_WIN_INT,	//1 //WIN1 COL START & CONTROL
	IN_WIN_COL29|IN_OSD_BLACK,		//2 //WIN1 COL END & COLOR
//WINDOW2    
	IN_WIN_SROW0|IN_WIN_EROW14,		//3 //WIN2 HEIGHT
	IN_WIN_COL0|IN_WIN_ENB|IN_WIN_INT,      //4 //WIN2 COL START & CONTROL
	IN_WIN_COL29|IN_OSD_BLACK,		//5 //WIN2 COL END & COLOR
                                                //  
//WINDOW3                                       //  
	IN_WIN_SROW0|IN_WIN_EROW14,		//6 //WIN3 HEIGHT
	IN_WIN_COL0|IN_WIN_DIS|IN_WIN_INT, 	//7 //WIN3 COL START & CONTROL
	IN_WIN_COL29|IN_OSD_BLUE,		//8 	//WIN3 COL END & COLOR
                                                
//WINDOW4                                       
	IN_WIN_SROW0|IN_WIN_EROW14,		//9  //WIN4 HEIGHT
	IN_WIN_COL0|IN_WIN_DIS|IN_WIN_INT,	//10 //WIN4 COL START & CONTROL
	IN_WIN_COL29|IN_OSD_MAGEN,		//11 //WIN4 COL END & COLOR
	0,		  			//12 //slide width(win1~4) 
	0,		  			//13 //slide height(win1~4)
	IN_OsdVDelay,	       			//14 // Vertical delay
	IN_OsdHDelay,	       			//15 // Horizontal Delay
	0x10,					//16 // Character height

	IN_F_STOP
};

code BYTE IN_VOLUMEWINDOW[] = {
	IN_ATTR_ROW15,IN_CII_COL0,
//WINDOW1
	IN_WIN_SROW0|IN_WIN_EROW14,		//WIN1 HEIGHT
	IN_WIN_COL0|IN_WIN_DIS|IN_WIN_INT,	//WIN1 COL START & CONTROL
	IN_WIN_COL29|IN_OSD_BLACK,		//WIN1 COL END & COLOR

//WINDOW2
	IN_WIN_SROW0|IN_WIN_EROW3,		//WIN2 HEIGHT
	IN_WIN_COL0|IN_WIN_ENB|IN_WIN_INT,   //WIN2 COL START & CONTROL
	IN_WIN_COL31|IN_OSD_BLACK,		//WIN2 COL END & COLOR

//WINDOW3
	IN_WIN_SROW0|IN_WIN_EROW14,		//WIN3 HEIGHT
	IN_WIN_COL0|IN_WIN_DIS|IN_WIN_INT, 	//WIN3 COL START & CONTROL
	IN_WIN_COL29|IN_OSD_BLUE,			//WIN3 COL END & COLOR

//WINDOW4
	IN_WIN_SROW0|IN_WIN_EROW14,		//WIN4 HEIGHT
	IN_WIN_COL0|IN_WIN_DIS|IN_WIN_INT,	//WIN4 COL START & CONTROL
	IN_WIN_COL29|IN_OSD_MAGEN,		//WIN4 COL END & COLOR
	
	0,					//addr 12:
	0,					//addr 13:
	#if defined(SXGA_Panel)
	0xdd,	//IN_OsdVDelay,			//addr 14:	// Vertical delay
	0x1d,	//IN_OsdHDelay,			//addr 15:	// Horizontal Delay
	#elif	defined(WXGA_Panel)
	0x9f,//IN_OsdVDelay, //0x48,//IN_OsdVDelay 	//14 // Vertical delay                                  
	0x19,//IN_OsdHDelay, //0x20,//IN_OsdHDelay 	//15 // Horizontal Delay
	#else
	0x9f,//IN_OsdVDelay, //0x48,//IN_OsdVDelay 	//14 // Vertical delay                                  
	0x19,//IN_OsdHDelay, //0x20,//IN_OsdHDelay 	//15 // Horizontal Delay
	#endif
	
	0x1e,					//addr 16:	// Character height
	0,					//addr 17:
	0x04,					//addr 18[2]:	// single/double
	
	IN_F_START,IN_ATTR_ROW15,IN_CII_COL18,0x04,	//Attr. row15,col18->0x04:width double
	IN_F_START,IN_ATTR_ROW2,IN_CII_COL30,0x00,	//Attr. row2,col30->character height double

	IN_F_STOP
};


code BYTE IN_WINDOW_OFF[] = {
	IN_F_START,IN_ATTR_ROW15,IN_CII_COL1,0x00,	//Attr. row15,col..->0x04:disable
	IN_F_START,IN_ATTR_ROW15,IN_CII_COL4,0x00,	//Attr. row15,col..->0x04:disable
	IN_F_START,IN_ATTR_ROW15,IN_CII_COL7,0x00,	//Attr. row15,col..->0x04:disable
	IN_F_START,IN_ATTR_ROW15,IN_CII_COL10,0x00,	//Attr. row15,col..->0x04:disable
	IN_F_STOP
};