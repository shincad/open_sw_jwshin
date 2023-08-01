#include "atc.h"
#include "TMS32INT.H"

int	*ATC_BUS	= (int *)0x816800;		/* atc bus base address */
int   Count_x = 0;
#define ATC_MODE	0x400
#define INT_DFF		0x500
#define A_IORD		0x400
#define B_IORD		0x500

int int_latch;
int read_data;
int n_7seg0=0xff;
int n_7seg1=0xff;
int int_flag=0;
int led0_di1=0xff,led1_di1=0xff,led2_di1=0xf0;
int led0_di2=0xff,led1_di2=0xff,led2_di2=0xff;

int int_latch = 0xff;

void atc_ale(int add)
{
		int_latch &= 0xfe;
		ATC_BUS[ATC_MODE] = int_latch;	/* buff enable */
			
		ATC_BUS[INT_DFF]=add;	/* data set */
		int_latch &= 0xfd;	
		ATC_BUS[ATC_MODE] = int_latch;	/* ale set */			
		int_latch |= 0x2;	
		ATC_BUS[ATC_MODE] = int_latch;	/* ale clr */	
		
		int_latch |= 0x1;	
		ATC_BUS[ATC_MODE] = int_latch;	/* buffer disable */							 	
}

void atc_a_write(int data)
{
		int_latch &= 0xfe;
		ATC_BUS[ATC_MODE] = int_latch;	/* buff enable */
		
		ATC_BUS[INT_DFF]=data;			/* data set */
			
		int_latch |= 0x10;	
		ATC_BUS[ATC_MODE] = int_latch;	/* a-iowr clr */
		int_latch &= 0xef;	
		ATC_BUS[ATC_MODE] = int_latch;	/* a-iowr set */	
		
		int_latch = 0x1;	
		ATC_BUS[ATC_MODE] = int_latch;	/* buffer disable */							 	
}

void atc_b_write(int data)
{
		int_latch &= 0xfe;
		ATC_BUS[ATC_MODE] = int_latch;	/* buff enable */
		
		ATC_BUS[INT_DFF]=data;			/* data set */
			
		int_latch |= 0x20;	
		ATC_BUS[ATC_MODE] = int_latch;	/* b-iowr clr */
		int_latch &= 0xdf;	
		ATC_BUS[ATC_MODE] = int_latch;	/* b-iowr set */	
		
		int_latch = 0x1;	
		ATC_BUS[ATC_MODE] = int_latch;	/* buffer disable */							 	
}

int atc_a_rd()
{
		
		int_latch = 0x3;	
		ATC_BUS[ATC_MODE] = int_latch;	/* buffer disable */	
		read_data = ATC_BUS[A_IORD];
		return(read_data);							 	
}

int atc_b_rd()
{
		
		int_latch = 0x3;	
		ATC_BUS[ATC_MODE] = int_latch;	/* buffer disable */	
		read_data = ATC_BUS[B_IORD];
		return(read_data);							 	
}


int atc_a_read_bit_di2(int bit)
{
	int i,temp;
	i=1;	
			
	if		((bit>=0)&&(bit<=7))
	{
		atc_ale(0x88);							
		atc_a_write(i<<bit);
		atc_b_write(0);
		atc_ale(0x8a);
		temp=atc_a_rd();
		atc_ale(0x88);							
		atc_a_write(0);	
			
		if((temp&1)==1)	
		{
			atc_ale(0x82);				/* led control address */
			led0_di2&=(~(1<<bit));
			atc_a_write(led0_di2);	
		}
		else
		{
			atc_ale(0x82);				/* led control address */
			led0_di2|=(1<<bit);			
			atc_a_write(led0_di2);		
		}
		return(temp&1);
	}	
	else if	((bit>=8) && (bit<=15))
	{
		atc_ale(0x88);
		bit%=8;							
		atc_a_write(i<<bit);
		atc_b_write(0);
		atc_ale(0x8a);
		temp=atc_a_rd();
		temp&=2;
		temp>>=1;
		atc_ale(0x88);							
		atc_a_write(0);
		
		if(temp==1)	
		{
			atc_ale(0x84);				/* led control address */	
			led1_di2&=(~(1<<bit));
			atc_a_write(led1_di2);	
		}
		else
		{
			atc_ale(0x84);			
			led1_di2|=(1<<bit);
			atc_a_write(led1_di2);		
		}							
		return(temp);		
	}
	else if	((bit>=16) && (bit<=23))
	{
		atc_ale(0x88);
		bit%=16;							
		atc_a_write(i<<bit);
		atc_b_write(0);
		atc_ale(0x8a);
		temp=atc_a_rd();
		temp&=4;
		temp>>=2;
		atc_ale(0x88);							
		atc_a_write(0);	
		
		if(temp==1)	
		{
			atc_ale(0x86);				/* led control address */
			led2_di2&=(~(1<<bit));
			atc_a_write(~(1<<bit));	
		}
		else
		{
			atc_ale(0x86);		
			led2_di2|=(1<<bit);		
			atc_a_write(led2_di2);		
		}				
		return(temp);			
	}
	else
		return -1;
}

int atc_b_read_bit_di2(int bit)
{
	int temp;
		
	if		((bit>=0)&&(bit<=7))
	{
		atc_ale(0x88);							
		atc_b_write(1<<bit);
		atc_a_write(0);			
		atc_ale(0x8c);
		temp=atc_b_rd();
		atc_ale(0x88);							
		atc_b_write(0);

		if((temp&1)==1)	
		{
			atc_ale(0x82);				/* led control address */
			led0_di2&=(~(1<<bit));
			atc_a_write(led0_di2);	
		}
		else
		{
			atc_ale(0x82);				/* led control address */
			led0_di2|=(1<<bit);			
			atc_a_write(led0_di2);		
		}
					
		return(temp&1);
	}	
	else if	((bit>=8) && (bit<=15))
	{
		atc_ale(0x88);
		bit%=8;					
		atc_b_write(1<<bit);
		atc_a_write(0);		
		atc_ale(0x8c);
		temp=atc_b_rd();
		temp&=2;
		temp>>=1;
		atc_ale(0x88);							
		atc_b_write(0);
			
		if(temp==1)	
		{
			atc_ale(0x84);				/* led control address */	
			led1_di2&=(~(1<<bit));
			atc_a_write(led1_di2);	
		}
		else
		{
			atc_ale(0x84);			
			led1_di2|=(1<<bit);
			atc_a_write(led1_di2);		
		}			
		return(temp);		
	}
	else if	((bit>=16) && (bit<=23))
	{
		atc_ale(0x88);
		bit%=16;					
		atc_b_write(1<<bit);
		atc_a_write(0);
		atc_ale(0x8c);
		temp=atc_b_rd();
		temp&=4;
		temp>>=2;
		atc_ale(0x88);							
		atc_b_write(0);
			
		if(temp==1)	
		{
			atc_ale(0x86);				/* led control address */
			led2_di2&=(~(1<<bit));
			atc_a_write(~(1<<bit));	
		}
		else
		{
			atc_ale(0x86);		
			led2_di2|=(1<<bit);		
			atc_a_write(led2_di2);		
		}			
		return(temp);			
	}
	else
		return -1;
}

void atc_rl_write_di2(int relay)
{
	atc_ale(0x80);						/* Relay control address */	
	atc_a_write(1<<relay);	
}

/*DI1*************************************************************/
#define INT_LS574	0x68


void atc_a_mode_di1(int n)
{
		atc_ale(INT_LS574);	
		atc_a_write(n);	
}

void atc_b_mode_di1(int n)
{
		atc_ale(INT_LS574);	
		atc_b_write(n);	
}

void atc_a_led_on_di1()
{
		atc_ale(INT_LS574);	
		int_latch|=0x40;
		atc_a_write(int_latch);
}

void atc_a_led_off_di1()
{
		atc_ale(INT_LS574);	
		int_latch&=0xbf;
		atc_a_write(int_latch);
}

void atc_b_led_on_di1()
{
		atc_ale(INT_LS574);	
		int_latch|=0x40;
		atc_b_write(int_latch);
}

void atc_b_led_off_di1()
{
		atc_ale(INT_LS574);	
		int_latch&=0xbf;
		atc_b_write(int_latch);
}

void atc_count_set_di1(int n)
{
		atc_ale(INT_LS574);	
		int_latch&=0xf0;	
		int_latch|=n;
		atc_a_write(int_latch);
}

#define LED0_OUT_DI1 0x6a
#define LED1_OUT_DI1 0x6c
#define LED2_OUT_DI1 0x6e

#define SEG0_OUT_DI1 0x74
#define SEG1_OUT_DI1 0x76

#define DI_OUT_DI1 	 0x6a
#define DI_IN_DI1	 0x6c



void atc_a_led_set0_di1(int n)
{
		atc_a_led_on_di1();
		atc_ale(LED0_OUT_DI1);							
		atc_a_write(~n);
}
void atc_a_led_set1_di1(int n)
{
		atc_a_led_on_di1();
		atc_ale(LED1_OUT_DI1);							
		atc_a_write(~n);
}
void atc_a_led_set2_di1(int n)
{
		atc_a_led_on_di1();
		atc_ale(LED2_OUT_DI1);							
		atc_a_write(~n);
}

void atc_a_7seg_set0_di1(int n)
{
		atc_a_led_on_di1();
		atc_ale(SEG0_OUT_DI1);							
		atc_a_write(n);
}
void atc_a_7seg_set1_di1(int n)
{
		atc_a_led_on_di1();
		atc_ale(SEG1_OUT_DI1);							
		atc_a_write(n);
}

int atc_a_read_in0_di1(int bit)
{
	int temp;
	atc_a_led_off_di1();
	atc_ale(DI_OUT_DI1);	
	atc_a_write(1<<bit);
	atc_ale(DI_IN_DI1);
	temp=atc_a_rd()&1;
	Delay_ms(5);
	if(temp==1)
		return 1;
	else 
		return 0;		
}
int atc_a_read_in1_di1(int bit)
{
	int temp;
	atc_a_led_off_di1();
	atc_ale(DI_OUT_DI1);	
	atc_a_write(1<<bit);
	atc_ale(DI_IN_DI1);
	temp=atc_a_rd()&2;
	if(temp==2)
		return 1;
	else 
		return 0;		
}
int atc_a_read_in2_di1(int bit)
{
	int temp;
	atc_a_led_off_di1();
	atc_ale(DI_OUT_DI1);	
	atc_a_write(1<<bit);
	atc_ale(DI_IN_DI1);
	temp=atc_a_rd()&4;	
	if(temp==4)
		return 1;
	else 
		return 0;		
}
int hex_2d(int number)			/* display 2-digit decimal number */
{ 
	int i,j;

  	i = number/10;				/* 10^1 */
  if(i == 0) j=0;
  else       j=i<<4;

  i = number % 10;				/* 10^0 */
  return j+i;
}

void test_di2()
{	
	int x;
	for(x=0;x<25;x++)
	{
		atc_a_read_bit_di2(x);
	}

}

void test_di1()
{
	int add,temp,temp1;
	
	s_printf("IN0 : ");
	for(add=0;add<8;add++)
	{
		s_printf("%d ",temp=atc_a_read_in0_di1(add));
		temp1=1<<add;
		led0_di1&=(~temp1);
		led0_di1=led0_di1|(temp<<add);
		atc_a_led_set0_di1(led0_di1);
	}	
	s_printf("	IN1 : ");
	for(add=0;add<8;add++)
	{
		s_printf("%d ",temp=atc_a_read_in1_di1(add));
		temp1=1<<add;
		led1_di1&=(~temp1);
		led1_di1=led1_di1|(temp<<add);
		atc_a_led_set1_di1(led1_di1);
	}	
	s_printf("	IN2 : ");
	for(add=0;add<8;add++)
	{
		s_printf("%d ",temp=atc_a_read_in2_di1(add));
		temp1=1<<add;
		led2_di1&=(~temp1);
		led2_di1=led2_di1|(temp<<add);
		atc_a_led_set2_di1(led2_di1);
	}
	PUTCHAR(CR);
	return;
}

void atc_io_scan()
{
	int add,temp,temp1;

	test_di2();
	test_di1();
	if(int_flag=1)
	{
		atc_a_7seg_set0_di1(hex_2d(n_7seg0++));
		atc_a_7seg_set1_di1(hex_2d(n_7seg1++));
		if(n_7seg0>100)
		{
			n_7seg0=0,n_7seg1=0;
		}
		int_flag=0;
	}	
	return;				
	
	for(add=0;add<=0xff;add++)
	{
		atc_a_7seg_set0_di1(add);
		atc_a_7seg_set1_di1(add);
		s_printf("\nATC LED ADDRESS : <%4x>  \n",add);
		Beep();
	}	
	Delay_ms(25);
	return;					
}

void c_int09()				/* Timer 0 interrupt service routine */
{ 
	Count_x++;
	if(Count_x >= 2)
	{
		Count_x=0;
		int_flag=1;	
	}
}
void c_int10()				/* Timer 0 interrupt service routine */
{ 
	Count_x++;
	if(Count_x >= 2)
	{
		Count_x=0;	
		int_flag=1;
	}
}
/* ==================================================================== */
/*	Interrupt Vector Table						*/
/* ==================================================================== */

  
void initz_int_tint0()
{  
    *Timer0_GCR = 0x02c0;				/* set Timer 0 */
  	*Timer0_PR = 1250000*5; 			/* 500msec		*/  
  	Set_interrupt(TINT0);				/* set Timer0 interrupt */   
  	Int_enable();
}
void initz_int_tint1()
{    
  	*Timer1_GCR = 0x02c0;				/* set Timer 0 */
  	*Timer1_PR = 1250000*5; 			/* 500msec		*/ 	
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
  	
	s_printf("\nATC-DI2 demo 2002.05.15. %f	\n",3.141592);
	s_printf("atc block test 2002 05	\n	\n");
	int_latch = 0x1;	
	ATC_BUS[ATC_MODE] = int_latch;	/* initz control latch */
	
	for(;;)
	{	
		atc_io_scan();
	}

}
