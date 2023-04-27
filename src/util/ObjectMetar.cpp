// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "util/ObjectMetar.h"
#include <iostream>
#include "common/GlobalVariables.h"
#include "objects/LatLon.h"
#include "objects/ObjectDateTime.h"
#include "objects/WString.h"
#include "util/UtilityIO.h"
#include "util/UtilityMath.h"
#include "radar/Metar.h"
#include "util/To.h"
#include "util/UtilityMetarConditions.h"
#include "util/UtilityString.h"

ObjectMetar::ObjectMetar(const LatLon& location, int index)
    : obsClosest{ Metar::findClosestObservation(location, index) }
{}

void ObjectMetar::process() {
    conditionsTimeString = "";

    metarData = UtilityIO::getHtml(GlobalVariables::tgftpSitePrefix + "/data/observations/metar/decoded/" + obsClosest.name + ".TXT");
    temperature = UtilityString::parse(metarData, "Temperature: (.*?) F");
    dewPoint = UtilityString::parse(metarData, "Dew Point: (.*?) F");
    windDirection = UtilityString::parse(metarData, "Wind: from the (.*?) \\(.*? degrees\\) at .*? MPH ");
    windSpeed = UtilityString::parse(metarData, "Wind: from the .*? \\(.*? degrees\\) at (.*?) MPH ");
    windGust = UtilityString::parse(metarData, "Wind: from the .*? \\(.*? degrees\\) at .*? MPH \\(.*? KT\\) gusting to (.*?) MPH");
    seaLevelPressure = UtilityString::parse(metarData, "Pressure \\(altimeter\\): .*? in. Hg \\((.*?) hPa\\)");
    visibility = UtilityString::parse(metarData, "Visibility: (.*?) mile");
    relativeHumidity = UtilityString::parse(metarData, "Relative Humidity: (.*?)%");
    windChill = UtilityString::parse(metarData, "Windchill: (.*?) F");
    heatIndex = UtilityMath::heatIndex(temperature, relativeHumidity);
//    rawMetar = UtilityString::parse(metarData, "ob: (.*?)" + GlobalVariables::newline);
    metarSkyCondition = UtilityString::toCamelCase(UtilityString::parse(metarData, "Sky conditions: (.*?)" + GlobalVariables::newline));
    metarWeatherCondition = UtilityString::toCamelCase(UtilityString::parse(metarData, "Weather: (.*?)" + GlobalVariables::newline));
    condition = "";
    if (decodeIcon) {
        if (metarWeatherCondition.empty() || WString::contains(metarWeatherCondition, "Inches Of Snow On Ground")) {
            condition = metarSkyCondition;
        } else {
            condition = metarWeatherCondition;
        }
        condition = WString::replace(condition, "; Lightning Observed", "");
        condition = WString::replace(condition, "; Cumulonimbus Clouds, Lightning Observed", "");
        if (condition == "Mist") {
            condition = "Fog/Mist";
        }
        icon = decodeIconFromMetar(condition, obsClosest);
        condition = WString::replace(condition, ";", " and");
    }
    metarDataList = WString::split(metarData, GlobalVariables::newline);
    if (metarDataList.size() > 2) {
        auto localStatus = WString::split(metarDataList[1], "/");
        if (localStatus.size() > 1) {
            conditionsTimeString = localStatus[0] + " " + obsClosest.name;
            timeStringUtc = WString::strip(localStatus[1]);
        }
    }
    seaLevelPressure = changePressureUnits(seaLevelPressure);
    temperature = changeDegreeUnits(temperature);
    dewPoint = changeDegreeUnits(dewPoint);
    windChill = changeDegreeUnits(windChill);
    heatIndex = changeDegreeUnits(heatIndex);
    if (windSpeed.empty()) {
        windSpeed = "0";
    }
    if (condition.empty()) {
        condition = "NA";
    }
}

string ObjectMetar::changePressureUnits(const string& value) {
    return value + " mb";
}

string ObjectMetar::changeDegreeUnits(const string& value) {
    const auto tmpNumber = static_cast<int>(To::Double(value));
    return To::string(tmpNumber);
}

string ObjectMetar::decodeIconFromMetar(const string& condition, const RID& obs) {
    const auto timeOfDay = ObjectDateTime::isDaytime(obs) ? "day" : "night";
    const auto conditionModified = WString::split(condition, ";")[0];
    string shortCondition;
    if (UtilityMetarConditions::iconFromCondition.find(conditionModified) != UtilityMetarConditions::iconFromCondition.end()) {
        shortCondition = UtilityMetarConditions::iconFromCondition.at(conditionModified);
    } else {
        std::cout << "Condition not found ObjectMetar: " << conditionModified << std::endl;
    }
    return GlobalVariables::nwsApiUrl + "icons/land/" + timeOfDay + "/" + shortCondition + "?size=medium";
}
