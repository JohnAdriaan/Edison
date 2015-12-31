//
// Field.cpp
//

#include "Field.h"

using namespace NMEA0183;

Field::Field() :
       valid(false) {
} // Field::Field()

void Field::Clear() {
    valid = false;
} // Field::Clear()

bool Field::Decode(const char *&line) {
    return *line++ == ',';
} // Field::Decode(line)

Field::Decodes Field::DecodeByte(const char *&line, byte width, byte &value, byte min, byte max) {
    value = 0;
    switch (*line) {
    case ',' :
    case '*' :
        return Empty;
    } // switch
    while (width-->0) {
        char c = *line++;
        switch (c) {
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            value = value * 10 + (c - '0');
            continue;
        case ',':
        case '*':
            --line;
            if (width>0) {
                return Invalid;
            } // if
            break;
        default:
            return Invalid;
        } // switch
        break;
    } // while
    if (min == max) {
        return Valid;
    } // if
    return (min <= value) && (value <= max) ?
           Valid :
           Invalid;
} // Field::DecodeByte(line, width, value, min, max)

Field::Decodes Field::DecodeWord(const char *&line, byte width, word &value, word min, word max) {
    value = 0;
    switch (*line) {
    case ',':
    case '*':
        return Empty;
    } // switch
    while (width-->0) {
        char c = *line++;
        switch (c) {
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            value = value * 10 + (c - '0');
            continue;
        case ',':
        case '*':
            --line;
            if (width>0) {
                return Invalid;
            } // if
            break;
        default:
            return Invalid;
        } // switch
        break;
    } // while
    if (min == max) {
        return Valid;
    } // if
    return (min <= value) && (value <= max) ?
           Valid :
           Invalid;
} // Field::DecodeWord(line, width, value, min, max)

Field::Decodes Field::DecodeReal(const char *&line, byte width, real &value, real min, real max) {
    bool minus = false;
    switch (*line) {
    case ',':
    case '*':
        return Empty;
    case '-' :
        minus = true;
        break;
    } // switch

    real factor = 0.;

    if (minus) {
        ++line;
    } // if
    value = 0.;

    for (;;) {
        char c = *line++;
        switch (c) {
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            factor *= 10.; // If we're in the decimal part
            value = value * 10. + (c - '0');
            if (width>0) {
                if (--width == 0) {
                    if (*line != '.') {
                        return Invalid;
                    } // if
                } // if
            } // if
            continue;
        case '.':
            if (width>0) {
                return Invalid;
            } // if
            if (factor>0.) {
                return Invalid;
            } // if
            factor = 1.;
            continue;
        case ',':
        case '*':
            --line;
            if (width>0) {
                return Invalid;
            } // if
            break;
        } // if
        break;
    } // for
    if (minus) {
        value = -value;
    } // if
    if (factor>0.) {
        value /= factor;
    } // if
    if (min == max) {
        return Valid;
    } // if
    return (min <= value) && (value <= max) ?
           Valid :
           Invalid;
} // Field::DecodeReal(line, width, value, min, max)
