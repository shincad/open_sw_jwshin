#include "user32.h"
#include <tms32int.h>

int	*ATC_BUS	= (int *)0x818000;	/* atc bus 	*/

#define ATC_MODE	0x400
#define INT_DFF		0x500
#define A_IORD	0x400
#define B_IORD	0x500

#define MAXQ	2048
unsigned queue[MAXQ];
unsigned front,rear;
queue_initz()
{
    front = rear = 0;
}

queue_clr()
{
    front = rear;
}
qput(unsigned k)
{
    if( (rear+1) % MAXQ == front )
    {
            return FALSE;
    }
    queue[rear] = k;
    rear = ++rear % MAXQ;
    return k;
}
unsigned qget()
{
    unsigned i;
    if( front == rear )
    {
            return FALSE;
    }
    i = queue[front];
    front = ++front%MAXQ;
    return i;
}
unsigned rxflag;
unsigned rxbuff;
unsigned iGETCH()
{
	unsigned i;
    while(1)
    {
		if( rxflag == 1 )
        {
        	rxflag = 0;
            return qget();
        }
    }
}

void c_int01()
{
    if( (rear+1) % MAXQ == front )
    {
		;
    }
    queue[rear] = rxbuff;
    rear = ++rear % MAXQ;
	rxflag=1;
}
void c_int09()
{
	if(SUPER_IO[BASE0+5]&0x1)
	{		
		rxbuff=SUPER_IO[0x3f8];
	}
}

asm("		.sect	\".vector\"		");
asm("IVT:	.space	1				");
asm("		.word	_c_int01		");
asm(" 		.space	7				");
asm("		.word	_c_int09		");

asm("		.data					");
asm("_ITTP	.word	IVT				");


int int_latch;
int read_data;

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
		
		ATC_BUS[INT_DFF]=data;	/* data set */
			
		int_latch |= 0x10;	
		ATC_BUS[ATC_MODE] = int_latch;	/* a-iowr clr */
		int_latch &= 0xef;	
		ATC_BUS[ATC_MODE] = int_latch;	/* a-iowr set */	
		
		int_latch |= 0x1;	
		ATC_BUS[ATC_MODE] = int_latch;	/* buffer disable */							 	
}

void atc_b_write(int data)
{
		int_latch &= 0xfe;
		ATC_BUS[ATC_MODE] = int_latch;	/* buff enable */
		
		ATC_BUS[INT_DFF]=data;	/* data set */
			
		int_latch |= 0x20;	
		ATC_BUS[ATC_MODE] = int_latch;	/* b-iowr clr */
		int_latch &= 0xdf;	
		ATC_BUS[ATC_MODE] = int_latch;	/* b-iowr set */	
		
		int_latch |= 0x1;	
		ATC_BUS[ATC_MODE] = int_latch;	/* buffer disable */							 	
}

int atc_a_rd()
{
		
		int_latch |= 0x1;	
		ATC_BUS[ATC_MODE] = int_latch;	/* buffer disable */	
		read_data = ATC_BUS[A_IORD];
		return(read_data);							 	
}

int atc_b_rd()
{
		
		int_latch |= 0x1;	
		ATC_BUS[ATC_MODE] = int_latch;	/* buffer disable */	
		read_data = ATC_BUS[B_IORD];
		return(read_data);							 	
}

void main()
{
	int a_count;
	int d_count;
	int temp;	
	int bit_flag;
	int led_flag;
	int x,y;
	Init_DSP();	Delay_ms(10);
	initz_prime3C(); Delay_ms(10);
	uprintf("\ntms32c32 demo 1999.03.16. %f",3.141592);
	uprintf("\ncall putchar(getch()) by COM1\n");
	CSTRB0[0]=0xf00e8;

	Delay_ms(1);
/*	
	eepromerase();
	for(x=0;x<128;x++)
	{
		mpage[x]=x;
	}
	pagewr(0x0);
	CSTRB0[0]=0xf0048;

	for(x=0;x<0xf;x++)
	{
		uprintf("\n%x ",EMBASE[0x1000+x]&0xff);
	}
*/	
	rxflag=0;	
	*Timer0_GCR=0x2c3;
        *Timer0_PR=100;                                /* 40Mhz -> 1msec call 10000 */
	queue_initz();
	Set_interrupt(INT0);
	Set_interrupt(TINT0);
	Edge_enable();
	Int_enable();
	
	iGETCH();
	
	int_latch = 0x1;	
	ATC_BUS[ATC_MODE] = int_latch;	/* initz control latch */
	
	a_count=0;
	d_count=0;
	
	bit_flag = 1;
	led_flag = 1;
	
	for(;1;)
	{
		uprintf("Relay on-off control\n");
		
			atc_ale(0x7e);				/* Relay control address */
			/*
			atc_a_write(bit_flag);
			*/
				atc_ale(0x7c);				/* led control address */
				atc_a_write(led_flag); 	
				atc_ale(0x7a);				/* led control address */
				atc_a_write(led_flag);			
				atc_ale(0x78);				/* led control address */
				atc_a_write(led_flag);
				
			bit_flag<<=1;
			if(bit_flag>=0x4)	bit_flag=1;
								
			led_flag<<=1;
			if(led_flag>=0x80)	led_flag=1;					
			Delay_ms(10);	
	}
	
	for(;1;)
	{
		uprintf("Address 0x818000 + %4x\n",a_count);
		for(d_count=0x0;d_count<=0xff;d_count++)
		{
			uprintf("atc data write ADD:%4x 	DATA:%4x\n",a_count,d_count);
			atc_ale(a_count);
			atc_a_write(d_count);
			atc_b_write(d_count);
			uprintf("atc data read a-iord:%4x 	b-iord:%4x\n",(0xff&atc_a_rd()),(0xff&atc_b_rd()));
			Delay_ms(50); 	
		}	
			
		a_count++;
		uprintf("Address INC++ 2002 05 07 \n");
		if(a_count>0xff)
		{ 
			a_count=0;			
		}
	}
	
	for(x=0;1;x++)
	{
		/*
		eppaddwr(x);
		uprintf("epp address port wr:%x rd:%x\n",x&0xff,eppaddrd()&0xff);
		GETCH();
		eppdatwr(x+1);
		uprintf("epp address port wr:%x rd:%x\n",(x+1)&0xff,eppdatrd()&0xff);
		*/
		/*
		sppdatwr(x);
		uprintf("spp address port wr:%x rd:%x\n",x&0xff,sppdatrd()&0xff);
		*/
		/*
		sppdatwr(GETCH());
		*/
		if('x'==(y=iGETCH()))
			break;
		PUTCHAR(y&0xff);
	}
	while(1);
}
