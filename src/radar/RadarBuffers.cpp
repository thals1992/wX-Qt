// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "radar/RadarBuffers.h"
#include "objects/Color.h"
#include "radarcolorpalette/ColorPalette.h"
#include "settings/RadarPreferences.h"

RadarBuffers::RadarBuffers() {
    const auto size = 150000;
    rectPoints.reserve(size);
    color.reserve(size);
    colorPens.reserve(size);
    colorBrushes.reserve(size);
}

void RadarBuffers::initialize() {
    rectPoints.clear();
    color.clear();
    colorPens.clear();
    colorBrushes.clear();
}

// DO NOT mark CONST
void RadarBuffers::setBackgroundColor() {
    ColorPalette::colorMap[productCode]->redValues->putByIndex(0, Color::red(Color::qcolorToInt(RadarPreferences::nexradRadarBackgroundColor)));
    ColorPalette::colorMap[productCode]->greenValues->putByIndex(0, Color::green(Color::qcolorToInt(RadarPreferences::nexradRadarBackgroundColor)));
    ColorPalette::colorMap[productCode]->blueValues->putByIndex(0, Color::blue(Color::qcolorToInt(RadarPreferences::nexradRadarBackgroundColor)));
}
