#ifndef LEDLIGHT_CALCULATION_TWO_OPERANDS_H
#define LEDLIGHT_CALCULATION_TWO_OPERANDS_H

#include "LedLightCalculationElement.h"

enum class LedLightCalculationTwoOperandsOperation {
  ADD,
  SUBTRACT,
  MULTIPLY,
  DIVIDE,
  POW,
  MAX,
  MIN
};


class LedLightCalculationTwoOperands : public LedLightCalculationElement {
private:
  LedLightCalculationTwoOperandsOperation operation;
  LedLightCalculationElement elementA;
  LedLightCalculationElement elementB;

public:
  LedLightCalculationTwoOperands(LedLightCalculationTwoOperandsOperation operation, LedLightCalculationElement elementA, LedLightCalculationElement elementB);
  LedLightCalculationValue getValue(double currentTimeSeconds, double relativePhase, CalculationElementPhaseMapping calculationElementPhaseMapping);
};

#endif  // LEDLIGHT_CALCULATION_TWO_OPERANDS_H