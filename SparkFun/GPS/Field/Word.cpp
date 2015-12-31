//
// Word.cpp
//

#include "Word.h"

using namespace NMEA0183;

Word::Word(byte width, word min, word max) :
      Field(),
      width(width),
      min(min),
      max(max),
      value() {
} // Word::Word(width, min, max)

bool Word::Decode(const char *&line) {
    Clear();

    if (!Field::Decode(line)) {
        return false;
    } // if
    switch (DecodeWord(line, width, value, min, max)) {
    case Empty :
        break;
    case Invalid :
        return false;
    case Valid :
        valid = true;
        break;
    } // switch
    return true;
} // Word::Decode(line)
