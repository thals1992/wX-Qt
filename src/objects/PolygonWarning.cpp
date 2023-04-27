// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "objects/PolygonWarning.h"
#include "objects/Color.h"
#include "objects/WString.h"
#include "radar/NexradUtil.h"
#include "radar/Warnings.h"
#include "util/Utility.h"
#include "util/UtilityIO.h"
#include "util/UtilityString.h"

const string PolygonWarning::pVtec{"([A-Z0]{1}\\.[A-Z]{3}\\.[A-Z]{4}\\.[A-Z]{2}\\.[A-Z]\\.[0-9]{4}\\.[0-9]{6}T[0-9]{4}Z\\-[0-9]{6}T[0-9]{4}Z)"};
const string PolygonWarning::baseUrl{"https://api.weather.gov/alerts/active?event="};

const unordered_map<PolygonType, int> PolygonWarning::defaultColors{
    {Smw, Color::rgb(255, 165, 0)},
    {Sqw, Color::rgb(199, 21, 133)},
    {Dsw, Color::rgb(255, 228, 196)},
    {Sps, Color::rgb(255, 228, 181)},
    {Tor, Color::rgb(243, 85, 243)},
    {Tst, Color::rgb(255, 255, 0)},
    {Ffw, Color::rgb(0, 255, 0)},
    {Mws, Color::rgb(255, 239, 213)}
};

const unordered_map<PolygonType, string> PolygonWarning::longName{
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

const vector<PolygonType> PolygonWarning::polygonList{
    Tor,
    Tst,
    Ffw,
    Smw,
    Sqw,
    Dsw,
    Sps
    // Mws
};

const unordered_map<PolygonType, string> PolygonWarning::namesByEnumId{
    {Tor, "tor"},
    {Tst, "tst"},
    {Ffw, "ffw"},
    {Smw, "smw"},
    {Sqw, "sqw"},
    {Dsw, "dsw"},
    {Sps, "sps"},
    {Mws, "mws"},
};

unordered_map<PolygonType, std::unique_ptr<PolygonWarning>> PolygonWarning::byType;

PolygonWarning::PolygonWarning(const PolygonType& type)
    : type{ type }
    , isEnabled{ WString::startsWith(Utility::readPref(prefTokenEnabled(), "false"), "t") }
    , storage{ DataStorage{prefTokenStorage()} }
    , timer{ DownloadTimer{"WARNINGS_" + getTypeName()} }
    , colorInt { Utility::readPrefInt("RADAR_COLOR_" + WString::toUpper(namesByEnumId.at(type)), defaultColors.at(type)) }
{
    storage.update();
}

void PolygonWarning::download() {
    if (timer.isRefreshNeeded()) {
        const auto html = UtilityIO::getHtml(getUrl());
        if (!html.empty()) {
            storage.setValue(html);
        }
    }
}

string PolygonWarning::getData() const {
    return storage.getValue();
}

// KEEP
// void PolygonWarning::enable() {
//    isEnabled = true;
//    Utility::writePref(prefTokenEnabled(), "true");
// }

// void PolygonWarning::disable() {
//    isEnabled = false;
//    Utility::writePref(prefTokenEnabled(), "false");
// }

string PolygonWarning::typeName() const {
    return namesByEnumId.at(type);
}

string PolygonWarning::getTypeName() const {
    return namesByEnumId.at(type);
}

string PolygonWarning::prefTokenEnabled() const {
    return "RADAR_SHOW_" + typeName();
}

string PolygonWarning::prefTokenStorage() const {
    return "SEVERE_DASHBOARD_" + typeName();
}

string PolygonWarning::prefTokenColor() const {
    return "RADAR_COLOR_" + typeName();
}

int PolygonWarning::color() const {
    return Utility::readPrefInt(prefTokenColor(), defaultColors.at(type));
}

string PolygonWarning::name() const {
    const auto tmp = longName.at(type);
    return WString::replace(tmp, "%20", " ");
}

string PolygonWarning::urlToken() const {
    return longName.at(type);
}

string PolygonWarning::url() const {
    return baseUrl + urlToken();
}

string PolygonWarning::getUrl() const {
    return baseUrl + urlToken();
}

int PolygonWarning::getCount() const {
    const auto vtecAl = UtilityString::parseColumn(storage.getValue(), pVtec);
    auto count = 0;
    for (const auto& vtec : vtecAl) {
        if (!WString::startsWith(vtec, "O.EXP") && !WString::startsWith(vtec, "O.CAN") && NexradUtil::isVtecCurrent(vtec)) {
            count += 1;
        }
    }
    return count;
}

string PolygonWarning::getLongName(PolygonType type) {
    return WString::replace(longName.at(type), "%20", " ");
}

string PolygonWarning::getShortName(PolygonType type) {
    return WString::toUpper(namesByEnumId.at(type));
}

bool PolygonWarning::areAnyEnabled() {
    auto anyEnabled = false;
    for (const auto& data : PolygonWarning::polygonList) {
        if (PolygonWarning::byType[data]->isEnabled) {
            anyEnabled = true;
        }
    }
    // bool test = std::any_of(PolygonWarning::polygonList.begin(), PolygonWarning::polygonList.end(), [](const PolygonType& data ){return PolygonWarning::byType[data].isEnabled;});
    return anyEnabled;
}

bool PolygonWarning::isCountNonZero() {
    auto count = 0;
    for (auto it : polygonList) {
        if (byType[it]->isEnabled) {
            count += Warnings::getCount(it);
        }
    }
    return count > 0;
}

void PolygonWarning::update() {
    isEnabled = WString::startsWith(Utility::readPref(prefTokenEnabled(), "false"), "t");
    colorInt = Utility::readPrefInt("RADAR_COLOR_" + WString::toUpper(namesByEnumId.at(type)), defaultColors.at(type));
}

void PolygonWarning::load() {
    for (auto data : polygonList) {
        if (byType.count(data) == 0) {
            byType[data] = std::make_unique<PolygonWarning>(data);
        } else {
            byType[data]->update();
        }
    }
}
