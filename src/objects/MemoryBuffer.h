// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef MEMORYBUFFER_H
#define MEMORYBUFFER_H

#include <QByteArray>
#include <cstdint>
#include <memory>

class MemoryBuffer {
public:
    MemoryBuffer();
    explicit MemoryBuffer(int);
    explicit MemoryBuffer(const QByteArray &);
    MemoryBuffer(char *, int);
    void mark(int);
    void mark();
    void reset();
    int getCapacity() const;
    int getPosition() const;
    void setPosition(int);
    float getFloat();
    float getFloat(int) const;
    float getFloatNative();
    float getFloatNative(int) const;
    void putFloat(float);
    void putByte(unsigned char);
    void put(unsigned char);
    void putInt(int);
    void putSignedShort(int16_t);
    int16_t getShort();
    int16_t getShortNative();
    uint16_t getUnsignedShort();
    int getInt();
    unsigned char get();
    unsigned char get(int) const;
    unsigned char getByIndex(int) const;
    void skipBytes(int);
    bool eof() const;
    QByteArray qbyteArray;

private:
    int position;
    int markPosition;
    int capacity;
};

#endif  // MEMORYBUFFER_H
