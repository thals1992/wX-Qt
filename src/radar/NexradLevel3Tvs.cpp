// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "radar/NexradLevel3Tvs.h"
#include "external/ExternalGeodeticCalculator.h"
#include "objects/WString.h"
#include "util/To.h"
#include "util/UtilityString.h"
#include "radar/NexradDownload.h"
#include "radar/NexradLevel3TextProduct.h"

void NexradLevel3Tvs::decode(const ProjectionNumbers& projectionNumbers, FileStorage& fileStorage) {
    const auto rawData = NexradLevel3TextProduct::download("TVS", projectionNumbers.getRadarSite());
    vector<double> stormList;
    if (rawData.size() > 10) {
        const auto tvs = UtilityString::parseColumn(rawData, "P  TVS(.{20})");
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
