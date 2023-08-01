#ifndef __NVTDEBUG_H__
#define __NVTDEBUG_H__

#include "OSD_Tab.H"

#define NVT_HW_DEBUG

#define NVT_WR_SCALER		0x80
#define NVT_RD_SCALER		0x81
#define NVT_WR_EEPROM		0x82
#define NVT_RD_EEPROM		0x83
#define NVT_WR_IIC			0x84
#define NVT_RD_IIC			0x85

extern xdata unsigned char IsNVTDebugActive;

unsigned char NVTHWDebug(unsigned char *pCmd, unsigned char *pOut);

#endif