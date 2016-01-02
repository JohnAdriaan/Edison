/*
 * UTC.cpp
 *
 *   Author: John Burger
 *   This code is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *   GNU General Public License for more details.
 */

#include "UTC.h"

using namespace NMEA0183;

UTC::UTC() :
     Struct(),
     hour(),
     min(),
     sec() {
} // UTC::UTC()

bool UTC::Decode(const char *&line) {
    Clear();

    if (!Struct::Decode(line)) {
        return false;
    } // if

    switch (DecodeByte(line,2,hour,0,23)) {
    case Empty :
        return true; // Is truly Empty
    case Invalid :
        return false;
    case Valid :
        break;
    } // switch

    switch (DecodeByte(line,2,min,0,59)) {
    case Empty : // Is partially Empty
    case Invalid :
        return false;
    case Valid :
        break;
    } // switch

    switch (DecodeReal(line,2,sec,0.,60.)) {
    case Empty : // Is partially Empty
    case Invalid :
        return false;
    case Valid :
        break;
    } // switch

    valid = true;
    return true;
} // UTC::Decode(line)
