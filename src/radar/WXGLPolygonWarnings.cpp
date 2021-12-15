// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "radar/WXGLPolygonWarnings.h"
#include "objects/LatLon.h"
#include "objects/ObjectWarning.h"

QVector<float> WXGLPolygonWarnings::addGeneric(const ProjectionNumbers& projectionNumbers, const ObjectPolygonWarning * objectPolygonWarning) {
    auto html = objectPolygonWarning->storage.getValue();
    auto warnings = ObjectWarning::parseJson(html);
    QVector<float> warningList;
    for (const auto& w : warnings) {
        if (objectPolygonWarning->type1 == PolygonType::sps || objectPolygonWarning->type1 == PolygonType::mws || w.isCurrent) {
            auto latLons = w.getPolygonAsLatLons(-1);
            warningList += LatLon::latLonListToListOfDoubles(latLons, projectionNumbers);
        }
    }
    return warningList;
}

QVector<float> WXGLPolygonWarnings::add(const ProjectionNumbers& projectionNumbers, const PolygonType& type) {
    auto html = ObjectPolygonWarning::polygonDataByType[type]->getData();
    auto warnings = ObjectWarning::parseJson(html);
    QVector<float> warningList;
    for (const auto& w : warnings) {
        if (w.isCurrent) {
            auto latLons = w.getPolygonAsLatLons(-1);
            warningList += LatLon::latLonListToListOfDoubles(latLons, projectionNumbers);
        }
    }
    return warningList;
}

int WXGLPolygonWarnings::getCount(const PolygonType& type) {
    auto html = ObjectPolygonWarning::polygonDataByType[type]->getData();
    auto warningList = ObjectWarning::parseJson(html);
    int i = 0;
    for (const auto& s : warningList) {
        if (s.isCurrent) {
            i += 1;
        }
    }
    return i;
}
