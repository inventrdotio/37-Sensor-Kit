int Led = 3;

void setup() {
  pinMode(Led, OUTPUT);  // Initialization  Output spin for the LED
}

void loop()  //Main program loop
{
  digitalWrite(Led, HIGH);  // LED  is switched on
  delay(4000);              // Wait mode for 4 seconds
  digitalWrite(Led, LOW);   // LED  is switched off
  delay(2000);              // Wait mode for another two seconds in which the LED is switched off
}