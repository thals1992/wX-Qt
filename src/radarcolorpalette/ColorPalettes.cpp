// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "radarcolorpalette/ColorPalettes.h"
#include <QVector>
#include <iostream>
#include "radarcolorpalette/ObjectColorPalette.h"
#include "util/UtilityList.h"

void ColorPalettes::initialize() {

    ObjectColorPalette::refreshPref();

    auto cm94 = new ObjectColorPalette(94);
    ObjectColorPalette::colorMap[94] = cm94;
    ObjectColorPalette::colorMap[94]->initialize();

    auto cm99 = new ObjectColorPalette(99);
    ObjectColorPalette::colorMap[99] = cm99;
    ObjectColorPalette::colorMap[99]->initialize();

    const QVector<int> colorMapNumbers = {19, 30, 56, 134, 135, 159, 161, 163, 165};

    ObjectColorPalette::colorMap[153] = cm94;
    ObjectColorPalette::colorMap[180] = cm94;
    ObjectColorPalette::colorMap[186] = cm94;

    ObjectColorPalette::colorMap[154] = cm99;
    ObjectColorPalette::colorMap[182] = cm99;
    auto cm172 = new ObjectColorPalette(172);
    ObjectColorPalette::colorMap[172] = cm172;
    ObjectColorPalette::colorMap[172]->initialize();
    ObjectColorPalette::colorMap[170] = cm172;
    for (auto index : UtilityList::range(colorMapNumbers.size())) {
        ObjectColorPalette::colorMap[colorMapNumbers[index]] = new ObjectColorPalette(colorMapNumbers[index]);
        ObjectColorPalette::colorMap[colorMapNumbers[index]]->initialize();
    }
    ObjectColorPalette::colorMap[37] = ObjectColorPalette::colorMap[19];
    ObjectColorPalette::colorMap[38] = ObjectColorPalette::colorMap[19];
}
