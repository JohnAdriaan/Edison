//
// Screen.cpp
//

#include <stdio.h> // for sprintf

#include "Screen.h"

static const bool wrapUD = false;  // Do Up() & Down() wrap around?

static const bool wrapLR = false; // Do Left() & Right() wrap around?

static const bool metric = true;

static const char degree = 0xF7; // '÷';

Screen::Screen(const GP20U7 &gps) :
        edOLED(),
        gps(gps),
        msg(),
        total(0),
        screen(Summary) {
    begin();
    setFontType(0);
} // Screen::Screen(gps)

bool Screen::Received(GP20U7::Messages message) {
    ++msg[message];
    ++total;
    switch (screen) {
    case None :
        return false;
    case Summary :
        if (message<GP20U7::GP20U7_Start) {
            return false;
        } // if
        if (message>GP20U7::GP20U7_End) {
            return false;
        } // if
        break;
    case GGA1 :
    case GGA2 :
        if (message!=GP20U7::GGA_FixedData) {
            return false;
        } // if
        break;
    case GLL :
        if (message!=GP20U7::GLL_LatLong) {
            return false;
        } // if
        break;
    case GSA1 :
    case GSA2 :
        if (message!=GP20U7::GSA_DilutionPrecision) {
            return false;
        } // if
        break;
    case GSV1 :
    case GSV2 :
    case GSV3 :
    case GSV4 :
    case GSV5 :
    case GSV6 :
        if (message!=GP20U7::GSV_SatsView) {
            return false;
        } // if
        break;
    case RMC1 :
    case RMC2 :
        if (message!=GP20U7::RMC_MinimumData) {
            return false;
        } // if
        break;
    case VTG :
        if (message!=GP20U7::VTG_CourseSpeed) {
            return false;
        } // if
        break;
    case Diag1 :
        break;
    case Diag2 :
        if (message<GP20U7::GP20U7_Start) {
            return false;
        } // if
        break;
    } // switch
    return true;
} // Screen::Received(Messages)

bool Screen::Prev() {
    switch (screen) {
    case None :
        return false;
    case Summary :
        if (!wrapUD) {
            return false;
        } // if
        screen = Diag1;
        break;
    case GGA1 :
    case GGA2 :
        screen = Summary;
        break;
    case GLL :
        screen = GGA1;
        break;
    case GSA1 :
    case GSA2 :
        screen = GLL;
        break;
    case GSV1 :
    case GSV2 :
    case GSV3 :
    case GSV4 :
    case GSV5 :
    case GSV6 :
        screen = GSA1;
        break;
    case RMC1 :
    case RMC2 :
        screen = GSV1;
        break;
    case VTG :
        screen = RMC1;
        break;
    case Diag1 :
    case Diag2 :
        screen = VTG;
        break;
    } // switch
    return true;
} // Screen::Prev()

bool Screen::Next() {
    switch (screen) {
    case None :
        return false;
    case Summary :
        screen = GGA1;
        break;
    case GGA1 :
    case GGA2 :
        screen = GLL;
        break;
    case GLL :
        screen = GSA1;
        break;
    case GSA1 :
    case GSA2 :
        screen = GSV1;
        break;
    case GSV1 :
    case GSV2 :
    case GSV3 :
    case GSV4 :
    case GSV5 :
    case GSV6 :
        screen = RMC1;
        break;
    case RMC1 :
    case RMC2 :
        screen = VTG;
        break;
    case VTG :
        screen = Diag1;
        break;
    case Diag1 :
    case Diag2 :
        if (!wrapUD) {
            return false;
        } // if
        screen = Summary;
        break;
    } // switch
    return true;
} // Screen::Next()

bool Screen::Left() {
    switch (screen) {
    case None :
        return false;
    case Summary :
        return false;
    case GGA1 :
        if (!wrapLR) {
            return false;
        } // if
        screen = GGA2;
        break;
    case GGA2 :
        screen = GGA1;
        break;
    case GLL :
        return false;
    case GSA1 :
        if (!wrapLR) {
            return false;
        } // if
        screen = GSA2;
        break;
    case GSA2 :
        screen = GSA1;
        break;
    case GSV1 :
        if (!wrapLR) {
            return false;
        } // if
        screen = GSV6;
        break;
    case GSV2 :
        screen = GSV1;
        break;
    case GSV3 :
        screen = GSV2;
        break;
    case GSV4 :
        screen = GSV3;
        break;
    case GSV5 :
        screen = GSV4;
        break;
    case GSV6 :
        screen = GSV5;
        break;
    case RMC1 :
        if (!wrapLR) {
            return false;
        } // if
        screen = RMC2;
        break;
    case RMC2 :
        screen = RMC1;
        break;
    case VTG :
        return false;
    case Diag1 :
        if (!wrapLR) {
            return false;
        } // if
        screen = Diag2;
        break;
    case Diag2 :
        screen = Diag1;
        break;
    } // switch
    return true;
} // Screen::Left()

bool Screen::Right() {
    switch (screen) {
    case None :
        return false;
    case Summary :
        return false;
    case GGA1 :
        screen = GGA2;
        break;
    case GGA2 :
        if (!wrapLR) {
            return false;
        } // if
        screen = GGA1;
        break;
    case GLL :
        return false;
    case GSA1 :
        screen = GSA2;
        break;
    case GSA2 :
        if (!wrapLR) {
            return false;
        } // if
        screen = GSA1;
        break;
    case GSV1 :
        screen = GSV2;
        break;
    case GSV2 :
        screen = GSV3;
        break;
    case GSV3 :
        screen = GSV4;
        break;
    case GSV4 :
        screen = GSV5;
        break;
    case GSV5 :
        screen = GSV6;
        break;
    case GSV6 :
        if (!wrapLR) {
            return false;
        } // if
        screen = GSV1;
        break;
    case RMC1 :
        screen = RMC2;
        break;
    case RMC2 :
        if (!wrapLR) {
            return false;
        } // if
        screen = RMC1;
        break;
    case VTG :
        return false;
    case Diag1 :
        screen = Diag2;
        break;
    case Diag2 :
        if (!wrapLR) {
            return false;
        } // if
        screen = Diag1;
        break;
    } // switch
    return true;
} // Screen::Right()

void Screen::Clear() {
    clear(PAGE);
    display();
} // Screen::Clear()

void Screen::Show() {
    clear(PAGE);
    switch (screen) {
    case None :
        break;
    case Summary :
        ShowSummary();
        break;
    case GGA1 :
        ShowGGA(true);
        break;
    case GGA2 :
        ShowGGA(false);
        break;
    case GLL :
        ShowGLL();
        break;
    case GSA1 :
        ShowGSA(true);
        break;
    case GSA2 :
        ShowGSA(false);
        break;
    case GSV1 :
        ShowGSV(0);
        break;
    case GSV2 :
        ShowGSV(4);
        break;
    case GSV3 :
        ShowGSV(8);
        break;
    case GSV4 :
        ShowGSV(12);
        break;
    case GSV5 :
        ShowGSV(16);
        break;
    case GSV6 :
        ShowGSV(20);
        break;
    case RMC1 :
        ShowRMC(true);
        break;
    case RMC2 :
        ShowRMC(false);
        break;
    case VTG :
        ShowVTG();
        break;
    case Diag1 :
        ShowDiag1();
        break;
    case Diag2 :
        ShowDiag2();
        break;
    } // switch
    display();
} // Screen::Show()

void Screen::ShowSummary() {
    setCursor(0,0);
    print("20U7");
    setCursor(36,0);
    print(gps.gga.sats);
    Print(gps.gsv.inView);
    setCursor(0,8);
    Print(gps.rmc.utc);

    setCursor(0,16);
    Print(gps.vtg.trueCourse, gps.vtg.t);
    setCursor(0,24);
    if (metric) {
        Print(gps.vtg.kph, gps.vtg.k);
    } // if
    else {
        Print(gps.vtg.knots, gps.vtg.n);
    } // else
    Print(gps.rmc.lat, gps.rmc.lon);
} // Screen::ShowSummary()

void Screen::ShowGGA(bool loc) {
    setCursor(0,0);
    print("GGA");
    setCursor(21,0);
    print(gps.gga.fix.String());
    Print(gps.gga.sats);
    setCursor(0,8);
    Print(gps.gga.utc);
    setCursor(0,16);
    Print("hdop", gps.gga.hdop);
    setCursor(0,24);
    Print(gps.gga.msl);
    if (loc) {
        Print(gps.gga.lat, gps.gga.lon);
        return;
    } // if
    setCursor(0,32);
    Print(gps.gga.geoid);
    if (!gps.gga.age.IsValid()) {
        return;
    } // if
    char line[12];
    ::sprintf(line, "%5.1f %04d",
              gps.gga.age.Value(), gps.gga.id.Value());
    setCursor(0,40);
    print(line);
} // Screen::ShowGGA()

void Screen::ShowGLL() {
    setCursor(0,0);
    print("GLL");
    Print(&gps.gll.status,gps.gll.valid);
    setCursor(0,16);
    Print(gps.gll.utc);
    Print(gps.gll.lat, gps.gll.lon);
} // Screen::ShowGLL()

void Screen::ShowGSA(bool sats) {
    setCursor(0,0);
    print("GSA");
    setCursor(40,0);
    write(gps.gsa.automatic.Char());
    setCursor(52,0);
    print(gps.gsa.fix.String());
    if (!sats) {
        setCursor(0,24);
        Print("pdop", gps.gsa.pdop);
        setCursor(0,32);
        Print("hdop", gps.gsa.hdop);
        setCursor(0,40);
        Print("vdop", gps.gsa.vdop);
        return;
    } // if
    for (unsigned row=0;
            row<3;
            ++row) {
        for (unsigned col=0;
                col<4;
                ++col) {
            const NMEA0183::Byte &b = gps.gsa.sat[row*4+col];
            if (b.IsValid()) {
                char line[4];
                ::sprintf(line, "%2d", b.Value());
                setCursor(col*16+4,(row+2)*8);
                print(line);
            } // if
        } // for
    } // for
} // Screen::ShowGSA()

void Screen::ShowGSV(unsigned sat) {
    setCursor(0,0);
    print("GSV");
    print(sat/4 + 1);
    Print(gps.gsv.inView);
    for (unsigned row=2;
            row<6;
            ++row) {
        Print(gps.gsv.sat[sat++],row*8);
    } // for
} // Screen::ShowGSV(sat)

void Screen::ShowRMC(bool loc) {
    setCursor(0,0);
    print("RMC");
    write(loc ? '1' : '2');
    Print(&gps.rmc.status, gps.rmc.valid);
    setCursor(0,8);
    Print(gps.rmc.date);
    setCursor(0,16);
    Print(gps.rmc.utc);
    if (loc) {
        Print(gps.rmc.lat, gps.rmc.lon);
        return;
    } // if
    setCursor(0,24);
    Print(gps.rmc.speed, "Kts");
    setCursor(0,32);
    Print(gps.rmc.course, "True");
    setCursor(0,40);
    Print(gps.rmc.var, gps.rmc.magnetic);
} // Screen::ShowRMC(latLon)

void Screen::ShowVTG() {
    setCursor(0,0);
    print("VTG");
    Print(0, gps.vtg.valid);

    setCursor(0,8);
    Print(gps.vtg.trueCourse, gps.vtg.t);
    setCursor(0,16);
    Print(gps.vtg.magCourse, gps.vtg.m);
    setCursor(0,24);
    Print(gps.vtg.knots, gps.vtg.n);
    setCursor(0,32);
    Print(gps.vtg.kph, gps.vtg.k);
} // Screen::ShowVTG()

void Screen::ShowDiag1() {
    setCursor(0,0);
    print("Diagnostics");

    setCursor(0,8);
    print("INV");
    setCursor(19,8);
    print(msg[GP20U7::INV_Invalid]);

    setCursor(0,16);
    print("CHK");
    setCursor(19,16);
    print(msg[GP20U7::CHK_Checksum]);

    setCursor(0,24);
    print("UNK");
    setCursor(19,24);
    print(msg[GP20U7::XXX_Unknown]);

    setCursor(0,40);
    print("TOT");
    setCursor(19,40);
    print(total);
} // Screen::ShowDiag1()

void Screen::ShowDiag2() {
    static const char name[][4] = { "GGA", "GLL", "GSA", "GSV", "RMC", "VTG" };
    char line[16];
    for (unsigned row = 0;
            row < 6;
            ++row) {
        setCursor(0,row*8);
        print(name[row]);
        ::sprintf(line, "%1d/%5d",
                  msg[(GP20U7::Messages)(GP20U7::GGA_Invalid+row)],
                  msg[(GP20U7::Messages)(GP20U7::GGA_FixedData+row)]
                 );
        setCursor(19,row*8);
        print(line);
    } // for
} // Screen::ShowDiag2()

void Screen::Print(const NMEA0183::Byte &sats) {
    setCursor(48,0);
    write('#');
    setCursor(53,0);
    print(sats.Value());
} // Screen::Print(sats)

void Screen::Print(const NMEA0183::Bool *status, const NMEA0183::Bool &valid) {
    if (status!=0) {
        setCursor(54,0);
        write(status->Char());
    } // if
    setCursor(59,0);
    write(valid.Char());
} // Screen::Print(status,valid)

void Screen::Print(const NMEA0183::Real &value, const NMEA0183::Char &c) {
    char line[12] = "     .    ";
    if (value.IsValid()) {
        ::sprintf(line, "%9.03f%c",
                  value.Value(), c.Value()
                 );
    } // if
    print(line);
} // Screen::Print(Real, Char)

void Screen::Print(const char *string,
                   const NMEA0183::Real &value) {
    char line[12] = "   .  ";
    if (value.IsValid()) {
        ::sprintf(line, "%7.02f", value.Value());
    } // if
    print(string);
    print(line);
} // Screen::Print(string, Real)

void Screen::Print(const NMEA0183::Real &value,
                   const char *string) {
    char line[12] = "   .  ";
    if (value.IsValid()) {
        ::sprintf(line, "%7.02f", value.Value());
    } // if
    print(line);
    print(string);
} // Screen::Print(Real, string)

void Screen::Print(const NMEA0183::Lat &lat, const NMEA0183::Lon &lon) {
    Print(lat,32);
    Print(lon,40);
} // Screen::Print(Lat,Lon)

void Screen::Print(const NMEA0183::Date &date) {
    static const char months[][4] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun",
                                      "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };
    char line[12];
    if (!date.IsValid()) {
        if (metric) {
            ::sprintf(line, "  /   /  ");
        } // if
        else {
            ::sprintf(line, "   /  /  ");
        } // else
    } // if
    else {
        if (metric) {
            ::sprintf(line,"%2d/%3s/%02d",date.day,months[date.month-1],date.year);
        } // if
        else {
            ::sprintf(line,"%3s/%2d/%02d",months[date.month-1],date.day,date.year);
        } // else
    } // else
    print(line);
} // Screen::Print(Date)

void Screen::Print(const NMEA0183::UTC &utc) {
    char line[12] = "  :  :  . ";
    if (utc.IsValid()) {
        int sec = (int)utc.sec;
        int frac = (int)((utc.sec - sec)*10);
        ::sprintf(line,"%2d:%02d:%02d.%1d",
                  utc.hour, utc.min, sec, frac
                 );
    } // if
    print(line);
} // Screen::Print(UTC)

void Screen::Print(const NMEA0183::Lat &lat, unsigned y) {
    char deg[8] = "  ";
    char min[8] = "  ";
    char sec[8] = "  ";
    if (lat.IsValid()) {
        int mins = (int)lat.minutes;
        int secs = (int)((lat.minutes - mins) * 60);
        ::sprintf(deg, "%2d", lat.degrees.Value());
        ::sprintf(min, "%2d", mins);
        ::sprintf(sec, "%2d", secs);
    } // if
    setCursor(6, y);
    print(deg);
    setCursor(17, y);
    write(degree);
    write(lat.north.Char());
    print(min);
    setCursor(40, y);
    write('\'');
    print(sec);
    setCursor(57, y);
    write('"');
} // Screen::Print(Lat,y)

void Screen::Print(const NMEA0183::Lon &lon, unsigned y) {
    char deg[8] = "  ";
    char min[8] = "  ";
    char sec[8] = "  ";
    if (lon.IsValid()) {
        int mins = (int)lon.minutes;
        int secs = (int)((lon.minutes - mins) * 60);
        ::sprintf(deg, "%3d", lon.degrees.Value());
        ::sprintf(min, "%2d", mins);
        ::sprintf(sec, "%2d", secs);
    } // if
    setCursor(0, y);
    print(deg);
    setCursor(17, y);
    write(degree);
    write(lon.east.Char());
    print(min);
    setCursor(40, y);
    write('\'');
    print(sec);
    setCursor(57, y);
    write('"');
} // Screen::Print(Lon,y)

void Screen::Print(const NMEA0183::Alt &alt) {
    char line[12] = "     . m";
    if (alt.IsValid()) {
        int val = (int)alt.alt;
        int frac = (int)((alt.alt - val) * 10);
        char c = alt.metres ? 'm' : '\'';
        ::sprintf(line, "%5d.%1d%c",
                  val, frac, c
                 );
    } // if
    print(line);
} // Screen::Print(Alt)

void Screen::Print(const NMEA0183::Sat &sat, unsigned y) {
    if (sat.IsValid()) {
        char num[3];
        ::sprintf(num, "%2d", sat.id.Value() );
        setCursor(0,y);
        print(num);
    } // if
    pixel(12,y+2);
    pixel(12,y+5);

    char el[8] = "  ";
    char az[8] = "   ";
    char snr[8] = "  ";
    if (sat.IsValid()) {
        ::sprintf(el, "%02d", sat.el.Value());
        ::sprintf(az, "%03d", sat.az.Value());
        ::sprintf(snr, "%2d", sat.snr.Value());
    } // if
    setCursor(14,y);
    print(el);
    setCursor(25,y);
    write(degree);
    setCursor(30,y);
    print(az);
    setCursor(47,y);
    write(degree);
    setCursor(52,y);
    print(snr);
} // Screen::Print(Sat,y)

Screen::~Screen() {
    invert(false);
    Clear();
} // Screen::~Screen()
