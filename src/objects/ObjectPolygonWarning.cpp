// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "objects/ObjectPolygonWarning.h"
#include "objects/Color.h"
#include "util/Utility.h"
#include "util/UtilityIO.h"
#include "util/UtilityString.h"
#include "util/UtilityTime.h"

const QString ObjectPolygonWarning::pVtec = "([A-Z0]{1}\\.[A-Z]{3}\\.[A-Z]{4}\\.[A-Z]{2}\\.[A-Z]\\.[0-9]{4}\\.[0-9]{6}T[0-9]{4}Z\\-[0-9]{6}T[0-9]{4}Z)";
const QString ObjectPolygonWarning::baseUrl = "https://api.weather.gov/alerts/active?event=";

const QHash<PolygonType, int> ObjectPolygonWarning::defaultColors = {
    {PolygonType::smw, Color::rgb(255, 165, 0)},
    {PolygonType::sqw, Color::rgb(199, 21, 133)},
    {PolygonType::dsw, Color::rgb(255, 228, 196)},
    {PolygonType::sps, Color::rgb(255, 228, 181)},
    {PolygonType::tor, Color::rgb(243, 85, 243)},
    {PolygonType::tst, Color::rgb(255, 255, 0)},
    {PolygonType::ffw, Color::rgb(0, 255, 0)},
    {PolygonType::mws, Color::rgb(255, 239, 213)}
};

const QHash<PolygonType, QString> ObjectPolygonWarning::longName = {
    {PolygonType::smw, "Special%20Marine%20Warning"},
    {PolygonType::sqw, "Snow%20Squall%20Warning"},
    {PolygonType::dsw, "Dust%20Storm%20Warning"},
    {PolygonType::sps, "Special%20Weather%20Statement"},
    {PolygonType::tor, "Tornado%20Warning"},
    {PolygonType::tst, "Severe%20Thunderstorm%20Warning"},
    {PolygonType::ffw, "Flash%20Flood%20Warning"},
    // {PolygonType::ffw, "Flood%20Warning"},
    {PolygonType::mws, "Marine%20Weather%20Statement"}
};

const QVector<PolygonType> ObjectPolygonWarning::polygonList = {
    PolygonType::tor,
    PolygonType::tst,
    PolygonType::ffw,
    PolygonType::smw,
    PolygonType::sqw,
    PolygonType::dsw,
    PolygonType::sps,
    PolygonType::mws
};

const QStringList ObjectPolygonWarning::namesByEnumId = {
    "none",
    "mcd",
    "mpd",
    "watch",
    "watchTornado",
    "tst",
    "tor",
    "ffw",
    "spotter",
    "spotterLabels",
    "windBarbGusts",
    "windBarb",
    "windBarbCircle",
    "locationDot",
    "locationDotCircle",
    "sti",
    "tvs",
    "hi",
    "observations",
    "swo",
    "smw",
    "sqw",
    "dsw",
    "sps",
    "mws",
};

QHash<PolygonType, ObjectPolygonWarning *> ObjectPolygonWarning::polygonDataByType;

ObjectPolygonWarning::ObjectPolygonWarning() {
}

ObjectPolygonWarning::ObjectPolygonWarning(const PolygonType& type1) {
    this->type1 = type1;
    isEnabled = Utility::readPref(prefTokenEnabled(), "false").startsWith("t");
    storage = DataStorage(prefTokenStorage());
    timer = DownloadTimer("WARNINGS_" + getTypeName());
    storage.update();
}

void ObjectPolygonWarning::download() {
    if (timer.isRefreshNeeded()) {
        auto html = UtilityIO::getHtml(getUrl());
        if (html != "") {
            storage.setValue(html);
        }
    }
}

QString ObjectPolygonWarning::getData() {
    return storage.getValue();
}

void ObjectPolygonWarning::enable() {
    isEnabled = true;
    Utility::writePref(prefTokenEnabled(), "true");
}

void ObjectPolygonWarning::disable() {
    isEnabled = false;
    Utility::writePref(prefTokenEnabled(), "false");
}

QString ObjectPolygonWarning::typeName() const {
    return namesByEnumId[type1];
}

QString ObjectPolygonWarning::getTypeName() const {
    return namesByEnumId[type1];
}

QString ObjectPolygonWarning::prefTokenEnabled() const {
    return "RADAR_SHOW_" + typeName();
}

QString ObjectPolygonWarning::prefTokenStorage() const {
    return "SEVERE_DASHBOARD_" + typeName();
}

QString ObjectPolygonWarning::prefTokenColor() const {
    return "RADAR_COLOR_" + typeName();
}

int ObjectPolygonWarning::color() const {
    return Utility::readPrefInt(prefTokenColor(), defaultColors[type1]);
}

QString ObjectPolygonWarning::name() const {
    auto nameLocal = longName[type1];
    nameLocal = nameLocal.replace("%20", " ");
    return nameLocal;
}

QString ObjectPolygonWarning::urlToken() const {
    return longName[type1];
}

QString ObjectPolygonWarning::url() const {
    return baseUrl + urlToken();
}

QString ObjectPolygonWarning::getUrl() const {
    return baseUrl + urlToken();
}

int ObjectPolygonWarning::getCount() const {
    const auto vtecAl = UtilityString::parseColumn(storage.getValue(), pVtec);
    auto count = 0;
    for (const auto& vtec : vtecAl) {
        if (!vtec.startsWith("O.EXP") && !vtec.startsWith("O.CAN") && UtilityTime::isVtecCurrent(vtec)) {
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

void ObjectPolygonWarning::load() {
    for (const auto& data : ObjectPolygonWarning::polygonList) {
        ObjectPolygonWarning::polygonDataByType[data] = new ObjectPolygonWarning(data);
    }
}
