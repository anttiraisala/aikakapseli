// Shape.h
#ifndef SHAPE_H
#define SHAPE_H

class Shape {
public:
  Shape();
  virtual ~Shape(); // Virtual destructor for proper cleanup

  virtual float calculateArea() const = 0;
  virtual void printArea() const = 0;
};

#endif // SHAPE_H
