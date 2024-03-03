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
  Serial.begin(9600);
  delay(1500);

  aikakapseliEeprom.init();
  aikakapseliEeprom.setToTime(5, 4, 3, 2, 1);
  Serial.print("Test value: ");
  Serial.println(aikakapseliEeprom.getTimeString());


  Serial.println("Let's start...");
  ///////////////////////////////////////////////////////////////
  /* Kommentoi pois / päälle sopiva koodi ja aja */


  //read();

  //write();

  clear();
  ///////////////////////////////////////////////////////////////
  Serial.println("Done.");
}

void loop() {
  // put your main code here, to run repeatedly:
/*
  aikakapseliEeprom.decreaseTime();
  Serial.print("Decrease time: ");
  Serial.println(aikakapseliEeprom.getTimeString());
  */
}

void write(void){
  Serial.println("Writing...");
  aikakapseliEeprom.setToTime(100, 1, 12, 34, 56);
  /*
  aikakapseliEeprom.setToTime(100, 0, 0, 0, 56);
  aikakapseliEeprom.setToTime(0, 0, 0, 0, 6);
  */
  aikakapseliEeprom.setToTime(100, 0, 0, 0, 10);
  aikakapseliEeprom.write();

  Serial.println("Reading after write...");
  read();
}

void clear(void){
  Serial.println("Clearing...");
  aikakapseliEeprom.clear();

  Serial.println("Reading after clear...");
  read();
}

void read(void){
  Serial.println("Reading...");
  aikakapseliEeprom.init();
  bool success=aikakapseliEeprom.read();
  if(success){
    Serial.println("aikakapseliEeprom.load() == true");
  } else {
    Serial.println("aikakapseliEeprom.load() == false");
  }

  Serial.print("Value in EEPROM: ");
  Serial.println(aikakapseliEeprom.getTimeString());

}
