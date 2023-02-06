/*
 * inventr.io 37 in 1 Sensor Kit (https://inventr.io/product/37-in-1-sensor-kit/)
 * Sensor Course (https://inventr.io/course/sensor-training/)
 *
 * Lesson - [KY-002] Shock Sensor
 *
 * The KY-002 is a simple shock sensor module that detects vibrations or impacts.
 * or movements in a variety of applications, such as detecting doors opening and
 * closing or detecting knocks on a table.
 *
 * Code contributions by David Schmidt
 */

/* This project just needs a Digital pin.
 * On the Hero (Arduino Uno compatible) we *could* use: D0-D13, A0-A5.
 * Skip: A0-A5 (save for Analog),
 *       D0/D1 (used by USB),
 *       D2/D3 (save for interrupts),
 *       D13 (used by LED_BUILTIN and SPI Clock),
 *       D5, D6, D9, D10 and D11 (save for PWM)
 *       D11 (SPI MOSI)
 *       D12 (SPI MISO)
 * Recommended for fewest conflicts:
 *    D4, D7 or D8
 */
const uint8_t KY_002_PIN = 10;        // Good digital pin not used for other purposes

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);  // define LED as output interface
  pinMode(KY_002_PIN, INPUT);    // output interface defines vibration sensor
}

void loop() {
  int val = digitalRead(KY_002_PIN);  // read digital interface is assigned a value of 3 val
  if (val)                    // When the shock sensor detects a signal flash LED
    digitalWrite(LED_BUILTIN, HIGH);
  else
    digitalWrite(LED_BUILTIN, LOW);
}