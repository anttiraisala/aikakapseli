#ifndef THRESHOLD_H
#define THRESHOLD_H

#include "LedLightCalculationElement.h"
#include "CalculationElementLink.h"
#include "HelperFunctions.h"


class Threshold : public LedLightCalculationElement {
public:
  Threshold(void);
  Threshold *setOutputLowLevel(double outputLowLevel);
  Threshold *setOutputHighLevel(double outputHighLevel);
  Threshold *setThresholdLevelForHigh(double thresholdLevelForHigh);
  Threshold *setInputElement(CalculationElementLink *inputElementLink);
  LedLightCalculationValue getValue(unsigned long loopSetColorsCounter, double currentTimeSeconds, double relativePhase);

  void debugPrint(void);

private:
  double outputLowLevel = 0.0;
  double outputHighLevel = 1.0;
  double thresholdLevelForHigh = 0.5;
  CalculationElementLink *inputElementLink;

  unsigned long previousLoopSetColorsCounter = 0;
  LedLightCalculationValue previousInputValue;
};

#endif  // THRESHOLD_H
