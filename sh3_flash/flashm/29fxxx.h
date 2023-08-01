/****************************************************************************/
/*																			*/
/*			Flash Rom(29f800/160/320) Process Header						*/
/*																			*/
/*			Copyright	:: Phoenix Information Technology					*/
/*			Cpu			:: SH3												*/
/*			Language	:: SHC												*/
/*			File Name	:: 29fxxx.c											*/
/*																			*/
/****************************************************************************/

#ifndef	__29FXXX_H__
#define	__29FXXX_H__

#define	Pass		1					/* Success */
#define	Fail		0					/* Fail */
#define	Error		0xff				/* Setting Value Error */

#define	_29fTrue	1
#define	_29fFalse	0

extern void _29fxxx_set_offset(unsigned long address);
extern void flash_erase_all(void);
extern unsigned short flash_write_proc(unsigned short * s_addr,
				unsigned short * d_addr,unsigned long count);
extern unsigned short flash_erase_proc(unsigned short sector);

#endif
