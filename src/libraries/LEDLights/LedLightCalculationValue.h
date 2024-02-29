#ifndef LEDLIGHT_CALCULATION_VALUE_H
#define LEDLIGHT_CALCULATION_VALUE_H

#include <Arduino.h>



struct ColorAsBytes {
  byte r = 0;
  byte g = 0;
  byte b = 0;
};

// Include necessary headers for your LedLightCalculationValue implementation
// (e.g., math libraries, data structures)

class LedLightCalculationValue {
public:
  // Constructor
  LedLightCalculationValue();
  LedLightCalculationValue(double value);
  LedLightCalculationValue(double valueR, double valueG, double valueB);

  double getValueV(void);
  double getValueR(void);
  double getValueG(void);
  double getValueB(void);
  ColorAsBytes getValueBytes(void);

  void setValue(double valueV);
  void setValue(double valueR, double valueG, double valueB);

  bool isValue(void) {
    return this->bIsValue;
  }

  bool isColor(void) {
    return this->bIsColor;
  }

private:

  byte limitDoubleValue(double d);

  double valueV;

  double valueR;
  double valueG;
  double valueB;

  bool bIsValue;
  bool bIsColor;
};

#endif  // LEDLIGHT_CALCULATION_VALUE_H