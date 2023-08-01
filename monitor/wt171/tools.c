#include	"TopHeader.h"
#include "extern.h"
#include "Tools.h"

void DelayNOP20()		// Lcall is 4byte 4cycle
{
	NOPx10;
	NOPx6;
	NOP;
	NOP;	
}

void DelayNOP12()		// Lcall is 4byte 4cycle
{
	NOPx6;
	NOP;
	NOP;
}

void DelayNOP10()		// Lcall is 4byte 4cycle
{
	NOPx6;
}

void DelayNOP6()		// Lcall is 4byte 4cycle
{
	NOP;
	NOP;
}
/*memorysave
void DelayNOP25()		// 25uS
{
	NOPx10;
	NOPx6;
	NOP;
	NOP;
	NOP;
	NOP;
	NOP;	
}
*/

#if defined(USE_UART)
void putss(BYTE value)
{
	BYTE temp;

	temp=value>>4;
	if (temp>=0x0A)  DBGputchar('A'+temp-0x0A);
	else 	DBGputchar('0'+temp);		
	temp=value&0x0f;
	if (temp>=0x0A)  DBGputchar('A'+temp-0x0A);
	else 	DBGputchar('0'+temp);			

}
#endif

#ifdef USE_TTXIIC

bit TTX_WriteData(BYTE temp)
{

	xdata BYTE count;
	
	for(count=0;count<8;count++) {
		
		TTX_SDA = ((temp&0x80)?1:0);//MSB
		DelayNOP6();
		TTX_SCL = 1;
		DelayNOP6();	
		TTX_SCL = 0;
		temp<<=1;
		}


	
	//DelayNOP6();
	//SDA = 1;		//Force to high!
	DelayNOP12();
	TTX_SCL = 1;
	DelayNOP6();
	if(TTX_SDA)//fail(Not ack!)
	{
		DelayNOP12();
		TTX_SCL=0;
		return 1;
	}
	else//success
	{
		DelayNOP12();
		TTX_SCL=0;
		return 0;
	}
}

	
bit TTX_START_I2C(BYTE sysaddr)
{
	DelayNOP12();

	//TTX_SCL = 1;//Critical Issue!!
	//TTX_SDA = 1;
		
	TTX_SDA = 1;
	TTX_SCL = 1;
	
	DelayNOP12();
	TTX_SDA = 0;		//START!
	DelayNOP12();
	TTX_SCL = 0;
	DelayNOP12();
	if(BTC_WriteData(sysaddr)) return 1;//fail!!
	else	return 0;				//success!!
}			

	

void TTX_STOP_I2C(void)
{
	DelayNOP12();
	
	//TTX_SCL = 1;//Critical Issue!!
	//TTX_SDA = 0;

	TTX_SDA = 0;
	TTX_SCL = 1;

	DelayNOP12();
	TTX_SDA = 1;		//STOP!
	DelayNOP12();

}

//#if	defined(VPC323x)
WORD TTX_ReadDataACK(void)
{
	xdata BYTE count;
	BYTE idata IICdata;

	for(count=0;count<8;count++) {
		IICdata<<= 1;
		TTX_SCL = 1;
		DelayNOP6();
		IICdata |= TTX_SDA;
		DelayNOP6();
		TTX_SCL = 0;
		DelayNOP6();
		}

	TTX_SDA = 0;	//ACK!!!를 준다.
	DelayNOP6();
	TTX_SCL = 1;
	DelayNOP12();
	TTX_SCL = 0;
	return (IICdata);
}
//#endif

WORD TTX_ReadDataNAK(void)
{
	xdata BYTE count;
	BYTE idata IICdata;
	
	for(count=0;count<8;count++) 
	{
		IICdata<<= 1;
		TTX_SCL = 1;
		DelayNOP6();
		IICdata |= TTX_SDA;
		DelayNOP6();
		TTX_SCL = 0;
		DelayNOP6();
	}
	
	TTX_SDA = 1;	//ACK!!!를 안준다.
	DelayNOP6();
	TTX_SCL = 1;
	DelayNOP12();
	TTX_SCL = 0;
	TTX_STOP_I2C();
	return (IICdata);
}
		
#endif
