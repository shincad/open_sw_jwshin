//-----------------------------------------
#ifndef _TUNER_H_
//-----------------------------------------
#define  _TUNER_H_

/*
//------���Ǵ� Ʃ�ʸ� CURRENT_TUNNER�� ������ ���־�� �Ѵ�.-------> �̺κ��� �����ؾ� �Ǵ� �κ���.
#define SAMSUNG_TCPN9082DA27C		1	//SAMSUNG NTSC ����Ʃ��, PHILIPS ����Ʃ�ʵ� �̰����� �����Ѵ�.
#define LGINOTEK_TAPC_H701F		2	// LGINOTEK����Ʃ��
#define SAMSUNG_TCPQ9091PD27D		3	// SamSung NTSC ���� Ʃ��.
#define SAMSUNG_TCPQ9091PD28L		4	// SamSung PAL ���� Ʃ��.
#define CURRENT_TUNNER				SAMSUNG_TCPQ9091PD27D	//SAMSUNG NTSC ����Ʃ��
*/


//--------�Ʒ��� DEFINE�� AFT�ÿ� ����� ����鿡 ���� �������̴�.--> �ǵ� �ʿ�� ����.
#define SAMSUNG			1	//Ʃ�� ������.
#define LGINOTEK		2	//Ʃ�� ������.
#define PHILLIPS		3	//Ʃ�� ������.

#if( (CURRENT_TUNNER==SAMSUNG_TCPN9082DA27C)||	(CURRENT_TUNNER==SAMSUNG_TCPQ9091PD27D))
 	#define TUNER_MANUFACTURER		SAMSUNG
#elif( CURRENT_TUNNER==LGINOTEK_TAPC_H701F)
 	#define TUNER_MANUFACTURER		LGINOTEK
#endif



#define	AUTO_SETUPDEBUG	0
#define	TOTAL_CHANNEL_SEARCH_RS232	0


// if( TUNER_MANUFACTURER==SAMSUNG)
// if( TUNER_MANUFACTURER==LGINOTEK)

//-------------------
// �Ʒ��� �����ʹ� BandSwitching�� �ϱ� ���ϱ� ���� PLL Reference�����ͷμ� ���ȴ�.(2003.1.16�� Fix)
#define VHF 0x1090	// 166.25Mhz	//ntsc LGINOTEK_TAPC_H701F�� �� ��.
#define UHF 0x2698	// 448.25Mhz	//ntsc LGINOTEK_TAPC_H701F�� �� ��.

#define VHF1 0x1075	// 171.25Mhz	//pal multi SAMSUNG_TCPQ9091PD28L�� �� ��.
#define UHF1 0x287A	// 467.25Mhz	//pal multi SAMSUNG_TCPQ9091PD28L�� �� ��.
//---------------------
// Tuner AFT�� �����ϱ� ���� ���ػ���μ� ����Ѵ�.
#define AFT_OVER 	0x04		// �� Ʃ�� �������� +100Khz�̻����� Ʃ�׵� ��� .
#define AFT_50P 	0x03		// �� Ʃ�� �������� +50Khz�̻����� Ʃ�׵� ��� .
#define AFT_OK 		0x02		// �� Ʃ�� ��  ���. 
#define AFT_50M 	0x01		// �� Ʃ�� �������� -50Khz���� �� Ʃ�׵� ���.
#define AFT_UNDER 	0x00		// �� Ʃ�� �������� -100Khz���� �� Ʃ�׵� ���.

#define AFT_4 0x04		// �� Ʃ�� �������� +100Khz�̻����� Ʃ�׵� ��� .
#define AFT_3 0x03		// �� Ʃ�� �������� +50Khz�̻����� Ʃ�׵� ��� .
#define AFT_2 0x02		// �� Ʃ�� ��  ���. 
#define AFT_1 0x01		// �� Ʃ�� �������� -50Khz���� �� Ʃ�׵� ���.
#define AFT_0 0x00		// �� Ʃ�� �������� -100Khz���� �� Ʃ�׵� ���.

//---------------------
// Tuner�� ������ ���� �ð��� ���� 
#define TUNER_STABLE_TIME 0x04
#define	NTSCColorSystem	ColorSystem&NTSC

#define sntsc_VHF 0x1090	
#define sntsc_UHF 0x2710	

#ifdef TunerRefDiv512	//---------------------------
#define spal_VHF 0x0A84
#define spal_UHF 0x1CF4
#else					//---------------------------
#define spal_VHF 0x1075	
#define spal_UHF 0x278a	
#endif
//----------------
void ShowSource(void);
void WriteTuner(unsigned char DivH,unsigned char DivL,unsigned char Band);
void WriteTun1(unsigned char DivH,unsigned char DivL,unsigned char Band);
unsigned char ReadTuner(void);
void SetTuner(unsigned int);
//void SetTuner1(unsigned int);
void ChannelSel(unsigned char);
void Pre_ChannelSel(unsigned char);
Bool ToggleChMask();
bit CheckChMask(BYTE channel);
bit CheckChCATV(BYTE channel);
bit CheckChFineTune(BYTE channel);
bit CheckChAFT(BYTE channel);
bit CheckChNotUSE(BYTE channel);

void CatvAirSelection(bit Selection);
BYTE GetRealChannel(BYTE channel);

void ViewCurrentChannel(void);

void idelay5m(BYTE time);

void TunnerInitialize(void);
BYTE AFT(unsigned int,BYTE);	// 1.17
BYTE SimpleAFT(unsigned int Divider,BYTE);
BYTE AFTPal(unsigned int Divider,BYTE);
void SimpleSearch(void);
void TunerTest(void);
BYTE GetFineTune(BYTE);
void  SetFineTune(BYTE channel,BYTE value);
BYTE  CalDispchannel(void);
void SetFinePLL(BYTE ch,BYTE FineTune);
void SetManualTune(BYTE channel);
//void SetColorSystem() ;
void TVParameterInit();
void TVCountrySet();

/*
void SetChannelStatus(BYTE channel,BYTE Value);
bit ToggleChMask(void);	// 1��16�� // by Lee 2.1
WORD GetPLLValue(void);
BYTE AftSubFunction( WORD AFTDivider, BYTE AFTValue, bit Test);
void AutoSearchChannel(bit simple);
*/

#if (TOTAL_CHANNEL_SEARCH_RS232==1)
void TunerTestSearch(void);
#endif

//code BYTE  AftRangeTable[];	// 4/15 by LKE
//code BYTE  CatvLimitTable[];
//code BYTE  TvLimitTable[];


//#define LCDMute(_x_,_y_)
//#define LCDMuteOff()	

#define	BIT_7	0x80
#define BIT_6	0x40
#define BIT_5	0x20
#define BIT_4	0x10
#define BIT_3	0x08
#define BIT_2	0x04
#define BIT_1   0x02
#define BIT_0	0x01

#if defined(USE_NTSCtuner)
#define	NTSC_COUNTRY	1
#else
#define	NTSC_COUNTRY	0
#define	CHANNELMEMORYMAX	100
#endif

#define	FALSE	0
#define	TRUE	1

#define	ANTENA_AIR		0
#define	ANTENA_CABLE	1

#if (CURRENT_TUNNER==LGINOTEK_TAPC_H701F)
#define	TunerAddr	0xC0
#else
#define	TunerAddr	0xC2
#endif

// Tuner�� Audio System�� �����ϱ� ����Parameter�� ����Ѵ�.
#define BTC_NTSC		0x20
#define BTC_NTSC_M		0x21
#define BTC_NTSC_JPN	0x22

#define	BTC_PAL			0x40
#define	BTC_PAL_BG		0x41
#define	BTC_PAL_I		0x42
#define	BTC_PAL_DK		0x43

#define	BTC_SECAM		0x80
#define	BTC_SECAML		0x81
//#define	SECAMLL	0x82
#define	BTC_SECAMDK		0x82
#define	BTC_SECAMLL		0x83


#define ep_Page(a)		(0xA0+(((a)/256)*2))
#define ep_Addr(b)		((b)%256)

#define	SourceType xEEPROMBuffer[TVMODE]

#define	PRMEMNUM	8
#define EnableAIR	0x00
#define EnableCATV	0x02
#define DisableAIR	0x01//0x00|0x01
#define DisableCATV	0x03//0x02|0x01
//-----------------------------------------
#endif
//-----------------------------------------