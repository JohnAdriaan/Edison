/*
 * VTG.cpp
 *
 *   Author: John Burger
 *   This code is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *   GNU General Public License for more details.
 */

#include "VTG.h"

using namespace NMEA0183;

VTG::VTG() :
     Message(),
     trueCourse(0., 360.),
     t("T"),
     magCourse(0., 360.),
     m("M"),
     knots(),
     n("N"),
     kph(),
     k("K"),
     mode() {
} // VTG::VTG()

bool VTG::Match(const char *&line) {
    return Message::Match(line, "VTG");
} // VTG::Match(line)

void VTG::Clear() {
    Message::Clear();
    trueCourse.Clear();
    t.Clear();
    magCourse.Clear();
    m.Clear();
    knots.Clear();
    n.Clear();
    kph.Clear();
    k.Clear();
    mode.Clear();
} // VTG::CLear()

bool VTG::Decode(const char *line) {
    Clear();
    if (!trueCourse.Decode(line)) {
        return false;
    } // if
    if (!t.Decode(line)) {
        return false;
    } // if
    if (!magCourse.Decode(line)) {
        return false;
    } // if
    if (!m.Decode(line)) {
        return false;
    } // if
    if (!knots.Decode(line)) {
        return false;
    } // if
    if (!n.Decode(line)) {
        return false;
    } // if
    if (!kph.Decode(line)) {
        return false;
    } // if
    if (!k.Decode(line)) {
        return false;
    } // if
    mode.Decode(line); // Optional
    if (!Message::Decode(line)) {
        return false;
    } // if
    Message::valid = true;
    return true;
} // VTG::Decode(line)
