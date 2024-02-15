
// EEPROM.h tarvitaan EEPROM -rw-operaatioihin
#include <EEPROM.h>

const char magicNumber[] = "AikakapseliEepromObject\n";

struct AikakapseliEepromObject {
  char magicNumber[sizeof(magicNumber)];
  float field1;
  byte field2;
  char string[10];
};

void setup() {
  // put your setup code here, to run once:

    Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  Serial.print("Sizeof:");
  Serial.println(strlen(magicNumber), DEC);


  AikakapseliEepromObject eepromObjectIn;

  // Koitetaan lukea
  EEPROM.get(0, eepromObjectIn);
  Serial.println("Read custom object from EEPROM: ");
  Serial.println(eepromObjectIn.magicNumber);

  if(strcmp(eepromObjectIn.magicNumber, magicNumber)==0){
    Serial.println("Was written before.");
    Serial.print("string: ");
    Serial.println(eepromObjectIn.string);
    Serial.print("field1: ");
    Serial.println(eepromObjectIn.field1);
    Serial.print("field2: ");
    Serial.println(eepromObjectIn.field2);
  } else {
    Serial.println("Was not written before.");

    AikakapseliEepromObject eepromObjectOut;
    strcpy(eepromObjectOut.magicNumber, magicNumber);
    strcpy(eepromObjectOut.string, "Antti");
    EEPROM.put(0, eepromObjectOut);
  }
}

void loop() {
  // put your main code here, to run repeatedly:

}
