/*
 * GLL.h
 *
 *   Author: John Burger
 *   This code is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *   GNU General Public License for more details.
 */

#ifndef NMEA0183_GLL_h
#define NMEA0183_GLL_h

#include "../Field/Bool.h"
#include "../Struct/Lat.h"
#include "../Struct/Lon.h"
#include "../Struct/UTC.h"
#include "../Struct/Mode.h"
#include "Message.h"

namespace NMEA0183 {

    // Geographic Position - Latitude/Longitude
    struct GLL : public Message {

    public: // Methods

        GLL();

        bool Match(const char *&line);

        void Clear();

        bool Decode(const char *line);

    public: // Variables

        Lat lat;

        Lon lon;

        UTC utc;

        Bool status;

        Mode mode;

    }; // GLL

} // NMEA0183

#endif // NMEA0183_GLL_h
