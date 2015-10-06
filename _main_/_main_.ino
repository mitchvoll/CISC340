// Main logic and navigation program

// include motor file and dependencies
#include "motor.h"
#include <Wire.h>
#include <Adafruit_MotorShield.h>

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.print("main.ino - setup()");
  
  //  Call functions from device files
  comm();
  led();
  sensor();

}

void loop() {
  // put your main code here, to run repeatedly:

}
