/*
 * CISC340 FALL 2015 - Project 1
 * motor program to provide functions for maneuvering robot
 * Mitch Vollebregt - 07401124
 * Mike Leroux - 10012715
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
Motor::Motor(int pin_1, int pin_2) {
  dc_pin_1 = pin_1;
  dc_pin_2 = pin_2;
  
  // create motor shield object
  afms = Adafruit_MotorShield();
}

void Motor::init(){
  afms.begin();
  // create dc motor objects for each motor
  dc_motor_1 = afms.getMotor(dc_pin_1);
  dc_motor_2 = afms.getMotor(dc_pin_2);
}

// drive function controls the speed, direction, and travel distance of the robot
// robot will first orient itself based on dir then move spd speed for trvl seconds 
// - param spd: value between 0-255 determines the speed of robot while going straight.
// - param dir: degrees 0-360 where 0 and 360 are forward and 180 is backwards.
//   degrees for direction scale how much the motor travels for turning. Defaults to 0.
//   Input is given as any value n 0<=n<=360
void Motor::drive(int spd, int dir=0){
  // do not bother turning the robot dir is 0 or 360
  if (dir != 0 && dir != 360){
    // turn robot left
    if (dir > 180 && dir < 360){
      dir = (dir-360)*-1;
      dc_motor_1->setSpeed(0); // pivot inside wheel
      // run outside wheel
      dc_motor_2->run(BACKWARD);
      dc_motor_2->setSpeed(100);
    }
    // turn robot right or backwards
    else if (dir > 0 && dir <= 180){
      dc_motor_2->setSpeed(0); // pivot inside wheel
      // run outside wheel
      dc_motor_1->run(BACKWARD);
      dc_motor_1->setSpeed(100);
    }
    // wait time for desired turn    
    int amount_to_travel = dir*9;
    delay(amount_to_travel);
    // stop motors after turn
    dc_motor_1->setSpeed(0);
    dc_motor_2->setSpeed(0);
  }
//  Serial.println("turning dir: " + String(dir));
//  Serial.println("driving straight");
  // move robot after turning
  dc_motor_1->run(BACKWARD);
  dc_motor_2->run(BACKWARD);
  dc_motor_1->setSpeed(spd);
  dc_motor_2->setSpeed(spd);
}

void Motor::pivot(){
  dc_motor_1->run(FORWARD);
  dc_motor_2->run(FORWARD);
  //  move backwards a little
  dc_motor_1->setSpeed(100);
  dc_motor_2->setSpeed(100);
  delay(200);

  //  pivot
  dc_motor_1->run(BACKWARD);
  dc_motor_2->run(FORWARD);
  delay(9*135);
  // continue driving forward
  drive(100,0);
  
}

// return the current speed of the robot
int Motor::spd(){ return current_speed; }

// return current direction relative to start in degrees
int Motor::dir(){ return current_dir; }



