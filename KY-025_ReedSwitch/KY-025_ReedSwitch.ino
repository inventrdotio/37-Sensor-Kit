/*
 * inventr.io 37 in 1 Sensor Kit (https://inventr.io/product/37-in-1-sensor-kit/)
 * Sensor Course (https://inventr.io/course/sensor-training/)
 *
 * Code contributions:
 *    David Schmidt (davids@inventr.io)
 *    biTToe        (bittoe@yahoo.com)
 * Lesson - [KY-025] Reed Switch
 *
 * The KY-025 is a compact, low-cost magnetic reed switch module that can be used with Arduino
 * and Raspberry Pi. The reed switch is a type of sensor that can detect the presence of a
 * magnetic field. It consists of two ferromagnetic reeds that are sealed in a glass tube.
 *
 * When a magnetic field is applied to the reed switch, the reeds become magnetized and
 * attract each other, closing the switch. When the magnetic field is removed, the reeds
 * lose their magnetization and return to their original position, opening the switch.
 * This makes the reed switch useful for detecting the position of a door or window,
 * the presence of a magnetic field in a motor, or the rotation of a wheel.
 *
 *+-+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
 *|          CALIBRATION
 *| The KY-25 is an all-or-nothing sensor.
 *| This means that the presence of any magnetic field
 *| can produce a change in the Analog Value.
 *|
 *| To calibrate this sensor, un-comment the Serial.print
 *| lines at the end of the sketch and run.
 *| With NO MAGNET present the output should read:
 *| Digital Value: 0 | Analog Value: 1023
 *|
 *| Place a magnet at the desired distance. The Analog Value
 *| should now be LESS THAN 1023. If the value is GREATER
 *| than ~510, the Digital Value will still be 0.
 *|
 *| Set the trigger point by adjusting the small screw on
 *| the blue potentiometer; this will change the analog
 *| output: Clockwise DECREASES Analog Value,
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
 * You can use HIGH, 1, true interchangably
 * You can use LOW, 0, false interchangably
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
 * These sensors are not calibrated in any meaningfuly way.
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

const uint8_t KY_025_DIGITAL_IN = 8;  // digital sensor
const uint8_t KY_025_ANALOG_IN = A0;  // analog sensor

void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);      // define LED_BUILTIN as output interface
  pinMode(KY_025_DIGITAL_IN, INPUT); // define digital pin as input interface
  pinMode(KY_025_ANALOG_IN, INPUT);  // define analog pin as input interface
}

void loop() {
  int ky025_Dval = digitalRead(KY_025_DIGITAL_IN); // Reads digital value
  int ky025_Aval = analogRead(KY_025_ANALOG_IN);   // Reads analog value

  if (ky025_Dval == HIGH) // Magnetic field detected
    digitalWrite(LED_BUILTIN, HIGH);
  else                    // No Magnetic field detected
    digitalWrite(LED_BUILTIN, LOW);
  delay(150);             // change this value to pole the sensor more or less often

  /*
   * To see what the sensor is writing to the Hero board
   * Uncomment the Serial.print lines below
   * This information is also useful during calibration
   */
//   Serial.print("Digital Value: ");
//   Serial.print(ky025_Dval);
//   Serial.print(" | ");
//   Serial.print("Analog value: ");
//   Serial.println(ky025_Aval);
}