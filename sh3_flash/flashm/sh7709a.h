/****************************************************************************/
/*		SH7709A/SH7729 Internal Register									*/
/****************************************************************************/
#ifndef		_SH7709A_H_
#define		_SH7709A_H_

struct st_sci {                                         /* struct SCI   */
              union {                                   /* SCSMR        */
                    unsigned char BYTE;                 /*  Byte Access */
                    struct {                            /*  Bit  Access */
                           unsigned char CA  :1;        /*    C/A       */
                           unsigned char CHR :1;        /*    CHR       */
                           unsigned char PE  :1;        /*    PE        */
                           unsigned char OE  :1;        /*    O/E       */
                           unsigned char STOP:1;        /*    STOP      */
                           unsigned char MP  :1;        /*    MP        */
                           unsigned char CKS :2;        /*    CKS       */
                           }      BIT;                  /*              */
                    }           SCSMR;                  /*              */
              char              wk1;                    /*              */
              unsigned char     SCBRR;                  /* SCBRR        */
              char              wk2;                    /*              */
              union {                                   /* SCSCR        */
                    unsigned char BYTE;                 /*  Byte Access */
                    struct {                            /*  Bit  Access */
                           unsigned char TIE :1;        /*    TIE       */
                           unsigned char RIE :1;        /*    RIE       */
                           unsigned char TE  :1;        /*    TE        */
                           unsigned char RE  :1;        /*    RE        */
                           unsigned char MPIE:1;        /*    MPIE      */
                           unsigned char TEIE:1;        /*    TEIE      */
                           unsigned char CKE :2;        /*    CKE       */
                           }      BIT;                  /*              */
                    }           SCSCR;                  /*              */
              char              wk3;                    /*              */
              unsigned char     SCTDR;                  /* SCTDR        */
              char              wk4;                    /*              */
              union {                                   /* SCSSR        */
                    unsigned char BYTE;                 /*  Byte Access */
                    struct {                            /*  Bit  Access */
                           unsigned char TDRE:1;        /*    TDRE      */
                           unsigned char RDRF:1;        /*    RDRF      */
                           unsigned char ORER:1;        /*    ORER      */
                           unsigned char FER :1;        /*    FER       */
                           unsigned char PER :1;        /*    PER       */
                           unsigned char TEND:1;        /*    TEND      */
                           unsigned char MPB :1;        /*    MPB       */
                           unsigned char MPBT:1;        /*    MPBT      */
                           }      BIT;                  /*              */
                    }           SCSSR;                  /*              */
              char              wk5;                    /*              */
              unsigned char     SCRDR;                  /* SCRDR        */
              char              wk6;                    /*              */
              union {                                   /* SCSCMR       */
                    unsigned char BYTE;                 /*  Byte Access */
                    struct {                            /*  Bit  Access */
                           unsigned char     :4;        /*              */
                           unsigned char SDIR:1;        /*    SDIR      */
                           unsigned char SINV:1;        /*    SINV      */
                           unsigned char     :1;        /*              */
                           unsigned char SMIF:1;        /*    SMIF      */
                           }      BIT;                  /*              */
                    }           SCSCMR;                 /*              */
};                                                      /*              */
struct st_scif {                                        /* struct SCIF  */
               union {                                  /* SCSMR        */
                     unsigned char BYTE;                /*  Byte Access */
                     struct {                           /*  Bit  Access */
                            unsigned char     :1;       /*              */
                            unsigned char CHR :1;       /*    CHR       */
                            unsigned char PE  :1;       /*    PE        */
                            unsigned char OE  :1;       /*    O/E       */
                            unsigned char STOP:1;       /*    STOP      */
                            unsigned char     :1;       /*              */
                            unsigned char CKS :2;       /*    CKS       */
                            }      BIT;                 /*              */
                     }          SCSMR;                  /*              */
               char             wk1;                    /*              */
               unsigned char    SCBRR;                  /* SCBRR        */
               char             wk2;                    /*              */
               union {                                  /* SCSCR        */
                     unsigned char BYTE;                /*  Byte Access */
                     struct {                           /*  Bit  Access */
                            unsigned char TIE:1;        /*    TIE       */
                            unsigned char RIE:1;        /*    RIE       */
                            unsigned char TE :1;        /*    TE        */
                            unsigned char RE :1;        /*    RE        */
                            unsigned char    :2;        /*              */
                            unsigned char CKE:2;        /*    CKE       */
                            }      BIT;                 /*              */
                     }          SCSCR;                  /*              */
               char             wk3;                    /*              */
               unsigned char    SCFTDR;                 /* SCFTDR       */
               char             wk4;                    /*              */
               union {                                  /* SCSSR        */
                     unsigned short WORD;               /*  Word Access */
                     struct {                           /*  Bit  Access */
                            unsigned short PERC:4;      /*    PER3-0    */
                            unsigned short FERC:4;      /*    FER3-0    */
                            unsigned short ER  :1;      /*    ER        */
                            unsigned short TEND:1;      /*    TEND      */
                            unsigned short TDFE:1;      /*    TDFE      */
                            unsigned short BRK :1;      /*    BRK       */
                            unsigned short FER :1;      /*    FER       */
                            unsigned short PER :1;      /*    PER       */
                            unsigned short RDF :1;      /*    RDF       */
                            unsigned short DR  :1;      /*    DR        */
                            }       BIT;                /*              */
                     }          SCSSR;                  /*              */
               unsigned char    SCFRDR;                 /* SCFRDR       */
               char             wk5;                    /*              */
               union {                                  /* SCFCR        */
                     unsigned char BYTE;                /*  Byte Access */
                     struct {                           /*  Bit  Access */
                            unsigned char RTRG :2;      /*    RTRG      */
                            unsigned char TTRG :2;      /*    TTRG      */
                            unsigned char MCE  :1;      /*    MCE       */
                            unsigned char TFRST:1;      /*    TFRST     */
                            unsigned char RFRST:1;      /*    RFRST     */
                            unsigned char LOOP :1;      /*    LOOP      */
                            }      BIT;                 /*              */
                     }          SCFCR;                  /*              */
               char             wk6;                    /*              */
               union {                                  /* SCFDR        */
                     unsigned short WORD;               /*  Word Access */
                     struct {                           /*  Byte Access */
                            unsigned short  :3;         /*              */
                            unsigned short T:5;         /*    T         */
                            unsigned short  :3;         /*              */
                            unsigned short R:5;         /*    R         */
                            }       BIT;                /*              */
                     }          SCFDR;                  /*              */
};                                                      /*              */
struct st_irda {                                        /* struct IrDA  */
               union {                                  /* SCSMR        */
                     unsigned char BYTE;                /*  Byte Access */
                     struct {                           /*  Bit  Access */
                            unsigned char IRMOD:1;      /*    IRMOD     */
                            unsigned char ICK  :4;      /*    ICK       */
                            unsigned char PSEL :1;      /*    PSEL      */
                            unsigned char CKS  :2;      /*    CKS       */
                            }      BIT;                 /*              */
                     }          SCSMR;                  /*              */
               char             wk1;                    /*              */
               unsigned char    SCBRR;                  /* SCBRR        */
               char             wk2;                    /*              */
               union {                                  /* SCSCR        */
                     unsigned char BYTE;                /*  Byte Access */
                     struct {                           /*  Bit  Access */
                            unsigned char TIE:1;        /*    TIE       */
                            unsigned char RIE:1;        /*    RIE       */
                            unsigned char TE :1;        /*    TE        */
                            unsigned char RE :1;        /*    RE        */
                            unsigned char    :2;        /*              */
                            unsigned char CKE:2;        /*    CKE       */
                            }      BIT;                 /*              */
                     }          SCSCR;                  /*              */
               char             wk3;                    /*              */
               unsigned char    SCFTDR;                 /* SCFTDR       */
               char             wk4;                    /*              */
               union {                                  /* SCSSR        */
                     unsigned short WORD;               /*  Word Access */
                     struct {                           /*  Bit  Access */
                            unsigned short PERC:4;      /*    PER3-0    */
                            unsigned short FERC:4;      /*    FER3-0    */
                            unsigned short ER  :1;      /*    ER        */
                            unsigned short TEND:1;      /*    TEND      */
                            unsigned short TDFE:1;      /*    TDFE      */
                            unsigned short BRK :1;      /*    BRK       */
                            unsigned short FER :1;      /*    FER       */
                            unsigned short PER :1;      /*    PER       */
                            unsigned short RDF :1;      /*    RDF       */
                            unsigned short DR  :1;      /*    DR        */
                            }       BIT;                /*              */
                     }          SCSSR;                  /*              */
               unsigned char    SCFRDR;                 /* SCFRDR       */
               char             wk5;                    /*              */
               union {                                  /* SCFCR        */
                     unsigned char BYTE;                /*  Byte Access */
                     struct {                           /*  Bit  Access */
                            unsigned char RTRG :2;      /*    RTRG      */
                            unsigned char TTRG :2;      /*    TTRG      */
                            unsigned char MCE  :1;      /*    MCE       */
                            unsigned char TFRST:1;      /*    TFRST     */
                            unsigned char RFRST:1;      /*    RFRST     */
                            unsigned char LOOP :1;      /*    LOOP      */
                            }      BIT;                 /*              */
                     }          SCFCR;                  /*              */
               char             wk6;                    /*              */
               union {                                  /* SCFDR        */
                     unsigned short WORD;               /*  Word Access */
                     struct {                           /*  Byte Access */
                            unsigned short  :3;         /*              */
                            unsigned short T:5;         /*    T         */
                            unsigned short  :3;         /*              */
                            unsigned short R:5;         /*    R         */
                            }       BIT;                /*              */
                     }          SCFDR;                  /*              */
};                                                      /*              */
struct st_tmu {                                         /* struct TMU   */
              union {                                   /* TOCR         */
                    unsigned char BYTE;                 /*  Byte Access */
                    struct {                            /*  Bit  Access */
                           unsigned char     :7;        /*              */
                           unsigned char TCOE:1;        /*    TCOE      */
                           }      BIT;                  /*              */
                    }           TOCR;                   /*              */
              char              wk;                     /*              */
              union {                                   /* TSTR         */
                    unsigned char BYTE;                 /*  Byte Access */
                    struct {                            /*  Bit  Access */
                           unsigned char     :5;        /*              */
                           unsigned char STR2:1;        /*    STR2      */
                           unsigned char STR1:1;        /*    STR1      */
                           unsigned char STR0:1;        /*    STR0      */
                           }      BIT;                  /*              */
                    }           TSTR;                   /*              */
};                                                      /*              */
struct st_tmu0 {                                        /* struct TMU0  */
               unsigned int     TCOR;                   /* TCOR         */
               unsigned int     TCNT;                   /* TCNT         */
               union {                                  /* TCR          */
                     unsigned short WORD;               /*  Word Access */
                     struct {                           /*  Bit  Access */
                            unsigned short     :7;      /*              */
                            unsigned short UNF :1;      /*    UNF       */
                            unsigned short     :2;      /*              */
                            unsigned short UNIE:1;      /*    UNIE      */
                            unsigned short CKEG:2;      /*    CKEG      */
                            unsigned short TPSC:3;      /*    TPSC      */
                            }       BIT;                /*              */
                     }          TCR;                    /*              */
};                                                      /*              */
struct st_tmu2 {                                        /* struct TMU2  */
               unsigned int     TCOR;                   /* TCOR         */
               unsigned int     TCNT;                   /* TCNT         */
               union {                                  /* TCR          */
                     unsigned short WORD;               /*  Word Access */
                     struct {                           /*  Bit  Access */
                            unsigned short     :6;      /*              */
                            unsigned short ICPF:1;      /*    ICPF      */
                            unsigned short UNF :1;      /*    UNF       */
                            unsigned short ICPE:2;      /*    ICPE      */
                            unsigned short UNIE:1;      /*    UNIE      */
                            unsigned short CKEG:2;      /*    CKEG      */
                            unsigned short TPSC:3;      /*    TPSC      */
                            }       BIT;                /*              */
                     }          TCR;                    /*              */
               char             wk[2];                  /*              */
               unsigned int     TCPR;                   /* TCPR         */
};                                                      /*              */
struct st_rtc {                                         /* struct RTC   */
              union {                                   /* R64CNT       */
                    unsigned char BYTE;                 /*  Byte Access */
                    struct {                            /*  Bit  Access */
                           unsigned char     :1;        /*              */
                           unsigned char Hz1 :1;        /*     1Hz      */
                           unsigned char Hz2 :1;        /*     2Hz      */
                           unsigned char Hz4 :1;        /*     4Hz      */
                           unsigned char Hz8 :1;        /*     8Hz      */
                           unsigned char Hz16:1;        /*    16Hz      */
                           unsigned char Hz32:1;        /*    32Hz      */
                           unsigned char Hz64:1;        /*    64Hz      */
                           }      BIT;                  /*              */
                    }           R64CNT;                 /*              */
              char              wk1;                    /*              */
              union {                                   /* RSECCNT      */
                    unsigned char BYTE;                 /*  Byte Access */
                    struct {                            /*  Bit  Access */
                           unsigned char    :1;         /*              */
                           unsigned char S10:3;         /*    10sec     */
                           unsigned char S1 :4;         /*     1sec     */
                           }      BIT;                  /*              */
                    }           RSECCNT;                /*              */
              char              wk2;                    /*              */
              union {                                   /* RMINCNT      */
                    unsigned char BYTE;                 /*  Byte Access */
                    struct {                            /*  Bit  Access */
                           unsigned char    :1;         /*              */
                           unsigned char M10:3;         /*    10min     */
                           unsigned char M1 :4;         /*     1min     */
                           }      BIT;                  /*              */
                    }           RMINCNT;                /*              */
              char              wk3;                    /*              */
              union {                                   /* RHRCNT       */
                    unsigned char BYTE;                 /*  Byte Access */
                    struct {                            /*  Bit  Access */
                           unsigned char    :2;         /*              */
                           unsigned char H10:2;         /*    10sec     */
                           unsigned char H1 :4;         /*     1sec     */
                           }      BIT;                  /*              */
                    }           RHRCNT;                 /*              */
              char              wk4;                    /*              */
              union {                                   /* RWKCNT       */
                    unsigned char BYTE;                 /*  Byte Access */
                    struct {                            /*  Bit  Access */
                           unsigned char   :5;          /*              */
                           unsigned char WK:3;          /*    week      */
                           }      BIT;                  /*              */
                    }           RWKCNT;                 /*              */
              char              wk5;                    /*              */
              union {                                   /* RDAYCNT      */
                    unsigned char BYTE;                 /*  Byte Access */
                    struct {                            /*  Bit  Access */
                           unsigned char    :2;         /*              */
                           unsigned char D10:2;         /*    10day     */
                           unsigned char D1 :4;         /*     1day     */
                           }      BIT;                  /*              */
                    }           RDAYCNT;                /*              */
              char              wk6;                    /*              */
              union {                                   /* RMONCNT      */
                    unsigned char BYTE;                 /*  Byte Access */
                    struct {                            /*  Bit  Access */
                           unsigned char    :3;         /*              */
                           unsigned char M10:1;         /*    10mon     */
                           unsigned char M1 :4;         /*     1mon     */
                           }      BIT;                  /*              */
                    }          RMONCNT;                 /*              */
              char             wk7;                     /*              */
              union {                                   /* RYRCNT       */
                    unsigned char BYTE;                 /*  Byte Access */
                    struct {                            /*  Bit  Access */
                           unsigned char Y10:4;         /*    10year    */
                           unsigned char Y1 :4;         /*     1year    */
                           }      BIT;                  /*              */
                    }           RYRCNT;                 /*              */
              char              wk8;                    /*              */
              union {                                   /* RSECAR       */
                    unsigned char BYTE;                 /*  Byte Access */
                    struct {                            /*  Bit  Access */
                           unsigned char ENB:1;         /*    ENB       */
                           unsigned char S10:3;         /*    10sec     */
                           unsigned char S1 :4;         /*     1sec     */
                           }      BIT;                  /*              */
                    }           RSECAR;                 /*              */
              char              wk9;                    /*              */
              union {                                   /* RMINAR       */
                    unsigned char BYTE;                 /*  Byte Access */
                    struct {                            /*  Bit  Access */
                           unsigned char ENB:1;         /*    ENB       */
                           unsigned char M10:3;         /*    10min     */
                           unsigned char M1 :4;         /*     1min     */
                           }      BIT;                  /*              */
                    }           RMINAR;                 /*              */
              char              wk10;                   /*              */
              union {                                   /* RHRAR        */
                    unsigned char BYTE;                 /*  Byte Access */
                    struct {                            /*  Bit  Access */
                           unsigned char ENB:1;         /*    ENB       */
                           unsigned char    :1;         /*              */
                           unsigned char H10:2;         /*    10sec     */
                           unsigned char H1 :4;         /*     1sec     */
                           }      BIT;                  /*              */
                    }           RHRAR;                  /*              */
              char              wk11;                   /*              */
              union {                                   /* RWKAR        */
                    unsigned char BYTE;                 /*  Byte Access */
                    struct {                            /*  Bit  Access */
                           unsigned char ENB:1;         /*    ENB       */
                           unsigned char    :4;         /*              */
                           unsigned char WK :3;         /*    week      */
                           }      BIT;                  /*              */
                    }           RWKAR;                  /*              */
              char              wk12;                   /*              */
              union {                                   /* RDAYAR       */
                    unsigned char BYTE;                 /*  Byte Access */
                    struct {                            /*  Bit  Access */
                           unsigned char ENB:1;         /*    ENB       */
                           unsigned char    :1;         /*              */
                           unsigned char D10:2;         /*    10day     */
                           unsigned char D1 :4;         /*     1day     */
                           }      BIT;                  /*              */
                    }           RDAYAR;                 /*              */
              char              wk13;                   /*              */
              union {                                   /* RMONAR       */
                    unsigned char BYTE;                 /*  Byte Access */
                    struct {                            /*  Bit  Access */
                           unsigned char ENB:1;         /*    ENB       */
                           unsigned char    :2;         /*              */
                           unsigned char M10:1;         /*    10mon     */
                           unsigned char M1 :4;         /*     1mon     */
                           }      BIT;                  /*              */
                    }           RMONAR;                 /*              */
              char              wk14;                   /*              */
              union {                                   /* RCR1         */
                    unsigned char BYTE;                 /*  Byte Access */
                    struct {                            /*  Bit  Access */
                           unsigned char CF :1;         /*    CF        */
                           unsigned char    :2;         /*              */
                           unsigned char CIE:1;         /*    CIE       */
                           unsigned char AIE:1;         /*    AIE       */
                           unsigned char    :2;         /*              */
                           unsigned char AF :1;         /*    AF        */
                           }      BIT;                  /*              */
                    }           RCR1;                   /*              */
              char              wk15;                   /*              */
              union {                                   /* RCR2         */
                    unsigned char BYTE;                 /*  Byte Access */
                    struct {                            /*  Bit  Access */
                           unsigned char PEF  :1;       /*    PEF       */
                           unsigned char PES  :3;       /*    PES       */
                           unsigned char RTCEN:1;       /*    RTCEN     */
                           unsigned char ADJ  :1;       /*    ADJ       */
                           unsigned char RESET:1;       /*    RESET     */
                           unsigned char START:1;       /*    START     */
                           }      BIT;                  /*              */
                    }           RCR2;                   /*              */
};                                                      /*              */
struct st_intc {                                        /* struct INTC  */
               union {                                  /* ICR0         */
                     unsigned short WORD;               /*  Word Access */
                     struct {                           /*  Bit  Access */
                            unsigned short NMIL:1;      /*    NMIL      */
                            unsigned short     :6;      /*              */
                            unsigned short NMIE:1;      /*    NMIE      */
                            }       BIT;                /*              */
                     }          ICR0;                   /*              */
               union {                                  /* IPRA         */
                     unsigned short WORD;               /*  Word Access */
                     struct {                           /*  Bit  Access */
                            unsigned short UU:4;        /*    TMU0      */
                            unsigned short UL:4;        /*    TMU1      */
                            unsigned short LU:4;        /*    TMU2      */
                            unsigned short LL:4;        /*    RTC       */
                            }       BIT;                /*              */
                     }          IPRA;                   /*              */
               union {                                  /* IPRB         */
                     unsigned short WORD;               /*  Word Access */
                     struct {                           /*  Bit  Access */
                            unsigned short UU:4;        /*    WDT       */
                            unsigned short UL:4;        /*    REF       */
                            unsigned short LU:4;        /*    SCI       */
                            }       BIT;                /*              */
                     }          IPRB;                   /*              */
               char             wk[234];                /*              */
               unsigned int     TRA;                    /* TRA          */
               unsigned int     EXPEVT;                 /* EXPEVT       */
               unsigned int     INTEVT;                 /* INTEVT       */
};                                                      /*              */
struct st_int {                                         /* struct INT   */
              unsigned int      INTEVT2;                /* INTEVT2      */
              union {                                   /* IRR0         */
                    unsigned char BYTE;                 /*  Byte Access */
                    struct {                            /*  Bit  Access */
                           unsigned char PINT0R:1;      /*    PINT0R    */
                           unsigned char PINT1R:1;      /*    PINT1R    */
                           unsigned char IRQ5R :1;      /*    IRQ5R     */
                           unsigned char IRQ4R :1;      /*    IRQ4R     */
                           unsigned char IRQ3R :1;      /*    IRQ3R     */
                           unsigned char IRQ2R :1;      /*    IRQ2R     */
                           unsigned char IRQ1R :1;      /*    IRQ1R     */
                           unsigned char IRQ0R :1;      /*    IRQ0R     */
                           }      BIT;                  /*              */
                    }           IRR0;                   /*              */
              char              wk1;                    /*              */
              union {                                   /* IRR1         */
                    unsigned char BYTE;                 /*  Byte Access */
                    struct {                            /*  Bit  Access */
                           unsigned char TXI1R:1;       /*    TXI1R     */
                           unsigned char BRI1R:1;       /*    BRI1R     */
                           unsigned char RXI1R:1;       /*    RXI1R     */
                           unsigned char ERI1R:1;       /*    ERI1R     */
                           unsigned char DEI3R:1;       /*    DEI3R     */
                           unsigned char DEI2R:1;       /*    DEI2R     */
                           unsigned char DEI1R:1;       /*    DEI1R     */
                           unsigned char DEI0R:1;       /*    DEI0R     */
                           }      BIT;                  /*              */
                    }           IRR1;                   /*              */
              char              wk2;                    /*              */
              union {                                   /* IRR2         */
                    unsigned char BYTE;                 /*  Byte Access */
                    struct {                            /*  Bit  Access */
                           unsigned char      :3;       /*              */
                           unsigned char ADIR :1;       /*    ADIR      */
                           unsigned char TXI2R:1;       /*    TXI2R     */
                           unsigned char BRI2R:1;       /*    BRI2R     */
                           unsigned char RXI2R:1;       /*    RXI2R     */
                           unsigned char ERI2R:1;       /*    ERI2R     */
                           }      BIT;                  /*              */
                    }           IRR2;                   /*              */
              char              wk3[7];                 /*              */
              union {                                   /* ICR1         */
                    unsigned short WORD;                /*  Word Access */
                    struct {                            /*  Bit  Access */
                           unsigned short MAI   :1;     /*    MAI       */
                           unsigned short IRQLVL:1;     /*    IRQLVL    */
                           unsigned short BLMSK :1;     /*    BLMSK     */
                           unsigned short IRLSEN:1;     /*    IRLSEN    */
                           unsigned short IRQ5S :2;     /*    IRQ5S     */
                           unsigned short IRQ4S :2;     /*    IRQ4S     */
                           unsigned short IRQ3S :2;     /*    IRQ3S     */
                           unsigned short IRQ2S :2;     /*    IRQ2S     */
                           unsigned short IRQ1S :2;     /*    IRQ1S     */
                           unsigned short IRQ0S :2;     /*    IRQ0S     */
                           }       BIT;                 /*              */
                    }           ICR1;                   /*              */
              union {                                   /* ICR2         */
                    unsigned short WORD;                /*  Word Access */
                    struct {                            /*  Bit  Access */
                           unsigned short INT15S:1;     /*    INT15S    */
                           unsigned short INT14S:1;     /*    INT14S    */
                           unsigned short INT13S:1;     /*    INT13S    */
                           unsigned short INT12S:1;     /*    INT12S    */
                           unsigned short INT11S:1;     /*    INT11S    */
                           unsigned short INT10S:1;     /*    INT10S    */
                           unsigned short INT9S :1;     /*    INT9S     */
                           unsigned short INT8S :1;     /*    INT8S     */
                           unsigned short INT7S :1;     /*    INT7S     */
                           unsigned short INT6S :1;     /*    INT6S     */
                           unsigned short INT5S :1;     /*    INT5S     */
                           unsigned short INT4S :1;     /*    INT4S     */
                           unsigned short INT3S :1;     /*    INT3S     */
                           unsigned short INT2S :1;     /*    INT2S     */
                           unsigned short INT1S :1;     /*    INT1S     */
                           unsigned short INT0S :1;     /*    INT0S     */
                           }       BIT;                 /*              */
                    }           ICR2;                   /*              */
              union {                                   /* PINTER       */
                    unsigned short WORD;                /*  Word Access */
                    struct {                            /*  Bit  Access */
                           unsigned short INT15E:1;     /*    INT15E    */
                           unsigned short INT14E:1;     /*    INT14E    */
                           unsigned short INT13E:1;     /*    INT13E    */
                           unsigned short INT12E:1;     /*    INT12E    */
                           unsigned short INT11E:1;     /*    INT11E    */
                           unsigned short INT10E:1;     /*    INT10E    */
                           unsigned short INT9E :1;     /*    INT9E     */
                           unsigned short INT8E :1;     /*    INT8E     */
                           unsigned short INT7E :1;     /*    INT7E     */
                           unsigned short INT6E :1;     /*    INT6E     */
                           unsigned short INT5E :1;     /*    INT5E     */
                           unsigned short INT4E :1;     /*    INT4E     */
                           unsigned short INT3E :1;     /*    INT3E     */
                           unsigned short INT2E :1;     /*    INT2E     */
                           unsigned short INT1E :1;     /*    INT1E     */
                           unsigned short INT0E :1;     /*    INT0E     */
                           }       BIT;                 /*              */
                    }           PINTER;                 /*              */
              union {                                   /* IPRC         */
                    unsigned short WORD;                /*  Word Access */
                    struct {                            /*  Bit  Access */
                           unsigned short UU:4;         /*    IRQ3      */
                           unsigned short UL:4;         /*    IRQ2      */
                           unsigned short LU:4;         /*    IRQ1      */
                           unsigned short LL:4;         /*    IRQ0      */
                           }       BIT;                 /*              */
                    }           IPRC;                   /*              */
              union {                                   /* IPRD         */
                    unsigned short WORD;                /*  Word Access */
                    struct {                            /*  Bit  Access */
                           unsigned short UU:4;         /*    PINT0-7   */
                           unsigned short UL:4;         /*    PINT8-15  */
                           unsigned short LU:4;         /*    IRQ5      */
                           unsigned short LL:4;         /*    IRQ4      */
                           }       BIT;                 /*              */
                    }           IPRD;                   /*              */
              union {                                   /* IPRE         */
                    unsigned short WORD;                /*  Word Access */
                    struct {                            /*  Bit  Access */
                           unsigned short UU:4;         /*    DMAC      */
                           unsigned short UL:4;         /*    IrDA      */
                           unsigned short LU:4;         /*    SCIF      */
                           unsigned short LL:4;         /*    A/D       */
                           }       BIT;                 /*              */
                    }           IPRE;                   /*              */
};                                                      /*              */
struct st_bsc {                                         /* struct BSC   */
              union {                                   /* MCSCR0       */
                    unsigned short WORD;                /*  Word Access */
                    struct {                            /*  Bit  Access */
                           unsigned short      :9;      /*              */
                           unsigned short CS2_0:1;      /*    CS2/0     */
                           unsigned short CAP  :2;      /*    CAP       */
                           unsigned short A    :4;      /*    A         */
                           }       BIT;                 /*              */
                    }           MCSCR0;                 /*              */
              union {                                   /* MCSCR1       */
                    unsigned short WORD;                /*  Word Access */
                    struct {                            /*  Bit  Access */
                           unsigned short      :9;      /*              */
                           unsigned short CS2_0:1;      /*    CS2/0     */
                           unsigned short CAP  :2;      /*    CAP       */
                           unsigned short A    :4;      /*    A         */
                           }       BIT;                 /*              */
                    }           MCSCR1;                 /*              */
              union {                                   /* MCSCR2       */
                    unsigned short WORD;                /*  Word Access */
                    struct {                            /*  Bit  Access */
                           unsigned short      :9;      /*              */
                           unsigned short CS2_0:1;      /*    CS2/0     */
                           unsigned short CAP  :2;      /*    CAP       */
                           unsigned short A    :4;      /*    A         */
                           }       BIT;                 /*              */
                    }           MCSCR2;                 /*              */
              union {                                   /* MCSCR3       */
                    unsigned short WORD;                /*  Word Access */
                    struct {                            /*  Bit  Access */
                           unsigned short      :9;      /*              */
                           unsigned short CS2_0:1;      /*    CS2/0     */
                           unsigned short CAP  :2;      /*    CAP       */
                           unsigned short A    :4;      /*    A         */
                           }       BIT;                 /*              */
                    }           MCSCR3;                 /*              */
              union {                                   /* MCSCR4       */
                    unsigned short WORD;                /*  Word Access */
                    struct {                            /*  Bit  Access */
                           unsigned short      :9;      /*              */
                           unsigned short CS2_0:1;      /*    CS2/0     */
                           unsigned short CAP  :2;      /*    CAP       */
                           unsigned short A    :4;      /*    A         */
                           }       BIT;                 /*              */
                    }           MCSCR4;                 /*              */
              union {                                   /* MCSCR5       */
                    unsigned short WORD;                /*  Word Access */
                    struct {                            /*  Bit  Access */
                           unsigned short      :9;      /*              */
                           unsigned short CS2_0:1;      /*    CS2/0     */
                           unsigned short CAP  :2;      /*    CAP       */
                           unsigned short A    :4;      /*    A         */
                           }       BIT;                 /*              */
                    }           MCSCR5;                 /*              */
              union {                                   /* MCSCR6       */
                    unsigned short WORD;                /*  Word Access */
                    struct {                            /*  Bit  Access */
                           unsigned short      :9;      /*              */
                           unsigned short CS2_0:1;      /*    CS2/0     */
                           unsigned short CAP  :2;      /*    CAP       */
                           unsigned short A    :4;      /*    A         */
                           }       BIT;                 /*              */
                    }           MCSCR6;                 /*              */
              union {                                   /* MCSCR7       */
                    unsigned short WORD;                /*  Word Access */
                    struct {                            /*  Bit  Access */
                           unsigned short      :9;      /*              */
                           unsigned short CS2_0:1;      /*    CS2/0     */
                           unsigned short CAP  :2;      /*    CAP       */
                           unsigned short A    :4;      /*    A         */
                           }       BIT;                 /*              */
                    }           MCSCR7;                 /*              */
              union {                                   /* BCR1         */
                    unsigned short WORD;                /*  Word Access */
                    struct {                            /*  Bit  Access */
                           unsigned short PULA  :1;     /*    PULA      */
                           unsigned short PULD  :1;     /*    PULD      */
                           unsigned short HIZMEM:1;     /*    HIZMEM    */
                           unsigned short HIZCNT:1;     /*    HIZCNT    */
                           unsigned short ENDIAN:1;     /*    ENDIAN    */
                           unsigned short A0BST :2;     /*    A0BST     */
                           unsigned short A5BST :2;     /*    A5BST     */
                           unsigned short A6BST :2;     /*    A6BST     */
                           unsigned short DRAMTP:3;     /*    DRAMTP    */
                           unsigned short A5PCM :1;     /*    A5PCM     */
                           unsigned short A6PCM :1;     /*    A6PCM     */
                           }       BIT;                 /*              */
                    }           BCR1;                   /*              */
              union {                                   /* BCR2         */
                    unsigned short WORD;                /*  Word Access */
                    struct {                            /*  Bit  Access */
                           unsigned short     :2;       /*              */
                           unsigned short A6SZ:2;       /*    A6SZ      */
                           unsigned short A5SZ:2;       /*    A5SZ      */
                           unsigned short A4SZ:2;       /*    A4SZ      */
                           unsigned short A3SZ:2;       /*    A3SZ      */
                           unsigned short A2SZ:2;       /*    A2SZ      */
                           }       BIT;                 /*              */
                    }           BCR2;                   /*              */
              union {                                   /* WCR1         */
                    unsigned short WORD;                /*  Word Access */
                    struct {                            /*  Bit  Access */
                           unsigned short WAITSEL:1;    /*    WAITSEL   */
                           unsigned short        :1;    /*              */
                           unsigned short A6IW   :2;    /*    A6IW      */
                           unsigned short A5IW   :2;    /*    A5IW      */
                           unsigned short A4IW   :2;    /*    A4IW      */
                           unsigned short A3IW   :2;    /*    A3IW      */
                           unsigned short A2IW   :2;    /*    A2IW      */
                           unsigned short        :2;    /*              */
                           unsigned short A0IW   :2;    /*    A0IW      */
                           }       BIT;                 /*              */
                    }           WCR1;                   /*              */
              union {                                   /* WCR2         */
                    unsigned short WORD;                /*  Word Access */
                    struct {                            /*  Bit  Access */
                           unsigned short A6W:3;        /*    A6W       */
                           unsigned short A5W:3;        /*    A5W       */
                           unsigned short A4W:3;        /*    A4W       */
                           unsigned short A3W:2;        /*    A3W       */
                           unsigned short A2W:2;        /*    A2W       */
                           unsigned short A0W:3;        /*    A0W       */
                           }       BIT;                 /*              */
                    }           WCR2;                   /*              */
              union {                                   /* MCR          */
                    unsigned short WORD;                /*  Word Access */
                    struct {                            /*  Bit  Access */
                           unsigned short TPC    :2;    /*    TPC       */
                           unsigned short RCD    :2;    /*    RCD       */
                           unsigned short TRWL   :2;    /*    TRWL      */
                           unsigned short TRAS   :2;    /*    TRAS      */
                           unsigned short RASD   :1;    /*    RASD      */
                           unsigned short BE     :1;    /*    BE        */
                           unsigned short AMX    :3;    /*    AMX       */
                           unsigned short RFSH   :1;    /*    RFSH      */
                           unsigned short RMODE  :1;    /*    RMODE     */
                           unsigned short EDOMODE:1;    /*    EDOMODE   */
                           }       BIT;                 /*              */
                    }           MCR;                    /*              */
              union {                                   /* DCR          */
                    unsigned short WORD;                /*  Word Access */
                    struct {                            /*  Bit  Access */
                           unsigned short TPC  :2;      /*    TPC       */
                           unsigned short RCD  :2;      /*    RCD       */
                           unsigned short      :2;      /*              */
                           unsigned short TRAS :2;      /*    TRAS      */
                           unsigned short      :1;      /*              */
                           unsigned short BE   :1;      /*    BE        */
                           unsigned short      :1;      /*              */
                           unsigned short AMX  :2;      /*    AMX       */
                           unsigned short RFSH :1;      /*    RFSH      */
                           unsigned short RMODE:1;      /*    RMODE     */
                           }       BIT;                 /*              */
                    }           DCR;                    /*              */
              union {                                   /* PCR          */
                    unsigned short WORD;                /*  Word Access */
                    struct {                            /*  Bit  Access */
                           unsigned short A6W3  :1;     /*    A6W3      */
                           unsigned short A5W3  :1;     /*    A5W3      */
                           unsigned short       :2;     /*              */
                           unsigned short A5TED2:1;     /*    A5TED2    */
                           unsigned short A6TED2:1;     /*    A6TED2    */
                           unsigned short A5TEH2:1;     /*    A5TEH2    */
                           unsigned short A6TEH2:1;     /*    A6TEH2    */
                           unsigned short A5TED1:1;     /*    A5TED1    */
                           unsigned short A5TED0:1;     /*    A5TED0    */
                           unsigned short A6TED1:1;     /*    A6TED1    */
                           unsigned short A6TED0:1;     /*    A6TED0    */
                           unsigned short A5TEH1:1;     /*    A5TEH1    */
                           unsigned short A5TEH0:1;     /*    A5TEH0    */
                           unsigned short A6TEH1:1;     /*    A6TEH1    */
                           unsigned short A6TEH0:1;     /*    A6TEH0    */
                           }       BIT;                 /*              */
                    }           PCR;                    /*              */
              union {                                   /* RTCSR        */
                    unsigned short WORD;                /*  Word Access */
                    struct {                            /*  Bit  Access */
                           unsigned short     :8;       /*              */
                           unsigned short CMF :1;       /*    CMF       */
                           unsigned short CMIE:1;       /*    CMIE      */
                           unsigned short CKS :3;       /*    CKS       */
                           unsigned short OVF :1;       /*    OVF       */
                           unsigned short OVIE:1;       /*    OVIE      */
                           unsigned short LMTS:1;       /*    LMTS      */
                           }       BIT;                 /*              */
                    }           RTCSR;                  /*              */
              unsigned short    RTCNT;                  /* RTCNT        */
              unsigned short    RTCOR;                  /* RTCOR        */
              unsigned short    RFCR;                   /* RFCR         */
              char              wk[8];                  /*              */
              union {                                   /* BCR3         */
                    unsigned short WORD;                /*  Word Access */
                    struct {                            /*  Bit  Access */
                           unsigned short EXTEND:1;     /*    EXTEND    */
                           unsigned short       :1;     /*              */
                           unsigned short TPC3  :2;     /*    TPC3      */
                           unsigned short RCD3  :2;     /*    RCD3      */
                           unsigned short TRAS3 :2;     /*    TRAS3     */
                           unsigned short       :2;     /*              */
                           unsigned short TPC2  :2;     /*    TPC2      */
                           unsigned short RCD2  :2;     /*    RCD2      */
                           unsigned short TRAS2 :2;     /*    TRAS2     */
                           }       BIT;                 /*              */
                    }           BCR3;                   /*              */
};                                                      /*              */
struct st_cpg {                                         /* struct CPG   */
              union {                                   /* FRQCR        */
                    unsigned short WORD;                /*  Word Access */
                    struct {                            /*  Bit  Access */
                           unsigned short STC2  :1;     /*    STC2      */
                           unsigned short IFC2  :1;     /*    IFC2      */
                           unsigned short PFC2  :1;     /*    PFC2      */
                           unsigned short       :3;     /*              */
                           unsigned short SLPFRQ:1;     /*    SLPFRQ    */
                           unsigned short CKOEN :1;     /*    CKOEN     */
                           unsigned short PLLEN :1;     /*    PLLEN     */
                           unsigned short PSTBY :1;     /*    PSTBY     */
                           unsigned short STC   :2;     /*    STC       */
                           unsigned short IFC   :2;     /*    IFC       */
                           unsigned short PFC   :2;     /*    PFC       */
                           }       BIT;                 /*              */
                    }           FRQCR;                  /*              */
              union {                                   /* STBCR        */
                    unsigned char BYTE;                 /*  Byte Access */
                    struct {                            /*  Bit  Access */
                           unsigned char STBY :1;       /*    STBY      */
                           unsigned char      :4;       /*              */
                           unsigned char MSTP2:1;       /*    TMU       */
                           unsigned char MSTP1:1;       /*    RTC       */
                           unsigned char MSTP0:1;       /*    SCI       */
                           }      BIT;                  /*              */
                    }           STBCR;                  /*              */
              char              wk;                     /*              */
              unsigned short    WTCNT;                  /* WTCNT        */
              union {                                   /* WTCSR        */
                    unsigned short WORD;                /*  Word Access */
                    struct {                            /*  Bit  Access */
                           unsigned char TME :1;        /*    TME       */
                           unsigned char WTIT:1;        /*    WTIT      */
                           unsigned char RSTS:1;        /*    RSTS      */
                           unsigned char WOVF:1;        /*    WOVF      */
                           unsigned char IOVF:1;        /*    IOVF      */
                           unsigned char CKS :3;        /*    CKS       */
                           }       BIT;                 /*              */
                    }           WTCSR;                  /*              */
              union {                                   /* STBCR2       */
                    unsigned char BYTE;                 /*  Byte Access */
                    struct {                            /*  Bit  Access */
                           unsigned char      :1;       /*              */
                           unsigned char MDCHG:1;       /*    MDCHG     */
                           unsigned char MSTP8:1;       /*    UBC       */
                           unsigned char MSTP7:1;       /*    DMAC      */
                           unsigned char MSTP6:1;       /*    DAC       */
                           unsigned char MSTP5:1;       /*    ADC       */
                           unsigned char MSTP4:1;       /*    SCIF      */
                           unsigned char MSTP3:1;       /*    IrDA      */
                           }      BIT;                  /*              */
                    }           STBCR2;                 /*              */
};                                                      /*              */
struct st_ubc {                                         /* struct UBC   */
              unsigned int      BDRB;                   /* BDRB         */
              unsigned int      BDMRB;                  /* BDMRB        */
              union {                                   /* BRCR         */
                    unsigned int LONG;                  /*  Long Access */
                    struct {                            /*  Bit  Access */
                           unsigned short       :10;    /*              */
                           unsigned short BASMA : 1;    /*    BASMA     */
                           unsigned short BASMB : 1;    /*    BASMB     */
                           unsigned short       : 4;    /*              */
                           unsigned short SCMFCA: 1;    /*    SCMCA     */
                           unsigned short SCMFCB: 1;    /*    SCMCB     */
                           unsigned short SCMFDA: 1;    /*    SCMDA     */
                           unsigned short SCMFDB: 1;    /*    SCMDB     */
                           unsigned short PCTE  : 1;    /*    PCTE      */
                           unsigned short PCBA  : 1;    /*    PCTA      */
                           unsigned short       : 2;    /*              */
                           unsigned short DBEB  : 1;    /*    DBEB      */
                           unsigned short PCBB  : 1;    /*    PCBB      */
                           unsigned short       : 2;    /*              */
                           unsigned short SEQ   : 1;    /*    SEQ       */
                           unsigned short       : 2;    /*              */
                           unsigned short ETBE  : 1;    /*    ETBE      */
                           }     BIT;                   /*              */
                    }           BRCR;                   /*              */
              unsigned short    BETR;                   /* BETR         */
              char              wk1[2];                 /*              */
              void             *BARB;                   /* BARB         */
              unsigned int      BAMRB;                  /* BAMRB        */
              union {                                   /* BBRB         */
                    unsigned short WORD;                /*  Word Access */
                    struct {                            /*  Bit  Access */
                           unsigned short    :6;        /*              */
                           unsigned short XYE:1;        /*    XYE       */
                           unsigned short XYS:1;        /*    XYS       */
                           unsigned short CDB:2;        /*    CDB       */
                           unsigned short IDB:2;        /*    IDB       */
                           unsigned short RWB:2;        /*    RWB       */
                           unsigned short SZB:2;        /*    SZB       */
                           }       BIT;                 /*              */
                    }           BBRB;                   /*              */
              char              wk2[2];                 /*              */
              union {                                   /* BRSR         */
                    unsigned int LONG;                  /*  Long Access */
                    struct {                            /*  Bit  Access */
                           unsigned int SVF: 1;         /*    SVF       */
                           unsigned int PID: 3;         /*    PID       */
                           unsigned int BSA:28;         /*    BSA       */
                           }     BIT;                   /*              */
                    }           BRSR;                   /*              */
              void             *BARA;                   /* BARA         */
              unsigned int      BAMRA;                  /* BAMRA        */
              union {                                   /* BBRA         */
                    unsigned short WORD;                /*  Word Access */
                    struct {                            /*  Bit  Access */
                           unsigned short    :8;        /*              */
                           unsigned short CDA:2;        /*    CDA       */
                           unsigned short IDA:2;        /*    IDA       */
                           unsigned short RWA:2;        /*    RWA       */
                           unsigned short SZA:2;        /*    SZA       */
                           }       BIT;                 /*              */
                    }           BBRA;                   /*              */
              char              wk3[2];                 /*              */
              union {                                   /* BRDR         */
                    unsigned int LONG;                  /*  Long Access */
                    struct {                            /*  Bit  Access */
                           unsigned int DVF: 1;         /*    DVF       */
                           unsigned int    : 3;         /*              */
                           unsigned int BDA:28;         /*    BDA       */
                           }     BIT;                   /*              */
                    }           BRDR;                   /*              */
              char              wk4[36];                /*              */
              unsigned char     BASRA;                  /* BASRA        */
              char              wk5[3];                 /*              */
              unsigned char     BASRB;                  /* BASRB        */
};                                                      /*              */
struct st_mmu {                                         /* struct MMU   */
              unsigned int      MMUCR;                  /* MMUCR        */
              char              wk[12];                 /*              */
              unsigned int      PTEH;                   /* PTEH         */
              unsigned int      PTEL;                   /* PTEL         */
              unsigned int      TTB;                    /* TTB          */
              unsigned int      TEA;                    /* TEA          */
};                                                      /*              */
union un_ccr {                                          /* union CCR    */
             unsigned int LONG;                         /*  Long Access */
             struct {                                   /*  Bit  Access */
                    unsigned int   :28;                 /*              */
                    unsigned int CF: 1;                 /*    CF        */
                    unsigned int CB: 1;                 /*    CB        */
                    unsigned int WT: 1;                 /*    WT        */
                    unsigned int CE: 1;                 /*    CE        */
                    }     BIT;                          /*              */
};                                                      /*              */
union un_ccr2 {                                         /* union CCR2   */
              unsigned int LONG;                        /*  Long Access */
              struct {                                  /*  Bit  Access */
                     unsigned int       :22;            /*              */
                     unsigned int W3LOAD: 1;            /*    W3LOAD    */
                     unsigned int W3LOCK: 1;            /*    W3LOCK    */
                     unsigned int       : 6;            /*              */
                     unsigned int W2LOAD: 1;            /*    W2LOAD    */
                     unsigned int W2LOCK: 1;            /*    W2LOCK    */
                     }     BIT;                         /*              */
};                                                      /*              */
struct st_dmac {                                        /* struct DMAC  */
               union {                                  /* DMAOR        */
                     unsigned short WORD;               /*  Word Access */
                     struct {                           /*  Bit  Access */
                            unsigned char     :6;       /*              */
                            unsigned char PR  :2;       /*    PR        */
                            unsigned char     :5;       /*              */
                            unsigned char AE  :1;       /*    AE        */
                            unsigned char NMIF:1;       /*    NMIF      */
                            unsigned char DME :1;       /*    DME       */
                            }       BIT;                /*              */
                     }          DMAOR;                  /*              */
};                                                      /*              */
struct st_dmac0 {                                       /* struct DMAC0 */
                void           *SAR;                    /* SAR          */
                void           *DAR;                    /* DAR          */
                unsigned int    DMATCR;                 /* DMATCR       */
                union {                                 /* CHCR         */
                      unsigned int LONG;                /*  Long Access */
                      struct {                          /*  Word Access */
                             unsigned short H;          /*    High Byte */
                             unsigned short L;          /*    Low  Byte */
                             }     WORD;                /*              */
                      struct {                          /*  Bit  Access */
                             unsigned char   :8;        /*              */
                             unsigned char   :3;        /*              */
                             unsigned char DI:1;        /*    DI        */
                             unsigned char RO:1;        /*    RO        */
                             unsigned char RL:1;        /*    RL        */
                             unsigned char AM:1;        /*    AM        */
                             unsigned char AL:1;        /*    AL        */
                             unsigned char DM:2;        /*    DM        */
                             unsigned char SM:2;        /*    SM        */
                             unsigned char RS:4;        /*    RS        */
                             unsigned char   :1;        /*              */
                             unsigned char DS:1;        /*    DS        */
                             unsigned char TM:1;        /*    TM        */
                             unsigned char TS:2;        /*    TS        */
                             unsigned char IE:1;        /*    IE        */
                             unsigned char TE:1;        /*    TE        */
                             unsigned char DE:1;        /*    DE        */
                             }     BIT;                 /*              */
                      }         CHCR;                   /*              */
};                                                      /*              */
struct st_cmt {                                         /* struct CMT   */
              union {                                   /* CMSTR        */
                    unsigned short WORD;                /*  Word Access */
                    struct {                            /*  Bit  Access */
                           unsigned char    :8;         /*              */
                           unsigned char    :7;         /*              */
                           unsigned char STR:1;         /*    STR       */
                           }       BIT;                 /*              */
                    }           CMSTR;                  /*              */
              union {                                   /* CMCSR        */
                    unsigned short WORD;                /*  Word Access */
                    struct {                            /*  Bit  Access */
                           unsigned char    :8;         /*              */
                           unsigned char CMF:1;         /*    CMF       */
                           unsigned char    :5;         /*              */
                           unsigned char CKS:2;         /*    CKS       */
                           }       BIT;                 /*              */
                    }           CMCSR;                  /*              */
              unsigned short    CMCNT;                  /* CMCNT        */
              unsigned short    CMCOR;                  /* CMCOR        */
};                                                      /*              */
struct st_ad {                                          /* struct A/D   */
             unsigned char      ADDRAH;                 /* ADDRAH       */
             char               wk1;                    /*              */
             unsigned char      ADDRAL;                 /* ADDRAL       */
             char               wk2;                    /*              */
             unsigned char      ADDRBH;                 /* ADDRBH       */
             char               wk3;                    /*              */
             unsigned char      ADDRBL;                 /* ADDRBL       */
             char               wk4;                    /*              */
             unsigned char      ADDRCH;                 /* ADDRCH       */
             char               wk5;                    /*              */
             unsigned char      ADDRCL;                 /* ADDRCL       */
             char               wk6;                    /*              */
             unsigned char      ADDRDH;                 /* ADDRDH       */
             char               wk7;                    /*              */
             unsigned char      ADDRDL;                 /* ADDRDL       */
             char               wk8;                    /*              */
             union {                                    /* ADCSR        */
                   unsigned char BYTE;                  /*  Byte Access */
                   struct {                             /*  Bit  Access */
                          unsigned char ADF  :1;        /*    ADF       */
                          unsigned char ADIE :1;        /*    ADIE      */
                          unsigned char ADST :1;        /*    ADST      */
                          unsigned char MULTI:1;        /*    MULTI     */
                          unsigned char CKS  :1;        /*    CKS       */
                          unsigned char CH   :3;        /*    CH        */
                          }      BIT;                   /*              */
                   }            ADCSR;                  /*              */
             char               wk9;                    /*              */
             union {                                    /* ADCR         */
                   unsigned char BYTE;                  /*  Byte Access */
                   struct {                             /*  Bit  Access */
                          unsigned char TRGE:2;         /*    TRGE      */
                          unsigned char SCN :1;         /*    SCN       */
                          }      BIT;                   /*              */
                   }            ADCR;                   /*              */
};                                                      /*              */
struct st_da {                                          /* struct D/A   */
             unsigned char      DADR0;                  /* DADR0        */
             char               wk1;                    /*              */
             unsigned char      DADR1;                  /* DADR1        */
             char               wk2;                    /*              */
             union {                                    /* DACR         */
                   unsigned char BYTE;                  /*  Byte Access */
                   struct {                             /*  Bit  Access */
                          unsigned char DAOE:2;         /*    DAOE      */
                          unsigned char DAE :1;         /*    DAE       */
                          }      BIT;                   /*              */
                   }            DACR;                   /*              */
};                                                      /*              */
struct st_port {                                        /* struct PORT  */
               union {                                  /* CR           */
                     unsigned short WORD;               /*  Word Access */
                     struct {                           /*  Bit  Access */
                            unsigned short P7MD:2;      /*    P7MD      */
                            unsigned short P6MD:2;      /*    P6MD      */
                            unsigned short P5MD:2;      /*    P5MD      */
                            unsigned short P4MD:2;      /*    P4MD      */
                            unsigned short P3MD:2;      /*    P3MD      */
                            unsigned short P2MD:2;      /*    P2MD      */
                            unsigned short P1MD:2;      /*    P1MD      */
                            unsigned short P0MD:2;      /*    P0MD      */
                            }       BIT;                /*              */
                     }          CR;                     /*              */
               char             wk[30];                 /*              */
               union {                                  /*              */
                     unsigned char BYTE;                /*  Byte Access */
                     struct {                           /*  Bit  Access */
                            unsigned char P7DT:1;       /*    Bit 7     */
                            unsigned char P6DT:1;       /*    Bit 6     */
                            unsigned char P5DT:1;       /*    Bit 5     */
                            unsigned char P4DT:1;       /*    Bit 4     */
                            unsigned char P3DT:1;       /*    Bit 3     */
                            unsigned char P2DT:1;       /*    Bit 2     */
                            unsigned char P1DT:1;       /*    Bit 1     */
                            unsigned char P0DT:1;       /*    Bit 0     */
                            }      BIT;                 /*              */
                     }          DR;                     /*              */
};                                                      /*              */
#define SCI   (*(volatile struct st_sci   *)0xFFFFFE80) /* SCI   Address*/
#define SCIF  (*(volatile struct st_scif  *)0xA4000150) /* SCIF  Address*/
#define IRDA  (*(volatile struct st_irda  *)0xA4000140) /* IrDA  Address*/
#define TMU   (*(volatile struct st_tmu   *)0xFFFFFE90) /* TMU   Address*/
#define TMU0  (*(volatile struct st_tmu0  *)0xFFFFFE94) /* TMU0  Address*/
#define TMU1  (*(volatile struct st_tmu0  *)0xFFFFFEA0) /* TMU1  Address*/
#define TMU2  (*(volatile struct st_tmu2  *)0xFFFFFEAC) /* TMU2  Address*/
#define RTC   (*(volatile struct st_rtc   *)0xFFFFFEC0) /* RTC   Address*/
#define INTC  (*(volatile struct st_intc  *)0xFFFFFEE0) /* INTC  Address*/
#define BSC   (*(volatile struct st_bsc   *)0xFFFFFF50) /* BSC   Address*/
#define CPG   (*(volatile struct st_cpg   *)0xFFFFFF80) /* CPG   Address*/
#define UBC   (*(volatile struct st_ubc   *)0xFFFFFF90) /* UBC   Address*/
#define MMU   (*(volatile struct st_mmu   *)0xFFFFFFE0) /* MMU   Address*/
#define CCR   (*(volatile union  un_ccr   *)0xFFFFFFEC) /* CCR   Address*/
#define CCR2  (*(volatile union  un_ccr2  *)0xA40000B0) /* CCR2  Address*/
#define DMAC  (*(volatile struct st_dmac  *)0xA4000060) /* DMAC  Address*/
#define DMAC0 (*(volatile struct st_dmac0 *)0xA4000020) /* DMAC0 Address*/
#define DMAC1 (*(volatile struct st_dmac0 *)0xA4000030) /* DMAC1 Address*/
#define DMAC2 (*(volatile struct st_dmac0 *)0xA4000040) /* DMAC2 Address*/
#define DMAC3 (*(volatile struct st_dmac0 *)0xA4000050) /* DMAC3 Address*/
#define CMT   (*(volatile struct st_cmt   *)0xA4000070) /* CMT   Address*/
#define AD    (*(volatile struct st_ad    *)0xA4000080) /* AD    Address*/
#define DA    (*(volatile struct st_da    *)0xA40000A0) /* DA    Address*/
#define PA    (*(volatile struct st_port  *)0xA4000100) /* PA    Address*/
#define PB    (*(volatile struct st_port  *)0xA4000102) /* PB    Address*/
#define PC    (*(volatile struct st_port  *)0xA4000104) /* PC    Address*/
#define PD    (*(volatile struct st_port  *)0xA4000106) /* PD    Address*/
#define PE    (*(volatile struct st_port  *)0xA4000108) /* PE    Address*/
#define PF    (*(volatile struct st_port  *)0xA400010A) /* PF    Address*/
#define PG    (*(volatile struct st_port  *)0xA400010C) /* PG    Address*/
#define PH    (*(volatile struct st_port  *)0xA400010E) /* PH    Address*/
#define PJ    (*(volatile struct st_port  *)0xA4000110) /* PJ    Address*/
#define PK    (*(volatile struct st_port  *)0xA4000112) /* PK    Address*/
#define PL    (*(volatile struct st_port  *)0xA4000114) /* PL    Address*/
#define SCP   (*(volatile struct st_port  *)0xA4000116) /* SCP   Address*/
#define INT   (*(volatile struct st_int   *)0xA4000000) /* INT   Address*/
#define st_tmu1  st_mtu0                        /* Change Struct TMU1   */
#define st_dmac1 st_dmac0                       /* Change Struct DMAC1  */
#define st_dmac2 st_dmac0                       /* Change Struct DMAC2  */
#define st_dmac3 st_dmac0                       /* Change Struct DMAC3  */

#endif
