#include "Threshold.h"

Threshold::Threshold(void) {}

Threshold *Threshold::setOutputLowLevel(double outputLowLevel) {
  this->outputLowLevel = outputLowLevel;
  return this;
}

Threshold *Threshold::setOutputHighLevel(double outputHighLevel) {
  this->outputHighLevel = outputHighLevel;
  return this;
}

Threshold *Threshold::setThresholdLevelForHigh(double thresholdLevelForHigh) {
  this->thresholdLevelForHigh = thresholdLevelForHigh;
  return this;
}

Threshold *Threshold::setInputElement(CalculationElementLink *inputElementLink) {
  this->inputElementLink = inputElementLink;
  return this;
}

LedLightCalculationValue Threshold::getValue(unsigned long loopSetColorsCounter, double currentTimeSeconds, double relativePhase) {
  LedLightCalculationValue inputValue = inputElementLink->getCalculationElement()->getValue(loopSetColorsCounter, currentTimeSeconds, inputElementLink->getMappedRelativePhase(relativePhase));

  if (inputValue.getValueV() >= thresholdLevelForHigh) {
    ledLightCalculationValue.setValue(outputHighLevel);
  } else {
    ledLightCalculationValue.setValue(outputLowLevel);
  }

  return ledLightCalculationValue;
}



/*
  double outputLowLevel = 0.0;
  double outputHighLevel = 1.0;
  double thresholdLevelForHigh = 0.5;
  CalculationElementLink *inputElementLink;
  */