#ifndef _INCLUDE_JUCESUBSTITITION_
#define _INCLUDE_JUCESUBSTITITION_

#include <string>

/*
** We don't want to couple to Juce. Most of the work is making it so we don't have to
** but in some cases its easier just to stub up the minimum we need which is what this file does
**
** Ideally this ends up empty when we are done.
*/

struct InputStream {
    virtual void read(char* data, size_t size);

    virtual int readInt();
    virtual short readShort();
    virtual char readByte();

    virtual int64_t getPosition();
    virtual void setPosition(int64_t);
};

struct FileInputStream : public InputStream {
};

struct AudioSampleBuffer {
};

// Type aliases
typedef int64_t int64;
typedef std::string String;

#endif
