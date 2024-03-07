#ifndef CROSS_DISSOLVE_H
#define CROSS_DISSOLVE_H

#include "LedLightCalculationElement.h"
#include "CalculationElementLink.h"
#include "HelperFunctions.h"
#include "LedLightCalculationTwoOperands.h"
#include "LedLightCalculationConstant.h"


class CrossDissolve : public LedLightCalculationElement {
public:

  CrossDissolve(void);

  CrossDissolve *setControlElement(CalculationElementLink *controlElementLink);
  CrossDissolve *setInput0Element(CalculationElementLink *input0ElementLink);
  CrossDissolve *setInput1Element(CalculationElementLink *input1ElementLink);

  LedLightCalculationValue getValue(unsigned long loopSetColorsCounter, double currentTimeSeconds, double relativePhase);

  void debugPrint(void);

private:
  CalculationElementLink *controlElementLink;
  CalculationElementLink *input0ElementLink;
  CalculationElementLink *input1ElementLink;

  LedLightCalculationTwoOperands *calculationTwoOperands;
  LedLightCalculationConstant *llc_one;
};



#endif  // CROSS_DISSOLVE_H
