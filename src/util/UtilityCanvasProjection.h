// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef UTILITYCANVASPROJECTION_H
#define UTILITYCANVASPROJECTION_H

#include <QVector>
#include "objects/LatLon.h"
#include "util/ProjectionNumbers.h"

class UtilityCanvasProjection {
public:
    static QVector<float> computeMercatorNumbers(float, float, const ProjectionNumbers&);
    static QVector<float> computeMercatorNumbersFromLatLon(const LatLon&, const ProjectionNumbers&);
};

#endif  // UTILITYCANVASPROJECTION_H
