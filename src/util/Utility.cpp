// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "util/Utility.h"
#include <QString>
#include "MyApplication.h"
#include "radar/UtilityRadar.h"
#include "util/To.h"

string Utility::getRadarSiteName(const string& radarSite) {
    return UtilityRadar::radarIdToName.at(radarSite);
}

LatLon Utility::getRadarSiteLatLon(const string& radarSite) {
    return {UtilityRadar::radarSiteToLat.at(radarSite), "-" + UtilityRadar::radarSiteToLon.at(radarSite)};
}

string Utility::getRadarSiteX(const string& radarSite) {
    return UtilityRadar::radarSiteToLat.at(radarSite);
}

string Utility::getRadarSiteY(const string& radarSite) {
    return UtilityRadar::radarSiteToLon.at(radarSite);
}

LatLon Utility::getWfoSiteLatLon(const string& wfo) {
    return {UtilityRadar::wfoSiteToLat.at(wfo), UtilityRadar::wfoSiteToLon.at(wfo)};
}

LatLon Utility::getSoundingSiteLatLon(const string& wfo) {
    return {UtilityRadar::soundingSiteToLat.at(wfo), "-" + UtilityRadar::soundingSiteToLon.at(wfo)};
}

string Utility::readPref(const string& key, const string& value) {
    return MyApplication::preferences->value(QString::fromStdString(key), QString::fromStdString(value)).toString().toStdString();
}

int Utility::readPrefInt(const string& key, int value) {
    return To::Int(MyApplication::preferences->value(QString::fromStdString(key), QString::fromStdString(To::string(value))).toString().toStdString());
}

void Utility::writePref(const string& key, const string& value) {
    MyApplication::preferences->setValue(QString::fromStdString(key), QString::fromStdString(value));
    MyApplication::preferences->sync();
}

void Utility::writePrefInt(const string& key, int value) {
    MyApplication::preferences->setValue(QString::fromStdString(key), QString::fromStdString(To::string(value)));
    MyApplication::preferences->sync();
}

vector<string> Utility::prefGetAllKeys() {
    const auto items = MyApplication::preferences->allKeys();
    vector<string> stringList;
    for (const auto& item : items) {
        stringList.push_back(item.toStdString());
    }
    return stringList;
}

string Utility::safeGet(const vector<string>& items, size_t index) {
    return items.size() <= index ? "" : items[index];
}
