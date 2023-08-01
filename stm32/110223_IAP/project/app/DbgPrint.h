#ifndef	_DBG_PRT
#define	_DBG_PRT

#include "stm32f10x_type.h"

extern void PrtChar	(u8		in);
extern void PrtShort(u16	in);
extern void PrtInt	(u32	in);
extern void PrtMsg	(u8	*in);
extern void PrtSpace	(void);
extern void PrtLF	(void);

#endif

