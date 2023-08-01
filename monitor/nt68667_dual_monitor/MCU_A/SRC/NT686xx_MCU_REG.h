/*----------------------------------------*/
/* NT68670_MCU System Register Declare		  */
/* Date : 2006/06/23					  */
/*----------------------------------------*/
#ifndef _NT686xx_MCU_REG_H_
#define _NT686xx_MCU_REG_H_
//#define SysRegOffset    0xf000
//#include "declare.h"

extern xdata unsigned char volatile SC_StarAddress;
extern xdata unsigned char volatile SC_SYNC_INT_FLAG1;
extern xdata unsigned char volatile SC_INDEX_CTRL;
extern xdata unsigned char volatile SC_INDEX_ADDR_LI;
extern xdata unsigned char volatile SC_INDEX_ADDR_HI;
extern xdata unsigned char volatile SC_INDEX_DATA;
extern xdata unsigned char volatile SC_RegPage;
extern xdata unsigned char volatile SC_ACE_DATA_PORT;

/* General I/O Port Control Registers */
extern xdata unsigned char volatile PortA;
	#define PA0   0x01
	#define PA1   0x02
	#define PA2   0x04
	#define PA3   0x08
	#define PA4   0x10
	#define PA5   0x20
	#define PA6   0x40
	#define PA7   0x80

extern xdata unsigned char volatile PortB;
	#define PB0   0x01
	#define PB1   0x02
	#define PB2   0x04
	#define PB3   0x08
	#define PB4   0x10
	#define PB5   0x20
	#define PB6   0x40
	#define PB7   0x80

extern xdata unsigned char volatile PortC;
	#define PC0   0x01
	#define PC1   0x02
	#define PC2   0x04
	#define PC3   0x08
	#define PC4   0x10
	#define PC5   0x20
	#define PC6   0x40
	#define PC7   0x80

extern xdata unsigned char volatile PortD;
	#define PD0   0x01
	#define PD1   0x02
	#define PD2   0x04
	#define PD3   0x08
	#define PD4   0x10
	#define PD5   0x20
	#define PD6   0x40

extern xdata unsigned char volatile PortE;
	#define PE0   0x01
	#define PE1   0x02

/* GPIO R/W Direction Control */
extern xdata unsigned char volatile RDPA_REG;
extern xdata unsigned char volatile RDPB_REG;
extern xdata unsigned char volatile RDPC_REG;
extern xdata unsigned char volatile RDPD_REG;
extern xdata unsigned char volatile RDPE_REG;


/* Watch-Dog Timer */
extern xdata unsigned char volatile CLRWDT;
	#define clrwdt   0x55

/* A/D Converter */
extern xdata unsigned char volatile ADC_CON;             // (-W-) : $00
	#define STRT_ADC  0x80                  // Start A to D Convert
	#define EN_ADC3   0x08                  // Enable ADC3
	#define EN_ADC2   0x04                  // Enable ADC2
	#define EN_ADC1   0x02                  // Enable ADC1
	#define EN_ADC0   0x01                  // Enable ADC0
extern xdata unsigned char volatile ADC_REG[4];  // (-R-) : ADC0 Value
	#define CMP_ADC   0x80                  // (-R-): Complete ADC


/* PWM D/A Converters */
extern xdata unsigned char volatile ENPWM_LB;  // (-W-) : Enable PWM01-PWM00
extern xdata unsigned char volatile ENPWM_HB;  // (-W-) : Enable PWM09-PWM02
extern xdata unsigned char volatile PWM_REG[10];


/* DDC Port-0 PB4,PB5 */
extern xdata unsigned char volatile DDC_CTRL_0;
	#define EN_DDC		0x80
	#define WPT_DDC		0x40
	#define LEN_256		0x20
	#define MODE_DDC2	0x10
	#define MODE_DDC	0x10
	#define CLR_PTR		0x02
	#define CLR_UPD		0x01
	#define UPD_DDC		0x01
extern xdata unsigned char volatile DDC_ADDR_0;
	#define VALID_B31	0xe0
	#define ADDR_B31	0x0e

/* DDC Port-1 PB6,PB7 */
extern xdata unsigned char volatile DDC_CTRL_1;
extern xdata unsigned char volatile DDC_ADDR_1;


/* Interrupt Sources */
extern xdata unsigned char volatile INT_SRC;
	#define INTIIC0_IRQ		0x20
	#define INTEXT_IRQ		0x10
	#define INTIIC1_IRQ		0x02
	#define INT_SC			0x01


/* External Interrupt */
extern xdata unsigned char volatile INTEXT_FLG;
extern xdata unsigned char volatile INTEXT_EN;
	#define INTE1		0x02
	#define INTE0		0x01
	#define INTE1_EDG	0x20
	#define INTE0_EDG	0x10
extern xdata unsigned char volatile INTSC_EN;
	#define SC_EN		0x01

/*I2C Port-0 (PB4,PB5) Control Register*/
extern xdata unsigned char volatile IIC0_CFG;
	#define PRENACK		0x80
	#define SEND_ACK	0x40
	#define STOP		0x20
	#define RESTART		0x10
	#define IIC_400K	0x0c
	#define IIC_200K	0x08
	#define IIC_100K	0x04
	#define IIC_50K		0x00
	#define MASTER		0x02
	#define WAIT_GEN	0x01
extern xdata unsigned char volatile IIC0_STATUS;
	#define DOWRITE		0x80
	#define DOREAD		0x40
	#define TXIN_NULL	0x20
	#define TX_NULL		0x10
	#define RXIN_FULL	0x08
	#define RX_FULL		0x04
	#define BUS_START	0x02
	#define BUS_STOP	0x01
extern xdata unsigned char volatile IIC0_INT_EN;
extern xdata unsigned char volatile IIC0INT_FLG;
	#define INTA			0x80
	#define INTTX			0x40
	#define INTRX			0x20
	#define INTNAK			0x10
	#define INTLOST			0x08
	#define SEND_START		0x02
	#define SEND_STOP		0x01
extern xdata unsigned char volatile IIC0INT_CLR;
	#define SET_NO_DATA_IN	0x04
	#define CLR_FIFO		0x02
extern xdata unsigned char volatile IIC0_TXDATA;
//extern xdata unsigned char volatile volatile IIC0_RXDATA;
extern xdata unsigned char volatile IIC0_RXDATA;
extern xdata unsigned char volatile IIC0_ADDR;
	#define ENIIC		0x01

/*I2C Port-1 (PB6,PB7) Control Register*/
extern xdata unsigned char volatile IIC1_CFG;
extern xdata unsigned char volatile IIC1_STATUS;
extern xdata unsigned char volatile IIC1_INT_EN;
extern xdata unsigned char volatile IIC1INT_FLG;
extern xdata unsigned char volatile IIC1INT_CLR;
extern xdata unsigned char volatile IIC1_TXDATA;
extern xdata unsigned char volatile IIC1_RXDATA;
extern xdata unsigned char volatile IIC1_ADDR;


/* Flash Memory */
extern xdata unsigned char volatile ISP_REG;
	#define ISP_FLG		0x02
	#define ISP_CH		0x01
extern xdata unsigned char volatile FLASH_BUF;
extern xdata unsigned char volatile CPU_CLK;
extern xdata unsigned char volatile BANK_SET;
extern xdata unsigned char volatile DDC_THRES;
	#define DIS_DDCTHR	0x10
extern xdata unsigned char volatile SC_HW_RST;
	#define PBUS_EN		0x10
	#define SC_RST		0x01

extern xdata unsigned char SC_SR;
extern xdata unsigned char HDCP_MUX;

extern xdata unsigned char volatile LDO_ADJ;
	// NT68670
	#define INT_SC			0x01
	#define SC_EN			0x01
	#define DIS_DDCTHR		0x10
	#define PBUS_EN			0x10
	#define SC_LOSS         0x80
	#define SC_RST			0x01
	#define LDO0				0x01
	#define LDO1				0x02
extern xdata unsigned char volatile CURR_ADJ1;
extern xdata unsigned char volatile CURR_ADJ2;
	#define	Tjnp_fe2p_cache	0x80
	#define	Tm_spi_ext		0x40
	#define	CURR_SPI_LEVEL3	0x30
	#define	CURR_SPI_LEVEL2	0x20
	#define	CURR_SPI_LEVEL1	0x10
	#define	CURR_SPI_LEVEL0	0x00
	#define	CURR_P3_LEVEL3	0x0c
	#define	CURR_P3_LEVEL2	0x08
	#define	CURR_P3_LEVEL1	0x04
	#define	CURR_P3_LEVEL0	0x00
	#define	CURR_PE_LEVEL3	0x03
	#define	CURR_PE_LEVEL2	0x02
	#define	CURR_PE_LEVEL1	0x01
	#define	CURR_PE_LEVEL0	0x00
extern xdata unsigned char volatile SLEW_CTL;

extern xdata unsigned char volatile SRAMstart;
extern xdata unsigned char volatile SRAMend;

extern xdata unsigned char volatile DDCPtr0;					//  (R/W) : $07 
extern xdata unsigned char volatile DDCPtr1;					//  (R/W) : $07 

#endif
