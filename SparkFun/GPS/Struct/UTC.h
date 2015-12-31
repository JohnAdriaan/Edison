//
// UTC.h
//

#ifndef NMEA0183_UTC_h
#define NMEA0183_UTC_h

#include "Struct.h"

namespace NMEA0183 {

    // Universal Coordinated Time
    struct UTC : public Struct {

    public: // Methods

        UTC();

        bool Decode(const char *&line);

    public: // Variables

        byte hour;

        byte min;

        real sec;

    }; // UTC

} // NMEA0183

#endif // NMEA0183_UTC_h
