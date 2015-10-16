// Main logic and navigation program

// include motor file and dependencies
#include "motor.h"
#include "led.h"
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include <Adafruit_NeoPixel.h>

Led led(6);   // create led object and set input pin

// sensor
//Constant to store the digital pin to read pulse from
//This value will not change
#define pulsePin 2 // attach pin 2 on the arduino to pin 2 on the sensor; don't attach anything to pin 4 on the sensor

// below is for the other 2 sensors
// pins to receive echo pulse
#define ECHOPIN_L 3
#define ECHOPIN_R 5

// pins to send trigger pulse
#define TRIGPIN_L 4
#define TRIGPIN_R 6
  
  

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.print("main.ino - setup()");

  //  sensor
  // Opening the serial connection 
  Serial.begin(9600);

  // setup the other two sensors, designating input and output
  pinMode(ECHOPIN_L, INPUT);
  pinMode(TRIGPIN_L, OUTPUT);
  pinMode(ECHOPIN_R, INPUT);
  pinMode(TRIGPIN_R, OUTPUT);

  //  motor
  motor wheels(1,2);
//  wheels.spin_move();
  wheels.drive(100,0);
  delay(3000);
  wheels.drive(0,0);
  delay(50);
  wheels.drive(50,180);
  
}

void loop() {
  // put your main code here, to run repeatedly:

  long test = sensorLeft();
  Serial.println("test: " + String(test));

  //testing led ring
  int color[3]={100,255,100};
  led.setAll(1,color);
  delay(500);
  led.setAll(0,color);
  delay(500);
  led.setAll(0,color);

}
