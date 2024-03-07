#ifndef AIKAKAPSELI_EEPROM_H
#define AIKAKAPSELI_EEPROM_H

/*
https://arduino.stackexchange.com/questions/226/what-is-the-real-lifetime-of-eeprom

SD Card wear leveling
https://forum.arduino.cc/t/sdcard-data-logging-wearing-down-the-sdcard/272072/2
*/

// EEPROM.h tarvitaan EEPROM -rw-operaatioihin
#include <EEPROM.h>

#include <Arduino.h>

#define AIKAKAPSELI_MAGICNUMBER 169


class AikakapseliEeprom {
private:

  struct AikakapseliEepromObject {
    //char magicNumber[sizeof(AIKAKAPSELI_MAGICNUMBER)];
    byte magicNumber;

    /*
16x2 -näytön tekstit
--------------------------------
1234567890123456

YYY:DDD:HH:MM:SS
100:100:23:40:01

*/
    byte years;
    unsigned int days;
    byte hours;
    byte minutes;
    byte seconds;
  };

  AikakapseliEepromObject eepromObject;
  #define TIME_FORMAT "YYY:DDD:HH:MM:SS"
  char stringRepresentation[sizeof(TIME_FORMAT)];

public:

  AikakapseliEeprom(void);
  void init(void);
  void setToTime(unsigned int years, unsigned int days, unsigned int hours, unsigned int minutes, unsigned int seconds);

  bool read(void);
  void write(void);
  /* Tyhjennetään EEPROM */
  void clear(void);
  void testRW(void);

  /* Vähentää kellonaikaa yhdellä sekunnilla. Jos ennen vähentämistä ollaan nollassa, niin ei vähennetä ja palautetaan false,
  muuten vähennetään aikaa ja palautetaan true */
  boolean decreaseTime(void);

  char *getTimeString(void);
};

#endif  // AIKAKAPSELI_EEPROM_H
