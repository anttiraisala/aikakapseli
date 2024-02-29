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
        ledLightCalculationValue.setValue(pow(valueA.getValueV(), valueB.getValueV()));
        break;

      case LedLightCalculationTwoOperandsOperation::POW:
        ledLightCalculationValue.setValue(valueA.getValueV() - valueB.getValueV());
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

  return this->ledLightCalculationValue;
}