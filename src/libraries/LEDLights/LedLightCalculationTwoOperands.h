#ifndef LEDLIGHT_CALCULATION_TWO_OPERANDS_H
#define LEDLIGHT_CALCULATION_TWO_OPERANDS_H

#include "LedLightCalculationElement.h"
#include "CalculationElementLink.h"

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
  CalculationElementLink *elementLinkA;
  CalculationElementLink *elementLinkB;

public:
  LedLightCalculationTwoOperands(LedLightCalculationTwoOperandsOperation operation, CalculationElementLink *elementLinkA, CalculationElementLink *elementLinkB);
  LedLightCalculationValue getValue(unsigned long loopSetColorsCounter, double currentTimeSeconds, double relativePhase);

  LedLightCalculationTwoOperands *setOperation(LedLightCalculationTwoOperandsOperation operation);
};

#endif  // LEDLIGHT_CALCULATION_TWO_OPERANDS_H