// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "util/ObjectCurrentConditions.h"
#include "common/GlobalVariables.h"
#include "util/ObjectMetar.h"
#include "util/UtilityIO.h"

ObjectCurrentConditions::ObjectCurrentConditions() {
}

ObjectCurrentConditions::ObjectCurrentConditions(const LatLon& latLon) {
    this->latLon = latLon;
}

void ObjectCurrentConditions::process() {
    QString stringValue = "";
    const auto objectMetar = ObjectMetar(latLon);
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
    stringValue += temperature;
    if (objectMetar.windChill != "0") {
        stringValue += "(" + windChill + ")";
    } else if (objectMetar.heatIndex != "0") {
        stringValue += "(" + heatIndex + ")";
    }
    stringValue += " / " + dewPoint + "(" + relativeHumidity + ")" + " - ";
    stringValue += seaLevelPressure + " - " + windDirection + " " + windSpeed;
    if (windGust != "") {
        stringValue += " G ";
    }
    stringValue += windGust + " mph" + " - " + visibility + " mi - " + condition;
    data = stringValue;
    iconUrl = objectMetar.icon;
    rawMetar = objectMetar.rawMetar;
    status = conditionsTimeString;
    formatCurrentConditions();
}

void ObjectCurrentConditions::formatCurrentConditions() {
    const QString separator = " - ";
    auto dataList = data.split(separator);
    QString topLineLocal = "";
    QString middleLineLocal = "";
    QString bottomLineLocal = "";
    if (dataList.size() > 4) {
        auto items = dataList[0].split("/");
        topLineLocal = dataList[4].replace("^ ", "") + " " + items[0] + dataList[2];
        middleLineLocal = items[1].replace("^ ", "") + separator + dataList[1] + separator + dataList[3];
        bottomLineLocal += status + " " + getObsFullName();
    }
    topLine = topLineLocal;
    middleLine = middleLineLocal;
    bottomLine = bottomLineLocal;
    summary = topLine + GlobalVariables::newline + middleLine;
}

QString ObjectCurrentConditions::getObsFullName() {
    const auto lines = UtilityIO::rawFileToStringArray(GlobalVariables::resDir + "stations_us4.txt");
    for (const auto& line : lines) {
        if (line.endsWith(obsStation)) {
            return line.split(",")[1];
        }
    }
    return "NA";
}
