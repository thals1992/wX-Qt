// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "util/UtilityTimeSunMoon.h"
#include <QDateTime>
#include <QTimeZone>
#include <iostream>
#include "settings/Location.h"
#include "external/SunSet.h"
#include "objects/ObjectDateTime.h"

string UtilityTimeSunMoon::getSunTimes(const LatLon& latLon) {
    SunSet sun;
    const auto offset = QTimeZone::systemTimeZone().offsetFromUtc(QDateTime::currentDateTime()) / 3600;
    sun.setPosition(latLon.lat(), latLon.lon(), offset);
    sun.setCurrentDate(ObjectDateTime::getYear(), ObjectDateTime::getMonth(), ObjectDateTime::getDay());
    // If you have daylight savings time, make sure you set the timezone appropriately as well
    sun.setTZOffset(offset);
    const auto sunrise = sun.calcSunrise();
    const auto sunset = sun.calcSunset();
    QTime sr{0, 0, 0};
    sr = sr.addSecs(static_cast<int>(60 * sunrise));
    QTime ss{0, 0, 0};
    ss = ss.addSecs(static_cast<int>(60 * sunset));
    return "Sunrise: " + sr.toString("hh:mm ap").toStdString() + " Sunset: " + ss.toString("hh:mm ap").toStdString();
}

vector<QTime> UtilityTimeSunMoon::getSunriseSunsetFromObs(const RID& obs) {
    SunSet sun;
    const auto offset = QTimeZone::systemTimeZone().offsetFromUtc(QDateTime::currentDateTime()) / 3600;
    sun.setPosition(obs.location.lat(), obs.location.lon(), offset);
    sun.setCurrentDate(ObjectDateTime::getYear(), ObjectDateTime::getMonth(), ObjectDateTime::getDay());
    // If you have daylight savings time, make sure you set the timezone appropriately as well
    sun.setTZOffset(offset);
    const auto sunrise = sun.calcSunrise();
    const auto sunset = sun.calcSunset();
    QTime sr{0, 0, 0};
    sr = sr.addSecs(static_cast<int>(60 * sunrise));
    QTime ss{0, 0, 0};
    ss = ss.addSecs(static_cast<int>(60 * sunset));
    return {sr, ss};
}
