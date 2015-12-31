//
// Alt.h
//

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
