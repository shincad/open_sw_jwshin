#include "OSD.H"

void ShowEmpowerMenu()
{
	WriteIIC560(0x080,0x00);
	
	ucOSDType = EMPOWER_MENU;
	ucOSDLvl1_Cursor = 0;
	
	ucOSDWidth = OSD_EP_WIDTH;
	SetPosition();
	ClearOSD();
	
	WriteIIC560(0x080,0x00);
	
}