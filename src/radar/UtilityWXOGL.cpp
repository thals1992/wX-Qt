// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "radar/UtilityWXOGL.h"
#include <QVector>
#include "external/ExternalPolygon.h"
#include "objects/ObjectPolygonWarning.h"
#include "objects/ObjectWarning.h"

QString UtilityWXOGL::showTextProducts(const LatLon& latLon) {
    // QString warningChunk = MyApplication::severeDashboardTor.getValue() + MyApplication::severeDashboardTst.getValue() + MyApplication::severeDashboardFfw.getValue();
    QString warningChunk;
    for (const auto& data : ObjectPolygonWarning::polygonList) {
        auto it = ObjectPolygonWarning::polygonDataByType[data];
        if (it->isEnabled) {
            warningChunk += it->storage.getValue();
        }
    }
    auto warnings = ObjectWarning::parseJson(warningChunk);
    QString urlToOpen = "";
    auto notFound = true;
    for (const auto& w : warnings) {
        auto latLons = w.getPolygonAsLatLons(1);
        if (latLons.size() > 0) {
            auto contains = ExternalPolygon::polygonContainsPoint(latLon, latLons);
            if (contains && notFound) {
                urlToOpen = w.getUrl();
                notFound = false;
            }
        }
    }
    return urlToOpen;
}
