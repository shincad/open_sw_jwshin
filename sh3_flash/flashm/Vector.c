/****************************************************************************/
/*																			*/
/*			INT Handler Process												*/
/*																			*/
/*			Copyright	:: Phoenix Information Technology					*/
/*			Cpu			:: SH3												*/
/*			Language	:: SHC												*/
/*			File Name	:: vector.c											*/
/*																			*/
/****************************************************************************/
#include "sh7709a.h"
#include "def.h"
#include "ext.h"
#if (_GCC_ == 1)
#include "gmachine3.h"
#endif
#if (_HITACHI_ == 1)
#include <smachine.h>
#endif

extern void nmi(void);
extern void irl15(void);
extern void irl14(void);
extern void irl13(void);
extern void irl12(void);
extern void irl11(void);
extern void irl10(void);
extern void irl9(void);
extern void irl8(void);
extern void irl7(void);
extern void irl6(void);
extern void irl5(void);
extern void irl4(void);
extern void irl3(void);
extern void irl2(void);
extern void irl1(void);
extern void tuni0(void);
extern void tuni1(void);
extern void tuni2(void);
extern void ticpi2(void);
extern void ati(void);
extern void pri(void);
extern void cui(void);
extern void eri(void);
extern void rxi(void);
extern void txi(void);
extern void tei(void);
extern void iti(void);
extern void rcmi(void);
extern void rovi(void);
extern void irq4(void);
extern void irq5(void);
extern void pint0(void);
extern void pint8(void);
extern void dei0(void);
extern void dei1(void);
extern void dei2(void);
extern void dei3(void);
extern void eri1(void);
extern void rxi1(void);
extern void bri1(void);
extern void txi1(void);
extern void eri2(void);
extern void rxi2(void);
extern void bri2(void);
extern void txi2(void);
extern void adi(void);

void vec(void);
void stack_push(int *);
void stack_pop(int *);

extern const int int_pri[];

int pointer;
int stack[20][2];

void (* const vect_table[])(void) = {
	nmi,0,											/* nmi		*/
	irl15,irl14,irl13,irl12,irl11,irl10,irl9,irl8,	/* irl15-8	*/
	irl7 ,irl6 ,irl5 ,irl4 ,irl3 ,irl2 ,irl1 , 0,	/* irl7-1	*/
	tuni0, tuni1, tuni2, ticpi2,					/* TMU0-2	*/
	ati, pri, cui,									/* RTC		*/
	eri, rxi, txi, tei,								/* SCI		*/
	iti,											/* WDT		*/
	rcmi, rovi,0,0,									/* Refresh	*/
	0,0,0,0,irq4,irq5,0,0,							/* irq4,5	*/
	pint0,pint8,0,0,0,0,0,0,						/* pint0,8	*/
	dei0,dei1,dei2,dei3,							/* DMAC		*/
	eri1,rxi1,bri1,txi1,							/* SCI1		*/
	eri2,rxi2,bri2,txi2,							/* SCI2		*/
	adi												/* A/D		*/
};

const int int_pri[] = {
	15, 0,							/* nmi		*/
	15,14,13,12,11,10, 9, 8,		/* irl15-8	*/
	 7, 6, 5, 4, 3, 2, 1, 0,		/* irl7-1	*/
	10, 0, 0, 0,					/* TMU0-2	*/
	 0, 0, 0,						/* RTC		*/
	 0, 0, 0, 0,					/* SCI		*/
	 0,								/* WDT		*/
	 0, 0, 0, 0,					/* Refresh	IPRB(11-8)	*/
	 0, 0, 0, 0, 0, 0, 0, 0,		/* IRQ0-5	IPRC,IPRD(7-0)	*/
	 0, 0, 0, 0, 0, 0, 0, 0,		/* PINT		IPRD(15-8)	*/
	 0, 0, 0, 0,					/* DMAC		IPRE(15-12)	*/
	 0, 0, 0, 0,					/* IrDA		IPRE(11-8)	*/
	 7, 7, 7, 7,					/* SCIF		IPRE(7-4)	*/
	 0								/* ADC		IPRE(3-0)	*/
};


void int100(void)
{
	for(;;);
}

void int400(void)
{
	for(;;);
}

void vec(void)
{
	unsigned long tmp;
	
	tmp = ((INT.INTEVT2 - 0x000001c0) >> 5) & 0x0000007f;
	
										/*set sr*/
	set_cr((get_cr() & 0xefffff0f)+(int_pri[tmp] << 4));
	(vect_table[tmp])();				/*jump interrupt routine*/
	set_cr(get_cr() | 0x10000000);		/*set BL bit*/
}
