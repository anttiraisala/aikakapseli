#include "AikakapseliEeprom.h"
#include <Arduino.h>
#include <stdio.h>
#include <EEPROMWearLevel.h>


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
  EEPROMwl.begin(6);
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
  this->eepromObject.magicNumber = AIKAKAPSELI_MAGICNUMBER;
  EEPROMwl.write(0, this->eepromObject.magicNumber);
  EEPROMwl.write(1, this->eepromObject.years);
  EEPROMwl.write(2, this->eepromObject.days);
  EEPROMwl.write(3, this->eepromObject.hours);
  EEPROMwl.write(4, this->eepromObject.minutes);
  EEPROMwl.write(5, this->eepromObject.seconds);
}

void AikakapseliEeprom::clear(void) {
  /*
  EEPROMwl.write(0, 0);
  EEPROMwl.write(1, 0);
  EEPROMwl.write(2, 0);
  EEPROMwl.write(3, 0);
  EEPROMwl.write(4, 0);
  EEPROMwl.write(5, 0);
*/
  Serial.println("Clearing EEPROM ...");
  int eepromSize = EEPROM.length();
  Serial.print("EEPROM.length():[");
  Serial.print(eepromSize, DEC);
  Serial.println("] bytes.");

  // Loop through each byte address and write 0
  for (int i = 0; i < eepromSize; i++) {
    EEPROM.write(i, 0x00);
  }
  Serial.println("EEPROM cleared!");
}

bool AikakapseliEeprom::read(void) {
  this->eepromObject.magicNumber = EEPROMwl.read(0);
  this->eepromObject.years = EEPROMwl.read(1);
  this->eepromObject.days = EEPROMwl.read(2);
  this->eepromObject.hours = EEPROMwl.read(3);
  this->eepromObject.minutes = EEPROMwl.read(4);
  this->eepromObject.seconds = EEPROMwl.read(5);

  if (AIKAKAPSELI_MAGICNUMBER == this->eepromObject.magicNumber) {
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
