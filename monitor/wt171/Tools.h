#if !defined _NFREN_Debug_Tools_
#define _NFREN_Debug_Tools_


void DelayNOP20();		// Lcall is 4byte 4cycle
void DelayNOP12();		// Lcall is 4byte 4cycle
void DelayNOP10();		// Lcall is 4byte 4cycle
void DelayNOP6()	;	// Lcall is 4byte 4cycle
//void DelayNOP25();		// 25uS


#if defined(USE_UART)
void putss(BYTE value);

#endif
#ifdef USE_TTXIIC
bit TTX_WriteData(BYTE temp);
bit TTX_START_I2C(BYTE sysaddr);
void TTX_STOP_I2C(void);
WORD TTX_ReadDataACK(void);
WORD TTX_ReadDataNAK(void);
#else
bit WriteData(BYTE temp);
bit START_I2C(BYTE sysaddr);
void STOP_I2C(void);
WORD ReadDataACK(void);
WORD ReadDataNAK(void);
#endif



#endif


