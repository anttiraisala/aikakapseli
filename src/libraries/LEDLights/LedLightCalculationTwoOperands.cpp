#include "LedLightCalculationTwoOperands.h"

LedLightCalculationTwoOperands::LedLightCalculationTwoOperands(LedLightCalculationTwoOperandsOperation operation, LedLightCalculationElement elementA, LedLightCalculationElement elementB) {
  this->operation = operation;
  this->elementA = elementA;
  this->elementB = elementB;
}

LedLightCalculationValue LedLightCalculationTwoOperands::getValue(double currentTimeSeconds, double relativePhase, CalculationElementPhaseMapping calculationElementPhaseMapping) {


  return this->ledLightCalculationValue;
}