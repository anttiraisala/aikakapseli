#include "LedLightCalculationSine.h"

LedLightCalculationSine::LedLightCalculationSine() {}

LedLightCalculationSine::LedLightCalculationSine(double phase, double frequency, double amplitude, double offset) {
  this->setParameters(phase, frequency, amplitude, offset);
}

void LedLightCalculationSine::setParameters(double phase, double frequency, double amplitude, double offset) {
  this->phase = phase;
  this->frequency = frequency;
  this->amplitude = amplitude;
  this->offset = offset;

  
}

LedLightCalculationValue LedLightCalculationSine::getValue(double currentTimeSeconds, double relativePhase, CalculationElementPhaseMapping calculationElementPhaseMapping) {
  return ledLightCalculationValue;
}