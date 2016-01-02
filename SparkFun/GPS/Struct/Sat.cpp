/*
 * Sat.cpp
 *
 *   Author: John Burger
 *   This code is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *   GNU General Public License for more details.
 */

#include "Sat.h"

using namespace NMEA0183;

Sat::Sat() :
     Struct(),
     id(2,1,MaxID),
     el(2,0,90),
     az(3,0,360),
     snr(2,0,99) {
} // Sat::Sat()

void Sat::Clear() {
    Struct::Clear();
    id.Clear();
    el.Clear();
    az.Clear();
    snr.Clear();
} // Sat::Clear()

bool Sat::Decode(const char *&line) {
    if (!id.Decode(line)) {
        return false;
    } // if
    if (!el.Decode(line)) {
        return false;
    } // if
    if (!az.Decode(line)) {
        return false;
    } // if
    if (!snr.Decode(line)) {
        return false;
    } // if
    valid = true;
    return true;
} // Sat::Decode(line)
