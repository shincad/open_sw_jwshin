/*

  Power Control Board for BT Information Technology
  
  This program is designed to control pc power switch and fan, brightness for LCD monitor.
  This program was built on arduino uno.
  
  circuit designed by shin
  firmware designed and written by shin
  rev 0.1 : 20170713 serial packet frame routine 
  rev 0.2 : 20170716 Motor driver L296 control for PC Fan
  rev 0.3 : 20170718 pc button & debounce implementation
  rev 0.4 : 20170719 pc LED Status check routine implementation
  rev 0.5 : 20170720 Ticker and Timer Interrupt Routine implementation
  rev 0.6 : 20170721 ethenet shield tcp packet test
  rev 0.7 : 20170722 ethernet shield tcp server packet implementation
  rev 0.8 : 20170723 lm35 temperature routine implementation
  rev 0.9 : 20170724 cds brightness routine implementation
  rev 1.2 : 20170802 serial packet string method test
  rev 1.3 : 20170807 redefined the serial transmit packet method
  rev 1.4 : 20170808 pin 4 (SD Card Chip Select) disable for tcp/ip
  rev 2.0 : 20170816 serial packet and ethernet packet redefined
  rev 2.1 : 20170818 packet test ok / decide to packet code
  rev 2.2 : 20170828 packet redefined for app  (for ok01)
  rev 2.3 : 20170907 Beta Version / TCP/IP Client Mode Added
  rev 2.4 : 20170908 Beta Version 2 / packet redefined for app
  rev 2.5 : 20170909 Beta Version 3 / Code optmization and serial command added.
  rev 2.6 : 20170914 TCP/IP Server Code modified / | delimiter Added. (for ok01)
  rev 3.0 : 20171019 add humidity sensor (use DHT11)
  rev 3.1 : 20171020 add StartBootFlag and debounceDelay modified and temp bug fixed.
  rev 3.2 : 20171022 bug fixed.
  rev 3.3 : 20171115 serial packet modified. (for ipset program) / Total Value transmit code added. (for ok01)   
  rev 3.4 : 20171123 separate Mac init command from total init command. (for customer)
 */ 


/* 
  Include header files
*/
#include <MsTimer2.h>   // for Timer
#include <SPI.h>
#include <Ethernet.h>
#include <utility/w5100.h>
#include <avr/wdt.h>
#include <EEPROM.h>

//------------------ Start, End delimiter
//------------------ <로 시작하며, >으로 끝난다.
#define SOP '<'
#define EOP '>'


//------------------- 각 Port의 정의    FAN_STBY와 PC_ON_SW 신호 서로 바꿈 +jwshin 170808
#define FAN_STBY      7
#define TESTLED       3       // SD Card CS가 4번이라서 변경함.
#define PC_ON         8
#define PCLED_DETECT  9
#define PC_ON_SW      2
#define lm35Pin       A5
#define CDS           A4
#define FAN_A         5
#define FAN_B         6
#define FAN_A_IN1     A0
#define FAN_A_IN2     A1
#define FAN_B_IN3     A2
#define FAN_B_IN4     A3
#define dht11_pin     4



// 00:08:dc:15:10:08
//byte macAddr[6] = {};

//---------------------- EEPROM에 저장하기 위한 임시변수 for network
/*
byte ip[4] = {10,10,10,100};
byte mac[6] = {0xde,0xad,0xbe,0xef,0xfe,0xed};
byte myDns[4] = {164,124,101,2};
byte gateway[4] = {255,255,255,0};
byte subnet[4] = {10,10,10,1};
*/

//-------------------- EEPROM에서 IP 및 기타 Setting을 읽어와서 Setting 함..
byte mac[6] = {EEPROM.read(3),EEPROM.read(4),EEPROM.read(5),EEPROM.read(6),EEPROM.read(7),EEPROM.read(8)};
byte ip[4] = {EEPROM.read(9),EEPROM.read(10),EEPROM.read(11),EEPROM.read(12)};
byte myDns[4] = {EEPROM.read(13),EEPROM.read(14),EEPROM.read(15),EEPROM.read(16)};
byte gateway[4] = {EEPROM.read(17),EEPROM.read(18),EEPROM.read(19),EEPROM.read(20)};
byte subnet[4] = {EEPROM.read(21),EEPROM.read(22),EEPROM.read(23),EEPROM.read(24)};



//----------------- for util part
volatile unsigned int DelayTick,Com1Tick,SystemTick,WatchDogTick,GetTempTick,GetBriTick,EtherTick,GetHumiTick;
unsigned int LedTick;
volatile unsigned int Sensor, OldSensor;
volatile unsigned int PCLEDStatus;
u8 bPcControlState;
unsigned char ToggleFlag13;
unsigned char FanManualMode;
unsigned char CdsManualMode;
short Temperature;
short Brightness;
short BriData;
short FanSpeed;
char Force4Flag;
volatile int eepAddr;


//-------------------------- dht11 variable
short DhtTemp;
short DhtHumi;
byte dht11_dat[5];
byte dht11_in;


//----------------------- button Debounce Variable
int buttonState;
int lastButtonState = HIGH;

unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 80;
int ledState = HIGH;
unsigned long CntLongBtnTick;
volatile int StartBootFlag;

//----------------- for Serial Part 
bool started = false;
bool ended = false;

char inData[80];
byte index;

String response="";

//-------------------------- 임시 테스트용으로 설정하였으나, 사용하지 않음.
//u16 TcpPort = 8181;
//IPAddress ip(10,10,10,100);
//IPAddress server(10,10,10,7);
//byte mac[] = {
//  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
//};
char EtherStatus;

// TCP Socket Server Port setting : 8181 
EthernetServer server(8181);


// TCP Client Socket 
EthernetClient clientSub;
String responseClient;

// 통합 관리 서버 IP
//byte cliip[] = { 192,168,25,9};
byte mainsvrip[] = {EEPROM.read(25),EEPROM.read(26),EEPROM.read(27),EEPROM.read(28)};

//----------------------- TCP/IP Socket Client Mode Data
void EtherClientLine(void)
{
  if(clientSub.available())
  {
    responseClient = clientSub.readStringUntil('\r');
    writeString(responseClient);

  }
}

//--------------------- TCP/IP WriteString
void writeString(String stringData)
{
  for(unsigned long i=0; i < stringData.length(); i++)
  {
    Serial.write(stringData[i]);
  }
}

//----------------------- TCP/IP Socket Data Receive
/*
* Socket Data는 @#@으로 시작되며, 중간 code Data, 마지막은 @*@로 끝나며, 길이는 8 Byte 이다..
*/
void EtherGetData2()
{
  EthernetClient client = server.available();
  if(client)
  {
    
    if(client.available() > 0)
    {
      response = client.readStringUntil('\r');
      if(response.startsWith("@#@") && response.endsWith("@*@") && response.length()==8)
      {
        DoParsingTcp(response);
      }
      else
      {
        client.print(F("@#@------@*@|"));   // not defined
      }
    }
  }
}


//-------------------  자리수를 4 digits 로 맞추기 위한 routine
String DigitConv(unsigned int Value)
{
  String Temp1;
  if(Value<10)
  {
    Temp1 = "000"+String(Value,DEC);
  }
  else if(Value<100)
  {
    Temp1 = "00"+String(Value,DEC);
  }
  else if(Value<1000)
  {
    Temp1 = "0"+String(Value,DEC);
  }
  else
  {
    Temp1 = String(Value,DEC);
  }
  return Temp1;
}

//--------------------------- 온도 측정 Routine 
//--------------------------- 0.1 sec 간격으로 측정된다.
//--------------------------- not used.
/*
void getTemp(void)
{
  if(GetTempTick == 0)
  {
    GetTempTick = 10;
    Temperature = analogRead(lm35Pin) / 9.31;
  }
}
*/

//-------------------  dht11 read data routine
byte read_dht11_dat() {
  byte i = 0;
  byte result=0;
  for(i=0; i< 8; i++) {
    while (!digitalRead(dht11_pin));
    delayMicroseconds(30);
    if (digitalRead(dht11_pin) != 0 )
      bitSet(result, 7-i);
    while (digitalRead(dht11_pin));
  }
  return result;
}

//---------------------------- DHT11 Temperature and Humidity Routine
//---------------------------- 1초 간격으로 Scan 
void getTempHumi(void)
{
  if(GetHumiTick == 0)
  {
    GetHumiTick = 100;
    digitalWrite(dht11_pin, LOW);
    delay(18);
    digitalWrite(dht11_pin, HIGH);
    delayMicroseconds(1);
    pinMode(dht11_pin,INPUT);
    delayMicroseconds(40);     
    if (digitalRead(dht11_pin)) {
      //Serial.println("dht11 start condition 1 not met"); // wait for DHT response signal: LOW
      delay(1000);
      return;
    }
    delayMicroseconds(80);
    if (!digitalRead(dht11_pin)) {
      //Serial.println("dht11 start condition 2 not met");  //wair for second response signal:HIGH
      return;
    }
    delayMicroseconds(80);// now ready for data receive
    for (int i=0; i<5; i++)
    { dht11_dat[i] = read_dht11_dat(); }  //recieved 40 bits data. Details are described in datasheet
    pinMode(dht11_pin, OUTPUT);
    digitalWrite(dht11_pin, HIGH);
    byte dht11_check_sum = dht11_dat[0]+dht11_dat[2];// check check_sum
    if(dht11_dat[4]!= dht11_check_sum) {
      //Serial.println("DHT11 checksum error");
    }
    /*
    Serial.print("Current humdity = ");
    Serial.print(dht11_dat[0], DEC);
    Serial.print("%  ");
    Serial.print("temperature = ");
    Serial.print(dht11_dat[2], DEC);
    Serial.println("C  ");  
    */
    DhtHumi = dht11_dat[0];
    DhtTemp = dht11_dat[2];
  }
}

//---------------------------- Analog Reference Voltage 5V 기준의 getTemp2 function 사용 
void getTemp2(void)
{
  if(GetTempTick == 0)
  {
    unsigned long Sum;
    unsigned int Val;
    unsigned int TempVal;
    GetTempTick = 10;
    
    for(int i=0;i<100;i++)
    {
      //Val = analogRead(lm35Pin) / 9.31;
      //-------------- analog reference voltage 를 5V 기준으로 만든 공식...
      Val = (5.0 * analogRead(lm35Pin)*100.0) / 1024;
      Sum = Sum + Val;
    }
    Temperature = Sum / 100;
    
  }
}

//------------------------- 조도측정 Routine
//------------------------- 0.1 sec 간격으로 측정된다.
void getBrightness(void)
{
  if(GetBriTick == 0)
  {
    unsigned long Sum;
    unsigned int Val;
    GetBriTick = 10;
    for(int i=0;i<100;i++)
    {
      Val = analogRead(CDS);
      Sum = Sum + Val;
    }
    Brightness = Sum / 100;
  }
}

//------------------------ 밝기 측정 Routine
void MeasuringBright(void)
{
  getBrightness();
  

  //if(CdsManualMode==1)
  //  return;
  /*  
  if(Brightness > 900)
  {
    BriData = 30;
    //server.print("900 이상");
    //Serial.print("<lcd,30>");
  }
  else if(Brightness > 500 && Brightness <= 900)
  {
    BriData = 50;
    //server.print("500에서 900사이 ");
    //Serial.print("<lcd,50>");
  }
  else if(Brightness > 300 && Brightness <= 500)
  {
    BriData = 70;
    //server.print("300에서 500사이 ");
    //Serial.print("<lcd,70>");
  }
  else if(Brightness <= 300)
  {
    BriData = 100;
    //server.print("300이하 ");
    //Serial.print("<lcd,100>");
  }
  else
  {

  }
  */
  if(Brightness > 900)
  {
    BriData = 10;
  }
  else if(Brightness > 800 && Brightness <= 900)
  {
    BriData = 20;
  }
  else if(Brightness > 700 && Brightness <= 800)
  {
    BriData = 30;
  }
  else if(Brightness > 600 && Brightness <= 700)
  {
    BriData = 40;
  }
  else if(Brightness > 500 && Brightness <= 600)
  {
    BriData = 50;
  }
  else if(Brightness > 400 && Brightness <= 500)
  {
    BriData = 60;
  }
  else if(Brightness > 300 && Brightness <= 400)
  {
    BriData = 70;
  }
  else if(Brightness > 200 && Brightness <= 300)
  {
    BriData = 80;
  }
  else if(Brightness > 100 && Brightness <= 200)
  {
    BriData = 90;
  }
  else if(Brightness <= 100)
  {
    BriData = 100;
  }

}

//---------------------------- FAN 구동 Routine
//---------------------------- L298N을 이용한 PWM 제어를 이용한다.
//---------------------------- tb6612 제어에도 동일하게 사용된다.
void RunningMotor(u16 Speed)
{
  digitalWrite(FAN_STBY, HIGH);     // tb6612용 Stand-by Pin 제어
  analogWrite(FAN_A, Speed);
  analogWrite(FAN_B, Speed);
  digitalWrite(FAN_A_IN1, LOW);
  digitalWrite(FAN_A_IN2,HIGH);
  digitalWrite(FAN_B_IN3, LOW);
  digitalWrite(FAN_B_IN4, HIGH);
}

void StopMotor()
{
  digitalWrite(FAN_STBY, LOW);      // tb6612용 Stand-by Pin 제어
  analogWrite(FAN_A,0);
  analogWrite(FAN_B,0);
  digitalWrite(FAN_A_IN1, LOW);
  digitalWrite(FAN_A_IN2, LOW);
  digitalWrite(FAN_B_IN3, LOW);
  digitalWrite(FAN_B_IN4, LOW);
}


//----------------------- 온도구간별 PWM 속도 제어
void MeasuringTempFan(void)
{
  

  getTemp2();

  /*
  if(PCLEDStatus == 1)
  {
    StopMotor();
    FanSpeed = 0;
    return;
  }
  */

  if(FanManualMode == 1)
  {
    return;
  } 

  if(Temperature < 27)
  {
    StopMotor();
    FanSpeed = 0;
  }
  else if(Temperature >= 28 && Temperature <=33)
  {
    RunningMotor(150);
    FanSpeed = (150 * 100) / 255;     // 58%
  }
  else if(Temperature >= 34 && Temperature < 40)
  {
    RunningMotor(200);
    FanSpeed = (200 * 100) / 255;     // 78%
  }
  else if(Temperature >= 40)
  {
    RunningMotor(255);
    FanSpeed = (255 * 100) * 255;     // 100%
  }
  else
  {
    //StopMotor();
  }
  
}


//-------------------------   모니터링 App으로 부터 받은 Packet을 분석하고, 응답하는 Routine
void DoParsingTcp(String Data)
{
  String TempStr;
  String TempValStr;
  TempStr = Data.substring(3,5);
  //-------------------------------- Push Power Button
  if(TempStr == "00")
  {
    SetPowerOn();
    //server.print("@#@PUSH@*@");
    server.print("@#@"+TempStr+"PUSH@*@|");
  }
  //-------------------------------- 강제 Power Button (4sec)
  else if(TempStr == "01")
  {
    //server.write("@#@4SEC@*@");
    server.print("@#@"+TempStr+"4SEC@*@|");
    SetPowerOffForce();
  }
  //-------------------------------- 온도값 요청
  else if(TempStr == "02")
  {
    TempValStr = DigitConv(Temperature);
    //server.print("@#@"+TempValStr+"@*@");
    server.print("@#@"+TempStr+TempValStr+"@*@|"); 
  }
  //-------------------------------- Fan 속도 요청
  else if(TempStr == "03")
  {
    TempValStr = DigitConv(FanSpeed);
    //server.print("@#@"+TempValStr+"@*@");
    server.print("@#@"+TempStr+TempValStr+"@*@|");
  }
  //-------------------------------- PC 전원상태 요청
  else if(TempStr == "04")
  {
    TempValStr = DigitConv(PCLEDStatus);
    //server.print("@#@"+TempValStr+"@*@");
    server.print("@#@"+TempStr+TempValStr+"@*@|");
  }
  //-------------------------------- 외부 조도 요청 
  else if(TempStr == "05")
  {
    TempValStr = DigitConv(Brightness);
    //server.print("@#@"+TempValStr+"@*@");
    server.print("@#@"+TempStr+TempValStr+"@*@|");
  }
  //-------------------------------- Fan 수동모드 속도 최대
  else if(TempStr == "06")
  {
    FanManualMode = 1;
    RunningMotor(255);
    FanSpeed = 100;
    //server.print("@#@FMAX@*@");
    server.print("@#@"+TempStr+"FMAX@*@|");
  }
  //-------------------------------- Fan 수동모드 속도 0
  else if(TempStr == "07")
  {
    FanManualMode = 1;
    StopMotor();
    FanSpeed = 0;
    server.print("@#@"+TempStr+"FMIN@*@|");
  }
  //-------------------------------- Fan Auto mode
  else if(TempStr == "08")
  {
    FanManualMode = 0;
    server.print("@#@"+TempStr+"AUTO@*@|");
  }
  else if(TempStr == "09")
  {
    TempValStr = DigitConv(DhtHumi);
    server.print("@#@"+TempStr+TempValStr+"@*@|");    
  }
  else if(TempStr == "10")
  {
    TempValStr = DigitConv(DhtTemp);
    server.print("@#@"+TempStr+TempValStr+"@*@|");
  }
  //-------------------------------- 정의되지 않음..
  else
  {
    server.print("@#@------@*@|");         // not defined
  }
}

/*
 * TogglePower
 * Port 8 : PC_ON TurnON Signal
 * Arg : u8 pin
 * Return : void
 */
void TogglePower(u8 pin)
{
  if(pin==1) digitalWrite(PC_ON,HIGH);
  else digitalWrite(PC_ON,LOW);
}

//------------------------ 4초 이상 버튼이 눌리는 지 Check
//------------------------ PC가 꺼져있으면 routine이 동작되지 않고, 그냥 빠짐. 
void GetSensor2(void)
{
  if(PCLEDStatus == 1)
    return;
  Sensor = digitalRead(PC_ON_SW);
  if(Sensor == 0)
  {
    CntLongBtnTick++;
  }
}

/*
 * SetPowerOn
 * Power On Routinre
 */
//-------------- on/off 시 이 routine 만 사용한다.
void SetPowerOn(void)
{
  TogglePower(1);
  UsrDelay(10);
  TogglePower(0);
  UsrDelay(10);
}

/*
 * SetPowerOff
 * Power Off Routine
 */
//---------------- not used.
void SetPowerOff(void)
{
  TogglePower(0);
  UsrDelay(100);
  TogglePower(1);
}

/*
 * SetPowerOff2
 * Power Off 2 Routine
 */
//----------------- not used.
void SetPowerOff2(void)
{
  TogglePower(0);
  UsrDelay(150);
  TogglePower(1);
  UsrDelay(600);
  TogglePower(0);
}

//----------------- 강제로 OFF 할 경우 이 Routine을 사용한다.
void SetPowerOffForce(void)
{
  while(PCLEDStatus == 0)         // pc LED가 꺼질때 까지 계속 POWER Pin Signal LOW로 유지...
  {
    TogglePower(1);
  }
  TogglePower(0);
}

/*
 *  PC Power Switch Detection 2 Routine
 */
//------------------------- debounce를 위해, millis() 함수를 사용한다.
void CheckPowerSwitch2(void)
{
  int reading = digitalRead(PC_ON_SW);
  if(reading != lastButtonState)
  {
    lastDebounceTime = millis();
  }
  if((unsigned long)(millis() - lastDebounceTime) > debounceDelay&&CntLongBtnTick<400)
  {
    if(reading != buttonState)
    {
      buttonState = reading;
      if(buttonState == HIGH)
      {
        if(Force4Flag == 0)
        { 
          if(StartBootFlag==1)  //-------------- CPU가 처음 Reset 되었을 경우, Power On 버튼 Routine에 진입하는 것을 방지하기 위해, StartBootFlag를 사용
          {
            StartBootFlag = 0;
            return;
          }
          CntLongBtnTick = 0;
          server.write("@#@00PUSH@*@|xx");
          SetPowerOn();
        }
        else
        {
          Force4Flag = 0;
          CntLongBtnTick = 0;
        }
      }
    }
    
  }
  else if(CntLongBtnTick > 400)
  {
    Force4Flag = 1;
    CntLongBtnTick = 0;
    server.write("@#@014SEC@*@|xx");
    SetPowerOffForce();
  }
 
  lastButtonState = reading;
  
}

//--------------------- 현재 PC의 전원 상태를 파악하여 Display
void DisplayLed(void)
{
  if(PCLEDStatus == 0)
  {
    digitalWrite(TESTLED, HIGH);
  }
  else
  {
    digitalWrite(TESTLED, LOW);
  }
}

//------------------------ Led Flickering for Test
//------------------------ EEPROM에 아무런 Data가 없을 경우, 계속적으로 Flickering
void Flicker_L13(void)
{
  if(LedTick==0) 
  {
    digitalWrite(TESTLED,ToggleFlag13);
    ToggleFlag13 ^= 0xff;
    LedTick = 5; // 0.1 sec flickering     
  }
}

//------------------------ Normal 상태의 LED 
void Flicker_normal(void)
{
  if(LedTick==0)
  {
    digitalWrite(TESTLED, ToggleFlag13);
    ToggleFlag13 ^= 0xff;
    LedTick = 50; // 1 sec flickering
  }
}


//----------------------- Serial Initialization

void SerialInit(void)
{
  Serial.begin(115200);
  Serial.flush();  
}

//----------------------- port init and variable init.
void UtilInit(void)
{
  DelayTick = 0;
  SystemTick = 0;
  GetTempTick = 10;
  GetBriTick = 10;
  GetHumiTick = 100;
  CntLongBtnTick = 0;
  Force4Flag = 0;
  EtherStatus = 0;
  //----------- Port 초기화
  pinMode(TESTLED,OUTPUT);
  pinMode(PC_ON,OUTPUT);
  pinMode(PCLED_DETECT,INPUT);
  pinMode(PC_ON_SW,INPUT);
  pinMode(FAN_STBY, OUTPUT);
  pinMode(A0,OUTPUT);
  pinMode(A1,OUTPUT);
  pinMode(A2,OUTPUT);
  pinMode(A3,OUTPUT);
  Sensor = digitalRead(PC_ON_SW);
  OldSensor = digitalRead(PC_ON_SW);
  LedTick = 10;     // 0.1 sec
  ToggleFlag13 = 0;
  FanManualMode = 0;
  CdsManualMode = 0;
  pinMode(dht11_pin, OUTPUT);
  digitalWrite(dht11_pin, HIGH);
  StartBootFlag = 1;
}


//----------------------- Ethernet init.
void EtherInit(void)
{
  Ethernet.begin(mac,ip, myDns, gateway, subnet);
  //  Ethernet.begin(macAddr,ipAddr,DnsAddr,GatewayAddr,SubnetAddr);
  //------------------ 3 sec socket timeout
  W5100.setRetransmissionTime(0x07D0);
  W5100.setRetransmissionCount(3);
  server.begin();
}


//------------------------ user delay function 
void UsrDelay(int time)
{
  DelayTick = time;
  while(DelayTick != 0);
}

//------------------------ Timer Interrupt Routine
void TickIsr(void)
{
  if(DelayTick!=0) DelayTick--;
  if(GetTempTick!=0) GetTempTick--;
  if(GetBriTick!=0) GetBriTick--;
  if(GetHumiTick!=0) GetHumiTick--;

  GetSensor2();        // Sensor Value Read
  PCLEDStatus = digitalRead(PCLED_DETECT);

  if(LedTick!=0) LedTick--;
  
}

/*
void EtherLine(void)
{
  String EthData;
  if(client.available())
  {
    EthData = client.readStringUntil('\r');
    writeString(EthData);
  }
}

void writeString(String stringData)
{
  for(unsigned long i=0; i<stringData.length(); i++)
  {
    Serial.write(stringData[i]);
  }
}
*/

//-------------------- Serial RX Interrupt Routine
void serialEvent(void)
{
  while(Serial.available()>0)
  {
    char inChar = Serial.read();

    if(inChar == SOP)
    {
      index = 0;
      inData[index] = '\0';
      started = true;
      ended = false;
    }
    else if(inChar == EOP)
    {
      ended = true;
      break;
    }
    else 
    {
      if(index < 79)
      {
        inData[index] = inChar;
        index++;
        inData[index] = '\0';
      }
    }
  }
  
}
//-------------------------- decimal to Hex Routine
String decToHex(byte decValue, byte desiredStringLength) {
  
  String hexString = String(decValue, HEX);
  while (hexString.length() < desiredStringLength) hexString = "0" + hexString;
  
  return hexString;
}

//-------------------------- Hex string to int decimal conversion
unsigned int hexToDec(String hexString) {
  
  unsigned int decValue = 0;
  int nextInt;
  
  for (int i = 0; i < hexString.length(); i++) {
    
    nextInt = int(hexString.charAt(i));
    if (nextInt >= 48 && nextInt <= 57) nextInt = map(nextInt, 48, 57, 0, 9);
    if (nextInt >= 65 && nextInt <= 70) nextInt = map(nextInt, 65, 70, 10, 15);
    if (nextInt >= 97 && nextInt <= 102) nextInt = map(nextInt, 97, 102, 10, 15);
    nextInt = constrain(nextInt, 0, 15);
    
    decValue = (decValue * 16) + nextInt;
  }
  
  return decValue;
}


//----------------------- ip 값 token function
// <ip,10.10.10.100>
void ipSendVal(char *value)
{
  char *ptr = strtok(value, ".");  
  while(ptr!=NULL)
  {
    Serial.println(ptr);
    ptr = strtok(NULL,".");
  }
}

//--------------------- mac address value token function
// <macaddr,ae:d2:80:27:66:a1>
void macSendVal(char *value)
{
  char *ptr = strtok(value,":");
  String inString = "";
  int val;
  int i=3;
  while(ptr!=NULL)
  {
    // inString = ptr;
    // EEPROM.write(i++,inString.toInt());
    val = hexToDec(ptr);  
    EEPROM.write(i++,val);
    ptr = strtok(NULL,":");
    
  }
  Serial.print(F("WriteOK"));
  /*
  Serial.print("<macaddr,");
  Serial.print(EEPROM.read(3),HEX);
  Serial.print(EEPROM.read(4),HEX);
  Serial.print(EEPROM.read(5),HEX);
  Serial.print(EEPROM.read(6),HEX);
  Serial.print(EEPROM.read(7),HEX);
  Serial.print(EEPROM.read(8),HEX);
  Serial.println(">");
  */
}

//------------------------- Serial Rx로 부터 들어온 코드를 분석
void sendCommand(char *command, char *value)
{
  //char s1[30] = "10.10.10.101";
  String inString ="";
  int val;
  if(strcmp(command,"dnp") == 0)
  {
    EEPROM.write(0,0x06);
    EEPROM.write(1,0x01);
    EEPROM.write(2,0x06);
    Serial.print(F("WriteOK"));
    //Serial.println("<dnp,060106>");    
  }
  else if(strcmp(command,"ip") == 0)
  {
    val = 9;      // ip address EEPROM Start Address
    char *ptr = strtok(value, ".");  
    while(ptr!=NULL)
    {
      inString = ptr;
      EEPROM.write(val++,inString.toInt());
      ptr = strtok(NULL,".");
    }
    Serial.print(F("WriteOK"));
    /*
    Serial.print("<ip,");
    Serial.print(EEPROM.read(9));
    Serial.print(EEPROM.read(10));
    Serial.print(EEPROM.read(11));
    Serial.print(EEPROM.read(12));
    Serial.println(">");
    */
  }
  else if(strcmp(command,"dns") == 0)
  {
    val = 13;      // dns EEPROM Start Address
    char *ptr = strtok(value, ".");  
    while(ptr!=NULL)
    {
      inString = ptr;
      EEPROM.write(val++,inString.toInt());
      ptr = strtok(NULL,".");
    }
    Serial.print(F("WriteOK"));
    /*
    Serial.print("<dns,");
    Serial.print(EEPROM.read(13));
    Serial.print(EEPROM.read(14));
    Serial.print(EEPROM.read(15));
    Serial.print(EEPROM.read(16));
    Serial.println(">");
    */
  }
  else if(strcmp(command,"gateway") == 0)
  {
    val = 17;      // gateway EEPROM Start Address
    char *ptr = strtok(value, ".");  
    while(ptr!=NULL)
    {
      inString = ptr;
      EEPROM.write(val++,inString.toInt());
      ptr = strtok(NULL,".");
    }
    Serial.print(F("WriteOK"));
    /*
    Serial.print("<gateway,");
    Serial.print(EEPROM.read(17));
    Serial.print(EEPROM.read(18));
    Serial.print(EEPROM.read(19));
    Serial.print(EEPROM.read(20));
    Serial.println(">");
    */
  }
  else if(strcmp(command,"subnet") == 0)
  {
    val = 21;      // subnet EEPROM Start Address
    char *ptr = strtok(value, ".");  
    while(ptr!=NULL)
    {
      inString = ptr;
      EEPROM.write(val++,inString.toInt());
      ptr = strtok(NULL,".");
    }
    Serial.print(F("WriteOK"));
    /*
    Serial.print("<subnet,");
    Serial.print(EEPROM.read(21));
    Serial.print(EEPROM.read(22));
    Serial.print(EEPROM.read(23));
    Serial.print(EEPROM.read(24));
    Serial.print(">");
    */
  }
  else if(strcmp(command,"mainsvrip") == 0)
  {
    val = 25;
    char *ptr = strtok(value,".");
    while(ptr!=NULL)
    {
      inString = ptr;
      EEPROM.write(val++,inString.toInt());
      ptr = strtok(NULL,".");
    }
    Serial.print(F("WriteOK"));
    /*
    Serial.print("<mainsvrip,");
    Serial.print(EEPROM.read(25));
    Serial.print(".");
    Serial.print(EEPROM.read(26));
    Serial.print(".");
    Serial.print(EEPROM.read(27));
    Serial.print(".");
    Serial.print(EEPROM.read(28));
    Serial.print(">");
    */
  }
  else if(strcmp(command,"macaddr") == 0)
  {
    macSendVal(value);
  }
  else if(strcmp(command,"ipcheck") == 0)
  {
    Serial.print("<ipcheck,");
    Serial.print(Ethernet.localIP());
    Serial.println(">");
  }
  else if(strcmp(command,"networkdisplay") == 0)
  {
    Serial.print(F("Mac : "));
    for(int Cnt=3;Cnt<9;Cnt++)
    { 
      Serial.print(EEPROM.read(Cnt),HEX);
      if(Cnt==8) continue; 
      Serial.print(":");
    }
    Serial.println();
    Serial.print(F("IP : "));
    for(int Cnt=9;Cnt<13;Cnt++)
    {
      Serial.print(EEPROM.read(Cnt));
      if(Cnt==12) continue;
      Serial.print(".");
    }
    Serial.println();
    Serial.print(F("DNS : "));
    for(int Cnt=13;Cnt<17;Cnt++)
    {
      Serial.print(EEPROM.read(Cnt));
      if(Cnt==16) continue;
      Serial.print(".");
    }
    Serial.println();
    Serial.print(F("GW : "));
    for(int Cnt=17;Cnt<21;Cnt++)
    {
      Serial.print(EEPROM.read(Cnt));
      if(Cnt==20) continue;
      Serial.print(".");
    }
    Serial.println();
    Serial.print(F("SM : "));
    for(int Cnt=21;Cnt<25;Cnt++)
    {
      Serial.print(EEPROM.read(Cnt));
      if(Cnt==24) continue;
      Serial.print(".");
    }
    Serial.println();
    Serial.print(F("SVRIP : "));
    for(int Cnt=25;Cnt<29;Cnt++)
    {
      Serial.print(EEPROM.read(Cnt));
      if(Cnt==28) continue;
      Serial.print(".");
    }
    Serial.println();
  }
  else if(strcmp(command,"pushbutton") == 0)
  {
    SetPowerOn();
    Serial.println("<pushbutton,1>");
  }
  else if(strcmp(command,"pushbutton4sec") == 0)
  {
    SetPowerOffForce();
    Serial.println("<pushbutton4sec,1>");
  }
  else if(strcmp(command,"eeprominit") == 0)
  {
    for(int i=0;i<3;i++)
    {
      EEPROM.write(i,0x00);
    }
    for(int i=9;i<50;i++)
    {
      EEPROM.write(i,0x00);
    }
    Serial.println(F("<eeprominit,1>"));
  }
  else if(strcmp(command,"macinit") == 0)
  {
    for(int i=3;i<9;i++)
    {
      EEPROM.write(i,0x00);
    }
    Serial.println(F("<macinit,1>")); 
  }
  else if(strcmp(command,"ethernetinit") == 0)
  {
    Ethernet.begin(mac,ip, myDns, gateway, subnet);
    W5100.setRetransmissionTime(0x07D0);
    W5100.setRetransmissionCount(3);
    server.begin();
    delay(1000);
    EthernetClient client = server.available();
    Serial.println(F("<ethernetinit,1>"));  
    client.stop();
  }
  else if(strcmp(command,"tcptransmit") == 0)
  {
    server.print(value);
  }
  else if(strcmp(command,"serialtransmit") == 0)
  {
    Serial.print(value);
  }
  else if(strcmp(command,"cpureset") == 0)
  {
    Serial.println("<cpureset,1>");
    while(1);  // Watchdog Timer가 8 sec 이므로 , 8 sec 이상 머물러 있으면 자동적으로 Reset...
  }
  else if(strcmp(command,"brightnessreq") == 0)
  {
    String CdsVal = String(BriData,DEC);
    Serial.println("<brightnessreq,"+CdsVal+">");
  }
  else if(strcmp(command,"temperaturereq") == 0)
  {
    String TempVal = String(Temperature,DEC);
    Serial.println("<temperaturereq,"+TempVal+">");
  }
  else if(strcmp(command,"fanspeedreq") == 0)
  {
    String FSpeedVal = String(FanSpeed,DEC);
    Serial.println("<fanspeedreq,"+FSpeedVal+">");
  }
  else if(strcmp(command,"humidityreq") == 0)
  {
    String TempVal = String(DhtHumi,DEC);
    Serial.println("<humidityreq,"+TempVal+">");  
  }
  else if(strcmp(command,"dhttempreq") == 0)
  {
    String TempVal = String(DhtTemp,DEC);
    Serial.println("<dhttempreq,"+TempVal+">"); 
  }
  else if(strcmp(command,"cdsauto") == 0)
  {
    if(strcmp(value,"1") == 0)
    {
      CdsManualMode = 0;
      Serial.print(F("<cdsauto,1>"));
    }
    else if(strcmp(value,"0") == 0)
    {
      CdsManualMode = 1;
      Serial.print(F("<cdsauto,0>"));
    }  
  }
  else if(strcmp(command,"lcdbrival") == 0)
  {
    inString = value;
    BriData = inString.toInt();
    CdsManualMode = 1;
    Serial.print(F("<lcdbrival,"));
    Serial.print(BriData);
    Serial.print(F(">"));
  }
  else if(strcmp(command,"fanauto") == 0)
  {
    if(strcmp(value,"1") == 0)
    {
      FanManualMode = 0;
      Serial.print(F("<fanauto,1>"));
    }
    else if(strcmp(value,"0") == 0)
    {
      FanManualMode = 1;      // Fan Manual Mode
      Serial.print(F("<fanauto,0>"));
    }
  }
  else if(strcmp(command,"fanmax") == 0)
  {
    if(strcmp(value,"1") == 0)
    {
      FanManualMode = 1;
      RunningMotor(255);
      FanSpeed = 100;
      Serial.print(F("<fanmax,1>"));
    }
    else if(strcmp(value,"0") == 0)
    {
      FanManualMode = 1;
      StopMotor();
      FanSpeed = 0;
      Serial.print(F("<fanmax,0>"));
    }
  }
  else if(strcmp(command,"tcpclient") == 0)
  {
    if(strcmp(value,"1") == 0)
    {
      if(!clientSub.connected())
      {
        clientSub.connect(mainsvrip,8282);
        Serial.println("<tcpclient,1>");
      }
    }
    else if(strcmp(value,"0") == 0)
    {
      clientSub.stop();
      Serial.println("<tcpclient,0>");
    }
  }
  else if(strcmp(command,"tcpclitransmit") == 0)
  {
    clientSub.print(value);
  }
  else if(strcmp(command,"totalreq") == 0)
  {
    String CdsVal = String(BriData,DEC);
    String TempVal = String(Temperature,DEC);
    String FSpeedVal = String(FanSpeed,DEC);
    String HumiVal = String(DhtHumi,DEC);
    String FanMode = String(FanManualMode,DEC);   
    if(strcmp(value,"1") == 0)
    {
      Serial.println("<totalreq,"+CdsVal+","+TempVal+","+FSpeedVal+","+HumiVal+","+FanMode+">|");    
    }
  }
  else
  {
  }
}

//------------------- Serial Rx Code 가 올바른 코드인 경우, sendCommand에 인수 전달
void HostLine(void)
{
  if(started && ended)
  {
    char *cmd = strtok(inData,",");
    if(cmd)
    {
      char *val = strtok(NULL,",");
      if(val)
      {
        sendCommand(cmd,val);
       // Serial.println(cmd);
       // Serial.println(val);
      }
    }

    started = false;
    ended = false;
    index = 0;
    inData[index] = '\0';
  }
}

//-------------------------- 초기화 Routine
void setup() 
{
  if((EEPROM.read(0)==06)&&(EEPROM.read(1)==01)&&(EEPROM.read(2)==06))
  {  
    wdt_disable();
    SerialInit();
    EtherInit();
    UtilInit();
    MsTimer2::set(10,TickIsr);
    MsTimer2::start();
    analogReference(DEFAULT);
    wdt_enable(WDTO_8S);
    delay(1000);
  }
  else
  {
    wdt_disable();
    SerialInit();
    UtilInit();
    MsTimer2::set(10,TickIsr);
    MsTimer2::start();
    analogReference(DEFAULT);
    wdt_enable(WDTO_8S);
    delay(1000);
  }
}

//--------------------------- main Routine
void loop() 
{
  if((EEPROM.read(0)==06)&&(EEPROM.read(1)==01)&&(EEPROM.read(2)==06))
  { 
    HostLine();
    CheckPowerSwitch2();
    EtherGetData2();        
    MeasuringTempFan();
    Flicker_normal();  
    MeasuringBright();
    //getTempHumi();  // -jwshin humidity sensor가 없는 경우..
    EtherClientLine();
    wdt_reset();
  }
  else
  {
    
    HostLine();
    Flicker_L13();
    wdt_reset();
    
  }
}