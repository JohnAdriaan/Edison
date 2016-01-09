/*
 * File.cpp
 *
 *   Author: John Burger
 *   This code is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *   GNU General Public License for more details.
 */

#include <unistd.h>
#include <errno.h>
#include <fcntl.h>

#include "File.h"

File::File() :
      handle(Invalid) {
} // File::File()

File::File(File &file) :
      handle(file.handle) {
    file.handle = Invalid;
} // File::File(file)

File::File(const char *name,
           Modes mode,
           Accesses access,
           int permissions) :
      handle(Invalid) {
    Open(name, mode, access, permissions);
} // File::File(name, mode, access, permissions)

File &File::operator =(const File &file) {
    if (handle!=file.handle) {
        handle = file.handle;
        file.handle = Invalid;
    } // if
    return *this;
} // File::operator =(File)

bool File::Open(const char *name,
                Modes mode,
                Accesses access,
                int permissions) {
    int oflag = 0;
    switch (mode) {
    case CreateOpen :
        oflag |= O_CREAT;
        break;
    case CreateNew :
        oflag |= O_CREAT | O_EXCL;
        break;
    case Truncate :
        oflag |= O_CREAT | O_TRUNC;
        break;
    case Exists :
        oflag |= 0;
        break;
    } // switch
    switch (access) {
    case ReadOnly :
        oflag |= O_RDONLY;
        break;
    case WriteOnly :
        oflag |= O_WRONLY;
        break;
    case ReadWrite :
        oflag |= O_RDWR;
        break;
    } // switch
    handle = ::open(name, oflag, permissions);
    return Valid();
} // File::File(name, mode, access, permissions)

bool File::Write(const void *data,
                 unsigned size) {
    if (!Valid()) {
        return false;
    } // if
    ssize_t result = ::write(handle, data, size);
    return result==(ssize_t)size;
} // File::Write(data, size)

bool File::Read(void *data, unsigned size, unsigned &read) {
    if (!Valid()) {
        return false;
    } // if
    ssize_t result = ::read(handle, data, size);
    if (result==-1) {
        if ((errno!=EAGAIN) &&
            (errno!=EWOULDBLOCK)) {
            return false;
        } // if
        result = 0;
    } // if
    read = result;
    return true;
} // File::Read(data, size, read)

void File::Close() {
    if (!Valid()) {
        return;
    } // if
    int temp = handle;
    handle = Invalid;
    ::close(temp);
} // File::Close()

File::~File() {
    Close();
} // File::~File()
