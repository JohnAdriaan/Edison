//
// Message.cpp
//

#include "Message.h"

using namespace NMEA0183;

Message::Message() :
         Struct() {
} // Message::Message()

static bool IsHex(char hex) {
    return ((('0'<=hex) && (hex<='9')) ||
            (('A'<=hex) && (hex<='F')) ||
            (('a'<=hex) && (hex<='f')));
} // IsHex(hex)

bool Message::Valid(const char *&line) {
    while (*line != '$') {
        if (*line++ < ' ') { // CR, LF or NUL
            return false;
        } // if
    } // while

    if (*(line+1) != 'G') {
        return false;
    } // if

    switch (*(line+2)) {
    case 'P' : // GPS
        break;
    case 'L' : // GLONASS
        break;
    default :
        return false;
    } // switch

    const char *end = line+3;
    while (*end != '*') {
        if (*end++ < ' ') { // CR, LF or NUL
            return false;
        } // if
    } // while

    if (!IsHex(*(end+1))) {
        return false;
    } // if
    if (!IsHex(*(end+2))) {
        return false;
    } // if

    return true;
} // Message::Valid(line)

static byte Hex(char hex) {
    if (hex<'0') {
        return 0;
    } // if
    if (hex<='9') {
        return hex - '0';
    } // if
    if (hex<'A') {
        return 0;
    } // if
    if (hex<='F') {
        return 10 + hex - 'A';
    } // if
    if (hex<'a') {
        return 0;
    } // if
    if (hex<='f') {
        return 10 + hex - 'a';
    } // if
    return 0;
} // Hex(char)

bool Message::Checksum(const char *line) {
    byte sum = 0;
    while (*++line != '*') {
        sum ^= (byte)*line;
    } // while

    byte hi = Hex(*(line+1));
    byte lo = Hex(*(line+2));
    return sum == ((hi << 4) | lo);
} // Message;:Checksum(line)

bool Message::Match(const char *&line, const char *msg) {
    const char *ptr = line + 3; // Go past "$G?"
    while (*msg != '\0') {
        if (*ptr++ != *msg++) {
            return false;
        } // if
    } // while
    line = ptr;
    return true;
} // Message::Match(line, msg)

bool Message::Decode(const char *line) {
    return *line == '*';
} // Message::Decode(line)
