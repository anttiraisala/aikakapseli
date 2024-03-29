#ifndef LEDLIGHT_CALCULATION_CONSTANT_H
#define LEDLIGHT_CALCULATION_CONSTANT_H

#include "LedLightCalculationElement.h"

class LedLightCalculationConstant : public LedLightCalculationElement {
public:
  // Constructor
  LedLightCalculationConstant();
  LedLightCalculationConstant(double valueV);
  LedLightCalculationConstant(double valueR, double valueG, double valueB);

  LedLightCalculationConstant *setValue(double valueR, double valueG, double valueB);
  LedLightCalculationConstant *setValue(double valueV);

  // Override getValue to calculate and return a LedLightCalculationElement based on relativePhase and value_
  LedLightCalculationValue getValue(unsigned long loopSetColorsCounter, double currentTimeSeconds, double relativePhase) override;
  LedLightCalculationValue getValue();

  void debugPrint(void);

private:
  
};



#endif  // LEDLIGHT_CALCULATION_CONSTANT_H
