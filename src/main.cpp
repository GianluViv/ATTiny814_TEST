#include <Arduino.h>
#define LED PIN_PB1

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("Hello World!");
  digitalWrite(LED, digitalRead(LED) ^ 1);
  delay(500);
  
}
