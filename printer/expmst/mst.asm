;  KD Line Printer Controller Firmware V2.2
;  TITLE    : mst.asm
;  ABSTRACT : Master Startup Program
;  AUTHOR(S): Jung-Wook Shin
;  DATE     : 1999. 1.
;  Copyright (c) 1996-1999  by  Jung-Wook Shin
;  Printer Lab. Phoenix Information Technology
;  All rights reserved.

                ORG     $0
                DC.L    SYS_STACKTOP
                DC.L    INISTART
                DC.L    $0
                DC.L    $0
                DC.L    $0
                DC.L    $0
                DC.L    $0
                DC.L    $0
                DC.L    $0
                DC.L    $0
                DC.L    $0
                DC.L    $0
                DC.L    $0
                DC.L    $0
                DC.L    $0
                DC.L    $0

                DC.L    $0
                DC.L    $0
                DC.L    $0
                DC.L    $0
                DC.L    $0
                DC.L    $0
                DC.L    $0
                DC.L    $0
                DC.L    $0
                DC.L    $0
                DC.L    _Serial
                DC.L    _Parallel
                DC.L    $0
                DC.L    $0
                DC.L    $0
                DC.L    $0
                ORG     $100
                DC.L    _S_M_Int
                DC.L    $0
                DC.L    $0
                DC.L    $0
                DC.L    $0
                DC.L    $0
                DC.L    $0
                DC.L    $0
                DC.L    $0
                DC.L    $0
                DC.L    $0
                DC.L    $0
                DC.L    $0
                DC.L    $0
                DC.L    $0
                DC.L    $0
                DC.L    $0
                DC.L    $0
                DC.L    $0
                DC.L    $0
                DC.L    $0
                DC.L    $0

                OPT     CASE
INISTART        IDNT
                SECTION CODE,,C
                XDEF    INISTART
                XREF    SYS_STACKTOP
                XREF    _main
;               XREF    __START
                XREF    __initcopy
                XREF    _S_M_Int
                XREF    _Serial
                XREF    _Parallel

                ORG     $400
INISTART:       MOVE.L  #SYS_STACKTOP,SP
                MOVE.W  #$2700,SR
                JSR     __initcopy
                JSR     _main
;                JSR     __START
                STOP    #$2700
                END     INISTART
