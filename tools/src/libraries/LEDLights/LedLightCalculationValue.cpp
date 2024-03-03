#include "HardwareSerial.h"
#include "LedLightCalculationValue.h"
#include "HelperFunctions.h"

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
  if (this->bIsValue) {
    return this->valueV;
  }

  return this->valueR;
}

double LedLightCalculationValue::getValueR(void) {
  if (this->bIsColor) {
    return this->valueR;
  }

  return this->valueV;
}

double LedLightCalculationValue::getValueG(void) {
  if (this->bIsColor) {
    return this->valueG;
  }

  return this->valueV;
}

double LedLightCalculationValue::getValueB(void) {
  if (this->bIsColor) {
    return this->valueB;
  }

  return this->valueV;
}

void LedLightCalculationValue::setValue(double valueV) {
  this->valueV = valueV;
  this->bIsValue = true;
  this->bIsColor = false;
}

void LedLightCalculationValue::setValue(double valueR, double valueG, double valueB) {
  this->valueR = valueR;
  this->valueG = valueG;
  this->valueB = valueB;
  this->bIsValue = false;
  this->bIsColor = true;
}

void LedLightCalculationValue::debugPrint(void) {
  Serial.println("\nLedLightCalculationValue::debugPrint -begins");
  Serial.print("bIsValue: ");
  Serial.println(bIsValue);
  Serial.print("bIsColor: ");
  Serial.println(bIsColor);
  serialPrintLnDouble("valueV: ", valueV);
  serialPrintLnDouble("valueR: ", valueR);
  serialPrintLnDouble("valueG: ", valueG);
  serialPrintLnDouble("valueB: ", valueB);
  serialPrintLnDouble("getValueV(): ", getValueV());
  serialPrintLnDouble("getValueR(): ", getValueR());
  serialPrintLnDouble("getValueG(): ", getValueG());
  serialPrintLnDouble("getValueB(): ", getValueB());
  Serial.println("LedLightCalculationValue::debugPrint -done");
}
