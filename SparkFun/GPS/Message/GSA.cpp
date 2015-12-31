//
// GSA.cpp
//

#include "GSA.h"

using namespace NMEA0183;

static const char * const fixes[] = { "",
                                      "NA",
                                      "2D",
                                      "3D",
                                      0 };

GSA::GSA() :
     Message(),
     automatic('M', 'A'),
     fix( fixes ),
     sat( { Byte(2),
            Byte(2),
            Byte(2),
            Byte(2),
            Byte(2),
            Byte(2),
            Byte(2),
            Byte(2),
            Byte(2),
            Byte(2),
            Byte(2),
            Byte(2) } ),
     pdop(),
     hdop(),
     vdop() {
} // GSA::GSA()

bool GSA::Match(const char *&line) {
    return Message::Match(line, "GSA");
} // GSA::Match(line)

void GSA::Clear() {
    Message::Clear();
    automatic.Clear();
    fix.Clear();
    for (byte channel = 0; channel<Sat::NumChannels; ++channel) {
        sat[channel].Clear();
    } // for
    pdop.Clear();
    hdop.Clear();
    vdop.Clear();
} // GSA::Clear()

bool GSA::Decode(const char *line) {
    Clear();

    if (!automatic.Decode(line)) {
        return false;
    } // if
    if (!fix.Decode(line)) {
        return false;
    } // if

    for (byte channel=0; channel<Sat::NumChannels; ++channel) {
        if (!sat[channel].Decode(line)) {
            return false;
        } // if
    } // for

    if (!pdop.Decode(line)) {
        return false;
    } // if
    if (!hdop.Decode(line)) {
        return false;
    } // if
    if (!vdop.Decode(line)) {
        return false;
    } // if
    if (!Message::Decode(line)) {
        return false;
    } // if

    valid = true;
    return true;
} // GSA::Decode(line)
