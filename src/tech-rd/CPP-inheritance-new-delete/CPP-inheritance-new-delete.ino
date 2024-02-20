#include "Shape.h"
#include "Rectangle.h"
#include "Circle.h"
#include <MemoryFree.h>


// Create instances of the classes
#define SHAPE_MAX_COUNT 10
int shapeCount = 0;
Shape* shapes[SHAPE_MAX_COUNT];

void setup() {
  Serial.begin(9600);

  // Dynamically create instances of Rectangle and Circle
  for (int i = 0; i < SHAPE_MAX_COUNT; ++i) {
    Shape* shape = getRandomShape();
    if(shape != nullptr){
      shapes[i] = shape;
      shapeCount++;
       Serial.print("shapeCount: ");
       Serial.println(shapeCount, DEC);
       Serial.print("freeMemory(): ");
       Serial.println(freeMemory(), DEC);
    } else {
      break;
    }    
  }

  serialPrintSizeofs();
}

void serialPrintSizeofs(){
  Serial.print("shapeCount: ");
  Serial.println(shapeCount, DEC);
  Serial.print("sizeof(shapes): ");
  Serial.println(sizeof(shapes), DEC);
  Serial.print("sizeof(Rectangle): ");
  Serial.println(sizeof(Rectangle), DEC);
  Serial.print("sizeof(Circle): ");
  Serial.println(sizeof(Circle), DEC);
  Serial.print("sizeof(float): ");
  Serial.println(sizeof(float), DEC);

  Serial.print("sizeof(kaikki): ");
  Serial.println(shapeCount*(sizeof(Circle)+sizeof(float)/*+sizeof(Rectangle)+sizeof(float)+sizeof(float)*/)+sizeof(shapes), DEC);

  delay(2000);
}

void loop() {
  // Print areas of the shapes
  for (int i = 0; i < shapeCount; ++i) {
    shapes[i]->printArea();
  }

  delay(2000); // Delay for readability in the Serial Monitor

  // Cleanup: Delete dynamically allocated instances
  for (int i = 0; i < shapeCount; ++i) {
    delete shapes[i];
  }

  serialPrintSizeofs();

  Serial.println("bye");

  // Exit loop to avoid continuous creation and deletion in this example
  while (true) {}
}

Shape* getRandomShape(){
  switch(random(2)){
    case 0: 
      return new Circle(random(5)+1);
      /*return new Rectangle(random(4)+1, random(4)+1);*/
      break;
    case 1: 
      return new Circle(random(5)+1);
      break; 
  }

  return 0;
}

