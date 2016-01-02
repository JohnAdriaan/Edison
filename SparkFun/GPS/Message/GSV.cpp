/*
 * GSV.cpp
 *
 *   Author: John Burger
 *   This code is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *   GNU General Public License for more details.
 */

#include "GSV.h"

using namespace NMEA0183;

GSV::GSV() :
     Message(),
     inView(2, 0, Sat::MaxSats),
     sat(),
     msg(1, 1, 9),
     num(1, 1, 9),
     tmpNum(),
     tmpInView(2, 0, Sat::MaxSats),
     index() {
} // GSV::GSV(num, max)

bool GSV::Match(const char *&line) {
    return Message::Match(line, "GSV");
} // GSV::Match(line)

void GSV::Clear(bool all) {
    Message::Clear();
    if (all) {
       inView.Clear();
    } // all
    for (byte i=inView.IsValid() ? inView : 0u;
            i<Sat::MaxChannels;
            ++i) {
        sat[i].Clear();
    } // for
    // Don't clear these - they're for housekeeping
    // msg.Clear();
    // num.Clear();
    tmpNum = 0;
    tmpInView.Clear();
    index = 0;
} // GSV::Clear(all)

bool GSV::Decode(const char *line) {
    if (!num.Decode(line)) {
        Clear(true);
        return false;
    } // if
    if (!msg.Decode(line)) {
        Clear(true);
        return false;
    } // if
    if (msg==1) { // Starting from scratch?
        Clear(false);
        if (!inView.Decode(line)) {
            return false;
        } // if
        tmpNum = num;
    } // if
    else {
        if (num != tmpNum) {
            return false;
        } // if
        if (msg > num) {
            return false;
        } // if
        if (!tmpInView.Decode(line)) {
            return false;
        } // if
        if (tmpInView != inView) {
            return false;
        } // if
    } // else
    while (*line!='*') {
        if (index >= Sat::MaxChannels) {
            return false;
        } // if
        if (!sat[index++].Decode(line)) {
            return false;
        } // if
    } // while
    if (!Message::Decode(line)) {
        return false;
    } // if
    valid = true;
    return true;
} // GSV::Decode(line)
