#ifndef DISTANCE_STATE_H
#define DISTANCE_STATE_H

enum class DistanceState {
    FAR,
    NEAR,
    RETREATING
};

char* getCurrentStateString(DistanceState state);

#endif // DISTANCE_STATE_H
