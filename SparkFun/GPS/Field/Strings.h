/*
 * Strings.h
 *
 *   Author: John Burger
 *   This code is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *   GNU General Public License for more details.
 */

#ifndef NMEA0183_Strings_h
#define NMEA0183_Strings_h

#include "Char.h"

namespace NMEA0183 {

    // Converts a byte into a string - don't forget the NULL pointer (not "") at the end. e.g.
    // Strings("0123", {"Zero","One","Two","Three",NULL});
    class Strings : public Char {

    public: // Methods

        // Pass in the array of strings to convert Char into
        Strings(const char *legal, const char * const *strings);

        // The representation of Char as a String()
        const char *String() const;

        // A helper function
        inline operator const char *() const;

    private: // Constants

        const char * const * const strings;

    }; // Strings

} // NMEA0183

inline NMEA0183::Strings::operator const char *() const {
    return String();
} // Strings::operator const char *()

#endif // NMEA0183_Strings_h
