// Circle.cpp
#include "Circle.h"
#include <Arduino.h>

Circle::Circle(float r) : data(new float) {
  *data = r;
  Serial.println("Circle constructor");
}

Circle::~Circle() {
  delete data; // Release dynamically allocated memory
  Serial.println("Circle destructor");
}

float Circle::calculateArea() const {
  return PI * (*data) * (*data);
}

void Circle::printArea() const {
  Serial.print("Circle Area: ");
  Serial.println(calculateArea());
}
