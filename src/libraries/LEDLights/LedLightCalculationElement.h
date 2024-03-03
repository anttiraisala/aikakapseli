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
#include "LedLightCalculationElement.h"

extern DistanceState currentDistanceState;
extern NoteState currentNoteState;


class LedLightCalculationElement {
public:

  virtual ~LedLightCalculationElement() {}  // Virtual destructor for proper object cleanup in inheritance
  virtual LedLightCalculationValue getValue(unsigned long loopSetColorsCounter, double currentTimeSeconds, double relativePhase) {}
  void setValue(LedLightCalculationValue value) {
    this->ledLightCalculationValue = value;
  }

  LedLightCalculationElement* setCalculationElementPhaseMapping(double startPhase, double endPhase);
  LedLightCalculationElement* setCalculationElementConstantMapping(double constantPhase);
  double getMappedPhase(double relativePhase);


private:
  double startPhase = 0.0;
  double endPhase = 2.0 * 3.14159265359;
  double constantPhase = 0.0;
  boolean bHasConstantMapping = false;

protected:
  LedLightCalculationValue ledLightCalculationValue;
};


#endif  // LEDLIGHT_CALCULATION_ELEMENT_H