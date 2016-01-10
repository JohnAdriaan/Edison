/*
 * Mode.cpp
 *
 *   Author: John Burger
 *   This code is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *   GNU General Public License for more details.
 */

#include "Mode.h"

using namespace NMEA0183;

const char * const modes[] = { "None",
                               "Auto",
                               "DGPS",
                               "D.R.", // Dead Reckoning
                               0 };

Mode::Mode() :
      Strings("NADE", modes) {
} // Mode::Mode()
