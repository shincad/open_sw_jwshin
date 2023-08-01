#ifndef _UserAdj_H_
#define  _UserAdj_H_

//extern code unsigned char ColorTab[];
/*
extern Byte code RGBmenuItem[3];
//extern code Byte FactmenuItem[];
//extern code unsigned char LanguageDummy[];
extern Byte code Page0Item[7];
extern Byte code Page0ItemD[3];
extern Byte code Page0ItemY[5];
extern Byte code Page0ItemV[5];
extern Byte code Page1Item[2];
extern Byte code Page2Item[4];
extern Byte code Page3Item[1];
extern Byte code Page4Item[6];
extern Byte code Page5Item[5];
extern Byte code Page6Item[7];
extern code FACTDEF FactItem[26];
*/
//extern code unsigned char TDA7440D_Tab[];

void LoadModeIndependentSettings(void);
void LoadModeDependentSettings(void);
void SaveModeDependentSettings(void);
void Recall(bit);
void AdjustProcess();
void MiscProcess(bit);
void SaveData(void);
void GetFuncRange(unsigned char);
void SetFuncMaxMin();
void LoadColor(unsigned short);
void SetSource();
void SaveBackLightTime(void);
void LoadPresetModeSettings(unsigned char);
void SetFineTune(void);

#endif
