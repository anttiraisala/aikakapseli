#include "LedLights.h"

/* Asiakkaan etäisyys -tilat */
#include "distance_state.h"
DistanceState distanceState = DistanceState::FAR;


/* Viestin asettaminen -tilat */
#include "note_state.h"
NoteState noteState = NoteState::NO_NOTE;


LedLights ledLights;


Adafruit_NeoPixel *pixels;

Adafruit_NeoPixel *getAdafruit_NeoPixel(byte pin) {
  Adafruit_NeoPixel *pixels = new Adafruit_NeoPixel(10, pin, NEO_GRB + NEO_KHZ800);
  pixels->begin();
  pixels->setBrightness(255);
  return pixels;
}

void setup() {
  randomSeed(analogRead(0));
  // put your setup code here, to run once:
  Serial.begin(9600);
  delay(2000);

  Serial.println("setup starts...");
  delay(1000);

  ledLights.init();
  ledLights.debugPrintLedSticks();
  ledLights.setLightsToZero();

  ledLights.setLightsToTestPattern();

  /*pixels = Adafruit_NeoPixel(10, 7, NEO_GRB + NEO_KHZ800);
  pixels.begin();
  pixels.setBrightness(255);*/
  pixels = getAdafruit_NeoPixel(7);
  //pixels->begin();
  //pixels->setBrightness(255);

  for (int i = 0; i < 10; i++) {
    pixels->setPixelColor(i, random(256), random(256), random(256));
  }
  pixels->show();



  Serial.println("setup done.");
}

void loop() {
  // put your main code here, to run repeatedly:
  for (int i = 0; i < 10; i++) {
    pixels->setPixelColor(i, random(256), random(256), random(256));
  }
  pixels->show();

  delay(100);
}
