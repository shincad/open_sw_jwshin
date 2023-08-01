/****************************************************************************/
/*																			*/
/*			Main Process 													*/
/*																			*/
/*			Copyright	:: Phoenix Information Technology 					*/
/*			Cpu			:: SH3												*/
/*			Language	:: SHC												*/
/*			File Name	:: main.c											*/
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
#include "sci.h"

/*	Function Proto Type Declaration 	*/
void ap_main();
static void buffer_clear();

										/* Write Program Command  */
#define	Wait	0						/* Wait */
#define	Erasu	1						/* Erase */
#define	Write	2						/* Write */
#define	Flash	3						/* Flash */

void ap_main()
{
	set_imask(15);						/* INT Mask  = 15*/
	
										/* Offset Setting 	*/
	_29fxxx_set_offset(StartAddressFlash);
	comm_init();
	
	ei();								/* Int Enable */
	set_imask(0);						/* INT Mask Release */
	
	buffer_clear();
	
	for(;;)
	{
		send_proc(0);
		rec_proc(0);
	}
}

/*	Buffer Clear 	*/
static void buffer_clear()
{
	unsigned long *add;
	unsigned long i;

	for(i=StartAddressRam ;i < EndAddressRam ;i+=4)
	{
		add = (unsigned long *)i;
		*add = 0xFFFFFFFF;
	}
}

