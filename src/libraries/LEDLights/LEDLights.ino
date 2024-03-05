#include <Arduino.h>
#include "CallbackTimer.h"


/* Tällä kontrolloidaan LED-Stickejä */
#include "LedLights.h"
LedLights ledLights;

/* Asiakkaan etäisyys -tilat */
#include "distance_state.h"
DistanceState distanceState = DistanceState::FAR;


/* Viestin asettaminen -tilat */
#include "note_state.h"
NoteState noteState = NoteState::NO_NOTE;


/* Testejä varten includataan luokat */
#include "LedLightCalculationElement.h"
#include "CalculationElementLink.h"
#include "LedLightCalculationConstant.h"
#include "LedLightCalculationSine.h"
#include "LedLightCalculationTwoOperands.h"
#include "BranchByState.h"

#include "HelperFunctions.h"




Adafruit_NeoPixel *pixels;

Adafruit_NeoPixel *getAdafruit_NeoPixel(byte pin) {
  Adafruit_NeoPixel *pixels = new Adafruit_NeoPixel(10, pin, NEO_GRB + NEO_KHZ800);
  pixels->begin();
  pixels->setBrightness(255);
  return pixels;
}

void serialprint(char *str, double d) {
  Serial.print(str);
  Serial.println(d, DEC);
}

void patternInit(void);

void serialPrintMillis(void) {
  Serial.print("millis(): ");
  Serial.println(millis());
}
CallbackTimer *serialPrintMillisTimer = new CallbackTimer(serialPrintMillis, millis(), 5000);

void tests(void) {
  Serial.println("");
  Serial.println("");
  Serial.println("tests begin...");
/*
  LedLightCalculationValue v = LedLightCalculationValue(253.0, 128.0, 17.0);
  LedLightCalculationConstant c = LedLightCalculationConstant();
  c.setValue(v);
  Serial.println(": 253.0, 128.0, 17.0");
  serialprint("c.getValue().getValueV(): ", c.getValue().getValueV());
  serialprint("c.getValue().getValueR(): ", c.getValue().getValueR());
  serialprint("c.getValue().getValueG(): ", c.getValue().getValueG());
  serialprint("c.getValue().getValueB(): ", c.getValue().getValueB());
  //
  v = LedLightCalculationValue(256.0, -128.0, 19.0);
  c = LedLightCalculationConstant();
  c.setValue(v);
  Serial.println(": 256.0, -128.0, 19.0");
  serialprint("c.getValue().getValueV(): ", c.getValue().getValueV());
  serialprint("c.getValue().getValueR(): ", c.getValue().getValueR());
  serialprint("c.getValue().getValueG(): ", c.getValue().getValueG());
  serialprint("c.getValue().getValueB(): ", c.getValue().getValueB());
  serialprint(".getValue().getValueBytes().r: ", c.getValue().getValueBytes().r);
  serialprint(".getValue().getValueBytes().g: ", c.getValue().getValueBytes().g);
  serialprint(".getValue().getValueBytes().b: ", c.getValue().getValueBytes().b);
*/

  int ledCount = 49;
  double endPhase = 1.0;

  LedLightCalculationSine *ledLightCalculationSine;
  ledLightCalculationSine = (new LedLightCalculationSine(0.0, 0.5, 0.2, 0.8))->setCalculationElementPhaseMapping(0.0, 2.0 * 3.14159265359 * 10.0);  //->setCalculationElementConstantMapping(0.0);
  ledLights.setCalculationElementLink(0, new CalculationElementLink(ledLightCalculationSine, endPhase / ledCount * 00.0, endPhase / ledCount * 09.0));
  ledLights.setCalculationElementLink(1, new CalculationElementLink(ledLightCalculationSine, endPhase / ledCount * 10.0, endPhase / ledCount * 19.0));
  ledLights.setCalculationElementLink(2, new CalculationElementLink(ledLightCalculationSine, endPhase / ledCount * 20.0, endPhase / ledCount * 29.0));
  ledLights.setCalculationElementLink(3, new CalculationElementLink(ledLightCalculationSine, endPhase / ledCount * 30.0, endPhase / ledCount * 39.0));
  ledLights.setCalculationElementLink(4, new CalculationElementLink(ledLightCalculationSine, endPhase / ledCount * 40.0, endPhase / ledCount * 49.0));


  /*
LedLightCalculationTwoOperands
enum class LedLightCalculationTwoOperandsOperation {
  ADD,
  SUBTRACT,
  MULTIPLY,
  DIVIDE,
  POW,
  MAX,
  MIN
};
*/

  LedLightCalculationConstant *cA = new LedLightCalculationConstant(2.5);
  LedLightCalculationConstant *cB = new LedLightCalculationConstant(3.5);
  LedLightCalculationConstant *cZ = new LedLightCalculationConstant(0.0);
  LedLightCalculationTwoOperands *operation = new LedLightCalculationTwoOperands(LedLightCalculationTwoOperandsOperation::ADD, new CalculationElementLink(cA), new CalculationElementLink(cB));
  cA->debugPrint();
  cB->debugPrint();
  Serial.println("ADD");
  operation->setOperation(LedLightCalculationTwoOperandsOperation::ADD)->getValue(0, 0.0, 0.0).debugPrint();
  Serial.println("SUBTRACT");
  operation->setOperation(LedLightCalculationTwoOperandsOperation::SUBTRACT)->getValue(0, 0.0, 0.0).debugPrint();
  Serial.println("MULTIPLY");
  operation->setOperation(LedLightCalculationTwoOperandsOperation::MULTIPLY)->getValue(0, 0.0, 0.0).debugPrint();
  Serial.println("DIVIDE");
  operation->setOperation(LedLightCalculationTwoOperandsOperation::DIVIDE)->getValue(0, 0.0, 0.0).debugPrint();
  Serial.println("POW");
  operation->setOperation(LedLightCalculationTwoOperandsOperation::POW)->getValue(0, 0.0, 0.0).debugPrint();
  Serial.println("MAX");
  operation->setOperation(LedLightCalculationTwoOperandsOperation::MAX)->getValue(0, 0.0, 0.0).debugPrint();
  Serial.println("MIN");
  operation->setOperation(LedLightCalculationTwoOperandsOperation::MIN)->getValue(0, 0.0, 0.0).debugPrint();
  //
  Serial.println("Division by zero coming up...");
  LedLightCalculationTwoOperands *operationZeroDivisin = new LedLightCalculationTwoOperands(LedLightCalculationTwoOperandsOperation::ADD, new CalculationElementLink(cA), new CalculationElementLink(cZ));
  operationZeroDivisin->setOperation(LedLightCalculationTwoOperandsOperation::DIVIDE)->getValue(0, 0.0, 0.0).debugPrint();
  // Complex
  /*

  (A+B) * (C+D)

  */

  LedLightCalculationConstant *cC = new LedLightCalculationConstant(5.0);
  LedLightCalculationConstant *cD = new LedLightCalculationConstant(7.0);
  LedLightCalculationTwoOperands *operation2 = new LedLightCalculationTwoOperands(LedLightCalculationTwoOperandsOperation::ADD, new CalculationElementLink(cC), new CalculationElementLink(cD));

  Serial.println("(A+B) ...");
  operation->setOperation(LedLightCalculationTwoOperandsOperation::ADD)->getValue(0, 0.0, 0.0).debugPrint();
  Serial.println("(C+D) ...");
  operation2->setOperation(LedLightCalculationTwoOperandsOperation::ADD)->getValue(0, 0.0, 0.0).debugPrint();
  Serial.println("(A+B) * (C+D) ...");
  LedLightCalculationTwoOperands *operation3 = new LedLightCalculationTwoOperands(LedLightCalculationTwoOperandsOperation::MULTIPLY, new CalculationElementLink(operation), new CalculationElementLink(operation2));
  operation3->getValue(0, 0.0, 0.0).debugPrint();


  Serial.println("(255, 128, 0) ...");
  LedLightCalculationConstant *color1 = new LedLightCalculationConstant(255, 128, 0);
  color1->debugPrint();
  Serial.println("(0.5) ...");
  LedLightCalculationConstant *cHalf = new LedLightCalculationConstant(0.5);
  cHalf->debugPrint();
  Serial.println("(255, 128, 0) * (0.5) ...");
  LedLightCalculationTwoOperands *oColorTimesNumber = new LedLightCalculationTwoOperands(LedLightCalculationTwoOperandsOperation::MULTIPLY, new CalculationElementLink(color1), new CalculationElementLink(cHalf));
  oColorTimesNumber->getValue(0, 0.0, 0.0).debugPrint();
  Serial.println("(0.5) * (255, 128, 0) ...");
  LedLightCalculationTwoOperands *oColorTimesNumberOtherWayAround = new LedLightCalculationTwoOperands(LedLightCalculationTwoOperandsOperation::MULTIPLY, new CalculationElementLink(cHalf), new CalculationElementLink(color1));
  oColorTimesNumberOtherWayAround->getValue(0, 0.0, 0.0).debugPrint();


  Serial.println("(2, 5, 8) ...");
  LedLightCalculationConstant *color258 = new LedLightCalculationConstant(2, 5, 8);
  color258->debugPrint();
  Serial.println("(3, 4, 9) ...");
  LedLightCalculationConstant *color349 = new LedLightCalculationConstant(3, 4, 9);
  color349->debugPrint();
  LedLightCalculationTwoOperands *oColorContraColor = new LedLightCalculationTwoOperands(new CalculationElementLink(color258), new CalculationElementLink(color349));
  oColorContraColor->getValue(0, 0.0, 0.0).debugPrint();





  /*
  ledLights.setCalculations(5, new CalculationElementLink(new LedLightCalculationConstant(0.0, 255.0, 255.0), &cepm));
  ledLights.setCalculations(6, new CalculationElementLink(new LedLightCalculationConstant(128.0, 0.0, 255.0), &cepm));
  ledLights.setCalculations(7, new CalculationElementLink(new LedLightCalculationConstant(0.0, 128.0, 255.0), &cepm));
*/
  /*
  ledLights.getCalculationElementLink(0)->debugPrint();
  ledLights.getCalculationElementLink(1)->debugPrint();
  ledLights.getCalculationElementLink(2)->debugPrint();
  ledLights.getCalculationElementLink(3)->debugPrint();
  ledLights.getCalculationElementLink(4)->debugPrint();
  Serial.println("Onko vielä?");
  delay(2000);
*/

  Serial.println("");
  Serial.println("tests done.");
  Serial.println("");
  Serial.println("");
}

void patternInitBreathing(void) {
  Serial.println("\npatternInit - begins");

  // hengitys alkaa
  Serial.println("hengitys alkaa");
  LedLightCalculationSine *llc_sinePattern = (new LedLightCalculationSine(0.0, 0.5, 0.2, 0.8))->setCalculationElementPhaseMapping(0.0, 2.0 * 3.14159265359 * 5.0);
  LedLightCalculationSine *llc_breathing = (new LedLightCalculationSine(0.0, 0.7, 0.10, 0.80))->setCalculationElementConstantMapping(0.0);
  LedLightCalculationConstant *llc_color = new LedLightCalculationConstant(80.0, 255.0, 100.0);
  LedLightCalculationConstant *llc_five = new LedLightCalculationConstant(5.0);
  //
  LedLightCalculationTwoOperands *o_BreathingAndPattern = new LedLightCalculationTwoOperands(LedLightCalculationTwoOperandsOperation::MULTIPLY, new CalculationElementLink(llc_breathing), new CalculationElementLink(llc_sinePattern));
  LedLightCalculationTwoOperands *o_PowerFive = new LedLightCalculationTwoOperands(LedLightCalculationTwoOperandsOperation::POW, new CalculationElementLink(o_BreathingAndPattern), new CalculationElementLink(llc_five));
  LedLightCalculationTwoOperands *o_ColorAndPattern = new LedLightCalculationTwoOperands(LedLightCalculationTwoOperandsOperation::MULTIPLY, new CalculationElementLink(llc_color), new CalculationElementLink(o_PowerFive));
  o_ColorAndPattern->getValue(0, 0.0, 0.0).debugPrint();
  o_ColorAndPattern->getValue(0, 0.0, 0.2).debugPrint();
  o_ColorAndPattern->getValue(0, 0.0, 0.4).debugPrint();
  o_ColorAndPattern->getValue(0, 0.0, 0.6).debugPrint();
  o_ColorAndPattern->getValue(0, 0.0, 0.8).debugPrint();
  o_ColorAndPattern->getValue(0, 0.0, 1.0).debugPrint();
  Serial.println("hengitys valmis");
  // hengitys valmis

  int ledCount = 49;
  double endPhase = 1.0;


/*
LedLightCalculationTwoOperands *o_ColorAndPatternTest;
  for(int i=0; i<55;i++){
  o_ColorAndPatternTest = new LedLightCalculationTwoOperands(LedLightCalculationTwoOperandsOperation::MULTIPLY, new CalculationElementLink(llc_color), new CalculationElementLink(o_PowerFive));
  Serial.print(i, DEC);
  Serial.print(" ");
}
delay(2000);
  */
  ledLights.init();
  //ledLights.setCalculationElementLink(0, new CalculationElementLink(o_ColorAndPatternTest, endPhase / ledCount * 00.0, endPhase / ledCount * 09.0));
  ledLights.setCalculationElementLink(0, new CalculationElementLink(o_ColorAndPattern, endPhase / ledCount * 00.0, endPhase / ledCount * 09.0));
  ledLights.setCalculationElementLink(1, new CalculationElementLink(o_ColorAndPattern, endPhase / ledCount * 10.0, endPhase / ledCount * 19.0));
  ledLights.setCalculationElementLink(2, new CalculationElementLink(o_ColorAndPattern, endPhase / ledCount * 20.0, endPhase / ledCount * 29.0));
  ledLights.setCalculationElementLink(3, new CalculationElementLink(o_ColorAndPattern, endPhase / ledCount * 30.0, endPhase / ledCount * 39.0));
  ledLights.setCalculationElementLink(4, new CalculationElementLink(o_ColorAndPattern, endPhase / ledCount * 40.0, endPhase / ledCount * 49.0));

/*
  ledLights.init();
  LedLightCalculationSine *ledLightCalculationSine;
  ledLightCalculationSine = (new LedLightCalculationSine(0.0, 0.5, 0.2, 0.8))->setCalculationElementPhaseMapping(0.0, 2.0 * 3.14159265359 * 10.0);  //->setCalculationElementConstantMapping(0.0);
  ledLights.setCalculationElementLink(0, new CalculationElementLink(ledLightCalculationSine, endPhase / ledCount * 00.0, endPhase / ledCount * 09.0));
  ledLights.setCalculationElementLink(1, new CalculationElementLink(ledLightCalculationSine, endPhase / ledCount * 10.0, endPhase / ledCount * 19.0));
  ledLights.setCalculationElementLink(2, new CalculationElementLink(ledLightCalculationSine, endPhase / ledCount * 20.0, endPhase / ledCount * 29.0));
  ledLights.setCalculationElementLink(3, new CalculationElementLink(ledLightCalculationSine, endPhase / ledCount * 30.0, endPhase / ledCount * 39.0));
  ledLights.setCalculationElementLink(4, new CalculationElementLink(ledLightCalculationSine, endPhase / ledCount * 40.0, endPhase / ledCount * 49.0));
*/







  Serial.println("\npatternInit - ends");
}




void setup() {
  randomSeed(analogRead(0));
  // put your setup code here, to run once:
  Serial.begin(19200);

  // Rotary Angle Sensors
  pinMode(54, INPUT);
  pinMode(55, INPUT);



  delay(2000);

  Serial.println("setup starts...");
  delay(1000);

  Serial.println("ledLights.debugPrintLedSticks() - before ledLights.init()");
  ledLights.debugPrintLedSticks();
  ledLights.init();
  Serial.println("ledLights.debugPrintLedSticks() - after ledLights.init()");
  ledLights.debugPrintLedSticks();
  delay(1000);

  //tests();
  ledLights.init();
  patternInitBreathing();
  Serial.println("ledLights.debugPrintLedSticks() - after patternInitBreathing()");
  ledLights.debugPrintLedSticks();
  /*
  delay(1000);
  ledLights.getCalculationElementLink(0)->debugPrint();
  ledLights.getCalculationElementLink(1)->debugPrint();
  ledLights.getCalculationElementLink(2)->debugPrint();
  ledLights.getCalculationElementLink(3)->debugPrint();
  ledLights.getCalculationElementLink(4)->debugPrint();
  Serial.println("Onko vielä?");
  delay(2000);
  */

  /*
  ledLights.debugPrintLedSticks();
  delay(1000);
  ledLights.setLightsToRandom();
  delay(1000);
  ledLights.setLightsToZero();
  delay(1000);

  ledLights.setLightsToTestPattern();
  delay(1000);

*/
  Serial.println("\nloopSetColors alkaa");
  ledLights.loopSetColors(750, NoteState::NO_NOTE, DistanceState::FAR);
  Serial.println("\nloopShow alkaa");
  ledLights.loopShow();



  Serial.println("");
  Serial.println("");
  Serial.println("setup done.");
}

double r0, r1;
AvgFilterD rFilter0;
AvgFilterD rFilter1;
void printR(void) {
  serialPrintLnDouble("r0:[", rFilter0.getValue(), "]");
  serialPrintLnDouble("r1:[", rFilter1.getValue(), "]");
}
CallbackTimer *printRTimer = new CallbackTimer(printR, millis(), 1000);


void loop() {
  serialPrintMillisTimer->loop(millis());

  //printRTimer->loop(millis());

  long a0 = analogRead(54);
  long a1 = analogRead(55);


  r0 = map_double_limit(a0, 0, 689, 0.0, 2.0 * 3.141596 * 16.0, 5.0);
  r1 = map_double_limit(a1, 0, 662, 0.0, 2.0 * 3.141596 * 4.0);
  r0 = 0.0;
  r1 = 1.0;
  rFilter0.putValue(r0);
  rFilter1.putValue(r1);

  double phase = 3.1415;
  double frequency = 1.0;
  double amplitude = 0.4;
  double offset = 0.6;

  //ledLightCalculationSine->setParameters(rFilter0.getValue(), rFilter1.getValue(), amplitude, offset);
  ledLights.loopSetColors(millis(), NoteState::NO_NOTE, DistanceState::FAR);
  //ledLights.loopSetColors(1.0*3.14159265359*1000, NoteState::NO_NOTE, DistanceState::FAR);
  ledLights.loopShow();

  delay(50);
}
