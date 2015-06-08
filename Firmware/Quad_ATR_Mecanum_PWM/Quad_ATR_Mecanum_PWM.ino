//=========================HEADER=============================================================
/*
   Quad ATR Mecanum with PWM Motor Control
   AUTHOR: Jason Traud
   DATE: 6/8/2015
   
   This firmware demonstrates basic movement routines on a four wheeled Mecanum robot with
   PWM motor Controllers
   
   Hardware: 
   
     Arduino Uno R3       (MCU-050-000)
     Programmable Mecanum (TP-095-004) 
     LMD18200 Breakout    (TE-058-000)

   Connections:    
     
     Arduino D3   -   PWM Pin on Front Right Motor Controller
     Arduino D4   -   Direction Pin on Front Right Motor Controller

     Arduino D6   -   PWM Pin on Front Left Motor Controller
     Arduino D8   -   Direction Pin on Front Left Motor Controller
     
     Arduino D5   -   PWM Pin on Rear Right Motor Controller
     Arduino D7   -   Direction Pin on Rear Right Motor Controller
     
     Arduino D9   -   PWM Pin on Rear Left Motor Controller
     Arduino D10  -   Direction Pin on Rear Left Motor Controller

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

// none

// ****************************************************
// Hardware Pin Connections
// ****************************************************

#define pwmFR 3
#define dirFR 4

#define pwmFL 6 
#define dirFL 8

#define pwmRR 5
#define dirRR 7

#define pwmRL 9
#define dirRL 10

// ****************************************************
// Motor Controller Variables
// ****************************************************

// Command struct for motor controllers
typedef struct {
	int pulse;
	bool direction;
	bool brake;
}	MotorValues;

// Defines structs for each motor
MotorValues motorFR;
MotorValues motorFL;
MotorValues motorRR;
MotorValues motorRL;


// ****************************************************
// Sets output analog values based on command struct
// RETURNS: none
// ****************************************************
void commandMotors() {
  analogWrite(pwmFR, motorFR.pulse);
  analogWrite(pwmRR, motorRR.pulse);
  analogWrite(pwmFL, motorFL.pulse);
  analogWrite(pwmRL, motorRL.pulse);
}

// ****************************************************
// Stops the robot by setting all outputs to 0
// RETURNS: none
// ****************************************************
void allStop() {
  analogWrite(pwmFR, 0);
  analogWrite(pwmRR, 0);
  analogWrite(pwmFL, 0);
  analogWrite(pwmRL, 0);
}

// ****************************************************
// Forward Movement Demonstration
// RETURNS: none
// ****************************************************
void forwardMovement() {
  
  // Set direction bits
  digitalWrite(dirFR, HIGH); digitalWrite(dirFL, LOW); digitalWrite(dirRR, HIGH); digitalWrite(dirRL, LOW);
  
  // Ramp up and command motor controllers
  for (int i = 0; i < 64; i++)
  { motorFR.pulse = i; motorFL.pulse = i; motorRR.pulse = i; motorRL.pulse = i; commandMotors(); delay(25); }  
  allStop();
}

// ****************************************************
// Backward Movement Demonstration
// RETURNS: none
// ****************************************************
void backwardMovement() {

  // Set direction bits
  digitalWrite(dirFR, LOW); digitalWrite(dirFL, HIGH); digitalWrite(dirRR, LOW); digitalWrite(dirRL, HIGH);
  
  // Ramp up and command motor controllers
  for (int i = 0; i < 64; i++)
  { motorFR.pulse = i; motorFL.pulse = i; motorRR.pulse = i; motorRL.pulse = i; commandMotors(); delay(25); }
  allStop();
}


// ****************************************************
// Sidestep Left Movement Demonstration
// RETURNS: none
// ****************************************************
void leftMovement() {

  // Set direction bits
  digitalWrite(dirFR, HIGH); digitalWrite(dirFL, LOW); digitalWrite(dirRR, LOW); digitalWrite(dirRL, HIGH);
  
  // Ramp up and command motor controllers
  for (int i = 0; i < 64; i++)
  { motorFR.pulse = i; motorFL.pulse = i; motorRR.pulse = i; motorRL.pulse = i; commandMotors(); delay(25); }
  allStop();
}


// ****************************************************
// Sidestep Right Movement Demonstration
// RETURNS: none
// ****************************************************
void rightMovement() {
  
  // Set direction bits
  digitalWrite(dirFR, LOW); digitalWrite(dirFL, HIGH); digitalWrite(dirRR, HIGH); digitalWrite(dirRL, LOW);
  
  // Ramp up and command motor controllers
  for (int i = 0; i < 64; i++)
  { motorFR.pulse = i; motorFL.pulse = i; motorRR.pulse = i; motorRL.pulse = i; commandMotors(); delay(25); }
  allStop();
}

// ****************************************************
// Spin Clockwise Movement Demonstration
// RETURNS: none
// ****************************************************
void spinClockwise () {
  
  // Set direction bits
  digitalWrite(dirFR, LOW); digitalWrite(dirFL, LOW); digitalWrite(dirRR, LOW); digitalWrite(dirRL, LOW);
  
  // Ramp up and command motor controllers
  for (int i = 0; i < 64; i++)
  { motorFR.pulse = i; motorFL.pulse = i; motorRR.pulse = i; motorRL.pulse = i; commandMotors(); delay(25); }
  allStop();
}

// ****************************************************
// Spin Counter-Clockwise Movement Demonstration
// RETURNS: none
// ****************************************************
void spinCounterClockwise () {
  
  // Set direction bits
  digitalWrite(dirFR, HIGH); digitalWrite(dirFL, HIGH); digitalWrite(dirRR, HIGH); digitalWrite(dirRL, HIGH);
  
  // Ramp up and command motor controllers
  for (int i = 0; i < 64; i++)
  { motorFR.pulse = i; motorFL.pulse = i; motorRR.pulse = i; motorRL.pulse = i; commandMotors(); delay(25); }
  allStop();
}

// ****************************************************
// Initial setup function, called once
// RETURNS: none
// ****************************************************
void setup() {
  
  // Set motor controller communication pins as outputs
  pinMode(pwmFR, OUTPUT);
  pinMode(dirFR, OUTPUT);
  
  pinMode(pwmFL, OUTPUT);
  pinMode(dirFL, OUTPUT);
  
  pinMode(pwmRR, OUTPUT);
  pinMode(dirRR, OUTPUT);
  
  pinMode(pwmRL, OUTPUT);
  pinMode(dirRL, OUTPUT);

  // Command all motors to stop
  allStop();
}

// ****************************************************
// Main program loop. We'll cycle through commands here
// RETURNS: none
// ****************************************************
void loop() {
  forwardMovement();
  backwardMovement();
  rightMovement();
  leftMovement();
  spinClockwise();
  spinCounterClockwise();
}
