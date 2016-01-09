/*
 * GPS.cpp
 *
 *   Author: John Burger
 *   This code is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *   GNU General Public License for more details.
 */

#include <GPS/GP20U7.h>
#include <File/File.h>
#include <uart/uart.h>
#include <Button/Button.h>

#include "Screen.h"

const char *fileName[GP20U7::GP20U7_Last] = {
        "INV.txt", "CHK.txt", "UNK.txt",

        "GGA.txt", "GLL.txt", "GSA.txt",
        "GSV.txt", "RMC.txt", "VTG.txt",

        "GGA.Inv.txt", "GLL.Inv.txt", "GSA.Inv.txt",
        "GSV.Inv.txt", "RMC.Inv.txt", "VTG.Inv.txt"
}; // filename

Button::A     freeze;
Button::B     quit;
Button::Up    prevScreen;
Button::Down  nextScreen;
Button::Left  leftScreen;
Button::Right rightScreen;

GP20U7 gps; // Decode and store values

Screen screen(gps);

edUART uart(edUART::UART1);

bool frozen = false; // Freeze current values?

bool finished = false;

int Button::A::Pressed() const {
    frozen = !frozen;
    screen.invert(frozen); // Show we're frozen (or not!)
    return 0; // Nothing to update
} // A::Pressed()

int Button::B::Pressed() const {
    finished = true;
    return 0; // Nothing to update
} // B::Pressed()

int Button::Up::Pressed() const {
    return screen.Prev();
} // Up::Pressed()

int Button::Down::Pressed() const {
    return screen.Next();
} // Down::Pressed()

int Button::Left::Pressed() const {
    return screen.Left();
} // Left::Pressed()

int Button::Right::Pressed() const {
    return screen.Right();
} // Right::Pressed()

int main(int argc, char *argv[]) {
    File dump;
    File msgFile[GP20U7::GP20U7_Last];

    if (argc>1) { // Any parameter at all?
        dump.Open("Dump.txt", File::Truncate, File::WriteOnly);
        for (unsigned msg = 0;
             msg<GP20U7::GP20U7_Last;
             ++msg) {
            msgFile[msg].Open(fileName[msg], File::Truncate, File::WriteOnly);
        } // for
    } // if

    uart.Configure(9600);       // Configure the UART as 9600 baud, raw mode
    Button::Configure(400,100); // 400 ms initial delay, 100 ms repeat
    while (!finished) {
        bool wait = true;    // Only wait if nothing happened
        bool update = false; // Only update if something changed

        char line[256];
        unsigned length = uart.ReadLine(line, sizeof line); // Read line from UART
        if (length>0) {
            dump.Write(line, length);
            if (!frozen) {                             // If not frozen
                GP20U7::Messages message = gps.Decode(line); // Decode with GPS
                if (message<GP20U7::GP20U7_Last) {
                    msgFile[message].Write(line, length);
                } // if
                update = screen.Received(message);           // Anything to update?
            } // if
            wait = false; // Either way, don't wait to process potential new line!
        } // if

        Button *button = Button::Poll(); // Poll for Button press
        if (button!=0) {                 // Was there one?
            if (button->Pressed()!=0) {  // Yes, but Pressed() may not actually do anything...
                update = true;           // ...but it did!
            } // if
        } // if

        // Updating the screen is VERY CPU-intensive,
        // so it's worth monitoring whether anything needs updating.
        // If not, don't!
        if (update) {
            screen.Show(); // Something updated, so Show() it
        } // if

        if (wait) {
            Button::Wait(50); // Nothing happened, so wait a bit
        } // if
    } // while
    return 0;
} // main(argc, argv[])
