 /*
 * inventr.io 37 in 1 Sensor Kit (https://inventr.io/product/37-in-1-sensor-kit/)
 * Sensor Course (https://inventr.io/course/sensor-training/)
 *
 * Code contributions:
 *    David Schmidt (davids@inventr.io)
 *    biTToe        (bittoe@yahoo.com)
 * Lesson - [KY-34] 7 ColorFlashing LED
 *
 * KY-034 is a module that includes a 7-color flashing LED. The LED can emit multiple 
 * colors: red, green, blue (RGB), cyan, magenta, yellow (CMY), and white. When powered on, 
 * the module will cycle through the seven colors in an unalterable, preset pattern.
 *
 * It is important to note that the specific details of how to use the KY-034 module
 * may vary depending on the specific manufacturer and version of the module;
 * therefore, it is recommended to consult the manufacturer's documentation or datasheet
 * for more detailed instructions.
 *
 * N.B.
 * There are at least TWO DIFFERENT KY-034 MODULES supplied in these kits: 
 * One module is labeled CNT5 and the other is labeled HW-481
 * Both modules have three pins
 * Both modules have four solder connections directly above the three pins
 * Both modules have one square solder-point (right-most) preceeded by three round solder-points
 *
 * The CNT5 module has the letter 'S' next to the leftmost pin indicating the +5v (Signal) pin.
 * The center pin is the ground and the rightmost pin is unused.
 *
 * The HW-481 module has a plus '+' next to the leftmost pin indicating the +5v (Signal) pin.
 * BOTH the center and the rightmost pin can be used as a ground with this module.
 *
 * This project uses:
 * One signal pin (S) or (+) depending on the module
 * The onboard LED
 * On the Hero (Arduino Uno compatible) we *could* use: D0-D13, A0-A5.
 * Skip: A0-A5 (can use for any ANALOG pin),
 *       D0/D1 (used by USB),
 *       D2/D3 (save for interrupts),
 *       D13 (used by LED_BUILTIN and SPI Clock),
 *       D5, D6, D9, D10 and D11 (save for PWM)
 *       D11 (SPI MOSI)
 *       D12 (SPI MISO)
 * Recommended for fewest conflicts:
 *    Digital pin: D4, D7, D8 or D13.
 *    Digital pin D13 is a good choice here because:
 *    The onboard LED should mimic the state of KY-034 (i.e., both on or both off).
 *    If they are not in the same state when the sketch is running, it will be easier
 *    to distinguish between bad programming, bad wiring, or a bad KY-034 module because
 *    they are both being driven by the same output pin.
 */

const uint8_t KY_034_FLASH_LED = 13;  // Set output to pin 13

void setup() {
  pinMode(KY_034_FLASH_LED, OUTPUT);  // Initialize Output pin for the LED
  digitalWrite(KY_034_FLASH_LED, LOW);// LED off
}

void loop() {
  digitalWrite(KY_034_FLASH_LED, HIGH);  // LED  is switched on
  // The KY-034 will continuously flash and repeat its set pattern until it is turned off
  // The Onboard LED will be HIGH while KY_034_FLASH_LED is HIGH
}