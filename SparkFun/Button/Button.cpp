/*
 * Button.cpp
 *
 *   Author: John Burger
 *   This code is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *   GNU General Public License for more details.
 */

#include <time.h>
#include "Button.h"

Button *Button::head = NULL;

unsigned Button::initial = 500; // Default 'initial' time

unsigned Button::repeat = 200;  // Default 'repeat' time

// CLOCK_MONOTONIC is a better timer that CLOCK_REALTIME (no nasty jumps back in time!),
// but it's not always implemented (unlike CLOCK_REALTIME).
clockid_t clockID = CLOCK_MONOTONIC;

void Button::Configure(unsigned initial, unsigned repeat) {
    Button::initial = initial;
    Button::repeat = repeat;

    // Check if CLOCK_MONOTONIC is implemented.
    // Note I don't actually care about the clock's resolution...
    if (::clock_getres(clockID, NULL)!=0) { // Error?
        clockID = CLOCK_REALTIME;     // Always implemented
    } // if
} // Button::Configure(initial, repeat)

Button *Button::Poll() {
    static Button *old = NULL;  // Last button Pressed()

    Button *ptr = head;         // Start at head of list
    while (ptr != NULL) {
        if (ptr->IsPressed()) { // Is this one Pressed()?
            break;              // Yes! Found!
        } // if
        ptr = ptr->next;        // No. Keep looking
    } // while
    // At this point, ptr is either a button or NULL

    uint64_t ms;
    if (ptr!=NULL) { // Button is pressed, so need the current time
        timespec time;
        if (::clock_gettime(clockID, &time)==0) {
            ms = time.tv_sec * 1000uLL +
                 time.tv_nsec / 1000000uLL;
        } // if
        else { // This doesn't make sense! Do something 'sensible'
            ptr->pressed += 50;
            ms = ptr->pressed * 2;
        } // else
    } // if
    if (old!=ptr) {             // If different from before (including NULL...)
        if (old!=NULL) {        // If there was an old button,
            old->pressed = 0;   // clear it
            old->held = 0;
        } // if
        old = ptr;              // Remember for next time
        if (ptr!=NULL) {
            ptr->pressed = ms;  // Store as start time
            ptr->held = 0;
        } // if
        return ptr;             // And return as "new" button (could be NULL)
    } // if
    if (ptr==NULL) {            // If (still) no Button IsPressed()
        return NULL;            // Return it.
    } // if
    // At this point, ptr points to an already-pressed Button

    uint64_t diff = ms - ptr->pressed;
    if (ptr->held == 0) {       // If this is the first press
        if (diff < initial) {   // Too early to start repeating?
            return NULL;        // Yep, so pretend not still down.
        } // if
        ptr->held = 1;           // Waited long enough
        ptr->pressed += initial; // Already factored in
        return ptr;              // So it's down again
    } // if

    // Already waited 'initial'
    if (diff < ptr->held * repeat) { // Repeating. Time for a new 'press'?
        return NULL;                 // Not yet
    } // if
    ++ptr->held;                 // Wait for next repeat
    return ptr;                  // And it's down again
} // Button::Poll()

void Button::Wait(unsigned ms) {
    const timespec wait = { 0, (int)ms * 1000 * 1000 }; // <ms>,000,000 ns == <ms>,000 us == <ms> ms
    ::nanosleep(&wait,NULL);
} // Button::Wait(ms)

int Button::Get(unsigned ms) {
    Button *button;
    for (;;) {
        button = Button::Poll();
        if (button!=NULL) {
            break;
        } // if
        Wait(ms);
    } // for
    return button->Pressed();
} // Button::Get()

Button::Button(Pins pin) :
        gpio(pin, INPUT),
        next(head),
        pressed(0),
        held(0) {
    head = this;
} // Button::Button(Pins)

bool Button::IsPressed() {
    return pinRead()==LOW;
} // Button::IsPressed()
