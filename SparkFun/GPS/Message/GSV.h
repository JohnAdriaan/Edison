//
// GSV.h
//

#ifndef NMEA0183_GSV_h
#define NMEA0183_GSV_h

#include "../Field/Byte.h"
#include "../Struct/Sat.h"
#include "Message.h"

namespace NMEA0183 {

    // GNSS Satellites in View (may take many lines)
    struct GSV : public Message {

    public: // Methods

        GSV();

        bool Match(const char *&line);

        void Clear(bool all);

        bool Decode(const char *line);

    public: // Variables

        Byte inView;

        Sat sat[Sat::MaxChannels];

    private: // Variables

        Byte msg;

        Byte num;

        byte tmpNum;

        Byte tmpInView;

        byte index;

    }; // GSV

} // NMEA0183

#endif // NMEA0183_GSV_h
