#ifndef CALCULATION_SIMPLEX_NOISE_H
#define CALCULATION_SIMPLEX_NOISE_H

#include "LedLightCalculationElement.h"
#include "CalculationElementLink.h"
#include "HelperFunctions.h"
#include "SimplexNoise.h"

class CalculationSimplexNoise : public LedLightCalculationElement {
public:
  CalculationSimplexNoise(void);
  CalculationSimplexNoise *setXRatio(double xRatio);
  CalculationSimplexNoise *setYRatio(double yRatio);
  CalculationSimplexNoise *setOutputAmplitude(double outputAmplitude);
  CalculationSimplexNoise *setOutputOffset(double outputOffset);
  LedLightCalculationValue getValue(unsigned long loopSetColorsCounter, double currentTimeSeconds, double relativePhase);

  void debugPrint(void);

private:
  /* Simplex noise x-axis is relativePhase and from 0 to 2*PI is mapped as from 0 to 1,
    x ismultiplied byt xRatio (default = 1.0) .
  y-axis goes from 0 to 1 in 1 seconds.
    y ismultiplied byt yRatio (default = 1.0) .
 */
  double xRatio = 1.0;
  double yRatio = 1.0;
  SimplexNoise sn;

/* Simplex noise returns values from -1 to 1. The output is first multiplied by outputAmplitude and then offset by outputOffset */
  double outputAmplitude = 1.0;
  double outputOffset = 0.0;
};

#endif  // CALCULATION_SIMPLEX_NOISE_H
