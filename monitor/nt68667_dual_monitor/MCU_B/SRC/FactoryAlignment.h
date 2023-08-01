#ifndef _FactoryAlignment_H_
#define  _FactoryAlignment_H_

enum tcCommandFormat{
	tcCommandType = 4,		//4
	tcPatternType,			//5
	tcData1,				//6
	tcData2,				//7
	tcData3,				//8
	tcData4				//9
};

enum tcCommandID{
	tcCommandx = 0x30,		//0x30
	tcCommandy,				//0x31
	tcCommandY				//0x32
};

enum tcPatternID{
	tcStart = 0,
	tcPatternWhite = 0x30,	//0x30
	tcPatternRed,		//0x31
	tcPatternGreen,		//0x32
	tcPatternBlue,		//0x33
	tcPatternBlack,		//0x34
	tcPatternGray00,	//0x35
	tcPatternGray10,	//0x36
	tcPatternGray20,	//0x37
	tcPatternGray30,	//0x38
	tcPatternGray40,	//0x39
	tcPatternGray50 = 0x41,	//0x41
	tcPatternGray60,	//0x42
	tcPatternGray70,	//0x43
	tcPatternGray80,	//0x44
	tcPatternGray90,	//0x45
	tcPatternGrayA0,	//0x46
	tcPatternGrayB0,	//0x47
	tcPatternGrayC0,	//0x48
	tcPatternGrayD0,	//0x49
	tcPatternGrayE0,	//0x4a
	tcPatternGrayF0,	//0x4b
	tcPatternGrayFF,	//0x4c
	tcDummy=0xff
};

void BenQ_FactoryAlignment(void);

#endif
