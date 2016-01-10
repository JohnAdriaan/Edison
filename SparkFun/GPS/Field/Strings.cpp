/*
 * Strings.cpp
 *
 *   Author: John Burger
 *   This code is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *   GNU General Public License for more details.
 */

#include "Strings.h"

using namespace NMEA0183;

// Use Char to do all the heavy lifting - but remember strings for display purposes
Strings::Strings(const char *legal, const char * const *strings) :
         Char(legal),
         strings(strings) {
} // Strings::Strings(legal, strings)

const char *NMEA0183::Strings::String() const {
    if (!IsValid()) {
        return "";
    } // if
    const char * const *string = &strings[0];
    for (const char *ptr = legal;
         (*string!=0) && (*ptr!='\0');
         (++string, ++ptr)) {
        if (*ptr==value) {
            return *string;
        } // if
    } // for
    return "";
} // Strings::String()
