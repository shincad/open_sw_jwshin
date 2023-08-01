#ifndef _Scaler_H
#define _Scaler_H

#define AutoPhaseOffset 8

#ifdef X17	//defined in Keil-c project
#define DT16A	0x00	//17"  
#endif
#ifdef X15	//defined in Keil-c project
#define DT16A	0x10	//15"	swap A/B port RGB
#endif
#ifdef X19
#define DT16A	0x00	//17"
#endif
#ifdef X21
#define DT16A	0x00	//21"
#endif

#define DTSSC	0x09	//enable Spread spectrum
//Power Control1
#define PU_RSDS		0x80
#define PU_LVDS		0x40
#define WARM_RST 	0x20
#define GCLK_OFF 	0x08
#define VCLK_OFF	0x04
#define DCLK_OFF	0x01
//Power Control2
#define ADC_MPU		0x80
#define PU_PLL		0x40
#define PU_HPLL 	0x20
#define PU_TMDS		0x02
#define PU_DDDS		0x01
//Reference clock 
#if 1
#define REFCLK		12000	//12MHz
#define HSYNC_CLK	(unsigned long)REFCLK*10*8	//REFCLK*10*8  Hsync reference clock
#define VSYNC_CLK	(unsigned long)REFCLK*10000/256	//REFCLK*10000/256  Vsync reference clock
#else
//#define REFCLK		CPU_CLK/1000/2
#define REFCLK		14318	//14.318MHz
#define HSYNC_CLK	(unsigned long)REFCLK*10*8	//REFCLK*10*8  Hsync reference clock
#define VSYNC_CLK	(unsigned long)REFCLK*10000/256	//REFCLK*10000/256  Vsync reference clock
//#define HSYNC_CLK	1145400L	//REFCLK*10*8  Hsync reference clock
//#define VSYNC_CLK	559297L	//REFCLK*10000/256  Vsync reference clock
#endif
//Free run screen type
#define muOSD		0x02
#define muPATTERN	0x01

extern code unsigned char TCON_Tab[];
extern code unsigned short H_ActiveTab[];
extern code unsigned short V_ActiveTab[];
extern code unsigned char PhaseTable[];
//extern code unsigned short H_ActErrTab[];
//extern code unsigned short H_DisActErrTab[];
extern code unsigned char TDA7440D_Tab[];

void InitScaler(void);
void TCONInit(void);
void UpdatePresetData(void);
void SetADC_Phase(void);
void SetADC_PLL(void);
void SetScaler(void);
void SetScalerAV(void);
void ForceToBackground(unsigned char,unsigned char,unsigned char);
void SetDisplayNormal(void);
void PowerSaving(void);
void ScalerPowerDown(void);
void ScalerPowerUp(void);
void SetHP(void);
void SetVP(void);
void SetDPLL(unsigned long dclk);
void SetSharpness(void);
void SetContrast(void);
void SetBrightness(void);
void SetInverter(void);
void LoadADC_Gain(void);
//void SetScalerEnable(void);
void SetOsdTrans();
void SetInterface();
void SetADCGain(unsigned char);
void SetADCOffset(unsigned char);
void SetLightContrast(void);
void SetLightBrightness(void);
void SetLightHS(void);
void SetLightHW(void);
void SetLightVS(void);
void SetLightVH(void);
void SetScalerMode(void);
void ADC_SEL(void);
void SetDisplayNormal_Video(void);
void LCDMute(void);
void LCDMuteOff(void);
void SetBass(void);
void	SetTreble(void);
void DVIBandWidthDetection(void);
void SetLVDS_PLL(unsigned long dclk);


//void SetVideoContrast(void);
//void SetVideoBrightness(void);
//void	SetVideoSaturation(void);
//void	SetVideoSharpness(void);
//void	SetVideoTint(void);

#endif
