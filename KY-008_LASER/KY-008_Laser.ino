/*
 * inventr.io 37 in 1 Sensor Kit (https://inventr.io/product/37-in-1-sensor-kit/)
 * Sensor Course (https://inventr.io/course/sensor-training/)
 *
 * Lesson - [KY-008] LASER
 *
 * The KY-008 is a laser transmitter module commonly used in DIY electronics
 * projects such as robots or home automation systems. It operates at a
 * wavelength of 650 nm and produces a red laser beam that can be used as a
 * sensor or an indicator. The module can be easily connected to a microcontroller,
 * such as an Arduino, and controlled with a few lines of code.
 *
 * Code contributions:
 *    David Schmidt (davids@inventr.io)
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
const int KY_008_PIN = 4;

void setup() {
  pinMode(KY_008_PIN, OUTPUT);  // define the digital output interface 13 feet
}

void loop() {
  digitalWrite(KY_008_PIN, HIGH);  // turn on LASER
  delay(1000);                     // delay one second
  digitalWrite(KY_008_PIN, LOW);   // turn off LASER
  delay(1000);                     // delay one second
}