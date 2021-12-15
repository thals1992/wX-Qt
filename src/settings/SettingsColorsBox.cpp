// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "settings/SettingsColorsBox.h"

SettingsColorsBox::SettingsColorsBox(QWidget * parent) : Widget(parent) {
    box = HBox(this);
    vbox1 = VBox(nullptr);
    vbox2 = VBox(nullptr);
    loadColors();
    int i = 0;
    for (const WXColor& color : colors) {
        objectColorLabels.push_back(new ObjectColorLabel(this, color));
        if (i >= colors.size() / 2) {
            vbox2.addLayout(objectColorLabels.back()->get());
        } else {
            vbox1.addLayout(objectColorLabels.back()->get());
        }
        i += 1;
    }
    vbox1.addStretch();
    vbox2.addStretch();
    box.addLayout(vbox1.get());
    box.addLayout(vbox2.get());
    setLayout(box.get());
}

void SettingsColorsBox::loadColors() {
    colors.push_back(WXColor("Cities", "RADAR_COLOR_CITY", 255, 255, 255));
    colors.push_back(WXColor("Counties", "RADAR_COLOR_COUNTY", 75, 75, 75));
    colors.push_back(WXColor("County Labels", "RADAR_COLOR_COUNTY_LABELS", 234, 214, 123));
    colors.push_back(WXColor("Draw Tool", "DRAW_TOOL_COLOR", 255, 0, 0));
    colors.push_back(WXColor("Flash Flood Warning", "RADAR_COLOR_FFW", 0, 255, 0));
    colors.push_back(WXColor("Hail Indicators", "RADAR_COLOR_HI", 0, 255, 0));
    colors.push_back(WXColor("Highways", "RADAR_COLOR_HW", 135, 135, 135));
    colors.push_back(WXColor("Lakes and Rivers", "RADAR_COLOR_LAKES", 0, 0, 255));
    colors.push_back(WXColor("Location Dot", "RADAR_COLOR_LOCDOT", 255, 255, 255));
    colors.push_back(WXColor("MCD", "RADAR_COLOR_MCD", 153, 51, 255));
    colors.push_back(WXColor("MPD", "RADAR_COLOR_MPD", 0, 255, 0));
    colors.push_back(WXColor("NWS Forecast Icon Bottom Color", "NWS_ICON_BOTTOM_COLOR", 255, 255, 255));
    colors.push_back(WXColor("NWS Forecast Icon Text Color", "NWS_ICON_TEXT_COLOR", 38, 97, 139));
    colors.push_back(WXColor("Nexrad Radar Background Color", "NEXRAD_RADAR_BACKGROUND_COLOR", 0, 0, 0));
    colors.push_back(WXColor("Observations", "RADAR_COLOR_OBS", 255, 255, 255));
    colors.push_back(WXColor("Secondary Roads", "RADAR_COLOR_HW_EXT", 91, 91, 91));
    colors.push_back(WXColor("Spotters", "RADAR_COLOR_SPOTTER", 255, 0, 245));
    colors.push_back(WXColor("State Lines", "RADAR_COLOR_STATE", 142, 142, 142));
    colors.push_back(WXColor("Storm Tracks", "RADAR_COLOR_STI", 255, 255, 255));
    colors.push_back(WXColor("Thunderstorm Warning", "RADAR_COLOR_TSTORM", 255, 255, 0));
    colors.push_back(WXColor("Thunderstorm Watch", "RADAR_COLOR_TSTORM_WATCH", 255, 187, 0));
    colors.push_back(WXColor("Tornado Warning", "RADAR_COLOR_TOR", 243, 85, 243));
    colors.push_back(WXColor("Tornado Watch", "RADAR_COLOR_TOR_WATCH", 255, 0, 0));
    colors.push_back(WXColor("Wind Barbs", "RADAR_COLOR_OBS_WINDBARBS", 255, 255, 255));
}
