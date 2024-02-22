#include "AikakapseliEeprom.h"
#include <Arduino.h>
#include <stdio.h>


AikakapseliEeprom::AikakapseliEeprom(void) {
  this->init();
}

#define TIME_FORMAT "YYY:DDD:HH:MM:SS"

char* AikakapseliEeprom::getTimeString(void) {

  sprintf(stringRepresentation, "%03d:%03d:%02d:%02d:%02d",
          this->eepromObject.years,
          this->eepromObject.days,
          this->eepromObject.hours,
          this->eepromObject.minutes,
          this->eepromObject.seconds);

  return stringRepresentation;
}

void AikakapseliEeprom::init(void) {
  this->setToTime(0, 0, 0, 0, 0);
}

boolean AikakapseliEeprom::decreaseTime(void) {
  if (this->eepromObject.years == 0 && this->eepromObject.days == 0 && this->eepromObject.hours == 0 && this->eepromObject.minutes == 0 && this->eepromObject.seconds == 0) {
    return false;
  }

  if (this->eepromObject.seconds > 0) {
    this->eepromObject.seconds--;
    return true;
  }

  this->eepromObject.seconds = 59;
  if (this->eepromObject.minutes > 0) {
    this->eepromObject.minutes--;
    return true;
  }

  this->eepromObject.minutes = 59;
  if (this->eepromObject.hours > 0) {
    this->eepromObject.hours--;
    return true;
  }

  this->eepromObject.hours = 23;
  if (this->eepromObject.days > 0) {
    this->eepromObject.days--;
    return true;
  }

  this->eepromObject.days = 364;
  if (this->eepromObject.years > 0) {
    this->eepromObject.years--;
    return true;
  }

  return true;
}

void AikakapseliEeprom::write(void) {
    strcpy(this->eepromObject.magicNumber, AIKAKAPSELI_MAGICNUMBER);
    EEPROM.put(0, this->eepromObject);
}

void AikakapseliEeprom::clear(void) {
  AikakapseliEepromObject clearedObject;
    strcpy(clearedObject.magicNumber, "Cleared");
    EEPROM.put(0, clearedObject);
}

void clear(void);

bool AikakapseliEeprom::read(void) {
  EEPROM.get(0, this->eepromObject);

  if (strcmp(AIKAKAPSELI_MAGICNUMBER, this->eepromObject.magicNumber) == 0) {
    return true;
  } else {
    return false;
  }
}

void AikakapseliEeprom::setToTime(unsigned int years, unsigned int days, unsigned int hours, unsigned int minutes, unsigned int seconds) {
  this->eepromObject.years = years;
  this->eepromObject.days = days;
  this->eepromObject.hours = hours;
  this->eepromObject.minutes = minutes;
  this->eepromObject.seconds = seconds;
}
