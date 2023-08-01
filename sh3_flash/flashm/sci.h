/****************************************************************************/
/*																			*/
/*			Serial define													*/
/*																			*/
/*			Copyright	:: Phoenix Information Technology					*/
/*			Cpu			:: SH3												*/
/*			Language	:: SHC												*/
/*			File Name	:: sci.h											*/
/*																			*/
/****************************************************************************/

#ifndef __SCI_H__
#define __SCI_H__

#define		CommSCIF		0
#define		CommChanelMax	1

extern void sci_init();
extern void set_send_data(short ch,unsigned char data);
extern unsigned short get_proc(short ch);
extern void send_proc(short ch);
extern void rec_proc(short ch);

#endif
