/*
 * GGA.cpp
 *
 *   Author: John Burger
 *   This code is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *   GNU General Public License for more details.
 */

#include "../Struct/Sat.h"
#include "GGA.h"

using namespace NMEA0183;

static const char * const fixes[] = { "N/A ",
                                      "GPS ",
                                      "Diff",
                                      "Prec",
                                      0 };

GGA::GGA() :
     Message(),
     utc(),
     lat(),
     lon(),
     fix( fixes ),
     sats(2, 0, 12),
     hdop(),
     msl(),
     geoid(),
     age(),
     id(4) {
} // GGA::GGA()

bool GGA::Match(const char *&line) {
    return Message::Match(line, "GGA");
} // GGA::Match(line)

void GGA::Clear() {
    Field::Clear();
    utc.Clear();
    lat.Clear();
    lon.Clear();
    fix.Clear();
    sats.Clear();
    hdop.Clear();
    msl.Clear();
    geoid.Clear();
    age.Clear();
    id.Clear();
} // GGA::Clear()

bool GGA::Decode(const char *line) {
    Clear();

    if (!utc.Decode(line)) {
        return false;
    } // if
    if (!lat.Decode(line)) {
        return false;
    } // if
    if (!lon.Decode(line)) {
        return false;
    } // if
    if (!fix.Decode(line)) {
        return false;
    } // if
    if (!sats.Decode(line)) {
        return false;
    } // if
    if (!hdop.Decode(line)) {
        return false;
    } // if
    if (!msl.Decode(line)) {
        return false;
    } // if
    if (!geoid.Decode(line)) {
        return false;
    } // if
    if (!age.Decode(line)) { // optional
        return false;
    } // if
    if (!id.Decode(line)) { // optional
        return false;
    } // if
    if (!Message::Decode(line)) {
        return false;
    } // if
    valid = true;
    return true;
} // GGA::Decode(line)
