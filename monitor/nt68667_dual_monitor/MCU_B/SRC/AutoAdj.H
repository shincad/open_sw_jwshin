#ifndef _AutoAdj_H_
#define _AutoAdj_H_

void AutoTune(void);
void AutoPosition(void);
void AutoClock(void);
void AutoPhaseFineTune(void);
void SetADC_Offset(unsigned char OffSet);
void SetADC_Gain(unsigned char OffSet);
void WriteADC_Offset(unsigned char r,unsigned char g,unsigned char b);
bit AutoColor(void);
///////////////////////////////////////////////////////////////////////////////
void CheckCmd(unsigned char i);
void ReadHistogram(void);
void CheckDotPattern(void);
void AutoClockByPhase(bit h);
unsigned long CheckPhaseData(void);
void SetADC_Offset_C(void);
void SetADC_Gain_C(void);
void SetADC_AutoOffset(void);
void UpdateADCOffset(void);

void CheckClock(void);
float CheckPhase(void);
void AutoDelay(void);
void GetHmask(void);

#endif