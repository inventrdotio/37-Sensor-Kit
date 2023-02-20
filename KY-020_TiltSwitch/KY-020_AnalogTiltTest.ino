const uint8_t tilt_pin = A0;

void setup() {
  Serial.begin(115200);
  pinMode(tilt_pin, INPUT);
}

void loop() {
  int val = analogRead(tilt_pin);
  Serial.println(val);
  delay(100);
}
