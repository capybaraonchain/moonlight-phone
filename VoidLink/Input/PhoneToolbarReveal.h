// Two separate gestures are required: an edge swipe, then a confirmation tap.
#pragma once
#include <stdbool.h>
#include <math.h>

typedef enum { PhoneToolbarVisible, PhoneToolbarHidden, PhoneToolbarPrompt } PhoneToolbarPhase;
typedef struct { PhoneToolbarPhase phase; double deadline; } PhoneToolbarReveal;

static inline void PhoneToolbarHide(PhoneToolbarReveal *state) {
    state->phase = PhoneToolbarHidden;
    state->deadline = 0;
}
static inline bool PhoneToolbarRequestPrompt(PhoneToolbarReveal *state, double now) {
    if (state->phase != PhoneToolbarHidden) return false;
    state->phase = PhoneToolbarPrompt;
    state->deadline = now + 4.0;
    return true;
}
static inline bool PhoneToolbarSwipe(PhoneToolbarReveal *state, double dx, double dy, double elapsed, double now) {
    if (!isfinite(dx) || !isfinite(dy) || !isfinite(elapsed) || elapsed < 0 || elapsed > 1.2 ||
        dy > -64 || fabs(dx) > 48 || -dy < fabs(dx) * 1.8) return false;
    return PhoneToolbarRequestPrompt(state, now);
}
static inline bool PhoneToolbarConfirm(PhoneToolbarReveal *state, double now) {
    if (state->phase != PhoneToolbarPrompt) return false;
    if (now >= state->deadline) { PhoneToolbarHide(state); return false; }
    state->phase = PhoneToolbarVisible;
    state->deadline = 0;
    return true;
}
static inline void PhoneToolbarCancelPrompt(PhoneToolbarReveal *state) {
    if (state->phase == PhoneToolbarPrompt) PhoneToolbarHide(state);
}
