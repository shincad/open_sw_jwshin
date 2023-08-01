
#ifndef __OSD_LF_H__
#define __OSD_LF_H__

// LF OSD Obj
enum LF_OSD_ITM {
	mLFMODE_OFFICE,
	mLFMODE_IMAGE,
	mLFMODE_ENTERTAINMENT,
	mLFMODE_ECONOMIC,
	mLFMODE_OFF,
	NUM_LF_MODE
};
enum LF_CUSOSD_LV1_ITM {
	mLF_EXIT,
	mLF_LUMIN,
	mLF_CONTRST,
	mLF_COLOR,
	mLF_SHRP,
	mLF_ACC,
	mLF_COLORTONE,
	mLF_YPEAK,
	mLF_RECALL,
	NUM_LF_CUS_ITM
};
enum LF_CUSOSD_LV2_ITM1 {
	mLF_SLDR,
	mLF_BAK
};

enum LF_CUSOSD_LV2_ITM2 {
	mBF_PRESET,
	mBF_FT,
	mBF_GREEN,
	mBF_BLUE,
	mBF_BACK,
	
	mBF_BACK1 = 1
};


enum LF_CUSOSD_LV2_ITM3 {
	mLF_NO,
	mLF_YES
};




void LoadColorPalette2();
void LFOSDInit(void);
void ShowLFMainMenu(void);
void ShowLFCusOSD(void);
void ShowLFCusMenu(void);
void SelectLFMITM(void);
void SelectLFCusITM(void);
void UnSelectLFCusITM(void);
void ActivateLFCusSLDR(void);
void InactivateLFCusSLDR(void);
void SelectLFCusSubITM(void);
void UnSelectLFCusSubITM(void);
void ShowLFCusItm(void);
void ShowShowLFCusSLDR(void);
void ShowLFCusLum(void);
void ShowLFCusCon(void);
void ShowLFCusClr(void);
void ShowLFCusShp(void);
void ShowLFCusTxt(void);
void ShowLFCusTxtItm(void);
void ShowLFYesNo(void);
void ShowBFColorTone(void);
void ShowBFColorToneITM(void);
void ShowBFFT(void);
void ShowBFGreen(void);
void ShowBFBlue(void);
void ShowLFCusYP(void);
void ShowLFCusYPItm(void);
void ShowLFDemoOSD(void);
void MoveLFDemoOSD(void);
void ShowBKStatus(void);

#endif