//Constant to store the digital pin to read pulse from
//This value will not change
const int pulsePin = 2; // attach pin 2 on the arduino to pin 2 on the sensor; don't attach anything to pin 4 on the sensor

// below is for the other 2 sensors
// pins to receive echo pulse
#define ECHOPIN_ONE 2
#define ECHOPIN_TWO 2

// pins to send trigger pulse
#define TRIGPIN_ONE 3
#define TRIGPIN_TWO 3

void setup() {
  //Opening the serial connection 
  Serial.begin(9600);

  // setup the other two sensors, designating input and output
  pinMode(ECHOPIN_ONE, INPUT);
  pinMode(TRIGPIN_ONE, OUTPUT);
  pinMode(ECHOPIN_TWO, INPUT);
  pinMode(TRIGPIN_TWO, OUTPUT);
}

void loop() {
  //variables needed to store values
  long cm;
  long pulse;
  long distanceOne;
  long distanceTwo;
  long dOne;
  long dTwo;
 
  pinMode(pulsePin, INPUT);
 // used to read in the pulse that is being sent by the MaxSonar device.
 // pulse Width representation with a scale factor of 147 uS per Inch.
 // determine pulswidth with time; returning an amount of time (which represents pulse width) in microseconds
  pulse = pulseIn(pulsePin, HIGH); 
  
  // set the trigger pins to low for 2uS
  digitalWrite(TRIGPIN_ONE, LOW);
  digitalWrite(TRIGPIN_TWO, LOW);
  delayMicroseconds(2);

  // send a 10uS high to trigger
  digitalWrite(TRIGPIN_ONE, HIGH);
  digitalWrite(TRIGPIN_TWO, HIGH);
  delayMicroseconds(10);
  
 // set trigger pins low again
  digitalWrite(TRIGPIN_ONE, LOW);
  digitalWrite(TRIGPIN_TWO, LOW);

  // read in pulses
  distanceOne = pulseIn(ECHOPIN_ONE, HIGH);
  distanceTwo = pulseIn(ECHOPIN_TWO, HIGH);

  // calculate distance from pulse time
  dOne = distanceOne/58; // in cm?
  dTwo = distanceTwo/58;
  
  //change inches to centimetres
  cm = (pulse/147) * 2.54;
  
  if (cm < 16 || dOne < 16 || dTwo < 16)// we can change this later, this is just an estimate; the sensor gets inaccurate less than 6 inches
    Serial.print("c"); // close 
  else if ((cm >= 16 && cm < 30) || (dOne >= 16 && dOne < 30) || (dTwo >= 16 && dTwo < 30) )
    Serial.print("m"); // medium distance
  else {
    Serial.print("f"); // far, default
  }  //return the distance
   delay(500); // in milli seconds - adjust
}

