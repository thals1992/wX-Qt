// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "spc/SpcMcdWatchMpdViewer.h"
#include "objects/FutureBytes.h"
#include "objects/FutureText.h"
#include "objects/LatLon.h"
#include "objects/WString.h"
#include "radar/Nexrad.h"
#include "settings/UtilityLocation.h"
#include "util/UtilityString.h"

SpcMcdWatchMpdViewer::SpcMcdWatchMpdViewer(QWidget * parent, const string& url)
    : Window{parent}
    , parent{ parent }
    , text{ Text{this} }
    , photo{ Photo{this, Scaled} }
    , sw{ TwoWidgetScroll{this, photo, boxText} }
    , button{ Button{this, None, "Radar"} }
    , shortcut{ Shortcut{QKeySequence{"R"}, this} }
    , token{ getToken(url) }
{
    setTitle(token);
    boxText.addWidget(button);
    boxText.addWidget(text);
    new FutureBytes{this, url, [this] (const auto& ba) { photo.setBytes(ba); }};
    new FutureText{this, token, [this] (const auto& s) { updateText(s); }};
}

void SpcMcdWatchMpdViewer::updateText(const string& html) {
    text.setText(html);
    auto textWithLatLon = html;
    if (WString::contains(token, "SPCWAT")) {
        textWithLatLon = LatLon::getWatchLatLon(WString::replace(token, "SPCWAT", ""));
    }
    auto stringOfLatLon = LatLon::storeWatchMcdLatLon(textWithLatLon);
    stringOfLatLon = WString::replace(stringOfLatLon, ":", "");
    const auto latLonList = LatLon::parseStringToLatLons(stringOfLatLon, -1.0, false);
    const auto center = UtilityLocation::getCenterOfPolygon(latLonList);
    const auto radarSite = UtilityLocation::getNearestRadarSites(center, 1, false)[0];
    const auto buttonRadarText = "Show Radar - " + radarSite.name;
    button.setText(buttonRadarText);
    button.connect([this, radarSite] { new Nexrad{this->parent, 1, true, radarSite.name}; });
    shortcut.connect([this, radarSite] { new Nexrad{this->parent, 1, true, radarSite.name}; });
}

string SpcMcdWatchMpdViewer::getToken(const string& url) {
    const auto items = WString::split(url, "/");
    auto s = items[items.size() - 1];
    s = WString::replace(s, ".gif", "");
    s = WString::replace(s, ".png", "");
    s = WString::toUpper(s);
    const auto tokenTrimmed = UtilityString::substring(s, s.size() - 4, s.size());
    if (WString::contains(url, "www.wpc.ncep.noaa.gov")) {
        s = "WPCMPD" + UtilityString::substring(s, s.size() - 4, s.size());
    } else if (WString::contains(url, "www.spc.noaa.gov") && WString::contains(url, "mcd")) {
        s = "SPCMCD" + tokenTrimmed;
    } else {
        const auto items1 = WString::split(url, "/");
        s = items1[items1.size() - 1];
        s = WString::replace(s, "_radar.gif", "");
        s = WString::replace(s, "ww", "");
        s = "SPCWAT" + s;
    }
    return s;
}
