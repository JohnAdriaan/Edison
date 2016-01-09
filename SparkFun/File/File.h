/*
 * File.h
 *
 *   Author: John Burger
 *   This code is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *   GNU General Public License for more details.
 */

#ifndef File_h
#define File_h

#include <sys/stat.h>

class File {

public: // Enums

    enum Modes {
        CreateOpen,  // Open, or create if necessary
        CreateNew,   // Create. Fails if already exists
        Truncate,    // Create, or truncate existing
        Exists       // Open only if exists
    }; // Modes

    enum Accesses {
        ReadOnly,
        WriteOnly,
        ReadWrite
    }; // Accesses

    enum Permissions {
        UserRead  = S_IRUSR,
        UserWrite = S_IWUSR,
        UserExec  = S_IXUSR,
        GroupRead  = S_IRGRP,
        GroupWrite = S_IWGRP,
        GroupExec  = S_IXGRP,
        OtherRead  = S_IROTH,
        OtherWrite = S_IWOTH,
        OtherExec  = S_IXOTH,

        Default = UserRead|UserWrite|GroupRead|OtherRead
    }; // Permissions

public: // Methods

    File();

    // Move constructor. Invalidates passed-in File
    File(File &file);

    explicit File(const char *name,
                  Modes mode=CreateOpen,
                  Accesses access=ReadWrite,
                  int permissions=Default);

    // Move assignment. Invalidates passed-in File
    File &operator =(File &file);

    bool Open(const char *name,
              Modes mode=CreateOpen,
              Accesses access=ReadWrite,
              int permissions=Default);

    inline bool Valid() const;

    bool Write(const void *data,
               unsigned size);

    inline bool Read(void *data,
                     unsigned size);

    bool Read(void *data,
              unsigned size,
              unsigned &read);

    void Close();

    ~File();

private: // Typedefs

    typedef int Handle;

private: // Variables

    Handle handle;

private: // Static variables

    static const Handle Invalid = -1;

}; // File

inline bool File::Valid() const {
    return handle!=Invalid;
} // File::Valid()

inline bool File::Read(void *data, unsigned size) {
    unsigned read;
    return Read(data, size, read) &&
           read==size;
} // File::Read(data, size)

#endif // File_h
