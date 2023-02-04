// KY-013 Analog Temperature
// Neither module I had read anything but 0 until I reversed the pins.  Ground is signal and signal is on '-'!!!!

uint8_t sensorPin = A0;   // select the input pin for the potentiometer

void setup() {
  Serial.begin(9600);
  pinMode(sensorPin, INPUT);
}

void loop() {
  int sensorValue = analogRead(sensorPin);
  Serial.println(sensorValue);
  delay(250);
}