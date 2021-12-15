// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "util/ObjectMetar.h"
#include <QVector>
#include "common/GlobalVariables.h"
#include "objects/LatLon.h"
#include "util/UtilityIO.h"
#include "util/UtilityMath.h"
#include "radar/UtilityMetar.h"
#include "util/To.h"
#include "util/UtilityMetarConditions.h"
#include "util/UtilityString.h"
#include "util/UtilityTimeSunMoon.h"

QString ObjectMetar::obsClosestClass;

ObjectMetar::ObjectMetar(const LatLon& location) {
    decodeIcon = true;
    conditionsTimeString = "";
    obsClosest = UtilityMetar::findClosestObservation(location);
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
    rawMetar = UtilityString::parse(metarData, "ob: (.*?)" + GlobalVariables::newline);
    metarSkyCondition = UtilityString::toCamelCase(UtilityString::parse(metarData, "Sky conditions: (.*?)" + GlobalVariables::newline));
    metarWeatherCondition = UtilityString::toCamelCase(UtilityString::parse(metarData, "Weather: (.*?)" + GlobalVariables::newline));
    decodeIcon = true;
    condition = "";
    if (decodeIcon) {
        if (metarWeatherCondition == "" || metarWeatherCondition.contains("Inches Of Snow On Ground")) {
            condition = metarSkyCondition;
        } else {
            condition = metarWeatherCondition;
        }
        condition = condition.replace("; Lightning Observed", "");
        condition = condition.replace("; Cumulonimbus Clouds, Lightning Observed", "");
        if (condition == "Mist") {
            condition = "Fog/Mist";
        }
        icon = decodeIconFromMetar(condition, obsClosest);
        condition = condition.replace(";", " and");
    }
    metarDataList = metarData.split(GlobalVariables::newline);
    if (metarDataList.size() > 2) {
        auto localStatus = metarDataList[1].split("/");
        if (localStatus.size() > 1) {
            conditionsTimeString = localStatus[0] + " " + obsClosest.name;
        }
    }
    seaLevelPressure = changePressureUnits(seaLevelPressure);
    temperature = changeDegreeUnits(temperature);
    dewPoint = changeDegreeUnits(dewPoint);
    windChill = changeDegreeUnits(windChill);
    heatIndex = changeDegreeUnits(heatIndex);
    if (windSpeed == "") {
        windSpeed = "0";
    }
    if (condition == "") {
        condition = "NA";
    }
}

QString ObjectMetar::changePressureUnits(const QString& value) const {
    return value + " mb";
}

QString ObjectMetar::changeDegreeUnits(const QString& value) const {
    const int tmpNumber = To::Float(value);
    const auto tmpString = To::String(tmpNumber);
    return tmpString;
}

QString ObjectMetar::decodeIconFromMetar(const QString& condition, const RID& obs) const {
    // 2 element list with sunrise 1st, sunrise 2nd
    const auto sunTimes = UtilityTimeSunMoon::getSunriseSunsetFromObs(obs);
    const auto currentTime = QTime::currentTime();
    QString timeOfDay = "day";
    if (currentTime > sunTimes[1] || currentTime < sunTimes[0]) {
        timeOfDay = "night";
    }
    const auto conditionModified = condition.split(";")[0];
    const auto shortCondition = UtilityMetarConditions::iconFromCondition[conditionModified];
    return GlobalVariables::nwsApiUrl + "icons/land/" + timeOfDay + "/" + shortCondition + "?size=medium";
}
