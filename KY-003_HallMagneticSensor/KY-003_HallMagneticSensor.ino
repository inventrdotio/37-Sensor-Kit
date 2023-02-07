/*
 * inventr.io 37 in 1 Sensor Kit (https://inventr.io/product/37-in-1-sensor-kit/)
 * Sensor Course (https://inventr.io/course/sensor-training/)
 *
 * Lesson - [KY-003] Hall Magnetic Sensor
 *
 * The KY-003 is a magnetic Hall-effect sensor. It can detect the presence of a magnetic
 * field and output an electrical signal proportional to the strength of the magnetic
 * field. The sensor operates by using the Hall effect, which is the production of a
 * voltage difference across an electrical conductor, transverse to an electric current
 * in the conductor and a magnetic field perpendicular to it. The KY-003 is typically
 * used in various applications such as detecting the position of a rotating magnet,
 * or as a switch triggered by a magnet.
 *
 * KY-003 sensor pin is HIGH until a magenetic field is detected, when sensor pin goes LOW.
 *
 * Code contributions by David Schmidt (davids@inventr.io)
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
const uint8_t KY_003_PIN = 10;  // define the Hall magnetic sensor interface

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);       // define LED as output interface
  pinMode(KY_003_PIN, INPUT_PULLUP);  // define the Hall magnetic sensor line as input
}

void loop() {
  if (digitalRead(KY_003_PIN) == LOW) {  // when the Hall sensor detects a magnetic field (LOW), Arduino LED lights up
    digitalWrite(LED_BUILTIN, HIGH);
  } else
    digitalWrite(LED_BUILTIN, LOW);
  delay(100);
}