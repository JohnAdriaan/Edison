/*
 * Char.h
 *
 *   Author: John Burger
 *   This code is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *   GNU General Public License for more details.
 */

#ifndef NMEA0183_Char_h
#define NMEA0183_Char_h

#include "Field.h"

namespace NMEA0183 {

    class Char : public Field {

    public: // Methods

        explicit Char(const char *legal);

        inline char Value() const;

        inline operator char() const;

        bool Decode(const char *&line);

    protected: // Constants

        const char * const legal;

    protected: // Variables

        char value;

    }; // Char

} // NMEA0183

inline char NMEA0183::Char::Value() const {
    return IsValid() ?
           value :
           ' ';
} // Char::Value()

inline NMEA0183::Char::operator char() const {
    return Value();
} // Char::operator char()

#endif // NMEA0183_Char_h
