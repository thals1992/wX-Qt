// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "settings/UIPreferences.h"
#include "objects/WString.h"
#include "util/Utility.h"

const int UIPreferences::boxPadding{2};
const int UIPreferences::padding{4};
int UIPreferences::mainScreenImageSize{350};
int UIPreferences::imageSizeNwsForecast{62};
int UIPreferences::comboBoxSize{20};
int UIPreferences::toolbarIconSize{36};
QMargins UIPreferences::textPadding;
bool UIPreferences::useNwsApi;
bool UIPreferences::useNwsApiForHourly;
bool UIPreferences::nexradMainScreen;
bool UIPreferences::mainScreenSevereDashboard;
bool UIPreferences::nexradScrollWheelMotion;
bool UIPreferences::rememberGOES;
bool UIPreferences::rememberMosaic;
vector<PrefBool> UIPreferences::homeScreenItemsImage{
    PrefBool{"Radar Mosaic", "RADAR_MOSAIC", true},
    PrefBool{"Visible Satellite", "VISIBLE_SATELLITE", true},
    PrefBool{"Alerts", "USWARN", false},
    PrefBool{"Analysis", "ANALYSIS_RADAR_AND_WARNINGS", false},
    PrefBool{"RTMA Temp", "RTMA_TEMP", false},
};
vector<PrefBool> UIPreferences::homeScreenItemsText{
    PrefBool{"Hourly", "HOURLY", true},
    PrefBool{"Wfo Text", "WFO_TEXT", false}
};

void UIPreferences::initialize() {
    textPadding = QMargins(padding, padding, padding, padding);
    mainScreenImageSize = Utility::readPrefInt("MAIN_SCREEN_IMAGE_SIZE", mainScreenImageSize);
    toolbarIconSize = Utility::readPrefInt("TOOLBAR_ICON_SIZE", toolbarIconSize);
    useNwsApi = WString::startsWith(Utility::readPref("USE_NWS_API_SEVEN_DAY", "false"), "t");
    useNwsApiForHourly = WString::startsWith(Utility::readPref("USE_NWS_API_HOURLY", "true"), "t");
    nexradMainScreen = WString::startsWith(Utility::readPref("NEXRAD_ON_MAIN_SCREEN", "false"), "t");
    mainScreenSevereDashboard = WString::startsWith(Utility::readPref("MAINSCREEN_SEVERE_DASH", "false"), "t");
    nexradScrollWheelMotion = WString::startsWith(Utility::readPref("NEXRAD_SCROLLWHEEL", "false"), "t");
    rememberGOES = WString::startsWith(Utility::readPref("REMEMBER_GOES", "false"), "t");
    rememberMosaic = WString::startsWith(Utility::readPref("REMEMBER_MOSAIC", "false"), "t");
}
