// Shared drag-lock state, independent of UIKit so event sequences can be tested.
#pragma once
#include <stdbool.h>
typedef struct { bool enabled; bool holding; } PhoneDragState;
enum { PhoneDragNone = 0, PhoneDragMove = 1, PhoneDragPress = 2, PhoneDragRelease = 4 };
static inline unsigned PhoneDragSetEnabled(PhoneDragState *state, bool enabled) {
    if (state->enabled == enabled) return PhoneDragNone;
    unsigned action = state->holding ? PhoneDragRelease : PhoneDragNone;
    state->enabled = enabled;
    state->holding = false;
    return action;
}
static inline unsigned PhoneDragBegin(PhoneDragState *state) {
    if (!state->enabled) return PhoneDragNone;
    unsigned action = PhoneDragMove | (state->holding ? PhoneDragNone : PhoneDragPress);
    state->holding = true;
    return action;
}
