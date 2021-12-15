// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "settings/RadarPreferences.h"
#include "objects/Color.h"
#include "objects/ObjectPolygonWarning.h"
#include "objects/ObjectPolygonWatch.h"
#include "ui/TextViewMetal.h"
#include "util/Utility.h"

bool RadarPreferences::wxoglRememberLocation;
bool RadarPreferences::mcd;
bool RadarPreferences::watch;
bool RadarPreferences::mpd;
bool RadarPreferences::swo;
bool RadarPreferences::hw;
bool RadarPreferences::hwEnhExt;
bool RadarPreferences::caBorders;
bool RadarPreferences::mxBorders;
bool RadarPreferences::locDot;
bool RadarPreferences::county;
bool RadarPreferences::lakes;
bool RadarPreferences::cities;
bool RadarPreferences::countyLabels;
bool RadarPreferences::obs;
bool RadarPreferences::spotters;
bool RadarPreferences::spotterLabels;
bool RadarPreferences::obsWindbarbs;
bool RadarPreferences::sti;
bool RadarPreferences::hi;
bool RadarPreferences::tvs;
bool RadarPreferences::showWpcFronts;
bool RadarPreferences::dualpaneshareposn;
bool RadarPreferences::radarShowControls;
bool RadarPreferences::radarShowStatusBar;
bool RadarPreferences::colorLegend;
int RadarPreferences::radarTextSize;
int RadarPreferences::dataRefreshInterval;

double RadarPreferences::warnLinesize = 0.0;
double RadarPreferences::watmcdLinesize = 0.0;
double RadarPreferences::stateLinesize = 0.0;
double RadarPreferences::countyLinesize = 0.0;
double RadarPreferences::hwLinesize = 0.0;
double RadarPreferences::hwExtLinesize = 0.0;
double RadarPreferences::lakeLinesize = 0.0;
double RadarPreferences::gpsCircleLinesize = 0.0;
double RadarPreferences::stiLinesize = 0.0;
double RadarPreferences::swoLinesize = 0.0;
double RadarPreferences::wbLinesize = 0.0;
// was 10.0 for vala/gtk port
double RadarPreferences::lineFactor = 20.0;
double RadarPreferences::locdotSize = 20.0;
double RadarPreferences::aviationSize = 20.0;

QColor RadarPreferences::colorHw;
QColor RadarPreferences::colorHwExt;
QColor RadarPreferences::colorState;
QColor RadarPreferences::colorTstorm;
QColor RadarPreferences::colorTstormWatch;
QColor RadarPreferences::colorTor;
QColor RadarPreferences::colorTorWatch;
QColor RadarPreferences::colorFfw;
QColor RadarPreferences::colorMcd;
QColor RadarPreferences::colorMpd;
QColor RadarPreferences::colorLocdot;
QColor RadarPreferences::colorSpotter;
QColor RadarPreferences::colorCity;
QColor RadarPreferences::colorLakes;
QColor RadarPreferences::colorCounty;
QColor RadarPreferences::colorSti;
QColor RadarPreferences::colorHi;
QColor RadarPreferences::colorObs;
QColor RadarPreferences::colorObsWindbarbs;
QColor RadarPreferences::colorCountyLabels;

void RadarPreferences::initialize() {
    wxoglRememberLocation = Utility::readPref("WXOGL_REMEMBER_LOCATION", "true").startsWith("t");
    mcd = Utility::readPref("RADAR_SHOW_MCD", "false").startsWith("t");
    watch = Utility::readPref("RADAR_SHOW_WATCH", "false").startsWith("t");
    mpd = Utility::readPref("RADAR_SHOW_MPD", "false").startsWith("t");
    swo = Utility::readPref("RADAR_SHOW_SWO", "false").startsWith("t");
    dataRefreshInterval = Utility::readPrefInt("RADAR_DATA_REFRESH_INTERVAL", 5);
    colorLegend = Utility::readPref("RADAR_COLOR_LEGEND", "false").startsWith("t");
    hw = Utility::readPref("COD_HW_DEFAULT", "false").startsWith("t");
    hwEnhExt = Utility::readPref("RADAR_HW_ENH_EXT", "false").startsWith("t");
    caBorders = Utility::readPref("RADARCANADALINES", "false").startsWith("t");
    mxBorders = Utility::readPref("RADARMEXICOLINES", "false").startsWith("t");
    locDot = Utility::readPref("COD_LOCDOT_DEFAULT", "true").startsWith("t");
    lakes = Utility::readPref("COD_LAKES_DEFAULT", "false").startsWith("t");
    county = Utility::readPref("RADAR_SHOW_COUNTY", "true").startsWith("t");
    countyLabels = Utility::readPref("RADAR_COUNTY_LABELS", "false").startsWith("t");
    cities = Utility::readPref("COD_CITIES_DEFAULT", "").startsWith("t");
    obs = Utility::readPref("WXOGL_OBS", "false").startsWith("t");
    spotters = Utility::readPref("WXOGL_SPOTTERS", "false").startsWith("t");
    spotterLabels = Utility::readPref("WXOGL_SPOTTERS_LABEL", "false").startsWith("t");
    obsWindbarbs = Utility::readPref("WXOGL_OBS_WINDBARBS", "false").startsWith("t");
    sti = Utility::readPref("RADAR_SHOW_STI", "false").startsWith("t");
    hi = Utility::readPref("RADAR_SHOW_HI", "false").startsWith("t");
    tvs = Utility::readPref("RADAR_SHOW_TVS", "false").startsWith("t");
    showWpcFronts = Utility::readPref("RADAR_SHOW_WPC_FRONTS", "false").startsWith("t");
    dualpaneshareposn = Utility::readPref("DUALPANE_SHARE_POSN", "true").startsWith("t");
    radarShowControls = Utility::readPref("RADAR_SHOW_CONTROLS", "true").startsWith("t");
    radarShowStatusBar = Utility::readPref("RADAR_SHOW_STATUSBAR", "true").startsWith("t");
    radarTextSize = Utility::readPrefInt("RADAR_TEXT_SIZE", 8);
    TextViewMetal::fontSize = radarTextSize;

    warnLinesize = Utility::readPrefInt("RADAR_WARN_LINESIZE", 20) / lineFactor;
    watmcdLinesize = Utility::readPrefInt("RADAR_WATMCD_LINESIZE", 20) / lineFactor;
    stateLinesize = Utility::readPrefInt("RADAR_STATE_LINESIZE", 10) / lineFactor;
    countyLinesize = Utility::readPrefInt("RADAR_COUNTY_LINESIZE", 10) / lineFactor;
    hwLinesize = Utility::readPrefInt("RADAR_HW_LINESIZE", 10) / lineFactor;
    hwExtLinesize = Utility::readPrefInt("RADAR_HWEXT_LINESIZE", 10) / lineFactor;
    lakeLinesize = Utility::readPrefInt("RADAR_LAKE_LINESIZE", 10) / lineFactor;
    gpsCircleLinesize = Utility::readPrefInt("RADAR_GPSCIRCLE_LINESIZE", 4) / lineFactor;
    stiLinesize = Utility::readPrefInt("RADAR_STI_LINESIZE", 10) / lineFactor;
    swoLinesize = Utility::readPrefInt("RADAR_SWO_LINESIZE", 20) / lineFactor;
    wbLinesize = Utility::readPrefInt("RADAR_WB_LINESIZE", 10) / lineFactor;
    locdotSize = Utility::readPrefInt("RADAR_LOCDOT_SIZE", 20) / lineFactor;
    aviationSize = Utility::readPrefInt("RADAR_AVIATION_SIZE", 20) / lineFactor;

    ObjectPolygonWarning::load();
    ObjectPolygonWatch::load();
    initializeColors();
}

void RadarPreferences::initializeColors() {
    colorHw = getInitialPreference("RADAR_COLOR_HW", Color::rgb(135, 135, 135));
    colorHwExt = getInitialPreference("RADAR_COLOR_HW_EXT", Color::rgb(91, 91, 91));
    colorState = getInitialPreference("RADAR_COLOR_STATE", Color::rgb(255, 255, 255));
    colorTstorm = getInitialPreference("RADAR_COLOR_TSTORM", Color::rgb(255, 255, 0));
    colorTstormWatch = getInitialPreference("RADAR_COLOR_TSTORM_WATCH", Color::rgb(255, 187, 0));
    colorTor = getInitialPreference("RADAR_COLOR_TOR", Color::rgb(243, 85, 243));
    colorTorWatch = getInitialPreference("RADAR_COLOR_TOR_WATCH", Color::rgb(255, 0, 0));
    colorFfw = getInitialPreference("RADAR_COLOR_FFW", Color::rgb(0, 255, 0));
    colorMcd = getInitialPreference("RADAR_COLOR_MCD", Color::rgb(153, 51, 255));
    colorMpd = getInitialPreference("RADAR_COLOR_MPD", Color::rgb(0, 255, 0));
    colorLocdot = getInitialPreference("RADAR_COLOR_LOCDOT", Color::rgb(255, 255, 255));
    colorSpotter = getInitialPreference("RADAR_COLOR_SPOTTER", Color::rgb(255, 0, 245));
    colorCity = getInitialPreference("RADAR_COLOR_CITY", Color::rgb(255, 255, 255));
    colorLakes = getInitialPreference("RADAR_COLOR_LAKES", Color::rgb(0, 0, 255));
    colorCounty = getInitialPreference("RADAR_COLOR_COUNTY", Color::rgb(75, 75, 75));
    colorSti = getInitialPreference("RADAR_COLOR_STI", Color::rgb(255, 255, 255));
    colorHi = getInitialPreference("RADAR_COLOR_HI", Color::rgb(0, 255, 0));
    colorObs = getInitialPreference("RADAR_COLOR_OBS", Color::rgb(255, 255, 255));
    colorObsWindbarbs = getInitialPreference("RADAR_COLOR_OBS_WINDBARBS", Color::rgb(255, 255, 255));
    colorCountyLabels = getInitialPreference("RADAR_COLOR_COUNTY_LABELS", Color::rgb(234, 214, 123));
}

QColor RadarPreferences::getInitialPreference(const QString& pref, int colorAsInt) {
    const auto color = Utility::readPrefInt(pref, colorAsInt);
    return Color::intToQColor(color);
}
