
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
#include "LedLightCalculationConstant.h"
#include "LedLightCalculationSine.h"




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

  CalculationElementPhaseMapping cepm1;
  cepm1.startPhase=0.0;
  cepm1.endPhase=2.0*3.14159265358/19.0*9.0;
  CalculationElementPhaseMapping cepm2;
  cepm2.startPhase=2.0*3.14159265358/19.0*10.0;
  cepm2.endPhase=2.0*3.14159265358;

  
  CalculationElementPhaseMapping cepm;

  ledLights.setCalculations(0, new LedLightCalculationSine(3.1415, 1.0, 0.4, 0.6), cepm1);
  ledLights.setCalculations(1, new LedLightCalculationConstant(0.0, 255, 0.0), cepm);
  ledLights.setCalculations(2, new LedLightCalculationSine(3.1415, 1.0, 0.4, 0.6), cepm1);
  ledLights.setCalculations(3, new LedLightCalculationSine(3.1415, 1.0, 0.4, 0.6), cepm2);
  ledLights.setCalculations(4, new LedLightCalculationConstant(255.0, 0.0, 255.0), cepm);
  ledLights.setCalculations(5, new LedLightCalculationConstant(0.0, 255.0, 255.0), cepm);
  ledLights.setCalculations(6, new LedLightCalculationConstant(128.0, 0.0, 255.0), cepm);
  ledLights.setCalculations(7, new LedLightCalculationConstant(0.0, 128.0, 255.0), cepm);



  Serial.println("");
  Serial.println("tests done.");
  Serial.println("");
  Serial.println("");
}



void setup() {
  randomSeed(analogRead(0));
  // put your setup code here, to run once:
  Serial.begin(9600);
  delay(2000);

  Serial.println("setup starts...");
  delay(1000);

  ledLights.init();
  delay(1000);

  tests();
  delay(1000);

  ledLights.debugPrintLedSticks();
  delay(1000);
  ledLights.setLightsToRandom();
  delay(1000);
  ledLights.setLightsToZero();
  delay(1000);

  ledLights.setLightsToTestPattern();
  delay(1000);


  ledLights.loopSetColors(750, NoteState::NO_NOTE, DistanceState::FAR);
  ledLights.loopShow();



  Serial.println("");
  Serial.println("");
  Serial.println("setup done.");
}

void loop() {


  delay(100);
}
