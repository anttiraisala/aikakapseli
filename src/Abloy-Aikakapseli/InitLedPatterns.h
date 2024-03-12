#ifndef INIT_LED_PATTERNS_H
#define INIT_LED_PATTERNS_H

#include <Arduino.h>
#include "LedLightCalculationElement.h"
#include "LedLightCalculationTwoOperands.h"
#include "StateManager.h"
#include "CalculationElementLink.h"
#include "LedLightCalculationValue.h"
#include "HelperFunctions.h"
#include "LedLightCalculationConstant.h"
#include "LedLightCalculationSine.h"
#include "BranchByState.h"
#include "LedLights.h"
#include "StateChangePulse.h"
#include "CrossDissolve.h"
#include "CalculationSimplexNoise.h"
#include "SweepingDot.h"
#include "Threshold.h"

void initPatterns(void);


#endif // INIT_LED_PATTERNS_H