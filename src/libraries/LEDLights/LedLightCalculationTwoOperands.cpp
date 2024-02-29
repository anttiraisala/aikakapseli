#include "LedLightCalculationTwoOperands.h"

LedLightCalculationTwoOperands::LedLightCalculationTwoOperands(LedLightCalculationTwoOperandsOperation operation, LedLightCalculationElement elementA, LedLightCalculationElement elementB) {
  this->operation = operation;
  this->elementA = elementA;
  this->elementB = elementB;
}

LedLightCalculationValue LedLightCalculationTwoOperands::getValue(double currentTimeSeconds, double relativePhase, CalculationElementPhaseMapping calculationElementPhaseMapping) {
  /*
  ADD,
    SUBTRACT,
    MULTIPLY,
    DIVIDE,
    POW,
    MAX,
    MIN
*/

  LedLightCalculationValue valueA = elementA.getValue(currentTimeSeconds, relativePhase, calculationElementPhaseMapping);
  LedLightCalculationValue valueB = elementB.getValue(currentTimeSeconds, relativePhase, calculationElementPhaseMapping);

  if (valueA.isValue() && valueB.isValue()) {
    switch (operation) {
      case LedLightCalculationTwoOperandsOperation::ADD:
        ledLightCalculationValue.setValue(valueA.getValueV() + valueB.getValueV());
        break;

      case LedLightCalculationTwoOperandsOperation::SUBTRACT:
        ledLightCalculationValue.setValue(valueA.getValueV() - valueB.getValueV());
        break;

      case LedLightCalculationTwoOperandsOperation::MULTIPLY:
        ledLightCalculationValue.setValue(valueA.getValueV() - valueB.getValueV());
        break;

      case LedLightCalculationTwoOperandsOperation::DIVIDE:
        ledLightCalculationValue.setValue(valueA.getValueV() / valueB.getValueV());
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

    this->ledLightCalculationValue.setValue(r, g, b);

    return this->ledLightCalculationValue;
  }


  return this->ledLightCalculationValue;
}