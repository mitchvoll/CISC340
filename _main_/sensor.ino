//Constant to store the digital pin to read pulse from
//This value will not change
const int pulsePin = 2; // attach pin 2 on the arduino to pin 2 on the sensor; don't attach anything to pin 4 on the sensor

// below is for the other 2 sensors
// pins to receive echo pulse
#define ECHOPIN_L 2
#define ECHOPIN_R 2

// pins to send trigger pulse
#define TRIGPIN_L 3
#define TRIGPIN_R 3

void setup() {
  //Opening the serial connection 
  Serial.begin(9600);

  // setup the other two sensors, designating input and output
  pinMode(ECHOPIN_L, INPUT);
  pinMode(TRIGPIN_L, OUTPUT);
  pinMode(ECHOPIN_R, INPUT);
  pinMode(TRIGPIN_R, OUTPUT);
}

// maxbotix ultrasonic sensor
long sensorCenter() {
  long pulse;
  long center; // in cm

   pinMode(pulsePin, INPUT);

   // used to read in the pulse that is being sent by the MaxSonar device.
   // pulse Width representation with a scale factor of 147 uS per Inch.
   // determine pulswidth with time; returning an amount of time (which represents pulse width) in microseconds
  pulse = pulseIn(pulsePin, HIGH); 
  center = (pulse/147) * 2.54;

  return center;
}

// SRF05 ultrasonic sensor
long sensorLeft() {
  long pulse;
  long left; // in cm

   // trigger the sensor
   digitalWrite(TRIGPIN_L, HIGH);
   delayMicroseconds(10);
   digitalWrite(TRIGPIN_L, LOW);

   // read in pulse
   pulse = pulseIn(ECHOPIN_L, HIGH);
   left = pulse/58; // conversion to cm

   return left; 
}

// SRF05 ultrasonic sensor
long sensorRight() {
  long pulse;
  long right; // in cm
  
   // trigger the sensor
   digitalWrite(TRIGPIN_R, HIGH);
   delayMicroseconds(10);
   digitalWrite(TRIGPIN_R, LOW);

   // read in pulse
   pulse = pulseIn(ECHOPIN_R, HIGH);
   right = pulse/58; // conversion to cm

   return right;
}

