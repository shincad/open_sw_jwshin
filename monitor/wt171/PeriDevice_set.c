/****************************************************************************
   +----------------------------------------------------------------------+
   | Copyright EDtech co.ltd 2002                                         |
   | EDtech co.ltd reserves the right to change products                  |
   | or specifications without notice.                                    |
   +----------------------------------------------------------------------+
   Project    : TFT LCD monitor & TV
   Version    : 
   File Name  : 
   Functions  : 
   Revision   :

   2003-01-10 2:39오후  JDHAN           Modified for Monitor-TV
****************************************************************************/

//****************************************************************//
//화일참조
//****************************************************************//
#include	"TopHeader.h"
#include	"EEPROMadr.h"
#include	"TVMODE.h"
#include <stdio.h>
#ifdef	DVI_EDIDWrite
#include	"DVIEDID.h"
#endif
#include "extern.h"

#if		defined(MCU_MTV230)
#include	"MTV230xfr.h"
//extern	xdata	WORD	xEEPROM_addr[MaxEepromBuffer];
//extern	xdata	BYTE	xEEPROM_data[MaxEepromBuffer];
extern	xdata	WORD	xEEPROM_addr[MaxEepromBuffer-20];
extern	xdata	BYTE	xEEPROM_data[MaxEepromBuffer-20];
#endif



//****************************************************************//
//함수선언
//****************************************************************//
bit WriteI2C(BYTE sysaddr, BYTE subaddr, BYTE writedata);
WORD ReadI2C(BYTE SystemAdr, WORD address);
BYTE ModeTotalcount(void);
bit START_I2C(BYTE sysaddr);
void STOP_I2C(void);
bit WriteData(BYTE temp);
void putss(BYTE);

//****************************************************************//
//변수선언
//****************************************************************//

#ifdef	DVI_EDIDWrite
extern	bit	YouHaveToInitDviEDID;
extern	BYTE idata MemoryCount;
#endif

//****************************************************************//
//Inital Channel Number
//****************************************************************//
#ifndef BtcBoard_Option
code BYTE IwantInitNTSC_AIRChannel[] = {6,7,9,11};
code BYTE IwantInitNTSC_CATVChannel[] = {6,7,9,11,22,45,78,100};
code BYTE IwantInitPAL_IChannel[] = {1,2,3,4};
code BYTE IwantInitPAL_BGChannel[] = {6,7,9,11,22,45,78,100};
code BYTE IwantInitPAL_DKChannel[] = {6,7,9,11,22,45,78,100};
code BYTE IwantInitSEC_BGChannel[] = {6,7,9,11,22,45,78,100};
code BYTE IwantInitSEC_DKChannel[] = {6,7,9,11,22,45,78,100};
code BYTE IwantInitSEC_LChannel[] = {1,2,3,4};
#endif

#ifdef	DVI_EDIDWrite
BYTE EEPROM_Read_02(WORD address)
{
	return((BYTE)ReadI2C(EEPROM_sysaddress_2402,address));
}
#endif

BYTE EEPROM_Read(WORD address)
{
	return((BYTE)ReadI2C(EEPROM_sysaddress,address));
}

BYTE AD9884_Read(BYTE address)
{
	return((BYTE)ReadI2C(ADC_sysaddress,address));
}

void EepromSetQue(WORD address, BYTE Recdata)
{


	BYTE temp;
	temp = (BYTE)(address>>8);
	temp = ((temp<<1)&0xfe)|EEPROM_sysaddress;
	xEEPROM_addr[EepromBufferQue] = (WORD)(temp<<8)|(address&0x00FF);
	xEEPROM_data[EepromBufferQue] = Recdata;
	EepromBufferQue++;
	if(EepromBufferQue>MaxEepromBuffer-1) {EepromBufferQue = 0;}

}

void		CheckTemMinSave()
{
	if(	(EEPROM_Read(TenTimeCheck_adr)>6)||
		(EEPROM_Read(TenTimeCheck1_adr)>10)||
		(EEPROM_Read(TenTimeCheck2_adr)>10)||
		(EEPROM_Read(TenTimeCheck3_adr)>10)||
		(EEPROM_Read(TenTimeCheck4_adr)>10)||
		(EEPROM_Read(TenTimeCheck5_adr)>10))
	{
		START_I2C(TenTimeCheck_adr);//start command & page address
		WriteData(0);
		WriteData(0);
		WriteData(0);
		WriteData(0);
		WriteData(0);
		WriteData(0);
		STOP_I2C();
	}	
}

void PeriDevice_set(void)
{


#if		defined(MCU_MTV230) 
	BYTE count;
	WORD EEPROMaddress;
	static BYTE idata EepromWriteTimer;
	static BYTE idata EepromPageInitCount;
	
	++EepromWriteTimer;
	if(ProgNo==0) 	if(EepromWriteTimer%3) return;	//15ms마다.  

	
	if(EepromBufferQue!=EepromQuepointer)
	{
		for(count=0;count<1;count++){					//EEPROM write time때메 하나씩..

			WriteI2C((BYTE)(xEEPROM_addr[EepromQuepointer]>>8),(BYTE)xEEPROM_addr[EepromQuepointer],xEEPROM_data[EepromQuepointer]);
			EepromQuepointer++;
			if(EepromQuepointer>MaxEepromBuffer-1) EepromQuepointer = 0;
			if(EepromBufferQue == EepromQuepointer) break;
		}
	}
	
	//CLOCK,PHASE,H-POS,V-POS,PRE-AUTO
	else{
		if(YouHaveToInitMode)
		{
			//start point
			EEPROMaddress=(EepromPageInitCount/4)*16+ModeEepromStartAddress;//address offset:16
			EEPROMaddress=EEPROMaddress&0x700;
			EEPROMaddress=(EEPROMaddress>>8);
			
			count = (ModeTotalcount()-1);
			
			if(EepromPageInitCount>=(ModeTotalcount()-1))
			{
				EepromPageInitCount=0;
				YouHaveToInitMode=0;
				YouHaveToInitTVchannel=1;
				EepromPageInitCount=0;
			}
			else{
				START_I2C(EEPROM_sysaddress|(BYTE)(EEPROMaddress<<1));//start command & page address
				WriteData((BYTE)(EepromPageInitCount/4)*16);			 //start
				WriteData(0x80);//WriteData(ModeList[EepromPageInitCount].H_pos);
				WriteData(ModeList[EepromPageInitCount].IVAS);
				WriteData(0x80);//WriteData(ModeList[EepromPageInitCount].Clock);
				WriteData(ModeList[EepromPageInitCount].Phase);
				
				EepromPageInitCount++;
				WriteData(0x80);
				//WriteData(0x80);
				WriteData(ModeList[EepromPageInitCount].IVAS);
				WriteData(0x80);
				WriteData(ModeList[EepromPageInitCount].Phase);
				
				EepromPageInitCount++;
				WriteData(0x80);
				//WriteData(0x80);
				WriteData(ModeList[EepromPageInitCount].IVAS);
				WriteData(0x80);
				WriteData(ModeList[EepromPageInitCount].Phase);
				
				EepromPageInitCount++;
				WriteData(0x80);
				//WriteData(0x80);
				WriteData(ModeList[EepromPageInitCount].IVAS);
				WriteData(0x80);
				WriteData(ModeList[EepromPageInitCount].Phase);
				
				EepromPageInitCount++;
				STOP_I2C();
			}
		}
		else if(YouHaveToInitTVchannel)
		{
		//initialize eeprom for TV channel
		YouHaveToInitTVchannel=0;
		
		}
		
		#ifdef	DVI_EDIDWrite
/*		else if(YouHaveToInitDviEDID)
		{
			if(MemoryCount<=7) 
			{
				START_I2C(EEPROM_sysaddress_2402);//start command & page address
				WriteData(MemoryCount*16);			//start
				for(count=MemoryCount*16;count<(MemoryCount*16+16);count++)
				{
					EEPROMaddress=DVIEDID_ROM[count];
					NOP;
					WriteData(DVIEDID_ROM[count]);
				}
				STOP_I2C();
			}
			++MemoryCount;
			if(MemoryCount==10) 
			{
				YouHaveToInitDviEDID=0;
				MemoryCount=0;
				LED_ON;
				for(count=0;count<0x80;count++)
				{
					if(DVIEDID_ROM[count]!= (BYTE)EEPROM_Read_02((WORD)count)) 
					{
						LED_OFF;
						while(1);
					}
				}
			}
		} */
		#endif
	}

#elif	defined(MCU_NT68F63)

	//*******************************//
	//								 //
	//  공사중(Under Construct!!!)	 //
	//								 //
	//*******************************//
	
#endif
}
