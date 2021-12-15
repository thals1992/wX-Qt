// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef OBJECTCOLORPALETTE_H
#define OBJECTCOLORPALETTE_H

#include <memory>
#include <QHash>
#include <QString>
#include "objects/MemoryBuffer.h"
#include "radarcolorpalette/ObjectColorPaletteLine.h"

class ObjectColorPalette {
public:
    explicit ObjectColorPalette(int);
    void initialize();
    void putInt(int);
    void putBytesViaBytes(unsigned char, unsigned char, unsigned char);
    void putBytes(const ObjectColorPaletteLine&);
    void putLine(const QString&);
    void position(int);
    static void loadColorMap(int);
    static void refreshPref();
    std::unique_ptr<MemoryBuffer> redValues;
    std::unique_ptr<MemoryBuffer> greenValues;
    std::unique_ptr<MemoryBuffer> blueValues;
    static QHash<int, QString> radarColorPalette;
    static QHash<int, ObjectColorPalette *> colorMap;

private:
    void setupBuffers(int);
    static void generate(int, const QString&);
    static void generate4bitGeneric(int);
    static void loadColorMap165();
    int colorMapCode;
};

#endif  // OBJECTCOLORPALETTE_H
