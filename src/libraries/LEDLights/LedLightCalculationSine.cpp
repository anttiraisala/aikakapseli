#include "LedLightCalculationSine.h"
#include "HelperFunctions.h"

LedLightCalculationSine::LedLightCalculationSine() {}

LedLightCalculationSine::LedLightCalculationSine(double timeRatio, double phase, double frequency, double amplitude, double offset) {
  this->setParameters(timeRatio, phase, frequency, amplitude, offset);
}

void LedLightCalculationSine::setParameters(double timeRatio, double phase, double frequency, double amplitude, double offset) {
  this->timeRatio = timeRatio;
  this->phase = phase;
  this->frequency = frequency;
  this->amplitude = amplitude;
  this->offset = offset;
  /*
  Serial.println("\nLedLightCalculationSine::setParameters");
  serialPrintLnDouble("  p: ", this->phase);
  serialPrintLnDouble("  f: ", this->frequency);
  serialPrintLnDouble("  a: ", this->amplitude);
  serialPrintLnDouble("  o: ", this->offset);
*/
}

LedLightCalculationValue LedLightCalculationSine::getValue(unsigned long loopSetColorsCounter, double currentTimeSeconds, double relativePhase) {
  /*  Serial.println("\nLedLightCalculationSine::getValue");
  serialPrintLnDouble("  currentTimeSeconds: ", currentTimeSeconds);
  serialPrintLnDouble("  relativePhase: ", relativePhase);
*/

  /*
struct CalculationElementPhaseMapping {
  double startPhase = 0.0;
  double endPhase = 0.0;
};

  double phase = 0.0;
  double frequency = 1.0;
  double amplitude = 1.0;
  double offset = 0.0;
*/

  /* Tämä on siksi, että internalTimeSeconds -muuttujaa kasvatettaisiin vain kun aidosti ollaan siirrytty ajassa eteenpäin, eli seuraava ledSticks->loop() -kierros */
  if (this->loopSetColorsCounter != loopSetColorsCounter) {
    this->loopSetColorsCounter = loopSetColorsCounter;
    deltaTimeSeconds = currentTimeSeconds - previousTimeSeconds;
    previousTimeSeconds = currentTimeSeconds;
    internalTimeSeconds += deltaTimeSeconds * timeRatio;
  }

  double finalSourcePhase = 2.0 * 3.14159265359 * relativePhase + phase;
  double sine = sin((internalTimeSeconds * 2.0 * 3.14159265359 * frequency) + finalSourcePhase) * amplitude + offset;

  sine = pow(sine, 14.0) * 255.0;
  //sine = pow(relativePhase, 4.0) * 255.0;
  /*
  Serial.print("currentTimeSeconds: ");
  Serial.println(currentTimeSeconds, DEC);
  Serial.print("relativePhase: ");
  Serial.println(relativePhase, DEC);
  Serial.print("phase: ");
  Serial.println(phase, DEC);
  Serial.print("finalSourcePhase: ");
  Serial.println(finalSourcePhase, DEC);
  Serial.print("frequency: ");
  Serial.println(frequency, DEC);
  Serial.print("amplitude: ");
  Serial.println(amplitude, DEC);
  Serial.print("sine: ");
  Serial.println(sine, DEC);
  Serial.println("");
*/
  /*
  Serial.println("\nLedLightCalculationSine::getValue");
  serialPrintLnDouble("  p: ", this->phase);
  serialPrintLnDouble("  f: ", this->frequency);
  serialPrintLnDouble("  a: ", this->amplitude);
  serialPrintLnDouble("  o: ", this->offset);
  serialPrintLnDouble("  currentTimeSeconds: ", currentTimeSeconds);
  serialPrintLnDouble("  relativePhase: ", relativePhase);
  serialPrintLnDouble("  currentTimeSeconds: ", currentTimeSeconds);
  serialPrintLnDouble("  startPhase: ", calculationElementPhaseMapping.startPhase);
  serialPrintLnDouble("  endPhase: ", calculationElementPhaseMapping.endPhase);
  serialPrintLnDouble("  sine: ", sine);
*/
  ledLightCalculationValue.setValue(sine);
  /*
  serialPrintLnDouble("  sine: ", sine);
  Serial.println("LedLightCalculationSine:: ends");
*/
  return ledLightCalculationValue;
}