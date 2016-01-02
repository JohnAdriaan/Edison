/*
 * Alt.h
 *
 *   Author: John Burger
 *   This code is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *   GNU General Public License for more details.
 */

#ifndef NMEA0183_Alt_h
#define NMEA0183_Alt_h

#include "../Field/Bool.h"
#include "../Field/Real.h"
#include "Struct.h"

namespace NMEA0183 {

    // Altitude
    struct Alt : public Struct {

    public: // Methods

        Alt();

        void Clear();

        bool Decode(const char *&line);

    public: // Variables

        Real alt;

        Bool metres;

    }; // Alt

} // NME0183

#endif // NMEA0183_Alt_h
