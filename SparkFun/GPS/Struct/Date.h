//
// Date.h
//

#ifndef NMEA0183_Date_h
#define NMEA0183_Date_h

#include "Struct.h"

namespace NMEA0183 {

    // Date (century assumed)
    struct Date : public Struct {

    public: // Methods

        Date();

        bool Decode(const char *&line);

    public: // Variables

        byte day;

        byte month;

        byte year;

    }; // Date

} // NMEA0183

#endif // NMEA0183_Date_h
