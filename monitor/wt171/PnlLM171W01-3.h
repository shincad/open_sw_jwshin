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

/*
FrameMode���� �ǳڴ������
�ϴ��� �Ķ�����߿��� ���� �Ķ���͸� �����Ѵ�.
1)	PanelMinHTotal-->"1" DE�ֱ���� Clock����
2)	PanelMaxHTotal-->default "2047"
3)	PanelMinVTotal-->"1" V�ֱ���� DE����
4)	PanelHerizontalsize-->panle V active size
5)	PanelVerticalsize-->panel H active size

6~9�׸��� OH�� ���� DE ��������Ʈ(OUTDCLK����), OH sync width
		  OV�� ���� DE ��������Ʈ(DE����), OV sync width
6)	DFLT_OHSYNCEND
7)	DFLT_OHACTIVESTART
8)	DFLT_OVSWIDTH
9)	DFLT_OVACTIVESTART

10)	PanelVSHSDisplace-->default "0"

11)	PanelDualData-->1: Dual
12)	PanelDataSwap-->��� A,B swap

13)	BIHAW-->B input H active size
14)	BIVAW-->B input V active size

* ->�߰��Ұ�.
15)	*8bit,6bit Panel-->0x51 bit4(if 6bit panle "1")
16)	*OutputHs Neg/Pos , OutputVs Neg/Pos
17)	*Dithering-->0x5e bit1(if 6bit panle "1")
*/

#define 	PanelMinHTotal          	1408//1344//set Panel min Htotal size
#define		PanelMaxHTotal			2047
#define 	PanelMinVTotal          	806//1032//1050//1032		//set Panel Vtotal size
#define 	PanelHerizontalsize         1280
#define 	PanelVerticalsize           768
#define		SXGA_Panel

#define 	PanelHSWidth				6
#define		DFLT_OHSYNCEND				((PanelHSWidth+2+3)/4)
#define		REAL_OHSWIDTH				(DFLT_OHSYNCEND*4-2)
#define		DFLT_OHACTIVESTART			(REAL_OHSWIDTH+2+1+PanelHBackPorch)	//must odd for background
#define 	PanelHBackPorch				6//4			//&&&&must even value for odd active start(for use bkg match)

#define 	PanelVSWidth				1
#define 	PanelVBackPorch				2
#define 	DFLT_OVSWIDTH				(PanelVSWidth+1)
#define 	DFLT_OVACTIVESTART			(DFLT_OVSWIDTH+PanelVBackPorch+1)

#if	defined(EMH1A)
#define		PanelVSHSDisplace			0
#elif defined(EMH2)
#define		PanelVSHSDisplace			4
#else
#define		PanelVSHSDisplace			0
#endif

#define		PanelDualData				0		//if 1 Dual Panel ,else "0" single panel
#define		PanelDataSwap				0		//ATEC LM181E05, //if 1 output swap,else "0" not swap

#define		Panel_8bit_OR_6bit			0		//if 1 6bit, else "0" 8bit, ���&������Բ� �����Ѵ�.
#define		OutputHsync_Neg_OR_Pos		1		//if 1 negative, else "0" positive(negative:low level ���� ������)
#define		OutputVsync_Neg_OR_Pos		1		//if 1 negative, else "0" positive(negative:low level ���� ������)
#define		OutputDE_Neg_OR_Pos			0		//if 1 negative, else "0" positive(negative:low level ���� ������)


#if	defined(USE_NTSCtuner)
#define		BIHAW						700
#define		BIVAW						230

#elif defined(USE_PALSECAMtuner)
#define		BIHAW						700
#define		BIVAW						250//274

#else
#define		BIHAW						700
#define		BIVAW						230
#endif