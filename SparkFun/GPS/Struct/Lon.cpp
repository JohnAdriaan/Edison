/*
 * Lon.cpp
 *
 *   Author: John Burger
 *   This code is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *   GNU General Public License for more details.
 */

#include "Lon.h"

using namespace NMEA0183;

Lon::Lon() :
     Struct(),
     degrees(3, 0, 180),
     minutes(),
     east('W', 'E') {
} // Lon::Lon()

void Lon::Clear() {
    Struct::Clear();
    degrees.Clear();
    minutes = 0.;
    east.Clear();
} // Lon::Clear()

bool Lon::Decode(const char *&line) {
    Clear();

    if (!degrees.Decode(line)) {
        return false;
    } // if
    switch (DecodeReal(line, 2, minutes, 0., 60.)) {
    case Empty :
        if (degrees.IsValid()) { // If degrees are valid, then the rest is missing!
            return false;
        } // if
        break;
    case Invalid :
        return false;
    case Valid :
        break;
    } // switch
    if (!east.Decode(line)) {
        return false;
    } // if
    valid = degrees.IsValid() &&
            east.IsValid();
    return true;
} // Lon::Decode(line)
