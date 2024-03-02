#ifndef LEDLIGHTS_H
#define LEDLIGHTS_H


#define LED_STICK_COUNT 5



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
#include "CalculationElementLink.h"



struct sLedStick {
  Adafruit_NeoPixel *neoPixel;
  CalculationElementLink *calculationElementLink;
};



class LedLights {

private:

  unsigned long currentTimeMillis = 0;
  unsigned long previousTimeMillis = 0;
  unsigned long deltaTimeMillis = 0;
  unsigned long loopSetColorsCounter = 0;
  NoteState noteState;
  DistanceState distanceState;

public:

  void setCalculationElementLink(byte index, CalculationElementLink *calculationElementLink);
  CalculationElementLink *getCalculationElementLink(byte index);



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

  double getCurrentTimeSeconds(void);
};


#endif  // LEDLIGHTS_H