// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "radar/ObjectMetalRadarBuffers.h"
#include "objects/Color.h"
#include "radarcolorpalette/ObjectColorPalette.h"
#include "settings/RadarPreferences.h"

ObjectMetalRadarBuffers::ObjectMetalRadarBuffers() {
    const auto size = 150000;
    rectPoints.reserve(size);
    color.reserve(size);
    colorPens.reserve(size);
    colorBrushes.reserve(size);
}

void ObjectMetalRadarBuffers::initialize() {
    rectPoints.clear();
    color.clear();
    colorPens.clear();
    colorBrushes.clear();
}

// DO NOT mark CONST
void ObjectMetalRadarBuffers::setBackgroundColor() {
    ObjectColorPalette::colorMap[productCode]->redValues->putByIndex(0, Color::red(Color::qcolorToInt(RadarPreferences::nexradRadarBackgroundColor)));
    ObjectColorPalette::colorMap[productCode]->greenValues->putByIndex(0, Color::green(Color::qcolorToInt(RadarPreferences::nexradRadarBackgroundColor)));
    ObjectColorPalette::colorMap[productCode]->blueValues->putByIndex(0, Color::blue(Color::qcolorToInt(RadarPreferences::nexradRadarBackgroundColor)));
}
