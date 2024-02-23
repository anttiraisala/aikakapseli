// Debug.h

#ifndef DEBUG_H
#define DEBUG_H


// Uncomment some of the next lines to enable debugging
/////////////////////////////////////////
#define DEBUG_MODE
#define DEBUG_DISTANCE_STATE
//#define DEBUG_NOTE_STATE
/////////////////////////////////////////


// By default they are defined as empty but if specified otherwise they are defined to output stuff
#define DEBUG_PRINTLN(x)
#define DEBUG_DISTANCE_STATE_PRINTLN(x)
#define DEBUG_NOTE_STATE_PRINTLN(x)


#ifdef DEBUG_MODE

  #define DEBUG_PRINTLN(x) Serial.println(x)

  #ifdef DEBUG_DISTANCE_STATE
    #define DEBUG_DISTANCE_STATE_PRINTLN(x) Serial.println(x)
  #endif

  #ifdef DEBUG_NOTE_STATE
    #define DEBUG_NOTE_STATE_PRINTLN(x) Serial.println(x)
  #endif

#endif // DEBUG_MODE

#endif // DEBUG_H
