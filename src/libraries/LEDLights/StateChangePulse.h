#ifndef STATE_CHANGE_PULSE_H
#define STATE_CHANGE_PULSE_H

#include "LedLightCalculationElement.h"
#include "CalculationElementLink.h"
#include "HelperFunctions.h"

#include "StateManager.h"

#define ACTIVE_STATE_LIST_SIZE 3

class StateChangePulse : public LedLightCalculationElement {
public:
  StateChangePulse(void);
  LedLightCalculationValue getValue(unsigned long loopSetColorsCounter, double currentTimeSeconds, double relativePhase);

  StateChangePulse *setState(byte state);
  StateChangePulse *setPreDelay(double preDelay);
  StateChangePulse *setPulseCount(unsigned int pulseCount);
  StateChangePulse *setPulseHighTimeSeconds(double pulseHighTimeSeconds);
  StateChangePulse *setPulseLowTimeSeconds(double pulseLowTimeSeconds);
  StateChangePulse *setPostOutput(double postOutput);

  void debugPrint(void);

private:
  double preDelay = 0.1;
  unsigned int pulseCount = 3;
  double pulseHighTimeSeconds = 0.35;
  double pulseLowTimeSeconds = 0.2;
  double postOutput = 0.0;

  byte activeStates[ACTIVE_STATE_LIST_SIZE];
  double (*functionPtrArray[ACTIVE_STATE_LIST_SIZE])(void);
  byte arrayPtr = 0;
  byte elementCount = 0;
};

#endif  // STATE_CHANGE_PULSE_H
