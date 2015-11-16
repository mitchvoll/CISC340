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
Motor wheels(1, 2); // declare motor object

long previousTime = millis();
int currentLedLit = 0;
int green[3] = {0, 200, 0};
int lightInterrupted = 0;

// verify obstacles
int obs_detected = 2;


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
  wheels.drive(100, 0);

}

void loop() {
  long currentTime = millis();
  if (lightInterrupted == 0) {
    led.setAll(0, green);
    led.setLed(currentLedLit, 1, green);
    currentLedLit += 1;
    if (currentLedLit >= 16) currentLedLit = 0;
  }
  previousTime = millis();

  //  get distances from rangefinders
  long cmCenter = sensorCenter();
  long cmLeft = sensorLeft();
  long cmRight = sensorRight();
  Serial.println("left: " + String(cmLeft));
  Serial.println("right: " + String(cmRight));
  Serial.println("center: " + String(cmCenter));
  Serial.println("obs: " + String(obs_detected));

  if ((cmLeft < 15 && cmRight < 15) || cmCenter < 15) {
    obs_detected >= 1 ? pivot(), obs_detected = 0 : obs_detected++;
  }

  else if ((cmCenter < 25) || (cmLeft < 25) || (cmRight < 25)) { // less than 30cm from wall
    if (cmRight > cmLeft) { // more space on the right
      obs_detected >= 2 ? turnRight(), obs_detected = 0 : obs_detected++;
    }
    else { // more space of the left
      obs_detected >= 2 ? turnLeft(), obs_detected = 0 : obs_detected++;
    }
  }

  else { // further than 30cm from wall
    obs_detected = 0;
    lightInterrupted = 0;
    forward();
  }
} // end loop

void forward() {
  // move in a straight line
  wheels.drive(100, 0);
  lightInterrupted = 0;
}

void turnRight() {
  // turn 20 degrees to the right
  wheels.drive(120, 30);

  //  lights
  lightInterrupted = 1;
  int color[3] = {228, 255, 46};
  led.setAll(0, color);
  led.setRange(0, 5, 1, color);
  led.setRange(14, 15, 1, color);

}

void turnLeft() {
  // turn 20 degrees to the left
  wheels.drive(100, 330);

  //  lights
  lightInterrupted = 1;
  int color[3] = {228, 255, 46};
  led.setAll(0, color);
  led.setRange(6, 13, 1, color);

}

void pivot() {
  // turn 180 degrees and continue driving
  wheels.pivot();

  //  lights
  lightInterrupted = 1;
  int color[3] = {0, 100, 200};
  led.setAll(0, color);
  led.setRange(9, 13, 1, color);
  led.setRange(14, 15, 1, color);
  led.setRange(0, 1, 1, color);
}
