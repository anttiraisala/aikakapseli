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

  /*
  stateManager.setDistanceState(750, StateManager::DistanceState::FAR);
  stateManager.setNoteState(750, StateManager::NoteState::NO_NOTE);
  ledLights.loopSetColors(750);
  ledLights.loopShow();
  delay(4000);
*/

  StateChangePulse *ssp = (new StateChangePulse())->setState((byte)StateManager::NoteState::DROPPED);
  CrossDissolve *cd = new CrossDissolve();
  cd->setControlElement(new CalculationElementLink(ssp));
  cd->setInput0Element(new CalculationElementLink(llc_colorWhite));
  cd->setInput1Element(new CalculationElementLink(llc_colorGreen));
  ledLights.setCalculationElementLink(1, new CalculationElementLink(cd));


  /************************************************************/
  /* Note slot - begins */

  /* NO_NOTE - begins */
  LedLightCalculationConstant *slotWhite = new LedLightCalculationConstant(255.0, 255.0, 255.0);
  LedLightCalculationConstant *slotFive = new LedLightCalculationConstant(5.0);
  LedLightCalculationSine *slotNoNoteSinRotate = (new LedLightCalculationSine(0.0, 0.5, 0.2, 0.6))->setCalculationElementPhaseMapping(0.0, 2.0 * 3.14159265359 * 2.0);
  LedLightCalculationTwoOperands *slotPowerFive = new LedLightCalculationTwoOperands(LedLightCalculationTwoOperandsOperation::POW, new CalculationElementLink(slotNoNoteSinRotate), new CalculationElementLink(slotFive));
  LedLightCalculationTwoOperands *slotNoNoteMultiplication = new LedLightCalculationTwoOperands(LedLightCalculationTwoOperandsOperation::MULTIPLY, new CalculationElementLink(slotWhite), new CalculationElementLink(slotPowerFive));
  int slotLedCount = 19;
  double slotEndPhase = 1.0;
  /*
  ledLights.setCalculationElementLink(2, new CalculationElementLink(slotNoNoteMultiplication, slotEndPhase / slotLedCount * 00.0, slotEndPhase / slotLedCount * 09.0));
  ledLights.setCalculationElementLink(3, new CalculationElementLink(slotNoNoteMultiplication, slotEndPhase / slotLedCount * 10.0, slotEndPhase / slotLedCount * 19.0));
  */
  /* NO_NOTE - ends */

  /* INSERTING- begins */
  LedLightCalculationConstant *slotLightGreen = new LedLightCalculationConstant(75.0, 255.0, 75.0);
  LedLightCalculationConstant *slotGreen = new LedLightCalculationConstant(0.0, 255.0, 0.0);

/*
  Serial.println(F("new CalculationSimplexNoise() - before"));
  CalculationSimplexNoise *slotInserting_noise = (new CalculationSimplexNoise())->setOutputAmplitude(0.05)->setOutputOffset(0.95)->setYRatio(0.250)->setCalculationElementPhaseMapping(0.0, 6.0);
  Serial.println(F("new CalculationSimplexNoise() - after"));
  */
  //
  LedLightCalculationSine *slotInserting_sine = (new LedLightCalculationSine(0.0, 0.5, 0.4, 0.5))->setCalculationElementPhaseMapping(0.0, 2.0 * 3.14159265359 * 2.0);
  LedLightCalculationTwoOperands *slotInserting_multiply = new LedLightCalculationTwoOperands(LedLightCalculationTwoOperandsOperation::MULTIPLY, new CalculationElementLink(slotGreen), new CalculationElementLink(slotInserting_sine));



  //ledLights.setCalculationElementLink(2, new CalculationElementLink(slotLightGreen));
  /* INSERTING- ends */

  /* DROPPED - begins */
  LedLightCalculationConstant *slotDroppedWhite = new LedLightCalculationConstant(255.0, 255.0, 255.0);
  LedLightCalculationConstant *slotDroppedGreen = new LedLightCalculationConstant(0.0, 255.0, 0.0);
  StateChangePulse *slotDroppedScp = (new StateChangePulse())->setState((byte)StateManager::NoteState::DROPPED)->setPostOutput(1.0)->setPreDelay(0.30);
  //
  CrossDissolve *slotCD = new CrossDissolve();
  slotCD->setControlElement(new CalculationElementLink(slotDroppedScp));
  slotCD->setInput0Element(new CalculationElementLink(slotDroppedWhite));
  slotCD->setInput1Element(new CalculationElementLink(slotDroppedGreen));
  //ledLights.setCalculationElementLink(2, new CalculationElementLink(slotCD));
  /* DROPPED - ends */


  /* Combined slot - begins */
  BranchByState *slotCombinedBranch = new BranchByState();
  slotCombinedBranch->setDefaultCalculationElementLink(new CalculationElementLink(slotNoNoteMultiplication));
  slotCombinedBranch->setStateAndCalculationElementLink((byte)StateManager::NoteState::INSERTING, new CalculationElementLink(slotInserting_multiply));
  slotCombinedBranch->setStateAndCalculationElementLink((byte)StateManager::NoteState::DROPPED, new CalculationElementLink(slotCD));

  ledLights.setCalculationElementLink(2, new CalculationElementLink(slotCombinedBranch, slotEndPhase / slotLedCount * 00.0, slotEndPhase / slotLedCount * 09.0));
  ledLights.setCalculationElementLink(3, new CalculationElementLink(slotCombinedBranch, slotEndPhase / slotLedCount * 10.0, slotEndPhase / slotLedCount * 19.0));






  /* Combined slot - ends */



  /* Note slot - ends */
  /************************************************************/







  Serial.println(F("initPatterns - ends"));
}
