#ifndef _ROM_MAP_H_
#define  _ROM_MAP_H_

extern code unsigned char EEP_GeoMap[],EEP_SyncMap[],EEP_FreqMap[];
extern unsigned char code KeyTable[16],DsubEdidTab[],DviEdidTab[];
extern unsigned char code McuRegTab[];
extern code unsigned char YPbPrSyncMap[];
//
#define ep_Mode_Data			0x300
#define ep_Sync_Data			0x500
#define ep_Shape_Offset			0x500
#define	ep_Vpos_Offset			0x501
#define ep_Hpos_Offset			0x502
#define ep_Clock_Offset			0x504
#define ep_Reso_Offset			0x506
#define ep_Phase_Offset			0x507
#define ep_DDC_Analog			0x000
#define ep_DDC_DVI				0x080
//

#define ep_FirmWare_Ver			0x200
#define ep_FirmWare_Rev		0x201
#define ep_Status				0x202
#define ep_Language				0x203
#define ep_Color_Ptr				0x204
#define ep_Sync_Source			0x205
#define ep_User_Ptr				0x206
#define ep_Input_CH_Sys			0x208	//Air/Cable +ChSystem 8

#define ep_ContMax				0x20a
#define ep_ContMin				0x20b
#define ep_BrigMax				0x20c
#define ep_BrigMin				0x20d
#define ep_Volume				0x20e
#define ep_VCMVol				0x20f
#define ep_Contrast				0x210
#define ep_Brightness			0x211
#define ep_BackLight				0x212
#define ep_sRGB_Saturation		0x213
#define ep_sRGB_Tint				0x214
#define ep_sRGB_Backlight		0x215
#define ep_DVI_Contrast			0x216
#define ep_Video_Contrast		0x217
#define ep_Video_Brightness		0x218
#define ep_Video_Saturation		0x219
#define ep_Video_Tint			0x21a
#define ep_Video_Shapness		0x21b
#define ep_Osd_Effect			0x21c
#define ep_Osd_Timer			0x21d
#define ep_OsdH_Pos				0x21e
#define ep_OsdV_Pos				0x21f
#define ep_ADC_R_Offset			0x220
#define ep_ADC_G_Offset			0x221
#define ep_ADC_B_Offset			0x222
#define ep_ADC_R_Gain			0x223
#define ep_ADC_G_Gain			0x224
#define ep_ADC_B_Gain			0x225
#define ep_Color1_R				0x226
#define ep_Color1_G				0x227
#define ep_Color1_B				0x228
#define ep_Color2_R				0x229
#define ep_Color2_G				0x22a
#define ep_Color2_B				0x22b
#define ep_Color3_R				0x22c
#define ep_Color3_G				0x22d
#define ep_Color3_B				0x22e
#define ep_Color4_R				0x22f
#define ep_Color4_G				0x230
#define ep_Color4_B				0x231
#define ep_Color5_R				0x232
#define ep_Color5_G				0x233
#define ep_Color5_B				0x234
#define ep_Color6_R				0x235
#define ep_Color6_G				0x236
#define ep_Color6_B				0x237
#define ep_Light_Contrast			0x238
#define ep_Light_Bright			0x239
#define ep_Light_HSLSB			0x23a
#define ep_Light_HSMSB			0x23b
#define ep_Light_HWLSB			0x23c
#define ep_Light_HWMSB			0x23d
#define ep_Light_VSLSB			0x23e
#define ep_Light_VSMSB			0x23f
#define ep_Light_VHLSB			0x240
#define ep_Light_VHMSB			0x241
#define ep_BkLightTime_Offset	0x2fc
#define ep_YPbPr_R_Offset		0x242
#define ep_YPbPr_G_Offset		0x243
#define ep_YPbPr_B_Offset		0x244
#define ep_Bass					0x246
#define ep_Treble				0x247

#define ep_RGBStatus			0x249		// +jwshin 060908
#endif
