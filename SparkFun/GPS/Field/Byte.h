///
// Byte.h
//

#ifndef NMEA0183_Byte_h
#define NMEA0183_Byte_h

#include "Field.h"

namespace NMEA0183 {

    class Byte : public Field {

    public: // Methods

        explicit Byte(byte width, byte min=0, byte max=0);

        inline byte Value() const;

        inline operator byte() const;

        bool Decode(const char *&line);

    protected: // Constants

        const byte width;

        const byte min;

        const byte max;

    protected: // Variables

        byte value;

    }; // Byte

} // NMEA0183

inline NMEA0183::byte NMEA0183::Byte::Value() const {
    return value;
} // Byte::Value()

inline NMEA0183::Byte::operator NMEA0183::byte() const {
    return Value();
} // Byte::operator byte()

#endif // NMEA0183_Byte_h
