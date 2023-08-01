/*----------------------------------------*/
/* NT68F632 System Register Declare		  */
/* Date : 2002/10/08					  */
/*----------------------------------------*/
#include "NT686xx_MCU_REG.H"

xdata unsigned char volatile SC_StarAddress _at_ 0x8000;
xdata unsigned char volatile SC_SYNC_INT_FLAG1 _at_ 0x80ab;
xdata unsigned char volatile SC_ACE_DATA_PORT _at_ 0x80b2;
xdata unsigned char volatile SC_INDEX_CTRL _at_ 0x80e0;
xdata unsigned char volatile SC_INDEX_ADDR_LI _at_ 0x80e1;
xdata unsigned char volatile SC_INDEX_ADDR_HI _at_ 0x80e2;
xdata unsigned char volatile SC_INDEX_DATA _at_ 0x80e3;
xdata unsigned char volatile SC_RegPage _at_ 0x80ff;

/* General I/O Port Control Registers */
xdata unsigned char volatile PortA _at_ 0xf000;
xdata unsigned char volatile PortB _at_ 0xf001;
xdata unsigned char volatile PortC _at_ 0xf002;
xdata unsigned char volatile PortD _at_ 0xf003;
xdata unsigned char volatile PortE _at_ 0xf004;
/* GPIO R/W Direction Control */
xdata unsigned char volatile RDPA_REG _at_ 0xf005;
xdata unsigned char volatile RDPB_REG _at_ 0xf006;
xdata unsigned char volatile RDPC_REG _at_ 0xf007;
xdata unsigned char volatile RDPD_REG _at_ 0xf008;
xdata unsigned char volatile RDPE_REG _at_ 0xf009;

/* Watch-Dog Timer */
xdata unsigned char volatile CLRWDT _at_ 0xf00a;

/* A/D Converter */
xdata unsigned char volatile ADC_CON _at_ 0xf00b;             // (-W-) : $00
xdata unsigned char volatile ADC_REG[4] _at_ 0xf00c;  // (-R-) : ADC0 Value

/* PWM D/A Converters */
xdata unsigned char volatile ENPWM_LB _at_ 0xf010;  // (-W-) : Enable PWM01-PWM00
xdata unsigned char volatile ENPWM_HB _at_ 0xf011;  // (-W-) : Enable PWM09-PWM02
xdata unsigned char volatile PWM_REG[10] _at_ 0xf012;

/* DDC Port-0 PB4,PB5 */
xdata unsigned char volatile DDC_CTRL_0 _at_ 0xf01c;
xdata unsigned char volatile DDC_ADDR_0 _at_ 0xf01d;

/* DDC Port-1 PB6,PB7 */
xdata unsigned char volatile DDC_CTRL_1 _at_ 0xf01e;
xdata unsigned char volatile DDC_ADDR_1 _at_ 0xf01f;


/* Interrupt Sources */
xdata unsigned char volatile INT_SRC _at_ 0xf020;

/* External Interrupt */
xdata unsigned char volatile INTEXT_FLG _at_ 0xf021;
xdata unsigned char volatile INTEXT_EN _at_ 0xf022;
xdata unsigned char volatile INTSC_EN _at_ 0xf024;

/*I2C Port-0 (PB4,PB5) Control Register*/
xdata unsigned char volatile IIC0_CFG _at_ 0xf039;
xdata unsigned char volatile IIC0_STATUS _at_ 0xf03a;
xdata unsigned char volatile IIC0_INT_EN _at_ 0xf03b;
xdata unsigned char volatile IIC0INT_FLG _at_ 0xf03c;
xdata unsigned char volatile IIC0INT_CLR _at_ 0xf03d;
xdata unsigned char volatile IIC0_TXDATA _at_ 0xf03e;
xdata unsigned char volatile IIC0_RXDATA _at_ 0xf03f;
xdata unsigned char volatile IIC0_ADDR _at_ 0xf040;

/*I2C Port-1 (PB6,PB7) Control Register*/
xdata unsigned char volatile IIC1_CFG _at_ 0xf041;
xdata unsigned char volatile IIC1_STATUS _at_ 0xf042;
xdata unsigned char volatile IIC1_INT_EN _at_ 0xf043;
xdata unsigned char volatile IIC1INT_FLG _at_ 0xf044;
xdata unsigned char volatile IIC1INT_CLR _at_ 0xf045;
xdata unsigned char volatile IIC1_TXDATA _at_ 0xf046;
xdata unsigned char volatile IIC1_RXDATA _at_ 0xf047;
xdata unsigned char volatile IIC1_ADDR _at_ 0xf048;

/* Flash Memory */
xdata unsigned char volatile ISP_REG _at_ 0xf049;
xdata unsigned char volatile FLASH_BUF _at_ 0xf04a;
xdata unsigned char volatile CPU_CLK _at_ 0xf04c;
xdata unsigned char volatile BANK_SET _at_ 0xf04d;
xdata unsigned char volatile DDC_THRES _at_ 0xf04e;
xdata unsigned char volatile SC_HW_RST _at_ 0xf04f;
xdata unsigned char volatile LDO_ADJ _at_ 0xf050;
xdata unsigned char volatile SC_SR		_at_ 0xf055;
xdata unsigned char volatile HDCP_MUX	_at_ 0xf056;
xdata unsigned char volatile CURR_ADJ1 _at_ 0xf060;
xdata unsigned char volatile CURR_ADJ2 _at_ 0xf061;
xdata unsigned char volatile SLEW_CTL _at_ 0xf062;

xdata unsigned char volatile SRAMstart _at_ 0xF400;
xdata unsigned char volatile SRAMend   _at_ 0xF600;

xdata unsigned char volatile DDCPtr0 _at_ 0xF800;					//  (R/W) : $07 
xdata unsigned char volatile DDCPtr1 _at_ 0xF900;					//  (R/W) : $07 

