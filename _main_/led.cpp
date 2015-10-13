#include <Adafruit_MotorShield.h>

#include <Adafruit_NeoPixel.h>



#include "Arduino.h"
#include "led.h"

#include <Adafruit_NeoPixel.h>


#define NUMPIXELS 16

// constructor
Led::Led(int data_pin) {
  pin = data_pin;
  pixels = Adafruit_NeoPixel(NUMPIXELS, pin, NEO_GRB + NEO_KHZ800);
  pixels.begin();
  pixels.setBrightness(255);
}

void Led::setAll(int onOff,int rgb[]){
    for(int i=0;i<NUMPIXELS;i++){
      if(onOff) pixels.setPixelColor(i, pixels.Color(rgb[0],rgb[1],rgb[2]));
      else pixels.setPixelColor(i, pixels.Color(0,0,0));
      pixels.show();
    }
}


void Led::setLed(int led_1_to_16, int onOff, int rgb[]){
    if(onOff) pixels.setPixelColor( led_1_to_16, pixels.Color(rgb[0],rgb[1],rgb[2]));
    else pixels.setPixelColor(led_1_to_16, pixels.Color(0,0,0));
    pixels.show();
  
}

void Led::setRange(int led_1_to_16_start, int led_1_to_16_end, int onOff, int rgb[]){
    for(int i=led_1_to_16_start;i<=led_1_to_16_end;i++){
      if(onOff) pixels.setPixelColor(i, pixels.Color(rgb[0],rgb[1],rgb[2]));
      else pixels.setPixelColor(i, pixels.Color(0,0,0));
      pixels.show();
    }

  
}
  



