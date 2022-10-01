// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef OBJECTCOLORPALETTE_H
#define OBJECTCOLORPALETTE_H

#include <memory>
#include <unordered_map>
#include <vector>
#include "objects/MemoryBuffer.h"
#include "radarcolorpalette/ObjectColorPaletteLine.h"

using std::unordered_map;
using std::vector;

class ObjectColorPalette {
public:
    explicit ObjectColorPalette(int);
    void initialize();
    void putBytesViaBytes(unsigned char, unsigned char, unsigned char) const;
    void putBytes(const ObjectColorPaletteLine&) const;
    void putLine(const string&) const;
    void putBytesFromLine(const ObjectColorPaletteLine&) const;
    void putVector(const vector<double>&) const;
    void position(int) const;
    static void loadColorMap(int);
    static void refreshPref();
    std::unique_ptr<MemoryBuffer> redValues;
    std::unique_ptr<MemoryBuffer> greenValues;
    std::unique_ptr<MemoryBuffer> blueValues;
    static unordered_map<int, string> radarColorPalette;
    static unordered_map<int, ObjectColorPalette *> colorMap;

private:
    void setupBuffers(int);
    static void generate(int, const string&);
    static void generate4bitGeneric(int);
    static void loadColorMap165();
    int colorMapCode;
};

#endif  // OBJECTCOLORPALETTE_H
