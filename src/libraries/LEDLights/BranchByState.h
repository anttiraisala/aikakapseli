#ifndef BRANCH_BY_STATE_H
#define BRANCH_BY_STATE_H

#include "LedLightCalculationElement.h"

class BranchByState : public LedLightCalculationElement {
public:

  // Override getValue to calculate and return a LedLightCalculationElement based on relativePhase and value_
  LedLightCalculationValue getValue(unsigned long loopSetColorsCounter, double currentTimeSeconds, double relativePhase) override;
  LedLightCalculationValue getValue();

  void debugPrint(void);

private:
  
};



#endif  // BRANCH_BY_STATE_H
