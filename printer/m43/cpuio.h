	.LIST	OFF
	.SECTION	CPUIO,DUMMY,LOCATE=H'FF80
;********************************************************
;							*
;	H8/520 CPU (MODE 3,4) I/O REGISTER DEFINITION	*
;							*
;	FILE NAME	CPUIO.H 			*
;	CREATED 	11/JAN/1991			*
;							*
;********************************************************
;
;	I/O PORT
;
	.RES.B	  8		;
P5DDR:	.RES.B	  1		; W   PORT 5 DATA DIRECTION REGISTER
	.RES.B	  1		;
P5DR:	.RES.B	  1		;R/W  PORT 5 DATA REGISTER
XEECS:	.EQU	H'01            ;R/W    0:EEPROM SELECT, RESET
XDINT:	.EQU	H'02            ; R     1->0:I/F DATA INPUT
XOLDPB: .EQU	H'04            ; R \\       RESERVED INTERRUPT
XMPDN:	.EQU	H'08            ;R/W    0:POWER DOWN
XEECK:	.EQU	H'10            ;R/W      EEPROM CLOCK
XEEDI:	.EQU	H'20            ;R/W      CPU -> EEPROM DATA
XEEDO:	.EQU	H'40            ; R       EEPROM -> CPU DATA
XPHI:	.EQU	H'80            ; W       PHI CLOCK OUTPUT
QEECS:	.EQU	  0		;
QDINT:	.EQU	  1		;
QOLDPB: .EQU	  2		;\\ 920320
QMPDN:	.EQU	  3		;
QEECK:	.EQU	  4		;
QEEDI:	.EQU	  5		;
QEEDO:	.EQU	  6		;

	.RES.B	  1		;
P7DDR:	.RES.B	  1		; W   PORT 7 DATA DIRECTION REGISTER
	.RES.B	  1		;
P7DR:	.RES.B	  1		;R/W  PORT 7 DATA REGISTER
XMDVS:	.EQU	H'01            ;R/W    0:MOTOR DRIVE ENABLE
XBZON:	.EQU	H'02            ;R/W    0:BUZZER ON
XA19	.EQU	H'04            ;         A19
XTXD1:	.EQU	H'08            ;         SERIAL TRANSMIT DATA LINE
;	.EQU	H'10            ;         SERIAL RECEIVE DATA LINE
XSCK1:	.EQU	H'20            ;         SERIAL CLOCK OUTPUT
XPHIOE: .EQU	H'40            ;       0:P57 I/O PORT  1:P57 phi OUTPUT
QMDVS:	.EQU	  0		;
QBZON:	.EQU	  1		;

	.RES.B	  1		;
;
;	16 BIT FREE RUNNING TIMER
;
TCR1:	.RES.B	  1		;R/W  TIMER 1 CONTROL REGISTER
XCKS0:	.EQU	H'01            ;       00:phi/4        01:phi/8
XCKS1:	.EQU	H'02            ;       10:phi/32       11:EXTERNAL CLOCK
XOEA:	.EQU	H'04            ;       1:OCRA OUTPUT ENABLE
XOEB:	.EQU	H'08            ;       1:OCRB OUTPUT ENABLE
XFOVIE: .EQU	H'10            ;       1:FOVI ENABLE
XOCIEA: .EQU	H'20            ;       1:OCIA ENABLE
XOCIEB: .EQU	H'40            ;       1:OCIB ENABLE
XICIE:	.EQU	H'80            ;       1:ICI  ENABLE
QOCIEA: .EQU	  5		;
QOCIAB: .EQU	  6		;
QICIE:	.EQU	  7		;

TCSR1:	.RES.B	  1		;R/W  TIMER 1 CONTROL/STATUS REGISTER
XCCLRA: .EQU	H'01            ;       0:FRC NOT CLEAR 1:CLEAR AT OCFA
XIEDG:	.EQU	H'02            ;       0:ICR H->L EDGE 1:L->H EDGE
XOLVLA: .EQU	H'04            ;       0:OCFA L OUTPUT 1:H OUTPUT
XOLVLB: .EQU	H'08            ;       0:OCFB L OUTPUT 1:H OUTPUT
XOVF:	.EQU	H'10            ;       1:FRC OVERFLOW
XOCFA:	.EQU	H'20            ;       1:FRC=OCRA
XOCFB:	.EQU	H'40            ;       1:FRC=OCRB
XICF:	.EQU	H'80            ;       1:FRC->ICR
QOCFA:	.EQU	  5		;
QOCFB:	.EQU	  6		;
QICF:	.EQU	  7		;

FRC1:	.RES.W	  1		;R/W  FREE RUNNING COUNTER 1
OCRA1:	.RES.W	  1		;R/W  OUTPUT COMPARE REGISTER A1
OCRB1:	.RES.W	  1		;R/W  OUTPUT COMPARE REGISTER B1
ICR1:	.RES.W	  1		; R   INPUT CAPTURE REGISTER 1
	.RES.B	  6		;
TCR2:	.RES.B	  1		;R/W  TIMER 2 CONTROL REGISTER
TCSR2:	.RES.B	  1		;R/W  TIMER 2 CONTROL/STATUS REGISTER
FRC2:	.RES.W	  1		;R/W  FREE RUNNING COUNTER 2
OCRA2:	.RES.W	  1		;R/W  OUTPUT COMPARE REGISTER A2
OCRB2:	.RES.W	  1		;R/W  OUTPUT COMPARE REGISTER B2
ICR2:	.RES.W	  1		; R   INPUT CAPTURE REGISTER 2
	.RES.B	 22		;
;
;	SERIAL COMMUNICATION INTERFACE 2
;
SMR2:	.RES.B	  1		;R/W  SERIAL MODE REGISTER
QHOTS:	.EQU	  3		;	0:COLD START	1:HOT START

BRR2:	.RES.B	  1		;R/W  BIT RATE REGISTER
SCR2:	.RES.B	  1		;R/W  SERIAL CONTROL REGISTER
TDR2:	.RES.B	  1		;R/W  TRANSMIT DATA REGISTER
SSR2:	.RES.B	  1		;R/W  SERIAL STATUS REGISTER
RDR2:	.RES.B	  1		; R   RECEIVE DATA REGISTER
	.RES.B	 10		;
;
;	8 BIT TIMER
;
TCR:	.RES.B	  1		;R/W  TIMER CONTROL REGISTER
;XCKS0: .EQU	H'01            ;       000:CLOCK STOP 001:phi/8  010:phi/64
;XCKS1: .EQU	H'02            ;       011:phi/1024   100:CLOCK STOP 101:0->1
XCKS2:	.EQU	H'04            ;       110:1->0 EDGE  111:0->1,1->0 EDGE
XCCLR0: .EQU	H'08            ;       00:NOT TCNT CLEAR  01:CLEAR AT CFMA
XCCLR1: .EQU	H'10            ;       10:CLEAR AT CFMB   11:CLEAR AT EXTERNAL
XOVIE:	.EQU	H'20            ;       1:OVFI ENABLE
XCMIEA: .EQU	H'40            ;       1:CMIA ENABLE
XCMIEB: .EQU	H'80            ;       1:CMIB ENABLE
QCMIEA: .EQU	  6		;

TCSR:	.RES.B	  1		;R/W  TIMER CONTROL/STATUS REGISTER
XOS0:	.EQU	H'01            ;       00:NOT OUTPUT   01:LOW OUTPUT
XOS1:	.EQU	H'02            ;       10:HIGH OUTPUT  11:TOGGLE OUTPUT
XOS2:	.EQU	H'04            ;       00:NOT OUTPUT   01:LOW OUTPUT
XOS3:	.EQU	H'08            ;       10:HIGH OUTPUT  11:TOGGLE OUTPUT
;	.EQU	H'10            ;
XTOVF:	.EQU	H'20            ;       1:TCNT OVERFLOW
XCFMA:	.EQU	H'40            ;       1:TCNT=TCORA
XCFMB:	.EQU	H'80            ;       1:TCNT=TCORB
QCFMA	.EQU	  6		;

TCORA:	.RES.B	  1		;R/W  OUTPUT COMPARE REGISTER A
TCORB:	.RES.B	  1		;R/W  OUTPUT COMPARE REGISTER B
TCNT:	.RES.B	  1		;R/W  TIMER COUNTER
	.RES.B	  3		;
;
;	SERIAL COMMUNICATION INTERFACE 1
;
SMR1:	.RES.B	  1		;R/W  SERIAL MODE REGISTER
;XCKS0: .EQU	H'01            ;       00:phi/4        01:phi/8
;XCKS1: .EQU	H'02            ;       10:phi/32       11:EXTERNAL CLOCK
;	.EQU	H'04            ;
XSTOP:	.EQU	H'08            ;       0:1 STOP BIT            1:2 STOP BIT
XPROE:	.EQU	H'10            ;       0:EVEN PARITY           1:ODD
XPREN:	.EQU	H'20            ;       0:PARITY DISABLE        1:ENABLE
XCHR:	.EQU	H'40            ;       0:8 BIT DATA            1:7 BIT DATA
XCA:	.EQU	H'80            ;       0:ASYNCHRONOUS MODE     1:CLOCK SYNC

BRR1:	.RES.B	  1		;R/W  BIT RATE REGISTER
SCR1:	.RES.B	  1		;R/W  SERIAL CONTROL REGISTER
XCKE0:	.EQU	H'01            ;       0:SCK DISABLE           1:SCK OUTPUT
XCKE1:	.EQU	H'02            ;       0:INTERNAL CLOCK        1:SCK INPUT
;	.EQU	H'04            ;
;	.EQU	H'08            ;
XRE:	.EQU	H'10            ;       1:RECEIVE ENABLE
XTE:	.EQU	H'20            ;       1:TRANSMIT ENABLE
XRIE:	.EQU	H'40            ;       1:RX INTERRUPT ENABLE
XTIE:	.EQU	H'80            ;       1:TX INETRRUPT ENABLE
QRE:	.EQU	  4		;
QTE:	.EQU	  5		;

TDR1:	.RES.B	  1		;R/W  TRANSMIT DATA REGISTER
SSR1:	.RES.B	  1		;R/W  SERIAL STATUS REGISTER
;	.EQU	H'01            ;
;	.EQU	H'02            ;
;	.EQU	H'04            ;
XPER:	.EQU	H'08            ;       1:PARITY ERROR
XFER:	.EQU	H'10            ;       1:FRAMING ERROR
XORER:	.EQU	H'20            ;       1:OVER RUN ERROR
XRDRF:	.EQU	H'40            ;       1:RECEIVE DATA FULL
XTDRE:	.EQU	H'80            ;       1:TRANSMIT DATA EMPTY
QTDRE:	.EQU	  7		;

RDR1:	.RES.B	  1		; R   RECEIVE DATA REGISTER
	.RES.B	  2		;
;
;	A/D CONVERTOR
;
	.RES.W	  1		; R   A/D DATA REGISTER A  (HEDALM)
	.RES.W	  1		; R   A/D DATA REGISTER B  (RBMSNS)
	.RES.W	  1		; R   A/D DATA REGISTER C  (FANSNS)
	.RES.W	  1		; R   A/D DATA REGISTER D  (THLALM)
	.RES.B	  1		;R/W  A/D CONTROL/STATUS REGISTER
	.RES.B	  1		;R/W  A/D CONTROL REGISTER
	.RES.B	  6		;
;
;	INTERRUPT PRIORITY REGSITER
;
IPRA:	.RES.B	  1		;R/W  INTERRUPT PRIORITY (IRQ0, IRQ1->7)
IPRB:	.RES.B	  1		;R/W  INTERRUPT PRIORITY (FRT1, FRT2)
IPRC:	.RES.B	  1		;R/W  INTERRUPT PRIORITY (TMR,	SCI1)
IPRD:	.RES.B	  1		;R/W  INTERRUPT PRIORITY (SCI2, A/D)
DTEA:	.RES.B	  1		;R/W  DATA TRANSFER ENABLE (IRQ0->3)
DTEB:	.RES.B	  1		;R/W  DATA TRANSFER ENABLE (FRT1, FRT2)
DTEC:	.RES.B	  1		;R/W  DATA TRANSFER ENABLE (TMR,  SCI1)
DTED:	.RES.B	  1		;R/W  DATA TRANSFER ENABLE (SCI2, A/D)
WCR:	.RES.B	  1		;R/W  WAIT CONTROL REGISTER
XWC0:	.EQU	H'01            ;       00:0 WAIT       01:1 WAIT
XWC1:	.EQU	H'02            ;       10:2 WAIT       11:3 WAIT
XWMS0:	.EQU	H'04            ;       00:PROG WAIT    01:NO WAIT
XWMS1:	.EQU	H'08            ;       10:             11:AUTO WAIT

RAMCR:	.RES.B	  1		;R/W  RAM CONTROL REGISTER
XRAME:	.EQU	H'80            ;       1:INTERNAL RAM ENABLE

MDCR:	.RES.B	  1		; R   MODE CONTROL REGISTER
SBYCR:	.RES.B	  1		;R/W  SOFTWARE STAND BY CONTROL REGSITER
NMICR:	.RES.B	  1		;R/W  NMI CONTROL REGISTER
IRQCR:	.RES.B	  1		;R/W  IRQ CONTROL REGISTER
XIRQ0E: .EQU	H'01            ;       1:IRQ0 ENABLE

	.RES.B	  1		;
RSTCSR	.RES.B	  1		;R/W  RESET CONTROL/STATUS REGISTER
	.LIST	ON
