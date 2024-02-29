#include "note_state.h"
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
    Serial.print(ledStick.neoPixel->getPin(), DEC);

    Serial.println("");
  }

  Serial.println("LedLights::debugPrintLedSticks() end");
}

void LedLights::init(void) {
  Serial.println("LedLights::init() begin");

  currentTimeMillis = previousTimeMillis = millis();
  deltaTimeMillis = 0;

  this->setLedStick(0, 2);
  this->setLedStick(1, 3);
  this->setLedStick(2, 4);
  this->setLedStick(3, 5);
  this->setLedStick(4, 6);
  this->setLedStick(5, 7);

  this->setLedStick(6, 8);
  this->setLedStick(7, 57);





  Serial.println("LedLights::init() end");
}

void setCalculations(byte index, LedLightCalculationElement *calculationElement, CalculationElementPhaseMapping calculationElementPhaseMapping);

void LedLights::setCalculations(byte index, LedLightCalculationElement *calculationElement, CalculationElementPhaseMapping calculationElementPhaseMapping) {
  Serial.print("LedLights::setCalculations() begin :");
  Serial.print(index, DEC);
  Serial.println();

  sLedStick ledStick = this->sLedSticks[index];
  ledStick.calculationElement = calculationElement;
  ledStick.calculationElementPhaseMapping = calculationElementPhaseMapping;

  this->sLedSticks[index] = ledStick;

  Serial.println("LedLights::setCalculations() end");
}

void LedLights::setLedStick(byte index, byte pin) {
  Serial.print("LedLights::setLedStick() begin :");
  Serial.print(pin, DEC);
  Serial.println();

  sLedStick ledStick;
  ledStick.neoPixel = new Adafruit_NeoPixel(10, pin, NEO_GRB + NEO_KHZ800);
  ledStick.neoPixel->begin();
  ledStick.neoPixel->setBrightness(255);
  for (byte led = 0; led < 10; led++) {
    //ledStick.neoPixel.setPixelColor(led, random(256), random(256), random(256));
    ledStick.neoPixel->setPixelColor(led, random(256), random(256), random(256));
  }
  ledStick.neoPixel->show();
  this->sLedSticks[index] = ledStick;

  Serial.println("LedLights::setLedStick() end");
}

void LedLights::setLightsToZero(void) {
  //Serial.println("LedLights::setLightsToZero() begin");

  Adafruit_NeoPixel *ledStick;
  for (byte i = 0; i < LED_STICK_COUNT; i++) {
    ledStick = this->sLedSticks[i].neoPixel;
    //Serial.print("pin :");
    //Serial.println(ledStick->getPin(), DEC);
    for (byte led = 0; led < 10; led++) {
      ledStick->setPixelColor(led, 0, 0, 0);
    }
  }

  for (byte i = 0; i < LED_STICK_COUNT; i++) {
    ledStick = this->sLedSticks[i].neoPixel;
    ledStick->show();
  }
  //Serial.println("LedLights::setLightsToZero() end");
}

void LedLights::setLightsToRandom(void) {
  //Serial.println("LedLights::setLightsToRandom() begin");

  Adafruit_NeoPixel *ledStick;
  for (byte i = 0; i < LED_STICK_COUNT; i++) {
    ledStick = this->sLedSticks[i].neoPixel;
    //Serial.print("pin :");
    //Serial.println(ledStick->getPin(), DEC);
    for (byte led = 0; led < 10; led++) {
      ledStick->setPixelColor(led, random(256), random(256), random(256));
    }
  }

  for (byte i = 0; i < LED_STICK_COUNT; i++) {
    ledStick = this->sLedSticks[i].neoPixel;
    ledStick->show();
  }
  //Serial.println("LedLights::setLightsToRandom() end");
}

void LedLights::setLightsToTestPattern(void) {
  Serial.println("LedLights::setLightsToTestPattern() begin");

  Adafruit_NeoPixel *ledStick;
  for (byte i = 0; i < LED_STICK_COUNT; i++) {
    ledStick = this->sLedSticks[i].neoPixel;
    Serial.print("pin :");
    Serial.println(ledStick->getPin(), DEC);
    for (byte led = 0; led < 10; led++) {
      if (led <= i) {
        ledStick->setPixelColor(led, 255, random(256), random(256));
      } else {
        ledStick->setPixelColor(led, 0, 0, 0);
      }
    }
  }

  for (byte i = 0; i < LED_STICK_COUNT; i++) {
    ledStick = this->sLedSticks[i].neoPixel;
    ledStick->show();
  }
  Serial.println("LedLights::setLightsToTestPattern() end");
}

void LedLights::loopSetColors(unsigned long currentTimeMillis, NoteState noteState, DistanceState distanceState) {
  //calculationElement
  //Serial.println("LedLights::loopSetColors() begin");

  this->previousTimeMillis = this->currentTimeMillis;
  this->currentTimeMillis = currentTimeMillis;
  this->deltaTimeMillis = this->currentTimeMillis - this->previousTimeMillis;

  Adafruit_NeoPixel *ledStick;
  LedLightCalculationElement *calculationElement;

  /*
  enum class NoteState {
    NO_NOTE,
    INSERTING,
    DROPPED
};
enum class DistanceState {
    FAR,
    NEAR,
    RETREATING
};
*/

  // Loop through LEDSticks
  for (byte i = 0; i < LED_STICK_COUNT; i++) {

    ledStick = this->sLedSticks[i].neoPixel;
    calculationElement = this->sLedSticks[i].calculationElement;
    CalculationElementPhaseMapping calculationElementPhaseMapping = this->sLedSticks[i].calculationElementPhaseMapping;


    if (DistanceState::NEAR == distanceState) {
      ledStick->setBrightness(255);
    }
    if (DistanceState::RETREATING == distanceState) {
      ledStick->setBrightness(130);
    }
    if (DistanceState::FAR == distanceState) {
      ledStick->setBrightness(30);
    }

    // Loop throught single LEDs
    for (byte led = 0; led < 10; led++) {

      double relativePhase = 1.0 / 9.0 * (double)led;

      LedLightCalculationValue ledLightCalculationValue = calculationElement->getValue(getCurrentTimeSeconds(), relativePhase, calculationElementPhaseMapping);

      byte r = ledLightCalculationValue.getValueBytes().r;
      byte g = ledLightCalculationValue.getValueBytes().g;
      byte b = ledLightCalculationValue.getValueBytes().b;

      ledStick->setPixelColor(led, r, g, b);
    }
  }

  //Serial.println("LedLights::loopSetColors() end");
}

void LedLights::loopShow(void) {
  //Serial.println("LedLights::loopShow() begin");


  Adafruit_NeoPixel *ledStick;

  for (byte i = 0; i < LED_STICK_COUNT; i++) {
    ledStick = this->sLedSticks[i].neoPixel;
    ledStick->show();
  }

  //Serial.println("LedLights::loopShow() end");
}

double LedLights::getCurrentTimeSeconds(void) {
  return (double)(this->currentTimeMillis) / 1000.0f;
}