// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "radar/WXGLNexradLevel3Tvs.h"
#include "external/ExternalGeodeticCalculator.h"
#include "external/ExternalGlobalCoordinates.h"
#include "util/To.h"
#include "util/UtilityString.h"
#include "radar/WXGLDownload.h"

void WXGLNexradLevel3Tvs::decode(const ProjectionNumbers& projectionNumbers, FileStorage& fileStorage) {
    const QString productCode = "TVS";
    WXGLDownload::getNidsTab(productCode, projectionNumbers.radarSite, fileStorage);
    const auto retStr1 = fileStorage.level3TextProductMap[productCode];
    QVector<float> stormList;
    if (retStr1.size() > 10) {
        const auto tvs = UtilityString::parseColumn(retStr1, "P  TVS(.{20})");
        for (const auto& t : tvs) {
            const auto stringValue = UtilityString::parse(t, ".{9}(.{7})");
            auto items = stringValue.split("/");
            const auto degree = To::Int(items[0].replace(" ", ""));
            const auto nm = To::Int(items[1].replace(" ", ""));
            const auto start = ExternalGlobalCoordinates::withPn(projectionNumbers, true);
            const auto ec = ExternalGeodeticCalculator::calculateEndingGlobalCoordinates(start, degree, nm * 1852.0);
            stormList.push_back(ec.getLatitude());
            stormList.push_back(ec.getLongitude() * -1.0);
        }
    }
    fileStorage.tvsData = stormList;
}
