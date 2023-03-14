/*
 * inventr.io 37 in 1 Sensor Kit (https://inventr.io/product/37-in-1-sensor-kit/)
 * Sensor Course (https://inventr.io/course/sensor-training/)
 *
 * Code contributions:
 *    David Schmidt (davids@inventr.io)
 *    biTToe        (bittoe@yahoo.com)
 * Lesson - [KY-028] digital temperature sensor
 *
 * The KY-028 module is equiped with an NTC Thermistor
 * An NTC thermistor is a resistor with a Negative Temperature Coefficient.
 * Having a negative temperature coefficient means its resistance decreases
 * with increasing temperature and vice-versa.
 * Therefor:
 * As temperature INCREASES, the output value of the analog sensor DECREASES.
 *
 * The module comes with a small potentiometer that can be adjusted to set
 * the temperature threshold (TRIGGER POINT), allowing the user to trigger
 * events or actions when the temperature goes above or below a certain point.
 *
 *+-+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
 *|          CALIBRATION
 *| This is a sensor-switch. It functions more like a thermostat
 *| It is not really set up to be used as a thermometer. 
 *| 
 *| To calibrate this sensor, un-comment the Serial.print
 *| lines at the end of the sketch and run.
 *| The Analog value will be somewhere between 0 & 1023
 *| The Digital Value will be 1 if the analog value is LESS than ~510
 *| The Digital Value will be 0 if the analog value is GREATER than ~510
 *| 
 *| Set the trigger point by adjusting the small screw on
 *| the blue potentiometer; this will change the analog
 *| output (sensitivity): Clockwise DECREASES Analog Value,
 *| Counterclockwise INCREASES Analog Value. When the
 *| Analog Value is LESS than about 510 the Digital
 *| Value should change from 0 to 1. This is your trigger point.
 *|
 *| To fine tune the sensitivity, observe LED2 on the sensor.
 *| When LED2 is ON you have crossed the threshold. Adjust
 *| the potentiometer so your trigger-point is consistent
 *| and reliable.
 *+-+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
 *
 * What can we do with this?
 *
 * Let’s say you have a computer case that you don’t want the temperature to go above 100deg F.
 * All you have to do is CALIBRATE the sensor by placing it in a “box” where the temperature
 * is a stable 100deg F. Then dial the potentiometer until you reach the *trigger point*
 *
 * When the sensor returns to regular ambient temperatures (as long as it’s cooler than 100deg F)
 * the analog output will be greater than 511.
 *
 * Install the sensor in the computer case and run the computer. As the temperature in the case
 * increases the analog output value will decrease. When that value is 510 or less, the
 * digital output will change from 0 (LOW) to 1 (HIGH). You can use this change to trigger
 * a fan or some other cooling device to reduce the temperature inside the case.
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

const uint8_t KY_028_DIGITAL_IN = 8;  // digital sensor
const uint8_t KY_028_ANALOG_IN = A0;  // analog sensor

void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);      // define LED_BUILTIN as output interface
  pinMode(KY_028_DIGITAL_IN, INPUT); // define digital pin as input interface
  pinMode(KY_028_ANALOG_IN, INPUT);  // define analog pin as input interface
}

void loop() {
  int ky028_Dval = digitalRead(KY_028_DIGITAL_IN); // Reads digital value
  int ky028_Aval = analogRead(KY_028_ANALOG_IN);   // Reads analog value

  if (ky028_Dval == HIGH) // temperature GREATER than set threshold
    digitalWrite(LED_BUILTIN, HIGH);
  else                    // temperatire LESS than set threshold
    digitalWrite(LED_BUILTIN, LOW);
  delay(150);             // change this value to pole the sensor more or less often

  /*
   * To see what the sensor is writing to the Hero board
   * Uncomment the Serial.print lines below
   * This information is also useful during calibration
   */
  // Serial.print("Digital Value: ");
  // Serial.print(ky028_Dval);
  // Serial.print(" | ");
  // Serial.print("Analog value: ");
  // Serial.println(ky028_Aval);
}