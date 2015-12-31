//
// Button.h
//

#ifndef Button_h
#define Button_h

#include <stdint.h>

#include "../gpio/gpio.h"

// This is the base Button class.
// Note the class definitions inside for the Buttons as used on the OLED Block.
// The only function missing for these actual Buttons is their Pressed() method - see BUTTON macro below.
// So if you instantiate any of these Buttons, you'll need to also provide its Pressed() method.
class Button : protected gpio {

public: // Classes

    // 1) Instantiate any of these classes: e.g.
    //      Button::B quit;
    // 2) Write the corresponding Button::XXX::Pressed() method: e.g.
    //      int Button::B::Pressed() const {
    //          finished = true;
    //          return 0;
    //      } // B::Pressed()
    class A;
    class B;
    class Up;
    class Down;
    class Left;
    class Right;
    class Select;

public: // Static functions

    // If two consecutive Poll() calls detect the same button, the second call will return NULL;
    // If a button is detected as held down for 'initial' ms, re-report it instead of NULL.
    // If after that the button is still held down, every 'repeat' ms re-report it.
    // This method also initialises the CLOCK.
    static void Configure(unsigned initial, unsigned repeat);

    // Poll all buttons.
    // If none are pressed, return NULL.
    // Otherwise, return the detected button: don't forget to call its Pressed()!
    static Button *Poll();

    // Implementation of a Wait for ms
    static void Wait(unsigned ms);

    // Call Poll() above UNTIL a Button IsPress()ed, waiting ms milliseconds between Poll()s.
    // Return Button's Pressed() result
    static int Get(unsigned ms);

public: // Methods

    // Is this Button Pressed?
    bool IsPressed();

public: // Hooks

    // Override this to implement what happens
    // Your code can interpret the returned value.
    virtual int Pressed() const = 0;

protected: // Enums

    // These are the gpio inputs used on the OLED display
    enum Pins {
        APin = 49,
        BPin = 46,
        UpPin = 47,
        DownPin = 44,
        LeftPin = 165,
        RightPin = 45,
        SelectPin = 48
    }; // Pins

protected: // Methods

    // Construct a Button on Pin
    explicit Button(Pins pin);

private: // Variables

    // Next Button in list
    Button *next;

    // Time this button was pressed (in ms), for auto-repeat
    uint64_t pressed;

    // Number of times reported held down
    unsigned held;

private: // Static variables

    // Head of list of Buttons
    static Button *head;

    // Number of ms to wait before auto-repeat
    static unsigned initial;

    // Number of ms to wait after auto-repeat starts
    static unsigned repeat;

}; // Button

// Derived Button classes only need:
// * A constructor to define the Pin;
// * A derived Pressed() function, to implement the pure virtual base.
// So here's a helper macro, using preprocessor macro magic.
#define BUTTON(NAME)                      \
    class Button::NAME : public Button {  \
    public: /* Methods */                 \
        inline NAME():Button(NAME##Pin){} \
    private: /* Overrides */              \
        virtual int Pressed() const;      \
    } // Button::NAME

BUTTON(A);
BUTTON(B);
BUTTON(Up);
BUTTON(Down);
BUTTON(Left);
BUTTON(Right);
BUTTON(Select);

#endif // Button_h
