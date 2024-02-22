#ifndef AIKAKAPSELI_EEPROM_H
#define AIKAKAPSELI_EEPROM_H

// EEPROM.h tarvitaan EEPROM -rw-operaatioihin
#include <EEPROM.h>

#include <Arduino.h>

#define AIKAKAPSELI_MAGICNUMBER "AikakapseliEepromObject"


class AikakapseliEeprom {
private:

  struct AikakapseliEepromObject {
    char magicNumber[sizeof(AIKAKAPSELI_MAGICNUMBER)];

    /*
16x2 -näytön tekstit
--------------------------------
1234567890123456

YYY:DDD:HH:MM:SS
100:100:23:40:01

*/
    byte years;
    byte days;
    byte hours;
    byte minutes;
    byte seconds;
  };

  AikakapseliEepromObject eepromObject;

public:

  AikakapseliEeprom(void);
  void init(void);  
  void setToTime(unsigned int years, unsigned int days, unsigned int hours, unsigned int minutes, unsigned int seconds);
  bool load(void);
  void save(void);
};

#endif  // AIKAKAPSELI_EEPROM_H
