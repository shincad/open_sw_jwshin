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

unsigned char DACData[6][2] = {{0xff,0x0f},     /* AD7248A */
                               {0x01,0x08},
                               {0x00,0x08},
                               {0xff,0x07},
                               {0x01,0x00},
                               {0x00,0x00}};


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

unsigned char IC910_Data[8] = {0x10,0x04,0x01,0x10,0x08,0x04,0x02,0x01};
unsigned char IC6_Data[5] = {0xdf,0xef,0xf7,0xfb,0xfd};

/*------------------------------------------------------------------*/
/*              RYD1,2 Board Total Test Routine                     */
/*------------------------------------------------------------------*/
void ryd1()
{
	int i=0;
	int k=0;
	unsigned char FRATogg=0;				
	atc_a_write(0x40,0);										/* Port Initialize */
	atc_a_write(0x42,0);										/* Port Initialize */
	while(1) {
		atc_a_write(0x40,FRATogg);								/* FRA Toggle */
		if(i<3) {
			atc_a_write(0x40,IC910_Data[i]);					/* IC9 Test FRA:D7,3RA:D4,2RA:D2,1RA:D0 */				
		}
		else {
			atc_a_write(0x42,IC910_Data[i]);					/* IC10 Test : 5RL,4RL,3RL,2RL,1RL : D4,D3,D2,D1,D0 */
		}
		s_printf("IC33 Read :%d, %x \n",i,atc_a_rd(0x4a));		/* 3RA,2RA,1RA,5RL,4RL,3RL,2RL,1RL Read */
		atc_a_write(0x44,IC6_Data[k]);							/* IC10 Test : D5,D4,D3,D2,D1 */			
		s_printf("IC29 Read : %x \n",atc_a_rd(0x48));			/* IC29 Read */
		s_printf("IC37 Read : %x \n",atc_a_rd(0x4c));			/* IC37 Read */
		s_printf("IC24 Read : %x \n",atc_a_rd(0x4e));			/* IC24 Read */
		i++;
		k++;
		if(i==8) {
			i=0;
			atc_a_write(0x40,0);
			atc_a_write(0x42,0);
			FRATogg ^= 0x80;
		}
		if(k==5) {
			k=0;
			atc_a_write(0x44,0);
		}
		Delay_ms(50);
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
    atc_a_write(0x68,0x8f);
    atc_b_write(0x68,0x8f);

    while(1) {

        atc_a_write(0x26,0x50);         /* Control Word Setting */
        atc_a_write(0x22,0xff);         /* Counter Value Write(LSB) */
        s_printf("Counter Value1: %x \n",atc_a_rd(0x22));     /* LSB Read */

        atc_a_write(0x2e,0x50);
        atc_a_write(0x2a,0xff);
        s_printf("Counter Value2: %x \n",atc_a_rd(0x2a));     /* LSB Read */

        atc_a_write(0x66,0x97);								  /* IC2 */	
        atc_a_write(0x64,0x04);
        s_printf("Counter Value3: %x \n",atc_a_rd(0x64));     /* LSB Read */


        atc_a_write(0x76,0x17);								  /* IC1 Counter 0 */ 		
        atc_a_write(0x70,0xff);
        s_printf("Counter Value4-0: %x \n",atc_a_rd(0x70));     /* LSB Read */
        
        
        atc_a_write(0x76,0x57);								  /* IC1 Counter 1 */ 		
        atc_a_write(0x72,0xff);
        s_printf("Counter Value4-1: %x \n",atc_a_rd(0x72));     /* LSB Read */

        atc_b_write(0x7e,0x57);
        atc_b_write(0x7a,0xff);
        s_printf("Counter Value5: %x \n",atc_b_rd(0x7a));     /* LSB Read */

        atc_a_write(0xce,0x50);
        atc_a_write(0xca,0xff);
        s_printf("Counter Value6: %x \n",atc_a_rd(0xca));     /* LSB Read */
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
    int osc_var=0x80;
    int osc_cnt=0;
    int dummy;
    
	s_printf("\n");
    LCD_str("All Test........");
    
    
    atc_a_write(0x02,osc_var&0x7f);					/* KL-13 Reset enable */
	atc_a_write(0x02,osc_var|0x80);					/* KL-13 reset disable */
		
	atc_a_write(0x26,0x57);						/* Counter 1, Mode 3, LSB,MSB, BCD Count */
	atc_a_write(0x22,4);						/* Counter Value Setting */

    atc_a_write(0x2e,0x57);
    atc_a_write(0x2a,4);
	
	atc_a_write(0x30,0x02);						/* swrp1=0,stop1,stop2 disable, osc 1 use.. */
	atc_a_write(0x18,0x02);						/* swrp2=0 */
	
	atc_a_write(0x02,osc_var+0x02);					/* Master A Alternative Signal Setting */
	atc_a_write(0x04,16);
	atc_a_write(0x02,osc_var+0x03);					/* Master A Sampling Frequency Setting */
	atc_a_write(0x04,16);
	atc_a_write(0x02,osc_var+0x04);					/* Master A Slope Setting */
    atc_a_write(0x04,32);
	atc_a_write(0x02,osc_var+0x05);					/* Master A Horizontal Division Number Setting */
	atc_a_write(0x04,16);
	atc_a_write(0x02,osc_var+0x08);					/* Master A latch of clock check counter setting */
	atc_a_write(0x04,0x00);						/* Null Value Setting */
	atc_a_write(0x02,osc_var+0x09);					/* Master A Counter Low Byte */
	dummy=atc_a_rd(0x08);	
	atc_a_write(0x02,osc_var+0x0a);					/* Master A Counter High Byte */
	dummy=atc_a_rd(0x08);

	atc_b_write(0x02,osc_var+0x02);					/* Master B Alternative Signal Setting */
	atc_b_write(0x04,16);	
	atc_b_write(0x02,osc_var+0x03);					/* Master B Sampling Frequency Setting */
	atc_b_write(0x04,16);
	atc_b_write(0x02,osc_var+0x04);					/* Master B Slope Setting */
	atc_b_write(0x04,32);
	atc_b_write(0x02,osc_var+0x05);					/* Master B Horizontal Division Number Setting */
	atc_b_write(0x04,16);
	atc_b_write(0x02,osc_var+0x08);					/* Master B latch of clock check counter setting */
	atc_b_write(0x04,0x00);							/* Null Value Setting */
	
	atc_b_write(0x02,osc_var+0x09);					/* Master B Counter Low Byte */
	dummy=atc_b_rd(0x0a);
	
	atc_b_write(0x02,osc_var+0x0a);					/* Master B Counter High Byte */
	dummy=atc_b_rd(0x0a);  
	
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
        atc_a_write(0x44,Ryd1Led[m]);
		
		atc_a_write(0x02,osc_var+0x01);					/* Master A ROM Address Setting */
		atc_a_write(0x04,osc_cnt);						/* swrp1,2 value --> address setting */
		
		atc_b_write(0x02,osc_var+0x01);					/* Master B ROM Address Setting */
		atc_b_write(0x04,osc_cnt); 						/* swrp1,2 value --> address setting */
		osc_cnt++;
	
		atc_a_write(0x02,osc_var&0x7f);					/* KL-13 Reset */
		atc_a_write(0x02,osc_var|0x80);					/* KL-13 Normal State */	
	
		s_printf("a: %x ",atc_a_rd(0x10));			 	/* swrp1,2 Read */
		
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
        if(osc_cnt==0xff) {
        	osc_cnt=0;
        }
        Togg ^= 0x87;
        LdmTogg ^= 0xff;
        atc_a_write(0x40,LdmTogg);
        atc_a_write(0x42,LdmTogg);
        PUTCHAR(CR);
        if('q' == GETCHAR()) {
        	atc_a_write(0x02,osc_var+0x0b);
        	atc_a_write(0x04,0x00);
        	atc_b_write(0x02,osc_var+0x0b);
        	atc_b_write(0x04,0x00);
            return;
        }
	}				


}

/*------------------------------------------------------------------*/
/*              Ryd2 Test Routine                                   */
/*------------------------------------------------------------------*/
void Ryd2()
{
	int i;
	while(1) {
		atc_a_write(0x40,0xff);
		atc_a_write(0x42,0x00);
		Delay_ms(50);
		atc_a_write(0x40,0x00);
		atc_a_write(0x42,0xff);
		Delay_ms(50);
		
		
	    if('q' == GETCHAR()) {
	            return;
	        }
		
	}
}


/*------------------------------------------------------------------*/
/*              Sa2 Test Routine                                    */
/*------------------------------------------------------------------*/
void Sa2()
{
    int x;
    atc_a_write(0xCE,0x17);     			         /* IC40 Counter Control Word Set */ 
	atc_a_write(0xC8,0x04);             			 /* Counter LSB Value Set */        
	while(1) {
	    for(x=0;x<6;x++) {
	        atc_a_write(0xDC,DACData[x][0]);             /* AD7248A LSB Data Write */
	        atc_a_write(0xDE,DACData[x][1]);             /*         MSB Data Write */
	        atc_a_write(0xD8,0x40);                      /* LDAC Active (D6 Bit)   */
	        atc_a_write(0xD8,0x00);                      /* LDAC Disable           */
		}

		for(x=0;x<=7;x++) {
			atc_a_write(0xD8,x);						 /* ADG508A SEL2,SEL1,SEL0(D2,D1,D0) Set */
			atc_a_write(0xD8,x&0x07);					 /* ADRC Low  : AD674B */
			atc_a_write(0xD8,x|0x08);					 /* ADRC High : AD674B */
			
			s_printf("%d Low Byte : %x ",x,atc_a_rd(0xC4));	 	 /* AD674B Low Byte Read */	
			s_printf("High Byte : %x \n",(atc_a_rd(0xC6)&0x0f)); /* AD674B High Byte(4 Bit) Read */
		}
	    if('q' == GETCHAR()) {
	        return;
	    }
	}
}


/*------------------------------------------------------------------*/
/*              Card Reader Definition                              */
/*------------------------------------------------------------------*/
// 0x58 --> Port 0 : Caution ~!! Don't Access Port 0...(Device will be out of order...) 
// 0x5A --> Port 1 : Command Port
// 0x5C --> Port 2 : Mode Change Port
// 0x5E --> Port 3 : Card Data I/O Port

#define		CARD_PORT1			0x5A
#define		CARD_PORT2			0x5C
#define		CARD_PORT3			0x5E
#define		CARD_NOEMPTY		0xff
#define		CARD_EMPTY			0x00
#define		XREQ_S				while((atc_a_rd(CARD_PORT2)&0x80) == 1);Delay_ms(10)	/* Start XREQ Check, Delay 10ms */
#define		XREQ_N				while((atc_a_rd(CARD_PORT2)&0x80) == 0);Delay_ms(10)	/* Normal XREQ Check, Delay 10ms */
#define		ValueSize			100
unsigned char ValSave[ValueSize];

/*------------------------------------------------------------------*/
/*              Card Write Routine                                  */
/*------------------------------------------------------------------*/
void CardWr()
{
	unsigned int i=0;
	atc_a_write(CARD_PORT1,0x00);			/* Reset Command */
	atc_a_write(CARD_PORT2,0x07);			/* Power ON */
	Delay_us(400);							/* Delay 400us */
	atc_a_write(CARD_PORT2,0x01);			/* Driver Reset Mode */
	Delay_us(5);							/* Delay 5us */
	atc_a_write(CARD_PORT1,0x11);			/* Card Address Set Command */
	atc_a_write(CARD_PORT3,0x00);			/* Dummy Output */
	XREQ_S;									
	atc_a_write(CARD_PORT2,0x15);			/* 1 Byte Tranfer Mode */
	XREQ_N;
	atc_a_write(CARD_PORT3,0x80);			/* Address : 1 A22 A21 A20 A19 A18 A17 A16 */
	XREQ_N;
	atc_a_write(CARD_PORT3,0x00);			/* Address : A15 A14 A13 A12 A11 A10 A9 A8 */
	XREQ_N;
	atc_a_write(CARD_PORT3,0x00);			/* Address : A7 A6 A5 A4 A3 A2 A1 A0 */
	XREQ_N;
	atc_a_write(CARD_PORT3,0x00);			/* Address : Dummy */
	XREQ_N;
	atc_a_rd(CARD_PORT3);					/* XREQ Reset */
	XREQ_N;
	atc_a_write(CARD_PORT1,0x41);			/* Card Write Command */
	for(i=0;i<ValueSize;i++) {				/* Data Write */
		atc_a_write(CARD_PORT3,i);
		XREQ_N;
	}
	atc_a_write(CARD_PORT1,0x00);			/* Reset Command */
	atc_a_rd(CARD_PORT3);					/* XREQ Reset */
	XREQ_N;
	atc_a_write(CARD_PORT2,0x00);			/* Power OFF Mode */
	Delay_ms(20);  							/* Power OFF Delay */
	s_printf("Write Complete..\n");
}
 
/*------------------------------------------------------------------*/
/*              Card Read Routine                                   */
/*------------------------------------------------------------------*/
void CardRd()
{
	unsigned int i=0;
	atc_a_write(CARD_PORT1,0x00);			/* Reset Command */
	atc_a_write(CARD_PORT2,0x07);			/* Power ON */
	Delay_us(400);							/* Delay 400us */
	atc_a_write(CARD_PORT2,0x01);			/* Driver Reset Mode */
	Delay_us(5);							/* Delay 5us */
	atc_a_write(CARD_PORT1,0x80);			/* Card Read Command */
	atc_a_write(CARD_PORT3,0x00);			/* Dummy Output */
	XREQ_S;
	atc_a_write(CARD_PORT2,0x15);			/* 1 Byte Transfer Mode */
	XREQ_N;
	atc_a_write(CARD_PORT1,0x88);			/* Card Address Set Mode */
	XREQ_N;
	atc_a_write(CARD_PORT3,0x00);			/* Address : A16 0 0 0 0 0 0 0 */
	XREQ_N;            
	atc_a_write(CARD_PORT3,0x40);			/* Address : A8 1 A22 A21 A20 A19 A18 A17 */
	XREQ_N;            
	atc_a_write(CARD_PORT3,0x00);   		/* Address : A0 A15 A14 A13 A12 A11 A10 A9 */
	XREQ_N;            
	atc_a_write(CARD_PORT3,0x00);        	/* Address : 0 A7 A6 A5 A4 A3 A2 A1 */
	XREQ_N;            
	atc_a_write(CARD_PORT3,0x00);           /* Address : Dummy */
	XREQ_N;            
	atc_a_rd(CARD_PORT3);					/* XREQ Reset */
	XREQ_N;            
	atc_a_write(CARD_PORT1,0x80);			/* Card Read Command */
	atc_a_write(CARD_PORT2,0x17);			/* Card Read Mode */
	for(i=0;i<1;i++) {						/* Dummy Data Read (1 Byte) */
		atc_a_rd(CARD_PORT3);
		XREQ_N;
	}
	for(i=0;i<ValueSize;i++) {				/* Data Read */
		ValSave[i] = atc_a_rd(CARD_PORT3);
		XREQ_N;
	}
	atc_a_write(CARD_PORT1,0x00);			/* Reset Command */
	atc_a_rd(CARD_PORT3);					/* XREQ Reset */
	XREQ_N;            
	atc_a_write(CARD_PORT2,0x00);			/* Power OFF Mode */
	Delay_ms(20);
	
	for(i=0;i<ValueSize;i++) {				/* Read Data Serial Output */
		s_printf("%d ",ValSave[i]);
	}
	s_printf("\n");
}

void Card_Init()
{
	int i;
	atc_a_write(CARD_PORT1,0x00);					/* Card Address Reset */
	atc_a_write(CARD_PORT2,0x07);					/* Driver Set Mode */
	Delay_us(400);									/* Delay 400us */
	if(atc_a_rd(CARD_PORT3) == CARD_NOEMPTY) {		/* Card Check 	0xff : Card Not Empty, 0x00 : Card Empty	*/
		s_printf("Card Detection Ok~!\n");
		atc_a_write(CARD_PORT2,0x01);				/* Driver Reset Mode */
		Delay_us(5);								/* Delay 5us */
		atc_a_write(CARD_PORT2,0x00);				/* Power OFF Mode */
		Delay_ms(100);  							/* Delay 100ms */
	} 
	else {
		s_printf("Card is empty..\n");				/* Card Empty */
		return;
	} 
	
	
	atc_a_write(CARD_PORT1,0x00);					/* Reset Command */
	atc_a_write(CARD_PORT2,0x07);					/* Power ON */
	Delay_us(400);									/* Delay 400us */
	atc_a_write(CARD_PORT2,0x01);					/* Driver Reset Mode */
	Delay_us(5);									/* Delay 5us */
	atc_a_write(CARD_PORT1,0x11);					/* Card Address Set Command */
	atc_a_write(CARD_PORT3,0x00);					/* Dummy Output */
	XREQ_S;
	atc_a_write(CARD_PORT2,0x15);					/* 1 Byte Transfer Mode */
	XREQ_N;
	atc_a_write(CARD_PORT3,0x80);					/* Address */
	XREQ_N;
	atc_a_write(CARD_PORT3,0x00);					/* Address */
	XREQ_N;
	atc_a_write(CARD_PORT3,0x00);					/* Address */
	XREQ_N;
	atc_a_write(CARD_PORT3,0x00);					/* Address */
	XREQ_N;
	atc_a_rd(CARD_PORT3);							/* XREQ Reset */
	XREQ_N;
	atc_a_write(CARD_PORT1,0x41);					/* Card Write Command */
	for(i=0;i<ValueSize;i++) {						/* Card Data Initialization : 0x00 */	
		atc_a_write(CARD_PORT3,0);
		XREQ_N;
	}
	atc_a_write(CARD_PORT1,0x00);					/* Reset Command */
	atc_a_rd(CARD_PORT3);							/* XREQ Reset */
	XREQ_N;
	atc_a_write(CARD_PORT2,0x00);					/* Power OFF Mode */
	Delay_ms(20);  									/* Power OFF Delay */	
	s_printf("Card Initial Complete..\n");			
	
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
	int c,d,e,f;
		
	atc_a_write(0x02,i&0x7f);					/* KL-13 Reset enable */
	atc_a_write(0x02,i|0x80);					/* KL-13 reset disable */
		
	atc_a_write(0x26,0x57);						/* CTC1 Counter 1, Mode 3, LSB BCD Count */
	atc_a_write(0x22,4);						/* Counter Value Setting */
	
    atc_a_write(0x2e,0x57);                     /* CTC2 Counter 1, Mode 3, LSB BCD Count */
	atc_a_write(0x2a,4);						/* Counter Value Setting */
	
	atc_a_write(0x30,0x02);						/* swrp1=0,stop1,stop2=0, osc 1 use.. */
	atc_a_write(0x18,0x02);						/* swrp2=0 */
	
	atc_a_write(0x02,i+0x02);					/* Master A Alternative Signal Setting */
	atc_a_write(0x04,16);
	
	atc_a_write(0x02,i+0x02);					/* Slave A Alternative Signal Setting */
	atc_a_write(0x06,16);
	
	atc_a_write(0x02,i+0x03);					/* Master A Sampling Frequency Setting */
	atc_a_write(0x04,32);
	
	atc_a_write(0x02,i+0x03);					/* Slave A Sampling Frequency Setting */
	atc_a_write(0x06,32);
	
	atc_a_write(0x02,i+0x04);					/* Master A Slope Setting */
    atc_a_write(0x04,32);
    
    atc_a_write(0x02,i+0x04);					/* Salve A Slope Setting */
    atc_a_write(0x04,32);
    
	atc_a_write(0x02,i+0x05);					/* Master A Horizontal Division Number Setting */
	atc_a_write(0x04,16);
	
	atc_a_write(0x02,i+0x05);					/* Slave A Horizontal Division Number Setting */
	atc_a_write(0x06,16);
	
	atc_a_write(0x02,i+0x08);					/* Master A latch of clock check counter setting */
	atc_a_write(0x04,0x00);						/* Null Value Setting */
	
	atc_a_write(0x02,i+0x08);					/* Slave A latch of clock check counter setting */	
	atc_a_write(0x06,0x00);						/* Null Value Setting */
	
	atc_a_write(0x02,i+0x09);					/* Master A Counter Low Byte */
	c=atc_a_rd(0x08);	
	
	atc_a_write(0x02,i+0x09);					/* Slave A Counter Low Byte */
	d=atc_a_rd(0x0c);
	
	atc_a_write(0x02,i+0x0a);					/* Master A Counter High Byte */
	c=atc_a_rd(0x08);

	atc_a_write(0x02,i+0x0a);					/* Slave A Counter High Byte */
	d=atc_a_rd(0x0c);
	
	atc_b_write(0x02,i+0x02);					/* Master B Alternative Signal Setting */
	atc_b_write(0x04,16);	

	atc_b_write(0x02,i+0x02);					/* Slave B Alternative Signal Setting */
	atc_b_write(0x06,16);			

	atc_b_write(0x02,i+0x03);					/* Master B Sampling Frequency Setting */
	atc_b_write(0x04,32);

	atc_b_write(0x02,i+0x03);					/* Slave B Sampling Frequency Setting */
	atc_b_write(0x06,32);

	atc_b_write(0x02,i+0x04);					/* Master B Slope Setting */
	atc_b_write(0x04,32);

	atc_b_write(0x02,i+0x04);					/* Slave B Slope Setting */
	atc_b_write(0x06,32);

	atc_b_write(0x02,i+0x05);					/* Master B Horizontal Division Number Setting */
	atc_b_write(0x04,16);

	atc_b_write(0x02,i+0x05);					/* Slave B Horizontal Division Number Setting */
	atc_b_write(0x06,16);

	atc_b_write(0x02,i+0x08);					/* Master B latch of clock check counter setting */
	atc_b_write(0x04,0x00);						/* Null Value Setting */

	atc_b_write(0x02,i+0x08);					/* Slave B latch of clock check counter setting */	
	atc_b_write(0x06,0x00);						/* Null Value Setting */

	atc_b_write(0x02,i+0x09);					/* Master B Counter Low Byte */
	e=atc_b_rd(0x0a);

	atc_b_write(0x02,i+0x09);					/* Slave B Counter Low Byte */
	f=atc_b_rd(0x0e);

	atc_b_write(0x02,i+0x0a);					/* Master B Counter High Byte */
	e=atc_b_rd(0x0a);  
	
	atc_b_write(0x02,i+0x0a);					/* Slave B Counter High Byte */	
	f=atc_b_rd(0x0e);
	
	while(1) {	
		atc_a_write(0x02,i+0x01);					/* Master A ROM Address Setting */
 		atc_a_write(0x04,atc_a_rd(0x10));			/* swrp1,2 value --> address setting */
				
		atc_b_write(0x02,i+0x01);					/* Master B ROM Address Setting */
		atc_b_write(0x04,atc_b_rd(0x10)); 			/* swrp1,2 value --> address setting */
					
		atc_a_write(0x02,i&0x7f);					/* KL-13 Reset */
		atc_a_write(0x02,i|0x80);					/* KL-13 Normal State */	

		if('q' == GETCHAR()) {
			atc_a_write(0x02,i+0x0b);
			atc_a_write(0x04,0);
			
			atc_a_write(0x02,i+0x0b);
			atc_a_write(0x06,0);
			
			atc_b_write(0x02,i+0x0b);
			atc_b_write(0x04,0);
			
			atc_b_write(0x02,i+0x0b);
			atc_b_write(0x06,0);
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
    s_printf("a --> RYD Total Board Test\n");
    s_printf("i --> Card Init\n");
    s_printf("w --> Card Write\n");
    s_printf("d --> Card Read\n");
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
            case '0' : sa_KL49();
                       break;

            case 'a' : ryd1();
                       break;
            case 'c' : cnttest();
					   break;	                       
            case 'r' : atc_all_reset();
                       break;
            case 's' : Sa2();
                       break;
            case 'd' : CardRd();
            		   break;	
			case 'i' : Card_Init();
					   break;
		    case 'w' : CardWr();
		    		   break;
			case 'x' : Ryd2();
					   break;			    		           		              

            default  :
                       s_printf("a --> RYD Total Board Test\n");
                       s_printf("i --> Card Init\n");
    				   s_printf("w --> Card Write\n");
    				   s_printf("d --> Card Read\n");
                       break;
        }
	}
}
