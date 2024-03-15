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

CrossDissolve *CrossDissolve::setUseSmoothStep(boolean useSmoothStep) {
  this->useSmoothStep = useSmoothStep;
  return this;
}
CrossDissolve *CrossDissolve::setSmoothStepA(double smoothStepA) {
  this->smoothStepA = smoothStepA;
  return this;
}
CrossDissolve *CrossDissolve::setSmoothStepB(double smoothStepB) {
  this->smoothStepB = smoothStepB;
  return this;
}

LedLightCalculationValue CrossDissolve::getValue(unsigned long loopSetColorsCounter, double currentTimeSeconds, double relativePhase) {

  LedLightCalculationValue controlValue;
  if (previousLoopSetColorsCounter != loopSetColorsCounter) {
    controlValue = controlElementLink->getCalculationElement()->getValue(loopSetColorsCounter, currentTimeSeconds, controlElementLink->getMappedRelativePhase(relativePhase));
    previousInputValue = controlValue;
    previousLoopSetColorsCounter = loopSetColorsCounter;
  } else {
    controlValue = previousInputValue;
  }

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

  if (useSmoothStep == true) {
    double t = min(max((controlValue.getValueV() - smoothStepA) / (smoothStepB - smoothStepA), 0.0), 1.0);
    controlValue.setValue(t * t * (3.0 - 2.0 * t));
  }

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

  boolean useSmoothStep = false;
  double smoothStepA = 0.0;
  double smoothStepB = 1.0;
*/