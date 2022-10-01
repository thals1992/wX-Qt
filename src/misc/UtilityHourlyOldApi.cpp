// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "misc/UtilityHourlyOldApi.h"
#include <iostream>
#include "common/GlobalVariables.h"
#include "objects/ObjectDateTime.h"
#include "objects/WString.h"
#include "settings/Location.h"
#include "util/To.h"
#include "util/UtilityIO.h"
#include "util/UtilityList.h"
#include "util/UtilityString.h"

string UtilityHourlyOldApi::getHourlyString(int locNumber) {
    const auto latLon  = Location::getLatLon(locNumber);
    const auto html = UtilityIO::getHtml("https://forecast.weather.gov/MapClick.php?lat=" +
            latLon.latStr() + "&lon=" +
            latLon.lonStr() + "&FcstType=digitalDWML");
    const auto header = To::stringPadLeft("Time", 14) + " "
        + To::stringPadLeft("Temp", 8)
        + To::stringPadLeft("Dew", 8)
        + To::stringPadLeft("Precip", 8)
        + To::stringPadLeft("Cloud", 8)
        + GlobalVariables::newline;
    return GlobalVariables::newline + header + parseHourly(html);
}

string UtilityHourlyOldApi::parseHourly(const string& html) {
    const vector<string> regexpList{
        "<temperature type=.hourly.*?>(.*?)</temperature>",
        "<temperature type=.dew point.*?>(.*?)</temperature>",
        "<time-layout.*?>(.*?)</time-layout>",
        "<probability-of-precipitation.*?>(.*?)</probability-of-precipitation>",
        "<cloud-amount type=.total.*?>(.*?)</cloud-amount>"
    };
    const auto rawData = UtilityString::parseXmlExt(regexpList, html);
    auto temp2List = UtilityString::parseXmlValue(rawData[0]);
    auto temp3List = UtilityString::parseXmlValue(rawData[1]);
    auto time2List = UtilityString::parseXml(rawData[2], "start-valid-time");
    auto temp4List = UtilityString::parseXmlValue(rawData[3]);
    auto temp5List = UtilityString::parseXmlValue(rawData[4]);

    const auto year = ObjectDateTime::getYear();
    auto temp2Len = temp2List.size();
    auto temp3Len = temp3List.size();
    auto temp4Len = temp4List.size();
    auto temp5Len = temp5List.size();

    string sb;
    for (auto j : range2(1, temp2Len)) {
        time2List[j] = UtilityString::replaceRegex(time2List[j], "-0[0-9]:00", "");
        time2List[j] = UtilityString::replaceRegex(time2List[j], "^.*?-", "");
        time2List[j] = WString::replace(time2List[j], "T", " ");
        time2List[j] = WString::replace(time2List[j], "00:00", "00");

        auto timeSplit = WString::split(time2List[j], " ");
        auto timeSplit2 = WString::split(timeSplit[0], "-");
        auto month = To::Int(timeSplit2[0]);
        auto day = To::Int(timeSplit2[1]);
        auto dayOfTheWeek = ObjectDateTime::dayOfWeekAbbreviation(year, month, day, 0);
        string temp3Val = ".";
        string temp4Val = ".";
        string temp5Val = ".";
        if (temp2Len == temp3Len) {
            temp3Val = temp3List[j];
        }
        if (temp2Len == temp4Len) {
            temp4Val = temp4List[j];
        }
        if (temp2Len == temp5Len) {
            temp5Val = temp5List[j];
        }
        time2List[j] = WString::replace(time2List[j], ":00", "");
        time2List[j] = WString::strip(time2List[j]);
        time2List[j] = QString::fromStdString(time2List[j]).trimmed().toStdString();
        // TODO FIXME above and below
        sb += To::stringPadLeft(dayOfTheWeek + " " + time2List[j], 12);
        // std::cout << To::stringPadLeft(dayOfTheWeek + " " + time2List[j], 12) << "AAA" << std::endl;
        sb += "   ";
        sb += To::stringPadLeft(temp2List[j], 8);
        sb += To::stringPadLeft(temp3Val, 8);
        sb += To::stringPadLeft(temp4Val, 8);
        sb += To::stringPadLeft(temp5Val, 8);
        sb += GlobalVariables::newline;
    }
    return sb;
}
