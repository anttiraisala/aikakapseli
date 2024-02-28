#ifndef LEDLIGHT_CALCULATION_CONSTANT_H
#define LEDLIGHT_CALCULATION_CONSTANT_H

#include "LedLightCalculationElement.h"

class LedLightCalculationConstant : public LedLightCalculationElement {
public:
  // Constructor
  LedLightCalculationConstant();

  // Override getValue to calculate and return a LedLightCalculationElement based on relativePhase and value_
  LedLightCalculationValue getValue(double relativePhase, CalculationElementPhaseMapping calculationElementPhaseMapping) override;
  LedLightCalculationValue getValue();

private:
  
};



#endif  // LEDLIGHT_CALCULATION_CONSTANT_H
