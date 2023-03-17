/*
 * inventr.io 37 in 1 Sensor Kit (https://inventr.io/product/37-in-1-sensor-kit/)
 * Sensor Course (https://inventr.io/course/sensor-training/)
 *
 * Code contributions:
 *    David Schmidt (davids@inventr.io)
 *    biTToe        (bittoe@yahoo.com)
 * Lesson - [KY-037] Big Sound Sensor
 *
 *** The KY-037 "Big Sound Sensor" & the KY-038 "Small Sound Sensor"
 *** function EXACTLY the same. The only difference is in the size
 *** and sensitivity of the microphones. 
 *
 * KY-037 is a module that is designed to detect sound intensity and convert
 * it into an analog voltage signal. It is also known as a big sound sensor
 * or a sound detection sensor module. 

 * This module has a built-in microphone that detects sound waves and converts
 * them into electrical signals. The output voltage of the module varies with
 * the intensity of the sound. The module has an adjustable sensitivity knob
 * that allows you to set the threshold level at which the sound is detected
 * and is widely used in various projects such as voice-activated lights,
 * sound-activated alarms, and interactive sound installations.
 * 
 * The sensitivity can be adjusted using the potentiometer on the module.
 * The module has a digital output that goes high when it detects a sound
 * above the set threshold and goes low when the sound is below the threshold.
 * 
 *+-+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
 *|          CALIBRATION
 *| The KY-037 Big Sound Sensor functions like a thermostat
 *| for sound. 
 *| 
 *| To calibrate this sensor, un-comment the Serial.print
 *| lines at the end of the sketch and run.
 *| The Analog value will be somewhere between 0 & 1023
 *| The Digital Value will be 1 if the analog value is LESS than ~510
 *| The Digital Value will be 0 if the analog value is GREATER than ~510
 *| 
 *| In a quiet room, set the trigger point by adjusting the small
 *| screw on the blue potentiometer; this will change the analog
 *| output (sensitivity): Clockwise DECREASES Analog Value,
 *| Counterclockwise INCREASES Analog Value. When the
 *| Analog Value is LESS than about 510 the Digital
 *| Value should change from 0 to 1. This is your trigger point.
 *|
 *| Place a sound source close to the microphone. You could use a
 *| speaker or small electric motor. The sensor is directional and
 *| will work best when the source is directly in front of the sensor.
 *| Turn-on your sound source. IF it is positioned correctly and it
 *| is loud enough, the analogue output will drop below 500
 *| and the digital output will change from 0 to 1.
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


const uint8_t KY_037_DIGITAL_IN = 8;  // digital sensor
const uint8_t KY_037_ANALOG_IN = A0;  // analog sensor

void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);      // define LED_BUILTIN as output interface
  pinMode(KY_037_DIGITAL_IN, INPUT); // define digital pin as input interface
  pinMode(KY_037_ANALOG_IN, INPUT);  // define analog pin as input interface
}

void loop() {
  int ky037_Dval = digitalRead(KY_037_DIGITAL_IN); // Reads digital value
  int ky037_Aval = analogRead(KY_037_ANALOG_IN);   // Reads analog value

  if (ky037_Dval == HIGH) // temperature GREATER than set threshold
    digitalWrite(LED_BUILTIN, HIGH);
  else                    // temperatire LESS than set threshold
    digitalWrite(LED_BUILTIN, LOW);
  delay(5);             // change this value to pole the sensor more or less often

  /*
   * To see what the sensor is writing to the Hero board
   * Uncomment the Serial.print lines below
   * This information is also useful during calibration
   */
  // Serial.print("Digital Value: ");
  // Serial.print(ky037_Dval);
  // Serial.print(" | ");
  // Serial.print("Analog value: ");
  // Serial.println(ky037_Aval);
}