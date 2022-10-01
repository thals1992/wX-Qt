// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "MyApplication.h"
#include <QDir>
#include "common/GlobalVariables.h"
#include "radarcolorpalette/ColorPalettes.h"
#include "settings/Location.h"
#include "settings/RadarPreferences.h"
#include "settings/UIPreferences.h"
#include "util/Utility.h"
#include "settings/UtilityStorePreferences.h"

QSettings * MyApplication::preferences;

void MyApplication::onCreate() {
    preferences = new QSettings{QString::fromStdString(GlobalVariables::appCreatorEmail), QString::fromStdString(GlobalVariables::appName)};
    if (Utility::readPref("LOC1_LABEL", "").empty()) {
        UtilityStorePreferences::setDefaults();
    }
    Location::refreshLocationData();
    ColorPalettes::initialize();
    RadarPreferences::initialize();
    UIPreferences::initialize();
}
