/*
 * Sat.h
 *
 *   Author: John Burger
 *   This code is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *   GNU General Public License for more details.
 */

#ifndef NMEA0183_Sat_h
#define NMEA0183_Sat_h

#include "../Field/Byte.h"
#include "../Field/Word.h"
#include "Struct.h"

namespace NMEA0183 {

    // Satellite information
    struct Sat : public Struct {

    public: // Static constants

        static const byte MaxID = 99;

        static const byte MaxSats = 32;

        static const byte NumChannels = 12; // Number channels used for decoding

        static const byte MaxChannels = 24; // Maximum number of channels

    public: // Methods

        Sat();

        void Clear();

        bool Decode(const char *&line);

    public: // Variables

        Byte id; // Satellite ID (01-MaxID)

        Byte el;  // Elevation

        Word az; // Azimuth

        Byte snr; // Signal/Noise ratio

    }; // Sat

} // NMEA0183

#endif // NMEA0183_Sat_h
