;               Slave Startup Program
;               Date : 1996. 11. 20.
;               Kia Information Systems. Printer Development Team.

                ORG     $0
                DC.L    SYS_STACKTOP
                DC.L    INISTART

                ORG     $100
                DC.L    _PFault
                DC.L    _PFault
                DC.L    $0
                DC.L    $0
                DC.L    _PFault
                DC.L    _PFault
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
                DC.L    _SOpInt
                DC.L    _SOpInt
                DC.L    $0
                DC.L    $0
                DC.L    _LpPe

                OPT     CASE
INISTART        IDNT
                SECTION CODE,,C
                XDEF    INISTART
                XREF    SYS_STACKTOP
                XREF    _main
;               XREF    __START
                XREF    __initcopy
                XREF    _SOpInt
                XREF    _PFault
                XREF    _LpPe

                ORG     $400
INISTART:       MOVE.L  #SYS_STACKTOP,SP
                MOVE.W  #$2700,SR

                JSR     __initcopy
                JSR     _main
;                JSR     __START
                STOP    #$2700
                END     INISTART
