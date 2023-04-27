// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "radar/NexradLevel3HailIndex.h"
#include "external/ExternalGeodeticCalculator.h"
#include "objects/WString.h"
#include "radar/NexradLevel3TextProduct.h"
#include "util/To.h"
#include "util/UtilityList.h"
#include "util/UtilityString.h"

const string NexradLevel3HailIndex::pattern{"(\\d+) "};

void NexradLevel3HailIndex::decode(const ProjectionNumbers& projectionNumbers, FileStorage& fileStorage) {
    const auto rawData = NexradLevel3TextProduct::download("HI", projectionNumbers.getRadarSite());
    const auto posn = UtilityString::parseColumn(rawData, "AZ/RAN(.*?)V");
    const auto hailPercent = UtilityString::parseColumn(rawData, "POSH/POH(.*?)V");
    const auto hailSize = UtilityString::parseColumn(rawData, "MAX HAIL SIZE(.*?)V");
    string posnStr;
    for (const auto& data : posn) {
        posnStr += WString::replace(data, "/", " ");
    }
    string hailPercentStr;
    for (const auto& data : hailPercent) {
        hailPercentStr += WString::replace(data, "/", " ");
    }
    hailPercentStr = WString::replace(hailPercentStr, "UNKNOWN", " 0 0 ");
    string hailSizeStr;
    for (const auto& data : hailSize) {
        hailSizeStr += WString::replace(data, "/", " ");
    }
    hailSizeStr = WString::replace(hailSizeStr, "UNKNOWN", " 0.00 ");
    hailSizeStr = WString::replace(hailSizeStr, "<0.50", " 0.49 ");
    posnStr = WString::replace(posnStr, "\\s+", " ");
    hailPercentStr = WString::replace(hailPercentStr, "\\s+", " ");
    const auto posnNumbers = UtilityString::parseColumn(posnStr, pattern);
    const auto hailPercentNumbers = UtilityString::parseColumn(hailPercentStr, pattern);
    const auto hailSizeNumbers = UtilityString::parseColumn(hailSizeStr, " ([0-9]{1}\\.[0-9]{2}) ");
    vector<double> stormList;
    if ((posnNumbers.size() == hailPercentNumbers.size()) && posnNumbers.size() > 1) {
        auto index = 0;
        for (auto data : range3(0, posnNumbers.size() - 2, 2)) {
            const auto hailSizeDbl = To::Double(hailSizeNumbers[index]);
            if (hailSizeDbl > 0.49 && (To::Int(hailPercentNumbers[data]) > 60 || To::Int(hailPercentNumbers[data + 1]) > 60)) {
                const auto degree = To::Int(posnNumbers[data]);
                const auto nm = To::Int(posnNumbers[data + 1]);
                const auto start = ExternalGlobalCoordinates::withPn(projectionNumbers, true);
                const auto ec = ExternalGeodeticCalculator::calculateEndingGlobalCoordinates(start, degree, nm * 1852.0);
                stormList.push_back(ec.getLatitude());
                stormList.push_back(ec.getLongitude() * -1.0);
                const auto baseSize = 0.015;
                auto indexForSizeLoop = 0;
                for (auto size : {0.99, 1.99, 2.99}) {
                    indexForSizeLoop += 1;
                    if (hailSizeDbl > size) {
                        stormList.push_back(ec.getLatitude() + 0.015 + (indexForSizeLoop) * baseSize);
                        stormList.push_back(ec.getLongitude() * -1.0);
                    }
                }
            }
            index += 1;
        }
    }
    fileStorage.hiData = stormList;
}
