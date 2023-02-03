#include <IRremote.h>

const int RECV_PIN = 10;  // Set input pin

IRrecv irrecv(RECV_PIN);

void setup() {
  Serial.begin(115200);
  irrecv.enableIRIn();  // Start the receiver
}
void loop() {
  if (IrReceiver.decode()) {
    Serial.print("Command # : ");
    Serial.println(IrReceiver.decodedIRData.command);
    Serial.print("Raw data  : ");
    Serial.println(IrReceiver.decodedIRData.decodedRawData);
    irrecv.resume();  // Receive the next value
  }
}