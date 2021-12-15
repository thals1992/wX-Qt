// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "util/UtilityTimeSunMoon.h"
#include <QDateTime>
#include <QTimeZone>
#include <iostream>
#include "settings/Location.h"
#include "external/SunSet.h"
#include "util/UtilityTime.h"

using namespace std;

QString UtilityTimeSunMoon::getSunTimesForHomescreen() {
    SunSet sun;
    int offset = QTimeZone::systemTimeZone().offsetFromUtc(QDateTime::currentDateTime()) / 3600;
    sun.setPosition(Location::getLatLonCurrent().lat, Location::getLatLonCurrent().lon, offset);
    sun.setCurrentDate(UtilityTime::getYear(), UtilityTime::getMonth(), UtilityTime::getDay());
    // If you have daylight savings time, make sure you set the timezone appropriately as well
    sun.setTZOffset(offset);
    double sunrise = sun.calcSunrise();
    double sunset = sun.calcSunset();
    QTime sr(0, 0, 0);
    sr = sr.addSecs(static_cast<int>(60 * sunrise));
    QTime ss(0, 0, 0);
    ss = ss.addSecs(static_cast<int>(60 * sunset));
    return "Sunrise: " + sr.toString("hh:mm ap") + " Sunset: " + ss.toString("hh:mm ap");
}

QString UtilityTimeSunMoon::getSunTimes(LatLon latLon) {
    SunSet sun;
    int offset = QTimeZone::systemTimeZone().offsetFromUtc(QDateTime::currentDateTime()) / 3600;
    sun.setPosition(latLon.lat, latLon.lon, offset);
    sun.setCurrentDate(UtilityTime::getYear(), UtilityTime::getMonth(), UtilityTime::getDay());
    // If you have daylight savings time, make sure you set the timezone appropriately as well
    sun.setTZOffset(offset);
    double sunrise = sun.calcSunrise();
    double sunset = sun.calcSunset();
    QTime sr(0, 0, 0);
    sr = sr.addSecs(static_cast<int>(60 * sunrise));
    QTime ss(0, 0, 0);
    ss = ss.addSecs(static_cast<int>(60 * sunset));
    return "Sunrise: " + sr.toString("hh:mm ap") + " Sunset: " + ss.toString("hh:mm ap");
}

QVector<QTime> UtilityTimeSunMoon::getSunriseSunsetFromObs(const RID& obs) {
    SunSet sun;
    int offset = QTimeZone::systemTimeZone().offsetFromUtc(QDateTime::currentDateTime()) / 3600;
    sun.setPosition(obs.location.lat, obs.location.lon, offset);
    sun.setCurrentDate(UtilityTime::getYear(), UtilityTime::getMonth(), UtilityTime::getDay());
    // If you have daylight savings time, make sure you set the timezone appropriately as well
    sun.setTZOffset(offset);
    double sunrise = sun.calcSunrise();
    double sunset = sun.calcSunset();
    QTime sr(0, 0, 0);
    sr = sr.addSecs(static_cast<int>(60 * sunrise));
    QTime ss(0, 0, 0);
    ss = ss.addSecs(static_cast<int>(60 * sunset));
    return {sr, ss};
}
