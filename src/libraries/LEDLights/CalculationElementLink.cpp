#include "CalculationElementLink.h"
#include "HelperFunctions.h"

void CalculationElementLink::debugPrint(void) {
  Serial.println(F("\nCalculationElementLink::debugPrint"));
  Serial.print(F("hasPhaseMapping()=="));
  if (this->hasPhaseMapping()) {
    Serial.println(F("true"));
  } else {
    Serial.println(F("false"));
  }
  serialPrintLnDouble("\ngetPhaseMappingStartPhase():", targetRelativeStartPhase);
  serialPrintLnDouble("getPhaseMappingStartPhase():", targetRelativeEndPhase, "\n");
}

CalculationElementLink::CalculationElementLink(LedLightCalculationElement *element) {
  this->bHasMapping = false;
  setCalculationElement(element);
}
CalculationElementLink::CalculationElementLink(LedLightCalculationElement *element, double targetRelativeStartPhase, double targetRelativeEndPhase) {
  setCalculationElement(element);
  setPhaseMapping(targetRelativeStartPhase, targetRelativeEndPhase);
}

void CalculationElementLink::setCalculationElement(LedLightCalculationElement *element) {
  this->element = element;
}

LedLightCalculationElement *CalculationElementLink::getCalculationElement(void) {
  return this->element;
}

void CalculationElementLink::setPhaseMapping(double targetRelativeStartPhase, double targetRelativeEndPhase) {  
  this->bHasMapping = true;
  this->targetRelativeStartPhase = targetRelativeStartPhase;
  this->targetRelativeEndPhase = targetRelativeEndPhase;
/*
  Serial.print("\nCalculationElementLink::setPhaseMapping");
  serialPrintLnDouble("\nthis->targetRelativeStartPhase:", targetRelativeStartPhase);
  serialPrintLnDouble("this->targetRelativeEndPhase:", targetRelativeEndPhase, "\n");
  */
}

bool CalculationElementLink::hasPhaseMapping(void) {
  return bHasMapping;
}

double CalculationElementLink::getPhaseMappingStartPhase() {
  if (bHasMapping == false) {
    return 0.0;
  }
}

double CalculationElementLink::getPhaseMappingEndPhase() {
  if (bHasMapping == false) {
    return 1.0;
  }
}

double CalculationElementLink::getMappedRelativePhase(double relativePhase) {
  if (bHasMapping == false) {
    return relativePhase;
  }
  return targetRelativeStartPhase + (targetRelativeEndPhase - targetRelativeStartPhase) * relativePhase;
}