/*=============================================================*/
/*  KD Line Printer Controller Firmware V2.2                   */
/*  TITLE    : m_define.h                                      */
/*  ABSTRACT : Master Define Header File                       */
/*  AUTHOR(S): Jung-Wook Shin                                  */
/*  DATE     : 1999. 1.                                        */
/*  Copyright (c) 1996-1999  by  Jung-Wook Shin                */
/*  Printer Lab. Phoenix Information Technology                */
/*  All rights reserved.                                       */
/*=============================================================*/

/*---------------------------------------------- Serial Definition -*/
#define M_6850CS    *(unsigned char *)  0x200001
#define ACIA        *(unsigned char *)  0x200001
#define ACIACR      *(unsigned char *)  0x200001
#define ACIASR      *(unsigned char *)  0x200001
#define ACIADR      *(unsigned char *)  0x200003

/*-------------------------------------------- Parallel Definition -*/
#define M_6821CS    *(unsigned char *)  0x180001
#define M_PORTCS    *(unsigned char *)  0x300007
#define P_RD_FIFO   *(unsigned char *)  0x30000B

/*------------------------------------------------------------------*/
#define TEST        *(unsigned char *)  0x30000B
#define M_ACK       *(unsigned char *)  0x300001
#define S_M_READ    *(unsigned char *)  0x300009
#define RD_FIFOFULL *(unsigned char *)  0x300003
#define WR_FIFO     *(unsigned char *)  0x300005
#define S_M_READ    *(unsigned char *)  0x300009
#define M_BRATE     *(unsigned char *)  0x30000F

/*------------------------------------------------------------------*/
#define DSLB00      *(unsigned char *)  0x280001
#define DSLC00      *(unsigned char *)  0x30000D

/*---------------------------------------------------------- SHIFT -*/
#define DSLB0       *(unsigned char *)  0x280001
#define DSLB1       *(unsigned char *)  0x280003
#define DSLB2       *(unsigned char *)  0x280005
#define DSLB3       *(unsigned char *)  0x280007
#define DSLB4       *(unsigned char *)  0x280009
#define DSLB5       *(unsigned char *)  0x28000B
#define DSLB6       *(unsigned char *)  0x28000D
#define DSLB7       *(unsigned char *)  0x28000F

/*------------------------------------------------------------------*/
#define STX             2
#define ETX             3
#define START           5
#define SendFIFO(a)     while((RD_FIFOFULL&0x01)==0);WR_FIFO=(unsigned char)a

/*------------------------------------------------------------------*/
#define INT_DIS         asm(" MOVE.W #$2700,SR ")
#define INT_ENB         asm(" MOVE.W #$2000,SR ")

/*------------------------------------------------------------------*/
#define MAX_HBUFF       5000
#define XON             0x11
#define XOFF            0x13
#define P_LIVE          500
#define P_DEAD          4500
#define N_DEAD          500
#define N_LIVE          4500

/*------------------------------------------------------------------*/
#define NORMAL_MODE     0
#define HEXDUMP_MODE    1
#define SELF_TEST_MODE  2

/*-------------------------------------------- Type Definition -*/
typedef unsigned char           u_char;
typedef unsigned int            u_int;

/*------------------------------- Character Image Control Flag -*/
#define GetDim3(a,b,c)          ((a<<2)|(b<<1)|c)
#define SM_NORMAL               0
#define SM_HTDOUBLE             1
#define SM_VTDOUBLE             2
#define SM_HTVTDOUBLE           3
#define SM_HTCONDENSE           4
#define SM_VTDOUBLE_HTCONDENSE  5

/*----------------- Character Image and Character String Image -*/
#define CH_IMG_PART0_BASE       0
#define CH_IMG_PART1_BASE       144

#define ST_IMG_PART0_BASE       0
#define ST_IMG_PART1_BASE       7344
#define SINGLE_BUFF             24
#define DOUBLE_BUFF             48

/*------------------------- ESC or Panel function Setting Flag -*/
#define KORENG_MODE             0
#define ONLY_ENGLISH_MODE       1
#define SP_NORMAL               0
#define COPY                    1
#define SP_300LPM               2
#define SP_410LPM               3
#define PARALLEL_PORT           0
#define SERIAL_PORT             1
#define NOT_BITIMG              0
#define BITIMG_8                1
#define BITIMG_24               2
#define MYUNGJO                 0
#define GODIC                   1
#define ENG1FONT                0
#define ENG2FONT                1
#define OCRFONT                 2
#define FONT410                 3
#define SEMI_EXPAND             1



/*-------------------------------------Panel Flag Setting Define -*/
#define EMUL                    0
#define CH_PITCH                1
#define LINE_SPACE              2
#define PRT_MODE                3
#define AUTOWRAP                4
#define HAN_STYLE               5
#define HAN_FON                 6
#define ENG_FON                 7
#define PAGE_LEN                8
#define B_RATE                  9
#define PARITY                  10
#define DATA_LEN                11
#define STOP_BIT                12
#define PROTOCOL                13
#define HOST_MODE               14
#define TIMEOUT_MODE            15

#define XON_MODE                0
#define DTR_MODE                1

#define KS                      0
#define KSSM                    1
#define TG                      2
#define HEXDUMP_N               3
#define HEXDUMP_W               4

#define CPI10_2_1               0
#define CPI12_2_1               1
#define CPI10_1_1               2
#define CPI13_2_1               3
#define CPI10_3_2               4
#define CPI15_2_1               5

#define LPI_6                   0
#define LPI_8                   1

#define NORMAL                  0
#define COPY                    1
#define HAN300LPM               2
#define ENG410LPM               3

#define ON                      0
#define OFF                     1

#define BYTE_2_WAN              0
#define BYTE_2_JOH              1
#define BYTE_3_JOH              2
#define BYTE_N_JOH              3

#define PRO_ENG                 0
#define OCR_B                   1
#define OCR_B_1                 2

#define INCH7                   0
#define INCH7_5                 1
#define INCH8                   2
#define INCH8_5                 3
#define INCH9                   4
#define INCH9_5                 5
#define INCH11                  6
#define INCH11_5                7
#define INCH12                  8
#define INCH14                  9

#define BPS_300                 0
#define BPS_600                 1
#define BPS_1200                2
#define BPS_2400                3
#define BPS_4800                4
#define BPS_9600                5
#define BPS_19200               6
#define BPS_38400               7

#define NON                     0
#define ODD                     1
#define EVEN                    2

#define BIT_8                   0
#define BIT_7                   1

#define STOP_1                  0
#define STOP_2                  1

#define XON_OFF                 0
#define DTR                     1

#define SERIAL_MODE             0
#define PARALLEL_MODE           1

#define ON                      0
#define OFF                     1

/*--------------------------------------- Program Setting Flag -*/
#define EMPTY                   1
#define NOTEMPTY                0
#define SET                     1
#define RESET                   0
#define CMD_WEIGHT              0x20

/*----------------------------------------------- Font Address -*/
#define FONT_ENG1_ADR           0x80000
#define FONT_ENG2_ADR           0x80D80
#define FONT_OCR_ADR            0x81C20
#define FONT_SEMI1_ADR          0x829A0
#define FONT_SEMI2_ADR          0x83BA0
#define FONT_SP_ADR             0x84D58
#define FONT_410_ADR            0xED8C0
#define FONT_CHA_ADR            0x10000
#define FONT_MKOR_ADR           0x9AE98
#define FONT_GKOR_ADR           0xC43D0

#define ENG_START_CODE          0x20
#define SEMI_START_CODE         0x80
#define SP_START_CODE           0xA1A0
#define CHA_START_CODE          0xCAA0
#define KOR_START_CODE          0xB0A0

/*-------------------------------------------------------------*/
#define MAX_LF_RANGE            100

/*-------------------------------------------------------------*/
#define PAPER_DOT_WIDTH         2448
#define OVER_RANGE              -1


/*-------------------------------------------------------------*/
#define STIMG_SWAP              1
#define STIMG_NOSWAP            0

/*--------------------------------------- KS Control Code Define -*/
#define BEL                     0x07
#define HT                      0x09
#define LF                      0x0A
#define VT                      0x0B
#define FF                      0x0C
#define CR                      0x0D
#define SO                      0x0E
#define SI                      0x0F
#define DC2                     0x12
#define DC4                     0x14
#define CAN                     0x18
#define ESC                     0x1B

/*---------------------------------- Kssm Control Code Define -*/
#define BEL_KM                  0x07
#define BS_KM                   0x08
#define HT_KM                   0x09
#define LF_KM                   0x0A
#define VT_KM                   0x0B
#define FF_KM                   0x0C
#define CR_KM                   0x0D
#define SO_KM                   0x0E
#define SI_KM                   0x0F
#define DC1_KM                  0x11
#define DC2_KM                  0x12
#define DC3_KM                  0x13
#define DC4_KM                  0x14
#define CAN_KM                  0x18
#define ESC_KM                  0x1B
#define FS                      0x1C
#define DEL_KM                  0x7F

/*---------------------------------- Tg Control Code Define ---*/
#define BEL_TG                  0x07
#define BS_TG                   0x08
#define HT_TG                   0x09
#define LF_TG                   0x0A
#define VT_TG                   0x0B
#define FF_TG                   0x0C
#define CR_TG                   0x0D
#define SO_TG                   0x0E
#define SI_TG                   0x0F
#define DC2_TG                  0x12
#define DC4_TG                  0x14
#define CAN_TG                  0x18
#define ESC_TG                  0x1B

/*------------------------------------------- ESC KS Code Define -*/
#define ESC_AST                 0x2A
#define ESC_UL                  0x2D
#define ESC_0                   0x30
#define ESC_1                   0x31
#define ESC_2                   0x32
#define ESC_3                   0x33
#define ESC_6                   0x36
#define ESC_7                   0x37
#define ESC_A                   0x41
#define ESC_C                   0x43
#define ESC_D                   0x44
#define ESC_E                   0x45
#define ESC_F                   0x46
#define ESC_G                   0x47
#define ESC_H                   0x48
#define ESC_J                   0x4A
#define ESC_K                   0x4B
#define ESC_L                   0x4C
#define ESC_S                   0x53
#define ESC_T                   0x54
#define ESC_U                   0x55
#define ESC_W                   0x57
#define ESC_c                   0x63
#define ESC_d                   0x64
#define ESC_h                   0x68
#define ESC_i                   0x69
#define ESC_j                   0x6A
#define ESC_n                   0x6E
#define ESC_q                   0x71
#define ESC_m                   0x6D
#define ESC_r                   0x72
#define ESC_s                   0x73
#define ESC_t                   0x74
#define ESC_u                   0x75
#define ESC_v                   0x76
#define ESC_w                   0x77
#define ESC_x                   0x78
#define ESC_y                   0x79
#define ESC_z                   0x7A
#define ESC_HEAD                0x3C

/*-------------------------------------- Kssm Esc Code Define -*/
#define ESCKM_A                 0x41
#define ESCKM_a                 0x61
#define ESCKM_B                 0x42
#define ESCKM_b                 0x62
#define ESCKM_C                 0x43
#define ESCKM_D                 0x44
#define ESCKM_d                 0x64
#define ESCKM_E                 0x45
#define ESCKM_EM                0x19
#define ESCKM_F                 0x46
#define ESCKM_G                 0x47
#define ESCKM_g                 0x67
#define ESCKM_H                 0x48
#define ESCKM_J                 0x4A
#define ESCKM_K                 0x4B
#define ESCKM_k                 0x6B
#define ESCKM_L                 0x4C
#define ESCKM_l                 0x6C
#define ESCKM_M                 0x6D
#define ESCKM_N                 0x4E
#define ESCKM_O                 0x4F
#define ESCKM_P                 0x50
#define ESCKM_p                 0x70
#define ESCKM_Q                 0x51
#define ESCKM_q                 0x71
#define ESCKM_R                 0x52
#define ESCKM_r                 0x72
#define ESCKM_S                 0x53
#define ESCKM_SI                0x0F
#define ESCKM_SO                0x0E
#define ESCKM_SP                0x20
#define ESCKM_T                 0x54
#define ESCKM_t                 0x74
#define ESCKM_U                 0x55
#define ESCKM_W                 0x57
#define ESCKM_w                 0x77
#define ESCKM_x                 0x78
#define ESCKM_Y                 0x59
#define ESCKM_Z                 0x5A
#define ESCKM_0                 0x30
#define ESCKM_1                 0x31
#define ESCKM_2                 0x32
#define ESCKM_3                 0x33
#define ESCKM_4                 0x34
#define ESCKM_5                 0x35
#define ESCKM_6                 0x36
#define ESCKM_7                 0x37
#define ESCKM_ECM               0x21
#define ESCKM_UL                0x2D
#define ESCKM_CLN               0x3A
#define ESCKM_EMP               0x26
#define ESCKM_PST               0x25
#define ESCKM_SLH               0x2F
#define ESCKM_DLR               0x24
#define ESCKM_RSLH              0x5C
#define ESCKM_AST               0x2A
#define ESCKM_QM                0x3F
#define ESCKM_xX                0x28
#define ESCKM_LT                0x3C
#define ESCKM_ALP               0x40

/*--------------------------------------- Kssm FS Code Define -*/
#define FS_a                    0x61
#define FS_D                    0x44
#define FS_DC2                  0x12
#define FS_DC4                  0x14
#define FS_J                    0x4A
#define FS_K                    0x4B
#define FS_k                    0x6B
#define FS_M                    0x4D
#define FS_r                    0x72
#define FS_S                    0x53
#define FS_SI                   0x0F
#define FS_SO                   0x0E
#define FS_T                    0x54
#define FS_t                    0x74
#define FS_U                    0x55
#define FS_V                    0x56
#define FS_v                    0x76
#define FS_W                    0x57
#define FS_X                    0x58
#define FS_x                    0x78
#define FS_2                    0x32
#define FS_ECM                  0x21
#define FS_UL                   0x2D
#define FS_EMP                  0x26
#define FS_DLR                  0x24
#define FS_PNT                  0x2E

/*-------------------------------------------- TG Code Define -*/
#define ESC_TG                  0x1B
#define ESC_BLACKET1            0x5B
#define ESC_BLACKET2            0x51             
#define ESCTG_h                 0x68
#define ESCTG_e					0x65
#define ESCTG_W					0x57
#define ESCTG_w					0x77
#define ESCTG_I					0x49
#define ESCTG_i					0x69
#define ESCTG_T					0x54
#define ESCTG_D					0x44
#define ESCTG_L					0x4C
#define ESCTG_d					0x64
#define ESCTG_N					0x4E
#define ESCTG_j					0x6A
#define ESCTG_k					0x6B
#define ESCTG_6					0x36
#define ESCTG_7					0x37
#define ESCTG_c					0x63
#define ESCTG_G					0x47
#define ESCTG_g					0x67
#define ESCTG_U					0x55
#define ESCTG_u					0x75
#define ESCTG_BK_R				0x52
#define ESCTG_BK_r				0x72
#define ESCTG_F					0x46
#define ESCTG_f					0x66
#define ESCTG_B					0x42
#define ESCTG_b					0x62
#define ESCTG_S					0x53
#define ESCTG_s					0x73
#define ESCTG_V					0x56
#define ESCTG_v					0x76
#define ESCTG_BK_M				0x4D
#define ESCTG_BK_m				0x6D


/*-------------------------------------------------------------*/
#define AutoClr2(a,b)         ((a<<1)|b)

/*-------------------------------------------------------------*/
#define SET_ITEM                1
#define SELF_TEST_START         2
#define SELF_TEST_STOP          3
#define CONFIG                  4
#define START                   5
#define LPI_CMD                 1
#define PL_CMD                  2
#define LF_CMD                  3
#define FF_CMD                  4
#define DATA_LF_CMD             5
#define DATA_FF_CMD             6

/*------------------------------------------------------------*/
union REG_UNION {
                unsigned short int Two;
                struct{
                        u_char Hi,Low;
                }Order;
};

/*------------------------------------------------------ Font -*/
union INT_UNION {
                unsigned short int Tow;
                struct{
                        u_char ChH,ChL;
                }Order;
};

/*------------------------------------------------------------*/
struct FONT_INFO {
                u_int HTDouble;
                u_int VTDouble;
                u_int HTCondense;
                u_int VTUp;
                u_int VTDn;
                u_int Reverse;
                u_int Shadow;
                u_int UnderLine;
                u_int BoldFace;
                u_char ScaleState;
};

/*---------------- Character Image And Character String Image -*/
struct CH_IMG {
                u_char Col;
                u_char Body;
                u_char Rear;
                u_char Buff[432];
                u_char ExpBuff[576];
                u_char AdjMod;
                u_char AdjRemain;
                u_char AdjModKor;
                u_char AdjRemainKor;
};

struct ST_IMG {
                u_char HaveVTUp;
                u_char HaveVT;
                u_int  Pos;
                u_char Part;
                u_char Buff[14688];
                u_char ExpBuff[19584];
};

/*----------------------- ESC and Panel function setting Flag -*/
struct LF_INFO {
                u_int DotLenOfLine;
                u_char Sum;
                u_int AdjMod;
                u_int AdjRemain;
};

struct AUTOCLR_CTR {
                u_char So;
                u_char W;
};

struct MARGIN {
                u_int Left;
                u_int Right;
                u_int Top;
                u_int Bottom;
};

struct FONTCPI_INFO {
                u_char Col;
                u_char AdjMod;
                u_char Body;
};

/*------------------------------------ KSSM ESCAPE ECM DEFINE -*/
#define CPI             0
#define PROPORTION      1
#define CONDEN          2
#define EMPHA           3
#define DBPRINT         4
#define HTDOUBLE        5
#define ITALIC          6
#define UNDERLINE       7

/*---------------------------------------- KSSM FS ECM DEFINE -*/
#define HT_WRITE		0
#define SEMI_CT			1
#define HT_DB			2
#define VT_DB			3
#define QUARTER1		4
#define QUARTER2		5
#define NOTUSED			6
#define ULINE			7

/*-------------------------------------------------------------*/
#define TIME_OUT        5000

/*-------------------------------------- TabFlag Define -------*/
#define ENG12           0
#define ENG13           1
#define KOR24           2





