/* sindotechno FND Test를 위한 firmware
written by jwshin 202005
*/



#include <MsTimer2.h>
#include <SPI.h>
#include <Ethernet.h>
#include <utility/w5100.h>
#include <avr/wdt.h>
#include <SoftwareSerial.h>


SoftwareSerial rs485(4,5);


volatile unsigned int DelayTick,SendIntervalTick,SendCallTick1,SendCallTick2,SendCallTick3,SendCallTick4,SendCallTick5;


char st[] = "90250120202020b4";
char st1[] = "40221ff8f2023f4a";
char st2[] = "41221FF8F2023F4B";
char st3[] = "40221ff8f100f185";
char st4[] = "40221ff8f101f184";
char st5[] = "40221ff8f102f187";
char st6[] = {144,37,1,32,32,32,32};
char st7[] = "90250120202020";


byte mac[] = {
	0xde,0xad,0xbe,0xef,0xfe,0xed
};


IPAddress ip(10,10,10,199);

IPAddress server(10,10,10,233);

EthernetClient client;


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

void UtilInit(void)
{
	DelayTick = 0;
	SendIntervalTick = 100;
	SendCallTick1 = 300;
	SendCallTick2 = 600;
	SendCallTick3 = 300;
	SendCallTick4 = 300;
	SendCallTick5 = 300;
}

unsigned char2digit(int ch) {
	static const char Hex[] = "0123456789ABCDEF0123456789abcdef";
  	char *p = memchr(Hex, ch, 32);
  	if (p) {
    	return (unsigned) (p - Hex) % 16;
  	}
  	return (unsigned) -1;  // error value
}

char *HexStringToString(char *dest, size_t size, const char *src) {
  	char *p = dest;
  	if (size <= 0) {
    	return NULL;
  	}
  	size--;
  	while (*src) {
    	if (size == 0) return NULL;
    	size--;

	    unsigned msb = char2digit(*src++);
	    if (msb > 15) return NULL;
	    unsigned lsb = char2digit(*src++);
	    if (lsb > 15) return NULL;
	    char ch = (char) (msb * 16 + lsb);

	    // Optionally test for embedded null character
	    if (ch == 0) return NULL;

	    *p++ = ch;
	}
	*p = '\0';
	return dest;
}

void testHex(const char *s) {
  	char buf[10];
  	char *dest = HexStringToString(buf, sizeof buf, s);
  	//printf("%-24s --> '%s'\n", s, dest ? dest : "NULL");
  	//Serial.print(dest);
  	rs485.print(dest);
}



unsigned char CRC8(const unsigned char *data, unsigned char len)
{
	unsigned char crc = 0x00;
	while(len--)
	{
		unsigned char extract = *data++;
		for(unsigned char temp = 8;temp;temp--)
		{
			unsigned char sum = (crc ^ extract) & 0x01;
			crc >>= 1;
			if(sum)
			{
				crc ^= 0x8c;
			}
			extract >>= 1;
		}
	}
	return crc;
}


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
		//Serial.print(Xor8(&st6[0]));
		st6[7] = Xor8(&st6[0]);
		Serial.print(st6);
		//rs485.print(st6); 
		SendIntervalTick = 100;	
	}

	
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
	
}