/*
 * NOTES: I was never able to get this working correctly.
 * The pin labels on our kit are in the opposite order than the ones everywhere else
 * including the wiring diagrams in our course.
 * I tried the pins in both orders (which may have disabled both of my units).
 * The unit in our kit is part IH-08H, NOT a KY-032 and pins are reversed.
 */

void setup() {
  Serial.begin(9600);
  pinMode(8, INPUT);  // set pin as input
}

void loop() {
  //Written for Robojax on Dec 28, 2017
  int detect = digitalRead(8);  // read obstacle status and store it into "detect"
  if (detect == LOW) {

    Serial.println("Obstacle in the way");
  } else {

    Serial.println("clear");
  }
  delay(500);
}