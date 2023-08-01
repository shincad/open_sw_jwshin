/*=============================================================*/
/*                  KD20B Controller Program                   */
/*                  Module Name : SLAVE                        */
/*                  Task   Name : Eeprom.c                     */
/*                  Programming Date : 1997. 1.                */
/*                  Kia Information Systems.                   */
/*                  Printer Development Team.                  */
/*                  Programmed by Shin Jung Wook               */
/*=============================================================*/

/*=============================================================*/
/*                       Include Part                          */
/*=============================================================*/

#include <stdio.h>
#include "define.h"
#include "extern.h"

/*=============================================================*/
/*                    Function Declaration                     */
/*=============================================================*/

EepSck_H(u_char);
EepSck_L(u_char);
EepRomCmd(u_char);
OutPut(u_char);
u_int ReadEepRom(u_char);
EepRom_WrEn();
EepRom_WrDis();
WriteEepRom(u_char,u_char,u_char);
EepRom_Erase(u_char);
SaveSetItem();
DefaultSetItem();
LoadSetItem();

/*=============================================================*/
/*                  EEPROM Serial Clock High                   */
/*=============================================================*/

EepSck_H(data)
u_char data;
{
	EEPTEMP2 = data;
    data     = data | 0x02;
    S_EEPCS  = data;

}

/*=============================================================*/
/*                  EEPROM Serial Clock Low                    */
/*=============================================================*/

EepSck_L(data)
u_char data;
{
    EEPTEMP2 = data;
    data     = data & 0xfd;
    S_EEPCS  = data;
}

/*=============================================================*/
/*                  EEPROM Command Routine (3 bit)             */
/*=============================================================*/

EepRomCmd(data)
u_char data;
{
    u_char shift;
    u_char temp;
    int i;
    temp = 0x01;
    for(i=0;i<=2;i++) {            /* 3 Bit Eeprom Command */
    	temp  = temp & 0xfb;
        shift = data >> i;
        if((shift & 0x01) != 0) {
        	temp = temp | 0x04;
            EepSck_H(temp);
            EepSck_L(temp);
        }
        else {
            EepSck_H(temp);
            EepSck_L(temp);
        }
    }
}

/*=============================================================*/
/*                  EEPROM Address Write Routine               */
/*=============================================================*/

OutPut(data)
u_char data;
{
    int i;
    u_char shift;
    u_char temp;
    temp = 0x01;
    for(i=0;i<=7;i++) {         /* 8 Bit Data Process */
    	temp  = temp & 0xfb;
        shift = data << i;
        if((shift & 0x80) != 0) {
        	temp = temp | 0x04;
            EepSck_H(temp);
            EepSck_L(temp);
        }
        else {
            EepSck_H(temp);
            EepSck_L(temp);
        }
    }
}

/*=============================================================*/
/*                  Read EEPROM Routine                        */
/*=============================================================*/

u_int ReadEepRom(addr)
u_char addr;
{
    u_int temp;
    int i;
    EEPDATA = 0;
    S_EEPCS = CSLTH;              /* Chip Select High */
    EepRomCmd(0x03);              /* Eeprom Read Command */
    OutPut(addr);                 /* Eeprom Address Output */
    for(i=0;i<=15;i++) {          /* 16 Bit Data Read Process */
    	temp = 0;
        EepSck_H(0x01);       /* Serial Clock High */
        EepSck_L(0x01);       /* Serial Clock Low  */
        if((S_STABIT & 0x40) == 0x40) {
        	temp = temp | 0x01;
        }
        else {
            temp = temp | 0x00;
        }
        EEPDATA = (EEPDATA | (temp << (15-i)));
    }
    EepSck_H(0x01);               /* Serial Clock High */
    EepSck_L(0x01);               /* Serial Clock Low  */
    S_EEPCS = CSLTL;              /* Chip Select Low   */
    return EEPDATA;
}

/*=============================================================*/
/*                  EEPROM Write Enable Routine                */
/*=============================================================*/

EepRom_WrEn()
{
    S_EEPCS = CSLTH;
    EepRomCmd(0x01);
    OutPut(0xff);
    S_EEPCS = CSLTL;
}

/*=============================================================*/
/*                  EEPROM Write Disable Routine               */
/*=============================================================*/

EepRom_WrDis()
{
    S_EEPCS = CSLTH;
    EepRomCmd(0x01);
    OutPut(0x00);
    S_EEPCS = CSLTL;
}

/*=============================================================*/
/*                  Write EEPROM Routine                       */
/*=============================================================*/

WriteEepRom(addr,data_h,data_l)
u_char addr;
u_char data_h;
u_char data_l;
{
    S_EEPCS = CSLTH;
    EepRomCmd(0x05);
    OutPut(addr);
    OutPut(data_h);
    OutPut(data_l);
    S_EEPCS = CSLTL;
    EepSck_H(EEPTEMP2);
    EepSck_L(EEPTEMP2);
    S_EEPCS = CSLTH;
    while((S_STABIT & 0x40) == 0) {
    	EepSck_H(EEPTEMP2);
        EepSck_L(EEPTEMP2);
    }
    S_EEPCS = CSLTL;
}

/*=============================================================*/
/*                  EEPROM Erase Routine                       */
/*=============================================================*/

EepRom_Erase(addr)
u_char addr;
{
    S_EEPCS = CSLTH;
    EepRomCmd(0x07);
    OutPut(addr);
    S_EEPCS = CSLTL;
    EepSck_H(0x00);
    EepSck_L(0x00);
    S_EEPCS = CSLTH;
    while((S_STABIT & 0x40) == 0) {
    	EepSck_H(0x01);
        EepSck_L(0x01);
    }
    S_EEPCS = CSLTL;
}

/*=============================================================*/
/*                  SaveSetItem Function                       */
/*=============================================================*/

SaveSetItem()
{
    u_int i;
    S_EEPCS = 0;
    EepRom_WrEn();
    for(i=0;i<=(MAX_MENU+1);i++) {
    	EepRom_Erase(i);
        WriteEepRom(i,0,SetItem[i]);
    }
    EepRom_WrDis();
}

/*=============================================================*/
/*                  DefaultSetItem Function                    */
/*=============================================================*/

DefaultSetItem()
{
    SetItem[0]  = 0;
    SetItem[1]  = 0;
    SetItem[2]  = 0;
    SetItem[3]  = 0;
    SetItem[4]  = 0;
    SetItem[5]  = 0;
    SetItem[6]  = 0;
    SetItem[7]  = 0;
    SetItem[8]  = 6;
    SetItem[9]  = 5;
    SetItem[10] = 0;
    SetItem[11] = 0;
    SetItem[12] = 0;
    SetItem[13] = 0;
    SetItem[14] = 1;
    SetItem[15] = 0;
    SetItem[16] = 0;
}

/*=============================================================*/
/*                  LoadSetItem Function                       */
/*=============================================================*/

LoadSetItem()
{
    u_int i;
    SetItem[0] = (u_char)ReadEepRom(0);
    for(i = 0;i<=(MAX_MENU+1);i++) {
    	SetItem[i] = (u_char)ReadEepRom(i);
    }
}
