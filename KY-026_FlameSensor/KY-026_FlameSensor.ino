/*
    Comments from biTTOE

    This is basically an infrared sensor (a flame is an IR source).

    While this is probably not the best solution for detecting a fire, it could be used to detect a pilot light or an overheating component.

    Just like the Reed Switch and the Linear Hall Switch, this switch has both an DIGITAL and an ANALOG output

    The digital value is HIGH if IR is detected and LOW if not.

    The analog output is 1023 in total darkness and somewhat lower when other lights are present. The analog value DECREASES with the intensity if the IR source.

    You can also trigger this sensor with the same IR remote you used in the IR remote sensor project.
 */

int led = 13;        // define the LED pin
int digitalPin = 2;  // KY-026 digital interface
int analogPin = A0;  // KY-026 analog interface
int digitalVal;      // digital readings
int analogVal;       //analog readings

void setup() {
  pinMode(led, OUTPUT);
  pinMode(digitalPin, INPUT);
  //pinMode(analogPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // Read the digital interface
  digitalVal = digitalRead(digitalPin);
  if (digitalVal == HIGH)  // if flame is detected
  {
    digitalWrite(led, HIGH);  // turn ON Arduino's LED
  } else {
    digitalWrite(led, LOW);  // turn OFF Arduino's LED
  }

  // Read the analog interface
  analogVal = analogRead(analogPin);
  Serial.println(analogVal);  // print analog value to serial

  delay(100);
}