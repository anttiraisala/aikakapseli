
/*
Liitettävät komponentit:
- OLED 1.12 inch (SH1107) ( I2C ) ( Tätä ei välttämättä ole valmiissa tuotteessa, mutta kehitysvaiheessa se on kätevä )
- 16x2 LCD (I2C)
- LED Stick D2-D7
- Adjustable PIR Motion Sensor ( A0/14 )  Asiakkaan lähestyminen 
- Infrared Reflective Sensor ( A1/15 )  Viestin pudottaminen
*/

// Tällä voidaan kehityksen aikana tulostella juttuja. Muista kytkeä pois päältä tuotannossa.
#include "debug.h"

// Tällä ajastetaan tehtävät tapahtumaan loop()-silmukassa
#include "CallbackTimer.h"

// Tällä havaitaan asiakkaan lähestyminen
#include "distance_sensor.h"
extern long millisWhenToExitRetreatingState;

// Tällä havaitaan viestin laittaminen
#include "note_sensor.h"
extern long millisWhenToExitDroppedState;



/* Asiakkaan etäisyys -tilat */
#include "distance_state.h"
DistanceState distanceState = DistanceState::FAR ;


/* Viestin asettaminen -tilat */
#include "note_state.h"
NoteState noteState = NoteState::NO_NOTE;


/* Tällä hoidetaan LCD-näytön tekstit */
#include "lcd_screen.h"
Lcd_screen *lcd;

/* Tällä kontrolloidaan LED-Stickejä */
#include "LedLights.h"
LedLights ledLights;
CallbackTimer *setLightsToRandomTimer;
void setLightsToRandom(void){
  ledLights.setLightsToRandom();
}


/* Tämä hoitaa 100-vuotisen laskurin */
//
#include "AikakapseliEeprom.h"
AikakapseliEeprom aikakapseliEeprom;
void decreaseTimeAndShow(void){
  aikakapseliEeprom.decreaseTime();
  lcd->setText(aikakapseliEeprom.getTimeString(), 0);
}
CallbackTimer *decreaseTimeAndShowTimer;
void writeTime(void){
  aikakapseliEeprom.write();
}
CallbackTimer *writeCountdownTimeToEepromTimer;




// Tällä pidetään kirjaa kuluneista millisekunneista
long currentTimeMillis = millis();
//
long nextMillisTo_checkForStateChanges=0;
long nextMillisTo_printState=0;


// Tehdään ajastus, että tilat tarkastetaan 10ms välein
void checkForStateChanges();
CallbackTimer *stateChangeTimer;
//

// Tällä tulostetaan debug-juttuja tiloista
#ifdef DEBUG_MODE
  CallbackTimer *debugPrintStatesTimer;
  
  void debugPrintStates(){
    DEBUG_DISTANCE_STATE_PRINTLN(getCurrentDistanceStateString(distanceState));
    DEBUG_NOTE_STATE_PRINTLN(getCurrentNoteStateString(noteState));
  }

#endif // DEBUG_MODE


void setup() {
  delay(1500);

  // put your setup code here, to run once:
  Serial.begin(9600);
  DEBUG_PRINTLN("setup()");

  ledLights.init();
  delay(1000);
  ledLights.setLightsToTestPattern();
  delay(1000);
  ledLights.setLightsToZero();
  delay(1000);

  lcd = new Lcd_screen();

  /* Vähän aikaa näytetään alkutekstiä, sitten alkaa varsinainen toiminta */
  delay(3000);
  lcd->clear();
  delay(1000);

  currentTimeMillis = millis();

  stateChangeTimer = new CallbackTimer(checkForStateChanges, currentTimeMillis, (unsigned long)10);

  decreaseTimeAndShowTimer = new CallbackTimer(decreaseTimeAndShow, currentTimeMillis, (unsigned long)1000);
  writeCountdownTimeToEepromTimer = new CallbackTimer(writeTime, currentTimeMillis, (unsigned long)1000*60*5);

  setLightsToRandomTimer = new CallbackTimer(setLightsToRandom, currentTimeMillis, (unsigned long)1000/20);


  #ifdef DEBUG_MODE
  debugPrintStatesTimer = new CallbackTimer(debugPrintStates, currentTimeMillis, (unsigned long)500);
  #endif // DEBUG_MODE

  /* Alustetaan aikalaskuri, yritetään lukea arvo EEPROM:sta */
  aikakapseliEeprom.init();
  if(aikakapseliEeprom.read()){
    DEBUG_PRINTLN("aikakapseliEeprom.read() == true");
  } else {
    aikakapseliEeprom.setToTime(0, 10, 0, 0, 0);
    DEBUG_PRINTLN("aikakapseliEeprom.read() == false");
  }
}

void loop() {
  // put your main code here, to run repeatedly:

  currentTimeMillis = millis();

  // Tilanvahdot 10ms välein
  stateChangeTimer->loop(currentTimeMillis);

  // Countdown -laskurin ajan vähentäminen ja arvon tulostus tasan sekunnin välein
  decreaseTimeAndShowTimer->loop(currentTimeMillis);
  // Countdown -laskurin ajan tallennus EEPROM:iin sähkökatkojen varalle
  writeCountdownTimeToEepromTimer->loop(currentTimeMillis);


  // Kehitystyön aikana vilkutellaan LEDejä sattumanvaraisesti
  setLightsToRandomTimer->loop(currentTimeMillis);

  // debug-tulostuksia 250ms välein
  #ifdef DEBUG_MODE
  debugPrintStatesTimer->loop(currentTimeMillis);
  #endif // DEBUG_MODE

  /* Hoidetaan LCD-näytön tekstien häviäminen ajallaan */
  lcd->loop(currentTimeMillis);
}

void checkForStateChanges(){
  //Serial.println(millis(), DEC);

  /* Asiakkaan etäisyys -tilat */
  switch (distanceState) {
    case DistanceState::FAR :
      if(isCustomerDetected() == true){
        distanceState = DistanceState::NEAR ;

        DEBUG_DISTANCE_STATE_PRINTLN("Change to DistanceState::NEAR");
      }
    break;

    case DistanceState::NEAR :
      if(isCustomerDetected() == false){
        distanceState = DistanceState::RETREATING ;
        millisWhenToExitRetreatingState = currentTimeMillis + 5000;

        DEBUG_DISTANCE_STATE_PRINTLN("Change to DistanceState::RETREATING");
      }
    break;

    case DistanceState::RETREATING :
      if(isCustomerDetected() == true){
        distanceState = DistanceState::NEAR ;

        DEBUG_DISTANCE_STATE_PRINTLN("Change to DistanceState::NEAR");
      } 
      if(currentTimeMillis > millisWhenToExitRetreatingState){
        distanceState = DistanceState::FAR ;

        DEBUG_DISTANCE_STATE_PRINTLN("Change to DistanceState::FAR");
      }
    break;
  }


  /* Viestin asettaminen -tilat */
  static unsigned long nextAllowedNoteStateChange=0;
  if(currentTimeMillis > nextAllowedNoteStateChange){
    switch (noteState) {
      case NoteState::NO_NOTE :
        if(isNoteDetected() == true){
          noteState = NoteState::INSERTING ;

          DEBUG_NOTE_STATE_PRINTLN("Change to NoteState::INSERTING");
          lcd->setText("Anna lupaus...", 1, currentTimeMillis, 2000);
          nextAllowedNoteStateChange = currentTimeMillis + 1000;
        }
      break;

      case NoteState::INSERTING :
        if(isNoteDetected() == false){
          noteState = NoteState::DROPPED ;
          millisWhenToExitDroppedState = currentTimeMillis + 5000;

          DEBUG_NOTE_STATE_PRINTLN("Change to NoteState::DROPPED");
          lcd->setText("Kiitos!", 1, currentTimeMillis, 2000);
          nextAllowedNoteStateChange = currentTimeMillis + 1000;
        }
      break;

      case NoteState::DROPPED :
        if(isNoteDetected() == true){
          noteState = NoteState::INSERTING ;

          DEBUG_NOTE_STATE_PRINTLN("Change to NoteState::INSERTING");
          lcd->setText("Anna lupaus...", 1, currentTimeMillis, 2000);
          nextAllowedNoteStateChange = currentTimeMillis + 1000;
        } 
        if(currentTimeMillis > millisWhenToExitDroppedState){
          noteState = NoteState::NO_NOTE ;

          DEBUG_NOTE_STATE_PRINTLN("Change to NoteState::NO_NOTE");
          nextAllowedNoteStateChange = currentTimeMillis + 1000;
        }
      break;
    }
  }
}