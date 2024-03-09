#include "StateManager.h"

/*

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

  
  unsigned long millisWhenToExitRetreatingState = 0;
  unsigned long millisWhenToExitDroppedState = 0;

  DistanceState distanceState = DistanceState::FAR;
  NoteState noteState = NoteState::NO_NOTE;
  DistanceState previousDistanceState = DistanceState::FAR;
  NoteState previousNoteState = NoteState::NO_NOTE;

  unsigned long previousDistanceStateChange = millis();
  unsigned long previousNoteStateChange = millis();

  double secondsAfterPreviousDistanceStateChange = 0.0;
  double secondsAfterPreviousNoteStateChange = 0.0;
*/

StateManager::StateManager(void) {
  DistanceState distanceState = DistanceState::FAR;
  NoteState noteState = NoteState::NO_NOTE;
  DistanceState previousDistanceState = DistanceState::FAR;
  NoteState previousNoteState = NoteState::NO_NOTE;

  millisWhenToExitRetreatingState = 0;
  millisWhenToExitDroppedState = 0;

  previousDistanceStateChange = millis();
  previousNoteStateChange = millis();
}

double StateManager::getSecondsAfterPreviousDistanceStateChange(void){
  return secondsAfterPreviousDistanceStateChange;
}

double StateManager::getSecondsAfterPreviousNoteStateChange(void){
  return secondsAfterPreviousNoteStateChange;
}


void StateManager::debugPrint(void){
  Serial.println(F("StateManager::debugPrint - begins"));

  Serial.println(getCurrentDistanceStateString());
  Serial.println(getCurrentNoteStateString());

  Serial.println(F("StateManager::debugPrint - ends"));
}

StateManager *StateManager::setDistanceState(unsigned long currentTimeMillis, DistanceState state) {
  if (distanceState == state) {
    return this;
  }

  previousDistanceState = distanceState;
  distanceState = state;
  previousDistanceStateChange = currentTimeMillis;

  updateSecondsAfterPreviousStateChanges(currentTimeMillis);

  return this;
}

StateManager *StateManager::setNoteState(unsigned long currentTimeMillis, NoteState state) {
  if (noteState == state) {
    return this;
  }

  previousNoteState = noteState;
  noteState = state;
  previousNoteStateChange = currentTimeMillis;

  updateSecondsAfterPreviousStateChanges(currentTimeMillis);

  return this;
}
StateManager *StateManager::updateSecondsAfterPreviousStateChanges(unsigned long currentTimeMillis) {

  secondsAfterPreviousDistanceStateChange = (currentTimeMillis - previousDistanceStateChange) / 1000.0;
  secondsAfterPreviousNoteStateChange = (currentTimeMillis - previousNoteStateChange) / 1000.0;

  serialPrintLnDouble("StateManager::secondsAfterPreviousDistanceStateChange:[", secondsAfterPreviousDistanceStateChange, "]");
  serialPrintLnDouble("StateManager::secondsAfterPreviousNoteStateChange:[", secondsAfterPreviousNoteStateChange, "]");

  return this;
}

StateManager::DistanceState StateManager::getDistanceState(void) {
  return distanceState;
}

StateManager::NoteState StateManager::getNoteState(void) {
  return noteState;
}
