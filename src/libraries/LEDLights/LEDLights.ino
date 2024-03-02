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

LedLightCalculationSine *ledLightCalculationSine;
void tests(void) {
  Serial.println("");
  Serial.println("");
  Serial.println("tests begin...");

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

  CalculationElementPhaseMapping cepm0;
  int ledCount = 49;
  double endPhase = 10.0;

  CalculationElementPhaseMapping cepm;

  ledLightCalculationSine = new LedLightCalculationSine(0.0, 0.1, 0.4, 0.6);
  ledLights.setCalculationElementLink(0, new CalculationElementLink(ledLightCalculationSine, endPhase / ledCount * 00.0, endPhase / ledCount * 09.0));
  ledLights.setCalculationElementLink(1, new CalculationElementLink(ledLightCalculationSine, endPhase / ledCount * 10.0, endPhase / ledCount * 19.0));
  ledLights.setCalculationElementLink(2, new CalculationElementLink(ledLightCalculationSine, endPhase / ledCount * 20.0, endPhase / ledCount * 29.0));
  ledLights.setCalculationElementLink(3, new CalculationElementLink(ledLightCalculationSine, endPhase / ledCount * 30.0, endPhase / ledCount * 39.0));
  ledLights.setCalculationElementLink(4, new CalculationElementLink(ledLightCalculationSine, endPhase / ledCount * 40.0, endPhase / ledCount * 49.0));
  /*
  ledLights.setCalculations(5, new CalculationElementLink(new LedLightCalculationConstant(0.0, 255.0, 255.0), &cepm));
  ledLights.setCalculations(6, new CalculationElementLink(new LedLightCalculationConstant(128.0, 0.0, 255.0), &cepm));
  ledLights.setCalculations(7, new CalculationElementLink(new LedLightCalculationConstant(0.0, 128.0, 255.0), &cepm));
*/

  ledLights.getCalculationElementLink(0)->debugPrint();
  ledLights.getCalculationElementLink(1)->debugPrint();
  ledLights.getCalculationElementLink(2)->debugPrint();
  ledLights.getCalculationElementLink(3)->debugPrint();
  ledLights.getCalculationElementLink(4)->debugPrint();
  Serial.println("Onko vielä?");
  delay(2000);


  Serial.println("");
  Serial.println("tests done.");
  Serial.println("");
  Serial.println("");
}




void setup() {
  randomSeed(analogRead(0));
  // put your setup code here, to run once:
  Serial.begin(9600);

  // Rotary Angle Sensors
  pinMode(54, INPUT);
  pinMode(55, INPUT);



  delay(2000);

  Serial.println("setup starts...");
  delay(1000);

  ledLights.init();
  delay(1000);

  tests();
  delay(1000);
  ledLights.getCalculationElementLink(0)->debugPrint();
  ledLights.getCalculationElementLink(1)->debugPrint();
  ledLights.getCalculationElementLink(2)->debugPrint();
  ledLights.getCalculationElementLink(3)->debugPrint();
  ledLights.getCalculationElementLink(4)->debugPrint();
  Serial.println("Onko vielä?");
  delay(2000);
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
CallbackTimer *printRTimer = new CallbackTimer(printR, millis(), 500);


void loop() {

  printRTimer->loop(millis());

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
