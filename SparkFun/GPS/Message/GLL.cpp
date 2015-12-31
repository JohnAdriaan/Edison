//
// GLL.cpp
//

#include "GLL.h"

using namespace NMEA0183;

GLL::GLL() :
     Message(),
     lat(),
     lon(),
     utc(),
     status('V', 'A'),
     valid('N', 'A') {
} // GLL::GLL()

void GLL::Clear() {
    Message::Clear();
    lat.Clear();
    lon.Clear();
    utc.Clear();
    status.Clear();
    valid.Clear();
} // GLL::Clear()

bool GLL::Match(const char *&line) {
    return Message::Match(line, "GLL");
} // GLL::Match(line)

bool GLL::Decode(const char *line) {
    Clear();
    if (!lat.Decode(line)) {
        return false;
    } // if
    if (!lon.Decode(line)) {
        return false;
    } // if
    if (!utc.Decode(line)) {
        return false;
    } // if
    if (!status.Decode(line)) {
        return false;
    } // is
    if (!valid.Decode(line)) {
        return false;
    } // if
    if (!Message::Decode(line)) {
        return false;
    } // if
    Message::valid = true;
    return true;
} // GLL::Decode(line)
