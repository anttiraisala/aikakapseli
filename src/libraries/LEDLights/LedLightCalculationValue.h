#ifndef LEDLIGHT_CALCULATION_VALUE_H
#define LEDLIGHT_CALCULATION_VALUE_H

#include "LedLightCalculationElement.h"

// Include necessary headers for your LedLightCalculationValue implementation
// (e.g., math libraries, data structures)

class LedLightCalculationValue : public LedLightCalculationElement {
public:
  // Constructor
  LedLightCalculationValue(double value);

  // Override getValue to calculate and return a LedLightCalculationElement based on relativePhase and value_
  LedLightCalculationElement getValue(double relativePhase, CalculationElementPhaseMapping calculationElementPhaseMapping) override;

private:
  double value;

  double valueR;
  double valueG;
  double valueB;

  bool isValue;
  bool isColor;  
};

#endif  // LEDLIGHT_CALCULATION_VALUE_H