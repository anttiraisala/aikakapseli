#include "LedLightCalculationConstant.h"

LedLightCalculationConstant::LedLightCalculationConstant() {}

LedLightCalculationValue LedLightCalculationConstant::getValue(double relativePhase, CalculationElementPhaseMapping calculationElementPhaseMapping){
  return this->getValue();
}

LedLightCalculationValue LedLightCalculationConstant::getValue(void){
  return this->ledLightCalculationValue;
}
