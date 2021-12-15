// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "misc/UtilityHourlyOldApi.h"
#include "common/GlobalVariables.h"
#include "settings/Location.h"
#include "util/To.h"
#include "util/UtilityIO.h"
#include "util/UtilityList.h"
#include "util/UtilityString.h"
#include "util/UtilityTime.h"

QString UtilityHourlyOldApi::getHourlyString(int locNumber) {
    auto latLon  = Location::getLatLon(locNumber);
    auto html = UtilityIO::getHtml("https://forecast.weather.gov/MapClick.php?lat=" +
            latLon.latString + "&lon=" +
            latLon.lonString + "&FcstType=digitalDWML");
    auto header = To::StringPadLeft("Time", 14) + " "
        + To::StringPadLeft("Temp", 8)
        + To::StringPadLeft("Dew", 8)
        + To::StringPadLeft("Precip", 8)
        + To::StringPadLeft("Cloud", 8) 
        + GlobalVariables::newline;
    return GlobalVariables::newline + header + parseHourly(html);
}

QString UtilityHourlyOldApi::parseHourly(const QString& html) {
    QStringList regexpList = {
        "<temperature type=.hourly.*?>(.*?)</temperature>",
        "<temperature type=.dew point.*?>(.*?)</temperature>",
        "<time-layout.*?>(.*?)</time-layout>",
        "<probability-of-precipitation.*?>(.*?)</probability-of-precipitation>",
        "<cloud-amount type=.total.*?>(.*?)</cloud-amount>"
    };
    auto rawData = UtilityString::parseXmlExt(regexpList, html);
    auto temp2List = UtilityString::parseXmlValue(rawData[0]);
    auto temp3List = UtilityString::parseXmlValue(rawData[1]);
    auto time2List = UtilityString::parseXml(rawData[2], "start-valid-time");
    auto temp4List = UtilityString::parseXmlValue(rawData[3]);
    auto temp5List = UtilityString::parseXmlValue(rawData[4]);

    // need to handle: <value xsi:nil="true"/>
    QString sb = "";
    auto year = UtilityTime::getYear();
    auto temp2Len = temp2List.size();
    auto temp3Len = temp3List.size();
    auto temp4Len = temp4List.size();
    auto temp5Len = temp5List.size();

    for (auto j : UtilityList::range2(1, temp2Len)) {
        time2List[j] = UtilityString::replaceRegex(time2List[j], "-0[0-9]:00", "");
        time2List[j] = UtilityString::replaceRegex(time2List[j], "^.*?-", "");
        time2List[j] = time2List[j].replace("T", " ");
        time2List[j] = time2List[j].replace("00:00", "00");

        auto timeSplit = time2List[j].split(" ");
        auto timeSplit2 = timeSplit[0].split("-");
        auto month = To::Int(timeSplit2[0]);
        auto day = To::Int(timeSplit2[1]);
        QString dayOfTheWeek = "";
        dayOfTheWeek = UtilityTime::dayOfWeek(year, month, day);

        QString temp3Val = ".";
        QString temp4Val = ".";
        QString temp5Val = ".";

        if (temp2Len == temp3Len) {
            temp3Val = temp3List[j];
        }
        if (temp2Len == temp4Len) {
            temp4Val = temp4List[j];
        }
        if (temp2Len == temp5Len) {
            temp5Val = temp5List[j];
        }

        time2List[j] = time2List[j].replace(":00", "");
        time2List[j] = time2List[j].trimmed();

        sb += To::StringPadLeft(dayOfTheWeek + " " + time2List[j], 12);
        sb += "   ";
        sb += To::StringPadLeft(temp2List[j], 8);
        sb += To::StringPadLeft(temp3Val, 8);
        sb += To::StringPadLeft(temp4Val, 8);
        sb += To::StringPadLeft(temp5Val, 8);
        sb += GlobalVariables::newline;
    }
    return sb;
}
