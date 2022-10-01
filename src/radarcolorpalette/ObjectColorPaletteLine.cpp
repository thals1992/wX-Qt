// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "radarcolorpalette/ObjectColorPaletteLine.h"
#include "util/To.h"

ObjectColorPaletteLine::ObjectColorPaletteLine(const vector<string>& items)
    : dbz{ To::Int(items[1]) }
    , red{ To::Int(items[2]) }
    , green{ To::Int(items[3]) }
    , blue{ To::Int(items[4]) }
{}

ObjectColorPaletteLine::ObjectColorPaletteLine(int d, const string& r, const string& g, const string& b)
    : dbz{ d }
    , red{ To::Int(r) }
    , green{ To::Int(g) }
    , blue{ To::Int(b) }
{}

vector<double> ObjectColorPaletteLine::asVector() const {
    return {red / 255.0, green / 255.0, blue / 255.0};
}
