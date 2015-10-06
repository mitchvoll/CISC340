// Main logic and navigation program

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.print("main.ino - setup()");
  
  //  Call functions from device files
  comm();
  led();
  motor;
  sensor;

}

void loop() {
  // put your main code here, to run repeatedly:

}
