#ifndef LEDLIGHT_CALCULATION_ELEMENT_H
#define LEDLIGHT_CALCULATION_ELEMENT_H

#include <Arduino.h>

/* Asiakkaan etäisyys -tilat */
#include "distance_state.h"

/* Viestin asettaminen -tilat */
#include "note_state.h"

#include "LedLightCalculationValue.h"

struct CalculationElementPhaseMapping {
  double startPhase = 0.0;
  double endPhase = 0.0;
};

class LedLightCalculationElement {
public:

  CalculationElementPhaseMapping calculationElementPhaseMapping;

  virtual ~LedLightCalculationElement() {}  // Virtual destructor for proper object cleanup in inheritance
  virtual LedLightCalculationValue getValue(double relativePhase, CalculationElementPhaseMapping calculationElementPhaseMapping) {}

private:

protected:
  LedLightCalculationValue ledLightCalculationValue;
};


#endif  // LEDLIGHT_CALCULATION_ELEMENT_H