
 
#ifndef led_h
#define led_h

#include "Arduino.h"

#include <Adafruit_NeoPixel.h>

class Led{
  public:
    Led(int pin);
    void setAll(int onOff,int rgb[]);
    void setLed(int led_1_to_16, int onOff, int rgb[]);
    void setRange(int led_1_to_16_start, int led_1_to_16_end, int onOff, int rgb[]);
    
  private:
    int pin;
    Adafruit_NeoPixel pixels;


};

#endif

