//
// Real.cpp
//

#include "Real.h"

using namespace NMEA0183;

Real::Real(real min, real max) :
      Field(),
      min(min),
      max(max),
      value() {
} // Real::Real(width, min, max)

bool Real::Decode(const char *&line) {
    Clear();

    if (!Field::Decode(line)) {
        return false;
    } // if
    switch (DecodeReal(line, 0, value, min, max)) {
    case Empty :
        break;
    case Invalid :
        return false;
    case Valid :
        valid = true;
        break;
    } // switch
    return true;
} // Real::Decode(line)
