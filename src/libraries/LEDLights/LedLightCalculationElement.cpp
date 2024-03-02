#include "LedLightCalculationElement.h"


double LedLightCalculationElement::getMappedPhase(double relativePhase) {
  return startPhase + (endPhase - startPhase) * relativePhase;
}