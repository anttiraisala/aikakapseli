#ifndef MVP_INITS_H
#define MVP_INITS_H

#include "LedLights.h"
extern LedLights ledLights;

#include "LedLightCalculationConstant.h"
#include "LedLightCalculationSine.h"

/* Asiakkaan etäisyys -tilat */
#include "distance_state.h"

/* Viestin asettaminen -tilat */
#include "note_state.h"





LedLightCalculationConstant *constantGreen = new LedLightCalculationConstant(0.0, 255.0, 0.0);
LedLightCalculationConstant *constantRed = new LedLightCalculationConstant(255.0, 0.0, 0.0);
LedLightCalculationSine *ledLightCalculationSine = new LedLightCalculationSine(1.0, 1.0 / 8.0, 0.4, 0.6);
LedLightCalculationSine *noteSlotCalculations = new LedLightCalculationSine(0.0, 1.0 / 4.92348572983475, 0.4, 0.6);

void coloring_DistanceStateFAR(void) {
  ledLights.setBrightness(30);

  CalculationElementPhaseMapping cepmSame;
  cepmSame.startPhase = 0.0;
  cepmSame.endPhase = 0.0;


  ledLights.setCalculations(0, constantGreen, cepmSame);
  //
  ledLights.setCalculations(5, constantGreen, cepmSame);

  CalculationElementPhaseMapping cepmSine0;
  double m = 12.0;
  cepmSine0.startPhase = m * 3.14159265359 / 60.0 * 0.0;
  cepmSine0.endPhase = m * 3.14159265359 / 60.0 * 9.0;
  CalculationElementPhaseMapping cepmSine1;
  cepmSine1.startPhase = m * 3.14159265359 / 60.0 * 10.0;
  cepmSine1.endPhase = m * 3.14159265359 / 60.0 * 19.0;
  CalculationElementPhaseMapping cepmSine2;
  cepmSine2.startPhase = m * 3.14159265359 / 60.0 * 20.0;
  cepmSine2.endPhase = m * 3.14159265359 / 60.0 * 29.0;
  CalculationElementPhaseMapping cepmSine3;
  cepmSine3.startPhase = m * 3.14159265359 / 60.0 * 30.0;
  cepmSine3.endPhase = m * 3.14159265359 / 60.0 * 39.0;
  CalculationElementPhaseMapping cepmSine4;
  cepmSine4.startPhase = m * 3.14159265359 / 60.0 * 40.0;
  cepmSine4.endPhase = m * 3.14159265359 / 60.0 * 49.0;
  CalculationElementPhaseMapping cepmSine5;
  cepmSine5.startPhase = m * 3.14159265359 / 60.0 * 50.0;
  cepmSine5.endPhase = m * 3.14159265359 / 60.0 * 59.0;



  ledLights.setCalculations(0, ledLightCalculationSine, cepmSine0);
  ledLights.setCalculations(1, ledLightCalculationSine, cepmSine1);
  ledLights.setCalculations(2, ledLightCalculationSine, cepmSine2);
  ledLights.setCalculations(3, ledLightCalculationSine, cepmSine3);
  ledLights.setCalculations(4, ledLightCalculationSine, cepmSine4);
  ledLights.setCalculations(5, ledLightCalculationSine, cepmSine5);
}

void calculations_NoNote(void) {
  CalculationElementPhaseMapping cepmNoteSlot0;
  cepmNoteSlot0.startPhase = 3.0 * 3.14159265359 / 19.0 * 0.0;
  cepmNoteSlot0.endPhase = 3.0 * 3.14159265359 / 19.0 * 9.0;
  CalculationElementPhaseMapping cepmNoteSlot1;
  cepmNoteSlot1.startPhase = 3.0 * 3.14159265359 / 19.0 * 10.0;
  cepmNoteSlot1.endPhase = 3.0 * 3.14159265359 / 19.0 * 19.0;
  //

  //
  ledLights.setCalculations(6, noteSlotCalculations, cepmNoteSlot0);
  ledLights.setCalculations(7, noteSlotCalculations, cepmNoteSlot1);
}

void calculations_Inserting(void) {
  CalculationElementPhaseMapping cepmNoteSlot0;
  cepmNoteSlot0.startPhase = 3.0 * 3.14159265359 / 19.0 * 0.0;
  cepmNoteSlot0.endPhase = 3.0 * 3.14159265359 / 19.0 * 9.0;
  CalculationElementPhaseMapping cepmNoteSlot1;
  cepmNoteSlot1.startPhase = 3.0 * 3.14159265359 / 19.0 * 10.0;
  cepmNoteSlot1.endPhase = 3.0 * 3.14159265359 / 19.0 * 19.0;
  //

  //
  ledLights.setCalculations(6, constantRed, cepmNoteSlot0);
  ledLights.setCalculations(7, constantRed, cepmNoteSlot1);
}

void calculations_Dropped(void) {
  CalculationElementPhaseMapping cepmNoteSlot0;
  cepmNoteSlot0.startPhase = 3.0 * 3.14159265359 / 19.0 * 0.0;
  cepmNoteSlot0.endPhase = 3.0 * 3.14159265359 / 19.0 * 9.0;
  CalculationElementPhaseMapping cepmNoteSlot1;
  cepmNoteSlot1.startPhase = 3.0 * 3.14159265359 / 19.0 * 10.0;
  cepmNoteSlot1.endPhase = 3.0 * 3.14159265359 / 19.0 * 19.0;
  //

  //
  ledLights.setCalculations(6, constantGreen, cepmNoteSlot0);
  ledLights.setCalculations(7, constantGreen, cepmNoteSlot1);
}


LedLightCalculationSine *ledLightCalculationSineRETREATING = new LedLightCalculationSine(1.0, 1.0 / 2.0, 0.4, 0.6);

void coloring_DistanceStateRETREATING(void) {
  ledLights.setBrightness(100);

  CalculationElementPhaseMapping cepmSame;
  cepmSame.startPhase = 0.0;
  cepmSame.endPhase = 0.0;


  ledLights.setCalculations(0, constantGreen, cepmSame);
  //
  ledLights.setCalculations(5, constantGreen, cepmSame);

  CalculationElementPhaseMapping cepmSine0;
  double m = 6.0;
  cepmSine0.startPhase = m * 3.14159265359 / 60.0 * 0.0;
  cepmSine0.endPhase = m * 3.14159265359 / 60.0 * 9.0;
  CalculationElementPhaseMapping cepmSine1;
  cepmSine1.startPhase = m * 3.14159265359 / 60.0 * 10.0;
  cepmSine1.endPhase = m * 3.14159265359 / 60.0 * 19.0;
  CalculationElementPhaseMapping cepmSine2;
  cepmSine2.startPhase = m * 3.14159265359 / 60.0 * 20.0;
  cepmSine2.endPhase = m * 3.14159265359 / 60.0 * 29.0;
  CalculationElementPhaseMapping cepmSine3;
  cepmSine3.startPhase = m * 3.14159265359 / 60.0 * 30.0;
  cepmSine3.endPhase = m * 3.14159265359 / 60.0 * 39.0;
  CalculationElementPhaseMapping cepmSine4;
  cepmSine4.startPhase = m * 3.14159265359 / 60.0 * 40.0;
  cepmSine4.endPhase = m * 3.14159265359 / 60.0 * 49.0;
  CalculationElementPhaseMapping cepmSine5;
  cepmSine5.startPhase = m * 3.14159265359 / 60.0 * 50.0;
  cepmSine5.endPhase = m * 3.14159265359 / 60.0 * 59.0;



  ledLights.setCalculations(0, ledLightCalculationSineRETREATING, cepmSine0);
  ledLights.setCalculations(1, ledLightCalculationSineRETREATING, cepmSine1);
  ledLights.setCalculations(2, ledLightCalculationSineRETREATING, cepmSine2);
  ledLights.setCalculations(3, ledLightCalculationSineRETREATING, cepmSine3);
  ledLights.setCalculations(4, ledLightCalculationSineRETREATING, cepmSine4);
  ledLights.setCalculations(5, ledLightCalculationSineRETREATING, cepmSine5);


  CalculationElementPhaseMapping cepmNoteSlot0;
  cepmNoteSlot0.startPhase = 3.0 * 3.14159265359 / 19.0 * 0.0;
  cepmNoteSlot0.endPhase = 3.0 * 3.14159265359 / 19.0 * 9.0;
  CalculationElementPhaseMapping cepmNoteSlot1;
  cepmNoteSlot1.startPhase = 3.0 * 3.14159265359 / 19.0 * 10.0;
  cepmNoteSlot1.endPhase = 3.0 * 3.14159265359 / 19.0 * 19.0;
  //

  //
  ledLights.setCalculations(6, noteSlotCalculations, cepmNoteSlot0);
  ledLights.setCalculations(7, noteSlotCalculations, cepmNoteSlot1);
}









LedLightCalculationSine *NEARledLightCalculationSine = new LedLightCalculationSine(1.0, 1.0 / 2.0, 0.4, 0.6);

void coloring_DistanceStateNEAR(void) {
  ledLights.setBrightness(255);

  CalculationElementPhaseMapping cepmSame;
  cepmSame.startPhase = 0.0;
  cepmSame.endPhase = 0.0;


  ledLights.setCalculations(0, constantGreen, cepmSame);
  //
  ledLights.setCalculations(5, constantGreen, cepmSame);

  CalculationElementPhaseMapping cepmSine0;
  double m = -2.0;
  cepmSine0.startPhase = m * 3.14159265359 / 60.0 * 0.0;
  cepmSine0.endPhase = m * 3.14159265359 / 60.0 * 9.0;
  CalculationElementPhaseMapping cepmSine1;
  cepmSine1.startPhase = m * 3.14159265359 / 60.0 * 10.0;
  cepmSine1.endPhase = m * 3.14159265359 / 60.0 * 19.0;
  CalculationElementPhaseMapping cepmSine2;
  cepmSine2.startPhase = m * 3.14159265359 / 60.0 * 20.0;
  cepmSine2.endPhase = m * 3.14159265359 / 60.0 * 29.0;
  CalculationElementPhaseMapping cepmSine3;
  cepmSine3.startPhase = m * 3.14159265359 / 60.0 * 30.0;
  cepmSine3.endPhase = m * 3.14159265359 / 60.0 * 39.0;
  CalculationElementPhaseMapping cepmSine4;
  cepmSine4.startPhase = m * 3.14159265359 / 60.0 * 40.0;
  cepmSine4.endPhase = m * 3.14159265359 / 60.0 * 49.0;
  CalculationElementPhaseMapping cepmSine5;
  cepmSine5.startPhase = m * 3.14159265359 / 60.0 * 50.0;
  cepmSine5.endPhase = m * 3.14159265359 / 60.0 * 59.0;



  ledLights.setCalculations(0, NEARledLightCalculationSine, cepmSine0);
  ledLights.setCalculations(1, NEARledLightCalculationSine, cepmSine1);
  ledLights.setCalculations(2, NEARledLightCalculationSine, cepmSine2);
  ledLights.setCalculations(3, NEARledLightCalculationSine, cepmSine3);
  ledLights.setCalculations(4, NEARledLightCalculationSine, cepmSine4);
  ledLights.setCalculations(5, NEARledLightCalculationSine, cepmSine5);


  CalculationElementPhaseMapping cepmNoteSlot0;
  cepmNoteSlot0.startPhase = 3.0 * 3.14159265359 / 19.0 * 0.0;
  cepmNoteSlot0.endPhase = 3.0 * 3.14159265359 / 19.0 * 9.0;
  CalculationElementPhaseMapping cepmNoteSlot1;
  cepmNoteSlot1.startPhase = 3.0 * 3.14159265359 / 19.0 * 10.0;
  cepmNoteSlot1.endPhase = 3.0 * 3.14159265359 / 19.0 * 19.0;
  //

  //
  ledLights.setCalculations(6, noteSlotCalculations, cepmNoteSlot0);
  ledLights.setCalculations(7, noteSlotCalculations, cepmNoteSlot1);
}


#endif  // MVP_INITS_H