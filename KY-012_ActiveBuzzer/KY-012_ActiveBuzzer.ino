//Example code KY012 active buzzer
int speakerPin = 8;

void setup() {
  pinMode(speakerPin, OUTPUT);
}

void loop() {
  analogWrite(speakerPin, 255);
  delay(500);
  analogWrite(speakerPin, 70);
  delay(100);
  analogWrite(speakerPin, 120);
  delay(500);
}