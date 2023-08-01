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
#ifndef _F63XREG_H
#define _F63XREG_H

//IO PORT
extern Byte volatile xdata PTA_REG;      
extern Byte volatile xdata PTB_REG;      
extern Byte volatile xdata PTC_REG;      
extern Byte volatile xdata PTD_REG;      
extern Byte volatile xdata PTE_REG;	 	 
extern Byte volatile xdata RDPA_REG;     
extern Byte volatile xdata RDPB_REG;     
extern Byte volatile xdata RDPC_REG;     
extern Byte volatile xdata RDPD_REG;     
extern Byte volatile xdata RDPE_REG;     

//WATCHDOG TIMER
extern Byte volatile xdata CLRWDT;       

//AD CONVERTER
extern Byte volatile xdata ADC_CON;      
extern Byte volatile xdata ADC0_REG;     
extern Byte volatile xdata ADC1_REG;     
extern Byte volatile xdata ADC2_REG;     
extern Byte volatile xdata ADC3_REG;     

//PWM
extern Byte volatile xdata ENPWM_LB;     
extern Byte volatile xdata ENPWM_HB;     
extern Byte volatile xdata PWM0_REG;     
extern Byte volatile xdata PWM1_REG;     
extern Byte volatile xdata PWM2_REG;     
extern Byte volatile xdata PWM3_REG;     
extern Byte volatile xdata PWM4_REG;     
extern Byte volatile xdata PWM5_REG;     
extern Byte volatile xdata PWM6_REG;     
extern Byte volatile xdata PWM7_REG;     
extern Byte volatile xdata PWM8_REG;     
extern Byte volatile xdata PWM9_REG;     
 
//DDC0
extern Byte volatile xdata DDC_CTL0;     
extern Byte volatile xdata DDC_ADDR0;    

//DDC1
extern Byte volatile xdata DDC_CTL1;     
extern Byte volatile xdata DDC_ADDR1;    

//IIC0
extern Byte volatile xdata IIC0_CFG;     
extern Byte volatile xdata IIC0_STATUS;  
extern Byte volatile xdata INTIIC0_EN;   
extern Byte volatile xdata INTIIC0_FLG;  
extern Byte volatile xdata INTIIC0_CLR;  
extern Byte volatile xdata IIC0_TXDATA;  
extern Byte volatile xdata IIC0_RXDATA;  
extern Byte volatile xdata IIC0_ADDR;    

//IIC1
extern Byte volatile xdata IIC1_CFG;     
extern Byte volatile xdata IIC1_STATUS;  
extern Byte volatile xdata INTIIC1_EN;   
extern Byte volatile xdata INTIIC1_FLG;  
extern Byte volatile xdata INTIIC1_CLR;  
extern Byte volatile xdata IIC1_TXDATA;  
extern Byte volatile xdata IIC1_RXDATA;  
extern Byte volatile xdata IIC1_ADDR;    

//INT
extern Byte volatile xdata INT_SRC;      
extern Byte volatile xdata INTEXT_FLG;   
extern Byte volatile xdata INTEXT_EN;    

//FLASH MEMORY reserved 
extern Byte volatile xdata ISP_REG;      
extern Byte volatile xdata FLASH_BUF;    

//Extended Control function
extern Byte volatile xdata EXT_FLG;	 	
#endif

