#ifndef NOTE_STATE_H
#define NOTE_STATE_H

enum class NoteState {
    NO_NOTE,
    INSERTING,
    DROPPED
};

char* getCurrentNoteStateString(NoteState state);

#endif // NOTE_STATE_H

