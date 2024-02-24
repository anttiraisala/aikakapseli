#include "note_state.h"
#include <Arduino.h>

long millisWhenToExitDroppedState = 0;

char* getCurrentNoteStateString(NoteState state) {
  if(state == NoteState::NO_NOTE){
    return "NoteState::NO_NOTE";
  }

  if(state == NoteState::INSERTING){
    return "NoteState::INSERTING";
  }

  if(state == NoteState::DROPPED){
    return "NoteState::DROPPED";
  }
  
  return "NoteState::Unknown";
}