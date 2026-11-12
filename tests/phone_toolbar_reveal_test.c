#include <assert.h>
#include "../VoidLink/Input/PhoneToolbarReveal.h"

int main(void) {
    PhoneToolbarReveal state = {0};
    assert(!PhoneToolbarSwipe(&state, 0, -100, .3, 1)); // no interception while controls are visible
    PhoneToolbarHide(&state);
    assert(!PhoneToolbarConfirm(&state, 1)); // a bottom tap alone never opens controls
    assert(!PhoneToolbarSwipe(&state, 0, -20, .2, 1)); // accidental short scroll
    assert(!PhoneToolbarSwipe(&state, 70, -75, .3, 1)); // diagonal movement
    assert(!PhoneToolbarSwipe(&state, 0, 90, .3, 1)); // wrong direction
    assert(!PhoneToolbarSwipe(&state, 0, -90, 2, 1)); // long drag
    assert(!PhoneToolbarSwipe(&state, NAN, -90, .3, 1));
    assert(state.phase == PhoneToolbarHidden);
    assert(PhoneToolbarSwipe(&state, 5, -90, .3, 2));
    assert(state.phase == PhoneToolbarPrompt); // even a deliberate swipe never fully opens
    assert(!PhoneToolbarSwipe(&state, 0, -100, .3, 3)); // repeated swipes do not confirm or extend timeout
    assert(state.deadline == 6);
    assert(PhoneToolbarConfirm(&state, 3));
    assert(state.phase == PhoneToolbarVisible);
    PhoneToolbarHide(&state);
    assert(PhoneToolbarSwipe(&state, 0, -80, .4, 4));
    assert(!PhoneToolbarConfirm(&state, 8)); // expired confirmation is rejected
    assert(state.phase == PhoneToolbarHidden);
    assert(PhoneToolbarRequestPrompt(&state, 10));
    PhoneToolbarCancelPrompt(&state); // rotation, interruption or cancellation
    assert(!PhoneToolbarConfirm(&state, 11));
    assert(state.phase == PhoneToolbarHidden);
    assert(PhoneToolbarSwipe(&state, 0, -80, .4, 12)); // next gesture still works
    assert(PhoneToolbarConfirm(&state, 13));
    PhoneToolbarCancelPrompt(&state);
    assert(state.phase == PhoneToolbarVisible); // interruptions do not hide a visible toolbar
    return 0;
}
