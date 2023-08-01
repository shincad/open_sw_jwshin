#include "user32.h"
#include <tms32int.h>

int	*ATC_BUS	= (int *)0x818000;	/* atc bus 	*/
#define A_ALE	0x400
#define B_ALE	0x500
#define A_WR	0x600
#define B_WR	0x700
#define A_RD	0x600
#define B_RD	0x700

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

void main()
{
	int a_count;
	int d_count;
	int temp;	
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
	a_count=0;
	d_count=0;
	
	for(;1;)
	{
		uprintf("Address ALE %4x\n",a_count);
		ATC_BUS[A_ALE+a_count]=0;
		ATC_BUS[B_ALE+a_count]=0;
		for(d_count=0x0;d_count<=0xff;d_count++)
		{
			uprintf("atc data write ADD:%4x DATA:%4x\n",a_count,d_count);
			ATC_BUS[A_WR+a_count]=d_count;
			ATC_BUS[B_WR+a_count]=d_count; 
		}		
		a_count++;
		uprintf("Address INC++ 2002 05 07 \n");
		if(a_count>0xff)
		{ 
			a_count=0;			
		}
		Delay_ms(10);
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
