#include "CrossDissolve.h"
#include "LedLightCalculationTwoOperands.h"

CrossDissolve::CrossDissolve(void) {
}

CrossDissolve *CrossDissolve::setControlElement(CalculationElementLink *controlElementLink) {
  this->controlElementLink = controlElementLink;
}
CrossDissolve *CrossDissolve::setInput0Element(CalculationElementLink *input0ElementLink) {
  this->input0ElementLink = input0ElementLink;
}
CrossDissolve *CrossDissolve::setInput1Element(CalculationElementLink *input1ElementLink) {
  this->input1ElementLink = input1ElementLink;
}

LedLightCalculationValue CrossDissolve::getValue(unsigned long loopSetColorsCounter, double currentTimeSeconds, double relativePhase) {

  LedLightCalculationValue controlValue = controlElementLink->getCalculationElement()->getValue(loopSetColorsCounter, currentTimeSeconds, controlElementLink->getMappedRelativePhase(relativePhase));
  LedLightCalculationValue input0Value = input0ElementLink->getCalculationElement()->getValue(loopSetColorsCounter, currentTimeSeconds, input0ElementLink->getMappedRelativePhase(relativePhase));
  LedLightCalculationValue input1Value = input1ElementLink->getCalculationElement()->getValue(loopSetColorsCounter, currentTimeSeconds, input1ElementLink->getMappedRelativePhase(relativePhase));
/*
  Serial.println(F("\nCrossDissolve::getValue - debug begins"));
  Serial.println(F("controlValue"));
  controlValue.debugPrint();
  Serial.println(F("input0Value"));
  input0Value.debugPrint();
  Serial.println(F("input1Value"));
  input1Value.debugPrint();
  Serial.println(F("\nCrossDissolve::getValue - debug ends"));
  delay(5000);
*/
  /*
  LedLightCalculationTwoOperands *calculationTwoOperands;
  LedLightCalculationConstant *llc_one;

//LedLightCalculationTwoOperands::performOperation();
*/
/*
  Serial.println(F("\nLedLightCalculationTwoOperands::performOperation - before"));
  */
  LedLightCalculationTwoOperands::performOperation(&ledLightCalculationValue, LedLightCalculationTwoOperandsOperation::CROSS_DISSOLVE, &controlValue, &input0Value, &input1Value);
 /* Serial.println(F("performOperation's value"));
  ledLightCalculationValue.debugPrint();
  Serial.println(F("\nLedLightCalculationTwoOperands::performOperation - after"));
  delay(5000);
*/
  return ledLightCalculationValue;
}

void CrossDissolve::debugPrint(void) {}

/*
  CalculationElementLink *controlElementLink;
  CalculationElementLink *input0ElementLink;
  CalculationElementLink *input1ElementLink;
*/