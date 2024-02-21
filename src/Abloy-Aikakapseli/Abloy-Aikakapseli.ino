
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



// Tällä pidetään kirjaa kuluneista millisekunneista
long currentTimeMillis = 0;
//
long nextMillisTo_checkForStateChanges=0;
long nextMillisTo_printState=0;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  DEBUG_PRINTLN("setup()");
}





void loop() {
  // put your main code here, to run repeatedly:

  currentTimeMillis = millis();

  if(currentTimeMillis > nextMillisTo_checkForStateChanges)
  {
    nextMillisTo_checkForStateChanges = currentTimeMillis + 10 ;
    checkForStateChanges();
  }

  if(currentTimeMillis > nextMillisTo_printState)
  {
    nextMillisTo_printState = currentTimeMillis + 250 ;
    DEBUG_DISTANCE_STATE_PRINTLN(getCurrentDistanceStateString(distanceState));
    DEBUG_NOTE_STATE_PRINTLN(getCurrentNoteStateString(noteState));
  }

}

void checkForStateChanges(){

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
        millisWhenToExitRetreatingState = currentTimeMillis + 10000;

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
    switch (noteState) {
    case NoteState::NO_NOTE :
      if(isNoteDetected() == true){
        noteState = NoteState::INSERTING ;

        DEBUG_NOTE_STATE_PRINTLN("Change to NoteState::INSERTING");
      }
    break;

    case NoteState::INSERTING :
      if(isNoteDetected() == false){
        noteState = NoteState::DROPPED ;
        millisWhenToExitDroppedState = currentTimeMillis + 5000;

        DEBUG_NOTE_STATE_PRINTLN("Change to NoteState::DROPPED");
      }
    break;

    case NoteState::DROPPED :
      if(isNoteDetected() == true){
        noteState = NoteState::INSERTING ;

        DEBUG_NOTE_STATE_PRINTLN("Change to NoteState::INSERTING");
      } 
      if(currentTimeMillis > millisWhenToExitDroppedState){
        noteState = NoteState::NO_NOTE ;

        DEBUG_NOTE_STATE_PRINTLN("Change to NoteState::NO_NOTE");
      }
    break;
  }

}
