// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "radar/WXGLNexradLevel3Tvs.h"
#include <string>
#include "external/ExternalGeodeticCalculator.h"
#include "external/ExternalGlobalCoordinates.h"
#include "objects/WString.h"
#include "util/To.h"
#include "util/UtilityString.h"
#include "radar/WXGLDownload.h"

void WXGLNexradLevel3Tvs::decode(const ProjectionNumbers& projectionNumbers, FileStorage& fileStorage) {
    const string productCode{"TVS"};
    WXGLDownload::getNidsTab(productCode, projectionNumbers.getRadarSite(), fileStorage);
    const auto retStr1 = fileStorage.level3TextProductMap[productCode];
    vector<double> stormList;
    if (retStr1.size() > 10) {
        const auto tvs = UtilityString::parseColumn(retStr1, "P  TVS(.{20})");
        for (const auto& t : tvs) {
            const auto stringValue = UtilityString::parse(t, ".{9}(.{7})");
            const auto items = WString::split(stringValue, "/");
            const auto degree = To::Int(WString::replace(items[0], " ", ""));
            const auto nm = To::Int(WString::replace(items[1], " ", ""));
            const auto start = ExternalGlobalCoordinates::withPn(projectionNumbers, true);
            const auto ec = ExternalGeodeticCalculator::calculateEndingGlobalCoordinates(start, degree, nm * 1852.0);
            stormList.push_back(ec.getLatitude());
            stormList.push_back(ec.getLongitude() * -1.0);
        }
    }
    fileStorage.tvsData = stormList;
}
