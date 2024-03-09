#include "AikakapseliEeprom.h"
#include <Arduino.h>


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  delay(3000);

  AikakapseliEeprom aikakapseliEeprom;
  aikakapseliEeprom.init();

  //aikakapseliEeprom.clear();


  Serial.println(F("Setup done."));
}

void loop() {
}