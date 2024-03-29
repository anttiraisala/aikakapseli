#include "SweepingDot.h"



SweepingDot::SweepingDot(void) {
  previousTimeSeconds = 0.0;
  internalTimeSeconds = -1000.0;
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
  double timeDifference = (currentTimeSeconds - previousTimeSeconds) * speedRatio;
  internalTimeSeconds += timeDifference;
  previousTimeSeconds = currentTimeSeconds;

  double timeDecimalPart = 0.0;
  if (internalTimeSeconds >= 0.0) {
    timeDecimalPart = internalTimeSeconds - ((double)((long)(internalTimeSeconds)));
  } else {
    double t2 = -1.0 * internalTimeSeconds;
    timeDecimalPart = 1.0 - (t2 - ((double)((long)(t2))));
  }
  double dotXLocation = timeDecimalPart;

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