#include "MCU.H"
#include "NT686xx_SC_REG.H"
#include "NT686xx_MCU_REG.H"
#include "8051.H"
#include "RAM.H"
#include "NVRAM.H"
#include "UserAdj.H"
#include "ModeHandle.H"
#include "Scaler.H"
#include "OSD.H"
#include "AutoAdj.H"
#include "sRGB.H"
#include "DDC_Ci.H"
#include "Board.H"
#include "Mis.H"
#include "NVTDebug.h"
#include "OSD_TAB.H"
#include "IIC.H"
#include "OSD_LF.H"
#if FE2P_LIB==ON
	#if NT68167
		#include "fe2p_nt68167 v1.1.h"
	#elif NT68667
		#include "fe2p_nt68667.h"
	#endif
#endif

//extern code unsigned char ID_Table[];

void main(void);

void main(void) using 0
{
ReStart:
	while(1) {

	EA = 0;
	BANK_SET = 0x22;	//select 2 banks architecture

#if PBusProtocol
	SC_HW_RST = PBUS_EN;
	SC_HW_RST = PBUS_EN|SC_RST;
	MCU_INT_ENABLE();
#endif	

	InitMCU();

	
	NVRAM_Init();				
	
	
	if(bExitSysLoop) continue;			
	
//	printf("Start Program\r\n");
	printf("Dnp System NT68667\r\n");
	
//	WriteIIC(SCALER_I2C_ADDR,0xff, 0x00);

	InitScaler();
	LoadModeIndependentSettings();
	
//	RGB_SW1_RGB2();			// -jwshin 121010

	if((ucPowerStatus & SoftPowerOnFlag)== 0){
		LED_RedOff();
		LED_GrnOff();
	}
	else{
		LED_GrnOn();
	}
	
	LoadFont();

	
/*	if(ucSource == mSource_DVI)
		ucPowerStatus |= InputSourceDVI;
	else
		ucPowerStatus &= ~InputSourceDVI;*/
	InputSourceSelect();

  CheckPowerStatus();				

	// Load RGB Gain & Offset
	LoadADC_Gain();

//	Write24C16(EPADDR_SN0,'C');
//	Write24C16(EPADDR_SN1,'S');

#ifdef ENABLE_TD_	//	THEFT DETERRENCE
	TD_Init();
#endif

#ifdef NVT_HW_DEBUG
	IsNVTDebugActive = 0;
#endif

//#ifndef NO_PRINT_LIB
//	printf("Start Program\r\n");
//#endif


	ucLoopTimer_10ms = 100;
	while(ucLoopTimer_10ms!=0){
		if(IsAC_PowerOff()) { printf("off\r\n"); bExitSysLoop=TRUE; break; }
	}
	
	while(bExitSysLoop == FALSE){
		
		CheckDDC2Bi();

#ifdef NVT_HW_DEBUG
		if(IsNVTDebugActive)	continue;
#endif	

		CheckKey();

		if(bExitSysLoop == TRUE){		//Exit
//			printf("exit\r\n");
			break;
		}			
		
		// Check frequency & sync
		Mode_Check();

		// time out??
		CheckTimer();
		
		Check_DDC_Update();

	//	LEDFlash();

#if FE2P_LIB==ON
		FE2P_Process(0);
#endif
	}

	
	printf("Restart\r\n");

	goto ReStart;
	}	//	end while(1)
}



