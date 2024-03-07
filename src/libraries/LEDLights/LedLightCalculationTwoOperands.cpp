#include "LedLightCalculationTwoOperands.h"

LedLightCalculationTwoOperands::LedLightCalculationTwoOperands(void) {}

LedLightCalculationTwoOperands::LedLightCalculationTwoOperands(LedLightCalculationTwoOperandsOperation operation) {
  this->operation = operation;
}

LedLightCalculationTwoOperands::LedLightCalculationTwoOperands(LedLightCalculationTwoOperandsOperation operation, CalculationElementLink *elementLinkA, CalculationElementLink *elementLinkB) {
  this->operation = operation;
  this->elementLinkA = elementLinkA;
  this->elementLinkB = elementLinkB;
}

LedLightCalculationTwoOperands::LedLightCalculationTwoOperands(CalculationElementLink *elementLinkA, CalculationElementLink *elementLinkB) {
  this->elementLinkA = elementLinkA;
  this->elementLinkB = elementLinkB;
}

LedLightCalculationTwoOperands *LedLightCalculationTwoOperands::setOperation(LedLightCalculationTwoOperandsOperation operation) {
  this->operation = operation;
  return this;
}

double lerp(double control, double a, double b) {
  return (b - a) * control + a;
}

static void LedLightCalculationTwoOperands::performOperation(LedLightCalculationValue *resultValue, LedLightCalculationTwoOperandsOperation operation, LedLightCalculationValue *valueA, LedLightCalculationValue *valueB) {
  performOperation(resultValue, operation, nullptr, valueA, valueB);
}

static void LedLightCalculationTwoOperands::performOperation(LedLightCalculationValue *resultValue, LedLightCalculationTwoOperandsOperation operation, LedLightCalculationValue *controlValue, LedLightCalculationValue *valueA, LedLightCalculationValue *valueB) {


  if (valueA->isValue() && valueB->isValue()) {
    switch (operation) {
      case LedLightCalculationTwoOperandsOperation::ADD:
        resultValue->setValue(valueA->getValueV() + valueB->getValueV());
        break;

      case LedLightCalculationTwoOperandsOperation::SUBTRACT:
        resultValue->setValue(valueA->getValueV() - valueB->getValueV());
        break;

      case LedLightCalculationTwoOperandsOperation::MULTIPLY:
        resultValue->setValue(valueA->getValueV() * valueB->getValueV());
        break;

      case LedLightCalculationTwoOperandsOperation::DIVIDE:
        if (valueB->getValueV() != 0.0) {
          resultValue->setValue(valueA->getValueV() / valueB->getValueV());
        } else {
          resultValue->setValue(0.0);
          Serial.println("ERROR: Tried to divide by zero.");
        }
        break;

      case LedLightCalculationTwoOperandsOperation::POW:
        resultValue->setValue(pow(valueA->getValueV(), valueB->getValueV()));
        break;

      case LedLightCalculationTwoOperandsOperation::MAX:
        if (valueA->getValueV() > valueB->getValueV()) {
          resultValue->setValue(valueA->getValueV());
        } else {
          resultValue->setValue(valueB->getValueV());
        }
        break;

      case LedLightCalculationTwoOperandsOperation::MIN:
        if (valueA->getValueV() < valueB->getValueV()) {
          resultValue->setValue(valueA->getValueV());
        } else {
          resultValue->setValue(valueB->getValueV());
        }
        break;

      case LedLightCalculationTwoOperandsOperation::CROSS_DISSOLVE:
        resultValue->setValue(lerp(controlValue->getValueV(), valueA->getValueV(), valueB->getValueV()));
        break;
    }

    return;
  }

  if (valueA->isColor() && valueB->isColor()) {
    if (operation == LedLightCalculationTwoOperandsOperation::CROSS_DISSOLVE) {
      resultValue->setValue(
        lerp(controlValue->getValueV(), valueA->getValueR(), valueB->getValueR()),
        lerp(controlValue->getValueV(), valueA->getValueG(), valueB->getValueG()),
        lerp(controlValue->getValueV(), valueA->getValueB(), valueB->getValueB()));
      return;
    }

    // R
    double r = 0.0;
    if (valueA->getValueR() > valueB->getValueR()) {
      r = valueA->getValueR();
    } else {
      r = valueB->getValueR();
    }
    // G
    double g = 0.0;
    if (valueA->getValueG() > valueB->getValueG()) {
      g = valueA->getValueG();
    } else {
      g = valueB->getValueG();
    }
    // B
    double b = 0.0;
    if (valueA->getValueB() > valueB->getValueB()) {
      b = valueA->getValueB();
    } else {
      b = valueB->getValueB();
    }

    resultValue->setValue(r, g, b);

    return;
  }

  if (valueA->isColor() && valueB->isValue()) {
    LedLightCalculationValue *temp = valueA;
    valueA = valueB;
    valueB = temp;
  }

  if (valueA->isValue() && valueB->isColor()) {
    double r = valueA->getValueV() * valueB->getValueR();
    double g = valueA->getValueV() * valueB->getValueG();
    double b = valueA->getValueV() * valueB->getValueB();

    resultValue->setValue(r, g, b);

    return;
  }
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

  performOperation(&ledLightCalculationValue, operation, &valueA, &valueB);

  return ledLightCalculationValue;
}
