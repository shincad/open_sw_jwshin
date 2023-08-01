	.LIST	OFF
;********************************************************
;							*
;	M4324 SLAVE CPU I/F I/O SYSTEM DEFINITION	*
;							*
;	FILE NAME	SCIIOS.H			*
;	CREATED		 9/NOV/1990			*
;							*
;********************************************************
;
;	SCI I/O CALL ENTRY
;
	.IMPORT		SCICAL	; SCI SYSTEM CALL ENTRY
	.IMPORT		SCINMI	; RESET SLAVE CPU
	.IMPORT		SCIHSP	; SEND PHASE STATUS RESQUEST TO SLAVE CPU
	.IMPORT		SCISNS	; SEND SENSOR STATUS REQUEST TO SLAVE CPU
	.IMPORT		SCIADS	; SEND TOP SENSOR A/D REQUEST TO SLAVE CPU
	.IMPORT		SCIADW	; SEND TOP SENSOR A/D REQUEST TO SLAVE CPU
	.IMPORT		SCIVER	; SEND SLAVE CPU VERSION REQUEST TO SLAVE CPU
	.IMPORT		SCISTS	; SEND STATUS REQUEST TO SLAVE CPU
	.IMPORT		SCICAN	; SEND CANCEL COMMAND TO SLAVE CPU
	.IMPORT		SCISTP	; SEND FORMS ESCAPE STOP COMMAND TO SLAVE CPU
	.IMPORT		SCICLC	; SEND CANCEL CLEAR COMMAND TO SLAVE CPU
	.IMPORT		SCICLE	; SEND ERROR FLAG 1 CLEAR COMMAND TO SLAVE CPU
	.IMPORT		SCIADV	; SEND TOP SENSOR THRESHOLD TO SLAVE CPU
	.IMPORT		SCIPEC	; SEND PE CHECK COUNT TO SLAVE CPU
	.IMPORT		SCILFT	; SEND LF MOTOR SPEED TABLE TO SLAVE CPU
	.IMPORT		SCIPRA	; SEND PRINT POSITION ADJUST
	.IMPORT		SCIBDT	; SEND BYTE DATA TO SLAVE CPU
	.IMPORT		SCIDAT	; SEND DATA TO SLAVE CPU
	.IMPORT		SCICMD	; SEND COMMAND TO SLAVE CPU
	.IMPORT		SCIPRT	; SEND PRINT COMMAND TO SLAVE CPU
	.LIST	ON
