#include "MYDEF.H"
#include "OSD.H"
#include "OSD_tab.H"
//Brightness
code unsigned char ENG_BRIGHT[]={
	10,"Brightness"
};
code unsigned char FRA_BRIGHT[]={
	10,"Luminosit"	
};
code unsigned char DEU_BRIGHT[]={
	10,"Helligkeit"
};
code unsigned char ESP_BRIGHT[]={
	11,"Luminosidad"
};
code unsigned char ITA_BRIGHT[]={
	10,"Luminosit"
};
code unsigned char JAP_BRIGHT[]={
	6,_J08,_J09,_J0a,_J0b,_J0c,_J0d
};
code unsigned char CHT_BRIGHT[]={
	2,_C1c,_C1d
};
code unsigned char CHI_BRIGHT[]={
	2,_C1c,_C1d
};
code unsigned char RUS_BRIGHT[]={
	7,_P01,_p,_P00,_o,_c,_P05,_b
};
//Contrast
code unsigned char ENG_CONTRAST[]={
	8,"Contrast"
};
code unsigned char FRA_CONTRAST[]={
	9,"Contraste"
};
code unsigned char DEU_CONTRAST[]={
	8,"Kontrast"
};
code unsigned char ESP_CONTRAST[]={
	9,"Contraste"
};
code unsigned char ITA_CONTRAST[]={
	9,"Contrasto"
};
code unsigned char JAP_CONTRAST[]={
	6,_J02,_J0e,_J0b,_J09,_J0d,_J0b
};
code unsigned char CHT_CONTRAST[]={
	2,_C52,_C21
};
code unsigned char CHI_CONTRAST[]={
	2,_C20,_C21
};
code unsigned char RUS_CONTRAST[]={
	9,_P06,_P07,_e,_P05,_P04,_o,_c,_P05,_b
};
//Phase
code unsigned char ENG_PHASE[]={
	5,"Phase"
};
code unsigned char FRA_PHASE[]={
	5,"Phase"
};
code unsigned char DEU_PHASE[]={
	5,"Phase"};
code unsigned char ESP_PHASE[]={
	4,"Fase"
};
code unsigned char ITA_PHASE[]={
	5,"Phase"
};
code unsigned char JAP_PHASE[]={
	4,_J05,_J12,_J03,_J2a
};
code unsigned char RUS_PHASE[]={
	4,_P0d,_a,_3,_a
};
code unsigned char CHT_PHASE[]={
	2,_C22,_C14
};
code unsigned char CHI_PHASE[]={
	2,_C22,_C14
};
//Clock
code unsigned char ENG_CLOCK[]={
	5,"Clock"
};
code unsigned char FRA_CLOCK[]={
	7,"Horoge"
};
code unsigned char DEU_CLOCK[]={
	4,"Takt"
};
code unsigned char ESP_CLOCK[]={
	5,"Reloj"	
};
code unsigned char ITA_CLOCK[]={
	5,"Clock"
};
code unsigned char JAP_CLOCK[]={
	4,_J0f,_J10,_J11,_J0f
};
code unsigned char RUS_CLOCK[]={
	7,_P0c,_a,_c,_P05,_o,_P05,_a
};
code unsigned char CHT_CLOCK[]={
	4,_C12,_C13,_C57,_C1d
};
code unsigned char CHI_CLOCK[]={
	4,_C12,_C13,_C4d,_C1d
};
//H position
code unsigned char ENG_HPOS[]={
	10,"H.Position"
};
code unsigned char FRA_HPOS[]={
	10,"Position-H"
};
code unsigned char DEU_HPOS[]={
	10,"H-Position"
};
code unsigned char ESP_HPOS[]={
	10,"Posicin-H"
};
code unsigned char ITA_HPOS[]={
	11,"Posizione O"
};
code unsigned char JAP_HPOS[]={
	7,_C12,_C13,_J2b,_J1b,_J11,_J2c,_J0e
};
code unsigned char RUS_HPOS[]={
	12,_P1b,_o,_P19,_o,_P0e,_DOT,_P16,_o,_P0a,_o,_p,_DOT
};
code unsigned char CHT_HPOS[]={
	4,_C12,_C13,_C14,_C15
};
code unsigned char CHI_HPOS[]={
	4,_C12,_C13,_C14,_C15
};
//V position
code unsigned char ENG_VPOS[]={
	10,"V.Position"
};
code unsigned char FRA_VPOS[]={
	10,"Position-V"
};
code unsigned char DEU_VPOS[]={
	10,"V-Position"
};
code unsigned char ESP_VPOS[]={
	10,"Posicin-V"
};
code unsigned char ITA_VPOS[]={
	11,"Posizione V"
};
code unsigned char JAP_VPOS[]={
	7,_C16,_C17,_J2b,_J1b,_J11,_J2c,_J0e
};
code unsigned char RUS_VPOS[]={
	13,_P1b,_o,_P19,_o,_P0e,_DOT,_P16,_o,_P07,_e,_p,_P05,_DOT
};
code unsigned char CHT_VPOS[]={
	4,_C16,_C17,_C14,_C15
};
code unsigned char CHI_VPOS[]={
	4,_C16,_C17,_C14,_C15
};

//Recall
code unsigned char ENG_RESET[]={
	6,"Recall"
};
code unsigned char FRA_RESET[]={
	6,"Rappel"
};
code unsigned char DEU_RESET[]={
	9,"Wiederruf"	
};
code unsigned char ESP_RESET[]={
	9,"Rellamada"
};
code unsigned char ITA_RESET[]={
	10,"Richiamaro"
};
code unsigned char JAP_RESET[]={
	4,_J17,_J29,_J11,_J0b
};
code unsigned char RUS_RESET[]={
	5,_C,_P08,_p,_o,_c
};
code unsigned char CHT_RESET[]={
	2,_C28,_C15
};
code unsigned char CHI_RESET[]={
	2,_C28,_C15
};
/*
//Color Temperature
code unsigned char ENG_COLOR[]={
	17,"Color Temperature"
};
code unsigned char FRA_COLOR[]={
	20,"Temperature couleurs"
};
code unsigned char DEU_COLOR[]={
	14,"Farbtemperatur"
};
code unsigned char ESP_COLOR[]={
	19,"Tempetatura Colores"
};
code unsigned char ITA_COLOR[]={
	18,"Temperatura Colore"
};
code unsigned char JAP_COLOR[]={
	3,0x81,0x82,0x86
};
code unsigned char CHI_COLOR[]={
	2,0x81,0x82
};
code unsigned char RUS_COLOR[]={
	18,'T','E','M',0xcf,'E','P','A',' ','T','y','P','A',' ',0xd4,'B','E','T','A'
};
//Language
code unsigned char ENG_LANG[]={
	8,"Language"
};
code unsigned char FRA_LANG[]={
	6,"Langue"
};
code unsigned char DEU_LANG[]={
	7,"Sprache"
};
code unsigned char ESP_LANG[]={
	6,"Idioma"
};
code unsigned char ITA_LANG[]={
	6,"Lingua"
};
code unsigned char JAP_LANG[]={
	2,0x7c,0x9a
};
code unsigned char CHI_LANG[]={
	2,0x7b,0x7c
};
code unsigned char RUS_LANG[]={
	4,0xc7,'3',0xc3,'K'
};
//Exit
code unsigned char ENG_EXIT[]={
	4,"Exit"
};
code unsigned char FRA_EXIT[]={
	7,"Quitter"
};
code unsigned char DEU_EXIT[]={
	9,"Verlassen"
};
code unsigned char ESP_EXIT[]={
	5,"Salir"
};
code unsigned char ITA_EXIT[]={
	6,"Uscita"
};
code unsigned char JAP_EXIT[]={
	2,0xb7,0xb8
};
code unsigned char CHI_EXIT[]={
	2,0x83,0x84
};
code unsigned char RUS_EXIT[]={
	5,'B',0xc3,'X','O',0xd3
};
*/
//Sharpness
code unsigned char ENG_SHAP[]={
	9,"Sharpness"
};
code unsigned char FRA_SHAP[]={
	7,"Nettet"
};
code unsigned char DEU_SHAP[]={
	7,"Schrfe"
};
code unsigned char ESP_SHAP[]={
	7,"Nitidez"
};
code unsigned char ITA_SHAP[]={
	9,"Nitidezza"
};
code unsigned char JAP_SHAP[]={
	6,_J06,_J07,_J03,_J08,_J0c,_J0d
};
code unsigned char RUS_SHAP[]={
	8,_P,_e,_3,_P00,_o,_c,_P05,_b
};
code unsigned char CHT_SHAP[]={
	3,_C2d,_C2e,_C1d
};
code unsigned char CHI_SHAP[]={
	3,_C2d,_C2e,_C1d
};
//OSD position
code unsigned char ENG_OSDPOS[]={
	12,"OSD Position"
};
code unsigned char FRA_OSDPOS[]={
	12,"Position OSD"
};
code unsigned char DEU_OSDPOS[]={
	12,"OSD Posicion"
};
code unsigned char ESP_OSDPOS[]={
	12,"Posicin OSD"
};
code unsigned char ITA_OSDPOS[]={
	13,"Posizione OSD"
};
code unsigned char JAP_OSDPOS[]={
	7,_O,_S,_D,_C14,_C15,_C19,_C1a
};
code unsigned char RUS_OSDPOS[]={
	12,_P1b,_o,_P19,_o,_P0e,_e,_P04,_P03,_e,_Space,_P12,_M
};
code unsigned char CHT_OSDPOS[]={
	4,_C0f,_C63,_C14,_C15
};
code unsigned char CHI_OSDPOS[]={
	4,_C3e,_C3f,_C14,_C15
};
/*
//OSD H position
code unsigned char ENG_OSDHPOS[]={
	12,"OSD Position"
};
code unsigned char FRA_OSDHPOS[]={
	12,"Position OSD"
};
code unsigned char DEU_OSDHPOS[]={
	12,"OSD Posicion"
};
code unsigned char ESP_OSDHPOS[]={
	15,"Posicin de OSD"
};
code unsigned char ITA_OSDHPOS[]={
	13,"Posizione OSD"
};
code unsigned char JAP_OSDHPOS[]={
	7,_O,_S,_D,_C14,_C15,_C19,_C1a
};
code unsigned char RUS_OSDHPOS[]={
	12,_P1b,_o,_P19,_o,_P0e,_e,_P04,_P03,_e,_Space,_P12,_M
};
code unsigned char CHT_OSDHPOS[]={
	4,_C0f,_C63,_C14,_C15
};
code unsigned char CHI_OSDHPOS[]={
	4,_C3e,_C3f,_C14,_C15
};

//OSD V position
code unsigned char ENG_OSDVPOS[]={
	21,"Vertical OSD Position"
};
code unsigned char FRA_OSDVPOS[]={
	22,"Position Verticale;OSD"
};
code unsigned char DEU_OSDVPOS[]={
	26,"Vertikale Position;des OSD"
};
code unsigned char ESP_OSDVPOS[]={
	21,"Posicin vertical OSD"
};
code unsigned char ITA_OSDVPOS[]={
	22,"Posizione verticale;OSD"
};
code unsigned char JAP_OSDVPOS[]={
	7,'O','S','D',0x8d,0xa5,0x8b,0xa6
};
code unsigned char CHI_OSDVPOS[]={
	7,'O','S','D',0x8d,0x8e,0x8b,0x8c
};
code unsigned char RUS_OSDVPOS[]={
	29,0xcf,'O',0xd0,'O',0xce,'E','H',0xc8,'E',' ','M','E','H',0xd1,';',0xcf,'O',
	' ',0xcb,'O','B','E','P','T',0xc8,'K','A',0xd0,0xc8	
};
*/
//Auto Setting
code unsigned char ENG_AUTOSET[]={
	12,"Auto Setting"
};
code unsigned char FRA_AUTOSET[]={
	12,"Rglage auto"
};
code unsigned char DEU_AUTOSET[]={
	13,"Autom. Einst."
};
code unsigned char ESP_AUTOSET[]={
	12,"Config. Auto"
};
code unsigned char ITA_AUTOSET[]={
	12,"Impost. aut."
};
code unsigned char JAP_AUTOSET[]={
	4,_C18,_C10,_C11,_C0e
};
code unsigned char RUS_AUTOSET[]={
	13,_A,_P07,_P05,_o,_P04,_a,_c,_P05,_p,_o,_P02,_P00,_a
};
code unsigned char CHT_AUTOSET[]={
	4,_C18,_C10,_C11,_C0e
};
code unsigned char CHI_AUTOSET[]={
	4,_C18,_C23,_C4c,_C0e
};
//Transparency OSD
code unsigned char ENG_TRANSOSD[]={
	14,"OSD Transparen"
};
/*
code unsigned char FRA_TRANSOSD[]={
	16,"Transparence OSD"
};
code unsigned char DEU_TRANSOSD[]={
	15,"OSD-Transparenz"
};
code unsigned char ESP_TRANSOSD[]={
	17,"Transparencia OSD"
};
code unsigned char ITA_TRANSOSD[]={
	16,"OSD Transparency"
};
code unsigned char JAP_TRANSOSD[]={
	6,'O','S','D','?','?','?'
};
code unsigned char CHI_TRANSOSD[]={
	6,'O','S','D','?','?','?'
};
code unsigned char RUS_TRANSOSD[]={
	17,0xcf,'P','O','3','P','A',0xcd,'H','O','C','T','b',' ','M','E','H',0xd1
};

//Auto and Input select
code unsigned char ENG_SOURSEL[]={
	12,"Input Select"
};
code unsigned char FRA_SOURSEL[]={
	21,"Select Auto et Entree"
};
code unsigned char DEU_SOURSEL[]={
	24,"Auto y Entrada;Seleccion"
};
code unsigned char ESP_SOURSEL[]={
	24,"Auto y Entrada;Seleccion"
};
code unsigned char ITA_SOURSEL[]={
	22,"Selezione Auto e;Input"
};
code unsigned char JAP_SOURCE[]={
	2,0xbb,0xbc
};
code unsigned char CHI_SOURCE[]={
	2,0xbb,0xbc
};
code unsigned char RUS_SOURCE[]={
	25,'A','B','T','O','M','A','T',0xc8,0xcd,'E','C','K',0xc8,0xc9,'B',';',0xc3,
	0xca,'O','P','B','X','O',0xd3,'A'
};
//Text/Graph Mode
code unsigned char ENG_TEXTMODE[]={
	10,"Graph/Text"
};
code unsigned char FRA_TEXTMODE[]={
	15,"Graphique/Texte"
};
code unsigned char DEU_TEXTMODE[]={
	10,"Graph/Text"
};
code unsigned char ESP_TEXTMODE[]={
	13,"Grefica/Texto"
};
code unsigned char ITA_TEXTMODE[]={
	13,"Grafico/Testo"
};
code unsigned char JAP_TEXTMODE[]={
	5,0x96,0x97,'/',0x7e,0x98
};
code unsigned char CHI_TEXTMODE[]={
	5,0x96,0x97,'/',0x7e,0x98
};
code unsigned char RUS_TEXTMODE[]={
	31,0xcb,'P','A',0xcc,0xc8,0xcd,'E','C','K',0xc8,0xc9,' ','P','E',0xce,0xc8,
	'M',';','T','E','K','C','T','O','B','O',0xc9,'P','E',0xce,0xc8,'M'	
};
*/
//Auto adjust
code unsigned char ENG_AUTOADJ[]={
	14,"Auto Adjust..."
};
code unsigned char FRA_AUTOADJ[]={
	22,"Rglage automatique..."
};
code unsigned char DEU_AUTOADJ[]={
	19,"Autom. Anpassung..."
};
code unsigned char ESP_AUTOADJ[]={
	20,"Ajuste automtico..."
};
code unsigned char ITA_AUTOADJ[]={
	22,"Regolazione automatica"
};
code unsigned char JAP_AUTOADJ[]={
	7,_C18,_C23,_C19,_C1a,_DOT,_DOT,_DOT
};
code unsigned char CHT_AUTOADJ[]={
	8,_C18,_C10,_C19,_C1a,_C01,_DOT,_DOT,_DOT
};
code unsigned char CHI_AUTOADJ[]={
	8,_C18,_C23,_C24,_C1a,_C01,_DOT,_DOT,_DOT
};
code unsigned char RUS_AUTOADJ[]={
	15,_A,_P07,_P05,_o,_P04,_a,_c,_P05,_p,_P02,_P00,_a,_DOT,_DOT,_DOT
};

// Volume
code unsigned char ENG_VOLUME[]={
	6,"Volume"
};
code unsigned char FRA_VOLUME[]={
	6,"Volume"
};
code unsigned char DEU_VOLUME[]={
	10,"Lautstrke"
};
code unsigned char ESP_VOLUME[]={
	7,"Volumen"
};
code unsigned char ITA_VOLUME[]={
	6,"Volume"
};
code unsigned char JAP_VOLUME[]={
	4,_C0c,_C0d,_C19,_C1a
};
code unsigned char RUS_VOLUME[]={
	9,_P09,_p,_o,_P17,_P00,_o,_c,_P05,_b
};
code unsigned char CHT_VOLUME[]={
	4,_C0c,_C0d,_C19,_C1a
};
code unsigned char CHI_VOLUME[]={
	4,_C0c,_C0d,_C24,_C1a
};

// Mute
code unsigned char ENG_MUTE[]={
	4,"Mute"
};
code unsigned char FRA_MUTE[]={
	4,"Muet"
};
code unsigned char DEU_MUTE[]={
	14,"Stummschaltung"
};
code unsigned char ESP_MUTE[]={
	8,"Silencio"
};
code unsigned char ITA_MUTE[]={
	4,"Mute"
};
code unsigned char JAP_MUTE[]={
	4,_J06,_J02,_J03,_J0b
};
code unsigned char RUS_MUTE[]={
	4,_P18,_P05,_y,_P00
};
code unsigned char CHT_MUTE[]={
	2,_C53,_C0c
};
code unsigned char CHI_MUTE[]={
	2,_C54,_C0c
};

//OSD Time Out
code unsigned char ENG_OSDTIME[]={
	12,"OSD Time Out"
};
code unsigned char FRA_OSDTIME[]={
	9,"Dlai OSD"
};
code unsigned char DEU_OSDTIME[]={
	11,"OSD-Auszeit"
};
code unsigned char ESP_OSDTIME[]={
	13,"Tiemp Esp OSD"
};
code unsigned char ITA_OSDTIME[]={
	11,"Timeout OSD"
};
code unsigned char JAP_OSDTIME[]={
	8,_O,_S,_D,_J00,_J01,_J03,_J04,_J05
};
code unsigned char RUS_OSDTIME[]={
	10,_P1b,_p,_o,_c,_P05,_o,_P02,_Space,_P12,_M
};
code unsigned char CHT_OSDTIME[]={
	6,_C0f,_C63,_C58,_C2a,_C59,_C5a
};
code unsigned char CHI_OSDTIME[]={
	6,_C3e,_C3f,_C29,_C2a,_C2b,_C2c
};
//Signal Out of Range
code unsigned char ENG_OUT[]={
	12,"Out of Range"
};
code unsigned char FRA_OUT[]={
	16,"Hors de la plage"
};
code unsigned char DEU_OUT[]={
	24,"Au|erhalb der Reichweite"
};
code unsigned char ESP_OUT[]={
	14,"Fuera de Rango"
};
code unsigned char ITA_OUT[]={
	13,"Fuori portata"
};
code unsigned char JAP_OUT[]={
	12,"Out of Range"
};
code unsigned char RUS_OUT[]={
	18,_H,_e,_P0a,_o,_P11,_y,_c,_P05,_P02,_P17,_P1a,_P02,_Space,_p,_e,_P0e,_P03,_P17
};
code unsigned char CHT_OUT[]={
	6,_C38,_C39,_C3a,_C3b,_C65,_C60
};
code unsigned char CHI_OUT[]={
	6,_C38,_C39,_C3a,_C3b,_C3c,_C3d
};

//No Signal
code unsigned char ENG_NOSIGNAL[]={
	15,"No Signal Input"
};
code unsigned char FRA_NOSIGNAL[]={
	13,"Pas de signal"
};
code unsigned char DEU_NOSIGNAL[]={
	18,"Kein Signaleingang"
};
code unsigned char ESP_NOSIGNAL[]={
	10,"Sin senal"
};
code unsigned char ITA_NOSIGNAL[]={
	15,"Selezione Input"
};
code unsigned char JAP_NOSIGNAL[]={
	4,_C0a,_C0b,_J20,_J21
};
code unsigned char RUS_NOSIGNAL[]={
	16,_H,_e,_P0f,_o,_P16,_y,_c,_P05,_P03,_P17,_P12,_p,_e,_P0e,_P03,_P17
};
code unsigned char CHT_NOSIGNAL[]={
	6,_C35,_C36,_C5d,_C5e,_C37,_C5c
};
code unsigned char CHI_NOSIGNAL[]={
	6,_C35,_C36,_C0a,_C0b,_C37,_C5c
};

//Hue
code unsigned char ENG_HUE[]={
	3,"Hue"
};

//Saturation
code unsigned char ENG_SATUR[]={
	5,"Color"
};
//Yes No string
code unsigned char ENG_YESNO[]={
	17,"  Yes        No  "
};
code unsigned char FRA_YESNO[]={
	17,"  Yes        No  "
};

//Auto Color
code unsigned char ENG_AUTOCOL[]={
	13,"White Balance"
};
//Auto Color
code unsigned char ENG_EEPROMINIT[]={
	12,"EEPROM INIT."
};
code unsigned char ENG_CHSEARCH[]={
	9,"CH SEARCH "
};

code unsigned char ENG_CHEDIT[]={
	7,"CH EDIT"
};
code unsigned char ENG_FINETUNE[]={
	9,"FINE TUNE"
};
code unsigned char ENG_TV_INPUT[]={
	8,"TV INPUT"
};

code unsigned char ENG_BACKLIGH[]={
	10,"Back Light"
};

code unsigned char VOID_CHAR[]={
	1,' '
};

code unsigned char ENG_FACTMENU[]={
	12,"Factory Menu"
};

code unsigned char SPACE[]={
	"                              "
};
//Light Contrast
code unsigned char ENG_LIGHTCONTRAST[]={
	14,"Light Contrast"
};

//Light Bright
code unsigned char ENG_LIGHTBRIGHT[]={
	12,"Light Bright"
};

//Light H start
code unsigned char ENG_LIGHTHS[]={
	13,"Light H Start"
};

//Light H width
code unsigned char ENG_LIGHTHW[]={
	13,"Light H Width"
};

//Light V start
code unsigned char ENG_LIGHTVS[]={
	13,"Light V Start"
};

//Light H width
code unsigned char ENG_LIGHTVH[]={
	13,"Light V Hight"
};

//Light Enable
code unsigned char ENG_LIGHTEN[]={
	12,"Light Enable"
};

//Light Enable
code unsigned char ENG_SCALERMODE[]={
	12,"Aspect Ratio"
};
//Closed Caption On/Off
code unsigned char ENG_CAPTIONMODE[]={
	14,"Closed Caption"
}; 
code unsigned char ENG_MPAARating[]={
	11,"MPAA Rating"
};
code unsigned char ENG_TVRating[]={
	9,"TV Rating"
};
//Treble/Bass
code unsigned char ENG_Treble[]={
	6,"Treble"
};
code unsigned char ENG_Bass[]={
	4,"Bass"
};
/*
code unsigned char LanguageDummy[]={
	0x7c,0x7d,0x7e,0x7f,0x80,0x81,0x82,0x83,0x84,0x85,
	0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,
	0x90,0x91,0x92,0x93,0x94,0x95,0x96,0x97,0x98,0x99,
	0x9a,0x9b,0x9c,0x9d,0x9e,0x9f,0xa0,0xa1,0xa2,0xa3,
};
*/
code unsigned char *DescTab[][9]={
	//_0 BRIGHTNESS 
	{ENG_BRIGHT,FRA_BRIGHT,DEU_BRIGHT,ESP_BRIGHT,
	ITA_BRIGHT,JAP_BRIGHT,RUS_BRIGHT,CHT_BRIGHT,CHI_BRIGHT},
	//_1 CONTRAST
	{ENG_CONTRAST,FRA_CONTRAST,DEU_CONTRAST,ESP_CONTRAST,
	ITA_CONTRAST,JAP_CONTRAST,RUS_CONTRAST,CHT_CONTRAST,CHI_CONTRAST},
	//_2 PHASE
	{ENG_PHASE,FRA_PHASE,DEU_PHASE,ESP_PHASE,
	ITA_PHASE,JAP_PHASE,RUS_PHASE,CHT_PHASE,CHI_PHASE},
	//_3 CLOCK
	{ENG_CLOCK,FRA_CLOCK,DEU_CLOCK,ESP_CLOCK,
	ITA_CLOCK,JAP_CLOCK,RUS_CLOCK,CHT_CLOCK,CHI_CLOCK},
	//_4 BACKLIGHT
	{ENG_BRIGHT,FRA_BRIGHT,DEU_BRIGHT,ESP_BRIGHT,
	ITA_BRIGHT,JAP_BRIGHT,RUS_BRIGHT,CHT_BRIGHT,CHI_BRIGHT},
	//{ENG_BACKLIGH,ENG_BACKLIGH,ENG_BACKLIGH,ENG_BACKLIGH,
	//ENG_BACKLIGH,ENG_BACKLIGH,ENG_BACKLIGH,ENG_BACKLIGH,ENG_BACKLIGH},
	//_5 HPOSITION
	{ENG_HPOS,FRA_HPOS,DEU_HPOS,ESP_HPOS,
	ITA_HPOS,JAP_HPOS,RUS_HPOS,CHT_HPOS,CHI_HPOS},
	//_6 VPOSITION
	{ENG_VPOS,FRA_VPOS,DEU_VPOS,ESP_VPOS,
	ITA_VPOS,JAP_VPOS,RUS_VPOS,CHT_VPOS,CHI_VPOS},
	//_7 OSD POSITION
	{ENG_OSDPOS,FRA_OSDPOS,DEU_OSDPOS,ESP_OSDPOS,
	ITA_OSDPOS,JAP_OSDPOS,RUS_OSDPOS,CHT_OSDPOS,CHI_OSDPOS},
	//_8 OSD V POSITION
	{ENG_OSDPOS,FRA_OSDPOS,DEU_OSDPOS,ESP_OSDPOS,
	ITA_OSDPOS,JAP_OSDPOS,RUS_OSDPOS,CHT_OSDPOS,CHI_OSDPOS},
	//_9 OSD TIMER
	{ENG_OSDTIME,FRA_OSDTIME,DEU_OSDTIME,ESP_OSDTIME,
	ITA_OSDTIME,JAP_OSDTIME,RUS_OSDTIME,CHT_OSDTIME,CHI_OSDTIME},
	//_10 SATURATION
	{ENG_SATUR,ENG_SATUR,ENG_SATUR,ENG_SATUR,
	ENG_SATUR,ENG_SATUR,ENG_SATUR,ENG_SATUR,ENG_SATUR},
	//_11 TINT
	{ENG_HUE,ENG_HUE,ENG_HUE,ENG_HUE,
	ENG_HUE,ENG_HUE,ENG_HUE,ENG_HUE,ENG_HUE},
	//_12 R GAIN
	{VOID_CHAR,VOID_CHAR,VOID_CHAR,VOID_CHAR,
	VOID_CHAR,VOID_CHAR,VOID_CHAR,VOID_CHAR,VOID_CHAR},
	//_13 G GAIN
	{VOID_CHAR,VOID_CHAR,VOID_CHAR,VOID_CHAR,
	VOID_CHAR,VOID_CHAR,VOID_CHAR,VOID_CHAR,VOID_CHAR},
	//_14 B GAIN
	{VOID_CHAR,VOID_CHAR,VOID_CHAR,VOID_CHAR,
	VOID_CHAR,VOID_CHAR,VOID_CHAR,VOID_CHAR,VOID_CHAR},
	//_15 COLOR TEMP.
	{VOID_CHAR,VOID_CHAR,VOID_CHAR,VOID_CHAR,
	VOID_CHAR,VOID_CHAR,VOID_CHAR,VOID_CHAR,VOID_CHAR},
	//{ENG_COLOR,FRA_COLOR,DEU_COLOR,ESP_COLOR,
	//ITA_COLOR,JAP_COLOR,RUS_COLOR,CHI_COLOR,CHI_COLOR},
	//_16 LANGUAGE
	{VOID_CHAR,VOID_CHAR,VOID_CHAR,VOID_CHAR,
	VOID_CHAR,VOID_CHAR,VOID_CHAR,VOID_CHAR,VOID_CHAR},
	//_17 SHAPNESS
	{ENG_SHAP,FRA_SHAP,DEU_SHAP,ESP_SHAP,
	ITA_SHAP,JAP_SHAP,RUS_SHAP,CHT_SHAP,CHI_SHAP},
	//_18 R ADC
	{VOID_CHAR,VOID_CHAR,VOID_CHAR,VOID_CHAR,
	VOID_CHAR,VOID_CHAR,VOID_CHAR,VOID_CHAR,VOID_CHAR},
	//_19 G ADC
	{VOID_CHAR,VOID_CHAR,VOID_CHAR,VOID_CHAR,
	VOID_CHAR,VOID_CHAR,VOID_CHAR,VOID_CHAR,VOID_CHAR},
	//_20 B ADC
	{VOID_CHAR,VOID_CHAR,VOID_CHAR,VOID_CHAR,
	VOID_CHAR,VOID_CHAR,VOID_CHAR,VOID_CHAR,VOID_CHAR},
	//_21 VOLUME
	{ENG_VOLUME,FRA_VOLUME,DEU_VOLUME,ESP_VOLUME,
	ITA_VOLUME,JAP_VOLUME,RUS_VOLUME,CHT_VOLUME,CHI_VOLUME},
	//_22 TRASN OSD
	{ENG_TRANSOSD,ENG_TRANSOSD,ENG_TRANSOSD,ENG_TRANSOSD,
	ENG_TRANSOSD,ENG_TRANSOSD,ENG_TRANSOSD,ENG_TRANSOSD,ENG_TRANSOSD},
//	{ENG_TRANSOSD,FRA_TRANSOSD,DEU_TRANSOSD,ESP_TRANSOSD,
//	ITA_TRANSOSD,JAP_TRANSOSD,RUS_TRANSOSD,CHI_TRANSOSD,CHI_TRANSOSD},
	//_23 VIDEO SOURCE
	{VOID_CHAR,VOID_CHAR,VOID_CHAR,VOID_CHAR,
	VOID_CHAR,VOID_CHAR,VOID_CHAR,VOID_CHAR,VOID_CHAR},
//	{ENG_SOURSEL,FRA_SOURSEL,DEU_SOURSEL,ESP_SOURSEL,
//	ITA_SOURSEL,JAP_SOURCE,RUS_SOURCE,CHI_SOURCE,CHI_SOURCE},
	//_24 BACKLIGHT2
	{ENG_BACKLIGH,ENG_BACKLIGH,ENG_BACKLIGH,ENG_BACKLIGH,
	ENG_BACKLIGH,ENG_BACKLIGH,ENG_BACKLIGH,ENG_BACKLIGH},
	//_25 VCMVOL
	{VOID_CHAR,VOID_CHAR,VOID_CHAR,VOID_CHAR,
	VOID_CHAR,VOID_CHAR,VOID_CHAR,VOID_CHAR,VOID_CHAR},
	//_26 pROFFSET
	{VOID_CHAR,VOID_CHAR,VOID_CHAR,VOID_CHAR,
	VOID_CHAR,VOID_CHAR,VOID_CHAR,VOID_CHAR,VOID_CHAR},
	//_27 pGOFFSET
	{VOID_CHAR,VOID_CHAR,VOID_CHAR,VOID_CHAR,
	VOID_CHAR,VOID_CHAR,VOID_CHAR,VOID_CHAR,VOID_CHAR},
	//_28 pBOFFSET
	{VOID_CHAR,VOID_CHAR,VOID_CHAR,VOID_CHAR,
	VOID_CHAR,VOID_CHAR,VOID_CHAR,VOID_CHAR,VOID_CHAR},
	//_29 pGOFFSET
	{VOID_CHAR,VOID_CHAR,VOID_CHAR,VOID_CHAR,
	VOID_CHAR,VOID_CHAR,VOID_CHAR,VOID_CHAR,VOID_CHAR},
	//_30 pGOFFSET
	{VOID_CHAR,VOID_CHAR,VOID_CHAR,VOID_CHAR,
	VOID_CHAR,VOID_CHAR,VOID_CHAR,VOID_CHAR,VOID_CHAR},
	//_31 pGOFFSET
	{VOID_CHAR,VOID_CHAR,VOID_CHAR,VOID_CHAR,
	VOID_CHAR,VOID_CHAR,VOID_CHAR,VOID_CHAR,VOID_CHAR},
	//_32 pGOFFSET
	{VOID_CHAR,VOID_CHAR,VOID_CHAR,VOID_CHAR,
	VOID_CHAR,VOID_CHAR,VOID_CHAR,VOID_CHAR,VOID_CHAR},
	//_33 pLIGHTCONTRAST
	{ENG_LIGHTCONTRAST,ENG_LIGHTCONTRAST,ENG_LIGHTCONTRAST,ENG_LIGHTCONTRAST,
	ENG_LIGHTCONTRAST,ENG_LIGHTCONTRAST,ENG_LIGHTCONTRAST,ENG_LIGHTCONTRAST,ENG_LIGHTCONTRAST},
	//_34 pLIGHTBRIGHT
	{ENG_LIGHTBRIGHT,ENG_LIGHTBRIGHT,ENG_LIGHTBRIGHT,ENG_LIGHTBRIGHT,
	ENG_LIGHTBRIGHT,ENG_LIGHTBRIGHT,ENG_LIGHTBRIGHT,ENG_LIGHTBRIGHT,ENG_LIGHTBRIGHT},
	//_35 pLIGHTHSTART
	{ENG_LIGHTHS,ENG_LIGHTHS,ENG_LIGHTHS,ENG_LIGHTHS,
	ENG_LIGHTHS,ENG_LIGHTHS,ENG_LIGHTHS,ENG_LIGHTHS,ENG_LIGHTHS},
	//_36 pLIGHTHWIDTH
	{ENG_LIGHTHW,ENG_LIGHTHW,ENG_LIGHTHW,ENG_LIGHTHW,
	ENG_LIGHTHW,ENG_LIGHTHW,ENG_LIGHTHW,ENG_LIGHTHW,ENG_LIGHTHW},
	//_37 pLIGHTVSTART
	{ENG_LIGHTVS,ENG_LIGHTVS,ENG_LIGHTVS,ENG_LIGHTVS,
	ENG_LIGHTVS,ENG_LIGHTVS,ENG_LIGHTVS,ENG_LIGHTVS,ENG_LIGHTVS},
	//_38 pLIGHTVHIGHT
	{ENG_LIGHTVH,ENG_LIGHTVH,ENG_LIGHTVH,ENG_LIGHTVH,
	ENG_LIGHTVH,ENG_LIGHTVH,ENG_LIGHTVH,ENG_LIGHTVH,ENG_LIGHTVH},
	//_39 pCHFINETUNE // Dummy
	{ENG_FINETUNE,ENG_FINETUNE,ENG_FINETUNE,ENG_FINETUNE,
	ENG_FINETUNE,ENG_FINETUNE,ENG_FINETUNE,ENG_FINETUNE,ENG_FINETUNE},
	// 40 treble
	{ENG_Treble,ENG_Treble,ENG_Treble,ENG_Treble,ENG_Treble,ENG_Treble,ENG_Treble,ENG_Treble,ENG_Treble},
	//41 Bass
	{ENG_Bass,ENG_Bass,ENG_Bass,ENG_Bass,ENG_Bass,ENG_Bass,ENG_Bass,ENG_Bass,ENG_Bass},
	//_41 FACT MENU
	{VOID_CHAR,VOID_CHAR,VOID_CHAR,VOID_CHAR,
	VOID_CHAR,VOID_CHAR,VOID_CHAR,VOID_CHAR,VOID_CHAR},
	//digital control
//_FACT MENU+1 ...AUDIO MUTE
	{ENG_MUTE,FRA_MUTE,DEU_MUTE,ESP_MUTE,
	ITA_MUTE,JAP_MUTE,RUS_MUTE,CHT_MUTE,CHI_MUTE},
	//_AUDIO MUTE+1 ...AUTO SETTING
	{ENG_AUTOSET,FRA_AUTOSET,DEU_AUTOSET,ESP_AUTOSET,
	ITA_AUTOSET,JAP_AUTOSET,RUS_AUTOSET,CHT_AUTOSET,CHI_AUTOSET},
	//_AUTO SETTING+1 ...RESET
	{ENG_RESET,FRA_RESET,DEU_RESET,ESP_RESET,
	ITA_RESET,JAP_RESET,RUS_RESET,CHT_RESET,CHI_RESET},
	//_43+1 ...AUTO COLOR
	{ENG_AUTOCOL,ENG_AUTOCOL,ENG_AUTOCOL,ENG_AUTOCOL,
	ENG_AUTOCOL,ENG_AUTOCOL,ENG_AUTOCOL,ENG_AUTOCOL,ENG_AUTOCOL},
	//_AUTO COLOR+1 ...AUTO ADJUST
	{ENG_AUTOADJ,FRA_AUTOADJ,DEU_AUTOADJ,ESP_AUTOADJ,
	ITA_AUTOADJ,JAP_AUTOADJ,RUS_AUTOADJ,CHT_AUTOADJ,CHI_AUTOADJ},
	//_AUTO ADJUST+1 ...TEXT MODE
	{VOID_CHAR,VOID_CHAR,VOID_CHAR,VOID_CHAR,
	VOID_CHAR,VOID_CHAR,VOID_CHAR,VOID_CHAR,VOID_CHAR},
	//_TEXT MODE+1.. pLIGHTEN
	{ENG_LIGHTEN,ENG_LIGHTEN,ENG_LIGHTEN,ENG_LIGHTEN,
	ENG_LIGHTEN,ENG_LIGHTEN,ENG_LIGHTEN,ENG_LIGHTEN,ENG_LIGHTEN},
	//_pLIGHTEN+1 ...pSCALERMODE
	{ENG_SCALERMODE,ENG_SCALERMODE,ENG_SCALERMODE,ENG_SCALERMODE,
	ENG_SCALERMODE,ENG_SCALERMODE,ENG_SCALERMODE,ENG_SCALERMODE,ENG_SCALERMODE},
	//_pSCALERMODE+1 ...INFORMATION	
	{VOID_CHAR,VOID_CHAR,VOID_CHAR,VOID_CHAR,
	VOID_CHAR,VOID_CHAR,VOID_CHAR,VOID_CHAR,VOID_CHAR},
	//_INFORMATION	+1 ...EXIT
	{VOID_CHAR,VOID_CHAR,VOID_CHAR,VOID_CHAR,
	VOID_CHAR,VOID_CHAR,VOID_CHAR,VOID_CHAR,VOID_CHAR},
	//{ENG_EXIT,FRA_EXIT,DEU_EXIT,ESP_EXIT,
	//ITA_EXIT,JAP_EXIT,RUS_EXIT,CHI_EXIT,CHI_EXIT},
	//_EXIT+1 ...OUT OF RANGE
	{ENG_OUT,FRA_OUT,DEU_OUT,ESP_OUT,
	ITA_OUT,ENG_OUT,ENG_OUT,ENG_OUT,ENG_OUT},
	//_OUT OF RANGE +1...NO SIGNAL
	{ENG_NOSIGNAL,FRA_NOSIGNAL,DEU_NOSIGNAL,ESP_NOSIGNAL,
	ITA_NOSIGNAL,JAP_NOSIGNAL,RUS_NOSIGNAL,CHT_NOSIGNAL,CHI_NOSIGNAL},
	//_NO SIGNAL+1 ...pEEPROMINIT
	{ENG_EEPROMINIT,ENG_EEPROMINIT,ENG_EEPROMINIT,ENG_EEPROMINIT,
	ENG_EEPROMINIT,ENG_EEPROMINIT,ENG_EEPROMINIT,ENG_EEPROMINIT,ENG_EEPROMINIT},
	//_pEEPROMINIT+1 ...pCHSEARCH
	{ENG_CHSEARCH,ENG_CHSEARCH,ENG_CHSEARCH,ENG_CHSEARCH,
	ENG_CHSEARCH,ENG_CHSEARCH,ENG_CHSEARCH,ENG_CHSEARCH,ENG_CHSEARCH},
	//_pCHSEARCH+1... pCHEDIT
	{ENG_CHEDIT,ENG_CHEDIT,ENG_CHEDIT,ENG_CHEDIT,
	ENG_CHEDIT,ENG_CHEDIT,ENG_CHEDIT,ENG_CHEDIT,ENG_CHEDIT},
	//_pCHEDIT+1 ...pCHFINETUNE
	{ENG_FINETUNE,ENG_FINETUNE,ENG_FINETUNE,ENG_FINETUNE,
	ENG_FINETUNE,ENG_FINETUNE,ENG_FINETUNE,ENG_FINETUNE,ENG_FINETUNE},
	//_pCHFINETUNE+1 ...pTVINPUT
	{ENG_TV_INPUT,ENG_TV_INPUT,ENG_TV_INPUT,ENG_TV_INPUT,
	ENG_TV_INPUT,ENG_TV_INPUT,ENG_TV_INPUT,ENG_TV_INPUT,ENG_TV_INPUT},
	//pTVINPUT+1 ...pCAPTION
	{ENG_CAPTIONMODE,ENG_CAPTIONMODE,ENG_CAPTIONMODE,
	ENG_CAPTIONMODE,ENG_CAPTIONMODE,ENG_CAPTIONMODE,
	ENG_CAPTIONMODE,ENG_CAPTIONMODE,ENG_CAPTIONMODE},
	
};
code unsigned char *DescTab_TV[][9]={
	//_53 pCHSEARCH
	{ENG_CHSEARCH,ENG_CHSEARCH,ENG_CHSEARCH,ENG_CHSEARCH,
	ENG_CHSEARCH,ENG_CHSEARCH,ENG_CHSEARCH,ENG_CHSEARCH,ENG_CHSEARCH},
	//_54 pCHEDIT
	{ENG_CHEDIT,ENG_CHEDIT,ENG_CHEDIT,ENG_CHEDIT,
	ENG_CHEDIT,ENG_CHEDIT,ENG_CHEDIT,ENG_CHEDIT,ENG_CHEDIT},
	//_55 pCHFINETUNE
	{ENG_FINETUNE,ENG_FINETUNE,ENG_FINETUNE,ENG_FINETUNE,
	ENG_FINETUNE,ENG_FINETUNE,ENG_FINETUNE,ENG_FINETUNE,ENG_FINETUNE},
	//_56 pTVINPUT
	{ENG_TV_INPUT,ENG_TV_INPUT,ENG_TV_INPUT,ENG_TV_INPUT,
	ENG_TV_INPUT,ENG_TV_INPUT,ENG_TV_INPUT,ENG_TV_INPUT,ENG_TV_INPUT},
};

code unsigned char *DescTab_Sound[][9]={
	//_21 VOLUME
	{ENG_VOLUME,FRA_VOLUME,DEU_VOLUME,ESP_VOLUME,
	ITA_VOLUME,JAP_VOLUME,RUS_VOLUME,CHT_VOLUME,CHI_VOLUME},
	//_40+1 AUDIO MUTE
	{ENG_MUTE,FRA_MUTE,DEU_MUTE,ESP_MUTE,
	ITA_MUTE,JAP_MUTE,RUS_MUTE,CHT_MUTE,CHI_MUTE},
 	// 65 Treble
	{ENG_Treble,ENG_Treble,ENG_Treble,ENG_Treble,ENG_Treble,ENG_Treble,ENG_Treble,ENG_Treble,ENG_Treble},
	// 66 Bass
	{ENG_Bass,ENG_Bass,ENG_Bass,ENG_Bass,ENG_Bass,ENG_Bass,ENG_Bass,ENG_Bass,ENG_Bass},
};

code unsigned char StrUser10[]={
	4,"User"
};
code unsigned char StrUser11[]={
	13,"Uinitialiser"
};
code unsigned char StrUser12[]={
	8,"Bentzer"
};
code unsigned char StrUser13[]={
	7,"Usuario"
};
code unsigned char StrUser14[]={
	6,"Utente"
};
code unsigned char StrUser15[]={
	4,_J02,_J03,_J28,_J03
};
code unsigned char StrUser16[]={
	12,_P1b,_o,_P19,_b,_3,_o,_P07,_a,_P05,_e,_P19,_b
};
code unsigned char StrUser17[]={
	5,_C42,_C43,_C44,_C18,_C0e
};
code unsigned char StrUser18[]={
	5,_C42,_C43,_C44,_C18,_C0e
};
code unsigned char Str93K[]={
	5,"9300$"
};
code unsigned char Str75K[]={
	5,"7500$"
};
code unsigned char Str65K[]={
	5,"6500$"
};
code unsigned char StrSRGB[]={
	5,"sRGB$"
};
code unsigned char *Tab_Color[]={
	Str93K,Str75K,Str65K,StrSRGB,StrUser10,
	Str93K,Str75K,Str65K,StrSRGB,StrUser11,
	Str93K,Str75K,Str65K,StrSRGB,StrUser12,
	Str93K,Str75K,Str65K,StrSRGB,StrUser13,
	Str93K,Str75K,Str65K,StrSRGB,StrUser14,
	Str93K,Str75K,Str65K,StrSRGB,StrUser15,
	Str93K,Str75K,Str65K,StrSRGB,StrUser16,
	Str93K,Str75K,Str65K,StrSRGB,StrUser17,
	Str93K,Str75K,Str65K,StrSRGB,StrUser18
};

code unsigned char StrR10[]={
	3,"Red"
};
code unsigned char StrR11[]={
	5,"Rouge"
};
code unsigned char StrR12[]={
	3,"Rot"
};
code unsigned char StrR13[]={
	4,"Rojo"
};
code unsigned char StrR14[]={
	5,"Rosso"
};
code unsigned char StrR15[]={
	1,_J32
};
code unsigned char StrR16[]={
	5,_K,_p,_a,_c,_P04
};
code unsigned char StrR17[]={
	2,_C50,_C1b
};
code unsigned char StrR18[]={
	2,_C46,_C1b
};
code unsigned char StrG10[]={
	5,"Green"
};
code unsigned char StrG11[]={
	4,"Vert"
};
code unsigned char StrG12[]={
	4,"Grn"
};
code unsigned char StrG13[]={
	5,"Verde"
};
code unsigned char StrG14[]={
	5,"Verde"
};
code unsigned char StrG15[]={
	1,_J36
};
code unsigned char StrG16[]={
	5,_P18,_e,_P19,_e,_P04
};
code unsigned char StrG17[]={
	2,_C4f,_C1b
};
code unsigned char StrG18[]={
	2,_C47,_C1b
};
code unsigned char StrB10[]={
	4,"Blue"
};
code unsigned char StrB11[]={
	4,"Bleu"
};
code unsigned char StrB12[]={
	4,"Blau"
};
code unsigned char StrB13[]={
	4,"Azul"
};
code unsigned char StrB14[]={
	3,"Blu"
};
code unsigned char StrB15[]={
	1,_J33
};
code unsigned char StrB16[]={
	6,_C,_P03,_P04,_e,_P0a,_o
};
code unsigned char StrB17[]={
	2,_C51,_C1b
};
code unsigned char StrB18[]={
	2,_C48,_C1b
};
code unsigned char *Tab_RGB[]={
	StrR10,StrG10,StrB10,
	StrR11,StrG11,StrB11,
	StrR12,StrG12,StrB12,
	StrR13,StrG13,StrB13,
	StrR14,StrG14,StrB14,
	StrR15,StrG15,StrB15,
	StrR16,StrG16,StrB16,
	StrR17,StrG17,StrB17,
	StrR18,StrG18,StrB17
};

code Byte ENG_USER[]={4,"User"};
code Byte FRA_USER[]={11,"Utilisateur"};
code Byte DEU_USER[]={8,"Bentzer"};
code Byte ESP_USER[]={7,"Usuario"};
code Byte ITA_USER[]={6,"Utente"};
code Byte JAP_USER[]={4,_J02,_J03,_J28,_J03};
code Byte CHI_USER[]={5,_C42,_C43,_C44,_C18,_C0e};
code Byte CHT_USER[]={5,_C42,_C43,_C44,_C18,_C0e};
code Byte RUS_USER[]={12,_P1b,_o,_P19,_b,_3,_o,_B,_a,_P05,_e,_P19,_b};
code Byte *UserTab[9]={ENG_USER,FRA_USER,DEU_USER,ESP_USER,ITA_USER,
						JAP_USER,RUS_USER,CHT_USER,CHI_USER};

code Byte ENG_ENTER[]={5,"Enter"};
code Byte FRA_ENTER[]={6,"Entree"};
code Byte DEU_ENTER[]={7,"Eingabe"};
code Byte ESP_ENTER[]={5,"Intro"};
code Byte ITA_ENTER[]={5,"Enter"};
code Byte JAP_ENTER[]={2,_C5c,_J1d};
code Byte CHI_ENTER[]={2,_C42,_C43};
code Byte CHT_ENTER[]={2,_C42,_C43};
code Byte RUS_ENTER[]={4,_B,_P07,_o,_P13};

code Byte ENG_SELECT[]={6,"Select"};
code Byte FRA_SELECT[]={11,'S',0x97,0x98,0x99,0x9a,0x9b,'o','n','n','e','r'};
code Byte DEU_SELECT[]={6,"Whlen"};
code Byte ESP_SELECT[]={6,"Selec."};
code Byte ITA_SELECT[]={9,"Selezione"};
code Byte JAP_SELECT[]={2,_C0f,_J35};
code Byte CHI_SELECT[]={2,_C30,_C31};
code Byte CHT_SELECT[]={2,_C0f,_C64};
code Byte RUS_SELECT[]={5,_B,_P00,_P08,_o,_p};

code Byte ENG_ADJUST[]={6,"Adjust"};
code Byte FRA_ADJUST[]={7,"Ajuster"};
code Byte DEU_ADJUST[]={10,"Einstellen"};
code Byte ESP_ADJUST[]={7,"Ajustar"};
code Byte ITA_ADJUST[]={11,"Regolazione"};
code Byte JAP_ADJUST[]={2,_C19,_C1a};
code Byte CHI_ADJUST[]={2,_C24,_C1a};
code Byte CHT_ADJUST[]={2,_C19,_C1a};
code Byte RUS_ADJUST[]={9,_H,_a,_c,_P05,_p,_o,_P02,_k,_a};

code unsigned char *KeyStrTab[]={
	ENG_ENTER,ENG_SELECT,ENG_ADJUST,
	FRA_ENTER,FRA_SELECT,FRA_ADJUST,
	DEU_ENTER,DEU_SELECT,DEU_ADJUST,
	ESP_ENTER,ESP_SELECT,ESP_ADJUST,
	ITA_ENTER,ITA_SELECT,ITA_ADJUST,
	JAP_ENTER,JAP_SELECT,JAP_ADJUST,
	RUS_ENTER,RUS_SELECT,RUS_ADJUST,
	CHT_ENTER,CHT_SELECT,CHT_ADJUST,
	CHI_ENTER,CHI_SELECT,CHI_ADJUST,
};

code Byte ENG_PICTURE[]={12,"Picture Mode"};
code Byte FRA_PICTURE[]={12,"Mode Picture"};
code Byte DEU_PICTURE[]={12,"Picutre Mode"};
code Byte ESP_PICTURE[]={13,"Modo Pelicula"};
code Byte ITA_PICTURE[]={16,"Modalit Picture"};
code Byte JAP_PICTURE[]={12,"Picture Mode"};
code Byte CHI_PICTURE[]={12,"Picture Mode"};
code Byte CHT_PICTURE[]={12,"Picture Mode"};
code Byte RUS_PICTURE[]={12,"Picture Mode"};

code Byte ENG_TEXT[]={9,"Text Mode"};
code Byte FRA_TEXT[]={10,"Mode Texte"};
code Byte DEU_TEXT[]={22,"Darstellung von Texten"};
code Byte ESP_TEXT[]={10,"Mode texto"};
code Byte ITA_TEXT[]={13,"Modalit Text"};
code Byte JAP_TEXT[]={9,"Text Mode"};
code Byte CHI_TEXT[]={9,"Text Mode"};
code Byte CHT_TEXT[]={9,"Text Mode"};
code Byte RUS_TEXT[]={9,"Text Mode"};

code Byte ENG_ECONOMY[]={7,"Economy"};
code Byte FRA_ECONOMY[]={8,"Economie"};
code Byte DEU_ECONOMY[]={11,"Sparsamkeit"};
code Byte ESP_ECONOMY[]={8,"economia"};
code Byte ITA_ECONOMY[]={7,"Economy"};
code Byte JAP_ECONOMY[]={7,"Economy"};
code Byte CHI_ECONOMY[]={7,"Economy"};
code Byte CHT_ECONOMY[]={7,"Economy"};
code Byte RUS_ECONOMY[]={7,"Economy"};

code unsigned char *TurboStrTab[]={
	ENG_PICTURE,ENG_TEXT,ENG_ECONOMY,
	FRA_PICTURE,FRA_TEXT,FRA_ECONOMY,
	DEU_PICTURE,DEU_TEXT,DEU_ECONOMY,
	ESP_PICTURE,ESP_TEXT,ESP_ECONOMY,
	ITA_PICTURE,ITA_TEXT,ITA_ECONOMY,
	JAP_PICTURE,JAP_TEXT,JAP_ECONOMY,
	RUS_PICTURE,RUS_TEXT,RUS_ECONOMY,
	CHT_PICTURE,CHT_TEXT,CHT_ECONOMY,
	CHI_PICTURE,CHI_TEXT,CHI_ECONOMY,
};

//Fact
code unsigned char FactAutoColor[]={
	10,"Auto Color"
};
code unsigned char FactEepromInit[]={
	11,"EEpromInit."
};
code unsigned char FactVcmVol[]={
	4,"Vcom"
};
code unsigned char FactBlackLevel[]={
	11,"Black Level"
};
code unsigned char FactR[]={
	1,"R"
};
code unsigned char FactG[]={
	1,"G"
};
code unsigned char FactB[]={
	1,"B"
};
code unsigned char FactNow[]={
	3,"Now"
};
code unsigned char FactMax[]={
	3,"Max"
};
code unsigned char FactMin[]={
	3,"Min"
};
code unsigned char FactAuto[]={
	9,"Auto Tune"
};

code ICONDEF MenuItem[7]={
	//function,position,icon index---For one bit icon
	//{pBRIGHTNESS	,ROW1+2		,0,6},		///0
	//{pCONTRAST		,ROW1+6		,0,1},		///1
	//{pHPOSITION		,ROW1+10	,0,2},		///2
	//{pVPOSITION		,ROW1+14	,0,0},		///3
	//{pSHARPNESS		,ROW1+18	,0,4},		///4
	//{pTRANSOSD		,ROW1+22	,0,3},	    ///5
	//function,position,icon index---For two bit icon
	{pBRIGHTNESS	,ROW1+2 	,0,0},		///0
	{pCONTRAST		,ROW1+6 	,0,1},		///1
	{pHPOSITION 	,ROW1+10	,0,2},		///2
	{pVPOSITION 	,ROW1+14	,0,3},		///3
	{pSHARPNESS 	,ROW1+18	,0,4},		///4
	{pTRANSOSD		,ROW1+22	,0,5},		///5
	{pTRANSOSD		,ROW1+26	,0,6},		///5
	};
Byte code RGBmenuItem[3]={pRCOLOR,pGCOLOR,pBCOLOR};	//level 1
//Byte code FactmenuItem[26]={pAUTOCOLOR,pEEPROMINIT,pVCMVOL,pBRIGHTNESS,pROFFSET,pGOFFSET,pBOFFSET,pRADC,pGADC,pBADC,
//							pRCOLOR,pGCOLOR,pBCOLOR,pRCOLOR,pGCOLOR,pBCOLOR,pRCOLOR,pGCOLOR,pBCOLOR,
//							pCONTRAST,pContMax,pContMin,pBACKLIGHT,pBrigMax,pBrigMin,pAUTOADJUST};
//------------------------------ pBACKLIGHT�� pBRIGHTNESS�� ����... +jwshin 061009
Byte code Page0Item[7]={pBRIGHTNESS,pCONTRAST,pCLOCK,pPHASE,pHPOSITION,pVPOSITION,pSHARPNESS};
Byte code Page0ItemD[3]={pBRIGHTNESS,pCONTRAST,pSHARPNESS};
Byte code Page0ItemY[5]={pBRIGHTNESS,pCONTRAST,pTINT,pSATURATION,pSHARPNESS};
Byte code Page0ItemV[5]={pBRIGHTNESS,pCONTRAST,pTINT,pSATURATION,pSHARPNESS};
Byte code Page1Item[4]={pVOLUME,pMUTE,pTreble,pBass};
//Byte code Page1Item[2]={pVOLUME,pMUTE};
Byte code Page2Item[7]={pCOLORTEMP,pCOLORTEMP,pCOLORTEMP,pCOLORTEMP,pRCOLOR,pGCOLOR,pBCOLOR};
Byte code Page3Item[9]={pLANGUAGE,pLANGUAGE,pLANGUAGE,pLANGUAGE,pLANGUAGE,pLANGUAGE,pLANGUAGE,pLANGUAGE,pLANGUAGE};
Byte code Page4Item[6]={pOSDTIMER,pOSDHPOSITION,pTRANSOSD,pAUTOSETTING,pRECALL,pSCALERMODE};
Byte code Page4ItemTV[7]={pOSDTIMER,pOSDHPOSITION,pTRANSOSD,pAUTOSETTING,pRECALL,pSCALERMODE,pCAPTION};
Byte code Page5Item[6]={pVIDEOSOURCE,pVIDEOSOURCE,pVIDEOSOURCE,pVIDEOSOURCE,pVIDEOSOURCE,pVIDEOSOURCE};
Byte code Page6Item[7]={pLIGHTEN,pLIGHTCONTRAST,pLIGHTBRIGHT,pLIGHTHSTART,pLIGHTHWIDTH,pLIGHTVSTART,pLIGHTVHIGHT};
Byte code Page7Item[4]={pCHSEARCH,pCHEDIT,pCHFINETUNE,pINPUT};

code FACTDEF FactItem[26]={
	//function,position,icon index
	{pAUTOCOLOR		,ROW2+1		,ROW2+1		,FactAutoColor	},		// 0
	{pAUTOADJUST	,ROW2+14	,ROW2+14	,FactAuto		},		// 1
	{pEEPROMINIT	,ROW3+1		,ROW3+1		,FactEepromInit	},		// 2
	{pVCMVOL		,ROW4+1		,ROW4+9		,FactVcmVol		},		// 3
	{pBRIGHTNESS	,ROW4+14 	,ROW4+26	,FactBlackLevel	},		// 4
	{pROFFSET		,ROW5+9		,ROW5+12	,FactR			},		// 5
	{pGOFFSET		,ROW5+16	,ROW5+19	,FactG			},		// 6
	{pBOFFSET		,ROW5+23	,ROW5+26	,FactB			},		// 7
	{pRADC			,ROW6+9		,ROW6+12	,FactR			},		// 8
	{pGADC			,ROW6+16	,ROW6+19	,FactG			},		// 9
	{pBADC			,ROW6+23	,ROW6+26	,FactB			},		// 10
	{pRCOLOR		,ROW7+9		,ROW7+12	,FactR			},		// 11
	{pGCOLOR		,ROW7+16	,ROW7+19	,FactG			},		// 12
	{pBCOLOR		,ROW7+23	,ROW7+26	,FactB			},		// 13
	{pRCOLOR		,ROW8+9		,ROW8+12	,FactR			},		// 14
	{pGCOLOR		,ROW8+16	,ROW8+19	,FactG			},		// 15
	{pBCOLOR		,ROW8+23	,ROW8+26	,FactB			},		// 16
	{pRCOLOR		,ROW9+9		,ROW9+12	,FactR			},		// 17
	{pGCOLOR		,ROW9+16	,ROW9+19	,FactG			},		// 18
	{pBCOLOR		,ROW9+23	,ROW9+26	,FactB			},		// 19
	{pCONTRAST		,ROW10+9	,ROW10+12	,FactNow		},		// 20
	{pContMax		,ROW10+16	,ROW10+19	,FactMax		},		// 21
	{pContMin		,ROW10+23	,ROW10+26	,FactMin		},		// 22
	{pBACKLIGHT		,ROW11+9	,ROW11+12	,FactNow		},		// 23
	{pBrigMax		,ROW11+16	,ROW11+19	,FactMax		},		// 24
	{pBrigMin		,ROW11+23	,ROW11+26	,FactMin		},		// 25
};

