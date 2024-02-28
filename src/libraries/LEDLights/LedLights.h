#ifndef LEDLIGHTS_H
#define LEDLIGHTS_H

#include <Arduino.h>

/* Asiakkaan etäisyys -tilat */
#include "distance_state.h"

/* Viestin asettaminen -tilat */
#include "note_state.h"

#include "Adafruit_NeoPixel.h"
#ifdef __AVR__
#include <avr/power.h>
#endif

/* Tällä lasketaan ledien värit */
#include "LedLightCalculationElement.h"



struct sLedStick {
  Adafruit_NeoPixel *neoPixel;
  CalculationElementPhaseMapping calculationElementPhaseMapping;
  LedLightCalculationElement *calculationElement;
};



class LedLights {

private:

  unsigned long previousTimeMillis = 0;
  unsigned long deltaTimeMillis = 0;
  NoteState noteState;
  DistanceState distanceState;

public:



  void setCalculations(byte index, LedLightCalculationElement *calculationElement, CalculationElementPhaseMapping calculationElementPhaseMapping);

#define LED_STICK_COUNT 8

  sLedStick sLedSticks[LED_STICK_COUNT];

  LedLights(void);

  void init(void);
  void setLedStick(byte index, byte pin);
  void setLightsToZero(void);
  void setLightsToRandom(void);
  void loopSetColors(unsigned long currentTimeMillis, NoteState noteState, DistanceState distanceState);
  void loopShow(void);

  void debugPrintLedSticks(void);
  void setLightsToTestPattern(void);
};


#endif  // LEDLIGHTS_H