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
  //ledLights.setCalculationElementLink(2, new CalculationElementLink(slotLightGreen));
  /* INSERTING- ends */

  /* DROPPED - begins */
  LedLightCalculationConstant *slotDroppedWhite = new LedLightCalculationConstant(255.0, 255.0, 255.0);
  LedLightCalculationConstant *slotDroppedGreen = new LedLightCalculationConstant(0.0, 255.0, 0.0);
  StateChangePulse *slotDroppedScp = (new StateChangePulse())->setState((byte)StateManager::NoteState::DROPPED);
  //
  CrossDissolve *slotCD = new CrossDissolve();
  slotCD->setControlElement(new CalculationElementLink(slotDroppedScp));
  slotCD->setInput0Element(new CalculationElementLink(slotDroppedWhite));
  slotCD->setInput1Element(new CalculationElementLink(slotDroppedGreen));
  ledLights.setCalculationElementLink(2, new CalculationElementLink(slotCD));
  /* DROPPED - ends */


  /* Combined slot - begins */




  /* Combined slot - ends */



  /* Note slot - ends */
  /************************************************************/







  Serial.println(F("initPatterns - ends"));
}
