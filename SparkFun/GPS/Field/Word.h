/*
 * Word.h
 *
 *   Author: John Burger
 *   This code is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *   GNU General Public License for more details.
 */

#ifndef NMEA0183_Word_h
#define NMEA0183_Word_h

#include "Field.h"

namespace NMEA0183 {

    class Word : public Field {

    public: // Methods

        explicit Word(byte width, word min=0, word max=0);

        inline word Value() const;

        inline operator word() const;

        bool Decode(const char *&line);

    private: // Constants

        const byte width;

        const word min;

        const word max;

    private: // Variables

        word value;

    }; // Word

} // NMEA0183

inline NMEA0183::word NMEA0183::Word::Value() const {
    return value;
} // Word::Value()

inline NMEA0183::Word::operator NMEA0183::word() const {
    return Value();
} // Word::operator Word()

#endif // NMEA0183_Word_h
