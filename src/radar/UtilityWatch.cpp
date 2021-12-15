// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "radar/UtilityWatch.h"
#include <QString>
#include "external/ExternalPolygon.h"
#include "objects/ObjectPolygonWatch.h"
#include "util/To.h"
#include "util/UtilityList.h"

QVector<float> UtilityWatch::add(const ProjectionNumbers& projectionNumbers, PolygonType type) {
    QVector<float> warningList;
    auto prefToken = ObjectPolygonWatch::polygonDataByType[type]->latLonList.getValue();
    if (prefToken != "") {
        auto polygons = prefToken.split(":");
        for (const auto& polygon : polygons) {
            if (polygon != "") {
                auto latLons = LatLon::parseStringToLatLons(polygon, 1.0, false);
                warningList += LatLon::latLonListToListOfDoubles(latLons, projectionNumbers);
            }
        }
    }
    return warningList;
}

QString UtilityWatch::countString(PolygonType type) {
    auto prefToken = ObjectPolygonWatch::polygonDataByType[type]->latLonList.getValue();
    QString name;
    if (type == PolygonType::mcd) {
        name = "SPCMCD";
    } else if (type == PolygonType::watch) {
        name = "SPCWAT";
    } else if (type == PolygonType::watchTornado) {
        name = "SPCWAT_TORNADO";
    } else if (type == PolygonType::mpd) {
        name = "WPCMPD";
    }
    if (prefToken != "") {
        auto polygons = prefToken.split(":");
        return name + ": " + To::String(static_cast<int>(polygons.size()) - 1) + " ";
    }
    return "";
}

QString UtilityWatch::show(LatLon latLon, PolygonType type) {
    QStringList numberList;
    QString watchLatLon;
    if (type == PolygonType::watch) {
        watchLatLon = ObjectPolygonWatch::watchLatlonCombined.getValue();
        numberList = ObjectPolygonWatch::polygonDataByType[PolygonType::watch]->numberList.getValue().split(":");
    } else {
        numberList = ObjectPolygonWatch::polygonDataByType[type]->numberList.getValue().split(":");
        watchLatLon = ObjectPolygonWatch::polygonDataByType[type]->latLonList.getValue();
    }
    auto latLonsFromString = watchLatLon.split(":");
    auto notFound = true;
    QString text = "";
    for (auto z : UtilityList::range(latLonsFromString.size())) {
        if (latLonsFromString[z] != "") {
            auto latLons = LatLon::parseStringToLatLonsForMcdLongPress(latLonsFromString[z], -1.0, false);
            if (latLons.size() > 3) {
                auto contains = ExternalPolygon::polygonContainsPoint(latLon, latLons);
                if (contains && notFound) {
                    text = numberList[z];
                    notFound = false;
                }
            }
        }
    }
    return text;
}
