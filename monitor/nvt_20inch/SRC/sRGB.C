#include "IIC.H"
#include "Scaler.H"
#include "MyDef.H"
#include "RAM.H"
#include <stdio.h>

code int rgb2yuv[3][3]={
	{  0x041B,  0x0810,  0x0191 },
	{ -0x025F, -0x04A7,  0x0707 },
	{  0x0707, -0x05E2,  -0x0124 } 
};

code int yuv2rgb[3][3]={
	{  0x12A1,  0x0000,  0x1989 }, 
	{  0x12A1, -0x0644, -0x0D01 }, 
	{  0x12A1,  0x2046,  0x0000 }
};

code int sincos_tbl[65]={
	0x0000,0x0064,0x00C9,0x012D,0x0191,0x01F5,0x0259,0x02BC,0x031F,0x0381,
	0x03E3,0x0444,0x04A5,0x0505,0x0564,0x05C2,0x061F,0x067B,0x06D7,0x0731,
	0x078A,0x07E3,0x083A,0x088F,0x08E3,0x0937,0x0988,0x09D8,0x0A26,0x0A73,
	0x0ABF,0x0B08,0x0B50,0x0B97,0x0BDB,0x0C1E,0x0C5E,0x0C9D,0x0CDA,0x0D15,
	0x0D4D,0x0D85,0x0DB9,0x0DEC,0x0E1C,0x0E4B,0x0E77,0x0EA1,0x0EC8,0x0EEE,
	0x0F10,0x0F31,0x0F4F,0x0F6C,0x0F85,0x0F9C,0x0FB1,0x0FC4,0x0FD4,0x0FE1,
	0x0FEC,0x0FF5,0x0FFB,0x0FFE,0x1000
};

#if 1 
int sine(unsigned char alpha)
{
	unsigned char value = alpha & 0x3f;
	switch (alpha & 0xC0){
        case 0x00:
            return( sincos_tbl[value ]);
        	break;
        case 0x40:
            return( sincos_tbl[(64 - value) ]);
        	break;
        case 0x80:
            return(-sincos_tbl[value ]);
        	break;
        case 0xC0:
            return(-sincos_tbl[(64 - value) ]);
        	break;
    }
}

int cosine(unsigned char alpha)
{
    return (sine(alpha + 64));
}

void product(int *first, int * second, int *result)
{
unsigned char i,j,k;
long res;
	for ( i=0;i<3;i++){
		for ( j=0;j<3;j++){
	        res = 0;
			for ( k=0;k<3;k++){
				res += (long)*(first + i*3 + k) * (long)*(second + k*3 + j);
	        }
	        //*(result + i*3 + j) = ((res)>>12);
	        *(result + i*3 + j) = ((res + 2048)>>12);
		}
	}
}

void sRGB(Byte Contrast,Byte RedGain,Byte GreenGain,Byte BlueGain)
{
xdata Byte i,j;
xdata Word ss,hh;
xdata short temp,gain[3];
xdata short result[3][3];
xdata short adjust[3][3];
xdata short UVrotated[3][3];
xdata short UserPrefContrast;
#define Saturation 50
#define Tint 50

	gain[0] = (Word)(RedGain+0x80);//((Word)RedGain << 1) + 56;
	gain[1] = (Word)(GreenGain+0x80);//((Word)GreenGain<< 1) + 56;
	gain[2] = (Word)(BlueGain+0x80);//((Word)BlueGain<< 1) + 56;
//	gain[0] = (Word)(RedGain);//((Word)RedGain << 1) + 56;
//	gain[1] = (Word)(GreenGain);//((Word)GreenGain<< 1) + 56;
//	gain[2] = (Word)(BlueGain);//((Word)BlueGain<< 1) + 56;

	//ss = ((Word)Saturation * 256 + 50) / 100;
	//hh = (((Word)Tint * 256 + 50) / 100) - 128;
	if(FuncBuf[pVIDEOSOURCE] < 3){
		ss = ((Word)FuncBuf[pSATURATION] * 256 + 50) / 100;
		hh = (((Word)FuncBuf[pTINT] * 256 + 50) / 100) - 128;
	}
	else{
		ss = 220;		// +jwshin 050728
		hh = 0;
		}

	UserPrefContrast = (Word)(Contrast * 25) / 10;
	//UserPrefContrast = (Word)Contrast;
	for(i=0; i<3; i++){
		UVrotated[i][0] = 0;
	}
	for(i=0; i<3; i++){
		UVrotated[0][i] = 0;
	}
	
	UVrotated[1][1] = (((((long)ss<<5) * (long)cosine(hh))+2048)>>12);
	UVrotated[1][2] = (((((long)ss<<5) * (long)sine(hh)  )+2048)>>12);
	UVrotated[2][1] = (((-(long)sine(hh)*((long)ss<<5))+2048)>>12);
	UVrotated[2][2] = ((( (long)cosine(hh)*((long)ss<<5))+2048)>>12);
	product(&UVrotated[0][0], &rgb2yuv[0][0], &adjust[0][0]);
	
	for(i=0; i<3; i++){
		adjust[0][i] =((((long)rgb2yuv[0][i]*((long)UserPrefContrast << 5))+2048)>>12);
	}
	
	product(&yuv2rgb[0][0],&adjust[0][0],&result[0][0]);
	
	for(i=0; i<3; i++){
		WriteIIC563(0x1d0,((i * 2) + 0x21));
		for(j=0; j<3; j++){
			temp = (((((long)(result[i][j]+8)>>4)*((long)gain[i]<<4))+2048)>>12);
			if(temp < 0){
				temp = temp ^ 0xffff;
				temp +=1 ;
				temp |= 0xf400;
			}
			WriteWordIIC563((0x1d1+(j*2)),temp);
		}
	}
	WriteIIC563(0x1d0,0x2d);
}
#else
void sRGB(Byte Contrast,Byte RedGain,Byte GreenGain,Byte BlueGain)
{
#define Saturation 50
#define Tint		50
	xdata Byte i,j;
	xdata Word ss,hh;
	xdata short temp,gain[3];
	xdata short UserPrefContrast;
	code Byte arry[3][3]={
							{1,0,0},
							{0,1,0},
							{0,0,1}
						  };
	gain[0] = (Word)(RedGain + 0x80);//((Word)RedGain << 1) + 56;
	gain[1] = (Word)(GreenGain + 0x80);//((Word)GreenGain<< 1) + 56;
	gain[2] = (Word)(BlueGain + 0x80);//((Word)BlueGain<< 1) + 56;

	ss = ((Word)Saturation * 256 + 50) / 100;
	hh = (((Word)Tint * 256 + 50) / 100) - 128;

	//UserPrefContrast = (Word)(Contrast * 25) / 10;
	UserPrefContrast = (Word)Contrast * 256 /100;
	for(i=0; i<3; i++){
		//if(SCRev > 2)	//C version srgb dithering
			WriteIIC563(0x1d0,((i * 2) + 0x21));
		//else			//A and B version srgb dithering
		//	WriteIIC563(0x1d0,((i * 2) + 0x31));
		for(j=0; j<3; j++){
			temp = ((((long)(UserPrefContrast)*((long)gain[i]<<5))+2048)>>12)*(long)arry[i][j];
			if(temp < 0){
				temp = temp ^ 0xffff;
				temp +=1 ;
				temp |= 0xf400;
			}
			WriteWordIIC563((0x1d1+(j*2)),temp);
		}
	}
	//if(SCRev > 2)	//C version srgb dithering
		WriteIIC563(0x1d0,0x2d);
	//else			//A and B version srgb dithering
	//	WriteIIC563(0x1d0,0x3d);
}

#endif


