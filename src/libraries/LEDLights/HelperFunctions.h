#ifndef HELPER_FUNCTIONS_H
#define HELPER_FUNCTIONS_H

#include <Arduino.h>

// double value to string buffer
// char *dtostrf(double val, signed char width, unsigned char prec, char *s)

void serialPrintDouble(char *prefix, double value, char *postfix);
void serialPrintLnDouble(char *prefix, double value, char *postfix);
void serialPrintLnDouble(char *prefix, double value);
void serialPrintDouble(char *prefix, double value);
void serialPrintDouble(double value);
void serialPrintLnDouble(double value);

double map_double(double value, double from_min, double from_max, double to_min, double to_max);
double map_double_limit(double value, double from_min, double from_max, double to_min, double to_max);
double map_double(double value, double from_min, double from_max, double to_min, double to_max, double unlinearityPower);
double map_double_limit(double value, double from_min, double from_max, double to_min, double to_max, double unlinearityPower);

class AvgFilterD {
  public:
  AvgFilterD(void);
  double getValue(void);
  void putValue(double value);

  private:
  #define ARRAY_SIZE 40
  double array[ARRAY_SIZE];
  byte arrayPtr;
};


#endif  // HELPER_FUNCTIONS_H