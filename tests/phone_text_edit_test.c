#include <assert.h>
#include <stdio.h>
#include "../VoidLink/Input/PhoneTextEdit.h"

static PhoneTextEdit diff(const uint16_t *a, size_t an, const uint16_t *b, size_t bn) {
    return PhoneTextDiff(a, an, b, bn);
}

#define U(...) (const uint16_t[]){__VA_ARGS__}
#define N(...) (sizeof((const uint16_t[]){__VA_ARGS__}) / sizeof(uint16_t))
#define DIFF(A, B) diff(U A, N A, U B, N B)

int main(void) {
    PhoneTextEdit e;
    // Typing one more character.
    e = DIFF(('h', 'e'), ('h', 'e', 'l'));
    assert(e.prefix == 2 && e.deletes == 0);
    // Backspace.
    e = DIFF(('h', 'e', 'l'), ('h', 'e'));
    assert(e.prefix == 2 && e.deletes == 1);
    // Autocorrect "teh" -> "the ".
    e = DIFF(('t', 'e', 'h'), ('t', 'h', 'e', ' '));
    assert(e.prefix == 1 && e.deletes == 2);
    // Nothing typed yet, a whole predicted word arrives.
    e = diff(NULL, 0, U('h', 'i'), 2);
    assert(e.prefix == 0 && e.deletes == 0);
    // Everything removed.
    e = diff(U('h', 'i'), 2, NULL, 0);
    assert(e.prefix == 0 && e.deletes == 2);
    // Unchanged.
    e = DIFF(('o', 'k'), ('o', 'k'));
    assert(e.prefix == 2 && e.deletes == 0);
    // An emoji is two UTF-16 units but one character on the desktop.
    e = DIFF(('a', 0xD83D, 0xDE00), ('a'));
    assert(e.prefix == 1 && e.deletes == 1);
    // Two emoji sharing a lead surrogate: the pair is replaced whole.
    e = DIFF(('a', 0xD83D, 0xDE00), ('a', 0xD83D, 0xDE01));
    assert(e.prefix == 1 && e.deletes == 1);
    // An edit in the middle retypes the tail.
    e = DIFF(('c', 'a', 't', 's'), ('c', 'u', 't', 's'));
    assert(e.prefix == 1 && e.deletes == 3);

    assert(PhoneEdgeAt(3, 393, 12) == PhoneEdgeLeft);
    assert(PhoneEdgeAt(390, 393, 12) == PhoneEdgeRight);
    assert(PhoneEdgeAt(200, 393, 12) == PhoneEdgeNone);
    assert(PhoneEdgeSwiped(PhoneEdgeLeft, 80, 10, 64));
    assert(PhoneEdgeSwiped(PhoneEdgeRight, -80, -20, 64));
    assert(!PhoneEdgeSwiped(PhoneEdgeLeft, 40, 0, 64));    // too short
    assert(!PhoneEdgeSwiped(PhoneEdgeLeft, 80, 90, 64));   // mostly vertical: a scroll
    assert(!PhoneEdgeSwiped(PhoneEdgeRight, 80, 0, 64));   // moving outward
    assert(!PhoneEdgeSwiped(PhoneEdgeNone, 200, 0, 64));
    assert(PhoneEdgeTapped(2, -3, 0.1));
    assert(!PhoneEdgeTapped(30, 0, 0.1));
    assert(!PhoneEdgeTapped(0, 0, 1.0));
    puts("phone text edit and edge swipe checks passed");
    return 0;
}
