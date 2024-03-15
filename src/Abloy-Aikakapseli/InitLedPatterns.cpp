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
  //ledLights.setCalculationElementLink(0, new CalculationElementLink(branchByDistance));

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
  //ledLights.setCalculationElementLink(1, new CalculationElementLink(cd));


  /* DistanceState - FAR - begins */

  LedLightCalculationConstant *distanceFar_ColorWhite = new LedLightCalculationConstant(255.0, 255.0, 255.0);

  // Sine rotating left
  LedLightCalculationConstant *number_Five = new LedLightCalculationConstant(5.0);
  LedLightCalculationSine *distanceFar_Sine = (new LedLightCalculationSine(0.0, 0.10, 0.3, 0.70))->setCalculationElementPhaseMapping(0.0, 2.0 * 3.14159265359 * 2.0);
  LedLightCalculationTwoOperands *distanceFar_PowerFive = new LedLightCalculationTwoOperands(LedLightCalculationTwoOperandsOperation::POW, new CalculationElementLink(distanceFar_Sine), new CalculationElementLink(new LedLightCalculationConstant(5.0)));
  LedLightCalculationTwoOperands *distanceFar_MultiplyByColor = new LedLightCalculationTwoOperands(LedLightCalculationTwoOperandsOperation::MULTIPLY, new CalculationElementLink(distanceFar_PowerFive), new CalculationElementLink(distanceFar_ColorWhite));
/*
  // rotate left
  LedLightCalculationConstant *distanceFar_RotateLeft_RotateLeftSpeed = new LedLightCalculationConstant(1.4 * -0.07);
  LedLightCalculationConstant *distanceFar_RotateLeftColor = new LedLightCalculationConstant(255.0, 0.0, 0.0);
  SweepingDot *distanceFar_RotateLeft_Rotate = (new SweepingDot())->setSpeedRatioElement(new CalculationElementLink(distanceFar_RotateLeft_RotateLeftSpeed))->setRotateInsteadOfSweep(true);
  LedLightCalculationTwoOperands *distanceFar_RotateLeft_PowerFive = new LedLightCalculationTwoOperands(LedLightCalculationTwoOperandsOperation::POW, new CalculationElementLink(distanceFar_RotateLeft_Rotate), new CalculationElementLink(number_Five));
  LedLightCalculationTwoOperands *distanceFar_RotateLeft_MultiplyByColor = new LedLightCalculationTwoOperands(LedLightCalculationTwoOperandsOperation::MULTIPLY, new CalculationElementLink(distanceFar_RotateLeftColor), new CalculationElementLink(distanceFar_RotateLeft_PowerFive));

  // Noise
  LedLightCalculationConstant *number_NoisePowerNumber = new LedLightCalculationConstant(2.5);
  //CalculationSimplexNoise *distanceFar_Noise = (new CalculationSimplexNoise())->setOutputAmplitude(0.5)->setOutputOffset(0.5)->setYRatio(0.15)->setCalculationElementPhaseMapping(4.0, 9.0);
  LedLightCalculationSine *distanceFar_Noise = (new LedLightCalculationSine(18.1213, 0.048, 0.5, 0.50))->setCalculationElementPhaseMapping(0.0, 2.0 * 3.14159265359);
  //
  LedLightCalculationTwoOperands *distanceFar_Noise_PowerFive = new LedLightCalculationTwoOperands(LedLightCalculationTwoOperandsOperation::POW, new CalculationElementLink(distanceFar_Noise), new CalculationElementLink(number_NoisePowerNumber));
  LedLightCalculationTwoOperands *distanceFar_Noise_MultiplyByColor = new LedLightCalculationTwoOperands(LedLightCalculationTwoOperandsOperation::MULTIPLY, new CalculationElementLink(distanceFar_ColorWhite), new CalculationElementLink(distanceFar_Noise_PowerFive));

  // CrossDissolve sine and rotate
  //CalculationSimplexNoise *distanceFar_Combine_CD_Sine_Rotate_Noise = (new CalculationSimplexNoise())->setOutputAmplitude(0.5)->setOutputOffset(0.5)->setYRatio(0.305)->setCalculationElementPhaseMapping(0.0, 6.0);
  LedLightCalculationSine *distanceFar_Combine_CD_Sine_Rotate_Noise = (new LedLightCalculationSine(11.1213, 0.048, 0.5, 0.50))->setCalculationElementPhaseMapping(2.0, 4.0 * 3.14159265359);
  //
  CrossDissolve *distanceFar_Combine_CD_Sine_Rotate = (new CrossDissolve())->setUseSmoothStep(true)->setSmoothStepA(0.4)->setSmoothStepB(0.60);
  //distanceFar_Combine_CD_Sine_Rotate->setControlElement(new CalculationElementLink(new LedLightCalculationConstant(1.0)));
  distanceFar_Combine_CD_Sine_Rotate->setControlElement(new CalculationElementLink(distanceFar_Combine_CD_Sine_Rotate_Noise));
  distanceFar_Combine_CD_Sine_Rotate->setInput0Element(new CalculationElementLink(distanceFar_MultiplyByColor));
  distanceFar_Combine_CD_Sine_Rotate->setInput1Element(new CalculationElementLink(distanceFar_RotateLeft_MultiplyByColor));

  // CrossDissolve Noise and SineRotate
  CalculationSimplexNoise *distanceFar_Combine_Noise_SineRotate = (new CalculationSimplexNoise())->setOutputAmplitude(0.5)->setOutputOffset(0.5)->setYRatio(0.305)->setCalculationElementPhaseMapping(0.0, 6.0);
  CrossDissolve *distanceFar_Combine_Noise_SineRotate_CD = (new CrossDissolve())->setUseSmoothStep(true)->setSmoothStepA(0.4)->setSmoothStepB(0.60);
  distanceFar_Combine_Noise_SineRotate_CD->setControlElement(new CalculationElementLink(distanceFar_Combine_Noise_SineRotate));
  distanceFar_Combine_Noise_SineRotate_CD->setInput0Element(new CalculationElementLink(distanceFar_Noise_MultiplyByColor));
  distanceFar_Combine_Noise_SineRotate_CD->setInput1Element(new CalculationElementLink(distanceFar_Combine_CD_Sine_Rotate));
*/

  LedLightCalculationSine *distanceFar_BreathingSine = (new LedLightCalculationSine(0.0, 0.2, 0.15, 0.25))->setCalculationElementConstantMapping(0.0);
  LedLightCalculationTwoOperands *distanceFar_breathing = new LedLightCalculationTwoOperands(LedLightCalculationTwoOperandsOperation::MULTIPLY, new CalculationElementLink(distanceFar_MultiplyByColor), new CalculationElementLink(distanceFar_BreathingSine));

  /* DistanceState - FAR - ends */


/* DistanceState - NEAR - begins */

   // Sine rotating left
  LedLightCalculationSine *distanceNear_Sine = (new LedLightCalculationSine(0.0, -0.6, 0.3, 0.70))->setCalculationElementPhaseMapping(0.0, 2.0 * 3.14159265359 * 2.0);
  LedLightCalculationTwoOperands *distanceNear_PowerFive = new LedLightCalculationTwoOperands(LedLightCalculationTwoOperandsOperation::POW, new CalculationElementLink(distanceNear_Sine), new CalculationElementLink(new LedLightCalculationConstant(5.0)));
  LedLightCalculationTwoOperands *distanceNear_MultiplyByColor = new LedLightCalculationTwoOperands(LedLightCalculationTwoOperandsOperation::MULTIPLY, new CalculationElementLink(distanceNear_PowerFive), new CalculationElementLink(distanceFar_ColorWhite));

  /* DistanceState - NEAR - ends */

/* DistanceState - RETREATING - begins */

  LedLightCalculationSine *distanceRetreating_Sine = (new LedLightCalculationSine(0.0, -0.1, 0.3, 0.70))->setCalculationElementPhaseMapping(0.0, 2.0 * 3.14159265359 * 2.0);
  LedLightCalculationTwoOperands *distanceRetreating_PowerFive = new LedLightCalculationTwoOperands(LedLightCalculationTwoOperandsOperation::POW, new CalculationElementLink(distanceRetreating_Sine), new CalculationElementLink(new LedLightCalculationConstant(5.0)));
  LedLightCalculationTwoOperands *distanceRetreating_MultiplyByColor = new LedLightCalculationTwoOperands(LedLightCalculationTwoOperandsOperation::MULTIPLY, new CalculationElementLink(distanceRetreating_PowerFive), new CalculationElementLink(distanceFar_ColorWhite));

  /* DistanceState - RETREATING - ends */

  /* LED branch by state - begins */

  BranchByState *leds_BranchByDistanceState = new BranchByState();
  leds_BranchByDistanceState->setDefaultCalculationElementLink(new CalculationElementLink(distanceFar_breathing));
  leds_BranchByDistanceState->setStateAndCalculationElementLink((byte)StateManager::DistanceState::NEAR, new CalculationElementLink(distanceNear_MultiplyByColor));
  leds_BranchByDistanceState->setStateAndCalculationElementLink((byte)StateManager::DistanceState::RETREATING, new CalculationElementLink(distanceRetreating_MultiplyByColor));

  LedLightCalculationConstant *leds_CrossDissolve_ColorGreen = new LedLightCalculationConstant(0.0, 255.0, 0.0);
  StateChangePulse *leds_StateChange_PulseNoteDropped = (new StateChangePulse())->setState((byte)StateManager::NoteState::DROPPED)->setPostOutput(0.0);
  CrossDissolve *leds_CrossDissolve_PulseNoteDropped = new CrossDissolve();
  leds_CrossDissolve_PulseNoteDropped->setControlElement(new CalculationElementLink(leds_StateChange_PulseNoteDropped));
  leds_CrossDissolve_PulseNoteDropped->setInput0Element(new CalculationElementLink(leds_BranchByDistanceState));
  leds_CrossDissolve_PulseNoteDropped->setInput1Element(new CalculationElementLink(leds_CrossDissolve_ColorGreen));



  /* LED branch by state - ends */

  LedLightCalculationElement *testElement = leds_CrossDissolve_PulseNoteDropped;

  int ledCount = 59;
  double endPhase = 1.0;
  //
  ledLights.init();
  ledLights.setCalculationElementLink(0, new CalculationElementLink(testElement, endPhase / ledCount * 00.0, endPhase / ledCount * 09.0));
  ledLights.setCalculationElementLink(1, new CalculationElementLink(testElement, endPhase / ledCount * 10.0, endPhase / ledCount * 19.0));
  ledLights.setCalculationElementLink(2, new CalculationElementLink(testElement, endPhase / ledCount * 20.0, endPhase / ledCount * 29.0));
  ledLights.setCalculationElementLink(3, new CalculationElementLink(testElement, endPhase / ledCount * 30.0, endPhase / ledCount * 39.0));
  ledLights.setCalculationElementLink(4, new CalculationElementLink(testElement, endPhase / ledCount * 40.0, endPhase / ledCount * 49.0));
  ledLights.setCalculationElementLink(5, new CalculationElementLink(testElement, endPhase / ledCount * 50.0, endPhase / ledCount * 59.0));


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

  ledLights.setCalculationElementLink(6, new CalculationElementLink(slotCombinedBranch, slotEndPhase / slotLedCount * 00.0, slotEndPhase / slotLedCount * 09.0));
  ledLights.setCalculationElementLink(7, new CalculationElementLink(slotCombinedBranch, slotEndPhase / slotLedCount * 10.0, slotEndPhase / slotLedCount * 19.0));






  /* Combined slot - ends */



  /* Note slot - ends */
  /************************************************************/







  Serial.println(F("initPatterns - ends"));
}
