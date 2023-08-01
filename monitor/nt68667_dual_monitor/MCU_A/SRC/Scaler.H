#ifndef _Scaler_H
#define _Scaler_H

#include "mydef.h"

extern code unsigned short H_ActiveTab[];
extern code unsigned short V_ActiveTab[];
extern code unsigned short PanelTypeTab[];

extern unsigned short GetHActive(unsigned char ucRes);
extern unsigned short GetVActive(unsigned char ucRes);
void InitScaler(void);
void TCONInit(void);
void UpdatePresetData(void);
void SetADC_Phase(void);
void SetADC_PLL(void);
void SetScaler(void);
void ForceToBackground(unsigned char color);
void SetDisplayNormal(void);
void PowerSaving(void);
void ScalerPowerDown(void);
void ScalerPowerUp(void);
void SetHP(void);
void SetVP(void);
void SetDPLL(void);
void SetContrast(void);
void SetBrightness(void);
void SetPanelIDX(void);
void LoadADC_Gain(void);
void SetVolume(void);
void SetStartDPLL(unsigned long);
void WritePage560(unsigned char,unsigned char,unsigned char *);
//void SetScalerOffset(void);
void WriteIIC560(unsigned short addr,unsigned char ch);
void WriteWordIIC560(unsigned short addr,unsigned short value);
unsigned char ReadIIC560(unsigned short addr);
unsigned short ReadWordIIC560(unsigned short addr);
#if PBusProtocol
void SetDataPortAddr(void);
void SetDataPortData(unsigned char Data);
unsigned char GetDataPortData(void);
#endif
void SetInterface(void);
void CheckRegPage(unsigned short);
void InputSourceSelect(void);
void ChangeScallerSetting(void);
void SetFreeRun(void);
void ScalerON(void);
void SetContrast(void);
void DVIBandWidthDetection(void);
//#if PanelID == CMO_M190E5_L0E  //neo 060811
void ScalerOutputON(bit);
void ScalerOutputOFF(void);
//#endif
void ReadGamma(void);

#endif
