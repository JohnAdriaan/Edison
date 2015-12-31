//
// Field.h
//

#ifndef NMEA0183_Field_h
#define NMEA0183_Field_h

#include "../NMEA0183.h"

namespace NMEA0183 {

    // The base Field class
    class Field {

    public: // Methods

        // Return whether Field is valid or not
        inline bool IsValid() const;

        // Clear Field to Invalid
        void Clear();

    protected: // Enums

        // The possible results of DecodeByte/Word/Real() below
        enum Decodes {
            Empty,
            Invalid,
            Valid
        }; // Decodes

    protected: // Methods

        // Can't instantiate just a bare Field()!
        Field();

        // Call this at the start of derived Decode function.
        // If it returns false, we're out of kilter in the message.
        // The Decode is Invalid - abort.
        bool Decode(const char *&line);

    protected: // Static methods

        // All Fields, at their base, are either Bytes, Words or Reals.
        // Decode next Field in line, returning the value, after checking against min and max (unless they're equal to each other)
        static Decodes DecodeByte(const char *&line, byte width, byte &value, byte min=0, byte max=0);

        static Decodes DecodeWord(const char *&line, byte width, word &value, word min=0, word max=0);

        static Decodes DecodeReal(const char *&line, byte width, real &value, real min=0., real max=0.);

    protected: // Variables

        bool valid;

    }; // Field

} // NMEA0183

inline bool NMEA0183::Field::IsValid() const {
    return valid;
} // Field::IsValid()

#endif // NMEA0183_Field_h
