	.LIST	OFF
;********************************************************
;							*
;	M4324 SLAVE CPU COMMAND CODE DEFINITION 	*
;							*
;	FILE NAME	SLVCMD.H			*
;	CREATED 	04/JUL/1991			*
;							*
;********************************************************
;
;	SLAVE CPU COMMAND CODE
;
;ZCPRL: .EQU	    1		; PRINT  (LOGICAL SEKKING)
;ZCPRF: .EUQ	    2		; PRINT  (FORWARD)
;ZCPRR: .EQU	    3		; PRINT  (REVERSE)
;ZCPRS: .EQU	    4		; PRINT  (SAME DIRECTION)

ZCCRM:	.EQU	    5		; CR MOVE
ZCRSPD: .EQU	    0		;   CR MOVE SPEED
ZCRHM:	.EQU	  160		;   CR HOME POSITION
ZCRCL:	.EQU	 1391		;   CR HAED COOLING POSITION

ZCCRI:	.EQU	    6		; CR INITIALIZE
ZFRMWX: .EQU	60000		;   FRAME WIDTH UPPER LIMIT
ZFRMWY: .EQU	59968		;   FRAME WIDTH LOWER LIMIT

ZCLFF:	.EQU	   11		; LF FORWARD
ZCLFR:	.EQU	   12		; LF REVERSE
ZCRESC: .EQU	  180		;   CR ESCAPE FOR PAPER HOTCHKISS

ZCINF:	.EQU	   13		; INSERT FORMS
ZCESF:	.EQU	   14		; ESCAPE FORMS
ZCEJB:	.EQU	   15		; EJECT BOTTOM
ZCEJS:	.EQU	   16		; EJECT SHEET
ZCIN2:	.EQU	   17		; INSERT SF-260
ZCINA:	.EQU	   18		; INSERT MULTI BIN ACSF
ZCLFPB: .EQU	   19		; LF FORWARD AND PAPER BAIL OPEN/CLOSE
ZCHSH:	.EQU	   20		; HEAD SHIFT MOTOR PHASE SET
ZCHSM:	.EQU	   21		; HEAD SHIFT MOVE
ZCHSP:	.EQU	   22		; HEAD SHIFT PUSH
ZCHSPC: .EQU	   23		; HEAD SHIFT POSITION CHECK
ZHSSP1: .EQU	   47  ;39	;\\ HEAD SHIFT SPEED FOR OPEN  (600pps) (500pps)
ZHSSP2: .EQU	   59		;   HEAD SHIFT SPEED FOR MOVE  (400pps)
ZHSSP3: .EQU	   59		;   HEAD SHIFT SPEED FOR PUSH  (400pps)
ZHSLKT: .EQU	   15*16+11	;   HEAD SHIFT LOCK TIME
ZHSDLY: .EQU	   96		;   HEAD SHIFT DELAY FOR DIRCTION CHANGE
ZHSMAX: .EQU	32767		; HEAD SHIFT POSITION MAX VALUE

ZCRSM:	.EQU	   24		; RIBBON SHIFT MOVE
;ZRSSP1: .EQU	    39		 ;   RIBBON SHIFT SPEED 1  (600pps)  \920608
ZRSSP1: .EQU	   47		;   RIBBON SHIFT SPEED 1  (500pps)   \920608
ZRSSP2: .EQU	   59		;   RIBBON SHIFT SPEED 2  (400pps)
ZRSP0:	.EQU	  168		;   RIBBON SHIFT MAX PULSE COUNT
ZRSP1:	.EQU	    5		;   RIBBON SHIFT HOME PULSE COUNT
ZRSHM:	.EQU	  192		;   RIBBON SHIFT HOME POSITION
ZRSESC: .EQU	  ZRSHM-147	;   RIBBON SHIFT ESCAPE POSITION
ZRSYL:	.EQU	  ZRSHM-105	;   RIBBON SHIFT YELLOW POSITION

ZCPBM:	.EQU	   26		; PAPER BAIL/LEVER MOVE
ZLVSPD: .EQU	   59		;   LEVER CHNAGE SPEED		 (400pps)
ZPBSPD: .EQU	   59		;   PAPER BAIL OPEN SPEED	 (400pps)
ZLPSPD: .EQU	   39		;   PAPER BAIL CLOSE SPEED AT LF (600pps)
ZLVLKT: .EQU	    2*16+2	;   LEVER CHANGE LOCK TIME
ZLPLKT: .EQU	    2*16+2	;   LEVER CHANGE PRELOCK TIME
ZPBLKT: .EQU	    2*16+2	;   PAPER BAIL LOCK TIME
ZPBP0:	.EQU	  115		;   PAPER BAIL MAX PULSE
ZPBP1:	.EQU	    4		;   PAPER BAIL HOME POSITION PULSE
ZPBCL:	.EQU	  164		;   PAPER BAIL CLOSE ADDRESS
ZPBHO:	.EQU	  ZPBCL-51	;   PAPER BAIL HALF OPEN ADDRESS
ZPBOP:	.EQU	  ZPBCL+56	;   PAPER BAIL OPEN ADDRESS
ZLVFM1: .EQU	  ZPBCL-99	;   LEVER FORMS SELECT ADDRESS
ZLVFM2: .EQU	  ZPBCL-77	;   LEVER FORMS SELECT ADDRESS
ZLVSH:	.EQU	  ZPBCL-51	;   LEVER SHEET SELECT ADDRESS

ZCPCK:	.EQU	   27		; PRCLK OUTPUT
ZPCKT:	.EQU	    2		;   PRCLK OUTPUT INTERVAL

ZCDTA:	.EQU	   29		; DATA TRANSFER A
ZCDTB:	.EQU	   30*ZH+H'0C   ; DATA TRANSFER B
ZCSTS:	.EQU	   31*ZH+H'0C   ; STATUS REQUEST
	.LIST	ON
