/***********************************************************************/
/*             Novatek MicroElectronics Corp.                          */
/*    2F, No. 3,Innovation Road 1, Science-Based Industrial Park,      */
/*    HsinChu 300,Taiwn, R.O.C.                                        */
/*    TEL:886-3-567-0889       FAX:886-3-577-0132                      */
/*    All Rights Reserved                                              */
/***********************************************************************/
/***********************************************************************/
/*    F63XDEF.h                                                        */
/*    Release Date:2000/12/17      Last Maintenance:2003/05/06         */
/*    Original Version:1.0.00      Last Version:1.2.00                 */
/*    Coding By:Alvin Lin          Maintenance By:Alvin Lin            */
/***********************************************************************/
//#ifndef _F63XREG_H
//#define _F63XREG_H
#include "MyDef.h"
//IO PORT
Byte volatile xdata PTA_REG      _at_ 0xf000;       // R/W
Byte volatile xdata PTB_REG      _at_ 0xf001;       // R/W
Byte volatile xdata PTC_REG      _at_ 0xf002;       // R/W
Byte volatile xdata PTD_REG      _at_ 0xf003;       // R/W
Byte volatile xdata PTE_REG	 	 _at_ 0xf004;	    // R/W
Byte volatile xdata RDPA_REG     _at_ 0xf005;       // R/W
Byte volatile xdata RDPB_REG     _at_ 0xf006;       // R/W
Byte volatile xdata RDPC_REG     _at_ 0xf007;       // R/W
Byte volatile xdata RDPD_REG     _at_ 0xf008;       // R/W
Byte volatile xdata RDPE_REG     _at_ 0xf009;       // R/W

//WATCHDOG TIMER
Byte volatile xdata CLRWDT       _at_ 0xf00a;       // W

//AD CONVERTER
Byte volatile xdata ADC_CON      _at_ 0xf00b;       // W
Byte volatile xdata ADC0_REG     _at_ 0xf00c;       // R
Byte volatile xdata ADC1_REG     _at_ 0xf00d;       // R
Byte volatile xdata ADC2_REG     _at_ 0xf00e;       // R
Byte volatile xdata ADC3_REG     _at_ 0xf00f;       // R

//PWM
Byte volatile xdata ENPWM_LB     _at_ 0xf010;       // W
Byte volatile xdata ENPWM_HB     _at_ 0xf011;       // W
Byte volatile xdata PWM0_REG     _at_ 0xf012;       // R/W
Byte volatile xdata PWM1_REG     _at_ 0xf013;       // R/W
Byte volatile xdata PWM2_REG     _at_ 0xf014;       // R/W
Byte volatile xdata PWM3_REG     _at_ 0xf015;       // R/W
Byte volatile xdata PWM4_REG     _at_ 0xf016;       // R/W
Byte volatile xdata PWM5_REG     _at_ 0xf017;       // R/W
Byte volatile xdata PWM6_REG     _at_ 0xf018;       // R/W
Byte volatile xdata PWM7_REG     _at_ 0xf019;       // R/W 
Byte volatile xdata PWM8_REG     _at_ 0xf01a;       // R/W 
Byte volatile xdata PWM9_REG     _at_ 0xf01b;       // R/W
 
//DDC0
Byte volatile xdata DDC_CTL0     _at_ 0xf01C;       // W
Byte volatile xdata DDC_ADDR0    _at_ 0xf01d;       // W

//DDC1
Byte volatile xdata DDC_CTL1     _at_ 0xf01e;       // W
Byte volatile xdata DDC_ADDR1    _at_ 0xf01f;       // W

//IIC0
Byte volatile xdata IIC0_CFG     _at_ 0xf039;       // R
Byte volatile xdata IIC0_STATUS  _at_ 0xf03A;       // W
Byte volatile xdata INTIIC0_EN   _at_ 0xf03B;       // W
Byte volatile xdata INTIIC0_FLG  _at_ 0xf03C;       // W
Byte volatile xdata INTIIC0_CLR  _at_ 0xf03D;       // R/W
Byte volatile xdata IIC0_TXDATA  _at_ 0xf03E;       // W
Byte volatile xdata IIC0_RXDATA  _at_ 0xf03F;       // W
Byte volatile xdata IIC0_ADDR    _at_ 0xf040;       // W

//IIC1
Byte volatile xdata IIC1_CFG     _at_ 0xf041;       // R
Byte volatile xdata IIC1_STATUS  _at_ 0xf042;       // W
Byte volatile xdata INTIIC1_EN   _at_ 0xf043;       // W
Byte volatile xdata INTIIC1_FLG  _at_ 0xf044;       // W
Byte volatile xdata INTIIC1_CLR  _at_ 0xf045;       // R/W
Byte volatile xdata IIC1_TXDATA  _at_ 0xf046;       // W
Byte volatile xdata IIC1_RXDATA  _at_ 0xf047;       // W
Byte volatile xdata IIC1_ADDR    _at_ 0xf048;       // W

//INT
Byte volatile xdata INT_SRC      _at_ 0xf020;       // R
Byte volatile xdata INTEXT_FLG   _at_ 0xf021;       // R
Byte volatile xdata INTEXT_EN    _at_ 0xf022;       // R/W

//FLASH MEMORY reserved 
Byte volatile xdata ISP_REG      _at_ 0xf049;       // R/W
Byte volatile xdata FLASH_BUF    _at_ 0xf04A;       // R/W

//Extended Control function
Byte volatile xdata EXT_FLG	 	_at_ 0xf04F;	   // R

//#endif

