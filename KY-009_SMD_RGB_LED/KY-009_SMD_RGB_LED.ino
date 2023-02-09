/*
 * inventr.io 37 in 1 Sensor Kit (https://inventr.io/product/37-in-1-sensor-kit/)
 * Sensor Course (https://inventr.io/course/sensor-training/)
 *
 * Lesson - [KY-009] SMD RGB LED
 *
 * The KY-009 is a module that consists of an RGB (Red, Green, Blue) LED, which
 * can emit various colors by mixing the intensities of the three individual colors.
 * The module can be easily connected to a microcontroller like an Arduino, and is
 * commonly used for adding colorful lighting effects to DIY electronics projects
 * such as mood lights, ambilight systems, and more.
 *
 * We use PWM pins for this device so that we can independently set the intensity
 * of each LED.  You must use resistors between the board and the Arduino to prevent
 * LED burnout.
 *
 * NOTE: KY-009 in at least one kit had the colors on different pins than labled.  The
 *       pins on two tested modules were BRG-, not BGR- as labled (red and green swapped).
 *
 * Code contributions:
 *    David Schmidt (davids@inventr.io)
 */

/* This project needs three PWM Digital pins.
 * On the Hero (Arduino Uno compatible) we *could* use: D0-D13, A0-A5.
 * Skip: A0-A5 (save for Analog),
 *       D0/D1 (used by USB),
 *       D2/D3 (save for interrupts),
 *       D13 (used by LED_BUILTIN and SPI Clock),
 *       D5, D6, D9, D10 and D11 (save for PWM)
 *       D11 (SPI MOSI)
 *       D12 (SPI MISO)
 * Recommended for fewest conflicts:
 *    D5, D6 and D9
 */

const int KY_009_RED_PIN = 6;    // select the pin for the red LED
const int KY_009_GREEN_PIN = 5;  // select the pin for the blue LED
const int KY_009_BLUE_PIN = 9;    // select the pin for the green LED

void setup() {
  pinMode(KY_009_RED_PIN,   OUTPUT);
  pinMode(KY_009_GREEN_PIN, OUTPUT);
  pinMode(KY_009_BLUE_PIN,  OUTPUT);
}

void loop() {
  analogWrite(KY_009_RED_PIN, 255); // show red LED for one second
  delay(1000);

  analogWrite(KY_009_RED_PIN, 0);   // turn off red LED
  analogWrite(KY_009_GREEN_PIN, 255); // turn on green LED for one second
  delay(1000);

  analogWrite(KY_009_GREEN_PIN, 0);   // turn off green LED
  analogWrite(KY_009_BLUE_PIN, 255); // turn on blue LED for one second
  delay(1000);
  analogWrite(KY_009_BLUE_PIN, 0);

  // Now slowly modify all colors, giving a fade from color to color
  for (int i = 255; i > 0; i--) {
    analogWrite(KY_009_RED_PIN, i);
    analogWrite(KY_009_BLUE_PIN, 255 - i);
    analogWrite(KY_009_GREEN_PIN, 128 - i);
    delay(10);
  }

  for (int i = 0; i < 255; i++) {
    analogWrite(KY_009_RED_PIN, i);
    analogWrite(KY_009_BLUE_PIN, 255 - i);
    analogWrite(KY_009_GREEN_PIN, 128 - i);
    delay(10);
  }
  analogWrite(KY_009_GREEN_PIN, 0);   // turn off green LED
  analogWrite(KY_009_BLUE_PIN, 0);
}