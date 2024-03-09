#include "StateChangePulse.h"
#include "HelperFunctions.h"

extern StateManager stateManager;

StateChangePulse::StateChangePulse(void) {}

StateChangePulse *StateChangePulse::setState(byte state) {
  if (arrayPtr < ACTIVE_STATE_LIST_SIZE) {
    activeStates[arrayPtr] = state;
    arrayPtr++;
    elementCount++;
  }

  return this;
}

StateChangePulse *StateChangePulse::setPreDelay(double preDelay) {
  this->preDelay = preDelay;
  return this;
}

StateChangePulse *StateChangePulse::setPulseHighTimeSeconds(double pulseHighTimeSeconds) {
  this->pulseHighTimeSeconds = pulseHighTimeSeconds;
  return this;
}

StateChangePulse *StateChangePulse::setPulseLowTimeSeconds(double pulseLowTimeSeconds) {
  this->pulseLowTimeSeconds = pulseLowTimeSeconds;
  return this;
}

StateChangePulse *StateChangePulse::setPulseCount(unsigned int pulseCount) {
  this->pulseCount = pulseCount;
  return this;
}

StateChangePulse *StateChangePulse::setPostOutput(double postOutput) {
  this->postOutput = postOutput;
  return this;
}

LedLightCalculationValue StateChangePulse::getValue(unsigned long loopSetColorsCounter, double currentTimeSeconds, double relativePhase) {
  //serialPrintLnDouble("currentTimeSeconds:[", currentTimeSeconds, "]");
  double secondsAfterStateChange = 0.0;
  bool found = false;
  for (byte i = 0; i < elementCount; i++) {
    byte stateProspect = activeStates[i];
    if (stateProspect == (byte)stateManager.getDistanceState()) {
  /*    Serial.print(F("stateProspect:["));
      Serial.print(stateProspect, DEC);
      Serial.println(F("]"));*/
      secondsAfterStateChange = stateManager.getSecondsAfterPreviousDistanceStateChange();
      found = true;
      break;
    }
    if (stateProspect == (byte)stateManager.getNoteState()) {
 /*     Serial.print(F("stateProspect:["));
      Serial.print(stateProspect, DEC);
      Serial.println(F("]"));*/
      secondsAfterStateChange = stateManager.getSecondsAfterPreviousNoteStateChange();
      found = true;
      break;
    }
  }

  ledLightCalculationValue.setValue(0.0);

  if (found == false) {
    return ledLightCalculationValue;
  }
/*
  Serial.println("found=true");
  serialPrintLnDouble("preDelay:[", preDelay, "]");

*/
  if (secondsAfterStateChange <= preDelay) {
    //serialPrintLnDouble("secondsAfterStateChange <= preDelay secondsAfterStateChange:[", secondsAfterStateChange, "]");
    return ledLightCalculationValue;
  }

  ledLightCalculationValue.setValue(secondsAfterStateChange);

  double secondsSincePulseStart = secondsAfterStateChange - preDelay;
  //serialPrintLnDouble("secondsSincePulseStart:[", secondsSincePulseStart, "]");

  /* Missä pulssissa ollaan menossa */
  /*
    double preDelay = 0.1;
  unsigned int pulseCount = 3;
  double pulseHighTimeSeconds = 0.35;
  double pulseLowTimeSeconds = 0.2;
  double postOutput = 0.0;
  */

  double a = secondsSincePulseStart / (pulseHighTimeSeconds + pulseLowTimeSeconds);
 /* serialPrintLnDouble("a:[", a, "]");
  serialPrintLnDouble("(double)((int)(a)):[", (double)((int)(a)), "]");
*/
  if (floor(a) >= (double)pulseCount) {
    ledLightCalculationValue.setValue(postOutput);
    return ledLightCalculationValue;
  }

  double decimalPart = a - (double)((int)(a));
  //serialPrintLnDouble("decimalPart:[", decimalPart, "]");
  double b = pulseHighTimeSeconds / (pulseHighTimeSeconds + pulseLowTimeSeconds);
  //serialPrintLnDouble("b:[", b, "]");

  if (decimalPart <= b) {
    ledLightCalculationValue.setValue(1.0);
  } else {
    ledLightCalculationValue.setValue(0.0);
  }

  return ledLightCalculationValue;
}

/*
  double getSecondsAfterPreviousDistanceStateChange(void);
  double getSecondsAfterPreviousNoteStateChange(void);

    enum class NoteState {
    NO_NOTE = 1,
    INSERTING = 2,
    DROPPED = 3
  };

  enum class DistanceState {
    FAR = 4,
    NEAR = 5,
    RETREATING = 6
  };

#define ACTIVE_STATE_LIST_SIZE 3
  byte activeStates[ACTIVE_STATE_LIST_SIZE];
  double (*functionPtrArray[ACTIVE_STATE_LIST_SIZE])(void);
  byte arrayPtr = 0;
  byte elementCount = 0;
  */