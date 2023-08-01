#include "8051.H"
#include "MATH.H"
#include "Scaler.H"
#include "AutoAdj.H"
#include "MyDef.H"
#include "IIC.H"
#include "RAM.H"
#include "stdio.h"
#include "F63XREG.H"
#include "F63XDEF.H"
#include "MCU.H"
#include "UserAdj.H"
#include "ModeHandle.H"
#include "ROM_MAP.H"
#include "OSD.H"
#include "Tuner.h"

void TunePositionOnly()
{
	Abort = 0;
	WriteIIC563(0x001,FuncBuf[pRADC]);
	WriteIIC563(0x004,FuncBuf[pGADC]);
	WriteIIC563(0x007,FuncBuf[pBADC]);
	AutoPosition();
	if(Abort)
		{	//fail
		LoadModeDependentSettings();
		SetHP();
		SetVP();
		#if PRINT_MESSAGE
			printf("Auto Position fail\n");
		#endif
		}
	else{		//ok
		SaveModeDependentSettings();
		#if PRINT_MESSAGE
			printf("Auto Position OK\n");
		#endif
		}
	SetContrast();
}

void AutoTune(void)
{
	Word addr;
//	Byte PixelRate;
	Abort = 0;
	NonFullScreen = 0;
	WriteIIC563(0x001,FuncBuf[pRADC]);
	WriteIIC563(0x004,FuncBuf[pGADC]);
	WriteIIC563(0x007,FuncBuf[pBADC]);
//	if(ModePoint < UserModeSt)
//		Recall();
	AutoPosition();
	if(!Abort)
		AutoClock();
//	PixelRate = ((unsigned long)FuncBuf[pCLOCK] * H_SYNC)/10000;
//	if(PixelRate >= PanelMaxPClk/1000)
//		Abort = 1;
	if(NonFullScreen && !Abort)	//non fullscreen recall
		{
		//addr = ep_Sync_Data + (ModePoint * 8);
		//FuncBuf[pCLOCK] = Read24C16(addr+4) << 8;
		//FuncBuf[pCLOCK] |= Read24C16(addr+5);
		LoadPresetModeSettings(2);
		SetADC_PLL();
		}
	CheckAnyKey();
#if 0
	if(Abort){
		if(NonFullScreen == 0){
			//goto Error;
		}
		else{
			Abort = 0;
			AutoClockByPhase(1);
		}
	}
	else{
		AutoClockByPhase(0);
	}
#else
	if(!Abort)
		AutoClockByPhase(0);
#endif
	CheckAnyKey();
	if(!Abort)
		AutoPhaseFineTune(16);
	CheckAnyKey();
	if(!Abort)
		AutoPosition();
	CheckAnyKey();
	if(Abort)
		{	//fail
		Osd_Off();
		//if(ModePoint < UserModeSt)
		//	addr = ModePoint * 8;
		//else
		//	addr = UserModeRefReso * 8;
		LoadPresetModeSettings(0);
		//LoadModeDependentSettings();
		SetADC_PLL();
		SetADC_Phase();
//-------------------------------------------------------
		if(SyncMode != 3)
			{
			SetHP();
			SetVP();
			}
		if(Interlance){
			WriteWordIIC563(0x032,Vresolution);		// Capture V_Active
		}
		else{
			WriteWordIIC563(0x032,Vresolution); 	// Capture V_Active
		}
		WriteWordIIC563(0x036,Hresolution); 	// Capture H_Active
		//WriteWordIIC563(0x036,Hresolution + H_ActErrTab[ResolutionPtr]); 	// Capture H_Active
		//SetScaler();
		//--------------------------------------------------
		addr = ep_Reso_Offset + (ModePoint * 8);
		Write24C16(addr,Read24C16(addr));
		//Write24C16(addr,(Read24C16(addr) & 0x7f));
		#if PRINT_MESSAGE
			printf("AutoTune fail\n");
		#endif
		}
	else{		//ok
		Osd_Off();
		SaveModeDependentSettings();
		//Range.Hpos_Ref = FuncBuf[pHPOSITION];
		//Range.Vpos_Ref = (Byte)FuncBuf[pVPOSITION];
		//Range.Clock_Ref = FuncBuf[pCLOCK];
		//SaveRangeRef();
		Write24C16(ep_Reso_Offset + (ModePoint * 8), ResolutionPtr|0x80);
		#if PRINT_MESSAGE
			printf("AutoTune OK\n");
		#endif
		}
	LoadADC_Gain();
}
#if 0
void AutoPosition(void)
{
	Byte temp;
	#if PRINT_MESSAGE
		printf("AutoPosition\n");
	#endif
	WriteIIC563(0x02A,0);  // AutoPosition Pixel mask -> H
	WriteIIC563(0x02B,24);  // AutoPosition Pixel mask -> H
	WriteIIC563(0x02C,0x00);  // AutoPosition Pixel mask -> H
	WriteIIC563(0x02D,0x00);  // AutoPosition Pixel mask -> H
	WriteIIC563(0x107,0x30);  // Red Noise Margin
	WriteIIC563(0x106,0x00);
	if(SyncMode == 3)
 	 	WriteIIC563(0x106,0x11);
	else
  	 	WriteIIC563(0x106,0x01);
	#if DVImode == HVmode
	if(SyncMode == 3)
		WaitSetup(5);
		//Sleep(50);
	#endif
   	LocalTimer = 10;
   	while((ReadIIC563(0x106) & BIT_0) && LocalTimer != 0)
		{
		CheckModeChange();
		if(Abort)
			return;
		}
   	if(LocalTimer != 0)
		{				// Auto-Position OK
    	FuncBuf[pVPOSITION] = ReadIIC563(0x109) & 0x07;
		FuncBuf[pVPOSITION] <<= 8;
    	FuncBuf[pVPOSITION] |= ReadIIC563(0x108);
    	FuncBuf[pHPOSITION] = ReadIIC563(0x10F) & 0x07;
		FuncBuf[pHPOSITION] <<= 8;
    	FuncBuf[pHPOSITION] |= ReadIIC563(0x10E);
		#if PRINT_MESSAGE
			printf("VP_Start = %d\n",FuncBuf[pVPOSITION]);
			printf("HP_Start = %d\n",FuncBuf[pHPOSITION]);
		#endif
		if(((FuncBuf[pVPOSITION] > 0xff) || (FuncBuf[pHPOSITION] > (FuncBuf[pCLOCK]-H_Act)))&&(SyncMode != 3))
			{
			Abort = 1;			// abort
			#if PRINT_MESSAGE
				printf("AutoPosition fail\n");
			#endif
			}
		else{
			if(ResolutionPtr < 4)
				{
				if(FuncBuf[pVPOSITION] > (VTotal - Vresolution-1))
					FuncBuf[pVPOSITION] = VTotal - Vresolution-14;
				}
			SetHP();
			SetVP();
			}
		}
	else
		{
		Abort = 1;			// abort
		#if PRINT_MESSAGE
			printf("AutoPosition fail\n");
		#endif
		}
   	// wait for next V pulse coming to latch data
	WriteIIC563(0x1ab,BIT_1);
	LocalTimer = 100;
	while(LocalTimer != 0)
		{
		Sleep(1);
		temp = ReadIIC563(0x1ab);
		if(temp & BIT_1)
			break;
		}
}
#endif

void AutoPosition(void)
{
	Word OldVp,NewVp,Vact,Hact;
	#if PRINT_MESSAGE
		printf("AutoPosition\n");
	#endif
	WriteIIC563(0x02A,0);  // AutoPosition Pixel mask -> H
	WriteIIC563(0x02B,24);  // AutoPosition Pixel mask -> H
	WriteIIC563(0x02C,0x00);  // AutoPosition Pixel mask -> H
	WriteIIC563(0x02D,0x00);  // AutoPosition Pixel mask -> H
	WriteIIC563(0x107,0x30);  // Red Noise Margin
	WriteIIC563(0x106,0x00);
	if(SyncMode == 3)
 	 	WriteIIC563(0x106,0x11);
	else
  	 	WriteIIC563(0x106,0x01);
	#if DVImode == HVmode
	if(SyncMode == 3)
		WaitSetup(5);
	#endif
	OldVp = FuncBuf[pVPOSITION];
   	LocalTimer = 100;
   	while((ReadIIC563(0x106) & BIT_0) && LocalTimer != 0)
		{
		CheckModeChange();
		if(Abort)
			return;
		}
   	if(LocalTimer != 0)
		{				// Auto-Position OK
		Hact = ReadWordIIC563(0x110) & 0x0fff;
    	//Hact = ReadIIC563(0x111) & 0x3f;
		//Hact <<= 8;
    	//Hact |= ReadIIC563(0x110);
//		if(Hact < 300)
		if(Hact < Hresolution - 100)
		{
			Abort = 1;
			return;
		}
		FuncBuf[pVPOSITION] = ReadWordIIC563(0x108) & 0x07ff;
    	//FuncBuf[pVPOSITION] = ReadIIC563(0x109) & 0x07;
		//FuncBuf[pVPOSITION] <<= 8;
    	//FuncBuf[pVPOSITION] |= ReadIIC563(0x108);
		GetFuncRange(pVPOSITION);
		if(FuncBuf[pVPOSITION] > FuncMax)//over VPosition Max
		{
			FuncBuf[pVPOSITION] = FuncMax;
			#if PRINT_MESSAGE
				printf("VPositon over Max");
			#endif
		}
		FuncBuf[pHPOSITION] = ReadWordIIC563(0x10e) & 0x07ff;
    	//FuncBuf[pHPOSITION] = ReadIIC563(0x10F) & 0x07;
		//FuncBuf[pHPOSITION] <<= 8;
    	//FuncBuf[pHPOSITION] |= ReadIIC563(0x10E);
		GetFuncRange(pHPOSITION);
		if(FuncBuf[pHPOSITION] > FuncMax)//over VPosition Max
		{
			FuncBuf[pHPOSITION] = FuncMax;
			#if PRINT_MESSAGE
				printf("HPositon over Max");
			#endif
		}

		Vact = ReadWordIIC563(0x10c) & 0x07ff;
    	//Vact = ReadIIC563(0x10d) & 0x07;
		//Vact <<= 8;
    	//Vact |= ReadIIC563(0x10c);
		NewVp = FuncBuf[pVPOSITION];
		#if PRINT_MESSAGE
			printf("VP_Start = %d\n",FuncBuf[pVPOSITION]);
			printf("HP_Start = %d\n",FuncBuf[pHPOSITION]);
		#endif
			
		if(((FuncBuf[pVPOSITION] > 0x40) || ((FuncBuf[pHPOSITION]>>1)  > (FuncBuf[pCLOCK]-Hresolution))||(Vact < 340))&&(SyncMode != 3))
		//if((FuncBuf[pVPOSITION] > 0xff) || ((FuncBuf[pHPOSITION]>>1) > (FuncBuf[pCLOCK]-Hresolution)))
		{
			Abort = 1;			// abort
			#if PRINT_MESSAGE
				printf("AutoPosition fail\n");
			#endif
		}
		else
		{
			//if(ResolutionPtr < 4)
			//	{
			//	if(FuncBuf[pVPOSITION] > (VTotal - Vresolution-1))
			//		FuncBuf[pVPOSITION] = VTotal - Vresolution-14;
			//	}
			SetHP();
			if(ResolutionPtr < 5 && Vact > 300)
			{
				if(NewVp >= (Vresolution - Vact) / 2)
					NewVp = NewVp - (Vresolution - Vact) / 2;
				else
				{
					Abort = 1;
					return;
				}
			}
			if(OldVp > NewVp)
			{
				for(;OldVp>=NewVp;OldVp--)
				{
					FuncBuf[pVPOSITION] = OldVp;
					SetVP();
				}
			}
			else if(OldVp < NewVp)
			{
				for(;OldVp<=NewVp;OldVp++)
				{
					FuncBuf[pVPOSITION] = OldVp;
					SetVP();
				}
			}
			else
			{
				FuncBuf[pVPOSITION] = OldVp;
				SetVP();
			}
		}
	}
	else
	{
		Abort = 1;			// abort
		#if PRINT_MESSAGE
			printf("AutoPosition fail\n");
		#endif
	}
   	// wait for next V pulse coming to latch data
	WaitVblank();
}

void AutoClock()
{
	//preset mode total
	bit FirstDo;
	Byte H_Difference,i,Compare;
	Word H_Ref,H_Act,TempClock;
	#if PRINT_MESSAGE
		printf("AutoClock\n");
	#endif
	TempClock = FuncBuf[pCLOCK];
	if(VTotal > (Vresolution + 190))	//not full screen
		{
		NonFullScreen = 1;
		#if PRINT_MESSAGE
			printf("Non Full Screen");
		#endif
		return;
		}
	H_Ref = Hresolution;
	if(H_Ref >= FuncBuf[pCLOCK])
		{
		Abort = 1;
		FuncBuf[pCLOCK] = H_Ref + FuncBuf[pHPOSITION];
		SetADC_PLL();
//		return;
		}
	WriteWordIIC563(0x117, H_Ref);
	FirstDo = 0;
	for(i=0;i<20;i++)
	{
		WriteIIC563(0x106,0x01);
	   	LocalTimer = 10;
	   	while((ReadIIC563(0x106) & BIT_0) && LocalTimer != 0)
		{
			CheckModeChange();
			if(Abort)
				return;
		}
		H_Act = ReadWordIIC563(0x110) & 0x0fff;
		//H_Act = ReadIIC563(0x111) & 0x0f;
		//H_Act <<= 8;
		//H_Act |= ReadIIC563(0x110);
		
		// 20040224 Jacky
		if(H_Act < (H_Ref - 124)){
			i = 0xff;
			break;
		}
		//------------------------
		H_Difference = ReadIIC563(0x119);
		Compare = (H_Difference & 0xC0) >> 6;
//		H_Difference = (H_Difference & 0x3F);
		H_Difference = (H_Difference & 0x3F) > AutoClock_Step ? AutoClock_Step : (H_Difference & 0x3f); // rev3
		if(Compare == 0){	//H_Act == H_Ref jacky20040326 for AutoPhasebyClock
			if(!FirstDo){
				FirstDo = 1;
				AutoPhaseByClock();
				if(Abort)
					return;
			}
			else
				break;				
		}
		//if(Compare == 0){	//H_Act == H_Ref
		//	break;
		//}
		if(Compare == 1)
		{
			FuncBuf[pCLOCK] += H_Difference;
			if(FuncBuf[pCLOCK] > 2248)// rev3
			{
				i = 0xff;
				break;
			}
		}
		if(Compare == 2 || Compare == 3)
		{
			FuncBuf[pCLOCK] -= H_Difference;
			if(FuncBuf[pCLOCK] < H_Ref)
			{
				i = 0xff;
				break;
			}
		}
		SetADC_PLL();
	}
	//printf("Clock divider 0 = %d\n",FuncBuf[pCLOCK]);
	if(i == 0xff)
	{
	#if PRINT_MESSAGE
		printf("None full screen\n");
	#endif
		Abort = 1;
		NonFullScreen = 1;
		return;
	}
	else
	{
	#if PRINT_MESSAGE
		if(i == 20)
			printf("AutoClock fail.\n");
	#endif
		if(abs(FuncBuf[pCLOCK] - TempClock) > (TempClock / 11))
//			FuncBuf[pCLOCK] = TempClock;
			Abort = 1;
		else
			FuncBuf[pCLOCK] = (FuncBuf[pCLOCK] + 2) & 0xfffc;
		
		GetFuncRange(pCLOCK);
		if(FuncBuf[pCLOCK] > FuncMax)//over VPosition Max
		{
			FuncBuf[pCLOCK] = FuncMax;
	#if PRINT_MESSAGE
				printf("Clock over Max");
	#endif
		}
		
		SetADC_PLL();
	}
}

void AutoClockByPhase(bit h)
{
	bit R_L,U_D;
	Byte k,temp;
	Word GoodClk;
	xdata unsigned long MaxMin,Value;
#if PRINT_MESSAGE
		printf("AutoClockByPhase\r\n");
#endif
//	if((ModePoint < UserModeSt)&&(h == 1)){
//		i = 0x104 + (ModePoint * 8);
//		FuncBuf[pCLOCK] = EEP_SyncMap[i];
//		i++;
//		FuncBuf[pCLOCK] <<= 8;
//		FuncBuf[pCLOCK] += EEP_SyncMap[i];
//	}
	if(h == 1)
		LoadPresetModeSettings(2);

	//printf("Phase ok = %d\n",(unsigned short)FuncBuf[pPHASE]);
	GoodClk = FuncBuf[pCLOCK];
	SetADC_PLL();
	WaitSetup(4);
	if(Abort)
		return;
	//Sleep(25);
	MaxMin = CheckPhaseData();
	//printf("Clock Value Original = %x %x\n",(unsigned short)(MaxMin >> 16),(unsigned short)MaxMin);
	temp = TempPhase;
	if(Abort)
		return;
	U_D = 0;
	R_L = 0;
	for(k=0; k<16; k++)
		{
		if(R_L)
			{
			FuncBuf[pCLOCK] += 2;
			SetADC_PLL();
			//printf("Clock divider 1 = %d\n",FuncBuf[pCLOCK]);
			WaitSetup(4);
			if(Abort)
				return;
			//Sleep(25);
			Value = CheckPhaseData();
			//printf("Clock Value %d = %x %x\n",(unsigned short)k,(unsigned short)(Value >> 16),(unsigned short)Value);
			if(Abort)
				return;
			if(MaxMin < Value)
				{
				GoodClk = FuncBuf[pCLOCK];
				MaxMin = Value;
				temp = TempPhase;
				U_D = 1;
				}
			else
				{
				if(U_D == 0)
					{
					R_L = 0;
					FuncBuf[pCLOCK] -= 2;
					U_D = 1;
					}
				else
					break;
				}
			}
		else{
			FuncBuf[pCLOCK] -= 2;
			SetADC_PLL();
			//printf("Clock divider 2 = %d\n",FuncBuf[pCLOCK]);
			WaitSetup(4);
			if(Abort)
				return;
			//Sleep(25);
			Value = CheckPhaseData();
			//printf("Clock Value %d = %x %x\n",(unsigned short)k,(unsigned short)(Value >> 16),(unsigned short)Value);
			if(Abort)
				return;
			if(MaxMin < Value)
				{
				GoodClk = FuncBuf[pCLOCK];
				MaxMin = Value;
				temp = TempPhase;
				U_D = 1;
				}
			else
				{
				if(U_D == 0)
					{
					R_L = 1;
					FuncBuf[pCLOCK] += 2;
					U_D = 1;
					}
				else
					break;
				}
			}
		}
	FuncBuf[pCLOCK] = GoodClk;
	//printf("Clock divider 3 = %d\n",FuncBuf[pCLOCK]);
	SetADC_PLL();
	FuncBuf[pPHASE] = (temp + 24) & 0x3f;
//	Repeat = 32;
	SetADC_Phase();
}

unsigned long CheckPhaseData()
{
	Byte ch;
	Word zz;
	xdata unsigned long Value,MinValueTemp,MaxValueTemp;
	MaxValueTemp = 0;
	MinValueTemp = 0xffffffff;
	FuncBuf[pPHASE] = 0;
	SetADC_Phase();
	WriteIIC563(0x106,0x02); 
   	LocalTimer = 10;
	for(FuncBuf[pPHASE]=4; FuncBuf[pPHASE]<0x42; FuncBuf[pPHASE] += 4)
		{
		while((ReadIIC563(0x106) & BIT_1) && LocalTimer != 0)
			{
			CheckModeChange();
			if(Abort)
				return 0;
			}
		SetADC_Phase();
		WriteIIC563(0x106,0x02);
	   	LocalTimer = 10;
        Value = 0x00000000;
        for(zz=0x116; zz>0x112; zz--)
			{
       		ch = ReadIIC563(zz);
            Value  = Value << 8;
            Value  = Value + ch;
        	}
		if(Value < MinValueTemp)
			{
			MinValueTemp = Value;
			TempPhase = (FuncBuf[pPHASE] - 4) & 0x3f;
			}
		if(Value > MaxValueTemp)
			MaxValueTemp = Value;
	}
	Value = MaxValueTemp - MinValueTemp;
	return Value;
}

/*
Byte AutoPhase(void)
{
unsigned short	zz;
unsigned char PhaseTemp1,PhaseTemp2,value,i,temp;
unsigned long Value,MinValueTemp,MaxValueTemp;
	if(Abort)
		return 0;
	#if PRINT_MESSAGE
		printf("Auto Phase\n");
	#endif
	MaxValueTemp = 0;
	MinValueTemp = 0xffffffff;
	PhaseTemp1 = 0;
	PhaseTemp2 = 0;
	FuncBuf[pPHASE] = 0;
	SetADC_Phase();
	WriteIIC563(0x106,0x02); // 0X01 --> 0X09
   	LocalTimer = 100;
	for(FuncBuf[pPHASE]=0; FuncBuf[pPHASE]<0x40; FuncBuf[pPHASE] = FuncBuf[pPHASE] + 2)
		{
		while((ReadIIC563(0x106) & BIT_1) && LocalTimer != 0)
			{
			if(Abort)
				return 0;
			}
		SetADC_Phase();
		WriteIIC563(0x106,0x02);
	   	LocalTimer = 100;
        Value = 0x00000000;
        for (zz=0x116; zz>0x112; zz--)
			{
       		value = ReadIIC563(zz);
            Value  = Value << 8;
            Value  = Value + value;
        	}
		i = (FuncBuf[pPHASE] - 2) & 0x3f;
		#if PRINT_MESSAGE
			printf("Phase %d = %x %x\n",(unsigned short)i,(unsigned short)(Value >> 16),(unsigned short)Value);
		#endif
		if(Value < MinValueTemp)
			{
			MinValueTemp = Value;
			PhaseTemp1 = i;
			}
		if(Value > MaxValueTemp)
			{
			MaxValueTemp = Value;
			PhaseTemp2 = i;
			}
		}
	Value = (unsigned long)FuncBuf[pHPOSITION] * H_SYNC;
	if(Value > 1000000)
		{
		i = (PhaseTemp1 + 4) & 0x3f;
		temp = 60;
		}
	else
		{
		i = (PhaseTemp1 + 26) & 0x3f;
		temp = 16;
		}
	FuncBuf[pPHASE] = i;
	SetADC_Phase();
	#if PRINT_MESSAGE
		printf("phase ok = %d\n",(unsigned short)FuncBuf[pPHASE]);
	#endif
	return temp;
}
*/
void AutoPhaseFineTune(Byte Val)
{
unsigned short   zz;
unsigned char   qq,uu,yy,i;
unsigned long   Phase_0, Phase_1, Phase_2, Phase_Pre3, Phase_Now3, Phase_Delta;
unsigned char   value;
	if(Abort)
		return;
    #if PRINT_MESSAGE
	printf("Auto Phase Fine Tune\n");
	#endif
//-------------------------at color xx , calculate phase-------------------------
    Phase_1 = 0x00000000;   // (i-1)
    Phase_2 = 0x00000000;   // (i-2)
    Phase_Pre3 = 0x00000000;   // (pre sum)->(delta)->(now sum)
    Phase_Delta = 0xffffffff;   // (min delta)
	qq = FuncBuf[pPHASE];
	WriteIIC563(0x106,0x02); // 0x01 --> 0x09
   	LocalTimer = 10;
	for(yy=1; yy<Val; yy++)
		{
	 	while((ReadIIC563(0x106) & BIT_1) && LocalTimer != 0)
			{
			CheckModeChange();
			if(Abort)
				return;
			}
		FuncBuf[pPHASE] = (qq + yy) & 0x3f;
		SetADC_Phase();
		WriteIIC563(0x106,0x02); // 0x01 --> 0x09
	   	LocalTimer = 100;
        Phase_Now3  = 0x00000000;
        for (zz=0x116; zz>0x112; zz--)
			{
       		value = ReadIIC563(zz);
            Phase_Now3  = Phase_Now3 << 8;
            Phase_Now3  = Phase_Now3 + value;
        	}
		i = (FuncBuf[pPHASE] - 1) & 0x3f;
		#if PRINT_MESSAGE
			printf("Phase %d = %x %x\n",(unsigned short)i,(unsigned short)(Phase_Now3>>16),(unsigned short)Phase_Now3);	
		#endif
        Phase_2 = Phase_1;  // Shift	
        Phase_1 = Phase_0;
        Phase_0 = Phase_Now3;
		Phase_Now3 = (Phase_0>>1) + (Phase_1>>1) + (Phase_2>>2); // Phase_Now3
		if(yy < 4)
			Phase_Pre3  = Phase_Now3;   // Phase_Pre3 = Phase_Now3
		else
			{
			if(Phase_Now3 > Phase_Pre3)
				Phase_Pre3  = Phase_Now3 - Phase_Pre3;
			else
				Phase_Pre3  = Phase_Pre3 - Phase_Now3;  // Phase_Pre3=delta
			if(Phase_Pre3 < Phase_Delta)
				{
				uu = i;           
				Phase_Delta = Phase_Pre3;
				}
			Phase_Pre3  = Phase_Now3;   // Phase_Pre3 = Phase_Now3
			}     
		}
	FuncBuf[pPHASE] = (uu - 3) & 0x3f;
	SetADC_Phase();
	#if PRINT_MESSAGE
		printf("Phase ok = %d\n",(unsigned short)FuncBuf[pPHASE]);
	#endif
}

void AutoPhaseByClock()
{
	//preset mode total
	Byte PhaseTemp;
	Word H_Act,MinHActiveTemp;
	#if PRINT_MESSAGE
		printf("AutoPhaseByClock\n");
	#endif
	MinHActiveTemp = 0xffff;
	FuncBuf[pPHASE] = 0;
	SetADC_Phase();
	
	for(FuncBuf[pPHASE]=4; FuncBuf[pPHASE]<0x42; FuncBuf[pPHASE] += 4)
	{
		WriteIIC563(0x106,0x01);
	   	LocalTimer = 10;
	   	while((ReadIIC563(0x106) & BIT_0) && LocalTimer != 0)
		{
			CheckModeChange();
			if(Abort)
				return;
		}
		SetADC_Phase();
		H_Act = ReadWordIIC563(0x110) & 0x0fff;
		//H_Act = ReadIIC563(0x111) & 0x0f;
		//H_Act <<= 8;
		//H_Act |= ReadIIC563(0x110);
		
		// 20040224 Jacky
		//if(H_Act < (H_Ref - 124)){
		//	i = 0xff;
		//	break;
		//}
		//------------------------
		if(H_Act < MinHActiveTemp)
		{
			MinHActiveTemp = H_Act;
			PhaseTemp = (FuncBuf[pPHASE] - 4) & 0x3f;
		}
#if PRINT_MESSAGE
		printf("AutoPhaseByClock H_Act %d = %d\n",(unsigned short)FuncBuf[pPHASE],H_Act);
#endif
	}
	FuncBuf[pPHASE] = PhaseTemp;
	SetADC_Phase();
#if PRINT_MESSAGE
		printf("AutoPhaseByClock Phase = %d\n",(unsigned short)FuncBuf[pPHASE]);
#endif
}

#if AUTO_COLOR == GaugeGain
void SetADC_Offset(unsigned char OffSet)
{
	xdata unsigned short l;
	xdata unsigned char i,j,k,m,n,value;
	xdata unsigned long PhaseResult,Temp;
	WriteIIC563(0x0fa,0x00);
	for(m=0; m<3; m++)
		{
		for(k=OffSet; k<128; k=k+8)
			{
			WriteIIC563(0x0f8,0x00);
			l = 0x003 + m*3;
			if(SCRev <= 2)	//Jacky 20041216 rev3
				WriteIIC563(l,k);
			else
				WriteIIC563(l,2*k);
			WaitSetup(5);
			//Sleep(5);
			i = 0x80 + (2-m)*0x08;
			WriteIIC563(0x0f8,i);
			LocalTimer = 10;
		   	while((ReadIIC563(0x0f8) & BIT_7) && LocalTimer != 0)
				{
				if(Abort)
					return;
				}
			if(LocalTimer == 0){
				Abort = 1;
				return;
			}
			j = 0;
			Temp = 0;
			for(i=0; i<8; i++)
				{
				WriteIIC563(0x0f9,i);
				value = ReadIIC563(0x0fd);
				PhaseResult = value;
				PhaseResult <<= 8;
				value = ReadIIC563(0x0fc);
				PhaseResult += value;
				PhaseResult <<= 8;
				value = ReadIIC563(0x0fb);
				PhaseResult += value;
				#if PRINT_MESSAGE
					//printf("PhaseResult %x = %x %x\n",(unsigned short)m,(unsigned short)k,(unsigned short)(PhaseResult>>8));
					printf("PhaseResult %x = %x %x %x\n",(unsigned short)m,(unsigned short)k,(unsigned short)(PhaseResult >> 16),(unsigned short)PhaseResult);
				#endif
				if(PhaseResult > Temp)
					{
					Temp = PhaseResult;
					j = i;
					}
				}
			if(Temp > (Vresolution*15)) //rev3
				{
				l = 0x003 + m*3;
				if(SCRev <= 2)	//Jacky 20041216 rev3
					j = k+j;
				else
					j = 2*(k+j);
				//j = k+j+OffSet2;
				WriteIIC563(l,j);
				#if PRINT_MESSAGE
				printf("Offset %x = %x %x\n",(unsigned short)m,(unsigned short)k,(unsigned short)j);
				#endif
				break;
				}
			}
		for(n=0; n<16; n++)
			{
			WriteIIC563(0x0f8,0x00);
			l = 0x003 + 3*m;
			if(SCRev <= 2)	//Jacky 20041216 rev3
			{
				if(n%2)
					WriteIIC563(l,(k+n/2)+0x80);
				else
					WriteIIC563(l,k+n/2);
			}
			else
				WriteIIC563(l,2*k+n);	// Jacky 20041210
			WaitSetup(2);
			//Sleep(5);
			LocalTimer = 10;
			i = 0x80 + (2-m)*0x08;
			WriteIIC563(0x0f8,i);
		   	while((ReadIIC563(0x0f8) & BIT_7) && LocalTimer != 0)
				{
				if(Abort)
					return;
				}
			if(LocalTimer == 0){
				Abort = 1;
				return;
			}
			j = 0;
			Temp = 0;
			for(i=0; i<8; i++)
				{
				WriteIIC563(0x0f9,i);
				value = ReadIIC563(0x0fd);
				PhaseResult = value;
				PhaseResult <<= 8;
				value = ReadIIC563(0x0fc);
				PhaseResult += value;
				PhaseResult <<= 8;
				value = ReadIIC563(0x0fb);
				PhaseResult += value;
				#if PRINT_MESSAGE
					//printf("PhaseResult %x = %x %x\n",(unsigned short)m,(unsigned short)n,(unsigned short)(PhaseResult>>8));
					printf("PhaseResult %x = %x %x %x\n",(unsigned short)m,(unsigned short)n,(unsigned short)(PhaseResult >> 16),(unsigned short)PhaseResult);
				#endif
				if(PhaseResult > Temp)
					{
					Temp = PhaseResult;
					j = i;
					}
				}
			if(j == 0)
				break;
			}
		l = 0x003 + 3*m;
		if(SCRev <= 2)	//Jacky 20041216 rev3
		{
			if(n%2)
				j = (k+n/2)+0x80;
			else
				j = k+n/2;
		}
		else
			j = 2*k+n;	// Jacky 20041210
		//j = k+n+OffSet2;
		WriteIIC563(l,j);
		#if PRINT_MESSAGE
			printf("Offset %x = %x %x\n",(unsigned short)m,(unsigned short)k,(unsigned short)j);
		#endif
		}
	Temp = ReadIIC563(0x003);
	if(SCRev <= 2)	//Jacky 20041216
		FuncBuf[pROFFSET] = (Temp & 0x7F) * 2 + ((Temp & 0x80) ? 1:0);
	else
		FuncBuf[pROFFSET] = Temp;
	Write24C16(ep_ADC_R_Offset,FuncBuf[pROFFSET]);
//	printf("R offset=%x\r\n",(unsigned short)FuncBuf[pROFFSET]);
	Temp = ReadIIC563(0x006);
	if(SCRev <= 2)	//Jacky 20041216
		FuncBuf[pGOFFSET] = (Temp & 0x7F) * 2 + ((Temp & 0x80) ? 1:0);
	else
		FuncBuf[pGOFFSET] = Temp;
	Write24C16(ep_ADC_G_Offset,FuncBuf[pGOFFSET]);
//	printf("G offset=%x\r\n",(unsigned short)FuncBuf[pGOFFSET]);
	Temp = ReadIIC563(0x009);
	if(SCRev <= 2)	//Jacky 20041216
		FuncBuf[pBOFFSET] = (Temp & 0x7F) * 2 + ((Temp & 0x80) ? 1:0);
	else
		FuncBuf[pBOFFSET] = Temp;
	Write24C16(ep_ADC_B_Offset,FuncBuf[pBOFFSET]);
//	printf("B offset=%x\r\n",(unsigned short)FuncBuf[pBOFFSET]);

//	FuncBuf[pROFFSET] = ReadIIC563(0x003);
//	Write24C16(ep_ADC_R_Offset,FuncBuf[pROFFSET]);
//	FuncBuf[pGOFFSET] = ReadIIC563(0x006);
//	Write24C16(ep_ADC_G_Offset,FuncBuf[pGOFFSET]);
//	FuncBuf[pBOFFSET] = ReadIIC563(0x009);
//	Write24C16(ep_ADC_B_Offset,FuncBuf[pBOFFSET]);
//	WriteIIC563(0x003,Read24C16(ep_ADC_R_Offset));
//	WriteIIC563(0x006,Read24C16(ep_ADC_G_Offset));
//	WriteIIC563(0x009,Read24C16(ep_ADC_B_Offset));
}

void SetADC_Gain(unsigned char OffSet)
{
unsigned short l;
unsigned char i,j,k,m,n,value;
unsigned long PhaseResult,Temp;
	WriteIIC563(0x0f8,0x00);
	WriteIIC563(0x0fa,0xf8);
	for(m=0; m<3; m++)
	{
		for(k=OffSet; k>7; k=k-8)
		{
			l = 0x001 + m * 3;
			WriteIIC563(l,k);
			WriteIIC563(0x0f8,0x00);
			WaitSetup(2);
			//Sleep(5);
			LocalTimer = 10;
			i = 0x80 + (2-m)*0x08;
			WriteIIC563(0x0f8,i);
		   	while((ReadIIC563(0x0f8) & BIT_7) && LocalTimer != 0)
			{
				if(Abort)
					return;
			}
			if(LocalTimer == 0){
				Abort = 1;
				return;
			}
			j = 0;
			Temp = 0;
			for(i=0; i<8; i++)
				{
				WriteIIC563(0x0f9,i);
				value = ReadIIC563(0x0fd);
				PhaseResult = value;
				PhaseResult <<= 8;
				value = ReadIIC563(0x0fc);
				PhaseResult += value;
				PhaseResult <<= 8;
				value = ReadIIC563(0x0fb);
				PhaseResult += value;
				#if PRINT_MESSAGE
					printf("PhaseResult %x = %x %x\n",(unsigned short)m,(unsigned short)k,(unsigned short)(PhaseResult>>8));
				#endif
				if(PhaseResult > Temp)
					{
					Temp = PhaseResult;
					j = i;
					}
				}
			if(Temp > 0x300)
				{
				i = 0x01 + m * 3;
				j = k+j;
//				WriteIIC563(i,j);
				#if PRINT_MESSAGE
					printf("Gain %x = %x %x\n",(unsigned short)m,(unsigned short)k,(unsigned short)j);
				#endif
				break;
			}
		}
		if(k == 0){
			LoadADC_Gain();
			return;
		}
		for(n=0; n<16; n++)
			{
			WriteIIC563(0x0f8,0x00);
			l = 0x001 + m * 3;
			WriteIIC563(l,k-n);
			WaitSetup(2);
			//Sleep(5);
			LocalTimer = 10;
			i = 0x80 + (2-m)*0x08;
			WriteIIC563(0x0f8,i);
		   	while((ReadIIC563(0x0f8) & BIT_7) && LocalTimer != 0){
				if(Abort)
					return;
			}
			if(LocalTimer == 0){
				Abort = 1;
				return;
			}
			j = 0;
			Temp = 0;
			for(i=0; i<8; i++)
				{
				WriteIIC563(0x0f9,i);
				value = ReadIIC563(0x0fd);
				PhaseResult = value;
				PhaseResult <<= 8;
				value = ReadIIC563(0x0fc);
				PhaseResult += value;
				PhaseResult <<= 8;
				value = ReadIIC563(0x0fb);
				PhaseResult += value;
				#if PRINT_MESSAGE
					printf("PhaseResult %x = %x %x\n",(unsigned short)m,(unsigned short)n,(unsigned short)(PhaseResult>>8));
				#endif
				if(PhaseResult > Temp)
					{
					Temp = PhaseResult;
					j = i;
					}
				}
			if(j == 7)
				break;
			}		
		l = 0x001 + m * 3;
		j = k-n+5;
		WriteIIC563(l,j);
		#if PRINT_MESSAGE
			printf("Gain %x = %x %x\n",(unsigned short)m,(unsigned short)k,(unsigned short)j);
		#endif
		}
	FuncBuf[pRADC] = ReadIIC563(0x001);
	Write24C16(ep_ADC_R_Gain,FuncBuf[pRADC]);
//	printf("R gain=%x\r\n",(unsigned short)FuncBuf[pRADC]);
	FuncBuf[pGADC] = ReadIIC563(0x004);
	Write24C16(ep_ADC_G_Gain,FuncBuf[pGADC]);
//	printf("G gain=%x\r\n",(unsigned short)FuncBuf[pGADC]);
	FuncBuf[pBADC] = ReadIIC563(0x007);
	Write24C16(ep_ADC_B_Gain,FuncBuf[pBADC]);
//	printf("B gain=%x\r\n",(unsigned short)FuncBuf[pGADC]);
}

void AutoColor(void)
{

xdata unsigned char r1,g1,b1,m,r2,g2,b2,temp;
	Abort = 0;
	WriteWordIIC563(0x034,FuncBuf[pHPOSITION] - 20);
	SetADC_Offset(0x20);
	m = 0xff;
	if(SCRev <= 2)	//Jacky 20041216
	{
		r1 = ReadIIC563(0x003);
		if(m > r1)
			m = r1;
		g1 = ReadIIC563(0x006);
		if(m > g1)
			m = g1;
		b1 = ReadIIC563(0x009);
		if(m > b1)
			m = b1;
	}
	else
	{
		temp = ReadIIC563(0x003);
		if(SCRev <= 2)	//Jacky 20041216
			r1 = (temp & 0x7F) * 2 + ((temp & 0x80) ? 1:0);
		else
			r1 = temp;
		if(m > r1)
			m = r1;
		temp = ReadIIC563(0x006);
		if(SCRev <= 2)	//Jacky 20041216
			g1 = (temp & 0x7F) * 2 + ((temp & 0x80) ? 1:0);
		else
			g1 = temp;
		if(m > g1)
			m = g1;
		temp = ReadIIC563(0x009);
		if(SCRev <= 2)	//Jacky 20041216
			b1 = (temp & 0x7F) * 2 + ((temp & 0x80) ? 1:0);
		else
			b1 = temp;
		if(m > b1)
			m = b1;
	}
	WriteIIC563(0x034,FuncBuf[pHPOSITION]);
	SetADC_Gain(0x80);
	if(m > 0)
		m = ((m / 8) - 1) * 8 / 2;
	WriteWordIIC563(0x034,FuncBuf[pHPOSITION] - 20);
	SetADC_Offset(m);
	temp = ReadIIC563(0x003);
	if(SCRev <= 2)	//Jacky 20041216
		r2 = (temp & 0x7F) * 2 + ((temp & 0x80) ? 1:0);
	else
		r2 = temp;
	temp = ReadIIC563(0x006);
	if(SCRev <= 2)	//Jacky 20041216
		g2 = (temp & 0x7F) * 2 + ((temp & 0x80) ? 1:0);
	else
		g2 = temp;
	temp = ReadIIC563(0x009);
	if(SCRev <= 2)	//Jacky 20041216
		b2 = (temp & 0x7F) * 2 + ((temp & 0x80) ? 1:0);
	else
		b2 = temp;
	WriteWordIIC563(0x034,FuncBuf[pHPOSITION]);
#if 1
	if(r1 > r2){
		r1 = r1 - r2;
	}
	else{
		r1 = r2 - r1;
	}
	if(g1 > g2){
		g1 = g1 - g2;
	}
	else{
		g1 = g2 - g1;
	}
	if(b1 > b2){
		b1 = b1 - b2;
	}
	else{
		b1 = b2 - b1;
	}
	if((r1 > 2) || (g1 > 2) || (b1 > 2))
		SetADC_Gain(0x80);
#else
	if((r1 != r2) || (g1 != g2) || (b1 != b2))
		SetADC_Gain(0xa0);
#endif

/*
	Abort = 0;
	WriteWordIIC563(0x034,FuncBuf[pHPOSITION] - 20);
	SetADC_Offset(0);
	WriteWordIIC563(0x034,FuncBuf[pHPOSITION]);
	SetADC_Gain(0);
	if(Abort)
		LoadADC_Gain();
*/
}
#else
void SetADC_Offset(unsigned char OffSet2)
{
	unsigned char i,value,rgb[3],Temp;
	unsigned short k;
	WriteIIC563(0x001,0xff);
	WriteIIC563(0x004,0xff);
	WriteIIC563(0x007,0xff);
	rgb[0] = Read24C16(ep_ADC_R_Offset);
	if((rgb[0] > 0xff)||(rgb[0] == 0))
		rgb[0] = 0x40;
	rgb[1] = Read24C16(ep_ADC_G_Offset);
	if((rgb[1] > 0xff)||(rgb[1] == 0))
		rgb[1] = 0x40;
	rgb[2] = Read24C16(ep_ADC_B_Offset);
	if((rgb[2] > 0xff)||(rgb[2] == 0))
		rgb[2] = 0x40;
	WriteADC_Offset(rgb[0],rgb[1],rgb[2]);

	for(k=0; k<256; k++){
		if(OffSet2 != 0)
			WriteIIC563(0x106,0x2a);
		else
			WriteIIC563(0x106,0x2e);
		LocalTimer = 10;
	   	while((ReadIIC563(0x106) & BIT_1) && LocalTimer != 0)
		{
			CheckModeChange();
			if(Abort)
				return;
		}
		i = 0;
		value = ReadIIC563(0x113);
//		printf("%d r = %x\r\n",(unsigned short)k,(unsigned short)value);
		if((value > 2) && (rgb[0] > 0)){
			rgb[0]++;
			i = 0xff;
		}
		if((value == 0) && (rgb[0] < 0xff)){
			rgb[0]--;
			i = 0xff;
		}
		value = ReadIIC563(0x114);
//		printf("%d g = %x\r\n",(unsigned short)k,(unsigned short)value);
		if((value > 2) && (rgb[1] > 0)){
			rgb[1]++;
			i = 0xff;
		}
		if((value == 0) && (rgb[1] < 0xff)){
			rgb[1]--;
			i = 0xff;
		}
		value = ReadIIC563(0x115);
//		printf("%d b = %x\r\n",(unsigned short)k,(unsigned short)value);
		if((value > 2) && (rgb[2] > 0)){
			rgb[2]++;
			i = 0xff;
		}
		if((value == 0) && (rgb[2] < 0xff)){
			rgb[2]--;
			i = 0xff;
		}
		if(i == 0){
			if(OffSet2 != 0){
				rgb[0] = rgb[0] - OffSet2;
				rgb[1] = rgb[1] - OffSet2;
				rgb[2] = rgb[2] - OffSet2;
				WriteADC_Offset(rgb[0],rgb[1],rgb[2]);
			}
			Write24C16(ep_ADC_R_Offset,rgb[0]);
			Write24C16(ep_ADC_G_Offset,rgb[1]);
			Write24C16(ep_ADC_B_Offset,rgb[2]);
			#if PRINT_MESSAGE
			printf("RGB %x;%x;%x\r\n",(unsigned short)rgb[0],(unsigned short)rgb[1],(unsigned short)rgb[2]);
			#endif
			break;
		}
		else{
			WriteADC_Offset(rgb[0],rgb[1],rgb[2]);
			WaitSetup(4);
		}
	}
	Temp = ReadIIC563(0x003);
	if(SCRev <= 2)	//Jacky 20041216
		FuncBuf[pROFFSET] = (Temp & 0x7F) * 2 + ((Temp & 0x80) ? 1:0);
	else
		FuncBuf[pROFFSET] = Temp;
	Write24C16(ep_ADC_R_Offset,FuncBuf[pROFFSET]);
//	printf("R offset=%x\r\n",(unsigned short)FuncBuf[pROFFSET]);
	Temp = ReadIIC563(0x006);
	if(SCRev <= 2)	//Jacky 20041216
		FuncBuf[pGOFFSET] = (Temp & 0x7F) * 2 + ((Temp & 0x80) ? 1:0);
	else
		FuncBuf[pGOFFSET] = Temp;
	Write24C16(ep_ADC_G_Offset,FuncBuf[pGOFFSET]);
//	printf("G offset=%x\r\n",(unsigned short)FuncBuf[pGOFFSET]);
	Temp = ReadIIC563(0x009);
	if(SCRev <= 2)	//Jacky 20041216
		FuncBuf[pBOFFSET] = (Temp & 0x7F) * 2 + ((Temp & 0x80) ? 1:0);
	else
		FuncBuf[pBOFFSET] = Temp;
	Write24C16(ep_ADC_B_Offset,FuncBuf[pBOFFSET]);
//	printf("B offset=%x\r\n",(unsigned short)FuncBuf[pBOFFSET]);
}

void WriteADC_Offset(unsigned char r,unsigned char g,unsigned char b)
{
	if(SCRev <= 2)	//Jacky 20041216
	{
		if(r%2)
			r = r/2+0x80;
		else
			r = r/2;
	}
	WriteIIC563(0x003,r);
	if(SCRev <= 2)	//Jacky 20041216
	{
		if(g%2)
			g = g/2+0x80;
		else
			g = g/2;
	}
	WriteIIC563(0x006,g);
	if(SCRev <= 2)	//Jacky 20041216
	{
		if(b%2)
			b = b/2+0x80;
		else
			b = b/2;
	}
	WriteIIC563(0x009,b);
}

void SetADC_Gain(void)
{
	unsigned char i,value;
	unsigned short k,rgb[3];
	rgb[0] = Read24C16(ep_ADC_R_Gain);
	rgb[1] = Read24C16(ep_ADC_G_Gain);
	rgb[2] = Read24C16(ep_ADC_B_Gain);
	if(rgb[0] > 0x100)
		rgb[0] = 0x80;
	WriteIIC563(0x001,rgb[0]);
	if(rgb[1] > 0x100)
		rgb[1] = 0x80;
	WriteIIC563(0x004,rgb[1]);
	if(rgb[2] > 0x100)
		rgb[2] = 0x80;
	WriteIIC563(0x007,rgb[2]);

	for(k=0; k<256; k++){
		LocalTimer = 10;
		WriteIIC563(0x106,0x2e);
	   	while((ReadIIC563(0x106) & BIT_1) && LocalTimer != 0)
		{
			CheckModeChange();
			if(Abort)
				return;
		}
		i = 0;
//		value = ReadIIC(NT68520_Addr,0x2b);
		value = ReadIIC563(0x113);
//		printf("%d r = %x\r\n",(unsigned short)k,(unsigned short)value);
		if((value == 0xff) && (rgb[0] > 0)){
			rgb[0]++;
			i = 0xff;
		}
		if((value < 0xfd) && (rgb[0] < 0xff)){
			rgb[0]--;
			i = 0xff;
		}
//		value = ReadIIC(NT68520_Addr,0x2c);
		value = ReadIIC563(0x114);
//		printf("%d g = %x\r\n",(unsigned short)k,(unsigned short)value);
		if((value == 0xff) && (rgb[1] > 0)){
			rgb[1]++;
			i = 0xff;
		}
		if((value < 0xfd) && (rgb[1] < 0xff)){
			rgb[1]--;
			i = 0xff;
		}
//		value = ReadIIC(NT68520_Addr,0x2d);
		value = ReadIIC563(0x115);
//		printf("%d b = %x\r\n",(unsigned short)k,(unsigned short)value);
		if((value == 0xff) && (rgb[2] > 0)){
			rgb[2]++;
			i = 0xff;
		}
		if((value < 0xfd) && (rgb[2] < 0xff)){
			rgb[2]--;
			i = 0xff;
		}
		if(i == 0){
//			rgb[0] = rgb[0] + 1;
//			rgb[1] = rgb[1] + 1;
//			rgb[2] = rgb[2] + 1;
//			WriteIIC(NT68520_Addr,0x02,rgb[0]);
//			WriteIIC(NT68520_Addr,0x04,rgb[1]);
//			WriteIIC(NT68520_Addr,0x06,rgb[2]);
			Write24C16(ep_ADC_R_Gain,rgb[0]);
			Write24C16(ep_ADC_G_Gain,rgb[1]);
			Write24C16(ep_ADC_B_Gain,rgb[2]);
//			printf("RGB %x;%x;%x\r\n",(unsigned short)rgb[0],(unsigned short)rgb[1],(unsigned short)rgb[2]);
			break;
		}
		else{
			WriteIIC563(0x001,rgb[0]);
			WriteIIC563(0x004,rgb[1]);
			WriteIIC563(0x007,rgb[2]);
			WaitSetup(4);
		}
	}
	FuncBuf[pRADC] = ReadIIC563(0x001);
	Write24C16(ep_ADC_R_Gain,FuncBuf[pRADC]);
//	printf("R gain=%x\r\n",(unsigned short)FuncBuf[pRADC]);
	FuncBuf[pGADC] = ReadIIC563(0x004);
	Write24C16(ep_ADC_G_Gain,FuncBuf[pGADC]);
//	printf("G gain=%x\r\n",(unsigned short)FuncBuf[pGADC]);
	FuncBuf[pBADC] = ReadIIC563(0x007);
	Write24C16(ep_ADC_B_Gain,FuncBuf[pBADC]);
//	printf("B gain=%x\r\n",(unsigned short)FuncBuf[pBADC]);
}
/*
void AutoColor(void)
{
	//WriteIIC563(0x02A,0);  // AutoPosition Pixel mask -> H
	//WriteIIC563(0x02B,24);  // AutoPosition Pixel mask -> H
	//WriteIIC563(0x02C,0x00);  // AutoPosition Pixel mask -> H
	//WriteIIC563(0x02D,0x00);  // AutoPosition Pixel mask -> H
	//WriteIIC563(0x107,0x30);  // Red Noise Margin
	//WriteIIC563(0x106,0x00);
	WriteWordIIC563(0x034,FuncBuf[pHPOSITION] - 10);
	SetADC_Offset(2);
	SetADC_Gain();
	WriteWordIIC563(0x034,FuncBuf[pHPOSITION]);
}

*/

#endif
//////////////////////////////////////////////////////////////////////////////

void CheckRCV(void)
{
unsigned char i;
	if(RI == 1){
		i = SBUF;
	//	printf("Recieved data\n");
		RI = 0;
		CheckCmd(i);
	}
}

void CheckCmd(unsigned char i)
{
	while(TI == 0){}
	SBUF = i;
	TI = 0;
	if(i == 13){		//command over
		while(TI == 0){}
//		printf("\n");
		switch(rwbuf){
		case 0x00:
//			printf("\r\n");
//			printf("W0 aaaa dd : Write 24C16\r\n");
//			printf("R0 aaaa    : Read  24C16\r\n");
//			printf("W1 aaaa dd : Write Scaler\r\n");
//			printf("R1 aaaa    : Read  Scaler\r\n");
//			printf("W2 aaaa dd : Write rgbGain\r\n");
//			printf("R2 aaaa    : Read  rgbGain\r\n");
//			printf("W3 aaaa dd :Z86229 0x%x \r\n");
//			printf("R3 aaaa    : Read  TW9908\r\n");
//			printf("R4 0       : Auto Black Level\r\n");
//			printf("R4 1       : Auto White Level\r\n");
//			printf("R4 2       : Auto Color\r\n");
//			printf("R4 3       : Set 6500K\r\n");
//			printf("R4 4       : Set 7500K\r\n");
//			printf("R4 5       : Set 9300K\r\n");
//			printf("R4 6       : Resive\r\n");
//			printf("R4 7       : DDC Write Enable\r\n");
		//	printf("R4 8       : Disable Report Status\r\n");
		//	printf("R4 9       : Enable Report Status\r\n");
//			printf("R4 a       : Enable CheckVideo\r\n");
//			printf("R4 b       : Disable CheckVideo\r\n");
		//	printf("W4 0 dd    : Set IIC BaudRate\r\n");
//			printf("   aaaa    : 16/8  bit Address\r\n");
//			printf("   dd      : 8     bit Data\r\n");
//			printf("Enter Key  : For help!\r\n");
			break;
		case 0xe0:
			Write24C16(abuf,dbuf);
//			printf("EEPROM: 0x%x = 0x%x\r\n",abuf,(unsigned short)dbuf);
			break;
		case 0xc1:
			dbuf = Read24C16(abuf);
//			printf("EEPROM: 0x%x = 0x%x\r\n",abuf,(unsigned short)dbuf);
			break;
		case 0xe2:
			abuf &= 0x1ff;
			WriteIIC563((unsigned short)abuf,dbuf);
//			printf("Scaler: 0x%x = 0x%x\r\n",(unsigned short)abuf,(unsigned short)dbuf);
			break;
		case 0xc3:
			abuf &= 0x1ff;
			dbuf = ReadIIC563((unsigned short)abuf);
//			printf("Scaler: 0x%x = 0x%x\r\n",(unsigned short)abuf,(unsigned short)dbuf);
			break;
		case 0xe4:
			abuf &= 0x03;
			switch(abuf){
			case 0:
				FuncBuf[pRCOLOR] = dbuf;
				break;
			case 1:
				FuncBuf[pGCOLOR] = dbuf;
				break;
			case 2:
				FuncBuf[pBCOLOR] = dbuf;
				break;
			}
//			printf("rgbGain : %x = %x\r\n",(unsigned short)abuf,(unsigned short)dbuf);
//			SetContrast();
		//	sRGB(FuncBuf[pCONTRAST],FuncBuf[pRCOLOR],FuncBuf[pGCOLOR],FuncBuf[pBCOLOR]);
			CmdTxBuffer[0] = 0x5a;
			break;
		case 0xc5:
			abuf &= 0x03;
			switch(abuf){
			case 0:
				dbuf=FuncBuf[pRCOLOR];
			//dbuf = R_Gain;
				break;
			case 1:
				dbuf = FuncBuf[pGCOLOR];
			//	dbuf = G_Gain;
				break;
			case 2:
				dbuf = FuncBuf[pBCOLOR];
			//	dbuf = B_Gain;
				break;
			}
//			printf("rgbGain : %x = %x\r\n",(unsigned short)abuf,(unsigned short)dbuf);
			break;
		case 0xe6:
			abuf &= 0x0ff;
			WriteIIC(TW990x_Addr,(unsigned char)abuf,dbuf);
//			printf("SAA7114: 0x%x = 0x%x\r\n",abuf,(unsigned short)dbuf);
//			SetCaptionTextDispMode((unsigned char)abuf);
//			printf("Z86229 0x%x \r\n",abuf);
			break;
		case 0xc7:
			abuf &= 0x0ff;
//			dbuf = ReadIIC_HW(SAA7114,(unsigned char)abuf);
//			SetCaptionTextDispMode((unsigned char)abuf);
//			printf("Z86229 0x%x \r\n",abuf);
			dbuf = ReadIIC(TW990x_Addr,(unsigned char)abuf);
//			printf("TW9908: 0x%x = 0x%x\r\n",abuf,(unsigned short)dbuf);
			break;
		case 0xc9:
			abuf &= 0x0ff;
			switch(abuf){
			case 0:
//				flag3 &= ~BIT_0;	//burn in mode off
//				flag3 &= ~BIT_2;	//disable report
//				Brightness = 50;
//				SetBrightness();
//				Contrast = 50;
//				sRGB();
				SetADC_Offset(0x00);
//				printf("Set Dark OK!\r\n");
				CmdTxBuffer[0] = 0x5a;
				break;
			case 1:		//white
				SetADC_Gain(0xf8);
//				printf("Set white OK!\r\n");
				CmdTxBuffer[0] = 0x5a;
				break;
			case 2:		//Auto Color
				AutoColor();
//				printf("Set Auto Color OK!\r\n");
				CmdTxBuffer[0] = 0x5a;
				break;
			case 3:		// user and 6500K
				Write24C16(ep_Color4_R,FuncBuf[pRCOLOR]);	//user
				Write24C16(ep_Color4_G,FuncBuf[pGCOLOR]);
				Write24C16(ep_Color4_B,FuncBuf[pBCOLOR]);
//				printf("Write USER\r\n");
				Write24C16(ep_Color1_R,FuncBuf[pRCOLOR]);	//6500K
				Write24C16(ep_Color1_G,FuncBuf[pGCOLOR]);
				Write24C16(ep_Color1_B,FuncBuf[pGCOLOR]);
//				printf("Write 6500K\r\n");
				CmdTxBuffer[0] = 0x5a;
				break;
//				Write24C16(0xee,R_Gain);	//user
//				Write24C16(0xef,G_Gain);
//				Write24C16(0xf0,B_Gain);
//				printf("Write USER\r\n");
//				Write24C16(0xf1,R_Gain);	//6500K
//				Write24C16(0xf2,G_Gain);
//				Write24C16(0xf3,B_Gain);
//				printf("Write 6500K\r\n");
//				CmdTxBuffer[0] = 0x5a;
//				break;

			case 4:		//7500K
				Write24C16(ep_Color2_R,FuncBuf[pRCOLOR]);	//7500K
				Write24C16(ep_Color2_G,FuncBuf[pGCOLOR]);
				Write24C16(ep_Color2_B,FuncBuf[pBCOLOR]);
//				printf("Write 7500K\r\n");
				CmdTxBuffer[0] = 0x5a;
				break;
			case 5:		//9300K
//				Write24C16(0xf7,R_Gain);	//9300K
//				Write24C16(0xf8,G_Gain);
//				Write24C16(0xf9,B_Gain);
			//	PowerStatus++;
//				FuncBuf[pVIDEOSOURCE]++;
//				SourceSelect();
//				printf("source change\r\n");
				CmdTxBuffer[0] = 0x5a;
				FactMode = 1;
				
				break;
//			case 4:		//7500K
////				Write24C16(0xf4,R_Gain);	//7500K
//				Write24C16(0xf5,G_Gain);
//				Write24C16(0xf6,B_Gain);
//				printf("Write 7500K\r\n");
//				CmdTxBuffer[0] = 0x5a;
//				break;
//			case 5:		//9300K
//				Write24C16(0xf7,R_Gain);	//9300K
//				Write24C16(0xf8,G_Gain);
//				Write24C16(0xf9,B_Gain);
//				PowerStatus++;
//				SourceSelect();
//				printf("source change\r\n");
//				CmdTxBuffer[0] = 0x5a;
//				break;			
			case 6:		//Auto adjust
//				AutoTune();
//				AutoClockByPhase();
//				printf("Auto adjust\r\n");
				ScanChannel();
				CmdTxBuffer[0] = 0x5a;
				break;
	//		case 8:
	//			flag3 &= ~BIT_2;		//Disable report
	//			printf("Disable Report Status\r\n");
	//			break;
	//		case 9:
	//			flag3 |= BIT_2;		//Set report
	//			printf("Report Status\r\n");
	//			break;
			case 0x0a:
				VideoTest = 1;
//				printf("Set Video test= 1\r\n");
				break;
			case 0x0b:		
				VideoTest = 0;
//				printf("Set Video test= 0\r\n");
				break;			
			}
			break;
	//	case 0xe8:		//Set IIC Baudrate
	//		dbuf &= 0x03;
	//		dbuf <<= 2;
	//		IIC_BaudRate = dbuf;
	//		printf("Set IIC Baudrate: %x\r\n",(unsigned short)dbuf);
	//		break;
		default:
			RcvError();
			return;
			break;
		}
		rwbuf = 0;
		abuf = 0;
		dbuf = 0;
//		printf("OK\r\n");
		return;
	}
	if((rwbuf & 0x80) == 0){	//function
		switch(i){
		case 0x30:
		case 0x31:
		case 0x32:
		case 0x33:
		case 0x34:
			i = i & 0x0f;
			i = i << 1;
			rwbuf = rwbuf + i;
			rwbuf |= 0x80;
			break;
		case 0x57:		//W
		case 0x77:		//w
			rwbuf &= 0xfe;
			break;
		case 0x52:		//R
		case 0x72:		//r
			rwbuf |= 0x01;
			break;
		default:
//			printf("\r\n");
			RcvError();
			break;
		}
	}
	else{		//address or data
		if(i == 0x20){
			if((rwbuf & 0x40) == 0){
				rwbuf |= 0x40;
			}
			else{
				if((rwbuf & 0x20) == 0){
					rwbuf |= 0x20;
				}
				else{
					RcvError();
				}
			}
			return;
		}
		if((i > 0x2f)&&(i < 0x3a)){
			i &= 0x0f;
		}
		else{
			if(i > 0x60){
				i = i - 0x20;
			}
			if(i > 0x40){
				i = i - 0x07;
			}
			if((i > 0x39)&&(i < 0x40)){
				i &= 0x0f;
			}
			else{
				RcvError();
				return;
			}
		}
		if((rwbuf & 0x60) == 0x40){
			abuf <<= 4;
			abuf += i;
		}
		if((rwbuf & 0x60) == 0x60){
			dbuf <<= 4;
			dbuf += i;
		}
	}
}

void RcvError(void)
{
	while(TI == 0){}
//	printf("\nError\r\n");
	rwbuf = 0;
	abuf = 0;
	dbuf = 0;
}
