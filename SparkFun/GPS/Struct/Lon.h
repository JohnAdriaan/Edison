/*
 * Lon.h
 *
 *   Author: John Burger
 *   This code is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *   GNU General Public License for more details.
 */

#ifndef NMEA0183_Lon_h
#define NMEA0183_Lon_h

#include "../Field/Bool.h"
#include "../Field/Byte.h"
#include "Struct.h"

namespace NMEA0183 {

    // Longitude
    struct Lon : public Struct {

    public: // Methods

        Lon();

        void Clear();

        bool Decode(const char *&line);

    public: // Variables

        Byte degrees;

        real minutes;

        Bool east;

    }; // Lon

} // NMEA0183

#endif // NMEA0183_Lon_h
