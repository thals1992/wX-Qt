// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "misc/UtilityHourly.h"
#include "common/GlobalVariables.h"
#include "misc/UtilityHourlyOldApi.h"
#include "settings/Location.h"
#include "settings/UIPreferences.h"
#include "util/To.h"
#include "util/Utility.h"
#include "util/UtilityDownloadNws.h"
#include "util/UtilityList.h"
#include "util/UtilityString.h"
#include "util/UtilityTime.h"

QHash<QString, QString> UtilityHourly::hourlyAbbreviations = {
    {"Showers And Thunderstorms", "Sh/Tst"},
    {"Chance", "Chc"},
    {"Slight", "Slt"},
    {"Light", "Lgt"},
    {"Scattered", "Sct"},
    {"Rain", "Rn"},
    {"Snow", "Sn"},
    {"Rn And Sn", "Rn/Sn"},
    {"Freezing", "Frz"},
    {"Drizzle", "Drz"},
    {"Isolated", "Iso"},
    {"Likely", "Lkly"},
    {"T-storms", "Tst"},
    {"Showers", "Shwr"},
    {"Rn And Sn", "Rn/Sn"}
};

QString UtilityHourly::getFooter() {
    auto footer = GlobalVariables::newline;
    for (const auto& s : hourlyAbbreviations.keys()) {
        footer += hourlyAbbreviations[s] + ": " + s + GlobalVariables::newline;
    }
    return footer;
}

QString UtilityHourly::get(int locationNumber) {
    if (UIPreferences::useNwsApiForHourly) {
        return getHourlyString(locationNumber);
    }
    return UtilityHourlyOldApi::getHourlyString(locationNumber);
}

QString UtilityHourly::getHourlyString(int locationNumber) {
    const auto html = UtilityDownloadNws::getHourlyData(Location::getLatLon(locationNumber));
    const auto header = QString("Time").leftJustified(7, ' ') + QString("T").leftJustified(4, ' ') + QString("Wind").leftJustified(8, ' ') + QString("WindDir").leftJustified(6, ' ') + GlobalVariables::newline;
    const auto footer = getFooter();
    return header + parse(html) + footer;
}

QString UtilityHourly::parse(const QString& html) {
    const auto startTimes = UtilityString::parseColumn(html, "\"startTime\": \"(.*?)\",");
    const auto temperatures = UtilityString::parseColumn(html, "\"temperature\": (.*?),");
    const auto windSpeeds = UtilityString::parseColumn(html, "\"windSpeed\": \"(.*?)\"");
    const auto windDirections = UtilityString::parseColumn(html, "\"windDirection\": \"(.*?)\"");
    const auto shortForecasts = UtilityString::parseColumn(html, "\"shortForecast\": \"(.*?)\"");
    QString stringValue = "";
    for (auto index : UtilityList::range(startTimes.size())) {
        const auto time = translateTime(Utility::safeGet(startTimes, index));
        const auto temperature = Utility::safeGet(temperatures, index).replace("\"", "");
        const auto windSpeed = Utility::safeGet(windSpeeds, index).replace(" to ", "-");
        const auto windDirection = Utility::safeGet(windDirections, index);
        const auto shortForecast = Utility::safeGet(shortForecasts, index);
        stringValue += time.leftJustified(7, ' ');
        stringValue += temperature.leftJustified(4, ' ');
        stringValue += windSpeed.leftJustified(8, ' ');
        stringValue += windDirection.leftJustified(4, ' ');
        stringValue += shortenConditions(shortForecast).leftJustified(18, ' ');
        stringValue += GlobalVariables::newline;
    }
    return stringValue;
}

QString UtilityHourly::shortenConditions(const QString& stringF) {
    auto hourly = stringF;
    for (const auto& s : hourlyAbbreviations.keys()) {
        hourly = hourly.replace(s, hourlyAbbreviations[s]);
    }
    return hourly;
}

QString UtilityHourly::translateTime(const QString& originalTime) {
    auto value = originalTime;
    value = value.replace("T", "-");
    auto originalTimeComponents = value.split("-");
    auto hour = To::Int(originalTimeComponents[3].replace(":00:00", ""));
    auto hourString = To::String(hour);
    auto dayOfTheWeek = UtilityTime::hourlyDayOfWeek(originalTime);
    return dayOfTheWeek + " " + hourString;
}
