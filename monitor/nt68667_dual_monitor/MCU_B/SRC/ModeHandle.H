#ifndef _ModeHandle_H_
#define _ModeHandle_H_

void Mode_Check(void);
void GetCounter(void);
void CheckFreq(void);
void GetMode(void);
void SetUserMode(unsigned char);
void SyncSource(void);
void NoSync(void);
void SetMinMax(void);
void CheckModeChange(void);
void GoToSeparateSync(void);
void GoToCompositeSync(void);
bit CheckSOG(void);
void MuteScreen(void);
void MuteScreen_1(void);
void CheckSyncMode(void);
void GoToDVI(void);
void SetAutoAdjTag(void);
//void ClearNewModeLED(void);
void WaitSetup(unsigned char time);
void CheckSelectSync(void);
void CheckDVI();
void CheckGreenPower(void);
unsigned char DVIPresentDetection(void);

#endif
