// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "settings/Location.h"
#include "radar/UtilityMetar.h"
#include "settings/UtilityLocation.h"
#include "util/To.h"
#include "util/Utility.h"
#include "util/UtilityIO.h"
#include "util/UtilityList.h"
#include "util/UtilityString.h"

int Location::currentLocationIndex = 0;
int Location::numberOfLocations = 1;
QVector<ObjectLocation> Location::locations;

int Location::getNumLocations() {
    return numberOfLocations;
}

QString Location::radar() {
    return locations[currentLocationIndex].rid;
}

QString Location::radarSite() {
    return locations[currentLocationIndex].rid;
}

QString Location::wfo() {
    return locations[currentLocationIndex].wfo;
}

QString Location::office() {
    return locations[currentLocationIndex].wfo;
}

QString Location::getRadarSite(int locationNumber) {
    return locations[locationNumber].rid;
}

QString Location::getWfo(int locationNumber) {
    return locations[locationNumber].wfo;
}

LatLon Location::getLatLon(int locationNumber) {
    return LatLon(getX(locationNumber), getY(locationNumber));
}

float Location::x() {
    return To::Float(locations[currentLocationIndex].lat);
}

float Location::getX(int locationNumber) {
    return To::Float(locations[locationNumber].lat);
}

float Location::y() {
    return To::Float(locations[currentLocationIndex].lon);
}

QString Location::name() {
    return locations[currentLocationIndex].name;
}

QString Location::locationName() {
    return locations[currentLocationIndex].getName();
}

QString Location::getName(int locationNumber) {
    return locations[locationNumber].name;
}

float Location::getY(int locationNumber) {
    return To::Float(locations[locationNumber].lon);
}

LatLon Location::getLatLonCurrent() {
    return LatLon(x(), y());
}

LatLon Location::getLatLonCurrentByString() {
    const auto locationNumber = To::Int(Utility::readPref("CURRENT_LOC_FRAGMENT", "1")) - 1;
    return LatLon(getX(locationNumber), getY(locationNumber));
}

QStringList Location::listOfNames() {
    QStringList names;
    for (const auto& location : locations) {
        names.push_back(location.name);
    }
    return names;
}

void Location::refreshLocationData() {
    initNumLocations();
    locations.clear();
    const auto locationString = Utility::readPref("CURRENT_LOC_FRAGMENT", "1");
    currentLocationIndex = To::Int(locationString) - 1;
    for (auto index : UtilityList::range(numberOfLocations)) {
        locations.push_back(ObjectLocation(index));
    }
}

void Location::initNumLocations() {
    numberOfLocations = To::Int(Utility::readPref("LOC_NUM_INT", "1"));
}

QStringList Location::getWfoRadarSiteFromPoint(const LatLon& latLon) {
    const auto pointData = UtilityIO::getHtml("https://api.weather.gov/points/" + latLon.latForNws() + "," + latLon.lonForNws());
    // "cwa": "IWX",
    // "radarStation": "KGRR"
    const auto wfo = UtilityString::parse(pointData, "\"cwa\": \"(.*?)\"");
    auto radarStation = UtilityString::parse(pointData, "\"radarStation\": \"(.*?)\"");
    radarStation = UtilityString::getLastXChars(radarStation, 3);
    return {wfo, radarStation};
}

void Location::changeLocationByIndex(int index) {
    currentLocationIndex = index;
    Utility::writePrefInt("CURRENT_LOC_FRAGMENT", index + 1);
}

QStringList Location::save(LatLon latLon, const QString& labelStr) {
    numberOfLocations += 1;
    const auto locNum = To::String(numberOfLocations);
    Utility::writePref("LOC" + locNum + "_X", latLon.latString);
    Utility::writePref("LOC" + locNum + "_Y", latLon.lonString);
    Utility::writePref("LOC" + locNum + "_LABEL", labelStr);
    Utility::writePref("LOC_NUM_INT", locNum);
    QString wfo = "";
    QString radarSite = "";
    const auto wfoAndRadar = getWfoRadarSiteFromPoint(latLon);
    wfo = wfoAndRadar[0];
    radarSite = wfoAndRadar[1];
    if (wfo == "") {
        wfo = UtilityLocation::getNearestOffice("WFO", latLon).toLower();
    }
    if (radarSite == "") {
        radarSite = UtilityLocation::getNearestOffice("RADAR", latLon);
    }
    Utility::writePref("RID" + locNum, radarSite.toUpper());
    Utility::writePref("NWS" + locNum, wfo.toUpper());
    refreshLocationData();
    return {locNum, "Saving location " + locNum + " as " + labelStr + " (" + latLon.latString + "," + latLon.lonString + ") " + "/" + " " + wfo.toUpper() + "(" + radarSite.toUpper() + ")"};
}

void Location::deleteItem(int index) {
    if (index > numberOfLocations) {
        return;
    }
    if (index == (numberOfLocations - 1)) {
        numberOfLocations -= 1;
    } else {
        for (auto i : UtilityList::range2(index + 1, numberOfLocations)) {
            const auto jStr = To::String(i + 1);
            const auto iStr = To::String(i);
            const auto x = Utility::readPref("LOC" + jStr + "_X", "");
            const auto y = Utility::readPref("LOC" + jStr + "_Y", "");
            const auto name = Utility::readPref("LOC" + jStr + "_LABEL", "");
            const auto wfo = Utility::readPref("NWS" + jStr, "");
            const auto rid = Utility::readPref("RID" + jStr, "");
            Utility::writePref("LOC" + iStr + "_X", x);
            Utility::writePref("LOC" + iStr + "_Y", y);
            Utility::writePref("LOC" + iStr + "_LABEL", name);
            Utility::writePref("NWS" + iStr, wfo);
            Utility::writePref("RID" + iStr, rid);
        }
        numberOfLocations -= 1;
    }
    setCurrentLocationStr("1");
    refreshLocationData();
}

void Location::setCurrentLocationStr(const QString& indexAsString) {
    Utility::writePref("CURRENT_LOC_FRAGMENT", indexAsString);
    Utility::writePrefInt("LOC_NUM_INT", numberOfLocations);
    currentLocationIndex = To::Int(indexAsString) - 1;
}

QVector<LatLon> Location::getListLatLons() {
    QVector<LatLon> latLons;
    for (auto i : UtilityList::range(locations.size())) {
        latLons.push_back(getLatLon(i));
    }
    return latLons;
}

QString Location::getObs() {
    return UtilityMetar::findClosestObservation(getLatLonCurrent()).name;
}

int Location::getCurrentLocation() {
    return currentLocationIndex;
}
