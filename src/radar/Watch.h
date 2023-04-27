// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef UTILITYWATCH_H
#define UTILITYWATCH_H

#include <string>
#include <vector>
#include "objects/LatLon.h"
#include "radar/PolygonType.h"
#include "radar/ProjectionNumbers.h"

using std::string;
using std::vector;

class Watch {
public:
    static vector<double> add(const ProjectionNumbers&, PolygonType);
    static string show(const LatLon&, PolygonType);
};

#endif  // UTILITYWATCH_H
