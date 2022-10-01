// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef UTILITYCANVASPROJECTION_H
#define UTILITYCANVASPROJECTION_H

#include <vector>
#include "objects/LatLon.h"
#include "radar/ProjectionNumbers.h"

using std::vector;

class UtilityCanvasProjection {
public:
    static vector<double> computeMercatorNumbers(double, double, const ProjectionNumbers&);
    static vector<double> computeMercatorNumbersFromLatLon(const LatLon&, const ProjectionNumbers&, int factor = 1.0);
};

#endif  // UTILITYCANVASPROJECTION_H
