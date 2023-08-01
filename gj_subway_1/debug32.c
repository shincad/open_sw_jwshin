#include "CSTARTUP.C"
#include "TMS32FUN.H"

#define TRUE 	 1
#define FALSE	 0

#define BASE0	0x3f8

int intz_prime3C()
{
	PPI[0x398]=0x33;
	PPI[0x398]=0x33;
    Delay_ms(50);

	PPI[0x398]=0xc0;
	if((PPI[0x399]&0xff)!=0x3c)
		return FALSE;

	PPI[0x398]=0xc2;
	PPI[0x399]=0xc;
	PPI[0x398]=0xc6;			/* print port base address */
	PPI[0x399]=0xde;
	PPI[0x398]=0xc7;
	PPI[0x399]=0xfe;
	PPI[0x398]=0xc8;
	PPI[0x399]=0xbe;
	PPI[0x398]=0xcb;
	PPI[0x399]=0x34;
	PPI[0x398]=0x55;
    Delay_ms(50);

	PPI[BASE0+3]=0x80;
	PPI[BASE0]=3;				/* 0xc=9.600 6=19.200 3=38400 2=57600 1=115200 */
	PPI[BASE0+1]=0;
	PPI[BASE0+3]=3;
	return TRUE;
}
		 
#define	CR	 0xd
#define	LF   0xa
#define BS   0x8
#define TAB  0x9
#define BELL 0x7

putcom(int ch)
{
	PPI[BASE0]=ch;
}

putch(int ch)
{		
        while(!((PPI[BASE0+5]&0xff)&0x20));
        PPI[BASE0] = ch;
}

putchar(int ch)
{
        putch(ch);
        if( ch == CR ) putch(LF);
        else if
          ( ch == LF ) putch(CR);
}

int getch()
{
        while(!((PPI[BASE0+5]&0xff)&0x1));
        return(PPI[BASE0]&0xff);
}

int getchar()
{
	int i;
    i = getch();
    i&=0xff;
    putchar(i);
    return(i);
}

putstr( char *ch )
{
	while( *ch != 0 ) 
	{
    	putchar(*ch);
        ch++;
    }
}

void main()
{
	int i;
	Init_DSP(); 	Delay_ms(50);
	if(intz_prime3C()==FALSE)	
	{
		Clearxf1();
	}
	else
		Setxf1();

	putcom(0x33);
	for(i=0;;i++)
	{
		PPI[0x378] = i;
		Clearxf0();
		Setxf0();
	}
}