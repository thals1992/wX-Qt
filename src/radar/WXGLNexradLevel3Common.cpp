// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "radar/WXGLNexradLevel3Common.h"
#include "util/UtilityCanvasProjection.h"

QVector<float> WXGLNexradLevel3Common::drawLine(
    const ExternalGlobalCoordinates& startEc,
    const ProjectionNumbers& projectionNumbers,
    float startBearing,
    float distance
) {
    const auto start = ExternalGlobalCoordinates(startEc.getLatitude(), startEc.getLongitude());
    const auto startCoords = computeMercatorNumbersFromEc(startEc, projectionNumbers);
    const auto ec = ExternalGeodeticCalculator::calculateEndingGlobalCoordinates(start, startBearing, distance);
    return startCoords + computeMercatorNumbersFromEc(ec, projectionNumbers);
}

QVector<float> WXGLNexradLevel3Common::drawLine(
    QVector<float> startPoint,
    const ProjectionNumbers& projectionNumbers,
    const ExternalGlobalCoordinates& start,
    float startBearing,
    float distance
) {
    const auto ec = ExternalGeodeticCalculator::calculateEndingGlobalCoordinates(start, startBearing, distance);
    return startPoint + computeMercatorNumbersFromEc(ec, projectionNumbers);
}

QVector<float> WXGLNexradLevel3Common::computeMercatorNumbersFromEc(const ExternalGlobalCoordinates& ec, const ProjectionNumbers& projectionNumbers) {
    return UtilityCanvasProjection::computeMercatorNumbers(ec.getLatitude(), ec.getLongitude() * -1.0, projectionNumbers);
}
