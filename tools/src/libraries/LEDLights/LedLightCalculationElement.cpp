#include "LedLightCalculationElement.h"

LedLightCalculationElement* LedLightCalculationElement::setCalculationElementPhaseMapping(double startPhase, double endPhase) {
  this->startPhase = startPhase;
  this->endPhase = endPhase;
  this->bHasConstantMapping = false;

  return this;
}

LedLightCalculationElement* LedLightCalculationElement::setCalculationElementConstantMapping(double constantPhase) {
  this->constantPhase = constantPhase;
  this->bHasConstantMapping = true;

  return this;
}

double LedLightCalculationElement::getMappedPhase(double relativePhase) {
  if (bHasConstantMapping == true) {
    return bHasConstantMapping;
  }

  return startPhase + (endPhase - startPhase) * relativePhase;
}