#ifndef _BOARD_H_
#define  _BOARD_H_

#include "mydef.H"

////////////////////////
#define BIT_0	0x01
#define BIT_1	0x02
#define BIT_2	0x04
#define BIT_3	0x08
#define BIT_4	0x10
#define BIT_5	0x20
#define BIT_6	0x40
#define BIT_7	0x80


////////////////////////
#define RESV       0

#define IN    1
#define OUT   0

#define HIGH  1
#define LOW   0

#define ADC_START     1
#define ADC_STOP      0
#define EN   1
#define DIS  0

#define PWM_ENABLED   1
#define PWM_DISABLED  0

#define DDC_ENABLED   1
#define DDC_DISABLED  0
#define DDC_WPT       1
#define DDC_RW        0
#define DDC_EDID_256  1
#define DDC_EDID_128  0
#define DDC_EDID_MOD  1
#define DDC_CLR_PTR   1
#define DDC_CLR_UPR   1
#define DDC_NO_EFFECT 0
////////////////////////

////////////////////////////////////////
#define BITS_TO_BYTE(p7,p6,p5,p4,p3,p2,p1,p0) ((p7<<7)|(p6<<6)|(p5<<5)|(p4<<4)|(p3<<3)|(p2<<2)|(p1<<1)|p0)
////////////////////////////////////////


#define DEFAULT_CLRWDT     0x55


void LED_GrnOn(void);
void LED_GrnOff(void);
void LED_RedOn(void);
void LED_RedOff(void);
void BackLightOn(void);
void BackLightOff(void);
void PanelPowerOff(void);
void PanelPowerOn(void);
void ResetOff(void);
void ResetOn(void);
void AUDIO_MUTE(void);
void AUDIO_On(void);
void AMP_STBY(void);
void AMP_On(void);
void EEP_WP_OFF(void);
void EEP_WP_ON(void);
//void EDID_WP_OFF(void);
//void EDID_WP_ON(void);
bit IsPanelPowerOn(void);
bit IsBackLightOn(void);
bit IsVGAconnected(void);
bit IsDVIconnected(void);

void	Button_En_SelA(void);			// +jwshin 120223
void  Button_En_SelB(void);
void RGB_SW1_RGB1(void);
void RGB_SW1_RGB2(void);

void SEL1_GrnOn(void);
void SEL1_GrnOff(void);

void SEL2_GrnOn(void);
void SEL2_GrnOff(void);


#if SCALAR_BOARD==PCBA_Q80x67
/*************************************************
	P C B _ Q 8 0 x 6 7 
**************************************************/
/////////////////////////////////////////
//
//			PWM
//
/////////////////////////////////////////
//#define PWM_BRIGHTNESS		PWM_REG[9]					//-jwshin 111214
#define PWM_VOLUME			PWM_REG[9]
#define PWM_PANELIDX		PWM_REG[6]

//------------------ DVI DDC 사용을 위해, Use24C02 Remark...
//#define Use24C02						// +jwshin 110414

#define DEFAULT_PWMEN_1_0  BITS_TO_BYTE(RESV     ,RESV     ,RESV     ,RESV     ,RESV     ,RESV     ,DIS,EN)
//#define DEFAULT_PWMEN_9_2  BITS_TO_BYTE(EN, DIS, DIS,EN,DIS,DIS,DIS,DIS)
//+jwshin 120223    
#define DEFAULT_PWMEN_9_2  BITS_TO_BYTE(DIS, DIS, DIS,DIS,DIS,DIS,DIS,DIS)
#define DEFAULT_PWM0       0x00
#define DEFAULT_PWM1       0x00
#define DEFAULT_PWM2       0x00
#define DEFAULT_PWM3       0x00
#define DEFAULT_PWM4       0x00
#define DEFAULT_PWM5       0x00
#define DEFAULT_PWM6       0x00
#define DEFAULT_PWM7       0x00
#define DEFAULT_PWM8       0x00
#define DEFAULT_PWM9       0x00
#ifdef Use24C02
#define DEFAULT_DDC_CTRL_0 BITS_TO_BYTE(DDC_DISABLED, DDC_WPT, DDC_EDID_128, 1, RESV, RESV, DDC_NO_EFFECT, DDC_NO_EFFECT)
#define DEFAULT_DDC_CTRL_1 BITS_TO_BYTE(DDC_DISABLED, DDC_WPT, DDC_EDID_128, 1, RESV, RESV, DDC_NO_EFFECT, DDC_NO_EFFECT)
#else
#define DEFAULT_DDC_CTRL_0 BITS_TO_BYTE(1, 1, 0, 1, RESV, RESV, DDC_NO_EFFECT, DDC_NO_EFFECT)
#define DEFAULT_DDC_CTRL_1 BITS_TO_BYTE(1, 1, 0, 1, RESV, RESV, DDC_NO_EFFECT, DDC_NO_EFFECT)
#endif
#define DEFAULT_DDC_ADDR_0 0x00
#define DEFAULT_DDC_ADDR_1 0x00

#define DEFAULT_INT_SRC    0x00
#define DEFAULT_INTEXT_FLG 0x00
#define DEFAULT_INTEXT_EN  0x00

/////////////////////////////////////////
//
//			ADC
//
/////////////////////////////////////////

#define DEFAULT_ADC_CON    BITS_TO_BYTE(ADC_START,RESV,RESV,RESV, EN, DIS, EN, EN)
#define DEFAULT_ADC0_REG   0x00
#define DEFAULT_ADC1_REG   0x00
#define DEFAULT_ADC2_REG   0x00
#define DEFAULT_ADC3_REG   0x00
#define WaitADConversion()		while((ADC_REG[3] & BIT_7) == 0){}
// -jwshin 110418
//#define IsAC_PowerOff()		((ADC_REG[3] & 0x7f) < 0x40)	//(!(PortD & BIT_0))		// lower then half voltage
#define IsAC_PowerOff()			0			// +jwshin 110418

#define Key1_Input()			(ADC_REG[0] & 0x7f)
#define Key2_Input()			(ADC_REG[1] & 0x7f)
#define GetPowerKeyStatus()		(PortC & BIT_5)

//---------------------------------------- +jwshin 120223 Button Select
#define Button_Select_A()			(PortA & BIT_4)
#define Button_Select_B()			(PortA & BIT_3)
//-----------------------------------------------------------------
/*
/////////////////////////////////////////
//
// Default to MCU Registers
//
/////////////////////////////////////////
#define CVDD_Reset() {unsigned char *ppp;
ppp = &RDPD_REG;
*ppp= *ppp | BIT_2;
}
*/
#define BLFastOff() {unsigned char __tmp__; \
                     __tmp__ = PortC;       \
                     __tmp__ |= RDPC_REG;   \
                     __tmp__ |= BIT_4;     \
                     PortC = __tmp__;       \
                    }

////////////////////////////////////////
#define GetHsyncLevel (PortD & BIT_6)	//need fast speed. so use #define.
#define GetVsyncLevel (PortA & BIT_3)	//need fast speed. so use #define.

/////////////////////////////////////////
#define PORTA_DEFAULT_OUT  BITS_TO_BYTE(HIGH,HIGH,LOW,HIGH,HIGH,LOW,LOW,LOW)
#define PORTB_DEFAULT_OUT  BITS_TO_BYTE(HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH)
#define PORTC_DEFAULT_OUT  BITS_TO_BYTE(HIGH,HIGH,HIGH,HIGH ,HIGH ,LOW,HIGH,LOW)
#define PORTD_DEFAULT_OUT  BITS_TO_BYTE(HIGH,HIGH,HIGH,HIGH,LOW ,LOW ,HIGH,HIGH)
#define PORTE_DEFAULT_OUT  BITS_TO_BYTE(LOW ,LOW ,LOW ,LOW ,LOW ,LOW ,LOW, LOW)

//#define PORTA_DEFAULT_DIR  BITS_TO_BYTE(OUT,  IN,   OUT,   OUT,  OUT,   OUT,   OUT,   OUT )
#define PORTA_DEFAULT_DIR  BITS_TO_BYTE(OUT,  OUT,   OUT,   IN,  IN,   OUT,   OUT,   OUT )			// +jwshin 120223
#define PORTB_DEFAULT_DIR  BITS_TO_BYTE(  IN,  IN,  IN,  IN,  IN,  IN,  IN,  IN)
#define PORTC_DEFAULT_DIR  BITS_TO_BYTE(IN,IN,IN,OUT,IN,IN,OUT,OUT )
#define PORTD_DEFAULT_DIR  BITS_TO_BYTE(OUT,  IN,   OUT,   OUT,  OUT,OUT,OUT,OUT)
#define PORTE_DEFAULT_DIR  BITS_TO_BYTE(OUT,OUT,OUT,OUT,OUT,OUT,OUT,OUT)




#elif SCALAR_BOARD==PCBA_Q50x50
/*************************************************
	P C B _ Q 5 0 x 5 0 
**************************************************/
/////////////////////////////////////////
//
//			PWM
//
/////////////////////////////////////////
//#define PWM_BRIGHTNESS		PWM_REG[9]
#define PWM_VOLUME			PWM_REG[9]
#define PWM_PANELIDX		PWM_REG[6]


#define DEFAULT_PWMEN_1_0  BITS_TO_BYTE(RESV     ,RESV     ,RESV     ,RESV     ,RESV     ,RESV     ,DIS,DIS)
#define DEFAULT_PWMEN_9_2  BITS_TO_BYTE(DIS, DIS, DIS,DIS,DIS,DIS,DIS,DIS)
#define DEFAULT_PWM0       0x80
#define DEFAULT_PWM1       0x80
#define DEFAULT_PWM2       0x80
#define DEFAULT_PWM3       0x80
#define DEFAULT_PWM4       0x80
#define DEFAULT_PWM5       0x80
#define DEFAULT_PWM6       0x80
#define DEFAULT_PWM7       0x80
#define DEFAULT_PWM8       0x80
#define DEFAULT_PWM9       0x80
#ifdef Use24C02
#define DEFAULT_DDC_CTRL_0 BITS_TO_BYTE(DDC_DISABLED, DDC_WPT, DDC_EDID_128, 1, RESV, RESV, DDC_NO_EFFECT, DDC_NO_EFFECT)
#define DEFAULT_DDC_CTRL_1 BITS_TO_BYTE(DDC_DISABLED, DDC_WPT, DDC_EDID_128, 1, RESV, RESV, DDC_NO_EFFECT, DDC_NO_EFFECT)
#else
#define DEFAULT_DDC_CTRL_0 BITS_TO_BYTE(1, 1, 0, 1, RESV, RESV, DDC_NO_EFFECT, DDC_NO_EFFECT)
#define DEFAULT_DDC_CTRL_1 BITS_TO_BYTE(1, 1, 0, 1, RESV, RESV, DDC_NO_EFFECT, DDC_NO_EFFECT)
#endif
#define DEFAULT_DDC_ADDR_0 0x00
#define DEFAULT_DDC_ADDR_1 0x00
#define DEFAULT_INT_SRC    0x00

#define DEFAULT_INTEXT_FLG 0x00
#define DEFAULT_INTEXT_EN  0x00

/////////////////////////////////////////
//
//			ADC
//
/////////////////////////////////////////

#define DEFAULT_ADC_CON    BITS_TO_BYTE(ADC_START,RESV,RESV,RESV, EN, DIS, EN, EN)
#define DEFAULT_ADC0_REG   0x00
#define DEFAULT_ADC1_REG   0x00
#define DEFAULT_ADC2_REG   0x00
#define DEFAULT_ADC3_REG   0x00
#define WaitADConversion()		while((ADC_REG[3] & BIT_7) == 0){}
#define IsAC_PowerOff()		((ADC_REG[3] & 0x7f) < 0x40)	//(!(PortD & BIT_0))		// lower then half voltage
#define Key1_Input()			(ADC_REG[0] & 0x7f)
#define Key2_Input()			(ADC_REG[1] & 0x7f)
#define GetPowerKeyStatus()		(P34)

/*
/////////////////////////////////////////
//
// Default to MCU Registers
//
/////////////////////////////////////////
#define CVDD_Reset() {unsigned char *ppp;
ppp = &RDPD_REG;
*ppp= *ppp | BIT_2;
}
*/
#define BLFastOff() {unsigned char __tmp__; \
                     __tmp__ = PortB;       \
                     __tmp__ |= RDPB_REG;   \
                     __tmp__ |= BIT_2;     \
                     PortB = __tmp__;       \
                    }

////////////////////////////////////////
#define GetHsyncLevel (PortD & BIT_6)	//need fast speed. so use #define.
#define GetVsyncLevel (PortA & BIT_3)	//need fast speed. so use #define.

/////////////////////////////////////////
#define PORTA_DEFAULT_OUT  BITS_TO_BYTE(LOW,HIGH,LOW,HIGH,LOW,LOW,LOW,HIGH)
#define PORTB_DEFAULT_OUT  BITS_TO_BYTE(LOW,LOW,HIGH,LOW,HIGH,HIGH,HIGH,HIGH)
#define PORTC_DEFAULT_OUT  BITS_TO_BYTE(LOW,LOW,LOW,HIGH ,HIGH ,LOW,LOW,LOW)
#define PORTD_DEFAULT_OUT  BITS_TO_BYTE(LOW,LOW,LOW,LOW,LOW ,LOW ,LOW,LOW)
#define PORTE_DEFAULT_OUT  BITS_TO_BYTE(LOW ,LOW ,LOW ,LOW ,LOW ,LOW ,LOW, LOW)

#define PORTA_DEFAULT_DIR  BITS_TO_BYTE(OUT,  OUT,   OUT,   OUT,  OUT,   OUT,   OUT,   OUT )
#define PORTB_DEFAULT_DIR  BITS_TO_BYTE(  IN,  IN,  IN,  OUT,  IN,  OUT,  IN,  IN)
#define PORTC_DEFAULT_DIR  BITS_TO_BYTE(IN, IN, IN, IN, IN, IN, OUT, OUT )
#define PORTD_DEFAULT_DIR  BITS_TO_BYTE(OUT,  IN,   IN,   IN,  IN, IN, IN, IN)
#define PORTE_DEFAULT_DIR  BITS_TO_BYTE(OUT,OUT,OUT,OUT,OUT,OUT,IN,IN)

#endif




#endif
