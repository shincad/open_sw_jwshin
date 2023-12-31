	.LIST	OFF
;********************************************************
;							*
;	M4324 DATA PROCESS 3 TASK DEFINITION		*
;							*
;	FILE NAME	AX_DP3.H			*
;	CREATED 	21/DEC/1990			*
;							*
;********************************************************
	.INCLUDE	"SYSDP3.H"
	.LIST	OFF
;
;	PACKET CODE FOR AX
;
ZPNOP:	.EQU	 0		; NOP
ZPOWN:	.EQU	 1		; OWN CODE CALL
ZPINI:	.EQU	 2		; INITIALIZE MODE EXIT
ZPON:	.EQU	 3		; ONLINE
ZPPE:	.EQU	 4		; PE
ZPOFF:	.EQU	 5		; OFFLINE
ZPCVC:	.EQU	 6		; COVER CLOSE
ZPIPR:	.EQU	 7		; INPUT PRIME
ZPMDC:	.EQU	 8		; PRINT MODE CHANGE
ZPPFC:	.EQU	 9		; PRINT FORMAT CHANGE
ZPFASW: .EQU	10		; TOP MARGIN FWD ADJUST FEED SW
ZPRASW: .EQU	11		; TOP MARGIN RVS ADJUST FEED SW
ZPF1SW: .EQU	12		; 1/180 INCH FWD FEED SW
ZPR1SW: .EQU	13		; 1/180 INCH RVS FEED SW
ZPLFSW: .EQU	14		; LF SW
ZPINSW: .EQU	15		; FF/INSERT SW
ZPEJSW: .EQU	16		; EJECT SW
ZPEJPE: .EQU	17		; EJECT AT PE
ZPCPSW: .EQU	18		; CUT POSITION FEED SW
ZP260M: .EQU	19		; PAPER MODE SET FOR SF-260
ZPPMSW: .EQU	20		; PAPER MODE SW
ZPHMSW: .EQU	21		; HEAD SHIFT MODE SW
ZPHSA1: .EQU	22		; HEAD SHIFT ADJUST SW (FACTORY ADJUST)
ZPHSA2: .EQU	23		; HEAD SHIFT ADJUST SW (HEAD EXCHANGE)
ZPHSA3: .EQU	24		; HEAD SHIFT ADJUST SW (PLATEN EXCHANGE)
ZPHSA4: .EQU	25		; HEAD SHIFT ADJUST SW (PUSH AND OPEN)
ZPEES:	.EQU	26		; STX + A  (EEPROM DATA SET)
ZPEEW:	.EQU	27		; STX + W  (EEPROM WRITE)
ZP8LP:	.EQU	28		; ESC + 0  (1/8   INCH LF PITCH SET)
ZP6LP:	.EQU	29		; ESC + 2  (1/6   INCH LF PITCH SET)
ZP3LP:	.EQU	30		; ESC + 3  (n/180 INCH LF PITCH SET)
ZPALP:	.EQU	31		; ESC + A  (n/60  INCH LF PITCH SET)
ZPPAGL: .EQU	32		; ESC + C  (n LINE PAGE LENGTH SET)
ZPPAGI: .EQU	33		; ESC + C  (n INCH PAGE LENGTH SET)
ZPSSKP: .EQU	34		; ESC + N  (n LINE SKIP PERFORATION SET)
ZPRSKP: .EQU	35		; ESC + O  (SKIP PERFORATION RESET)
ZPVTCL: .EQU	36		; ESC + b  (VT POSITION CLEAR)
ZPVTST: .EQU	37		; ESC + b  (VT POSITION SET AT nTH LINE)
ZPIPRN: .EQU	38		; ESC + @  (PRINTER RESET)
ZPACSF: .EQU	39		; ESC + EM (ACSF CONTROL)
ZPPTYP: .EQU	40		; ESC + |  (PAPER CONTROL)
ZPEJCD: .EQU	41		; FF	   (EJECT)
ZPFFCD: .EQU	42		; FF	   (FORM FEED)
ZPVTCD: .EQU	43		; VT	   (VERTICAL TAB)
ZPLFCD: .EQU	44		; LF	   (LINE FEED)
ZPFORJ: .EQU	45		; ESC + J  (FORWARD n/180 INCH FEED)
ZPREVJ: .EQU	46		; ESC + j  (REVERSE n/180 INCH FEED)
ZPPRF:	.EQU	47		; CR	   (FEED BYE PRINT)
ZPPRG:	.EQU	48		; CR	   (FEED BYE PRINT)
ZPPRT	.EQU	49		; CR	   (PRINT)
ZPPRS:	.EQU	50		; CR	   (PRINT START)
ZPPRE	.EQU	51		; CR	   (PRINT END)
;
	.LIST	ON
