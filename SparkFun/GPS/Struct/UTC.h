/*
 * UTC.h
 *
 *   Author: John Burger
 *   This code is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *   GNU General Public License for more details.
 */

#ifndef NMEA0183_UTC_h
#define NMEA0183_UTC_h

#include "Struct.h"

namespace NMEA0183 {

    // Universal Coordinated Time
    struct UTC : public Struct {

    public: // Methods

        UTC();

        bool Decode(const char *&line);

    public: // Variables

        byte hour;

        byte min;

        real sec;

    }; // UTC

} // NMEA0183

#endif // NMEA0183_UTC_h
