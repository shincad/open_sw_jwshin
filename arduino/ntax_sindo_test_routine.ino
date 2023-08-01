/* jungjin FND Test를 위한 firmware
written by jwshin 20200623
*/



#include <MsTimer2.h>
#include <SPI.h>
#include <Ethernet.h>
#include <utility/w5100.h>
#include <avr/wdt.h>
#include <SoftwareSerial.h>


SoftwareSerial rs485(4,5);


volatile unsigned int DelayTick,SendIntervalTick,SendCallTick1,SendCallTick2,SendCallTick3,SendCallTick4,SendCallTick5;

/*------------------------------- test를 위한 코드 선언 ----*/

/* 알파벳 대문자로 할 것 ! */
char st[] = "90250120202020B4";
char st1[] = "40221FF8F2023F4A";
char st2[] = "41221FF8F2023F4B";
char st3[] = "40221FF8F100F185";
char st4[] = "40221FF8F101F184";
char st5[] = "40221FF8F102F187";
char st7[] = "40221100F100F173";

unsigned int TotalCnt=111;
unsigned char Togg;


byte mac[] = {
	0xde,0xad,0xbe,0xef,0xfe,0xed
};


IPAddress ip(10,10,10,199);

IPAddress server(10,10,10,233);

EthernetClient client;


/* Timer Interrupt */
void TickIsr(void)
{
	if(DelayTick!=0) DelayTick--;
	if(SendIntervalTick!=0) SendIntervalTick--;
	if(SendCallTick1!=0) SendCallTick1--;
	if(SendCallTick2!=0) SendCallTick2--;
	if(SendCallTick3!=0) SendCallTick3--;
	if(SendCallTick4!=0) SendCallTick4--;
	if(SendCallTick5!=0) SendCallTick5--;


}

/* 변수 초기화 */
void UtilInit(void)
{
	TotalCnt = 0;
	DelayTick = 0;
	SendIntervalTick = 100;
	SendCallTick1 = 300;
	SendCallTick2 = 600;
	SendCallTick3 = 300;
	SendCallTick4 = 300;
	SendCallTick5 = 300;
}


unsigned char hex_to_int(unsigned char c){
        unsigned int first = c / 16 - 3;
        unsigned int second = c % 16;
        unsigned int result = first*10 + second;
        if(result > 9) result--;
        return result;
}

//--------------hex 값을 Ascii 값으로 변환
unsigned char hex_to_ascii(unsigned char c, unsigned char d){
        unsigned int high = hex_to_int(c) * 16;
        unsigned int low = hex_to_int(d);
        return high+low;
}

// Power On Code 전송을 위한 Routine
void ConvSend()
{
	unsigned int length = strlen(st);
	unsigned int i;
	unsigned char buf = 0;
	for(i=0;i<length;i++)
	{
		if(i%2!=0)
		{
			//Serial.write(hex_to_ascii(buf,st[i]));
			rs485.write(hex_to_ascii(buf,st[i]));
		}
		else
		{
			buf = st[i];
		}
	}
}

//--- 호출코드 전송 Routine
void CalcFunc()
{
	char buffer[]={};
	String Temp;
	String Temp2;
	String Temp3;
	unsigned int length;
	unsigned int x;
	unsigned char *Temp4;
	unsigned char buf=0;
	unsigned char buf2[16];
	unsigned char buf3[8];
	//for(int i = 1;i<1000;i++)
	if(TotalCnt<1000)
	{
		// int를 ascii로 변환 
		Temp = itoa(TotalCnt,buffer,10);
		Temp2 = Temp;

		TotalCnt+=111;
		// 신도 순번에 맞는 초기 Packet과 중간 순번 대기 및 호출번호 데이터 합성
		if(Togg==0)
			Temp3 = "40221"+Temp2+"F"+Temp2+"F1";
		else
			Temp3 = "40225"+Temp2+"F"+Temp2+"F1"; 
		
		// Temp3안에 있는 String Data(Hex)를 ASCII로 변환 배열 1,3,5,7,9,11,13 (총 7개 배열로 저장)
		for(int j=0;j<14;j++)
		{
			if(j%2!=0)
			{
				buf2[j] = hex_to_ascii(buf,Temp3[j]);
				//Serial.write(buf2[j]);
			}
			else
			{
				buf=Temp3[j];
			}
		}
		
		// 저장된 배열을 순차적으로 만들기 위해, buf3[0]-buf3[6]까지 저장
		x=0;
		for(int k=1;k<=15;k+=2)
		{
			buf3[x]=buf2[k];
			x++;
		}
		// Xor8 routine을 이용해서 Xor Checksum을 생성한 후, 이 값을 제일 마지막 배열인 buf3[7]에 저장
		buf3[7]=Xor8(&buf3[0]);
		// 완성된 8 Byte Data를 순차적으로 rs485로 전송.
		for(int p=0;p<8;p++)
		{
			//Serial.write(buf3[p]);
			rs485.write(buf3[p]);
		}

		delay(1000);	
	}
	if(TotalCnt>1000)
	{
		TotalCnt = 111;
		Togg ^= 0xff;
	}



}

void TestRoutine(void)
{

}


//-------------------- Xor chekcsum 생성 routine
unsigned char Xor8(const unsigned char *data)
{
	//unsigned char crc = data[0];
	unsigned char crc = data[0];
		//unsigned char extract = *data++;
	unsigned char extract;
	for(unsigned char temp = 1;temp<7;temp++)
	{
		extract = data[temp];
		crc ^= extract;
	}
	return crc;
}



void setup()
{
	//Ethernet.begin(mac,ip);

	rs485.begin(19200);
	Serial.begin(19200);
	MsTimer2::set(10,TickIsr);
    MsTimer2::start();
	//client.connect(server,8888);
}


void loop()
{
	
	if(SendIntervalTick==0)
	{
		//testHex(st);
		//Serial.print(CRC8(&st6[0],7));
		ConvSend();
		//CalcFunc();
		SendIntervalTick = 300;	
	}

	if(SendCallTick1==0)
	{
		CalcFunc();
		SendCallTick1 = 10;
	}

	/*
	if(SendCallTick1==0)
	{
		testHex(st1);
		SendCallTick1 = 600;
	}
	if(SendCallTick2==0)
	{
		testHex(st2);
		SendCallTick2 = 600;
	}
	*/
}