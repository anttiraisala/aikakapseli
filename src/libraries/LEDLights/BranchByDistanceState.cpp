#include "BranchByDistanceState.h"
#include "CalculationElementLink.h"
#include "LedLightCalculationElement.h"

#include <Arduino.h>

#include "StateManager.h"
extern StateManager stateManager;

/*
extern DistanceState currentDistanceState;
extern NoteState currentNoteState;
*/

BranchByDistanceState::BranchByDistanceState(void) {
  elementCount = 0;
  defaultElementLink = nullptr;
  for (byte i = 0; i < BRANCH_BY_STATE_LIST_SIZE; i++) {
    states[i] = 0;
    calculationElementLinks[i] = nullptr;
  }
}

void BranchByDistanceState::debugPrint(void) {
  Serial.println("BranchByDistanceState::debugPrint - begins");

  Serial.print("elementCount: ");
  Serial.println(elementCount, DEC);

  for (byte i = 0; i < elementCount; i++) {
    Serial.print("  element: [");
    Serial.print(i, DEC);
    Serial.print("]  DistanceState: [");
    Serial.print(states[i], DEC);
    Serial.println("]");
  }

  if (defaultElementLink == nullptr) {
    Serial.println("defaultElementLink == nullptr");
  } else {
    Serial.println("defaultElementLink != nullptr");
  }

  Serial.println("BranchByDistanceState::debugPrint - ends");
}

LedLightCalculationValue BranchByDistanceState::getValue(unsigned long loopSetColorsCounter, double currentTimeSeconds, double relativePhase) {
  CalculationElementLink *sourceCalculationElementLink = nullptr;
  LedLightCalculationElement *sourceCalculationElement;

  for (byte i = 0; i < elementCount; i++) {
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



/*
  byte states[BRANCH_BY_STATE_LIST_SIZE];
  CalculationElementLink *calculationElementLinks[BRANCH_BY_STATE_LIST_SIZE];
  byte elementCount=0;
  CalculationElementLink *defaultElementLink;
*/