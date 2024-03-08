#include "InitLedPatterns.h"

extern LedLights ledLights;


void initPatterns(void) {
  Serial.println(F("initPatterns - begin"));
  ledLights.init();
  ledLights.setLightsToZero();

  LedLightCalculationConstant *llc_colorRed = new LedLightCalculationConstant(255.0, 0.0, 0.0);
  LedLightCalculationConstant *llc_colorGreen = new LedLightCalculationConstant(0.0, 255.0, 0.0);
  LedLightCalculationConstant *llc_colorBlue = new LedLightCalculationConstant(0.0, 0.0, 255.0);
  LedLightCalculationConstant *llc_colorWhite = new LedLightCalculationConstant(255.0, 255.0, 255.0);

  BranchByState *branchByDistance = new BranchByState();
  branchByDistance->setStateAndCalculationElementLink((byte)StateManager::DistanceState::FAR, new CalculationElementLink(llc_colorRed));
  branchByDistance->setStateAndCalculationElementLink((byte)StateManager::DistanceState::NEAR, new CalculationElementLink(llc_colorGreen));
  branchByDistance->setStateAndCalculationElementLink((byte)StateManager::DistanceState::RETREATING, new CalculationElementLink(llc_colorBlue));
  branchByDistance->setDefaultCalculationElementLink(new CalculationElementLink(llc_colorWhite));
  ledLights.setCalculationElementLink(0, new CalculationElementLink(branchByDistance));

  branchByDistance->debugPrint();
  delay(1000);


  stateManager.setDistanceState(750, StateManager::DistanceState::FAR);
  stateManager.setNoteState(750, StateManager::NoteState::NO_NOTE);
  ledLights.loopSetColors(750);
  ledLights.loopShow();
  delay(4000);
  Serial.println(F("initPatterns - ends"));
}
