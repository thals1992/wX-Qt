// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "objects/LatLon.h"
#include <cmath>
#include <iostream>
#include "common/GlobalVariables.h"
#include "util/To.h"
#include "util/Utility.h"
#include "util/UtilityCanvasProjection.h"
#include "util/UtilityIO.h"
#include "util/UtilityList.h"
#include "util/UtilityMath.h"
#include "util/UtilityString.h"

LatLon::LatLon() {
    latString = To::String(0.0);
    lonString = To::String(0.0);
    lat = 0.0;
    lon = 0.0;
    distance = 0;
}

LatLon::LatLon(double x, double y) {
    latString = To::String(x);
    lonString = To::String(y);
    lat = x;
    lon = y;
    distance = 0;
}

LatLon::LatLon(float x, float y) {
    latString = To::String(x);
    lonString = To::String(y);
    lat = x;
    lon = y;
    distance = 0;
}

LatLon::LatLon(const QString& x, const QString& y) {
    latString = x;
    lonString = y;
    lat = To::Double(x);
    lon = To::Double(y);
    distance = 0;
}

LatLon::LatLon(const QString& temp) {
    latString = UtilityString::substring(temp, 0, 4);
    lonString = UtilityString::substring(temp, 4, 8);
    latString = UtilityString::addPeriodBeforeLastTwoChars(latString);
    lonString = UtilityString::addPeriodBeforeLastTwoChars(lonString);
    auto tmpDbl = To::Float(lonString);
    if (tmpDbl < 40.00) {
        tmpDbl += 100;
        lonString = To::String(tmpDbl);
    }
    lat = To::Float(latString);
    lon = To::Float(lonString);
}

LatLon::LatLon(const QVector<float>& coords) {
    latString = To::String(coords[0]);
    lonString = To::String(coords[1]);
    lat = coords[0];
    lon = coords[1];
    distance = 0;
}

float LatLon::dist(LatLon location2) const {
    const float theta = lon - location2.lon;
    float dist = sin(UtilityMath::deg2rad(lat)) * sin(UtilityMath::deg2rad(location2.lat)) + cos(UtilityMath::deg2rad(lat)) * cos(UtilityMath::deg2rad(location2.lat)) * cos(UtilityMath::deg2rad(theta));
    dist = acos(dist);
    dist = UtilityMath::rad2deg(dist);
    dist = dist * 60.0 * 1.1515;
    return dist;
}

// used in UtilitySwoD1 and UtilityDownloadRadar
QString LatLon::printSpaceSeparated() const {
    return latString + " " + lonString + " ";
}

ExternalPoint LatLon::asPoint() const {
    return ExternalPoint(lat, lon);
}

QVector<float> LatLon::asList() const {
    return {static_cast<float>(lat), static_cast<float>(lon)};
}

LatLon LatLon::fromList(QVector<float> coords) {
    return LatLon(coords[0], coords[1]);
}

LatLon LatLon::fromRadarSite(const QString& radarSite) {
    const auto ridX = Utility::getRadarSiteX(radarSite);
    const auto ridY = Utility::getRadarSiteY(radarSite);
    const auto latNum = To::Double(ridX);
    const auto lonNum = -1.0 * To::Double(ridY);
    return LatLon(latNum, lonNum);
}

// FIXME TODO
QString LatLon::latForNws() const {
    return QString::number(lat, 'g', 4);
}

QString LatLon::lonForNws() const {
    return QString::number(lon, 'g', 4);
}

QString LatLon::printPretty() const {
    auto len = 7;
    return UtilityString::truncate(latString, len) + ", " + UtilityString::truncate(lonString, len) + " ";
}

QString LatLon::storeWatchMcdLatLon(const QString& html) {
    const auto coordinates = UtilityString::parseColumn(html, "([0-9]{8}).*?");
    QString stringValue;
    for (const auto& coor : coordinates) {
        stringValue += getLatLonFromString(coor).printSpaceSeparated();
    }
    stringValue += ":";
    return stringValue.replace(" :", ":");
}

// 36517623 is 3651 -7623
LatLon LatLon::getLatLonFromString(const QString& latLonString) {
    const auto latString = latLonString.left(4);
    const auto lonString = latLonString.right(4);
    auto lat = To::Float(latString);
    auto lon = To::Float(lonString);
    lat /= 100.0;
    lon /= 100.0;
    if (lon < 40.0) {
        lon += 100.0;
    }
    return LatLon(lat, -1.0f * lon);
}

QString LatLon::getLatLon(const QString& number) {
    const auto html = UtilityIO::getHtml(GlobalVariables::nwsSPCwebsitePrefix + "/products/watch/wou" + number + ".html");
    return UtilityString::parseMultiLineLastMatch(html, GlobalVariables::pre2Pattern);
}

QVector<float> LatLon::latLonListToListOfDoubles(const QVector<LatLon>& latLons, const ProjectionNumbers& projectionNumbers) {
    QVector<float> warningList;
    if (latLons.size() > 0) {
        auto startCoordinates = UtilityCanvasProjection::computeMercatorNumbersFromLatLon(latLons[0], projectionNumbers);
        warningList += startCoordinates;
        for (auto index : UtilityList::range2(1, latLons.size())) {
            auto coordinates = UtilityCanvasProjection::computeMercatorNumbersFromLatLon(latLons[index], projectionNumbers);
            warningList += coordinates;
            warningList += coordinates;
        }
        warningList += startCoordinates;
    }
    return warningList;
}

QVector<LatLon> LatLon::parseStringToLatLons(const QString& stringOfNumbers, float multiplier, bool isWarning) {
    const auto listOfNumbers = stringOfNumbers.split(" ");
    QVector<float> x;
    QVector<float> y;
    for (auto i : UtilityList::range(listOfNumbers.size())) {
        if (!isWarning) {
            if (i % 2 == 0) {
                y.push_back(To::Float(listOfNumbers[i]));
            } else {
                x.push_back(To::Float(listOfNumbers[i]) * -1.0);
            }
        } else {
            if (i % 2 == 0) {
                x.push_back(To::Float(listOfNumbers[i]) * multiplier);
            } else {
                y.push_back(To::Float(listOfNumbers[i]));
            }
        }
    }
    QVector<LatLon> latLons;
    if (y.size() > 3 && x.size() > 3 && x.size() == y.size()) {
        for (auto index : UtilityList::range(x.size())) {
            const LatLon latLon(y[index], x[index]);
            latLons.push_back(latLon);
        }
    }
    return latLons;
}

QVector<LatLon> LatLon::parseStringToLatLonsForMcdLongPress(const QString& stringOfNumbers, float multiplier, bool isWarning) {
    const auto listOfNumbers = stringOfNumbers.split(" ");
    QVector<float> x;
    QVector<float> y;
    for (auto i : UtilityList::range(listOfNumbers.size())) {
        if (!isWarning) {
            if (i % 2 == 0) {
                y.push_back(To::Float(listOfNumbers[i]));
            } else {
                x.push_back(To::Float(listOfNumbers[i]) * 1.0);
            }
        } else {
            if (i % 2 == 0) {
                x.push_back(To::Float(listOfNumbers[i]) * multiplier);
            } else {
                y.push_back(To::Float(listOfNumbers[i]));
            }
        }
    }
    QVector<LatLon> latLons;
    if (y.size() > 3 && x.size() > 3 && x.size() == y.size()) {
        for (int index : UtilityList::range(x.size())) {
            const LatLon latLon(y[index], x[index]);
            latLons.push_back(latLon);
        }
    }
    return latLons;
}
