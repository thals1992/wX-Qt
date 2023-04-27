// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef WXGLNEXRADLEVEL3COMMON_H
#define WXGLNEXRADLEVEL3COMMON_H

#include <vector>
#include "external/ExternalGeodeticCalculator.h"
#include "external/ExternalGlobalCoordinates.h"
#include "radar/ProjectionNumbers.h"

using std::vector;

class NexradLevel3Common {
public:
    static vector<double> drawLine(const ExternalGlobalCoordinates&, const ProjectionNumbers&, double, double);
    static vector<double> drawLine(const vector<double>&, const ProjectionNumbers&, const ExternalGlobalCoordinates&, double, double);
    static vector<double> computeMercatorNumbersFromEc(const ExternalGlobalCoordinates&, const ProjectionNumbers&);
};

#endif  // WXGLNEXRADLEVEL3COMMON_H
