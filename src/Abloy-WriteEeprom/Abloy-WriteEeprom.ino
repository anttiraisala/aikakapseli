#include "AikakapseliEeprom.h"
AikakapseliEeprom aikakapseliEeprom;



/*

setup() -funktiossa on funktiokutsut:

- read()
- write()
- clear()

, kommentoi ne käyttöön / pois tarpeen mukaan ja aja ohjelma.

*/


void read(void);
void write(void);
void clear(void);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(19200);
  delay(1500);

  aikakapseliEeprom.init();
  aikakapseliEeprom.setToTime(5, 4, 3, 2, 1);
  Serial.print(F("Test value: "));
  Serial.println(aikakapseliEeprom.getTimeString());


  Serial.println(F("Let's start..."));
  ///////////////////////////////////////////////////////////////
  /* Kommentoi pois / päälle sopiva koodi ja aja */

  //clear();

  read();

  //write();

  //clear();
  ///////////////////////////////////////////////////////////////
  Serial.println(F("Done."));
}

void loop() {
  // put your main code here, to run repeatedly:
/*
  aikakapseliEeprom.decreaseTime();
  Serial.print(F("Decrease time: "));
  Serial.println(aikakapseliEeprom.getTimeString());
  */
}

void write(void){
  Serial.println(F("Writing..."));
  aikakapseliEeprom.setToTime(100, 1, 12, 34, 56);
  /*
  aikakapseliEeprom.setToTime(100, 0, 0, 0, 56);
  aikakapseliEeprom.setToTime(0, 0, 0, 0, 6);
  */
  aikakapseliEeprom.setToTime(100, 0, 0, 0, 10);
  aikakapseliEeprom.write();

  Serial.println(F("Reading after write..."));
  read();
}

void clear(void){
  Serial.println(F("Clearing..."));
  aikakapseliEeprom.clear();

  Serial.println(F("Reading after clear..."));
  read();
}

void read(void){
  Serial.println(F("Reading..."));
  aikakapseliEeprom.init();
  bool success=aikakapseliEeprom.read();
  if(success){
    Serial.println(F("aikakapseliEeprom.load() == true"));
  } else {
    Serial.println(F("aikakapseliEeprom.load() == false"));
  }

  Serial.print(F("Value in EEPROM: "));
  Serial.println(aikakapseliEeprom.getTimeString());

}

