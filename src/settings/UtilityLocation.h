// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef UTILITYLOCATION_H
#define UTILITYLOCATION_H

#include <string>
#include <vector>
#include "objects/LatLon.h"
#include "radar/RID.h"

using std::string;
using std::vector;

class UtilityLocation {
public:
    static vector<RID> getNearestRadarSites(const LatLon&, int, bool = true);
    static LatLon getSiteLocation(const string&, const string& = "RID");
    static string getNearestOffice(const string&, const LatLon&);
    static LatLon getCenterOfPolygon(const vector<LatLon>&);
};

#endif  // UTILITYLOCATION_H
