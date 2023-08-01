	.LIST	OFF
;********************************************************
;							*
;	M4324 EEPROM I/O SYSTEM DEFINITION		*
;							*
;	FILE NAME	EEPIOS.H			*
;	CREATED		24/OCT/1990			*
;							*
;********************************************************
;
;	EEPROM I/O CALL ENTRY
;
	.IMPORT		EEWRDI	; WRITE DISABLE
	.IMPORT		EEWREN	; WRITE ENABLE
	.IMPORT		EERDWD	; WORD READ
	.IMPORT		EERD	; WORD READ
	.IMPORT		EEWRWD	; WORD WRITE
	.IMPORT		EERDBF	; BUFFER READ FROM EEPROM
	.IMPORT		EEWRBF	; BUFFER WRITE TO EEPROM
	.LIST	ON
