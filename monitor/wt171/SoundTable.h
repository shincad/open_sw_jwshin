//**************************************************************************
//
//		SoundTable.h
//    		AUDIO processor source
//   		Written by smpark
//		Start at 2003.7.23
//
//**************************************************************************

#if !defined  _NFREN_SOUND_TABLE_
#define _NFREN_SOUND_TABLE_

/*
BYTE code VolumeTable[101]={		// 1.3
0,									//0
36 ,40 ,43 ,46 ,49 ,53 ,57 ,60 ,64 ,68 ,		//0
72 ,76 ,80 ,84 ,88 ,91 ,95 ,98 ,101,104,//1	//1
106,111,114,117,120,125,129,132,136,142,//2//2
146,150,152,155,157,159,162,164,166,167,//3//3
169,170,172,173,174,176,177,178,180,181,//4//4

182,183,184,185,186,187,188,189,190,191,//5
192,193,194,195,196,197,198,199,200,200,//6
201,201,202,202,203,203,204,204,205,205,//7
206,206,207,207,208,208,209,210,211,212,//8
213,214,215,216,217,218,219,220,221,222,//9
};
*/

// smpark 20030722
unsigned char code BassLevel[101]={
0xA0,	// 0	: -12 dB
0xA8,	// 1	: -11 dB
0xAA,	// 2
0xAC,	// 3
0xAE,	// 4
0xB0,	// 5
0xB2,	// 6 
0xB4,	// 7  
0xB6,	// 8 
0xB8,	// 9 

0xBA,	// 10
0xBC,	// 11
0xBE,	// 12
0xC0,	// 13
0xC2,	// 14
0xC4,	// 15
0xC6,	// 16
0xC8,	// 17
0xCA,	// 18
0xCB,	// 19

0xCC,	// 20 
0xCE,	// 21
0xCF,	// 22
0xD1,	// 23
0xD2,	// 24
0xD4,	// 25
0xD5,	// 26
0xD7,	// 27
0xD8,	// 28
0xDA,	// 29

0xDB,	// 30 
0xDD,	// 31
0xDE,	// 32
0xE0,	// 33
0xE1,	// 34
0xE3,	// 35
0xE4,	// 36
0xE6,	// 37
0xE7,	// 38
0xE9,	// 39

0xEA,	// 40
0xEC,	// 41
0xED,	// 42
0xEF,	// 43
0xF0,	// 44
0xF2,	// 45
0xF3,	// 46
0xF5,	// 47
0xF6,	// 48
0xF8,	// 49   :  -1 dB

0x00,	// 50   :   0 dB	
0x08,	// 51   :   1 dB
0x0A,	// 52
0x0B,	// 53
0x0D,	// 54
0x0F,	// 55
0x11,	// 56
0x12,	// 57
0x14,	// 58
0x15,	// 59

0x17,	// 60
0x18,	// 61
0x1A,	// 62
0x1B,	// 63
0x1D,	// 64
0x1F,	// 65
0x21,	// 66
0x23,	// 67
0x25,	// 68
0x27,	// 69

0x29,	// 70
0x2B,	// 71
0x2D,	// 72
0x2F,	// 73
0x31,	// 74
0x33,	// 75
0x35,	// 76
0x37,	// 77
0x39,	// 78
0x3B,	// 79

0x3D,	// 80
0x3F,	// 81
0x41,	// 82
0x43,	// 83
0x45,	// 84
0x47,	// 85
0x49,	// 86
0x4B,	// 87
0x4D,	// 88
0x4F,	// 89

0x51,	// 90
0x53,	// 91
0x55,	// 92
0x57,	// 93
0x58,	// 94   :  11 dB
0x60,	// 95   :  12 dB
0x64,	// 96
0x68,	// 97	:  14 dB 
0x70,	// 98	:  16 dB
0x78,	// 99	:  18 dB 

0x7F	// 100	:  20 dB
};

// smpark 20030722
unsigned char code TrebleLevel[101]={
0xA0,	// 0	: -12 dB
0xA8,	// 1	: -11 dB
0xAA,	// 2
0xAC,	// 3
0xAE,	// 4
0xB0,	// 5
0xB2,	// 6 
0xB4,	// 7  
0xB6,	// 8 
0xB8,	// 9

0xBA,	// 10 
0xBC,	// 11
0xBE,	// 12
0xC0,	// 13
0xC2,	// 14
0xC4,	// 15
0xC6,	// 16
0xC8,	// 17
0xCA,	// 18
0xCB,	// 19

0xCC,	// 20 
0xCE,	// 21
0xCF,	// 22
0xD1,	// 23
0xD2,	// 24
0xD4,	// 25
0xD5,	// 26
0xD7,	// 27
0xD8,	// 28
0xDA,	// 29

0xDB,	// 30 
0xDD,	// 31
0xDE,	// 32
0xE0,	// 33
0xE1,	// 34
0xE3,	// 35
0xE4,	// 36
0xE6,	// 37
0xE7,	// 38
0xE9,	// 39

0xEA,	// 40
0xEC,	// 41
0xED,	// 42
0xEF,	// 43
0xF0,	// 44
0xF2,	// 45
0xF3,	// 46
0xF5,	// 47
0xF6,	// 48
0xF8,	// 49   :  -1 dB

0x00,	// 50   :   0 dB	
0x08,	// 51   :   1 dB
0x0A,	// 52
0x0B,	// 53
0x0D,	// 54
0x0F,	// 55
0x11,	// 56
0x12,	// 57
0x14,	// 58
0x15,	// 59

0x17,	// 60
0x18,	// 61
0x1A,	// 62
0x1B,	// 63
0x1D,	// 64
0x1F,	// 65
0x21,	// 66
0x23,	// 67
0x25,	// 68
0x27,	// 69

0x29,	// 70
0x2B,	// 71
0x2D,	// 72
0x2F,	// 73
0x31,	// 74
0x33,	// 75
0x35,	// 76
0x37,	// 77
0x39,	// 78
0x3B,	// 79

0x3D,	// 80
0x3F,	// 81
0x41,	// 82
0x43,	// 83
0x45,	// 84
0x47,	// 85
0x49,	// 86
0x4B,	// 87
0x4D,	// 88
0x4F,	// 89

0x51,	// 90
0x53,	// 91
0x55,	// 92
0x57,	// 93
0x58,	// 94
0x60,	// 95
0x64,	// 96
0x68,	// 97 
0x69,	// 98
0x70,	// 99 	:  14 dB

0x78	// 100 	:  15 dB 
};

// smpark 20030722
unsigned char code LoudnessLevel[101]={

0x00,	// 0     :   0 dB	
0x01,	// 1     :   0.25 dB
0x01,	// 2     :   0.25 dB
0x02,	// 3     :   0.5 dB
0x02,	// 4     :   0.5 dB
0x03,	// 5     :   0.75 dB
0x03,	// 6     :   0.75 dB
0x04,	// 7     :   1 dB
0x04,	// 8     :   1 dB
0x05,	// 9

0x06,	// 10
0x06,	// 11
0x07,	// 12
0x08,	// 13
0x08,	// 14
0x09,	// 15
0x0A,	// 16
0x0A,	// 17
0x0B,	// 18
0x0C,	// 19

0x0C,	// 20
0x0D,	// 21
0x0E,	// 22
0x0E,	// 23
0x0F,	// 24
0x10,	// 25
0x10,	// 26
0x11,	// 27
0x12,	// 28
0x12,	// 29

0x13,	// 30
0x14,	// 31
0x14,	// 32
0x15,	// 33
0x16,	// 34
0x16,	// 35
0x16,	// 36
0x17,	// 37
0x18,	// 38
0x18,	// 39

0x19,	// 40
0x1A,	// 41
0x1A,	// 42
0x1B,	// 43
0x1C,	// 44
0x1C,	// 45
0x1D,	// 46
0x1E,	// 47
0x1E,	// 48
0X1F,	// 49

0x20,	// 50
0x20,	// 51
0x21,	// 52
0x22,	// 53
0x22,	// 54
0x23,	// 55
0x24,	// 56
0x24,	// 57
0x25,	// 58
0x26,	// 59

0x26,	// 60
0x27,	// 61
0x28,	// 62
0x28,	// 63
0x29,	// 64
0x2A,	// 65
0x2A,	// 66
0x2B,	// 67
0x2C,	// 68
0x2C,	// 69

0x2D,	// 70
0x2E,	// 71
0x2E,	// 72
0x2F,	// 73
0x30,	// 74
0x30,	// 75
0x31,	// 76
0x32,	// 77
0x32,	// 78
0x33,	// 79

0x34,	// 80
0x34,	// 81
0x35,	// 82
0x36,	// 83
0x36,	// 84
0x37,	// 85
0x38,	// 86
0x38,	// 87
0x39,	// 88
0x3A,	// 89

0x3A,	// 90
0x3B,	// 91
0x3C,	// 92
0x3C,	// 93
0x3D,	// 94
0x3E,	// 95
0x3E,	// 96
0x3F,	// 97
0x3F,	// 98
0x40,	// 99	:  16 dB
0x44	// 100	:  17 dB
};

#endif //_NFREN_SOUND_TABLE_
