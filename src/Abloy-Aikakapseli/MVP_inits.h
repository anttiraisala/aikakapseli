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








void coloring_DistaneStateFAR(void) {
  CalculationElementPhaseMapping cepmSame;
  cepmSame.startPhase = 0.0;
  cepmSame.endPhase = 0.0;

  LedLightCalculationConstant *constantGreen = new LedLightCalculationConstant(0.0, 255.0, 0.0);
  ledLights.setCalculations(0, constantGreen, cepmSame);
  //
  ledLights.setCalculations(5, constantGreen, cepmSame);

  CalculationElementPhaseMapping cepmSine0;
  cepmSine0.startPhase = 3.0 * 3.14159265359 / 60.0 * 0.0;
  cepmSine0.endPhase = 3.0 * 3.14159265359 / 60.0 * 9.0;
  CalculationElementPhaseMapping cepmSine1;
  cepmSine1.startPhase = 3.0 * 3.14159265359 / 60.0 * 10.0;
  cepmSine1.endPhase = 3.0 * 3.14159265359 / 60.0 * 19.0;
  CalculationElementPhaseMapping cepmSine2;
  cepmSine2.startPhase = 3.0 * 3.14159265359 / 60.0 * 20.0;
  cepmSine2.endPhase = 3.0 * 3.14159265359 / 60.0 * 29.0;
  CalculationElementPhaseMapping cepmSine3;
  cepmSine3.startPhase = 3.0 * 3.14159265359 / 60.0 * 30.0;
  cepmSine3.endPhase = 3.0 * 3.14159265359 / 60.0 * 39.0;
  CalculationElementPhaseMapping cepmSine4;
  cepmSine4.startPhase = 3.0 * 3.14159265359 / 60.0 * 40.0;
  cepmSine4.endPhase = 3.0 * 3.14159265359 / 60.0 * 49.0;
  CalculationElementPhaseMapping cepmSine5;
  cepmSine5.startPhase = 3.0 * 3.14159265359 / 60.0 * 50.0;
  cepmSine5.endPhase = 3.0 * 3.14159265359 / 60.0 * 59.0;

  LedLightCalculationSine *ledLightCalculationSine = new LedLightCalculationSine(1.0, 1.0 / 2.0, 0.4, 0.6);

  ledLights.setCalculations(0, ledLightCalculationSine, cepmSine0);
  ledLights.setCalculations(1, ledLightCalculationSine, cepmSine1);
  ledLights.setCalculations(2, ledLightCalculationSine, cepmSine2);
  ledLights.setCalculations(3, ledLightCalculationSine, cepmSine3);
  ledLights.setCalculations(4, ledLightCalculationSine, cepmSine4);
  ledLights.setCalculations(5, ledLightCalculationSine, cepmSine5);


  CalculationElementPhaseMapping cepmNoteSlot0;
  cepmNoteSlot0.startPhase = 3.0 * 3.14159265359 / 19.0 * 0.0;
  cepmNoteSlot0.endPhase = 3.0 * 3.14159265359 / 19.0 * 9.0;
  CalculationElementPhaseMapping cepmNoteSlot1;
  cepmNoteSlot1.startPhase = 3.0 * 3.14159265359 / 19.0 * 10.0;
  cepmNoteSlot1.endPhase = 3.0 * 3.14159265359 / 19.0 * 19.0;
  //
  LedLightCalculationSine *noteSlotCalculations = new LedLightCalculationSine(0.0, 1.0 / 4.92348572983475, 0.4, 0.6);
  //
  ledLights.setCalculations(6, noteSlotCalculations, cepmNoteSlot0);
  ledLights.setCalculations(7, noteSlotCalculations, cepmNoteSlot1);
}

#endif // MVP_INITS_H