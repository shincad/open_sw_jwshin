#if 0
#include "Panel.H"

xdata unsigned char ucPanelID;
xdata unsigned char ucPanelName[MAX_NAME_LEN];


code unsigned char *ucPanelBrand[4] = { "AUO", "LPL", "QDI", "CPT" };
code unsigned char ucPanelSize[3] = { 15, 17, 19 };

code _PANEL_T_ Panel_t[TOTAL_PANEL_ID] = {
	// PanelType,    default IDX
	{ AUO15, 35 },
	{ LPL15,  75 },
	{ QDI15, 115 },
	{ CPT15, 155 },

	{ AUO17, 37 },
	{ LPL17,  77 },
	{ QDI17, 117 },
	{ CPT17, 157 },

	{ AUO19, 39 },
	{ LPL19,  79 },
	{ QDI19, 119 },
	{ CPT19, 159 }
};

unsigned char Panel_NextID()
{
	if (++ucPanelID == TOTAL_PANEL_ID )
		ucPanelID = 0;
	return ucPanelID;
}

unsigned char Panel_PrevID()
{
	if (--ucPanelID == 0xff )
		ucPanelID = TOTAL_PANEL_ID-1;

	return ucPanelID;
}

//
//	Only for initialize in the LoadModeIndependentSettings() while startup
//
unsigned char Panel_CurrentPanelID()
{

#if (PanelID == AUO15 ) 		
		return PID_AUO15;
#elif (PanelID == LPL15 )	
		return PID_LPL15;
#elif (PanelID == QDI15 )	
		return PID_QDI15;
#elif (PanelID == CPT15 )	
		return PID_CPT15;

#elif (PanelID == AUO17 )	
		return PID_AUO17;
#elif (PanelID == LPL17 )	
		return PID_LPL17;
#elif (PanelID == QDI17 )	
		return PID_QDI17;
#elif (PanelID == CPT17 )	
		return PID_CPT17;
		
#elif (PanelID == AUO19 )	
		return PID_AUO19;
#elif (PanelID == LPL19 )	
		return PID_LPL19;
#elif (PanelID == QDI19 )	
		return PID_QDI19;
#elif (PanelID == CPT19 )	
		return PID_CPT19;
#else
		return PID_UNKNOWN;
#endif
	
}

unsigned char Panel_GetNameString(unsigned short namecode)
{
unsigned char i, k;

	k = (namecode>>4) & 0x0f;
	for (i=0; ucPanelBrand[k][i] != '\0'; i++)
		ucPanelName[i] = ucPanelBrand[k][i];
	
	k = namecode & 0x0f;
	sprintf(&ucPanelName[i], "%2d", (unsigned short)ucPanelSize[k]);	// 15 or 17 or 19 ...
	i += 2;	// since 15, 17 or 19
	ucPanelName[i] = '\0';

	return (i);		//	return string length

}

#endif

/*
unsigned char Panel_GetNameString(unsigned short namecode, unsigned char *namestr)
//unsigned char Panel_GetNameString(unsigned short namecode)
{

	unsigned char i, k;

	k = ucPanelSize[(namecode>>8) & 0x0f ];
	sprintf(&namestr[0],"%d0", k);	// 150 or 170 or 190 ...

	k = ucPanelType[(namecode>>4) & 0x0f ];
	namestr[3] = k;

	namestr[4] = '_';

	k = namecode & 0x0f;
	for (i=0; ucPanelBrand[k][i] != '\r'; i++)
		namestr[5+i] = ucPanelBrand[k][i];

	namestr[5+i] = '\r';

	return (5+i);	// return string length
	
}
*/


