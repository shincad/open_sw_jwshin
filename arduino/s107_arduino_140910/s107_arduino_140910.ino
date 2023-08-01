//Arduino code to control a helicotper.
int IRledPin =  3;    
int incomingByte = 0;
String incomingString;
int pulseValues[33];
int pulseLength = 0;

void setup()   {                
  // initialize the IR digital pin as an output:
  pinMode(IRledPin, OUTPUT);      
  pinMode(13, OUTPUT);   
  Serial.begin(9600);

  for (int i=0; i < 13; i++) 
    pulseValues[i] = 0;


}

void loop()                     
{
  SendCode();
}


void pulseIR(long microsecs) {
  cli();  // this turns off any background interrupts

  while (microsecs > 0) {
    // 38 kHz is about 13 microseconds high and 13 microseconds low
    digitalWrite(IRledPin, HIGH);  // this takes about 3 microseconds to happen
    delayMicroseconds(10);         // hang out for 10 microseconds
    digitalWrite(IRledPin, LOW);   // this also takes about 3 microseconds
    delayMicroseconds(10);         // hang out for 10 microseconds

    // so 26 microseconds altogether
    microsecs -= 26;

  }

  sei();  // this turns them back on
}

void Zero()
{  
  pulseIR(300);
  delayMicroseconds(300);
  pulseLength += 600;
}

void One()
{
  pulseIR(300);
  delayMicroseconds(600); 
  pulseLength += 900;
}

void sendPulseValue(int pulseValue)
{
  if (pulseValue == 1)
    One();
  else
    Zero(); 
}

void checkPulseChanges()
{
  if (Serial.available() > 0)
  {
    incomingByte = Serial.read();

    //Pulse 1
    if (incomingByte == 'a')
      pulseValues[0] = 0;
    if (incomingByte == 'A')
      pulseValues[0] = 1;

    //Pulse 2
    if (incomingByte == 'b')
      pulseValues[1] = 0;
    if (incomingByte =='B')
      pulseValues[1] = 1;

    //Pulse 3
    if (incomingByte == 'c')
      pulseValues[2] = 0;
    if (incomingByte == 'C')
      pulseValues[2] = 1;

    //Pulse 4
    if (incomingByte == 'd')
      pulseValues[3] = 0;
    if (incomingByte == 'D')
      pulseValues[3] = 1;

    //Pulse 5
    if (incomingByte == 'e')
      pulseValues[4] = 0;
    if (incomingByte == 'E')
      pulseValues[4] = 1;

    //Pulse 6
    if (incomingByte == 'f')
      pulseValues[5] = 0;
    if (incomingByte == 'F')
      pulseValues[5] = 1;

    //Pulse 7
    if (incomingByte == 'g')
      pulseValues[6] = 0;
    if (incomingByte == 'G')
      pulseValues[6] = 1;    

    //Pulse 8
    if (incomingByte == 'h')
      pulseValues[7] = 0;
    if (incomingByte == 'H')
      pulseValues[7] = 1;

    //Pulse 9
    if (incomingByte == 'i')
      pulseValues[8] = 0;
    if (incomingByte == 'I')
      pulseValues[8] = 1;

    //Pulse 10
    if (incomingByte == 'j')
      pulseValues[9] = 0;
    if (incomingByte == 'J')
      pulseValues[9] = 1;

    //Pulse 11
    if (incomingByte == 'k')
      pulseValues[10] = 0;
    if (incomingByte == 'K')
      pulseValues[10] = 1;

    //Pulse 12
    if (incomingByte == 'l')
      pulseValues[11] = 0;
    if (incomingByte == 'L')
      pulseValues[11] = 1;

    //Pulse 13
    if (incomingByte == 'm')
      pulseValues[12] = 0;
    if (incomingByte == 'M')
      pulseValues[12] = 1;

    //Pulse 14
    if (incomingByte == 'o')
      pulseValues[13] = 0;
    if (incomingByte == 'O')
      pulseValues[13] = 1;

    //Pulse 15
    if (incomingByte == 'p')
      pulseValues[14] = 0;
    if (incomingByte == 'P')
      pulseValues[14] = 1;

    //Pulse 16
    if (incomingByte == 'q')
      pulseValues[15] = 0;
    if (incomingByte == 'Q')
      pulseValues[15] = 1;

    //Pulse 17
    if (incomingByte == 'r')
      pulseValues[16] = 0;
    if (incomingByte == 'R')
      pulseValues[16] = 1;

    //Pulse 18
    if (incomingByte == 's')
      pulseValues[17] = 0;
    if (incomingByte == 'S')
      pulseValues[17] = 1;

    //Pulse 19
    if (incomingByte == 't')
      pulseValues[18] = 0;
    if (incomingByte == 'T')
      pulseValues[18] = 1;

    //Pulse 20
    if (incomingByte == 'u')
      pulseValues[19] = 0;
    if (incomingByte == 'U')
      pulseValues[19] = 1;

    //Pulse 21
    if (incomingByte == 'v')
      pulseValues[20] = 0;
    if (incomingByte == 'V')
      pulseValues[20] = 1;

    //Pulse 22
    if (incomingByte == 'w')
      pulseValues[21] = 0;
    if (incomingByte == 'W')
      pulseValues[21] = 1;

    //Pulse 23
    if (incomingByte == 'x')
      pulseValues[22] = 0;
    if (incomingByte == 'X')
      pulseValues[22] = 1;

    //Pulse 24
    if (incomingByte == 'y')
      pulseValues[23] = 0;
    if (incomingByte == 'Y')
      pulseValues[23] = 1;

    //Pulse 25
    if (incomingByte == 'z')
      pulseValues[24] = 0;
    if (incomingByte == 'Z')
      pulseValues[24] = 1;

    //Pulse 26
    if (incomingByte == '1')
      pulseValues[25] = 0;
    if (incomingByte == '2')
      pulseValues[25] = 1;

    //Pulse 27
    if (incomingByte == '3')
      pulseValues[26] = 0;
    if (incomingByte == '4')
      pulseValues[26] = 1;

    //Pulse 28
    if (incomingByte == '5')
      pulseValues[27] = 0;
    if (incomingByte == '6')
      pulseValues[27] = 1;

    //Pulse 29
    if (incomingByte == '7')
      pulseValues[28] = 0;
    if (incomingByte == '8')
      pulseValues[28] = 1;

    //Pulse 30
    if (incomingByte == '9')
      pulseValues[29] = 0;
    if (incomingByte == '!')
      pulseValues[29] = 1;

    //Pulse 31
    if (incomingByte == '@')
      pulseValues[30] = 0;
    if (incomingByte == '#')
      pulseValues[30] = 1;

    //Pulse 32
    if (incomingByte == '$')
      pulseValues[31] = 0;
    if (incomingByte == '%')
      pulseValues[31] = 1;

    //Pulse 33
    if (incomingByte == '^')
      pulseValues[32] = 0;
    if (incomingByte == '&')
      pulseValues[32] = 1;      
  }

}

void SendCode() {

  while (true)
  {
    checkPulseChanges();

    pulseIR(4000);
    delayMicroseconds(2000);
    pulseLength=6000;

    sendPulseValue(pulseValues[0]);
    sendPulseValue(pulseValues[1]);
    sendPulseValue(pulseValues[2]);
    sendPulseValue(pulseValues[3]);
    sendPulseValue(pulseValues[4]);
    sendPulseValue(pulseValues[5]);
    sendPulseValue(pulseValues[6]);
    sendPulseValue(pulseValues[7]);
    sendPulseValue(pulseValues[8]);
    sendPulseValue(pulseValues[9]);
    sendPulseValue(pulseValues[10]);
    sendPulseValue(pulseValues[11]);
    sendPulseValue(pulseValues[12]);
    sendPulseValue(pulseValues[13]);
    sendPulseValue(pulseValues[14]);
    sendPulseValue(pulseValues[15]);
    sendPulseValue(pulseValues[16]);
    sendPulseValue(pulseValues[17]);
    sendPulseValue(pulseValues[18]);
    sendPulseValue(pulseValues[19]);
    sendPulseValue(pulseValues[20]);
    sendPulseValue(pulseValues[21]);
    sendPulseValue(pulseValues[22]);
    sendPulseValue(pulseValues[23]);
    sendPulseValue(pulseValues[24]);
    sendPulseValue(pulseValues[25]);
    sendPulseValue(pulseValues[26]);
    sendPulseValue(pulseValues[27]);
    sendPulseValue(pulseValues[28]);
    sendPulseValue(pulseValues[29]);
    sendPulseValue(pulseValues[30]);
    sendPulseValue(pulseValues[31]);

    //Footer
    pulseIR(360); 
    delayMicroseconds( (28600 - pulseLength) ); 
   } 
}

