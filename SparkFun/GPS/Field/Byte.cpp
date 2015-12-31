//
// Byte.cpp
//

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
