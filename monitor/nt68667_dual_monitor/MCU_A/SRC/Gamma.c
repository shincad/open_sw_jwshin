#include "Scaler.H"
#include "MCU.H"
#include "MyDef.H"
#include "NT686xx_MCU_REG.H"
#include "NT686xx_SC_REG.H"

#include "IIC.H"
#include "PANEL.H"
#include "RAM.H"
#include "OSD.H"
#include "ROM_MAP.H"
#include "8051.H"
#include "NVRAM.H"
#include "Board.H"
#include "Mis.H"
#include "OD.H"
#include "stdio.h"

#ifdef USE_GAMMA
/*
void WriteGammaTable(unsigned char *p)
{
unsigned short i,l;
unsigned char volatile *pBus;
	CheckRegPage(INDEX_CTRL);
	pBus = &SC_StarAddress;
	pBus += (unsigned char)INDEX_CTRL;
	l = p[1] * 256;
	l = l + p[0] + 2;
	*pBus = p[2];
	pBus++;
	*pBus = p[3];
	pBus++;
	*pBus = p[4];
	pBus++;
	for(i=5; i<l; i++){
		*pBus = p[i];
	}
}
*/
void LoadGamma(void)
{
#if PanelID==INL_190AW01 //PanelID==CMO_M220Z1_L03
	code unsigned char GammaTabR[] = {
0x03, 0x02, 0x00, 0x00, 0x00, 
0,0,0,0,0,0,0,13,0,13,0,13,0,14,0,15,
0,15,0,16,0,16,0,17,0,18,0,19,64,20,0,21,
192,21,0,22,64,23,0,24,192,24,192,25,192,26,192,27,
192,28,64,29,0,30,192,31,192,32,64,33,0,34,0,35,
0,36,192,36,192,37,128,38,64,39,0,40,0,41,192,41,
192,42,192,43,192,44,128,45,192,46,192,47,128,48,64,49,
64,50,128,51,128,52,64,53,64,54,0,55,0,56,192,56,
192,57,0,59,0,60,192,60,192,61,0,63,128,63,64,64,
64,65,64,66,128,67,128,68,64,69,64,70,64,71,0,72,
192,72,192,73,192,74,0,76,192,76,192,77,64,79,0,80,
0,81,192,81,0,83,0,84,0,85,192,85,128,86,128,87,
64,88,64,89,0,90,64,91,64,92,192,92,192,93,128,94,
128,95,64,96,64,97,64,98,64,99,64,100,0,101,0,102,
192,102,192,103,128,104,64,105,192,106,128,107,128,108,192,109,
0,111,0,112,192,112,0,114,0,115,64,116,0,117,64,118,
0,119,0,120,0,121,64,122,0,123,0,124,192,124,0,126,
0,127,192,127,128,128,192,129,192,130,128,131,64,132,64,133,
0,134,0,135,192,135,192,136,0,138,0,139,0,140,192,140,
64,142,64,143,0,144,0,145,0,146,0,147,0,148,0,149,
0,150,192,150,192,151,128,152,128,153,64,154,0,155,128,155,
128,156,192,157,128,158,128,159,128,160,128,161,128,162,128,163,
64,164,64,165,64,166,0,167,0,168,64,169,64,170,64,171,
128,172,0,174,64,175,0,176,192,176,192,177,192,178,192,179,
192,180,192,181,192,182,128,183,192,184,192,185,192,186,192,187,
0,189,0,190,0,191,192,191,128,193,192,194,192,195,192,196,
192,197,192,198,192,199,0,201,0,202,192,202,192,203,0,205,
64,206,192,206,192,207,0,209,64,210,64,211,64,212,128,213,
128,214,64,215,64,216,128,217,128,218,128,219,128,220,0,222,
0,223,192,223,192,224,64,226,64,227,0,228,0,229,0,230,
0,231,0,232,64,233,128,234,128,235,128,236,128,237,192,238,
192,239,192,240,0,242,0,243,0,244,192,244,0,246,0,247,
0,248,0,249,128,250,64,251,128,252,128,253,64,254,0,255,
};
	code unsigned char GammaTabG[] = {		
0x03, 0x02, 0x10, 0x00, 0x00, 
0,0,0,0,0,0,0,13,0,13,0,14,0,15,0,16,
0,16,0,17,0,17,0,18,0,19,0,20,0,21,0,22,
64,23,0,24,192,24,0,25,128,26,128,27,192,28,64,29,
64,30,64,31,64,32,64,33,0,34,0,35,0,36,192,36,
192,37,128,38,128,39,128,40,64,41,64,42,64,43,64,44,
0,45,0,46,0,47,64,48,0,49,192,49,192,50,0,52,
0,53,192,53,0,55,192,55,192,56,128,57,128,58,128,59,
128,60,128,61,64,62,64,63,64,64,0,65,64,66,64,67,
64,68,0,69,0,70,0,71,0,72,192,72,192,73,0,75,
0,76,0,77,192,77,0,79,0,80,0,81,192,81,192,82,
192,83,192,84,192,85,192,86,192,87,128,88,128,89,128,90,
128,91,128,92,64,93,0,94,0,95,192,95,128,96,128,97,
128,98,192,99,128,100,128,101,128,102,64,103,64,104,64,105,
64,106,64,107,0,108,0,109,0,110,64,111,64,112,0,113,
64,114,64,115,64,116,0,117,0,118,0,119,0,120,192,120,
192,121,0,123,0,124,192,124,192,125,192,126,192,127,128,128,
192,129,0,131,0,132,192,132,192,133,128,134,128,135,128,136,
128,137,192,138,0,140,192,140,192,141,0,143,0,144,192,144,
192,145,192,146,0,148,192,148,192,149,128,150,128,151,64,152,
0,153,128,153,64,154,64,155,0,156,64,157,64,158,64,159,
64,160,64,161,128,162,64,163,0,164,0,165,0,166,0,167,
0,168,0,169,0,170,0,171,0,172,0,173,64,174,64,175,
0,176,64,177,128,178,128,179,64,180,64,181,0,182,64,183,
0,184,64,185,64,186,64,187,0,188,192,189,0,191,128,191,
128,192,192,193,0,195,192,195,128,196,128,197,128,198,128,199,
128,200,192,201,64,203,0,204,0,205,0,206,0,207,192,207,
64,209,64,210,64,211,64,212,128,213,64,214,64,215,0,216,
64,217,128,218,128,219,64,220,192,221,192,222,128,223,128,224,
128,225,128,226,128,227,64,228,64,229,64,230,64,231,64,232,
64,233,64,234,64,235,0,236,64,237,64,238,64,239,192,239,
0,241,192,241,0,243,128,243,128,244,128,245,192,246,128,247,
0,248,0,249,192,249,192,250,128,251,128,252,192,253,0,255,
	};
	code unsigned char GammaTabB[] =
	{		
0x03, 0x02, 0x20, 0x00, 0x00, 
0,0,0,0,0,0,0,18,0,18,0,18,0,19,0,19,
0,21,64,21,192,21,0,22,0,24,0,25,128,25,0,26,
0,28,192,28,128,29,64,30,0,31,192,32,192,33,192,34,
0,36,192,36,128,37,192,38,128,39,192,40,128,41,64,42,
64,43,192,44,128,45,0,46,192,46,64,48,64,49,0,50,
192,50,64,52,0,53,0,54,192,54,192,55,0,57,192,57,
128,58,192,59,192,60,192,61,128,62,192,63,192,64,128,65,
64,66,192,67,192,68,128,69,0,70,0,71,64,72,0,73,
192,73,192,74,64,76,0,77,192,77,192,78,128,80,128,81,
64,82,0,83,128,84,128,85,64,86,0,87,128,88,64,89,
0,90,0,91,64,92,64,93,192,93,192,94,192,95,192,96,
128,97,192,98,192,99,128,100,128,101,64,102,64,103,0,104,
0,105,192,105,0,107,0,108,0,109,0,110,64,111,128,112,
64,113,0,114,64,115,128,116,128,117,64,118,64,119,64,120,
64,121,0,122,0,123,64,124,64,125,0,126,0,127,0,128,
0,129,0,130,64,131,0,132,0,133,192,133,192,134,0,136,
192,136,128,137,128,138,192,139,0,141,192,141,192,142,192,143,
0,145,192,145,192,146,192,147,192,148,128,149,64,150,192,150,
192,151,128,152,128,153,128,154,128,155,192,156,128,157,128,158,
128,159,128,160,128,161,128,162,128,163,128,164,128,165,64,166,
64,167,64,168,64,169,0,170,0,171,0,172,64,173,0,174,
0,175,0,176,64,177,0,178,0,179,64,180,0,181,192,181,
128,182,128,183,128,184,128,185,64,186,64,187,128,188,128,189,
128,190,64,191,0,192,64,193,64,194,64,195,128,196,128,197,
64,198,0,199,0,200,192,200,192,201,192,202,128,203,128,204,
128,205,128,206,128,207,64,208,0,209,0,210,0,211,0,212,
0,213,0,214,192,214,128,215,128,216,64,217,64,218,64,219,
64,220,64,221,64,222,0,223,0,224,0,225,128,225,0,227,
0,228,64,229,64,230,192,230,128,231,64,232,64,233,0,234,
192,234,192,235,192,236,0,238,192,238,128,239,192,240,128,241,
64,242,64,243,128,244,128,245,64,246,0,247,192,247,128,248,
64,249,0,250,0,251,0,252,64,253,0,254,128,254,0,255,
	};
	
	
	
#elif PanelID==HSD_HSD190MEN3_A

	code unsigned char GammaTabR[] =
	{
0x03, 0x02, 0x00, 0x00, 0x00, 
0,0,0,0,0,5,0,5,0,7,0,9,0,10,0,11,
0,12,0,14,0,15,0,17,0,18,0,19,0,20,0,22,
64,23,0,24,0,26,64,27,0,28,128,29,0,31,0,32,
128,33,192,34,0,36,128,37,192,38,192,39,64,41,128,42,
192,43,64,45,192,46,192,47,0,49,192,49,64,51,192,52,
0,54,192,54,0,56,128,57,128,58,0,60,64,61,64,62,
64,63,64,64,64,65,64,66,64,67,64,68,128,69,192,70,
0,72,64,73,128,74,192,75,0,77,64,78,64,79,192,80,
128,81,192,82,0,84,0,85,0,86,0,87,64,88,64,89,
0,90,0,91,64,92,64,93,0,94,64,95,128,96,128,97,
192,98,192,99,0,101,0,102,64,103,128,104,128,105,128,106,
192,107,192,108,192,109,0,111,0,112,0,113,0,114,0,115,
0,116,192,116,0,118,0,119,0,120,192,120,0,122,192,122,
192,123,128,124,128,125,192,126,128,127,0,128,0,129,0,130,
0,131,192,131,192,132,192,133,192,134,192,135,192,136,192,137,
192,138,128,139,128,140,128,141,128,142,64,143,0,144,0,145,
0,146,0,147,192,147,0,149,64,150,64,151,0,152,128,153,
128,154,64,155,0,156,0,157,0,158,0,159,0,160,0,161,
0,162,192,162,0,164,0,165,64,166,64,167,64,168,64,169,
64,170,64,171,64,172,64,173,64,174,0,175,64,176,0,177,
0,178,192,178,64,180,0,181,192,181,128,182,128,183,128,184,
64,185,0,186,128,186,64,187,128,188,64,189,0,190,128,190,
64,191,0,192,128,192,128,193,64,194,0,195,192,195,192,196,
64,197,0,198,0,199,0,200,192,200,128,201,64,202,64,203,
0,204,192,204,128,205,64,206,64,207,0,208,0,209,128,209,
0,210,0,211,192,211,64,212,0,213,128,213,0,214,0,215,
192,215,128,216,64,217,192,217,64,218,64,219,64,220,192,220,
64,221,192,221,64,222,64,223,192,223,64,224,0,225,192,225,
64,227,64,228,192,228,128,229,64,230,64,231,0,232,192,232,
64,233,192,233,0,235,192,235,64,236,0,237,128,237,128,238,
64,239,192,239,64,240,0,241,128,241,128,242,64,243,192,243,
64,244,0,245,128,245,128,246,128,247,0,248,192,248,0,251
	};
	code unsigned char GammaTabG[] =
	{		
0x03, 0x02, 0x10, 0x00, 0x00, 
0,0,0,0,0,6,0,6,0,8,0,9,0,10,0,10,
0,12,0,14,0,15,0,16,0,17,0,19,0,20,0,21,
0,22,0,23,0,25,0,26,0,27,0,28,128,29,128,30,
0,32,192,32,64,34,128,35,192,36,192,37,128,38,0,40,
64,41,192,42,0,44,192,44,0,46,192,46,192,47,192,48,
0,50,0,51,0,52,64,53,128,54,128,55,192,56,192,57,
192,58,0,60,0,61,192,61,64,63,0,64,0,65,0,66,
0,67,192,67,0,69,192,69,64,71,64,72,128,73,128,74,
128,75,128,76,192,77,192,78,192,79,0,81,0,82,0,83,
0,84,192,84,0,86,0,87,0,88,192,88,192,89,192,90,
128,91,64,92,0,93,128,94,0,96,192,96,128,97,192,98,
192,99,192,100,192,101,192,102,192,103,192,104,192,105,0,107,
192,107,0,109,0,110,0,111,192,111,0,113,192,113,0,115,
128,115,64,116,128,117,128,118,64,119,0,120,0,121,192,121,
192,122,128,123,64,124,128,125,128,126,64,127,0,128,192,128,
192,129,128,130,128,131,128,132,128,133,64,134,0,135,64,136,
0,137,0,138,128,138,64,139,128,140,64,141,64,142,192,142,
128,143,64,144,64,145,64,146,0,147,0,148,64,149,0,150,
64,151,64,152,64,153,0,154,64,155,64,156,64,157,0,158,
64,159,64,160,64,161,192,161,0,163,192,163,0,165,192,165,
192,166,192,167,192,168,192,169,192,170,192,171,192,172,192,173,
128,174,128,175,128,176,64,177,128,178,128,179,128,180,64,181,
0,182,192,182,0,184,128,184,0,185,64,186,0,187,0,188,
128,188,0,189,0,190,192,190,64,191,0,192,192,192,128,193,
128,194,64,195,0,196,0,197,192,197,192,198,128,199,64,200,
64,201,0,202,192,202,128,203,0,204,64,205,0,206,0,207,
128,207,0,208,0,209,192,209,128,210,64,211,0,212,128,212,
128,213,64,214,64,215,192,215,128,216,64,217,64,218,0,219,
192,219,128,220,64,221,192,221,192,222,128,223,128,224,0,226,
192,226,0,228,192,228,192,229,192,230,128,231,64,232,64,233,
64,234,0,235,0,236,192,236,0,238,192,238,128,239,64,240,
128,241,64,242,192,242,192,243,192,244,128,246,128,247,0,249,
	};
	code unsigned char GammaTabB[] =
	{		
0x03, 0x02, 0x20, 0x00, 0x00, 
0,0,0,0,0,5,0,5,0,7,0,8,0,9,0,10,
0,11,0,12,0,13,0,14,0,15,0,16,0,17,0,18,
64,19,0,20,64,21,64,22,64,23,0,24,0,25,64,26,
64,27,0,28,0,29,0,30,192,30,192,31,128,32,192,33,
192,34,128,35,64,36,128,37,64,38,0,39,0,40,0,41,
64,42,0,43,192,43,0,45,0,46,192,46,128,47,64,48,
64,49,64,50,0,51,0,52,0,53,0,54,192,54,128,55,
128,56,64,57,64,58,64,59,64,60,64,61,0,62,0,63,
128,63,64,64,64,65,0,66,192,66,128,67,64,68,64,69,
0,70,0,71,192,71,192,72,128,73,128,74,64,75,64,76,
64,77,0,78,0,79,192,79,0,81,192,81,128,82,64,83,
64,84,0,85,192,85,192,86,128,87,64,88,0,89,192,89,
128,90,128,91,64,92,0,93,192,93,192,94,192,95,128,96,
128,97,64,98,0,99,64,100,0,101,192,101,128,102,192,103,
128,104,64,105,0,106,0,107,192,107,128,108,128,109,64,110,
64,111,0,112,192,112,128,113,128,114,64,115,64,116,0,117,
192,117,128,118,64,119,0,120,192,120,128,121,128,122,64,123,
0,124,192,124,128,125,64,126,64,127,192,127,64,128,0,129,
192,129,192,130,128,131,64,132,0,133,192,133,192,134,128,135,
64,136,0,137,192,137,192,138,128,139,64,140,0,141,192,141,
192,142,64,143,0,144,192,144,192,145,128,146,64,147,0,148,
0,149,0,150,192,150,128,151,128,152,128,153,128,154,64,155,
64,156,64,157,64,158,0,159,0,160,0,161,192,161,192,162,
192,163,192,164,192,165,192,166,128,167,128,168,128,169,128,170,
128,171,128,172,128,173,64,174,0,175,192,175,64,177,0,178,
0,179,0,180,0,181,192,181,128,182,128,183,192,184,128,185,
64,186,0,187,192,187,0,189,192,189,64,190,64,191,192,191,
192,192,128,193,128,194,64,195,64,196,0,197,192,197,128,198,
0,200,128,200,128,201,128,202,192,203,192,204,128,205,192,206,
192,207,192,208,192,209,128,210,192,211,128,212,128,213,192,214,
192,215,192,216,0,218,128,219,192,220,192,221,0,223,0,224,
64,226,64,228,0,230,0,232,0,234,128,236,128,239,0,251,
	};


#elif PanelID==LPL_LM170ME03_TLLX
//#elif PanelID==INL_190AW01						// +jwshin 111209
	code unsigned char GammaTabR[] =
	{
/*
0x03, 0x02, 0x00, 0x00, 0x00, 
0,0,0,0,0,4,0,4,0,6,0,7,0,9,0,9,
0,10,0,12,0,13,0,14,0,15,0,17,0,17,0,18,
0,20,0,21,64,22,0,23,128,24,64,25,128,26,192,27,
0,29,0,30,64,31,128,32,192,33,192,34,0,36,64,37,
64,38,192,39,128,40,64,41,128,42,192,43,192,44,192,45,
0,47,192,47,192,48,192,49,192,50,0,52,128,53,64,54,
128,55,192,56,192,57,192,58,0,60,128,61,64,62,64,63,
0,64,0,65,64,66,128,67,128,68,192,69,192,70,192,71,
192,72,192,73,0,75,0,76,64,77,128,78,192,79,192,80,
0,82,0,83,64,84,64,85,128,86,128,87,128,88,128,89,
128,90,192,91,0,93,0,94,64,95,0,96,0,97,0,98,
64,99,128,100,128,101,192,102,192,103,128,104,128,105,128,106,
64,107,128,108,64,109,64,110,0,111,64,112,0,113,0,114,
64,115,128,116,64,117,64,118,128,119,64,120,128,121,128,122,
192,123,192,124,0,126,64,127,64,128,64,129,128,130,128,131,
192,132,192,133,192,134,192,135,0,137,0,138,64,139,0,140,
0,141,0,142,64,143,0,144,0,145,64,146,64,147,0,148,
0,149,128,150,128,151,128,152,128,153,192,154,192,155,192,156,
192,157,0,159,128,159,64,160,64,161,64,162,64,163,64,164,
64,165,128,166,128,167,128,168,128,169,128,170,128,171,128,172,
64,173,0,174,0,175,192,175,128,176,128,177,64,178,64,179,
64,180,0,181,192,181,64,183,0,184,0,185,192,185,128,186,
128,187,64,188,0,189,0,190,192,190,128,191,0,192,0,193,
192,193,128,194,64,195,0,196,0,197,192,197,128,198,0,199,
192,199,192,200,192,201,128,202,64,203,64,204,128,205,64,206,
192,206,192,207,128,208,128,209,64,210,0,211,192,211,192,212,
128,213,64,214,0,215,64,216,64,217,64,218,192,218,128,219,
192,220,192,221,128,222,0,223,192,223,128,224,128,225,128,226,
0,227,192,227,192,228,192,229,64,230,192,230,0,232,128,232,
64,233,192,233,0,235,192,235,128,236,0,237,192,237,64,238,
0,239,128,239,0,240,64,241,0,242,128,242,0,243,0,244,
0,245,0,246,192,246,64,247,0,248,0,249,64,250,0,253,
*/
// RED LESS
0x03, 0x02, 0x00, 0x00, 0x00, 
0,0,0,0,0,4,0,4,0,6,0,7,0,8,0,8,
0,9,0,10,0,11,0,12,0,13,0,14,0,15,0,16,
0,17,0,18,64,19,0,20,128,21,64,22,128,23,192,24,
0,25,0,26,64,27,128,28,192,29,192,30,0,31,64,32,
64,33,192,34,128,35,64,36,128,37,192,38,192,39,192,40,
0,41,192,42,192,43,192,44,192,45,0,46,128,47,64,48,
128,49,192,50,192,51,192,52,0,54,128,55,64,56,64,57,
0,58,0,60,64,61,128,62,128,64,192,65,192,66,192,67,
192,68,192,69,0,70,0,71,64,72,128,73,192,74,192,76,
0,77,0,78,64,79,64,80,128,81,128,82,128,84,128,85,
128,86,192,87,0,88,0,89,64,90,0,92,0,93,0,94,
64,95,128,96,128,97,192,98,192,99,128,100,128,101,128,102,
64,103,128,104,64,105,64,106,0,107,64,108,0,109,0,110,
64,111,128,112,64,113,64,114,128,115,64,116,128,117,128,118,
192,119,192,120,0,121,64,123,64,124,64,125,128,126,128,127,
192,128,192,128,192,129,192,130,0,131,0,132,64,133,0,134,
0,135,0,136,64,137,0,138,0,139,64,140,64,141,0,142,
0,143,128,144,128,145,128,146,128,147,192,148,192,149,192,150,
192,151,0,152,128,153,64,154,64,155,64,156,64,157,64,158,
64,159,128,160,128,161,128,162,128,163,128,164,128,165,128,166,
64,167,0,168,0,169,192,170,128,171,128,172,64,173,64,174,
64,175,0,176,192,177,64,178,0,179,0,180,192,181,128,182,
128,183,64,184,0,185,0,186,192,187,128,188,0,189,0,190,
192,191,128,192,64,193,0,194,0,195,192,195,128,196,0,197,
192,198,192,199,192,200,128,200,64,201,64,202,128,203,64,204,
192,204,192,205,128,206,128,207,64,208,0,209,192,210,192,210,
128,211,64,211,0,212,64,213,64,214,64,215,192,215,128,216,
192,217,192,218,128,219,0,220,192,220,128,221,128,222,128,223,
0,224,192,225,192,226,192,227,64,227,192,228,0,229,128,230,
64,231,192,231,0,232,192,233,128,233,0,234,192,235,64,235,
0,236,128,237,0,238,64,238,0,239,128,240,0,241,0,242,
0,243,0,244,192,245,64,246,0,247,0,248,64,250,0,252,
	};
	code unsigned char GammaTabG[] =
	{		
0x03, 0x02, 0x10, 0x00, 0x00, 
0,0,0,0,0,4,0,4,0,8,0,9,0,11,0,12,
0,13,0,14,0,15,0,16,0,17,0,19,0,20,192,20,
0,22,0,23,128,24,128,25,128,26,128,27,192,28,192,29,
192,30,192,31,0,33,0,34,0,35,64,36,64,37,128,38,
128,39,192,40,128,41,192,42,128,43,128,44,192,45,192,46,
0,48,0,49,0,50,0,51,0,52,0,53,64,54,64,55,
128,56,128,57,128,58,192,59,192,60,192,61,192,62,192,63,
192,64,128,65,192,66,192,67,0,69,0,70,0,71,0,72,
0,73,0,74,64,75,64,76,128,77,128,78,192,79,128,80,
64,81,0,82,64,83,128,84,192,85,128,86,192,87,128,88,
128,89,192,90,192,91,0,93,0,94,64,95,64,96,0,97,
192,97,0,99,0,100,64,101,64,102,64,103,64,104,128,105,
128,106,128,107,192,108,192,109,192,110,0,112,192,112,192,113,
192,114,192,115,0,117,0,118,0,119,0,120,0,121,0,122,
0,123,0,124,0,125,0,126,0,127,0,128,192,128,0,130,
0,131,0,132,0,133,64,134,64,135,64,136,64,137,128,138,
128,139,128,140,128,141,192,142,128,143,64,144,0,145,0,146,
0,147,64,148,64,149,64,150,64,151,64,152,64,153,64,154,
0,155,64,156,0,157,64,158,0,159,0,160,0,161,0,162,
0,163,0,164,0,165,0,166,0,167,0,168,0,169,0,170,
0,171,192,171,192,172,192,173,192,174,192,175,192,176,128,177,
128,178,64,179,64,180,64,181,0,182,0,183,192,183,128,184,
128,185,128,186,64,187,64,188,64,189,0,190,0,191,128,191,
64,192,64,193,192,193,192,194,128,195,64,196,0,197,0,198,
0,199,128,199,64,200,64,201,64,202,0,203,192,203,128,204,
64,205,128,206,64,207,192,207,128,208,64,209,64,210,0,211,
0,212,192,212,128,213,128,214,128,215,0,216,0,217,192,217,
192,218,128,219,128,220,64,221,64,222,64,223,192,223,192,224,
128,225,64,226,64,227,0,228,0,229,192,229,192,230,128,231,
0,232,0,233,192,233,128,234,64,235,64,236,0,237,192,237,
192,238,128,239,0,240,192,240,128,241,64,242,0,243,192,243,
192,244,192,245,0,247,192,247,0,249,0,250,192,251,0,255,
	};
	code unsigned char GammaTabB[] =
	{		
0x03, 0x02, 0x20, 0x00, 0x00, 
0,0,0,0,0,2,0,2,0,5,0,6,0,8,0,9,
0,10,0,11,0,13,0,14,0,15,0,17,0,17,0,19,
128,20,64,21,0,22,0,24,64,25,0,26,0,27,192,28,
192,29,0,31,192,32,128,33,192,34,0,36,0,37,0,38,
0,39,64,40,128,41,64,42,128,43,128,44,128,45,128,46,
128,47,128,48,128,49,128,50,128,51,0,53,192,53,192,54,
0,56,0,57,192,57,64,59,64,60,64,61,64,62,64,63,
64,64,64,65,0,66,128,67,128,68,128,69,128,70,128,71,
192,72,192,73,128,74,192,75,192,76,128,77,192,78,192,79,
192,80,128,81,128,82,192,83,192,84,128,85,128,86,128,87,
128,88,192,89,128,90,128,91,64,92,128,93,192,94,128,95,
128,96,128,97,64,98,128,99,128,100,128,101,64,102,64,103,
128,104,128,105,128,106,64,107,64,108,128,109,128,110,64,111,
64,112,0,113,128,114,128,115,128,116,64,117,128,118,128,119,
64,120,0,121,64,122,0,123,0,124,192,124,192,125,192,126,
128,127,64,128,192,128,64,130,192,130,0,132,128,132,128,133,
128,134,192,135,128,136,64,137,128,138,64,139,0,140,128,140,
64,141,64,142,0,143,192,143,192,144,128,145,128,146,128,147,
128,148,64,149,64,150,0,151,64,152,0,153,64,154,0,155,
0,156,192,156,128,157,64,158,64,159,0,160,0,161,128,161,
64,162,64,163,192,163,0,165,128,165,64,166,64,167,0,168,
64,169,192,169,128,170,128,171,64,172,64,173,192,173,128,174,
64,175,0,176,64,177,192,177,128,178,64,179,0,180,64,181,
192,181,128,182,128,183,64,184,64,185,192,185,128,186,128,187,
64,188,64,189,0,190,0,191,64,191,192,191,0,193,128,193,
192,193,128,194,64,195,192,195,192,196,128,197,0,198,0,199,
128,199,0,200,64,201,192,201,128,202,64,203,0,204,0,205,
128,205,64,206,0,207,0,208,0,209,192,209,64,210,128,211,
64,212,64,213,192,213,128,214,128,215,0,217,128,217,64,218,
64,219,64,220,64,221,0,222,0,223,0,224,64,225,0,226,
0,227,0,228,64,229,0,230,192,230,0,232,64,233,0,234,
64,235,0,236,128,237,128,238,128,239,64,241,192,242,0,253,

	};


#else	//#elif PanelID==CPT_CLAA170EA07P
	code unsigned char GammaTabR[] =
	{
0x03, 0x02, 0x00, 0x00, 0x00, 
0,0,0,0,0,4,0,4,0,4,0,7,0,8,0,9,
0,9,0,10,0,12,0,13,0,13,0,15,0,16,0,17,
0,18,0,20,0,21,0,22,64,23,64,24,128,25,192,26,
0,28,0,29,64,30,192,31,192,32,192,33,64,35,128,36,
64,37,128,38,0,40,0,41,0,42,64,43,64,44,64,45,
192,46,192,47,192,48,128,49,192,50,192,51,192,52,192,53,
64,55,64,56,64,57,64,58,128,59,192,60,192,61,192,62,
192,63,192,64,0,66,0,67,0,68,0,69,64,70,64,71,
64,72,128,73,128,74,64,75,0,76,0,77,128,78,128,79,
128,80,128,81,192,82,192,83,192,84,128,86,64,87,64,88,
128,89,192,90,192,91,0,93,64,94,64,95,128,96,128,97,
192,98,192,99,192,100,192,101,0,103,0,104,0,105,0,106,
0,107,0,108,0,109,0,110,0,111,0,112,0,113,0,114,
0,115,64,116,128,117,128,118,64,119,64,120,192,121,128,122,
128,123,0,125,64,126,0,127,64,128,64,129,64,130,64,131,
128,132,128,133,128,134,128,135,192,136,192,137,192,138,192,139,
0,141,192,141,192,142,0,144,192,144,128,145,128,146,192,147,
192,148,0,150,192,150,0,152,0,153,0,154,0,155,128,156,
128,157,128,158,0,160,192,160,192,161,192,162,64,164,0,165,
0,166,192,166,64,168,64,169,0,170,0,171,0,172,192,172,
192,173,128,174,128,175,128,176,64,177,64,178,64,179,64,180,
0,181,0,182,64,183,0,184,0,185,192,185,192,186,128,187,
128,188,64,189,0,190,0,191,192,191,64,192,0,193,192,193,
64,195,192,195,128,196,64,197,0,198,64,199,192,199,128,200,
64,201,0,202,0,203,192,203,128,204,64,205,0,206,0,207,
192,207,128,208,64,209,64,210,0,211,192,211,128,212,128,213,
64,214,0,215,192,215,128,216,128,217,64,218,0,219,192,219,
128,220,64,221,64,222,0,223,128,223,64,224,192,224,192,225,
192,226,128,227,128,228,0,229,0,230,192,230,192,231,128,232,
64,233,64,234,0,235,192,235,128,236,64,237,128,238,64,239,
0,240,192,240,192,241,192,242,64,243,0,244,192,244,128,245,
64,246,64,247,192,247,64,248,192,248,0,249,0,250,0,255,
	};
	code unsigned char GammaTabG[] =
	{		
0x03, 0x02, 0x10, 0x00, 0x00, 
0,0,0,0,0,2,0,2,0,4,0,4,0,5,0,5,
0,7,0,8,0,8,0,9,0,10,64,11,192,11,0,12,
0,14,64,15,0,16,192,16,128,18,0,19,192,19,192,20,
128,22,64,23,0,24,192,24,64,26,0,27,0,28,192,28,
192,30,128,31,64,32,0,34,192,34,128,35,64,36,0,37,
0,39,128,39,128,40,0,42,0,43,192,43,128,44,0,46,
192,46,128,47,0,48,0,50,192,50,128,51,64,52,0,54,
0,55,192,55,64,56,0,58,0,59,128,59,64,60,0,62,
192,62,128,63,0,64,192,64,64,66,0,67,192,67,192,68,
64,70,0,71,192,71,192,72,0,74,192,74,128,75,64,76,
128,77,128,78,128,79,64,80,0,82,192,82,128,83,128,84,
0,86,192,86,192,87,192,88,64,90,0,91,0,92,64,93,
64,94,64,95,64,96,64,97,64,98,0,99,0,100,64,101,
64,102,0,103,0,104,64,105,0,106,192,106,128,107,0,109,
192,109,128,110,64,111,128,112,128,113,64,114,0,115,192,116,
0,118,192,118,64,119,0,121,192,121,128,122,64,123,0,125,
0,126,0,127,192,127,0,129,192,129,128,130,128,131,64,133,
0,134,192,134,192,135,64,137,0,138,192,138,192,139,64,141,
0,142,192,142,192,143,192,144,192,145,192,146,192,147,0,149,
192,149,192,150,192,151,64,153,192,153,192,154,0,156,0,157,
0,158,64,159,64,160,64,161,0,162,128,163,128,164,128,165,
64,166,0,167,128,168,128,169,64,170,64,171,128,172,128,173,
64,174,0,175,64,176,64,177,192,177,0,179,64,180,0,181,
192,181,128,182,0,184,192,184,128,185,64,186,192,187,192,188,
128,189,64,190,192,190,128,191,128,192,64,193,0,194,0,195,
128,196,64,197,192,197,128,198,192,199,128,200,64,201,0,202,
64,203,0,204,192,204,192,205,128,206,128,207,128,208,64,209,
64,210,64,211,128,212,0,213,0,214,192,214,192,215,192,216,
128,217,192,218,64,220,192,220,128,221,128,222,192,223,128,224,
64,225,0,226,0,227,128,228,64,229,64,230,128,231,192,232,
192,233,192,234,128,236,64,237,64,238,192,239,0,241,64,242,
192,243,0,245,0,246,128,247,0,249,192,249,128,251,0,255,
	};
	code unsigned char GammaTabB[] =
	{		
0x03, 0x02, 0x20, 0x00, 0x00, 
0,0,0,0,0,2,0,2,0,4,0,5,0,5,0,6,
0,6,0,7,0,8,0,9,64,9,0,10,0,11,128,11,
64,12,192,12,192,13,192,14,128,15,64,16,0,17,0,18,
0,19,192,19,192,20,192,21,64,22,0,23,192,23,128,24,
128,25,128,26,128,27,64,28,0,29,0,30,0,31,192,31,
128,32,64,33,64,34,0,35,192,35,192,36,192,37,128,38,
64,39,0,40,192,40,192,41,128,42,128,43,64,44,0,45,
0,46,192,46,128,47,64,48,0,49,192,49,128,50,64,51,
64,52,0,53,192,53,128,54,128,55,64,56,0,57,192,57,
192,58,128,59,64,60,0,61,192,61,192,62,64,63,0,64,
192,64,128,65,64,66,0,67,0,68,192,68,192,69,128,70,
64,71,0,72,192,72,192,73,128,74,64,75,0,76,0,77,
192,77,128,78,64,79,0,80,192,80,192,81,128,82,64,83,
64,84,64,85,64,86,0,87,192,87,128,88,128,89,128,90,
64,91,0,92,0,93,192,93,128,94,128,95,64,96,64,97,
0,98,192,98,128,99,64,100,64,101,0,102,0,103,192,103,
128,104,64,105,0,106,0,107,192,107,128,108,64,109,0,110,
192,110,128,111,128,112,64,113,64,114,64,115,64,116,0,117,
192,117,192,118,128,119,64,120,64,121,64,122,64,123,0,124,
0,125,0,126,192,126,128,127,64,128,64,129,0,130,0,131,
192,131,192,132,128,133,128,134,128,135,128,136,64,137,64,138,
0,139,192,139,192,140,128,141,128,142,128,143,64,144,64,145,
64,146,64,147,0,148,0,149,0,150,192,150,192,151,192,152,
192,153,192,154,192,155,192,156,128,157,128,158,64,159,64,160,
64,161,64,162,0,163,0,164,0,165,0,166,0,167,64,168,
64,169,64,170,0,171,0,172,128,172,128,173,128,174,128,175,
128,176,128,177,128,178,64,179,64,180,64,181,64,182,64,183,
64,184,64,185,0,186,0,187,0,188,192,188,192,189,192,190,
128,191,128,192,192,193,128,194,128,195,192,196,128,197,128,198,
128,199,192,200,192,201,192,202,192,203,192,204,0,206,64,207,
64,208,128,209,128,210,0,212,0,213,128,214,192,215,64,217,
128,218,0,220,128,221,64,223,192,224,64,227,0,229,0,254,
	};
	
#endif
	
	WriteIIC560(GAMMA_CTRL,0x00);	//gamma off, 10bit
	Sleep(20);
	WriteSequenceScaler(INDEX_CTRL,GammaTabR);
	Sleep(20);
	WriteSequenceScaler(INDEX_CTRL,GammaTabG);
	Sleep(20);
	WriteSequenceScaler(INDEX_CTRL,GammaTabB);
	// Reset Gamma
	WriteIIC560(INDEX_CTRL, 0x34);
	WriteIIC560(INDEX_ADDR_LI, 0x00);
	WriteIIC560(INDEX_ADDR_HI, 0x00);
	WriteIIC560(INDEX_DATA, 0x00);
	WriteIIC560(INDEX_DATA, 0x00);
	WriteIIC560(INDEX_ADDR_LI, 0x00);
	//
	Sleep(20);	// Fill in gamma data about one frame later //ming 02/07/2007
	WriteIIC560(GAMMA_CTRL,0x80);	//gamma on, 8bit


}

#endif



