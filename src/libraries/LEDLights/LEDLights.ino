#include "LedLights.h"

/* Asiakkaan etäisyys -tilat */
#include "distance_state.h"
DistanceState distanceState = DistanceState::FAR ;


/* Viestin asettaminen -tilat */
#include "note_state.h"
NoteState noteState = NoteState::NO_NOTE;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  delay(2000);

}

void loop() {
  // put your main code here, to run repeatedly:

}
