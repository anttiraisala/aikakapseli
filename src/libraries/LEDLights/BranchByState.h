#ifndef BRANCH_BY_STATE_H
#define BRANCH_BY_STATE_H

#include "LedLightCalculationElement.h"
#include "CalculationElementLink.h"
#include "HelperFunctions.h"

#define BRANCH_BY_STATE_LIST_SIZE 3

class BranchByState : public LedLightCalculationElement {
public:
  BranchByState(void);
  LedLightCalculationValue getValue(unsigned long loopSetColorsCounter, double currentTimeSeconds, double relativePhase);

  BranchByState *setStateAndCalculationElementLink(byte state, CalculationElementLink *calculationElementLink);
  BranchByState *setDefaultCalculationElementLink(CalculationElementLink *calculationElementLink);

  void debugPrint(void);

private:

  byte states[BRANCH_BY_STATE_LIST_SIZE];
  CalculationElementLink *calculationElementLinks[BRANCH_BY_STATE_LIST_SIZE];
  byte elementCount = 0;
  CalculationElementLink *defaultElementLink;
};

#endif  // BRANCH_BY_STATE_H
