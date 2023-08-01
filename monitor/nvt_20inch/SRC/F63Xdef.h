/***********************************************************************/
/*             Novatek MicroElectronics Corp.                          */
/*    2F, No. 3,Innovation Road 1, Science-Based Industrial Park,      */
/*    HsinChu 300,Taiwn, R.O.C.                                        */
/*    TEL:886-3-567-0889       FAX:886-3-577-0132                      */
/*    All Rights Reserved                                              */
/***********************************************************************/
/***********************************************************************/
/*    F63Xdef.h                                                        */
/*    Release Date:2000/12/17      Last Maintenance:2003/05/06         */
/*    Original Version:1.0.00      Last Version:1.2.00                 */
/*    Coding By:Alvin Lin          Maintenance By:Alvin Lin            */
/***********************************************************************/
#ifndef _F63XDEF_H
#define _F63XDEF_H

#define SysRegOffset    0xf000
#define PA0             0x01       
#define PA1             0x02       
#define PA2             0x04       
#define PA3             0x08       
#define PA4             0x10       
#define PA5             0x20       
#define PA6             0x40       
#define PA7             0x80       
#define PB0             0x01       
#define PB1             0x02       
#define PB2             0x04       
#define PB3             0x08       
#define PB4             0x10       
#define PB5             0x20       
#define PB6             0x40       
#define PB7             0x80       
#define PC0             0x01       
#define PC1             0x02       
#define PC2             0x04       
#define PC3             0x08       
#define PC4             0x10       
#define PC5             0x20       
#define PC6             0x40       
#define PC7             0x80       
#define PD0             0x01       
#define PD1             0x02       
#define PD2             0x04       
#define PD3             0x08       
#define PD4             0x10       
#define PD5             0x20       
#define PD6             0x40       
#define PE0             0x01       
#define PE1             0x02       

#define RDPA_0          0x01       
#define RDPA_1          0x02       
#define RDPA_2          0x04       
#define RDPA_3          0x08       
#define RDPA_4          0x10       
#define RDPA_5          0x20       
#define RDPA_6          0x40       
#define RDPA_7          0x80       
#define RDPB_0          0x01       
#define RDPB_1          0x02       
#define RDPB_2          0x04       
#define RDPB_3          0x08       
#define RDPB_4          0x10       
#define RDPB_5          0x20       
#define RDPB_6          0x40       
#define RDPB_7          0x80       
#define RDPC_0          0x01       
#define RDPC_1          0x02       
#define RDPC_2          0x04       
#define RDPC_3          0x08       
#define RDPC_4          0x10       
#define RDPC_5          0x20       
#define RDPC_6          0x40       
#define RDPC_7          0x80       
#define RDPD_0          0x01       
#define RDPD_1          0x02       
#define RDPD_2          0x04       
#define RDPD_3          0x08       
#define RDPD_4          0x10       
#define RDPD_5          0x20       
#define RDPE_0          0x01       
#define RDPE_1          0x02       

#define WDT_CLEAR	0x55
#define WDT_DISABLE	0xAA	//not support in NT68F63XES

#define STRT_ADC        0x80       
#define EN_ADC          0x10       
#define EN_ADC3         0x08       
#define EN_ADC2         0x04       
#define EN_ADC1         0x02       
#define EN_ADC0         0x01       
#define CMP_ADC         0x80       

#define EN_PWM9         0x80       
#define EN_PWM8         0x40       
#define EN_PWM7         0x20       
#define EN_PWM6         0x10       
#define EN_PWM5         0x08       
#define EN_PWM4         0x04       
#define EN_PWM3         0x02       
#define EN_PWM2         0x01       
#define EN_PWM1         0x02       
#define EN_PWM0         0x01       

#define EN_DDC          0x80       
#define WPT_DDC         0x40       
#define LEN_EDID        0x20       
#define CLR_PTR         0x02       
#define CLR_UPD         0x01       
#define UPD_DDC         0x01       
#define VALID_3         0x80       
#define VALID_2         0x40       
#define VALID_1         0x20       
#define ADDR_3          0x08       
#define ADDR_2          0x04       
#define ADDR_1          0x02       

#define INT_IIC0	0x20
#define INT_EXT		0x10
#define INT_IIC1	0x02
#define INTE1           0x02       
#define INTE0           0x01       

#define CLR_INTE1	0x02
#define CLR_INTE0	0x01


#define INTE1_EDG       0x20       
#define INTE0_EDG       0x10       

#define PRENACK		0x80
#define SEND_ACK	0x40
#define STOP		0x20
#define RESTART		0x10
#define RB1		0x08
#define RB0		0x04
#define MASTER		0x02
#define WAIT		0x01
#define WRITE 		0x80
#define READ 		0x40
#define TXDATA_NULL	0x20
#define TX_NULL		0x10
#define RXDATA_FULL	0x08
#define RX_FULL		0x04
#define BUS_START	0x02
#define BUS_STOP	0x01
#define INTA		0x80
#define INTTX		0x40
#define INTRX 		0x20
#define INTNAK 		0x10
#define INTLOST 	0x08
#define CLR_TX_FIFO	0x04
#define CLR_FIFO	0x02
#define START_GEN 	0x02
#define STOP_GEN	0x01
#define ENIIC		0x01
#define ENIIC0		0x01
#define ENIIC1		0x01

#define ISP_FLG         0x02       
#define ISP_CH          0x01       

#define LOW_PWR		0x01
#endif


    
