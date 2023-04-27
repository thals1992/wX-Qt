// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "misc/UtilityHourly.h"
#include "common/GlobalVariables.h"
#include "misc/UtilityHourlyOldApi.h"
#include "objects/ObjectDateTime.h"
#include "objects/WString.h"
#include "settings/Location.h"
#include "settings/UIPreferences.h"
#include "util/To.h"
#include "util/Utility.h"
#include "util/UtilityDownloadNws.h"
#include "util/UtilityList.h"
#include "util/UtilityString.h"

const unordered_map<string, string> UtilityHourly::hourlyAbbreviations{
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

string UtilityHourly::getFooter() {
    auto footer = GlobalVariables::newline;
    for (const auto& s : hourlyAbbreviations) {
        footer += s.second + ": " + s.first + GlobalVariables::newline;
    }
    return footer;
}

string UtilityHourly::get(int locationNumber) {
    if (UIPreferences::useNwsApiForHourly) {
        return getHourlyString(locationNumber);
    }
    return UtilityHourlyOldApi::getHourlyString(locationNumber);
}

string UtilityHourly::getHourlyString(int locationNumber) {
    auto html = UtilityDownloadNws::getHourlyData(Location::getLatLon(locationNumber));
    if (html.size() < 150) {
        // qDebug() << "HOURLY:" << html << ":\n";
    }
    if (html.empty()) {
        // qDebug() << "HOURLY: 2nd download attempt:\n";
        html = UtilityDownloadNws::getHourlyData(Location::getLatLon(locationNumber));
    }
    const auto header = To::stringPadLeft("Time", 8) + To::stringPadLeft("T", 5) + To::stringPadLeft("Wind", 9) + To::stringPadLeft("WindDir", 6) + GlobalVariables::newline;
    const auto footer = getFooter();
    return header + parse(html) + footer;
}

string UtilityHourly::parse(const string& html) {
    const auto startTimes = UtilityString::parseColumn(html, "\"startTime\": \"(.*?)\",");
    const auto temperatures = UtilityString::parseColumn(html, "\"temperature\": (.*?),");
    const auto windSpeeds = UtilityString::parseColumn(html, "\"windSpeed\": \"(.*?)\"");
    const auto windDirections = UtilityString::parseColumn(html, "\"windDirection\": \"(.*?)\"");
    const auto shortForecasts = UtilityString::parseColumn(html, "\"shortForecast\": \"(.*?)\"");
    string stringValue;
    for (auto index : range(startTimes.size())) {
        const auto time = ObjectDateTime::translateTimeForHourly(Utility::safeGet(startTimes, index));
        const auto temperature = Utility::safeGet(temperatures, index);
        const auto windSpeed = WString::replace(Utility::safeGet(windSpeeds, index), " to ", "-");
        const auto windDirection = Utility::safeGet(windDirections, index);
        const auto shortForecast = Utility::safeGet(shortForecasts, index);
        stringValue += To::stringPadLeft(time, 7);
        stringValue += To::stringPadLeft(temperature, 4);
        stringValue += To::stringPadLeft(windSpeed, 8);
        stringValue += To::stringPadLeft(windDirection, 4);
        stringValue += To::stringPadLeft(shortenConditions(shortForecast), 18);
        stringValue += GlobalVariables::newline;
    }
    return stringValue;
}

string UtilityHourly::shortenConditions(const string& stringF) {
    auto hourly = stringF;
    for (const auto& data : hourlyAbbreviations) {
        hourly = WString::replace(hourly, data.first, data.second);
    }
    return hourly;
}
