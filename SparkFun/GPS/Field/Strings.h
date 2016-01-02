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

#include "Byte.h"

namespace NMEA0183 {

    // Converts a byte into a string - don't forget the NULL pointer (not "") at the end. e.g.
    // Strings({"Zero","One","Two","Three",NULL});
    class Strings : public Byte {

    public: // Methods

        // Pass in the array of strings to convert value into
        explicit Strings(const char * const *strings);

        // The representation of num as a String()
        inline const char *String() const;

        // A helper function
        inline operator const char *() const;

    private: // Constants

        const char * const * const strings;

    }; // Strings

} // NMEA0183

inline const char *NMEA0183::Strings::String() const {
    if (!IsValid()) {
        return "";
    } // if
    return strings[value];
} // Strings::String()

inline NMEA0183::Strings::operator const char *() const {
    return String();
} // Strings::operator const char *()

#endif // NMEA0183_Strings_h
