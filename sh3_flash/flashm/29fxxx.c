/****************************************************************************/
/*																			*/
/*			Flash ROM(29f800/160/320) Process								*/
/*																			*/
/*			Copyright	:: Phoenix Information Technology					*/
/*			Cpu			:: SH3												*/
/*			Language	:: SHC												*/
/*			File Name	:: 29fxxx.c											*/
/*																			*/
/****************************************************************************/
#include "29fxxx.h"
#include "def.h"

/*	Flash Size	*/
#define __29F800B__		1
#define __29F160B__		2
#define __29F320B__		3

/*	Flash Rom Select (Alpha Project B/D Select)	*/
#if (AP_SH3_0A == 1)
#define __FlashType__	__29F800B__
#elif (AP_SH3_1A == 1)
#define __FlashType__	__29F800B__
#elif (AP_SH3D_0A == 1)
#define __FlashType__	__29F800B__
#elif (AP_SH3_2A == 1)
#define __FlashType__	__29F320B__
#elif (AP_SH3D_1A == 1)
#define __FlashType__	__29F320B__
#endif

/*	Flash Rom Sector	*/
#if (__FlashType__ == __29F800B__)
const unsigned long SectorAddress[] =
{
	0x00000000,
	0x00004000,
	0x00006000,
	0x00008000,
	0x00010000,
	0x00020000,
	0x00030000,
	0x00040000,
	0x00050000,
	0x00060000,
	0x00070000,
	0x00080000,
	0x00090000,
	0x000a0000,
	0x000b0000,
	0x000c0000,
	0x000d0000,
	0x000e0000,
	0x000f0000,
	0x00100000,
};
#elif (__FlashType__ == __29F160B__)
const unsigned long SectorAddress[] =
{
	0x00000000,
	0x00004000,
	0x00006000,
	0x00008000,
	0x00010000,
	0x00020000,
	0x00030000,
	0x00040000,
	0x00050000,
	0x00060000,
	0x00070000,
	0x00080000,
	0x00090000,
	0x000a0000,
	0x000b0000,
	0x000c0000,
	0x000d0000,
	0x000e0000,
	0x000f0000,
	0x00100000,
	0x00110000,
	0x00120000,
	0x00130000,
	0x00140000,
	0x00150000,
	0x00160000,
	0x00170000,
	0x00180000,
	0x00190000,
	0x001a0000,
	0x001b0000,
	0x001c0000,
	0x001d0000,
	0x001e0000,
	0x001f0000,
	0x00200000
};
#elif (__FlashType__ == __29F320B__)
const unsigned long SectorAddress[] =
{
	0x00000000,
	0x00002000,
	0x00004000,
	0x00006000,
	0x00008000,
	0x0000a000,
	0x0000c000,
	0x0000e000,
	0x00010000,
	0x00020000,
	0x00030000,
	0x00040000,
	0x00050000,
	0x00060000,
	0x00070000,
	0x00080000,
	0x00090000,
	0x000a0000,
	0x000b0000,
	0x000c0000,
	0x000d0000,
	0x000e0000,
	0x000f0000,
	0x00100000,
	0x00110000,
	0x00120000,
	0x00130000,
	0x00140000,
	0x00150000,
	0x00160000,
	0x00170000,
	0x00180000,
	0x00190000,
	0x001a0000,
	0x001b0000,
	0x001c0000,
	0x001d0000,
	0x001e0000,
	0x001f0000,
	0x00200000,
	0x00210000,
	0x00220000,
	0x00230000,
	0x00240000,
	0x00250000,
	0x00260000,
	0x00270000,
	0x00280000,
	0x00290000,
	0x002a0000,
	0x002b0000,
	0x002c0000,
	0x002d0000,
	0x002e0000,
	0x002f0000,
	0x00300000,
	0x00310000,
	0x00320000,
	0x00330000,
	0x00340000,
	0x00350000,
	0x00360000,
	0x00370000,
	0x00380000,
	0x00390000,
	0x003a0000,
	0x003b0000,
	0x003c0000,
	0x003d0000,
	0x003e0000,
	0x003f0000,
	0x00400000
};
#endif

/*	Macro	*/
#define SectorMax		((sizeof(SectorAddress) / sizeof(long)) - 1)

#define Sector2Addr(d)	\
(\
(unsigned short *)( (long)(offset_addr + SectorAddress[(d)]) )\
)

#define MemoryAccessShort(adr)	(*((unsigned short *)adr))

#define scAddress1st	(offset_addr + 0x0aaa)
#define scAddress2nd	(offset_addr + 0x0554)
#define scAddress3rd	scAddress1st

/*	Variable Declaration	*/
static unsigned long offset_addr;

/*	Variable ProtoType Declaration	*/
static unsigned short erase_check(unsigned long sector);
static void flash_reset_word();
static void flash_write_word(unsigned short * address,unsigned short data);
static void flash_erase_sector(unsigned short sector);
static unsigned short flash_pooling_word(
				unsigned short * address,unsigned short data);
static unsigned short erase_check(unsigned long sector);


/*	Flash Rom Address Offset  */
void _29fxxx_set_offset(unsigned long address)
{
	offset_addr = address;
}

/*	Reset Command	*/
static void flash_reset_word()
{
	MemoryAccessShort(scAddress1st) = 0xaa;
	MemoryAccessShort(scAddress2nd) = 0x55;
	MemoryAccessShort(scAddress3rd) = 0xf0;
}

/*	Write Command	*/
static void flash_write_word(unsigned short * address,unsigned short data)
{
	MemoryAccessShort(scAddress1st) = 0xaa;
	MemoryAccessShort(scAddress2nd) = 0x55;
	MemoryAccessShort(scAddress3rd) = 0xa0;
	*address = data;
}

/*	Sector Erase Command	*/
static void flash_erase_sector(unsigned short sector)
{
	short i;
	unsigned short * tmp;

	MemoryAccessShort(scAddress1st) = 0xaa;
	MemoryAccessShort(scAddress2nd) = 0x55;
	MemoryAccessShort(scAddress3rd) = 0x80;
	MemoryAccessShort(scAddress1st) = 0xaa;
	MemoryAccessShort(scAddress2nd) = 0x55;

	tmp = Sector2Addr(sector);
	*tmp = (unsigned short)0x30;
}

/*	All Erase Command */
void flash_erase_all(void)
{
	unsigned short i;
	unsigned short ans;

	MemoryAccessShort(scAddress1st) = 0xaa;
	MemoryAccessShort(scAddress2nd) = 0x55;
	MemoryAccessShort(scAddress3rd) = 0x80;
	MemoryAccessShort(scAddress1st) = 0xaa;
	MemoryAccessShort(scAddress2nd) = 0x55;
	MemoryAccessShort(scAddress3rd) = 0x10;

	ans = Pass;
	for (i=0;i<SectorMax;i++)
	{
		ans = erase_check(i);
	}
	
	flash_reset_word();
}

/*	Polling Command	*/
static unsigned short flash_pooling_word(
				unsigned short * address,unsigned short data)
{
	unsigned short tmp;
	unsigned short flag;
	unsigned short ans;

	flag = _29fTrue;
	address;

	while(flag == _29fTrue)
	{
		tmp = *address;
		if ((tmp & 0x0080) != (data & 0x0080))
		{
			if (tmp & 0x0020)
			{
				flag = _29fFalse;
				tmp = *address;
				if ((tmp & 0x0080) != (data & 0x0080))
				{
					ans = Fail;
				}
				else
				{
					ans = Pass;
				}
			}
		}
		else
		{
			flag = _29fFalse;
			ans = Pass;
		}
	}

	return ans;
}

/*	Write Function	*/
unsigned short flash_write_proc(unsigned short * s_addr,
				unsigned short * d_addr,unsigned long count)
{
	unsigned short ans;
	unsigned short flag;
	unsigned short tmp;
	unsigned short tmp2;

	flag = _29fTrue;
	
	if (count != 0)
	{
		count /= 2;
		
		while(flag == _29fTrue)
		{
			tmp = *s_addr;
		
			flash_write_word(d_addr,tmp);
			ans = flash_pooling_word(d_addr,tmp);
			if (ans == Fail)
			{
				flag = _29fFalse;
			}
			else
			{
				d_addr++;
				s_addr++;
				count--;
				if (count == 0)
				{
					flag = _29fFalse;
				}
			}
		}
	}
	
	return ans;
}

/*	Erase Check 	*/
static unsigned short erase_check(unsigned long sector)
{
	unsigned long i;
	unsigned short * data;
	unsigned short ans;

	data = Sector2Addr(sector);
	for (i=SectorAddress[sector];i<SectorAddress[sector+1];i+=2)
	{
		ans = flash_pooling_word(data,(unsigned short)0xffff);
		data++;
		if (ans == Fail)
		{
			i = SectorAddress[sector+1];
		}
	}
	flash_reset_word();
	return ans;
}

/*	Erase Function	*/
unsigned short flash_erase_proc(unsigned short sector)
{
	unsigned short ans;
	unsigned short flag;
	unsigned short tmp;
	unsigned short i;

	ans = Pass;
	
	if (sector < SectorMax)
	{
		flash_erase_sector(sector);
		ans = erase_check(sector);
		
		flash_reset_word();
	}
	else
	{
		ans = Error;
	}
	
	return ans;
}
