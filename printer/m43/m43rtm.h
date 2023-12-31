	.LIST	OFF
;********************************************************
;							*
;	H8/520 (MODE 3,4) REAL TIME MONITOR FOR M4324	*
;							*
;	FILE NAME	M43RTM.H			*
;	CREATED		 7/NOV/1990			*
;							*
;********************************************************
;
;	TASK STATUS
;
XTWSLP:	.EQU	H'0001		; 1:SLEEP WAIT STATUS
XTWTMR:	.EQU	H'0002		; 1:TIMER WAIT STATUS
XTWFLG:	.EQU	H'0004		; 1:EVENT FLAG WAIT STATUS
XTWPKR:	.EQU	H'0020		; 1:PACKET RECEIVE WAIT STATUS
XTWPKS:	.EQU	H'0040		; 1:PACKET SEND WAIT STATUS
XTRDY:	.EQU	H'1000		; 1:READY STATUS
XTSUS:	.EQU	H'2000		; 1:SUSPEND STATUS
XTDMT:	.EQU	H'4000		; 1:DORMANT STATUS
XTCYC:	.EQU	H'8000		; 1:CYCLIC WAKE UP MODE
	;
QTWSLP:	.EQU	  0		; 1:SLEEP WAIT STATUS
QTWTMR:	.EQU	  1		; 1:TIMER WAIT STATUS
QTWFLG:	.EQU	  2		; 1:EVENT FLAG WAIT STATUS
QTWPKR:	.EQU	  5		; 1:PACKET RECEIVE WAIT STATUS
QTWPKS:	.EQU	  6		; 1:PACKET SEND WAIT STATUS
QTRDY:	.EQU	 12		; 1:READY STATUS
QTSUS:	.EQU	 13		; 1:SUSPEND STATUS
QTDMT:	.EQU	 14		; 1:DORMANT STATUS
QTCYC:	.EQU	 15		; 1:CYCLIC WAKE UP MODE
;
;	TASK INITIAL STATUS
;
ZTIST1:	.EQU	H'40		; CREAT, WITHOUT TRB
ZTIST2:	.EQU	H'48		; CREAT, WITH TRB
ZTIST3:	.EQU	H'10		; CREAT AND START, WITHOUT TRB
ZTIST4:	.EQU	H'18		; CREAT AND START, WITH TRB
;
;	EVENT FLAG WAIT MODE
;
XTFCL0:	.EQU	H'01		;  00:NOT CLEAR  01:EVENT FLAG ALL CLEAR
XTFCL1:	.EQU	H'02		;  10:NOT CLEAR  11:EVENT FLAG PARTIAL CLEAR
XTFOR:	.EQU	H'04		;   1:EVENT FLAG OR WAIT
	;
QTFCL0:	.EQU	  0		;  00:NOT CLEAR  01:EVENT FLAG ALL CLEAR
QTFCL1:	.EQU	  1		;  10:NOT CLEAR  11:EVENT FLAG PARTIAL CLEAR
QTFOR:	.EQU	  2		;   1:EVENT FLAG OR WAIT
;
;	SYSTEM CALL ANSWER CODE
;
ZE_OK:	.EQU	  0		; OPERATION COMPLETE
ZE_WUP:	.EQU	  1		; WAKE UP BEFORE TIME OUT
ZE_CAL:	.EQU	  2		; WAKE UP BY CALL TASK
ZE_TST:	.EQU	 16		; TASK STATUS ERROR
ZE_NOT:	.EQU	 32		; NO CURRENT TASK
ZE_NOP:	.EQU	 35		; NO PACKET DATA IN PACKET
ZE_TBL:	.EQU	128		; INVALID DEFINITION TABLE
ZE_PRI:	.EQU	129		; INVALID TASK PRIORITY
ZE_TIM:	.EQU	131		; INVALID TIMER COUNT
ZE_OWN:	.EQU	132		; NOT OWNER TASK
ZE_SYS:	.EQU	144		; UNDEFINED SYSTEM CALL
ZE_ISR:	.EQU	145		; CAN'T CALL FROM ISR
;
;	SYSTEM CALL NO.
;
STATSK:	.EQU	  0		; START TASK
ENDTSK:	.EQU	  1		; END TASK
TERTSK:	.EQU	  2		; TERMINATE TASK
SUSTSK:	.EQU	  3		; SUSPEND TASK
RSMTSK:	.EQU	  4		; RESUME TASK
SLPTSK:	.EQU	  5		; SLEEP TASK
WAITSK:	.EQU	  6		; TIMER WAIT TASK
WUPTSK:	.EQU	  7		; WAKE UP TASK
CYCWUP:	.EQU	  8		; CYCLIC WAKE UP TASK
CANCYC:	.EQU	  9		; CANCEL CYCLIC WAKE UP TASK
ROTTSK:	.EQU	 10		; ROTATE TASK
PRCTSK:	.EQU	 11		; CHANGE TASK PRIORITY
GETTSK:	.EQU	 12		; GET CURRENT TCB POINTER
CHKTSK:	.EQU	 13		; CHECK TASK STATUS
SETFLG:	.EQU	 14		; SET EVENT FLAG
ANDFLG:	.EQU	 15		; AND EVENT FLAG
ORFLG:	.EQU	 16		; OR  EVENT FLAG
WAIFLG:	.EQU	 17		; WAIT ON EVENT FLAG
CHKFLG:	.EQU	 18		; CHECK EVENT FLAG STATUS
SNDPKT:	.EQU	 29		; SEND PACKET DATA
SDCPKT:	.EQU	 30		; SEND PACKET DATA WITH CHECK
RCVPKT:	.EQU	 31		; RECEIVE PACKET DATA
POLPKT:	.EQU	 32		; POLL PACKET DATA
LOKPKT:	.EQU	 33		; LOOK PACKET DATA
LKNPKT:	.EQU	 34		; LOOK NEXT PACKET DATA
WAIPKT:	.EQU	 35		; WAIT PACKET
CHKPKT:	.EQU	 36		; CHECK PACKET STATUS
GETVER:	.EQU	 44		; GET VERSION NO.
;
;	SYSTEM CALL MACRO
;
	.MACRO	INIRTM
	TRAPA	#0
	.ENDM
;
	.MACRO	STATSK
	MOV:E	#STATSK,R0
	TRAPA	#1
	.ENDM
;
	.MACRO	ENDTSK
	MOV:E	#ENDTSK,R0
	TRAPA	#1
	.ENDM
;
	.MACRO	TERTSK
	MOV:E	#TERTSK,R0
	TRAPA	#1
	.ENDM
;
	.MACRO	SUSTSK
	MOV:E	#SUSTSK,R0
	TRAPA	#1
	.ENDM
;
	.MACRO	RSMTSK
	MOV:E	#RSMTSK,R0
	TRAPA	#1
	.ENDM
;
	.MACRO	SLPTSK
	MOV:E	#SLPTSK,R0
	TRAPA	#1
	.ENDM
;
	.MACRO	WAITSK
	MOV:E	#WAITSK,R0
	TRAPA	#1
	.ENDM
;
	.MACRO	WUPTSK
	MOV:E	#WUPTSK,R0
	TRAPA	#1
	.ENDM
;
	.MACRO	CYCWUP
	MOV:E	#CYCWUP,R0
	TRAPA	#1
	.ENDM
;
	.MACRO	CANCYC
	MOV:E	#CANCYC,R0
	TRAPA	#1
	.ENDM
;
	.MACRO	ROTTSK
	MOV:E	#ROTTSK,R0
	TRAPA	#1
	.ENDM
;
	.MACRO	PRCTSK
	MOV:E	#PRCTSK,R0
	TRAPA	#1
	.ENDM
;
	.MACRO	GETTSK
	MOV:E	#GETTSK,R0
	TRAPA	#1
	.ENDM
;
	.MACRO	CHKTSK
	MOV:E	#CHKTSK,R0
	TRAPA	#1
	.ENDM
;
	.MACRO	CALTSK
	TRAPA	#2
	.ENDM
;
	.MACRO	RETTSK
	TRAPA	#3
	.ENDM
;
	.MACRO	RETWUP
	TRAPA	#4
	.ENDM
;
	.MACRO	RETORF
	TRAPA	#5
	.ENDM
;
	.MACRO	RETINT
	TRAPA	#6
	.ENDM
;
	.MACRO	SETFLG
	MOV:E	#SETFLG,R0
	TRAPA	#1
	.ENDM
;
	.MACRO	ANDFLG
	MOV:E	#ANDFLG,R0
	TRAPA	#1
	.ENDM
;
	.MACRO	ORFLG
	MOV:E	#ORFLG,R0
	TRAPA	#1
	.ENDM
;
	.MACRO	WAIFLG
	MOV:E	#WAIFLG,R0
	TRAPA	#1
	.ENDM
;
	.MACRO	CHKFLG
	MOV:E	#CHKFLG,R0
	TRAPA	#1
	.ENDM
;
	.MACRO	SNDPKT
	MOV:E	#SNDPKT,R0
	TRAPA	#1
	.ENDM
;
	.MACRO	SDCPKT
	MOV:E	#SDCPKT,R0
	TRAPA	#1
	.ENDM
;
	.MACRO	RCVPKT
	MOV:E	#RCVPKT,R0
	TRAPA	#1
	.ENDM
;
	.MACRO	POLPKT
	MOV:E	#POLPKT,R0
	TRAPA	#1
	.ENDM
;
	.MACRO	LOKPKT
	MOV:E	#LOKPKT,R0
	TRAPA	#1
	.ENDM
;
	.MACRO	LKNPKT
	MOV:E	#LKNPKT,R0
	TRAPA	#1
	.ENDM
;
	.MACRO	WAIPKT
	MOV:E	#WAIPKT,R0
	TRAPA	#1
	.ENDM
;
	.MACRO	CHKPKT
	MOV:E	#CHKPKT,R0
	TRAPA	#1
	.ENDM
;
	.MACRO	GETVER
	MOV:E	#GETVER,R0
	TRAPA	#1
	.ENDM
;
	.MACRO	TSTTSK	S,T
	BTST.W	\S,\T+4
	.ENDM
;
	.MACRO	RETR2	T
	MOV.W	\T+12,FP
	MOV:F.W	R2,@(4:8,FP)
	.ENDM
;
	.MACRO	CLRFLG	T
	CLR.W	\T+10
	.ENDM
;
	.MACRO	TSTPKT P
	TST.B	\P+6
	.ENDM
	.LIST	ON
