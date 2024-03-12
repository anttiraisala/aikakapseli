#ifndef SWEEPING_DOT_H
#define SWEEPING_DOT_H

#include "LedLightCalculationElement.h"
#include "CalculationElementLink.h"
#include "HelperFunctions.h"


class SweepingDot : public LedLightCalculationElement {
public:
  SweepingDot(void);
  SweepingDot *setRotateInsteadOfSweep(boolean rotateInsteadOfSweep);
  SweepingDot *setSpeedRatioElement(CalculationElementLink *speedRatioElementLink);
  LedLightCalculationValue getValue(unsigned long loopSetColorsCounter, double currentTimeSeconds, double relativePhase);

  void debugPrint(void);

private:
  double previousTimeSeconds = 0.0;
  double internalTimeSeconds = 0.0;
  CalculationElementLink *speedRatioElementLink;

  boolean rotateInsteadOfSweep = false;
};

#endif  // CALCULATION_SIMPLEX_NOISE_H
