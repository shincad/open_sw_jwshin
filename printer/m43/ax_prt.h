	.LIST		OFF
;********************************************************
;							*
;	M4324 PRINT APPLICATION DEFINITION		*
;							*
;	FILE NAME	SYSPRT.H			*
;	CREATED		11/NOV/1990			*
;							*
;********************************************************
;
	.INCLUDE	"SYSPRT.H"
	.LIST		OFF
;
;	USER OPTION FLAG
;
;YPCF3:	.RES.B	  1		; PRINT USER OPTION FLAG
;	.EQU	0->2		;     PRINT TYPE NO.
;	.EQU	  3		;
;	.EQU	  4		;
;	.EQU	  5		;
;	.EQU	  6		;
QOFFP:	.EQU	  7		;   1:PRINT BY OFFLINE SW
ZPRTYP:	.EQU	H'07		;     PRINT TYPE MASK
ZNORP:	.EQU	  0		;     NORMAL PRINT
ZKVEP:	.EQU	  1		;     KANJI VERTICAL ENLARGED PRINT
ZXNP:	.EQU	  2		;     xN SIZE PRINT
ZBARP:	.EQU	  3		;     BAR CODE PRINT
ZOCRP:	.EQU	  4		;     OCR CODE PRINT
	.LIST	ON
