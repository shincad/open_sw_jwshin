#ifndef _FACTORY_H_
#define _FACTORY_H_


void FactoryEnterMode();
extern void FactoryShowMenu(void);
//extern void FactoryOFF(void);
extern void FactoryEnter(void);
extern void FactoryItemUp();
extern void FactoryItemDown();
extern void FactoryValueUp(void);
extern void FactoryValueDown(void);
extern void FactoryMoveUp();
extern void FactoryMoveDown();
//extern void FactoryReset();
extern void ClearEEPROM();


extern void LF_FactoryUp();
extern void LF_FactoryDown();
extern void LF_FactoryEnter();
extern void LF_FactoryShowMenu();


#endif

