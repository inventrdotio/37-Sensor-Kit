/*
 * inventr.io 37 in 1 Sensor Kit (https://inventr.io/product/37-in-1-sensor-kit/)
 * Sensor Course (https://inventr.io/course/sensor-training/)
 *
 * Code contributions by David Schmidt and user biTTOE.
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

#define DEBUG false  // Set to false and use Serial Plotter for graph of all temperatures

// Need a Digital pin.
// On the Hero (Arduino Uno compatible) we *could* use: D0-D13, A0-A5.
// Skip: A0-A5 (save for Analog),
//       D0/D1 (used by USB),
//       D2/D3 (save for interrupts),
//       D13 (used by LED_BUILTIN and SPI Clock),
//       D5, D6, D9, D10 and D11 (save for PWM)
//       D11 (SPI MOSI)
//       D12 (SPI MISO)
// Recommended for least conflicts:
//    D4, D7 or D8
const uint8_t KY_001_PIN = 4;   // Good digital pin not used for other purposes

// Use OneWire library to communicate with KY-001's DS18S20 temperature chip
OneWire ds(KY_001_PIN);   // Create OneWire object to communicate with sensor

// Each OneWire sensor is configured with a unique 64 bit address starting with an
// 8 bit "family" code, 48 bit address and an 8 bit Cyclic Redundancy Check (CRC)
// checksum to validate that the address read has no errors.
//
// Since we can have multiple DS18x20 sensors on the wire we will poll for all
// devices on the wire, validate and identify each and save the addresses of all
// DS18x20 type sensors here.
const int MAX_DS_DEVICES = 5;   // We will save addresses for up to 5 sensors.
byte ds_addresses[MAX_DS_DEVICES][8];   // 64 bits for each address
int ds_count = 0;

// Function to print a 64 bit number as hexadecimal digits
void print_address(byte[8]);

void setup(void) {
  Serial.begin(9600);  // initialize console to 9600 baud.  Be sure to set Serial Monitor to 9600 baud

  // Scan OneWire for all devices, saving all DS18x20 device addresses
  for (int i = 0; i < MAX_DS_DEVICES; i++) {
    if (DEBUG) Serial.println("Searching for valid devices on OneWire");
    if (ds.search(ds_addresses[ds_count])) { // if we found another address
      if (DEBUG) Serial.print("Device Address: ");
      if (DEBUG) print_address(ds_addresses[i]);

      if (OneWire::crc8(ds_addresses[i], 7) != ds_addresses[i][7]) {
        if (DEBUG) Serial.println(" CRC is not valid (skipped)");
        break;
      }

      switch (ds_addresses[ds_count][0]) {
      case 0x10:
        if (DEBUG) Serial.println(", DS18S20");
        break;
      case 0x28:
        if (DEBUG) Serial.println(", DS18B20");
        break;
      default:
        if (DEBUG) Serial.println(", UNKNOWN (skipped)");
        continue;     // continue for loop with next device.
      }
      ds_count++;   // valid DS18x20 device, point to next address slot.
    } else {
      break;  // No more devices.  ds_count countains count of valid devices found
    }
    delay(1000);
  }
  Serial.print("Found ");
  Serial.print(ds_count);
  Serial.println(" devices.\n");
  if (ds_count == 0) return;
}

void loop(void) {
  // For conversion of raw data to C
  int HighByte, LowByte, TReading, SignBit, Tc_100, Whole, Fract;

  byte data[12];
  byte addr[8];

  // DS18S20 supports having multiple devices on the same wire, each returning their own address
  // Each time through the loop() we will find the next module and retrieve it's data
  for (int i = 0; i < ds_count; i++) {
    if (!DEBUG && i > 0) Serial.print(", ");    // Add separator if not in DEBUG mode
    // Now read data from detected sensor
    ds.reset();
    ds.select(ds_addresses[i]);
    // since we supply 5v we don't need to supply parasitic power and wait.
    ds.write(0x44, false);  // start conversion
    // Wait until we get a completion bit (1)
    while(!ds.read_bit()) {}  // Returns 0 (false) until temp is ready to read.

    // we might do a ds.depower() here, but the reset will take care of it.
    byte present = ds.reset();
    ds.select(ds_addresses[i]);
    ds.write(0xBE);  // Read Scratchpad

    if (DEBUG) Serial.print("Data    = ");
    // Serial.print(present, HEX);
    // Serial.print(" ");
    for (int i = 0; i < 9; i++) {  // we need 9 bytes
      data[i] = ds.read();         // Read next byte
      if (DEBUG) {
        char hex_string[3];           // 2 hex digits plus trailing null
        sprintf(hex_string, "%02x", data[i]);
        Serial.print(hex_string);
        Serial.print(" ");
      }
    }
    uint8_t crc = OneWire::crc8(data, 8);
    if (crc != data[8]) {
      if (DEBUG) {
        Serial.print(" BAD CRC! (0x");
        char hex_string[3];           // 2 hex digits plus trailing null
        sprintf(hex_string, "%02x", crc);
        Serial.print(hex_string);
        Serial.println(")");
      }
      return;
    }
    if (DEBUG) Serial.println();

    // Get 16 bit reading from first two data bytes
    TReading = (data[1] << 8) + data[0];
    Serial.print(TReading * .0625);

    if (DEBUG) Serial.print(" degrees Celsius\n");
    //End conversion to C
  }
  Serial.println();
}

void print_address(byte address[8]) {
  char hex_string[3];  // 2 hex digits plus trailing null

  for (int i = 0; i < 8; i++) {
    sprintf(hex_string, "%02x", address[i]);
    Serial.print(hex_string);
    if (i == 3) Serial.print(":");  // display ':' between 32bit values
  }
}
