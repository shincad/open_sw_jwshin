#include "atc.h"
#include "TMS32INT.H"					/* interrupt vector define */

int	*ATC_BUS	= (int *)0x816800;		/* atc-mb base address */
int int_latch=0x80;						/* Altera EPLD Internal latch */

#define ATC_MODE	0x400				/* control address */
#define INT_DFF		0x500
#define A_IORD		0x400
#define B_IORD		0x500
#define AB_CLK		0x700
#define SW_CLK		1
#define SYS_CLK		0

#define DSP_BUS		0					/* control bits define */
#define ATC_A_ALE  	1
#define ATC_B_ALE	2
#define A_WR		4
#define B_WR		5
#define PCLK_MODE	6
#define SW_RESET	7

/* ATC DI2 Port define */
#define ATC_DI2_IC10	0x80			/* Relay control bit2 bit1 bit0 */
#define ATC_DI2_IC23	0x82			/* LED control bit7 ~  bit0 */
#define ATC_DI2_IC24	0x84			/* .. */
#define ATC_DI2_IC25	0x86			/* .. */
int ATC_DI2_A_LED2,ATC_DI2_A_LED1,ATC_DI2_A_LED0;

#define ATC_DI2_IC21	0x88			/* DI Data set */
#define ATC_DI2_IC17	0x8a			/* DI-A Data read port bit2(P2) bit1(P1) bit0(P0) */
#define ATC_DI2_IC18	0x8c			/* DI-B Data read port bit2(P2) bit1(P1) bit0(P0) */
int ATC_DI2_A_DI2,ATC_DI2_A_DI1,ATC_DI2_A_DI0;
int ATC_DI2_B_DI2,ATC_DI2_B_DI1,ATC_DI2_B_DI0;

int Count_x = 0;						/* global count */
int	int_flag=0xff;						/* interrupt flag */

int temp;								/* general temp register */

int bit_set(int reg,int bit)
{
	int x;
	x = 1<<bit;
	return(reg|x);
}

int bit_clear(int reg,int bit)
{
	int x;
	x = 1<<bit;
	return(reg&(~x));
}

void bit_set_int_latch(int bit)
{
		int x;
		x = 1<<bit;			
		int_latch |= x;	
}

void bit_clear_int_latch(int bit)
{
		int x;
		x = 1<<bit;			
		int_latch &= (~x);	
}

void sel_pclk(int x)
{
	if(x=SYS_CLK)						/* H1/N */
	{
		bit_clear_int_latch(PCLK_MODE);
		ATC_BUS[ATC_MODE] = int_latch;	/*  */		
	}
	else
	{
		bit_set_int_latch(PCLK_MODE);
		ATC_BUS[ATC_MODE] = int_latch;	/* S/W CLK */
	}	
}

void ab_clk()
{
		ATC_BUS[AB_CLK] = 0xff;			/* Null data out  */		
}

void atc_a_ale(int addr)
{
		bit_clear_int_latch(DSP_BUS);
		ATC_BUS[ATC_MODE] = int_latch;	/* buff enable */
			
		ATC_BUS[INT_DFF]=addr;			/* data set */
		
		bit_clear_int_latch(ATC_A_ALE);
		ATC_BUS[ATC_MODE] = int_latch;	/* ale set */
			
		bit_clear_int_latch(ATC_A_ALE);
		ATC_BUS[ATC_MODE] = int_latch;	/* ale clr */
							
		bit_set_int_latch(ATC_A_ALE);
		ATC_BUS[ATC_MODE] = int_latch;	/* ale set */	

		bit_set_int_latch(DSP_BUS);
		ATC_BUS[ATC_MODE] = int_latch;	/* buff disable */											 	
}

void atc_b_ale(int addr)
{
		bit_clear_int_latch(DSP_BUS);
		ATC_BUS[ATC_MODE] = int_latch;	/* buff enable */
			
		ATC_BUS[INT_DFF]=addr;				/* data set */
	
		bit_set_int_latch(ATC_B_ALE);	
		ATC_BUS[ATC_MODE] = int_latch;	/* ale set */	
		
		bit_clear_int_latch(ATC_B_ALE);
		ATC_BUS[ATC_MODE] = int_latch;	/* ale clr */					
		
		bit_set_int_latch(ATC_B_ALE);
		ATC_BUS[ATC_MODE] = int_latch;	/* ale set */	
		
		bit_set_int_latch(DSP_BUS);
		ATC_BUS[ATC_MODE] = int_latch;	/* buff disable */											 	
}

void atc_a_write(int addr,int data)
{
		atc_a_ale(addr);
		
		bit_clear_int_latch(DSP_BUS);
		ATC_BUS[ATC_MODE] = int_latch;	/* buff enable */
			
		ATC_BUS[INT_DFF]=data;			/* data set */
			
		bit_clear_int_latch(A_WR);		
		ATC_BUS[ATC_MODE] = int_latch;	/* a-iowr clr */
		
		bit_set_int_latch(A_WR);	
		ATC_BUS[ATC_MODE] = int_latch;	/* a-iowr set */
		
		bit_clear_int_latch(A_WR);		
		ATC_BUS[ATC_MODE] = int_latch;	/* a-iowr clr */	
				
		bit_set_int_latch(DSP_BUS);
		ATC_BUS[ATC_MODE] = int_latch;	/* buff disable */								 	
}

void atc_b_write(int addr,int data)
{
		atc_b_ale(addr);
		
		bit_clear_int_latch(DSP_BUS);
		ATC_BUS[ATC_MODE] = int_latch;	/* buff enable */
			
		ATC_BUS[INT_DFF]=data;			/* data set */
			
		bit_clear_int_latch(B_WR);		
		ATC_BUS[ATC_MODE] = int_latch;	/* b-iowr clr */
		
		bit_set_int_latch(B_WR);	
		ATC_BUS[ATC_MODE] = int_latch;	/* b-iowr set */
		
		bit_clear_int_latch(B_WR);		
		ATC_BUS[ATC_MODE] = int_latch;	/* b-iowr clr */
					
		bit_set_int_latch(DSP_BUS);
		ATC_BUS[ATC_MODE] = int_latch;	/* buff disable */						 	
}

int atc_a_rd(int addr)
{		
		atc_a_ale(addr);		
		return(ATC_BUS[A_IORD]&0xff);				 	
}

int atc_b_rd(int addr)
{		
		atc_b_ale(addr);			
		return(ATC_BUS[B_IORD]&0xff);				 	
}

void atc_all_reset()
{
	bit_clear_int_latch(SW_RESET);
	ATC_BUS[ATC_MODE] = int_latch;
	
	bit_set_int_latch(SW_RESET);
	ATC_BUS[ATC_MODE] = int_latch;
	/*
	Delay_ms(50);
	*/
	bit_clear_int_latch(SW_RESET);
	ATC_BUS[ATC_MODE] = int_latch;
}


/* ==================================================================== */
/*	atc di2  control routine											*/
/* ==================================================================== */
int atc_di2_a_di0(int bit)
{	
	int x;
	x = 1<<bit;
	atc_a_write(ATC_DI2_IC21,x);
	x= atc_a_rd(ATC_DI2_IC17)&0x1;		/* Port-A Address */
	atc_a_write(ATC_DI2_IC21,0x0);		/* 불안해서 넣어 보았다 그라니 OK */
	Delay_us(10);
	return(x);			
}

int atc_di2_b_di0(int bit)
{	
	int x;
	x = 1<<bit;
	atc_b_write(ATC_DI2_IC21,x);
	x= atc_b_rd(ATC_DI2_IC18)&0x1;		/* Port-B address */
	atc_b_write(ATC_DI2_IC21,0x0);		/* 불안해서 넣어 보았다 그라니 OK */
	Delay_us(10);
	return(x);			
}

int atc_di2_a_di1(int bit)
{	
	int x;
	x = 1<<bit;
	atc_a_write(ATC_DI2_IC21,x);
	x = atc_a_rd(ATC_DI2_IC17)&0x2;
	atc_a_write(ATC_DI2_IC21,0x0);
	x>>=1;  
	Delay_us(10);	
	return(x);			
}
int atc_di2_b_di1(int bit)
{	
	int x;
	x = 1<<bit;
	atc_b_write(ATC_DI2_IC21,x);
	x = atc_b_rd(ATC_DI2_IC18)&0x2;
	atc_b_write(ATC_DI2_IC21,0x0);
	x>>=1;  
	Delay_us(10);	
	return(x);			
}

int atc_di2_a_di2(int bit)
{	
	int x;
	x = 1<<bit;
	atc_a_write(ATC_DI2_IC21,x);
	x = atc_a_rd(ATC_DI2_IC17)&0x4;
	atc_a_write(ATC_DI2_IC21,0x0);
	x>>=2;
	Delay_us(10);	  
	return(x);			
}
int atc_di2_b_di2(int bit)
{	
	int x;
	x = 1<<bit;
	atc_b_write(ATC_DI2_IC21,x);
	x = atc_b_rd(ATC_DI2_IC18)&0x4;
	atc_b_write(ATC_DI2_IC21,0x0);
	x>>=2;
	Delay_us(10);	  
	return(x);			
}


void test_di2_di_scan()
{
	int i;
	int x,y,z;
	s_printf("\n");
	for(;;)
	{
		s_printf("DI2 : ");		
		for(x=7;x>=0;x--)
		{
			y=atc_di2_a_di2(x);
			z=y<<x;
			ATC_DI2_A_LED2=bit_clear(ATC_DI2_A_LED2,x);
			ATC_DI2_A_LED2|=z;
			s_printf("%d ",y);
			atc_a_write(ATC_DI2_IC10,6);
		}		
		s_printf("    DI1 : ");
		for(x=7;x>=0;x--)
		{
			y=atc_di2_a_di1(x);
			z=y<<x;
			ATC_DI2_A_LED1=bit_clear(ATC_DI2_A_LED1,x);
			ATC_DI2_A_LED1|=z;
			s_printf("%d ",y);
			atc_a_write(ATC_DI2_IC10,5);
		}
		s_printf("    DI0  : ");
		for(x=7;x>=0;x--)
		{
			y=atc_di2_a_di0(x);
			z=y<<x;
			ATC_DI2_A_LED0=bit_clear(ATC_DI2_A_LED0,x);
			ATC_DI2_A_LED0|=z;
			s_printf("%d ",y);
			atc_a_write(ATC_DI2_IC10,3);
		}
		atc_a_write(ATC_DI2_IC23,~ATC_DI2_A_LED0);
		atc_a_write(ATC_DI2_IC24,~ATC_DI2_A_LED1);
		atc_a_write(ATC_DI2_IC25,~ATC_DI2_A_LED2);	
		/*
		atc_a_write(ATC_DI2_IC23,i);
		atc_a_write(ATC_DI2_IC24,i);
		atc_a_write(ATC_DI2_IC25,i++);
		*/						
		PUTCHAR(CR);		
	}				
}

void atc_io_scan()
{
	char x;

	s_printf(" RYD1 Test \n");
	for(x=0;;)
	{
			s_printf("%x\n",x);	
			atc_a_write(0x40,x<<7);			
			atc_a_write(0x44,~(x++));	
	
			s_getchar();	
	}
	
}

/* ==================================================================== */
/*	Interrupt service routine											*/
/* ==================================================================== */
void c_int09()				/* Timer 0 interrupt service routine */
{ 

}
void c_int10()				/* Timer 1 interrupt service routine */
{ 
	Count_x++;
	if(Count_x >= 1)
	{
		int_flag=1;	
		Count_x=0;
	}
}

/* ==================================================================== */
/*	Interrupt initz routine											*/
/* ==================================================================== */
void initz_int_tint0()
{  
    *Timer0_GCR = 0x02c0;				/* set Timer 0 			*/
  	*Timer0_PR = 1250000*5; 			/* 100msec*n				*/  
  	Set_interrupt(TINT0);				/* set Timer0 interrupt */   
  	Int_enable();
}
void initz_int_tint1()
{    
  	*Timer1_GCR = 0x02c0;				/* set Timer 0 			*/
  	*Timer1_PR = 1250000*5; 			/* 100msec*n				*/ 	
	Set_interrupt(TINT1);				/* set Timer0 interrupt */
  	Int_enable();
}
asm("		.sect	\".vector\"	");
asm("IVT:	.space	9			");
asm("		.word	_c_int09	");			/* Timer 0 */
asm("		.word	_c_int10	");			/* Timer 0 */
asm("		.data				");
asm("_ITTP:					");	
asm("		.word	IVT			"); 
 	  
void main()
{
		
  	Init_DSP(); Delay_ms(50);			/* initialize DSP, 8255A, LCD */
  	Init_8255();
  	Init_LCD();
  	Init_8251();						/* initialize 8251A */
  	Beep();
  
  	initz_int_tint1();
  	Delay_ms(50);
  	
	s_printf("\nATC-block test 2002. 05. 15. %f	\n",3.141592);
	s_printf("atc block test 2002. 05. 17.	\n	\n");
	
 	atc_all_reset();
	ATC_BUS[ATC_MODE] = int_latch;		/* initz control latch */
		
	for(;;)
	{	
		atc_io_scan();
	}
}
