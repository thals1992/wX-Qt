// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "util/CurrentConditions.h"
#include "common/GlobalVariables.h"
#include "objects/ObjectDateTime.h"
#include "objects/WString.h"
#include "util/ObjectMetar.h"
#include "util/UtilityIO.h"

string CurrentConditions::metarFileName{"stations_us4.txt"};
bool CurrentConditions::metarSitesInitialized{false};
vector<string> CurrentConditions::metarSites;

void CurrentConditions::process(const LatLon& latLon, int index) {
    this->latLon = latLon;
    string stringValue;
    auto objectMetar = ObjectMetar{latLon, index};
    objectMetar.process();
    obsStation = objectMetar.obsClosest.name;
    conditionsTimeString = objectMetar.conditionsTimeString;
    temperature = objectMetar.temperature + GlobalVariables::degreeSymbol;
    windChill = objectMetar.windChill + GlobalVariables::degreeSymbol;
    heatIndex = objectMetar.heatIndex + GlobalVariables::degreeSymbol;
    dewPoint = objectMetar.dewPoint + GlobalVariables::degreeSymbol;
    relativeHumidity = objectMetar.relativeHumidity + "%";
    seaLevelPressure = objectMetar.seaLevelPressure;
    windDirection = objectMetar.windDirection;
    windSpeed = objectMetar.windSpeed;
    windGust = objectMetar.windGust;
    visibility = objectMetar.visibility;
    condition = objectMetar.condition;
    timeStringUtc = objectMetar.timeStringUtc;
    stringValue += temperature;
    if (objectMetar.windChill != "0") {
        stringValue += "(" + windChill + ")";
    } else if (objectMetar.heatIndex != "0") {
        stringValue += "(" + heatIndex + ")";
    }
    stringValue += " / " + dewPoint + "(" + relativeHumidity + ")" + " - ";
    stringValue += seaLevelPressure + " - " + windDirection + " " + windSpeed;
    if (!windGust.empty()) {
        stringValue += " G ";
    }
    stringValue += windGust + " mph" + " - " + visibility + " mi - " + condition;
    data = stringValue;
    iconUrl = objectMetar.icon;
    status = conditionsTimeString;
    formatCurrentConditions();
}

void CurrentConditions::formatCurrentConditions() {
    const string separator = " - ";
    const auto dataList = WString::split(data, separator);
    string topLineLocal;
    string middleLineLocal;
    string bottomLineLocal;
    if (dataList.size() > 4) {
        const auto items = WString::split(dataList[0], "/");
        topLineLocal = WString::replace(dataList[4], "^ ", "") + " " + items[0] + dataList[2];
        middleLineLocal = WString::replace(items[1], "^ ", "") + separator + dataList[1] + separator + dataList[3];
        bottomLineLocal += status + GlobalVariables::newline + getObsFullName();
    }
    topLine = topLineLocal;
    middleLine = middleLineLocal;
    bottomLine = bottomLineLocal;
    summary = topLine + GlobalVariables::newline + middleLine;
}

void CurrentConditions::loadMetarData() {
    if (!metarSitesInitialized) {
        metarSitesInitialized = true;
        metarSites = UtilityIO::rawFileToStringArray(GlobalVariables::resDir + metarFileName);
    }
}

string CurrentConditions::getObsFullName() const {
    loadMetarData();
    for (const auto& line : metarSites) {
        if (WString::endsWith(line, obsStation)) {
            return WString::split(line, ",")[1];
        }
    }
    return "NA";
}

// compare the timestamp in the metar to the current time
// if older than a certain amount, download the 2nd closest site and process
void CurrentConditions::timeCheck() {
    const auto obsTime = ObjectDateTime::fromObs(timeStringUtc);
    const auto currentTime = ObjectDateTime::getCurrentTimeInUTC();
    const auto isTimeCurrent = ObjectDateTime::timeDifference(currentTime, obsTime.get(), 120);
    if (!isTimeCurrent) {
        process(latLon, 1);
    }
}
