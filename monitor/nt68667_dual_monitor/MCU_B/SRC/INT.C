#include "8051.H"
#include "RAM.H"
//#include "MyDef.H"
#include "NT686xx_MCU_REG.H"
#include "INT.H"
#include "Board.H"	// INIT_CLRWDT
#include "Ddc_ci.H"
#include "OSD_TAB.H"
#include "BFControl.H"

void Timer0(void) interrupt 1 using 2
{

	TR0 = 0;                        //Timer 0 run control. Starts timer when set to 1.
#if NT68167
	TL0 = (65536-T0_Speed)%256;
	TH0 = (65536-T0_Speed)/256;
#else
#if CoreSpeed == 0x36
	TL0 = (65536-3000)%256;			//1mS for (36MHz) CPU
	TH0 = (65536-3000)/256;
#else
	TL0 = (65536-2000)%256;			//1mS for (24MHz) CPU
	TH0 = (65536-2000)/256;
#endif
#endif

	TR0 = 1;                        //Timer 0 run control. Starts timer when set to 1.
	if(usTimer1_1ms != 0)			// 1ms
		usTimer1_1ms--;
	if(ucTime2Backlight > 1)	// 1: Turn ON 0: Do nothing
		ucTime2Backlight--;
	if(++ucTimer10ms >= 10){	// 10ms
		CLRWDT = DEFAULT_CLRWDT;
		ucTimer10ms = 0;
		if(ucSyncSourceTimer != 0)
			ucSyncSourceTimer--;
		if(usOSDTimer_10ms != 0)
			usOSDTimer_10ms--;
		//--------------------- +jwshin 120302   NoSignal에서의 Mode 전환 화면을 위한 Timer ~!.
		if(usOSD2Timer_10ms != 0)
			usOSD2Timer_10ms--;
		//------------------------------------------		
		if(ucLoopTimer_10ms != 0)
			ucLoopTimer_10ms--;
		if(ucSyncStableTimer_10ms != 0)
			ucSyncStableTimer_10ms--;
		if(ucTime2RepeatKey != 0)
			ucTime2RepeatKey--;
		if(usPoSvTimer != 0)
			usPoSvTimer--;
		//----------------- +jwshin 111213
		if(ucNoSigTimer != 0) 
			ucNoSigTimer--;
		//------------------------------------	
#ifndef BF_MOVING_WINDOW
		if(ucLFDemoTimer != 0)
			ucLFDemoTimer--;
#endif
#ifdef BF_MOVING_WINDOW
		ucBFMovingTimer = 1;
#endif
		}
	else if(ucTimer10ms == 5){
#if FE2P_LIB==ON
		if(feSave_Timer != 0)	//Fe2p timer 2006/10/31 Alvin
			feSave_Timer--;
#endif
		if(usBFTimer_10ms != 0)
			usBFTimer_10ms--;
			
		if(++ucLEDTimer_10ms == 25){	//10ms * 25 = 250ms
			ucLEDTimer_10ms = 0;
			if(bStatusReport !=0 )	//#ifdef TC_ENABLE_TRUECOLOR
				bIsLEDFlashing = TRUE;
			if(ucBestMesgTimer != 0)
				ucBestMesgTimer--;
			if(++ucTimer1000ms >= 4){	// 250ms * 4 = 1000ms
				ucTimer1000ms = 0;
				if(usWarningMsgTimer_1s != 0)
					usWarningMsgTimer_1s--;
#ifdef ENABLE_TD_			//	THEFT DETERRENCE					
				if(ucTD_State == TD_POSSIBLE_THEFT && ucTD_Timeout != 0){
					if(++ucTD_TimeoutS >= 60){
						ucTD_TimeoutS = 0;
						ucTD_Timeout--;
					}
				}
				if(ucTD_PinFailedTimer != 0 )
					ucTD_PinFailedTimer--;
#endif
				if(ucPowerStatus > 0x7f){
					if(++usPOTTimerS_900 >= 900){
						usPOTTimerS_900 = 0;
						bPOTUpdate = TRUE;
						if(++ucPOTTimerM_4 >= 4){
							ucPOTTimerM_4 = 0;
							if(++ulPOTTimerH > 0x0ffff)
								ulPOTTimerH = 0x0ffff;
							//else
							//	bPOTUpdate = TRUE;
						}
					}
				}
			}
		}
	}

}

void IntGroup0(void) interrupt 0 using 1
{
unsigned short loop;
unsigned char i;
	if((INT_SRC & INTIIC0_IRQ) != 0){
		i = IIC0INT_FLG;
		bDDC_Ci_Channel = 0;
		if(i & INTA){
			IIC0INT_CLR = INTA;
			if(IIC0_STATUS & DOWRITE){  // Slave Addr || 0x01 ==> Read
				IIC0_INT_EN = (INTA | INTTX);
				ucDDCCiTxOut = 0;
				ucDDCCiTxChecksum = 0x50;
			}
			else{  // Slave Addr ==> Write
				IIC0_INT_EN = (INTA | INTRX);
				IIC0_CFG |= SEND_ACK;
				ucDDCCiRxIn = 0;
				bDDCCmdUpdate = TRUE;
			}
		}
		else if(i & INTTX){
			if(bFactoryMode == FALSE){
				if(ucDDCCiTxOut != ucDDCCiTxIn){
					i = ucDDCCiTxBuffer[ucDDCCiTxOut++];
					ucDDCCiTxChecksum ^= i;
					IIC0_TXDATA = i;
					IIC0INT_CLR = INTTX;
				}
				else{
					IIC0_TXDATA = ucDDCCiTxChecksum;
					IIC0INT_CLR = INTTX;
					ucDDCCiTxOut = 0;
					loop = 10000;
					while((IIC0_STATUS & TX_NULL) == 0){
						if(--loop == 0)
							break;
					}
					IIC0INT_CLR = (INTTX | SET_NO_DATA_IN);
				}
			}
			else{	//BenQ factory
				if(ucDDCCiTxOut != ucDDCCiTxIn){
					i = ucDDCCiTxBuffer[ucDDCCiTxOut++];
//					ucDDCCiTxChecksum += i;
					IIC0_TXDATA = i;
					IIC0INT_CLR = INTTX;
				}
				else{
//					IIC0_TXDATA = ucDDCCiTxChecksum;
					i = ucDDCCiTxBuffer[ucDDCCiTxOut++];
					IIC0_TXDATA = i;
					IIC0INT_CLR = INTTX;
					ucDDCCiTxOut = 0;
					loop = 10000;
					while((IIC0_STATUS & TX_NULL) == 0){
						if(--loop == 0)
							break;
					}
					IIC0INT_CLR = (INTTX | SET_NO_DATA_IN);
				}
			}
		}
		else if(i & INTRX){
			i = IIC0_RXDATA;
			ucDDCCiRxBuffer[ucDDCCiRxIn++] = i;
			IIC0INT_CLR = INTRX;
			if(ucDDCCiRxIn > DDCCi_BUFFER_SIZE-1)
				ucDDCCiRxIn = 2;
		} 
		else if(i & INTNAK){
			IIC0INT_CLR = INTNAK;
		}
		else if(i & INTLOST){
			IIC0INT_CLR = INTLOST;
		}
	}
#if (NT68670 || NT68670B || NT68667)
	if(INT_SRC & INT_SC){
		MCU_INT_DISABLE();
		BLFastOff();
		ucTime2Backlight = 0;
		bOptAbort = TRUE;
		usTmpHSync = 0xffff;
	}
#endif

#if (NT68167)
	if((INT_SRC & INT_SC)){
		MCU_INT_DISABLE();
		BLFastOff();
		ucTime2Backlight = 0;
		bOptAbort = TRUE;
		usTmpHSync = 0xffff;
	}
#endif	

}

#if (!NT68167)
void IntGroup1(void) interrupt 2 using 3
{
unsigned char i;
unsigned short loop;
//unsigned char port;
	if((INT_SRC & INTIIC1_IRQ) != 0){
		i = IIC1INT_FLG;
		bDDC_Ci_Channel = 1;
		if(i & INTA){
			IIC1INT_CLR = INTA;
			if(IIC1_STATUS & DOWRITE){  // Slave Addr || 0x01 ==> Read
				IIC1_INT_EN = (INTA | INTTX);
				ucDDCCiTxOut = 0;
				ucDDCCiTxChecksum = 0x50;
			}
			else{  // Slave Addr ==> Write
				IIC1_INT_EN = (INTA | INTRX);
				IIC1_CFG |= SEND_ACK;
				ucDDCCiRxIn = 0;
				bDDCCmdUpdate = TRUE;
			}
		}
		else if(i & INTTX){
			if(bFactoryMode == FALSE){
				if(ucDDCCiTxOut != ucDDCCiTxIn){
					i = ucDDCCiTxBuffer[ucDDCCiTxOut++];
					ucDDCCiTxChecksum ^= i;
					IIC1_TXDATA = i;
					IIC1INT_CLR = INTTX;
				}
				else{
					IIC1_TXDATA = ucDDCCiTxChecksum;
					IIC1INT_CLR = INTTX;
					ucDDCCiTxOut = 0;
					loop = 10000;
					while((IIC1_STATUS & TX_NULL) == 0){
						if(--loop == 0)
							break;
					}
					IIC1INT_CLR = (INTTX | SET_NO_DATA_IN);
				}
			}
			else{	//BenQ factory
				if(ucDDCCiTxOut != ucDDCCiTxIn){
					i = ucDDCCiTxBuffer[ucDDCCiTxOut++];
//					ucDDCCiTxChecksum += i;
					IIC1_TXDATA = i;
					IIC1INT_CLR = INTTX;
				}
				else{
//					IIC1_TXDATA = ucDDCCiTxChecksum;
					i = ucDDCCiTxBuffer[ucDDCCiTxOut++];
					IIC1_TXDATA = i;
					IIC1INT_CLR = INTTX;
					ucDDCCiTxOut = 0;
					loop = 10000;
					while((IIC1_STATUS & TX_NULL) == 0){
						if(--loop == 0)
							break;
					}
					IIC1INT_CLR = (INTTX | SET_NO_DATA_IN);
				}
			}
		}
		else if(i & INTRX){
			i = IIC1_RXDATA;
			ucDDCCiRxBuffer[ucDDCCiRxIn++] = i;
			IIC1INT_CLR = INTRX;
			if(ucDDCCiRxIn > DDCCi_BUFFER_SIZE-1)
				ucDDCCiRxIn = 2;
		} 
		else if(i & INTNAK){
			IIC1INT_CLR = INTNAK;
		}
		else if(i & INTLOST){
			IIC1INT_CLR = INTLOST;
		}
	}

	
#if NT68665
	if((INT_SRC & INTEXT_IRQ) != 0){
		if((INTEXT_FLG & INTE0) != 0){
			INTEXT_FLG = INTE0;
			MCU_INT_DISABLE();
///////////////////////////////////////////
			BLFastOff();
//////////////////////////////////////////
			ucTime2Backlight = 0;
			bOptAbort = TRUE;
			usTmpHSync = 0xffff;
//			usTmpVSync = 0x55aa;
		}
	}
	#endif
}
#endif

void IntUART(void) interrupt 4 using 1
{
unsigned char i;
	if(RI == 1){
		RI=0;
		i = SBUF;
		ucUARTRxBuffer[ucUARTRxIn] = i;
		if(++ucUARTRxIn > UART_RX_BUFFER_SIZE-1)
			ucUARTRxIn = 0;
	}

	if(TI == 1){
		TI = 0;
		if(ucUARTTxIn != ucUARTTxOut){
			SBUF = ucUARTTxBuffer[ucUARTTxOut];
			if(++ucUARTTxOut > UART_TX_BUFFER_SIZE-1)
				ucUARTTxOut = 0;
		}
		else{
			ucIsTransDisabled = 1;
		}
	}

}

#ifndef NO_PRINT_LIB
char UART_Putchar(unsigned char c)
{
	//If the buffer is full, return an error value.
	if(((ucUARTTxIn+1)%UART_TX_BUFFER_SIZE) == ucUARTTxOut) return -1;

	EA = 0;
	
	ucUARTTxBuffer[ucUARTTxIn] = c;
	if(++ucUARTTxIn > UART_TX_BUFFER_SIZE-1)
		ucUARTTxIn = 0;

	if(ucIsTransDisabled){
		ucIsTransDisabled = 0;
		TI = 1;
	}
	
	EA = 1;
	
	return 0;
}

char putchar(char c)
{
//	volatile unsigned int i;
unsigned short i;
	while(UART_Putchar(c) != 0){
		for(i=0; i<1000; i++){}
	}
	return (c);
}
#endif

