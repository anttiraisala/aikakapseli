#include "LedLightCalculationElement.h"

LedLightCalculationElement* LedLightCalculationElement::setCalculationElementPhaseMapping(double startPhase, double endPhase) {
  this->startPhase = startPhase;
  this->endPhase = endPhase;
  return this;
}

double LedLightCalculationElement::getMappedPhase(double relativePhase) {
  return startPhase + (endPhase - startPhase) * relativePhase;
}