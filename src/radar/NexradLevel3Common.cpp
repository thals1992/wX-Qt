// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "radar/NexradLevel3Common.h"
#include "util/UtilityCanvasProjection.h"

vector<double> NexradLevel3Common::drawLine(
    const ExternalGlobalCoordinates& startEc,
    const ProjectionNumbers& projectionNumbers,
    double startBearing,
    double distance
) {
    const auto start = ExternalGlobalCoordinates{startEc.getLatitude(), startEc.getLongitude()};
    const auto startCoords = computeMercatorNumbersFromEc(startEc, projectionNumbers);
    const auto ec = ExternalGeodeticCalculator::calculateEndingGlobalCoordinates(start, startBearing, distance);
    const auto coordinates = computeMercatorNumbersFromEc(ec, projectionNumbers);
    return {startCoords[0], startCoords[1], coordinates[0], coordinates[1]};
}

vector<double> NexradLevel3Common::drawLine(
    const vector<double>& startPoint,
    const ProjectionNumbers& projectionNumbers,
    const ExternalGlobalCoordinates& start,
    double startBearing,
    double distance
) {
    const auto ec = ExternalGeodeticCalculator::calculateEndingGlobalCoordinates(start, startBearing, distance);
    const auto coordinates = computeMercatorNumbersFromEc(ec, projectionNumbers);
    auto listToReturn = startPoint;
    listToReturn.push_back(coordinates[0]);
    listToReturn.push_back(coordinates[1]);
    return listToReturn;
}

vector<double> NexradLevel3Common::computeMercatorNumbersFromEc(const ExternalGlobalCoordinates& ec, const ProjectionNumbers& projectionNumbers) {
    return UtilityCanvasProjection::computeMercatorNumbers(ec.getLatitude(), ec.getLongitude() * -1.0, projectionNumbers);
}
