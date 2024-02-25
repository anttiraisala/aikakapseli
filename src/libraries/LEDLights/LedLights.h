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

class LedLights {

private:

  unsigned long previousTimeMillis = 0;
  unsigned long deltaTimeMillis = 0;
  NoteState noteState;
  DistanceState distanceState;

  struct sLedStick {
    Adafruit_NeoPixel *neoPixel;
  };

  #define LED_STICK_COUNT 6

  sLedStick sLedSticks[LED_STICK_COUNT];

public:

  LedLights(void);

  void init(void);
  void setLedStick(byte index, byte pin);
  void setLightsToZero(void);
  void setLightsToTestPattern(void);
  void loopSetColors(unsigned long currentTimeMillis, NoteState noteState, DistanceState distanceState);
  void loopShow(void);

  void debugPrintLedSticks(void);
};


#endif  // LEDLIGHTS_H