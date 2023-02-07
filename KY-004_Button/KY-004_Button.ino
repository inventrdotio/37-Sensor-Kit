/*
 * inventr.io 37 in 1 Sensor Kit (https://inventr.io/product/37-in-1-sensor-kit/)
 * Sensor Course (https://inventr.io/course/sensor-training/)
 *
 * Lesson - [KY-003] Hall Magnetic Sensor
 *
 * The KY-004 is a simple tactile button module for use with Arduino or other
 * microcontrollers. It consists of a push button switch and a resistor to pull
 * the input high when the button is not pressed. When the button is pressed,
 * the input is connected to ground, providing a low signal to the microcontroller.
 * The module provides a convenient and compact way to add a physical button input
 * to a microcontroller project.
 *
 * KY-004 sensor pin is HIGH until the button is pressed and then sensor pin goes LOW.
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
const int KY_004_PIN = 4;  // the number of the pushbutton pin

int buttonState = 0;  // variable for reading the pushbutton status

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);  // built in LED is an OUTPUT
  pinMode(KY_004_PIN, INPUT_PULLUP);    // Button is an input
}

void loop() {
  // read the state of the pushbutton value:
  buttonState = digitalRead(KY_004_PIN);

  if (digitalRead(KY_004_PIN) == LOW)        // if button is pressed, state is LOW (false)
    digitalWrite(LED_BUILTIN, HIGH);  // turn on built in LED
  else
    digitalWrite(LED_BUILTIN, LOW);  // turn off built in LED
}
