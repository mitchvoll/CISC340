// Main logic and navigation program

// include motor file and dependencies
#include "motor.h"
#include "led.h"
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include <Adafruit_NeoPixel.h>

#define pulsePin 7 // attach pin 2 on the arduino to pin 2 on the sensor; don't attach anything to pin 4 on the sensor

// below is for the other 2 sensors
// pins to receive echo pulse
#define ECHOPIN_L 3
#define ECHOPIN_R 5

// pins to send trigger pulse
#define TRIGPIN_L 4
#define TRIGPIN_R 6

Led led(8);   // create led object and set input pin
Motor wheels(1,2); // declare motor object

void setup() {
  Serial.begin(9600);
  // Opening the serial connection 
  Serial.print("main.ino - setup()");

  // setup the other two sensors, designating input and output
  pinMode(ECHOPIN_L, INPUT);
  pinMode(TRIGPIN_L, OUTPUT);
  pinMode(ECHOPIN_R, INPUT);
  pinMode(TRIGPIN_R, OUTPUT);

  
  wheels.init(); // init Motor class
  wheels.drive(100,0);
  
}

void loop() {
   // put your main code here, to run repeatedly:

  long left = sensorLeft();
  long right = sensorRight();
  long center = sensorCenter();
  Serial.println("left: " + String(left));
  Serial.println("right: " + String(right));
  Serial.println("center: " + String(center));
  delay(500);
  
  long cmCenter = sensorCenter();
  long cmLeft = sensorLeft();
  long cmRight = sensorRight();

  if ((cmCenter < 20) || (cmLeft < 20) || (cmRight < 20)) { // less than 20cm from wall
    if (cmRight > cmLeft) { // more space on the right
      lightRight();
      turnRight();
    }
    else { // more space of the left
      lightLeft();
      turnLeft();
    }  
  } 
  else if ((cmCenter < 30) || (cmLeft < 30) || (cmRight < 30)) { // less than 30cm from wall
    lightWall();
  }
  else { // further than 30cm from wall
    lightNormal();
  }

  //testing led ring
  //int color[3]={100,255,100};
  //led.setAll(1,color);
  //delay(500);
  //led.setAll(0,color);
  //delay(500);
  //led.setAll(0,color);

} // end loop

void turnRight() { // turn slightly to the right
  wheels.drive(100,30);
} // end trunRight

void turnLeft() { // turn slightly to the left
  wheels.drive(100,330);
} // end turnLeft

void lightWall() { // light when wall is too near
 
} // end lightWall

void lightNormal() { // light for regular driving 
  
} //end lightNormal

void lightLeft() { // light for turning left
  
} // end lightLeft

void lightRight() { // light for truring right

 
} // end lightRight




