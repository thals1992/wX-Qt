// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include <QStringList>
#include "external/ExternalGeodeticCalculator.h"
#include "external/ExternalGlobalCoordinates.h"
#include "radar/WXGLNexradLevel3Common.h"
#include "radar/WXGLNexradLevel3WindBarbs.h"
#include "util/To.h"
#include "util/UtilityList.h"

QVector<float> WXGLNexradLevel3WindBarbs::decodeAndPlot(const ProjectionNumbers& projectionNumbers, bool isGust, FileStorage& fileStorage) {
    QVector<float> stormList;
    const auto arrWb = (!isGust) ? fileStorage.obsArrWb : fileStorage.obsArrWbGust;
    const float degreeShift = 180.00;
    const float arrowLength = 2.5;
    const float arrowSpacing = 3.0;
    const float barbLengthScaleFactor = 0.4;
    const float arrowBend = 60.0;
    const float nmScaleFactor = -1852.0;
    const float barbLength = 15.0;
    const float barbOffset = 0.0;
    for (const auto& windBarb : arrWb) {
        const auto metarArr = windBarb.split(":");
        auto angle = 0;
        auto length = 0;
        float locXDbl = 0.0;
        float locYDbl = 0.0;
        if (metarArr.size() > 3) {
            locXDbl = To::Float(metarArr[0]);
            locYDbl = To::Float(metarArr[1]);
            angle = To::Int(metarArr[2]);
            length = To::Int(metarArr[3]);
        }
        if (length > 4) {
            const float degree = 0.0;
            const float nm = 0.0;
            const float degree2 = angle;
            const float startLength = nm * nmScaleFactor;
            auto above50 = false;
            auto start = ExternalGlobalCoordinates(locXDbl, locYDbl);
            auto ec = ExternalGeodeticCalculator::calculateEndingGlobalCoordinates(start, degree, nm * nmScaleFactor * barbLengthScaleFactor);
            stormList += WXGLNexradLevel3Common::computeMercatorNumbersFromEc(ec, projectionNumbers);
            start = ExternalGlobalCoordinates(ec.getLatitude(), ec.getLongitude());
            ec = ExternalGeodeticCalculator::calculateEndingGlobalCoordinates(start, degree2 + degreeShift, barbLength * nmScaleFactor * barbLengthScaleFactor);
            const auto end = ExternalGlobalCoordinates(ec.getLatitude(), ec.getLongitude());
            stormList += WXGLNexradLevel3Common::computeMercatorNumbersFromEc(ec, projectionNumbers);
            int barbCount = length / 10;
            auto halfBarb = false;
            auto oneHalfBarb = false;
            if (((length - barbCount * 10) > 4 && length > 10) || length < 10) {
                halfBarb = true;
            }
            if (length < 10) {
                oneHalfBarb = true;
            }
            if (length > 49) {
                above50 = true;
                barbCount -= 4;
            } else {
                above50 = false;
            }
            auto index = 0;
            if (above50) {
                // initial angled line;
                ec = ExternalGeodeticCalculator::calculateEndingGlobalCoordinates(
                    end,
                    degree2,
                    barbOffset + startLength + index * arrowSpacing * nmScaleFactor * barbLengthScaleFactor);
                stormList += WXGLNexradLevel3Common::drawLine(ec, projectionNumbers, degree2 - arrowBend * 2.0, startLength + arrowLength * nmScaleFactor);
                // perpendicular line from main barb;
                ec = ExternalGeodeticCalculator::calculateEndingGlobalCoordinates(
                    end,
                    degree2,
                    barbOffset + startLength + -1.0 * arrowSpacing * nmScaleFactor * barbLengthScaleFactor);
                stormList += WXGLNexradLevel3Common::drawLine(ec, projectionNumbers, degree2 - 90.0, startLength + 0.80 * arrowLength * nmScaleFactor);
                // connecting line parallel to main barb;
                ec = ExternalGeodeticCalculator::calculateEndingGlobalCoordinates(
                    end,
                    degree2,
                    barbOffset + startLength + index * arrowSpacing * nmScaleFactor * barbLengthScaleFactor);
                stormList += WXGLNexradLevel3Common::drawLine(ec, projectionNumbers, degree2 - 180.0, startLength + 0.5 * arrowLength * nmScaleFactor);
                index += 1;
            }
            for ([[maybe_unused]] auto i : UtilityList::range2(index, barbCount)) {
                ec = ExternalGeodeticCalculator::calculateEndingGlobalCoordinates(
                    end,
                    degree2,
                    barbOffset + startLength + index * arrowSpacing * nmScaleFactor * barbLengthScaleFactor);
                stormList += WXGLNexradLevel3Common::drawLine(ec, projectionNumbers, degree2 - arrowBend * 2.0, startLength + arrowLength * nmScaleFactor);
                index += 1;
            }
            float halfBarbOffsetFudge = 0.0;
            if (oneHalfBarb) {
                halfBarbOffsetFudge = nmScaleFactor * 1.0;
            }
            if (halfBarb) {
                ec = ExternalGeodeticCalculator::calculateEndingGlobalCoordinates(
                    end,
                    degree2,
                    barbOffset + halfBarbOffsetFudge + startLength + index * arrowSpacing * nmScaleFactor * barbLengthScaleFactor);
                stormList += WXGLNexradLevel3Common::drawLine(ec, projectionNumbers, degree2 - arrowBend * 2.0, startLength + arrowLength / 2.0 * nmScaleFactor);
            }
        }
    }
    return stormList;
}
