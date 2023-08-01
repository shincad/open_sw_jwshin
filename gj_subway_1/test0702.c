/*================================================================*/
/*  ATC Block Test Program                                        */
/*  TITLE    : test.c                                             */
/*  ABSTRACT : ATC Block Bus Test Firmware                        */
/*  AUTHOR(S): HSMin & JWShin                                     */
/*  DATE     : 2002. 6.                                           */
/*  Copyright (c) 2002                                            */
/*  SOC-ATC, R&D Center Hyundai Information Technology            */
/*  All rights reserved                                           */
/*================================================================*/

#include "atc.h"
#include "TMS32INT.H"					/* interrupt vector define */

int	*ATC_BUS	= (int *)0x816800;		/* atc-mb base address */
int int_latch=0x80;                     /* Altera EPLD Internal latch */

#define ATC_MODE	0x400				/* control address */
#define INT_DFF		0x500
#define A_IORD		0x400
#define B_IORD		0x500
#define AB_CLK		0x700
#define SW_CLK		1

#define SYS_CLK     0

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

/* Led & 7 Segment Pattern Data */

unsigned char Ryd1Led[5]= {0xDF,0xEF,0xF7,0xFB,0xFD};
unsigned char Di2LedData[8] = {0x80,0x40,0x20,0x10,0x8,0x4,0x2,0x1};
unsigned char Di1LedData[8] = {0x80,0x40,0x20,0x10,0x8,0x4,0x2,0x1};
unsigned char Di1Segment[10] = {0x0,0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,0x99};
unsigned char LdmSegment[10] = {0x02,0xcf,0x11,0x85,0x4c,0xa4,0x20,0x8e,0x0,0x84};

/* LDM 7 Segment Data */
/* 0 : 1000$0001 */
/* 1 : 1100$1111 */
/* 2 : 1001$0001 */
/* 3 : 1000$0101 */
/* 4 : 1100$1100 */
/* 5 : 1010$0100 */
/* 6 : 1010$0000 */
/* 7 : 1000$1110 */
/* 8 : 1000$0000 */
/* 9 : 1000$0100 */


int Count_x = 0;						/* global count */
int	int_flag=0xff;						/* interrupt flag */

int Rxbuff;

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
    if(x==SYS_CLK)                      /* H1/N */
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
        ATC_BUS[ATC_MODE] = int_latch;  /* ale clr */
							
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
    x= atc_a_rd(ATC_DI2_IC17)&0x1;
    atc_a_write(ATC_DI2_IC21,0x0);
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

/*-----------------------------------------------------------------*/
/*             LCD Test Routine                                    */
/*-----------------------------------------------------------------*/

unsigned char LCD_Data[4] = {'|','/','-',0xA4};
int k=0;
void LCDtest(void)
{
    LCD_command(0xC0);
    LCD_data(LCD_Data[k]);
    k++;
    if(k==4) {
        k=0;
    }
}

/*------------------------------------------------------------------*/
/*              RYD1 Board Test Routine                             */
/*------------------------------------------------------------------*/
void ryd1test()
{
    int i=0;
    int k=0;
    unsigned char RelayTogg=0;              /* Relay On,Off Toggle */
    LCD_str("RYD1 Test.......");
    while(1) {
        LCDtest();
        atc_a_write(0x40,RelayTogg);        /* RYD1 Relay */
        RelayTogg ^= 0x80;                  /* Relay Toggling */
        atc_a_write(0x44,Ryd1Led[i]);       /* RYD1 IC6(574) */
        i++;
        if(i == 5) {                        /* 5 LED Toggling End.. */
            i = 0;
        }
        Delay_ms(100);
        if('q' == GETCHAR()) {
            return;
        }
    }
}


/*------------------------------------------------------------------*/
/*              DI2 Board Test Routine                              */
/*------------------------------------------------------------------*/
void di2test()
{
    int i=0;
    int x=0;
    int y=0;
    int z=0;
    int RelayTogg=0;
    int di2_io=0x82;
    s_printf("\n");
    LCD_str("DI2 Test........");
	for(;;)
	{
        LCDtest();
        s_printf("DI2 : ");                    /* DI2 Data Scan.. */
		for(x=7;x>=0;x--)
		{
			y=atc_di2_a_di2(x);
			z=y<<x;
			ATC_DI2_A_LED2=bit_clear(ATC_DI2_A_LED2,x);
			ATC_DI2_A_LED2|=z;
			s_printf("%d ",y);
		}		
        s_printf("    DI1 : ");                /* DI1 Data Scan.. */
		for(x=7;x>=0;x--)
		{
			y=atc_di2_a_di1(x);
			z=y<<x;
			ATC_DI2_A_LED1=bit_clear(ATC_DI2_A_LED1,x);
			ATC_DI2_A_LED1|=z;
			s_printf("%d ",y);
		}
        s_printf("    DI0  : ");               /* DI0 Data Scan.. */
		for(x=7;x>=0;x--)
		{
			y=atc_di2_a_di0(x);
			z=y<<x;
			ATC_DI2_A_LED0=bit_clear(ATC_DI2_A_LED0,x);
			ATC_DI2_A_LED0|=z;
			s_printf("%d ",y);
		}

        atc_a_write(ATC_DI2_IC10,RelayTogg);      /* DI2 Relay On,Off */
        atc_a_write(ATC_DI2_IC10,RelayTogg);
        atc_a_write(ATC_DI2_IC10,RelayTogg);
        RelayTogg ^= 0x07;                        /* DI2 IC9(574) Bit2,1,0 */

        atc_a_write(di2_io,~(Di2LedData[i]));     /* DI2 IC23,24,25 */
        Delay_ms(20);                             /*     0x82,84,86 */
        PUTCHAR(CR);
        i++;
        if(i==8) {
            atc_a_write(di2_io,0);
            i=0;
            di2_io+=2;
        }
        if(di2_io==0x88) {
            di2_io = 0x82;
        }
        if('q' == GETCHAR()) {
            return;
        }
    }
}

/*------------------------------------------------------------------*/
/*              DI1 Board Test Routine                              */
/*------------------------------------------------------------------*/
void di1test()
{
    int i=0;
    int j=0;
    int di1_io=0x6a;
    LCD_str("DI1 Test........");
    while(1) {
        LCDtest();
        Beep();
        atc_a_write(di1_io,~(Di1LedData[i]));       /* DI1 IC23,24,25 */
                                                    /*     0x6a,6c,6e */
        atc_a_write(0x68,0xff);

        atc_a_write(0x74,Di1Segment[j]);            /* Upper 2 Segments */
        atc_a_write(0x76,Di1Segment[j]);            /* Lower 2 Segments */
        i++;
        j++;
        if(j==10) {
            j=0;
        }

        if((di1_io == 0x6e)&&(i==5)) {
            atc_a_write(di1_io,0);
            i = 0;
            di1_io = 0x6a;
        }
        if(i == 8) {
            atc_a_write(di1_io,0);
            i=0;
            di1_io += 2;
        }
        if('q' == GETCHAR()) {
            return;
        }
        Delay_ms(100);
    }
}

/*------------------------------------------------------------------*/
/*              8253 Count Test Routine                             */
/*------------------------------------------------------------------*/
void cnttest()
{   int i=0;
    int Togg=0xDF;
    int Val1,Val2,Val3,Val4;


    s_printf("Counter Value...4 Values..?\n");
    s_printf("LSB upper byte..?\n");
    Val1 = GETCHAR1()&0x0f;
    s_printf("LSB lower byte..?\n");
    Val2 = GETCHAR1()&0x0f;
    s_printf("MSB upper byte..?\n");
    Val3 = GETCHAR1()&0x0f;
    s_printf("MSB lower byte..?\n");
    Val4 = GETCHAR1()&0x0f;
    Val1 = (Val1<<4)+Val2;
    Val3 = (Val3<<4)+Val4;

                                        /* Counter 0,16Bit Access,Mode 4 */
        atc_a_write(0x66,0x38);         /* Control Word Setting */
        atc_a_write(0x60,Val1);         /* Counter Value Write(LSB) */
        atc_a_write(0x60,Val3);         /* Counter Value Write(MSB) */
    LCD_str("8253 Count Test ");
    while(1) {
        LCDtest();
        atc_a_write(0x68,Togg);         /* IC35 Bit 5 Clock used.. */
        Togg^=0x20;
        s_printf("Counter LSB: %x ",atc_a_rd(0x60));     /* LSB Read */
        s_printf("Counter MSB: %x \n",atc_a_rd(0x60));   /* MSB Read */

        if('q' == GETCHAR()) {
            return;
        }
    }

}
/*------------------------------------------------------------------*/
/*              LDM2 Test Routine                                   */
/*------------------------------------------------------------------*/
void ldm2test()
{
    int i=0;
    int Togg=0;
    LCD_str("LDM2 Test.......");
    while(1) {
        LCDtest();
        Beep();
        atc_a_write(0xa0,Togg);                  /* LED Toggling */
        atc_a_write(0xa4,Togg);
        atc_a_write(0xa8,Togg);
        Togg^= 0xff;
        atc_a_write(0xac,LdmSegment[i]);         /* LDM 7 Segment Counting */
        atc_a_write(0xb0,LdmSegment[i]);
        atc_a_write(0xb4,LdmSegment[i]);
        atc_a_write(0xb8,LdmSegment[i]);
        i++;
        if(i==10) {
            i=0;
        }
        if('q' == GETCHAR()) {
            return;
        }
        Delay_ms(100);
    }
}

/*------------------------------------------------------------------*/
/*              Relay Test Routine                                  */
/*------------------------------------------------------------------*/
void relaytest()
{
    int Togg=0;
    char Val;
    s_printf("Delay Value...?\n");
    s_printf("1-9\n");
    Val = GETCHAR1();
    Val = Val&0x0f;
    s_printf("Value is %d\n",Val);
    if((Val>9) || (Val<=0)) {
        s_printf("Default Value is 1..\n");
        Val = 1;
    }
    LCD_str("Relay Test......");
    while(1) {
        LCDtest();
        atc_a_write(ATC_DI2_IC10,6);      /* DI2 Relay On,Off */
        Delay_ms(Val*1);
        atc_a_write(ATC_DI2_IC10,5);      /* DI2 Relay On,Off */
        Delay_ms(Val*1);
        atc_a_write(ATC_DI2_IC10,3);      /* DI2 Relay On,Off */
        Delay_ms(Val*1);
        atc_a_write(0x40,Togg);
        Togg ^= 0x80;
        if('q' == GETCHAR()) {
            return;
        }
        Delay_ms(Val*20);
    }
}

/*------------------------------------------------------------------*/
/*              All Test Routine                                    */
/*------------------------------------------------------------------*/
void alltest()
{
    int i=0;
    int j=0;
    int m=0;
    int x=0;
    int y=0;
    int z=0;
    int Togg=0;
    int LdmTogg=0;
	s_printf("\n");
    LCD_str("All Test........");
	for(;;)
	{
        LCDtest();
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


		/*di2 led*/ 
		

        atc_a_write(ATC_DI2_IC23,~(Di2LedData[i]));
        atc_a_write(ATC_DI2_IC24,~(Di2LedData[i]));
        atc_a_write(ATC_DI2_IC25,~(Di2LedData[i]));

				
		
		/*
		dI1 led & 7seg */
        atc_a_write(0x6a,~(Di1LedData[j]));
        atc_a_write(0x6c,~(Di1LedData[j]));
        atc_a_write(0x6e,~(Di1LedData[j]));
		
        atc_a_write(0x68,0xff);
        atc_a_write(0x74,Di1Segment[j]);
        atc_a_write(0x76,Di1Segment[j]);
				
		/* ldm2 led  */		
        atc_a_write(0xa0,LdmTogg);
        atc_a_write(0xa4,LdmTogg);
        atc_a_write(0xa8,LdmTogg);
        atc_a_write(0xac,LdmSegment[j]);
        atc_a_write(0xb0,LdmSegment[j]);
        atc_a_write(0xb4,LdmSegment[j]);
        atc_a_write(0xb8,LdmSegment[j]);
		
		/* ryd1 led & relay */				
        atc_a_write(0x40,Togg);
        atc_a_write(0x44,Ryd1Led[m]);
		
        i++;
        j++;
        m++;
        if(i==8) {
            i = 0;
        }
        if(j==10) {
            j = 0;
        }
        if(m==5) {
            m=0;
        }
        Togg ^= 0x87;
        LdmTogg ^= 0xff;
        PUTCHAR(CR);
        if('q' == GETCHAR()) {
            return;
        }
	}				


}

void sa_KL47()
{
    int i;
    int x;
    while(1) {
        for(i=0xC0;i<=0xCE;i++) {       /* KL47 OEA */
            atc_a_write(i,0);
        }
        for(i=0xD8;i<=0xDE;i++) {
            atc_a_write(i,0);
        }
        for(i=0xD0;i<=0xD6;i++) {       /* KL47 OEB */
            x=atc_a_rd(i);
        }
        atc_a_write(0xC0,0);            /* KL47 CS1 */
        atc_a_write(0xC2,0);

        x=atc_a_rd(0xC4);               /* KL47 CS2R */
        x=atc_a_rd(0xC6);               /* KL47 CS3R */

        for(i=0xC8;i<=0xCE;i++) {       /* KL47 CS4 */
            atc_a_write(i,0);
        }

        atc_a_write(0xD8,0);            /* KL47 CS5 */
        atc_a_write(0xDA,0);

        atc_a_write(0xDC,0);            /* KL47 CS6 */
        atc_a_write(0xCE,0);




        if('q' == GETCHAR()) {
            return;
        }
    }
}

void sa_KL48()
{
    int i;
    int x;
    while(1) {
        for(i=0xC4;i<=0xC6;i++) {
            x=atc_b_rd(i);
        }
        for(i=0xC8;i<=0xCE;i++) {
            x=atc_b_rd(i);
        }
        x=atc_b_rd(0xDA);

        for(i=0xDC;i<=0xDE;i++) {
            x=atc_b_rd(i);
        }

        for(i=0xC0;i<=0xC2;i++) {
            atc_b_write(i,0);
        }

        for(i=0xD0;i<=0xD6;i++) {
            atc_b_write(i,0);
        }
        atc_b_write(0xD8,0);


        atc_b_write(0xC0,0);
        atc_b_write(0xC2,0);

        x=atc_b_rd(0xD4);
        x=atc_b_rd(0xD6);
        atc_b_write(0xD8,0);


        if('q' == GETCHAR()) {
            return;
        }
    }
}

void sa_KL49()
{
    int x=0;
    bit_clear_int_latch(PCLK_MODE);
    ATC_BUS[ATC_MODE] = int_latch;
    s_printf("KL49 Bit Test\n");

    while(1) {
        atc_a_write(0xD8,x);
        x^= 0x0F;               /* SEL0,SEL1,SEL2,ADRC Toggle */
        if('q' == GETCHAR()) {
            return;
        }
    }
}

void sa_IC40()
{
    int i;
    int Val1,Val2,Val3,Val4;


    s_printf("Counter Value...4 Values..?\n");
    s_printf("LSB upper byte..?\n");
    Val1 = GETCHAR1()&0x0f;
    s_printf("LSB lower byte..?\n");
    Val2 = GETCHAR1()&0x0f;
    s_printf("MSB upper byte..?\n");
    Val3 = GETCHAR1()&0x0f;
    s_printf("MSB lower byte..?\n");
    Val4 = GETCHAR1()&0x0f;
    Val1 = (Val1<<4)+Val2;
    Val3 = (Val3<<4)+Val4;

                                        /* Counter 0,16Bit Access,Mode 4 */
        atc_a_write(0xCE,0x34);         /* Control Word Setting */
        atc_a_write(0xC8,Val1);         /* Counter Value Write(LSB) */
        atc_a_write(0xC8,Val3);         /* Counter Value Write(MSB) */
    LCD_str("8253 Count Test ");
    while(1) {
        LCDtest();
        s_printf("Counter LSB: %x ",atc_a_rd(0xC8));     /* LSB Read */
        s_printf("Counter MSB: %x \n",atc_a_rd(0xC8));   /* MSB Read */

        if('q' == GETCHAR()) {
            return;
        }
    }
}

void sa_KL50()
{
    int x=0;

    atc_a_write(0xCE,0x34);     /* Counter 0, Mode 2, Binary Count used.. */

    atc_a_write(0xC8,0x04);     /* LSB Load */
    atc_a_write(0xC8,0x04);     /* MSB Load */

    while(1) {

        bit_clear_int_latch(ATC_A_ALE);         /* A-ALE Low */
        ATC_BUS[ATC_MODE] = int_latch;
							
        bit_set_int_latch(ATC_A_ALE);           /* A-ALE High */
        ATC_BUS[ATC_MODE] = int_latch;

        if('q' == GETCHAR()) {
            return;
        }
    }

}

void sa_KL51()
{
    int x;
    while(1) {
        atc_a_write(0xDC,0xff);     /* CSLSB Active */
        atc_a_write(0xDE,0x07);     /* CSMSB Active */

        atc_a_write(0xD8,0x40);     /* LDAC Active... D6 bit is High */
        atc_a_write(0xC0,0x00);     /* LDAC Disable */

        x=(atc_a_rd(0xDA)&0x01);    /* D0,D1 Data Read */
        s_printf(" %x ",x);

        x=(atc_a_rd(0xDA)&0x02);
        s_printf(" %x ",x);

        if('q' == GETCHAR()) {
            return;
        }
    }

}

void ADConv()
{
    int x,y;
    while(1) {
/*        atc_a_write(0xDC,0xff);
        atc_a_write(0xDE,0x0f);
        atc_a_write(0xD8,0x40);
        atc_a_write(0xC0,0x00);
        atc_a_write(0xD8,0x05);
        Delay_ms(1);
        atc_a_write(0xDC,0x01);
        atc_a_write(0xDE,0x08);
        atc_a_write(0xD8,0x40);
        atc_a_write(0xC0,0x00);
        atc_a_write(0xD8,0x05);
        Delay_ms(1);
        atc_a_write(0xDC,0x00);
        atc_a_write(0xDE,0x08);
        atc_a_write(0xD8,0x40);
        atc_a_write(0xC0,0x00);

        atc_a_write(0xD8,0x05);
        Delay_ms(1);
        atc_a_write(0xDC,0xff);
        atc_a_write(0xDE,0x07);
        atc_a_write(0xD8,0x40);
        atc_a_write(0xC0,0x00);

        atc_a_write(0xD8,0x05);
        Delay_ms(1);
        atc_a_write(0xDC,0x01);
        atc_a_write(0xDE,0x00);
        atc_a_write(0xD8,0x40);
        atc_a_write(0xC0,0x00);

        atc_a_write(0xD8,0x05);
        Delay_ms(1);
        atc_a_write(0xDC,0x00);
        atc_a_write(0xDE,0x00);
        atc_a_write(0xD8,0x40);
        atc_a_write(0xC0,0x00);

        atc_a_write(0xD8,0x05);
        Delay_ms(1); */


        atc_a_write(0xDC,0xff);
        atc_a_write(0xDE,0x0f);
        atc_a_write(0xD8,0x45);
        atc_a_write(0xC0,0x00);
        
        x=atc_a_rd(0xC4);               
        atc_a_write(0xD8,0x0D);
        Delay_us(100);
        atc_a_write(0xD8,0x05); 
        y=atc_a_rd(0xC6);               
	atc_a_write(0xD8,0x0D);
        Delay_us(100);
        atc_a_write(0xD8,0x05);
        
        s_printf("Mode 0: %x %x \n",y,x);
        Delay_ms(100); 

        atc_a_write(0xDC,0x00);
        atc_a_write(0xDE,0x08);
        atc_a_write(0xD8,0x45);
        atc_a_write(0xC0,0x00);

	
        x=atc_a_rd(0xC4);          
        atc_a_write(0xD8,0x0D);
        Delay_us(100);
        atc_a_write(0xD8,0x05); 
        y=atc_a_rd(0xC6);               
	atc_a_write(0xD8,0x0D);
        Delay_us(100);
        atc_a_write(0xD8,0x05);
        s_printf("Mode 1: %x %x \n",y,x);
        Delay_ms(100); 

        atc_a_write(0xDC,0x00);
        atc_a_write(0xDE,0x00);
        atc_a_write(0xD8,0x45);
        atc_a_write(0xC0,0x00);

	x=atc_a_rd(0xC4);               
        atc_a_write(0xD8,0x0D);
        Delay_us(100);
        atc_a_write(0xD8,0x05); 
        y=atc_a_rd(0xC6);               
	atc_a_write(0xD8,0x0D);
        Delay_us(100);
        atc_a_write(0xD8,0x05);
      
        s_printf("Mode 2: %x %x \n",y,x);
        Delay_ms(100); 


        if('q' == GETCHAR()) {
            return;
        }
    }
}

void osc_ic15()
{
	int i=0x80;										/* /SRST,DSEL1,LV2,LV1,IA4,IA3,IA2,IA1 */
	int x=0;
		
	atc_a_write(0x02,i&0x7f);					/* KL-13 Reset enable */
	atc_a_write(0x02,i|0x80);					/* KL-13 reset disable */
		
	atc_a_write(0x26,0x57);						/* Counter 1, Mode 3, LSB,MSB, BCD Count */
	atc_a_write(0x22,4);						/* Counter Value Setting */
	
	atc_a_write(0x30,0x06);						/* swrp1=0,stop1,stop2 disable, osc 1 use.. */
	atc_a_write(0x18,0x00);						/* swrp2=0 */
	
	atc_a_write(0x02,i+0x02);					/* Master A Alternative Signal Setting */
	atc_a_write(0x04,2);
	atc_a_write(0x02,i+0x03);					/* Master A Sampling Frequency Setting */
	atc_a_write(0x04,2);
	atc_a_write(0x02,i+0x04);					/* Master A Slope Setting */
    atc_a_write(0x04,2);
	atc_a_write(0x02,i+0x05);					/* Master A Horizontal Division Number Setting */
	atc_a_write(0x04,2);
	atc_a_write(0x02,i+0x08);					/* Master A latch of clock check counter setting */
	atc_a_write(0x04,0x00);						/* Null Value Setting */
	atc_a_write(0x02,i+0x09);					/* Master A Counter Low Byte */
	atc_a_write(0x04,4);	
	atc_a_write(0x02,i+0x0a);					/* Master A Counter High Byte */
	atc_a_write(0x04,0x00);

	atc_b_write(0x02,i+0x02);					/* Master B Alternative Signal Setting */
	atc_b_write(0x04,2);	
	atc_b_write(0x02,i+0x03);					/* Master B Sampling Frequency Setting */
	atc_b_write(0x04,2);
	atc_b_write(0x02,i+0x04);					/* Master B Slope Setting */
	atc_b_write(0x04,2);
	atc_b_write(0x02,i+0x05);					/* Master B Horizontal Division Number Setting */
	atc_b_write(0x04,2);
	atc_b_write(0x02,i+0x08);					/* Master B latch of clock check counter setting */
	atc_b_write(0x04,0x00);						/* Null Value Setting */
	
	atc_b_write(0x02,i+0x09);					/* Master B Counter Low Byte */
	atc_b_write(0x04,4);
	
	atc_b_write(0x02,i+0x0a);					/* Master B Counter High Byte */
	atc_b_write(0x04,0x00);  
		
		
	while(1) {	
		atc_a_write(0x02,i+0x01);					/* Master A ROM Address Setting */
		atc_a_write(0x04,atc_a_rd(0x10));			/* swrp1,2 value --> address setting */
		
		atc_b_write(0x02,i+0x01);					/* Master B ROM Address Setting */
		atc_b_write(0x04,atc_b_rd(0x10)); 			/* swrp1,2 value --> address setting */
	
	
		atc_a_write(0x02,i&0x7f);					/* KL-13 Reset */
		atc_a_write(0x02,i|0x80);					/* KL-13 Normal State */	
	
		s_printf("a: %x ",atc_a_rd(0x10));			 /* swrp1,2 Read */
		s_printf("FLK : %x \n",atc_a_rd(0x00)&0x80); /* FLK Signal monitoring */
	
		if('q' == GETCHAR()) {
			atc_a_write(0x02,i+0x0b);				 /* KL-13 internal logic counter clear */
			atc_a_write(0x04,0x00);
	        return;
	    }
	}
}

void test_cs5()
{
    int x=0;
    bit_clear_int_latch(PCLK_MODE);
    ATC_BUS[ATC_MODE] = int_latch;         /* Sys Clk Active */

    while(1) {
        atc_a_write(0xD8,x);
        x^=0x07;
        atc_a_write(0xC0,0);

        if('q' == GETCHAR()) {
            return;
        }
    }
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

		/*di2 led*/ 
		

		atc_a_write(ATC_DI2_IC23,i);
		atc_a_write(ATC_DI2_IC24,i);
		atc_a_write(ATC_DI2_IC25,i);	
				
		/*
		atc_a_write(ATC_DI2_IC23,~ATC_DI2_A_LED0);
		atc_a_write(ATC_DI2_IC24,~ATC_DI2_A_LED1);
		atc_a_write(ATC_DI2_IC25,~ATC_DI2_A_LED2);	
		/*
		
		/*
		dI1 led & 7seg */
		atc_a_write(0x6a,i);			
		atc_a_write(0x6c,i);	
		atc_a_write(0x6e,i);	
		
		atc_a_write(0x68,0xff);	/* led on control */			
		atc_a_write(0x74,i);	
		atc_a_write(0x76,i);	
				
		/* ldm2 led  */		
		atc_a_write(0xa0,i);			
		atc_a_write(0xa4,i);	
		atc_a_write(0xa8,i);					
		atc_a_write(0xac,i);	
		atc_a_write(0xb0,i);	
		atc_a_write(0xb4,i);					
		atc_a_write(0xb8,i);	
		
		/* ryd1 led & relay */				
        atc_a_write(0x40,i<<7);
        atc_a_write(0x44,~(i++));
		
		/*
		atc_a_write(ATC_DI2_IC23,i);
		atc_a_write(ATC_DI2_IC24,i);
		atc_a_write(ATC_DI2_IC25,i++);
		*/						
		PUTCHAR(CR);		
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
/*  Interrupt initz routine                                             */
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
asm("IVT:   .space  9           ");
asm("       .word   _c_int09    ");
asm("       .word   _c_int10    ");
asm("		.data				");
asm("_ITTP:					");	
asm("		.word	IVT			"); 
 	  
void main()
{
    int Val=0;
  	Init_DSP(); Delay_ms(50);			/* initialize DSP, 8255A, LCD */
  	Init_8255();
  	Init_LCD();
  	Init_8251();						/* initialize 8251A */

  	Beep();
  

    initz_int_tint1();

  	Delay_ms(50);
  	
 	atc_all_reset();
	ATC_BUS[ATC_MODE] = int_latch;		/* initz control latch */
    LCD_str("ATC-Block Test..");
    s_printf("ATC-block Test Program...\n");
    s_printf("Hyundai Information Technology...\n");
    s_printf("Target CPU is TMS320C32...\n");
    s_printf("\n");
    s_printf("\n");
    s_printf("Menu Select..\n");
    s_printf("1 --> RYD1 Board Test\n");
    s_printf("2 --> DI2 Board Test\n");
    s_printf("3 --> DI1 Board Test\n");
    s_printf("4 --> LDM2 Board Test\n");
    s_printf("5 --> Relay Test\n");
    s_printf("6 --> All Test\n");
    s_printf("7 --> 8253(DI1) Test\n");
    s_printf("8 --> Sys Clk on\n");
    s_printf("9 --> SW Clk on\n");
    s_printf("q --> quit\n");

    while(1)
    {
        Val = GETCHAR1();
        switch(Val&0xff) {
            case '1' : s_printf("Running...\n");
                       LCD_clear();
                       Delay_ms(50);
                       ryd1test();
                       break;
            case '2' : s_printf("Running...\n");
                       LCD_clear();
                       Delay_ms(50);
                       di2test();
                       break;
            case '3' : s_printf("Running...\n");
                       LCD_clear();
                       Delay_ms(50);
                       di1test();
                       break;
            case '4' : s_printf("Running...\n");
                       LCD_clear();
                       Delay_ms(50);
                       ldm2test();
                       break;
            case '5' : s_printf("Running...\n");
                       LCD_clear();
                       Delay_ms(50);
                       relaytest();
                       break;
            case '6' : s_printf("Running...\n");
                       LCD_clear();
                       Delay_ms(50);
                       alltest();
                       break;
            case '7' : s_printf("Running...\n");
                       LCD_clear();
                       Delay_ms(50);
                       cnttest();
                       break;
            case '8' : sel_pclk(SYS_CLK);
                       s_printf("Sys Clock Output\n");
                       break;
            case '9' : sel_pclk(SW_CLK);
                       s_printf("SW Clock Output\n");
                       break;
            case '0' : sa_KL47();
                       break;

            case 'a' : ADConv();
                       break;
			case 'c' : osc_ic15();
					   break;	                       
            case 'r' : atc_all_reset();
                       break;
            default  :
                       s_printf("1 --> RYD1 Board Test\n");
                       s_printf("2 --> DI2 Board Test\n");
                       s_printf("3 --> DI1 Board Test\n");
                       s_printf("4 --> LDM2 Board Test\n");
                       s_printf("5 --> Relay Test\n");
                       s_printf("6 --> All Test\n");
                       s_printf("7 --> 8253(DI1) Test\n");
                       s_printf("8 --> Sys Clk on\n");
                       s_printf("9 --> SW Clk on\n");
                       s_printf("q --> quit\n");
                       break;
        }
	}
}
