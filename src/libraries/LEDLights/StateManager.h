#ifndef STATEMANAGER_H
#define STATEMANAGER_H

#include <Arduino.h>

/*

enum class NoteState {
    NO_NOTE,
    INSERTING,
    DROPPED
};

char* getCurrentNoteStateString(NoteState state);

enum class DistanceState {
    FAR,
    NEAR,
    RETREATING
};

char* getCurrentDistanceStateString(DistanceState state);
*/

class StateManager {

public:
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

  char *getCurrentDistanceStateString() {
    if (distanceState == DistanceState::FAR) {
      return "DistanceState::FAR";
    }

    if (distanceState == DistanceState::NEAR) {
      return "DistanceState::NEAR";
    }

    if (distanceState == DistanceState::RETREATING) {
      return "DistanceState::RETREATING";
    }

    return "DistanceState::Unknown";
  }

  char *getCurrentNoteStateString() {
    if (noteState == NoteState::NO_NOTE) {
      return "NoteState::NO_NOTE";
    }

    if (noteState == NoteState::INSERTING) {
      return "NoteState::INSERTING";
    }

    if (noteState == NoteState::DROPPED) {
      return "NoteState::DROPPED";
    }

    return "NoteState::Unknown";
  }

  StateManager *setDistanceState(unsigned long currentTimeMillis, DistanceState state);
  StateManager *setNoteState(unsigned long currentTimeMillis, NoteState state);
  StateManager *updateSecondsAfterPreviousStateChanges(unsigned long currentTimeMillis);

  DistanceState getDistanceState(void);
  NoteState getNoteState(void);

  StateManager(void);

  unsigned long millisWhenToExitRetreatingState = 0;
  unsigned long millisWhenToExitDroppedState = 0;

  void debugPrint(void);

private:


  DistanceState distanceState = DistanceState::FAR;
  NoteState noteState = NoteState::NO_NOTE;




  DistanceState previousDistanceState = DistanceState::FAR;
  NoteState previousNoteState = NoteState::NO_NOTE;

  unsigned long previousDistanceStateChange = millis();
  unsigned long previousNoteStateChange = millis();

  double secondsAfterPreviousDistanceStateChange = 0.0;
  double secondsAfterPreviousNoteStateChange = 0.0;
};


#endif  // STATEMANAGER_H