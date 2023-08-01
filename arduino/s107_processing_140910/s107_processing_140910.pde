import processing.serial.*; 
import controlP5.*;
import JMyron.*;

JMyron m;

ControlP5 controlP5;
CheckBox checkbox;
Button b;

float boxX;
float boxY;
int boxSize = 20;
boolean mouseOverBox = false;
byte[] previousFlags = new byte[32];
byte[] flagsToSend = new byte[32];
Serial port; 
String outString;

int helicopterUpSpeed = 0;
int helicopterPitch = 63;
int helicopterYaw = 68;

void setup() {
  m = new JMyron();
  m.start(640,480);
  size(640, 480);

  controlP5 = new ControlP5(this);
  checkbox = controlP5.addCheckBox("checkBox", 20, 20);  
  // make adjustments to the layout of a checkbox.
  checkbox.setColorForeground(color(120));
  checkbox.setColorActive(color(255));
  checkbox.setColorLabel(color(128));
  checkbox.setItemsPerRow(8);
  checkbox.setSpacingColumn(30);
  checkbox.setSpacingRow(10);
  // add items to a checkbox.
  checkbox.addItem("1", 0);
  checkbox.addItem("2", 0);
  checkbox.addItem("3", 0);
  checkbox.addItem("4", 0);
  checkbox.addItem("5", 0);
  checkbox.addItem("6", 0);
  checkbox.addItem("7", 0);
  checkbox.addItem("8", 0);
  checkbox.addItem("9", 0);
  checkbox.addItem("10", 0);
  checkbox.addItem("11", 0);
  checkbox.addItem("12", 0);
  checkbox.addItem("13", 0);
  checkbox.addItem("14", 0);
  checkbox.addItem("15", 0);
  checkbox.addItem("16", 0);
  checkbox.addItem("17", 0);
  checkbox.addItem("18", 0);
  checkbox.addItem("19", 0);
  checkbox.addItem("20", 0);
  checkbox.addItem("21", 0);
  checkbox.addItem("22", 0);
  checkbox.addItem("23", 0);
  checkbox.addItem("24", 0);
  checkbox.addItem("25", 0);
  checkbox.addItem("26", 0);
  checkbox.addItem("27", 0);
  checkbox.addItem("28", 0);
  checkbox.addItem("29", 0);
  checkbox.addItem("30", 0);
  checkbox.addItem("31", 0);
  checkbox.addItem("32", 0);

  checkbox.deactivateAll();


  controlP5.addButton("Up", 0, 120, 120, 35, 20);
  controlP5.addButton("Down", 0, 120, 160, 35, 20);
  
  controlP5.addButton("Forward", 0, 180, 120, 45, 20);
  controlP5.addButton("Backward", 0, 180, 160, 45, 20);  
  
  controlP5.addButton("TurnLeft", 0, 60, 120, 40, 20);
  controlP5.addButton("TurnRight", 0, 60, 160, 40, 20);  
  

  port = new Serial(this, Serial.list()[0], 9600);

  for (int i=0;i<32;i++) 
  {
    flagsToSend[i] = 0;
    previousFlags[i] = 0;
  }

  addMouseWheelListener(new java.awt.event.MouseWheelListener() { 
    public void mouseWheelMoved(java.awt.event.MouseWheelEvent evt) { 
      mouseWheel(evt.getWheelRotation());
    }
  }
  ); 

  startSetUp();
}

String addForwardZeroesTT(String inputString, int totalLength)
{

  String outString = "";
  for (int i = 0; i < (totalLength - inputString.length()); i++)
    outString += "0";

  outString = outString + inputString;

  return outString;
}


//Incremental like bits
//0000, 0001, 0010, 0011, 0100, etc
void Up()
{
  String currentSpeed = addForwardZeroesTT(binary(helicopterUpSpeed), 7);

  if(helicopterUpSpeed <= 125)
    helicopterUpSpeed += 1;

  String newSpeed = addForwardZeroesTT(binary(helicopterUpSpeed), 7);

  setNewSpeed(currentSpeed, newSpeed);
}

void Down()
{
  String currentSpeed = addForwardZeroesTT(binary(helicopterUpSpeed), 7);
  if (helicopterUpSpeed > 0)
    helicopterUpSpeed -= 1;
  String newSpeed = addForwardZeroesTT(binary(helicopterUpSpeed), 7);

  setNewSpeed(currentSpeed, newSpeed);
} 


void Backward()
{
  String currentSpeed = addForwardZeroesTT(binary(helicopterPitch), 7);

  helicopterPitch += 1;

  String newSpeed = addForwardZeroesTT(binary(helicopterPitch), 7);

   setNewPitch(currentSpeed, newSpeed);
}

void Forward()
{
  String currentSpeed = addForwardZeroesTT(binary(helicopterPitch), 7);

  helicopterPitch -= 1;

  String newSpeed = addForwardZeroesTT(binary(helicopterPitch), 7);

   setNewPitch(currentSpeed, newSpeed);
}

void TurnLeft()
{
  String currentSpeed = addForwardZeroesTT(binary(helicopterYaw), 7);

  helicopterYaw -= 1;

  String newSpeed = addForwardZeroesTT(binary(helicopterYaw), 7);

  setNewYaw(currentSpeed, newSpeed);
}

void TurnRight()
{
  String currentSpeed = addForwardZeroesTT(binary(helicopterYaw), 7);

  helicopterYaw += 1;

  String newSpeed = addForwardZeroesTT(binary(helicopterYaw), 7);

  setNewYaw(currentSpeed, newSpeed);
}


void setNewSpeed(String currentSpeed, String newSpeed)
{

  //Compare each bit and see if it needs changing.
  if  (newSpeed.charAt(6) != currentSpeed.charAt(6) )
    checkbox.toggle(23);

  if  (newSpeed.charAt(5) != currentSpeed.charAt(5) )
    checkbox.toggle(22);

  if  (newSpeed.charAt(4) != currentSpeed.charAt(4) )
    checkbox.toggle(21);    

  if  (newSpeed.charAt(3) != currentSpeed.charAt(3) )
    checkbox.toggle(20);    

  if  (newSpeed.charAt(2) != currentSpeed.charAt(2) )
    checkbox.toggle(19);    

  if  (newSpeed.charAt(1) != currentSpeed.charAt(1) )
    checkbox.toggle(18);    

  if  (newSpeed.charAt(0) != currentSpeed.charAt(0) )
    checkbox.toggle(17);
}

void setNewPitch(String currentSpeed, String newSpeed)
{
  if  (newSpeed.charAt(6) != currentSpeed.charAt(6) )
    checkbox.toggle(15);

  if  (newSpeed.charAt(5) != currentSpeed.charAt(5) )
    checkbox.toggle(14);

  if  (newSpeed.charAt(4) != currentSpeed.charAt(4) )
    checkbox.toggle(13);    

  if  (newSpeed.charAt(3) != currentSpeed.charAt(3) )
    checkbox.toggle(12);    

  if  (newSpeed.charAt(2) != currentSpeed.charAt(2) )
    checkbox.toggle(11);    

  if  (newSpeed.charAt(1) != currentSpeed.charAt(1) )
    checkbox.toggle(10);    

  if  (newSpeed.charAt(0) != currentSpeed.charAt(0) )
    checkbox.toggle(9);
}

void setNewYaw(String currentSpeed, String newSpeed)
{
  if  (newSpeed.charAt(6) != currentSpeed.charAt(6) )
    checkbox.toggle(7);

  if  (newSpeed.charAt(5) != currentSpeed.charAt(5) )
    checkbox.toggle(6);

  if  (newSpeed.charAt(4) != currentSpeed.charAt(4) )
    checkbox.toggle(5);    

  if  (newSpeed.charAt(3) != currentSpeed.charAt(3) )
    checkbox.toggle(4);    

  if  (newSpeed.charAt(2) != currentSpeed.charAt(2) )
    checkbox.toggle(3);    

  if  (newSpeed.charAt(1) != currentSpeed.charAt(1) )
    checkbox.toggle(2);    

  if  (newSpeed.charAt(0) != currentSpeed.charAt(0) )
    checkbox.toggle(1);
}

void startSetUp()
{
  //First clear the arduino.
  port.write('a'); 
  port.write('b'); 
  port.write('c'); 
  port.write('d'); 
  port.write('e'); 
  port.write('f'); 
  port.write('g'); 
  port.write('h'); 
  port.write('i'); 
  port.write('j'); 
  port.write('k'); 
  port.write('l');
  port.write('m'); 
  port.write('o'); 
  port.write('p'); 
  port.write('q');
  port.write('r'); 
  port.write('s'); 
  port.write('t'); 
  port.write('u');
  port.write('v'); 
  port.write('w'); 
  port.write('x'); 
  port.write('y'); 
  port.write('z'); 
  port.write('1'); 
  port.write('3'); 
  port.write('5');
  port.write('7'); 
  port.write('9'); 
  port.write('@'); 
  port.write('$'); 
  port.write('^');


  //Set the pulse to the basic configuration.
  checkbox.toggle(1);
  checkbox.toggle(6);


  checkbox.toggle(10);
  checkbox.toggle(11);

  checkbox.toggle(12);
  checkbox.toggle(13);
  checkbox.toggle(14);
  checkbox.toggle(15);
  checkbox.toggle(16);

  checkbox.toggle(25);

  checkbox.toggle(28);
  checkbox.toggle(29);
  checkbox.toggle(30);
}


void draw() 
{ 
  background(200);
  
  m.update();
  int[] img = m.image();
  
  //first draw the camera view onto the screen
  loadPixels();
  
  for(int i=0;i<640*480;i++){
      pixels[i] = img[i];
  }
  updatePixels();
   noFill();
  int[][] a;
   
  CheckHelicopterPosition();  
  
  
  text(" Current Speed: " + helicopterUpSpeed, 230, 135);
  text(" Pitch: " + helicopterPitch, 230, 165);
  text(" Yaw: " + helicopterYaw, 230, 195);  
}


void CheckHelicopterPosition()
{
  
  noFill();
  int[][] a;
  
  m.trackColor(255,255,0,255);
  //draw bounding boxes of globs
  a = m.globBoxes();
  stroke(255,0,0);
  
  int averageY = 0;
  
  for(int i=0;i<a.length;i++){
    int[] b = a[i];
    rect(b[0], b[1], b[2], b[3]);
    
    averageY += b[1];
    
  }
  
  if (a.length > 0)
  {
  averageY = averageY / a.length;
  line(0,averageY,640,averageY);
  
    text(" Average Y: " + averageY, 230, 215);  
    
    if (averageY > 240)
     {
      text(" Action: up ", 350, 20);
      delay(150);
      //Up();
     } 
     else
     {
      text(" Action down ", 350,20); 
      //delay(250);
      //Down();
     }
  }  

  
}  
  
  
  
void controlEvent(ControlEvent theEvent) {
  if (theEvent.isGroup()) {

    for (int i=0;i<theEvent.group().arrayValue().length;i++) 
    {
      byte n = (byte)theEvent.group().arrayValue()[i];
      flagsToSend[i] = n;
      //there was a change in the flags, send the update.
      if (previousFlags[i] != flagsToSend[i])
      {
        println(i);

        if (i==0) {   
          if (n == 0) { 
            port.write('a');
          } 
          else { 
            port.write('A');
          }
        }
        if (i==1) {   
          if (n == 0) { 
            port.write('b');
          } 
          else { 
            port.write('B');
          }
        } 
        if (i==2) {   
          if (n == 0) { 
            port.write('c');
          } 
          else { 
            port.write('C');
          }
        }
        if (i==3) {   
          if (n == 0) { 
            port.write('d');
          } 
          else { 
            port.write('D');
          }
        }                 
        if (i==4) {   
          if (n == 0) { 
            port.write('e');
          } 
          else { 
            port.write('E');
          }
        }    
        if (i==5) {   
          if (n == 0) { 
            port.write('f');
          } 
          else { 
            port.write('F');
          }
        }  
        if (i==6) {   
          if (n == 0) { 
            port.write('g');
          } 
          else { 
            port.write('G');
          }
        }
        if (i==7) {   
          if (n == 0) { 
            port.write('h');
          } 
          else { 
            port.write('H');
          }
        }
        if (i==8) {   
          if (n == 0) { 
            port.write('i');
          } 
          else { 
            port.write('I');
          }
        }
        if (i==9) {   
          if (n == 0) { 
            port.write('j');
          } 
          else { 
            port.write('J');
          }
        }
        if (i==10) {   
          if (n == 0) { 
            port.write('k');
          } 
          else { 
            port.write('K');
          }
        }
        if (i==11) {   
          if (n == 0) { 
            port.write('l');
          } 
          else { 
            port.write('L');
          }
        }
        if (i==12) {   
          if (n == 0) { 
            port.write('m');
          } 
          else { 
            port.write('M');
          }
        }
        if (i==13) {   
          if (n == 0) { 
            port.write('o');
          } 
          else { 
            port.write('O');
          }
        }  
        if (i==14) {   
          if (n == 0) { 
            port.write('p');
          } 
          else { 
            port.write('P');
          }
        }
        if (i==15) {   
          if (n == 0) { 
            port.write('q');
          } 
          else { 
            port.write('Q');
          }
        }
        if (i==16) {   
          if (n == 0) { 
            port.write('r');
          } 
          else { 
            port.write('R');
          }
        }
        if (i==17) {   
          if (n == 0) { 
            port.write('s');
          } 
          else { 
            port.write('S');
          }
        }
        if (i==18) {   
          if (n == 0) { 
            port.write('t');
          } 
          else { 
            port.write('T');
          }
        }
        if (i==19) {   
          if (n == 0) { 
            port.write('u');
          } 
          else { 
            port.write('U');
          }
        }
        if (i==20) {   
          if (n == 0) { 
            port.write('v');
          } 
          else { 
            port.write('V');
          }
        }
        if (i==21) {   
          if (n == 0) { 
            port.write('w');
          } 
          else { 
            port.write('W');
          }
        }
        if (i==22) {   
          if (n == 0) { 
            port.write('x');
          } 
          else { 
            port.write('X');
          }
        }
        if (i==23) {   
          if (n == 0) { 
            port.write('y');
          } 
          else { 
            port.write('Y');
          }
        }
        if (i==24) {   
          if (n == 0) { 
            port.write('z');
          } 
          else { 
            port.write('Z');
          }
        }
        if (i==25) {   
          if (n == 0) { 
            port.write('1');
          } 
          else { 
            port.write('2');
          }
        }
        if (i==26) {   
          if (n == 0) { 
            port.write('3');
          } 
          else { 
            port.write('4');
          }
        }
        if (i==27) {   
          if (n == 0) { 
            port.write('5');
          } 
          else { 
            port.write('6');
          }
        }
        if (i==28) {   
          if (n == 0) { 
            port.write('7');
          } 
          else { 
            port.write('8');
          }
        }
        if (i==29) {   
          if (n == 0) { 
            port.write('9');
          } 
          else { 
            port.write('!');
          }
        }
        if (i==30) {   
          if (n == 0) { 
            port.write('@');
          } 
          else { 
            port.write('#');
          }
        }
        if (i==31) {   
          if (n == 0) { 
            port.write('$');
          } 
          else { 
            port.write('%');
          }
        }
        if (i==32) {   
          if (n == 0) { 
            port.write('^');
          } 
          else { 
            port.write('&');
          }
        }
      }

      previousFlags[i]=n;
    }
  }
}


void mouseWheel(int delta) {
  if (delta == 1)
    Down();
  else
    Up();
}

