/*
 * CISC340 FALL 2015 - Project 1
 * motor program to provide functions for maneuvering robot
 * Mitch Vollebregt - 07401124
 * Mike Leroux - 10012715
 * Greg Slasor - <STUDENTNUM>
 */
 
#ifndef motor_h
#define motor_h

#include "Arduino.h"

// required adafruit motor shield libraries
// need to obtain library from https://github.com/adafruit/Adafruit_Motor_Shield_V2_Library
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_PWMServoDriver.h"

class Motor{
  public:
    Motor(int dc_pin_1, int dc_pin_2);
    void drive(int spd, int dir);
    void init();
    int spd();
    int dir();
    void pivot();
  private:
    int dc_pin_1;
    int dc_pin_2;
    int current_speed;
    int current_dir;
    Adafruit_MotorShield afms;
    Adafruit_DCMotor *dc_motor_1;
    Adafruit_DCMotor *dc_motor_2;
};

#endif

