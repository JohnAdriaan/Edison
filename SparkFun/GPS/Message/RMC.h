/*
 * RMC.h
 *
 *   Author: John Burger
 *   This code is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *   GNU General Public License for more details.
 */

#ifndef NMEA0183_RMC_h
#define NMEA0183_RMC_h

#include "../Field/Bool.h"
#include "../Field/Char.h"
#include "../Field/Real.h"
#include "../Struct/UTC.h"
#include "../Struct/Lat.h"
#include "../Struct/Lon.h"
#include "../Struct/Date.h"
#include "Message.h"

namespace NMEA0183 {

    // Recommended Minimum Specific GNSS Data
    struct RMC : public Message {

    public: // Methods

        RMC();

        bool Match(const char *&line);

        void Clear();

        bool Decode(const char *line);

    public: // Variables

        UTC utc;

        Bool status;

        Lat lat;

        Lon lon;

        Real speed;

        Real course;

        Date date;

        Real var;

        Char magnetic;

        Bool valid;

    }; // RMC

} // NMEA0183

#endif // NMEA0183_RMC_h
