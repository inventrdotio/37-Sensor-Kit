/*
 * inventr.io 37 in 1 Sensor Kit (https://inventr.io/product/37-in-1-sensor-kit/)
 * Sensor Course (https://inventr.io/course/sensor-training/)
 *
 * Code contributions:
 *    David Schmidt (davids@inventr.io)
 *    biTToe        (bittoe@yahoo.com)
 * Lesson - [KY-036] Touch sensor
 *
 * The KY-036 touch sensor is a small module that can detect touch or contact
 * with a conductive material such as a finger or a piece of metal. It works
 * by measuring changes in capacitance when an object comes into contact with
 * the sensor. 
 *
 * The module has four pins: (AO) analog out, (G) ground, (+) 5v (DO) digital out.
 * When the module is touched, the capacitance changes and the (DO) pin
 * sends a signal to the microcontroller
 *
 * It's worth noting that the KY-036 touch sensor is not very sensitive and may 
 * require a firm touch to activate. If you need a more sensitive touch sensor,
 * you may want to consider using a capacitive touch sensor module instead.
 *
 *+-+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
 *|          CALIBRATION
 *|
 *| This sensor does not utilize the analog out (AO) pin. The value of
 *| AO is ~1023 when +5v is supplied and ~603 when a 3.3 v is supplied.
 *|
 *| To calibrate this sensor turn the potemtiometer screw clockwise (CW)
 *| until you hear an audible 'CLICK'. This just past the point where
 *| the sensor is at it maximum sensitivity and the point where the wiper
 *| is no longer in contact with the resistor. You will know you've reached
 *| this point when you hear the same 'CLICK' every 1-1/2 turns CW.
 *|
 *| When you reach this point, rotate the screw two full turns (720 deg)
 *| counter-clockwise (CCW) This will ensure a good connection.
 *|
 *| If everything is correct and the sketch is running both of the LEDs
 *| (LED_BUILTIN & the external LED) should be off. Touch the small wire
 *| on the top of the sensor with your finger (or other metal object) and
 *| both LEDs should turn on. Touch the sensor again and they
 *| should turn off.
 *|
 *| To see what the program is doing un-comment the Serial.print lines
 *| and open the serial monitor.
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
 * With the EXCEPTION of KY-036 TouchSensor all of the above sensors function
 * in exactly the same way and use exactly the same code, albeit with different
 * variable names. 
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
 * These sensors are not calibrated in any meaningful way.
 * They are detectors as opposed to calibrated sensors; their outputs are not meant to
 * be converted to functional units (dB, degrees, lumens, Teslas... etc)
 *
 * This project uses:
 * One Digital pin (DO) to INPUT #8
 * The analog pin (AO) is not used in this application
 * The onboard LED (LED_BUILTIN) to #13 (hardwired)
 * An external LED to pin #13 (with a 330 Ohm resistor to ground)
 * is used in this example to make the touch activation more apparent.
 *
 * On the Hero (Arduino Uno compatible) we *could* use: D0-D13, A0-A5.
 * Skip: A0-A5 (can use for any ANALOG pin),
 *       D0/D1 (used by USB),
 *       D2/D3 (save for interrupts),
 *    ** D13 (used by LED_BUILTIN and SPI Clock)
 *             but also shared by an external LED in this sketch
 *       D5, D6, D9, D10 and D11 (save for PWM)
 *       D11 (SPI MOSI)
 *       D12 (SPI MISO)
 * Recommended for fewest conflicts:
 *    Digital pin: D4, D7 or D8
 *    Digital pin 13 to an external LED & LED_BUILTIN
 */

const uint8_t KY_036_DIGITAL_IN = 8;  // digital sensor
int KY_036_Flag = -1;                 // Flag initially set to (-1)

void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);      // define LED_BUILTIN as output interface
  pinMode(KY_036_DIGITAL_IN, INPUT); // define digital pin as input interface
}

void loop() {
  int ky036_Dval = digitalRead(KY_036_DIGITAL_IN); // Reads digital value
  if (ky036_Dval == HIGH) {                        // Touch detected

  // Serial.print("\nky036_Dval: ");           // Uncomment the Serial.print
  // Serial.println(ky036_Dval);               // statement to see how the
  // Serial.print("KY_036_Flag pre-toggle: "); // the FLAG changes
  // Serial.println(KY_036_Flag);              // with each touch
  
    KY_036_Flag = KY_036_Flag * -1; // toggle the Flag from -1 to +1 with each touch of the sensor

  // Serial.print("KY_036_Flag post-toggle: "); // Uncomment these as well
  // Serial.println(KY_036_Flag);               // to see the variables change

    if(KY_036_Flag > 0) { // if the Flag is +1 (LED ON)
      digitalWrite(LED_BUILTIN, HIGH);
    }
    else {                // if the flag is -1 (LED OFF)
      digitalWrite(LED_BUILTIN, LOW);
    }  
    delay(250); // The sensor bounces and we only want to capture the first touch
   }
}