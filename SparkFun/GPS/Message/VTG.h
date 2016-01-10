/*
 * VTG.h
 *
 *   Author: John Burger
 *   This code is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *   GNU General Public License for more details.
 */

#ifndef NMEA0183_VTG_h
#define NMEA0183_VTG_h

#include "../Field/Bool.h"
#include "../Field/Char.h"
#include "../Field/Real.h"
#include "../Struct/Mode.h"
#include "Message.h"

namespace NMEA0183 {

    // Course over Ground and Ground Speed
    struct VTG : public Message {

    public: // Methods

        VTG();

        bool Match(const char *&line);

        void Clear();

        bool Decode(const char *line);

    public: // Variables

        Real trueCourse;

        Char t;

        Real magCourse;

        Char m;

        Real knots;

        Char n;

        Real kph;

        Char k;

        Mode mode;

    }; // VTG

} // NMEA0183

#endif // NMEA0183_VTG_h
