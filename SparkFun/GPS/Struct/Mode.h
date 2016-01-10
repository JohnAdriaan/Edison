/*
 * Mode.h
 *
 *   Author: John Burger
 *   This code is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *   GNU General Public License for more details.
 */

#ifndef NMEA0183_Mode_h
#define NMEA0183_Mode_h

#include "../Field/Strings.h"

namespace NMEA0183 {

    // GPS Mode
    struct Mode : public Strings {

    public: // Methods

        Mode();

    }; // Mode

} // NME0183

#endif // NMEA0183_Mode_h
