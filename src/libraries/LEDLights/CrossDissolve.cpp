#include "CrossDissolve.h"
#include "LedLightCalculationTwoOperands.h"

CrossDissolve::CrossDissolve(void) {
  calculationTwoOperands = new LedLightCalculationTwoOperands();
  llc_one = new LedLightCalculationConstant(1.0);
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
  LedLightCalculationTwoOperands *calculationTwoOperands;
  LedLightCalculationConstant *llc_one;
*/
LedLightCalculationTwoOperands::performOperation();

}

void CrossDissolve::debugPrint(void) {}

/*
  CalculationElementLink *controlElementLink;
  CalculationElementLink *input0ElementLink;
  CalculationElementLink *input1ElementLink;
*/