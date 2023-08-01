// Connect (+) of IR LED to 5Vcc
// connect (-) to pin 4 with a 100 Ohm resistor in line.  For best results make a transistor circuit with external power source

#define RED 3	// the output pin of the IR LED

void setup() {
	pinMode(RED, OUTPUT);	// set IR LED (Pin 4) to Output
} 

void loop() {
//Do you magic here.  The code directly below just throttles up to 60 and back down to 0.  
//You can get data from the serial port, a joystick, or whatever.  You just need to translate your input into values between 0 and 127.
//Pass those values to Transmit( ) as an integer between 0 and 127 and that's it!

	int t;
	for (t = 0; t < 40; t++) {
		Transmit(63, 63, t, 63);  //Rudder = 63, elevator = 63, throttle = t, trim = 63
             // Transmit(63, 63, ((40 - t) + 128), 63); //This would cause Channel "B" to throttle down

	}

	for (t = 40; t > 0; t--) {
		Transmit(63, 63, t, 63);
             // Transmit(63, 63, ((40 - t) + 128), 63); //This would cause Channel "B" to throttle up 
	}
} //End loop()

void Transmit(byte rudder, byte elevator, byte throttle, byte trim) {
	static byte Code[4];
	byte mask = 128; 	//bitmask
	int i;

	Code[0] = rudder; // 0 -> 127; 63 is the midpoint.
	Code[1] = elevator; // 0 -> 127; 63 is the midpoint.
	Code[2] = throttle; // 0 -> 127; 0 is throttle off
	Code[3] = trim;	// Haven't messed with this
    
	OutPulse(2002);  // Start 38Khz pulse for 2000us (2002us is evenly divided by 26)
	delayMicroseconds(2000);  // 2000us off.

	for (i = 0; i<4; i++) {		// Loops through the Code[]
		for (mask = 128; mask > 0; mask >>=1) {	// See Arduino reference for bit masking (really cool stuff!)
		OutPulse(312); 		// Sends 312 pulse each loop

			if(Code[i] & mask) {          //If both bit positions are 1 you get 1              
				delayMicroseconds(688);     // send 1 (700 off)
			} 
			else {
				delayMicroseconds(288);     // send 0 (300 off)
			}
		} //End mask loop
	}  //End i loop

	OutPulse(312);  //Send 300 microsecond Closing Pulse
	delay(60);        

} // End Transmit
 

void OutPulse(int Pulse) {  //sends 38Khz pulses over the Pulse Length
	int p;

	for(p = 0; p < (Pulse / 26) - 1; p++) {  //Takes about 26 microseconds per loop
		digitalWrite(RED, HIGH);
		  delayMicroseconds(10);
		digitalWrite(RED, LOW);
		  delayMicroseconds(10);
	}
}  //End OutPulse
