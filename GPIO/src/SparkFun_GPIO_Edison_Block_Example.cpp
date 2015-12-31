  /****************************************************************
  Example file for SparkFun GPIO Edison Block Support

  14 Jul 2015- Mike Hord, SparkFun Electronics
  Code developed in Intel's Eclipse IOT-DK

  This code requires the Intel mraa library to function; for more
  information see https://github.com/intel-iot-devkit/mraa

  This code is beerware; if you use it, please buy me (or any other
  SparkFun employee) a cold beverage next time you run into one of
  us at the local.
  ****************************************************************/

#include "mraa.hpp"

#include <iostream>
#include <unistd.h>

using namespace mraa;
using namespace std;

int main()
{

  // Oddly, GPIO pin assignment numbers when using the MRAA libraries are not
  //  the same as those inside the operating system. Thus, while we're using
  //  pin 14 as far as the OS is concerned to drive the LED, we're using pin 36
  //  as far as MRAA is concerned. The cheat sheet for that can be found here:
  //  https://github.com/intel-iot-devkit/mraa/blob/master/docs/edison.md
  Gpio LEDPin(36);
  LEDPin.dir(DIR_OUT);

  // Now do a quick little flicker.
  LEDPin.write(0);
  usleep(100000);
  LEDPin.write(1);
  usleep(100000);
  LEDPin.write(0);

	// Alternatively, we can declare the pin in "raw" mode, which has a slightly
  //  different and more unwieldy constructor.
	Gpio buttonPin(15, true, true);
	buttonPin.dir(DIR_IN);

	// In this infinite loop, we'll blink the LED once whenever someone presses
	//  the button.
	while (1)
	{
    // We *know* that if the IO pin reads as 0, or is low, read() returns zero.
    //  However, if it's high, it *may* return something else; the only guarantee
    //  is that it will be nonzero. Thus, *don't test to see if a read() returned
    //  a 1!!!
    if (buttonPin.read() == 0)
    {
      LEDPin.write(1);
      sleep(1);
      LEDPin.write(0);
      sleep(1);
    }
	}

	return MRAA_SUCCESS;
}
