// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "objects/MemoryBuffer.h"
#include <iostream>

MemoryBuffer::MemoryBuffer() {
    capacity = 0;
    position = 0;
    markPosition = 0;
    qbyteArray = QByteArray(0, '0');
}

MemoryBuffer::MemoryBuffer(int count) {
    capacity = count;
    position = 0;
    markPosition = 0;
    qbyteArray = QByteArray(count, '0');
}

MemoryBuffer::MemoryBuffer(const QByteArray& qarray) {
    qbyteArray = QByteArray(qarray);
    capacity = qbyteArray.size();
    position = 0;
    markPosition = 0;
}

MemoryBuffer::MemoryBuffer(char * d, int size) {
    qbyteArray = QByteArray(d, size);
    capacity = qbyteArray.size();
    position = 0;
    markPosition = 0;
}

void MemoryBuffer::mark(int markAt) {
    markPosition = position;
    position = markAt;
}

void MemoryBuffer::mark() {
    markPosition = position;
}

void MemoryBuffer::reset() {
    position = markPosition;
}

int MemoryBuffer::getCapacity() const {
    return capacity;
}

int MemoryBuffer::getPosition() const {
    return position;
}

void MemoryBuffer::setPosition(int posn) {
    position = posn;
}

void MemoryBuffer::skipBytes(int count) {
    position += count;
}

bool MemoryBuffer::eof() const {
    if (position < (getCapacity() - 1))
        return false;
    else
        return true;
}

float MemoryBuffer::getFloat() {
//    float f;
//    uchar b[] = {b3, b2, b1, b0};
//    memcpy(&f, &b, sizeof(f));
//    return f;
    union {
        float f;
        uchar b[4];
    } u;
    u.b[3] = qbyteArray.at(position);
    u.b[2] = qbyteArray.at(position + 1);
    u.b[1] = qbyteArray.at(position + 2);
    u.b[0] = qbyteArray.at(position + 3);
    position += 4;
    return u.f;
}

float MemoryBuffer::getFloat(int index) const {
    union {
        float f;
        uchar b[4];
    } u;
    u.b[3] = qbyteArray.at(index);
    u.b[2] = qbyteArray.at(index + 1);
    u.b[1] = qbyteArray.at(index + 2);
    u.b[0] = qbyteArray.at(index + 3);
    return u.f;
}

float MemoryBuffer::getFloatNative() {
//    float f;
//    uchar b[] = {b3, b2, b1, b0};
//    memcpy(&f, &b, sizeof(f));
//    return f;
    union {
        float f;
        uchar b[4];
    } u;
    u.b[0] = qbyteArray.at(position);
    u.b[1] = qbyteArray.at(position + 1);
    u.b[2] = qbyteArray.at(position + 2);
    u.b[3] = qbyteArray.at(position + 3);
    position += 4;
    return u.f;
}

float MemoryBuffer::getFloatNative(int index) const {
    union {
        float f;
        uchar b[4];
    } u;
    u.b[0] = qbyteArray.at(index);
    u.b[1] = qbyteArray.at(index + 1);
    u.b[2] = qbyteArray.at(index + 2);
    u.b[3] = qbyteArray.at(index + 3);
    return u.f;
}

unsigned char MemoryBuffer::get() {
    position += 1;
    return qbyteArray.at(position - 1);
}

unsigned char MemoryBuffer::get(int index) const {
    return qbyteArray.at(index);
}

unsigned char MemoryBuffer::getByIndex(int index) const {
    return qbyteArray.at(index);
}

void MemoryBuffer::putFloat(float newValue) {
    memcpy(qbyteArray.data() + position, &newValue, sizeof(newValue));
    position += 4;
}

void MemoryBuffer::putByte(unsigned char newValue) {
    memcpy(qbyteArray.data() + position, &newValue, sizeof(newValue));
    position += 1;
}

void MemoryBuffer::put(unsigned char newValue) {
    memcpy(qbyteArray.data() + position, &newValue, sizeof(newValue));
    position += 1;
}

void MemoryBuffer::putInt(int newValue) {
    memcpy(qbyteArray.data() + position, &newValue, sizeof(newValue));
    position += 4;
}

void MemoryBuffer::putSignedShort(int16_t newValue) {
    memcpy(qbyteArray.data() + position, &newValue, sizeof(newValue));
    position += 2;
}

int16_t MemoryBuffer::getShort() {
    union {
        int16_t f;
        uchar b[2];
    } u;
    u.b[1] = qbyteArray.at(position);
    u.b[0] = qbyteArray.at(position + 1);
    position += 2;
    return u.f;
}

int16_t MemoryBuffer::getShortNative() {
    union {
        int16_t f;
        uchar b[2];
    } u;
    u.b[0] = qbyteArray.at(position);
    u.b[1] = qbyteArray.at(position + 1);
    position += 2;
    return u.f;
}

uint16_t MemoryBuffer::getUnsignedShort() {
    union {
        uint16_t f;
        uchar b[2];
    } u;
    u.b[1] = qbyteArray.at(position);
    u.b[0] = qbyteArray.at(position + 1);
    position += 2;
    return u.f;
}

int MemoryBuffer::getInt() {
    union {
        int f;
        uchar b[4];
    } u;
    u.b[3] = qbyteArray.at(position);
    u.b[2] = qbyteArray.at(position + 1);
    u.b[1] = qbyteArray.at(position + 2);
    u.b[0] = qbyteArray.at(position + 3);
    position += 4;
    return u.f;
}

/*
 *Type	Typical Bit Width	Typical Range
char	1byte	-127 to 127 or 0 to 255
unsigned char	1byte	0 to 255
signed char	1byte	-127 to 127
int	4bytes	-2147483648 to 2147483647
unsigned int	4bytes	0 to 4294967295
signed int	4bytes	-2147483648 to 2147483647
short int	2bytes	-32768 to 32767
unsigned short int	2bytes	0 to 65,535
signed short int	2bytes	-32768 to 32767
long int	8bytes	-2,147,483,648 to 2,147,483,647
signed long int	8bytes	same as long int
unsigned long int	8bytes	0 to 18,446,744,073,709,551,615
long long int	8bytes	-(2^63) to (2^63)-1
unsigned long long int	8bytes	0 to 18,446,744,073,709,551,615
float	4bytes
double	8bytes
long double	12bytes
wchar_t	2 or 4 bytes	1 wide character
 * */
