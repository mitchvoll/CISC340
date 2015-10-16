// Main logic and navigation program

// include motor file and dependencies
#include "motor.h"
#include "led.h"
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include <Adafruit_NeoPixel.h>

Led led(6);   // create led object and set input pin
  
  

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.print("main.ino - setup()");

  motor wheels(1,2);
//  wheels.spin_move();
  
}

void loop() {
  // put your main code here, to run repeatedly:


  //testing led ring
  int color[3]={100,255,100};
  led.setAll(1,color);
  delay(500);
  led.setAll(0,color);
  delay(500);
  led.setAll(0,color);

}
