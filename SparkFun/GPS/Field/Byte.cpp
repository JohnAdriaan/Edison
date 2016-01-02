/*
 * Byte.cpp
 *
 *   Author: John Burger
 *   This code is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *   GNU General Public License for more details.
 */

#include "Byte.h"

using namespace NMEA0183;

Byte::Byte(byte width, byte min, byte max) :
      Field(),
      width(width),
      min(min),
      max(max),
      value() {
} // Byte::Byte(width, min, max)

bool Byte::Decode(const char *&line) {
    Clear();

    if (!Field::Decode(line)) {
        return false;
    } // if
    switch (DecodeByte(line, width, value, min, max)) {
    case Empty :
        break;
    case Invalid :
        return false;
    case Valid :
        valid = true;
        break;
    } // switch
    return true;
} // Byte::Decode(line)
