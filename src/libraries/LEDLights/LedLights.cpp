#include "Adafruit_NeoPixel.h"
#include "LedLights.h"
#include "HelperFunctions.h"


LedLights::LedLights() {
}

void LedLights::debugPrintLedSticks(void) {
  Serial.println("\nLedLights::debugPrintLedSticks() begin");

  Adafruit_NeoPixel *neoPixel;
  CalculationElementLink *calculationElementLink;

  Serial.print("LED_STICK_COUNT: ");
  Serial.println(LED_STICK_COUNT, DEC);

  for (byte i = 0; i < LED_STICK_COUNT; i++) {
    sLedStick ledStick = this->sLedSticks[i];
    Serial.print("index: ");
    Serial.println(i, DEC);

    neoPixel = ledStick.neoPixel;
    if (neoPixel != nullptr) {
      Serial.print("  pin ");
      Serial.print(neoPixel->getPin(), DEC);
    } else {
      Serial.println("  neoPixel == nullptr");
    }

    calculationElementLink = ledStick.calculationElementLink;
    if (calculationElementLink != nullptr) {
      calculationElementLink->debugPrint();
    } else {
      Serial.println("  calculationElementLink == nullptr");
    }





    Serial.println("");
  }

  Serial.println("LedLights::debugPrintLedSticks() end");
}

/*
struct sLedStick {
  Adafruit_NeoPixel *neoPixel;
  CalculationElementLink *calculationElementLink;
};
*/

void LedLights::init(void) {
  //Serial.println("LedLights::init() begin");

  currentTimeMillis = previousTimeMillis = millis();
  deltaTimeMillis = 0;

  for (byte i = 0; i < LED_STICK_COUNT; i++) {
    sLedStick emptyStick;
    emptyStick.neoPixel = nullptr;
    emptyStick.calculationElementLink = nullptr;
    sLedSticks[i] = emptyStick;
  }

  this->setLedStick(0, 2);
  this->setLedStick(1, 3);
  this->setLedStick(2, 4);
  this->setLedStick(3, 5);
  this->setLedStick(4, 6);

  this->setLedStick(5, 7);
  this->setLedStick(6, 8);
  this->setLedStick(7, 57);


  //Serial.println("LedLights::init() end");
}

/*
struct sLedStick {
  Adafruit_NeoPixel *neoPixel;
  CalculationElementLink *calculationElementLink;
};

*/

CalculationElementLink *LedLights::getCalculationElementLink(byte index) {
  sLedStick ledStick = this->sLedSticks[index];
  return ledStick.calculationElementLink;
}

void LedLights::setCalculationElementLink(byte index, CalculationElementLink *calculationElementLink) {
  /*Serial.print("LedLights::setCalculationElementLink() begin :");
  Serial.print(index, DEC);
  Serial.println();
*/
  /*
struct sLedStick {
  Adafruit_NeoPixel *neoPixel;
  CalculationElementLink *calculationElementLink;
};
*/

  //calculationElementLink->debugPrint();


  sLedStick *ledStick = &(this->sLedSticks[index]);
  ledStick->calculationElementLink = calculationElementLink;

  //Serial.println("LedLights::setCalculationElementLink() end");
}

void LedLights::setLedStick(byte index, byte pin) {
  /* Serial.print("LedLights::setLedStick() begin :");
  Serial.print(pin, DEC);
  Serial.println();*/

  sLedStick ledStick;
  ledStick.calculationElementLink = nullptr;
  ledStick.neoPixel = new Adafruit_NeoPixel(10, pin, NEO_GRB + NEO_KHZ800);
  ledStick.neoPixel->begin();
  ledStick.neoPixel->setBrightness(255);
  for (byte led = 0; led < 10; led++) {
    //ledStick.neoPixel.setPixelColor(led, random(256), random(256), random(256));
    ledStick.neoPixel->setPixelColor(led, random(256), random(256), random(256));
  }
  ledStick.neoPixel->show();
  this->sLedSticks[index] = ledStick;

  //Serial.println("LedLights::setLedStick() end");
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

  loopSetColorsCounter++;

  Adafruit_NeoPixel *neoPixel;
  CalculationElementLink *calculationElementLink;
  LedLightCalculationElement *calculationElement;

  /*
struct sLedStick {
  Adafruit_NeoPixel *neoPixel;
  CalculationElementLink *calculationElementLink;
};
*/

  /*
class CalculationElementLink {
private:
  LedLightCalculationElement *element = nullptr;
  CalculationElementPhaseMapping *mapping = nullptr;
*/

  // Loop through LEDSticks
  for (byte i = 0; i < LED_STICK_COUNT; i++) {

    neoPixel = this->sLedSticks[i].neoPixel;
    if (neoPixel == nullptr) {
      continue;
    }

    calculationElementLink = this->sLedSticks[i].calculationElementLink;
    if (calculationElementLink == nullptr) {
      continue;
    }

    calculationElement = calculationElementLink->getCalculationElement();
    if (calculationElement == nullptr) {
      continue;
    }


    //calculationElementLink->debugPrint(); delay(1000);

    // Loop throught single LEDs
    for (byte led = 0; led < 10; led++) {

      double relativePhase = 1.0 / 9.0 * (double)led;

      LedLightCalculationValue ledLightCalculationValue = calculationElement->getValue(loopSetColorsCounter, getCurrentTimeSeconds(), calculationElementLink->getMappedRelativePhase(relativePhase));

      byte r = ledLightCalculationValue.getValueBytes().r;
      byte g = ledLightCalculationValue.getValueBytes().g;
      byte b = ledLightCalculationValue.getValueBytes().b;

      neoPixel->setPixelColor(led, r, g, b);
    }
  }

  //Serial.println("LedLights::loopSetColors() end");
}

void LedLights::loopShow(void) {
  // Serial.println("LedLights::loopShow() begin");

  Adafruit_NeoPixel *neoPixel;

  for (byte i = 0; i < LED_STICK_COUNT; i++) {
    neoPixel = this->sLedSticks[i].neoPixel;
    if (neoPixel == nullptr) {
      continue;
    }
    neoPixel->show();
  }

  //  Serial.println("LedLights::loopShow() end");
}

double LedLights::getCurrentTimeSeconds(void) {
  return (double)(this->currentTimeMillis) / 1000.0f;
}