// Rectangle.cpp
#include "Rectangle.h"
#include <Arduino.h>

Rectangle::Rectangle(float w, float h) : data(new float[2]) {
  data[0] = w;
  data[1] = h;
  Serial.println("Rectangle constructor");
}

Rectangle::~Rectangle() {
  delete[] data; // Release dynamically allocated memory
  Serial.println("Rectangle destructor");
}

float Rectangle::calculateArea() const {
  return data[0] * data[1];
}

void Rectangle::printArea() const {
  Serial.print("Rectangle Area: ");
  Serial.println(calculateArea());
}
