//******************************************************************
//
//		Copyright (C) 2004.  NOVATEK MICROELECTRONICS CORP.
// All rights reserved.  No part of this program may be reproduced
//
//
//================================================================
//
// MODULE:  NT68670_SC_REG.h
//
// USAGE :  NT68670_SC_REG register name and bit definitions 
//
//******************************************************************
#ifndef __NT686xx_SC_REG_H__
    #define __NT686xx_SC_REG_H__

#include "MyDef.h"
    //**************************************************************
    //	         R E G I S T E R  D E F I N I T I O N S
    //**************************************************************
	#define BIT7					0x80
	#define BIT6					0x40
	#define BIT5					0x20
	#define BIT4					0x10
	#define BIT3					0x08
	#define BIT2					0x04
	#define BIT1					0x02
	#define BIT0					0x01
                        	
	#define ADC_CTRL				0x000	//0
		//#define Reserved			BIT7			
		//#define Reserved			BIT6			
		//#define Reserved			BIT5			
		#define HPLL_HSYNC_SEL		BIT4
		#define HSYNC_SEL			BIT3
		//#define Reserved			BIT2
		#define REG_VREF ADCPLL		BIT1
		//#define Reserved			BIT0
	#define RGAIN_HI				0x001	//1
	#define ADC_TEST1				0x002	//2
	#define ROFFSET					0x003	//3
	#define GGAIN_HI				0x004	//4
	#define ADC_TEST2				0x005	//5
	#define GOFFSET					0x006	//6
	#define BGAIN_HI				0x007	//7
	#define ADC_MID_CH_SEL			0x008	//8
		//#define Reserved			BIT7
		//#define Reserved			BIT6
		//#define Reserved			BIT5
		//#define Reserved			BIT4
		#define YUV_SEL0			BIT3
		#define CHANNEL_SEL			BIT2
		#define BMID				BIT1
		#define RMID				BIT0
	#define BOFFSET					0x009	//9
	//#define RESERVED				0x00A	//10
	//#define RESERVED				0x00B	//10
	//#define RESERVED				0x00C	//12
	//#define RESERVED				0x00D	//13
	#define ADC_POWER_UP			0x00E	//14
		//#define Reserved			BIT7
		//#define Reserved			BIT6
		#define BGAIN0				BIT5
		#define GGAIN0				BIT4
		#define RGAIN0				BIT3
		#define PU_BADC				BIT2
		#define PU_GADC				BIT1
		#define PU_RADC				BIT0
	//#define RESERVED				0x00F	//15
	#define ADC_BW_CTRL				0x010	//16
		//#define Reserved			BIT7
		//#define Reserved			BIT6
		//#define Reserved			BIT5
		//#define Reserved			BIT4
		//#define Reserved			BIT3
		#define ADC_BW_MASK			0x06
		//#define Reserved			BIT0
	//#define RESERVED				0x011	//17
	#define SOG_SLICER_CTRL			0x012	//18
		#define SOG_THR				0xf8
		#define EN_SOG_SLICER		BIT2
		//#define Reserved			BIT1
		//#define Reserved			BIT0
	#define ADC_VREF_TEST			0x013	//19
	#define HS_TRIG_LEVEL			0x014	//20
	//#define RESERVED				0x015	//21
	#define DVI_PIXELCLK			0x016	//22
	//#define RESERVED				0x017	//23
	#define DVI_CTRL1				0x018	//24
	#define DVI_CTRL2				0x019	//25
	#define DVI_CTRL3				0x01A	//26
	#define DVI_CTRL4				0x01B	//27
	#define DVI_CTRL5				0x01C	//28
	#define DVI_CTRL6				0x01D	//29
	#define DVI_CTRL7				0x01E	//30
	#define PRE_PATTER_CTRL			0x01F	//31
	#define GPORT_CTRL				0x020	//32
		#define GI_VSYNC_EDGE		BIT7
		#define GI_IFLD_INV			BIT6
		#define GI_MKWIN_EN			BIT5
		#define GI_WRAP_SEL			BIT4
		#define GI_HSYNC_EDGE		BIT3
		#define GI_INTE_EN			BIT2
		#define GI_SRC_SEL			BIT1
		#define GI_CAP_EN			BIT0
	#define CLAMP_BEGIN				0x021	//33
		#define CLAMP_EDG			BIT7
		#define CLAMP_POL			BIT6
		#define CLAMP_BEG_MASK		0x3F
	#define CLAMP_WIDTH				0x022	//34
		#define CLAMP_EB			BIT7
		#define CLP_CLK_SEL			BIT6
		#define CLAMP_WID_MASK		0x3F
	#define DIGITAL_CTRL			0x023	//35
		#define YPBPR_EN			BIT7
		#define CLAMP_SOURCE		BIT6
		#define HS_DEJITTER_EN		BIT5
		#define DEJITTER_RST		BIT4
		#define HCAP_DE_EN			BIT3
	//#define RESERVED				0x024	//36
	#define ADC_CK_CTRL				0x025	//37
		#define CLKI_INV			BIT6
		#define CLKI_DLY			0x0F
	#define CAP_SWAP				0x026	//38
		#define CLAMP_MASK_EN		BIT7
		//#define Reserved			BIT6
		#define CAP_RB_SWAP			BIT5
		//#define Reserved			BIT4
		//#define Reserved			BIT3
		#define CAP_BIT_SWAP		BIT2
		//#define Reserved			BIT1
		#define CAP_DATA_DLY		BIT0
	#define GI_V_DE_DLY				0x027	//39
		#define GI_DEDLY_MASK		0x70
		#define GI_VSDLY_MASK		0x0F
	//#define RESERVED				0x028	//40
	//#define RESERVED				0x029	//41
	#define GI_HMASK_BEG			0x02A	//42
	#define GI_HMASK_END			0x02B	//43
	#define GI_VMASK_BEG			0x02C	//44
	#define GI_VMASK_END			0x02D	//45
	#define GI_CAP_VBEGO_LI			0x02E	//46
	#define GI_CAP_VBEGO_HI			0x02F	//47
	#define GI_CAP_VBEGE_LI			0x030	//48
	#define GI_CAP_VBEGE_HI			0x031	//49
	#define GI_CAP_VLEN_LI 			0x032	//50
	#define GI_CAP_VLEN_HI 			0x033	//51
	#define GI_CAP_HBEG_LI			0x034	//52
	#define GI_CAP_HBEG_HI			0x035	//53
	#define GI_CAP_HWID_LI			0x036	//54
	#define GI_CAP_HWID_HI			0x037	//55
	#define GI_ALT_CTRL				0x038	//56
		#define GI_ALT_CK_INV		BIT4
		#define DE_MK_EN			BIT3
		#define CLK_MK_EN			BIT2
		#define GI_ALT_INV			BIT1
		#define GI_ALT_EN			BIT0
	#define GI_CLK_MASK_WID			0x039	//57
	//#define RESERVED				0x03A	//58
	//#define RESERVED				0x03B	//59
	#define DVI_CAP_HWID_LI			0x03C	//60
	#define DVI_CAP_HWID_HI			0x03D	//61
	#define DVI_CAP_VLEN_LI			0x03E	//62
	#define DVI_CAP_VLEN_HI			0x03F	//63
	#define VI_CTRL1				0x040	//64
		//#define Reserved			BIT7
		#define VI_BT656_EN			0x60
		#define UV_SWAP				BIT4
		#define YUV_SWAP			BIT3
		#define EXFLD_EN			BIT2
		#define VI_INTE_EN			BIT1
		#define VI_CAP_EN			BIT0
	#define VI_CTRL2				0x041	//65
		#define VI_CAP_656_AUTO		BIT5
		#define VI_MKWIN_EN			BIT4
		#define VI_WRAP_SEL			BIT3
		#define VI_SYNC_EDGE		BIT2
		#define VCAP_656_EN			BIT1
		#define HCAP_656_EN			BIT0
	#define VI_CTRL3				0x042	//66
		#define VI_656CLK_INV		BIT5
		#define VI_IFLD_INV			BIT4
		#define VI_601CLK_INV		BIT3
	#define VI_VSDLY				0x043	//67
	//#define Reserved				0x044	//68
	//#define Reserved				0x045	//69
	//#define Reserved				0x046	//70
	#define VI_HMASK_BEG			0x047	//71
	#define VI_HMASK_END			0x048	//72
	#define VI_VMASK_BEG			0x049	//73
	#define VI_VMASK_END			0x04A	//74
	#define COLOR_COFFA_LI			0x04B	//75
	#define COLOR_COFFA_HI			0x04C	//76
	#define COLOR_COFFB_LI			0x04D	//77
	#define COLOR_COFFB_HI			0x04E	//78
	#define COLOR_COFFC_LI			0x04F	//79
	#define COLOR_COFFC_HI			0x050	//80
	#define COLOR_COFFD_LI			0x051	//81
	#define COLOR_COFFD_HI			0x052	//82
	#define VI_CAP_VBEGO_LI			0x053	//83
	#define VI_CAP_VBEGO_HI			0x054	//84
	#define VI_CAP_VBEGE_LI         0x055	//85
	#define VI_CAP_VBEGE_HI         0x056	//86
	#define VI_CAP_VLEN_LI			0x057	//87
	#define VI_CAP_VLEN_HI			0x058	//88
	#define VI_CAP_HBENG_LI			0x059	//89
	#define VI_CAP_HBENG_HI			0x05A	//90
	#define VI_CAP_HWID_LI			0x05B	//91
	#define VI_CAP_HWID_HI			0x05C	//92
	//#define Reserved				0x05D	//93
	//#define Reserved				0x05E	//94
	//#define Reserved				0x05F	//95
	#define BK_H_SHAP_CTRL			0x060	//96
		#define BK_H_ASRP			BIT6
		#define BK_H_SRPSMO			BIT4
		#define BK_H_SRP			0x0F
	#define BK_CTRL1				0x061	//97
		#define GAIN_DITH_EN		BIT3
		#define GAIN_DITH_MODE		BIT2
		#define BK_CH_SEL			0x03
	#define BK_OFFSET				0x062	//98
	#define BK_GAIN					0x063	//99
	#define INTE_CTRL				0x064	//100
		#define IEXT_EN				0xE0
		#define V_INTE_TYPE			0x18
		#define H_INTE_TYPE			0x07
	#define GAMMA_CTRL				0x065	//101
		#define GAMMA_EN			BIT7
		#define TBL_8_10B_SEL		BIT6
	#define BK_V_SHAP_CTRL			0x066	//102
		#define V_INTE_SHFIT_EN		BIT5
		#define BK_V_SRP_MASK		BIT4
	//#define Reserved				0x067	//103
	#define NR_CTRL					0x068	//104
		#define NR_ROUND			BIT5
		#define NR_EDGE_DET			BIT4
		//#define Reserved			BIT3
		#define NR_TYPE				0x07
	#define NR_THR_CTRL1			0x069	//105
		#define NR_EDGE_THR			0xF0
		#define NT_THR				0x0F
	#define JITTER_CTRL				0x06A	//106
		#define JC_MAX_TPRE			0xC0
		//#define Reserved			BIT5
		#define JC_EN				BIT4
		#define JC_LEVEL			0x0F
#define NR_THR_CTRL2				0x06B	//107
	//#define Reserved				0x06C	//108
	//#define Reserved				0x06D	//109
	//#define Reserved				0x06E	//110
	//#define Reserved				0x06F	//111
	#define GPIO_CTRL				0x070	//112
		#define PWM1_EN				BIT5
		#define PWM0_EN				BIT4
	//#define Reserved				0x071	//113
	#define BP_SYNC_CTRL			0x072	//114
		#define BP_HSYNC_EN			BIT4
		//#define Reserved			BIT3
		#define REFCKO_EN			BIT2
		#define BP_HSYNC_SEL		BIT1
		#define BP_VSYNC_EN			BIT0
	//#define Reserved				0x073	//115
	#define PWM0_LCNT				0x074	//116
	#define PWM0_HCNT				0x075	//117
	#define PWM1_LCNT				0x076	//118
	#define PWM1_HCNT				0x077	//119
	#define DDC0_CTRL				0x078	//120
	#define DDC0_SLAVE_ADDR			0x079	//121
	#define DDC0_SLAVE_MASK			0x07A	//122
	#define DDC1_CTRL				0x07B	//123
	#define DDC1_SLAVE_ADDR			0x07C	//124
	#define DDC1_SLAVE_MASK			0x07D	//125
	#define PWM_CTRL1				0x07E	//126
		#define PWM1_VS_LOCK		BIT7
		#define PWM1_DIV1			0x60
		#define PWM1_CLK			BIT4
		#define PWM0_VS_LOCK		BIT3
		#define PWM0_DIV1			0x06
		#define PWM0_CLK			BIT1
	#define PWM_CTRL2				0x07F	//127
		#define PWM1_DIV2			0x06
		#define PWM0_DIV2			BIT1
	#define OSD_CTRL1				0x080	//128
		#define ROT_EN				BIT7
		#define FLIP_EN		 		BIT6
		#define MIR_EN				BIT5
		#define WIN4_EN	 			BIT4
		#define WIN3_EN				BIT3
		#define WIN2_EN				BIT2
		#define WIN1_EN				BIT1
		#define OSD_EN				BIT0
	#define OSD_HS_LI				0x081	//129
	#define OSD_HS_HI				0x082	//130
	#define OSD_HW					0x083	//131
	#define OSD_VS_LI				0x084	//132
	#define OSD_VS_HI				0x085	//133
	#define OSD_VH					0x086	//134
    #define OSD_SHIFT_ROW			0x087	//135
	#define OSD_FONT1B_ADDR_LI		0x088	//136
	#define OSD_FONT1B_ADDR_HI		0x089	//137
	#define OSD_FONT2B_ADDR_LI		0x08A	//138
	#define OSD_FONT2B_ADDR_HI		0x08B	//139
	#define OSD_FONT4B_ADDR_LI		0x08C	//140
	#define OSD_FONT4B_ADDR_HI		0x08D	//141
	#define OSD_FADE_STEP			0x08E	//142
		#define FAD_V_STEP_MASK		0xF0
		#define FAD_H_STEP_MASK		0x0F
	#define OSD_FADE_FREQ			0x08F	//143
		#define FAD_EN				BIT7
		#define FAD_VFREQ_MASK		0x78
		#define FAD_HFREQ_MASK		0x0F
		
	#define OSD_ZOOM_CTL			0x090	//144
		#define VROW_ZMEN			BIT3
		#define HROW_ZMEN			BIT2
		#define VGLOB_ZMEN			BIT1
		#define HGLOB_ZMEN			BIT0
	#define HZM_PATN_LI				0x091	//145
	#define VHZM_PATN				0x092	//146
		#define VZM_PATN_HI			0x30
		#define HZM_PATN_HI			0x0F
	#define VZM_PATN_LI				0x093	//147
	#define VZM_PATN_MI				0x094	//148
	#define VHGLOB_ZMRNG			0x095	//149
	#define VGLOB_ZMRNG1			0xC0
	#define HGLOB_ZMRNG1			0x30
	#define VGLOB_ZMRNG0			0x0C
	#define HGLOB_ZMRNG0			0x03
	#define HROW_ZMPN_BYTE0			0x096	//150
	#define HROW_ZMPN_BYTE1			0x097	//152
	#define HROW_ZMPN_BYTE2			0x098	//153
	#define HROW_ZMPN_BYTE3			0x099	//154
	#define VROW_ZMPN_BYTE0			0x09A	//155
	#define VROW_ZMPN_BYTE1			0x09B	//156
	#define VROW_ZMPN_BYTE2			0x09C	//157
	#define VROW_ZMPN_BYTE3			0x09D	//158
	#define VHROW_ZMRNG 			0x09E	//159
		#define VROW_ZMRNG_MASK		0x0C
		#define HROW_ZMRNG_MASK		0x03
	#define OSD_BLINK_CTL			0x0A0	//160
		#define OSD_BLINK			BIT7
		#define BS_BLINK			BIT6
		#define BLINK_FREQ_MASK		0x1C
		#define BLINK_RATE_MASK		0x03
	#define OSD_TRANSLUCENT_CTL		0x0A1	//161
		#define TP_LEVEL_TWO_MASK	0x38
		#define TP_LEVEL_ONE_MASK	0x07
	#define SPACE_CTL				0x0A2	//162
		#define V_FS_SEL			0x80
		#define H_FS_SEL			0x40
		#define VSPACE_MASK			0x38
		#define HSPACE_MASK			0x07
	#define OSD_WIN_GRADIENT_CTRL1	0x0A3
	#define OSD_WIN_GRADIENT_CTRL2	0x0A4
	#define WIN_SEL					0x0A5	//163
		#define WIN8_EN	 			BIT7
		#define WIN7_EN				BIT6
		#define WIN6_EN				BIT5
		#define WIN5_EN				BIT4
		#define WIN_SEL_MASK		0x07
	#define WIN_HS					0x0A6	//164
		#define WIN_HS_MASK			0x3F
	#define WIN_HE					0x0A7	//165
		#define WIN_HE_MASK			0x3F
	#define WIN_VS					0x0A8	//166
		#define WIN_VS_MASK			0x1F
	#define WIN_VE					0x0A9	//167
		#define WIN_VE_MASK			0x1F
	#define OSD_WIN_ATTR			0x0AA	//168
		#define WIN_BLEN			0x80
		#define WIN_BL_TYPE			0x60
		#define WIN_MIX				0x10
		#define WIN_SDSZ_MASK		0x0C
		#define WIN_SDEN			0x02
	#define WIN_CL					0x0AB	//169
#if NT68670B
	#define WIN_SDCL				0x0AC	//170
#else
	#define WIN_SDCL				0x0AB	//169
#endif
	#define WIN_BL_HWID				0x0AD	//171
		#define WIN_BL_HWID_MASK	0x38
		#define WIN_BL_VWID_MASK	0x07
#if NT68670B
	#define WIN_BL_RCL				0x0AC	//172
#else
	#define WIN_BL_RCL				0x0AE	//172
#endif
	#define WIN_BL_LCL				0x0AF	//173
	#define OSD_SCR_BYTE0			0x0B0	//174
	#define OSD_SCR_BYTE1			0x0B1	//175
	#define OSD_SCR_BYTE2			0x0B2	//176
	#define OSD_SCR_BYTE3			0x0B3	//177
	#define OSD_BCR_BYTE0			0x0B4	//178
	#define OSD_BCR_BYTE1			0x0B5	//179
	#define OSD_BCR_BYTE2			0x0B6	//180
	#define OSD_BCR_BYTE3			0x0B7	//181

	#define BOR_SHA_COL_01			0x0B8	//182
		#define OSD_BCR1_MASK		0xF0
		#define OSD_BCR0_MASK		0x0F
	#define BOR_SHA_COL_23			0x0B9	//183
		#define OSD_BCR3_MASK		0xF0
		#define OSD_BCR2_MASK		0x0F
	#define BOR_SHA_COL_45			0x0BA	//184
		#define OSD_BCR5_MASK		0xF0
		#define OSD_BCR4_MASK		0x0F
	#define BOR_SHA_COL_67			0x0BB	//185
		#define OSD_BCR7_MASK		0xF0
		#define OSD_BCR6_MASK		0x0F
	#define BOR_SHA_COL_89			0x0BC	//186
		#define OSD_BCR9_MASK		0xF0
		#define OSD_BCR8_MASK		0x0F
	#define BOR_SHA_COL_1011		0x0BD	//187
		#define OSD_BCR11_MASK		0xF0
		#define OSD_BCR10_MASK		0x0F
	#define BOR_SHA_COL_1213		0x0BE	//188
		#define OSD_BCR13_MASK		0xF0
		#define OSD_BCR12_MASK		0x0F
	#define BOR_SHA_COL_1415		0x0BF	//189
		#define OSD_BCR15_MASK		0xF0
		#define OSD_BCR14_MASK		0x0F
	#define BOR_SHA_COL_1617		0x0C0	//190
		#define OSD_BCR17_MASK		0xF0
		#define OSD_BCR16_MASK		0x0F
	#define BOR_SHA_COL_1819		0x0C1	//191
		#define OSD_BCR19_MASK		0xF0
		#define OSD_BCR18_MASK		0x0F
	#define BOR_SHA_COL_2021		0x0C2	//192
		#define OSD_BCR21_MASK		0xF0
		#define OSD_BCR20_MASK		0x0F
	#define BOR_SHA_COL_2223		0x0C3	//193
		#define OSD_BCR23_MASK		0xF0
		#define OSD_BCR22_MASK		0x0F
	#define BOR_SHA_COL_2425		0x0C4	//194
		#define OSD_BCR25_MASK		0xF0
		#define OSD_BCR24_MASK		0x0F
	#define BOR_SHA_COL_2627		0x0C5	//195
		#define OSD_BCR27_MASK		0xF0
		#define OSD_BCR26_MASK		0x0F
	#define BOR_SHA_COL_2829		0x0C6	//196
		#define OSD_BCR29_MASK		0xF0
		#define OSD_BCR28_MASK		0x0F
	#define BOR_SHA_COL_3031		0x0C7	//197
		#define OSD_BCR31_MASK		0xF0
		#define OSD_BCR30_MASK		0x0F

	#define OSD_H_SPLIT				0x0C8	//198
		#define H_SPL_EN			0x80
		#define SPL_HP_MASK			0x3F
	#define SPL_HW					0x0C9	//199
	#define OSD_V_SPLIT				0x0CA	//200
		#define V_SPL_EN			0x80
		#define SPL_VP_MASK			0x1F
	#define SPL_VH					0x0CB	//201
	#define OSD_FC_ATTR_LSB			0x0CC	//202
	#define OSD_FC_ATTR_MSB			0x0CD	//203
	#define OSD_CODE_FC				0x0CE	//204
	#define OSD_CODE_FC_CTL			0x0CF	//205
		#define FADE_MODE			0xC0
		#define BG_MIX_EN			0x20
		#define FG_MIX_EN			0x10
		#define BS_MIX_EN			0x08
		#define WIN_MIX_EN			0x04
		#define FC_MASK				0x02
		#define FC_EN_RDY			0x01

	#define HPLL_CTRL1				0x0D0	//208
		#define HSDDS_DEBUG_MODE	BIT7
		#define VER_COUB_BYPASS		BIT6
		#define DBL_EN				BIT5
		//#define Reserved			BIT4
		#define HSDDS_RST			BIT3
		#define OCLK_DIV			BIT2
		#define HSDDS_UNLOCK_CHK	BIT1
		//#define Reserved			BIT0
	#define HPLL_FREQ_CTRL			0x0D1	//209
		#define HSDDS_LOOP_FILTER	0x70
		#define HSDDS_DIV_CTRL		BIT3
		//#define Reserved			BIT2
		#define HPLL_FREQ_RANGE_MASK	0x03
	#define HSDDS_RATIO_LI			0x0D2	//210
	#define HSDDS_RATIO_MI			0x0D3	//211
	#define HSDDS_RATIO_HI			0x0D4	//212
	#define HPLL_PHASE_CTRL			0x0D5	//213
		//#define Reserved			BIT7
		//#define Reserved			BIT6
		//#define Reserved			BIT5
		//#define Reserved			BIT4
		#define HS_INV				BIT3
		#define HPLL_OP_LOOP		BIT2
		#define HS_QUICK_UNLOCK_CHK	BIT1
		#define HPLL_EN				BIT0
	#define HPLL_CTRL2				0x0D6	//214
		#define HPLL_LOCK_EN		BIT7
		#define HPLL_PLOOP_FIT_MASK	0x60
		#define HPLL_FLOOP_FIT0_MASK	0x18
		#define HPLL_FLOOP_FIT1_MASK	0x07
	#define HSDDS_DIVIDER_LI		0x0D7	//215
	#define HSDDS_DIVIDER_HI		0x0D8	//216
	#define HPLL_PHASE_CTRL1		0x0D9	//217
		#define CLK_DLY_SEL_MASK	0xc0
		#define HS_PHASE_STEP		0x3f
	#define HPLL_PHASE_CTRL2		0x0DA	//218
		//#define Reserved			BIT7
		//#define Reserved			BIT6
		//#define ADC_CKI_INV		BIT5
		//#define ADC_CKO_INV		BIT4
		#define ADC_CK_DELAY		0x0f
	#define HPLL_LINE_CNT			0x0DB	//219
		//#define Reserved			BIT7
		//#define Reserved			BIT6
		//#define ADC_CKI_INV		BIT5
		#define HS_LINE_CNT_SEL		0x1f
	#define HPLL_CTRL3				0x0DC	//220
		#define ADC_CK_DUTY_MASK	0xf0
		#define TMDS_CK_EN			BIT7
		#define HSDDS_COAST_EN		BIT6
		#define CAP_CKO_INV			BIT5
		#define EXT_CKIN_EN			BIT4
	#define HS_CNT_RESULT_LI		0x0DD	//221
	#define HS_CNT_RESULT_MI		0x0DE	//222
	#define HS_CNT_RESULT_HI		0x0DF	//223

	#define INDEX_CTRL				0x0E0	//224
		#define TBL_SEL_MASK		0xf0
		#define GAMMA_TBL_RED		0x00
		#define GAMMA_TBL_GREEN		0x01
		#define GAMMA_TBL_BLUE		0x02
		#define GAMMA_TBL_RGB		0x03
		#define OSD_CODE			0x04
		#define OSD_ATTR_MSB		0x05
		#define OSD_ATTR_LSB		0x06
		#define OSD_ATTR			0x07
		#define OSD_CODE_ATTR		0x08
		#define OSD_HOST_CODE_ATTR	0x09
		#define OSD_FONT_1BIT		0x0A
		#define OSD_FONT_2BIT		0x0B
		#define OSD_FONT_4BIT		0x0D
		#define DDC0_RAM			0x0E
		#define DDC1_RAM			0x0F
		#define PORT_RW				BIT3
	#define INDEX_ADDR_LI			0x0E1	//225
	#define INDEX_ADDR_HI			0x0E2	//226
	#define INDEX_DATA				0x0E3	//227
	//#define Reserved				0x0E4	//228
	//#define Reserved				0x0E5	//229
	//#define Reserved				0x0E6	//230
	//#define Reserved				0x0E7	//231
	//#define Reserved				0x0E8	//232
	//#define Reserved				0x0E9	//233
	//#define Reserved				0x0EA	//234
	//#define Reserved				0x0EB	//235
	//#define Reserved				0x0EC	//236
	//#define Reserved				0x0ED	//237
	//#define Reserved				0x0EE	//238
	//#define Reserved				0x0EF	//239
	#define DPLL_CTRL1				0x0F0	//240
		#define DDDS_DEBUG_MODE		BIT7
		//#define Reserved			BIT6
		//#define Reserved			BIT5
		//#define Reserved			BIT4
		#define DDDS_RST			BIT3
		//#define Reserved			BIT2
		#define DDDS_UNLOCK_CHK		BIT1
		#define DDDS_EN				BIT0
	#define DPLL_FREQ_CTRL			0x0F1	//241
		//#define Reserved			BIT7
		#define DDDS_LOOP_FILTER	0x70
		#define DDDS_FREQ_DIV		0x0f
	#define DDDS_RATIO_LI			0x0F2	//242
	#define DDDS_RATIO_MI			0x0F3	//243
	#define DDDS_RATIO_HI			0x0F4	//244
	#define SSC_CTRL				0x0F5	//245
		#define SSC_MODE_FREQ_MASK	0xf0
		#define SSC_RATIO_MASK		0x0e
		#define SSC_EN				BIT0
	//#define Reserved				0x0F6	//246
	//#define Reserved				0x0F7	//247
	#define GAUGE_CTRL				0x0F8	//248
		#define GAUGE_EN			BIT7
		//#define Reserved			BIT6
		//#define Reserved			BIT5
		#define GAUGE_SEL			0x18
		#define GAUGE_STEP			0x07
	#define GAUGE_AREA_SEL			0x0F9	//249
	#define GAUGE_OFFSET			0x0FA	//250
	#define GAUGE_RESULT_LI			0x0FB	//251
	#define GAUGE_RESULT_MI			0x0FC	//252
	#define GAUGE_RESULT_HI			0x0FD	//253
	//#define Reserved				0x0FE	//254


	#define PRODUCT_ID				0x100	//256
	#define POWER_CTRL1				0x101	//257
		#define Reserved			BIT7
		#define PU_LVDSA			BIT6
		#define WARM_RST			BIT5
		//#define Reserved			BIT4
		#define GCLK_OFF			BIT3
		#define VCLK_OFF			BIT2
		#define PU_LVDSB			BIT1
		#define DCLK_OFF			BIT0
	#define POWER_CTRL2				0x102	//258
		//#define Reserved			BIT7
		//#define Reserved			BIT6
		#define PU_HPLL				BIT5
		//#define Reserved			BIT4
		#define PU_ADC				BIT3
		//#define Reserved			BIT2
		#define PU_TMDS				BIT1
		#define PU_DDDS				BIT0
	//#define Reserved				0x103	//259
	//#define Reserved				0x104	//260
	//#define Reserved				0x105	//261
	#define GI_AUTO_TUNE_CTRL		0x106	//262
		//#define Reserved			BIT7
		#define GI_AUTO_MASK		BIT6
		#define GI_GAINPHS_AREA		BIT5
		#define GI_POS_DE			BIT4
		#define GI_GAINPHS_SEL		0xc0
		#define GI_GAINPHS_EN		BIT1
		#define GI_POS_EN			BIT0
	#define GI_POS_THR				0x107	//263
	#define GI_POS_VBEGO_LI			0x108	//264
	#define GI_POS_VBEGO_HI			0x109	//265
	#define GI_POS_VBEGE_LI			0x10A	//266
	#define GI_POS_VBEGE_HI			0x10B	//267
	#define GI_POS_VLEN_LI			0x10C	//268
	#define GI_POS_VLEN_HI			0x10D	//269
	#define GI_POS_HBEG_LI			0x10E	//270
	#define GI_POS_HBEG_HI			0x10F	//271
	#define GI_POS_HWID_LI			0x110	//272
	#define GI_POS_HWID_HI			0x111	//273
	#define GI_PHS_MASK				0x112	//274
	#define GI_PHS_SDIFF_LI0		0x113	//275
	#define GI_PHS_SDIFF_LI1		0x114	//276
	#define GI_PHS_SDIFF_HI0		0x115	//277
	#define GI_PHS_SDIFF_HI1		0x116	//278
	#define GI_CLK_REF_LI			0x117	//279
	#define GI_CLK_REF_HI			0x118	//280
	#define GI_CLK_RESULT			0x119	//281
		#define GI_CLK_COMP_MASK	0xc0
		#define GI_CLK_DIFF_MASK	0xc0
	//#define Reserved				0x11A	//282
	#define VI_AUTO_CTRL			0x11B	//283
		//#define Reserved			BIT7
		//#define Reserved			BIT6
		#define VI_AUTO_MASK		BIT5
		#define VI_AUTO_HREF		BIT4
		#define VI_GAIN_AREA		BIT3
		#define VI_GAIN_SEL			BIT2
		#define VI_GAIN_EN			BIT1
		#define VI_POS_EN			BIT0
	#define VI_POS_THR				0x11C	//284
	#define VI_VTOTAL_LI			0x11D	//285
	#define VI_VTOTAL_HI			0x11E	//286
	#define VI_POS_VBEGO_LI			0x11F	//287
	#define VI_POS_VBEGO_HI			0x120	//288
	#define VI_POS_VBEGE_LI			0x121	//289
	#define VI_POS_VBEGE_HI			0x122	//290
	#define VI_POS_VLEN_LI			0x123	//291
	#define VI_POS_VLEN_HI			0x124	//292
	#define VI_HTOTAL_LI			0x125	//293
	#define VI_HTOTAL_HI			0x126	//294
	#define VI_POS_HBEG_LI			0x127	//295
	#define VI_POS_HBEG_HI			0x128	//296
	#define VI_POS_HWID_LI			0x129	//297
	#define VI_POS_HWID_HI			0x12A	//298
	#define Y_MINMAX				0x12B	//299
	//#define Reserved				0x12C	//300
	//#define Reserved				0x12D	//301
	//#define Reserved				0x12E	//302
	//#define Reserved				0x12F	//303
	#define BRIGHT_FRM_CTRL			0x130	//304
		//#define Reserved			BIT7
		//#define Reserved			BIT6
		//#define Reserved			BIT5
		//#define Reserved			BIT4
		//#define Reserved			BIT3
		//#define Reserved			BIT2
		#define BRIGHT_FRM2_EN		BIT1
		#define BRIGHT_FRM1_EN		BIT0
	#define BRIGHT_FRM_SEL			0x131	//305
		//#define BRIGHT_FRM_SEL	BIT0
	#define BRIGHT_FRM_HS_LI		0x132	//306
	#define BRIGHT_FRM_HS_HI		0x133	//307
	#define BRIGHT_FRM_HW_LI		0x134	//308
	#define BRIGHT_FRM_HW_HI		0x135	//309
	#define BRIGHT_FRM_VS_LI		0x136	//310
	#define BRIGHT_FRM_VS_HI		0x137	//311
	#define BRIGHT_FRM_VH_LI		0x138	//312
	#define BRIGHT_FRM_VH_HI		0x139	//313
	#define BRIGHT_FRM_GAIN			0x13A	//314
	#define BRIGHT_FRM_OFFSET		0x13B	//315
	//#define Reserved				0x13C	//316
	//#define Reserved				0x13D	//317
	//#define Reserved				0x13E	//318
	#define DVI_CTRL8				0x13F	//319
	#define DVI_CTRL9				0x140	//320
	#define DVI_CTRL10				0x141	//321
	#define DVI_CTRL11				0x142	//322
	#define DVI_CTRL12				0x143	//323
	#define DVI_CTRL13				0x144	//324
	#define DVI_CTRL14				0x145	//325
	#define DVI_CTRL15				0x146	//326
	#define DVI_CTRL16				0x147	//327
	#define VI_HTO_RD_LI			0x14C	//332
	#define VI_HTO_RD_HI			0x14D	//333
	#define DH_ELOCK_LI				0x14E	//334
	#define DH_ELOCK_HI				0x14F	//335
	#define DISPLAY_CTRL			0x150	//336
		#define DP_BIT_SHF			BIT7
		//#define Reserved			BIT6
		//#define Reserved			BIT5
		//#define Reserved			BIT4
		#define DP_COLDEP			BIT3
		#define DP_BUSWID			BIT2
		#define DP_DE				BIT1
		#define DP_EN				BIT0
	#define DSP_VLOCK_POS_W				0x151	//337
	#define DSP_HLOCK_POS_W				0x152	//338
	//#define Reserved				0x153	//339
	#define DISPLAY_MUTE_CTRL		0x154	//340
		#define DP_PATT_MASK		0xf0
		#define PATT_BK				BIT3
		#define CBAR_EN				BIT2
		#define DP_MUTE_MASK		0x03
	//#define Reserved				0x155	//341
	#define DISPLAY_POL_CTRL		0x156	//342
		#define DDE_POL				BIT7
		#define DCLK_POL			BIT6
		#define DHS_POL				BIT5
		#define DVS_POL				BIT4
		//#define Reserved			BIT3
		//#define Reserved			BIT2
		//#define Reserved			BIT1
		//#define Reserved			BIT0
	#define DISPLAY_CLK_CTRL		0x157	//343
		#define DOUT_STAG			BIT7
		#define DCLK_SYCN_SEL		0x60
		#define DCLK_DLY			0x1f
	#define DITH_CTRL				0x158	//344
		#define DITH_MODE			0xf0
		//#define Reserved			BIT3
		#define DITH_8BIT			BIT2
		#define DITH_TURBO			BIT1
		#define DITH_EN				BIT0
	#define DITPLAY_CHANNEL			0x159	//345
		#define INT_FAST_EN			BIT7
		//#define Reserved			BIT6
		#define DP_RGB				0x07
	#define CBAR_FG					0x15a	//346
	#define DV_TOTAL_LI				0x15b	//347
	#define DV_TOTAL_HI				0x15c	//348
	#define DV_VS_WID				0x15d	//349
	#define DH_HTOTAL_LI			0x15e	//350
	#define DH_HTOTAL_HI			0x15f	//351
	#define DH_HS_WID				0x160	//352
	#define DISPLAY_BR_CTRL			0x161	//353
	#define DV_BG_BEG_LI			0x162	//354
	#define DV_BG_BEG_HI			0x163	//355
	#define DV_BG_LEN_LI			0x164	//356
	#define DV_BG_LEN_HI			0x165	//357
	#define DH_BG_BEG_LI			0x166	//358
	#define DH_BG_BEG_HI			0x167	//359
	#define DH_BG_WID_LI			0x168	//360
	#define DH_BG_WID_HI			0x169	//361
	#define DISP_SWAP				0x16A	//362
		//#define Reserved			BIT7
		//#define Reserved			BIT6
		//#define Reserved			BIT5
		#define DP_PORT_SWAP		BIT4
		#define DP_BYTE_SWAPB		BIT3
		#define DP_BYTE_SWAPA		BIT2
		#define SP_BIT_SWAPB		BIT1
		#define SP_BIT_SWAPA		BIT0
	#define DP_BG_R					0x16B	//363
	#define DP_BG_G					0x16C	//364
	#define DP_BG_B					0x16D	//365
	#define GD_WIN_CTRL				0x16E	//366
		//#define Reserved			BIT7
		#define GD_PRIO				BIT6
		#define GD_FRM_INV			BIT5
		#define GD_DEALT_SP			BIT4
		#define GD_DEALT			BIT3
		#define GD_FLD				0x06
		#define GD_EN				BIT0
	#define GDV_ACT_BEG_LI			0x16F	//367
	#define GDV_ACT_BEG_HI			0x170	//368
	#define GDV_ACT_LEN_LI			0x171	//369
	#define GDV_ACT_LEN_HI			0x172	//370
	#define GDH_ACT_BEG_LI			0x173	//371
	#define GDH_ACT_BEG_HI			0x174	//372
	#define GDH_ACT_WID_LI			0x175	//373
	#define GDH_ACT_WID_HI			0x176	//374
	#define DSP_HLOCK_POS_R			0x177	//375
	#define DSP_VLOCK_POS_R			0x178	//376
	#define VD_WIN_CTRL				0x179	//377
		//#define Reserved			BIT7
		//#define Reserved			BIT6
		//#define Reserved			BIT5
		//#define Reserved			BIT4
		//#define Reserved			BIT3
		#define VD_FLD				0x06
		#define VD_EN				BIT0
	#define VDV_ACT_BEG_LI			0x17A	//378
	#define VDV_ACT_BEG_HI			0x17B	//379
	#define VDV_ACT_LEN_LI			0x17C	//380
	#define VDV_ACT_LEN_HI			0x17D	//381
	#define VDH_ACT_BEG_LI			0x17E	//382
	#define VDH_ACT_BEG_HI			0x17F	//383
	#define VDH_ACT_WID_LI			0x180	//384
	#define VDH_ACT_WID_HI			0x181	//385
	#define DSP_HTOTAL_R			0x182	//386
	//#define Reserved				0x183	//387
	#define HR_VALUE				0x184	//388
	//#define Reserved				0x185	//389
	#define INSIDE_CTRL1			0x186	//390
	//#define Reserved				0x187	//391
	#define VCR_CTRL				0x188	//392
		//#define Reserved			BIT7
		//#define Reserved			BIT6
		//#define Reserved			BIT5
		#define SC_MUTE_DIS			BIT4
		//#define Reserved			BIT3
		//#define Reserved			BIT2
		//#define Reserved			BIT1
		#define VCR_EN				BIT0
	//#define Reserved				0x189	//393
	//#define Reserved				0x18A	//394
	//#define Reserved				0x18B	//395
	//#define Reserved				0x18C	//396
	//#define Reserved				0x18D	//397
	#define FIFO_FLAG				0x18E	//398
		//#define Reserved			BIT7
		//#define Reserved			BIT6
		//#define Reserved			BIT5
		//#define Reserved			BIT4
		//#define Reserved			BIT3
		//#define Reserved			BIT2
		#define INT_FFOV			BIT1
		#define INT_FFUN			BIT0
	#define FIFO_FLAG_EN			0x18F	//399
		//#define Reserved			BIT7
		//#define Reserved			BIT6
		//#define Reserved			BIT5
		//#define Reserved			BIT4
		//#define Reserved			BIT3
		//#define Reserved			BIT2
		#define INT_FFOV_EN			BIT1
		#define INT_FFUN_EN			BIT0
	//#define Reserved				0x190	//400
	#define INSIDE_CTRL2			0x191	//401
	//#define Reserved				0x192	//402
	//#define Reserved				0x193	//403
	//#define Reserved				0x194	//404
	//#define Reserved				0x195	//405
	#define GI_SYNC_CTRL			0x196	//406
		#define DVI_SYNC_SEL		BIT7
		#define GI_ADCHS_INV		BIT6
		#define GI_HS_SRC			0x30
		#define GI_VCNT_BIT			0x0c
		#define GI_SYNC_TYPE		0x03
	#define GI_SYNC_CTRL2			0x197	//407
		#define COAST_EN			BIT7
		#define SYNC_OUT_SEL0		BIT6
		#define GI_VRUN_EN			BIT5
		#define GI_HRUN_EN			BIT4
		#define GI_VSO_POL			BIT3
		#define GI_HSO_POL			BIT2
		#define GI_VSO_EN			BIT1
		#define GI_HSO_EN			BIT0
	#define GI_FIELD_WIN			0x198	//408
		#define GI_FLD_WINEDN		0xf0
		#define GI_FLD_WINBEG		0x0f
	#define GI_SYNC_CTRL3			0x199	//409
		//#define Reserved			BIT7
		#define SYNC_OUT_SEL1		BIT6
		#define HSYNC_CNT_MOD		BIT5
		//#define Reserved			BIT4
		//#define Reserved			BIT3
		//#define Reserved			BIT2
		#define GI_FLD_EDGE			BIT1
		#define GI_FLD_INV			BIT0
	#define GI_SYNC_STATUS			0x19A	//410
		#define GI_VCNT_OV			BIT7
		#define GI_HCNT_OV			BIT6
		#define GI_CSPRE			BIT5
		#define GI_VPRE				BIT4
		#define GI_HPRE				BIT3
		#define GI_INTE				BIT2
		#define GI_VPOL				BIT1
		#define GI_HPOL				BIT0
	#define GI_HCNT_LI				0x19B	//411
	#define GI_HCNT_HI				0x19C	//412
	#define GI_VCNT_LI				0x19D	//413
	#define GI_VCNT_HI				0x19E	//414
	#define HREE_DIV_LI				0x19F	//415
	#define HREE_DIV_HI				0x1A0	//416
	#define VREE_DIV_LI				0x1A1	//417
	#define VREE_DIV_HI				0x1A2	//418
	#define HPRE_THR_LO				0x1A3	//419
	#define HPRE_THR_HI				0x1A4	//420
	#define VPRE_THR_LO				0x1A5	//421
	#define VPRE_THR_HI				0x1A6	//422
	#define HCNT_THR				0x1A7	//423
	#define V_CHANG_CTRL			0x1A8	//424
		#define H_CHANG_CNT			0xe0
		#define VCNT_THR			0x1f
	#define SYNC_INT_EN1			0x1A9	//425
		#define INT_INV				BIT7
		//#define Reserved			BIT6
		#define INT_VFREQ_EN		BIT5
		#define INT_HFREQ_EN		BIT4
		#define INT_VPOL_EN			BIT3
		#define INT_HPOL_EN			BIT2
		#define INT_VEDGE_EN		BIT1
		#define INT_HEDGE_EN		BIT0
	#define SYNC_INT_EN2			0x1AA	//426
		//#define Reserved			BIT7
		//#define Reserved			BIT6
		//#define Reserved			BIT5
		#define INT_DVIPRE_EN		BIT4
		#define INT_ISPRE_EN		BIT3
		#define INT_CSPRE_EN		BIT2
		#define INT_VPRE_EN			BIT1
		#define INT_HPRE_EN			BIT0
	#define SYNC_INT_FLAG1			0x1AB	//427
		//#define Reserved			BIT7
		//#define Reserved			BIT6
		#define INT_VFREQ			BIT5
		#define INT_HFREQ			BIT4
		#define INT_VPOL			BIT3
		#define INT_HPOL			BIT2
		#define INT_VEDGE			BIT1
		#define INT_HEDGE			BIT0
	#define SYNC_INT_FLAG2			0x1AC	//428
		//#define Reserved			BIT7
		//#define Reserved			BIT6
		//#define Reserved			BIT5
		#define INT_DVIPRE			BIT4
		#define INT_ISPRE			BIT3
		#define INT_CSPRE			BIT2
		#define INT_VPRE			BIT1
		#define INT_HPRE			BIT0
	#define DVI_STATUS				0x1AD	//429
		//#define Reserved			BIT7
		//#define Reserved			BIT6
		//#define Reserved			BIT5
		//#define Reserved			BIT4
		//#define Reserved			BIT3
		//#define Reserved			BIT2
		//#define Reserved			BIT1
		#define DVI_SCDT			BIT0
	//#define Reserved				0x1AE	//430
	//#define Reserved				0x1AF	//431
	//#define Reserved				0x1B0	//432
	#define GI_HS_WID				0x1B1	//433
	#define GI_VS_WID				0x1B2	//434
	#define PRE_COAST				0x1B3	//435
	#define POS_COAST				0x1B4	//436
	//#define Reserved				0x1B5	//437
	//#define Reserved				0x1B6	//438
	//#define Reserved				0x1B7	//439
	#define LVDS_CTRL				0x1B8	//440
		//#define Reserved			BIT7
		//#define Reserved			BIT6
		#define LVDS_LEVEL			0x38
		#define LVDS_ICO			0x06
		#define LVDS_RFB			BIT0
	//#define Reserved				0x1B9~0x1CF	//430~463
	#define INSIDE_CTRL3			0x1c6
	#define SRGB_CTRL				0x1D0	//464
		//#define Reserved			BIT7
		//#define Reserved			BIT6
		#define SRGB_DITH_EN		BIT5
		#define RANDOM_DITH_EN		BIT4
		#define SRGB_FORCE_UPD		BIT3
		#define SRGB_BK_SEL			0x06
		#define SRGB_EN				BIT0
	#define SRGB_COEF_R_LI			0x1D1	//465
	#define SRGB_COEF_R_HI			0x1D2	//466
	#define SRGB_COEF_G_LI			0x1D3	//467
	#define SRGB_COEF_G_HI			0x1D4	//468
	#define SRGB_COEF_B_LI			0x1D5	//469
	#define SRGB_COEF_B_HI			0x1D6	//470
	#define SRGB_COEF_OFFSET		0x1D7	//471
	#define SRGB_DITH_CTRL			0x1D8	//472
		#define SRGB_DITH_10		0x0c
		#define SRGB_DITH_01		0x03
	#define MISC_O_RD_LI			0x1DC	//476
	#define MISC_O_RD_HI			0x1DD	//477
	#define MISC_E_RD_LI			0x1DE	//478
	#define MISC_E_RD_HI			0x1DF	//479
	
	#define ADC_OP_CURRENT			0x1F1	//497
		#define OP_R				0x30
		#define OP_G				0x0C
		#define OP_B				0x03
	#define LVDS_MISC_CTRL1			0x1F5	//501
	#define LVDS_MISC_CTRL2			0x1F6	//502
	#define LVDS_MISC_CTRL3			0x1F7	//503
	#define LVDS_MISC_CTRL4			0x1F8	//504

	#define REG_PAGE_CTRL			0x1ff
		#define PD_LV1				BIT7
		#define PD_LV3				BIT6


#endif // __NT68670_SC_REG_H__

