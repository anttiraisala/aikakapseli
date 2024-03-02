#include "LedLightCalculationConstant.h"
#include "HelperFunctions.h"

LedLightCalculationConstant::LedLightCalculationConstant() {}

LedLightCalculationConstant::LedLightCalculationConstant(double valueV) {
  this->ledLightCalculationValue.setValue(valueV);
}

LedLightCalculationConstant::LedLightCalculationConstant(double valueR, double valueG, double valueB) {
  this->ledLightCalculationValue.setValue(valueR, valueG, valueB);
}

LedLightCalculationValue LedLightCalculationConstant::getValue(unsigned long loopSetColorsCounter, double currentTimeSeconds, double relativePhase){
  return this->getValue();
}

LedLightCalculationValue LedLightCalculationConstant::getValue(void){
  return this->ledLightCalculationValue;
}

void LedLightCalculationConstant::debugPrint(void) {
  Serial.println("\nLedLightCalculationConstant::debugPrint -begins");
  ledLightCalculationValue.debugPrint();
  Serial.println("LedLightCalculationConstant::debugPrint -ends\n");
}
