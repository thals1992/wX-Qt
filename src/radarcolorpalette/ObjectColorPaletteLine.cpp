// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "radarcolorpalette/ObjectColorPaletteLine.h"
#include "objects/Color.h"
#include "util/To.h"

ObjectColorPaletteLine::ObjectColorPaletteLine() {
}

ObjectColorPaletteLine::ObjectColorPaletteLine(const QStringList& stringList) {
    dbz = To::Int(stringList[1]);
    red = To::Int(stringList[2]);
    green = To::Int(stringList[3]);
    blue = To::Int(stringList[4]);
}

ObjectColorPaletteLine::ObjectColorPaletteLine(int d, const QString& r, const QString& g, const QString& b) {
    dbz = d;
    red = To::Int(r);
    green = To::Int(g);
    blue = To::Int(b);
}

int ObjectColorPaletteLine::asInt() const {
    return Color::rgb(red, green, blue);
}
