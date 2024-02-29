#ifndef LEDLIGHT_CALCULATION_SINE_H
#define LEDLIGHT_CALCULATION_SINE_H

#include "LedLightCalculationElement.h"

class LedLightCalculationSine : public LedLightCalculationElement {
public:
  // Constructor
  LedLightCalculationSine();
  LedLightCalculationSine(double phase, double frequency, double amplitude, double offset);

  void setParameters(double phase, double frequency, double amplitude, double offset);
  LedLightCalculationValue getValue(double currentTimeSeconds, double relativePhase, CalculationElementPhaseMapping calculationElementPhaseMapping) override;

private:
  double phase = 0.0;
  double frequency = 1.0;
  double amplitude = 1.0;
  double offset = 0.0;
};



#endif  // LEDLIGHT_CALCULATION_SINE_H