#include "AikakapseliEeprom.h"
#include <Arduino.h>


AikakapseliEeprom::AikakapseliEeprom(void) {
  this->setToTime(0, 0, 0, 0, 0);
}

void AikakapseliEeprom::init(void) {
}

void AikakapseliEeprom::save(void) {}

bool AikakapseliEeprom::load(void) {
  EEPROM.get(0, this->eepromObject);

  if(strcmp(AIKAKAPSELI_MAGICNUMBER, this->eepromObject.magicNumber)==0){
    return true;
  } else {
    return false;
  }

}

void AikakapseliEeprom::setToTime(unsigned int years, unsigned int days, unsigned int hours, unsigned int minutes, unsigned int seconds) {}
