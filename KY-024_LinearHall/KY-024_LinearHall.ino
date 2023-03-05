/*
 * inventr.io 37 in 1 Sensor Kit (https://inventr.io/product/37-in-1-sensor-kit/)
 * Sensor Course (https://inventr.io/course/sensor-training/)
 *
 * Code contributions:
 *    David Schmidt (davids@inventr.io)
 *    biTToe        (bittoe@yahoo.com)
 * Lesson - [KY-024] Linear Hall
 *
 * The KY-024 linear hall effect sensor is a type of magnetic sensor
 * that measures the strength and direction of a magnetic field. It works
 * based on the Hall effect, which states that when a magnetic field is applied
 * perpendicular to a current-carrying conductor, a voltage is generated
 * proportional to the magnetic field strength.
 *
 * The KY-024 sensor is used in various applications, including linear positioning,
 * linear speed sensing, and linear current sensing. It's a compact, low-cost,
 * and easy-to-use device that can interface with microcontrollers like Arduino and Raspberry Pi.
 * Many laptops & tablets use a hall effect switch to determine the position of the lid (open or closed)
 *
 * The KY-024 sensor outputs an analog voltage signal proportional to the strength of the
 * magnetic field it's exposed to, making it easy to read and process the data.
 * Additionally, it has a linear response to the magnetic field, meaning that the
 * output voltage changes linearly with the magnetic field strength, making it ideal for
 * applications that require accurate and reliable measurements.
 *
 * Comments by biTToe:
 *
 * Each sensor is equipped with:
 * Two output pins: digital (DO) and analog (AO).
 * Two on-board LEDs: Power (LED1) & Threshold (LED2)
 *
 * When the intensity of the signal is GREATER than the set threshold:
 ** DO == 1, AO < 500, LED2 is ON
 * When the intensity of the signal is LESS than the set threshold:
 ** DO == 0, AO > 500, LED2 is OFF
 * KY-024 is sensitive to BOTH fiels strenght and polarity
 *
 * With no magnet nearby:
 * the analog output (AO) is ~512
 * The digital output (DO) is 0
 * LED2 is OFF
 *
 * For the TOP of the sensor:
 * As the NORTH POLE of a magnet approaches the TOP/FRONT side of the sensor
 ** the ANALOG output INCREASES (AO > 512) 
 ** the DIGITAL output is 0 (DO == 0).
 ** LED2 is OFF
 *
 * As the NORTH POLE of a magnet approaches the BOTTOM/BACK side of the sensor
 ** the ANALOG output DECREASES (AO < 512)
 ** the DIGITAL output is 1 (DO == 1).
 ** LED2 is ON
 *
 * With the SOUTH POLE of the magnet the above outputs are reversed.
 * Get a magnet and play around.
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
 * KY-027 LightCup
 *
 * They all function in exactly the same way and use exactly the same code,
 * albeit with different variable names. 
 *
 * Each sensor is equipped with:
 * two output pins: digital (DO) and analog (AO).
 * Two on-board LEDs: Power (LED1) & Threshold (LED2)

 * When the intensity of the signal is GREATER than the set threshold:
 * DO == 1, AO < 500, LED2 is ON
 
 * When the intensity of the signal is LESS than the set threshold:
 * DO == 0, AO > 500, LED2 is OFF
 
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

const uint8_t KY_024_DIGITAL_OUT = 8;  // digital sensor
const uint8_t KY_024_ANALOG_OUT = A0;  // analog sensor

void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);  // define LED_BUILTIN as output interface
}

void loop() {
  int ky024_Dval = digitalRead(KY_024_DIGITAL_OUT);  // Reads digital value & sets pin as input
  int ky024_Aval = analogRead(KY_024_ANALOG_OUT);    // Reads analog value & sets pin as input

  if (ky024_Dval == HIGH) // (S) on FRONT or (N) on BACK of sensor
    digitalWrite(LED_BUILTIN, HIGH);
  else                    // (N) on the FRONT or (S) on the BACK of sensor
    digitalWrite(LED_BUILTIN, LOW);
  delay(150);             // change this value to pole the sensor more or less often

  /*
   * To see what the sensor is writing to the Hero board
   * Uncomment the Serial.print lines below
   * This information is also useful during calibration
   */
  // Serial.print("Digital Value: ");
  // Serial.print(ky024_Dval);
  // Serial.print(" | ");
  // Serial.print("Analog value: ");
  // Serial.println(ky024_Aval);
}