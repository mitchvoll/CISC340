/*
 * CISC340 FALL 2015 - Project 1
 * motor program to provide functions for maneuvering robot
 * Mitch Vollebregt - 07401124
 * Mike Leroux - <STUDENTNUM>
 * Greg Slasor - <STUDENTNUM>
 */ 

#include "Arduino.h"
#include "motor.h"

// required adafruit motor shield libraries
// need to obtain library from https://github.com/adafruit/Adafruit_Motor_Shield_V2_Library
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_PWMServoDriver.h"

// constructor
motor::motor(int pin_1, int pin_2) {
  dc_pin_1 = pin_1;
  dc_pin_2 = pin_2;
  
  // create motor shield object
  afms = Adafruit_MotorShield();
  
  // create dc motor objects for each motor
  dc_motor_1 = afms.getMotor(pin_1);
  dc_motor_2 = afms.getMotor(pin_2);
}

// drive function controls the speed, direction, and travel distance of the robot
// robot will first orient itself based on dir then move spd speed for trvl seconds 
// - param spd: value between 0-255 determines the speed of robot while going straight.
// - param dir: degrees 0-360 where 0 and 360 are forward and 180 is backwards.
//   degrees for direction get devided into 8 45 degree segments. Defaults to 0.
//   but input is given as any value n 0<=n<=360
// - param trvl: determines how long robot moves forward in seconds.
//   Defaults to -1 which means indefinite
void motor::drive(int spd, int dir=0, int trvl=-1){
//  need to implement  
}

int motor::spd(){ return current_speed; }

// return current direction relative to start in degrees
int motor::dir(){ return current_dir; }

void motor::spin_move(){
  dc_motor_1->setSpeed(100);
  dc_motor_1->run(FORWARD);
  dc_motor_2->setSpeed(100);
  dc_motor_2->run(BACKWARD);
  delay(4000);
}



