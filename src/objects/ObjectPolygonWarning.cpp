// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "objects/ObjectPolygonWarning.h"
#include "objects/Color.h"
#include "objects/WString.h"
#include "radar/WXGLNexrad.h"
#include "util/Utility.h"
#include "util/UtilityIO.h"
#include "util/UtilityString.h"

const string ObjectPolygonWarning::pVtec{"([A-Z0]{1}\\.[A-Z]{3}\\.[A-Z]{4}\\.[A-Z]{2}\\.[A-Z]\\.[0-9]{4}\\.[0-9]{6}T[0-9]{4}Z\\-[0-9]{6}T[0-9]{4}Z)"};
const string ObjectPolygonWarning::baseUrl{"https://api.weather.gov/alerts/active?event="};

const unordered_map<PolygonType, int> ObjectPolygonWarning::defaultColors{
    {Smw, Color::rgb(255, 165, 0)},
    {Sqw, Color::rgb(199, 21, 133)},
    {Dsw, Color::rgb(255, 228, 196)},
    {Sps, Color::rgb(255, 228, 181)},
    {Tor, Color::rgb(243, 85, 243)},
    {Tst, Color::rgb(255, 255, 0)},
    {Ffw, Color::rgb(0, 255, 0)},
    {Mws, Color::rgb(255, 239, 213)}
};

const unordered_map<PolygonType, string> ObjectPolygonWarning::longName{
    {Smw, "Special%20Marine%20Warning"},
    {Sqw, "Snow%20Squall%20Warning"},
    {Dsw, "Dust%20Storm%20Warning"},
    {Sps, "Special%20Weather%20Statement"},
    {Tor, "Tornado%20Warning"},
    {Tst, "Severe%20Thunderstorm%20Warning"},
    {Mws, "Marine%20Weather%20Statement"},
    {Ffw, "Flash%20Flood%20Warning"}
//     {Ffw, "Flood%20Warning"}
};

const vector<PolygonType> ObjectPolygonWarning::polygonList{
    Tor,
    Tst,
    Ffw,
    Smw,
    Sqw,
    Dsw,
    Sps,
    Mws
};

const unordered_map<PolygonType, string> ObjectPolygonWarning::namesByEnumId{
    {Tor, "tor"},
    {Tst, "tst"},
    {Ffw, "ffw"},
    {Smw, "smw"},
    {Sqw, "sqw"},
    {Dsw, "dsw"},
    {Sps, "sps"},
    {Mws, "mws"},
};

unordered_map<PolygonType, std::unique_ptr<ObjectPolygonWarning>> ObjectPolygonWarning::polygonDataByType;

ObjectPolygonWarning::ObjectPolygonWarning(const PolygonType& type)
    : type{ type }
    , isEnabled{ WString::startsWith(Utility::readPref(prefTokenEnabled(), "false"), "t") }
    , storage{ DataStorage{prefTokenStorage()} }
    , timer{ DownloadTimer{"WARNINGS_" + getTypeName()} }
    , colorInt { Utility::readPrefInt("RADAR_COLOR_" + WString::toUpper(namesByEnumId.at(type)), defaultColors.at(type)) }
{
    storage.update();
}

void ObjectPolygonWarning::download() {
    if (timer.isRefreshNeeded()) {
        const auto html = UtilityIO::getHtml(getUrl());
        if (!html.empty()) {
            storage.setValue(html);
        }
    }
}

string ObjectPolygonWarning::getData() const {
    return storage.getValue();
}

// KEEP
// void ObjectPolygonWarning::enable() {
//    isEnabled = true;
//    Utility::writePref(prefTokenEnabled(), "true");
// }

// void ObjectPolygonWarning::disable() {
//    isEnabled = false;
//    Utility::writePref(prefTokenEnabled(), "false");
// }

string ObjectPolygonWarning::typeName() const {
    return namesByEnumId.at(type);
}

string ObjectPolygonWarning::getTypeName() const {
    return namesByEnumId.at(type);
}

string ObjectPolygonWarning::prefTokenEnabled() const {
    return "RADAR_SHOW_" + typeName();
}

string ObjectPolygonWarning::prefTokenStorage() const {
    return "SEVERE_DASHBOARD_" + typeName();
}

string ObjectPolygonWarning::prefTokenColor() const {
    return "RADAR_COLOR_" + typeName();
}

int ObjectPolygonWarning::color() const {
    return Utility::readPrefInt(prefTokenColor(), defaultColors.at(type));
}

string ObjectPolygonWarning::name() const {
    const auto tmp = longName.at(type);
    return WString::replace(tmp, "%20", " ");
}

string ObjectPolygonWarning::urlToken() const {
    return longName.at(type);
}

string ObjectPolygonWarning::url() const {
    return baseUrl + urlToken();
}

string ObjectPolygonWarning::getUrl() const {
    return baseUrl + urlToken();
}

int ObjectPolygonWarning::getCount() const {
    const auto vtecAl = UtilityString::parseColumn(storage.getValue(), pVtec);
    auto count = 0;
    for (const auto& vtec : vtecAl) {
        if (!WString::startsWith(vtec, "O.EXP") && !WString::startsWith(vtec, "O.CAN") && WXGLNexrad::isVtecCurrent(vtec)) {
            count += 1;
        }
    }
    return count;
}

bool ObjectPolygonWarning::areAnyEnabled() {
    auto anyEnabled = false;
    for (const auto& data : ObjectPolygonWarning::polygonList) {
        if (ObjectPolygonWarning::polygonDataByType[data]->isEnabled) {
            anyEnabled = true;
        }
    }
    // bool test = std::any_of(ObjectPolygonWarning::polygonList.begin(), ObjectPolygonWarning::polygonList.end(), [](const PolygonType& data ){return ObjectPolygonWarning::polygonDataByType[data].isEnabled;});
    return anyEnabled;
}

void ObjectPolygonWarning::update() {
    isEnabled = WString::startsWith(Utility::readPref(prefTokenEnabled(), "false"), "t");
    colorInt = Utility::readPrefInt("RADAR_COLOR_" + WString::toUpper(namesByEnumId.at(type)), defaultColors.at(type));
}

void ObjectPolygonWarning::load() {
    for (auto data : polygonList) {
        if (polygonDataByType.count(data) == 0) {
            polygonDataByType[data] = std::make_unique<ObjectPolygonWarning>(data);
        } else {
            polygonDataByType[data]->update();
        }
    }
}
