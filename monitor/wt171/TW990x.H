/****************************************************************
Filename  	: TW990x.h

Function	:  Color Decoder header

*****************************************************************/
#ifndef _TW990x_H
#define _TW990x_H


//***************  TW990X Registor **************************
#define TW99_ID			0x00
#define TW99_CSTATUS	0x01
#define TW99_INFORM		0x02
#define TW99_OPFORM		0x03
#define TW99_HDELAY		0x04
#define TW99_POLARITY	0x05
#define TW99_ACNTL		0x06
#define TW99_CROP_HI	0x07
#define TW99_VDELAY_LO	0x08
#define TW99_VACTIVE_LO 0x09
#define TW99_HDELAY_LO 	0x0A
#define TW99_HACTIVE_LO 0x0B
#define TW99_CNTRL1		0x0C
#define TW99_VSCALE_LO 	0x0D
#define TW99_SCALE_HI	0x0E
#define TW99_HSCALE_LO 	0x0F
#define TW99_BRIGHT		0x10
#define TW99_CONTRAST  	0x11
#define TW99_SHARP		0x12
#define TW99_SAT_U		0x13
#define TW99_SAT_V		0x14
#define TW99_HUE		0x15
#define TW99_SHARP2		0x16

#define TW99_VSHARP		0x17			// smpark 20030730

#define TW99_CORING		0x18
#define TW99_VBICNTL	0x19
#define TW99_CC_STATUS 	0x1A
#define TW99_CC_DATA	0x1B
#define TW99_SDT		0x1C
#define TW99_SDTR		0x1D
#define TW99_GPIO		0x1E
#define TW99_TEST		0x1F
#define TW99_CLMPG		0x20
#define TW99_IAGC		0x21
#define TW99_AGCGAIN	0x22
#define TW99_PEAKWT		0x23
#define TW99_CLMPL		0x24
#define TW99_SYNCT		0x25
#define TW99_MISSCNT	0x26
#define TW99_PCLAMP		0x27
#define TW99_VCNTL		0x28
#define TW99_VCNTL2		0x29
#define TW99_CKILL		0x2A
#define TW99_COMB		0x2B
#define TW99_LD_HCNTL	0x2C
#define TW99_MISC1		0x2D
#define TW99_MISC2		0x2E
#define TW99_MISC3		0x2F
#define TW99_MACRODET 	0x30
#define TW99_CLCNTL2	0x31
#define TW99_FILLDATA	0x32
#define TW99_VBICNTL1	0x33
#define TW99_VBICNTL2	0x34
#define TW99_MISC4		0x35
#define TW99_SLI_LEVEL	0x36
#define TW99_WSS1		0x37
#define TW99_WSS2		0x38
#define TW99_CSTATUS3  	0x39
#define TW99_HREF		0x3A

//***************  TW9903 Registor **************************
#define TW99_CLMPMODE 	0x3B

//***************  TW9908 Registor **************************
#define TW99_RGBCNTL	0x3C
#define TW99_QCLAMP		0x3D
#define TW99_SAGCGAIN	0x3E
#define TW99_FBGAIN		0x3F
#define TW99_SBRIGHT	0x40
#define TW99_SCONTRAST 	0x41
#define TW99_SCBGAIN	0x42
#define TW99_SCRGAIN	0x43
#define TW99_SHUE		0x44  


void AVDecoder_Init(void);
void SetAV_Brightness(void);
void SetAV_Contrast(void);
void SetAV_Saturation(void);
void SetAV_Tint(void);
void SetAV_Sharpness(void);
void AVDecoderSleep(void);
void putss(BYTE value);
void	SetBlueScrren(BYTE MenuVal);
void TVColorSet(void);
void SaveCurrentColorToUser();

#endif
