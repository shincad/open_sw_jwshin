/****************************************************************************/
/*																			*/
/*			Comm Process Header												*/
/*																			*/
/*			Copyright	:: Phoenix Information Technology					*/
/*			Cpu			:: SH3												*/
/*			Language	:: SHC												*/
/*			File Name	:: comm.h											*/
/*																			*/
/****************************************************************************/

#ifndef __COMM_H__
#define __COMM_H__

extern void comm_init();
extern void comm_proc(unsigned char data);
extern unsigned short str_comp(unsigned char * str1,unsigned char * str2);

#endif
