
;CodeVisionAVR C Compiler V2.05.3 Standard
;(C) Copyright 1998-2011 Pavel Haiduc, HP InfoTech s.r.l.
;http://www.hpinfotech.com

;Chip type                : ATmega128
;Program type             : Application
;Clock frequency          : 16.000000 MHz
;Memory model             : Small
;Optimize for             : Size
;(s)printf features       : int, width
;(s)scanf features        : int, width
;External RAM size        : 0
;Data Stack size          : 1024 byte(s)
;Heap size                : 0 byte(s)
;Promote 'char' to 'int'  : Yes
;'char' is unsigned       : Yes
;8 bit enums              : Yes
;Global 'const' stored in FLASH     : No
;Enhanced function parameter passing: Yes
;Enhanced core instructions         : On
;Smart register allocation          : On
;Automatic register allocation      : On

	#pragma AVRPART ADMIN PART_NAME ATmega128
	#pragma AVRPART MEMORY PROG_FLASH 131072
	#pragma AVRPART MEMORY EEPROM 4096
	#pragma AVRPART MEMORY INT_SRAM SIZE 4351
	#pragma AVRPART MEMORY INT_SRAM START_ADDR 0x100

	#define CALL_SUPPORTED 1

	.LISTMAC
	.EQU UDRE=0x5
	.EQU RXC=0x7
	.EQU USR=0xB
	.EQU UDR=0xC
	.EQU SPSR=0xE
	.EQU SPDR=0xF
	.EQU EERE=0x0
	.EQU EEWE=0x1
	.EQU EEMWE=0x2
	.EQU EECR=0x1C
	.EQU EEDR=0x1D
	.EQU EEARL=0x1E
	.EQU EEARH=0x1F
	.EQU WDTCR=0x21
	.EQU MCUCR=0x35
	.EQU RAMPZ=0x3B
	.EQU SPL=0x3D
	.EQU SPH=0x3E
	.EQU SREG=0x3F
	.EQU XMCRA=0x6D
	.EQU XMCRB=0x6C

	.DEF R0X0=R0
	.DEF R0X1=R1
	.DEF R0X2=R2
	.DEF R0X3=R3
	.DEF R0X4=R4
	.DEF R0X5=R5
	.DEF R0X6=R6
	.DEF R0X7=R7
	.DEF R0X8=R8
	.DEF R0X9=R9
	.DEF R0XA=R10
	.DEF R0XB=R11
	.DEF R0XC=R12
	.DEF R0XD=R13
	.DEF R0XE=R14
	.DEF R0XF=R15
	.DEF R0X10=R16
	.DEF R0X11=R17
	.DEF R0X12=R18
	.DEF R0X13=R19
	.DEF R0X14=R20
	.DEF R0X15=R21
	.DEF R0X16=R22
	.DEF R0X17=R23
	.DEF R0X18=R24
	.DEF R0X19=R25
	.DEF R0X1A=R26
	.DEF R0X1B=R27
	.DEF R0X1C=R28
	.DEF R0X1D=R29
	.DEF R0X1E=R30
	.DEF R0X1F=R31

	.EQU __SRAM_START=0x0100
	.EQU __SRAM_END=0x10FF
	.EQU __DSTACK_SIZE=0x0400
	.EQU __HEAP_SIZE=0x0000
	.EQU __CLEAR_SRAM_SIZE=__SRAM_END-__SRAM_START+1

	.MACRO __CPD1N
	CPI  R30,LOW(@0)
	LDI  R26,HIGH(@0)
	CPC  R31,R26
	LDI  R26,BYTE3(@0)
	CPC  R22,R26
	LDI  R26,BYTE4(@0)
	CPC  R23,R26
	.ENDM

	.MACRO __CPD2N
	CPI  R26,LOW(@0)
	LDI  R30,HIGH(@0)
	CPC  R27,R30
	LDI  R30,BYTE3(@0)
	CPC  R24,R30
	LDI  R30,BYTE4(@0)
	CPC  R25,R30
	.ENDM

	.MACRO __CPWRR
	CP   R@0,R@2
	CPC  R@1,R@3
	.ENDM

	.MACRO __CPWRN
	CPI  R@0,LOW(@2)
	LDI  R30,HIGH(@2)
	CPC  R@1,R30
	.ENDM

	.MACRO __ADDB1MN
	SUBI R30,LOW(-@0-(@1))
	.ENDM

	.MACRO __ADDB2MN
	SUBI R26,LOW(-@0-(@1))
	.ENDM

	.MACRO __ADDW1MN
	SUBI R30,LOW(-@0-(@1))
	SBCI R31,HIGH(-@0-(@1))
	.ENDM

	.MACRO __ADDW2MN
	SUBI R26,LOW(-@0-(@1))
	SBCI R27,HIGH(-@0-(@1))
	.ENDM

	.MACRO __ADDW1FN
	SUBI R30,LOW(-2*@0-(@1))
	SBCI R31,HIGH(-2*@0-(@1))
	.ENDM

	.MACRO __ADDD1FN
	SUBI R30,LOW(-2*@0-(@1))
	SBCI R31,HIGH(-2*@0-(@1))
	SBCI R22,BYTE3(-2*@0-(@1))
	.ENDM

	.MACRO __ADDD1N
	SUBI R30,LOW(-@0)
	SBCI R31,HIGH(-@0)
	SBCI R22,BYTE3(-@0)
	SBCI R23,BYTE4(-@0)
	.ENDM

	.MACRO __ADDD2N
	SUBI R26,LOW(-@0)
	SBCI R27,HIGH(-@0)
	SBCI R24,BYTE3(-@0)
	SBCI R25,BYTE4(-@0)
	.ENDM

	.MACRO __SUBD1N
	SUBI R30,LOW(@0)
	SBCI R31,HIGH(@0)
	SBCI R22,BYTE3(@0)
	SBCI R23,BYTE4(@0)
	.ENDM

	.MACRO __SUBD2N
	SUBI R26,LOW(@0)
	SBCI R27,HIGH(@0)
	SBCI R24,BYTE3(@0)
	SBCI R25,BYTE4(@0)
	.ENDM

	.MACRO __ANDBMNN
	LDS  R30,@0+(@1)
	ANDI R30,LOW(@2)
	STS  @0+(@1),R30
	.ENDM

	.MACRO __ANDWMNN
	LDS  R30,@0+(@1)
	ANDI R30,LOW(@2)
	STS  @0+(@1),R30
	LDS  R30,@0+(@1)+1
	ANDI R30,HIGH(@2)
	STS  @0+(@1)+1,R30
	.ENDM

	.MACRO __ANDD1N
	ANDI R30,LOW(@0)
	ANDI R31,HIGH(@0)
	ANDI R22,BYTE3(@0)
	ANDI R23,BYTE4(@0)
	.ENDM

	.MACRO __ANDD2N
	ANDI R26,LOW(@0)
	ANDI R27,HIGH(@0)
	ANDI R24,BYTE3(@0)
	ANDI R25,BYTE4(@0)
	.ENDM

	.MACRO __ORBMNN
	LDS  R30,@0+(@1)
	ORI  R30,LOW(@2)
	STS  @0+(@1),R30
	.ENDM

	.MACRO __ORWMNN
	LDS  R30,@0+(@1)
	ORI  R30,LOW(@2)
	STS  @0+(@1),R30
	LDS  R30,@0+(@1)+1
	ORI  R30,HIGH(@2)
	STS  @0+(@1)+1,R30
	.ENDM

	.MACRO __ORD1N
	ORI  R30,LOW(@0)
	ORI  R31,HIGH(@0)
	ORI  R22,BYTE3(@0)
	ORI  R23,BYTE4(@0)
	.ENDM

	.MACRO __ORD2N
	ORI  R26,LOW(@0)
	ORI  R27,HIGH(@0)
	ORI  R24,BYTE3(@0)
	ORI  R25,BYTE4(@0)
	.ENDM

	.MACRO __DELAY_USB
	LDI  R24,LOW(@0)
__DELAY_USB_LOOP:
	DEC  R24
	BRNE __DELAY_USB_LOOP
	.ENDM

	.MACRO __DELAY_USW
	LDI  R24,LOW(@0)
	LDI  R25,HIGH(@0)
__DELAY_USW_LOOP:
	SBIW R24,1
	BRNE __DELAY_USW_LOOP
	.ENDM

	.MACRO __GETD1S
	LDD  R30,Y+@0
	LDD  R31,Y+@0+1
	LDD  R22,Y+@0+2
	LDD  R23,Y+@0+3
	.ENDM

	.MACRO __GETD2S
	LDD  R26,Y+@0
	LDD  R27,Y+@0+1
	LDD  R24,Y+@0+2
	LDD  R25,Y+@0+3
	.ENDM

	.MACRO __PUTD1S
	STD  Y+@0,R30
	STD  Y+@0+1,R31
	STD  Y+@0+2,R22
	STD  Y+@0+3,R23
	.ENDM

	.MACRO __PUTD2S
	STD  Y+@0,R26
	STD  Y+@0+1,R27
	STD  Y+@0+2,R24
	STD  Y+@0+3,R25
	.ENDM

	.MACRO __PUTDZ2
	STD  Z+@0,R26
	STD  Z+@0+1,R27
	STD  Z+@0+2,R24
	STD  Z+@0+3,R25
	.ENDM

	.MACRO __CLRD1S
	STD  Y+@0,R30
	STD  Y+@0+1,R30
	STD  Y+@0+2,R30
	STD  Y+@0+3,R30
	.ENDM

	.MACRO __POINTB1MN
	LDI  R30,LOW(@0+(@1))
	.ENDM

	.MACRO __POINTW1MN
	LDI  R30,LOW(@0+(@1))
	LDI  R31,HIGH(@0+(@1))
	.ENDM

	.MACRO __POINTD1M
	LDI  R30,LOW(@0)
	LDI  R31,HIGH(@0)
	LDI  R22,BYTE3(@0)
	LDI  R23,BYTE4(@0)
	.ENDM

	.MACRO __POINTW1FN
	LDI  R30,LOW(2*@0+(@1))
	LDI  R31,HIGH(2*@0+(@1))
	.ENDM

	.MACRO __POINTD1FN
	LDI  R30,LOW(2*@0+(@1))
	LDI  R31,HIGH(2*@0+(@1))
	LDI  R22,BYTE3(2*@0+(@1))
	LDI  R23,BYTE4(2*@0+(@1))
	.ENDM

	.MACRO __POINTB2MN
	LDI  R26,LOW(@0+(@1))
	.ENDM

	.MACRO __POINTW2MN
	LDI  R26,LOW(@0+(@1))
	LDI  R27,HIGH(@0+(@1))
	.ENDM

	.MACRO __POINTW2FN
	LDI  R26,LOW(2*@0+(@1))
	LDI  R27,HIGH(2*@0+(@1))
	.ENDM

	.MACRO __POINTD2FN
	LDI  R26,LOW(2*@0+(@1))
	LDI  R27,HIGH(2*@0+(@1))
	LDI  R24,BYTE3(2*@0+(@1))
	LDI  R25,BYTE4(2*@0+(@1))
	.ENDM

	.MACRO __POINTBRM
	LDI  R@0,LOW(@1)
	.ENDM

	.MACRO __POINTWRM
	LDI  R@0,LOW(@2)
	LDI  R@1,HIGH(@2)
	.ENDM

	.MACRO __POINTBRMN
	LDI  R@0,LOW(@1+(@2))
	.ENDM

	.MACRO __POINTWRMN
	LDI  R@0,LOW(@2+(@3))
	LDI  R@1,HIGH(@2+(@3))
	.ENDM

	.MACRO __POINTWRFN
	LDI  R@0,LOW(@2*2+(@3))
	LDI  R@1,HIGH(@2*2+(@3))
	.ENDM

	.MACRO __GETD1N
	LDI  R30,LOW(@0)
	LDI  R31,HIGH(@0)
	LDI  R22,BYTE3(@0)
	LDI  R23,BYTE4(@0)
	.ENDM

	.MACRO __GETD2N
	LDI  R26,LOW(@0)
	LDI  R27,HIGH(@0)
	LDI  R24,BYTE3(@0)
	LDI  R25,BYTE4(@0)
	.ENDM

	.MACRO __GETB1MN
	LDS  R30,@0+(@1)
	.ENDM

	.MACRO __GETB1HMN
	LDS  R31,@0+(@1)
	.ENDM

	.MACRO __GETW1MN
	LDS  R30,@0+(@1)
	LDS  R31,@0+(@1)+1
	.ENDM

	.MACRO __GETD1MN
	LDS  R30,@0+(@1)
	LDS  R31,@0+(@1)+1
	LDS  R22,@0+(@1)+2
	LDS  R23,@0+(@1)+3
	.ENDM

	.MACRO __GETBRMN
	LDS  R@0,@1+(@2)
	.ENDM

	.MACRO __GETWRMN
	LDS  R@0,@2+(@3)
	LDS  R@1,@2+(@3)+1
	.ENDM

	.MACRO __GETWRZ
	LDD  R@0,Z+@2
	LDD  R@1,Z+@2+1
	.ENDM

	.MACRO __GETD2Z
	LDD  R26,Z+@0
	LDD  R27,Z+@0+1
	LDD  R24,Z+@0+2
	LDD  R25,Z+@0+3
	.ENDM

	.MACRO __GETB2MN
	LDS  R26,@0+(@1)
	.ENDM

	.MACRO __GETW2MN
	LDS  R26,@0+(@1)
	LDS  R27,@0+(@1)+1
	.ENDM

	.MACRO __GETD2MN
	LDS  R26,@0+(@1)
	LDS  R27,@0+(@1)+1
	LDS  R24,@0+(@1)+2
	LDS  R25,@0+(@1)+3
	.ENDM

	.MACRO __PUTB1MN
	STS  @0+(@1),R30
	.ENDM

	.MACRO __PUTW1MN
	STS  @0+(@1),R30
	STS  @0+(@1)+1,R31
	.ENDM

	.MACRO __PUTD1MN
	STS  @0+(@1),R30
	STS  @0+(@1)+1,R31
	STS  @0+(@1)+2,R22
	STS  @0+(@1)+3,R23
	.ENDM

	.MACRO __PUTB1EN
	LDI  R26,LOW(@0+(@1))
	LDI  R27,HIGH(@0+(@1))
	CALL __EEPROMWRB
	.ENDM

	.MACRO __PUTW1EN
	LDI  R26,LOW(@0+(@1))
	LDI  R27,HIGH(@0+(@1))
	CALL __EEPROMWRW
	.ENDM

	.MACRO __PUTD1EN
	LDI  R26,LOW(@0+(@1))
	LDI  R27,HIGH(@0+(@1))
	CALL __EEPROMWRD
	.ENDM

	.MACRO __PUTBR0MN
	STS  @0+(@1),R0
	.ENDM

	.MACRO __PUTBMRN
	STS  @0+(@1),R@2
	.ENDM

	.MACRO __PUTWMRN
	STS  @0+(@1),R@2
	STS  @0+(@1)+1,R@3
	.ENDM

	.MACRO __PUTBZR
	STD  Z+@1,R@0
	.ENDM

	.MACRO __PUTWZR
	STD  Z+@2,R@0
	STD  Z+@2+1,R@1
	.ENDM

	.MACRO __GETW1R
	MOV  R30,R@0
	MOV  R31,R@1
	.ENDM

	.MACRO __GETW2R
	MOV  R26,R@0
	MOV  R27,R@1
	.ENDM

	.MACRO __GETWRN
	LDI  R@0,LOW(@2)
	LDI  R@1,HIGH(@2)
	.ENDM

	.MACRO __PUTW1R
	MOV  R@0,R30
	MOV  R@1,R31
	.ENDM

	.MACRO __PUTW2R
	MOV  R@0,R26
	MOV  R@1,R27
	.ENDM

	.MACRO __ADDWRN
	SUBI R@0,LOW(-@2)
	SBCI R@1,HIGH(-@2)
	.ENDM

	.MACRO __ADDWRR
	ADD  R@0,R@2
	ADC  R@1,R@3
	.ENDM

	.MACRO __SUBWRN
	SUBI R@0,LOW(@2)
	SBCI R@1,HIGH(@2)
	.ENDM

	.MACRO __SUBWRR
	SUB  R@0,R@2
	SBC  R@1,R@3
	.ENDM

	.MACRO __ANDWRN
	ANDI R@0,LOW(@2)
	ANDI R@1,HIGH(@2)
	.ENDM

	.MACRO __ANDWRR
	AND  R@0,R@2
	AND  R@1,R@3
	.ENDM

	.MACRO __ORWRN
	ORI  R@0,LOW(@2)
	ORI  R@1,HIGH(@2)
	.ENDM

	.MACRO __ORWRR
	OR   R@0,R@2
	OR   R@1,R@3
	.ENDM

	.MACRO __EORWRR
	EOR  R@0,R@2
	EOR  R@1,R@3
	.ENDM

	.MACRO __GETWRS
	LDD  R@0,Y+@2
	LDD  R@1,Y+@2+1
	.ENDM

	.MACRO __PUTBSR
	STD  Y+@1,R@0
	.ENDM

	.MACRO __PUTWSR
	STD  Y+@2,R@0
	STD  Y+@2+1,R@1
	.ENDM

	.MACRO __MOVEWRR
	MOV  R@0,R@2
	MOV  R@1,R@3
	.ENDM

	.MACRO __INWR
	IN   R@0,@2
	IN   R@1,@2+1
	.ENDM

	.MACRO __OUTWR
	OUT  @2+1,R@1
	OUT  @2,R@0
	.ENDM

	.MACRO __CALL1MN
	LDS  R30,@0+(@1)
	LDS  R31,@0+(@1)+1
	ICALL
	.ENDM

	.MACRO __CALL1FN
	LDI  R30,LOW(2*@0+(@1))
	LDI  R31,HIGH(2*@0+(@1))
	CALL __GETW1PF
	ICALL
	.ENDM

	.MACRO __CALL2EN
	LDI  R26,LOW(@0+(@1))
	LDI  R27,HIGH(@0+(@1))
	CALL __EEPROMRDW
	ICALL
	.ENDM

	.MACRO __GETW1STACK
	IN   R26,SPL
	IN   R27,SPH
	ADIW R26,@0+1
	LD   R30,X+
	LD   R31,X
	.ENDM

	.MACRO __GETD1STACK
	IN   R26,SPL
	IN   R27,SPH
	ADIW R26,@0+1
	LD   R30,X+
	LD   R31,X+
	LD   R22,X
	.ENDM

	.MACRO __NBST
	BST  R@0,@1
	IN   R30,SREG
	LDI  R31,0x40
	EOR  R30,R31
	OUT  SREG,R30
	.ENDM


	.MACRO __PUTB1SN
	LDD  R26,Y+@0
	LDD  R27,Y+@0+1
	SUBI R26,LOW(-@1)
	SBCI R27,HIGH(-@1)
	ST   X,R30
	.ENDM

	.MACRO __PUTW1SN
	LDD  R26,Y+@0
	LDD  R27,Y+@0+1
	SUBI R26,LOW(-@1)
	SBCI R27,HIGH(-@1)
	ST   X+,R30
	ST   X,R31
	.ENDM

	.MACRO __PUTD1SN
	LDD  R26,Y+@0
	LDD  R27,Y+@0+1
	SUBI R26,LOW(-@1)
	SBCI R27,HIGH(-@1)
	CALL __PUTDP1
	.ENDM

	.MACRO __PUTB1SNS
	LDD  R26,Y+@0
	LDD  R27,Y+@0+1
	ADIW R26,@1
	ST   X,R30
	.ENDM

	.MACRO __PUTW1SNS
	LDD  R26,Y+@0
	LDD  R27,Y+@0+1
	ADIW R26,@1
	ST   X+,R30
	ST   X,R31
	.ENDM

	.MACRO __PUTD1SNS
	LDD  R26,Y+@0
	LDD  R27,Y+@0+1
	ADIW R26,@1
	CALL __PUTDP1
	.ENDM

	.MACRO __PUTB1PMN
	LDS  R26,@0
	LDS  R27,@0+1
	SUBI R26,LOW(-@1)
	SBCI R27,HIGH(-@1)
	ST   X,R30
	.ENDM

	.MACRO __PUTW1PMN
	LDS  R26,@0
	LDS  R27,@0+1
	SUBI R26,LOW(-@1)
	SBCI R27,HIGH(-@1)
	ST   X+,R30
	ST   X,R31
	.ENDM

	.MACRO __PUTD1PMN
	LDS  R26,@0
	LDS  R27,@0+1
	SUBI R26,LOW(-@1)
	SBCI R27,HIGH(-@1)
	CALL __PUTDP1
	.ENDM

	.MACRO __PUTB1PMNS
	LDS  R26,@0
	LDS  R27,@0+1
	ADIW R26,@1
	ST   X,R30
	.ENDM

	.MACRO __PUTW1PMNS
	LDS  R26,@0
	LDS  R27,@0+1
	ADIW R26,@1
	ST   X+,R30
	ST   X,R31
	.ENDM

	.MACRO __PUTD1PMNS
	LDS  R26,@0
	LDS  R27,@0+1
	ADIW R26,@1
	CALL __PUTDP1
	.ENDM

	.MACRO __PUTB1RN
	MOVW R26,R@0
	SUBI R26,LOW(-@1)
	SBCI R27,HIGH(-@1)
	ST   X,R30
	.ENDM

	.MACRO __PUTW1RN
	MOVW R26,R@0
	SUBI R26,LOW(-@1)
	SBCI R27,HIGH(-@1)
	ST   X+,R30
	ST   X,R31
	.ENDM

	.MACRO __PUTD1RN
	MOVW R26,R@0
	SUBI R26,LOW(-@1)
	SBCI R27,HIGH(-@1)
	CALL __PUTDP1
	.ENDM

	.MACRO __PUTB1RNS
	MOVW R26,R@0
	ADIW R26,@1
	ST   X,R30
	.ENDM

	.MACRO __PUTW1RNS
	MOVW R26,R@0
	ADIW R26,@1
	ST   X+,R30
	ST   X,R31
	.ENDM

	.MACRO __PUTD1RNS
	MOVW R26,R@0
	ADIW R26,@1
	CALL __PUTDP1
	.ENDM

	.MACRO __PUTB1RON
	MOV  R26,R@0
	MOV  R27,R@1
	SUBI R26,LOW(-@2)
	SBCI R27,HIGH(-@2)
	ST   X,R30
	.ENDM

	.MACRO __PUTW1RON
	MOV  R26,R@0
	MOV  R27,R@1
	SUBI R26,LOW(-@2)
	SBCI R27,HIGH(-@2)
	ST   X+,R30
	ST   X,R31
	.ENDM

	.MACRO __PUTD1RON
	MOV  R26,R@0
	MOV  R27,R@1
	SUBI R26,LOW(-@2)
	SBCI R27,HIGH(-@2)
	CALL __PUTDP1
	.ENDM

	.MACRO __PUTB1RONS
	MOV  R26,R@0
	MOV  R27,R@1
	ADIW R26,@2
	ST   X,R30
	.ENDM

	.MACRO __PUTW1RONS
	MOV  R26,R@0
	MOV  R27,R@1
	ADIW R26,@2
	ST   X+,R30
	ST   X,R31
	.ENDM

	.MACRO __PUTD1RONS
	MOV  R26,R@0
	MOV  R27,R@1
	ADIW R26,@2
	CALL __PUTDP1
	.ENDM


	.MACRO __GETB1SX
	MOVW R30,R28
	SUBI R30,LOW(-@0)
	SBCI R31,HIGH(-@0)
	LD   R30,Z
	.ENDM

	.MACRO __GETB1HSX
	MOVW R30,R28
	SUBI R30,LOW(-@0)
	SBCI R31,HIGH(-@0)
	LD   R31,Z
	.ENDM

	.MACRO __GETW1SX
	MOVW R30,R28
	SUBI R30,LOW(-@0)
	SBCI R31,HIGH(-@0)
	LD   R0,Z+
	LD   R31,Z
	MOV  R30,R0
	.ENDM

	.MACRO __GETD1SX
	MOVW R30,R28
	SUBI R30,LOW(-@0)
	SBCI R31,HIGH(-@0)
	LD   R0,Z+
	LD   R1,Z+
	LD   R22,Z+
	LD   R23,Z
	MOVW R30,R0
	.ENDM

	.MACRO __GETB2SX
	MOVW R26,R28
	SUBI R26,LOW(-@0)
	SBCI R27,HIGH(-@0)
	LD   R26,X
	.ENDM

	.MACRO __GETW2SX
	MOVW R26,R28
	SUBI R26,LOW(-@0)
	SBCI R27,HIGH(-@0)
	LD   R0,X+
	LD   R27,X
	MOV  R26,R0
	.ENDM

	.MACRO __GETD2SX
	MOVW R26,R28
	SUBI R26,LOW(-@0)
	SBCI R27,HIGH(-@0)
	LD   R0,X+
	LD   R1,X+
	LD   R24,X+
	LD   R25,X
	MOVW R26,R0
	.ENDM

	.MACRO __GETBRSX
	MOVW R30,R28
	SUBI R30,LOW(-@1)
	SBCI R31,HIGH(-@1)
	LD   R@0,Z
	.ENDM

	.MACRO __GETWRSX
	MOVW R30,R28
	SUBI R30,LOW(-@2)
	SBCI R31,HIGH(-@2)
	LD   R@0,Z+
	LD   R@1,Z
	.ENDM

	.MACRO __GETBRSX2
	MOVW R26,R28
	SUBI R26,LOW(-@1)
	SBCI R27,HIGH(-@1)
	LD   R@0,X
	.ENDM

	.MACRO __GETWRSX2
	MOVW R26,R28
	SUBI R26,LOW(-@2)
	SBCI R27,HIGH(-@2)
	LD   R@0,X+
	LD   R@1,X
	.ENDM

	.MACRO __LSLW8SX
	MOVW R30,R28
	SUBI R30,LOW(-@0)
	SBCI R31,HIGH(-@0)
	LD   R31,Z
	CLR  R30
	.ENDM

	.MACRO __PUTB1SX
	MOVW R26,R28
	SUBI R26,LOW(-@0)
	SBCI R27,HIGH(-@0)
	ST   X,R30
	.ENDM

	.MACRO __PUTW1SX
	MOVW R26,R28
	SUBI R26,LOW(-@0)
	SBCI R27,HIGH(-@0)
	ST   X+,R30
	ST   X,R31
	.ENDM

	.MACRO __PUTD1SX
	MOVW R26,R28
	SUBI R26,LOW(-@0)
	SBCI R27,HIGH(-@0)
	ST   X+,R30
	ST   X+,R31
	ST   X+,R22
	ST   X,R23
	.ENDM

	.MACRO __CLRW1SX
	MOVW R26,R28
	SUBI R26,LOW(-@0)
	SBCI R27,HIGH(-@0)
	ST   X+,R30
	ST   X,R30
	.ENDM

	.MACRO __CLRD1SX
	MOVW R26,R28
	SUBI R26,LOW(-@0)
	SBCI R27,HIGH(-@0)
	ST   X+,R30
	ST   X+,R30
	ST   X+,R30
	ST   X,R30
	.ENDM

	.MACRO __PUTB2SX
	MOVW R30,R28
	SUBI R30,LOW(-@0)
	SBCI R31,HIGH(-@0)
	ST   Z,R26
	.ENDM

	.MACRO __PUTW2SX
	MOVW R30,R28
	SUBI R30,LOW(-@0)
	SBCI R31,HIGH(-@0)
	ST   Z+,R26
	ST   Z,R27
	.ENDM

	.MACRO __PUTD2SX
	MOVW R30,R28
	SUBI R30,LOW(-@0)
	SBCI R31,HIGH(-@0)
	ST   Z+,R26
	ST   Z+,R27
	ST   Z+,R24
	ST   Z,R25
	.ENDM

	.MACRO __PUTBSRX
	MOVW R30,R28
	SUBI R30,LOW(-@1)
	SBCI R31,HIGH(-@1)
	ST   Z,R@0
	.ENDM

	.MACRO __PUTWSRX
	MOVW R30,R28
	SUBI R30,LOW(-@2)
	SBCI R31,HIGH(-@2)
	ST   Z+,R@0
	ST   Z,R@1
	.ENDM

	.MACRO __PUTB1SNX
	MOVW R26,R28
	SUBI R26,LOW(-@0)
	SBCI R27,HIGH(-@0)
	LD   R0,X+
	LD   R27,X
	MOV  R26,R0
	SUBI R26,LOW(-@1)
	SBCI R27,HIGH(-@1)
	ST   X,R30
	.ENDM

	.MACRO __PUTW1SNX
	MOVW R26,R28
	SUBI R26,LOW(-@0)
	SBCI R27,HIGH(-@0)
	LD   R0,X+
	LD   R27,X
	MOV  R26,R0
	SUBI R26,LOW(-@1)
	SBCI R27,HIGH(-@1)
	ST   X+,R30
	ST   X,R31
	.ENDM

	.MACRO __PUTD1SNX
	MOVW R26,R28
	SUBI R26,LOW(-@0)
	SBCI R27,HIGH(-@0)
	LD   R0,X+
	LD   R27,X
	MOV  R26,R0
	SUBI R26,LOW(-@1)
	SBCI R27,HIGH(-@1)
	ST   X+,R30
	ST   X+,R31
	ST   X+,R22
	ST   X,R23
	.ENDM

	.MACRO __MULBRR
	MULS R@0,R@1
	MOVW R30,R0
	.ENDM

	.MACRO __MULBRRU
	MUL  R@0,R@1
	MOVW R30,R0
	.ENDM

	.MACRO __MULBRR0
	MULS R@0,R@1
	.ENDM

	.MACRO __MULBRRU0
	MUL  R@0,R@1
	.ENDM

	.MACRO __MULBNWRU
	LDI  R26,@2
	MUL  R26,R@0
	MOVW R30,R0
	MUL  R26,R@1
	ADD  R31,R0
	.ENDM

;NAME DEFINITIONS FOR GLOBAL VARIABLES ALLOCATED TO REGISTERS
	.DEF _LedCnt=R5
	.DEF _Cnt=R6
	.DEF _TotalFlag=R4
	.DEF _AdcVal=R8
	.DEF _rx_wr_index0=R11
	.DEF _rx_rd_index0=R10
	.DEF _rx_counter0=R13
	.DEF _tx_wr_index0=R12

	.CSEG
	.ORG 0x00

;START OF CODE MARKER
__START_OF_CODE:

;INTERRUPT VECTORS
	JMP  __RESET
	JMP  _ext_int0_isr
	JMP  _ext_int1_isr
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  _timer1_ovf_isr
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  _usart0_rx_isr
	JMP  0x00
	JMP  _usart0_tx_isr
	JMP  _adc_isr
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00

_tbl10_G100:
	.DB  0x10,0x27,0xE8,0x3,0x64,0x0,0xA,0x0
	.DB  0x1,0x0
_tbl16_G100:
	.DB  0x0,0x10,0x0,0x1,0x10,0x0,0x1,0x0

;REGISTER BIT VARIABLES INITIALIZATION
__REG_BIT_VARS:
	.DW  0x0000

_0x3:
	.DB  0x7F,0x3F,0x1F,0x8F,0xC7,0xE3,0xF1,0xF8
	.DB  0xFC,0xFE,0xFC,0xF8,0xF1,0xE3,0xC7,0x8F
	.DB  0x1F,0x3F,0xFF
_0x4:
	.DB  0x5A,0x46,0x32,0x28,0x28,0x28,0x28,0x32
	.DB  0x46,0x5A,0x46,0x32,0x28,0x28,0x28,0x28
	.DB  0x32,0x46
_0x5:
	.DB  0x3F,0x6,0x5B,0x4F,0x66,0x6D,0x7D,0x7
	.DB  0x7F,0x6F
_0x42:
	.DB  0x0

__GLOBAL_INI_TBL:
	.DW  0x01
	.DW  0x02
	.DW  __REG_BIT_VARS*2

	.DW  0x13
	.DW  _pattern_table
	.DW  _0x3*2

	.DW  0x12
	.DW  _delay_table
	.DW  _0x4*2

	.DW  0x0A
	.DW  _FndDef
	.DW  _0x5*2

	.DW  0x01
	.DW  0x05
	.DW  _0x42*2

_0xFFFFFFFF:
	.DW  0

__RESET:
	CLI
	CLR  R30
	OUT  EECR,R30

;INTERRUPT VECTORS ARE PLACED
;AT THE START OF FLASH
	LDI  R31,1
	OUT  MCUCR,R31
	OUT  MCUCR,R30
	STS  XMCRB,R30

;DISABLE WATCHDOG
	LDI  R31,0x18
	OUT  WDTCR,R31
	OUT  WDTCR,R30

;CLEAR R2-R14
	LDI  R24,(14-2)+1
	LDI  R26,2
	CLR  R27
__CLEAR_REG:
	ST   X+,R30
	DEC  R24
	BRNE __CLEAR_REG

;CLEAR SRAM
	LDI  R24,LOW(__CLEAR_SRAM_SIZE)
	LDI  R25,HIGH(__CLEAR_SRAM_SIZE)
	LDI  R26,LOW(__SRAM_START)
	LDI  R27,HIGH(__SRAM_START)
__CLEAR_SRAM:
	ST   X+,R30
	SBIW R24,1
	BRNE __CLEAR_SRAM

;GLOBAL VARIABLES INITIALIZATION
	LDI  R30,LOW(__GLOBAL_INI_TBL*2)
	LDI  R31,HIGH(__GLOBAL_INI_TBL*2)
__GLOBAL_INI_NEXT:
	LPM  R24,Z+
	LPM  R25,Z+
	SBIW R24,0
	BREQ __GLOBAL_INI_END
	LPM  R26,Z+
	LPM  R27,Z+
	LPM  R0,Z+
	LPM  R1,Z+
	MOVW R22,R30
	MOVW R30,R0
__GLOBAL_INI_LOOP:
	LPM  R0,Z+
	ST   X+,R0
	SBIW R24,1
	BRNE __GLOBAL_INI_LOOP
	MOVW R30,R22
	RJMP __GLOBAL_INI_NEXT
__GLOBAL_INI_END:

	OUT  RAMPZ,R24

;HARDWARE STACK POINTER INITIALIZATION
	LDI  R30,LOW(__SRAM_END-__HEAP_SIZE)
	OUT  SPL,R30
	LDI  R30,HIGH(__SRAM_END-__HEAP_SIZE)
	OUT  SPH,R30

;DATA STACK POINTER INITIALIZATION
	LDI  R28,LOW(__SRAM_START+__DSTACK_SIZE)
	LDI  R29,HIGH(__SRAM_START+__DSTACK_SIZE)

	JMP  _main

	.ESEG
	.ORG 0

	.DSEG
	.ORG 0x500

	.CSEG
;/*****************************************************
;This program was produced by the
;CodeWizardAVR V2.05.3 Standard
;Automatic Program Generator
;© Copyright 1998-2011 Pavel Haiduc, HP InfoTech s.r.l.
;http://www.hpinfotech.com
;
;Project :
;Version :
;Date    : 2012-08-25
;Author  : No Name
;Company : No Name
;Comments:
;
;
;Chip type               : ATmega128
;Program type            : Application
;AVR Core Clock frequency: 16.000000 MHz
;Memory model            : Small
;External RAM size       : 0
;Data Stack size         : 1024
;*****************************************************/
;
;#include <mega128.h>
	#ifndef __SLEEP_DEFINED__
	#define __SLEEP_DEFINED__
	.EQU __se_bit=0x20
	.EQU __sm_mask=0x1C
	.EQU __sm_powerdown=0x10
	.EQU __sm_powersave=0x18
	.EQU __sm_standby=0x14
	.EQU __sm_ext_standby=0x1C
	.EQU __sm_adc_noise_red=0x08
	.SET power_ctrl_reg=mcucr
	#endif
;
;#include <delay.h>
;
;//------------------------------------------------------
;// LED Control¿ª ¿ß«— LED Pattern Table
;//
;//------------------------------------------------------
;unsigned char pattern_table[] = {
;0x7F, /* 01111111 */
;0x3F, /* 00111111 */
;0x1F, /* 00011111 */
;0x8F, /* 10001111 */
;0xC7, /* 11000111 */
;0xE3, /* 11100011 */
;0xF1, /* 11110001 */
;0xF8, /* 11111000 */
;0xFC, /* 11111100 */
;0xFE, /* 11111110 */
;0xFC, /* 11111100 */
;0xF8, /* 11111000 */
;0xF1, /* 11110001 */
;0xE3, /* 11100011 */
;0xC7, /* 11000111 */
;0x8F, /* 10001111 */
;0x1F, /* 00011111 */
;0x3F, /* 00111111 */
;255};

	.DSEG
;
;unsigned char delay_table[] = {
;90,
;70,
;50,
;40,
;40,
;40,
;40,
;50,
;70,
;90,
;70,
;50,
;40,
;40,
;40,
;40,
;50,
;70,
;0};
;
;unsigned char LedCnt=0;
;
;//------------------ 7-Segment Definition
;unsigned char FndDef[10] = { 0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f };
;
;unsigned int Cnt;
;
;unsigned char TotalFlag;
;
;unsigned int AdcVal;
;
;#define BIT_SET(ADDRESS,BIT)    (ADDRESS |= (1<<BIT))
;#define BIT_CLR(ADDRESS,BIT)    (ADDRESS &= ~(1<<BIT))
;
;unsigned int adc[1];
;
;// External Interrupt 0 service routine
;interrupt [EXT_INT0] void ext_int0_isr(void)
; 0000 005C {

	.CSEG
_ext_int0_isr:
	ST   -Y,R30
	IN   R30,SREG
; 0000 005D // Place your code here
; 0000 005E 	TotalFlag = 0;
	CLR  R4
; 0000 005F 
; 0000 0060 }
	OUT  SREG,R30
	LD   R30,Y+
	RETI
;
;// External Interrupt 1 service routine
;interrupt [EXT_INT1] void ext_int1_isr(void)
; 0000 0064 {
_ext_int1_isr:
	ST   -Y,R30
; 0000 0065 // Place your code here
; 0000 0066 	TotalFlag = 1;
	LDI  R30,LOW(1)
	MOV  R4,R30
; 0000 0067 
; 0000 0068 }
	LD   R30,Y+
	RETI
;
;#ifndef RXB8
;#define RXB8 1
;#endif
;
;#ifndef TXB8
;#define TXB8 0
;#endif
;
;#ifndef UPE
;#define UPE 2
;#endif
;
;#ifndef DOR
;#define DOR 3
;#endif
;
;#ifndef FE
;#define FE 4
;#endif
;
;#ifndef UDRE
;#define UDRE 5
;#endif
;
;#ifndef RXC
;#define RXC 7
;#endif
;
;#define FRAMING_ERROR (1<<FE)
;#define PARITY_ERROR (1<<UPE)
;#define DATA_OVERRUN (1<<DOR)
;#define DATA_REGISTER_EMPTY (1<<UDRE)
;#define RX_COMPLETE (1<<RXC)
;
;// USART0 Receiver buffer
;#define RX_BUFFER_SIZE0 8
;char rx_buffer0[RX_BUFFER_SIZE0];
;
;#if RX_BUFFER_SIZE0 <= 256
;unsigned char rx_wr_index0,rx_rd_index0,rx_counter0;
;#else
;unsigned int rx_wr_index0,rx_rd_index0,rx_counter0;
;#endif
;
;// This flag is set on USART0 Receiver buffer overflow
;bit rx_buffer_overflow0;
;
;// USART0 Receiver interrupt service routine
;interrupt [USART0_RXC] void usart0_rx_isr(void)
; 0000 009B {
_usart0_rx_isr:
	ST   -Y,R30
	ST   -Y,R31
	IN   R30,SREG
	ST   -Y,R30
; 0000 009C char status,data;
; 0000 009D status=UCSR0A;
	ST   -Y,R17
	ST   -Y,R16
;	status -> R17
;	data -> R16
	IN   R17,11
; 0000 009E data=UDR0;
	IN   R16,12
; 0000 009F if ((status & (FRAMING_ERROR | PARITY_ERROR | DATA_OVERRUN))==0)
	MOV  R30,R17
	ANDI R30,LOW(0x1C)
	BRNE _0x6
; 0000 00A0    {
; 0000 00A1    rx_buffer0[rx_wr_index0++]=data;
	MOV  R30,R11
	INC  R11
	LDI  R31,0
	SUBI R30,LOW(-_rx_buffer0)
	SBCI R31,HIGH(-_rx_buffer0)
	ST   Z,R16
; 0000 00A2 #if RX_BUFFER_SIZE0 == 256
; 0000 00A3    // special case for receiver buffer size=256
; 0000 00A4    if (++rx_counter0 == 0) rx_buffer_overflow0=1;
; 0000 00A5 #else
; 0000 00A6    if (rx_wr_index0 == RX_BUFFER_SIZE0) rx_wr_index0=0;
	LDI  R30,LOW(8)
	CP   R30,R11
	BRNE _0x7
	CLR  R11
; 0000 00A7    if (++rx_counter0 == RX_BUFFER_SIZE0)
_0x7:
	INC  R13
	LDI  R30,LOW(8)
	CP   R30,R13
	BRNE _0x8
; 0000 00A8       {
; 0000 00A9       rx_counter0=0;
	CLR  R13
; 0000 00AA       rx_buffer_overflow0=1;
	SET
	BLD  R2,0
; 0000 00AB       }
; 0000 00AC #endif
; 0000 00AD    }
_0x8:
; 0000 00AE }
_0x6:
	LD   R16,Y+
	LD   R17,Y+
	RJMP _0x41
;
;#ifndef _DEBUG_TERMINAL_IO_
;// Get a character from the USART0 Receiver buffer
;#define _ALTERNATE_GETCHAR_
;#pragma used+
;char getchar(void)
; 0000 00B5 {
; 0000 00B6 char data;
; 0000 00B7 while (rx_counter0==0);
;	data -> R17
; 0000 00B8 data=rx_buffer0[rx_rd_index0++];
; 0000 00B9 #if RX_BUFFER_SIZE0 != 256
; 0000 00BA if (rx_rd_index0 == RX_BUFFER_SIZE0) rx_rd_index0=0;
; 0000 00BB #endif
; 0000 00BC #asm("cli")
; 0000 00BD --rx_counter0;
; 0000 00BE #asm("sei")
; 0000 00BF return data;
; 0000 00C0 }
;#pragma used-
;#endif
;
;// USART0 Transmitter buffer
;#define TX_BUFFER_SIZE0 8
;char tx_buffer0[TX_BUFFER_SIZE0];
;
;#if TX_BUFFER_SIZE0 <= 256
;unsigned char tx_wr_index0,tx_rd_index0,tx_counter0;
;#else
;unsigned int tx_wr_index0,tx_rd_index0,tx_counter0;
;#endif
;
;// USART0 Transmitter interrupt service routine
;interrupt [USART0_TXC] void usart0_tx_isr(void)
; 0000 00D0 {
_usart0_tx_isr:
	ST   -Y,R26
	ST   -Y,R30
	ST   -Y,R31
	IN   R30,SREG
	ST   -Y,R30
; 0000 00D1 if (tx_counter0)
	LDS  R30,_tx_counter0
	CPI  R30,0
	BREQ _0xD
; 0000 00D2    {
; 0000 00D3    --tx_counter0;
	SUBI R30,LOW(1)
	STS  _tx_counter0,R30
; 0000 00D4    UDR0=tx_buffer0[tx_rd_index0++];
	LDS  R30,_tx_rd_index0
	SUBI R30,-LOW(1)
	STS  _tx_rd_index0,R30
	SUBI R30,LOW(1)
	LDI  R31,0
	SUBI R30,LOW(-_tx_buffer0)
	SBCI R31,HIGH(-_tx_buffer0)
	LD   R30,Z
	OUT  0xC,R30
; 0000 00D5 #if TX_BUFFER_SIZE0 != 256
; 0000 00D6    if (tx_rd_index0 == TX_BUFFER_SIZE0) tx_rd_index0=0;
	LDS  R26,_tx_rd_index0
	CPI  R26,LOW(0x8)
	BRNE _0xE
	LDI  R30,LOW(0)
	STS  _tx_rd_index0,R30
; 0000 00D7 #endif
; 0000 00D8    }
_0xE:
; 0000 00D9 }
_0xD:
	LD   R30,Y+
	OUT  SREG,R30
	LD   R31,Y+
	LD   R30,Y+
	LD   R26,Y+
	RETI
;
;#ifndef _DEBUG_TERMINAL_IO_
;// Write a character to the USART0 Transmitter buffer
;#define _ALTERNATE_PUTCHAR_
;#pragma used+
;void putchar(char c)
; 0000 00E0 {
; 0000 00E1 while (tx_counter0 == TX_BUFFER_SIZE0);
;	c -> Y+0
; 0000 00E2 #asm("cli")
; 0000 00E3 if (tx_counter0 || ((UCSR0A & DATA_REGISTER_EMPTY)==0))
; 0000 00E4    {
; 0000 00E5    tx_buffer0[tx_wr_index0++]=c;
; 0000 00E6 #if TX_BUFFER_SIZE0 != 256
; 0000 00E7    if (tx_wr_index0 == TX_BUFFER_SIZE0) tx_wr_index0=0;
; 0000 00E8 #endif
; 0000 00E9    ++tx_counter0;
; 0000 00EA    }
; 0000 00EB else
; 0000 00EC    UDR0=c;
; 0000 00ED #asm("sei")
; 0000 00EE }
;#pragma used-
;#endif
;
;// Standard Input/Output functions
;#include <stdio.h>
;
;// Timer1 overflow interrupt service routine
;interrupt [TIM1_OVF] void timer1_ovf_isr(void)
; 0000 00F7 {
_timer1_ovf_isr:
	ST   -Y,R30
	ST   -Y,R31
	IN   R30,SREG
	ST   -Y,R30
; 0000 00F8 // Place your code here
; 0000 00F9 	 if(TotalFlag == 0) {
	TST  R4
	BRNE _0x17
; 0000 00FA 
; 0000 00FB 	 	TCNT1 = 49911;
	LDI  R30,LOW(49911)
	LDI  R31,HIGH(49911)
	OUT  0x2C+1,R31
	OUT  0x2C,R30
; 0000 00FC    	PORTA = ~FndDef[Cnt++];
	MOVW R30,R6
	ADIW R30,1
	MOVW R6,R30
	SBIW R30,1
	SUBI R30,LOW(-_FndDef)
	SBCI R31,HIGH(-_FndDef)
	LD   R30,Z
	COM  R30
	OUT  0x1B,R30
; 0000 00FD    	if(Cnt==10) Cnt=0;
	LDI  R30,LOW(10)
	LDI  R31,HIGH(10)
	CP   R30,R6
	CPC  R31,R7
	BRNE _0x18
	CLR  R6
	CLR  R7
; 0000 00FE    }
_0x18:
; 0000 00FF 
; 0000 0100 
; 0000 0101 }
_0x17:
_0x41:
	LD   R30,Y+
	OUT  SREG,R30
	LD   R31,Y+
	LD   R30,Y+
	RETI
;
;#define ADC_VREF_TYPE 0x00
;
;// ADC interrupt service routine
;interrupt [ADC_INT] void adc_isr(void)
; 0000 0107 {
_adc_isr:
; 0000 0108 unsigned int adc_data;
; 0000 0109 // Read the AD conversion result
; 0000 010A adc_data=ADCW;
	ST   -Y,R17
	ST   -Y,R16
;	adc_data -> R16,R17
	__INWR 16,17,4
; 0000 010B // Place your code here
; 0000 010C adc[0] = adc_data;
	__PUTWMRN _adc,0,16,17
; 0000 010D 
; 0000 010E 
; 0000 010F }
	LD   R16,Y+
	LD   R17,Y+
	RETI
;
;void MUX_input()
; 0000 0112 {
_MUX_input:
; 0000 0113     ADMUX &= 0xe0;
	IN   R30,0x7
	ANDI R30,LOW(0xE0)
	OUT  0x7,R30
; 0000 0114     ADMUX = 0;
	LDI  R30,LOW(0)
	OUT  0x7,R30
; 0000 0115     ADCSRA |= 0x40;
	SBI  0x6,6
; 0000 0116 }
	RET
;
;void Action()
; 0000 0119 {
_Action:
; 0000 011A   unsigned char FirstData;
; 0000 011B   //putch(adc[0]);
; 0000 011C   FirstData = adc[0];
	ST   -Y,R17
;	FirstData -> R17
	LDS  R17,_adc
; 0000 011D   delay_ms(30);
	LDI  R26,LOW(30)
	LDI  R27,0
	CALL _delay_ms
; 0000 011E   AdcVal = adc[0];
	__GETWRMN 8,9,0,_adc
; 0000 011F 
; 0000 0120 
; 0000 0121 }
	LD   R17,Y+
	RET
;
;// Declare your global variables here
;
;void main(void)
; 0000 0126 {
_main:
; 0000 0127 // Declare your local variables here
; 0000 0128 
; 0000 0129 // Input/Output Ports initialization
; 0000 012A // Port A initialization
; 0000 012B // Func7=Out Func6=Out Func5=Out Func4=Out Func3=Out Func2=Out Func1=Out Func0=Out
; 0000 012C // State7=0 State6=0 State5=0 State4=0 State3=0 State2=0 State1=0 State0=0
; 0000 012D PORTA=0x00;
	LDI  R30,LOW(0)
	OUT  0x1B,R30
; 0000 012E DDRA=0xFF;
	LDI  R30,LOW(255)
	OUT  0x1A,R30
; 0000 012F 
; 0000 0130 // Port B initialization
; 0000 0131 // Func7=In Func6=In Func5=In Func4=In Func3=In Func2=In Func1=In Func0=In
; 0000 0132 // State7=T State6=T State5=T State4=T State3=T State2=T State1=T State0=T
; 0000 0133 PORTB=0x00;
	LDI  R30,LOW(0)
	OUT  0x18,R30
; 0000 0134 DDRB=0x00;
	OUT  0x17,R30
; 0000 0135 
; 0000 0136 // Port C initialization
; 0000 0137 // Func7=Out Func6=Out Func5=Out Func4=Out Func3=Out Func2=Out Func1=Out Func0=Out
; 0000 0138 // State7=0 State6=0 State5=0 State4=0 State3=0 State2=0 State1=0 State0=0
; 0000 0139 PORTC=0x00;
	OUT  0x15,R30
; 0000 013A DDRC=0xFF;
	LDI  R30,LOW(255)
	OUT  0x14,R30
; 0000 013B 
; 0000 013C // Port D initialization
; 0000 013D // Func7=In Func6=In Func5=In Func4=In Func3=In Func2=In Func1=In Func0=In
; 0000 013E // State7=T State6=T State5=T State4=T State3=T State2=T State1=T State0=T
; 0000 013F PORTD=0x00;
	LDI  R30,LOW(0)
	OUT  0x12,R30
; 0000 0140 DDRD=0x00;
	OUT  0x11,R30
; 0000 0141 
; 0000 0142 // Port E initialization
; 0000 0143 // Func7=In Func6=In Func5=In Func4=In Func3=In Func2=In Func1=In Func0=In
; 0000 0144 // State7=T State6=T State5=T State4=T State3=T State2=T State1=T State0=T
; 0000 0145 PORTE=0x00;
	OUT  0x3,R30
; 0000 0146 DDRE=0x00;
	OUT  0x2,R30
; 0000 0147 
; 0000 0148 // Port F initialization
; 0000 0149 // Func7=In Func6=In Func5=In Func4=In Func3=In Func2=In Func1=In Func0=In
; 0000 014A // State7=T State6=T State5=T State4=T State3=T State2=T State1=T State0=T
; 0000 014B PORTF=0x00;
	STS  98,R30
; 0000 014C DDRF=0x00;
	STS  97,R30
; 0000 014D 
; 0000 014E // Port G initialization
; 0000 014F // Func4=In Func3=In Func2=In Func1=In Func0=In
; 0000 0150 // State4=T State3=T State2=T State1=T State0=T
; 0000 0151 PORTG=0x00;
	STS  101,R30
; 0000 0152 DDRG=0x00;
	STS  100,R30
; 0000 0153 
; 0000 0154 // Timer/Counter 0 initialization
; 0000 0155 // Clock source: System Clock
; 0000 0156 // Clock value: Timer 0 Stopped
; 0000 0157 // Mode: Normal top=0xFF
; 0000 0158 // OC0 output: Disconnected
; 0000 0159 ASSR=0x00;
	OUT  0x30,R30
; 0000 015A TCCR0=0x00;
	OUT  0x33,R30
; 0000 015B TCNT0=0x00;
	OUT  0x32,R30
; 0000 015C OCR0=0x00;
	OUT  0x31,R30
; 0000 015D 
; 0000 015E // Timer/Counter 1 initialization
; 0000 015F // Clock source: System Clock
; 0000 0160 // Clock value: 15.625 kHz
; 0000 0161 // Mode: Normal top=0xFFFF
; 0000 0162 // OC1A output: Discon.
; 0000 0163 // OC1B output: Discon.
; 0000 0164 // OC1C output: Discon.
; 0000 0165 // Noise Canceler: Off
; 0000 0166 // Input Capture on Falling Edge
; 0000 0167 // Timer1 Overflow Interrupt: On
; 0000 0168 // Input Capture Interrupt: Off
; 0000 0169 // Compare A Match Interrupt: Off
; 0000 016A // Compare B Match Interrupt: Off
; 0000 016B // Compare C Match Interrupt: Off
; 0000 016C TCCR1A=0x00;
	OUT  0x2F,R30
; 0000 016D TCCR1B=0x05;
	LDI  R30,LOW(5)
	OUT  0x2E,R30
; 0000 016E TCNT1H=0x00;
	LDI  R30,LOW(0)
	OUT  0x2D,R30
; 0000 016F TCNT1L=0x00;
	OUT  0x2C,R30
; 0000 0170 ICR1H=0x00;
	OUT  0x27,R30
; 0000 0171 ICR1L=0x00;
	OUT  0x26,R30
; 0000 0172 OCR1AH=0x00;
	OUT  0x2B,R30
; 0000 0173 OCR1AL=0x00;
	OUT  0x2A,R30
; 0000 0174 OCR1BH=0x00;
	OUT  0x29,R30
; 0000 0175 OCR1BL=0x00;
	OUT  0x28,R30
; 0000 0176 OCR1CH=0x00;
	STS  121,R30
; 0000 0177 OCR1CL=0x00;
	STS  120,R30
; 0000 0178 
; 0000 0179 // Timer/Counter 2 initialization
; 0000 017A // Clock source: System Clock
; 0000 017B // Clock value: Timer2 Stopped
; 0000 017C // Mode: Normal top=0xFF
; 0000 017D // OC2 output: Disconnected
; 0000 017E TCCR2=0x00;
	OUT  0x25,R30
; 0000 017F TCNT2=0x00;
	OUT  0x24,R30
; 0000 0180 OCR2=0x00;
	OUT  0x23,R30
; 0000 0181 
; 0000 0182 // Timer/Counter 3 initialization
; 0000 0183 // Clock source: System Clock
; 0000 0184 // Clock value: Timer3 Stopped
; 0000 0185 // Mode: Normal top=0xFFFF
; 0000 0186 // OC3A output: Discon.
; 0000 0187 // OC3B output: Discon.
; 0000 0188 // OC3C output: Discon.
; 0000 0189 // Noise Canceler: Off
; 0000 018A // Input Capture on Falling Edge
; 0000 018B // Timer3 Overflow Interrupt: Off
; 0000 018C // Input Capture Interrupt: Off
; 0000 018D // Compare A Match Interrupt: Off
; 0000 018E // Compare B Match Interrupt: Off
; 0000 018F // Compare C Match Interrupt: Off
; 0000 0190 TCCR3A=0x00;
	STS  139,R30
; 0000 0191 TCCR3B=0x00;
	STS  138,R30
; 0000 0192 TCNT3H=0x00;
	STS  137,R30
; 0000 0193 TCNT3L=0x00;
	STS  136,R30
; 0000 0194 ICR3H=0x00;
	STS  129,R30
; 0000 0195 ICR3L=0x00;
	STS  128,R30
; 0000 0196 OCR3AH=0x00;
	STS  135,R30
; 0000 0197 OCR3AL=0x00;
	STS  134,R30
; 0000 0198 OCR3BH=0x00;
	STS  133,R30
; 0000 0199 OCR3BL=0x00;
	STS  132,R30
; 0000 019A OCR3CH=0x00;
	STS  131,R30
; 0000 019B OCR3CL=0x00;
	STS  130,R30
; 0000 019C 
; 0000 019D // External Interrupt(s) initialization
; 0000 019E // INT0: On
; 0000 019F // INT0 Mode: Falling Edge
; 0000 01A0 // INT1: On
; 0000 01A1 // INT1 Mode: Falling Edge
; 0000 01A2 // INT2: Off
; 0000 01A3 // INT3: Off
; 0000 01A4 // INT4: Off
; 0000 01A5 // INT5: Off
; 0000 01A6 // INT6: Off
; 0000 01A7 // INT7: Off
; 0000 01A8 EICRA=0x0A;
	LDI  R30,LOW(10)
	STS  106,R30
; 0000 01A9 EICRB=0x00;
	LDI  R30,LOW(0)
	OUT  0x3A,R30
; 0000 01AA EIMSK=0x03;
	LDI  R30,LOW(3)
	OUT  0x39,R30
; 0000 01AB EIFR=0x03;
	OUT  0x38,R30
; 0000 01AC 
; 0000 01AD // Timer(s)/Counter(s) Interrupt(s) initialization
; 0000 01AE TIMSK=0x04;
	LDI  R30,LOW(4)
	OUT  0x37,R30
; 0000 01AF 
; 0000 01B0 ETIMSK=0x00;
	LDI  R30,LOW(0)
	STS  125,R30
; 0000 01B1 
; 0000 01B2 // USART0 initialization
; 0000 01B3 // Communication Parameters: 8 Data, 1 Stop, No Parity
; 0000 01B4 // USART0 Receiver: On
; 0000 01B5 // USART0 Transmitter: On
; 0000 01B6 // USART0 Mode: Asynchronous
; 0000 01B7 // USART0 Baud Rate: 9600
; 0000 01B8 UCSR0A=0x00;
	OUT  0xB,R30
; 0000 01B9 UCSR0B=0xD8;
	LDI  R30,LOW(216)
	OUT  0xA,R30
; 0000 01BA UCSR0C=0x06;
	LDI  R30,LOW(6)
	STS  149,R30
; 0000 01BB UBRR0H=0x00;
	LDI  R30,LOW(0)
	STS  144,R30
; 0000 01BC UBRR0L=0x67;
	LDI  R30,LOW(103)
	OUT  0x9,R30
; 0000 01BD 
; 0000 01BE // USART1 initialization
; 0000 01BF // USART1 disabled
; 0000 01C0 UCSR1B=0x00;
	LDI  R30,LOW(0)
	STS  154,R30
; 0000 01C1 
; 0000 01C2 // Analog Comparator initialization
; 0000 01C3 // Analog Comparator: Off
; 0000 01C4 // Analog Comparator Input Capture by Timer/Counter 1: Off
; 0000 01C5 ACSR=0x80;
	LDI  R30,LOW(128)
	OUT  0x8,R30
; 0000 01C6 SFIOR=0x00;
	LDI  R30,LOW(0)
	OUT  0x20,R30
; 0000 01C7 
; 0000 01C8 // ADC initialization
; 0000 01C9 // ADC Clock frequency: 125.000 kHz
; 0000 01CA // ADC Voltage Reference: AREF pin
; 0000 01CB ADMUX=ADC_VREF_TYPE & 0xff;
	OUT  0x7,R30
; 0000 01CC ADCSRA=0x8F;
	LDI  R30,LOW(143)
	OUT  0x6,R30
; 0000 01CD 
; 0000 01CE // SPI initialization
; 0000 01CF // SPI disabled
; 0000 01D0 SPCR=0x00;
	LDI  R30,LOW(0)
	OUT  0xD,R30
; 0000 01D1 
; 0000 01D2 // TWI initialization
; 0000 01D3 // TWI disabled
; 0000 01D4 TWCR=0x00;
	STS  116,R30
; 0000 01D5 
; 0000 01D6 // Global enable interrupts
; 0000 01D7 #asm("sei")
	sei
; 0000 01D8 
; 0000 01D9 
; 0000 01DA PORTA = 0x80;
	LDI  R30,LOW(128)
	OUT  0x1B,R30
; 0000 01DB delay_ms(1000);
	LDI  R26,LOW(1000)
	LDI  R27,HIGH(1000)
	CALL _delay_ms
; 0000 01DC PORTA = 0xff;
	LDI  R30,LOW(255)
	OUT  0x1B,R30
; 0000 01DD delay_ms(1000);
	LDI  R26,LOW(1000)
	LDI  R27,HIGH(1000)
	CALL _delay_ms
; 0000 01DE TotalFlag = 0;
	CLR  R4
; 0000 01DF 
; 0000 01E0 while (1)
_0x19:
; 0000 01E1       {
; 0000 01E2 
; 0000 01E3       	MUX_input();
	RCALL _MUX_input
; 0000 01E4         Action();
	RCALL _Action
; 0000 01E5       // Place your code here
; 0000 01E6 				 if (delay_table[LedCnt] > 0) {
	CALL SUBOPT_0x0
	SUBI R30,LOW(-_delay_table)
	SBCI R31,HIGH(-_delay_table)
	LD   R26,Z
	CPI  R26,LOW(0x1)
	BRLO _0x1C
; 0000 01E7 						PORTC = pattern_table[LedCnt];
	CALL SUBOPT_0x0
	SUBI R30,LOW(-_pattern_table)
	SBCI R31,HIGH(-_pattern_table)
	LD   R30,Z
	OUT  0x15,R30
; 0000 01E8 						delay_ms(delay_table[LedCnt]);
	CALL SUBOPT_0x0
	SUBI R30,LOW(-_delay_table)
	SBCI R31,HIGH(-_delay_table)
	LD   R26,Z
	LDI  R27,0
	CALL _delay_ms
; 0000 01E9 						LedCnt++;
	INC  R5
; 0000 01EA 				}
; 0000 01EB 				else{
	RJMP _0x1D
_0x1C:
; 0000 01EC 						LedCnt = 0;
	CLR  R5
; 0000 01ED 				}
_0x1D:
; 0000 01EE 
; 0000 01EF 				if(TotalFlag == 1) {
	LDI  R30,LOW(1)
	CP   R30,R4
	BREQ PC+3
	JMP _0x1E
; 0000 01F0 					if((AdcVal >0)&&(AdcVal<0x1f)) {
	CLR  R0
	CP   R0,R8
	CPC  R0,R9
	BRSH _0x20
	LDI  R30,LOW(31)
	LDI  R31,HIGH(31)
	CP   R8,R30
	CPC  R9,R31
	BRLO _0x21
_0x20:
	RJMP _0x1F
_0x21:
; 0000 01F1 						PORTA = ~FndDef[0];
	LDS  R30,_FndDef
	RJMP _0x40
; 0000 01F2 					}
; 0000 01F3 					else if((AdcVal > 0x20)&&(AdcVal<0x3f)) {
_0x1F:
	LDI  R30,LOW(32)
	LDI  R31,HIGH(32)
	CP   R30,R8
	CPC  R31,R9
	BRSH _0x24
	LDI  R30,LOW(63)
	LDI  R31,HIGH(63)
	CP   R8,R30
	CPC  R9,R31
	BRLO _0x25
_0x24:
	RJMP _0x23
_0x25:
; 0000 01F4 						PORTA = ~FndDef[1];
	__GETB1MN _FndDef,1
	RJMP _0x40
; 0000 01F5 					}
; 0000 01F6 					else if((AdcVal > 0x40)&&(AdcVal<0x5f)) {
_0x23:
	LDI  R30,LOW(64)
	LDI  R31,HIGH(64)
	CP   R30,R8
	CPC  R31,R9
	BRSH _0x28
	LDI  R30,LOW(95)
	LDI  R31,HIGH(95)
	CP   R8,R30
	CPC  R9,R31
	BRLO _0x29
_0x28:
	RJMP _0x27
_0x29:
; 0000 01F7 						PORTA = ~FndDef[2];
	__GETB1MN _FndDef,2
	RJMP _0x40
; 0000 01F8 					}
; 0000 01F9 					else if((AdcVal > 0x60)&&(AdcVal<0x7f)) {
_0x27:
	LDI  R30,LOW(96)
	LDI  R31,HIGH(96)
	CP   R30,R8
	CPC  R31,R9
	BRSH _0x2C
	LDI  R30,LOW(127)
	LDI  R31,HIGH(127)
	CP   R8,R30
	CPC  R9,R31
	BRLO _0x2D
_0x2C:
	RJMP _0x2B
_0x2D:
; 0000 01FA 						PORTA = ~FndDef[3];
	__GETB1MN _FndDef,3
	RJMP _0x40
; 0000 01FB 					}
; 0000 01FC 					else if((AdcVal > 0x80)&&(AdcVal<0x9f)) {
_0x2B:
	LDI  R30,LOW(128)
	LDI  R31,HIGH(128)
	CP   R30,R8
	CPC  R31,R9
	BRSH _0x30
	LDI  R30,LOW(159)
	LDI  R31,HIGH(159)
	CP   R8,R30
	CPC  R9,R31
	BRLO _0x31
_0x30:
	RJMP _0x2F
_0x31:
; 0000 01FD 						PORTA = ~FndDef[4];
	__GETB1MN _FndDef,4
	RJMP _0x40
; 0000 01FE 					}
; 0000 01FF 					else if((AdcVal >0xa0)&&(AdcVal<0xbf)) {
_0x2F:
	LDI  R30,LOW(160)
	LDI  R31,HIGH(160)
	CP   R30,R8
	CPC  R31,R9
	BRSH _0x34
	LDI  R30,LOW(191)
	LDI  R31,HIGH(191)
	CP   R8,R30
	CPC  R9,R31
	BRLO _0x35
_0x34:
	RJMP _0x33
_0x35:
; 0000 0200 						PORTA = ~FndDef[5];
	__GETB1MN _FndDef,5
	RJMP _0x40
; 0000 0201 					}
; 0000 0202 					else if((AdcVal >0xc0)&&(AdcVal<0xdf)) {
_0x33:
	LDI  R30,LOW(192)
	LDI  R31,HIGH(192)
	CP   R30,R8
	CPC  R31,R9
	BRSH _0x38
	LDI  R30,LOW(223)
	LDI  R31,HIGH(223)
	CP   R8,R30
	CPC  R9,R31
	BRLO _0x39
_0x38:
	RJMP _0x37
_0x39:
; 0000 0203 						PORTA = ~FndDef[6];
	__GETB1MN _FndDef,6
	RJMP _0x40
; 0000 0204 					}
; 0000 0205 					else if((AdcVal >0xe0)&&(AdcVal<0xff)) {
_0x37:
	LDI  R30,LOW(224)
	LDI  R31,HIGH(224)
	CP   R30,R8
	CPC  R31,R9
	BRSH _0x3C
	LDI  R30,LOW(255)
	LDI  R31,HIGH(255)
	CP   R8,R30
	CPC  R9,R31
	BRLO _0x3D
_0x3C:
	RJMP _0x3B
_0x3D:
; 0000 0206 						PORTA = ~FndDef[7];
	__GETB1MN _FndDef,7
	RJMP _0x40
; 0000 0207 					}
; 0000 0208 					else {
_0x3B:
; 0000 0209 						PORTA = ~FndDef[8];
	__GETB1MN _FndDef,8
_0x40:
	COM  R30
	OUT  0x1B,R30
; 0000 020A 					}
; 0000 020B 
; 0000 020C 
; 0000 020D 				}
; 0000 020E 
; 0000 020F 
; 0000 0210       }
_0x1E:
	RJMP _0x19
; 0000 0211 }
_0x3F:
	RJMP _0x3F
	#ifndef __SLEEP_DEFINED__
	#define __SLEEP_DEFINED__
	.EQU __se_bit=0x20
	.EQU __sm_mask=0x1C
	.EQU __sm_powerdown=0x10
	.EQU __sm_powersave=0x18
	.EQU __sm_standby=0x14
	.EQU __sm_ext_standby=0x1C
	.EQU __sm_adc_noise_red=0x08
	.SET power_ctrl_reg=mcucr
	#endif

	.CSEG

	.CSEG

	.CSEG

	.DSEG
_pattern_table:
	.BYTE 0x13
_delay_table:
	.BYTE 0x13
_FndDef:
	.BYTE 0xA
_adc:
	.BYTE 0x2
_rx_buffer0:
	.BYTE 0x8
_tx_buffer0:
	.BYTE 0x8
_tx_rd_index0:
	.BYTE 0x1
_tx_counter0:
	.BYTE 0x1

	.CSEG
;OPTIMIZER ADDED SUBROUTINE, CALLED 3 TIMES, CODE SIZE REDUCTION:1 WORDS
SUBOPT_0x0:
	MOV  R30,R5
	LDI  R31,0
	RET


	.CSEG
_delay_ms:
	adiw r26,0
	breq __delay_ms1
__delay_ms0:
	__DELAY_USW 0xFA0
	wdr
	sbiw r26,1
	brne __delay_ms0
__delay_ms1:
	ret

;END OF CODE MARKER
__END_OF_CODE:
