#include "BranchByDistanceState.h"
#include "CalculationElementLink.h"
#include "LedLightCalculationElement.h"

#include "StateManager.h"
extern StateManager stateManager;

/*
extern DistanceState currentDistanceState;
extern NoteState currentNoteState;
*/


LedLightCalculationValue BranchByDistanceState::getValue(unsigned long loopSetColorsCounter, double currentTimeSeconds, double relativePhase) {
  CalculationElementLink *sourceCalculationElementLink = nullptr;
  LedLightCalculationElement *sourceCalculationElement;

  for (byte i = 0; i < BRANCH_BY_STATE_LIST_SIZE; i++) {
    if (states[i] == (byte)stateManager.getDistanceState()) {
      sourceCalculationElementLink = calculationElementLinks[i];
      break;
    }
  }

  if (sourceCalculationElementLink == nullptr) {
    if (defaultElementLink != nullptr) {
      sourceCalculationElementLink = defaultElementLink;
    } else {
      if (elementCount > 0) {
        sourceCalculationElementLink = states[0];
      }
    }
  }

  if (sourceCalculationElementLink != nullptr) {
    sourceCalculationElement = sourceCalculationElementLink->getCalculationElement();

    return sourceCalculationElement->getValue(loopSetColorsCounter, currentTimeSeconds, sourceCalculationElementLink->getMappedRelativePhase(relativePhase));
  }

  Serial.print("ERROR; BranchByDistanceState, no definition found for state ");
  Serial.println(stateManager.getCurrentDistanceStateString());

  return ledLightCalculationValue;
}

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