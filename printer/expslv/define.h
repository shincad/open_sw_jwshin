/*=============================================================*/
/*                  KD20B Controller Program                   */
/*                  Module Name : SLAVE                        */
/*                  define.h                                   */
/*                  Programming Date : 1997. 1. 15             */
/*                  Kia Information Systems.                   */
/*                  Printer Development Team.                  */
/*                  Programmed by Shin Jung Wook               */
/*=============================================================*/

/*=============================================================*/
/*                 Memory Map of This Module                   */
/*                 ROM : 0 - 1FFFF : 27C210                    */
/*                 RAM : 80000 - 8FFFF : 62256 2EA             */
/*                 I/O : 100000 - 18000F                       */
/*=============================================================*/

#define WR_LPDATA       *(unsigned char *)      0x100001
#define WR_LPSTB        *(unsigned char *)      0x100003
#define WR_LPPRIME      *(unsigned char *)      0x100005
#define RD_LPSTA        *(unsigned char *)      0x100007
#define S_PORTCS        *(unsigned char *)      0x100009
#define FUNC_CS         *(unsigned char *)      0x10000B
#define S_OPCS          *(unsigned char *)      0x200001
#define OP_LED1         *(unsigned char *)      0x200003
#define OP_LED2         *(unsigned char *)      0x200005

/*----------------------------------------------- (LP) STATUS -*/
/*  STATUS: BIT5-BIT0      EEPROM-DO: BIT6                    -*/
/*-------------------------------------------------------------*/
#define S_STABIT        *(unsigned char *)      0x18000F

/*---------------------------------------------------- EEPROM -*/
/*    S_EEPCS  : SD0 = CS , SD1 = SCK , SD2 = DI               */
/*    S_STABIT : BIT6=EEPROM-DO, STATUS 1-6                    */
/*-------------------------------------------------------------*/
#define S_EEPCS         *(unsigned char *)      0x180003

#define S_M_WRITE       *(unsigned char *)      0x180005
#define RD_FIFOEM       *(unsigned char *)      0x180007
#define RD_FIFO         *(unsigned char *)      0x180009
#define FIFO_RS         *(unsigned char *)      0x18000B
#define RD_SM_INTACK    *(unsigned char *)      0x18000D
#define S_STABIT        *(unsigned char *)      0x18000F

/*------------------------------------------------ LCD DEFINE -*/
/*       --------  OP_LED1 (WRITE)    --------  OP_LED2 (WRITE)*/
/*      |  BIT0  -                   |  BIT0  - LCD RS         */
/*      |        -                   |        - LCD R/(W)      */
/*      |        - TEST              |        -                */
/*      |   |    - PAPERUPCONT       |   |    - BUZZER         */
/*      |        -                   |        - STANDARD       */
/*      |        - ONLINE            |        - HIGHDENSITY    */
/*      |        -                   |        - HIGHSPEED      */
/*      |  BIT7  -                   |  BIT7  -                */
/*       --------                     --------                 */
/*       --------  OP_LED1 (READ)     --------  OP_LED2 (READ) */
/*      |  BIT0  - PAPERUPCONT       |  BIT0  -                */
/*      |        - SMALLCONT (DOWN)  |        -                */
/*      |        - SMALLCONT (UP)    |        -                */
/*      |   |    - LINEFEED          |   |    -                */
/*      |        - FORMFEED          |        - PRINTMODE      */
/*      |        -                   |        -                */
/*      |        - ONLINE            |        - MODE           */
/*      |  BIT7  -                   |  BIT7  - TEST           */
/*       --------                     --------                 */
/*-------------------------------------------------------------*/

#define LCD_IWR         0xFC
#define LCD_DWR         0xFD
#define STAND_LED       0xEF
#define HIGHSP_LED      0xBF
#define HIGHDS_LED      0xDF
#define ONLINE_ON       0xDF
#define LED_OFF         0xFF
#define TESTLED_ON      0xFB
#define TOPLED_ON       0xF7

/*-------------------------------------------- PRINT MODE LED -*/

#define BOTONG          2
#define GOSOK           0
#define GOPUMWI         1

/*-------------------------------------------------- DC1 CODE -*/

#define DC1             0x11

/*--------------------------------------------- EEPROM CS H,L -*/

#define CSLTH           0x01
#define CSLTL           0x00

/*------------------------------------------- OPTION DISPLAY  -*/

#define PRINT_MODE      3
#define COPY_ITEM       1
#define HAN300_ITEM     2
#define ENG410_ITEM     3
#define DSP_COPY_ITEM   "COPY MODE"
#define DSP_HAN300_ITEM "HAN 300 LPM MODE"
#define DSP_ENG410_ITEM "ENG 410 LPM MODE"

/*------------------------------------------- DISPLAY MESSAGE -*/

#define DSP_ONLINE              "ON LINE"
#define DSP_OFFLINE             "OFF LINE"
#define DSP_SELF_TEST_WAIT      "SELF TEST (WAIT)"
#define DSP_SELF_TEST           "SELF TEST..."
#define DSP_OFFLINE_WAIT        "OFF LINE (WAIT)"
#define DSP_ONLINE_WAIT         "ON LINE (WAIT)"
#define DSP_SAVING              "SAVING"
#define DSP_INITIALIZE          "Initializing..."
#define DSP_INITEEPROM          "Init EEPROM..."
#define DSP_KDLOGO              "Phoenix Printer"
#define DSP_PAPER_END           "PAPER END ERROR "
#define DSP_PLATEN_OPEN         "PLATEN OPEN ERR "

/*-------------------------------------------- OPERATING MODE -*/

#define NORMAL          0
#define SELF_TEST_START 1
#define SELF_TEST_STOP  2
#define SELF_TEST_RUN   3

/*-------------------------------------------- MAXMENU DEFINE -*/

#define MAX_MENU        15
#define MAX_ITEM        11

/*-------------------------------------------- READKEY DEFINE -*/

#define ONLINE_KEY            1
#define PRT_MODE_KEY          2
#define MODE_KEY              3
#define TEST_KEY              4
#define TOP_KEY               5
#define MISE_UP_KEY           6
#define MISE_DOWN_KEY         7
#define LF_KEY                8
#define FF_KEY                9

/*----------------------------------------- CALLMASTER DEFINE -*/

#define STX                   0x02
#define ETX                   0x03
#define SET_ITEM              1
#define SELF_TEST_START_CMD   2
#define SELF_TEST_STOP_CMD    3
#define CONFIG                4
#define START                 5

/*--------------------------------------------- ESCAPE DEFINE -*/

#define ESC             0x1B
#define NL              0x0A
#define EM              0x19

/*-------------------------------------------- COMMAND DEFINE -*/

#define LPI_CMD         1
#define PL_CMD          2
#define LF_CMD          3
#define FF_CMD          4
#define DATA_LF_CMD     5
#define DATA_FF_CMD     6

/*---------------------------------------------- ERROR DEFINE -*/

#define MST_STX_ERR     "MASTER STX ERROR"
#define MST_ETX_ERR     "MASTER ETX ERROR"

/*----------------------------------- MODE KEY DIRECTION FLAG -*/

#define PLUS_DIRECTION   '1'
#define MINUS_DIRECTION  '0'

/*------------------------------------- FLAG SET,RESET DEFINE -*/
#define FLAG_SET         '1'
#define FLAG_RESET       '0'
#define SET              '1'
#define RESET            '0'

/*------------------------------------------- KEY WAIT DEFINE -*/

#define ON_LINE_KEY_WAIT        while((OP_LED1 & 0x40) == 0)
#define PRINT_MODE_KEY_WAIT     while((OP_LED2 & 0x10) == 0)
#define MODE_KEY_WAIT           while((OP_LED2 & 0x40) == 0)
#define TEST_KEY_WAIT           while((OP_LED2 & 0x80) == 0)
#define TOP_KEY_WAIT            while((OP_LED1 & 0x01) == 0)
#define MISE_UP_KEY_WAIT        while((OP_LED1 & 0x04) == 0)
#define MISE_DOWN_KEY_WAIT      while((OP_LED1 & 0x02) == 0)

/*------------------------------------------ INTERRUPT DEFINE -*/

#define INT_DIS                 asm(" MOVE.W #$2700,SR ")
#define INT_ENB                 asm(" MOVE.W #$23FF,SR ")
#define INT_DIS_PANEL           asm(" MOVE.W #$2400,SR ")


/* Weight the tail of a command with 20H in CallMaster Function */

#define CMD_WEIGHT              0x20

/*-------------------------------------------- Type Definition -*/

typedef unsigned char           u_char;
typedef unsigned int            u_int;

/*------------------------------------------ Port Check Define -*/

#define FIFO_EMPTY_CHK          while((RD_FIFOEM & 0x01) == 0)
#define ACK_CHK                 while((RD_LPSTA & 0x20) > 0)
#define PFAULT_CHK              while((RD_LPSTA & 0x10) != 0)
#define SLCT_PFAULT_CHK         while((RD_LPSTA & 0x14) != 0)

/*------------------------------------------- ErrorCode Define -*/

#define PAPER_END       0x00
#define PLATEN_OPEN     0x01
#define PAPER_NEA_END   0x02
#define PAPER_PH_OPEN   0x03
#define FORMS_CHECK     0x04
#define RIBBON_CHECK    0x05
#define IF_PARITY_ERR   0x06
#define BUFFER_FULL     0x07
#define INV_FUNC_CODE   0x08
#define SHUTTLE_LOCK    0x09
#define HD_FIRE_ERROR   0x0A
#define HD_OVER_HEAT    0x0B

#define SHTTL_SNS_ERR   0x0D

#define SHTTL_SPD_ERR   0x0F

#define HD_REG_ERROR    0x11
#define HD_EOH_CHK      0x12
#define MEMORY_ERROR    0x13
#define BLOWER_STOP     0x14
#define SHTTL_DRV_ERR1  0x15
#define TR_DRIVER_ERR   0x16
#define H_TR_ERROR      0x17
#define HD_TR_CHK       0x18
#define SLNID_DRV_ERR   0x19
#define SLV_INVAL_ERR   0x1A
#define SLAVE_CPU_ERR   0x1B


#define MASTR_CPU_ERR   0x1E
#define POWER_ALARM1    0x1F

#define RBN_DRVER_ERR   0x21
#define SHTTL_DRV_ERR2  0x22


#define EEPROM_ERROR    0x25
 

#define FAN_STOP        0x28







#define POWER_ALARM2    0x30


/*------------------------------------------------------------*/
union REG_UNION {
                unsigned short int Two;
                struct{
                        u_char Hi,Low;
                }Order;
};
