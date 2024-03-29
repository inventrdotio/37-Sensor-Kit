/*
 * inventr.io 37 in 1 Sensor Kit (https://inventr.io/product/37-in-1-sensor-kit/)
 * Sensor Course (https://inventr.io/course/sensor-training/)
 *
 * Code contributions by David Schmidt and Frank Visco.
 *
 * Lesson - [KY-032] Avoidance Tracking
 *
 *
 * KY-032 is an infrared (IR) obstacle avoidance sensor
 * The module consists of an IR transmitter and receiver that can detect
 * the presence of an object in front of the sensor by measuring the reflection
 * of the IR light. It has a functional range between 2cm and 40cm
 *
 * The sensor outputs a digital signal that can be read by a microcontroller
 * to determine the presence or absence of an obstacle. 
 *
 ** like many of the digital sensors in this kit
 ** The default state of this sensor is HIGH when it is idle
 ** When there is NOTHING detected the digital output will be HIGH, 
 ** which can also be represented as "true" or 1
 ** When the sensor detects an obstacle the digital output will be LOW, 
 ** which can also be represented by "false" or 0
 *
 * The KY-032 has one jumper (EN) and 4 pins: GND, +, out, EN.
 *
 * The KY-032 sensor can be enabled or disabled via hardware or software
 * With the EN jumper in place, the sensor will be in constant detection mode.
 *
 * If you remove the EN jumper you can enable and disable the sensor by sending
 * a HIGH (enable) or LOW (disable) signal to the EN pin
 * a HIGH signal will enable the sensor and a LOW signal will disable it.
 * 
 * Library requirements:
 * None
 *
 * Code contributions:
 *    David Schmidt (davids@inventr.io)
 *    biTToe (scy1961@yahoo.com)
 * 
 * .-------------------------------.
 * > Avoidance tracker Calibration <
 * :---------------------------------------------------------------------------------------:
 * | To get this to work you have to adjust both the output and input potentiometers (POTs).
 * |
 * | The POT on the right, which sits just below the EN jumper, adjusts the LED output.
 * | -Turn this clockwise (to the right) as far as it will go. 
 * |
 * | The POT on the left adjusts sensor sensitivity.
 * | -Turn this as far counterclockwise (to the left) as it will go.
 * | -Place your hand or some other flat object about 4″ (~10cm) above the sensor.
 * | -SLOWLY turn the POT clockwise (right) until the LED on the PCB comes on and the serial output says “obstacle in the way”
 * |
 * | There is a small range for detection but With a little finesse, gentle nudging, and tweaking
 * | of the POT you should be able to get a detection range between 0 and ~10″ (~25cm).
 * | You really have to play with the detection sensitivity to get it to work reliably and consistently
 * :---------------------------------------------------------------------------------------:
 *
 * This project uses: 
 * One Digital pin to INPUT (object detection).
 * One *optional* digital pin to OUTPUT (enable/disable sensor)
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
const uint8_t KY_032_SENSOR_PIN = 8;  // set sensor output to a digitial pin

// If you want the ability to enable and disable the sensor manually
// you must remove the EN jumper on the module and
// assign the EN pin to a digital pin:
//    const uint8_t KY_032_ENABLE_PIN = 5;
// Set the pin mode
//    pinMode(KY_032_ENABLE_PIN, OUTPUT);
// Enable the device by writing HIGH to KY_032_ENABLE_PIN
//    digitalWrite(KY_032_ENABLE_PIN, HIGH);

void setup() {
  Serial.begin(9600);
  pinMode(KY_032_SENSOR_PIN, INPUT);  // set pin as input
}

void loop() {

  if (digitalRead(KY_032_SENSOR_PIN) == LOW) {  // could also be written if(!digitalRead(KY_032_SENSOR_PIN))
    Serial.println("Obstacle in the way");
  } else {
    Serial.println("The path is clear");
  }
  delay(250);

  /* 
   *To see what the sensor is writing to the Hero board
   * Uncomment the two Serial.print lines below 
   * KY_032_SENSOR_PIN = 1 | No object detected
   * KY_032_SENSOR_PIN = 0 | Object detected
   * This information is also useful during calibration
  */

  // Serial.print("\nKY_032_SENSOR_PIN = "); // Print the digital output of the sensor for debugging purposes
  // Serial.println(digitalRead(KY_032_SENSOR_PIN));
}