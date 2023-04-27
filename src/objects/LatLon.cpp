// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "objects/LatLon.h"
#include <cmath>
#include <iostream>
#include "common/GlobalVariables.h"
#include "objects/WString.h"
#include "settings/UtilityLocation.h"
#include "util/To.h"
#include "util/Utility.h"
#include "util/UtilityCanvasProjection.h"
#include "util/UtilityIO.h"
#include "util/UtilityList.h"
#include "util/UtilityMath.h"
#include "util/UtilityString.h"

LatLon::LatLon()
    : latString{ To::string(0.0) }
    , lonString{ To::string(0.0) }
    , latNum{ 0.0 }
    , lonNum{ 0.0 }
{}

LatLon::LatLon(double x, double y)
    : latString{ To::string(x) }
    , lonString{ To::string(y) }
    , latNum{ x }
    , lonNum{ y }
{}

LatLon::LatLon(const string& x, const string& y)
    : latString{ x }
    , lonString{ y }
    , latNum{ To::Double(x) }
    , lonNum{ To::Double(y) }
{}

LatLon::LatLon(const string& temp)
    : latString{ UtilityString::substring(temp, 0, 4) }
    , lonString{ UtilityString::substring(temp, 4, 8) }
{
    latString = UtilityString::addPeriodBeforeLastTwoChars(latString);
    lonString = UtilityString::addPeriodBeforeLastTwoChars(lonString);
    auto tmpDbl = To::Double(lonString);
    if (tmpDbl < 40.00) {
        tmpDbl += 100;
        lonString = To::string(tmpDbl);
    }
    latNum = To::Double(latString);
    lonNum = To::Double(lonString);
}

LatLon::LatLon(const vector<float>& coords)
    : latString{ To::string(coords[0]) }
    , lonString{ To::string(coords[1]) }
    , latNum{ coords[0] }
    , lonNum{ coords[1] }
{}

double LatLon::lat() const {
    return latNum;
}

double LatLon::lon() const {
    return lonNum;
}

// void LatLon::setLon(double d) {
//    lonString = To::string(d);
//    lonNum = d;
// }

string LatLon::latStr() const {
    return latString;
}

string LatLon::lonStr() const {
    return lonString;
}

void LatLon::setLonStr(const string& s) {
    lonString = s;
    lonNum = To::Double(s);
}

double LatLon::dist(const LatLon& location2) const {
    const auto theta = lon() - location2.lon();
    auto dist = sin(UtilityMath::deg2rad(lat())) * sin(UtilityMath::deg2rad(location2.lat())) + cos(UtilityMath::deg2rad(lat())) * cos(UtilityMath::deg2rad(location2.lat())) * cos(UtilityMath::deg2rad(theta));
    dist = acos(dist);
    dist = UtilityMath::rad2deg(dist);
    dist = dist * 60.0 * 1.1515;
    return dist;
}

// used in UtilitySwoD1 and UtilityDownloadRadar
string LatLon::printSpaceSeparated() const {
    return latString + " " + lonString + " ";
}

// used by UtilityNexradDraw::initGeom for location dots
vector<double> LatLon::getProjection(const ProjectionNumbers& pn) const {
    return UtilityCanvasProjection::computeMercatorNumbersFromLatLon(*this, pn, -1.0);
}

ExternalPoint LatLon::asPoint() const {
    return {lat(), lon()};
}

vector<double> LatLon::asList() const {
    return {lat(), lon()};
}

LatLon LatLon::fromList(vector<double> coords) {
    return {coords[0], coords[1]};
}

LatLon LatLon::fromRadarSite(const string& radarSite) {
    const auto ridX = UtilityLocation::getRadarSiteX(radarSite);
    const auto ridY = UtilityLocation::getRadarSiteY(radarSite);
    const auto latNum = To::Double(ridX);
    const auto lonNum = -1.0 * To::Double(ridY);
    return {latNum, lonNum};
}

// FIXME TODO
string LatLon::latForNws() const {
    return QString::number(lat(), 'g', 4).toStdString();
}

string LatLon::lonForNws() const {
    return QString::number(lon(), 'g', 4).toStdString();
}

string LatLon::printPretty() const {
    const auto len = 7;
    return UtilityString::truncate(latString, len) + ", " + UtilityString::truncate(lonString, len) + " ";
}

string LatLon::storeWatchMcdLatLon(const string& html) {
    const auto coordinates = UtilityString::parseColumn(html, "([0-9]{8}).*?");
    string stringValue;
    for (const auto& coordinate : coordinates) {
        stringValue += getLatLonFromString(coordinate).printSpaceSeparated();
    }
    stringValue += ":";
    return WString::replace(stringValue, " :", ":");
}

// 36517623 is 3651 -7623
LatLon LatLon::getLatLonFromString(const string& latLonString) {
    const string latString{ UtilityString::substring(latLonString, 0, 4) };
    const string lonString{ UtilityString::substring(latLonString, 4, 8) };
    auto lat = To::Double(latString);
    auto lon = To::Double(lonString);
    lat /= 100.0;
    lon /= 100.0;
    if (lon < 40.0) {
        lon += 100.0;
    }
    return {lat, -1.0 * lon};
}

string LatLon::getLatLon(const string& number) {
    const auto html = UtilityIO::getHtml(GlobalVariables::nwsSPCwebsitePrefix + "/products/watch/wou" + number + ".html");
    return UtilityString::parseMultiLineLastMatch(html, GlobalVariables::pre2Pattern);
}

vector<double> LatLon::latLonListToListOfDoubles(const vector<LatLon>& latLons, const ProjectionNumbers& projectionNumbers) {
    vector<double> warningList;
    if (!latLons.empty()) {
        const auto startCoordinates = UtilityCanvasProjection::computeMercatorNumbersFromLatLon(latLons[0], projectionNumbers);
        warningList.push_back(startCoordinates[0]);
        warningList.push_back(startCoordinates[1]);
        for (auto index : range3(1, latLons.size(), 1)) {
            const auto coordinates = UtilityCanvasProjection::computeMercatorNumbersFromLatLon(latLons[index], projectionNumbers);
            warningList.push_back(coordinates[0]);
            warningList.push_back(coordinates[1]);
            warningList.push_back(coordinates[0]);
            warningList.push_back(coordinates[1]);
        }
        warningList.push_back(startCoordinates[0]);
        warningList.push_back(startCoordinates[1]);
    }
    return warningList;
}

vector<LatLon> LatLon::parseStringToLatLons(const string& stringOfNumbers, int multiplier, bool isWarning) {
    const auto listOfNumbers = WString::split(stringOfNumbers, " ");
    vector<double> x;
    vector<double> y;
    for (auto i : range(listOfNumbers.size())) {
        if (!isWarning) {
            if (i % 2 == 0) {
                y.push_back(To::Double(listOfNumbers[i]));
            } else {
                x.push_back(To::Double(listOfNumbers[i]) * -1.0);
            }
        } else {
            if (i % 2 == 0) {
                x.push_back(To::Double(listOfNumbers[i]) * multiplier);
            } else {
                y.push_back(To::Double(listOfNumbers[i]));
            }
        }
    }
    vector<LatLon> latLons;
    if (y.size() > 3 && x.size() > 3 && x.size() == y.size()) {
        for (auto index : range(x.size())) {
            latLons.emplace_back(y[index], x[index]);
        }
    }
    return latLons;
}

vector<LatLon> LatLon::parseStringToLatLonsForMcdLongPress(const string& stringOfNumbers, int multiplier, bool isWarning) {
    const auto listOfNumbers = WString::split(stringOfNumbers, " ");
    vector<double> x;
    vector<double> y;
    for (auto i : range(listOfNumbers.size())) {
        if (!isWarning) {
            if (i % 2 == 0) {
                y.push_back(To::Double(listOfNumbers[i]));
            } else {
                x.push_back(To::Double(listOfNumbers[i]) * 1.0);
            }
        } else {
            if (i % 2 == 0) {
                x.push_back(To::Double(listOfNumbers[i]) * multiplier);
            } else {
                y.push_back(To::Double(listOfNumbers[i]));
            }
        }
    }
    vector<LatLon> latLons;
    if (y.size() > 3 && x.size() > 3 && x.size() == y.size()) {
        for (int index : range(x.size())) {
            latLons.emplace_back(y[index], x[index]);
        }
    }
    return latLons;
}

string LatLon::getWatchLatLon(const string& number) {
    const auto html = UtilityIO::getHtml(GlobalVariables::nwsSPCwebsitePrefix + "/products/watch/wou" + number + ".html");
    return parseNwsPreSecondMatch(html);
}

string LatLon::parseNwsPreSecondMatch(const string& html) {
    const auto lines = WString::split(html, GlobalVariables::newline);
    auto preFound = false;
    auto endPreFound = false;
    auto preCount = 0;
    vector<string> modifiedLines;
    for (const auto& line : lines) {
        if (WString::contains(line, "<pre>")) {
            preFound = true;
            preCount += 1;
            continue;
        }
        if (WString::contains(line, "</pre>")) {
            if (preCount == 2) {
                endPreFound = true;
            }
        }
        if (preFound && preCount == 2 && !endPreFound) {
            modifiedLines.push_back(line);
        }
    }
    return WString::join(modifiedLines, GlobalVariables::newline);
}
