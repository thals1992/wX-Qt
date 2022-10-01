// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "util/UtilityCanvasProjection.h"
#include <cmath>
#include <numbers>

vector<double> UtilityCanvasProjection::computeMercatorNumbers(double lat, double lon, const ProjectionNumbers& projectionNumbers) {
    const auto test1 = 180.0 / std::numbers::pi * log(tan(std::numbers::pi / 4.0 + lat * (std::numbers::pi / 180.0) / 2.0));
    const auto test2 = 180.0 / std::numbers::pi * log(tan(std::numbers::pi / 4.0 + projectionNumbers.x() * (std::numbers::pi / 180.0) / 2.0));
    const auto y = -1.0 * (test1 - test2) * projectionNumbers.getOneDegreeScaleFactor() + projectionNumbers.yCenter;
    const auto x = -1.0 * (lon - projectionNumbers.y()) * projectionNumbers.getOneDegreeScaleFactor() + projectionNumbers.xCenter;
    return {x, y};
}

vector<double> UtilityCanvasProjection::computeMercatorNumbersFromLatLon(const LatLon& latLon, const ProjectionNumbers& projectionNumbers, int factor) {
    return computeMercatorNumbers(latLon.lat(), factor * latLon.lon(), projectionNumbers);
}
