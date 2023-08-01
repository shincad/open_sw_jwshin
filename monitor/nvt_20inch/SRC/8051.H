#ifndef	_8051_H_
#define _8051_H_

/*==============================================================================
  Internal Special Function Registers
==============================================================================*/
	sfr ACC    = 0xE0;
	sfr B      = 0xF0;
	sfr PSW    = 0xD0;
	sfr SP     = 0x81;
	sfr DPL    = 0x82;
	sfr DPH    = 0x83;
	sfr P0     = 0x80;
	sfr P1     = 0x90;
	sfr P2     = 0xA0;
	sfr P3     = 0xB0;
	sfr IE     = 0xA8;
	sfr IP     = 0xB8;
	sfr PCON   = 0x87;
	sfr TCON   = 0x88;
	sfr TMOD   = 0x89;
	sfr TL0    = 0x8A;
	sfr TL1    = 0x8B;
	sfr TH0    = 0x8C;
	sfr TH1    = 0x8D;
	sfr T2CON  = 0xC8;
	sfr RCAP2L = 0xCA;
	sfr RCAP2H = 0xCB;
	sfr TL2    = 0xCC;
	sfr TH2    = 0xCD;
	sfr SCON   = 0x98;
	sfr SBUF   = 0x99;


/*==============================================================================
  Bit Addressable Function Register
==============================================================================*/
/*---PSW---*/
	sbit CY    = 0xD7;
	sbit AC    = 0xD6;
	sbit F0    = 0xD5;
	sbit RS1   = 0xD4;
	sbit RS0   = 0xD3;
	sbit OV    = 0xD2;
	sbit P     = 0xD0;
/*---TCON---*/
	sbit TF1   = 0x8F;
	sbit TR1   = 0x8E;
	sbit TF0   = 0x8D;
	sbit TR0   = 0x8C;
	sbit IE1   = 0x8B;
	sbit IT1   = 0x8A;
	sbit IE0   = 0x89;
	sbit IT0   = 0x88;
/*---T2CON---*/
	sbit TF2   = 0xCF;
	sbit EXF2  = 0xCE;
	sbit RCLK  = 0xCD;
	sbit TCLK  = 0xCC;
	sbit EXEN2 = 0xCB;
	sbit TR2   = 0xCA;
	sbit CT2   = 0xC9;
	sbit CPRL2 = 0xC8;
/*---SCON---*/
	sbit SM0   = 0x9F;
	sbit SM1   = 0x9E;
	sbit SM2   = 0x9D;
	sbit REN   = 0x9C;
	sbit TB8   = 0x9B;
	sbit RB8   = 0x9A;
	sbit TI    = 0x99;
	sbit RI    = 0x98;
/*---IE---*/
	sbit EA    = 0xAF;
	sbit ET2   = 0xAD;
	sbit ES    = 0xAC;
	sbit ET1   = 0xAB;
	sbit EX1   = 0xAA;
	sbit ET0   = 0xA9;
	sbit EX0   = 0xA8;
/*---IP---*/
	sbit PT2   = 0xBD;
	sbit PS    = 0xBC;
	sbit PT1   = 0xBB;
	sbit PX1   = 0xBA;
	sbit PT0   = 0xB9;
	sbit PX0   = 0xB8;

/*==============================================================================
  I/O port function definition
==============================================================================*/
/*---P0---*/
	sbit P00 = 0x80;
	sbit P01 = 0x81;
	sbit P02 = 0x82;
	sbit P03 = 0x83;
	sbit P04 = 0x84;
	sbit P05 = 0x85;
	sbit P06 = 0x86;
	sbit P07 = 0x87;
/*---P1---*/
	sbit P10 = 0x90;
	sbit P11 = 0x91;
	sbit P12 = 0x92;
	sbit P13 = 0x93;
	sbit P14 = 0x94;
	sbit P15 = 0x95;
	sbit P16 = 0x96;
	sbit P17 = 0x97;
/*---P2---*/
	sbit P20 = 0xA0;
	sbit P21 = 0xA1;
	sbit P22 = 0xA2;
	sbit P23 = 0xA3;
	sbit P24 = 0xA4;
	sbit P25 = 0xA5;
	sbit P26 = 0xA6;
	sbit P27 = 0xA7;
/*---P3---*/
	sbit P30 = 0xB0;
	sbit P31 = 0xB1;
	sbit P32 = 0xB2;
	sbit P33 = 0xB3;
	sbit ISCL = 0xB4;
	sbit ISDA = 0xB5;
	sbit P36 = 0xB6;
	sbit P37 = 0xB7;
#endif
