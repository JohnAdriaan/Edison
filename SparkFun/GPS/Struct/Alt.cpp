/*
 * Alt.cpp
 *
 *   Author: John Burger
 *   This code is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *   GNU General Public License for more details.
 */

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
