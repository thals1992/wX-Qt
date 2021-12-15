// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "MyApplication.h"
#include <QDebug>
#include <QDir>
#include <QStandardPaths>
#include "common/GlobalVariables.h"
#include "objects/RadarGeometry.h"
#include "radarcolorpalette/ColorPalettes.h"
#include "settings/Location.h"
#include "settings/RadarPreferences.h"
#include "settings/UIPreferences.h"
#include "util/Utility.h"
#include "settings/UtilityStorePreferences.h"

QSettings * MyApplication::preferences;

void MyApplication::onCreate() {
    preferences = new QSettings(GlobalVariables::appCreatorEmail, GlobalVariables::appName);
    if (Utility::readPref("LOC1_LABEL", "") == "") {
        UtilityStorePreferences::setDefaults();
    }
    Location::refreshLocationData();
    RadarGeometry::initialize();
    ColorPalettes::initialize();
    RadarPreferences::initialize();
    UIPreferences::initialize();
}
