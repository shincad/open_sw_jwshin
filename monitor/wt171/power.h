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

   2003-01-10 2:39����  JDHAN           Modified for Monitor-TV
****************************************************************************/

//Power on sequence
#define NoSignalCheckTime		150	//300*5ms���� ����ȣ�� ����.
#define	SyncSignalStableTime 		30	//100*5���� ���ļ�ä�͸��� äũ�Ѵ�.


//Power on sequence
#define	MainPowerON			5
#define	WaitEepromInitialize 		6
#define	DevicestableWait		7
#define	DecoderStableWait		8
#define	PanelPowerON			9
#define	PanelLVDSON			10
#define	PanelInvertPwmON		11
#define	PowerOnNormalStatus		12
#define	ScalerstableWait		13
#define	MenuValueLoadandApply		14
#define	NormalDisplayPrepare		15
#define	DisplayLightOnstatus 		16
#define	GeneralStatus			17
#define	FreeRunStatus			21
#define	OutOfFreqStatus			22
#define	CheckCableMessage		23
#define	OnlyLedOnOffStatus		24
#define	DPMSOff				25
#define	DPMSLedOnOff			26
#define	WakeUpFreeRun			27
#define	BeforeFreeRunScalerInit		28
#define	BeforeCheckCableScalerInit	29
#define	BeforeNoVideoScalerInit		30
#define	AfterNoVideoScalerInit		31
#define	NoVideoStatus			32


//Power off sequence
#define	PanelInvertOFF			5
#define	PanelInvertPwmOFF		6
#define	PanelPowerOFF			7
#define	MainPowerOFF			8
#define	PowerOffNormalStatus		9
#define	SystemInitstatus		10


void InvertSmartStart();
void InvertSmartStop();
