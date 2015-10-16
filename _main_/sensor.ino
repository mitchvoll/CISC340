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

