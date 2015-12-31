//
// Lon.h
//

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
