//
// Alt.cpp
//

#include "Alt.h"

using namespace NMEA0183;

Alt::Alt() :
     Struct(),
     alt(),
     metres('F', 'M') {
} // Alt::Alt()

void Alt::Clear() {
    Struct::Clear();
    alt.Clear();
    metres.Clear();
} // Alt::Clear()

bool Alt::Decode(const char *&line) {
    Clear();
    if (!alt.Decode(line)) {
        return false;
    } // if
    if (!metres.Decode(line)) {
        return false;
    } // if
    valid = true;
    return true;
} // Alt::Decode(line)
