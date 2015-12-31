//
// Bool.h
//

#ifndef NMEA0183_Bool_h
#define NMEA0183_Bool_h

#include "Field.h"

namespace NMEA0183 {

    class Bool : public Field {

    public: // Methods

        // Chars that mean 'false' and 'true'
        Bool(char no, char yes);

        inline char Char() const;

        inline bool Value() const;

        inline operator bool() const;

        bool Decode(const char *&line);

    private: // Constants

        const char no;

        const char yes;

    private: // Variables

        bool value;

    }; // Bool

} // NMEA0183

inline char NMEA0183::Bool::Char() const {
    if (!IsValid()) {
        return ' ';
    } // if
    return value ? yes : no;
} // Bool::Char()

inline bool NMEA0183::Bool::Value() const {
    return value;
} // Bool::Value()

inline NMEA0183::Bool::operator bool() const {
    return Value();
} // Bool::operator bool()

#endif // NMEA0183_Bool_h
