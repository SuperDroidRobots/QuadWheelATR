/*********************************************************

Quad-Wheel Vectoring Robot Example
Jason Traud
SuperDroid Robots
November 5, 2013

This code uses an Arduino Uno mounted on a Tri-Wheel Vectoring platform
TP-094-004. The robot commands four PWM motor controllers (TE-058-000)
to control three independent omni-directional wheels. 

The goal of this firmware is to cycle through the possible motor movements
to provide a base for future autonomous routines. 

Platform:
http://www.superdroidrobots.com/shop/item.aspx/ig32-mecanum-wheel-vectoring-robot-platform/1485/

Motor Controller:
http://www.superdroidrobots.com/shop/item.aspx/pwm-motor-controller-3a-12-55v/583/

Vectoring Robot Support Page:
http://www.superdroidrobots.com/shop/custom.aspx/vectoring-robots/44/

***********************************************************/

// Define pins for PWM motor controllers
#define pwmFR 3
#define dirFR 4

#define pwmFL 6 
#define dirFL 8

#define pwmRR 5
#define dirRR 7

#define pwmRL 9
#define dirRL 10

// Include necessary header files
#include "Arduino.h"

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


void setup() {
  
  // Set moro controller communication pins as outputs
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

// Stops the Robot
void allStop() {
  analogWrite(pwmFR, 0);
  analogWrite(pwmRR, 0);
  analogWrite(pwmFL, 0);
  analogWrite(pwmRL, 0);
}

void commandMotors() {
  analogWrite(pwmFR, motorFR.pulse);
  analogWrite(pwmRR, motorRR.pulse);
  analogWrite(pwmFL, motorFL.pulse);
  analogWrite(pwmRL, motorRL.pulse);
}

void forwardMovement() {
  
  // Set direction bits
  digitalWrite(dirFR, HIGH); digitalWrite(dirFL, LOW); digitalWrite(dirRR, HIGH); digitalWrite(dirRL, LOW);
  
  // Ramp up and command motor controllers
  for (int i = 0; i < 64; i++)
  { motorFR.pulse = i; motorFL.pulse = i; motorRR.pulse = i; motorRL.pulse = i; commandMotors(); delay(25); }  
  allStop();
}

void backwardMovement() {

  // Set direction bits
  digitalWrite(dirFR, LOW); digitalWrite(dirFL, HIGH); digitalWrite(dirRR, LOW); digitalWrite(dirRL, HIGH);
  
  // Ramp up and command motor controllers
  for (int i = 0; i < 64; i++)
  { motorFR.pulse = i; motorFL.pulse = i; motorRR.pulse = i; motorRL.pulse = i; commandMotors(); delay(25); }
  allStop();
}

void leftMovement() {

  // Set direction bits
  digitalWrite(dirFR, HIGH); digitalWrite(dirFL, LOW); digitalWrite(dirRR, LOW); digitalWrite(dirRL, HIGH);
  
  // Ramp up and command motor controllers
  for (int i = 0; i < 64; i++)
  { motorFR.pulse = i; motorFL.pulse = i; motorRR.pulse = i; motorRL.pulse = i; commandMotors(); delay(25); }
  allStop();
}

void rightMovement() {
  
  // Set direction bits
  digitalWrite(dirFR, LOW); digitalWrite(dirFL, HIGH); digitalWrite(dirRR, HIGH); digitalWrite(dirRL, LOW);
  
  // Ramp up and command motor controllers
  for (int i = 0; i < 64; i++)
  { motorFR.pulse = i; motorFL.pulse = i; motorRR.pulse = i; motorRL.pulse = i; commandMotors(); delay(25); }
  allStop();
}

void spinClockwise () {
  
  // Set direction bits
  digitalWrite(dirFR, LOW); digitalWrite(dirFL, LOW); digitalWrite(dirRR, LOW); digitalWrite(dirRL, LOW);
  
  // Ramp up and command motor controllers
  for (int i = 0; i < 64; i++)
  { motorFR.pulse = i; motorFL.pulse = i; motorRR.pulse = i; motorRL.pulse = i; commandMotors(); delay(25); }
  allStop();
}

void spinCounterClockwise () {
  
  // Set direction bits
  digitalWrite(dirFR, HIGH); digitalWrite(dirFL, HIGH); digitalWrite(dirRR, HIGH); digitalWrite(dirRL, HIGH);
  
  // Ramp up and command motor controllers
  for (int i = 0; i < 64; i++)
  { motorFR.pulse = i; motorFL.pulse = i; motorRR.pulse = i; motorRL.pulse = i; commandMotors(); delay(25); }
  allStop();
}

// The sample program commands the motor movements in a continuous loop
void loop() 
{
  forwardMovement();
  backwardMovement();
  rightMovement();
  leftMovement();
  spinClockwise();
  spinCounterClockwise();
}
