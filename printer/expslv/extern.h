/*=============================================================*/
/*                  KD20B Controller Program                   */
/*                  Module Name : SLAVE                        */
/*                  Extern.h                                   */
/*                  Programming Date : 1997. 1. 15             */
/*                  Kia Information Systems.                   */
/*                  Printer Development Team.                  */
/*                  Programmed by Shin Jung Wook               */
/*=============================================================*/

#ifndef __EXTERN_H
#define __EXTERN_H      1


extern  char    DspMsg1[17];
extern  int     ModeLedPos;
extern  unsigned char   PModeSave1;
extern  unsigned char   PModeSave2;
extern  unsigned char   OpMode;
extern  char    *DspMenu[16];
extern  char    *DspItem[16][11];
extern  char    *ErrorMenu[49];
extern  unsigned char    SetItem[17];
extern  unsigned char    OnLineFlag;
extern  unsigned char    PaperEndFlag;
extern  unsigned char    OldKey1;
extern  unsigned char    NewKey1;
extern  unsigned char    OldKey2;
extern  unsigned char    NewKey2;
extern  unsigned char    MCmd1;
extern  unsigned char    MCmd2;
extern  unsigned int     MValue;
extern  unsigned int     CharDotLen;
extern  unsigned int     PageDotLen;
extern  unsigned int     RLen;
extern  int              CurPos;
extern  unsigned char    EEPTEMP2;
extern  unsigned int     EEPDATA;
extern  unsigned char    ErrCode;
extern  unsigned char    EqualFlag;
extern  Display( char *);
extern  CallMaster(char);
#endif
