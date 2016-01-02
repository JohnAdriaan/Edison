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

// This helper function returns the number of non-NULL pointers in the array
static byte Num(const char * const *strings) {
    byte num = 0;
    while (*strings++ != 0) {
        ++num;
    } // while
    return num;
} // Num(strings)

// Use Byte to do all the heavy lifting - but remember strings for display purposes
Strings::Strings(const char * const *strings) :
         Byte(1, 0, Num(strings)),
         strings(strings) {
} // Strings::Strings(strings)
