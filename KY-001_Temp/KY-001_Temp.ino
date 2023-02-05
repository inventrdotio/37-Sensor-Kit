/*
 * inventr.io 37 in 1 Sensor Kit (https://inventr.io/product/37-in-1-sensor-kit/)
 * Sensor Course (https://inventr.io/course/sensor-training/)
 *
 * Lesson 1 - [KY-001] Temperature Sensor
 *
 * The KY-001 is a simple temperature sensor module that measures ambient temperature using
 * a DS18B20 digital thermometer chip.  The DS18B20 is a 1-Wire digital thermometer chip that
 * is often used with the KY-001 temperature sensor module in electronics projects.
 *
 * The DS18B20 provides 9-bit to 12-bit temperature readings in Celsius, with a temperature
 * range of -55°C to +125°C and a temperature accuracy of ±0.5°C in the range of -10°C to +85°C.
 * The chip communicates with microcontrollers using the 1-Wire protocol, which allows multiple
 * DS18B20 devices to be connected to a single microcontroller pin, making it a cost-effective
 * solution for temperature sensing in various applications.
 *
 * Library requirements:
 * Install OneWire library from Arduino IDE library manager
 */

#include <OneWire.h>  // OneWire library

// Need a Digital pin.
// On the Hero (Arduino Uno compatible) we *could* use: D0-D13, A0-A5.
// Skip: A0-A5 (save for Analog),
//       D0/D1 (used by USB),
//       D2/D3 (save for interrupts),
//       D13 (used by LED_BUILTIN),
//       D5, D6, D9, D10 and D11 (save for PWM)
// Recommended:
//    D4, D7, D8 or D12
const uint8_t KY_001_PIN = 4;

// Use OneWire library to communicate with KY-001's DS18S20 temperature chip
OneWire ds(KY_001_PIN);

void setup(void) {
  Serial.begin(9600);  // initialize console to 9600 baud.  Be sure to set Serial Monitor to 9600 baud
}

void loop(void) {
  char byte_text[3];  // storage for printing hex bytes

  // For conversion of raw data to C
  int HighByte, LowByte, TReading, SignBit, Tc_100, Whole, Fract;

  byte data[12];
  byte addr[8];

  // DS18S20 supports having multiple devices on the same wire, each returning their own address
  // Each time through the loop() we will find the next module and retrieve it's data
  if (!ds.search(addr)) {                        // Returns TRUE if valid address found
    Serial.print("No more sensors found.\n\n");  //
    ds.reset_search();
    return;
  }

  Serial.print("Address = ");
  for (int i = 0; i < 8; i++) {
    sprintf(byte_text, "%02x", addr[i]);
    Serial.print(byte_text);
    if (i == 3) Serial.print(":");
  }
  if (addr[0] == 0x10)
    Serial.print(", DS18S20");
  else if (addr[0] == 0x28)
    Serial.print(", DS18B20");
  else {
    Serial.print(", UNKNOWN: 0x");
    sprintf(byte_text, addr[0]);
    Serial.println(byte_text);
    return;
  }

  if (OneWire::crc8(addr, 7) != addr[7]) {
    Serial.print(" CRC is not valid!\n");
    return;
  }
  Serial.println();

  // Now read data from detected sensor
  ds.reset();
  ds.select(addr);
  ds.write(0x44, 1);  // start conversion, with parasite power on at the end

  delay(1000);  // maybe 750ms is enough, maybe not

  // we might do a ds.depower() here, but the reset will take care of it.
  byte present = ds.reset();
  ds.select(addr);
  ds.write(0xBE);  // Read Scratchpad

  Serial.print("Data    = ");
  // Serial.print(present, HEX);
  // Serial.print(" ");
  for (int i = 0; i < 9; i++) {  // we need 9 bytes
    data[i] = ds.read();         // Read next byte
    sprintf(byte_text, "%02x", data[i]);
    Serial.print(byte_text);
    Serial.print(" ");
  }
  uint8_t crc = OneWire::crc8(data, 8);
  if (crc != data[8]) {
    Serial.print(" BAD CRC! (0x");
    sprintf(byte_text, "%02x", crc);
    Serial.print(byte_text);
    Serial.println(")");
    return;
  }
  Serial.println();

  // Conversion of raw data to degrees Celsius
  LowByte = data[0];
  HighByte = data[1];
  TReading = (HighByte << 8) + LowByte;
  SignBit = TReading & 0x8000;  // test most sig bit
  if (SignBit)                  // negative
  {
    TReading = (TReading ^ 0xffff) + 1;  // 2's comp
  }
  Tc_100 = (6 * TReading) + TReading / 4;  // multiply by (100 * 0.0625) or 6.25

  Whole = Tc_100 / 100;  // separate off the whole and fractional portions
  Fract = Tc_100 % 100;

  if (SignBit)  // If its negative
    Serial.print("-");
  Serial.print(Whole);
  Serial.print(".");
  if (Fract < 10) {
    Serial.print("0");
  }
  Serial.print(Fract);

  Serial.print(" degrees Celsius\n");
  //End conversion to C
}