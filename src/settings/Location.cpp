// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "settings/Location.h"
#include <algorithm>
#include "objects/WString.h"
#include "radar/Metar.h"
#include "settings/UtilityLocation.h"
#include "util/To.h"
#include "util/Utility.h"
#include "util/UtilityIO.h"
#include "util/UtilityList.h"
#include "util/UtilityString.h"

int Location::currentLocationIndex{0};
int Location::numberOfLocations{1};
vector<ObjectLocation> Location::locations;
ComboBox * Location::comboBox;

int Location::getNumLocations() {
    return numberOfLocations;
}

string Location::radar() {
    return locations[currentLocationIndex].getRadarSite();
}

string Location::radarSite() {
    return locations[currentLocationIndex].getRadarSite();
}

string Location::wfo() {
    return locations[currentLocationIndex].getWfo();
}

string Location::office() {
    return locations[currentLocationIndex].getWfo();
}

string Location::getRadarSite(int locationNumber) {
    return locations[locationNumber].getRadarSite();
}

string Location::getWfo(int locationNumber) {
    return locations[locationNumber].getWfo();
}

LatLon Location::getLatLon(int locationNumber) {
    return locations[locationNumber].getLatLon();
}

string Location::name() {
    return locations[currentLocationIndex].getName();
}

string Location::locationName() {
    return locations[currentLocationIndex].getName();
}

string Location::getName(int locationNumber) {
    return locations[locationNumber].getName();
}

LatLon Location::getLatLonCurrent() {
    return locations[currentLocationIndex].getLatLon();
}

vector<string> Location::listOfNames() {
    vector<string> names;
    std::transform(locations.cbegin(), locations.cend(), std::back_inserter(names), [] (const auto& location ) { return location.getName();} );
//    for (const auto& location : locations) {
//        names.push_back(location.getName());
//    }
    return names;
}

void Location::refreshLocationData() {
    initNumLocations();
    locations.clear();
    const auto locationString = Utility::readPref("CURRENT_LOC_FRAGMENT", "1");
    currentLocationIndex = To::Int(locationString) - 1;
    for (auto index : range(numberOfLocations)) {
        locations.emplace_back(index);
    }
}

void Location::initNumLocations() {
    numberOfLocations = To::Int(Utility::readPref("LOC_NUM_INT", "1"));
}

vector<string> Location::getWfoRadarSiteFromPoint(const LatLon& latLon) {
    const auto pointData = UtilityIO::getHtml("https://api.weather.gov/points/" + latLon.latForNws() + "," + latLon.lonForNws());
    // "cwa": "IWX",
    // "radarStation": "KGRR"
    const auto wfo = UtilityString::parse(pointData, "\"cwa\": \"(.*?)\"");
    auto radarStation = UtilityString::parse(pointData, "\"radarStation\": \"(.*?)\"");
    radarStation = UtilityString::getLastXChars(radarStation, 3);
    return {wfo, radarStation};
}

void Location::setCurrentLocation(int index) {
    currentLocationIndex = index;
    Utility::writePrefInt("CURRENT_LOC_FRAGMENT", index + 1);
}

vector<string> Location::save(const LatLon& latLon, const string& labelStr) {
    numberOfLocations += 1;
    const auto locNum = To::string(numberOfLocations);
    Utility::writePref("LOC" + locNum + "_X", latLon.latStr());
    Utility::writePref("LOC" + locNum + "_Y", latLon.lonStr());
    Utility::writePref("LOC" + locNum + "_LABEL", labelStr);
    Utility::writePref("LOC_NUM_INT", locNum);
    const auto wfoAndRadar = getWfoRadarSiteFromPoint(latLon);
    auto wfo = wfoAndRadar[0];
    auto radarSite = wfoAndRadar[1];
    // if (true) {
    if (wfo.empty()) {
        wfo = WString::toLower(UtilityLocation::getNearestOffice("WFO", latLon));
    }
    if (radarSite.empty()) {
        radarSite = UtilityLocation::getNearestOffice("RADAR", latLon);
    }
    Utility::writePref("RID" + locNum, WString::toUpper(radarSite));
    Utility::writePref("NWS" + locNum, WString::toUpper(wfo));
    refreshLocationData();
    return {locNum, "Saving location " + locNum + " as " + labelStr + " (" + latLon.latStr() + "," + latLon.lonStr() + ") " + "/" + " " + WString::toUpper(wfo) + "(" + WString::toUpper(radarSite) + ")"};
}

void Location::deleteItem(int index) {
    if (index > numberOfLocations) {
        return;
    }
    if (index == (numberOfLocations - 1)) {
        numberOfLocations -= 1;
    } else {
        for (auto i : range2(index + 1, numberOfLocations)) {
            const auto jStr = To::string(i + 1);
            const auto iStr = To::string(i);
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

void Location::setCurrentLocationStr(const string& indexAsString) {
    Utility::writePref("CURRENT_LOC_FRAGMENT", indexAsString);
    Utility::writePrefInt("LOC_NUM_INT", numberOfLocations);
    currentLocationIndex = To::Int(indexAsString) - 1;
}

vector<LatLon> Location::getListLatLons() {
    vector<LatLon> latLons;
    for (auto i : range(locations.size())) {
        latLons.push_back(getLatLon(i));
    }
    return latLons;
}

string Location::getObs() {
    return Metar::findClosestObservation(getLatLonCurrent()).name;
}

int Location::getCurrentLocation() {
    return currentLocationIndex;
}

void Location::setMainScreenComboBox() {
    comboBox->block();
    comboBox->setList(listOfNames());
    comboBox->setIndex(getCurrentLocation());
    comboBox->unblock();
}
