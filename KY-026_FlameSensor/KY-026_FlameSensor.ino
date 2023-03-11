/*
 * inventr.io 37 in 1 Sensor Kit (https://inventr.io/product/37-in-1-sensor-kit/)
 * Sensor Course (https://inventr.io/course/sensor-training/)
 *
 * Code contributions:
 *    David Schmidt (davids@inventr.io)
 *    biTToe        (bittoe@yahoo.com)
 * Lesson - [KY-026] Flame sensor
 *
 * The KY-026 Flame Sensor Module is a small electronic device that can detect flames
 * or fire in the vicinity. It is a type of infrared sensor that works by detecting
 * the infrared radiation emitted by flames.
 *
 * This is basically an infrared sensor and while it is probably not the best solution
 * for detecting an actual fire, it might be used to detect a pilot light or a
 * flame-activated switch.
 *
 * For me, this sensor was significantly more sensitive than I had anticipated. 
 * Initially I placed my candle at 10" (25cm) in a brightly lit room. 
 * The digital output was 1 and the analog output was 32. I could not reduce
 * The sensitivity of the sensor with the potentiometer. As I moved the candle 
 * farther away the analog value began to climb and at about 3ft. (1m) I was able
 * to calibrate the trigger point easily; however, if the flame was closer than
 *  about 18" (500cm) the sensor became overloaded: the digital output was 1 and 
 * the analog output bottomed-out in the 30s. This made calibration impossible.
 *
 * The safety police will tell you: The KY-026 flame detector module is not suitable
 * for use in industrial or critical applications. It is designed for educational
 * and hobbyist purposes only: YMMV
 *
 *+-+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
 *|          CALIBRATION
 *| The KY-026 is an adjustable sensor. This means you can
 *| adjust the sensitivity of the sensor to match the
 *| strength or intensity of your flame.
 *|
 *| To calibrate this sensor, un-comment the Serial.print
 *| lines at the end of the sketch and run.
 *| With NO FLAME present the output should read:
 *| Digital Value: 0 | Analog Value: ~1023
 *|
 *| Place a lit candle ~3ft (1m) from the sensor. The Analog Value
 *| should now be LESS THAN 1023. If the value is GREATER
 *| than ~510, the Digital Value will still be 0.
 *|
 *| Set the trigger point by adjusting the small screw on
 *| the blue potentiometer; this will change the analog
 *| output (sensitivity): Clockwise DECREASES Analog Value,
 *| Counterclockwise INCREASES Analog Value. When the
 *| Analog Value is LESS than about 510 the Digital
 *| Value should change from 0 to 1. 
 *|
 *| To fine tune the sensitivity, observe LED2 on the sensor.
 *| When LED2 is ON you have crossed the threshold. Adjust
 *| the potentiometer so your trigger-point is consistent
 *| and reliable.
 *+-+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
 *
 ** N.B.
 *
 * You can use HIGH, 1, true interchangeably
 * You can use LOW, 0, false interchangeably
 * but you should be consistent
 *
 * There are seven sensors in this kit that have
 * a red PCB and a blue potentiometer
 * KY-024 LinearHall  | KY-036 TouchSensor
 * KY-025 ReedSwitch  | KY-037 BigSoundSensor
 * KY-026 FlameSensor | KY-038 SmallSoundSensor
 *
 * They all function in exactly the same way and use exactly the same code,
 * albeit with different variable names.
 *
 * Each sensor is equipped with:
 * two output pins: digital (DO) and analog (AO).
 * Two on-board LEDs: Power (LED1) & Threshold (LED2)

 * When the intensity of the signal is GREATER than the set threshold:
 * DO == 1, AO < ~500, LED2 is ON
 
 * When the intensity of the signal is LESS than the set threshold:
 * DO == 0, AO > ~500, LED2 is OFF
 
 * The analog pin output (AO) is a range from 0 to 1023
 * The digital pin output (DO) is either 0 or 1
 * These are sensors that detects a physical signal: noise, heat, magnetic field... etc
 * Each sensor has a limited range of detection. 
 *
 * ** THE STRONGER THE SIGNAL, THE LOWER THE Analog Value -Closer to 0 **
 * ** THE WEAKER THE SIGNAL, THE HIGHER THE Analog Value -Closer to 1024 **
 * ** (AO) LESS THAN ~512 triggers (DO) to 1
 * ** (AO) GREATER than ~512 triggers (DO) to 0
 *
 * These sensors are not calibrated in any meaningful  way.
 * They are detectors as opposed to calibrated sensors; their outputs are not meant to
 * be converted to functional units (dB, degrees, lumens, Teslas... etc)
 *
 * This project uses:
 * One Digital pin to OUTPUT (HIGH or LOW)
 * One Analog pin to OUTPUT (Magnetic field strength & polarity)
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
 *    Digital pin: D4, D7 or D8
 *    Analog pin:  A0-A5
 */

const uint8_t KY_026_DIGITAL_IN = 8;  // digital sensor
const uint8_t KY_026_ANALOG_IN = A0;  // analog sensor

void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);      // define LED_BUILTIN as output interface
  pinMode(KY_026_DIGITAL_IN, INPUT); // define digital pin as input interface
  pinMode(KY_026_ANALOG_IN, INPUT);  // define analog pin as input interface
}

void loop() {
  int ky026_Dval = digitalRead(KY_026_DIGITAL_IN); // Reads digital value
  int ky026_Aval = analogRead(KY_026_ANALOG_IN);   // Reads analog value

  if (ky026_Dval == HIGH) // Flame detected
    digitalWrite(LED_BUILTIN, HIGH);
  else                    // No Flame detected
    digitalWrite(LED_BUILTIN, LOW);
  delay(150);             // change this value to pole the sensor more or less often

  /*
   * To see what the sensor is writing to the Hero board
   * Uncomment the Serial.print lines below
   * This information is also useful during calibration
   */
  // Serial.print("Digital Value: ");
  // Serial.print(ky026_Dval);
  // Serial.print(" | ");
  // Serial.print("Analog value: ");
  // Serial.println(ky026_Aval);
}