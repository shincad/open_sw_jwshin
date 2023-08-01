#include "IIC.H"
#include "Scaler.H"
#include "MyDef.H"
#include "RAM.H"
#include "sRGB.H"
//#include "PANEL.H"
#include "nt68563_reg.h"

#if 1
#define LinearRGB

#ifdef LinearRGB
code int defautlTab[3][3]={
	{  0x1000,  0x0000,  0x0000 },
	{  0x0000,  0x1000,  0x0000 },
	{  0x0000,  0x0000,  0x1000 } 
};
#else
code int rgb2yuv[3][3]={
	{  0x041B,  0x0810,  0x0191 },
	{ -0x025F, -0x04A7,  0x0707 },
	{  0x0707, -0x05E2, -0x0124 } 
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

int sine(unsigned char alpha)
{
	unsigned char value = alpha & 0x3f;
	switch(alpha & 0xC0){
        case 0x00:
            return(sincos_tbl[value]);
        	break;
        case 0x40:
            return(sincos_tbl[(64 - value)]);
        	break;
        case 0x80:
            return(-sincos_tbl[value]);
        	break;
        case 0xC0:
            return(-sincos_tbl[(64 - value)]);
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
	for( i=0;i<3;i++){
		for( j=0;j<3;j++){
	        res = 0;
			for( k=0;k<3;k++){
				res += (long)*(first + i*3 + k) * (long)*(second + k*3 + j);
	        }
	        *(result + i*3 + j) = ((res + 2048)>>12);
		}
	}
}
#endif

void SetContrastRGB(void)
{
#define MAX_USERCONTRAST 	150
#define MID_USERCONTRAST 	128
#define MIN_USERCONTRAST 	78
	unsigned char i,j;
	int temp,gain[3];
	xdata int result[3][3];
	int UserPrefContrast;

#ifndef LinearRGB
	
	unsigned short ss,hh;
	xdata int adjust[3][3];
	xdata int UVrotated[3][3];

#endif
		gain[0] = ucR_Gain;
		gain[1] = ucG_Gain;
		gain[2] = ucB_Gain;

	if(ucContrast > 50){
		UserPrefContrast = ((unsigned short)(ucContrast-50) * (MAX_USERCONTRAST-MID_USERCONTRAST) + 25)/50 + MID_USERCONTRAST;
	}
	else{
		UserPrefContrast = ((unsigned short)ucContrast * (MID_USERCONTRAST-MIN_USERCONTRAST) + 25)/50 + MIN_USERCONTRAST;
	}
#ifndef LinearRGB
	ss = 128;
	hh = 0;
/*
	if(ucContrast > 50){
		UserPrefContrast = ((unsigned short)(ucContrast-50) * (MAX_CONTRAST-MID_CONTRAST) + 25)/50 + MID_CONTRAST;
	}
	else{
		UserPrefContrast = ((unsigned short)ucContrast * (MID_CONTRAST-MIN_CONTRAST) + 25)/50 + MIN_CONTRAST;
	}
*/


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
	
#else
	for(i=0; i<3; i++){
	  	for(j=0; j<3; j++){
				result[i][j] = defautlTab[i][j];
	  	}
	 }

	result[0][0] = (int)((float)result[0][0] * UserPrefContrast / 128 + 0.5);
	result[1][1] = (int)((float)result[1][1] * UserPrefContrast / 128 + 0.5);
	result[2][2] = (int)((float)result[2][2] * UserPrefContrast / 128 + 0.5);
#endif

	for(i=0; i<3; i++){
		WriteIIC560(0x1d0,((i * 2) + 0x21));
		for(j=0; j<3; j++){
			temp = (((((long)(result[i][j]+8)>>4)*((long)gain[i]<<4))+2048)>>12);
			if(temp < 0){
				temp = temp ^ 0xffff;
				temp +=1 ;
				temp |= 0xf400;
			}
#ifdef Debug
			printf("%x ",temp);
#endif
			WriteWordIIC560((0x1d1+(j*2)),temp);
		}
#ifdef Debug
		printf("\r\n");
#endif
	}

//	WriteIIC_WaitV(0x1d0,0x2d);
	WriteIIC_WaitV(SCALER_I2C_ADDR,0xd0,0x2d);	//0x2d
//	WriteIIC_WaitV(SCALER_I2C_ADDR,0xd0,0x3d);	//(noise testing)

}



#else
// STEWARD

void SetContrastRGB(void)
{
#define USER_GAIN_MAX	255
#define USER_GAIN_MIN 	127
#define USER_GAIN_RANGE 128

	unsigned int tR,tB,tG;
//	tR = 200+(unsigned int)(((double)100*ucR_Gain/255) * ((double)ucContrast/100));
//	tG = 200+(unsigned int)(((double)100*ucG_Gain/255) * ((double)ucContrast/100));
//	tB = 200+(unsigned int)(((double)100*ucB_Gain/255) * ((double)ucContrast/100));

	if ( ucColorTemperature == COLOR_USER )
	{
		tR = (unsigned short)ucR_Gain*USER_GAIN_RANGE/255+USER_GAIN_MIN;
		tG = (unsigned short)ucG_Gain*USER_GAIN_RANGE/255+USER_GAIN_MIN;
		tB = (unsigned short)ucB_Gain*USER_GAIN_RANGE/255+USER_GAIN_MIN;
	}
	else
	{
//#ifdef TC_ENABLE_TRUECOLOR
//		tR = 0xff;
//		tG = 0xff;
//		tB = 0xff;
//#else
		tR = ucR_Gain;
		tG = ucG_Gain;
		tB = ucB_Gain;
//#endif
	}
//printf("RGB0=%d\r\n",(unsigned short)ucContrast);
//printf("RGB0=%d,%d,%d\r\n",(unsigned short)tR,(unsigned short)tG,(unsigned short)tB);
 tR = (unsigned int)(((double)180+((double)150*ucContrast/100))*((double)tR/255)); //20060313 Steward modified //Set 250 in center point (Contrast=50%)
 tG = (unsigned int)(((double)180+((double)150*ucContrast/100))*((double)tG/255)); //20060313 Steward modified
 tB = (unsigned int)(((double)180+((double)150*ucContrast/100))*((double)tB/255));  //20060313 Steward modified
//printf("RGB1=%d,%d,%d\r\n",(unsigned short)tR,(unsigned short)tG,(unsigned short)tB);

	WriteIIC560(0x1d0,((0 * 2) + 0x21));
	WriteWordIIC560(0x1d1,tR);
	WriteWordIIC560(0x1d3,0);
	WriteWordIIC560(0x1d5,0);
	WriteIIC560(SRGB_COEF_OFFSET, ((unsigned short)ucBkOffset[0]*RGB_OFFSET_SCOPE)/255+RGB_OFFSET_MIN);
	
	WriteIIC560(0x1d0,((1 * 2) + 0x21));	
	WriteWordIIC560(0x1d1,0);
	WriteWordIIC560(0x1d3,tG);
	WriteWordIIC560(0x1d5,0);
	WriteIIC560(SRGB_COEF_OFFSET, ((unsigned short)ucBkOffset[1]*RGB_OFFSET_SCOPE)/255+RGB_OFFSET_MIN);

	WriteIIC560(0x1d0,((2 * 2) + 0x21));
	WriteWordIIC560(0x1d1,0);
	WriteWordIIC560(0x1d3,0);
	WriteWordIIC560(0x1d5,tB);
	WriteIIC560(SRGB_COEF_OFFSET, ((unsigned short)ucBkOffset[2]*RGB_OFFSET_SCOPE)/255+RGB_OFFSET_MIN);

//	WriteIIC_WaitV(0x1d0,0x2d);
	WriteIIC_WaitV(SCALER_I2C_ADDR,0xd0,0x2D); //0x2d
//	WriteIIC_WaitV(SCALER_I2C_ADDR,0xd0,0x3d);	//(noise testing)

//	tR=0x1FF;
}

#endif