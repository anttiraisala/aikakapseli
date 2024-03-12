#include "SweepingDot.h"



SweepingDot::SweepingDot(void) {
  previousTimeSeconds = 0.0;
  internalTimeSeconds = 0.0;
}

SweepingDot *SweepingDot::setRotateInsteadOfSweep(boolean rotateInsteadOfSweep) {
  this->rotateInsteadOfSweep = rotateInsteadOfSweep;
  return this;
}

SweepingDot *SweepingDot::setSpeedRatioElement(CalculationElementLink *speedRatioElementLink) {
  this->speedRatioElementLink = speedRatioElementLink;
  return this;
}

LedLightCalculationValue SweepingDot::getValue(unsigned long loopSetColorsCounter, double currentTimeSeconds, double relativePhase) {

  LedLightCalculationValue speedRatioValue = speedRatioElementLink->getCalculationElement()->getValue(loopSetColorsCounter, currentTimeSeconds, speedRatioElementLink->getMappedRelativePhase(relativePhase));
  double speedRatio = speedRatioValue.getValueV();
  internalTimeSeconds += (currentTimeSeconds - previousTimeSeconds) * speedRatio;
  previousTimeSeconds = currentTimeSeconds;

  double timeDecimalPart = internalTimeSeconds - ((double)((long)(internalTimeSeconds)));
  if(rotateInsteadOfSweep == true){
    ledLightCalculationValue.setValue(timeDecimalPart);
    return ledLightCalculationValue;
  }

  if(timeDecimalPart>=0.5){
    ledLightCalculationValue.setValue(1.0-timeDecimalPart);
  } else {
    ledLightCalculationValue.setValue(timeDecimalPart);
  }


  //Serial.println(timeDecimalPart);


  return ledLightCalculationValue;
}

/*
  double previousTimeSeconds = 0.0;
  double internalTimeSeconds = 0.0;
  double speedRatio = 1.0;
  */