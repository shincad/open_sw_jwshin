/****************************************************************************/
/*																			*/
/*			SCIF Comm Process												*/
/*																			*/
/*			Copyright	::  Phoenix Information Technology					*/
/*			Cpu			:: SH3												*/
/*			Language	:: SHC												*/
/*			File Name	:: sio.c											*/
/*																			*/
/****************************************************************************/
#include "sh7709a.h"
#include "def.h"
#include "ext.h"
#include "sci.h"

#define		CommSend		0
#define		CommRec			1
#define		CommSdRcMax		2

#define		CommBufferSize	0x0080

#define		cmWait			0
#define		cmStart			1
#define		cmRunning		2
#define		cmEnd			3

#define		cmRecEnpty		0x0100


#if (AP_SH3_0A == 1)
	#if (Sci9600Bps)
	#define		Brate	64			/* 20MHz * 1000000 / (64 / 2 * 9600bps) - 1*/
	#elif (Sci38400Bps)
	#define		Brate	15			/* 20MHz * 1000000 / (64 / 2 * 38400bps) - 1*/
	#endif
#elif (AP_SH3_1A == 1)
	#if (Sci9600Bps)
	#define		Brate	103			/* 32MHz * 1000000 / (64 / 2 * 9600bps) - 1*/
	#elif (Sci38400Bps)
	#define		Brate	25			/* 32MHz * 1000000 / (64 / 2 * 38400bps) - 1*/
	#endif
#elif (AP_SH3D_0A == 1)
	#if (Sci9600Bps)
	#define		Brate	103			/* 32MHz * 1000000 / (64 / 2 * 9600bps) - 1*/
	#elif (Sci38400Bps)
	#define		Brate	25			/* 32MHz * 1000000 / (64 / 2 * 38400bps) - 1*/
	#endif
#elif (AP_SH3_2A == 1)
	#if (Sci9600Bps)
	#define		Brate	103			/* 32MHz * 1000000 / (64 / 2 * 9600bps) - 1*/
	#elif (Sci38400Bps)
	#define		Brate	25			/* 32MHz * 1000000 / (64 / 2 * 38400bps) - 1*/
	#endif
#elif (AP_SH3D_1A == 1)
	#if (Sci9600Bps)
	#define		Brate	103			/* 32MHz * 1000000 / (64 / 2 * 9600bps) - 1*/
	#elif (Sci38400Bps)
	#define		Brate	25			/* 32MHz * 1000000 / (64 / 2 * 38400bps) - 1*/
	#endif
#endif

/*	Macro	*/
#define	cmWrPointer(ch,s)	cmData[ch][s].wr_pointer
#define	cmRdPointer(ch,s)	cmData[ch][s].rd_pointer
#define	cmBuffer(ch,s,p)	cmData[ch][s].buffer[p]
#define	cmStates(ch,s)		cmData[ch][s].states

#define	cmBufferSet(ch,s)	cmBuffer(ch,s,(cmWrPointer(ch,s)))
#define	cmBufferGet(ch,s)	cmBuffer(ch,s,(cmRdPointer(ch,s)))

/*	Variable	*/
struct stComm
{
	short wr_pointer;
	short rd_pointer;
	unsigned char buffer[CommBufferSize+30];
	short states;
};

struct stComm cmData[CommChanelMax][CommSdRcMax];

/*	Function	*/

static void scif_init();				/* SCIF Init */
void bri2();
void eri2();
void rxi2();
void txi2();


/* Comm Process Init 	*/
const unsigned char start_mes[] = "KD Flash Write..";

void sci_init()
{
	short i;

	scif_init();

	for(i=0;i<CommChanelMax;i++)
	{
		cmWrPointer(i,CommSend) = 0;
		cmWrPointer(i,CommRec) = 0;
		cmRdPointer(i,CommSend) = 0;
		cmRdPointer(i,CommRec) = 0;
		cmStates(i,CommSend) = cmWait;
		cmStates(i,CommRec) = cmWait;
	}
	
	for (i=0;i<sizeof(start_mes);i++)
	{
		set_send_data(CommSCIF,start_mes[i]);
	}
}

/*	Tx Buffer Write	*/
void set_send_data(short ch,unsigned char data)
{
	cmBufferSet(ch,CommSend) = data;
	cmWrPointer(ch,CommSend) = IncPointer(cmWrPointer(ch,CommSend),CommBufferSize);
}

/*	RX Buffer Read	*/
unsigned short get_proc(short ch)
{
	unsigned short ans;

	SCIF.SCSCR.BYTE &= ~0x40;		/*RIE = 0*/
	
	if (cmWrPointer(ch,CommRec) != cmRdPointer(ch,CommRec))
	{
		ans = (unsigned short)cmBufferGet(ch,CommRec) & 0x00ff;
		cmRdPointer(ch,CommRec)
			 = IncPointer(cmRdPointer(ch,CommRec),CommBufferSize);
	}
	else
	{
		ans = cmRecEnpty;
	}
	
	SCIF.SCSCR.BYTE |= 0x40;			/*RIE = 1*/
	
	return ans;
}

/*	Tx Process	*/
void send_proc(short ch)
{
	if (SCIF.SCSSR.WORD & 0x0020)		/*TDFE == 1*/
	{
		if (cmWrPointer(CommSCIF,CommSend)!= cmRdPointer(CommSCIF,CommSend))
		{
			SCIF.SCFTDR = cmBufferGet(CommSCIF,CommSend);
			cmRdPointer(CommSCIF,CommSend)
				 = IncPointer(cmRdPointer(CommSCIF,CommSend),CommBufferSize);
			SCIF.SCSCR.BYTE |= 0x80;	/*TIE = 1*/
			SCIF.SCSSR.WORD &= ~0x0020;	/*TDFE = 0*/
		}
	}
}

/*	RX Process	*/
void rec_proc(short ch)
{
	unsigned short tmp;

	tmp = get_proc(ch);
	
	if (tmp != cmRecEnpty)
	{
		comm_proc((unsigned char)(tmp & 0x00ff));
	}
}

/*	SCIF Channel Init	*/
static void scif_init()					/* SCIF Init */
{
	unsigned short dummy;
	unsigned char a;

										/* Int Level */
	INT.IPRE.WORD = (INT.IPRE.WORD & ~0x00f0) | 0x0070;
	SCIF.SCSMR.BYTE = 0x00;				
										/*8bit  Data */
										/* Non Parity */
										/* 1 Stop Bit */
										
	a = (unsigned char)Brate;
	SCIF.SCBRR = a;						/* Bit Rate */
	SCIF.SCSCR.BYTE = 0x70;				/* RX Int Enable */
										/* TX Enable */
										/* RX Enable */
	dummy = SCIF.SCSSR.WORD;			/* Dummy Read */
	SCIF.SCSSR.WORD = 0x0060;			
	SCIF.SCFCR.BYTE = 0x30;				/*  RX Trigger =1, TX Trigger =1	*/
}

/*	SCIF Break Int Routine 	*/
void bri2()
{
	unsigned short dummy;
	
	dummy = SCIF.SCSSR.WORD;
	SCIF.SCSSR.WORD &= ~0x0010;			/*BRK = 0*/
}

/*	SCIF RX Error Int Routine 	*/
void eri2()
{
	unsigned short dummy;
	
	dummy = SCIF.SCSSR.WORD;
	SCIF.SCSSR.WORD &= ~0x0080;			/*ER = 0*/
}

/*	SCIF RX Data Full Int Routine 	*/
void rxi2()						
{
	unsigned short dummy;
	unsigned char a;

	dummy = SCIF.SCSSR.WORD;
	
	cmBufferSet(CommSCIF,CommRec) = SCIF.SCFRDR;
	a = cmBufferSet(CommSCIF,CommRec);
	cmWrPointer(CommSCIF,CommRec)
		 = IncPointer(cmWrPointer(CommSCIF,CommRec),CommBufferSize);

	SCIF.SCSSR.WORD &= ~0x0001;			/*DR = 0*/
	SCIF.SCSSR.WORD &= ~0x0002;			/*RDF = 0*/
}

/*	SCIF TX Data Empty Routine 	*/
void txi2()							
{
	unsigned short dummy;

	dummy = SCIF.SCSSR.WORD;
	if (SCIF.SCSSR.WORD & 0x0020)		/*TDFE == 1*/
	{
		if (cmWrPointer(CommSCIF,CommSend) != cmRdPointer(CommSCIF,CommSend))
		{
			SCIF.SCFTDR = cmBufferGet(CommSCIF,CommSend);
			cmRdPointer(CommSCIF,CommSend)
				 = IncPointer(cmRdPointer(CommSCIF,CommSend),CommBufferSize);
		}
		else
		{
			SCIF.SCSCR.BYTE &= ~0x80;	/*TIE = 0*/
		}
	}
	SCIF.SCSSR.WORD &= ~0x0020;			/*TDFE = 0*/
	SCIF.SCSSR.WORD &= ~0x0040;			/*TEND = 0*/
}
