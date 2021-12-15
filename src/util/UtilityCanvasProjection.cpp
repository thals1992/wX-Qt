// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "util/UtilityCanvasProjection.h"
#include <cmath>

QVector<float> UtilityCanvasProjection::computeMercatorNumbers(float lat, float lon, const ProjectionNumbers& projectionNumbers) {
    const float test1 = (180.0 / M_PI * log(tan(M_PI / 4 + lat * (M_PI / 180) / 2)));
    const float test2 = (180.0 / M_PI * log(tan(M_PI / 4 + projectionNumbers.xDbl() * (M_PI / 180) / 2)));
    const float y = -((test1 - test2) * projectionNumbers.getOneDegreeScaleFactor()) + projectionNumbers.yCenter;
    const float x = -((lon - projectionNumbers.yDbl()) * projectionNumbers.getOneDegreeScaleFactor()) + projectionNumbers.xCenter;
    return {x, y};
}

QVector<float> UtilityCanvasProjection::computeMercatorNumbersFromLatLon(const LatLon& latLon, const ProjectionNumbers& projectionNumbers) {
    return computeMercatorNumbers(latLon.lat, latLon.lon, projectionNumbers);
}
