#include "Adafruit_NeoPixel.h"
#include "LedLights.h"


LedLights::LedLights() {
}

void LedLights::debugPrintLedSticks(void) {
  Serial.println("LedLights::debugPrintLedSticks() begin");

  for (byte i = 0; i < LED_STICK_COUNT; i++) {
    sLedStick ledStick = this->sLedSticks[i];
    Serial.print("index: ");
    Serial.print(i, DEC);
    Serial.print(" pin ");
    Serial.print(ledStick.neoPixel.getPin(), DEC);

    Serial.println("");
  }

  Serial.println("LedLights::debugPrintLedSticks() end");
}

void LedLights::init(void) {
  Serial.println("LedLights::init() begin");

  previousTimeMillis = millis();
  deltaTimeMillis = 0;

  this->setLedStick(0, 2);
 this->setLedStick(1, 3);
  this->setLedStick(2, 4);
  this->setLedStick(3, 5);
  this->setLedStick(4, 6);
  //this->setLedStick(5, 7);

  Serial.println("LedLights::init() end");
}

void LedLights::setLedStick(byte index, byte pin) {
  Serial.print("LedLights::setLedStick() begin :");
  Serial.print(pin, DEC);
  Serial.println();

  sLedStick ledStick;
  ledStick.neoPixel = Adafruit_NeoPixel(10, pin, NEO_GRB + NEO_KHZ800);
  ledStick.neoPixel.begin();
  ledStick.neoPixel.setBrightness(255);
  for (byte led = 0; led < 10; led++) {
    //ledStick.neoPixel.setPixelColor(led, random(256), random(256), random(256));
    ledStick.neoPixel.setPixelColor(led, 255, 0, 0);
  }
  ledStick.neoPixel.show();
  this->sLedSticks[index] = ledStick;

  Serial.println("LedLights::setLedStick() end");
}

void LedLights::setLightsToZero(void) {
  Serial.println("LedLights::setLightsToZero() begin");

  Adafruit_NeoPixel ledStick;
  for (byte i = 0; i < LED_STICK_COUNT; i++) {
    ledStick = this->sLedSticks[i].neoPixel;
    Serial.print("pin :");
    Serial.println(ledStick.getPin(), DEC);
    ledStick.begin();
    for (byte led = 0; led < 10; led++) {
      //ledStick.setPixelColor(led, 0, 0, 0);
      ledStick.setPixelColor(led, 0, random(256), 0);
    }
    ledStick.show();
  }
  /*
  for (byte i = 0; i < LED_STICK_COUNT; i++) {
    ledStick = this->sLedSticks[i].neoPixel;
    ledStick.show();
  }
  */
  Serial.println("LedLights::setLightsToZero() end");
}

void LedLights::setLightsToTestPattern(void) {}

void LedLights::loopSetColors(unsigned long currentTimeMillis, NoteState noteState, DistanceState distanceState) {}
void LedLights::loopShow(void) {}