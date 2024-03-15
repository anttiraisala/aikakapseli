#include "CalculationSimplexNoise.h"

CalculationSimplexNoise::CalculationSimplexNoise(void) {
  sn.init();
}
CalculationSimplexNoise *CalculationSimplexNoise::CalculationSimplexNoise::setXRatio(double xRatio) {
  this->xRatio = xRatio;
  return this;
}
CalculationSimplexNoise *CalculationSimplexNoise::CalculationSimplexNoise::setYRatio(double yRatio) {
  this->yRatio = yRatio;
  return this;
}
CalculationSimplexNoise *CalculationSimplexNoise::setOutputAmplitude(double outputAmplitude) {
  this->outputAmplitude = outputAmplitude;
  return this;
}
CalculationSimplexNoise *CalculationSimplexNoise::setOutputOffset(double outputOffset) {
  this->outputOffset = outputOffset;
  return this;
}

LedLightCalculationValue CalculationSimplexNoise::getValue(unsigned long loopSetColorsCounter, double currentTimeSeconds, double relativePhase) {

  double elementSpecificMapping = getMappedPhase(relativePhase);

  double noise = sn.noise(elementSpecificMapping * xRatio, currentTimeSeconds * yRatio) * outputAmplitude + outputOffset;


  ledLightCalculationValue.setValue(noise);


  return ledLightCalculationValue;
}