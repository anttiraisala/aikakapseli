#include "LedLightCalculationValue.h"


// This abstract base class (LedLightCalculationElement)
// serves as a placeholder for different calculation types.
// You can further extend this class to create specialized
// calculation elements with specific implementations
// for `getValue`.

LedLightCalculationValue::LedLightCalculationValue() {}

LedLightCalculationValue::LedLightCalculationValue(double valueV) {
  this->setValue(valueV);
}

LedLightCalculationValue::LedLightCalculationValue(double valueR, double valueG, double valueB) {
  this->setValue(valueR, valueG, valueB);
}

ColorAsBytes LedLightCalculationValue::getValueBytes(void) {
  ColorAsBytes v;

  v.r = limitDoubleValue(this->getValueR());
  v.g = limitDoubleValue(this->getValueG());
  v.b = limitDoubleValue(this->getValueB());

  return v;
}

inline byte LedLightCalculationValue::limitDoubleValue(double d) {
  if (d <= 0.0) {
    return 0;
  }

  if (d >= 255.0) {
    return 255;
  }

  return (byte)(d + 0.5);
}

double LedLightCalculationValue::getValueV(void) {
  if (this->isValue) {
    return this->valueV;
  }

  return this->valueR;
}

double LedLightCalculationValue::getValueR(void) {
  if (this->isColor) {
    return this->valueR;
  }

  return this->valueV;
}

double LedLightCalculationValue::getValueG(void) {
  if (this->isColor) {
    return this->valueG;
  }

  return this->valueV;
}

double LedLightCalculationValue::getValueB(void) {
  if (this->isColor) {
    return this->valueB;
  }

  return this->valueV;
}

void LedLightCalculationValue::setValue(double valueV) {
  this->valueV = valueV;
  this->isValue = true;
  this->isColor = false;
}

void LedLightCalculationValue::setValue(double valueR, double valueG, double valueB) {
  this->valueR = valueR;
  this->valueG = valueG;
  this->valueB = valueB;
  this->isValue = false;
  this->isColor = true;
}
