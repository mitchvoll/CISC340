//CISC 340 Project 2

#include "pitches.h"

// Tie input variables to pins
const int top_input_pin = 0;
const int middle_input_pin = A0;
const int bottom_input_pin = A1;

// Tie output variables to pins
const int top_output_pin = 1;
const int middle_output_pin = 5;
const int bottom_output_pin  = 9;

int top_button = LOW;
int temp = 0;

// notes in the Jeopardy melody:
  int jeopardy[] = {
  NOTE_C4, NOTE_F4, NOTE_C4, NOTE_F3, NOTE_C4, NOTE_F4, NOTE_C4,
  NOTE_C4, NOTE_F4, NOTE_C4, NOTE_F4,
  NOTE_A4, NOTE_G4, NOTE_F4, NOTE_E4, NOTE_D4, NOTE_CS4,
  NOTE_C4, NOTE_F4, NOTE_C4, NOTE_F3, NOTE_C4, NOTE_F4, NOTE_C4,
  NOTE_F4, NOTE_D4, NOTE_C4, NOTE_AS3,
  NOTE_A3, NOTE_G3, NOTE_F3};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int jeopardyDurations[] = {
  4, 4, 4, 4, 4, 4, 2,
  4, 4, 4, 4,
  3, 8, 8, 8, 8, 8,
  4, 4, 4, 4, 4, 4, 2,
  3, 8, 4, 4,
  4, 4, 4 };



void setup() {
  // set pin each as input or output as appropriate 
   pinMode(top_input_pin, INPUT);
   pinMode(top_output_pin, OUTPUT);

   pinMode(middle_input_pin, INPUT);
   pinMode(middle_output_pin, OUTPUT);

   pinMode(bottom_input_pin, INPUT);
   pinMode(bottom_output_pin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
 

  //Get the temperature from the sensor
  temp = analogRead(bottom_input_pin);
  
  // Check to see if buttons been pressed
  top_button = digitalRead(top_input_pin);
  
      // When top_button is HIGH this means the button has been pressed
      if (top_button == HIGH) {
          //Send a max valued signal to the cloudbit
          analogWrite(bottom_output_pin, 255);

          //Play the jeopory notes
          play_jeopardyMelody();

        } 
        else {
          //Send the temperature value to the cloudbit
          analogWrite(bottom_output_pin, temp); 
        }
  
  } // end loop

   // Function for playing jeoparody notes
   void play_jeopardyMelody(){
    // iterate over the notes of the melody:
    for (int thisNote = 0; thisNote < (sizeof(jeopardyDurations)/2); thisNote++) {

      // to calculate the note duration, take one second 
      // divided by the note type.
      //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
      int jeopardyDuration = 1000/jeopardyDurations[thisNote];
      tone(middle_output_pin, jeopardy[thisNote], jeopardyDuration);
  
      // to distinguish the notes, set a minimum time between them.
      // the note's duration + 30% seems to work well:
      int pauseBetweenNotes = jeopardyDuration * 1.30;
      delay(pauseBetweenNotes);
      // stop the tone playing:
      noTone(middle_output_pin);
    }

  } // end play_jepordyMelody
