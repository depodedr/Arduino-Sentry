// Dylan DePodesta - 1327812
// Elliot Wong - 1302982

// Pixy Libraries 
#include <SPI.h> 
#include <Pixy.h>

Pixy pixy; // Name for pixy pan tilt control
Pixy control; // Name for the bluetooth control

int32_t pan;
int32_t tilt;
int ervalpan = 0;
int ervaltilt = 0;
char state; // Bluetooth controller modes
char mode;

class ServoLoop // Loop for the servo motor control
{
public:
  ServoLoop(int32_t pgain, int32_t dgain);

  void update(int32_t error);
   
  int32_t m_pos; // Position number 
  int32_t m_prevError; // Previous error number  
  int32_t m_pgain; 
  int32_t m_dgain; 
};

ServoLoop panLoop(300, 500); // Initial Position pan
ServoLoop tiltLoop(500, 700); // Initial position tilt

ServoLoop::ServoLoop(int32_t pgain, int32_t dgain) // looping the servo
{
  m_pos = PIXY_RCS_CENTER_POS;
  m_pgain = pgain;
  m_dgain = dgain;
  m_prevError = 0x80000000L;
}

void ServoLoop::update(int32_t error) // Function for servo loop
{
  long int vel;
  char buf[32];
  if (m_prevError!=0x80000000)
  {  
    vel = (error*m_pgain + (error - m_prevError)*m_dgain)>>10; // calculating vel
    m_pos += vel; // calculating real position 
    if (m_pos>PIXY_RCS_MAX_POS) 
      m_pos = PIXY_RCS_MAX_POS; 
    else if (m_pos<PIXY_RCS_MIN_POS) 
      m_pos = PIXY_RCS_MIN_POS;
  }
  m_prevError = error;
}

 
void setup() 
{
 Serial.begin(9600); 

 pixy.init();
 control.init();
}
 
void loop() 
{

 if(Serial.available() > 0)
 {
 state = Serial.read(); // Reading the state 
 }
  // Control Pixy via Bluetooth app on Smart Phone
  if (state == '0') // Pixy turns left on control
 {
  ervaltilt = 0;
  ervalpan = 5;
  Serial.println('A');
 }

 else if (state == '1') // Pixy turns right on control
 {
  
  ervaltilt = 0;
  ervalpan = -5;
  Serial.println('B');
 }

 else if (state == '3') //Pixy goes down on control
 {
  ervalpan = 0;
  ervaltilt = 5;
  Serial.println('C');
 }

 else if (state == '2') //Pixy goes up control
 {
  ervalpan = 0;
  ervaltilt = -5;
  Serial.println('D');
 }

 else if (state == '4')
 {
  ervalpan = 0;
  ervaltilt = 0;
  Serial.println('E');
 }

// The code below here is just going to be copied and pasted 4 more times
// The define statements are in each block of code becasue calculating the midpoint,
// messes around with our remote control so it is in the coded blocks

 else if (state == '5') //FIND BLUE object and tracks it
{
#define X_CENTER        ((PIXY_MAX_X-PIXY_MIN_X)/2) // defining the centre of x position     
#define Y_CENTER        ((PIXY_MAX_Y-PIXY_MIN_Y)/2) // Defining the centre of y position

  static int i = 0;
  int w,j, sigBlock, counterVal;
  uint16_t blocks;
  char buf[32]; 
  int32_t panError, tiltError;
  
  blocks = pixy.getBlocks(); // Getting the pixy blocks

  // Checks for the right signature value and follows it
  if (blocks)
  counterVal = 0;
  {
  for (w = 0; w < blocks; w++ ){
    if (pixy.blocks[w].signature == 1) {
        sigBlock = w;
        counterVal++;
      }
    }
    if (counterVal > 0) {
        panError = X_CENTER-pixy.blocks[sigBlock].x;
        tiltError = pixy.blocks[sigBlock].y-Y_CENTER;
        
        panLoop.update(panError);
        tiltLoop.update(tiltError);
        
        pixy.setServos(panLoop.m_pos, tiltLoop.m_pos);
        
        i++;
        
        // do this (print) every 50 frames because printing every
        // frame would bog down the Arduino
        if (i%50==0) 
        {
          sprintf(buf, "Detected %d:\n", blocks);
          Serial.print(buf);
        for (j=0; j<blocks; j++)
        {
          sprintf(buf, "  block %d: ", j);
          Serial.print(buf); 
          pixy.blocks[j].print();
        }
      }
    }
    // this else statement says to do nothing if the signature from pixy is the wrong one
    else {
    }
  }
}

else if (state == '6') //FIND Red object and tracks it
{
#define X_CENTER        ((PIXY_MAX_X-PIXY_MIN_X)/2)       
#define Y_CENTER        ((PIXY_MAX_Y-PIXY_MIN_Y)/2)

  static int i = 0;
  int w,j, sigBlock, counterVal;
  uint16_t blocks;
  char buf[32]; 
  int32_t panError, tiltError;
  
  blocks = pixy.getBlocks();
  
  if (blocks)
  counterVal = 0;
  {
  for (w = 0; w < blocks; w++ ){
    if (pixy.blocks[w].signature == 2) {
        sigBlock = w;
        counterVal++;
      }
    }
    if (counterVal > 0) {
        panError = X_CENTER-pixy.blocks[sigBlock].x;
        tiltError = pixy.blocks[sigBlock].y-Y_CENTER;
        
        panLoop.update(panError);
        tiltLoop.update(tiltError);
        
        pixy.setServos(panLoop.m_pos, tiltLoop.m_pos);
        
        i++;
        
        // do this (print) every 50 frames because printing every
        // frame would bog down the Arduino
        if (i%50==0) 
        {
          sprintf(buf, "Detected %d:\n", blocks);
          Serial.print(buf);
        for (j=0; j<blocks; j++)
        {
          sprintf(buf, "  block %d: ", j);
          Serial.print(buf); 
          pixy.blocks[j].print();
        }
      }
    }
    else {
    }
  }
}

else if (state == '7') //FIND green object and track it
{
#define X_CENTER        ((PIXY_MAX_X-PIXY_MIN_X)/2)       
#define Y_CENTER        ((PIXY_MAX_Y-PIXY_MIN_Y)/2)

  static int i = 0;
  int w,j, sigBlock, counterVal;
  uint16_t blocks;
  char buf[32]; 
  int32_t panError, tiltError;
  
  blocks = pixy.getBlocks();
  
  if (blocks)
  counterVal = 0;
  {
  for (w = 0; w < blocks; w++ ){
    if (pixy.blocks[w].signature == 3) {
        sigBlock = w;
        counterVal++;
      }
    }
    if (counterVal > 0) {
        panError = X_CENTER-pixy.blocks[sigBlock].x;
        tiltError = pixy.blocks[sigBlock].y-Y_CENTER;
        
        panLoop.update(panError);
        tiltLoop.update(tiltError);
        
        pixy.setServos(panLoop.m_pos, tiltLoop.m_pos);
        
        i++;
        
        // do this (print) every 50 frames because printing every
        // frame would bog down the Arduino
        if (i%50==0) 
        {
          sprintf(buf, "Detected %d:\n", blocks);
          Serial.print(buf);
        for (j=0; j<blocks; j++)
        {
          sprintf(buf, "  block %d: ", j);
          Serial.print(buf); 
          pixy.blocks[j].print();
        }
      }
    }
    else {
    }
  }
}

else if (state == '8') //FIND purple object and tracks it
{
#define X_CENTER        ((PIXY_MAX_X-PIXY_MIN_X)/2)       
#define Y_CENTER        ((PIXY_MAX_Y-PIXY_MIN_Y)/2)

  static int i = 0;
  int w,j, sigBlock, counterVal;
  uint16_t blocks;
  char buf[32]; 
  int32_t panError, tiltError;
  
  blocks = pixy.getBlocks();
  
  if (blocks)
  counterVal = 0;
  {
  for (w = 0; w < blocks; w++ ){
    if (pixy.blocks[w].signature == 4) {
        sigBlock = w;
        counterVal++;
      }
    }
    if (counterVal > 0) {
        panError = X_CENTER-pixy.blocks[sigBlock].x;
        tiltError = pixy.blocks[sigBlock].y-Y_CENTER;
        
        panLoop.update(panError);
        tiltLoop.update(tiltError);
        
        pixy.setServos(panLoop.m_pos, tiltLoop.m_pos);
        
        i++;
        
        // do this (print) every 50 frames because printing every
        // frame would bog down the Arduino
        if (i%50==0) 
        {
          sprintf(buf, "Detected %d:\n", blocks);
          Serial.print(buf);
        for (j=0; j<blocks; j++)
        {
          sprintf(buf, "  block %d: ", j);
          Serial.print(buf); 
          pixy.blocks[j].print();
        }
      }
    }
    else {
    }
  }
}

// this if statement prevents the motors from reacting to the values left by the bluetooth directional buttons
if((state != '5') && (state != '6') && (state != '7') && (state != '8'))
{
 pan = pan+ervalpan;
 tilt = tilt+ervaltilt;
 
   control.setServos(pan,tilt);

   delay(10);
 }
}


