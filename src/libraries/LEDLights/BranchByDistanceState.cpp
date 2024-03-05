#include "BranchByDistanceState.h"

#include "StateManager.h"
extern StateManager stateManager;

/*
extern DistanceState currentDistanceState;
extern NoteState currentNoteState;
*/


LedLightCalculationValue BranchByDistanceState::getValue(unsigned long loopSetColorsCounter, double currentTimeSeconds, double relativePhase) {}

BranchByDistanceState *BranchByDistanceState::setStateAndCalculationElementLink(StateManager::DistanceState state, CalculationElementLink *calculationElementLink) {
  states[elementCount] = (byte)state;
  calculationElementLinks[elementCount] = calculationElementLink;
  elementCount++;
  if (elementCount >= BRANCH_BY_STATE_LIST_SIZE) {
    elementCount = 0;
  }
  return this;
}

BranchByDistanceState *BranchByDistanceState::setDefaultCalculationElementLink(CalculationElementLink *calculationElementLink) {
  defaultElementLink = calculationElementLink;
  return this;
}

void debugPrint(void) {
}

/*
  byte states[BRANCH_BY_STATE_LIST_SIZE];
  CalculationElementLink *calculationElementLinks[BRANCH_BY_STATE_LIST_SIZE];
  byte elementCount=0;
  CalculationElementLink *defaultElementLink;
*/