#include <Arduino.h>

 #define LED 2

void setup() {
  Serial.begin(115200);
  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);
}

void loop() {
  Serial.println("Hello, world!");
  delay(3000);
  digitalWrite(LED, HIGH);
  delay(3000);
  digitalWrite(LED, LOW);
}
