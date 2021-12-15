// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "settings/UIPreferences.h"
#include "util/Utility.h"

const int UIPreferences::boxPadding = 2;
const int UIPreferences::padding = 4;
int UIPreferences::mainScreenImageSize = 350;
int UIPreferences::imageSizeNwsForecast = 62;
int UIPreferences::imageWithTextSize = 600;
int UIPreferences::comboBoxSize = 20;
QMargins UIPreferences::textPadding;
QMargins UIPreferences::zeroPadding;
QString UIPreferences::homeScreenTokens;
bool UIPreferences::useNwsApi;
bool UIPreferences::useNwsApiForHourly;
bool UIPreferences::lightningUseGoes;
bool UIPreferences::nexradMainScreen;
bool UIPreferences::mainScreenSevereDashboard;
QVector<PrefBool> UIPreferences::homeScreenItemsImage;
QVector<PrefBool> UIPreferences::homeScreenItemsText;

void UIPreferences::initialize() {
    textPadding = QMargins(padding, padding, padding, padding);
    zeroPadding = QMargins(0, 0, 0, 0);
    homeScreenTokens = Utility::readPref("HOMESCREEN_TOKENS", "HOURLY:WFO_TEXT:");
    mainScreenImageSize = Utility::readPrefInt("MAIN_SCREEN_IMAGE_SIZE", mainScreenImageSize);
    useNwsApi = Utility::readPref("USE_NWS_API_SEVEN_DAY", "false").startsWith("t");
    useNwsApiForHourly = Utility::readPref("USE_NWS_API_HOURLY", "true").startsWith("t");
    lightningUseGoes = Utility::readPref("LIGHTNING_USE_GOES", "true").startsWith("t");
    nexradMainScreen = Utility::readPref("NEXRAD_ON_MAIN_SCREEN", "false").startsWith("t");
    // nexradMainScreen = false;
    mainScreenSevereDashboard = Utility::readPref("MAINSCREEN_SEVERE_DASH", "false").startsWith("t");

    homeScreenItemsImage = {
        PrefBool("Visible Satellite", "VISIBLE_SATELLITE", true),
        PrefBool("Radar Mosaic", "RADAR_MOSAIC", true),
        PrefBool("Alerts", "USWARN", false),
        PrefBool("Forecast Map", "ANALYSIS_RADAR_AND_WARNINGS", false),
    };
    homeScreenItemsText = {
        PrefBool("Hourly", "HOURLY", false),
        PrefBool("Wfo Text", "WFO_TEXT", false)
    };
}
