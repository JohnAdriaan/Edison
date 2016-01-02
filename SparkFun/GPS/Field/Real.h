/*
 * Real.h
 *
 *   Author: John Burger
 *   This code is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *   GNU General Public License for more details.
 */

#ifndef NMEA0183_Real_h
#define NMEA0183_Real_h

#include "Field.h"

namespace NMEA0183 {

    class Real : public Field {

    public: // Methods

        explicit Real(real min=0., real max=0.);

        inline real Value() const;

        inline operator real() const;

        bool Decode(const char *&line);

    private: // Constants

        const real min;

        const real max;

    private: // Variables

        real value;

    }; // Real

} // NMEA0183

inline NMEA0183::real NMEA0183::Real::Value() const {
    return value;
} // Real::Value()

inline NMEA0183::Real::operator NMEA0183::real() const {
    return Value();
} // Real::operator real()

#endif // NMEA0183_Real_h
