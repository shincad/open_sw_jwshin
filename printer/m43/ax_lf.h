	.LIST	OFF
;********************************************************
;							*
;	M4324 APPLICATION LF CONSTANT DEFINITION	*
;							*
;	FILE NAME	AX_LF.H 			*
;	CREATED 	04/JUL/1991			*
;							*
;********************************************************
;
ZFINCH: .EQU	      360		; 1 INCH FEED COUNT
ZRLF:	.EQU	   ZFINCH/3		; REVERSE LF MAX COUNT
ZRLF1:	.EQU	       96		; REVERSE LF MAX COUNT FOR BOTTOM
Z6LPI:	.EQU	   ZFINCH/6		; 1/6	INCH FEED COUNT
Z8LPI:	.EQU	   ZFINCH/8		; 1/8	INCH FEED COUNT
ZF60:	.EQU	   ZFINCH/60		; 1/60	INCH FEED COUNT
ZF120:	.EQU	   ZFINCH/120		; 1/120 INCH FEED COUNT 921110 IN
ZF180:	.EQU	   ZFINCH/180		; 1/180 INCH FEED COUNT
ZF4P:	.EQU	 4*ZFINCH/180		;  4 PIN FEED COUNT
ZF20P:	.EQU	20*ZFINCH/180		; 20 PIN FEED COUNT
ZF22P:	.EQU	22*ZFINCH/180		; 22 PIN FEED COUNT	-> 920108
ZF24P:	.EQU	24*ZFINCH/180		; 24 PIN FEED COUNT
ZF26P:	.EQU	26*ZFINCH/180		; 26 PIN FEED COUNT	-> 920408
ZFF7IS: .EQU	 6*ZFINCH		; 7 INCH FEED VALUE FOR FORMS (SF-261)
ZFF7IA: .EQU	 6*ZFINCH		; 7 INCH FEED VALUE FOR FORMS
	.LIST	ON
