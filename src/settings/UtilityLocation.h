// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef UTILITYLOCATION_H
#define UTILITYLOCATION_H

#include <string>
#include <unordered_map>
#include <vector>
#include "objects/LatLon.h"
#include "objects/OfficeTypeEnum.h"
#include "radar/RID.h"

using std::string;
using std::unordered_map;
using std::vector;

class UtilityLocation {
public:
    static vector<RID> getNearestRadarSites(const LatLon&, int, bool = true);
    static LatLon getSiteLocation(const string&, OfficeTypeEnum);
    static string getNearestOffice(const string&, const LatLon&);
    static LatLon getCenterOfPolygon(const vector<LatLon>&);
    static string getRadarSiteName(const string&);
    static LatLon getRadarSiteLatLon(const string&);
    static string getRadarSiteX(const string&);
    static string getRadarSiteY(const string&);
    static LatLon getWfoSiteLatLon(const string&);
    static LatLon getSoundingSiteLatLon(const string&);
    static string getNearest(const LatLon&, const unordered_map<string, LatLon>&);
};

#endif  // UTILITYLOCATION_H
