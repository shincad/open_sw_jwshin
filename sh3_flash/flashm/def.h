/****************************************************************************/
/*																			*/
/*			Global Define													*/
/*																			*/
/*			Copyright	:: Phoenix Information Technology					*/
/*			Cpu			:: SH3												*/
/*			Language	:: SHC												*/
/*			File Name	:: def.h											*/
/*																			*/
/****************************************************************************/

#ifndef __DEF_H__
#define __DEF_H__

/*	 Board Select */
#define AP_SH3_0A		0
#define AP_SH3_1A		1
#define AP_SH3D_0A		0
#define AP_SH3_2A		0
#define AP_SH3D_1A		0

/*	Compiler Select	*/
#define _GCC_			0
#define _HITACHI_		1

/*	Transfer Bit Rate	*/
#define Sci9600Bps		0
#define Sci38400Bps		1

/*Address, Size */
#if (AP_SH3_0A == 1)
#define StartAddressRam		0x0c000000	/*RAM Start */
#define EndAddressRam		0x0c0fffff	/*RAM End */
#define StartAddressFlash	0xB4000000	/* Flash Start*/
#elif (AP_SH3_1A == 1)
#define StartAddressRam		0x0c000000	/*RAM Start */
#define EndAddressRam		0x0c0fffff	/*RAM End */
#define StartAddressFlash	0xB4000000	/*Flash Start */
#elif (AP_SH3D_0A == 1)
#define StartAddressRam		0x0c000000	/*RAM Start */
#define EndAddressRam		0x0c0fffff	/*RAM End */
#define StartAddressFlash	0xB4000000	/*Flash Start */
#elif (AP_SH3_2A == 1)
#define StartAddressRam		0x0c000000	/*RAM Start */
#define EndAddressRam		0x0c3fffff	/*RAM End */
#define StartAddressFlash	0xB4000000	/*Flash Start */
#elif (AP_SH3D_1A == 1)
#define StartAddressRam		0x0c000000	/*RAM Start */
#define EndAddressRam		0x0c3fffff	/*RAM End */
#define StartAddressFlash	0xB4000000	/*Flash Start */
#endif

#define ON		1
#define OFF		0

/*	Macro */

/*pointer Increase,Decrease	(Max = 2^x)
P : Pointer
M : Pointer  Upper Limit
*/
#define IncPointer(P,M)		((P+1) & (M-1))
#define DecPointer(P,M)		((P-1) & (M-1))

/*Bit Operator Macro */
#define	Bset( VAR, BIT )	((VAR) |=  (BIT))
#define	Bclr( VAR, BIT )	((VAR) &= ~(BIT))
#define	Bexor( VAR, BIT )	((VAR) ^=  (BIT))
#define	Bxor( VAR, BIT )	((VAR) ^=  (BIT))
#define	Btest( VAR, BIT )	((VAR) &   (BIT))
#define	Btst( VAR, BIT )	((VAR) &   (BIT))
#define	Bcmp( VAR, BIT )	((BIT) == ((VAR) & (BIT)))

/*Odd, Even Value decision */
#define	Odd( VAR )			Btest( VAR, 0x01 )	/*Odd */
#define	Even( VAR )			!ODD( VAR )			/*Even*/

#endif
