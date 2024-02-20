// Shape.cpp
#include "Shape.h"
#include <Arduino.h>

Shape::Shape() {
  Serial.println("Shape constructor");
}

Shape::~Shape() {
  Serial.println("Shape destructor");
}
