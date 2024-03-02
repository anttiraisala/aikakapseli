#ifndef CALCULATION_ELEMENT_LINK_H
#define CALCULATION_ELEMENT_LINK_H

#include "LedLightCalculationElement.h"


/*
struct CalculationElementPhaseMapping {
  double startPhase = 0.0;
  double endPhase = 2.0*3.14159265359;
};
*/

class CalculationElementLink {
public:
  CalculationElementLink(LedLightCalculationElement *element);
  CalculationElementLink(LedLightCalculationElement *element, double targetRelativeStartPhase, double targetRelativeEndPhase);

  LedLightCalculationElement* getCalculationElement();
  void setCalculationElement(LedLightCalculationElement *element);

  void setPhaseMapping(double targetRelativeStartPhase, double targetRelativeEndPhase);
  double getPhaseMappingStartPhase();
  double getPhaseMappingEndPhase();
  bool hasPhaseMapping();
  double getMappedRelativePhase(double relativePhase);

  void debugPrint(void);

private:
  LedLightCalculationElement *element = nullptr;
  bool bHasMapping=false;
  double targetRelativeStartPhase;
  double targetRelativeEndPhase;
};


#endif  // CALCULATION_ELEMENT_LINK_H