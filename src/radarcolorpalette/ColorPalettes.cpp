// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "radarcolorpalette/ColorPalettes.h"
#include <vector>
#include "radarcolorpalette/ObjectColorPalette.h"
#include "util/UtilityList.h"

using std::vector;

void ColorPalettes::initialize() {
    ObjectColorPalette::refreshPref();
    ObjectColorPalette::colorMap[94] = new ObjectColorPalette{94};
    ObjectColorPalette::colorMap[94]->initialize();
    ObjectColorPalette::colorMap[99] = new ObjectColorPalette{99};
    ObjectColorPalette::colorMap[99]->initialize();
    ObjectColorPalette::colorMap[153] = ObjectColorPalette::colorMap[94];
    ObjectColorPalette::colorMap[180] = ObjectColorPalette::colorMap[94];
    ObjectColorPalette::colorMap[186] = ObjectColorPalette::colorMap[94];
    ObjectColorPalette::colorMap[154] = ObjectColorPalette::colorMap[99];
    ObjectColorPalette::colorMap[182] = ObjectColorPalette::colorMap[99];
    ObjectColorPalette::colorMap[172] = new ObjectColorPalette{172};
    ObjectColorPalette::colorMap[172]->initialize();
    ObjectColorPalette::colorMap[170] = ObjectColorPalette::colorMap[172];
    for (auto it : {19, 30, 56, 134, 135, 159, 161, 163, 165}) {
        ObjectColorPalette::colorMap[it] = new ObjectColorPalette{it};
        ObjectColorPalette::colorMap[it]->initialize();
    }
    ObjectColorPalette::colorMap[37] = ObjectColorPalette::colorMap[19];
    ObjectColorPalette::colorMap[38] = ObjectColorPalette::colorMap[19];
}
