#include "HelperFunctions.h"


void serialPrintDouble(char *prefix, double value, char *postfix) {
  char buffer[30];
  dtostrf(value, 0, 6, buffer);
  if (prefix != nullptr) Serial.print(prefix);
  Serial.print(buffer);
  if (postfix != nullptr) Serial.print(postfix);
}

void serialPrintLnDouble(char *prefix, double value, char *postfix) {
  serialPrintDouble(prefix, value, postfix);
  Serial.println("");
}

void serialPrintLnDouble(char *prefix, double value) {
  serialPrintDouble(prefix, value, "\n");
}

void serialPrintDouble(char *prefix, double value) {
  serialPrintDouble(prefix, value, nullptr);
}

void serialPrintDouble(double value) {
  serialPrintDouble(value);
}

void serialPrintLnDouble(double value) {
  serialPrintDouble(nullptr, value, "\n");
}


double map_double(double value, double from_min, double from_max, double to_min, double to_max) {

  if (from_max - from_min == 0) {
    return from_min;
  }

  double slope = 1.0 * (to_max - to_min) / (from_max - from_min);
  double output = to_min + slope * (value - from_min);

  return output;
}

double map_double_limit(double value, double from_min, double from_max, double to_min, double to_max) {
  double tempValue = map_double(value, from_min, from_max, to_min, to_max);
  if (tempValue < to_min) {
    return to_min;
  }

  if (tempValue > to_max) {
    return to_max;
  }

  return tempValue;
}


double map_double(double value, double from_min, double from_max, double to_min, double to_max, double unlinearityPower) {
  if (from_max - from_min == 0) {
    return from_min;
  }

  double normalizedValue = (value - from_min) / (from_max - from_min);
  if (unlinearityPower != 1.0) {
    normalizedValue = pow(normalizedValue, unlinearityPower);
  }
  return normalizedValue * (to_max - to_min) + to_min;
}

double map_double_limit(double value, double from_min, double from_max, double to_min, double to_max, double unlinearityPower) {
  double tempValue = map_double(value, from_min, from_max, to_min, to_max, unlinearityPower);
  if (tempValue < to_min) {
    return to_min;
  }

  if (tempValue > to_max) {
    return to_max;
  }

  return tempValue;
}

/*
class avgFilterD {
  #define ARRAY_SIZE 3

  public:
  double getValue(void);
  void putValue(double value);

  private:
  double *array;
};*/


AvgFilterD::AvgFilterD() {
  arrayPtr = 0;
}

void AvgFilterD::putValue(double value) {
  this->array[arrayPtr] = value;
  if (++arrayPtr >= ARRAY_SIZE) {
    arrayPtr = 0;
  }
}

double AvgFilterD::getValue(void) {
  double sum = 0;
  for (byte i = 0; i < ARRAY_SIZE; i++) {
    sum += this->array[i];
  }
  return sum / (double)ARRAY_SIZE;
}
