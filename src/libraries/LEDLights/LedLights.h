#ifndef LEDLIGHTS_H
#define LEDLIGHTS_H

#include <Arduino.h>


#include "Adafruit_NeoPixel.h"
#ifdef __AVR__
#include <avr/power.h>
#endif

class LedLights {

private:


public:

  void init(void);
  void loopSetColors(unsigned long currentTimeMillis, byte noteState, byte distanceState);
  void loopShow(void);
};


#endif  // LEDLIGHTS_H