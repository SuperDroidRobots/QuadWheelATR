//=========================HEADER=============================================================
/*
   Quad ATR Mecanum with Sabertooth
   AUTHOR: Jason Traud
   DATE: 6/8/2015
   
   This firmware demonstrates basic movement routines on a Mecanum ATR with a Sabertooth
   motor controller.
   
   Hardware: 
   
     Arduino Uno R3       (MCU-050-000)
     Programmable Mecanum (TP-095-004) 
     Sabertooth 2x25      (TE-091-225)

   Connections:    
     
     Arduino D3   -   Sabertooth S1 (Serial COM)
     Arduino D4   -   Sabertooth S2 (Emergency Stop)
     Arduino Gnd  -   Sabertooth 0V (A common ground is needed for stable communication) 
     
   DIP Switch Settings:
   
     00 11 11 (Address 128, front)
     00 10 11 (Address 129, rear)
     
   Support:    
     
     SuperDroid Robots Support Forum
       http://www.sdrobots.com/forums/   
     
     Vectoring Robot Support Page
       http://www.superdroidrobots.com/shop/custom.aspx/vectoring-robots/44/  
   
             
			
   License: CCAv3.0 Attribution-ShareAlike (http://creativecommons.org/licenses/by-sa/3.0/)
   You're free to use this code for any venture. Attribution is greatly appreciated. 
//============================================================================================
*/

// ****************************************************
// Libraries
// ****************************************************
#include <SoftwareSerial.h>
#include <Sabertooth.h>

// *********************
// Define hardware pins
// *********************
#define sabertoothEstop 4 // This is connected to S2 on the motor controllers. 
                          // When this pin is pulled low the motors will stop. 

// Declaration of the software serial UART and motor controller objects
SoftwareSerial SWSerial(2, 3); // RX on pin 2 (unused), TX on pin 3 (to S1).
Sabertooth frontSaber(128, SWSerial); // Address 128, front motors, 1 = left, 2 = right
Sabertooth rearSaber(129, SWSerial);  // Address 130, rear motors, 1 = left, 2 = right


//******************************************************************************
// Sets up our serial com, hardware pins, SPI bus for ethernet shield and motor controller.
// RETURNS: Nothing
//******************************************************************************
void setup() 
{
  delay(2000);           // Short delay to allow the motor controllers
                         // to power up before we attempt to send it commands.
                         // If you try to talk to them before the finish booting
                         // they can lock up and be unresponsive
  
  Serial.begin(9600);    // Serial for the debug output
  SWSerial.begin(9600);  // Serial for the motor controllers
  
  frontSaber.autobaud(); // Allows the motor controllers to detect the baud rate
  rearSaber.autobaud();  // we're using and adjust appropriately
  
  // Initialize GPIO inputs and outputs
  pinMode(sabertoothEstop, OUTPUT);
 
  allStop();		// Make sure all motors are stopped for safety
}

//******************************************************************************
// This is our main program loop and is wrapped in an implied while(true) loop.
// This sample code demonstrates example movement for the robot and alternates
// through the motions by calling the commandMotors function. 
// 
// Description of the type of movement and the power level sent is printed to
// the serial console at a baud rate of 9600
// 
// RETURNS: Nothing
//******************************************************************************
void loop() 
{
  int i = 0; // Counters
  int j = 0;
  int movementDelay = 15; // Delay in between movement commands
  int speedDelta = 64;
  int topForwardSpeed = 127 + speedDelta;
  int topBackwardSpeed = 127 - speedDelta;
  
  // *************************
  // Front and Back Motion
  // *************************
  for(int i = 127; i < topForwardSpeed; i++)
  {
    commandMotors(i, 127, 127, 1);     
    Serial.print("Forward Power: "); Serial.println(i); delay(movementDelay);
  }
  allStop(); // Stops the motors 
  
  for(int i = 127; i > topBackwardSpeed; i--)
  {
    commandMotors(i, 127, 127, 1); 
    Serial.print("Backward Power: "); Serial.println(i); delay(movementDelay);
  }
  allStop(); // Stops the motors 
  
  // *************************
  // Right and Left Motion
  // *************************  
  for(int i = 127; i < topForwardSpeed; i++)
  {
    commandMotors(127, i, 127, 1); 
    Serial.print("Right Power: "); Serial.println(i); delay(movementDelay);
  }
  allStop(); // Stops the motors 
  
  for(int i = 127; i > topBackwardSpeed; i--)
  {
    commandMotors(127, i, 127, 1); 
    Serial.print("Left Power: "); Serial.println(i); delay(movementDelay);
  }  
  allStop(); // Stops the motors 
  
  // *************************
  // Clockwise and Counter clockwise  Motion
  // *************************
  for(int i = 127; i < topForwardSpeed; i++)
  {
    commandMotors(127, 127, i, 1); 
    Serial.print("CW Power: "); Serial.println(i); delay(movementDelay);
  }
  allStop(); // Stops the motors 
  
  for(int i = 127; i > topBackwardSpeed; i--)
  {
    commandMotors(127, 127, i, 1); 
    Serial.print("CCW Power: "); Serial.println(i); delay(movementDelay);
  }
  allStop();
  
  // *************************
  // Diagonal Motion
  // *************************
  for(int i = 127; i < topForwardSpeed; i++)
  {
    commandMotors(i, i, 127, 1); 
    Serial.print("Top Right Power: "); Serial.println(i); delay(movementDelay);
  }  
  allStop(); // Stops the motors   
  
  for(int i = 127; i > topBackwardSpeed; i--)
  {
    commandMotors(i, i, 127, 1); 
    Serial.print("Rear Left Power: "); Serial.println(i); delay(movementDelay);
  }  
  allStop(); // Stops the motors  
  
  j = 127; // Reinitialize 
  for(int i = 127; i < topForwardSpeed; i++)
  {
    commandMotors(i, j, 127, 1); j--;
    Serial.print("Top left Power: "); Serial.println(i); delay(movementDelay);
  }  
  allStop(); // Stops the motors 
  
  j = 127; // Reinitialize 
    for(int i = 127; i > topBackwardSpeed; i--)
  {
    commandMotors(i, j, 127, 1); j++;
    Serial.print("Rear Left Power: "); Serial.println(i); delay(movementDelay);
  }  
  allStop(); // Stops the motors  
}

//******************************************************************************
// Sets the speed of all motor controllers to zero and sets all ESTOPs
// RETURNS: NONE
//******************************************************************************
void allStop()
{
  digitalWrite(sabertoothEstop, LOW);
  
  frontSaber.motor(1, 0);
  frontSaber.motor(2, 0);
  rearSaber.motor(1, 0);
  rearSaber.motor(2, 0);
}



//******************************************************************************
// Processes all motor commands. 
// The function expects three values; 
//    yAxis is our forward and back movement
//    xAxis is our left and right movement
//    spin is our third access
//    mode is the type of movement we're sending (tank versus vectoring)
//
// To understand the input of this function you need to envision a grid with 0,0
// in the bottom left, 127,127 in the center and 255,255 in the top right. The location
// of the data point passed into this function relative to the 127,127 center point
// is the direction that the robot is commanded to vector
// 
// RETURNS: NONE
//******************************************************************************
void commandMotors(int yAxis, int xAxis, int spin, int mode)
{
  // Initialize our local variables
  int leftFrontPower = 0;
  int leftRearPower = 0;
  int rightFrontPower = 0; 
  int rightRearPower = 0;
  int maxMotorPower = 0;
  double tempScale = 0;
  
  // Motor Constants 
  int motorValueMax = 255;  
  int motorValueMin = 0;
  int motorZero = 127;
  
  // Bound our incoming data to a safe and expected range
  if (yAxis > motorValueMax) { yAxis = motorValueMax; }
  else  if (yAxis < motorValueMin) { yAxis = motorValueMin; }  
  if (xAxis > motorValueMax) { xAxis = motorValueMax; }
  else  if (xAxis < motorValueMin) { xAxis = motorValueMin; }  
  if (spin > motorValueMax) { spin = motorValueMax; }
  else  if (spin < motorValueMin) { spin = motorValueMin; }
    
  // Shift incoming data to straddle 0
  yAxis = yAxis - 127;
  xAxis = xAxis - 127;
  spin = spin - 127;
  
  // A mode value of 1 passed into this function changes the motor mixing to
  // vectoring mode
  if (mode == 1)
  {    
    // *************************
    // Front and Back Motion
    // *************************
    leftFrontPower = leftFrontPower + yAxis;
    leftRearPower = leftRearPower + yAxis;
    rightFrontPower = rightFrontPower + yAxis;
    rightRearPower = rightRearPower + yAxis;
    
    // *************************
    // Left and Right Motion
    // *************************
    leftFrontPower = leftFrontPower + xAxis;
    leftRearPower = leftRearPower - xAxis;
    rightFrontPower = rightFrontPower - xAxis;
    rightRearPower = rightRearPower + xAxis;
    
    // *************************
    // Spin
    // *************************
    leftFrontPower = leftFrontPower + spin;
    leftRearPower = leftRearPower + spin;
    rightFrontPower = rightFrontPower - spin;
    rightRearPower = rightRearPower - spin;
  
    // After our mixing above our motor powers are most likely going to exceed
    // our maximum values. We need to find our maximum and scale everything down
    // to values that our motor controller can understand 
    maxMotorPower = max(abs(leftFrontPower), abs(leftRearPower));
    maxMotorPower = max(maxMotorPower, abs(rightFrontPower));
    maxMotorPower = max(maxMotorPower, abs(rightRearPower)); 
    
    // Scale down by the maximum value if we exceed 127
    if (maxMotorPower > 127)
    {
     tempScale = (double)127 / (double)maxMotorPower;
     leftFrontPower = tempScale * (double)leftFrontPower;
     leftRearPower = tempScale * (double)leftRearPower;
     rightFrontPower = tempScale * (double)rightFrontPower;
     rightRearPower = tempScale * (double)rightRearPower;
    }
    
    // Cleans up our output data
    leftFrontPower = boundAndDeadband(leftFrontPower);
    leftRearPower = boundAndDeadband(leftRearPower);
    rightFrontPower = boundAndDeadband(rightFrontPower);
    rightRearPower = boundAndDeadband(rightRearPower);
    
    // Raises the ESTOP lines before commanding the motors
    digitalWrite(sabertoothEstop, HIGH);
    
    // Applies our calculated and bounded values to our drive motor controllers
    frontSaber.motor(1, rightFrontPower);
    frontSaber.motor(2, leftFrontPower);
    rearSaber.motor(1, rightRearPower);
    rearSaber.motor(2, leftRearPower);   
  }
  
  // If the mode value is not "1" then we are in tank mode
  else 
  {
    // Applies our calculated and bounded values to our drive motor controllers
    frontSaber.drive(yAxis);
    frontSaber.turn(xAxis);
    
    rearSaber.drive(yAxis);
    rearSaber.turn(xAxis);
  }
}

//******************************************************************************
// Cleans up our values for the motor controllers 
// The motor controllers only accept a value range of -127 to 127. We also apply
// a deadband so the robot doesn't drift when idle
// 
// RETURNS: Cleaned up value
//******************************************************************************
int boundAndDeadband (int inputValue) 
{
  if (inputValue < -127)  { inputValue = -127; }
  if (inputValue > 127)   { inputValue = 127; }
  if ((inputValue < 5) && (inputValue > -5)) { inputValue = 0; }

  return inputValue; 
}
