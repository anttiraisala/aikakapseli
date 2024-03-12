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
  double dotXLocation = timeDecimalPart;
  if (speedRatio < 0.0) {
    dotXLocation = 1.0 + dotXLocation;
  }

  if (rotateInsteadOfSweep == false) {
    dotXLocation = dotXLocation * 2.0;

    if (dotXLocation >= 1.0) {
      dotXLocation = 2.0 - dotXLocation;
    }
  }
  /*
    Serial.print(dotXLocation);
  Serial.print(" ");
*/
  double differenceFromDotXLocation = dotXLocation - relativePhase;
  if (differenceFromDotXLocation < 0.0) {
    differenceFromDotXLocation = -1.0 * differenceFromDotXLocation;
  }

  differenceFromDotXLocation = 1.0 - differenceFromDotXLocation;



  differenceFromDotXLocation = pow(differenceFromDotXLocation, 8.0);

  ledLightCalculationValue.setValue(differenceFromDotXLocation);







  //Serial.println(timeDecimalPart);


  return ledLightCalculationValue;
}

/*
  double previousTimeSeconds = 0.0;
  double internalTimeSeconds = 0.0;
  double speedRatio = 1.0;
  */