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


public:

  void init(void);
  void loopSetColors(unsigned long currentTimeMillis, NoteState noteState, DistanceState distanceState);
  void loopShow(void);
};


#endif  // LEDLIGHTS_H