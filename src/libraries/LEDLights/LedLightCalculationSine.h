#ifndef LEDLIGHT_CALCULATION_SINE_H
#define LEDLIGHT_CALCULATION_SINE_H

#include "LedLightCalculationElement.h"

class LedLightCalculationSine : public LedLightCalculationElement {
public:
  // Constructor
  LedLightCalculationSine();
  LedLightCalculationSine(double timeRatio, double phase, double frequency, double amplitude, double offset);

  void setParameters(double timeRatio, double phase, double frequency, double amplitude, double offset);
  LedLightCalculationValue getValue(unsigned long loopSetColorsCounter, double currentTimeSeconds, double relativePhase) override;

private:
  double timeRatio = 1.0;
  double phase = 0.0;
  double frequency = 1.0;
  double amplitude = 1.0;
  double offset = 0.0;

  double previousTimeSeconds = 0.0;
  double deltaTimeSeconds = 0.0;
  double internalTimeSeconds = 0.0;
  unsigned long loopSetColorsCounter = 0;
};



#endif  // LEDLIGHT_CALCULATION_SINE_H