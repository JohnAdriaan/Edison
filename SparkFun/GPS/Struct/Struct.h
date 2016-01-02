/*
 * Struct.h
 *
 *   Author: John Burger
 *   This code is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *   GNU General Public License for more details.
 */

#ifndef NMEA0183_Struct_hH_
#define NMEA0183_Struct_hH_

#include "../Field/Field.h"

namespace NMEA0183 {

    struct Struct : public Field {

    protected: // Methods

        Struct();

    }; // Struct

} // NMEA0183

#endif // NMEA0183_Struct_h
