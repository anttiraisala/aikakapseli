#include "LedLightCalculationTwoOperands.h"

LedLightCalculationTwoOperands::LedLightCalculationTwoOperands(LedLightCalculationTwoOperandsOperation operation, CalculationElementLink *elementLinkA, CalculationElementLink *elementLinkB) {
  this->operation = operation;
  this->elementLinkA = elementLinkA;
  this->elementLinkB = elementLinkB;
}

LedLightCalculationTwoOperands *LedLightCalculationTwoOperands::setOperation(LedLightCalculationTwoOperandsOperation operation) {
  this->operation = operation;
  return this;
}

LedLightCalculationValue LedLightCalculationTwoOperands::getValue(unsigned long loopSetColorsCounter, double currentTimeSeconds, double relativePhase) {
  /*
  ADD,
    SUBTRACT,
    MULTIPLY,
    DIVIDE,
    POW,
    MAX,
    MIN
*/
  /*
    neoPixel = this->sLedSticks[i].neoPixel;
    calculationElementLink = this->sLedSticks[i].calculationElementLink;
    calculationElement = calculationElementLink->getCalculationElement();

    //calculationElementLink->debugPrint(); delay(1000);

    // Loop throught single LEDs
    for (byte led = 0; led < 10; led++) {

      double relativePhase = 1.0 / 9.0 * (double)led;

      LedLightCalculationValue ledLightCalculationValue = calculationElement->getValue(loopSetColorsCounter, getCurrentTimeSeconds(), calculationElementLink->getMappedRelativePhase(relativePhase));

*/

  LedLightCalculationElement *calculationElementA = elementLinkA->getCalculationElement();
  LedLightCalculationElement *calculationElementB = elementLinkB->getCalculationElement();

  LedLightCalculationValue valueA = calculationElementA->getValue(loopSetColorsCounter, currentTimeSeconds, elementLinkA->getMappedRelativePhase(relativePhase));
  LedLightCalculationValue valueB = calculationElementB->getValue(loopSetColorsCounter, currentTimeSeconds, elementLinkB->getMappedRelativePhase(relativePhase));

  if (valueA.isValue() && valueB.isValue()) {
    switch (operation) {
      case LedLightCalculationTwoOperandsOperation::ADD:
        ledLightCalculationValue.setValue(valueA.getValueV() + valueB.getValueV());
        break;

      case LedLightCalculationTwoOperandsOperation::SUBTRACT:
        ledLightCalculationValue.setValue(valueA.getValueV() - valueB.getValueV());
        break;

      case LedLightCalculationTwoOperandsOperation::MULTIPLY:
        ledLightCalculationValue.setValue(valueA.getValueV() * valueB.getValueV());
        break;

      case LedLightCalculationTwoOperandsOperation::DIVIDE:
        if (valueB.getValueV() != 0.0) {
          ledLightCalculationValue.setValue(valueA.getValueV() / valueB.getValueV());
        } else {
          ledLightCalculationValue.setValue(0.0);
          Serial.println("ERROR: Tried to divide by zero.");
        }
        break;

      case LedLightCalculationTwoOperandsOperation::POW:
        ledLightCalculationValue.setValue(pow(valueA.getValueV(), valueB.getValueV()));
        break;

      case LedLightCalculationTwoOperandsOperation::MAX:
        if (valueA.getValueV() > valueB.getValueV()) {
          ledLightCalculationValue.setValue(valueA.getValueV());
        } else {
          ledLightCalculationValue.setValue(valueB.getValueV());
        }
        break;

      case LedLightCalculationTwoOperandsOperation::MIN:
        if (valueA.getValueV() < valueB.getValueV()) {
          ledLightCalculationValue.setValue(valueA.getValueV());
        } else {
          ledLightCalculationValue.setValue(valueB.getValueV());
        }
        break;
    }

    return this->ledLightCalculationValue;
  }

  if (valueA.isColor() && valueB.isColor()) {
    // R
    double r = 0.0;
    if (valueA.getValueR() > valueB.getValueR()) {
      r = valueA.getValueR();
    } else {
      r = valueB.getValueR();
    }
    // G
    double g = 0.0;
    if (valueA.getValueG() > valueB.getValueG()) {
      g = valueA.getValueG();
    } else {
      g = valueB.getValueG();
    }
    // B
    double b = 0.0;
    if (valueA.getValueB() > valueB.getValueB()) {
      b = valueA.getValueB();
    } else {
      b = valueB.getValueB();
    }

    this->ledLightCalculationValue.setValue(r, g, b);

    return this->ledLightCalculationValue;
  }

  if (valueA.isColor() && valueB.isValue()) {
    LedLightCalculationValue temp = valueA;
    valueA = valueB;
    valueB = temp;
  }

  if (valueA.isValue() && valueB.isColor()) {
    double r = valueA.getValueV() * valueB.getValueR();
    double g = valueA.getValueV() * valueB.getValueG();
    double b = valueA.getValueV() * valueB.getValueB();

    ledLightCalculationValue.setValue(r, g, b);

    return this->ledLightCalculationValue;
  }


  return this->ledLightCalculationValue;
}