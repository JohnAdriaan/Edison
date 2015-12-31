//
// Screen.h
//

#ifndef SCREEN_H_
#define SCREEN_H_

#include <GPS/GP20U7.h>
#include <oled/Edison_OLED.h>

class Screen : public edOLED {

public: // Enums

    enum Screens {
        None,
        Summary,
        GGA1,
        GGA2,
        GLL,
        GSA1,
        GSA2,
        GSV1,
        GSV2,
        GSV3,
        GSV4,
        GSV5,
        GSV6,
        RMC1,
        RMC2,
        VTG,
        Diag1,
        Diag2
    }; // Screens

public: // Methods

    Screen(const GP20U7 &gps);

    // Return whether to call Show()
    bool Received(GP20U7::Messages message);

    // Return whether to call Show()
    bool Prev();

    // Return whether to call Show()
    bool Next();

    // Return whether to call Show()
    bool Left();

    // Return whether to call Show()
    bool Right();

    void Show();

    ~Screen();

private: // Methods

    void Clear();

    void ShowSummary();

    void ShowGGA(bool loc);

    void ShowGLL();

    void ShowGSA(bool sats);

    void ShowGSV(unsigned start);

    void ShowRMC(bool loc);

    void ShowVTG();

    void ShowDiag1();

    void ShowDiag2();

private: // Methods

    void Print(const NMEA0183::Byte &sats);

    void Print(const NMEA0183::Bool *status,
               const NMEA0183::Bool &valid);

    void Print(const NMEA0183::Real &value,
               const NMEA0183::Char &c);

    void Print(const char *string,
               const NMEA0183::Real &value);

    void Print(const NMEA0183::Real &value,
               const char *string);

    void Print(const NMEA0183::Lat &lat,
               const NMEA0183::Lon &lon);

    void Print(const NMEA0183::Date &date);

    void Print(const NMEA0183::UTC &utc);

    void Print(const NMEA0183::Lat &lat,unsigned y);

    void Print(const NMEA0183::Lon &lon,unsigned y);

    void Print(const NMEA0183::Alt &alt);

    void Print(const NMEA0183::Sat &sat, unsigned y);

private: // Variables

    const GP20U7 &gps;

    unsigned msg[GP20U7::GP20U7_Last];

    unsigned total;

    Screens screen;

}; // Screen

#endif // SCREEN_H_
