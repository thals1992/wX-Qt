// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef WXGLPOLYGONWARNINGS_H
#define WXGLPOLYGONWARNINGS_H

#include <string>
#include <vector>
#include "objects/LatLon.h"
#include "objects/PolygonWarning.h"
#include "radar/PolygonType.h"
#include "radar/ProjectionNumbers.h"

using std::string;
using std::vector;

class Warnings {
public:
    static vector<double> addGeneric(const ProjectionNumbers& projectionNumbers, const PolygonWarning *);
    static vector<double> add(const ProjectionNumbers&, const PolygonType&);
    static int getCount(const PolygonType&);
    static string show(const LatLon&);
};

#endif  // WXGLPOLYGONWARNINGS_H
