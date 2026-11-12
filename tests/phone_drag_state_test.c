#include <assert.h>
#include "../VoidLink/Input/PhoneDragState.h"
int main(void) {
    PhoneDragState s = {0};
    assert(PhoneDragBegin(&s) == PhoneDragNone);
    assert(PhoneDragSetEnabled(&s, true) == PhoneDragNone);
    assert(s.enabled && !s.holding);
    assert(PhoneDragBegin(&s) == (PhoneDragMove | PhoneDragPress));
    // Finger lifts do not change lock ownership. Re-touch only moves, never presses twice.
    for (int i = 0; i < 10; ++i) assert(PhoneDragBegin(&s) == PhoneDragMove);
    assert(PhoneDragSetEnabled(&s, false) == PhoneDragRelease);
    assert(!s.enabled && !s.holding);
    assert(PhoneDragSetEnabled(&s, false) == PhoneDragNone);
    // Cancel while armed must not generate a click or a spurious held button.
    assert(PhoneDragSetEnabled(&s, true) == PhoneDragNone);
    assert(PhoneDragSetEnabled(&s, false) == PhoneDragNone);
    assert(PhoneDragSetEnabled(&s, true) == PhoneDragNone);
    assert(PhoneDragBegin(&s) & PhoneDragPress);
    // Disconnect / interruption follows the exact same release path as Drop.
    assert(PhoneDragSetEnabled(&s, false) == PhoneDragRelease);
    return 0;
}
