#ifndef _MCU_H_
#define  _MCU_H_

#define REG_F000 0x81
#define REG_F102 0x69
#define REG_FB04 0x02
#define REG_FB40 0x04
#define REG_FB43 0x15

void InitMCU(void);
void CheckKey(void);
void ScanKeyPad(void);

void StartDDCCI(void);
void StopDDCCI(void);

#endif
