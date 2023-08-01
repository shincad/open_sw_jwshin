	.LIST	OFF
;********************************************************
;							*
;	M4324 USER ID DEFINITION			*
;							*
;	FILE NAME	USERID.H			*
;	CREATED		 2/DEC/1990			*
;							*
;********************************************************
;
;	ROM SIZE
;
;	.EQU	    0		; NO ROM CHECK
ROM512:	.EQU	    1+128	; 512K ROM  (SHADOW USE)
ROM1M:	.EQU	    2		;   1M ROM
ROM1MS:	.EQU	    2+128	;   1M ROM  (SHADOW USE)
ROM2M:	.EQU	    4		;   2M ROM
ROM2MS:	.EQU	    4+128	;   2M ROM  (SHADOW USE)
ROM4M:	.EQU	    8		;   4M ROM
;
;	USER ID
;
AX_ID:	.EQU	    1		; AX
NCRID:	.EQU	    2		; NCR
SE_ID:	.EQU	    3		; SEIKO
ICSID:	.EQU	    4		; ICS
CJKID:	.EQU	    5		; CJK
HA_ID:	.EQU	    6		; HA
	.LIST	ON
