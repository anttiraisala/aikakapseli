#include "LedLightCalculationSine.h"
#include "HelperFunctions.h"

LedLightCalculationSine::LedLightCalculationSine() {}

LedLightCalculationSine::LedLightCalculationSine(double phase, double frequency, double amplitude, double offset) {
  this->setParameters(phase, frequency, amplitude, offset);
}

void LedLightCalculationSine::setParameters(double phase, double frequency, double amplitude, double offset) {
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

LedLightCalculationValue LedLightCalculationSine::getValue(double currentTimeSeconds, double relativePhase, CalculationElementPhaseMapping calculationElementPhaseMapping) {


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

  double finalSourcePhase = 0.0;
  if (calculationElementPhaseMapping.endPhase != calculationElementPhaseMapping.startPhase) {
    finalSourcePhase = (calculationElementPhaseMapping.endPhase - calculationElementPhaseMapping.startPhase) * relativePhase + calculationElementPhaseMapping.startPhase;
  }
  finalSourcePhase += phase;

  double sine = sin((currentTimeSeconds * 2.0 * 3.14159265359 * frequency * -1.0) + finalSourcePhase) * amplitude + offset;

  sine = pow(sine, 6.0) * 255.0;
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

  return ledLightCalculationValue;
}