#include <sparklibs.h>
#include <oled/Edison_OLED.h>

#include <Button/Button.h>

Button::A     nextFont;
Button::B     quit;
Button::Up    prevRow;
Button::Down  nextRow;
Button::Left  prevChar;
Button::Right nextChar;

edOLED display;      // The actual OLED display instance
unsigned char start; // Current first char on display

unsigned char MinChar; // First char in font
unsigned char MaxChar; // Last char in font
unsigned CharWidth;    // Width of each char in font
unsigned CharHeight;   // Height of each char in font
unsigned CharsInRow;   // Calculation of chars in row (accounting for possible Hex display)
unsigned Rows;         // Calculation of number of rows
bool ShowHex;          // Whether to show Hex at start

bool finished;       // Can I quit now?

// Call this to configure the buttons:
// * Initial delay and repeat rates
void InitButtons() {
    Button::Configure(400,100); // 400 ms initial, 100 ms repeat
} // InitButtons()

// Call this to initialise the screen.
void InitScreen() {
    display.begin();        // Use display
} // InitScreen()

// Set font, and calculate font variables
void SetFont(unsigned char font) {
    display.setFontType(font); // Start with first font
    MinChar = display.getFontStartChar();                 // Get first char in font
    MaxChar = MinChar + (display.getFontTotalChar() - 1); // Calculate last char in font
    CharWidth = display.getFontWidth();                   // Get char width
    CharHeight = display.getFontHeight();                 // Get char height
    CharsInRow = LCDWIDTH / CharWidth;         // Calculate chars in row
    Rows = LCDHEIGHT / CharHeight;             // Calculate number of rows
    ShowHex = (CharHeight<=LCDHEIGHT/3) &&     // If two Hex digits will fit...
              (MinChar<='0') &&                // ...and there are digits...
              (MaxChar>='F');                  // ...and Hex digits...
    if (ShowHex) {
        --CharsInRow;                          // ...make room for Hex on display
    } // if
    start = MinChar;   // Reset start to first char in font
} // InitFont()

// When Button::A is Pressed(), choose next font
int Button::A::Pressed() const {
    static int font = 0; // Starting font

    ++font;              // Next font
    if (font >= display.getTotalFonts()) { // Too far?
        font = 0;              // Start again
    } // if
    SetFont(font); // Set font, and recalculate variables
    return font;
} // A::Pressed()

// When Button B is Pressed(), quit
int Button::B::Pressed() const {
    finished = true;
    return 0;
} // B::Pressed()

// When Button Up is Pressed(), start up one row
int Button::Up::Pressed() const {
    if (start>=MinChar + CharsInRow) {
        start -= CharsInRow;
    } // if
    else {
        start = MinChar;
    } // else
    return start;
} // Up::Pressed()

// When Button Down is Pressed(), start down one row
int Button::Down::Pressed() const {
    if (start<=MaxChar-CharsInRow) {
        start += CharsInRow;
    } // if
    return start;
} // Down::Pressed()

// When Button Left is Pressed(), start at previous character
int Button::Left::Pressed() const {
    if (start>MinChar) {
        --start;
    } // if
    return start;
} // Left::Pressed()

// When Button Right is Pressed(), start at next character
int Button::Right::Pressed() const {
    if (start<MaxChar) {
        ++start;
    } // if
    return start;
} // Right::Pressed()

// Return char representing hex of value
inline char Hex(uint8_t value) {
    return value>9 ?
           ('A' + value - 10) :
           ('0' + value);
} // Hex(value)

// Something changed. Show entire page again
void ShowPage() {
    display.clear(PAGE);

    unsigned char c = start;   // Starting char to display
    unsigned startCol = 0;     // Assume no Hex to show
    if (ShowHex) {
        display.drawChar(0, CharHeight * 1/2,
                         Hex((c>>4) & 0xF),
                         BLACK, NORM);
        display.drawChar(0, CharHeight * 3/2,
                         Hex((c>>0) & 0xF),
                         BLACK, NORM);
        startCol = CharWidth * 3/2;          // Leave room for Hex
        display.setColor(WHITE);
    } // for

    for (unsigned row=0;                   // Run through rows
            row <= LCDHEIGHT-CharHeight;
            row += CharHeight) {
        for (unsigned col=startCol;        // Run through columns
                col <= LCDWIDTH-CharWidth;
                col += CharWidth) {
            display.drawChar(col, row, c);
            if (c++ == MaxChar) {          // Next character
                display.display();
                return;                    // Too far?
            } // if
        } // for
    } // for
    display.display();
} // ShowPage()

// Clean up screen on exit
void DoneScreen() {
    display.clear(PAGE);
    display.display();
} // DoneScreen()

// Entry point
int main() {
    InitButtons();
    InitScreen();
    SetFont(0);
    while (!finished) {
        ShowPage();       // Show screen
        Button::Get(50);  // Wait for Button, checking every 50 ms
    } // for
    DoneScreen();
    return 0;
} // main()
