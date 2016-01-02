/*
 * Lat.h
 *
 *   Author: John Burger
 *   This code is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *   GNU General Public License for more details.
 */

#ifndef NMEA0183_Lat_h
#define NMEA0183_Lat_h

#include "../Field/Bool.h"
#include "../Field/Byte.h"
#include "Struct.h"

namespace NMEA0183 {

    // Latitude
    struct Lat : public Struct {

    public: // Methods

        Lat();

        void Clear();

        bool Decode(const char *&line);

    public: // Variables

        Byte degrees;

        real minutes;

        Bool north;

    }; // Lat

} // NMEA0183

#endif // GPS_NMEA0183_Lat_h
