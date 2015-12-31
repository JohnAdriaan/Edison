//
// NMEA0183.h
//

#ifndef NMEA0183_h
#define NMEA0183_h

#include <stdint.h>

namespace NMEA0183 {

    // Many fields are only a byte in size
    typedef uint8_t byte;

    // Some are slightly larger
    typedef uint16_t word;

    // And some are decimal numbers
    typedef double real;

    // NMEA-0183 messages are a series of character or numerical values, separated by commas.
    // But each one might be omitted, so a flag is required - called "valid" in the base Field class.
    class Field;

        // This is one of two character values, indicating False or True (or empty...)
        class Bool;

        // This could be one of a number of possible characters
        class Char;

        // This is an unsigned value less than 256
        class Byte;

        // This is an unsigned value less than 65,536
        class Word;

        // This is a decimal value
        class Real;

        // This is actually a Byte - but the value should be printed as one of an array of strings
        class Strings;

    // Some NMEA-0183 fields are either formatted digits (ddmmyy as Date), or come in groups (ddmm.mmm,N,).
    // These Structures can be referenced for common code - but deep down they're really just Fields.
    struct Struct;

        // The time ",hhmmss.ss", decoded into hour, min, sec
        struct UTC;

        // The date ",ddmmyy", decoded into day, month, year
        struct Date;

        // The latitude ",ddmm.mmm,S,", decoded into degrees and minutes, but displayed as dd°Smm'ss"
        struct Lat;

        // The longitude ",dddmm.mmm,E,", decoded into degrees and minutes, but displayed as ddd°Emm'ss"
        struct Lon;

        // The altitude ",aa.aaa,M,", decoded into altitude and units (feet or metres)
        struct Alt;

        // The fields of a satellite: azimuth, elevation and signal-to-noise ratio (snr)
        struct Sat;

    // An NMEA-0183 Message is a collection of Fields and Structs, prefixed with a standard code
    struct Message;

        // GPS Fix Data
        struct GGA;

        // GPS Lat Long
        struct GLL;

        // GPS Dilution of Precision and Active Satellites
        struct GSA;

        // GPS Satellites in View
        struct GSV;

        // Recommended Minimum data, type C
        struct RMC;

        // Track Made Good and Ground Speed
        struct VTG;

} // NMEA0183

#endif // NMEA0183_h
