// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "radar/WXGLNexradLevel3StormInfo.h"
#include "radar/WXGLDownload.h"
#include "radar/WXGLNexradLevel3Common.h"
#include "util/To.h"
#include "util/UtilityList.h"
#include "util/UtilityString.h"

void WXGLNexradLevel3StormInfo::decode(const ProjectionNumbers& projectionNumbers, FileStorage& fileStorage) {
    const QString productCode = "STI";
    WXGLDownload::getNidsTab(productCode, projectionNumbers.radarSite, fileStorage);
    const auto retStr1 = fileStorage.level3TextProductMap[productCode];
    QVector<float> stormList;
    if (retStr1.size() > 10) {
        auto position = UtilityString::parseColumn(retStr1, "AZ/RAN(.*?)V");
        auto motion = UtilityString::parseColumn(retStr1, "MVT(.*?)V");
        QString posnStr = "";
        for (auto& pos : position) {
            posnStr += pos.replace("/", " ");
        }
        QString motionStr = "";
        for (auto& m : motion) {
            motionStr += m.replace("/", " ");
        }
        motionStr = motionStr.replace("NEW", "  0  0  ");
        QString reg = "(\\d+) ";
        auto posnNumbers = UtilityString::parseColumn(posnStr, reg);
        auto motNumbers = UtilityString::parseColumn(motionStr, reg);
        float sti15IncrLen = 0.40;
        if ((posnNumbers.size() == motNumbers.size()) && posnNumbers.size() > 1) {
            const auto degreeShift = 180;
            const float arrowLength = 2.0;
            const float arrowBend = 20.0;
            for (auto index : UtilityList::range3(0, posnNumbers.size() - 2, 2)) {
                const auto degree = To::Int(posnNumbers[index]);
                const auto nm = To::Int(posnNumbers[index + 1]);
                const auto degree2 = To::Float(motNumbers[index]);
                const auto nm2 = To::Int(motNumbers[index + 1]);
                auto start = ExternalGlobalCoordinates::withPn(projectionNumbers, true);
                auto ec = ExternalGeodeticCalculator::calculateEndingGlobalCoordinates(start, degree, nm * 1852.0);
                stormList += WXGLNexradLevel3Common::computeMercatorNumbersFromEc(ec, projectionNumbers);
                start = ExternalGlobalCoordinates(ec.getLatitude(), ec.getLongitude());
                ec = ExternalGeodeticCalculator::calculateEndingGlobalCoordinates(start, degree2 + degreeShift, nm2 * 1852.0);
                const auto tmpCoords = WXGLNexradLevel3Common::computeMercatorNumbersFromEc(ec, projectionNumbers);
                stormList += tmpCoords;
                QVector<ExternalGlobalCoordinates> ecArr;
                QVector<LatLon> latLons;
                for (auto z : {0, 1, 2, 3}) {
                    ecArr.push_back(ExternalGeodeticCalculator::calculateEndingGlobalCoordinates(start, degree2 + degreeShift, nm2 * 1852.0 * z * 0.25));
                    latLons.push_back(LatLon::fromList(WXGLNexradLevel3Common::computeMercatorNumbersFromEc(ecArr[z], projectionNumbers)));
                }
                auto endPoint = tmpCoords;
                if (nm2 > 0) {
                    start = ExternalGlobalCoordinates(ec.getLatitude(), ec.getLongitude());
                    for (const float b : {degree2 + arrowBend, degree2 - arrowBend}) {
                        stormList += WXGLNexradLevel3Common::drawLine(endPoint, projectionNumbers, start, b, arrowLength * 1852.0);
                    }
                    // 15,30,45 min ticks;
                    float stormTrackTickMarkAngleOff90 = 30.0;
                    for (auto index2 : {0, 1, 2, 3}) {
                        const QVector<float> angles = {
                            static_cast<float>(degree2 - (90.0 + stormTrackTickMarkAngleOff90)),
                            static_cast<float>(degree2 + (90.0 - stormTrackTickMarkAngleOff90)),
                            static_cast<float>(degree2 - (90.0 - stormTrackTickMarkAngleOff90)),
                            static_cast<float>(degree2 + (90.0 + stormTrackTickMarkAngleOff90))
                        };
                        for (const float d : angles) {
                            stormList += drawTickMarks(latLons[index2], projectionNumbers, ecArr[index2], d, arrowLength * 1852.0 * sti15IncrLen);
                        }
                    }
                }
            }
        }
        fileStorage.stiData = stormList;
    }
}

QVector<float> WXGLNexradLevel3StormInfo::drawTickMarks(
    const LatLon& startPoint,
    const ProjectionNumbers& projectionNumbers,
    const ExternalGlobalCoordinates& ecArr,
    float startBearing,
    float distance
) {
    auto items = startPoint.asList();
    const auto start = ExternalGlobalCoordinates(ecArr.getLatitude(), ecArr.getLongitude());
    const auto ec = ExternalGeodeticCalculator::calculateEndingGlobalCoordinates(start, startBearing, distance);
    items += WXGLNexradLevel3Common::computeMercatorNumbersFromEc(ec, projectionNumbers);
    return items;
}
