#include "LedLightCalculationConstant.h"
#include "HelperFunctions.h"

LedLightCalculationConstant::LedLightCalculationConstant() {}

LedLightCalculationConstant::LedLightCalculationConstant(double valueV) {
  this->ledLightCalculationValue.setValue(valueV);
}

LedLightCalculationConstant::LedLightCalculationConstant(double valueR, double valueG, double valueB) {
  this->ledLightCalculationValue.setValue(valueR, valueG, valueB);
}

LedLightCalculationConstant *LedLightCalculationConstant::setValue(double valueR, double valueG, double valueB) {
  this->ledLightCalculationValue.setValue(valueR, valueG, valueB);
  return this;
}

LedLightCalculationConstant *LedLightCalculationConstant::setValue(double valueV) {
  this->ledLightCalculationValue.setValue(valueV);
  return this;
}



LedLightCalculationValue LedLightCalculationConstant::getValue(unsigned long loopSetColorsCounter, double currentTimeSeconds, double relativePhase){
  return this->getValue();
}

LedLightCalculationValue LedLightCalculationConstant::getValue(void){
  return this->ledLightCalculationValue;
}

void LedLightCalculationConstant::debugPrint(void) {
  Serial.println(F("\nLedLightCalculationConstant::debugPrint -begins"));
  ledLightCalculationValue.debugPrint();
  Serial.println(F("LedLightCalculationConstant::debugPrint -ends\n"));
}
