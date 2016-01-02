/*
 * GP20U7.cpp
 *
 *   Author: John Burger
 *   This code is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *   GNU General Public License for more details.
 */

#include "GP20U7.h"

using namespace NMEA0183;

GP20U7::GP20U7() :
        gga(),
        gll(),
        gsa(),
        gsv(),
        rmc(),
        vtg() {
} // GP20U7::GP20U7()

GP20U7::Messages GP20U7::Decode(const char *line) {
    if (!Message::Valid(line)) {
        return INV_Invalid;
    } // if

    if (!Message::Checksum(line)) {
        return CHK_Checksum;
    } // if

    if (gga.Match(line)) {
        return gga.Decode(line) ?
               GGA_FixedData :
               GGA_Invalid;
    } // if
    if (gll.Match(line)) {
        return gll.Decode(line) ?
               GLL_LatLong :
               GLL_Invalid;
    } // if
    if (gsa.Match(line)) {
        return gsa.Decode(line) ?
               GSA_DilutionPrecision :
               GSA_Invalid;
    } // if
    if (gsv.Match(line)) {
        return gsv.Decode(line) ?
               GSV_SatsView :
               GSV_Invalid;
    } // if
    if (rmc.Match(line)) {
        return rmc.Decode(line) ?
               RMC_MinimumData :
               RMC_Invalid;
    } // if
    if (vtg.Match(line)) {
        return vtg.Decode(line) ?
               VTG_CourseSpeed :
               VTG_Invalid;
    } // if

    return XXX_Unknown;
} // GP20U7::Decode(line)
