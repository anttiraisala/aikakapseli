#ifndef BRANCH_BY_DISTANCE_STATE_H
#define BRANCH_BY_DISTANCE_STATE_H

#include "LedLightCalculationElement.h"
#include "CalculationElementLink.h"
#include "HelperFunctions.h"

#define BRANCH_BY_STATE_LIST_SIZE 3

class BranchByDistanceState : public LedLightCalculationElement {
public:
  BranchByDistanceState(void);
  LedLightCalculationValue getValue(unsigned long loopSetColorsCounter, double currentTimeSeconds, double relativePhase);

  BranchByDistanceState *setStateAndCalculationElementLink(StateManager::DistanceState state, CalculationElementLink *calculationElementLink);
  BranchByDistanceState *setDefaultCalculationElementLink(CalculationElementLink *calculationElementLink);

private:

  byte states[BRANCH_BY_STATE_LIST_SIZE];
  CalculationElementLink *calculationElementLinks[BRANCH_BY_STATE_LIST_SIZE];
  byte elementCount = 0;
  CalculationElementLink *defaultElementLink;
};

#endif  // BRANCH_BY_DISTANCE_STATE_H
