//
// RMC.cpp
//

#include "RMC.h"

using namespace NMEA0183;

RMC::RMC() :
     Message(),
     utc(),
     status('V', 'A'),
     lat(),
     lon(),
     speed(),
     course(0., 360.),
     date(),
     var(),
     magnetic("EW"),
     valid('N', 'A') {
} // RMC::RMC()

bool RMC::Match(const char *&line) {
    return Message::Match(line, "RMC");
} // RMC::Match(line)

void RMC::Clear() {
    Message::Clear();
    utc.Clear();
    status.Clear();
    lat.Clear();
    lon.Clear();
    speed.Clear();
    course.Clear();
    date.Clear();
    var.Clear();
    magnetic.Clear();
    valid.Clear();
} // RMC::Clear()

bool RMC::Decode(const char *line) {
    Clear();

    if (!utc.Decode(line)) {
        return false;
    } // if
    if (!status.Decode(line)) {
        return false;
    } // if
    if (!lat.Decode(line)) {
        return false;
    } // if
    if (!lon.Decode(line)) {
        return false;
    } // if
    if (!speed.Decode(line)) {
        return false;
    } // if
    if (!course.Decode(line)) {
        return false;
    } // if
    if (!date.Decode(line)) {
        return false;
    } // if
    if (!var.Decode(line)) {
        return false;
    } // if
    if (!magnetic.Decode(line)) {
        return false;
    } // if
    if (!valid.Decode(line)) {
        return false;
    } // if
    if (!Message::Decode(line)) {
        return false;
    } // if
    Message::valid = true;
    return true;
} // RMC::Decode(line)
