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
  
long previousTime = millis();
int currentLedLit = 0; 
int green[3] = {0,200,0};
int lightInterrupted = 0;


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

  long currentTime = millis();
  if(lightInterrupted == 0){
    led.setAll(0,green);
    led.setLed(currentLedLit, 1, green);
    currentLedLit+=1;
    if(currentLedLit >=16) currentLedLit = 0;
  }
  previousTime = millis();
  
  long cmCenter = sensorCenter();
  long cmLeft = sensorLeft();
  long cmRight = sensorRight();

  if ((cmCenter < 30) || (cmLeft < 30) || (cmRight < 30)) { // less than 30cm from wall
    if ((cmCenter < 15) || (cmLeft < 15) || (cmRight < 15))
      wheels.pivot();
    else if (cmRight > cmLeft) { // more space on the right
      lightRight();
      turnRight();
    }
    else { // more space of the left
      lightLeft();
      turnLeft();
    }  
  } 
  else if ((cmCenter < 100) || (cmLeft < 100) || (cmRight < 100)) { // less than 30cm from wall
    lightWall(cmCenter, cmLeft, cmRight);
    forward();
  }
  else { // further than 30cm from wall
    lightInterrupted = 0;
    forward();
  }
} // end loop

void forward() { // move in a straight line
  lightInterrupted = 0;
  wheels.drive(100, 0);
  
} // end forward

void turnRight() { // turn slightly to the right
  wheels.drive(100,30);
} // end trunRight

void turnLeft() { // turn slightly to the left
  wheels.drive(100,330);
} // end turnLeft

void lightWall(long cmCenter, long cmLeft, long cmRight) { // light when wall is too near
  
  lightInterrupted = 1;
  int color[3]={200,0,0};
  led.setAll(0,color);
  led.setAll(1,color);
  
  int color1[3] = {255 - int(cmRight)*9, 75,0};
  int color2[3] = {255 - int(cmCenter)*9, 75,0};
  int color3[3] = {255 - int(cmLeft)*9, 75,0};
  
  led.setRange(2,4,1, color1);
  led.setRange(5,7,1, color2);
  led.setRange(8,9,1, color3);
} // end lightWall

void lightPivot(){
  lightInterrupted = 1;
  int color[3]={0,200,0};
  led.setAll(0,color);
  led.setRange(9,13,1,color);
  led.setRange(14,15,1,color);
  led.setRange(0,1,1,color);
}
void lightLeft() { // light for turning left
  lightInterrupted = 1;
  int color[3]={228,255,46};
  led.setAll(0,color);
  led.setRange(6,13,1,color);
} // end lightLeft

void lightRight() { // light for truring right
  lightInterrupted = 1;
  int color[3]={228,255,46};
  led.setAll(0,color);
  led.setRange(0,5,1,color);
  led.setRange(14,15,1,color);
// 
} // end lightRight




