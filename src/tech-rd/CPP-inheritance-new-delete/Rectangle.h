// Rectangle.h
#ifndef RECTANGLE_H
#define RECTANGLE_H
#include "Shape.h"

class Rectangle : public Shape {
private:
  float* data;

public:
  Rectangle(float w, float h);
  ~Rectangle() override;

  float calculateArea() const override;
  void printArea() const override;
};

#endif // RECTANGLE_H
