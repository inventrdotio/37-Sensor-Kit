//KY018 Photo resistor module

uint8_t sensorPin = A0;   // select the input pin for the potentiometer
int ledPin = 13;      // select the pin for the LED

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(115200);
}

void loop() {
  int sensorValue = analogRead(sensorPin);
  Serial.println(sensorValue);
  digitalWrite(ledPin, HIGH);
  delay(sensorValue);
  digitalWrite(ledPin, LOW);
  delay(sensorValue);
}