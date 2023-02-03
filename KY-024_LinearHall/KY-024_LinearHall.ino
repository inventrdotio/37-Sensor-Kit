/*
          .————————————.
| Linear (analog) hall effect switch |
| –                                - |
| – ANALOG pin returns strength &.   |
| – polarity of the magnetic field   |
| – DIGITAL pin returns only the     |
| – magnetic polarity of the field   |
| – You MUST set the pinMode of BOTH |
| – the analog and digital pins,     |
| – Otherwise dig_val is ALWAYS == 0 |
           :————————————:
Comments by biTToe:

Many laptops use the hall effect switch to determine the position of the lid (open or closed) It is more reliable than a mechanical switch.

The cool thing about this switch is that it has two sensors.
The analog sensor returns both field strength and polarity
The digital sensor returns only polarity.

With no magnet nearby:
the analog value is ~512 | range 0 – 1023 ideally
The digital value is 0 (LOW)

For the FRONT side of the sensor:
As the north pole of a magnet approaches the FRONT side of the sensor, the analog output value INCREASES (>512) and the digital output is LOW.

As the south pole of a magnet approaches the FRONT side of the sensor, the analog output value DECREASES (<512) and the digital output is HIGH.

For the BACK side of the sensor it is just the opposite.

Get a magnet and play around.
Here is my code with better variable names and better comments IMHO
*/

int led = 13;        // onboard led
int digitalPin = 3;  // digital sensor
int analogPin = A0;  // analog sensor
int dig_val;
int ana_val;

void setup() {
  Serial.begin(9600);
  pinMode(led, OUTPUT);        // define led as output interface
  pinMode(digitalPin, INPUT);  // define digital pin as input
  pinMode(analogPin, INPUT);   // define analog pin as input
}
void loop() {
  dig_val = digitalRead(digitalPin);  // Get digital value
  ana_val = analogRead(analogPin);    // Get analog value
  if (dig_val == HIGH)                // (S) on FRONT or (N) on BACK of sensor
  {
    digitalWrite(led, HIGH);
  } else  // (N) on the BACK or (S) on the FRONT of sensor
  {
    digitalWrite(led, LOW);
  }
  Serial.print("Digital Value: ");
  Serial.println(dig_val);
  Serial.print("Analog value: ");
  Serial.println(ana_val);
  Serial.print("\n\n");
  delay(1000);
}