#include <SPI.h>
#include <Ethernet.h>
#include <EthernetUdp.h>
#include <MsTimer2.h>
#include <SoftwareSerial.h>


SoftwareSerial rs485(4,5);

#define MESSAGE_GAP_TIMEOUT_IN_MS	5
#define LED_TOGGLE_MEGS	50

byte mac[] = {
	0xDE,0xAD,0xBE,0xEF,0xFE,0xED
};
//IPAddress local_ip(192,168,0,100);
IPAddress local_ip(10,10,10,199);
IPAddress remote_ip(255,255,255,255);

unsigned int localPort = 8888;

char RecvBuffer[256];

EthernetUDP Udp;

unsigned int recvIndex = 0;
unsigned long msgIndex = 0;
unsigned long receiveTime = 0;

char receiveTimeString[32];
char msgIndexString[32];

const byte LED_PIN = 9;

void setup()
{
  Ethernet.begin(mac, local_ip);
  Udp.begin(localPort);
  
  rs485.begin(19200);
  
  pinMode(LED_PIN, OUTPUT);

  // set an end-of-message detection timeout of 5ms
  MsTimer2::set(MESSAGE_GAP_TIMEOUT_IN_MS, onTimer);
}

bool dumpData = false;
bool timerStarted = false;

// If this timer expires, this means no additional character was received for a while: notify main loop
void onTimer() {
  dumpData = true;        
}

void loop()
{
   char received;

   if (rs485.available() > 0) {
      received = rs485.read();     
      RecvBuffer[recvIndex++] = received;
   }

    // first time we get an empty buffer after receiving stuff:
    // this could be the end of the message, (re)start the end-of-message detection timer. 
    if (recvIndex>0) {

      if (!timerStarted){
        MsTimer2::start();
        timerStarted = true;
      }
    } 

   // If the timer expired and positioned this var, we should now dump the received message
   // into a UDP packet to the remote host/logger.
   if (dumpData) {
      receiveTime = micros() - MESSAGE_GAP_TIMEOUT_IN_MS*1000; 
      
      // reinitialize vars for next detection/dump
      dumpData = false;
      MsTimer2::stop();
      timerStarted = false;   

      //msgIndex++ ;
      //if (msgIndex > 999) msgIndex = 0;
     
      // build and send UDP message
      Udp.beginPacket(remote_ip, 8888);
      
      //sprintf(receiveTimeString, "%015lu: ", receiveTime);
      //Udp.write(receiveTimeString, strlen(receiveTimeString));

      //sprintf(msgIndexString, "%04lu: ", msgIndex);
      //Udp.write(msgIndexString, strlen(msgIndexString));
      
      Udp.write(RecvBuffer, recvIndex);
      //Udp.write("\r\n");
    
      Udp.endPacket();

      // reset index for next message
      recvIndex = 0;
   } 
} 