// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "radar/UtilityWatch.h"
#include "external/ExternalPolygon.h"
#include "objects/ObjectPolygonWatch.h"
#include "objects/WString.h"
#include "util/UtilityList.h"

vector<double> UtilityWatch::add(const ProjectionNumbers& projectionNumbers, PolygonType type) {
    vector<double> warningList;
    const auto prefToken = ObjectPolygonWatch::polygonDataByType[type]->latLonList.getValue();
    if (!prefToken.empty()) {
        const auto polygons = WString::split(prefToken, ":");
        for (const auto& polygon : polygons) {
            const auto latLons = LatLon::parseStringToLatLons(polygon, 1.0, false);
            const auto b = LatLon::latLonListToListOfDoubles(latLons, projectionNumbers);
            addAll(warningList, b);
        }
    }
    return warningList;
}

string UtilityWatch::show(const LatLon& latLon, PolygonType type) {
    vector<string> numberList;
    string watchLatLon;
    if (type == Watch) {
        watchLatLon = ObjectPolygonWatch::watchLatlonCombined.getValue();
        numberList = WString::split(ObjectPolygonWatch::polygonDataByType[Watch]->numberList.getValue(), ":");
    } else {
        numberList = WString::split(ObjectPolygonWatch::polygonDataByType[type]->numberList.getValue(), ":");
        watchLatLon = ObjectPolygonWatch::polygonDataByType[type]->latLonList.getValue();
    }
    const auto latLonsFromString = WString::split(watchLatLon, ":");
    auto notFound = true;
    string text;
    for (auto z : range(latLonsFromString.size())) {
        if (!latLonsFromString[z].empty()) {
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
