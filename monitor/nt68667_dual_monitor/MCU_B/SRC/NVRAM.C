#include "NVRAM.H"
#include "stdio.h"
#include "8051.H"
#include "RAM.H"
#include "IIC.H"
#include "MCU.H"
#include "ROM_MAP.H"
#include "MyDef.H"
#include "NT686xx_MCU_REG.H"
#include "Board.H"
#include "Mis.H"
#include "ddc_ci.H"
#include "Factory.H"
#include "HDCP.h"
#if FE2P_LIB==ON
	#if NT68167
		#include "fe2p_nt68167 v1.1.h"
	#elif NT68667
		#include "fe2p_nt68667.h"
	#endif
#endif


#if FE2P_LIB==ON

#define ValidFlagAddr 0xfff
#define BLOCK0 0x0000
#define BLOCK1 0x1000
#define FE2P_SAVE_TIME 100	// 100x10ms

unsigned char FE2P_CheckValidBlock()
{
	unsigned char Dat;
	
	Fe2p_ByteRead(ValidFlagAddr,&Dat);
	//NVTprint1("block0 flag %02d\r\n",(unsigned short)Dat);
	if(Dat == 0x55)
		return 0;
	Fe2p_ByteRead(ValidFlagAddr+BLOCK1,&Dat);
	//NVTprint1("block1 flag %02d\r\n",(unsigned short)Dat);
	if(Dat == 0x55)
		return 1;

	return 0xff;	//FE2P block damage
}

void FE2P_LoadToSram()
{
	feValid_Block = FE2P_CheckValidBlock();
	if(feValid_Block > 1)
		{
		feValid_Block = 0;
		InitEEPROM(1);				
		FE2P_Process(1);
		#if FE2P_DEBUG
			printf("FE2P Initialization\n\r");
		#endif
		}
		
	else		//JERRY+
	{
	if(feValid_Block == 0)
		Fe2p_PageRead(BLOCK0,Fe2pBuf,2048);	//block0 first 2k
	else
		Fe2p_PageRead(BLOCK1,Fe2pBuf,2048);	//block1 first 2k
//		#if FE2P_DEBUG
			printf("FE2P Load Flash To SRAM 9000h,Block %02d\n\r",(unsigned short)feValid_Block);
//		#endif
	}
}

void FE2P_SaveToFlash()
{
	unsigned short Offset,i;
	
	if(feValid_Block > 1)
		feValid_Block = 1;
	if(feValid_Block == 0)
		Offset = BLOCK1;	//save to block 1
	else
		Offset = BLOCK0;

//	if ( IsAC_PowerOff() )	return;
		
		
#if NT68670 || NT68670B || NT68167
		
	Fe2p_WriteEnable();
	Fe2p_SectorErase(Offset);	// 100~150ms
	

	for(i=0;i<2048;i+=0x100)
	{
		Fe2p_WriteEnable();
		Fe2p_PageWrite(i+Offset,Fe2pBufAddr+i, 0x100);	// 256bytes 3~4.5ms
	}
	Fe2p_WriteEnable();
	Fe2p_ByteWrite(ValidFlagAddr+Offset,0x55);	//set new valid flag
	Offset ^= BLOCK1;
	Fe2p_WriteEnable();
	Fe2p_ByteWrite(ValidFlagAddr+Offset,0x00);	//clear old valid flag
	feValid_Block ^= 1;


#else
	Fe2p_BlockErase(Offset);	// 100~150ms
	
		
	for(i=0;i<2048;i++)
	{
		Fe2p_ByteWrite(i+Offset,Fe2pBuf[i]);
	}
	Fe2p_ByteWrite(ValidFlagAddr+Offset,0x55);	//set new valid flag
	Offset ^= BLOCK1;
	Fe2p_ByteWrite(ValidFlagAddr+Offset,0x00);	//clear old valid flag
	feValid_Block ^= 1;
#endif
	
//	#if FE2P_DEBUG
		printf("FE2P Save SRAM To Flash ,Block %02d\n\r",(unsigned short)feValid_Block);
//	#endif
}

void FE2P_Process(bit ForceUpdate)
{
	if((feSave && feSave_Timer == 0) || ForceUpdate)
		{
		FE2P_SaveToFlash();
		feSave = 0;
	}
}

void FE2P_ClearBuffer()
{
	unsigned short i;
	for(i=0;i<2048;i++)
		Fe2pBuf[i] = 0xff;
}
#endif


code unsigned char initTab[]={
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
};

unsigned char Read24C16(unsigned short addr16)
{

unsigned char ch;
#if FE2P_LIB==ON
	ch = Fe2pBuf[addr16];
#else
unsigned short device,addr;
	addr = addr16 & 0x0ff;
	device = (addr16 >> 7) & 0x0e;
	device |= EEPROM_ADDR;
	ch = ReadIIC(device,addr);
#endif
	return ch;


	
}

unsigned short Read24C16_Short(unsigned short addr16)
{
unsigned short ret = 0;
#if FE2P_LIB==ON
	ret = Fe2pBuf[addr16];
	ret <<= 8;
	ret += Fe2pBuf[addr16+1];
#else
	ret = Read24C16(addr16);
	addr16++;
	ret <<= 8;
	ret += Read24C16(addr16);
#endif
	return ret;
}

#if 0
void ReadPage24C16(unsigned short addr16,unsigned char *ReadBuffer,unsigned char l)	//xyy 2007.10.22   22:24:25
{
#if FE2P_LIB==ON
unsigned char i;
	for(i=0;i<l;i++){
		ReadBuffer[i] = Fe2pBuf[addr16++];
	}
#else
unsigned char device,addr,i;
	device = (addr16 >> 7) & 0x0e;
	device |= EEPROM_ADDR;
	addr = (unsigned char)addr16;
/* start bit */
	IIC_Start();
/* transmit data */
	WriteByte(device);
	WriteByte(addr);
	ISCL = 1;
	SetISCL();		/* SCL=1 */
/* start bit */
	IIC_Start();
/* transmit data */
	WriteByte(device+1);
	for(i=0;i<(l-1);i++){
		ReadBuffer[i] = ReadByte();
		MasterACK();
	}
	ReadBuffer[l-1] = ReadByte();
/* no ack */
	MasterNACK();
/* stop bit */
	IIC_Stop();
#endif
}
#endif

void Write24C16(unsigned short target,unsigned char value)
{
#if FE2P_LIB==ON
		Fe2pBuf[target] = value;
		feSave = 1;
		feSave_Timer = FE2P_SAVE_TIME;
#else
unsigned char device,addr;
//	if( NVRAM_IsEnabled() )
	{
		EEP_WP_OFF();
		addr = (unsigned char)target;
		device = (unsigned char)((target>>7)&0x0e);
		device |= EEPROM_ADDR;
		WriteIIC(device,addr,value);
		Sleep(12);
		EEP_WP_ON();
	}
#endif
}

void Write24C16_Short(unsigned short target, unsigned short value)
{
#if FE2P_LIB==ON
	Fe2pBuf[target] = value>>8;
	Fe2pBuf[target+1] = (unsigned char)value;
	feSave = 1;
	feSave_Timer = FE2P_SAVE_TIME;
#else
	Write24C16(target,(unsigned char)(value >> 8));
	target++;
	Write24C16(target,(unsigned char)value);
#endif
}


void WritePage24C16(unsigned short target,unsigned short offset,unsigned char *value,unsigned char length)
{
#if FE2P_LIB==ON
unsigned char i;
//JERRY		for(i=0;i<256;i++)
//JERRY			Fe2pBuf[target+i] = value[offset+i];
		for(i=0;i<length;i++)
			Fe2pBuf[target+i] = value[offset+i];
		feSave = 1;
		feSave_Timer = FE2P_SAVE_TIME;
#else
unsigned char i,ch;
//	if( NVRAM_IsEnabled() )
	{
		EEP_WP_OFF();
	/* start bit */
		IIC_Start();
	/* transmit data */
		i = (unsigned char)((target >>7 ) & 0x0e);
		i |= EEPROM_ADDR;
		WriteByte(i);
		i = (unsigned char)target;
		WriteByte(i);
		for(i=0; i<length; i++){
			ch = value[offset + i];
			WriteByte(ch);
		}
	/* stop bit */
		IIC_Stop();
		Sleep(12);
		EEP_WP_ON();
	}
#endif
}

void InitEEPROM(bit k)
{
unsigned short addr;
unsigned short i;
unsigned char temp;

	if(k == 0){
		WritePage24C16(0x00,0,MCU_DataMap,16);
		Write24C16(EPADDR_EMPTY0, 0x55);
		Write24C16(EPADDR_EMPTY1, 0xaa);
		for(addr=0x10; addr<0x40; addr=addr+16){
			WritePage24C16(addr,addr,MCU_DataMap,16);
		}

		bExitSysLoop = TRUE;
//		Write24C16(EPADDR_FACTORY, 1);
		Write24C16(EPADDR_POT_BYTE0,(unsigned char)ulPOTTimerH);//0x1a = POT byte 0
		Write24C16(EPADDR_POT_BYTE1,(unsigned char)(ulPOTTimerH >> 8));//0x1b = POT byte 1
		Write24C16(EPADDR_POT_15M, ucPOTTimerM_4);	//0x2d = POT_15M
	}
	else{
		temp = Read24C16(EPADDR_PERFECTUNE);
		for(addr=0x00; addr<0x70; addr=addr+16){
			WritePage24C16(addr,addr,MCU_DataMap,16);
		}
		Write24C16(EPADDR_BURNIN, 0x01);				
#ifndef Use24C02
		for(i=0;i <0x80; i+=16){	//INITAL	EDID
			WritePage24C16(DDC_ADDR_ANALOG+i,i,_Default_Analog_EDID,16);
			WritePage24C16(DDC_ADDR_DIGITAL+i,i,_Default_Digital_EDID,16);
		}
#endif
		if(temp == 1){	//FGA done
			Write24C16(EPADDR_PERFECTUNE, 1);
		}
//		else{
//			for(i=0; i<0x60; i+=16){	//INITAL	TRUECOLOR
//				WritePage24C16(NVRAM_TRUECOLOR+i,i,_Default_TrueColor_Value,16);
//			}
//		}
		bExitSysLoop = TRUE;	
	}

	Write24C16(EPADDR_RGB_OFFSET, MCU_DataMap[EPADDR_RGB_OFFSET]);
	
//WRITE NEW MODE
	for(i=0; i<0x80; i+=16){
		WritePage24C16(NVRAM_SYNC(0)+i,0,initTab,16);
	}

//write factory mode in user area
	//for(i=0; i<NUMBER_OF_USER_MODE; i++){
	//	InitModeData(i);
	//}

	InitModeData16();

	Write24C16(EPADDR_TD_ACMODE, 0);
	Write24C16(EPADDR_TD_STATE, TD_NORMAL);

	Write24C16(EPADDR_RSO_NOTF, 0x00);	// REQUEST BY FACTORY 2007-04-20

	Write24C16(EPADDR_EMPTY0, 0x55);
	Write24C16(EPADDR_EMPTY1, 0xaa);
	Write24C16(EPADDR_FWVER, VERSION);
	Write24C16(EPADDR_FWREVER, REVERSION);

#if FE2P_LIB==ON
// IGNORED BY NT68631B; HERE IS FOR COMPILER WARNING MESSAGE
	FE2P_Process(1);

	#if (NT68670||NT68670B||NT68167)
		Fe2p_WriteStatus(0);
	#else
/*		if ( !bExitSysLoop )
		{
			Fe2p_Configure(0,0);
			Fe2p_SectorErase(0);
		}
 */
		Fe2p_WriteStatus(0);
	#endif

#endif

	EA = 0;
	while(1){};

}

void InitModeData16()
{
xdata unsigned char ucbuf16[16];
_Monitor_Timing_ table;
unsigned char i;
	
	for(i=0; i<((NUMBER_OF_USER_MODE>>1)<<1); i +=2 ){
		table = EEPROM_TimingTable[i];
		ucbuf16[0] = (unsigned char)(table.usHStart>>8);
#if NT68167
		ucbuf16[1] = (unsigned char)table.usHStart-18;
#else
		ucbuf16[1] = (unsigned char)table.usHStart;
#endif
		ucbuf16[2] = (unsigned char)table.ucResolution;
		ucbuf16[3] = 32;
		ucbuf16[4] = (unsigned char)(table.usHTotal>>8);
		ucbuf16[5] = (unsigned char)table.usHTotal;
		ucbuf16[6] = (unsigned char)(table.usVStart>>8);
		ucbuf16[7] = (unsigned char)table.usVStart;
		Write24C16_Short(NVRAM_HTOTAL50(i), table.usHTotal);		// 50%
		
		table = EEPROM_TimingTable[i+1];
		ucbuf16[8] = (unsigned char)(table.usHStart>>8);
#if NT68167
		ucbuf16[9] = (unsigned char)table.usHStart-18;
#else
		ucbuf16[9] = (unsigned char)table.usHStart;
#endif
		ucbuf16[10] = (unsigned char)table.ucResolution;
		ucbuf16[11] = 32;
		ucbuf16[12] = (unsigned char)(table.usHTotal>>8);
		ucbuf16[13] = (unsigned char)table.usHTotal;
		ucbuf16[14] = (unsigned char)(table.usVStart>>8);
		ucbuf16[15] = (unsigned char)table.usVStart;
		Write24C16_Short(NVRAM_HTOTAL50((i+1)), table.usHTotal);		// 50%

		WritePage24C16( NVRAM_TIMING(i), 0, ucbuf16, 16);
	}

	if ( (NUMBER_OF_USER_MODE & BIT_0) ==1 ) {

		table = EEPROM_TimingTable[NUMBER_OF_USER_MODE-1];
		ucbuf16[0] = (unsigned char)(table.usHStart>>8);
#if NT68167
		ucbuf16[1] = (unsigned char)table.usHStart-18;
#else
		ucbuf16[1] = (unsigned char)table.usHStart;
#endif
		ucbuf16[2] = (unsigned char)table.ucResolution;
		ucbuf16[3] = 32;
		ucbuf16[4] = (unsigned char)(table.usHTotal>>8);
		ucbuf16[5] = (unsigned char)table.usHTotal;
		ucbuf16[6] = (unsigned char)(table.usVStart>>8);
		ucbuf16[7] = (unsigned char)table.usVStart;
		Write24C16_Short(NVRAM_HTOTAL50((NUMBER_OF_USER_MODE-1)), table.usHTotal);		// 50%

		WritePage24C16( NVRAM_TIMING(NUMBER_OF_USER_MODE-1), 0, ucbuf16, 8);
	}

}


/*
void ClearAutoAdjTag(void)
{
unsigned short addr;
	for(addr=0x5b0; addr<0x5be; addr++){
		Write24C16(addr,0x00);
	}
}
*/


#ifndef Use24C02
void LoadDDCData(unsigned char ddcsw)
{
#if FE2P_LIB==ON
unsigned char *p;
unsigned short addr,len,i;
	switch(ddcsw){
	case 1:
		DDC_CTRL_0 = 0;
		p = &DDCPtr0;
		addr = DDC_ADDR_ANALOG;
		len = 128;
		break;
	case 2:
		DDC_CTRL_1 = 0;
		p = &DDCPtr1;
		addr = DDC_ADDR_ANALOG;
		len = 128;
		break;
	}
	for(i=0; i<len; i++){
		*p = Read24C16(addr + i);
		p++;
	}
#else	
unsigned char *p,i;
unsigned short device,addr;
	if(ddcsw == 1){
		DDC_CTRL_0 = 0;
		p = &DDCPtr0;
		bGLEDState = TRUE;
#if NT68167
		addr = (unsigned char)DDC_ADDR_ANALOG;
		device = (unsigned char)(DDC_ADDR_ANALOG >> 7) & 0x0e;
#else
		addr = (unsigned char)DDC_ADDR_DIGITAL;
		device = (unsigned char)(DDC_ADDR_DIGITAL >> 7) & 0x0e;
#endif
	}
	else{
		DDC_CTRL_1 = 0;
		p = &DDCPtr1;
		bGLEDState = FALSE;
		addr = (unsigned char)DDC_ADDR_ANALOG;
		device = (unsigned char)(DDC_ADDR_ANALOG >> 7) & 0x0e;
	}
	
		device |= EEPROM_ADDR;
	/* start bit */
		IIC_Start();
	/* transmit data */
		WriteByte(device);
		WriteByte(addr);
		ISCL = 1;
		SetISCL();		/* SCL=1 */
	//	IIC_DelayHigh();
	/* start bit */
		IIC_Start();
	/* transmit data */
		WriteByte(device+1);
		for(i=0; i<128; i++){
			*p = ReadByte();
			if(i != 127)
				MasterACK();
			p++;
		}
	/* no ack */
		MasterNACK();
	/* stop bit */
		IIC_Stop();
#endif



	if(ddcsw == 1){
		
//#ifdef EDID_FROM_A_ONLY
//		unsigned char *pAnalog;
//		
//		pAnalog = &DDCPtr1;
//		p =  &DDCPtr0;
//		
//		*(p+0x14) = 0x80;
//		//*(p+0x7f) = *(p+0x7f)+0x0E-0x80;
//		*(p+0x18) = 0x2A;
//		*(p+0x7f) = *(pAnalog+0x7f)+(unsigned char)(*(pAnalog+0x14)-0x80+*(pAnalog+0x18)-0x2A);
//		
//#endif

		DDC_CTRL_0 = (EN_DDC | WPT_DDC | MODE_DDC | CLR_UPD | CLR_PTR);
		DDC_CTRL_0 = (EN_DDC | WPT_DDC | MODE_DDC);
	}
	else if(ddcsw == 2){
		DDC_CTRL_1 = (EN_DDC | WPT_DDC | MODE_DDC | CLR_UPD | CLR_PTR);
		DDC_CTRL_1 = (EN_DDC | WPT_DDC | MODE_DDC);
	}
	


}
#endif

#ifndef Use24C02
void SaveDDCData(unsigned char ddcsw)
{
unsigned char *p,i;
unsigned short k;

//	LED_GrnOff();
//	LED_RedOn();
	if(ddcsw == 1){
		DDC_CTRL_0 = (EN_DDC | MODE_DDC | CLR_UPD);
		i = IIC0_STATUS & 0x03;
	}
	else{
		DDC_CTRL_1 = (EN_DDC | MODE_DDC | CLR_UPD);
		i = IIC1_STATUS & 0x03;
	}
	ucLoopTimer_10ms = DDC_DELAY_TIME;
	while(ucLoopTimer_10ms != 0){
		if(ddcsw == 1){
			if((IIC0_STATUS & 0x03) != i){
				i = IIC0_STATUS & 0x03;
				ucLoopTimer_10ms = DDC_DELAY_TIME;
			}
			if((DDC_CTRL_0 & UPD_DDC) != 0){		//up date ddc
				DDC_CTRL_0 = (EN_DDC | MODE_DDC | CLR_UPD);
				ucLoopTimer_10ms = DDC_DELAY_TIME;
			}
		}
		else{
			if((IIC1_STATUS & 0x03) != i){
				i = IIC1_STATUS & 0x03;
				ucLoopTimer_10ms = DDC_DELAY_TIME;
			}
			if((DDC_CTRL_1 & UPD_DDC) != 0){		//up date ddc
				DDC_CTRL_1 = (EN_DDC | MODE_DDC | CLR_UPD);
				ucLoopTimer_10ms = DDC_DELAY_TIME;
			}
		}
	}
	if(ddcsw == 1){
		p = &DDCPtr0;
		for(k=0; k<128; k=k+16){
#if NT68167
			WritePage24C16(DDC_ADDR_ANALOG+k,k,p,16);
#else
			WritePage24C16(DDC_ADDR_DIGITAL+k,k,p,16);
#endif
			if((DDC_CTRL_0 & UPD_DDC) != 0){		//up date ddc
				break;
			}
		}
		
		DDC_CTRL_0 = EN_DDC|MODE_DDC|WPT_DDC;
	}
	else{
		p = &DDCPtr1;
		for(k=0; k<128; k=k+16){
#if (!NT68167)
			WritePage24C16(DDC_ADDR_ANALOG+k,k,p,16);
#endif
			if((DDC_CTRL_1 & UPD_DDC) != 0){		//up date ddc
				break;
			}
		}
		
		DDC_CTRL_1 = EN_DDC|MODE_DDC|WPT_DDC;

#ifdef EDID_FROM_A_ONLY
		{
			unsigned char *pDigital;
			DDC_CTRL_0 = 0;
			pDigital = &DDCPtr0;
			
			for ( k=0; k<128;k++)
				*(pDigital+k) = *(p+k);
			
			*(pDigital+0x14) = 0x80;
			//*(pDigital+0x7f) = *(p+0x7f)+0x0E-0x80;
			*(pDigital+0x18) = 0x2A;
			*(pDigital+0x7f) = *(p+0x7f)+(unsigned char)(*(p+0x14)-0x80+*(p+0x18)-0x2A);
			
			for(k=0; k<128; k=k+16){
			WritePage24C16(DDC_ADDR_DIGITAL+k,k,pDigital,16);
				if((DDC_CTRL_0 & UPD_DDC) != 0){		//up date ddc
					break;
				}
			}
			
			DDC_CTRL_0 = (EN_DDC |WPT_DDC | CLR_UPD | CLR_PTR);
			DDC_CTRL_0 = EN_DDC|MODE_DDC|WPT_DDC;
		}
#endif

		for ( i=0;i<SN_LEN; i++)			//ucSerialNum[i] = Read24C16( EPADDR_SN0+i );
			ucSerialNum[i] = Read24C16( DDC_ADDR_ANALOG+0x4d+i );
	}
#if FE2P_LIB==ON
	FE2P_Process(1);	
#endif
	LED_GrnOn();
	LED_RedOff();
}
#endif


void NVRAM_Init()
{
unsigned char i;
unsigned long temp;

//		printf(" %x \r\n", (unsigned short)Read24C16(EPADDR_EMPTY0));	// +jwshin 111208
		
		if(Read24C16(EPADDR_EMPTY0) != 0x55){//0x00 = eeprom empty
			InitEEPROM(1);
		}
		if(Read24C16(EPADDR_EMPTY1) != 0xaa){//0x01 = eeprom empty
			InitEEPROM(1);
		}
		if(Read24C16(EPADDR_FWVER) != VERSION){//0x02 = F/W version
			InitEEPROM(1);
		}
		if(Read24C16(EPADDR_FWREVER) != REVERSION){//0x03 = F/W reversion
			InitEEPROM(0);
		}

	//set power status
		ucPowerStatus = Read24C16(EPADDR_POWER);//0x04 = Power Status
		ucSource = ucPowerStatus & ~SoftPowerOnFlag;

		temp = Read24C16(EPADDR_POT_BYTE1);//0x1b = POT byte 1
		temp <<= 8;
		temp += Read24C16(EPADDR_POT_BYTE0);//0x1a = POT byte 0
		ucPOTTimerM_4 = Read24C16(EPADDR_POT_15M);
		Set_ulPOTTimerH(temp);
		bIsDDCCiSupported = Read24C16(EPADDR_DDCCI);
		
		for(i=0;i<SN_LEN; i++)
		
			//---------------- +jwshin 111214
			ucSerialNum[i] = Read24C16( EPADDR_SN0+i );	

//----------- -jwshin 111214 Serial Number 사용을 위해
/*		
#ifdef Use24C02
			ucSerialNum[i] = Read24C16( EPADDR_SN0+i );
#else
			ucSerialNum[i] = Read24C16( DDC_ADDR_ANALOG+0x4d+i );
#endif
*/

//		bFactoryMode = Read24C16(EPADDR_FACTORY);
//---------------------- -jwshin 111205
/*
		if(Read24C16(EPADDR_BURNIN) != 0){
			printf("Factroy Mode\n\r");				
			FactoryEnterMode();
	#ifdef BenQ_FACTORY
			BenQ_EnterFactoryMode();
	#endif								
		}
*/		
//-------------------------------------------	
	if(bIsDDCCiSupported)
	 	StartDDCCI();
	else
		StopDDCCI();

}

void Check_DDC_Update(void)
{
#ifdef Use24C02
/*
//	if( (IsDVIconnected() == TRUE) || (IsVGAconnected() == TRUE) ){
	if(bFactoryMode == FALSE){
		EDID_WP_ON();
	}
	else{
		EDID_WP_OFF();
	}
*/
#else
//check ddc update
//	if( ((IsDVIconnected() != TRUE) && (IsVGAconnected() != TRUE)) || bFactoryMode ){
	if(bFactoryMode == FALSE){

		DDC_CTRL_0 = EN_DDC|MODE_DDC;
		DDC_CTRL_1 = EN_DDC|MODE_DDC;
	}
	else{
		DDC_CTRL_0 = EN_DDC|MODE_DDC|WPT_DDC;
		DDC_CTRL_1 = EN_DDC|MODE_DDC|WPT_DDC;		
	}
	
	#if NT68167
		if((DDC_CTRL_0 & UPD_DDC) != 0){	//up date ddc
			SaveDDCData(1);
		}
	#else
		if((DDC_CTRL_0 & UPD_DDC) != 0){	//up date ddc
			SaveDDCData(1);
		}
		if((DDC_CTRL_1 & UPD_DDC) != 0){	//up date ddc
			SaveDDCData(2);
		}
	#endif
#endif
}




