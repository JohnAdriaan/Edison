/*
 * Date.h
 *
 *   Author: John Burger
 *   This code is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *   GNU General Public License for more details.
 */

#ifndef NMEA0183_Date_h
#define NMEA0183_Date_h

#include "Struct.h"

namespace NMEA0183 {

    // Date (century assumed)
    struct Date : public Struct {

    public: // Methods

        Date();

        bool Decode(const char *&line);

    public: // Variables

        byte day;

        byte month;

        byte year;

    }; // Date

} // NMEA0183

#endif // NMEA0183_Date_h
