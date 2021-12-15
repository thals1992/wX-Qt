// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "util/Utility.h"
#include "MyApplication.h"
#include "radar/UtilityRadar.h"
#include "util/To.h"

QString Utility::getRadarSiteName(const QString& radarSite) {
    return UtilityRadar::radarIdToName[radarSite];
}

LatLon Utility::getRadarSiteLatLon(const QString& radarSite) {
    const auto lat = UtilityRadar::radarSiteToLat[radarSite];
    const auto lon = "-" + UtilityRadar::radarSiteToLon[radarSite];
    return LatLon(lat, lon);
}

QString Utility::getRadarSiteX(const QString& radarSite) {
    return UtilityRadar::radarSiteToLat[radarSite];
}

QString Utility::getRadarSiteY(const QString& radarSite) {
    return UtilityRadar::radarSiteToLon[radarSite];
}

LatLon Utility::getWfoSiteLatLon(const QString& wfo) {
    const auto lat = UtilityRadar::wfoSiteToLat[wfo];
    const auto lon = UtilityRadar::wfoSiteToLon[wfo];
    return LatLon(lat, lon);
}

LatLon Utility::getSoundingSiteLatLon(const QString& wfo) {
    const auto lat = UtilityRadar::soundingSiteToLat[wfo];
    const auto lon = "-" + UtilityRadar::soundingSiteToLon[wfo];
    return LatLon(lat, lon);
}

QString Utility::readPref(const QString& key, const QString& value) {
    return MyApplication::preferences->value(key, value).toString();
}

int Utility::readPrefInt(const QString& key, int value) {
    return To::Int(MyApplication::preferences->value(key, To::String(value)).toString());
}

void Utility::writePref(const QString& key, const QString& value) {
    MyApplication::preferences->setValue(key, value);
    MyApplication::preferences->sync();
}

void Utility::writePrefInt(const QString& key, int value) {
    MyApplication::preferences->setValue(key, To::String(value));
    MyApplication::preferences->sync();
}

QStringList Utility::prefGetAllKeys() {
    return MyApplication::preferences->allKeys();
}

QString Utility::safeGet(const QStringList& items, int index) {
    if (items.size() <= index)
        return "";
    else
        return items[index];
}
