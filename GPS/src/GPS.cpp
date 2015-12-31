#include <GPS/GP20U7.h>
#include <uart/uart.h>

#include <Button/Button.h>
#include "Screen.h"

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

int main() {
    uart.Configure(9600);       // Configure the UART as 9600 baud, raw mode
    Button::Configure(400,100); // 400 ms initial delay, 100 ms repeat
    while (!finished) {
        bool wait = true;    // Only wait if nothing happened
        bool update = false; // Only update if something changed

        char line[256];
        if (uart.ReadLine(line, sizeof line)) { // Read line from UART
            if (!frozen) {                             // If not frozen
                GP20U7::Messages message = gps.Decode(line); // Decode with GPS
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
} // main()
