#ifndef __OD_H__
#define __OD_H__


#if _Enable_OD_ == ON
// OD
extern xdata unsigned char ucCurODMode;
extern xdata unsigned char ucPrevODMode;
#endif



void EnableOD(void);
void DisableOD(void);
void SetODTable(unsigned char index);
void WriteODTable(unsigned char *p);

#endif