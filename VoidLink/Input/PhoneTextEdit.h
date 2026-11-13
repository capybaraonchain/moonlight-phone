#ifndef PHONE_TEXT_EDIT_H
#define PHONE_TEXT_EDIT_H

#include <stddef.h>
#include <stdint.h>

// The iPhone keyboard edits a local copy of what was typed (autocorrect,
// predictions, slide typing and dictation all rewrite earlier characters).
// The desktop only needs the difference: how many characters to remove before
// its caret, then the UTF-16 offset from which the new text is typed.
typedef struct {
    size_t prefix;   // UTF-16 units shared by both texts
    size_t deletes;  // characters (code points) to remove on the desktop
} PhoneTextEdit;

static inline int PhoneTextIsTrailSurrogate(uint16_t unit) {
    return unit >= 0xDC00 && unit <= 0xDFFF;
}

static inline PhoneTextEdit PhoneTextDiff(const uint16_t *before, size_t beforeLength,
                                          const uint16_t *after, size_t afterLength) {
    size_t limit = beforeLength < afterLength ? beforeLength : afterLength;
    size_t prefix = 0;
    while (prefix < limit && before[prefix] == after[prefix]) prefix++;
    // Two different emoji can share their lead surrogate; never split a pair.
    if (prefix > 0 && ((prefix < beforeLength && PhoneTextIsTrailSurrogate(before[prefix])) ||
                       (prefix < afterLength && PhoneTextIsTrailSurrogate(after[prefix])))) prefix--;
    size_t deletes = 0;
    for (size_t i = prefix; i < beforeLength; i++) {
        if (!PhoneTextIsTrailSurrogate(before[i])) deletes++;
    }
    return (PhoneTextEdit){prefix, deletes};
}

// Edge swipes: a finger that starts in the narrow strip beside the screen edge
// is kept off the desktop until it proves to be a swipe, a tap or neither.
typedef enum { PhoneEdgeNone = 0, PhoneEdgeLeft = 1, PhoneEdgeRight = 2 } PhoneEdge;

static inline PhoneEdge PhoneEdgeAt(double x, double width, double strip) {
    if (x <= strip) return PhoneEdgeLeft;
    if (x >= width - strip) return PhoneEdgeRight;
    return PhoneEdgeNone;
}

// Distance travelled away from the edge; negative when moving outward.
static inline double PhoneEdgeTravel(PhoneEdge edge, double dx) {
    return edge == PhoneEdgeLeft ? dx : edge == PhoneEdgeRight ? -dx : 0;
}

static inline int PhoneEdgeSwiped(PhoneEdge edge, double dx, double dy, double distance) {
    double travel = PhoneEdgeTravel(edge, dx);
    double drift = dy < 0 ? -dy : dy;
    return travel >= distance && drift <= travel * 0.75;
}

static inline int PhoneEdgeTapped(double dx, double dy, double seconds) {
    return dx * dx + dy * dy <= 10 * 10 && seconds < 0.6;
}

#endif
