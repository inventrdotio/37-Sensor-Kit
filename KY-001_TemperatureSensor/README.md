# KY-001 Temperature Sensor

<img src="KY-001_TemperatureSensor.jpg">

The KY-001 is a simple temperature sensor module that measures ambient temperature using a DS18B20 digital thermometer chip.  The DS18B20 is a 1-Wire digital thermometer chip that is often used with the KY-001 temperature sensor module in electronics projects.

The DS18B20 provides 9-bit to 12-bit temperature readings in Celsius, with a temperature range of -55°C to +125°C and a temperature accuracy of ±0.5°C in the range of -10°C to +85°C.  The chip communicates with microcontrollers using the 1-Wire protocol, which allows multiple DS18B20 devices to be connected to a single microcontroller pin, making it a cost-effective solution for temperature sensing in various applications.

# Connecting Multiple KY-001 modules
To connect multiple KY-001 temperature sensor modules to an Arduino, you can use the 1-Wire protocol. The 1-Wire protocol allows multiple devices to be connected to a single data line (i.e., a single digital pin) on the microcontroller, with each device having a unique 64-bit identifier.

Here's how you can connect multiple KY-001 modules to an Arduino:

* Connect the power (VCC) and ground (GND) pins of each KY-001 module to the corresponding power and ground pins on the Arduino.
* Connect the data (S) pin of each KY-001 module to a single digital pin on the Arduino, using a 4.7kΩ resistor to pull the data line up to VCC.
* In your Arduino sketch, include the "OneWire" library, which provides the functions required to communicate with the KY-001 modules over the 1-Wire protocol.
* Initialize a OneWire object in your sketch, passing the digital pin connected to the KY-001 modules to the constructor.
* Use the "search()" function to search for all the KY-001 modules connected to the digital pin, and retrieve their 64-bit identifier.
* Use the "reset()" function to reset the communication with a specific KY-001 module, and the "read()" function to read the temperature value from the module.
* Repeat the steps 5 and 6 for each KY-001 module connected to the digital pin, to retrieve the temperature readings from all the modules.

With these steps, you should be able to connect multiple KY-001 temperature sensor modules to an Arduino and retrieve temperature readings from each module.

# Code
Included code can read up to 5 KY-001 modules and report temperatures for each.  Use Serial Plotter to display a graph of all temperatures.

# Wiring diagram
<img src="KY-001_TemperatureSensorWiring.jpg" width="350">

# Library
Install OneWire library from Arduino IDE library manager.
