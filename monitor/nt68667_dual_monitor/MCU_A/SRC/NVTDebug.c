#include "NVTDebug.h"
#include "scaler.h"
#include "NVRAM.H"
#include "NT686xx_MCU_REG.H"
#include "8051.H"

#ifdef NVT_HW_DEBUG
xdata unsigned char IsNVTDebugActive;

unsigned char NVTHWDebug(unsigned char *pCmd, unsigned char *pOut)
{
	unsigned short addr;
	unsigned char  value;
	
	if (pCmd[3] != 0xFE) return 0;
	
	addr = pCmd[5];
	addr <<= 8;
	addr |= pCmd[6];

	if ((pCmd[4] == NVT_RD_SCALER) || (pCmd[4] == NVT_RD_EEPROM)){
		if (pCmd[4] == NVT_RD_SCALER)
			value = ReadIIC560(addr);
		else if (pCmd[4] == NVT_RD_EEPROM)
			value = Read24C16(addr);
		
		pOut[0] = 0x6e;
		pOut[1] = 0x88;
		pOut[2] = 0x02;
		pOut[3] = 0x00;
		pOut[4] = 0xFE;
		pOut[5] = 0x00;
		pOut[6] = pCmd[4];
		pOut[7] = pCmd[5];
		pOut[8] = pCmd[6];
		pOut[9] = value;
		//printf("DEBUG READ: 0x%04X-0x%02X\n\r", (unsigned short)pCmd[6], value);
		IsNVTDebugActive = 1;
		IIC0_INT_EN &= ~INTE1;
		return 10;
	}
	else if(pCmd[4] == NVT_WR_SCALER){
		WriteIIC560(addr,pCmd[7]);
		//printf("SCALER WR:0x%04X DATA:0x%02X\n\r", addr, (unsigned short)pCmd[7]);	
	}
	else if(pCmd[4] == NVT_WR_EEPROM){
		Write24C16(addr,pCmd[7]);
		//printf("EEPROM WR:0x%04X DATA:0x%02X\n\r", addr, (unsigned short)pCmd[10]);	
	}
	else if(pCmd[4] == NVT_WR_IIC){
	}
	else return 0;
	
	IsNVTDebugActive = 1;
	IIC0_INT_EN &= ~INTE1;
	return 1;
}
#endif