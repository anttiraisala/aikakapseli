#ifndef LEDLIGHT_CALCULATION_ELEMENT_H
#define LEDLIGHT_CALCULATION_ELEMENT_H

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

#include <Arduino.h>

/* Asiakkaan etäisyys -tilat */
#include "distance_state.h"

/* Viestin asettaminen -tilat */
#include "note_state.h"

#include "LedLightCalculationValue.h"

struct CalculationElementPhaseMapping {
  double startPhase = 0.0;
  double endPhase = 2.0*3.14159265359;
};

class LedLightCalculationElement {
public:

  CalculationElementPhaseMapping calculationElementPhaseMapping;

  virtual ~LedLightCalculationElement() {}  // Virtual destructor for proper object cleanup in inheritance
  virtual LedLightCalculationValue getValue(double currentTimeSeconds, double relativePhase, CalculationElementPhaseMapping calculationElementPhaseMapping) {}
  void setValue(LedLightCalculationValue value){
    this->ledLightCalculationValue = value;
  }

private:

protected:
  LedLightCalculationValue ledLightCalculationValue;
};


#endif  // LEDLIGHT_CALCULATION_ELEMENT_H