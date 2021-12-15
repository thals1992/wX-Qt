// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "objects/WXColor.h"
#include "objects/Color.h"
#include "settings/RadarPreferences.h"
#include "util/To.h"
#include "util/Utility.h"

WXColor::WXColor() {
}

WXColor::WXColor(const QString& uiLabel, const QString& prefVar, int defaultRed, int defaultGreen, int defaultBlue) {
    this->uiLabel = uiLabel;
    this->prefVar = prefVar;
    this->defaultRed = defaultRed;
    this->defaultGreen = defaultGreen;
    this->defaultBlue = defaultBlue;
    defaultcolorAsInt = Color::rgb(defaultRed, defaultGreen, defaultBlue);
    colorAsInt = Utility::readPrefInt(prefVar, Color::rgb(defaultRed, defaultGreen, defaultBlue));
    red = Color::red(colorAsInt);
    green = Color::green(colorAsInt);
    blue = Color::blue(colorAsInt);
    qcolor = Color::intToQColor(colorAsInt);
    qcolorDefault = Color::intToQColor(defaultcolorAsInt);
}

void WXColor::setValue(int newValue) const {
    Utility::writePref(prefVar, To::String(newValue));
    RadarPreferences::initializeColors();
}

QString WXColor::styleSheetCurrent() const {
    return "QLabel { background-color : rgb(" + To::String(red) + "," + To::String(green) + "," + To::String(blue) + ");}";
}
