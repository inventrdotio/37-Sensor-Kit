/*
.————————————-.
| Digital Temp Switch
|
| Digital and analog outputs:
| + dig_val: 0/1 TRUE/FALSE HIGH/LOW
| –HIGH when ana_val ~510
|
| + ana_val : 0 – 1023
| –Decreases as temp increases
| –set trigger point w/ potentiometer
|
| – You MUST set the pinMode of BOTH
| – the analog and digital pins,
| – Otherwise dig_val is ALWAYS == 0
:————————————-:

  Comments by biTTOE:
  This is a sensor-switch.
  It is not really set up to be used as a thermometer. It’s really more like a thermostat

  Like all of the sensors in this kit with a red PCB and a blue potentiometer, it has TWO outputs: one analog, one digital.

  The digital output has two possible states: 1 or 0 (TRUE/FALSE, HIGH/LOW)
  The analog output has a value between 0 & 1023, and a *SWITCHING POINT* for the digital switch between 510 & 511.

  SO:
  As temperature INCREASES, the output value of the analog sensor DECREASES.
  When the analog output is 510 or LESS, the digital value is HIGH.
  When the analog output is 511 or GREATER the digital value is LOW.

  What can we do with this?

  Let’s say you have a computer case that you don’t want the temperature to go above 90deg F.
  All you have to do is CALIBRATE the sensor by placing it in a “box” where the temperature is a stable 90deg F. Then dial
  the potentiometer until the analog output reads between 510-511. This is your *SWITCHING POINT*

  When the sensor returns to regular ambient temperatures (as long as it’s cooler than 90deg F) the analog output will be
  greater than 511, perhaps greater than 600 or more.

  Install the sensor in the computer case and run the computer. As the temperature in the case increases the analog output
  value will decrease. When that value is 510 or less then the digital output will change from 0 (LOW) to 1 (HIGH).

  You could use this change to trigger a fan or some other cooling device to reduce the temperature in the case.

  All the red PCB sensors in this kit work in this same way for whatever it is they are designed to detect.

  You could use the reed switch to set some acceptable lever of magnetic field and have it trigger when the field exceeds
  a defined magnitude, setting it up in the same manner as the temp sensor:

  CALIBRATE the sensor, using the potentiometer, in a magnetic field that is at the threshold of unacceptable, then install
  the sensor where you need it. If the magnetic field strength increases to the point where the analog output becomes less
  than 510, the digital output will go to HIGH and you can use that to trigger a secondary event or alarm.
*/

int led = 13;        // onboard led
int digitalPin = 3;  // digital sensor
int analogPin = A0;  // analog sensor
int dig_val;
int ana_val = 0;

void setup() {
  Serial.begin(9600);
  pinMode(led, OUTPUT);        // define led as output interface
  pinMode(digitalPin, INPUT);  // define digital pin as input
  pinMode(analogPin, INPUT);   // define analog pin as input
}

void loop() {
  dig_val = digitalRead(digitalPin);  // Get digital value
  ana_val = analogRead(analogPin);    // Get analog value
  if (dig_val == HIGH)                // * ANAout val 510 temp decrease
    digitalWrite(led, HIGH);
  else
    digitalWrite(led, LOW);

  Serial.print("Digital Value: ");
  Serial.println(dig_val);
  Serial.print("Analog value: ");
  Serial.println(ana_val, DEC);
  Serial.print("\n\n");
  delay(1000);
}