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

#include	"..\TopHeader.h"
#include	"math.h"
//#include	<stdlib.h>
#include	"..\power.h"
#include	"..\AutoTuneValue.h"
#include "extern.h"

//****************************************************************//
//함수선언
//****************************************************************//
//In AD9884.c
void SetADCHtotal(WORD Recdata);
void SetADCPhaseReg(BYTE Recdata);
void SetADCColorReg(void);
bit WriteI2C(BYTE sysaddr, BYTE subaddr, BYTE writedata);
void EepromSetQue(WORD address, BYTE Recdata);
void WordWriteScaler(BYTE address, WORD Recdata);
void ArrangeFunctionTable(void);

//In scaler_set.c
#ifdef	USE_4BitInterface								//4bit통신 함수선언
void	WriteReg4bit(BYTE address, BYTE Recdata);
#define	WriteScaler(val1,val2) WriteReg4bit(val1,val2)	
BYTE	ReadScalerParallel(BYTE address);
#define	ReadScaler	ReadScalerParallel

#else													//1bit통신 함수선언
void	WriteReg1bit(BYTE address, BYTE Recdata);
#define	WriteScaler(val0, val1) WriteReg1bit(val0, val1)
BYTE	ReadScalerSerial(BYTE address);
#define	ReadScaler	ReadScalerSerial
#endif


#if defined (MicomXFRbackup) && defined(Mtv230OSDbackup)
extern xdata BYTE xMicomBuffer[57];
#elif defined(MicomXFRbackup)
extern xdata BYTE xMicomBuffer[256];
#endif


/*
		Color & DC level set
		  |
		  |
		Red or Green or Blue Auto start
		  |
		  |
		Red,Green,Blue Left, Right edge read		
		  |
		  |
		Red Left와 Green Left,등등 각각색깔에 대한 edge를 서로 비교한다.
		서로 같이 않으면 phase가 unstable한것으로 간주하여 ADC에 phase를 셋팅하고 다시 auto start과정으로 넘어간다.
		Left,Right를 통해 전제 active size를 산출하여 auto clock을 한다.
*/
#ifdef	OldPhaseSearch
xdata WORD SumPhase[32] _at_	0x0A00;
#else
xdata DWORD SumPhase[32] _at_	0x0A00;
#endif

void AutoDisplayadjust(void)
{
	BYTE idata temp;
	static BYTE idata ChangeDiv;
	#ifdef OldPhaseSearch
	static BYTE idata ChangeDiv;
	DWORD idata SUM_TEMP=0;
	static DWORD	idata SUM =0;
	#else
	DWORD idata SUM_TEMP=0xffffffff;
	static DWORD	idata SUM =0;
	#endif
	
	static BYTE idata ClockCheckCount;
	static WORD idata RealMeasureActive;
	
	#ifdef	PhaseCheckCount
	static BYTE idata AutoPhaseCount;
	#endif
	
	if(!AutoFlag) return;//flag check!!
	if(PowerOnsequence!=GeneralStatus) {AutoFlag=0;AutoProcess=0;return;}	//Normal인경우만 auto-tune
	
	ArrangeFunctionTable();
	
	if( 	CurrentFunction != 0 &&	CurrentFunction != 5 &&		CurrentFunction != 6 &&
			#if defined(USE_SCART)	
			CurrentFunction != 12 &&
			#endif		
			CurrentFunction != 7 )	{AutoFlag=0;AutoProcess=0;return;}		//RGB check!!(RGB모드만 오토실행!!)
	
	
	switch(AutoProcess)
	{
		case 0://OSD, ColorSet, Dc bias, Next set!
			if(!NowTopOsdOn)
			{
				OSDWindows=AutoTuneMainWindow;//OSD display!!
				OSDcharacters=AutoTuneChars;
				OSDstatus=AUTOTuneOSD;
			}

			ADCPHASE = 0;

			WriteI2C(ADC_sysaddress,0x08,~(0x70));	//Red gain		//contrast	//2003-05-30
			WriteI2C(ADC_sysaddress,0x09,~(0x70));	//Green gain
			WriteI2C(ADC_sysaddress,0x0a,~(0x70));	//Blue gain
			
			WriteI2C(ADC_sysaddress,0x0b,(0x7F-80)<<1);	//Red Offset	//brightness
			WriteI2C(ADC_sysaddress,0x0c,(0x7F-80)<<1);
			WriteI2C(ADC_sysaddress,0x0d,(0x7F-80)<<1);
			WriteScaler(0x17,(ModeList[CurrentMode].IHAW >= 1280) ? SXGA_CLOCK_DCvalue : NotSXGA_CLOCK_DCvalue);  // dc bias level for position
			AutoProcess=1;//Next!!
			break;
		
		case 1://auto-tune start
			if(AutoFirst) if((ReadScaler(0x12)&0x01)==0) break;	//auto처음진입시 auto complete은 물어보지 않는다!!//0x12[1]:auto start
			AutoFirst = 1;
			
			++AutoColorSet;
			if(AutoColorSet == 4) AutoColorSet = 1;			//유효AutoColorSet : 1~3
			
			if(ClockCompleted&&!PhaseCompleted) AutoProcess = 5; //Clock->Phase
			else AutoProcess = 2;
			
			switch(AutoColorSet)
			{												//0x12 (auto adjust start bit) = 1로.
				case	1: 	//Red!
					WriteScaler(0x12,BIN_TO_BYTE(1,1,1, 0,0, 0,0,0));									//Auto toggle!
					WriteScaler(0x12,BIN_TO_BYTE(1,1,1, 0,0, 0,1,0));
				break;
				
				case	2: 	//Green!
					WriteScaler(0x12,BIN_TO_BYTE(1,1,1, 0,1, 0,0,0));									//Auto toggle!
					WriteScaler(0x12,BIN_TO_BYTE(1,1,1, 0,1, 0,1,0));
				break;
				
				case	3: 	//Blue!
					WriteScaler(0x12,BIN_TO_BYTE(1,1,1, 1,0, 0,0,0));									//Auto toggle!
					WriteScaler(0x12,BIN_TO_BYTE(1,1,1, 1,0, 0,1,0));
				break;
				default  : break;
			}
			break;
		
		case 2://각 컬러에 대한 에지 체크
			if((ReadScaler(0x12)&0x01)==0) break;//auto complete!!//0x12[1]:auto start
			switch(AutoColorSet)
			{
				case	1: //Red read
					RedL_Edge=RedR_Edge=RedT_Edge=RedB_Edge=0;
					RedL_Edge = (ReadScaler(0x1C)&0x07)<<8|ReadScaler(0x1D);
					RedR_Edge = (ReadScaler(0x1E)&0x07)<<8|ReadScaler(0x1F);
					RedT_Edge = (ReadScaler(0x20)&0x07)<<8|ReadScaler(0x21);
					if(RedT_Edge<=4) RedT_Edge=200;
					AutoProcess = 1;//읽고->auto flag start로.
				break;
				
				case	2: //Grn read
					GrnL_Edge=GrnR_Edge=GrnT_Edge=GrnB_Edge=0;
					GrnL_Edge = (ReadScaler(0x1C)&0x07)<<8|ReadScaler(0x1D);
					GrnR_Edge = (ReadScaler(0x1E)&0x07)<<8|ReadScaler(0x1F);
					GrnT_Edge = (ReadScaler(0x20)&0x07)<<8|ReadScaler(0x21);
					if(GrnT_Edge<=4) GrnT_Edge=200;
					AutoProcess = 1;
				break;
				
				case	3: //Blu read
					BluL_Edge=BluR_Edge=BluT_Edge=BluB_Edge=0;
					BluL_Edge = (ReadScaler(0x1C)&0x07)<<8|ReadScaler(0x1D);
					BluR_Edge = (ReadScaler(0x1E)&0x07)<<8|ReadScaler(0x1F);
					BluT_Edge = (ReadScaler(0x20)&0x07)<<8|ReadScaler(0x21);
					if(BluT_Edge<=4) BluT_Edge=200;
					
					if(!PhaseCompleted) AutoProcess = 3;//R,G,B를 모두 읽으면->active 계산식으로.
					else AutoProcess = 6;//To Position!!
				break;
				
				default	 : break;
			}
			break;
		
		case 3:
			if(AutoColorSet != 3) break;
			if((ReadScaler(0x12)&0x01)==0) break;//auto complete!!//0x12[1]:auto start
			
			//DOSMODE(350,400)인 경우 Clock 조절은 하지 않는다.
			//기본 modetable.c의 클럭을 셋팅해놓는다.//2003-01-29 10:25오전
			if(ModeList[CurrentMode].IVAW==350||ModeList[CurrentMode].IVAW==400)
			{
				ADCPLL = NowHtotal;					//2003-05-30
				SetADCHtotal(NowHtotal-1);	//2003-01-29 10:25오전
				ClockValue=0x80;						//2003-01-29 10:25오전
				ClockCheckCount=0;
				AutoColorSet = 0;
				AutoProcess = 44;
				ClockCompleted=1;
				break;
			}

			if(!PhaseStableSet && (RedL_Edge>2040 || GrnL_Edge>2040 || BluL_Edge>2040))//특정색깔이 존재하지 않거나 phase가 unstable한경우
			if((RedL_Edge != GrnL_Edge)||(RedR_Edge != GrnR_Edge))
			{
				AutoProcess = 1;
				if(ADCPHASE>=32) SetADCPhaseReg(ADCPHASE-32);
				else SetADCPhaseReg(ADCPHASE);
				
				ADCPHASE++;
//				if(ADCPHASE>32*2)//32*2(바퀴)
				if(ADCPHASE>32*3)//32*3(바퀴)
				{
					PhaseStableSet = 1;	
					ADCPHASE = 0;
				}
				break;
			}	//phase가 잘 맞지 않았으면 처음으로..
			PhaseStableSet = 1;	
			
			RedL_Edge=RedL_Edge;	// mean  ?
			RedR_Edge=RedR_Edge;	//?
			if(GrnL_Edge>=BluL_Edge&&BluL_Edge<=RedL_Edge) RedL_Edge=BluL_Edge;
			if(GrnR_Edge<=BluR_Edge&&BluR_Edge>=RedR_Edge) RedR_Edge=BluR_Edge;
			if(RedL_Edge>=GrnL_Edge&&GrnL_Edge<=BluL_Edge) RedL_Edge=GrnL_Edge;
			if(BluR_Edge<=GrnR_Edge&&GrnR_Edge>=RedR_Edge) RedR_Edge=GrnR_Edge;
			
			RealMeasureActive = ((RedR_Edge - RedL_Edge + 1 + 1)/2)	* 2;//측정된 edge..


			
			if((ClockCheckCount>255)||(abs(RealMeasureActive-ModeList[CurrentMode].IHAW)>0x7F))//clock check 128번을 초과시!
		//	if( (ClockCheckCount>=255))
		//		||(abs(ModeList[CurrentMode].IHAW-RealMeasureActive)>10)
			//	||(abs(RealMeasureActive-ModeList[CurrentMode].IHAW)>0x7F) )//clock check 255 초과시!, 영역초과가 20이상, 128초과..
			{
				ClockCheckCount=0;
				ADCPLL = NowHtotal;
				SetADCHtotal(NowHtotal-1);
				AutoColorSet = 0;
				AutoProcess = 44;
				ClockCompleted=1;
				ADCPHASE=0;
				ClockValue=0x80;
				break;
			}
			else if(RealMeasureActive== NowHactive)
			{
				if(abs(ADCPLL-NowHtotal)>0&&abs(ADCPLL-NowHtotal)<=4) ADCPLL=NowHtotal;	//올바르지 못한 패턴에 대한 오토보상??
				ClockCheckCount=0;
				PhaseStableSet = 0;
				SetADCHtotal(ADCPLL-1);
				AutoColorSet = 0;
				AutoProcess = 44;
				ClockCompleted=1;
				ADCPHASE=0;
				ClockValue=0x80+(ADCPLL-NowHtotal);
				break;	//auto clock 끝!!
			}
			if(RealMeasureActive <= NowHactive) ADCPLL = ADCPLL+1;
			else ADCPLL = (WORD)((ADCPLL-1)/2)*2;//Not Odd!!
			
			SetADCHtotal(ADCPLL-1);
			AutoColorSet = 0;
			AutoProcess = 1;	//계산식후->auto flag start로..
			PhaseStableSet = 0;
			++ClockCheckCount;
			break;
	
		case 44://
			WriteScaler(0x17,(ModeList[CurrentMode].IHAW >= 1280) ? SXGA_PHASE_DCvalue : NotSXGA_PHASE_DCvalue);  // dc bias level for position
			AutoProcess = 4;
			break;
	
		case 4://	
			if((ReadScaler(0x12)&0x01)==0) break;	//0x12[1]:auto start //auto complete!!
			
			AutoProcess=1;//1단계로 간다.
			if(ADCPHASE!=32) {WriteI2C(ADC_sysaddress,0x04,ADCPHASE<<3);break;}//위상32단계를 모두 하지 않으면 건너뛴다.
			
			#ifdef OldPhaseSearch
			SUM_TEMP=0;
			#else
			SUM_TEMP=0xffffffff;
			#endif
			SUM=0;
			ADCPHASE=0;
			
			for(temp=0; temp < 32; temp++) 
			{
				#ifdef OldPhaseSearch	//------------------------------------------------------------------
				if(temp==0)    
					SUM = SumPhase[30]+SumPhase[31]+SumPhase[temp]+SumPhase[temp+1]+SumPhase[temp+2];
				else if(temp==1)	 
					SUM = SumPhase[31]+SumPhase[0]+SumPhase[temp]+SumPhase[temp+1]+SumPhase[temp+2];
				else if(temp==30)	  
					SUM = SumPhase[temp-2]+SumPhase[temp-1]+SumPhase[temp]+SumPhase[31]+SumPhase[0];
				else if(temp==31)	  
					SUM = SumPhase[temp-2]+SumPhase[temp-1]+SumPhase[temp]+SumPhase[0]+SumPhase[1];
				else 
					SUM = SumPhase[temp-2]+SumPhase[temp-1]+SumPhase[temp]+SumPhase[temp+1]+SumPhase[temp+2];
				
				if(SUM_TEMP < SUM ) 
				{
					SUM_TEMP = SUM;
					ADCPHASE = temp;
				}	
					
				#else	//-----------------------------------------------------------------------------------
				if(temp==31)	
				{
					SUM = labs(SumPhase[temp]-SumPhase[0]);
				}
				else
				{
					SUM = labs(SumPhase[temp]-SumPhase[temp+1]);
				}
				if(SUM_TEMP > SUM )
				{
					ADCPHASE =	temp;
					SUM_TEMP = SUM;
				}
				#endif	//-----------------------------------------------------------------------------------
			}

			WriteI2C(ADC_sysaddress,0x04,ADCPHASE<<3);

			#ifdef PhaseCheckCount	//------------------------------------------------------------------
			if(++AutoPhaseCount==2)
			{
				AutoPhaseCount=0;
				PhaseValue=ADCPHASE;	
				PhaseCompleted=1;
				WriteScaler(0x17,(ModeList[CurrentMode].IHAW >= 1280) ? SXGA_POSITION_DCvalue : NotSXGA_POSITION_DCvalue);//dc bias level for position //2002-12-03 10:26오전
			}
			else
			{
				AutoColorSet = 0;
				AutoProcess = 44;
				ClockCompleted=1;
				ADCPHASE=0;
			}
			#else	//-----------------------------------------------------------------------------------
			PhaseValue=ADCPHASE;
			PhaseCompleted=1;
			WriteScaler(0x17,(ModeList[CurrentMode].IHAW >= 1280) ? SXGA_POSITION_DCvalue : NotSXGA_POSITION_DCvalue);//dc bias level for position //2002-12-03 10:26오전
			#endif	//-----------------------------------------------------------------------------------
			break;
		
		case 5://
			if((ReadScaler(0x12)&0x01)==0) break;//auto complete!!//0x12[1]:auto start
			switch(AutoColorSet)
			{
				case	1: //Red read
					SUM_TEMP=(DWORD)(ReadScaler(0x18))<<24|(DWORD)(ReadScaler(0x19))<<16|(DWORD)(ReadScaler(0x1a))<<8|(DWORD)(ReadScaler(0x1b));
					SUM=SUM_TEMP;
					AutoProcess = 1;//읽고->auto flag start로.
					break;
				
				case	2: //Grn read
					SUM_TEMP=(DWORD)(ReadScaler(0x18))<<24|(DWORD)(ReadScaler(0x19))<<16|(DWORD)(ReadScaler(0x1a))<<8|(DWORD)(ReadScaler(0x1b));
					SUM=SUM+SUM_TEMP;
					AutoProcess = 1;
					break;
				
				case	3: //Blu read
					SUM_TEMP=(DWORD)(ReadScaler(0x18))<<24|(DWORD)(ReadScaler(0x19))<<16|(DWORD)(ReadScaler(0x1a))<<8|(DWORD)(ReadScaler(0x1b));
					SUM=SUM+SUM_TEMP;
					AutoProcess = 4;//SUM를 모두 읽으면->sum 계산식으로.
					
					#ifdef OldPhaseSearch	//---------------------------------------
					if(!ADCPHASE)
					{
						SUM_TEMP=SUM;
						ChangeDiv=0;
						while(1)
						{
							++ChangeDiv;
							SUM_TEMP = SUM_TEMP>>1;
							if(!SUM_TEMP) break;
						}
					}
					SumPhase[ADCPHASE] = SUM>>(ChangeDiv-11);
					
					#else					//---------------------------------------
					if(!ADCPHASE)
					{
						SUM_TEMP=SUM;
						ChangeDiv=0;
						while(1)
						{
							++ChangeDiv;
							SUM_TEMP = SUM_TEMP>>1;
							if(!SUM_TEMP) break;
						}
					}
					SumPhase[ADCPHASE] = SUM>>(ChangeDiv-11);
					
					//SumPhase[ADCPHASE] = SUM;
					//SumPhase[0] = SUM;
					//PC debug!!
					#if defined (MicomXFRbackup)
					if(ADCPHASE==1)
					{
						xMicomBuffer[0x74] = (BYTE)(SumPhase[1]>>8);
						xMicomBuffer[0x75] = (BYTE)(SumPhase[1]>>0);
						xMicomBuffer[0x76] = (BYTE)(SumPhase[2]>>8);
						xMicomBuffer[0x77] = (BYTE)(SumPhase[2]>>0);
						xMicomBuffer[0x70] = (BYTE)(SUM>>24);
						xMicomBuffer[0x71] = (BYTE)(SUM>>16);
						xMicomBuffer[0x72] = (BYTE)(SUM>>8);
						xMicomBuffer[0x73] = (BYTE)(SUM>>0);
					}
					#endif
					
					#endif					//---------------------------------------
					
					++ADCPHASE;
					break;
			}
			break;
		
		case 6://
			RedL_Edge = RedL_Edge%NowHtotal-38;
			GrnL_Edge = GrnL_Edge%NowHtotal-38;
			BluL_Edge = BluL_Edge%NowHtotal-38;
			
			//H-Position
			if(RedL_Edge<=GrnL_Edge && RedL_Edge<=BluL_Edge )
			{
				if(RedL_Edge>ModeList[CurrentMode].IHAS+0xFF) RedL_Edge = ModeList[CurrentMode].IHAS;//2003-05-30
				WordWriteScaler(0x02,RedL_Edge);;
				//HorizontalValue=RedL_Edge-ModeList[CurrentMode].IHAS+0x80;
				HorizontalValue=ModeList[CurrentMode].IHAS+0x80-RedL_Edge;	//2003-05-30
			}
			else if(GrnL_Edge<=RedL_Edge && GrnL_Edge<=BluL_Edge) 
			{
				if(GrnL_Edge>ModeList[CurrentMode].IHAS+0xFF) GrnL_Edge = ModeList[CurrentMode].IHAS;
				WordWriteScaler(0x02,GrnL_Edge);
				//HorizontalValue=GrnL_Edge-ModeList[CurrentMode].IHAS+0x80;
				HorizontalValue=ModeList[CurrentMode].IHAS+0x80-GrnL_Edge;	//2003-05-30
			}
			else 
			{
				if(BluL_Edge>ModeList[CurrentMode].IHAS+0xFF) BluL_Edge = ModeList[CurrentMode].IHAS;
				WordWriteScaler(0x02,BluL_Edge);
				//HorizontalValue=BluL_Edge-ModeList[CurrentMode].IHAS+0x80;
				HorizontalValue=ModeList[CurrentMode].IHAS+0x80-BluL_Edge;	//2003-05-30
			}
			
			//V-Position
			//2003-05-03 1:38오후
			if(RedT_Edge<=GrnT_Edge && RedT_Edge<=BluT_Edge )
			{
				if(RedT_Edge<=ModeList[CurrentMode].IVAS+50)
				{
					WordWriteScaler(0x06,abs(RedT_Edge-4));
					WordWriteScaler(0x08,abs(RedT_Edge-4));
					VerticalValue=abs(RedT_Edge-4);
				}
				else
				{
					VerticalValue = ModeList[CurrentMode].IVAS;
				}
			}
			else if(GrnT_Edge<=RedT_Edge && GrnT_Edge<=BluT_Edge)
			{
				if(GrnT_Edge<=ModeList[CurrentMode].IVAS+50)
				{
					WordWriteScaler(0x06,abs(GrnT_Edge-4));
					WordWriteScaler(0x08,abs(GrnT_Edge-4));
					VerticalValue=abs(GrnT_Edge-4);
				}
				else
				{
					VerticalValue = ModeList[CurrentMode].IVAS;
				}
			}
			else
			{
				if(BluT_Edge>ModeList[CurrentMode].IVAS+50) BluT_Edge = ModeList[CurrentMode].IVAS;
				WordWriteScaler(0x06,abs(BluT_Edge-4));
				WordWriteScaler(0x08,abs(BluT_Edge-4));
				VerticalValue=abs(BluT_Edge-4);
			}
			
			AutoProcess=7;
			SetADCColorReg();			//color값 원래대로.
			OSDstatus=OSDoff;//OSD Off
			break;
		
		case 7://auto end~~
			AutoFlag = 0;
			AutoFirst = 0;
			AutoColorSet = 0;
			ClockCompleted=0;
			PhaseCompleted=0;
			AutoProcess = 0;			//auto phase 끝!
			PhaseStableSet=0;
			EepromSetQue(CurrentMode*4+0,HorizontalValue);
			EepromSetQue(CurrentMode*4+1,VerticalValue);
			EepromSetQue(CurrentMode*4+2,ClockValue);
			EepromSetQue(CurrentMode*4+3,PhaseValue);
			break;
	}
}
