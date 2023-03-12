/*
 * inventr.io 37 in 1 Sensor Kit (https://inventr.io/product/37-in-1-sensor-kit/)
 * Sensor Course (https://inventr.io/course/sensor-training/)
 *
 * Code contributions:
 *    David Schmidt (davids@inventr.io)
 *    biTToe        (bittoe@yahoo.com)
 * Lesson - [KY-036] Touch sensor
 *
 *
 *+-+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
 *|          CALIBRATION
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
 * There are six sensors in this kit that have
 * a red PCB and a blue potentiometer
 * KY-024 LinearHall  | KY-036 TouchSensor
 * KY-025 ReedSwitch  | KY-037 BigSoundSensor
 * KY-026 FlameSensor | KY-038 SmallSoundSensor
 * KY-028 DigitalTempSensor
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

const uint8_t KY_036_DIGITAL_IN = 8;  // digital sensor
const uint8_t KY_036_ANALOG_IN = A0;  // analog sensor

void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);      // define LED_BUILTIN as output interface
  pinMode(KY_036_DIGITAL_IN, INPUT); // define digital pin as input interface
  pinMode(KY_036_ANALOG_IN, INPUT);  // define analog pin as input interface
}

void loop() {
  int ky036_Dval = digitalRead(KY_036_DIGITAL_IN); // Reads digital value
  int ky036_Aval = analogRead(KY_036_ANALOG_IN);   // Reads analog value

  if (ky036_Dval == HIGH) // Touch detected
    digitalWrite(LED_BUILTIN, HIGH);
  else                    // No Touch detected
    digitalWrite(LED_BUILTIN, LOW);
  delay(150);             // change this value to pole the sensor more or less often

  /*
   * To see what the sensor is writing to the Hero board
   * Uncomment the Serial.print lines below
   * This information is also useful during calibration
   */
  Serial.print("Digital Value: ");
  Serial.print(ky036_Dval);
  Serial.print(" | ");
  Serial.print("Analog value: ");
  Serial.println(ky036_Aval);
}