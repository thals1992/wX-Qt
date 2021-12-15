// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "radar/WXGLNexradLevel3HailIndex.h"
#include "external/ExternalGeodeticCalculator.h"
#include "external/ExternalGlobalCoordinates.h"
#include "radar/WXGLDownload.h"
#include "util/To.h"
#include "util/UtilityList.h"
#include "util/UtilityString.h"


const QString WXGLNexradLevel3HailIndex::pattern = "(\\d+) ";

void WXGLNexradLevel3HailIndex::decode(const ProjectionNumbers& projectionNumbers, FileStorage& fileStorage) {
    const QString productCode = "HI";
    WXGLDownload::getNidsTab(productCode, projectionNumbers.radarSite, fileStorage);
    const auto hailData = fileStorage.level3TextProductMap[productCode];
    auto posn = UtilityString::parseColumn(hailData, "AZ/RAN(.*?)V");
    auto hailPercent = UtilityString::parseColumn(hailData, "POSH/POH(.*?)V");
    auto hailSize = UtilityString::parseColumn(hailData, "MAX HAIL SIZE(.*?)V");
    QString posnStr;
    for (auto data : posn) {
        posnStr += data.replace("/", " ");
    }
    QString hailPercentStr;
    for (auto data : hailPercent) {
        hailPercentStr += data.replace("/", " ");
    }
    hailPercentStr = hailPercentStr.replace("UNKNOWN", " 0 0 ");
    QString hailSizeStr;
    for (auto data : hailSize) {
        hailSizeStr += data.replace("/", " ");
    }
    hailSizeStr = hailSizeStr.replace("UNKNOWN", " 0.00 ");
    hailSizeStr = hailSizeStr.replace("<0.50", " 0.49 ");
    posnStr = posnStr.replace("\\s+", " ");
    hailPercentStr = hailPercentStr.replace("\\s+", " ");
    const auto posnNumbers = UtilityString::parseColumn(posnStr, pattern);
    const auto hailPercentNumbers = UtilityString::parseColumn(hailPercentStr, pattern);
    const auto hailSizeNumbers = UtilityString::parseColumn(hailSizeStr, " ([0-9]{1}\\.[0-9]{2}) ");
    QVector<float> stormList;
    if ((posnNumbers.size() == hailPercentNumbers.size()) && posnNumbers.size() > 1) {
        auto index = 0;
        for (auto data : UtilityList::range3(0, posnNumbers.size() - 2, 2)) {
            auto hailSizeDbl = To::Double(hailSizeNumbers[index]);
            if (hailSizeDbl > 0.49 && (To::Int(hailPercentNumbers[data]) > 60 || To::Int(hailPercentNumbers[data + 1]) > 60)) {
                const auto degree = To::Int(posnNumbers[data]);
                const auto nm = To::Int(posnNumbers[data + 1]);
                const auto start = ExternalGlobalCoordinates::withPn(projectionNumbers, true);
                const auto ec = ExternalGeodeticCalculator::calculateEndingGlobalCoordinates(start, degree, nm * 1852.0);
                stormList.push_back(ec.getLatitude());
                stormList.push_back(ec.getLongitude() * -1.0);
                auto baseSize = 0.015;
                auto indexForSizeLoop = 0;
                for (const auto& size : {0.99f, 1.99f, 2.99f}) {
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
