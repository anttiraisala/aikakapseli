#include "LedLightCalculationConstant.h"

LedLightCalculationConstant::LedLightCalculationConstant() {}

LedLightCalculationConstant::LedLightCalculationConstant(double valueV) {
  this->ledLightCalculationValue.setValue(valueV);
}

LedLightCalculationConstant::LedLightCalculationConstant(double valueR, double valueG, double valueB) {
  this->ledLightCalculationValue.setValue(valueR, valueG, valueB);
}

LedLightCalculationValue LedLightCalculationConstant::getValue(double relativePhase, CalculationElementPhaseMapping calculationElementPhaseMapping){
  return this->getValue();
}

LedLightCalculationValue LedLightCalculationConstant::getValue(void){
  return this->ledLightCalculationValue;
}
