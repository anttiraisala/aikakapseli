// Circle.h
#ifndef CIRCLE_H
#define CIRCLE_H
#include "Shape.h"

class Circle : public Shape {
private:
  float* data;

public:
  Circle(float r);
  ~Circle() override;

  float calculateArea() const override;
  void printArea() const override;
};

#endif // CIRCLE_H
