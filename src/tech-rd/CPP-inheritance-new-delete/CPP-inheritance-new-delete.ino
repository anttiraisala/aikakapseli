#include "Shape.h"
#include "Rectangle.h"
#include "Circle.h"

// Create instances of the classes
Shape* shapes[2];

void setup() {
  Serial.begin(9600);

  // Dynamically create instances of Rectangle and Circle
  shapes[0] = new Rectangle(5.0, 3.0);
  shapes[1] = new Circle(2.5);
}

void loop() {
  // Print areas of the shapes
  for (int i = 0; i < 2; ++i) {
    shapes[i]->printArea();
  }

  delay(2000); // Delay for readability in the Serial Monitor

  // Cleanup: Delete dynamically allocated instances
  for (int i = 0; i < 2; ++i) {
    delete shapes[i];
  }

  // Exit loop to avoid continuous creation and deletion in this example
  while (true) {}
}
