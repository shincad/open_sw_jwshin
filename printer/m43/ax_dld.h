	.LIST	OFF
;********************************************************
;							*
;	M4324 AX DOWNLOAD & GAIJI BUFFER ID DEFINITION	*
;							*
;	FILE NAME	AX_DLD.H			*
;	CREATED 	23/OCT/1990			*
;							*
;********************************************************
;
;	<< DOWNLOAD & GAIJI BUFFER ID DEFINE >>
;
YDLID0: .EQU	  0		; DOWNLOAD ID 0 OFFSET
YDLID1: .EQU	  1		; DOWNLOAD ID 1 OFFSET
;
;	<< ID 0 [ DLDID ] >>
;
QDLQMD: .EQU	  0		; DOWNLOAD LQ	  MODE
QDSCRT: .EQU	  1		;	   SCRIPT MODE
;	.EQU	2->6		; << Free bit >>
QNDDWL: .EQU	  7		; NOT DEFINE DOWNLOAD
	;
XDLQMD: .EQU	H'01            ;
XDSCRT: .EQU	H'02            ;
;	.EQU	H'04            ;
;	.EQU	H'08            ;
;	.EQU	H'10            ;
;	.EQU	H'20            ;
;	.EQU	H'40            ;
XNDDWL: .EQU	H'80            ;
;
;	<< ID 1 [ DLDID+1 ] >>
;
QROMCP: .EQU	  0		; ROM COPY
QSYMBL: .EQU	  1		; SYMBOL COPY
QENTDL: .EQU	  2		; ENTRY DOWNLOAD
QDSLON: .EQU	  3		; DLSEL=ON -> bit2=ON
QENT5F: .EQU	  4		; ENTRY DEFINE H'5F
QENT20: .EQU	  5		; ENTRY DEFINE H'20
QENT7F: .EQU	  6		; ENTRY DEFINE H'7F
;	.EQU	  7		; << Free bit >>
	;
XROMCP: .EQU	H'01            ;
XSYMBL: .EQU	H'02            ;
XENTDL: .EQU	H'04            ;
XDSLON: .EQU	H'08            ;
XENT5F: .EQU	H'10            ;
XENT20: .EQU	H'20            ;
XENT7F: .EQU	H'40            ;
;	.EQU	H'80            ;
;
;	<< DOWNLOAD CONSTANT >>
;
ZDLFSZ: .EQU	  4		; DOWNLOAD FLAG    SIZE
ZDLCSZ: .EQU	 42		;	   COLUMN  SIZE
ZDLBLK: .EQU	ZDLCSZ*3+ZDLFSZ ;	   1 BLOCK SIZE
;
;	<< GAIJI CONSTANT >>
;
ZGJCD:	.EQU	 H'7E           ; 911207 사용자 정의문자
ZGJBLK: .EQU	 24*3		; GAIJI 1 BLOCK SIZE
	.LIST	ON
