/*
 * Char.cpp
 *
 *   Author: John Burger
 *   This code is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *   GNU General Public License for more details.
 */

#include "Char.h"

using namespace NMEA0183;

Char::Char(const char *legal) :
      Field(),
      legal(legal),
      value() {
} // Char::Char(legal)

bool Char::Decode(const char *&line) {
    Clear();

    if (!Field::Decode(line)) {
        return false;
    } // if
    value = *line++;
    switch (value) {
    case ',' :
    case '*' :
        --line;
        return true;
    } // switch

    for (const char *ptr = legal; *ptr!='\0'; ++ptr) {
        if (value == *ptr) {
            valid = true;
            return true;
        } // if
    } // for
    return false;
} // Char::Decode(line)
