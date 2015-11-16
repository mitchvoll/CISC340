# CISC340_PROJECT_2

# CISC340_PROJECT_1
All project files are in */\_main\_*. The file *\_main\_.ino* is the main program that contains the navigation logic and component usage logic. The other files are for component functions so we can avoid lots of merge conflicts from working on the same file. 

The entire folder compiles so that functions written in each file are usable in *\_main\_.ino* so you should be able to build your function and test it from the _main_ file. If you have access to an Arduino let me know if you get output in the serial monitor with the current config, I don't have my Arduino so I couldn't test it.

## Libraries and Classes
- Also if you want to write your module as a library or class instead to allow the main program to use your module as an object. You can just remove your .ino file and include a .cpp and .h file instead. 
- Good tutorial https://www.arduino.cc/en/Hacking/LibraryTutorial 

## Including Libraries
- Most of our modules will need Adafruit libraries to use and the Arduino IDE build system doesn't allow you to include a library from the same directory as your project. So we'll each have to install all required libraries through the Arduino IDE, so I guess maybe we should keep a list of what libraries we're using and where to get them.
- Good tutorial for installing libraries as .zip - https://www.arduino.cc/en/Guide/Libraries

  - motor
    - Adafruit motor shield - https://github.com/ladyada/Adafruit_Motor_Shield_V2_Library/archive/master.zip 
  - led
    - Adafruit NeoPixel - https://github.com/adafruit/Adafruit_NeoPixel/archive/master.zip
  - sensor
  - communication


## Current project directory
- /\_main\_
  - \_main\_.ino
  - motor.cpp
  - motor.h
  - led.ino
  - sensor.ino
  - communication.ino
