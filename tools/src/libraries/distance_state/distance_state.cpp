#include "distance_state.h"
#include <Arduino.h>

long millisWhenToExitRetreatingState = 0;

char* getCurrentDistanceStateString(DistanceState state) {
  if(state == DistanceState::FAR){
    return "DistanceState::FAR";
  }

  if(state == DistanceState::NEAR){
    return "DistanceState::NEAR";
  }

  if(state == DistanceState::RETREATING){
    return "DistanceState::RETREATING";
  }
  
  return "DistanceState::Unknown";
}