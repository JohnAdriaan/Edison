//
// GSA.h
//

#ifndef NMEA0183_GSA_h
#define NMEA0183_GSA_h

#include "../Field/Bool.h"
#include "../Field/Byte.h"
#include "../Field/Real.h"
#include "../Field/Strings.h"
#include "../Struct/Sat.h"
#include "Message.h"

namespace NMEA0183 {

    // GNSS Dilution of Precision and Active Satellites
    struct GSA : public Message {

    public: // Methods

        GSA();

        bool Match(const char *&line);

        void Clear();

        bool Decode(const char *line);

    public: // Variables;

        Bool automatic;

        Strings fix;

        Byte sat[Sat::NumChannels];

        Real pdop;

        Real hdop;

        Real vdop;

    }; // GSA

} // NMEA0183

#endif // NMEA0183_GSA_h
